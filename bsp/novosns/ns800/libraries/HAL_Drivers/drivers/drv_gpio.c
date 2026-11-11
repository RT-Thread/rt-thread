/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-05-17     swtblue           add interrupt operation function
 */

#include <board.h>
#include "drv_gpio.h"
#include "gpio.h"
#include "exti.h"
#include "syscon.h"
#include "interrupt.h"
#include <ctype.h>
#include <stdlib.h>

#ifdef BSP_USING_GPIO

#define PIN_ENTRY(pin_macro) {pin_macro}
#define NS800_PIN_MAP_SIZE  (sizeof(pin_map_table) / sizeof(pin_map_table[0]))
#define NS800_EXTI_LINES    16U

#if defined(GPIOZ)
#define __NS800_PORT_MAX 12u
#elif defined(GPIOK)
#define __NS800_PORT_MAX 11u
#elif defined(GPIOJ)
#define __NS800_PORT_MAX 10u
#elif defined(GPIOI)
#define __NS800_PORT_MAX 9u
#elif defined(GPIOH)
#define __NS800_PORT_MAX 8u
#elif defined(GPIOG)
#define __NS800_PORT_MAX 7u
#elif defined(GPIOF)
#define __NS800_PORT_MAX 6u
#elif defined(GPIOE)
#define __NS800_PORT_MAX 5u
#elif defined(GPIOD)
#define __NS800_PORT_MAX 4u
#elif defined(GPIOC)
#define __NS800_PORT_MAX 3u
#elif defined(GPIOB)
#define __NS800_PORT_MAX 2u
#elif defined(GPIOA)
#define __NS800_PORT_MAX 1u
#else
#define __NS800_PORT_MAX 0u
#error Unsupported NS800 GPIO peripheral.
#endif

#define PIN_STPORT_MAX __NS800_PORT_MAX


