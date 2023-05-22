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
 * FilePath: fxhci_dev.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:12:46
 * Description:  This files is for implementation of XHCI device
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include <string.h>
#include "fsleep.h"
#include "fcache.h"
#include "fdebug.h"

#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI_DEV"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

static u32 FXhciGenRounte(FXhci *const xhci, const int hubport, const int hubaddr)
{
    FASSERT(xhci);
    if (!hubaddr)
    {
        return 0;
    }

    u32 route_string = FXHCI_SC_GET(ROUTE, xhci->dev[hubaddr].ctx.slot);
    int i;

    for (i = 0; i < 20; i += 4)
    {
        if (!(route_string & (0xf << i)))
        {
            route_string |= (hubport & 0xf) << i;
            break;
        }
    }

    return route_string;
}

static int FXhciGetRoothubPort(FXhci *const xhci, const int hubport, const int hubaddr)
{
    FASSERT(xhci);
    if (!hubaddr)
    {
        return hubport;
    }

    return FXHCI_SC_GET(RHPORT, xhci->dev[hubaddr].ctx.slot);
}

static int FXhciGetTT(FXhci *const xhci, const FUsbSpeed speed,
                      const int hubport, const int hubaddr,
                      int *const tt, int *const tt_port)
{
    FASSERT(xhci);
    if (!hubaddr)
    {
        return 0;
    }

    const FXhciSlotCtx *const slot = xhci->dev[hubaddr].ctx.slot;

    if ((*tt = FXHCI_SC_GET(TTID, slot)))
    {
        *tt_port = FXHCI_SC_GET(TTPORT, slot);
    }
    else if (speed < FUSB_HIGH_SPEED &&
             FXHCI_SC_GET(SPEED1, slot) - 1 == FUSB_HIGH_SPEED)
    {
        *tt = hubaddr;
        *tt_port = hubport;
    }

    return *tt != 0;
}

static void FXhciReapSlots(FXhci *const xhci, int skip_slot)
{
    FASSERT(xhci);
    int i;
    FUsb *instance = xhci->usb;

    FUSB_INFO("Xhci resource shortage, trying to reap old slots.");
    for (i = 1; i <= xhci->max_slots_en; i++)
    {
        if (i == skip_slot)
        {
            continue;    /* don't reap slot we were working on */
        }
        if (xhci->dev[i].transfer_rings[1])
        {
            continue;    /* slot still in use */
        }
        if (NULL == xhci->dev[i].ctx.raw)
        {
            continue;    /* slot already disabled */
        }

        const FXhciTransCode cc = FXhciCmdDisableSlot(xhci, i);
        if (cc != FXHCI_CC_SUCCESS)
        {
            FUSB_INFO("Failed to disable slot %d: %d.", i, cc);
        }
        else
        {
            FUSB_INFO("Successfully reaped slot %d.", i);
        }
        xhci->dcbaa[i] = 0;

        FUSB_FREE(instance, xhci->dev[i].ctx.raw);
        xhci->dev[i].ctx.raw = NULL;
    }
}

static FXhciInputCtx *FXhciMakeInputCtx(FXhci *xhci, const size_t ctxsize)
{
    int i;
    const size_t size = (1 + FXHCI_NUM_EPS) * ctxsize;
    FUsb *instance = xhci->usb;
    FXhciInputCtx *const ic = FUSB_ALLOCATE(instance, sizeof(*ic), FUSB_DEFAULT_ALIGN);
    void *dma_buffer = FUSB_ALLOCATE(instance, size, 64);

    if ((NULL == ic) || (NULL == dma_buffer))
    {
        FUSB_FREE(instance, ic);
        FUSB_FREE(instance, dma_buffer);
        return NULL;
    }


    memset(dma_buffer, 0, size);
    ic->drop = dma_buffer + 0;
    ic->add = dma_buffer + 4;
    dma_buffer += ctxsize;
    for (i = 0; i < FXHCI_NUM_EPS; i++, dma_buffer += ctxsize)
    {
        ic->dev.ep[i] = dma_buffer;
    }

    return ic;
}

/**
 * @name: FXhciSetAddress
 * @msg: 设备USB设备的地址
 * @return {FUsbDev *}, USB设备实例
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {FUsbSpeed} speed, USB设备的速度类型
 * @param {int} hubport, USB设备连接的port号
 * @param {int} hubaddr, USB设备连接的hub地址
 */
