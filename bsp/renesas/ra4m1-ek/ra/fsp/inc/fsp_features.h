/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef FSP_FEATURES_H
#define FSP_FEATURES_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* C99 includes. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

/* Different compiler support. */
#include "fsp_common_api.h"
#include "../../fsp/src/bsp/mcu/all/bsp_compiler_support.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Available modules. */
typedef enum e_fsp_ip
{
    FSP_IP_CFLASH = 0,                 ///< Code Flash
    FSP_IP_DFLASH = 1,                 ///< Data Flash
    FSP_IP_RAM    = 2,                 ///< RAM
    FSP_IP_LVD    = 3,                 ///< Low Voltage Detection
    FSP_IP_CGC    = 3,                 ///< Clock Generation Circuit
    FSP_IP_LPM    = 3,                 ///< Low Power Modes
    FSP_IP_FCU    = 4,                 ///< Flash Control Unit
    FSP_IP_ICU    = 6,                 ///< Interrupt Control Unit
    FSP_IP_DMAC   = 7,                 ///< DMA Controller
    FSP_IP_DTC    = 8,                 ///< Data Transfer Controller
    FSP_IP_IOPORT = 9,                 ///< I/O Ports
    FSP_IP_PFS    = 10,                ///< Pin Function Select
    FSP_IP_ELC    = 11,                ///< Event Link Controller
    FSP_IP_MPU    = 13,                ///< Memory Protection Unit
    FSP_IP_MSTP   = 14,                ///< Module Stop
    FSP_IP_MMF    = 15,                ///< Memory Mirror Function
    FSP_IP_KEY    = 16,                ///< Key Interrupt Function
    FSP_IP_CAC    = 17,                ///< Clock Frequency Accuracy Measurement Circuit
    FSP_IP_DOC    = 18,                ///< Data Operation Circuit
    FSP_IP_CRC    = 19,                ///< Cyclic Redundancy Check Calculator
    FSP_IP_SCI    = 20,                ///< Serial Communications Interface
    FSP_IP_IIC    = 21,                ///< I2C Bus Interface
    FSP_IP_SPI    = 22,                ///< Serial Peripheral Interface
    FSP_IP_CTSU   = 23,                ///< Capacitive Touch Sensing Unit
    FSP_IP_SCE    = 24,                ///< Secure Cryptographic Engine
    FSP_IP_SLCDC  = 25,                ///< Segment LCD Controller
    FSP_IP_AES    = 26,                ///< Advanced Encryption Standard
    FSP_IP_TRNG   = 27,                ///< True Random Number Generator
    FSP_IP_FCACHE = 30,                ///< Flash Cache
    FSP_IP_SRAM   = 31,                ///< SRAM
    FSP_IP_ADC    = 32,                ///< A/D Converter
    FSP_IP_DAC    = 33,                ///< 12-Bit D/A Converter
    FSP_IP_TSN    = 34,                ///< Temperature Sensor
    FSP_IP_DAAD   = 35,                ///< D/A A/D Synchronous Unit
    FSP_IP_ACMPHS = 36,                ///< High Speed Analog Comparator
    FSP_IP_ACMPLP = 37,                ///< Low Power Analog Comparator
    FSP_IP_OPAMP  = 38,                ///< Operational Amplifier
    FSP_IP_SDADC  = 39,                ///< Sigma Delta A/D Converter
    FSP_IP_RTC    = 40,                ///< Real Time Clock
    FSP_IP_WDT    = 41,                ///< Watch Dog Timer
    FSP_IP_IWDT   = 42,                ///< Independent Watch Dog Timer
    FSP_IP_GPT    = 43,                ///< General PWM Timer
    FSP_IP_POEG   = 44,                ///< Port Output Enable for GPT
    FSP_IP_OPS    = 45,                ///< Output Phase Switch
    FSP_IP_AGT    = 47,                ///< Asynchronous General-Purpose Timer
    FSP_IP_CAN    = 48,                ///< Controller Area Network
    FSP_IP_IRDA   = 49,                ///< Infrared Data Association
    FSP_IP_QSPI   = 50,                ///< Quad Serial Peripheral Interface
    FSP_IP_USBFS  = 51,                ///< USB Full Speed
    FSP_IP_SDHI   = 52,                ///< SD/MMC Host Interface
    FSP_IP_SRC    = 53,                ///< Sampling Rate Converter
    FSP_IP_SSI    = 54,                ///< Serial Sound Interface
    FSP_IP_DALI   = 55,                ///< Digital Addressable Lighting Interface
    FSP_IP_ETHER  = 64,                ///< Ethernet MAC Controller
    FSP_IP_EDMAC  = 64,                ///< Ethernet DMA Controller
    FSP_IP_EPTPC  = 65,                ///< Ethernet PTP Controller
    FSP_IP_PDC    = 66,                ///< Parallel Data Capture Unit
    FSP_IP_GLCDC  = 67,                ///< Graphics LCD Controller
    FSP_IP_DRW    = 68,                ///< 2D Drawing Engine
    FSP_IP_JPEG   = 69,                ///< JPEG
    FSP_IP_DAC8   = 70,                ///< 8-Bit D/A Converter
    FSP_IP_USBHS  = 71,                ///< USB High Speed
    FSP_IP_OSPI   = 72,                ///< Octa Serial Peripheral Interface
    FSP_IP_CEC    = 73,                ///< HDMI CEC
    FSP_IP_TFU    = 74,                ///< Trigonometric Function Unit
    FSP_IP_IIRFA  = 75,                ///< IIR Filter Accelerator
    FSP_IP_CANFD  = 76,                ///< CAN-FD
    FSP_IP_ULPT   = 77,                ///< Ultra Low Power Timer ULPT
    FSP_IP_SAU    = 78,                ///< Serial Array Unit
    FSP_IP_IICA   = 79,                ///< Serial Interface IICA
    FSP_IP_UARTA  = 80,                ///< Serial Interface UARTA
    FSP_IP_TAU    = 81,                ///< Timer Array Unit
    FSP_IP_TML    = 82,                ///< 32-bit Interval Timer
    FSP_IP_MACL   = 83,                ///< 32-bit Multiply-Accumulator
    FSP_IP_USBCC  = 84,                ///< USB Type-C Controller
} fsp_ip_t;

