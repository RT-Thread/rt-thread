/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#include <stdio.h>
#include <stdlib.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#if defined(UART_INSTANCE_COUNT)
#include "fsl_uart_hal.h"
#endif
#if defined(LPUART_INSTANCE_COUNT)
#include "fsl_lpuart_hal.h"
#endif
#if defined(UART0_INSTANCE_COUNT)
#include "fsl_lpsci_hal.h"
#endif
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"
#include "print_scan.h"

#if (defined(USB_INSTANCE_COUNT) &&  (defined(BOARD_USE_VIRTUALCOM)))
  #include "usb_device_config.h"
  #include "usb.h"
  #include "usb_device_stack_interface.h"
  #include "usb_descriptor.h"
  #include "virtual_com.h"
#endif

extern uint32_t g_app_handle;
#if __ICCARM__
#include <yfuns.h>
#endif

static int debug_putc(int ch, void* stream);

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Operation functions definiations for debug console. */
typedef struct DebugConsoleOperationFunctions {
    union {
        void (* Send)(void *base, const uint8_t *buf, uint32_t count);
#if defined(UART_INSTANCE_COUNT)
        void (* UART_Send)(UART_Type *base, const uint8_t *buf, uint32_t count);
#endif
#if defined(LPUART_INSTANCE_COUNT)
        void (* LPUART_Send)(LPUART_Type* base, const uint8_t *buf, uint32_t count);
#endif
#if defined(UART0_INSTANCE_COUNT)
        void (* UART0_Send)(UART0_Type* base, const uint8_t *buf, uint32_t count);
#endif
#if (defined(USB_INSTANCE_COUNT) && defined(BOARD_USE_VIRTUALCOM))
        void (* USB_Send)(uint32_t base, const uint8_t *buf, uint32_t count);
#endif
    } tx_union;
    union{
        void (* Receive)(void *base, uint8_t *buf, uint32_t count);
#if defined(UART_INSTANCE_COUNT)
        uart_status_t (* UART_Receive)(UART_Type *base, uint8_t *buf, uint32_t count);
#endif
#if defined(LPUART_INSTANCE_COUNT)
        lpuart_status_t (* LPUART_Receive)(LPUART_Type* base, uint8_t *buf, uint32_t count);
#endif
#if defined(UART0_INSTANCE_COUNT)
        lpsci_status_t (* UART0_Receive)(UART0_Type* base, uint8_t *buf, uint32_t count);
#endif
#if (defined(USB_INSTANCE_COUNT) && defined(BOARD_USE_VIRTUALCOM))
        usb_status_t (* USB_Receive)(uint32_t base, uint8_t *buf, uint32_t count);
#endif

    } rx_union;
} debug_console_ops_t;

