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

#ifndef HAL_INCLUDE_HAL_PWM_PERIPH_H_
#define HAL_INCLUDE_HAL_PWM_PERIPH_H_

/* ----------------------------------------------------------------------------
   -- PWM Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** PWM_Type Register Layout Typedef */
typedef struct
{
    volatile uint32_t cmd;             /**< ADV_TIMER0 command register. */
    volatile uint32_t config;          /**< ADV_TIMER0 configuration register. */
    volatile uint32_t threshold;       /**< ADV_TIMER0 threshold configuration register. */
    volatile uint32_t ch_threshold[4]; /**< ADV_TIMER0 channel threshold configuration register. */
    volatile uint32_t ch_lut[4];       /**< ADV_TIMER0 channel LUT configuration register. */
    volatile uint32_t counter;         /**< ADV_TIMER0 counter register. */
} pwm_t;

/* ----------------------------------------------------------------------------
   -- PWM Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name CMD */
/* ADV_TIMER0 start command bitfield. */
#define PWM_CMD_START_MASK                                           (0x1)
#define PWM_CMD_START_SHIFT                                          (0)
#define PWM_CMD_START(val)                                           (((uint32_t)(((uint32_t)(val)) << PWM_CMD_START_SHIFT)) & PWM_CMD_START_MASK)

/* ADV_TIMER0 stop command bitfield. */
#define PWM_CMD_STOP_MASK                                            (0x2)
#define PWM_CMD_STOP_SHIFT                                           (1)
#define PWM_CMD_STOP(val)                                            (((uint32_t)(((uint32_t)(val)) << PWM_CMD_STOP_SHIFT)) & PWM_CMD_STOP_MASK)

/* ADV_TIMER0 update command bitfield. */
#define PWM_CMD_UPDATE_MASK                                          (0x4)
#define PWM_CMD_UPDATE_SHIFT                                         (2)
#define PWM_CMD_UPDATE(val)                                          (((uint32_t)(((uint32_t)(val)) << PWM_CMD_UPDATE_SHIFT)) & PWM_CMD_UPDATE_MASK)

/* ADV_TIMER0 reset command bitfield. */
#define PWM_CMD_RESET_MASK                                           (0x8)
#define PWM_CMD_RESET_SHIFT                                          (3)
#define PWM_CMD_RESET(val)                                           (((uint32_t)(((uint32_t)(val)) << PWM_CMD_RESET_SHIFT)) & PWM_CMD_RESET_MASK)

/* ADV_TIMER0 arm command bitfield. */
#define PWM_CMD_ARM_MASK                                             (0x10)
#define PWM_CMD_ARM_SHIFT                                            (4)
#define PWM_CMD_ARM(val)                                             (((uint32_t)(((uint32_t)(val)) << PWM_CMD_ARM_SHIFT)) & PWM_CMD_ARM_MASK)


/*! @name CONFIG */
/* ADV_TIMER0 input source configuration bitfield:
  - 0-31: GPIO[0] to GPIO[31]
  - 32-35: Channel 0 to 3 of ADV_TIMER0
  - 36-39: Channel 0 to 3 of ADV_TIMER1
  - 40-43: Channel 0 to 3 of ADV_TIMER2
  - 44-47: Channel 0 to 3 of ADV_TIMER3 */
#define PWM_CONFIG_INSEL_MASK                                        (0xff)
#define PWM_CONFIG_INSEL_SHIFT                                       (0)
#define PWM_CONFIG_INSEL(val)                                        (((uint32_t)(((uint32_t)(val)) << PWM_CONFIG_INSEL_SHIFT)) & PWM_CONFIG_INSEL_MASK)

/* ADV_TIMER0 trigger mode configuration bitfield:
  - 3'h0: trigger event at each clock cycle.
  - 3'h1: trigger event if input source is 0
  - 3'h2: trigger event if input source is 1
  - 3'h3: trigger event on input source rising edge
  - 3'h4: trigger event on input source falling edge
  - 3'h5: trigger event on input source falling or rising edge
  - 3'h6: trigger event on input source rising edge when armed
  - 3'h7: trigger event on input source falling edge when armed */
