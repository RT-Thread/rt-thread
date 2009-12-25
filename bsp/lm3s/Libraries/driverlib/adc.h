//*****************************************************************************
//
// adc.h - ADC headers for using the ADC driver functions.
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
// This is part of revision 4694 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __ADC_H__
#define __ADC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Values that can be passed to ADCSequenceConfigure as the ulTrigger
// parameter.
//
//*****************************************************************************
#define ADC_TRIGGER_PROCESSOR   0x00000000  // Processor event
#define ADC_TRIGGER_COMP0       0x00000001  // Analog comparator 0 event
#define ADC_TRIGGER_COMP1       0x00000002  // Analog comparator 1 event
#define ADC_TRIGGER_COMP2       0x00000003  // Analog comparator 2 event
#define ADC_TRIGGER_EXTERNAL    0x00000004  // External event
#define ADC_TRIGGER_TIMER       0x00000005  // Timer event
#define ADC_TRIGGER_PWM0        0x00000006  // PWM0 event
#define ADC_TRIGGER_PWM1        0x00000007  // PWM1 event
#define ADC_TRIGGER_PWM2        0x00000008  // PWM2 event
#define ADC_TRIGGER_ALWAYS      0x0000000F  // Always event

//*****************************************************************************
//
// Values that can be passed to ADCSequenceStepConfigure as the ulConfig
// parameter.
//
//*****************************************************************************
#define ADC_CTL_TS              0x00000080  // Temperature sensor select
#define ADC_CTL_IE              0x00000040  // Interrupt enable
#define ADC_CTL_END             0x00000020  // Sequence end select
#define ADC_CTL_D               0x00000010  // Differential select
#define ADC_CTL_CH0             0x00000000  // Input channel 0
#define ADC_CTL_CH1             0x00000001  // Input channel 1
#define ADC_CTL_CH2             0x00000002  // Input channel 2
#define ADC_CTL_CH3             0x00000003  // Input channel 3
#define ADC_CTL_CH4             0x00000004  // Input channel 4
#define ADC_CTL_CH5             0x00000005  // Input channel 5
#define ADC_CTL_CH6             0x00000006  // Input channel 6
#define ADC_CTL_CH7             0x00000007  // Input channel 7
#define ADC_CTL_CH8             0x00000008  // Input channel 8
#define ADC_CTL_CH9             0x00000009  // Input channel 9
#define ADC_CTL_CH10            0x0000000A  // Input channel 10
#define ADC_CTL_CH11            0x0000000B  // Input channel 11
#define ADC_CTL_CH12            0x0000000C  // Input channel 12
#define ADC_CTL_CH13            0x0000000D  // Input channel 13
#define ADC_CTL_CH14            0x0000000E  // Input channel 14
#define ADC_CTL_CH15            0x0000000F  // Input channel 15

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void ADCIntRegister(unsigned long ulBase, unsigned long ulSequenceNum,
                           void (*pfnHandler)(void));
extern void ADCIntUnregister(unsigned long ulBase,
                             unsigned long ulSequenceNum);
extern void ADCIntDisable(unsigned long ulBase, unsigned long ulSequenceNum);
extern void ADCIntEnable(unsigned long ulBase, unsigned long ulSequenceNum);
extern unsigned long ADCIntStatus(unsigned long ulBase,
                                  unsigned long ulSequenceNum,
                                  tBoolean bMasked);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulSequenceNum);
extern void ADCSequenceEnable(unsigned long ulBase,
                              unsigned long ulSequenceNum);
extern void ADCSequenceDisable(unsigned long ulBase,
                               unsigned long ulSequenceNum);
extern void ADCSequenceConfigure(unsigned long ulBase,
                                 unsigned long ulSequenceNum,
                                 unsigned long ulTrigger,
                                 unsigned long ulPriority);
extern void ADCSequenceStepConfigure(unsigned long ulBase,
                                     unsigned long ulSequenceNum,
                                     unsigned long ulStep,
                                     unsigned long ulConfig);
extern long ADCSequenceOverflow(unsigned long ulBase,
                                unsigned long ulSequenceNum);
extern void ADCSequenceOverflowClear(unsigned long ulBase,
                                     unsigned long ulSequenceNum);
extern long ADCSequenceUnderflow(unsigned long ulBase,
                                 unsigned long ulSequenceNum);
extern void ADCSequenceUnderflowClear(unsigned long ulBase,
                                      unsigned long ulSequenceNum);
extern long ADCSequenceDataGet(unsigned long ulBase,
                               unsigned long ulSequenceNum,
                               unsigned long *pulBuffer);
extern void ADCProcessorTrigger(unsigned long ulBase,
                                unsigned long ulSequenceNum);
extern void ADCSoftwareOversampleConfigure(unsigned long ulBase,
                                           unsigned long ulSequenceNum,
                                           unsigned long ulFactor);
extern void ADCSoftwareOversampleStepConfigure(unsigned long ulBase,
                                               unsigned long ulSequenceNum,
                                               unsigned long ulStep,
                                               unsigned long ulConfig);
extern void ADCSoftwareOversampleDataGet(unsigned long ulBase,
                                         unsigned long ulSequenceNum,
                                         unsigned long *pulBuffer,
                                         unsigned long ulCount);
extern void ADCHardwareOversampleConfigure(unsigned long ulBase,
                                           unsigned long ulFactor);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __ADC_H__
