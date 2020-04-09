/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FSL_LOG_H
#define _FSL_LOG_H

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*************************************************************************************************
 * Prototypes
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Initializes
 *
 * Call this function to init the buffer
 * @param baseAddr, device base address
 * @param device, device type
 * @param baudRate, device communicate baudrate
 * @param clkSrcFreq, device source clock freq
 *
 * @return              	Indicates whether initialization was successful or not.
 * @retval kStatus_Success  Execution successfully
 * @retval kStatus_Fail     Execution failure
 */
status_t LOG_Init(uint32_t baseAddr, uint8_t device, uint32_t baudRate, uint32_t clkSrcFreq);

/*!
 * @brief De-Initializes
 *
 * Call this function to deinit the buffer
 *
 * @return Indicates whether Deinit was successful or not.
 */
void LOG_Deinit(void);

/*!
 * @brief log push interface
 *
 * Call this function to print log
 * @param fmt, buffer pointer
 * @param size, avaliable size
 * @return indicate the push size
 * @retval-1 indicate buffer is full or transfer fail.
 * @retval size return the push log size.
 */
int LOG_Push(uint8_t *buf, size_t size);

/*!
 * @brief log read one line function
 *
 * Call this function to print log
 * @param fmt, buffer pointer
 * @param size, avaliable size
 * @reutrn the number of the recieved character
 */
int LOG_ReadLine(uint8_t *buf, size_t size);

/*!
 * @brief log read one character function
 *
 * Call this function to GETCHAR
 * @param ch receive address
 * @reutrn the number of the recieved character
 */
int LOG_ReadCharacter(uint8_t *ch);

/*!
 * @brief wait log and io idle
 *
 * Call this function to wait log buffer empty and io idle before enter low power mode.
 * @return Indicates whether wait idle was successful or not.
 */
status_t LOG_WaitIdle(void);

/*!
 * @brief log pop function
 *
 * Call this function to pop log from buffer.
 * @param buf buffer address to pop
 * @param size log size to pop
 * @return pop log size.
 */
int LOG_Pop(uint8_t *buf, size_t size);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif
