#ifndef structures
#define structures
#define WORD 4
typedef unsigned char 	U_BYTE;
typedef unsigned short	U_SHORT;
typedef unsigned int	U_INT;
typedef enum dataFormat {BIG, LITTLE} ORDERING;

typedef struct HEADER{
	U_BYTE	chunkID[WORD];
	U_INT	chunkSize;
	U_BYTE	format[WORD];
	
	U_BYTE	subChunk1ID[WORD];
	U_INT	subChunk1Size;
	U_SHORT	audioFormat;
	U_INT	numChannels;
	U_INT	sampleRate;
	U_INT	byteRate;
	U_SHORT	blockAlign;
	U_SHORT	bitsPerSample;
	U_SHORT	extraVal;
	
	U_BYTE	subChunk2ID[WORD];
	U_INT	subChunk2Size;
	U_BYTE	*data;
} HEAD;

void getFile(char *filename);
void destroyFile(HEAD *file);
void printFile(HEAD *file);
#endif
