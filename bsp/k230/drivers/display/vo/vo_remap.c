#include "vo_display_remap.h"

#include <rtthread.h>

#include "board.h"
#include "ioremap.h"

#include <string.h>

#define DSI_PHY_REG_BASE_PHYS   (DSI_BASE_ADDR + 0x400UL)
#define DSI_PHY_REG_SIZE        (DSI_IO_SIZE - 0x400UL)

struct vo_display_remap *display_remap;

static struct vo_display_remap g_display_remap;
static int g_remap_ready;

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

    g_display_remap.vo_base = rt_ioremap_nocache((void *)VO_BASE_ADDR, VO_IO_SIZE);
    g_display_remap.dsi_base = rt_ioremap_nocache((void *)DSI_BASE_ADDR, DSI_IO_SIZE);
    g_display_remap.sysctl_base = rt_ioremap((void *)RMU_BASE_ADDR, RMU_IO_SIZE);
    g_display_remap.phy_base = rt_ioremap_nocache((void *)DSI_PHY_REG_BASE_PHYS, DSI_PHY_REG_SIZE);
    g_display_remap.clock_base = rt_ioremap((void *)CMU_BASE_ADDR, CMU_IO_SIZE);
    g_display_remap.timestamp_base = rt_ioremap((void *)STC_BASE_ADDR, STC_IO_SIZE);

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
