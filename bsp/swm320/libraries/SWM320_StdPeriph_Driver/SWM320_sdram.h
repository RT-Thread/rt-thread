#ifndef __SWM320_SDRAM_H__
#define __SWM320_SDRAM_H__

typedef struct {	
	uint8_t CellSize;			// SDRAM颗粒的容量，SDRAM_CELLSIZE_16Mb、SDRAM_CELLSIZE_64Mb、SDRAM_CELLSIZE_128Mb、SDRAM_CELLSIZE_256Mb
	uint8_t CellBank;			// SDRAM颗粒有几个bank，SDRAM_CELLBANK_2、SDRAM_CELLBANK_4
	uint8_t CellWidth;			// SDRAM颗粒的位宽，SDRAM_CELLWIDTH_16、SDRAM_CELLWIDTH_32
	uint8_t CASLatency;			// 列地址到有效数据输出间隔，SDRAM_CASLATENCY_2、SDRAM_CASLATENCY_3
	
	uint8_t TimeTMRD;			// MRS to New Command
	uint8_t TimeTRRD;			// Activate to activate on different banks
	uint8_t TimeTRAS;			// Self refresh time，最小Self-refresh周期
	uint8_t TimeTRC;			// Row cycle delay，Refresh命令到Activate命令间延时，也是两个连续Refresh命令间延时
	uint8_t TimeTRCD;			// Row to column delay，行地址到列地址间延时，也即Activate命令到读写命令间延时
	uint8_t TimeTRP;			// Row precharge delay，Precharge命令到另一个命令间延时
} SDRAM_InitStructure;

#define SDRAM_CELLSIZE_16Mb		3
#define SDRAM_CELLSIZE_64Mb		0
#define SDRAM_CELLSIZE_128Mb	1
#define SDRAM_CELLSIZE_256Mb	2

#define SDRAM_CELLBANK_2		0
#define SDRAM_CELLBANK_4		1

#define SDRAM_CELLWIDTH_16		0
#define SDRAM_CELLWIDTH_32		1

#define SDRAM_CASLATENCY_2		2
#define SDRAM_CASLATENCY_3		3

#define SDRAM_TMRD_3			3
#define SDRAM_TMRD_4			4
#define SDRAM_TMRD_5			5
#define SDRAM_TMRD_6			6
#define SDRAM_TMRD_7			7

#define SDRAM_TRRD_2			2
#define SDRAM_TRRD_3			3

#define SDRAM_TRAS_2			2
#define SDRAM_TRAS_3			3
#define SDRAM_TRAS_4			4
#define SDRAM_TRAS_5			5
#define SDRAM_TRAS_6			6
#define SDRAM_TRAS_7			7

#define SDRAM_TRC_2				2
#define SDRAM_TRC_3				3
#define SDRAM_TRC_4				4
#define SDRAM_TRC_5				5
#define SDRAM_TRC_6				6
#define SDRAM_TRC_7				7
#define SDRAM_TRC_8				8
#define SDRAM_TRC_9				9
#define SDRAM_TRC_10			10
#define SDRAM_TRC_11			11
#define SDRAM_TRC_12			12
#define SDRAM_TRC_13			13
#define SDRAM_TRC_14			14
#define SDRAM_TRC_15			15

#define SDRAM_TRCD_3			3
#define SDRAM_TRCD_4			4
#define SDRAM_TRCD_5			5
#define SDRAM_TRCD_6			6
#define SDRAM_TRCD_7			7

#define SDRAM_TRP_3				3
#define SDRAM_TRP_4				4
#define SDRAM_TRP_5				5
#define SDRAM_TRP_6				6
#define SDRAM_TRP_7				7



void SDRAM_Init(SDRAM_InitStructure * initStruct);

void SDRAM_Enable(void);
void SDRAM_Disable(void);

#endif //__SWM320_SDRAM_H__
