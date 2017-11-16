/*
 * File      : drv_led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-10-07     yiyue.fang    modified from LED driver code for Energy Micro 
 *                              EFM32_G8xx_STK starter kit
 */

#include "board.h"
#include "drv_led.h"

#define LEG_GPIO_PORT           GPIOA
#define LEG_GPIO_PIN            GPIO_PIN_5
#define LED_GPIO_ENABLE_CLK()   __HAL_RCC_GPIOA_CLK_ENABLE()

/**
 * This function light up LED
 *
 * @param led LED number (6)
 */
void led_set(int led)
{
    if (led == 0)
    {
        HAL_GPIO_WritePin(LEG_GPIO_PORT, LEG_GPIO_PIN, GPIO_PIN_SET);
    }
}

/**
 * This function return LED status, on or off
 *
 * @param led LED number (0-1)
 */
int led_get(int led)
{
    int ret = 0;

    if (led == 0)
    {
        ret = HAL_GPIO_ReadPin(LEG_GPIO_PORT, LEG_GPIO_PIN);
    }

    return ret;
}

/**
 * This function turn off LED
 *
 * @param led LED number (0-1)
 */
void led_clear(int led)
{
    if (led == 0)
    {
        HAL_GPIO_WritePin(LEG_GPIO_PORT, LEG_GPIO_PIN, GPIO_PIN_RESET);
    }
}

/**
 * This function toggle LED, switch from on to off or vice versa
 *
 * @param led LED number (0-1)
 */
void led_toggle(int led)
{
    if (led == 0)
    {
        HAL_GPIO_TogglePin(LEG_GPIO_PORT, LEG_GPIO_PIN);
    }
}

/**
 * This function light up LEDs according value of 2 least significat bits
 *
 * @param value Bit pattern
 */
void led_value(int value)
{
    /* Set the value directly using 0xc as a mask. */
    HAL_GPIO_WritePin(LEG_GPIO_PORT, LEG_GPIO_PIN, GPIO_PIN_SET);
    
}

/**
 * This function initialize LED interface
 */
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    LED_GPIO_ENABLE_CLK();
    
    GPIO_InitStruct.Pin = LEG_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LEG_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * This function initialize LED interface
 */
void led_deinit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /*Configure GPIO pin : PA5 */
    GPIO_InitStruct.Pin = LEG_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LEG_GPIO_PORT, &GPIO_InitStruct);
}
