/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rtservice.h>

#define DBG_TAG "fw.qemu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>

#include "fw_cfg.h"

/* arch-specific ctrl & data register offsets are not available in ACPI, DT */
#if !(defined(FW_CFG_CTRL_OFF) && defined(FW_CFG_DATA_OFF))
# if (defined(ARCH_ARM) || defined(ARCH_ARMV8) || defined(ARCH_LOONGARCH) || defined(ARCH_RISCV))
#  define FW_CFG_CTRL_OFF 0x08
#  define FW_CFG_DATA_OFF 0x00
#  define FW_CFG_DMA_OFF 0x10
# elif defined(ARCH_PARISC) /* parisc */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x04
# elif (defined(ARCH_PPC) || defined(ARCH_SPARC32))     /* ppc/mac,sun4m */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x02
# elif (defined(ARCH_IA32) || defined(ARCH_SPARC64))    /* x86, sun4u */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x01
#  define FW_CFG_DMA_OFF 0x04
# else
#  error "QEMU FW_CFG not available on this architecture!"
# endif
#endif

struct fw_cfg_device
{
    struct rt_device parent;

    rt_uint32_t size;
    rt_uint16_t select;
    char name[FW_CFG_MAX_FILE_PATH];
};
#define raw_to_fw_cfg_device(raw) rt_container_of(raw, struct fw_cfg_device, parent)

static void *_fw_cfg_dev_base;
static void *_fw_cfg_reg_ctrl;
static void *_fw_cfg_reg_data;
static void *_fw_cfg_reg_dma;
static rt_bool_t _fw_cfg_is_mmio;
static rt_uint32_t _fw_cfg_rev = 0;

static RT_DEFINE_SPINLOCK(_fw_cfg_dev_lock);

static void fw_cfg_sel_endianness(rt_uint16_t key)
{
    if (_fw_cfg_is_mmio)
    {
        HWREG16(_fw_cfg_reg_ctrl) = rt_cpu_to_be16(key);
    }
    else
    {
        HWREG16(_fw_cfg_reg_ctrl) = key;
    }
}

static rt_base_t fw_cfg_read_blob(rt_uint16_t key, void *buf, rt_off_t pos, rt_size_t count)
{
    rt_uint8_t tmp;

    rt_spin_lock(&_fw_cfg_dev_lock);
    fw_cfg_sel_endianness(key);

    while (pos-- > 0)
    {
        tmp = HWREG8(_fw_cfg_reg_data);
    }

    if (count)
    {
        int loop = count;
        rt_uint8_t *buffer = buf;

        do {
            tmp = HWREG8(_fw_cfg_reg_data);
            *buffer++ = tmp;
        } while (--loop);
    }

    rt_spin_unlock(&_fw_cfg_dev_lock);

    return count;
}

rt_inline rt_bool_t fw_cfg_dma_enabled(void)
{
    return (_fw_cfg_rev & FW_CFG_VERSION_DMA) && _fw_cfg_reg_dma;
}

/* qemu fw_cfg device is sync today, but spec says it may become async */
rt_inline void fw_cfg_wait_for_control(struct fw_cfg_dma_access *dma)
{
    for (;;)
    {
        rt_uint32_t ctrl = rt_be32_to_cpu(HWREG32(&dma->control));

        /* Do not reorder the read to dma->control */
        rt_hw_rmb();

        if ((ctrl & ~FW_CFG_DMA_CTL_ERROR) == 0)
        {
            break;
        }

        rt_hw_cpu_relax();
    }
}

rt_inline rt_base_t fw_cfg_dma_transfer(void *address, rt_uint32_t length, rt_uint32_t control)
{
    rt_ubase_t dma_pa;
    rt_base_t res = length;
    struct fw_cfg_dma_access dma =
    {
        .address = rt_cpu_to_be64((rt_uint64_t)(address ? rt_kmem_v2p(address) : 0)),
        .length = rt_cpu_to_be32(length),
        .control = rt_cpu_to_be32(control),
    };

    dma_pa = (rt_ubase_t)rt_kmem_v2p(&dma);

    HWREG32(_fw_cfg_reg_dma) = rt_cpu_to_be32((rt_uint64_t)dma_pa >> 32);
    /* Force memory to sync before notifying device via MMIO */
    rt_hw_wmb();
    HWREG32(_fw_cfg_reg_dma + 4) = rt_cpu_to_be32(dma_pa);

    fw_cfg_wait_for_control(&dma);

    if ((rt_be32_to_cpu(HWREG32(&dma.control)) & FW_CFG_DMA_CTL_ERROR))
    {
        res = -RT_EIO;
    }

    return res;
}

