/*********************************************************************************************************//**
 * @file    IP/Example/ht32f1xxxx_conf.h
 * @version $Rev:: 2922         $
 * @date    $Date:: 2023-06-07 #$
 * @brief   Library configuration file.
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
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F1XXXX_CONF_H
#define __HT32F1XXXX_CONF_H

/* Exported constants --------------------------------------------------------------------------------------*/

#define RETARGET_ITM        0
#define RETARGET_USB        1
#define RETARGET_SYSLOG     2
#define RETARGET_COM1       10
#define RETARGET_COM2       11
#define RETARGET_USART0     12
#define RETARGET_USART1     13
#define RETARGET_UART0      14
#define RETARGET_UART1      15


/* Retarget settings of the C standard I/O library functions (printf, scanf, getchar, ...etc.)              */
/*
//  <q> Enable Retarget
//  <o1> Retarget Port
//      <0=> ITM
//      <1=> USB Virtual COM
//      <2=> Syslog
//      <10=> COM1
//      <11=> COM2
//      <12=> USART0
//      <13=> USART1
//      <14=> UART0
//      <15=> UART1
//  <q2> Enable Auto Return
//       <i> Auto Return function adds "\r" before "\n" automatically when print message by Retarget.
*/
#define _RETARGET            1
#define RETARGET_PORT        10
#define _AUTO_RETURN         0

#ifndef AUTO_RETURN
#if (_AUTO_RETURN == 1)
#define AUTO_RETURN
#endif
#endif

/* Enable Interrupt Mode for UxART Retarget
// <h> Retarget COM/UxART Setting
//  <o0> UxART Baudrate
//  <q1> Enable Interrupt Mode for UxART Tx Retarget
//  <q2> Define UxARTn_IRQHandler By Retarget (ht32_serial.c)
//    <i> Disable (RETARGET_DEFINE_HANDLER = 0) if application already have UxARTn_IRQHandler.
//    <i> RETARGET_UART_IRQHandler() shall be called by UxARTn_IRQHandler when disable.
//  <o3> Tx Buffer Length (in byte)
// </h>
*/
#define RETARGET_UxART_BAUDRATE       115200
#define RETARGET_INT_MODE             0
#define RETARGET_DEFINE_HANDLER       1
#define RETARGET_INT_BUFFER_SIZE      64

#if (_RETARGET == 1)
#if (RETARGET_PORT == RETARGET_ITM)
#elif (RETARGET_PORT == RETARGET_USB)
  #define RETARGET_IS_USB
//  <h> Retarget USB Virtual COM Setting
//  <o0> Communication (Interrupt IN)
//      <1=> Endpoint 1
//      <2=> Endpoint 2
//      <3=> Endpoint 3
//      <4=> Endpoint 4
//      <5=> Endpoint 5
//      <6=> Endpoint 6
//      <7=> Endpoint 7
//  <o1> Data Rx (Bulk OUT)
//      <1=> Endpoint 1
//      <2=> Endpoint 2
//      <3=> Endpoint 3
//      <4=> Endpoint 4
//      <5=> Endpoint 5
//      <6=> Endpoint 6
//      <7=> Endpoint 7
//  <o2> Data Tx (Bulk IN)
//      <1=> Endpoint 1
//      <2=> Endpoint 2
//      <3=> Endpoint 3
//      <4=> Endpoint 4
//      <5=> Endpoint 5
//      <6=> Endpoint 6
//      <7=> Endpoint 7
//  <o3> Communication Endpoint Buffer Length (in byte) <4-64:4>
//  <o4> Data Rx Endpoint Buffer Length (in byte) <4-64:4>
//  <o5> Data Tx Endpoint Buffer Length (in byte) <4-64:4>
//  <o6> Rx Buffer Length (in byte) <64-1024:4>
//  <o7> Tx Buffer Length (in byte) <1-63:1>
//    <i> Please use "SERIAL_Flush()" to sent out the buffer data immediately when Tx Buffer Length > 1.
//  <o8> USB Tx Mode (BULK IN)
//      <0=> Block Mode (Wait until both USB and terminal software are ready)
//      <1=> Non-Block Mode (Drop data if USB or terminal software is not ready)
//  <q9> Enable HSI Auto Trim By USB Function
//    <i> Need turn on if the USB clock source is from HSI (PLL USBPLL clock Source).
  #define RETARGET_CTRL_EPT      (5)
  #define RETARGET_RX_EPT        (6)
  #define RETARGET_TX_EPT        (7)
  #define RETARGET_CTRL_EPTLEN   (8)
  #define RETARGET_RX_EPTLEN     (64)
  #define RETARGET_TX_EPTLEN     (64)
  #define RETARGET_BUFFER_SIZE   (64)
  #define RETARGET_TXBUFFER_SIZE (1) // Use "SERIAL_Flush()" to sent out the buffer data immediately when Tx Buffer Length > 1.
  #define RETARGET_USB_MODE      (0)
  #define RETARGET_HSI_ATM       (1)
