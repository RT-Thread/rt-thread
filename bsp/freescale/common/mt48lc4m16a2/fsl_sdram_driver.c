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
#include "fsl_sdram_driver.h"
#include "fsl_sdramc_driver.h"
#include "fsl_os_abstraction.h"
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_DRV_Init
 * Description   : Initializes the SDRAM device.
 * The function is used to drive the MT48LC4M16A2 SDRAM external memory.
 *END**************************************************************************/
void SDRAM_Init(void)
{
    sdram_refresh_config_t configure;
    sdram_blockctl_configure_t ctlConfig;

    /* SDRAM configuration*/
    ctlConfig.portSize = kSDRAM16BitPortSize;
    ctlConfig.location = kSDRAMCommandbit19;
    /* Time configure for 24Mhz as the clock frequency*/
    /* SDRAM with trc-60ns(min), trcd-15ns(min), trp-15ns(min), tras-37ns (min) */
    ctlConfig.latency = kSDRAMLatencyOne;    
    ctlConfig.address = SDRAM_START_ADDRESS;
    ctlConfig.addressMask = 0x7c0000;    /* 8MByte*/

    configure.refreshTime = kSDRAMRefreshThreeClocks;   /*trc=txsr-67ns(min)*/
    configure.sdramRefreshRow = 15625;

    /* SDRAM controller initialization*/
    SDRAM_DRV_Init(0, &configure, kSDRAMBlock0, &ctlConfig);
    
    /* SDRAM initialization sequence */
    SDRAM_Initialization_sequence(kSDRAMBlock0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SDRAM_Initialization_sequence
 * Description   : The SDRAM Initializes sequence.
 *END**************************************************************************/
void SDRAM_Initialization_sequence(sdram_block_selection_t whichBlock)
{
    uint32_t *mrsAddr = 0;
    /* Issue a PALL command */
    SDRAM_DRV_SendCommand(0, whichBlock, kSDRAMPrechargeCommand);

    /*  Accessing a SDRAM location*/
    *(uint16_t *)(SDRAM_START_ADDRESS) = SDRAM_COMMAND_ACCESSVALUE;
  
    /* Enable the refresh */
    SDRAM_DRV_SetRefreshCmd(0, whichBlock, true);

    /* Wait for cycles */
    OSA_TimeDelay(1);

    /* Issue MSR command */
    SDRAM_DRV_SendCommand(0, whichBlock, kSDRAMMrsCommand);
    /* Put the right value on SDRAM address bus for SDRAM mode register,
    *  The address of SDRAM Pins is as below:
    *  A2 ~ A0:   burst length   0
    *     000->1 
    *     001->2
    *     010->4
    *     011->8
    *     res
    * A3:   burst type
    *        0 -> seq
    *        1 -> Interleave
    *
    * A6 ~ A4:  CAS latency
    *       000-> res
    *       001-> 1
    *       010-> 2
    *      011-> 3
    *       res
    * A8 ~ A7:  Operationg Mode
    *       00->Stardard Operation
    *       res
    * A9:    Write Burst Mode
    *       0-> Programmed Burst Length
    *      1-> Single Location Access
    */
    mrsAddr = (uint32_t *)(SDRAM_START_ADDRESS + 0x00000800U);
    *mrsAddr = SDRAM_COMMAND_ACCESSVALUE;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
