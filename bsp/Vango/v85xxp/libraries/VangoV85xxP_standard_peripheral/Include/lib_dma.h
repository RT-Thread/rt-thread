/**
  ******************************************************************************
  * @file    lib_dma.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
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
#define DMA_CHANNEL_0       (0)
#define DMA_CHANNEL_1       (1)
#define DMA_CHANNEL_2       (2)
#define DMA_CHANNEL_3       (3)
   
typedef struct
{
  uint32_t DestAddr;          /* destination address */
  uint32_t SrcAddr;           /* source address */
  uint8_t  FrameLen;          /* Frame length */
  uint8_t  PackLen;           /* Package length */
  uint32_t ContMode;          /* Continuous mode */
  uint32_t TransMode;         /* Transfer mode */  
  uint32_t ReqSrc;            /* DMA request source */
  uint32_t DestAddrMode;      /* Destination address mode */
  uint32_t SrcAddrMode;       /* Source address mode */
  uint32_t TransSize;         /* Transfer size mode */
} DMA_InitType;

/**************  Bits definition for DMA_CxCTL register      ******************/



/**************  Bits definition for DMA_AESCTL register     ******************/
/****************************** DMA Instances *********************************/
#define IS_DMA_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DMA)

//ContMode
#define DMA_CONTMODE_ENABLE     DMA_CCTL_CONT
#define DMA_CONTMODE_DISABLE    0
#define IS_DMA_CONTMOD(__CONTMOD__)  (((__CONTMOD__) == DMA_CONTMODE_ENABLE) ||\
                                      ((__CONTMOD__) == DMA_CONTMODE_DISABLE))

//TransMode
#define DMA_TRANSMODE_SINGLE    0
#define DMA_TRANSMODE_PACK      DMA_CCTL_TMODE
#define IS_DMA_TRANSMOD(__TRANSMOD__)  (((__TRANSMOD__) == DMA_TRANSMODE_SINGLE) ||\
                                        ((__TRANSMOD__) == DMA_TRANSMODE_PACK))

//ReqSrc
#define DMA_REQSRC_SOFT           (0x0U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000000 */
#define DMA_REQSRC_ADC            (0x1U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000080 */
#define DMA_REQSRC_UART0TX        (0x2U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000100 */
#define DMA_REQSRC_UART0RX        (0x3U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000180 */
#define DMA_REQSRC_UART1TX        (0x4U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000200 */
#define DMA_REQSRC_UART1RX        (0x5U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000280 */
#define DMA_REQSRC_UART2TX        (0x6U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000300 */
#define DMA_REQSRC_UART2RX        (0x7U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000380 */
#define DMA_REQSRC_UART3TX        (0x8U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000400 */
#define DMA_REQSRC_UART3RX        (0x9U << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000480 */
#define DMA_REQSRC_UART4TX        (0xAU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000500 */
#define DMA_REQSRC_UART4RX        (0xBU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000580 */
#define DMA_REQSRC_UART5TX        (0xCU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000600 */
#define DMA_REQSRC_UART5RX        (0xDU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000680 */
#define DMA_REQSRC_ISO78160TX     (0xEU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000700 */
#define DMA_REQSRC_ISO78160RX     (0xFU << DMA_CCTL_DMASEL_Pos)             /*!< 0x00000780 */
#define DMA_REQSRC_ISO78161TX     (0x10U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000800 */
#define DMA_REQSRC_ISO78161RX     (0x11U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000880 */
#define DMA_REQSRC_TIMER0         (0x12U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000900 */
#define DMA_REQSRC_TIMER1         (0x13U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000980 */
#define DMA_REQSRC_TIMER2         (0x14U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000A00 */
#define DMA_REQSRC_TIMER3         (0x15U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000A80 */
#define DMA_REQSRC_SPI1TX         (0x16U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000B00 */
#define DMA_REQSRC_SPI1RX         (0x17U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000B80 */
#define DMA_REQSRC_U32K0          (0x18U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000C00 */
#define DMA_REQSRC_U32K1          (0x19U << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000C80 */
#define DMA_REQSRC_CMP1           (0x1AU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000D00 */
#define DMA_REQSRC_CMP2           (0x1BU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000D80 */
#define DMA_REQSRC_SPI3TX         (0x1CU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000E00 */
#define DMA_REQSRC_SPI3RX         (0x1DU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000E80 */
#define DMA_REQSRC_SPI2TX         (0x1EU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000F00 */
#define DMA_REQSRC_SPI2RX         (0x1FU << DMA_CCTL_DMASEL_Pos)            /*!< 0x00000F80 */

