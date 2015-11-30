#ifndef structures
#define structures
#define WORD 4
typedef unsigned char 	BYTE;
typedef unsigned short	HALF;
typedef unsigned int	U_INT;
typedef enum dataFormat {BIG, LITTLE} ORDERING;

typedef struct HEADER{
	BYTE	chunkID[WORD];
	U_INT	chunkSize;
	BYTE	format[WORD];
	
	BYTE	subChunk1ID[WORD];
	U_INT	subChunk1Size;
	HALF	audioFormat;
	U_INT	numChannels;
	U_INT	sampleRate;
	U_INT	byteRate;
	HALF	blockAlign;
	HALF	bitsPerSample;
	HALF	extraVal;
	
	BYTE	subChunk2ID[WORD];
	U_INT	subChunk2Size;
	BYTE	*data;
} HEAD;

void getFile(char*, HEAD*, BYTE*);

#endif
