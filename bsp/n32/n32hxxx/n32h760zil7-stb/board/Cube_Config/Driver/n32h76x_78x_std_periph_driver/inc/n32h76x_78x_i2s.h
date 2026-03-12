/** ----------------------------------------------------------------------------
 *         Nationz Technology Software Support  -  NATIONZ  -
 * -----------------------------------------------------------------------------
 * Copyright (c) 2019, Nationz Corporation  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Nationz's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONZ "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------------
 */
/** ****************************************************************************
 * @copyright      Nationz Co.,Ltd
 *                 Copyright (c) 2019 All Rights Reserved
 *******************************************************************************
 * @file     ns3610cm4_spi.h
 * @author
 * @date
 * @version  v1.0.0
 * @brief
 ******************************************************************************/
#ifndef __NS3610CM4_I2S_H
#define __NS3610CM4_I2S_H

/* Includes ------------------------------------------------------------------*/
#include "n32h76x_78x.h"
#include "n32h76x_78x_rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** Bit definition for I2S_RX_FIFO register **/
#define I2S_RX_FIFO            ((uint16_t)0xFFFF)

/** Bit definition for I2S_FIFO_BURST_NUM register **/
#define I2S_FIFO_BURST_NUM_TX  ((uint16_t)0x0007)   /* I2S TX FIFO Half Empty Threshold Value Configure */
#define I2S_FIFO_BURST_NUM_RX  ((uint16_t)0x0070)   /* I2S RX FIFO Half Full Threshold Value Configure */

/** Bit definition for I2S_FIFO_NUM register **/
#define I2S_FIFO_NUM_TX_CNT ((uint16_t)0x000F)      /* I2S TX FIFO Valid Data Number */
#define I2S_FIFO_NUM_RX_CNT ((uint16_t)0x00F0)      /* I2S RX FIFO Valid Data Number */

/** Bit definition for I2S_TRANS_NUM register **/
#define I2S_TRANS_NUM       ((uint16_t)0xFFFF)

/** Bit definition for I2S_I2SCFG register **/
#define I2SCFG_I2SEN        ((uint16_t)0x0001)      /* I2S Enable */
#define SPI_I2SCFG_MOD      ((uint16_t)0x0002)      /* I2S Mode */

#define I2SCFG_STD          ((uint16_t)0x000C)      /* STD[3:2] bits (I2S standard selection) */
#define I2SCFG_STDSEL1      ((uint16_t)0x0008)      /* Bit 1 */
#define I2SCFG_STDSEL0      ((uint16_t)0x0004)      /* Bit 0 */
												    
#define I2SCFG_TDATLEN      ((uint16_t)0x00C0)      /* TDATLEN[1:0] bits (Data length to be transferred) */
#define I2SCFG_TDATLEN1     ((uint16_t)0x0080)      /* Bit 1 */
#define I2SCFG_TDATLEN0     ((uint16_t)0x0040)      /* Bit 0 */
												    
#define I2SCFG_CHLEN        ((uint16_t)0x0100)      /* Channel Length */
#define I2SCFG_PCMFSYNC     ((uint16_t)0x0200)      /* PCM frame synchronization */
#define I2SCFG_CLKPOL       ((uint16_t)0x0400)      /* steady state clock polarity */
#define I2SCFG_ERR_BYPASS   ((uint16_t)0x0800)      /* PCM Long for 13bit is No bypass */

/** Bit definition for SPI_I2SPR register **/
#define I2SPR_I2SDIV        ((uint16_t)0x00FF)      /* I2S Linear prescaler */
#define I2SPR_ODD           ((uint16_t)0x0100)      /* Odd factor for the prescaler */
#define I2SPR_MCKOEN        ((uint16_t)0x0800)      /* Master Clock Output Enable */

/* -------------------------- Up is the Bit Define -------------------------------- */

