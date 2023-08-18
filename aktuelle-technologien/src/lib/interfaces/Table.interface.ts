export interface Table {
  id: number;
  reservations: string[];
  size: number;
  round?: boolean;
}

export interface Reservation {
  table: number;
  time: string;
}
