/**
 *  \file   gpmc.c
 *
 *  \brief  GPMC  APIs.
 *
 *   This file contains the device abstraction layer APIs for GPMC.
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

#include "hw_gpmc.h"
#include "hw_types.h"
#include "gpmc.h"

/*******************************************************************************
*                       INTERNAL API DEFINITIONS
*******************************************************************************/
/**
* \brief   This function reads the IP revision code of GPMC.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  ipRev          IP revision code of GPMC.\n
*/
unsigned int  GPMCRevisionGet(unsigned int baseAddr)
{
    unsigned int ipRev;

    ipRev =  (HWREG(baseAddr + GPMC_REVISION) & GPMC_REVISION_REVISION);

    return (ipRev);
}

/**
* \brief   This function sets the idle mode for gpmc.\n
*
* \param   baseaddr       Memory address of gpmc.\n
* 
* \param   mode           Idle mode.\n
*                         This can take one of the following values :\n
*                         GPMC_IDLEMODE_FORCEIDLE -- for force-idle. \n
*                         GPMC_IDLEMODE_NOIDLE    -- for no-idle. \n
*                         GPMC_IDLEMODE_SMARTIDLE -- for smart-idle.\n 
*
* \return  none.\n
*/
void  GPMCIdleModeSelect(unsigned int baseAddr, unsigned int mode)
{
    HWREG(baseAddr + GPMC_SYSCONFIG) &= ~GPMC_SYSCONFIG_IDLEMODE;
    HWREG(baseAddr + GPMC_SYSCONFIG) |= ((mode <<
                                         GPMC_SYSCONFIG_IDLEMODE_SHIFT)
                                         & GPMC_SYSCONFIG_IDLEMODE);
}

/**
* \brief   This function configs the internal OCP clock gating strategy.\n
*
* \param   baseaddr       Memory address of gpmc.\n
* 
* \param   configVal      Config value.\n
*                         This can take one of the following values :\n
*                         GPMC_AUTOIDLE_FREERUN -- When Interface clock is 
*                                                  free-running. \n
*                         GPMC_AUTOIDLE_AUTORUN -- When Automatic Interface clk 
*                                                  gating strategy is applied.\n
*
* \return  none.\n
*/
void  GPMCAutoIdleConfig(unsigned int baseAddr, unsigned int configVal)
{
    HWREG(baseAddr + GPMC_SYSCONFIG) &= ~GPMC_SYSCONFIG_AUTOIDLE;
    HWREG(baseAddr + GPMC_SYSCONFIG)= ((configVal <<
                                        GPMC_SYSCONFIG_AUTOIDLE_SHIFT)
                                        & GPMC_SYSCONFIG_AUTOIDLE);
}

/**
* \brief   This function resets the GPMC.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  None.\n
*/

void  GPMCModuleSoftReset(unsigned int baseAddr)
{

    HWREG(baseAddr + GPMC_SYSCONFIG)= (GPMC_SYSCONFIG_SOFTRESET_RESET <<
                                       GPMC_SYSCONFIG_SOFTRESET_SHIFT);
}

/**
* \brief   This function gets the software resets status of GPMC.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  status         Reset status : \n
*                            0 : Module reset is on-going.\n
*                            1 : Module reset is completed.\n
*/

unsigned int  GPMCModuleResetStatusGet(unsigned int baseAddr)
{
    unsigned int resetStat;

    resetStat = (HWREG(baseAddr + GPMC_SYSSTATUS) & GPMC_SYSSTATUS_RESETDONE);

    return (resetStat);
}

/**
* \brief   This function gets Interrupt status of interrupt passed.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag for which interrupt status has to get.\n
*                         This can take one of the following values :\n
*                         GPMC_FIFOEVENT_STATUS         : For FIFOEvent 
*                                                         interrupt status.\n
*                         GPMC_TERMINALCOUNT_STATUS     : For TerminalCountEvent
*                                                         interrupt status.\n
*                         GPMC_WAIT0EDGEDETECTION_STATUS: For Wait1 Edge
*                                                         Detection interrupt
*                                                         status.\n
*                         GPMC_WAIT1EDGEDETECTION_STATUS: For Wait1 Edge
*                                                         Detection interrupt 
*                                                         status.\n
*
* 
* \return  intSts         Interrupt Status. Return value meaning depends on the
*                         interrupt flag passed. \n
*                         if flag is GPMC_FIFOEVENT_STATUS, then \n
*                            0 : Less than FIFOTHRESHOLD bytes are available in 
*                                prefetch/read mode.\n
*                                Less than FIFOTHRESHOLD byte free spaces are
*                                available in write-posting/write mode. \n
*                            1 : Atleast FIFOTHRESHOLD bytes are available in 
*                                prefetch/read mode.\n
*                                Atlease FIFOTHRESHOLD byte free places are
*                                available in write-posting/write mode.\n
*                         if flag is GPMC_TERMINALCOUNT_STATUS, then \n
*                            0 : CountValue is greater than 0.\n
*                            1 : CountValue is equal to 0.\n
*                         if flag is GPMC_WAIT0EDGEDETECTION_STATUS, then \n
*                            0 : A transition on WAIT0 input pin has not been 
*                                detected.\n
*                            1 : A transition on WAIT0 input pin has been 
*                                detected.\n
*                         if flag is GPMC_WAIT1EDGEDETECTION_STATUS, then \n
*                            0 : A transition on WAIT1 input pin has not been 
*                                detected.\n
*                            1 : A transition on WAIT1 input pin has been 
*                                detected.\n
*                
*/
unsigned int  GPMCIntStatusGet(unsigned int baseAddr, unsigned int flag)
{

    unsigned int retVal;

    retVal = 0;

    switch(flag)
    {
        case GPMC_FIFOEVENT_STATUS:
             retVal = ((HWREG(baseAddr + GPMC_IRQSTATUS) &
                        GPMC_IRQSTATUS_FIFOEVENTSTATUS) >>
                        GPMC_IRQSTATUS_FIFOEVENTSTATUS_SHIFT );
        break;
        case GPMC_TERMINALCOUNT_STATUS:
             retVal = ((HWREG(baseAddr + GPMC_IRQSTATUS) &
                        GPMC_IRQSTATUS_TERMINALCOUNTSTATUS) >>
                        GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_SHIFT);
        break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
             retVal = ((HWREG(baseAddr + GPMC_IRQSTATUS) &
                        GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS) >>
                        GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_SHIFT);
        break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
             retVal = ((HWREG(baseAddr + GPMC_IRQSTATUS) &
                        GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS) >>
                        GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_SHIFT);
        break;
    }

    return (retVal);
}

/**
* \brief   This function clears/resets the interrupt status.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag for which interrupt status has to reset.\n
*                         This can take one of the following values :\n
*                         GPMC_FIFOEVENT_STATUS         : For FIFOEvent 
*                                                         interrupt status.\n
*                         GPMC_TERMINALCOUNT_STATUS     : For TerminalCountEvent
*                                                         interrupt status.\n
*                         GPMC_WAIT0EDGEDETECTION_STATUS: For Wait1 Edge
*                                                         Detection interrupt
*                                                         status.\n
*                         GPMC_WAIT1EDGEDETECTION_STATUS: For Wait1 Edge
*                                                         Detection interrupt 
*                                                         status.\n
*
* \return  None. 
*
*/
void  GPMCIntStatusClear(unsigned int baseAddr, unsigned int flag)
{
    switch(flag)
    {
        case GPMC_FIFOEVENT_STATUS:
             HWREG(baseAddr + GPMC_IRQSTATUS) |=
                  (GPMC_IRQSTATUS_FIFOEVENTSTATUS_RESET <<
                   GPMC_IRQSTATUS_FIFOEVENTSTATUS_SHIFT);

        break;
        case GPMC_TERMINALCOUNT_STATUS:
             HWREG(baseAddr + GPMC_IRQSTATUS) |=
                  (GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_RESET <<
                   GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_SHIFT);
        break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
             HWREG(baseAddr + GPMC_IRQSTATUS) |=
                  (GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_RESET <<
                   GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_SHIFT);
        break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
             HWREG(baseAddr + GPMC_IRQSTATUS) |=
                  (GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_RESET <<
                   GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_SHIFT);
        break;
    }
}

