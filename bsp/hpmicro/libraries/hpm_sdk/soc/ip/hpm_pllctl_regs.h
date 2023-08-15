/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PLLCTL_H
#define HPM_PLLCTL_H

typedef struct {
    __RW uint32_t XTAL;                        /* 0x0: Crystal control and status */
    __R  uint8_t  RESERVED0[124];              /* 0x4 - 0x7F: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x80: PLLx config0 */
        __RW uint32_t CFG1;                    /* 0x84: PLLx config1 */
        __RW uint32_t CFG2;                    /* 0x88: PLLx config2 */
        __RW uint32_t FREQ;                    /* 0x8C: PLLx frac mode frequency adjust */
        __RW uint32_t LOCK;                    /* 0x90: PLLx lock control */
        __R  uint8_t  RESERVED0[12];           /* 0x94 - 0x9F: Reserved */
        __R  uint32_t STATUS;                  /* 0xA0: PLLx status */
        __R  uint8_t  RESERVED1[28];           /* 0xA4 - 0xBF: Reserved */
        __RW uint32_t DIV0;                    /* 0xC0: PLLx divider0 control */
        __RW uint32_t DIV1;                    /* 0xC4: PLLx divider1 control */
        __R  uint8_t  RESERVED2[56];           /* 0xC8 - 0xFF: Reserved */
    } PLL[5];
} PLLCTL_Type;


/* Bitfield definition for register: XTAL */
/*
 * RESPONSE (RO)
 *
 * Crystal oscillator status
 * 0: Oscillator is not stable
 * 1: Oscillator is stable for use
 */
#define PLLCTL_XTAL_RESPONSE_MASK (0x20000000UL)
#define PLLCTL_XTAL_RESPONSE_SHIFT (29U)
#define PLLCTL_XTAL_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTL_XTAL_RESPONSE_MASK) >> PLLCTL_XTAL_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * Crystal oscillator enable status
 * 0: Oscillator is off
 * 1: Oscillator is on
 */
#define PLLCTL_XTAL_ENABLE_MASK (0x10000000UL)
#define PLLCTL_XTAL_ENABLE_SHIFT (28U)
#define PLLCTL_XTAL_ENABLE_GET(x) (((uint32_t)(x) & PLLCTL_XTAL_ENABLE_MASK) >> PLLCTL_XTAL_ENABLE_SHIFT)

/*
 * RAMP_TIME (RW)
 *
 * Rampup time of XTAL oscillator in cycles of IRC24M clock
 * 0: 0 cycle
 * 1: 1 cycle
 * 2: 2 cycle
 * 1048575: 1048575 cycles
 */
#define PLLCTL_XTAL_RAMP_TIME_MASK (0xFFFFFUL)
#define PLLCTL_XTAL_RAMP_TIME_SHIFT (0U)
#define PLLCTL_XTAL_RAMP_TIME_SET(x) (((uint32_t)(x) << PLLCTL_XTAL_RAMP_TIME_SHIFT) & PLLCTL_XTAL_RAMP_TIME_MASK)
#define PLLCTL_XTAL_RAMP_TIME_GET(x) (((uint32_t)(x) & PLLCTL_XTAL_RAMP_TIME_MASK) >> PLLCTL_XTAL_RAMP_TIME_SHIFT)

/* Bitfield definition for register of struct array PLL: CFG0 */
/*
 * SS_RSTPTR (RW)
 *
 * reset pointer, for sscg, lock when lock_en[31]&~pll_ana_pd&~pll_lock_comb
 */
#define PLLCTL_PLL_CFG0_SS_RSTPTR_MASK (0x80000000UL)
#define PLLCTL_PLL_CFG0_SS_RSTPTR_SHIFT (31U)
#define PLLCTL_PLL_CFG0_SS_RSTPTR_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_RSTPTR_SHIFT) & PLLCTL_PLL_CFG0_SS_RSTPTR_MASK)
#define PLLCTL_PLL_CFG0_SS_RSTPTR_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_RSTPTR_MASK) >> PLLCTL_PLL_CFG0_SS_RSTPTR_SHIFT)

