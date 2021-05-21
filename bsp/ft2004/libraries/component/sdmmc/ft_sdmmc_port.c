/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 16:52:05
 * @LastEditTime: 2021-04-15 13:51:10
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_printf.h"
#include "ft_generic_timer.h"
#include "ft_assert.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "ft_sdmmc.h"
#include "ft_sdmmc_common.h"

static void freertos_task_delay(u32 delay_tick)
{
    (void)vTaskDelay(delay_tick);
}

static void *freertos_heap_alloc(size_t size)
{
    void *ptr = pvPortMalloc(size);
    FT_SDMMC_DEBUG_D("allocate %x size %d", ptr, size);
    return ptr;
}

static void freertos_heap_free(void *ptr)
{
    Ft_assertNoneReturn(NULL != ptr);
    FT_SDMMC_DEBUG_D("do free %x", ptr);
    vPortFree(ptr);
}

static bool_t freertos_dma_capable(const void *ptr)
{
    /* no check implemented */
    return TRUE;
}

/* specify cpu or os depended implementation */
static const Sdmmc_OSImpl_t sdmmc_os_impl = {
    .task_delay = freertos_task_delay,  /* freeRTOS delay */
    .heap_alloc = freertos_heap_alloc,  /* freeRTOS heap memory allocator */
    .heap_free  = freertos_heap_free,   /* freeRTOS heap free */
    .check_dma_capable = freertos_dma_capable, /* freeRTOS mem allign check */
    .printf = Ft_printf,    /* freeRTOS printf */
    .tick_period = portTICK_PERIOD_MS,  /* freeRTOS tick period */
    .event_queue = NULL,    /* freeRTOS follow type QueueHandle_t */
    .io_intr_event = NULL,  /* freeRTOS follow type SemaphoreHandle_t */
};

const Sdmmc_OSImpl_t *get_sdmmc_os_impl()
{
    return &sdmmc_os_impl;
}
