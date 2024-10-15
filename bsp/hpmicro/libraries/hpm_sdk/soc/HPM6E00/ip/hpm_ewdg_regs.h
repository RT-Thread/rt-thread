/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_EWDG_H
#define HPM_EWDG_H

typedef struct {
    __RW uint32_t CTRL0;                       /* 0x0: wdog ctrl register 0
Note: Parity check is required once writing to this register. The result should be zero by modular two addition of all bits */
    __RW uint32_t CTRL1;                       /* 0x4: wdog ctrl register 1
Note: Parity check is required once writing to this register. The result should be zero by modular two addition of all bits */
    __RW uint32_t OT_INT_VAL;                  /* 0x8: wdog timeout interrupt counter value */
    __RW uint32_t OT_RST_VAL;                  /* 0xC: wdog timeout reset counter value */
    __W  uint32_t WDT_REFRESH_REG;             /* 0x10: wdog refresh register */
    __W  uint32_t WDT_STATUS;                  /* 0x14: wdog status register */
    __RW uint32_t CFG_PROT;                    /* 0x18: ctrl register protection register */
    __RW uint32_t REF_PROT;                    /* 0x1C: refresh protection register */
    __RW uint32_t WDT_EN;                      /* 0x20: Wdog enable */
    __RW uint32_t REF_TIME;                    /* 0x24: Refresh period value */
} EWDG_Type;


/* Bitfield definition for register: CTRL0 */
/*
 * CLK_SEL (RW)
 *
 * clock select
 * 0：bus clock
 * 1：ext clock
 */
#define EWDG_CTRL0_CLK_SEL_MASK (0x20000000UL)
#define EWDG_CTRL0_CLK_SEL_SHIFT (29U)
#define EWDG_CTRL0_CLK_SEL_SET(x) (((uint32_t)(x) << EWDG_CTRL0_CLK_SEL_SHIFT) & EWDG_CTRL0_CLK_SEL_MASK)
#define EWDG_CTRL0_CLK_SEL_GET(x) (((uint32_t)(x) & EWDG_CTRL0_CLK_SEL_MASK) >> EWDG_CTRL0_CLK_SEL_SHIFT)

/*
 * DIV_VALUE (RW)
 *
 * clock divider, the clock divider works as 2 ^ div_value for wdt counter
 */
#define EWDG_CTRL0_DIV_VALUE_MASK (0xE000000UL)
#define EWDG_CTRL0_DIV_VALUE_SHIFT (25U)
#define EWDG_CTRL0_DIV_VALUE_SET(x) (((uint32_t)(x) << EWDG_CTRL0_DIV_VALUE_SHIFT) & EWDG_CTRL0_DIV_VALUE_MASK)
#define EWDG_CTRL0_DIV_VALUE_GET(x) (((uint32_t)(x) & EWDG_CTRL0_DIV_VALUE_MASK) >> EWDG_CTRL0_DIV_VALUE_SHIFT)

/*
 * WIN_EN (RW)
 *
 * window mode enable
 */
#define EWDG_CTRL0_WIN_EN_MASK (0x1000000UL)
#define EWDG_CTRL0_WIN_EN_SHIFT (24U)
#define EWDG_CTRL0_WIN_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL0_WIN_EN_SHIFT) & EWDG_CTRL0_WIN_EN_MASK)
#define EWDG_CTRL0_WIN_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL0_WIN_EN_MASK) >> EWDG_CTRL0_WIN_EN_SHIFT)

/*
 * WIN_LOWER (RW)
 *
 * Once window mode is opened, the lower counter value to refresh wdt
 * 00: 4/8 overtime value
 * 01: 5/8 of overtime value
 * 10: 6/8 of overtime value
 * 11: 7/8 of overtime value
 */
