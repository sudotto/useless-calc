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
	bu.speed = 10;
	bu.dead = false;
	return bu;
}

bullet move_bullet(bullet bu, player target){
	if(!bu.dead){
		/*int hyp = dist(target.rect.x, target.rect.y, bu.rect.x, bu.rect.y);
		int x = (bu.rect.x - target.rect.x);
		int y = (bu.rect.y - target.rect.y);
		bu.rect.x -= (x / hyp) * bu.speed;
		bu.rect.y -= (y / hyp) * bu.speed;*/

		float x_dist = target.rect.x - bu.rect.x;
		float y_dist = target.rect.y - bu.rect.y;    
		float distance = dist(x_dist, y_dist);
		float dx = x_dist / bu.speed;
		float dy = y_dist / bu.speed;
		bu.rect.x += dx;
		bu.rect.y += dy;
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
