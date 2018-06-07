/*
 * File      : nuc970_sys.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#ifndef DRIVERS_NUC97X_SYS_H_
#define DRIVERS_NUC97X_SYS_H_

#ifdef __cplusplus
extern "C" {
#endif

/** \brief  Structure type of clock source
 */
typedef enum CLKn {

    SYS_UPLL     = 1,   /*!< UPLL clock */
    SYS_APLL     = 2,   /*!< APLL clock */
    SYS_SYSTEM   = 3,   /*!< System clock */
    SYS_HCLK1    = 4,   /*!< HCLK1 clock */
    SYS_HCLK234  = 5,   /*!< HCLK234 clock */
    SYS_PCLK     = 6,   /*!< PCLK clock */
    SYS_CPU      = 7,   /*!< CPU clock */

}  CLK_Type;

INT32 sysGetPLL(UINT32 reg);
UINT32 sysGetClock(CLK_Type clk);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_NUC97X_SYS_H_ */
