/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 *2026-05-17      Jeffery Yuan      add interrupt operation function
 */

#include <board.h>
#include "drv_gpio.h"
#include "NS800RT7xxx_TI_gpio.h"
#include <ctype.h>
#include <stdlib.h>

#ifdef BSP_USING_GPIO

#define PIN_ENTRY(pin_macro) {pin_macro}



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



static struct rt_pin_irq_hdr pin_irq_hdr_table[32] =
{
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
		{-1, 0, RT_NULL, RT_NULL},
};


static const struct pin_irq_map pin_irq_map[32] =
{
    {GPIO_PIN_0, EXTI3_0_IRQn},
    {GPIO_PIN_1, EXTI3_0_IRQn},
    {GPIO_PIN_2, EXTI3_0_IRQn},
    {GPIO_PIN_3, EXTI3_0_IRQn},
    {GPIO_PIN_4, EXTI7_4_IRQn},
    {GPIO_PIN_5, EXTI7_4_IRQn},
    {GPIO_PIN_6, EXTI7_4_IRQn},
    {GPIO_PIN_7, EXTI7_4_IRQn},
    {GPIO_PIN_8, EXTI11_8_IRQn},
    {GPIO_PIN_9, EXTI11_8_IRQn},
    {GPIO_PIN_10, EXTI11_8_IRQn},
    {GPIO_PIN_11, EXTI11_8_IRQn},
    {GPIO_PIN_12, EXTI15_12_IRQn},
    {GPIO_PIN_13, EXTI15_12_IRQn},
    {GPIO_PIN_14, EXTI15_12_IRQn},
    {GPIO_PIN_15, EXTI15_12_IRQn},
    {GPIO_PIN_16, EXTI3_0_IRQn},
    {GPIO_PIN_17, EXTI3_0_IRQn},
    {GPIO_PIN_18, EXTI3_0_IRQn},
    {GPIO_PIN_19, EXTI3_0_IRQn},
    {GPIO_PIN_20, EXTI7_4_IRQn},
    {GPIO_PIN_21, EXTI7_4_IRQn},
    {GPIO_PIN_22, EXTI7_4_IRQn},
    {GPIO_PIN_23, EXTI7_4_IRQn},
    {GPIO_PIN_24, EXTI11_8_IRQn},
    {GPIO_PIN_25, EXTI11_8_IRQn},
    {GPIO_PIN_26, EXTI11_8_IRQn},
    {GPIO_PIN_27, EXTI11_8_IRQn},
    {GPIO_PIN_28, EXTI15_12_IRQn},
    {GPIO_PIN_29, EXTI15_12_IRQn},
    {GPIO_PIN_30, EXTI15_12_IRQn},
    {GPIO_PIN_31, EXTI15_12_IRQn},
};




/* 1. PIN_NUM: 从(port, pin)获取引脚编号 */
int get_pin_num(GPIO_TypeDef *port, GPIO_PinNum pin)
{
    /* 遍历数组查找匹配 */
    for (int i = 0; i < 225; i++)
    {
        if (pin_map_table[i].port == port &&
            pin_map_table[i].pin == (uint16_t)pin)
            {
            return i;  /* 返回引脚编号 */
        }
    }
    return -1;  /* 未找到 */
}

/* 2. PIN_PORT: 从引脚编号获取端口索引 */
uint8_t get_port_index(GPIO_TypeDef *port)
{
    /* 由于新平台端口地址可能不连续，需要映射 */
    if (port == GPIOA) return 0;
    if (port == GPIOB) return 1;
    if (port == GPIOC) return 2;
    if (port == GPIOD) return 3;
    if (port == GPIOE) return 4;
    if (port == GPIOF) return 5;
    if (port == GPIOG) return 6;
    if (port == GPIOH) return 7;
    /* 如果有更多端口继续添加 */
    return 0xFF;  /* 无效端口 */
}

/* 3. PIN_NO: 从引脚编号获取引脚索引 */
uint8_t get_pin_index(uint16_t pin)
{
    /* 提取引脚位的位置 */
    switch (pin)
    {
        case GPIO_PIN_0:  return 0;
        case GPIO_PIN_1:  return 1;
        case GPIO_PIN_2:  return 2;
        case GPIO_PIN_3:  return 3;
        case GPIO_PIN_4:  return 4;
        case GPIO_PIN_5:  return 5;
        case GPIO_PIN_6:  return 6;
        case GPIO_PIN_7:  return 7;
        case GPIO_PIN_8:  return 8;
        case GPIO_PIN_9:  return 9;
        case GPIO_PIN_10: return 10;
        case GPIO_PIN_11: return 11;
        case GPIO_PIN_12: return 12;
        case GPIO_PIN_13: return 13;
        case GPIO_PIN_14: return 14;
        case GPIO_PIN_15: return 15;
        case GPIO_PIN_16: return 16;
        case GPIO_PIN_17: return 17;
        case GPIO_PIN_18: return 18;
        case GPIO_PIN_19: return 19;
        case GPIO_PIN_20: return 20;
        case GPIO_PIN_21: return 21;
        case GPIO_PIN_22: return 22;
        case GPIO_PIN_23: return 23;
        case GPIO_PIN_24: return 24;
        case GPIO_PIN_25: return 25;
        case GPIO_PIN_26: return 26;
        case GPIO_PIN_27: return 27;
        case GPIO_PIN_28: return 28;
        case GPIO_PIN_29: return 29;
        case GPIO_PIN_30: return 30;
        case GPIO_PIN_31: return 31;
        default: return 0xFF;  /* 无效引脚 */
    }
}

