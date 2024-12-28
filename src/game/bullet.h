#ifndef BULLET_H
#define BULLET_H

#define DEBUG 0

#define WIN_W 600
#define WIN_H 600

#define GAME_SPEED 9000

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"

int better_rand(int min, int max);
bool point_in_rect(int x, int y, SDL_Rect rect);
int dist(int x_dist, int y_dist);

typedef enum {
	LEFT,
	RIGHT,
	TRACKER,
	STATIONARY
} bullet_type;

typedef struct {
	bool init;
	float x;
	float y;
	float w;
	float h;
	int age;
	bool dead;
	bullet_type type;
	float speed;
	float x_vel;
	float y_vel;
} bullet;

bullet new_bullet(bullet_type type, int x, int y);

bullet new_left_bullet();
bullet new_right_bullet();
bullet new_tracker_bullet();
bullet new_stationary_bullet();

bullet move_bullet(bullet bu, int x, int y);
bool hit_bullet(bullet bu, player target);
void render_bullet(SDL_Renderer* rend, bullet bu);

int end_bullet(bullet* bullets);
void push_bullet(bullet* bullets, bullet bu);
void pop_bullet(bullet* bullets, int i);

#endif
