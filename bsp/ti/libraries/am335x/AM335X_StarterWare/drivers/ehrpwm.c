/**
 *  \file   ehrpwm.c
 *
 *  \brief  This file contains the device abstraction layer APIs for EHRPWM.
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

/* HW Macros */
#include "hw_types.h"
/* Driver APIs */
#include "ehrpwm.h"
#include "hw_pwmss.h"



/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief  This API configures the clock divider of the Time base module.
 *         The clock divider can be calculated using the equation
 *         TBCLK = SYSCLKOUT/(HSPCLKDIV × CLKDIV)
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   tbClk         Timebase clock to be generated.
 * \param   moduleClk     Input clock of the PWM module (sysclk2)
 *
 * \return  None.
 *
 **/
void EHRPWMTimebaseClkConfig(unsigned int baseAddr,
                             unsigned int tbClk,
                             unsigned int moduleClk)

{
    unsigned int clkDiv = moduleClk/tbClk;
    unsigned int hspClkDiv;
    unsigned int lspClkDiv, lspClkDivSetting = 0;

    if(clkDiv > EHRPWM_TBCTL_HSPCLKDIV_14)
    {
        hspClkDiv = EHRPWM_TBCTL_HSPCLKDIV_DIVBY14; /* reg setting */
        lspClkDiv = clkDiv/EHRPWM_TBCTL_HSPCLKDIV_14; /* divider */
        /* reg setting */
        while(lspClkDiv > 1)
        {
           lspClkDiv = lspClkDiv >> 1;
           lspClkDivSetting++;
        }
    }
    else
    {
        hspClkDiv = clkDiv/2; /* reg setting */
        /* divide by 1 */
        lspClkDivSetting = EHRPWM_TBCTL_HSPCLKDIV_DIVBY1;
    }

    HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
            (~EHRPWM_TBCTL_CLKDIV)) | ((lspClkDivSetting <<
            EHRPWM_TBCTL_CLKDIV_SHIFT) & EHRPWM_TBCTL_CLKDIV);

    HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
            (~EHRPWM_TBCTL_HSPCLKDIV)) | ((hspClkDiv <<
            EHRPWM_TBCTL_HSPCLKDIV_SHIFT) & EHRPWM_TBCTL_HSPCLKDIV);
}


/**
 * \brief  This API configures the PWM Frequency/Period. The period count
 *         determines the period of the final output waveform. For the given
 *         period count, in the case of UP and DOWN counter the count value will
 *         be loaded as is. In the case of UP_DOWN counter the count is halfed.
 *
 * \param   baseAddr     Base Address of the PWM Module Registers.
 * \param   tbClk        Timebase clock.
 * \param   pwmFreq      Frequency of the PWM Output. If the counter direction
 *                       is up-down this value has to be halfed, so that the
 *                       period of the final output is equal to pwmFreq.
 *
 * \param   counterDir           Direction of the counter(up, down, up-down)
 * \param   enableShadowWrite    Whether write to Period register is to be shadowed
 *
 * \return  None.
 *
 **/
void EHRPWMPWMOpFreqSet(unsigned int baseAddr,
                        unsigned int tbClk,
                        unsigned int pwmFreq,
                        unsigned int counterDir,
                        bool enableShadowWrite)
{
     unsigned int tbPeriodCount = tbClk/pwmFreq;

     HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
             (~EHRPWM_PRD_LOAD_SHADOW_MASK)) | ((enableShadowWrite <<
            EHRPWM_TBCTL_PRDLD_SHIFT) & EHRPWM_PRD_LOAD_SHADOW_MASK);

     HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
             (~EHRPWM_COUNTER_MODE_MASK)) | ((counterDir <<
            EHRPWM_TBCTL_CTRMODE_SHIFT) &  EHRPWM_COUNTER_MODE_MASK);

     if(EHRPWM_COUNT_UP_DOWN == counterDir)
     {
         HWREGH(baseAddr + EHRPWM_TBPRD) = (unsigned short)tbPeriodCount/2;
     }
     else
     {
         HWREGH(baseAddr + EHRPWM_TBPRD) = (unsigned short)tbPeriodCount;
     }

}


/**
 * \brief  This API configures emulation mode. This setting determines
 *         the behaviour of Timebase during emulation (debugging).
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   mode          Emulation mode. Possible values are,
 *                        - EHRPWM_STOP_AFTER_NEXT_TB_INCREMENT \n
 *                        - EHRPWM_STOP_AFTER_A_COMPLETE_CYCLE \n
 *                        - EHRPWM_FREE_RUN \n
 * \return  None.
 *
 **/
void EHRPWMTBEmulationModeSet(unsigned int baseAddr, unsigned int mode)
{
     HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
         (~EHRPWM_TBCTL_FREE_SOFT)) | (mode & EHRPWM_TBCTL_FREE_SOFT);
}


/**
 * \brief  This API enables the synchronization. When a sync-in event is generated
 *         the couter is reloaded with the new value. After sync the counter
 *         will use the new value.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   tbPhsValue    Phase value to be reloaded after sync
 * \param   phsCountDir   Count direction after sync. Possible values are
 *                        - EHRPWM_COUNT_DOWN_AFTER_SYNC \n
 *                        - EHRPWM_COUNT_UP_AFTER_SYNC \n
 * \return  None.
 *
 **/
