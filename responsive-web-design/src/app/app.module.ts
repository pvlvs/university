import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { HeaderComponent } from './areas/header/header.component';
import { FooterComponent } from './areas/footer/footer.component';
import { SliderComponent } from './areas/slider/slider.component';
import { LandingPageComponent } from './areas/landing-page/landing-page.component';
import { SearchComponent } from './areas/landing-page/search/search.component';
import { ReactiveFormsModule } from '@angular/forms';
import { ImageTextComponent } from './areas/image-text/image-text.component';
import { ProductPresentationComponent } from './areas/product-presentation/product-presentation.component';
import { CounterComponent } from './areas/counter/counter.component';
import { ProgressComponent } from './areas/progress/progress.component';
import { StatsComponent } from './areas/stats/stats.component';
import { MenuComponent } from './areas/header/menu/menu.component';
import { ListComponent } from './areas/header/menu/list/list.component';
import { SignInComponent } from './areas/header/menu/sign-in/sign-in.component';
import { CreateAccountComponent } from './areas/header/menu/create-account/create-account.component';
import { HeadlineComponent } from './areas/header/menu/headline/headline.component';
import { GoogleBtnComponent } from './components/google-btn/google-btn.component';
import { FacebookBtnComponent } from './components/facebook-btn/facebook-btn.component';
import { InputComponent } from './components/input/input.component';
import { PasswordComponent } from './areas/header/menu/password/password.component';

@NgModule({
  declarations: [
    AppComponent,
    HeaderComponent,
    FooterComponent,
    SliderComponent,
    LandingPageComponent,
    SearchComponent,
    ImageTextComponent,
    ProductPresentationComponent,
    CounterComponent,
    ProgressComponent,
    StatsComponent,
    MenuComponent,
    ListComponent,
    SignInComponent,
    CreateAccountComponent,
    HeadlineComponent,
    GoogleBtnComponent,
    FacebookBtnComponent,
    InputComponent,
    PasswordComponent,
  ],
  imports: [BrowserModule, ReactiveFormsModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
