/**
 *  \file       ecap.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for ECAP. It also contains some
 *              related macro definitions and some files to be included.
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


#ifndef _ECAP_H_
#define _ECAP_H_

#include "hw_ecap.h"
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/*
** Values that can be passed to ECAPOperatingModeSelect API as modeSelect
** to select type operating mode.
*/

#define  ECAP_CAPTURE_MODE               1
#define  ECAP_APWM_MODE                  0 

/****************************************************************************/
/*
** Values that can be passed to ECAPTimeStampRead API as capEvtFlag
** to determine for which capture event time-stamp has to be returned
*/

#define  ECAP_CAPTURE_EVENT_1            0x08     
#define  ECAP_CAPTURE_EVENT_2            0x0c
#define  ECAP_CAPTURE_EVENT_3            0x10
#define  ECAP_CAPTURE_EVENT_4            0x14

/****************************************************************************/
/*
** Values that can be passed to ECAPOneShotModeConfig API as stopVal
** which determines number of captures allowed to occur before
** Capture register(1-4) frozen.\n
*/

#define  ECAP_CAPTURE_EVENT1_STOP        (0x00 << ECAP_ECCTL2_STOP_WRAP_SHIFT)  
#define  ECAP_CAPTURE_EVENT2_STOP        (0x01 << ECAP_ECCTL2_STOP_WRAP_SHIFT) 
#define  ECAP_CAPTURE_EVENT3_STOP        (0x02 << ECAP_ECCTL2_STOP_WRAP_SHIFT)
#define  ECAP_CAPTURE_EVENT4_STOP        (0x03 << ECAP_ECCTL2_STOP_WRAP_SHIFT)

/****************************************************************************/
/*
** Values that can be passed to ECAPAPWMPolarityConfig API as flag
** which determines the output polarity for APWM output
*/

#define  ECAP_APWM_ACTIVE_HIGH           0 
#define  ECAP_APWM_ACTIVE_LOW            1   

/****************************************************************************/
/*
** Values that can be passed to ECAPCounterControl API  as flag
** which determines whether counter to be configured  to stop
** or free running
*/

#define  ECAP_COUNTER_STOP               0
#define  ECAP_COUNTER_FREE_RUNNING       1

/****************************************************************************/
/*
** Values that can be passed to ECAPSyncInOutSelect API  as syncIn
** to disable syncIn or to enable counter to be loaded from
** CNTPHS register upon a SYNCI signal
*/

#define  ECAP_SYNC_IN_DISABLE            (0 << ECAP_ECCTL2_SYNCI_EN_SHIFT)
#define  ECAP_ENABLE_Counter             (1 << ECAP_ECCTL2_SYNCI_EN_SHIFT)

/****************************************************************************/
/*
** Values that can be passed to ECAPSyncInOutSelect API  as syncOut
** to select syncIn event to be the Sync-Out signal or select 
** PRD_eq event to be Sync-Out signal or to disaqble syncOut
** signal
*/

#define  ECAP_SYNC_IN                    (00 << ECAP_ECCTL2_SYNCO_SEL_SHIFT)
#define  ECAP_PRD_EQ                     (01 << ECAP_ECCTL2_SYNCO_SEL_SHIFT)
#define  ECAP_SYNC_OUT_DISABLE           (10 << ECAP_ECCTL2_SYNCO_SEL_SHIFT)
 
/****************************************************************************/
/*
** Values that can be passed to ECAPIntEnable/Disable  API 
** to enable or disable interrupt or it can be passed
** ECAPIntStatus to get the interrupt or it can be passed 
** to ECAPIntStatusClear to clear the interrupt status 
*/

#define  ECAP_CEVT1_INT                  ECAP_ECEINT_CEVT1                   
#define  ECAP_CEVT2_INT                  ECAP_ECEINT_CEVT2
#define  ECAP_CEVT3_INT                  ECAP_ECEINT_CEVT3
#define  ECAP_CEVT4_INT                  ECAP_ECEINT_CEVT4
#define  ECAP_CNTOVF_INT                 ECAP_ECEINT_CTROVF 
#define  ECAP_PRDEQ_INT                  ECAP_ECEINT_CTR_PRD
#define  ECAP_CMPEQ_INT                  ECAP_ECEINT_CTR_CMP

/* It can be passed to ECAPIntStatusClear to clear global interrupt flag */
#define ECAP_GLOBAL_INT                   ECAP_ECFLG_INT

