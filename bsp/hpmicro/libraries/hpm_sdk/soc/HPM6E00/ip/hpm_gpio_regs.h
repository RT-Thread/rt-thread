/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_GPIO_H
#define HPM_GPIO_H

typedef struct {
    struct {
        __R  uint32_t VALUE;                   /* 0x0: GPIO input value */
        __R  uint8_t  RESERVED0[12];           /* 0x4 - 0xF: Reserved */
    } DI[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x100: GPIO output value */
        __RW uint32_t SET;                     /* 0x104: GPIO output set */
        __RW uint32_t CLEAR;                   /* 0x108: GPIO output clear */
        __RW uint32_t TOGGLE;                  /* 0x10C: GPIO output toggle */
    } DO[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x200: GPIO direction value */
        __RW uint32_t SET;                     /* 0x204: GPIO direction set */
        __RW uint32_t CLEAR;                   /* 0x208: GPIO direction clear */
        __RW uint32_t TOGGLE;                  /* 0x20C: GPIO direction toggle */
    } OE[16];
    struct {
        __W  uint32_t VALUE;                   /* 0x300: GPIO interrupt flag value */
        __R  uint8_t  RESERVED0[12];           /* 0x304 - 0x30F: Reserved */
    } IF[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x400: GPIO interrupt enable value */
        __RW uint32_t SET;                     /* 0x404: GPIO interrupt enable set */
        __RW uint32_t CLEAR;                   /* 0x408: GPIO interrupt enable clear */
        __RW uint32_t TOGGLE;                  /* 0x40C: GPIO interrupt enable toggle */
    } IE[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x500: GPIO interrupt polarity value */
        __RW uint32_t SET;                     /* 0x504: GPIO interrupt polarity set */
        __RW uint32_t CLEAR;                   /* 0x508: GPIO interrupt polarity clear */
        __RW uint32_t TOGGLE;                  /* 0x50C: GPIO interrupt polarity toggle */
    } PL[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x600: GPIO interrupt type value */
        __RW uint32_t SET;                     /* 0x604: GPIO interrupt type set */
        __RW uint32_t CLEAR;                   /* 0x608: GPIO interrupt type clear */
        __RW uint32_t TOGGLE;                  /* 0x60C: GPIO interrupt type toggle */
    } TP[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x700: GPIO interrupt asynchronous value */
        __RW uint32_t SET;                     /* 0x704: GPIO interrupt asynchronous set */
        __RW uint32_t CLEAR;                   /* 0x708: GPIO interrupt asynchronous clear */
        __RW uint32_t TOGGLE;                  /* 0x70C: GPIO interrupt asynchronous toggle */
    } AS[16];
    struct {
        __RW uint32_t VALUE;                   /* 0x800: GPIO dual edge interrupt enable value */
        __RW uint32_t SET;                     /* 0x804: GPIO dual edge interrupt enable set */
        __RW uint32_t CLEAR;                   /* 0x808: GPIO dual edge interrupt enable clear */
        __RW uint32_t TOGGLE;                  /* 0x80C: GPIO dual edge interrupt enable toggle */
    } PD[16];
} GPIO_Type;


/* Bitfield definition for register of struct array DI: VALUE */
/*
 * INPUT (RO)
 *
 * GPIO input bus value, each bit represents a bus bit
 * 0: low level presents on chip pin
 * 1: high level presents on chip pin
 */
#define GPIO_DI_VALUE_INPUT_MASK (0xFFFFFFFFUL)
#define GPIO_DI_VALUE_INPUT_SHIFT (0U)
#define GPIO_DI_VALUE_INPUT_GET(x) (((uint32_t)(x) & GPIO_DI_VALUE_INPUT_MASK) >> GPIO_DI_VALUE_INPUT_SHIFT)

/* Bitfield definition for register of struct array DO: VALUE */
/*
 * OUTPUT (RW)
 *
 * GPIO output register value, each bit represents a bus bit
 * 0: chip pin output low level when direction is output
 * 1: chip pin output high level when direction is output
 */
#define GPIO_DO_VALUE_OUTPUT_MASK (0xFFFFFFFFUL)
#define GPIO_DO_VALUE_OUTPUT_SHIFT (0U)
#define GPIO_DO_VALUE_OUTPUT_SET(x) (((uint32_t)(x) << GPIO_DO_VALUE_OUTPUT_SHIFT) & GPIO_DO_VALUE_OUTPUT_MASK)
#define GPIO_DO_VALUE_OUTPUT_GET(x) (((uint32_t)(x) & GPIO_DO_VALUE_OUTPUT_MASK) >> GPIO_DO_VALUE_OUTPUT_SHIFT)

