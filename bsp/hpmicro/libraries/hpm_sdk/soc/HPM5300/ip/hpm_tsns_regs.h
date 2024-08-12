/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_TSNS_H
#define HPM_TSNS_H

typedef struct {
    __R  uint32_t T;                           /* 0x0: Temperature */
    __R  uint32_t TMAX;                        /* 0x4: Maximum Temperature */
    __R  uint32_t TMIN;                        /* 0x8: Minimum Temperature */
    __R  uint32_t AGE;                         /* 0xC: Sample age */
    __RW uint32_t STATUS;                      /* 0x10: Status */
    __RW uint32_t CONFIG;                      /* 0x14: Configuration */
    __RW uint32_t VALIDITY;                    /* 0x18: Sample validity */
    __RW uint32_t FLAG;                        /* 0x1C: Temperature flag */
    __RW uint32_t UPPER_LIM_IRQ;               /* 0x20: Maximum temperature to interrupt */
    __RW uint32_t LOWER_LIM_IRQ;               /* 0x24: Minimum temperature to interrupt */
    __RW uint32_t UPPER_LIM_RST;               /* 0x28: Maximum temperature to reset */
    __RW uint32_t LOWER_LIM_RST;               /* 0x2C: Minimum temperature to reset */
    __RW uint32_t ASYNC;                       /* 0x30: Configuration in asynchronous mode */
    __R  uint8_t  RESERVED0[4];                /* 0x34 - 0x37: Reserved */
    __RW uint32_t ADVAN;                       /* 0x38: Advance configuration */
} TSNS_Type;


/* Bitfield definition for register: T */
/*
 * T (RO)
 *
 * Signed number of temperature in 256 x celsius degree
 */
#define TSNS_T_T_MASK (0xFFFFFFFFUL)
#define TSNS_T_T_SHIFT (0U)
#define TSNS_T_T_GET(x) (((uint32_t)(x) & TSNS_T_T_MASK) >> TSNS_T_T_SHIFT)

/* Bitfield definition for register: TMAX */
/*
 * T (RO)
 *
 * maximum temperature ever found
 */
#define TSNS_TMAX_T_MASK (0xFFFFFFFFUL)
#define TSNS_TMAX_T_SHIFT (0U)
#define TSNS_TMAX_T_GET(x) (((uint32_t)(x) & TSNS_TMAX_T_MASK) >> TSNS_TMAX_T_SHIFT)

/* Bitfield definition for register: TMIN */
/*
 * T (RO)
 *
 * minimum temperature ever found
 */
#define TSNS_TMIN_T_MASK (0xFFFFFFFFUL)
#define TSNS_TMIN_T_SHIFT (0U)
#define TSNS_TMIN_T_GET(x) (((uint32_t)(x) & TSNS_TMIN_T_MASK) >> TSNS_TMIN_T_SHIFT)

/* Bitfield definition for register: AGE */
/*
 * AGE (RO)
 *
 * age of T register in 24MHz clock cycles
 */
#define TSNS_AGE_AGE_MASK (0xFFFFFFFFUL)
#define TSNS_AGE_AGE_SHIFT (0U)
#define TSNS_AGE_AGE_GET(x) (((uint32_t)(x) & TSNS_AGE_AGE_MASK) >> TSNS_AGE_AGE_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * VALID (RO)
 *
 * indicate value in T is valid or not
 * 0: not valid
 * 1:valid
 */
#define TSNS_STATUS_VALID_MASK (0x80000000UL)
#define TSNS_STATUS_VALID_SHIFT (31U)
#define TSNS_STATUS_VALID_GET(x) (((uint32_t)(x) & TSNS_STATUS_VALID_MASK) >> TSNS_STATUS_VALID_SHIFT)

/*
 * TRIGGER (W1C)
 *
 * Software trigger for sensing in trigger mode, trigger will be ignored if in sensing or other mode
 */
