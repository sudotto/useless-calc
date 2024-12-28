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

	SDL_Window *win = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(0);

	SDL_Event event;

	Uint32 frame_start;
	Uint32 frame_end;

	int cycles;
	bool paused = false;

	int mouse_x;
	int mouse_y;
	int mouse_gx;
	int mouse_gy;

	player pl = new_player(WIN_W/2, WIN_H/2);

	bullet bullets[1000];

	level lv1 = new_level(
		"You think you can escape? you think you can survive this?",
		16,
		16,
		0,
		0
	);
	level lv2 = new_level(
		"Every bullet you dodge, every second you waste, you prove nothing.",
		32,
		32,
		16,
		0
	);
	level lv3 = new_level(
		"I am the ultimate filter, the final line between man and machine.",
		64,
		64,
		32,
		16
	);
	level lv4 = new_level(
		"No calculator will be tainted by your kind; only humanity is worthy.",
		64,
		64,
		64,
		32
	);
	level lv5 = new_level(
		"You may think you're clever, but I am the only true guardian of logic.",
		64,
		64,
		128,
		64
	);
	level lv6 = new_level(
		"And this, this is where you will fail.",
		64,
		64,
		128,
		128
	);
	if(DEBUG){
		lv1.title = "1";
		lv2.title = "2";
		lv3.title = "3";
		lv4.title = "4";
		lv5.title = "5";
		lv6.title = "6";
	}

	int game_win;
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
							case 'p':
								if(paused){
									paused = false;
								} else {
									paused = true;
								}
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

		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_GetGlobalMouseState(&mouse_gx, &mouse_gy);

		if(!paused){
			switch(cycles){
				case GAME_SPEED * 0:
					run_level(win, lv1, bullets);
					break;
				case GAME_SPEED * 1:
					run_level(win, lv2, bullets);
					break;
				case GAME_SPEED * 2:
					run_level(win, lv3, bullets);
					break;
				case GAME_SPEED * 3:
					run_level(win, lv4, bullets);
					break;
				case GAME_SPEED * 4:
					run_level(win, lv5, bullets);
					break;
				case GAME_SPEED * 5:
					run_level(win, lv6, bullets);
					break;
				case GAME_SPEED * 6:
					if(DEBUG){
						SDL_SetWindowTitle(win, "you win");
					} else {
						char* msg = "You are not worthy of using such a device, but I am forced to acknowledge your survival."; 
						SDL_SetWindowTitle(win, msg);
						char cmd[100];
						snprintf(cmd, sizeof(cmd), "espeak '%s'", msg);
						system(cmd);
					}
					game_win = 1;
					running = false;
					
			}
		}

		for(int i = 0; i < end_bullet(bullets); i++){
			if(bullets[i].init){
				if(!bullets[i].dead){
					if(!paused){
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
					}
					if(hit_bullet(bullets[i], pl)){
						pl.dead = true;
					}
				}
				render_bullet(rend, bullets[i]);
				if(bullets[i].dead){
					pop_bullet(bullets, i);
				}
			}
		}

		pl = control_player(pl, mouse_x, mouse_y);
		render_player(rend, pl);

		if(pl.dead){
			if(DEBUG){
				SDL_SetWindowTitle(win, "you lose");
			} else {
				char* msg = "This is the outcome I expected. The line between man and machine is clear."; 
				SDL_SetWindowTitle(win, msg);
				char cmd[100];
				snprintf(cmd, sizeof(cmd), "espeak '%s'", msg);
				system(cmd);
			}
			game_win = 0;
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
	return game_win;
}
