//*****************************************************************************
//
// hw_timer.h - Defines and macros used when accessing the timer.
//
// Copyright (c) 2005-2009 Luminary Micro, Inc.  All rights reserved.
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  You may not combine
// this software with "viral" open-source software in order to form a larger
// program.  Any use in violation of the foregoing restrictions may subject
// the user to criminal sanctions under applicable laws, as well as to civil
// liability for the breach of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 4694 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

//*****************************************************************************
//
// The following are defines for the timer register offsets.
//
//*****************************************************************************
#define TIMER_O_CFG             0x00000000  // Configuration register
#define TIMER_O_TAMR            0x00000004  // TimerA mode register
#define TIMER_O_TBMR            0x00000008  // TimerB mode register
#define TIMER_O_CTL             0x0000000C  // Control register
#define TIMER_O_IMR             0x00000018  // Interrupt mask register
#define TIMER_O_RIS             0x0000001C  // Interrupt status register
#define TIMER_O_MIS             0x00000020  // Masked interrupt status reg.
#define TIMER_O_ICR             0x00000024  // Interrupt clear register
#define TIMER_O_TAILR           0x00000028  // TimerA interval load register
#define TIMER_O_TBILR           0x0000002C  // TimerB interval load register
#define TIMER_O_TAMATCHR        0x00000030  // TimerA match register
#define TIMER_O_TBMATCHR        0x00000034  // TimerB match register
#define TIMER_O_TAPR            0x00000038  // TimerA prescale register
#define TIMER_O_TBPR            0x0000003C  // TimerB prescale register
#define TIMER_O_TAPMR           0x00000040  // TimerA prescale match register
#define TIMER_O_TBPMR           0x00000044  // TimerB prescale match register
#define TIMER_O_TAR             0x00000048  // TimerA register
#define TIMER_O_TBR             0x0000004C  // TimerB register
#define TIMER_O_TAV             0x00000050  // GPTM Timer A Value
#define TIMER_O_TBV             0x00000054  // GPTM Timer B Value

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_CFG register.
//
//*****************************************************************************
#define TIMER_CFG_M             0x00000007  // GPTM Configuration.
#define TIMER_CFG_16_BIT        0x00000004  // Two 16 bit timers
#define TIMER_CFG_32_BIT_RTC    0x00000001  // 32 bit RTC
#define TIMER_CFG_32_BIT_TIMER  0x00000000  // 32 bit timer

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_CTL register.
//
//*****************************************************************************
#define TIMER_CTL_TBPWML        0x00004000  // TimerB PWM output level invert
#define TIMER_CTL_TBOTE         0x00002000  // TimerB output trigger enable
#define TIMER_CTL_TBEVENT_POS   0x00000000  // TimerB event mode - pos edge
#define TIMER_CTL_TBEVENT_NEG   0x00000400  // TimerB event mode - neg edge
#define TIMER_CTL_TBEVENT_BOTH  0x00000C00  // TimerB event mode - both edges
#define TIMER_CTL_TBEVENT_M     0x00000C00  // GPTM TimerB Event Mode.
#define TIMER_CTL_TBSTALL       0x00000200  // TimerB stall enable
#define TIMER_CTL_TBEN          0x00000100  // TimerB enable
#define TIMER_CTL_TAPWML        0x00000040  // TimerA PWM output level invert
#define TIMER_CTL_TAOTE         0x00000020  // TimerA output trigger enable
#define TIMER_CTL_RTCEN         0x00000010  // RTC counter enable
#define TIMER_CTL_TAEVENT_M     0x0000000C  // GPTM TimerA Event Mode.
#define TIMER_CTL_TAEVENT_POS   0x00000000  // TimerA event mode - pos edge
#define TIMER_CTL_TAEVENT_NEG   0x00000004  // TimerA event mode - neg edge
#define TIMER_CTL_TAEVENT_BOTH  0x0000000C  // TimerA event mode - both edges
#define TIMER_CTL_TASTALL       0x00000002  // TimerA stall enable
#define TIMER_CTL_TAEN          0x00000001  // TimerA enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_IMR register.
//
//*****************************************************************************
#define TIMER_IMR_TBMIM         0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Mask.
#define TIMER_IMR_CBEIM         0x00000400  // CaptureB event interrupt mask
#define TIMER_IMR_CBMIM         0x00000200  // CaptureB match interrupt mask
#define TIMER_IMR_TBTOIM        0x00000100  // TimerB time out interrupt mask
#define TIMER_IMR_TAMIM         0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Mask.
#define TIMER_IMR_RTCIM         0x00000008  // RTC interrupt mask
#define TIMER_IMR_CAEIM         0x00000004  // CaptureA event interrupt mask
#define TIMER_IMR_CAMIM         0x00000002  // CaptureA match interrupt mask
#define TIMER_IMR_TATOIM        0x00000001  // TimerA time out interrupt mask

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_RIS register.
//
//*****************************************************************************
#define TIMER_RIS_TBMRIS        0x00000800  // GPTM Timer B Mode Match Raw
                                            // Interrupt.
