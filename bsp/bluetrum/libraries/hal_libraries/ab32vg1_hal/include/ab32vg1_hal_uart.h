/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_UART_H__
#define AB32VG1_HAL_UART_H__

#include "ab32vg1_hal_def.h"

/* Exported types */
/** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/**
  * @brief UART Init Structure definition
  */

struct uart_init
{
    uint32_t baud;          /*!< This member configures the UART communication baud rate.
                                Baud Rate Register[31:16] is used to configure the rx rate.
                                Baud Rate Register[15: 0] is used to configure the tx rate.
                                The baud rate register is computed using the following formula:
                                    UARTBAUD = Fsys_clock/BaudRate-1
                                    for example: UARTBAUD= (26000000/2)/baud-1 */

    uint8_t  word_len;      /*!< Specifies the number of data bits transmitted or received in a frame.
                                This parameter can be a value of @ref UARTEx_Word_Length. */

    uint8_t  stop_bits;     /*!< Specifies the number of stop bits transmitted.
                                This parameter can be a value of @ref UART_Stop_Bits. */

    uint8_t  mode;          /*!< Specifies whether the receive or one line mode is enabled or disabled.
                                This parameter can be a value of @ref UART_Mode. */
};

/**
 * @brief UART handle struction definition
 *
 */
struct uart_handle
{
    hal_sfr_t           instance;
    struct uart_init    init;
};

/**
  * @}
  */

/* Exported constants */

/**
 * @defgroup UARTEx_Word_Length UART Word Length
 * @{
 */
#define UART_WORDLENGTH_8B                  (0x00u)         /*!< 8 bit long UART frame      */
#define UART_WORDLENGTH_9B                  (0x01u)         /*!< 9 bit long UART frame      */
/**
 * @}
 */

/**
 * @defgroup UART_Stop_Bits UART Number of Stop Bits
 * @{
 */
#define UART_STOPBITS_1                     (0x00u)         /*!< UART frame with 1 stop bit    */
#define UART_STOPBITS_2                     (0x01u)         /*!< UART frame with 2 stop bit    */
/**
 * @}
 */

/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */
#define UART_MODE_TX                        (0x00u)         /*!< TX mode                    */
#define UART_MODE_TX_RX                     (0x01u)         /*!< RX and TX mode             */
#define UART_MODE_1LINE                     (0x02u)         /*!< oneline mode             */

/**
  * @}
  */

#define UART_FLAG_RXPND                       (BIT(9))        /*!< RX one byte finish flag  */
#define UART_FLAG_TXPND                       (BIT(8))        /*!< TX one byte finish flag  */

#define UART_MODULE_ENABLE                    (BIT(0))        /*!< UART enable bit                */
#define UART_BIT9_ENABLE                      (BIT(1))        /*!< BIT9 enable bit                */
#define UART_RXIT_ENABLE                      (BIT(2))        /*!< Receive interrupt enable bit   */
#define UART_TXIT_ENABLE                      (BIT(3))        /*!< Transmit interrupt enable bit  */
#define UART_SB2_ENABLE                       (BIT(4))        /*!< Two stop bit enable bit        */
#define UART_CLK_SRC1                         (BIT(5))        /*!< Clock source select bit        */
#define UART_1LINE_ENABLE                     (BIT(6))        /*!< One-Line mode enable bit       */
#define UART_RX_ENABLE                        (BIT(7))        /*!< Receive enable bit             */

#define UART0N                                (0x00u)         /*!< Number of UART0        */
#define UART1N                                (0x01u)         /*!< Number of UART1        */
#define UART2N                                (0x02u)         /*!< Number of UART2        */

#define UART0_BASE                            ((hal_sfr_t)(&UART0CON))
#define UART1_BASE                            ((hal_sfr_t)(&UART1CON))
#define UART2_BASE                            ((hal_sfr_t)(&UART2CON))

/* Exported function */
/** @addtogroup UART_Exported_Functions UART Exported Functions
  * @{
  */

/** @addtogroup UART_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization functions */
hal_error_t hal_uart_init(struct uart_handle *huart);
void hal_uart_deinit(hal_sfr_t uartx);
void hal_uart_mspinit(struct uart_handle *huart);

/**
  * @}
  */

void hal_uart_control(hal_sfr_t uartx, uint32_t cntl, uint32_t param);
void hal_uart_write(hal_sfr_t uartx, uint8_t data);
uint8_t hal_uart_read(hal_sfr_t uartx);
uint32_t hal_uart_getflag(hal_sfr_t uartx, uint32_t flag);
void hal_uart_clrflag(hal_sfr_t uartx, uint32_t flag);

/**
  * @}
  */

/* Private function */
/** @addtogroup UART_Private_Functions UART Private Functions
  * @{
  */
void uart_config_all(struct uart_handle *huart);

/**
  * @}
  */

#endif
