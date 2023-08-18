<script lang="ts">
	import History from '$lib/History.svelte';
	import Side from '$lib/Side.svelte';
	import ProcessTable from '$lib/ProcessTable.svelte';
	import type { PageData } from './$types';

	export let data: PageData;
</script>

<svelte:head>
	<title>{data.title}</title>
</svelte:head>

<main class="2xl:h-[calc(100vh-7rem)] py-16 flex flex-col 2xl:grid 2xl:grid-cols-5 gap-8">
	<Side deviceId={data.deviceId} />

	<ProcessTable deviceId={data.deviceId} />

	<History entries={data.entries} />
</main>