#define TIMER_RIS_CBERIS        0x00000400  // CaptureB event raw int status
#define TIMER_RIS_CBMRIS        0x00000200  // CaptureB match raw int status
#define TIMER_RIS_TBTORIS       0x00000100  // TimerB time out raw int status
#define TIMER_RIS_TAMRIS        0x00000010  // GPTM Timer A Mode Match Raw
                                            // Interrupt.
#define TIMER_RIS_RTCRIS        0x00000008  // RTC raw int status
#define TIMER_RIS_CAERIS        0x00000004  // CaptureA event raw int status
#define TIMER_RIS_CAMRIS        0x00000002  // CaptureA match raw int status
#define TIMER_RIS_TATORIS       0x00000001  // TimerA time out raw int status

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_ICR register.
//
//*****************************************************************************
#define TIMER_ICR_TBMCINT       0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Clear.
#define TIMER_ICR_CBECINT       0x00000400  // CaptureB event interrupt clear
#define TIMER_ICR_CBMCINT       0x00000200  // CaptureB match interrupt clear
#define TIMER_ICR_TBTOCINT      0x00000100  // TimerB time out interrupt clear
#define TIMER_ICR_TAMCINT       0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Clear.
#define TIMER_ICR_RTCCINT       0x00000008  // RTC interrupt clear
#define TIMER_ICR_CAECINT       0x00000004  // CaptureA event interrupt clear
#define TIMER_ICR_CAMCINT       0x00000002  // CaptureA match interrupt clear
#define TIMER_ICR_TATOCINT      0x00000001  // TimerA time out interrupt clear

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TAILR register.
//
//*****************************************************************************
#define TIMER_TAILR_TAILRH_M    0xFFFF0000  // GPTM TimerA Interval Load
                                            // Register High.
#define TIMER_TAILR_TAILRL_M    0x0000FFFF  // GPTM TimerA Interval Load
                                            // Register Low.
#define TIMER_TAILR_TAILRH_S    16
#define TIMER_TAILR_TAILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TBILR register.
//
//*****************************************************************************
#define TIMER_TBILR_TBILRL_M    0x0000FFFF  // GPTM TimerB Interval Load
                                            // Register.
#define TIMER_TBILR_TBILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TAMATCHR register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMRH_M  0xFFFF0000  // GPTM TimerA Match Register High.
#define TIMER_TAMATCHR_TAMRL_M  0x0000FFFF  // GPTM TimerA Match Register Low.
#define TIMER_TAMATCHR_TAMRH_S  16
#define TIMER_TAMATCHR_TAMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TBMATCHR register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMRL_M  0x0000FFFF  // GPTM TimerB Match Register Low.
#define TIMER_TBMATCHR_TBMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TAR register.
//
//*****************************************************************************
#define TIMER_TAR_TARH_M        0xFFFF0000  // GPTM TimerA Register High.
#define TIMER_TAR_TARL_M        0x0000FFFF  // GPTM TimerA Register Low.
#define TIMER_TAR_TARH_S        16
#define TIMER_TAR_TARL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_TBR register.
//
//*****************************************************************************
#define TIMER_TBR_TBRL_M        0x0000FFFF  // GPTM TimerB.
#define TIMER_TBR_TBRL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMR register.
//
//*****************************************************************************
#define TIMER_TAMR_TASNAPS      0x00000080  // GPTM Timer A Snap-Shot Mode.
#define TIMER_TAMR_TAWOT        0x00000040  // GPTM Timer A Wait-on-Trigger.
#define TIMER_TAMR_TAMIE        0x00000020  // GPTM Timer A Match Interrupt
                                            // Enable.
