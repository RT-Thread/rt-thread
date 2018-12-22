//*****************************************************************************
//
//  am_hal_uart.h
//! @file
//!
//! @brief Functions for accessing and configuring the UART.
//!
//! @addtogroup uart2 UART
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_HAL_UART_H
#define AM_HAL_UART_H

//*****************************************************************************
//
//! @name UART Interrupts
//! @brief Macro definitions for UART FIFO levels.
//!
//! They may be used with the \e am_hal_uart_fifo_config() function.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_UART_INT_OVER_RUN            AM_REG_UART_IER_OEIM_M
#define AM_HAL_UART_INT_BREAK_ERR           AM_REG_UART_IER_BEIM_M
#define AM_HAL_UART_INT_PARITY_ERR          AM_REG_UART_IER_PEIM_M
#define AM_HAL_UART_INT_FRAME_ERR           AM_REG_UART_IER_FEIM_M
#define AM_HAL_UART_INT_RX_TMOUT            AM_REG_UART_IER_RTIM_M
#define AM_HAL_UART_INT_TX                  AM_REG_UART_IER_TXIM_M
#define AM_HAL_UART_INT_RX                  AM_REG_UART_IER_RXIM_M
#define AM_HAL_UART_INT_DSRM                AM_REG_UART_IER_DSRMIM_M
#define AM_HAL_UART_INT_DCDM                AM_REG_UART_IER_DCDMIM_M
#define AM_HAL_UART_INT_CTSM                AM_REG_UART_IER_CTSMIM_M
#define AM_HAL_UART_INT_TXCMP               AM_REG_UART_IER_TXCMPMIM_M
//! @}

//*****************************************************************************
//
//! @name UART FIFO Levels
//! @brief Macro definitions for RTV interrupt status bits.
//!
//! These macros correspond to the bits in the UART interrupt status register.
//! They may be used with any of the \e am_hal_uart_int_x() functions.
//!
//! @{
//
//*****************************************************************************
//TX
#define AM_HAL_UART_TX_FIFO_1_8             AM_REG_UART_IFLS_TXIFLSEL(0)
#define AM_HAL_UART_TX_FIFO_1_4             AM_REG_UART_IFLS_TXIFLSEL(1)
#define AM_HAL_UART_TX_FIFO_1_2             AM_REG_UART_IFLS_TXIFLSEL(2)
#define AM_HAL_UART_TX_FIFO_3_4             AM_REG_UART_IFLS_TXIFLSEL(3)
#define AM_HAL_UART_TX_FIFO_7_8             AM_REG_UART_IFLS_TXIFLSEL(4)
// RX
#define AM_HAL_UART_RX_FIFO_1_8             AM_REG_UART_IFLS_RXIFLSEL(0)
#define AM_HAL_UART_RX_FIFO_1_4             AM_REG_UART_IFLS_RXIFLSEL(1)
#define AM_HAL_UART_RX_FIFO_1_2             AM_REG_UART_IFLS_RXIFLSEL(2)
#define AM_HAL_UART_RX_FIFO_3_4             AM_REG_UART_IFLS_RXIFLSEL(3)
#define AM_HAL_UART_RX_FIFO_7_8             AM_REG_UART_IFLS_RXIFLSEL(4)
//! @}

//*****************************************************************************
//
//! @name UART Status Register
//! @brief Macro definitions for UART Status Register Bits.
//!
//! They may be used with the \e am_hal_uart_status_get() function.
//!
//! @{
//
//*****************************************************************************
// This is the overrun error indicator.
#define AM_HAL_UART_RSR_OVERRUN_NOERR       AM_REG_UART_RSR_OESTAT_NOERR
#define AM_HAL_UART_RSR_OVERRUN_ERROR       AM_REG_UART_RSR_OESTAT_ERR

// This is the break error indicator.
#define AM_HAL_UART_RSR_BREAK_NOERR         AM_REG_UART_RSR_BESTAT_NOERR
#define AM_HAL_UART_RSR_BREAK_ERROR         AM_REG_UART_RSR_BESTAT_ERR