/*
 * REFDIV (RW)
 *
 * refclk diverder, lock when lock_en[24]&~pll_ana_pd
 */
#define PLLCTL_PLL_CFG0_REFDIV_MASK (0x3F000000UL)
#define PLLCTL_PLL_CFG0_REFDIV_SHIFT (24U)
#define PLLCTL_PLL_CFG0_REFDIV_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_REFDIV_SHIFT) & PLLCTL_PLL_CFG0_REFDIV_MASK)
#define PLLCTL_PLL_CFG0_REFDIV_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_REFDIV_MASK) >> PLLCTL_PLL_CFG0_REFDIV_SHIFT)

/*
 * POSTDIV1 (RW)
 *
 * lock when lock_en[20]&~pll_ana_pd
 */
#define PLLCTL_PLL_CFG0_POSTDIV1_MASK (0x700000UL)
#define PLLCTL_PLL_CFG0_POSTDIV1_SHIFT (20U)
#define PLLCTL_PLL_CFG0_POSTDIV1_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_POSTDIV1_SHIFT) & PLLCTL_PLL_CFG0_POSTDIV1_MASK)
#define PLLCTL_PLL_CFG0_POSTDIV1_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_POSTDIV1_MASK) >> PLLCTL_PLL_CFG0_POSTDIV1_SHIFT)

/*
 * SS_SPREAD (RW)
 *
 * lock when lock_en[14]&~pll_ana_pd
 */
#define PLLCTL_PLL_CFG0_SS_SPREAD_MASK (0x7C000UL)
#define PLLCTL_PLL_CFG0_SS_SPREAD_SHIFT (14U)
#define PLLCTL_PLL_CFG0_SS_SPREAD_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_SPREAD_SHIFT) & PLLCTL_PLL_CFG0_SS_SPREAD_MASK)
#define PLLCTL_PLL_CFG0_SS_SPREAD_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_SPREAD_MASK) >> PLLCTL_PLL_CFG0_SS_SPREAD_SHIFT)

/*
 * SS_DIVVAL (RW)
 *
 * sscg divval, lock when lock_en[8]&~pll_ana_pd
 */
#define PLLCTL_PLL_CFG0_SS_DIVVAL_MASK (0x3F00U)
#define PLLCTL_PLL_CFG0_SS_DIVVAL_SHIFT (8U)
#define PLLCTL_PLL_CFG0_SS_DIVVAL_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_DIVVAL_SHIFT) & PLLCTL_PLL_CFG0_SS_DIVVAL_MASK)
#define PLLCTL_PLL_CFG0_SS_DIVVAL_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_DIVVAL_MASK) >> PLLCTL_PLL_CFG0_SS_DIVVAL_SHIFT)

/*
 * SS_DOWNSPREAD (RW)
 *
 * Downspread control
 * 1’b0 –> Center-Spread
 * 1’b1 –> Downspread
 */
#define PLLCTL_PLL_CFG0_SS_DOWNSPREAD_MASK (0x80U)
#define PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SHIFT (7U)
#define PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SHIFT) & PLLCTL_PLL_CFG0_SS_DOWNSPREAD_MASK)
#define PLLCTL_PLL_CFG0_SS_DOWNSPREAD_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_DOWNSPREAD_MASK) >> PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SHIFT)

/*
 * SS_RESET (RW)
 *
 */
#define PLLCTL_PLL_CFG0_SS_RESET_MASK (0x40U)
#define PLLCTL_PLL_CFG0_SS_RESET_SHIFT (6U)
#define PLLCTL_PLL_CFG0_SS_RESET_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_RESET_SHIFT) & PLLCTL_PLL_CFG0_SS_RESET_MASK)
#define PLLCTL_PLL_CFG0_SS_RESET_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_RESET_MASK) >> PLLCTL_PLL_CFG0_SS_RESET_SHIFT)

/*
 * SS_DISABLE_SSCG (RW)
 *
 */
#define PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK (0x20U)
#define PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_SHIFT (5U)
#define PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_SHIFT) & PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK)
#define PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK) >> PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_SHIFT)

/*
 * DSMPD (RW)
 *
 * 1: int mode;  0: frac mode
 */
