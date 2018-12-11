#ifndef __SWM320_SDRAM_H__
#define __SWM320_SDRAM_H__

typedef struct
{
    uint8_t DataWidth;          // 16、32

    uint8_t CellSize;           // SDRAM颗粒的容量
    uint8_t CellBank;           // SDRAM颗粒有几个bank
    uint8_t CellWidth;          // SDRAM颗粒的位宽 16、32
} SDRAM_InitStructure;

#define SDRAM_CELLSIZE_16Mb     3
#define SDRAM_CELLSIZE_64Mb     0
#define SDRAM_CELLSIZE_128Mb    1
#define SDRAM_CELLSIZE_256Mb    2

#define SDRAM_CELLBANK_2        0
#define SDRAM_CELLBANK_4        1

void SDRAM_Init(SDRAM_InitStructure *initStruct);

#endif //__SWM320_SDRAM_H__
