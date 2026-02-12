/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_i2s.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_i2s.h"
#include "n32h76x_78x_spi.h"
#include "n32h76x_78x.h"


/* SPI registers Masks */
#define CTRL1_CLR_MASK  			      ((uint16_t)0xF9F7U)
#define I2SCFG_CLR_MASK 			      ((uint16_t)0x05FCU)
#define I2SPR_CLEAR_Mask            ((uint16_t)0x0FFFU)

/* SPI or I2S mode selection masks */
#define SPI_MODE_ENABLE             ((uint16_t)0xFFFDU)
#define I2S_MODE_ENABLE             ((uint16_t)0x0002U)

/* I2S I2SE mask */
#define I2SCFG_I2SEN_ENABLE         ((uint16_t)0x0001U)
#define I2SCFG_I2SEN_DISABLE        ((uint16_t)0xFFFEU)



/**
*\*\name    I2S_InitStruct.
*\*\fun     Fills each I2S_InitStruct member with its default value.
*\*\param   I2S_InitStruct :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - MCLKEnable
*\*\          - AudioFrequency
*\*\          - CLKPOL
*\*\return  none
**/
void I2S_InitStruct(I2S_InitType* I2S_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the MCLKEnable member */
    I2S_InitStruct->MCLKEnable = I2S_MCLK_DISABLE;

    /* Initialize the AudioFrequency member */
    I2S_InitStruct->ClkSrcFrequency = I2S_AUDIO_FREQ_DEFAULT;

    /* Initialize the CLKPOL member */
    I2S_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}


/**
*\*\name    I2S_Mode_Select.
*\*\fun     Select working on SPI mode or I2S mode.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   Mode :
*\*\          - SEL_SPI_Mode
*\*\          - SEL_I2S_Mode
*\*\return  none
*\*\note    Must be used with I2S or SPI OFF.
**/
void I2S_SPIModeSelect(I2S_Module* I2Sx, uint16_t Mode)
{
    /* Clear MODSEL bit */
    I2Sx->I2SCFGR &= I2S_MODE_MASK;
    /* Select the mode */
    I2Sx->I2SCFGR |= Mode;
}

/**
*\*\name    I2S_Mode_Config.
*\*\fun     Config the I2s I2sMode.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   I2sMode :
*\*\          - I2S_MODE_SlAVE_TX
*\*\          - I2S_MODE_SlAVE_RX
*\*\          - I2S_MODE_MASTER_TX
*\*\          - I2S_MODE_MASTER_RX
*\*\return  none
*\*\note    Must be used with I2S OFF.
**/
void I2S_ModeConfig(I2S_Module* I2Sx, uint16_t I2sMode)
{
    /* Clear SPI_I2SCFGR MODCFG bits */
    I2Sx->I2SCFGR &= I2S_MODE_MASK;
    /* Set SPI_I2SCFGR MODCFG bits */
    I2Sx->I2SCFGR |= I2sMode;
}

/**
*\*\name    I2S_Standard_Config.
*\*\fun     Config the I2s Standard.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   I2sMode :
*\*\          - I2S_STD_PHILLIPS
*\*\          - I2S_STD_MSB_ALIGN
*\*\          - I2S_STD_LSB_ALIGN
*\*\          - I2S_STD_PCM_SHORTFRAME
*\*\          - I2S_STD_PCM_LONGFRAME
*\*\return  none
**/
void I2S_StandardConfig(I2S_Module* I2Sx, uint16_t Standard)
{
    /* Clear SPI_I2SCFGR STDSEL and PCMFSYNC bit */
    I2Sx->I2SCFGR &= I2S_STANDARD_MASK;
    /* Set SPI_I2SCFGR STDSEL and PCMFSYNC bit */
    I2Sx->I2SCFGR |= Standard;
}

