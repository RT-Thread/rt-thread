/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-10      Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(BSP_USING_WHC)

#include "drv_whc.h"
#include <stdio.h>

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "whc.demo"
#define DBG_COLOR
#include <rtdbg.h>

#define USE_WORMHOLE_CHNAME    "whc0-0"

typedef enum
{
    evCMD_MEM_ALLOCATE,
    evCMD_MEM_FREE,
    evCMD_MEM_COPY,
    evCMD_DEVMEM_WRITE,
    evCMD_DEVMEM_READ,
    evCMD_MEM_SET
} nu_whc_cmd;

typedef enum
{
    evCMD_REQ,
    evCMD_RESP,
} nu_whc_cmd_type;

#define CMD_TYPE_Pos           16
#define CMD_TYPE_Msk           (3<<CMD_TYPE_Pos)
#define PACK_MSG_CMD(t, x)     (((t<<CMD_TYPE_Pos)&CMD_TYPE_Msk)|x)
#define CMD_IS_REQ(m)          (((m.u32Cmd&CMD_TYPE_Msk)>>CMD_TYPE_Pos)==evCMD_REQ)
#define CMD_IS_RESP(m)         (((m.u32Cmd&CMD_TYPE_Msk)>>CMD_TYPE_Pos)==evCMD_RESP)

typedef struct
{
    union
    {
        nu_whc_msg sMsgBuf;
        struct
        {
            uint32_t   u32Cmd;
            uint32_t   u32Addr0; //Dst, free, allocate, set
            uint32_t   u32Addr1; //Src, value
            uint32_t   u32Size;
        } msg;
    };
} whc_mem;
typedef whc_mem *whc_mem_t;

static struct rt_semaphore tx_sem;
static struct rt_semaphore rx_sem;
static rt_device_t device = RT_NULL;

static rt_err_t whc_tx_complete(rt_device_t dev, void *buffer)
{
    return rt_sem_release(&tx_sem);
}

static rt_err_t whc_rx_indicate(rt_device_t dev, rt_size_t size)
{
    return rt_sem_release(&rx_sem);
}

static rt_err_t proc_msg(whc_mem_t req, whc_mem_t resp)
{
    switch ((nu_whc_cmd)req->msg.u32Cmd)
    {
    case evCMD_MEM_ALLOCATE:
        resp->msg.u32Addr0 = (uint32_t)rt_malloc(req->msg.u32Size);
        resp->msg.u32Size  = req->msg.u32Size;
        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_MEM_ALLOCATE);
        break;

    case evCMD_MEM_FREE:
        rt_free((void *)req->msg.u32Addr0);
        resp->msg.u32Addr0 = (uint32_t)req->msg.u32Addr0;
        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_MEM_FREE);
        resp->msg.u32Size  = 0;
        break;

    case evCMD_MEM_COPY:
        rt_memcpy((void *)req->msg.u32Addr0, (void *)req->msg.u32Addr1, req->msg.u32Size);
        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_MEM_COPY);
        resp->msg.u32Addr0 = (uint32_t)req->msg.u32Addr0;
        resp->msg.u32Addr1 = (uint32_t)req->msg.u32Addr1;
        resp->msg.u32Size  = req->msg.u32Size;
        break;

    case evCMD_MEM_SET:
        rt_memset((void *)req->msg.u32Addr0, (req->msg.u32Addr1 & 0xff), req->msg.u32Size);
        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_MEM_SET);
        resp->msg.u32Addr0 = (uint32_t)req->msg.u32Addr0;
        resp->msg.u32Addr1 = (uint32_t)(req->msg.u32Addr1 & 0xff);
        resp->msg.u32Size  = req->msg.u32Size;
        break;

    case evCMD_DEVMEM_WRITE:
        *((vu32 *)req->msg.u32Addr0) = req->msg.u32Addr1;

        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_DEVMEM_WRITE);
        resp->msg.u32Addr0 = 0;
        resp->msg.u32Addr1 = 0;
        resp->msg.u32Size  = sizeof(uint32_t);
        break;

    case evCMD_DEVMEM_READ:
        resp->msg.u32Cmd   = PACK_MSG_CMD(evCMD_RESP, evCMD_DEVMEM_READ);
        resp->msg.u32Addr0 = *((vu32 *)req->msg.u32Addr0);
        resp->msg.u32Addr1 = 0;
        resp->msg.u32Size  = sizeof(uint32_t);
        break;

    default:
        return -RT_ERROR;
    }

    return -RT_ERROR;
}

static rt_err_t send_msg(whc_mem_t req)
{
    if (device)
    {
        if (sizeof(nu_whc_msg) != rt_device_write(device, 0, req, sizeof(nu_whc_msg)))
        {
            LOG_E("Failed to send msg.");
            return -RT_ERROR;
        }

        if (-RT_ETIMEOUT == rt_sem_take(&tx_sem, 100))
            LOG_E("Timeout cant get ACK.");
    }

    return RT_EOK;
}