#define PLLCTL_PLL_CFG0_DSMPD_MASK (0x8U)
#define PLLCTL_PLL_CFG0_DSMPD_SHIFT (3U)
#define PLLCTL_PLL_CFG0_DSMPD_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG0_DSMPD_SHIFT) & PLLCTL_PLL_CFG0_DSMPD_MASK)
#define PLLCTL_PLL_CFG0_DSMPD_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG0_DSMPD_MASK) >> PLLCTL_PLL_CFG0_DSMPD_SHIFT)

/* Bitfield definition for register of struct array PLL: CFG1 */
/*
 * PLLCTRL_HW_EN (RW)
 *
 * 1: hardware controll PLL settings, software can update register, but result unknown; suggested only update fbdiv and frac value
 * 0: full software control PLL settings
 */
#define PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK (0x80000000UL)
#define PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_SHIFT (31U)
#define PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_SHIFT) & PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK)
#define PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK) >> PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_SHIFT)

/*
 * CLKEN_SW (RW)
 *
 * the clock enable used to gate pll output, should be set after lock, and clear before power down pll.
 * pll_clock_enable = pllctrl_hw_en ? (pll_lock_comb & enable & pll_clk_enable_chg) : clken_sw;
 */
#define PLLCTL_PLL_CFG1_CLKEN_SW_MASK (0x4000000UL)
#define PLLCTL_PLL_CFG1_CLKEN_SW_SHIFT (26U)
#define PLLCTL_PLL_CFG1_CLKEN_SW_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG1_CLKEN_SW_SHIFT) & PLLCTL_PLL_CFG1_CLKEN_SW_MASK)
#define PLLCTL_PLL_CFG1_CLKEN_SW_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG1_CLKEN_SW_MASK) >> PLLCTL_PLL_CFG1_CLKEN_SW_SHIFT)

/*
 * PLLPD_SW (RW)
 *
 * pll power down.
 * pll_ana_pd = pllctrl_hw_en ? (pll_pd_soc|pll_pd_chg) : pllpd_sw;
 * pll_pd_soc is just delay of soc enable, for soc to control pll on/off;
 * pll_pd_chg is used to power down pll when div_chg_mode is 1, if software update pll parameter(fbdiv or frac), pll_ctrl will power down pll, update parameter, then power up pll. response to soc will not de-asserted at this sequence
 */
#define PLLCTL_PLL_CFG1_PLLPD_SW_MASK (0x2000000UL)
#define PLLCTL_PLL_CFG1_PLLPD_SW_SHIFT (25U)
#define PLLCTL_PLL_CFG1_PLLPD_SW_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG1_PLLPD_SW_SHIFT) & PLLCTL_PLL_CFG1_PLLPD_SW_MASK)
#define PLLCTL_PLL_CFG1_PLLPD_SW_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG1_PLLPD_SW_MASK) >> PLLCTL_PLL_CFG1_PLLPD_SW_SHIFT)

/*
 * LOCK_CNT_CFG (RW)
 *
 * used to wait lock if set larger than lock time;
 * default 1500 24M cycle if refdiv is 1, 4500 cycle if refdiv is 3
 */
#define PLLCTL_PLL_CFG1_LOCK_CNT_CFG_MASK (0x8000U)
#define PLLCTL_PLL_CFG1_LOCK_CNT_CFG_SHIFT (15U)
#define PLLCTL_PLL_CFG1_LOCK_CNT_CFG_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG1_LOCK_CNT_CFG_SHIFT) & PLLCTL_PLL_CFG1_LOCK_CNT_CFG_MASK)
#define PLLCTL_PLL_CFG1_LOCK_CNT_CFG_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG1_LOCK_CNT_CFG_MASK) >> PLLCTL_PLL_CFG1_LOCK_CNT_CFG_SHIFT)

/* Bitfield definition for register of struct array PLL: CFG2 */
/*
 * FBDIV_INT (RW)
 *
 * fbdiv used in int mode
 */
