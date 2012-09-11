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
#include "score.h"

// This initialies our score and gets the image with the numbers that we'll
// draw in the screen
void initialize_scores(void){
	score1 = score2 = 0;
	numbers = new_image("numbers.png");
}

// This draws the 2 scores in the screen. As our maximum score is "12", we
// don't treat cases when the sore have more than 2 digits.
void draw_scores(void){
	int digit;
	// All the numbers are 46x46 pixels
	surface *buffer = new_surface(46, 46);
	// Drawing the Player 1 score...
	// The first digit:
	fill_surface(buffer, BLACK);
	digit = score1 / 10;
	blit_surface(numbers, buffer,
			46*digit, 0, 46, 46,
			0, 0);
	draw_surface(buffer, window, 27, 27);
	// The second digit:
	fill_surface(buffer, BLACK);
	digit = score1 % 10;
	blit_surface(numbers, buffer,
			46*digit, 0, 46, 46,
			0, 0);
	draw_surface(buffer, window, 27+35, 27);
	// Drawing the Player 2 score...
	// The first digit:
	fill_surface(buffer, BLACK);
	digit = score2 / 10;
	blit_surface(numbers, buffer,
			46*digit, 0, 46, 46,
			0, 0);
	draw_surface(buffer, window, window_width - 27 - 35 - 46, 27);
	// The second digit:
	fill_surface(buffer, BLACK);
	digit = score2 % 10;
	blit_surface(numbers, buffer,
			46*digit, 0, 46, 46,
			0, 0);
	draw_surface(buffer, window, window_width - 27 - 46, 27);
	// Done. Destroying the buffer...
	destroy_surface(buffer);
}
