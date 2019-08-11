/*
 * This is a modified version of the file printf.c, which was distributed
 * by Motorola as part of the M5407C3BOOT.zip package used to initialize
 * the M5407C3 evaluation board.
 *
 * Copyright:
 *      1999-2000 MOTOROLA, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Motorola, Inc. This
 *  software is provided on an "AS IS" basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, MOTOROLA
 *  DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED, INCLUDING
 *  IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 *  PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH REGARD TO THE
 *  SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF) AND ANY
 *  ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL MOTOROLA BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING
 *  WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS
 *  INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY
 *  LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Motorola assumes no responsibility for the maintenance and support
 *  of this software

 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdarg.h>
#include <stdlib.h>
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#include <stdio.h>
#endif

#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#endif

#include "fsl_debug_console_conf.h"
#include "fsl_str.h"

#include "fsl_common.h"
#include "serial_manager.h"

#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef NDEBUG
#if (defined(DEBUG_CONSOLE_ASSERT_DISABLE) && (DEBUG_CONSOLE_ASSERT_DISABLE > 0U))
#undef assert
#define assert(n)
#endif
#endif

/*! @brief character backspace ASCII value */
#define DEBUG_CONSOLE_BACKSPACE 127

/* lock definition */
#if (DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DEBUG_CONSOLE_SYNCHRONIZATION_FREERTOS)

static SemaphoreHandle_t s_debugConsoleReadSemaphore;
static SemaphoreHandle_t s_debugConsoleReadWaitSemaphore;

#elif(DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DDEBUG_CONSOLE_SYNCHRONIZATION_BM)

static volatile uint8_t s_debugConsoleReadWaitSemaphore;

#else

#endif /* DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DEBUG_CONSOLE_SYNCHRONIZATION_FREERTOS */

/*! @brief get current runing environment is ISR or not */
#ifdef __CA7_REV
#define IS_RUNNING_IN_ISR() SystemGetIRQNestingLevel()
#else
#define IS_RUNNING_IN_ISR() __get_IPSR()
#endif /* __CA7_REV */

/* semaphore definition */
#if (DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DEBUG_CONSOLE_SYNCHRONIZATION_FREERTOS)

/* mutex semaphore */
#define DEBUG_CONSOLE_CREATE_MUTEX_SEMAPHORE(mutex) (mutex = xSemaphoreCreateMutex())

/* clang-format off */
#define DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(mutex) \
{                                                 \
        if (IS_RUNNING_IN_ISR() == 0U)            \
        {                                         \
            xSemaphoreGive(mutex);                \
        }                                         \
}

#define DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_BLOCKING(mutex) \
{                                                          \
        if (IS_RUNNING_IN_ISR() == 0U)                     \
        {                                                  \
            xSemaphoreTake(mutex, portMAX_DELAY);          \
        }                                                  \
}

#define DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_NONBLOCKING(mutex, result) \
{                                                                     \
        if (IS_RUNNING_IN_ISR() == 0U)                                \
        {                                                             \
            result = xSemaphoreTake(mutex, 0U);                       \
        }                                                             \
        else                                                          \
        {                                                             \
            result = 1U;                                              \
        }                                                             \
}
/* clang-format on */

/* Binary semaphore */
#define DEBUG_CONSOLE_CREATE_BINARY_SEMAPHORE(binary) (binary = xSemaphoreCreateBinary())
#define DEBUG_CONSOLE_TAKE_BINARY_SEMAPHORE_BLOCKING(binary) (xSemaphoreTake(binary, portMAX_DELAY))
#define DEBUG_CONSOLE_GIVE_BINARY_SEMAPHORE_FROM_ISR(binary) (xSemaphoreGiveFromISR(binary, NULL))

#elif(DEBUG_CONSOLE_SYNCHRONIZATION_BM == DEBUG_CONSOLE_SYNCHRONIZATION_MODE)

