/* THIS FILE HAS BEEN GENERATED, DO NOT MODIFY IT. */
/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 * and GreenWaves Technologies
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
 */


#ifndef HAL_INCLUDE_HAL_PWM_CTRL_PERIPH_H_
#define HAL_INCLUDE_HAL_PWM_CTRL_PERIPH_H_

/* ----------------------------------------------------------------------------
   -- PWM_CTRL Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** PWM_CTRL_Type Register Layout Typedef */
typedef struct
{
    volatile uint32_t event_cfg; /**< ADV_TIMERS events configuration register. */
    volatile uint32_t cg; /**< ADV_TIMERS channels clock gating configuration register. */
} pwm_ctrl_t;

/* ----------------------------------------------------------------------------
   -- PWM_CTRL Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name EVENT_CFG */
/* ADV_TIMER output event 0 source configuration bitfiled:
  - 4'h0: ADV_TIMER0 channel 0.
  - 4'h1: ADV_TIMER0 channel 1.
  - 4'h2: ADV_TIMER0 channel 2.
  - 4'h3: ADV_TIMER0 channel 3.
  - 4'h4: ADV_TIMER1 channel 0.
  - 4'h5: ADV_TIMER1 channel 1.
  - 4'h6: ADV_TIMER1 channel 2.
  - 4'h7: ADV_TIMER1 channel 3.
  - 4'h8: ADV_TIMER2 channel 0.
  - 4'h9: ADV_TIMER2 channel 1.
  - 4'hA: ADV_TIMER2 channel 2.
  - 4'hB: ADV_TIMER2 channel 3.
  - 4'hC: ADV_TIMER3 channel 0.
  - 4'hD: ADV_TIMER3 channel 1.
  - 4'hE: ADV_TIMER3 channel 2.
  - 4'hF: ADV_TIMER3 channel 3. */
#define PWM_CTRL_EVENT_CFG_SEL0_MASK                                 (0xf)
#define PWM_CTRL_EVENT_CFG_SEL0_SHIFT                                (0)
#define PWM_CTRL_EVENT_CFG_SEL0(val)                                 (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_EVENT_CFG_SEL0_SHIFT)) & PWM_CTRL_EVENT_CFG_SEL0_MASK)

/* ADV_TIMER output event 1 source configuration bitfiled:
  - 4'h0: ADV_TIMER0 channel 0.
  - 4'h1: ADV_TIMER0 channel 1.
  - 4'h2: ADV_TIMER0 channel 2.
  - 4'h3: ADV_TIMER0 channel 3.
  - 4'h4: ADV_TIMER1 channel 0.
  - 4'h5: ADV_TIMER1 channel 1.
  - 4'h6: ADV_TIMER1 channel 2.
  - 4'h7: ADV_TIMER1 channel 3.
  - 4'h8: ADV_TIMER2 channel 0.
  - 4'h9: ADV_TIMER2 channel 1.
  - 4'hA: ADV_TIMER2 channel 2.
  - 4'hB: ADV_TIMER2 channel 3.
  - 4'hC: ADV_TIMER3 channel 0.
  - 4'hD: ADV_TIMER3 channel 1.
  - 4'hE: ADV_TIMER3 channel 2.
  - 4'hF: ADV_TIMER3 channel 3. */
#define PWM_CTRL_EVENT_CFG_SEL1_MASK                                 (0xf0)
#define PWM_CTRL_EVENT_CFG_SEL1_SHIFT                                (4)
#define PWM_CTRL_EVENT_CFG_SEL1(val)                                 (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_EVENT_CFG_SEL1_SHIFT)) & PWM_CTRL_EVENT_CFG_SEL1_MASK)

/* ADV_TIMER output event 2 source configuration bitfiled:
  - 4'h0: ADV_TIMER0 channel 0.
  - 4'h1: ADV_TIMER0 channel 1.
  - 4'h2: ADV_TIMER0 channel 2.
  - 4'h3: ADV_TIMER0 channel 3.
  - 4'h4: ADV_TIMER1 channel 0.
  - 4'h5: ADV_TIMER1 channel 1.
  - 4'h6: ADV_TIMER1 channel 2.
  - 4'h7: ADV_TIMER1 channel 3.
  - 4'h8: ADV_TIMER2 channel 0.
  - 4'h9: ADV_TIMER2 channel 1.
  - 4'hA: ADV_TIMER2 channel 2.
  - 4'hB: ADV_TIMER2 channel 3.
  - 4'hC: ADV_TIMER3 channel 0.
  - 4'hD: ADV_TIMER3 channel 1.
  - 4'hE: ADV_TIMER3 channel 2.
  - 4'hF: ADV_TIMER3 channel 3. */
