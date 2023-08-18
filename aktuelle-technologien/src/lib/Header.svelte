<script lang="ts">
  import { page } from '$app/stores';
  import { onMount } from 'svelte';

  interface MenuItem {
    name: string;
    href: string;
  }

  export let isCheckout = false;

  const menuItems: MenuItem[] = [
    { name: 'Menu', href: '/menu' },
    { name: 'Table Selection', href: '/tables' }
  ];

  const mobileMenuItems: MenuItem[] = [
    { name: 'Home', href: '/' },
    ...menuItems
  ];

  let button: HTMLButtonElement;
  let close: HTMLButtonElement;
  let navCon: HTMLElement;
  let nav: HTMLElement;

  onMount(() => {
    function toggleClasses(): void {
      navCon?.classList.toggle('bg-black-transparent');
      navCon?.classList.toggle('bg-transparent');
      nav.classList.toggle('top-0');
      nav.classList.toggle('-top-[157px]');
      navCon?.classList.toggle('pointer-events-none');
    }

    button?.addEventListener('click', () => {
      if (!nav.classList.contains('animate-slide-out')) {
        nav.classList.add('animate-slide-out');
      }

      toggleClasses();
    });

    close?.addEventListener('click', () => {
      toggleClasses();
    });

    navCon?.addEventListener('click', () => {
      if (navCon.classList.contains('bg-black-transparent')) {
        toggleClasses();
      }
    });

    nav?.addEventListener('click', (e) => {
      e.stopPropagation();
    });
  });
</script>

<header class="flex justify-between text-2xl">
  <h1 class="font-bold">
    <a href="/"
      ><span class="text-green">Gastro</span><span class="text-red">Gnome</span
      ></a
    >
  </h1>

  {#if !isCheckout}
    <nav class="hidden gap-x-8 md:flex xl:gap-x-32">
      {#each menuItems as item}
        <a
          href={item.href}
          class="border-b-4 border-transparent {$page.url.pathname === item.href
            ? ' border-b-red'
            : ''}">{item.name}</a
        >
      {/each}
    </nav>

    <div class="w-[150px]" />

    <button bind:this={button} class="self-start md:hidden">
      <svg
        xmlns="http://www.w3.org/2000/svg"
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
        <path d="M4 6l16 0" />
        <path d="M4 12l16 0" />
        <path d="M4 18l16 0" />
      </svg>
    </button>

    <section
      bind:this={navCon}
      class="pointer-events-none absolute inset-0 z-10 bg-transparent transition-colors duration-500 md:hidden"
    >
      <nav
        bind:this={nav}
        class="absolute -top-[157px] right-4 flex flex-col gap-y-2 rounded-bl-md rounded-br-md bg-white p-4 pt-8 transition-[top] duration-500 ease-out"
      >
        <button bind:this={close} class="self-end text-red">
          <svg
            xmlns="http://www.w3.org/2000/svg"
            class="icon icon-tabler icon-tabler-x"
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

        {#each mobileMenuItems as item}
          <a href={item.href} class="text-base">{item.name}</a>
        {/each}
      </nav>
    </section>
  {/if}
</header>
