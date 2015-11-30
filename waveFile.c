#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"

static unsigned int makeInt(U_BYTE *bufferArray, int size){
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
static void pullValue(U_BYTE *source, U_BYTE *dest, int startIndex, int range){
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
int printHead(HEAD *h){
      printf("Chunk ID:         %.4s\n", h->chunkID);
      printf("Chunk Size:       %u\n", h->chunkSize);
      printf("Format:           %.4s\n", h->format);
      printf("Sub-Chunk 1 ID:   %.4s\n", h->subChunk1ID);
      printf("Sub-Chunk 1 Size: %u\n", h->subChunk1Size);
      printf("Audio format:     %hu\n", h->audioFormat);
      printf("# of Channels:    %hu\n", h->numChannels);
      printf("Sample Rate:      %u\n", h->sampleRate);
      printf("Byte Rate:        %u\n", h->byteRate);
      printf("Block Align:      %hu\n", h->blockAlign);
      printf("Bit/Sample:       %hu\n", h->bitsPerSample);
      printf("ExtraVal:         %hu\n", h->extraVal);
      printf("Sub-Chunk 2 ID:   %.4s\n", h->subChunk2ID);
      printf("Sub-Chunk 2 Size: %u\n", h->subChunk2Size);
}

HEAD * getFile(char *arg){
	U_BYTE buff[WORD * 13];
	U_BYTE temp[WORD];
	U_BYTE halfTemp[WORD/2];
	
	// Read contents of wave file.
	FILE *fp = fopen(arg, "rb");	
	if (fp == NULL)
		return NULL;
	int check = fread(&buff, sizeof(U_BYTE), sizeof(buff), fp);
	fclose(fp);
	
	// Assign heap space.
	HEAD *file = malloc(sizeof(HEAD));
	if (file == NULL)
		return NULL;
	
	

	// Tedius work of setting the struct up for processing.
	pullValue(&buff[0], &temp[0], 0, WORD);     // U_BYTE
	memcpy(file->chunkID, temp, WORD);
  
	pullValue(&buff[0], &temp[0], 4, sizeof(int));     // INT
	file->chunkSize = makeInt(temp, WORD);
	
	pullValue(&buff[0], &temp[0], 8, WORD);     // U_BYTE
	memcpy(file->format, temp, WORD);
	pullValue(&buff[0], &temp[0], 12, WORD);    // U_BYTE
	memcpy(file->subChunk1ID, temp, WORD);
  
	pullValue(&buff[0], &temp[0], 16, WORD);     // INT
	file->subChunk1Size = makeInt(temp, WORD);
  
	pullValue(&buff[0], &halfTemp[0], 20, WORD/2);       // 16 bit
	file->audioFormat = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], &halfTemp[0], 22, WORD/2);       // 16 bit
	file->numChannels = (short)makeInt(halfTemp, WORD/2);
  
	pullValue(&buff[0], &temp[0], 24, WORD);     // INT
	file->sampleRate = makeInt(temp, WORD);
	pullValue(&buff[0], &temp[0], 28, WORD);     // INT
	file->byteRate = makeInt(temp, WORD);
  
	pullValue(&buff[0], halfTemp, 32, WORD/2);       // 16 bit
	file->blockAlign = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], halfTemp, 34, WORD/2);       // 16 bit
	file->bitsPerSample = (short)makeInt(halfTemp, WORD/2);
	pullValue(&buff[0], halfTemp, 36, WORD/2);       // 16 bit
	file->extraVal = (short)makeInt(halfTemp, WORD/2);
  
	pullValue(&buff[0], temp, 38, WORD);    // U_BYTE
	memcpy(file->subChunk2ID, temp, WORD);
  
	pullValue(&buff[0], temp, 42, WORD);     // INT
	file->subChunk2Size = makeInt(temp, WORD);
  
	// Point to data.
	file->data = malloc(file->subChunk2Size);
	if (file->data == NULL){
		free(file);
		return NULL;
	}
	
	// %%%%%%$$$$ -> [$$$$]
	memcpy(file->data, &buff[46], file->subChunk2Size);
	
	return file;
}
