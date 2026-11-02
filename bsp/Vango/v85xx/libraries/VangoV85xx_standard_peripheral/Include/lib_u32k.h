/**
  ******************************************************************************
  * @file    lib_u32k.h 
  * @author  Application Team
  * @version V4.5.0
  * @date    2019-05-14
  * @brief   UART 32K library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_U32K_H
#define __LIB_U32K_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
typedef struct
{
  uint32_t Debsel;
  uint32_t Parity;
  uint32_t WordLen;
  uint32_t FirstBit;
  uint32_t AutoCal;
  uint32_t Baudrate;
  uint32_t LineSel;
} U32K_InitType;
//Debsel
#define U32K_DEBSEL_0   U32K_CTRL0_DEBSEL_0
#define U32K_DEBSEL_1   U32K_CTRL0_DEBSEL_1
#define U32K_DEBSEL_2   U32K_CTRL0_DEBSEL_2
#define U32K_DEBSEL_3   U32K_CTRL0_DEBSEL_3
//Parity
#define U32K_PARITY_EVEN    U32K_CTRL0_PMODE_EVEN
#define U32K_PARITY_ODD     U32K_CTRL0_PMODE_ODD
#define U32K_PARITY_0       U32K_CTRL0_PMODE_0
#define U32K_PARITY_1       U32K_CTRL0_PMODE_1
#define U32K_PARITY_NONE    0
//WordLen
#define U32K_WORDLEN_8B     0
#define U32K_WORDLEN_9B     U32K_CTRL0_MODE
//FirstBit
#define U32K_FIRSTBIT_LSB   0
#define U32K_FIRSTBIT_MSB   U32K_CTRL0_MSB
//AutoCal
#define U32K_AUTOCAL_ON     0
#define U32K_AUTOCAL_OFF    U32K_CTRL0_ACOFF
//Line
#define U32K_LINE_RX0       U32K_CTRL1_RXSEL_RX0
#define U32K_LINE_RX1       U32K_CTRL1_RXSEL_RX1
#define U32K_LINE_RX2       U32K_CTRL1_RXSEL_RX2
#define U32K_LINE_RX3       U32K_CTRL1_RXSEL_RX3

//INT
#define U32K_INT_RXOV       U32K_CTRL1_RXOVIE
#define U32K_INT_RXPE       U32K_CTRL1_RXPEIE
#define U32K_INT_RX         U32K_CTRL1_RXIE
#define U32K_INT_Msk       (U32K_INT_RXOV \
                           |U32K_INT_RXPE \
                           |U32K_INT_RX)

//INT Status
#define U32K_INTSTS_RXOV       U32K_STS_RXOV
#define U32K_INTSTS_RXPE       U32K_STS_RXPE
#define U32K_INTSTS_RX         U32K_STS_RXIF
#define U32K_INTSTS_Msk       (U32K_INTSTS_RXOV \
                              |U32K_INTSTS_RXPE \
                              |U32K_INTSTS_RX)

//WKUMode
#define U32K_WKUMOD_RX  0                  // Wake-up when receive data
#define U32K_WKUMOD_PC  U32K_CTRL0_WKUMODE // Wake-up when receive data and parity/stop bit correct 
                   
/* Private macros ------------------------------------------------------------*/
#define IS_U32K_DEBSEL(__DEBSEL__)  (((__DEBSEL__) == U32K_DEBSEL_0) ||\
                                     ((__DEBSEL__) == U32K_DEBSEL_1) ||\
                                     ((__DEBSEL__) == U32K_DEBSEL_2) ||\
                                     ((__DEBSEL__) == U32K_DEBSEL_3))

#define IS_U32K_PARITY(__PARITY__)  (((__PARITY__) == U32K_PARITY_EVEN) ||\
                                     ((__PARITY__) == U32K_PARITY_ODD)  ||\
                                     ((__PARITY__) == U32K_PARITY_0)    ||\
                                     ((__PARITY__) == U32K_PARITY_1)    ||\
                                     ((__PARITY__) == U32K_PARITY_NONE))

#define IS_U32K_WORDLEN(__WORDLEN__)  (((__WORDLEN__) == U32K_WORDLEN_8B) || ((__WORDLEN__) == U32K_WORDLEN_9B))
  
#define IS_U32K_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == U32K_FIRSTBIT_LSB) || ((__FIRSTBIT__) == U32K_FIRSTBIT_MSB))

#define IS_U32K_AUTOCAL(__AUTOCAL__)  (((__AUTOCAL__) == U32K_AUTOCAL_ON) || ((__AUTOCAL__) == U32K_AUTOCAL_OFF))

#define IS_U32K_LINE(__LINE__)  (((__LINE__) == U32K_LINE_RX0) ||\
                                 ((__LINE__) == U32K_LINE_RX1) ||\
                                 ((__LINE__) == U32K_LINE_RX2) ||\
                                 ((__LINE__) == U32K_LINE_RX3))

#define IS_U32K_BAUDRATE(__BAUDRATE__)  ((__BAUDRATE__) < 9601UL)

#define IS_U32K_INT(__INT__)  ((((__INT__) & U32K_INT_Msk) != 0U) &&\
                               (((__INT__) & ~U32K_INT_Msk) == 0U))

#define IS_U32K_INTFLAGR(__INTFLAGR__)  (((__INTFLAGR__) == U32K_INTSTS_RXOV) ||\
                                         ((__INTFLAGR__) == U32K_INTSTS_RXPE) ||\
                                         ((__INTFLAGR__) == U32K_INTSTS_RX))

#define IS_U32K_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & U32K_INTSTS_Msk) != 0U) &&\
                                         (((__INTFLAGC__) & ~U32K_INTSTS_Msk) == 0U))

#define IS_U32K_WKUMODE(__WKUMODE__)  (((__WKUMODE__) == U32K_WKUMOD_RX) || ((__WKUMODE__) == U32K_WKUMOD_PC))

/* Exported Functions ------------------------------------------------------- */
/* U32K Exported Functions Group1: 
                                   (De)Initialization  -----------------------*/
void U32K_DeInit(U32K_TypeDef *U32Kx);
void U32K_Init(U32K_TypeDef *U32Kx, U32K_InitType *InitStruct);
void U32K_StructInit(U32K_InitType *InitStruct);
/* U32K Exported Functions Group2: 
                                   Interrupt (flag) configure  ---------------*/
void U32K_INTConfig(U32K_TypeDef *U32Kx, uint32_t INTMask, uint8_t NewState);
uint8_t U32K_GetINTStatus(U32K_TypeDef *U32Kx, uint32_t INTMask);
void U32K_ClearINTStatus(U32K_TypeDef *U32Kx, uint32_t INTMask);
/* U32K Exported Functions Group3: 
                                   Receive datas -----------------------------*/
uint8_t U32K_ReceiveData(U32K_TypeDef *U32Kx);
/* U32K Exported Functions Group4: 
                                   MISC Configuration -------- ---------------*/
void U32K_BaudrateConfig(U32K_TypeDef *U32Kx, uint32_t BaudRate);
void U32K_Cmd(U32K_TypeDef *U32Kx, uint32_t NewState);
void U32K_LineConfig(U32K_TypeDef *U32Kx, uint32_t Line);
void U32K_WKUModeConfig(U32K_TypeDef *U32Kx, uint32_t WKUMode);
                           
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_U32K_H */

/*********************************** END OF FILE ******************************/
