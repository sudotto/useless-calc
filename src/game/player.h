#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect rect;
	bool dead;
} player;

player new_player(int x, int y);
player control_player(player pl, int x, int y);
void render_player(SDL_Renderer* rend, player pl);

#endif
