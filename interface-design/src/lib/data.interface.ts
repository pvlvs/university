export interface Data {
	client_id: number;
	processes: Process[];
	brightness: number;
	capacity: number;
	charging: boolean;
}

export interface Process {
	pid: string;
	name: string;
	consumption: string;
}

export interface Entry {
	date: string;
	consumption: string;
	cost: number;
}

export interface Message {
	id: number;
	type: string;
	device_id: number;
	pid: string;
	brightness: number;
}
