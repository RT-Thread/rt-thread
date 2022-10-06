/**
 *  \file   elm.c
 *
 *  \brief  ELM APIs.
 *
 *   This file contains the device abstraction layer APIs for ELM.
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

#include "hw_elm.h"
#include "hw_types.h"
#include "elm.h"

/*******************************************************************************
*                       INTERNAL API DEFINITIONS
*******************************************************************************/
/**
* \brief   This function reads the IP revision code of ELM.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \return  ipRev          IP revision code of ELM.\n
*/
unsigned int  ELMRevisionGet(unsigned int baseAddr)
{
    unsigned int ipRev;

    ipRev =  (HWREG(baseAddr + ELM_REVISION) & ELM_REVISION_REVISION);

    return (ipRev);
}

/**
* \brief   This function configs the Internal OCP clock gating strategy.\n
*
* \param   baseaddr       Base address of ELM.\n
* 
* \param   configVal      config value for OCP clk gating.\n
*                         This can take one of the following values :\n
*                         ELM_AUTOGATING_OCP_FREE   -- OCP clock is free-running\n
*                         ELM_AUTOGATING_OCP_GATING -- Automatic internal OCP 
*                                                      clock gating strategy is 
*                                                      applied based on the OCP 
*                                                      interface activity.\n
*
* \return  none.\n
*/
void  ELMCAutoGatingConfig(unsigned int baseAddr, unsigned int configVal)
{
    HWREG(baseAddr + ELM_SYSCONFIG) &= ~ELM_SYSCONFIG_AUTOGATING;
    HWREG(baseAddr + ELM_SYSCONFIG)= ((configVal <<
                                        ELM_SYSCONFIG_AUTOGATING_SHIFT)
                                        & ELM_SYSCONFIG_AUTOGATING);
}

/**
* \brief   This function sets the idle mode for ELM.\n
*
* \param   baseaddr       Base address of ELM.\n
* 
* \param   mode           Idle mode.\n
*                         This can take one of the following values :\n
*                         ELM_IDLEMODE_FORCEIDLE -- for force-idle. \n
*                         ELM_IDLEMODE_NOIDLE    -- for no-idle. \n
*                         ELM_IDLEMODE_SMARTIDLE -- for smart-idle.\n 
*
* \return  none.\n
*/
void  ELMCIdleModeSelect(unsigned int baseAddr, unsigned int mode)
{
    HWREG(baseAddr + ELM_SYSCONFIG) &= ~ELM_SYSCONFIG_SIDLEMODE;
    HWREG(baseAddr + ELM_SYSCONFIG) |= ((mode <<
                                         ELM_SYSCONFIG_SIDLEMODE_SHIFT)
                                         & ELM_SYSCONFIG_SIDLEMODE);
}

/**
* \brief   This function Resets the ELM.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \return  None.\n
*/

void  ELMModuleReset(unsigned int baseAddr)
{
    HWREG(baseAddr + ELM_SYSCONFIG)= (ELM_SYSCONFIG_SOFTRESET_RESET <<
                                      ELM_SYSCONFIG_SOFTRESET_SHIFT);
}

/**
* \brief   This function sets the OCP Clock activity when module is in IDLE 
*          mode.\n
*
* \param   baseaddr       Base address of ELM.\n
* 
* \param   configVal      Config value.\n
*                         This can take one of the following values :\n
*                         ELM_CLOCKACTIVITYOCP_OCP_OFF -- OCP clock is swith off\n
*                         ELM_CLOCKACTIVITYOCP_OCP_ON  -- OCP Clock is 
*                                                         maintained during 
*                                                         wake up period.\n
*
* \return  none.\n
*/
void  ELMOCPClkActivityConfig(unsigned int baseAddr, unsigned int configVal)
{
    HWREG(baseAddr + ELM_SYSCONFIG) &= ~ELM_SYSCONFIG_CLOCKACTIVITYOCP;
    HWREG(baseAddr + ELM_SYSCONFIG) |= ((configVal <<
                                         ELM_SYSCONFIG_CLOCKACTIVITYOCP_SHIFT)
                                         & ELM_SYSCONFIG_CLOCKACTIVITYOCP);
}

/**
* \brief   This function gets the software resets status of ELM.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \return  status         Reset status : \n
*                            0 : Module reset is on-going.\n
*                            1 : Module reset is completed.\n
*/

unsigned int  ELMModuleResetStatusGet(unsigned int baseAddr)
{
    unsigned int resetStat;

    resetStat = (HWREG(baseAddr + ELM_SYSSTATUS) & ELM_SYSSTATUS_RESETDONE);

    return (resetStat);
}

