/*
 * File      : drv_pin.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-13     Liuguang     the first version. 
 */
#include "drv_pin.h" 

#include "fsl_common.h" 
#include "fsl_iomuxc.h" 
#include "fsl_gpio.h" 

#ifdef RT_USING_PIN

/* GPIO外设时钟会在GPIO_PinInit中自动配置, 如果定义了以下宏则不会自动配置 */ 
#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    #error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

/* RT1052 PIN描述结构体 */
struct rt1052_pin
{
    rt_uint16_t   pin; 
    GPIO_Type    *gpio; 
    rt_uint32_t   gpio_pin; 
}; 

#define __ARRAY_LEN(array) (sizeof(array)/sizeof(array[0])) 
#define __RT1052_PIN_DEFAULT {0, 0, 0} 
#define __RT1052_PIN(INDEX, PORT, PIN) {INDEX, PORT, PIN} 

static struct rt1052_pin rt1052_pin_map[] = 
{
    __RT1052_PIN_DEFAULT, 
    
    /* GPIO4 */
    __RT1052_PIN( 1, GPIO4,  0),    /* GPIO_EMC_00 */
    __RT1052_PIN( 2, GPIO4,  1),    /* GPIO_EMC_01 */
    __RT1052_PIN( 3, GPIO4,  2),    /* GPIO_EMC_02 */
    __RT1052_PIN( 4, GPIO4,  3),    /* GPIO_EMC_03 */
    __RT1052_PIN( 5, GPIO4,  4),    /* GPIO_EMC_04 */
    __RT1052_PIN( 6, GPIO4,  5),    /* GPIO_EMC_05 */
    __RT1052_PIN( 7, GPIO4,  6),    /* GPIO_EMC_06 */
    __RT1052_PIN( 8, GPIO4,  7),    /* GPIO_EMC_07 */
    __RT1052_PIN( 9, GPIO4,  8),    /* GPIO_EMC_08 */
    __RT1052_PIN(10, GPIO4,  9),    /* GPIO_EMC_09 */
    __RT1052_PIN(11, GPIO4, 10),    /* GPIO_EMC_10 */
    __RT1052_PIN(12, GPIO4, 11),    /* GPIO_EMC_11 */
    __RT1052_PIN(13, GPIO4, 12),    /* GPIO_EMC_12 */
    __RT1052_PIN(14, GPIO4, 13),    /* GPIO_EMC_13 */
    __RT1052_PIN(15, GPIO4, 14),    /* GPIO_EMC_14 */
    __RT1052_PIN(16, GPIO4, 15),    /* GPIO_EMC_15 */
    __RT1052_PIN(17, GPIO4, 16),    /* GPIO_EMC_16 */
    __RT1052_PIN(18, GPIO4, 17),    /* GPIO_EMC_17 */
    __RT1052_PIN(19, GPIO4, 18),    /* GPIO_EMC_18 */
    __RT1052_PIN(20, GPIO4, 19),    /* GPIO_EMC_19 */
    __RT1052_PIN(21, GPIO4, 20),    /* GPIO_EMC_20 */
    __RT1052_PIN(22, GPIO4, 21),    /* GPIO_EMC_21 */
    __RT1052_PIN(23, GPIO4, 22),    /* GPIO_EMC_22 */
    __RT1052_PIN(24, GPIO4, 23),    /* GPIO_EMC_23 */
    __RT1052_PIN(25, GPIO4, 24),    /* GPIO_EMC_24 */
    __RT1052_PIN(26, GPIO4, 25),    /* GPIO_EMC_25 */
    __RT1052_PIN(27, GPIO4, 26),    /* GPIO_EMC_26 */
    __RT1052_PIN(28, GPIO4, 27),    /* GPIO_EMC_27 */
    __RT1052_PIN(29, GPIO4, 28),    /* GPIO_EMC_28 */
    __RT1052_PIN(30, GPIO4, 29),    /* GPIO_EMC_29 */
    __RT1052_PIN(31, GPIO4, 30),    /* GPIO_EMC_30 */
    __RT1052_PIN(32, GPIO4, 31),    /* GPIO_EMC_31 */
    
