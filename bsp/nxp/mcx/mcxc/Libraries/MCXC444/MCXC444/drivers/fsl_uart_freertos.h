/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_UART_RTOS_H__
#define __FSL_UART_RTOS_H__

#include "fsl_uart.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

/*!
 * @addtogroup uart_freertos_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief UART FreeRTOS driver version. */
#define FSL_UART_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 5, 0))
/*@}*/

/*! @brief UART configuration structure */
typedef struct _uart_rtos_config
{
    UART_Type *base;                /*!< UART base address */
    uint32_t srcclk;                /*!< UART source clock in Hz*/
    uint32_t baudrate;              /*!< Desired communication speed */
    uart_parity_mode_t parity;      /*!< Parity setting */
    uart_stop_bit_count_t stopbits; /*!< Number of stop bits to use */
    uint8_t *buffer;                /*!< Buffer for background reception */
    uint32_t buffer_size;           /*!< Size of buffer for background reception */
} uart_rtos_config_t;

/*!
 * @cond RTOS_PRIVATE
 * @name UART FreeRTOS handler
 *
 * These are the only valid states for txEvent and rxEvent (uart_rtos_handle_t).
 */
/*@{*/
/*! @brief Event flag - transfer complete. */
#define RTOS_UART_COMPLETE 0x1U
/*! @brief Event flag - ring buffer overrun. */
#define RTOS_UART_RING_BUFFER_OVERRUN 0x2U
/*! @brief Event flag - hardware buffer overrun. */
#define RTOS_UART_HARDWARE_BUFFER_OVERRUN 0x4U
/*@}*/

/*! @brief UART FreeRTOS transfer structure. */
typedef struct _uart_rtos_handle
{
    UART_Type *base;               /*!< UART base address */
    uart_transfer_t txTransfer;    /*!< TX transfer structure */
    uart_transfer_t rxTransfer;    /*!< RX transfer structure */
    SemaphoreHandle_t rxSemaphore; /*!< RX semaphore for resource sharing */
    SemaphoreHandle_t txSemaphore; /*!< TX semaphore for resource sharing */
    EventGroupHandle_t rxEvent;    /*!< RX completion event */
    EventGroupHandle_t txEvent;    /*!< TX completion event */
    void *t_state;                 /*!< Transactional state of the underlying driver */
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    StaticSemaphore_t txSemaphoreBuffer; /*!< Statically allocated memory for txSemaphore */
    StaticSemaphore_t rxSemaphoreBuffer; /*!< Statically allocated memory for rxSemaphore */
    StaticEventGroup_t txEventBuffer;    /*!< Statically allocated memory for txEvent */
    StaticEventGroup_t rxEventBuffer;    /*!< Statically allocated memory for rxEvent */
#endif
} uart_rtos_handle_t;
/*! \endcond */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name UART RTOS Operation
 * @{
 */

/*!
 * @brief Initializes a UART instance for operation in RTOS.
 *
 * @param handle The RTOS UART handle, the pointer to an allocated space for RTOS context.
 * @param t_handle The pointer to the allocated space to store the transactional layer internal state.
 * @param cfg The pointer to the parameters required to configure the UART after initialization.
 * @return 0 succeed; otherwise fail.
 */
int UART_RTOS_Init(uart_rtos_handle_t *handle, uart_handle_t *t_handle, const uart_rtos_config_t *cfg);

/*!
 * @brief Deinitializes a UART instance for operation.
 *
 * This function deinitializes the UART module, sets all register values to reset value,
 * and frees the resources.
 *
 * @param handle The RTOS UART handle.
 */
int UART_RTOS_Deinit(uart_rtos_handle_t *handle);

/*!
 * @name UART transactional Operation
 * @{
 */

/*!
 * @brief Sends data in the background.
 *
 * This function sends data. It is a synchronous API.
 * If the hardware buffer is full, the task is in the blocked state.
 *
 * @param handle The RTOS UART handle.
 * @param buffer The pointer to the buffer to send.
 * @param length The number of bytes to send.
 */
int UART_RTOS_Send(uart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length);

/*!
 * @brief Receives data.
 *
 * This function receives data from UART. It is a synchronous API. If data is immediately available,
 * it is returned immediately and the number of bytes received.
 *
 * @param handle The RTOS UART handle.
 * @param buffer The pointer to the buffer to write received data.
 * @param length The number of bytes to receive.
 * @param received The pointer to a variable of size_t where the number of received data is filled.
 */
int UART_RTOS_Receive(uart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_UART_RTOS_H__ */