/*! @brief State structure storing debug console. */
typedef struct DebugConsoleState {
    debug_console_device_type_t type;/*<! Indicator telling whether the debug console is inited. */
    uint8_t instance;               /*<! Instance number indicator. */
    void*   base;                   /*<! Base of the IP register. */
    debug_console_ops_t ops;        /*<! Operation function pointers for debug uart operations. */
} debug_console_state_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Debug UART state information.*/
static debug_console_state_t s_debugConsole;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* See fsl_debug_console.h for documentation of this function.*/
debug_console_status_t DbgConsole_Init(
        uint32_t uartInstance, uint32_t baudRate, debug_console_device_type_t device)
{
    if (s_debugConsole.type != kDebugConsoleNone)
    {
        return kStatus_DEBUGCONSOLE_Failed;
    }

    /* Set debug console to initialized to avoid duplicated init operation.*/
    s_debugConsole.type = device;
    s_debugConsole.instance = uartInstance;

    /* Switch between different device. */
    switch (device)
    {
#if (defined(USB_INSTANCE_COUNT) && defined(BOARD_USE_VIRTUALCOM))  /*&& defined()*/
       case kDebugConsoleUSBCDC:
         {
                VirtualCom_Init();
                s_debugConsole.base = (void*)g_app_handle;
                s_debugConsole.ops.tx_union.USB_Send = VirtualCom_SendDataBlocking;
                s_debugConsole.ops.rx_union.USB_Receive = VirtualCom_ReceiveDataBlocking;
         }
         break;
#endif
#if defined(UART_INSTANCE_COUNT)
        case kDebugConsoleUART:
            {
                UART_Type * g_Base[UART_INSTANCE_COUNT] = UART_BASE_PTRS;
                UART_Type * base = g_Base[uartInstance];
                uint32_t uartSourceClock;

                s_debugConsole.base = base;
                CLOCK_SYS_EnableUartClock(uartInstance);

                /* UART clock source is either system or bus clock depending on instance */
                uartSourceClock = CLOCK_SYS_GetUartFreq(uartInstance);

                /* Initialize UART baud rate, bit count, parity and stop bit. */
                UART_HAL_SetBaudRate(base, uartSourceClock, baudRate);
                UART_HAL_SetBitCountPerChar(base, kUart8BitsPerChar);
                UART_HAL_SetParityMode(base, kUartParityDisabled);
#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
                UART_HAL_SetStopBitCount(base, kUartOneStopBit);
#endif

                /* Finally, enable the UART transmitter and receiver*/
                UART_HAL_EnableTransmitter(base);
                UART_HAL_EnableReceiver(base);

                /* Set the funciton pointer for send and receive for this kind of device. */
                s_debugConsole.ops.tx_union.UART_Send = UART_HAL_SendDataPolling;
                s_debugConsole.ops.rx_union.UART_Receive = UART_HAL_ReceiveDataPolling;
            }
            break;
#endif
#if defined(UART0_INSTANCE_COUNT)
        case kDebugConsoleLPSCI:
            {
                /* Declare config sturcuture to initialize a uart instance. */
                UART0_Type * g_Base[UART0_INSTANCE_COUNT] = UART0_BASE_PTRS;
                UART0_Type * base = g_Base[uartInstance];
                uint32_t uartSourceClock;

                s_debugConsole.base = base;
                CLOCK_SYS_EnableLpsciClock(uartInstance);

                uartSourceClock = CLOCK_SYS_GetLpsciFreq(uartInstance);

                /* Initialize LPSCI baud rate, bit count, parity and stop bit. */
                LPSCI_HAL_SetBaudRate(base, uartSourceClock, baudRate);
                LPSCI_HAL_SetBitCountPerChar(base, kLpsci8BitsPerChar);
                LPSCI_HAL_SetParityMode(base, kLpsciParityDisabled);
#if FSL_FEATURE_LPSCI_HAS_STOP_BIT_CONFIG_SUPPORT
                LPSCI_HAL_SetStopBitCount(base, kLpsciOneStopBit);
#endif

                /* Finally, enable the LPSCI transmitter and receiver*/
                LPSCI_HAL_EnableTransmitter(base);
                LPSCI_HAL_EnableReceiver(base);

                /* Set the funciton pointer for send and receive for this kind of device. */
                s_debugConsole.ops.tx_union.UART0_Send = LPSCI_HAL_SendDataPolling;
                s_debugConsole.ops.rx_union.UART0_Receive = LPSCI_HAL_ReceiveDataPolling;
            }
            break;
#endif
#if defined(LPUART_INSTANCE_COUNT)
        case kDebugConsoleLPUART:
            {
                LPUART_Type* g_Base[LPUART_INSTANCE_COUNT] = LPUART_BASE_PTRS;
                LPUART_Type* base = g_Base[uartInstance];
                uint32_t lpuartSourceClock;

                s_debugConsole.base = base;
                CLOCK_SYS_EnableLpuartClock(uartInstance);

                /* LPUART clock source is either system or bus clock depending on instance */
                lpuartSourceClock = CLOCK_SYS_GetLpuartFreq(uartInstance);

                /* initialize the parameters of the LPUART config structure with desired data */
                LPUART_HAL_SetBaudRate(base, lpuartSourceClock, baudRate);
                LPUART_HAL_SetBitCountPerChar(base, kLpuart8BitsPerChar);
                LPUART_HAL_SetParityMode(base, kLpuartParityDisabled);
                LPUART_HAL_SetStopBitCount(base, kLpuartOneStopBit);

                /* finally, enable the LPUART transmitter and receiver */
                LPUART_HAL_SetTransmitterCmd(base, true);
                LPUART_HAL_SetReceiverCmd(base, true);

                /* Set the funciton pointer for send and receive for this kind of device. */
                s_debugConsole.ops.tx_union.LPUART_Send = LPUART_HAL_SendDataPolling;
                s_debugConsole.ops.rx_union.LPUART_Receive = LPUART_HAL_ReceiveDataPolling;

            }
            break;
#endif
        /* If new device is requried as the low level device for debug console,
         * Add the case branch and add the preprocessor macro to judge whether
         * this kind of device exist in this SOC. */
        default:
            /* Device identified is invalid, return invalid device error code. */
            return kStatus_DEBUGCONSOLE_InvalidDevice;
    }

    /* Configure the s_debugConsole structure only when the inti operation is successful. */
    s_debugConsole.instance = uartInstance;

    return kStatus_DEBUGCONSOLE_Success;
}

/* See fsl_debug_console.h for documentation of this function.*/
debug_console_status_t DbgConsole_DeInit(void)
{
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return kStatus_DEBUGCONSOLE_Success;
    }

    switch(s_debugConsole.type)
    {
#if defined(UART_INSTANCE_COUNT)
        case kDebugConsoleUART:
            CLOCK_SYS_DisableUartClock(s_debugConsole.instance);
            break;
#endif
#if defined(UART0_INSTANCE_COUNT)
        case kDebugConsoleLPSCI:
            CLOCK_SYS_DisableLpsciClock(s_debugConsole.instance);
            break;
#endif
#if defined(LPUART_INSTANCE_COUNT)
        case kDebugConsoleLPUART:
             CLOCK_SYS_DisableLpuartClock(s_debugConsole.instance);
            break;
#endif
#if (defined(USB_INSTANCE_COUNT) && defined(BOARD_USE_VIRTUALCOM))
        case kDebugConsoleUSBCDC:
             VirtualCom_Deinit();
             CLOCK_SYS_DisableUsbfsClock(0);
            break;
#endif
        default:
            return kStatus_DEBUGCONSOLE_InvalidDevice;
    }

    s_debugConsole.type = kDebugConsoleNone;
    return kStatus_DEBUGCONSOLE_Success;
}