// </h>
#elif (RETARGET_PORT == RETARGET_COM1)
  #define RETARGET_COM_PORT         COM1
  #define RETARGET_USART_PORT       COM1_PORT
  #define RETARGET_UART_IRQn        COM1_IRQn
  #define RETARGET_UART_IRQHandler  COM1_IRQHandler
  #define RETARGET_IS_UART
#elif (RETARGET_PORT == RETARGET_COM2)
  #define RETARGET_COM_PORT         COM2
  #define RETARGET_USART_PORT       COM2_PORT
  #define RETARGET_UART_IRQn        COM2_IRQn
  #define RETARGET_UART_IRQHandler  COM2_IRQHandler
  #define RETARGET_IS_UART
#elif (RETARGET_PORT == RETARGET_USART0)
  #define RETARGET_UxART_IPN        USART0
  #define RETARGET_USART_PORT       STRCAT2(HT_, RETARGET_UxART_IPN)
  #define RETARGET_UART_IRQn        STRCAT2(RETARGET_UxART_IPN, _IRQn)
  #define RETARGET_UART_IRQHandler  STRCAT2(RETARGET_UxART_IPN, _IRQHandler)
  #define RETARGET_IS_UART
#elif (RETARGET_PORT == RETARGET_USART1)
  #define RETARGET_UxART_IPN        USART1
  #define RETARGET_USART_PORT       STRCAT2(HT_, RETARGET_UxART_IPN)
  #define RETARGET_UART_IRQn        STRCAT2(RETARGET_UxART_IPN, _IRQn)
  #define RETARGET_UART_IRQHandler  STRCAT2(RETARGET_UxART_IPN, _IRQHandler)
  #define RETARGET_IS_UART
#elif (RETARGET_PORT == RETARGET_UART0)
  #define RETARGET_UxART_IPN        UART0
  #define RETARGET_USART_PORT       STRCAT2(HT_, RETARGET_UxART_IPN)
  #define RETARGET_UART_IRQn        STRCAT2(RETARGET_UxART_IPN, _IRQn)
  #define RETARGET_UART_IRQHandler  STRCAT2(RETARGET_UxART_IPN, _IRQHandler)
  #define RETARGET_IS_UART
#elif (RETARGET_PORT == RETARGET_UART1)
  #define RETARGET_UxART_IPN        UART1
  #define RETARGET_USART_PORT       STRCAT2(HT_, RETARGET_UxART_IPN)
  #define RETARGET_UART_IRQn        STRCAT2(RETARGET_UxART_IPN, _IRQn)
  #define RETARGET_UART_IRQHandler  STRCAT2(RETARGET_UxART_IPN, _IRQHandler)
  #define RETARGET_IS_UART
#endif
  extern void RETARGET_Configuration(void);
#else
  #define RETARGET_Configuration(...)
  #undef printf
  #undef getchar
  #define printf(...)
  #define getchar()  (0)
#endif

#if (RETARGET_DEFINE_HANDLER == 0)
#undef RETARGET_UART_IRQHandler
#endif