FUsbDev *FXhciSetAddress(FUsbHc *controller, FUsbSpeed speed, int hubport, int hubaddr)
{
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    const size_t ctxsize = FXhciGetCtxSize(&xhci->mmio);
    FXhciDevInfo *di = NULL;
    FUsbDev *dev = NULL;
    FUsb *instance = controller->usb;
    int i;

    FXhciInputCtx *const ic = FXhciMakeInputCtx(xhci, ctxsize);
    FXhciTransRing *const tr = FUSB_ALLOCATE(instance, sizeof(*tr), FUSB_DEFAULT_ALIGN);

    if (NULL != tr)
    {
        FASSERT(NULL == tr->ring);
        tr->ring = FXHCI_ALIGN(xhci, 16, FXHCI_TRANSFER_RING_SIZE * sizeof(FXhciTrb));
    }

    if ((NULL == ic) || (NULL == tr) || (NULL == tr->ring))
    {
        FUSB_INFO("Out of memory.");
        goto _free_return;
    }


    int slot_id;
    FXhciTransCode cc = FXhciCmdEnableSlot(xhci, &slot_id);
    if (cc == FXHCI_CC_NO_SLOTS_AVAILABLE)
    {
        FXhciReapSlots(xhci, 0);
        cc = FXhciCmdEnableSlot(xhci, &slot_id);
    }

    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_INFO("Enable slot failed: %d.", cc);
        goto _free_return;
    }
    else
    {
        FUSB_INFO("Enabled slot %d.", slot_id);
    }

    di = &xhci->dev[slot_id];
    void *dma_buffer = FUSB_ALLOCATE(instance, FXHCI_NUM_EPS * ctxsize, 64);
    if (NULL == dma_buffer)
    {
        goto _disable_return;
    }

    memset(dma_buffer, 0, FXHCI_NUM_EPS * ctxsize);
    for (i = 0; i < FXHCI_NUM_EPS; i++, dma_buffer += ctxsize)
    {
        di->ctx.ep[i] = dma_buffer;
    }

    *ic->add = (1 << 0) /* Slot Context */ | (1 << 1) /* EP0 Context */;

    FXHCI_SC_SET(ROUTE, ic->dev.slot, FXhciGenRounte(xhci, hubport, hubaddr));
    FXHCI_SC_SET(SPEED1, ic->dev.slot, speed + 1);
    FXHCI_SC_SET(CTXENT, ic->dev.slot, 1); /* the endpoint 0 context */
    FXHCI_SC_SET(RHPORT, ic->dev.slot, FXhciGetRoothubPort(xhci, hubport, hubaddr));

    int tt, tt_port;
    if (FXhciGetTT(xhci, speed, hubport, hubaddr, &tt, &tt_port))
    {
        FUSB_INFO("TT for %d: %d[%d].", slot_id, tt, tt_port);
        FXHCI_SC_SET(MTT, ic->dev.slot, FXHCI_SC_GET(MTT, xhci->dev[tt].ctx.slot));
        FXHCI_SC_SET(TTID, ic->dev.slot, tt);
        FXHCI_SC_SET(TTPORT, ic->dev.slot, tt_port);
    }

    di->transfer_rings[1] = tr;
    FXhciInitCycleRing(tr, FXHCI_TRANSFER_RING_SIZE);

    ic->dev.ep0->tr_dq_low = (uintptr)(tr->ring);
    ic->dev.ep0->tr_dq_high = 0;
    FXHCI_EC_SET(TYPE, ic->dev.ep0, FXHCI_EP_CONTROL);
    FXHCI_EC_SET(AVRTRB, ic->dev.ep0, 8);
    FXHCI_EC_SET(MPS, ic->dev.ep0, FUsbSpeedtoDefaultMaxPacketSz(speed));
    FXHCI_EC_SET(CERR, ic->dev.ep0, 3);
    FXHCI_EC_SET(DCS, ic->dev.ep0, 1);

    xhci->dcbaa[slot_id] = (uintptr)(di->ctx.raw);

    FCacheDCacheInvalidateRange((uintptr)ic, sizeof(*ic)); /* flush cache of input address */

    cc = FXhciCmdAddressDevice(xhci, slot_id, ic);
    if (cc == FXHCI_CC_RESOURCE_ERROR)
    {
        FXhciReapSlots(xhci, slot_id);
        cc = FXhciCmdAddressDevice(xhci, slot_id, ic);
    }

    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_INFO("Address device failed: %d.", cc);
        goto _disable_return;
    }
    else
    {
        FUSB_INFO("Addressed device %d (USB: %d).",
                  slot_id, FXHCI_SC_GET(UADDR, di->ctx.slot));
    }

    fsleep_millisec(FUSB_SET_ADDRESS_MDELAY);

    dev = FUsbInitDevEntry(controller, slot_id);
    if (!dev)
    {
        goto _disable_return;
    }

    dev->address = slot_id;
    dev->hub = hubaddr;
    dev->port = hubport;
    dev->speed = speed;
    dev->endpoints[0].dev = dev;
    dev->endpoints[0].endpoint = 0;
    dev->endpoints[0].toggle = 0;
    dev->endpoints[0].direction = FUSB_SETUP;
    dev->endpoints[0].type = FUSB_CONTROL_EP;

    u8 buf[8];
    if (FUsbGetDescriptor(dev, FUsbGenerateReqType(FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_STANDARD, FUSB_REQ_RECP_DEV), FUSB_DESC_TYPE_DEVICE, 0, buf, sizeof(buf)) != sizeof(buf))
    {
        FUSB_INFO("First FUsbGetDescriptor(FUSB_DESC_TYPE_DEVICE) failed.");
        goto _disable_return;
    }

    dev->endpoints[0].maxpacketsize = FUsbDecodeMaxPacketSz0(speed, buf[7]);
    if (dev->endpoints[0].maxpacketsize != FUsbSpeedtoDefaultMaxPacketSz(speed))
    {
        memset((void *)ic->dev.ep0, 0x00, ctxsize);
        *ic->add = (1 << 1); /* EP0 Context */
        FXHCI_EC_SET(MPS, ic->dev.ep0, dev->endpoints[0].maxpacketsize);

        /* flush cache of input context before send command */
        FCacheDCacheInvalidateRange((uintptr)ic, sizeof(*ic));

        cc = FXhciCmdEvaluateCtx(xhci, slot_id, ic);
        if (cc == FXHCI_CC_RESOURCE_ERROR)
        {
            FXhciReapSlots(xhci, slot_id);
            cc = FXhciCmdEvaluateCtx(xhci, slot_id, ic);
        }
        if (cc != FXHCI_CC_SUCCESS)
        {
            FUSB_INFO("Context evaluation failed: %d.", cc);
            goto _disable_return;
        }
    }

    goto _free_ic_return;

