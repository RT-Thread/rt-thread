/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BCFG_H
#define HPM_BCFG_H

typedef struct {
    __RW uint32_t VBG_CFG;                     /* 0x0: Bandgap config */
    __R  uint8_t  RESERVED0[4];                /* 0x4 - 0x7: Reserved */
    __RW uint32_t IRC32K_CFG;                  /* 0x8: On-chip 32k oscillator config */
    __RW uint32_t XTAL32K_CFG;                 /* 0xC: XTAL 32K config */
    __RW uint32_t CLK_CFG;                     /* 0x10: Clock config */
} BCFG_Type;


/* Bitfield definition for register: VBG_CFG */
/*
 * VBG_TRIMMED (RW)
 *
 * Bandgap trim happened, this bit set by hardware after trim value loaded, and stop load, write 0 will clear this bit and reload trim value
 * 0: bandgap is not trimmed
 * 1: bandgap is trimmed
 */
#define BCFG_VBG_CFG_VBG_TRIMMED_MASK (0x80000000UL)
#define BCFG_VBG_CFG_VBG_TRIMMED_SHIFT (31U)
#define BCFG_VBG_CFG_VBG_TRIMMED_SET(x) (((uint32_t)(x) << BCFG_VBG_CFG_VBG_TRIMMED_SHIFT) & BCFG_VBG_CFG_VBG_TRIMMED_MASK)
#define BCFG_VBG_CFG_VBG_TRIMMED_GET(x) (((uint32_t)(x) & BCFG_VBG_CFG_VBG_TRIMMED_MASK) >> BCFG_VBG_CFG_VBG_TRIMMED_SHIFT)

/*
 * POWER_SAVE (RW)
 *
 * Bandgap works in power save mode
 * 0: not in power save mode
 * 1: bandgap work in power save mode
 */
#define BCFG_VBG_CFG_POWER_SAVE_MASK (0x1000000UL)
#define BCFG_VBG_CFG_POWER_SAVE_SHIFT (24U)
#define BCFG_VBG_CFG_POWER_SAVE_SET(x) (((uint32_t)(x) << BCFG_VBG_CFG_POWER_SAVE_SHIFT) & BCFG_VBG_CFG_POWER_SAVE_MASK)
#define BCFG_VBG_CFG_POWER_SAVE_GET(x) (((uint32_t)(x) & BCFG_VBG_CFG_POWER_SAVE_MASK) >> BCFG_VBG_CFG_POWER_SAVE_SHIFT)

/*
 * VBG_1P0 (RW)
 *
 * Bandgap 1.0V output trim
 */
#define BCFG_VBG_CFG_VBG_1P0_MASK (0x1F0000UL)
#define BCFG_VBG_CFG_VBG_1P0_SHIFT (16U)
#define BCFG_VBG_CFG_VBG_1P0_SET(x) (((uint32_t)(x) << BCFG_VBG_CFG_VBG_1P0_SHIFT) & BCFG_VBG_CFG_VBG_1P0_MASK)
#define BCFG_VBG_CFG_VBG_1P0_GET(x) (((uint32_t)(x) & BCFG_VBG_CFG_VBG_1P0_MASK) >> BCFG_VBG_CFG_VBG_1P0_SHIFT)

/*
 * VBG_P65 (RW)
 *
 * Bandgap 0.65V output trim
 */
#define BCFG_VBG_CFG_VBG_P65_MASK (0x1F00U)
#define BCFG_VBG_CFG_VBG_P65_SHIFT (8U)
#define BCFG_VBG_CFG_VBG_P65_SET(x) (((uint32_t)(x) << BCFG_VBG_CFG_VBG_P65_SHIFT) & BCFG_VBG_CFG_VBG_P65_MASK)
#define BCFG_VBG_CFG_VBG_P65_GET(x) (((uint32_t)(x) & BCFG_VBG_CFG_VBG_P65_MASK) >> BCFG_VBG_CFG_VBG_P65_SHIFT)

/*
 * VBG_P50 (RW)
 *
 * Bandgap 0.50V output trim
 */
#define BCFG_VBG_CFG_VBG_P50_MASK (0x1FU)
#define BCFG_VBG_CFG_VBG_P50_SHIFT (0U)
#define BCFG_VBG_CFG_VBG_P50_SET(x) (((uint32_t)(x) << BCFG_VBG_CFG_VBG_P50_SHIFT) & BCFG_VBG_CFG_VBG_P50_MASK)
#define BCFG_VBG_CFG_VBG_P50_GET(x) (((uint32_t)(x) & BCFG_VBG_CFG_VBG_P50_MASK) >> BCFG_VBG_CFG_VBG_P50_SHIFT)

