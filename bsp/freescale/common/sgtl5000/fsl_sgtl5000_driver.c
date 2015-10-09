/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#include "fsl_sgtl5000_driver.h"

/*******************************************************************************
 *Code
 ******************************************************************************/
 static volatile uint32_t i2c_state = 0;

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_Init
 * Description   : Initialize the sgtl5000 board.
 * This function has configured the sgtl5000 board. If the codec_config is NULL,
 * use default setting. 
 *END**************************************************************************/
sgtl_status_t SGTL_Init(sgtl_handler_t *handler, sgtl_init_t *codec_config)
{
    if(i2c_state == 0)
    {
        SGTL_I2CInit(handler);
    }
    i2c_state ++;
    /* NULL pointer means default setting. */
    if(codec_config == NULL)
    {
        /*
        * Power up Inputs/Outputs/Digital Blocks
        * Power up LINEOUT, HP, ADC, DAC.
        */
        SGTL_WriteReg(handler,CHIP_ANA_POWER, 0x6AFF);
        /*
        * Power up desired digital blocks.
        * I2S_IN (bit 0), I2S_OUT (bit 1), DAP (bit 4), DAC (bit 5), ADC (bit 6) are powered on
        */
        SGTL_WriteReg(handler,CHIP_DIG_POWER, 0x0073);
        /* Configure SYS_FS clock to 48kHz, MCLK_FREQ to 256*Fs. */
        SGTL_ModifyReg(handler,CHIP_CLK_CTRL, 0xFFC8, 0x0008); 
        /*
        * Configure the I2S clocks in slave mode.
        * I2S LRCLK is same as the system sample clock.
        * Data length = 16 bits.
        */
        SGTL_ModifyReg(handler,CHIP_I2S_CTRL, 0xFFFF, 0x0130);
        /* I2S_IN -> DAC -> HP_OUT, Route I2S_IN to DAC */
        SGTL_ModifyReg(handler,CHIP_SSS_CTRL, 0xFFDF, 0x0010);   
        /* Select DAC as the input to HP_OUT */
        SGTL_ModifyReg(handler,CHIP_ANA_CTRL, 0xFFBF, 0x0000);
        /* LINE_IN -> ADC -> I2S_OUT. Set ADC input to LINE_IN. */
        SGTL_ModifyReg(handler,CHIP_ANA_CTRL, 0xFFFF, 0x0004); 
        /* Route ADC to I2S_OUT */
        SGTL_ModifyReg(handler,CHIP_SSS_CTRL, 0xFFFC, 0x0000); 
        /* Default using I2S left format. */
        SGTL_SetProtocol(handler,kSgtlBusI2SLeft);
    }
    else
    {
        SGTL_WriteReg(handler,CHIP_ANA_POWER, 0x6AFF);
        SGTL_SetDataRoute(handler,codec_config->route);
        SGTL_SetProtocol(handler, codec_config->bus);
        SGTL_SetMasterSlave(handler, codec_config->master_slave);
    }
    /*
    * Input Volume Control
    * Configure ADC left and right analog volume to desired default.
    * Example shows volume of 0dB.
    */
    SGTL_WriteReg(handler,CHIP_ANA_ADC_CTRL, 0x0000);
    /*	
    * Volume and Mute Control
    * Configure HP_OUT left and right volume to minimum, unmute.
    * HP_OUT and ramp the volume up to desired volume.
    */
    /* Code assumes that left and right volumes are set to same value. */
    SGTL_WriteReg(handler,CHIP_ANA_HP_CTRL, 0x1818);
    SGTL_ModifyReg(handler,CHIP_ANA_CTRL, 0xFFEF, 0x0000); 
    /* LINEOUT and DAC volume control. */
    SGTL_ModifyReg(handler,CHIP_ANA_CTRL, 0xFEFF, 0x0000); 
    /* Configure DAC left and right digital volume. */
    SGTL_WriteReg(handler,CHIP_DAC_VOL, 0x5C5C);
    /* Configure ADC volume, reduce 6db. */
    SGTL_WriteReg(handler,CHIP_ANA_ADC_CTRL, 0x0100);
    /* Unmute DAC*/
    SGTL_ModifyReg(handler,CHIP_ADCDAC_CTRL, 0xFFFB, 0x0000); 
    SGTL_ModifyReg(handler,CHIP_ADCDAC_CTRL, 0xFFF7, 0x0000); 
    /* Unmute ADC. */
    SGTL_ModifyReg(handler,CHIP_ANA_CTRL, 0xFFFE ,0x0000);
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_I2CInit
 * Description   : Initialize the I2C transfer.
 * The sgtl5000 codec is controlled by I2C, using I2C transfer can access the sgtl register. 
 *END**************************************************************************/
sgtl_status_t SGTL_I2CInit(sgtl_handler_t *handler)
{
    /* The master structure initialize */
    I2C_DRV_MasterInit(handler->i2c_instance, &handler->state);
    /* Configure the device info of I2C */
    handler->device.baudRate_kbps = 100;
    handler->device.address = SGTL5000_I2C_ADDR;
    I2C_DRV_MasterSetBaudRate(handler->i2c_instance, &handler->device);
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_Deinit
 * Description   : Deinit the sgtl5000 board.
 * This function would free the i2c source applied. 
 *END**************************************************************************/
sgtl_status_t SGTL_Deinit(sgtl_handler_t *handler)
{
    i2c_state --;
    if(i2c_state == 0)
    {
        I2C_DRV_MasterDeinit(handler->i2c_instance);
    }
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetMasterSlave
 * Description   : Set master or slave mode of sgtl5000.
 * This function would set MS bit in CHIP_I2S_CTRL. 
 *END**************************************************************************/
sgtl_status_t SGTL_SetMasterSlave(sgtl_handler_t * handler, bool master)
{
    if(master == 1)
    {
        SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MS_CLR_MASK, SGTL5000_I2S_MASTER);
        uint16_t test;
        SGTL_ReadReg(handler,CHIP_I2S_CTRL, &test);
    }
    else
    {
        SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MS_CLR_MASK, SGTL5000_I2S_SLAVE);
    }
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetModuleCmd
 * Description   : Enable modules in sgtl5000.
 * This function would open both digital and analog switch.
 *END**************************************************************************/
sgtl_status_t SGTL_SetModuleCmd(sgtl_handler_t * handler,sgtl_module_t module,bool isEnabled)
{
    sgtl_status_t ret = kStatus_SGTL_Success;
    switch(module)
    {
        case kSgtlModuleADC:
            SGTL_ModifyReg(handler, CHIP_DIG_POWER, SGTL5000_ADC_ENABLE_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_ADC_ENABLE_SHIFT));
            SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_ADC_POWERUP_CLR_MASK,
                ((uint16_t)isEnabled << SGTL5000_ADC_POWERUP_SHIFT) );
            break;
        case kSgtlModuleDAC:
            SGTL_ModifyReg(handler, CHIP_DIG_POWER, SGTL5000_DAC_ENABLE_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_DAC_ENABLE_SHIFT));
            SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_DAC_POWERUP_CLR_MASK,
                ((uint16_t)isEnabled << SGTL5000_DAC_POWERUP_SHIFT));
            break;
        case kSgtlModuleDAP:
            SGTL_ModifyReg(handler, CHIP_DIG_POWER, SGTL5000_DAP_ENABLE_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_DAP_ENABLE_SHIFT));
            SGTL_ModifyReg(handler, DAP_CONTROL, DAP_CONTROL_DAP_EN_CLR_MASK, 
                ((uint16_t)isEnabled << DAP_CONTROL_DAP_EN_SHIFT));
            break;
        case kSgtlModuleI2SIN:
            SGTL_ModifyReg(handler, CHIP_DIG_POWER, SGTL5000_I2S_IN_ENABLE_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_I2S_IN_ENABLE_SHIFT));
            break;
        case kSgtlModuleI2SOUT:
            SGTL_ModifyReg(handler, CHIP_DIG_POWER, SGTL5000_I2S_OUT_ENABLE_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_I2S_OUT_ENABLE_SHIFT));
            break;
        case kSgtlModuleHP:
            SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_HEADPHONE_POWERUP_CLR_MASK,
                ((uint16_t)isEnabled << SGTL5000_HEADPHONE_POWERUP_SHIFT));
            break;
         case kSgtlModuleLineOut:
            SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_LINEOUT_POWERUP_CLR_MASK,
                ((uint16_t)isEnabled << SGTL5000_LINEOUT_POWERUP_SHIFT));
            break;
        default:
            ret = kStatus_SGTL_Fail;
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetDataRoute
 * Description   : Set the audio data route in sgtl5000.
 * This function would configure data route of sgtl5000.
 *END**************************************************************************/
 sgtl_status_t SGTL_SetDataRoute(sgtl_handler_t * handler,sgtl_route_t route)
{
    sgtl_status_t ret = kStatus_SGTL_Success;
    switch(route)
    {
        case kSgtlRouteBypass:
            /* Bypass means from line-in to HP*/
            SGTL_WriteReg(handler, CHIP_DIG_POWER, 0x0000);
            SGTL_SetModuleCmd(handler, kSgtlModuleHP, 1);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_LINEIN);
            break;
        case kSgtlRoutePlayback:
            /* Data route I2S_IN-> DAC-> HP */
            SGTL_SetModuleCmd(handler, kSgtlModuleHP, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAC, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SIN, 1);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_I2S_IN);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC);
            break;
        case kSgtlRoutePlaybackandRecord:
            /* I2S IN->DAC->HP  LINE_IN->ADC->I2S_OUT */
            SGTL_SetModuleCmd(handler, kSgtlModuleHP, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAC, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SIN, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SOUT,1);
            SGTL_SetModuleCmd(handler, kSgtlModuleADC, 1);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_I2S_IN);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC);
            break;
        case kSgtlRoutePlaybackwithDAP:
            /* I2S_IN->DAP->DAC->HP */
            SGTL_SetModuleCmd(handler, kSgtlModuleHP, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAC, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SIN, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAP, 1);
            SGTL_ModifyReg(handler,CHIP_SSS_CTRL, SGTL5000_DAP_SEL_CLR_MASK, SGTL5000_DAP_SEL_I2S_IN);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_DAP);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC);
            break;
        case kSgtlRoutePlaybackwithDAPandRecord:
            /* I2S_IN->DAP->DAC->HP,  LINE_IN->ADC->I2S_OUT */
            SGTL_SetModuleCmd(handler, kSgtlModuleHP, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAC, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SIN, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SOUT,1);
            SGTL_SetModuleCmd(handler, kSgtlModuleADC, 1);
            SGTL_SetModuleCmd(handler, kSgtlModuleDAP, 1);
            SGTL_ModifyReg(handler, DAP_CONTROL, DAP_CONTROL_DAP_EN_CLR_MASK, 0x0001);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_DAP_SEL_CLR_MASK, SGTL5000_DAP_SEL_I2S_IN);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_DAP);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC);
            break;
        case kSgtlRouteRecord:
            /* LINE_IN->ADC->I2S_OUT */
            SGTL_SetModuleCmd(handler, kSgtlModuleI2SOUT,1);
            SGTL_SetModuleCmd(handler, kSgtlModuleADC, 1);
            SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN);
            SGTL_ModifyReg(handler, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC);
            break;
        default:
            ret = kStatus_SGTL_Fail;
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetProtocol
 * Description   : Set the audio transfer protocol.
 * This function would configure protocol of audio transfer.
 *END**************************************************************************/