_disable_return:
    FXhciCmdDisableSlot(xhci, slot_id);
    xhci->dcbaa[slot_id] = 0;
    FUsbDetachDev(controller, slot_id);
    dev = NULL;
_free_return:
    if (tr)
    {
        FUSB_FREE(instance, (void *)tr->ring);
    }
    FUSB_FREE(instance, tr);
    if (di)
    {
        FUSB_FREE(instance, di->ctx.raw);
        di->ctx.raw = 0;
    }
_free_ic_return:
    if (ic)
    {
        FUSB_FREE(instance, ic->raw);
        FUSB_FREE(instance, ic);
    }
    return dev;
}

static int FXhciFinishHubConfig(FUsbDev *const dev, FXhciInputCtx *const ic)
{
    int type = FUsbIsSuperSpeed(dev->speed) ? 0x2a : 0x29; /* similar enough */
    FUsbHubDescriptor desc;

    if (FUsbGetDescriptor(dev, FUsbGenerateReqType(FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_CLASS, FUSB_REQ_RECP_DEV), type, 0, &desc, sizeof(desc)) != sizeof(desc))
    {
        FUSB_INFO("Failed to fetch hub descriptor.");
        return FXHCI_CC_COMMUNICATION_ERROR;
    }

    FXHCI_SC_SET(HUB, ic->dev.slot, 1);
    FXHCI_SC_SET(MTT, ic->dev.slot, 0); /* No support for Multi-TT */
    FXHCI_SC_SET(NPORTS, ic->dev.slot, desc.bNbrPorts);

    if (dev->speed == FUSB_HIGH_SPEED)
        FXHCI_SC_SET(TTT, ic->dev.slot,
                     (desc.wHubCharacteristics >> 5) & 0x0003);

    return 0;
}

