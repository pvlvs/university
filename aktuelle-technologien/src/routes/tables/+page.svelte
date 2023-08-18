<script lang="ts">
  import { goto } from '$app/navigation';
  import Header from '$lib/Header.svelte';
  import type { Reservation, Table } from '$lib/interfaces/Table.interface';
  import { showTimeoutDialog, tablesStore } from '../../store';
  import Legend from './Legend.svelte';
  import tables from './tables.json';
  import TimeoutDialog from './TimeoutDialog.svelte';

  let tableArr: Table[] = JSON.parse(JSON.stringify(tables));
  let reservations: Reservation[] = [];
  let preview: Table | undefined;
  let startInput: HTMLInputElement;
  let endInput: HTMLInputElement;
  let countdown = setInterval(countdownHandler, 1000);
  let reservationEdit: { id: number; target: string } | undefined;

  $: remainingTime = 300;
  $: tableArr, reservations, preview;
  $: disabled = !reservations.length;

  showTimeoutDialog.subscribe((value) => {
    if (!value) {
      resetCountdown();

      reservations = [];
      preview = undefined;

      tablesStore.set(reservations);
    }
  });

  function countdownHandler(): void {
    remainingTime -= 1;

    if (remainingTime === 0) {
      clearInterval(countdown);
      showTimeoutDialog.set(true);
    }
  }

  function resetCountdown(): void {
    clearInterval(countdown);
    remainingTime = 300;
    countdown = setInterval(countdownHandler, 1000);
  }

  function hasReservation(table: Table | undefined): boolean {
    let returnVal = false;

    if (table) {
      const reservation = reservations.find((r) => r.table === table.id);

      if (reservation) {
        table.reservations.some((r) => {
          if (r === reservation.time) {
            returnVal = true;
          }
        });
      }
    }

    return returnVal;
  }

  function previewTable(table: Table): void {
    if (reservationEdit) {
      preview?.reservations.splice(
        reservationEdit.id,
        0,
        reservationEdit.target
      );

      reservationEdit = undefined;
      preview = preview;
    }

    if (preview?.id === table.id) {
      preview = undefined;
    } else {
      preview = table;
    }

    if (startInput) {
      startInput.value = '';
    }
    if (endInput) {
      endInput.value = '';
    }
  }

  function addReservation(table: Table): void {
    if (startInput.value && endInput.value) {
      resetCountdown();

      const reservationTime = startInput.value + ' - ' + endInput.value;

      reservations.push({
        table: table.id,
        time: reservationTime
      });

      tableArr[tableArr.findIndex((t) => t.id === table.id)].reservations.push(
        reservationTime
      );

      reservations = reservations;
      tableArr = tableArr;
      preview = preview;
      reservationEdit = undefined;

      startInput.value = '';
      endInput.value = '';

      tablesStore.set(reservations);
    }
  }

  function editReservation(reservation: Reservation): void {
    preview = tableArr.find((t) => t.id === reservation.table);

    const targetId = preview?.reservations.findIndex(
      (r) => r === reservation.time
    );
    const target = preview?.reservations.splice(
      preview?.reservations.findIndex((r) => r === reservation.time),
      1
    )[0];

    reservationEdit = { id: targetId!, target: target! };

    startInput.value = reservation.time.split(' - ')[0];
    endInput.value = reservation.time.split(' - ')[1];

    preview = preview;
  }

  function deleteReservation(reservation: Reservation): void {
    const id = tableArr.findIndex((t) => t.id === reservation.table);

    tableArr[id].reservations.splice(
      tableArr[id].reservations.findIndex((r) => r === reservation.time),
      1
    );

    reservations.splice(
      reservations.findIndex((r) => r === reservation),
      1
    );

    tableArr = tableArr;
    preview = preview;
    reservations = reservations;
  }
</script>

<Header />

