#include "bflb_gpio.h"
#include "hardware/gpio_reg.h"

void bflb_gpio_init(struct bflb_device_s *dev, uint8_t pin, uint32_t cfgset)
{
    uint32_t cfg = 0;
    uint32_t reg_base;
    uint32_t cfg_address;
    uint8_t drive;
    uint8_t function;
    uint16_t mode;

    reg_base = dev->reg_base;

    function = (cfgset & GPIO_FUNC_MASK) >> GPIO_FUNC_SHIFT;
    mode = (cfgset & GPIO_MODE_MASK);
    drive = (cfgset & GPIO_DRV_MASK) >> GPIO_DRV_SHIFT;

#if defined(BL616)
    /* disable muxed to be xtal32k */
    if (pin == GPIO_PIN_16) {
        *(volatile uint32_t *)(0x2000f000 + 0x38) &= ~(1 << 20);
    } else if (pin == GPIO_PIN_17) {
        *(volatile uint32_t *)(0x2000f000 + 0x38) &= ~(1 << 21);
    }
#endif

#if defined(BL702) || defined(BL602) || defined(BL702L)
    uint32_t regval;
    uint8_t is_odd = 0;

    regval = getreg32(reg_base + GLB_GPIO_CFGCTL34_OFFSET + ((pin >> 5) << 2));
    regval &= ~(1 << (pin & 0x1f));
    putreg32(regval, reg_base + GLB_GPIO_CFGCTL34_OFFSET + ((pin >> 5) << 2));

    is_odd = (pin % 2);

    cfg_address = reg_base + GLB_GPIO_CFGCTL0_OFFSET + (pin / 2 * 4);
    cfg = getreg32(cfg_address);
    cfg &= ~(0xffff << (16 * is_odd));

    regval = getreg32(reg_base + GLB_GPIO_CFGCTL34_OFFSET + ((pin >> 5) << 2));
    if (mode == GPIO_INPUT) {
        cfg |= (1 << (is_odd * 16 + 0));
        regval &= ~(1 << (pin & 0x1f));
        function = 11;
    } else if (mode == GPIO_OUTPUT) {
        regval |= (1 << (pin & 0x1f));
        function = 11;
#if defined(BL702L)
        if (function == 22) {
            regval &= ~(1 << (pin & 0x1f));
        }
#endif
    } else if (mode == GPIO_ANALOG) {
        regval &= ~(1 << (pin & 0x1f));
        function = 10;
    } else if (mode == GPIO_ALTERNATE) {
        cfg |= (1 << (is_odd * 16 + 0));
#if defined(BL702L)
        if (function == 22) {
            cfg &= ~(1 << (is_odd * 16 + 0));
        }
#endif
        regval &= ~(1 << (pin & 0x1f));
    } else {
    }
    putreg32(regval, reg_base + GLB_GPIO_CFGCTL34_OFFSET + ((pin >> 5) << 2));

    if (cfgset & GPIO_PULLUP) {
        cfg |= (1 << (is_odd * 16 + 4));
    } else if (cfgset & GPIO_PULLDOWN) {
        cfg |= (1 << (is_odd * 16 + 5));
    } else {
    }

    if (cfgset & GPIO_SMT_EN) {
        cfg |= (1 << (is_odd * 16 + 1));
    }

    cfg |= (drive << (is_odd * 16 + 2));
    cfg |= (function << (is_odd * 16 + 8));
#if defined(BL702L)
    /* configure output mode:set and clr mode */
    if ((function != 22) || (function != 21)) {
        cfg |= (1 << (is_odd * 16 + 15));
    }
#endif
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    cfg_address = reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2);
    cfg = 0;
    cfg |= GLB_REG_GPIO_0_INT_MASK;

    if (mode == GPIO_INPUT) {
        cfg |= GLB_REG_GPIO_0_IE;
        function = 11;
    } else if (mode == GPIO_OUTPUT) {
        cfg |= GLB_REG_GPIO_0_OE;
        function = 11;
    } else if (mode == GPIO_ANALOG) {
        function = 10;
    } else if (mode == GPIO_ALTERNATE) {
        cfg |= GLB_REG_GPIO_0_IE;
    } else {
    }

    if (cfgset & GPIO_PULLUP) {
        cfg |= GLB_REG_GPIO_0_PU;
    } else if (cfgset & GPIO_PULLDOWN) {
        cfg |= GLB_REG_GPIO_0_PD;
    } else {
    }

    if (cfgset & GPIO_SMT_EN) {
        cfg |= GLB_REG_GPIO_0_SMT;
    }

    cfg |= (drive << GLB_REG_GPIO_0_DRV_SHIFT);
    cfg |= (function << GLB_REG_GPIO_0_FUNC_SEL_SHIFT);

    /* configure output mode:set and clr mode */
    cfg |= 0x1 << GLB_REG_GPIO_0_MODE_SHIFT;