#define PLLCTL_PLL_CFG2_FBDIV_INT_MASK (0xFFFU)
#define PLLCTL_PLL_CFG2_FBDIV_INT_SHIFT (0U)
#define PLLCTL_PLL_CFG2_FBDIV_INT_SET(x) (((uint32_t)(x) << PLLCTL_PLL_CFG2_FBDIV_INT_SHIFT) & PLLCTL_PLL_CFG2_FBDIV_INT_MASK)
#define PLLCTL_PLL_CFG2_FBDIV_INT_GET(x) (((uint32_t)(x) & PLLCTL_PLL_CFG2_FBDIV_INT_MASK) >> PLLCTL_PLL_CFG2_FBDIV_INT_SHIFT)

/* Bitfield definition for register of struct array PLL: FREQ */
/*
 * FRAC (RW)
 *
 * PLL output frequency is :
 * Fout = Fref/refdiv*(fbdiv + frac/2^24)/postdiv1
 * for default refdiv=1 and postdiv1=1, 24MHz refclk
 * Fout is 24*fbdiv in int mode
 * if frac is set to 0x800000, Fout is 24*(fbdiv+0.5)
 * Fout is 24*fbdiv in int mode
 * if frac is set to 0x200000, Fout is 24*(fbdiv+0.125)
 */
#define PLLCTL_PLL_FREQ_FRAC_MASK (0xFFFFFF00UL)
#define PLLCTL_PLL_FREQ_FRAC_SHIFT (8U)
#define PLLCTL_PLL_FREQ_FRAC_SET(x) (((uint32_t)(x) << PLLCTL_PLL_FREQ_FRAC_SHIFT) & PLLCTL_PLL_FREQ_FRAC_MASK)
#define PLLCTL_PLL_FREQ_FRAC_GET(x) (((uint32_t)(x) & PLLCTL_PLL_FREQ_FRAC_MASK) >> PLLCTL_PLL_FREQ_FRAC_SHIFT)

/*
 * FBDIV_FRAC (RW)
 *
 * fbdiv used in frac mode
 */
#define PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK (0xFFU)
#define PLLCTL_PLL_FREQ_FBDIV_FRAC_SHIFT (0U)
#define PLLCTL_PLL_FREQ_FBDIV_FRAC_SET(x) (((uint32_t)(x) << PLLCTL_PLL_FREQ_FBDIV_FRAC_SHIFT) & PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK)
#define PLLCTL_PLL_FREQ_FBDIV_FRAC_GET(x) (((uint32_t)(x) & PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK) >> PLLCTL_PLL_FREQ_FBDIV_FRAC_SHIFT)

/* Bitfield definition for register of struct array PLL: LOCK */
/*
 * LOCK_SS_RSTPTR (RW)
 *
 * lock bit of field ss_rstptr
 * 0: field is open foe software to change
 * 1: field is locked, not changeable
 */
#define PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK (0x80000000UL)
#define PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_SHIFT (31U)
#define PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_SET(x) (((uint32_t)(x) << PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_SHIFT) & PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK)
#define PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_GET(x) (((uint32_t)(x) & PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK) >> PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_SHIFT)

/*
 * LOCK_REFDIV (RW)
 *
 * lock bit of field refdiv
 * 0: field is open foe software to change
 * 1: field is locked, not changeable
 */
#define PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK (0x1000000UL)
#define PLLCTL_PLL_LOCK_LOCK_REFDIV_SHIFT (24U)
#define PLLCTL_PLL_LOCK_LOCK_REFDIV_SET(x) (((uint32_t)(x) << PLLCTL_PLL_LOCK_LOCK_REFDIV_SHIFT) & PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK)
#define PLLCTL_PLL_LOCK_LOCK_REFDIV_GET(x) (((uint32_t)(x) & PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK) >> PLLCTL_PLL_LOCK_LOCK_REFDIV_SHIFT)

/*
 * LOCK_POSTDIV1 (RW)
 *
 * lock bit of field postdiv1
 * 0: field is open foe software to change
 * 1: field is locked, not changeable
 */
