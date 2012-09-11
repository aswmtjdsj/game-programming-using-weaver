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
#include "ball.h"

// This function initializes the ball 
void initialize_ball(void){
	ball = (struct ball *) malloc(sizeof(struct ball));
	ball -> image = new_image("ball.png");
	// Putting the ball in the center of screen:
	ball -> x = (window_width - ball -> image -> width) / 2;
	ball -> y = (window_height - ball -> image -> height) / 2 + 50;
	ball -> cx = ball -> cy = ball -> dy = 0;
	// How many pixels per second the ball starts moving
	// It should be able to cross the screen in 10 seconds
	ball -> speed = window_width / 10;
	// The ball can go left or right. It's random:
	ball -> dx = ((rand()%2)?(ball -> speed):(-ball -> speed));
}

// This function moves the ball in the screen
void move_ball(void){
	// Updating the values cx and cy
	ball -> cy  += (ball -> dy * 100) / fps;
	ball -> cx += (ball -> dx * 100) / fps;

	// Checking if the ball went off the screen
	if(ball -> x <= -(ball -> image -> width)){
		score2 ++;
		ball -> x = window_width / 2;
		ball -> y = window_height / 2 + 100;
		ball -> dx *= -1;
		draw_scores();
		draw_rectangle(0, 100, window_width-1, window_height - 101, YELLOW);
		play_sound("explosion.ogg");
	}
	else if(ball -> x >= window_width + ball -> image -> width){
		score1 ++;
		ball -> x = window_width / 2;
		ball -> y = window_height / 2 + 100;
		ball -> dx *= -1;
		draw_scores();
		draw_rectangle(0, 100, window_width-1, window_height - 101, YELLOW);
		play_sound("explosion.ogg");
	}
	// Checking if the ball collides with the first paddle:
	else if(ball -> x <= paddle1 -> x + paddle1 -> image -> width &&
			(ball -> y >= paddle1 -> y - ball -> image -> height &&
			 ball -> y <= paddle1 -> y + paddle1 -> image -> height) &&
			ball -> dx < 0){
		int ball_center_y = ball -> y + ball -> image -> height / 2;
		int paddle_center_y = paddle1 -> y + paddle1 -> image -> height / 2;
		ball -> speed += 5;
		ball -> dy = -((float)(paddle_center_y - ball_center_y) / 
				(float)(paddle1 -> image -> height / 2)) * 0.65 * ball -> speed;
		ball -> dx = (int) sqrtf((float)((ball -> speed)*(ball -> speed) - (ball -> dy)*(ball -> dy)));
		play_sound("hit.ogg");
		return;
	}
	// Checking if the ball collides with the second paddle:
	else if(ball -> x + ball -> image -> width >= paddle2 -> x &&
			(ball -> y >= paddle2 -> y - ball -> image -> height &&
			 ball -> y <= paddle2 -> y + paddle2 -> image -> height) &&
			ball -> dx > 0){
		int ball_center_y = ball -> y + ball -> image -> height / 2;
		int paddle_center_y = paddle2 -> y + paddle2 -> image -> height / 2;
		ball -> speed += 5;
		ball -> dy = -((float)(paddle_center_y - ball_center_y) / 
				(float)(paddle2 -> image -> height / 2)) * 0.65 * ball -> speed;
		ball -> dx = -(int) sqrtf((float)((ball -> speed)*(ball -> speed) - (ball -> dy)*(ball -> dy)));
		play_sound("hit.ogg");
		return;
	}
	// Checking if the ball is colliding with the top or bottom of screen
	if(ball -> y <= 100 && ball -> dy < 0){
		ball -> dy *= -1;
		ball -> y = 102;
		draw_rectangle(0, 100, window_width-1, window_height - 101, YELLOW);
		return;
	}
	else if(ball -> y >= window_height - ball -> image -> height && ball -> dy > 0){
		ball -> dy *= -1;
		ball -> y = window_height - ball -> image -> height - 1;
		draw_rectangle(0, 100, window_width-1, window_height - 101, YELLOW);
		return;
	}

	// If we moved more than 100 centipixels, we need to update the movement
	if(ball -> cy >= 100 || ball -> cy <= -100 ||
			ball -> cx >= 100 || ball -> cx <= -100){
		// How many pixels we move in X and Y-axis:
		int change_x = ((ball -> cx >= 100)?(ball -> cx / 100):(ball -> cx / -100));
		int change_y = ((ball -> cy >= 100)?(ball -> cy / 100):(ball -> cy / -100));
		int buffer_x, buffer_y;
		// In this buffer we will manipulate the ball image
		surface *buffer = new_surface(ball -> image -> width + change_x,
				ball -> image -> height + change_y);

		// In wich coordinate should we draw the buffer?
		buffer_x = ((ball -> cx > 0)?(ball -> x):(ball -> x - change_x));
		buffer_y = ((ball -> cy > 0)?(ball -> y):(ball -> y - change_y));
		// Moving the ball...
		ball -> x += ball -> cx / 100;
		ball -> y += ball -> cy / 100;    
		// Updating buffer and screen...
		blit_surface(background, buffer, buffer_x, buffer_y - 100, 
				ball -> image -> width + change_x, 
				ball -> image -> height + change_y, 0, 0);
		draw_surface(ball -> image, buffer, 
				(ball -> cx > 0)?(change_x):(0), 
				(ball -> cy > 0)?(change_y):(0));
		draw_surface(buffer, window, buffer_x, buffer_y);
		// Updating the centipixels offset...
		ball -> cx %= 100;
		ball -> cy %= 100;
	}
}
