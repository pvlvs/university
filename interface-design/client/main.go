package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"os/exec"
	"reflect"
	"strconv"
	"strings"
	"time"

	"golang.org/x/net/websocket"
)

type Process struct {
	Pid         string `json:"pid"`
	Name        string `json:"name"`
	Consumption string `json:"consumption"`
}

type Message struct {
	Id         int
	Type       string `json:"type"`
	DeviceId   int    `json:"device_id"`
	Pid        string `json:"pid"`
	Brightness int    `json:"brightness"`
}

type Data struct {
	ClientId   int       `json:"client_id"`
	Processes  []Process `json:"processes"`
	Brightness int       `json:"brightness"`
	Capacity   int       `json:"capacity"`
	Charging   int       `json:"charging"`
}

var url string = "localhost:8080"
var data Data
var processes []Process

func initClient() {
	ws, err := websocket.Dial(fmt.Sprintf("ws://%s/commands", url), "", fmt.Sprintf("http://%s/", url))
	incomingMessages := make(chan string)

	if err != nil {
		fmt.Println("Dial failed: ", err.Error())
		os.Exit(1)
	}

	go func() {
		for {
			ws.Write(createData())
			time.Sleep(20 * time.Second)
		}
	}()

	go func() {
		for {
			newData := readData(processes)

			if !reflect.DeepEqual(newData, data) {
				data = newData
				msg, _ := json.Marshal(data)

				ws.Write(msg)
			}

			time.Sleep(250 * time.Millisecond)
		}
	}()

	go readMessages(ws, incomingMessages)

	for {
		var event Message

		message := <-incomingMessages
		err := json.Unmarshal([]byte(message), &event)

		if err != nil {
			fmt.Println(err)
			return
		}

		switch event.Type {
		case "kill":
			killCmd := exec.Command("kill", "-9", fmt.Sprint(event.Pid))
			killCmd.Run()
		case "sleep":
			suspendCmd := exec.Command("systemctl", "suspend")
			suspendCmd.Run()
		case "power":
			powerCmd := exec.Command("poweroff")
			powerCmd.Run()
		case "brightness":
			if err := os.WriteFile("/sys/class/backlight/intel_backlight/brightness", []byte(fmt.Sprint(event.Brightness)), 0666); err != nil {
				log.Fatal(err)
			}

			data.Brightness = event.Brightness
		}
	}
}

func readMessages(ws *websocket.Conn, incomingMessages chan string) {
	for {
		var message string

		if err := websocket.Message.Receive(ws, &message); err != nil {
			fmt.Println("Error: ", err.Error())
			return
		}

		incomingMessages <- message
	}
}

func createData() []byte {
	var splitIndex int

	lines := []string{}
	processStrings := []string{}

	powertopCmd := exec.Command("sudo", "powertop", "--csv")
	if err := powertopCmd.Run(); err != nil {
		log.Fatal(err)
	}

	file, err := os.Open("powertop.csv")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		if err != nil {
			fmt.Println("Dial failed: ", err.Error())
			os.Exit(1)
		}
		lines = append(lines, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	for i := range lines {
		if lines[i] == " *  *  *   Overview of Software Power Consumers   *  *  *" {
			splitIndex = i
			break
		}
	}

	for _, line := range lines[splitIndex:] {
		if strings.Contains(line, "PID") {
			processStrings = append(processStrings, line)
		}
	}

	filterProcesses(processStrings, &processes)

	data = readData(processes)

	msg, _ := json.Marshal(data)

	return msg
}

func filterProcesses(processStrings []string, processes *[]Process) {
	*processes = nil

	for _, str := range processStrings {
		if strings.Contains(str, "PID") {
			consumptionSplit := strings.Split(str, "; ")
			consumption := strings.TrimSpace(consumptionSplit[len(consumptionSplit)-1])

			if consumption != "0 mW" {
				pid := stringBetween(str, "PID", "]")
				processName := stringBetween(str, "]", ";")
				pathName := stringBetween(processName, " ", " ")
				name := strings.Split(pathName, "/")[len(strings.Split(pathName, "/"))-1]

				if pathName == "" {
					pathName = stringBetween(processName, "[", "]")
					name = strings.Split(pathName, "/")[0]
				}

				if strings.TrimSpace(processName) == "" || strings.TrimSpace(pathName) == "" {
					name = processName
				}

				*processes = append(*processes, Process{
					Pid:         strings.TrimSpace(pid),
					Name:        strings.TrimSpace(name),
					Consumption: strings.TrimSpace(consumption),
				})
			}
		}
	}

	if len(*processes) >= 50 {
		*processes = (*processes)[:49]
	}
}

func readData(processes []Process) (data Data) {
	var charging int

	brightness, _ := os.ReadFile("/sys/class/backlight/intel_backlight/brightness")
	capacity, _ := os.ReadFile("/sys/class/power_supply/BAT1/capacity")
	status, _ := os.ReadFile("/sys/class/power_supply/BAT1/status")

	brightnessValue, _ := strconv.Atoi(strings.TrimSpace(string(brightness)))
	capacityValue, _ := strconv.Atoi(strings.TrimSpace(string(capacity)))
	chargingBool := strings.TrimSpace(string(status)) != "Discharging"

	if chargingBool {
		charging = 1
	}

	data = Data{
		ClientId:   2,
		Processes:  processes,
		Brightness: brightnessValue,
		Capacity:   capacityValue,
		Charging:   charging,
	}

	return
}

func stringBetween(str string, start string, end string) (result string) {
	s := strings.Index(str, start)

	if s == -1 {
		return
	}

	s += len(start)
	e := strings.Index(str[s:], end)

	if e == -1 {
		return
	}

	e += s

	return str[s:e]
}

func main() {
	fmt.Println("Starting Client")

	initClient()
}
