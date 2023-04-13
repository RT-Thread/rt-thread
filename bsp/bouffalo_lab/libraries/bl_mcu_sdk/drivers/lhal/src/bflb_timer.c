#include "bflb_timer.h"
#include "bflb_gpio.h"
#include "hardware/timer_reg.h"

void bflb_timer_init(struct bflb_device_s *dev, const struct bflb_timer_config_s *config)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    /* Disable timer */
    regval = getreg32(reg_base + TIMER_TCER_OFFSET);
    regval &= ~(1 << (dev->idx + 1));
    putreg32(regval, reg_base + TIMER_TCER_OFFSET);

    /* Timer interrupr clear */
    bflb_timer_compint_clear(dev, TIMER_COMP_ID_0);
    bflb_timer_compint_clear(dev, TIMER_COMP_ID_1);
    bflb_timer_compint_clear(dev, TIMER_COMP_ID_2);

    /* Configure clock source */
    regval = getreg32(reg_base + TIMER_TCCR_OFFSET);
    if (dev->idx == 0) {
        regval &= ~TIMER_CS_0_MASK;
        regval |= (config->clock_source << TIMER_CS_0_SHIFT);
    } else {
        regval &= ~TIMER_CS_1_MASK;
        regval |= (config->clock_source << TIMER_CS_1_SHIFT);
    }
    putreg32(regval, reg_base + TIMER_TCCR_OFFSET);

    /* Configure clock div */
    regval = getreg32(reg_base + TIMER_TCDR_OFFSET);
    regval &= ~(0xff << (TIMER_TCDR0_SHIFT + 8 * dev->idx));
    regval |= (config->clock_div << (TIMER_TCDR0_SHIFT + 8 * dev->idx));
    putreg32(regval, reg_base + TIMER_TCDR_OFFSET);

    /* Configure counter mode */
    regval = getreg32(reg_base + TIMER_TCMR_OFFSET);
    if (config->counter_mode == TIMER_COUNTER_MODE_PROLOAD) {
        regval &= ~(1 << (1 + dev->idx));
    } else {
        regval |= (1 << (1 + dev->idx));
    }
    putreg32(regval, reg_base + TIMER_TCMR_OFFSET);

    /* Configure preload trigger source */
    regval = getreg32(reg_base + TIMER_TPLCR0_OFFSET + 4 * dev->idx);
    regval &= ~TIMER_TPLCR0_MASK;
    if (config->trigger_comp_id != TIMER_COMP_NONE) {
        regval |= ((config->trigger_comp_id + 1) << TIMER_TPLCR0_SHIFT);
    }
    putreg32(regval, reg_base + TIMER_TPLCR0_OFFSET + 4 * dev->idx);

    if (config->counter_mode == TIMER_COUNTER_MODE_PROLOAD) {
        bflb_timer_set_preloadvalue(dev, config->preload_val);
    }

    if (config->trigger_comp_id < TIMER_COMP_ID_1) {
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_0, false);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_1, true);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_2, true);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_0, config->comp0_val - 2);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_1, 0xffffffff);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_2, 0xffffffff);
    } else if (config->trigger_comp_id < TIMER_COMP_ID_2) {
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_0, false);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_1, false);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_2, true);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_0, config->comp0_val - 2);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_1, config->comp1_val - 2);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_2, 0xffffffff);
    } else if (config->trigger_comp_id < TIMER_COMP_NONE) {
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_0, false);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_1, false);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_2, false);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_0, config->comp0_val - 2);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_1, config->comp1_val - 2);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_2, config->comp2_val - 2);
    } else {
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_0, true);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_1, true);
        bflb_timer_compint_mask(dev, TIMER_COMP_ID_2, true);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_0, 0xffffffff);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_1, 0xffffffff);
        bflb_timer_set_compvalue(dev, TIMER_COMP_ID_2, 0xffffffff);
    }
}

void bflb_timer_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + TIMER_TCER_OFFSET);
    regval &= ~(1 << (dev->idx + 1));
    putreg32(regval, reg_base + TIMER_TCER_OFFSET);
}

void bflb_timer_start(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + TIMER_TCER_OFFSET);
    regval |= (1 << (dev->idx + 1));
    putreg32(regval, reg_base + TIMER_TCER_OFFSET);
}

void bflb_timer_stop(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + TIMER_TCER_OFFSET);
    regval &= ~(1 << (dev->idx + 1));
    putreg32(regval, reg_base + TIMER_TCER_OFFSET);
}

void bflb_timer_set_preloadvalue(struct bflb_device_s *dev, uint32_t val)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg32(val, reg_base + TIMER_TPLVR0_OFFSET + 4 * dev->idx);
}

