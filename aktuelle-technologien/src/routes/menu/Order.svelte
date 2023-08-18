<script lang="ts">
  import type { MenuItem } from '$lib/interfaces/Menu.interface';
  import { orderStore } from '../../store';
  import { goto } from '$app/navigation';

  let container: HTMLElement;
  let menu: HTMLElement;
  let button: HTMLButtonElement;

  let selected: MenuItem[] = [];

  $: selected && calculateTotal();
  $: disabled = !selected.length;
  $: total = 0;

  orderStore.subscribe((value) => {
    selected = value;
  });

  function calculateTotal() {
    total = 0;

    selected.forEach((item) => {
      total += item.price * (item.count ?? 1);
    });
  }

  function removeItem(item: MenuItem) {
    if (
      selected[selected.indexOf(item)].count &&
      selected[selected.indexOf(item)].count! > 1
    ) {
      selected[selected.indexOf(item)].count! -= 1;
    } else {
      selected.splice(selected.indexOf(item), 1);
      orderStore.set(selected);
    }

    calculateTotal();
  }

  function toggleMenu(): void {
    container.classList.toggle('left-8');
    container.classList.toggle('z-20');
    container.classList.toggle('shadow-md');
    container.classList.toggle('rounded-b-xl');
    menu.classList.toggle('hidden');
    menu.classList.toggle('flex');
    button.classList.toggle('w-full');
    button.classList.toggle('rounded-full');
    button.classList.toggle('rounded-t-xl');

    button.children[0].classList.toggle('hidden');
  }
</script>

<section
  bind:this={container}
  class="absolute right-8 top-32 bg-white xl:static"
>
  <button
    bind:this={button}
    on:click={toggleMenu}
    class="flex justify-end gap-x-4 rounded-full bg-green p-2 xl:hidden"
  >
    <span class="hidden text-lg text-white">Order</span>

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
        d="M19 3v12h-5c-.023 -3.681 .184 -7.406 5 -12zm0 12v6h-1v-3m-10 
        -14v17m-3 -17v3a3 3 0 1 0 6 0v-3"
      />
    </svg>
  </button>

  <section
    bind:this={menu}
    class="hidden h-fit flex-col rounded-b-md shadow-md xl:flex"
  >
    <h2
      class="hidden items-center justify-center gap-x-1 rounded-t-md bg-green p-4 text-white xl:flex"
    >
      <span>Order</span>

      <svg
        width="16"
        height="16"
        viewBox="0 0 24 24"
        stroke-width="2"
        stroke="white"
        fill="none"
        stroke-linecap="round"
        stroke-linejoin="round"
        class="mb-1"
      >
        <path stroke="none" d="M0 0h24v24H0z" fill="none" />
        <path
          d="M19 3v12h-5c-.023 -3.681 .184 -7.406 5 -12zm0 12v6h-1v-3m-10 -14v17m-3 -17v3a3 3 0 1 0 6 0v-3"
        />
      </svg>
    </h2>

    <ul class="flex flex-col gap-y-4 px-6 pt-4">
      {#each selected as item}
        <li class="flex items-baseline justify-between gap-x-4">
          <div class="mr-auto flex flex-col">
            <span
              >{item.name}
              <span class="text-green"
                >{item.count && item.count > 1 ? `x${item.count}` : ''}</span
              ></span
            >
            <span class="text-xs">{item.info}</span>
          </div>

          <span class="whitespace-nowrap">{(+item.price).toFixed(2)}€</span>

          <button on:click={() => removeItem(item)}>
            <svg
              width="16"
              height="16"
              viewBox="0 0 24 24"
              stroke-width="2"
              stroke="currentColor"
              fill="none"
              stroke-linecap="round"
              stroke-linejoin="round"
              class="text-red"
            >
              <path stroke="none" d="M0 0h24v24H0z" fill="none" />
              <path d="M18 6l-12 12" />
              <path d="M6 6l12 12" />
            </svg>
          </button>
        </li>
      {/each}

      <li
        class={`flex justify-between ${
          disabled ? 'opacity-50' : ' border-t border-t-black pt-4 text-green'
        }`}
      >
        <span>Total</span>
        <span class="pr-8">{total.toFixed(2)}€</span>
      </li>
    </ul>

    <button
      {disabled}
      on:click={() => goto('/checkout')}
      class="mx-auto mb-6 mt-8 block rounded-md bg-green px-4 py-2 text-white {disabled &&
        'opacity-50'}">Order Now</button
    >
  </section>
</section>