#define DEBUG_CONSOLE_CREATE_MUTEX_SEMAPHORE(mutex)
#define DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_BLOCKING(mutex)
#define DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(mutex)
#define DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_NONBLOCKING(mutex, result) (result = 1U)

#define DEBUG_CONSOLE_CREATE_BINARY_SEMAPHORE(binary)
#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
#define DEBUG_CONSOLE_TAKE_BINARY_SEMAPHORE_BLOCKING(binary) \
    {                                                        \
        while (!binary)                                      \
        {                                                    \
        }                                                    \
        binary = false;                                      \
    }
#define DEBUG_CONSOLE_GIVE_BINARY_SEMAPHORE_FROM_ISR(binary) (binary = true)
#else
#define DEBUG_CONSOLE_TAKE_BINARY_SEMAPHORE_BLOCKING(binary)
#define DEBUG_CONSOLE_GIVE_BINARY_SEMAPHORE_FROM_ISR(binary)
#endif /* DEBUG_CONSOLE_TRANSFER_NON_BLOCKING */

/* add other implementation here
*such as :
* #elif(DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DDEBUG_CONSOLE_SYNCHRONIZATION_xxx)
*/

#else

#error RTOS type is not defined by DEBUG_CONSOLE_SYNCHRONIZATION_MODE.

#endif /* DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DEBUG_CONSOLE_SYNCHRONIZATION_FREERTOS */

#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
/* receive state structure */
typedef struct _debug_console_write_ring_buffer
{
    uint32_t ringBufferSize;
    volatile uint32_t ringHead;
    volatile uint32_t ringTail;
    uint8_t ringBuffer[DEBUG_CONSOLE_TRANSMIT_BUFFER_LEN];
} debug_console_write_ring_buffer_t;
#endif

typedef struct _debug_console_state_struct
{
    uint8_t serialHandleBuffer[SERIAL_MANAGER_HANDLE_SIZE];
    serial_handle_t serialHandle; /*!< serial manager handle */
#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
    debug_console_write_ring_buffer_t writeRingBuffer;
    uint8_t readRingBuffer[DEBUG_CONSOLE_RECEIVE_BUFFER_LEN];
#endif
    uint8_t serialWriteHandleBuffer[SERIAL_MANAGER_WRITE_HANDLE_SIZE];
    uint8_t serialReadHandleBuffer[SERIAL_MANAGER_READ_HANDLE_SIZE];
} debug_console_state_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Debug console state information. */
static debug_console_state_struct_t s_debugConsoleState;
serial_handle_t g_serialHandle; /*!< serial manager handle */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief This is a printf call back function which is used to relocate the log to buffer
 * or print the log immediately when the local buffer is full.
 *
 * @param[in] buf   Buffer to store log.
 * @param[in] indicator Buffer index.
 * @param[in] val Target character to store.
 * @param[in] len length of the character
 *
 */
#if SDK_DEBUGCONSOLE
static void DbgConsole_PrintCallback(char *buf, int32_t *indicator, char val, int len);
#endif

int DbgConsole_SendData(uint8_t *ch, size_t size);

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)

static void DbgConsole_SerialManagerTxCallback(void *callbackParam,
                                               serial_manager_callback_message_t *message,
                                               serial_manager_status_t status)
{
    debug_console_state_struct_t *ioState;
    uint32_t sendDataLength;

    if ((NULL == callbackParam) || (NULL == message))
    {
        return;
    }

    ioState = (debug_console_state_struct_t *)callbackParam;

    ioState->writeRingBuffer.ringTail += message->length;
    if (ioState->writeRingBuffer.ringTail >= ioState->writeRingBuffer.ringBufferSize)
    {
        ioState->writeRingBuffer.ringTail = 0U;
    }

    if (kStatus_SerialManager_Success == status)
    {
        if (ioState->writeRingBuffer.ringTail != ioState->writeRingBuffer.ringHead)
        {
            if (ioState->writeRingBuffer.ringHead > ioState->writeRingBuffer.ringTail)
            {
                sendDataLength = ioState->writeRingBuffer.ringHead - ioState->writeRingBuffer.ringTail;
            }
            else
            {
                sendDataLength = ioState->writeRingBuffer.ringBufferSize - ioState->writeRingBuffer.ringTail;
            }

            SerialManager_WriteNonBlocking(((serial_write_handle_t)&ioState->serialWriteHandleBuffer[0]),
                                           &ioState->writeRingBuffer.ringBuffer[ioState->writeRingBuffer.ringTail],
                                           sendDataLength);
        }
    }
    else
    {
    }
}