#define EWDG_CTRL0_WIN_LOWER_MASK (0xC00000UL)
#define EWDG_CTRL0_WIN_LOWER_SHIFT (22U)
#define EWDG_CTRL0_WIN_LOWER_SET(x) (((uint32_t)(x) << EWDG_CTRL0_WIN_LOWER_SHIFT) & EWDG_CTRL0_WIN_LOWER_MASK)
#define EWDG_CTRL0_WIN_LOWER_GET(x) (((uint32_t)(x) & EWDG_CTRL0_WIN_LOWER_MASK) >> EWDG_CTRL0_WIN_LOWER_SHIFT)

/*
 * CFG_LOCK (RW)
 *
 * The register is locked and unlock is needed before re-config registers
 * Once the lock mechanism takes effect, the CTRL0, CTRL1, timeout int register, timeout rst register, needs unlock before re-config them.
 * The register update needs to be finished in the required period defined by UPD_OT_TIME register
 */
#define EWDG_CTRL0_CFG_LOCK_MASK (0x200000UL)
#define EWDG_CTRL0_CFG_LOCK_SHIFT (21U)
#define EWDG_CTRL0_CFG_LOCK_SET(x) (((uint32_t)(x) << EWDG_CTRL0_CFG_LOCK_SHIFT) & EWDG_CTRL0_CFG_LOCK_MASK)
#define EWDG_CTRL0_CFG_LOCK_GET(x) (((uint32_t)(x) & EWDG_CTRL0_CFG_LOCK_MASK) >> EWDG_CTRL0_CFG_LOCK_SHIFT)

/*
 * OT_SELF_CLEAR (RW)
 *
 * overtime reset can be self released after 32 function cycles
 */
#define EWDG_CTRL0_OT_SELF_CLEAR_MASK (0x20000UL)
#define EWDG_CTRL0_OT_SELF_CLEAR_SHIFT (17U)
#define EWDG_CTRL0_OT_SELF_CLEAR_SET(x) (((uint32_t)(x) << EWDG_CTRL0_OT_SELF_CLEAR_SHIFT) & EWDG_CTRL0_OT_SELF_CLEAR_MASK)
#define EWDG_CTRL0_OT_SELF_CLEAR_GET(x) (((uint32_t)(x) & EWDG_CTRL0_OT_SELF_CLEAR_MASK) >> EWDG_CTRL0_OT_SELF_CLEAR_SHIFT)

/*
 * REF_OT_REQ (RW)
 *
 * If refresh event has to be limited into a period after refresh unlocked.
 * Note: the refresh overtime counter works in bus clock domain, not in wdt function clock domain. The wdt divider doesn't take effect for refresh counter
 */
#define EWDG_CTRL0_REF_OT_REQ_MASK (0x8000U)
#define EWDG_CTRL0_REF_OT_REQ_SHIFT (15U)
#define EWDG_CTRL0_REF_OT_REQ_SET(x) (((uint32_t)(x) << EWDG_CTRL0_REF_OT_REQ_SHIFT) & EWDG_CTRL0_REF_OT_REQ_MASK)
#define EWDG_CTRL0_REF_OT_REQ_GET(x) (((uint32_t)(x) & EWDG_CTRL0_REF_OT_REQ_MASK) >> EWDG_CTRL0_REF_OT_REQ_SHIFT)

/*
 * WIN_UPPER (RW)
 *
 * The upper threshold of window value
 * The window period upper limit is: lower_limit + (overtime_rst_value / 16) * upper_reg_value
 * If this register value is zero, then no upper level limitation
 */
#define EWDG_CTRL0_WIN_UPPER_MASK (0x7000U)
#define EWDG_CTRL0_WIN_UPPER_SHIFT (12U)
#define EWDG_CTRL0_WIN_UPPER_SET(x) (((uint32_t)(x) << EWDG_CTRL0_WIN_UPPER_SHIFT) & EWDG_CTRL0_WIN_UPPER_MASK)
#define EWDG_CTRL0_WIN_UPPER_GET(x) (((uint32_t)(x) & EWDG_CTRL0_WIN_UPPER_MASK) >> EWDG_CTRL0_WIN_UPPER_SHIFT)