static const rt_pin_info_t pin_map_table[225] = {
    /* 0-21: 连续 */
    [0] = PIN_ENTRY(GPIO_0),
    [1] = PIN_ENTRY(GPIO_1),
    [2] = PIN_ENTRY(GPIO_2),
    [3] = PIN_ENTRY(GPIO_3),
    [4] = PIN_ENTRY(GPIO_4),
    [5] = PIN_ENTRY(GPIO_5),
    [6] = PIN_ENTRY(GPIO_6),
    [7] = PIN_ENTRY(GPIO_7),
    [8] = PIN_ENTRY(GPIO_8),
    [9] = PIN_ENTRY(GPIO_9),
    [10] = PIN_ENTRY(GPIO_10),
    [11] = PIN_ENTRY(GPIO_11),
    [12] = PIN_ENTRY(GPIO_12),
    [13] = PIN_ENTRY(GPIO_13),
    [14] = PIN_ENTRY(GPIO_14),
    [15] = PIN_ENTRY(GPIO_15),
    [16] = PIN_ENTRY(GPIO_16),
    [17] = PIN_ENTRY(GPIO_17),
    [18] = PIN_ENTRY(GPIO_18),
    [19] = PIN_ENTRY(GPIO_19),
    [20] = PIN_ENTRY(GPIO_20),
    [21] = PIN_ENTRY(GPIO_21),

    /* 22-32: 不连续 */
    [22] = PIN_ENTRY(GPIO_22),
    [23] = PIN_ENTRY(GPIO_23),
    [24] = PIN_ENTRY(GPIO_24),
    [25] = PIN_ENTRY(GPIO_25),
    [26] = PIN_ENTRY(GPIO_26),
    [27] = PIN_ENTRY(GPIO_27),
    [28] = PIN_ENTRY(GPIO_28),
    [29] = PIN_ENTRY(GPIO_29),
    [30] = PIN_ENTRY(GPIO_30),
    [31] = PIN_ENTRY(GPIO_31),
    [32] = PIN_ENTRY(GPIO_32),

    /* 33-63: 连续 */
    [33] = PIN_ENTRY(GPIO_33),
    [34] = PIN_ENTRY(GPIO_34),
    [35] = PIN_ENTRY(GPIO_35),
    [36] = PIN_ENTRY(GPIO_36),
    [37] = PIN_ENTRY(GPIO_37),
    [38] = PIN_ENTRY(GPIO_38),
    [39] = PIN_ENTRY(GPIO_39),
    [40] = PIN_ENTRY(GPIO_40),
    [41] = PIN_ENTRY(GPIO_41),
    [42] = PIN_ENTRY(GPIO_42),
    [43] = PIN_ENTRY(GPIO_43),
    [44] = PIN_ENTRY(GPIO_44),
    [45] = PIN_ENTRY(GPIO_45),
    [46] = PIN_ENTRY(GPIO_46),
    [47] = PIN_ENTRY(GPIO_47),
    [48] = PIN_ENTRY(GPIO_48),
    [49] = PIN_ENTRY(GPIO_49),
    [50] = PIN_ENTRY(GPIO_50),
    [51] = PIN_ENTRY(GPIO_51),
    [52] = PIN_ENTRY(GPIO_52),
    [53] = PIN_ENTRY(GPIO_53),
    [54] = PIN_ENTRY(GPIO_54),
    [55] = PIN_ENTRY(GPIO_55),
    [56] = PIN_ENTRY(GPIO_56),
    [57] = PIN_ENTRY(GPIO_57),
    [58] = PIN_ENTRY(GPIO_58),
    [59] = PIN_ENTRY(GPIO_59),
    [60] = PIN_ENTRY(GPIO_60),
    [61] = PIN_ENTRY(GPIO_61),
    [62] = PIN_ENTRY(GPIO_62),
    [63] = PIN_ENTRY(GPIO_63),

    /* 64-94: 连续 */
    [64] = PIN_ENTRY(GPIO_64),
    [65] = PIN_ENTRY(GPIO_65),
    [66] = PIN_ENTRY(GPIO_66),
    [67] = PIN_ENTRY(GPIO_67),
    [68] = PIN_ENTRY(GPIO_68),
    [69] = PIN_ENTRY(GPIO_69),
    [70] = PIN_ENTRY(GPIO_70),
    [71] = PIN_ENTRY(GPIO_71),
    [72] = PIN_ENTRY(GPIO_72),
    [73] = PIN_ENTRY(GPIO_73),
    [74] = PIN_ENTRY(GPIO_74),
    [75] = PIN_ENTRY(GPIO_75),
    [76] = PIN_ENTRY(GPIO_76),
    [77] = PIN_ENTRY(GPIO_77),
    [78] = PIN_ENTRY(GPIO_78),
    [79] = PIN_ENTRY(GPIO_79),
    [80] = PIN_ENTRY(GPIO_80),
    [81] = PIN_ENTRY(GPIO_81),
    [82] = PIN_ENTRY(GPIO_82),
    [83] = PIN_ENTRY(GPIO_83),
    [84] = PIN_ENTRY(GPIO_84),
    [85] = PIN_ENTRY(GPIO_85),
    [86] = PIN_ENTRY(GPIO_86),
    [87] = PIN_ENTRY(GPIO_87),
    [88] = PIN_ENTRY(GPIO_88),
    [89] = PIN_ENTRY(GPIO_89),
    [90] = PIN_ENTRY(GPIO_90),
    [91] = PIN_ENTRY(GPIO_91),
    [92] = PIN_ENTRY(GPIO_92),
    [93] = PIN_ENTRY(GPIO_93),
    [94] = PIN_ENTRY(GPIO_94),

    /* 不连续引脚 */
    [99] = PIN_ENTRY(GPIO_99),
    [100] = PIN_ENTRY(GPIO_100),
    [103] = PIN_ENTRY(GPIO_103),
    [104] = PIN_ENTRY(GPIO_104),
    [105] = PIN_ENTRY(GPIO_105),
    [106] = PIN_ENTRY(GPIO_106),
    [133] = PIN_ENTRY(GPIO_133),
    [183] = PIN_ENTRY(GPIO_183),
    [184] = PIN_ENTRY(GPIO_184),
    [198] = PIN_ENTRY(GPIO_198),
    [199] = PIN_ENTRY(GPIO_199),
    [200] = PIN_ENTRY(GPIO_200),
    [201] = PIN_ENTRY(GPIO_201),
    [202] = PIN_ENTRY(GPIO_202),
    [203] = PIN_ENTRY(GPIO_203),
    [204] = PIN_ENTRY(GPIO_204),
    [205] = PIN_ENTRY(GPIO_205),
    [206] = PIN_ENTRY(GPIO_206),
    [207] = PIN_ENTRY(GPIO_207),
    [208] = PIN_ENTRY(GPIO_208),
    [209] = PIN_ENTRY(GPIO_209),
    [210] = PIN_ENTRY(GPIO_210),
    [211] = PIN_ENTRY(GPIO_211),
    [212] = PIN_ENTRY(GPIO_212),
    [213] = PIN_ENTRY(GPIO_213),
    [214] = PIN_ENTRY(GPIO_214),
    [215] = PIN_ENTRY(GPIO_215),
    [216] = PIN_ENTRY(GPIO_216),
    [217] = PIN_ENTRY(GPIO_217),
    [218] = PIN_ENTRY(GPIO_218),
    [219] = PIN_ENTRY(GPIO_219),
    [220] = PIN_ENTRY(GPIO_220),
    [221] = PIN_ENTRY(GPIO_221),
    [222] = PIN_ENTRY(GPIO_222),
    [223] = PIN_ENTRY(GPIO_223),
    [224] = PIN_ENTRY(GPIO_224),
};

