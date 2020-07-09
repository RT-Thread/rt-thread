/*
 * Copyright (C) 2011-2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
*/

#ifndef _GPIO_DEFINE_H_
#define  _GPIO_DEFINE_H_

#if 0
#define GPIO_DR_OFFSET              0x0000
#define GPIO_GDIR_OFFSET            0x0004
#define GPIO_PSR_OFFSET             0x0008
#endif

typedef enum {
    GPIO_PORT1 = 0,
    GPIO_PORT2 = 1,
    GPIO_PORT3 = 2,
    GPIO_PORT4 = 3,
    GPIO_PORT5 = 4,
    GPIO_PORT6 = 5,
    GPIO_PORT7 = 6,
} GPIO_PORT;

typedef struct {
    unsigned int DR;
    unsigned int GDIR;
    unsigned int PSR;
    unsigned int ICR1;
    unsigned int ICR2;
    unsigned int IMR;
    unsigned int ISR;
    unsigned int EDGE_SEL;
} CSP_GPIO_REGS, *PCSP_GPIO_REGS;

#define GPIO_GDIR_INPUT             0   // GPIO pin is input
#define GPIO_GDIR_OUTPUT            1   // GPIO pin is output

#define GPIO_LOW_LEVEL              0   // GPIO pin is low
#define GPIO_HIGH_LEVEL             1   // GPIO pin is high

#define GPIO_ICR_LOW_LEVEL          0   // Interrupt is low-level
#define GPIO_ICR_HIGH_LEVEL         1   // Interrupt is high-level
#define GPIO_ICR_RISE_EDGE          2   // Interrupt is rising edge
#define GPIO_ICR_FALL_EDGE          3   // Interrupt is falling edge

#define GPIO_IMR_MASKED             0   // Interrupt is masked
#define GPIO_IMR_UNMASKED           1   // Interrupt is unmasked

#define GPIO_EDGE_SEL_DISABLE       0   // Edge select is disabled
#define GPIO_EDGE_SEL_ENABLE        1   // Edge select is enabled

#define GPIO_PIN_MASK(pin)          (1U << (pin))
#define GPIO_PIN_VAL(val, pin)      ((val) << (pin))
#define GPIO_ICR_MASK(pin)          (0x3U << ((pin) << 1))
#define GPIO_ICR_VAL(val, pin)      ((val) << ((pin) << 1))

//#########################################
//# GPIO peripheral defines
//#########################################
#define GPIO_DR0_OFFSET	0x00    //  32bit gpio pta data direction reg
#define GPIO_GDIR0_OFFSET	0x04    //  32bit gpio pta output config 1 reg
#define GPIO_PSR0_OFFSET	0x08    //  32bit gpio pta output config 2 reg
#define GPIO_ICR1_OFFSET	0x0C    //  32bit gpio pta input config A1 reg
#define GPIO_ICR2_OFFSET	0x10    //  32bit gpio pta input config A2 reg
#define GPIO_IMR_OFFSET	0x14    //  32bit gpio pta input config B1 reg
#define GPIO_ISR_OFFSET	0x18    // GPIO Interrupt Status Register
#define GPIO_EDGE_SEL_OFFSET	0x1C    // GPIO Edge Detect Register

#define GPIO1_DR                   GPIO1_BASE_ADDR+0x00
#define GPIO1_GDIR                 GPIO1_BASE_ADDR+0x04
#define GPIO1_PSR                  GPIO1_BASE_ADDR+0x08
#define GPIO1_ICR1                 GPIO1_BASE_ADDR+0x0C
#define GPIO1_ICR2                 GPIO1_BASE_ADDR+0x10
#define GPIO1_IMR                  GPIO1_BASE_ADDR+0x14
#define GPIO1_ISR                  GPIO1_BASE_ADDR+0x18
#define GPIO1_EDGE_SEL             GPIO1_BASE_ADDR+0x1C

