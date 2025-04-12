import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {
  username = 'Karolis'; // Change this later to be dynamic
  score = 0;
  currentTime: string = '';

  ngOnInit(): void {
    this.updateTime();
    setInterval(() => this.updateTime(), 1000);

    // Simulate score updates (replace with socket later)
    setInterval(() => {
      this.score += Math.floor(Math.random() * 5); // random test logic
    }, 5000);
  }

  updateTime(): void {
    this.currentTime = new Date().toLocaleString();
  }
}
