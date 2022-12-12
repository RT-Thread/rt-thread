/**
  ******************************************************************************
  * @file    lib_uart.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
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
  uint32_t WordLen;
  uint32_t FirstBit;
  uint32_t Baudrate;
} UART_InitType;
//Mode
#define UART_MODE_RX   UART_CTRL_RXEN
#define UART_MODE_TX   UART_CTRL_TXEN
#define UART_MODE_OFF  0
#define UART_MODE_Msk  (UART_CTRL_RXEN | UART_CTRL_TXEN)
//Parity
#define UART_PARITY_EVEN    UART_CTRL2_PMODE_EVEN
#define UART_PARITY_ODD     UART_CTRL2_PMODE_ODD
#define UART_PARITY_0       UART_CTRL2_PMODE_0
#define UART_PARITY_1       UART_CTRL2_PMODE_1
#define UART_PARITY_NONE    0
//WordLen
#define UART_WORDLEN_8B     0
#define UART_WORDLEN_9B     UART_CTRL2_MODE
//FirstBit
#define UART_FIRSTBIT_LSB   0
#define UART_FIRSTBIT_MSB   UART_CTRL2_MSB

//UART Configration Information struct
typedef struct 
{
  uint32_t Mode_Transmit  :1; //1: TX Enable; 0: TX Disable
  uint32_t Mode_Receive   :1; //1: RX Enable; 0: RX Disable
  uint32_t Baudrate;          //The value of current budrate
  uint8_t  Parity;            //0: parity bit=0; 1: parity bit=1; 2: Even parity; 3:Odd parity
  uint8_t  WordLen;           //8: data bits=8; 9: data bits=9
  uint8_t  FirstBit;          //0: LSB transmit first; 1: MSB transmit first
} UART_ConfigINFOType;

//status
#define UART_FLAG_RXPARITY    UART_STATE_RXPSTS
#define UART_FLAG_TXDONE      UART_STATE_TXDONE
#define UART_FLAG_RXPE        UART_STATE_RXPE
#define UART_FLAG_RXOV        UART_STATE_RXOV
#define UART_FLAG_TXOV        UART_STATE_TXOV
#define UART_FLAG_RXFULL      UART_STATE_RXFULL
#define UART_FLAG_RCMsk      (UART_FLAG_TXDONE \
                             |UART_FLAG_RXPE   \
                             |UART_FLAG_RXOV   \
                             |UART_STATE_RXFULL\
                             |UART_FLAG_TXOV)

//interrupt
#define UART_INT_TXDONE     UART_CTRL_TXDONEIE
#define UART_INT_RXPE       UART_CTRL_RXPEIE
#define UART_INT_RXOV       UART_CTRL_RXOVIE
#define UART_INT_TXOV       UART_CTRL_TXOVIE
#define UART_INT_RX         UART_CTRL_RXIE
#define UART_INT_Msk       (UART_INT_TXDONE \
                           |UART_INT_RXPE   \
                           |UART_INT_RXOV   \
                           |UART_INT_TXOV   \
                           |UART_INT_RX)

//INTStatus
#define UART_INTSTS_TXDONE  UART_INTSTS_TXDONEIF
#define UART_INTSTS_RXPE    UART_INTSTS_RXPEIF  
#define UART_INTSTS_RXOV    UART_INTSTS_RXOVIF  
#define UART_INTSTS_TXOV    UART_INTSTS_TXOVIF  
#define UART_INTSTS_RX      UART_INTSTS_RXIF    
#define UART_INTSTS_Msk    (UART_INTSTS_TXDONE \
                           |UART_INTSTS_RXPE   \
                           |UART_INTSTS_RXOV   \
                           |UART_INTSTS_TXOV   \
                           |UART_INTSTS_RX)
 
/* Private macros ------------------------------------------------------------*/
#define IS_UART_MODE(__MODE__)  (((((__MODE__) & UART_MODE_Msk) != 0U) && (((__MODE__) & ~UART_MODE_Msk) == 0U)) ||\
                                 ((__MODE__) == UART_MODE_OFF))

#define IS_UART_PARITY(__PARITY__)  (((__PARITY__) == UART_PARITY_EVEN) ||\
                                     ((__PARITY__) == UART_PARITY_ODD)  ||\
                                     ((__PARITY__) == UART_PARITY_0)    ||\
                                     ((__PARITY__) == UART_PARITY_1)    ||\
                                     ((__PARITY__) == UART_PARITY_NONE))

#define IS_UART_WORDLEN(__WORDLEN__)  (((__WORDLEN__) == UART_WORDLEN_8B) ||\
                                       ((__WORDLEN__) == UART_WORDLEN_9B))

#define IS_UART_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == UART_FIRSTBIT_LSB) ||\
                                         ((__FIRSTBIT__) == UART_FIRSTBIT_MSB))

#define IS_UART_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 0x100000UL)

#define IS_UART_FLAGR(__FLAGR__)  (((__FLAGR__) == UART_FLAG_RXPARITY) ||\
                                   ((__FLAGR__) == UART_FLAG_TXDONE)   ||\
                                   ((__FLAGR__) == UART_FLAG_RXPE)     ||\
                                   ((__FLAGR__) == UART_FLAG_RXOV)     ||\
                                   ((__FLAGR__) == UART_FLAG_TXOV)     ||\
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

/* Exported Functions ------------------------------------------------------- */
/* UART Exported Functions Group1: 
                                   Initialization and functions --------------*/
void UART_DeInit(UART_TypeDef *UARTx);
void UART_Init(UART_TypeDef *UARTx, UART_InitType *InitStruct);
void UART_StructInit(UART_InitType *InitStruct);
/* UART Exported Functions Group2: 
                                   (Interrupt) Flag --------------------------*/
uint8_t UART_GetFlag(UART_TypeDef *UARTx, uint32_t FlagMask);
void UART_ClearFlag(UART_TypeDef *UARTx, uint32_t FlagMask);
void UART_INTConfig(UART_TypeDef *UARTx, uint32_t INTMask, uint8_t NewState);
uint8_t UART_GetINTStatus(UART_TypeDef *UARTx, uint32_t INTMask);
void UART_ClearINTStatus(UART_TypeDef *UARTx, uint32_t INTMask);
/* UART Exported Functions Group3: 
                                   Transfer datas ----------------------------*/
void UART_SendData(UART_TypeDef *UARTx, uint8_t ch);
uint8_t UART_ReceiveData(UART_TypeDef *UARTx);
/* UART Exported Functions Group4: 
                                   MISC Configuration ------------------------*/
void UART_BaudrateConfig(UART_TypeDef *UARTx, uint32_t BaudRate);
void UART_Cmd(UART_TypeDef *UARTx, uint32_t Mode, uint32_t NewState);
void UART_GetConfigINFO(UART_TypeDef *UARTx, UART_ConfigINFOType *ConfigInfo);
                            
                                     
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_UART_H */

/*********************************** END OF FILE ******************************/