/**
*\*\name    I2S_DataFormat_Config.
*\*\fun     Config the I2s DataFormat.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   DataFormat :
*\*\          - I2S_DATA_FMT_16BITS
*\*\          - I2S_DATA_FMT_16BITS_EXTENDED
*\*\          - I2S_DATA_FMT_24BITS
*\*\          - I2S_DATA_FMT_32BITS
*\*\return  none
**/
void I2S_DataFormatConfig(I2S_Module* I2Sx, uint16_t DataFormat)
{
    /* Clear SPI_I2SCFGR CHBITS and TDATLEN bit */
    I2Sx->I2SCFGR &= I2S_DATA_FORMAT_MASK;
    /* Set SPI_I2SCFGR CHBITS and TDATLEN bit */
    I2Sx->I2SCFGR |= DataFormat;
}

/**
*\*\name    I2S_MCLK_Enable.
*\*\fun     Enable the I2s MCLK.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_MclkEnable(I2S_Module* I2Sx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set SPI_I2SPREDIV MCLKOEN bit */
        I2Sx->I2SPR |= I2S_MCLK_ENABLE;
    }
    else
    {
        /* Clear SPI_I2SPREDIV MCLKOEN bit */
        I2Sx->I2SPR &= I2S_MCLK_DISABLE;
    }
}

/**
*\*\name    I2S_Config_MCLKEnable_And_AudioFrequency.
*\*\fun     Config the I2s MCLKEnable and AudioFrequency.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   AudioFrequency :
*\*\          - I2S_AUDIO_FREQ_192K
*\*\          - I2S_AUDIO_FREQ_96K
*\*\          - I2S_AUDIO_FREQ_48K
*\*\          - I2S_AUDIO_FREQ_44K
*\*\          - I2S_AUDIO_FREQ_32K
*\*\          - I2S_AUDIO_FREQ_22K
*\*\          - I2S_AUDIO_FREQ_16K
*\*\          - I2S_AUDIO_FREQ_11K
*\*\          - I2S_AUDIO_FREQ_8K
*\*\          - I2S_AUDIO_FREQ_DEFAULT
*\*\return  none
**/
void I2S_AudioFrequencyConfig(I2S_Module* I2Sx, uint32_t AudioFrequency)
{
    uint16_t i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0;///
    RCC_ClocksTypeDef RCC_Clocks;
    uint32_t sourceclock = 0;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
    if (AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    else
    {
        /* Check the frame length (For the SPI_I2SCFGR CHBITSbit) */
        if (I2Sx->I2SCFGR & SPI_I2SCFG_CHLEN)
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }
        else
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }

        /* I2S Clock source is System clock: Get System Clock frequency */
        RCC_GetClocksFreqValue(&RCC_Clocks);

        /* Get the source clock value: based on System Clock value */
        sourceclock = RCC_Clocks.SysClkFreq;

        /* Compute the Real divider depending on the MCLK output state with a floating point */
        /* Get the I2Sx->I2SPREDIV MCLKOEN bit state */
        if (I2Sx->I2SPR & I2S_MCLK_ENABLE)
        {
            /* MCLK output is enabled */
            tmp = (uint16_t)(((((sourceclock / 256) * 10) / AudioFrequency)) + 5);
        }
        else
        {
            /* MCLK output is disabled */
            tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10) / AudioFrequency)) + 5);
        }

        /* Remove the floating point */
        tmp = tmp / 10;

        /* Check the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

        /* Get the Mask for the Odd bit (SPI_I2SPREDIV[8]) register */
        i2sodd = (uint16_t)(i2sodd << 8);
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0xFF))
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to I2Sx I2SPREDIV register the computed value */
    I2Sx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (I2Sx->I2SPR & I2S_MCLK_ENABLE)));
}

/**
*\*\name    I2S_CLKPOL_Config.
*\*\fun     Config the I2s CLKPOL.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   CLKPOL :
*\*\          - I2S_CLKPOL_LOW
*\*\          - I2S_CLKPOL_HIGH
*\*\return  none
**/
void I2S_ClkPolConfig(I2S_Module* I2Sx, uint16_t CLKPOL)
{
    /* Clear SPI_I2SPREDIV CLKPOL bit */
    I2Sx->I2SCFGR &= I2S_CLKPOL_MASK;
    /* Set SPI_I2SPREDIV CLKPOL bit */
    I2Sx->I2SCFGR |= CLKPOL;
}