#define PWM_CONFIG_MODE_MASK                                         (0x700)
#define PWM_CONFIG_MODE_SHIFT                                        (8)
#define PWM_CONFIG_MODE(val)                                         (((uint32_t)(((uint32_t)(val)) << PWM_CONFIG_MODE_SHIFT)) & PWM_CONFIG_MODE_MASK)

/* ADV_TIMER0 clock source configuration bitfield:
  - 1'b0: FLL
  - 1'b1: reference clock at 32kHz */
#define PWM_CONFIG_CLKSEL_MASK                                       (0x800)
#define PWM_CONFIG_CLKSEL_SHIFT                                      (11)
#define PWM_CONFIG_CLKSEL(val)                                       (((uint32_t)(((uint32_t)(val)) << PWM_CONFIG_CLKSEL_SHIFT)) & PWM_CONFIG_CLKSEL_MASK)

/* ADV_TIMER0 center-aligned mode configuration bitfield:
  - 1'b0: The counter counts up and down alternatively.
  - 1'b1: The counter counts up and resets to 0 when reach threshold. */
#define PWM_CONFIG_UPDOWNSEL_MASK                                    (0x1000)
#define PWM_CONFIG_UPDOWNSEL_SHIFT                                   (12)
#define PWM_CONFIG_UPDOWNSEL(val)                                    (((uint32_t)(((uint32_t)(val)) << PWM_CONFIG_UPDOWNSEL_SHIFT)) & PWM_CONFIG_UPDOWNSEL_MASK)

/* ADV_TIMER0 prescaler value configuration bitfield. */
#define PWM_CONFIG_PRESC_MASK                                        (0xff0000)
#define PWM_CONFIG_PRESC_SHIFT                                       (16)
#define PWM_CONFIG_PRESC(val)                                        (((uint32_t)(((uint32_t)(val)) << PWM_CONFIG_PRESC_SHIFT)) & PWM_CONFIG_PRESC_MASK)


/*! @name THRESHOLD */
/* ADV_TIMER0 threshold low part configuration bitfield. It defines start counter value. */
#define PWM_THRESHOLD_TH_LO_MASK                                     (0xffff)
#define PWM_THRESHOLD_TH_LO_SHIFT                                    (0)
#define PWM_THRESHOLD_TH_LO(val)                                     (((uint32_t)(((uint32_t)(val)) << PWM_THRESHOLD_TH_LO_SHIFT)) & PWM_THRESHOLD_TH_LO_MASK)

/* ADV_TIMER0 threshold high part configuration bitfield. It defines end counter value. */
#define PWM_THRESHOLD_TH_HI_MASK                                     (0xffff0000)
#define PWM_THRESHOLD_TH_HI_SHIFT                                    (16)
#define PWM_THRESHOLD_TH_HI(val)                                     (((uint32_t)(((uint32_t)(val)) << PWM_THRESHOLD_TH_HI_SHIFT)) & PWM_THRESHOLD_TH_HI_MASK)


/*! @name CH_THRESHOLD */
/* ADV_TIMER0 channel 0 threshold configuration bitfield. */
#define PWM_CH_THRESHOLD_TH_MASK                                     (0xffff)
#define PWM_CH_THRESHOLD_TH_SHIFT                                    (0)
#define PWM_CH_THRESHOLD_TH(val)                                     (((uint32_t)(((uint32_t)(val)) << PWM_CH_THRESHOLD_TH_SHIFT)) & PWM_CH_THRESHOLD_TH_MASK)

/* ADV_TIMER0 channel 0 threshold match action on channel output signal configuration bitfield:
  - 3'h0: set.
  - 3'h1: toggle then next threshold match action is clear.
  - 3'h2: set then next threshold match action is clear.
  - 3'h3: toggle.
  - 3'h4: clear.
  - 3'h5: toggle then next threshold match action is set.
  - 3'h6: clear then next threshold match action is set. */
