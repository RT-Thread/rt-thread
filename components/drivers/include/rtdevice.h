/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-08     bernard      first version.
 * 2014-07-12     bernard      Add workqueue implementation.
 */

#ifndef __RT_DEVICE_H__
#define __RT_DEVICE_H__

#include <rtthread.h>

#include "ipc/ringbuffer.h"
#include "ipc/completion.h"
#include "ipc/dataqueue.h"
#include "ipc/workqueue.h"
#include "ipc/waitqueue.h"
#include "ipc/pipe.h"
#include "ipc/poll.h"
#include "ipc/ringblk_buf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RT_DEVICE(device)            ((rt_device_t)device)

#ifdef RT_USING_RTC
#include "drivers/rtc.h"
#ifdef RT_USING_ALARM
#include "drivers/alarm.h"
#endif
#endif /* RT_USING_RTC */

#ifdef RT_USING_SPI
#include "drivers/spi.h"
#endif /* RT_USING_SPI */

#ifdef RT_USING_MTD_NOR
#include "drivers/mtd_nor.h"
#endif /* RT_USING_MTD_NOR */

#ifdef RT_USING_MTD_NAND
#include "drivers/mtd_nand.h"
#endif /* RT_USING_MTD_NAND */

#ifdef RT_USING_USB_DEVICE
#include "drivers/usb_device.h"
#endif /* RT_USING_USB_DEVICE */

#ifdef RT_USING_USB_HOST
#include "drivers/usb_host.h"
#endif /* RT_USING_USB_HOST */

#ifdef RT_USING_SERIAL
#include "drivers/serial.h"
#endif /* RT_USING_SERIAL */

#ifdef RT_USING_I2C
#include "drivers/i2c.h"
#include "drivers/i2c_dev.h"

#ifdef RT_USING_I2C_BITOPS
#include "drivers/i2c-bit-ops.h"
#endif /* RT_USING_I2C_BITOPS */
#endif /* RT_USING_I2C */

#ifdef RT_USING_SDIO
#include "drivers/mmcsd_core.h"
#include "drivers/sd.h"
#include "drivers/sdio.h"
#endif

#ifdef RT_USING_WDT
#include "drivers/watchdog.h"
#endif

#ifdef RT_USING_PIN
#include "drivers/pin.h"
#endif

#ifdef RT_USING_CAN
#include "drivers/can.h"
#endif

#ifdef RT_USING_HWTIMER
#include "drivers/hwtimer.h"
#endif

#ifdef RT_USING_AUDIO
#include "drivers/audio.h"
#endif

#ifdef RT_USING_CPUTIME
#include "drivers/cputime.h"
#endif

#ifdef RT_USING_ADC
#include "drivers/adc.h"
#endif

#ifdef RT_USING_DAC
#include "drivers/dac.h"
#endif

#ifdef RT_USING_PWM
#include "drivers/rt_drv_pwm.h"
#endif

#ifdef RT_USING_PM
#include "drivers/pm.h"
#endif

#ifdef RT_USING_WIFI
#include "drivers/wlan.h"
#endif

#ifdef MTD_USING_NOR
#include "drivers/mtdnor.h"
#endif
#ifdef MTD_USING_NAND
#include "drivers/mtdnand.h"
#endif

#ifdef RT_USING_HWCRYPTO
#include "drivers/crypto.h"
#endif

#ifdef RT_USING_PULSE_ENCODER
#include "drivers/pulse_encoder.h"
#endif

#ifdef RT_USING_INPUT_CAPTURE
#include "drivers/rt_inputcapture.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __RT_DEVICE_H__ */
