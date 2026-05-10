#include "vo_display_remap.h"

#include <rtthread.h>

#include <string.h>

#define VO_REG_BASE_PHYS        0x09084000UL
#define VO_REG_SIZE             0x00010000UL
#define DSI_REG_BASE_PHYS       0x09085000UL
#define DSI_REG_SIZE            0x00001000UL
#define SYSCTL_REG_BASE_PHYS    0x91101000UL
#define DSI_PHY_REG_BASE_PHYS   0x09085400UL
#define CLOCK_REG_BASE_PHYS     0x91100000UL
#define TIMESTAMP_REG_BASE_PHYS 0x91108000UL
#define AUX_REG_SIZE            0x00001000UL

struct vo_display_remap *display_remap;

static struct vo_display_remap g_display_remap;
static int g_remap_ready;

extern void *rt_ioremap(unsigned long phys_addr, unsigned long size);
extern void *rt_ioremap_nocache(unsigned long phys_addr, unsigned long size);
extern void rt_iounmap(void *addr);

static void unmap_if_present(void **addr)
{
    if (addr != RT_NULL && *addr != RT_NULL)
    {
        rt_iounmap(*addr);
        *addr = RT_NULL;
    }
}

void vo_display_remap_deinit(void)
{
    if (!g_remap_ready)
    {
        return;
    }

    unmap_if_present(&g_display_remap.timestamp_base);
    unmap_if_present(&g_display_remap.clock_base);
    unmap_if_present(&g_display_remap.phy_base);
    unmap_if_present(&g_display_remap.sysctl_base);
    unmap_if_present(&g_display_remap.dsi_base);
    unmap_if_present(&g_display_remap.vo_base);

    memset(&g_display_remap, 0, sizeof(g_display_remap));
    display_remap = RT_NULL;
    g_remap_ready = 0;
}

int vo_display_remap_init(void)
{
    if (g_remap_ready)
    {
        return 0;
    }

    memset(&g_display_remap, 0, sizeof(g_display_remap));

    g_display_remap.vo_base = rt_ioremap_nocache(VO_REG_BASE_PHYS, VO_REG_SIZE);
    g_display_remap.dsi_base = rt_ioremap_nocache(DSI_REG_BASE_PHYS, DSI_REG_SIZE);
    g_display_remap.sysctl_base = rt_ioremap(SYSCTL_REG_BASE_PHYS, AUX_REG_SIZE);
    g_display_remap.phy_base = rt_ioremap(DSI_PHY_REG_BASE_PHYS, AUX_REG_SIZE);
    g_display_remap.clock_base = rt_ioremap(CLOCK_REG_BASE_PHYS, AUX_REG_SIZE);
    g_display_remap.timestamp_base = rt_ioremap(TIMESTAMP_REG_BASE_PHYS, AUX_REG_SIZE);

    if (g_display_remap.vo_base == RT_NULL ||
        g_display_remap.dsi_base == RT_NULL ||
        g_display_remap.sysctl_base == RT_NULL ||
        g_display_remap.phy_base == RT_NULL ||
        g_display_remap.clock_base == RT_NULL ||
        g_display_remap.timestamp_base == RT_NULL)
    {
        rt_kprintf("vo_remap: failed to map display registers\n");
        vo_display_remap_deinit();
        return -1;
    }

    display_remap = &g_display_remap;
    g_remap_ready = 1;
    return 0;
}
