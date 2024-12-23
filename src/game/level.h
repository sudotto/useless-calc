#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>

#include "bullet.h"

void camera_shake(SDL_Window* win, int intensity, int duration);

typedef struct {
	char* title;
	int left;
	int right;
	int tracker;
	int stationary;
} level;

level new_level(char* title, int left, int right, int tracker, int stationary);
void run_level(SDL_Window* win, level lv, bullet* bullets);

#endif
