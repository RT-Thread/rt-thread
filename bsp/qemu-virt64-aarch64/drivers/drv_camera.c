/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-07     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "vfio.camera"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drv_camera.h>

#define VFIO_CAMERA_WIDTH_BAR       0
#define VFIO_CAMERA_HEIGHT_BAR      1
#define VFIO_CAMERA_FRAMEBUFFER_BAR 2
#define VFIO_CAMERA_STATUS_BAR      3

/* Status register */
#define BAR3_FRAME_COUNT_OFFSET     0x00
#define BAR3_FRAME_READY_OFFSET     0x04

struct vfio_camera
{
    struct rt_device parent;
    void *framebuffer;
    void *status_regs;      /* BAR3: status registers */
    int width;
    int height;
    rt_uint32_t last_frame_count;
    struct rt_semaphore frame_sem;  /* Frame ready notification */
};

static rt_uint32_t vfio_camera_get_frame_count(struct vfio_camera *vc)
{
    return HWREG32(vc->status_regs + BAR3_FRAME_COUNT_OFFSET);
}

static rt_bool_t vfio_camera_wait_frame(struct vfio_camera *vc, rt_int32_t timeout_ms)
{
    rt_uint32_t current_count;
    rt_tick_t start_tick, timeout_tick;

    /* Fast path: check frame count first */
    current_count = vfio_camera_get_frame_count(vc);
    if (current_count != vc->last_frame_count)
    {
        vc->last_frame_count = current_count;
        return RT_TRUE;
    }

    start_tick = rt_tick_get();
    timeout_tick = rt_tick_from_millisecond(timeout_ms);

    /* Poll with small sleep - allow frame dropping */
    do {
        current_count = vfio_camera_get_frame_count(vc);

        if (current_count != vc->last_frame_count)
        {
            vc->last_frame_count = current_count;
            return RT_TRUE;
        }

        /* Short sleep to reduce CPU usage */
        rt_thread_mdelay(1);

        /* Check overall timeout */
        if ((rt_tick_get() - start_tick) >= timeout_tick)
        {
            /* Timeout */
            return RT_FALSE;
        }
    } while (RT_TRUE);
}

static rt_ssize_t vfio_camera_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct vfio_camera *vc = rt_container_of(dev, struct vfio_camera, parent);

    /* Wait for new frame (up to 30ms - about 1 frame at 30fps) */
    if (!vfio_camera_wait_frame(vc, 30))
    {
        return 0;
    }

    /* If buffer is NULL, just return success (frame is ready) */
    if (buffer == RT_NULL)
    {
        return 1;  /* Frame ready */
    }

    /* Direct memory access - no memcpy overhead */
    rt_memcpy(buffer, vc->framebuffer + pos, size);
    return size;
}

static rt_err_t vfio_camera_control(rt_device_t dev, int cmd, void *args)
{
    struct vfio_camera *vc = rt_container_of(dev, struct vfio_camera, parent);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CAMERA_GET_WIDTH:
        if (args)
        {
            *(int *)args = vc->width;
        }
        break;

    case RT_DEVICE_CTRL_CAMERA_GET_HEIGHT:
        if (args)
        {
            *(int *)args = vc->height;
        }
        break;

    case RT_DEVICE_CTRL_CAMERA_GET_FRAMEBUFFER:
        if (args)
        {
            *(void **)args = vc->framebuffer;
        }
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops vfio_camera_ops =
{
    .read = vfio_camera_read,
    .control = vfio_camera_control,
};
#endif

static void vfio_camera_isr(int irqno, void *args)
{
    struct vfio_camera *vc = args;

    /* Frame ready interrupt from backend */
    rt_sem_release(&vc->frame_sem);
}

static rt_err_t vfio_camera_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    void *fmt_regs;
    const char *dev_name;
    struct vfio_camera *vc = rt_calloc(1, sizeof(*vc));

    if (!vc)
    {
        LOG_E("Failed to allocate vfio_camera");
        return -RT_ENOMEM;
    }

    /* Initialize semaphore for frame notification */
    rt_sem_init(&vc->frame_sem, "cam_frm", 0, RT_IPC_FLAG_PRIO);

    fmt_regs = rt_pci_iomap(pdev, VFIO_CAMERA_WIDTH_BAR);
    if (!fmt_regs)
    {
        LOG_E("Failed to map BAR0 (width)");
        goto _fail;
    }
    vc->width = HWREG32(fmt_regs);
    rt_iounmap(fmt_regs);

    fmt_regs = rt_pci_iomap(pdev, VFIO_CAMERA_HEIGHT_BAR);
    if (!fmt_regs)
    {
        LOG_E("Failed to map BAR1 (height)");
        goto _fail;
    }
    vc->height = HWREG32(fmt_regs);
    rt_iounmap(fmt_regs);

    vc->framebuffer = rt_pci_iomap(pdev, VFIO_CAMERA_FRAMEBUFFER_BAR);
    if (!vc->framebuffer)
    {
        LOG_E("Failed to map BAR2 (framebuffer)");
        goto _fail;
    }

    vc->status_regs = rt_pci_iomap(pdev, VFIO_CAMERA_STATUS_BAR);
    if (!vc->status_regs)
    {
        LOG_E("Failed to map BAR3 (status)");
        goto _fail;
    }

    /* Initialize frame count */
    vc->last_frame_count = vfio_camera_get_frame_count(vc);

    vc->parent.type = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    vc->parent.ops = &vfio_camera_ops;
#else
    vc->parent.read = vfio_camera_read;
    vc->parent.control = vfio_camera_control;
#endif

    rt_dm_dev_set_name_auto(&vc->parent, "camera");
    dev_name = rt_dm_dev_get_name(&vc->parent);

    if ((err = rt_device_register(&vc->parent, dev_name, RT_DEVICE_FLAG_RDONLY)))
    {
        LOG_E("Failed to register device: %d", err);
        goto _fail;
    }

    rt_hw_interrupt_install(pdev->irq, vfio_camera_isr, vc, dev_name);
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_unmask(pdev);

    pdev->parent.user_data = vc;

    LOG_I("%s %ux%u %s", dev_name, vc->width, vc->height, "RGB24");

    return RT_EOK;

_fail:
    if (vc->status_regs)
    {
        rt_iounmap(vc->status_regs);
    }
    if (vc->framebuffer)
    {
        rt_iounmap(vc->framebuffer);
    }
    rt_sem_detach(&vc->frame_sem);
    rt_free(vc);

    return err;
}

static rt_err_t vfio_camera_remove(struct rt_pci_device *pdev)
{
    struct vfio_camera *vc = pdev->parent.user_data;

    /* INTx is shared, don't mask all */
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_mask(pdev);
    rt_pci_clear_master(pdev);

    rt_device_unregister(&vc->parent);

    rt_iounmap(vc->status_regs);
    rt_iounmap(vc->framebuffer);
    rt_sem_detach(&vc->frame_sem);
    rt_free(vc);

    return RT_EOK;
}

static const struct rt_pci_device_id vfio_camera_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_QEMU, 0x5678), },
    { /* sentinel */ }
};

static struct rt_pci_driver vfio_camera_driver =
{
    .name = "vfio-camera",

    .ids = vfio_camera_pci_ids,
    .probe = vfio_camera_probe,
    .remove = vfio_camera_remove,
};
RT_PCI_DRIVER_EXPORT(vfio_camera_driver);
