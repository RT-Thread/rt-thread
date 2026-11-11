/**
  ******************************************************************************
  * @file    lib_dma.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   DMA library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_DMA_H
#define __LIB_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
//Channel
#define DMA_CHANNEL_0       0
#define DMA_CHANNEL_1       1
#define DMA_CHANNEL_2       2
#define DMA_CHANNEL_3       3
   
typedef struct
{
  uint32_t DestAddr;          /* destination address */
  uint32_t SrcAddr;           /* source address */
  uint8_t FrameLen;           /* Frame length */
  uint8_t PackLen;            /* Package length */
  uint32_t ContMode;          /* Continuous mode */
  uint32_t TransMode;         /* Transfer mode */  
  uint32_t ReqSrc;            /* DMA request source */
  uint32_t DestAddrMode;      /* Destination address mode */
  uint32_t SrcAddrMode;       /* Source address mode */
  uint32_t TransSize;         /* Transfer size mode */
} DMA_InitType;
//ContMode
#define DMA_CONTMODE_ENABLE     DMA_CTL_CONT
#define DMA_CONTMODE_DISABLE    0
//TransMode
#define DMA_TRANSMODE_SINGLE    0
#define DMA_TRANSMODE_PACK      DMA_CTL_TMODE
//ReqSrc
#define DMA_REQSRC_SOFT             DMA_CTL_DMASEL_SOFT   
#define DMA_REQSRC_UART0TX          DMA_CTL_DMASEL_UART0TX
#define DMA_REQSRC_UART0RX          DMA_CTL_DMASEL_UART0RX
#define DMA_REQSRC_UART1TX          DMA_CTL_DMASEL_UART1TX
#define DMA_REQSRC_UART1RX          DMA_CTL_DMASEL_UART1RX
#define DMA_REQSRC_UART2TX          DMA_CTL_DMASEL_UART2TX
#define DMA_REQSRC_UART2RX          DMA_CTL_DMASEL_UART2RX
#define DMA_REQSRC_UART3TX          DMA_CTL_DMASEL_UART3TX
#define DMA_REQSRC_UART3RX          DMA_CTL_DMASEL_UART3RX
#define DMA_REQSRC_UART4TX          DMA_CTL_DMASEL_UART4TX
#define DMA_REQSRC_UART4RX          DMA_CTL_DMASEL_UART4RX
#define DMA_REQSRC_UART5TX          DMA_CTL_DMASEL_UART5TX
#define DMA_REQSRC_UART5RX          DMA_CTL_DMASEL_UART5RX
#define DMA_REQSRC_ISO78160TX       DMA_CTL_DMASEL_ISO78160TX
#define DMA_REQSRC_ISO78160RX       DMA_CTL_DMASEL_ISO78160RX
#define DMA_REQSRC_ISO78161TX       DMA_CTL_DMASEL_ISO78161TX
#define DMA_REQSRC_ISO78161RX       DMA_CTL_DMASEL_ISO78161RX
#define DMA_REQSRC_TIMER0           DMA_CTL_DMASEL_TIMER0 
#define DMA_REQSRC_TIMER1           DMA_CTL_DMASEL_TIMER1 
#define DMA_REQSRC_TIMER2           DMA_CTL_DMASEL_TIMER2 
#define DMA_REQSRC_TIMER3           DMA_CTL_DMASEL_TIMER3 
#define DMA_REQSRC_SPI1TX           DMA_CTL_DMASEL_SPI1TX  
#define DMA_REQSRC_SPI1RX           DMA_CTL_DMASEL_SPI1RX  
#define DMA_REQSRC_U32K0            DMA_CTL_DMASEL_U32K0  
#define DMA_REQSRC_U32K1            DMA_CTL_DMASEL_U32K1  
#define DMA_REQSRC_CMP1             DMA_CTL_DMASEL_CMP1   
#define DMA_REQSRC_CMP2             DMA_CTL_DMASEL_CMP2
#define DMA_REQSRC_SPI2TX           DMA_CTL_DMASEL_SPI2TX  
#define DMA_REQSRC_SPI2RX           DMA_CTL_DMASEL_SPI2RX 
//DestAddrMode
#define DMA_DESTADDRMODE_FIX        DMA_CxCTL_DMODE_FIX 
#define DMA_DESTADDRMODE_PEND       DMA_CxCTL_DMODE_PEND
#define DMA_DESTADDRMODE_FEND       DMA_CxCTL_DMODE_FEND
//SrcAddrMode
#define DMA_SRCADDRMODE_FIX         DMA_CxCTL_SMODE_FIX 
#define DMA_SRCADDRMODE_PEND        DMA_CxCTL_SMODE_PEND
#define DMA_SRCADDRMODE_FEND        DMA_CxCTL_SMODE_FEND
//TransSize
#define DMA_TRANSSIZE_BYTE          DMA_CxCTL_SIZE_BYTE 
#define DMA_TRANSSIZE_HWORD         DMA_CxCTL_SIZE_HWORD
#define DMA_TRANSSIZE_WORD          DMA_CxCTL_SIZE_WORD 

