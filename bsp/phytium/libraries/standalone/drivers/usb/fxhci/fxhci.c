/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxhci.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:17:20
 * Description:  This files is for implmentation of XHCI driver
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include <string.h>
#include "fsleep.h"
#include "fcache.h"

#include "fparameters.h"
#include "fdebug.h"

#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

typedef enum
{
    FXHCI_OP_REG,
} FXhciHandShakeType;

static void FXhciStart(FUsbHc *controller);
static void FXhciStop(FUsbHc *controller);
static FXhciTransCode FXhciReset(FUsbHc *controller);
static void FXhciReinit(FUsbHc *controller);
static void FXhciShutdown(FUsbHc *controller);
static FXhciTransCode FXhciBulk(FUsbEndpoint *ep, int size, u8 *data, int finalize);
static FXhciTransCode FXhciControl(FUsbDev *dev, FUsbDirection dir, int drlen, void *devreq,
                                   int dalen, u8 *data);
static void *FXhciCreateIntrQueue(FUsbEndpoint *ep, int reqsize, int reqcount, int reqtiming);
static void FXhciDestoryIntrQueue(FUsbEndpoint *ep, void *queue);
static u8 *FXhciPollIntrQueue(void *queue);

/*
 * Some structures must not cross page boundaries. To get this,
 * we align them by their size (or the next greater power of 2).
 */
/**
 * @name: FXhciAlign
 * @msg: 分配一段对齐的内存
 * @return {*}
 * @param {FXhci} *xhci, XHCI控制器实例
 * @param {size_t} min_align, 对齐方式
 * @param {size_t} size, 请求的字节数目
 */
void *FXhciAlign(FXhci *const xhci, const size_t min_align, const size_t size)
{
    FASSERT(xhci && xhci->usb);
    size_t align;
    FUsb *instance = xhci->usb;

    if (!(size & (size - 1)))
    {
        align = size;    /* It's a power of 2 */
    }
    else
    {
        align = 1 << ((sizeof(unsigned) << 3) - __builtin_clz(size));
    }

    if (align < min_align)
    {
        align = min_align;
    }

    return FUSB_ALLOCATE(instance, size, align);
}

#ifdef FMEMP_TAG_DEBUG
void *FXhciAlignTag(FXhci *const xhci, const size_t min_align, const size_t size,  const char *file, unsigned long line, const char *msg)
{
    FASSERT(xhci && xhci->usb);
    size_t align;
    FUsb *instance = xhci->usb;

    if (!(size & (size - 1)))
    {
        align = size;    /* It's a power of 2 */
    }
    else
    {
        align = 1 << ((sizeof(unsigned) << 3) - __builtin_clz(size));
    }

    if (align < min_align)
    {
        align = min_align;
    }

    return FUsbMempAllocateTag(instance, size, align, file, line, msg);
}
#endif

/**
 * @name: FXhciClearTrb
 * @msg: 清空TRB，反转TRB的Cycle state
 * @return {*}
 * @param {FXhciTrb} *trb, TRB实例
 * @param {int} pcs, TRB ring的Cycle state
 */
void FXhciClearTrb(FXhciTrb *const trb, const int pcs)
{
    FASSERT(trb);

    trb->ptr_low = 0;
    trb->ptr_high = 0;
    trb->status = 0;
    trb->control = !pcs;

    return;
}

/**
 * @name: FXhciInitCycleRing
 * @msg: 初始化TRB ring
 * @return {*}
 * @param {FXhciTransRing} *tr, TRB ring实例
 * @param {size_t} ring_size, TRB ring中的TRB数目
 */
void FXhciInitCycleRing(FXhciTransRing *const tr, const size_t ring_size)
{
    FASSERT(tr && tr->ring);

    memset((void *)tr->ring, 0, ring_size * sizeof(*tr->ring));
    FXHCI_TRB_SET(TT, &tr->ring[ring_size - 1], FXHCI_TRB_LINK); /* TRB Type */
    FXHCI_TRB_SET(TC, &tr->ring[ring_size - 1], 1); /* Toggle Cycle */

    /* only one segment that points to itself */
    tr->ring[ring_size - 1].ptr_low = (uintptr)(tr->ring);

    tr->pcs = 1;
    tr->cur = tr->ring;

    return;
}

/**
 * @name: FXhciHandShake
 * @msg: 等待XHCI状态，完成握手
 * @return {FError} 等待返回值
 * @param {FXhci} *xhci, xhci实例
 * @param {FXhciHandShakeType} type, 等待类型，e.g 等待Op寄存器
 * @param {uintptr} reg_off, 寄存器偏移量
 * @param {u32} mask, 寄存器掩码位
 * @param {u32} wait_for, 等待的状态，如果状态到达，成功退出
 * @param {s32} timeout, 等待的tick超时
 */
static FError FXhciHandShake(FXhci *xhci, FXhciHandShakeType type, uintptr reg_off, u32 mask, u32 wait_for, s32 timeout)
{
    FASSERT(xhci);
    FError ret = FUSB_SUCCESS;

    switch (type)
    {
        case FXHCI_OP_REG:
            ret = FXhciWaitOper32(&xhci->mmio, reg_off, mask, wait_for, timeout);
            break;
        default:
            FASSERT(0);
            break;
    }

    return ret;
}

/**
 * @name: FXhciWaitReady
 * @msg: 等待XHCI控制器重置完成
 * @return {*}
 * @param {FXhci} *xhci, xhci实例
 */
static FError FXhciWaitReady(FXhci *const xhci)
{
    FASSERT(xhci);
    FUSB_INFO("Waiting for controller to be ready.");
    FError ret = FXhciHandShake(xhci, FXHCI_OP_REG, FXHCI_REG_OP_USBSTS, FXHCI_REG_OP_USBSTS_CNR, 0, FXHCI_TIMEOUT);

    if (FUSB_SUCCESS == ret)
    {
        FUSB_INFO("Waiting for controller success.");
    }
    else
    {
        FUSB_ERROR("Waiting for controller timeout.");
    }

    return ret;
}

