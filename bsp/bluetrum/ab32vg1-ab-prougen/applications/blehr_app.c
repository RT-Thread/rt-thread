/*
 * Copyright (c) 2021-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-15     greedyhao    the first version
 */

#include <rtthread.h>
#include <stdint.h>
#include <stddef.h>

#ifdef BSP_USING_NIMBLE

void nimble_port_run(void);
void nimble_port_init(void);
int ble_hci_rtthread_init(void);
void ble_svc_gap_init(void);
void ble_store_ram_init(void);
int blehr_main(void);
void bb_init(void);

void bthw_get_heap_info(void **p_heap, uint16_t **p_heap_size, uint32_t *p_block_size);
typedef void (*nsmem_cb_init_func)(void *heap_buf, void *heap_size_buf, uint32_t mem_block_max);
#define nsmem_cb_init   ((nsmem_cb_init_func)0x84140)

int btctrl_mem_init(void)
{
    void *heap_buf;
    uint16_t *heap_size_buf;
    uint32_t block_size;

    bthw_get_heap_info(&heap_buf, &heap_size_buf, &block_size);
    nsmem_cb_init(heap_buf, heap_size_buf, block_size);
    return 0;
}
INIT_BOARD_EXPORT(btctrl_mem_init);

static void blehr_thread_entry(void *param)
{
    bb_init();
    nimble_port_init();

    ble_hci_rtthread_init();
    ble_svc_gap_init();

    /* XXX Need to have template for store */
    ble_store_ram_init();

    blehr_main();

    nimble_port_run();
}

static int blehr_sample(void)
{
    rt_thread_t tid = rt_thread_create(
        "blehr",
        blehr_thread_entry,
        RT_NULL,
        1024,
        15,
        1);

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
}
MSH_CMD_EXPORT(blehr_sample, blehr_sample);

#endif
