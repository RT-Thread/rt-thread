/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_LPUART_RTOS_H__
#define __FSL_LPUART_RTOS_H__

#include "FreeRTOSConfig.h"
#include "fsl_lpuart.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

/*!
 * @addtogroup lpuart_freertos_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LPUART freertos driver version 2.2.5. */
#define FSL_LPUART_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 2, 5))
/*@}*/

/*! @brief LPUART RTOS configuration structure. */
typedef struct _lpuart_rtos_config
{
    LPUART_Type *base;                /*!< UART base address */
    uint32_t srcclk;                  /*!< UART source clock in Hz*/
    uint32_t baudrate;                /*!< Desired communication speed */
    lpuart_parity_mode_t parity;      /*!< Parity setting */
    lpuart_stop_bit_count_t stopbits; /*!< Number of stop bits to use */
    uint8_t *buffer;                  /*!< Buffer for background reception */
    uint32_t buffer_size;             /*!< Size of buffer for background reception */
} lpuart_rtos_config_t;

/*!
* @cond RTOS_PRIVATE
* @name LPUART event flags
*
* This are only valid states for txEvent and rxEvent (lpuart_rtos_handle_t).
*/
/*@{*/
/*! @brief Event flag - transfer complete. */
#define RTOS_LPUART_COMPLETE 0x1
/*! @brief Event flag - ring buffer overrun. */
#define RTOS_LPUART_RING_BUFFER_OVERRUN 0x2
/*! @brief Event flag - hardware buffer overrun. */
#define RTOS_LPUART_HARDWARE_BUFFER_OVERRUN 0x4
/*@}*/

/*! @brief LPUART FreeRTOS transfer structure. */
typedef struct _lpuart_rtos_handle
{
    LPUART_Type *base;             /*!< UART base address */
    lpuart_transfer_t txTransfer;  /*!< TX transfer structure */
    lpuart_transfer_t rxTransfer;  /*!< RX transfer structure */
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
} lpuart_rtos_handle_t;
/*! \endcond */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPUART RTOS Operation
 * @{
 */

/*!
 * @brief Initializes an LPUART instance for operation in RTOS.
 *
 * @param handle The RTOS LPUART handle, the pointer to an allocated space for RTOS context.
 * @param t_handle The pointer to an allocated space to store the transactional layer internal state.
 * @param cfg The pointer to the parameters required to configure the LPUART after initialization.
 * @return 0 succeed, others failed
 */
int LPUART_RTOS_Init(lpuart_rtos_handle_t *handle, lpuart_handle_t *t_handle, const lpuart_rtos_config_t *cfg);

/*!
 * @brief Deinitializes an LPUART instance for operation.
 *
 * This function deinitializes the LPUART module, sets all register value to the reset value,
 * and releases the resources.
 *
 * @param handle The RTOS LPUART handle.
 */
int LPUART_RTOS_Deinit(lpuart_rtos_handle_t *handle);

/*!
 * @name LPUART transactional Operation
 * @{
 */

/*!
 * @brief Sends data in the background.
 *
 * This function sends data. It is an synchronous API.
 * If the hardware buffer is full, the task is in the blocked state.
 *
 * @param handle The RTOS LPUART handle.
 * @param buffer The pointer to buffer to send.
 * @param length The number of bytes to send.
 */
int LPUART_RTOS_Send(lpuart_rtos_handle_t *handle, const uint8_t *buffer, uint32_t length);

/*!
 * @brief Receives data.
 *
 * This function receives data from LPUART. It is an synchronous API. If any data is immediately available
 * it is returned immediately and the number of bytes received.
 *
 * @param handle The RTOS LPUART handle.
 * @param buffer The pointer to buffer where to write received data.
 * @param length The number of bytes to receive.
 * @param received The pointer to a variable of size_t where the number of received data is filled.
 */
int LPUART_RTOS_Receive(lpuart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPUART_RTOS_H__ */
