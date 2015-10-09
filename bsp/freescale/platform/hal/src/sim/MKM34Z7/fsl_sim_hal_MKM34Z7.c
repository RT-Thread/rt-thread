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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_sim_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetLptmrChSelMode
 * Description   : Sets the LPTMR channel x source select setting.
 * This function selects the LPTMR channel x source select setting.
 *
 *END**************************************************************************/ 
void SIM_HAL_SetLptmrChSelMode(SIM_Type * base,
                               uint8_t channel,
                               sim_lptmr_src_sel_t select)
{
    switch(channel)
    {
        case 0:
            SIM_BWR_SOPT1_CFG_LPTMR0SEL(base, select);
            break;
        case 1:
            SIM_BWR_SOPT1_CFG_LPTMR1SEL(base, select);
            break;
        case 2:
            SIM_BWR_SOPT1_CFG_LPTMR2SEL(base, select);
            break;
        case 3:
            SIM_BWR_SOPT1_CFG_LPTMR3SEL(base, select);
            break;
        default:
            break;
    }
}                               

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetLptmrChSelMode
 * Description   : Gets the LPTMR channel x source select setting.
 * This function gets the LPTMR channel x source select setting.
 *
 *END**************************************************************************/ 
sim_lptmr_src_sel_t SIM_HAL_GetLptmrChSelMode(SIM_Type * base,
                                              uint8_t channel)
{
    sim_lptmr_src_sel_t retValue = (sim_lptmr_src_sel_t)0;
    
    switch(channel)
    {
        case 0:
            retValue = (sim_lptmr_src_sel_t)SIM_BRD_SOPT1_CFG_LPTMR0SEL(base);
            break;
        case 1:
            retValue = (sim_lptmr_src_sel_t)SIM_BRD_SOPT1_CFG_LPTMR1SEL(base);
            break;
        case 2:
            retValue = (sim_lptmr_src_sel_t)SIM_BRD_SOPT1_CFG_LPTMR2SEL(base);
            break;
        case 3:
            retValue = (sim_lptmr_src_sel_t)SIM_BRD_SOPT1_CFG_LPTMR3SEL(base);
            break;
        default:
            break;
    }
    return retValue;
}              
 
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetOutDiv
 * Description   : Set all clock out dividers setting at one time
 * This function will set the setting for all system clock out dividers.
 *
 *END**************************************************************************/
