/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PLB_H
#define HPM_PLB_H

typedef struct {
    struct {
        __RW uint32_t LOOKUP_TABLE[4];         /* 0x0 - 0xC: TYPE A CHN lookup_table 0 */
        __RW uint32_t SW_INJECT;               /* 0x10: TYPE A CHN software inject */
        __R  uint8_t  RESERVED0[12];           /* 0x14 - 0x1F: Reserved */
    } TYPE_A[4];
    __R  uint8_t  RESERVED0[896];              /* 0x80 - 0x3FF: Reserved */
    struct {
        __RW uint32_t LUT[2];                  /* 0x400 - 0x404: TYPE B CHN lookup table 0 */
        __RW uint32_t CMP[4];                  /* 0x408 - 0x414: TYPE B CHN data unit cmp0 */
        __RW uint32_t MODE;                    /* 0x418: TYPE B CHN mode ctrl */
        __RW uint32_t SW_INJECT;               /* 0x41C: TYPE B CHN software inject */
    } TYPE_B[4];
} PLB_Type;


/* Bitfield definition for register of struct array TYPE_A: 0 */
/*
 * LOOKUP_TABLE (RW)
 *
 * using 4 bit trig_in as lookup index. software can program this register as trig_in's true table.
 */
#define PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_MASK (0xFFFFU)
#define PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_SHIFT (0U)
#define PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_SET(x) (((uint32_t)(x) << PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_SHIFT) & PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_MASK)
#define PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_GET(x) (((uint32_t)(x) & PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_MASK) >> PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_SHIFT)

/* Bitfield definition for register of struct array TYPE_A: SW_INJECT */
/*
 * SW_INJECT (RW)
 *
 * software can inject value to TYPEA's output
 */
#define PLB_TYPE_A_SW_INJECT_SW_INJECT_MASK (0xFU)
#define PLB_TYPE_A_SW_INJECT_SW_INJECT_SHIFT (0U)
#define PLB_TYPE_A_SW_INJECT_SW_INJECT_SET(x) (((uint32_t)(x) << PLB_TYPE_A_SW_INJECT_SW_INJECT_SHIFT) & PLB_TYPE_A_SW_INJECT_SW_INJECT_MASK)
#define PLB_TYPE_A_SW_INJECT_SW_INJECT_GET(x) (((uint32_t)(x) & PLB_TYPE_A_SW_INJECT_SW_INJECT_MASK) >> PLB_TYPE_A_SW_INJECT_SW_INJECT_SHIFT)

/* Bitfield definition for register of struct array TYPE_B: 0 */
/*
 * LOOKUP_TABLE (RW)
 *
 * lut0 and lut1 union as 64bit, consider each 4bit as one slice. then, total 16 slice. slice0 as bit3:0, slice1 as bit7:4...etc. using 4bit trig in as index of slice. the operate sel in data unit of type B channle is decided by which slice value choosed by trig_in
 */
#define PLB_TYPE_B_LUT_LOOKUP_TABLE_MASK (0xFFFFFFFFUL)
#define PLB_TYPE_B_LUT_LOOKUP_TABLE_SHIFT (0U)
#define PLB_TYPE_B_LUT_LOOKUP_TABLE_SET(x) (((uint32_t)(x) << PLB_TYPE_B_LUT_LOOKUP_TABLE_SHIFT) & PLB_TYPE_B_LUT_LOOKUP_TABLE_MASK)
#define PLB_TYPE_B_LUT_LOOKUP_TABLE_GET(x) (((uint32_t)(x) & PLB_TYPE_B_LUT_LOOKUP_TABLE_MASK) >> PLB_TYPE_B_LUT_LOOKUP_TABLE_SHIFT)

/* Bitfield definition for register of struct array TYPE_B: 0 */
/*
 * CMP_VALUE (RW)
 *
 * cmp value, using as data unit operation
 */
#define PLB_TYPE_B_CMP_CMP_VALUE_MASK (0xFFFFFFFFUL)
#define PLB_TYPE_B_CMP_CMP_VALUE_SHIFT (0U)
#define PLB_TYPE_B_CMP_CMP_VALUE_SET(x) (((uint32_t)(x) << PLB_TYPE_B_CMP_CMP_VALUE_SHIFT) & PLB_TYPE_B_CMP_CMP_VALUE_MASK)
#define PLB_TYPE_B_CMP_CMP_VALUE_GET(x) (((uint32_t)(x) & PLB_TYPE_B_CMP_CMP_VALUE_MASK) >> PLB_TYPE_B_CMP_CMP_VALUE_SHIFT)

/* Bitfield definition for register of struct array TYPE_B: MODE */
/*
 * OPT_SEL (RW)
 *
 * operation selection in data unit.
 */
#define PLB_TYPE_B_MODE_OPT_SEL_MASK (0x10000UL)
#define PLB_TYPE_B_MODE_OPT_SEL_SHIFT (16U)
#define PLB_TYPE_B_MODE_OPT_SEL_SET(x) (((uint32_t)(x) << PLB_TYPE_B_MODE_OPT_SEL_SHIFT) & PLB_TYPE_B_MODE_OPT_SEL_MASK)
#define PLB_TYPE_B_MODE_OPT_SEL_GET(x) (((uint32_t)(x) & PLB_TYPE_B_MODE_OPT_SEL_MASK) >> PLB_TYPE_B_MODE_OPT_SEL_SHIFT)

