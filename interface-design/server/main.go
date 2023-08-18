package main

import (
	"fmt"
	"io"
	"net/http"

	"golang.org/x/net/websocket"
)

var clientWs *websocket.Conn
var browserWs *websocket.Conn
var data []byte

func commandsHandler(ws *websocket.Conn) {
	fmt.Println("Connection established with local client:", ws.RemoteAddr())

	buf := make([]byte, 1048576)
	clientWs = ws

	for {
		n, err := ws.Read(buf)

		if err != nil {
			if err == io.EOF {
				break
			}

			fmt.Println(err)
			continue
		}

		data = buf[:n]

		if browserWs != nil {
			browserWs.Write(data)
		}
	}
}

func processesHandler(ws *websocket.Conn) {
	fmt.Println("Connection established with browser client:", ws.RemoteAddr())

	browserWs = ws
	browserWs.Write(data)

	toClient(ws, clientWs)
}

func toClient(ws *websocket.Conn, target *websocket.Conn) {
	buf := make([]byte, 1048576)

	for {
		n, err := ws.Read(buf)

		if err != nil {
			if err == io.EOF {
				break
			}

			fmt.Println(err)
			continue
		}

		msg := buf[:n]

		target.Write([]byte(string(msg)))
	}
}

func main() {
	fmt.Println("Starting server at port 8080")

	http.Handle("/commands", websocket.Handler(commandsHandler))
	http.Handle("/processes", websocket.Handler(processesHandler))

	http.ListenAndServe(":8080", nil)
}