#define PWM_CTRL_EVENT_CFG_SEL2_MASK                                 (0xf00)
#define PWM_CTRL_EVENT_CFG_SEL2_SHIFT                                (8)
#define PWM_CTRL_EVENT_CFG_SEL2(val)                                 (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_EVENT_CFG_SEL2_SHIFT)) & PWM_CTRL_EVENT_CFG_SEL2_MASK)

/* ADV_TIMER output event 3 source configuration bitfiled:
  - 4'h0: ADV_TIMER0 channel 0.
  - 4'h1: ADV_TIMER0 channel 1.
  - 4'h2: ADV_TIMER0 channel 2.
  - 4'h3: ADV_TIMER0 channel 3.
  - 4'h4: ADV_TIMER1 channel 0.
  - 4'h5: ADV_TIMER1 channel 1.
  - 4'h6: ADV_TIMER1 channel 2.
  - 4'h7: ADV_TIMER1 channel 3.
  - 4'h8: ADV_TIMER2 channel 0.
  - 4'h9: ADV_TIMER2 channel 1.
  - 4'hA: ADV_TIMER2 channel 2.
  - 4'hB: ADV_TIMER2 channel 3.
  - 4'hC: ADV_TIMER3 channel 0.
  - 4'hD: ADV_TIMER3 channel 1.
  - 4'hE: ADV_TIMER3 channel 2.
  - 4'hF: ADV_TIMER3 channel 3. */
#define PWM_CTRL_EVENT_CFG_SEL3_MASK                                 (0xf000)
#define PWM_CTRL_EVENT_CFG_SEL3_SHIFT                                (12)
#define PWM_CTRL_EVENT_CFG_SEL3(val)                                 (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_EVENT_CFG_SEL3_SHIFT)) & PWM_CTRL_EVENT_CFG_SEL3_MASK)

/* ADV_TIMER output event enable configuration bitfield. ENA[i]=1 enables output event i generation. */
#define PWM_CTRL_EVENT_CFG_ENA_MASK                                  (0xf0000)
#define PWM_CTRL_EVENT_CFG_ENA_SHIFT                                 (16)
#define PWM_CTRL_EVENT_CFG_ENA(val)                                  (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_EVENT_CFG_ENA_SHIFT)) & PWM_CTRL_EVENT_CFG_ENA_MASK)


/*! @name CG */
/* ADV_TIMER clock gating configuration bitfield.
  - ENA[i]=0: clock gate ADV_TIMERi.
  - ENA[i]=1: enable ADV_TIMERi.  */
#define PWM_CTRL_CG_ENA_MASK                                         (0xffff)
#define PWM_CTRL_CG_ENA_SHIFT                                        (0)
#define PWM_CTRL_CG_ENA(val)                                         (((uint32_t)(((uint32_t)(val)) << PWM_CTRL_CG_ENA_SHIFT)) & PWM_CTRL_CG_ENA_MASK)


