#include "kd_vo_reg.h"
#include "vo_display_remap.h"

#include <rtthread.h>

#include <stddef.h>
#include <stdint.h>

#define KD_VO_MODULE_ID             11

#define VO_REG_RESET               0x004
#define VO_REG_ENABLE              0x004
#define VO_REG_WRAP_CTRL0          0x008
#define VO_REG_WRAP_CTRL1          0x00c
#define VO_REG_WRAP_CTRL2          0x010
#define VO_REG_MIX_ORDER0          0x034
#define VO_REG_MIX_ORDER1          0x038
#define VO_REG_MIX_ORDER2          0x03c
#define VO_REG_MIX_ORDER3          0x040
#define VO_REG_MIX_ORDER4          0x044
#define VO_REG_MIX_ORDER5          0x048
#define VO_REG_MIX_ORDER6          0x04c
#define VO_REG_MIX_ORDER7          0x050
#define VO_REG_HSYNC               0x100
#define VO_REG_HSYNC1              0x104
#define VO_REG_VSYNC1              0x108
#define VO_REG_HSYNC2              0x10c
#define VO_REG_VSYNC2              0x110
#define VO_REG_LAYER_CFG_EXTRA     0x118
#define VO_REG_ACTIVE_H            0x0c0
#define VO_REG_ACTIVE_V            0x0c4
#define VO_REG_TOTAL_SIZE          0x11c
#define VO_REG_BG_COLOR            0x3d0
#define VO_REG_MIX_ENABLE          0x3c0
#define VO_REG_MIX_ALPHA0          0x3c4
#define VO_REG_MIX_ALPHA1          0x3c8
#define VO_REG_MIX_PRIORITY0       0x3cc
#define VO_REG_MIX_PRIORITY1       0x950
#define VO_REG_LAYER_ENABLE        0x380
#define VO_REG_LOAD_CTL            0x004
#define VO_REG_INTR_FRAME          0x3e0
#define VO_REG_INTR_VTTH           0x3e4
#define VO_REG_INTR_CLEAR0         0x3d4
#define VO_REG_INTR_CLEAR1         0x3d8
#define VO_REG_INTR_MASK0          0x3e8
#define VO_REG_USER_SYNC           0x780

#define VO_MIX_ENABLE_SDK          0x000000ffU

#define VO_OSD_COUNT               4U
#define VO_OSD_INFO                0x00
#define VO_OSD_SIZE                0x04
#define VO_OSD_VLU_ADDR0           0x08
#define VO_OSD_ALP_ADDR0           0x0c
#define VO_OSD_VLU_ADDR1           0x10
#define VO_OSD_ALP_ADDR1           0x14
#define VO_OSD_DMA_CTRL            0x18
#define VO_OSD_STRIDE              0x1c
#define VO_OSD_ADDR_SEL_MODE       0x20

#define VO_OSD_FORMAT_RGB565       0x02

struct vo_osd_plane {
    k_u32 offset;
    k_u32 enable_bit;
    k_u32 xctl;
    k_u32 yctl;
};

static const struct vo_osd_plane vo_osd_planes[VO_OSD_COUNT] = {
    {0x280, 4,  0x0e8, 0x0ec},
    {0x2c0, 5,  0x0f0, 0x0f4},
    {0x300, 6,  0x0f8, 0x0fc},
    {0x850, 7,  0x820, 0x824},
};

#define VO_SYS_RESET_OFFSET        0x090
#define VO_PIXCLK_REG_OFFSET       0x078
#define VO_TIMESTAMP_CTRL_OFFSET   0x000
#define VO_TIMESTAMP_TIME_HI       0x070
#define VO_TIMESTAMP_TIME_LO       0x074
#define VO_TIMESTAMP_PTP_HI        0x078
#define VO_TIMESTAMP_PTP_LO        0x07c

#if defined(__riscv)
#define VO_FENCE_WO() __asm__ volatile("fence w,o" ::: "memory")
#define VO_FENCE_IR() __asm__ volatile("fence i,r" ::: "memory")
#else
#define VO_FENCE_WO() __asm__ volatile("" ::: "memory")
#define VO_FENCE_IR() __asm__ volatile("" ::: "memory")
#endif

extern void K_LOG(int level, int module, const char *fmt, ...);
extern void dwc_dsi_disable(void);

