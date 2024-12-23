#include <SDL2/SDL.h>

#include "level.h"
#include "bullet.h"

level new_level(char* title, int left, int right, int tracker, int stationary){
	level lv;
	lv.title = title;
	lv.left = left;
	lv.right = right;
	lv.tracker = tracker;
	lv.stationary = stationary;
	return lv;
}

void run_level(SDL_Window* win, level lv, bullet* bullets){
	SDL_SetWindowTitle(win, lv.title);
	for(int i = 0; i < lv.left; i++){
		push_bullet(bullets, new_left_bullet());
	}
	for(int i = 0; i < lv.right; i++){
		push_bullet(bullets, new_right_bullet());
	}
	for(int i = 0; i < lv.tracker; i++){
		push_bullet(bullets, new_tracker_bullet());
	}
	for(int i = 0; i < lv.stationary; i++){
		push_bullet(bullets, new_stationary_bullet());
	}
}
