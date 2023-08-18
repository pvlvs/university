export interface MenuCategory {
  title: string;
  items: MenuItem[];
}

export interface MenuItem {
  name: string;
  price: number;
  info: string;
  filter: string[];
  allergens: string[];
  additives: string[];
  count?: number;
}

export interface activeFilter {
  filter: string[];
  allergens: string[];
  additives: string[];
}
