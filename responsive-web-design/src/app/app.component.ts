import { Component } from '@angular/core';
import { timer } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent {
  public timer: number = 2500;

  public blockPage = false;

  public countDown(): void {
    timer(100).subscribe(() => {
      this.timer -= 100;

      if (this.timer) {
        this.countDown();
      } else {
        this.timer = 2500;
      }
    });
  }

  public triggerWarning(): void {
    if (this.timer === 2500) {
      this.countDown();
    } else {
      this.timer = 2500;
    }
  }
}
