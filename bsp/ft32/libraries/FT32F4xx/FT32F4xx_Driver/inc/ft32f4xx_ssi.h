/**
  ******************************************************************************
  * @file    ft32f4xx_hal_sai.h
  * @author  xcao
  * @brief   Header file of SSI module.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4xx_SSI_H
#define __FT32F4xx_SSI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/** @defgroup SSI_Exported_Types SSI Exported Types
  * @{
  */

/**
  * @brief  State structures definition
  */
typedef enum
{
    SSI_STATE_RESET      = 0x00U,  /*!< SSI not yet initialized or disabled                */
    SSI_STATE_READY      = 0x01U,  /*!< SSI initialized and ready for use                  */
    SSI_STATE_BUSY       = 0x02U,  /*!< SSI internal process is ongoing                    */
    SSI_STATE_BUSY_TX    = 0x12U,  /*!< Data transmission process is ongoing               */
    SSI_STATE_BUSY_RX    = 0x22U,  /*!< Data reception process is ongoing                  */
    SSI_STATE_TIMEOUT    = 0x03U,  /*!< SSI timeout state                                  */
    SSI_STATE_ERROR      = 0x04U   /*!< SSI error state                                    */
} SSI_StateTypeDef;


/** @defgroup SSI_Init_Structure_definition SSI Init Structure definition
  * @brief  SSI Init Structure definition
  * @{
  */
typedef struct
{
    uint32_t         Mode;                     /*!< Specifies the SSI Mode.
                                                  This parameter can be a value of @ref SSI_MODE                           */

    FunctionalState  SyncMode;                 /*!< Configure the SSI synchronization Mode.                                  */

    FunctionalState  TCHEN;                    /*!< Configure the SSI two-channel operation Mode.                            */

    FunctionalState  OVERSAMPLE;               /*!< Configure the SSI oversample clk output.                                 */

    FunctionalState  RFRCLKDIS;                /*!< Configure the SSI receive frame clock disable
                                                  when ssi receive has been disabled                                       */

    FunctionalState  TFRCLKDIS;                /*!< Configure the SSI receive frame clock disable
                                                  when ssi transmit  has been disabled                                     */

    uint32_t         AC97FRDIV;                /*!< Specifies the AC97 frame rate divider
                                                  This parameter can be a value from 0x00 - 0x3f
                                                  eg:0x01 = SSI will operate every 2 frames                                */

    uint32_t         AC97SLOTWIDTH;            /*!< Specifies the AC97 frame slot data width
                                                  This parameter can be a value of @ref SSI_AC97SLOTWIDTH                  */

    FunctionalState  AC97RXTAGINFIFO;          /*!< Configure the AC97 received tag data store to FIFO                       */

    FunctionalState  AC97VarMode;              /*!< Configure the AC97 variable mode                                         */

} SSI_InitTypeDef;
/**
  * @}
  */


/** @defgroup SSI_TxInitType Structure_definition SSI Tx Init Structure definition
  * @brief  SSI Tx Init Structure definition
  * @{
  */
