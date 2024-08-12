/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BUTN_H
#define HPM_BUTN_H

typedef struct {
    __RW uint32_t BTN_STATUS;                  /* 0x0: Button status */
    __RW uint32_t BTN_IRQ_MASK;                /* 0x4: Button interrupt mask */
    __RW uint32_t LED_INTENSE;                 /* 0x8: Debounce setting */
} BUTN_Type;


/* Bitfield definition for register: BTN_STATUS */
/*
 * XWCLICK (RW)
 *
 * wake button click status when power button held, write 1 to clear flag
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_STATUS_XWCLICK_MASK (0x70000000UL)
#define BUTN_BTN_STATUS_XWCLICK_SHIFT (28U)
#define BUTN_BTN_STATUS_XWCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_XWCLICK_SHIFT) & BUTN_BTN_STATUS_XWCLICK_MASK)
#define BUTN_BTN_STATUS_XWCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_XWCLICK_MASK) >> BUTN_BTN_STATUS_XWCLICK_SHIFT)

/*
 * WCLICK (RW)
 *
 * wake button click status, write 1 to clear flag
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_STATUS_WCLICK_MASK (0x7000000UL)
#define BUTN_BTN_STATUS_WCLICK_SHIFT (24U)
#define BUTN_BTN_STATUS_WCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_WCLICK_SHIFT) & BUTN_BTN_STATUS_WCLICK_MASK)
#define BUTN_BTN_STATUS_WCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_WCLICK_MASK) >> BUTN_BTN_STATUS_WCLICK_SHIFT)

/*
 * XPCLICK (RW)
 *
 * power button click status when wake button held, write 1 to clear flag
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_STATUS_XPCLICK_MASK (0x700000UL)
#define BUTN_BTN_STATUS_XPCLICK_SHIFT (20U)
#define BUTN_BTN_STATUS_XPCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_XPCLICK_SHIFT) & BUTN_BTN_STATUS_XPCLICK_MASK)
#define BUTN_BTN_STATUS_XPCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_XPCLICK_MASK) >> BUTN_BTN_STATUS_XPCLICK_SHIFT)

/*
 * PCLICK (RW)
 *
 * power button click status, write 1 to clear flag
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_STATUS_PCLICK_MASK (0x70000UL)
#define BUTN_BTN_STATUS_PCLICK_SHIFT (16U)
#define BUTN_BTN_STATUS_PCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_PCLICK_SHIFT) & BUTN_BTN_STATUS_PCLICK_MASK)
#define BUTN_BTN_STATUS_PCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_PCLICK_MASK) >> BUTN_BTN_STATUS_PCLICK_SHIFT)

/*
 * DBTN (RW)
 *
 * Dual button press status, write 1 to clear flag
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_STATUS_DBTN_MASK (0xF00U)
#define BUTN_BTN_STATUS_DBTN_SHIFT (8U)
#define BUTN_BTN_STATUS_DBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_DBTN_SHIFT) & BUTN_BTN_STATUS_DBTN_MASK)
#define BUTN_BTN_STATUS_DBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_DBTN_MASK) >> BUTN_BTN_STATUS_DBTN_SHIFT)

/*
 * WBTN (RW)
 *
 * Wake button press status, write 1 to clear flag
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_STATUS_WBTN_MASK (0xF0U)
#define BUTN_BTN_STATUS_WBTN_SHIFT (4U)
#define BUTN_BTN_STATUS_WBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_WBTN_SHIFT) & BUTN_BTN_STATUS_WBTN_MASK)
#define BUTN_BTN_STATUS_WBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_WBTN_MASK) >> BUTN_BTN_STATUS_WBTN_SHIFT)

/*
 * PBTN (RW)
 *
 * Power button press status, write 1 to clear flag
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_STATUS_PBTN_MASK (0xFU)
#define BUTN_BTN_STATUS_PBTN_SHIFT (0U)
#define BUTN_BTN_STATUS_PBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_STATUS_PBTN_SHIFT) & BUTN_BTN_STATUS_PBTN_MASK)
#define BUTN_BTN_STATUS_PBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_STATUS_PBTN_MASK) >> BUTN_BTN_STATUS_PBTN_SHIFT)

/* Bitfield definition for register: BTN_IRQ_MASK */
/*
 * XWCLICK (RW)
 *
 * wake button click status when power button held interrupt enable
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_IRQ_MASK_XWCLICK_MASK (0x70000000UL)
#define BUTN_BTN_IRQ_MASK_XWCLICK_SHIFT (28U)
#define BUTN_BTN_IRQ_MASK_XWCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_XWCLICK_SHIFT) & BUTN_BTN_IRQ_MASK_XWCLICK_MASK)
#define BUTN_BTN_IRQ_MASK_XWCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_XWCLICK_MASK) >> BUTN_BTN_IRQ_MASK_XWCLICK_SHIFT)

/*
 * WCLICK (RW)
 *
 * wake button click interrupt enable
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_IRQ_MASK_WCLICK_MASK (0x7000000UL)
#define BUTN_BTN_IRQ_MASK_WCLICK_SHIFT (24U)
#define BUTN_BTN_IRQ_MASK_WCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_WCLICK_SHIFT) & BUTN_BTN_IRQ_MASK_WCLICK_MASK)
#define BUTN_BTN_IRQ_MASK_WCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_WCLICK_MASK) >> BUTN_BTN_IRQ_MASK_WCLICK_SHIFT)

/*
 * XPCLICK (RW)
 *
 * power button click status when wake button held interrupt enable
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_IRQ_MASK_XPCLICK_MASK (0x700000UL)
#define BUTN_BTN_IRQ_MASK_XPCLICK_SHIFT (20U)
#define BUTN_BTN_IRQ_MASK_XPCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_XPCLICK_SHIFT) & BUTN_BTN_IRQ_MASK_XPCLICK_MASK)
#define BUTN_BTN_IRQ_MASK_XPCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_XPCLICK_MASK) >> BUTN_BTN_IRQ_MASK_XPCLICK_SHIFT)

/*
 * PCLICK (RW)
 *
 * power button click interrupt enable
 * bit0: clicked
 * bit1: double clicked
 * bit2: tripple clicked
 */