/* Bitfield definition for register of struct array DO: SET */
/*
 * OUTPUT (RW)
 *
 * GPIO output register value, each bit represents a bus bit
 * 0: chip pin output low level when direction is output
 * 1: chip pin output high level when direction is output
 */
#define GPIO_DO_SET_OUTPUT_MASK (0xFFFFFFFFUL)
#define GPIO_DO_SET_OUTPUT_SHIFT (0U)
#define GPIO_DO_SET_OUTPUT_SET(x) (((uint32_t)(x) << GPIO_DO_SET_OUTPUT_SHIFT) & GPIO_DO_SET_OUTPUT_MASK)
#define GPIO_DO_SET_OUTPUT_GET(x) (((uint32_t)(x) & GPIO_DO_SET_OUTPUT_MASK) >> GPIO_DO_SET_OUTPUT_SHIFT)

/* Bitfield definition for register of struct array DO: CLEAR */
/*
 * OUTPUT (RW)
 *
 * GPIO output register value, each bit represents a bus bit
 * 0: chip pin output low level when direction is output
 * 1: chip pin output high level when direction is output
 */
#define GPIO_DO_CLEAR_OUTPUT_MASK (0xFFFFFFFFUL)
#define GPIO_DO_CLEAR_OUTPUT_SHIFT (0U)
#define GPIO_DO_CLEAR_OUTPUT_SET(x) (((uint32_t)(x) << GPIO_DO_CLEAR_OUTPUT_SHIFT) & GPIO_DO_CLEAR_OUTPUT_MASK)
#define GPIO_DO_CLEAR_OUTPUT_GET(x) (((uint32_t)(x) & GPIO_DO_CLEAR_OUTPUT_MASK) >> GPIO_DO_CLEAR_OUTPUT_SHIFT)

/* Bitfield definition for register of struct array DO: TOGGLE */
/*
 * OUTPUT (RW)
 *
 * GPIO output register value, each bit represents a bus bit
 * 0: chip pin output low level when direction is output
 * 1: chip pin output high level when direction is output
 */
#define GPIO_DO_TOGGLE_OUTPUT_MASK (0xFFFFFFFFUL)
#define GPIO_DO_TOGGLE_OUTPUT_SHIFT (0U)
#define GPIO_DO_TOGGLE_OUTPUT_SET(x) (((uint32_t)(x) << GPIO_DO_TOGGLE_OUTPUT_SHIFT) & GPIO_DO_TOGGLE_OUTPUT_MASK)
#define GPIO_DO_TOGGLE_OUTPUT_GET(x) (((uint32_t)(x) & GPIO_DO_TOGGLE_OUTPUT_MASK) >> GPIO_DO_TOGGLE_OUTPUT_SHIFT)

/* Bitfield definition for register of struct array OE: VALUE */
/*
 * DIRECTION (RW)
 *
 * GPIO direction, each bit represents a bus bit
 * 0: input
 * 1: output
 */
#define GPIO_OE_VALUE_DIRECTION_MASK (0xFFFFFFFFUL)
#define GPIO_OE_VALUE_DIRECTION_SHIFT (0U)
#define GPIO_OE_VALUE_DIRECTION_SET(x) (((uint32_t)(x) << GPIO_OE_VALUE_DIRECTION_SHIFT) & GPIO_OE_VALUE_DIRECTION_MASK)
#define GPIO_OE_VALUE_DIRECTION_GET(x) (((uint32_t)(x) & GPIO_OE_VALUE_DIRECTION_MASK) >> GPIO_OE_VALUE_DIRECTION_SHIFT)

/* Bitfield definition for register of struct array OE: SET */
/*
 * DIRECTION (RW)
 *
 * GPIO direction, each bit represents a bus bit
 * 0: input
 * 1: output
 */
#define GPIO_OE_SET_DIRECTION_MASK (0xFFFFFFFFUL)
#define GPIO_OE_SET_DIRECTION_SHIFT (0U)
#define GPIO_OE_SET_DIRECTION_SET(x) (((uint32_t)(x) << GPIO_OE_SET_DIRECTION_SHIFT) & GPIO_OE_SET_DIRECTION_MASK)
#define GPIO_OE_SET_DIRECTION_GET(x) (((uint32_t)(x) & GPIO_OE_SET_DIRECTION_MASK) >> GPIO_OE_SET_DIRECTION_SHIFT)