#define TSNS_STATUS_TRIGGER_MASK (0x1U)
#define TSNS_STATUS_TRIGGER_SHIFT (0U)
#define TSNS_STATUS_TRIGGER_SET(x) (((uint32_t)(x) << TSNS_STATUS_TRIGGER_SHIFT) & TSNS_STATUS_TRIGGER_MASK)
#define TSNS_STATUS_TRIGGER_GET(x) (((uint32_t)(x) & TSNS_STATUS_TRIGGER_MASK) >> TSNS_STATUS_TRIGGER_SHIFT)

/* Bitfield definition for register: CONFIG */
/*
 * IRQ_EN (RW)
 *
 * Enable interrupt
 */
#define TSNS_CONFIG_IRQ_EN_MASK (0x80000000UL)
#define TSNS_CONFIG_IRQ_EN_SHIFT (31U)
#define TSNS_CONFIG_IRQ_EN_SET(x) (((uint32_t)(x) << TSNS_CONFIG_IRQ_EN_SHIFT) & TSNS_CONFIG_IRQ_EN_MASK)
#define TSNS_CONFIG_IRQ_EN_GET(x) (((uint32_t)(x) & TSNS_CONFIG_IRQ_EN_MASK) >> TSNS_CONFIG_IRQ_EN_SHIFT)

/*
 * RST_EN (RW)
 *
 * Enable reset
 */
#define TSNS_CONFIG_RST_EN_MASK (0x40000000UL)
#define TSNS_CONFIG_RST_EN_SHIFT (30U)
#define TSNS_CONFIG_RST_EN_SET(x) (((uint32_t)(x) << TSNS_CONFIG_RST_EN_SHIFT) & TSNS_CONFIG_RST_EN_MASK)
#define TSNS_CONFIG_RST_EN_GET(x) (((uint32_t)(x) & TSNS_CONFIG_RST_EN_MASK) >> TSNS_CONFIG_RST_EN_SHIFT)

/*
 * COMPARE_MIN_EN (RW)
 *
 * Enable compare for minimum temperature
 */
#define TSNS_CONFIG_COMPARE_MIN_EN_MASK (0x2000000UL)
#define TSNS_CONFIG_COMPARE_MIN_EN_SHIFT (25U)
#define TSNS_CONFIG_COMPARE_MIN_EN_SET(x) (((uint32_t)(x) << TSNS_CONFIG_COMPARE_MIN_EN_SHIFT) & TSNS_CONFIG_COMPARE_MIN_EN_MASK)
#define TSNS_CONFIG_COMPARE_MIN_EN_GET(x) (((uint32_t)(x) & TSNS_CONFIG_COMPARE_MIN_EN_MASK) >> TSNS_CONFIG_COMPARE_MIN_EN_SHIFT)

/*
 * COMPARE_MAX_EN (RW)
 *
 * Enable compare for maximum temperature
 */
#define TSNS_CONFIG_COMPARE_MAX_EN_MASK (0x1000000UL)
#define TSNS_CONFIG_COMPARE_MAX_EN_SHIFT (24U)
#define TSNS_CONFIG_COMPARE_MAX_EN_SET(x) (((uint32_t)(x) << TSNS_CONFIG_COMPARE_MAX_EN_SHIFT) & TSNS_CONFIG_COMPARE_MAX_EN_MASK)
#define TSNS_CONFIG_COMPARE_MAX_EN_GET(x) (((uint32_t)(x) & TSNS_CONFIG_COMPARE_MAX_EN_MASK) >> TSNS_CONFIG_COMPARE_MAX_EN_SHIFT)

/*
 * SPEED (RW)
 *
 * cycles of a progressive step in 24M clock, valid from 24-255, default 96
 * 24: 24 cycle for a step
 * 25: 25 cycle for a step
 * 26: 26 cycle for a step
 * ...
 * 255: 255 cycle for a step
 */
#define TSNS_CONFIG_SPEED_MASK (0xFF0000UL)
#define TSNS_CONFIG_SPEED_SHIFT (16U)
#define TSNS_CONFIG_SPEED_SET(x) (((uint32_t)(x) << TSNS_CONFIG_SPEED_SHIFT) & TSNS_CONFIG_SPEED_MASK)
#define TSNS_CONFIG_SPEED_GET(x) (((uint32_t)(x) & TSNS_CONFIG_SPEED_MASK) >> TSNS_CONFIG_SPEED_SHIFT)

