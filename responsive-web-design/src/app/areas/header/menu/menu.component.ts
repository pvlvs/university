import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';

@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.scss'],
})
export class MenuComponent implements OnInit {
  @Output() close = new EventEmitter<boolean>();

  @Input() activeComponent?: string;
  @Input() isMenu?: boolean;

  constructor() {}

  ngOnInit(): void {}

  public stopPropagation(e: Event): void {
    e.stopPropagation();
  }

  public changeOrCloseComponent(component: string): void {
    const changeForm =
      component === 'create-account'
        ? true
        : component === 'sign-in'
        ? true
        : component === 'password'
        ? true
        : false;

    if (!this.isMenu && !changeForm) {
      this.close.emit(this.isMenu);
    } else {
      this.activeComponent = component;
    }
  }
}
