#ifndef __SWM341_I2C_H__
#define __SWM341_I2C_H__


typedef struct {
    uint8_t  Master;        //1 主机模式    0 从机模式
    uint32_t MstClk;        //主机传输时钟频率

    uint8_t  Addr10b;       //1 10位地址模式     0 7位地址模式
    uint16_t SlvAddr;       //从机地址
    uint16_t SlvAddrMsk;

    uint8_t  TXEmptyIEn;    //发送寄存器空中断使能
    uint8_t  RXNotEmptyIEn; //接收寄存器非空中断使能
    uint8_t  SlvSTADetIEn;  //从机检测到起始中断使能
    uint8_t  SlvSTODetIEn;  //从机检测到终止中断使能
} I2C_InitStructure;


/* Interrupt Type */
#define I2C_IT_TX_EMPTY     (1 <<  0)   //TX FIFO Empty
#define I2C_IT_RX_NOT_EMPTY (1 <<  1)   //RX FIFO Not Empty
#define I2C_IT_RX_OVF       (1 <<  2)   //RX FIFO Overflow
#define I2C_IT_TX_DONE      (1 <<  3)   //发送完成（接收到ACK）
#define I2C_IT_RX_DONE      (1 <<  4)   //接收完成（发送出ACK）
#define I2C_IT_SLV_DET_STA  (1 <<  8)   //从机检测到起始位
#define I2C_IT_SLV_DET_STP  (1 <<  9)   //从机检测到停止位
#define I2C_IT_ARB_LOST     (1 << 16)   //主机Arbitration lost
#define I2C_IT_SCL_LOW_TO   (1 << 17)   //主机SCL Low Timeout


void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitStructure * initStruct);

void I2C_Open(I2C_TypeDef * I2Cx);
void I2C_Close(I2C_TypeDef * I2Cx);

uint8_t I2C_Start(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t wait);
void I2C_Stop(I2C_TypeDef * I2Cx, uint8_t wait);
uint8_t I2C_Write(I2C_TypeDef * I2Cx, uint8_t data, uint8_t wait);
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t ack, uint8_t wait);

uint8_t I2C_StartDone(I2C_TypeDef * I2Cx);
uint8_t I2C_StopDone(I2C_TypeDef * I2Cx);
uint8_t I2C_WriteDone(I2C_TypeDef * I2Cx);
uint8_t I2C_ReadDone(I2C_TypeDef * I2Cx);
uint8_t I2C_IsAck(I2C_TypeDef * I2Cx);

void I2C_INTEn(I2C_TypeDef * I2Cx, uint32_t it);        //中断使能
void I2C_INTDis(I2C_TypeDef * I2Cx, uint32_t it);       //中断禁止
void I2C_INTClr(I2C_TypeDef * I2Cx, uint32_t it);       //中断标志清除
uint32_t I2C_INTStat(I2C_TypeDef * I2Cx, uint32_t it);  //中断状态查询

#endif //__SWM341_I2C_H__