#if (defined(DEBUG_CONSOLE_RX_ENABLE) && (DEBUG_CONSOLE_RX_ENABLE > 0U))

static void DbgConsole_SerialManagerRxCallback(void *callbackParam,
                                               serial_manager_callback_message_t *message,
                                               serial_manager_status_t status)
{
    if ((NULL == callbackParam) || (NULL == message))
    {
        return;
    }

    if (kStatus_SerialManager_Notify == status)
    {
    }
    else if (kStatus_SerialManager_Success == status)
    {
        /* release s_debugConsoleReadWaitSemaphore from RX callback */
        DEBUG_CONSOLE_GIVE_BINARY_SEMAPHORE_FROM_ISR(s_debugConsoleReadWaitSemaphore);
    }
    else
    {
    }
}
#endif

#endif

status_t DbgConsole_ReadOneCharacter(uint8_t *ch)
{
#if (defined(DEBUG_CONSOLE_RX_ENABLE) && (DEBUG_CONSOLE_RX_ENABLE > 0U))

#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING) && \
    (DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DDEBUG_CONSOLE_SYNCHRONIZATION_BM) && defined(OSA_USED)
    return kStatus_Fail;
#else
    status_t status = kStatus_SerialManager_Error;

/* recieve one char every time */
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
    status =
        SerialManager_ReadNonBlocking(((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]), ch, 1);
#else
    status = SerialManager_ReadBlocking(((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]), ch, 1);
#endif
    if (kStatus_SerialManager_Success != status)
    {
        return kStatus_Fail;
    }
    /* wait s_debugConsoleReadWaitSemaphore from RX callback */
    DEBUG_CONSOLE_TAKE_BINARY_SEMAPHORE_BLOCKING(s_debugConsoleReadWaitSemaphore);

    return kStatus_Success;
#endif

#else

    return kStatus_Fail;

#endif
}

#if DEBUG_CONSOLE_ENABLE_ECHO_FUNCTION
static status_t DbgConsole_EchoCharacter(uint8_t *ch, bool isGetChar, int *index)
{
    /* Due to scanf take \n and \r as end of string,should not echo */
    if (((*ch != '\r') && (*ch != '\n')) || (isGetChar))
    {
        /* recieve one char every time */
        if (1 != DbgConsole_SendData(ch, 1U))
        {
            return kStatus_Fail;
        }
    }

    if ((!isGetChar) && (index))
    {
        if (DEBUG_CONSOLE_BACKSPACE == *ch)
        {
            if ((*index >= 2))
            {
                *index -= 2;
            }
            else
            {
                *index = 0;
            }
        }
    }

    return kStatus_Success;
}
#endif

