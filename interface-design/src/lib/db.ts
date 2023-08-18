import { writable } from 'svelte/store';
import type { Data, Message } from './data.interface';

export const wsState = writable<Data>();

let ws: WebSocket;
const messageObj: Message = { id: 1, type: '', device_id: 2, pid: '', brightness: 200 };

export function connect(): void {
	ws = new WebSocket('ws://localhost:8080/processes');

	ws.addEventListener('message', (message) => {
		if (message.data) {
			const data: Data = JSON.parse(message.data);

			if (data) {
				wsState.set(data);
				messageObj.brightness = data.brightness;
			}
		}
	});
}

export function handleProcess(deviceId: number, pid: string): void {
	messageObj.device_id = deviceId;
	messageObj.type = 'kill';
	messageObj.pid = pid;

	ws.send(JSON.stringify(messageObj));
}

export function handleSleep(deviceId: number): void {
	messageObj.device_id = deviceId;
	messageObj.type = 'sleep';

	ws.send(JSON.stringify(messageObj));
}

export function handlePower(deviceId: number): void {
	messageObj.device_id = deviceId;
	messageObj.type = 'power';

	ws.send(JSON.stringify(messageObj));
}

export function handleBrightness(deviceId: number, brightness: number): void {
	messageObj.device_id = deviceId;
	messageObj.type = 'brightness';
	messageObj.brightness = brightness;

	ws.send(JSON.stringify(messageObj));
}
