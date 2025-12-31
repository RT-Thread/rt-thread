/**
  ******************************************************************************
  * @file               ft32f4xx_i2s.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for
  *               the I2S firmware library
  * @version            V1.0.0
  * @date                   2025-04-01
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_I2S_H
#define __FT32F4XX_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup I2S
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup I2S_Exported_Types I2S Exported Types
  * @{
  */

/**
  * @brief  I2S Init structure definition
  */
typedef struct
{
    uint32_t I2S_Channel0;                /*!< Specifies the I2S channel 0 operating mode.
                                             This parameter can be a value of @ref I2S_Channel0_Configuration */

    uint32_t I2S_Channel1;                /*!< Specifies the I2S channel 1 operating mode.
                                             This parameter can be a value of @ref I2S_Channel1_Configuration */

    uint32_t I2S_TranMasterSlaveConfig;   /*!< Specifies the I2S transmitter master or slave.
                                             This parameter can be a value of @ref I2S_MASTER_SLAVE */

    uint32_t I2S_RecMasterSlaveConfig;    /*!< Specifies the I2S receiver master or slave.
                                             This parameter can be a value of @ref I2S_MASTER_SLAVE */

    uint32_t I2S_TranSampleRate;          /*!< Specifies the I2S transmit sample rate.
                                             This parameter can be a value of @ref I2S_RATE */

    uint32_t I2S_TranSampleResolution;    /*!< Specifies the I2S transmit sample resolution.
                                             This parameter can be a value of @ref I2S_RESOLUTION */

    uint32_t I2S_RecSampleRate;           /*!< Specifies the I2S receive sample rate.
                                             This parameter can be a value of @ref I2S_RATE */

    uint32_t I2S_RecSampleResolution;     /*!< Specifies the I2S transmit sample resolution.
                                             This parameter can be a value of @ref I2S_RESOLUTION */

    uint32_t I2S_TFIFOAEmptyThreshold;    /*!< Specifies the I2S transmit FIFO almost empty threshold
                                             This parameter can be a value of @ref I2S_FIFO_THRESHOLD */

    uint32_t I2S_TFIFOAFullThreshold;     /*!< Specifies the I2S transmit FIFO almost full threshold
                                             This parameter can be a value of @ref I2S_FIFO_THRESHOLD */

    uint32_t I2S_RFIFOAEmptyThreshold;    /*!< Specifies the I2S receive FIFO almost empty threshold
                                             This parameter can be a value of @ref I2S_FIFO_THRESHOLD */

    uint32_t I2S_RFIFOAFullThreshold;     /*!< Specifies the I2S receive FIFO almost full threshold
                                             This parameter can be a value of @ref I2S_FIFO_THRESHOLD */

    uint32_t I2S_Standard;                /*!< Specifies the standard used for the I2S communication
                                             This parameter can be a value of @ref I2S_STANDARD */
} I2S_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup I2S_Exported_Constants I2S Exported Constants
  * @{
  */
/** @defgroup I2S_Periph
  * @{
  */
#define IS_I2S_ALL_PERIPH(PERIPH)       (((PERIPH) == I2S2) || \
                                         ((PERIPH) == I2S3))
/**
  * @}
  */

/** @defgroup I2S_Channel0_Configuration
  * @{
  */
#define I2S_Ch0_Disable     ((uint32_t)0x00000000)
#define I2S_Ch0_Transmitter ((uint32_t)0x00000001)
#define I2S_Ch0_Receiver    ((uint32_t)0x00000010)

#define IS_I2S_CH0_CONFIG(CONFIG)       (((CONFIG) == I2S_Ch0_Disable)     || \
                                         ((CONFIG) == I2S_Ch0_Transmitter) || \
                                         ((CONFIG) == I2S_Ch0_Receiver))
/**
  * @}
  */

/** @defgroup I2S_Channel1_Configuration
  * @{
  */
#define I2S_Ch1_Disable     ((uint32_t)0x00000000)
#define I2S_Ch1_Transmitter ((uint32_t)0x00000001)
#define I2S_Ch1_Receiver    ((uint32_t)0x00000010)

#define IS_I2S_CH1_CONFIG(CONFIG)       (((CONFIG) == I2S_Ch1_Disable)     || \
                                         ((CONFIG) == I2S_Ch1_Transmitter) || \
                                         ((CONFIG) == I2S_Ch1_Receiver))
/**
  * @}
  */

/** @defgroup I2S_MASTER_SLAVE
  * @{
  */