rt_inline rt_base_t fw_cfg_write_blob(rt_uint16_t key, void *buf, rt_off_t pos, rt_size_t count)
{
    rt_base_t res = count;

    rt_spin_lock(&_fw_cfg_dev_lock);

    if (pos == 0)
    {
        res = fw_cfg_dma_transfer(buf, count, key << 16 | FW_CFG_DMA_CTL_SELECT | FW_CFG_DMA_CTL_WRITE);
    }
    else
    {
        fw_cfg_sel_endianness(key);
        res = fw_cfg_dma_transfer(RT_NULL, pos, FW_CFG_DMA_CTL_SKIP);

        if (res >= 0)
        {
            res = fw_cfg_dma_transfer(buf, count, FW_CFG_DMA_CTL_WRITE);
        }
    }

    rt_spin_unlock(&_fw_cfg_dev_lock);

    return res;
}

#ifdef RT_GRAPHIC_FB
struct ramfb_device
{
    struct rt_graphic_device parent;

    const struct fw_cfg_file *file;
};

extern void platform_get_ramfb_params(rt_uint32_t *width, rt_uint32_t *height);

static rt_uint32_t ramfb_formats[] =
{
#define fourcc_code(a, b, c, d) \
    ((rt_uint32_t)(a) |         \
    ((rt_uint32_t)(b) << 8) |   \
    ((rt_uint32_t)(c) << 16) |  \
    ((rt_uint32_t)(d) << 24))

    fourcc_code('A', 'R', '2', '4'),
    fourcc_code('A', 'B', '2', '4'),
    fourcc_code('R', 'G', '2', '4'),
};

static rt_uint32_t ramfb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
};

static rt_err_t ramfb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    void *framebuffer;
    rt_size_t framebuffer_size;
    rt_uint32_t stride, format, bpp;
    struct fw_cfg_ram_fb ram_fb;
    struct ramfb_device *ramfb = rt_container_of(plane->graphic, struct ramfb_device, parent);

    bpp = rt_graphic_mode_bpp(mode);
    stride = RT_ALIGN(rect->width * (bpp / 8), sizeof(rt_uint32_t));
    framebuffer_size = rect->height * stride;
    framebuffer = rt_malloc_align(framebuffer_size, ARCH_PAGE_SIZE);

    if (!framebuffer)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(ramfb_modes); ++i)
    {
        if (mode == ramfb_modes[i])
        {
            format = ramfb_formats[i];
            break;
        }
    }

    ram_fb.addr   = rt_cpu_to_be64((rt_ubase_t)rt_kmem_v2p(framebuffer));
    ram_fb.fourcc = rt_cpu_to_be32(format);
    ram_fb.flags  = rt_cpu_to_be32(0);
    ram_fb.width  = rt_cpu_to_be32(rect->width);
    ram_fb.height = rt_cpu_to_be32(rect->height);
    ram_fb.stride = rt_cpu_to_be32(stride);

    if (fw_cfg_write_blob(rt_be16_to_cpu(ramfb->file->select),
            &ram_fb, 0, sizeof(struct fw_cfg_ram_fb)) < 0)
    {
        rt_free_align(framebuffer);
        return -RT_ERROR;
    }

    if (plane->framebuffer)
    {
        rt_free_align(plane->framebuffer);
    }

    plane->bits_per_pixel = bpp;
    plane->line_length = stride;

    plane->framebuffer = framebuffer;
    plane->screen_len = framebuffer_size;
    plane->framebuffer_len = framebuffer_size;

    return RT_EOK;
}

const struct rt_graphic_plane_ops ramfb_plane_ops =
{
    .fb_remap = ramfb_plane_fb_remap,
};

static rt_err_t fw_cfg_setup_ramfb(const struct fw_cfg_file *file)
{
    rt_err_t err;
    rt_uint32_t width, height;
    struct ramfb_device *ramfb = rt_calloc(1, sizeof(*ramfb));

    if (!ramfb)
    {
        return -RT_ENOMEM;
    }

    ramfb->file = file;
    platform_get_ramfb_params(&width, &height);

    if ((err = rt_graphic_device_simple_register(&ramfb->parent,
            width, height, 0, &ramfb_plane_ops,
            ramfb_modes, RT_ARRAY_SIZE(ramfb_modes))))
    {
        rt_free(ramfb);
    }

    return err;
}
#endif /* RT_GRAPHIC_FB */

static rt_ssize_t fw_cfg_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    struct fw_cfg_device *fw = raw_to_fw_cfg_device(dev);

    if (pos <= fw->size)
    {
        if (size > fw->size - pos)
        {
            size = fw->size - pos;
        }

        res = fw_cfg_read_blob(fw->select, buffer, pos, size);
    }
    else
    {
        res = 0;
    }

    return res;
}

static struct rt_device_ops fw_cfg_ops =
{
    .read = fw_cfg_read,
};

static const char * const fw_export[] =
{
    "etc/acpi/rsdp", "acpi_rsdp",
    "etc/acpi/tables", "acpi_tables",
};

