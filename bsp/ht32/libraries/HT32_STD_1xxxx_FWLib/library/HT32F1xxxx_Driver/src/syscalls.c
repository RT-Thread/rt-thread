/*********************************************************************************************************//**
 * @file    syscalls.c
 * @version $Rev:: 2904         $
 * @date    $Date:: 2023-03-27 #$
 * @brief   Implementation of system call related functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

/** @addtogroup HT32_Peripheral_Driver HT32 Peripheral Driver
  * @{
  */

/** @defgroup SYSCALLS System call functions
  * @brief System call functions for GNU toolchain
  * @{
  */


/* Global variables ----------------------------------------------------------------------------------------*/
/** @defgroup SYSCALLS_Global_Variable System call global variables
  * @{
  */
#undef errno
extern int errno;
extern int  _end;
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SYSCALLS_Exported_Functions System call exported functions
  * @{
  */
caddr_t _sbrk(int incr)
{
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;

  if (heap == NULL)
  {
    heap = (unsigned char *)&_end;
  }
  prev_heap = heap;

  heap += incr;

  return (caddr_t) prev_heap;
}

int link(char *old, char *new) {
return -1;
}

int _close(int fd)
{
  return -1;
}

int _fstat(int fd, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd)
{
  return 1;
}

int _lseek(int fd, int ptr, int dir)
{
  return 0;
}

int _read(int fd, char *ptr, int len)
{
  return 0;
}

int _write(int fd, char *ptr, int len)
{
  return len;
}

void abort(void)
{
  /* Abort called                                                                                           */
  while (1);
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
