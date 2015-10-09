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

#include <stdlib.h>
#include "fsl_qspi_hal.h"
#if FSL_FEATURE_SOC_QuadSPIO_COUNT

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_Init
 * Description   : Init QSPI and put qspi into a known state.
 *
 *END**************************************************************************/
void QSPI_HAL_Init(QuadSPI_Type * base)
{
    QuadSPI_BWR_MCR_MDIS(base, 0U);
    QSPI_HAL_SoftwareReset(base);
    QSPI_HAL_ClearFifo(base, kQspiAllFifo);
    QSPI_HAL_ClearSeqId(base, kQspiAllSeq);
    /* To a known state */
    QuadSPI_WR_BUF0CR(base, 0U);
    QuadSPI_WR_BUF0IND(base,0U);
    QuadSPI_WR_BUF1CR(base,0U);
    QuadSPI_WR_BUF1IND(base,0U);
    QuadSPI_WR_BUF2CR(base,0U);
    QuadSPI_WR_BUF2IND(base,0U);
    QuadSPI_WR_BUF3CR(base,0U);
    QuadSPI_WR_DLPR(base,0U);
    QuadSPI_WR_FLSHCR(base,0U);
    QuadSPI_WR_RBCT(base,0U);
    QuadSPI_WR_TBCT(base,0U);
    QuadSPI_WR_RSER(base,0U);
    QuadSPI_WR_SFA1AD(base,0U);
    QuadSPI_WR_SFA2AD(base,0U);
    QuadSPI_WR_SFACR(base,0U);
    QuadSPI_WR_SFAR(base,0U);
    QuadSPI_WR_SFB1AD(base,0U);
    QuadSPI_WR_SFB2AD(base,0U);
    QuadSPI_WR_SMPR(base,0U);
    QuadSPI_WR_SOCCR(base,0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_Deinit
 * Description   : Deinit QSPI. This function will disable QSPI clock.
 *
 *END**************************************************************************/
void QSPI_HAL_SoftwareReset(QuadSPI_Type * base)
{
    /* Reset QSPI AHB domain */
    QuadSPI_BWR_MCR_SWRSTHD(base,1U);
    /* Reset QSPI buffer */
    QuadSPI_BWR_MCR_SWRSTSD(base,1U);
    /* Wait several ticks until the ahb domain and serial flash domain are reset*/
    for (volatile uint32_t i=0; i<100; i++)
    {
        __ASM("nop");
    }
    /*Disable QSPI clock*/
    QuadSPI_BWR_MCR_MDIS(base, 1U);
    /* Clear the reset flag */
    QuadSPI_BWR_MCR_SWRSTSD(base,0U);
    QuadSPI_BWR_MCR_SWRSTHD(base,0U);
    QuadSPI_BWR_MCR_MDIS(base, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetFlashTiming
 * Description   : Set flash timing parameter to QSPI. This includes data hold
 * time, CS hold time and CS setup time.
 *END**************************************************************************/
void QSPI_HAL_SetFlashTiming(QuadSPI_Type * base, qspi_flash_timing_t * TimingConfig)
{
    QuadSPI_BWR_FLSHCR_TCSS(base,TimingConfig->CSHoldTime);
    QuadSPI_BWR_FLSHCR_TDH(base,TimingConfig->dataHoldTime);
    QuadSPI_BWR_FLSHCR_TCSH(base,TimingConfig->CSSetupTime); /* This only valid in DDR mode */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_ConfigFlash
 * Description   : Configure serial flash parameter, including flash size, address
 * lookup table and etc.
 *END**************************************************************************/
void QSPI_HAL_ConfigFlash(QuadSPI_Type * base, qspi_flash_config_t *config)
{
    assert(config != NULL);
    /* First disable QSPI */
    QuadSPI_BWR_MCR_MDIS(base,1U);
    /* Config the serial flash size */
    uint32_t address = FSL_FEATURE_QSPI_AMBA_BASE + config->flashA1Size;
    QuadSPI_WR_SFA1AD(base, address);
    address += config->flashA2Size;
    QuadSPI_WR_SFA2AD(base,address);
    address += config->flashB1Size;
    QuadSPI_WR_SFB1AD(base,address);
    address += config->flashB2Size;
    QuadSPI_WR_SFB2AD(base,address);
    /* Set Word Addressable feature */
    QuadSPI_BWR_SFACR_WA(base,config->wordaddress);
    /* Set Cloumn address space */
    QuadSPI_BWR_SFACR_CAS(base,config->cloumnspace);
    /* Config look up table */
    QSPI_HAL_UnlockLUT(base);
    uint32_t i = 0;
    for (i = 0; i < FSL_FEATURE_QSPI_LUT_DEPTH; i ++)
    {
        QuadSPI_WR_LUT(base, i, config->lookuptable[i]);
    }
    QSPI_HAL_LockLUT(base);
    /* Config parallel mode */
    QuadSPI_BWR_IPCR_PAR_EN(base,config->parallelmode);
    QuadSPI_BWR_BFGENCR_PAR_EN(base,config->parallelmode);
    /* Config flash timing */
    QuadSPI_BWR_FLSHCR_TCSS(base,config->CSHoldTime);
    QuadSPI_BWR_FLSHCR_TDH(base,config->dataHoldTime);
    QuadSPI_BWR_FLSHCR_TCSH(base,config->CSSetupTime); /* This only valid in DDR mode */
    /* Set flash endianness */
    QSPI_HAL_SetEndianness(base, config->endian);
    /* Set DQS feature */
    if (config->DQSEnable)
    {
        QuadSPI_BWR_MCR_DQS_EN(base,true);
        QuadSPI_BWR_MCR_DQS_LAT_EN(base, true);
        /* Configure DQS features */
        QuadSPI_BWR_SOCCR_DLYTAPSELA(base, config->dqs_config.portADelayTapNum);
        QuadSPI_BWR_SOCCR_DLYTAPSELB(base,config->dqs_config.portBDelayTapNum);
        QuadSPI_BWR_SOCCR_DQSINVSEL(base, config->dqs_config.DQSClkInverse);
        QuadSPI_BWR_SOCCR_DQSPADLPEN(base,config->dqs_config.DQSPadLoopback);
        QuadSPI_BWR_SOCCR_DQSLPEN(base,config->dqs_config.DQSLoopback);
        QuadSPI_BWR_SOCCR_DQSPHASEL(base, config->dqs_config.shift);
    }
    if (config->DDREnable)
    {
        QuadSPI_BWR_MCR_DDR_EN(base,true);        
    }
    if (config->octalmode)
    {
        /* SOCCR bit settings */
        QuadSPI_BWR_SOCCR_OCTEN(base,true);
        QuadSPI_BWR_SOCCR_DIFFCKEN(base,true);
        QuadSPI_BWR_SOCCR_CK2EN(base,true);
    }
    if ((config->DDREnable) || (config->DQSEnable))
    {
        QuadSPI_WR_DLPR(base, config->dataLearnValue);
    }
    /* Enable QSPI again */
    QuadSPI_BWR_MCR_MDIS(base,0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_ClearFifo
 * Description   : Clear Tx/Rx FIFO/buffer pointer and state.
 *
 *END**************************************************************************/
void QSPI_HAL_ClearFifo(QuadSPI_Type * base, qspi_fifo_t fifo)
{
    uint32_t val = QuadSPI_RD_MCR(base);
    QuadSPI_WR_MCR(base,(val | (uint32_t)fifo));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetAHBBufferSize
 * Description   : Set AHB buffer size.
 *
 *END**************************************************************************/
void QSPI_HAL_SetAHBBufferSize(QuadSPI_Type * base, uint32_t buff_index, uint32_t size)
{
    assert(buff_index < FSL_FEATURE_QSPI_AHB_BUFFER_COUNT);
    switch (buff_index)
    {
        case 0:
            QuadSPI_BWR_BUF0CR_ADATSZ(base,size/8);
            break;
        case 1:
            QuadSPI_BWR_BUF1CR_ADATSZ(base,size/8);
            break;
        case 2:
            QuadSPI_BWR_BUF2CR_ADATSZ(base,size/8);
            break;
        case 3:
            QuadSPI_BWR_BUF3CR_ADATSZ(base,size/8);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetAHBBufferMaster
 * Description   : Set AHB buffer master. Only this master can access the buffer.
 *
 *END**************************************************************************/
void QSPI_HAL_SetAHBBufferMaster(QuadSPI_Type * base, uint32_t buff_index, uint32_t master_id)
{
    assert(buff_index < FSL_FEATURE_QSPI_AHB_BUFFER_COUNT);
    switch (buff_index)
    {
        case 0:
            QuadSPI_BWR_BUF0CR_MSTRID(base,master_id);
            break;
        case 1:
            QuadSPI_BWR_BUF1CR_MSTRID(base,master_id);
            break;
        case 2:
            QuadSPI_BWR_BUF2CR_MSTRID(base,master_id);
            break;
        case 3:
            QuadSPI_BWR_BUF3CR_MSTRID(base,master_id);
            break;
        default:
            break;
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetParallelModeCmd
 * Description   : Enable or disable command parallel mode.
 *
 *END**************************************************************************/
void QSPI_HAL_SetParallelModeCmd(QuadSPI_Type * base, qspi_command_seq_t command, bool enable)
{
    if ((uint32_t)command & kQspiIPSeq)
    {
        QuadSPI_BWR_IPCR_PAR_EN(base,enable);
    }
    if ((uint32_t)command & kQspiBufferSeq)
    {
        QuadSPI_BWR_BFGENCR_PAR_EN(base,enable);
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_UnlockLUT
 * Description   : Unlock lookup table.
 *
 *END**************************************************************************/
void QSPI_HAL_UnlockLUT(QuadSPI_Type * base)
{
    /* Unlock the LUT */
    QuadSPI_WR_LUTKEY(base, 0x5AF05AF0U);
    QuadSPI_WR_LCKCR(base, 0x2U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_LockLUT
 * Description   : Lock lookup table. Users cannot write LUT unless unlocked.
 *
 *END**************************************************************************/
void QSPI_HAL_LockLUT(QuadSPI_Type * base)
{
    /* Lock the lookup table */
    QuadSPI_WR_LUTKEY(base, 0x5AF05AF0U);
    QuadSPI_WR_LCKCR(base, 0x1U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetLUT
 * Description   : Set a serial flash command into a LUT register.
 *
 *END**************************************************************************/
void QSPI_HAL_SetLUT(QuadSPI_Type * base, uint32_t index, uint32_t command)
{
    assert (index < FSL_FEATURE_QSPI_LUT_DEPTH);
    /* Write Lookup table */
    QuadSPI_WR_LUT(base,index,command);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetIntCmd
 * Description   : Enable or disable the one or more interrupt source.
 *
 *END**************************************************************************/
void QSPI_HAL_SetIntCmd(QuadSPI_Type * base, uint32_t IntFlag, bool enable)
{
    uint32_t val = QuadSPI_RD_RSER(base);
    if (enable == true)
    {
        QuadSPI_WR_RSER(base, val |IntFlag);
    }
    else
    {
        QuadSPI_WR_RSER(base, (val & (~IntFlag)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_SetDmaCmd
 * Description   : Enable or disable the one or more dma source.
 *
 *END**************************************************************************/
void QSPI_HAL_SetDmaCmd(QuadSPI_Type * base, qspi_dma_flag_t DmaFlag, bool enable)
{
    uint32_t val = QuadSPI_RD_RSER(base);
    if (enable == true)
    {
        QuadSPI_WR_RSER(base, (val|(uint32_t)DmaFlag));
    }
    else
    {
        QuadSPI_WR_RSER(base, (val & (~(uint32_t)DmaFlag)));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_GetRxFifoAddr
 * Description   : Enable or disable the one or more dma source.
 *
 *END**************************************************************************/
uint32_t QSPI_HAL_GetRxFifoAddr(QuadSPI_Type * base)
{
    /* From RDBR */
    if (QuadSPI_BRD_RBCT_RXBRD(base))
    {
        return (uint32_t)(&QuadSPI_RBDR_REG(base, 0U));
    }
    else
    {
        /* From ARDB */
        return FSL_FEATURE_QSPI_ARDB_BASE;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_WriteDataBlocking
 * Description   : Write a series of data into Tx fifo in blocking way.
 *
 *END**************************************************************************/
void QSPI_HAL_WriteDataBlocking(QuadSPI_Type * base, uint32_t * addr, uint32_t size)
{
    assert (size >= 16U);
    /* Write data to IP buffer */
    uint32_t i = 0;
    for (i = 0; i < size/4; i ++)
    {
        /* Check if the buffer is full */
        while(QuadSPI_BRD_SR_TXFULL(base)){}
        QuadSPI_WR_TBDR(base, *addr++);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_ReadDataBlocking
 * Description   : Read a series of data from Rx fifo in blocking way.
 *
 *END**************************************************************************/
void QSPI_HAL_ReadDataBlocking(QuadSPI_Type * base, uint32_t * addr, uint32_t size)
{
    assert(addr && size);
    uint32_t i = 0, j = 0, level = 0;
    while (i < size/4)
    {
        level = QuadSPI_BRD_RBSR_RDBFL(base);
        /* Check if there is data */
        while (!level){}
        /* Data from RBDR */
        if (QuadSPI_BRD_RBCT_RXBRD(base))
        {
            for (j = 0; j < level; j ++)
            {
                addr[i + j] = QuadSPI_RD_RBDR(base,j);
            }
        }
        else
        {
           /* Data from ARDB. */
           for (j = 0; j < level; j ++)
           {
               addr[i + j] = ((uint32_t *)FSL_FEATURE_QSPI_ARDB_BASE)[j];
           }
        }
        i += level;
    } 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_HAL_ReadData
 * Description   : Read a data from Rx FIFO or buffer.
 *
 *END**************************************************************************/
uint32_t QSPI_HAL_ReadData(QuadSPI_Type * base, uint32_t index)
{
    if (QuadSPI_BRD_RBCT_RXBRD(base))
    {
        return QuadSPI_RD_RBDR(base, index); 
    }
    else
    {
       /* Data from ARDB. */
       return((uint32_t *)FSL_FEATURE_QSPI_ARDB_BASE)[index];
    }
}
#endif