/*
 * AVERAGE (RW)
 *
 * Average time, default in 3
 * 0: measure and return
 * 1: twice and average
 * 2: 4 times and average
 * . . .
 * 7: 128 times and average
 */
#define TSNS_CONFIG_AVERAGE_MASK (0x700U)
#define TSNS_CONFIG_AVERAGE_SHIFT (8U)
#define TSNS_CONFIG_AVERAGE_SET(x) (((uint32_t)(x) << TSNS_CONFIG_AVERAGE_SHIFT) & TSNS_CONFIG_AVERAGE_MASK)
#define TSNS_CONFIG_AVERAGE_GET(x) (((uint32_t)(x) & TSNS_CONFIG_AVERAGE_MASK) >> TSNS_CONFIG_AVERAGE_SHIFT)

/*
 * CONTINUOUS (RW)
 *
 * continuous mode that keep sampling temperature peridically
 * 0: trigger mode
 * 1: continuous mode
 */
#define TSNS_CONFIG_CONTINUOUS_MASK (0x10U)
#define TSNS_CONFIG_CONTINUOUS_SHIFT (4U)
#define TSNS_CONFIG_CONTINUOUS_SET(x) (((uint32_t)(x) << TSNS_CONFIG_CONTINUOUS_SHIFT) & TSNS_CONFIG_CONTINUOUS_MASK)
#define TSNS_CONFIG_CONTINUOUS_GET(x) (((uint32_t)(x) & TSNS_CONFIG_CONTINUOUS_MASK) >> TSNS_CONFIG_CONTINUOUS_SHIFT)

/*
 * ASYNC (RW)
 *
 * Acynchronous mode, this mode can work without clock, only available function ios compare to certain ADC value
 * 0: active mode
 * 1: Async mode
 */
#define TSNS_CONFIG_ASYNC_MASK (0x2U)
#define TSNS_CONFIG_ASYNC_SHIFT (1U)
#define TSNS_CONFIG_ASYNC_SET(x) (((uint32_t)(x) << TSNS_CONFIG_ASYNC_SHIFT) & TSNS_CONFIG_ASYNC_MASK)
#define TSNS_CONFIG_ASYNC_GET(x) (((uint32_t)(x) & TSNS_CONFIG_ASYNC_MASK) >> TSNS_CONFIG_ASYNC_SHIFT)

/*
 * ENABLE (RW)
 *
 * Enable temperature
 * 0: disable, temperature sensor is shut down
 * 1: enable. Temperature sensor enabled
 */
#define TSNS_CONFIG_ENABLE_MASK (0x1U)
#define TSNS_CONFIG_ENABLE_SHIFT (0U)
#define TSNS_CONFIG_ENABLE_SET(x) (((uint32_t)(x) << TSNS_CONFIG_ENABLE_SHIFT) & TSNS_CONFIG_ENABLE_MASK)
#define TSNS_CONFIG_ENABLE_GET(x) (((uint32_t)(x) & TSNS_CONFIG_ENABLE_MASK) >> TSNS_CONFIG_ENABLE_SHIFT)

/* Bitfield definition for register: VALIDITY */
/*
 * VALIDITY (RW)
 *
 * time for temperature values to expire in 24M clock cycles
 */
#define TSNS_VALIDITY_VALIDITY_MASK (0xFFFFFFFFUL)
#define TSNS_VALIDITY_VALIDITY_SHIFT (0U)
#define TSNS_VALIDITY_VALIDITY_SET(x) (((uint32_t)(x) << TSNS_VALIDITY_VALIDITY_SHIFT) & TSNS_VALIDITY_VALIDITY_MASK)
#define TSNS_VALIDITY_VALIDITY_GET(x) (((uint32_t)(x) & TSNS_VALIDITY_VALIDITY_MASK) >> TSNS_VALIDITY_VALIDITY_SHIFT)

