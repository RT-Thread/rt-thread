/**
 *  \file       mcspi.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for McSPI. It also contains some
 *              related macro definitions.
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

#ifndef _MCSPI_H_
#define _MCSPI_H_

#include "hw_mcspi.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS 
****************************************************************************/

/*
** Values used to determine the channel number used for McSPI communication.
*/
#define MCSPI_CHANNEL_0                (0)
#define MCSPI_CHANNEL_1                (1)
#define MCSPI_CHANNEL_2                (2)
#define MCSPI_CHANNEL_3                (3)

/*
** Maximum number of McSPI channels used.
*/
#define MCSPI_MAX_CH                   (4)
/*
** Values used for determining the granularity for McSPI clock. 
*/
#define MCSPI_CLK_GRAN_2_PWR_N         (0)
#define MCSPI_CLK_GRAN_1               (1)

/*
** Values of polarity and phase of SPICLK that are used to configure the clock 
** value in various modes of operation.
*/
#define MCSPI_CLK_MODE_0              ((MCSPI_CH0CONF_POL_ACTIVEHIGH << \
                                        MCSPI_CH0CONF_POL_SHIFT) | \
                                        MCSPI_CH0CONF_PHA_ODD)
#define MCSPI_CLK_MODE_1               ((MCSPI_CH0CONF_POL_ACTIVEHIGH << \
                                         MCSPI_CH0CONF_POL_SHIFT) | \
                                         MCSPI_CH0CONF_PHA_EVEN)
#define MCSPI_CLK_MODE_2               ((MCSPI_CH0CONF_POL_ACTIVELOW << \
                                         MCSPI_CH0CONF_POL_SHIFT) | \
                                         MCSPI_CH0CONF_PHA_ODD)
#define MCSPI_CLK_MODE_3               ((MCSPI_CH0CONF_POL_ACTIVELOW << \
                                         MCSPI_CH0CONF_POL_SHIFT) | \
                                         MCSPI_CH0CONF_PHA_EVEN)


/*
** Values of Single/Multi channel that can be used in master mode.
*/
#define MCSPI_SINGLE_CH                (MCSPI_MODULCTRL_SINGLE_SINGLE)
#define MCSPI_MULTI_CH                 (MCSPI_MODULCTRL_SINGLE_MULTI)

/*
** Values used to configure the chip select time control(TCS).
*/
#define MCSPI_CS_TCS_0PNT5_CLK             (MCSPI_CH0CONF_TCS0_0P5)
#define MCSPI_CS_TCS_1PNT5_CLK             (MCSPI_CH0CONF_TCS0_1P5)
#define MCSPI_CS_TCS_2PNT5_CLK             (MCSPI_CH0CONF_TCS0_2P5)
#define MCSPI_CS_TCS_3PNT5_CLK             (MCSPI_CH0CONF_TCS0_3P5)
    
/*
** Value used to set the polarity for start bit for McSPI communication.
*/
#define MCSPI_START_BIT_POL_LOW            (MCSPI_CH0CONF_SBPOL_LOWLEVEL)
#define MCSPI_START_BIT_POL_HIGH           (MCSPI_CH0CONF_SBPOL)

/*
** Values used to configure communication on data line pins. 
*/
#define MCSPI_DATA_LINE_COMM_MODE_0        ((MCSPI_CH0CONF_IS_LINE0) | \
                                            (MCSPI_CH0CONF_DPE1_ENABLED) | \
                                            (MCSPI_CH0CONF_DPE0_ENABLED)) 
#define MCSPI_DATA_LINE_COMM_MODE_1        ((MCSPI_CH0CONF_IS_LINE0)| \
                                            (MCSPI_CH0CONF_DPE1_ENABLED)| \
                                            (MCSPI_CH0CONF_DPE0_DISABLED << \
                                             MCSPI_CH0CONF_DPE0_SHIFT))
#define MCSPI_DATA_LINE_COMM_MODE_2        ((MCSPI_CH0CONF_IS_LINE0) | \
                                            (MCSPI_CH0CONF_DPE1_DISABLED << \
                                             MCSPI_CH0CONF_DPE1_SHIFT) | \
                                            (MCSPI_CH0CONF_DPE0_ENABLED)) 
#define MCSPI_DATA_LINE_COMM_MODE_3        ((MCSPI_CH0CONF_IS_LINE0) | \
                                            (MCSPI_CH0CONF_DPE1_DISABLED << \
                                             MCSPI_CH0CONF_DPE1_SHIFT) | \
                                            (MCSPI_CH0CONF_DPE0_DISABLED << \
                                             MCSPI_CH0CONF_DPE0_SHIFT))
#define MCSPI_DATA_LINE_COMM_MODE_4         ((MCSPI_CH0CONF_IS_LINE1 << \
                                              MCSPI_CH0CONF_IS_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE1_ENABLED) | \
                                             (MCSPI_CH0CONF_DPE0_ENABLED))
