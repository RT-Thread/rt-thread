/**
 * \file   uart_irda_cir.h
 *
 * \brief  This file contains the prototyes of the functions defined in
 *         <uart_irda_cir.c>. This also contains some related macro
 *         definitions and some files to be included.
 *
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

#ifndef _UART_IRDA_CIR_H_
#define _UART_IRDA_CIR_H_

#include "hw_uart_irda_cir.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS 
****************************************************************************/

/* The size of the Transmitter FIFO. */
#define TX_FIFO_SIZE                        (64)

/* The size of the Receiver FIFO. */
#define RX_FIFO_SIZE                        (64)

/*
** Values to configure the Operating modes of UART.
*/
#define UART16x_OPER_MODE                   (UART_MDR1_MODE_SELECT_UART16X)
#define UART_SIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_SIR)
#define UART16x_AUTO_BAUD_OPER_MODE         (UART_MDR1_MODE_SELECT_UART16XAUTO)
#define UART13x_OPER_MODE                   (UART_MDR1_MODE_SELECT_UART13X)
#define UART_MIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_MIR)
#define UART_FIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_FIR)
#define UART_CIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_CIR)
#define UART_DISABLED_MODE                  (UART_MDR1_MODE_SELECT_DISABLED)

/****************************************************************************/
/*
** Values to control the Line characteristics.
*/

/* Break condition generation controls. */
#define UART_BREAK_COND_DISABLE             (UART_LCR_BREAK_EN_NORMAL << \
                                             UART_LCR_BREAK_EN_SHIFT)
#define UART_BREAK_COND_ENABLE              (UART_LCR_BREAK_EN_FORCE << \
                                             UART_LCR_BREAK_EN_SHIFT)

/* Values to control parity feature. */

#define UART_PARITY_REPR_1                  (UART_LCR_PARITY_TYPE2 | \
                                             (UART_LCR_PARITY_TYPE1_ODD << \
                                              UART_LCR_PARITY_TYPE1_SHIFT) | \
                                              UART_LCR_PARITY_EN)

#define UART_PARITY_REPR_0                  (UART_LCR_PARITY_TYPE2 | \
                                             (UART_LCR_PARITY_TYPE1_EVEN << \
                                              UART_LCR_PARITY_TYPE1_SHIFT) | \
                                              UART_LCR_PARITY_EN)

#define UART_ODD_PARITY                     ((UART_LCR_PARITY_TYPE1_ODD << \
                                              UART_LCR_PARITY_TYPE1_SHIFT) | \
                                              UART_LCR_PARITY_EN)

#define UART_EVEN_PARITY                    ((UART_LCR_PARITY_TYPE1_EVEN << \
                                              UART_LCR_PARITY_TYPE1_SHIFT) | \
                                              UART_LCR_PARITY_EN)

#define UART_PARITY_NONE                    (UART_LCR_PARITY_EN_DISABLE << \
                                             UART_LCR_PARITY_EN_SHIFT)


/* Number of Stop Bits per frame. */

#define UART_FRAME_NUM_STB_1                (UART_LCR_NB_STOP_1BIT << \
                                             UART_LCR_NB_STOP_SHIFT)
#define UART_FRAME_NUM_STB_1_5_2            (UART_LCR_NB_STOP_2BIT << \
                                             UART_LCR_NB_STOP_SHIFT)

/* Word Length per frame. */

#define UART_FRAME_WORD_LENGTH_5            (UART_LCR_CHAR_LENGTH_5BIT)
#define UART_FRAME_WORD_LENGTH_6            (UART_LCR_CHAR_LENGTH_6BIT)
#define UART_FRAME_WORD_LENGTH_7            (UART_LCR_CHAR_LENGTH_7BIT)
#define UART_FRAME_WORD_LENGTH_8            (UART_LCR_CHAR_LENGTH_8BIT)

/****************************************************************************/
/* 
** Values associated with setting the Trigger Levels and DMA mode selection. 
*/

/* Values for trigger level for the Receiver FIFO. */