/**
 * @name: FXhciHcInit
 * @msg: 创建XHCI USB 控制器实例，完成初始化
 * @return {FUsbHc *} XHCI控制器实例
 * @param {FUsb} *instance, USB实例
 * @param {uintptr} base_addr, XHCI控制器基地址
 */
FUsbHc *FXhciHcInit(FUsb *instance, uintptr base_addr)
{
    FASSERT(instance);
    int i;
    FXhciMMIO *mmio = NULL;
    u32 reg_val;
    u16 hc_version;
    uintptr xhci_base_addr =  base_addr + FUSB3_XHCI_OFFSET;

    FUSB_DEBUG("Xhci base addr: 0x%x.", xhci_base_addr);
    /* First, allocate and initialize static controller structures */
    FUsbHc *const controller = FUsbAllocateHc(instance);
    if (NULL == controller)
    {
        FUSB_ERROR("Out of memory.");
        return NULL;
    }

    /* set USB Hc CB according to XHCI */
    controller->type = FUSB_HC_XHCI;
    controller->start = FXhciStart;
    controller->stop = FXhciStop;
    controller->reset = FXhciReset;
    controller->init = FXhciReinit;
    controller->shutdown = FXhciShutdown;
    controller->bulk = FXhciBulk;
    controller->control = FXhciControl;
    controller->set_address = FXhciSetAddress;
    controller->finish_device_config = FXhciFinishDevConfig;
    controller->destroy_device = FXhciDestoryDev;
    controller->create_intr_queue = FXhciCreateIntrQueue;
    controller->destroy_intr_queue = FXhciDestoryIntrQueue;
    controller->poll_intr_queue = FXhciPollIntrQueue;

    /* allocate xhci instance */
    controller->reg_base = base_addr;
    FASSERT(NULL == controller->instance);
    controller->instance = FUSB_ALLOCATE(instance, sizeof(FXhci), FUSB_DEFAULT_ALIGN);
    if (NULL == controller->instance)
    {
        FUSB_INFO("Out of memory.");
        goto _free_controller;
    }

    controller->usb = instance;

    FXhci *const xhci = (FXhci *)controller->instance;
    xhci->usb = instance;

    /* init roothub at slot-0 */
    FUsbInitDevEntry(controller, 0);
    xhci->roothub = controller->devices[0];

    /* allocate command ring and event ring */
    FASSERT((NULL == xhci->cr.ring) && (NULL == xhci->er.ring) &&
            (NULL == xhci->ev_ring_table));
    xhci->cr.ring = FXHCI_ALIGN(xhci, 64, FXHCI_COMMAND_RING_SIZE * sizeof(FXhciTrb));
    xhci->er.ring = FXHCI_ALIGN(xhci, 64, FXHCI_EVENT_RING_SIZE * sizeof(FXhciTrb));
    xhci->ev_ring_table = FXHCI_ALIGN(xhci, 64, sizeof(FXhciErstEntry));
    if ((NULL == xhci->roothub) || (NULL == xhci->cr.ring) ||
        (NULL == xhci->er.ring) || (NULL == xhci->ev_ring_table))
    {
        FUSB_INFO("Out of memory.");
        goto _free_xhci;
    }

    /* setup xhci mmio for register access */
    mmio = &xhci->mmio;
    FXhciSetupMMIO(mmio, xhci_base_addr);

    /* check if XHCI version is supported */
    hc_version = FXhciReadHcVersion(mmio);
    if (hc_version < FXHCI_HC_VERSION_MIN || hc_version > FXHCI_HC_VERSION_MAX)
    {
        FUSB_ERROR("Xhci version 0x%x not support.", hc_version);
        goto _free_xhci;
    }

    const unsigned pagesize = FXhciReadOper32(mmio, FXHCI_REG_OP_PAGESIZE) << 12;

    FUSB_INFO("regbase: 0x%x", mmio->base);
    FUSB_INFO("caplen:  0x%x", FXhciReadCaplen(mmio));
    FUSB_INFO("rtsoff:  0X%x", mmio->runtime_base - mmio->base);
    FUSB_INFO("dboff:  0X%x", mmio->doorbell_base - mmio->base);
    FUSB_INFO("hciversion: 0x%x", FXhciReadHcVersion(mmio));
    FUSB_INFO("context size: %dB ", FXhciGetCtxSize(mmio));
    FUSB_INFO("page size: %dB ", pagesize);

    /*
     * We haven't touched the hardware yet. So we allocate all dynamic
     * structures at first and can still chicken out easily if we run out
     * of memory.
     */
    reg_val = FXhciReadCap32(&xhci->mmio, FXHCI_REG_CAP_HCSPARAMS1);
    xhci->max_slots_en = FXHCI_REG_CAP_HCSPARAMS1_MAX_SLOTS_GET(reg_val); /* record max slot num */

    /* allocate device related memory, DCBAA and device info */
    FASSERT(NULL == xhci->dcbaa);
    xhci->dcbaa = FXHCI_ALIGN(xhci, 64, (xhci->max_slots_en + 1) * sizeof(u64));
    FASSERT(NULL == xhci->dev);
    xhci->dev = FUSB_ALLOCATE(instance, (xhci->max_slots_en + 1) * sizeof(*xhci->dev), FUSB_DEFAULT_ALIGN);
    if ((NULL == xhci->dcbaa) || (NULL == xhci->dev))
    {
        FUSB_INFO("Out of memory.");
        goto _free_xhci;
    }

    /*
     * Let dcbaa[0] point to another array of pointers, sp_ptrs.
     * The pointers therein point to scratchpad buffers (pages).
     */
    reg_val = FXhciReadCap32(&xhci->mmio, FXHCI_REG_CAP_HCSPARAMS2);
    const size_t max_sp_bufs = FXHCI_REG_CAP_HCSPARAMS2_MAX_SCRATCHPAD_BUFS_GET(reg_val);
    FUSB_INFO("Max scratchpad bufs: 0x%lx reg_val : 0x%x.", max_sp_bufs, reg_val);
    if (0 < max_sp_bufs)
    {
        FUSB_INFO("Allocate sp_ptrs.");
        const size_t sp_ptrs_size = max_sp_bufs * sizeof(u64);
        /* allocate scratchpad bufs entry to preserve pointers of scratchpad buf */
        FASSERT(NULL == xhci->sp_ptrs);
        xhci->sp_ptrs = FXHCI_ALIGN(xhci, 64, sp_ptrs_size);
        if (NULL == xhci->sp_ptrs)
        {
            FUSB_INFO("Out of memory.");
            goto _free_xhci_structs;
        }

        for (i = 0; (size_t)i < max_sp_bufs; ++i)
        {
            /* allocate each scratchpad buf */
            void *const page = FUSB_ALLOCATE(instance, pagesize, pagesize);
            if (NULL == page)
            {
                FUSB_INFO("Out of memory.");
                goto _free_xhci_structs;
            }

            xhci->sp_ptrs[i] = (uintptr)(page); /* assign pointer to scratchpad buf*/
        }

        xhci->dcbaa[0] = (uintptr)(xhci->sp_ptrs); /* assign pointer to scratchpad bufs entry */
    }

    /* Now start working on the hardware */
    if (FUSB_SUCCESS != FXhciWaitReady(xhci))
    {
        goto _free_xhci_structs;
    }

    /* TODO: Check if BIOS claims ownership (and hand over) */

    if (FUSB_CC_SUCCESS != FXhciReset(controller))
    {
        goto _free_xhci_structs;
    }

    FXhciReinit(controller);

    /* init roothub device instance */
    xhci->roothub->controller = controller;
    xhci->roothub->init = FXhciRootHubInit;
    xhci->roothub->init(xhci->roothub);

    FUSB_INFO("Init xhc@%p success.", controller);
    return controller;

_free_xhci_structs:
    if (xhci->sp_ptrs)
    {
        for (i = 0; (size_t)i < max_sp_bufs; ++i)
        {
            if (xhci->sp_ptrs[i])
            {
                FUSB_FREE(instance, (void *)(uintptr)(xhci->sp_ptrs[i]));
            }
        }
    }
    FUSB_FREE(instance, xhci->sp_ptrs);
    FUSB_FREE(instance, xhci->dcbaa);

_free_xhci:
    FUSB_FREE(instance, (void *)xhci->ev_ring_table);
    FUSB_FREE(instance, (void *)xhci->er.ring);
    FUSB_FREE(instance, (void *)xhci->cr.ring);
    FUSB_FREE(instance, xhci->roothub);
    FUSB_FREE(instance, xhci->dev);
    FUSB_FREE(instance, xhci);

_free_controller:
    FUsbDetachHc(controller);
    FUSB_FREE(instance, controller);

    return NULL;
}

