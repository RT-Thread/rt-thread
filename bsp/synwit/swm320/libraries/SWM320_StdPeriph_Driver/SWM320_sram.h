#ifndef __SWM320_SRAM_H__
#define __SWM320_SRAM_H__

typedef struct {
    uint8_t ClkDiv;             //SRAM_CLKDIV_5...SRAM_CLKDIV_16，根据SRAM芯片所能跑的最高频率选择合适分频
    uint8_t DataWidth;          //SRAM_DATAWIDTH_8、SRAM_DATAWIDTH_16
} SRAM_InitStructure;


#define SRAM_CLKDIV_4   3
#define SRAM_CLKDIV_5   4
#define SRAM_CLKDIV_6   5
#define SRAM_CLKDIV_7   6
#define SRAM_CLKDIV_8   7
#define SRAM_CLKDIV_9   8
#define SRAM_CLKDIV_10  9
#define SRAM_CLKDIV_11  10
#define SRAM_CLKDIV_12  11
#define SRAM_CLKDIV_13  12
#define SRAM_CLKDIV_14  13
#define SRAM_CLKDIV_15  14
#define SRAM_CLKDIV_16  15

#define SRAM_DATAWIDTH_8    1
#define SRAM_DATAWIDTH_16   0


void SRAM_Init(SRAM_InitStructure * initStruct);


#endif //__SWM320_SRAM_H__
