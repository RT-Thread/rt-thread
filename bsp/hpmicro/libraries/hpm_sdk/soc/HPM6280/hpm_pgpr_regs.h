/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PGPR_H
#define HPM_PGPR_H

typedef struct {
    __RW uint32_t PMIC_GPR00;                  /* 0x0: Generic control */
    __RW uint32_t PMIC_GPR01;                  /* 0x4: Generic control */
    __RW uint32_t PMIC_GPR02;                  /* 0x8: Generic control */
    __RW uint32_t PMIC_GPR03;                  /* 0xC: Generic control */
    __RW uint32_t PMIC_GPR04;                  /* 0x10: Generic control */
    __RW uint32_t PMIC_GPR05;                  /* 0x14: Generic control */
    __RW uint32_t PMIC_GPR06;                  /* 0x18: Generic control */
    __RW uint32_t PMIC_GPR07;                  /* 0x1C: Generic control */
    __RW uint32_t PMIC_GPR08;                  /* 0x20: Generic control */
    __RW uint32_t PMIC_GPR09;                  /* 0x24: Generic control */
    __RW uint32_t PMIC_GPR10;                  /* 0x28: Generic control */
    __RW uint32_t PMIC_GPR11;                  /* 0x2C: Generic control */
    __RW uint32_t PMIC_GPR12;                  /* 0x30: Generic control */
    __RW uint32_t PMIC_GPR13;                  /* 0x34: Generic control */
    __RW uint32_t PMIC_GPR14;                  /* 0x38: Generic control */
    __RW uint32_t PMIC_GPR15;                  /* 0x3C: Generic control */
} PGPR_Type;


/* Bitfield definition for register: PMIC_GPR00 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR00_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR00_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR00_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR00_GPR_SHIFT) & PGPR_PMIC_GPR00_GPR_MASK)
#define PGPR_PMIC_GPR00_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR00_GPR_MASK) >> PGPR_PMIC_GPR00_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR01 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR01_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR01_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR01_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR01_GPR_SHIFT) & PGPR_PMIC_GPR01_GPR_MASK)
#define PGPR_PMIC_GPR01_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR01_GPR_MASK) >> PGPR_PMIC_GPR01_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR02 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR02_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR02_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR02_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR02_GPR_SHIFT) & PGPR_PMIC_GPR02_GPR_MASK)
#define PGPR_PMIC_GPR02_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR02_GPR_MASK) >> PGPR_PMIC_GPR02_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR03 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR03_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR03_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR03_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR03_GPR_SHIFT) & PGPR_PMIC_GPR03_GPR_MASK)
#define PGPR_PMIC_GPR03_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR03_GPR_MASK) >> PGPR_PMIC_GPR03_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR04 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR04_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR04_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR04_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR04_GPR_SHIFT) & PGPR_PMIC_GPR04_GPR_MASK)
#define PGPR_PMIC_GPR04_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR04_GPR_MASK) >> PGPR_PMIC_GPR04_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR05 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR05_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR05_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR05_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR05_GPR_SHIFT) & PGPR_PMIC_GPR05_GPR_MASK)
#define PGPR_PMIC_GPR05_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR05_GPR_MASK) >> PGPR_PMIC_GPR05_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR06 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR06_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR06_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR06_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR06_GPR_SHIFT) & PGPR_PMIC_GPR06_GPR_MASK)
#define PGPR_PMIC_GPR06_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR06_GPR_MASK) >> PGPR_PMIC_GPR06_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR07 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR07_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR07_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR07_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR07_GPR_SHIFT) & PGPR_PMIC_GPR07_GPR_MASK)
#define PGPR_PMIC_GPR07_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR07_GPR_MASK) >> PGPR_PMIC_GPR07_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR08 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR08_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR08_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR08_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR08_GPR_SHIFT) & PGPR_PMIC_GPR08_GPR_MASK)
#define PGPR_PMIC_GPR08_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR08_GPR_MASK) >> PGPR_PMIC_GPR08_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR09 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR09_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR09_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR09_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR09_GPR_SHIFT) & PGPR_PMIC_GPR09_GPR_MASK)
#define PGPR_PMIC_GPR09_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR09_GPR_MASK) >> PGPR_PMIC_GPR09_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR10 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR10_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR10_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR10_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR10_GPR_SHIFT) & PGPR_PMIC_GPR10_GPR_MASK)
#define PGPR_PMIC_GPR10_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR10_GPR_MASK) >> PGPR_PMIC_GPR10_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR11 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR11_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR11_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR11_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR11_GPR_SHIFT) & PGPR_PMIC_GPR11_GPR_MASK)
#define PGPR_PMIC_GPR11_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR11_GPR_MASK) >> PGPR_PMIC_GPR11_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR12 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR12_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR12_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR12_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR12_GPR_SHIFT) & PGPR_PMIC_GPR12_GPR_MASK)
#define PGPR_PMIC_GPR12_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR12_GPR_MASK) >> PGPR_PMIC_GPR12_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR13 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR13_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR13_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR13_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR13_GPR_SHIFT) & PGPR_PMIC_GPR13_GPR_MASK)
#define PGPR_PMIC_GPR13_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR13_GPR_MASK) >> PGPR_PMIC_GPR13_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR14 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR14_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR14_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR14_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR14_GPR_SHIFT) & PGPR_PMIC_GPR14_GPR_MASK)
#define PGPR_PMIC_GPR14_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR14_GPR_MASK) >> PGPR_PMIC_GPR14_GPR_SHIFT)

/* Bitfield definition for register: PMIC_GPR15 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define PGPR_PMIC_GPR15_GPR_MASK (0xFFFFFFFFUL)
#define PGPR_PMIC_GPR15_GPR_SHIFT (0U)
#define PGPR_PMIC_GPR15_GPR_SET(x) (((uint32_t)(x) << PGPR_PMIC_GPR15_GPR_SHIFT) & PGPR_PMIC_GPR15_GPR_MASK)
#define PGPR_PMIC_GPR15_GPR_GET(x) (((uint32_t)(x) & PGPR_PMIC_GPR15_GPR_MASK) >> PGPR_PMIC_GPR15_GPR_SHIFT)




#endif /* HPM_PGPR_H */