int DbgConsole_SendData(uint8_t *ch, size_t size)
{
    status_t status = kStatus_SerialManager_Error;
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
    uint32_t sendDataLength;
    int txBusy = 0;
#endif
    assert(NULL != ch);
    assert(0 != size);

#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
    uint32_t regPrimask = DisableGlobalIRQ();
    if (s_debugConsoleState.writeRingBuffer.ringHead != s_debugConsoleState.writeRingBuffer.ringTail)
    {
        txBusy = 1;
        sendDataLength =
            (s_debugConsoleState.writeRingBuffer.ringHead + s_debugConsoleState.writeRingBuffer.ringBufferSize -
             s_debugConsoleState.writeRingBuffer.ringTail) %
            s_debugConsoleState.writeRingBuffer.ringBufferSize;
    }
    else
    {
        sendDataLength = 0U;
    }
    sendDataLength = s_debugConsoleState.writeRingBuffer.ringBufferSize - sendDataLength;
    if (sendDataLength <= size)
    {
        EnableGlobalIRQ(regPrimask);
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        s_debugConsoleState.writeRingBuffer.ringBuffer[s_debugConsoleState.writeRingBuffer.ringHead++] = ch[i];
        if (s_debugConsoleState.writeRingBuffer.ringHead >= s_debugConsoleState.writeRingBuffer.ringBufferSize)
        {
            s_debugConsoleState.writeRingBuffer.ringHead = 0U;
        }
    }

    status = kStatus_SerialManager_Success;

    if (!txBusy)
    {
        if (s_debugConsoleState.writeRingBuffer.ringHead > s_debugConsoleState.writeRingBuffer.ringTail)
        {
            sendDataLength =
                s_debugConsoleState.writeRingBuffer.ringHead - s_debugConsoleState.writeRingBuffer.ringTail;
        }
        else
        {
            sendDataLength =
                s_debugConsoleState.writeRingBuffer.ringBufferSize - s_debugConsoleState.writeRingBuffer.ringTail;
        }

        status = (status_t)SerialManager_WriteNonBlocking(
            ((serial_write_handle_t)&s_debugConsoleState.serialWriteHandleBuffer[0]),
            &s_debugConsoleState.writeRingBuffer.ringBuffer[s_debugConsoleState.writeRingBuffer.ringTail],
            sendDataLength);
    }
    EnableGlobalIRQ(regPrimask);
#else
    status = (status_t)SerialManager_WriteBlocking(
        ((serial_write_handle_t)&s_debugConsoleState.serialWriteHandleBuffer[0]), ch, size);
#endif
    return ((kStatus_Success == status) ? (int)size : -1);
}

int DbgConsole_ReadLine(uint8_t *buf, size_t size)
{
    int i;

    assert(buf != NULL);

    /* take mutex lock function */
    DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_BLOCKING(s_debugConsoleReadSemaphore);

    for (i = 0; i < size; i++)
    {
        /* recieve one char every time */
        if (kStatus_Success != DbgConsole_ReadOneCharacter(&buf[i]))
        {
            /* release mutex lock function */
            DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(s_debugConsoleReadSemaphore);
            return -1;
        }
#if DEBUG_CONSOLE_ENABLE_ECHO_FUNCTION
        DbgConsole_EchoCharacter(&buf[i], false, &i);
#endif
        /* analysis data */
        if (('\r' == buf[i]) || ('\n' == buf[i]))
        {
            /* End of Line. */
            if (0 == i)
            {
                buf[i] = '\0';
                i = -1;
            }
            else
            {
                break;
            }
        }
    }
    /* get char should not add '\0'*/
    if (i == size)
    {
        buf[i] = '\0';
    }
    else
    {
        buf[i + 1] = '\0';
    }

    /* release mutex lock function */
    DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(s_debugConsoleReadSemaphore);

    return i;
}

int DbgConsole_ReadCharacter(uint8_t *ch)
{
    int ret;

    assert(ch);

    /* take mutex lock function */
    DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_BLOCKING(s_debugConsoleReadSemaphore);
    /* read one character */
    if (kStatus_Success == DbgConsole_ReadOneCharacter(ch))
    {
        ret = 1;
#if DEBUG_CONSOLE_ENABLE_ECHO_FUNCTION
        DbgConsole_EchoCharacter(ch, true, NULL);
#endif
    }
    else
    {
        ret = -1;
    }

    /* release mutex lock function */
    DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(s_debugConsoleReadSemaphore);

    return ret;
}

#if SDK_DEBUGCONSOLE
static void DbgConsole_PrintCallback(char *buf, int32_t *indicator, char val, int len)
{
    int i = 0;

    for (i = 0; i < len; i++)
    {
        if ((*indicator + 1) >= DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN)
        {
            DbgConsole_SendData((uint8_t *)buf, *indicator);
            *indicator = 0U;
        }

        buf[*indicator] = val;
        (*indicator)++;
    }
}
#endif