/**
*\*\name    SPI_I2S_EnableInt.
*\*\fun     Enables or disables the specified SPI/I2S interrupts.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_IT :
*\*\         - SPI_I2S_INT_TE
*\*\         - SPI_I2S_INT_RNE
*\*\      	 - SPI_I2S_INT_ERR
*\*\      	 - SPI_I2S_INT_RXONLYC
*\*\      	 - SPI_I2S_INT_RXFIFOF
*\*\      	 - SPI_I2S_INT_RXFIFOHF
*\*\      	 - SPI_I2S_INT_TXFIFOHE
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EnableInt(I2S_Module* I2Sx, uint8_t I2S_IT, FunctionalState Cmd)
{
    uint16_t itpos, itmask;

    /* Get the SPI/I2S IT index */
    itpos = I2S_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S interrupt */
        I2Sx->CR2 |= itmask;
    }
    else
    {
        /* Disable the selected SPI/I2S interrupt */
        I2Sx->CR2 &= (uint16_t)~itmask;
    }
}

/**
*\*\name    I2S_Data_Transmit.
*\*\fun     Transmits a Data through the I2Sx/I2Sx peripheral.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   Data           \* Data to be transmitted *\
*\*\return  none
**/
void I2S_TransmitData(I2S_Module* I2Sx, uint16_t Data)
{
    /* Write in the SPI_DAT register the data to be sent */
    I2Sx->DR = Data;
}

/**
*\*\name    I2S_DataFifoTransmit.
*\*\fun     Transmits a Data using FIFO through the I2Sx/I2Sx peripheral.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\param   Data           \* Data to be transmitted *\
*\*\return  none
**/
void I2S_DataFifoTransmit(I2S_Module* I2Sx, uint16_t Data)
{
    /* Write in the SPI_DAT register the data to be sent */
    I2Sx->DR = Data;
}

/**
*\*\name    I2S_ReceiveData.
*\*\fun     Get SPI/I2S data from SPI_DAT register.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  The data in the SPI_DAT register
**/
uint16_t I2S_ReceiveData(I2S_Module* I2Sx)
{
    /* Return the data in the SPI_DAT register */
    return I2Sx->DR;
}

/**
*\*\name    I2S_DataFifoGet.
*\*\fun     Get SPI/I2S data from RXFIFO register.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  The data in the SPI_DAT register
**/
uint16_t I2S_DataFifoGet(I2S_Module* I2Sx)
{
    /* Return the data in the SPI_DAT register */
    return I2Sx->RXFIFO;
}

/**
*\*\name    I2S_Rx_Fifo_Num_Get.
*\*\fun     Get I2S Receive Data Counter in FIFO.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  The RX FIFO Data Count
**/
uint16_t I2S_Rx_Fifo_Num_Get(I2S_Module* I2Sx)
{
    /* Return The RX  Data Count in FIFO*/
    return ((I2Sx->FIFOCNT & I2S_FIFO_NUM_RX_CNT) >> 4);
}

/**
*\*\name    I2S_Tx_Fifo_Num_Get.
*\*\fun     Get I2S Send Data Counter in FIFO.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  The TX Data Count in FIFO
**/
uint16_t I2S_Tx_Fifo_Num_Get(I2S_Module* I2Sx)
{
    /* Return The TX Data Count in FIFO */
    return ((I2Sx->FIFOCNT & I2S_FIFO_NUM_TX_CNT));
}

