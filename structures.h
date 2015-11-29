#ifndef structures
#define structures
#define WORD 4
typedef unsigned char BYTE;
typedef enum dataFormat {BIG, LITTLE} ORDERING;

typedef struct HEADER{
	char  chunkID[WORD];
	int   chunkSize;
	char  format[WORD];

	char  subChunk1ID[WORD];
	int   subChunk1Size;
	short   audioFormat;
	short   numChannels;
	int   sampleRate;
	int   byteRate;
	short   blockAlign;
	short   bitsPerSample;

	char  subChunk2ID[WORD];
	int   subChunk2Size;

} HEAD;

void getFile(char*, HEAD*, BYTE*);

#endif