typedef struct
{
    FunctionalState  FIFO0EN;                   /*!< Configure the SSI TX FIFO0                                         */

    FunctionalState  FIFO1EN;                   /*!< Configure the SSI TX FIFO1                                         */

    uint32_t         FIFO0WaterMark;            /*!< Specifies the SSI FIFO WaterMark to determine the FIFO empty flag.
                                                   This parameter can be a value of @ref SSI_FIFO_WATERMARK           */

    uint32_t         FIFO1WaterMark;            /*!< Specifies the SSI FIFO WaterMark to determine the FIFO empty flag.
                                                   This parameter can be a value of @ref SSI_FIFO_WATERMARK           */

    uint32_t         TxDataType;                /*!< Specifies data transfers start from MSB or LSB bit and
                                                   data truncate high-order or truncate low-order.
                                                   This parameter can be a value of @ref SSI_TRANSDATA_TYPE           */

    uint32_t         DataSize;                  /*!< Specifies the SSI WORD Data size.
                                                   This parameter can be a value of @ref SSI_DATA_SIZE                */

    uint32_t         TxSlotMsk;                 /*!< Specifies the SSI frame slots mask.
                                                   This parameter can be a value of @ref SSI_SLOTMSK                  */

    uint32_t         AC97TxSlotEn;              /*!< Specifies the SSI AC97 slots enable.
                                                   This parameter can be a value of @ref SSI_AC97SLOTEN
                                                   Only used for fixed mode                                           */

    uint32_t         CODECCMDADDR;              /*!< Specifies the SSI AC97 command addr slot
                                                   value Reference codec addr */

    uint32_t         CODECCMDDATA;              /*!< Specifies the SSI AC97 data slot
                                                   value range can be 0x00000-0xfffff                                 */

    uint32_t         FrameSyncPolarity;         /*!< Specifies the SSI frame sync polarity
                                                   This parameter can be a value of @ref SSI_FRAMESYNC_POLARITY       */

    FunctionalState  FrameSyncLenBit;           /*!< Configure the SSI frame lenth for one-word or one-clock-bit        */

    FunctionalState  FrameSyncEarly;            /*!< Configure the SSI frame sync assert position                       */

    FunctionalState  FrameSyncFromExit;         /*!< Configure the SSI frame sync from exit                             */

    uint32_t         FrameRate  ;                /*!< Specifies the SSI frame rate divide ration on the word clock.
                                                   In network mode , this ration sets the number of words of per frame.
                                                   In normal mode , specifies 5'b00000 equel to ratio of 1 provides continuous
                                                   periodic data word transfer.A bit-length frame sync must be used in this case.
                                                   this value range from 00000 to 11111 to control the nomber of words in a frame*/

    FunctionalState  TxClkFromExit;             /*!< Configure the SSI Transmit Clock direction                         */

    uint32_t         TxClkPolarity;             /*!< Specifies the SSI format of bit clock edge used to clock out data
                                                   This paramete can be a value of @ref SSI_CLOCK_POLARITY            */

    uint32_t         FixedDivParam;             /*!< Specifies fixed divider paramter
                                                   This parameter can be a value of @ref SSI_BITCLK_FIXDIV            */

    uint8_t          CustomDivParam;            /*!< Specifies custom divider parameter
                                                   This paramter from 1 to 256(PM = 0x00 to 0xFF)                     */
} SSI_TxInitTypeDef;

/**
  * @}
  */


/** @defgroup SSI_RxInitType Structure_definition SSI Rx Init Structure definition
  * @brief  SSI Rx Init Structure definition
  * @{
  */
typedef struct
{
    FunctionalState  FIFO0EN;                   /*!< Configure the SSI RX FIFO0                                         */

    FunctionalState  FIFO1EN;                   /*!< Configure the SSI RX FIFO1                                         */

    uint32_t         FIFO0WaterMark;            /*!< Specifies the SSI FIFO WaterMark to determine the FIFO empty flag.
                                                   This parameter can be a value of @ref SSI_FIFO_WATERMARK           */

    uint32_t         FIFO1WaterMark;            /*!< Specifies the SSI FIFO WaterMark to determine the FIFO empty flag.
                                                   This parameter can be a value of @ref SSI_FIFO_WATERMARK           */

    uint32_t         RxDataType;                /*!< Specifies data transfers start from MSB or LSB bit and
                                                   data truncate high-order or truncate low-order.
                                                   This parameter can be a value of @ref SSI_TRANSDATA_TYPE           */

    uint32_t         DataSize;                  /*!< Specifies the SSI WORD Data size.
                                                   This parameter can be a value of @ref SSI_DATA_SIZE                */

    uint32_t         RxSlotMsk;                 /*!< Specifies the SSI frame slots mask.
                                                   This parameter can be a value of @ref SSI_SLOTMSK                  */

    uint32_t         FrameSyncPolarity;         /*!< Specifies the SSI frame sync polarity
                                                   This parameter can be a value of @ref SSI_FRAMESYNC_POLARITY       */

    FunctionalState  FrameSyncLenBit;           /*!< Configure the SSI frame lenth for one-word or one-clock-bit        */

    FunctionalState  FrameSyncEarly;            /*!< Configure the SSI frame sync assert position                       */

    FunctionalState  FrameSyncFromExit;         /*!< Configure the SSI frame sync from exit                             */

    uint32_t         FrameRate;                 /*!< Specifies the frame Rate                                           */

    FunctionalState  RxClkFromExit;             /*!< Configure the SSI Transmit Clock direction                         */

    uint32_t         RxClkPolarity;             /*!< Specifies the SSI format of bit clock edge used to clock out data
                                                   This paramete can be a value  of @ref SSI_CLOCK_POLARITY           */

    uint32_t         FixedDivParam;             /*!< Specifies fixed divider paramter
                                                   This parameter can be a value of @ref SSI_BITCLK_FIXDIV            */

    uint8_t          CustomDivParam;            /*!< Specifies custom divider parameter
                                                   This paramter from 1 to 256(PM = 0x00 to 0xFF)                     */
} SSI_RxInitTypeDef;