/* Bitfield definition for register: FLAG */
/*
 * RECORD_MIN_CLR (RW)
 *
 * Clear minimum recorder of temerature, write 1 to clear
 */
#define TSNS_FLAG_RECORD_MIN_CLR_MASK (0x200000UL)
#define TSNS_FLAG_RECORD_MIN_CLR_SHIFT (21U)
#define TSNS_FLAG_RECORD_MIN_CLR_SET(x) (((uint32_t)(x) << TSNS_FLAG_RECORD_MIN_CLR_SHIFT) & TSNS_FLAG_RECORD_MIN_CLR_MASK)
#define TSNS_FLAG_RECORD_MIN_CLR_GET(x) (((uint32_t)(x) & TSNS_FLAG_RECORD_MIN_CLR_MASK) >> TSNS_FLAG_RECORD_MIN_CLR_SHIFT)

/*
 * RECORD_MAX_CLR (RW)
 *
 * Clear maximum recorder of temerature, write 1 to clear
 */
#define TSNS_FLAG_RECORD_MAX_CLR_MASK (0x100000UL)
#define TSNS_FLAG_RECORD_MAX_CLR_SHIFT (20U)
#define TSNS_FLAG_RECORD_MAX_CLR_SET(x) (((uint32_t)(x) << TSNS_FLAG_RECORD_MAX_CLR_SHIFT) & TSNS_FLAG_RECORD_MAX_CLR_MASK)
#define TSNS_FLAG_RECORD_MAX_CLR_GET(x) (((uint32_t)(x) & TSNS_FLAG_RECORD_MAX_CLR_MASK) >> TSNS_FLAG_RECORD_MAX_CLR_SHIFT)

/*
 * UNDER_TEMP (RW)
 *
 * Clear under temperature status, write 1 to clear
 */
#define TSNS_FLAG_UNDER_TEMP_MASK (0x20000UL)
#define TSNS_FLAG_UNDER_TEMP_SHIFT (17U)
#define TSNS_FLAG_UNDER_TEMP_SET(x) (((uint32_t)(x) << TSNS_FLAG_UNDER_TEMP_SHIFT) & TSNS_FLAG_UNDER_TEMP_MASK)
#define TSNS_FLAG_UNDER_TEMP_GET(x) (((uint32_t)(x) & TSNS_FLAG_UNDER_TEMP_MASK) >> TSNS_FLAG_UNDER_TEMP_SHIFT)

/*
 * OVER_TEMP (RW)
 *
 * Clear over temperature status, write 1 to clear
 */
#define TSNS_FLAG_OVER_TEMP_MASK (0x10000UL)
#define TSNS_FLAG_OVER_TEMP_SHIFT (16U)
#define TSNS_FLAG_OVER_TEMP_SET(x) (((uint32_t)(x) << TSNS_FLAG_OVER_TEMP_SHIFT) & TSNS_FLAG_OVER_TEMP_MASK)
#define TSNS_FLAG_OVER_TEMP_GET(x) (((uint32_t)(x) & TSNS_FLAG_OVER_TEMP_MASK) >> TSNS_FLAG_OVER_TEMP_SHIFT)

/*
 * IRQ (RW)
 *
 * IRQ flag, write 1 to clear
 */
#define TSNS_FLAG_IRQ_MASK (0x1U)
#define TSNS_FLAG_IRQ_SHIFT (0U)
#define TSNS_FLAG_IRQ_SET(x) (((uint32_t)(x) << TSNS_FLAG_IRQ_SHIFT) & TSNS_FLAG_IRQ_MASK)
#define TSNS_FLAG_IRQ_GET(x) (((uint32_t)(x) & TSNS_FLAG_IRQ_MASK) >> TSNS_FLAG_IRQ_SHIFT)

/* Bitfield definition for register: UPPER_LIM_IRQ */
/*
 * T (RW)
 *
 * Maximum temperature for compare
 */
