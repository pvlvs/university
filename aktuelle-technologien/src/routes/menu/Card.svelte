<script lang="ts">
  import type { MenuCategory, MenuItem } from '$lib/interfaces/Menu.interface';
  import { categoriesStore, orderStore } from '../../store';

  let selected: MenuItem[] = [];
  let categories: MenuCategory[] = [];
  $: selected, categories;

  categoriesStore.subscribe((value) => {
    categories = value;
  });

  orderStore.subscribe((value) => {
    selected = value;
  });

  function selectItem(item: MenuItem) {
    if (selected.includes(item)) {
      if (!selected[selected.indexOf(item)].count) {
        selected[selected.indexOf(item)].count = 1;
      }
      selected[selected.indexOf(item)].count! += 1;
    } else {
      selected = [...selected, item];
    }

    orderStore.set(selected);
  }

  function createInfoString(item: MenuItem): string {
    let infoStr = item.info;
    const addStr =
      '(' +
      item.allergens
        .concat(item.additives)
        .map((a) => a.split(') ')[0].split('(')[1])
        .join(', ') +
      ')';

    if (infoStr && addStr.length > 2) {
      infoStr += `${addStr && ', '} ${addStr}`;
    } else if (addStr.length > 2) {
      infoStr = addStr;
    }

    return infoStr;
  }
</script>

<div class="col-span-2 my-32 p-6 shadow-lg xl:my-0">
  {#each categories as category}
    <section>
      <h2 class="mb-8 text-center text-3xl">{category.title}</h2>
      <ul class="mb-16 flex flex-col gap-y-6">
        {#each category.items as item}
          <li class="flex gap-x-4">
            <button
              on:click={() => selectItem(item)}
              class="flex place-content-center"
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
              >
                <path stroke="none" d="M0 0h24v24H0z" fill="none" />
                <path d="M6 19m-2 0a2 2 0 1 0 4 0a2 2 0 1 0 -4 0" />
                <path d="M17 19m-2 0a2 2 0 1 0 4 0a2 2 0 1 0 -4 0" />
                <path d="M17 17h-11v-14h-2" />
                <path d="M6 5l6 .429m7.138 6.573l-.143 1h-13" />
                <path d="M15 6h6m-3 -3v6" />
              </svg>
            </button>
            <div>
              <h3 class="xl:text-2xl">{item.name}</h3>
              <p class="xl:text-base">{createInfoString(item)}</p>
            </div>
            <span class="ml-auto whitespace-nowrap text-2xl">{item.price}€</span
            >
          </li>
        {/each}
      </ul>
    </section>
  {/each}
</div>
