import { Component, EventEmitter, OnInit, Output } from '@angular/core';

@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.scss'],
})
export class HeaderComponent implements OnInit {
  @Output() blockPage = new EventEmitter<boolean>();

  public showMenu: boolean = false;
  public isMenu: boolean = false;
  public activeComponent = '';

  constructor() {}

  ngOnInit(): void {}

  public triggerMenu(clicked: boolean): void {
    this.showMenu = !this.showMenu;
    this.blockPage.emit(this.showMenu);
    this.activeComponent = this.activeComponent ? '' : 'list';

    this.isMenu = clicked;
  }

  public showCreateAccount(): void {
    this.activeComponent = 'create-account';
    this.showMenu = true;
  }

  public showSignIn(): void {
    this.activeComponent = 'sign-in';
    this.showMenu = true;
  }
}
