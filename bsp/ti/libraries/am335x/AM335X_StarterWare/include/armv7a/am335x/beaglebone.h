/**
 * \file   beaglebone.h
 *
 * \brief  This file contains prototype declarations of functions which 
 *         performs EVM configurations.
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


#ifndef _BEALGEBONE_H_
#define _BEAGLEBONE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                    INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define CTRL_NUM_IOPAD_REGS                 (211)

#define BBB_BOARD_NAME                      ("A335BON")
#define BBB_A1_VERSION                      ("00A1")
#define BBB_A2_VERSION                      ("00A2")
#define BBB_A3_VERSION                      ("00A3")
#define BBB_A5_VERSION                      ("00A5")
#define BBB_A6_VERSION                      ("00A6")
#define BOARD_ID_BBB_A1                     (0x1)
#define BOARD_ID_BBB_A2                     (0x2)
#define BOARD_ID_BBB_A3                     (0x3)
#define BOARD_ID_BBB_A5                     (0x4)
#define BOARD_ID_BBB_A6                     (0x5)

/*
** Structure to map selection of IO Pad for power down configuration
*/
typedef struct ioPadMap {
    unsigned int ioPad;
    unsigned int sel;
}tIOPadMap;

/*
** Structure to store the control register context. More registers
** can be added to this if need to be saved.
*/
typedef struct ctrlRegContext {
    unsigned int pwmssctrl;
    unsigned int gmiisel;
    tIOPadMap ioPadMap[CTRL_NUM_IOPAD_REGS];
}CTRLREGCONTEXT;

/*****************************************************************************
**                    FUNCTION PROTOTYPES
*****************************************************************************/

extern unsigned int BoardInfoCheck(unsigned char *boardId,
                                   unsigned char *boardVer);
extern void ControlRegContextSave(CTRLREGCONTEXT *contextPtr);
extern void ControlRegContextRestore(CTRLREGCONTEXT *contextPtr);
extern void GPIO1ModuleClkConfig(void);
extern void GPIO1Pin23PinMuxSetup(void);
extern void GPIO0ModuleClkConfig(void);
extern void UART0ModuleClkConfig(void);
extern void UARTPinMuxSetup(unsigned int instanceNum);
extern void CPSWPinMuxSetup(void);
extern void CPSWClkEnable(void);
extern unsigned int RTCRevisionInfoGet(void);
extern void EDMAModuleClkConfig(void);
extern void EVMMACAddrGet(unsigned int addrIdx, unsigned char *macAddr);
extern void WatchdogTimer1ModuleClkConfig(void);
extern void DMTimer2ModuleClkConfig(void);
extern void DMTimer3ModuleClkConfig(void);
extern void DMTimer4ModuleClkConfig(void);
extern void DMTimer6ModuleClkConfig(void);
extern void DMTimer7ModuleClkConfig(void);
extern void DMTimer1msModuleClkConfig(unsigned int clkselect);
extern void EVMPortMIIModeSelect(void);
extern void RTCModuleClkConfig(void);
extern void HSMMCSDModuleClkConfig(void);
extern void HSMMCSDPinMuxSetup(void);
extern void I2C0ModuleClkConfig(void);
extern void I2C1ModuleClkConfig(void);
extern void I2CPinMuxSetup(unsigned int instance);
extern void GpioPinMuxSetup(unsigned int offsetAddr,
                            unsigned int padConfValue);
extern void IOPadContextSave(CTRLREGCONTEXT *contextPtr, unsigned int ioPadOff);
extern void IOPadContextRestore(CTRLREGCONTEXT *contextPtr,
                                unsigned int ioPadOff);
void IOPadConfigure(unsigned int ioPadOff, unsigned int ioPadValue);
void IOPadSelConfigure(CTRLREGCONTEXT *contextPtr, unsigned int ioPadValue);
void IOPadSel(CTRLREGCONTEXT *contextPtr, unsigned int ioPadOff,
              unsigned int ioPadSel);
#ifdef __cplusplus
}
#endif

#endif

/******************************** End of file *******************************/
