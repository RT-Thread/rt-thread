/**
  ******************************************************************************
  * @file    lib_iso7816.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   ISO7816 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_ISO7816_H
#define __LIB_ISO7816_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

typedef struct
{
  uint32_t FirstBit;
  uint32_t ACKLen;
  uint32_t Parity;
  uint32_t Baudrate;
} ISO7816_InitType;

//FirstBit
#define ISO7816_FIRSTBIT_LSB    ISO7816_INFO_LSB
#define ISO7816_FIRSTBIT_MSB    0
#define IS_ISO7816_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == ISO7816_FIRSTBIT_LSB) ||\
                                            ((__FIRSTBIT__) == ISO7816_FIRSTBIT_MSB))
//ACKLen
#define ISO7816_ACKLEN_1        0
#define ISO7816_ACKLEN_2        ISO7816_CFG_ACKLEN
#define IS_ISO7816_ACKLEN(__ACKLEN__)  (((__ACKLEN__) == ISO7816_ACKLEN_1) ||\
                                        ((__ACKLEN__) == ISO7816_ACKLEN_2))
//Parity
#define ISO7816_PARITY_EVEN     0
#define ISO7816_PARITY_ODD      ISO7816_CFG_CHKP
#define IS_ISO7816_PARITY(__PARITY__)  (((__PARITY__) == ISO7816_PARITY_EVEN) || ((__PARITY__) == ISO7816_PARITY_ODD))

#define IS_ISO7816_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) > 299UL)
#define IS_ISO7816_PRESCALER(__PRESCALER__)  (((__PRESCALER__) <= 0x80) && ((__PRESCALER__) > 0U))

//interrupt
#define ISO7816_INT_RXOV        ISO7816_CFG_OVIE
#define ISO7816_INT_TX          ISO7816_CFG_SDIE
#define ISO7816_INT_RX          ISO7816_CFG_RCIE
#define ISO7816_INT_Msk         (ISO7816_INT_RXOV \
                                |ISO7816_INT_TX   \
                                |ISO7816_INT_RX)
#define IS_ISO7816_INT(__INT__)  ((((__INT__) & ISO7816_INT_Msk) != 0U) &&\
                                  (((__INT__) & ~ISO7816_INT_Msk) == 0U))   
                            
//INTStatus
#define ISO7816_INTSTS_RXOV     ISO7816_INFO_OVIF
#define ISO7816_INTSTS_TX       ISO7816_INFO_SDIF
#define ISO7816_INTSTS_RX       ISO7816_INFO_RCIF
#define ISO7816_INTSTS_Msk      (ISO7816_INTSTS_RXOV \
                                 |ISO7816_INTSTS_TX  \
                                 |ISO7816_INTSTS_RX)
#define IS_ISO7816_INTFLAGR(__INTFLAG__)  (((__INTFLAG__) == ISO7816_INTSTS_RXOV)   ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_TX)     ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_RX))                        

#define IS_ISO7816_INTFLAGC(__INTFLAG__)  ((((__INTFLAG__)&ISO7816_INTSTS_Msk) != 0U) &&\
                                           (((__INTFLAG__)&(~ISO7816_INTSTS_Msk)) == 0U))
//status
#define ISO7816_FLAG_SDERR      ISO7816_INFO_SDERR
#define ISO7816_FLAG_RCERR      ISO7816_INFO_RCERR
#define ISO7816_FLAG_Msk        (ISO7816_FLAG_SDERR|ISO7816_FLAG_RCERR)
#define IS_ISO7816_FLAGR(__FLAG__)  (((__FLAG__) == ISO7816_FLAG_SDERR) || ((__FLAG__) == ISO7816_FLAG_RCERR))
#define IS_ISO7816_FLAGC(__FLAG__)  ((((__FLAG__) & ISO7816_FLAG_Msk) != 0U) &&\
                                     (((__FLAG__) & (~ISO7816_FLAG_Msk)) == 0U))

/* Exported Functions ------------------------------------------------------- */
void ISO7816_DeInit(ISO7816_TypeDef *ISO7816x);
void ISO7816_StructInit(ISO7816_InitType *InitStruct);
void ISO7816_Init(ISO7816_TypeDef *ISO7816x, ISO7816_InitType *Init_Struct);
void ISO7816_Cmd(ISO7816_TypeDef *ISO7816x, uint32_t NewState);
void ISO7816_BaudrateConfig(ISO7816_TypeDef *ISO7816x, uint32_t BaudRate);
void ISO7816_CLKDIVConfig(ISO7816_TypeDef *ISO7816x, uint32_t Prescaler);
void ISO7816_CLKOutputCmd(ISO7816_TypeDef *ISO7816x, uint32_t NewState);
void ISO7816_SendData(ISO7816_TypeDef *ISO7816x, uint8_t ch);
uint8_t ISO7816_ReceiveData(ISO7816_TypeDef *ISO7816x);
void ISO7816_INTConfig(ISO7816_TypeDef *ISO7816x, uint32_t INTMask, uint8_t NewState);
uint8_t ISO7816_GetINTStatus(ISO7816_TypeDef *ISO7816x, uint32_t INTMask);
void ISO7816_ClearINTStatus(ISO7816_TypeDef *ISO7816x, uint32_t INTMask);
uint8_t ISO7816_GetFlag(ISO7816_TypeDef *ISO7816x, uint32_t FlagMask);
void ISO7816_ClearFlag(ISO7816_TypeDef *ISO7816x, uint32_t FlagMask);
uint8_t ISO7816_GetLastTransmitACK(ISO7816_TypeDef *ISO7816x);
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_TypeDef *ISO7816x);


#ifdef __cplusplus
}
#endif

#endif /* __LIB_ISO7816_H */

/*********************************** END OF FILE ******************************/
