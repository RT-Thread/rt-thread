/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef HAL_INCLUDE_HAL_FLL_H_
#define HAL_INCLUDE_HAL_FLL_H_

#define FLL_STATUS_OFFSET        0x000
#define FLL_CONF1_OFFSET         0x004
#define FLL_CONF2_OFFSET         0x008
#define FLL_INTEGRATOR_OFFSET    0x00C

#define FLL_STATUS_MULT_FACTOR_BIT                 0
#define FLL_STATUS_MULT_FACTOR_WIDTH               16
#define FLL_STATUS_MULT_FACTOR_MASK                (0xFFFF)

#define FLL_CONF1_MODE_BIT                       31
#define FLL_CONF1_MODE_WIDTH                     1
#define FLL_CONF1_MODE_MASK                      (0x80000000)

#define FLL_CONF1_LOCK_BIT                       30
#define FLL_CONF1_LOCK_WIDTH                     1
#define FLL_CONF1_LOCK_MASK                      (0x40000000)

#define FLL_CONF1_DIV_BIT                        26
#define FLL_CONF1_DIV_WIDTH                      4
#define FLL_CONF1_DIV_MASK                       (0x3C000000)

#define FLL_CONF1_DCO_BIT                        16
#define FLL_CONF1_DCO_WIDTH                      10
#define FLL_CONF1_DCO_MASK                       (0x03FF0000)

#define FLL_CONF1_MULT_FACTOR_BIT                0
#define FLL_CONF1_MULT_FACTOR_WIDTH              16
#define FLL_CONF1_MULT_FACTOR_MASK               (0xFFFF)

#define FLL_CONF1_MODE_STANDALONE                0
#define FLL_CONF1_MODE_NORMAL                    1

#define FLL_CONF2_GAIN_BIT                       0
#define FLL_CONF2_GAIN_WIDTH                     4
#define FLL_CONF2_GAIN_MASK                      (0x0000000F)

#define FLL_CONF2_DEASSERT_CYCLES_BIT            4
#define FLL_CONF2_DEASSERT_CYCLES_WIDTH          6
#define FLL_CONF2_DEASSERT_CYCLES_MASK           (0x000003F0)

#define FLL_CONF2_ASSERT_CYCLES_BIT              10
#define FLL_CONF2_ASSERT_CYCLES_WIDTH            6
#define FLL_CONF2_ASSERT_CYCLES_MASK             (0x0000FC00)

#define FLL_CONF2_TOLERANCE_BIT                  16
#define FLL_CONF2_TOLERANCE_WIDTH                12
#define FLL_CONF2_TOLERANCE_MASK                 (0x0FFF0000)

#define FLL_CONF2_STA_CLOCK_BIT                  29
#define FLL_CONF2_STA_CLOCK_WIDTH                1
#define FLL_CONF2_STA_CLOCK_MASK                 (0x20000000)

#define FLL_CONF2_OPEN_LOOP_BIT                  30
#define FLL_CONF2_OPEN_LOOP_WIDTH                1
#define FLL_CONF2_OPEN_LOOP_MASK                 (0x40000000)

#define FLL_CONF2_DITHERING_BIT                  31
#define FLL_CONF2_DITHERING_WIDTH                1
#define FLL_CONF2_DITHERING_MASK                 (0x80000000)

#define FLL_INTEGRATOR_INT_BIT                       16
#define FLL_INTEGRATOR_INT_WIDTH                     10
#define FLL_INTEGRATOR_INT_MASK                      (0x03FF0000)

#define FLL_INTEGRATOR_FRACT_BIT                     6
#define FLL_INTEGRATOR_FRACT_WIDTH                   10
#define FLL_INTEGRATOR_FRACT_MASK                    (0x0000FFC0)

#if !defined(LANGUAGE_ASSEMBLY) && !defined(_ASMLANGUAGE)

typedef union {
  struct {
    unsigned int actual_mult_factor:16;  /* Fll current multiplication factor */
    unsigned int reserved:16;
  };
  unsigned int raw;
} fll_reg_status_t;

