#include <stdlib.h>
#include <stdio.h>
#include <endian.h>
#include "structures.h"

U_BYTE * convolve(HEAD *dry, HEAD *impulse, U_INT dataSize){
	U_BYTE * data = malloc(dataSize);
	if (data == NULL){
		printf("Could not get space for output data\n");
		return NULL;
	}
	
	U_SHORT samples[dataSize/2];
	// Zero the data array
	for (int i = 0; i < (dataSize/2); i++){
		samples[i] = 0;
	}
	
	// Step through
	U_INT drySize = makeInt(&dry->head[SUB_CHUNK_2_SIZE], WORD);
	U_INT impulseSize = makeInt(&impulse->head[SUB_CHUNK_2_SIZE], WORD);
	U_SHORT current = 0; 
	U_SHORT dryVal= 0;
	U_SHORT impVal = 0;
	for (U_INT i = 0; i < drySize; i+= 2){
		for (U_INT j = 0; j < impulseSize; j+= 2){
			current = (data[i+j+1] << 8) | data[i+j];
			dryVal = (dry->data[i+1] << 8) | dry->data[i];
			impVal = (impulse->data[j+1] << 8) | impulse->data[j];
			current = current + (dryVal * impVal);
			data[i+j] = current & 0xFF;
			data[i+j+1] = (current >> 8) & 0xFF;
		}
	}
	
	return data;
}


