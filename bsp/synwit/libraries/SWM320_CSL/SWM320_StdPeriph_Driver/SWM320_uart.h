#ifndef __SWM320_UART_H__
#define __SWM320_UART_H__

typedef struct {
    uint32_t Baudrate;

    uint8_t  DataBits;          //数据位位数，可取值UART_DATA_8BIT、UART_DATA_9BIT

    uint8_t  Parity;            //奇偶校验位，可取值UART_PARITY_NONE、UART_PARITY_ODD、UART_PARITY_EVEN、UART_PARITY_ONE、UART_PARITY_ZERO

    uint8_t  StopBits;          //停止位位数，可取值UART_STOP_1BIT、UART_STOP_2BIT

    uint8_t  RXThreshold;       //取值0--7
    uint8_t  RXThresholdIEn;    //当RX FIFO中数据个数 >  RXThreshold时触发中断

    uint8_t  TXThreshold;       //取值0--7
    uint8_t  TXThresholdIEn;    //当TX FIFO中数据个数 <= TXThreshold时触发中断

    uint8_t  TimeoutTime;       //超时时长 = TimeoutTime/(Baudrate/10) 秒
    uint8_t  TimeoutIEn;        //超时中断，RX FIFO非空，且超过 TimeoutTime/(Baudrate/10) 秒没有在RX线上接收到数据时触发中断
} UART_InitStructure;


#define UART_DATA_8BIT      0
#define UART_DATA_9BIT      1

#define UART_PARITY_NONE    0
#define UART_PARITY_ODD     1
#define UART_PARITY_EVEN    3
#define UART_PARITY_ONE     5
#define UART_PARITY_ZERO    7

#define UART_STOP_1BIT      0
#define UART_STOP_2BIT      1

#define UART_RTS_1BYTE      0
#define UART_RTS_2BYTE      1
#define UART_RTS_4BYTE      2
#define UART_RTS_6BYTE      3

#define UART_ABR_RES_OK     1
#define UART_ABR_RES_ERR    2

#define UART_ERR_FRAME      1
#define UART_ERR_PARITY     2
#define UART_ERR_NOISE      3


/* Interrupt Type */
#define UART_IT_RX_THR      (1 << UART_CTRL_RXIE_Pos)   //RX FIFO Threshold, RX FIFO中数据个数 >  RXThreshold
#define UART_IT_RX_TOUT     (1 << UART_CTRL_TOIE_Pos)   //RX Timeout, 超过 TimeoutTime/(Baudrate/10) 秒没有在RX线上接收到数据
#define UART_IT_TX_THR      (1 << UART_CTRL_TXIE_Pos)   //TX FIFO Threshold, TX FIFO中数据个数 <= TXThreshold
#define UART_IT_TX_DONE     (1 << UART_CTRL_TXDOIE_Pos) //TX Done, 发送FIFO空且发送发送移位寄存器已将最后一位发送出去



void UART_Init(UART_TypeDef * UARTx, UART_InitStructure * initStruct);  //UART串口初始化
void UART_Open(UART_TypeDef * UARTx);
void UART_Close(UART_TypeDef * UARTx);

void UART_WriteByte(UART_TypeDef * UARTx, uint32_t data);               //发送一个字节数据
uint32_t UART_ReadByte(UART_TypeDef * UARTx, uint32_t * data);          //读取一个字节数据，并指出数据是否Valid

uint32_t UART_IsTXBusy(UART_TypeDef * UARTx);
uint32_t UART_IsRXFIFOEmpty(UART_TypeDef * UARTx);                      //接收FIFO是否空，如果不空则可以继续UART_ReadByte()
uint32_t UART_IsTXFIFOFull(UART_TypeDef * UARTx);                       //发送FIFO是否满，如果不满则可以继续UART_WriteByte()


void UART_SetBaudrate(UART_TypeDef * UARTx, uint32_t baudrate);         //设置波特率
uint32_t UART_GetBaudrate(UART_TypeDef * UARTx);                        //获取当前使用的波特率

void UART_CTSConfig(UART_TypeDef * UARTx, uint32_t enable, uint32_t polarity);
uint32_t UART_CTSLineState(UART_TypeDef * UARTx);

void UART_RTSConfig(UART_TypeDef * UARTx, uint32_t enable, uint32_t polarity, uint32_t threshold);
uint32_t UART_RTSLineState(UART_TypeDef * UARTx);

void UART_LINConfig(UART_TypeDef * UARTx, uint32_t detectedIEn, uint32_t generatedIEn);
void UART_LINGenerate(UART_TypeDef * UARTx);
uint32_t UART_LINIsDetected(UART_TypeDef * UARTx);
uint32_t UART_LINIsGenerated(UART_TypeDef * UARTx);

void UART_ABRStart(UART_TypeDef * UARTx, uint32_t detectChar);
uint32_t UART_ABRIsDone(UART_TypeDef * UARTx);


void UART_INTEn(UART_TypeDef * UARTx, uint32_t it);
void UART_INTDis(UART_TypeDef * UARTx, uint32_t it);
uint32_t UART_INTStat(UART_TypeDef * UARTx, uint32_t it);


#endif //__SWM320_UART_H__