/**
  * @}
  */

/** @defgroup SSI_Handle_Structure_definition SSI Handle Structure definition
  * @brief  SSI handle Structure definition
  * @{
  */
typedef struct __SSI_HandleTypeDef
{
    SSI_TypeDef              *Instance;          /*!< SSI Blockx registers base address                                 */

    uint8_t                  *pBuffPtr0;         /*!< Pointer to SSI transfer Buffer0                                   */

    uint8_t                  *pBuffPtr1;         /*!< Pointer to SSI transfer Buffer1                                   */

    uint16_t                  XferSize0;         /*!< SSI transfer size0                                                */

    uint16_t                  XferSize1;         /*!< SSI transfer size1                                                */

    uint16_t                  XferCount0;        /*!< SSI transfer counter0                                             */

    uint16_t                  XferCount1;        /*!< SSI transfer counter1                                             */

    __IO SSI_StateTypeDef     State;             /*!< SSI communication state                                           */

    __IO uint32_t             ErrorCode;         /*!< SSI Error code                                                    */


} SSI_HandleTypeDef;
/**
  * @}
  */


/* Exported functions ---------------------------------------------------------*/
/** @defgroup SSI_Exported_Functions SSI Exported Functions
  * @{
  */
void SSI_Init(SSI_HandleTypeDef *ssi,
              SSI_InitTypeDef *ssi_init,
              SSI_TxInitTypeDef *ssi_txinit,
              SSI_RxInitTypeDef *ssi_rxinit);

void SSI_Transmit(SSI_HandleTypeDef *ssi,
                  SSI_InitTypeDef *ssi_init,
                  SSI_TxInitTypeDef *ssi_txinit,
                  uint8_t *pData0,
                  uint8_t *pData1,
                  uint16_t Size0,
                  uint16_t Size1,
                  uint32_t Timeout);

void SSI_Receive(SSI_HandleTypeDef *ssi,
                 SSI_InitTypeDef *ssi_init,
                 SSI_RxInitTypeDef *ssi_rxinit,
                 uint8_t *pData0,
                 uint8_t *pData1,
                 uint16_t Size0,
                 uint16_t Size1,
                 uint32_t Timeout);

void TxConfigInit(SSI_HandleTypeDef *ssi, SSI_InitTypeDef *ssi_init, SSI_TxInitTypeDef *ssi_txinit);
void RxConfigInit(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit);