#define PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK (0x100000UL)
#define PLLCTL_PLL_LOCK_LOCK_POSTDIV1_SHIFT (20U)
#define PLLCTL_PLL_LOCK_LOCK_POSTDIV1_SET(x) (((uint32_t)(x) << PLLCTL_PLL_LOCK_LOCK_POSTDIV1_SHIFT) & PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK)
#define PLLCTL_PLL_LOCK_LOCK_POSTDIV1_GET(x) (((uint32_t)(x) & PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK) >> PLLCTL_PLL_LOCK_LOCK_POSTDIV1_SHIFT)

/*
 * LOCK_SS_SPEAD (RW)
 *
 * lock bit of field ss_spead
 * 0: field is open foe software to change
 * 1: field is locked, not changeable
 */
#define PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_MASK (0x4000U)
#define PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_SHIFT (14U)
#define PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_SET(x) (((uint32_t)(x) << PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_SHIFT) & PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_MASK)
#define PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_GET(x) (((uint32_t)(x) & PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_MASK) >> PLLCTL_PLL_LOCK_LOCK_SS_SPEAD_SHIFT)

/*
 * LOCK_SS_DIVVAL (RW)
 *
 * lock bit of field ss_divval
 * 0: field is open foe software to change
 * 1: field is locked, not changeable
 */
#define PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK (0x100U)
#define PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_SHIFT (8U)
#define PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_SET(x) (((uint32_t)(x) << PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_SHIFT) & PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK)
#define PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_GET(x) (((uint32_t)(x) & PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK) >> PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_SHIFT)

/* Bitfield definition for register of struct array PLL: STATUS */
/*
 * ENABLE (RO)
 *
 * enable from SYSCTL block
 */
#define PLLCTL_PLL_STATUS_ENABLE_MASK (0x8000000UL)
#define PLLCTL_PLL_STATUS_ENABLE_SHIFT (27U)
#define PLLCTL_PLL_STATUS_ENABLE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_STATUS_ENABLE_MASK) >> PLLCTL_PLL_STATUS_ENABLE_SHIFT)

/*
 * RESPONSE (RO)
 *
 * response to SYSCTL, PLL is power down when both enable and response are 0.
 */
#define PLLCTL_PLL_STATUS_RESPONSE_MASK (0x4U)
#define PLLCTL_PLL_STATUS_RESPONSE_SHIFT (2U)
#define PLLCTL_PLL_STATUS_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_STATUS_RESPONSE_MASK) >> PLLCTL_PLL_STATUS_RESPONSE_SHIFT)

/*
 * PLL_LOCK_COMB (RO)
 *
 */
#define PLLCTL_PLL_STATUS_PLL_LOCK_COMB_MASK (0x2U)
#define PLLCTL_PLL_STATUS_PLL_LOCK_COMB_SHIFT (1U)
#define PLLCTL_PLL_STATUS_PLL_LOCK_COMB_GET(x) (((uint32_t)(x) & PLLCTL_PLL_STATUS_PLL_LOCK_COMB_MASK) >> PLLCTL_PLL_STATUS_PLL_LOCK_COMB_SHIFT)

/*
 * PLL_LOCK_SYNC (RO)
 *
 */
#define PLLCTL_PLL_STATUS_PLL_LOCK_SYNC_MASK (0x1U)
#define PLLCTL_PLL_STATUS_PLL_LOCK_SYNC_SHIFT (0U)
#define PLLCTL_PLL_STATUS_PLL_LOCK_SYNC_GET(x) (((uint32_t)(x) & PLLCTL_PLL_STATUS_PLL_LOCK_SYNC_MASK) >> PLLCTL_PLL_STATUS_PLL_LOCK_SYNC_SHIFT)

/* Bitfield definition for register of struct array PLL: DIV0 */
/*
 * BUSY (RO)
 *
 * Busy flag
 * 0: divider is working
 * 1: divider is changing status
 */
#define PLLCTL_PLL_DIV0_BUSY_MASK (0x80000000UL)
#define PLLCTL_PLL_DIV0_BUSY_SHIFT (31U)
#define PLLCTL_PLL_DIV0_BUSY_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV0_BUSY_MASK) >> PLLCTL_PLL_DIV0_BUSY_SHIFT)

/*
 * RESPONSE (RO)
 *
 * Crystal oscillator status
 * 0: Oscillator is not stable
 * 1: Oscillator is stable for use
 */