struct ns800_pin_irq
{
    struct rt_pin_irq_hdr hdr;
    GPIO_TypeDef *port;
    GPIO_PinNum gpio_pin;
    IRQn_Type irqno;
    rt_bool_t enabled;
};

static struct ns800_pin_irq pin_irq_table[NS800_EXTI_LINES];
static rt_uint32_t pin_irq_enable_mask;
static rt_uint32_t pin_irq_rising_mask;
static rt_uint32_t pin_irq_falling_mask;

int get_pin_num(GPIO_TypeDef *port, GPIO_PinNum pin)
{
    rt_uint32_t i;

    for (i = 0U; i < NS800_PIN_MAP_SIZE; i++)
    {
        if ((pin_map_table[i].port == port) && (pin_map_table[i].pin == pin))
        {
            return (int)i;
        }
    }

    return -1;
}

uint8_t get_port_index(GPIO_TypeDef *port)
{
    if (port == GPIOA) return 0U;
    if (port == GPIOB) return 1U;
    if (port == GPIOC) return 2U;
    if (port == GPIOD) return 3U;
    if (port == GPIOE) return 4U;
    if (port == GPIOF) return 5U;
    if (port == GPIOG) return 6U;
    if (port == GPIOH) return 7U;

    return 0xFFU;
}

uint8_t get_pin_index(uint16_t pin)
{
    return (pin <= GPIO_PIN_31) ? (uint8_t)pin : 0xFFU;
}

uint8_t get_port_index_by_num(int pin_num)
{
    const rt_pin_info_t *info = get_pin_info(pin_num);

    if (info == RT_NULL)
    {
        return 0xFFU;
    }

    return get_port_index(info->port);
}

uint8_t get_pin_index_by_num(int pin_num)
{
    const rt_pin_info_t *info = get_pin_info(pin_num);

    if (info == RT_NULL)
    {
        return 0xFFU;
    }

    return get_pin_index(info->pin);
}

const rt_pin_info_t *get_pin_info(int pin_num)
{
    if ((pin_num < 0) || (pin_num >= (int)NS800_PIN_MAP_SIZE))
    {
        return RT_NULL;
    }

    if (pin_map_table[pin_num].port == RT_NULL)
    {
        return RT_NULL;
    }

    return &pin_map_table[pin_num];
}

