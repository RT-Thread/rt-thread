/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PDGO_H
#define HPM_PDGO_H

typedef struct {
    __W  uint32_t DGO_TURNOFF;                 /* 0x0: trunoff control */
    __RW uint32_t DGO_RC32K_CFG;               /* 0x4: RC32K CLOCK */
    __R  uint8_t  RESERVED0[1528];             /* 0x8 - 0x5FF: Reserved */
    __RW uint32_t DGO_GPR00;                   /* 0x600: Generic control 0 */
    __RW uint32_t DGO_GPR01;                   /* 0x604: Generic control 1 */
    __RW uint32_t DGO_GPR02;                   /* 0x608: Generic control 2 */
    __RW uint32_t DGO_GPR03;                   /* 0x60C: Generic control 3 */
    __R  uint8_t  RESERVED1[240];              /* 0x610 - 0x6FF: Reserved */
    __RW uint32_t DGO_CTR0;                    /* 0x700: control register 0 */
    __RW uint32_t DGO_CTR1;                    /* 0x704: control register 1 */
    __RW uint32_t DGO_CTR2;                    /* 0x708: control register 2 */
    __RW uint32_t DGO_CTR3;                    /* 0x70C: control register 3 */
    __RW uint32_t DGO_CTR4;                    /* 0x710: control register 4 */
} PDGO_Type;


/* Bitfield definition for register: DGO_TURNOFF */
/*
 * COUNTER (WO)
 *
 * trunoff counter, counter stops when it counts down to 0, the trunoff occurs when the counter value is 1.
 */
#define PDGO_DGO_TURNOFF_COUNTER_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_TURNOFF_COUNTER_SHIFT (0U)
#define PDGO_DGO_TURNOFF_COUNTER_SET(x) (((uint32_t)(x) << PDGO_DGO_TURNOFF_COUNTER_SHIFT) & PDGO_DGO_TURNOFF_COUNTER_MASK)
#define PDGO_DGO_TURNOFF_COUNTER_GET(x) (((uint32_t)(x) & PDGO_DGO_TURNOFF_COUNTER_MASK) >> PDGO_DGO_TURNOFF_COUNTER_SHIFT)

/* Bitfield definition for register: DGO_RC32K_CFG */
/*
 * IRC_TRIMMED (RW)
 *
 * IRC32K trim happened, this bit set by hardware after trim value loaded, and stop load, write 0 will clear this bit and reload trim value
 * 0: irc is not trimmed
 * 1: irc is trimmed
 */
#define PDGO_DGO_RC32K_CFG_IRC_TRIMMED_MASK (0x80000000UL)
#define PDGO_DGO_RC32K_CFG_IRC_TRIMMED_SHIFT (31U)
#define PDGO_DGO_RC32K_CFG_IRC_TRIMMED_SET(x) (((uint32_t)(x) << PDGO_DGO_RC32K_CFG_IRC_TRIMMED_SHIFT) & PDGO_DGO_RC32K_CFG_IRC_TRIMMED_MASK)
#define PDGO_DGO_RC32K_CFG_IRC_TRIMMED_GET(x) (((uint32_t)(x) & PDGO_DGO_RC32K_CFG_IRC_TRIMMED_MASK) >> PDGO_DGO_RC32K_CFG_IRC_TRIMMED_SHIFT)

/*
 * CAPEX7_TRIM (RW)
 *
 * IRC32K bit 7
 */
#define PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_MASK (0x800000UL)
#define PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_SHIFT (23U)
#define PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_SET(x) (((uint32_t)(x) << PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_SHIFT) & PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_MASK)
#define PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_GET(x) (((uint32_t)(x) & PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_MASK) >> PDGO_DGO_RC32K_CFG_CAPEX7_TRIM_SHIFT)

/*
 * CAPEX6_TRIM (RW)
 *
 * IRC32K bit 6
 */
#define PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_MASK (0x400000UL)
#define PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_SHIFT (22U)
#define PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_SET(x) (((uint32_t)(x) << PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_SHIFT) & PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_MASK)
#define PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_GET(x) (((uint32_t)(x) & PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_MASK) >> PDGO_DGO_RC32K_CFG_CAPEX6_TRIM_SHIFT)

