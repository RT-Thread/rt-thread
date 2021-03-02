/**
    *****************************************************************************
    * @file     cmem7_conf.h
    *
    * @brief    CMEM7 config file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_CONF_H
#define __CMEM7_CONF_H

#define _ADC
#define _AES
#define _CAN
#define _DDR
#define _DMA
#define _EFUSE
#define _ETH
#define _FLASH
#define _GPIO
#define _I2C
#define _MISC
#define _RTC
#define _SPI
#define _TIM
#define _UART
#define _USB
#define _WDG

//#define _MARVELL
//#define _IP1826D
#define _M7NORFLASH
#define _ME_6095_F

#define USE_FULL_ASSERT    1

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((unsigned char *)__FILE__, __LINE__))

    static void assert_failed(unsigned char* file, unsigned long line) {
        while (1) {
            ;
        }
    }
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

typedef enum _BOOL {FALSE = 0, TRUE = 1} BOOL;

/**
  * System clock frequency, unit is Hz.
  */
#define SYSTEM_CLOCK_FREQ        300000000
//250000000
//300000000

/**
  * @brief  usecond delay
    * @note     It can't delay in an accurate time
    * @param[in] usec usecond to be delay
    * @retval None
    */
static void udelay(unsigned long usec) {
  unsigned long count = 0;
  unsigned long utime = SYSTEM_CLOCK_FREQ / 1000000 * usec;

  while(++count < utime) ;
}

/**
  * UART definition for print
    */
#define PRINT_UART                          UART2

/**
  * DDR type definition
  */
#define DDR_TYPE                3   // 2 for DDR2, 3 for DDR3

#if (DDR_TYPE == 3)
# define DDR_SIZE               (256 << 20)
#elif (DDR_TYPE == 2)
# define DDR_SIZE               (128 << 20)
#else
# error
#endif

#endif /* __CMEM7_CONF_H */