/**
 * @name: FXhciReset
 * @msg: 重置XHCI控制器
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc控制器
 */
static FUsbTransCode FXhciReset(FUsbHc *const controller)
{
    FASSERT(controller);
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    u32 reg_val;

    /* stop xhci if still run */
    FXhciStop(controller);

    reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD);
    reg_val |= FXHCI_REG_OP_USBCMD_HCRST;
    FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD, reg_val);

    FUSB_INFO("Resetting hc...");
    if (FUSB_SUCCESS != FXhciHandShake(xhci, FXHCI_OP_REG, FXHCI_REG_OP_USBCMD, FXHCI_REG_OP_USBCMD_HCRST, 0, FXHCI_TIMEOUT))
    {
        FUSB_ERROR("Wait hc reset timeout !!!");
        return -1;
    }

    return FUSB_CC_SUCCESS;
}

/**
 * @name: FXhciReinit
 * @msg: 重新初始化XHCI控制器
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc控制器
 */
static void FXhciReinit(FUsbHc *controller)
{
    FASSERT(controller);
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    const FUsbConfig *const config = &controller->usb->config;
    u32 reg_val;
    u64 reg_val64;

    /* wait xhci ready */
    if (FUSB_SUCCESS != FXhciWaitReady(xhci))
    {
        return;
    }

    /* Enable all available slots */
    reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_CONFIG);
    reg_val &= ~FXHCI_REG_OP_CONFIG_MAX_SLOTS_EN_MASK;
    reg_val |= FXHCI_REG_OP_CONFIG_MAX_SLOTS_EN_SET(xhci->max_slots_en);
    FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_CONFIG, reg_val);

    /* Set DCBAA */
    FXhciWriteOper64(&xhci->mmio, FXHCI_REG_OP_DCBAAP, (u64)(uintptr)xhci->dcbaa);
    FUSB_INFO("dcba at 0x%lx", FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_DCBAAP));

    /* Initialize command ring */
    FXhciInitCycleRing(&xhci->cr, FXHCI_COMMAND_RING_SIZE);
    FUSB_INFO("command ring @%p", xhci->cr.ring);
    reg_val64 = FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_CRCR);

    reg_val64 = FXHCI_REG_OP_CRCR_CR_PTR_MASK & (u64)(uintptr)xhci->cr.ring;
    reg_val64 |= FXHCI_REG_OP_CRCR_RCS & xhci->cr.pcs;
    FXhciWriteOper64(&xhci->mmio, FXHCI_REG_OP_CRCR, reg_val64);

    /* Make sure interrupts are disabled */
    reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD);
    reg_val &= ~FXHCI_REG_OP_USBCMD_INTE;
    FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD, reg_val);

    /* Initialize event ring */
    FXhciResetEvtRing(&xhci->er);
    FUSB_INFO("event ring @%p (0x%08p) ",
              xhci->er.ring, (uintptr)(xhci->er.ring));

    reg_val = FXhciReadCap32(&xhci->mmio, FXHCI_REG_CAP_HCSPARAMS2);
    FUSB_INFO("ERST Max: %d",
              FXHCI_REG_CAP_HCSPARAMS2_ERST_MAX_GET(reg_val));
    memset((void *)xhci->ev_ring_table, 0x00, sizeof(FXhciErstEntry));
    xhci->ev_ring_table[0].seg_base_lo = (uintptr)(xhci->er.ring);
    xhci->ev_ring_table[0].seg_base_hi = 0;
    xhci->ev_ring_table[0].seg_size = FXHCI_EVENT_RING_SIZE;

    /* pass event ring table to hardware */
    WMB();

    /* Initialize primary interrupter */
    FXhciWriteRt32(&xhci->mmio, 0, FXHCI_REG_RT_IR_ERSTSZ, FXHCI_REG_RT_IR_ERSTSZ_MASK & 1); /* Segment Table Size = 1 */
    FXhciUpdateEvtDQ(xhci);

    /* erstba has to be written at last */
    FXhciWriteRt64(&xhci->mmio, 0, FXHCI_REG_RT_IR_ERSTBA, FXHCI_REG_RT_IR_ERSTBA_MASK & ((u64)(uintptr)xhci->ev_ring_table));
    FUSB_INFO("ERST base: 0x%lx == %p",
              FXhciReadRt64(&xhci->mmio, 0, FXHCI_REG_RT_IR_ERSTBA),
              xhci->ev_ring_table);

    FXhciStart(controller);

    /* run Cmd Nop to test if command ring okay */
    for (int i = 0; i < 3; ++i)
    {
        FUSB_INFO("Noop run #%d .", i);
        if (FXHCI_CC_SUCCESS != FXhciCmdNop(xhci))
        {
            FUSB_ERROR("Noop command failed. ");
            break;
        }
    }

    return;
}

