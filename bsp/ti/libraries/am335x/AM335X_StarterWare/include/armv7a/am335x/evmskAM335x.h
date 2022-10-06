/**
 * \file   evmskAM335x.h
 *
 * \brief  This file contains prototype declarations of functions which 
 *         performs EVM configurations for EVM-SK.
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


#ifndef _EVM_AM335X_H_
#define _EVM_AM335X_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                    INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define CTRL_NUM_IOPAD_REGS                 (211)

#define PRINT_WRG(x)                        UARTPuts ("\r\n|WARNING|", -1);\
                                            UARTPuts (x, -1); \
                                            UARTPuts ("|\r\n", -1);            
                                 
#define PRINT_ERR(x)                        UARTPuts ("\r\n|ERROR|", -1); \
                                            UARTPuts (x, -1); \
                                            UARTPuts ("|\r\n", -1);                                                                   
                                 
#define EVMSK_BOARD_NAME                    ("A335_S")
#define EVMSK_1_2B_VERSION                  ("1.2B")
#define EVMSK_1_3A_VERSION                  ("1.3A")
#define BOARD_ID_EVMSK_1_2B                 (0x1)
#define BOARD_ID_EVMSK_1_3A                 (0x2)

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
extern void LCDBackLightEnable(void);
extern void LCDBackLightDisable(void);
extern unsigned int LCDPinMuxSetup(void);
extern void TSCADCPinMuxSetUp(void);
extern void GPIO1Pin29PinMuxSetup(void);
extern void GPIO1Pin4PinMuxSetup(void);
extern void LCDModuleClkConfig(void);
extern void I2C1ModuleClkConfig(void);
extern void I2C0ModuleClkConfig(void);
extern void GPIO0ModuleClkConfig(void);
extern void GPIO1ModuleClkConfig(void);
extern void TSCADCModuleClkConfig(void);
extern void DMTimer2ModuleClkConfig(void);
extern void DMTimer3ModuleClkConfig(void);
extern void DMTimer4ModuleClkConfig(void);
extern void DMTimer6ModuleClkConfig(void);
extern void DMTimer7ModuleClkConfig(void);
extern void I2CPinMuxSetup(unsigned int instance);
extern void UARTPinMuxSetup(unsigned int instanceNum);
extern void UART0ModuleClkConfig(void);
extern void EVMMACAddrGet(unsigned int addrIdx, unsigned char *macAddr);
extern void EVMPortRGMIIModeSelect(void);
extern void CPSWClkEnable(void);
extern void WatchdogTimer1ModuleClkConfig(void);
extern void McASP1PinMuxSetup(void);
extern void McASP1ModuleClkConfig(void);
extern void EDMAModuleClkConfig(void);
extern unsigned int EDMA3CrossBarChannelMap(unsigned int baseAdd, 
                                     unsigned int crossBarEvent,
                                     unsigned int Channel);
extern unsigned int EDMAVersionGet(void);
extern void UPDNPinControl(void);
extern void CPSWPinMuxSetup(void);
extern void ControlRegContextSave(CTRLREGCONTEXT *contextPtr);
extern void ControlRegContextRestore(CTRLREGCONTEXT *contextPtr);
extern void HSMMCSDModuleClkConfig(void);
extern void RTCModuleClkConfig(void);
extern void ECAPPinMuxSetup(unsigned int instanceNum);
extern void GPIO0Pin2PinMuxSetup(void);
extern void GPIO1Pin2PinMuxSetup(void);
extern void GpioPinMuxSetup(unsigned int offsetAddr,
                            unsigned int padConfValue);
extern unsigned int RtcVersionGet(void);
extern void HSMMCSDPinMuxSetup(void);
extern void USB0ModuleClkConfig(void);
extern void GPIO3ModuleClkConfig(void);
extern void USBModuleClkEnable(unsigned int ulIndex, unsigned int ulBase);
extern void USBModuleClkDisable(unsigned int ulIndex, unsigned int ulBase);

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

