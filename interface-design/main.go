package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"time"

	"database/sql"

	_ "github.com/go-sql-driver/mysql"

	"github.com/joho/godotenv"
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

func handleCommands(message Message, db *sql.DB) string {
	switch message.Type {
	case "kill":
		killCmd := exec.Command("kill", "-9", fmt.Sprint(message.Pid))
		killCmd.Run()
	case "sleep":
		suspendCmd := exec.Command("systemctl", "suspend")
		suspendCmd.Run()
	case "power":
		powerCmd := exec.Command("poweroff")
		powerCmd.Run()
	case "brightness":
		if err := os.WriteFile("/sys/class/backlight/intel_backlight/brightness", []byte(fmt.Sprint(message.Brightness)), 0666); err != nil {
			log.Fatal(err)
		}
	}

	_, err := db.Exec(`UPDATE messages SET type='', pid=? WHERE id=?`, 0, 1)
	if err != nil {
		log.Fatal("Failed to update messages", err)
	}

	query := "UPDATE messages SET type='', pid='0' WHERE id='1';"
	return query
}

func createData(db *sql.DB) {
	var splitIndex int

	processes := []Process{}
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

	// brightnessValue := 200
	// capacityValue := 75
	// charging = 0

	data, _ := json.Marshal(processes)

	_, err = db.Exec(`UPDATE client_data SET client_id=?, processes=CAST(? as JSON), brightness=?, capacity=?, charging=? WHERE id=?`, 2, data, brightnessValue, capacityValue, charging, 1)
	if err != nil {
		log.Fatal("Failed to create data", err)
	}
}

func filterProcesses(processStrings []string, processes *[]Process) {
	for _, str := range processStrings {
		if strings.Contains(str, "PID") {
			pid := stringBetween(str, "PID", "]")
			processName := stringBetween(str, "]", ";")
			pathName := stringBetween(processName, " ", " ")
			name := strings.Split(pathName, "/")[len(strings.Split(pathName, "/"))-1]
			consumptionSplit := strings.Split(str, "; ")
			consumption := strings.TrimSpace(consumptionSplit[len(consumptionSplit)-1])

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
	err := godotenv.Load()
	if err != nil {
		log.Fatal("failed to load env", err)
	}

	db, err := sql.Open("mysql", os.Getenv("DSN"))
	if err != nil {
		log.Fatalf("failed to connect: %v", err)
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		log.Fatalf("failed to ping: %v", err)
	}

	log.Println("Successfully connected to PlanetScale!")

	go func() {
		for {
			createData(db)
		}
	}()

	for {
		var message Message

		err = db.QueryRow(`SELECT * FROM messages WHERE id = ?`, 1).Scan(&message.Id, &message.Type, &message.DeviceId, &message.Pid, &message.Brightness)
		if err != nil {
			log.Fatal("db.Exec", err)
		}

		if message.Type != "" {
			handleCommands(message, db)
		}

		time.Sleep(5 * time.Second)
	}
}
