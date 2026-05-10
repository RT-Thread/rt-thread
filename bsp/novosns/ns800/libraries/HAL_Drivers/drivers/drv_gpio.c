/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 *
 */

#include <board.h>
#include "drv_gpio.h"
#include "NS800RT7xxx_TI_gpio.h"
#include <ctype.h>
#include <stdlib.h>

#ifdef BSP_USING_GPIO

#define PIN_ENTRY(pin_macro) {pin_macro}

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

#define PIN_STPORT(pin)     (pin_map_table[(pin)].port)
#define PIN_STPIN(pin)      (pin_map_table[(pin)].pin)


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

static rt_err_t ns800_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    return RT_EOK;
}

static rt_err_t ns800_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    return RT_EOK;
}

static rt_err_t ns800_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    return RT_EOK;
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

rt_inline void pin_irq_hdr(int irqno)
{

}

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_ns800rt7_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */

