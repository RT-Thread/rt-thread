/**
  ******************************************************************************
  * @file    md_UART.h
  * @brief   ES32F0271 UART Header File.
  *
  * @version V1.00.01
  * @date    04/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_UART_H__
#define __MD_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include <stdbool.h>
#include "es32f0271.h"
#include "reg_uart.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (UART1) | defined (UART2) | defined (UART3) | defined (SUART1) | defined (SUART2)

/** @defgroup UART UART
  * @brief UART micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_UART_Public_Types UART Public Init Type
  * @{
  */

typedef struct
{
  uint32_t BaudRate;                  /*!< This field defines expected Usart communication baud rate.*/

  uint32_t BitOrder;                  /*!< Specifies the MSB of data bits will be transmitted or received first.
                                           This parameter can be a value of @ref MD_UART_LCON_MSB_FIRST.*/

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref MD_UART_LCON_PS_EVEN.*/

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref MD_UART_LCON_STOP_1.*/

  uint32_t DataWidth;                 /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref MD_UART_LCON_DLS_8.*/

} md_uart_init_typedef;

/**
  * @} MD_UART_Public_Types
  */

/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Public functions -----------------------------------------------------------*/
/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_UART_Public_Constants UART Public Constants
  * @{
  */

/** @defgroup UART_BAUDRATE UART Baudrate Definitation
  * @{
  */
#define  MD_UART_BAUDRATE_1200             (1200U)                            /* baud rate=1200   bps */
#define  MD_UART_BAUDRATE_2400             (2400U)                            /* baud rate=2400   bps */
#define  MD_UART_BAUDRATE_4800             (4800U)                            /* baud rate=4800   bps */
#define  MD_UART_BAUDRATE_9600             (9600U)                            /* baud rate=9600   bps */
#define  MD_UART_BAUDRATE_19200            (19200U)                           /* baud rate=19200  bps */
#define  MD_UART_BAUDRATE_38400            (38400U)                           /* baud rate=38400  bps */
#define  MD_UART_BAUDRATE_57600            (57600U)                           /* baud rate=57600  bps */
#define  MD_UART_BAUDRATE_115200            (115200U)                          /* baud rate=115200 bps */
#define  MD_UART_BAUDRATE_230400            (230400U)                          /* baud rate=230400 bps */
#define  MD_UART_BAUDRATE_460800            (460800U)                          /* baud rate=460800 bps */
#define  MD_UART_BAUDRATE_512000            (512000U)                          /* baud rate=512000 bps */
#define  MD_UART_BAUDRATE_921600            (921600U)                          /* baud rate=921600 bps */
/**
  * @} UART_BAUDRATE UART Baudrate Definitation
  */

/** @defgroup UART_LCON UART_LCON Register
  * @{
  */
#define MD_UART_LCON_MSB_FIRST            (1U)                               /** @brief data Most significant bit first */
#define MD_UART_LCON_LSB_FIRST            (0U)                               /** @brief data Least significant bit first */
#define MD_UART_LCON_PS_EVEN              (1U)                               /** @brief data Even parity bit selection */
#define MD_UART_LCON_PS_ODD               (0U)                               /** @brief data Odd parity bit selection */
#define MD_UART_LCON_STOP_2               (1U)                               /** @brief data 2(1.5) Stop bit */
#define MD_UART_LCON_STOP_1               (0U)                               /** @brief data 2(1.5) Stop bit */
#define MD_UART_LCON_DLS_8                (0U)                               /** @brief data Date length 8  */
#define MD_UART_LCON_DLS_7                (1U)                               /** @brief data Date length 7 */
#define MD_UART_LCON_DLS_6                (2U)                               /** @brief data Date length 6  */
#define MD_UART_LCON_DLS_5                (3U)                               /** @brief data Date length 5  */
/**
  * @} UART_LCON UART_LCON Register
  */

/** @defgroup UART_MCON UART_MCON Register
  * @{
  */
#define MD_UART_MCON_ABRMOD_0             (0U)                               /** @brief data Receiver DMA disable */
#define MD_UART_MCON_ABRMOD_1             (1U)                               /** @brief data Repeat auto-baud rate detection after timeout enable */
#define MD_UART_MCON_ABRMOD_2             (2U)                               /** @brief data Repeat auto-baud rate detection after timeout disable */
#define MD_UART_MCON_RTSSET_LOW           (1U)                               /** @brief data RTSn set control bit RTSn level is 0 */
#define MD_UART_MCON_RTSSET_HIGH          (0U)                               /** @brief data RTSn set control bit RTSn level is 1 */
/**
  * @} UART_MCON UART_MCON Register
  */

/** @defgroup UART_MCON UART_MCON Register
  * @{
  */
#define MD_UART_RS485_AADINV_LOW          (0U)                               /** @brief data Low : Transfering data, High: Idle */
#define MD_UART_RS485_AADINV_HIGH         (1U)                               /** @brief data High: Transfering data, Low : Idle */
/**
  * @} UART_MCON UART_MCON Register
  */

/** @defgroup UART_FCON UART_FCON Register
  * @{
  */
#define MD_UART_FCON_TXTH_0                 (0U)                            /** @brief data Transmit FIFO trigger threshold: FIFO empty */
#define MD_UART_FCON_TXTH_2                 (1U)                            /** @brief data Transmit FIFO trigger threshold: 2 characters in the FIFO */
#define MD_UART_FCON_TXTH_4                 (2U)                            /** @brief data Transmit FIFO trigger threshold: 4 characters in the FIFO */
#define MD_UART_FCON_TXTH_8                 (3U)                            /** @brief data Transmit FIFO trigger threshold: 8 characters in the FIFO */
#define MD_UART_FCON_TFRST                  (1U)                            /** @brief data Transmitter FIFO reset */
#define MD_UART_FCON_RXTH_1                 (0U)                            /** @brief data Receive FIFO trigger threshold: 1 character in the FIFO */
#define MD_UART_FCON_RXTH_4                 (1U)                            /** @brief data Receive FIFO trigger threshold: 4 characters in the FIFO */
#define MD_UART_FCON_RXTH_8                 (2U)                            /** @brief data Receive FIFO trigger threshold: 8 characters in the FIFO */
#define MD_UART_FCON_RXTH_14                (3U)                            /** @brief data Receive FIFO trigger threshold: 14 characters in the FIFO */
#define MD_UART_FCON_RFRST                  (1U)                            /** @brief data Receive FIFO reset */
/**
  * @} UART_FCON UART_FCON Register
  */

/** 
  * @} MD_UART_Public_Constants UART Public Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_UART_Public_Macros UART Public Macros
  * @{
  */

/**
  * @brief  Read Receiver Buffer Register
  * @note   Contains the received data character.
  *         The RXBR register provides the parallel interface between the
  *         input shift register and the internal bus.
  *         When receiving with the parity enabled, the value read in the
  *         MSB bit is the received parity bit.
  * @param  UARTx UART Instance
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0x1FF
  */
__STATIC_INLINE uint16_t md_uart_get_rxbuf(UART_TypeDef *UARTx)
{
  return (uint16_t) ((READ_REG(UARTx->RXBUF))>>UART_RXBUF_RXBUF_POSS);
}

/**
  * @brief  Write Transmit buffer register
  * @note   Contains the data character to be transmitted.
  *         The TXBR register provides the parallel interface between the
  *         internal bus and the output shift register.
  *         When transmitting with the parity enabled the value written in
  *         the MSB (bit 7 or bit 8 depending on the data length) has no
  *         effect because it is replaced by the parity.
  * @param  UARTx UART Instance
  * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void md_uart_send_txbuf(UART_TypeDef *UARTx, uint8_t TxData)
{
  WRITE_REG (UARTx->TXBUF, (uint8_t)TxData);
}

/**
  * @brief  Set UARTx Baud rate register.
  * @note   This bits can only be written when the UART is disabled.
  *         (RXEN and TXEN=0 in the LCR register).
  * @param  UARTx UART Instance.
  * @param  UART buad rate value.
  * @retval None
  */
__STATIC_INLINE void md_uart_set_brr(UART_TypeDef *UARTx, uint32_t baudrate)
{
  WRITE_REG(UARTx->BRR, baudrate);
}

/**
  * @brief  Get UARTx baud rate.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @retval UARTx Baudrate.
  */
__STATIC_INLINE uint32_t md_uart_get_brr(UART_TypeDef *UARTx)
{
  return (uint32_t) (READ_REG(UARTx->BRR)>>UART_BRR_BRR_POSS);
}

/**
  * @brief  UARTx Transmitter enable.
  * @note   This bit enables the transmitter. It is set and cleared by
  *         software.
  * @param  UARTx UART Instance
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_txen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_TXEN_MSK);
}

/**
  * @brief  UARTx Transmitter disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_txen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_TXEN_MSK);
}

/**
  * @brief  Check if UART Transmitter is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_tx(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_TXEN_MSK) == (UART_LCON_TXEN_MSK));
}

/**
  * @brief  UARTx Receiver enable
  * @note   This bit enables the receiver. It is set and cleared by software.
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_lcon_rxen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_RXEN_MSK);
}

/**
  * @brief  UARTx Receiver Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_lcon_rxen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_RXEN_MSK);
}

/**
  * @brief  Check if UARTx Receiver is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_rxen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_RXEN_MSK) == (UART_LCON_RXEN_MSK));
}

/**
  * @brief  UARTx Debounce Enable.
  * @note   This bit enables the debounce. It is set and cleared by software.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_decen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_DBCEN_MSK);
}

/**
  * @brief  UART Debounce Disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_dbcen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_DBCEN_MSK);
}

/**
  * @brief  Check if UART Debounce is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_dbcen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_DBCEN_MSK) == (UART_LCON_DBCEN_MSK));
}

/**
  * @brief  Enable UARTx Break control bit.
  * @note   This is used to cause a break condition to be transmitted to the
  *         receiving device. The serial data output (Tx) is forced to the
  *         Spacing State (logic 0).
  *         This bit can only be written when the UART is disabled.
  *         (RXENand TXEN=0).
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_lcon_break(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_BREAK_MSK);
}

/**
  * @brief  Disable UARTx Break control bit.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_break(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_BREAK_MSK);
}

/**
  * @brief  Check if UARTx Break control bit is enabled.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_break(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_BREAK_MSK) == (UART_LCON_BREAK_MSK));
}

/**
  * @brief  UARTx Swap TX/RX pins.
  * @note   This allows to work in the case of a cross-wired connection to another UART.
  *         This bit can only be written when the UART is disabled (RXEN and TXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_swap(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_SWAP_MSK);
}

/**
  * @brief  UARTx Swap TX/RX pins disabl.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_disable_lcon_swap(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_SWAP_MSK);
}

/**
  * @brief  Check if UART Swap TX/RX pins is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_swap(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_SWAP_MSK) == (UART_LCON_SWAP_MSK));
}

/**
  * @brief  UARTx TX pin active level inversion.
  * @note   This allows the use of an external inverter on the TX line.
  *         This bit can only be written when the UART is disabled (RXEN and TXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_txinv(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_TXINV_MSK);
}

/**
  * @brief  UARTx TX pin active level inversion disable.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_txinv(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_TXINV_MSK);
}

/**
  * @brief  Check if UARTx TX pin active level is inverted.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_txinv(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_TXINV_MSK) == (UART_LCON_TXINV_MSK));
}

/**
  * @brief  UARTx RX pin active level inversion.
  * @note   This allows the use of an external inverter on the RX line.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_rxinv(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_RXINV_MSK);
}

/**
  * @brief  UARTx RX pin active level inversion disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_rxinv(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_RXINV_MSK);
}

/**
  * @brief  Check if UART RX pin active level is inverted.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_rxinv(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_RXINV_MSK) == (UART_LCON_RXINV_MSK));
}

/**
  * @brief  UARTx Binary data inversion.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  *         The parity bit is also inverted.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_datainv(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_RXINV_MSK);
}

/**
  * @brief  UARTx Binary data inverted disable.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_datainv(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_RXINV_MSK);
}

/**
  * @brief  Check if UARTx Binary data is inverted.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_datainv(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_DATAINV_MSK) == (UART_LCON_DATAINV_MSK));
}

/**
  * @brief  Set UARTx Most significant bit first.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @param  msb This parameter can be one of the following values:
  *         @arg @ref MD_UART_LCON_LSB_FIRST
  *         @arg @ref MD_UART_LCON_MSB_FIRST
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lcon_msb(UART_TypeDef *UARTx, uint32_t msb)
{
  MODIFY_REG(UARTx->LCON, UART_LCON_MSB_MSK, msb<<UART_LCON_MSB_POS);
}

/**
  * @brief  Get UARTx Most significant bit first bit.
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_LCON_MSB_FIRST
  *         @arg @ref MD_UART_LCON_LSB_FIRST
  */
__STATIC_INLINE uint32_t md_uart_get_lcon_msb(UART_TypeDef *UARTx)
{
  return (uint32_t)((READ_BIT(UARTx->LCON, UART_LCON_MSB_MSK))>>UART_LCON_MSB_POS);
}

/**
  * @brief  UARTx Parity bit selection.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @param  parity This parameter can be one of the following values:
  *         @arg @ref MD_UART_LCON_PS_ODD
  *         @arg @ref MD_UART_LCON_PS_EVEN
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lcon_ps(UART_TypeDef *UARTx, uint32_t parity)
{
  MODIFY_REG(UARTx->LCON, UART_LCON_PS_MSK, parity<<UART_LCON_PS_POS);
}

/**
  * @brief  Get UARTx Parity bit selection.
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_PARITY_ODD
  *         @arg @ref MD_UART_PARITY_EVEN
  */
__STATIC_INLINE uint32_t md_uart_get_lcon_ps(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->LCON, UART_LCON_PS_MSK))>>UART_LCON_PS_POS);
}