// This is the parity error indicator.
#define AM_HAL_UART_RSR_PARITY_NOERR        AM_REG_UART_RSR_PESTAT_NOERR
#define AM_HAL_UART_RSR_PARITY_ERROR        AM_REG_UART_RSR_PESTAT_ERR

// This is the framing error indicator.
#define AM_HAL_UART_RSR_FRAME_ERROR_NOERR   AM_REG_UART_RSR_FESTAT_NOERR
#define AM_HAL_UART_RSR_FRAME_ERROR_ERROR   AM_REG_UART_RSR_FESTAT_ERR
//! @}

//*****************************************************************************
//
//! @name UART Flag Register
//! @brief Macro definitions for UART Flag Register Bits.
//!
//! They may be used with the \e am_hal_uart_flags_get() function.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_UART_FR_RING                 AM_REG_UART_FR_RI_M
#define AM_HAL_UART_FR_TX_EMPTY             AM_REG_UART_FR_TXFE_XMTFIFO_EMPTY
#define AM_HAL_UART_FR_RX_FULL              AM_REG_UART_FR_RXFF_RCVFIFO_FULL
#define AM_HAL_UART_FR_TX_FULL              AM_REG_UART_FR_TXFF_XMTFIFO_FULL
#define AM_HAL_UART_FR_RX_EMPTY             AM_REG_UART_FR_RXFE_RCVFIFO_EMPTY
#define AM_HAL_UART_FR_BUSY                 AM_REG_UART_FR_BUSY_BUSY
#define AM_HAL_UART_FR_DCD_DETECTED         AM_REG_UART_FR_DCD_DETECTED
#define AM_HAL_UART_FR_DSR_READY            AM_REG_UART_FR_DSR_READY
#define AM_HAL_UART_FR_CTS                  AM_REG_UART_FR_CTS_M
//! @}


//*****************************************************************************
//
//! @name UART Config Macros
//! @brief Macro definitions for available Data bits.
//!
//! They may be used with the \e am_hal_uart_config_t structure used by \e
//! am_hal_uart_config().
//!
//! @{
//
//*****************************************************************************
//*****************************************************************************
//
// Data bits defines.
//
//*****************************************************************************
#define AM_HAL_UART_DATA_BITS_8             AM_REG_UART_LCRH_WLEN(3)
#define AM_HAL_UART_DATA_BITS_7             AM_REG_UART_LCRH_WLEN(2)
#define AM_HAL_UART_DATA_BITS_6             AM_REG_UART_LCRH_WLEN(1)
#define AM_HAL_UART_DATA_BITS_5             0

//*****************************************************************************
//
// Parity defines.
//
//*****************************************************************************
#define AM_HAL_UART_PARITY_NONE             0
#define AM_HAL_UART_PARITY_ODD              AM_REG_UART_LCRH_PEN_M
#define AM_HAL_UART_PARITY_EVEN             AM_REG_UART_LCRH_PEN_M |       \
                                            AM_REG_UART_LCRH_EPS_M

//*****************************************************************************
//
// Flow control defines.
//
//*****************************************************************************
#define AM_HAL_UART_FLOW_CTRL_NONE          0
#define AM_HAL_UART_FLOW_CTRL_RTS_CTS       AM_REG_UART_CR_CTSEN_M |       \
                                            AM_REG_UART_CR_RTSEN_M
//! @}

//*****************************************************************************
//
//! UART configuration structure
//
//*****************************************************************************
typedef struct
{
    //
    //! Desired Baudrate for the UART.
    //
    uint32_t ui32BaudRate;

    //
    //! Number of data bits.
    //!
    //! Valid values for ui32DataBits are:
    //!
    //!     AM_HAL_UART_DATA_BITS_8
    //!     AM_HAL_UART_DATA_BITS_7
    //!     AM_HAL_UART_DATA_BITS_6
    //!     AM_HAL_UART_DATA_BITS_5
    //
    uint32_t ui32DataBits;

    //
    //! Use two stop bits.
    //
    bool bTwoStopBits;

    //
    //! Parity.
    //!
    //! Valid values for ui32Parity are:
    //!
    //!     AM_HAL_UART_PARITY_NONE
    //!     AM_HAL_UART_PARITY_ODD
    //!     AM_HAL_UART_PARITY_EVEN
    //
    uint32_t ui32Parity;

    //
    //! Flow control.
    //!
    //! Valid values for ui32FlowCtrl are:
    //!
    //!     AM_HAL_UART_FLOW_CTRL_NONE
    //!     AM_HAL_UART_FLOW_CTRL_RTS_CTS
    //
    uint32_t ui32FlowCtrl;
}
am_hal_uart_config_t;