/**
*\*\name    I2S_Tx_Fifo_Half_Full_Threshold_Cfg.
*\*\fun     Configure TX FIFO Half Empty Threshold Value.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  None
**/
void I2S_Tx_Fifo_Half_Full_Threshold_Cfg(I2S_Module* I2Sx, uint8_t threshold)
{
    /* Configure TX FIFO Half Empty Threshold Value  */
    I2Sx->FIFONUM |= (threshold & I2S_FIFO_BURST_NUM_TX);
}

/**
*\*\name    I2S_Rx_Fifo_Half_Full_Threshold_Cfg.
*\*\fun     Configure RX FIFO Half Empty Threshold Value.
*\*\param   I2Sx :
*\*\          - I2S1
*\*\          - I2S2
*\*\          - I2S3
*\*\          - I2S4
*\*\return  None
**/
void I2S_Rx_Fifo_Half_Full_Threshold_Cfg(I2S_Module* I2Sx, uint8_t threshold)
{
    /* Configure RX FIFO Half Empty Threshold Value */
    I2Sx->FIFONUM |= ((threshold >> 4) & I2S_FIFO_BURST_NUM_RX);
}

/**
*\*\name    SPI_I2S_GetStatus.
*\*\fun     Checks whether the specified SPI/I2S flag is set or not.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_FLAG :
*\*\				 - SPI_I2S_BUSY_FLAG
*\*\				 - SPI_I2S_OVER_FLAG
*\*\				 - SPI_MODERR_FLAG
*\*\				 - SPI_CRCERR_FLAG
*\*\				 - I2S_UNDER_FLAG
*\*\				 - I2S_CHSIDE_FLAG
*\*\				 - SPI_I2S_TE_FLAG
*\*\				 - SPI_I2S_RNE_FLAG
*\*\				 - SPI_I2S_RXONLYC_FLAG
*\*\				 - SPI_I2S_RXFIFOF_FLAG
*\*\				 - SPI_I2S_TXFIFOE_FLAG
*\*\				 - SPI_I2S_RXFIFOHF_FLAG
*\*\				 - SPI_I2S_TXFIFOHE_FLAG
*\*\return  The new state of SPI_I2S_FLAG (SET or RESET).
**/
FlagStatus I2S_GetStatus(I2S_Module* I2Sx, uint8_t i2s_flag)
{
    FlagStatus bitstatus;

    /* Check the status of the specified SPI/I2S flag */
    if ((I2Sx->SR & i2s_flag) != (uint16_t)RESET)
    {
        /* SPI_I2S_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the SPI_I2S_FLAG status */
    return bitstatus;
}

/**
*\*\name    I2S_GetIntStatus.
*\*\fun     Checks whether the specified SPI/I2S interrupt has occurred or not.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_IT :
*\*\         - SPI_I2S_INT_TE
*\*\         - SPI_I2S_INT_RNE
*\*\         - SPI_I2S_INT_RXONLYC
*\*\         - SPI_I2S_INT_RXFIFOF
*\*\         - SPI_I2S_INT_RXFIFOHF
*\*\         - SPI_I2S_INT_TXFIFOHE
*\*\         - SPI_I2S_INT_CRCERR
*\*\         - SPI_I2S_INT_MODERR
*\*\         - SPI_I2S_INT_OVERERR
*\*\         - I2S_I2S_INT_UNDER
*\*\return  The new state of SPI_I2S_IT (SET or RESET).
**/

INTStatus I2S_GetIntStatus(const I2S_Module* I2sx, uint8_t I2S_IT)
{
    INTStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* Get the SPI/I2S IT index */
    itpos = 0x01 << (I2S_IT & 0x0F);

    /* Get the SPI/I2S IT mask */
    itmask = I2S_IT >> 4;

    /* Set the IT mask */
    itmask = 0x01 << itmask;

    /* Get the SPI_I2S_IT enable bit status */
    enablestatus = (I2sx->CR2 & itmask);

    /* Check the status of the specified SPI/I2S interrupt */
    if (((I2sx->SR & itpos) != (uint16_t)RESET) && enablestatus)
    {
        /* SPI_I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_IT is reset */
        bitstatus = RESET;
    }

    /* Return the SPI_I2S_IT status */
    return bitstatus;
}


/**
*\*\name    I2S_ClrITPendingBit.
*\*\fun     Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_IT :
*\*\				 - SPI_INT_CRCERR
*\*\return  none.
**/
void I2S_ClrITPendingBit(I2S_Module* I2Sx, uint8_t I2S_IT)
{
    uint16_t itpos;

    /* Get the SPI IT index */
    itpos = 0x0001 << (I2S_IT & 0x0F);

    /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
    I2Sx->SR = (uint16_t)~itpos;
}


void I2S_Reset(I2S_Module* I2Sx)
{
    if (I2Sx == I2S1)
    {
        RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_I2S1);
    }

    else if (I2Sx == I2S2)
    {
        RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_I2S2);
    }

    else if (I2Sx == I2S3)
    {
        RCC_EnableAPB1PeriphReset4(RCC_APB1_PERIPHRST_I2S3);
    }

    else if (I2Sx == I2S4)
    {
        RCC_EnableAPB1PeriphReset4(RCC_APB1_PERIPHRST_I2S4);
    }
}