static inline void __raw_writel(k_u32 value, volatile void *addr)
{
    *(volatile k_u32 *)addr = value;
}

static inline k_u32 __raw_readl(const volatile void *addr)
{
    return *(const volatile k_u32 *)addr;
}

static inline uintptr_t vo_base_addr(void)
{
    if (display_remap == RT_NULL || display_remap->vo_base == RT_NULL)
    {
        (void)vo_display_remap_init();
    }
    return (uintptr_t)display_remap->vo_base;
}

static inline uintptr_t clock_base_addr(void)
{
    if (display_remap == RT_NULL || display_remap->clock_base == RT_NULL)
    {
        (void)vo_display_remap_init();
    }
    return (uintptr_t)display_remap->clock_base;
}

static inline uintptr_t sysctl_base_addr(void)
{
    if (display_remap == RT_NULL || display_remap->sysctl_base == RT_NULL)
    {
        (void)vo_display_remap_init();
    }
    return (uintptr_t)display_remap->sysctl_base;
}

static inline uintptr_t timestamp_base_addr(void)
{
    if (display_remap == RT_NULL || display_remap->timestamp_base == RT_NULL)
    {
        (void)vo_display_remap_init();
    }
    return (uintptr_t)display_remap->timestamp_base;
}

static void vo_write(k_u32 value, k_u32 offset)
{
    K_LOG(7, KD_VO_MODULE_ID,
          "[Func]:%s [Line]:%d [Info]:VO write: offset 0x%x, val 0x%x\n",
          __func__, 61, offset, value);
    VO_FENCE_WO();
    __raw_writel(value, (void *)(vo_base_addr() + offset));
}

static k_u32 vo_read(k_u32 offset)
{
    k_u32 value;

    value = __raw_readl((void *)(vo_base_addr() + offset));
    VO_FENCE_IR();

    return value;
}

void kd_vo_set_pixclk(k_u32 div)
{
    uintptr_t addr = clock_base_addr() + VO_PIXCLK_REG_OFFSET;
    k_u32 val;

    val = __raw_readl((void *)addr);
    VO_FENCE_IR();
    val &= ~0x7f8U;
    val |= div << 3;
    val |= 0x80000000U;
    VO_FENCE_WO();
    __raw_writel(val, (void *)addr);
}

void kd_vo_wrap_init(void)
{
    unsigned int i;

    vo_write(0x00000011U, VO_REG_WRAP_CTRL0);
    vo_write(0x00000088U, VO_REG_WRAP_CTRL1);
    vo_write(0x00000000U, VO_REG_WRAP_CTRL2);

    for (i = 0; i <= 7; ++i) {
        vo_write(0x01010101U, (i + 5U) * 4U);
    }

    vo_write(0x76543210U, VO_REG_MIX_ORDER0);
    vo_write(0x76543210U, VO_REG_MIX_ORDER2);
    vo_write(0x76543210U, VO_REG_MIX_ORDER4);
    vo_write(0x76543210U, VO_REG_MIX_ORDER6);
    vo_write(0xfedcba98U, VO_REG_MIX_ORDER1);
    vo_write(0xfedcba98U, VO_REG_MIX_ORDER3);
    vo_write(0xfedcba98U, VO_REG_MIX_ORDER5);
    vo_write(0xfedcba98U, VO_REG_MIX_ORDER7);

    for (i = 0; i <= 9; ++i) {
        vo_write(0x00000701U, (i + 32U) * 4U);
    }

    vo_write(0x00000701U, 0x800U);
    vo_write(0x00000701U, 0x804U);
    vo_write(0x00000701U, 0x808U);
    vo_write(0x00000701U, 0x80cU);
    vo_write(0x00000701U, 0x810U);
    vo_write(0x00000000U, VO_REG_LAYER_CFG_EXTRA);
}

static void kd_vo_software_reset(void)
{
    vo_write(0x0000000fU, VO_REG_RESET);
    vo_write(0x00000000U, VO_REG_WRAP_CTRL0);
    vo_write(0x00000000U, VO_REG_ENABLE);
}