#define UART_FCR_RX_TRIG_LVL_8              (UART_FCR_RX_FIFO_TRIG_8CHAR <<   \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_16             (UART_FCR_RX_FIFO_TRIG_16CHAR <<  \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_56             (UART_FCR_RX_FIFO_TRIG_56CHAR <<  \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_60             (UART_FCR_RX_FIFO_TRIG_60CHAR <<  \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)


/* Values for the trigger level for the Transmitter FIFO. */

#define UART_FCR_TX_TRIG_LVL_8              (UART_FCR_TX_FIFO_TRIG_8SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_16             (UART_FCR_TX_FIFO_TRIG_16SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_32             (UART_FCR_TX_FIFO_TRIG_32SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_56             (UART_FCR_TX_FIFO_TRIG_56SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)

/* Values corresponding to DMA mode selection. */

#define UART_DMA_MODE_0_ENABLE              (UART_SCR_DMA_MODE_2_MODE0)
#define UART_DMA_MODE_1_ENABLE              (UART_SCR_DMA_MODE_2_MODE1)
#define UART_DMA_MODE_2_ENABLE              (UART_SCR_DMA_MODE_2_MODE2)
#define UART_DMA_MODE_3_ENABLE              (UART_SCR_DMA_MODE_2_MODE3)

/*
** Values used to choose the path for configuring the DMA Mode.
** DMA Mode could be configured either through FCR or SCR.
*/
#define UART_DMA_EN_PATH_FCR                (UART_SCR_DMA_MODE_CTL_FCR)
#define UART_DMA_EN_PATH_SCR                (UART_SCR_DMA_MODE_CTL_SCR)

/****************************************************************************/
/*
** Values related to enabling/disabling of Interrupts.
*/

/* Values for enabling/disabling the interrupts of UART. */

#define UART_INT_CTS                        (UART_IER_CTS_IT)
#define UART_INT_RTS                        (UART_IER_RTS_IT)
#define UART_INT_XOFF                       (UART_IER_XOFF_IT)
#define UART_INT_SLEEPMODE                  (UART_IER_SLEEP_MODE_IT)
#define UART_INT_MODEM_STAT                 (UART_IER_MODEM_STS_IT)
#define UART_INT_LINE_STAT                  (UART_IER_LINE_STS_IT)
#define UART_INT_THR                        (UART_IER_THR_IT)
#define UART_INT_RHR_CTI                    (UART_IER_RHR_IT)

/****************************************************************************/
/*
** Values related to Line Status information.
*/

/* Values pertaining to UART Line Status information. */

#define UART_FIFO_PE_FE_BI_DETECTED         (UART_LSR_RX_FIFO_STS)
#define UART_BREAK_DETECTED_ERROR           (UART_LSR_RX_BI)
#define UART_FRAMING_ERROR                  (UART_LSR_RX_FE)
#define UART_PARITY_ERROR                   (UART_LSR_RX_PE)
#define UART_OVERRUN_ERROR                  (UART_LSR_RX_OE)

/****************************************************************************/
/*
** Values related to status of Interrupt souces.
*/

/* Values pertaining to status of UART Interrupt sources. */

#define UART_INTID_MODEM_STAT               (UART_IIR_IT_TYPE_MODEMINT << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_TX_THRES_REACH           (UART_IIR_IT_TYPE_THRINT << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_THRES_REACH           (UART_IIR_IT_TYPE_RHRINT << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_LINE_STAT_ERROR       (UART_IIR_IT_TYPE_RXSTATUSERROR << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_CHAR_TIMEOUT             (UART_IIR_IT_TYPE_RXTIMEOUT << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_XOFF_SPEC_CHAR_DETECT    (UART_IIR_IT_TYPE_XOFF << \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_MODEM_SIG_STATE_CHANGE   (UART_IIR_IT_TYPE_STATECHANGE << \
                                             UART_IIR_IT_TYPE_SHIFT)

/* Values indicating the UART Interrupt pending status. */
#define UART_INT_PENDING                    (0)
#define UART_N0_INT_PENDING                 (1)


/****************************************************************************/
/*
** Values pertaining to control of Enhanced Features.
*/

/* Values for controlling Auto-CTS and Auto-RTS features. */