#endif
    putreg32(cfg, cfg_address);
}

void bflb_gpio_deinit(struct bflb_device_s *dev, uint8_t pin)
{
    bflb_gpio_init(dev, pin, GPIO_INPUT | GPIO_FLOAT);
}

void bflb_gpio_set(struct bflb_device_s *dev, uint8_t pin)
{
#if defined(BL702) || defined(BL602)
    uint32_t regval = getreg32(dev->reg_base + GLB_GPIO_CFGCTL32_OFFSET);
    putreg32(regval | 1 << (pin & 0x1f), dev->reg_base + GLB_GPIO_CFGCTL32_OFFSET);
#elif defined(BL702L)
    uint32_t regval = getreg32(dev->reg_base + GLB_GPIO_CFGCTL35_OFFSET);
    putreg32(regval | 1 << (pin & 0x1f), dev->reg_base + GLB_GPIO_CFGCTL35_OFFSET);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    putreg32(1 << (pin & 0x1f), dev->reg_base + GLB_GPIO_CFG138_OFFSET + ((pin >> 5) << 2));
#endif
}

void bflb_gpio_reset(struct bflb_device_s *dev, uint8_t pin)
{
#if defined(BL702) || defined(BL602)
    uint32_t regval = getreg32(dev->reg_base + GLB_GPIO_CFGCTL32_OFFSET);
    putreg32(regval & ~(1 << (pin & 0x1f)), dev->reg_base + GLB_GPIO_CFGCTL32_OFFSET);
#elif defined(BL702L)
    uint32_t regval = getreg32(dev->reg_base + GLB_GPIO_CFGCTL36_OFFSET);
    putreg32(regval & ~(1 << (pin & 0x1f)), dev->reg_base + GLB_GPIO_CFGCTL36_OFFSET);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    putreg32(1 << (pin & 0x1f), dev->reg_base + GLB_GPIO_CFG140_OFFSET + ((pin >> 5) << 2));
#endif
}

bool bflb_gpio_read(struct bflb_device_s *dev, uint8_t pin)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    return (getreg32(dev->reg_base + GLB_GPIO_CFGCTL30_OFFSET) & (1 << pin));
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    return (getreg32(dev->reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2)) & GLB_REG_GPIO_0_I);
#endif
}

void bflb_gpio_pin0_31_write(struct bflb_device_s *dev, uint32_t val)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg32(val, dev->reg_base + GLB_GPIO_CFGCTL32_OFFSET);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    putreg32(val, dev->reg_base + GLB_GPIO_CFG136_OFFSET);
#endif
}

void bflb_gpio_pin32_63_write(struct bflb_device_s *dev, uint32_t val)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg32(val, dev->reg_base + GLB_GPIO_CFGCTL33_OFFSET);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    putreg32(val, dev->reg_base + GLB_GPIO_CFG137_OFFSET);
#endif
}

uint32_t bflb_gpio_pin0_31_read(struct bflb_device_s *dev)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    return (getreg32(dev->reg_base + GLB_GPIO_CFGCTL30_OFFSET));
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    return (getreg32(dev->reg_base + GLB_GPIO_CFG128_OFFSET));
#endif
}

uint32_t bflb_gpio_pin32_63_read(struct bflb_device_s *dev)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    return (getreg32(dev->reg_base + GLB_GPIO_CFGCTL31_OFFSET));
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    return (getreg32(dev->reg_base + GLB_GPIO_CFG129_OFFSET));
#endif
}