    __RT1052_PIN(33, GPIO3, 18),    /* GPIO_EMC_32 */
    __RT1052_PIN(34, GPIO3, 19),    /* GPIO_EMC_33 */
    __RT1052_PIN(35, GPIO3, 20),    /* GPIO_EMC_34 */
    __RT1052_PIN(36, GPIO3, 21),    /* GPIO_EMC_35 */
    __RT1052_PIN(37, GPIO3, 22),    /* GPIO_EMC_36 */
    __RT1052_PIN(38, GPIO3, 23),    /* GPIO_EMC_37 */
    __RT1052_PIN(39, GPIO3, 24),    /* GPIO_EMC_38 */
    __RT1052_PIN(40, GPIO3, 25),    /* GPIO_EMC_39 */
    __RT1052_PIN(41, GPIO3, 26),    /* GPIO_EMC_40 */
    __RT1052_PIN(42, GPIO3, 27),    /* GPIO_EMC_41 */ 
    
    /* GPIO1 */
    __RT1052_PIN(43, GPIO1,  0),    /* GPIO_AD_B0_00 */ 
    __RT1052_PIN(44, GPIO1,  1),    /* GPIO_AD_B0_01 */
    __RT1052_PIN(45, GPIO1,  2),    /* GPIO_AD_B0_02 */
    __RT1052_PIN(46, GPIO1,  3),    /* GPIO_AD_B0_03 */
    __RT1052_PIN(47, GPIO1,  4),    /* GPIO_AD_B0_04 */
    __RT1052_PIN(48, GPIO1,  5),    /* GPIO_AD_B0_05 */
    __RT1052_PIN(49, GPIO1,  6),    /* GPIO_AD_B0_06 */
    __RT1052_PIN(50, GPIO1,  7),    /* GPIO_AD_B0_07 */
    __RT1052_PIN(51, GPIO1,  8),    /* GPIO_AD_B0_08 */
    __RT1052_PIN(52, GPIO1,  9),    /* GPIO_AD_B0_09 */
    __RT1052_PIN(53, GPIO1, 10),    /* GPIO_AD_B0_10 */
    __RT1052_PIN(54, GPIO1, 11),    /* GPIO_AD_B0_11 */
    __RT1052_PIN(55, GPIO1, 12),    /* GPIO_AD_B0_12 */
    __RT1052_PIN(56, GPIO1, 13),    /* GPIO_AD_B0_13 */
    __RT1052_PIN(57, GPIO1, 14),    /* GPIO_AD_B0_14 */
    __RT1052_PIN(58, GPIO1, 15),    /* GPIO_AD_B0_15 */
    __RT1052_PIN(59, GPIO1, 16),    /* GPIO_AD_B1_00 */
    __RT1052_PIN(60, GPIO1, 17),    /* GPIO_AD_B1_01 */
    __RT1052_PIN(61, GPIO1, 18),    /* GPIO_AD_B1_02 */
    __RT1052_PIN(62, GPIO1, 19),    /* GPIO_AD_B1_03 */
    __RT1052_PIN(63, GPIO1, 20),    /* GPIO_AD_B1_04 */
    __RT1052_PIN(64, GPIO1, 21),    /* GPIO_AD_B1_05 */
    __RT1052_PIN(65, GPIO1, 22),    /* GPIO_AD_B1_06 */
    __RT1052_PIN(66, GPIO1, 23),    /* GPIO_AD_B1_07 */
    __RT1052_PIN(67, GPIO1, 24),    /* GPIO_AD_B1_08 */
    __RT1052_PIN(68, GPIO1, 25),    /* GPIO_AD_B1_09 */
    __RT1052_PIN(69, GPIO1, 26),    /* GPIO_AD_B1_10 */
    __RT1052_PIN(70, GPIO1, 27),    /* GPIO_AD_B1_11 */
    __RT1052_PIN(71, GPIO1, 28),    /* GPIO_AD_B1_12 */
    __RT1052_PIN(72, GPIO1, 29),    /* GPIO_AD_B1_13 */
    __RT1052_PIN(73, GPIO1, 30),    /* GPIO_AD_B1_14 */
    __RT1052_PIN(74, GPIO1, 31),    /* GPIO_AD_B1_15 */