#define I2S_MASTER                          0x00000000
#define I2S_SLAVE                           0x00000001


#define IS_I2S_MASTERSLAVE_STATE(STATE)     (((STATE) == I2S_MASTER) || \
                                             ((STATE) == I2S_SLAVE))
/**
  * @}
  */

/** @defgroup I2S_SAMPLE_RATE
  * @{
  */
#define IS_I2S_SAMPLE_RATE(SAMPLE_RATE)   ((SAMPLE_RATE) <= (uint16_t)0x7FF)
/**
  * @}
  */

/** @defgroup I2S_RESOLUTION
  * @{
  */
#define IS_I2S_RESOLUTION(RESOLUTION)   ((RESOLUTION) <= (uint8_t)0x1F)
/**
  * @}
  */

/** @defgroup I2S_FIFO_THRESHOLD
  * @{
  */
#define IS_I2S_FIFO_THRESHOLD(FIFO_THRESHOLD)   ((FIFO_THRESHOLD) <= (uint8_t)0x07)
/**
  * @}
  */

/** @defgroup I2S_STANDARD
  * @{
  */
#define I2S_Philips          ((uint32_t)0x00000249)
#define I2S_Right_Justified  ((uint32_t)0x000004D3)
#define I2S_Left_Justified   ((uint32_t)0x000006DB)
#define I2S_DSP              ((uint32_t)0x00000A69)

#define IS_I2S_STANDARD(STANDARD)  (((STANDARD) == I2S_Philips)         || \
                                    ((STANDARD) == I2S_Right_Justified) || \
                                    ((STANDARD) == I2S_Left_Justified)  || \
                                    ((STANDARD) == I2S_DSP))
/**
  * @}
  */

/** @defgroup I2S_CHANNEL_ENABLE
  * @{
  */
#define I2S_CH0                          I2S_CTRL_I2SEN0
#define I2S_CH1                          I2S_CTRL_I2SEN1

#define IS_I2S_CHANNEL_SEL(CHy)       (((CHy) == I2S_CH0) || \
                                       ((CHy) == I2S_CH1))
/**
  * @}
  */

/** @defgroup I2S_CHANNEL_TRANSMITTER_OR_RECEIVER
  * @{
  */
#define I2S_CH0_TRANREC                         I2S_CTRL_TRCFG0
#define I2S_CH1_TRANREC                         I2S_CTRL_TRCFG1

#define IS_I2S_CHANNEL_TRANREC(CHy_TRANREC)     (((CHy_TRANREC) == I2S_CTRL_TRCFG0) || \
                                                 ((CHy_TRANREC) == I2S_CTRL_TRCFG1))
/**
  * @}
  */
/** @defgroup I2S_TRANSMITTER_RECEIVER
  * @{
  */
#define I2S_TRANSMITTER                 0x00000001
#define I2S_RECEIVER                    0x00000000

#define IS_I2S_TRANREC_STATE(STATE)     (((STATE) == I2S_TRANSMITTER) || \
                                         ((STATE) == I2S_RECEIVER))
/**
  * @}
  */

/** @defgroup I2S_CHANNEL_CLOCK_STROBE
  * @{
  */
#define I2S_CH0_CLOCK_STROBE                         I2S_CID_CTRL_I2SSTROBE0
#define I2S_CH1_CLOCK_STROBE                         I2S_CID_CTRL_I2SSTROBE1

#define IS_I2S_CHANNEL_CLOCK_STROBE(CHy_CLOCK)       (((CHy_CLOCK) == I2S_CID_CTRL_I2SSTROBE0) || \
                                                      ((CHy_CLOCK) == I2S_CID_CTRL_I2SSTROBE1))
/**
  * @}
  */

/** @defgroup I2S_SCK_POLAR
  * @{
  */
#define I2S_SCK_POLAR_RISE          ((uint8_t)0x00)
#define I2S_SCK_POLAR_FALL          ((uint8_t)0x01)

#define IS_I2S_SCK_POLAR(SCK_POLAR) (((SCK_POLAR) == I2S_SCK_POLAR_FALL) || \
                                     ((SCK_POLAR) == I2S_SCK_POLAR_RISE))
/**
  * @}
  */

/** @defgroup I2S_WS_POLAR
  * @{
  */
#define I2S_WS_POLAR_0          ((uint8_t)0x00)
#define I2S_WS_POLAR_1          ((uint8_t)0x01)

#define IS_I2S_WS_POLAR(WS_POLAR)  (((WS_POLAR) == I2S_WS_POLAR_0) || \
                                    ((WS_POLAR) == I2S_WS_POLAR_1))