/**
* \brief   This function enables the interrupts.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag for which interrupt has to enable.
*                         This can take one of the following values :\n
*                         GPMC_FIFOEVENT_INT          : For FIFOEvent interrupt.\n
*                         GPMC_TERMINALCOUNT_INT      : For TerminalCountEvent
*                                                       interrupt.\n
*                         GPMC_WAIT0EDGEDETECTION_INT : For Wait1 Edge
*                                                       Detection interrupt.\n
*                         GPMC_WAIT1EDGEDETECTION_INT : For Wait1 Edge
*                                                       Detection interrupt.\n
*
*
* \return  None. \n
*
*/
void  GPMCIntEnable(unsigned int baseAddr, unsigned int flag)
{
    switch(flag)
    {
        case GPMC_FIFOEVENT_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) |= GPMC_IRQENABLE_FIFOEVENTENABLE;
        break;
        case GPMC_TERMINALCOUNT_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) |=
                  (GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE);
        break;
        case GPMC_WAIT0EDGEDETECTION_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) |=
                  (GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE);
        break;
        case GPMC_WAIT1EDGEDETECTION_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) |=
                  (GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE);
        break;
    }
}

/**
* \brief   This function disable/masks the interrupts.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag for which interrupt has to mask.\n
*                         This can take one of the following values :\n
*                         GPMC_FIFOEVENT_INT          : For FIFOEvent interrupt.\n
*                         GPMC_TERMINALCOUNT_INT      : For TerminalCountEvent
*                                                       interrupt.\n
*                         GPMC_WAIT0EDGEDETECTION_INT : For Wait1 Edge
*                                                       Detection interrupt.\n
*                         GPMC_WAIT1EDGEDETECTION_INT : For Wait1 Edge
*                                                       Detection interrupt. \n
*
* \return  None.\n 
*
*/
void  GPMCIntDisable(unsigned int baseAddr, unsigned int flag)
{
    switch(flag)
    {
        case GPMC_FIFOEVENT_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) &=
                  (~GPMC_IRQENABLE_FIFOEVENTENABLE);
        break;
        case GPMC_TERMINALCOUNT_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) &=
                  (~GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE);
        break;
        case GPMC_WAIT0EDGEDETECTION_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) &=
                  (~GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE);
        break;
        case GPMC_WAIT1EDGEDETECTION_INT:
             HWREG(baseAddr + GPMC_IRQENABLE) &=
                  (~GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE);
        break;
    }
}

/**
* \brief   This function sets the start timeout value(TIMEOUTSTARTVALUE) 
*          of the timeout counter.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   timoutVal      Timeout start Value in GPMC_FCLK cycles.\n
*
* \return  None. \n
*
*/
void  GPMCTimeOutStartValSet(unsigned int baseAddr, unsigned int timeoutVal)
{
    HWREG(baseAddr + GPMC_TIMEOUT_CONTROL) &=
                                       ~GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE;
    HWREG(baseAddr + GPMC_TIMEOUT_CONTROL) |= ((timeoutVal <<
                                GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE_SHIFT) &
                                GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE);
}

/**
* \brief   This function configures the timeout feature.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag to indicate whether to enable or disable the 
*                         feature.\n
*                         This can take one of the following values :\n
*                         GPMC_TIMEOUTFEATURE_ENABLE  - To enable the timout
*                                                       feature.\n
*                         GPMC_TIMEOUTFEATURE_DISABLE - To disable the timout 
*                                                       feature.\n
* \return  None. \n
*
*/
void  GPMCTimeOutFeatureConfig(unsigned int baseAddr, unsigned int flag)
{
    if(flag == GPMC_TIMEOUTFEATURE_ENABLE)
    {
        HWREG(baseAddr + GPMC_TIMEOUT_CONTROL) |=
                                   GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TOENABLED;
    }
    else if (flag == GPMC_TIMEOUTFEATURE_DISABLE)
    {
        HWREG(baseAddr + GPMC_TIMEOUT_CONTROL) &=
                                (~GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TOENABLED);
    }
}

/**
* \brief   This function returns the address of illegal access when an error 
*          occures.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  illegalAddrVal Address of illegal access. \n
*
*/
unsigned int  GPMCErrAddrGet(unsigned int baseAddr)
{
    unsigned int retVal;

    retVal = (HWREG(baseAddr + GPMC_ERR_ADDRESS) & GPMC_ERR_ADDRESS_ILLEGALADD);

    return (retVal);
}

/**
* \brief   This function returns the status of error validity.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  ErrValstatus   Error validity status. \n
*                         0 : Error fields are no longer valid.\n
*                         1 : Error detected and logged in the 
*                             other error fields.\n
*
*/
unsigned int  GPMCErrValStatusGet(unsigned int baseAddr)
{
    unsigned int status;

    status = (HWREG(baseAddr + GPMC_ERR_TYPE) & GPMC_ERR_TYPE_ERRORVALID);

    return (status);
}

/**
* \brief   This function returns the System Command of the transaction 
*          that caused the error.\n
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \return  errCmd         System Command that caused the error. \n
*
*/
unsigned int  GPMCErrSysCmdGet(unsigned int baseAddr)
{
    unsigned int cmd;

    cmd = ((HWREG(baseAddr + GPMC_ERR_TYPE) & GPMC_ERR_TYPE_ILLEGALMCMD)
            >> GPMC_ERR_TYPE_ILLEGALMCMD_SHIFT);

    return (cmd);
}

/**
* \brief   This function returns whether passed error is occured or not.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   errFlag        Type of the error.\n
*                         This can take one of the following values :\n
*                         GPMC_TIMEOUT_ERROR     -- For timeout error.\n
*                         GPMC_NOTSUPPMCMD_ERROR -- For non-supported cmd error.\n
*                         GPMC_NOTSUPPADD_ERROR  -- For non-supported add error.\n
* 
* \return  ErrStatus \n
*
*                         1 : If passed argument type of error occured.\n
*                         0 : If passed argument type of error doesn't occured.\n
*
*/
unsigned int  GPMCErrStatusGet(unsigned int baseAddr, unsigned int err)
{
    unsigned int retVal;

    retVal = 0;

    switch(err)
    {
        case GPMC_TIMEOUT_ERROR:
             retVal = (( HWREG(baseAddr + GPMC_ERR_TYPE) &
                         GPMC_ERR_TYPE_ERRORTIMEOUT) >>
                         GPMC_ERR_TYPE_ERRORTIMEOUT_SHIFT );
        break;
        case GPMC_NOTSUPPMCMD_ERROR:
             retVal = (( HWREG(baseAddr + GPMC_ERR_TYPE) &
                         GPMC_ERR_TYPE_ERRORNOTSUPPMCMD) >>
                         GPMC_ERR_TYPE_ERRORNOTSUPPMCMD_SHIFT );
        break;
        case GPMC_NOTSUPPADD_ERROR:
             retVal = (( HWREG(baseAddr + GPMC_ERR_TYPE) &
                         GPMC_ERR_TYPE_ERRORNOTSUPPADD) >>
                         GPMC_ERR_TYPE_ERRORNOTSUPPADD_SHIFT );
        break;
    }
    return (retVal);
}

/**
* \brief   This function sets/selects the waitpin polarity.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   pin            Wait pin.\n
*                         This can take one of the following values :\n
*                         GPMC_WAIT_PIN0   -- For WAITPIN0.\n
*                         GPMC_WAIT_PIN1   -- For WAITPIN1.\n
* 
* \param  polarity        Wait pin polarity.\n
*                         This can take one of the following values :\n
*                         GPMC_WAIT_PIN_POLARITY_LOW  -- for active low.\n
*                         GPMC_WAIT_PIN_POLARITY_HIGH -- for active high.\n
*
* \return  None.\n
*
*/
void  GPMCWaitPinPolaritySelect(unsigned int baseAddr, unsigned int pin,
                                unsigned int polarity)
{
    if(pin == GPMC_WAIT_PIN0)
    {
        if(polarity == GPMC_WAIT_PIN_POLARITY_HIGH)
        {
            HWREG(baseAddr + GPMC_CONFIG) |= (GPMC_CONFIG_WAIT0PINPOLARITY);
        }
        else if(polarity == GPMC_WAIT_PIN_POLARITY_LOW)
        {
            HWREG(baseAddr + GPMC_CONFIG) &= (~GPMC_CONFIG_WAIT0PINPOLARITY);
        }
    }
    else if(pin == GPMC_WAIT_PIN1)
    {
        if(polarity == GPMC_WAIT_PIN_POLARITY_HIGH)
        {
            HWREG(baseAddr + GPMC_CONFIG) |= (GPMC_CONFIG_WAIT1PINPOLARITY);
        }
        else if(polarity == GPMC_WAIT_PIN_POLARITY_LOW)
        {
            HWREG(baseAddr + GPMC_CONFIG) &= (~GPMC_CONFIG_WAIT1PINPOLARITY);
        }
    }
}