    /* GPIO2 */
    __RT1052_PIN( 75, GPIO2,  0),    /* GPIO_B0_00 */
    __RT1052_PIN( 76, GPIO2,  1),    /* GPIO_B0_01 */
    __RT1052_PIN( 77, GPIO2,  2),    /* GPIO_B0_02 */
    __RT1052_PIN( 78, GPIO2,  3),    /* GPIO_B0_03 */
    __RT1052_PIN( 79, GPIO2,  4),    /* GPIO_B0_04 */
    __RT1052_PIN( 80, GPIO2,  5),    /* GPIO_B0_05 */
    __RT1052_PIN( 81, GPIO2,  6),    /* GPIO_B0_06 */
    __RT1052_PIN( 82, GPIO2,  7),    /* GPIO_B0_07 */
    __RT1052_PIN( 83, GPIO2,  8),    /* GPIO_B0_08 */
    __RT1052_PIN( 84, GPIO2,  9),    /* GPIO_B0_09 */
    __RT1052_PIN( 85, GPIO2, 10),    /* GPIO_B0_10 */
    __RT1052_PIN( 86, GPIO2, 11),    /* GPIO_B0_11 */
    __RT1052_PIN( 87, GPIO2, 12),    /* GPIO_B0_12 */
    __RT1052_PIN( 88, GPIO2, 13),    /* GPIO_B0_13 */
    __RT1052_PIN( 89, GPIO2, 14),    /* GPIO_B0_14 */
    __RT1052_PIN( 90, GPIO2, 15),    /* GPIO_B0_15 */
    __RT1052_PIN( 91, GPIO2, 16),    /* GPIO_B1_00 */
    __RT1052_PIN( 92, GPIO2, 17),    /* GPIO_B1_01 */
    __RT1052_PIN( 93, GPIO2, 18),    /* GPIO_B1_02 */
    __RT1052_PIN( 94, GPIO2, 19),    /* GPIO_B1_03 */
    __RT1052_PIN( 95, GPIO2, 20),    /* GPIO_B1_04 */
    __RT1052_PIN( 96, GPIO2, 21),    /* GPIO_B1_05 */
    __RT1052_PIN( 97, GPIO2, 22),    /* GPIO_B1_06 */
    __RT1052_PIN( 98, GPIO2, 23),    /* GPIO_B1_07 */
    __RT1052_PIN( 99, GPIO2, 24),    /* GPIO_B1_08 */
    __RT1052_PIN(100, GPIO2, 25),    /* GPIO_B1_09 */
    __RT1052_PIN(101, GPIO2, 26),    /* GPIO_B1_10 */
    __RT1052_PIN(102, GPIO2, 27),    /* GPIO_B1_11 */
    __RT1052_PIN(103, GPIO2, 28),    /* GPIO_B1_12 */
    __RT1052_PIN(104, GPIO2, 29),    /* GPIO_B1_13 */
    __RT1052_PIN(105, GPIO2, 30),    /* GPIO_B1_14 */
    __RT1052_PIN(106, GPIO2, 31),    /* GPIO_B1_15 */
    
    /* GPIO3 */
    __RT1052_PIN(107, GPIO3,  0),    /* GPIO_SD_B1_00 */
    __RT1052_PIN(108, GPIO3,  1),    /* GPIO_SD_B1_01 */
    __RT1052_PIN(109, GPIO3,  2),    /* GPIO_SD_B1_02 */
    __RT1052_PIN(110, GPIO3,  3),    /* GPIO_SD_B1_03 */
    __RT1052_PIN(111, GPIO3,  4),    /* GPIO_SD_B1_04 */
    __RT1052_PIN(112, GPIO3,  5),    /* GPIO_SD_B1_05 */
    __RT1052_PIN(113, GPIO3,  6),    /* GPIO_SD_B1_06 */
    __RT1052_PIN(114, GPIO3,  7),    /* GPIO_SD_B1_07 */
    __RT1052_PIN(115, GPIO3,  8),    /* GPIO_SD_B1_08 */
    __RT1052_PIN(116, GPIO3,  9),    /* GPIO_SD_B1_09 */
    __RT1052_PIN(117, GPIO3, 10),    /* GPIO_SD_B1_10 */
    __RT1052_PIN(118, GPIO3, 11),    /* GPIO_SD_B1_11 */
    __RT1052_PIN(119, GPIO3, 12),    /* GPIO_SD_B0_00 */
    __RT1052_PIN(120, GPIO3, 13),    /* GPIO_SD_B0_01 */
    __RT1052_PIN(121, GPIO3, 14),    /* GPIO_SD_B0_02 */
    __RT1052_PIN(122, GPIO3, 15),    /* GPIO_SD_B0_03 */
    __RT1052_PIN(123, GPIO3, 16),    /* GPIO_SD_B0_04 */
    __RT1052_PIN(124, GPIO3, 17),    /* GPIO_SD_B0_05 */

