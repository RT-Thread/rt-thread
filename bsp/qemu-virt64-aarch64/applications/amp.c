/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dt-bindings/size.h>

#include <cpu.h>
#include <mmu.h>
#include <psci.h>
#include <stdlib.h>
#include <posix/stdio.h>

#ifdef RT_USING_RPMSG
static int rpmsg_write(int argc, char**argv)
{
    struct rt_device *dev;

    if (argc != 3 || !(dev = rt_device_find(argv[1])))
    {
        rt_kprintf("Usage: %s <device> <message>\n", __func__);
        return -1;
    }

    if (!rt_device_open(dev, 0))
    {
        rt_device_write(dev, 0, argv[2], rt_strlen(argv[2]) + 1);
        rt_device_close(dev);
    }
    else
    {
        rt_kprintf("Open %s fail", argv[1]);
        return -1;
    }

    return 0;
}
MSH_CMD_EXPORT(rpmsg_write, rpmsg write msg to device);

static int rpmsg_read(int argc, char**argv)
{
    struct rt_device *dev;

    if (argc != 2 || !(dev = rt_device_find(argv[1])))
    {
        rt_kprintf("Usage: %s <device>\n", __func__);
        return -1;
    }

    if (!rt_device_open(dev, 0))
    {
        char msg[32];
        rt_ssize_t len;

        while ((len = rt_device_read(dev, 0, msg, sizeof(msg) - 1)) > 0)
        {
            msg[len] = '\0';
            rt_kputs(msg);
        }
        rt_kputs("\n");

        rt_device_close(dev);
    }
    else
    {
        rt_kprintf("Open %s fail", argv[1]);
        return -1;
    }

    return 0;
}
MSH_CMD_EXPORT(rpmsg_read, rpmsg read all msg from device);

static int rpmsg_startup(void)
{
    struct rt_rpmsg_endpoint_info info;
    struct rt_device *dev = rt_device_find("rpmsg_char0");

    if (dev && !rt_device_open(dev, 0))
    {
        rt_strcpy(info.name, "rpmsg-char");
        info.src = 114;
        info.dst = 514;
        if (rt_rpmsg_mode() == RT_RPMSG_MODE_SLAVE)
        {
            info.src ^= info.dst;
            info.dst ^= info.src;
            info.src ^= info.dst;
        }
        rt_device_control(dev, RT_DEVICE_CTRL_RPMSG_CREATE_EPT, &info);

        rt_device_close(dev);
    }

    return 0;
}
INIT_APP_EXPORT(rpmsg_startup);
#endif /* RT_USING_RPMSG */

struct compare
{
    struct rt_device *udev;
    struct rt_device *vdev;
};

static int virtio_device_compare(rt_device_t dev, void *data)
{
    struct compare *cmp = data;

    if (dev->user_data == (cmp->udev->user_data ? : cmp->udev))
    {
        cmp->vdev = dev;

        return RT_EOK;
    }

    return -RT_EEMPTY;
}

static void join_virtio(void *amp_dtb, struct rt_bus *virtio_bus,
        const char *dev_name, const char *path)
{
    int dev_offset;
    rt_ssize_t len;
    const void *data;
    struct compare cmp;
    struct rt_device *dev;
    struct rt_ofw_node *np;

    if (!(dev = rt_device_find(dev_name)))
    {
        return;
    }

    cmp.udev = dev;
    cmp.vdev = RT_NULL;

    rt_bus_for_each_dev(virtio_bus, &cmp, virtio_device_compare);

    if (!cmp.vdev)
    {
        return;
    }
    np = cmp.vdev->ofw_node;
    dev_offset = fdt_path_offset(amp_dtb, path);

    data = rt_ofw_prop_read_raw(np, "reg", &len);
    fdt_setprop(amp_dtb, dev_offset, "reg", data, len);

    data = rt_ofw_prop_read_raw(np, "interrupts", &len);
    fdt_setprop(amp_dtb, dev_offset, "interrupts", data, len);

    fdt_setprop_cstring(amp_dtb, dev_offset, "status", "okay");

    rt_bus_remove_device(cmp.vdev);
}

