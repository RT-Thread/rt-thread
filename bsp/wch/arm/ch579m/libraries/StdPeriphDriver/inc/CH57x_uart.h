


#ifndef __CH57x_UART_H__
#define __CH57x_UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"


/**
  * @brief  LINE error and status define
  */
#define  STA_ERR_BREAK      RB_LSR_BREAK_ERR       // 数据间隔错误
#define  STA_ERR_FRAME      RB_LSR_FRAME_ERR       // 数据帧错误
#define  STA_ERR_PAR        RB_LSR_PAR_ERR         // 奇偶校验位出错
#define  STA_ERR_FIFOOV     RB_LSR_OVER_ERR        // 接收数据溢出

#define  STA_TXFIFO_EMP     RB_LSR_TX_FIFO_EMP     // 当前发送FIFO空，可以继续填充发送数据
#define  STA_TXALL_EMP      RB_LSR_TX_ALL_EMP      // 当前所有发送数据都发送完成
#define  STA_RECV_DATA      RB_LSR_DATA_RDY        // 当前有接收到数据


/**
  * @brief  Configuration UART TrigByte num
  */
typedef enum
{
    UART_1BYTE_TRIG = 0,        // 1字节触发
    UART_2BYTE_TRIG,            // 2字节触发
    UART_4BYTE_TRIG,            // 4字节触发
    UART_7BYTE_TRIG,            // 7字节触发

}UARTByteTRIGTypeDef;


/****************** UART0 */
void UART0_DefInit( void );                             /* 串口默认初始化配置 */
void UART0_BaudRateCfg( UINT32 baudrate );              /* 串口波特率配置 */
void UART0_ByteTrigCfg( UARTByteTRIGTypeDef b );        /* 串口字节触发中断配置 */
void UART0_INTCfg( UINT8 s,  UINT8 i );                 /* 串口中断配置 */
void UART0_Reset( void );                               /* 串口软件复位 */

#define UART0_CLR_RXFIFO()       (R8_UART0_FCR |= RB_FCR_RX_FIFO_CLR)          /* 清除当前接收FIFO */
#define UART0_CLR_TXFIFO()       (R8_UART0_FCR |= RB_FCR_TX_FIFO_CLR)          /* 清除当前发送FIFO */

#define UART0_GetITFlag()       (R8_UART0_IIR&RB_IIR_INT_MASK)          /* 获取当前中断标志 */
// please refer to LINE error and status define
#define UART0_GetLinSTA()       (R8_UART0_LSR)          /* 获取当前通讯状态 */

#define UART0_SendByte(b)       (R8_UART0_THR = b)      /* 串口单字节发送 */
void UART0_SendString( PUINT8 buf, UINT16 l );          /* 串口多字节发送 */
#define UART0_RecvByte()        ( R8_UART0_RBR )        /* 串口读取单字节 */
UINT16 UART0_RecvString( PUINT8 buf );                  /* 串口读取多字节 */



/****************** UART1 */
void UART1_DefInit( void );                             /* 串口默认初始化配置 */
void UART1_BaudRateCfg( UINT32 baudrate );              /* 串口波特率配置 */
void UART1_ByteTrigCfg( UARTByteTRIGTypeDef b );        /* 串口字节触发中断配置 */
void UART1_INTCfg( UINT8 s,  UINT8 i );                 /* 串口中断配置 */
void UART1_Reset( void );                               /* 串口软件复位 */

#define UART1_CLR_RXFIFO()       (R8_UART1_FCR |= RB_FCR_RX_FIFO_CLR)          /* 清除当前接收FIFO */
#define UART1_CLR_TXFIFO()       (R8_UART1_FCR |= RB_FCR_TX_FIFO_CLR)          /* 清除当前发送FIFO */

#define UART1_GetITFlag()       (R8_UART1_IIR&RB_IIR_INT_MASK)          /* 获取当前中断标志 */
// please refer to LINE error and status define
#define UART1_GetLinSTA()       (R8_UART1_LSR)          /* 获取当前通讯状态 */

#define UART1_SendByte(b)       (R8_UART1_THR = b)      /* 串口单字节发送 */
void UART1_SendString( PUINT8 buf, UINT16 l );          /* 串口多字节发送 */
#define UART1_RecvByte()        ( R8_UART1_RBR )        /* 串口读取单字节 */
UINT16 UART1_RecvString( PUINT8 buf );                  /* 串口读取多字节 */



/****************** UART2 */
void UART2_DefInit( void );                             /* 串口默认初始化配置 */
void UART2_BaudRateCfg( UINT32 baudrate );              /* 串口波特率配置 */
void UART2_ByteTrigCfg( UARTByteTRIGTypeDef b );        /* 串口字节触发中断配置 */
void UART2_INTCfg( UINT8 s,  UINT8 i );                 /* 串口中断配置 */
void UART2_Reset( void );                               /* 串口软件复位 */

#define UART2_CLR_RXFIFO()       (R8_UART2_FCR |= RB_FCR_RX_FIFO_CLR)          /* 清除当前接收FIFO */
#define UART2_CLR_TXFIFO()       (R8_UART2_FCR |= RB_FCR_TX_FIFO_CLR)          /* 清除当前发送FIFO */

#define UART2_GetITFlag()       (R8_UART2_IIR&RB_IIR_INT_MASK)          /* 获取当前中断标志 */
// please refer to LINE error and status define
#define UART2_GetLinSTA()       (R8_UART2_LSR)          /* 获取当前通讯状态 */

#define UART2_SendByte(b)       (R8_UART2_THR = b)      /* 串口单字节发送 */
void UART2_SendString( PUINT8 buf, UINT16 l );          /* 串口多字节发送 */
#define UART2_RecvByte()        ( R8_UART2_RBR )        /* 串口读取单字节 */
UINT16 UART2_RecvString( PUINT8 buf );                  /* 串口读取多字节 */




/****************** UART3 */
void UART3_DefInit( void );                             /* 串口默认初始化配置 */
void UART3_BaudRateCfg( UINT32 baudrate );              /* 串口波特率配置 */
void UART3_ByteTrigCfg( UARTByteTRIGTypeDef b );        /* 串口字节触发中断配置 */
void UART3_INTCfg( UINT8 s,  UINT8 i );                 /* 串口中断配置 */
void UART3_Reset( void );                               /* 串口软件复位 */

#define UART3_CLR_RXFIFO()       (R8_UART3_FCR |= RB_FCR_RX_FIFO_CLR)          /* 清除当前接收FIFO */
#define UART3_CLR_TXFIFO()       (R8_UART3_FCR |= RB_FCR_TX_FIFO_CLR)          /* 清除当前发送FIFO */

#define UART3_GetITFlag()       (R8_UART3_IIR&RB_IIR_INT_MASK)          /* 获取当前中断标志 */
// please refer to LINE error and status define
#define UART3_GetLinSTA()       (R8_UART3_LSR)          /* 获取当前通讯状态 */

#define UART3_SendByte(b)       (R8_UART3_THR = b)      /* 串口单字节发送 */
void UART3_SendString( PUINT8 buf, UINT16 l );          /* 串口多字节发送 */
#define UART3_RecvByte()        ( R8_UART3_RBR )        /* 串口读取单字节 */
UINT16 UART3_RecvString( PUINT8 buf );                  /* 串口读取多字节 */



#ifdef __cplusplus
}
#endif

#endif  // __CH57x_UART_H__

