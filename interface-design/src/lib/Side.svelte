<script lang="ts">
	import { handleBrightness, handlePower, handleSleep, wsState } from './db';
	export let deviceId: number;

	$: brightness = 1500;
	$: capacity = 100;
	$: charging = false;

	wsState.subscribe((state) => {
		if (state) {
			brightness = state.brightness;
			capacity = state.capacity;
			charging = state.charging;
		}
	});

	async function changeBrightness() {
		// handleBrightness(deviceId, brightness);

		await fetch('/api/data', {
			method: 'POST',
			body: JSON.stringify({
				type: 'brightness',
				device_id: deviceId,
				brightness: brightness
			}),
			headers: {
				'content-type': 'application/json'
			}
		});
	}

	async function toSleep() {
		// handleSleep(deviceId);

		await fetch('/api/data', {
			method: 'POST',
			body: JSON.stringify({
				type: 'sleep',
				device_id: deviceId
			}),
			headers: {
				'content-type': 'application/json'
			}
		});
	}

	async function powerOff() {
		// handlePower(deviceId);

		await fetch('/api/data', {
			method: 'POST',
			body: JSON.stringify({
				type: 'power',
				device_id: deviceId
			}),
			headers: {
				'content-type': 'application/json'
			}
		});
	}
</script>