void SSI_MspInit(SSI_HandleTypeDef *ssi);
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup SSI_Exported_Constants SSI Exported Constants
  * @{
  */
/** @defgroup SAI_Error_Code SAI Error Code
  * @{
  */
#define SSI_ERROR_NONE    0x00000000U  /*!< No error                                    */
#define SSI_ERROR_OVR     0x00000001U  /*!< Overrun Error                               */
#define SSI_ERROR_UDR     0x00000002U  /*!< Underrun error                              */
#define SSI_ERROR_TIMEOUT 0x00000040U  /*!< Timeout error                               */
#define SSI_ERROR_DMA     0x00000080U  /*!< DMA error                                   */
/**
  * @}
  */


/** @defgroup SSI_BITCLK_FIXDIV Clock Divider Presets
  * @{
  */
//#define FIX_CLOCK_DIV2    0x00000000U  /* Fixed 2x  frequency division */
#define FIX_CLOCK_DIV4    0x00000001U  /* Fixed 4x  frequency division */
#define FIX_CLOCK_DIV16   0x00000003U  /* Fixed 16x frequency division */
#define FIX_CLOCK_DIV32   0x00000004U  /* Fixed 32x frequency division */
/**
  * @}
  */


/** @defgroup SSI_MODE Presets
  * @{
  */
#define NET         0x00000001
#define NORMAL      0x00000002
#define I2S_MASTER  0x00000003
#define I2S_SLAVE   0x00000004
#define AC97        0x00000005
/**
  * @}
  */

/** @defgroup I2S_MODE_PARAM Presets
  * @{
  */
#define I2S_MASTER_PARAM 0x00000020
#define I2S_SLAVE_PARAM  0x00000040
/**
  * @}
  */

/** @defgroup SSI_TRANSDATA_TYPE Presets
  * @{
  */
#define MSB_MSW     0x00000001
#define MSB_LSW     0x00000002
#define LSB_MSW     0x00000003
//#define LSB_LSW     0x00000004
/**
  * @}
  */

/** @defgroup SSI_FIFO_WATERMARK Presets
  * @{
  */
#define WATERMARKEQ0 0x00000000
#define WATERMARKEQ1 0x00000001
#define WATERMARKEQ2 0x00000002
#define WATERMARKEQ3 0x00000003
#define WATERMARKEQ4 0x00000004
#define WATERMARKEQ5 0x00000005
#define WATERMARKEQ6 0x00000006
#define WATERMARKEQ7 0x00000007
#define WATERMARKEQ8 0x00000008
#define WATERMARKEQ9 0x00000009
#define WATERMARKEQA 0x0000000A
#define WATERMARKEQB 0x0000000B
#define WATERMARKEQC 0x0000000C
#define WATERMARKEQD 0x0000000D
#define WATERMARKEQE 0x0000000E
#define WATERMARKEQF 0x0000000F
/**
  * @}
  */

/** @defgroup SSI_DATA_SIZE Presets
  * @{
  */
#define SSI_DATA_WL8  0x00000003
#define SSI_DATA_WL10 0x00000004
#define SSI_DATA_WL12 0x00000005
#define SSI_DATA_WL16 0x00000007
#define SSI_DATA_WL18 0x00000008
#define SSI_DATA_WL20 0x00000009
#define SSI_DATA_WL22 0x0000000A
#define SSI_DATA_WL24 0x0000000B
/**
  * @}
  */

/** @defgroup SSI_FRAME_LEGNTH Presets
  * @{
  */
#define SSI_FRAME_LEN0  0x00000000 /* bit-lenth frame sync must be used */
#define SSI_FRAME_LEN1  0x00000100
#define SSI_FRAME_LEN2  0x00000200
#define SSI_FRAME_LEN3  0x00000300
#define SSI_FRAME_LEN4  0x00000400
#define SSI_FRAME_LEN5  0x00000500
#define SSI_FRAME_LEN6  0x00000600
#define SSI_FRAME_LEN7  0x00000700
#define SSI_FRAME_LEN8  0x00000800
#define SSI_FRAME_LEN9  0x00000900
#define SSI_FRAME_LEN10 0x00000A00
#define SSI_FRAME_LEN11 0x00000B00
#define SSI_FRAME_LEN12 0x00000C00
#define SSI_FRAME_LEN13 0x00000D00
#define SSI_FRAME_LEN14 0x00000E00
#define SSI_FRAME_LEN15 0x00000F00
#define SSI_FRAME_LEN16 0x00001F00
/**
  * @}
  */

/** @defgroup SSI_CLOCK_POLARITY Presets
  * @{
  */
#define RISINGEDGE  0x00000000
#define FALLINGEDGE 0x00000001
/**
  * @}
  */

/** @defgroup SSI_FRAMESYNC_POLARITY Presets
  * @{
  */
#define ACTIVEHIGH  0x00000000
#define ACTIVELOW   0x00000001
/**
  * @}
  */

/** @defgroup SSI_AC97SLOTWIDTH Presets
  * @{
  */
#define SLOTWIDEQ20 0x00000000
#define SLOTWIDEQ16 0x00000001
/**
  * @}
  */


/** @defgroup SSI_SLOTMSK Presets
 *  @{
 */
/*1 no data transmit in this time slot*/
#define ENALLSLOTS  0x00000000
#define ENSLOTS1    0xFFFFFFFE
#define ENSLOTS2    0xFFFFFFFD
#define ENSLOTS3    0xFFFFFFFB
#define ENSLOTS4    0xFFFFFFF7
#define ENSLOTS5    0xFFFFFFEF
#define ENSLOTS6    0xFFFFFFDF
#define ENSLOTS7    0xFFFFFFBF
#define ENSLOTS8    0xFFFFFF7F
#define ENSLOTS9    0xFFFFFEFF
#define ENSLOTS10   0xFFFFFDFF
#define ENSLOTS11   0xFFFFFBFF
#define ENSLOTS12   0xFFFFF7FF
#define ENSLOTS13   0xFFFFEFFF
#define ENSLOTS14   0xFFFFDFFF
#define ENSLOTS15   0xFFFFBFFF
#define ENSLOTS16   0xFFFF7FFF
#define ENSLOTS17   0xFFFEFFFF
#define ENSLOTS18   0xFFFDFFFF
#define ENSLOTS19   0xFFFBFFFF
#define ENSLOTS20   0xFFF7FFFF
#define ENSLOTS21   0xFFEFFFFF
#define ENSLOTS22   0xFFDFFFFF
#define ENSLOTS23   0xFFBFFFFF
#define ENSLOTS24   0xFF7FFFFF
#define ENSLOTS25   0xFEFFFFFF
#define ENSLOTS26   0xFDFFFFFF
#define ENSLOTS27   0xFBFFFFFF
#define ENSLOTS28   0xF7FFFFFF
#define ENSLOTS29   0xEFFFFFFF
#define ENSLOTS30   0xDFFFFFFF
#define ENSLOTS31   0xBFFFFFFF
#define ENSLOTS32   0x7FFFFFFF
/**
  * @}
  */


/** @defgroup SSI_AC97SLOTEN Presets
 *  @{
 */
#define AC97SLOT0EN    0x00000004
#define AC97SLOT1EN    0x00000008
#define AC97SLOT2EN    0x00000010
#define AC97SLOT3EN    0x00000020
#define AC97SLOT4EN    0x00000040
#define AC97SLOT5EN    0x00000080
#define AC97SLOT6EN    0x00000100
#define AC97SLOT7EN    0x00000200
#define AC97SLOT8EN    0x00000400
#define AC97SLOT9EN    0x00000800
#define AC97SLOT10EN   0x00001000
#define AC97SLOT11EN   0x00002000
#define AC97SLOT12EN   0x00004000
/**
  * @}
  */


/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @addtogroup SAI_Private_Macros
  * @{
  */
#define IS_SSI_MODE(MODE) (((MODE) == NET) ||\
                           ((MODE) == NORMAL)  ||\
                           ((MODE) == I2S_MASTER) ||\
                           ((MODE) == I2S_SLAVE) ||\
                           ((MODE) == AC97))

#define IS_SSI_AC97SLOTWIDTH(SLOTWIDTH) (((SLOTWIDTH) == SLOTWIDEQ20) || \
                                         ((SLOTWIDTH) == SLOTWIDEQ16))


