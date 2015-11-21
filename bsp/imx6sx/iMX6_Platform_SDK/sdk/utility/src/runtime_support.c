/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file  runtime_support.c
 * @brief Support routines for the newlib C Standard Library implementation.
 *
 * @ingroup diag_util
 */

#include <reent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include "uart/imx_uart.h"
#include "sdk.h"
#include "timer/timer.h"

//! Set this define to 1 to have _write() convert LF line endings to CRLF
#define CONVERT_LF_TO_CRLF 1

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

// Must redefine errno as an extern int according to newlib docs.
#undef errno
extern int errno;

//! @name Malloc heap extents
//! 
//! Defined in the linker script.
//@{
extern int free_memory_start;
extern int free_memory_end;
//@}

//! @name Environment
//@{
char * __env[1] = { 0 };
char ** environ = __env;
//@}

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}

int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*!
 * @brief Check to see if a terminal device is connected or not.
 * @return 1 always to indicate a serial port exists always
 */
int _isatty(int fd)
{
    return 1;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

/*!
 * @brief Close a file descriptor.
 * @retval  -1
 */
int _close(int fd)
{
    return -1;
}

/*!
 * @brief Move read/write pointer.
 * @return 0 is always returned as specified in the newlib documentation for a minimal implementation.
 */
off_t _lseek(int fd, off_t offset, int whence)
{
    return (off_t)0;
}

/*!
 * @brief Get status of a file.
 *
 * @return 0 is always returned as specified in the newlib documentation for a minimal implementation.
 */
int _fstat(int fd, struct stat * st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*!
 * @brief Read characters from the serial port.
 *
 * It reads up to nbytes data or till a new line (someone hits enter).
 *
 * @param   fd      not used
 * @param   buf     pointer to the buffer for the receiving characters via serial port
 * @param   nbytes  Maximum number of characters that can be received.
 *
 * @return  the number of characters actually read
 */
int _read(int fd, char *buf, int nbytes)
{
    int i = 0, j = 1;

    for (i = 0; i < nbytes; ++i)
    {
        *buf = uart_getchar(g_debug_uart_port);

        if ((*buf == '\n') || (*buf == '\r'))
        {
            break;
        } else if(*buf != 0xFF) {
            ++j;
            ++buf;
        }
    }

    return j;
}

/*!
 * @brief Write chars to the serial port.
 *
 * Ignore fd, since stdout and stderr are the same.
 * Since we have no filesystem, open will only return an error.
 *
 * If the #CONVERT_LF_TO_CRLF macro is set to 1, this function will convert any single
 * LF chars into CRLF pairs.
 *
 * @param   fd      not used
 * @param   buf     pointer to the buffer of data to the serial port
 * @param   nbytes  number of bytes to write to the serial port
 * @return  number of bytes to write to the serial port
 */
int _write(int fd, char *buf, int nbytes)
{
    int i;

    for (i = 0; i < nbytes; ++i, ++buf)
    {
#if CONVERT_LF_TO_CRLF
        static bool lastCharWasCR = false;
        
        // Insert a CR before the LF, unless the previous char in the source
        // buffer was a CR. This is to prevent converting a CRLF to CRCRLF.
        if (*buf == '\n' && !lastCharWasCR)
        {
            uint8_t cr = '\r';
            uart_putchar(g_debug_uart_port, &cr);
        }
#endif // CONVERT_LF_TO_CRLF
        
        // Send the char out the debug UART.
        uart_putchar(g_debug_uart_port, (uint8_t *)buf);
        
#if CONVERT_LF_TO_CRLF
        lastCharWasCR = (*buf == '\r');
#endif // CONVERT_LF_TO_CRLF
    }

    return nbytes;
}


/*!
 * @brief Write string to the serial port without buffering
 *
 * @param   str      not used
 * @return  number of bytes to write to the serial port
 */
int _raw_puts(char str[])
{
    int i;

    int len = strlen(str);
    
    for (i = 0; i < len; i++)
    {        
        // Send the char out the debug UART.
        uart_putchar(g_debug_uart_port, (uint8_t *)&str[i]);
    }

    return len;
}

/*!
 * @brief The low level system call upon which malloc is built.
 *
 * Here is a very simple implementation. The heap ranges from the variables
 * @i free_memory_start to @i free_memory_end that must be defined in the linker
 * script. Allocation starts at @i free_memory_start.
 *
 * If we run out of memory, a message is printed and abort() is called.
 *
 * @param   nbytes  the number of bytes to be allocated from the heap
 * @return  the previous heap address
 */
caddr_t _sbrk(int nbytes)
{
    static caddr_t heap_ptr = NULL;
    caddr_t base;

    if (heap_ptr == NULL)
    {
        heap_ptr = (caddr_t)&free_memory_start;
    }

    base = heap_ptr;
    heap_ptr += nbytes;
    
    // Abort if we run out of memory.
    if (heap_ptr > (caddr_t)&free_memory_end)
    {
        _write(1, "** Heap ran out of memory! **\n", 24);
        abort();
    }
    
    return base;
}

__attribute__ ((noreturn)) void _exit(int status)
{
    _sys_exit(status);
    while (1) ;
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

pid_t _getpid()
{
    return 1;
}

int _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}

int _unlink(char *name)
{
    errno = ENOENT;
    return -1; 
}

int _stat(const char *file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

clock_t _times(struct tms *buf)
{
    return -1;
}

int _gettimeofday(struct timeval *ptimeval, void *ptimezone)
{
    if (ptimeval)
    {
        uint64_t us = time_get_microseconds();
        ptimeval->tv_sec = us / 1000000;
        ptimeval->tv_usec = us - ptimeval->tv_sec;
    }
    
    return 0;
}

int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////


    