/**
*\*\name    I2S_Init.
*\*\fun     Initializes the SPIx peripheral according to the specified parameters in the I2S_InitStruct.
*\*\param   SPIx :
*\*\          - SPI2
*\*\          - SPI3
*\*\param   I2S_InitStruct :
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX
*\*\           - I2S_MODE_SlAVE_RX
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS
*\*\           - I2S_STD_MSB_ALIGN
*\*\           - I2S_STD_LSB_ALIGN
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED
*\*\           - I2S_DATA_FMT_24BITS
*\*\           - I2S_DATA_FMT_32BITS
*\*\          - MCLKEnable
*\*\           - I2S_MCLK_ENABLE
*\*\           - I2S_MCLK_DISABLE
*\*\          - AudioFrequency
*\*\           - I2S_AUDIO_FREQ_192K
*\*\           - I2S_AUDIO_FREQ_96K
*\*\           - I2S_AUDIO_FREQ_48K
*\*\           - I2S_AUDIO_FREQ_44K
*\*\           - I2S_AUDIO_FREQ_32K
*\*\           - I2S_AUDIO_FREQ_22K
*\*\           - I2S_AUDIO_FREQ_16K
*\*\           - I2S_AUDIO_FREQ_11K
*\*\           - I2S_AUDIO_FREQ_8K
*\*\           - I2S_AUDIO_FREQ_DEFAULT
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW
*\*\           - I2S_CLKPOL_HIGH
*\*\          - ClkSrcFrequency
*\*\           - RCC_Clocks.SysclkFreq
*\*\           - RCC_Clocks.HclkFreq
*\*\           - RCC_Clocks.Pclk1Freq
*\*\           - RCC_Clocks.Pclk2Freq
*\*\           - RCC_Clocks.AdcPllClkFreq
*\*\           - RCC_Clocks.AdcHclkFreq
*\*\           - RCC_Clocks.ShrtpllFreq
*\*\           - user defined
**/
void I2S_Init(I2S_Module* I2Sx, const I2S_InitType* I2S_InitStruct)
{
    uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0;
//    RCC_ClocksTypeDef RCC_Clocks;
    uint32_t sourceclock = 0;


    /*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
    /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
    I2Sx->I2SCFGR &= I2SCFG_CLR_MASK;
    I2Sx->I2SPR = 0x0002;

    /* Get the I2SCFGR register value */
    tmpreg = I2Sx->I2SCFGR;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/

    if (I2S_InitStruct->AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = ( uint16_t )0;
        i2sdiv = ( uint16_t )2;
    }

    /* If the requested audio frequency is not the default, compute the prescaler */
    else
    {
        /* Check the frame length (For the Prescaler computing) */
        if ( I2S_InitStruct->DataFormat == I2S_DATA_FMT_16BITS )
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }
        else
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }

        /* Get the source clock value: based on System Clock value */
        sourceclock = I2S_InitStruct->ClkSrcFrequency;

        /* Compute the Real divider depending on the MCLK output state with a floating point */
        if ( I2S_InitStruct->MCLKEnable == I2S_MCLK_ENABLE )
        {
            /* MCLK output is enabled */
            tmp = ( uint16_t )((((( sourceclock / 256 ) * 10 ) / I2S_InitStruct->AudioFrequency ) ) + 5 );
        }
        else
        {
            /* MCLK output is disabled */
            tmp = ( uint16_t )((((( sourceclock / ( 32 * packetlength ) ) * 10 ) / I2S_InitStruct->AudioFrequency ) ) + 5 );
        }

        /* Remove the floating point */
        tmp = tmp / 10;

        /* Check the parity of the divider */
        i2sodd = ( uint16_t )( tmp & ( uint16_t )0x0001 );

        /* Compute the i2sdiv prescaler */
        i2sdiv = ( uint16_t )(( tmp - i2sodd ) / 2 );

        /* Get the Mask for the Odd bit (SPI_I2SPR[10]) register */
        i2sodd = ( uint16_t )( i2sodd << 10 );
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if (( i2sdiv < 2 ) || ( i2sdiv > 0x3FF ) )
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to SPIx I2SPR register the computed value */
    I2Sx->I2SPR = ( uint16_t )( i2sdiv | ( uint16_t )( i2sodd | ( uint16_t )I2S_InitStruct->MCLKEnable ) );

    /* Configure the I2S with the SPI_InitStruct values */
    tmpreg |= ( uint16_t )( I2S_MODE_ENABLE | ( uint16_t )( I2S_InitStruct->I2sMode | \
                            ( uint16_t )( I2S_InitStruct->Standard | ( uint16_t )( I2S_InitStruct->DataFormat | \
                                          ( uint16_t )I2S_InitStruct->CLKPOL ) ) ) );

    /* Write to SPIx I2SCFGR */
    I2Sx->I2SCFGR = tmpreg;
}

