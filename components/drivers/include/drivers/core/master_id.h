/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-20     GuEe-GUI     the first version
 */

#ifndef __RT_DM_MASTER_ID_H__
#define __RT_DM_MASTER_ID_H__

#define MASTER_ID_CUSTOM                                0

/* Block */
#define MASTER_ID_NVME                                  1
#define MASTER_ID_SCSI_SD                               2
#define MASTER_ID_SCSI_CDROM                            3
#define MASTER_ID_SDIO                                  4
#define MASTER_ID_VIRTUAL_BLOCK                         5

/* Char */
#define MASTER_ID_RPMSG_EPT                             11
#define MASTER_ID_RPMSG_CHAR                            12
#define MASTER_ID_SERIAL                                13

/* Clock Timer */
#define MASTER_ID_HWTIMER                               21
#define MASTER_ID_PTP                                   22
#define MASTER_ID_RTC                                   23

/* Graphic Display */
#define MASTER_ID_GRAPHIC_BACKLIGHT                     31
#define MASTER_ID_GRAPHIC_FRAMEBUFFER                   32
#define MASTER_ID_LED                                   33

/* Hardware Monitor */
#define MASTER_ID_DVFS                                  41
#define MASTER_ID_SENSOR                                42
#define MASTER_ID_THERMAL                               43
#define MASTER_ID_WATCHDOG                              44

/* I2C */
#define MASTER_ID_I2C_BUS                               51
#define MASTER_ID_I2C_DEV                               52

/* IO Contorl */
#define MASTER_ID_ADC                                   61
#define MASTER_ID_DAC                                   62
#define MASTER_ID_PIN                                   63
#define MASTER_ID_PWM                                   64

/* Memory */
#define MASTER_ID_MEM                                   71
#define MASTER_ID_MTD                                   72

/* MISC */
#define MASTER_ID_MISC                                  81

/* Multimedia */
#define MASTER_ID_AUDIO                                 91

/* Net */
#define MASTER_ID_CAN                                   101
#define MASTER_ID_ETH                                   102
#define MASTER_ID_PHY                                   103
#define MASTER_ID_WLAN                                  104

/* Input */
#define MASTER_ID_INPUT                                 111
#define MASTER_ID_TOUCH                                 112

/* Security */
#define MASTER_ID_HWCRYPTO                              121
#define MASTER_ID_RNG                                   122
#define MASTER_ID_TEE                                   123

/* SPI */
#define MASTER_ID_SPI_BUS                               131
#define MASTER_ID_SPI_DEV                               132

/* TTY */
#define MASTER_ID_TTY                                   141
#define MASTER_ID_TTY_SLAVES                            142
#define MASTER_ID_TTY_ALTERNATE                        	143
#define MASTER_ID_PTMX                                  144

/* USB */
#define MASTER_ID_USB_DEV                               151
#define MASTER_ID_USB_BUS                               152
#define MASTER_ID_USB_OTG                               153

#endif /* __RT_DM_MASTER_ID_H__ */
