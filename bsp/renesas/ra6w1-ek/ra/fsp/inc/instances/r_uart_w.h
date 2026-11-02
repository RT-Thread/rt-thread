/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_UART_W_H
#define R_UART_W_H

/*******************************************************************************************************************//**
 * @addtogroup UART_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_uart_api.h"
#include "r_uart_w_cfg.h"
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
  #include "FreeRTOS.h"
  #include "event_groups.h"
 #endif
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DEFAULT_UART_W_IRQ_PRIORITY    5

#if !BSP_MCU_GROUP_RA6W1
 #define UART1_CHANNEL_NUM             0
 #define UART2_CHANNEL_NUM             1
 #define UART3_CHANNEL_NUM             2
 #define UART4_CHANNEL_NUM             3
#endif

#if (BSP_FEATURE_UART_W_VALID_CHANNEL_MASK & 0x1)
 #define UART_W_CHANNEL_OFFSET         0
#elif (BSP_FEATURE_UART_W_VALID_CHANNEL_MASK & 0x2)
 #define UART_W_CHANNEL_OFFSET         1
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** UART flow control mode definition */
typedef enum e_uart_w_auto_flow_control
{
    UART_W_AUTO_FLOW_CONTROL_DISABLED = 0, ///< Disable auto flow control
    UART_W_AUTO_FLOW_CONTROL_ENABLED  = 1, ///< Enable auto flow control
} uart_w_auto_flow_control_t;

typedef enum e_uart_w_loop_back
{
    UART_W_LOOP_BACK_DISABLE = 0,      ///< Disable loop back
    UART_W_LOOP_BACK_ENABLE  = 1,      ///< Enable loop back
} uart_w_loop_back_t;

typedef enum e_uart_w_fifo_enable
{
    UART_W_FIFO_DISABLE = 0,           ///< Disable fifo
    UART_W_FIFO_ENABLE  = 1,           ///< Enable fifo
} uart_w_fifo_enable_t;

typedef enum e_uart_w_extended_data_bits
{
    UART_W_EXTENDED_DATA_BITS_DISABLE = 0, ///< Disable extended word length configuration
    UART_W_EXTENDED_DATA_BITS_ENABLE  = 1, ///< Enable extended word length configuration
} uart_w_extended_data_bits_t;

/** UART Data bit length definition */
typedef enum e_uart_w_data_bits
{
    UART_W_DATA_BITS_5 = 0U,           ///< Data bits 5-bit
    UART_W_DATA_BITS_6 = 1U,           ///< Data bits 6-bit
    UART_W_DATA_BITS_7 = 2U,           ///< Data bits 7-bit
    UART_W_DATA_BITS_8 = 3U,           ///< Data bits 8-bit
} uart_w_data_bits_t;

/** Receive FIFO trigger configuration. */
typedef enum e_uart_w_rx_fifo_trigger
{
    UART_W_RX_FIFO_TRIGGER_EIGHTH         = 0x0, ///< Received Data Available Interrupt when FIFO is 1/8 full
    UART_W_RX_FIFO_TRIGGER_QUARTER        = 0x1, ///< Received Data Available Interrupt when FIFO is 1/4 full
    UART_W_RX_FIFO_TRIGGER_HALF           = 0x2, ///< Received Data Available Interrupt when FIFO is 1/2 full
    UART_W_RX_FIFO_TRIGGER_THREE_QUARTERS = 0x3, ///< Received Data Available Interrupt when FIFO is 3/4 full
    UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS  = 0x4, ///< Received Data Available Interrupt when FIFO is 7/8 full
} uart_w_rx_fifo_trigger_t;

/** Transmit FIFO trigger configuration. */
typedef enum e_uart_w_tx_fifo_trigger
{
    UART_W_TX_FIFO_TRIGGER_EIGHTH         = 0x0, ///< Transmit Data Interrupt when FIFO is 1/8 full
    UART_W_TX_FIFO_TRIGGER_QUARTER        = 0x1, ///< Transmit Data Interrupt when FIFO is 1/4 full
    UART_W_TX_FIFO_TRIGGER_HALF           = 0x2, ///< Transmit Data Interrupt when FIFO is 1/2 full
    UART_W_TX_FIFO_TRIGGER_THREE_QUARTERS = 0x3, ///< Transmit Data Interrupt when FIFO is 3/4 full
    UART_W_TX_FIFO_TRIGGER_SEVEN_EIGHTHS  = 0x4, ///< Transmit Data Interrupt when FIFO is 7/8 full
} uart_w_tx_fifo_trigger_t;

/** RS-485 Enable/Disable. */
typedef enum e_uart_w_rs485_enable
{
    UART_W_RS485_DISABLE = 0,          ///< RS-485 disabled.
    UART_W_RS485_ENABLE  = 1,          ///< RS-485 enabled.
} uart_w_rs485_enable_t;

