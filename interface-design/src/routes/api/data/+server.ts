import type { RequestHandler } from './$types';
import { connect } from '@planetscale/database';
import { PS_HOST, PS_USERNAME, PS_PASSWORD } from '$env/static/private';

const config = {
	host: PS_HOST,
	username: PS_USERNAME,
	password: PS_PASSWORD
};
const connection = connect(config);

export const GET = (async () => {
	const results = await connection.execute('SELECT * FROM client_data WHERE id = 1;', [1]);

	return new Response(JSON.stringify(results.rows[0]));
}) satisfies RequestHandler;

export const POST = (async ({ request }) => {
	const data = await request.json();

	switch (data.type) {
		case 'kill':
			handleProcess(data.device_id, data.pid);
			break;
		case 'sleep':
			handleSleep(data.device_id);
			break;
		case 'power':
			handlePower(data.device_id);
			break;
		case 'brightness':
			handleBrightness(data.device_id, data.brightness);
			break;
	}

	return new Response(JSON.stringify('Success!'));
}) satisfies RequestHandler;

function handleProcess(deviceId: number, pid: string): void {
	connection.execute(
		`UPDATE messages SET type='kill', device_id='${deviceId}', pid='${pid}' WHERE id='1';`
	);
}

function handleSleep(deviceId: number): void {
	connection.execute(`UPDATE messages SET type='sleep', device_id='${deviceId}' WHERE id='1';`);
}

function handlePower(deviceId: number): void {
	connection.execute(`UPDATE messages SET type='power', device_id='${deviceId}' WHERE id='1';`);
}

function handleBrightness(deviceId: number, brightness: number): void {
	connection.execute(
		`UPDATE messages SET type='brightness', device_id='${deviceId}' , brightness='${brightness}' WHERE id='1';`
	);
}
