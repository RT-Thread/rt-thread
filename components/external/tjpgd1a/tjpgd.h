/*----------------------------------------------------------------------------/
/ TJpgDec - Tiny JPEG Decompressor include file               (C)ChaN, 2011
/----------------------------------------------------------------------------*/

/* System Configurations */

#define	JD_SZBUF		512	/* Size of stream input buffer (should be multiple of 512) */
#define JD_FORMAT		1	/* Output RGB format 0:RGB888 (3 BYTE/pix), 1:RGB565 (1 WORD/pix) */
#define	JD_USE_SCALE	1	/* Use descaling feature for output */


/*---------------------------------------------------------------------------*/

#include "integer.h"


/* Error code */
typedef enum {
	JDR_OK = 0,	/* 0: Succeeded */
	JDR_INTR,	/* 1: Interrupted by output function */	
	JDR_INP,	/* 2: Device error or wrong termination of input stream */
	JDR_MEM1,	/* 3: Insufficient memory pool for the image */
	JDR_MEM2,	/* 4: Insufficient stream input buffer */
	JDR_PAR,	/* 5: Parameter error */
	JDR_FMT1,	/* 6: Data format error (may be damaged data) */
	JDR_FMT2,	/* 7: Right format but not supported */
	JDR_FMT3	/* 8: Not supported JPEG standard */
} JRESULT;


typedef struct {
	WORD left, right, top, bottom;
} JRECT;


/* Decompressor object structure */
typedef struct JDEC JDEC;
struct JDEC {
	UINT dctr;				/* Number of bytes available in the input buffer */
	BYTE* dptr;				/* Current data read ptr */
	BYTE* inbuf;			/* Bit stream input buffer */
	BYTE dmsk;				/* Current bit in the current read byte */
	BYTE scale;				/* Output scaling ratio */
	BYTE msx, msy;			/* MCU size in unit of block (width, height) */
	BYTE qtid[3];			/* Quantization table ID of each component */
	SHORT dcv[3];			/* Previous DC element of each component */
	WORD nrst;				/* Restart inverval */
	UINT width, height;		/* Size of the input image (pixel) */
	BYTE* huffbits[2][2];	/* Huffman bit distribution tables [id][dcac] */
	WORD* huffcode[2][2];	/* Huffman code word tables [id][dcac] */
	BYTE* huffdata[2][2];	/* Huffman decoded data tables [id][dcac] */
	LONG* qttbl[4];			/* Dequaitizer tables [id] */
	void* workbuf;			/* Working buffer for IDCT and RGB output */
	BYTE* mcubuf;			/* Working buffer for the MCU */
	void* pool;				/* Pointer to available memory pool */
	UINT sz_pool;			/* Size of momory pool (bytes available) */
	UINT (*infunc)(JDEC*, BYTE*, UINT);/* Pointer to jpeg stream input function */
	UINT (*outfunc)(JDEC*, void*, JRECT*);	/* Pointer to RGB output function */
	void* device;			/* Pointer to I/O device identifiler for the session */
};


#define	LDB_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr))<<8)|(WORD)*(BYTE*)((ptr)+1))



/* TJpgDec API functions */
JRESULT jd_prepare (JDEC*, UINT(*)(JDEC*,BYTE*,UINT), void*, UINT, void*);
JRESULT jd_decomp (JDEC*, UINT(*)(JDEC*,void*,JRECT*), BYTE);