#define TSNS_UPPER_LIM_IRQ_T_MASK (0xFFFFFFFFUL)
#define TSNS_UPPER_LIM_IRQ_T_SHIFT (0U)
#define TSNS_UPPER_LIM_IRQ_T_SET(x) (((uint32_t)(x) << TSNS_UPPER_LIM_IRQ_T_SHIFT) & TSNS_UPPER_LIM_IRQ_T_MASK)
#define TSNS_UPPER_LIM_IRQ_T_GET(x) (((uint32_t)(x) & TSNS_UPPER_LIM_IRQ_T_MASK) >> TSNS_UPPER_LIM_IRQ_T_SHIFT)

/* Bitfield definition for register: LOWER_LIM_IRQ */
/*
 * T (RW)
 *
 * Minimum temperature for compare
 */
#define TSNS_LOWER_LIM_IRQ_T_MASK (0xFFFFFFFFUL)
#define TSNS_LOWER_LIM_IRQ_T_SHIFT (0U)
#define TSNS_LOWER_LIM_IRQ_T_SET(x) (((uint32_t)(x) << TSNS_LOWER_LIM_IRQ_T_SHIFT) & TSNS_LOWER_LIM_IRQ_T_MASK)
#define TSNS_LOWER_LIM_IRQ_T_GET(x) (((uint32_t)(x) & TSNS_LOWER_LIM_IRQ_T_MASK) >> TSNS_LOWER_LIM_IRQ_T_SHIFT)

/* Bitfield definition for register: UPPER_LIM_RST */
/*
 * T (RW)
 *
 * Maximum temperature for compare
 */
#define TSNS_UPPER_LIM_RST_T_MASK (0xFFFFFFFFUL)
#define TSNS_UPPER_LIM_RST_T_SHIFT (0U)
#define TSNS_UPPER_LIM_RST_T_SET(x) (((uint32_t)(x) << TSNS_UPPER_LIM_RST_T_SHIFT) & TSNS_UPPER_LIM_RST_T_MASK)
#define TSNS_UPPER_LIM_RST_T_GET(x) (((uint32_t)(x) & TSNS_UPPER_LIM_RST_T_MASK) >> TSNS_UPPER_LIM_RST_T_SHIFT)

/* Bitfield definition for register: LOWER_LIM_RST */
/*
 * T (RW)
 *
 * Minimum temperature for compare
 */
#define TSNS_LOWER_LIM_RST_T_MASK (0xFFFFFFFFUL)
#define TSNS_LOWER_LIM_RST_T_SHIFT (0U)
#define TSNS_LOWER_LIM_RST_T_SET(x) (((uint32_t)(x) << TSNS_LOWER_LIM_RST_T_SHIFT) & TSNS_LOWER_LIM_RST_T_MASK)
#define TSNS_LOWER_LIM_RST_T_GET(x) (((uint32_t)(x) & TSNS_LOWER_LIM_RST_T_MASK) >> TSNS_LOWER_LIM_RST_T_SHIFT)

/* Bitfield definition for register: ASYNC */
/*
 * ASYNC_TYPE (RW)
 *
 * Compare hotter than or colder than in asynchoronous mode
 * 0: hotter than
 * 1: colder than
 */
#define TSNS_ASYNC_ASYNC_TYPE_MASK (0x1000000UL)
#define TSNS_ASYNC_ASYNC_TYPE_SHIFT (24U)
#define TSNS_ASYNC_ASYNC_TYPE_SET(x) (((uint32_t)(x) << TSNS_ASYNC_ASYNC_TYPE_SHIFT) & TSNS_ASYNC_ASYNC_TYPE_MASK)
#define TSNS_ASYNC_ASYNC_TYPE_GET(x) (((uint32_t)(x) & TSNS_ASYNC_ASYNC_TYPE_MASK) >> TSNS_ASYNC_ASYNC_TYPE_SHIFT)

/*
 * POLARITY (RW)
 *
 * Polarity of internal comparator
 */