/* e.g. PE.7 */
static rt_base_t ns800_pin_get(const char *name)
{
    char port_name;
    int pin_index;
    uint8_t port_index;
    GPIO_TypeDef *port = RT_NULL;
    char *endptr;

    if ((name == RT_NULL) || (name[0] == '\0'))
    {
        return -RT_EINVAL;
    }

    if ((name[0] != 'P') && (name[0] != 'p'))
    {
        return -RT_EINVAL;
    }

    port_name = (char)toupper((unsigned char)name[1]);
    if (name[2] != '.')
    {
        return -RT_EINVAL;
    }

    pin_index = (int)strtol(&name[3], &endptr, 10);
    if ((endptr == &name[3]) || (*endptr != '\0'))
    {
        return -RT_EINVAL;
    }

    if ((pin_index < 0) || (pin_index > 31))
    {
        return -RT_EINVAL;
    }

    port_index = (uint8_t)(port_name - 'A');
    switch (port_index)
    {
    case 0: port = GPIOA; break;
    case 1: port = GPIOB; break;
    case 2: port = GPIOC; break;
    case 3: port = GPIOD; break;
    case 4: port = GPIOE; break;
    case 5: port = GPIOF; break;
    case 6: port = GPIOG; break;
    case 7: port = GPIOH; break;
    default:
        return -RT_EINVAL;
    }

    return get_pin_num(port, (GPIO_PinNum)pin_index);
}

static void ns800rt7_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    RT_UNUSED(dev);

    if (info == RT_NULL)
    {
        return;
    }

    if (value == PIN_LOW)
    {
        GPIO_clearPin(info->port, info->pin);
    }
    else
    {
        GPIO_setPin(info->port, info->pin);
    }
}

static rt_ssize_t ns800rt7_pin_read(rt_device_t dev, rt_base_t pin)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    RT_UNUSED(dev);

    if (info == RT_NULL)
    {
        return -RT_EINVAL;
    }

    return GPIO_readPin(info->port, info->pin) ? PIN_HIGH : PIN_LOW;
}

static void ns800rt7_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    RT_UNUSED(dev);

    if (info == RT_NULL)
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_OUT);
        break;
    case PIN_MODE_INPUT:
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
        break;
    case PIN_MODE_INPUT_PULLUP:
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_PULLUP);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_PULLDOWN);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
        break;
    case PIN_MODE_OUTPUT_OD:
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_OD);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_OUT);
        break;
    default:
        return;
    }

    GPIO_setAnalogMode(info->port, info->pin, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
    GPIO_setQualificationMode(info->port, info->pin, GPIO_QUAL_SYNC);
    GPIO_setDriveLevel(info->port, info->pin, GPIO_DRV_MAX);
}

static rt_bool_t ns800_pin_irq_mode_valid(rt_uint8_t mode)
{
    return (mode == PIN_IRQ_MODE_RISING) ||
           (mode == PIN_IRQ_MODE_FALLING) ||
           (mode == PIN_IRQ_MODE_RISING_FALLING);
}

static int ns800_pin_to_exti_line(GPIO_PinNum pin)
{
    uint8_t pin_index = get_pin_index(pin);

    if (pin_index == 0xFFU)
    {
        return -1;
    }

    return (int)(pin_index & 0x0FU);
}

static IRQn_Type ns800_exti_get_irqn(uint32_t line)
{
    if (line < 4U)
    {
        return EXTI3_0_IRQn;
    }
    else if (line < 8U)
    {
        return EXTI7_4_IRQn;
    }
    else if (line < 12U)
    {
        return EXTI11_8_IRQn;
    }

    return EXTI15_12_IRQn;
}

static uint32_t ns800_exti_irq_group_mask(IRQn_Type irqno)
{
    switch (irqno)
    {
    case EXTI3_0_IRQn:
        return 0x000FU;
    case EXTI7_4_IRQn:
        return 0x00F0U;
    case EXTI11_8_IRQn:
        return 0x0F00U;
    case EXTI15_12_IRQn:
        return 0xF000U;
    default:
        return 0U;
    }
}

