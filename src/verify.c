#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "problem.h"
#include "verify.h"

bool verify(){
	system("clear");
	printf("it looks like you aren't logged!\n in please enter this verification code at http://localhost:7777");
	int code = better_rand(1000,9999);
	printf("your verification code is: %i\n", code);
	sleep(2);
	char cmd[100];
	snprintf(cmd, sizeof(cmd), "firefox http://localhost:7777/?c=%i && node server.js", code);
	if(!system(cmd)){
		return true;
	}
	return false;
}