void EHRPWMTimebaseSyncEnable(unsigned int baseAddr,
                              unsigned int tbPhsValue,
                              unsigned int phsCountDir)
{
     HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
             (~EHRPWM_TBCTL_PHSDIR)) |((phsCountDir << EHRPWM_TBCTL_PHSDIR_SHIFT)
             & EHRPWM_TBCTL_PHSDIR);

     HWREGH(baseAddr + EHRPWM_TBPHS) = tbPhsValue & EHRPWM_TBPHS_TBPHS;

     HWREGH(baseAddr + EHRPWM_TBCTL) |= EHRPWM_SYNC_ENABLE;
}


/**
 * \brief   This API disables the synchronization. Even if sync-in event occurs
 *          the count value will not be reloaded.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 *
 * \return  None.
 *
 **/
void EHRPWMTimebaseSyncDisable(unsigned int baseAddr)
{
     HWREGH(baseAddr + EHRPWM_TBCTL) &= (~EHRPWM_SYNC_ENABLE);
}


/**
 * \brief   This API generates sw forced sync pulse. This API can be used for
 *          testing. When this API is called sync-in will be generated.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 *
 * \return  None.
 *
 **/
void EHRPWMTriggerSWSync(unsigned int baseAddr)
{
     HWREGH(baseAddr + EHRPWM_TBCTL) |= EHRPWM_TBCTL_SWFSYNC;
}


/**
 * \brief   This API selects the output sync source. It determines on which of
 *          the following event sync-out has to be generated.
 *
 * \param   baseAddr        Base Address of the PWM Module Registers.
 * \param   syncOutMode     Sync out mode. Possible values are,
 *                          - EHRPWM_SYNCOUT_SYNCIN \n
 *                          - EHRPWM_SYNCOUT_COUNTER_EQUAL_ZERO \n
 *                          - EHRPWM_SYNCOUT_COUNTER_EQUAL_COMPAREB \n
 *                          - EHRPWM_SYNCOUT_DISABLE \n
 * \return  None.
 *
 **/
void EHRPWMSyncOutModeSet(unsigned int baseAddr, unsigned int syncOutMode)
{
     HWREGH(baseAddr + EHRPWM_TBCTL) = (HWREGH(baseAddr + EHRPWM_TBCTL) &
             (~EHRPWM_SYNCOUT_MASK)) | syncOutMode;
}


/**
 * \brief   This API loads the TB counter. The new value is taken immediately.
 *
 * \param   baseAddr     Base Address of the PWM Module Registers.
 * \param   tbCount      Time base count value to be loaded.
 * \return  None.
 *
 **/
void EHRPWMWriteTBCount(unsigned int baseAddr, unsigned int tbCount)
{
     HWREGH(baseAddr + EHRPWM_TBCTR) = tbCount & EHRPWM_TBCTR_TBCTR;
}


/**
 * \brief   This API gets the TB counter current value. The count operation is
 *          not affected by the read.
 *
 * \param   baseAddr     Base Address of the PWM Module Registers.
 * \return  tbCount      Current Timebase count value.
 *
 **/
unsigned int EHRPWMReadTBCount(unsigned int baseAddr)
{
    return (unsigned int)(HWREGH(baseAddr + EHRPWM_TBCTR));
}


/**
 * \brief   This API gets the TB status as indicated by the tbStatusMask parameter
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   tbStatusMask  Indicates which status is needed.
 *                        - EHRPWM_TBSTS_CTRMAX
 *                          - whether the counter has reached the max value \n
 *                        - EHRPWM_TBSTS_SYNCI
 *                          - indicates external sync event has occured \n
 *                        - EHRPWM_TBSTS_CTRDIR - gives the counter direction \n
 *
 * \return  tbStatus      Requested status is returned. The user need
 *                        to extract the appropriate bits by shifting.
 *
 **/
unsigned int EHRPWMTBStatusGet(unsigned int baseAddr, unsigned int tbStatusMask)
{
    return (unsigned int)(HWREGH(baseAddr + EHRPWM_TBSTS) & tbStatusMask);
}


/**
 * \brief   This API clears the TB status bits indicated by the tbStatusMask parameter
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   tbStatusMask  Indicates which status bit need to be cleared.
 *                        - EHRPWM_TBSTS_CTRMAX \n
 *                        - EHRPWM_TBSTS_SYNCI \n
 *                        - EHRPWM_TBSTS_CTRDIR \n
 * \return  None
 *
 **/
void EHRPWMTBClearStatus(unsigned int baseAddr, unsigned int tbStatusMask)
{
    HWREGH(baseAddr + EHRPWM_TBSTS) |= tbStatusMask &
        ((EHRPWM_TBSTS_CTRMAX << EHRPWM_TBSTS_CTRMAX_SHIFT)|
         (EHRPWM_TBSTS_SYNCI << EHRPWM_TBSTS_SYNCI_SHIFT));
}


/**
 * \brief   This API loads the CMPA value. When CMPA value equals the counter
 *          value, then an event is generated both in the up direction and
 *          down direction.
 *
 * \param   baseAddr                   Base Address of the PWM Module Registers.
 * \param   CMPAVal                    CMPA value to be loaded.
 * \param   enableShadowWrite          Enable write to shadow register.
 * \param   ShadowToActiveLoadTrigger  Shadow to active register load trigger.
 * \param   OverwriteShadowFull        Overwrite even if previous value is not
 *                                     loaded to active register.
 *
 * \return  bool    Flag indicates whether the CMPA value is
 *                  written or not.
 *
 **/
bool EHRPWMLoadCMPA(unsigned int baseAddr,
                    unsigned int CMPAVal,
                    bool enableShadowWrite,
                    unsigned int ShadowToActiveLoadTrigger,
                    bool OverwriteShadowFull)
{
    bool status = FALSE;

    if((OverwriteShadowFull) ||
        ((HWREGH(baseAddr+EHRPWM_CMPCTL) & EHRPWM_CMPCTL_SHDWAFULL) ==
                             EHRPWM_SHADOW_A_EMPTY))
    {
        HWREGH(baseAddr + EHRPWM_CMPCTL) = (HWREGH(baseAddr + EHRPWM_CMPCTL) &
            (~EHRPWM_CMPCTL_SHDWAMODE)) | ((enableShadowWrite <<
            EHRPWM_CMPCTL_SHDWAMODE_SHIFT) & EHRPWM_CMPCTL_SHDWAMODE);

        HWREGH(baseAddr + EHRPWM_CMPCTL) = (HWREGH(baseAddr + EHRPWM_CMPCTL) &
            (~EHRPWM_COMPA_LOAD_MASK)) |((ShadowToActiveLoadTrigger <<
            EHRPWM_CMPCTL_LOADAMODE_SHIFT) & EHRPWM_COMPA_LOAD_MASK);

        HWREGH(baseAddr + EHRPWM_CMPA) = CMPAVal & EHRPWM_CMPA_CMPA;

        status = TRUE;
    }

    return status;
}


/**
 * \brief  This API loads the CMPB value. When CMPB value equals the counter
 *         value, then an event is generated both in the up direction and
 *         down direction.
 *
 * \param   baseAddr                   Base Address of the PWM Module Registers.
 * \param   CMPBVal                    CMPB value to be loaded.
 * \param   enableShadowWrite          Enable write to shadow register.
 * \param   ShadowToActiveLoadTrigger  Shadow to active register load trigger.
 * \param   OverwriteShadowFull        Overwrite even if previous value is not
 *                                     loaded to active register.
 *
 * \return  bool   Flag indicates whether the CMPB value is
 *                 written or not.
 *
 **/
bool EHRPWMLoadCMPB(unsigned int baseAddr,
                    unsigned int CMPBVal,
                    bool enableShadowWrite,
                    unsigned int ShadowToActiveLoadTrigger,
                    bool OverwriteShadowFull)
{
    bool status = FALSE;

    if((OverwriteShadowFull) ||
        ((HWREGH(baseAddr+EHRPWM_CMPCTL) & EHRPWM_CMPCTL_SHDWBFULL) ==
                             EHRPWM_SHADOW_B_EMPTY))
    {
        HWREGH(baseAddr + EHRPWM_CMPCTL) = (HWREGH(baseAddr + EHRPWM_CMPCTL)
            & (~EHRPWM_CMPCTL_SHDWBMODE)) | ((enableShadowWrite <<
            EHRPWM_CMPCTL_SHDWBMODE_SHIFT) & EHRPWM_CMPCTL_SHDWBMODE);

        HWREGH(baseAddr + EHRPWM_CMPCTL) = (HWREGH(baseAddr + EHRPWM_CMPCTL) &
            (~EHRPWM_COMPB_LOAD_MASK)) | ((ShadowToActiveLoadTrigger <<
            EHRPWM_CMPCTL_LOADBMODE_SHIFT) & EHRPWM_COMPB_LOAD_MASK);

        HWREGH(baseAddr + EHRPWM_CMPB) = CMPBVal & EHRPWM_CMPB_CMPB;

        status = TRUE;
    }
    return status;
}


/**
 * \brief  This API configures the action to be taken on A by the Action
 *         qualifier module upon receiving the events. This will determine
 *         the output waveform.
 *
 * \param   zero      Action to be taken when CTR = 0
 * \param   period    Action to be taken when CTR = PRD
 * \param   CAUp      Action to be taken when CTR = CAUp
 * \param   CADown    Action to be taken when CTR = CADown
 * \param   CBUp      Action to be taken when CTR = CBUp
 * \param   CBDown    Action to be taken when CTR = CBDown
 * \param   SWForced  Action to be taken when SW forced event has been generated
 *
 *     Possible values for the actions are
 *          - EHRPWM_XXXX_XXXX_DONOTHING \n
 *          - EHRPWM_XXXX_XXXX_CLEAR \n
 *          - EHRPWM_XXXX_XXXX_SET \n
 *          - EHRPWM_XXXX_XXXX_TOGGLE \n
 *
 * \return  None
 *
 **/
void EHRPWMConfigureAQActionOnA(unsigned int baseAddr,
                                unsigned int zero,
                                unsigned int period,
                                unsigned int CAUp,
                                unsigned int CADown,
                                unsigned int CBUp,
                                unsigned int CBDown,
                                unsigned int SWForced)
{
    HWREGH(baseAddr + EHRPWM_AQCTLA) =
        ((CBDown << EHRPWM_AQCTLA_CBD_SHIFT) & EHRPWM_AQCTLA_CBD) |
        ((CBUp << EHRPWM_AQCTLA_CBU_SHIFT) & EHRPWM_AQCTLA_CBU) |
        ((CADown << EHRPWM_AQCTLA_CAD_SHIFT) & EHRPWM_AQCTLA_CAD) |
        ((CAUp << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
        ((period << EHRPWM_AQCTLA_PRD_SHIFT) & EHRPWM_AQCTLA_PRD) |
        ((zero << EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);


    HWREGH(baseAddr + EHRPWM_AQSFRC) = (HWREGH(baseAddr + EHRPWM_AQSFRC) &
            (~EHRPWM_AQSFRC_ACTSFA)) | ((SWForced <<
            EHRPWM_AQSFRC_ACTSFA_SHIFT) & EHRPWM_AQSFRC_ACTSFA);
}


/**
 * \brief  his API configures the action to be taken on B by the Action
 *         qualifier module upon receiving the events. This will determine
 *         the output waveform.
 *
 * \param   zero      Action to be taken when CTR = 0
 * \param   period    Action to be taken when CTR = PRD
 * \param   CAUp      Action to be taken when CTR = CAUp
 * \param   CADown    Action to be taken when CTR = CADown
 * \param   CBUp      Action to be taken when CTR = CBUp
 * \param   CBDown    Action to be taken when CTR = CBDown
 * \param   SWForced  Action to be taken when SW forced event has been generated
 *
 *     Possible values for the actions are
 *         - EHRPWM_XXXX_XXXX_DONOTHING \n
 *         - EHRPWM_XXXX_XXXX_CLEAR \n
 *         - EHRPWM_XXXX_XXXX_SET \n
 *         - EHRPWM_XXXX_XXXX_TOGGLE \n
 *
 * \return  None
 *
 **/
void EHRPWMConfigureAQActionOnB(unsigned int baseAddr,
                                unsigned int zero,
                                unsigned int period,
                                unsigned int CAUp,
                                unsigned int CADown,
                                unsigned int CBUp,
                                unsigned int CBDown,
                                unsigned int SWForced)
{
    HWREGH(baseAddr + EHRPWM_AQCTLB) =
        ((CBDown << EHRPWM_AQCTLB_CBD_SHIFT) & EHRPWM_AQCTLB_CBD) |
        ((CBUp << EHRPWM_AQCTLB_CBU_SHIFT) & EHRPWM_AQCTLB_CBU) |
        ((CADown << EHRPWM_AQCTLB_CAD_SHIFT) & EHRPWM_AQCTLB_CAD) |
        ((CAUp << EHRPWM_AQCTLB_CAU_SHIFT) & EHRPWM_AQCTLB_CAU) |
        ((period << EHRPWM_AQCTLB_PRD_SHIFT) & EHRPWM_AQCTLB_PRD) |
        ((zero << EHRPWM_AQCTLB_ZRO_SHIFT) & EHRPWM_AQCTLB_ZRO);


    HWREGH(baseAddr + EHRPWM_AQSFRC) =
        (HWREGH(baseAddr + EHRPWM_AQSFRC) & (~EHRPWM_AQSFRC_ACTSFB)) |
     ((SWForced << EHRPWM_AQSFRC_ACTSFB_SHIFT) & EHRPWM_AQSFRC_ACTSFB);
}


/**
 * \brief  This API triggers the SW forced event on A. This can be used for
 *         testing the AQ sub-module.Every call to this API will trigger a
 *         single event.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMSWForceA(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_AQSFRC) |= EHRPWM_AQSFRC_OTSFA;
}


/**
 * \brief  This API triggers the SW forced event on B. This can be used for
 *         testing the AQ sub-module.Every call to this API will trigger a
 *         single event.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMSWForceB(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_AQSFRC) |= EHRPWM_AQSFRC_OTSFB;
}



/**
 * \brief   This API forces a value continuously on A. The output can be forced
 *          to low or high.
 *
 * \param   baseAddr             Base Address of the PWM Module Registers.
 * \param   forceVal             Value to be forced
 * \param   activeRegReloadMode  Shadow to active reg load trigger
 *
 * \return  None
 *
 **/
void EHRPWMAQContSWForceOnA(unsigned int baseAddr,
                            unsigned int forceVal,
                            unsigned int activeRegReloadMode)
{
    HWREGH(baseAddr + EHRPWM_AQSFRC) =
        (HWREGH(baseAddr + EHRPWM_AQSFRC) & (~EHRPWM_AQSFRC_RLDCSF)) |
       ((activeRegReloadMode << EHRPWM_AQSFRC_RLDCSF_SHIFT) & EHRPWM_AQSFRC_RLDCSF);


    HWREGH(baseAddr + EHRPWM_AQCSFRC) =
        (HWREGH(baseAddr + EHRPWM_AQCSFRC) & (~EHRPWM_AQCSFRC_CSFA)) |
       ((forceVal << EHRPWM_AQCSFRC_CSFA_SHIFT) & EHRPWM_AQCSFRC_CSFA);
}


/**
 * \brief   This API forces a value continuously on B. The output can be forced
 *          to low or high.
 *
 * \param   baseAddr               Base Address of the PWM Module Registers.
 * \param   forceVal               Value to be forced
 * \param   activeRegReloadMode    Shadow to active reg load trigger
 *
 * \return  None
 *
 **/
void EHRPWMAQContSWForceOnB(unsigned int baseAddr,
                            unsigned int forceVal,
                            unsigned int activeRegReloadMode)
{
    HWREGH(baseAddr + EHRPWM_AQSFRC) =
        (HWREGH(baseAddr + EHRPWM_AQSFRC) & (~EHRPWM_AQSFRC_RLDCSF)) |
    ((activeRegReloadMode << EHRPWM_AQSFRC_RLDCSF_SHIFT) & EHRPWM_AQSFRC_RLDCSF);

    HWREGH(baseAddr + EHRPWM_AQCSFRC) =
        (HWREGH(baseAddr + EHRPWM_AQCSFRC) & (~EHRPWM_AQCSFRC_CSFB)) |
        ((forceVal << EHRPWM_AQCSFRC_CSFB_SHIFT) & EHRPWM_AQCSFRC_CSFB);
}


/**
 * \brief   This API selects the source for delay blocks in dead band sub-module.
 *          The Dead band generator has two sub-modules, one for raising edge delay
 *          and the other for falling edge delay. This can be configured when a delay
 *          is need between two signals during signal change. The dead band generator
 *          is usefull in full-inverters.
 *
 * \param   baseAddr          Base Address of the PWM Module Registers.
 * \param   DBgenSource       Source selection. The possible values can be
 *                            - EHRPWM_DBCTL_IN_MODE_AREDAFED \n
 *                            - EHRPWM_DBCTL_IN_MODE_BREDAFED \n
 *                            - EHRPWM_DBCTL_IN_MODE_AREDBFED \n
 *                            - EHRPWM_DBCTL_IN_MODE_BREDBFED \n
 *
 * \return  None
 *
 **/

void EHRPWMDBSourceSelect(unsigned int baseAddr, unsigned int DBgenSource)
{
    HWREGH(baseAddr + EHRPWM_DBCTL) =
        (HWREGH(baseAddr + EHRPWM_DBCTL) & (~EHRPWM_DBCTL_IN_MODE)) |
        ((DBgenSource << EHRPWM_DBCTL_IN_MODE_SHIFT) & EHRPWM_DBCTL_IN_MODE);
}


/**
 * \brief   This API selects the polarity. This allows to selectively invert
 *          one of the delayed signals before it is sent out of the dead-band
 *          sub-module.
 *
 * \param   baseAddr         Base Address of the PWM Module Registers.
 * \param   DBgenSource      Polarity. The possible values can be :
 *                           - HRPWM_DBCTL_POLSEL_ACTIVEHIGH \n
 *                           - EHRPWM_DBCTL_POLSEL_ALC \n
 *                           - EHRPWM_DBCTL_POLSEL_AHC \n
 *                           - EHRPWM_DBCTL_POLSEL_ACTIVELOW \n
 * \return  None
 *
 **/
void EHRPWMDBPolaritySelect(unsigned int baseAddr, unsigned int DBgenPol)
{
    HWREGH(baseAddr + EHRPWM_DBCTL) =
        (HWREGH(baseAddr + EHRPWM_DBCTL) & (~EHRPWM_DBCTL_POLSEL)) |
       ((DBgenPol << EHRPWM_DBCTL_POLSEL_SHIFT) & EHRPWM_DBCTL_POLSEL);
}


/**
 * \brief   This API selects output mode. This allows to selectively enable or
 *          bypass the dead-band generation for the falling-edge and rising-edge
 *          delay.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   DBgenOpMode   Output mode. The possible values can be :
 *                        - EHRPWM_DBCTL_OUT_MODE_BYPASS \n
 *                        - EHRPWM_DBCTL_OUT_MODE_NOREDBFED \n
 *                        - EHRPWM_DBCTL_OUT_MODE_AREDNOFED \n
 *                        - EHRPWM_DBCTL_OUT_MODE_AREDBFED \n
 * \return  None
 *
 **/
void EHRPWMDBOutput(unsigned int baseAddr, unsigned int DBgenOpMode)
{
    HWREGH(baseAddr + EHRPWM_DBCTL) =
        (HWREGH(baseAddr + EHRPWM_DBCTL) & (~EHRPWM_DBCTL_OUT_MODE)) |
       ((DBgenOpMode << EHRPWM_DBCTL_OUT_MODE_SHIFT) & EHRPWM_DBCTL_OUT_MODE);
}


/**
 * \brief   This API sets the raising edge delay.
 *
 * \param   baseAddr           Base Address of the PWM Module Registers.
 * \param   raisingEdgeDelay   Raising Edge Delay
 *
 * \return  None
 *
 **/
void EHRPWMDBConfigureRED(unsigned int baseAddr, unsigned int raisingEdgeDelay)
{
    HWREGH(baseAddr + EHRPWM_DBRED) =
        (HWREGH(baseAddr + EHRPWM_DBRED) & (~EHRPWM_DBRED_DEL)) |
        ((raisingEdgeDelay << EHRPWM_DBRED_DEL_SHIFT) & EHRPWM_DBRED_DEL);
}


/**
 * \brief   This API sets the Falling edge delay.
 *
 * \param   baseAddr            Base Address of the PWM Module Registers.
 * \param   fallingEdgeDelay    Falling Edge Delay
 *
 * \return  None
 *
 **/
void EHRPWMDBConfigureFED(unsigned int baseAddr, unsigned int fallingEdgeDelay)
{
    HWREGH(baseAddr + EHRPWM_DBFED) =
        (HWREGH(baseAddr + EHRPWM_DBFED) & (~EHRPWM_DBFED_DEL)) |
           ((fallingEdgeDelay << EHRPWM_DBFED_DEL_SHIFT) & EHRPWM_DBFED_DEL);
}


/**
 * \brief   This API configures the chopper duty cyce. In Chopper sub-module the
 *          PWM signal is modulated with a carrier signal. Th duty cycle of the
 *          carrier signal is configured with this API.
 *
 * \param   baseAddr     Base Address of the PWM Module Registers.
 * \param   dutyCycle    Duty cycle of the chopping carrier.
 *                       Possible values are :
 *                       - EHRPWM_DUTY_12_5_PER \n
 *                       - EHRPWM_DUTY_25_PER \n
 *                       - EHRPWM_DUTY_37_5_PER \n
 *                       - EHRPWM_DUTY_50_PER \n
 *                       - EHRPWM_DUTY_62_5_PER \n
 *                       - EHRPWM_DUTY_75_PER \n
 *                       - EHRPWM_DUTY_87_5_PER \n
 *
 * \return  None
 *
 **/
void EHRPWMConfigureChopperDuty(unsigned int baseAddr, unsigned int dutyCycle)
{
    HWREGH(baseAddr + EHRPWM_PCCTL) =
        (HWREGH(baseAddr + EHRPWM_PCCTL) & (~EHRPWM_PCCTL_CHPDUTY)) |
       ((dutyCycle << EHRPWM_PCCTL_CHPDUTY_SHIFT) & EHRPWM_PCCTL_CHPDUTY);
}


/**
 * \brief   This API configures the chopper frequency. In chopper sub-module the
 *          PWM signal is modulated with a carrier signal. The frequency of the
 *          carrier signal is configured with this API.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   freqDiv     Frequency divider
 * \return  None
 *
 **/
void EHRPWMConfigureChopperFreq(unsigned int baseAddr, unsigned int freqDiv)
{

    if(freqDiv > EHRPWM_PCCTL_CHPFREQ_DIVBY8)
    {
       freqDiv =  EHRPWM_PCCTL_CHPFREQ_DIVBY8;
    }

    HWREGH(baseAddr + EHRPWM_PCCTL) =
        (HWREGH(baseAddr + EHRPWM_PCCTL) & (~EHRPWM_PCCTL_CHPFREQ)) |
        ((freqDiv << EHRPWM_PCCTL_CHPFREQ_SHIFT) & EHRPWM_PCCTL_CHPFREQ);
}


/**
 * \brief  This API configures one shot pulse width. The chopper module is
 *         useful in switching operations for pulse transformers. The one-shot
 *         block provides a high energy first pulse to ensure hard and fast power
 *         switch turn on, while the subsequent pulses sustain pulses, ensuring
 *         the power switch remains on.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   OSPWCycles    Number of clocks the OSPW to be ON.
 *
 * \return  None
 *
 **/
void EHRPWMConfigureChopperOSPW(unsigned int baseAddr, unsigned int OSPWCycles)
{
    HWREGH(baseAddr + EHRPWM_PCCTL) =
        (HWREGH(baseAddr + EHRPWM_PCCTL) & (~EHRPWM_PCCTL_OSHTWTH)) |
       ((OSPWCycles << EHRPWM_PCCTL_OSHTWTH_SHIFT) & EHRPWM_PCCTL_OSHTWTH);
}


/**
 * \brief   This API enables the PWM chopper sub-module.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/

void EHRPWMChopperEnable(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_PCCTL) |= EHRPWM_PCCTL_CHPEN;
}


/**
 * \brief   This API disables the PWM chopper sub-module. This will cause the
 *          chopper module to be by-passed.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMChopperDisable(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_PCCTL) &= (~EHRPWM_PCCTL_CHPEN);
}


/**
 * \brief   This API enables the trip event. The trip signals indicates
 *          external fault, and the ePWM outputs can be programmed to
 *          respond accordingly when faults occur.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   osht_CBC    Enable OST or CBC event
 *
 * \return  None
 *
 **/
void EHRPWMTZTripEventEnable(unsigned int baseAddr, bool osht_CBC)
{
     if(EHRPWM_TZ_ONESHOT == osht_CBC)
     {
         HWREGH(baseAddr + EHRPWM_TZSEL) |= EHRPWM_TZSEL_OSHT1;
     }
     if(EHRPWM_TZ_CYCLEBYCYCLE == osht_CBC)
     {
         HWREGH(baseAddr + EHRPWM_TZSEL) |= EHRPWM_TZSEL_CBC1;
     }
}


/**
 * \brief   This API disable the trip event. The trip events will be ignored.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   osht_CBC    Disable OST or CBC event
 *
 * \return  None
 *
 **/
void EHRPWMTZTripEventDisable(unsigned int baseAddr, bool osht_CBC)
{
     if(EHRPWM_TZ_ONESHOT == osht_CBC)
     {
         HWREGH(baseAddr + EHRPWM_TZSEL) &= (~EHRPWM_TZSEL_OSHT1);
     }
     if(EHRPWM_TZ_CYCLEBYCYCLE == osht_CBC)
     {
         HWREGH(baseAddr + EHRPWM_TZSEL) &= (~EHRPWM_TZSEL_CBC1);
     }
}


/**
 * \brief   This API configures the o/p on A when a trip event is recognized.
 *          The output can be set to high or low or high impedence.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   opValue     o/p state to be configured
 *
 * \return  None
 *
 **/
void EHRPWMTZForceAOnTrip(unsigned int baseAddr, unsigned int opValue)
{
   HWREGH(baseAddr + EHRPWM_TZCTL) =
       (HWREGH(baseAddr + EHRPWM_TZCTL) & (~EHRPWM_TZCTL_TZA)) |
       ((opValue << EHRPWM_TZCTL_TZA_SHIFT) & EHRPWM_TZCTL_TZA);
}


/**
 * \brief  This API configures the o/p on B when a trip event is recognised.
 *         The output can be set to high or low or high impedence.
 *
 * \param   baseAddr   Base Address of the PWM Module Registers.
 * \param   opValue    o/p state to be configured
 *
 * \return  None
 *
 **/
void EHRPWMTZForceBOnTrip(unsigned int baseAddr, unsigned int opValue)
{
   HWREGH(baseAddr + EHRPWM_TZCTL) =
       (HWREGH(baseAddr + EHRPWM_TZCTL) & (~EHRPWM_TZCTL_TZB)) |
       ((opValue << EHRPWM_TZCTL_TZB_SHIFT) & EHRPWM_TZCTL_TZB);
}


/**
 * \brief   This API enables the trip interrupt. When trip event occurs
 *          the sub-module can be configured to interrupt CPU.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   osht_CBC    enable OST or CBC
 *
 * \return  None
 *
 **/
void EHRPWMTZIntEnable(unsigned int baseAddr, bool osht_CBC)
{
    if(EHRPWM_TZ_ONESHOT == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZEINT) |= EHRPWM_TZEINT_OST;
    }
    if(EHRPWM_TZ_CYCLEBYCYCLE == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZEINT) |= EHRPWM_TZEINT_CBC;
    }
}


/**
 * \brief   This API disables the trip interrupt.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   osht_CBC    disable OST or CBC
 *
 * \return  None
 *
 **/
void EHRPWMTZIntDisable(unsigned int baseAddr, bool osht_CBC)
{
    if(EHRPWM_TZ_ONESHOT == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZEINT) &= (~EHRPWM_TZEINT_OST);
    }
    if(EHRPWM_TZ_CYCLEBYCYCLE == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZEINT) &= (~EHRPWM_TZEINT_CBC);
    }
}


/**
 * \brief   This API returns the flag status requested.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   flagToRead  status to be read. The possible values can be,
 *                      - EHRPWM_TZCLR_OST \n
 *                      - EHRPWM_TZCLR_CBC \n
 *                      - EHRPWM_TZCLR_INT \n
 *
 * \return  None
 *
 **/
unsigned int EHRPWMTZFlagGet(unsigned int baseAddr, unsigned int flagToRead)
{
    return (unsigned int)(HWREGH(baseAddr + EHRPWM_TZFLG) & flagToRead);
}


/**
 * \brief   This API clears the flag.
 *
 * \param   baseAddr     Base Address of the PWM Module Registers.
 * \param   flagToClear  Status to be cleared. The possible values can be,
 *                       - EHRPWM_TZCLR_OST \n
 *                       - EHRPWM_TZCLR_CBC \n
 *                       - EHRPWM_TZCLR_INT \n
 *
 *
 * \return  None
 *
 **/
void EHRPWMTZFlagClear(unsigned int baseAddr, unsigned int flagToClear)
{
    HWREGH(baseAddr + EHRPWM_TZCLR) = flagToClear &
        (EHRPWM_TZCLR_OST | EHRPWM_TZCLR_CBC | EHRPWM_TZCLR_INT);
}


/**
 * \brief   This API enables to generate SW forced trip
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   osht_CBC    generate OST or CBC trip
 *
 * \return  None
 *
 **/
