/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-29   onelife     Initial creation for EFM32GG_DK3750 board
 */

/***************************************************************************//**
 * @addtogroup EFM32GG_DK3750
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "dev_keys.h"

#if defined(EFM32_USING_KEYS)
#if defined(RT_USING_RTGUI)
#include <rtgui/event.h>
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_KEYS_DEBUG
#define keys_debug(format,args...)          rt_kprintf(format, ##args)
#else
#define keys_debug(format,args...)
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct efm32_joy_device              joy;
static struct rt_device                     joy_dev;
static struct rtgui_event_mouse             mouse;
static rt_bool_t                            click;

/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *  Keys interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 ******************************************************************************/
static void efm32_keys_isr(rt_device_t dev)
{
    rt_uint16_t flag, joystick;

    /* Clear DEK interrupt */
    flag = DVK_getInterruptFlags();
    DVK_clearInterruptFlags(flag);

    if (flag & BC_INTFLAG_PB)
    {
    }

    if (flag & BC_INTFLAG_DIP)
    {

    }

    if (flag & BC_INTFLAG_JOYSTICK)
    {
        joystick = DVK_getJoystick();
        keys_debug("Keys: joystick %x\n", joystick);

#ifdef RT_USING_RTGUI
        switch (joystick)
        {
        case BC_UIF_JOYSTICK_RIGHT:
            joy.x += 2;
            if (joy.x > joy.max_x)
            {
                joy.x = joy.max_x;
            }
            break;
        case BC_UIF_JOYSTICK_LEFT:
            joy.x -= 2;
            if (joy.x < joy.min_x)
            {
                joy.x = joy.min_x;
            }
            break;
        case BC_UIF_JOYSTICK_DOWN:
            joy.y += 2;
            if (joy.y > joy.max_y)
            {
                joy.y = joy.max_y;
            }
            break;
        case BC_UIF_JOYSTICK_UP:
            joy.y -= 2;
            if (joy.y < joy.min_y)
            {
                joy.y = joy.min_y;
            }
            break;
        case BC_UIF_JOYSTICK_CENTER:
            break;
        default:
            break;
        }
#endif

        if (joystick)
        {
            if (joystick != BC_UIF_JOYSTICK_CENTER)
            {
                mouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
                mouse.x = joy.x;
                mouse.y = joy.y;
                rtgui_server_post_event((&mouse.parent), sizeof(mouse));
                rt_timer_start(&joy.timer);
            }
            else
            {
                click = RT_TRUE;
                mouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
                mouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
                rtgui_server_post_event((&mouse.parent), sizeof(mouse));
            }
        }
        else
        {
            if (click)
            {
                click = RT_FALSE;
                mouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
                mouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
                rtgui_server_post_event((&mouse.parent), sizeof(mouse));
            }
            else
            {
                rt_timer_stop(&joy.timer);
            }
        }
    }

    if (flag & BC_INTFLAG_AEM)
    {
    }
}

/***************************************************************************//**
 * @brief
 *  Keys timeout handler
 *
 * @details
 *
 * @note
 *
 * @param[in] param
 *  Parameter
 ******************************************************************************/
static void efm32_keys_timer_isr(void *param)
{
    rt_uint16_t joystick;

    joystick = DVK_getJoystick();

#ifdef RT_USING_RTGUI
    switch (joystick)
    {
    case BC_UIF_JOYSTICK_RIGHT:
        joy.x += 2;
        if (joy.x > joy.max_x)
        {
            joy.x = joy.max_x;
        }
        break;
    case BC_UIF_JOYSTICK_LEFT:
        joy.x -= 2;
        if (joy.x < joy.min_x)
        {
            joy.x = joy.min_x;
        }
        break;
    case BC_UIF_JOYSTICK_DOWN:
        joy.y += 2;
        if (joy.y > joy.max_y)
        {
            joy.y = joy.max_y;
        }
        break;
    case BC_UIF_JOYSTICK_UP:
        joy.y -= 2;
        if (joy.y < joy.min_y)
        {
            joy.y = joy.min_y;
        }
        break;
    }

    if (joystick)
    {
        mouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
        mouse.x = joy.x;
        mouse.y = joy.y;
        rtgui_server_post_event((&mouse.parent), sizeof(mouse));
    }
#endif
}

/***************************************************************************//**
 * @brief
 *   Initialize keys device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm32_keys_init (rt_device_t dev)
{
    struct rt_device_graphic_info lcd_info;
    rt_device_t lcd;

    lcd = rt_device_find(LCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
        keys_debug("Keys err: Can't find LCD\n");
        return -RT_ERROR;
    }

    lcd->control(lcd, RTGRAPHIC_CTRL_GET_INFO, (void *)&lcd_info);

    click               = RT_FALSE;
    joy.x               = 0;
    joy.y               = 0;
    joy.min_x           = 0;
    joy.max_x           = lcd_info.width;
    joy.min_y           = 0;
    joy.max_y           = lcd_info.height;

    mouse.parent.sender = RT_NULL;
    mouse.wid           = RT_NULL;
    mouse.button        = 0;

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Initialize keys related hardware and register joystic device to kernel
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void efm32_hw_keys_init(void)
{
    /* Configure joystick interrupt pin */
    GPIO_PinModeSet(KEYS_INT_PORT, KEYS_INT_PIN, gpioModeInputPullFilter, 1);

    /* Enable joystick interrupt */
    GPIO_IntConfig(KEYS_INT_PORT, KEYS_INT_PIN, true, true, true);

    efm32_irq_hook_init_t hook;
    hook.type       = efm32_irq_type_gpio;
    hook.unit       = KEYS_INT_PIN;
    hook.cbFunc     = efm32_keys_isr;
    hook.userPtr    = RT_NULL;
    efm32_irq_hook_register(&hook);

    if ((rt_uint8_t)KEYS_INT_PIN % 2)
    {
        NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
        NVIC_SetPriority(GPIO_ODD_IRQn, EFM32_IRQ_PRI_DEFAULT);
        NVIC_EnableIRQ(GPIO_ODD_IRQn);
    }
    else
    {
        NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
        NVIC_SetPriority(GPIO_EVEN_IRQn, EFM32_IRQ_PRI_DEFAULT);
        NVIC_EnableIRQ(GPIO_EVEN_IRQn);
    }

    /* Enable DVK joystick interrupt */
    DVK_enableInterrupt(BC_INTEN_JOYSTICK);

    rt_timer_init(&joy.timer,
        "joy_tmr",
        efm32_keys_timer_isr,
        RT_NULL,
        KEYS_POLL_TIME,
        RT_TIMER_FLAG_PERIODIC);

    joy_dev.init        = efm32_keys_init;
    joy_dev.open        = RT_NULL;
    joy_dev.close       = RT_NULL;
    joy_dev.read        = RT_NULL;
    joy_dev.write       = RT_NULL;
    joy_dev.control     = RT_NULL;
    joy_dev.user_data   = (void *)&joy;

    /* register joy stick device */
    rt_device_register(&joy_dev, "joy", RT_DEVICE_FLAG_RDWR);

    keys_debug("Keys: H/W init OK!\n");
}

#endif /* defined(EFM32_USING_KEYS) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