/*
 * CAP_TRIM (RW)
 *
 * capacitor trim bits
 */
#define PDGO_DGO_RC32K_CFG_CAP_TRIM_MASK (0x1FFU)
#define PDGO_DGO_RC32K_CFG_CAP_TRIM_SHIFT (0U)
#define PDGO_DGO_RC32K_CFG_CAP_TRIM_SET(x) (((uint32_t)(x) << PDGO_DGO_RC32K_CFG_CAP_TRIM_SHIFT) & PDGO_DGO_RC32K_CFG_CAP_TRIM_MASK)
#define PDGO_DGO_RC32K_CFG_CAP_TRIM_GET(x) (((uint32_t)(x) & PDGO_DGO_RC32K_CFG_CAP_TRIM_MASK) >> PDGO_DGO_RC32K_CFG_CAP_TRIM_SHIFT)

/* Bitfield definition for register: DGO_GPR00 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PDGO_DGO_GPR00_GPR_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_GPR00_GPR_SHIFT (0U)
#define PDGO_DGO_GPR00_GPR_SET(x) (((uint32_t)(x) << PDGO_DGO_GPR00_GPR_SHIFT) & PDGO_DGO_GPR00_GPR_MASK)
#define PDGO_DGO_GPR00_GPR_GET(x) (((uint32_t)(x) & PDGO_DGO_GPR00_GPR_MASK) >> PDGO_DGO_GPR00_GPR_SHIFT)

/* Bitfield definition for register: DGO_GPR01 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PDGO_DGO_GPR01_GPR_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_GPR01_GPR_SHIFT (0U)
#define PDGO_DGO_GPR01_GPR_SET(x) (((uint32_t)(x) << PDGO_DGO_GPR01_GPR_SHIFT) & PDGO_DGO_GPR01_GPR_MASK)
#define PDGO_DGO_GPR01_GPR_GET(x) (((uint32_t)(x) & PDGO_DGO_GPR01_GPR_MASK) >> PDGO_DGO_GPR01_GPR_SHIFT)

/* Bitfield definition for register: DGO_GPR02 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PDGO_DGO_GPR02_GPR_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_GPR02_GPR_SHIFT (0U)
#define PDGO_DGO_GPR02_GPR_SET(x) (((uint32_t)(x) << PDGO_DGO_GPR02_GPR_SHIFT) & PDGO_DGO_GPR02_GPR_MASK)
#define PDGO_DGO_GPR02_GPR_GET(x) (((uint32_t)(x) & PDGO_DGO_GPR02_GPR_MASK) >> PDGO_DGO_GPR02_GPR_SHIFT)

/* Bitfield definition for register: DGO_GPR03 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PDGO_DGO_GPR03_GPR_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_GPR03_GPR_SHIFT (0U)
#define PDGO_DGO_GPR03_GPR_SET(x) (((uint32_t)(x) << PDGO_DGO_GPR03_GPR_SHIFT) & PDGO_DGO_GPR03_GPR_MASK)
#define PDGO_DGO_GPR03_GPR_GET(x) (((uint32_t)(x) & PDGO_DGO_GPR03_GPR_MASK) >> PDGO_DGO_GPR03_GPR_SHIFT)

/* Bitfield definition for register: DGO_CTR0 */
/*
 * RETENTION (RW)
 *
 * dgo register status retenion
 */
#define PDGO_DGO_CTR0_RETENTION_MASK (0x10000UL)
#define PDGO_DGO_CTR0_RETENTION_SHIFT (16U)
#define PDGO_DGO_CTR0_RETENTION_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR0_RETENTION_SHIFT) & PDGO_DGO_CTR0_RETENTION_MASK)
#define PDGO_DGO_CTR0_RETENTION_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR0_RETENTION_MASK) >> PDGO_DGO_CTR0_RETENTION_SHIFT)

/* Bitfield definition for register: DGO_CTR1 */
/*
 * AOTO_SYS_WAKEUP (RW)
 *
 * software wakeup： 0 : wakeup once； 1：auto wakeup Continuously
 */
#define PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK (0x80000000UL)
#define PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_SHIFT (31U)
#define PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_SHIFT) & PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK)
#define PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK) >> PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_SHIFT)

/*
 * WAKEUP_EN (RW)
 *
 * permit wakeup pin or software wakeup
 */