/*
 * REF_LOCK (RW)
 *
 * WDT refresh has to be unlocked firstly once refresh lock is enable.
 */
#define EWDG_CTRL0_REF_LOCK_MASK (0x20U)
#define EWDG_CTRL0_REF_LOCK_SHIFT (5U)
#define EWDG_CTRL0_REF_LOCK_SET(x) (((uint32_t)(x) << EWDG_CTRL0_REF_LOCK_SHIFT) & EWDG_CTRL0_REF_LOCK_MASK)
#define EWDG_CTRL0_REF_LOCK_GET(x) (((uint32_t)(x) & EWDG_CTRL0_REF_LOCK_MASK) >> EWDG_CTRL0_REF_LOCK_SHIFT)

/*
 * REF_UNLOCK_MEC (RW)
 *
 * Unlock refresh mechanism
 * 00: the required unlock password is the same with refresh_psd_register
 * 01: the required unlock password is a ring shift left value of refresh_psd_register
 * 10: the required unlock password is always 16'h55AA, no matter what refresh_psd_register is
 * 11: the required unlock password is a LSFR result of refresh_psd_register, the characteristic polynomial is X^15 + 1
 */
#define EWDG_CTRL0_REF_UNLOCK_MEC_MASK (0x18U)
#define EWDG_CTRL0_REF_UNLOCK_MEC_SHIFT (3U)
#define EWDG_CTRL0_REF_UNLOCK_MEC_SET(x) (((uint32_t)(x) << EWDG_CTRL0_REF_UNLOCK_MEC_SHIFT) & EWDG_CTRL0_REF_UNLOCK_MEC_MASK)
#define EWDG_CTRL0_REF_UNLOCK_MEC_GET(x) (((uint32_t)(x) & EWDG_CTRL0_REF_UNLOCK_MEC_MASK) >> EWDG_CTRL0_REF_UNLOCK_MEC_SHIFT)

/*
 * EN_DBG (RW)
 *
 * WTD enable or not in debug mode
 */
#define EWDG_CTRL0_EN_DBG_MASK (0x4U)
#define EWDG_CTRL0_EN_DBG_SHIFT (2U)
#define EWDG_CTRL0_EN_DBG_SET(x) (((uint32_t)(x) << EWDG_CTRL0_EN_DBG_SHIFT) & EWDG_CTRL0_EN_DBG_MASK)
#define EWDG_CTRL0_EN_DBG_GET(x) (((uint32_t)(x) & EWDG_CTRL0_EN_DBG_MASK) >> EWDG_CTRL0_EN_DBG_SHIFT)

/*
 * EN_LP (RW)
 *
 * WDT enable or not in low power mode
 * 2'b00: wdt is halted once in low power mode
 * 2'b01: wdt will work with 1/4 normal clock freq in low power mode
 * 2'b10: wdt will work with 1/2 normal clock freq in low power mode
 * 2'b11: wdt will work with normal clock freq in low power mode
 */
#define EWDG_CTRL0_EN_LP_MASK (0x3U)
#define EWDG_CTRL0_EN_LP_SHIFT (0U)
#define EWDG_CTRL0_EN_LP_SET(x) (((uint32_t)(x) << EWDG_CTRL0_EN_LP_SHIFT) & EWDG_CTRL0_EN_LP_MASK)
#define EWDG_CTRL0_EN_LP_GET(x) (((uint32_t)(x) & EWDG_CTRL0_EN_LP_MASK) >> EWDG_CTRL0_EN_LP_SHIFT)

/* Bitfield definition for register: CTRL1 */
/*
 * REF_FAIL_RST_EN (RW)
 *
 * Refresh violation will trigger an reset.
 * These event will be taken as a refresh violation:
 * 1) Not refresh in the window once window mode is enabled
 * 2) Not unlock refresh firstly if unlock is required
 * 3) Not refresh in the required time after unlock, once refresh unlock overtime is enabled.
 * 4) Not write the required word to refresh wdt.
 */