#define UART_AUTO_CTS_ENABLE                (UART_EFR_AUTO_CTS_EN)
#define UART_AUTO_CTS_DISABLE               (UART_EFR_AUTO_CTS_EN_NORMAL)

#define UART_AUTO_RTS_ENABLE                (UART_EFR_AUTO_RTS_EN)
#define UART_AUTO_RTS_DISABLE               (UART_EFR_AUTO_RTS_EN_NORMAL)

/* Values to enable/disable detection of Special Character. */

#define UART_SPECIAL_CHAR_DETECT_ENABLE     (UART_EFR_SPECIAL_CHAR_DETECT)
#define UART_SPECIAL_CHAR_DETECT_DISABLE    (UART_EFR_SPECIAL_CHAR_DETECT_NORMAL)


/* Values to configure the options for Software Flow Control. */

#define UART_NO_SOFTWARE_FLOW_CONTROL       ((UART_EFR_SW_FLOW_CONTROL_TX_NONE << \
                                              UART_EFR_SW_FLOW_CONTROL_TX_SHIFT) | \
                                             (UART_EFR_SW_FLOW_CONTROL_RX_NONE << \
                                              UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

#define UART_TX_RX_XON1_XOFF1               ((UART_EFR_SW_FLOW_CONTROL_TX_XONOFF1 << \
                                              UART_EFR_SW_FLOW_CONTROL_TX_SHIFT) | \
                                             (UART_EFR_SW_FLOW_CONTROL_RX_XONOFF1 << \
                                              UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))  

#define UART_TX_RX_XON2_XOFF2               ((UART_EFR_SW_FLOW_CONTROL_TX_XONOFF2 << \
                                              UART_EFR_SW_FLOW_CONTROL_TX_SHIFT) | \
                                             (UART_EFR_SW_FLOW_CONTROL_RX_XONOFF2 << \
                                              UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

#define UART_TX_RX_XON1_XOFF1_XON2_XOFF2    ((UART_EFR_SW_FLOW_CONTROL_TX_XONOFF1AND2 << \
                                              UART_EFR_SW_FLOW_CONTROL_TX_SHIFT) | \
                                             (UART_EFR_SW_FLOW_CONTROL_RX_XONOFF1AND2 << \
                                              UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

/****************************************************************************/
/*
** Values corresponding to Mode Definition Register 2(MDR2).
*/

/* Values to enable/disable Pulse shaping for UART. */
#define UART_PULSE_NORMAL                   (UART_MDR2_UART_PULSE_NORMAL << \
                                             UART_MDR2_UART_PULSE_SHIFT)
#define UART_PULSE_SHAPING                  (UART_MDR2_UART_PULSE_SHAPING << \
                                             UART_MDR2_UART_PULSE_SHIFT)
/****************************************************************************/
/*
** Values corresponding to Mode Definition Register 3(MDR3).
*/

/* Values used to control the method of setting the TX DMA Threshold value. */
#define UART_TX_DMA_THRESHOLD_64            (UART_MDR3_SET_TX_DMA_THRESHOLD_64 << \
                                             UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT)
#define UART_TX_DMA_THRESHOLD_REG           (UART_MDR3_SET_TX_DMA_THRESHOLD_REG << \
                                             UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT)

/****************************************************************************/
/*
** Macros related to control and status of Modem Signals.
*/

/* Values to enable/disable XON any feature. */

#define UART_XON_ANY_ENABLE                 (UART_MCR_XON_EN_ENABLE << \
                                             UART_MCR_XON_EN_SHIFT)
#define UART_XON_ANY_DISABLE                (UART_MCR_XON_EN_DISABLE << \
                                             UART_MCR_XON_EN_SHIFT)

/* Values to enable/disable Loopback mode of operation. */

#define UART_LOOPBACK_MODE_ENABLE           (UART_MCR_LOOPBACK_EN_LOOPBACK << \
                                             UART_MCR_LOOPBACK_EN_SHIFT)
#define UART_LOOPBACK_MODE_DISABLE          (UART_MCR_LOOPBACK_EN_NORMAL << \
                                             UART_MCR_LOOPBACK_EN_SHIFT)

