#define WIN_W 270
#define WIN_H 270

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "bullet.h"

int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *win = SDL_CreateWindow("", 0, 0, WIN_W, WIN_H, 0);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_ShowCursor(0);
	
	SDL_Event event;

	Uint32 frame_start;
	Uint32 frame_end;
	
	int mouse_x;
	int mouse_y;
	int mouse_gx;
	int mouse_gy;

	player pl = new_player(WIN_W/2, WIN_H/2);
	bullet test_bu = new_bullet(100, 100);

	bool running = true;

	while(running){
		frame_start = SDL_GetTicks();
		//test_bu.dead = true;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case 'q':
							running = false;
							break;
						case 'b':
							test_bu.dead = false;
							break;
					}
					break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);

		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_GetGlobalMouseState(&mouse_gx, &mouse_gy);

		pl = control_player(pl, mouse_x, mouse_y);
		render_player(rend, pl);

		test_bu = move_bullet(test_bu, pl.rect.x, pl.rect.y);

		render_bullet(rend, test_bu);
		if(hit_bullet(test_bu, pl)){
			pl.dead = true;
		}

		if(pl.dead){
			SDL_SetWindowTitle(win, "<YOU DIED>");
			SDL_Delay(1000);
			running = false;
		}
		//SDL_SetWindowPosition(win, mouse_gx-(WIN_W/2), mouse_gy-(WIN_H/2));

		SDL_RenderPresent(rend);

		frame_end = SDL_GetTicks() - frame_end;

		if(frame_end < 1/60){
			SDL_Delay(1/60 - frame_end);
		}
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