/*************Code for DbgConsole Init, Deinit, Printf, Scanf *******************************/

/* See fsl_debug_console.h for documentation of this function. */
status_t DbgConsole_Init(uint8_t instance, uint32_t baudRate, serial_port_type_t device, uint32_t clkSrcFreq)
{
    serial_manager_config_t serialConfig;
    status_t status = kStatus_SerialManager_Error;

#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
    serial_port_uart_config_t uartConfig = {
        .instance = instance,
        .clockRate = clkSrcFreq,
        .baudRate = baudRate,
        .parityMode = kSerialManager_UartParityDisabled,
        .stopBitCount = kSerialManager_UartOneStopBit,
        .enableRx = 1,
        .enableTx = 1,
    };
#endif

#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
    serial_port_usb_cdc_config_t usbCdcConfig = {
        .controllerIndex = (serial_port_usb_cdc_controller_index_t)instance,
    };
#endif

#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
    serial_port_swo_config_t swoConfig = {
        .clockRate = clkSrcFreq, .baudRate = baudRate, .port = instance, .protocol = kSerialManager_SwoProtocolNrz,
    };
#endif

    serialConfig.type = device;
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
    serialConfig.ringBuffer = &s_debugConsoleState.readRingBuffer[0];
    serialConfig.ringBufferSize = DEBUG_CONSOLE_RECEIVE_BUFFER_LEN;
#endif

    if (kSerialPort_Uart == device)
    {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
        serialConfig.portConfig = &uartConfig;
#else
        return status;
#endif
    }
    else if (kSerialPort_UsbCdc == device)
    {
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
        serialConfig.portConfig = &usbCdcConfig;
#else
        return status;
#endif
    }
    else if (kSerialPort_Swo == device)
    {
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
        serialConfig.portConfig = &swoConfig;
#else
        return status;
#endif
    }
    else
    {
        return status;
    }

    memset(&s_debugConsoleState, 0U, sizeof(s_debugConsoleState));

    s_debugConsoleState.serialHandle = (serial_handle_t)&s_debugConsoleState.serialHandleBuffer[0];
    g_serialHandle = s_debugConsoleState.serialHandle;
    status = SerialManager_Init(s_debugConsoleState.serialHandle, &serialConfig);

    assert(kStatus_SerialManager_Success == status);

    DEBUG_CONSOLE_CREATE_MUTEX_SEMAPHORE(s_debugConsoleReadSemaphore);
    DEBUG_CONSOLE_CREATE_BINARY_SEMAPHORE(s_debugConsoleReadWaitSemaphore);

#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
    s_debugConsoleState.writeRingBuffer.ringBufferSize = DEBUG_CONSOLE_TRANSMIT_BUFFER_LEN;
#endif

    {
        status = SerialManager_OpenWriteHandle(
            s_debugConsoleState.serialHandle, ((serial_write_handle_t)&s_debugConsoleState.serialWriteHandleBuffer[0]));
        assert(kStatus_SerialManager_Success == status);
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
        SerialManager_InstallTxCallback(((serial_write_handle_t)&s_debugConsoleState.serialWriteHandleBuffer[0]),
                                        DbgConsole_SerialManagerTxCallback, &s_debugConsoleState);
#endif
    }

#if (defined(DEBUG_CONSOLE_RX_ENABLE) && (DEBUG_CONSOLE_RX_ENABLE > 0U))
    {
        status = SerialManager_OpenReadHandle(s_debugConsoleState.serialHandle,
                                              ((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]));
        assert(kStatus_SerialManager_Success == status);
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
        SerialManager_InstallRxCallback(((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]),
                                        DbgConsole_SerialManagerRxCallback, &s_debugConsoleState);
#endif
    }
#endif
    return kStatus_Success;
}

