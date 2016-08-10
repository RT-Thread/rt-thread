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

#include <string.h>
#include "fsl_sdramc_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_SDRAM_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_Init
 * Description   : Initialize SDRAM controller.
 *
 *END**************************************************************************/
void SDRAM_DRV_Init(uint32_t instance, sdram_refresh_config_t *configure, sdram_block_selection_t whichBlock,
                    sdram_blockctl_configure_t *ctlConfig)
{
    assert(instance < SDRAM_INSTANCE_COUNT);
    assert(configure);
    uint32_t busClock;
    SDRAM_Type * base = g_sdramBase[instance];

    /* Un-gate sdram controller clock*/
    CLOCK_SYS_EnableSdramcClock(instance);

    /* Reset the SDRAM module*/
    SDRAM_HAL_Init(base);

    /* Initialize SDRAM Auto refresh*/
    busClock = CLOCK_SYS_GetFlexbusFreq();
    SDRAM_HAL_SetAutoRefresh(base, configure->refreshTime, busClock,configure->sdramRefreshRow);        

    /* Sets the SDRAM block*/
    SDRAM_HAL_SetBlockControl(base, whichBlock, ctlConfig);  

    /* Sets the valid access*/ 
    SDRAM_HAL_SetOperateValidCmd(base, whichBlock, true);  
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_Deinit
 * Description   : Deinitialize SDRAM
 *
 *END**************************************************************************/
void SDRAM_DRV_Deinit(uint32_t instance)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    /*Reset SDRAM*/
    SDRAM_HAL_Init(base);

    /* Disable SDRAM clock. */
    CLOCK_SYS_DisableSdramcClock(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SendCommand()
 * Description   : Sends the command to SDRAM. There are Precharge command and MRS command.
 *
 *END**************************************************************************/
void SDRAM_DRV_SendCommand(uint32_t instance, sdram_block_selection_t whichBlock, sdram_command_t command)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SendCommand(base, whichBlock, command);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SDRAM_DRV_IsCommandFinished
 * Description   : Gets the SDRAM command execute status
 *
 *END*************************************************************************/
bool SDRAM_DRV_IsCommandFinished(uint32_t instance, sdram_block_selection_t whichBlock, sdram_command_t command)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    return SDRAM_HAL_IsCommandFinished(base, whichBlock, command);    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SendSelfRefreshCmd
 * Description   : Send self-refresh command to SDRAM.
 *
 *END**************************************************************************/
void SDRAM_DRV_SendSelfRefreshCmd(uint32_t instance)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SendSelfRefreshCmd(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SendSelfRefreshExitCmd
 * Description   : Send self-refresh command to SDRAM.
 *
 *END**************************************************************************/
void SDRAM_DRV_SendSelfRefreshExitCmd(uint32_t instance)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SendSelfRefreshExitCmd(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SetRefreshCmd
 * Description   : Enables/disables the SDRAM Refresh.
 *
 *END**************************************************************************/
void SDRAM_DRV_SetRefreshCmd(uint32_t instance, sdram_block_selection_t whichBlock, bool enable)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SetRefreshCmd(base, whichBlock, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SetWriteProtectCmd
 * Description   : Enables or disables the write protect.
 *
 *END**************************************************************************/
void SDRAM_DRV_SetWriteProtectCmd(uint32_t instance, sdram_block_selection_t whichBlock, bool enable)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SetWriteProtectCmd(base, whichBlock, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_SetOperateValidCmd
 * Description   : Enables/disables the operation valid.
 *
 *END**************************************************************************/
void SDRAM_DRV_SetOperateValidCmd(uint32_t instance,  sdram_block_selection_t whichBlock, bool enable)
{
    assert(instance < SDRAM_INSTANCE_COUNT);

    SDRAM_Type * base = g_sdramBase[instance];

    SDRAM_HAL_SetOperateValidCmd(base, whichBlock, enable);
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

