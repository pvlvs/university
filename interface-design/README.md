# Connected

A prototype for the university module _interface design_.

**Connected** is a dashboard, to which one can connect a computer. The dashboard takes all the required data, that is collected by the connected computer. After that, the brightness, the battery percentage and all the active processes (limited to fifty) with their power consumption will be displayed.

When everything is set up correctly, the user additionally can change the brightness, suspend or poweroff the connected machine or stop a process.

## Technologies

The project is divided in to three parts. The desktop client, the server and the b client.

For presentation purposes I had to fall back to [planetscale](https://www.planetscale.com), as I could't find a free alternative to [railway](https://railway.app/), which requires a 90 day old GitHub account, that I could't provide.

### The desktop client

The desktop client is a simple script written in go. It generates a .csv file with the help off [powertop](https://github.com/fenrus75/powertop). After that, it reads out the required data for battery percentage, if the connected machine is charging, and the screen brightness.

Being connected to the server vie a websocket, it also listens to commands, that were send by the browser and executes the corresponding command.

The code can be found under /client/main.go.

### The server

A very simple web server written in go. It sends the desktops data to the browser and the browsers commands to the desktop.

The code can be found under /server/main.go.

### the browser client

The browser client is a simple web application written with [SvelteKit](https://kit.svelte.dev/) in TypeScript. Instead of npm this project uses [pnpm](https://pnpm.io/). To install all required dependencies run `pnpm install` or `pnpm i` for short.

## Running the Project

As this is a mere prototype, it only runs on linux. As linux distributions are flavorful, the desktop client might not find the required data, as different distributions store information in different places. The prototype was written on and execute on [Arch Linux](https://archlinux.org/).

To run the project you'll need to run the server with `go run /server/main.go`, run the desktop client with `go run /client/main.go` and serve the dashboard with `pnpm run dev`.