uint8_t get_port_index_by_num(int pin_num)
{
    const rt_pin_info_t *info = get_pin_info(pin_num);

    if (info == RT_NULL)
    {
        return 0xFF;
    }

    return get_port_index(info->port);
}

uint8_t get_pin_index_by_num(int pin_num)
{
    const rt_pin_info_t *info = get_pin_info(pin_num);

    if (info == RT_NULL)
    {
        return 0xFF;
    }

    return get_pin_index(info->pin);
}

const rt_pin_info_t* get_pin_info(int pin_num)
{
    if(pin_num < 0 || pin_num >=225)
        return NULL;

    if(pin_map_table[pin_num].port == NULL)
    {
        return NULL;
    }

    return &pin_map_table[pin_num];
}


static uint32_t pin_irq_enable_mask = 0;

#define ITEM_NUM(items) (sizeof(items) / sizeof((items)[0]))

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
        goto out;
    }

    if ((name[0] != 'P') && (name[0] != 'p'))
    {
        goto out;
    }

    port_name = (char)toupper((unsigned char)name[1]);
    if (name[2] != '.')
    {
        goto out;
    }

    pin_index = (int)strtol(&name[3], &endptr, 10);
    if ((endptr == &name[3]) || (*endptr != '\0'))
    {
        goto out;
    }

    if ((pin_index < 0) || (pin_index > 31))
    {
        goto out;
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
        goto out;
    }

    return get_pin_num(port, (GPIO_PinNum)pin_index);

out:
    rt_kprintf("Px.y  x:A~H  y:0-31, e.g. PA.0\n");
    return -RT_EINVAL;
}

static void ns800rt7_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    if (info == RT_NULL)
    {
        return ;
    }

    if(value == 0)
    {
        GPIO_clearPin(info->port, info->pin);
    }
    else if(value == 1)
    {
        GPIO_setPin(info->port, info->pin);
    }
}

static rt_ssize_t ns800rt7_pin_read(rt_device_t dev, rt_base_t pin)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    if (info == RT_NULL)
    {
        return -RT_EINVAL;
    }

    return (GPIO_readPin(info->port, info->pin)) ? PIN_HIGH : PIN_LOW;
}

static void ns800rt7_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const rt_pin_info_t *info = get_pin_info(pin);

    if (info == RT_NULL)
    {
        return ;
    }

    GPIO_setAnalogMode(info->port, info->pin, GPIO_ANALOG_DISABLED);
    GPIO_setQualificationMode(info->port, info->pin, GPIO_QUAL_SYNC);
    GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_STD);
    GPIO_setDriveLevel(info->port, info->pin, GPIO_DRV_MAX);

    if (mode == PIN_MODE_OUTPUT )
    {
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
        GPIO_clearPin(info->port, info->pin);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_OUT);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_PULLUP);
        GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_PULLDOWN);
        GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_IN);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIO_setPadConfig(info->port, info->pin, GPIO_PIN_TYPE_OD);
        GPIO_setPinConfig(info->port, info->pin, ALT0_FUNCTION);
        GPIO_clearPin(info->port, info->pin);
        GPIO_setDirectionMode(info->port, info->pin, GPIO_DIR_MODE_OUT);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint32_t pinbit)
{
    rt_int32_t mapindex = get_pin_index(pinbit);
    if (mapindex < 0 || mapindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
}




static rt_err_t ns800_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;
		const rt_pin_info_t *info = get_pin_info(pin);
    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
    case PIN_IRQ_MODE_FALLING:
    case PIN_IRQ_MODE_RISING_FALLING:
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        /* hardware not supported */
    case PIN_IRQ_MODE_LOW_LEVEL:
        /* hardware not supported */
    default:
        return -RT_EINVAL;
    }
    irqindex = get_pin_index(info->pin);
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_hdr_table))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_table[irqindex].pin == info->pin &&
        pin_irq_hdr_table[irqindex].hdr == hdr &&
        pin_irq_hdr_table[irqindex].mode == mode &&
        pin_irq_hdr_table[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_table[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    pin_irq_hdr_table[irqindex].pin = info->pin;
    pin_irq_hdr_table[irqindex].hdr = hdr;
    pin_irq_hdr_table[irqindex].mode = mode;
    pin_irq_hdr_table[irqindex].args = args;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t ns800_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;
		const rt_pin_info_t *info = get_pin_info(pin);
	
    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = get_pin_index(info->pin);
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_table[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_table[irqindex].pin = -1;
    pin_irq_hdr_table[irqindex].hdr = RT_NULL;
    pin_irq_hdr_table[irqindex].mode = 0;
    pin_irq_hdr_table[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}


static SYSCON_ExtiSel EXTI_enableGpioLine (GPIO_TypeDef *port, GPIO_PinNum pin)
{
    SYSCON_ExtiSel retLine;
    retLine = (SYSCON_ExtiSel)((uint16_t)pin % 16);
    /* Unlock SYSCON register writing function */
    SYSCON_UNLOCK;
	
	
	

    if (port == GPIOA)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_0);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_8);
        }
    }
    else if (port == GPIOB)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_1);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_9);
        }
    }
    else if (port == GPIOC)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_2);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_10);
        }
    }
    else if (port == GPIOH)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_3);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_11);
        }
    }
    else if (port == GPIOD)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_4);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_12);
        }
    }
    else if (port == GPIOE)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_5);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_13);
        }
    }
    else if (port == GPIOF)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_6);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_14);
        }
    }
    else if (port == GPIOG)
    {
        if (pin < GPIO_PIN_16)
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_7);
        }
        else
        {
            SYSCON_setExtiSel(SYSCON, retLine, SYSCON_EXTI_PINSEL_15);
        }
    }

    /* Lock SYSCON register writing function */
    SYSCON_LOCK;

    return retLine;
}

