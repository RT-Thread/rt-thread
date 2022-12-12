/**
  ******************************************************************************
  * @file    lib_uart.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   UART library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_UART_H
#define __LIB_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
//UART Init struct    
typedef struct
{
  uint32_t Mode;
  uint32_t Parity;
  uint32_t FirstBit;
  uint32_t Baudrate;
} UART_InitType;

//Mode
#define UART_MODE_RX   (0x1U << UART_CTRL_RXEN_Pos)
#define UART_MODE_TX   (0x1U << UART_CTRL_TXEN_Pos)
#define UART_MODE_OFF  0
#define UART_MODE_Msk  (UART_MODE_RX | UART_MODE_TX)
//Parity
#define UART_PARITY_EVEN    (0x1U << UART_CTRL2_PMODE_Pos)
#define UART_PARITY_ODD     (0x3U << UART_CTRL2_PMODE_Pos)
#define UART_PARITY_0       (0x5U << UART_CTRL2_PMODE_Pos)
#define UART_PARITY_1       (0x7U << UART_CTRL2_PMODE_Pos)
#define UART_PARITY_NONE    (0x0U << UART_CTRL2_PMODE_Pos)

//FirstBit
#define UART_FIRSTBIT_LSB   0
#define UART_FIRSTBIT_MSB   (0x1U << UART_CTRL2_MSB_Pos)

//UART Configration Information struct
typedef struct 
{
  uint32_t Mode_Transmit  :1; //1: TX Enable; 0: TX Disable
  uint32_t Mode_Receive   :1; //1: RX Enable; 0: RX Disable
  uint32_t Baudrate;          //The value of current budrate
  uint8_t  Parity;             //0:1+8+1 mode; 1: Even parity; 3:Odd parity; 5: parity bit=0; 7: parity bit=1;
  uint8_t  FirstBit;          //0: LSB transmit first; 1: MSB transmit first
} UART_ConfigINFOType;

//status
#define UART_FLAG_DMATXDONE   (0x1U << UART_STATE_DMATXDONE_Pos)
#define UART_FLAG_RXPARITY    (0x1U << UART_STATE_RXPSTS_Pos)
#define UART_FLAG_TXDONE      (0x1U << UART_STATE_TXDONE_Pos)
#define UART_FLAG_RXPE        (0x1U << UART_STATE_RXPE_Pos)
#define UART_FLAG_RXOV        (0x1U << UART_STATE_RXOV_Pos)
#define UART_FLAG_TXOV        (0x1U << UART_STATE_TXOV_Pos)
#define UART_FLAG_RXFULL      (0x1U << UART_STATE_RXFULL_Pos)
#define UART_FLAG_RCMsk      (UART_FLAG_DMATXDONE \
                             |UART_FLAG_TXDONE    \
                             |UART_FLAG_RXPE      \
                             |UART_FLAG_RXOV      \
                             |UART_FLAG_RXFULL    \
                             |UART_FLAG_TXOV)

//interrupt
#define UART_INT_TXDONE     (0x1U << UART_CTRL_TXDONEIE_Pos)
#define UART_INT_RXPE       (0x1U << UART_CTRL_RXPEIE_Pos)
#define UART_INT_RXOV       (0x1U << UART_CTRL_RXOVIE_Pos)
#define UART_INT_TXOV       (0x1U << UART_CTRL_TXOVIE_Pos)
#define UART_INT_RX         (0x1U << UART_CTRL_RXIE_Pos)
#define UART_INT_Msk       (UART_INT_TXDONE \
                           |UART_INT_RXPE   \
                           |UART_INT_RXOV   \
                           |UART_INT_TXOV   \
                           |UART_INT_RX)

//INTStatus
#define UART_INTSTS_TXDONE  (0x1U << UART_INTSTS_TXDONEIF_Pos)
#define UART_INTSTS_RXPE    (0x1U << UART_INTSTS_RXPEIF_Pos)
#define UART_INTSTS_RXOV    (0x1U << UART_INTSTS_RXOVIF_Pos)
#define UART_INTSTS_TXOV    (0x1U << UART_INTSTS_TXOVIF_Pos) 
#define UART_INTSTS_RX      (0x1U << UART_INTSTS_RXIF_Pos)
#define UART_INTSTS_Msk    (UART_INTSTS_TXDONE \
                           |UART_INTSTS_RXPE   \
                           |UART_INTSTS_RXOV   \
                           |UART_INTSTS_TXOV   \
                           |UART_INTSTS_RX)
 
/* Private macros ------------------------------------------------------------*/
#define IS_UART_MODE(__MODE__)  (((((__MODE__) & UART_MODE_Msk) != 0U) && (((__MODE__) & ~UART_MODE_Msk) == 0U)))

