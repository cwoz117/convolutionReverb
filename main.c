#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

int main(int argCount, char *arg[]){
	HEAD *file = getFile(arg[1]);
	if (file == NULL)
            exit(0);
	printHead(file);
	destroyFile(file);
	
}
