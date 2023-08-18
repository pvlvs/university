<script lang="ts">
	import Header from '$lib/Header.svelte';
	import { onMount } from 'svelte';
	import '../app.css';
	import type { Data } from '$lib/data.interface';
	import { wsState } from '$lib/db';
	import { page } from '$app/stores';
	import { connect } from '$lib/db';

	onMount(() => {
		// connect();
		getData();
	});

	setInterval(getData, 3000000);

	async function getData(): Promise<void> {
		const response = await fetch(`${$page.url.origin}/api/data`);
		const data: Data = await response.json();

		wsState.set(data);
	}
</script>

<Header />

<slot />