/**
*\*\name    I2S_Enable.
*\*\fun     Enables or disables the specified SPI peripheral (in I2S mode).
*\*\param   SPIx :
*\*\          - SPI2
*\*\          - SPI3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_Enable(I2S_Module* I2Sx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral (in I2S mode) */
        I2Sx->I2SCFGR |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral (in I2S mode) */
        I2Sx->I2SCFGR &= I2SCFG_I2SEN_DISABLE;
    }
}

/* I2S_EXT  */
/**
*\*\name    I2S_EXTInit.
*\*\fun     Initializes the I2Sx_EXT peripheral according to the specified parameters in the I2S_EXT_InitStruct.
*\*\param   I2Sx_EXT :
*\*\          - I2S2_EXT
*\*\          - I2S3_EXT
*\*\param   I2S_InitStruct:
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX
*\*\           - I2S_MODE_SlAVE_RX
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS
*\*\           - I2S_STD_MSB_ALIGN
*\*\           - I2S_STD_LSB_ALIGN
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED
*\*\           - I2S_DATA_FMT_24BITS
*\*\           - I2S_DATA_FMT_32BITS
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW
*\*\           - I2S_CLKPOL_HIGH
*\*\return  none
**/
void I2S_EXTInit(I2S_EXT_Module* I2Sx_EXT, const I2S_InitType* I2S_EXT_InitStruct)
{
    uint16_t tmpregister;
    RCC_ClocksTypeDef RCC_Clocks;

    /*----------------------- I2Sx_EXT I2S_CFGR Configuration -----------------*/
    /* Clear I2SMOD, I2SE, MODCFG, PCMSYNC, STDSEL, CLKPOL, TDATLEN and CHLEN bits */
    I2Sx_EXT->I2S_CFGR &= I2SCFG_CLR_MASK;

    /* Get the SPI_I2S_CFGR register value */
    tmpregister = I2Sx_EXT->I2S_CFGR;



    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreqValue(&RCC_Clocks);



    /* Configure the I2S with the SPI_InitStruct values */
    tmpregister |= (uint16_t)(
                       I2S_MODE_ENABLE
                       | (uint16_t)(I2S_EXT_InitStruct->I2sMode
                                    | (uint16_t)(I2S_EXT_InitStruct->Standard
                                            | (uint16_t)(I2S_EXT_InitStruct->DataFormat | (uint16_t)I2S_EXT_InitStruct->CLKPOL))));

    /* Write to I2Sx_EXT SPI_I2S_CFGR */
    I2Sx_EXT->I2S_CFGR = tmpregister;
}


