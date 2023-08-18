<script lang="ts">
  import Header from '$lib/Header.svelte';
  import type { MenuItem } from '$lib/interfaces/Menu.interface';
  import Card from './Card.svelte';
  import Filter from './Filter.svelte';
  import Order from './Order.svelte';
</script>

<Header />

<main class="mt-16 block grid-cols-4 gap-x-16 xl:grid">
  <Filter />
  <Card />
  <Order />
</main>
