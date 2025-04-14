import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';

interface LeaderboardEntry {
  username: string;
  score: number;
}

@Component({
  selector: 'app-leaderboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './leaderboard.component.html',
  styleUrls: ['./leaderboard.component.css']
})
export class LeaderboardComponent implements OnInit {
  leaderboard: LeaderboardEntry[] = [];

  ngOnInit(): void {
    this.generateDummyData();
  }

  generateDummyData() {
    const usernames = ['Karolis', 'Zoe', 'Max', 'Liam', 'Ava', 'Noah', 'Mia', 'Lucas', 'Olivia', 'Jack'];

    this.leaderboard = usernames.map(username => ({
      username,
      score: Math.floor(Math.random() * 100)
    }))
    .sort((a, b) => b.score - a.score); // Sort high to low
  }
}
