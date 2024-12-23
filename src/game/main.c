#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "bullet.h"
#include "level.h"

int main(){
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *win = SDL_CreateWindow("grace period", 0, 0, WIN_W, WIN_H, 0);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(0);

	SDL_Event event;

	Uint32 frame_start;
	Uint32 frame_end;

	int cycles;

	int mouse_x;
	int mouse_y;
	int mouse_gx;
	int mouse_gy;

	player pl = new_player(WIN_W/2, WIN_H/2);

	bullet bullets[100];

	level lv1 = new_level("level 1",3,3,0,0);
	level lv2 = new_level("level 2",5,5,3,0);
	level lv3 = new_level("level 3",7,7,5,3);
	level lv4 = new_level("level 4",9,9,7,5);
	level lv5 = new_level("level 5",11,11,9,7);

	bool running = true;

	while(running){
		frame_start = SDL_GetTicks();
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
					}
					if(DEBUG){
						switch(event.key.keysym.sym){
							case 'c':
								printf("%i\n", end_bullet(bullets));
								break;
							case 'l':
								push_bullet(bullets, new_left_bullet());
								break;
							case 'r':
								push_bullet(bullets, new_right_bullet());
								break;
							case 't':
								push_bullet(bullets, new_tracker_bullet());
								break;
							case 's':
								push_bullet(bullets, new_stationary_bullet());
								break;
						}
					}
					break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);

		switch(cycles){
			case 20000 * 2:
				run_level(win, lv1, bullets);
				break;
			case 20000 * 3:
				run_level(win, lv2, bullets);
				break;
			case 20000 * 4:
				run_level(win, lv3, bullets);
				break;
			case 20000 * 5:
				run_level(win, lv4, bullets);
				break;
			case 20000 * 6:
				run_level(win, lv5, bullets);
				break;
		}

		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_GetGlobalMouseState(&mouse_gx, &mouse_gy);

		pl = control_player(pl, mouse_x, mouse_y);
		render_player(rend, pl);

		for(int i = 0; i < end_bullet(bullets); i++){
			if(bullets[i].init){
				if(!bullets[i].dead){
					render_bullet(rend, bullets[i]);
					switch(bullets[i].type){
						case LEFT:
							bullets[i] = move_bullet(bullets[i], WIN_W, bullets[i].y);
							break;
						case RIGHT:
							bullets[i] = move_bullet(bullets[i], 0, bullets[i].y);
							break;
						case TRACKER:
							bullets[i] = move_bullet(bullets[i], pl.rect.x, pl.rect.y);
							break;
						case STATIONARY:
							bullets[i] = move_bullet(bullets[i], 0, 0);
							break;
					}
					if(hit_bullet(bullets[i], pl)){
						pl.dead = true;
					}
				}
				if(bullets[i].dead){
					printf("popped a bullet\n");
					pop_bullet(bullets, i);
				}
			}
		}

		if(pl.dead){
			SDL_SetWindowTitle(win, "you died");
			SDL_Delay(1000);
			running = false;
		}
		//SDL_SetWindowPosition(win, mouse_gx-(WIN_W/2), mouse_gy-(WIN_H/2));

		SDL_RenderPresent(rend);

		cycles++;

		frame_end = SDL_GetTicks() - frame_end;
		if(frame_end < 1/60){
			SDL_Delay(1/60 - frame_end);
		}
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