/**
* \brief   This function controls the write protect output pin level.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   pinLevel       Write Protect pin level.\n
*                         This can take one of the following values :\n
*                         GPMC_WP_PIN_LEVEL_LOW  -- for level low.\n
*                         GPMC_WP_PIN_LEVEL_HIGH -- for level high.\n
*
* \return  None.\n
*
*/
void  GPMCWriteProtectPinLevelCtrl(unsigned int baseAddr, unsigned int pinLevel)
{
    if(pinLevel == GPMC_WP_PIN_LEVEL_HIGH)
    {
        HWREG(baseAddr + GPMC_CONFIG) |= (GPMC_CONFIG_WRITEPROTECT);
    }
    else if(pinLevel == GPMC_WP_PIN_LEVEL_LOW)
    {
        HWREG(baseAddr + GPMC_CONFIG) &= (~GPMC_CONFIG_WRITEPROTECT);
    }
}

/**
* \brief   This function configs the limited address device support.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag to indicate whether to enable/disable the 
*                         Limited Address device support.\n
*                         This can take one of the following values :\n
*                         GPMC_LIMITEDADDRESS_SUPPORT_ENABLE  -- To enable 
*                                                                the support.\n
*                         GPMC_LIMITEDADDRESS_SUPPORT_DISABLE -- To disable 
*                                                                the support.\n
*
* \return  None.\n
*
*/
void  GPMCLimitedAddrDevSupportConfig(unsigned int baseAddr, unsigned int flag)
{
    if(flag == GPMC_LIMITEDADDRESS_SUPPORT_ENABLE)
    {
        HWREG(baseAddr + GPMC_CONFIG) |= (GPMC_CONFIG_LIMITEDADDRESS);
    }
    else if(flag == GPMC_LIMITEDADDRESS_SUPPORT_DISABLE)
    {
        HWREG(baseAddr + GPMC_CONFIG) &= (~GPMC_CONFIG_LIMITEDADDRESS);
    }
}

/**
* \brief   This function configs the Force Posted Write feature to NAND 
*          Cmd/Add/Data location.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
* 
* \param   flag           Flag to indicate whether to enable/disable the 
*                         Force Posted Write feature.\n
*                         This can take one of the following values :\n
*                         GPMC_FORCEPOSTEDWRITE_ENABLE  -- To enable the 
*                                                          feature.\n
*                         GPMC_FORCEPOSTEDWRITE_DISABLE -- To disable 
*                                                          the feature.\n
*
* \return  None.\n
*
*/
void  GPMCNANDForcePostedWriteFeatureConfig(unsigned int baseAddr,
                                            unsigned int flag)
{
    if(flag == GPMC_FORCEPOSTEDWRITE_ENABLE)
    {
        HWREG(baseAddr + GPMC_CONFIG) |= (GPMC_CONFIG_NANDFORCEPOSTEDWRITE);
    }
    else if(flag == GPMC_FORCEPOSTEDWRITE_DISABLE)
    {
        HWREG(baseAddr + GPMC_CONFIG) &= (~GPMC_CONFIG_NANDFORCEPOSTEDWRITE);
    }
}

/**
* \brief   This function gets the waitpin status.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   pin            Wait pin.\n
*                         This can take one of the following values :\n
*                         GPMC_WAIT_PIN0   -- For WAITPIN0.\n
*                         GPMC_WAIT_PIN1   -- For WAITPIN1.\n
*
* \return  pinStatus      Pin Status.\n
*                            0 : If the status is active low.\n
*                            1 : If the status is active high.\n
*
*/
unsigned int  GPMCWaitPinStatusGet(unsigned int baseAddr, unsigned int pin)
{
    unsigned int pinStatus;

    pinStatus = 0;

    if(pin == GPMC_WAIT_PIN0)
    {
        pinStatus = ((HWREG(baseAddr + GPMC_STATUS) & GPMC_STATUS_WAIT0STATUS)
                      >> GPMC_STATUS_WAIT0STATUS_SHIFT);
    }
    else if(pin == GPMC_WAIT_PIN1)
    {
        pinStatus = ((HWREG(baseAddr + GPMC_STATUS) & GPMC_STATUS_WAIT1STATUS)
                      >> GPMC_STATUS_WAIT1STATUS_SHIFT);
    }

    return (pinStatus);
}

/**
* \brief   This function gets the empty write buffer status.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  Status         Empty buffer status.\n
*                            0 : If the Write Buffer is not empty.\n
*                            1 : If the Write Buffer is empty.\n
*
*/
unsigned int  GPMCEmptyWriteBuffStatusGet(unsigned int baseAddr)
{
    unsigned int status;

    status = (HWREG(baseAddr + GPMC_STATUS) &
              GPMC_STATUS_EMPTYWRITEBUFFERSTATUS);

    return (status);
}

/**
* \brief   This function selects the FCLK DIVIDER for the chip select passed.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   divideVal      FCLK Divice value.\n
*                         This can take one of the following values :\n
*                         GPMC_FCLK_DIV_BY_1 -- For GPMC_CLK = (GPMC_FCLK / 1)\n
*                         GPMC_FCLK_DIV_BY_2 -- For GPMC_CLK = (GPMC_FCLK / 2)\n
*                         GPMC_FCLK_DIV_BY_3 -- For GPMC_CLK = (GPMC_FCLK / 3)\n
*                         GPMC_FCLK_DIV_BY_4 -- For GPMC_CLK = (GPMC_FCLK / 4)\n
* \return  None.\n
*
*/
void  GPMCFclkDividerSelect(unsigned int baseAddr, unsigned int csNum,
                            unsigned int divideVal)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_GPMCFCLKDIVIDER;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((divideVal <<
                                           GPMC_CONFIG1_0_GPMCFCLKDIVIDER_SHIFT)
                                           & GPMC_CONFIG1_0_GPMCFCLKDIVIDER );
}

/**
* \brief   This function selects the signals timing latencies scalar factor 
*          for the chip select.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   scaleftr       Scalar factor.\n
*                         This can take one of the following values :\n
*                         GPMC_TIMEPARAGRANULARITY_X1 -- For x1 latencies\n
*                         GPMC_TIMEPARAGRANULARITY_X2 -- For x2 latencies\n
* \return  None.\n
*
*/
void  GPMCTimeParaGranularitySelect(unsigned int baseAddr, unsigned int csNum,
                                    unsigned int scaleftr)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_TIMEPARAGRANULARITY;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((scaleftr <<
                                       GPMC_CONFIG1_0_TIMEPARAGRANULARITY_SHIFT)
                                       & GPMC_CONFIG1_0_TIMEPARAGRANULARITY );
}

/**
* \brief   This function selects the Address and data multiplexed protocol
*          for the device connected to csNum.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   protocol       Protocol type.\n
*                         This can take one of the following values :\n
*                         GPMC_MUXADDDATA_AADMUX    -- For Address, address and
*                                                      data(AAD) muxed protocol.\n
*                         GPMC_MUXADDDATA_NOMUX     -- For Non-muxed prorocol.\n
*                         GPMC_MUXADDDATA_ADMUX     -- For Address & Data muxed
*                                                      protocol.\n
* \return  None.\n
*
*/
void  GPMCAddrDataMuxProtocolSelect(unsigned int baseAddr, unsigned int csNum,
                                    unsigned int protocol)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_MUXADDDATA;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((protocol <<
                                       GPMC_CONFIG1_0_MUXADDDATA_SHIFT)
                                       & GPMC_CONFIG1_0_MUXADDDATA );
}

