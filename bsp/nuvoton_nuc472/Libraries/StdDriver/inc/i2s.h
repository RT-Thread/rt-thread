/******************************************************************************
 * @file     i2s.h
 * @version  V0.10
 * $Revision: 12 $
 * $Date: 15/09/22 6:48p $
 * @brief    NUC472/NUC442 I2S driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __I2S_H__
#define __I2S_H__

#include "NUC472_442.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_I2S_Driver I2S Driver
  @{
*/

/** @addtogroup NUC472_442_I2S_EXPORTED_CONSTANTS I2S Exported Constants
  @{
*/
#define I2S_DATABIT_8           (0 << I2S_CTL_WDWIDTH_Pos)       /*!< I2S data width is 8-bit  \hideinitializer */
#define I2S_DATABIT_16          (1 << I2S_CTL_WDWIDTH_Pos)       /*!< I2S data width is 16-bit  \hideinitializer */
#define I2S_DATABIT_24          (2 << I2S_CTL_WDWIDTH_Pos)       /*!< I2S data width is 24-bit  \hideinitializer */
#define I2S_DATABIT_32          (3 << I2S_CTL_WDWIDTH_Pos)       /*!< I2S data width is 32-bit  \hideinitializer */

/* Audio Format */
#define I2S_MONO                I2S_CTL_MONO_Msk                   /*!< Mono channel  \hideinitializer */
#define I2S_STEREO              0                                  /*!< Stereo channel  \hideinitializer */

/* I2S Data Format */
#define I2S_FORMAT_MSB          I2S_CTL_FORMAT_Msk                 /*!< MSB data format  \hideinitializer */
#define I2S_FORMAT_I2S          0                                  /*!< I2S data format  \hideinitializer */
#define I2S_FORMAT_PCMB         I2S_CTL_FORMAT_Msk                 /*!< PCMB data format  \hideinitializer */
#define I2S_FORMAT_PCMA         0                                  /*!< PCMA data format  \hideinitializer */

/* I2S Interface */
#define I2S_PCM                 I2S_CTL_PCMEN_Msk                  /*!< PCM interface is selected  \hideinitializer */
#define I2S_I2S                 0                                  /*!< I2S interface is selected  \hideinitializer */

/* I2S Operation mode */
#define I2S_MODE_SLAVE          I2S_CTL_SLAVE_Msk                  /*!< As slave mode  \hideinitializer */
#define I2S_MODE_MASTER         0                                  /*!< As master mode  \hideinitializer */

/* I2S FIFO Threshold */
#define I2S_FIFO_TX_LEVEL_WORD_0    0                              /*!< TX threshold is 0 word  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_1    (1 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 1 word  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_2    (2 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 2 words  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_3    (3 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 3 words  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_4    (4 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 4 words  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_5    (5 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 5 words  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_6    (6 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 6 words  \hideinitializer */
#define I2S_FIFO_TX_LEVEL_WORD_7    (7 << I2S_CTL_TXTH_Pos)        /*!< TX threshold is 7 words  \hideinitializer */

#define I2S_FIFO_RX_LEVEL_WORD_1    0                              /*!< RX threshold is 1 word  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_2    (1 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 2 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_3    (2 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 3 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_4    (3 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 4 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_5    (4 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 5 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_6    (5 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 6 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_7    (6 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 7 words  \hideinitializer */
#define I2S_FIFO_RX_LEVEL_WORD_8    (7 << I2S_CTL_RXTH_Pos)        /*!< RX threshold is 8 words  \hideinitializer */

/* I2S Record Channel */
#define I2S_MONO_RIGHT          0                                  /*!< Record mono right channel  \hideinitializer */
#define I2S_MONO_LEFT           I2S_CTL_RXLCH_Msk                  /*!< Record mono left channel  \hideinitializer */

/* I2S Channel */
#define I2S_RIGHT               0                                  /*!< Select right channel  \hideinitializer */
#define I2S_LEFT                1                                  /*!< Select left channel  \hideinitializer */

/*@}*/ /* end of group NUC472_442_I2S_EXPORTED_CONSTANTS */

/** @addtogroup NUC472_442_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/**
  * @brief  Enable zero cross detect function.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32ChMask is the mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return none
  * \hideinitializer
  */
static __INLINE void I2S_ENABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CTL |= I2S_CTL_RZCEN_Msk;
    else
        i2s->CTL |= I2S_CTL_LZCEN_Msk;
}

/**
  * @brief  Disable zero cross detect function.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32ChMask is the mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return none
  * \hideinitializer
  */
static __INLINE void I2S_DISABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CTL &= ~I2S_CTL_RZCEN_Msk;
    else
        i2s->CTL &= ~I2S_CTL_LZCEN_Msk;
}

