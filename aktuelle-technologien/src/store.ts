import type { MenuCategory, MenuItem } from '$lib/interfaces/Menu.interface';
import { writable, type Writable } from 'svelte/store';
import menu from './routes/menu/menu.json';
import type { Reservation } from '$lib/interfaces/Table.interface';

export const categoriesStore: Writable<MenuCategory[]> = writable(
  JSON.parse(JSON.stringify(menu))
);

export const orderStore: Writable<MenuItem[]> = writable([]);
export const tablesStore: Writable<Reservation[]> = writable([]);
export const showTimeoutDialog = writable(false);
