/**
 *  \file       hsi2c.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for high speed I2C. It also contains some
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

#ifndef _I2C_H_
#define _I2C_H_

#include "hw_hsi2c.h"
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/*
** Values that can be passed to  I2CMasterControl API as cmd to configure mode
** of operation of I2C
*/

#define     I2C_CFG_MST_TX              I2C_CON_TRX | I2C_CON_MST
#define     I2C_CFG_MST_RX              I2C_CON_MST
#define     I2C_CFG_STOP                I2C_CON_STP
#define     I2C_CFG_N0RMAL_MODE         (0 << I2C_CON_STB_SHIFT) 
#define     I2C_CFG_SRT_BYTE_MODE       I2C_CON_STB
#define     I2C_CFG_7BIT_SLAVE_ADDR     (0 << I2C_CON_XSA_SHIFT) 
#define     I2C_CFG_10BIT_SLAVE_ADDR    I2C_CON_XSA
#define     I2C_CFG_10BIT_OWN_ADDR_0    I2C_CON_XOA0
#define     I2C_CFG_10BIT_OWN_ADDR_1    I2C_CON_XOA1
#define     I2C_CFG_10BIT_OWN_ADDR_2    I2C_CON_XOA2
#define     I2C_CFG_10BIT_OWN_ADDR_3    I2C_CON_XOA3
#define     I2C_CFG_7BIT_OWN_ADDR_0     (0 << I2C_CON_XOA0_SHIFT)
#define     I2C_CFG_7BIT_OWN_ADDR_1     (0 << I2C_CON_XOA1_SHIFT)
#define     I2C_CFG_7BIT_OWN_ADDR_2     (0 << I2C_CON_XOA2_SHIFT
#define     I2C_CFG_7BIT_OWN_ADDR_3     (0 << I2C_CON_XOA3_SHIFT)

/****************************************************************************/
/*
** Values that can be passed to  I2CMasterIntEnableEx API as intFlag to Enable
** interrupts.
*/

#define     I2C_INT_ARBITRATION_LOST     I2C_IRQSTATUS_AL
#define     I2C_INT_NO_ACK               I2C_IRQSTATUS_NACK
#define     I2C_INT_ADRR_READY_ACESS     I2C_IRQSTATUS_ARDY
#define     I2C_INT_RECV_READY           I2C_IRQSTATUS_RRDY
#define     I2C_INT_TRANSMIT_READY       I2C_IRQSTATUS_XRDY
#define     I2C_INT_GENERAL_CALL         I2C_IRQSTATUS_GC
#define     I2C_INT_START                I2C_IRQSTATUS_STC
#define     I2C_INT_ACCESS_ERROR         I2C_IRQSTATUS_AERR
#define     I2C_INT_STOP_CONDITION       I2C_IRQSTATUS_BF
#define     I2C_INT_ADRR_SLAVE           I2C_IRQSTATUS_AAS
#define     I2C_INT_TRANSMIT_UNDER_FLOW  I2C_IRQSTATUS_XUDF
#define     I2C_INT_RECV_OVER_RUN        I2C_IRQSTATUS_ROVR
#define     I2C_INT_RECV_DRAIN           I2C_IRQSTATUS_RDR
#define     I2C_INT_TRANSMIT_DRAIN       I2C_IRQSTATUS_XDR   

/****************************************************************************/
/*
** Values that can be passed to I2CFIFOThersholdConfig/I2CFIFOClear API as 
** flag to select recieve or transmit mode.
*/
#define     I2C_TX_MODE                  1
#define     I2C_RX_MODE                  0

/****************************************************************************/
/*
** Values that can be passed to I2CBufferStatus API as flag to get status
** of the internal buffer.
*/

#define     I2C_TX_BUFFER_STATUS         0
#define     I2C_RX_BUFFER_STATUS         1
#define     I2C_FIFO_DEPTH               2

/****************************************************************************/
/*
** Values that can be passed to I2COwnAddressSet  API as flag to select
** any one of the HSI2C own address field .
*/

#define     HI2C_OWN_ADDR_0                0
#define     HI2C_OWN_ADDR_1                1
#define     HI2C_OWN_ADDR_2                2
#define     HI2C_OWN_ADDR_3                3