static SYSCON_ExtiPinSel ns800_exti_get_pin_sel(GPIO_TypeDef *port, GPIO_PinNum pin)
{
    uint8_t port_sel;

    if (port == GPIOA) port_sel = 0U;
    else if (port == GPIOB) port_sel = 1U;
    else if (port == GPIOC) port_sel = 2U;
    else if (port == GPIOH) port_sel = 3U;
    else if (port == GPIOD) port_sel = 4U;
    else if (port == GPIOE) port_sel = 5U;
    else if (port == GPIOF) port_sel = 6U;
    else if (port == GPIOG) port_sel = 7U;
    else port_sel = 0xFFU;

    if ((port_sel != 0xFFU) && (pin >= GPIO_PIN_16))
    {
        port_sel += 8U;
    }

    return (SYSCON_ExtiPinSel)port_sel;
}

static rt_err_t ns800_exti_select_gpio(GPIO_TypeDef *port, GPIO_PinNum pin,
                                       uint32_t line)
{
    SYSCON_ExtiPinSel pin_sel = ns800_exti_get_pin_sel(port, pin);

    if ((uint32_t)pin_sel > (uint32_t)SYSCON_EXTI_PINSEL_15)
    {
        return -RT_EINVAL;
    }

    SYSCON_UNLOCK;
    SYSCON_setExtiSel(SYSCON, (SYSCON_ExtiSel)line, pin_sel);
    SYSCON_LOCK;

    return RT_EOK;
}

static void ns800_exti_apply_edge_mask(void)
{
    EXTI_setRiseEdgeTrigSelReg(EXTI, pin_irq_rising_mask);
    EXTI_setFallEdgeTrigSelReg(EXTI, pin_irq_falling_mask);
}

static void ns800_exti_disable_line_locked(uint32_t line)
{
    uint32_t line_mask = 1UL << line;
    IRQn_Type irqno = ns800_exti_get_irqn(line);

    pin_irq_enable_mask &= ~line_mask;
    pin_irq_rising_mask &= ~line_mask;
    pin_irq_falling_mask &= ~line_mask;

    EXTI_clearIntrMaskReg(EXTI, line_mask);
    ns800_exti_apply_edge_mask();
    EXTI_clearPendReg(EXTI, line_mask);

    if ((pin_irq_enable_mask & ns800_exti_irq_group_mask(irqno)) == 0U)
    {
        Interrupt_disable(irqno);
    }
}

