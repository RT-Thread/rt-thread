/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-06     xiaonong      first version.
 */

#ifndef __DRV_SD_H
#define __DRV_SD_H

#include <stdint.h>
#include <rtthread.h>
#include <LPC54608.h>
#include "fsl_card.h"
#include "fsl_iocon.h"
#include <rtdevice.h>

#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC2               0x02u   /*!< Selects pin function 2 */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_MODE_PULLUP         0x20u   /*!< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_FAST         0x0400u   /*!< Fast mode, slew rate control is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port 2 */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port 2 */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port 2 */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port 2 */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port 2 */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port 2 */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port 2 */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port 2 */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port 3 */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port 1 */
#define PIN28_IDX                       28u   /*!< Pin number for pin 28 in a port 1 */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port 0 */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */
#define PORT1_IDX                        1u   /*!< Port index */
#define PORT2_IDX                        2u   /*!< Port index */
#define PORT3_IDX                        3u   /*!< Port index */

struct mci_device
{
    struct rt_device                parent;      /**< RT-Thread device struct */
    struct rt_device_blk_geometry   geometry;    /**< sector size, sector count */
    sd_card_t                       card;        /**< Card descriptor */
    rt_event_t finish_event;                     /**< data send finish event*/
    rt_bool_t data_error;                        /**< data send error*/
    struct rt_mutex lock;
};

extern rt_err_t mci_hw_init(const char *device_name);

#endif // __DRV_SD_H