#define EWDG_CTRL1_REF_FAIL_RST_EN_MASK (0x800000UL)
#define EWDG_CTRL1_REF_FAIL_RST_EN_SHIFT (23U)
#define EWDG_CTRL1_REF_FAIL_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_REF_FAIL_RST_EN_SHIFT) & EWDG_CTRL1_REF_FAIL_RST_EN_MASK)
#define EWDG_CTRL1_REF_FAIL_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_REF_FAIL_RST_EN_MASK) >> EWDG_CTRL1_REF_FAIL_RST_EN_SHIFT)

/*
 * REF_FAIL_INT_EN (RW)
 *
 * Refresh violation will trigger an interrupt
 */
#define EWDG_CTRL1_REF_FAIL_INT_EN_MASK (0x400000UL)
#define EWDG_CTRL1_REF_FAIL_INT_EN_SHIFT (22U)
#define EWDG_CTRL1_REF_FAIL_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_REF_FAIL_INT_EN_SHIFT) & EWDG_CTRL1_REF_FAIL_INT_EN_MASK)
#define EWDG_CTRL1_REF_FAIL_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_REF_FAIL_INT_EN_MASK) >> EWDG_CTRL1_REF_FAIL_INT_EN_SHIFT)

/*
 * UNL_REF_FAIL_RST_EN (RW)
 *
 * Refresh unlock fail will trigger a reset
 */
#define EWDG_CTRL1_UNL_REF_FAIL_RST_EN_MASK (0x200000UL)
#define EWDG_CTRL1_UNL_REF_FAIL_RST_EN_SHIFT (21U)
#define EWDG_CTRL1_UNL_REF_FAIL_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_UNL_REF_FAIL_RST_EN_SHIFT) & EWDG_CTRL1_UNL_REF_FAIL_RST_EN_MASK)
#define EWDG_CTRL1_UNL_REF_FAIL_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_UNL_REF_FAIL_RST_EN_MASK) >> EWDG_CTRL1_UNL_REF_FAIL_RST_EN_SHIFT)

/*
 * UNL_REF_FAIL_INT_EN (RW)
 *
 * Refresh unlock fail will trigger a interrupt
 */
#define EWDG_CTRL1_UNL_REF_FAIL_INT_EN_MASK (0x100000UL)
#define EWDG_CTRL1_UNL_REF_FAIL_INT_EN_SHIFT (20U)
#define EWDG_CTRL1_UNL_REF_FAIL_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_UNL_REF_FAIL_INT_EN_SHIFT) & EWDG_CTRL1_UNL_REF_FAIL_INT_EN_MASK)
#define EWDG_CTRL1_UNL_REF_FAIL_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_UNL_REF_FAIL_INT_EN_MASK) >> EWDG_CTRL1_UNL_REF_FAIL_INT_EN_SHIFT)

/*
 * OT_RST_EN (RW)
 *
 * WDT overtime will generate a reset
 */
#define EWDG_CTRL1_OT_RST_EN_MASK (0x20000UL)
#define EWDG_CTRL1_OT_RST_EN_SHIFT (17U)
#define EWDG_CTRL1_OT_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_OT_RST_EN_SHIFT) & EWDG_CTRL1_OT_RST_EN_MASK)
#define EWDG_CTRL1_OT_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_OT_RST_EN_MASK) >> EWDG_CTRL1_OT_RST_EN_SHIFT)

/*
 * OT_INT_EN (RW)
 *
 * WDT can generate an interrupt warning before timeout
 */
#define EWDG_CTRL1_OT_INT_EN_MASK (0x10000UL)
#define EWDG_CTRL1_OT_INT_EN_SHIFT (16U)
#define EWDG_CTRL1_OT_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_OT_INT_EN_SHIFT) & EWDG_CTRL1_OT_INT_EN_MASK)
#define EWDG_CTRL1_OT_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_OT_INT_EN_MASK) >> EWDG_CTRL1_OT_INT_EN_SHIFT)