//*****************************************************************************
//
// Structure for containing information about the UART's configuration while
// it is powered down.
//
//*****************************************************************************
typedef struct
{
    uint32_t ILPR;
    uint32_t IBRD;
    uint32_t FBRD;
    uint32_t LCRH;
    uint32_t CR;
    uint32_t IFLS;
    uint32_t IER;
    uint32_t UARTEN;
    uint32_t bValid;
}
am_hal_uart_pwrsave_t;

//*****************************************************************************
//
// Global Variables
//
//*****************************************************************************
extern am_hal_uart_pwrsave_t am_hal_uart_pwrsave[AM_REG_UART_NUM_MODULES];

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_uart_pwrctrl_enable(uint32_t ui32Module);
extern void am_hal_uart_pwrctrl_disable(uint32_t ui32Module);
extern void am_hal_uart_power_on_restore(uint32_t ui32Module);
extern void am_hal_uart_power_off_save(uint32_t ui32Module);
extern void am_hal_uart_config(uint32_t ui32Module,
                               am_hal_uart_config_t *psConfig);
extern uint32_t am_hal_uart_status_get(uint32_t ui32Module);
extern uint32_t am_hal_uart_int_status_get(uint32_t ui32Module,
                                           bool bEnabledOnly);
extern void am_hal_uart_int_clear(uint32_t ui32Module,
                                  uint32_t ui32Interrupt);
extern void am_hal_uart_int_disable(uint32_t ui32Module,
                                    uint32_t ui32Interrupt);
extern void am_hal_uart_int_enable(uint32_t ui32Module,
                                   uint32_t ui32Interrupt);
extern uint32_t am_hal_uart_int_enable_get(uint32_t ui32Module);
extern void am_hal_uart_enable(uint32_t ui32Module);
extern void am_hal_uart_disable(uint32_t ui32Module);
extern void am_hal_uart_clock_enable(uint32_t ui32Module);
extern void am_hal_uart_clock_disable(uint32_t ui32Module);
extern void am_hal_uart_fifo_config(uint32_t ui32Module, uint32_t ui32LvlCfg);
extern uint32_t am_hal_uart_flags_get(uint32_t ui32Module);

// rx/tx polled
extern void am_hal_uart_char_transmit_polled(uint32_t ui32Module,
                                             char cChar);
extern void am_hal_uart_string_transmit_polled(uint32_t ui32Module,
                                               char *pcString);
extern void am_hal_uart_char_receive_polled(uint32_t ui32Module,
                                            char *pcChar);
extern void am_hal_uart_line_receive_polled(uint32_t ui32Module,
                                            uint32_t ui32MaxChars,
                                            char *pcChar);

// rx/tx buffered
extern void am_hal_uart_init_buffered(uint32_t ui32Module,
                                      uint8_t *pui8RxArray,
                                      uint32_t ui32RxSize,
                                      uint8_t *pui8TxArray,
                                      uint32_t ui32TxSize);
extern void am_hal_uart_get_status_buffered(uint32_t ui32Module,
                          uint32_t *pui32RxSize,
                          uint32_t *pui32TxSize);
extern void am_hal_uart_service_buffered(uint32_t ui32Module,
                                         uint32_t ui32Status);

extern void am_hal_uart_service_buffered_timeout_save(uint32_t ui32Module,
                                                      uint32_t ui32Status);
extern void am_hal_uart_char_transmit_buffered(uint32_t ui32Module,
                                               char cChar);
extern void am_hal_uart_string_transmit_buffered(uint32_t ui32Module,
                                                 char *pcString);
extern uint32_t am_hal_uart_char_receive_buffered(uint32_t ui32Module,
                                                  char *pcString,
                                                  uint32_t ui32MaxChars);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_UART_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
