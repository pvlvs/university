import { Component, OnInit } from '@angular/core';

interface Sushi {
  type: string;
  paragraph: string;
  weight: number;
  calories: number;
  imageSrc: string;
  alt: string;
}

@Component({
  selector: 'app-product-presentation',
  templateUrl: './product-presentation.component.html',
  styleUrls: ['./product-presentation.component.scss'],
})
export class ProductPresentationComponent implements OnInit {
  public sushiArr: Sushi[] = [
    {
      type: 'PLATE',
      paragraph:
        'Not limiting yourself to a single type of sushi, guaranties the best time for your taste buds. And having a whole plate, lets you share some with your friends and improving the good time you are having.',
      weight: 1344,
      calories: 5432,
      imageSrc: './assets/media/product/sushi_plate.png',
      alt: 'A plate filled with sushi',
    },
    {
      type: 'SINGLE',
      paragraph:
        'One of the most iconic dishes from asia. Combining fish with healthy and diverse vegetables from the plant world. By conveniently coming in a bite-sized form, you can always put some in the fridge for later or have a little snack in between.',
      weight: 48,
      calories: 198,
      imageSrc: './assets/media/product/sushi.png',
      alt: 'A piece of sushi',
    },
  ];

  public activeSushi: Sushi = this.sushiArr[0];

  constructor() {}

  ngOnInit(): void {}

  public setSushi(index: number): void {
    this.activeSushi = this.sushiArr[index];
  }
}