#define MCSPI_DATA_LINE_COMM_MODE_5         ((MCSPI_CH0CONF_IS_LINE1 << \
                                              MCSPI_CH0CONF_IS_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE1_ENABLED) | \
                                             (MCSPI_CH0CONF_DPE0_DISABLED << \
                                              MCSPI_CH0CONF_DPE0_SHIFT))
#define MCSPI_DATA_LINE_COMM_MODE_6         ((MCSPI_CH0CONF_IS_LINE1 << \
                                              MCSPI_CH0CONF_IS_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE1_DISABLED << \
                                              MCSPI_CH0CONF_DPE1_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE0_ENABLED))
#define MCSPI_DATA_LINE_COMM_MODE_7         ((MCSPI_CH0CONF_IS_LINE1 << \
                                              MCSPI_CH0CONF_IS_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE1_DISABLED << \
                                              MCSPI_CH0CONF_DPE1_SHIFT) | \
                                             (MCSPI_CH0CONF_DPE0_DISABLED << \
                                              MCSPI_CH0CONF_DPE0_SHIFT))

/*
** Values used to enable initial delay for first transfer from McSPI peripheral.
*/
#define MCSPI_INITDLY_0                     (MCSPI_MODULCTRL_INITDLY_NODELAY)
#define MCSPI_INITDLY_4                     (MCSPI_MODULCTRL_INITDLY_4CLKDLY \
                                             << MCSPI_MODULCTRL_INITDLY_SHIFT)
#define MCSPI_INITDLY_8                     (MCSPI_MODULCTRL_INITDLY_8CLKDLY \
                                             << MCSPI_MODULCTRL_INITDLY_SHIFT)
#define MCSPI_INITDLY_16                    (MCSPI_MODULCTRL_INITDLY_16CLKDLY \
                                             << MCSPI_MODULCTRL_INITDLY_SHIFT)
#define MCSPI_INITDLY_32                    (MCSPI_MODULCTRL_INITDLY_32CLKDLY \
                                             << MCSPI_MODULCTRL_INITDLY_SHIFT)

/*
** Values used to determine transmit/receive modes of McSPI peripheral in
**  master mode. 
*/
#define MCSPI_TX_RX_MODE                    (MCSPI_CH0CONF_TRM_TXRX) 
#define MCSPI_RX_ONLY_MODE                  (MCSPI_CH0CONF_TRM_RXONLY << \
                                             MCSPI_CH0CONF_TRM_SHIFT)
#define MCSPI_TX_ONLY_MODE                  (MCSPI_CH0CONF_TRM_TXONLY << \
                                             MCSPI_CH0CONF_TRM_SHIFT)

/*
** Values that can be passed to enable/disable/clear status of  the various
** interrupts of McSPI peripheral.
** These macros can also be used to check the status obtained from 
** 'McSPIIntStatusGet' API.
** 0 <= chan <= 3 \n
*/
#define MCSPI_INT_TX_EMPTY(chan)           (1 << ((chan) * 4))
#define MCSPI_INT_TX_UNDERFLOW(chan)       (2 << ((chan) * 4))
#define MCSPI_INT_RX_FULL(chan)            (4 << ((chan) * 4))
#define MCSPI_INT_RX0_OVERFLOW             (8u)
#define MCSPI_INT_EOWKE                    (MCSPI_IRQENABLE_EOW_ENABLE)

/*
** Values used to check the status of McSPI channel status registers and FIFO.
*/
#define MCSPI_CH_STAT_RXS_FULL             (MCSPI_CH0STAT_RXS)
#define MCSPI_CH_STAT_TXS_EMPTY            (MCSPI_CH0STAT_TXS)
#define MCSPI_CH_STAT_EOT                  (MCSPI_CH0STAT_EOT)    
#define MCSPI_CH_TXFFE                     (MCSPI_CH0STAT_TXFFE)
#define MCSPI_CH_TXFFF                     (MCSPI_CH0STAT_TXFFF)
#define MCSPI_CH_RXFFE                     (MCSPI_CH0STAT_RXFFE)
#define MCSPI_CH_RXFFF                     (MCSPI_CH0STAT_RXFFF)

/*
** Values used to set the word length for McSPI communication.
** 'n' can take values only between 4 <= n <= 32. 
*/
#define MCSPI_WORD_LENGTH(n)           ((n - 1) << MCSPI_CH0CONF_WL_SHIFT)
/*
** Values used to set CS polarity for the McSPI peripheral.
*/
#define MCSPI_CS_POL_HIGH            (MCSPI_CH0CONF_EPOL_ACTIVEHIGH)
#define MCSPI_CS_POL_LOW             (MCSPI_CH0CONF_EPOL)

/*
** Values used to enable/disable the read/write DMA events of McSPI peripheral. 
*/
#define MCSPI_DMA_RX_EVENT           (MCSPI_CH0CONF_DMAR)
#define MCSPI_DMA_TX_EVENT           (MCSPI_CH0CONF_DMAW)

/*
** Value used to enable the turbo mode of operation for McSPI peripheral. 
*/
#define MCSPI_SET_STATUS_BIT         (MCSPI_SYST_SSB)