/**
  * @brief  UARTx Parity enable.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lcon_pe(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_LCON_PE_MSK);
}

/**
  * @brief  UARTx Parity disable.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lcon_pe(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_LCON_PE_MSK);
}

/**
  * @brief  Check if UARTx Parity is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lcon_pe(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LCON, UART_LCON_PE_MSK) == (UART_LCON_PE_MSK));
}

/**
  * @brief  Set UARTx Stop bit.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance.
  * @param  stop This parameter can be one of the following values:
  *         @arg @ref MD_UART_LCON_STOP_1
  *         @arg @ref MD_UART_LCON_STOP_2
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lcon_stop(UART_TypeDef *UARTx, uint32_t stop)
{
  MODIFY_REG(UARTx->LCON, UART_LCON_STOP_MSK, stop<<UART_LCON_STOP_POS);
}

/**
  * @brief  Get UARTx Stop bit.
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_LCON_STOP_1
  *         @arg @ref MD_UART_LCON_STOP_2
  */
__STATIC_INLINE uint32_t md_uart_get_lcon_stop(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->LCON, UART_LCON_STOP_MSK))>>UART_LCON_STOP_POS);
}

/**
  * @brief  UARTx Date length selection.
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0).
  * @param  UARTx UART Instance.
  * @param  width This parameter can be one of the following values:
  *         @arg @ref MD_UART_LCON_DLS_8
  *         @arg @ref MD_UART_LCON_DLS_7
  *         @arg @ref MD_UART_LCON_DLS_6
  *         @arg @ref MD_UART_LCON_DLS_5
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lcon_dls(UART_TypeDef *UARTx, uint32_t width)
{
  MODIFY_REG(UARTx->LCON, UART_LCON_DLS_MSK, width<<UART_LCON_DLS_POSS);
}

/**
  * @brief  Get UARTx data stop bit
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_LCON_DLS_8
  *         @arg @ref MD_UART_LCON_DLS_7
  *         @arg @ref MD_UART_LCON_DLS_6
  *         @arg @ref MD_UART_LCON_DLS_5
  */