#define PWM_CH_THRESHOLD_MODE_MASK                                   (0x70000)
#define PWM_CH_THRESHOLD_MODE_SHIFT                                  (16)
#define PWM_CH_THRESHOLD_MODE(val)                                   (((uint32_t)(((uint32_t)(val)) << PWM_CH_THRESHOLD_MODE_SHIFT)) & PWM_CH_THRESHOLD_MODE_MASK)


/*! @name CH_LUT */

/*! @name COUNTER */

/*! @name CMD */
typedef union
{
    struct
    {
        /* ADV_TIMER0 start command bitfield. */
        uint32_t start:1;
        /* ADV_TIMER0 stop command bitfield. */
        uint32_t stop:1;
        /* ADV_TIMER0 update command bitfield. */
        uint32_t update:1;
        /* ADV_TIMER0 reset command bitfield. */
        uint32_t reset:1;
        /* ADV_TIMER0 arm command bitfield. */
        uint32_t arm:1;
    } field;
    uint32_t word;
} pwm_cmd_t;

/*! @name CONFIG */
typedef union
{
    struct
    {
        /* ADV_TIMER0 input source configuration bitfield:
        - 0-31: GPIO[0] to GPIO[31]
        - 32-35: Channel 0 to 3 of ADV_TIMER0
        - 36-39: Channel 0 to 3 of ADV_TIMER1
        - 40-43: Channel 0 to 3 of ADV_TIMER2
        - 44-47: Channel 0 to 3 of ADV_TIMER3 */
        uint32_t insel:8;
        /* ADV_TIMER0 trigger mode configuration bitfield:
        - 3'h0: trigger event at each clock cycle.
        - 3'h1: trigger event if input source is 0
        - 3'h2: trigger event if input source is 1
        - 3'h3: trigger event on input source rising edge
        - 3'h4: trigger event on input source falling edge
        - 3'h5: trigger event on input source falling or rising edge
        - 3'h6: trigger event on input source rising edge when armed
        - 3'h7: trigger event on input source falling edge when armed */
        uint32_t mode:3;
        /* ADV_TIMER0 clock source configuration bitfield:
        - 1'b0: FLL
        - 1'b1: reference clock at 32kHz */
        uint32_t clksel:1;
        /* ADV_TIMER0 center-aligned mode configuration bitfield:
        - 1'b0: The counter counts up and down alternatively.
        - 1'b1: The counter counts up and resets to 0 when reach threshold. */
        uint32_t updownsel:1;
        uint32_t reserved_0:3;
        /* ADV_TIMER0 prescaler value configuration bitfield. */
        uint32_t presc:8;
    } field;
    uint32_t word;
} pwm_config_t;

/*! @name THRESHOLD */
typedef union
{
    struct
    {
        /* ADV_TIMER0 threshold low part configuration bitfield. It defines start counter value. */
        uint32_t th_lo:16;
        /* ADV_TIMER0 threshold high part configuration bitfield. It defines end counter value. */
        uint32_t th_hi:16;
    } field;
    uint32_t word;
} pwm_threshold_t;

/*! @name CH_THRESHOLD */
typedef union
{
    struct
    {
        /* ADV_TIMER0 channel 0 threshold configuration bitfield. */
        uint32_t th:16;
        /* ADV_TIMER0 channel 0 threshold match action on channel output signal configuration bitfield:
        - 3'h0: set.
        - 3'h1: toggle then next threshold match action is clear.
        - 3'h2: set then next threshold match action is clear.
        - 3'h3: toggle.
        - 3'h4: clear.
        - 3'h5: toggle then next threshold match action is set.
        - 3'h6: clear then next threshold match action is set. */
        uint32_t mode:3;
    } field;
    uint32_t word;
} pwm_ch_threshold_t;

/*! @name CH_LUT */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} pwm_ch_lut_t;

/*! @name COUNTER */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} pwm_counter_t;


#endif /* HAL_INCLUDE_HAL_PWM_PERIPH_H_ */
