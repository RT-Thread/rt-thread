/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/05/10     flyingcys    first version
*/

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "bflb_gpio.h"
#include "bflb_i2c.h"

// I2C0
#ifdef I2C0_SCL_USING_GPIO0
#define I2C0_GPIO_SCL       GPIO_PIN_0
#elif defined(I2C0_SCL_USING_GPIO2)
#define I2C0_GPIO_SCL       GPIO_PIN_2
#elif defined(I2C0_SCL_USING_GPIO4)
#define I2C0_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C0_SCL_USING_GPIO6)
#define I2C0_GPIO_SCL       GPIO_PIN_6
#elif defined(I2C0_SCL_USING_GPIO8)
#define I2C0_GPIO_SCL       GPIO_PIN_8
#elif defined(I2C0_SCL_USING_GPIO10)
#define I2C0_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C0_SCL_USING_GPIO12)
#define I2C0_GPIO_SCL       GPIO_PIN_12
#elif defined(I2C0_SCL_USING_GPIO14)
#define I2C0_GPIO_SCL       GPIO_PIN_14
#elif defined(I2C0_SCL_USING_GPIO16)
#define I2C0_GPIO_SCL       GPIO_PIN_16
#elif defined(I2C0_SCL_USING_GPIO18)
#define I2C0_GPIO_SCL       GPIO_PIN_18
#elif defined(I2C0_SCL_USING_GPIO20)
#define I2C0_GPIO_SCL       GPIO_PIN_20
#elif defined(I2C0_SCL_USING_GPIO22)
#define I2C0_GPIO_SCL       GPIO_PIN_22
#elif defined(I2C0_SCL_USING_GPIO24)
#define I2C0_GPIO_SCL       GPIO_PIN_24
#elif defined(I2C0_SCL_USING_GPIO26)
#define I2C0_GPIO_SCL       GPIO_PIN_26
#elif defined(I2C0_SCL_USING_GPIO28)
#define I2C0_GPIO_SCL       GPIO_PIN_28
#elif defined(I2C0_SCL_USING_GPIO30)
#define I2C0_GPIO_SCL       GPIO_PIN_30
#elif defined(I2C0_SCL_USING_GPIO32)
#define I2C0_GPIO_SCL       GPIO_PIN_32
#elif defined(I2C0_SCL_USING_GPIO34)
#define I2C0_GPIO_SCL       GPIO_PIN_34
#elif defined(I2C0_SCL_USING_GPIO36)
#define I2C0_GPIO_SCL       GPIO_PIN_36
#elif defined(I2C0_SCL_USING_GPIO38)
#define I2C0_GPIO_SCL       GPIO_PIN_38
#elif defined(I2C0_SCL_USING_GPIO40)
#define I2C0_GPIO_SCL       GPIO_PIN_40
#elif defined(I2C0_SCL_USING_GPIO42)
#define I2C0_GPIO_SCL       GPIO_PIN_42
#elif defined(I2C0_SCL_USING_GPIO44)
#define I2C0_GPIO_SCL       GPIO_PIN_44
#endif

