#include "bflb_wdg.h"
#include "bflb_clock.h"
#include "hardware/timer_reg.h"

void bflb_wdg_init(struct bflb_device_s *dev, const struct bflb_wdg_config_s *config)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);

    regval = getreg32(reg_base + TIMER_WMER_OFFSET);
    regval &= ~TIMER_WE;
    if (config->mode == WDG_MODE_INTERRUPT) {
        regval &= ~TIMER_WRIE;
    } else {
        regval |= TIMER_WRIE;
    }
    putreg32(regval, reg_base + TIMER_WMER_OFFSET);

    /* Configure clock source */
    regval = getreg32(reg_base + TIMER_TCCR_OFFSET);
    regval &= ~TIMER_CS_WDT_MASK;
    regval |= (config->clock_source << TIMER_CS_WDT_SHIFT);
    putreg32(regval, reg_base + TIMER_TCCR_OFFSET);

    /* Configure clock div */
    regval = getreg32(reg_base + TIMER_TCDR_OFFSET);
    regval &= ~TIMER_WCDR_MASK;
    regval |= (config->clock_div << TIMER_WCDR_SHIFT);
    putreg32(regval, reg_base + TIMER_TCDR_OFFSET);

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);
    putreg16(config->comp_val, reg_base + TIMER_WMR_OFFSET);
}

void bflb_wdg_start(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);

    regval = getreg32(reg_base + TIMER_WMER_OFFSET);
    regval |= TIMER_WE;
    putreg32(regval, reg_base + TIMER_WMER_OFFSET);
}

void bflb_wdg_stop(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);

    regval = getreg32(reg_base + TIMER_WMER_OFFSET);
    regval &= ~TIMER_WE;
    putreg32(regval, reg_base + TIMER_WMER_OFFSET);
}

uint16_t bflb_wdg_get_countervalue(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    return getreg16(reg_base + TIMER_WVR_OFFSET);
}

void bflb_wdg_set_countervalue(struct bflb_device_s *dev, uint16_t value)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);
    putreg16(value, reg_base + TIMER_WMR_OFFSET);
}

void bflb_wdg_reset_countervalue(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);

    regval = getreg32(reg_base + TIMER_WCR_OFFSET);
    regval |= TIMER_WCR;
    putreg32(regval, reg_base + TIMER_WCR_OFFSET);
}

void bflb_wdg_compint_clear(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg16(0xBABA, reg_base + TIMER_WFAR_OFFSET);
    putreg16(0xEB10, reg_base + TIMER_WSAR_OFFSET);

    regval = getreg32(reg_base + TIMER_WICR_OFFSET);
    regval |= TIMER_WICLR;
    putreg32(regval, reg_base + TIMER_WICR_OFFSET);
}