static rt_err_t fw_cfg_register_file(const struct fw_cfg_file *file)
{
    rt_err_t err;
    const char *name = RT_NULL;
    struct fw_cfg_device *fw;

#ifdef RT_GRAPHIC_FB
    if (fw_cfg_dma_enabled() && !rt_strcmp(file->name, FW_CFG_RAMFB_FILENAME))
    {
        if (fw_cfg_setup_ramfb(file) < 0)
        {
            LOG_W("failed to setup ramfb");
        }

        return RT_EOK;
    }
#endif /* RT_GRAPHIC_FB */

    for (int i = 0; i < RT_ARRAY_SIZE(fw_export); i += 2)
    {
        if (!rt_strcmp(fw_export[i], file->name))
        {
            name = fw_export[i + 1];
            break;
        }
    }

    if (!name)
    {
        return RT_EOK;
    }

    if (!(fw = rt_malloc(sizeof(*fw))))
    {
        return -RT_ENOMEM;
    }

    fw->size = rt_be32_to_cpu(file->size);
    fw->select = rt_be16_to_cpu(file->select);
    rt_strncpy(fw->name, file->name, FW_CFG_MAX_FILE_PATH);

    fw->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    fw->parent.ops = &fw_cfg_ops;
#else
    fw->parent.read = fw_cfg_read,
#endif

    if ((err = rt_device_register(&fw->parent, name, RT_DEVICE_FLAG_RDONLY)))
    {
        rt_free(fw);
        return err;
    }

    return RT_EOK;
}

static rt_err_t fw_cfg_register_dir_entries(void)
{
    rt_err_t err = 0;
    rt_uint32_t count;
    rt_size_t dir_size;
    rt_be32_t files_count;
    struct fw_cfg_file *dir;

    err = fw_cfg_read_blob(FW_CFG_FILE_DIR, &files_count, 0, sizeof(files_count));

    if (err < 0)
    {
        return err;
    }

    count = rt_be32_to_cpu(files_count);
    dir_size = count * sizeof(struct fw_cfg_file);

    dir = rt_malloc(dir_size);

    if (!dir)
    {
        return -RT_ENOMEM;
    }

    err = fw_cfg_read_blob(FW_CFG_FILE_DIR, dir, sizeof(files_count), dir_size);

    if (err < 0)
    {
        return err;
    }

    for (int i = 0; i < count; ++i)
    {
        if ((err = fw_cfg_register_file(&dir[i])))
        {
            break;
        }
    }

    rt_free(dir);

    return err;
}

static rt_err_t qemu_fw_cfg_probe(struct rt_platform_device *pdev)
{
    rt_le32_t rev;
    rt_err_t err = RT_EOK;
    char sig[FW_CFG_SIG_SIZE];
    rt_uint32_t ctrl = FW_CFG_CTRL_OFF, data = FW_CFG_DATA_OFF, dma;
    struct rt_device *dev = &pdev->parent;

#ifdef FW_CFG_DMA_OFF
    dma = FW_CFG_DMA_OFF;
#else
    dma = RT_UINT32_MAX;
#endif

    rt_dm_dev_prop_read_u32(dev, "ctrl", &ctrl);
    rt_dm_dev_prop_read_u32(dev, "data", &data);
    rt_dm_dev_prop_read_u32(dev, "dma", &dma);

    if (!(_fw_cfg_dev_base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

#ifdef ARCH_SUPPORT_PIO
    _fw_cfg_is_mmio = RT_FALSE;
#else
    _fw_cfg_is_mmio = RT_TRUE;
#endif

    _fw_cfg_reg_ctrl = _fw_cfg_dev_base + ctrl;
    _fw_cfg_reg_data = _fw_cfg_dev_base + data;

    if (dma != RT_UINT32_MAX)
    {
        _fw_cfg_reg_dma = _fw_cfg_dev_base + dma;
    }
    else
    {
        _fw_cfg_reg_dma = RT_NULL;
    }

    if (fw_cfg_read_blob(FW_CFG_SIGNATURE, sig, 0, FW_CFG_SIG_SIZE) < 0 ||
        rt_memcmp(sig, "QEMU", FW_CFG_SIG_SIZE))
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    if (fw_cfg_read_blob(FW_CFG_ID, &rev, 0, sizeof(rev)) < 0)
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    _fw_cfg_rev = rt_le32_to_cpu(rev);

    fw_cfg_register_dir_entries();

_fail:
    return err;
}

static const struct rt_ofw_node_id qemu_fw_cfg_ofw_ids[] =
{
    { .compatible = "qemu,fw-cfg-mmio", },
    { /* sentinel */ }
};

static struct rt_platform_driver qemu_fw_cfg_driver =
{
    .name = "qemu-fw-cfg",
    .ids = qemu_fw_cfg_ofw_ids,

    .probe = qemu_fw_cfg_probe,
};

static int qemu_fw_cfg_drv_register(void)
{
    rt_platform_driver_register(&qemu_fw_cfg_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(qemu_fw_cfg_drv_register);