#ifdef I2C0_SDA_USING_GPIO1
#define I2C0_GPIO_SDA       GPIO_PIN_1
#elif defined(I2C0_SDA_USING_GPIO3)
#define I2C0_GPIO_SDA       GPIO_PIN_3
#elif defined(I2C0_SDA_USING_GPIO5)
#define I2C0_GPIO_SDA       GPIO_PIN_5
#elif defined(I2C0_SDA_USING_GPIO7)
#define I2C0_GPIO_SDA       GPIO_PIN_7
#elif defined(I2C0_SDA_USING_GPIO9)
#define I2C0_GPIO_SDA       GPIO_PIN_9
#elif defined(I2C0_SDA_USING_GPIO11)
#define I2C0_GPIO_SDA       GPIO_PIN_11
#elif defined(I2C0_SDA_USING_GPIO13)
#define I2C0_GPIO_SDA       GPIO_PIN_13
#elif defined(I2C0_SDA_USING_GPIO15)
#define I2C0_GPIO_SDA       GPIO_PIN_15
#elif defined(I2C0_SDA_USING_GPIO17)
#define I2C0_GPIO_SDA       GPIO_PIN_17
#elif defined(I2C0_SDA_USING_GPIO19)
#define I2C0_GPIO_SDA       GPIO_PIN_19
#elif defined(I2C0_SDA_USING_GPIO21)
#define I2C0_GPIO_SDA       GPIO_PIN_21
#elif defined(I2C0_SDA_USING_GPIO23)
#define I2C0_GPIO_SDA       GPIO_PIN_23
#elif defined(I2C0_SDA_USING_GPIO25)
#define I2C0_GPIO_SDA       GPIO_PIN_25
#elif defined(I2C0_SDA_USING_GPIO27)
#define I2C0_GPIO_SDA       GPIO_PIN_27
#elif defined(I2C0_SDA_USING_GPIO29)
#define I2C0_GPIO_SDA       GPIO_PIN_29
#elif defined(I2C0_SDA_USING_GPIO31)
#define I2C0_GPIO_SDA       GPIO_PIN_31
#elif defined(I2C0_SDA_USING_GPIO33)
#define I2C0_GPIO_SDA       GPIO_PIN_33
#elif defined(I2C0_SDA_USING_GPIO35)
#define I2C0_GPIO_SDA       GPIO_PIN_35
#elif defined(I2C0_SDA_USING_GPIO37)
#define I2C0_GPIO_SDA       GPIO_PIN_37
#elif defined(I2C0_SDA_USING_GPIO39)
#define I2C0_GPIO_SDA       GPIO_PIN_39
#elif defined(I2C0_SDA_USING_GPIO41)
#define I2C0_GPIO_SDA       GPIO_PIN_41
#elif defined(I2C0_SDA_USING_GPIO43)
#define I2C0_GPIO_SDA       GPIO_PIN_43
#elif defined(I2C0_SDA_USING_GPIO45)
#define I2C0_GPIO_SDA       GPIO_PIN_45
#endif

// I2C1
#ifdef I2C1_SCL_USING_GPIO0
#define I2C1_GPIO_SCL       GPIO_PIN_0
#elif defined(I2C1_SCL_USING_GPIO2)
#define I2C1_GPIO_SCL       GPIO_PIN_2
#elif defined(I2C1_SCL_USING_GPIO4)
#define I2C1_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C1_SCL_USING_GPIO6)
#define I2C1_GPIO_SCL       GPIO_PIN_6
#elif defined(I2C1_SCL_USING_GPIO8)
#define I2C1_GPIO_SCL       GPIO_PIN_8
#elif defined(I2C1_SCL_USING_GPIO10)
#define I2C1_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C1_SCL_USING_GPIO12)
#define I2C1_GPIO_SCL       GPIO_PIN_12
#elif defined(I2C1_SCL_USING_GPIO14)
#define I2C1_GPIO_SCL       GPIO_PIN_14
#elif defined(I2C1_SCL_USING_GPIO16)
#define I2C1_GPIO_SCL       GPIO_PIN_16
#elif defined(I2C1_SCL_USING_GPIO18)
#define I2C1_GPIO_SCL       GPIO_PIN_18
#elif defined(I2C1_SCL_USING_GPIO20)
#define I2C1_GPIO_SCL       GPIO_PIN_20
#elif defined(I2C1_SCL_USING_GPIO22)
#define I2C1_GPIO_SCL       GPIO_PIN_22
#elif defined(I2C1_SCL_USING_GPIO24)
#define I2C1_GPIO_SCL       GPIO_PIN_24
#elif defined(I2C1_SCL_USING_GPIO26)
#define I2C1_GPIO_SCL       GPIO_PIN_26
#elif defined(I2C1_SCL_USING_GPIO28)
#define I2C1_GPIO_SCL       GPIO_PIN_28
#elif defined(I2C1_SCL_USING_GPIO30)
#define I2C1_GPIO_SCL       GPIO_PIN_30
#elif defined(I2C1_SCL_USING_GPIO32)
#define I2C1_GPIO_SCL       GPIO_PIN_32
#elif defined(I2C1_SCL_USING_GPIO34)
#define I2C1_GPIO_SCL       GPIO_PIN_34
#elif defined(I2C1_SCL_USING_GPIO36)
#define I2C1_GPIO_SCL       GPIO_PIN_36
#elif defined(I2C1_SCL_USING_GPIO38)
#define I2C1_GPIO_SCL       GPIO_PIN_38
#elif defined(I2C1_SCL_USING_GPIO40)
#define I2C1_GPIO_SCL       GPIO_PIN_40
#elif defined(I2C1_SCL_USING_GPIO42)
#define I2C1_GPIO_SCL       GPIO_PIN_42
#elif defined(I2C1_SCL_USING_GPIO44)
#define I2C1_GPIO_SCL       GPIO_PIN_44
#endif

#ifdef I2C1_SDA_USING_GPIO26
#define I2C1_GPIO_SDA       GPIO_PIN_1
#elif defined(I2C1_SDA_USING_GPIO3)
#define I2C1_GPIO_SDA       GPIO_PIN_3
#elif defined(I2C1_SDA_USING_GPIO5)
#define I2C1_GPIO_SDA       GPIO_PIN_5
#elif defined(I2C1_SDA_USING_GPIO7)
#define I2C1_GPIO_SDA       GPIO_PIN_7
#elif defined(I2C1_SDA_USING_GPIO9)
#define I2C1_GPIO_SDA       GPIO_PIN_9
#elif defined(I2C1_SDA_USING_GPIO11)
#define I2C1_GPIO_SDA       GPIO_PIN_11
#elif defined(I2C1_SDA_USING_GPIO13)
#define I2C1_GPIO_SDA       GPIO_PIN_13
#elif defined(I2C1_SDA_USING_GPIO15)
#define I2C1_GPIO_SDA       GPIO_PIN_15
#elif defined(I2C1_SDA_USING_GPIO17)
#define I2C1_GPIO_SDA       GPIO_PIN_17
#elif defined(I2C1_SDA_USING_GPIO19)
#define I2C1_GPIO_SDA       GPIO_PIN_19
#elif defined(I2C1_SDA_USING_GPIO21)
#define I2C1_GPIO_SDA       GPIO_PIN_21
#elif defined(I2C1_SDA_USING_GPIO23)
#define I2C1_GPIO_SDA       GPIO_PIN_23
#elif defined(I2C1_SDA_USING_GPIO25)
#define I2C1_GPIO_SDA       GPIO_PIN_25
#elif defined(I2C1_SDA_USING_GPIO27)
#define I2C1_GPIO_SDA       GPIO_PIN_27
#elif defined(I2C1_SDA_USING_GPIO29)
#define I2C1_GPIO_SDA       GPIO_PIN_29
#elif defined(I2C1_SDA_USING_GPIO31)
#define I2C1_GPIO_SDA       GPIO_PIN_31
#elif defined(I2C1_SDA_USING_GPIO33)
#define I2C1_GPIO_SDA       GPIO_PIN_33
#elif defined(I2C1_SDA_USING_GPIO35)
#define I2C1_GPIO_SDA       GPIO_PIN_35
#elif defined(I2C1_SDA_USING_GPIO37)
#define I2C1_GPIO_SDA       GPIO_PIN_37
#elif defined(I2C1_SDA_USING_GPIO39)
#define I2C1_GPIO_SDA       GPIO_PIN_39
#elif defined(I2C1_SDA_USING_GPIO41)
#define I2C1_GPIO_SDA       GPIO_PIN_41
#elif defined(I2C1_SDA_USING_GPIO43)
#define I2C1_GPIO_SDA       GPIO_PIN_43
#elif defined(I2C1_SDA_USING_GPIO45)
#define I2C1_GPIO_SDA       GPIO_PIN_45
#endif

// I2C2
#ifdef I2C2_SCL_USING_GPIO0
#define I2C2_GPIO_SCL       GPIO_PIN_0
#elif defined(I2C2_SCL_USING_GPIO2)
#define I2C2_GPIO_SCL       GPIO_PIN_2
#elif defined(I2C2_SCL_USING_GPIO4)
#define I2C2_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C2_SCL_USING_GPIO6)
#define I2C2_GPIO_SCL       GPIO_PIN_6
#elif defined(I2C2_SCL_USING_GPIO8)
#define I2C2_GPIO_SCL       GPIO_PIN_8
#elif defined(I2C2_SCL_USING_GPIO10)
#define I2C2_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C2_SCL_USING_GPIO12)
#define I2C2_GPIO_SCL       GPIO_PIN_12
#elif defined(I2C2_SCL_USING_GPIO14)
#define I2C2_GPIO_SCL       GPIO_PIN_14
#elif defined(I2C2_SCL_USING_GPIO16)
#define I2C2_GPIO_SCL       GPIO_PIN_16
#elif defined(I2C2_SCL_USING_GPIO18)
#define I2C2_GPIO_SCL       GPIO_PIN_18
#elif defined(I2C2_SCL_USING_GPIO20)
#define I2C2_GPIO_SCL       GPIO_PIN_20
#elif defined(I2C2_SCL_USING_GPIO22)
#define I2C2_GPIO_SCL       GPIO_PIN_22
#elif defined(I2C2_SCL_USING_GPIO24)
#define I2C2_GPIO_SCL       GPIO_PIN_24
#elif defined(I2C2_SCL_USING_GPIO26)
#define I2C2_GPIO_SCL       GPIO_PIN_26
#elif defined(I2C2_SCL_USING_GPIO28)
#define I2C2_GPIO_SCL       GPIO_PIN_28
#elif defined(I2C2_SCL_USING_GPIO30)
#define I2C2_GPIO_SCL       GPIO_PIN_30
#elif defined(I2C2_SCL_USING_GPIO32)
#define I2C2_GPIO_SCL       GPIO_PIN_32
#elif defined(I2C2_SCL_USING_GPIO34)
#define I2C2_GPIO_SCL       GPIO_PIN_34
#elif defined(I2C2_SCL_USING_GPIO36)
#define I2C2_GPIO_SCL       GPIO_PIN_36
#elif defined(I2C2_SCL_USING_GPIO38)
#define I2C2_GPIO_SCL       GPIO_PIN_38
#elif defined(I2C2_SCL_USING_GPIO40)
#define I2C2_GPIO_SCL       GPIO_PIN_40
#elif defined(I2C2_SCL_USING_GPIO42)
#define I2C2_GPIO_SCL       GPIO_PIN_42
#elif defined(I2C2_SCL_USING_GPIO44)
#define I2C2_GPIO_SCL       GPIO_PIN_44
#endif

#ifdef I2C2_SDA_USING_GPIO26
#define I2C2_GPIO_SDA       GPIO_PIN_1
#elif defined(I2C2_SDA_USING_GPIO3)
#define I2C2_GPIO_SDA       GPIO_PIN_3
#elif defined(I2C2_SDA_USING_GPIO5)
#define I2C2_GPIO_SDA       GPIO_PIN_5
#elif defined(I2C2_SDA_USING_GPIO7)
#define I2C2_GPIO_SDA       GPIO_PIN_7
#elif defined(I2C2_SDA_USING_GPIO9)
#define I2C2_GPIO_SDA       GPIO_PIN_9
#elif defined(I2C2_SDA_USING_GPIO11)
#define I2C2_GPIO_SDA       GPIO_PIN_11
#elif defined(I2C2_SDA_USING_GPIO13)
#define I2C2_GPIO_SDA       GPIO_PIN_13
#elif defined(I2C2_SDA_USING_GPIO15)
#define I2C2_GPIO_SDA       GPIO_PIN_15
#elif defined(I2C2_SDA_USING_GPIO17)
#define I2C2_GPIO_SDA       GPIO_PIN_17
#elif defined(I2C2_SDA_USING_GPIO19)
#define I2C2_GPIO_SDA       GPIO_PIN_19
#elif defined(I2C2_SDA_USING_GPIO21)
#define I2C2_GPIO_SDA       GPIO_PIN_21
#elif defined(I2C2_SDA_USING_GPIO23)
#define I2C2_GPIO_SDA       GPIO_PIN_23
#elif defined(I2C2_SDA_USING_GPIO25)
#define I2C2_GPIO_SDA       GPIO_PIN_25
#elif defined(I2C2_SDA_USING_GPIO27)
#define I2C2_GPIO_SDA       GPIO_PIN_27
#elif defined(I2C2_SDA_USING_GPIO29)
#define I2C2_GPIO_SDA       GPIO_PIN_29
#elif defined(I2C2_SDA_USING_GPIO31)
#define I2C2_GPIO_SDA       GPIO_PIN_31
#elif defined(I2C2_SDA_USING_GPIO33)
#define I2C2_GPIO_SDA       GPIO_PIN_33
#elif defined(I2C2_SDA_USING_GPIO35)
#define I2C2_GPIO_SDA       GPIO_PIN_35
#elif defined(I2C2_SDA_USING_GPIO37)
#define I2C2_GPIO_SDA       GPIO_PIN_37
#elif defined(I2C2_SDA_USING_GPIO39)
#define I2C2_GPIO_SDA       GPIO_PIN_39
#elif defined(I2C2_SDA_USING_GPIO41)
#define I2C2_GPIO_SDA       GPIO_PIN_41
#elif defined(I2C2_SDA_USING_GPIO43)
#define I2C2_GPIO_SDA       GPIO_PIN_43
#elif defined(I2C2_SDA_USING_GPIO45)
#define I2C2_GPIO_SDA       GPIO_PIN_45
#endif

// I2C3
#ifdef I2C3_SCL_USING_GPIO0
#define I2C3_GPIO_SCL       GPIO_PIN_0
#elif defined(I2C3_SCL_USING_GPIO2)
#define I2C3_GPIO_SCL       GPIO_PIN_2
#elif defined(I2C3_SCL_USING_GPIO4)
#define I2C3_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C3_SCL_USING_GPIO6)
#define I2C3_GPIO_SCL       GPIO_PIN_6
#elif defined(I2C3_SCL_USING_GPIO8)
#define I2C3_GPIO_SCL       GPIO_PIN_8
#elif defined(I2C3_SCL_USING_GPIO10)
#define I2C3_GPIO_SCL       GPIO_PIN_4
#elif defined(I2C3_SCL_USING_GPIO12)
#define I2C3_GPIO_SCL       GPIO_PIN_12
#elif defined(I2C3_SCL_USING_GPIO14)
#define I2C3_GPIO_SCL       GPIO_PIN_14
#elif defined(I2C3_SCL_USING_GPIO16)
#define I2C3_GPIO_SCL       GPIO_PIN_16
#elif defined(I2C3_SCL_USING_GPIO18)
#define I2C3_GPIO_SCL       GPIO_PIN_18
#elif defined(I2C3_SCL_USING_GPIO20)
#define I2C3_GPIO_SCL       GPIO_PIN_20
#elif defined(I2C3_SCL_USING_GPIO22)
#define I2C3_GPIO_SCL       GPIO_PIN_22
#elif defined(I2C3_SCL_USING_GPIO24)
#define I2C3_GPIO_SCL       GPIO_PIN_24
#elif defined(I2C3_SCL_USING_GPIO26)
#define I2C3_GPIO_SCL       GPIO_PIN_26
#elif defined(I2C3_SCL_USING_GPIO28)
#define I2C3_GPIO_SCL       GPIO_PIN_28
#elif defined(I2C3_SCL_USING_GPIO30)
#define I2C3_GPIO_SCL       GPIO_PIN_30
#elif defined(I2C3_SCL_USING_GPIO32)
#define I2C3_GPIO_SCL       GPIO_PIN_32
#elif defined(I2C3_SCL_USING_GPIO34)
#define I2C3_GPIO_SCL       GPIO_PIN_34
#elif defined(I2C3_SCL_USING_GPIO36)
#define I2C3_GPIO_SCL       GPIO_PIN_36
#elif defined(I2C3_SCL_USING_GPIO38)
#define I2C3_GPIO_SCL       GPIO_PIN_38
#elif defined(I2C3_SCL_USING_GPIO40)
#define I2C3_GPIO_SCL       GPIO_PIN_40
#elif defined(I2C3_SCL_USING_GPIO42)
#define I2C3_GPIO_SCL       GPIO_PIN_42
#elif defined(I2C3_SCL_USING_GPIO44)
#define I2C3_GPIO_SCL       GPIO_PIN_44
#endif

