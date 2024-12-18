#include <stdio.h>
#include <stdbool.h>

int menu(char* prompt, char* answers[10], int count){
	printf("<%s>\n", prompt);
	for(int i = 0; i < count; i++){
		if(answers[i] != ""){
			printf("[%i] %s\n", i + 1, answers[i]);
		}
	}
	int choice;
	scanf("%i", &choice);
	return choice - 1;
}

void operation(int op){
	int x;
	int y;
	int z;
	printf("X: ");
	scanf("%i", &x);
	printf("Y: ");
	scanf("%i", &y);
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
	printf("Answer: %i", z);
}

int main(){
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
	while(running){
		choice = menu("what operation do you want?", operations, 4);
		operation(choice);
	}
	return 0;
}