static IRQn_Type EXTI_getLineIrqn (SYSCON_ExtiSel line)
{
    IRQn_Type irq = EXTI3_0_IRQn;

    switch (line)
    {
        case SYSCON_EXTISEL_0:
        case SYSCON_EXTISEL_1:
        case SYSCON_EXTISEL_2:
        case SYSCON_EXTISEL_3:
        {
            irq = EXTI3_0_IRQn;
        }
        break;

        case SYSCON_EXTISEL_4:
        case SYSCON_EXTISEL_5:
        case SYSCON_EXTISEL_6:
        case SYSCON_EXTISEL_7:
        {
            irq = EXTI7_4_IRQn;
        }
        break;

        case SYSCON_EXTISEL_8:
        case SYSCON_EXTISEL_9:
        case SYSCON_EXTISEL_10:
        case SYSCON_EXTISEL_11:
        {
            irq = EXTI11_8_IRQn;
        }
        break;

        case SYSCON_EXTISEL_12:
        case SYSCON_EXTISEL_13:
        case SYSCON_EXTISEL_14:
        case SYSCON_EXTISEL_15:
        {
            irq = EXTI15_12_IRQn;
        }
        break;

        default:
            break;
    }

    return irq;
}

void EXTI_handler(void);


static rt_err_t ns800_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{    
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    rt_uint8_t gpio_port_souce=0;
    const rt_pin_info_t *info = get_pin_info(pin);
		uint32_t key_line_idx = 0;
		IRQn_Type key_irq_idx;
    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = get_pin_index(info->pin);
        if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_table[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        irqmap = &pin_irq_map[irqindex];

				key_line_idx = EXTI_enableGpioLine(info->port,info->pin);
				key_irq_idx = EXTI_getLineIrqn((SYSCON_ExtiSel)key_line_idx);
				EXTI_setIntrMaskReg(EXTI, (1 << key_line_idx));
				/* Interrupt handler function registration. */
				Interrupt_register(key_irq_idx, &EXTI_handler);
				/* Enable the interrupt signals. Enable global interrupts.*/
				Interrupt_enable(key_irq_idx);

        switch (pin_irq_hdr_table[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
					  GPIO_setPadConfig(info->port,info->pin, GPIO_PIN_TYPE_PULLDOWN);
            EXTI_setRiseEdgeTrigSelReg(EXTI, (1 << key_line_idx));
            break;
        case PIN_IRQ_MODE_FALLING:
					  GPIO_setPadConfig(info->port,info->pin, GPIO_PIN_TYPE_PULLUP);
            EXTI_setFallEdgeTrigSelReg(EXTI, (1 << key_line_idx));
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
					  GPIO_setPadConfig(info->port,info->pin, GPIO_PIN_TYPE_STD);
						EXTI_setRiseEdgeTrigSelReg(EXTI, (1 << key_line_idx));
            EXTI_setFallEdgeTrigSelReg(EXTI, (1 << key_line_idx));
            break;
        }
				/* Enable the interrupt signals. Enable global interrupts.*/
				Interrupt_enable(irqmap->irqno);
				rt_kprintf("IRQn=%d\n",irqmap->irqno);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(info->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

        if ((irqmap->pinbit>=GPIO_PIN_0)&&(irqmap->pinbit<=GPIO_PIN_3))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)))
            {
							  Interrupt_disable(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_4)&&(irqmap->pinbit<=GPIO_PIN_7))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)))
            {
							  Interrupt_disable(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_8)&&(irqmap->pinbit<=GPIO_PIN_11))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_12)&&(irqmap->pinbit<=GPIO_PIN_15))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_16)&&(irqmap->pinbit<=GPIO_PIN_19))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_16|GPIO_PIN_17|GPIO_PIN_18|GPIO_PIN_19)))
            {
							  Interrupt_disable(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_20)&&(irqmap->pinbit<=GPIO_PIN_23))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_20|GPIO_PIN_21|GPIO_PIN_22|GPIO_PIN_23)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_24)&&(irqmap->pinbit<=GPIO_PIN_27))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_24|GPIO_PIN_25|GPIO_PIN_26|GPIO_PIN_27)))
            {
							  Interrupt_disable(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit>=GPIO_PIN_28)&&(irqmap->pinbit<=GPIO_PIN_31))
        {
            if(!(pin_irq_enable_mask&(GPIO_PIN_28|GPIO_PIN_29|GPIO_PIN_30|GPIO_PIN_31)))
            {
							  Interrupt_disable(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQ(irqmap->irqno);
        }

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}




rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_table[irqno].hdr)
    {
        pin_irq_hdr_table[irqno].hdr(pin_irq_hdr_table[irqno].args);
    }
}