void EHRPWMTZSWFrcEvent(unsigned int baseAddr, bool osht_CBC)
{
    if(EHRPWM_TZ_ONESHOT == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZFRC) = EHRPWM_TZFRC_OST;
    }
    if(EHRPWM_TZ_CYCLEBYCYCLE == osht_CBC)
    {
        HWREGH(baseAddr + EHRPWM_TZFRC) = EHRPWM_TZFRC_CBC;
    }
}


/**
 * \brief   This API disables the interrupt.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMETIntDisable(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_ETSEL) &= (~EHRPWM_ETSEL_INTEN);
}


/**
 * \brief   This API enables the interrupt.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMETIntEnable(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_ETSEL) |= EHRPWM_ETSEL_INTEN;
}


/**
 * \brief   This API selects the interrupt source.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   selectInt   Event which triggers interrupt. The possible source can be,
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUZERO \n
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUPRD \n
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUCMPAINC \n
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUCMPADEC \n
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBINC \n
 *                      - EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBDEC \n
 *
 * \return  None
 *
 **/
void EHRPWMETIntSourceSelect(unsigned int baseAddr, unsigned int selectInt)
{
    HWREGH(baseAddr + EHRPWM_ETSEL) =
        (HWREGH(baseAddr + EHRPWM_ETSEL) & (~EHRPWM_ETSEL_INTSEL)) |
       ((selectInt << EHRPWM_ETSEL_INTSEL_SHIFT) & EHRPWM_ETSEL_INTSEL);
}