/**
 * @name: FXhciShutdown
 * @msg: 关闭XHCI控制器
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc控制器
 */
static void FXhciShutdown(FUsbHc *const controller)
{
    int i;
    u32 reg_val;

    if (controller == NULL)
    {
        return;
    }

    /* detach the Hc instance */
    FUsbDetachHc(controller);

    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci && xhci->usb);
    FUsb *instance = xhci->usb;
    FXhciStop(controller); /* stop xhci instance */

    /* free scatchpad bufs */
    if (NULL != xhci->sp_ptrs)
    {
        reg_val = FXhciReadCap32(&xhci->mmio, FXHCI_REG_CAP_HCSPARAMS2);
        const size_t max_sp_bufs = FXHCI_REG_CAP_HCSPARAMS2_MAX_SCRATCHPAD_BUFS_GET(reg_val);
        for (i = 0; (size_t)i < max_sp_bufs; ++i)
        {
            if (NULL != (void *)(uintptr)xhci->sp_ptrs[i])
            {
                FUSB_FREE(instance, (void *)(uintptr)(xhci->sp_ptrs[i]));
            }
        }
    }


    FUSB_FREE(instance, xhci->sp_ptrs);
    FUSB_FREE(instance, xhci->dcbaa);
    FUSB_FREE(instance, xhci->dev);
    FUSB_FREE(instance, (void *)xhci->ev_ring_table);
    FUSB_FREE(instance, (void *)xhci->er.ring);
    FUSB_FREE(instance, (void *)xhci->cr.ring);
    FUSB_FREE(instance, xhci);

    return;
}

/**
 * @name: FXhciStart
 * @msg: 启动XHCI控制器
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc控制器
 */
static void FXhciStart(FUsbHc *controller)
{
    FASSERT(controller);
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    u32 reg_val;

    /* setting the USBCMD register Run/Stop (R/S) bit to ‘1’ */
    reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD);
    reg_val |= FXHCI_REG_OP_USBCMD_RUN_STOP;
    FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD, reg_val);

    if (FUSB_SUCCESS != FXhciHandShake(xhci, FXHCI_OP_REG, FXHCI_REG_OP_USBSTS, FXHCI_REG_OP_USBSTS_HCH, 0, FXHCI_TIMEOUT))
    {
        FUSB_ERROR("Wait hc start timeout !!!");
    }

    return;
}

/**
 * @name: FXhciStop
 * @msg: 停止XHCI控制器
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc控制器
 */
static void FXhciStop(FUsbHc *controller)
{
    FASSERT(controller);
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    u32 reg_val;

    /* setting the USBCMD register Run/Stop (R/S) bit to ‘0’ */
    reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD);
    reg_val &= ~FXHCI_REG_OP_USBCMD_RUN_STOP;
    FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_USBCMD, reg_val);

    if (FUSB_SUCCESS != FXhciHandShake(xhci, FXHCI_OP_REG, FXHCI_REG_OP_USBSTS, FXHCI_REG_OP_USBSTS_HCH, FXHCI_REG_OP_USBSTS_HCH, FXHCI_TIMEOUT))
    {
        FUSB_ERROR("Wait hc stop timeout !!!");
    }

    return;
}

/**
 * @name: FXhciResetEp
 * @msg: 重置XHCI端点
 * @return {FError} 返回错误码
 * @param {FUsbDev} *dev, 端点所在的USB设备实例
 * @param {FUsbEndpoint} *ep, 端点实例
 */
static FError FXhciResetEp(FUsbDev *const dev, FUsbEndpoint *const ep)
{
    FASSERT(dev && dev->controller);
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    const int slot_id = dev->address;
    const int ep_id = (NULL != ep) ? FXhciEpId(ep) : FXHCI_EP0_ID; /* ep-0 or normal ep */
    FXhciEpCtx *const epctx = xhci->dev[slot_id].ctx.ep[ep_id];

    FUSB_INFO("Resetting ID %d EP %d (ep state: %d) ",
              slot_id, ep_id, FXHCI_EC_GET(STATE, epctx));

    /* Run Reset Endpoint Command if the EP is in Halted state */
    if (FXHCI_EC_GET(STATE, epctx) == FXHCI_EC_STATE_HALTED)
    {
        const FXhciTransCode cc = FXhciCmdResetEp(xhci, slot_id, ep_id);
        if (cc != FXHCI_CC_SUCCESS)
        {
            FUSB_INFO("Reset endpoint command failed: %d .", cc);
            return FUSB_ERR_TRANS_FAIL;
        }
    }

    /* Clear TT buffer for bulk and control endpoints behind a TT */
    const int hub = dev->hub;
    if (hub && dev->speed < FUSB_HIGH_SPEED &&
        dev->controller->devices[hub]->speed == FUSB_HIGH_SPEED)
    {
        /* TODO */;
    }

    /* Reset transfer ring if the endpoint is in the right state */
    const unsigned ep_state = FXHCI_EC_GET(STATE, epctx);
    if (ep_state == FXHCI_EC_STATE_STOPPED || ep_state == FXHCI_EC_STATE_ERROR)
    {
        FXhciTransRing *const tr =
            xhci->dev[slot_id].transfer_rings[ep_id];
        const FXhciTransCode cc = FXhciCmdSetTrDq(xhci, slot_id, ep_id,
                                  tr->ring, 1);
        if (cc != FXHCI_CC_SUCCESS)
        {
            FUSB_INFO("Set TR dequeue command failed: %d .", cc);
            return FUSB_ERR_TRANS_FAIL;
        }

        FXhciInitCycleRing(tr, FXHCI_TRANSFER_RING_SIZE);
    }

    FUSB_INFO("Finished resetting ID %d EP %d (ep state: %d) ",
              slot_id, ep_id, FXHCI_EC_GET(STATE, epctx));

    return FUSB_SUCCESS;
}