/* Macros used to force the Modem Control lines to active/inactive states. */

#define UART_DCD_CONTROL                    (UART_MCR_CD_STS_CH)
#define UART_RI_CONTROL                     (UART_MCR_RI_STS_CH)
#define UART_RTS_CONTROL                    (UART_MCR_RTS)
#define UART_DTR_CONTROL                    (UART_MCR_DTR)


/* Values that indicate the values on Modem Control lines. */

#define UART_DCD_VALUE                      (UART_MSR_NCD_STS)
#define UART_RI_VALUE                       (UART_MSR_NRI_STS)
#define UART_DSR_VALUE                      (UART_MSR_NDSR_STS)
#define UART_CTS_VALUE                      (UART_MSR_NCTS_STS)

/* Values used to detect the changes in Modem Control lines. */

#define UART_DCD_STS_CHANGED                (UART_MSR_DCD_STS)
#define UART_RI_STS_CHANGED                 (UART_MSR_RI_STS)
#define UART_DSR_STS_CHANGED                (UART_MSR_DSR_STS)
#define UART_CTS_STS_CHANGED                (UART_MSR_CTS_STS)


/****************************************************************************/
/*
** Values related to the control and status of Supplementary registers.
*/

/*
** Values used to enable/disable a granularity of 1 for TX and RX FIFO trigger
** levels.
*/
#define UART_RX_TRIG_LVL_GRAN_1_DISABLE     (UART_SCR_RX_TRIG_GRANU1_DISABLE << \
                                             UART_SCR_RX_TRIG_GRANU1_SHIFT)
#define UART_RX_TRIG_LVL_GRAN_1_ENABLE      (UART_SCR_RX_TRIG_GRANU1_ENABLE << \
                                             UART_SCR_RX_TRIG_GRANU1_SHIFT)

#define UART_TX_TRIG_LVL_GRAN_1_DISABLE     (UART_SCR_TX_TRIG_GRANU1_DISABLE << \
                                              UART_SCR_TX_TRIG_GRANU1_SHIFT)
#define UART_TX_FIFO_LVL_GRAN_1_ENABLE      (UART_SCR_TX_TRIG_GRANU1_ENABLE << \
                                             UART_SCR_TX_TRIG_GRANU1_SHIFT)

/* Value used to enable/disable DSRn interrupt. */

#define UART_DSRn_INT_DISABLE               (UART_SCR_DSR_IT_DISABLE << \
                                             UART_SCR_DSR_IT_SHIFT)
#define UART_DSRn_INT_ENABLE                (UART_SCR_DSR_IT_ENABLE << \
                                             UART_SCR_DSR_IT_SHIFT)

/* Values to control the module Wake-Up rights for RX, CTSn and DSRn pins. */

#define UART_RX_CTS_DSR_WAKEUP_DISABLE      (UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_DISABLE << \
                                             UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT)
#define UART_RX_CTS_DSR_WAKEUP_ENABLE       (UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_ENABLE << \
                                             UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT)

/* Values to control the THR interrupt modes. */

#define UART_THR_INT_NORMAL                 (UART_SCR_TX_EMPTY_CTL_IT_NORMAL << \
                                             UART_SCR_TX_EMPTY_CTL_IT_SHIFT)
#define UART_THR_INT_FIFO_TSR_EMPTY         (UART_SCR_TX_EMPTY_CTL_IT_EMPTY << \
                                             UART_SCR_TX_EMPTY_CTL_IT_SHIFT)

/* Values to control the DMA counter reset features. */

#define UART_DMA_CNTR_NO_RESET_FIFO_RESET   (UART_SSR_DMA_COUNTER_RST_MODE0 << \
                                             UART_SSR_DMA_COUNTER_RST_SHIFT)
#define UART_DMA_CNTR_RESET_FIFO_RESET      (UART_SSR_DMA_COUNTER_RST_MODE1 << \
                                             UART_SSR_DMA_COUNTER_RST_SHIFT)

/* Values indicating the Falling edge status on RX, CTSn and DSRn pins. */