#define PDGO_DGO_CTR1_WAKEUP_EN_MASK (0x10000UL)
#define PDGO_DGO_CTR1_WAKEUP_EN_SHIFT (16U)
#define PDGO_DGO_CTR1_WAKEUP_EN_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR1_WAKEUP_EN_SHIFT) & PDGO_DGO_CTR1_WAKEUP_EN_MASK)
#define PDGO_DGO_CTR1_WAKEUP_EN_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR1_WAKEUP_EN_MASK) >> PDGO_DGO_CTR1_WAKEUP_EN_SHIFT)

/*
 * PIN_WAKEUP_STATUS (RO)
 *
 * wakeup pin status
 */
#define PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_MASK (0x1U)
#define PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_SHIFT (0U)
#define PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_MASK) >> PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_SHIFT)

/* Bitfield definition for register: DGO_CTR2 */
/*
 * RESETN_PULLUP_DISABLE (RW)
 *
 * resetn pin pull up disable
 */
#define PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_MASK (0x1000000UL)
#define PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_SHIFT (24U)
#define PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_SHIFT) & PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_MASK)
#define PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_MASK) >> PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_SHIFT)

/*
 * WAKEUP_PULLDN_DISABLE (RW)
 *
 * wakeup pin pull down disable
 */
#define PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_MASK (0x10000UL)
#define PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_SHIFT (16U)
#define PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_SHIFT) & PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_MASK)
#define PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_MASK) >> PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_SHIFT)

/* Bitfield definition for register: DGO_CTR3 */
/*
 * WAKEUP_COUNTER (RW)
 *
 * software wakeup counter
 */
#define PDGO_DGO_CTR3_WAKEUP_COUNTER_MASK (0xFFFFFFFFUL)
#define PDGO_DGO_CTR3_WAKEUP_COUNTER_SHIFT (0U)
#define PDGO_DGO_CTR3_WAKEUP_COUNTER_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR3_WAKEUP_COUNTER_SHIFT) & PDGO_DGO_CTR3_WAKEUP_COUNTER_MASK)
#define PDGO_DGO_CTR3_WAKEUP_COUNTER_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR3_WAKEUP_COUNTER_MASK) >> PDGO_DGO_CTR3_WAKEUP_COUNTER_SHIFT)

/* Bitfield definition for register: DGO_CTR4 */
/*
 * BANDGAP_LESS_POWER (RW)
 *
 * Banggap work in power save mode, banggap function normally
 * 0: banggap works in high performance mode
 * 1: banggap works in power saving mode
 */
#define PDGO_DGO_CTR4_BANDGAP_LESS_POWER_MASK (0x2U)
#define PDGO_DGO_CTR4_BANDGAP_LESS_POWER_SHIFT (1U)
#define PDGO_DGO_CTR4_BANDGAP_LESS_POWER_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR4_BANDGAP_LESS_POWER_SHIFT) & PDGO_DGO_CTR4_BANDGAP_LESS_POWER_MASK)
#define PDGO_DGO_CTR4_BANDGAP_LESS_POWER_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR4_BANDGAP_LESS_POWER_MASK) >> PDGO_DGO_CTR4_BANDGAP_LESS_POWER_SHIFT)

/*
 * BANDGAP_LP_MODE (RW)
 *
 * Banggap work in low power mode, banggap function limited
 * 0: banggap works in normal mode
 * 1: banggap works in low power mode
 */
#define PDGO_DGO_CTR4_BANDGAP_LP_MODE_MASK (0x1U)
#define PDGO_DGO_CTR4_BANDGAP_LP_MODE_SHIFT (0U)
#define PDGO_DGO_CTR4_BANDGAP_LP_MODE_SET(x) (((uint32_t)(x) << PDGO_DGO_CTR4_BANDGAP_LP_MODE_SHIFT) & PDGO_DGO_CTR4_BANDGAP_LP_MODE_MASK)
#define PDGO_DGO_CTR4_BANDGAP_LP_MODE_GET(x) (((uint32_t)(x) & PDGO_DGO_CTR4_BANDGAP_LP_MODE_MASK) >> PDGO_DGO_CTR4_BANDGAP_LP_MODE_SHIFT)




#endif /* HPM_PDGO_H */
