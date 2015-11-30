#ifndef structures
#define structures
#define WORD 4
typedef unsigned char 	BYTE;
typedef unsigned short	HALF;
typedef unsigned int	WORD;
typedef enum dataFormat {BIG, LITTLE} ORDERING;

typedef struct HEADER{
	BYTE	chunkID[WORD];
	WORD	chunkSize;
	BYTE	format[WORD];
	
	BYTE	subChunk1ID[WORD];
	WORD	subChunk1Size;
	HALF	audioFormat;
	WORD	numChannels;
	WORD	sampleRate;
	WORD	byteRate;
	HALF	blockAlign;
	HALF	bitsPerSample;
	HALF	extraVal;
	
	BYTE	subChunk2ID[WORD];
	WORD	subChunk2Size;
	BYTE	*data;
} HEAD;

void getFile(char*, HEAD*, BYTE*);

#endif