/**
* \brief   This function selects the device type for the device connected to 
*          csNum.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   devType        Device Type.\n
*                         This can take one of the following values :\n
*                         GPMC_DEVICETYPE_NANDLIKE  -- For NAND flash like
*                                                      devices.\n
*                         GPMC_DEVICETYPE_NORLIKE   -- For NOR flash like
*                                                      devices.\n
* \return  None.\n
*
*/
void  GPMCDevTypeSelect(unsigned int baseAddr, unsigned int csNum,
                        unsigned int devType)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_DEVICETYPE;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((devType <<
                                       GPMC_CONFIG1_0_DEVICETYPE_SHIFT)
                                       & GPMC_CONFIG1_0_DEVICETYPE );
}

/**
* \brief   This function selects the device size for the device connected to 
*          csNum.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   devSize        Device Size.\n
*                         This can take one of the following values :\n
*                         GPMC_DEVICESIZE_8BITS   -- For 8-bit device.\n
*                         GPMC_DEVICESIZE_16BITS  -- For 16-bit device.\n
* \return  None.\n
*
*/
void  GPMCDevSizeSelect(unsigned int baseAddr, unsigned int csNum,
                        unsigned int devSize)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_DEVICESIZE;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((devSize <<
                                               GPMC_CONFIG1_0_DEVICESIZE_SHIFT)
                                               & GPMC_CONFIG1_0_DEVICESIZE );
}

/**
* \brief   This function selects the WAIT PIN for the device connected to 
*          csNum.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   waitPin        Wait Pin.\n
*                         This can take one of the following values :\n
*                         GPMC_WAIT_PIN0  -- To Select WAITPIN0.\n
*                         GPMC_WAIT_PIN1  -- To Select WAITPIN1.\n
* \return  None.\n
*
*/
void  GPMCWaitPinSelect(unsigned int baseAddr, unsigned int csNum,
                        unsigned int waitPin)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_WAITPINSELECT;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((waitPin <<
                                             GPMC_CONFIG1_0_WAITPINSELECT_SHIFT)
                                             & GPMC_CONFIG1_0_WAITPINSELECT );
}

/**
* \brief   This function configs/selects the wait monitoring time for the device
*          connected to csNum.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   flag           Flag to indicate the wait monitoring time.\n
*                         This can take one of the following values :\n
*                         GPMC_WAITMONITORINGTIME_WITH_VALIDDATA  -- For wait
*                                               pin monitoring with valid data.\n
*                         GPMC_WAITMONITORINGTIME_ONECLKB4_VALIDDATA  -- For 
*                                               wait pin monitoring one GPMC_CLK
*                                               before valid data. \n
*                         GPMC_WAITMONITORINGTIME_TWOCLKB4_VALIDDATA  -- For 
*                                               wait pin monitoring two GPMC_CLK
*                                               before valid data. \n
* \return  None.\n
*
*/
void  GPMCWaitMonitoringTimeSelect(unsigned int baseAddr, unsigned int csNum,
                                   unsigned int flag)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_WAITMONITORINGTIME;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((flag <<
                                       GPMC_CONFIG1_0_WAITMONITORINGTIME_SHIFT)
                                       & GPMC_CONFIG1_0_WAITMONITORINGTIME );
}

/**
* \brief   This function configs the wait pin monitoring for read and write
*          access.
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   mode           Mode for which wait monitoring has to config.\n
*                         This can take one of the following values :\n
*                         GPMC_MODE_READ   -- To config the  wait
*                                              monitoring for READ.\n
*                         GPMC_MODE_WRITE  -- To config the  wait
*                                              monitoring for WRITE.\n
*
* \param   flag           Flag to indicate whether to enable/disable the wait
*                         monitoring.\n
*                         This can take one of the following values :\n
*                         GPMC_WAITMONITORING_ENABLE  -- To enable the wait
*                         monitoring.\n
*                         GPMC_WAITMONITORING_DISABLE -- To disable the wait
*                         monitoring.\n
* \return  None.\n
*
*/
void  GPMCWaitPinMonitoringConfig(unsigned int baseAddr, unsigned int csNum,
                                  unsigned int mode, unsigned int flag)
{
    if(mode == GPMC_MODE_WRITE)
    {
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) &=
                                            ~GPMC_CONFIG1_0_WAITWRITEMONITORING;
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((flag <<
                                       GPMC_CONFIG1_0_WAITWRITEMONITORING_SHIFT)
                                       & GPMC_CONFIG1_0_WAITWRITEMONITORING );
    }
    else if(mode == GPMC_MODE_READ)
    {
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) &=
                                             ~GPMC_CONFIG1_0_WAITREADMONITORING;
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((flag <<
                                       GPMC_CONFIG1_0_WAITREADMONITORING_SHIFT)
                                       & GPMC_CONFIG1_0_WAITREADMONITORING );
   }
}

/**
* \brief   This function configs the output GPMC_CLK activation time.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   flag           Flag to indicate the activation time of GPMC_CLK.\n
*                         This can take one of the following values :\n
*                         GPMC_CLKACTIVATIONTIME_ATSTART     -- For First rising
*                                                           edge of GPMC_CLK at
*                                                           start access time.\n
*                         GPMC_CLKACTIVATIONTIME_ONECLK_AFTR -- For First rising
*                                                           edge of GPMC_CLK one
*                                                           GPMC_FCLK cycle aftr
*                                                           start access time.\n
*                         GPMC_CLKACTIVATIONTIME_TWOCLK_AFTR -- For First rising
*                                                           edge of GPMC_CLK two
*                                                           GPMC_FCLK cycle aftr
*                                                            start access time.\n
* \return  None.\n
*
*/
void  GPMCClkActivationTimeConfig(unsigned int baseAddr, unsigned int csNum,
                                  unsigned int flag)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_CLKACTIVATIONTIME;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((flag <<
                                       GPMC_CONFIG1_0_CLKACTIVATIONTIME_SHIFT)
                                       & GPMC_CONFIG1_0_CLKACTIVATIONTIME );
}

/**
* \brief   This function sets the device page length.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   pageLen        Device Page Length.\n
*                         This can take one of the following values :\n
*                         GPMC_DEV_PAGELENGTH_FOUR    -- For 4 words page 
*                                                        length.\n
*                         GPMC_DEV_PAGELENGTH_EIGHT   -- For 8 words page 
*                                                        length.\n
*                         GPMC_DEV_PAGELENGTH_SIXTEEN -- For 16 words page
*                                                        length. \n
* \return  None.\n
*
*/
void  GPMCDevPageLenSet(unsigned int baseAddr, unsigned int csNum,
                           unsigned int pageLen)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &=
                                       ~GPMC_CONFIG1_0_ATTACHEDDEVICEPAGELENGTH;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((pageLen <<
                                  GPMC_CONFIG1_0_ATTACHEDDEVICEPAGELENGTH_SHIFT)
                                  & GPMC_CONFIG1_0_ATTACHEDDEVICEPAGELENGTH);
}

/**
* \brief   This function selects the write type.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   writeType      writeType for the write mode operation.\n
*                         This can take one of the following values :\n
*                         GPMC_WRITETYPE_ASYNC -- For write asynchronous.\n
*                         GPMC_WRITETYPE_SYNC  -- For write synchronous.\n
*
* \return  None.\n
*
*/
void  GPMCWriteTypeSelect(unsigned int baseAddr, unsigned int csNum,
                          unsigned int writeType)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_WRITETYPE;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((writeType <<
                                  GPMC_CONFIG1_0_WRITETYPE_SHIFT)
                                  & GPMC_CONFIG1_0_WRITETYPE);
}

/**
* \brief   This function selects the read type.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   readType       readType for the read mode operation.\n
*                         This can take one of the following values :\n
*                         GPMC_READTYPE_ASYNC -- For read asynchronous.\n
*                         GPMC_READTYPE_SYNC  -- For read synchronous.\n
*
* \return  None.\n
*
*/
void  GPMCReadTypeSelect(unsigned int baseAddr, unsigned int csNum,
                         unsigned int readType)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_READTYPE;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((readType <<
                                               GPMC_CONFIG1_0_READTYPE_SHIFT)
                                               & GPMC_CONFIG1_0_READTYPE);
}