__STATIC_INLINE uint32_t md_uart_get_lcon_dls(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->LCON, UART_LCON_DLS_MSK))>>UART_LCON_DLS_POSS);
}

/**
  * @brief  UARTx Transmitter DMA enable.
  * @note   This bit is set and cleared by software. This bit enables the DMA transmitter.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_txdmaen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_TXDMAEN_MSK);
}

/**
  * @brief  UARTx Transmitter DMA enable disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_txdmaen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_TXDMAEN_MSK);
}

/**
  * @brief  Check if UARTx Transmitter DMA is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_txdmaen(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->MCON, UART_MCON_TXDMAEN_MSK) == (UART_MCON_TXDMAEN_MSK));
}

/**
  * @brief  UARTx Receiver DMA enable.
  * @note   This bit is set and cleared by software. This bit enables the DMA Receiver.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_rxdmaen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_RXDMAEN_MSK);
}

/**
  * @brief  UARTx Receiver DMA disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_rxdmaen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_RXDMAEN_MSK);
}

/**
  * @brief  Check if UARTx UARTx Receiver DMA is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_rxdmaen(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->MCON, UART_MCON_RXDMAEN_MSK) == (UART_MCON_RXDMAEN_MSK));
}

/**
  * @brief  UARTx Auto baud rate detection repeat enable.
  * @note   This bit is set to enable baud rate detection repeat one more time 
  *         after the first failure of auto-baud rate detection.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_abrrept(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_MCON_ABRREPT_MSK);
}

/**
  * @brief  UARTx Auto baud rate detection repeat disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_abrrept(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_MCON_ABRREPT_MSK);
}

/**
  * @brief  Check if UARTx Auto baud rate detection repeat is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_abrrept(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_ABRREPT_MSK) == (UART_MCON_ABRREPT_MSK));
}

/**
  * @brief  Set UARTx Auto baud rate mode.
  * @note   MD_UART_MCON_ABRMOD_0: Mode 0 detect falling edge to second falling edge (detect 2 Bps).
  *         MD_UART_MCON_ABRMOD_1: Mode 1 detect falling edge to first rising edge (detect 1 Bps).
  *         MD_UART_MCON_ABRMOD_2: Mode 2 detect falling edge to first rising edge (detect 2 Bps).
  * @param  UARTx UART Instance.
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref MD_UART_MCON_ABRMOD_0
  *         @arg @ref MD_UART_MCON_ABRMOD_1
  *         @arg @ref MD_UART_MCON_ABRMOD_2
  * @retval None
  */
__STATIC_INLINE void md_uart_set_mcon_abrmod(UART_TypeDef *UARTx, uint32_t mode)
{
  MODIFY_REG(UARTx->MCON, UART_MCON_ABRMOD_MSK, mode<<UART_MCON_ABRMOD_POSS);
}

/**
  * @brief  Get UARTx Auto baud rate mode.
  * @param  UARTx UART Instance.
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_MCON_ABRMOD_0
  *         @arg @ref MD_UART_MCON_ABRMOD_1
  *         @arg @ref MD_UART_MCON_ABRMOD_2
  */
__STATIC_INLINE uint32_t md_uart_get_mcon_abrmod(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->MCON, UART_MCON_ABRMOD_MSK))>>UART_MCON_ABRMOD_POSS);
}

/**
  * @brief  UARTx Auto baud rate enable.
  * @note   This bit is set by software and cleared by hardware after the
  *         auto-baud rate finish.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_abren(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LCON, UART_MCON_ABREN_MSK);
}

/**
  * @brief  UARTx Auto baud rate disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_abren(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LCON, UART_MCON_ABREN_MSK);
}

/**
  * @brief  Check if UARTx Auto baud rate is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_abren(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_ABREN_MSK) == (UART_MCON_ABREN_MSK));
}

/**
  * @brief  UARTx break request enable.
  * @note   This bit is set by software and automatically cleared by
  *         hardware in the next clock cycle.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_bkreq(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_BKREQ_MSK);
}

/**
  * @brief  UARTx break request disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_bkreq(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_BKREQ_MSK);
}

/**
  * @brief  Check if UARTx break request is enabled
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_bkreq(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_BKREQ_MSK) == (UART_MCON_BKREQ_MSK));
}

/**
  * @brief  UARTx Half-duplex enable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_hden(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_HDEN_MSK);
}

/**
  * @brief  UARTx Half-duplex disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_hden(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_HDEN_MSK);
}

/**
  * @brief  Check if UARTx Half-duplex is enabled.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_hden(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_HDEN_MSK) == (UART_MCON_HDEN_MSK));
}

/**
  * @brief  UARTx IrDA mode enable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_iren(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_IREN_MSK);
}

/**
  * @brief  UARTx IrDA mode disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_iren(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_IREN_MSK);
}

/**
  * @brief  Check if UARTx IrDA mode is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_iren(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_IREN_MSK) == (UART_MCON_IREN_MSK));
}

/**
  * @brief  UARTx Auto flow control enable.
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_mcon_afcen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_AFCEN_MSK);
}

/**
  * @brief  UARTx Auto flow control disable.
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_mcon_afcen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_AFCEN_MSK);
}

/**
  * @brief  Check if Auto flow control is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_mcon_afcen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_AFCEN_MSK) == (UART_MCON_AFCEN_MSK));
}

/**
  * @brief  Set UARTx RTSn set control bit.
  * @note   If Auto flow control disable, user can control RTSn output level by this bit.
  *         MD_UART_MCON_RTSSET_LOW : RTSn level is 0
  *         MD_UART_MCON_RTSSET_HIGH: RTSn level is 1
  * @param  UARTx UART Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_UART_MCON_RTSSET_LOW
  *         @arg @ref MD_UART_MCON_RTSSET_HIGH
  * @retval None
  */
__STATIC_INLINE void md_uart_set_mcon_rtsset(UART_TypeDef *UARTx, uint32_t level)
{
  MODIFY_REG(UARTx->MCON, UART_MCON_RTSSET_MSK, level<<UART_MCON_RTSSET_POS);
}

/**
  * @brief  Get UARTx RTSn set control bit.
  * @param  UARTx UART Instance.
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_MCON_RTSSET_LOW : RTSn level is 0
  *         @arg @ref MD_UART_MCON_RTSSET_HIGH: RTSn level is 1
  */
__STATIC_INLINE uint32_t md_uart_get_mcon_rtsset(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->MCON, UART_MCON_RTSSET_MSK))>>UART_MCON_RTSSET_POS);
}

