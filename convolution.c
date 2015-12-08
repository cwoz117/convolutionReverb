#include <stdlib.h>
#include <stdio.h>
#include <endian.h>
#include <string.h>
#include "structures.h"

void inputSide(HEAD *dry, HEAD *impulse, HEAD *output){
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

void outputSide(HEAD *dry, HEAD *impulse, HEAD *output){
	U_INT iMax;
	U_INT jMax;
	U_INT outMax;
	memcpy(&iMax, &dry->head[DATA_SIZE], WORD);
	memcpy(&jMax, &impulse->head[DATA_SIZE], WORD);
	memcpy(&outMax, &output->head[DATA_SIZE], WORD);
	iMax = iMax/2;
	jMax = jMax/2;
	outMax = outMax/2;
	for (int i = 0; i < outMax; i++){
		output->data[i] = 0;
		for (int j = 0; j < jMax; j++){
			if ((i-j) >= 0 && (i-j) < iMax){
				output->data[i] += (dry->data[i-j] * impulse->data[j]);
			}
		}
	}
}
