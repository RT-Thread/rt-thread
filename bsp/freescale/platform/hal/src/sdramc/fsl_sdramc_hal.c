/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_sdramc_hal.h"

#if FSL_FEATURE_SOC_SDRAM_COUNT
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_Init
 * Description   : Reset all the configurable registers to be reset state for SDRAM.
 * It should be called before configuring the SDRAM controller module.
 *
 *END*************************************************************************/
void SDRAM_HAL_Init(SDRAM_Type * base)
{
    SDRAM_WR_CTRL(base, 0);
    SDRAM_WR_AC(base, 0, 0);
    SDRAM_WR_AC(base, 1, 0);
    SDRAM_WR_CM(base, 0, 0);
    SDRAM_WR_CM(base, 1, 0);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SendCommand
 * Description   : Sends the command to SDRAM
 *
 *END*************************************************************************/
void SDRAM_HAL_SendCommand(SDRAM_Type *base, sdram_block_selection_t whichBlock, sdram_command_t command)
{
    if(command == kSDRAMMrsCommand)
    {
        SDRAM_BWR_AC_IMRS(base, whichBlock, 1U);
    }
    else if (command == kSDRAMPrechargeCommand)
    {
        SDRAM_BWR_AC_IP(base, whichBlock, 1U);
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_IsCommandFinished
 * Description   : Sends the command to SDRAM
 *
 *END*************************************************************************/
bool SDRAM_HAL_IsCommandFinished(SDRAM_Type *base, sdram_block_selection_t whichBlock, sdram_command_t command)
{
    if(command == kSDRAMMrsCommand)
    {
        return SDRAM_BRD_AC_IMRS(base, whichBlock);
    }
    else
    {
        return SDRAM_BRD_AC_IP(base, whichBlock);
    }
}
/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SetAutoRefresh
 * Description   : Sets the refresh count which controls the refresh frequency.
 *
 *END*************************************************************************/
void SDRAM_HAL_SetAutoRefresh(SDRAM_Type *base, sdram_refresh_time_t refreshTime,
                               uint32_t busClock, uint32_t rowRefresh)
{
    uint32_t cycles;

    cycles = SDRAM_ONESEC_NANOSECOND / (busClock / 1000);   
    cycles = (rowRefresh * 1000 / cycles) / 16 - 1;
    assert(cycles <= SDRAM_CTRL_RC_MASK);
    SDRAM_BWR_CTRL_RC(base, cycles);
    SDRAM_BWR_CTRL_RTIM(base, refreshTime);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SetRefreshCmd
 * Description   : Enables or disables the refresh.
 *
 *END*************************************************************************/
void SDRAM_HAL_SetRefreshCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable)
{
    if(enable)
    {
      SDRAM_BWR_AC_RE(base, whichBlock, 1u);        
    }
    else
    {
      SDRAM_BWR_AC_RE(base, whichBlock, 0u);
    }

}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SetWriteProtectCmd
 * Description   : Enables or disables the write protection.
 *
 *END*************************************************************************/
void SDRAM_HAL_SetWriteProtectCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable)
{
    if(enable)
    {
      SDRAM_BWR_CM_WP(base, whichBlock, 1u);        
    }
    else
    {
      SDRAM_BWR_CM_WP(base, whichBlock, 0u);        
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SetOperateValidCmd
 * Description   : Enables or disables the operation valid.
 *
 *END*************************************************************************/
void SDRAM_HAL_SetOperateValidCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable)
{
    if(enable)
    {
       SDRAM_BWR_CM_V(base, whichBlock, 1u);        
    }
    else
    {
       SDRAM_BWR_CM_V(base, whichBlock, 0u);         
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_HAL_SetBlockControl
 * Description   : Sets the Port Size, specification latency, command bit and 
 * address for the SDRAM block.
 *
 *END*************************************************************************/
void SDRAM_HAL_SetBlockControl(SDRAM_Type *base, sdram_block_selection_t whichBlock, 
                    sdram_blockctl_configure_t *configure)
{
    assert(configure);
   
    SDRAM_BWR_AC_PS(base, whichBlock, configure->portSize);
    SDRAM_BWR_AC_CASL(base, whichBlock, configure->latency);
    SDRAM_BWR_AC_CBM(base, whichBlock, configure->location);
    SDRAM_BWR_AC_BA(base, whichBlock, (configure->address & SDRAM_AC_BA_MASK) >> SDRAM_AC_BA_SHIFT );
    SDRAM_BWR_CM_BAM(base, whichBlock, (configure->addressMask & SDRAM_CM_BAM_MASK) >> SDRAM_CM_BAM_SHIFT);
}


#endif /* FSL_FEATURE_SOC_CMT_COUNT */
/******************************************************************************
 * EOF
 ******************************************************************************/