/*
 * CTL_VIO_RST_EN (RW)
 *
 * Ctrl update violation will trigger a reset
 * The violation event is to try updating the locked register before unlock them
 */
#define EWDG_CTRL1_CTL_VIO_RST_EN_MASK (0x80U)
#define EWDG_CTRL1_CTL_VIO_RST_EN_SHIFT (7U)
#define EWDG_CTRL1_CTL_VIO_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_CTL_VIO_RST_EN_SHIFT) & EWDG_CTRL1_CTL_VIO_RST_EN_MASK)
#define EWDG_CTRL1_CTL_VIO_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_CTL_VIO_RST_EN_MASK) >> EWDG_CTRL1_CTL_VIO_RST_EN_SHIFT)

/*
 * CTL_VIO_INT_EN (RW)
 *
 * Ctrl update violation will trigger a interrupt
 */
#define EWDG_CTRL1_CTL_VIO_INT_EN_MASK (0x40U)
#define EWDG_CTRL1_CTL_VIO_INT_EN_SHIFT (6U)
#define EWDG_CTRL1_CTL_VIO_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_CTL_VIO_INT_EN_SHIFT) & EWDG_CTRL1_CTL_VIO_INT_EN_MASK)
#define EWDG_CTRL1_CTL_VIO_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_CTL_VIO_INT_EN_MASK) >> EWDG_CTRL1_CTL_VIO_INT_EN_SHIFT)

/*
 * UNL_CTL_FAIL_RST_EN (RW)
 *
 * Unlock register update failure will trigger a reset
 */
#define EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_MASK (0x20U)
#define EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_SHIFT (5U)
#define EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_SHIFT) & EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_MASK)
#define EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_MASK) >> EWDG_CTRL1_UNL_CTL_FAIL_RST_EN_SHIFT)

/*
 * UNL_CTL_FAIL_INT_EN (RW)
 *
 * Unlock register update failure will trigger a interrupt
 */
#define EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_MASK (0x10U)
#define EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_SHIFT (4U)
#define EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_SHIFT) & EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_MASK)
#define EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_MASK) >> EWDG_CTRL1_UNL_CTL_FAIL_INT_EN_SHIFT)

/*
 * PARITY_FAIL_RST_EN (RW)
 *
 * Parity error will trigger a reset
 * A parity check is required once writing to ctrl0 and ctrl1 register. The result should be zero by modular two addition of all bits
 */
#define EWDG_CTRL1_PARITY_FAIL_RST_EN_MASK (0x8U)
#define EWDG_CTRL1_PARITY_FAIL_RST_EN_SHIFT (3U)
#define EWDG_CTRL1_PARITY_FAIL_RST_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_PARITY_FAIL_RST_EN_SHIFT) & EWDG_CTRL1_PARITY_FAIL_RST_EN_MASK)
#define EWDG_CTRL1_PARITY_FAIL_RST_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_PARITY_FAIL_RST_EN_MASK) >> EWDG_CTRL1_PARITY_FAIL_RST_EN_SHIFT)

/*
 * PARITY_FAIL_INT_EN (RW)
 *
 * Parity error will trigger a interrupt
 */
#define EWDG_CTRL1_PARITY_FAIL_INT_EN_MASK (0x4U)
#define EWDG_CTRL1_PARITY_FAIL_INT_EN_SHIFT (2U)
#define EWDG_CTRL1_PARITY_FAIL_INT_EN_SET(x) (((uint32_t)(x) << EWDG_CTRL1_PARITY_FAIL_INT_EN_SHIFT) & EWDG_CTRL1_PARITY_FAIL_INT_EN_MASK)
#define EWDG_CTRL1_PARITY_FAIL_INT_EN_GET(x) (((uint32_t)(x) & EWDG_CTRL1_PARITY_FAIL_INT_EN_MASK) >> EWDG_CTRL1_PARITY_FAIL_INT_EN_SHIFT)

