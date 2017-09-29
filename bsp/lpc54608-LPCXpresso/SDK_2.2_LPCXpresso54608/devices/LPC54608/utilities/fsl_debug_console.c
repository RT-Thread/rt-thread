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
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdarg.h>
#include <stdlib.h>
#if defined(__CC_ARM)
#include <stdio.h>
#endif
#include <math.h>
#include "fsl_debug_console.h"

#if (defined(FSL_FEATURE_SOC_UART_COUNT) && (FSL_FEATURE_SOC_UART_COUNT > 0)) || \
    (defined(FSL_FEATURE_SOC_IUART_COUNT) && (FSL_FEATURE_SOC_IUART_COUNT > 0))
#include "fsl_uart.h"
#endif /* FSL_FEATURE_SOC_UART_COUNT || FSL_FEATURE_SOC_IUART_COUNT */

#if defined(FSL_FEATURE_SOC_LPSCI_COUNT) && (FSL_FEATURE_SOC_LPSCI_COUNT > 0)
#include "fsl_lpsci.h"
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */

#if defined(FSL_FEATURE_SOC_LPUART_COUNT) && (FSL_FEATURE_SOC_LPUART_COUNT > 0)
#include "fsl_lpuart.h"
#endif /* FSL_FEATURE_SOC_LPUART_COUNT */

#if defined(FSL_FEATURE_SOC_USB_COUNT) && (FSL_FEATURE_SOC_USB_COUNT > 0) && defined(BOARD_USE_VIRTUALCOM)
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_cdc_acm.h"
#include "usb_device_ch9.h"
#include "virtual_com.h"
#endif

#if defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0)
#include "fsl_usart.h"
#endif /* FSL_FEATURE_SOC_FLEXCOMM_COUNT */

/*! @brief Keil: suppress ellipsis warning in va_arg usage below. */
#if defined(__CC_ARM)
#pragma diag_suppress 1256
#endif /* __CC_ARM */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief This definition is maximum line that debugconsole can scanf each time.*/
#define IO_MAXLINE 20U

/*! @brief The overflow value.*/
#ifndef HUGE_VAL
#define HUGE_VAL (99.e99)
#endif /* HUGE_VAL */

#if SCANF_FLOAT_ENABLE
static double fnum = 0.0;
#endif /* SCANF_FLOAT_ENABLE */

