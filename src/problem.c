#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "problem.h"

int better_rand(int min, int max){
	int x = rand() % (max - min + 1);
	return x;
}

bool getint(int* x){
	if(!scanf("%i", x)){
		while(getchar() != '\n');
		return false;
	} else {
		return true;
	}
}

bool problem(){
	int x = better_rand(0, 100);
	int y = better_rand(0, 100);
	int op = better_rand(0, 3);
	char op_sym[4] = {'+', '-', '*', '/'};
	printf("Please verify your humanity... \n What is ");
	printf("%i %c %i ?\nanswer: ", x, op_sym[op], y);
	int answer;
	int correct;
	getint(&answer);
	switch(op){
		case 0:
			correct = x + y;
			break;
		case 1:
			correct = x - y;
			break;
		case 2:
			correct = x * y;
			break;
		case 3:
			correct = x / y;
			break;
	}
	if(answer == correct){
		return true;
	} else {
		return false;
	}
}