typedef struct
{
  uint32_t Mode;       /* AES mode */
  uint32_t Direction;  /* Direction */
  uint32_t *KeyStr;    /* AES key */
} DMA_AESInitType;
//AES MODE
#define DMA_AESMODE_128     DMA_AESCTL_MODE_AES128
#define DMA_AESMODE_192     DMA_AESCTL_MODE_AES192
#define DMA_AESMODE_256     DMA_AESCTL_MODE_AES256
//AES Direction
#define DMA_AESDIRECTION_ENCODE         DMA_AESCTL_ENC
#define DMA_AESDIRECTION_DECODE         0

//INT
#define DMA_INT_C3DA        DMA_IE_C3DAIE
#define DMA_INT_C2DA        DMA_IE_C2DAIE
#define DMA_INT_C1DA        DMA_IE_C1DAIE
#define DMA_INT_C0DA        DMA_IE_C0DAIE
#define DMA_INT_C3FE        DMA_IE_C3FEIE
#define DMA_INT_C2FE        DMA_IE_C2FEIE
#define DMA_INT_C1FE        DMA_IE_C1FEIE
#define DMA_INT_C0FE        DMA_IE_C0FEIE
#define DMA_INT_C3PE        DMA_IE_C3PEIE
#define DMA_INT_C2PE        DMA_IE_C2PEIE
#define DMA_INT_C1PE        DMA_IE_C1PEIE
#define DMA_INT_C0PE        DMA_IE_C0PEIE
#define DMA_INT_Msk        (0xFFFUL)

//INTSTS
#define DMA_INTSTS_C3DA         DMA_STS_C3DA   
#define DMA_INTSTS_C2DA         DMA_STS_C2DA   
#define DMA_INTSTS_C1DA         DMA_STS_C1DA   
#define DMA_INTSTS_C0DA         DMA_STS_C0DA   
#define DMA_INTSTS_C3FE         DMA_STS_C3FE   
#define DMA_INTSTS_C2FE         DMA_STS_C2FE   
#define DMA_INTSTS_C1FE         DMA_STS_C1FE   
#define DMA_INTSTS_C0FE         DMA_STS_C0FE   
#define DMA_INTSTS_C3PE         DMA_STS_C3PE   
#define DMA_INTSTS_C2PE         DMA_STS_C2PE   
#define DMA_INTSTS_C1PE         DMA_STS_C1PE   
#define DMA_INTSTS_C0PE         DMA_STS_C0PE   
#define DMA_INTSTS_C3BUSY       DMA_STS_C3BUSY 
#define DMA_INTSTS_C2BUSY       DMA_STS_C2BUSY 
#define DMA_INTSTS_C1BUSY       DMA_STS_C1BUSY 
#define DMA_INTSTS_C0BUSY       DMA_STS_C0BUSY
#define DMA_INTSTS_Msk         (0xFFF0UL)

/* Private macros ------------------------------------------------------------*/
#define IS_DMA_CHANNEL(__CH__)  (((__CH__) == DMA_CHANNEL_0) ||\
                                 ((__CH__) == DMA_CHANNEL_1) ||\
                                 ((__CH__) == DMA_CHANNEL_2) ||\
                                 ((__CH__) == DMA_CHANNEL_3))

#define IS_DMA_ALIGNEDADDR_WORD(__ADDRW__)  (((__ADDRW__) & 0x3U) == 0U)

#define IS_DMA_ALIGNEDADDR_HWORD(__ADDRHW__)  (((__ADDRHW__) & 0x1U) == 0U)

#define IS_DMA_CONTMOD(__CONTMOD__)  (((__CONTMOD__) == DMA_CONTMODE_ENABLE) ||\
                                      ((__CONTMOD__) == DMA_CONTMODE_DISABLE))

#define IS_DMA_TRANSMOD(__TRANSMOD__)  (((__TRANSMOD__) == DMA_TRANSMODE_SINGLE) ||\
                                        ((__TRANSMOD__) == DMA_TRANSMODE_PACK))