    /* GPIO5 */
    __RT1052_PIN(125, GPIO5,  0),    /* WAKEUP */
    __RT1052_PIN(126, GPIO5,  1),    /* PMIC_ON_REQ */
    __RT1052_PIN(127, GPIO5,  2)     /* PMIC_STBY_REQ */
}; 

static void rt1052_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    gpio_pin_config_t gpio; 
    rt_uint32_t config_value = 0; 
    
    if((pin > __ARRAY_LEN(rt1052_pin_map)) || (pin == 0))
    {
        return; 
    }
    
    if(rt1052_pin_map[pin].gpio != GPIO5)
    {
        CLOCK_EnableClock(kCLOCK_Iomuxc); 
        
    }
    else
    {
        CLOCK_EnableClock(kCLOCK_IomuxcSnvs); 
    }
    
    /* 配置IOMUXC: 将IO配置为GPIO */ 
    IOMUXC_SetPinMux(0x401F8010U + pin*4, 0x5U, 0, 0, 0, 0); 
    
    gpio.outputLogic = 0; 
    gpio.interruptMode = kGPIO_NoIntmode; 
    
    switch(mode)
    {
        case PIN_MODE_OUTPUT:
        {
            config_value = 0x1030U;
            gpio.direction = kGPIO_DigitalOutput; 
        }
        break; 
        
        case PIN_MODE_INPUT:
        {
            config_value = 0x1030U;
            gpio.direction = kGPIO_DigitalInput; 
        }
        break;
        
        case PIN_MODE_INPUT_PULLDOWN:
        {
            config_value = 0x1030U;
            gpio.direction = kGPIO_DigitalInput; 
        }
        break; 
        
        case PIN_MODE_INPUT_PULLUP:
        {
            config_value = 0x5030U;
            gpio.direction = kGPIO_DigitalInput; 
        }
        break;
        
        case PIN_MODE_OUTPUT_OD:
        {
            config_value = 0x1830U;
            gpio.direction = kGPIO_DigitalOutput; 
        }
        break;
    }
    
    /* 配置GPIO模式: 上下拉模式, 开漏模, IO翻转速度(50MHz) */ 
    IOMUXC_SetPinConfig(0, 0, 0, 0, 0x401F8200U + pin*4, config_value); 
    
    GPIO_PinInit(rt1052_pin_map[pin].gpio, rt1052_pin_map[pin].gpio_pin, &gpio); 
}

static int rt1052_pin_read(rt_device_t dev, rt_base_t pin)
{
    return GPIO_PinRead(rt1052_pin_map[pin].gpio, rt1052_pin_map[pin].gpio_pin); 
}

static void rt1052_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_PinWrite(rt1052_pin_map[pin].gpio, rt1052_pin_map[pin].gpio_pin, value);
}

static struct rt_pin_ops rt1052_pin_ops = 
{
    .pin_mode  = rt1052_pin_mode, 
    .pin_read  = rt1052_pin_read, 
    .pin_write = rt1052_pin_write
}; 

int rt_hw_pin_init(void)
{
    int ret = RT_EOK; 
    
    ret = rt_device_pin_register("pin", &rt1052_pin_ops, RT_NULL);
    
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init); 

#endif /*RT_USING_PIN */
