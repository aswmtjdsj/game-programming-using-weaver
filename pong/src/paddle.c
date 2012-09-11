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

#include "paddle.h"

// This initializes the paddles. It should be called once in the
// beginning of the game
void initialize_paddles(void){
	// Allocating space
	paddle1 = (struct paddle *) malloc(sizeof(struct paddle));
	paddle2 = (struct paddle *) malloc(sizeof(struct paddle));
	// Loading the images
	paddle1 -> image = new_image("paddle1.png");
	paddle2 -> image = new_image("paddle2.png");
	// Setting the first paddle coordinates
	paddle1 -> x = 1;
	paddle1 -> y = 100 + ((window_height - 100) / 2) - (paddle1 -> image -> height / 2);
	paddle1 -> cy = 0;
	// Setting the second paddle coordinates
	paddle2 -> x = window_width - paddle2 -> image -> width - 1;
	paddle2 -> y = 100 + ((window_height - 100) / 2) - (paddle2 -> image -> height / 2);
	paddle2 -> cy = 0;
	// Setting speed
	paddle1 -> speed = paddle2 -> speed = 200; 
}

// This moves a paddle up or down.
void move_paddle(struct paddle *pad, int direction){
	// We don't move if this would put us outside the game area
	if((direction == UP && pad -> y > 102) || 
			(direction == DOWN && pad -> y + pad -> image -> height < window_height - 1)){  
		// Updating paddle cy value
		int move = (pad -> speed * 100) / fps;
		pad -> cy += ((direction == UP)? (-move):(move));
		// If we moved more than 100 "centipixels", we should erase and draw the paddle again
		if(pad -> cy >= 100 || pad -> cy <= -100){
			// First we erase the given paddle drawing a rectangle with the background
			// in the area where the paddle is standing.
			blit_surface(background, window, 
					pad -> x, pad -> y - 100, pad -> image -> width, pad -> image -> height,
					pad -> x, pad -> y);
			// Next we change the paddle coordinate
			pad -> y += pad -> cy / 100;
			pad -> cy %= 100;
			// And finally we draw the paddle again
			draw_surface(pad -> image, window, pad -> x, pad -> y);
		}
	}
}