/**
  * @brief  UARTx LoopBack enable.
  * @note   This is used to put the UART into a diagnostic mode for test purpose. 
  *         If operating in UART mode, data on the TXD line is held high, 
  *         while serial data output is looped back to the RXD line, internally. 
  *         In this mode, all the interrupts are fully functional. 
  *         If operating in infrared mode, data on the TXD with IrDA line is held low, 
  *         while serial data output is inverted and looped back to the RXD line.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_mcon_lpbken(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->MCON, UART_MCON_LPBKEN_MSK);
}

/**
  * @brief  UARTx LoopBack disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_mcon_lpbken(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->MCON, UART_MCON_LPBKEN_MSK);
}

/**
  * @brief  Check if UARTx LoopBack is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lpbken(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->MCON, UART_MCON_LPBKEN_MSK) == (UART_MCON_LPBKEN_MSK));
}

/**
  * @brief  Set UARTx Delay value.
  * @note   Contains a direction control RTSn Delay value. This register
  *         works in conjunction with an 8-bit counter in terms of number of
  *         DIVISOR bit duration.
  * @param  UARTx UART Instance.
  * @param  UARTx Delay value.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_rs485_dly(UART_TypeDef *UARTx, uint32_t delay)
{
  MODIFY_REG(UARTx->RS485, UART_RS485_DLY_MSK, delay<<UART_RS485_DLY_POSS);
}

/**
  * @brief  Get UARTx Delay value.
  * @param  UARTx UART Instance.
  * @retval UARTx Delay value.
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_dly(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->RS485, UART_RS485_DLY_MSK))>>UART_RS485_DLY_POSS);
}

/**
  * @brief  Set UARTx Address match value.
  * @param  UARTx UART Instance.
  * @param  UARTx Address match value.
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rs485_addr(UART_TypeDef *UARTx, uint32_t address)
{
  MODIFY_REG(UARTx->RS485, UART_RS485_ADDR_MSK, address<<UART_RS485_ADDR_POSS);
}

/**
  * @brief  Get UARTx Address match value.
  * @param  UARTx UART Instance.
  * @retval UARTx Address match value.
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_addr(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->RS485, UART_RS485_ADDR_MSK))>>UART_RS485_ADDR_POSS);
}

/**
  * @brief  Set UARTx Automatic address detection invert.
  * @note   This bit retains the DE(RTSn) polarity direction control signal on pin.
  * @param  UARTx UART Instance.
  * @param  aadinv can be one of the following value:
  *         @arg @ref MD_UART_RS485_AADINV_LOW  (Low : Transfering data, High: Idle)
  *         @arg @ref MD_UART_RS485_AADINV_HIGH (High: Transfering data, Low : Idle)
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rs485_aadinv(UART_TypeDef *UARTx, uint32_t aadinv)
{
  MODIFY_REG(UARTx->RS485, UART_RS485_AADINV_MSK, aadinv<<UART_RS485_AADINV_POS);
}

/**
  * @brief  Get UARTx Automatic address detection invert.
  * @param  UARTx UART Instance.
  * @retval the retval can be one of the following value:
  *         @arg @ref MD_UART_RS485_AADINV_LOW  (Low : Transfering data, High: Idle)
  *         @arg @ref MD_UART_RS485_AADINV_HIGH (High: Transfering data, Low : Idle)
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_aadinv(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->RS485, UART_RS485_AADINV_MSK))>>UART_RS485_AADINV_POS);
}

/**
  * @brief  UARTx Automatic address detection auto-control enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_rs485_aadacen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->RS485, UART_RS485_AADACEN_MSK);
}

/**
  * @brief  UARTx Automatic address detection auto-control disable
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_rs485_aadacen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->RS485, UART_RS485_AADACEN_MSK);
}

/**
  * @brief  Check if UARTx Automatic address detection auto-control is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rs485_aadacen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->RS485, UART_RS485_AADACEN_MSK) == (UART_RS485_AADACEN_MSK));
}

/**
  * @brief  UARTx Automatic address detection normal mode enable.
  * @note   Note that it can be active with RS-485 AAD operation mode.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_rs485_aadnen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->RS485, UART_RS485_AADNEN_MSK);
}

/**
  * @brief  UARTx Automatic address detection normal mode disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_rs485_aadnen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->RS485, UART_RS485_AADNEN_MSK);
}

/**
  * @brief  Check if Automatic address detection normal mode is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rs485_aadnen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->RS485, UART_RS485_AADNEN_MSK) == (UART_RS485_AADNEN_MSK));
}

/**
  * @brief  UARTx Automatic address detection operation mode enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_rs485_aaden(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->RS485, UART_RS485_AADEN_MSK);
}

/**
  * @brief  UARTx Automatic address detection operation mode disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_rs485_aaden(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->RS485, UART_RS485_AADEN_MSK);
}

/**
  * @brief  Check if UARTx Automatic address detection operation mode is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rs485_aaden(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->RS485, UART_RS485_AADEN_MSK) == (UART_RS485_AADEN_MSK));
}

/**
  * @brief  Set UARTx Block Length (Only UART).
  * @note   This bit-field gives the Block length in Smartcard T=1
  *         Reception. Its value equals the number of information
  *         characters + the length of the Epilogue Field (1-LEC/2-CRC) - 1.
  *         This bit-field can be used also in other modes. In this case, the
  *         Block length counter is reset when RXEN=0 (receiver disabled).
  * @param  UARTx UART Instance.
  * @param  Block Length.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_scard_blen(UART_TypeDef *UARTx, uint32_t blocklength)
{
  MODIFY_REG(UARTx->SCARD, UART_SCARD_BLEN_MSK, blocklength<<UART_SCARD_BLEN_POSS);
}

/**
  * @brief  Get UARTx Block Length (Only UART).
  * @param  UARTx UART Instance.
  * @retval Block Length.
  */
__STATIC_INLINE uint32_t md_uart_get_scard_blen(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->SCARD, UART_SCARD_BLEN_MSK))>>UART_SCARD_BLEN_POSS);
}

/**
  * @brief  Set UARTx Guard time value(Only UART).
  * @param  UARTx UART Instance.
  * @param  Guard time value.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_scard_gt(UART_TypeDef *UARTx, uint32_t guardtime)
{
  MODIFY_REG(UARTx->SCARD, UART_SCARD_GT_MSK, guardtime<<UART_SCARD_GT_POSS);
}

/**
  * @brief  Get UARTx Guard time value(Only UART).
  * @param  UARTx UART Instance.
  * @retval Guard time value.
  */
__STATIC_INLINE uint32_t md_uart_get_scard_gt(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->SCARD, UART_SCARD_GT_MSK))>>UART_SCARD_GT_POSS);
}

/**
  * @brief  Set UARTx Prescaler value (Only UART).
  * @note   In IrDA Low-power and normal IrDA mode:
  *           Used for programming the prescaler for dividing the UART
  *           source clock to achieve the low-power frequency.
  *           The source clock is divided by the value given in the register (8
  *           significant bits)
  *         In Smartcard mode:
  *           Used for programming the prescaler for dividing the UART
  *           source clock to provide the Smartcard clock.
  *           The value given in the register (5 significant bits) is multiplied by
  *           2 to give the division factor of the source clock frequency.
  * @param  UARTx UART Instance.
  * @param  Prescaler value.
  * @retval None
  */
__STATIC_INLINE void md_uart_set_scard_psc(UART_TypeDef *UARTx, uint32_t prescaler)
{
  MODIFY_REG(UARTx->SCARD, UART_SCARD_PSC_MSK, prescaler<<UART_SCARD_PSC_POSS);
}

/**
  * @brief  Get UARTx Prescaler value (Only UART).
  * @param  UARTx UART Instance.
  * @retval Prescaler value.
  */
__STATIC_INLINE uint32_t md_uart_get_scard_psc(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->SCARD, UART_SCARD_PSC_MSK))>>UART_SCARD_PSC_POSS);
}

/**
  * @brief  Set UARTx Smartcard auto-retry count (Only UART).
  * @note   This bit-field specifies the number of retries in transmit and
  *         receive, in Smartcard mode.
  *         In transmission mode, it specifies the number of automatic
  *         retransmission retries, before generating a transmission error
  *         (FE bit set).
  *         In reception mode, it specifies the number or erroneous
  *         reception trials, before generating a reception error (RXNE and
  *         PE bits set).
  * @param  UARTx UART Instance.
  * @param  smartcard auto-retry count Min_Value=0x00 Max_Value=0x07.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_scard_sccnt(UART_TypeDef *UARTx, uint32_t count)
{
  MODIFY_REG(UARTx->SCARD, UART_SCARD_SCCNT_MSK, count<<UART_SCARD_SCCNT_POSS);
}

/**
  * @brief  Get UARTx Smartcard auto-retry count (Only UART).
  * @param  UARTx UART Instance.
  * @retval smartcard auto-retry count Min_Value=0x00 Max_Value=0x07
  */