/*
 * OUT3_SEL (RW)
 *
 * trig out 3 output type in current channel
 */
#define PLB_TYPE_B_MODE_OUT3_SEL_MASK (0xF000U)
#define PLB_TYPE_B_MODE_OUT3_SEL_SHIFT (12U)
#define PLB_TYPE_B_MODE_OUT3_SEL_SET(x) (((uint32_t)(x) << PLB_TYPE_B_MODE_OUT3_SEL_SHIFT) & PLB_TYPE_B_MODE_OUT3_SEL_MASK)
#define PLB_TYPE_B_MODE_OUT3_SEL_GET(x) (((uint32_t)(x) & PLB_TYPE_B_MODE_OUT3_SEL_MASK) >> PLB_TYPE_B_MODE_OUT3_SEL_SHIFT)

/*
 * OUT2_SEL (RW)
 *
 * trig out 2 output type in current channel
 */
#define PLB_TYPE_B_MODE_OUT2_SEL_MASK (0xF00U)
#define PLB_TYPE_B_MODE_OUT2_SEL_SHIFT (8U)
#define PLB_TYPE_B_MODE_OUT2_SEL_SET(x) (((uint32_t)(x) << PLB_TYPE_B_MODE_OUT2_SEL_SHIFT) & PLB_TYPE_B_MODE_OUT2_SEL_MASK)
#define PLB_TYPE_B_MODE_OUT2_SEL_GET(x) (((uint32_t)(x) & PLB_TYPE_B_MODE_OUT2_SEL_MASK) >> PLB_TYPE_B_MODE_OUT2_SEL_SHIFT)

/*
 * OUT1_SEL (RW)
 *
 * trig out 1 output type in current channel
 */
#define PLB_TYPE_B_MODE_OUT1_SEL_MASK (0xF0U)
#define PLB_TYPE_B_MODE_OUT1_SEL_SHIFT (4U)
#define PLB_TYPE_B_MODE_OUT1_SEL_SET(x) (((uint32_t)(x) << PLB_TYPE_B_MODE_OUT1_SEL_SHIFT) & PLB_TYPE_B_MODE_OUT1_SEL_MASK)
#define PLB_TYPE_B_MODE_OUT1_SEL_GET(x) (((uint32_t)(x) & PLB_TYPE_B_MODE_OUT1_SEL_MASK) >> PLB_TYPE_B_MODE_OUT1_SEL_SHIFT)

/*
 * OUT0_SEL (RW)
 *
 * trig out 0 output type in current channel
 */
#define PLB_TYPE_B_MODE_OUT0_SEL_MASK (0xFU)
#define PLB_TYPE_B_MODE_OUT0_SEL_SHIFT (0U)
#define PLB_TYPE_B_MODE_OUT0_SEL_SET(x) (((uint32_t)(x) << PLB_TYPE_B_MODE_OUT0_SEL_SHIFT) & PLB_TYPE_B_MODE_OUT0_SEL_MASK)
#define PLB_TYPE_B_MODE_OUT0_SEL_GET(x) (((uint32_t)(x) & PLB_TYPE_B_MODE_OUT0_SEL_MASK) >> PLB_TYPE_B_MODE_OUT0_SEL_SHIFT)

/* Bitfield definition for register of struct array TYPE_B: SW_INJECT */
/*
 * SOFTWARE_INJECT (RW)
 *
 * data unit value can be changed if program this register
 */
#define PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_MASK (0xFFFFFFFFUL)
#define PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_SHIFT (0U)
#define PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_SET(x) (((uint32_t)(x) << PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_SHIFT) & PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_MASK)
#define PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_GET(x) (((uint32_t)(x) & PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_MASK) >> PLB_TYPE_B_SW_INJECT_SOFTWARE_INJECT_SHIFT)



/* LOOKUP_TABLE register group index macro definition */
#define PLB_TYPE_A_LOOKUP_TABLE_0 (0UL)
#define PLB_TYPE_A_LOOKUP_TABLE_1 (1UL)
#define PLB_TYPE_A_LOOKUP_TABLE_2 (2UL)
#define PLB_TYPE_A_LOOKUP_TABLE_3 (3UL)

/* TYPE_A register group index macro definition */
#define PLB_TYPE_A_0 (0UL)
#define PLB_TYPE_A_1 (1UL)
#define PLB_TYPE_A_2 (2UL)
#define PLB_TYPE_A_3 (3UL)

/* LUT register group index macro definition */
#define PLB_TYPE_B_LUT_0 (0UL)
#define PLB_TYPE_B_LUT_1 (1UL)

/* CMP register group index macro definition */
#define PLB_TYPE_B_CMP_0 (0UL)
#define PLB_TYPE_B_CMP_1 (1UL)
#define PLB_TYPE_B_CMP_2 (2UL)
#define PLB_TYPE_B_CMP_3 (3UL)

/* TYPE_B register group index macro definition */
#define PLB_TYPE_B_0 (0UL)
#define PLB_TYPE_B_1 (1UL)
#define PLB_TYPE_B_2 (2UL)
#define PLB_TYPE_B_3 (3UL)


#endif /* HPM_PLB_H */
