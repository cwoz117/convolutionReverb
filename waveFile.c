#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "structures.h"

// 32768.0
const float hearingAid = 32768.0f;

void destroy(HEAD *file){
	if (file != NULL){
		free(file->head);
		free(file->data);
		free(file);
	}
}

// TODO
void writeToFile(HEAD *mem, char *arg){
	FILE *fp = fopen(arg, "wb");
	if (fp == NULL){
		printf("WRITE_TO_FILE - Could not open a new file\n");
		return;
	}
	// Write Header
	fwrite(&mem->head[0], sizeof(U_BYTE), HEADER_SIZE, fp);
	
	
	// Write Data.
	short val;
	U_INT dataSize;
	memcpy(&dataSize, &mem->head[DATA_SIZE], WORD);
	
	printf("WRITE_TO_FILE - data size to write: %d\n", dataSize);
	for (int i = 0; i < (dataSize/2); i++){
		val =(hearingAid * mem->data[i]);
		fwrite(&val, sizeof(U_SHORT), 1, fp);
	}
	
	printf("WRITE_TO_FILE - Finished data\n");
	
	fclose(fp);
}



U_BYTE * generateHead(U_INT dataSize){
	U_BYTE *ary = malloc(HEADER_SIZE);
	if (ary == NULL){
	  printf("could not allocate space\n");
	  return NULL;
	}
	memcpy(&ary[CHUNK_ID], "RIFF", WORD);
	memcpy(&ary[FORMAT], "WAVE", WORD);
	memcpy(&ary[SUB_CHUNK_1_ID], "fmt ", WORD);
	memcpy(&ary[SUB_CHUNK_2_ID], "data", WORD);
	
	int wavNum[] = {38,18,44100,88200,1,1,2,16,0};
	U_INT chunkSize = dataSize + 38;
	memcpy(&ary[CHUNK_SIZE], &chunkSize, WORD);
	memcpy(&ary[SUB_CHUNK_1_SIZE], &wavNum[1], WORD);
	memcpy(&ary[SAMPLE_RATE], &wavNum[2], WORD);
	memcpy(&ary[BYTE_RATE], &wavNum[3], WORD);
	memcpy(&ary[DATA_SIZE], &dataSize, WORD);

	memcpy(&ary[AUDIO_FORMAT], &wavNum[4], HALFWORD);
	memcpy(&ary[CHANNEL_COUNT], &wavNum[5], HALFWORD);
	memcpy(&ary[BLOCK_ALIGN], &wavNum[6], HALFWORD);
	memcpy(&ary[BITS_PER_SAMPLE], &wavNum[7], HALFWORD);
	memcpy(&ary[EXTRANEOUS_VAL], &wavNum[8], HALFWORD);
	
	return ary;
}

void printHead(HEAD *file){
	U_INT i = 0;
	U_INT val;
	U_SHORT halfVal;
	while (i < HEADER_SIZE){
		switch(i) {
			case CHUNK_ID      : case FORMAT: 
			case SUB_CHUNK_1_ID: case SUB_CHUNK_2_ID:
      			printf("%.4s\n", &file->head[i]);
      			i += WORD;
      			break;
      		case AUDIO_FORMAT   : case CHANNEL_COUNT : case BLOCK_ALIGN: 
      		case BITS_PER_SAMPLE: case EXTRANEOUS_VAL:
				memcpy(&halfVal, &file->head[i], HALFWORD);
				printf("%hu\n", halfVal);
				i += HALFWORD;
				break; 
			default:
				memcpy(&val, &file->head[i], WORD);
				printf("%u\n", val);
				i += WORD;
				break;
		}
	}
}

HEAD * getFile(char *arg){
	HEAD *file;
	U_INT dataSize = 0;
	
	// Read contents of wave file.
	FILE *fp = fopen(arg, "rb");	
	if (fp == NULL)
		printf("GET_FILE - Error opening file\n");
	printf("GET_FILE - Opened file\n");
	
	file = malloc(sizeof(HEAD));
	if (file == NULL)
		return NULL;
	
	file->head = malloc(HEADER_SIZE);
	if (file->head == NULL){
		fclose(fp);
		free(file);
		printf("GET_FILE - Could not create space for header\n");
		return NULL;
	}
	fread(&file->head[0], HEADER_SIZE, 1, fp);
	printf("GET_FILE - Copied Header data from file\n");

	
	// Create space for data.
	memcpy(&dataSize, &file->head[DATA_SIZE], WORD);
	printf("Get_FILE - File Size: %u\n", dataSize);
	file->data = malloc((dataSize/2) * sizeof(float));
	if (file->data == NULL){
		free(file->head);
		fclose(fp);
		return NULL;
	}
	printf("GET_FILE - Created Space for data\n");
	
	// Fill data with float values
	short sample = 50;
	for (int i =0; i < (dataSize/2); i++){
		fread(&sample, HALFWORD, 1, fp);
		file->data[i] = (float)((sample / hearingAid));
	}
	printf("GET_FILE - Filled data with floats\n");
	
	fclose(fp);
	return file;
}
