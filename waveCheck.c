#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"

static unsigned int makeInt(BYTE *bufferArray, int size){
	unsigned int created = 0;
	unsigned int temp = 0;
	for (int i = 0; i < size; i++){
	      unsigned int j = (unsigned int) bufferArray[i];
		temp = j << (i * 8);
		created = created | temp;
	}
	return created;
}

//VOLATILE
static void pullValue(BYTE *source, BYTE *dest, int startIndex, int range){
	for (int i = 0; i < range; i ++){
		dest[i] = source[startIndex];
		startIndex++;
	}
}

void destroyFile(HEAD *file){
	if (file != NULL){
		if (file->data != NULL)
			free(file->data);
		free(file);
	}
}

HEAD * getFile(char *arg){
	BYTE buff[WORD * 13];
	BYTE temp[WORD];
	BYTE halfTemp[WORD/2];
	
	// Read contents of wave file.
	FILE *fp = fopen(arg, "rb");	
	if (fp == NULL)
		return NULL;
	int check = fread(&buff, sizeof(BYTE), sizeof(buff), fp);
	fclose(fp);
	
	// Assign heap space.
	HEAD *file = malloc(sizeof(HEAD));
	if (file == NULL)
		return NULL;
	
	

	// Tedius work of setting the struct up for processing.
	pullValue(&buff[0], &temp[0], 0, sizeof(temp));     // BYTE
	memcpy(head->chunkID, temp, WORD);
  
	pullValue(&buff[0], &temp[0], 4, sizeof(int));     // INT
	head->chunkSize = makeInt(temp, WORD);
	
	pullValue(&buff[0], &temp[0], 8, sizeof(temp));     // BYTE
	memcpy(head->format, temp, WORD);
	pullValue(&buff[0], &temp[0], 12, sizeof(temp));    // BYTE
	memcpy(head->subChunk1ID, temp, WORD);
  
	pullValue(&buff[0], &temp[0], 16, sizeof(temp));     // INT
	head->subChunk1Size = makeInt(temp, WORD);
  
	pullValue(&buff[0], &halfTemp[0], 20, sizeof(halfTemp));       // 16 bit
	head->audioFormat = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], &halfTemp[0], 22, sizeof(halfTemp));       // 16 bit
	head->numChannels = (short)makeInt(halfTemp, WORD/2);
  
	pullValue(&buff[0], &temp[0], 24, sizeof(temp));     // INT
	head->sampleRate = makeInt(temp, WORD);
	pullValue(&buff[0], &temp[0], 28, sizeof(temp));     // INT
	head->byteRate = makeInt(temp, WORD);
  
	pullValue(&buff[0], halfTemp, 32, sizeof(halfTemp));       // 16 bit
	head->blockAlign = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], halfTemp, 34, sizeof(halfTemp));       // 16 bit
	head->bitsPerSample = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], halfTemp, 36, sizeof(halfTemp));       // 16 bit
	head->extraVal = (short)makeInt(halfTemp, WORD/2);
  
	pullValue(&buff[0], temp, 38, sizeof(temp));    // BYTE
	memcpy(head->subChunk2ID, temp, WORD);
  
	pullValue(&buff[0], temp, 42, sizeof(temp));     // INT
	head->subChunk2Size = makeInt(temp, WORD);
  
	// Point to data.
	head->data = malloc(head->subChunkSize);
	if (head->data == NULL){
		free(file);
		return NULL;
	}
	
	// %%%%%%$$$$ -> [$$$$]
	memcpy(head->data, buff[46], head->subChunkSize);
	
	return file;
}
