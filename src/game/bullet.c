#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "player.h" 
#include "level.h" 
#include "bullet.h" 

int better_rand(int min, int max){
	int x = rand() % (max - min + 1);
	return x;
}

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

bullet new_bullet(bullet_type type, int x, int y){
	bullet bu;
	bu.init = true;
	bu.type = type;
	bu.x = x;
	bu.y = y;
	bu.w = 4;
	bu.h = 4;
	bu.speed = 0.1;
	bu.age = 0;
	bu.x_vel = 0;
	bu.y_vel = 0;
	bu.dead = false;
	return bu;
}

bullet new_left_bullet(){
	return new_bullet(LEFT, 0, better_rand(0, WIN_H));
}

bullet new_right_bullet(){
	return new_bullet(RIGHT, WIN_W, better_rand(0, WIN_H));
}

bullet new_tracker_bullet(){
	return new_bullet(TRACKER, better_rand(0, WIN_W), 0);
}

bullet new_stationary_bullet(){
	return new_bullet(STATIONARY, better_rand(0, WIN_W), better_rand(0, WIN_H));
}

bullet move_bullet(bullet bu, int x, int y){
	if(bu.type != STATIONARY){
		float dx = x - bu.x;
		float dy = y - bu.y;
		float d = fabs(dist(dx, dy));
		float scale = fabs(bu.speed / d);
		bu.x_vel = dx * scale;
		bu.y_vel = dy * scale;
		bu.x += bu.x_vel;
		bu.y += bu.y_vel;
		if(bu.x == x && bu.y == y){
			bu.dead = true;
		}
	}
	if(bu.age >= GAME_SPEED){
		bu.dead = true;
	}
	bu.age++;
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
	if(bu.dead){
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	} else {
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	}
	SDL_RenderFillRect(rend, &rect);
}

int end_bullet(bullet* bullets){
	for(int i = 0; i < 1000; i++){
		if(!bullets[i].init){
			return i;
		}
	}
	return 0;
}

void push_bullet(bullet* bullets, bullet bu){
	bullets[end_bullet(bullets)] = bu;
}

void pop_bullet(bullet* bullets, int i){
	for(i; bullets[i].init; i++){
		bullets[i] = bullets[i + 1];
	}
}