#define UART_RX_CTS_DSR_NO_FALL_EDGE        (UART_SSR_RX_CTS_DSR_WAKE_UP_STS_NONE << \
                                             UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT)
#define UART_RX_CTS_DSR_FALL_EDGE           (UART_SSR_RX_CTS_DSR_WAKE_UP_STS_DETECTED << \
                                             UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT)

/* Values indicating the filled status of TX FIFO. */

#define UART_TX_FIFO_NOT_FULL               (UART_SSR_TX_FIFO_FULL_NOTFULL)
#define UART_TX_FIFO_FULL                   (UART_SSR_TX_FIFO_FULL_FULL)

/****************************************************************************/
/*
** Values related to Auxilliary Control Register(ACREG).
*/

/* Values to set/clear the SD pin. */

#define UART_SD_PIN_LOW                     (UART_ACREG_SD_MOD_LOW << \
                                             UART_ACREG_SD_MOD_SHIFT)
#define UART_SD_PIN_HIGH                    (UART_ACREG_SD_MOD_HIGH << \
                                             UART_ACREG_SD_MOD_SHIFT)

/****************************************************************************/
/*
** Values controlling System Configuration functions.
*/

/* Values controlling Power Management Request/Acknowledgement modes. */

#define UART_IDLEMODE_FORCE_IDLE            (UART_SYSC_IDLEMODE_FORCE << \
                                             UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_NO_IDLE               (UART_SYSC_IDLEMODE_NOIDLE << \
                                             UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_SMART_IDLE            (UART_SYSC_IDLEMODE_SMART << \
                                             UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_SMART_IDLE_WAKEUP     (UART_SYSC_IDLEMODE_WAKEUP << \
                                             UART_SYSC_IDLEMODE_SHIFT)

/* Values enabling/disabling WakeUp capability. */

#define UART_WAKEUP_ENABLE                  (UART_SYSC_ENAWAKEUP_ENABLE << \
                                             UART_SYSC_ENAWAKEUP_SHIFT)
#define UART_WAKEUP_DISABLE                 (UART_SYSC_ENAWAKEUP_DISABLE << \
                                             UART_SYSC_ENAWAKEUP_SHIFT)

/* Values to enable /disable Autoidle mode. */
#define UART_AUTO_IDLE_MODE_ENABLE          (UART_SYSC_AUTOIDLE_ENABLE)
#define UART_AUTO_IDLE_MODE_DISABLE         (UART_SYSC_AUTOIDLE_DISABLE)

/****************************************************************************/
/*
** Values configuring Wake-up modes for the UART in Wake-Up Enable Register.
*/

/* Values that enable/disable Wake-Up generation ability for various signals. */
#define UART_WAKEUP_TX_INTERRUPT            (UART_WER_EVENT_7_TX_WAKEUP_EN)
#define UART_WAKEUP_RLS_INTERRUPT           (UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT)
#define UART_WAKEUP_RHR_INTERRUPT           (UART_WER_EVENT_5_RHR_INTERRUPT)
#define UART_WAKEUP_RX_ACTIVITY             (UART_WER_EVENT_4_RX_ACTIVITY)
#define UART_WAKEUP_DCD_ACTIVITY            (UART_WER_EVENT_3_DCD_CD_ACTIVITY)
#define UART_WAKEUP_RI_ACTIVITY             (UART_WER_EVENT_2_RI_ACTIVITY)
#define UART_WAKEUP_DSR_ACTIVITY            (UART_WER_EVENT_1_DSR_ACTIVITY)
#define UART_WAKEUP_CTS_ACTIVITY            (UART_WER_EVENT_0_CTS_ACTIVITY)

/****************************************************************************/
/*
** Values indicating the line characteristics of UART Autobauding mode
** communication.
*/

/* Values indicating the parity in UART Autobauding mode. */

