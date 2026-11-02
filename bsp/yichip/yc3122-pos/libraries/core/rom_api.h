/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_rom_api.h
 * @brief    source file for setting rom_api
 *
 * Change Logs:
 * Date           Author      Version        Notes
 * 2020-11-05     wushengyan         V1.0.0         the first version
 */
#ifndef __ROM_API_H__
#define __ROM_API_H__

#define YC3122_AA   (0)
#define YC3122_AB   (1)
#define IC_DEVICE   YC3122_AB
#if (IC_DEVICE == YC3122_AA) 
/* TIMER */
#define FUNC_DELAY_US_ADDR                  (0x5030 + 1)
#define FUNC_DELAY_MS_ADDR                  (0x5068 + 1)

/* OTP */
#define FUNC_INIT_OTP_ADDR                  (0x5468 + 1)
#define FUNC_DEINIT_OTP_ADDR                (0x54c8 + 1)
#define FUNC_READ_OTP_ADDR                  (0x5510 + 1)
#define FUNC_WRITE_OTP_ADDR                 (0x5648 + 1)
#define FUNC_READ_CHIPID_ADDR               (0x56ac + 1)
#define FUNC_READ_CHIPLF_ADDR               (0x56ba + 1)

/* LPM */
#define FUNC_LIGHT_SLEEP_ADDR               (0x5338 + 1)
#define FUNC_DEEP_SLEEP_ADDR                (0x535c + 1)

/* QSPI */
#define FUNC_ENC_WRITE_FLASH_ADDR           (0x67c0 + 1)
#define FUNC_QSPI_FLASH_SECTORERASE_ADDR    (0x59a8 + 1)
#define FUNC_QSPI_FLASH_BLOCKERASE_ADDR     (0x59b4 + 1)
#define FUNC_QSPI_FLASH_BLOCK64ERASE_ADDR   (0x59c0 + 1)
#define FUNC_QSPI_FLASH_WRITE_ADDR          (0x58e8 + 1)
#define FUNC_QSPI_FLASH_READ_ADDR           (0x59ea + 1)
#define FUNC_FLASH_BLANK_CHECK              (0x670c + 1)
#define FUNC_PREFETCH                       (0x5398 + 1)
#define FUNC_READ_FLASH_ID                  (0x5a54 + 1)

#elif (IC_DEVICE == YC3122_AB)

/* TIMER */
#define FUNC_DELAY_US_ADDR                  (0x5020 + 1)
#define FUNC_DELAY_MS_ADDR                  (0x5058 + 1)

/* OTP */
#define FUNC_INIT_OTP_ADDR                  (0x5458 + 1)
#define FUNC_DEINIT_OTP_ADDR                (0x54b8 + 1)
#define FUNC_READ_OTP_ADDR                  (0x5500 + 1)
#define FUNC_WRITE_OTP_ADDR                 (0x5638 + 1)
#define FUNC_READ_CHIPID_ADDR               (0x569c + 1)
#define FUNC_READ_CHIPLF_ADDR               (0x56aa + 1)

/* LPM */
#define FUNC_LIGHT_SLEEP_ADDR               (0x5328 + 1)
#define FUNC_DEEP_SLEEP_ADDR                (0x534c + 1)

/* QSPI */
#define FUNC_ENC_WRITE_FLASH_ADDR           (0x6798 + 1)
#define FUNC_QSPI_FLASH_SECTORERASE_ADDR    (0x5998 + 1)
#define FUNC_QSPI_FLASH_BLOCKERASE_ADDR     (0x59a4 + 1)
#define FUNC_QSPI_FLASH_BLOCK64ERASE_ADDR   (0x59b0 + 1)
#define FUNC_QSPI_FLASH_WRITE_ADDR          (0x58d8 + 1)
#define FUNC_QSPI_FLASH_READ_ADDR           (0x59da + 1)
#define FUNC_FLASH_BLANK_CHECK              (0x66e4 + 1)
#define FUNC_PREFETCH                       (0x5388 + 1)
#define FUNC_READ_FLASH_ID                  (0x5a44 + 1)
#define FUNC_QSPI_FLASH_CMD                 (0x57ec + 1)

#endif


#endif