/**
 * @name: FXhciEnqueueTrb
 * @msg: TRB入队，向TRB ring加入一条TRB
 * @return {*}
 * @param {FXhciTransRing} *tr, TRB ring实例
 */
static void FXhciEnqueueTrb(FXhciTransRing *const tr)
{
    FASSERT(tr);

    const int chain = FXHCI_TRB_GET(CH, tr->cur);
    FXHCI_TRB_SET(C, tr->cur, tr->pcs); /* Cycle Bit */
    ++tr->cur;

    while (FXHCI_TRB_GET(TT, tr->cur) == FXHCI_TRB_LINK)
    {
        FUSB_DEBUG("Handling link pointer. ");

        const int tc = FXHCI_TRB_GET(TC, tr->cur);
        FXHCI_TRB_SET(CH, tr->cur, chain); /* Chain Bit */

        WMB();

        FXHCI_TRB_SET(C, tr->cur, tr->pcs); /* Cycle Bit */
        tr->cur = (void *)(uintptr)(tr->cur->ptr_low);

        /* toggle cycle state */
        if (tc)
        {
            tr->pcs ^= 1;
        }
    }

    return;
}

/**
 * @name: FXhciRingDoorbell
 * @msg: 提醒Hc处理刚加入的TRB
 * @return {*}
 * @param {FUsbEndpoint} *ep, 端点实例
 */
static void FXhciRingDoorbell(FUsbEndpoint *const ep)
{
    FASSERT(ep);
    FXhci *xhci = FXHCI_INST_GET(ep->dev->controller);

    /* Ensure all TRB changes are written to memory. */
    WMB();

    FXhciWriteDb32(&xhci->mmio, ep->dev->address, FXhciEpId(ep));

    return;
}

/**
 * @name: FXhciEnqueueTD
 * @msg: 填充一条TRB
 * @return {*}
 * @param {FXhciTransRing} *tr, TRB ring实例
 * @param {int} ep, 端点实例
 * @param {size_t} mps, 最大包长度
 * @param {int} dalen, 数据长度
 * @param {void} *data, 数据缓冲区
 * @param {int} dir, 发送方向
 */
static void FXhciEnqueueTD(FXhciTransRing *const tr, const int ep, const size_t mps,
                           const int dalen, void *const data, const int dir)
{
    FASSERT(tr);
    FXhciTrb *trb = NULL;                      /* cur TRB */
    u8 *cur_start = data;                      /* cur data pointer */
    size_t length = dalen;                     /* remaining bytes */
    size_t packets = (length + mps - 1) / mps; /* remaining packets */
    size_t residue = 0;                        /* residue from last TRB */
    size_t trb_count = 0;                      /* TRBs added so far */

    while ((length > 0) || (trb_count == 0) /* enqueue at least one */)
    {
        const size_t cur_end = ((size_t)cur_start + 0x10000) & ~0xffff; /* best guess, send at most 0x1000 bytes */
        size_t cur_length = cur_end - (size_t)cur_start;

        if (length < cur_length)
        {
            cur_length = length;
            packets = 0;
            length = 0;
        }
        else
        {
            packets -= (residue + cur_length) / mps;
            residue = (residue + cur_length) % mps;
            length -= cur_length;
        }

        trb = tr->cur;
        FXhciClearTrb(trb, tr->pcs);
        trb->ptr_low = (uintptr)(cur_start);
        FXHCI_TRB_SET(TL, trb, cur_length); /* Transfer Length */
        FXHCI_TRB_SET(TDS, trb, min((size_t)FXHCI_TRB_MAX_TD_SIZE, packets)); /* TD Size */
        FXHCI_TRB_SET(CH, trb, 1); /* associate this TRB with the next TRB on the Ring */

        /* Check for first, data stage TRB, only Ep0 can handle */
        if ((trb_count == 0) && ep == FXHCI_EP0_ID)
        {
            FXHCI_TRB_SET(DIR, trb, dir); /* Direction */
            FXHCI_TRB_SET(TT, trb, FXHCI_TRB_DATA_STAGE); /* TRB Type */
        }
        else
        {
            FXHCI_TRB_SET(TT, trb, FXHCI_TRB_NORMAL); /* TRB Type */
        }

        /*
         * This is a workaround for Synopsys DWC3. If the ENT flag is
         * not set for the Normal and Data Stage TRBs. We get Event TRB
         * with length 0x20d from the controller when we enqueue a TRB
         * for the IN endpoint with length 0x200.
         */
        if (0 == length)
        {
            /* xHC shall fetch and evaluate the next TRB before saving the endpoint state */
            FXHCI_TRB_SET(ENT, trb, 1); /* Evaluate Next TRB */
        }

        FXhciEnqueueTrb(tr);

        cur_start += cur_length;
        ++trb_count;
    }

    trb = tr->cur;
    FXhciClearTrb(trb, tr->pcs);
    trb->ptr_low = (uintptr)(trb); /* for easier debugging only */
    FXHCI_TRB_SET(TT, trb, FXHCI_TRB_EVENT_DATA); /* set transfer type */
    FXHCI_TRB_SET(IOC, trb, 1); /* xHc shalle notify the system of the completion by placing an Transfer Event TRB on the Event ring */

    FXhciEnqueueTrb(tr);

    return;
}