/**
* \brief   This function configs the access type for read and write.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   mode           Mode for which access type has to config.\n
*                         This can take one of the following values :\n
*                         GPMC_MODE_READ   -- To config access
*                                             type for READ.\n
*                         GPMC_MODE_WRITE  -- To config access
*                                             type for WRITE.\n
* \param   AccessType     Access Type.\n
*                         This can take one of the following values :\n
*                         GPMC_ACCESSTYPE_SINGLE   -- For single access.\n
*                         GPMC_ACCESSTYPE_MULTIPLE -- For multiple access.\n
*
* \return  None.\n
*
*/
void  GPMCAccessTypeSelect(unsigned int baseAddr, unsigned int csNum,
                           unsigned int mode, unsigned int accessType)
{
    if(mode == GPMC_MODE_WRITE)
    {
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_WRITEMULTIPLE;
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((accessType <<
                                            GPMC_CONFIG1_0_WRITEMULTIPLE_SHIFT)
                                            & GPMC_CONFIG1_0_WRITEMULTIPLE );
    }
    else if(mode == GPMC_MODE_READ)
    {

        HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_READMULTIPLE;
        HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((accessType <<
                                            GPMC_CONFIG1_0_READMULTIPLE_SHIFT)
                                            & GPMC_CONFIG1_0_READMULTIPLE);
   }
}

/**
* \brief   This function configs the wrapping burst capability.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   flag           Flag to indicate whether to enable/disable 
*                         Synchronous wrapping burst capability.\n
*                         This can take one of the following values :\n
*                         GPMC_WRAPBURST_ENABLE   -- To enable the wrap burst
*                                                     capability.\n
*                         GPMC_WRAPBURST_DISABLE  -- To disable the wrap burst
*                                                     capability.\n
*
* \return  None.\n
*
*/
void  GPMCSyncWrapBurstConfig(unsigned int baseAddr, unsigned int csNum,
                              unsigned int flag)
{
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) &= ~GPMC_CONFIG1_0_WRAPBURST;
    HWREG(baseAddr + GPMC_CONFIG1(csNum)) |= ((flag <<
                                        GPMC_CONFIG1_0_WRAPBURST_SHIFT)
                                        & GPMC_CONFIG1_0_WRAPBURST);
}

/**
* \brief   This function configs the timing parameters for Chip Select signal.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Configuration value for chip select timing parameters
*                         Use the GPMC_CS_TIMING_CONFIG macro to get the value 
*                         of conf. \n
*
* \return  None.\n
*
*/
void  GPMCCSTimingConfig(unsigned int baseAddr, unsigned int csNum,
                         unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG2(csNum)) = conf;
}

/**
* \brief   This function configs the timing parameters for ADV# signal.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Configuration value for ADV# signal timing parameters 
*                         Use the GPMC_ADV_TIMING_CONFIG macro to get the value 
*                         of conf. \n
*
* \return  None.\n
*
*/
void  GPMCADVTimingConfig(unsigned int baseAddr, unsigned int csNum,
                          unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG3(csNum)) = conf;
}

/**
* \brief   This function configs the timing parameters for WE# and OE# signal.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Configuration value for WE# and OE# signal timing
*                         Parameters. Use the GPMC_WE_OE_TIMING_CONFIG macro to
*                         get the value of conf. \n
*
* \return  None.\n
*
*/
void  GPMCWEAndOETimingConfig(unsigned int baseAddr, unsigned int csNum,
                              unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG4(csNum)) = conf;
}

/**
* \brief   This function configs the RdAccessTime and CycleTime timing 
*          parameters.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Configuration value for RdAccessTime and CycleTime
*                         timing parameters. Use the 
*                         GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG macro to
*                         get the value of conf. \n
*
* \return  None.\n
*
*/
void  GPMCRdAccessAndCycleTimeTimingConfig(unsigned int baseAddr,
                                           unsigned int csNum,
                                           unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG5(csNum)) = conf;
}

/**
* \brief   This function configs the WrAccessTime, Cycle2Cycle and BusTurnAround
*          timing parameters.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   wrAccessTime   Write Access Time(Delay from StartAccessTime to the 
*                         GPMC_FCLK rising edge corresponding the GPMC_CLK 
*                         rising edge used by the attached memory for the 
*                         first data capture) in GPMC_FCLK cycles.\n
*
*        wrDataOnADmuxBus Specifies on which GPMC_FCLK rising edge the first 
*                         data of the synchronous burst write is driven in the 
*                         add/data multiplexed bus.\n
*
* \return  None.\n
*
*/
void  GPMCWrAccessAndWrDataOnADMUXBusTimingConfig(unsigned int baseAddr,
                                                  unsigned int csNum,
                                                  unsigned int wrAccessTime,
                                                  unsigned int wrDataOnADmuxBus)
{
    unsigned int conf;

    conf = ( ((wrAccessTime << GPMC_CONFIG6_0_WRACCESSTIME_SHIFT) &
             GPMC_CONFIG6_0_WRACCESSTIME) |
             ((wrDataOnADmuxBus << GPMC_CONFIG6_0_WRDATAONADMUXBUS_SHIFT) &
             GPMC_CONFIG6_0_WRDATAONADMUXBUS) );

    HWREG(baseAddr + GPMC_CONFIG6(csNum)) |= conf;
}

/**
* \brief   This function configs the Cycle2Cycle and BusTurnAround  timing
*          parameters.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Configuration value for Cycle2Cycle and BusTurnAround
*                         timing parameters. Use the 
*                         GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG macro to
*                         get the value of conf. \n
*
* \return  None.\n
*
*/
void  GPMCycle2CycleAndTurnArndTimeTimingConfig(unsigned int baseAddr,
                                                unsigned int csNum,
                                                unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG6(csNum)) |= conf;
}

/**
* \brief   This function enables/disables the chip select. This function
*          is called during the chip select configuration.\n 
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   conf           Flag to indicate whether to enable or disable 
*                         the Chip select.\n
*                         This can take one of the following values :\n
*                         GPMC_CS_ENABLE  -- To enable the chip select.\n
*                         GPMC_CS_DISABLE -- To disable the chip select.\n
*
* \return  None.\n
*
*/
void  GPMCCSConfig(unsigned int baseAddr, unsigned int csNum,
                   unsigned int conf)
{
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) &= ~GPMC_CONFIG7_0_CSVALID;
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) |= ((conf <<
                                               GPMC_CONFIG7_0_CSVALID_SHIFT) &
                                               GPMC_CONFIG7_0_CSVALID);
}

/**
* \brief   This function sets the base address for the chip select spcified.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param   addr           Chip Select Base address.Value can range from 
*                         0 to 0x3F\n
*
* \return  None.\n
*
*/
void  GPMCBaseAddrSet(unsigned int baseAddr, unsigned int csNum,
                      unsigned int addr)
{
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) &= ~GPMC_CONFIG7_0_BASEADDRESS;
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) |= ((addr <<
                                               GPMC_CONFIG7_0_BASEADDRESS_SHIFT)
                                               & GPMC_CONFIG7_0_BASEADDRESS);
}

/**
* \brief   This function sets the chip select mask address or size.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param  addrMask        Address Mask to set. \n
*                         This can take one of the following values :\n
*                         GPMC_CS_SIZE_256MB  -- For Chip-select size of 256 MB.\n
*                         GPMC_CS_SIZE_128MB  -- For Chip-select size of 128 MB.\n
*                         GPMC_CS_SIZE_64MB   -- For Chip-select size of 64 MB.\n
*                         GPMC_CS_SIZE_32MB   -- For Chip-select size of 32 MB.\n
*                         GPMC_CS_SIZE_16MB   -- For Chip-select size of 16 MB.\n
*
* \return  None.\n
*
*/
void  GPMCMaskAddrSet(unsigned int baseAddr, unsigned int csNum,
                      unsigned int addrMask)
{
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) &= (~GPMC_CONFIG7_0_MASKADDRESS);
    HWREG(baseAddr + GPMC_CONFIG7(csNum)) |= ((addrMask <<
                                               GPMC_CONFIG7_0_MASKADDRESS_SHIFT)
                                               & GPMC_CONFIG7_0_MASKADDRESS);
}

/**
* \brief   This function writes the NAND command to COMMAND register.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number for which NAND is interfaced.
*                         This can take one of the following values :
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param  cmd             COMMAND to write. 
*
* \return  None.\n
*
*/
void  GPMCSNANDCmdWrite(unsigned int baseAddr, unsigned int csNum,
                        unsigned int cmd)
{
    HWREG(baseAddr + GPMC_NAND_COMMAND(csNum)) = cmd;
}