static size_t FXhciBoundInterval(const FUsbEndpoint *const ep)
{
    if ((ep->dev->speed == FUSB_LOW_SPEED &&
         (ep->type == FUSB_ISOCHRONOUS_EP ||
          ep->type == FUSB_INTERRUPT_EP)) ||
        (ep->dev->speed == FUSB_FULL_SPEED &&
         ep->type == FUSB_INTERRUPT_EP))
    {
        if (ep->interval < 3)
        {
            return 3;
        }
        else if (ep->interval > 11)
        {
            return 11;
        }
        else
        {
            return ep->interval;
        }
    }
    else
    {
        if (ep->interval < 0)
        {
            return 0;
        }
        else if (ep->interval > 15)
        {
            return 15;
        }
        else
        {
            return ep->interval;
        }
    }
}

static int FXhciFinishEpConfig(const FUsbEndpoint *const ep, FXhciInputCtx *const ic)
{
    FXhci *const xhci = FXHCI_INST_GET(ep->dev->controller);
    FASSERT(xhci);
    FUsb *instance = xhci->usb;
    const int ep_id = FXhciEpId(ep);
    FUSB_INFO("ep_id: %d.", ep_id);

    if (ep_id <= 1 || 32 <= ep_id)
    {
        return FXHCI_CC_DRIVER_ERROR;
    }

    FXhciTransRing *const tr = FUSB_ALLOCATE(instance, sizeof(*tr), FUSB_DEFAULT_ALIGN);
    if (NULL != tr)
    {
        FASSERT(NULL == tr->ring);
        tr->ring = FXHCI_ALIGN(xhci, 16, FXHCI_TRANSFER_RING_SIZE * sizeof(FXhciTrb));
    }

    if ((NULL == tr) || (NULL == tr->ring))
    {
        FUSB_FREE(instance, tr);
        FUSB_ERROR("Out of memory.");
        return FXHCI_CC_OUT_OF_MEMORY;
    }

    xhci->dev[ep->dev->address].transfer_rings[ep_id] = tr;
    FXhciInitCycleRing(tr, FXHCI_TRANSFER_RING_SIZE);

    *ic->add |= (1 << ep_id);
    if ((int)FXHCI_SC_GET(CTXENT, ic->dev.slot) < ep_id)
    {
        FXHCI_SC_SET(CTXENT, ic->dev.slot, ep_id);
    }

    FXhciEpCtx *const epctx = ic->dev.ep[ep_id];

    FUSB_DEBUG("Filling epctx (@%p).", epctx);
    epctx->tr_dq_low = (uintptr)(tr->ring);
    epctx->tr_dq_high = 0;

    FXHCI_EC_SET(INTVAL, epctx, FXhciBoundInterval(ep));
    FXHCI_EC_SET(CERR, epctx, 3);
    FXHCI_EC_SET(TYPE, epctx, ep->type | ((ep->direction != FUSB_OUT) << 2));
    FXHCI_EC_SET(MPS, epctx, ep->maxpacketsize);
    FXHCI_EC_SET(DCS, epctx, 1);

    size_t avrtrb;
    switch (ep->type)
    {
        case FUSB_BULK_EP:
        case FUSB_ISOCHRONOUS_EP:
            avrtrb = 3 * 1024;
            break;
        case FUSB_INTERRUPT_EP:
            avrtrb = 1024;
            break;
        default:
            avrtrb = 8;
            break;
    }
    FXHCI_EC_SET(AVRTRB, epctx, avrtrb);
    FXHCI_EC_SET(MXESIT, epctx, FXHCI_EC_GET(MPS, epctx) * FXHCI_EC_GET(MBS, epctx));

    return 0;
}

/**
 * @name: FXhciFinishDevConfig
 * @msg: 完成USB设备配置
 * @return {FXhciTransCode} 传输返回码
 * @param {FUsbDev} *dev, USB设备实例
 */