static void whc_daemon(void *parameter)
{
    rt_err_t ret;

    device  = rt_device_find(USE_WORMHOLE_CHNAME);
    RT_ASSERT(device);

    /* Init semaphores */
    ret = rt_sem_init(&tx_sem, "whc_tx", 0, RT_IPC_FLAG_PRIO);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_sem_init(&rx_sem, "whc_rx", 0, RT_IPC_FLAG_PRIO);
    RT_ASSERT(ret == RT_EOK);

    /* Set tx complete function */
    ret = rt_device_set_tx_complete(device, whc_tx_complete);
    RT_ASSERT(ret == RT_EOK);

    /* Set rx indicate function */
    ret = rt_device_set_rx_indicate(device, whc_rx_indicate);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_open(device, 0);
    if (!device)
    {
        LOG_E("Failed to open %s", USE_WORMHOLE_CHNAME);
        return;
    }

    while (1)
    {
        if (rt_sem_take(&rx_sem, RT_WAITING_FOREVER) == RT_EOK)
        {
            nu_whc_msg sNuWhcMsg;
            whc_mem_t psWhcMem = (whc_mem_t)&sNuWhcMsg;

            if (sizeof(nu_whc_msg) != rt_device_read(device, 0, psWhcMem, sizeof(nu_whc_msg)))
                continue;

            if (CMD_IS_REQ(psWhcMem->msg))
            {
                nu_whc_msg sNuWhcMsg_Resp;

                proc_msg((whc_mem_t)&sNuWhcMsg, (whc_mem_t)&sNuWhcMsg_Resp);
                send_msg((whc_mem_t)&sNuWhcMsg_Resp);
            }
            else if (CMD_IS_RESP(psWhcMem->msg))
            {
                LOG_I("Get Resp. 0x%08x 0x%08x 0x%08x %d",
                      psWhcMem->msg.u32Cmd,
                      psWhcMem->msg.u32Addr0,
                      psWhcMem->msg.u32Addr1,
                      psWhcMem->msg.u32Size);
            }

        } //if

    } //while
}

static int wormhole_app(void)
{
    rt_err_t result = 0;
    rt_thread_t thread;

    thread = rt_thread_create("whcD", whc_daemon, RT_NULL, 2048, 25, 20);
    if (thread != RT_NULL)
    {
        result = rt_thread_startup(thread);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_COMPONENT_EXPORT(wormhole_app);

void *whc_malloc(uint32_t u32Size)
{
    whc_mem sWhcMem;

    sWhcMem.msg.u32Cmd = PACK_MSG_CMD(evCMD_REQ, evCMD_MEM_ALLOCATE);
    sWhcMem.msg.u32Size  = (uint32_t)u32Size;

    send_msg(&sWhcMem);

    return 0;
}
RTM_EXPORT(whc_malloc);

void *whc_memcpy(void *pvDst, void *pvSrc, uint32_t u32Size)
{
    whc_mem sWhcMem;

    sWhcMem.msg.u32Cmd = PACK_MSG_CMD(evCMD_REQ, evCMD_MEM_COPY);
    sWhcMem.msg.u32Addr0 = (uint32_t)pvDst;
    sWhcMem.msg.u32Addr1 = (uint32_t)pvSrc;
    sWhcMem.msg.u32Size  = (uint32_t)u32Size;

    send_msg(&sWhcMem);

    return 0;
}
RTM_EXPORT(whc_memcpy);


uint32_t whc_devmem_write(void *pvaddr, uint32_t u32value)
{
    whc_mem sWhcMem;

    sWhcMem.msg.u32Cmd = PACK_MSG_CMD(evCMD_REQ, evCMD_DEVMEM_WRITE);
    sWhcMem.msg.u32Addr0 = (uint32_t)pvaddr;
    sWhcMem.msg.u32Addr1 = u32value;
    sWhcMem.msg.u32Size  = sizeof(uint32_t);

    send_msg(&sWhcMem);

    return 0;
}
RTM_EXPORT(whc_devmem_write);

uint32_t whc_devmem_read(void *pvaddr)
{
    whc_mem sWhcMem;

    sWhcMem.msg.u32Cmd = PACK_MSG_CMD(evCMD_REQ, evCMD_DEVMEM_READ);
    sWhcMem.msg.u32Addr0 = (uint32_t)pvaddr;
    sWhcMem.msg.u32Addr1 = 0;
    sWhcMem.msg.u32Size  = sizeof(uint32_t);

    send_msg(&sWhcMem);

    return 0;
}
RTM_EXPORT(whc_devmem_read);

void whc_devmem(int argc, char *argv[])
{
    volatile unsigned int u32Addr;
    unsigned int value = 0, mode = 0;

    if (argc < 2 || argc > 3)
    {
        goto exit_devmem;
    }

    if (argc == 3)
    {
        if (rt_sscanf(argv[2], "0x%x", &value) != 1)
            goto exit_devmem;
        mode = 1; //Write
    }

    if (rt_sscanf(argv[1], "0x%x", &u32Addr) != 1)
        goto exit_devmem;
    else if (u32Addr & (4 - 1))
        goto exit_devmem;

    if (mode)
    {
        whc_devmem_write((void *) u32Addr, value);
    }
    rt_kprintf("0x%08x\n", whc_devmem_read((void *)u32Addr));

    return;
exit_devmem:
    rt_kprintf("Read: whc_devmem <physical address in hex>\n");
    rt_kprintf("Write: whc_devmem <physical address in hex> <value in hex format>\n");
    return;
}
MSH_CMD_EXPORT(whc_devmem, dump device registers);

#endif /* #if defined(BSP_USING_HWSEM)*/