#define IS_UART_PARITY(__PARITY__)  (((__PARITY__) == UART_PARITY_EVEN) ||\
                                     ((__PARITY__) == UART_PARITY_ODD)  ||\
                                     ((__PARITY__) == UART_PARITY_0)    ||\
                                     ((__PARITY__) == UART_PARITY_1)    ||\
                                     ((__PARITY__) == UART_PARITY_NONE))

#define IS_UART_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == UART_FIRSTBIT_LSB) ||\
                                         ((__FIRSTBIT__) == UART_FIRSTBIT_MSB))

#define IS_UART_BAUDRATE(__BAUDRATE__) ((300UL <= (__BAUDRATE__)) &&\
                                      ((__BAUDRATE__) <= 819200UL))

#define IS_UART_FLAGR(__FLAGR__)  (((__FLAGR__) == UART_FLAG_DMATXDONE)   ||\
                                   ((__FLAGR__) == UART_FLAG_RXPARITY)    ||\
                                   ((__FLAGR__) == UART_FLAG_TXDONE)      ||\
                                   ((__FLAGR__) == UART_FLAG_RXPE)        ||\
                                   ((__FLAGR__) == UART_FLAG_RXOV)        ||\
                                   ((__FLAGR__) == UART_FLAG_TXOV)        ||\
                                   ((__FLAGR__) == UART_FLAG_RXFULL))

#define IS_UART_FLAGC(__FLAGC__)  ((((__FLAGC__) & UART_FLAG_RCMsk) != 0U) &&\
                                   (((__FLAGC__) & ~UART_FLAG_RCMsk) == 0U))

#define IS_UART_INT(__INT__)  ((((__INT__) & UART_INT_Msk) != 0U) &&\
                               (((__INT__) & ~UART_INT_Msk) == 0U))

#define IS_UART_INTFLAGR(__INTFLAGR__)  (((__INTFLAGR__) == UART_INTSTS_TXDONE) ||\
                                         ((__INTFLAGR__) == UART_INTSTS_RXPE) ||\
                                         ((__INTFLAGR__) == UART_INTSTS_RXOV) ||\
                                         ((__INTFLAGR__) == UART_INTSTS_TXOV) ||\
                                         ((__INTFLAGR__) == UART_INTSTS_RX))

#define IS_UART_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & UART_INTSTS_Msk) != 0U) &&\
                                         (((__INTFLAGC__) & ~UART_INTSTS_Msk) == 0U))

/****************************** UART Instances ********************************/
#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART0) || \
                                        ((INSTANCE) == UART1) || \
                                        ((INSTANCE) == UART2) || \
                                        ((INSTANCE) == UART3) || \
                                        ((INSTANCE) == UART4) || \
                                        ((INSTANCE) == UART5))

/* Exported Functions ------------------------------------------------------- */
/* UART Exported Functions Group1: 
                                   Initialization and functions --------------*/
void UART_DeInit(UART_Type *UARTx);
void UART_Init(UART_Type *UARTx, UART_InitType *InitStruct);
void UART_StructInit(UART_InitType *InitStruct);
/* UART Exported Functions Group2: 
                                   (Interrupt) Flag --------------------------*/
uint8_t UART_GetFlag(UART_Type *UARTx, uint32_t FlagMask);
void UART_ClearFlag(UART_Type *UARTx, uint32_t FlagMask);
void UART_INTConfig(UART_Type *UARTx, uint32_t INTMask, uint8_t NewState);
uint8_t UART_GetINTStatus(UART_Type *UARTx, uint32_t INTMask);
void UART_ClearINTStatus(UART_Type *UARTx, uint32_t INTMask);
/* UART Exported Functions Group3: 
                                   Transfer datas ----------------------------*/
void UART_SendData(UART_Type *UARTx, uint8_t ch);
uint8_t UART_ReceiveData(UART_Type *UARTx);
/* UART Exported Functions Group4: 
                                   MISC Configuration ------------------------*/
void UART_BaudrateConfig(UART_Type *UARTx, uint32_t BaudRate);
void UART_Cmd(UART_Type *UARTx, uint32_t Mode, uint32_t NewState);
void UART_GetConfigINFO(UART_Type *UARTx, UART_ConfigINFOType *ConfigInfo);
                            
                                     
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_UART_H */

/*********************************** END OF FILE ******************************/