/* Bitfield definition for register of struct array OE: CLEAR */
/*
 * DIRECTION (RW)
 *
 * GPIO direction, each bit represents a bus bit
 * 0: input
 * 1: output
 */
#define GPIO_OE_CLEAR_DIRECTION_MASK (0xFFFFFFFFUL)
#define GPIO_OE_CLEAR_DIRECTION_SHIFT (0U)
#define GPIO_OE_CLEAR_DIRECTION_SET(x) (((uint32_t)(x) << GPIO_OE_CLEAR_DIRECTION_SHIFT) & GPIO_OE_CLEAR_DIRECTION_MASK)
#define GPIO_OE_CLEAR_DIRECTION_GET(x) (((uint32_t)(x) & GPIO_OE_CLEAR_DIRECTION_MASK) >> GPIO_OE_CLEAR_DIRECTION_SHIFT)

/* Bitfield definition for register of struct array OE: TOGGLE */
/*
 * DIRECTION (RW)
 *
 * GPIO direction, each bit represents a bus bit
 * 0: input
 * 1: output
 */
#define GPIO_OE_TOGGLE_DIRECTION_MASK (0xFFFFFFFFUL)
#define GPIO_OE_TOGGLE_DIRECTION_SHIFT (0U)
#define GPIO_OE_TOGGLE_DIRECTION_SET(x) (((uint32_t)(x) << GPIO_OE_TOGGLE_DIRECTION_SHIFT) & GPIO_OE_TOGGLE_DIRECTION_MASK)
#define GPIO_OE_TOGGLE_DIRECTION_GET(x) (((uint32_t)(x) & GPIO_OE_TOGGLE_DIRECTION_MASK) >> GPIO_OE_TOGGLE_DIRECTION_SHIFT)

/* Bitfield definition for register of struct array IF: VALUE */
/*
 * IRQ_FLAG (W1C)
 *
 * GPIO interrupt flag, write 1 to clear this flag
 * 0: no irq
 * 1: irq pending
 */
#define GPIO_IF_VALUE_IRQ_FLAG_MASK (0xFFFFFFFFUL)
#define GPIO_IF_VALUE_IRQ_FLAG_SHIFT (0U)
#define GPIO_IF_VALUE_IRQ_FLAG_SET(x) (((uint32_t)(x) << GPIO_IF_VALUE_IRQ_FLAG_SHIFT) & GPIO_IF_VALUE_IRQ_FLAG_MASK)
#define GPIO_IF_VALUE_IRQ_FLAG_GET(x) (((uint32_t)(x) & GPIO_IF_VALUE_IRQ_FLAG_MASK) >> GPIO_IF_VALUE_IRQ_FLAG_SHIFT)

/* Bitfield definition for register of struct array IE: VALUE */
/*
 * IRQ_EN (RW)
 *
 * GPIO interrupt enable, each bit represents a bus bit
 * 0: irq is disabled
 * 1: irq is enable
 */
#define GPIO_IE_VALUE_IRQ_EN_MASK (0xFFFFFFFFUL)
#define GPIO_IE_VALUE_IRQ_EN_SHIFT (0U)
#define GPIO_IE_VALUE_IRQ_EN_SET(x) (((uint32_t)(x) << GPIO_IE_VALUE_IRQ_EN_SHIFT) & GPIO_IE_VALUE_IRQ_EN_MASK)
#define GPIO_IE_VALUE_IRQ_EN_GET(x) (((uint32_t)(x) & GPIO_IE_VALUE_IRQ_EN_MASK) >> GPIO_IE_VALUE_IRQ_EN_SHIFT)

/* Bitfield definition for register of struct array IE: SET */
/*
 * IRQ_EN (RW)
 *
 * GPIO interrupt enable, each bit represents a bus bit
 * 0: irq is disabled
 * 1: irq is enable
 */
#define GPIO_IE_SET_IRQ_EN_MASK (0xFFFFFFFFUL)
#define GPIO_IE_SET_IRQ_EN_SHIFT (0U)
#define GPIO_IE_SET_IRQ_EN_SET(x) (((uint32_t)(x) << GPIO_IE_SET_IRQ_EN_SHIFT) & GPIO_IE_SET_IRQ_EN_MASK)
#define GPIO_IE_SET_IRQ_EN_GET(x) (((uint32_t)(x) & GPIO_IE_SET_IRQ_EN_MASK) >> GPIO_IE_SET_IRQ_EN_SHIFT)

/* Bitfield definition for register of struct array IE: CLEAR */
/*
 * IRQ_EN (RW)
 *
 * GPIO interrupt enable, each bit represents a bus bit
 * 0: irq is disabled
 * 1: irq is enable
 */
