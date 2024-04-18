/*********************************************************************************************************//**
 * @file    ht32_retarget.c
 * @version $Rev:: 6977         $
 * @date    $Date:: 2023-06-07 #$
 * @brief   Retarget layer for target-dependent low level functions.
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
#include "ht32.h"
#include "ht32_board.h"

#if defined (__CC_ARM)
  #pragma import(__use_no_semihosting_swi)
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #ifndef __MICROLIB
  __asm(".global __use_no_semihosting");
  #endif
#endif

#if (_RETARGET == 1)
#include <stdio.h>

#if defined (__CC_ARM)
  #include <rt_misc.h>
#endif

/** @addtogroup HT32_Peripheral_Driver HT32 Peripheral Driver
  * @{
  */

/** @defgroup RETARGET Retarget
  * @brief Retarget related functions
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Private_Define Retarget private definitions
  * @{
  */

#if (RETARGET_PORT == RETARGET_ITM)
#define ITM_PORT8(n)    (*((vu8 *)(0xE0000000 + 4 * n)))
#define ITM_PORT16(n)   (*((vu16 *)(0xE0000000 + 4 * n)))
#define ITM_PORT32(n)   (*((vu32 *)(0xE0000000 + 4 * n)))

#define DEMCR           (*((vu32 *)(0xE000EDFC)))
#define TRCENA          (0x01000000)
volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY; /* For Keil MDK-ARM only                                */
#endif
/**
  * @}
  */

/* Global variables ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Global_Variable Retarget global variables
  * @{
  */
#if defined (__CC_ARM)
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #ifndef __MICROLIB
  FILE __stdout;
  FILE __stdin;
  FILE __stderr;
  #endif
#endif

#if defined (__SES_ARM) && defined(__SEGGER_RTL_VERSION)
struct __SEGGER_RTL_FILE_impl {         // NOTE: Provides implementation for FILE
  int stub; // only needed so impl has size != 0.
};
static FILE __SEGGER_RTL_stdin_file  = { 0 };  // stdin reads from UART
static FILE __SEGGER_RTL_stdout_file = { 0 };  // stdout writes to UART
static FILE __SEGGER_RTL_stderr_file = { 0 };  // stderr writes to UART

FILE *stdin  = &__SEGGER_RTL_stdin_file;  // NOTE: Provide implementation of stdin for RTL.
FILE *stdout = &__SEGGER_RTL_stdout_file; // NOTE: Provide implementation of stdout for RTL.
FILE *stderr = &__SEGGER_RTL_stderr_file; // NOTE: Provide implementation of stderr for RTL.