/* See fsl_debug_console.h for documentation of this function. */
status_t DbgConsole_Deinit(void)
{
    {
        SerialManager_CloseWriteHandle(((serial_write_handle_t)&s_debugConsoleState.serialWriteHandleBuffer[0]));
    }
#if (defined(DEBUG_CONSOLE_RX_ENABLE) && (DEBUG_CONSOLE_RX_ENABLE > 0U))
    {
        SerialManager_CloseReadHandle(((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]));
    }
#endif

    return kStatus_Success;
}

status_t DbgConsole_Flush(void)
{
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)

#if (DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DDEBUG_CONSOLE_SYNCHRONIZATION_BM) && defined(OSA_USED)

    if (s_debugConsoleState.writeRingBuffer.ringHead != s_debugConsoleState.writeRingBuffer.ringTail)
    {
        return kStatus_Fail;
    }

#else

    while (s_debugConsoleState.writeRingBuffer.ringHead != s_debugConsoleState.writeRingBuffer.ringTail)
    {
#if (DEBUG_CONSOLE_SYNCHRONIZATION_MODE == DEBUG_CONSOLE_SYNCHRONIZATION_FREERTOS)
        if (IS_RUNNING_IN_ISR() == 0U)
        {
            vTaskDelay(1);
        }
        else
        {
            return kStatus_Fail;
        }
#endif
    }

#endif

#endif
    return kStatus_Success;
}

#if SDK_DEBUGCONSOLE
/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Printf(const char *formatString, ...)
{
    va_list ap;
    int logLength = 0U, result = 0U;
    char printBuf[DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN] = {0U};

    va_start(ap, formatString);
    /* format print log first */
    logLength = StrFormatPrintf(formatString, ap, printBuf, DbgConsole_PrintCallback);
    /* print log */
    result = DbgConsole_SendData((uint8_t *)printBuf, logLength);

    va_end(ap);

    return result;
}

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Putchar(int ch)
{
    /* print char */
    return DbgConsole_SendData((uint8_t *)&ch, 1U);
}

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Scanf(char *formatString, ...)
{
    va_list ap;
    int result;
    char scanfBuf[DEBUG_CONSOLE_SCANF_MAX_LOG_LEN + 1U] = {0U};

    /* scanf log */
    DbgConsole_ReadLine((uint8_t *)scanfBuf, DEBUG_CONSOLE_SCANF_MAX_LOG_LEN);
    /* get va_list */
    va_start(ap, formatString);
    /* format scanf log */
    result = StrFormatScanf(scanfBuf, formatString, ap);

    va_end(ap);

    return result;
}

#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
status_t DbgConsole_TryGetchar(char *ch)
{
#if (defined(DEBUG_CONSOLE_RX_ENABLE) && (DEBUG_CONSOLE_RX_ENABLE > 0U))
    uint32_t length = 0;
    status_t status = kStatus_Fail;

    assert(ch);

    /* take mutex lock function */
    DEBUG_CONSOLE_TAKE_MUTEX_SEMAPHORE_BLOCKING(s_debugConsoleReadSemaphore);

    if (kStatus_SerialManager_Success ==
        SerialManager_TryRead(((serial_read_handle_t)&s_debugConsoleState.serialReadHandleBuffer[0]), (uint8_t *)ch, 1,
                              &length))
    {
        if (length)
        {
#if DEBUG_CONSOLE_ENABLE_ECHO_FUNCTION
            DbgConsole_EchoCharacter(ch, true, NULL);
#endif
            status = kStatus_Success;
        }
    }
    /* release mutex lock function */
    DEBUG_CONSOLE_GIVE_MUTEX_SEMAPHORE(s_debugConsoleReadSemaphore);
    return status;
#else
    return kStatus_Fail;
#endif
}
#endif

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Getchar(void)
{
    uint8_t ch = 0U;

    /* Get char */
    DbgConsole_ReadCharacter(&ch);

    return (int)ch;
}

#endif /* SDK_DEBUGCONSOLE */

