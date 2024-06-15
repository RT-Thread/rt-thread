
/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_panel.h"
#include "hpm_clock_drv.h"

extern hpm_panel_t panel_tm070rdh13;
extern hpm_panel_t panel_cc10128007;
extern hpm_panel_t panel_mc10128007_31b;
extern hpm_panel_t panel_tm103xdgp01;

static hpm_panel_t *panel_list[] = {
#if defined(CONFIG_PANEL_RGB_TM070RDH13) && CONFIG_PANEL_RGB_TM070RDH13
    &panel_tm070rdh13,
#endif

#if defined(CONFIG_PANEL_LVDS_CC10128007) && CONFIG_PANEL_LVDS_CC10128007
    &panel_cc10128007,
#endif

#if defined(CONFIG_PANEL_MIPI_MC10128007_31B) && CONFIG_PANEL_MIPI_MC10128007_31B
    &panel_mc10128007_31b,
#endif

#if defined(CONFIG_PANEL_LVDS_TM103XDGP01) && CONFIG_PANEL_LVDS_TM103XDGP01
    &panel_tm103xdgp01,
#endif
};

hpm_panel_t *hpm_panel_find_device_default(void)
{
    if (sizeof(panel_list) > 0)
        return panel_list[0];
    return NULL;
}

hpm_panel_t *hpm_panel_find_device(const char *name)
{
    int n = sizeof(panel_list) / sizeof(panel_list[0]);

    for (int i = 0; i < n; i++)
        if (!strcmp(panel_list[i]->name, name))
            return panel_list[i];

    return NULL;
}

const char *hpm_panel_get_name(hpm_panel_t *panel)
{
    return panel->name;
}

const hpm_panel_timing_t *hpm_panel_get_timing(hpm_panel_t *panel)
{
    return &panel->timing;
}

hpm_panel_if_type_t hpm_panel_get_if_type(hpm_panel_t *panel)
{
    return panel->if_type;
}

void hpm_panel_register_interface(hpm_panel_t *panel, hpm_panel_hw_interface_t *hw_if)
{
    if (hw_if)
        memcpy(&panel->hw_if, hw_if, sizeof(*hw_if));
}

void hpm_panel_reset(hpm_panel_t *panel)
{
    if (panel->funcs.reset)
        panel->funcs.reset(panel);
}

void hpm_panel_init(hpm_panel_t *panel)
{
    if (panel->funcs.init)
        panel->funcs.init(panel);
}

void hpm_panel_power_on(hpm_panel_t *panel)
{
    if (panel->funcs.power_on)
        panel->funcs.power_on(panel);
}

void hpm_panel_power_off(hpm_panel_t *panel)
{
    if (panel->funcs.power_off)
        panel->funcs.power_off(panel);
}

void hpm_panel_set_backlight(hpm_panel_t *panel, uint16_t percent)
{
    if (percent > 100)
        percent = 100;

    if (panel->hw_if.set_backlight &&
        panel->state.backlight_percent != percent) {
        panel->hw_if.set_backlight(percent);
        panel->state.backlight_percent = percent;
    }
}

uint8_t hpm_panel_get_backlight(hpm_panel_t *panel)
{
    return panel->state.backlight_percent;
}

void hpm_panel_delay_ms(uint32_t ms)
{
    clock_cpu_delay_ms(ms);
}

void hpm_panel_delay_us(uint32_t us)
{
    clock_cpu_delay_us(us);
}