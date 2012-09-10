/*
  Copyright (C) 2012 bbnc

 This file is part of ball.

 ball is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 ball is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
    
 You should have received a copy of the GNU General Public License
 along with ball.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "weaver/weaver.h"
#include "game.h"


int main(int argc, char **argv){

  awake_the_weaver(); // Initializing Weaver API

  fill_screen(SCREEN_COLOR);

  // define the parametres
  circle ** many_circles;
  float ball_x, ball_y, radius;
  float *dx, *dy;
  int c_id;
  int num_circles = CIRCLE_NUMBER;
  if(argc > 1)
	  sscanf(argv[1], "%d", &num_circles);

  // alloc the memory
  many_circles = (circle *) malloc(num_circles* sizeof(circle*));
  dx = (float*)malloc(num_circles* sizeof(float));
  dy = (float*)malloc(num_circles* sizeof(float));

  // initialize the values
  for(c_id = 0; c_id < num_circles; c_id ++)
  {
	  radius = 50 + rand() % 50;
	  ball_x = window_width / 2;
	  ball_y = window_height / 2;
	  many_circles[c_id] = new_circle(ball_x, ball_y, radius);
	  unsigned int c_color = rand() % 3;
	  draw_circle(ball_x, ball_y, radius, c_color == 0?RED:c_color==1?GREEN:BLUE);
	  dx[c_id] = (rand() % 200 - 100) / 80.f;
	  dy[c_id] = (rand() % 200 - 100) / 80.f;
  }

  // Main loop
  for(;;){
    get_input();

    if(keyboard[ANY]){
      break;
    }
	
	// update status
	for(c_id = 0; c_id < num_circles; c_id ++)
	{
		draw_circle(many_circles[c_id] -> x, many_circles[c_id] -> y, many_circles[c_id] -> z, SCREEN_COLOR); // to erase

		ball_x = many_circles[c_id] -> x;
		ball_y = many_circles[c_id] -> y;
		radius = many_circles[c_id] -> z;

		ball_x += dx[c_id];
		ball_y += dy[c_id];
		if(ball_y < radius || ball_y > window_height - radius)
			dy[c_id]*= -1;
		if(ball_x < radius || ball_x > window_width - radius)
			dx[c_id]*= -1;

		many_circles[c_id] -> x	= ball_x;
		many_circles[c_id] -> y	= ball_y;
		unsigned int c_color = rand() % 3;
		draw_circle(many_circles[c_id] -> x, many_circles[c_id] -> y, many_circles[c_id] -> z, c_color == 0?RED:c_color==1?GREEN:BLUE); // to erase
	}
	weaver_rest(10000000);
  }

  free(many_circles);
  free(dx);
  free(dy);
  may_the_weaver_sleep();
  return 0;
}