__STATIC_INLINE uint32_t md_uart_get_scard_sccnt(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->SCARD, UART_SCARD_SCCNT_MSK))>>UART_SCARD_SCCNT_POSS);
}

/**
  * @brief  Smartcard clock enable(Only UART).
  * @note   This bit allows the user to enable the SCK pin.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_scard_sclken(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->SCARD, UART_SCARD_SCLKEN_MSK);
}

/**
  * @brief  Smartcard clock disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_scard_sclken(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->SCARD, UART_SCARD_SCLKEN_MSK);
}

/**
  * @brief  Check if Smartcard clock is enable.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_scard_sclken(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->SCARD, UART_SCARD_SCLKEN_MSK) == (UART_SCARD_SCLKEN_MSK));
}

/**
  * @brief  Smartcard NACK enable(Only UART).
  * @note   This bit allows the user to enable nack detection.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_scard_scnack(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->SCARD, UART_SCARD_SCNACK_MSK);
}

/**
  * @brief  Smartcard NACK disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_scard_scnack(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->SCARD, UART_SCARD_SCNACK_MSK);
}

/**
  * @brief  Check if Smartcard NACK is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_scard_scnack(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->SCARD, UART_SCARD_SCNACK_MSK) == (UART_SCARD_SCNACK_MSK));
}

/**
  * @brief  Smartcard mode enable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_scard_scen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->SCARD, UART_SCARD_SCEN_MSK);
}

/**
  * @brief  Smartcard mode disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_scard_scen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->SCARD, UART_SCARD_SCEN_MSK);
}

/**
  * @brief  Check if Smartcard mode is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_scard_scen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->SCARD, UART_SCARD_SCEN_MSK) == (UART_SCARD_SCEN_MSK));
}

/**
  * @brief  Enable LIN mode break request.
  * @note   This bit is set by software and automatically cleared by
  *         hardware in the next clock cycle.
  *         Writing 1 to this bit sets request to send a BREAK on the line, as
  *         soon as the transmit machine is available.
  *         It generates 13 bits rate low pulse in Lin mode.
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_lin_linbkreq(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LIN, UART_LIN_LINBKREQ_MSK);
}

/**
  * @brief  Disable LIN mode break request.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_linbkreq(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LIN, UART_LIN_LINBKREQ_MSK);
}

/**
  * @brief  Check if LIN break is enabled
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enable_linbkreq(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->LIN, UART_LIN_LINBKREQ_MSK) == (UART_LIN_LINBKREQ_MSK));
}

/**
  * @brief  UARTx LIN mode enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_lin_linen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->LIN, UART_LIN_LINEN_MSK);
}

/**
  * @brief  UART LIN mode disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_lin_linen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->LIN, UART_LIN_LINEN_MSK);
}

/**
  * @brief  Check if UARTx LIN mode is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lin_linen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->LIN, UART_LIN_LINEN_MSK) == (UART_LIN_LINEN_MSK));
}

/**
  * @brief  UARTx receive timeout enable.
  * @note   When this feature is enabled, the RTOIF flag in the UART_RIF
  *         register is set if the RX line is idle (no reception) for the duration
  *         programmed in the RTOR (receiver timeout register).
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_rtor_rtoen(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->RTOR, UART_RTOR_RTOEN_MSK);
}

/**
  * @brief  UARTx receive timeout disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_rtor_rtoen(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->RTOR, UART_RTOR_RTOEN_MSK);
}

/**
  * @brief  Check if UARTx receive timeout is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rtor_rtoen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->RTOR, UART_RTOR_RTOEN_MSK) == (UART_RTOR_RTOEN_MSK));
}

/**
  * @brief  Set UARTx receiver timeout value.
  * @note   This bit-field gives the Receiver timeout value in terms of number of bit duration.
  *         In standard mode:
  *           the RTOF flag is set if, after the last received character, 
  *           no new start bit is detected for more than the RTO value.
  *         In Smartcard mode:
  *           this value is used to implement the CWT and BWT. See Smartcard section for more details.
  *           In this case, the timeout measurement is done starting from the Stop Bit of the last 
  *           received character.
  * @param  UARTx UART Instance.
  * @param  timeout UART timeout value.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_rtor_rto(UART_TypeDef *UARTx, uint32_t timeout)
{
  MODIFY_REG(UARTx->RTOR, UART_RTOR_RTO_MSK, timeout<<UART_RTOR_RTO_POSS);
}

/**
  * @brief  Get UARTx receiver timeout value.
  * @param  UARTx UART Instance.
  * @retval UART timeout value.
  */
__STATIC_INLINE uint32_t md_uart_get_rtor_rto(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->RTOR, UART_RTOR_RTO_MSK))>>UART_RTOR_RTO_POSS);
}

/**
  * @brief  Set UARTx Transmit FIFO level.
  * @note   This is used to indicate the number of data entries in the Transmit FIFO. 
  *         It's value from 0 to 16.
  * @param  UARTx UART Instance.
  * @param  Value between Min_Data=0x00 and Max_Data=0x010.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_fcon_txfl(UART_TypeDef *UARTx, uint32_t level)
{
  MODIFY_REG(UARTx->FCON, UART_FCON_TXFL_MSK, level<<UART_FCON_TXFL_POSS);
}

/**
  * @brief  Get UARTx Transmit FIFO level.
  * @param  UARTx UART Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x010.
  */
__STATIC_INLINE uint32_t md_uart_get_fcon_txfl(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->FCON, UART_FCON_TXFL_MSK))>>UART_FCON_TXFL_POSS);
}

/**
  * @brief  Set UARTx Transmit FIFO trigger threshold.
  * @note   This is used to select the threshold level in the transmit FIFO at
  *         which the Transmit FIFO trigger threshold flag is generated.
  * @param  UARTx UART Instance
  * @param  level This parameter can be one of the following values:
  *         @arg @ref MD_UART_FCON_TXTH_0
  *         @arg @ref MD_UART_FCON_TXTH_2
  *         @arg @ref MD_UART_FCON_TXTH_4
  *         @arg @ref MD_UART_FCON_TXTH_8
  * @retval None
  */
__STATIC_INLINE void md_uart_set_fcon_txth(UART_TypeDef *UARTx, uint32_t level)
{
  MODIFY_REG(UARTx->FCON, UART_FCON_TXTH_MSK, level<<UART_FCON_TXTH_POSS);
}

/**
  * @brief  Get UARTx Tx FIFO trigger threshold
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_FCON_TXTH_0
  *         @arg @ref MD_UART_FCON_TXTH_2
  *         @arg @ref MD_UART_FCON_TXTH_4
  *         @arg @ref MD_UART_FCON_TXTH_8
  */
__STATIC_INLINE uint32_t md_uart_get_fcon_txth(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->FCON, UART_FCON_TXTH_MSK))>>UART_FCON_TXTH_POSS);
}

/**
  * @brief  Transmit FIFO reset.
  * @note   When FIFO is set, all the byte in the transmit FIFO are cleared
  *         and treats the FIFO as empty. Note that this bit will return to 0 in
  *         the next clock cycle.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_fcon_tfrst(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->FCON, UART_FCON_TFRST_MSK);
}

/**
  * @brief  Set UARTx Receive FIFO level.
  * @note   This bit is set by hardware. This is used to indicate the number
  *         of data entries in the Receive FIFO. It's value from 0 to 16.
  * @param  UARTx UART Instance.
  * @param  Value between Min_Data=0x00 and Max_Data=0x010.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_fcon_rxfl(UART_TypeDef *UARTx, uint32_t level)
{
  MODIFY_REG(UARTx->FCON, UART_FCON_RXFL_MSK, level<<UART_FCON_RXFL_POSS);
}

/**
  * @brief  Get UARTx Receive FIFO level.
  * @param  UARTx UART Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x010.
  */
