#ifndef __SWM320_I2C_H__
#define __SWM320_I2C_H__

typedef struct {
    uint8_t  Master;        //1 主机模式
    uint8_t  Addr7b;        //1 7位地址     0 10位地址

    uint32_t MstClk;        //主机传输时钟频率
    uint8_t  MstIEn;        //主机模式中断使能

    uint16_t SlvAddr;       //从机地址
    uint8_t  SlvRxEndIEn;   //从机接收完成中断使能
    uint8_t  SlvTxEndIEn;   //从机发送完成中断使能
    uint8_t  SlvSTADetIEn;  //从机检测到起始中断使能
    uint8_t  SlvSTODetIEn;  //从机检测到终止中断使能
    uint8_t  SlvRdReqIEn;   //从机接收到读请求中断使能
    uint8_t  SlvWrReqIEn;   //从机接收到写请求中断使能
} I2C_InitStructure;


void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitStructure * initStruct);

void I2C_Open(I2C_TypeDef * I2Cx);
void I2C_Close(I2C_TypeDef * I2Cx);

uint8_t I2C_Start(I2C_TypeDef * I2Cx, uint8_t addr);
void I2C_Stop(I2C_TypeDef * I2Cx);
uint8_t I2C_Write(I2C_TypeDef * I2Cx, uint8_t data);
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t ack);

#endif //__SWM320_I2C_H__
