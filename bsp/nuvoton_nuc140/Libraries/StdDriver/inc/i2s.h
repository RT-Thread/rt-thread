/**************************************************************************//**
 * @file     i2s.h
 * @version  V3.0
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    I2S driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __I2S_H__
#define __I2S_H__


#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2S_Driver I2S Driver
  @{
*/

/** @addtogroup I2S_EXPORTED_CONSTANTS I2S Exported Constants
  @{
*/
#define I2S_DATABIT_8           (0 << I2S_CON_WORDWIDTH_Pos)       /*!< I2S data width is 8-bit */
#define I2S_DATABIT_16          (1 << I2S_CON_WORDWIDTH_Pos)       /*!< I2S data width is 16-bit */
#define I2S_DATABIT_24          (2 << I2S_CON_WORDWIDTH_Pos)       /*!< I2S data width is 24-bit */
#define I2S_DATABIT_32          (3 << I2S_CON_WORDWIDTH_Pos)       /*!< I2S data width is 32-bit */

/* Audio Format */
#define I2S_MONO                I2S_CON_MONO_Msk                   /*!< Mono channel */
#define I2S_STEREO              0                                  /*!< Stereo channel */

/* I2S Data Format */
#define I2S_FORMAT_MSB          I2S_CON_FORMAT_Msk                 /*!< MSB data format */
#define I2S_FORMAT_I2S          0                                  /*!< I2S data format */

/* I2S Operation mode */
#define I2S_MODE_SLAVE          I2S_CON_SLAVE_Msk                  /*!< As slave mode */
#define I2S_MODE_MASTER         0                                  /*!< As master mode */

/* I2S FIFO Threshold */
#define I2S_FIFO_TX_LEVEL_WORD_0    0                              /*!< TX threshold is 0 word */
#define I2S_FIFO_TX_LEVEL_WORD_1    (1 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 1 word */
#define I2S_FIFO_TX_LEVEL_WORD_2    (2 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 2 words */
#define I2S_FIFO_TX_LEVEL_WORD_3    (3 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 3 words */
#define I2S_FIFO_TX_LEVEL_WORD_4    (4 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 4 words */
#define I2S_FIFO_TX_LEVEL_WORD_5    (5 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 5 words */
#define I2S_FIFO_TX_LEVEL_WORD_6    (6 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 6 words */
#define I2S_FIFO_TX_LEVEL_WORD_7    (7 << I2S_CON_TXTH_Pos)        /*!< TX threshold is 7 words */

#define I2S_FIFO_RX_LEVEL_WORD_1    0                              /*!< RX threshold is 1 word */
#define I2S_FIFO_RX_LEVEL_WORD_2    (1 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 2 words */
#define I2S_FIFO_RX_LEVEL_WORD_3    (2 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 3 words */
#define I2S_FIFO_RX_LEVEL_WORD_4    (3 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 4 words */
#define I2S_FIFO_RX_LEVEL_WORD_5    (4 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 5 words */
#define I2S_FIFO_RX_LEVEL_WORD_6    (5 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 6 words */
#define I2S_FIFO_RX_LEVEL_WORD_7    (6 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 7 words */
#define I2S_FIFO_RX_LEVEL_WORD_8    (7 << I2S_CON_RXTH_Pos)        /*!< RX threshold is 8 words */

/* I2S Record Channel */
#define I2S_MONO_RIGHT          0                                  /*!< Record mono right channel */
#define I2S_MONO_LEFT           I2S_CON_RXLCH_Msk                  /*!< Record mono left channel */

/* I2S Channel */
#define I2S_RIGHT               0                                  /*!< Select right channel */
#define I2S_LEFT                1                                  /*!< Select left channel */

/*@}*/ /* end of group I2S_EXPORTED_CONSTANTS */

/** @addtogroup I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/**
  * @brief  Enable zero cross detection function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return None
  * @details This function will set RCHZCEN or LCHZCEN bit of I2SCON register to enable zero cross detection function.
  */
static __INLINE void I2S_ENABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CON |= I2S_CON_RCHZCEN_Msk;
    else
        i2s->CON |= I2S_CON_LCHZCEN_Msk;
}

/**
  * @brief  Disable zero cross detection function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return None
  * @details This function will clear RCHZCEN or LCHZCEN bit of I2SCON register to disable zero cross detection function.
  */
static __INLINE void I2S_DISABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CON &= ~I2S_CON_RCHZCEN_Msk;
    else
        i2s->CON &= ~I2S_CON_LCHZCEN_Msk;
}

/**
  * @brief  Enable I2S TX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set TXDMA bit of I2SCON register to transmit data with PDMA.
  */
#define I2S_ENABLE_TXDMA(i2s)  ( (i2s)->CON |= I2S_CON_TXDMA_Msk )

/**
  * @brief  Disable I2S TX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TXDMA bit of I2SCON register to disable TX DMA function.
  */
#define I2S_DISABLE_TXDMA(i2s) ( (i2s)->CON &= ~I2S_CON_TXDMA_Msk )

/**
  * @brief  Enable I2S RX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set RXDMA bit of I2SCON register to receive data with PDMA.
  */