#define GPIO_IE_CLEAR_IRQ_EN_MASK (0xFFFFFFFFUL)
#define GPIO_IE_CLEAR_IRQ_EN_SHIFT (0U)
#define GPIO_IE_CLEAR_IRQ_EN_SET(x) (((uint32_t)(x) << GPIO_IE_CLEAR_IRQ_EN_SHIFT) & GPIO_IE_CLEAR_IRQ_EN_MASK)
#define GPIO_IE_CLEAR_IRQ_EN_GET(x) (((uint32_t)(x) & GPIO_IE_CLEAR_IRQ_EN_MASK) >> GPIO_IE_CLEAR_IRQ_EN_SHIFT)

/* Bitfield definition for register of struct array IE: TOGGLE */
/*
 * IRQ_EN (RW)
 *
 * GPIO interrupt enable, each bit represents a bus bit
 * 0: irq is disabled
 * 1: irq is enable
 */
#define GPIO_IE_TOGGLE_IRQ_EN_MASK (0xFFFFFFFFUL)
#define GPIO_IE_TOGGLE_IRQ_EN_SHIFT (0U)
#define GPIO_IE_TOGGLE_IRQ_EN_SET(x) (((uint32_t)(x) << GPIO_IE_TOGGLE_IRQ_EN_SHIFT) & GPIO_IE_TOGGLE_IRQ_EN_MASK)
#define GPIO_IE_TOGGLE_IRQ_EN_GET(x) (((uint32_t)(x) & GPIO_IE_TOGGLE_IRQ_EN_MASK) >> GPIO_IE_TOGGLE_IRQ_EN_SHIFT)

/* Bitfield definition for register of struct array PL: VALUE */
/*
 * IRQ_POL (RW)
 *
 * GPIO interrupt polarity, each bit represents a bus bit
 * 0: irq is high level or rising edge
 * 1: irq is low level or falling edge
 */
#define GPIO_PL_VALUE_IRQ_POL_MASK (0xFFFFFFFFUL)
#define GPIO_PL_VALUE_IRQ_POL_SHIFT (0U)
#define GPIO_PL_VALUE_IRQ_POL_SET(x) (((uint32_t)(x) << GPIO_PL_VALUE_IRQ_POL_SHIFT) & GPIO_PL_VALUE_IRQ_POL_MASK)
#define GPIO_PL_VALUE_IRQ_POL_GET(x) (((uint32_t)(x) & GPIO_PL_VALUE_IRQ_POL_MASK) >> GPIO_PL_VALUE_IRQ_POL_SHIFT)

/* Bitfield definition for register of struct array PL: SET */
/*
 * IRQ_POL (RW)
 *
 * GPIO interrupt polarity, each bit represents a bus bit
 * 0: irq is high level or rising edge
 * 1: irq is low level or falling edge
 */
#define GPIO_PL_SET_IRQ_POL_MASK (0xFFFFFFFFUL)
#define GPIO_PL_SET_IRQ_POL_SHIFT (0U)
#define GPIO_PL_SET_IRQ_POL_SET(x) (((uint32_t)(x) << GPIO_PL_SET_IRQ_POL_SHIFT) & GPIO_PL_SET_IRQ_POL_MASK)
#define GPIO_PL_SET_IRQ_POL_GET(x) (((uint32_t)(x) & GPIO_PL_SET_IRQ_POL_MASK) >> GPIO_PL_SET_IRQ_POL_SHIFT)

/* Bitfield definition for register of struct array PL: CLEAR */
/*
 * IRQ_POL (RW)
 *
 * GPIO interrupt polarity, each bit represents a bus bit
 * 0: irq is high level or rising edge
 * 1: irq is low level or falling edge
 */
#define GPIO_PL_CLEAR_IRQ_POL_MASK (0xFFFFFFFFUL)
#define GPIO_PL_CLEAR_IRQ_POL_SHIFT (0U)
#define GPIO_PL_CLEAR_IRQ_POL_SET(x) (((uint32_t)(x) << GPIO_PL_CLEAR_IRQ_POL_SHIFT) & GPIO_PL_CLEAR_IRQ_POL_MASK)
#define GPIO_PL_CLEAR_IRQ_POL_GET(x) (((uint32_t)(x) & GPIO_PL_CLEAR_IRQ_POL_MASK) >> GPIO_PL_CLEAR_IRQ_POL_SHIFT)

/* Bitfield definition for register of struct array PL: TOGGLE */
/*
 * IRQ_POL (RW)
 *
 * GPIO interrupt polarity, each bit represents a bus bit
 * 0: irq is high level or rising edge
 * 1: irq is low level or falling edge
 */