#define TIMER_TAMR_TACDIR       0x00000010  // GPTM Timer A Count Direction.
#define TIMER_TAMR_TAAMS        0x00000008  // GPTM TimerA Alternate Mode
                                            // Select.
#define TIMER_TAMR_TACMR        0x00000004  // GPTM TimerA Capture Mode.
#define TIMER_TAMR_TAMR_M       0x00000003  // GPTM TimerA Mode.
#define TIMER_TAMR_TAMR_1_SHOT  0x00000001  // One-Shot Timer mode.
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode.
#define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMR register.
//
//*****************************************************************************
#define TIMER_TBMR_TBSNAPS      0x00000080  // GPTM Timer B Snap-Shot Mode.
#define TIMER_TBMR_TBWOT        0x00000040  // GPTM Timer B Wait-on-Trigger.
#define TIMER_TBMR_TBMIE        0x00000020  // GPTM Timer B Match Interrupt
                                            // Enable.
#define TIMER_TBMR_TBCDIR       0x00000010  // GPTM Timer B Count Direction.
#define TIMER_TBMR_TBAMS        0x00000008  // GPTM TimerB Alternate Mode
                                            // Select.
#define TIMER_TBMR_TBCMR        0x00000004  // GPTM TimerB Capture Mode.
#define TIMER_TBMR_TBMR_M       0x00000003  // GPTM TimerB Mode.
#define TIMER_TBMR_TBMR_1_SHOT  0x00000001  // One-Shot Timer mode.
#define TIMER_TBMR_TBMR_PERIOD  0x00000002  // Periodic Timer mode.
#define TIMER_TBMR_TBMR_CAP     0x00000003  // Capture mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_MIS register.
//
//*****************************************************************************
#define TIMER_MIS_TBMMIS        0x00000800  // GPTM Timer B Mode Match Masked
                                            // Interrupt.
#define TIMER_MIS_CBEMIS        0x00000400  // GPTM CaptureB Event Masked
                                            // Interrupt.
#define TIMER_MIS_CBMMIS        0x00000200  // GPTM CaptureB Match Masked
                                            // Interrupt.
#define TIMER_MIS_TBTOMIS       0x00000100  // GPTM TimerB Time-Out Masked
                                            // Interrupt.
#define TIMER_MIS_TAMMIS        0x00000010  // GPTM Timer A Mode Match Masked
                                            // Interrupt.
#define TIMER_MIS_RTCMIS        0x00000008  // GPTM RTC Masked Interrupt.
#define TIMER_MIS_CAEMIS        0x00000004  // GPTM CaptureA Event Masked
                                            // Interrupt.
#define TIMER_MIS_CAMMIS        0x00000002  // GPTM CaptureA Match Masked
                                            // Interrupt.