#define IS_SSI_BITCLK_FIXDIV(FIXDIV) (((FIXDIV) == FIX_CLOCK_DIV4)  || \
                                      ((FIXDIV) == FIX_CLOCK_DIV16) || \
                                      ((FIXDIV) == FIX_CLOCK_DIV32) \
                                     )

#define IS_SSI_DATA_SIZE(DATA_SIZE) (((DATA_SIZE) == SSI_DATA_WL8) || \
                                     ((DATA_SIZE) == SSI_DATA_WL10) || \
                                     ((DATA_SIZE) == SSI_DATA_WL12) || \
                                     ((DATA_SIZE) == SSI_DATA_WL14) || \
                                     ((DATA_SIZE) == SSI_DATA_WL16) || \
                                     ((DATA_SIZE) == SSI_DATA_WL18) || \
                                     ((DATA_SIZE) == SSI_DATA_WL20) || \
                                     ((DATA_SIZE) == SSI_DATA_WL22) || \
                                     ((DATA_SIZE) == SSI_DATA_WL24) \
                                    )

#define IS_SSI_FRAMELEN(FRLEN) (((FRLEN) == SSI_FRAME_LEN0) ||\
                               ((FRLEN) == SSI_FRAME_LEN1  )||\
                               ((FRLEN) == SSI_FRAME_LEN2  )||\
                               ((FRLEN) == SSI_FRAME_LEN3  )||\
                               ((FRLEN) == SSI_FRAME_LEN4  )||\
                               ((FRLEN) == SSI_FRAME_LEN5  )||\
                               ((FRLEN) == SSI_FRAME_LEN6  )||\
                               ((FRLEN) == SSI_FRAME_LEN7  )||\
                               ((FRLEN) == SSI_FRAME_LEN8  )||\
                               ((FRLEN) == SSI_FRAME_LEN9  )||\
                               ((FRLEN) == SSI_FRAME_LEN10 )||\
                               ((FRLEN) == SSI_FRAME_LEN11 )||\
                               ((FRLEN) == SSI_FRAME_LEN12 )||\
                               ((FRLEN) == SSI_FRAME_LEN13 )||\
                               ((FRLEN) == SSI_FRAME_LEN14 )||\
                               ((FRLEN) == SSI_FRAME_LEN15 )||\
                               ((FRLEN) == SSI_FRAME_LEN16 ))