/** I2s Mode select**/
#define I2S_MODE_SEL_MASK   (~SPI_I2SCFG_MOD)       /* selet spi/I2S mode bit */
#define SEL_SPI_MODE        ((uint16_t)0x0000) 
#define SEL_I2S_MODE        (SPI_I2SCFG_MOD)


#define I2SCFG_CFG      ((uint16_t)0x0030)      /* I2S Mode Configure */
#define I2SCFG_CFG1     ((uint16_t)0x0020)      /* I2S Mode Configure Bit */
#define I2SCFG_CFG0     ((uint16_t)0x0010)      /* I2S Mode Configure Bit */
/** I2sMode **/
#define I2S_MODE_SlAVE_TX         ((uint16_t)0x0000U)
#define I2S_MODE_SlAVE_RX         (I2SCFG_CFG0)
#define I2S_MODE_MASTER_TX        (I2SCFG_CFG1)
#define I2S_MODE_MASTER_RX        (I2SCFG_CFG0 | I2SCFG_CFG1)
#define I2S_MODE_MASK             (I2SCFG_CFG) /* MODCFG bit Mask */
     

																			  
/** I2S_EXT_DMA_transfer_requests **/
#define I2S_EXT_DMA_TX                ((uint16_t)0x0004U)
#define I2S_EXT_DMA_RX                ((uint16_t)0x0002U)
/** I2S_EXT_interrupts_definition **/
#define I2S_EXT_INT_TEINTEN           ((uint16_t)0x0010U)
#define I2S_EXT_INT_RNEINTEN          ((uint16_t)0x0020U)
#define I2S_EXT_INT_ERRINTEN          ((uint16_t)0x0040U)
																	    																    
/** I2S_EXT_flags_definition **/      
#define I2S_EXT_TE_FLAG     			    ((uint16_t)0x0001U) 
#define I2S_EXT_RNE_FLAG    			    ((uint16_t)0x0002U) 
#define I2S_EXT_BUSY_FLAG   			    ((uint16_t)0x0004U) 
#define I2S_EXT_OVER_FLAG   			    ((uint16_t)0x0020U) 
#define I2S_EXT_UNDER_FLAG  			    ((uint16_t)0x0040U) 
#define I2S_EXT_CHSIDE_FLAG 			    ((uint16_t)0x0080U) 
																			 
/** I2S_interrupts_definition **/
#define I2S_INT_TE                ((uint8_t)0x40)
#define I2S_INT_RNE               ((uint8_t)0x51)
#define I2S_INT_ERR               ((uint8_t)0x60)
#define I2S_INT_RXONLYC           ((uint8_t)0xEC)
#define I2S_INT_RXFIFOF           ((uint8_t)0xCB)
#define I2S_INT_RXFIFOHF          ((uint8_t)0xB9)
#define I2S_INT_TXFIFOHE          ((uint8_t)0xA8)
#define I2S_INT_MODERR            ((uint8_t)0x64)
#define I2S_INT_CRCERR            ((uint8_t)0x63)
#define I2S_INT_OVERERR           ((uint8_t)0x65)
#define I2S_INT_UNDER             ((uint8_t)0x66)
																	    

/** I2S_flags_definition **/
#define I2S_TE_FLAG           		((uint16_t)0x0001U)
#define I2S_RNE_FLAG          		((uint16_t)0x0002U)
#define I2S_BUSY_FLAG         		((uint16_t)0x0004U)
#define I2S_CRCERR_FLAG           ((uint16_t)0x0008U)
#define I2S_MODERR_FLAG           ((uint16_t)0x0010U)
#define I2S_OVER_FLAG         		((uint16_t)0x0020U)
#define I2S_UNDER_FLAG            ((uint16_t)0x0040U)
#define I2S_CHSIDE_FLAG           ((uint16_t)0x0080U)
#define I2S_TXFIFOHE_FLAG         ((uint16_t)0x0100U)
#define I2S_RXFIFOHF_FLAG         ((uint16_t)0x0200U)
#define I2S_TXFIFOE_FLAG          ((uint16_t)0x0400U)
#define I2S_RXFIFOF_FLAG          ((uint16_t)0x0800U)
#define I2S_RXONLYC_FLAG          ((uint16_t)0x1000U)

