#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

static int printHead(HEAD *h){
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

int main(int argCount, char *arg[]){
	HEAD *file = getFile(arg[1]);
	if (h == NULL)
            exit(0);
	printHead(h);
	destroyFile(file);
	
}
