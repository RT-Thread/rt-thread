/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-02     Ran Chen     multicore communication thread
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USE_MULTICORE

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
#include "rpmsg_lite.h"
#include "rpmsg_queue.h"
#include "rpmsg_ns.h"
#endif

#ifdef BSP_USE_MULTICORE_KICK_OFF
#include "mcmgr.h"
#include "board.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MULTICORE_THREAD_STACK_SIZE    2048
#define MULTICORE_THREAD_PRIORITY      10
#define MULTICORE_THREAD_TIMESLICE     5

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
#ifndef RPMSG_LITE_LINK_ID
#define RPMSG_LITE_LINK_ID            (RL_PLATFORM_IMXRT1180_M33_M7_LINK_ID)
#endif

#ifndef RPMSG_NS_ANNOUNCE_STRING
#define RPMSG_LITE_NS_ANNOUNCE_STRING "rpmsg-openamp-demo-channel"
#else
#define RPMSG_LITE_NS_ANNOUNCE_STRING RPMSG_NS_ANNOUNCE_STRING
#endif

#ifndef RPMSG_LOCAL_EPT_ADDR
#define LOCAL_EPT_ADDR                (40U)
#else
#define LOCAL_EPT_ADDR                RPMSG_LOCAL_EPT_ADDR
#endif

#ifndef RPMSG_SHARED_MEM_SIZE
#define SH_MEM_TOTAL_SIZE             (6144U)
#else
#define SH_MEM_TOTAL_SIZE             RPMSG_SHARED_MEM_SIZE
#endif

#define APP_RPMSG_READY_EVENT_DATA    (1U)

typedef struct the_message
{
    uint32_t DATA;
} THE_MESSAGE, *THE_MESSAGE_PTR;

static THE_MESSAGE msg = {0};

/* Shared memory for RPMsg */
#if defined(__ICCARM__) /* IAR Workbench */
#pragma location = "rpmsg_sh_mem_section"
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE];
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION) /* Keil MDK */
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section("rpmsg_sh_mem_section")));
#elif defined(__GNUC__)
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section(".noinit.$rpmsg_sh_mem")));
#else
#error "RPMsg: Please provide your definition of rpmsg_lite_base[]!"
#endif

static struct rpmsg_lite_instance *my_rpmsg = NULL;
static struct rpmsg_lite_endpoint *my_ept   = NULL;
static rpmsg_queue_handle my_queue          = NULL;
static rpmsg_ns_handle ns_handle            = NULL;
static bool error_occurred                  = false;
static volatile uint32_t remote_addr        = 0U;
#endif /* BSP_USE_MULTICORE_RPMSG_LITE */

#ifdef BSP_USE_MULTICORE_KICK_OFF
static volatile uint16_t RPMsgRemoteReadyEventData = 0U;
#endif

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

#ifdef BSP_USE_MULTICORE_KICK_OFF
static void RPMsgRemoteReadyEventHandler(mcmgr_core_t coreNum, uint16_t eventData, void *context)
{
    uint16_t *data = (uint16_t *)context;
    *data = eventData;
}

static rt_err_t multicore_kickoff_init(void)
{
    uint32_t core1_image_size, core1_image_source_addr, core1_image_dest_addr;
    uint32_t core1_boot_addr;
    mcmgr_status_t status;

    rt_kprintf("[Multicore] Initializing MCMGR (CM33 as master core)...\r\n");
    status = MCMGR_Init();
    if (status != kStatus_MCMGR_Success)
    {
        rt_kprintf("[Multicore] MCMGR initialization failed!\r\n");
        return -RT_ERROR;
    }
    rt_kprintf("[Multicore] MCMGR initialized successfully\r\n");

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
    /* Register the application event before starting the secondary core */
    (void)MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, RPMsgRemoteReadyEventHandler,
                              (void *)&RPMsgRemoteReadyEventData);