/*! @brief Operation functions definitions for debug console. */
typedef struct DebugConsoleOperationFunctions
{
    union
    {
        void (*PutChar)(void *base, const uint8_t *buffer, size_t length);
#if (defined(FSL_FEATURE_SOC_UART_COUNT) && (FSL_FEATURE_SOC_UART_COUNT > 0)) || \
    (defined(FSL_FEATURE_SOC_IUART_COUNT) && (FSL_FEATURE_SOC_IUART_COUNT > 0))
        void (*UART_PutChar)(UART_Type *base, const uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_UART_COUNT || FSL_FEATURE_SOC_IUART_COUNT */
#if defined(FSL_FEATURE_SOC_LPSCI_COUNT) && (FSL_FEATURE_SOC_LPSCI_COUNT > 0)
        void (*LPSCI_PutChar)(UART0_Type *base, const uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
#if defined(FSL_FEATURE_SOC_LPUART_COUNT) && (FSL_FEATURE_SOC_LPUART_COUNT > 0)
        void (*LPUART_PutChar)(LPUART_Type *base, const uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
#if defined(FSL_FEATURE_SOC_USB_COUNT) && (FSL_FEATURE_SOC_USB_COUNT > 0) && defined(BOARD_USE_VIRTUALCOM)
        void (*USB_PutChar)(usb_device_handle base, const uint8_t *buf, size_t count);
#endif /* FSL_FEATURE_SOC_USB_COUNT && BOARD_USE_VIRTUALCOM*/
#if defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0)
        void (*USART_PutChar)(USART_Type *base, const uint8_t *data, size_t length);
#endif /* FSL_FEATURE_SOC_FLEXCOMM_COUNT */
    } tx_union;
    union
    {
        status_t (*GetChar)(void *base, const uint8_t *buffer, size_t length);
#if (defined(FSL_FEATURE_SOC_UART_COUNT) && (FSL_FEATURE_SOC_UART_COUNT > 0)) || \
    (defined(FSL_FEATURE_SOC_IUART_COUNT) && (FSL_FEATURE_SOC_IUART_COUNT > 0))
        status_t (*UART_GetChar)(UART_Type *base, uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_UART_COUNT || FSL_FEATURE_SOC_IUART_COUNT*/
#if defined(FSL_FEATURE_SOC_LPSCI_COUNT) && (FSL_FEATURE_SOC_LPSCI_COUNT > 0)
        status_t (*LPSCI_GetChar)(UART0_Type *base, uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
#if defined(FSL_FEATURE_SOC_LPUART_COUNT) && (FSL_FEATURE_SOC_LPUART_COUNT > 0)
        status_t (*LPUART_GetChar)(LPUART_Type *base, uint8_t *buffer, size_t length);
#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
#if defined(FSL_FEATURE_SOC_USB_COUNT) && (FSL_FEATURE_SOC_USB_COUNT > 0) && defined(BOARD_USE_VIRTUALCOM)
        status_t (*USB_GetChar)(usb_device_handle base, uint8_t *buf, size_t count);
#endif /* FSL_FEATURE_SOC_USB_COUNT && BOARD_USE_VIRTUALCOM*/
#if defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0)
        status_t (*USART_GetChar)(USART_Type *base, uint8_t *data, size_t length);
#endif
    } rx_union;
} debug_console_ops_t;

/*! @brief State structure storing debug console. */
typedef struct DebugConsoleState
{
    uint8_t type;            /*!< Indicator telling whether the debug console is initialized. */
    void *base;              /*!< Base of the IP register. */
    debug_console_ops_t ops; /*!< Operation function pointers for debug UART operations. */
} debug_console_state_t;

/*! @brief Type of KSDK printf function pointer. */
typedef int (*PUTCHAR_FUNC)(int a);

#if PRINTF_ADVANCED_ENABLE
/*! @brief Specification modifier flags for printf. */
enum _debugconsole_printf_flag
{
    kPRINTF_Minus = 0x01U,              /*!< Minus FLag. */
    kPRINTF_Plus = 0x02U,               /*!< Plus Flag. */
    kPRINTF_Space = 0x04U,              /*!< Space Flag. */
    kPRINTF_Zero = 0x08U,               /*!< Zero Flag. */
    kPRINTF_Pound = 0x10U,              /*!< Pound Flag. */
    kPRINTF_LengthChar = 0x20U,         /*!< Length: Char Flag. */
    kPRINTF_LengthShortInt = 0x40U,     /*!< Length: Short Int Flag. */
    kPRINTF_LengthLongInt = 0x80U,      /*!< Length: Long Int Flag. */
    kPRINTF_LengthLongLongInt = 0x100U, /*!< Length: Long Long Int Flag. */
};
#endif /* PRINTF_ADVANCED_ENABLE */

/*! @brief Specification modifier flags for scanf. */
enum _debugconsole_scanf_flag
{
    kSCANF_Suppress = 0x2U,      /*!< Suppress Flag. */
    kSCANF_DestMask = 0x7cU,     /*!< Destination Mask. */
    kSCANF_DestChar = 0x4U,      /*!< Destination Char Flag. */
    kSCANF_DestString = 0x8U,    /*!< Destination String FLag. */
    kSCANF_DestSet = 0x10U,      /*!< Destination Set Flag. */
    kSCANF_DestInt = 0x20U,      /*!< Destination Int Flag. */
    kSCANF_DestFloat = 0x30U,    /*!< Destination Float Flag. */
    kSCANF_LengthMask = 0x1f00U, /*!< Length Mask Flag. */
#if SCANF_ADVANCED_ENABLE
    kSCANF_LengthChar = 0x100U,        /*!< Length Char Flag. */
    kSCANF_LengthShortInt = 0x200U,    /*!< Length ShortInt Flag. */
    kSCANF_LengthLongInt = 0x400U,     /*!< Length LongInt Flag. */
    kSCANF_LengthLongLongInt = 0x800U, /*!< Length LongLongInt Flag. */
#endif                                 /* SCANF_ADVANCED_ENABLE */
#if PRINTF_FLOAT_ENABLE
    kSCANF_LengthLongLongDouble = 0x1000U, /*!< Length LongLongDuoble Flag. */
#endif                                     /*PRINTF_FLOAT_ENABLE */
    kSCANF_TypeSinged = 0x2000U,           /*!< TypeSinged Flag. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Debug UART state information. */
static debug_console_state_t s_debugConsole = {.type = DEBUG_CONSOLE_DEVICE_TYPE_NONE, .base = NULL, .ops = {{0}, {0}}};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if SDK_DEBUGCONSOLE
static int DbgConsole_PrintfFormattedData(PUTCHAR_FUNC func_ptr, const char *fmt, va_list ap);
static int DbgConsole_ScanfFormattedData(const char *line_ptr, char *format, va_list args_ptr);
double modf(double input_dbl, double *intpart_ptr);
#endif /* SDK_DEBUGCONSOLE */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*************Code for DbgConsole Init, Deinit, Printf, Scanf *******************************/

/* See fsl_debug_console.h for documentation of this function. */
status_t DbgConsole_Init(uint32_t baseAddr, uint32_t baudRate, uint8_t device, uint32_t clkSrcFreq)
{
    if (s_debugConsole.type != DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return kStatus_Fail;
    }

    /* Set debug console to initialized to avoid duplicated initialized operation. */
    s_debugConsole.type = device;

    /* Switch between different device. */
    switch (device)
    {
#if (defined(FSL_FEATURE_SOC_UART_COUNT) && (FSL_FEATURE_SOC_UART_COUNT > 0)) || \
    (defined(FSL_FEATURE_SOC_IUART_COUNT) && (FSL_FEATURE_SOC_IUART_COUNT > 0))
        case DEBUG_CONSOLE_DEVICE_TYPE_UART:
        case DEBUG_CONSOLE_DEVICE_TYPE_IUART:
        {
            uart_config_t uart_config;
            s_debugConsole.base = (UART_Type *)baseAddr;
            UART_GetDefaultConfig(&uart_config);
            uart_config.baudRate_Bps = baudRate;
            /* Enable clock and initial UART module follow user configure structure. */
            UART_Init(s_debugConsole.base, &uart_config, clkSrcFreq);
            UART_EnableTx(s_debugConsole.base, true);
            UART_EnableRx(s_debugConsole.base, true);
            /* Set the function pointer for send and receive for this kind of device. */
            s_debugConsole.ops.tx_union.UART_PutChar = UART_WriteBlocking;
            s_debugConsole.ops.rx_union.UART_GetChar = UART_ReadBlocking;
        }
        break;
#endif /* FSL_FEATURE_SOC_UART_COUNT */
#if defined(FSL_FEATURE_SOC_LPSCI_COUNT) && (FSL_FEATURE_SOC_LPSCI_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_LPSCI:
        {
            lpsci_config_t lpsci_config;
            s_debugConsole.base = (UART0_Type *)baseAddr;
            LPSCI_GetDefaultConfig(&lpsci_config);
            lpsci_config.baudRate_Bps = baudRate;
            /* Enable clock and initial UART module follow user configure structure. */
            LPSCI_Init(s_debugConsole.base, &lpsci_config, clkSrcFreq);
            LPSCI_EnableTx(s_debugConsole.base, true);
            LPSCI_EnableRx(s_debugConsole.base, true);
            /* Set the function pointer for send and receive for this kind of device. */
            s_debugConsole.ops.tx_union.LPSCI_PutChar = LPSCI_WriteBlocking;
            s_debugConsole.ops.rx_union.LPSCI_GetChar = LPSCI_ReadBlocking;
        }
        break;
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
#if defined(FSL_FEATURE_SOC_LPUART_COUNT) && (FSL_FEATURE_SOC_LPUART_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_LPUART:
        {
            lpuart_config_t lpuart_config;
            s_debugConsole.base = (LPUART_Type *)baseAddr;
            LPUART_GetDefaultConfig(&lpuart_config);
            lpuart_config.baudRate_Bps = baudRate;
            /* Enable clock and initial UART module follow user configure structure. */
            LPUART_Init(s_debugConsole.base, &lpuart_config, clkSrcFreq);
            LPUART_EnableTx(s_debugConsole.base, true);
            LPUART_EnableRx(s_debugConsole.base, true);
            /* Set the function pointer for send and receive for this kind of device. */
            s_debugConsole.ops.tx_union.LPUART_PutChar = LPUART_WriteBlocking;
            s_debugConsole.ops.rx_union.LPUART_GetChar = LPUART_ReadBlocking;
        }
        break;
#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
#if defined(FSL_FEATURE_SOC_USB_COUNT) && (FSL_FEATURE_SOC_USB_COUNT > 0) && defined(BOARD_USE_VIRTUALCOM)
        case DEBUG_CONSOLE_DEVICE_TYPE_USBCDC:
        {
            s_debugConsole.base = USB_VcomInit();
            s_debugConsole.ops.tx_union.USB_PutChar = USB_VcomWriteBlocking;
            s_debugConsole.ops.rx_union.USB_GetChar = USB_VcomReadBlocking;
        }
        break;
#endif /* FSL_FEATURE_SOC_USB_COUNT && BOARD_USE_VIRTUALCOM*/
#if defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_FLEXCOMM:
        {
            usart_config_t usart_config;
            s_debugConsole.base = (USART_Type *)baseAddr;
            USART_GetDefaultConfig(&usart_config);
            usart_config.baudRate_Bps = baudRate;
            /* Enable clock and initial UART module follow user configure structure. */
            USART_Init(s_debugConsole.base, &usart_config, clkSrcFreq);
            /* Set the function pointer for send and receive for this kind of device. */
            s_debugConsole.ops.tx_union.USART_PutChar = USART_WriteBlocking;
            s_debugConsole.ops.rx_union.USART_GetChar = USART_ReadBlocking;
        }
        break;
#endif  /* FSL_FEATURE_SOC_FLEXCOMM_COUNT*/
        /* If new device is required as the low level device for debug console,
         * Add the case branch and add the preprocessor macro to judge whether
         * this kind of device exist in this SOC. */
        default:
            /* Device identified is invalid, return invalid device error code. */
            return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

/* See fsl_debug_console.h for documentation of this function. */
status_t DbgConsole_Deinit(void)
{
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return kStatus_Success;
    }

    switch (s_debugConsole.type)
    {
#if (defined(FSL_FEATURE_SOC_UART_COUNT) && (FSL_FEATURE_SOC_UART_COUNT > 0)) || \
    (defined(FSL_FEATURE_SOC_IUART_COUNT) && (FSL_FEATURE_SOC_IUART_COUNT > 0))
        case DEBUG_CONSOLE_DEVICE_TYPE_UART:
        case DEBUG_CONSOLE_DEVICE_TYPE_IUART:
            /* Disable UART module. */
            UART_Deinit(s_debugConsole.base);
            break;
#endif /* FSL_FEATURE_SOC_UART_COUNT */
#if defined(FSL_FEATURE_SOC_LPSCI_COUNT) && (FSL_FEATURE_SOC_LPSCI_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_LPSCI:
            /* Disable LPSCI module. */
            LPSCI_Deinit(s_debugConsole.base);
            break;
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
#if defined(FSL_FEATURE_SOC_LPUART_COUNT) && (FSL_FEATURE_SOC_LPUART_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_LPUART:
            /* Disable LPUART module. */
            LPUART_Deinit(s_debugConsole.base);
            break;
#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
#if defined(FSL_FEATURE_SOC_USB_COUNT) && (FSL_FEATURE_SOC_USB_COUNT > 0) && defined(BOARD_USE_VIRTUALCOM)
        case DEBUG_CONSOLE_DEVICE_TYPE_USBCDC:
            /* Disable USBCDC module. */
            USB_VcomDeinit(s_debugConsole.base);
            break;
#endif /* FSL_FEATURE_SOC_USB_COUNT && BOARD_USE_VIRTUALCOM*/
#if defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0)
        case DEBUG_CONSOLE_DEVICE_TYPE_FLEXCOMM:
        {
            USART_Deinit((USART_Type *)s_debugConsole.base);
        }
        break;
#endif /* FSL_FEATURE_SOC_FLEXCOMM_COUNT*/
        default:
            s_debugConsole.type = DEBUG_CONSOLE_DEVICE_TYPE_NONE;
            break;
    }

    /* Device identified is invalid, return invalid device error code. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return kStatus_InvalidArgument;
    }

    s_debugConsole.type = DEBUG_CONSOLE_DEVICE_TYPE_NONE;
    return kStatus_Success;
}

#if SDK_DEBUGCONSOLE
/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Printf(const char *fmt_s, ...)
{
    va_list ap;
    int result;

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }
    va_start(ap, fmt_s);
    result = DbgConsole_PrintfFormattedData(DbgConsole_Putchar, fmt_s, ap);
    va_end(ap);

    return result;
}

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Putchar(int ch)
{
    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }
    s_debugConsole.ops.tx_union.PutChar(s_debugConsole.base, (uint8_t *)(&ch), 1);

    return 1;
}

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Scanf(char *fmt_ptr, ...)
{
    /* Plus one to store end of string char */
    char temp_buf[IO_MAXLINE + 1];
    va_list ap;
    int32_t i;
    char result;

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }
    va_start(ap, fmt_ptr);
    temp_buf[0] = '\0';

    for (i = 0; i < IO_MAXLINE; i++)
    {
        temp_buf[i] = result = DbgConsole_Getchar();

        if ((result == '\r') || (result == '\n'))
        {
            /* End of Line. */
            if (i == 0)
            {
                temp_buf[i] = '\0';
                i = -1;
            }
            else
            {
                break;
            }
        }
    }

    if ((i == IO_MAXLINE))
    {
        temp_buf[i] = '\0';
    }
    else
    {
        temp_buf[i + 1] = '\0';
    }
    result = DbgConsole_ScanfFormattedData(temp_buf, fmt_ptr, ap);
    va_end(ap);

    return result;
}

/* See fsl_debug_console.h for documentation of this function. */
int DbgConsole_Getchar(void)
{
    char ch;
    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }
    while (kStatus_Success != s_debugConsole.ops.rx_union.GetChar(s_debugConsole.base, (uint8_t *)(&ch), 1))
    {
        return -1;
    }

    return ch;
}

/*************Code for process formatted data*******************************/
/*!
 * @brief Scanline function which ignores white spaces.
 *
 * @param[in]   s The address of the string pointer to update.
 * @return      String without white spaces.
 */
static uint32_t DbgConsole_ScanIgnoreWhiteSpace(const char **s)
{
    uint8_t count = 0;
    uint8_t c;

    c = **s;
    while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == '\v') || (c == '\f'))
    {
        count++;
        (*s)++;
        c = **s;
    }
    return count;
}

/*!
 * @brief This function puts padding character.
 *
 * @param[in] c         Padding character.
 * @param[in] curlen    Length of current formatted string .
 * @param[in] width     Width of expected formatted string.
 * @param[in] count     Number of characters.
 * @param[in] func_ptr  Function to put character out.
 */
static void DbgConsole_PrintfPaddingCharacter(
    char c, int32_t curlen, int32_t width, int32_t *count, PUTCHAR_FUNC func_ptr)
{
    int32_t i;

    for (i = curlen; i < width; i++)
    {
        func_ptr(c);
        (*count)++;
    }
}

/*!
 * @brief Converts a radix number to a string and return its length.
 *
 * @param[in] numstr    Converted string of the number.
 * @param[in] nump      Pointer to the number.
 * @param[in] neg       Polarity of the number.
 * @param[in] radix     The radix to be converted to.
 * @param[in] use_caps  Used to identify %x/X output format.

 * @return Length of the converted string.
 */
static int32_t DbgConsole_ConvertRadixNumToString(char *numstr, void *nump, int32_t neg, int32_t radix, bool use_caps)
{
#if PRINTF_ADVANCED_ENABLE
    int64_t a;
    int64_t b;
    int64_t c;

    uint64_t ua;
    uint64_t ub;
    uint64_t uc;
#else
    int32_t a;
    int32_t b;
    int32_t c;

    uint32_t ua;
    uint32_t ub;
    uint32_t uc;
#endif /* PRINTF_ADVANCED_ENABLE */

    int32_t nlen;
    char *nstrp;

    nlen = 0;
    nstrp = numstr;
    *nstrp++ = '\0';

    if (neg)
    {
#if PRINTF_ADVANCED_ENABLE
        a = *(int64_t *)nump;
#else
        a = *(int32_t *)nump;
#endif /* PRINTF_ADVANCED_ENABLE */
        if (a == 0)
        {
            *nstrp = '0';
            ++nlen;
            return nlen;
        }
        while (a != 0)
        {
#if PRINTF_ADVANCED_ENABLE
            b = (int64_t)a / (int64_t)radix;
            c = (int64_t)a - ((int64_t)b * (int64_t)radix);
            if (c < 0)
            {
                uc = (uint64_t)c;
                c = (int64_t)(~uc) + 1 + '0';
            }
#else
            b = a / radix;
            c = a - (b * radix);
            if (c < 0)
            {
                uc = (uint32_t)c;
                c = (uint32_t)(~uc) + 1 + '0';
            }
#endif /* PRINTF_ADVANCED_ENABLE */
            else
            {
                c = c + '0';
            }
            a = b;
            *nstrp++ = (char)c;
            ++nlen;
        }
    }
    else
    {
#if PRINTF_ADVANCED_ENABLE
        ua = *(uint64_t *)nump;
#else
        ua = *(uint32_t *)nump;
#endif /* PRINTF_ADVANCED_ENABLE */
        if (ua == 0)
        {
            *nstrp = '0';
            ++nlen;
            return nlen;
        }
        while (ua != 0)
        {
#if PRINTF_ADVANCED_ENABLE
            ub = (uint64_t)ua / (uint64_t)radix;
            uc = (uint64_t)ua - ((uint64_t)ub * (uint64_t)radix);
#else
            ub = ua / (uint32_t)radix;
            uc = ua - (ub * (uint32_t)radix);
#endif /* PRINTF_ADVANCED_ENABLE */

            if (uc < 10)
            {
                uc = uc + '0';
            }
            else
            {
                uc = uc - 10 + (use_caps ? 'A' : 'a');
            }
            ua = ub;
            *nstrp++ = (char)uc;
            ++nlen;
        }
    }
    return nlen;
}

#if PRINTF_FLOAT_ENABLE
/*!
 * @brief Converts a floating radix number to a string and return its length.
 *
 * @param[in] numstr            Converted string of the number.
 * @param[in] nump              Pointer to the number.
 * @param[in] radix             The radix to be converted to.
 * @param[in] precision_width   Specify the precision width.

 * @return Length of the converted string.
 */
static int32_t DbgConsole_ConvertFloatRadixNumToString(char *numstr,
                                                       void *nump,
                                                       int32_t radix,
                                                       uint32_t precision_width)
{
    int32_t a;
    int32_t b;
    int32_t c;
    int32_t i;
    uint32_t uc;
    double fa;
    double dc;
    double fb;
    double r;
    double fractpart;
    double intpart;

    int32_t nlen;
    char *nstrp;
    nlen = 0;
    nstrp = numstr;
    *nstrp++ = '\0';
    r = *(double *)nump;
    if (!r)
    {
        *nstrp = '0';
        ++nlen;
        return nlen;
    }
    fractpart = modf((double)r, (double *)&intpart);
    /* Process fractional part. */
    for (i = 0; i < precision_width; i++)
    {
        fractpart *= radix;
    }
    if (r >= 0)
    {
        fa = fractpart + (double)0.5;
        if (fa >= pow(10, precision_width))
        {
            intpart++;
        }
    }
    else
    {
        fa = fractpart - (double)0.5;
        if (fa <= -pow(10, precision_width))
        {
            intpart--;
        }
    }
    for (i = 0; i < precision_width; i++)
    {
        fb = fa / (int32_t)radix;
        dc = (fa - (int64_t)fb * (int32_t)radix);
        c = (int32_t)dc;
        if (c < 0)
        {
            uc = (uint32_t)c;
            c = (int32_t)(~uc) + 1 + '0';
        }
        else
        {
            c = c + '0';
        }
        fa = fb;
        *nstrp++ = (char)c;
        ++nlen;
    }
    *nstrp++ = (char)'.';
    ++nlen;
    a = (int32_t)intpart;
    if (a == 0)
    {
        *nstrp++ = '0';
        ++nlen;
    }
    else
    {
        while (a != 0)
        {
            b = (int32_t)a / (int32_t)radix;
            c = (int32_t)a - ((int32_t)b * (int32_t)radix);
            if (c < 0)
            {
                uc = (uint32_t)c;
                c = (int32_t)(~uc) + 1 + '0';
            }
            else
            {
                c = c + '0';
            }
            a = b;
            *nstrp++ = (char)c;
            ++nlen;
        }
    }
    return nlen;
}
#endif /* PRINTF_FLOAT_ENABLE */

/*!
 * @brief This function outputs its parameters according to a formatted string.
 *
 * @note I/O is performed by calling given function pointer using following
 * (*func_ptr)(c);
 *
 * @param[in] func_ptr  Function to put character out.
 * @param[in] fmt_ptr   Format string for printf.
 * @param[in] args_ptr  Arguments to printf.
 *
 * @return Number of characters
 */
static int DbgConsole_PrintfFormattedData(PUTCHAR_FUNC func_ptr, const char *fmt, va_list ap)
{
    /* va_list ap; */
    char *p;
    int32_t c;

    char vstr[33];
    char *vstrp = NULL;
    int32_t vlen = 0;

    int32_t done;
    int32_t count = 0;

    uint32_t field_width;
    uint32_t precision_width;
    char *sval;
    int32_t cval;
    bool use_caps;
    uint8_t radix = 0;

#if PRINTF_ADVANCED_ENABLE
    uint32_t flags_used;
    int32_t schar, dschar;
    int64_t ival;
    uint64_t uval = 0;
    bool valid_precision_width;
#else
    int32_t ival;
    uint32_t uval = 0;
#endif /* PRINTF_ADVANCED_ENABLE */

#if PRINTF_FLOAT_ENABLE
    double fval;
#endif /* PRINTF_FLOAT_ENABLE */

    /* Start parsing apart the format string and display appropriate formats and data. */
    for (p = (char *)fmt; (c = *p) != 0; p++)
    {
        /*
         * All formats begin with a '%' marker.  Special chars like
         * '\n' or '\t' are normally converted to the appropriate
         * character by the __compiler__.  Thus, no need for this
         * routine to account for the '\' character.
         */
        if (c != '%')
        {
            func_ptr(c);
            count++;
            /* By using 'continue', the next iteration of the loop is used, skipping the code that follows. */
            continue;
        }

        use_caps = true;

#if PRINTF_ADVANCED_ENABLE
        /* First check for specification modifier flags. */
        flags_used = 0;
        done = false;
        while (!done)
        {
            switch (*++p)
            {
                case '-':
                    flags_used |= kPRINTF_Minus;
                    break;
                case '+':
                    flags_used |= kPRINTF_Plus;
                    break;
                case ' ':
                    flags_used |= kPRINTF_Space;
                    break;
                case '0':
                    flags_used |= kPRINTF_Zero;
                    break;
                case '#':
                    flags_used |= kPRINTF_Pound;
                    break;
                default:
                    /* We've gone one char too far. */
                    --p;
                    done = true;
                    break;
            }
        }
#endif /* PRINTF_ADVANCED_ENABLE */

        /* Next check for minimum field width. */
        field_width = 0;
        done = false;
        while (!done)
        {
            c = *++p;
            if ((c >= '0') && (c <= '9'))
            {
                field_width = (field_width * 10) + (c - '0');
            }
#if PRINTF_ADVANCED_ENABLE
            else if (c == '*')
            {
                field_width = (uint32_t)va_arg(ap, uint32_t);
            }
#endif /* PRINTF_ADVANCED_ENABLE */
            else
            {
                /* We've gone one char too far. */
                --p;
                done = true;
            }
        }
        /* Next check for the width and precision field separator. */
        precision_width = 6;
#if PRINTF_ADVANCED_ENABLE
        valid_precision_width = false;
#endif /* PRINTF_ADVANCED_ENABLE */
        if (*++p == '.')
        {
            /* Must get precision field width, if present. */
            precision_width = 0;
            done = false;
            while (!done)
            {
                c = *++p;
                if ((c >= '0') && (c <= '9'))
                {
                    precision_width = (precision_width * 10) + (c - '0');
#if PRINTF_ADVANCED_ENABLE
                    valid_precision_width = true;
#endif /* PRINTF_ADVANCED_ENABLE */
                }
#if PRINTF_ADVANCED_ENABLE
                else if (c == '*')
                {
                    precision_width = (uint32_t)va_arg(ap, uint32_t);
                    valid_precision_width = true;
                }
#endif /* PRINTF_ADVANCED_ENABLE */
                else
                {
                    /* We've gone one char too far. */
                    --p;
                    done = true;
                }
            }
        }
        else
        {
            /* We've gone one char too far. */
            --p;
        }
#if PRINTF_ADVANCED_ENABLE
        /*
         * Check for the length modifier.
         */
        switch (/* c = */ *++p)
        {
            case 'h':
                if (*++p != 'h')
                {
                    flags_used |= kPRINTF_LengthShortInt;
                    --p;
                }
                else
                {
                    flags_used |= kPRINTF_LengthChar;
                }
                break;
            case 'l':
                if (*++p != 'l')
                {
                    flags_used |= kPRINTF_LengthLongInt;
                    --p;
                }
                else
                {
                    flags_used |= kPRINTF_LengthLongLongInt;
                }
                break;
            default:
                /* we've gone one char too far */
                --p;
                break;
        }
#endif /* PRINTF_ADVANCED_ENABLE */
        /* Now we're ready to examine the format. */
        c = *++p;
        {
            if ((c == 'd') || (c == 'i') || (c == 'f') || (c == 'F') || (c == 'x') || (c == 'X') || (c == 'o') ||
                (c == 'b') || (c == 'p') || (c == 'u'))
            {
                if ((c == 'd') || (c == 'i'))
                {
#if PRINTF_ADVANCED_ENABLE
                    if (flags_used & kPRINTF_LengthLongLongInt)
                    {
                        ival = (int64_t)va_arg(ap, int64_t);
                    }
                    else
#endif /* PRINTF_ADVANCED_ENABLE */
                    {
                        ival = (int32_t)va_arg(ap, int32_t);
                    }
                    vlen = DbgConsole_ConvertRadixNumToString(vstr, &ival, true, 10, use_caps);
                    vstrp = &vstr[vlen];
#if PRINTF_ADVANCED_ENABLE
                    if (ival < 0)
                    {
                        schar = '-';
                        ++vlen;
                    }
                    else
                    {
                        if (flags_used & kPRINTF_Plus)
                        {
                            schar = '+';
                            ++vlen;
                        }
                        else
                        {
                            if (flags_used & kPRINTF_Space)
                            {
                                schar = ' ';
                                ++vlen;
                            }
                            else
                            {
                                schar = 0;
                            }
                        }
                    }
                    dschar = false;
                    /* Do the ZERO pad. */
                    if (flags_used & kPRINTF_Zero)
                    {
                        if (schar)
                        {
                            func_ptr(schar);
                            count++;
                        }
                        dschar = true;

                        DbgConsole_PrintfPaddingCharacter('0', vlen, field_width, &count, func_ptr);
                        vlen = field_width;
                    }
                    else
                    {
                        if (!(flags_used & kPRINTF_Minus))
                        {
                            DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                            if (schar)
                            {
                                func_ptr(schar);
                                count++;
                            }
                            dschar = true;
                        }
                    }
                    /* The string was built in reverse order, now display in correct order. */
                    if ((!dschar) && schar)
                    {
                        func_ptr(schar);
                        count++;
                    }
#endif /* PRINTF_ADVANCED_ENABLE */
                }

#if PRINTF_FLOAT_ENABLE
                if ((c == 'f') || (c == 'F'))
                {
                    fval = (double)va_arg(ap, double);
                    vlen = DbgConsole_ConvertFloatRadixNumToString(vstr, &fval, 10, precision_width);
                    vstrp = &vstr[vlen];

#if PRINTF_ADVANCED_ENABLE
                    if (fval < 0)
                    {
                        schar = '-';
                        ++vlen;
                    }
                    else
                    {
                        if (flags_used & kPRINTF_Plus)
                        {
                            schar = '+';
                            ++vlen;
                        }
                        else
                        {
                            if (flags_used & kPRINTF_Space)
                            {
                                schar = ' ';
                                ++vlen;
                            }
                            else
                            {
                                schar = 0;
                            }
                        }
                    }
                    dschar = false;
                    if (flags_used & kPRINTF_Zero)
                    {
                        if (schar)
                        {
                            func_ptr(schar);
                            count++;
                        }
                        dschar = true;
                        DbgConsole_PrintfPaddingCharacter('0', vlen, field_width, &count, func_ptr);
                        vlen = field_width;
                    }
                    else
                    {
                        if (!(flags_used & kPRINTF_Minus))
                        {
                            DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                            if (schar)
                            {
                                func_ptr(schar);
                                count++;
                            }
                            dschar = true;
                        }
                    }
                    if ((!dschar) && schar)
                    {
                        func_ptr(schar);
                        count++;
                    }
#endif /* PRINTF_ADVANCED_ENABLE */
                }
#endif /* PRINTF_FLOAT_ENABLE */
                if ((c == 'X') || (c == 'x'))
                {
                    if (c == 'x')
                    {
                        use_caps = false;
                    }
#if PRINTF_ADVANCED_ENABLE
                    if (flags_used & kPRINTF_LengthLongLongInt)
                    {
                        uval = (uint64_t)va_arg(ap, uint64_t);
                    }
                    else
#endif /* PRINTF_ADVANCED_ENABLE */
                    {
                        uval = (uint32_t)va_arg(ap, uint32_t);
                    }
                    vlen = DbgConsole_ConvertRadixNumToString(vstr, &uval, false, 16, use_caps);
                    vstrp = &vstr[vlen];

#if PRINTF_ADVANCED_ENABLE
                    dschar = false;
                    if (flags_used & kPRINTF_Zero)
                    {
                        if (flags_used & kPRINTF_Pound)
                        {
                            func_ptr('0');
                            func_ptr((use_caps ? 'X' : 'x'));
                            count += 2;
                            /*vlen += 2;*/
                            dschar = true;
                        }
                        DbgConsole_PrintfPaddingCharacter('0', vlen, field_width, &count, func_ptr);
                        vlen = field_width;
                    }
                    else
                    {
                        if (!(flags_used & kPRINTF_Minus))
                        {
                            if (flags_used & kPRINTF_Pound)
                            {
                                vlen += 2;
                            }
                            DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                            if (flags_used & kPRINTF_Pound)
                            {
                                func_ptr('0');
                                func_ptr(use_caps ? 'X' : 'x');
                                count += 2;

                                dschar = true;
                            }
                        }
                    }

                    if ((flags_used & kPRINTF_Pound) && (!dschar))
                    {
                        func_ptr('0');
                        func_ptr(use_caps ? 'X' : 'x');
                        count += 2;
                        vlen += 2;
                    }
#endif /* PRINTF_ADVANCED_ENABLE */
                }
                if ((c == 'o') || (c == 'b') || (c == 'p') || (c == 'u'))
                {
#if PRINTF_ADVANCED_ENABLE
                    if (flags_used & kPRINTF_LengthLongLongInt)
                    {
                        uval = (uint64_t)va_arg(ap, uint64_t);
                    }
                    else
#endif /* PRINTF_ADVANCED_ENABLE */
                    {
                        uval = (uint32_t)va_arg(ap, uint32_t);
                    }
                    switch (c)
                    {
                        case 'o':
                            radix = 8;
                            break;
                        case 'b':
                            radix = 2;
                            break;
                        case 'p':
                            radix = 16;
                            break;
                        case 'u':
                            radix = 10;
                            break;
                        default:
                            break;
                    }
                    vlen = DbgConsole_ConvertRadixNumToString(vstr, &uval, false, radix, use_caps);
                    vstrp = &vstr[vlen];
#if PRINTF_ADVANCED_ENABLE
                    if (flags_used & kPRINTF_Zero)
                    {
                        DbgConsole_PrintfPaddingCharacter('0', vlen, field_width, &count, func_ptr);
                        vlen = field_width;
                    }
                    else
                    {
                        if (!(flags_used & kPRINTF_Minus))
                        {
                            DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                        }
                    }
#endif /* PRINTF_ADVANCED_ENABLE */
                }
#if !PRINTF_ADVANCED_ENABLE
                DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
#endif /* !PRINTF_ADVANCED_ENABLE */
                if (vstrp != NULL)
                {
                    while (*vstrp)
                    {
                        func_ptr(*vstrp--);
                        count++;
                    }
                }
#if PRINTF_ADVANCED_ENABLE
                if (flags_used & kPRINTF_Minus)
                {
                    DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                }
#endif /* PRINTF_ADVANCED_ENABLE */
            }
            else if (c == 'c')
            {
                cval = (char)va_arg(ap, uint32_t);
                func_ptr(cval);
                count++;
            }
            else if (c == 's')
            {
                sval = (char *)va_arg(ap, char *);
                if (sval)
                {
#if PRINTF_ADVANCED_ENABLE
                    if (valid_precision_width)
                    {
                        vlen = precision_width;
                    }
                    else
                    {
                        vlen = strlen(sval);
                    }
#else
                    vlen = strlen(sval);
#endif /* PRINTF_ADVANCED_ENABLE */
#if PRINTF_ADVANCED_ENABLE
                    if (!(flags_used & kPRINTF_Minus))
#endif /* PRINTF_ADVANCED_ENABLE */
                    {
                        DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                    }

#if PRINTF_ADVANCED_ENABLE
                    if (valid_precision_width)
                    {
                        while ((*sval) && (vlen > 0))
                        {
                            func_ptr(*sval++);
                            count++;
                            vlen--;
                        }
                        /* In case that vlen sval is shorter than vlen */
                        vlen = precision_width - vlen;
                    }
                    else
                    {
#endif /* PRINTF_ADVANCED_ENABLE */
                        while (*sval)
                        {
                            func_ptr(*sval++);
                            count++;
                        }
#if PRINTF_ADVANCED_ENABLE
                    }
#endif /* PRINTF_ADVANCED_ENABLE */

#if PRINTF_ADVANCED_ENABLE
                    if (flags_used & kPRINTF_Minus)
                    {
                        DbgConsole_PrintfPaddingCharacter(' ', vlen, field_width, &count, func_ptr);
                    }
#endif /* PRINTF_ADVANCED_ENABLE */
                }
            }
            else
            {
                func_ptr(c);
                count++;
            }
        }
    }
    return count;
}

/*!
 * @brief Converts an input line of ASCII characters based upon a provided
 * string format.
 *
 * @param[in] line_ptr The input line of ASCII data.
 * @param[in] format   Format first points to the format string.
 * @param[in] args_ptr The list of parameters.
 *
 * @return Number of input items converted and assigned.
 * @retval IO_EOF When line_ptr is empty string "".
 */
static int DbgConsole_ScanfFormattedData(const char *line_ptr, char *format, va_list args_ptr)
{
    uint8_t base;
    int8_t neg;
    /* Identifier for the format string. */
    char *c = format;
    char temp;
    char *buf;
    /* Flag telling the conversion specification. */
    uint32_t flag = 0;
    /* Filed width for the matching input streams. */
    uint32_t field_width;
    /* How many arguments are assigned except the suppress. */
    uint32_t nassigned = 0;
    /* How many characters are read from the input streams. */
    uint32_t n_decode = 0;

    int32_t val;

    const char *s;
    /* Identifier for the input string. */
    const char *p = line_ptr;

    /* Return EOF error before any conversion. */
    if (*p == '\0')
    {
        return -1;
    }

    /* Decode directives. */
    while ((*c) && (*p))
    {
        /* Ignore all white-spaces in the format strings. */
        if (DbgConsole_ScanIgnoreWhiteSpace((const char **)&c))
        {
            n_decode += DbgConsole_ScanIgnoreWhiteSpace(&p);
        }
        else if ((*c != '%') || ((*c == '%') && (*(c + 1) == '%')))
        {
            /* Ordinary characters. */
            c++;
            if (*p == *c)
            {
                n_decode++;
                p++;
                c++;
            }
            else
            {
                /* Match failure. Misalignment with C99, the unmatched characters need to be pushed back to stream.
                 * However, it is deserted now. */
                break;
            }
        }
        else
        {
            /* convernsion specification */
            c++;
            /* Reset. */
            flag = 0;
            field_width = 0;
            base = 0;

            /* Loop to get full conversion specification. */
            while ((*c) && (!(flag & kSCANF_DestMask)))
            {
                switch (*c)
                {
#if SCANF_ADVANCED_ENABLE
                    case '*':
                        if (flag & kSCANF_Suppress)
                        {
                            /* Match failure. */
                            return nassigned;
                        }
                        flag |= kSCANF_Suppress;
                        c++;
                        break;
                    case 'h':
                        if (flag & kSCANF_LengthMask)
                        {
                            /* Match failure. */
                            return nassigned;
                        }

                        if (c[1] == 'h')
                        {
                            flag |= kSCANF_LengthChar;
                            c++;
                        }
                        else
                        {
                            flag |= kSCANF_LengthShortInt;
                        }
                        c++;
                        break;
                    case 'l':
                        if (flag & kSCANF_LengthMask)
                        {
                            /* Match failure. */
                            return nassigned;
                        }

                        if (c[1] == 'l')
                        {
                            flag |= kSCANF_LengthLongLongInt;
                            c++;
                        }
                        else
                        {
                            flag |= kSCANF_LengthLongInt;
                        }
                        c++;
                        break;
#endif /* SCANF_ADVANCED_ENABLE */
#if SCANF_FLOAT_ENABLE
                    case 'L':
                        if (flag & kSCANF_LengthMask)
                        {
                            /* Match failure. */
                            return nassigned;
                        }
                        flag |= kSCANF_LengthLongLongDouble;
                        c++;
                        break;
#endif /* SCANF_FLOAT_ENABLE */
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if (field_width)
                        {
                            /* Match failure. */
                            return nassigned;
                        }
                        do
                        {
                            field_width = field_width * 10 + *c - '0';
                            c++;
                        } while ((*c >= '0') && (*c <= '9'));
                        break;
                    case 'd':
                        base = 10;
                        flag |= kSCANF_TypeSinged;
                        flag |= kSCANF_DestInt;
                        c++;
                        break;
                    case 'u':
                        base = 10;
                        flag |= kSCANF_DestInt;
                        c++;
                        break;
                    case 'o':
                        base = 8;
                        flag |= kSCANF_DestInt;
                        c++;
                        break;
                    case 'x':
                    case 'X':
                        base = 16;
                        flag |= kSCANF_DestInt;
                        c++;
                        break;
                    case 'i':
                        base = 0;
                        flag |= kSCANF_DestInt;
                        c++;
                        break;
#if SCANF_FLOAT_ENABLE
                    case 'a':
                    case 'A':
                    case 'e':
                    case 'E':
                    case 'f':
                    case 'F':
                    case 'g':
                    case 'G':
                        flag |= kSCANF_DestFloat;
                        c++;
                        break;
#endif /* SCANF_FLOAT_ENABLE */
                    case 'c':
                        flag |= kSCANF_DestChar;
                        if (!field_width)
                        {
                            field_width = 1;
                        }
                        c++;
                        break;
                    case 's':
                        flag |= kSCANF_DestString;
                        c++;
                        break;
                    default:
                        return nassigned;
                }
            }

            if (!(flag & kSCANF_DestMask))
            {
                /* Format strings are exhausted. */
                return nassigned;
            }

            if (!field_width)
            {
                /* Large than length of a line. */
                field_width = 99;
            }

            /* Matching strings in input streams and assign to argument. */
            switch (flag & kSCANF_DestMask)
            {
                case kSCANF_DestChar:
                    s = (const char *)p;
                    buf = va_arg(args_ptr, char *);
                    while ((field_width--) && (*p))
                    {
                        if (!(flag & kSCANF_Suppress))
                        {
                            *buf++ = *p++;
                        }
                        else
                        {
                            p++;
                        }
                        n_decode++;
                    }

                    if ((!(flag & kSCANF_Suppress)) && (s != p))
                    {
                        nassigned++;
                    }
                    break;
                case kSCANF_DestString:
                    n_decode += DbgConsole_ScanIgnoreWhiteSpace(&p);
                    s = p;
                    buf = va_arg(args_ptr, char *);
                    while ((field_width--) && (*p != '\0') && (*p != ' ') && (*p != '\t') && (*p != '\n') &&
                           (*p != '\r') && (*p != '\v') && (*p != '\f'))
                    {
                        if (flag & kSCANF_Suppress)
                        {
                            p++;
                        }
                        else
                        {
                            *buf++ = *p++;
                        }
                        n_decode++;
                    }

                    if ((!(flag & kSCANF_Suppress)) && (s != p))
                    {
                        /* Add NULL to end of string. */
                        *buf = '\0';
                        nassigned++;
                    }
                    break;
                case kSCANF_DestInt:
                    n_decode += DbgConsole_ScanIgnoreWhiteSpace(&p);
                    s = p;
                    val = 0;
                    if ((base == 0) || (base == 16))
                    {
                        if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X')))
                        {
                            base = 16;
                            if (field_width >= 1)
                            {
                                p += 2;
                                n_decode += 2;
                                field_width -= 2;
                            }
                        }
                    }

                    if (base == 0)
                    {
                        if (s[0] == '0')
                        {
                            base = 8;
                        }
                        else
                        {
                            base = 10;
                        }
                    }

                    neg = 1;
                    switch (*p)
                    {
                        case '-':
                            neg = -1;
                            n_decode++;
                            p++;
                            field_width--;
                            break;
                        case '+':
                            neg = 1;
                            n_decode++;
                            p++;
                            field_width--;
                            break;
                        default:
                            break;
                    }

                    while ((*p) && (field_width--))
                    {
                        if ((*p <= '9') && (*p >= '0'))
                        {
                            temp = *p - '0';
                        }
                        else if ((*p <= 'f') && (*p >= 'a'))
                        {
                            temp = *p - 'a' + 10;
                        }
                        else if ((*p <= 'F') && (*p >= 'A'))
                        {
                            temp = *p - 'A' + 10;
                        }
                        else
                        {
                            temp = base;
                        }

                        if (temp >= base)
                        {
                            break;
                        }
                        else
                        {
                            val = base * val + temp;
                        }
                        p++;
                        n_decode++;
                    }
                    val *= neg;
                    if (!(flag & kSCANF_Suppress))
                    {
#if SCANF_ADVANCED_ENABLE
                        switch (flag & kSCANF_LengthMask)
                        {
                            case kSCANF_LengthChar:
                                if (flag & kSCANF_TypeSinged)
                                {
                                    *va_arg(args_ptr, signed char *) = (signed char)val;
                                }
                                else
                                {
                                    *va_arg(args_ptr, unsigned char *) = (unsigned char)val;
                                }
                                break;
                            case kSCANF_LengthShortInt:
                                if (flag & kSCANF_TypeSinged)
                                {
                                    *va_arg(args_ptr, signed short *) = (signed short)val;
                                }
                                else
                                {
                                    *va_arg(args_ptr, unsigned short *) = (unsigned short)val;
                                }
                                break;
                            case kSCANF_LengthLongInt:
                                if (flag & kSCANF_TypeSinged)
                                {
                                    *va_arg(args_ptr, signed long int *) = (signed long int)val;
                                }
                                else
                                {
                                    *va_arg(args_ptr, unsigned long int *) = (unsigned long int)val;
                                }
                                break;
                            case kSCANF_LengthLongLongInt:
                                if (flag & kSCANF_TypeSinged)
                                {
                                    *va_arg(args_ptr, signed long long int *) = (signed long long int)val;
                                }
                                else
                                {
                                    *va_arg(args_ptr, unsigned long long int *) = (unsigned long long int)val;
                                }
                                break;
                            default:
                                /* The default type is the type int. */
                                if (flag & kSCANF_TypeSinged)
                                {
                                    *va_arg(args_ptr, signed int *) = (signed int)val;
                                }
                                else
                                {
                                    *va_arg(args_ptr, unsigned int *) = (unsigned int)val;
                                }
                                break;
                        }
#else
                        /* The default type is the type int. */
                        if (flag & kSCANF_TypeSinged)
                        {
                            *va_arg(args_ptr, signed int *) = (signed int)val;
                        }
                        else
                        {
                            *va_arg(args_ptr, unsigned int *) = (unsigned int)val;
                        }
#endif /* SCANF_ADVANCED_ENABLE */
                        nassigned++;
                    }
                    break;
#if SCANF_FLOAT_ENABLE
                case kSCANF_DestFloat:
                    n_decode += DbgConsole_ScanIgnoreWhiteSpace(&p);
                    fnum = strtod(p, (char **)&s);

                    if ((fnum >= HUGE_VAL) || (fnum <= -HUGE_VAL))
                    {
                        break;
                    }

                    n_decode += (int)(s) - (int)(p);
                    p = s;
                    if (!(flag & kSCANF_Suppress))
                    {
                        if (flag & kSCANF_LengthLongLongDouble)
                        {
                            *va_arg(args_ptr, double *) = fnum;
                        }
                        else
                        {
                            *va_arg(args_ptr, float *) = (float)fnum;
                        }
                        nassigned++;
                    }
                    break;
#endif /* SCANF_FLOAT_ENABLE */
                default:
                    return nassigned;
            }
        }
    }
    return nassigned;
}
#endif /* SDK_DEBUGCONSOLE */
/*************Code to support toolchain's printf, scanf *******************************/
/* These function __write and __read is used to support IAR toolchain to printf and scanf*/
#if (defined(__ICCARM__))
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

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return ((size_t)-1);
    }

    /* Send data. */
    s_debugConsole.ops.tx_union.PutChar(s_debugConsole.base, buffer, 1);
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

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return ((size_t)-1);
    }

    /* Receive data. */
    s_debugConsole.ops.rx_union.GetChar(s_debugConsole.base, buffer, size);

    return size;
}

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

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Send data. */
    s_debugConsole.ops.tx_union.PutChar(s_debugConsole.base, (uint8_t *)buffer, size);
    return 0;
}