/**
* \brief   This function writes the NAND address to ADDRESS register.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number for which NAND is interfaced.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param  addr            ADDRESS to write. \n
*
* \return  None.\n
*
*/
void  GPMCNANDAddrWrite(unsigned int baseAddr, unsigned int csNum,
                        unsigned int addr)
{
    HWREG(baseAddr + GPMC_NAND_ADDRESS(csNum)) = addr;
}

/**
* \brief   This function writes the NAND data to DATA register.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number for which NAND is interfaced.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \param  data            data to write. \n
*
* \return  None.\n
*
*/
void  GPMCNANDDataWrite(unsigned int baseAddr, unsigned int csNum,
                         unsigned int data)
{
    HWREG(baseAddr + GPMC_NAND_DATA(csNum)) = data;
}

/**
* \brief   This function the data from NAND DATA register.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select Number for which NAND is interfaced.\n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \return  Read NAND data.\n
*
*/
unsigned int  GPMCNANDDataRead(unsigned int baseAddr, unsigned int csNum)
{
    unsigned int data;

    data = HWREG(baseAddr + GPMC_NAND_DATA(csNum));

    return (data);
}

/**
* \brief   This function selects the access mode of the prefetch engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   accessMode     Access mode of prefetch engine.\n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_ACCESSMODE_READ  -- For READ Access 
*                                                           mode.\n
*                         GPMC_PREFETCH_ACCESSMODE_WRITE -- For WRITE Access
*                                                            mode.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchAccessModeSelect(unsigned int baseAddr,
                                  unsigned int accessMode)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                             ~GPMC_PREFETCH_CONFIG1_ACCESSMODE;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((accessMode <<
                                        GPMC_PREFETCH_CONFIG1_ACCESSMODE_SHIFT)
                                        & GPMC_PREFETCH_CONFIG1_ACCESSMODE);
}

/**
* \brief   This function select the synchronization type to use on FIFO 
*          threshold crossing.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   syncType       Synchronization type.\n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_SYNCTYPE_DMA  -- For DMA sync mode \n
*                         GPMC_PREFETCH_SYNCTYPE_INT  -- For INTERRUPT sync
*                                                        mode.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchSyncTypeSelect(unsigned int baseAddr, unsigned int syncType)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                              ~GPMC_PREFETCH_CONFIG1_DMAMODE;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((syncType <<
                                        GPMC_PREFETCH_CONFIG1_DMAMODE_SHIFT)
                                        & GPMC_PREFETCH_CONFIG1_DMAMODE);
}

/**
* \brief   This function congigs when the PREFETCH engine has to start the
*          access to CS.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   flag           Flag to specify when PREFETCH engine has to start 
*                         the access to CS.\n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_ACCESSCS_AT_START       --  To start the
*                                                                   access as 
*                                                                   soon as 
*                                                                   STARTENGINE 
*                                                                   is set.\n
*                         GPMC_PREFETCH_ACCESSCS_AT_STARTANDWAIT -- To start the
*                                                                   access as 
*                                                                   soon as 
*                                                                   STARTENGINE
*                                                                   is set and 
*                                                                   non wait 
*                                                                   edge  
*                                                                   detection 
*                                                                   on the  
*                                                                   selected 
*                                                                   wait pin.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchSyncModeConfig(unsigned int baseAddr,unsigned int flag)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                             ~GPMC_PREFETCH_CONFIG1_SYNCHROMODE;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((flag <<
                                        GPMC_PREFETCH_CONFIG1_SYNCHROMODE_SHIFT)
                                        & GPMC_PREFETCH_CONFIG1_SYNCHROMODE);
}

/**
* \brief   This function selects the wait pin edge detector to start the 
*          PREFETCH engine in synchronized mode.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   waitPin        Wait pin to use for edge detector. \n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_WAITPINSELECTOR_W0 -- To Selects 
*                                                             Wait0EdgeDetection\n
*                         GPMC_PREFETCH_WAITPINSELECTOR_W1 -- To Selects 
*                                                             Wait1EdgeDetection\n
*
* \return  None.\n
*
*/
void GPMCPrefetchWaitPinSelect(unsigned int baseAddr, unsigned int waitPin)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                         ~GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((waitPin <<
                                    GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_SHIFT)
                                    & GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR);
}

/**
* \brief   This function enables the PREFETCH POSTWRITE engine. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchEngineEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |=
                                 (GPMC_PREFETCH_CONFIG1_ENABLEENGINE_ENABLED <<
                                  GPMC_PREFETCH_CONFIG1_ENABLEENGINE_SHIFT);
}

/**
* \brief   This function disable the PREFETCH POSTWRITE engine. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchEngineDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1)) &=
                                        (~GPMC_PREFETCH_CONFIG1_ENABLEENGINE);
}

/**
* \brief   This function sets the FIFOTHRESHOLD (maximum number of bytes read 
*          from the FIFO or written to the FIFO by the host on a DMA or 
*          interrupt request) value for the PREFETCH and POSTWRITE engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   fifoThrsld     FIFO threshold value. \n
*
* \return  None.\n
*
*/
void GPMCPrefetchFifoThrldValSet(unsigned int baseAddr, unsigned int fifoThrsld)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                         ~GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((fifoThrsld <<
                                    GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD_SHIFT)
                                    & GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD);
}

/**
* \brief   This function selects the chip select(CS) where Prefetch Postwrite 
*          engine is active.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select. \n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchCSSelect(unsigned int baseAddr, unsigned int csNum)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                        ~GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((csNum <<
                                   GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR_SHIFT)
                                    & GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR);
}

/**
* \brief   This function configs the access cycle optimization for PREFETCH 
*          engine. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   configVal      access cycle optimization config value.\n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_OPTIMIZED_ACCESS_ENABLE  -- To enable
*                                                                   the access 
*                                                                   optimization\n
*                         GPMC_PREFETCH_OPTIMIZED_ACCESS_DISABLE -- To disable
*                                                                   the access 
*                                                                   optimization\n
*                                                                    
* \return  None.\n
*
*/
void GPMCPrefetchAccessCycleOptConfig(unsigned int baseAddr,
                                      unsigned int configVal)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                   ~GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((configVal <<
                              GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_SHIFT)
                              & GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS);
}

/**
* \brief   This function sets the number of GPMC_FCLK cycles to be substracted 
*          from RdCycleTime,WrCycleTime, AccessTime, CSRdOffTime, CSWrOffTime, 
*          ADVRdOffTime,ADVWrOffTime, OEOffTime, WEOffTime for PREFETCH 
*          engine cycle optimization. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   cleOptVal      Cycle optimization value. This can take value from
*                         0 to 7.\n
*                                                                    
* \return  None.\n
*
*/
void GPMCPrefetchCycleOptValSet(unsigned int baseAddr, unsigned int cleOptVal)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                      ~GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((cleOptVal <<
                              GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION_SHIFT)
                              & GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION);
}

/**
* \brief   This function configs the PREFETCH and POSTWRITE ROUND
*          ROBIN arbitration. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   configVal      Round Robin arbitration config value.\n
*                         This can take one of the following values :\n
*                         GPMC_PREFETCH_RR_ARBITRATION_ENABLE   -- To enable
*                                                                  the Round
*                                                                  robin 
*                                                                  arbitration\n
*                         GPMC_PREFETCH_RR_ARBITRATION_DISABLE  -- To disable
*                                                                  the Round
*                                                                  robin 
*                                                                  arbitration\n
*
* \return  None.\n
*
*/
void GPMCPrefetchRRArbitrationConfig(unsigned int baseAddr,
                                     unsigned int configVal)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                       ~GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((configVal <<
                                  GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN_SHIFT)
                                  & GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN);
}

/**
* \brief   This function sets the number of access to be granted to PREFETCH 
*          engine when ROUND ROBIN arbitration. i.e When an arbitration occurs
*          between a direct memory access and a PFPW engine access, the direct
*          memory access is always serviced. If the PFPWEnRoundRobin is enabled
*          value set by this function plus one number of access is granted to  
*          the PREFETCH and WRITE POST engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   accessVal      Access value to set. \n
*
* \return  None.\n
*
*/
void GPMCPrefetchWeightedPrioSet(unsigned int baseAddr, unsigned int accessVal)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  &=
                                        ~GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(1))  |= ((accessVal <<
                                   GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO_SHIFT)
                                   & GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO);
}