/**
*\*\name    I2S_EXT_InitStruct.
*\*\fun     Fills each I2S_EXT_InitStruct member with its default value.
*\*\param   I2S_EXT_InitStruct :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - CLKPOL
*\*\return  none
**/
void I2S_EXTInitStruct(I2S_InitType* I2S_EXT_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_EXT_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_EXT_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_EXT_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the CLKPOL member */
    I2S_EXT_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}

/**
*\*\name    I2S_EXTEnable.
*\*\fun     Enables or disables the specified I2S EXT peripheral.
*\*\param   I2Sx_EXT :
*\*\          - I2S2_EXT
*\*\          - I2S3_EXT
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_EXTEnable(I2S_EXT_Module* I2Sx_EXT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S_EXT peripheral */
        I2Sx_EXT->I2S_CFGR |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected I2S_EXT peripheral */
        I2Sx_EXT->I2S_CFGR &= I2SCFG_I2SEN_DISABLE;
    }
}

/**
*\*\name    I2S_EXT_TransmitData.
*\*\fun     Transmits a Data through the I2Sx_EXT peripheral.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   Data 			\* Data to be transmitted *\
*\*\return  none
**/
void I2S_EXTTransmitData(I2S_EXT_Module* I2Sx, uint16_t Data)
{
    /* Write in the DAT register the data to be sent */
    I2Sx->I2S_DAT = Data;
}


/**
*\*\name    I2S_EXTReceiveData.
*\*\fun     Returns the most recent received data by the I2Sx_EXT peripheral.
*\*\param   I2Sx :
*\*\				 - I2S1_EXT
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\				 - I2S4_EXT
*\*\return  The data in the I2S_DAT register.
**/
uint16_t I2S_EXTReceiveData(const I2S_EXT_Module* I2Sx)
{
    /* Return the data in the DAT register */
    return I2Sx->I2S_DAT;
}


/**
*\*\name    I2S_EXTEnableDma.
*\*\fun     Enables or disables the I2Sx DMA interface.
*\*\param   I2Sx :
*\*\				 - I2S1_EXT
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\				 - I2S4_EXT
*\*\param   I2S_EXT_DMAReq :
*\*\         - I2S_EXT_DMA_TX
*\*\         - I2S_EXT_DMA_RX
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EXTEnableDma(I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S_EXT DMA requests */
        I2Sx->I2S_CTRL2 |= I2S_EXT_DMAReq;
    }
    else
    {
        /* Disable the selected I2S_EXT DMA requests */
        I2Sx->I2S_CTRL2 &= (uint16_t)~I2S_EXT_DMAReq;
    }
}

/**
*\*\name    I2S_EXTEnableInt.
*\*\fun     Enables or disables the specified I2S_EXT interrupts.
*\*\param   I2Sx :
*\*\				 - I2S1_EXT
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\				 - I2S4_EXT
*\*\param   I2S_EXT_IT :
*\*\      	 - I2S_EXT_INT_TEINTEN
*\*\      	 - I2S_EXT_INT_RNEINTEN
*\*\      	 - I2S_EXT_INT_ERRINTEN
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EXTEnableInt(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT, FunctionalState Cmd)
{
    uint16_t itmask;

    /* Set the IT mask */
    itmask = I2S_EXT_IT;

    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S interrupt */
        I2Sx->I2S_CTRL2 |= itmask;
    }
    else
    {
        /* Disable the selected I2S interrupt */
        I2Sx->I2S_CTRL2 &= (uint16_t)~itmask;
    }
}