static void join_cpu(void *amp_dtb, struct rt_ofw_node *cpu_np)
{
    int cpu_offset;
    const char *string = RT_NULL;

    rt_ofw_prop_read_string(cpu_np, "compatible", &string);

    fdt_open_into(amp_dtb, amp_dtb, fdt_totalsize(amp_dtb) + FDT_PADDING_SIZE);
    cpu_offset = fdt_path_offset(amp_dtb, "/cpus/cpu@" RT_STRINGIFY(RT_CPUS_NR));
    fdt_setprop_string(amp_dtb, cpu_offset, "compatible", string);
}

static rt_bool_t match_cpu_hwid(int cpu, rt_uint64_t hwid)
{
    return cpu == hwid;
}

static int amp_startup(void)
{
    rt_ubase_t level;
    void *amp_kernel, *amp_dtb;
    rt_uint32_t dtb_entry, amp_entry;
    static rt_bool_t startup = RT_FALSE;
    struct rt_bus *virtio_bus;
    struct rt_ofw_node *amp_soc, *amp_mem, *amp_cpu;

    if (startup || rt_ofw_bootargs_select("amp_mode", 0))
    {
        return -1;
    }

    startup = RT_TRUE;

    if (!(amp_soc = rt_ofw_find_node_by_path("/amp_soc")))
    {
        rt_kprintf("No AMP SoC node found\n");
    }

    /* Build DTB */
    rt_ofw_prop_read_u32(amp_soc, "dtb-entry", &dtb_entry);
    amp_dtb = rt_ioremap_cached((void *)(rt_ubase_t)dtb_entry, ARCH_PAGE_SIZE);

    if (!amp_dtb)
    {
        return (int)-RT_ENOMEM;
    }

    if (!(amp_mem = rt_ofw_parse_phandle(amp_soc, "memory-region", 0)))
    {
        rt_iounmap(amp_dtb);
        return (int)-RT_EINVAL;
    }

    virtio_bus = rt_bus_find_by_name("virtio");
    RT_ASSERT(virtio_bus != RT_NULL);

    join_virtio(amp_dtb, virtio_bus, "vdb", "/virtio_blk");

    /* Ready to start the AMP OS */
    rt_ofw_prop_read_u32(amp_soc, "kernel-entry", &amp_entry);

    /*
     * Add ARM64 load DTB code (MOV <Wd>, #<imm>):
     *  sf      [31]:    0b1
     *  opc     [30-29]: 0b10
     *  code    [28-23]: 0b100101
     *  hw      [22-21]: 0b01 (MOVZ X0, #<dtb_entry >> 16>, LSL #16)
     *  imm16   [20-5]:  dtb_entry >> 16
     *  Rd      [4-0]:   0 (x0)
     */
    amp_entry -= sizeof(rt_uint32_t);
    amp_kernel = rt_ioremap_cached((void *)(rt_ubase_t)amp_entry, ARCH_PAGE_SIZE);

    if (!amp_kernel)
    {
        rt_iounmap(amp_dtb);
        return (int)-RT_ENOMEM;
    }
    *(rt_uint32_t *)amp_kernel = RT_BIT(31);
    *(rt_uint32_t *)amp_kernel |= 0x2 << 29;
    *(rt_uint32_t *)amp_kernel |= 0x25 << 23;
    *(rt_uint32_t *)amp_kernel |= 0x1 << 21;
    *(rt_uint32_t *)amp_kernel |= (dtb_entry >> 16) << 5;
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, amp_kernel, sizeof(rt_uint32_t));

    rt_iounmap(amp_kernel);

    level = rt_hw_interrupt_disable();
    /*
     * This is a hack, rt_cpu_mpidr_table array size is RT_CPUS_NR + 1,
     * We can call PSCI_CPU_ON for the last one,
     * We just restore it to zero after the PSCI called.
     */
    amp_cpu = rt_ofw_get_cpu_node(RT_CPUS_NR, RT_NULL, &match_cpu_hwid);
    join_cpu(amp_dtb, amp_cpu);
    rt_cpu_mpidr_table[RT_CPUS_NR] = rt_ofw_get_cpu_hwid(amp_cpu, 0);
    rt_psci_cpu_on(RT_CPUS_NR, amp_entry);
    rt_hw_rmb();

    rt_cpu_mpidr_table[RT_CPUS_NR] = 0;
    rt_hw_wmb();

    rt_hw_interrupt_enable(level);

    rt_iounmap(amp_dtb);

    return 0;
}
#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
MSH_CMD_EXPORT(amp_startup, AMP system startup);
#else
INIT_APP_EXPORT(amp_startup);
#endif