/* Bitfield definition for register: IRC32K_CFG */
/*
 * IRC_TRIMMED (RW)
 *
 * IRC32K trim happened, this bit set by hardware after trim value loaded, and stop load, write 0 will clear this bit and reload trim value
 * 0: irc is not trimmed
 * 1: irc is trimmed
 */
#define BCFG_IRC32K_CFG_IRC_TRIMMED_MASK (0x80000000UL)
#define BCFG_IRC32K_CFG_IRC_TRIMMED_SHIFT (31U)
#define BCFG_IRC32K_CFG_IRC_TRIMMED_SET(x) (((uint32_t)(x) << BCFG_IRC32K_CFG_IRC_TRIMMED_SHIFT) & BCFG_IRC32K_CFG_IRC_TRIMMED_MASK)
#define BCFG_IRC32K_CFG_IRC_TRIMMED_GET(x) (((uint32_t)(x) & BCFG_IRC32K_CFG_IRC_TRIMMED_MASK) >> BCFG_IRC32K_CFG_IRC_TRIMMED_SHIFT)

/*
 * CAPEX7_TRIM (RW)
 *
 * IRC32K bit 7
 */
#define BCFG_IRC32K_CFG_CAPEX7_TRIM_MASK (0x800000UL)
#define BCFG_IRC32K_CFG_CAPEX7_TRIM_SHIFT (23U)
#define BCFG_IRC32K_CFG_CAPEX7_TRIM_SET(x) (((uint32_t)(x) << BCFG_IRC32K_CFG_CAPEX7_TRIM_SHIFT) & BCFG_IRC32K_CFG_CAPEX7_TRIM_MASK)
#define BCFG_IRC32K_CFG_CAPEX7_TRIM_GET(x) (((uint32_t)(x) & BCFG_IRC32K_CFG_CAPEX7_TRIM_MASK) >> BCFG_IRC32K_CFG_CAPEX7_TRIM_SHIFT)

/*
 * CAPEX6_TRIM (RW)
 *
 * IRC32K bit 6
 */
#define BCFG_IRC32K_CFG_CAPEX6_TRIM_MASK (0x400000UL)
#define BCFG_IRC32K_CFG_CAPEX6_TRIM_SHIFT (22U)
#define BCFG_IRC32K_CFG_CAPEX6_TRIM_SET(x) (((uint32_t)(x) << BCFG_IRC32K_CFG_CAPEX6_TRIM_SHIFT) & BCFG_IRC32K_CFG_CAPEX6_TRIM_MASK)
#define BCFG_IRC32K_CFG_CAPEX6_TRIM_GET(x) (((uint32_t)(x) & BCFG_IRC32K_CFG_CAPEX6_TRIM_MASK) >> BCFG_IRC32K_CFG_CAPEX6_TRIM_SHIFT)

/*
 * CAP_TRIM (RW)
 *
 * capacitor trim bits
 */
#define BCFG_IRC32K_CFG_CAP_TRIM_MASK (0x1FFU)
#define BCFG_IRC32K_CFG_CAP_TRIM_SHIFT (0U)
#define BCFG_IRC32K_CFG_CAP_TRIM_SET(x) (((uint32_t)(x) << BCFG_IRC32K_CFG_CAP_TRIM_SHIFT) & BCFG_IRC32K_CFG_CAP_TRIM_MASK)
#define BCFG_IRC32K_CFG_CAP_TRIM_GET(x) (((uint32_t)(x) & BCFG_IRC32K_CFG_CAP_TRIM_MASK) >> BCFG_IRC32K_CFG_CAP_TRIM_SHIFT)

/* Bitfield definition for register: XTAL32K_CFG */
/*
 * HYST_EN (RW)
 *
 * crystal 32k hysteres enable
 */
#define BCFG_XTAL32K_CFG_HYST_EN_MASK (0x1000U)
#define BCFG_XTAL32K_CFG_HYST_EN_SHIFT (12U)
#define BCFG_XTAL32K_CFG_HYST_EN_SET(x) (((uint32_t)(x) << BCFG_XTAL32K_CFG_HYST_EN_SHIFT) & BCFG_XTAL32K_CFG_HYST_EN_MASK)
#define BCFG_XTAL32K_CFG_HYST_EN_GET(x) (((uint32_t)(x) & BCFG_XTAL32K_CFG_HYST_EN_MASK) >> BCFG_XTAL32K_CFG_HYST_EN_SHIFT)

