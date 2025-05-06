/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-11     Rbb666       the first version
 */
#include <hal_data.h>
#include <rtthread.h>

#define RTL_8211F_PAGE_SELECT 0x1F
#define RTL_8211F_EEELCR_ADDR 0x11
#define RTL_8211F_LED_PAGE 0xD04
#define RTL_8211F_LCR_ADDR 0x10

static int phy_rtl8211f_led_fixup(ether_phy_instance_ctrl_t *phydev)
{
    uint32_t val1, val2 = 0;

    /* switch to led page */
    R_ETHER_PHY_Write(phydev, RTL_8211F_PAGE_SELECT, RTL_8211F_LED_PAGE);

    /* set led1(green) Link 10/100/1000M, and set led2(yellow) Link 10/100/1000M+Active */
    R_ETHER_PHY_Read(phydev, RTL_8211F_LCR_ADDR, &val1);
    val1 |= (1 << 5);
    val1 |= (1 << 8);
    val1 &= (~(1 << 9));
    val1 |= (1 << 10);
    val1 |= (1 << 11);
    R_ETHER_PHY_Write(phydev, RTL_8211F_LCR_ADDR, val1);

    /* set led1(green) EEE LED function disabled so it can keep on when linked */
    R_ETHER_PHY_Read(phydev, RTL_8211F_EEELCR_ADDR, &val2);
    val2 &= (~(1 << 2));
    R_ETHER_PHY_Write(phydev, RTL_8211F_EEELCR_ADDR, val2);

    /* switch back to page0 */
    R_ETHER_PHY_Write(phydev, RTL_8211F_PAGE_SELECT, 0xa42);

    return 0;
}

void ether_phy_targets_initialize_rtl8211_rgmii(ether_phy_instance_ctrl_t *p_instance_ctrl)
{
    rt_thread_mdelay(100);
    phy_rtl8211f_led_fixup(p_instance_ctrl);
}
