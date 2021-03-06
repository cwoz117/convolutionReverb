#ifndef structures
#define structures

#define BYTE 		 8
#define HALFWORD 	 2
#define WORD 		 4
#define HEADER_SIZE	46	// Total File size = 46 + SUB_CHUNK_2_SIZE

//Header Format: Int's are little endian, Char arrays are Big-Endian
// NOTE: Defined, but not used by our Wav format, needed for offsetting.
#define CHUNK_ID	 		 0 	// RIFF
#define CHUNK_SIZE			 4 	// 38 (U_INT)
#define FORMAT				 8 	// WAVE
#define	SUB_CHUNK_1_ID		12 	// "fmt "
#define SUB_CHUNK_1_SIZE	16 	// 18
#define AUDIO_FORMAT		20	// 1 		short
#define CHANNEL_COUNT		22	// 1 		short
#define SAMPLE_RATE			24	// 44100
#define	BYTE_RATE			28	// 88200
#define BLOCK_ALIGN			32	// 2 		short
#define BITS_PER_SAMPLE		34	// 16 		short
#define EXTRANEOUS_VAL		36	// 0 		short *NOTE
#define SUB_CHUNK_2_ID		38	// data
#define	DATA_SIZE			42	// 0

typedef unsigned char 	U_BYTE;
typedef unsigned short	U_SHORT;
typedef unsigned int	U_INT;

typedef struct HEADER{
	U_BYTE	*head;
	float	*data;
} HEAD;

U_BYTE 	* generateHead(U_INT dataSize);
HEAD 	* getFile(char *filename);
void	inputSide(HEAD *dry, HEAD *impulse, HEAD *output);
void	outputSide(HEAD *dry, HEAD *impulse, HEAD *output);
void 	destroy(HEAD *file);
void 	printHead(HEAD *file);
void 	writeToFile(HEAD *mem, char *filename);



#endif
