/*
  Copyright (C) 2012 bbnc

 This file is part of Vector.

 Vector is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Vector is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
    
 You should have received a copy of the GNU General Public License
 along with Vector.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "weaver/weaver.h"
#include "game.h"

int main(int argc, char **argv){
  awake_the_weaver(); // Initializing Weaver API
  
  camera *cam = new_camera(0.0, 0.0, 100.0, 100.0);
  circle *star   = new_circle(50.0, 50.0, 20.0);
  circle *planet = new_circle(90.0, 90.0,  5.0);
  rectangle *trash = new_rectangle(75.0, 50.0, 1.25, 2.5);
  rectangle *ufo   = new_rectangle(25.0, 50.0, 1.5,  1.5);
  film_fullcircle(cam, star, YELLOW);
  film_fullcircle(cam, planet, BLUE);
  film_rectangle(cam, trash, GREEN);
  film_fullrectangle(cam, ufo, WHITE);

  int camera_moved = 0;

  // Main loop
  for(;;){
    get_input();
    if(keyboard[ESC]){
      break;
    }
	if(keyboard[UP] || keyboard[DOWN] || keyboard[LEFT] || keyboard[RIGHT] ||
			keyboard[MINUS] || keyboard[PLUS] || keyboard[ENTER]){
		film_fullcircle(cam, star, BLACK);
		film_fullcircle(cam, planet, BLACK);
		film_rectangle(cam, trash, BLACK);
		film_fullrectangle(cam, ufo, BLACK);
		camera_moved = 1;
	}
	if(keyboard[UP])
		cam -> y -= 1.0;
	if(keyboard[DOWN])
		cam -> y += 1.0;
	if(keyboard[LEFT])
		cam -> x -= 1.0;
	if(keyboard[RIGHT])
		cam -> x += 1.0;
	if(keyboard[PLUS])
		zoom_camera(cam, 1.01);
	if(keyboard[MINUS])
		zoom_camera(cam, 0.99);
	if(keyboard[ENTER])
		center_camera(cam, 50.0, 50.0);

	film_fullcircle(cam, planet, BLACK);
	rotate_circle(planet, 50.0, 50.0, 0.01);
	film_fullcircle(cam, planet, BLUE);

	if(camera_moved){
		film_fullcircle(cam, star, YELLOW);
		film_rectangle(cam, trash, GREEN);
		film_fullrectangle(cam, ufo, WHITE);
		camera_moved = 0;
	}

    weaver_rest(10000000);
  }
  may_the_weaver_sleep();
  return 0;
}
