/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * ESP32-S3 (Xtensa) app-startup glue for the RT-Thread ESP BSP family.
 *
 * Derived from ESP-IDF's FreeRTOS-Kernel portable/xtensa/port.c (Apache-2.0)
 * the same way the ESP32-C3 BSP derives its RISC-V counterpart: only the
 * functions IDF code actually calls through the FreeRTOS-Wrapper shim are
 * kept; the RISC-V include set is dropped and nothing Xtensa-specific beyond
 * the core id is needed (coprocessor and vector handling live in
 * libcpu/xtensa/esp32s3, not here).
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    first version (ESP32-S3)
 */

#include "sdkconfig.h"
#include <stdint.h>
#include "esp_attr.h"
#include "esp_system.h"
#include "esp_log.h"
#include <rthw.h>
#include "FreeRTOS.h"       /* This pulls in portmacro.h */
#include "task.h"
#include "portmacro.h"

static const char *TAG = "cpu_start";

/* ---------------------------------------------- Port Implementations --- */

BaseType_t xPortInIsrContext(void)
{
    return (BaseType_t)rt_interrupt_get_nest();
}

BaseType_t IRAM_ATTR xPortInterruptedFromISRContext(void)
{
    /* single core: reading the nesting counter is atomic wrt this task */
    return (BaseType_t)rt_interrupt_get_nest();
}

uint32_t xPortGetTickRateHz(void)
{
    return (uint32_t)configTICK_RATE_HZ;
}

/* ---------------------------------------------- Misc Implementations --- */

extern void esp_startup_start_app_common(void);

void esp_startup_start_app(void)
{
    esp_startup_start_app_common();

    ESP_LOGI(TAG, "Starting scheduler.");
    vTaskStartScheduler();
}