#define IS_DMA_REQSRC(__REQSRC__)  (((__REQSRC__) == DMA_REQSRC_SOFT)       ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART0TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART0RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART1TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART1RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART2TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART2RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART3TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART3RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART4TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART4RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART5TX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_UART5RX)    ||\
                                    ((__REQSRC__) == DMA_REQSRC_ISO78160TX) ||\
                                    ((__REQSRC__) == DMA_REQSRC_ISO78160RX) ||\
                                    ((__REQSRC__) == DMA_REQSRC_ISO78161TX) ||\
                                    ((__REQSRC__) == DMA_REQSRC_ISO78161RX) ||\
                                    ((__REQSRC__) == DMA_REQSRC_TIMER0)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_TIMER1)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_TIMER2)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_TIMER3)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI1TX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI1RX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_U32K0)      ||\
                                    ((__REQSRC__) == DMA_REQSRC_U32K1)      ||\
                                    ((__REQSRC__) == DMA_REQSRC_CMP1)       ||\
                                    ((__REQSRC__) == DMA_REQSRC_CMP2)       ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI2TX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI2RX))

#define IS_DMA_DESTADDRMOD(__DAM__)  (((__DAM__) == DMA_DESTADDRMODE_FIX)  ||\
                                      ((__DAM__) == DMA_DESTADDRMODE_PEND) ||\
                                      ((__DAM__) == DMA_DESTADDRMODE_FEND))

#define IS_DMA_SRCADDRMOD(__SAM__)  (((__SAM__) == DMA_SRCADDRMODE_FIX)  ||\
                                     ((__SAM__) == DMA_SRCADDRMODE_PEND) ||\
                                     ((__SAM__) == DMA_SRCADDRMODE_FEND))

#define IS_DMA_TRANSSIZE(__TSIZE__)  (((__TSIZE__) == DMA_TRANSSIZE_BYTE)  ||\
                                      ((__TSIZE__) == DMA_TRANSSIZE_HWORD) ||\
                                      ((__TSIZE__) == DMA_TRANSSIZE_WORD))

#define IS_DMA_AESMOD(__AESMOD__)  (((__AESMOD__) == DMA_AESMODE_128) ||\
                                    ((__AESMOD__) == DMA_AESMODE_192) ||\
                                    ((__AESMOD__) == DMA_AESMODE_256))

#define IS_DMA_AESDIR(__AESDIR__)  (((__AESDIR__) == DMA_AESDIRECTION_ENCODE) ||\
                                    ((__AESDIR__) == DMA_AESDIRECTION_DECODE))

#define IS_DMA_INT(__INT__)  ((((__INT__) & DMA_INT_Msk) != 0U) &&\
                              (((__INT__) & ~DMA_INT_Msk) == 0U))

#define IS_DMA_INTFLAGR(__INTFLAGR__)  (((__INTFLAGR__) == DMA_INTSTS_C3DA) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C2DA) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C1DA) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C0DA) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C3FE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C2FE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C1FE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C0FE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C3PE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C2PE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C1PE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C0PE) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C3BUSY) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C2BUSY) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C1BUSY) ||\
                                        ((__INTFLAGR__) == DMA_INTSTS_C0BUSY))

#define IS_DMA_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & DMA_INTSTS_Msk) != 0U) &&\
                                        (((__INTFLAGC__) & ~DMA_INTSTS_Msk) == 0U))

/* Exported Functions ------------------------------------------------------- */
/* DMA Exported Functions Group1: 
                                   (De)Initialization ------------------------*/
void DMA_DeInit(uint32_t Channel);
void DMA_Init(DMA_InitType *InitStruct, uint32_t Channel);
void DMA_AESDeInit(void);
void DMA_AESInit(DMA_AESInitType *InitStruct);
/* DMA Exported Functions Group2: 
                                   Interrupt (flag) --------------------------*/
void DMA_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t DMA_GetINTStatus(uint32_t INTMask);
void DMA_ClearINTStatus(uint32_t INTMask);
/* DMA Exported Functions Group3:
                                   MISC Configuration ------------------------*/
void DMA_Cmd(uint32_t Channel, uint32_t NewState);
void DMA_AESCmd(uint32_t NewState);
void DMA_StopTransmit(uint32_t Channel, uint32_t NewState);
uint8_t DMA_GetFrameLenTransferred(uint32_t Channel);
uint8_t DMA_GetPackLenTransferred(uint32_t Channel);


#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_DMA_H */

/*********************************** END OF FILE ******************************/
