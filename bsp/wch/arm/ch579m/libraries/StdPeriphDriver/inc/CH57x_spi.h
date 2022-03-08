


#ifndef __CH57x_SPI_H__
#define __CH57x_SPI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

/**
  * @brief  SPI0 interrupt bit define
  */

#define SPI0_IT_FST_BYTE        RB_SPI_IE_FST_BYTE              // 从机模式的首字节命令模式下，接收到首字节中断
#define SPI0_IT_FIFO_OV         RB_SPI_IE_FIFO_OV               // FIFO 溢出
#define SPI0_IT_DMA_END         RB_SPI_IE_DMA_END               // DMA 传输结束
#define SPI0_IT_FIFO_HF         RB_SPI_IE_FIFO_HF               // FIFO 使用过半
#define SPI0_IT_BYTE_END        RB_SPI_IE_BYTE_END              // 单字节传输完成
#define SPI0_IT_CNT_END         RB_SPI_IE_CNT_END               // 全部字节传输完成



/**
  * @brief  Configuration data mode
  */
typedef enum
{
    Mode0_LowBitINFront = 0,                    // 模式0，低位在前
    Mode0_HighBitINFront,                       // 模式0，高位在前
    Mode3_LowBitINFront,                        // 模式3，低位在前
    Mode3_HighBitINFront,                       // 模式3，高位在前
}ModeBitOrderTypeDef;


/**
  * @brief  Configuration SPI0 slave mode
  */
typedef enum
{
    Mode_DataStream = 0,                // 数据流模式
    Mose_FirstCmd,                      // 首字节命令模式
}Slave_ModeTypeDef;


/**************** SPI0 */
void SPI0_MasterDefInit( void );                            /* 主机模式默认初始化：模式0+3线全双工+8MHz */
void SPI0_CLKCfg( UINT8 c );                                /* SPI0 基准时钟配置，= d*Tsys */
void SPI0_DataMode( ModeBitOrderTypeDef m );                /* 设置数据流模式 */

void SPI0_MasterSendByte( UINT8 d );                        /* 发送单字节 (buffer) */
UINT8 SPI0_MasterRecvByte( void );                          /* 接收单字节 (buffer) */

void SPI0_MasterTrans( UINT8 *pbuf, UINT16 len );           /* 使用FIFO连续发送多字节 */
void SPI0_MasterRecv( UINT8 *pbuf, UINT16 len );            /* 使用FIFO连续接收多字节 */

void SPI0_MasterDMATrans( PUINT8 pbuf, UINT16 len);         /* DMA方式连续发送数据   */
void SPI0_MasterDMARecv( PUINT8 pbuf, UINT16 len);          /* DMA方式连续接收数据  */


void SPI0_SlaveInit( void );                                /* 设备模式默认初始化，建议设置MISO的GPIO对应为输入模式 */
#define SetFirstData(d)         (R8_SPI0_SLAVE_PRE = d)     /* 加载首字节数据内容 */
void SPI0_SlaveSendByte( UINT8 d );                         /* 从机模式，发送一字节数据 */
UINT8 SPI0_SlaveRecvByte( void );                           /* 从机模式，接收一字节数据 */

void SPI0_SlaveTrans( UINT8 *pbuf, UINT16 len );            /* 从机模式，发送多字节数据 */
void SPI0_SlaveRecv( PUINT8 pbuf, UINT16 len );             /* 从机模式，接收多字节数据  */

void SPI0_SlaveDMATrans( PUINT8 pbuf, UINT16 len);          /* 从机模式，DMA方式发送多字节数据 */
void SPI0_SlaveDMARecv( PUINT8 pbuf, UINT16 len);           /* 从机模式，DMA方式接收多字节数据 */

// refer to SPI0 interrupt bit define
#define SPI0_ITCfg(s,f)         ((s)?(R8_SPI0_INTER_EN|=f):(R8_SPI0_INTER_EN&=~f))
#define SPI0_GetITFlag(f)       (R8_SPI0_INT_FLAG&f)        /* 获取中断标志状态，0-未置位，(!0)-触发 */
#define SPI0_ClearITFlag(f)     (R8_SPI0_INT_FLAG = f)      /* 清除当前中断标志 */




/**************** SPI1 */
void SPI1_MasterDefInit( void );                            /* 主机模式默认初始化：模式0+3线全双工+8MHz */
void SPI1_CLKCfg( UINT8 c );                                /* SPI1 基准时钟配置，= d*Tsys */
void SPI1_DataMode( ModeBitOrderTypeDef m );                /* 设置数据流模式 */

void SPI1_MasterSendByte( UINT8 d );                        /* 发送单字节 (buffer) */
UINT8 SPI1_MasterRecvByte( void );                          /* 接收单字节 (buffer) */

void SPI1_MasterTrans( UINT8 *pbuf, UINT16 len );           /* 使用FIFO连续发送多字节 */
void SPI1_MasterRecv( UINT8 *pbuf, UINT16 len );            /* 使用FIFO连续接收多字节 */


// refer to SPI1 interrupt bit define
#define SPI1_ITCfg(s,f)         ((s)?(R8_SPI1_INTER_EN|=f):(R8_SPI1_INTER_EN&=~f))
#define SPI1_GetITFlag(f)       (R8_SPI1_INT_FLAG&f)        /* 获取中断标志状态，0-未置位，(!0)-触发 */
#define SPI1_ClearITFlag(f)     (R8_SPI1_INT_FLAG = f)      /* 清除当前中断标志 */




#ifdef __cplusplus
}
#endif

#endif  // __CH57x_SPI_H__