/**
 * \brief   This API prescales the event on which interrupt is to be generated
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   prescale    prescalar value
 *
 * \return  None
 *
 **/
void EHRPWMETIntPrescale(unsigned int baseAddr, unsigned int prescale)
{
    HWREGH(baseAddr + EHRPWM_ETPS) =
        (HWREGH(baseAddr + EHRPWM_ETPS) & (~EHRPWM_ETPS_INTPRD)) |
       ((prescale << EHRPWM_ETPS_INTPRD_SHIFT) & EHRPWM_ETPS_INTPRD);
}


/**
 * \brief   This API returns the number of events occured
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  eventCount  number of events occured
 *
 **/
bool EHRPWMETEventCount(unsigned int baseAddr)
{
    return (bool)((HWREGH(baseAddr + EHRPWM_ETPS) & EHRPWM_ETPS_INTCNT) >>
                EHRPWM_ETPS_INTCNT_SHIFT);
}


/**
 * \brief   This API returns the interrupt status
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  status      Status of the interrupt
 *
 **/
bool EHRPWMETIntStatus(unsigned int baseAddr)
{
    return (bool)((HWREGH(baseAddr + EHRPWM_ETFLG) & EHRPWM_ETFLG_INT) >>
                EHRPWM_ETFLG_INT_SHIFT);
}