/**
 * @name: FXhciControl
 * @msg: XHCI控制传输
 * @return {FXhciTransCode} 传输返回值
 * @param {FUsbDev} *dev, USB设备实例
 * @param {FUsbDirection} dir, 控制传输类型, IN, OUT, SETUP
 * @param {int} drlen, USB请求长度
 * @param {void} *devreq, USB请求，参考FUsbDevReq
 * @param {int} dalen, 控制传输数据长度
 * @param {unsigned char} *src, 控制传输数据
 */
static FXhciTransCode FXhciControl(FUsbDev *const dev, const FUsbDirection dir,
                                   const int drlen, void *const devreq, const int dalen,
                                   unsigned char *const src)
{
    FASSERT(dev && dev->controller);
    unsigned char *data = src;
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    FXhciEpCtx *const epctx = xhci->dev[dev->address].ctx.ep0;
    FXhciTransRing *const tr = xhci->dev[dev->address].transfer_rings[1];
    FASSERT(epctx && tr);

    /* check the transfer data length, less than WORD size, u16 pointer can hold */
    const size_t off = (size_t)data & 0xffff;
    if ((off + dalen) > ((FXHCI_TRANSFER_RING_SIZE - 4) << 16))
    {
        FUSB_ERROR("Unsupported transfer size 0x%lx!!!", dalen);
        return FXHCI_CC_GENERAL_ERROR;
    }

    /* Reset endpoint if it's not running and not disabled */
    const unsigned ep_state = FXHCI_EC_GET(STATE, epctx);
    if (ep_state > FXHCI_EC_STATE_RUNNING)
    {
        if (FUSB_SUCCESS != FXhciResetEp(dev, NULL))
        {
            FUSB_ERROR("Reset endpoint failed !!!");
            return FXHCI_CC_GENERAL_ERROR;
        }
    }

    /* Fill and enqueue setup TRB */
    FXhciTrb *const setup = tr->cur;
    FXhciClearTrb(setup, tr->pcs);
    setup->ptr_low = ((u32 *)devreq)[0]; /* request data */
    setup->ptr_high = ((u32 *)devreq)[1];
    FXHCI_TRB_SET(TL, setup, drlen/*8*/); /* Transfer length */
    FXHCI_TRB_SET(TRT, setup, (dalen > 0) ? ((dir == FUSB_OUT) ? FXHCI_TRB_TRT_OUT_DATA : FXHCI_TRB_TRT_IN_DATA) : FXHCI_TRB_TRT_NO_DATA);
    FXHCI_TRB_SET(TT, setup, FXHCI_TRB_SETUP_STAGE); /* TRB Type */
    FXHCI_TRB_SET(IDT, setup, 1); /* Immediate Data (IDT). shall be set to ‘1’ in a Setup Stage TRB */
    FXHCI_TRB_SET(IOC, setup, 1); /* Interrupt On Completion (IOC) */
    FXhciEnqueueTrb(tr);

    /* Fill and enqueue data TRBs (if any) */
    if (dalen > 0)
    {
        const unsigned mps = FXHCI_EC_GET(MPS, epctx);
        const unsigned dt_dir = (dir == FUSB_OUT) ? FXHCI_TRB_DIR_OUT : FXHCI_TRB_DIR_IN;
        FXhciEnqueueTD(tr, FXHCI_EP0_ID, mps, dalen, data, dt_dir);
    }

    /* Fill status TRB */
    FXhciTrb *const status = tr->cur;
    FXhciClearTrb(status, tr->pcs);
    FXHCI_TRB_SET(DIR, status, (dir == FUSB_OUT) ? FXHCI_TRB_DIR_IN : FXHCI_TRB_DIR_OUT); /* Direction */
    FXHCI_TRB_SET(TT, status, FXHCI_TRB_STATUS_STAGE); /* TRB Type */
    FXHCI_TRB_SET(IOC, status, 1); /* Interrupt On Completion */
    FXhciEnqueueTrb(tr);

    /* Ring doorbell for EP0 */
    FXhciRingDoorbell(&dev->endpoints[0]);

    /* Wait for transfer events from IN DATA OUT stages */
    int i, transferred = 0;
    const int n_stages = 2 + !!dalen; /* 2 stage without data */

    /* flush cache of request data / transfer data before transfer */
    if (dalen > 0)
    {
        FCacheDCacheInvalidateRange((uintptr)data, dalen);
        FCacheDCacheInvalidateRange((uintptr)devreq, drlen);
    }

    for (i = 0; i < n_stages; ++i)
    {
        const FXhciTransCode ret = FXhciWaitForTransfer(xhci, dev->address, 1);
        transferred += ret; /* record bytes transfered successfully */
        if (ret < FXHCI_CC_ZERO_BYTES) /* negative ret means transfer error */
        {
            if (ret == FXHCI_CC_TIMEOUT)
            {
                FUSB_ERROR("Stopping ID %d EP 1 ",
                           dev->address);
                FXhciCmdStopEp(xhci, dev->address, FXHCI_EP0_ID);
            }

            FUSB_ERROR("Stage %d/%d failed: %d \r\n"
                       "  trb ring:   @%p \r\n"
                       "  setup trb:  @%p \r\n"
                       "  status trb: @%p \r\n"
                       "  ep state:   %d -> %d \r\n"
                       "  usbsts:     0x%08x ",
                       i, n_stages, ret,
                       tr->ring, setup, status,
                       ep_state, FXHCI_EC_GET(STATE, epctx),
                       FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBSTS));
            return ret;
        }
    }

    /* flush cache of request data / transfer data after transfer */
    if (dalen > 0)
    {
        FCacheDCacheInvalidateRange((uintptr)data, dalen);
        FCacheDCacheInvalidateRange((uintptr)devreq, drlen);
    }

    return transferred;
}

/**
 * @name: FXhciBulk
 * @msg: XHCI块传输
 * @return {FXhciTransCode}
 * @param {FUsbEndpoint} *ep, 端点实例
 * @param {int} size,
 * @param {u8} *src
 * @param {int} finalize
 * @note: finalize == 1: if data is of packet aligned size, add a zero length packet
 */