#if (defined(__KSDK_STDLIB__))
int _WRITE(int fd, const void *buf, size_t nbytes)
{
    if (buf == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }


    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Send data.*/
    s_debugConsole.ops.tx_union.Send(s_debugConsole.base, (uint8_t const *)buf, nbytes);
    return nbytes;

}

int _READ(int fd, void *buf, size_t nbytes)
{

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Receive data.*/
    s_debugConsole.ops.rx_union.Receive(s_debugConsole.base, buf, nbytes);
    return nbytes;
}
#elif __ICCARM__

#pragma weak __write
size_t __write(int handle, const unsigned char * buffer, size_t size)
{
    if (buffer == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }

    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != _LLIO_STDOUT) && (handle != _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return _LLIO_ERROR;
    }

    /* Send data.*/
    s_debugConsole.ops.tx_union.Send(s_debugConsole.base, (uint8_t const *)buffer, size);
    return size;
}

#pragma weak __read
size_t __read(int handle, unsigned char * buffer, size_t size)
{
    /* This function only reads from "standard in", for all other file*/
    /* handles it returns failure.*/
    if (handle != _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return _LLIO_ERROR;
    }

    /* Receive data.*/
    s_debugConsole.ops.rx_union.Receive(s_debugConsole.base, buffer, size);

    return size;
}

#elif (defined(__GNUC__))
#pragma weak _write
int _write (int handle, char *buffer, int size)
{
    if (buffer == 0)
    {
        /* return -1 if error */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != 1) && (handle != 2))
    {
        return -1;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Send data.*/
    s_debugConsole.ops.tx_union.Send(s_debugConsole.base, (uint8_t *)buffer, size);
    return size;
}

#pragma weak _read
int _read(int handle, char *buffer, int size)
{
    /* This function only reads from "standard in", for all other file*/
    /* handles it returns failure.*/
    if (handle != 0)
    {
        return -1;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Receive data.*/
    s_debugConsole.ops.rx_union.Receive(s_debugConsole.base, (uint8_t *)buffer, size);
    return size;
}
#elif defined(__CC_ARM) && !defined(MQX_STDIO)
struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

/* FILE is typedef in stdio.h. */
#pragma weak __stdout
FILE __stdout;
FILE __stdin;

#pragma weak fputc
int fputc(int ch, FILE *f)
{
    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Send data.*/
    s_debugConsole.ops.tx_union.Send(s_debugConsole.base, (const uint8_t*)&ch, 1);
    return 1;
}

#pragma weak fgetc
int fgetc(FILE *f)
{
    uint8_t temp;
    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }

    /* Receive data.*/
    s_debugConsole.ops.rx_union.Receive(s_debugConsole.base, &temp, 1);
    return temp;
}

#endif

/*************Code for debug_printf/scanf/assert*******************************/
int debug_printf(const char  *fmt_s, ...)
{
   va_list  ap;
   int  result;
   /* Do nothing if the debug uart is not initialized.*/
   if (s_debugConsole.type == kDebugConsoleNone)
   {
       return -1;
   }
   va_start(ap, fmt_s);
   result = _doprint(NULL, debug_putc, -1, (char *)fmt_s, ap);
   va_end(ap);

   return result;
}

static int debug_putc(int ch, void* stream)
{
    const unsigned char c = (unsigned char) ch;
    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }
    s_debugConsole.ops.tx_union.Send(s_debugConsole.base, &c, 1);

    return 0;

}

int debug_putchar(int ch)
{
    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }
    debug_putc(ch, NULL);

    return 1;
}

int debug_scanf(const char  *fmt_ptr, ...)
{
    char    temp_buf[IO_MAXLINE];
    va_list ap;
    uint32_t i;
    char result;

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }
    va_start(ap, fmt_ptr);
    temp_buf[0] = '\0';

    for (i = 0; i < IO_MAXLINE; i++)
    {
        temp_buf[i] = result = debug_getchar();

        if ((result == '\r') || (result == '\n'))
        {
            /* End of Line */
            if (i == 0)
            {
                i = (uint32_t)-1;
            }
            else
            {
                break;
            }
        }

        temp_buf[i + 1] = '\0';
    }

    result = scan_prv(temp_buf, (char *)fmt_ptr, ap);
    va_end(ap);

   return result;
}

int debug_getchar(void)
{
    unsigned char c;

    /* Do nothing if the debug uart is not initialized.*/
    if (s_debugConsole.type == kDebugConsoleNone)
    {
        return -1;
    }
    s_debugConsole.ops.rx_union.Receive(s_debugConsole.base, &c, 1);

    return c;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