typedef union {
  struct {
    unsigned int mult_factor:16;      /* Fll requested multiplication factor, reset: 0x5f5.
                                         If RefClk=32768 and Div=2 Freq= 24.98 MHz */
    unsigned int dco_input:10;        /* DCO input code for stand alone mode, reset: 0x121 */
    unsigned int clock_out_divider:4; /* Fll clock output divider, reset: 0x1 e.g div 2 */
    unsigned int output_lock_enable:1;/* Fll output gated by lock signal (active high), reset 1 */
    unsigned int mode:1;              /* Fll mode. 0: stand alone (unlocked), 1: normal, reset 0 */
  };
  unsigned int raw;
} fll_reg_conf1_t;

typedef union {
  struct {
    unsigned int loop_gain:4;         /* Fll loop gain, reset: 0x9 */
    unsigned int de_assert_cycles:6;  /* Normal mode: number of refclock unstable cycles till lock de-assert
                                         Standalone mode: lower 6 bits of lock assert counter. Reset: 0x10 */
    unsigned int assert_cycles:6;     /* Normal mode: number of refclock stable cycles till lock assert
                                         Standalone mode: upper 6 bits of lock assert counter. Reset: 0x10 */
    unsigned int lock_tolerance:12;   /* Lock tolerance: margin arounf the target mult factor where clock is
                                         considered as stable. Reset: 0x200
                                         With Fmax=250Mhw (Div=2^4), Fmin=32K (Div=2^15)
                                         Tolerance: 32K*(512/16)=1.048MHz .. 512 Hz */
    unsigned int pad:1;
    unsigned int config_clock_sel:1;  /* Select ref clock when mode = standalone, 0:RefClock, 1: DcoOut. Reset:1 */
    unsigned int open_loop:1;         /* When 1 clock operates in open loop when locked */
    unsigned int dithering:1;         /* When 1 Dithering is enabled */
  };
  unsigned int raw;
} fll_reg_conf2_t;

typedef union {
  struct {
    unsigned int pad1:6;
    unsigned int state_fract_part:10; /* Integrator state: fractional part (dithering input unit) */
    unsigned int state_int_part:10;   /* Integratot state: integer part (DCO input bits) */
    unsigned int pad2:6;
  };
  unsigned int raw;
} fll_reg_integrator_t;

#endif



#define FLL_STATUS_MULT_FACTOR_GET(value)          ((((unsigned int)(value)) >> 0) & 0xFFFF)
#define FLL_STATUS_MULT_FACTOR_SET(dst,src,factor) (__BITINSERT((dst),(src),16,0))
#define FLL_STATUS_MULT_FACTOR(factor)             ((factor) << 16)


#define FLL_CONF1_MODE_GET(value)                ((((unsigned int)(value)) >> 16) & 0x1)
#define FLL_CONF1_MODE_SET(dst,src)              (__BITINSERT((dst),(src),1,31))
#define FLL_CONF1_MODE(factor)                   ((factor) << 31)

#define FLL_CONF1_LOCK_GET(value)                ((((unsigned int)(value)) >> 16) & 0x1)
#define FLL_CONF1_LOCK_SET(dst,src)              (__BITINSERT((dst),(src),30,1))
#define FLL_CONF1_LOCK(factor)                   ((factor) << 30)

#define FLL_CONF1_DIV_GET(value)                 ((((unsigned int)(value)) >> 26) & 0xF)
#define FLL_CONF1_DIV_SET(dst,src)               (__BITINSERT((dst),(src),26,4))
#define FLL_CONF1_DIV(factor)                    ((factor) << 26)

#define FLL_CONF1_DCO_GET(value)                 ((((unsigned int)(value)) >> 16) & 0x3FF)
#define FLL_CONF1_DCO_SET(dst,src)               (__BITINSERT((dst),(src),16,10))
#define FLL_CONF1_DCO(factor)                    ((factor) << 16)