/**
* \brief   This function sets the transfer count (number of bytes to be read or
*          written by the engine to the selected CS) for the PREFETCH engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   trnsCntVal     Tranfer count value. Value can range from 0 to 2000h
*                         i.e 8 KB.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchTrnsCntValSet(unsigned int baseAddr, unsigned int trnsCntVal)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(2))  &=
                                           ~GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT;
    HWREG(baseAddr + GPMC_PREFETCH_CONFIG(2))  |= ((trnsCntVal <<
                                      GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT_SHIFT)
                                      & GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT);
}

/**
* \brief   This function resets the FIFO pointer to 0 in prefetch mode 
*           and 40h in postwrite mode starts the PREFETCH and POST WRITE engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchEngineStart(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONTROL)  =
                                      GPMC_PREFETCH_CONTROL_STARTENGINE_START ;
}

/**
* \brief   This function stops the PREFETCH and POST WRITE engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCPrefetchEngineStop(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_PREFETCH_CONTROL)  =
                                        GPMC_PREFETCH_CONTROL_STARTENGINE_STOP;
}

/**
* \brief   This function gets the status of PREFETCH and POST WRITE engine.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  status         Prefetch engine status\n
*                            0 : If engine is stopped.\n
*                            1 : If engine is running.\n
*
*/
unsigned int  GPMCPrefetchEngineStatusGet(unsigned int baseAddr)
{
    unsigned int status;

    status = ( HWREG(baseAddr + GPMC_PREFETCH_CONTROL) &
                     GPMC_PREFETCH_CONTROL_STARTENGINE );

    return (status);
}

/**
* \brief   This function gets the number of remaining bytes to be read or to be
*          written by the engine according to the TransferCount value.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  count value.\n
*
*/
unsigned int  GPMCPrefetchCountValGet(unsigned int baseAddr)
{
    unsigned int cntVal;

    cntVal = ( HWREG(baseAddr + GPMC_PREFETCH_STATUS) &
                     GPMC_PREFETCH_STATUS_COUNTVALUE );

    return (cntVal);
}

/**
* \brief   This function gets the PREFETCH engine FIFO threshold status. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  stauts         Threshold status.\n
*                            1 : FIFO Pointer is greater than FIFO Threshold.\n
*                            0 : FIFO Pointer is smaller or equal to FIFO 
*                                Threshold.\n
*
*/
unsigned int  GPMCPrefetchFifoThrldStatusGet(unsigned int baseAddr)
{
    unsigned int status;

    status = ((HWREG(baseAddr + GPMC_PREFETCH_STATUS) &
                     GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS)
                     >> GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS_SHIFT);

    return (status);

}

/**
* \brief   This function gets the FIFO pointer value of PREFETCH engine.
*          FIFO pointer value indicates number of bytes available to be read 
*          or number of free empty place to write.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  FIFO pointer value.\n
*
*/
unsigned int GPMCPrefetchFifoPtrValGet(unsigned int baseAddr)
{
    unsigned int fifoPtrVal;

    fifoPtrVal = ((HWREG(baseAddr + GPMC_PREFETCH_STATUS) &
                         GPMC_PREFETCH_STATUS_FIFOPOINTER)
                         >> GPMC_PREFETCH_STATUS_FIFOPOINTER_SHIFT);

    return (fifoPtrVal);
}

/**
* \brief   This function selects the ECC algorithm to use for ECC error
*          detection and correction.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccAlgo        ECC algorithm to use.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_ALGORITHM_HAMMINGCODE -- For Hamming code.\n
*                         GPMC_ECC_ALGORITHM_BCH         -- For BCH.\n
* \return  None.\n
*
*/
void GPMCECCAlgoSelect(unsigned int baseAddr, unsigned int algo)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECCALGORITHM;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((algo <<
                                           GPMC_ECC_CONFIG_ECCALGORITHM_SHIFT)
                                           & GPMC_ECC_CONFIG_ECCALGORITHM);
}

/**
* \brief   This function selects the Error correction capability used for BCH 
*          ECC algorithm.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   errCorrCapVal  Error correction capability value.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_4BITS  -- For Up to 4 
*                                                                bits error 
*                                                                 correction.\n
*                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS  -- For Up to 8
*                                                                 bits error
*                                                                 correction.\n
*                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_16BITS -- For Up to 16
*                                                                 bits error 
*                                                                 correction.\n
*
* \return  None.\n
*
*/
void GPMCECCBCHErrCorrectionCapSelect(unsigned int baseAddr,
                                      unsigned int errCorrCapVal)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECCBCHTSEL;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((errCorrCapVal <<
                                           GPMC_ECC_CONFIG_ECCBCHTSEL_SHIFT)
                                           & GPMC_ECC_CONFIG_ECCBCHTSEL);
}

/**
* \brief   This function sets the wrap mode(Spare area organization definition)
*          for the ECC BCH algorithm.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   wrapModeVal    Wrap mode value. Value can range from 0x00 to 0x0F.\n
*
* \return  None.\n
*
*/
void GPMCECCBCHWrapModeValSet(unsigned int baseAddr, unsigned int wrapModeVal)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECCWRAPMODE;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((wrapModeVal <<
                                           GPMC_ECC_CONFIG_ECCWRAPMODE_SHIFT)
                                           & GPMC_ECC_CONFIG_ECCWRAPMODE);
}

/**
* \brief   This function selects number of columns to use for ECC calculation.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccColVal      ECC column value.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_COLUMNS_8   -- ECC calculated on 8 columns.\n
*                         GPMC_ECC_COLUMNS_16  -- ECC calculated on 16 columns.\n
*
* \return  None.\n
*
*/
void GPMCECCColumnSelect(unsigned int baseAddr, unsigned int eccColVal)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECC16B;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((eccColVal <<
                                           GPMC_ECC_CONFIG_ECC16B_SHIFT)
                                           & GPMC_ECC_CONFIG_ECC16B);
}

/**
* \brief   This function selects the number of sectors to process with the BCH
*          algorithm.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   numOfSects     Number of sectors.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_BCH_NUMOFSECTS_1  -- For 1 sector (512 bytes
*                                                       page).\n 
*                         GPMC_ECC_BCH_NUMOFSECTS_2  -- For 2 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_3  -- For 3 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_4  -- For 4 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_5  -- For 5 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_6  -- For 6 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_7  -- For 7 sectors. \n
*                         GPMC_ECC_BCH_NUMOFSECTS_8  -- For 8 sectors
*                                                       (4KB page).\n
*
* \return  None.\n
*
*/
void GPMCECCBCHNumOfSectorsSelect(unsigned int baseAddr,
                                  unsigned int numOfSects)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECCTOPSECTOR;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((numOfSects <<
                                           GPMC_ECC_CONFIG_ECCTOPSECTOR_SHIFT)
                                           & GPMC_ECC_CONFIG_ECCTOPSECTOR);
}

/**
* \brief   This function selects the Chip-select where ECC is computed.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   csNum          Chip Select. \n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
*
* \return  None.\n
*
*/
void GPMCECCCSSelect(unsigned int baseAddr, unsigned int csNum)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= ~GPMC_ECC_CONFIG_ECCCS;
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= ((csNum <<
                                           GPMC_ECC_CONFIG_ECCCS_SHIFT)
                                           & GPMC_ECC_CONFIG_ECCCS);
}

/**
* \brief   This function Enables the ECC feature.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCECCEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) |= (GPMC_ECC_CONFIG_ECCENABLE);
}

/**
* \brief   This function disables the ECC feature.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCECCDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_ECC_CONFIG) &= (~GPMC_ECC_CONFIG_ECCENABLE);
}

/**
* \brief   This function clears all ECC result registers.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
void GPMCECCResultRegClear(unsigned int baseAddr)
{
    HWREG(baseAddr + GPMC_ECC_CONTROL) |= (GPMC_ECC_CONTROL_ECCCLEAR);
}

/**
* \brief   This function selects the ECC result register where the first
*          ECC computation will be stored.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccResReg      ECC result register.\n
*                         This can take one of the following values :\n
*                         GPMC_ECCPOINTER_RESULT_1 -- ECC pointer for result 1
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_2 -- ECC pointer for result 2 
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_3 -- ECC pointer for result 3
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_4 -- ECC pointer for result 4
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_5 -- ECC pointer for result 5
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_6 -- ECC pointer for result 6
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_7 -- ECC pointer for result 7
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_8 -- ECC pointer for result 8
*                                                     register.\n
*                         GPMC_ECCPOINTER_RESULT_9 -- ECC pointer for result 9
*                                                     register.\n
*
* \return  None.\n
*
*/
void GPMCECCResultRegSelect(unsigned int baseAddr, unsigned int eccResReg)
{

    HWREG(baseAddr + GPMC_ECC_CONTROL) &= ~GPMC_ECC_CONTROL_ECCPOINTER;
    HWREG(baseAddr + GPMC_ECC_CONTROL) |= ((eccResReg <<
                                           GPMC_ECC_CONTROL_ECCPOINTER_SHIFT)
                                           & GPMC_ECC_CONTROL_ECCPOINTER);

}