void kd_vo_reset(void)
{
    uintptr_t reset_addr;

    (void)vo_display_remap_init();
    reset_addr = sysctl_base_addr() + VO_SYS_RESET_OFFSET;

    VO_FENCE_WO();
    __raw_writel(0, (void *)reset_addr);
    rt_thread_mdelay(1);

    VO_FENCE_WO();
    __raw_writel(0xffffffffU, (void *)reset_addr);
    rt_thread_mdelay(1);

    dwc_dsi_disable();
    kd_vo_software_reset();
    rt_thread_mdelay(3);
}

void kd_vo_timestamp_enable(void)
{
    uintptr_t addr = timestamp_base_addr() + VO_TIMESTAMP_CTRL_OFFSET;
    k_u32 val;

    val = __raw_readl((void *)addr);
    VO_FENCE_IR();

    if ((val & 0x1U) == 0) {
        val &= ~0x18U;
        val |= 0x8U;
        val |= 0x1U;
        VO_FENCE_WO();
        __raw_writel(val, (void *)addr);
    }
}

void k230_get_timestamp(k_u32 *ptp_time, k_u32 *time)
{
    uintptr_t base = timestamp_base_addr();
    k_u32 val;

    val = __raw_readl((void *)(base + VO_TIMESTAMP_TIME_HI));
    VO_FENCE_IR();
    time[1] = val;

    val = __raw_readl((void *)(base + VO_TIMESTAMP_TIME_LO));
    VO_FENCE_IR();
    time[0] = val;

    val = __raw_readl((void *)(base + VO_TIMESTAMP_PTP_HI));
    VO_FENCE_IR();
    ptp_time[1] = val;

    val = __raw_readl((void *)(base + VO_TIMESTAMP_PTP_LO));
    VO_FENCE_IR();
    ptp_time[0] = val;
}

void kd_vo_enable(void)
{
    vo_write(0x00000011U, VO_REG_ENABLE);
    kd_vo_timestamp_enable();
}

void kd_vo_set_config_mix(void)
{
    vo_write(0x0000007fU, VO_REG_MIX_ENABLE);
    vo_write(0xffffffffU, VO_REG_MIX_ALPHA0);
    vo_write(0xffffffffU, VO_REG_MIX_ALPHA1);
    vo_write(0xffffffffU, 0x940U);
    vo_write(0x00003210U, VO_REG_MIX_PRIORITY0);
    vo_write(0xba987654U, VO_REG_MIX_PRIORITY1);
    vo_write(0x00000001U, VO_REG_LAYER_ENABLE);
    vo_write(0x00000000U, VO_REG_INTR_CLEAR1);
    vo_write(0x00000001U, VO_REG_INTR_CLEAR0);
    vo_write(0x11111111U, 0x340U);
    vo_write(0x000000ffU, VO_REG_MIX_ENABLE);
    vo_write(0x00000000U, VO_REG_INTR_FRAME);
    vo_write(0x00000000U, VO_REG_INTR_VTTH);
    vo_write(0x00000000U, VO_REG_INTR_MASK0);
}

static void kd_vo_set_sync_pair(k_u32 low, k_u32 high, k_u32 offset)
{
    k_u32 val = (low & 0xffffU) | (high << 16);

    vo_write(val, offset);
}

static void kd_vo_set_hsync(k_u32 low, k_u32 high)
{
    kd_vo_set_sync_pair(low, high, VO_REG_HSYNC);
}

static void kd_vo_set_hsync1(k_u32 low, k_u32 high)
{
    kd_vo_set_sync_pair(low, high, VO_REG_HSYNC1);
}

static void kd_vo_set_hsync2(k_u32 low, k_u32 high)
{
    kd_vo_set_sync_pair(low, high, VO_REG_HSYNC2);
}

static void kd_vo_set_vsync1(k_u32 low, k_u32 high)
{
    kd_vo_set_sync_pair(low, high, VO_REG_VSYNC1);
}

static void kd_vo_set_vsync2(k_u32 low, k_u32 high)
{
    kd_vo_set_sync_pair(low, high, VO_REG_VSYNC2);
}

