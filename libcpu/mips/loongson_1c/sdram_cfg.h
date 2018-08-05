
#ifndef __OPENLOONGSON_SDRAM_CFG_H
#define __OPENLOONGSON_SDRAM_CFG_H


//#define	SD_FREQ	(6 * PLL_M) / (2 * SDRAM_PARAM_DIV_NUM)
#define	SD_FREQ	(((APB_CLK / 4) * (PLL_MULT / CPU_DIV)) / SDRAM_PARAM_DIV_NUM)

 
/* 颗粒行数 */
#define	ROW_1K		0x7
#define	ROW_2K		0x0
#define	ROW_4K		0x1
#define	ROW_8K		0x2
#define	ROW_16K		0x3
/* 颗粒列数 */
#define	COL_256		0x7
#define	COL_512		0x0
#define	COL_1K		0x1
#define	COL_2K		0x2
#define	COL_4K		0x3
/* 颗粒位宽 */
#define	WIDTH_8		0x0
#define	WIDTH_16	0x1
#define	WIDTH_32	0x2

#define	TRCD		3
#define	TCL			3
#define	TRP			3
#define	TRFC		8
#define	TRAS		6
#define	TREF		0x818
#define	TWR			2

#define	DEF_SEL		0x1
#define	DEF_SEL_N	0x0
#define	HANG_UP		0x1
#define	HANG_UP_N	0x0
#define	CFG_VALID	0x1


#if 0
// 白菜板8MB
/*
    以型号为IS42S16400的SDRAM为例，
    物理参数为，
    容量：8MB
    位宽：16位
    列宽：8位，即2的8次方，即256
    行宽：12位，即2的12次方，即4K

    所以，
    颗粒的位宽=WIDTH_16
    颗粒的列数=COL_256
    颗粒的行数=ROW_4K

    再结合宏SD_PARA0和芯片手册中寄存器SD_CONFIG，相信一看就能明白
    替换宏SD_PARA0中的行宽、列宽和位宽
*/
#define SDRAM_WIDTH         (WIDTH_16)
#define SDRAM_COL           (COL_256)
#define SDRAM_ROW           (ROW_4K)

#else

// 智龙32MByte
#define SDRAM_WIDTH         (WIDTH_16)
#define SDRAM_COL           (COL_512)
#define SDRAM_ROW           (ROW_8K)

#endif

#define	SD_PARA0	(0x7f<<25 | \
					(TRAS << 21) | \
					(TRFC << 17) | (TRP << 14) | (TCL << 11) | \
					(TRCD << 8) | (SDRAM_WIDTH << 6) | (SDRAM_COL << 3) | \
					SDRAM_ROW)

#define	SD_PARA1	((HANG_UP_N << 8) | (DEF_SEL_N << 7) | (TWR << 5) | (TREF >> 7))

#define	SD_PARA1_EN	((CFG_VALID << 9) | (HANG_UP_N << 8) | \
					(DEF_SEL_N << 7) | (TWR << 5) | (TREF >> 7))


#endif