void bflb_gpio_int_init(struct bflb_device_s *dev, uint8_t pin, uint8_t trig_mode)
{
    uint32_t reg_base;
    uint32_t cfg_address;
    uint32_t regval;

    reg_base = dev->reg_base;

    bflb_gpio_init(dev, pin, GPIO_INPUT | GPIO_FLOAT);

    bflb_gpio_int_mask(dev, pin, true);
    bflb_gpio_int_clear(dev, pin);

#if defined(BL702) || defined(BL602)
    cfg_address = reg_base + GLB_GPIO_INT_MODE_SET1_OFFSET + ((pin / 10) << 2);
    regval = getreg32(cfg_address);
    regval &= ~(0x07 << ((pin % 10) * 3));
    regval |= (trig_mode << ((pin % 10) * 3));
#elif defined(BL702L)
    cfg_address = reg_base + GLB_GPIO_INT_MODE_SET1_OFFSET + ((pin / 8) << 2);
    regval = getreg32(cfg_address);
    regval &= ~(0x0f << ((pin % 8) * 4));
    regval |= (trig_mode << ((pin % 8) * 4));
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    cfg_address = reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2);
    regval = getreg32(cfg_address);
    regval &= ~GLB_REG_GPIO_0_INT_MODE_SET_MASK;
    regval |= (trig_mode << GLB_REG_GPIO_0_INT_MODE_SET_SHIFT);
#endif
    putreg32(regval, cfg_address);
}

void bflb_gpio_int_mask(struct bflb_device_s *dev, uint8_t pin, bool mask)
{
    uint32_t reg_base;
    uint32_t cfg_address;
    uint32_t regval;

    reg_base = dev->reg_base;
#if defined(BL702) || defined(BL602) || defined(BL702L)
    cfg_address = reg_base + GLB_GPIO_INT_MASK1_OFFSET;

    regval = getreg32(cfg_address);
    if (mask) {
        regval |= (1 << pin);
    } else {
        regval &= ~(1 << pin);
    }
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    cfg_address = reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2);

    regval = getreg32(cfg_address);
    if (mask) {
        regval |= GLB_REG_GPIO_0_INT_MASK;
    } else {
        regval &= ~GLB_REG_GPIO_0_INT_MASK;
    }
#endif
    putreg32(regval, cfg_address);
}

bool bflb_gpio_get_intstatus(struct bflb_device_s *dev, uint8_t pin)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    return (getreg32(dev->reg_base + GLB_GPIO_INT_STAT1_OFFSET) & (1 << pin));
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    return (getreg32(dev->reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2)) & GLB_GPIO_0_INT_STAT);
#endif
}

void bflb_gpio_int_clear(struct bflb_device_s *dev, uint8_t pin)
{
    uint32_t reg_base;
    uint32_t cfg_address;
    uint32_t regval;

    reg_base = dev->reg_base;
#if defined(BL702) || defined(BL602) || defined(BL702L)
    cfg_address = reg_base + GLB_GPIO_INT_CLR1_OFFSET;

    regval = getreg32(cfg_address);
    regval |= (1 << pin);
    putreg32(regval, cfg_address);
    regval &= ~(1 << pin);
    putreg32(regval, cfg_address);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
    cfg_address = reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2);

    regval = getreg32(cfg_address);
    regval |= GLB_REG_GPIO_0_INT_CLR;
    putreg32(regval, cfg_address);
    regval &= ~GLB_REG_GPIO_0_INT_CLR;
    putreg32(regval, cfg_address);
#endif
}