void bflb_timer_set_compvalue(struct bflb_device_s *dev, uint8_t cmp_no, uint32_t val)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg32(val, reg_base + TIMER_TMR0_0_OFFSET + 0x0c * dev->idx + 4 * cmp_no);
}

uint32_t bflb_timer_get_compvalue(struct bflb_device_s *dev, uint8_t cmp_no)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    return getreg32(reg_base + TIMER_TMR0_0_OFFSET + 0x0c * dev->idx + 4 * cmp_no);
}

uint32_t bflb_timer_get_countervalue(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    return getreg32(reg_base + TIMER_TCR0_OFFSET + 4 * dev->idx);
}

void bflb_timer_compint_mask(struct bflb_device_s *dev, uint8_t cmp_no, bool mask)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + TIMER_TIER0_OFFSET + 4 * dev->idx);
    if (mask) {
        regval &= ~(1 << cmp_no);
    } else {
        regval |= (1 << cmp_no);
    }
    putreg32(regval, reg_base + TIMER_TIER0_OFFSET + 4 * dev->idx);
}

bool bflb_timer_get_compint_status(struct bflb_device_s *dev, uint8_t cmp_no)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + TIMER_TSR0_OFFSET + 4 * dev->idx);

    if (regval & (1 << cmp_no)) {
        return true;
    } else {
        return false;
    }
}

void bflb_timer_compint_clear(struct bflb_device_s *dev, uint8_t cmp_no)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + TIMER_TICR0_OFFSET + 4 * dev->idx);
    regval |= (1 << cmp_no);
    putreg32(regval, reg_base + TIMER_TICR0_OFFSET + 4 * dev->idx);
}

#if !defined(BL702) && !defined(BL602)
void bflb_timer_capture_init(struct bflb_device_s *dev, const struct bflb_timer_capture_config_s *config)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
#if defined(BL702L)
    regval = getreg32(0x20000000 + 0xc);
    regval &= ~(0x3 << 14);
    switch (config->pin & 0x03) {
        case 0:
            regval &= ~(1 << 10);
            regval |= (0 << 14);
            break;
        case 1:
            regval &= ~(1 << 11);
            regval |= (1 << 14);
            break;
        case 2:
            regval &= ~(1 << 12);
            regval |= (2 << 14);
            break;
        case 3:
            regval &= ~(1 << 13);
            regval |= (3 << 14);
            break;

        default:
            break;
    }
    putreg32(regval, 0x20000000 + 0xc);
    struct bflb_device_s *gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, config->pin, (0 << GPIO_FUNC_SHIFT) | GPIO_ALTERNATE | GPIO_FLOAT | GPIO_SMT_EN | GPIO_DRV_1);
#else
    regval = getreg32(0x20000000 + 0x258);
    regval &= ~(3 << 12);
    switch (config->pin & 0x03) {
        case 0:
            regval &= ~(1 << 8);
            regval |= (0 << 12);
            break;
        case 1:
            regval &= ~(1 << 9);
            regval |= (1 << 12);
            break;
        case 2:
            regval &= ~(1 << 10);
            regval |= (2 << 12);
            break;
        case 3:
            regval &= ~(1 << 11);
            regval |= (3 << 12);
            break;

        default:
            break;
    }
    putreg32(regval, 0x20000000 + 0x258);
    struct bflb_device_s *gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, config->pin, (31 << GPIO_FUNC_SHIFT) | GPIO_ALTERNATE | GPIO_FLOAT | GPIO_SMT_EN | GPIO_DRV_1);
#endif

    regval = getreg32(reg_base + TIMER_GPIO_OFFSET);
    /* polarity: 1->neg, 0->pos */
    if (config->polarity == TIMER_CAPTURE_POLARITY_NEGATIVE) {
        regval |= (1 << (5 + dev->idx));
    } else {
        regval &= ~(1 << (5 + dev->idx));
    }
    regval |= TIMER0_GPIO_EN;
    putreg32(regval, reg_base + TIMER_GPIO_OFFSET);
}

uint32_t bflb_timer_capture_get_pulsewidth(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t lat1 = 0;
    uint32_t lat2 = 0;
    reg_base = dev->reg_base;

    do {
        lat1 = getreg32(reg_base + TIMER_GPIO_LAT1_OFFSET);
        lat2 = getreg32(reg_base + TIMER_GPIO_LAT2_OFFSET);
    } while (!(getreg32(reg_base + TIMER_GPIO_OFFSET) & TIMER_GPIO_LAT_OK) || (lat1 >= lat2));

    return (lat2 - lat1);
}
#endif