#define IS_DMA_REQSRC(__REQSRC__)  (((__REQSRC__) == DMA_REQSRC_SOFT)       ||\
                                    ((__REQSRC__) == DMA_REQSRC_ADC)        ||\
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
                                    ((__REQSRC__) == DMA_REQSRC_SPI3TX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI3RX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI2TX)     ||\
                                    ((__REQSRC__) == DMA_REQSRC_SPI2RX))


//DestAddrMode
#define DMA_DESTADDRMODE_FIX          (0x0U << DMA_CCTL_DMODE_Pos)            /*!< 0x00000000 */
#define DMA_DESTADDRMODE_PEND         (0x1U << DMA_CCTL_DMODE_Pos)            /*!< 0x00000020 */
#define DMA_DESTADDRMODE_FEND         (0x2U << DMA_CCTL_DMODE_Pos)            /*!< 0x00000040 */
#define IS_DMA_DESTADDRMOD(__DAM__)  (((__DAM__) == DMA_DESTADDRMODE_FIX)  ||\
                                      ((__DAM__) == DMA_DESTADDRMODE_PEND) ||\
                                      ((__DAM__) == DMA_DESTADDRMODE_FEND))

//SrcAddrMode
#define DMA_SRCADDRMODE_FIX          (0x0U << DMA_CCTL_SMODE_Pos)            /*!< 0x00000000 */
#define DMA_SRCADDRMODE_PEND         (0x1U << DMA_CCTL_SMODE_Pos)            /*!< 0x00000008 */
#define DMA_SRCADDRMODE_FEND         (0x2U << DMA_CCTL_SMODE_Pos)            /*!< 0x00000010 */
#define IS_DMA_SRCADDRMOD(__SAM__)  (((__SAM__) == DMA_SRCADDRMODE_FIX)  ||\
                                     ((__SAM__) == DMA_SRCADDRMODE_PEND) ||\
                                     ((__SAM__) == DMA_SRCADDRMODE_FEND))

//TransSize
#define DMA_TRANSSIZE_BYTE           (0x0U << DMA_CCTL_SIZE_Pos) 
#define DMA_TRANSSIZE_HWORD          (0x1U << DMA_CCTL_SIZE_Pos)
#define DMA_TRANSSIZE_WORD           (0x2U << DMA_CCTL_SIZE_Pos) 
#define IS_DMA_TRANSSIZE(__TSIZE__)  (((__TSIZE__) == DMA_TRANSSIZE_BYTE)  ||\
                                      ((__TSIZE__) == DMA_TRANSSIZE_HWORD) ||\
                                      ((__TSIZE__) == DMA_TRANSSIZE_WORD))

#define IS_DMA_ALIGNEDADDR_WORD(__ADDRW__)    (((__ADDRW__) & 0x3U) == 0U)
#define IS_DMA_ALIGNEDADDR_HWORD(__ADDRHW__)  (((__ADDRHW__) & 0x1U) == 0U)

typedef struct
{
  uint32_t Mode;       /* AES mode */
  uint32_t Direction;  /* Direction */
  uint32_t *KeyStr;    /* AES key */
} DMA_AESInitType;

//AES MODE
#define DMA_AESMODE_128        (0x0U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000000 */
#define DMA_AESMODE_192        (0x1U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000004 */
#define DMA_AESMODE_256        (0x2U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000008 */
#define IS_DMA_AESMOD(__AESMOD__)  (((__AESMOD__) == DMA_AESMODE_128) ||\
                                    ((__AESMOD__) == DMA_AESMODE_192) ||\
                                    ((__AESMOD__) == DMA_AESMODE_256))

//AES Direction
#define DMA_AESDIRECTION_ENCODE         DMA_AESCTL_ENC
#define DMA_AESDIRECTION_DECODE         0
#define IS_DMA_AESDIR(__AESDIR__)  (((__AESDIR__) == DMA_AESDIRECTION_ENCODE) ||\
                                    ((__AESDIR__) == DMA_AESDIRECTION_DECODE))

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
#define IS_DMA_INT(__INT__)  ((((__INT__) & DMA_INT_Msk) != 0U) &&\
                              (((__INT__) & ~DMA_INT_Msk) == 0U))

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

#define IS_DMA_CHANNEL(__CH__)  (((__CH__) == DMA_CHANNEL_0) ||\
                                 ((__CH__) == DMA_CHANNEL_1) ||\
                                 ((__CH__) == DMA_CHANNEL_2) ||\
                                 ((__CH__) == DMA_CHANNEL_3))

/* Exported Functions ------------------------------------------------------- */
/* DMA Exported Functions Group1: 
                                   (De)Initialization ------------------------*/
void DMA_DeInit(uint32_t Channel);
void DMA_Init(DMA_InitType *InitStruct, uint32_t Channel);
void DMA_StructInit(DMA_InitType *InitStruct);
void DMA_ASEDeInit(void);
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
