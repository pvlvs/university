<script lang="ts">
  export let href: string;
  export let bgColor: string;
</script>

<a
  {href}
  class={`box-border min-w-[12rem] rounded px-8 py-2 text-center text-base text-white md:py-4 md:text-2xl ${bgColor}`}
>
  <slot />
</a>