/**
 * \brief   This API clears the interrupt
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/

void EHRPWMETIntClear(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_ETCLR) |= EHRPWM_ETCLR_INT;
}


/**
 * \brief   This API forces interrupt to be generated
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMETIntSWForce(unsigned int baseAddr)
{
    HWREGH(baseAddr + EHRPWM_ETFRC) |= EHRPWM_ETFRC_INT;
}


/**
 * \brief   This API loads the HR PHS value.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 * \param   TBPHSHRVal  TB PHS HR value
 *
 * \return  None
 *
 **/

void EHRPWMLoadTBPHSHR(unsigned int baseAddr, unsigned int TBPHSHRVal)
{
    HWREGH(baseAddr + EHRPWM_TBPHSHR) =
        (HWREGH(baseAddr + EHRPWM_TBPHSHR) & (~EHRPWM_TBPHSHR_TBPHSHR)) |
        ((TBPHSHRVal << EHRPWM_TBPHSHR_TBPHSHR_SHIFT) & EHRPWM_TBPHSHR_TBPHSHR);
}


/**
 * \brief   This API loads CMPAHR value.
 *
 * \param   baseAddr                  Base Address of the PWM Module Registers.
 * \param   CMPAHRVal                 CMPAHR value to he loaded
 * \param   ShadowToActiveLoadTrigger Condition when the active reg to be loaded
 *                                    from shadow register.
 *
 * \return  None
 *
 **/
void EHRPWMLoadCMPAHR(unsigned int baseAddr,
                      unsigned int CMPAHRVal,
                      unsigned int ShadowToActiveLoadTrigger)
{
    HWREGH(baseAddr + EHRPWM_CMPAHR) =
        (HWREGH(baseAddr + EHRPWM_CMPAHR) & (~EHRPWM_CMPAHR_CMPAHR)) |
        ((CMPAHRVal << EHRPWM_CMPAHR_CMPAHR_SHIFT) & EHRPWM_CMPAHR_CMPAHR);

    HWREGH(baseAddr + EHRPWM_HRCNFG) =
        (HWREGH(baseAddr + EHRPWM_HRCNFG) & (~EHRPWM_HR_HRLOAD)) |
        ((ShadowToActiveLoadTrigger << EHRPWM_HR_HRLOAD_SHIFT) & EHRPWM_HR_HRLOAD);
}


/**
 * \brief   This API configures control mode and edge mode. In also enables the
 *          HR sub-module.
 *
 * \param   baseAddr      Base Address of the PWM Module Registers.
 * \param   ctrlMode      phase control or duty control
 * \param   MEPCtrlEdge      Edge on which MEP to be applied (raising, falling, both)
 *
 * \return  None
 *
 **/
void EHRPWMConfigHR(unsigned int baseAddr,
                    unsigned int ctrlMode,
                    unsigned int MEPCtrlEdge)
{
    HWREGH(baseAddr + EHRPWM_HRCNFG) =
        (HWREGH(baseAddr + EHRPWM_HRCNFG) & (~EHRPWM_HR_CTLMODE)) |
        ((ctrlMode << EHRPWM_HR_CTLMODE_SHIFT) & EHRPWM_HR_CTLMODE);

    HWREGH(baseAddr + EHRPWM_HRCNFG) =
        (HWREGH(baseAddr + EHRPWM_HRCNFG) & (~EHRPWM_HR_EDGEMODE)) |
        ((MEPCtrlEdge << EHRPWM_HR_EDGEMODE_SHIFT) & EHRPWM_HR_EDGEMODE);
}


/**
 * \brief   This API disables the HR sub-module.
 *
 * \param   baseAddr    Base Address of the PWM Module Registers.
 *
 * \return  None
 *
 **/
void EHRPWMHRDisable(unsigned int baseAddr)
{
     HWREGH(baseAddr + EHRPWM_HRCNFG) &= (~EHRPWM_HR_EDGEMODE);
}

/**
 * \brief   This functions enables clock for EHRPWM module in PWMSS subsystem.
 *
 * \param   baseAdd   It is the Memory address of the PWMSS instance used.
 *
 * \return  None.
 *
 **/
void EHRPWMClockEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + PWMSS_CLOCK_CONFIG) |= PWMSS_EHRPWM_CLK_EN_ACK;
}

/**
 * \brief   This functions enables clock for EHRPWM module in PWMSS subsystem.
 *
 * \param   baseAdd   It is the Memory address of the PWMSS instance used.
 *
 * \return  None.
 *
 **/
void EHRPWMClockDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + PWMSS_CLOCK_CONFIG) |= PWMSS_EHRPWM_CLK_STOP_ACK;
}

/**
 * \brief   This functions determines whether clock is enabled or not.
 *
 * \param   baseAdd   It is the Memory address of the PWMSS instance used.
 *
 * \return  return's '1' if clocked is enabled.
 *          return's '0' if clocked is not enabled.
 *
 **/
unsigned int EHRPWMClockEnableStatusGet(unsigned int baseAdd)
{
    unsigned int status;

    status = HWREG(baseAdd + PWMSS_CLOCK_STATUS);

    status = status << PWMSS_EHRPWM_CLK_EN_ACK_SHIFT;

    return status;
}

/**
 * \brief   This functions determines whether clock is disabled or not.
 *
 * \param   baseAdd   It is the Memory address of the PWMSS instance used.
 *
 * \return  return's '1' if clocked is disabled.
 *          return's '0' if clocked is not disabled.
 *
 **/
unsigned int EHRPWMClockDisableStatusGet(unsigned int baseAdd)
{
    unsigned int status;

    status = HWREG(baseAdd + PWMSS_CLOCK_STATUS);

    status = status << PWMSS_EHRPWM_CLK_STOP_ACK_SHIFT;

    return status;
}