#define I2S_ENABLE_RXDMA(i2s) ( (i2s)->CON |= I2S_CON_RXDMA_Msk )

/**
  * @brief  Disable I2S RX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RXDMA bit of I2SCON register to disable RX DMA function.
  */
#define I2S_DISABLE_RXDMA(i2s) ( (i2s)->CON &= ~I2S_CON_RXDMA_Msk )

/**
  * @brief  Enable I2S TX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set TXEN bit of I2SCON register to enable I2S TX function.
  */
#define I2S_ENABLE_TX(i2s) ( (i2s)->CON |= I2S_CON_TXEN_Msk )

/**
  * @brief  Disable I2S TX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TXEN bit of I2SCON register to disable I2S TX function.
  */
#define I2S_DISABLE_TX(i2s) ( (i2s)->CON &= ~I2S_CON_TXEN_Msk )

/**
  * @brief  Enable I2S RX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set RXEN bit of I2SCON register to enable I2S RX function.
  */
#define I2S_ENABLE_RX(i2s) ( (i2s)->CON |= I2S_CON_RXEN_Msk )

/**
  * @brief  Disable I2S RX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RXEN bit of I2SCON register to disable I2S RX function.
  */
#define I2S_DISABLE_RX(i2s) ( (i2s)->CON &= ~I2S_CON_RXEN_Msk )

/**
  * @brief  Enable TX Mute function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set MUTE bit of I2SCON register to enable I2S TX mute function.
  */
#define I2S_ENABLE_TX_MUTE(i2s)  ( (i2s)->CON |= I2S_CON_MUTE_Msk )

/**
  * @brief  Disable TX Mute function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear MUTE bit of I2SCON register to disable I2S TX mute function.
  */
#define I2S_DISABLE_TX_MUTE(i2s) ( (i2s)->CON &= ~I2S_CON_MUTE_Msk )

/**
  * @brief  Clear TX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TX FIFO. The internal TX FIFO pointer will be reset to FIFO start point.
  */
#define I2S_CLR_TX_FIFO(i2s) ( (i2s)->CON |= I2S_CON_CLR_TXFIFO_Msk )

/**
  * @brief  Clear RX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RX FIFO. The internal RX FIFO pointer will be reset to FIFO start point.
  */
#define I2S_CLR_RX_FIFO(i2s) ( (i2s)->CON |= I2S_CON_CLR_RXFIFO_Msk )

/**
  * @brief  This function sets the recording source channel when mono mode is used.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Ch Left or right channel. Valid values are:
  *                - \ref I2S_MONO_LEFT
  *                - \ref I2S_MONO_RIGHT
  * @return None
  * @details This function selects the recording source channel of monaural mode.
  */
static __INLINE void I2S_SET_MONO_RX_CHANNEL(I2S_T *i2s, uint32_t u32Ch)
{
    u32Ch == I2S_MONO_LEFT ?
    (i2s->CON |= I2S_CON_RXLCH_Msk) :
    (i2s->CON &= ~I2S_CON_RXLCH_Msk);
}

/**
  * @brief  Write data to I2S TX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Data The value written to TX FIFO.
  * @return None
  * @details This macro will write a value to TX FIFO.
  */
#define I2S_WRITE_TX_FIFO(i2s, u32Data)  ( (i2s)->TXFIFO = (u32Data) )

/**
  * @brief  Read RX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return The value read from RX FIFO.
  * @details This function will return a value read from RX FIFO.
  */
#define I2S_READ_RX_FIFO(i2s) ( (i2s)->RXFIFO )

/**
  * @brief  Get the interrupt flag.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return The interrupt flags specified by the u32mask parameter.
  * @details This macro will return the combination flags of I2SSTATUS register. The flags are specified by the u32mask parameter.
  */
#define I2S_GET_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS & (u32Mask) )

/**
  * @brief  Clear the interrupt flag.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return None
  * @details This macro will clear the interrupt flags specified by the u32mask parameter.
  */
#define I2S_CLR_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS = (u32Mask) )

/**
  * @brief  Get transmit FIFO level
  * @param[in] i2s The pointer of the specified I2S module.
  * @return TX FIFO level
  * @details This macro will return the number of available words in TX FIFO.
  */
#define I2S_GET_TX_FIFO_LEVEL(i2s) ( (((i2s)->STATUS & I2S_STATUS_TX_LEVEL_Msk) >> I2S_STATUS_TX_LEVEL_Pos) & 0xF )

/**
  * @brief  Get receive FIFO level
  * @param[in] i2s The pointer of the specified I2S module.
  * @return RX FIFO level
  * @details This macro will return the number of available words in RX FIFO.
  */
#define I2S_GET_RX_FIFO_LEVEL(i2s) ( (((i2s)->STATUS & I2S_STATUS_RX_LEVEL_Msk) >> I2S_STATUS_RX_LEVEL_Pos) & 0xF )


/* Function prototype declaration */
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat);
void I2S_Close(I2S_T *i2s);
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask);
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask);
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock);
void I2S_DisableMCLK(I2S_T *i2s);

/*@}*/ /* end of group I2S_EXPORTED_FUNCTIONS */


/*@}*/ /* end of group I2S_Driver */

/*@}*/ /* end of group Device_Driver */

#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

