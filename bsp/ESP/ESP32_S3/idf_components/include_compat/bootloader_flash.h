/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Compatibility shim for the vendored ESP-IDF fork on ESP32-S3.
 *
 * flash_ops_esp32s3.c includes bootloader_flash.h (not the priv header) and
 * calls bootloader_flash_wrap_set under SOC_CACHE_SUPPORT_WRAP. The fork
 * implements that symbol in bootloader_flash.c but never declares it in
 * bootloader_flash.h, so the call is an implicit declaration. The priv-header
 * shim covers flash_qio_mode.c; this one covers the spi_flash call site.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-10     seteiro      declare bootloader_flash_wrap_set for S3
 */
#pragma once

#include_next <bootloader_flash.h>
#include <bootloader_flash_priv.h>

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_CACHE_SUPPORT_WRAP
esp_err_t bootloader_flash_wrap_set(spi_flash_wrap_mode_t mode);
#endif

#ifdef __cplusplus
}
#endif