/* Bitfield definition for register: OT_INT_VAL */
/*
 * OT_INT_VAL (RW)
 *
 * WDT timeout interrupt value
 */
#define EWDG_OT_INT_VAL_OT_INT_VAL_MASK (0xFFFFU)
#define EWDG_OT_INT_VAL_OT_INT_VAL_SHIFT (0U)
#define EWDG_OT_INT_VAL_OT_INT_VAL_SET(x) (((uint32_t)(x) << EWDG_OT_INT_VAL_OT_INT_VAL_SHIFT) & EWDG_OT_INT_VAL_OT_INT_VAL_MASK)
#define EWDG_OT_INT_VAL_OT_INT_VAL_GET(x) (((uint32_t)(x) & EWDG_OT_INT_VAL_OT_INT_VAL_MASK) >> EWDG_OT_INT_VAL_OT_INT_VAL_SHIFT)

/* Bitfield definition for register: OT_RST_VAL */
/*
 * OT_RST_VAL (RW)
 *
 * WDT timeout reset value
 */
#define EWDG_OT_RST_VAL_OT_RST_VAL_MASK (0xFFFFU)
#define EWDG_OT_RST_VAL_OT_RST_VAL_SHIFT (0U)
#define EWDG_OT_RST_VAL_OT_RST_VAL_SET(x) (((uint32_t)(x) << EWDG_OT_RST_VAL_OT_RST_VAL_SHIFT) & EWDG_OT_RST_VAL_OT_RST_VAL_MASK)
#define EWDG_OT_RST_VAL_OT_RST_VAL_GET(x) (((uint32_t)(x) & EWDG_OT_RST_VAL_OT_RST_VAL_MASK) >> EWDG_OT_RST_VAL_OT_RST_VAL_SHIFT)

/* Bitfield definition for register: WDT_REFRESH_REG */
/*
 * WDT_REFRESH_REG (WO)
 *
 * Write this register by 32'h5A45_524F to refresh wdog
 * Note: Reading this register can read back wdt real time counter value, while it is only used by debug purpose
 */
#define EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_MASK (0xFFFFFFFFUL)
#define EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_SHIFT (0U)
#define EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_SET(x) (((uint32_t)(x) << EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_SHIFT) & EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_MASK)
#define EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_GET(x) (((uint32_t)(x) & EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_MASK) >> EWDG_WDT_REFRESH_REG_WDT_REFRESH_REG_SHIFT)

/* Bitfield definition for register: WDT_STATUS */
/*
 * PARITY_ERROR (W1C)
 *
 * parity error
 * Write one to clear the bit
 */
#define EWDG_WDT_STATUS_PARITY_ERROR_MASK (0x40U)
#define EWDG_WDT_STATUS_PARITY_ERROR_SHIFT (6U)
#define EWDG_WDT_STATUS_PARITY_ERROR_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_PARITY_ERROR_SHIFT) & EWDG_WDT_STATUS_PARITY_ERROR_MASK)
#define EWDG_WDT_STATUS_PARITY_ERROR_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_PARITY_ERROR_MASK) >> EWDG_WDT_STATUS_PARITY_ERROR_SHIFT)

/*
 * OT_RST (W1C)
 *
 * Timeout happens, a reset will happen once enable bit set
 * This bit can be cleared only by refreshing wdt or reset
 */
#define EWDG_WDT_STATUS_OT_RST_MASK (0x20U)
#define EWDG_WDT_STATUS_OT_RST_SHIFT (5U)
#define EWDG_WDT_STATUS_OT_RST_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_OT_RST_SHIFT) & EWDG_WDT_STATUS_OT_RST_MASK)
#define EWDG_WDT_STATUS_OT_RST_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_OT_RST_MASK) >> EWDG_WDT_STATUS_OT_RST_SHIFT)

