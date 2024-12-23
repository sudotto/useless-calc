#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"

player new_player(int x, int y){
	player pl;
	pl.rect.x = x;
	pl.rect.y = y;
	pl.rect.w = 10;
	pl.rect.h = 10;
	pl.dead = false;
	return pl;
}

player control_player(player pl, int x, int y){
	if(!pl.dead){
		pl.rect.x = x;
		pl.rect.y = y;
	}
	return pl;
}

void render_player(SDL_Renderer* rend, player pl){
	SDL_Rect rect;
	SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
	SDL_RenderFillRect(rend, &pl.rect);
}