#define GPIO_PL_TOGGLE_IRQ_POL_MASK (0xFFFFFFFFUL)
#define GPIO_PL_TOGGLE_IRQ_POL_SHIFT (0U)
#define GPIO_PL_TOGGLE_IRQ_POL_SET(x) (((uint32_t)(x) << GPIO_PL_TOGGLE_IRQ_POL_SHIFT) & GPIO_PL_TOGGLE_IRQ_POL_MASK)
#define GPIO_PL_TOGGLE_IRQ_POL_GET(x) (((uint32_t)(x) & GPIO_PL_TOGGLE_IRQ_POL_MASK) >> GPIO_PL_TOGGLE_IRQ_POL_SHIFT)

/* Bitfield definition for register of struct array TP: VALUE */
/*
 * IRQ_TYPE (RW)
 *
 * GPIO interrupt type, each bit represents a bus bit
 * 0: irq is triggered by level
 * 1: irq is triggered by edge
 */
#define GPIO_TP_VALUE_IRQ_TYPE_MASK (0xFFFFFFFFUL)
#define GPIO_TP_VALUE_IRQ_TYPE_SHIFT (0U)
#define GPIO_TP_VALUE_IRQ_TYPE_SET(x) (((uint32_t)(x) << GPIO_TP_VALUE_IRQ_TYPE_SHIFT) & GPIO_TP_VALUE_IRQ_TYPE_MASK)
#define GPIO_TP_VALUE_IRQ_TYPE_GET(x) (((uint32_t)(x) & GPIO_TP_VALUE_IRQ_TYPE_MASK) >> GPIO_TP_VALUE_IRQ_TYPE_SHIFT)

/* Bitfield definition for register of struct array TP: SET */
/*
 * IRQ_TYPE (RW)
 *
 * GPIO interrupt type, each bit represents a bus bit
 * 0: irq is triggered by level
 * 1: irq is triggered by edge
 */
#define GPIO_TP_SET_IRQ_TYPE_MASK (0xFFFFFFFFUL)
#define GPIO_TP_SET_IRQ_TYPE_SHIFT (0U)
#define GPIO_TP_SET_IRQ_TYPE_SET(x) (((uint32_t)(x) << GPIO_TP_SET_IRQ_TYPE_SHIFT) & GPIO_TP_SET_IRQ_TYPE_MASK)
#define GPIO_TP_SET_IRQ_TYPE_GET(x) (((uint32_t)(x) & GPIO_TP_SET_IRQ_TYPE_MASK) >> GPIO_TP_SET_IRQ_TYPE_SHIFT)

/* Bitfield definition for register of struct array TP: CLEAR */
/*
 * IRQ_TYPE (RW)
 *
 * GPIO interrupt type, each bit represents a bus bit
 * 0: irq is triggered by level
 * 1: irq is triggered by edge
 */
#define GPIO_TP_CLEAR_IRQ_TYPE_MASK (0xFFFFFFFFUL)
#define GPIO_TP_CLEAR_IRQ_TYPE_SHIFT (0U)
#define GPIO_TP_CLEAR_IRQ_TYPE_SET(x) (((uint32_t)(x) << GPIO_TP_CLEAR_IRQ_TYPE_SHIFT) & GPIO_TP_CLEAR_IRQ_TYPE_MASK)
#define GPIO_TP_CLEAR_IRQ_TYPE_GET(x) (((uint32_t)(x) & GPIO_TP_CLEAR_IRQ_TYPE_MASK) >> GPIO_TP_CLEAR_IRQ_TYPE_SHIFT)

/* Bitfield definition for register of struct array TP: TOGGLE */
/*
 * IRQ_TYPE (RW)
 *
 * GPIO interrupt type, each bit represents a bus bit
 * 0: irq is triggered by level
 * 1: irq is triggered by edge
 */
#define GPIO_TP_TOGGLE_IRQ_TYPE_MASK (0xFFFFFFFFUL)
#define GPIO_TP_TOGGLE_IRQ_TYPE_SHIFT (0U)
#define GPIO_TP_TOGGLE_IRQ_TYPE_SET(x) (((uint32_t)(x) << GPIO_TP_TOGGLE_IRQ_TYPE_SHIFT) & GPIO_TP_TOGGLE_IRQ_TYPE_MASK)
#define GPIO_TP_TOGGLE_IRQ_TYPE_GET(x) (((uint32_t)(x) & GPIO_TP_TOGGLE_IRQ_TYPE_MASK) >> GPIO_TP_TOGGLE_IRQ_TYPE_SHIFT)