/****************************************************************************/
/*
** Values that can be passed to I2CIdleModeSelect  API as flag to select
** any one of the idle mode of operation.
*/

#define     I2C_FORCE_IDLE_MODE          (0 << I2C_SYSC_IDLEMODE_SHIFT)   
#define     I2C_NO_IDLE_MODE             (1 << I2C_SYSC_IDLEMODE_SHIFT)   
#define     I2C_SMART_IDLE_MODE          (2 << I2C_SYSC_IDLEMODE_SHIFT)   
#define     I2C_SMART_IDLE_WAKEUP_MODE   (3 << I2C_SYSC_IDLEMODE_SHIFT)   

/****************************************************************************/
/*
** Values that can be passed to I2CClockActivitySelect  API as flag to select
** the type of activity
*/

#define     I2C_CUT_OFF_BOTH_CLK         (0 << I2C_SYSC_CLKACTIVITY_SHIFT)   
#define     I2C_CUT_OFF_SYS_CLK          (1 << I2C_SYSC_CLKACTIVITY_SHIFT)   
#define     I2C_CUT_OFF_OCP_CLK          (2 << I2C_SYSC_CLKACTIVITY_SHIFT)   
#define     I2C_KEEP_ALIVE_BOTH_CLK      (3 << I2C_SYSC_CLKACTIVITY_SHIFT)   

/****************************************************************************/
/*
** Values that can be passed to I2CWakeUpEnable  API as eventFlag to select
** the type of wakeup signal to be Enabled.
*/

#define     I2C_WAKE_UP_ARBITRATION_LOST  I2C_WE_AL
#define     I2C_WAKE_UP_NO_ACK            I2C_WE_NACK
#define     I2C_WAKE_UP_ADRR_RDY_ACCESS   I2C_WE_ARDY
#define     I2C_WAKE_UP_GENERAL_CALL      I2C_WE_GC
#define     I2C_WAKE_UP_START             I2C_WE_STC
#define     I2C_WAKE_UP_STOP_CONDITION    I2C_WE_BF
#define     I2C_WAKE_UP_ADRR_SLAVE        I2C_WE_AAS
#define     I2C_WAKE_UP_TX_UNDER_FLOW     I2C_WE_XUDF
#define     I2C_WAKE_UP_RECV_OVER_RUN     I2C_WE_ROVR
#define     I2C_WAKE_UP_RECV_DRAIN        I2C_WE_RDR
#define     I2C_WAKE_UP_TRANSMIT_DRAIN    I2C_WE_XDR
#define     I2C_WAKE_UP_DATA_RECV_TX_RDY  I2C_WE_DRDY

/****************************************************************************/
/*
** Values that can be passed to I2CWakeUpEnable  API as flag to select
** the requet source to generate asynchronous signal.
*/

#define     I2C_WAKE_UP_IRQ               1
#define     I2C_WAKE_UP_DMA_RECV          2
#define     I2C_WAKE_UP_DMA_TRANSMIT      3
  
/****************************************************************************/
/*
** Values that can be passed to I2CMasterIntStatus/I2CSlaveIntStatus
** /I2CMasterIntStatusEx/I2CSlaveIntStatusEx API as flag to select
** RAWIRQSTATUS or IRQSTATUS.
*/

#define     I2C_STATUS_RAW                0
#define     I2C_STATUS                    1

/****************************************************************************/
/*
** Values that can be passed to I2COwnAddressSet API
*/

#define     I2C_OWN_ADDR_0                0
#define     I2C_OWN_ADDR_1                1
#define     I2C_OWN_ADDR_2                2
#define     I2C_OWN_ADDR_3                3


/*
** Structure to save the I2C context
*/
typedef struct i2cContext {
    unsigned int prescalar;
    unsigned int lowdivider;
    unsigned int highdivider;
    unsigned int ownaddr;
}I2CCONTEXT;



/*****************************************************************************/
/*
** Prototypes for the APIs
*/

