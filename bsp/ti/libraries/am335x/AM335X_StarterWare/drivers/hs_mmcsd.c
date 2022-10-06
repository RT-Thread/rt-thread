/**
 *  \file   hs_mmcsd.c
 *
 *  \brief  Device abstraction layer for HS MMC/SD
 *
 *   This file contains the device abstraction layer APIs for HS MMC/SD.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "soc_AM335x.h"
#include "hw_types.h"
#include "hs_mmcsd.h"
#include "hw_hs_mmcsd.h"

/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   Soft reset the MMC/SD controller
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 *
 * \return   0   on reset success
 *          -1   on reset fail
 *
 **/
int HSMMCSDSoftReset(unsigned int baseAddr)
{
    volatile unsigned int timeout = 0xFFFF;

    HWREG(baseAddr + MMCHS_SYSCONFIG) |= MMCHS_SYSCONFIG_SOFTRESET;

    do {
        if ((HWREG(baseAddr + MMCHS_SYSSTATUS) & MMCHS_SYSSTATUS_RESETDONE) ==
                                               MMCHS_SYSSTATUS_RESETDONE)
        {
            break;
        }
    } while(timeout--);

    if (0 == timeout)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * \brief   Soft reset the MMC/SD controller lines
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   flag          reset flags indicating the lines to be reset.
 *
 * flag can take the following values \n
 * HS_MMCSD_DATALINE_RESET \n
 * HS_MMCSD_CMDLINE_RESET \n
 * HS_MMCSD_ALL_RESET \n
 *
 * \return   0   on reset success
 *          -1   on reset fail
 *
 **/
int HSMMCSDLinesReset(unsigned int baseAddr, unsigned int flag)
{
    volatile unsigned int timeout = 0xFFFF;

    HWREG(baseAddr + MMCHS_SYSCTL) |= flag;

    do {
        if ((HWREG(baseAddr + MMCHS_SYSCTL) & flag) == flag)
        {
            break;
        }
    } while(timeout--);

    if (0 == timeout)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * \brief   Configure the MMC/SD controller standby, idle and wakeup modes
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   config        The standby, idle and wakeup modes
 *
 * flag can take the values (or a combination of the following)\n
 *     HS_MMCSD_STANDBY_xxx - Standby mode configuration \n
 *     HS_MMCSD_CLOCK_xxx - Clock mode configuration \n
 *     HS_MMCSD_SMARTIDLE_xxx - Smart IDLE mode configuration \n
 *     HS_MMCSD_WAKEUP_xxx - Wake up configuration \n
 *     HS_MMCSD_AUTOIDLE_xxx - Auto IDLE mode configuration \n
 *
 * \return  None.
 *
 **/
void HSMMCSDSystemConfig(unsigned int baseAddr, unsigned int config)
{
    HWREG(baseAddr + MMCHS_SYSCONFIG) &= ~(MMCHS_SYSCONFIG_STANDBYMODE |
                                          MMCHS_SYSCONFIG_CLOCKACTIVITY |
                                          MMCHS_SYSCONFIG_SIDLEMODE |
                                          MMCHS_SYSCONFIG_ENAWAKEUP |
                                          MMCHS_SYSCONFIG_AUTOIDLE);

    HWREG(baseAddr + MMCHS_SYSCONFIG) |= config;
}

/**
 * \brief   Configure the MMC/SD bus width
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   width         SD/MMC bus width
 *
 * width can take the values \n 
 *     HS_MMCSD_BUS_WIDTH_8BIT \n
 *     HS_MMCSD_BUS_WIDTH_4BIT \n
 *     HS_MMCSD_BUS_WIDTH_1BIT \n
 *
 * \return  None.
 *
 **/
void HSMMCSDBusWidthSet(unsigned int baseAddr, unsigned int width)
{
    switch (width)
    {
        case HS_MMCSD_BUS_WIDTH_8BIT: 
            HWREG(baseAddr + MMCHS_CON) |= MMCHS_CON_DW8;
        break;

        case HS_MMCSD_BUS_WIDTH_4BIT:
            HWREG(baseAddr + MMCHS_CON) &= ~MMCHS_CON_DW8;
            HWREG(baseAddr + MMCHS_HCTL) |= 
                    (MMCHS_HCTL_DTW_4_BITMODE << MMCHS_HCTL_DTW_SHIFT);
        break;

        case HS_MMCSD_BUS_WIDTH_1BIT:
            HWREG(baseAddr + MMCHS_CON) &= ~MMCHS_CON_DW8;
            HWREG(baseAddr + MMCHS_HCTL) &= ~MMCHS_HCTL_DTW;
            HWREG(baseAddr + MMCHS_HCTL) |=
                    (MMCHS_HCTL_DTW_1_BITMODE << MMCHS_HCTL_DTW_SHIFT);
        break;
    }
}

/**
 * \brief   Configure the MMC/SD bus voltage
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   volt          SD/MMC bus voltage
 *
 * volt can take the values \n 
 *     HS_MMCSD_BUS_VOLT_1P8 \n
 *     HS_MMCSD_BUS_VOLT_3P0 \n
 *     HS_MMCSD_BUS_VOLT_3P3 \n
 *
 * \return  None.
 *
 **/
void HSMMCSDBusVoltSet(unsigned int baseAddr, unsigned int volt)
{
    HWREG(baseAddr + MMCHS_HCTL) &= ~MMCHS_HCTL_SDVS;
    HWREG(baseAddr + MMCHS_HCTL) |= volt;
}

/**
 * \brief   Turn MMC/SD bus power on / off
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   pwr           power on / off setting
 *
 * pwr can take the values \n
 *     HS_MMCSD_BUS_POWER_ON \n
 *     HS_MMCSD_BUS_POWER_OFF \n
 *
 * \return  0 if the operation succeeded
 *         -1 if the operation failed
 *
 **/
int HSMMCSDBusPower(unsigned int baseAddr, unsigned int pwr)
{
    volatile unsigned int timeout = 0xFFFFF;

    HWREG(baseAddr + MMCHS_HCTL) =
            (HWREG(baseAddr + MMCHS_HCTL) & ~MMCHS_HCTL_SDBP) | pwr;

    if (pwr == HS_MMCSD_BUS_POWER_ON)
    {
        do {
                if ((HWREG(baseAddr + MMCHS_HCTL) & MMCHS_HCTL_SDBP) != 0)
                {
                    break;
                }
        } while(timeout--);
    }

    if (timeout == 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * \brief   Turn Internal clocks on / off
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   pwr           clock on / off setting
 *
 * pwr can take the values \n
 *     HS_MMCSD_INTCLOCK_ON \n
 *     HS_MMCSD_INTCLOCK_OFF \n
 *
 * \return  0 if the operation succeeded
 *         -1 if the operation failed
 *
 **/
int HSMMCSDIntClock(unsigned int baseAddr, unsigned int pwr)
{
    HWREG(baseAddr + MMCHS_SYSCTL) =
            (HWREG(baseAddr + MMCHS_SYSCTL) & ~MMCHS_SYSCTL_ICE) | pwr;

    if (pwr == HS_MMCSD_INTCLOCK_ON)
    {
        if(HSMMCSDIsIntClockStable(baseAddr, 0xFFFF) == 0)
        {
            return -1;
        }
    }

    return 0;
}

/**
 * \brief   Get the internal clock stable status
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   retry         retry times to poll for stable
 *
 * \note: if retry is zero the status is not polled. If it is non-zero status
 *        is polled for retry times
 *
 * \return  1 if the clock is stable
 *          0 if the clock is not stable
 *
 **/
unsigned int HSMMCSDIsIntClockStable(unsigned int baseAddr, unsigned int retry)
{
    volatile unsigned int status = 0;

    do {
            status = (HWREG(baseAddr + MMCHS_SYSCTL) & MMCHS_SYSCTL_ICS) >>
                                            MMCHS_SYSCTL_ICS_SHIFT;
            if ((status == 1) || (retry == 0))
            {
                break;
            }
    } while (retry--);

    return status;
}

/**
 * \brief   Set the supported voltage list
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   volt          Supported bus voltage
 *
 * volt can take the values (or a combination of)\n 
 *     HS_MMCSD_SUPPORT_VOLT_1P8 \n
 *     HS_MMCSD_SUPPORT_VOLT_3P0 \n
 *     HS_MMCSD_SUPPORT_VOLT_3P3 \n
 *
 * \return  None.
 *
 **/
void HSMMCSDSupportedVoltSet(unsigned int baseAddr, unsigned int volt)
{
    HWREG(baseAddr + MMCHS_CAPA) &= ~(MMCHS_CAPA_VS18 | MMCHS_CAPA_VS30 |
                                      MMCHS_CAPA_VS33);
    HWREG(baseAddr + MMCHS_CAPA) |= volt;
}

/**
 * \brief   Check if the controller supports high speed
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 *
 * \return  0 if high speed is not supported
 *          1 if high speed is supported
 *
 **/
unsigned int HSMMCSDIsHSupported(unsigned int baseAddr)
{
    return (HWREG(baseAddr + MMCHS_CAPA) & MMCHS_CAPA_HSS) >> MMCHS_CAPA_HSS_SHIFT;
}

/**
 * \brief   Set data timeout value
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   timeout       the data time out value
 *
 * Timeout value is the exponential of 2, as mentioned in the controller
 * reference manual.\n
 *
 * \note: Please use HS_MMCSD_DATA_TIMEOUT(n) for setting this value\n
 *        13 <= n <= 27
 *
 * \return  None.
 *
 **/
void HSMMCSDDataTimeoutSet(unsigned int baseAddr, unsigned int timeout)
{
    HWREG(baseAddr + MMCHS_SYSCTL) &= ~(MMCHS_SYSCTL_DTO);
    HWREG(baseAddr + MMCHS_SYSCTL) |= timeout;
}    

/**
 * \brief   Set output bus frequency
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   freq_in       The input/ref frequency to the controller
 * \param   freq_out      The required output frequency on the bus
 * \param   bypass        If the reference clock is to be bypassed
 *
 * \return   0  on clock enable success
 *          -1  on clock enable fail
 *
 * \note: If the clock is set properly, the clocks are enabled to the card with
 * the return of this function
 **/
int HSMMCSDBusFreqSet(unsigned int baseAddr, unsigned int freq_in,
                      unsigned int freq_out, unsigned int bypass)
{
    volatile unsigned int clkd = 0;
	volatile unsigned int regVal = 0;

    /* First enable the internal clocks */
    if (HSMMCSDIntClock(baseAddr, HS_MMCSD_INTCLOCK_ON) == -1)
    {
        return -1;
    }

    if (bypass == 0)
    {
        /* Calculate and program the divisor */
        clkd = freq_in / freq_out;
        clkd = (clkd < 2) ? 2 : clkd;
        clkd = (clkd > 1023) ? 1023 : clkd;

		/* Do not cross the required freq */
		while((freq_in/clkd) > freq_out)
		{
			if (clkd == 1023)
			{
				/* Return we we cannot set the clock freq */
			   return -1;
			}

			clkd++;
		}

        regVal = HWREG(baseAddr + MMCHS_SYSCTL) & ~MMCHS_SYSCTL_CLKD;
        HWREG(baseAddr + MMCHS_SYSCTL) = regVal | (clkd << MMCHS_SYSCTL_CLKD_SHIFT);

        /* Wait for the interface clock stabilization */
        if(HSMMCSDIsIntClockStable(baseAddr, 0xFFFF) == 0)
        {
            return -1;
        }
        
        /* Enable clock to the card */
        HWREG(baseAddr + MMCHS_SYSCTL) |= MMCHS_SYSCTL_CEN;
    }

    return 0;
}    

/**
 * \brief   Sends INIT stream to the card
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 *
 * \return   0  If INIT command could be initiated
 *          -1  If INIT command could not be completed/initiated
 *
 **/
int HSMMCSDInitStreamSend(unsigned int baseAddr)
{
    unsigned int status;

    /* Enable the command completion status to be set */
    HSMMCSDIntrStatusEnable(baseAddr, HS_MMCSD_SIGEN_CMDCOMP);

    /* Initiate the INIT command */
    HWREG(baseAddr + MMCHS_CON) |= MMCHS_CON_INIT;
    HWREG(baseAddr + MMCHS_CMD) = 0x00;

    status = HSMMCSDIsCmdComplete(baseAddr, 0xFFFF);

    HWREG(baseAddr + MMCHS_CON) &= ~MMCHS_CON_INIT;
    /* Clear all status */
    HSMMCSDIntrStatusClear(baseAddr, 0xFFFFFFFF);

    return status;
}

/**
 * \brief   Enables the controller events to set flags in status register
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_INTR_xxx
 *
 * \note: This function only enables the reflection of events in status register.
 * To enable events to generate a h/w interrupt request \see HSMMCSDIntrEnable()
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusEnable(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + MMCHS_IE) |= flag;
}

/**
 * \brief   Disables the controller events to set flags in status register
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_INTR_xxx
 *
 * \note: This function only enables the reflection of events in status register.
 * To disable events to generate a h/w interrupt request \see HSMMCSDIntrEnable()
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusDisable(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + MMCHS_IE) &= ~flag;
}

/**
 * \brief   Enables the controller events to generate a h/w interrupt request
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_SIGEN_xxx
 *
 * \return   none
 *
 **/
void HSMMCSDIntrEnable(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + MMCHS_ISE) |= flag;
	HSMMCSDIntrStatusEnable(baseAddr, flag);
}

/**
 * \brief   Gets the status bits from the controller 
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific status required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_STAT_xxx
 *
 * \return   status flags
 *
 **/
unsigned int HSMMCSDIntrStatusGet(unsigned int baseAddr, unsigned int flag)
{
    return HWREG(baseAddr + MMCHS_STAT) & flag;
}

/**
 * \brief   Clear the status bits from the controller 
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific status required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_STAT_xxx
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusClear(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + MMCHS_STAT) = flag;
}

/**
 * \brief    Checks if the command is complete
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    retry       retry times to poll for completion
 *
 * \return   1 if the command is complete
 *           0 if the command is not complete
 **/
unsigned int HSMMCSDIsCmdComplete(unsigned int baseAddr, unsigned int retry)
{
    volatile unsigned int status = 0;

    do {
        status = (HWREG(baseAddr + MMCHS_STAT) & MMCHS_STAT_CC) >>
                                    MMCHS_STAT_CC_SHIFT;
        if (( 1 == status) || (0  == retry))
        {
            break;
        }
    } while (retry--);

    return status;
}

/**
 * \brief    Checks if the transfer is complete
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    retry       retry times to poll for completion
 *
 * \return   1 if the transfer is complete
 *           0 if the transfer is not complete
 **/
unsigned int HSMMCSDIsXferComplete(unsigned int baseAddr, unsigned int retry)
{
    volatile unsigned int status = 0;

    do {
        status = (HWREG(baseAddr + MMCHS_STAT) & MMCHS_STAT_TC) >>
                                    MMCHS_STAT_TC_SHIFT;
        if ((1 == status) || (0 == retry))
        {
            break;
        }
    } while (retry--);

    return status;
}

/**
 * \brief    Set the block length/size for data transfer
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    blklen      Command to be passed to the controller/card
 * 
 * \note: blklen should be within the limits specified by the controller/card
 *
 * \return   none
 **/
void HSMMCSDBlkLenSet(unsigned int baseAddr, unsigned int blklen)
{
    HWREG(baseAddr + MMCHS_BLK) &= ~MMCHS_BLK_BLEN;
    HWREG(baseAddr + MMCHS_BLK) |= blklen;
}

/**
 * \brief    Pass the MMC/SD command to the controller/card
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers
 * \param   cmd         Command to be passed to the controller/card
 * \param   cmdArg      argument for the command
 * \param   data        data pointer, if it is a data command, else must be null
 * \param   nblks       data length in number of blocks (multiple of BLEN)
 * \param   dmaEn       Should dma be enabled (1) or disabled (0)
 *
 * \note: Please use HS_MMCSD_CMD(cmd, type, restype, rw) to form command
 *
 * \return   none
 **/
void HSMMCSDCommandSend(unsigned int baseAddr, unsigned int cmd,
                        unsigned int cmdarg, void *data,
                        unsigned int nblks, unsigned int dmaEn)
{
    if (NULL != data)
    {
        cmd |= (MMCHS_CMD_DP | MMCHS_CMD_MSBS | MMCHS_CMD_BCE);
    }

    if (1 == dmaEn)
    {
        cmd |= MMCHS_CMD_DE;
    }

    /* Set the block information; block length is specified separately */
    HWREG(baseAddr + MMCHS_BLK) &= ~MMCHS_BLK_NBLK;
    HWREG(baseAddr + MMCHS_BLK) |= nblks << MMCHS_BLK_NBLK_SHIFT;

    /* Set the command/command argument */
    HWREG(baseAddr + MMCHS_ARG) = cmdarg;
    HWREG(baseAddr + MMCHS_CMD) = cmd;

}

/**
 * \brief    Get the command response from the conntroller
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    rsp         pointer to buffer which is to be filled with the response
 *
 * \note: that this function shall return the values from all response registers.
 * Hence, rsp, must be a pointer to memory which can hold max response length.
 * It is the responsibility of the caller to use only the required/relevant
 * parts of the response
 *
 * \return   none
 **/
void HSMMCSDResponseGet(unsigned int baseAddr, unsigned int *rsp)
{
    unsigned int i;

    for (i = 0; i <=3; i++)
    {
        rsp[i] = HWREG(baseAddr + MMCHS_RSP(i));
    }
}

/**
 * \brief    Send the data to the card from the conntroller
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    data        pointer to buffer which is to be filled with the data
 * \param    len         length of the data
 *
 * \note: this function reads the data in chunks of 32 bits (4-byte words).
 * Hence, the len should be multiple of 4-byte words
 *
 * \return   none
 **/
void HSMMCSDDataGet(unsigned int baseAddr, unsigned char *data, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len/4; i++)
	{
		((unsigned int*)data)[i] = HWREG(baseAddr + MMCHS_DATA);
	}
}

/**
 * \brief    Check if the card is inserted and detected
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 *
 * \return   0  if the card is not inserted and detected
 *           1  if the card is inserted and detected
 *
 * \note: that this functional may not be available for all instances of the
 * controler. This function, is only useful of the controller has a dedicated
 * card detect pin. If not, the card detection mechanism is application
 * implementation specific
 **/
unsigned int HSMMCSDIsCardInserted(unsigned int baseAddr)
{
    return (HWREG(baseAddr + MMCHS_PSTATE) & MMCHS_PSTATE_CINS) >>
                MMCHS_PSTATE_CINS_SHIFT;
}

/**
 * \brief    Check if the card is write protected
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 *
 * \return   0  if the card is not write protected
 *           1  if the card is write protected
 * \note: that this functional may not be available for all instances of the
 * controler. This function, is only useful of the controller has a dedicated
 * write protect detect pin. If not, the write protect detection mechanism is
 * application implementation specific
 **/
unsigned int HSMMCSDIsCardWriteProtected(unsigned int baseAddr)
{
    return (HWREG(baseAddr + MMCHS_PSTATE) & MMCHS_PSTATE_WP) >>
                MMCHS_PSTATE_WP_SHIFT;
}

/**
 * \brief   This API can be used to save the register context of MMCSD
 *
 * \param   mmcsdBase     Base address of MMCSD instance
 * \param   contextPtr    Pointer to the structure where MMCSD register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void MMCSDContextSave(unsigned int mmcsdBase, MMCSDCONTEXT *contextPtr)
{
    contextPtr->capa = HWREG(mmcsdBase + MMCHS_CAPA);
    contextPtr->systemConfig = HWREG(mmcsdBase + MMCHS_SYSCONFIG);
    contextPtr->ctrlInfo = HWREG(mmcsdBase + MMCHS_CON);
    contextPtr->sysCtl = HWREG(mmcsdBase + MMCHS_SYSCTL);
    contextPtr->pState = HWREG(mmcsdBase + MMCHS_PSTATE);
    contextPtr->hctl = HWREG(mmcsdBase + MMCHS_HCTL);
}


/**
 * \brief   This API can be used to restore the register context of MMCSD
 *
 * \param   mmcsdBase     Base address of MMCSD instance
 * \param   contextPtr    Pointer to the structure where MMCSD register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void MMCSDContextRestore(unsigned int mmcsdBase, MMCSDCONTEXT *contextPtr)
{
    HWREG(mmcsdBase + MMCHS_SYSCONFIG) = contextPtr->systemConfig;
    HWREG(mmcsdBase + MMCHS_SYSCTL) = contextPtr->sysCtl;
    HWREG(mmcsdBase + MMCHS_CAPA) = contextPtr->capa;
    HWREG(mmcsdBase + MMCHS_CON) = contextPtr->ctrlInfo;
    HWREG(mmcsdBase + MMCHS_HCTL) = contextPtr->hctl;
    HWREG(mmcsdBase + MMCHS_PSTATE) = contextPtr->pState;
}
