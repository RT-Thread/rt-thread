/*
 * Copyright 2021-2025 NXP
 * All rights reserved.
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
#define MULTICORE_THREAD_STACK_SIZE 2048
#define MULTICORE_THREAD_PRIORITY   10
#define MULTICORE_THREAD_TIMESLICE  5
#ifdef BSP_USE_MULTICORE_RPMSG_LITE
#ifndef RPMSG_LITE_LINK_ID
#define RPMSG_LITE_LINK_ID (RL_PLATFORM_IMXRT1180_M33_M7_LINK_ID)
#endif

#ifndef RPMSG_NS_ANNOUNCE_STRING
#define RPMSG_LITE_NS_ANNOUNCE_STRING "rpmsg-openamp-demo-channel"
#else
#define RPMSG_LITE_NS_ANNOUNCE_STRING RPMSG_NS_ANNOUNCE_STRING
#endif

#ifndef RPMSG_LOCAL_EPT_ADDR
#define LOCAL_EPT_ADDR (30U)
#else
#define LOCAL_EPT_ADDR RPMSG_LOCAL_EPT_ADDR
#endif

#define APP_RPMSG_READY_EVENT_DATA (1U)

typedef struct the_message
{
    uint32_t DATA;
} THE_MESSAGE, *THE_MESSAGE_PTR;

static volatile THE_MESSAGE msg = { 0 };
static struct rpmsg_lite_instance * volatile my_rpmsg = NULL;
static struct rpmsg_lite_endpoint * volatile my_ept = NULL;
static volatile rpmsg_queue_handle my_queue = NULL;
static bool error_occurred = false;
#endif /* BSP_USE_MULTICORE_RPMSG_LITE */

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
#ifdef BSP_USE_MULTICORE_KICK_OFF
static rt_err_t multicore_kickoff_init(void)
{
    mcmgr_status_t status;

    rt_kprintf("[Multicore] Initializing MCMGR ...\r\n");
    status = MCMGR_Init();
    if (status != kStatus_MCMGR_Success)
    {
        rt_kprintf("[Multicore] MCMGR initialization failed!\r\n");
        return -RT_ERROR;
    }
    rt_kprintf("[Multicore] MCMGR initialized successfully\r\n");

    return RT_EOK;
}
#endif /* BSP_USE_MULTICORE_KICK_OFF */
#ifdef BSP_USE_MULTICORE_RPMSG_LITE
static void app_nameservice_isr_cb(uint32_t new_ept, const char *new_ept_name,
                                   uint32_t flags, void *user_data)
{
    /* Nameservice callback - can be extended as needed */
}

static rt_err_t rpmsg_lite_init(void)
{
    uint32_t startupData;
    mcmgr_status_t status;

    rt_kprintf("[RPMsg] Initializing RPMsg-Lite (CM7 as remote)...\r\n");

    /* Get the startup data from CM33 master core */
    do
    {
        status = MCMGR_GetStartupData(kMCMGR_Core0, &startupData);
    } while (status != kStatus_MCMGR_Success);

    /* Initialize RPMsg-Lite as remote (CM7 side) */
    my_rpmsg = rpmsg_lite_remote_init((void *)(char *)(platform_patova(startupData)),
                                      RPMSG_LITE_LINK_ID, RL_NO_FLAGS);
    if (my_rpmsg == NULL)
    {
        rt_kprintf("[RPMsg] Failed to initialize rpmsg!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Signal the CM33 master core we are ready */
    (void)MCMGR_TriggerEvent(kMCMGR_Core0, kMCMGR_RemoteApplicationEvent,
                             APP_RPMSG_READY_EVENT_DATA);

    /* Wait for link up with CM33 master */
    rpmsg_lite_wait_for_link_up(my_rpmsg, RL_BLOCK);
    rt_kprintf("[RPMsg] Link is up with CM33 master!\r\n");

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
    rpmsg_ns_handle ns_handle = rpmsg_ns_bind(my_rpmsg, app_nameservice_isr_cb, NULL);
    if (ns_handle == NULL)
    {
        rt_kprintf("[RPMsg] Failed to bind name service!\r\n");
        error_occurred = true;
        return -RT_ERROR;
    }

    /* Announce service */
//    SDK_DelayAtLeastUs(1000000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    (void)rpmsg_ns_announce(my_rpmsg, my_ept, RPMSG_LITE_NS_ANNOUNCE_STRING,
                            (uint32_t)RL_NS_CREATE);
    rt_kprintf("[RPMsg] Nameservice announced\r\n");

    return RT_EOK;
}

static void rpmsg_lite_communication(void)
{
    volatile uint32_t remote_addr = 0U;

    rt_kprintf("[RPMsg] Starting ping-pong communication...\r\n");

    while (msg.DATA <= 100U)
    {
        rt_kprintf("[RPMsg] Waiting for ping...\r\n");

        (void)rpmsg_queue_recv(my_rpmsg, my_queue, (uint32_t *)&remote_addr,
                               (char *)&msg, sizeof(THE_MESSAGE), NULL, RL_BLOCK);

        msg.DATA++;

        rt_kprintf("[RPMsg] Received: %u, Sending pong: %u\r\n", msg.DATA - 1, msg.DATA);

        (void)rpmsg_lite_send(my_rpmsg, my_ept, remote_addr, (char *)&msg,
                              sizeof(THE_MESSAGE), RL_BLOCK);
    }

    rt_kprintf("[RPMsg] Ping-pong communication completed!\r\n");
}

static void rpmsg_lite_cleanup(void)
{
    rt_kprintf("[RPMsg] Cleaning up resources...\r\n");

    if (my_ept)
    {
        (void)rpmsg_lite_destroy_ept(my_rpmsg, my_ept);
        my_ept = NULL;
    }

    if (my_queue)
    {
        (void)rpmsg_queue_destroy(my_rpmsg, my_queue);
        my_queue = NULL;
    }

    if (my_rpmsg)
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
#ifndef BSP_USE_MULTICORE_RPMSG_LITE
    uint32_t startupData;
    mcmgr_status_t status;
#endif

    rt_kprintf("\r\n=== Multicore Communication Thread Started ===\r\n");

#ifdef BSP_USE_MULTICORE_KICK_OFF
    /* Initialize and kickoff CM33 core */
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
#else
         /* Get the startup data */
    do
    {
        status = MCMGR_GetStartupData(kMCMGR_Core0, &startupData);
    } while (status != kStatus_MCMGR_Success);
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
//        rt_kprintf("[Multicore] Communication thread created successfully\r\n");
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