extern void I2CSoftReset(unsigned int baseAdd);
extern void I2CMasterStop(unsigned int baseAdd);
extern void I2CMasterStart(unsigned int baseAdd);
extern void I2CMasterEnable(unsigned int baseAdd);
extern void I2CMasterDisable(unsigned int baseAdd);
extern void I2CAutoIdleEnable(unsigned int baseAdd);
extern void I2CAutoIdleDisable(unsigned int baseAdd);
extern void I2CDMATxEventEnable(unsigned int baseAdd);
extern void I2CDMARxEventEnable(unsigned int baseAdd);
extern void I2CDMATxEventDisable(unsigned int baseAdd);
extern unsigned int I2CMasterErr(unsigned int baseAdd);
extern void I2CDMARxEventDisable(unsigned int baseAdd);
extern void I2CGlobalWakeUpEnable(unsigned int baseAdd);
extern void I2CGlobalWakeUpDisable(unsigned int baseAdd);
extern unsigned int I2CDataCountGet(unsigned int baseAdd);
extern unsigned int I2CSlaveDataGet(unsigned int baseAdd);
extern unsigned char I2CMasterDataGet(unsigned int baseAdd);
extern unsigned int I2CMasterBusBusy(unsigned int baseAdd);
extern unsigned int I2CMasterBusy(unsigned int baseAdd);
extern unsigned int I2CSlaveIntStatus(unsigned int baseAdd);
extern unsigned int I2CMasterIntStatus(unsigned int baseAdd);
extern unsigned int I2CSystemStatusGet(unsigned int baseAdd);
extern unsigned int I2CSlaveIntRawStatus(unsigned int baseAdd);
extern unsigned int I2CMasterIntRawStatus(unsigned int baseAdd);
extern unsigned int I2CActiveOwnAddressGet(unsigned int baseAdd);
extern void I2CFIFOClear(unsigned int baseAdd, unsigned int flag);
extern void I2CSlaveDataPut(unsigned int baseAdd,unsigned int data);
extern void I2CMasterControl(unsigned int baseAdd, unsigned int cmd);
extern void I2CSetDataCount(unsigned int baseAdd, unsigned int count);
extern void I2CIdleModeSelect(unsigned int baseAdd, unsigned int flag);
extern void I2CMasterDataPut(unsigned int baseAdd, unsigned char data);
extern void I2CWakeUpEnable(unsigned int baseAdd, unsigned int eventFlag,
                            unsigned int flag);
extern void I2CWakeUpDisable(unsigned int baseAdd, unsigned int eventFlag,
                             unsigned int flag);
extern void I2CMasterInitExpClk(unsigned int baseAdd, unsigned int SysClk,
                                unsigned int IClk, unsigned int outputClk);
extern void I2COwnAddressSet(unsigned int baseAdd, unsigned int slaveAdd,
                             unsigned int flag);
extern void I2CSlaveIntClearEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CClockActivitySelect(unsigned int baseAdd, unsigned int flag);
extern void I2CSlaveIntEnableEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CMasterIntClearEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CSlaveIntDisableEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CMasterIntEnableEx(unsigned int baseAdd, unsigned int intFlag);
extern unsigned int I2CBufferStatus(unsigned int baseAdd, unsigned int flag);
extern void I2CMasterIntDisableEx(unsigned int baseAdd, unsigned int intFlag);

extern void I2CMasterSlaveAddrSet(unsigned int baseAdd, unsigned int slaveAdd);
extern void I2CSlaveIntRawStatusClearEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CFIFOThresholdConfig(unsigned int baseAdd, unsigned int threshlodVal,
                                   unsigned int flag);
extern unsigned int I2CSlaveIntStatusEx(unsigned int baseAdd, unsigned int intFlag);
extern void I2CMasterIntRawStatusClearEx(unsigned int baseAdd, unsigned int intFlag);
extern unsigned int I2CMasterIntStatusEx(unsigned int baseAdd, unsigned int intFlag);
extern unsigned int I2CSlaveIntRawStatusEx(unsigned int baseAdd, unsigned int intFlag);
extern unsigned int I2CMasterSlaveAddrGet(unsigned int baseAdd, unsigned int slaveAdd);
extern unsigned int I2CMasterIntRawStatusEx(unsigned int baseAdd, unsigned int intFlag);

extern void I2CContextSave(unsigned int i2cBase, I2CCONTEXT *contextPtr);
extern void I2CContextRestore(unsigned int i2cBase, I2CCONTEXT *contextPtr);

#ifdef __cplusplus
}
#endif

#endif
