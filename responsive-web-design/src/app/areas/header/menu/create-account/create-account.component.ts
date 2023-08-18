import { Component, EventEmitter, OnInit, Output } from '@angular/core';
import {
  FormGroup,
  Validators,
  FormBuilder,
  FormControl,
  ValidatorFn,
  AbstractControl,
  ValidationErrors,
} from '@angular/forms';

@Component({
  selector: 'app-create-account',
  templateUrl: './create-account.component.html',
  styleUrls: ['./create-account.component.scss'],
})
export class CreateAccountComponent implements OnInit {
  @Output() changeComponent = new EventEmitter<string>();

  public form: FormGroup = this.fb.group({
    name: ['', Validators.required],
    mail: ['', Validators.required],
    password: ['', [Validators.required, Validators.min(8)]],
    confirmPassword: [
      '',
      [Validators.required, Validators.min(8), this.compareControl()],
    ],
  });

  public checked = false;

  constructor(private readonly fb: FormBuilder) {}

  ngOnInit(): void {}

  public get nameControl(): FormControl {
    return this.form.get('name') as FormControl;
  }

  public get mailControl(): FormControl {
    return this.form.get('mail') as FormControl;
  }

  public get pwControl(): FormControl {
    return this.form.get('password') as FormControl;
  }

  public get pwConfirmControl(): FormControl {
    return this.form.get('confirmPassword') as FormControl;
  }

  private compareControl(): ValidatorFn {
    return (control: AbstractControl): ValidationErrors | null => {
      const value = control.value;

      if (!value) {
        return null;
      }

      return this.pwControl.value != this.pwConfirmControl.value
        ? { equals: true }
        : null;
    };
  }
}