__STATIC_INLINE uint32_t md_uart_get_fcon_rxfl(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->FCON, UART_FCON_RXFL_MSK))>>UART_FCON_TXFL_POSS);
}

/**
  * @brief  Set UARTx Receive FIFO trigger threshold.
  * @note   This is used to select the threshold level in the receiver FIFO at
  *         which the Receive FIFO trigger threshold flag is generated.
  * @param  UARTx UART Instance.
  * @param  level This parameter can be one of the following values:
  *         @arg @ref MD_UART_FCON_RXTH_1
  *         @arg @ref MD_UART_FCON_RXTH_4
  *         @arg @ref MD_UART_FCON_RXTH_8
  *         @arg @ref MD_UART_FCON_RXTH_14
  * @retval None
  */
__STATIC_INLINE void md_uart_set_fcon_rxth(UART_TypeDef *UARTx, uint32_t level)
{
  MODIFY_REG(UARTx->FCON, UART_FCON_RXTH_MSK, level<<UART_FCON_RXTH_POSS);
}

/**
  * @brief  Get UARTx Receive FIFO trigger threshold.
  * @param  UARTx UART Instance.
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_FCON_RXTH_1
  *         @arg @ref MD_UART_FCON_RXTH_4
  *         @arg @ref MD_UART_FCON_RXTH_8
  *         @arg @ref MD_UART_FCON_RXTH_14
  */
__STATIC_INLINE uint32_t md_uart_get_fcon_rxth(UART_TypeDef *UARTx)
{
  return ((READ_BIT(UARTx->FCON, UART_FCON_RXTH_MSK))>>UART_FCON_RXTH_POSS);
}

