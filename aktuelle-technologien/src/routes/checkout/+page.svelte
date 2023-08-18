<script lang="ts">
  import type { MenuItem } from '$lib/interfaces/Menu.interface';
  import Header from '$lib/Header.svelte';
  import { orderStore, tablesStore } from '../../store';
  import ContentBox from './ContentBox.svelte';
  import ContentListItem from './ContentListItem.svelte';
  import type { Reservation } from '$lib/interfaces/Table.interface';
  import { onMount } from 'svelte';

  let order: MenuItem[] = [];
  let reservations: Reservation[] = [];
  let reservationsCost: number = 0;

  orderStore.subscribe((value) => {
    if (value.length) {
      order = value;
    }
  });

  tablesStore.subscribe((value) => {
    if (value.length) {
      reservations = value;
      reservationsCost = 10 + (reservations.length - 1) * 15;
    }
  });

  onMount(() => {
    tablesStore.set([]);
    orderStore.set([]);
  });
</script>

<Header isCheckout={true} />

<main
  class="pointer-events-none absolute inset-0 box-border flex h-fit min-h-screen flex-wrap items-center gap-32 px-8 py-32 xl:px-16"
>
  <section class="flex flex-1 flex-col gap-y-4 text-2xl">
    <h1 class="mb-8 text-5xl text-green">Thank you for your reservation!</h1>
    <p>
      Your reservation has been placed. Show the following QR-Code at arrival
      and you'll be guided to your table.
    </p>
    <p>
      If you don't arrive within fifteen minutes of your reservation, your
      rerservation expires.
    </p>
  </section>

  <section class="flex flex-1 flex-wrap gap-x-16 gap-y-4">
    <div class="flex flex-1 flex-col gap-4">
      {#if reservations.length}
        <ContentBox title="Reservation Contact">
          <ul class="flex flex-col gap-2">
            <ContentListItem>
              <span>Name</span>
              <span>Marlene Musta</span>
            </ContentListItem>
            <ContentListItem>
              <span>Phone Number</span>
              <span>0123/11928374</span>
            </ContentListItem>
          </ul>
        </ContentBox>
      {:else}
        <ContentBox title="Address">
          <ul class="flex flex-col gap-2">
            <ContentListItem>
              <span>Name</span>
              <span class="text-right">Marlene Musta</span>
            </ContentListItem>
            <ContentListItem>
              <span>Phone number</span>
              <span class="text-right"> 0123/11928374 </span>
            </ContentListItem>
            <ContentListItem>
              <span>Street</span>
              <span class="text-right">Marktstraße 13</span>
            </ContentListItem>
            <ContentListItem>
              <span>Postal Code</span>
              <span class="text-right">78120</span>
            </ContentListItem>
            <ContentListItem>
              <span>City</span>
              <span class="text-right">Furtwangen im Schwarzwald</span>
            </ContentListItem>
          </ul>
        </ContentBox>
      {/if}

      <ContentBox title="Payment Method">
        <ContentListItem>
          <span>Paypal</span>
          <span class="text-right">(example@mail.com)</span>
        </ContentListItem>
      </ContentBox>
    </div>

    <ContentBox title="Reservation Summary">
      <ul class="flex flex-col gap-4">
        {#each reservations as reservation}
          <li class=" flex justify-between">
            <span>Table {reservation.table}</span>
            <span class="text-right">{reservation.time}</span>
          </li>
        {/each}
        {#if reservations.length}
          <li
            class="flex justify-between border-t border-t-black-transparent pt-4 text-green"
          >
            <span>Tables</span>
            <span class="text-right">
              {(reservations.length
                ? reservations.length === 1
                  ? 10
                  : 10 + 15 * reservations.length
                : 0
              )
                .toFixed(2)
                .padStart(5, '0')} €
            </span>
          </li>
        {/if}
        {#each order as item}
          <li class="flex justify-between gap-x-3">
            <div class="flex flex-col">
              <span>
                {item.name}
                {#if item.count && item.count > 1}
                  <span class="text-green">x{item.count}</span>
                {/if}
              </span>
              <span>{item.info}</span>
            </div>

            <span class="text-right">{item.price}€</span>
          </li>
        {/each}
        <li
          class="flex justify-between border-t border-black-transparent pt-6 text-green"
        >
          <span>Total</span>
          <span class="text-right">
            {(
              order.reduce((a, b) => a + b.price * (b.count ? b.count : 1), 0) +
              reservationsCost
            ).toFixed(2)}€
          </span>
        </li>
      </ul>
    </ContentBox>
  </section>
</main>