static FXhciTransCode FXhciBulk(FUsbEndpoint *const ep, const int size, u8 *const src,
                                const int finalize)
{
    /* finalize: Hopefully the xHCI controller always does this.
       We have no control over the packets. */
    FASSERT(ep);
    u8 *data = src;
    FXhci *const xhci = FXHCI_INST_GET(ep->dev->controller);
    FASSERT(xhci);
    const int slot_id = ep->dev->address;
    const int ep_id = FXhciEpId(ep); /* must not for Ep0 */
    FXhciEpCtx *const epctx = xhci->dev[slot_id].ctx.ep[ep_id];
    FXhciTransRing *const tr = xhci->dev[slot_id].transfer_rings[ep_id];

    /* check the transfer data length, less than WORD size, u16 pointer can hold */
    const size_t off = (size_t)data & 0xffff;
    if ((off + size) > ((FXHCI_TRANSFER_RING_SIZE - 2) << 16))
    {
        FUSB_INFO("Unsupported transfer size .");
        return FXHCI_CC_GENERAL_ERROR;
    }

    /* Reset endpoint if it's not running */
    const unsigned ep_state = FXHCI_EC_GET(STATE, epctx);
    if (ep_state > FXHCI_EC_STATE_RUNNING)
    {
        if (FUSB_SUCCESS != FXhciResetEp(ep->dev, ep))
        {
            return FXHCI_CC_GENERAL_ERROR;
        }
    }

    FCacheDCacheInvalidateRange((uintptr)data, size);

    /* Enqueue transfer and ring doorbell */
    const unsigned mps = FXHCI_EC_GET(MPS, epctx);
    const unsigned dir = (ep->direction == FUSB_OUT) ? FXHCI_TRB_DIR_OUT : FXHCI_TRB_DIR_IN;
    FXhciEnqueueTD(tr, ep_id, mps, size, data, dir);
    FXhciRingDoorbell(ep);

    /* Wait for transfer event */
    const FXhciTransCode ret = FXhciWaitForTransfer(xhci, ep->dev->address, ep_id);
    if (ret < FXHCI_CC_ZERO_BYTES)
    {
        if (ret == FXHCI_CC_TIMEOUT)
        {
            FUSB_INFO("Stopping ID %d EP %d ",
                      ep->dev->address, ep_id);
            FXhciCmdStopEp(xhci, ep->dev->address, ep_id);
        }

        FUSB_INFO("Bulk transfer failed: %d \r\n"
                  "  ep state: %d -> %d \r\n"
                  "  usbsts:   0x%08x ",
                  ret, ep_state,
                  FXHCI_EC_GET(STATE, epctx),
                  FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBSTS));

        return ret;
    }

    return ret;
}

/**
 * @name: FXhciNextTrb
 * @msg: 获取下一个可用的TRB
 * @return {FXhciTrb*} 可用的TRB
 * @param {FXhciTrb} *cur, 当前TRB
 * @param {int} *pcs, 传入的待反转的Cycle state
 */
static FXhciTrb *FXhciNextTrb(FXhciTrb *cur, int *const pcs)
{
    FASSERT(cur);
    ++cur;

    while (FXHCI_TRB_GET(TT, cur) == FXHCI_TRB_LINK)
    {
        if (pcs && FXHCI_TRB_GET(TC, cur))
        {
            *pcs ^= 1;
        }

        cur = (void *)(uintptr)(cur->ptr_low);
    }

    return cur;
}

/**
 * @name: FXhciCreateIntrQueue
 * @msg: 创建XHCI的中断队列
 * @return {void *} 成功则返回指向中断队列的指针，失败返回NULL
 * @param {FUsbEndpoint} *ep, 端点实例
 * @param {int} reqsize, 中断队列可接受的请求字节数
 * @param {int} reqcount, 中断队列可接受的最大请求数目
 * @param {int} reqtiming, 请求超时
 * @note create and hook-up an intr queue into device schedul
 */
static void *FXhciCreateIntrQueue(FUsbEndpoint *const ep, const int reqsize, const int reqcount,
                                  const int reqtiming)
{
    /* reqtiming: We ignore it and use the interval from the
        endpoint descriptor configured earlier. */
    FASSERT(ep);
    FXhci *const xhci = FXHCI_INST_GET(ep->dev->controller);
    FASSERT(xhci && xhci->usb);
    FUsb *instance = xhci->usb;
    const int slot_id = ep->dev->address;
    const int ep_id = FXhciEpId(ep);
    FXhciTransRing *const tr = xhci->dev[slot_id].transfer_rings[ep_id];

    if (reqcount > (FXHCI_TRANSFER_RING_SIZE - 2))
    {
        FUSB_INFO("Reqcount is too high, at most %d supported .",
                  FXHCI_TRANSFER_RING_SIZE - 2);
        return NULL;
    }

    if (reqsize > 0x10000)
    {
        FUSB_INFO("Reqsize is too large, at most 64KiB supported .");
        return NULL;
    }

    if (xhci->dev[slot_id].interrupt_queues[ep_id])
    {
        FUSB_INFO("Only one interrupt queue per endpoint supported .");
        return NULL;
    }

    /* Allocate intrq structure and reqdata chunks */
    FXhciIntrQ *const intrq = FUSB_ALLOCATE(instance, sizeof(*intrq), FUSB_DEFAULT_ALIGN);
    if (NULL == intrq)
    {
        FUSB_INFO("Out of memory.");
        return NULL;
    }

    int i;
    int pcs = tr->pcs;
    FXhciTrb *cur = tr->cur;
    for (i = 0; i < reqcount; ++i)
    {
        if (FXHCI_TRB_GET(C, cur) == (unsigned int)pcs)
        {
            FUSB_INFO("Not enough empty TRBs .");
            goto _free_return;
        }

        /* allocate request buffer for each TRB */
        void *const reqdata = FXHCI_ALIGN(xhci, 1, reqsize);
        if (NULL == reqdata)
        {
            FUSB_INFO("Out of memory.");
            goto _free_return;
        }

        FXhciClearTrb(cur, pcs);
        cur->ptr_low = (uintptr)(reqdata);
        cur->ptr_high = 0;
        FXHCI_TRB_SET(TL, cur, reqsize); /* Transfer Length */
        FXHCI_TRB_SET(TT, cur, FXHCI_TRB_NORMAL); /* TRB Type */
        FXHCI_TRB_SET(ISP, cur, 1); /* Interrupt-on Short Packet */
        FXHCI_TRB_SET(IOC, cur, 1); /* Interrupt On Completion */

        cur = FXhciNextTrb(cur, &pcs);
    }

    intrq->size = reqsize;
    intrq->count = reqcount;
    intrq->next = tr->cur;
    intrq->ready = NULL;
    intrq->ep = ep;
    xhci->dev[slot_id].interrupt_queues[ep_id] = intrq;

    /* Now enqueue all the prepared TRBs but the last
       and ring the doorbell. */
    for (i = 0; i < (reqcount - 1); ++i)
    {
        FXhciEnqueueTrb(tr);
    }

    FXhciRingDoorbell(ep);
    return intrq;

_free_return:
    cur = tr->cur;
    for (--i; i >= 0; --i)
    {
        FUSB_FREE(instance, (void *)(uintptr)(cur->ptr_low));
        cur = FXhciNextTrb(cur, NULL);
    }
    FUSB_FREE(instance, intrq);
    return NULL;
}

