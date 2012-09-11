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

#ifndef _SCORE_H
#define _SCORE_H
#include "game.h"

int score1, score2;
surface *numbers;
void initialize_scores(void);
void draw_scores(void);
#endif
