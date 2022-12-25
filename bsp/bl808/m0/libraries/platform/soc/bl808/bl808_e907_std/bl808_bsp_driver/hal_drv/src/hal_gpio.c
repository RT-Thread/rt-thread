/**
 * @file hal_gpio.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "bl808_glb.h"
#include "bl808_gpio.h"
#include "hal_gpio.h"

static void GPIO_IRQ(void);

struct gpio_int_cfg_private {
    slist_t list;
    uint32_t pin;
    void (*cbfun)(uint32_t pin);
};

static slist_t gpio_int_head = SLIST_OBJECT_INIT(gpio_int_head);

/**
 * @brief
 *
 * @param pin
 * @param mode
 */
void gpio_set_mode(uint32_t pin, uint32_t mode)
{
    GLB_GPIO_Cfg_Type gpio_cfg;

    gpio_cfg.gpioFun = GPIO_FUN_GPIO;
    gpio_cfg.gpioPin = pin;
    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.outputMode = 0;

    switch (mode) {
        case GPIO_OUTPUT_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_NONE;
            break;

        case GPIO_OUTPUT_PP_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_UP;
            break;

        case GPIO_OUTPUT_PD_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_DOWN;
            break;

        case GPIO_INPUT_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_NONE;
            break;

        case GPIO_INPUT_PP_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_UP;
            break;

        case GPIO_INPUT_PD_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_DOWN;
            break;
        case GPIO_HZ_MODE:
            GLB_GPIO_Set_HZ(pin);
        default:
            CPU_Interrupt_Disable(GPIO_INT0_IRQn);
            GLB_GPIO_IntMask(pin, MASK);

            GLB_GPIO_INT_Cfg_Type intCfg;

            intCfg.gpioPin = pin;
            intCfg.intMask = MASK;

            gpio_cfg.gpioMode = GPIO_MODE_INPUT;

            if (mode == GPIO_ASYNC_RISING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_RISING_EDGE;
            } else if (mode == GPIO_ASYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_FALLING_EDGE;
            } else if (mode == GPIO_ASYNC_HIGH_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_HIGH_LEVEL;
            } else if (mode == GPIO_ASYNC_LOW_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_LOW_LEVEL;
            } else if (mode == GPIO_SYNC_RISING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_RISING_EDGE;
            } else if (mode == GPIO_SYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_FALLING_EDGE;
            } else if (mode == GPIO_SYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_NONE;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_FALLING_RISING_EDGE;
            } else if (mode == GPIO_SYNC_HIGH_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_HIGH_LEVEL;
            } else if (mode == GPIO_SYNC_LOW_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_LOW_LEVEL;
            }

            GLB_GPIO_Int_Init(&intCfg);
            break;
    }

    GLB_GPIO_Init(&gpio_cfg);
}
/**
 * @brief
 *
 * @param pin
 * @param value
 */
void gpio_write(uint32_t pin, uint32_t value)
{
    GLB_GPIO_Write(pin, value);
}
/**
 * @brief
 *
 * @param pin
 */
void gpio_toggle(uint32_t pin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (pin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    if (BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_O)) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_O);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_O);
    }

    BL_WR_WORD(gpioCfgAddress, tmpVal);
}
/**
 * @brief
 *
 * @param pin
 * @return int
 */
int gpio_read(uint32_t pin)
{
    return GLB_GPIO_Read(pin);
}
/**
 * @brief
 *
 * @param pin
 * @param cbFun
 */
void gpio_attach_irq(uint32_t pin, void (*cbfun)(uint32_t pin))
{
    struct gpio_int_cfg_private *int_cfg = malloc(sizeof(struct gpio_int_cfg_private));
    int_cfg->cbfun = cbfun;
    int_cfg->pin = pin;
    slist_add_tail(&gpio_int_head, &int_cfg->list);
    CPU_Interrupt_Disable(GPIO_INT0_IRQn);
    Interrupt_Handler_Register(GPIO_INT0_IRQn, GPIO_IRQ);
    CPU_Interrupt_Enable(GPIO_INT0_IRQn);
}
/**
 * @brief
 *
 * @param pin
 * @param enabled
 */
void gpio_irq_enable(uint32_t pin, uint8_t enabled)
{
    if (enabled) {
        GLB_GPIO_IntMask(pin, UNMASK);
    } else {
        GLB_GPIO_IntMask(pin, MASK);
    }
}

static void GPIO_IRQ(void)
{
    slist_t *i;
    uint32_t timeOut = 0;
#define GLB_GPIO_INT0_CLEAR_TIMEOUT (32)
    slist_for_each(i, &gpio_int_head)
    {
        struct gpio_int_cfg_private *int_cfg = slist_entry(i, struct gpio_int_cfg_private, list);

        if (SET == GLB_Get_GPIO_IntStatus(int_cfg->pin)) {
            int_cfg->cbfun(int_cfg->pin);
            GLB_Clr_GPIO_IntStatus(int_cfg->pin);
            /* timeout check */
            timeOut = GLB_GPIO_INT0_CLEAR_TIMEOUT;

            do {
                timeOut--;
            } while ((SET == GLB_Get_GPIO_IntStatus(int_cfg->pin)) && timeOut);

            if (!timeOut) {
                //MSG("WARNING: Clear GPIO interrupt status fail.\r\n");
            }
        }
    }
}