/**
* \brief   This function gets Interrupt status.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   flag           Flag for which interrupt status has to get.\n
*                         This can take one of the following values :\n
*                         ELM_LOC_VALID_0_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_1_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_2_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_3_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_4_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_5_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_6_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_LOC_VALID_7_STATUS         : Error-location 
*                                                          status for syndrome 
*                                                          polynomial 0.\n
*                         ELM_PAGE_VALID_STATUS          : Error-location 
*                                                          status for a full
*                                                          page. \n
*
* \return  intSts         Interrupt Status. Return value meaning depends on the
*                         param flag. \n
*                         if flag is ELM_LOC_VALID_i_STATUS where i = 0 to 7, 
*                         then\n
*                            0 : No syndrome processed or process in progress.\n
*                            1 : Error-location process completed.\n
*
*                         if flag is ELM_PAGE_VALID_STATUS, then\n
*                            0 : Error locations invalid for all polynomials 
*                                enabled.\n
*                            1 : All error locations valid.\n
*
*                
*/
unsigned int  ELMIntStatusGet(unsigned int baseAddr, unsigned int flag)
{

    unsigned int retVal;

    retVal = 0;

    switch(flag)
    {
        case ELM_LOC_VALID_0_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_0) >>
                        ELM_IRQSTATUS_LOC_VALID_0_SHIFT );
        break;
        case ELM_LOC_VALID_1_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_1) >>
                        ELM_IRQSTATUS_LOC_VALID_1_SHIFT );
        break;
        case ELM_LOC_VALID_2_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_2) >>
                        ELM_IRQSTATUS_LOC_VALID_2_SHIFT );
        break;
        case ELM_LOC_VALID_3_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_3) >>
                        ELM_IRQSTATUS_LOC_VALID_3_SHIFT );
        break;
        case ELM_LOC_VALID_4_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_4) >>
                        ELM_IRQSTATUS_LOC_VALID_4_SHIFT );
        break;
        case ELM_LOC_VALID_5_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_5) >>
                        ELM_IRQSTATUS_LOC_VALID_5_SHIFT );
        break;
        case ELM_LOC_VALID_6_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_6) >>
                        ELM_IRQSTATUS_LOC_VALID_6_SHIFT );
        break;
        case ELM_LOC_VALID_7_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_LOC_VALID_7) >>
                        ELM_IRQSTATUS_LOC_VALID_7_SHIFT );
        break;
        case ELM_PAGE_VALID_STATUS:
             retVal = ((HWREG(baseAddr + ELM_IRQSTATUS) &
                        ELM_IRQSTATUS_PAGE_VALID) >>
                        ELM_IRQSTATUS_PAGE_VALID_SHIFT );
        break;
    }

    return (retVal);
}

/**
* \brief   This function clears the interrupt.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   flag           Flag for which interrupt status has to clear.\n
*                         This can take one of the following values :\n
*                         ELM_LOC_VALID_0_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_1_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_2_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_3_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_4_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_5_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_6_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_7_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_PAGE_VALID_STATUS         : Error-location 
*                                                         interrupt for a full
*                                                         page.\n
*
* \return  None. \n
*
*/
void  ELMIntStatusClear(unsigned int baseAddr, unsigned int flag)
{
    switch(flag)
    {
        case ELM_LOC_VALID_0_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_0;
        break;
        case ELM_LOC_VALID_1_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_1;
        break;
        case ELM_LOC_VALID_2_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_2;
        break;
        case ELM_LOC_VALID_3_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_3;
        break;
        case ELM_LOC_VALID_4_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_4;
        break;
        case ELM_LOC_VALID_5_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_5;
        break;
        case ELM_LOC_VALID_6_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_6;
        break;
        case ELM_LOC_VALID_7_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_LOC_VALID_7;
        break;
        case ELM_PAGE_VALID_STATUS:
             HWREG(baseAddr + ELM_IRQSTATUS) |= ELM_IRQSTATUS_PAGE_VALID;
        break;

    }
}