void kd_vo_set_background(k_u32 rgb888)
{
    k_u32 r = (rgb888 >> 16) & 0xffU;
    k_u32 g = (rgb888 >> 8) & 0xffU;
    k_u32 b = rgb888 & 0xffU;
    k_u32 y;
    k_u32 cb;
    k_u32 cr;
    k_u32 yuv;

    y = (66U * r + 129U * g + 25U * b + 128U) >> 8;
    y += 16U;
    cb = ((-38 * (int)r - 74 * (int)g + 112 * (int)b + 128) >> 8) + 128;
    cr = ((112 * (int)r - 94 * (int)g - 18 * (int)b + 128) >> 8) + 128;

    yuv = ((cr & 0xffU) << 16) | ((cb & 0xffU) << 8) | (y & 0xffU);
    vo_write(yuv, VO_REG_BG_COLOR);
    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_set_background_yuv(k_u32 yuv)
{
    vo_write(yuv, VO_REG_BG_COLOR);
    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_set_osd_rgb565_framebuffer(k_u32 osd, k_u64 paddr, k_u32 width, k_u32 height, k_u32 pitch)
{
    kd_vo_set_osd_rgb565_framebuffer_ex(osd, paddr, paddr, width, height, pitch,
                                        0x0000007fU, 0x00000100U);
}

void kd_vo_set_osd_rgb565_framebuffer_ex(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                         k_u32 width, k_u32 height, k_u32 pitch,
                                         k_u32 dma_ctrl, k_u32 addr_sel)
{
    k_u32 stride;

    if (pitch == 0)
        return;

    /*
     * The K230 SDK passes OSD stride in 64-bit words.  For RGB565 this is
     * width * 2 / 8, which is equivalent to pitch / 8.
     */
    stride = pitch / 8U;
    kd_vo_set_osd_rgb565_framebuffer_raw(osd, paddr, alpha_paddr, width, height,
                                         stride, dma_ctrl, addr_sel);
}

void kd_vo_set_osd_rgb565_framebuffer_raw(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                          k_u32 width, k_u32 height, k_u32 stride_reg,
                                          k_u32 dma_ctrl, k_u32 addr_sel)
{
    kd_vo_set_osd_rgb565_framebuffer_format_raw(osd, paddr, alpha_paddr,
                                                width, height, stride_reg,
                                                VO_OSD_FORMAT_RGB565,
                                                dma_ctrl, addr_sel);
}

void kd_vo_set_osd_rgb565_framebuffer_format_raw(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                                 k_u32 width, k_u32 height, k_u32 stride_reg,
                                                 k_u32 info, k_u32 dma_ctrl, k_u32 addr_sel)
{
    k_u32 base;
    const struct vo_osd_plane *plane;
    k_u32 start_x;
    k_u32 start_y;
    k_u32 value;

    if (osd >= VO_OSD_COUNT || paddr == 0 || width == 0 || height == 0)
        return;

    plane = &vo_osd_planes[osd];
    base = (k_u32)paddr;
    (void)alpha_paddr;

    vo_write(info, plane->offset + VO_OSD_INFO);
    vo_write(width | (height << 16), plane->offset + VO_OSD_SIZE);

    start_x = vo_read(VO_REG_ACTIVE_H) & 0x1fffU;
    start_y = vo_read(VO_REG_ACTIVE_V) & 0x1fffU;
    vo_write(((start_x + width - 1U) << 16) | start_x, plane->xctl);
    vo_write(((start_y + height - 1U) << 16) | start_y, plane->yctl);

    vo_write(base, plane->offset + VO_OSD_VLU_ADDR0);
    vo_write(base, plane->offset + VO_OSD_VLU_ADDR1);
    vo_write(base, plane->offset + VO_OSD_ALP_ADDR0);
    vo_write(base, plane->offset + VO_OSD_ALP_ADDR1);
    vo_write(stride_reg, plane->offset + VO_OSD_STRIDE);
    vo_write(dma_ctrl, plane->offset + VO_OSD_DMA_CTRL);
    vo_write(addr_sel, plane->offset + VO_OSD_ADDR_SEL_MODE);

    value = vo_read(VO_REG_LAYER_CFG_EXTRA);
    value |= 1U << plane->enable_bit;
    vo_write(value, VO_REG_LAYER_CFG_EXTRA);

    value = vo_read(VO_REG_MIX_ENABLE);
    value |= 1U << plane->enable_bit;
    vo_write(value, VO_REG_MIX_ENABLE);

    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_disable_osd_all(void)
{
    k_u32 layer_enable;

    layer_enable = vo_read(VO_REG_LAYER_CFG_EXTRA);

    for (k_u32 i = 0; i < VO_OSD_COUNT; i++) {
        layer_enable &= ~(1U << vo_osd_planes[i].enable_bit);
    }

    vo_write(layer_enable, VO_REG_LAYER_CFG_EXTRA);
    vo_write(0x00000000U, VO_REG_MIX_ENABLE);
    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_select_osd(k_u32 osd)
{
    k_u32 layer_enable;
    k_u32 mix_enable;

    if (osd >= VO_OSD_COUNT)
        return;

    layer_enable = vo_read(VO_REG_LAYER_CFG_EXTRA);
    mix_enable = vo_read(VO_REG_MIX_ENABLE);

    for (k_u32 i = 0; i < VO_OSD_COUNT; i++) {
        layer_enable &= ~(1U << vo_osd_planes[i].enable_bit);
    }

    layer_enable |= 1U << vo_osd_planes[osd].enable_bit;
    mix_enable |= VO_MIX_ENABLE_SDK;

    vo_write(layer_enable, VO_REG_LAYER_CFG_EXTRA);
    vo_write(mix_enable, VO_REG_MIX_ENABLE);
    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_commit(void)
{
    vo_write(0x00000011U, VO_REG_LOAD_CTL);
}

void kd_vo_poke(k_u32 offset, k_u32 value)
{
    vo_write(value, offset);
}

void kd_vo_debug_dump(void)
{
    (void)vo_display_remap_init();

    rt_kprintf("VO base=%p\n", display_remap ? display_remap->vo_base : RT_NULL);
    rt_kprintf("VO load/enable=0x%08x dma_sw=0x%08x active_h=0x%08x active_v=0x%08x total=0x%08x\n",
               vo_read(VO_REG_LOAD_CTL), vo_read(VO_REG_WRAP_CTRL0),
               vo_read(VO_REG_ACTIVE_H), vo_read(VO_REG_ACTIVE_V), vo_read(VO_REG_TOTAL_SIZE));
    rt_kprintf("VO layer_en=0x%08x mix_en=0x%08x mix_alpha0=0x%08x mix_alpha1=0x%08x bg=0x%08x\n",
               vo_read(VO_REG_LAYER_CFG_EXTRA), vo_read(VO_REG_MIX_ENABLE),
               vo_read(VO_REG_MIX_ALPHA0), vo_read(VO_REG_MIX_ALPHA1), vo_read(VO_REG_BG_COLOR));
    rt_kprintf("VO pri0=0x%08x pri1=0x%08x intr_frame=0x%08x intr_vtth=0x%08x intr_mask=0x%08x\n",
               vo_read(VO_REG_MIX_PRIORITY0), vo_read(VO_REG_MIX_PRIORITY1),
               vo_read(VO_REG_INTR_FRAME), vo_read(VO_REG_INTR_VTTH), vo_read(VO_REG_INTR_MASK0));

    for (k_u32 i = 0; i < VO_OSD_COUNT; i++) {
        const struct vo_osd_plane *plane = &vo_osd_planes[i];

        rt_kprintf("OSD%u off=0x%03x bit=%u info=0x%08x size=0x%08x x=0x%08x y=0x%08x\n",
                   i, plane->offset, plane->enable_bit,
                   vo_read(plane->offset + VO_OSD_INFO),
                   vo_read(plane->offset + VO_OSD_SIZE),
                   vo_read(plane->xctl), vo_read(plane->yctl));
        rt_kprintf("OSD%u addr0=0x%08x alp0=0x%08x addr1=0x%08x alp1=0x%08x dma=0x%08x stride=0x%08x sel=0x%08x\n",
                   i,
                   vo_read(plane->offset + VO_OSD_VLU_ADDR0),
                   vo_read(plane->offset + VO_OSD_ALP_ADDR0),
                   vo_read(plane->offset + VO_OSD_VLU_ADDR1),
                   vo_read(plane->offset + VO_OSD_ALP_ADDR1),
                   vo_read(plane->offset + VO_OSD_DMA_CTRL),
                   vo_read(plane->offset + VO_OSD_STRIDE),
                   vo_read(plane->offset + VO_OSD_ADDR_SEL_MODE));
    }
}

void kd_vo_debug_summary(void)
{
    (void)vo_display_remap_init();

    rt_kprintf("VO_SUM load=0x%08x dma_sw=0x%08x layer_en=0x%08x mix_en=0x%08x alpha0=0x%08x alpha1=0x%08x bg=0x%08x\n",
               vo_read(VO_REG_LOAD_CTL), vo_read(VO_REG_WRAP_CTRL0),
               vo_read(VO_REG_LAYER_CFG_EXTRA), vo_read(VO_REG_MIX_ENABLE),
               vo_read(VO_REG_MIX_ALPHA0), vo_read(VO_REG_MIX_ALPHA1),
               vo_read(VO_REG_BG_COLOR));
    rt_kprintf("VO_SUM active_h=0x%08x active_v=0x%08x total=0x%08x pri0=0x%08x pri1=0x%08x intr=0x%08x\n",
               vo_read(VO_REG_ACTIVE_H), vo_read(VO_REG_ACTIVE_V),
               vo_read(VO_REG_TOTAL_SIZE), vo_read(VO_REG_MIX_PRIORITY0),
               vo_read(VO_REG_MIX_PRIORITY1), vo_read(VO_REG_INTR_FRAME));

    for (k_u32 i = 0; i < VO_OSD_COUNT; i++) {
        const struct vo_osd_plane *plane = &vo_osd_planes[i];
        k_u32 info = vo_read(plane->offset + VO_OSD_INFO);
        k_u32 size = vo_read(plane->offset + VO_OSD_SIZE);
        k_u32 addr = vo_read(plane->offset + VO_OSD_VLU_ADDR0);
        k_u32 stride = vo_read(plane->offset + VO_OSD_STRIDE);
        k_u32 dma = vo_read(plane->offset + VO_OSD_DMA_CTRL);
        k_u32 sel = vo_read(plane->offset + VO_OSD_ADDR_SEL_MODE);

        if (info || size || addr || (vo_read(VO_REG_LAYER_CFG_EXTRA) & (1U << plane->enable_bit))) {
            rt_kprintf("VO_SUM OSD%u bit=%u off=0x%03x info=0x%08x size=0x%08x addr=0x%08x alp=0x%08x stride=0x%08x dma=0x%08x sel=0x%08x x=0x%08x y=0x%08x\n",
                       i, plane->enable_bit, plane->offset, info, size, addr,
                       vo_read(plane->offset + VO_OSD_ALP_ADDR0), stride, dma,
                       sel, vo_read(plane->xctl), vo_read(plane->yctl));
        }
    }
}

void kd_vo_set_timing(const k_vo_timing *timing)
{
    k_u32 hactive;
    k_u32 hback_porch;
    k_u32 htotal;
    k_u32 vactive;
    k_u32 vback_porch;
    k_u32 vtotal;
    k_u32 val;

    hback_porch = timing->hback_porch;
    hactive = timing->hactive;
    htotal = hactive + hback_porch + timing->hsync_len + timing->hfront_porch;

    vback_porch = timing->vback_porch;
    vactive = timing->vactive;
    vtotal = vactive + vback_porch + timing->vsync_len + timing->vfront_porch;

    kd_vo_set_hsync(2, 5);
    kd_vo_set_hsync1(2, 5);
    kd_vo_set_hsync2(2, 5);
    kd_vo_set_vsync1(0, 0);
    kd_vo_set_vsync2(0, 0);

    val = ((hactive + hback_porch - 1U) << 16) | hback_porch;
    vo_write(val, VO_REG_ACTIVE_H);

    val = ((vactive + vback_porch - 1U) << 16) | vback_porch;
    vo_write(val, VO_REG_ACTIVE_V);

    val = (vtotal << 16) | htotal;
    vo_write(val, VO_REG_TOTAL_SIZE);

    val = ((vactive - 1U) << 16) | hactive;
    val += 0x7fffU;
    vo_write(val, VO_REG_USER_SYNC);

}

void kd_vo_set_vtth_intr(k_u32 status, k_u32 line)
{
    (void)status;
    (void)line;
    vo_write(0x00000000U, VO_REG_INTR_VTTH);
}

void kd_vo_set_frame_intr(k_bool status)
{
    k_u32 val = ((k_u32)status) << 20;

    vo_write(val, VO_REG_INTR_FRAME);
    kd_vo_set_vtth_intr(0, 0);
}