/** UART channel control block. */
typedef struct st_uart_w_instance_ctrl
{
    /* Parameters to control UART peripheral device */
    /* FIFO depth of the UART channel */
    uint8_t fifo_depth;

    /* Used to determine if the channel is configured */
    uint32_t open;

    /* Source buffer pointer used to fill hardware FIFO from transmit ISR. */
    uint8_t const * p_tx_src;

    /* Size of source buffer pointer used to fill hardware FIFO from transmit ISR. */
    uint32_t tx_src_bytes;

    /* Destination buffer pointer used for receiving data. */
    uint8_t * p_rx_dest;

    /* Size of destination buffer pointer used for receiving data. */
    uint32_t rx_dest_bytes;

    /* Pointer to the configuration block. */
    uart_cfg_t const * p_cfg;

    /* Base register for this channel */
    UART_Type * p_reg;

    /* Pointer to callback that is called when a uart_event_t occurs. */
    void (* p_callback)(uart_callback_args_t *);

    /* Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory. */
    uart_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR

    /* Timer handler for uart tx completion */
    TimerHandle_t uart_tx_done_timer;

    /* Flag that indicates that uart trnsmition is ongoing */
    bool tx_onging_flag;
 #endif
#endif
} uart_w_instance_ctrl_t;

/** Register settings to achieve a desired baud rate and modulation duty. */
typedef struct st_uart_w_baud_setting_t
{
    uint32_t fra_baud;                 ///< Baud rate fractional part
    uint32_t int_baud;                 ///< Baud rate integer part
} uart_w_baud_setting_t;

/** UART on SCI device Configuration */
typedef struct st_uart_w_extended_cfg
{
    uart_w_baud_setting_t    * p_baud_setting;             ///< Register settings for a desired baud rate.
    uart_w_loop_back_t         loop_back_enable;           ///< Enable loop back.
    uart_w_fifo_enable_t       fifo_enable;                ///< Enable FIFO.
    uart_w_rx_fifo_trigger_t   rx_fifo_trigger;            ///< RX FIFO trigger level.
    uart_w_tx_fifo_trigger_t   tx_fifo_trigger;            ///< TX FIFO trigger level.
    uart_w_auto_flow_control_t flow_control;               ///< CTS/RTS function
    uart_w_rs485_enable_t      rs485_enable;               ///< RS-485 settings.
#if !BSP_MCU_GROUP_RA6W1
    uart_w_extended_data_bits_t extended_data_bits_enable; ///< Enable extended data bits configuration.
    uart_w_data_bits_t          data_bits;                 ///< Data bit length (5, 6 or 7 or 8)
    uint8_t   gen_ipl;                                     ///< Generic interrupt priority.
    IRQn_Type gen_irq;
#endif                                                     ///< Generic interrupt IRQ number.
} uart_w_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const uart_api_t g_uart_on_uart_w;

/** @endcond */

fsp_err_t R_UART_W_Open(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg);
fsp_err_t R_UART_W_Read(uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_UART_W_Write(uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
fsp_err_t R_UART_W_BaudSet(uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting);
fsp_err_t R_UART_W_InfoGet(uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info);
fsp_err_t R_UART_W_Close(uart_ctrl_t * const p_api_ctrl);
fsp_err_t R_UART_W_Abort(uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort);
fsp_err_t R_UART_W_ReadStop(uart_ctrl_t * const p_api_ctrl, uint32_t * remaining_bytes);

#if BSP_MCU_GROUP_RA6W1
fsp_err_t R_UART_W_ConfSet(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg);
fsp_err_t R_UART_W_ReceiveSuspend(uart_ctrl_t * const p_api_ctrl);
fsp_err_t R_UART_W_ReceiveResume(uart_ctrl_t * const p_api_ctrl);

#endif

fsp_err_t R_UART_W_BaudCalculate(uint32_t baudrate, uart_w_baud_setting_t * const p_baud_setting);
fsp_err_t R_UART_W_CallbackSet(uart_ctrl_t * const          p_api_ctrl,
                               void (                     * p_callback)(uart_callback_args_t *),
                               void * const                 p_context,
                               uart_callback_args_t * const p_callback_memory);
bool R_UART_W_IsWritting(uart_ctrl_t * const p_api_ctrl);
bool R_UART_W_IsOpened(uart_ctrl_t * const p_api_ctrl);

#if !BSP_MCU_GROUP_RA6W1
void hw_clk_enable_uart_w_clk(uint8_t channel);

#endif

/*******************************************************************************************************************/ /**
 * @} (end addtogroup UART_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
