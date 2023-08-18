<script lang="ts">
	import type { Process } from './data.interface';
	import { handleProcess, wsState } from './db';

	export let deviceId: number;

	let processes: Process[] = [];
	let deleted: string[] = [];
	let orderObj = {
		order: 'consumption',
		direction: 'desc'
	};

	$: processes = [];
	$: deleted, deviceId;
	$: total = 0;
	$: timeSinceData = 0;

	wsState.subscribe((state) => {
		if (state && state.client_id === deviceId && state.processes && state.processes != processes) {
			processes = state.processes ?? [];
			timeSinceData = 0;

			sortProcesses();
		}
	});

	setInterval(() => {
		timeSinceData++;
	}, 1000);

	async function killProcess(pid: string): Promise<void> {
		// handleProcess(deviceId, pid);

		await fetch('/api/data', {
			method: 'POST',
			body: JSON.stringify({
				device_id: deviceId,
				type: 'kill',
				pid: pid
			}),
			headers: {
				'content-type': 'application/json'
			}
		});

		deleted.push(pid);
		deleted = deleted;

		setTimeout(() => {
			const processId: number = processes.findIndex((p) => p.pid === pid);

			processes.splice(processId, 1);
			deleted.splice(deleted.indexOf(pid), 1);

			deleted = deleted;
			processes = processes;
		}, 1500);
	}

	function sortBy(isName: boolean = false): void {
		const dir = orderObj.direction;
		const order = orderObj.order;

		if (order === 'consumption' && isName) {
			orderObj.direction = 'asc';
		} else if (order === 'name' && !isName) {
			orderObj.direction = 'desc';
		} else {
			orderObj.direction = dir === 'asc' ? 'desc' : 'asc';
		}

		if (isName) {
			orderObj.order = 'name';
		} else {
			orderObj.order = 'consumption';
		}

		orderObj = orderObj;

		sortProcesses();
	}

	function sortProcesses(): void {
		const sortByCon = (a: Process, b: Process) => {
			const consumptionSplitOne = a.consumption.split(' ');
			const consumptionSplitTwo = b.consumption.split(' ');
			const conOneUnit = consumptionSplitOne[1];
			const conTwoUnit = consumptionSplitTwo[1];
			let conOne = Number(consumptionSplitOne[0]);
			let conTwo = Number(consumptionSplitTwo[0]);

			if (conOneUnit === 'mW') {
				conOne *= 1000;
			}
			if (conTwoUnit === 'mW') {
				conTwo *= 1000;
			}
			return conOne - conTwo;
		};

		if (orderObj.order === 'name') {
			switch (orderObj.direction) {
				case 'asc':
					processes.sort((a, b) => a.name.toLowerCase().localeCompare(b.name.toLowerCase()));
					break;
				case 'desc':
					processes.sort((a, b) => b.name.toLowerCase().localeCompare(a.name.toLowerCase()));
					break;
				default:
					processes.sort((a, b) => sortByCon(a, b));
			}
		} else {
			switch (orderObj.direction) {
				case 'asc':
					processes.sort((a, b) => sortByCon(a, b));

					break;
				case 'desc':
					processes.sort((a, b) => sortByCon(b, a));

					break;
				default:
					processes.sort((a, b) => sortByCon(a, b));
			}
		}

		processes = processes;
	}
</script>

<section
	class="h-[calc(100vh-12rem)] 2xl:h-[calc(100vh-25rem)] pt-4 pb-28 col-span-3 relative bg-white drop-shadow-lg overflow-hidden rounded"
