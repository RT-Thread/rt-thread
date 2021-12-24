/*
File Name    : rom_api.h
Author       : Yichip
Version      : V1.0
Date         : 2020/02/11
Description  : rom fun information.
*/

#ifndef __ROM_API_H__
#define __ROM_API_H__

/* TIMER */
#define FUNC_DELAY_US_ADDR               (0x4238 + 1)
#define FUNC_DELAY_MS_ADDR               (0x425c + 1)

/* OTP */
#define FUNC_INIT_OTP_ADDR               (0x442c + 1)
#define FUNC_DEINIT_OTP_ADDR             (0x4480 + 1)
#define FUNC_READ_OTP_ADDR               (0x449c + 1)
#define FUNC_WRITE_OTP_ADDR              (0x4594 + 1)
#define FUNC_READ_CHIPID_ADDR            (0x45d8 + 1)
#define FUNC_READ_CHIPLF_ADDR            (0x45e6 + 1)

/* LPM */
#define FUNC_LPM_READ_ADDR               (0x4c80 + 1)
#define FUNC_LPM_WRITE_ADDR              (0x4c9c + 1)
#define FUNC_LPM_BT_WRITE_ADDR           (0x4cb0 + 1)
#define FUNC_LPM_BT_READ_ADDR            (0x4d24 + 1)
#define FUNC_LPM_SLEEP_ADDR              (0x4d68 + 1)
#define FUNC_SETLPMVAL_ADDR              (0x4280 + 1)

/* QSPI */
#define FUNC_ENC_WRITE_FLASH_ADDR        (0x51f0 + 1)
#define FUNC_QSPI_FLASH_SECTORERASE_ADDR (0x48b4 + 1)
#define FUNC_QSPI_FLASH_BLOCKERASE_ADDR  (0x48c0 + 1)
#define FUNC_QSPI_FLASH_WRITE_ADDR       (0x47f4 + 1)
#define FUNC_QSPI_FLASH_READ_ADDR        (0x48f6 + 1)
#define FUNC_FLASH_BLANK_CHECK           (0x513c + 1)
#define FUNC_PREFETCH                    (0x4404 + 1)
#define FUNC_READ_FLASH_ID               (0x4960 + 1)

#endif
