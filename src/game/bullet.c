#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "player.h" 
#include "bullet.h" 

bool point_in_rect(int x, int y, SDL_Rect rect){
	if(x >= rect.x && x <= rect.x + rect.w){
		if(y >= rect.y && y <= rect.y + rect.h){
			return true;
		}
	}
	return false;
}

int dist(int x_dist, int y_dist){
	return sqrt((pow(x_dist, 2) + pow(y_dist, 2)));
}

bullet new_bullet(int x, int y){
	bullet bu;
	bu.rect.x = x;
	bu.rect.y = y;
	bu.rect.w = 4;
	bu.rect.h = 4;
	bu.speed = 3;
	bu.dead = false;
	return bu;
}

bullet move_bullet(bullet bu, player target){
	if(!bu.dead){
		float dx = bu.rect.x - target.rect.x;
		float dy = bu.rect.y - target.rect.y;
		float d = dist(dx, dy);
		float scale = fabs(bu.speed / d);
		float x = dx * scale;
		float y = dy * scale;
		bu.rect.x -= x;// / 10;
		bu.rect.y -= y;// / 10;
	}
	return bu;
}

bool hit_bullet(bullet bu, player target){
	if(point_in_rect(bu.rect.x+2, bu.rect.y+2, target.rect)){
		return true;
	}
	return false;
}

void render_bullet(SDL_Renderer* rend, bullet bu){
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRect(rend, &bu.rect);
}