>
	<h2 class="text-2xl px-8">Active Processes</h2>
	<h3 class="px-8 mb-4">Last update: {timeSinceData}s ago</h3>

	<div class="box-border h-full mt-14 px-8 overflow-y-scroll">
		<table class="w-full">
			<thead class="h-13 absolute top-20 left-8 right-8 grid grid-cols-12">
				<th class="col-span-6 py-2 font-normal text-sm text-left">
					<button on:click={() => sortBy(true)} class="flex gap-x-1">
						<span>NAME</span>
						{#if orderObj.order === 'name'}
							<svg
								width="20"
								height="20"
								viewBox="0 0 24 24"
								stroke-width="2"
								stroke="currentColor"
								fill="none"
								stroke-linecap="round"
								stroke-linejoin="round"
							>
								{#if orderObj.direction === 'asc'}
									<path stroke="none" d="M0 0h24v24H0z" fill="none" />
									<path d="M15 10v-5c0 -1.38 .62 -2 2 -2s2 .62 2 2v5m0 -3h-4" />
									<path d="M19 21h-4l4 -7h-4" />
									<path d="M4 15l3 3l3 -3" />
									<path d="M7 6v12" />
								{:else if orderObj.direction === 'desc'}
									<path stroke="none" d="M0 0h24v24H0z" fill="none" />
									<path d="M15 21v-5c0 -1.38 .62 -2 2 -2s2 .62 2 2v5m0 -3h-4" />
									<path d="M19 10h-4l4 -7h-4" />
									<path d="M4 15l3 3l3 -3" />
									<path d="M7 6v12" />
								{/if}
							</svg>
						{:else}
							<svg
								width="20"
								height="20"
								viewBox="0 0 24 24"
								stroke-width="2"
								stroke="currentColor"
								fill="none"
								stroke-linecap="round"
								stroke-linejoin="round"
								class="text-neutral-500"
							>
								<path stroke="none" d="M0 0h24v24H0z" fill="none" />
								<path d="M15 10v-5c0 -1.38 .62 -2 2 -2s2 .62 2 2v5m0 -3h-4" />
								<path d="M19 21h-4l4 -7h-4" />
								<path d="M4 15l3 3l3 -3" />
								<path d="M7 6v12" />
							</svg>
						{/if}
					</button>
				</th>
				<th class="col-span-3 py-2 px-4 font-normal text-sm text-right">ACTIONS</th>
				<th class="col-span-3 py-2 font-normal text-sm">
					<button on:click={() => sortBy()} class="ml-auto flex gap-x-1">
						<span>USE</span>
						{#if orderObj.order === 'consumption'}
							<svg
								width="20"
								height="20"
								viewBox="0 0 24 24"
								stroke-width="2"
								stroke="currentColor"
								fill="none"
								stroke-linecap="round"
								stroke-linejoin="round"
							>
								{#if orderObj.direction === 'asc'}
									<path stroke="none" d="M0 0h24v24H0z" fill="none" />
									<path d="M4 15l3 3l3 -3" />
									<path d="M7 6v12" />
									<path d="M17 3a2 2 0 0 1 2 2v3a2 2 0 1 1 -4 0v-3a2 2 0 0 1 2 -2z" />
									<path d="M17 16m-2 0a2 2 0 1 0 4 0a2 2 0 1 0 -4 0" />
									<path d="M19 16v3a2 2 0 0 1 -2 2h-1.5" />
								{:else}
									<path stroke="none" d="M0 0h24v24H0z" fill="none" />
									<path d="M4 15l3 3l3 -3" />
									<path d="M7 6v12" />
									<path d="M17 14a2 2 0 0 1 2 2v3a2 2 0 1 1 -4 0v-3a2 2 0 0 1 2 -2z" />
									<path d="M17 5m-2 0a2 2 0 1 0 4 0a2 2 0 1 0 -4 0" />
									<path d="M19 5v3a2 2 0 0 1 -2 2h-1.5" />
								{/if}
							</svg>
						{:else}
							<svg
								width="20"
								height="20"
								viewBox="0 0 24 24"
								stroke-width="2"
								stroke="currentColor"
								fill="none"
								stroke-linecap="round"
								stroke-linejoin="round"
								class="text-neutral-500"
							>
								<path stroke="none" d="M0 0h24v24H0z" fill="none" />
								<path d="M4 15l3 3l3 -3" />
								<path d="M7 6v12" />
								<path d="M17 14a2 2 0 0 1 2 2v3a2 2 0 1 1 -4 0v-3a2 2 0 0 1 2 -2z" />
								<path d="M17 5m-2 0a2 2 0 1 0 4 0a2 2 0 1 0 -4 0" />
								<path d="M19 5v3a2 2 0 0 1 -2 2h-1.5" />
							</svg>
						{/if}
					</button>
				</th>
			</thead>
			<tbody>
				{#each processes as process}
					{#if deleted.includes(process.pid)}
						<tr class=" border-t border-neutral-200 bg-red-600 text-white">
							<td colspan="3" class="py-3 text-center">Process stopped.</td>
						</tr>
					{:else}
						<tr class="h-13 border-t border-neutral-200 grid grid-cols-12">
							<td class="col-span-6 py-2 text-left">{process.name}</td>
							<td class="col-span-3 py-2">
								<button
									class="ml-auto py-1 px-2 flex gap-x-2 hover:bg-red-600 rounded-sm transition-colors duration-300 group"
									on:click={() => killProcess(process.pid)}
								>
									<span
										class="group-hover:text-white transition-colors duration-300 hidden sm:block"
										>STOP</span
									>
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="text-red-600 group-hover:text-white transition-colors duration-300"
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
										<path d="M18 6l-12 12" />
										<path d="M6 6l12 12" />
									</svg>
								</button>
							</td>
							<td class="col-span-3 py-2 text-right">{process.consumption}</td>
						</tr>
					{/if}
				{/each}

				{#if !processes.length}
					<tr class="border-t border-neutral-200">
						<td colspan="3" class="pt-4 text-left">There is no active process.</td>
					</tr>
				{/if}
			</tbody>
		</table>
	</div>

	<div class="py-4 px-8 flex justify-between border-t bg-white">
		<span>Month total:</span>
		<span>{total} W</span>
	</div>
</section>