/*
//<e0> Enable HT32 Time Function
//  <i> Provide "Time_GetTick()" and "Time_Dealy()" functions.

//  <o1> Timer Selection
//      <0=> BFTM0
//      <1=> BFTM1
//      <2=> SCTM0
//      <3=> SCTM1
//      <4=> SCTM2
//      <5=> SCTM3
//      <6=> PWM0
//      <7=> PWM1
//      <8=> PWM2
//      <9=> GPTM0
//      <10=> GPTM1
//      <11=> MCTM0

//  <h> Timer Clock Setting
//  </h>
//    <i> Timer Clock = (Core Clock) / (APB Peripheral Clock Prescaler)
//    <i> HTCFG_TIME_CLKSRC = _HTCFG_TIME_CORECLK / (2^HTCFG_TIME_PCLK_DIV)
//    <i> _HTCFG_TIME_CORECLK = LIBCFG_MAX_SPEED or HTCFG_TIME_CLK_MANUAL (selected by HTCFG_TIME_CLKSEL)

//  <o2> -- Core Clock Setting (CK_AHB)
//    <i> HTCFG_TIME_CLKSEL
//    <i> 0 = Default Maximum (LIBCFG_MAX_SPEED)
//    <i> 1 = Manual Input (HTCFG_TIME_CLK_MANUAL)
//       <0=> Default Maximum (LIBCFG_MAX_SPEED)
//       <1=> Manual Input (HTCFG_TIME_CLK_MANUAL)

//  <o3> -- Core Clock Manual Input (Hz)
//    <i> HTCFG_TIME_CLK_MANUAL
//    <i> Only meaningful when Core Clock Setting (HTCFG_TIME_CLKSEL) = Manual Input (1)

//  <o4> -- APB Peripheral Clock Prescaler
//    <i> HTCFG_TIME_PCLK_DIV
//       <0=> /1
//       <1=> /2
//       <2=> /4
//       <3=> /8

//  <o5> Time Tick (Hz, not applicable for BFTM) <1-1000000:100>
//    <i> Not applicable for BFTM, fixed TICKHZ to HTCFG_TIME_CLKSRC for BFTM.
*/
#if (0) // Enable HT32 Time Function
#define HTCFG_TIME_IPSEL                          (0)
#define HTCFG_TIME_CLKSEL                         (0)         // 0 = Default Maximum (LIBCFG_MAX_SPEED), 1 = Manual Input (HTCFG_TIME_CLKSRC)
#define HTCFG_TIME_CLK_MANUAL                     (20000000)  // Only meaningful when HTCFG_TIME_CLKSEL = 1 (Manual Input)
#define HTCFG_TIME_PCLK_DIV                       (0)         // 0 ~ 3. (/1, /2, /4, /8)
#define HTCFG_TIME_TICKHZ                         (1000)      // Hz, not applicable for BFTM, fixed TICKHZ to HTCFG_TIME_CLKSRC for BFTM
#define HTCFG_TIME_MULTIPLE                       (1)         // MUST be 1, 2, 4, 8. TICK = COUNT / MULTIPLE. Not applicable for BFTM.
/*

  Timer Clock = (Core Clock) / (APB Peripheral Clock Prescaler)
  HTCFG_TIME_CLKSRC = (_HTCFG_TIME_CORECLK) / (2^HTCFG_TIME_PCLK_DIV)
  where _HTCFG_TIME_CORECLK can be LIBCFG_MAX_SPEED or HTCFG_TIME_CLK_MANUAL (selected by HTCFG_TIME_CLKSEL)

  Tick Range: 0 ~ 2^32 / HTCFG_TIME_TICKHZ (maximum tick time)
  Interrupt Time: _HTCFG_TIME_OVERFLOW_VALUE / (HTCFG_TIME_TICKHZ * HTCFG_TIME_MULTIPLE) Second
  (Interrupt Time is not applicable for BFTM)

  Example: 32-bit BFTM with 48 MHz Timer Clock
    HTCFG_TIME_TICKHZ = HTCFG_TIME_CLKSRC = 48000000
    Tick Range: 0 ~ 2^32 / 48000000 = 0 ~ 89.478485 Second (maximum tick time, return to 0 every 89.478485 Second)
    BFTM do not use interrupt

  Example: 16-bit GPTM with 1 ms tick
    HTCFG_TIME_TICKHZ = 1000 (Hz)
    HTCFG_TIME_MULTIPLE = 1 (1 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 1000 = 0 ~ 4294967 Second = 0 ~ 49.7 Day (maximum tick time, return to 0 every 49.7 Day)
    Interrupt Time: 65536 / (1000 * 1) = 65.536 Second (Trigger interrupt every 65.536 Second)
*/
#endif
/*
//</e>
*/

/* !!! NOTICE !!!
 * How to adjust the value of High Speed External oscillator (HSE)?
   The default value of HSE is define by "HSE_VALUE" in "ht32fxxxxx_nn.h".
   If your board uses a different HSE speed, please add a new compiler preprocessor
   C define, "HSE_VALUE=n000000" ("n" represents n MHz) in the toolchain/IDE,
   or edit the "HSE_VALUE" in the "ht32f1xxxx_conf.h" file (this file).
*/
/*
//<e0> Enable User Define HSE Value
//  <i> Enable user define HSE value to overwrite default "HSE_VALUE" define in "ht32fxxxxx_nn.h".
//  <o1> HSE Value (Hz)
*/
#if (0)
#define HSE_VALUE                 16000000
#endif
/*
//</e>
*/