/**
 * @name: FXhciDestoryIntrQueue
 * @msg: 删除中断队列
 * @return {*}
 * @param {FUsbEndpoint} *ep, 端点实例
 * @param {void} *q, 中断队列
 * @note remove queue from device schedule, dropping all data that came in
 */
static void FXhciDestoryIntrQueue(FUsbEndpoint *const ep, void *const q)
{
    FASSERT(ep && q);
    FXhci *const xhci = FXHCI_INST_GET(ep->dev->controller);
    FASSERT(xhci);
    FUsb *instance = xhci->usb;
    const int slot_id = ep->dev->address;
    const int ep_id = FXhciEpId(ep);
    FXhciTransRing *const tr = xhci->dev[slot_id].transfer_rings[ep_id];
    FXhciIntrQ *const intrq = (FXhciIntrQ *)q;

    /* Make sure the endpoint is stopped */
    if (FXHCI_EC_GET(STATE, xhci->dev[slot_id].ctx.ep[ep_id]) == FXHCI_EC_STATE_RUNNING)
    {
        const FXhciTransCode cc = FXhciCmdStopEp(xhci, slot_id, ep_id);
        if (cc != FXHCI_CC_SUCCESS)
        {
            FUSB_INFO("Warning: Failed to stop endpoint .");
        }
    }

    /* Process all remaining transfer events */
    FXhciHandleEvts(xhci);

    /* Free all pending transfers and the interrupt queue structure */
    int i;
    for (i = 0; (size_t)i < intrq->count; ++i)
    {
        FUSB_FREE(instance, (void *)(uintptr)(intrq->next->ptr_low));
        intrq->next = FXhciNextTrb(intrq->next, NULL);
    }

    xhci->dev[slot_id].interrupt_queues[ep_id] = NULL;
    FUSB_FREE(instance, (void *)intrq);

    /* Reset the controller's dequeue pointer and reinitialize the ring */
    FXhciCmdSetTrDq(xhci, slot_id, ep_id, tr->ring, 1);
    FXhciInitCycleRing(tr, FXHCI_TRANSFER_RING_SIZE);

    return;
}

/**
 * @name: FXhciPollIntrQueue
 * @msg: 轮询一次中断队列进行处理
 * @return {*}
 * @param {void} *q, 中断队列
 * @note read one intr-packet from queue, if available. extend the queue for new input.
   return NULL if nothing new available.
   Recommended use: while (data=poll_intr_queue(q)) process(data);
 */
static u8 *FXhciPollIntrQueue(void *const q)
{
    if (NULL == q)
    {
        return NULL;
    }

    FXhciIntrQ *const intrq = (FXhciIntrQ *)q;
    FUsbEndpoint *const ep = intrq->ep;
    FXhci *const xhci = FXHCI_INST_GET(ep->dev->controller);
    FASSERT(xhci);

    /* TODO: Reset interrupt queue if it gets halted? */
    FXhciHandleEvts(xhci);

    u8 *reqdata = NULL;
    while (!reqdata && intrq->ready)
    {
        const int ep_id = FXhciEpId(ep);
        FXhciTransRing *const tr =
            xhci->dev[ep->dev->address].transfer_rings[ep_id];

        /* Fetch the request's buffer */
        reqdata = (void *)(uintptr)(intrq->next->ptr_low);

        /* Enqueue the last (spare) TRB and ring doorbell */
        FXhciEnqueueTrb(tr);
        FXhciRingDoorbell(ep);

        /* Reuse the current buffer for the next spare TRB */
        FXhciClearTrb(tr->cur, tr->pcs);
        tr->cur->ptr_low = (uintptr)(reqdata);
        tr->cur->ptr_high = 0;
        FXHCI_TRB_SET(TL, tr->cur, intrq->size); /* Transfer Length */
        FXHCI_TRB_SET(TT, tr->cur, FXHCI_TRB_NORMAL); /* TRB Type */
        FXHCI_TRB_SET(ISP, tr->cur, 1); /* Interrupt-on Short Packet */
        FXHCI_TRB_SET(IOC, tr->cur, 1); /* Interrupt On Completion */

        /* Check if anything was transferred */
        const size_t read = FXHCI_TRB_GET(TL, intrq->next);
        if (!read)
        {
            reqdata = NULL;
        }
        else if (read < intrq->size)
            /* At least zero it, poll interface is rather limited */
        {
            memset(reqdata + read, 0x00, intrq->size - read);
        }

        /* Advance the interrupt queue */
        if (intrq->ready == intrq->next)
            /* This was last TRB being ready */
        {
            intrq->ready = NULL;
        }
        intrq->next = FXhciNextTrb(intrq->next, NULL);
    }

    return reqdata;
}