/*
 * GMSEL (RW)
 *
 * crystal 32k gm selection
 */
#define BCFG_XTAL32K_CFG_GMSEL_MASK (0x300U)
#define BCFG_XTAL32K_CFG_GMSEL_SHIFT (8U)
#define BCFG_XTAL32K_CFG_GMSEL_SET(x) (((uint32_t)(x) << BCFG_XTAL32K_CFG_GMSEL_SHIFT) & BCFG_XTAL32K_CFG_GMSEL_MASK)
#define BCFG_XTAL32K_CFG_GMSEL_GET(x) (((uint32_t)(x) & BCFG_XTAL32K_CFG_GMSEL_MASK) >> BCFG_XTAL32K_CFG_GMSEL_SHIFT)

/*
 * CFG (RW)
 *
 * crystal 32k config
 */
#define BCFG_XTAL32K_CFG_CFG_MASK (0x10U)
#define BCFG_XTAL32K_CFG_CFG_SHIFT (4U)
#define BCFG_XTAL32K_CFG_CFG_SET(x) (((uint32_t)(x) << BCFG_XTAL32K_CFG_CFG_SHIFT) & BCFG_XTAL32K_CFG_CFG_MASK)
#define BCFG_XTAL32K_CFG_CFG_GET(x) (((uint32_t)(x) & BCFG_XTAL32K_CFG_CFG_MASK) >> BCFG_XTAL32K_CFG_CFG_SHIFT)

/*
 * AMP (RW)
 *
 * crystal 32k amplifier
 */
#define BCFG_XTAL32K_CFG_AMP_MASK (0x3U)
#define BCFG_XTAL32K_CFG_AMP_SHIFT (0U)
#define BCFG_XTAL32K_CFG_AMP_SET(x) (((uint32_t)(x) << BCFG_XTAL32K_CFG_AMP_SHIFT) & BCFG_XTAL32K_CFG_AMP_MASK)
#define BCFG_XTAL32K_CFG_AMP_GET(x) (((uint32_t)(x) & BCFG_XTAL32K_CFG_AMP_MASK) >> BCFG_XTAL32K_CFG_AMP_SHIFT)

/* Bitfield definition for register: CLK_CFG */
/*
 * XTAL_SEL (RO)
 *
 * crystal selected
 */
#define BCFG_CLK_CFG_XTAL_SEL_MASK (0x10000000UL)
#define BCFG_CLK_CFG_XTAL_SEL_SHIFT (28U)
#define BCFG_CLK_CFG_XTAL_SEL_GET(x) (((uint32_t)(x) & BCFG_CLK_CFG_XTAL_SEL_MASK) >> BCFG_CLK_CFG_XTAL_SEL_SHIFT)

/*
 * KEEP_IRC (RW)
 *
 * force irc32k run
 */
#define BCFG_CLK_CFG_KEEP_IRC_MASK (0x10000UL)
#define BCFG_CLK_CFG_KEEP_IRC_SHIFT (16U)
#define BCFG_CLK_CFG_KEEP_IRC_SET(x) (((uint32_t)(x) << BCFG_CLK_CFG_KEEP_IRC_SHIFT) & BCFG_CLK_CFG_KEEP_IRC_MASK)
#define BCFG_CLK_CFG_KEEP_IRC_GET(x) (((uint32_t)(x) & BCFG_CLK_CFG_KEEP_IRC_MASK) >> BCFG_CLK_CFG_KEEP_IRC_SHIFT)

/*
 * FORCE_XTAL (RW)
 *
 * force switch to crystal
 */
#define BCFG_CLK_CFG_FORCE_XTAL_MASK (0x10U)
#define BCFG_CLK_CFG_FORCE_XTAL_SHIFT (4U)
#define BCFG_CLK_CFG_FORCE_XTAL_SET(x) (((uint32_t)(x) << BCFG_CLK_CFG_FORCE_XTAL_SHIFT) & BCFG_CLK_CFG_FORCE_XTAL_MASK)
#define BCFG_CLK_CFG_FORCE_XTAL_GET(x) (((uint32_t)(x) & BCFG_CLK_CFG_FORCE_XTAL_MASK) >> BCFG_CLK_CFG_FORCE_XTAL_SHIFT)




#endif /* HPM_BCFG_H */
