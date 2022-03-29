/**
  ******************************************************************************
  * @file    lib_iso7816.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
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
  uint32_t Parity;
  uint32_t Baudrate;
  uint32_t TXRetry;
  uint32_t RXACKLength;
  uint32_t TXNACKLength;
} ISO7816_InitType;
//FirstBit
#define ISO7816_FIRSTBIT_MSB   (0UL)
#define ISO7816_FIRSTBIT_LSB    ISO7816_CFG_LSB
#define IS_ISO7816_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == ISO7816_FIRSTBIT_MSB) ||\
                                            ((__FIRSTBIT__) == ISO7816_FIRSTBIT_LSB))
//Parity
#define ISO7816_PARITY_EVEN    (0UL)
#define ISO7816_PARITY_ODD      ISO7816_CFG_CHKP
#define IS_ISO7816_PARITY(__PARITY__)  (((__PARITY__) == ISO7816_PARITY_EVEN) ||\
                                        ((__PARITY__) == ISO7816_PARITY_ODD))
//Baudrate
#define IS_ISO7816_BAUDRATE(__BAUDRATE__) ((200UL <= (__BAUDRATE__)) &&\
                                          ((__BAUDRATE__) <= 2625000UL))
//TXRetry
#define ISO7816_TXRTY_0            ((0x00U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_1            ((0x01U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_2            ((0x02U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_3            ((0x03U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_4            ((0x04U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_5            ((0x05U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_6            ((0x06U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_7            ((0x07U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_8            ((0x08U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_9            ((0x09U << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_10           ((0x0AU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_11           ((0x0BU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_12           ((0x0CU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_13           ((0x0DU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_14           ((0x0EU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define ISO7816_TXRTY_15           ((0x0FU << ISO7816_CFG_TXRTYCNT_Pos) \
                                   | (1U << 10))
#define IS_ISO7816_TXRTY(__TXRTY__)          (((__TXRTY__) == ISO7816_TXRTY_0)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_1)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_2)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_3)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_4)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_5)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_6)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_7)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_8)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_9)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_10)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_11)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_12)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_13)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_14)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_15))
//RXACKLength
#define ISO7816_RXACKLEN_2    (0UL)
#define ISO7816_RXACKLEN_1    (ISO7816_CFG_RXACKSET)
#define IS_ISO7816_RXACKLEN(__RXACKLEN__)  (((__RXACKLEN__) == ISO7816_RXACKLEN_2) ||\
                                            ((__RXACKLEN__) == ISO7816_RXACKLEN_1))
//TXNACKLength
#define ISO7816_TXNACKLEN_0  (0UL)
#define ISO7816_TXNACKLEN_1  (ISO7816_CFG_AUTORXACK)
#define ISO7816_TXNACKLEN_2  (ISO7816_CFG_AUTORXACK | ISO7816_CFG_ACKLEN)
#define IS_ISO7816_TXNACKLEN(__TXNACKLEN__)  (((__TXNACKLEN__) == ISO7816_TXNACKLEN_0) ||\
                                              ((__TXNACKLEN__) == ISO7816_TXNACKLEN_1) ||\
                                              ((__TXNACKLEN__) == ISO7816_TXNACKLEN_2))

#define IS_ISO7816_PRESCALER(__PRESCALER__)  ((__PRESCALER__) <= 0x80)

//interrupt
#define ISO7816_INT_TXRTYERR    ISO7816_CFG_TXRTYERRIE
#define ISO7816_INT_RXOV        ISO7816_CFG_RXOVIE
#define ISO7816_INT_TXDONE      ISO7816_CFG_TXDONEIE
#define ISO7816_INT_RX          ISO7816_CFG_RXIE
#define ISO7816_INT_RXERR       ISO7816_CFG_RXERRIE
#define ISO7816_INT_Msk         (ISO7816_INT_TXRTYERR  \
                                |ISO7816_INT_RXOV      \
                                |ISO7816_INT_TXDONE    \
                                |ISO7816_INT_RX        \
                                |ISO7816_INT_RXERR)
#define IS_ISO7816_INT(__INT__)  ((((__INT__) & ISO7816_INT_Msk) != 0U) &&\
                                  (((__INT__) & ~ISO7816_INT_Msk) == 0U))   

//INTStatus
#define ISO7816_INTSTS_TXRTYERR ISO7816_INFO_TXRTYERRIF
#define ISO7816_INTSTS_RXOV     ISO7816_INFO_RXOVIF
#define ISO7816_INTSTS_TXDONE   ISO7816_INFO_TXDONEIF
#define ISO7816_INTSTS_RX       ISO7816_INFO_RXIF
#define ISO7816_INTSTS_RXERR    ISO7816_INFO_RXERRIF
#define ISO7816_INTSTS_Msk     (ISO7816_INTSTS_TXRTYERR \
                               |ISO7816_INTSTS_RXOV     \
                               |ISO7816_INTSTS_TXDONE   \
                               |ISO7816_INTSTS_RX       \
                               |ISO7816_INTSTS_RXERR)
#define IS_ISO7816_INTFLAGR(__INTFLAG__)  (((__INTFLAG__) == ISO7816_INTSTS_TXRTYERR) ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_RXOV)     ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_TXDONE)   ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_RX)       ||\
                                           ((__INTFLAG__) == ISO7816_INTSTS_RXERR))

#define IS_ISO7816_INTFLAGC(__INTFLAG__)  ((((__INTFLAG__)&ISO7816_INTSTS_Msk) != 0U) &&\
                                           (((__INTFLAG__)&(~ISO7816_INTSTS_Msk)) == 0U))
//status
#define ISO7816_FLAG_DMATXDONE      ISO7816_INFO_DMATXDONE
#define IS_ISO7816_FLAGR(__FLAG__)  ((__FLAG__) == ISO7816_FLAG_DMATXDONE)
#define IS_ISO7816_FLAGC(__FLAG__)  ((__FLAG__) == ISO7816_FLAG_DMATXDONE)

/****************************** ISO7816 Instances *****************************/
#define IS_ISO7816_ALL_INSTANCE(INSTANCE) (((INSTANCE) == ISO78160) || \
                                           ((INSTANCE) == ISO78161))

/* Exported Functions ------------------------------------------------------- */
void ISO7816_DeInit(ISO7816_Type *ISO7816x);
void ISO7816_StructInit(ISO7816_InitType *InitStruct);
void ISO7816_Init(ISO7816_Type *ISO7816x, ISO7816_InitType *Init_Struct);
void ISO7816_Cmd(ISO7816_Type *ISO7816x, uint32_t NewState);
void ISO7816_BaudrateConfig(ISO7816_Type *ISO7816x, uint32_t BaudRate);
void ISO7816_CLKDIVConfig(ISO7816_Type *ISO7816x, uint32_t Prescaler);
void ISO7816_CLKOutputCmd(ISO7816_Type *ISO7816x, uint32_t NewState);
void ISO7816_SendData(ISO7816_Type *ISO7816x, uint8_t ch);
uint8_t ISO7816_ReceiveData(ISO7816_Type *ISO7816x);
void ISO7816_INTConfig(ISO7816_Type *ISO7816x, uint32_t INTMask, uint8_t NewState);
uint8_t ISO7816_GetINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask);
void ISO7816_ClearINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask);
uint8_t ISO7816_GetFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask);
void ISO7816_ClearFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask);
uint8_t ISO7816_GetLastTransmitACK(ISO7816_Type *ISO7816x);
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_Type *ISO7816x);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_ISO7816_H */

/*********************************** END OF FILE ******************************/
