import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';

@Component({
  selector: 'app-headline',
  templateUrl: './headline.component.html',
  styleUrls: ['./headline.component.scss']
})
export class HeadlineComponent implements OnInit {
  @Input() title?: string;
  @Output() changeComponent = new EventEmitter<void>();

  constructor() { }

  ngOnInit(): void {
  }

}
