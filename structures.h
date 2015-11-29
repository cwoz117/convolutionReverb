#ifndef structures
#define structures
#define WORD 4
typedef unsigned char BYTE;
typedef enum dataFormat {BIG, LITTLE} ORDERING;

typedef struct HEADER{
	BYTE  chunkID[WORD];
	unsigned int   chunkSize;
	BYTE  format[WORD];

	BYTE  subChunk1ID[WORD];
	unsigned int      subChunk1Size;
	unsigned short    audioFormat;
	unsigned short    numChannels;
	unsigned int      sampleRate;
	unsigned int      byteRate;
	unsigned short    blockAlign;
	unsigned short    bitsPerSample;
	unsigned short    extraVal;

	BYTE  subChunk2ID[WORD];
	unsigned int   subChunk2Size;

} HEAD;

void getFile(char*, HEAD*, BYTE*);

#endif