#define UART_AUTOBAUD_NO_PARITY             (UART_UASR_PARITY_TYPE_NONE << \
                                             UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_PARITY_SPACE          (UART_UASR_PARITY_TYPE_SPACE << \
                                             UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_EVEN_PARITY           (UART_UASR_PARITY_TYPE_EVEN << \
                                             UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_ODD_PARITY            (UART_UASR_PARITY_TYPE_ODD << \
                                             UART_UASR_PARITY_TYPE_SHIFT)

/* Values indicating the word length in UART Autobaud mode. */

#define UART_AUTOBAUD_CHAR_LENGTH_7         (UART_UASR_BIT_BY_CHAR_7BITS << \
                                             UART_UASR_BIT_BY_CHAR_SHIFT)
#define UART_AUTOBAUD_CHAR_LENGTH_8         (UART_UASR_BIT_BY_CHAR_8BITS << \
                                             UART_UASR_BIT_BY_CHAR_SHIFT)

/* Values indicating the baud rate in UART Autobaud mode. */

#define UART_AUTOBAUD_NO_SPEED_IDEN         (UART_UASR_SPEED_NONE)
#define UART_AUTOBAUD_SPEED_115200          (UART_UASR_SPEED_115200)
#define UART_AUTOBAUD_SPEED_57600           (UART_UASR_SPEED_57600)
#define UART_AUTOBAUD_SPEED_38400           (UART_UASR_SPEED_38400)
#define UART_AUTOBAUD_SPEED_28800           (UART_UASR_SPEED_28800)
#define UART_AUTOBAUD_SPEED_19200           (UART_UASR_SPEED_19200)
#define UART_AUTOBAUD_SPEED_14400           (UART_UASR_SPEED_14400)
#define UART_AUTOBAUD_SPEED_9600            (UART_UASR_SPEED_9600)
#define UART_AUTOBAUD_SPEED_4800            (UART_UASR_SPEED_4800)
#define UART_AUTOBAUD_SPEED_2400            (UART_UASR_SPEED_2400)
#define UART_AUTOBAUD_SPEED_1200            (UART_UASR_SPEED_1200)

/****************************************************************************/
/*
** Miscellaneous macros.
*/
/*
** Values used to choose the trigger level granularity.
*/
#define UART_TRIG_LVL_GRANULARITY_4         (0x0000)
#define UART_TRIG_LVL_GRANULARITY_1         (0x0001)

/* Values to be used while switching between register configuration modes. */

#define UART_REG_CONFIG_MODE_A              (0x0080)
#define UART_REG_CONFIG_MODE_B              (0x00BF)
#define UART_REG_OPERATIONAL_MODE           (0x007F)

/* Parameterized macro to configure the FIFO settings. */
#define UART_FIFO_CONFIG(txGra, rxGra, txTrig, rxTrig, txClr, rxClr, dmaEnPath, dmaMode) \
                        ((unsigned int) \
                         (((txGra & 0xF) << 26) | \
                          ((rxGra & 0xF) << 22) | \
                          ((txTrig & 0xFF) << 14) | \
                          ((rxTrig & 0xFF) << 6) | \
                          ((txClr & 0x1) << 5) | \
                          ((rxClr & 0x1) << 4) | \
                          ((dmaEnPath & 0x1) << 3) | \
                          (dmaMode & 0x7)))

#define UART_FIFO_CONFIG_TXGRA     (0xF << 26)
#define UART_FIFO_CONFIG_RXGRA     (0xF << 22)
#define UART_FIFO_CONFIG_TXTRIG    (0xFF << 14)
#define UART_FIFO_CONFIG_RXTRIG    (0xFF << 6)
#define UART_FIFO_CONFIG_TXCLR     (0x1 << 5)
#define UART_FIFO_CONFIG_RXCLR     (0x1 << 4)
#define UART_FIFO_CONFIG_DMAENPATH (0x1 << 3)
#define UART_FIFO_CONFIG_DMAMODE   (0x7 << 0)

/* Parameterized macro used to determine a value to be written to FCR. */
#define UART_FCR_PROGRAM(rxFIFOTrig, txFIFOTrig, dmaMode, txClr, rxClr, fifoEn) \
                        ((unsigned int) \
                         (((rxFIFOTrig & 0x3) << 6) | \
                          ((txFIFOTrig & 0x3) << 4) | \
                          ((dmaMode & 0x1) << 3) | \
                          ((txClr & 0x1) << 2) | \
                          ((rxClr & 0x1) << 1) | \
                          (fifoEn & 0x1)))

