<script lang="ts">
  import FilterItem from './FilterItem.svelte';
  import type { activeFilter } from '$lib/interfaces/Menu.interface';

  let container: HTMLElement;
  let menu: HTMLElement;
  let button: HTMLButtonElement;

  let active: activeFilter = {
    filter: [],
    allergens: [],
    additives: []
  };
  $: active;

  const filters = [
    'Alcohol free',
    'Alcohol',
    'Meat',
    'Fish',
    'Warm',
    'Cold',
    'Vegetarian',
    'Vegan'
  ];
  const allergens = [
    '(a) Eier',
    '(b) Fisch',
    '(c) Krustentiere',
    '(d) Milch',
    '(e) Sellerie',
    '(f) Sesam',
    '(g) Dioxid und Sulfit',
    '(h) Erdnüsse',
    '(i) Lupine',
    '(k) Cashewnüsse',
    '(m) Sojabohnen',
    '(n) Weichtiere'
  ];
  const additives = [
    '(1) Farbstoffe',
    '(2) mit Antioxydationsmittel',
    '(3) chinhaltig',
    '(4) Süßungsmittel',
    '(5) Penylalalinquelle',
    '(6) Säurungsmittel',
    '(7) koffeinhaltig',
    '(8) Geschmacksverstärker'
  ];

  function toggleMenu(): void {
    container.classList.toggle('right-8');
    container.classList.toggle('z-20');
    container.classList.toggle('shadow-md');
    container.classList.toggle('rounded-b-xl');
    menu.classList.toggle('hidden');
    menu.classList.toggle('flex');
    button.classList.toggle('w-full');
    button.classList.toggle('rounded-full');
    button.classList.toggle('rounded-t-xl');

    button.children[1].classList.toggle('hidden');
  }
</script>

<section
  bind:this={container}
  class="absolute left-8 top-32 bg-white xl:static"
>
  <button
    bind:this={button}
    on:click={toggleMenu}
    class="flex gap-x-4 rounded-full bg-red p-2 xl:hidden"
  >
    <svg
      width="24"
      height="24"
      viewBox="0 0 24 24"
      stroke-width="2"
      stroke="currentColor"
      fill="none"
      stroke-linecap="round"
      stroke-linejoin="round"
      class="text-white"
    >
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path
        d="M4 4h16v2.172a2 2 0 0 1 -.586 1.414l-4.414 4.414v7l-6 2v-8.5l-4.48 
        -4.928a2 2 0 0 1 -.52 -1.345v-2.227z"
      />
    </svg>

    <span class="hidden text-lg text-white">Filter</span>
  </button>

  <ul bind:this={menu} class="hidden flex-col gap-y-2 px-6 py-4 xl:flex">
    <FilterItem
      title="Filter"
      optionsType="filter"
      options={filters}
      bind:active
    />
    <FilterItem
      title="Allergens"
      optionsType="allergens"
      options={allergens}
      bind:active
    />
    <FilterItem
      title="Additives"
      optionsType="additives"
      options={additives}
      bind:active
    />
  </ul>
</section>