#define IS_SSI_SLOTMSK(SLOTMSK) (  ((SLOTMSK) == ENALLSLOTS) || \
                                   ((SLOTMSK) == ENSLOTS0  ) || \
                                   ((SLOTMSK) == ENSLOTS1  ) || \
                                   ((SLOTMSK) == ENSLOTS2  ) || \
                                   ((SLOTMSK) == ENSLOTS3  ) || \
                                   ((SLOTMSK) == ENSLOTS4  ) || \
                                   ((SLOTMSK) == ENSLOTS5  ) || \
                                   ((SLOTMSK) == ENSLOTS6  ) || \
                                   ((SLOTMSK) == ENSLOTS7  ) || \
                                   ((SLOTMSK) == ENSLOTS8  ) || \
                                   ((SLOTMSK) == ENSLOTS9  ) || \
                                   ((SLOTMSK) == ENSLOTS10 ) || \
                                   ((SLOTMSK) == ENSLOTS11 ) || \
                                   ((SLOTMSK) == ENSLOTS12 ) || \
                                   ((SLOTMSK) == ENSLOTS13 ) || \
                                   ((SLOTMSK) == ENSLOTS14 ) || \
                                   ((SLOTMSK) == ENSLOTS15 ) || \
                                   ((SLOTMSK) == ENSLOTS16 ) || \
                                   ((SLOTMSK) == ENSLOTS17 ) || \
                                   ((SLOTMSK) == ENSLOTS18 ) || \
                                   ((SLOTMSK) == ENSLOTS19 ) || \
                                   ((SLOTMSK) == ENSLOTS20 ) || \
                                   ((SLOTMSK) == ENSLOTS21 ) || \
                                   ((SLOTMSK) == ENSLOTS22 ) || \
                                   ((SLOTMSK) == ENSLOTS23 ) || \
                                   ((SLOTMSK) == ENSLOTS24 ) || \
                                   ((SLOTMSK) == ENSLOTS25 ) || \
                                   ((SLOTMSK) == ENSLOTS26 ) || \
                                   ((SLOTMSK) == ENSLOTS27 ) || \
                                   ((SLOTMSK) == ENSLOTS28 ) || \
                                   ((SLOTMSK) == ENSLOTS29 ) || \
                                   ((SLOTMSK) == ENSLOTS30 ) || \
                                   ((SLOTMSK) == ENSLOTS31 ))


#define IS_SSI_AC97SLOTSEN(AC97SLOTEN)  (((AC97SLOTEN) == AC97SLOT0EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT1EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT2EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT3EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT4EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT5EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT6EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT7EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT8EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT9EN ) ||\
                                         ((AC97SLOTEN) == AC97SLOT10EN) ||\
                                         ((AC97SLOTEN) == AC97SLOT11EN) ||\
                                         ((AC97SLOTEN) == AC97SLOT12EN))


#define IS_SSI_TRANSDATA_TYPE(TRANSDATA) (((TRANSDATA) == MSB_MSW) || \
                                          ((TRANSDATA) == MSB_LSW) || \
                                          ((TRANSDATA) == LSB_MSW)\
                                         )

#define IS_SSI_FIFO_WATERMARK(WATERMARK) (((WATERMARK) == WATERMARKEQ0) || \
                                          ((WATERMARK) == WATERMARKEQ1) || \
                                          ((WATERMARK) == WATERMARKEQ2) || \
                                          ((WATERMARK) == WATERMARKEQ3) || \
                                          ((WATERMARK) == WATERMARKEQ4) || \
                                          ((WATERMARK) == WATERMARKEQ5) || \
                                          ((WATERMARK) == WATERMARKEQ6) || \
                                          ((WATERMARK) == WATERMARKEQ7) || \
                                          ((WATERMARK) == WATERMARKEQ8) || \
                                          ((WATERMARK) == WATERMARKEQ9) || \
                                          ((WATERMARK) == WATERMARKEQA) || \
                                          ((WATERMARK) == WATERMARKEQB) || \
                                          ((WATERMARK) == WATERMARKEQC) || \
                                          ((WATERMARK) == WATERMARKEQD) || \
                                          ((WATERMARK) == WATERMARKEQE) || \
                                          ((WATERMARK) == WATERMARKEQF)\
                                         )

#define IS_SSI_FRAMESYNC_POLARITY(FRPOLARITY) (((FRPOLARITY) == ACTIVEHIGH) || \
                                             ((FRPOLARITY) == ACTIVELOW))

#define IS_SSI_CLOCK_POLARITY(CKPOLARITY) (((CKPOLARITY) == RISINGEDGE) ||\
                                           ((CKPOLARITY) == FALLINGEDGE))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* FT32F4xx_SSI_H */
