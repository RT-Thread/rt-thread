/**
 * \file
 *
 * \brief Syscalls for SAM0 (GCC).
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#undef errno
extern int errno;
extern int _end;

extern caddr_t _sbrk(int incr);
extern int     link(char *old, char *_new);
extern int     _close(int file);
extern int     _fstat(int file, struct stat *st);
extern int     _isatty(int file);
extern int     _lseek(int file, int ptr, int dir);
extern void    _exit(int status);
extern void    _kill(int pid, int sig);
extern int     _getpid(void);

/**
 * \brief Replacement of C library of _sbrk
 */
extern caddr_t _sbrk(int incr)
{
	static unsigned char *heap = NULL;
	unsigned char *       prev_heap;

	if (heap == NULL) {
		heap = (unsigned char *)&_end;
	}
	prev_heap = heap;

	heap += incr;

	return (caddr_t)prev_heap;
}

/**
 * \brief Replacement of C library of link
 */
extern int link(char *old, char *_new)
{
	(void)old, (void)_new;
	return -1;
}

/**
 * \brief Replacement of C library of _close
 */
extern int _close(int file)
{
	(void)file;
	return -1;
}

/**
 * \brief Replacement of C library of _fstat
 */
extern int _fstat(int file, struct stat *st)
{
	(void)file;
	st->st_mode = S_IFCHR;

	return 0;
}

/**
 * \brief Replacement of C library of _isatty
 */
extern int _isatty(int file)
{
	(void)file;
	return 1;
}

/**
 * \brief Replacement of C library of _lseek
 */
extern int _lseek(int file, int ptr, int dir)
{
	(void)file, (void)ptr, (void)dir;
	return 0;
}
#if 0
/**
 * \brief Replacement of C library of _exit
 */
extern void _exit(int status)
{
	printf("Exiting with status %d.\n", status);

	for (;;)
		;
}
#endif
/**
 * \brief Replacement of C library of _kill
 */
extern void _kill(int pid, int sig)
{
	(void)pid, (void)sig;
	return;
}

/**
 * \brief Replacement of C library of _getpid
 */
extern int _getpid(void)
{
	return -1;
}

#ifdef __cplusplus
}
#endif
