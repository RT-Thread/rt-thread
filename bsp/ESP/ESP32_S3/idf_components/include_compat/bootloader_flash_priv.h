/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Compatibility shim for the vendored ESP-IDF fork on ESP32-S3.
 *
 * bootloader_flash.c implements bootloader_flash_wrap_set() under
 * #if SOC_CACHE_SUPPORT_WRAP (true on S3 via soc_caps.h), and
 * flash_qio_mode.c calls it under the same guard. The fork never declares
 * the prototype in any header, so -Werror=implicit-function-declaration
 * fails scons. C3 is unaffected: its soc_caps leave SOC_CACHE_SUPPORT_WRAP
 * unset, so both the call and the body are compiled out.
 *
 * This directory is prepended to the esp-idf group's CPPPATH so the
 * include_next below reaches the real bootloader_flash_priv.h in the
 * package. Delete this shim if the package grows a matching declaration.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-10     seteiro      declare bootloader_flash_wrap_set for S3
 */

#pragma once

#include_next <bootloader_flash_priv.h>

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_CACHE_SUPPORT_WRAP
esp_err_t bootloader_flash_wrap_set(spi_flash_wrap_mode_t mode);
#endif

#ifdef __cplusplus
}
#endif