sgtl_status_t SGTL_SetProtocol(sgtl_handler_t *handler, sgtl_protocol_t protocol)
{
    sgtl_status_t ret = kStatus_SGTL_Success;
    switch(protocol)
    {
        case kSgtlBusI2S:
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_I2S_LJ);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_ONE_BIT_DELAY);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE);
            break;
        case kSgtlBusI2SLeft:
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_I2S_LJ);
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_NO_DELAY);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE);            
            break;
        case kSgtlBusI2SRight:
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_RJ);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE);            
            break;
        case kSgtlBusPCMA:
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_PCM);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_ONE_BIT_DELAY);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_FALLING_EDGE);            
            break;
        case kSgtlBusPCMB:
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_PCM);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_NO_DELAY);
            SGTL_ModifyReg(handler, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_FALLING_EDGE);            
            break;
        default:
            ret = kStatus_SGTL_Fail;
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetPLL
 * Description   : While using pll in sgtl5000, setting the divider of pll divide and fract.
 * This function would compute divide and fract according to mclk and fs expected.
 *END**************************************************************************/
sgtl_status_t SGTL_SetPLL(sgtl_handler_t *handler, uint32_t mclk, uint32_t fs)
{
    uint32_t pll_in = 0, pll_out = 0;
    /* Power up PLL */
    SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_PLL_POWERUP_CLR_MASK, 
    (1 << SGTL5000_PLL_POWERUP_SHIFT));
    SGTL_ModifyReg(handler, CHIP_ANA_POWER, SGTL5000_VCOAMP_POWERUP_CLR_MASK, 
    (1 << SGTL5000_VCOAMP_POWERUP_SHIFT));
    /* Set the PLL_CTRL register */
    if(mclk >= 17000000)
    {
        SGTL_ModifyReg(handler, CHIP_CLK_TOP_CTRL, SGTL5000_INPUT_FREQ_DIV2_CLR_MASK, 
            (1<< SGTL5000_INPUT_FREQ_DIV2_SHIFT));
        pll_in = mclk/2;
    }
    else
    {
        SGTL_ModifyReg(handler, CHIP_CLK_TOP_CTRL, SGTL5000_INPUT_FREQ_DIV2_CLR_MASK, 0x0000);
        pll_in = mclk;
    }
    if(fs == 44100)
    {
        pll_out = 180633600;
    }
    else
    {
        pll_out = 196608000;
    }
    uint32_t divider = 0, fract = 0;
    divider = pll_out/pll_in;
    fract = ((10 * pll_out/pll_in) - 10 * divider) * 2048;
    fract /= 10;
    SGTL_ModifyReg(handler, CHIP_PLL_CTRL, SGTL5000_PLL_INT_DIV_CLR_MASK, divider);
    SGTL_ModifyReg(handler, CHIP_PLL_CTRL, SGTL5000_PLL_FRAC_DIV_CLR_MASK, fract);
    /* Set using PLL */
    SGTL_ModifyReg(handler, CHIP_CLK_CTRL, SGTL5000_MCLK_FREQ_CLR_MASK, SGTL5000_MCLK_FREQ_PLL);
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetVolume
 * Description   : Set volume of sgtl5000 compontents.
 * This function would set compontents' volume as expected.
 *END**************************************************************************/