/**
*\*\name    I2S_EXT_GetStatus.
*\*\fun     Checks whether the specified I2S_EXT flag is set or not.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_FLAG :
*\*\				 - I2S_EXT_BUSY_FLAG
*\*\				 - I2S_EXT_OVER_FLAG
*\*\				 - I2S_EXT_UNDER_FLAG
*\*\				 - I2S_EXT_CHSIDE_FLAG
*\*\				 - I2S_EXT_TE_FLAG
*\*\				 - I2S_EXT_RNE_FLAG
*\*\return  The new state of I2S_EXT_FLAG (SET or RESET).
**/
FlagStatus I2S_EXTGetStatus(const I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_FLAG)
{
    FlagStatus bitstatus;

    /* Check the status of the specified I2S_EXT flag */
    if ((I2Sx->I2S_STS & I2S_EXT_FLAG) != (uint16_t)RESET)
    {
        /* I2S_EXT_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* I2S_EXT_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the I2S_EXT_FLAG status */
    return bitstatus;
}

/**
*\*\name    I2S_EXTGetIntStatus.
*\*\fun     Checks whether the specified I2S_EXT interrupt has occurred or not.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_IT :
*\*\      	 - I2S_EXT_TE_FLAG
*\*\      	 - I2S_EXT_RNE_FLAG
*\*\      	 - I2S_EXT_BUSY_FLAG
*\*\      	 - I2S_EXT_OVER_FLAG
*\*\      	 - I2S_EXT_UNDER_FLAG
*\*\      	 - I2S_EXT_CHSIDE_FLAG
*\*\return  The new state of I2S_EXT_IT (SET or RESET).
**/

INTStatus I2S_EXTGetIntStatus(const I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT)
{
    INTStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* Get the SPI/I2S IT index */
    itpos = 0x01 << (I2S_EXT_IT & 0x0F);

    /* Get the SPI/I2S IT mask */
    itmask = I2S_EXT_IT >> 4;

    /* Set the IT mask */
    itmask = 0x01 << itmask;

    /* Get the SPI_I2S_IT enable bit status */
    enablestatus = (I2Sx->I2S_CTRL2 & itmask);

    /* Check the status of the specified SPI/I2S interrupt */
    if (((I2Sx->I2S_STS & itpos) != (uint16_t)RESET) && enablestatus)
    {
        /* SPI_I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_IT is reset */
        bitstatus = RESET;
    }

    /* Return the SPI_I2S_IT status */
    return bitstatus;

}

/**
*\*\name    I2S_EXTClrITPendingBit.
*\*\fun     Clears the SPI_EXTx CRC Error (CRCERR) interrupt pending bit.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_IT :
*\*\				 - SPI_INT_CRCERR
*\*\return  none.
**/
void I2S_EXTClrITPendingBit(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT)
{
    uint16_t itpos;

    /* Get the SPI IT index */
    itpos = 0x0001 << (I2S_EXT_IT & 0x0F);

    /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
    I2Sx->I2S_STS = (uint16_t)~itpos;
}

/**
*\*\name    SPI_I2S_EnableDma.
*\*\fun     Enables or disables the SPIx/I2Sx DMA interface.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_DMAReq :
*\*\         - SPI_I2S_DMA_TX
*\*\         - SPI_I2S_DMA_RX
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EnableDma(I2S_Module* I2Sx, uint16_t I2S_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S DMA requests */
        I2Sx->CR2 |= I2S_DMAReq;
    }
    else
    {
        /* Disable the selected SPI/I2S DMA requests */
        I2Sx->CR2 &= (uint16_t)~I2S_DMAReq;
    }
}