<main class="mt-20 grid grid-cols-1 gap-x-24 gap-y-16 lg:grid-cols-[15fr,8fr]">
  <section>
    <div class="relative grid h-fit grid-cols-10 gap-4 border border-black p-6">
      {#each tableArr as table}
        <button
          on:click={() => previewTable(table)}
          class="relative w-full
				{table.round ? 'rounded-full' : 'rounded'}
				{table.id !== preview?.id ? 'opacity-25' : ''}
				{table.size === 12 ? 'col-span-2 row-span-2' : ''}
        {hasReservation(table)
            ? 'bg-green'
            : table.reservations.length
            ? 'bg-red'
            : 'bg-black-transparent'}
				{table.size === 8
            ? table !== tableArr.find((t) => t.size === 8)
              ? 'col-span-3'
              : 'row-span-3'
            : 'pb-[100%]'}"
        >
          <span
            class="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2 text-white"
            >{hasReservation(table) ? table.id : ''}</span
          >
        </button>
      {/each}

      <span class="absolute -left-6 -top-6 h-12 w-12 bg-white" />
      <span class="absolute -right-6 -top-6 h-12 w-12 bg-white" />
      <span class="absolute -bottom-6 -right-6 h-12 w-12 bg-white" />
      <span class="absolute -bottom-6 -left-6 h-12 w-12 bg-white" />
    </div>
  </section>
  <Legend />

  <section
    class="relative flex min-h-[300px] flex-col gap-y-8 border-black sm:flex-row lg:flex-col lg:border lg:p-6"
  >
    <div
      class="flex flex-1 flex-col gap-y-8 border border-b-0 p-6 sm:border-b sm:border-r-0 lg:border-0 lg:py-0"
    >
      <div class="flex justify-between">
        <span>Remaining Time:</span>
        <span class="text-end"
          >{Math.floor(remainingTime / 60).toFixed(0) +
            ':' +
            (remainingTime % 60).toFixed(0).padStart(2, '0')}</span
        >
      </div>

      <div>
        <span
          class="block w-full rounded-t py-3 text-center text-white shadow-md {hasReservation(
            preview
          )
            ? 'bg-green'
            : preview
            ? 'bg-red'
            : 'bg-black-transparent'}"
        >
          {preview ? 'Table ' + preview.id : 'No Table Selected'}
        </span>
        {#if preview}
          <ul class="rounded rounded-t-none border border-t-0 px-6 pb-6 pt-4">
            <li class="mb-4">
              {preview.reservations.length ? 'Reservations' : 'No reservations'}
            </li>
            {#each preview.reservations as reservation}
              <li
                class="mb-2 {reservations.find(
                  (r) => r.table === preview?.id && r.time === reservation
                )
                  ? 'text-green'
                  : ''}"
              >
                {reservation}
              </li>
            {/each}

            <li>
              <input type="time" bind:this={startInput} class="w-24 border-b" />
              -
              <input type="time" bind:this={endInput} class="w-24 border-b" />
              <button
                on:click={() => preview && addReservation(preview)}
                class="ml-2 border-b">+Add</button
              >
            </li>
          </ul>
        {/if}
      </div>
    </div>

    <div
      class="relative flex h-[1px] w-full bg-black sm:h-full sm:w-[1px] sm:flex-col lg:h-0 lg:w-0"
    >
      <span
        class="absolute left-0 top-1/2 h-6 w-12 -translate-x-1/2 -translate-y-1/2 bg-white sm:left-1/2 sm:top-0 sm:-translate-x-1/2"
      />
      <span
        class="absolute bottom-1/2 left-full h-6 w-12 -translate-x-1/2 translate-y-1/2 bg-white sm:bottom-0 sm:left-1/2 sm:-translate-x-1/2"
      />
    </div>

    <div
      class="flex flex-1 flex-col justify-end border border-t-0 p-6 sm:border-l-0 sm:border-t lg:mt-auto lg:border-0"
    >
      <ul class="flex flex-col justify-end gap-y-4">
        {#each reservations as reservations}
          <li class="flex justify-between">
            <span class="text-green">Table {reservations.table}</span>
            <div class="flex gap-x-3">
              <span>{reservations.time}</span>
              <div>
                <button on:click={() => editReservation(reservations)}>
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
                    <path
                      d="M4 20h4l10.5 -10.5a1.5 1.5 0 0 0 -4 -4l-10.5 10.5v4"
                    />
                    <path d="M13.5 6.5l4 4" />
                  </svg>
                </button>
                <button
                  on:click={() => deleteReservation(reservations)}
                  class="text-red"
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
                    <path d="M18 6l-12 12" />
                    <path d="M6 6l12 12" />
                  </svg>
                </button>
              </div>
            </div>
          </li>
        {/each}
      </ul>
      <div class="mt-4 flex items-center justify-between">
        <span
          >Total: {(reservations.length
            ? reservations.length === 1
              ? 10
              : 10 + 15 * reservations.length
            : 0
          )
            .toFixed(2)
            .padStart(5, '0')} €</span
        >
        <button
          {disabled}
          on:click={() => goto('/checkout')}
          class="rounded bg-green px-6 py-2 text-white {disabled &&
            'opacity-50'}">Reserve</button
        >
      </div>
    </div>

    <span class="absolute -left-6 -top-6 h-12 w-12 bg-white" />
    <span class="absolute -right-6 -top-6 h-12 w-12 bg-white" />
    <span class="absolute -bottom-6 -right-6 h-12 w-12 bg-white" />
    <span class="absolute -bottom-6 -left-6 h-12 w-12 bg-white" />
  </section>

  <TimeoutDialog />
</main>