/* Over-sampling rate for MIR mode used to obtain the Divisor Values. */
#define UART_MIR_OVERSAMPLING_RATE_41          (41)
#define UART_MIR_OVERSAMPLING_RATE_42          (42)

/******************************************************************************
**                  FUNCTION PROTOTYPES
******************************************************************************/

/* APIs pertaining to UART. */

extern unsigned int UARTOperatingModeSelect(unsigned int baseAdd,
                                            unsigned int modeFlag);
extern unsigned int UARTDivisorValCompute(unsigned int moduleClk,
                                          unsigned int baudRate,
                                          unsigned int modeFlag,
                                          unsigned int mirOverSampRate);
extern unsigned int UARTDivisorLatchWrite(unsigned int baseAdd,
                                          unsigned int divisorValue);
extern void UARTDivisorLatchEnable(unsigned int baseAdd);
extern void UARTDivisorLatchDisable(unsigned int baseAdd);
extern unsigned int UARTRegConfigModeEnable(unsigned int baseAdd,
                                     unsigned int modeFlag);
extern void UARTRegConfModeRestore(unsigned int baseAdd,
                                   unsigned int lcrRegValue);
extern void UARTBreakCtl(unsigned int baseAdd, unsigned int breakState);
extern void UARTLineCharacConfig(unsigned int baseAdd,
                                 unsigned int wLenStbFlag,
                                 unsigned int parityFlag);
extern void UARTParityModeSet(unsigned int baseAdd, unsigned int parityFlag);

extern unsigned int UARTParityModeGet(unsigned int baseAdd);
extern void UARTDMAEnable(unsigned int baseAdd, unsigned int dmaModeFlag);
extern void UARTDMADisable(unsigned int baseAdd);
extern unsigned int UARTFIFOConfig(unsigned int baseAdd,
                                   unsigned int fifoConfig);
extern unsigned int UARTEnhanFuncEnable(unsigned int baseAdd);
extern void UARTEnhanFuncBitValRestore(unsigned int baseAdd,
                                       unsigned int enhanFnBitVal);
extern unsigned int UARTSubConfigMSRSPRModeEn(unsigned int baseAdd);

extern unsigned int UARTSubConfigTCRTLRModeEn(unsigned int baseAdd);
extern unsigned int UARTSubConfigXOFFModeEn(unsigned int baseAdd);
extern void UARTTCRTLRBitValRestore(unsigned int baseAdd,
                                    unsigned int tcrTlrBitVal);
extern void UARTIntEnable(unsigned int baseAdd, unsigned int intFlag);
extern void UARTIntDisable(unsigned int baseAdd, unsigned int intFlag);
extern unsigned int UARTSpaceAvail(unsigned int baseAdd);
extern unsigned int UARTCharsAvail(unsigned int baseAdd);
extern unsigned int UARTCharPutNonBlocking(unsigned int baseAdd,
                                           unsigned char byteWrite);
extern signed char UARTCharGetNonBlocking(unsigned int baseAdd);
extern signed char UARTCharGet(unsigned int baseAdd);
extern int UARTCharGetTimeout(unsigned int baseAdd,
                                        unsigned int timeOutVal);

extern void UARTCharPut(unsigned int baseAdd, unsigned char byteTx);
extern void UARTFIFOCharPut(unsigned int baseAdd, unsigned char byteTx);
extern signed char UARTFIFOCharGet(unsigned int baseAdd);
extern unsigned int UARTFIFOWrite(unsigned int baseAdd, unsigned char *pBuffer,
                                  unsigned int numTxBytes);
extern unsigned int UARTRxErrorGet(unsigned int baseAdd);
extern unsigned int UARTIntIdentityGet(unsigned int baseAdd);
extern unsigned int UARTIntPendingStatusGet(unsigned int baseAdd);
extern unsigned int UARTFIFOEnableStatusGet(unsigned int baseAdd);
extern void UARTAutoRTSAutoCTSControl(unsigned int baseAdd,
                                      unsigned int autoCtsControl,
                                      unsigned int autoRtsControl);
