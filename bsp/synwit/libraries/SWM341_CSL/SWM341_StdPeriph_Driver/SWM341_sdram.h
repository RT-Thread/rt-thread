#ifndef __SWM341_SDRAM_H__
#define __SWM341_SDRAM_H__

typedef struct {
    uint8_t Size;               // SDRAM 容量，SDRAM_SIZE_2MB、SDRAM_SIZE_8MB、SDRAM_SIZE_16MB、SDRAM_SIZE_32MB
    uint8_t ClkDiv;             // SDRAM 时钟分频，SDRAM_CLKDIV_1、SDRAM_CLKDIV_2
    uint8_t CASLatency;         // 列地址到有效数据输出间隔，SDRAM_CASLATENCY_2、SDRAM_CASLATENCY_3
    uint8_t RefreshTime;        // 刷新时间，单位 ms，在这个时间内 SDRAM 必须完成一次整片刷新，通常为 64ms

    uint8_t TimeTRP;            // Row precharge delay，Precharge命令到另一个命令间延时
    uint8_t TimeTRCD;           // Row to column delay，行地址到列地址间延时，也即Activate命令到读写命令间延时
    uint8_t TimeTRC;            // Row cycle time, Activate to Activate on same bank
                                // 若 SDRAM 颗粒除了 tRC，还有 tRFC 或 tRRC 参数，则按照二者中较大的计算 TimeTRC
} SDRAM_InitStructure;

                                // rowaddr         bankaddr        coladdr
#define SDRAM_SIZE_2MB      3   // HADDR[20:10]    HADDR[9]        HADDR[8:1]
#define SDRAM_SIZE_8MB      0   // HADDR[22:11]    HADDR[10:9]     HADDR[8:1]
#define SDRAM_SIZE_16MB     1   // HADDR[23:12]    HADDR[11:10]    HADDR[9:1]
#define SDRAM_SIZE_32MB     2   // HADDR[24:12]    HADDR[11:10]    HADDR[9:1]

#define SDRAM_CLKDIV_1      0   // 支持的 CPU 频率范围：80MHz--125MHz
#define SDRAM_CLKDIV_2      1   // 支持的 CPU 频率范围：20MHz--160Mhz

#define SDRAM_CASLATENCY_2  0
#define SDRAM_CASLATENCY_3  1


#define SDRAM_TRP_1         0
#define SDRAM_TRP_2         1
#define SDRAM_TRP_3         2
#define SDRAM_TRP_4         3

#define SDRAM_TRCD_1        0
#define SDRAM_TRCD_2        1
#define SDRAM_TRCD_3        2
#define SDRAM_TRCD_4        3

#define SDRAM_TRC_4         3
#define SDRAM_TRC_5         4
#define SDRAM_TRC_6         5
#define SDRAM_TRC_7         6
#define SDRAM_TRC_8         7
#define SDRAM_TRC_9         8
#define SDRAM_TRC_10        9
#define SDRAM_TRC_11        10
#define SDRAM_TRC_12        11
#define SDRAM_TRC_13        12
#define SDRAM_TRC_14        13
#define SDRAM_TRC_15        14
#define SDRAM_TRC_16        15


void SDRAM_Init(SDRAM_InitStructure * initStruct);

void SDRAM_Enable(void);
void SDRAM_Disable(void);

#endif //__SWM341_SDRAM_H__
