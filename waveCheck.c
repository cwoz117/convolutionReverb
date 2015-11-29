#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"

static int makeInt(ORDERING dataOrder, char *bufferArray, int size){
	int created = 0;
	int temp = 0;
	if (dataOrder == BIG){
		for (int i = 0; i < size; i++){
			temp = (int)bufferArray[i] << i * 8;
			created = created | temp;
		}
	} else {
		for (int i = size; i > 0; --i){
			temp = (int)bufferArray[i] << i * 8;
			created = created | temp;
		}
	}
	return created;
}


//VOLATILE
static void pullValue(BYTE *source, BYTE *dest, int startIndex, int range){
	for (int i = 0; i < range; i ++){
		dest[i] = source[startIndex];
		startIndex ++;
	}
}

void getFile(char *arg, HEAD *head, BYTE *data){
      
	FILE *fp = fopen(arg, "rb");
      
      BYTE buff[WORD * 13];
      BYTE temp[WORD];
      BYTE halfTemp[WORD/2];

	int check = fread(&buff, sizeof(BYTE), sizeof(buff), fp);

      // Tedius work of setting the struct up for processing.
      pullValue(&buff[0], temp, 0, sizeof(temp));     // BYTE
      memcpy(head->chunkID, temp, WORD);
      
      pullValue(&buff[0], temp, 4, sizeof(temp));     // INT
      head->chunkSize = makeInt(LITTLE, temp, WORD);
      
      pullValue(&buff[0], temp, 8, sizeof(temp));     // BYTE
      memcpy(head->format, temp, WORD);
      pullValue(&buff[0], temp, 12, sizeof(temp));    // BYTE
      memcpy(head->subChunk1ID, temp, WORD);
      
      pullValue(&buff[0], temp, 16, sizeof(temp));     // INT
      head->subChunk1Size = makeInt(LITTLE, temp, WORD);
      
      pullValue(&buff[0], temp, 20, sizeof(halfTemp));       // 16 bit
      head->audioFormat = (short)makeInt(LITTLE, halfTemp, WORD/2);
      pullValue(&buff[0], temp, 22, sizeof(halfTemp));       // 16 bit
      head->numChannels = (short)makeInt(LITTLE, halfTemp, WORD/2);
      
      pullValue(&buff[0], temp, 24, sizeof(temp));     // INT
      head->sampleRate = makeInt(LITTLE, temp, WORD);
      pullValue(&buff[0], temp, 28, sizeof(temp));     // INT
      head->byteRate = makeInt(LITTLE, temp, WORD);
      
      pullValue(&buff[0], temp, 32, sizeof(halfTemp));       // 16 bit
      head->blockAlign = (short)makeInt(LITTLE, halfTemp, WORD/2);
      pullValue(&buff[0], temp, 34, sizeof(halfTemp));       // 16 bit
      head->bitsPerSample = (short)makeInt(LITTLE, halfTemp, WORD/2);
      
      pullValue(&buff[0], temp, 36, sizeof(temp));    // BYTE
      memcpy(head->subChunk2ID, temp, WORD);
      
      pullValue(&buff[0], temp, 40, sizeof(temp));     // INT
      head->subChunk2Size = makeInt(LITTLE, temp, WORD);
      
      // Get the data Array filled
	fclose(fp);
}