/** I2S_DMA_transfer_requests **/

#define I2S_DMA_TX                ((uint16_t)0x0004U)
#define I2S_DMA_RX                ((uint16_t)0x0002U)

/** I2S Init structure definition **/

typedef struct
{
    uint16_t I2sMode;           /*!< Specifies the I2S operating mode.
                                     This parameter can be a value of @ref I2sMode */
														    
    uint16_t Standard;          /*!< Specifies the standard used for the I2S communication.
                                     This parameter can be a value of @ref Standard */
														    
    uint16_t DataFormat;        /*!< Specifies the data format for the I2S communication.
                                     This parameter can be a value of @ref I2S_Data_Format */
														    
    uint16_t MCLKEnable;        /*!< Specifies whether the I2S MCLK output is enabled or not.
                                     This parameter can be a value of @ref I2S_MCLK_Output */
														    
    uint32_t AudioFrequency;    /*!< Specifies the frequency selected for the I2S communication.
                                     This parameter can be a value of @ref I2S_Audio_Frequency */
														    
    uint16_t CLKPOL;            /*!< Specifies the idle state of the I2S clock.
                                     This parameter can be a value of @ref I2S_Clock_Polarity */  
	  uint32_t ClkSrcFrequency;   /*!< Specifies the I2S clock source frequency in Hz.*/
} I2S_InitType;


/**  Standard **/
#define I2S_STD_PHILLIPS          ((uint16_t)0x0000U)
#define I2S_STD_MSB_ALIGN         (I2SCFG_STDSEL0)
#define I2S_STD_LSB_ALIGN         (I2SCFG_STDSEL1)
#define I2S_STD_PCM_SHORTFRAME    (I2SCFG_STDSEL0 | I2SCFG_STDSEL1)
#define I2S_STD_PCM_LONGFRAME     (I2SCFG_STDSEL0 | I2SCFG_STDSEL1 | I2SCFG_PCMFSYNC)
#define I2S_STANDARD_MASK         (I2SCFG_STD) /* STDSEL and PCMFSYNC bit Mask */


/** I2S_Data_Format **/
#define I2S_DATA_FORMAT_MASK          (~(I2SCFG_CHLEN | I2SCFG_TDATLEN)) /* CHBITS and TDATLEN bit Mask */
#define I2S_DATA_FMT_16BITS           ((uint16_t)0x0000U)
#define I2S_DATA_FMT_16BITS_EXTENDED  (I2SCFG_CHLEN)
#define I2S_DATA_FMT_24BITS           (I2SCFG_CHLEN | I2SCFG_TDATLEN0)
#define I2S_DATA_FMT_32BITS           (I2SCFG_CHLEN | I2SCFG_TDATLEN1)

/** I2S_MCLK_Output **/

#define I2S_MCLK_ENABLE              ((uint16_t)0x0800U)
#define I2S_MCLK_DISABLE             ((uint16_t)0x0000U)


/** I2S_Audio_Frequency **/

#define I2S_AUDIO_FREQ_192K           ((uint32_t)192000U)
#define I2S_AUDIO_FREQ_96K            ((uint32_t)96000U)
#define I2S_AUDIO_FREQ_48K            ((uint32_t)48000U)
#define I2S_AUDIO_FREQ_44K            ((uint32_t)44100U)
#define I2S_AUDIO_FREQ_32K            ((uint32_t)32000U)
#define I2S_AUDIO_FREQ_22K            ((uint32_t)22050U)
#define I2S_AUDIO_FREQ_16K            ((uint32_t)16000U)
#define I2S_AUDIO_FREQ_11K            ((uint32_t)11025U)
#define I2S_AUDIO_FREQ_8K             ((uint32_t)8000U)
#define I2S_AUDIO_FREQ_DEFAULT        ((uint32_t)2U)