void CLOCK_HAL_SetOutDiv(SIM_Type * base,
                         uint8_t sysDiv,
                         uint8_t busDiv,
                         uint8_t flashclkmode)
{
    uint32_t clkdiv = 0;
    
    clkdiv |= SIM_CLKDIV1_CLKDIVSYS(sysDiv);
    clkdiv |= SIM_CLKDIV1_CLKDIVBUS(busDiv);
    clkdiv |= SIM_CLKDIV1_FLASHCLKMODE(flashclkmode);
    
    SIM_WR_CLKDIV1(base, clkdiv);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetOutDiv
 * Description   : Get all clock out dividers setting at one time
 * This function will get the setting for all system clock out dividers.
 *
 *END**************************************************************************/
void CLOCK_HAL_GetOutDiv(SIM_Type * base,
                         uint8_t *sysDiv,
                         uint8_t *busDiv,
                         uint8_t *flashclkmode)
{
    *sysDiv       = SIM_BRD_CLKDIV1_CLKDIVSYS(base);
    *busDiv       = SIM_BRD_CLKDIV1_CLKDIVBUS(base);
    *flashclkmode = SIM_BRD_CLKDIV1_FLASHCLKMODE(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetSpiOutInvCmd
 * Description   : Set SPI output signal inverting setting.
 * This function will set SPI output signal inverting setting.
 *
 *END**************************************************************************/
void CLOCK_HAL_SetSpiOutInvCmd(SIM_Type * base, 
                               uint32_t instance,
                               uint8_t  inv_type,
                               sim_spi_out_invert_sel_t setting)
{
    assert (instance < SPI_INSTANCE_COUNT);
    switch (instance)
    {
    case 0:
        switch (inv_type)
        {
        case 0:
            SIM_BWR_CTRL_REG_SPI0_INV0(base, setting);
            break;
        case 1:
            SIM_BWR_CTRL_REG_SPI0_INV1(base, setting);
            break;
        case 2:
            SIM_BWR_CTRL_REG_SPI0_INV2(base, setting);
            break;
        case 3:
            SIM_BWR_CTRL_REG_SPI0_INV3(base, setting);
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (inv_type)
        {
        case 0:
            SIM_BWR_CTRL_REG_SPI1_INV0(base, setting);
            break;
        case 1:
            SIM_BWR_CTRL_REG_SPI1_INV1(base, setting);
            break;
        case 2:
            SIM_BWR_CTRL_REG_SPI1_INV2(base, setting);
            break;
        case 3:
            SIM_BWR_CTRL_REG_SPI1_INV3(base, setting);
            break;
        default:
            break;
        }
        break;
        
    default:
        break;
    }
}                               
                                   
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetSpiOutInvCmd
 * Description   : Get the SPI output signal inverting setting.
 * This function will get the SPI output signal inverting setting.
 *
 *END**************************************************************************/
sim_spi_out_invert_sel_t CLOCK_HAL_GetSpiOutInvCmd(SIM_Type * base,
                                                   uint32_t instance,
                                                   uint8_t  inv_type)
{
    sim_spi_out_invert_sel_t retValue = (sim_spi_out_invert_sel_t)0;
    
    assert (instance < SPI_INSTANCE_COUNT);
    switch (instance)
    {
    case 0:
        switch (inv_type)
        {
        case 0:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI0_INV0(base);
            break;
        case 1:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI0_INV1(base);
            break;
        case 2:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI0_INV2(base);
            break;
        case 3:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI0_INV3(base);
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (inv_type)
        {
        case 0:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI1_INV0(base);
            break;
        case 1:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI1_INV1(base);
            break;
        case 2:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI1_INV2(base);
            break;
        case 3:
            retValue = (sim_spi_out_invert_sel_t)SIM_BRD_CTRL_REG_SPI1_INV3(base);
            break;
        default:
            break;
        }
        break;
        
    default:
        break;
    }
    
    return retValue;
}                                                   

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTmrPrimaryCntSrcSelMode
 * Description   : Sets the Quadtimer channel x Primary Count source select setting.
 * This function selects the Quadtimer channel x Primary Count source.
 *
 *END**************************************************************************/
void SIM_HAL_SetTmrPrimaryCntSrcSelMode(SIM_Type * base,
                                        uint8_t channel,
                                        sim_tmr_Primary_src_sel_t select)
{
    switch(channel)
    {
        case 0:
            SIM_BWR_MISC_CTL_TMR0PCSSEL(base, select);
            break;
        case 1:
            SIM_BWR_MISC_CTL_TMR1PCSSEL(base, select);
            break;
        case 2:
            SIM_BWR_MISC_CTL_TMR2PCSSEL(base, select);
            break;
        case 3:
            SIM_BWR_MISC_CTL_TMR3PCSSEL(base, select);
            break;
        default:
            break;
    }
}                                        

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTmrPrimaryCntSrcSelMode
 * Description   : Gets the Quadtimer channel x Primary Count source select setting.
 * This function gets the Quadtimer channel x Primary Count source select setting.
 *
 *END**************************************************************************/
sim_tmr_Primary_src_sel_t SIM_HAL_GetTmrPrimaryCntSrcSelMode(SIM_Type * base,
                                                             uint8_t channel)
{
    sim_tmr_Primary_src_sel_t retValue = (sim_tmr_Primary_src_sel_t)0;
    
    switch(channel)
    {
        case 0:
            retValue = (sim_tmr_Primary_src_sel_t)SIM_BRD_MISC_CTL_TMR0PCSSEL(base);
            break;
        case 1:
            retValue = (sim_tmr_Primary_src_sel_t)SIM_BRD_MISC_CTL_TMR1PCSSEL(base);
            break;
        case 2:
            retValue = (sim_tmr_Primary_src_sel_t)SIM_BRD_MISC_CTL_TMR2PCSSEL(base);
            break;
        case 3:
            retValue = (sim_tmr_Primary_src_sel_t)SIM_BRD_MISC_CTL_TMR3PCSSEL(base);
            break;
        default:
            break;
    }
    
    return retValue;
}                                                       
                                                       
 /*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTmrSecondCntSrcSelMode
 * Description   : Sets the Quadtimer channel x Secondary Count source select setting.
 * This function selects the Quadtimer channel x Secondary Count source.
 *
 *END**************************************************************************/ 
void SIM_HAL_SetTmrSecondCntSrcSelMode(SIM_Type * base,
                                       uint8_t channel,
                                       sim_tmr_sencond_src_sel_t select)
{
    switch(channel)
    {
        case 0:
            SIM_BWR_MISC_CTL_TMR0SCSEL(base, select);
            break;
        case 1:
            SIM_BWR_MISC_CTL_TMR1SCSEL(base, select);
            break;
        case 2:
            SIM_BWR_MISC_CTL_TMR2SCSEL(base, select);
            break;
        case 3:
            SIM_BWR_MISC_CTL_TMR3SCSEL(base, select);
            break;
        default:
            break;
    }
}                                       

 /*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTmrSecondCntSrcSelMode
 * Description   : Gets the Quadtimer channel x Secondary Count source select setting.
 * This function gets the Quadtimer channel x Secondary Count source select setting.
 *
 *END**************************************************************************/  
sim_tmr_sencond_src_sel_t SIM_HAL_GetTmrSecondCntSrcSelMode(SIM_Type * base,
                                                            uint8_t channel)
{
    sim_tmr_sencond_src_sel_t retValue = (sim_tmr_sencond_src_sel_t)0;
    
    switch(channel)
    {
        case 0:
            retValue = (sim_tmr_sencond_src_sel_t)SIM_BRD_MISC_CTL_TMR0SCSEL(base);
            break;
        case 1:
            retValue = (sim_tmr_sencond_src_sel_t)SIM_BRD_MISC_CTL_TMR1SCSEL(base);
            break;
        case 2:
            retValue = (sim_tmr_sencond_src_sel_t)SIM_BRD_MISC_CTL_TMR2SCSEL(base);
            break;
        case 3:
            retValue = (sim_tmr_sencond_src_sel_t)SIM_BRD_MISC_CTL_TMR3SCSEL(base);
            break;
        default:
            break;
    }
    
    return retValue;
}                                                            

 /*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartIrdaSelMode
 * Description   : Sets the UART x IRDA select setting.
 * This function  sets the UART x IRDA select setting.
 *
 *END**************************************************************************/   
void SIM_HAL_SetUartIrdaSelMode(SIM_Type * base,
                                uint32_t instance,
                                sim_uart_irda_sel_t select)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    switch (instance)
    {
    case 0:
        SIM_BWR_MISC_CTL_UART0IRSEL(base, select);
        break;
    case 1:
        SIM_BWR_MISC_CTL_UART1IRSEL(base, select);
        break;
    case 2:
        SIM_BWR_MISC_CTL_UART2IRSEL(base, select);
        break;
    case 3:
        SIM_BWR_MISC_CTL_UART3IRSEL(base, select);
        break;
    default:
        break;
    }
    
}                                

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartIrdaSelMode
 * Description   : Gets the UART x IRDA select setting.
 * This function  gets the UART x IRDA select setting.
 *
 *END**************************************************************************/ 
sim_uart_irda_sel_t SIM_HAL_GetUartIrdaSelMode(SIM_Type * base,
                                               uint32_t instance)
{
    sim_uart_irda_sel_t retValue = (sim_uart_irda_sel_t)0;

    assert (instance < UART_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_uart_irda_sel_t)SIM_BRD_MISC_CTL_UART0IRSEL(base);
        break;
    case 1:
        retValue = (sim_uart_irda_sel_t)SIM_BRD_MISC_CTL_UART1IRSEL(base);
        break;
    case 2:
        retValue = (sim_uart_irda_sel_t)SIM_BRD_MISC_CTL_UART2IRSEL(base);
        break;
    case 3:
        retValue = (sim_uart_irda_sel_t)SIM_BRD_MISC_CTL_UART3IRSEL(base);
        break;
    default:
        break;
    }

    return retValue;
}                                                                                       

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcCompensationValueCmd
 * Description   : Gets the ADC Temperature Compensation Value.
 * This function  gets the ADC Temperature Compensation Value.
 *
 *END**************************************************************************/
 uint16_t SIM_HAL_GetAdcCompensationValueCmd(SIM_Type * base, uint8_t temperature)
 {
    assert (temperature < 3);
    uint16_t retValue = 0;
    
    switch(temperature)
    {
        case 0:
            retValue = SIM_BRD_ADC_COMP0_ADCCOMPVAL0(base);
            break;
        case 1:
            retValue = SIM_BRD_ADC_COMP0_ADCCOMPVAL1(base);
            break;
        case 2:
            retValue = SIM_BRD_ADC_COMP1_ADCCOMPVAL2(base);
            break;
        default:
            break;
    }
    
    return retValue;
 }

/*******************************************************************************
 * EOF
 ******************************************************************************/