/**
* \brief   This function configs i.e enables or disable the interrupts.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   intflag        intFlag for which interrupt has to config.\n
*                         This can take one of the following values :\n
*                         ELM_LOC_VALID_0_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_1_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_2_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_3_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_4_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_5_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_6_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_LOC_VALID_7_STATUS        : Error-location 
*                                                         interrupt for syndrome
*                                                         polynomial 0.\n
*                         ELM_PAGE_VALID_STATUS         : Error-location 
*                                                         interrupt for a full
*                                                         page. \n
*
* \param   configVal     Config Value.\n
*                        This can take one of the following values :\n
*                        ELM_INT_ENALBLE                : To enble the interrupt\n
*                        ELM_INT_DISALBLE               : To disable the 
*                                                         interrupt.\n
* \return  None. \n
*
*/
void  ELMIntConfig(unsigned int baseAddr, unsigned int intFlag,
                   unsigned int configVal)
{
    switch(intFlag)
    {
        case ELM_LOC_VALID_0_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_0;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_0;
            }
        break;
        case ELM_LOC_VALID_1_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_1;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_1;
            }
        break;
        case ELM_LOC_VALID_2_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_2;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_2;
            }
        break;
        case ELM_LOC_VALID_3_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_3;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_3;
            }
        break;
        case ELM_LOC_VALID_4_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_4;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_4;
            }
        break;
        case ELM_LOC_VALID_5_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_5;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_5;
            }
        break;
        case ELM_LOC_VALID_6_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_6;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_6;
            }
        break;
        case ELM_LOC_VALID_7_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |=
                      ELM_IRQENABLE_LOCATION_MASK_7;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &=
                      ~ELM_IRQENABLE_LOCATION_MASK_7;
            }
        break;
        case ELM_PAGE_VALID_STATUS:
            if(configVal == ELM_INT_ENALBLE)
            {
                HWREG(baseAddr + ELM_IRQENABLE) |= ELM_IRQENABLE_PAGE_MASK;
            }
            else
            {
                HWREG(baseAddr + ELM_IRQENABLE) &= ~ELM_IRQENABLE_PAGE_MASK;
            }
        break;
    }

}

/**
* \brief   This function sets the Error correction level for BCH alogorithm.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   bchECCLevel    BCH error correction level.\n
*                         This can take one of the following values :\n
*                         ELM_ECC_BCH_LEVEL_16BITS    : For Upto 16 bits error
*                                                       correction.\n
*                         ELM_ECC_BCH_LEVEL_8BITS     : For Upto 8 bits error
*                                                       correction.\n
*                         ELM_ECC_BCH_LEVEL_4BITS     : For Upto 4 bits error
*                                                       correction.\n
*
* \return  None. \n
*
*/
void  ELMErrCorrectionLevelSet(unsigned int baseAddr, unsigned int bchECCLevel)
{

    HWREG(baseAddr + ELM_LOCATION_CONFIG) &= ~ELM_LOCATION_CONFIG_ECC_BCH_LEVEL;
    HWREG(baseAddr + ELM_LOCATION_CONFIG) |= ( bchECCLevel <<
                                       ELM_LOCATION_CONFIG_ECC_BCH_LEVEL_SHIFT);

}

/**
* \brief   This function sets the size of the buffers for which 
*          the error-location engine is used.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   eccSize        eccSize in number of nibbles (i.e 4-bits entities).\n
*
* \return  None. \n
*
*/
void  ELMECCSizeSet(unsigned int baseAddr, unsigned int eccSize)
{
    HWREG(baseAddr + ELM_LOCATION_CONFIG) &= ~ELM_LOCATION_CONFIG_ECC_SIZE;
    HWREG(baseAddr + ELM_LOCATION_CONFIG) |= ( eccSize <<
                                            ELM_LOCATION_CONFIG_ECC_SIZE_SHIFT);
}

/**
* \brief   This function sets mode of the ELM module.\n
*
* \param   mode           mode of the ELM.\n
*                         This can take one of the following values :\n
*                         ELM_MODE_PAGE       -- For page mode.\n
*                         ELM_MODE_CONTINUOUS -- For continuous mode.\n
* 
* \param   sectorNum      Sector number or syndrome polynomial number which has 
*                         to select as part of the page in page mode.\n
*                         This can take one of the following values :\n
*                         ELM_PAGEMODE_SECTOR_0 -- For selecting syndrome 
*                                                  polynomial 0 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_1 -- For selecting syndrome 
*                                                  polynomial 1 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_2 -- For selecting syndrome 
*                                                  polynomial 2 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_3 -- For selecting syndrome 
*                                                  polynomial 3 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_4 -- For selecting syndrome 
*                                                  polynomial 4 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_5 -- For selecting syndrome 
*                                                  polynomial 5 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_6 -- For selecting syndrome 
*                                                  polynomial 6 as part of the 
*                                                  page in page mode.\n
*                         ELM_PAGEMODE_SECTOR_7 -- For selecting syndrome 
*                                                  polynomial 7 as part of the 
*                                                  page in page mode.\n
                                       
* \return  None. \n
*
*/
void  ELMModeSet(unsigned int baseAddr, unsigned int mode,
                 unsigned int sectorNum)
{
    if(mode == ELM_MODE_CONTINUOUS)
    {
        HWREG(baseAddr + ELM_PAGE_CTRL) &= ~( 1 << sectorNum );
    }
    else
    {
        HWREG(baseAddr + ELM_PAGE_CTRL) = ( mode << sectorNum );
    }
}


