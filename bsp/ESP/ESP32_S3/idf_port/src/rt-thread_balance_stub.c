/*
 * Link-compat shims for the ESP32-S3 BSP.
 *
 * The ESP32-C3 original also stubs out ceil()/floor() because the RISC-V
 * multilib setup pulls no libm; the Xtensa toolchain links real libm through
 * g++, so stubbing them here would silently mis-round IDF's math - they are
 * deliberately NOT stubbed in this BSP.
 *
 * _end/_edata: referenced by IDF heap/newlib sbrk glue but not emitted by the
 * esp32s3 sections.ld fragment (same situation as the C3 BSP handled here).
 *
 * opendir/readdir/closedir/select: newlib syscall entry points that would
 * otherwise resolve against the VFS component, which this BSP does not
 * compile (same rationale as ESP32-C3; kept because the xtensa newlib here is
 * the same fork-provided library).
 */
#include "rtconfig.h"

void _end(void)
{
    return;
}

void _edata(void)
{
    return;
}

#ifndef BSP_USING_BLE /* the BLE component brings VFS, which provides these */
void opendir(void)
{
    return;
}

void readdir(void)
{
    return;
}

void closedir(void)
{
    return;
}

void select(void)
{
    return;
}
#endif /* BSP_USING_BLE */

/*
 * Link-compat stubs for ESP-IDF files that v1 of this BSP keeps in the build
 * for boot-path reasons but whose optional features are switched off:
 *
 * - bootloader_sha256_* : image-signature checking. The real implementation
 *   lives on mbedtls, which is not compiled (no Wi-Fi/TLS). The app never
 *   verifies its own image at runtime; the second-stage bootloader we ship
 *   carries its own copy. Prototypes per
 *   components/bootloader_support/private_include/bootloader_sha.h.
 * - esp_flash_encryption_enabled : defined by flash_encrypt.c (excluded,
 *   flash encryption off). Referenced unconditionally from bootloader_flash.c
 *   / esp_ota_ops / bootloader_utility.
 * - task_wdt_timeout_abort_xtensa : esp_system/task_wdt.c compiles to nothing
 *   with CONFIG_ESP_TASK_WDT_INIT=0 (its xtensa abort path needs the real
 *   FreeRTOS snapshot API, absent in the RT-Thread wrapper), but
 *   esp_system/crosscore_int.c still references the symbol.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void *bootloader_sha256_start(void);
void  bootloader_sha256_data(void *handle, const void *data, size_t len);
void  bootloader_sha256_finish(void *handle, uint8_t *digest);

void *bootloader_sha256_start(void)
{
    return NULL;
}

void bootloader_sha256_data(void *handle, const void *data, size_t len)
{
    (void)handle;
    (void)data;
    (void)len;
}

void bootloader_sha256_finish(void *handle, uint8_t *digest)
{
    (void)handle;
    if (digest)
    {
        for (int i = 0; i < 32; i++)
        {
            digest[i] = 0;
        }
    }
}

bool esp_flash_encryption_enabled(void)
{
    return false;
}

void task_wdt_timeout_abort_xtensa(bool current_core)
{
    (void)current_core;
}

/*
 * Debug aid while bringing the port up: esp_system_abort() is the common
 * funnel of abort()/ESP_ERROR_CHECK/assert and its panic path is silent
 * before the console exists. Linked via -Wl,--wrap=esp_system_abort (see
 * rtconfig.py): print the reason with the ROM printf, then halt.
 */
void __attribute__((noreturn)) __wrap_esp_system_abort(const char *details)
{
    extern int esp_rom_printf(const char *fmt, ...);
    esp_rom_printf("\nrt-s3: esp_system_abort: %s\n", details ? details : "(null)");
    for (;;)
    {
    }
}

/*
 * ESP32-S3 bring-up note (flash):
 * The fork's esp_flash_api.c esp_flash_init_main() fast path reads the chip id
 * out of the ROM legacy struct (rom_spiflash_legacy_data at 0x3fceffe4, struct
 * at 0x3fcef6a4). On this board the other fields (chip_size 8MB, sector 4KB,
 * status mask) survive, but device_id arrives 0, and the fork's live-RDID
 * fallback path (written around a C6 cache-suspend bug) ends in
 * ESP_ERR_NOT_FOUND at startup.c's assert. Until that fork bug is fixed
 * properly, this BSP bypasses default-chip init: the bootloader already mapped
 * the flash (partition table + app run through the cache), read-only access
 * needs no driver re-init, and v1 offers no flash write/OTA API.
 * -Wl,--wrap=esp_flash_init_default_chip routes startup.c's call here.
 */
typedef int esp_err_t;
esp_err_t __wrap_esp_flash_init_default_chip(void)
{
    return 0 /* ESP_OK */;
}