<section class="col-span-full flex flex-col lg:grid lg:grid-cols-5 gap-8">
	<div class="h-full px-8 py-4 bg-white drop-shadow-lg rounded col-span-3">
		<h2 class="mb-8 mr-auto text-2xl flex justify-between">
			<span>Brightness</span>
			<span
				style="color: {brightness > 1250 ? '#dc2626' : brightness > 750 ? '#ea580c' : '#16a34a'};"
			>
				{brightness}
			</span>
		</h2>

		<div class="flex flex-col gap-y-2">
			<div class="flex justify-between">
				<span>0</span>
				<span class="pl-8">500</span>
				<span>1000</span>
				<span>1500</span>
			</div>
			<input
				type="range"
				class="h-full"
				min="0"
				max="1500"
				bind:value={brightness}
				on:change={changeBrightness}
			/>
		</div>
	</div>

	<div class="p-4 flex flex-col gap-x-4 bg-white drop-shadow-lg rounded col-span-2">
		<h2 class="mb-8 text-2xl flex items-center gap-x-2">
			<span>Power</span>
			<span class="ml-auto">
				{#if charging}
					<svg
						class="text-green-600"
						width="32"
						height="32"
						viewBox="0 0 24 24"
						stroke-width="2"
						stroke="currentColor"
						fill="none"
						stroke-linecap="round"
						stroke-linejoin="round"
					>
						<path stroke="none" d="M0 0h24v24H0z" fill="none" />
						<path
							d="M4 9a2 2 0 0 1 2 -2h11a2 2 0 0 1 2 2v.5a.5 .5 0 0 0 .5 .5a.5 .5 0 0 1 .5 .5v3a.5 .5 0 0 1 -.5 .5a.5 .5 0 0 0 -.5 .5v.5a2 2 0 0 1 -2 2h-4.5"
						/>
						<path d="M3 15h6v2a2 2 0 0 1 -2 2h-2a2 2 0 0 1 -2 -2v-2z" />
						<path d="M6 22v-3" />
						<path d="M4 15v-2.5" />
						<path d="M8 15v-2.5" />
					</svg>
				{:else if capacity > 75}
					<svg
						class="text-green-600"
						width="32"
						height="32"
						viewBox="0 0 24 24"
						stroke-width="2"
						stroke="currentColor"
						fill="none"
						stroke-linecap="round"
						stroke-linejoin="round"
					>
						<path stroke="none" d="M0 0h24v24H0z" fill="none" />
						<path
							d="M6 7h11a2 2 0 0 1 2 2v.5a.5 .5 0 0 0 .5 .5a.5 .5 0 0 1 .5 .5v3a.5 .5 0 0 1 -.5 .5a.5 .5 0 0 0 -.5 .5v.5a2 2 0 0 1 -2 2h-11a2 2 0 0 1 -2 -2v-6a2 2 0 0 1 2 -2"
						/>
						<path d="M7 10l0 4" />
						<path d="M10 10l0 4" />
						<path d="M13 10l0 4" />
						<path d="M16 10l0 4" />
					</svg>
				{:else if capacity > 50}
					<svg
						class="text-orange-600"
						width="32"
						height="32"
						viewBox="0 0 24 24"
						stroke-width="2"
						stroke="currentColor"
						fill="none"
						stroke-linecap="round"
						stroke-linejoin="round"
					>
						<path stroke="none" d="M0 0h24v24H0z" fill="none" />
						<path
							d="M6 7h11a2 2 0 0 1 2 2v.5a.5 .5 0 0 0 .5 .5a.5 .5 0 0 1 .5 .5v3a.5 .5 0 0 1 -.5 .5a.5 .5 0 0 0 -.5 .5v.5a2 2 0 0 1 -2 2h-11a2 2 0 0 1 -2 -2v-6a2 2 0 0 1 2 -2"
						/>
						<path d="M7 10l0 4" />
						<path d="M10 10l0 4" />
						<path d="M13 10l0 4" />
					</svg>
				{:else if capacity > 25}
					<svg
						class="text-orange-600"
						width="32"
						height="32"
						viewBox="0 0 24 24"
						stroke-width="2"
						stroke="currentColor"
						fill="none"
						stroke-linecap="round"
						stroke-linejoin="round"
					>
						<path stroke="none" d="M0 0h24v24H0z" fill="none" />
						<path
							d="M6 7h11a2 2 0 0 1 2 2v.5a.5 .5 0 0 0 .5 .5a.5 .5 0 0 1 .5 .5v3a.5 .5 0 0 1 -.5 .5a.5 .5 0 0 0 -.5 .5v.5a2 2 0 0 1 -2 2h-11a2 2 0 0 1 -2 -2v-6a2 2 0 0 1 2 -2"
						/>
						<path d="M7 10l0 4" />
						<path d="M10 10l0 4" />
					</svg>
				{:else if capacity < 25}
					<svg
						class="text-red-600"
						width="32"
						height="32"
						viewBox="0 0 24 24"
						stroke-width="2"
						stroke="currentColor"
						fill="none"
						stroke-linecap="round"
						stroke-linejoin="round"
					>
						<path stroke="none" d="M0 0h24v24H0z" fill="none" />
						<path
							d="M6 7h11a2 2 0 0 1 2 2v.5a.5 .5 0 0 0 .5 .5a.5 .5 0 0 1 .5 .5v3a.5 .5 0 0 1 -.5 .5a.5 .5 0 0 0 -.5 .5v.5a2 2 0 0 1 -2 2h-11a2 2 0 0 1 -2 -2v-6a2 2 0 0 1 2 -2"
						/>
						<path d="M7 10l0 4" />
					</svg>
				{/if}
			</span> <span>{capacity ?? '-'}%</span>
		</h2>

		<div class="flex flex-wrap gap-4">
			<button
				class="min-w-[9rem] p-4 bg-green-600 hover:bg-green-700 transition text-white flex-1 flex gap-x-2 justify-center rounded-lg drop-shadow-md"
				on:click={toSleep}
			>
				Sleep
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="icon icon-tabler icon-tabler-zzz"
					width="24"
					height="24"
					viewBox="0 0 24 24"
					stroke-width="2"
					stroke="currentColor"
					fill="none"
					stroke-linecap="round"
					stroke-linejoin="round"
				>
					<path stroke="none" d="M0 0h24v24H0z" fill="none" />
					<path d="M4 12h6l-6 8h6" />
					<path d="M14 4h6l-6 8h6" />
				</svg>
			</button>
			<button
				class="min-w-[9rem] p-4 bg-red-600 hover:bg-red-700 transition text-white flex-1 flex gap-x-2 justify-center rounded-lg drop-shadow-md"
				on:click={powerOff}
			>
				Power Off
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="icon icon-tabler icon-tabler-power"
					width="24"
					height="24"
					viewBox="0 0 24 24"
					stroke-width="2"
					stroke="currentColor"
					fill="none"
					stroke-linecap="round"
					stroke-linejoin="round"
				>
					<path stroke="none" d="M0 0h24v24H0z" fill="none" />
					<path d="M7 6a7.75 7.75 0 1 0 10 0" />
					<path d="M12 4l0 8" />
				</svg>
			</button>
		</div>
	</div>
</section>