#endif

    /* Get CM7 core image information */
    if (kStatus_Success != BOARD_GetCore1ImageAddrSize(&core1_image_source_addr, 
                                                        &core1_image_dest_addr,
                                                        &core1_image_size, 
                                                        &core1_boot_addr))
    {
        rt_kprintf("[Multicore] Failed to get CM7 core image info!\r\n");
        return -RT_ERROR;
    }

    rt_kprintf("[Multicore] CM7 core image info:\r\n");
    rt_kprintf("  Source addr = 0x%08x\r\n", core1_image_source_addr);
    rt_kprintf("  Dest addr   = 0x%08x\r\n", core1_image_dest_addr);
    rt_kprintf("  Size        = %u (~%uK) bytes\r\n", 
               core1_image_size, (core1_image_size + 1023UL) / 1024UL);
    rt_kprintf("  Boot addr   = 0x%08x\r\n", core1_boot_addr);

    /* Prepare CM7 core */
    BOARD_PrepareCore1(core1_image_source_addr, core1_image_dest_addr, 
                       core1_image_size, core1_boot_addr);

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
    /* Boot CM7 core application */
    rt_kprintf("[Multicore] Starting CM7 core...\r\n");
    (void)MCMGR_StartCore(kMCMGR_Core1, (void *)core1_boot_addr, 
                          (uint32_t)rpmsg_lite_base, kMCMGR_Start_Synchronous);

    /* Wait until the CM7 core signals it's ready */
    rt_kprintf("[Multicore] Waiting for CM7 core ready signal...\r\n");
    while (APP_RPMSG_READY_EVENT_DATA != RPMsgRemoteReadyEventData)
    {
        rt_thread_mdelay(10);
    }
    rt_kprintf("[Multicore] CM7 core is ready!\r\n");
#else
    /* Boot CM7 core without RPMsg */
    rt_kprintf("[Multicore] Starting CM7 core...\r\n");
    (void)MCMGR_StartCore(kMCMGR_Core1, (void *)core1_boot_addr, 
                          0, kMCMGR_Start_Synchronous);
    rt_kprintf("[Multicore] CM7 core started!\r\n");
#endif

    return RT_EOK;
}
#endif /* BSP_USE_MULTICORE_KICK_OFF */

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
static void app_nameservice_isr_cb(uint32_t new_ept, const char *new_ept_name, 
                                   uint32_t flags, void *user_data)
{
    uint32_t *data = (uint32_t *)user_data;
    *data = new_ept;
}

