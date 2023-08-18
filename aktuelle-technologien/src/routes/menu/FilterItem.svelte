<script lang="ts">
  import type {
    MenuCategory,
    MenuItem,
    activeFilter
  } from '$lib/interfaces/Menu.interface';
  import { categoriesStore } from '../../store';
  import menu from './menu.json';

  export let title: string;
  export let options: string[] = [];
  export let optionsType = '';
  export let active: activeFilter = {
    filter: [],
    allergens: [],
    additives: []
  };

  let open = false;
  let remainingOptions: string[] = [];
  $: remainingOptions;

  filterFilter();

  function updateActive(option: string): void {
    switch (optionsType) {
      case 'filter':
        active.filter.indexOf(option) > -1
          ? remove(active.filter, option)
          : add(active.filter, option);
        break;

      case 'additives':
        active.additives.indexOf(option) > -1
          ? remove(active.additives, option)
          : add(active.additives, option);
        break;

      case 'allergens':
        active.allergens.indexOf(option) > -1
          ? remove(active.allergens, option)
          : add(active.allergens, option);
        break;
    }
  }

  function add(target: string[], item: string): void {
    target.push(item);

    active = active;

    filterFilter();
  }

  function remove(target: string[], item: string): void {
    target.splice(target.indexOf(item), 1);

    active = active;

    filterFilter();
  }

  function filterFilter(): void {
    const categories: MenuCategory[] = JSON.parse(JSON.stringify(menu));
    let updatedCategories: MenuCategory[] = [...categories];
    remainingOptions = [];

    updatedCategories = [];

    categories.forEach((category: MenuCategory) => {
      category.items = category.items.filter((item: MenuItem) => {
        return (
          active.filter.every((f) => item.filter.includes(f)) &&
          active.allergens.every((f) => !item.allergens.includes(f)) &&
          active.additives.every((f) => !item.additives.includes(f))
        );
      });
    });

    categories.forEach((category: MenuCategory) => {
      if (category.items.length) {
        updatedCategories.push(category);
      }
    });

    updatedCategories.forEach((category: MenuCategory) => {
      category.items.forEach((item: MenuItem) => {
        item.filter.forEach((f) => {
          if (!remainingOptions.includes(f)) {
            remainingOptions.push(f);
          }
        });
        item.allergens.forEach((f) => {
          if (!remainingOptions.includes(f)) {
            remainingOptions.push(f);
          }
        });
        item.additives.forEach((f) => {
          if (!remainingOptions.includes(f)) {
            remainingOptions.push(f);
          }
        });
      });
    });

    categoriesStore.set(updatedCategories);
  }
</script>

<li>
  <button on:click={() => (open = !open)} class="flex w-full justify-between">
    <b>{title}</b>
    <svg
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
      {#if !open}
        <path d="M6 9l6 6l6 -6" />
      {:else}
        <path d="M6 15l6 -6l6 6" />
      {/if}
    </svg>
  </button>

  <ul class="my-2 {open ? 'flex' : 'hidden'} flex-col gap-y-3">
    {#each options as option}
      <li class="ml-4">
        <button
          on:click={() => updateActive(option)}
          disabled={!!(
            remainingOptions.length &&
            (optionsType === 'filter'
              ? !remainingOptions.includes(option)
              : !active.additives.includes(option) &&
                !active.allergens.includes(option) &&
                !remainingOptions.includes(option))
          )}
          class="w-full text-start {remainingOptions.length &&
            ((
              optionsType === 'filter'
                ? active.filter.includes(option)
                : optionsType === 'additives'
                ? active.additives.includes(option)
                : active.allergens.includes(option)
            )
              ? 'text-green'
              : !remainingOptions.includes(option) &&
                'text-black-transparent')}"
        >
          {option}
        </button>
      </li>
    {/each}
  </ul>
</li>