sgtl_status_t SGTL_SetVolume(sgtl_handler_t *handler, sgtl_module_t module, uint32_t volume)
{
    uint16_t vol = 0;
    sgtl_status_t ret = kStatus_SGTL_Success;
    switch(module)
    {
        case kSgtlModuleADC:
            vol = volume |(volume << 4);
            ret = SGTL_ModifyReg(handler,CHIP_ANA_ADC_CTRL, SGTL5000_ADC_VOL_LEFT_CLR_MASK &
                SGTL5000_ADC_VOL_RIGHT_CLR_MASK, vol);
            break;
        case kSgtlModuleDAC:
            vol = volume |(volume << 8);
            ret = SGTL_WriteReg(handler, CHIP_DAC_VOL, vol);
            break;
        case kSgtlModuleHP:
            vol = volume | (volume << 8);
            ret = SGTL_WriteReg(handler,CHIP_ANA_HP_CTRL, vol);
            break;
        case kSgtlModuleLineOut:
            vol = volume | (volume << 8);
            ret = SGTL_WriteReg(handler,CHIP_LINE_OUT_VOL, vol);
            break;
        default:
            ret = kStatus_SGTL_Fail;
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_GetVolume
 * Description   : Get volume of sgtl5000 compontents.
 * This function would set compontents' volume as expected.
 *END**************************************************************************/
uint32_t SGTL_GetVolume(sgtl_handler_t *handler, sgtl_module_t module)
{
    uint16_t vol = 0;
    switch(module)
    {
        case kSgtlModuleADC:
            SGTL_ReadReg(handler,CHIP_ANA_ADC_CTRL, &vol);
            vol = (vol & (uint16_t)SGTL5000_ADC_VOL_LEFT_GET_MASK) >> SGTL5000_ADC_VOL_LEFT_SHIFT;
            break;
        case kSgtlModuleDAC:
            SGTL_ReadReg(handler, CHIP_DAC_VOL, &vol);
            vol = (vol & (uint16_t)SGTL5000_DAC_VOL_LEFT_GET_MASK) >> SGTL5000_DAC_VOL_LEFT_SHIFT;
            break;
        case kSgtlModuleHP:
            SGTL_ReadReg(handler,CHIP_ANA_HP_CTRL, &vol);
            vol = (vol & (uint16_t)SGTL5000_HP_VOL_LEFT_GET_MASK) >> SGTL5000_HP_VOL_LEFT_SHIFT;
            break;
        case kSgtlModuleLineOut:
            SGTL_ReadReg(handler,CHIP_LINE_OUT_VOL, &vol);
            vol = (vol & (uint16_t)SGTL5000_LINE_OUT_VOL_LEFT_GET_MASK) >> SGTL5000_LINE_OUT_VOL_LEFT_SHIFT;
            break;
        default:
            vol = 0;
            break;
    }
    return vol;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_SetMuteCmd
 * Description   : Mute compontents in sgtl5000.
 * This function would mute compontents as expected.
 *END**************************************************************************/
sgtl_status_t SGTL_SetMuteCmd(sgtl_handler_t * handler,sgtl_module_t module, bool isEnabled)
{
    sgtl_status_t ret = kStatus_SGTL_Success;
    switch(module)
    {
        case kSgtlModuleADC:
            ret = SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_MUTE_ADC_CLR_MASK, isEnabled);
            break;
        case kSgtlModuleDAC:
            if(isEnabled)
            {
                ret = SGTL_ModifyReg(handler, CHIP_ADCDAC_CTRL, SGTL5000_DAC_MUTE_LEFT_CLR_MASK & 
                    SGTL5000_DAC_MUTE_RIGHT_CLR_MASK, 0x000C);
            }
            else
            {
                ret = SGTL_ModifyReg(handler, CHIP_ADCDAC_CTRL, SGTL5000_DAC_MUTE_LEFT_CLR_MASK & 
                    SGTL5000_DAC_MUTE_RIGHT_CLR_MASK, 0x0000);
            }
            break;
        case kSgtlModuleHP:
            ret = SGTL_ModifyReg(handler,CHIP_ANA_CTRL, SGTL5000_MUTE_HP_CLR_MASK, 
                ((uint16_t)isEnabled << SGTL5000_MUTE_HP_SHIFT));
            break;
        case kSgtlModuleLineOut:
            ret = SGTL_ModifyReg(handler, CHIP_ANA_CTRL, SGTL5000_MUTE_LO_CLR_MASK,  
                ((uint16_t)isEnabled << SGTL5000_MUTE_LO_SHIFT));
            break;
        default:
            ret = kStatus_SGTL_Fail;
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_ConfigDataFormat
 * Description   : Configure the audio data format of the sgtl5000.
 * This function would configure the sample rate and the data length.
 *END**************************************************************************/
sgtl_status_t SGTL_ConfigDataFormat
(
sgtl_handler_t *handler, 
uint32_t mclk, 
uint32_t sample_rate, 
uint8_t bits
)
{
    uint16_t val ; 
    sgtl_status_t retval;
    uint16_t mul_clk = mclk/sample_rate;
    retval = SGTL_ReadReg(handler, CHIP_CLK_CTRL, &val);

    if(retval != kStatus_SGTL_Success)
    {
        return kStatus_SGTL_Fail;
    }
   /* Configure the mul_clk. Sgtl-5000 only support 256, 384 and 512 oversample rate */
   if((mul_clk/128 - 2) > 2)
   {
       return kStatus_SGTL_Fail;
   }
   else
   {
       val = mul_clk/128 -2;
   }
    switch(sample_rate)
    {
        case 8000:
            val |= 0x0020;
            break;     
        case 11025:
            val |= 0x0024;
            break;
        case 12000:
            val |= 0x0028;
            break;    
        case 16000:
            val |= 0x0010;
            break;  
        case 22050:
            val |= 0x0014;
            break;  
        case 24000:
            val |= 0x0018;
            break;   
        case 32000:
            val |= 0x0000;
            break;           
        case 44100:
            val |= 0x0004;
            break;         
        case 48000:
            val |= 0x0008;
            break;            
        case 96000:
            val |= 0x000C;
            break;           
        default:
            retval = kStatus_SGTL_Fail;
            break;
    }
    SGTL_WriteReg(handler,CHIP_CLK_CTRL , val);
    /* data bits configure,sgtl supports 16bit, 20bit 24bit, 32bit */
    switch(bits)
    {
        case 16:
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_16);
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,0xFEFF, SGTL5000_I2S_SCLKFREQ_32FS);
            break;
        case 20:
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_20);
            break;
        case 24:
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_24);
            break;
        case 32:
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_32);
            SGTL_ModifyReg(handler,CHIP_I2S_CTRL,0xFEFF, SGTL5000_I2S_SCLKFREQ_64FS);
            break;
        default:
            retval = kStatus_SGTL_Fail;
            break;
    }
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_WriteReg
 * Description   : Write the specified register of sgtl5000.
 * The writing process is through I2C.
 *END**************************************************************************/
