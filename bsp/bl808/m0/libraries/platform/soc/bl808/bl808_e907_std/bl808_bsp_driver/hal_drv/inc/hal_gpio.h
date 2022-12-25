/**
 * @file hal_gpio.h
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
#ifndef __HAL_GPIO__H__
#define __HAL_GPIO__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

enum gpio_pin_type {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_16,
    GPIO_PIN_17,
    GPIO_PIN_18,
    GPIO_PIN_19,
    GPIO_PIN_20,
    GPIO_PIN_21,
    GPIO_PIN_22,
    GPIO_PIN_23,
    GPIO_PIN_24,
    GPIO_PIN_25,
    GPIO_PIN_26,
    GPIO_PIN_27,
    GPIO_PIN_28,
    GPIO_PIN_29,
    GPIO_PIN_30,
    GPIO_PIN_31,
    GPIO_PIN_32,
    GPIO_PIN_33,
    GPIO_PIN_34,
    GPIO_PIN_35,
    GPIO_PIN_36,
    GPIO_PIN_37,
    GPIO_PIN_38,
    GPIO_PIN_39,
    GPIO_PIN_40,
    GPIO_PIN_41,
    GPIO_PIN_42,
    GPIO_PIN_43,
    GPIO_PIN_44,
    GPIO_PIN_45,
    GPIO_PIN_MAX,
};

#define GPIO_OUTPUT_MODE                         0
#define GPIO_OUTPUT_PP_MODE                      1
#define GPIO_OUTPUT_PD_MODE                      2
#define GPIO_INPUT_MODE                          3
#define GPIO_INPUT_PP_MODE                       4
#define GPIO_INPUT_PD_MODE                       5
#define GPIO_ASYNC_RISING_TRIGER_INT_MODE        6
#define GPIO_ASYNC_FALLING_TRIGER_INT_MODE       7
#define GPIO_ASYNC_HIGH_LEVEL_INT_MODE           8
#define GPIO_ASYNC_LOW_LEVEL_INT_MODE            9
#define GPIO_SYNC_RISING_TRIGER_INT_MODE         10
#define GPIO_SYNC_FALLING_TRIGER_INT_MODE        11
#define GPIO_SYNC_RISING_FALLING_TRIGER_INT_MODE 12
#define GPIO_SYNC_HIGH_LEVEL_INT_MODE            13
#define GPIO_SYNC_LOW_LEVEL_INT_MODE             14
#define GPIO_HZ_MODE                             15

void gpio_set_mode(uint32_t pin, uint32_t mode);
void gpio_write(uint32_t pin, uint32_t value);
void gpio_toggle(uint32_t pin);
int gpio_read(uint32_t pin);
void gpio_attach_irq(uint32_t pin, void (*cbfun)(uint32_t pin));
void gpio_irq_enable(uint32_t pin, uint8_t enabled);
#endif
