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
	bu.x = x;
	bu.y = y;
	bu.w = 4;
	bu.h = 4;
	bu.speed = 0.01;
	bu.x_vel = 0;
	bu.y_vel = 0;
	bu.dead = false;
	return bu;
}

bullet move_bullet(bullet bu, int x, int y){
	if(!bu.dead){
		float dx = x - bu.x;
		float dy = y - bu.y;
		float d = fabs(dist(dx, dy));
		float scale = fabs(bu.speed / d);
		bu.x_vel = dx * scale;
		bu.y_vel = dy * scale;
		bu.x += bu.x_vel;
		bu.y += bu.y_vel;
	}
	return bu;
}

bool hit_bullet(bullet bu, player target){
	if(point_in_rect(bu.x+2, bu.y+2, target.rect)){
		return true;
	}
	return false;
}

void render_bullet(SDL_Renderer* rend, bullet bu){
	SDL_Rect rect;
	rect.x = bu.x;
	rect.y = bu.y;
	rect.w = bu.w;
	rect.h = bu.h;
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRect(rend, &rect);
}