/*
 * OT_INT (W1C)
 *
 * Timeout happens, a interrupt will happen once enable bit set
 * This bit can be cleared only by refreshing wdt or reset
 */
#define EWDG_WDT_STATUS_OT_INT_MASK (0x10U)
#define EWDG_WDT_STATUS_OT_INT_SHIFT (4U)
#define EWDG_WDT_STATUS_OT_INT_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_OT_INT_SHIFT) & EWDG_WDT_STATUS_OT_INT_MASK)
#define EWDG_WDT_STATUS_OT_INT_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_OT_INT_MASK) >> EWDG_WDT_STATUS_OT_INT_SHIFT)

/*
 * CTL_UNL_FAIL (W1C)
 *
 * Unlock ctrl reg update protection fail
 * Write one to clear the bit
 */
#define EWDG_WDT_STATUS_CTL_UNL_FAIL_MASK (0x8U)
#define EWDG_WDT_STATUS_CTL_UNL_FAIL_SHIFT (3U)
#define EWDG_WDT_STATUS_CTL_UNL_FAIL_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_CTL_UNL_FAIL_SHIFT) & EWDG_WDT_STATUS_CTL_UNL_FAIL_MASK)
#define EWDG_WDT_STATUS_CTL_UNL_FAIL_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_CTL_UNL_FAIL_MASK) >> EWDG_WDT_STATUS_CTL_UNL_FAIL_SHIFT)

/*
 * CTL_VIO (W1C)
 *
 * Violate register update protection mechanism
 * Write one to clear the bit
 */
#define EWDG_WDT_STATUS_CTL_VIO_MASK (0x4U)
#define EWDG_WDT_STATUS_CTL_VIO_SHIFT (2U)
#define EWDG_WDT_STATUS_CTL_VIO_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_CTL_VIO_SHIFT) & EWDG_WDT_STATUS_CTL_VIO_MASK)
#define EWDG_WDT_STATUS_CTL_VIO_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_CTL_VIO_MASK) >> EWDG_WDT_STATUS_CTL_VIO_SHIFT)

/*
 * REF_UNL_FAIL (W1C)
 *
 * Refresh unlock fail
 * Write one to clear the bit
 */
#define EWDG_WDT_STATUS_REF_UNL_FAIL_MASK (0x2U)
#define EWDG_WDT_STATUS_REF_UNL_FAIL_SHIFT (1U)
#define EWDG_WDT_STATUS_REF_UNL_FAIL_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_REF_UNL_FAIL_SHIFT) & EWDG_WDT_STATUS_REF_UNL_FAIL_MASK)
#define EWDG_WDT_STATUS_REF_UNL_FAIL_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_REF_UNL_FAIL_MASK) >> EWDG_WDT_STATUS_REF_UNL_FAIL_SHIFT)

/*
 * REF_VIO (W1C)
 *
 * Refresh fail
 * Write one to clear the bit
 */
#define EWDG_WDT_STATUS_REF_VIO_MASK (0x1U)
#define EWDG_WDT_STATUS_REF_VIO_SHIFT (0U)
#define EWDG_WDT_STATUS_REF_VIO_SET(x) (((uint32_t)(x) << EWDG_WDT_STATUS_REF_VIO_SHIFT) & EWDG_WDT_STATUS_REF_VIO_MASK)
#define EWDG_WDT_STATUS_REF_VIO_GET(x) (((uint32_t)(x) & EWDG_WDT_STATUS_REF_VIO_MASK) >> EWDG_WDT_STATUS_REF_VIO_SHIFT)

/* Bitfield definition for register: CFG_PROT */
/*
 * UPD_OT_TIME (RW)
 *
 * The period in which register update has to be in after unlock
 * The required period is less than： 128 * 2 ^ UPD_OT_TIME * bus_clock_cycle
 */