int __attribute__((weak)) __sys_readc(void)
{
    char tmp;
    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Receive data. */
    s_debugConsole.ops.rx_union.GetChar(s_debugConsole.base, (uint8_t *)&tmp, sizeof(tmp));
    return tmp;
}
#endif

/* These function __write and __read is used to support ARM_GCC, KDS, Atollic toolchains to printf and scanf*/
#elif(defined(__GNUC__))

#if ((defined(__GNUC__) && (!defined(__MCUXPRESSO))) || \
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

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Send data. */
    s_debugConsole.ops.tx_union.PutChar(s_debugConsole.base, (uint8_t *)buffer, size);
    return size;
}

int __attribute__((weak)) _read(int handle, char *buffer, int size)
{
    /* This function only reads from "standard in", for all other file handles it returns failure. */
    if (handle != 0)
    {
        return -1;
    }

    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Receive data. */
    s_debugConsole.ops.rx_union.GetChar(s_debugConsole.base, (uint8_t *)buffer, size);
    return size;
}
#endif

/* These function fputc and fgetc is used to support KEIL toolchain to printf and scanf*/
#elif defined(__CC_ARM)
struct __FILE
{
    int handle;
    /*
     * Whatever you require here. If the only file you are using is standard output using printf() for debugging,
     * no file handling is required.
     */
};

/* FILE is typedef in stdio.h. */
#pragma weak __stdout
#pragma weak __stdin
FILE __stdout;
FILE __stdin;

#pragma weak fputc
int fputc(int ch, FILE *f)
{
    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Send data. */
    s_debugConsole.ops.tx_union.PutChar(s_debugConsole.base, (uint8_t *)(&ch), 1);
    return 1;
}

#pragma weak fgetc
int fgetc(FILE *f)
{
    char ch;
    /* Do nothing if the debug UART is not initialized. */
    if (s_debugConsole.type == DEBUG_CONSOLE_DEVICE_TYPE_NONE)
    {
        return -1;
    }

    /* Receive data. */
    s_debugConsole.ops.rx_union.GetChar(s_debugConsole.base, (uint8_t *)(&ch), 1);
    return ch;
}
#endif /* __ICCARM__ */
