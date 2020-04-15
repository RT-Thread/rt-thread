/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_errno.h
 * @brief    header file for error num
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

/******************************************************************************
 * @file
 * @details     Error code field difination
 *              Error number is devided into 4 field:
 *              0x8******* : 8  : means < 0
 *              0x*A****** : A  : means type number: bsp(1), driver(2), hal(3), app(4)...
 *              0x**AB**** : AB : means module number: timer(1), rtc(2), ....
 *              0x****AB** : AB : means API number: module API's definition
 *              0x******AB : AB : means sub error number
 *                                  0 ~ 0x80 is common error such as EPERM, refer to errno.h
 *                                  0x80 ~ 0xFF is specific error, can difine in module
 *
 *              For example 0x81020113 means:
 *                  1. 0x8*******: value < 0, means error happened
 *                  2. 0x*1******: type number is 1, means bsp error
 *                  3. 0x**02****: module number is 02, means RTC error
 *                  4. 0x****01**: module API is 01, means RTC's init
 *                  5. 0x******13: specific error is 0x13=19=ENODEV, means no such device
 *
 *              For special bsp module example, you can return:
 *                  (BSP_ERRNO_TIMER_BASE | BSP_API_RTC_INIT | EPERM)    for rtc init error
 *                  (BSP_ERRNO_TIMER_BASE | BSP_API_RTC_SETTIME | ENXIO) for rtc settime error
 *
 *              Here list the common sub error number (0x******AB) below(0~127 defined in errno.h as standard err code):
 *              Code          Hex    Deci   Meaning
 *              -------------------------------------------------------
 *              EPERM         0x01    1   Operation not permitted
 *              EIO           0x05    5   I/O error
 *              ENXIO         0x06    6   No such device or address
 *              ENOMEM        0x0C   12   Out of memory
 *              EACCES        0x0D   13   Permission denied
 *              EINVAL        0x16   22      Invalid argument
 *              ...
 *              SPEC_ERR_BASE 0x80  128   module special error number base
 *              ...
 *              ERRNO_MAX     0xFF   --   Max sub error number
 ******************************************************************************/

#ifndef _DRV_ERRNO_H_
#define _DRV_ERRNO_H_


#include <errno.h>

#define ERRNO_DRV_START 0X80

/* drvier General return codes */
typedef enum {
    EDRV = ERRNO_DRV_START,   ///< Unspecified error
    EDRV_BUSY,                ///< Driver is busy
    EDRV_TIMEOUT,             ///< Timeout occurred
    EDRV_UNSUPPORTED,         ///< Operation not supported
    EDRV_PARAMETER,           ///< Parameter error
    EDRV_SPECIFIC             ///< Start of driver specific errors
} drv_common_err_e;


/** Get error type */
#define GET_ERROR_TYPE(errno) \
    (error & 0xFF000000 >> 24)
/** Get error module */
#define GET_ERROR_MODULE(error) \
    (error & 0x00FF0000 >> 16)
/** Get error API */
#define GET_ERROR_API(error) \
    (error & 0x0000FF00 >> 8)
/** Get errno */
#define GET_ERROR_NUM(error) \
    (error & 0x000000FF)

#ifndef CSI_DRV_ERRNO_BASE
/** means bsp errors */
#define CSI_DRV_ERRNO_BASE          0x81000000
#endif

/** driver module id definition*/
#define CSI_DRV_ERRNO_GPIO_BASE     0x81010000
#define CSI_DRV_ERRNO_USART_BASE    0x81020000
#define CSI_DRV_ERRNO_SPI_BASE      0x81030000
#define CSI_DRV_ERRNO_I2C_BASE      0x81040000
#define CSI_DRV_ERRNO_FLASH_BASE    0x81050000
#define CSI_DRV_ERRNO_PWM_BASE      0x81060000
#define CSI_DRV_ERRNO_RTC_BASE      0x81070000
#define CSI_DRV_ERRNO_TIMER_BASE    0x81080000
#define CSI_DRV_ERRNO_WDT_BASE      0x81090000
#define CSI_DRV_ERRNO_AES_BASE      0x810A0000
#define CSI_DRV_ERRNO_CRC_BASE      0x810B0000
#define CSI_DRV_ERRNO_RSA_BASE      0x810C0000
#define CSI_DRV_ERRNO_SHA_BASE      0x810D0000
#define CSI_DRV_ERRNO_TRNG_BASE     0x810E0000
#define CSI_DRV_ERRNO_EFLASH_BASE   0x810F0000
#define CSI_DRV_ERRNO_DMA_BASE      0x81100000

#endif /* CSI_DRV_ERRNO_H */
