/*
  Copyright (C) 2012 bbnc

 This file is part of pong.

 pong is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 pong is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
    
 You should have received a copy of the GNU General Public License
 along with pong.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "game.h"
#include "project.h"

int main(int argc, char **argv){
  awake_the_weaver(); // Initializing Weaver API

  hide_cursor();
  initialize_background();
  draw_surface(background, window, 0, 100);
  draw_rectangle(0, 100, window_width-1, window_height - 101, YELLOW);
  
  initialize_paddles();
  draw_surface(paddle1 -> image, window, paddle1 -> x, paddle1 -> y);
  draw_surface(paddle2 -> image, window, paddle2 -> x, paddle2 -> y);

  initialize_scores();
  draw_scores();

  initialize_ball();
  draw_surface(ball -> image, window, ball -> x, ball -> y);

  play_music("einklang.ogg");

  // Main loop
  for(;;){
    get_input();
	if(keyboard[ESC] || score1 == 12 || score2 == 12){
      break;
    }
	if(keyboard[W])
		move_paddle(paddle1, UP);
	else if(keyboard[S])
		move_paddle(paddle1, DOWN);
	if(keyboard[I])
		move_paddle(paddle2, UP);
	else if(keyboard[K])
		move_paddle(paddle2, DOWN);

	move_ball();

    weaver_rest(10000000);
  }
  may_the_weaver_sleep();
  return 0;
}