/**
* \brief   This function sets the ECCSIZE1 value. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccSize        ECC size for which size has to set.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_SIZE_0 -- For ECC size 0.\n
*                         GPMC_ECC_SIZE_1 -- For ECC size 1.\n
*
* \param   eccSizeVal     ECC size value.\n
*
* \return  None.\n
*
*/
void GPMCECCSizeValSet(unsigned int baseAddr,unsigned int eccSize,
                       unsigned int eccSizeVal)
{
    if(eccSize == GPMC_ECC_SIZE_0)
    {
        HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                               ~GPMC_ECC_SIZE_CONFIG_ECCSIZE0;
        HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= ((eccSizeVal <<
                                            GPMC_ECC_SIZE_CONFIG_ECCSIZE0_SHIFT)
                                            & GPMC_ECC_SIZE_CONFIG_ECCSIZE0);

    }
    else if(eccSize == GPMC_ECC_SIZE_1)
    {
        HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                               ~GPMC_ECC_SIZE_CONFIG_ECCSIZE1;
        HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= ((eccSizeVal <<
                                            GPMC_ECC_SIZE_CONFIG_ECCSIZE1_SHIFT)
                                              & GPMC_ECC_SIZE_CONFIG_ECCSIZE1);
    }
}

/**
* \brief   This function selects the ECC size for the ECC result register. \n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccResReg      ECC result register for which ECC size has to select.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_RESULT_1 -- For ECC result 1 register.\n
*                         GPMC_ECC_RESULT_2 -- For ECC result 2 register.\n
*                         GPMC_ECC_RESULT_3 -- For ECC result 3 register.\n
*                         GPMC_ECC_RESULT_4 -- For ECC result 4 register.\n
*                         GPMC_ECC_RESULT_5 -- For ECC result 5 register.\n
*                         GPMC_ECC_RESULT_6 -- For ECC result 6 register.\n
*                         GPMC_ECC_RESULT_7 -- For ECC result 7 register.\n
*                         GPMC_ECC_RESULT_8 -- For ECC result 8 register.\n
*                         GPMC_ECC_RESULT_9 -- For ECC result 9 register.\n
*
* \param   eccSize        ECC size.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_SIZE_0 -- For ECC size 0.\n
*                         GPMC_ECC_SIZE_1 -- For ECC size 1.\n
*
 \return  None.\n
*
*/
void GPMCECCResultSizeSelect(unsigned int baseAddr,unsigned int eccResReg,
                             unsigned int eccSize)
{
    switch(eccResReg)
    {
        case GPMC_ECC_RESULT_1:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                           ~GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_2:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                           ~GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_3:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                          ~GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_4:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                       ~GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_5:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                           ~GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_6:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                          ~GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_7:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                          ~GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_8:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                          ~GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE);
        break;
        case GPMC_ECC_RESULT_9:
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) &=
                                          ~GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE;
             HWREG(baseAddr + GPMC_ECC_SIZE_CONFIG) |= (( eccSize <<
                                      GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE_SHIFT)
                                      & GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE);
        break;
    }
}

/**
* \brief   This function gets the ECC result from the ECC register.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   eccResReg      ECC result register for from which ECC value has to 
*                         retrive.\n
*                         This can take one of the following values :\n
*                         GPMC_ECC_RESULT_1 -- For ECC result 1 register.\n
*                         GPMC_ECC_RESULT_2 -- For ECC result 2 register.\n
*                         GPMC_ECC_RESULT_3 -- For ECC result 3 register.\n
*                         GPMC_ECC_RESULT_4 -- For ECC result 4 register.\n
*                         GPMC_ECC_RESULT_5 -- For ECC result 5 register.\n
*                         GPMC_ECC_RESULT_6 -- For ECC result 6 register.\n
*                         GPMC_ECC_RESULT_7 -- For ECC result 7 register.\n
*                         GPMC_ECC_RESULT_8 -- For ECC result 8 register.\n
*                         GPMC_ECC_RESULT_9 -- For ECC result 9 register.\n
*
* \return  ECC result.\n
*
*/
unsigned int GPMCECCResultGet(unsigned int baseAddr,unsigned int eccResReg)
{
    unsigned int res;

    res = HWREG(baseAddr + GPMC_ECC_RESULT(eccResReg));

    return (res);
}

/**
* \brief   This function gets the BCH result.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   resIndex       BCH ECC result index.\n 
*                         This can take one of the following values :\n
*                         GPMC_BCH_RESULT_0 -- For BCH result 0.\n
*                         GPMC_BCH_RESULT_1 -- For BCH result 1.\n
*                         GPMC_BCH_RESULT_2 -- For BCH result 2.\n
*                         GPMC_BCH_RESULT_3 -- For BCH result 3.\n
*                         GPMC_BCH_RESULT_4 -- For BCH result 4.\n
*                         GPMC_BCH_RESULT_5 -- For BCH result 5.\n
*                         GPMC_BCH_RESULT_6 -- For BCH result 6.\n
*
* \param   csNum          Chip Select. \n
*                         This can take one of the following values :\n
*                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
*                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
*                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
*                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
*                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
*                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
*                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
*                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n

* \return  ECC result.\n
*
*/
unsigned int GPMCECCBCHResultGet(unsigned int baseAddr,unsigned int resIndex,
                                 unsigned int csNum)
{
    unsigned int res;

    res = 0;

    switch(resIndex)
    {
        case GPMC_BCH_RESULT_0:
             res = HWREG(baseAddr + GPMC_BCH_RESULT0(csNum));
        break;
        case GPMC_BCH_RESULT_1:
             res = HWREG(baseAddr + GPMC_BCH_RESULT1(csNum));
        break;
        case GPMC_BCH_RESULT_2:
             res = HWREG(baseAddr + GPMC_BCH_RESULT2(csNum));
        break;
        case GPMC_BCH_RESULT_3:
             res = HWREG(baseAddr + GPMC_BCH_RESULT3(csNum));
        break;
        case GPMC_BCH_RESULT_4:
             res = HWREG(baseAddr + GPMC_BCH_RESULT4(csNum));
        break;
        case GPMC_BCH_RESULT_5:
             res = HWREG(baseAddr + GPMC_BCH_RESULT5(csNum));
        break;
        case GPMC_BCH_RESULT_6:
             res = HWREG(baseAddr + GPMC_BCH_RESULT6(csNum));
        break;
    }

    return (res);
}

/**
* \brief   This function write the data to BCH_SWDATA register. This is used 
*          to directly padd data to the BCH ECC calculator without accessing
*          the actual NAND flash interface.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \param   bchData        BCH data to be included in the BCH calculation.
*                         Only bits 0 to 7 are taken into account, if
*                         the calculator is configured to use 8 bits data
*                         using GPMCECCColumnSelect function.\n
*
* \return  None.\n
*
*/
void GPMCECCBCHSWDataWrite(unsigned int baseAddr,unsigned int bchData)
{
    HWREG(baseAddr + GPMC_BCH_SWDATA) = ( bchData & GPMC_BCH_SWDATA_BCH_DATA);
}

/**
* \brief   This function read the data to BCH_SWDATA register. This is used 
*          to directly padd data to the BCH ECC calculator without accessing
*          the actual NAND flash interface.\n
*
* \param   baseAddr       Memory address of GPMC.\n
*
* \return  None.\n
*
*/
unsigned int GPMCECCBCHSWDataRead(unsigned int baseAddr)
{
    unsigned int bchData;

    bchData = (HWREG(baseAddr + GPMC_BCH_SWDATA) & GPMC_BCH_SWDATA_BCH_DATA);

    return (bchData);
}

/***************************** End Of File ***********************************/