#define GPIO2_DR                   GPIO2_BASE_ADDR+0x00
#define GPIO2_GDIR                 GPIO2_BASE_ADDR+0x04
#define GPIO2_PSR                  GPIO2_BASE_ADDR+0x08
#define GPIO2_ICR1                 GPIO2_BASE_ADDR+0x0C
#define GPIO2_ICR2                 GPIO2_BASE_ADDR+0x10
#define GPIO2_IMR                  GPIO2_BASE_ADDR+0x14
#define GPIO2_ISR                  GPIO2_BASE_ADDR+0x18
#define GPIO2_EDGE_SEL             GPIO2_BASE_ADDR+0x1C

#define GPIO3_DR                   GPIO3_BASE_ADDR+0x00
#define GPIO3_GDIR                 GPIO3_BASE_ADDR+0x04
#define GPIO3_PSR                  GPIO3_BASE_ADDR+0x08
#define GPIO3_ICR1                 GPIO3_BASE_ADDR+0x0C
#define GPIO3_ICR2                 GPIO3_BASE_ADDR+0x10
#define GPIO3_IMR                  GPIO3_BASE_ADDR+0x14
#define GPIO3_ISR                  GPIO3_BASE_ADDR+0x18
#define GPIO3_EDGE_SEL             GPIO3_BASE_ADDR+0x1C

#define GPIO4_DR                   GPIO4_BASE_ADDR+0x00
#define GPIO4_GDIR                 GPIO4_BASE_ADDR+0x04
#define GPIO4_PSR                  GPIO4_BASE_ADDR+0x08
#define GPIO4_ICR1                 GPIO4_BASE_ADDR+0x0C
#define GPIO4_ICR2                 GPIO4_BASE_ADDR+0x10
#define GPIO4_IMR                  GPIO4_BASE_ADDR+0x14
#define GPIO4_ISR                  GPIO4_BASE_ADDR+0x18
#define GPIO4_EDGE_SEL             GPIO4_BASE_ADDR+0x1C

#define GPIO5_DR                   GPIO5_BASE_ADDR+0x00
#define GPIO5_GDIR                 GPIO5_BASE_ADDR+0x04
#define GPIO5_PSR                  GPIO5_BASE_ADDR+0x08
#define GPIO5_ICR1                 GPIO5_BASE_ADDR+0x0C
#define GPIO5_ICR2                 GPIO5_BASE_ADDR+0x10
#define GPIO5_IMR                  GPIO5_BASE_ADDR+0x14
#define GPIO5_ISR                  GPIO5_BASE_ADDR+0x18
#define GPIO5_EDGE_SEL             GPIO5_BASE_ADDR+0x1C

#define GPIO6_DR                   GPIO6_BASE_ADDR+0x00
#define GPIO6_GDIR                 GPIO6_BASE_ADDR+0x04
#define GPIO6_PSR                  GPIO6_BASE_ADDR+0x08
#define GPIO6_ICR1                 GPIO6_BASE_ADDR+0x0C
#define GPIO6_ICR2                 GPIO6_BASE_ADDR+0x10
#define GPIO6_IMR                  GPIO6_BASE_ADDR+0x14
#define GPIO6_ISR                  GPIO6_BASE_ADDR+0x18
#define GPIO6_EDGE_SEL             GPIO6_BASE_ADDR+0x1C

#define GPIO7_DR                   GPIO7_BASE_ADDR+0x00
#define GPIO7_GDIR                 GPIO7_BASE_ADDR+0x04
#define GPIO7_PSR                  GPIO7_BASE_ADDR+0x08
#define GPIO7_ICR1                 GPIO7_BASE_ADDR+0x0C
#define GPIO7_ICR2                 GPIO7_BASE_ADDR+0x10
#define GPIO7_IMR                  GPIO7_BASE_ADDR+0x14
#define GPIO7_ISR                  GPIO7_BASE_ADDR+0x18
#define GPIO7_EDGE_SEL             GPIO7_BASE_ADDR+0x1C

#endif
