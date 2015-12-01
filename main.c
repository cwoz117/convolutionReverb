#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"

int main(int argCount, char *arg[]){	
	if (argCount == 4){
		HEAD *dry = getFile(arg[1]);
		if (dry == NULL)
			exit(0);	
		HEAD *iresp = getFile(arg[2]);
		if (iresp == NULL){
			destroy(dry);
			exit(0);
		}
		HEAD *output = malloc(sizeof(HEAD));
		if (output == NULL){
			destroy(dry);
			destroy(iresp);
			exit(0);
		}

		printf("Starting\n");

		// Convolve
		U_INT outSize = makeInt(&dry->head[SUB_CHUNK_2_SIZE], WORD) + 
						makeInt(&iresp->head[SUB_CHUNK_2_SIZE], WORD) - 1;
		output->head = generateHead();
		if (output->head == NULL){
			destroy(dry);
			destroy(iresp);
			destroy(output);
			exit(0);
		}
		output->data = convolve(dry, iresp, outSize);
		//output->data = malloc(outSize);
		if (output->data == NULL){
			destroy(dry);
			destroy(iresp);
			destroy(output);
			exit(0);
		}
		updateHeadData(output->head, outSize);
		writeToFile(output, arg[3], makeInt(&output->head[SUB_CHUNK_2_SIZE], WORD));
		destroy(output);
		destroy(dry);
		destroy(iresp);
	} else {
		printf("invalid number of arguments\n");
		exit(0);
	} 
}


