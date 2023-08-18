<script lang="ts">
	import type { Entry } from '$lib/data.interface';

	export let entries: Entry[];

	$: total = entries.reduce((prev, curr) => {
		return {
			date: curr.date,
			consumption: curr.consumption,
			cost: prev.cost + curr.cost
		};
	});
</script>

<section
	class="h-[calc(100vh-12rem)] 2xl:h-[calc(100vh-25rem)] max-h-full py-4 col-span-2 relative bg-white drop-shadow-lg overflow-hidden rounded"
>
	<h2 class="text-2xl px-8 mb-4">Use History</h2>

	<div class="h-[calc(100%-9.5rem)] mt-20 px-8 overflow-y-scroll">
		<table class="w-full">
			<thead class="h-13 absolute top-20 left-8 right-8 grid grid-cols-6">
				<th class="col-span-2 py-2 font-normal text-sm text-left">DATE</th>
				<th class="col-span-2 py-2 font-normal text-sm text-right">CONSUMPTION</th>
				<th class="col-span-2 py-2 font-normal text-sm text-right">COST</th>
			</thead>

			<tbody>
				{#each entries as entry}
					<tr class="border-t border-neutral-200 grid grid-cols-6">
						<td class="col-span-2 py-2 text-left">{entry.date}</td>
						<td class="col-span-2 py-2 text-right">{entry.consumption} kWh</td>
						<td class="col-span-2 py-2 text-right">{entry.cost.toFixed(2)} €</td>
					</tr>
				{/each}
			</tbody>
		</table>
	</div>

	<div class="py-4 px-8 flex justify-between border-t bg-white">
		<span>Month total:</span>
		<span>{total?.cost.toFixed(2)} €</span>
	</div>
</section>