sgtl_status_t SGTL_WriteReg(sgtl_handler_t *handler, uint16_t reg, uint16_t val)
{
    i2c_device_t *device = &(handler->device);   
    uint8_t cmd[2],buff[2];
    uint8_t retval = 0;
    /* The register address */
    cmd[0] = (reg & 0xFF00U) >> 8U;
    cmd[1] = reg & 0xFF;  
    /* Data */
    buff[0] = (val & 0xFF00U) >> 8U;
    buff[1] = val & 0xFF;  
    retval = I2C_DRV_MasterSendDataBlocking(handler->i2c_instance,device,cmd,2,buff,2,OSA_WAIT_FOREVER);
    if(retval != kStatus_I2C_Success)
    {
        return kStatus_SGTL_I2CFail;
    }
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_ReadReg
 * Description   : Read the specified register value of sgtl5000.
 * The reading process is through I2C.
 *END**************************************************************************/
sgtl_status_t SGTL_ReadReg(sgtl_handler_t *handler, uint16_t reg, uint16_t *val)
{
    i2c_device_t *device = &(handler->device); 
    uint8_t buff[2];
    uint8_t data[2];
    uint8_t retval = 0;
    buff[0] = (reg & 0xFF00U) >> 8U;
    buff[1] = reg & 0xFF;
    retval = I2C_DRV_MasterReceiveDataBlocking(handler->i2c_instance,device,buff,2,data,2,OSA_WAIT_FOREVER);
    if(retval != kStatus_I2C_Success)
    {
        return kStatus_SGTL_I2CFail;
    }
    *val = (uint16_t)(((uint32_t)data[0] << 8U) | (uint32_t)data[1]); 
    return kStatus_SGTL_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SGTL_ModifyReg
 * Description   : Modify the specified register value of sgtl5000.
 * The modify process is through I2C.
 *END**************************************************************************/
sgtl_status_t SGTL_ModifyReg(sgtl_handler_t *handler, uint16_t reg, uint16_t clr_mask, uint16_t val)
{
    uint8_t retval = 0;	
    uint16_t reg_val;	
    retval = SGTL_ReadReg(handler, reg, &reg_val);
    if(retval != kStatus_SGTL_Success)
    {
        return kStatus_SGTL_Fail;
    }
    reg_val &= clr_mask;
    reg_val |= val;	
    retval = SGTL_WriteReg(handler, reg, reg_val);
    if(retval != kStatus_SGTL_Success)
    {
        return kStatus_SGTL_Fail;
    }	
    return kStatus_SGTL_Success;
}

/*******************************************************************************
 *EOF
 ******************************************************************************/

