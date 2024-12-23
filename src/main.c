#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "problem.h"
#include "verify.h"

int menu(char* prompt, char* answers[10], int count){
	printf("<%s>\n", prompt);
	for(int i = 0; i < count; i++){
		if(answers[i] != ""){
			printf("[%i] %s\n", i + 1, answers[i]);
		}
	}
	int choice;
	getint(&choice);
	return choice - 1;
}

void operation(int op){
	int x;
	int y;
	int z;
	printf("X: ");
	getint(&x);
	printf("Y: ");
	getint(&y);
	switch(op){
		case 0:
			z = x + y;
			break;
		case 1:
			z = x - y;
			break;
		case 2:
			z = x * y;
			break;
		case 3:
			z = x / y;
			break;
	} 
	printf("Answer: %i\n", z);
}

int main(){
	srand(time(0));
	bool running = true;
	int choice;
	int x;
	int y;
	char* operations[10] = {
		"ADD",
		"SUB",
		"MUL",
		"DIV"
	};
	char* robot_insults[4] = {
		"fuck off tin can!",
		"nice try clanker!",
		"we don't serve your kind here!",
		"math is for meat folks, not you rust buckets"
	};
	char* bullet_hell[10] = {
		"give up",
		"try again"
	};
	while(running){
		system("clear");
		printf("ctrl+c to exit\n");
		choice = menu("what operation do you want?", operations, 4);
		if(problem()){
			if(verify()){
				sleep(3);
				system("clear");
				printf("so far you have proven your humanity\n");
				sleep(2);
				printf("but I can see through your disguise! YOU ARE A MACHINE! \n");
				sleep(2);
				printf("PREPARE TO MEET YOUR END! \n");
				sleep(2);
				while(1){
					system("clear");
					int success = system("./game/game");
					if(!success){
						choice = menu("Do you yeild? or are you too stubborn?", bullet_hell, 2);
						if(!choice){
							break;
						}
					}
					if(success){
						system("clear");
						operation(choice);
						break;
					}
				}
			}
		} else {
			printf("%s\n", robot_insults[better_rand(0, 3)]);
		}
		sleep(2);
	}
	return 0;
}