#define FLL_CONF1_MULT_FACTOR_GET(value)         ((((unsigned int)(value)) >> 0) &0xFFFF)
#define FLL_CONF1_MULT_FACTOR_SET(dst,src)       (__BITINSERT((dst),(src),0,16))
#define FLL_CONF1_MULT_FACTOR(factor)            ((factor) << 0)

#define FLL_CONF2_GAIN_GET(value)                ((((unsigned int)(value)) >> 0) & 0xF)
#define FLL_CONF2_GAIN_SET(dst,src)              (__BITINSERT((dst),(src),4,0))
#define FLL_CONF2_GAIN(value)                    ((value) << 0)

#define FLL_CONF2_ASSERT_CYCLES_GET(value)       ((((unsigned int)(value)) >> 4) & 0x3F)
#define FLL_CONF2_ASSERT_CYCLES_SET(dst,src)     (__BITINSERT((dst),(src),6,4))
#define FLL_CONF2_ASSERT_CYCLES(value)           ((value) << 4)

#define FLL_CONF2_DEASSERT_CYCLES_GET(value)     ((((unsigned int)(value)) >> 10) & 0x3F)
#define FLL_CONF2_DEASSERT_CYCLES_SET(dst,src)   (__BITINSERT((dst),(src),6,10))
#define FLL_CONF2_DEASSERT_CYCLES(value)         ((value) << 10)

#define FLL_CONF2_TOLERANCE_GET(value)           ((((unsigned int)(value)) >> 16) & 0xFFF)
#define FLL_CONF2_TOLERANCE_SET(dst,src)         (__BITINSERT((dst),(src),12,16))
#define FLL_CONF2_TOLERANCE(value)               ((value) << 16)

#define FLL_CONF2_STA_CLOCK_GET(value)           ((((unsigned int)(value)) >> 29) & 0x1)
#define FLL_CONF2_STA_CLOCK_SET(dst,src)         (__BITINSERT((dst),(src),1,29))
#define FLL_CONF2_STA_CLOCK(value)               ((value) << 29)

#define FLL_CONF2_OPEN_LOOP_GET(value)           ((((unsigned int)(value)) >> 30) & 0x1)
#define FLL_CONF2_OPEN_LOOP_SET(dst,src)         (__BITINSERT((dst),(src),1,30))
#define FLL_CONF2_OPEN_LOOP(value)               ((value) << 30)

#define FLL_CONF2_DITHER_GET(value)              ((((unsigned int)(value)) >> 31) & 0x1)
#define FLL_CONF2_DITHER_SET(dst,src)            (__BITINSERT((dst),(src),1,31))
#define FLL_CONF2_DITHER(value)                  ((value) << 31)

#define FLL_INTEGRATOR_FRACT_GET(value)          ((((unsigned int)(value)) >> 6) & 0x3FF)
#define FLL_INTEGRATOR_FRACT_SET(dst,src)        (__BITINSERT((dst),(src),6,10))
#define FLL_INTEGRATOR_FRACT(value)              ((value) << 6)

#define FLL_INTEGRATOR_INT_GET(value)          ((((unsigned int)(value)) >> 16) & 0x3FF)
#define FLL_INTEGRATOR_INT_SET(dst,src)        (__BITINSERT((dst),(src),16,10))
#define FLL_INTEGRATOR_INT(value)              ((value) << 16)

/* Maximum Log2(DCO Frequency) */
#define FLL_LOG2_MAXDCO     29
/* Maximum Log2(Clok Divider) */
#define FLL_LOG2_MAXDIV     15
/* Maximum Log2(Multiplier) */
#define FLL_LOG2_MAXM       (FLL_LOG2_MAXDCO - ARCHI_REF_CLOCK_LOG2)

/* TODO: doc */
void pulp_fll_init(void);
unsigned int __fll_init(int fll);
unsigned int __rt_fll_set_freq(int fll, unsigned int frequency);

#endif /* HAL_INCLUDE_HAL_FLL_H_ */