/* Bitfield definition for register of struct array AS: VALUE */
/*
 * IRQ_ASYNC (RW)
 *
 * GPIO interrupt asynchronous, each bit represents a bus bit
 * 0: irq is triggered base on system clock
 * 1: irq is triggered combinational
 * Note: combinational interrupt is sensitive to environment noise
 */
#define GPIO_AS_VALUE_IRQ_ASYNC_MASK (0xFFFFFFFFUL)
#define GPIO_AS_VALUE_IRQ_ASYNC_SHIFT (0U)
#define GPIO_AS_VALUE_IRQ_ASYNC_SET(x) (((uint32_t)(x) << GPIO_AS_VALUE_IRQ_ASYNC_SHIFT) & GPIO_AS_VALUE_IRQ_ASYNC_MASK)
#define GPIO_AS_VALUE_IRQ_ASYNC_GET(x) (((uint32_t)(x) & GPIO_AS_VALUE_IRQ_ASYNC_MASK) >> GPIO_AS_VALUE_IRQ_ASYNC_SHIFT)

/* Bitfield definition for register of struct array AS: SET */
/*
 * IRQ_ASYNC (RW)
 *
 * GPIO interrupt asynchronous, each bit represents a bus bit
 * 0: irq is triggered base on system clock
 * 1: irq is triggered combinational
 * Note: combinational interrupt is sensitive to environment noise
 */
#define GPIO_AS_SET_IRQ_ASYNC_MASK (0xFFFFFFFFUL)
#define GPIO_AS_SET_IRQ_ASYNC_SHIFT (0U)
#define GPIO_AS_SET_IRQ_ASYNC_SET(x) (((uint32_t)(x) << GPIO_AS_SET_IRQ_ASYNC_SHIFT) & GPIO_AS_SET_IRQ_ASYNC_MASK)
#define GPIO_AS_SET_IRQ_ASYNC_GET(x) (((uint32_t)(x) & GPIO_AS_SET_IRQ_ASYNC_MASK) >> GPIO_AS_SET_IRQ_ASYNC_SHIFT)

/* Bitfield definition for register of struct array AS: CLEAR */
/*
 * IRQ_ASYNC (RW)
 *
 * GPIO interrupt asynchronous, each bit represents a bus bit
 * 0: irq is triggered base on system clock
 * 1: irq is triggered combinational
 * Note: combinational interrupt is sensitive to environment noise
 */
#define GPIO_AS_CLEAR_IRQ_ASYNC_MASK (0xFFFFFFFFUL)
#define GPIO_AS_CLEAR_IRQ_ASYNC_SHIFT (0U)
#define GPIO_AS_CLEAR_IRQ_ASYNC_SET(x) (((uint32_t)(x) << GPIO_AS_CLEAR_IRQ_ASYNC_SHIFT) & GPIO_AS_CLEAR_IRQ_ASYNC_MASK)
#define GPIO_AS_CLEAR_IRQ_ASYNC_GET(x) (((uint32_t)(x) & GPIO_AS_CLEAR_IRQ_ASYNC_MASK) >> GPIO_AS_CLEAR_IRQ_ASYNC_SHIFT)

/* Bitfield definition for register of struct array AS: TOGGLE */
/*
 * IRQ_ASYNC (RW)
 *
 * GPIO interrupt asynchronous, each bit represents a bus bit
 * 0: irq is triggered base on system clock
 * 1: irq is triggered combinational
 * Note: combinational interrupt is sensitive to environment noise
 */
#define GPIO_AS_TOGGLE_IRQ_ASYNC_MASK (0xFFFFFFFFUL)
#define GPIO_AS_TOGGLE_IRQ_ASYNC_SHIFT (0U)
#define GPIO_AS_TOGGLE_IRQ_ASYNC_SET(x) (((uint32_t)(x) << GPIO_AS_TOGGLE_IRQ_ASYNC_SHIFT) & GPIO_AS_TOGGLE_IRQ_ASYNC_MASK)
#define GPIO_AS_TOGGLE_IRQ_ASYNC_GET(x) (((uint32_t)(x) & GPIO_AS_TOGGLE_IRQ_ASYNC_MASK) >> GPIO_AS_TOGGLE_IRQ_ASYNC_SHIFT)

/* Bitfield definition for register of struct array PD: VALUE */
/*
 * IRQ_DUAL (RW)
 *
 * GPIO dual edge interrupt enable
 * 0: single edge interrupt
 * 1: dual edge interrupt enable
 */
