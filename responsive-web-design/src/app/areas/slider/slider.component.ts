import {
  AfterViewInit,
  ChangeDetectorRef,
  Component,
  ElementRef,
  HostListener,
  OnInit,
  ViewChild,
} from '@angular/core';
import { timer } from 'rxjs';
export interface Media {
  media: string;
  title: string;
}

@Component({
  selector: 'app-slider',
  templateUrl: './slider.component.html',
  styleUrls: ['./slider.component.scss'],
})
export class SliderComponent implements OnInit, AfterViewInit {
  @ViewChild('section') section?: ElementRef;

  public mediaArr: Media[] = [
    {
      media: 'chef',
      title:
        'Made by real people, with years of experience, to guarantee the best taste.',
    },
    { media: 'spices', title: 'Using the freshest and purest spices' },
    {
      media: 'bread',
      title: 'Not being limited by your culinary preferences.',
    },
    {
      media: 'burger',
      title: 'Not only a great taste, but also a great look.',
    },
    {
      media: 'drink',
      title: "We don't always bring the heat. But we always keep our cool.",
    },
    {
      media: 'pasta',
      title:
        'Bringing the kitchen of all the cultures around the world to you.',
    },
    {
      media: 'potato',
      title: "You don't have to order a full meal. We got you anyway.",
    },
  ];

  public index: number = 1;
  public length: number = this.mediaArr.length;

  public translateVal: string = '';
  public isTranslating = false;

  constructor(private readonly cd: ChangeDetectorRef) {}

  ngOnInit(): void {}

  ngAfterViewInit(): void {
    this.mediaArr.push(this.mediaArr[0]);
    this.mediaArr.push(this.mediaArr[1]);

    this.setTranslate();
    this.cd.detectChanges();
  }

  public slide(next: boolean): void {
    if (!this.isTranslating) {
      if (next) {
        this.index++;
      } else {
        this.index--;
      }

      this.setTranslate();
      this.isTranslating = true;

      timer(1500).subscribe(() => {
        this.isTranslating = false;

        if (this.index === this.length && !next) {
          this.index = 0;
        } else if (this.index === 0) {
          this.index = this.length;
        } else if (
          this.mediaArr.length > this.length + 1 &&
          this.index === this.length + 1 &&
          next
        ) {
          this.index = 1;
        }

        this.setTranslate();
      });
    }
  }

  public setTranslate(): void {
    if (this.section) {
      const width =
        this.section.nativeElement.getBoundingClientRect().width * this.index;

      this.translateVal = `translate3d(-${width}px, 0px, 0px)`;
    }
  }

  @HostListener('window:resize')
  onResize() {
    if (this.section) {
      this.isTranslating = false;
      this.setTranslate();
    }
  }
}
