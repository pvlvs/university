<script>
	import { page } from '$app/stores';
</script>

<header
	class="h-[6rem] p-4 sm:px-8 flex items-center gap-x-6 sm:gap-x-12 bg-green-600 text-white rounded-b-md font-bold drop-shadow-md"
>
	<h1 class="pr-6 sm:pr-12 text-3xl border-r">Connected</h1>
	<nav class="flex gap-x-4 items-center">
		<a
			href="/device/2"
			class={`py-2 px-4 flex gap-2 rounded-md drop-shadow-md ${
				$page.url.pathname === '/device/2' ? 'bg-white text-gray-950' : ''
			}`}
		>
			<svg
				xmlns="http://www.w3.org/2000/svg"
				class="icon icon-tabler icon-tabler-device-laptop"
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
				<path d="M3 19l18 0" />
				<path d="M5 6m0 1a1 1 0 0 1 1 -1h12a1 1 0 0 1 1 1v8a1 1 0 0 1 -1 1h-12a1 1 0 0 1 -1 -1z" />
			</svg>
			<span class="hidden sm:block">Mobile</span>
		</a>
		<button class="py-4 flex gap-2 rounded-sm">
			<svg
				xmlns="http://www.w3.org/2000/svg"
				class="icon icon-tabler icon-tabler-plus"
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
				<path d="M12 5l0 14" />
				<path d="M5 12l14 0" />
			</svg>
			<span class="hidden sm:block">Add</span>
		</button>
	</nav>
</header>