#define BUTN_BTN_IRQ_MASK_PCLICK_MASK (0x70000UL)
#define BUTN_BTN_IRQ_MASK_PCLICK_SHIFT (16U)
#define BUTN_BTN_IRQ_MASK_PCLICK_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_PCLICK_SHIFT) & BUTN_BTN_IRQ_MASK_PCLICK_MASK)
#define BUTN_BTN_IRQ_MASK_PCLICK_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_PCLICK_MASK) >> BUTN_BTN_IRQ_MASK_PCLICK_SHIFT)

/*
 * DBTN (RW)
 *
 * Dual button press interrupt enable
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_IRQ_MASK_DBTN_MASK (0xF00U)
#define BUTN_BTN_IRQ_MASK_DBTN_SHIFT (8U)
#define BUTN_BTN_IRQ_MASK_DBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_DBTN_SHIFT) & BUTN_BTN_IRQ_MASK_DBTN_MASK)
#define BUTN_BTN_IRQ_MASK_DBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_DBTN_MASK) >> BUTN_BTN_IRQ_MASK_DBTN_SHIFT)

/*
 * WBTN (RW)
 *
 * Wake button press interrupt enable
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_IRQ_MASK_WBTN_MASK (0xF0U)
#define BUTN_BTN_IRQ_MASK_WBTN_SHIFT (4U)
#define BUTN_BTN_IRQ_MASK_WBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_WBTN_SHIFT) & BUTN_BTN_IRQ_MASK_WBTN_MASK)
#define BUTN_BTN_IRQ_MASK_WBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_WBTN_MASK) >> BUTN_BTN_IRQ_MASK_WBTN_SHIFT)

/*
 * PBTN (RW)
 *
 * Power button press interrupt enable
 * bit0: button pressed
 * bit1: button confirmd
 * bit2: button long pressed
 * bit3: button long long pressed
 */
#define BUTN_BTN_IRQ_MASK_PBTN_MASK (0xFU)
#define BUTN_BTN_IRQ_MASK_PBTN_SHIFT (0U)
#define BUTN_BTN_IRQ_MASK_PBTN_SET(x) (((uint32_t)(x) << BUTN_BTN_IRQ_MASK_PBTN_SHIFT) & BUTN_BTN_IRQ_MASK_PBTN_MASK)
#define BUTN_BTN_IRQ_MASK_PBTN_GET(x) (((uint32_t)(x) & BUTN_BTN_IRQ_MASK_PBTN_MASK) >> BUTN_BTN_IRQ_MASK_PBTN_SHIFT)

/* Bitfield definition for register: LED_INTENSE */
/*
 * RLED (RW)
 *
 * Rbutton brightness 0
 */
#define BUTN_LED_INTENSE_RLED_MASK (0xF0000UL)
#define BUTN_LED_INTENSE_RLED_SHIFT (16U)
#define BUTN_LED_INTENSE_RLED_SET(x) (((uint32_t)(x) << BUTN_LED_INTENSE_RLED_SHIFT) & BUTN_LED_INTENSE_RLED_MASK)
#define BUTN_LED_INTENSE_RLED_GET(x) (((uint32_t)(x) & BUTN_LED_INTENSE_RLED_MASK) >> BUTN_LED_INTENSE_RLED_SHIFT)

/*
 * PLED (RW)
 *
 * Pbutton brightness 0
 */
#define BUTN_LED_INTENSE_PLED_MASK (0xFU)
#define BUTN_LED_INTENSE_PLED_SHIFT (0U)
#define BUTN_LED_INTENSE_PLED_SET(x) (((uint32_t)(x) << BUTN_LED_INTENSE_PLED_SHIFT) & BUTN_LED_INTENSE_PLED_MASK)
#define BUTN_LED_INTENSE_PLED_GET(x) (((uint32_t)(x) & BUTN_LED_INTENSE_PLED_MASK) >> BUTN_LED_INTENSE_PLED_SHIFT)




#endif /* HPM_BUTN_H */