/**
* \brief   This function sets the fragments of syndrome polynomial for 
*          error-location processing.\n
*
* \param   baseAddr       Base address of ELM.\n
* 
* \param   synFrgmtId     Syndrome fragment ID.\n
*                         This can take one of the following values :\n
*                         ELM_SYNDROME_FRGMT_0 - For syndrome fragment 0.\n
*                         ELM_SYNDROME_FRGMT_1 - For syndrome fragment 1.\n
*                         ELM_SYNDROME_FRGMT_2 - For syndrome fragment 2.\n
*                         ELM_SYNDROME_FRGMT_3 - For syndrome fragment 3.\n
*                         ELM_SYNDROME_FRGMT_4 - For syndrome fragment 4.\n
*                         ELM_SYNDROME_FRGMT_5 - For syndrome fragment 5.\n
*                         ELM_SYNDROME_FRGMT_6 - For syndrome fragment 6.\n
* \param   synFrgmtVal    Syndrome fragment value.\n
*
* \return  None. \n
*
*/
void  ELMSyndromeFrgmtSet(unsigned int baseAddr, unsigned int synFrgmtId,
                          unsigned int synFrgmtVal)
{
    if(synFrgmtId != ELM_SYNDROME_FRGMT_6)
    {
        HWREG(baseAddr + ELM_SYNDROME_FRAGMENT(synFrgmtId)) = ( synFrgmtVal );
    }
    else
    {
        HWREG(baseAddr + ELM_SYNDROME_FRAGMENT(synFrgmtId)) =
             ( synFrgmtVal & ELM_SYNDROME_FRAGMENT_6_SYNDROME_6 );
    }
}

/**
* \brief   This function starts the error-location processing for the polynomial
*          set in the syndrome fragment registers.\n
*
* \param   baseAddr       Base address of ELM.\n
*
* \return  None. \n
*
*/
void  ELMErrLocProcessingStart(unsigned int baseAddr)
{
    HWREG(baseAddr + ELM_SYNDROME_FRAGMENT(ELM_SYNDROME_FRGMT_6)) |=
         ( ELM_SYNDROME_FRAGMENT_6_SYNDROME_VALID );
}

/**
* \brief   This function gets the error-location processing status.\n
*
* \param   baseAddr       Base address of ELM.\n
*
* \return  status. \n
*          0 : ECC error-location process failed.\n
*          1 : ECC error-location process passed.\n
*
*/
unsigned int ELMErrLocProcessingStatusGet(unsigned int baseAddr)
{
    unsigned int status;

    status = ((HWREG(baseAddr + ELM_LOCATION_STATUS) &
                     ELM_LOCATION_STATUS_ECC_CORRECTABLE) >>
                     ELM_LOCATION_STATUS_ECC_CORRECTABLE_SHIFT);

    return (status);
}

/**
* \brief   This function gets the number of errors detected and located 
*          during error-location processing.\n
*
* \param   baseAddr       Base address of ELM.\n
*
* \return  Number of errors detected and located.\n 
*
*/
unsigned int ELMNumOfErrsGet(unsigned int baseAddr)
{
    unsigned int numOfErrs;

    numOfErrs = (HWREG(baseAddr + ELM_LOCATION_STATUS) &
                      ELM_LOCATION_STATUS_ECC_NB_ERRORS);

    return (numOfErrs);
}

/**
* \brief   This function gets the Error-location bit address for the error 
*          number passed.\n 
*
* \param   baseAddr       Base address of ELM.\n
*
* \param   errNum         Error number.\n
*                         This can take one of the following values :\n
*                         ELM_ERROR_NUM_0 - For 0th error.\n
*                         ELM_ERROR_NUM_1 - For 1th error.\n
*                         ELM_ERROR_NUM_2 - For 2th error.\n
*                         ELM_ERROR_NUM_3 - For 3th error.\n
*                         ELM_ERROR_NUM_4 - For 4th error.\n
*                         ELM_ERROR_NUM_5 - For 5th error.\n
*                         ELM_ERROR_NUM_6 - For 6th error.\n
*                         ELM_ERROR_NUM_7 - For 7th error.\n
*                         ELM_ERROR_NUM_8 - For 8th error.\n
*                         ELM_ERROR_NUM_9 - For 9th error.\n
*                         ELM_ERROR_NUM_10 - For 10th error.\n
*                         ELM_ERROR_NUM_11 - For 11th error.\n
*                         ELM_ERROR_NUM_12 - For 12th error.\n
*                         ELM_ERROR_NUM_13 - For 13th error.\n
*                         ELM_ERROR_NUM_14 - For 14th error.\n
*                         ELM_ERROR_NUM_15 - For 15th error.\n
*
* \return  Bit address for the error number.\n 
*
*/
unsigned int ELMErrLocBitAddrGet(unsigned int baseAddr, unsigned int errNum)
{
    unsigned int bitAddr;

    bitAddr = (HWREG(baseAddr + ELM_ERROR_LOCATION(errNum)) &
                     ELM_ERROR_LOCATION_0_ECC_ERROR_LOCATION);

    return (bitAddr);
}
/***************************** End Of File ***********************************/