/*! @name EVENT_CFG */
typedef union
{
    struct
    {
        /* ADV_TIMER output event 0 source configuration bitfiled:
        - 4'h0: ADV_TIMER0 channel 0.
        - 4'h1: ADV_TIMER0 channel 1.
        - 4'h2: ADV_TIMER0 channel 2.
        - 4'h3: ADV_TIMER0 channel 3.
        - 4'h4: ADV_TIMER1 channel 0.
        - 4'h5: ADV_TIMER1 channel 1.
        - 4'h6: ADV_TIMER1 channel 2.
        - 4'h7: ADV_TIMER1 channel 3.
        - 4'h8: ADV_TIMER2 channel 0.
        - 4'h9: ADV_TIMER2 channel 1.
        - 4'hA: ADV_TIMER2 channel 2.
        - 4'hB: ADV_TIMER2 channel 3.
        - 4'hC: ADV_TIMER3 channel 0.
        - 4'hD: ADV_TIMER3 channel 1.
        - 4'hE: ADV_TIMER3 channel 2.
        - 4'hF: ADV_TIMER3 channel 3. */
        uint32_t sel0:4;
        /* ADV_TIMER output event 1 source configuration bitfiled:
        - 4'h0: ADV_TIMER0 channel 0.
        - 4'h1: ADV_TIMER0 channel 1.
        - 4'h2: ADV_TIMER0 channel 2.
        - 4'h3: ADV_TIMER0 channel 3.
        - 4'h4: ADV_TIMER1 channel 0.
        - 4'h5: ADV_TIMER1 channel 1.
        - 4'h6: ADV_TIMER1 channel 2.
        - 4'h7: ADV_TIMER1 channel 3.
        - 4'h8: ADV_TIMER2 channel 0.
        - 4'h9: ADV_TIMER2 channel 1.
        - 4'hA: ADV_TIMER2 channel 2.
        - 4'hB: ADV_TIMER2 channel 3.
        - 4'hC: ADV_TIMER3 channel 0.
        - 4'hD: ADV_TIMER3 channel 1.
        - 4'hE: ADV_TIMER3 channel 2.
        - 4'hF: ADV_TIMER3 channel 3. */
        uint32_t sel1:4;
        /* ADV_TIMER output event 2 source configuration bitfiled:
        - 4'h0: ADV_TIMER0 channel 0.
        - 4'h1: ADV_TIMER0 channel 1.
        - 4'h2: ADV_TIMER0 channel 2.
        - 4'h3: ADV_TIMER0 channel 3.
        - 4'h4: ADV_TIMER1 channel 0.
        - 4'h5: ADV_TIMER1 channel 1.
        - 4'h6: ADV_TIMER1 channel 2.
        - 4'h7: ADV_TIMER1 channel 3.
        - 4'h8: ADV_TIMER2 channel 0.
        - 4'h9: ADV_TIMER2 channel 1.
        - 4'hA: ADV_TIMER2 channel 2.
        - 4'hB: ADV_TIMER2 channel 3.
        - 4'hC: ADV_TIMER3 channel 0.
        - 4'hD: ADV_TIMER3 channel 1.
        - 4'hE: ADV_TIMER3 channel 2.
        - 4'hF: ADV_TIMER3 channel 3. */
        uint32_t sel2:4;
        /* ADV_TIMER output event 3 source configuration bitfiled:
        - 4'h0: ADV_TIMER0 channel 0.
        - 4'h1: ADV_TIMER0 channel 1.
        - 4'h2: ADV_TIMER0 channel 2.
        - 4'h3: ADV_TIMER0 channel 3.
        - 4'h4: ADV_TIMER1 channel 0.
        - 4'h5: ADV_TIMER1 channel 1.
        - 4'h6: ADV_TIMER1 channel 2.
        - 4'h7: ADV_TIMER1 channel 3.
        - 4'h8: ADV_TIMER2 channel 0.
        - 4'h9: ADV_TIMER2 channel 1.
        - 4'hA: ADV_TIMER2 channel 2.
        - 4'hB: ADV_TIMER2 channel 3.
        - 4'hC: ADV_TIMER3 channel 0.
        - 4'hD: ADV_TIMER3 channel 1.
        - 4'hE: ADV_TIMER3 channel 2.
        - 4'hF: ADV_TIMER3 channel 3. */
        uint32_t sel3:4;
        /* ADV_TIMER output event enable configuration bitfield. ENA[i]=1 enables output event i generation. */
        uint32_t ena:4;
    } field;
    uint32_t word;
} pwm_ctrl_event_cfg_t;

/*! @name CG */
typedef union
{
    struct
    {
        /* ADV_TIMER clock gating configuration bitfield.
        - ENA[i]=0: clock gate ADV_TIMERi.
        - ENA[i]=1: enable ADV_TIMERi.  */
        uint32_t ena:16;
    } field;
    uint32_t word;
} pwm_ctrl_cg_t;


#endif /* HAL_INCLUDE_HAL_PWM_CTRL_PERIPH_H_ */
