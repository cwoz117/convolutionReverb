#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

static int printHead(HEAD *h){
      printf("Chunk ID: %.4s\n", h->chunkID);
      printf("Chunk Size: %d\n", h->chunkSize);
      printf("Format: %.4s\n", h->format);
      printf("Sub-Chunk 1 ID: %.4s\n", h->subChunk1ID);
      printf("Sub-Chunk 1 Size: %d\n", h->subChunk1Size);
      printf("Audio format: %d\n", h->audioFormat);
      printf("# of Channels: %d\n", h->numChannels);
      printf("Sample Rate: %d\n", h->sampleRate);
      printf("Byte Rate: %d\n", h->byteRate);
      printf("Block Align: %d\n", h->blockAlign);
      printf("Bit/Sample: %d\n", h->bitsPerSample);
      printf("Sub-Chunk 2 ID: %.4s\n", h->subChunk2ID);
      printf("Sub-Chunk 2 Size: %d\n", h->subChunk2Size);
}

int main(int argCount, char *arg[]){
	HEAD *h = malloc(sizeof(HEAD));
	printf("h size: %d\n", sizeof(HEAD));
	if (h == NULL){
            printf("malloc couldnt do it");
      }
	BYTE *data;
	getFile(arg[1], h, data);
	printHead(h);

	if (h != NULL)
	      free(h);
	//if (data != NULL)
	//     free(data);
}