extern void UARTSpecialCharDetectControl(unsigned int baseAdd,
                                         unsigned int controlFlag);
extern void UARTSoftwareFlowCtrlOptSet(unsigned int baseAdd,
                                       unsigned int swFlowCtrl);
extern void UARTPulseShapingControl(unsigned int baseAdd,
                                    unsigned int shapeControl);

extern void UARTModuleReset(unsigned int baseAdd);
extern void UARTIdleModeConfigure(unsigned int baseAdd, unsigned int modeFlag);
extern void UARTWakeUpControl(unsigned int baseAdd, unsigned int controlFlag);
extern void UARTAutoIdleModeControl(unsigned int baseAdd,
                                    unsigned int modeFlag);
extern void UARTFlowCtrlTrigLvlConfig(unsigned int baseAdd,
                                      unsigned int rtsHaltFlag,
                                      unsigned int rtsStartFlag);
extern void UARTXON1XOFF1ValProgram(unsigned int baseAdd,
                                    unsigned char xon1Value,
                                    unsigned char xoff1Value);
extern void UARTXON2XOFF2ValProgram(unsigned int baseAdd,
                                    unsigned char xon2Value,
                                    unsigned char xoff2Value);
extern void UARTXONAnyFeatureControl(unsigned int baseAdd,
                                     unsigned int controlFlag);
extern void UARTLoopbackModeControl(unsigned int baseAdd,
                                    unsigned int controlFlag);
extern void UARTModemControlSet(unsigned int baseAdd, unsigned int modeFlag);

extern void UARTModemControlClear(unsigned int baseAdd, unsigned int modeFlag);
extern unsigned int UARTModemStatusGet(unsigned int baseAdd);
extern unsigned int UARTModemStatusChangeCheck(unsigned int baseAdd);
extern void UARTResumeOperation(unsigned int baseAdd);

extern void UARTWakeUpEventsEnable(unsigned int baseAdd,
                                   unsigned int wakeUpFlag);
extern void UARTWakeUpEventsDisable(unsigned int baseAdd,
                                    unsigned int wakeUpFlag);
extern void UARTFIFOTrigLvlGranControl(unsigned int baseAdd,
                                       unsigned int rxFIFOGranCtrl,
                                       unsigned int txFIFOGranCtrl);
extern void UARTDSRInterruptControl(unsigned int baseAdd,
                                    unsigned int controlFlag);
extern void UARTTxEmptyIntControl(unsigned int baseAdd,
                                  unsigned int controlFlag);
extern void UARTRXCTSDSRWakeUpConfigure(unsigned int baseAdd,
                                        unsigned int wakeUpFlag);
extern unsigned int UARTRXCTSDSRTransitionStatusGet(unsigned int baseAdd);

extern void UARTDMACounterResetControl(unsigned int baseAdd,
                                       unsigned int controlFlag);
extern unsigned int UARTTxFIFOFullStatusGet(unsigned int baseAdd);
extern unsigned int UARTTxFIFOLevelGet(unsigned int baseAdd);
extern unsigned int UARTRxFIFOLevelGet(unsigned int baseAdd);
extern unsigned int UARTAutobaudParityGet(unsigned int baseAdd);
extern unsigned int UARTAutobaudWordLenGet(unsigned int baseAdd);
extern unsigned int UARTAutobaudSpeedGet(unsigned int baseAdd);
extern void UARTScratchPadRegWrite(unsigned int baseAdd,
                                   unsigned int scratchValue);
extern unsigned int UARTScratchPadRegRead(unsigned int baseAdd);
extern unsigned int UARTModuleVersionNumberGet(unsigned int baseAdd);
extern void UARTFIFORegisterWrite(unsigned int baseAdd, unsigned int fcrValue);
extern void UARTTxDMAThresholdControl(unsigned int baseAdd, unsigned int thrsCtrlFlag);
extern void UARTTxDMAThresholdValConfig(unsigned int baseAdd, unsigned int thrsValue);

#ifdef __cplusplus
}
#endif

#endif

/********************************* End of File********************************/