void bflb_gpio_uart_init(struct bflb_device_s *dev, uint8_t pin, uint8_t uart_func)
{
    uint32_t reg_base;
    uint32_t regval;
    uint8_t sig;
    uint8_t sig_pos;

    reg_base = dev->reg_base;
#if defined(BL702) || defined(BL602)
#define GLB_UART_SIG_SEL_0_OFFSET (0xC0)
    regval = getreg32(reg_base + GLB_UART_SIG_SEL_0_OFFSET);

    sig = pin % 8;
    sig_pos = sig << 2;

    regval &= (~(0x0f << sig_pos));
    regval |= (uart_func << sig_pos);

    for (uint8_t i = 0; i < 8; i++) {
        /* reset other sigs which are the same with uart_func */
        sig_pos = i << 2;
        if (((regval & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
            regval &= (~(0x0f << sig_pos));
            regval |= (0x0f << sig_pos);
        }
    }

    putreg32(regval, reg_base + GLB_UART_SIG_SEL_0_OFFSET);
#elif defined(BL702L)
#define GLB_UART_SIG_SEL_0_OFFSET (0xC0)
    regval = getreg32(reg_base + GLB_UART_SIG_SEL_0_OFFSET);

    sig = pin % 4;
    sig_pos = sig << 2;

    regval &= (~(0x0f << sig_pos));
    regval |= (uart_func << sig_pos);

    for (uint8_t i = 0; i < 4; i++) {
        /* reset other sigs which are the same with uart_func */
        sig_pos = i << 2;
        if (((regval & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
            regval &= (~(0x0f << sig_pos));
            regval |= (0x0f << sig_pos);
        }
    }

    putreg32(regval, reg_base + GLB_UART_SIG_SEL_0_OFFSET);
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
#define GLB_UART_CFG1_OFFSET (0x154)
#define GLB_UART_CFG2_OFFSET (0x158)
    uint32_t regval2;
    sig = pin % 12;

    if (sig < 8) {
        sig_pos = sig << 2;

        regval = getreg32(reg_base + GLB_UART_CFG1_OFFSET);
        regval &= (~(0x0f << sig_pos));
        regval |= (uart_func << sig_pos);

        for (uint8_t i = 0; i < 8; i++) {
            /* reset other sigs which are the same with uart_func */
            sig_pos = i << 2;
            if (((regval & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
                regval &= (~(0x0f << sig_pos));
                regval |= (0x0f << sig_pos);
            }
        }
        regval2 = getreg32(reg_base + GLB_UART_CFG2_OFFSET);

        for (uint8_t i = 8; i < 12; i++) {
            /* reset other sigs which are the same with uart_func */
            sig_pos = (i - 8) << 2;
            if (((regval2 & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
                regval2 &= (~(0x0f << sig_pos));
                regval2 |= (0x0f << sig_pos);
            }
        }
        putreg32(regval, reg_base + GLB_UART_CFG1_OFFSET);
        putreg32(regval2, reg_base + GLB_UART_CFG2_OFFSET);
    } else {
        sig_pos = (sig - 8) << 2;

        regval = getreg32(reg_base + GLB_UART_CFG2_OFFSET);
        regval &= (~(0x0f << sig_pos));
        regval |= (uart_func << sig_pos);

        for (uint8_t i = 8; i < 12; i++) {
            /* reset other sigs which are the same with uart_func */
            sig_pos = (i - 8) << 2;
            if (((regval & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
                regval &= (~(0x0f << sig_pos));
                regval |= (0x0f << sig_pos);
            }
        }
        regval2 = getreg32(reg_base + GLB_UART_CFG1_OFFSET);

        for (uint8_t i = 0; i < 8; i++) {
            /* reset other sigs which are the same with uart_func */
            sig_pos = i << 2;
            if (((regval2 & (0x0f << sig_pos)) == (uart_func << sig_pos)) && (i != sig) && (uart_func != 0x0f)) {
                regval2 &= (~(0x0f << sig_pos));
                regval2 |= (0x0f << sig_pos);
            }
        }
        putreg32(regval, reg_base + GLB_UART_CFG2_OFFSET);
        putreg32(regval2, reg_base + GLB_UART_CFG1_OFFSET);
    }
#endif
    bflb_gpio_init(dev, pin, (7 << GPIO_FUNC_SHIFT) | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
}

int bflb_gpio_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;
    uint8_t pin = arg;

    reg_base = dev->reg_base;
    switch (cmd) {
        case GPIO_CMD_GET_GPIO_FUN:
#if defined(BL702) || defined(BL602) || defined(BL702L)
            if ((pin % 2)) {
                regval = getreg32(reg_base + GLB_GPIO_CFGCTL0_OFFSET + (pin / 2 * 4)) & GLB_REG_GPIO_0_FUNC_SEL_MASK;
                regval >>= GLB_REG_GPIO_0_FUNC_SEL_SHIFT;
            } else {
                regval = getreg32(reg_base + GLB_GPIO_CFGCTL0_OFFSET + (pin / 2 * 4)) & GLB_REG_GPIO_1_FUNC_SEL_MASK;
                regval >>= GLB_REG_GPIO_1_FUNC_SEL_SHIFT;
            }
#elif defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
            regval = getreg32(reg_base + GLB_GPIO_CFG0_OFFSET + (pin << 2)) & GLB_REG_GPIO_0_FUNC_SEL_MASK;
            regval >>= GLB_REG_GPIO_0_FUNC_SEL_SHIFT;
#endif
            return regval;
        default:
            ret = -EPERM;
            break;
    }
    return ret;
}