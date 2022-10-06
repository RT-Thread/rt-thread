/**
 * \file     gpio.h
 *
 * \brief    This file contains the function prototypes for the device
 *           abstraction layer for GPIO and some related macros.
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
 
#ifndef      __GPIO_H__
#define      __GPIO_H__

#include "hw_gpio.h"
#ifdef __cplusplus
extern "C" {
#endif

/************* GPIO pin directions.************************************/

/* This is used to configure a GPIO pin as an input pin. */
#define GPIO_DIR_INPUT                1
/* This is used to configure a GPIO pin as an output pin.*/
#define GPIO_DIR_OUTPUT               0

/******************Interrupt Trigger Level Types.**********************/

/* Disable interrupt generation on both the edges of a signal on a pin.*/
#define GPIO_INT_TYPE_NOEDGE          0

/* Enable interrupt generation on falling edge of a signal on a pin.*/
#define GPIO_INT_TYPE_FALLEDGE        1

/* Enable interrupt generation on the rising edge of a signal on a pin.*/
#define GPIO_INT_TYPE_RISEDGE         2

/* Enable interrupt generation on both the edges of a signal on a pin.*/
#define GPIO_INT_TYPE_BOTHEDGE        3

/*****************Interrupt Pending status.*****************************/

/* This signifies interrupt status as cleared.*/
#define GPIO_INT_NOPEND               0

/* This signifies interrupt status as pending.*/
#define GPIO_INT_PEND                 1

/*****************Write values to a pin.********************************/

/* This is used to write a logic 0 to a pin.*/
#define GPIO_PIN_LOW                  0

/* This is used to write a logic 1 to a pin.*/
#define GPIO_PIN_HIGH                 1


/*****************Bit Mask values for banks.***************************/
/* 
** The following macros are used by the application while invoking
** the function 'GPIOBankPinsWrite'. Any one or a combination of 
** the below macros is passed as 'setPins' and 'clrPins' to 
** 'GPIOBankPinsWrite'.
*/
#define GPIO_BANK_PIN_0              GPIO_DIR_DIR0
#define GPIO_BANK_PIN_1              GPIO_DIR_DIR1
#define GPIO_BANK_PIN_2              GPIO_DIR_DIR2
#define GPIO_BANK_PIN_3              GPIO_DIR_DIR3
#define GPIO_BANK_PIN_4              GPIO_DIR_DIR4
#define GPIO_BANK_PIN_5              GPIO_DIR_DIR5
#define GPIO_BANK_PIN_6              GPIO_DIR_DIR6
#define GPIO_BANK_PIN_7              GPIO_DIR_DIR7
#define GPIO_BANK_PIN_8              GPIO_DIR_DIR8
#define GPIO_BANK_PIN_9              GPIO_DIR_DIR9
#define GPIO_BANK_PIN_10             GPIO_DIR_DIR10
#define GPIO_BANK_PIN_11             GPIO_DIR_DIR11
#define GPIO_BANK_PIN_12             GPIO_DIR_DIR12
#define GPIO_BANK_PIN_13             GPIO_DIR_DIR13
#define GPIO_BANK_PIN_14             GPIO_DIR_DIR14
#define GPIO_BANK_PIN_15             GPIO_DIR_DIR15



/*****************************************************************************
**                   FUNCTION DECLARATIONS                                   
*****************************************************************************/


void GPIODirModeSet(unsigned int baseAdd, unsigned int pinNumber,
                    unsigned int pinDir);
unsigned int GPIODirModeGet(unsigned int baseAdd, unsigned int pinNumber);
void GPIOPinWrite(unsigned int baseAdd, unsigned int pinNumber,
                  unsigned int bitValue);
int GPIOPinRead(unsigned int baseAdd, unsigned int pinNumber);
void GPIOIntTypeSet(unsigned int baseAdd, unsigned int pinNumber,
                    unsigned int intType);
unsigned int GPIOIntTypeGet(unsigned int baseAdd, unsigned int pinNumber);
unsigned int GPIOPinIntStatus(unsigned int baseAdd, unsigned int pinNumber);
void GPIOPinIntClear(unsigned int baseAdd, unsigned int pinNumber);
void GPIOBankIntEnable(unsigned int baseAdd, unsigned int bankNumber);
void GPIOBankIntDisable(unsigned int baseAdd, unsigned int bankNumber);
void GPIOBankPinsWrite(unsigned int baseAdd, unsigned int bankNumber,
                       unsigned int setPins, unsigned int clrPins);


#ifdef __cplusplus
}
#endif
#endif
