#define GPIO_PD_VALUE_IRQ_DUAL_MASK (0x1U)
#define GPIO_PD_VALUE_IRQ_DUAL_SHIFT (0U)
#define GPIO_PD_VALUE_IRQ_DUAL_SET(x) (((uint32_t)(x) << GPIO_PD_VALUE_IRQ_DUAL_SHIFT) & GPIO_PD_VALUE_IRQ_DUAL_MASK)
#define GPIO_PD_VALUE_IRQ_DUAL_GET(x) (((uint32_t)(x) & GPIO_PD_VALUE_IRQ_DUAL_MASK) >> GPIO_PD_VALUE_IRQ_DUAL_SHIFT)

/* Bitfield definition for register of struct array PD: SET */
/*
 * IRQ_DUAL (RW)
 *
 * GPIO dual edge interrupt enable set
 * 0: keep original edge interrupt type
 * 1: dual edge interrupt enable
 */
#define GPIO_PD_SET_IRQ_DUAL_MASK (0x1U)
#define GPIO_PD_SET_IRQ_DUAL_SHIFT (0U)
#define GPIO_PD_SET_IRQ_DUAL_SET(x) (((uint32_t)(x) << GPIO_PD_SET_IRQ_DUAL_SHIFT) & GPIO_PD_SET_IRQ_DUAL_MASK)
#define GPIO_PD_SET_IRQ_DUAL_GET(x) (((uint32_t)(x) & GPIO_PD_SET_IRQ_DUAL_MASK) >> GPIO_PD_SET_IRQ_DUAL_SHIFT)

/* Bitfield definition for register of struct array PD: CLEAR */
/*
 * IRQ_DUAL (RW)
 *
 * GPIO dual edge interrupt enable clear
 * 0: keep original edge interrupt type
 * 1: single edge interrupt enable
 */
#define GPIO_PD_CLEAR_IRQ_DUAL_MASK (0x1U)
#define GPIO_PD_CLEAR_IRQ_DUAL_SHIFT (0U)
#define GPIO_PD_CLEAR_IRQ_DUAL_SET(x) (((uint32_t)(x) << GPIO_PD_CLEAR_IRQ_DUAL_SHIFT) & GPIO_PD_CLEAR_IRQ_DUAL_MASK)
#define GPIO_PD_CLEAR_IRQ_DUAL_GET(x) (((uint32_t)(x) & GPIO_PD_CLEAR_IRQ_DUAL_MASK) >> GPIO_PD_CLEAR_IRQ_DUAL_SHIFT)

/* Bitfield definition for register of struct array PD: TOGGLE */
/*
 * IRQ_DUAL (RW)
 *
 * GPIO dual edge interrupt enable toggle
 * 0: keep original edge interrupt type
 * 1: change original edge interrupt type to another one.
 */
#define GPIO_PD_TOGGLE_IRQ_DUAL_MASK (0x1U)
#define GPIO_PD_TOGGLE_IRQ_DUAL_SHIFT (0U)
#define GPIO_PD_TOGGLE_IRQ_DUAL_SET(x) (((uint32_t)(x) << GPIO_PD_TOGGLE_IRQ_DUAL_SHIFT) & GPIO_PD_TOGGLE_IRQ_DUAL_MASK)
#define GPIO_PD_TOGGLE_IRQ_DUAL_GET(x) (((uint32_t)(x) & GPIO_PD_TOGGLE_IRQ_DUAL_MASK) >> GPIO_PD_TOGGLE_IRQ_DUAL_SHIFT)



/* DI register group index macro definition */
#define GPIO_DI_GPIOA (0UL)
#define GPIO_DI_GPIOB (1UL)
#define GPIO_DI_GPIOC (2UL)
#define GPIO_DI_GPIOD (3UL)
#define GPIO_DI_GPIOE (4UL)
#define GPIO_DI_GPIOF (5UL)
#define GPIO_DI_GPIOV (11UL)
#define GPIO_DI_GPIOW (12UL)
#define GPIO_DI_GPIOX (13UL)
#define GPIO_DI_GPIOY (14UL)
#define GPIO_DI_GPIOZ (15UL)

/* DO register group index macro definition */
#define GPIO_DO_GPIOA (0UL)
#define GPIO_DO_GPIOB (1UL)
#define GPIO_DO_GPIOC (2UL)
#define GPIO_DO_GPIOD (3UL)
#define GPIO_DO_GPIOE (4UL)
#define GPIO_DO_GPIOF (5UL)
#define GPIO_DO_GPIOV (11UL)
#define GPIO_DO_GPIOW (12UL)
#define GPIO_DO_GPIOX (13UL)
#define GPIO_DO_GPIOY (14UL)
#define GPIO_DO_GPIOZ (15UL)