/** I2S_Clock_Polarity **/
#define I2S_CLKPOL_LOW                ((uint16_t)0x0000U)
#define I2S_CLKPOL_HIGH               (SPI_I2SCFG_CLKPOL)
#define I2S_CLKPOL_MASK               (~SPI_I2SCFG_CLKPOL) /* MCLKOEN bit Mask */

/** I2S Converter **/                   
#define I2S_TURN_ON                   (I2SCFG_I2SEN | SPI_I2SCFG_MOD)       /* I2SEN and MODSEL bit */
#define I2S_TURN_OFF                  (~(I2SCFG_I2SEN | SPI_I2SCFG_MOD))    /* I2SEN  bit Mask */

///** I2S_EXT_DMA_transfer_requests **/

#define I2S_EXT_DMA_TX                ((uint16_t)0x0004U)
#define I2S_EXT_DMA_RX                ((uint16_t)0x0002U)

void I2S_Reset(I2S_Module* I2Sx);
void I2S_EnableInt(I2S_Module* I2Sx, uint8_t I2S_IT, FunctionalState Cmd);
FlagStatus I2S_GetStatus(I2S_Module* I2Sx, uint8_t i2s_flag);
INTStatus I2S_GetIntStatus(const I2S_Module* I2sx, uint8_t I2S_IT);
void I2S_ClrITPendingBit(I2S_Module* I2Sx, uint8_t I2S_IT);
void I2S_TransmitData(I2S_Module* I2Sx, uint16_t Data);
uint16_t I2S_ReceiveData(I2S_Module* I2Sx);
void I2S_EnableDma(I2S_Module* I2Sx, uint16_t I2S_DMAReq, FunctionalState Cmd);
void I2S_Init(I2S_Module* I2Sx,const I2S_InitType* I2S_InitStruct);
void I2S_Enable(I2S_Module* I2Sx, FunctionalState Cmd);
void I2S_InitStruct(I2S_InitType* I2S_InitStruct);
void I2S_MclkEnable(I2S_Module* I2Sx, FunctionalState Cmd);
void I2S_StandardConfig(I2S_Module* I2Sx, uint16_t Standard);
void I2S_ModeConfig(I2S_Module* I2Sx, uint16_t I2sMode);
void I2S_DataFormatConfig(I2S_Module* I2Sx, uint16_t DataFormat);
void I2S_ClkPolConfig(I2S_Module* I2Sx, uint16_t CLKPOL);
void I2S_AudioFrequencyConfig(I2S_Module* I2Sx, uint32_t AudioFrequency);
void I2S_EXTInit(I2S_EXT_Module* I2Sx_EXT,const I2S_InitType* I2S_EXT_InitStruct);
void I2S_EXTInitStruct(I2S_InitType* I2S_EXT_InitStruct);
void I2S_EXTEnable(I2S_EXT_Module* I2Sx_EXT, FunctionalState Cmd);
void I2S_EXTTransmitData(I2S_EXT_Module* I2Sx, uint16_t Data);
uint16_t  I2S_EXTReceiveData(const I2S_EXT_Module* I2Sx);
FlagStatus I2S_EXTGetStatus(const I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_FLAG);
void I2S_EXTEnableDma(I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_DMAReq, FunctionalState Cmd);
void I2S_EXTEnableInt(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT, FunctionalState Cmd);
void I2S_SPIModeSelect(I2S_Module* I2Sx, uint16_t Mode);
INTStatus I2S_EXTGetIntStatus(const I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT);
void I2S_DataFifoTransmit(I2S_Module* I2Sx, uint16_t Data);
uint16_t I2S_DataFifoGet(I2S_Module* I2Sx);
void I2S_EXTClrITPendingBit(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT);

#ifdef __cplusplus
}

#endif
#endif /*__NS3610CM4_I2S_H */


/******************* (C) COPYRIGHT 2019 NATIONZ *****END OF FILE****/