/*
//<q> Enable CKOUT Function
*/
#define ENABLE_CKOUT              0


/* The DEBUG definition to enter debug mode for library                                                     */
/*
//<q> Library Debug Mode
*/
#define HT32_LIB_DEBUG      0


/* Enable/disable the specific peripheral inclusion                                                         */

//  <h> Library Inclusion Configuration
/* ADC -----------------------------------------------------------------------------------------------------*/
/*
//<q> ADC Library
*/
#define _ADC          1

/* AES -----------------------------------------------------------------------------------------------------*/
/*
//<q> AES Library
*/
#define _AES          1

/* BFTM ----------------------------------------------------------------------------------------------------*/
/*
//<q> BFTM Library
*/
#define _BFTM         1

/* Clock Control -------------------------------------------------------------------------------------------*/
/*
//<q> Clock Control Library
*/
#define _CKCU         1

/* Comparator/OPA ------------------------------------------------------------------------------------------*/
/*
//<q> Comparator/OPA Library
*/
#define _CMP_OPA      1

/* Comparator ----------------------------------------------------------------------------------------------*/
/*
//<q> Comparator Library
*/
#define _CMP          1

/* CRC -----------------------------------------------------------------------------------------------------*/
/*
//<q> CRC Library
*/
#define _CRC          1

/* CSIF ----------------------------------------------------------------------------------------------------*/
/*
//<q> CSIF Library
*/
#define _CSIF         1

/* EBI -----------------------------------------------------------------------------------------------------*/
/*
//<q> EBI Library
*/
#define _EBI          1

/* EXTI ----------------------------------------------------------------------------------------------------*/
/*
//<q> EXTI Library
*/
#define _EXTI         1

/* Flash ---------------------------------------------------------------------------------------------------*/
/*
//<q> Flash Library
*/
#define _FLASH        1

/* GPIO ----------------------------------------------------------------------------------------------------*/
/*
//<q> GPIO Library
*/
#define _GPIO         1

/* GPTM ----------------------------------------------------------------------------------------------------*/
/*
//<q> GPTM Library
*/
#define _GPTM         1

/* I2C -----------------------------------------------------------------------------------------------------*/
/*
//<q> I2C Library
*/
#define _I2C          1

/* I2S -----------------------------------------------------------------------------------------------------*/
/*
//<q> I2S Library
*/
#define _I2S          1

/* MCTM ----------------------------------------------------------------------------------------------------*/
/*
//<q> MCTM Library
*/
#define _MCTM         1

/* PDMA ----------------------------------------------------------------------------------------------------*/
/*
//<q> PDMA Library
*/
#define _PDMA         1

/* PWM -----------------------------------------------------------------------------------------------------*/
/*
//<q> PWM Library
*/
#define _PWM          1

/* PWRCU ---------------------------------------------------------------------------------------------------*/
/*
//<q> PWRCU Library
*/
#define _PWRCU        1

/* RSTCU ---------------------------------------------------------------------------------------------------*/
/*
//<q> RSTCU Library
*/
#define _RSTCU        1

/* RTC -----------------------------------------------------------------------------------------------------*/
/*
//<q> RTC Library
*/
#define _RTC          1

/* SCI -----------------------------------------------------------------------------------------------------*/
/*
//<q> SCI Library
*/
#define _SCI          1

/* SCTM ----------------------------------------------------------------------------------------------------*/
/*
//<q> SCTM Library
*/
#define _SCTM         1

/* SDIO ----------------------------------------------------------------------------------------------------*/
/*
//<q> SDIO Library
*/
#define _SDIO         1

/* SPI -----------------------------------------------------------------------------------------------------*/
/*
//<q> SPI Library
*/
#define _SPI          1

/* USART ---------------------------------------------------------------------------------------------------*/
/*
//<q0> USART/UART Library
*/
#define _USART        1

/* USBD ----------------------------------------------------------------------------------------------------*/
/*
//<q> USB Library
*/
#define _USB          1

/* WDT -----------------------------------------------------------------------------------------------------*/
/*
//<q> WDT Library
*/
#define _WDT          1

/* Misc ----------------------------------------------------------------------------------------------------*/
/*
//<q> Misc Library
*/
#define _MISC         1

/* Serial --------------------------------------------------------------------------------------------------*/
/*
//<q> Serial Library
*/
#define _SERIAL       1

/* Software Random Number ----------------------------------------------------------------------------------*/
/*
//<q> Software Random Number Library
*/
#define _SWRAND       1


// </h>

#endif
