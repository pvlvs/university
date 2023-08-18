import {
  AfterViewInit,
  Component,
  ElementRef,
  OnInit,
  ViewChild,
} from '@angular/core';
import { Subject, timer } from 'rxjs';

interface Counter {
  value: number;
  label: string;
  target: number;
}

@Component({
  selector: 'app-counter',
  templateUrl: './counter.component.html',
  styleUrls: ['./counter.component.scss'],
})
export class CounterComponent implements OnInit, AfterViewInit {
  @ViewChild('container') container?: ElementRef;

  private observer?: IntersectionObserver;

  public counterArr: Counter[] = [
    { value: 0, label: 'TOTAL LAUNCHES', target: 139 },
    { value: 0, label: 'TOTAL LANDINGS', target: 117 },
    { value: 0, label: 'TOTAL DELIVERIES', target: 109 },
  ];

  constructor() {}

  ngOnInit(): void {
    this.createObserver();
  }

  ngAfterViewInit() {
    if (this.container && this.observer) {
      this.observer.observe(this.container.nativeElement);
    }
  }

  ngOnDestroy() {
    if (this.observer) {
      this.observer.disconnect();
      this.observer = undefined;
    }
  }

  private createObserver() {
    const options = {
      rootMargin: '0px',
      threshold: 0,
    };

    this.observer = new IntersectionObserver((entries, observer) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          this.count();
        }
      });
    }, options);
  }

  public count(): void {
    let done = 0;
    this.counterArr.forEach((counter) => {
      counter.value = 0;
    });

    this.counterArr.forEach((counter) => {
      const updateCounter = () => {
        const increment = counter.target / 100;

        if (counter.value < counter.target - 1) {
          counter.value = Math.ceil(counter.value + increment);

          timer(counter.value < counter.target * 0.9 ? 10 : 45).subscribe(
            () => {
              updateCounter();
            }
          );
        } else {
          done++;

          if (done === 3) {
            this.counterArr.forEach((counter) => {
              counter.value = counter.target;
            });
          }
        }
      };

      updateCounter();
    });
  }
}