void HAL_GPIO_EXTI_Callback(rt_uint16_t GPIO_Pin)
{
    pin_irq_hdr(get_pin_index(GPIO_Pin));
}


void EXTI_handler(void)
{
    rt_interrupt_enter();

    uint32_t tempPr = EXTI_getPendReg(EXTI);

    if(tempPr & (1 << SYSCON_EXTISEL_0))
    {
			if(pin_irq_hdr_table[GPIO_PIN_0].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_0);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_16].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_16);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_1))
		{
			if(pin_irq_hdr_table[GPIO_PIN_1].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_1);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_17].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_17);
			}
		}
    if(tempPr & (1 << SYSCON_EXTISEL_2))
    {
			if(pin_irq_hdr_table[GPIO_PIN_2].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_2);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_18].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_18);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_3))
		{
			if(pin_irq_hdr_table[GPIO_PIN_3].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_3);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_19].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_19);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_4))
    {
			if(pin_irq_hdr_table[GPIO_PIN_4].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_4);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_20].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_20);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_5))
		{
			if(pin_irq_hdr_table[GPIO_PIN_5].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_5);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_21].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_21);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_6))
		{
			if(pin_irq_hdr_table[GPIO_PIN_6].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_6);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_22].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_22);
			}
		}
    if(tempPr & (1 << SYSCON_EXTISEL_7))
    {
			if(pin_irq_hdr_table[GPIO_PIN_7].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_7);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_23].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_23);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_8))
		{
			if(pin_irq_hdr_table[GPIO_PIN_8].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_8);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_24].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_24);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_9))
    {
			if(pin_irq_hdr_table[GPIO_PIN_9].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_9);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_25].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_25);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_10))
		{
			if(pin_irq_hdr_table[GPIO_PIN_10].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_10);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_26].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_26);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_11))
		{
			if(pin_irq_hdr_table[GPIO_PIN_11].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_11);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_27].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_27);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_12))
    {
			if(pin_irq_hdr_table[GPIO_PIN_12].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_12);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_28].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_28);
			}
    }
		if(tempPr & (1 << SYSCON_EXTISEL_13))
		{
			if(pin_irq_hdr_table[GPIO_PIN_13].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_13);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_29].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_29);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_14))
		{
			if(pin_irq_hdr_table[GPIO_PIN_14].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_14);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_30].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_30);
			}
		}
		if(tempPr & (1 << SYSCON_EXTISEL_15))
    {
			if(pin_irq_hdr_table[GPIO_PIN_15].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_15);
			}
			else if(pin_irq_hdr_table[GPIO_PIN_31].hdr)
			{
				HAL_GPIO_EXTI_Callback(GPIO_PIN_31);
			}
    }
		
    EXTI_clearPendReg(EXTI, tempPr);

    rt_interrupt_leave();

}


static const struct rt_pin_ops _ns800rt7_pin_ops =
{
    ns800rt7_pin_mode,
    ns800rt7_pin_write,
    ns800rt7_pin_read,
    ns800_pin_attach_irq,
    ns800_pin_dettach_irq,
    ns800_pin_irq_enable,
    ns800_pin_get,
    RT_NULL,
};


int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_ns800rt7_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */

