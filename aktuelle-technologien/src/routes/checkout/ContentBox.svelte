<script lang="ts">
  export let title: string;
</script>

<div class="h-fit flex-1 rounded border">
  <span class="block bg-green px-4 py-3 text-center text-white">{title}</span>
  <div class="px-6 py-4">
    <slot />
  </div>
</div>