/**
  * @}
  */

/** @defgroup I2S_ALIGNMENT
  * @{
  */
#define I2S_ALIGN_LSB                ((uint8_t)0x00)
#define I2S_ALIGN_MSB                ((uint8_t)0x01)

#define IS_I2S_ALIGNMENT(ALIGNMENT)  (((ALIGNMENT) == I2S_ALIGN_LSB) || \
                                      ((ALIGNMENT) == I2S_ALIGN_MSB))
/**
  * @}
  */

/** @defgroup I2S_TRAN_DATA_WS_DEL
  * @{
  */
#define I2S_TRAN_DATA_WS_DEL_0             ((uint8_t)0x00)
#define I2S_TRAN_DATA_WS_DEL_1             ((uint8_t)0x01)

#define IS_I2S_TRAN_DATA_WS_DEL(DELAY)     (((DELAY) == I2S_TRAN_DATA_WS_DEL_0) || \
                                            ((DELAY) == I2S_TRAN_DATA_WS_DEL_1))
/**
  * @}
  */

/** @defgroup I2S_REC_DATA_WS_DEL
  * @{
  */
#define I2S_REC_DATA_WS_DEL_0             ((uint8_t)0x00)
#define I2S_REC_DATA_WS_DEL_1             ((uint8_t)0x01)

#define IS_I2S_REC_DATA_WS_DEL(DELAY)     (((DELAY) == I2S_REC_DATA_WS_DEL_0) || \
                                           ((DELAY) == I2S_REC_DATA_WS_DEL_1))
/**
  * @}
  */

/** @defgroup I2S_WS_FORMAT
  * @{
  */
#define I2S_WS_PHILIPS               ((uint8_t)0x00)
#define I2S_WS_DSP                   ((uint8_t)0x01)

#define IS_I2S_WS_FORMAT(FORMAT)     (((FORMAT) == I2S_WS_PHILIPS) || \
                                      ((FORMAT) == I2S_WS_DSP))
/**
  * @}
  */

/** @defgroup I2S_registers
  * @{
  */
#define I2S_Register_CTRL          ((uint8_t)0x00)
#define I2S_Register_INTR_STAT     ((uint8_t)0x04)
#define I2S_Register_SRR           ((uint8_t)0x08)
#define I2S_Register_CID_CTRL      ((uint8_t)0x0C)
#define I2S_Register_TFIFO_STAT    ((uint8_t)0x10)
#define I2S_Register_RFIFO_STAT    ((uint8_t)0x14)
#define I2S_Register_TFIFO_CTRL    ((uint8_t)0x18)
#define I2S_Register_RFIFO_CTRL    ((uint8_t)0x1C)
#define I2S_Register_DEV_CONF      ((uint8_t)0x20)
#define I2S_Register_POLL_STAT     ((uint8_t)0x24)

#define IS_I2S_REGISTER(REGISTER)     (((REGISTER) == I2S_Register_CTRL      ) || \
                                       ((REGISTER) == I2S_Register_INTR_STAT ) || \
                                       ((REGISTER) == I2S_Register_SRR       ) || \
                                       ((REGISTER) == I2S_Register_CID_CTRL  ) || \
                                       ((REGISTER) == I2S_Register_TFIFO_STAT) || \
                                       ((REGISTER) == I2S_Register_RFIFO_STAT) || \
                                       ((REGISTER) == I2S_Register_TFIFO_CTRL) || \
                                       ((REGISTER) == I2S_Register_RFIFO_CTRL) || \
                                       ((REGISTER) == I2S_Register_DEV_CONF  ) || \
                                       ((REGISTER) == I2S_Register_POLL_STAT ))
/**
  * @}
  */

/** @defgroup I2S_interrupts_definition
  * @{
  */
#define I2S_IT_TDATAUNDERR             I2S_INTR_STAT_TDATAUNDERR
#define I2S_IT_RDATAOVRERR             I2S_INTR_STAT_RDATAOVRERR
#define I2S_IT_TFIFOEMPTY              I2S_INTR_STAT_TFIFOEMPTY
#define I2S_IT_TFIFOAEMPTY             I2S_INTR_STAT_TFIFOAEMPTY
#define I2S_IT_TFIFOFULL               I2S_INTR_STAT_TFIFOFULL
#define I2S_IT_TFIFOAFULL              I2S_INTR_STAT_TFIFOAFULL
#define I2S_IT_RFIFOEMPTY              I2S_INTR_STAT_RFIFOEMPTY
#define I2S_IT_RFIFOAEMPTY             I2S_INTR_STAT_RFIFOAEMPTY
#define I2S_IT_RFIFOFULL               I2S_INTR_STAT_RFIFOFULL
#define I2S_IT_RFIFOAFULL              I2S_INTR_STAT_RFIFOAFULL