#define PLLCTL_PLL_DIV0_RESPONSE_MASK (0x20000000UL)
#define PLLCTL_PLL_DIV0_RESPONSE_SHIFT (29U)
#define PLLCTL_PLL_DIV0_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV0_RESPONSE_MASK) >> PLLCTL_PLL_DIV0_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * Crystal oscillator enable status
 * 0: Oscillator is off
 * 1: Oscillator is on
 */
#define PLLCTL_PLL_DIV0_ENABLE_MASK (0x10000000UL)
#define PLLCTL_PLL_DIV0_ENABLE_SHIFT (28U)
#define PLLCTL_PLL_DIV0_ENABLE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV0_ENABLE_MASK) >> PLLCTL_PLL_DIV0_ENABLE_SHIFT)

/*
 * DIV (RW)
 *
 * Divider
 * 0: divide by 1
 * 1: divide by2
 * . . .
 * 255: divide by 256
 */
#define PLLCTL_PLL_DIV0_DIV_MASK (0xFFU)
#define PLLCTL_PLL_DIV0_DIV_SHIFT (0U)
#define PLLCTL_PLL_DIV0_DIV_SET(x) (((uint32_t)(x) << PLLCTL_PLL_DIV0_DIV_SHIFT) & PLLCTL_PLL_DIV0_DIV_MASK)
#define PLLCTL_PLL_DIV0_DIV_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV0_DIV_MASK) >> PLLCTL_PLL_DIV0_DIV_SHIFT)

/* Bitfield definition for register of struct array PLL: DIV1 */
/*
 * BUSY (RO)
 *
 * Busy flag
 * 0: divider is working
 * 1: divider is changing status
 */
#define PLLCTL_PLL_DIV1_BUSY_MASK (0x80000000UL)
#define PLLCTL_PLL_DIV1_BUSY_SHIFT (31U)
#define PLLCTL_PLL_DIV1_BUSY_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV1_BUSY_MASK) >> PLLCTL_PLL_DIV1_BUSY_SHIFT)

/*
 * RESPONSE (RO)
 *
 * Crystal oscillator status
 * 0: Oscillator is not stable
 * 1: Oscillator is stable for use
 */
#define PLLCTL_PLL_DIV1_RESPONSE_MASK (0x20000000UL)
#define PLLCTL_PLL_DIV1_RESPONSE_SHIFT (29U)
#define PLLCTL_PLL_DIV1_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV1_RESPONSE_MASK) >> PLLCTL_PLL_DIV1_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * Crystal oscillator enable status
 * 0: Oscillator is off
 * 1: Oscillator is on
 */
#define PLLCTL_PLL_DIV1_ENABLE_MASK (0x10000000UL)
#define PLLCTL_PLL_DIV1_ENABLE_SHIFT (28U)
#define PLLCTL_PLL_DIV1_ENABLE_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV1_ENABLE_MASK) >> PLLCTL_PLL_DIV1_ENABLE_SHIFT)

/*
 * DIV (RW)
 *
 * Divider
 * 0: divide by 1
 * 1: divide by2
 * . . .
 * 255: divide by 256
 */
#define PLLCTL_PLL_DIV1_DIV_MASK (0xFFU)
#define PLLCTL_PLL_DIV1_DIV_SHIFT (0U)
#define PLLCTL_PLL_DIV1_DIV_SET(x) (((uint32_t)(x) << PLLCTL_PLL_DIV1_DIV_SHIFT) & PLLCTL_PLL_DIV1_DIV_MASK)
#define PLLCTL_PLL_DIV1_DIV_GET(x) (((uint32_t)(x) & PLLCTL_PLL_DIV1_DIV_MASK) >> PLLCTL_PLL_DIV1_DIV_SHIFT)



/* PLL register group index macro definition */
#define PLLCTL_PLL_PLL0 (0UL)
#define PLLCTL_PLL_PLL1 (1UL)
#define PLLCTL_PLL_PLL2 (2UL)
#define PLLCTL_PLL_PLL3 (3UL)
#define PLLCTL_PLL_PLL4 (4UL)


#endif /* HPM_PLLCTL_H */
