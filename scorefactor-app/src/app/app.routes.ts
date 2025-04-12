import { RouterModule, Routes } from '@angular/router';
import { HomeComponent } from './pages/home/home.component';
import { LeaderboardComponent } from './pages/leaderboard/leaderboard.component';
import { NgModule } from '@angular/core';

export const routes: Routes = [
  { path: '', component: HomeComponent },
  { path: 'leaderboard', component: LeaderboardComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}

