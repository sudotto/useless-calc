#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"

bool point_in_rect(int x, int y, SDL_Rect rect);
int dist(int x_dist, int y_dist);

typedef struct {
	SDL_Rect rect;
	bool dead;
	float speed;
	float x_vel;
	float y_vel;
} bullet;

bullet new_bullet(int x, int y);
bullet move_bullet(bullet bu, player target);
bool hit_bullet(bullet bu, player target);
void render_bullet(SDL_Renderer* rend, bullet bu);

#endif