/*
** Value used to set the value of SPICLK in master mode of McSPI peripheral. 
*/
#define MCSPI_CLK_HIGH               (MCSPI_SYST_SPICLK)
#define MCSPI_CLK_LOW                (0x00000000)

/*
** Value used to enable/disable multiple word ocp access. 
*/
#define MCSPI_MOA_ENABLE            (MCSPI_MODULCTRL_MOA)
#define MCSPI_MOA_DISABLE           (MCSPI_MODULCTRL_MOA_DISABLED)

/*
** Value used to enable/disable FDAA operation of McSPI peripheral. 
*/
#define MCSPI_FDAA_DISABLE           (MCSPI_MODULCTRL_FDAA_NOSHADOWREG)
#define MCSPI_FDAA_ENABLE            (MCSPI_MODULCTRL_FDAA)

/*
** Values used to enable/disable the Tx/Rx FIFOs of McSPI peripheral. 
*/
#define MCSPI_RX_FIFO_ENABLE         (MCSPI_CH0CONF_FFER)
#define MCSPI_RX_FIFO_DISABLE        (MCSPI_CH0CONF_FFER_FFDISABLED)
#define MCSPI_TX_FIFO_ENABLE         (MCSPI_CH0CONF_FFEW)    
#define MCSPI_TX_FIFO_DISABLE        (MCSPI_CH0CONF_FFEW_FFDISABLED)    


extern void McSPIClkConfig(unsigned int baseAdd, unsigned int spiInClk, 
                           unsigned int spiOutClk,
                           unsigned int chNum, unsigned int clkMode);
extern void McSPIWordLengthSet(unsigned int baseAdd, unsigned int wordLength,
                        unsigned int chNum);
extern void McSPICSEnable(unsigned int baseAdd);
extern void McSPICSDisable(unsigned int baseAdd);
extern void McSPICSTimeControlSet(unsigned int baseAdd, unsigned int csTimeControl,
                           unsigned int chNum);
extern void McSPICSAssert(unsigned int baseAdd, unsigned int chNum);
extern void McSPICSDeAssert(unsigned int baseAdd, unsigned int chNum);
extern void McSPIStartBitEnable(unsigned int baseAdd, unsigned int chNum);
extern void McSPIStartBitPolarityConfig(unsigned int baseAdd, 
                 unsigned int startBitPol, unsigned int chNum);
extern void McSPICSPolarityConfig(unsigned int baseAdd, unsigned int spiEnPol,
                           unsigned int chNum);
extern void McSPIStartBitDisable(unsigned int baseAdd,unsigned int chNum);
extern void McSPIMasterModeEnable(unsigned int baseAdd);
extern unsigned int McSPIMasterModeConfig(unsigned int baseAdd, 
                                          unsigned int channelMode, 
                                          unsigned int trMode, 
                          unsigned int pinMode,
                                          unsigned int chNum);
extern void McSPIChannelEnable(unsigned int baseAdd, unsigned int chNum);
extern void McSPIChannelDisable(unsigned int baseAdd, unsigned int chNum);
extern void McSPIReset(unsigned int baseAdd);
extern void McSPITurboModeEnable(unsigned int baseAdd, unsigned int chNum);
extern void McSPITurboModeDisable(unsigned int baseAdd, unsigned int chNum);
extern void McSPITxFIFOConfig(unsigned int baseAdd, unsigned int txFifo, 
                       unsigned int chNum);
extern void McSPIRxFIFOConfig(unsigned int baseAdd, unsigned int rxFifo, 
                       unsigned int chNum);
extern void McSPIFIFOTrigLvlSet(unsigned int baseAdd, unsigned char afl, 
                         unsigned char ael, unsigned int trMode);
extern void McSPIWordCountSet(unsigned int baseAdd, unsigned short wCnt);
extern void McSPIDMAEnable(unsigned int baseAdd, unsigned int dmaFlags,
                    unsigned int chNum);
extern void McSPIDMADisable(unsigned int baseAdd, unsigned int dmaFlags,
                     unsigned int chNum);
extern void McSPIIntEnable(unsigned int baseAdd, unsigned int intFlags);
extern void McSPIIntDisable(unsigned int baseAdd, unsigned int intFlags);
extern void McSPIInitDelayConfig(unsigned int baseAdd, unsigned int initDelay);
extern void McSPITransmitData(unsigned int baseAdd, unsigned int txData,
                       unsigned int chNum);
extern unsigned int McSPIReceiveData(unsigned int baseAdd,unsigned int chNum);
extern unsigned int McSPIIntStatusGet(unsigned int baseAdd);
extern void McSPIIntStatusClear(unsigned int baseAdd, unsigned int intFlags);
extern unsigned int McSPIChannelStatusGet(unsigned int baseAdd, unsigned int chNum);
extern void McSPIMultipleWordAccessConfig(unsigned int baseAdd, unsigned int moa);
extern void McSPIFIFODatManagementConfig(unsigned int baseAdd, unsigned int fdaa);

#ifdef __cplusplus
}
#endif

#endif

/*************************** END OF FILE **************************************/
