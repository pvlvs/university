import { Component, EventEmitter, OnInit, Output } from '@angular/core';

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements OnInit {
  @Output() close = new EventEmitter<void>();
  @Output() changeComponent = new EventEmitter<string>();

  constructor() {}

  ngOnInit(): void {}
}
