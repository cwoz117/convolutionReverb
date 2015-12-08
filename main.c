#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structures.h"

static void destroyAll(HEAD *a, HEAD *b, HEAD *c){
	destroy(a);
	destroy(b);
	destroy(c);
}
int main(int argCount, char *arg[]){	
	if (argCount == 4){
	
		clock_t start, end;
		
		// Load two files
		HEAD *dry = getFile(arg[1]);
		HEAD *iresp = getFile(arg[2]);
		HEAD *output = malloc(sizeof(HEAD));
		if (dry == NULL || iresp == NULL || output == NULL){
			printf("MAIN - Could not load sample files\n");
			destroyAll(dry, iresp, output);
			exit(-1);
		}	
		printf("MAIN - Created Space for 3 files\n");
		// Determine data size for output file
		U_INT dataSize;
		U_INT impSize;
		memcpy(&dataSize, &dry->head[DATA_SIZE], WORD);
		memcpy(&impSize, &iresp->head[DATA_SIZE], WORD);
		
		U_INT outSamples = ((dataSize + impSize)/2) - 1;
		output->head = generateHead(dataSize + impSize - HALFWORD);
		output->data = calloc(sizeof(float), outSamples);
		if (output->head == NULL || output->data == NULL){
			printf("MAIN - Could not generate output file\n");
			destroyAll(dry, iresp, output);
			exit(-1);
		}
		
		// Convolve
		printf("MAIN - setup output file, starting convolve...\n");
		start = clock();
		outputSide(dry, iresp, output);
		end = clock();
		printf("MAIN - finished convolution in %ld\n", (end - start)/CLOCKS_PER_SEC);
		
		// Save file
		writeToFile(output, arg[3]);
		printf("MAIN - Wrote to file\n");
		
		// Clean up
		destroyAll(dry, iresp, output);
		printf("MAIN - Cleaned up data\n");
		
	} else {
		printf("invalid number of arguments\n");
		exit(0);
	} 
}


