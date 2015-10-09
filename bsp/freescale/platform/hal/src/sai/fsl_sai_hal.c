/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "fsl_sai_hal.h"
#if FSL_FEATURE_SOC_I2S_COUNT

/******************************************************************************
*Code
******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxInit
 * Description   : Initialize the sai Tx register, just set the register vaule to zero.
 *This function just clear the register value of sai.
 *END**************************************************************************/
void SAI_HAL_TxInit(I2S_Type * base)
{
    /* Software reset and FIFO reset */
    I2S_BWR_TCSR_SR(base, 1);
    I2S_BWR_TCSR_FR(base, 1);
    /* Clear all registers */
    I2S_WR_TCSR(base, 0);
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    I2S_WR_TCR1(base, 0);
#endif
    I2S_WR_TCR2(base, 0);
    I2S_WR_TCR3(base, 0);
    I2S_WR_TCR4(base, 0);
    I2S_WR_TCR5(base, 0);
    I2S_WR_TMR(base,0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxInit
 * Description   : Initialize the sai Rx register, just set the register vaule to zero.
 *This function just clear the register value of sai.
 *END**************************************************************************/
void SAI_HAL_RxInit(I2S_Type * base)
{
    /* Software reset and FIFO reset */
    I2S_BWR_RCSR_SR(base, 1);
    I2S_BWR_RCSR_FR(base, 1);
    /* Clear all registers */
    I2S_WR_RCSR(base, 0);
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    I2S_WR_RCR1(base, 0);
#endif
    I2S_WR_RCR2(base, 0);
    I2S_WR_RCR3(base, 0);
    I2S_WR_RCR4(base, 0);
    I2S_WR_RCR5(base, 0);
    I2S_WR_RMR(base,0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetProtocol
 * Description   : According to the protocol type to set the registers for tx.
 *The protocol can be I2S left, I2S right, I2S and so on.
 *END**************************************************************************/
void SAI_HAL_TxSetProtocol(I2S_Type * base,sai_protocol_t protocol)
{
    switch (protocol)
    {
        case kSaiBusI2SLeft:
            I2S_BWR_TCR2_BCP(base,1u);/* Bit clock polarity */
            I2S_BWR_TCR4_MF(base,1u);/* MSB transmitted fisrt */
            I2S_BWR_TCR4_FSE(base,0u);/*Frame sync not early */
            I2S_BWR_TCR4_FSP(base,0u);/* Frame sync polarity, left channel is high */
            I2S_BWR_TCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;

        case kSaiBusI2SRight:
            I2S_BWR_TCR2_BCP(base,1u);/* Bit clock polarity */
            I2S_BWR_TCR4_MF(base,1u);/* MSB transmitted firsrt */
            I2S_BWR_TCR4_FSE(base,0u);/*Frame sync not early */
            I2S_BWR_TCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */
            I2S_BWR_TCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;

        case kSaiBusI2SType:
            I2S_BWR_TCR2_BCP(base,1u);/*Bit clock polarity */
            I2S_BWR_TCR4_MF(base,1u);/*MSB transmitted firsrt */
            I2S_BWR_TCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_TCR4_FSP(base,1u);/* Frame sync polarity, left channel is low */
            I2S_BWR_TCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;

        case kSaiBusPCMA:
            I2S_BWR_TCR2_BCP(base,0u); /* Bit clock active low */
            I2S_BWR_TCR4_MF(base, 1u); /* MSB transmitted first */
            I2S_BWR_TCR4_SYWD(base, 0u); /* Only one bit clock in a frame sync */
            I2S_BWR_TCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_TCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */                
            I2S_BWR_TCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;
            
        case kSaiBusPCMB:
            I2S_BWR_TCR2_BCP(base,0u); /* Bit clock active high */
            I2S_BWR_TCR4_MF(base, 1u); /* MSB transmitted first */
            I2S_BWR_TCR4_FSE(base,0u);/* Frame sync not early */
            I2S_BWR_TCR4_SYWD(base, 0u); /* Only one bit clock in a frame sync */
            I2S_BWR_TCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */
            I2S_BWR_TCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;
            
        case kSaiBusAC97:
            I2S_BWR_TCR2_BCP(base,1u); /* Bit clock active high */
            I2S_BWR_TCR4_MF(base,1u); /* MSB transmitted first */
            I2S_BWR_TCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_TCR4_FRSZ(base,12u); /* There are 13 words in a frame in AC'97 */
            I2S_BWR_TCR4_SYWD(base,15u); /* Length of frame sync, 16 bit transmitted in first word */
            I2S_BWR_TCR5_W0W(base,15u); /* The first word have 16 bits */
            I2S_BWR_TCR5_WNW(base,19u); /* Other word is 20 bits */
            I2S_BWR_TCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;
            
        default:
            break;
        }
}  

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetProtocol
 * Description   : According to the protocol type to set the registers for rx.
 *The protocol can be I2S left, I2S right, I2S and so on.
 *END**************************************************************************/
void SAI_HAL_RxSetProtocol(I2S_Type * base,sai_protocol_t protocol)
{
    switch (protocol)
    {
        case kSaiBusI2SLeft:
            I2S_BWR_RCR2_BCP(base,1u);/* Bit clock polarity */
            I2S_BWR_RCR4_MF(base,1u);/* MSB transmitted fisrt */
            I2S_BWR_RCR4_FSE(base,0u);/*Frame sync one bit early */
            I2S_BWR_RCR4_FSP(base,0u);/* Frame sync polarity, left channel is high */
            I2S_BWR_RCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_RCR3_WDFL(base, 0u); /* The first word set the start flag */
            break;

        case kSaiBusI2SRight:
            I2S_BWR_RCR2_BCP(base,1u);/* Bit clock polarity */
            I2S_BWR_RCR4_MF(base,1u);/* MSB transmitted fisrt */
            I2S_BWR_RCR4_FSE(base,0u);/*Frame sync one bit early */
            I2S_BWR_RCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */
            I2S_BWR_RCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_RCR3_WDFL(base, 0u);/* The first word set the start flag */
            break;

        case kSaiBusI2SType:
            I2S_BWR_RCR2_BCP(base,1u);/*Bit clock polarity */
            I2S_BWR_RCR4_MF(base,1u);/*MSB transmitted fisrt */
            I2S_BWR_RCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_RCR4_FSP(base,1u);/* Frame sync polarity, left channel is low */
            I2S_BWR_RCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_RCR3_WDFL(base, 0u);/* The first word set the start flag */
            break;

        case kSaiBusPCMA:
            I2S_BWR_RCR2_BCP(base,0u); /* Bit clock active high */
            I2S_BWR_RCR4_MF(base, 1u); /* MSB transmitted first */
            I2S_BWR_RCR4_SYWD(base, 0u); /* Only one bit clock in a frame sync */
            I2S_BWR_RCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_RCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */                
            I2S_BWR_RCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */
            I2S_BWR_RCR3_WDFL(base, 0u);/* The first word set the start flag */
            break;
            
        case kSaiBusPCMB:
            I2S_BWR_RCR2_BCP(base,0u); /* Bit clock active high */
            I2S_BWR_RCR4_MF(base, 1u); /* MSB transmitted first */
            I2S_BWR_RCR4_FSE(base,0u);/* Frame sync not early */
            I2S_BWR_RCR4_SYWD(base, 0u); /* Only one bit clock in a frame sync */
            I2S_BWR_RCR4_FSP(base,0u);/* Frame sync polarity, left chennel is high */                
            I2S_BWR_RCR4_FRSZ(base,1u);/* I2S uses 2 word in a frame */                
            break;
            
        case kSaiBusAC97:
            I2S_BWR_RCR2_BCP(base,1u); /* Bit clock active high */
            I2S_BWR_RCR4_MF(base,1u); /* MSB transmitted first */
            I2S_BWR_RCR4_FSE(base,1u);/* Frame sync one bit early */
            I2S_BWR_RCR4_FRSZ(base,12u); /* There are 13 words in a frame in AC'97 */
            I2S_BWR_RCR4_SYWD(base,15u); /* Length of frame sync, 16 bit transmitted in first word */
            I2S_BWR_RCR5_W0W(base,15u); /* The first word have 16 bits */
            I2S_BWR_RCR5_WNW(base,19u); /* Other word is 20 bits */
            I2S_BWR_RCR3_WDFL(base, 0u);/* The first word set the start flag */
            break;

        default:
            break;
    }
}

#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_SetMclkDiv
 * Description   : Set the divider from the clock source to get the master clock.
 *The function would compute the divider number and set the number to the registers.
 *END**************************************************************************/
void SAI_HAL_SetMclkDiv(I2S_Type * base, uint32_t mclk, uint32_t src_clk)
{
    uint32_t freq = src_clk;
    uint16_t fract, divide;
    uint32_t remaind = 0;
    uint32_t current_remainder = 0xffffffff;
    uint16_t current_fract = 0;
    uint16_t current_divide = 0;
    uint32_t mul_freq = 0;
    uint32_t max_fract = 256;
    /*In order to prevent overflow */
    freq /= 100;
    mclk/= 100;
    max_fract = mclk * 4096/freq + 1;
    if(max_fract > 256)
    {
        max_fract = 256;
    }
    /* Looking for the closet frequency */
    for (fract = 1; fract < max_fract; fract ++)
    {
        mul_freq = freq * fract;
        remaind = mul_freq % mclk;
        divide = mul_freq/mclk;
        /* Find the exactly frequency */
        if (remaind == 0)
        {
            current_fract = fract;
            current_divide = mul_freq/mclk;
            break;
        }
        /* closer to next one */
        if (remaind > mclk/2)
        {
            remaind = mclk - remaind;
            divide += 1;
        }
        /* Update the closest div and fract */
        if (remaind < current_remainder)
        {
            current_fract = fract;
            current_divide = divide;
            current_remainder = remaind;
        }
    }
    /* Clear the FRACT and DIV bit  */
    I2S_WR_MDR(base, 0U);
    /* Waiting for change updated */
    while(I2S_BRD_MCR_DUF(base))
    {}
    I2S_BWR_MDR_DIVIDE(base, current_divide -1);
    /* Waiting for the divider updated */
    while(I2S_BRD_MCR_DUF(base))
    {}
    I2S_BWR_MDR_FRACT(base, current_fract - 1);
    /* Waiting for the divider updated */
    while(I2S_BRD_MCR_DUF(base))
    {}
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxClockSetup
 * Description   : Set all clock parameters into register for tx.
 *The function would compute the divider number and set the number to the registers.
 *END**************************************************************************/
void SAI_HAL_TxClockSetup(I2S_Type * base, sai_clock_setting_t * clk_config)
{
    /* First configure bit clock */
    uint32_t bclk_div = clk_config->bclk_src_freq/clk_config->bclk;
    I2S_BWR_TCR2_MSEL(base, clk_config->bclk_src);
    I2S_BWR_TCR2_DIV(base, (bclk_div/2-1));
    /* If bit clock source is mclk, compute mclk divider */
    if (clk_config->bclk_src == kSaiBclkSourceMclkDiv)
    {
        /* Enable MCLK */
        I2S_BWR_MCR_MOE(base, 1u);
        /* Configure MCLK source */
        I2S_BWR_MCR_MICS(base, clk_config->mclk_src);
#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
        /* Configure MCLK divider */
        SAI_HAL_SetMclkDiv(base, clk_config->mclk, clk_config->mclk_src_freq);
 #endif
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxClockSetup
 * Description   : Set all clock parameters into register for rx.
 *The function would compute the divider number and set the number to the registers.
 *END**************************************************************************/
void SAI_HAL_RxClockSetup(I2S_Type * base, sai_clock_setting_t * clk_config)
{
    /* First configure bit clock */
    uint32_t bclk_div = clk_config->bclk_src_freq/clk_config->bclk;
    I2S_BWR_RCR2_MSEL(base, clk_config->bclk_src);
    I2S_BWR_RCR2_DIV(base, (bclk_div/2-1));
    /* If bit clock source is mclk, compute mclk divider */
    if (clk_config->bclk_src == kSaiBclkSourceMclkDiv)
    {
        /* Enable MCLK */
        I2S_BWR_MCR_MOE(base, 1u);
        /* Configure MCLK source */
        I2S_BWR_MCR_MICS(base, clk_config->mclk_src);
#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
        /* Configure MCLK divider */
        SAI_HAL_SetMclkDiv(base, clk_config->mclk, clk_config->mclk_src_freq);
 #endif
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetWordWidth
 * Description   : Set the tx word width. It can be 8bits, 16bits, 24bits and 32bits.
 *The function will set word width for different protocol.
 *END**************************************************************************/
void SAI_HAL_TxSetWordWidth(I2S_Type * base, sai_protocol_t protocol, uint32_t bits)
{
    if ((protocol == kSaiBusI2SLeft) ||(protocol == kSaiBusI2SRight) ||(protocol == kSaiBusI2SType))
    {
        I2S_BWR_TCR4_SYWD(base, bits -1);
    }
    I2S_BWR_TCR5_W0W(base, bits -1);
    I2S_BWR_TCR5_WNW(base, bits -1);
    I2S_BWR_TCR5_FBT(base, bits -1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetWordWidth
 * Description   : Set the rx word width. It can be 8bits, 16bits, 24bits and 32bits.
 *The function will set word width for different protocol.
 *END**************************************************************************/
void SAI_HAL_RxSetWordWidth(I2S_Type * base, sai_protocol_t protocol, uint32_t bits)
{
    if ((protocol == kSaiBusI2SLeft) ||(protocol == kSaiBusI2SRight) ||(protocol == kSaiBusI2SType))
    {
        I2S_BWR_RCR4_SYWD(base, bits -1);
    }
    I2S_BWR_RCR5_W0W(base, bits -1);
    I2S_BWR_RCR5_WNW(base, bits -1);
    I2S_BWR_RCR5_FBT(base, bits -1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetMonoStereo
 * Description   : Set the mono or stereo mode for tx.
 *
 *END**************************************************************************/
void SAI_HAL_TxSetMonoStereo(I2S_Type * base, sai_mono_stereo_t mono_stereo)
{
    if (mono_stereo == kSaiMono)
    {
        I2S_WR_TMR(base, 2u);
    }
    else
    {
        I2S_WR_TMR(base, 0u);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetMonoStereo
 * Description   : Set the mono or stereo mode for rx.
 *
 *END**************************************************************************/
void SAI_HAL_RxSetMonoStereo(I2S_Type * base, sai_mono_stereo_t mono_stereo)
{
    if (mono_stereo == kSaiMono)
    {
        I2S_WR_RMR(base, 2u);
    }
    else
    {
        I2S_WR_RMR(base, 0u);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetMasterSlave
 * Description   : Set the tx master or slave mode.
 *The slave or master mode only would affect the clock direction relevant registers.
 *END**************************************************************************/
void SAI_HAL_TxSetMasterSlave(I2S_Type * base, sai_master_slave_t master_slave_mode)
{
    if (master_slave_mode == kSaiMaster)
    {
        I2S_BWR_TCR2_BCD(base,1);/* Bit clock generated internal */
        I2S_BWR_TCR4_FSD(base,1);/* Frame sync generated internal */
        I2S_BWR_MCR_MOE(base,1);/* Master clock generated internal */
    }
    else
    {
        I2S_BWR_TCR2_BCD(base,0);/* Bit clock generated external */
        I2S_BWR_TCR4_FSD(base,0);/* Frame sync generated external */
        I2S_BWR_MCR_MOE(base,0);/* Master clock generated external */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetMasterSlave
 * Description   : Set the rx master or slave mode.
 *The slave or master mode only would affect the clock direction relevant registers.
 *END**************************************************************************/
void SAI_HAL_RxSetMasterSlave(I2S_Type * base, sai_master_slave_t master_slave_mode)
{
    if (master_slave_mode == kSaiMaster)
    {
        I2S_BWR_RCR2_BCD(base,1);/* Bit clock generated internal */
        I2S_BWR_RCR4_FSD(base,1);/* Frame sync generated internal */
        I2S_BWR_MCR_MOE(base,1);/* Master clock generated internal */
    }
    else
    {
        I2S_BWR_RCR2_BCD(base,0);/* Bit clock generated external */
        I2S_BWR_RCR4_FSD(base,0);/* Frame sync generated external */
        I2S_BWR_MCR_MOE(base,0);/* Master clock generated external */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetSyncMode
 * Description   : Set the tx sync mode.
 *Theer are four kinds of sync mode, async, sync, sync with other sai tx, sync with other sai rx.
 *END**************************************************************************/
void SAI_HAL_TxSetSyncMode(I2S_Type * base, sai_sync_mode_t sync_mode)
{
    switch (sync_mode)
    {
        case kSaiModeAsync:
            I2S_BWR_TCR2_SYNC(base,0);
            break;
        case kSaiModeSync:
            I2S_BWR_TCR2_SYNC(base,1);
            I2S_BWR_RCR2_SYNC(base,0);/* Receiver must be async mode */
            break;
        case kSaiModeSyncWithOtherTx:
            I2S_BWR_TCR2_SYNC(base,2);
            break;
        case kSaiModeSyncWithOtherRx:
            I2S_BWR_TCR2_SYNC(base,3);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetSyncMode
 * Description   : Set the rx sync mode.
 *Theer are four kinds of sync mode, async, sync, sync with other sai tx, sync with other sai rx.
 *END**************************************************************************/
void SAI_HAL_RxSetSyncMode(I2S_Type * base,sai_sync_mode_t sync_mode)
{
    switch (sync_mode)
    {
        case kSaiModeAsync:
            I2S_BWR_RCR2_SYNC(base,0);
            break;
        case kSaiModeSync:
            I2S_BWR_RCR2_SYNC(base,1);
            I2S_BWR_TCR2_SYNC(base,0);/* Receiver must be async mode */
            break;
        case kSaiModeSyncWithOtherTx:
            I2S_BWR_RCR2_SYNC(base,3);
            break;
        case kSaiModeSyncWithOtherRx:
            I2S_BWR_RCR2_SYNC(base,2);
            break;
        default:
            break;
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetIntCmd
 * Description   : Enable the interrupt request source for tx.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
void SAI_HAL_TxSetIntCmd(I2S_Type * base, uint32_t source, bool enable)
{
    uint32_t  val = I2S_RD_TCSR(base);
    if (enable == true)
    {
        I2S_WR_TCSR(base, val |source);
    }
    else
    {
        I2S_WR_TCSR(base, (val & (~source)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetIntCmd
 * Description   : Enable the interrupt request source for rx.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
void SAI_HAL_RxSetIntCmd(I2S_Type * base, uint32_t source, bool enable)
{
    uint32_t  val = I2S_RD_RCSR(base);
    if (enable == true)
    {
        I2S_WR_RCSR(base, val |source);
    }
    else
    {
        I2S_WR_RCSR(base, (val & (~source)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetDmaCmd
 * Description   : Enable the dma request source for tx.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
void SAI_HAL_TxSetDmaCmd(I2S_Type * base, uint32_t source, bool enable)
{
    uint32_t  val = I2S_RD_TCSR(base);
    if (enable == true)
    {
        I2S_WR_TCSR(base, val |source);
    }
    else
    {
        I2S_WR_TCSR(base, (val & (~source)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetDmaCmd
 * Description   : Enable the dma request source for rx.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
void SAI_HAL_RxSetDmaCmd(I2S_Type * base, uint32_t source, bool enable)
{
    uint32_t  val = I2S_RD_RCSR(base);
    if (enable == true)
    {
        I2S_WR_RCSR(base, val |source);
    }
    else
    {
        I2S_WR_RCSR(base, (val & (~source)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxClearStateFlag
 * Description   : Clear the state flag of tx registers.
 *The state flag incudes word start flag, sync error flag and fifo error flag.
 *END**************************************************************************/
void SAI_HAL_TxClearStateFlag(I2S_Type * base, uint32_t flag_mask)
{
    uint32_t val = I2S_RD_TCSR(base);
    /* FIFO request cannot clear */
    if (flag_mask & kSaiStateFlagFIFORequest)
    {
        flag_mask &= (uint32_t)(~kSaiStateFlagFIFORequest);
    }
    /* FIFO warning cannot clear */
    if (flag_mask & kSaiStateFlagFIFOWarning)
    {
        flag_mask &= (uint32_t)(~kSaiStateFlagFIFOWarning);
    }
    /* Check if need to clear software reset. */
    if (flag_mask & kSaiStateFlagSoftReset)
    {
        val &= (uint32_t)(~kSaiStateFlagSoftReset);
        flag_mask &= (uint32_t)(~kSaiStateFlagSoftReset);
    }
    /* Clear other flags. */
    val  |= flag_mask;
    I2S_WR_TCSR(base, val);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxClearStateFlag
 * Description   : Clear the state flag of rx registers.
 *The state flag incudes word start flag, sync error flag and fifo error flag.
 *END**************************************************************************/
void SAI_HAL_RxClearStateFlag(I2S_Type * base, uint32_t flag_mask)
{
    uint32_t val = I2S_RD_RCSR(base);
    /* FIFO request cannot clear */
    if (flag_mask & kSaiStateFlagFIFORequest)
    {
        flag_mask &= (uint32_t)(~kSaiStateFlagFIFORequest);
    }
    /* FIFO warning cannot clear */
    if (flag_mask & kSaiStateFlagFIFOWarning)
    {
        flag_mask &= (uint32_t)(~kSaiStateFlagFIFOWarning);
    }
    /* Check if need to clear software reset. */
    if (flag_mask & kSaiStateFlagSoftReset)
    {
        val &= (uint32_t)(~kSaiStateFlagSoftReset);
        flag_mask &= (uint32_t)(~kSaiStateFlagSoftReset);
    }
    /* Clear other flags. */
    val  |= flag_mask;
    I2S_WR_RCSR(base, val);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetReset
 * Description   : Reset tx according to reset mode.
 *The reset mode can be software reset and FIFO reset. 
 *END**************************************************************************/
void SAI_HAL_TxSetReset(I2S_Type * base, uint32_t  reset_mask)
{
    uint32_t val = I2S_RD_TCSR(base);
    I2S_WR_TCSR(base, val |reset_mask);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetReset
 * Description   : Reset rx according to reset mode.
 *The reset mode can be software reset and FIFO reset. 
 *END**************************************************************************/
void SAI_HAL_RxSetReset(I2S_Type * base, uint32_t reset_mask)
{
    uint32_t val = I2S_RD_RCSR(base);
    I2S_WR_RCSR(base, val |reset_mask);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetRunModeCmd
 * Description   : Set the work mode for tx.
 *The work mode have stop mode, debug mode and normal mode. 
 *END**************************************************************************/
void SAI_HAL_TxSetRunModeCmd(I2S_Type * base, sai_run_mode_t run_mode, bool enable)
{
    switch (run_mode)
    {
        case kSaiRunModeStop:
            I2S_BWR_TCSR_STOPE(base, enable);/* Stop mode */
            break;
        case kSaiRunModeDebug:
            I2S_BWR_TCSR_DBGE(base, enable);/* Debug mode */
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetRunModeCmd
 * Description   : Set the work mode for rx.
 *The work mode have stop mode, debug mode and normal mode. 
 *END**************************************************************************/
void SAI_HAL_RxSetRunModeCmd(I2S_Type * base,sai_run_mode_t run_mode,bool enable)
{
    switch (run_mode)
    {
        case kSaiRunModeStop:
            I2S_BWR_RCSR_STOPE(base, enable);/* Stop mode */
            break;
        case kSaiRunModeDebug:
            I2S_BWR_RCSR_DBGE(base, enable);/* Debug mode */
            break;
        default:
            break;
    }
}

#if FSL_FEATURE_SAI_FIFO_COUNT > 1
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxGetFifoWRPointer
 * Description   : Get tx fifo read and write pointer.
 *
 *END**************************************************************************/
void SAI_HAL_TxGetFifoWRPointer(I2S_Type * base,  uint32_t fifo_channel, 
       uint32_t * r_ptr, uint32_t * w_ptr)
{
    uint32_t val = I2S_RD_TFR(base, fifo_channel);
    *r_ptr = (val >> I2S_TFR_RFP_SHIFT) & I2S_TFR_RFP_MASK;
    *w_ptr = (val >> I2S_TFR_WFP_SHIFT) & I2S_TFR_WFP_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxGetFifoWRPointer
 * Description   : Get rx fifo read and write pointer.
 *
 *END**************************************************************************/
void SAI_HAL_RxGetFifoWRPointer(I2S_Type * base,  uint32_t fifo_channel, 
       uint32_t * r_ptr, uint32_t * w_ptr)
{
    uint32_t val = I2S_RD_RFR(base, fifo_channel);
    *r_ptr = (val >> I2S_RFR_RFP_SHIFT) & I2S_RFR_RFP_MASK;
    *w_ptr = (val >> I2S_RFR_WFP_SHIFT) & I2S_RFR_WFP_MASK;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_ReceiveDataBlocking
 * Description   : Receive data in blocking way.
 *The sending would wait until there is vaild data in FIFO for reading.
 *END**************************************************************************/
void SAI_HAL_ReceiveDataBlocking(I2S_Type * base,uint32_t rx_channel,
    uint8_t *rxBuff, uint32_t size)
{
    assert(rx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);
    uint32_t bytes = (I2S_BRD_RCR5_WNW(base) + 1)/8;
    uint32_t i =0, j = 0, data = 0;
    /* Wait while fifo is empty */
    for (i = 0; i < (size/bytes); i ++)
    {
        while(!I2S_BRD_RCSR_FWF(base))
        {}
        data = I2S_RD_RDR(base,rx_channel);
        for (j = 0; j < bytes; j ++)
        {
            *rxBuff = (data >> (8U * j)) & 0xFF;
            rxBuff ++;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_SendDataBlocking
 * Description   : Send data in blocking way.
 *The sending would wait until there is space for writing.
 *END**************************************************************************/
void SAI_HAL_SendDataBlocking(I2S_Type * base,uint32_t tx_channel,
    uint8_t * txBuff, uint32_t size)
{
    assert(tx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);
    uint32_t bytes = (I2S_BRD_TCR5_WNW(base) + 1)/8;
    uint32_t i =0, j = 0, data = 0, temp = 0;
    /* Wait while fifo is empty */
    for (i = 0; i < (size/bytes); i ++)
    {
        while(!I2S_BRD_TCSR_FWF(base))
        {}
        for (j = 0; j < bytes; j ++)
        {
            temp = (uint32_t)(*txBuff);
            data |= (temp << (8U * j));
            txBuff ++;
        }
        I2S_WR_TDR(base, tx_channel, data);
        data = 0;
    }
}
#endif