/**
  * @brief  Enable I2S Tx DMA function. I2S requests DMA to transfer data to Tx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_ENABLE_TXDMA(i2s)  ( (i2s)->CTL |= I2S_CTL_TXPDMAEN_Msk )

/**
  * @brief  Disable I2S Tx DMA function. I2S requests DMA to transfer data to Tx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_DISABLE_TXDMA(i2s) ( (i2s)->CTL &= ~I2S_CTL_TXPDMAEN_Msk )

/**
  * @brief  Enable I2S Rx DMA function. I2S requests DMA to transfer data from Rx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_ENABLE_RXDMA(i2s) ( (i2s)->CTL |= I2S_CTL_RXPDMAEN_Msk )

/**
  * @brief  Disable I2S Rx DMA function. I2S requests DMA to transfer data from Rx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_DISABLE_RXDMA(i2s) ( (i2s)->CTL &= ~I2S_CTL_RXPDMAEN_Msk )

/**
  * @brief  Enable I2S Tx function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_ENABLE_TX(i2s) ( (i2s)->CTL |= I2S_CTL_TXEN_Msk )

/**
  * @brief  Disable I2S Tx function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_DISABLE_TX(i2s) ( (i2s)->CTL &= ~I2S_CTL_TXEN_Msk )

/**
  * @brief  Enable I2S Rx function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_ENABLE_RX(i2s) ( (i2s)->CTL |= I2S_CTL_RXEN_Msk )

/**
  * @brief  Disable I2S Rx function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_DISABLE_RX(i2s) ( (i2s)->CTL &= ~I2S_CTL_RXEN_Msk )

/**
  * @brief  Enable Tx Mute function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_ENABLE_TX_MUTE(i2s)  ( (i2s)->CTL |= I2S_CTL_MUTE_Msk )

/**
  * @brief  Disable Tx Mute function .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_DISABLE_TX_MUTE(i2s) ( (i2s)->CTL &= ~I2S_CTL_MUTE_Msk )

/**
  * @brief  Clear Tx FIFO. Internal pointer is reset to FIFO start point.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_CLR_TX_FIFO(i2s) ( (i2s)->CTL |= I2S_CTL_TXCLR_Msk )

/**
  * @brief  Clear Rx FIFO. Internal pointer is reset to FIFO start point.
  * @param[in] i2s is the base address of I2S module.
  * @return none
  * \hideinitializer
  */
#define I2S_CLR_RX_FIFO(i2s) ( (i2s)->CTL |= I2S_CTL_RXCLR_Msk )

/**
  * @brief  This function sets the recording source channel when mono mode is used.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Ch left or right channel. Valid values are:
  *                - \ref I2S_MONO_LEFT
  *                - \ref I2S_MONO_RIGHT
  * @return none
  * \hideinitializer
  */
static __INLINE void I2S_SET_MONO_RX_CHANNEL(I2S_T *i2s, uint32_t u32Ch)
{
    u32Ch == I2S_MONO_LEFT ?
    (i2s->CTL |= I2S_CTL_RXLCH_Msk) :
    (i2s->CTL &= ~I2S_CTL_RXLCH_Msk);
}

/**
  * @brief  Write data to I2S Tx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Data: The data written to FIFO.
  * @return none
  * \hideinitializer
  */
#define I2S_WRITE_TX_FIFO(i2s, u32Data)  ( (i2s)->TX = u32Data )

/**
  * @brief  Read Rx FIFO.
  * @param[in] i2s is the base address of I2S module.
  * @return Data in Rx FIFO.
  * \hideinitializer
  */
#define I2S_READ_RX_FIFO(i2s) ( (i2s)->RX )

/**
  * @brief  This function gets the interrupt flag according to the mask parameter.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Mask is the mask for the all interrupt flags.
  * @return The masked bit value of interrupt flag.
  * \hideinitializer
  */
#define I2S_GET_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS & (u32Mask) )

/**
  * @brief  This function clears the interrupt flag according to the mask parameter.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Mask is the mask for the all interrupt flags.
  * @return none
  * \hideinitializer
  */
#define I2S_CLR_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS |= (u32Mask) )

/**
  * @brief  Get transmit FIFO level
  * @param[in] i2s is the base address of I2S module.
  * @return FIFO level
  * \hideinitializer
  */
#define I2S_GET_TX_FIFO_LEVEL(i2s) ( (((i2s)->STATUS & I2S_STATUS_TXCNT_Msk) >> I2S_STATUS_TXCNT_Pos) & 0xF )

/**
  * @brief  Get receive FIFO level
  * @param[in] i2s is the base address of I2S module.
  * @return FIFO level
  * \hideinitializer
  */
#define I2S_GET_RX_FIFO_LEVEL(i2s) ( (((i2s)->STATUS & I2S_STATUS_RXCNT_Msk) >> I2S_STATUS_RXCNT_Pos) & 0xF )

uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat, uint32_t u32AudioInterface);
void I2S_Close(I2S_T *i2s);
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask);
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask);
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock);
void I2S_DisableMCLK(I2S_T *i2s);
void I2S_SetFIFO(I2S_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold);

/*@}*/ /* end of group NUC472_442_I2S_EXPORTED_FUNCTIONS */


/*@}*/ /* end of group NUC472_442_I2S_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif


#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

