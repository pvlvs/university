<script lang="ts">
  import { showTimeoutDialog, tablesStore } from '../../store';

  let dialogContainer: HTMLElement;

  showTimeoutDialog.subscribe((value) => {
    if (value && dialogContainer) {
      dialogContainer.classList.remove('hidden');
    }
  });

  function reloadPage() {
    tablesStore.set([]);

    dialogContainer.classList.add('hidden');
    showTimeoutDialog.set(false);
  }
</script>

<section
  bind:this={dialogContainer}
  class="fixed inset-0 hidden h-screen w-screen overflow-hidden bg-black-transparent"
>
  <div
    class="absolute left-1/2 top-1/2 box-border flex w-4/5 max-w-md -translate-x-1/2 -translate-y-1/2 flex-col gap-y-8 rounded bg-white px-8 py-4 text-center shadow-lg"
  >
    <h2 class="text-xl text-red">Your Session Expired!</h2>
    <p>
      Your Session has expired due to prolonged inactivity. Your current
      reservations have been undone. Please reload the page and place new
      reservations. Your existing orders will remain.
    </p>
    <button class="m-auto rounded bg-green px-4 py-2 text-white">
      <button on:click={reloadPage}>Reload page </button>
    </button>
  </div>
</section>