static rt_err_t rpmsg_lite_init(void)
{
    rt_kprintf("[RPMsg] Initializing RPMsg-Lite (CM33 as master)...\r\n");

    /* Initialize RPMsg-Lite as master */
    my_rpmsg = rpmsg_lite_master_init(rpmsg_lite_base, SH_MEM_TOTAL_SIZE, 
                                      RPMSG_LITE_LINK_ID, RL_NO_FLAGS);
    if (my_rpmsg == NULL)
    {
        rt_kprintf("[RPMsg] Failed to initialize rpmsg!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Create queue */
    my_queue = rpmsg_queue_create(my_rpmsg);
    if (my_queue == NULL)
    {
        rt_kprintf("[RPMsg] Failed to create queue!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Create endpoint */
    my_ept = rpmsg_lite_create_ept(my_rpmsg, LOCAL_EPT_ADDR, rpmsg_queue_rx_cb, my_queue);
    if (my_ept == NULL)
    {
        rt_kprintf("[RPMsg] Failed to create endpoint!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Bind nameservice */
    ns_handle = rpmsg_ns_bind(my_rpmsg, app_nameservice_isr_cb, (void *)&remote_addr);
    if (ns_handle == NULL)
    {
        rt_kprintf("[RPMsg] Failed to bind name service!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Wait until the CM7 core issues the nameservice announce */
    rt_kprintf("[RPMsg] Waiting for CM7 nameservice announce...\r\n");
    while (0U == remote_addr)
    {
    }
    rt_kprintf("[RPMsg] Got remote endpoint address: 0x%x\r\n", remote_addr);

    return RT_EOK;
}

static void rpmsg_lite_communication(void)
{
    uint32_t len = 0U;

    rt_kprintf("[RPMsg] Starting ping-pong communication...\r\n");

    /* Send the first message to CM7 */
    msg.DATA = 0U;
    rt_kprintf("[RPMsg] Sending initial ping: %u\r\n", msg.DATA);
    (void)rpmsg_lite_send(my_rpmsg, my_ept, remote_addr, (char *)&msg, 
                          sizeof(THE_MESSAGE), RL_DONT_BLOCK);

    while (msg.DATA <= 100U)
    {
        uint32_t recv_addr = 0;
        
        rt_kprintf("[RPMsg] Waiting for pong from CM7...\r\n");
        
        (void)rpmsg_queue_recv(my_rpmsg, my_queue, &recv_addr, (char *)&msg, 
                               sizeof(THE_MESSAGE), &len, RL_BLOCK);
        
        rt_kprintf("[RPMsg] Received pong: %u (size=%u)\r\n", msg.DATA, len);
        
        msg.DATA++;
        
        if (msg.DATA <= 100U)
        {
            rt_kprintf("[RPMsg] Sending ping: %u\r\n", msg.DATA);
            (void)rpmsg_lite_send(my_rpmsg, my_ept, remote_addr, (char *)&msg, 
                                  sizeof(THE_MESSAGE), RL_BLOCK);
        }
    }

    rt_kprintf("[RPMsg] Ping-pong communication completed!\r\n");
}

static void rpmsg_lite_cleanup(void)
{
    rt_kprintf("[RPMsg] Cleaning up resources...\r\n");

    if (my_ept != NULL)
    {
        (void)rpmsg_lite_destroy_ept(my_rpmsg, my_ept);
        my_ept = NULL;
    }

    if (my_queue != NULL)
    {
        (void)rpmsg_queue_destroy(my_rpmsg, my_queue);
        my_queue = NULL;
    }

    if (ns_handle != NULL)
    {
        (void)rpmsg_ns_unbind(my_rpmsg, ns_handle);
        ns_handle = NULL;
    }

    if (my_rpmsg != NULL)
    {
        (void)rpmsg_lite_deinit(my_rpmsg);
        my_rpmsg = NULL;
    }

    msg.DATA = 0U;
}
#endif /* BSP_USE_MULTICORE_RPMSG_LITE */

/*******************************************************************************
 * Thread Entry
 ******************************************************************************/
static void multicore_thread_entry(void *parameter)
{
    rt_kprintf("\r\n=== Multicore Communication Thread Started (CM33 Master) ===\r\n");

#ifdef BSP_USE_MULTICORE_KICK_OFF
    /* Initialize and kickoff CM7 core */
    if (multicore_kickoff_init() != RT_EOK)
    {
        rt_kprintf("[Multicore] Kickoff initialization failed!\r\n");
        return;
    }
#endif

#ifdef BSP_USE_MULTICORE_RPMSG_LITE
    /* Initialize RPMsg-Lite */
    if (rpmsg_lite_init() != RT_EOK)
    {
        rt_kprintf("[Multicore] RPMsg-Lite initialization failed!\r\n");
        goto cleanup;
    }

    /* Start communication */
    rpmsg_lite_communication();

cleanup:
    /* Cleanup resources */
    rpmsg_lite_cleanup();

    if (error_occurred)
    {
        rt_kprintf("[Multicore] Error occurred during communication!\r\n");
    }
    else
    {
        rt_kprintf("[Multicore] Communication completed successfully!\r\n");
    }
#endif

    rt_kprintf("=== Multicore Communication Thread Ended ===\r\n");
}

/*******************************************************************************
 * Public Functions
 ******************************************************************************/
int multicore_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("multicore",
                           multicore_thread_entry,
                           RT_NULL,
                           MULTICORE_THREAD_STACK_SIZE,
                           MULTICORE_THREAD_PRIORITY,
                           MULTICORE_THREAD_TIMESLICE);

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
        rt_kprintf("[Multicore] Communication thread created successfully\r\n");
        return RT_EOK;
    }
    else
    {
        rt_kprintf("[Multicore] Failed to create communication thread!\r\n");
        return -RT_ERROR;
    }
}
INIT_APP_EXPORT(multicore_init);

#endif /* BSP_USE_MULTICORE */