#define IS_I2S_CLEAR_IT(IT)            ((((IT) & (uint32_t)0xFFFF00EE) == 0x00) && ((IT) != 0x00))

#define IS_I2S_GET_IT(IT)              (((IT) == I2S_IT_TDATAUNDERR) || ((IT) == I2S_IT_RDATAOVRERR) || \
                                        ((IT) == I2S_IT_TFIFOEMPTY)  || ((IT) == I2S_IT_TFIFOAEMPTY) || \
                                        ((IT) == I2S_IT_TFIFOFULL)   || ((IT) == I2S_IT_TFIFOAFULL)  || \
                                        ((IT) == I2S_IT_RFIFOEMPTY)  || ((IT) == I2S_IT_RFIFOAEMPTY) || \
                                        ((IT) == I2S_IT_RFIFOFULL)   || ((IT) == I2S_IT_RFIFOAFULL))
/**
  * @}
  */

/** @defgroup I2S_FIFO_IT_MASK
  * @{
  */
#define I2S_TFIFOEMPTY_MASK         I2S_CID_CTRL_TFIFOEMPTYMASK
#define I2S_TFIFOAEMPTY_MASK            I2S_CID_CTRL_TFIFOAEMPTYMASK
#define I2S_TFIFOFULL_MASK              I2S_CID_CTRL_TFIFOFULLMASK
#define I2S_TFIFOAFULL_MASK             I2S_CID_CTRL_TFIFOAFULLMASK
#define I2S_RFIFOEMPTY_MASK             I2S_CID_CTRL_RFIFOEMPTYMASK
#define I2S_RFIFOAEMPTY_MASK            I2S_CID_CTRL_RFIFOAEMPTYMASK
#define I2S_RFIFOFULL_MASK              I2S_CID_CTRL_RFIFOFULLMASK
#define I2S_RFIFOAFULL_MASK             I2S_CID_CTRL_RFIFOAFULLMASK

#define IS_I2S_FIFO_IT_MASK(IT_MASK)   (((IT_MASK) == I2S_TFIFOEMPTY_MASK)     || \
                                        ((IT_MASK) == I2S_TFIFOAEMPTY_MASK)    || \
                                        ((IT_MASK) == I2S_TFIFOFULL_MASK)      || \
                                        ((IT_MASK) == I2S_TFIFOAFULL_MASK)     || \
                                        ((IT_MASK) == I2S_RFIFOEMPTY_MASK)     || \
                                        ((IT_MASK) == I2S_RFIFOAEMPTY_MASK)    || \
                                        ((IT_MASK) == I2S_RFIFOFULL_MASK)      || \
                                        ((IT_MASK) == I2S_RFIFOAFULL_MASK))
/**
  * @}
  */

/** @defgroup I2S_DATA_IT_MASK
  * @{
  */
#define I2S_0_MASK         I2S_CID_CTRL_I2SMASK0
#define I2S_1_MASK         I2S_CID_CTRL_I2SMASK1

#define IS_I2S_DATA_IT_MASK(IT_MASK)   (((IT_MASK) == I2S_0_MASK) || \
                                        ((IT_MASK) == I2S_1_MASK))
/**
  * @}
  */

/** @defgroup I2S_POLL_STAT
  * @{
  */
#define I2S_STAT_TFIFOEMPTY              I2S_POLL_STAT_TXEMPTY
#define I2S_STAT_TFIFOAEMPTY             I2S_POLL_STAT_TXAEMPTY
#define I2S_STAT_TXUNDERRUN              I2S_POLL_STAT_TXUNDERRUN
#define I2S_STAT_RFIFOFULL               I2S_POLL_STAT_RXFULL
#define I2S_STAT_RFIFOAFULL              I2S_POLL_STAT_RXAFULL
#define I2S_STAT_RXOVERRUN               I2S_POLL_STAT_RXOVERRUN

#define IS_I2S_GET_STAT(STAT)          (((STAT) == I2S_STAT_TFIFOEMPTY)  || \
                                        ((STAT) == I2S_STAT_TFIFOAEMPTY) || \
                                        ((STAT) == I2S_STAT_TXUNDERRUN)  || \
                                        ((STAT) == I2S_STAT_RFIFOFULL)   || \
                                        ((STAT) == I2S_STAT_RFIFOAFULL)  || \
                                        ((STAT) == I2S_STAT_RXOVERRUN))