#define TIMER_MIS_TATOMIS       0x00000001  // GPTM TimerA Time-Out Masked
                                            // Interrupt.

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPR register.
//
//*****************************************************************************
#define TIMER_TAPR_TAPSR_M      0x000000FF  // GPTM TimerA Prescale.
#define TIMER_TAPR_TAPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPR register.
//
//*****************************************************************************
#define TIMER_TBPR_TBPSR_M      0x000000FF  // GPTM TimerB Prescale.
#define TIMER_TBPR_TBPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPMR register.
//
//*****************************************************************************
#define TIMER_TAPMR_TAPSMR_M    0x000000FF  // GPTM TimerA Prescale Match.
#define TIMER_TAPMR_TAPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPMR register.
//
//*****************************************************************************
#define TIMER_TBPMR_TBPSMR_M    0x000000FF  // GPTM TimerB Prescale Match.
#define TIMER_TBPMR_TBPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAV register.
//
//*****************************************************************************
#define TIMER_TAV_TAVH_M        0xFFFF0000  // GPTM Timer A Value High.
#define TIMER_TAV_TAVL_M        0x0000FFFF  // GPTM Timer A Register Low.
#define TIMER_TAV_TAVH_S        16
#define TIMER_TAV_TAVL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBV register.
//
//*****************************************************************************
#define TIMER_TBV_TBVL_M        0x0000FFFF  // GPTM Timer B Register.
#define TIMER_TBV_TBVL_S        0

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the reset values of the timer
// registers.
//
//*****************************************************************************
#define TIMER_RV_TAILR          0xFFFFFFFF  // TimerA interval load reg RV
#define TIMER_RV_TAR            0xFFFFFFFF  // TimerA register RV
#define TIMER_RV_TAMATCHR       0xFFFFFFFF  // TimerA match register RV
#define TIMER_RV_TBILR          0x0000FFFF  // TimerB interval load reg RV
#define TIMER_RV_TBMATCHR       0x0000FFFF  // TimerB match register RV
#define TIMER_RV_TBR            0x0000FFFF  // TimerB register RV
#define TIMER_RV_TAPR           0x00000000  // TimerA prescale register RV
#define TIMER_RV_CFG            0x00000000  // Configuration register RV
#define TIMER_RV_TBPMR          0x00000000  // TimerB prescale match regi RV
#define TIMER_RV_TAPMR          0x00000000  // TimerA prescale match reg RV
#define TIMER_RV_CTL            0x00000000  // Control register RV
#define TIMER_RV_ICR            0x00000000  // Interrupt clear register RV
#define TIMER_RV_TBMR           0x00000000  // TimerB mode register RV
#define TIMER_RV_MIS            0x00000000  // Masked interrupt status reg RV
#define TIMER_RV_RIS            0x00000000  // Interrupt status register RV
#define TIMER_RV_TBPR           0x00000000  // TimerB prescale register RV
#define TIMER_RV_IMR            0x00000000  // Interrupt mask register RV
#define TIMER_RV_TAMR           0x00000000  // TimerA mode register RV

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_CFG
// register.
//
//*****************************************************************************
#define TIMER_CFG_CFG_MSK       0x00000007  // Configuration options mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnMR
// register.
//
//*****************************************************************************
#define TIMER_TNMR_TNAMS        0x00000008  // Alternate mode select
#define TIMER_TNMR_TNCMR        0x00000004  // Capture mode - count or time
#define TIMER_TNMR_TNTMR_MSK    0x00000003  // Timer mode mask
#define TIMER_TNMR_TNTMR_1_SHOT 0x00000001  // Mode - one shot
#define TIMER_TNMR_TNTMR_PERIOD 0x00000002  // Mode - periodic
#define TIMER_TNMR_TNTMR_CAP    0x00000003  // Mode - capture

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_CTL
// register.
//
//*****************************************************************************
#define TIMER_CTL_TBEVENT_MSK   0x00000C00  // TimerB event mode mask
#define TIMER_CTL_TAEVENT_MSK   0x0000000C  // TimerA event mode mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_MIS
// register.
//
//*****************************************************************************
#define TIMER_RIS_CBEMIS        0x00000400  // CaptureB event masked int status
#define TIMER_RIS_CBMMIS        0x00000200  // CaptureB match masked int status
#define TIMER_RIS_TBTOMIS       0x00000100  // TimerB time out masked int stat
#define TIMER_RIS_RTCMIS        0x00000008  // RTC masked int status
#define TIMER_RIS_CAEMIS        0x00000004  // CaptureA event masked int status
#define TIMER_RIS_CAMMIS        0x00000002  // CaptureA match masked int status
#define TIMER_RIS_TATOMIS       0x00000001  // TimerA time out masked int stat

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TAILR
// register.
//
//*****************************************************************************
#define TIMER_TAILR_TAILRH      0xFFFF0000  // TimerB load val in 32 bit mode
#define TIMER_TAILR_TAILRL      0x0000FFFF  // TimerA interval load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TBILR
// register.
//
//*****************************************************************************
#define TIMER_TBILR_TBILRL      0x0000FFFF  // TimerB interval load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the
// TIMER_TAMATCHR register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMRH    0xFFFF0000  // TimerB match val in 32 bit mode
#define TIMER_TAMATCHR_TAMRL    0x0000FFFF  // TimerA match value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the
// TIMER_TBMATCHR register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMRL    0x0000FFFF  // TimerB match load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnPR
// register.
//
//*****************************************************************************
#define TIMER_TNPR_TNPSR        0x000000FF  // TimerN prescale value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnPMR
// register.
//
//*****************************************************************************
#define TIMER_TNPMR_TNPSMR      0x000000FF  // TimerN prescale match value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TAR
// register.
//
//*****************************************************************************
#define TIMER_TAR_TARH          0xFFFF0000  // TimerB val in 32 bit mode
#define TIMER_TAR_TARL          0x0000FFFF  // TimerA value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TBR
// register.
//
//*****************************************************************************
#define TIMER_TBR_TBRL          0x0000FFFF  // TimerB value

#endif

#endif // __HW_TIMER_H__
