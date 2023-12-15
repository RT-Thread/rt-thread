#ifndef __SWM320_CAN_H__
#define __SWM320_CAN_H__

#define CAN_FRAME_STD   0
#define CAN_FRAME_EXT   1

typedef struct {
    uint8_t  Mode;          //CAN_MODE_NORMAL、CAN_MODE_LISTEN、CAN_MODE_SELFTEST
    uint8_t  CAN_BS1;       //CAN_BS1_1tq、CAN_BS1_2tq、... ... 、CAN_BS1_16tq
    uint8_t  CAN_BS2;       //CAN_BS2_1tq、CAN_BS2_2tq、... ... 、CAN_BS2_8tq
    uint8_t  CAN_SJW;       //CAN_SJW_1tq、CAN_SJW_2tq、CAN_SJW_3tq、CAN_SJW_4tq
    uint32_t Baudrate;      //波特率，即位传输速率，取值1--1000000
    uint8_t  FilterMode;    //CAN_FILTER_16b、CAN_FILTER_32b
    union {
        uint32_t FilterMask32b;     //FilterCheck & (~FilterMask) == ID & (~FilterMask)的Message通过过滤
        struct {                    // 0 must match    1 don't care
            uint16_t FilterMask16b1;
            uint16_t FilterMask16b2;
        };
    };
    union {
        uint32_t FilterCheck32b;
        struct {
            uint16_t FilterCheck16b1;
            uint16_t FilterCheck16b2;
        };
    };
    uint8_t  RXNotEmptyIEn;     //接收FIFO非空，有数据可读
    uint8_t  RXOverflowIEn;     //接收FIFO溢出，有数据丢失
    uint8_t  ArbitrLostIEn;     //控制器丢失仲裁变成接收方
    uint8_t  ErrPassiveIEn;     //接收/发送错误计数值达到127
} CAN_InitStructure;

#define CAN_MODE_NORMAL     0   //常规模式
#define CAN_MODE_LISTEN     1   //监听模式
#define CAN_MODE_SELFTEST   2   //自测模式

#define CAN_BS1_1tq         0
#define CAN_BS1_2tq         1
#define CAN_BS1_3tq         2
#define CAN_BS1_4tq         3
#define CAN_BS1_5tq         4
#define CAN_BS1_6tq         5
#define CAN_BS1_7tq         6
#define CAN_BS1_8tq         7
#define CAN_BS1_9tq         8
#define CAN_BS1_10tq        9
#define CAN_BS1_11tq        10
#define CAN_BS1_12tq        11
#define CAN_BS1_13tq        12
#define CAN_BS1_14tq        13
#define CAN_BS1_15tq        14
#define CAN_BS1_16tq        15

#define CAN_BS2_1tq         0
#define CAN_BS2_2tq         1
#define CAN_BS2_3tq         2
#define CAN_BS2_4tq         3
#define CAN_BS2_5tq         4
#define CAN_BS2_6tq         5
#define CAN_BS2_7tq         6
#define CAN_BS2_8tq         7

#define CAN_SJW_1tq         0
#define CAN_SJW_2tq         1
#define CAN_SJW_3tq         2
#define CAN_SJW_4tq         3

#define CAN_FILTER_16b      0   //两个16位过滤器
#define CAN_FILTER_32b      1   //一个32位过滤器

typedef struct {
    uint32_t id;        //消息ID
    uint8_t  format;    //帧格式：CAN_FRAME_STD、CAN_FRAME_EXT
    uint8_t  remote;    //消息是否为远程帧
    uint8_t  size;      //接收到的数据个数
    uint8_t  data[8];   //接收到的数据
} CAN_RXMessage;


/* Interrupt Type */
#define CAN_IT_RX_NOTEMPTY  (0x01 << 0)     //RX Buffer Not Empty
#define CAN_IT_RX_OVERFLOW  (0x01 << 3)     //RX Buffer Overflow
#define CAN_IT_TX_EMPTY     (0x01 << 1)     //TX Buffer Empty
#define CAN_IT_ARBLOST      (0x01 << 6)     //Arbitration lost
#define CAN_IT_ERR          (0x01 << 7)
#define CAN_IT_ERR_WARN     (0x01 << 2)     //TXERR/RXERR计数值达到Error Warning Limit
#define CAN_IT_ERR_PASS     (0x01 << 5)     //TXERR/RXERR计数值达到127
#define CAN_IT_WAKEUP       (0x01 << 4)



void CAN_Init(CAN_TypeDef * CANx, CAN_InitStructure * initStruct);
void CAN_Open(CAN_TypeDef * CANx);
void CAN_Close(CAN_TypeDef * CANx);

void CAN_Transmit(CAN_TypeDef * CANx, uint32_t format, uint32_t id, uint8_t data[], uint32_t size, uint32_t once);
void CAN_TransmitRequest(CAN_TypeDef * CANx, uint32_t format, uint32_t id, uint32_t once);
void CAN_Receive(CAN_TypeDef * CANx, CAN_RXMessage *msg);

uint32_t CAN_TXComplete(CAN_TypeDef * CANx);
uint32_t CAN_TXSuccess(CAN_TypeDef * CANx);

void CAN_AbortTransmit(CAN_TypeDef * CANx);

uint32_t CAN_TXBufferReady(CAN_TypeDef * CANx);
uint32_t CAN_RXDataAvailable(CAN_TypeDef * CANx);

void CAN_SetBaudrate(CAN_TypeDef * CANx, uint32_t baudrate, uint32_t CAN_BS1, uint32_t CAN_BS2, uint32_t CAN_SJW);

void CAN_SetFilter32b(CAN_TypeDef * CANx, uint32_t check, uint32_t mask);
void CAN_SetFilter16b(CAN_TypeDef * CANx, uint16_t check1, uint16_t mask1, uint16_t check2, uint16_t mask2);


void CAN_INTEn(CAN_TypeDef * CANx, uint32_t it);
void CAN_INTDis(CAN_TypeDef * CANx, uint32_t it);
void CAN_INTClr(CAN_TypeDef * CANx, uint32_t it);
uint32_t CAN_INTStat(CAN_TypeDef * CANx);

#endif //__SWM320_CAN_H__
