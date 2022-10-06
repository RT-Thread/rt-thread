/**
 * \file    gpio_v2.h
 *
 * \brief   This file contains the prototypes of the APIs present in the
 *          device abstraction layer file of GPIO belonging to AM335X SoC.
 *          This also contains some related macros.
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

#ifndef  _GPIO_V2_H_
#define  _GPIO_V2_H_

#include "hw_gpio_v2.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                       MACRO DEFINITIONS                                   
*****************************************************************************/

/* Values used to configure the direction of GPIO pins. */
#define GPIO_DIR_INPUT                   (GPIO_OE_OUTPUTEN_DISABLED)
#define GPIO_DIR_OUTPUT                  (GPIO_OE_OUTPUTEN_ENABLED)

/* Values helping to decide the value on a GPIO pin. */
#define GPIO_PIN_LOW                     (0x0)
#define GPIO_PIN_HIGH                    (0x1)

/* Values denoting the Interrupt Line number to be used. */
#define GPIO_INT_LINE_1                  (0x0)
#define GPIO_INT_LINE_2                  (0x1)

/* Values denoting the Smart Wakeup Interrupt Line to be used. */
#define GPIO_INT_SWAKEUP_LINE_1          (0x0)
#define GPIO_INT_SWAKEUP_LINE_2          (0x1)

/*
** Values used to enable/disable interrupt generation due to level
** detection on an input GPIO pin.
*/
#define GPIO_INT_TYPE_NO_LEVEL           (0x01)
#define GPIO_INT_TYPE_LEVEL_LOW          (0x04)
#define GPIO_INT_TYPE_LEVEL_HIGH         (0x08)
#define GPIO_INT_TYPE_BOTH_LEVEL         (0x0C)

/*
** Values used to enable/disable interrupt generation due to edge
** detection on an input GPIO pin.
*/
#define GPIO_INT_TYPE_NO_EDGE            (0x80)
#define GPIO_INT_TYPE_RISE_EDGE          (0x10)
#define GPIO_INT_TYPE_FALL_EDGE          (0x20)
#define GPIO_INT_TYPE_BOTH_EDGE          (0x30)

/* Values used for Idle Mode configurations. */
#define GPIO_IDLE_MODE_FORCE_IDLE        (GPIO_SYSCONFIG_IDLEMODE_FORCEIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_NO_IDLE           (GPIO_SYSCONFIG_IDLEMODE_NOIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_SMART_IDLE        (GPIO_SYSCONFIG_IDLEMODE_SMARTIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_SMART_IDLE_WAKEUP (GPIO_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)

/* Values used to enable/disable Auto-Idle mode. */
#define GPIO_AUTO_IDLE_MODE_ENABLE       (GPIO_SYSCONFIG_AUTOIDLE_AUTOMATIC)
#define GPIO_AUTO_IDLE_MODE_DISABLE      (GPIO_SYSCONFIG_AUTOIDLE_FREERUN)

/* Values used to configure the Gating Ratio. */
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_1  (GPIO_CTRL_GATINGRATIO_N_1 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)    
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_2  (GPIO_CTRL_GATINGRATIO_N_2 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_4  (GPIO_CTRL_GATINGRATIO_N_4 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_8  (GPIO_CTRL_GATINGRATIO_N_8 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)

/* Values used to enable/disable Debouncing feature for an input pin. */
#define GPIO_DEBOUNCE_FUNC_ENABLE        (GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_DEBOUNCE)
#define GPIO_DEBOUNCE_FUNC_DISABLE       (GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_NODEBOUNCE)

/*
** Structure to store the GPIO context
*/
typedef struct gpioContext{
    unsigned int ctrl;
    unsigned int dir;
    unsigned int data;
}GPIOCONTEXT;


/*****************************************************************************
**                       FUNCTION PROTOTYPES                                   
*****************************************************************************/

extern void GPIOModuleReset(unsigned int baseAdd);
extern void GPIOModuleEnable(unsigned int baseAdd);
extern void GPIOModuleDisable(unsigned int baseAdd);
extern void GPIODirModeSet(unsigned int baseAdd,
                           unsigned int pinNumber,
                           unsigned int pinDirection);
extern unsigned int GPIODirModeGet(unsigned int baseAdd,
                                   unsigned int pinNumber);
extern void GPIOPinWrite(unsigned int baseAdd,
                         unsigned int pinNumber,
                         unsigned int pinValue);
extern unsigned int GPIOPinRead(unsigned int baseAdd,
                                unsigned int pinNumber);
extern void GPIOMultiplePinsWrite(unsigned int baseAdd,
                                  unsigned int setMask,
                                  unsigned int clrMask);
extern unsigned int GPIOMultiplePinsRead(unsigned int baseAdd,
                                         unsigned int readMask);
extern void GPIOPinIntEnable(unsigned int baseAdd,
                             unsigned int intLine,
                             unsigned int pinNumber);

extern void GPIOPinIntDisable(unsigned int baseAdd,
                              unsigned int intLine,
                              unsigned int pinNumber);
extern void GPIOIntTypeSet(unsigned int baseAdd,
                           unsigned int pinNumber,
                           unsigned int eventType);
extern unsigned int GPIOIntTypeGet(unsigned int baseAdd,
                                   unsigned int pinNumber);
extern unsigned int GPIOPinIntStatus(unsigned int baseAdd,
                                     unsigned int intLine,
                                     unsigned int pinNumber);
extern void GPIOPinIntClear(unsigned int baseAdd,
                            unsigned int intLine,
                            unsigned int pinNumber);
extern unsigned int GPIORawIntStatus(unsigned int baseAdd,
                                     unsigned int intLine,
                                     unsigned int readMask);
extern void GPIOTriggerPinInt(unsigned int baseAdd,
                              unsigned int intLine,
                              unsigned int pinNumber);
extern void GPIOWakeupGlobalEnable(unsigned int baseAdd);
extern void GPIOWakeupGlobalDisable(unsigned int baseAdd);
extern void GPIOPinIntWakeUpEnable(unsigned int baseAdd,
                                   unsigned int intLine,
                                   unsigned int pinNumber);
extern void GPIOPinIntWakeUpDisable(unsigned int baseAdd,
                                    unsigned int intLine,
                                    unsigned int pinNumber);
extern void GPIOAutoIdleModeControl(unsigned int baseAdd,
                                    unsigned int modeFlag);
extern void GPIOIdleModeConfigure(unsigned int baseAdd,
                                  unsigned int modeFlag);
extern void GPIOGatingRatioConfigure(unsigned int baseAdd,
                                     unsigned int configFlag);

extern void GPIODebounceFuncControl(unsigned int baseAdd,
                                    unsigned int pinNumber,
                                    unsigned int controlFlag);
extern void GPIODebounceTimeConfig(unsigned int baseAdd,
                                   unsigned int debounceTime);
extern unsigned int GPIORevisionInfoGet(unsigned int baseAdd);
extern void gpioContextSave(unsigned int baseAdd, GPIOCONTEXT *contextPtr);
extern void gpioContextRestore(unsigned int baseAdd, GPIOCONTEXT *contextPtr);


#ifdef __cplusplus
}
#endif

#endif

/********************************* End Of File ******************************/