FXhciTransCode FXhciFinishDevConfig(FUsbDev *const dev)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    FUsb *instance = xhci->usb;
    int slot_id = dev->address;
    FXhciDevInfo *const di = &xhci->dev[slot_id];

    int i;
    FXhciTransCode ret = FXHCI_CC_ZERO_BYTES;

    FXhciInputCtx *const ic = FXhciMakeInputCtx(xhci, FXhciGetCtxSize(&xhci->mmio));
    if (!ic)
    {
        FUSB_INFO("Out of memory.");
        return FXHCI_CC_OUT_OF_MEMORY;
    }

    *ic->add = (1 << 0); /* Slot Context */

    ic->dev.slot->f1 = di->ctx.slot->f1;
    ic->dev.slot->f2 = di->ctx.slot->f2;
    ic->dev.slot->f3 = di->ctx.slot->f3;
    /* f4 *must* be 0 in the Input Context... yeah, it's weird, I know. */

    FCacheDCacheInvalidateRange((uintptr)ic, sizeof(*ic));

    if (dev->descriptor->bDeviceClass == FUSB_HUB_DEVICE)
    {
        ret = FXhciFinishHubConfig(dev, ic);
        if (ret)
        {
            goto _free_return;
        }
    }

    for (i = 1; i < dev->num_endp; ++i)
    {
        ret = FXhciFinishEpConfig(&dev->endpoints[i], ic);
        if (ret)
        {
            goto _free_ep_ctx_return;
        }
    }

    const int config_id = dev->configuration->bConfigurationValue;
    FUSB_INFO("config_id: %d ", config_id);
    FXhciTransCode cc = FXhciCmdConfigureEp(xhci, slot_id, config_id, ic);

    if (cc == FXHCI_CC_RESOURCE_ERROR || cc == FXHCI_CC_BANDWIDTH_ERROR)
    {
        FXhciReapSlots(xhci, slot_id);
        cc = FXhciCmdConfigureEp(xhci, slot_id, config_id, ic);
    }

    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_INFO("Configure endpoint failed: %d.", cc);
        ret = FXHCI_CC_CONTROLLER_ERROR;
        goto _free_ep_ctx_return;
    }
    else
    {
        FUSB_INFO("Endpoints configured.");
    }

    goto _free_return;

_free_ep_ctx_return:
    for (i = 2; i < 31; ++i)
    {
        if (di->transfer_rings[i])
        {
            FUSB_FREE(instance, (void *)di->transfer_rings[i]->ring);
            FUSB_FREE(instance, di->transfer_rings[i]);
        }
        di->transfer_rings[i] = NULL;
    }
_free_return:
    if (NULL != ic)
    {
        FUSB_FREE(instance, ic->raw);
        FUSB_FREE(instance, ic);
    }
    return ret;
}

/**
 * @name: FXhciDestoryDev
 * @msg: 删除指定USB设备实例
 * @return {*}
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {int} slot_id, USB设备所在的slot号
 */
void FXhciDestoryDev(FUsbHc *const controller, const int slot_id)
{
    FXhci *const xhci = FXHCI_INST_GET(controller);
    FASSERT(xhci);
    FUsb *instance = xhci->usb;

    if (slot_id <= 0 || slot_id > xhci->max_slots_en)
    {
        return;
    }

    FXhciInputCtx *const ic = FXhciMakeInputCtx(xhci, FXhciGetCtxSize(&xhci->mmio));
    if (NULL == ic)
    {
        FUSB_WARN("Out of memory, leaking resources! ");
        return;
    }

    const int num_eps = controller->devices[slot_id]->num_endp;
    *ic->add = 0;                    /* Leave Slot/EP0 state as it is for now. */
    *ic->drop = (1 << num_eps) - 1;  /* Drop all endpoints we can. */
    *ic->drop &= ~(1 << 1 | 1 << 0); /* Not allowed to drop EP0 or Slot. */

    FCacheDCacheInvalidateRange((uintptr)ic, sizeof(*ic));

    FXhciTransCode cc = FXhciCmdEvaluateCtx(xhci, slot_id, ic);

    if (NULL != ic)
    {
        FUSB_FREE(instance, ic->raw);
        FUSB_FREE(instance, ic);
    }

    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_INFO("Failed to quiesce slot %d: %d.", slot_id, cc);
    }

    cc = FXhciCmdStopEp(xhci, slot_id, FXHCI_EP0_ID);
    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_INFO("Failed to stop EP0 on slot %d: %d.", slot_id, cc);
    }

    int i;
    FXhciDevInfo *const di = &xhci->dev[slot_id];
    for (i = 1; i < /*num_eps*/FXHCI_NUM_EPS; ++i)
    {
        if (di->transfer_rings[i])
        {
            FUSB_FREE(instance, (void *)di->transfer_rings[i]->ring);
            FUSB_FREE(instance, (void *)di->transfer_rings[i]);
        }
        FUSB_FREE(instance, di->interrupt_queues[i]);
    }

    /* free device context */
    if (NULL != di->ctx.raw)
    {
        FUSB_FREE(instance, di->ctx.raw);
        di->ctx.raw = NULL;
    }

    FUSB_INFO("Stopped slot %d, but not disabling it yet.", slot_id);
    di->transfer_rings[1] = NULL;

    return;
}