/** Signals that can be mapped to an interrupt. */
typedef enum e_fsp_signal
{
    FSP_SIGNAL_ADC_COMPARE_MATCH = 0,             ///< ADC COMPARE MATCH
    FSP_SIGNAL_ADC_COMPARE_MISMATCH,              ///< ADC COMPARE MISMATCH
    FSP_SIGNAL_ADC_SCAN_END,                      ///< ADC SCAN END
    FSP_SIGNAL_ADC_SCAN_END_B,                    ///< ADC SCAN END B
    FSP_SIGNAL_ADC_WINDOW_A,                      ///< ADC WINDOW A
    FSP_SIGNAL_ADC_WINDOW_B,                      ///< ADC WINDOW B
    FSP_SIGNAL_AES_RDREQ = 0,                     ///< AES RDREQ
    FSP_SIGNAL_AES_WRREQ,                         ///< AES WRREQ
    FSP_SIGNAL_AGT_COMPARE_A = 0,                 ///< AGT COMPARE A
    FSP_SIGNAL_AGT_COMPARE_B,                     ///< AGT COMPARE B
    FSP_SIGNAL_AGT_INT,                           ///< AGT INT
    FSP_SIGNAL_CAC_FREQUENCY_ERROR = 0,           ///< CAC FREQUENCY ERROR
    FSP_SIGNAL_CAC_MEASUREMENT_END,               ///< CAC MEASUREMENT END
    FSP_SIGNAL_CAC_OVERFLOW,                      ///< CAC OVERFLOW
    FSP_SIGNAL_CAN_ERROR = 0,                     ///< CAN ERROR
    FSP_SIGNAL_CAN_FIFO_RX,                       ///< CAN FIFO RX
    FSP_SIGNAL_CAN_FIFO_TX,                       ///< CAN FIFO TX
    FSP_SIGNAL_CAN_MAILBOX_RX,                    ///< CAN MAILBOX RX
    FSP_SIGNAL_CAN_MAILBOX_TX,                    ///< CAN MAILBOX TX
    FSP_SIGNAL_CGC_MOSC_STOP = 0,                 ///< CGC MOSC STOP
    FSP_SIGNAL_LPM_SNOOZE_REQUEST,                ///< LPM SNOOZE REQUEST
    FSP_SIGNAL_LVD_LVD1,                          ///< LVD LVD1
    FSP_SIGNAL_LVD_LVD2,                          ///< LVD LVD2
    FSP_SIGNAL_VBATT_LVD,                         ///< VBATT LVD
    FSP_SIGNAL_LVD_VBATT  = FSP_SIGNAL_VBATT_LVD, ///< LVD VBATT
    FSP_SIGNAL_ACMPHS_INT = 0,                    ///< ACMPHS INT
    FSP_SIGNAL_ACMPLP_INT = 0,                    ///< ACMPLP INT
    FSP_SIGNAL_CTSU_END   = 0,                    ///< CTSU END
    FSP_SIGNAL_CTSU_READ,                         ///< CTSU READ
    FSP_SIGNAL_CTSU_WRITE,                        ///< CTSU WRITE
    FSP_SIGNAL_DALI_DEI = 0,                      ///< DALI DEI
    FSP_SIGNAL_DALI_CLI,                          ///< DALI CLI
    FSP_SIGNAL_DALI_SDI,                          ///< DALI SDI
    FSP_SIGNAL_DALI_BPI,                          ///< DALI BPI
    FSP_SIGNAL_DALI_FEI,                          ///< DALI FEI
    FSP_SIGNAL_DALI_SDI_OR_BPI,                   ///< DALI SDI OR BPI
    FSP_SIGNAL_DMAC_INT     = 0,                  ///< DMAC INT
    FSP_SIGNAL_DOC_INT      = 0,                  ///< DOC INT
    FSP_SIGNAL_DRW_INT      = 0,                  ///< DRW INT
    FSP_SIGNAL_DTC_COMPLETE = 0,                  ///< DTC COMPLETE
    FSP_SIGNAL_DTC_END,                           ///< DTC END
    FSP_SIGNAL_EDMAC_EINT           = 0,          ///< EDMAC EINT
    FSP_SIGNAL_ELC_SOFTWARE_EVENT_0 = 0,          ///< ELC SOFTWARE EVENT 0
    FSP_SIGNAL_ELC_SOFTWARE_EVENT_1,              ///< ELC SOFTWARE EVENT 1
    FSP_SIGNAL_EPTPC_IPLS = 0,                    ///< EPTPC IPLS
    FSP_SIGNAL_EPTPC_MINT,                        ///< EPTPC MINT
    FSP_SIGNAL_EPTPC_PINT,                        ///< EPTPC PINT
    FSP_SIGNAL_EPTPC_TIMER0_FALL,                 ///< EPTPC TIMER0 FALL
    FSP_SIGNAL_EPTPC_TIMER0_RISE,                 ///< EPTPC TIMER0 RISE
    FSP_SIGNAL_EPTPC_TIMER1_FALL,                 ///< EPTPC TIMER1 FALL
    FSP_SIGNAL_EPTPC_TIMER1_RISE,                 ///< EPTPC TIMER1 RISE
    FSP_SIGNAL_EPTPC_TIMER2_FALL,                 ///< EPTPC TIMER2 FALL
    FSP_SIGNAL_EPTPC_TIMER2_RISE,                 ///< EPTPC TIMER2 RISE
    FSP_SIGNAL_EPTPC_TIMER3_FALL,                 ///< EPTPC TIMER3 FALL
    FSP_SIGNAL_EPTPC_TIMER3_RISE,                 ///< EPTPC TIMER3 RISE
    FSP_SIGNAL_EPTPC_TIMER4_FALL,                 ///< EPTPC TIMER4 FALL
    FSP_SIGNAL_EPTPC_TIMER4_RISE,                 ///< EPTPC TIMER4 RISE
    FSP_SIGNAL_EPTPC_TIMER5_FALL,                 ///< EPTPC TIMER5 FALL
    FSP_SIGNAL_EPTPC_TIMER5_RISE,                 ///< EPTPC TIMER5 RISE
    FSP_SIGNAL_FCU_FIFERR = 0,                    ///< FCU FIFERR
    FSP_SIGNAL_FCU_FRDYI,                         ///< FCU FRDYI
    FSP_SIGNAL_GLCDC_LINE_DETECT = 0,             ///< GLCDC LINE DETECT
    FSP_SIGNAL_GLCDC_UNDERFLOW_1,                 ///< GLCDC UNDERFLOW 1
    FSP_SIGNAL_GLCDC_UNDERFLOW_2,                 ///< GLCDC UNDERFLOW 2
    FSP_SIGNAL_GPT_CAPTURE_COMPARE_A = 0,         ///< GPT CAPTURE COMPARE A
    FSP_SIGNAL_GPT_CAPTURE_COMPARE_B,             ///< GPT CAPTURE COMPARE B
    FSP_SIGNAL_GPT_COMPARE_C,                     ///< GPT COMPARE C
    FSP_SIGNAL_GPT_COMPARE_D,                     ///< GPT COMPARE D
    FSP_SIGNAL_GPT_COMPARE_E,                     ///< GPT COMPARE E
    FSP_SIGNAL_GPT_COMPARE_F,                     ///< GPT COMPARE F
    FSP_SIGNAL_GPT_COUNTER_OVERFLOW,              ///< GPT COUNTER OVERFLOW
    FSP_SIGNAL_GPT_COUNTER_UNDERFLOW,             ///< GPT COUNTER UNDERFLOW
    FSP_SIGNAL_GPT_AD_TRIG_A,                     ///< GPT AD TRIG A
    FSP_SIGNAL_GPT_AD_TRIG_B,                     ///< GPT AD TRIG B
    FSP_SIGNAL_OPS_UVW_EDGE,                      ///< OPS UVW EDGE
    FSP_SIGNAL_ICU_IRQ0 = 0,                      ///< ICU IRQ0
    FSP_SIGNAL_ICU_IRQ1,                          ///< ICU IRQ1
    FSP_SIGNAL_ICU_IRQ2,                          ///< ICU IRQ2
    FSP_SIGNAL_ICU_IRQ3,                          ///< ICU IRQ3
    FSP_SIGNAL_ICU_IRQ4,                          ///< ICU IRQ4
    FSP_SIGNAL_ICU_IRQ5,                          ///< ICU IRQ5
    FSP_SIGNAL_ICU_IRQ6,                          ///< ICU IRQ6
    FSP_SIGNAL_ICU_IRQ7,                          ///< ICU IRQ7
    FSP_SIGNAL_ICU_IRQ8,                          ///< ICU IRQ8
    FSP_SIGNAL_ICU_IRQ9,                          ///< ICU IRQ9
    FSP_SIGNAL_ICU_IRQ10,                         ///< ICU IRQ10
    FSP_SIGNAL_ICU_IRQ11,                         ///< ICU IRQ11
    FSP_SIGNAL_ICU_IRQ12,                         ///< ICU IRQ12
    FSP_SIGNAL_ICU_IRQ13,                         ///< ICU IRQ13
    FSP_SIGNAL_ICU_IRQ14,                         ///< ICU IRQ14
    FSP_SIGNAL_ICU_IRQ15,                         ///< ICU IRQ15
    FSP_SIGNAL_ICU_SNOOZE_CANCEL,                 ///< ICU SNOOZE CANCEL
    FSP_SIGNAL_IIC_ERI = 0,                       ///< IIC ERI
    FSP_SIGNAL_IIC_RXI,                           ///< IIC RXI
    FSP_SIGNAL_IIC_TEI,                           ///< IIC TEI
    FSP_SIGNAL_IIC_TXI,                           ///< IIC TXI
    FSP_SIGNAL_IIC_WUI,                           ///< IIC WUI
    FSP_SIGNAL_IOPORT_EVENT_1 = 0,                ///< IOPORT EVENT 1
    FSP_SIGNAL_IOPORT_EVENT_2,                    ///< IOPORT EVENT 2
    FSP_SIGNAL_IOPORT_EVENT_3,                    ///< IOPORT EVENT 3
    FSP_SIGNAL_IOPORT_EVENT_4,                    ///< IOPORT EVENT 4
    FSP_SIGNAL_IOPORT_EVENT_B = 0,                ///< IOPORT EVENT B
    FSP_SIGNAL_IOPORT_EVENT_C,                    ///< IOPORT EVENT C
    FSP_SIGNAL_IOPORT_EVENT_D,                    ///< IOPORT EVENT D
    FSP_SIGNAL_IOPORT_EVENT_E,                    ///< IOPORT EVENT E
    FSP_SIGNAL_IWDT_UNDERFLOW = 0,                ///< IWDT UNDERFLOW
    FSP_SIGNAL_JPEG_JDTI      = 0,                ///< JPEG JDTI
    FSP_SIGNAL_JPEG_JEDI,                         ///< JPEG JEDI
    FSP_SIGNAL_KEY_INT       = 0,                 ///< KEY INT
    FSP_SIGNAL_PDC_FRAME_END = 0,                 ///< PDC FRAME END
    FSP_SIGNAL_PDC_INT,                           ///< PDC INT
    FSP_SIGNAL_PDC_RECEIVE_DATA_READY,            ///< PDC RECEIVE DATA READY
    FSP_SIGNAL_POEG_EVENT = 0,                    ///< POEG EVENT
    FSP_SIGNAL_QSPI_INT   = 0,                    ///< QSPI INT
    FSP_SIGNAL_RTC_ALARM  = 0,                    ///< RTC ALARM
    FSP_SIGNAL_RTC_PERIOD,                        ///< RTC PERIOD
    FSP_SIGNAL_RTC_CARRY,                         ///< RTC CARRY
    FSP_SIGNAL_SCE_INTEGRATE_RDRDY = 0,           ///< SCE INTEGRATE RDRDY
    FSP_SIGNAL_SCE_INTEGRATE_WRRDY,               ///< SCE INTEGRATE WRRDY
    FSP_SIGNAL_SCE_LONG_PLG,                      ///< SCE LONG PLG
    FSP_SIGNAL_SCE_PROC_BUSY,                     ///< SCE PROC BUSY
    FSP_SIGNAL_SCE_RDRDY_0,                       ///< SCE RDRDY 0
    FSP_SIGNAL_SCE_RDRDY_1,                       ///< SCE RDRDY 1
    FSP_SIGNAL_SCE_ROMOK,                         ///< SCE ROMOK
    FSP_SIGNAL_SCE_TEST_BUSY,                     ///< SCE TEST BUSY
    FSP_SIGNAL_SCE_WRRDY_0,                       ///< SCE WRRDY 0
    FSP_SIGNAL_SCE_WRRDY_1,                       ///< SCE WRRDY 1
    FSP_SIGNAL_SCE_WRRDY_4,                       ///< SCE WRRDY 4
    FSP_SIGNAL_SCI_AM = 0,                        ///< SCI AM
    FSP_SIGNAL_SCI_ERI,                           ///< SCI ERI
    FSP_SIGNAL_SCI_RXI,                           ///< SCI RXI
    FSP_SIGNAL_SCI_RXI_OR_ERI,                    ///< SCI RXI OR ERI
    FSP_SIGNAL_SCI_TEI,                           ///< SCI TEI
    FSP_SIGNAL_SCI_TXI,                           ///< SCI TXI
    FSP_SIGNAL_SDADC_ADI = 0,                     ///< SDADC ADI
    FSP_SIGNAL_SDADC_SCANEND,                     ///< SDADC SCANEND
    FSP_SIGNAL_SDADC_CALIEND,                     ///< SDADC CALIEND
    FSP_SIGNAL_SDHIMMC_ACCS = 0,                  ///< SDHIMMC ACCS
    FSP_SIGNAL_SDHIMMC_CARD,                      ///< SDHIMMC CARD
    FSP_SIGNAL_SDHIMMC_DMA_REQ,                   ///< SDHIMMC DMA REQ
    FSP_SIGNAL_SDHIMMC_SDIO,                      ///< SDHIMMC SDIO
    FSP_SIGNAL_SPI_ERI = 0,                       ///< SPI ERI
    FSP_SIGNAL_SPI_IDLE,                          ///< SPI IDLE
    FSP_SIGNAL_SPI_RXI,                           ///< SPI RXI
    FSP_SIGNAL_SPI_TEI,                           ///< SPI TEI
    FSP_SIGNAL_SPI_TXI,                           ///< SPI TXI
    FSP_SIGNAL_SRC_CONVERSION_END = 0,            ///< SRC CONVERSION END
    FSP_SIGNAL_SRC_INPUT_FIFO_EMPTY,              ///< SRC INPUT FIFO EMPTY
    FSP_SIGNAL_SRC_OUTPUT_FIFO_FULL,              ///< SRC OUTPUT FIFO FULL
    FSP_SIGNAL_SRC_OUTPUT_FIFO_OVERFLOW,          ///< SRC OUTPUT FIFO OVERFLOW
    FSP_SIGNAL_SRC_OUTPUT_FIFO_UNDERFLOW,         ///< SRC OUTPUT FIFO UNDERFLOW
    FSP_SIGNAL_SSI_INT = 0,                       ///< SSI INT
    FSP_SIGNAL_SSI_RXI,                           ///< SSI RXI
    FSP_SIGNAL_SSI_TXI,                           ///< SSI TXI
    FSP_SIGNAL_SSI_TXI_RXI,                       ///< SSI TXI RXI
    FSP_SIGNAL_TRNG_RDREQ = 0,                    ///< TRNG RDREQ
    FSP_SIGNAL_USB_FIFO_0 = 0,                    ///< USB FIFO 0
    FSP_SIGNAL_USB_FIFO_1,                        ///< USB FIFO 1
    FSP_SIGNAL_USB_INT,                           ///< USB INT
    FSP_SIGNAL_USB_RESUME,                        ///< USB RESUME
    FSP_SIGNAL_USB_USB_INT_RESUME,                ///< USB USB INT RESUME
    FSP_SIGNAL_WDT_UNDERFLOW  = 0,                ///< WDT UNDERFLOW
    FSP_SIGNAL_ULPT_COMPARE_A = 0,                ///< ULPT COMPARE A
    FSP_SIGNAL_ULPT_COMPARE_B,                    ///< ULPT COMPARE B
    FSP_SIGNAL_ULPT_INT,                          ///< ULPT INT
} fsp_signal_t;

typedef void (* fsp_vector_t)(void);

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
