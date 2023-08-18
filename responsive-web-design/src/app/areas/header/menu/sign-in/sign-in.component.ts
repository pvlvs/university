import { Component, EventEmitter, OnInit, Output } from '@angular/core';
import {
  FormBuilder,
  FormControl,
  FormGroup,
  Validators,
} from '@angular/forms';

@Component({
  selector: 'app-sign-in',
  templateUrl: './sign-in.component.html',
  styleUrls: ['./sign-in.component.scss'],
})
export class SignInComponent implements OnInit {
  @Output() changeComponent = new EventEmitter<string>();

  public form: FormGroup = this.fb.group({
    mail: ['', Validators.required],
    password: ['', Validators.required],
  });

  constructor(private readonly fb: FormBuilder) {}

  ngOnInit(): void {}

  public get mailControl(): FormControl {
    return this.form.get('mail') as FormControl;
  }

  public get pwControl(): FormControl {
    return this.form.get('password') as FormControl;
  }
}