#define EWDG_CFG_PROT_UPD_OT_TIME_MASK (0xF0000UL)
#define EWDG_CFG_PROT_UPD_OT_TIME_SHIFT (16U)
#define EWDG_CFG_PROT_UPD_OT_TIME_SET(x) (((uint32_t)(x) << EWDG_CFG_PROT_UPD_OT_TIME_SHIFT) & EWDG_CFG_PROT_UPD_OT_TIME_MASK)
#define EWDG_CFG_PROT_UPD_OT_TIME_GET(x) (((uint32_t)(x) & EWDG_CFG_PROT_UPD_OT_TIME_MASK) >> EWDG_CFG_PROT_UPD_OT_TIME_SHIFT)

/*
 * UPD_PSD (RW)
 *
 * The password of unlocking register update
 */
#define EWDG_CFG_PROT_UPD_PSD_MASK (0xFFFFU)
#define EWDG_CFG_PROT_UPD_PSD_SHIFT (0U)
#define EWDG_CFG_PROT_UPD_PSD_SET(x) (((uint32_t)(x) << EWDG_CFG_PROT_UPD_PSD_SHIFT) & EWDG_CFG_PROT_UPD_PSD_MASK)
#define EWDG_CFG_PROT_UPD_PSD_GET(x) (((uint32_t)(x) & EWDG_CFG_PROT_UPD_PSD_MASK) >> EWDG_CFG_PROT_UPD_PSD_SHIFT)

/* Bitfield definition for register: REF_PROT */
/*
 * REF_UNL_PSD (RW)
 *
 * The password to unlock refreshing
 */
#define EWDG_REF_PROT_REF_UNL_PSD_MASK (0xFFFFU)
#define EWDG_REF_PROT_REF_UNL_PSD_SHIFT (0U)
#define EWDG_REF_PROT_REF_UNL_PSD_SET(x) (((uint32_t)(x) << EWDG_REF_PROT_REF_UNL_PSD_SHIFT) & EWDG_REF_PROT_REF_UNL_PSD_MASK)
#define EWDG_REF_PROT_REF_UNL_PSD_GET(x) (((uint32_t)(x) & EWDG_REF_PROT_REF_UNL_PSD_MASK) >> EWDG_REF_PROT_REF_UNL_PSD_SHIFT)

/* Bitfield definition for register: WDT_EN */
/*
 * WDOG_EN (RW)
 *
 * Wdog is enabled, the re-written of this register is impacted by enable lock function
 */
#define EWDG_WDT_EN_WDOG_EN_MASK (0x1U)
#define EWDG_WDT_EN_WDOG_EN_SHIFT (0U)
#define EWDG_WDT_EN_WDOG_EN_SET(x) (((uint32_t)(x) << EWDG_WDT_EN_WDOG_EN_SHIFT) & EWDG_WDT_EN_WDOG_EN_MASK)
#define EWDG_WDT_EN_WDOG_EN_GET(x) (((uint32_t)(x) & EWDG_WDT_EN_WDOG_EN_MASK) >> EWDG_WDT_EN_WDOG_EN_SHIFT)

/* Bitfield definition for register: REF_TIME */
/*
 * REFRESH_PERIOD (RW)
 *
 * The refresh period after refresh unlocked
 * Note: the refresh overtime counter works in bus clock domain, not in wdt function clock domain. The wdt divider doesn't take effect for refresh counter
 */
#define EWDG_REF_TIME_REFRESH_PERIOD_MASK (0xFFFFU)
#define EWDG_REF_TIME_REFRESH_PERIOD_SHIFT (0U)
#define EWDG_REF_TIME_REFRESH_PERIOD_SET(x) (((uint32_t)(x) << EWDG_REF_TIME_REFRESH_PERIOD_SHIFT) & EWDG_REF_TIME_REFRESH_PERIOD_MASK)
#define EWDG_REF_TIME_REFRESH_PERIOD_GET(x) (((uint32_t)(x) & EWDG_REF_TIME_REFRESH_PERIOD_MASK) >> EWDG_REF_TIME_REFRESH_PERIOD_SHIFT)




#endif /* HPM_EWDG_H */
