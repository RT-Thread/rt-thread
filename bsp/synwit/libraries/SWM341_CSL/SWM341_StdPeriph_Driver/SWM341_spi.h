#ifndef __SWM341_SPI_H__
#define __SWM341_SPI_H__

typedef struct {
    uint8_t  FrameFormat;   //帧格式：SPI_FORMAT_SPI、SPI_FORMAT_TI_SSI
    uint8_t  SampleEdge;    //在SPI帧格式下，选择数据采样边沿：SPI_FIRST_EDGE、SPI_SECOND_EDGE
    uint8_t  IdleLevel;     //在SPI帧格式下，选择空闲时（无数据传输时）时钟线的电平：SPI_LOW_LEVEL、SPI_HIGH_LEVEL
    uint8_t  WordSize;      //字长度, 有效值4-16
    uint8_t  Master;        //1 主机模式    0 从机模式
    uint8_t  clkDiv;        //SPI_CLK = SYS_CLK / clkDiv，有效值：SPI_CLKDIV_4、SPI_CLKDIV_8、... ... 、SPI_CLKDIV_512

    uint8_t  RXThreshold;   //取值1--8
    uint8_t  RXThresholdIEn;//当RX FIFO中数据个数 >= RXThreshold时触发中断

    uint8_t  TXThreshold;   //取值0--7
    uint8_t  TXThresholdIEn;//当TX FIFO中数据个数 <= TXThreshold时触发中断

    uint8_t  TXCompleteIEn; //发送FIFO空且发送移位寄存器空中断使能
} SPI_InitStructure;

#define SPI_FORMAT_SPI          0       //Motorola SPI 格式
#define SPI_FORMAT_TI_SSI       1       //TI SSI 格式
#define SPI_FORMAT_I2S          2

#define SPI_FIRST_EDGE          0       //第一个时钟沿开始采样
#define SPI_SECOND_EDGE         1       //第二个时钟沿开始采样

#define SPI_LOW_LEVEL           0       //空闲时时钟线保持低电平
#define SPI_HIGH_LEVEL          1       //空闲时时钟线保持高电平

#define SPI_CLKDIV_2            8
#define SPI_CLKDIV_4            0
#define SPI_CLKDIV_8            1
#define SPI_CLKDIV_16           2
#define SPI_CLKDIV_32           3
#define SPI_CLKDIV_64           4
#define SPI_CLKDIV_128          5
#define SPI_CLKDIV_256          6
#define SPI_CLKDIV_512          7


/* Interrupt Type */
#define SPI_IT_RX_OVF       (1 << 0)    //RX FIFO Overflow
#define SPI_IT_RX_FULL      (1 << 1)    //RX FIFO Full
#define SPI_IT_RX_HFULL     (1 << 2)    //RX FIFO Half Full
#define SPI_IT_TX_EMPTY     (1 << 3)    //TX FIFO Empty
#define SPI_IT_TX_HFULL     (1 << 4)    //TX FIFO Half Full
#define SPI_IT_RX_THRES     (1 << 5)    //RX FIFO Threshold（接收FIFO中数据个数大于CTRL.RFTHR设定值）
#define SPI_IT_TX_THRES     (1 << 6)    //TX FIFO Threshold（发送FIFO中数据个数小于CTRL.TFTHR设定值）
#define SPI_IT_TX_DONE      (1 << 9)    //TX Done（发送FIFO空且发送移位寄存器空）
#define SPI_IT_CS_FALL      (1 << 10)   //从机模式下，CS下降沿中断
#define SPI_IT_CS_RISE      (1 << 11)   //从机模式下，CS上升沿中断


void SPI_Init(SPI_TypeDef * SPIx, SPI_InitStructure * initStruct);      //SPI初始化
void SPI_Open(SPI_TypeDef * SPIx);                                      //SPI打开，允许收发
void SPI_Close(SPI_TypeDef * SPIx);                                     //SPI关闭，禁止收发

uint32_t SPI_Read(SPI_TypeDef * SPIx);
void SPI_Write(SPI_TypeDef * SPIx, uint32_t data);
void SPI_WriteWithWait(SPI_TypeDef * SPIx, uint32_t data);
uint32_t SPI_ReadWrite(SPI_TypeDef * SPIx, uint32_t data);

uint32_t SPI_IsRXEmpty(SPI_TypeDef * SPIx);             //接收FIFO是否空，如果不空则可以继续SPI_Read()
uint32_t SPI_IsTXFull(SPI_TypeDef * SPIx);              //发送FIFO是否满，如果不满则可以继续SPI_Write()
uint32_t SPI_IsTXEmpty(SPI_TypeDef * SPIx);             //发送FIFO是否空


void SPI_INTEn(SPI_TypeDef * SPIx, uint32_t it);        //中断使能
void SPI_INTDis(SPI_TypeDef * SPIx, uint32_t it);       //中断禁止
void SPI_INTClr(SPI_TypeDef * SPIx, uint32_t it);       //中断标志清除
uint32_t SPI_INTStat(SPI_TypeDef * SPIx, uint32_t it);  //中断状态查询




typedef struct {
    uint8_t  Mode;          //I2S_MASTER_TX、I2S_MASTER_RX、I2S_MASTER_TX_RX、I2S_SLAVE_TX、I2S_SLAVE_RX、I2S_SLAVE_TX_RX
    uint8_t  FrameFormat;   //I2S_I2S_PHILIPS、I2S_MSB_JUSTIFIED、I2S_PCM_SHORT、I2S_PCM_LONG0、I2S_PCM_LONG1
    uint8_t  ChannelLen;    //I2S_CHNNLEN_16、I2S_CHNNLEN_32
    uint8_t  DataLen;       //I2S_DATALEN_8、I2S_DATALEN_16、I2S_DATALEN_24、I2S_DATALEN_32
    uint32_t ClkFreq;       //I2S_SCLK Frequency

    uint8_t  RXThreshold;   //取值1--8
    uint8_t  RXThresholdIEn;//当RX FIFO中数据个数 >= RXThreshold时触发中断

    uint8_t  TXThreshold;   //取值0--7
    uint8_t  TXThresholdIEn;//当TX FIFO中数据个数 <= TXThreshold时触发中断

    uint8_t  TXCompleteIEn; //发送FIFO空且发送移位寄存器空中断使能
} I2S_InitStructure;

#define I2S_MASTER_RX       5
#define I2S_MASTER_TX       6
#define I2S_SLAVE_RX        1
#define I2S_SLAVE_TX        2

#define I2S_I2S_PHILIPS     0
#define I2S_MSB_JUSTIFIED   1
#define I2S_PCM_SHORT       2
#define I2S_PCM_LONG0       3   //PCM Long Mode Sync Width 1 SCLK period
#define I2S_PCM_LONG1       4   //PCM Long Mode Sync Width 1 Data Length

#define I2S_CHNNLEN_16      0
#define I2S_CHNNLEN_32      1

#define I2S_DATALEN_8       0
#define I2S_DATALEN_16      1
#define I2S_DATALEN_24      2
#define I2S_DATALEN_32      3

void I2S_Init(SPI_TypeDef * SPIx, I2S_InitStructure * initStruct);      //I2S初始化
void I2S_Open(SPI_TypeDef * SPIx);                                      //I2S打开，允许收发
void I2S_Close(SPI_TypeDef * SPIx);                                     //I2S关闭，禁止收发


#endif //__SWM341_SPI_H__