/**
  * @brief  Receive FIFO reset
  * @note   When FIFO is set, all the byte in the receiver FIFO are cleared
  *         and treats the FIFO as empty. Note that this bit will return to 0 in
  *         the next clock cycle.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_set_fcon_rfrst(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->FCON, UART_FCON_RFRST_MSK);
}

/**
  * @brief  Check if Transmit FIFO overrun error.
  * @note   This bit is set and cleared by hardware Tx line start transmit
  *         data. An overrun error occurs when the FIFO is full and a new
  *         character write at the Transmit. The data in the FIFO is retained
  *         and the data in the TXBR register is lost.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_tfoerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_TFOERR_MSK) == (UART_STAT_TFOERR_MSK));
}

/**
  * @brief  Check if Transmit FIFO full.
  * @note   This bit is set and cleared by hardware when the TX FIFO is no
  *         longer full.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_tffull(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_TFFULL_MSK) == (UART_STAT_TFFULL_MSK));
}

/**
  * @brief  Check if Transmit FIFO empty.
  * @note   This bit is set and cleared by hardware when the TX FIFO is no
  *         longer empty.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_tfempty(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_TFEMPTY_MSK) == (UART_STAT_TFEMPTY_MSK));
}

/**
  * @brief  Check if Transmit FIFO trigger threshold flag.
  * @note   This bit is set and cleared by hardware when transmit FIFO
  *         arrived threshold level in the FCR register.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_tfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_TFTH_MSK) == (UART_STAT_TFTH_MSK));
}

/**
  * @brief  Check if Transmit shift register busy.
  * @note   This bit is cleared by hardware.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_tsbsy(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_TSBUSY_MSK) == (UART_STAT_TSBUSY_MSK));
}

/**
  * @brief  Check if Receive FIFO underrun error.
  * @note   This bit is set and cleared by hardware when receive a new
  *         data. An underrun error occurs when the FIFO is empty at the
  *         receive. The data in the FIFO is read 0 in the RXBR register.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rfuerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RFUERR_MSK) == (UART_STAT_RFUERR_MSK));
}

/**
  * @brief  Check if Receive FIFO overrun error.
  * @note   This bit is set and cleared by hardware when read data in the
  *         RXBR register. An overrun error occurs when the FIFO is full
  *         and a new character arrives at the receiver. The data in the
  *         FIFO is retained and the data in the RXBR register is lost.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rfoerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RFOERR_MSK) == (UART_STAT_RFOERR_MSK));
}

/**
  * @brief  Check if Receive FIFO full.
  * @note   This bit is set and cleared by hardware when the RX FIFO is no
  *         longer full.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rffull(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RFFULL_MSK) == (UART_STAT_RFFULL_MSK));
}

/**
  * @brief  Check if Receive FIFO empty.
  * @note   This bit is cleared when the RX FIFO is no longer empty.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rfempty(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RFEMPTY_MSK) == (UART_STAT_RFEMPTY_MSK));
}

/**
  * @brief  Check if Receive FIFO trigger threshold flag.
  * @note   This bit is set and cleared by hardware when receive FIFO
  *         arrived threshold level in the FCR register.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RFTH_MSK) == (UART_STAT_RFTH_MSK));
}

/**
  * @brief  Check if Receive shiftregister busy.
  * @note   This bit is set and cleared by hardware.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_rsbsy(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_RSBUSY_MSK) == (UART_STAT_RSBUSY_MSK));
}

/**
  * @brief  Get UARTx Clear to send status.
  * @note   This bit is the complement of CTSn. When CTSn is asserted, it
  *         is an indication that the modem or data set is ready to exchange
  *         data with UART.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_get_stat_ctssta(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_CTSSTA_MSK)>>UART_STAT_CTSSTA_POS);
}

/**
  * @brief  Check if Break error.
  * @note   This bit is used to indicate the detection of a break sequence on
  *         the serial input data.
  *         This error is associated with the character at the top of the FIFO.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_bkerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_BKERR_MSK) == (UART_STAT_BKERR_MSK));
}

/**
  * @brief  Check if Framing Error.
  * @note   When the received characters stop bit is a logic 0(i.e. the
  *         receiver did not have a valid stop bit), a framing error occurs.
  *         This error is associated with the character at the top of the FIFO.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_ferr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_FERR_MSK) == (UART_STAT_FERR_MSK));
}

/**
  * @brief  Check if Parity Error.
  * @note   When the receive character does not have correct parity
  *         information and is suspect, a parity error occurs.
  *         This error is associated with the character at the top of the FIFO.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_stat_perr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->STAT, UART_STAT_PERR_MSK) == (UART_STAT_PERR_MSK));
}

/**
  * @brief  Transmit FIFO overrun interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_tfover(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_TFOVER_MSK);
}

/**
  * @brief  Transmit FIFO empty interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_tfempty(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_TFEMPTY_MSK);
}

/**
  * @brief  Transmit FIFO trigger threshold interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_tfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_TFTH_MSK);
}

/**
  * @brief  Transmission byte complete enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_tbc(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_TBC_MSK);
}

/**
  * @brief  Receive FIFO underrun interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rfuerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RFUERR_MSK);
}

/**
  * @brief  Receive FIFO overrun interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rfoerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RFOERR_MSK);
}

/**
  * @brief  Receive FIFO full interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rffull(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RFFULL_MSK);
}

/**
  * @brief  Receive FIFO trigger threshold interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RFTH_MSK);
}

/**
  * @brief  Bit Noise detection enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_noise(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_NOISE_MSK);
}

/**
  * @brief  End of block interrupt enable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_eob(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_EOB_MSK);
}

/**
  * @brief  LINBK: LIN break detection interrupt enable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_linbk(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_LINBK_MSK);
}

/**
  * @brief  Address match interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_addrm(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_ADDRM_MSK);
}

/**
  * @brief  Receiver Timeout interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rxto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RXTO_MSK);
}

/**
  * @brief  Delta CTS status interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_dcts(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_DCTS_MSK);
}

/**
  * @brief  Auto-Baud rate detection Timeout interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_abto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_ABTO_MSK);
}

/**
  * @brief  Auto-Baud rate detection End interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_abend(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_ABEND_MSK);
}

/**
  * @brief  Receiver byte error interrupt enable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_enable_ier_rxberr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IER, UART_IER_RXBERR_MSK);
}

/**
  * @brief  Transmit FIFO overrun interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_tfover(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_TFOVER_MSK);
}

/**
  * @brief  Transmit FIFO empty interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_tfempty(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_TFEMPTY_MSK);
}

/**
  * @brief  Transmit FIFO trigger threshold interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_tfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_TFTH_MSK);
}

/**
  * @brief  Transmission byte complete interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_tbc(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_TBC_MSK);
}

/**
  * @brief  Receive FIFO underrun interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rfuerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RFUERR_MSK);
}

/**
  * @brief  Receive FIFO overrun interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rfoerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RFOERR_MSK);
}

/**
  * @brief  Receive FIFO full interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rffull(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RFFULL_MSK);
}

/**
  * @brief  Receive FIFO trigger threshold interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RFTH_MSK);
}

/**
  * @brief  Bit Noise detection disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_noise(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_NOISE_MSK);
}

/**
  * @brief  End of block interrupt disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_eob(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_EOB_MSK);
}

/**
  * @brief  LIN break detection interrupt disable(Only UART).
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_linbk(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_LINBK_MSK);
}

/**
  * @brief  Address match interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_addrm(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_ADDRM_MSK);
}

/**
  * @brief  Receiver Timeout interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rxto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RXTO_MSK);
}

/**
  * @brief  Delta CTS status interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_dcts(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_DCTS_MSK);
}

/**
  * @brief  Auto-Baud rate detection Timeout interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_abto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_ABTO_MSK);
}

/**
  * @brief  Auto-Baud rate detection End interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_abend(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_ABEND_MSK);
}

/**
  * @brief  Receiver byte error interrupt disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_disable_idr_rxberr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->IDR, UART_IDR_RXBERR_MSK);
}

/**
  * @brief  Check if Tx FIFO overrun interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_tfover(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_TFOVER_MSK) == (UART_IVS_TFOVER_MSK));
}

/**
  * @brief  Check if Tx FIFO empty interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_tfempty(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_TFEMPTY_MSK) == (UART_IVS_TFEMPTY_MSK));
}

/**
  * @brief  Check if Tx FIFO trigger threshold interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_tfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_TFTH_MSK) == (UART_IVS_TFTH_MSK));
}

/**
  * @brief  Check if Tx complete interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_tbc(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_TBC_MSK) == (UART_IVS_TBC_MSK));
}

/**
  * @brief  Check if Rx FIFO underrun interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rfuerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RFUERR_MSK) == (UART_IVS_RFUERR_MSK));
}

/**
  * @brief  Check if Rx FIFO overrun interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rfoerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RFOERR_MSK) == (UART_IVS_RFOERR_MSK));
}

/**
  * @brief  Check if Rx FIFO full interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rffull(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RFFULL_MSK) == (UART_IVS_RFFULL_MSK));
}

/**
  * @brief  Check if Rx FIFO trigger threshold interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RFTH_MSK) == (UART_IVS_RFTH_MSK));
}

/**
  * @brief  Check if noise detection interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_noise(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_NOISE_MSK) == (UART_IVS_NOISE_MSK));
}

/**
  * @brief  Check if end of block detection interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_eob(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_EOB_MSK) == (UART_IVS_EOB_MSK));
}

/**
  * @brief  Check if LIN break detection interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_linbk(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_LINBK_MSK) == (UART_IVS_LINBK_MSK));
}

/**
  * @brief  Check if address match interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_addrm(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_ADDRM_MSK) == (UART_IVS_ADDRM_MSK));
}

/**
  * @brief  Check if RX timeout interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rxto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RXTO_MSK) == (UART_IVS_RXTO_MSK));
}

/**
  * @brief  Check if delta CTS status interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_dcts(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_DCTS_MSK) == (UART_IVS_DCTS_MSK));
}

/**
  * @brief  Check if auto-baud rate detection interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_abto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_ABTO_MSK) == (UART_IVS_ABTO_MSK));
}

/**
  * @brief  Check if auto-baud rate detection end interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_abend(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_ABEND_MSK) == (UART_IVS_ABEND_MSK));
}

/**
  * @brief  Check if RX byte error interrupt is enabled.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_ivs_rxberr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IVS, UART_IVS_RXBERR_MSK) == (UART_IVS_RXBERR_MSK));
}

/**
  * @brief  Get Transmit FIFO overrun interrupt flag.
  * @note   This bit is set by hardware when an overrun error occurs that
  *         the FIFO is full and a new character write at the Transmit.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_tfover(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_TFOVER_MSK) == (UART_RIF_TFOVER_MSK));
}

/**
  * @brief  Get Transmit FIFO empty interrupt flag.
  * @note   This bit is set by hardware when transmit FIFO is empty from
  *         have data to empty.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_txempty(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_TFEMPTY_MSK) == (UART_RIF_TFEMPTY_MSK));
}

/**
  * @brief  Get Transmit FIFO trigger threshold interrupt flag
  * @note   This bit is set by hardware when transmit FIFO arrived
  *         threshold level in the FCR register.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_tfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_TFTH_MSK) == (UART_RIF_TFTH_MSK));
}

/**
  * @brief  Get Transmission byte complete interrupt flag.
  * @note   This bit is set by hardware when transmission byte complete.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_tbc(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_TBC_MSK) == (UART_RIF_TBC_MSK));
}

/**
  * @brief  Get Receive FIFO underrun interrupt flag
  * @note   This bit is set by hardware when an underrun error occurs that
  *         the FIFO is empty and a new character read at the Receive.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rfuerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RFUERR_MSK) == (UART_RIF_RFUERR_MSK));
}

/**
  * @brief  Get Receive FIFO overrun interrupt flag.
  * @note   This bit is set by hardware when an overrun error occurs that
  *         the FIFO is full and a new character arrive at the Receive.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rfoerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RFOERR_MSK) == (UART_RIF_RFOERR_MSK));
}

/**
  * @brief  Get Receive FIFO full interrupt flag.
  * @note   This bit is set by hardware when receive FIFO is full.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rffull(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RFFULL_MSK) == (UART_RIF_RFFULL_MSK));
}

/**
  * @brief  Get Receive FIFO trigger threshold interrupt flag.
  * @note   This bit is set by hardware when receive FIFO arrived threshold
  *         level in the FCR register.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RFTH_MSK) == (UART_RIF_RFTH_MSK));
}

/**
  * @brief  Get Bit Noise detection interrupt flag.
  * @note   This bit is set by hardware when START bit Noise is detected.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_noise(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_NOISE_MSK) == (UART_RIF_NOISE_MSK));
}

/**
  * @brief  Get End of block interrupt flag(Only UART).
  * @note   This bit is set by hardware when blcok length value equals the
  *         number of data byte.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_eob(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_EOB_MSK) == (UART_RIF_EOB_MSK));
}

/**
  * @brief  Get LIN break detection interrupt flag(Only UART).
  * @note   This bit is set by hardware when lin break is detected.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_linbk(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_LINBK_MSK) == (UART_RIF_LINBK_MSK));
}

/**
  * @brief  Get Address match interrupt flag.
  * @note   This bit is set by hardware when the data in the RXBR register
  *         defined by ADD[7:0] in the RS485 register is received.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_addrm(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_ADDRM_MSK) == (UART_RIF_ADDRM_MSK));
}

/**
  * @brief  Get Receiver Timeout interrupt flag.
  * @note   This bit is set by hardware when the timeout value,
  *         programmed in the RTOR register has lapsed, without any
  *         communication.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rxto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RXTO_MSK) == (UART_RIF_RXTO_MSK));
}

/**
  * @brief  Get Delta CTS status interrupt flag.
  * @note   This bit is set by hardware when the CTS input toggles.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_dcts(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_DCTS_MSK) == (UART_RIF_DCTS_MSK));
}

/**
  * @brief  Get Auto-Baud rate detection timeout interrupt flag.
  * @note   This bit is set by hardware when the baud rate detection timeout.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_abto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_ABTO_MSK) == (UART_RIF_ABTO_MSK));
}

/**
  * @brief  Get Auto-Baud rate detection end interrupt flag.
  * @note   This bit is set by hardware when the baud rate detection end.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_abend(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_ABEND_MSK) == (UART_RIF_ABEND_MSK));
}

/**
  * @brief  Get Receiver byte error flag.
  * @note   This bit is set by hardware when a parity error or frame error
  *         occurs in receiver.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rif_rxberr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_RIF_RXBERR_MSK) == (UART_RIF_RXBERR_MSK));
}

/**
  * @brief  Get Transmit FIFO overrun interrupt flag masked.
  * @note   This bit is set by hardware when an overrun error occurs that
  *         the FIFO is full and a new character write at the Transmit.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_tfover(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_TFOVER_MSK) == (UART_IFM_TFOVER_MSK));
}

/**
  * @brief  Get Transmit FIFO empty interrupt flag masked.
  * @note   This bit is set by hardware when transmit FIFO is empty from
  *         have data to empty.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_txempty(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_TFEMPTY_MSK) == (UART_IFM_TFEMPTY_MSK));
}

/**
  * @brief  Get Transmit FIFO trigger threshold interrupt flag masked.
  * @note   This bit is set by hardware when transmit FIFO arrived
  *         threshold level in the FCR register.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_tfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_TFTH_MSK) == (UART_IFM_TFTH_MSK));
}

/**
  * @brief  Get Transmission byte complete interrupt flag masked.
  * @note   This bit is set by hardware when transmission byte complete.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_tbc(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_TBC_MSK) == (UART_IFM_TBC_MSK));
}

/**
  * @brief  Get Receive FIFO underrun interrupt flag masked.
  * @note   This bit is set by hardware when an underrun error occurs that
  *         the FIFO is empty and a new character read at the Receive.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rfuerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RFUERR_MSK) == (UART_IFM_RFUERR_MSK));
}

/**
  * @brief  Get Receive FIFO overrun interrupt flag masked.
  * @note   This bit is set by hardware when an overrun error occurs that
  *         the FIFO is full and a new character arrive at the Receive.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rfoerr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RFOERR_MSK) == (UART_IFM_RFOERR_MSK));
}

/**
  * @brief  Get Receive FIFO full interrupt flag masked.
  * @note   This bit is set by hardware when receive FIFO is full.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rffull(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RFFULL_MSK) == (UART_IFM_RFFULL_MSK));
}

/**
  * @brief  Get Receive FIFO trigger threshold interrupt flag masked.
  * @note   This bit is set by hardware when receive FIFO arrived threshold
  *         level in the FCR register.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rfth(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RFTH_MSK) == (UART_IFM_RFTH_MSK));
}

/**
  * @brief  Get Bit Noise detection interrupt flag masked.
  * @note   This bit is set by hardware when START bit Noise is detected.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_noise(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_NOISE_MSK) == (UART_IFM_NOISE_MSK));
}

/**
  * @brief  Get End of block interrupt flag masked(Only UART).
  * @note   This bit is set by hardware when block length value equals the
  *         number of data byte.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_eob(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_EOB_MSK) == (UART_IFM_EOB_MSK));
}

/**
  * @brief  Get LIN break detection interrupt flag masked(Only UART).
  * @note   This bit is set by hardware when lin break is detected.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_linbk(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_LINBK_MSK) == (UART_IFM_LINBK_MSK));
}

/**
  * @brief  Get Address match interrupt flag masked.
  * @note   This bit is set by hardware when the data in the RXBR register
  *         defined by ADD[7:0] in the RS485 register is received.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_addrm(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_ADDRM_MSK) == (UART_IFM_ADDRM_MSK));
}

/**
  * @brief  Get Receiver Timeout interrupt flag masked.
  * @note   This bit is set by hardware when the timeout value,
  *         programmed in the RTOR register has lapsed, without any
  *         communication.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rxto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RXTO_MSK) == (UART_IFM_RXTO_MSK));
}

/**
  * @brief  Get Delta CTS status interrupt flag masked.
  * @note   This bit is set by hardware when the CTS input toggles.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_dcts(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->IFM, UART_RIF_DCTS_MSK) == (UART_IFM_DCTS_MSK));
}

/**
  * @brief  Get Auto-Baud rate detection timeout interrupt flag masked.
  * @note   This bit is set by hardware when the baud rate detection timeout.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_abto(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_ABTO_MSK) == (UART_IFM_ABTO_MSK));
}

/**
  * @brief  Get Auto-Baud rate detection end interrupt flag masked.
  * @note   This bit is set by hardware when the baud rate detection end.
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_abend(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_ABEND_MSK) == (UART_IFM_ABEND_MSK));
}

/**
  * @brief  Get Receiver byte error interrupt flag masked.
  * @note   This bit is set by hardware when a parity error, frame error or
  *         break error occurs in receiver.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_ifm_rxberr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->RIF, UART_IFM_RXBERR_MSK) == (UART_IFM_RXBERR_MSK));
}

/**
  * @brief  Transmit FIFO overrun interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_txover(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_TFOVER_MSK);
}

/**
  * @brief  Transmit FIFO empty interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_txempty(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_TFEMPTY_MSK);
}

/**
  * @brief  Transmit FIFO trigger threshold interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_tfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_TFTH_MSK);
}

/**
  * @brief  Transmission byte complete interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_tbc(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_TBC_MSK);
}

/**
  * @brief  Receive FIFO underrun interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rfuerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RFUERR_MSK);
}

/**
  * @brief  Receive FIFO overrun interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rfoerr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RFOERR_MSK);
}

/**
  * @brief  Receive FIFO full interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rffull(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RFFULL_MSK);
}

/**
  * @brief  Receive FIFO trigger threshold interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rfth(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RFTH_MSK);
}

/**
  * @brief  Bit Noise detection interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_noise(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_NOISE_MSK);
}

/**
  * @brief  End of block interrupt flag clear(Only UART).
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_eob(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_EOB_MSK);
}

/**
  * @brief  LIN break detection interrupt flag clear(Only UART).
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_linbk(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_LINBK_MSK);
}

/**
  * @brief  Address match interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_addrm(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_ADDRM_MSK);
}

/**
  * @brief  Receiver Timeout interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rxto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RXTO_MSK);
}

/**
  * @brief  Delta CTS status interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_dcts(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_DCTS_MSK);
}

/**
  * @brief  Auto-Baud rate detection timeout interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_abto(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_ABTO_MSK);
}

/**
  * @brief  Auto-Baud rate detection end interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_abend(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_ABEND_MSK);
}

/**
  * @brief  Receiver byte error interrupt flag clear.
  * @param  UARTx UART Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_uart_clear_flag_rxberr(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->ICR, UART_ICR_RXBERR_MSK);
}

/**
  * @} MD_UART_Public_Macros UART Public Macros
  */

/* Public functions -----------------------------------------------------------*/
void md_uart_set_baudrate (UART_TypeDef *UARTx, uint32_t baudrate);
void md_uart_init(UART_TypeDef *UARTx, md_uart_init_typedef *UART_InitStruct);
void md_uart_send (UART_TypeDef *UARTx, uint8_t ch);
uint8_t md_uart_recv (UART_TypeDef *UARTx);
uint32_t md_uart_get_baudrate (UART_TypeDef *UARTx);

/**
  * @} UART
  */

#endif

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}

#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
