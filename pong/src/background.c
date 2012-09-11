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
#include "background.h"

// This function initializes our background. It should be called once in
// the beginning of the program
void initialize_background(void){
	// First we load the file "texture.png" located in the directory "images"
	surface *texture = new_image("texture.png");
	// Next we allocate space for our background. It'll have the same
	// width than the screen. But how the first 100 lines of the screen
	// will be occupied by the scores, it'll have a height 100 pixels
	// smaller.
	background = new_surface(window_width, window_height - 100);
	// Now we apply the texture to our bigger surface.
	apply_texture(texture, background);
	// Done. Now we don't need the texture anymore. We destroy the surface
	// that stores the texture.
	destroy_surface(texture);
}