/* OE register group index macro definition */
#define GPIO_OE_GPIOA (0UL)
#define GPIO_OE_GPIOB (1UL)
#define GPIO_OE_GPIOC (2UL)
#define GPIO_OE_GPIOD (3UL)
#define GPIO_OE_GPIOE (4UL)
#define GPIO_OE_GPIOF (5UL)
#define GPIO_OE_GPIOV (11UL)
#define GPIO_OE_GPIOW (12UL)
#define GPIO_OE_GPIOX (13UL)
#define GPIO_OE_GPIOY (14UL)
#define GPIO_OE_GPIOZ (15UL)

/* IF register group index macro definition */
#define GPIO_IF_GPIOA (0UL)
#define GPIO_IF_GPIOB (1UL)
#define GPIO_IF_GPIOC (2UL)
#define GPIO_IF_GPIOD (3UL)
#define GPIO_IF_GPIOE (4UL)
#define GPIO_IF_GPIOF (5UL)
#define GPIO_IF_GPIOV (11UL)
#define GPIO_IF_GPIOW (12UL)
#define GPIO_IF_GPIOX (13UL)
#define GPIO_IF_GPIOY (14UL)
#define GPIO_IF_GPIOZ (15UL)

/* IE register group index macro definition */
#define GPIO_IE_GPIOA (0UL)
#define GPIO_IE_GPIOB (1UL)
#define GPIO_IE_GPIOC (2UL)
#define GPIO_IE_GPIOD (3UL)
#define GPIO_IE_GPIOE (4UL)
#define GPIO_IE_GPIOF (5UL)
#define GPIO_IE_GPIOV (11UL)
#define GPIO_IE_GPIOW (12UL)
#define GPIO_IE_GPIOX (13UL)
#define GPIO_IE_GPIOY (14UL)
#define GPIO_IE_GPIOZ (15UL)

/* PL register group index macro definition */
#define GPIO_PL_GPIOA (0UL)
#define GPIO_PL_GPIOB (1UL)
#define GPIO_PL_GPIOC (2UL)
#define GPIO_PL_GPIOD (3UL)
#define GPIO_PL_GPIOE (4UL)
#define GPIO_PL_GPIOF (5UL)
#define GPIO_PL_GPIOV (11UL)
#define GPIO_PL_GPIOW (12UL)
#define GPIO_PL_GPIOX (13UL)
#define GPIO_PL_GPIOY (14UL)
#define GPIO_PL_GPIOZ (15UL)

/* TP register group index macro definition */
#define GPIO_TP_GPIOA (0UL)
#define GPIO_TP_GPIOB (1UL)
#define GPIO_TP_GPIOC (2UL)
#define GPIO_TP_GPIOD (3UL)
#define GPIO_TP_GPIOE (4UL)
#define GPIO_TP_GPIOF (5UL)
#define GPIO_TP_GPIOV (11UL)
#define GPIO_TP_GPIOW (12UL)
#define GPIO_TP_GPIOX (13UL)
#define GPIO_TP_GPIOY (14UL)
#define GPIO_TP_GPIOZ (15UL)

/* AS register group index macro definition */
#define GPIO_AS_GPIOA (0UL)
#define GPIO_AS_GPIOB (1UL)
#define GPIO_AS_GPIOC (2UL)
#define GPIO_AS_GPIOD (3UL)
#define GPIO_AS_GPIOE (4UL)
#define GPIO_AS_GPIOF (5UL)
#define GPIO_AS_GPIOV (11UL)
#define GPIO_AS_GPIOW (12UL)
#define GPIO_AS_GPIOX (13UL)
#define GPIO_AS_GPIOY (14UL)
#define GPIO_AS_GPIOZ (15UL)

/* PD register group index macro definition */
#define GPIO_PD_GPIOA (0UL)
#define GPIO_PD_GPIOB (1UL)
#define GPIO_PD_GPIOC (2UL)
#define GPIO_PD_GPIOD (3UL)
#define GPIO_PD_GPIOE (4UL)
#define GPIO_PD_GPIOF (5UL)
#define GPIO_PD_GPIOV (11UL)
#define GPIO_PD_GPIOW (12UL)
#define GPIO_PD_GPIOX (13UL)
#define GPIO_PD_GPIOY (14UL)
#define GPIO_PD_GPIOZ (15UL)


#endif /* HPM_GPIO_H */
