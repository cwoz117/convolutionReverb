#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"

U_INT makeInt(U_BYTE *bufferArray, int size){
	U_INT created = 0;
	U_INT temp = 0;
	for (U_INT i = 0; i < size; i++){
	      U_INT j = bufferArray[i];
		temp = j << (i * BYTE);
		created = created | temp;
	}
	return created;
}

void writeToFile(HEAD *mem, char *arg, int dataSize){
	FILE *fp = fopen(arg, "wb");
	if (fp != NULL){
		fwrite(mem->head, sizeof(U_BYTE), HEADER_SIZE, fp);
		if (mem->data != NULL)
			fwrite(&mem->data[0], sizeof(U_BYTE), dataSize, fp);
	}
	fclose(fp);
}

void destroy(HEAD *file){
  free(file->head);
  free(file->data);
  free(file);
}


/*
	char *str[4];
	str[0] = "RIFF";
	str[1] = "WAVE";
	str[2] = "fmt ";
	str[3] = "data";
	U_BYTE *headAry = malloc(HEADER_SIZE);
	if (headAry == NULL){
	  printf("could not allocate space\n");
	  return NULL;
	}
	U_INT i, j = 0;
	while (i < HEADER_SIZE){
		switch(i) {
			case CHUNK_ID      : case FORMAT: 
			case SUB_CHUNK_1_ID: case SUB_CHUNK_2_ID:
      			memcpy(&headAry[i], &file->head[i], WORD);
      			i += WORD;
      			break;
      		case AUDIO_FORMAT   : case CHANNEL_COUNT : case BLOCK_ALIGN: 
      		case BITS_PER_SAMPLE: case EXTRANEOUS_VAL:
      			memcpy(&headAry[i], &file->head[i], HALFWORD);
				i += HALFWORD;
				break; 
			case SUB_CHUNK_2_SIZE: case CHUNK_SIZE:
				j = size;
				if (i == CHUNK_SIZE){
					j += 38;
				}
				headAry[i+0] = (char)(0xFF & j);
				headAry[i+1] = (char)(0xFF & (j >> 8));
				headAry[i+2] = (char)(0xFF & (j >> 16));
				headAry[i+3] = (char)(0xFF & (j >> 24));
				i += WORD;
				break;
			default:
				memcpy(&headAry[i], &file->head[i], WORD);
				i += WORD;
				break;
		}
	}
	return headAry;
*/
void setLittleEndian(int index, int size, U_BYTE *head, U_INT value){
	U_BYTE myWord[4];
	for (int i = 0; i < WORD; i++){
		myWord[i] = 0xFF & (value >> i*8);
	}
	memcpy(&head[index], &myWord[0], size);
}

U_BYTE * generateHead(){
	U_BYTE *headAry = malloc(HEADER_SIZE);
	if (headAry == NULL){
	  printf("could not allocate space\n");
	  return NULL;
	}
	memcpy(&headAry[CHUNK_ID], "RIFF", WORD);
	memcpy(&headAry[FORMAT], "WAVE", WORD);
	memcpy(&headAry[SUB_CHUNK_1_ID], "fmt ", WORD);
	memcpy(&headAry[SUB_CHUNK_2_ID], "data", WORD);
	
	setLittleEndian(CHUNK_SIZE, WORD, headAry, 38);
	setLittleEndian(SUB_CHUNK_1_SIZE, WORD, headAry, 18);
	setLittleEndian(SAMPLE_RATE, WORD, headAry, 44100);
	setLittleEndian(BYTE_RATE, WORD, headAry, 88200);
	setLittleEndian(SUB_CHUNK_2_SIZE, WORD, headAry, 0);
	
	setLittleEndian(AUDIO_FORMAT, HALFWORD, headAry, 1);
	setLittleEndian(CHANNEL_COUNT, HALFWORD, headAry, 1);
	setLittleEndian(BLOCK_ALIGN, HALFWORD, headAry, 2);
	setLittleEndian(BITS_PER_SAMPLE, HALFWORD, headAry, 16);
	setLittleEndian(EXTRANEOUS_VAL, HALFWORD, headAry, 0);
	
	return headAry;
	
}
void updateHeadData(U_BYTE *head, U_INT dataSize){
	setLittleEndian(CHUNK_SIZE, WORD, head, (38 + dataSize));
	setLittleEndian(SUB_CHUNK_2_SIZE, WORD, head, dataSize);
}

void printHead(HEAD *file){
	U_INT i = 0;
	
	while (i < HEADER_SIZE){
		switch(i) {
			case CHUNK_ID      : case FORMAT: 
			case SUB_CHUNK_1_ID: case SUB_CHUNK_2_ID:
      			printf("%.4s\n", &file->head[i]);
      			i += WORD;
      			break;
      		case AUDIO_FORMAT   : case CHANNEL_COUNT : case BLOCK_ALIGN: 
      		case BITS_PER_SAMPLE: case EXTRANEOUS_VAL:
				printf("%hu\n", makeInt(&file->head[i], HALFWORD));
				i += HALFWORD;
				break; 
			default:
				printf("%u\n", makeInt(&file->head[i], WORD));
				i += WORD;
				break;
		}
	}
}

HEAD * getFile(char *arg){
	U_BYTE buff[HEADER_SIZE];
	U_BYTE temp[WORD];
	U_BYTE halfTemp[HALFWORD];
	
	// Read contents of wave file.
	FILE *fp = fopen(arg, "rb");	
	if (fp == NULL)
		return NULL;
		
	int check = fread(&buff, sizeof(U_BYTE), sizeof(buff), fp);
	
	// Assign and fill heap space for header.
	HEAD *file = malloc(sizeof(HEAD));
	if (file == NULL){
		fclose(fp);
		return NULL;
	}
	file->head = malloc(HEADER_SIZE);
	if (file->head == NULL){
		fclose(fp);
		free(file);
		return NULL;
	}
	memcpy(file->head, buff, HEADER_SIZE);
      
	// Point to data.
	file->data = malloc(makeInt(&file->head[SUB_CHUNK_2_SIZE], WORD));
	if (file->data == NULL){
		fclose(fp);
		free(file->head);
		free(file);
		return NULL;
	}
	
	// read the rest of the file
	fread(file->data, sizeof(U_BYTE), makeInt(&file->head[SUB_CHUNK_2_SIZE], WORD), fp);
	
	fclose(fp);
	return file;
}