/**
  * @}
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2S_Exported_Functions
  * @{
  */

/* Initialization and Configuration functions *********************************/
void I2S_DeInit(I2S_TypeDef* I2Sx);
void I2S_Init(I2S_TypeDef* I2Sx, I2S_InitTypeDef* I2S_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void I2S_ChannelConfig(I2S_TypeDef* I2Sx, uint32_t CHy, FunctionalState NewState);
void I2S_ChannelTranRecConfig(I2S_TypeDef* I2Sx, uint32_t CHy_TRANREC, uint32_t I2S_TranRec);
void I2S_LoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_SFRResetCmd(I2S_TypeDef* I2Sx);
void I2S_TranMasterSlaveConfig(I2S_TypeDef* I2Sx, uint32_t I2S_MS);
void I2S_RecMasterSlaveConfig(I2S_TypeDef* I2Sx, uint32_t I2S_MS);
void I2S_TranSyncResetCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_RecSyncResetCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_TranSyncLoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_RecSyncLoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_TranSampleRateConfig(I2S_TypeDef* I2Sx, uint16_t SAMPLE_RATE);
void I2S_TranSampleResolutionConfig(I2S_TypeDef* I2Sx, uint8_t RESOLUTION);
void I2S_RecSampleRateConfig(I2S_TypeDef* I2Sx, uint16_t SAMPLE_RATE);
void I2S_RecSampleResolutionConfig(I2S_TypeDef* I2Sx, uint8_t RESOLUTION);
void I2S_ChannelClockConfig(I2S_TypeDef* I2Sx, uint32_t CHy_CLOCK, FunctionalState NewState);
void I2S_TranSyncUnitCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_RecSyncUnitCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_StandardConfig(I2S_TypeDef* I2Sx, uint32_t Standard);
void I2S_TranSckPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_SCK_Polar);
void I2S_RecSckPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_SCK_Polar);
void I2S_TranWSPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Polar);
void I2S_RecWSPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Polar);
void I2S_TranAPBAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align);
void I2S_RecAPBAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align);
void I2S_TranI2SAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align);
void I2S_RecI2SAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align);
void I2S_TranDataWSDelConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Tran_Data_WS_Del);
void I2S_RecDataWSDelConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Rec_Data_WS_Del);
void I2S_TranWSFormatConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Format);
void I2S_RecWSFormatConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Format);

/* TX/RX FIFO control functions ***********************************************/
void I2S_TFIFOResetCmd(I2S_TypeDef* I2Sx);
void I2S_RFIFOResetCmd(I2S_TypeDef* I2Sx);
uint8_t I2S_GetTranFIFOLevel(I2S_TypeDef* I2Sx);
uint8_t I2S_GetRecFIFOLevel(I2S_TypeDef* I2Sx);
void I2S_TFIFOAEmptyThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold);
void I2S_TFIFOAFullThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold);
void I2S_RFIFOAEmptyThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold);
void I2S_RFIFOAFullThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold);

/* I2S registers management functions *****************************************/
uint32_t I2S_ReadRegister(I2S_TypeDef* I2Sx, uint8_t I2S_Register);

/* Data transfers management functions ****************************************/
void I2S_SendData(I2S_TypeDef* I2Sx, uint32_t Data);
uint32_t I2S_ReceiveData(I2S_TypeDef* I2Sx);

/* Interrupts and flags management functions **********************************/
void I2S_AllITMaskCmd(I2S_TypeDef* I2Sx, FunctionalState NewState);
void I2S_FIFOITConfig(I2S_TypeDef* I2Sx, uint32_t I2S_IT_Mask, FunctionalState NewState);
void I2S_DataITConfig(I2S_TypeDef* I2Sx, uint32_t I2S_IT_Mask, FunctionalState NewState);
ITStatus I2S_GetITStatus(I2S_TypeDef* I2Sx, uint32_t I2S_IT);
void I2S_ClearITPendingBit(I2S_TypeDef* I2Sx, uint32_t I2S_IT);
uint8_t I2S_GetUnderrunCode(I2S_TypeDef* I2Sx);
uint8_t I2S_GetOverrunCode(I2S_TypeDef* I2Sx);
FlagStatus I2S_GetPollStatus(I2S_TypeDef* I2Sx, uint32_t I2S_Stat);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_I2S_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE*******************/
