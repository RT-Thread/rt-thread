/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "esp_private/esp_int_wdt.h"
#include "esp_system.h"
#include "esp_heap_caps_init.h"
#include "esp_task_wdt.h"
#include "esp_task.h"
#include "esp_private/crosscore_int.h"
#include "esp_log.h"
#include "esp_memory_utils.h"
#include "esp_freertos_hooks.h"
#include "sdkconfig.h"
#include "esp_freertos_hooks.h"

#if CONFIG_SPIRAM
#include "esp_psram.h"
#include "esp_private/esp_psram_extram.h"
#endif

#if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
static const char* TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

// Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting
volatile unsigned port_xSchedulerRunning[portNUM_PROCESSORS] = {0};

// For now, running FreeRTOS on one core and a bare metal on the other (or other OSes)
// is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
// should mirror each other's values.
//
// And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE.
#if CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

#if !defined CONFIG_IDF_RTOS_RTTHREAD
static void main_task(void* args);
#endif

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
void esp_gdbstub_init(void);
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

extern void app_main(void);

void esp_startup_start_app_common(void)
{
#if CONFIG_ESP_INT_WDT
    esp_int_wdt_init();
    //Initialize the interrupt watch dog for CPU0.
    esp_int_wdt_cpu_init();
#endif

    esp_crosscore_int_init();

#if CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME && !CONFIG_IDF_TARGET_ESP32C2
    esp_gdbstub_init();
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

#if !defined CONFIG_IDF_RTOS_RTTHREAD
    portBASE_TYPE res = xTaskCreatePinnedToCore(&main_task, "main",
                                                ESP_TASK_MAIN_STACK, NULL,
                                                ESP_TASK_MAIN_PRIO, NULL, ESP_TASK_MAIN_CORE);
    assert(res == pdTRUE);
    (void)res;
#endif
}

#if !CONFIG_FREERTOS_UNICORE
static volatile bool s_other_cpu_startup_done = false;
static bool other_cpu_startup_idle_hook_cb(void)
{
    s_other_cpu_startup_done = true;
    return true;
}
#endif

#if !defined CONFIG_IDF_RTOS_RTTHREAD
static void main_task(void* args)
{
#if !CONFIG_FREERTOS_UNICORE
    // Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack
    esp_register_freertos_idle_hook_for_cpu(other_cpu_startup_idle_hook_cb, !xPortGetCoreID());
    while (!s_other_cpu_startup_done) {
        ;
    }
    esp_deregister_freertos_idle_hook_for_cpu(other_cpu_startup_idle_hook_cb, !xPortGetCoreID());
#endif

    // [refactor-todo] check if there is a way to move the following block to esp_system startup
    heap_caps_enable_nonos_stack_heaps();

    // Now we have startup stack RAM available for heap, enable any DMA pool memory
#if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    if (esp_psram_is_initialized()) {
        esp_err_t r = esp_psram_extram_reserve_dma_pool(CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL);
        if (r != ESP_OK) {
            ESP_EARLY_LOGE(TAG, "Could not reserve internal/DMA pool (error 0x%x)", r);
            abort();
        }
    }
#endif

    //Initialize TWDT if configured to do so
#if CONFIG_ESP_TASK_WDT
    esp_task_wdt_config_t twdt_config = {
        .timeout_ms = CONFIG_ESP_TASK_WDT_TIMEOUT_S * 1000,
        .idle_core_mask = 0,
#if CONFIG_ESP_TASK_WDT_PANIC
        .trigger_panic = true,
#endif
    };
#if CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
    twdt_config.idle_core_mask |= (1 << 0);
#endif
#if CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
    twdt_config.idle_core_mask |= (1 << 1);
#endif
    ESP_ERROR_CHECK(esp_task_wdt_init(&twdt_config));
#endif // CONFIG_ESP_TASK_WDT

    app_main();
    vTaskDelete(NULL);
}
#endif
