import {
  Component,
  ElementRef,
  EventEmitter,
  OnDestroy,
  OnInit,
  Output,
  ViewChild,
} from '@angular/core';
import { FormControl } from '@angular/forms';
import { Subject, takeUntil, timer } from 'rxjs';

@Component({
  selector: 'app-search',
  templateUrl: './search.component.html',
  styleUrls: ['./search.component.scss'],
})
export class SearchComponent implements OnInit, OnDestroy {
  @ViewChild('input') input?: ElementRef;

  public control: FormControl = new FormControl<string>('');
  public isSearching = false;
  public isTyping = false;

  private destroy = new Subject<void>();

  constructor() {}

  ngOnInit(): void {
    this.control.markAsTouched();

    this.control.valueChanges.pipe(takeUntil(this.destroy)).subscribe((v) => {
      if (!this.isTyping) {
        this.isTyping = true;
      }

      if (!v) {
        this.isTyping = false;
      } else {
        this.isSearching = true;
      }
    });
  }

  ngOnDestroy(): void {
    this.destroy.next();
    this.destroy.complete();
  }

  public onFocus(): void {
    this.isSearching = true;
  }

  public onBlur(): void {
    timer(100).subscribe(() => {
      this.isSearching = false;
    });
  }

  public clear(): void {
    this.control.setValue('');

    if (this.input) {
      this.input.nativeElement.focus();
    }

    this.isSearching = true;
    this.isTyping = false;
  }
}