/****************************************************************************/
/*
** Values that can be passed to ECAPStandByModeConfig API 
** to configure ECAP module in different stand by mode.
**  
*/
#define     ECAP_SMART_STAND_BY_WAKE_UP     3
#define     ECAP_FORCE_STAND_BY             0  
#define     ECAP_SMART_STAND_BY             2
#define     ECAP_NO_STAND_BY                1
/****************************************************************************/
/*
** Values that can be passed to ECAPIdleModeConfig API 
** to configure ECAP module in different Idle mode.
**  
*/
#define     ECAP_SMART_IDLE_WAKE_UP        3  
#define     ECAP_SMART_IDLE_MODE           2
#define     ECAP_FORCE_IDLE_MODE           0
#define     ECAP_NO_IDLE_MODE              1

/*
** Structure to save the ECAP context
*/
typedef struct ecapContext {
    unsigned short ecctl2;
    unsigned short ecclr;
    unsigned short eceint;
    unsigned int pwm0ssclkconfig;
    unsigned int tsctr;
    unsigned int cap1;
    unsigned int cap2;
}ECAPCONTEXT;

void ECAPClockStop(unsigned int baseAdd);
void ECAPClockEnable(unsigned int baseAdd);
void ECAPOneShotREARM(unsigned int baseAdd);
void ECAPGlobalIntEnable(unsigned int baseAdd);
void ECAPContinousModeConfig(unsigned int baseAdd);
void ECAPCaptureLoadingEnable(unsigned int baseAdd);
void ECAPCaptureLoadingDisable(unsigned int baseAdd);
unsigned int ECAPPeripheralIdGet(unsigned int baseAdd);
unsigned int ECAPClockStopStatusGet(unsigned int baseAdd);
unsigned int ECAPClockEnableStatusGet(unsigned int baseAdd);
void ECAPIntEnable(unsigned int baseAdd, unsigned int flag);
void ECAPIntDisable(unsigned int baseAdd, unsigned int flag);
void ECAPIntStatusClear(unsigned int baseAdd, unsigned int flag);
void ECAPCounterControl(unsigned int baseAdd, unsigned int flag);
void ECAPCounterConfig(unsigned int baseAdd, unsigned int countVal);
unsigned int ECAPIntStatus(unsigned int baseAdd, unsigned int flag);
void ECAPAPWMPolarityConfig(unsigned int baseAdd, unsigned int flag);
void ECAPSyncInOutSelect(unsigned int baseAdd, unsigned int syncIn,
                         unsigned int syncOut);
void ECAPPrescaleConfig(unsigned int baseAdd, unsigned int prescale);
void ECAPOneShotModeConfig(unsigned int baseAdd, unsigned int stopVal);
void ECAPAPWMCaptureConfig(unsigned int baseAdd, unsigned int compareVal,
                           unsigned int periodVal);
void ECAPAPWMShadowCaptureConfig(unsigned int baseAdd, unsigned int compareVal,
                                 unsigned int periodVal);
void ECAPOperatingModeSelect(unsigned int baseAdd, unsigned int modeSelect);
unsigned int ECAPTimeStampRead(unsigned int baseAdd, unsigned int capEvtFlag);
void ECAPCounterPhaseValConfig(unsigned int baseAdd, unsigned int cntPhaseVal);
void ECAPCapeEvtPolarityConfig(unsigned int baseAdd, unsigned int capEvt1pol,
                               unsigned int capEvt2pol, unsigned int capEvt3pol,
                               unsigned int capEvt4pol);
void ECAPCaptureEvtCntrRstConfig(unsigned int baseAdd, unsigned int CounterRst1,
                                 unsigned int CounterRst2,unsigned int CounterRst3,
                                 unsigned int CounterRst4);
void ECAPClockEnable(unsigned int baseAdd);
void ECAPClockDisable(unsigned int baseAdd);
unsigned int ECAPClockEnableStatusGet(unsigned int baseAdd);
unsigned int ECAPClockDisableStatusGet(unsigned int baseAdd);
extern void EcapContextSave(unsigned int ecapBase, unsigned int pwmssBase,
                            ECAPCONTEXT *contextPtr);
extern void EcapContextRestore(unsigned int ecapBase, unsigned int pwmssBase,
                               ECAPCONTEXT *contextPtr);

#endif  