#define TSNS_ASYNC_POLARITY_MASK (0x10000UL)
#define TSNS_ASYNC_POLARITY_SHIFT (16U)
#define TSNS_ASYNC_POLARITY_SET(x) (((uint32_t)(x) << TSNS_ASYNC_POLARITY_SHIFT) & TSNS_ASYNC_POLARITY_MASK)
#define TSNS_ASYNC_POLARITY_GET(x) (((uint32_t)(x) & TSNS_ASYNC_POLARITY_MASK) >> TSNS_ASYNC_POLARITY_SHIFT)

/*
 * VALUE (RW)
 *
 * Value of async mode to compare
 */
#define TSNS_ASYNC_VALUE_MASK (0x7FFU)
#define TSNS_ASYNC_VALUE_SHIFT (0U)
#define TSNS_ASYNC_VALUE_SET(x) (((uint32_t)(x) << TSNS_ASYNC_VALUE_SHIFT) & TSNS_ASYNC_VALUE_MASK)
#define TSNS_ASYNC_VALUE_GET(x) (((uint32_t)(x) & TSNS_ASYNC_VALUE_MASK) >> TSNS_ASYNC_VALUE_SHIFT)

/* Bitfield definition for register: ADVAN */
/*
 * ASYNC_IRQ (RO)
 *
 * interrupt status of asynchronous mode
 */
#define TSNS_ADVAN_ASYNC_IRQ_MASK (0x2000000UL)
#define TSNS_ADVAN_ASYNC_IRQ_SHIFT (25U)
#define TSNS_ADVAN_ASYNC_IRQ_GET(x) (((uint32_t)(x) & TSNS_ADVAN_ASYNC_IRQ_MASK) >> TSNS_ADVAN_ASYNC_IRQ_SHIFT)

/*
 * ACTIVE_IRQ (RO)
 *
 * interrupt status of active mode
 */
#define TSNS_ADVAN_ACTIVE_IRQ_MASK (0x1000000UL)
#define TSNS_ADVAN_ACTIVE_IRQ_SHIFT (24U)
#define TSNS_ADVAN_ACTIVE_IRQ_GET(x) (((uint32_t)(x) & TSNS_ADVAN_ACTIVE_IRQ_MASK) >> TSNS_ADVAN_ACTIVE_IRQ_SHIFT)

/*
 * SAMPLING (RO)
 *
 * temperature sampling is working
 */
#define TSNS_ADVAN_SAMPLING_MASK (0x10000UL)
#define TSNS_ADVAN_SAMPLING_SHIFT (16U)
#define TSNS_ADVAN_SAMPLING_GET(x) (((uint32_t)(x) & TSNS_ADVAN_SAMPLING_MASK) >> TSNS_ADVAN_SAMPLING_SHIFT)

/*
 * NEG_ONLY (RW)
 *
 * use negative compare polarity only
 */
#define TSNS_ADVAN_NEG_ONLY_MASK (0x2U)
#define TSNS_ADVAN_NEG_ONLY_SHIFT (1U)
#define TSNS_ADVAN_NEG_ONLY_SET(x) (((uint32_t)(x) << TSNS_ADVAN_NEG_ONLY_SHIFT) & TSNS_ADVAN_NEG_ONLY_MASK)
#define TSNS_ADVAN_NEG_ONLY_GET(x) (((uint32_t)(x) & TSNS_ADVAN_NEG_ONLY_MASK) >> TSNS_ADVAN_NEG_ONLY_SHIFT)

/*
 * POS_ONLY (RW)
 *
 * use positive compare polarity only
 */
#define TSNS_ADVAN_POS_ONLY_MASK (0x1U)
#define TSNS_ADVAN_POS_ONLY_SHIFT (0U)
#define TSNS_ADVAN_POS_ONLY_SET(x) (((uint32_t)(x) << TSNS_ADVAN_POS_ONLY_SHIFT) & TSNS_ADVAN_POS_ONLY_MASK)
#define TSNS_ADVAN_POS_ONLY_GET(x) (((uint32_t)(x) & TSNS_ADVAN_POS_ONLY_MASK) >> TSNS_ADVAN_POS_ONLY_SHIFT)




#endif /* HPM_TSNS_H */