static rt_err_t ns800_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const rt_pin_info_t *info = get_pin_info(pin);
    struct ns800_pin_irq *pin_irq;
    rt_base_t level;
    int line;

    RT_UNUSED(device);

    if ((info == RT_NULL) || (PIN_PORT(pin) >= PIN_STPORT_MAX) || (hdr == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (!ns800_pin_irq_mode_valid(mode))
    {
        return -RT_EINVAL;
    }

    line = ns800_pin_to_exti_line(info->pin);
    if ((line < 0) || (line >= (int)NS800_EXTI_LINES))
    {
        return -RT_ENOSYS;
    }

    pin_irq = &pin_irq_table[line];

    level = rt_hw_interrupt_disable();
    if ((pin_irq->hdr.pin == pin) &&
        (pin_irq->hdr.hdr == hdr) &&
        (pin_irq->hdr.mode == mode) &&
        (pin_irq->hdr.args == args))
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (pin_irq->hdr.pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    pin_irq->hdr.pin = pin;
    pin_irq->hdr.hdr = hdr;
    pin_irq->hdr.mode = mode;
    pin_irq->hdr.args = args;
    pin_irq->port = info->port;
    pin_irq->gpio_pin = info->pin;
    pin_irq->irqno = ns800_exti_get_irqn((uint32_t)line);
    pin_irq->enabled = RT_FALSE;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ns800_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const rt_pin_info_t *info = get_pin_info(pin);
    struct ns800_pin_irq *pin_irq;
    rt_base_t level;
    int line;

    RT_UNUSED(device);

    if ((info == RT_NULL) || (PIN_PORT(pin) >= PIN_STPORT_MAX))
    {
        return -RT_EINVAL;
    }

    line = ns800_pin_to_exti_line(info->pin);
    if ((line < 0) || (line >= (int)NS800_EXTI_LINES))
    {
        return -RT_ENOSYS;
    }

    pin_irq = &pin_irq_table[line];

    level = rt_hw_interrupt_disable();
    if (pin_irq->hdr.pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (pin_irq->hdr.pin != pin)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EINVAL;
    }

    if (pin_irq->enabled)
    {
        ns800_exti_disable_line_locked((uint32_t)line);
    }

    pin_irq->hdr.pin = -1;
    pin_irq->hdr.hdr = RT_NULL;
    pin_irq->hdr.mode = 0U;
    pin_irq->hdr.args = RT_NULL;
    pin_irq->port = RT_NULL;
    pin_irq->gpio_pin = GPIO_PIN_0;
    pin_irq->enabled = RT_FALSE;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

void EXTI_handler(void);

static rt_err_t ns800_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    const rt_pin_info_t *info = get_pin_info(pin);
    struct ns800_pin_irq *pin_irq;
    rt_base_t level;
    uint32_t line_mask;
    int line;

    RT_UNUSED(device);

    if ((info == RT_NULL) || (PIN_PORT(pin) >= PIN_STPORT_MAX))
    {
        return -RT_EINVAL;
    }

    line = ns800_pin_to_exti_line(info->pin);
    if ((line < 0) || (line >= (int)NS800_EXTI_LINES))
    {
        return -RT_ENOSYS;
    }

    pin_irq = &pin_irq_table[line];
    line_mask = 1UL << (uint32_t)line;

    if (enabled == PIN_IRQ_ENABLE)
    {
        if (pin_irq->hdr.pin != pin)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (ns800_exti_select_gpio(info->port, info->pin, (uint32_t)line) != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        switch (pin_irq->hdr.mode)
        {
        case PIN_IRQ_MODE_RISING:
            pin_irq_rising_mask |= line_mask;
            pin_irq_falling_mask &= ~line_mask;
            break;
        case PIN_IRQ_MODE_FALLING:
            pin_irq_rising_mask &= ~line_mask;
            pin_irq_falling_mask |= line_mask;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            pin_irq_rising_mask |= line_mask;
            pin_irq_falling_mask |= line_mask;
            break;
        default:
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        pin_irq_enable_mask |= line_mask;
        pin_irq->irqno = ns800_exti_get_irqn((uint32_t)line);
        pin_irq->enabled = RT_TRUE;

        EXTI_clearPendReg(EXTI, line_mask);
        ns800_exti_apply_edge_mask();
        EXTI_setIntrMaskReg(EXTI, line_mask);
        Interrupt_register(pin_irq->irqno, &EXTI_handler);
        Interrupt_enable(pin_irq->irqno);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();

        if ((pin_irq->hdr.pin == pin) && pin_irq->enabled)
        {
            ns800_exti_disable_line_locked((uint32_t)line);
            pin_irq->enabled = RT_FALSE;
        }

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

void EXTI_handler(void)
{
    uint32_t pending;
    uint32_t line;

    rt_interrupt_enter();

    pending = EXTI_getPendReg(EXTI) & pin_irq_enable_mask & 0xFFFFU;
    EXTI_clearPendReg(EXTI, pending);

    for (line = 0U; line < NS800_EXTI_LINES; line++)
    {
        if ((pending & (1UL << line)) && pin_irq_table[line].hdr.hdr)
        {
            pin_irq_table[line].hdr.hdr(pin_irq_table[line].hdr.args);
        }
    }

    rt_interrupt_leave();
}

static const struct rt_pin_ops _ns800rt7_pin_ops =
{
    ns800rt7_pin_mode,
    ns800rt7_pin_write,
    ns800rt7_pin_read,
    ns800_pin_attach_irq,
    ns800_pin_detach_irq,
    ns800_pin_irq_enable,
    ns800_pin_get,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    rt_uint32_t i;

    for (i = 0U; i < NS800_EXTI_LINES; i++)
    {
        pin_irq_table[i].hdr.pin = -1;
    }

    return rt_device_pin_register("pin", &_ns800rt7_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */

