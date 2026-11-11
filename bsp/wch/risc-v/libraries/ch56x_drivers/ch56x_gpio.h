/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __CH56X_GPIO_H__
#define __CH56X_GPIO_H__

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Fixed linear mapping : 32 pins per port, for ports A,B,C,D...
*/
#define GET_PIN(port,pin)       (GPIO_P##port##_PIN_START + pin)

#ifdef SOC_SERIES_CH569
#define GPIO_INT_PINS { \
        GET_PIN(A,2), GET_PIN(A,3),  GET_PIN(A,4),  GET_PIN(B,3), \
        GET_PIN(B,4), GET_PIN(B,11), GET_PIN(B,12), GET_PIN(B,15) \
        }
#else
#define GPIO_INT_PINS { \
        GET_PIN(A,3),  GET_PIN(A,4),  GET_PIN(A,6), GET_PIN(A,10), \
        GET_PIN(A,11), GET_PIN(A,12), GET_PIN(B,4), GET_PIN(B,10), \
        }
#endif

/*
 * R8_GPIO_INT_FLAG / R8_GPIO_INT_STATUS (CH567,CH568):
 *    write 1 to specific bit to clear int flag
 *
 * R8_GPIO_INT_ENABLE:
 *    To use EXTIx function, pin should be set as input.
 *    For wakeup function, also set RB_SLP_GPIO_WAKE.
 *
 * R8_GPIO_INT_MODE:
 * R8_GPIO_INT_POLAR:
 */
#if defined(SOC_SERIES_CH569)
union _gpio_interrupt
{
    uint8_t reg;
    struct
    {
        uint8_t pa2  : 1;
        uint8_t pa3  : 1;
        uint8_t pa4  : 1;
        uint8_t pb3  : 1;
        uint8_t pb4  : 1;
        uint8_t pb11 : 1;
        uint8_t pb12 : 1;
        uint8_t pb15 : 1;
    };
};

#else

union _gpio_interrupt
{
    uint8_t reg;
    struct
    {
        uint8_t pa3  : 1;
        uint8_t pa4  : 1;
        uint8_t pa6  : 1;
        uint8_t pa10 : 1;
        uint8_t pa11 : 1;
        uint8_t pa12 : 1;
        uint8_t pb4  : 1;
        uint8_t pb10 : 1;
    };
};
#endif

#define GPIO_IE_DISABLE         0
#define GPIO_IE_ENABLE          1

#define GPIO_IM_LEVEL           0
#define GPIO_IM_EDGE            1

#define GPIO_IP_LOW_FALLING     0
#define GPIO_IP_HIGH_RISING     1

/*
 * R8_PIN_ALTERNATE (CH569)  : reset value is 0x01
 * R8_PORT_PIN (CH567/CH568) : reset value is 0x00
 */
union _gpio_pin_alternate
{
    uint8_t reg;
    struct
    {
        uint8_t pin_mii   : 1;  // RW, ETH uses RMII/RGMII (CH565W/CH569W)
        uint8_t pin_tmr1  : 1;  // RW, TMR1/PWM5/CAP1 remapping
        uint8_t pin_tmr2  : 1;  // RW, TMR2/PWM6/CAP2 remapping
        uint8_t resv_3    : 1;
        uint8_t pin_uart0 : 1;  // RW, RXD0/TXD0 remapping
        uint8_t pin_uart1 : 1;  // RW, CH567 only
        uint8_t resv_6    : 2;
    };
};
#define RB_PIN_MII              0x01
#define RB_PIN_TMR1             0x02
#define RB_PIN_TMR2             0x04
#define RB_PIN_UART0            0x10
#define RB_PIN_UART1            0x20

#ifdef SOC_SERIES_CH569
#define GPIO_ALT_RMII           0
#define GPIO_ALT_RGMII          1
#define GPIO_ALT_TMR1_PB15      0
#define GPIO_ALT_TMR1_PB0       1
#define GPIO_ALT_TMR2_PA4       0
#define GPIO_ALT_TMR2_PB3       1
#define GPIO_ALT_UART0_PB5_6    0
#define GPIO_ALT_UART0_PA5_6    1
#else
#define GPIO_ALT_TMR1_PA10      0
#define GPIO_ALT_TMR1_PB2       1
#define GPIO_ALT_TMR2_PA11      0
#define GPIO_ALT_TMR2_PB11      1
#define GPIO_ALT_UART0_PB4_7    0
#define GPIO_ALT_UART0_PA15_14  1
#define GPIO_ALT_UART1_PA8_9    0
#define GPIO_ALT_UART1_PB8_9    1
#endif

struct gpio_px_regs
{
    uint32_t  DIR;  // reset value for pins is 0, input pins
    uint32_t  PIN;  // RO
    uint32_t  OUT;  // reset value is 0
    uint32_t  CLR;  // reset value is 0
    uint32_t  PU;   // reset value is 0
    uint32_t  PD;   // reset value is 0
    uint32_t  DRV;  // reset value for pins is 0, 8mA
    uint32_t  SMT;  // reset value for pins is 1, enable schmitt trigger
} __packed;

CHECK_STRUCT_SIZE(struct gpio_px_regs, 0x20);

#define GPIO_PX_DIR_IN          0
#define GPIO_PX_DIR_OUT         1

#define GPIO_PX_PU_DISABLE      0
#define GPIO_PX_PU_ENABLE       1
#define GPIO_PX_PD_DISABLE      0  // for DIR_IN
#define GPIO_PX_PD_ENABLE       1  // for DIR_IN
#define GPIO_PX_PD_PUSH_PULL    0  // for DIR_OUT
#define GPIO_PX_PD_OPEN_DRAIN   1  // for DIR_OUT

#define GPIO_PX_DRV_8mA         0
#define GPIO_PX_DRV_16mA        1

#define GPIO_PX_SMT_DISABLE     0
#define GPIO_PX_SMT_SLOW        1  // for DIR_OUT
#define GPIO_PX_SMT_ENABLE      1  // for DIR_IN

/*
 * 0x12  R8_PIN_ALTERNATE:   GPIO multi-use remapping register
 * 0x1c  R8_GPIO_INT_FLAG:   GPIO interrupt flag register
 * 0x1d  R8_GPIO_INT_ENABLE: GPIO interrupt enable register
 * 0x1e  R8_GPIO_INT_MODE:   GPIO interrupt mode register
 * 0x1f  R8_GPIO_INT_POLAR:  GPIO interrupt polarity register
 *
 * 0x40  R32_PA_DIR:  PA pin direction control
 * 0x44  R32_PA_PIN:  PA pin input status
 * 0x48  R32_PA_OUT:  PA pin output register
 * 0x4c  R32_PA_CLR:  PA pin output clear
 * 0x50  R32_PA_PU:   PA pin pull-up resistor enable register
 * 0x54  R32_PA_PD:   PA pin open drain output / input pull-down control
 * 0x58  R32_PA_DRV:  PA pin output driving capability register
 * 0x5c  R32_PA_SMT:  PA pin slow output / schmitt trigger input control
 *
 * 0x60  R32_PB_DIR:
 * 0x64  R32_PB_PIN:
 * 0x68  R32_PB_OUT:
 * 0x6c  R32_PB_CLR:
 * 0x70  R32_PB_PU:
 * 0x74  R32_PB_PD:
 * 0x78  R32_PB_DRV:
 * 0x7c  R32_PB_SMT:
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read.
 */
struct gpio_registers
{
    uint32_t                    resv_00[4];
    uint8_t                     resv_10[2];
    union _gpio_pin_alternate   PIN_ALTERNATE;
    uint8_t                     resv_13;
    uint32_t                    resv_14[2];
    union _gpio_interrupt       INT_FLAG;
    union _gpio_interrupt       INT_ENABLE;
    union _gpio_interrupt       INT_MODE;
    union _gpio_interrupt       INT_POLAR;
    uint32_t                    resv_20[8];
    struct gpio_px_regs         PA;
    struct gpio_px_regs         PB;
} __packed;

CHECK_STRUCT_SIZE(struct gpio_registers, 0x80);

#ifdef __cplusplus
}
#endif

#endif
