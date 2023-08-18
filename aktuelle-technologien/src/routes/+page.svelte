<script>
  import LinkButton from '$lib/LinkButton.svelte';
  import Layout from './+layout.svelte';
  import smoothie from '$lib/assets/smoothie.jpg';
</script>

<Layout>
  <header class="text-center md:text-start">
    <a href="/" class="text-3xl font-bold md:text-5xl">
      <span class="text-green">Gastro</span><span class="text-red">Gnome</span>
    </a>
  </header>

  <main
    class="absolute left-1/2 top-[calc(50%+4rem)] flex h-fit w-full -translate-x-1/2 -translate-y-1/2 items-center gap-x-16 p-16 pt-0 xl:-mt-12 xl:px-32"
  >
    <section class="flex flex-col gap-y-8">
      <h1 class="text-6xl leading-tight xl:text-6xl 2xl:text-8xl">
        Focus on what's important. <span class="border-b-8 border-red"
          >Food</span
        >.
      </h1>

      <p
        class="pb-4 text-base leading-normal opacity-70 md:text-2xl xl:pr-16 xl:leading-10"
      >
        Whether you're craving a hearty meal or planning a special occasion, we
        make it easy to enjoy delicious food and great company. Order now or
        reserve your spot today!
      </p>

      <div class="flex flex-wrap justify-center gap-x-8 gap-y-4 md:gap-x-16">
        <LinkButton href="/menu" bgColor="bg-red">Menu</LinkButton>
        <LinkButton href="/tables" bgColor="bg-green"
          >Table Selection</LinkButton
        >
      </div>
    </section>

    <section class="hidden lg:block">
      <img
        src={smoothie}
        alt="A green smoothie"
        class="w-auto rounded-3xl shadow-xl"
      />
    </section>
  </main>
</Layout>
