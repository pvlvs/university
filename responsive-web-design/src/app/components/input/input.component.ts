import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { FormControl } from '@angular/forms';
import { Subject, takeUntil } from 'rxjs';

@Component({
  selector: 'app-input',
  templateUrl: './input.component.html',
  styleUrls: ['./input.component.scss'],
})
export class InputComponent implements OnInit, OnDestroy {
  @Input() control: FormControl = new FormControl<string>('');
  @Input() type?: string;
  @Input() label?: string;
  @Input() placeholder?: string;
  @Input() error: string = '';
  @Input() isPassword = false;
  @Input() checksPasswordStrength = false;

  public showError = false;
  public showRequirements = false;
  public showStrength = false;
  public pwStrength: number = 0;
  public strength: string = 'Too weak';

  public pwRequirements: string =
    'Your password should be at least 8 characters long, contain both lower and upper-case letters, and include either a number or a symbol.';

  public displayedError = '';
  public matchError: string =
    "The passwords you entered don't match. Please try again.";

  private destroy = new Subject<void>();

  constructor() {}

  ngOnInit(): void {
    this.control.valueChanges
      .pipe(takeUntil(this.destroy))
      .subscribe((v: string) => {
        if (v) {
          if (this.checksPasswordStrength) {
            this.getStrength(v);
            this.showStrength = true;
          } else {
            this.showStrength = false;
          }
        } else {
          this.showRequirements = false;
        }

        if (!v) {
          this.showError = true;
        }
      });
  }

  ngOnDestroy(): void {
    this.destroy.next();
    this.destroy.complete();
  }

  public showPassword(): void {
    this.type = this.type === 'text' ? 'password' : 'text';
  }

  public getStrength(v: string): void {
    this.pwStrength = 0;

    // if v includes numbers
    if (/\d/.test(v)) {
      this.pwStrength++;
    }

    // if v includes special characters
    if (/[ `!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?~]/.test(v)) {
      this.pwStrength++;
    }

    // if v includes lower-case letter
    if (/[a-z]/.test(v)) {
      this.pwStrength++;
    }

    // if v includes upper-case letter
    if (/[A-Z]/.test(v)) {
      this.pwStrength++;
    }

    // if v has at least 8 characters
    if (v.length >= 8) {
      this.pwStrength++;

      if (v.length >= 10) {
        this.pwStrength++;
      }
    }

    if (this.pwStrength < 4) {
      this.strength = 'Too Weak';
    } else if (this.pwStrength === 4) {
      this.strength = 'Medium';
    } else {
      this.strength = 'Strong';
    }
  }

  public validate(v: string): void {
    if (
      this.checksPasswordStrength &&
      v &&
      (v.length < 8 || this.pwStrength < 4)
    ) {
      this.showRequirements = true;
    } else {
      this.showRequirements = false;
    }

    if (this.control.dirty || this.control.errors?.['equals']) {
      this.showError = true;
    }

    if (this.control.errors?.['equals']) {
      this.displayedError = this.matchError;
    } else {
      this.displayedError = this.error;
    }

    if (this.control.valid) {
      this.showError = false;
    }
  }
}