/*************Code to support toolchain's printf, scanf *******************************/
/* These function __write and __read is used to support IAR toolchain to printf and scanf*/
#if (defined(__ICCARM__))
#if defined(SDK_DEBUGCONSOLE_UART)
#pragma weak __write
size_t __write(int handle, const unsigned char *buffer, size_t size)
{
    if (buffer == 0)
    {
        /*
         * This means that we should flush internal buffers.  Since we don't we just return.
         * (Remember, "handle" == -1 means that all handles should be flushed.)
         */
        return 0;
    }

    /* This function only writes to "standard out" and "standard err" for all other file handles it returns failure. */
    if ((handle != 1) && (handle != 2))
    {
        return ((size_t)-1);
    }

    /* Send data. */
    DbgConsole_SendData((uint8_t *)buffer, size);

    return size;
}

#pragma weak __read
size_t __read(int handle, unsigned char *buffer, size_t size)
{
    /* This function only reads from "standard in", for all other file  handles it returns failure. */
    if (handle != 0)
    {
        return ((size_t)-1);
    }

    /* Receive data.*/
    DbgConsole_ReadLine(buffer, size);

    return size;
}
#endif /* SDK_DEBUGCONSOLE_UART */

/* support LPC Xpresso with RedLib */
#elif(defined(__REDLIB__))

#if (!SDK_DEBUGCONSOLE) && (defined(SDK_DEBUGCONSOLE_UART))
int __attribute__((weak)) __sys_write(int handle, char *buffer, int size)
{
    if (buffer == 0)
    {
        /* return -1 if error. */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err" for all other file handles it returns failure. */
    if ((handle != 1) && (handle != 2))
    {
        return -1;
    }

    /* Send data. */
    DbgConsole_SendData((uint8_t *)buffer, size);

    return 0;
}

int __attribute__((weak)) __sys_readc(void)
{
    char tmp;

    /* Receive data. */
    DbgConsole_ReadCharacter((uint8_t *)&tmp);

    return tmp;
}
#endif

/* These function __write and __read is used to support ARM_GCC, KDS, Atollic toolchains to printf and scanf*/
#elif(defined(__GNUC__))

#if ((defined(__GNUC__) && (!defined(__MCUXPRESSO)) && (defined(SDK_DEBUGCONSOLE_UART))) || \
     (defined(__MCUXPRESSO) && (!SDK_DEBUGCONSOLE) && (defined(SDK_DEBUGCONSOLE_UART))))

int __attribute__((weak)) _write(int handle, char *buffer, int size)
{
    if (buffer == 0)
    {
        /* return -1 if error. */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err" for all other file handles it returns failure. */
    if ((handle != 1) && (handle != 2))
    {
        return -1;
    }

    /* Send data. */
    DbgConsole_SendData((uint8_t *)buffer, size);

    return size;
}

int __attribute__((weak)) _read(int handle, char *buffer, int size)
{
    /* This function only reads from "standard in", for all other file handles it returns failure. */
    if (handle != 0)
    {
        return -1;
    }

    /* Receive data. */
    return DbgConsole_ReadLine((uint8_t *)buffer, size);
}
#endif

/* These function fputc and fgetc is used to support KEIL toolchain to printf and scanf*/
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#if defined(SDK_DEBUGCONSOLE_UART)
#if defined(__CC_ARM)
struct __FILE
{
    int handle;
    /*
     * Whatever you require here. If the only file you are using is standard output using printf() for debugging,
     * no file handling is required.
     */
};
#endif

/* FILE is typedef in stdio.h. */
#pragma weak __stdout
#pragma weak __stdin
FILE __stdout;
FILE __stdin;

#pragma weak fputc
int fputc(int ch, FILE *f)
{
    /* Send data. */
    return DbgConsole_SendData((uint8_t *)(&ch), 1);
}

#pragma weak fgetc
int fgetc(FILE *f)
{
    char ch;

    /* Receive data. */
    DbgConsole_ReadCharacter((uint8_t *)&ch);

    return ch;
}
#endif /* SDK_DEBUGCONSOLE_UART */
#endif /* __ICCARM__ */
