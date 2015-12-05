#include <stdlib.h>
#include <stdio.h>
#include <endian.h>
#include <string.h>
#include "structures.h"

void convolve(HEAD *dry, HEAD *impulse, HEAD *output){
	U_INT iMax;
	U_INT jMax;
	memcpy(&iMax, &dry->head[DATA_SIZE], WORD);
	memcpy(&jMax, &impulse->head[DATA_SIZE], WORD);
	iMax = iMax/2;
	jMax = jMax/2;
	for (int i = 0; i < iMax; i++){
		for (int j = 0; j < jMax; j++){
			output->data[i+j] += (dry->data[i] * impulse->data[j]);
		}
	}
}