static int          _stdin_ungot  = EOF;
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Exported_Functions Retarget exported functions
  * @{
  */

void RETARGET_Configuration(void)
{
#ifdef RETARGET_IS_UART
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  USART_InitTypeDef USART_InitStructure;
  #ifdef RETARGET_UxART_BAUDRATE
  USART_InitStructure.USART_BaudRate = RETARGET_UxART_BAUDRATE;
  #else
  USART_InitStructure.USART_BaudRate = 115200;
  #endif
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  #ifdef RETARGET_COM_PORT
  HT32F_DVB_COMInit(RETARGET_COM_PORT, &USART_InitStructure);
  #else
  { /* Enable peripheral clock of UxART                                                                     */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.RETARGET_UxART_IPN        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  USART_Init(RETARGET_USART_PORT, &USART_InitStructure);
  USART_TxCmd(RETARGET_USART_PORT, ENABLE);
  USART_RxCmd(RETARGET_USART_PORT, ENABLE);
  #if (RETARGET_INT_MODE == 1)
  NVIC_EnableIRQ(RETARGET_UART_IRQn);
  #endif
  #endif
#endif

#if (RETARGET_PORT == RETARGET_ITM)
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  CKCU_MCUDBGConfig(CKCU_DBG_TRACE_ON, ENABLE);
  AFIO_GPxConfig(TRACESWO_GPIO_ID, TRACESWO_AFIO_PIN, TRACESWO_AFIO_MODE);
#endif

#ifdef NON_USB_IN_APP
  SERIAL_USBDInit();
#endif
}

int __backspace(FILE *stream)
{
  if (stream == 0) // Remove the compiler warning
  {
  }
  return 0;
}

/*
  Keil and IAR before 9.20 share fputc() to implement printf
*/
int fputc (int ch, FILE *f)
{
  #if 0
  if (f == 0) // Remove the compiler warning
  {
  }
  #endif
  #if (RETARGET_PORT == RETARGET_ITM)
  if (DEMCR & TRCENA)
  {
    while (ITM_PORT32(0) == 0);
    ITM_PORT8(0) = ch;
  }
  return (ch);
  #else
  #ifdef AUTO_RETURN
  if (ch == '\n')
  {
    SERIAL_PutChar('\r');
  }
  #endif
  return (SERIAL_PutChar(ch));
  #endif
}

#if defined (__ICCARM__)
#if (__VER__ > 9010000)
/*
  IAR's version after 9.20 use write to implement printf
*/
int __write(int Handle,
            const unsigned char * Buf,
            int Bufsize)
{
  size_t nChars = 0;
  if (Handle == -1)
  {
    return 0;
  }
  /* Check for stdout and stderr
     (only necessary if FILE descriptors are enabled.)  */
  if (Handle != 1 && Handle != 2)
  {
    return -1;
  }
  for (/*Empty */; Bufsize > 0; --Bufsize)
  {
    SERIAL_PutChar(*Buf++);
    ++nChars;
  }
  return nChars;
}
#endif
int __read(int Handle, unsigned char *Buf, size_t BufSize)
{
  #if (RETARGET_PORT != RETARGET_ITM)
  int nChars = 0;

  if (Handle != 0)
  {
    return -1;
  }

  for (/* Empty */; BufSize > 0; --BufSize)
  {
    unsigned char c = NULL;
    c = SERIAL_GetChar();
    if (c == 0)
      break;
    *Buf++ = c;
    ++nChars;
  }
  #endif
  return nChars;
}

#elif defined(__SES_ARM)
#if defined(__SEGGER_RTL_VERSION)
/*
  SES's version after 6.20 use RTL to implement printf.
*/
/*********************************************************************************************************//**
 * @brief Get character from standard input..
 * @retval Character received.
 ************************************************************************************************************/
static char _stdin_getc(void) {
  unsigned char c;

  if (_stdin_ungot != EOF) {
    c = _stdin_ungot;
    _stdin_ungot = EOF;
  } else {
    c = SERIAL_GetChar();
  }
  return c;
}

/*********************************************************************************************************//**
  * @brief Get file status.
  * @param Pointer to file.
  * @retval -1: Failure, stream is not a valid file. 0: Success, stream is a valid file.
  ***********************************************************************************************************/
int __SEGGER_RTL_X_file_stat(FILE *stream) {
  if (stream == stdin || stream == stdout || stream == stderr) {
    return 0;       // NOTE: stdin, stdout, and stderr are assumed to be valid.
  } else {
    return EOF;
  }
}

/*********************************************************************************************************//**
  * @brief  Get stream buffer size.
  * @param  stream: Pointer to file.
  * @retval Nonzero number of characters to use for buffered I/O; for unbuffered I/O, return 1.
  ***********************************************************************************************************/
int __SEGGER_RTL_X_file_bufsize(FILE *stream) {
  (void)stream;
  return 1;
}

/*********************************************************************************************************//**
  * @brief  Read data from file.
  * @param  stream: Pointer to file to read from.
  * @param  s: Pointer to object that receives the input.
  * @param  len: Number of characters to read from file.
  * @retval -1: Failure, stream is not a valid file. >0: Success, stream is a valid file.
  ***********************************************************************************************************/
int __SEGGER_RTL_X_file_read(FILE *stream, char *s, unsigned len) {
  int c;

  if (stream == stdin) {
    c = 0;
    while (len > 0) {
      *s = _stdin_getc();
      ++s;
      ++c;
      --len;
    }
  } else {
    c = EOF;
  }
  return c;
}

/*********************************************************************************************************//**
  * @brief  Write data to file.
  * @param  stream: Pointer to file to write to.
  * @param  s:Pointer to object to write to file.
  * @param  len:Number of characters to write to the file.
  * @retval -1: Failure, stream is not a valid file. >0: Success, stream is a valid file.
  ***********************************************************************************************************/
int __SEGGER_RTL_X_file_write(FILE *stream, const char *s, unsigned len) {
  if ((stream == stdout) || (stream == stderr)) {
    //BSP_UART_WriteBlocking(_UART_Port, (const unsigned char*) s, len);
    for (/*Empty */; len > 0; --len)
    {
      SERIAL_PutChar(*s++);
    }
    return len;
  } else {
    return EOF;
  }
}

/*********************************************************************************************************//**
  * @brief  ush character back to stream.
  * @param  stream: Pointer to file to push back to.
  * @param  c: Character to push back.
  * @retval -1: Failure, stream is not a valid file. >0: Success, stream is a valid file.
  ***********************************************************************************************************/
int __SEGGER_RTL_X_file_unget(FILE *stream, int c) {
  if (stream == stdin) {
    if (c != EOF && _stdin_ungot == EOF) {
      _stdin_ungot = c;
    } else {
      c = EOF;
    }
  } else {
    c = EOF;
  }
  return c;
}
#endif
#else
int fgetc (FILE *f)
{
  #if 0
  if (f == 0) // Remove the compiler warning
  {
  }
  #endif
  #if (RETARGET_PORT == RETARGET_ITM)
  /* For Keil MDK-ARM only                                                                                  */
  while (ITM_CheckChar() == 0);
  return (ITM_ReceiveChar());
  #else
  return (SERIAL_GetChar());
  #endif
}
#endif

void _ttywrch(int ch)
{
  #if (RETARGET_PORT == RETARGET_ITM)
  if (DEMCR & TRCENA)
  {
    while (ITM_PORT32(0) == 0);
    ITM_PORT8(0) = ch;
  }
  #else
  SERIAL_PutChar(ch);
  #endif
}
#endif

void _sys_exit(int return_code)
{
  if (return_code == 0) // Remove the compiler warning
  {
  }

label:  goto label;  /* endless loop                                                                        */
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