#ifdef I2C3_SDA_USING_GPIO26
#define I2C3_GPIO_SDA       GPIO_PIN_1
#elif defined(I2C3_SDA_USING_GPIO3)
#define I2C3_GPIO_SDA       GPIO_PIN_3
#elif defined(I2C3_SDA_USING_GPIO5)
#define I2C3_GPIO_SDA       GPIO_PIN_5
#elif defined(I2C3_SDA_USING_GPIO7)
#define I2C3_GPIO_SDA       GPIO_PIN_7
#elif defined(I2C3_SDA_USING_GPIO9)
#define I2C3_GPIO_SDA       GPIO_PIN_9
#elif defined(I2C3_SDA_USING_GPIO11)
#define I2C3_GPIO_SDA       GPIO_PIN_11
#elif defined(I2C3_SDA_USING_GPIO13)
#define I2C3_GPIO_SDA       GPIO_PIN_13
#elif defined(I2C3_SDA_USING_GPIO15)
#define I2C3_GPIO_SDA       GPIO_PIN_15
#elif defined(I2C3_SDA_USING_GPIO17)
#define I2C3_GPIO_SDA       GPIO_PIN_17
#elif defined(I2C3_SDA_USING_GPIO19)
#define I2C3_GPIO_SDA       GPIO_PIN_19
#elif defined(I2C3_SDA_USING_GPIO21)
#define I2C3_GPIO_SDA       GPIO_PIN_21
#elif defined(I2C3_SDA_USING_GPIO23)
#define I2C3_GPIO_SDA       GPIO_PIN_23
#elif defined(I2C3_SDA_USING_GPIO25)
#define I2C3_GPIO_SDA       GPIO_PIN_25
#elif defined(I2C3_SDA_USING_GPIO27)
#define I2C3_GPIO_SDA       GPIO_PIN_27
#elif defined(I2C3_SDA_USING_GPIO29)
#define I2C3_GPIO_SDA       GPIO_PIN_29
#elif defined(I2C3_SDA_USING_GPIO31)
#define I2C3_GPIO_SDA       GPIO_PIN_31
#elif defined(I2C3_SDA_USING_GPIO33)
#define I2C3_GPIO_SDA       GPIO_PIN_33
#elif defined(I2C3_SDA_USING_GPIO35)
#define I2C3_GPIO_SDA       GPIO_PIN_35
#elif defined(I2C3_SDA_USING_GPIO37)
#define I2C3_GPIO_SDA       GPIO_PIN_37
#elif defined(I2C3_SDA_USING_GPIO39)
#define I2C3_GPIO_SDA       GPIO_PIN_39
#elif defined(I2C3_SDA_USING_GPIO41)
#define I2C3_GPIO_SDA       GPIO_PIN_41
#elif defined(I2C3_SDA_USING_GPIO43)
#define I2C3_GPIO_SDA       GPIO_PIN_43
#elif defined(I2C3_SDA_USING_GPIO45)
#define I2C3_GPIO_SDA       GPIO_PIN_45
#endif

int rt_hw_i2c_init(void);

#endif /* __DRV_I2C_H__ */
