/*
 * This is a generated file
 * 
 * Copyright 2021 QuickLogic
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

#ifndef __ADV_TIMER_UNIT_H_
#define __ADV_TIMER_UNIT_H_

//---------------------------------//
//
// Module: ADV_TIMER_UNIT
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

#ifndef __I
#define __I volatile
#endif

#ifndef __O
#define __O volatile
#endif

#include "stdint.h"

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t timer_0_cmd_register;
    struct {
      __IO uint32_t  start_command :  1;
      __IO uint32_t  stop_command :  1;
      __IO uint32_t  update_command :  1;
      __IO uint32_t  reset_command :  1;
      __IO uint32_t  arm_command :  1;
      __IO uint32_t  reserved1  : 27;
    } timer_0_cmd_register_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t timer_0_config_register;
    struct {
      __IO uint32_t  input_source_sel :  8;
      __IO uint32_t  trigger_mode_sel :  3;
      __IO uint32_t  clock_sel  :  1;
      __IO uint32_t  up_down_counter_sel :  1;
      __IO uint32_t  reserved2  :  3;
      __IO uint32_t  prescaler_value :  8;
      __IO uint32_t  reserved1  :  8;
    } timer_0_config_register_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t timer_0_threshold_register;
    struct {
      __IO uint32_t  threshold_low : 16;
      __IO uint32_t  threshold_high : 16;
    } timer_0_threshold_register_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t timer_0_threshold_channel_0_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_0_threshold_channel_0_reg_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t timer_0_threshold_channel_1_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_0_threshold_channel_1_reg_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t timer_0_threshold_channel_2_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_0_threshold_channel_2_reg_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t timer_0_threshold_channel_3_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_0_threshold_channel_3_reg_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t timer_0_threshold_channel_0_lut;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t timer_0_threshold_channel_1_lut;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t timer_0_threshold_channel_2_lut;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t timer_0_threshold_channel_3_lut;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t timer_0_counter_status_register;
    struct {
      __IO uint32_t  counter_value : 16;
      __IO uint32_t  reserved1  : 16;
    } timer_0_counter_status_register_b;
  };
  __I uint32_t    unused0[4];

  // Offset = 0x0040
  union {
    __IO uint32_t timer_1_cmd_register;
    struct {
      __IO uint32_t  start_command :  1;
      __IO uint32_t  stop_command :  1;
      __IO uint32_t  update_command :  1;
      __IO uint32_t  reset_command :  1;
      __IO uint32_t  arm_command :  1;
      __IO uint32_t  reserved1  : 27;
    } timer_1_cmd_register_b;
  };

  // Offset = 0x0044
  union {
    __IO uint32_t timer_1_config_register;
    struct {
      __IO uint32_t  input_source_sel :  8;
      __IO uint32_t  trigger_mode_sel :  3;
      __IO uint32_t  clock_sel  :  1;
      __IO uint32_t  up_down_counter_sel :  1;
      __IO uint32_t  reserved2  :  3;
      __IO uint32_t  prescaler_value :  8;
      __IO uint32_t  reserved1  :  8;
    } timer_1_config_register_b;
  };

  // Offset = 0x0048
  union {
    __IO uint32_t timer_1_threshold_register;
    struct {
      __IO uint32_t  threshold_low : 16;
      __IO uint32_t  threshold_high : 16;
    } timer_1_threshold_register_b;
  };

  // Offset = 0x004c
  union {
    __IO uint32_t timer_1_threshold_channel_0_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_1_threshold_channel_0_reg_b;
  };

  // Offset = 0x0050
  union {
    __IO uint32_t timer_1_threshold_channel_1_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_1_threshold_channel_1_reg_b;
  };

  // Offset = 0x0054
  union {
    __IO uint32_t timer_1_threshold_channel_2_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_1_threshold_channel_2_reg_b;
  };

  // Offset = 0x0058
  union {
    __IO uint32_t timer_1_threshold_channel_3_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_1_threshold_channel_3_reg_b;
  };

  // Offset = 0x005c
  union {
    __IO uint32_t timer_1_threshold_channel_0_lut;
  };

  // Offset = 0x0060
  union {
    __IO uint32_t timer_1_threshold_channel_1_lut;
  };

  // Offset = 0x0064
  union {
    __IO uint32_t timer_1_threshold_channel_2_lut;
  };

  // Offset = 0x0068
  union {
    __IO uint32_t timer_1_threshold_channel_3_lut;
  };

  // Offset = 0x006c
  union {
    __IO uint32_t timer_1_counter_status_register;
    struct {
      __IO uint32_t  counter_value : 16;
      __IO uint32_t  reserved1  : 16;
    } timer_1_counter_status_register_b;
  };
  __I uint32_t    unused1[4];

  // Offset = 0x0080
  union {
    __IO uint32_t timer_2_cmd_register;
    struct {
      __IO uint32_t  start_command :  1;
      __IO uint32_t  stop_command :  1;
      __IO uint32_t  update_command :  1;
      __IO uint32_t  reset_command :  1;
      __IO uint32_t  arm_command :  1;
      __IO uint32_t  reserved1  : 27;
    } timer_2_cmd_register_b;
  };

  // Offset = 0x0084
  union {
    __IO uint32_t timer_2_config_register;
    struct {
      __IO uint32_t  input_source_sel :  8;
      __IO uint32_t  trigger_mode_sel :  3;
      __IO uint32_t  clock_sel  :  1;
      __IO uint32_t  up_down_counter_sel :  1;
      __IO uint32_t  reserved2  :  3;
      __IO uint32_t  prescaler_value :  8;
      __IO uint32_t  reserved1  :  8;
    } timer_2_config_register_b;
  };

  // Offset = 0x0088
  union {
    __IO uint32_t timer_2_threshold_register;
    struct {
      __IO uint32_t  threshold_low : 16;
      __IO uint32_t  threshold_high : 16;
    } timer_2_threshold_register_b;
  };

  // Offset = 0x008c
  union {
    __IO uint32_t timer_2_threshold_channel_0_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_2_threshold_channel_0_reg_b;
  };

  // Offset = 0x0090
  union {
    __IO uint32_t timer_2_threshold_channel_1_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_2_threshold_channel_1_reg_b;
  };

  // Offset = 0x0094
  union {
    __IO uint32_t timer_2_threshold_channel_2_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_2_threshold_channel_2_reg_b;
  };

  // Offset = 0x0098
  union {
    __IO uint32_t timer_2_threshold_channel_3_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_2_threshold_channel_3_reg_b;
  };

  // Offset = 0x009c
  union {
    __IO uint32_t timer_2_threshold_channel_0_lut;
  };

  // Offset = 0x00a0
  union {
    __IO uint32_t timer_2_threshold_channel_1_lut;
  };

  // Offset = 0x00a4
  union {
    __IO uint32_t timer_2_threshold_channel_2_lut;
  };

  // Offset = 0x00a8
  union {
    __IO uint32_t timer_2_threshold_channel_3_lut;
  };

  // Offset = 0x00ac
  union {
    __IO uint32_t timer_2_counter_status_register;
    struct {
      __IO uint32_t  counter_value : 16;
      __IO uint32_t  reserved1  : 16;
    } timer_2_counter_status_register_b;
  };
  __I uint32_t    unused2[4];

  // Offset = 0x00c0
  union {
    __IO uint32_t timer_3_cmd_register;
    struct {
      __IO uint32_t  start_command :  1;
      __IO uint32_t  stop_command :  1;
      __IO uint32_t  update_command :  1;
      __IO uint32_t  reset_command :  1;
      __IO uint32_t  arm_command :  1;
      __IO uint32_t  reserved1  : 27;
    } timer_3_cmd_register_b;
  };

  // Offset = 0x00c4
  union {
    __IO uint32_t timer_3_config_register;
    struct {
      __IO uint32_t  input_source_sel :  8;
      __IO uint32_t  trigger_mode_sel :  3;
      __IO uint32_t  clock_sel  :  1;
      __IO uint32_t  up_down_counter_sel :  1;
      __IO uint32_t  reserved2  :  3;
      __IO uint32_t  prescaler_value :  8;
      __IO uint32_t  reserved1  :  8;
    } timer_3_config_register_b;
  };

  // Offset = 0x00c8
  union {
    __IO uint32_t timer_3_threshold_register;
    struct {
      __IO uint32_t  threshold_low : 16;
      __IO uint32_t  threshold_high : 16;
    } timer_3_threshold_register_b;
  };

  // Offset = 0x00cc
  union {
    __IO uint32_t timer_3_threshold_channel_0_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_3_threshold_channel_0_reg_b;
  };

  // Offset = 0x00d0
  union {
    __IO uint32_t timer_3_threshold_channel_1_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_3_threshold_channel_1_reg_b;
  };

  // Offset = 0x00d4
  union {
    __IO uint32_t timer_3_threshold_channel_2_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_3_threshold_channel_2_reg_b;
  };

  // Offset = 0x00d8
  union {
    __IO uint32_t timer_3_threshold_channel_3_reg;
    struct {
      __IO uint32_t  threshold_value : 16;
      __IO uint32_t  threshold_mode :  3;
      __IO uint32_t  reserved1  : 13;
    } timer_3_threshold_channel_3_reg_b;
  };

  // Offset = 0x00dc
  union {
    __IO uint32_t timer_3_threshold_channel_0_lut;
  };

  // Offset = 0x00e0
  union {
    __IO uint32_t timer_3_threshold_channel_1_lut;
  };

  // Offset = 0x00e4
  union {
    __IO uint32_t timer_3_threshold_channel_2_lut;
  };

  // Offset = 0x00e8
  union {
    __IO uint32_t timer_3_threshold_channel_3_lut;
  };

  // Offset = 0x00ec
  union {
    __IO uint32_t timer_3_counter_status_register;
    struct {
      __IO uint32_t  counter_value : 16;
      __IO uint32_t  reserved1  : 16;
    } timer_3_counter_status_register_b;
  };
  __I uint32_t    unused3[4];

  // Offset = 0x0100
  union {
    __IO uint32_t adv_timer_event_cfg_register;
    struct {
      __IO uint32_t  event0_sel :  4;
      __IO uint32_t  event1_sel :  4;
      __IO uint32_t  event2_sel :  4;
      __IO uint32_t  event3_sel :  4;
      __IO uint32_t  event_enable :  4;
      __IO uint32_t  reserved1  : 12;
    } adv_timer_event_cfg_register_b;
  };

  // Offset = 0x0104
  union {
    __IO uint32_t adv_timer_cfg_register;
    struct {
      __IO uint32_t  adv_timer_enable :  4;
      __IO uint32_t  reserved1  : 28;
    } adv_timer_cfg_register_b;
  };
} AdvTimerUnit_t;


#define REG_TIMER_0_CMD_REGISTER       0x000
#define   REG_TIMER_0_CMD_REGISTER_RESERVED1_LSB   5
#define   REG_TIMER_0_CMD_REGISTER_RESERVED1_MASK  0x7ffffff
#define   REG_TIMER_0_CMD_REGISTER_ARM_COMMAND_LSB 4
#define   REG_TIMER_0_CMD_REGISTER_ARM_COMMAND_MASK 0x1
#define   REG_TIMER_0_CMD_REGISTER_RESET_COMMAND_LSB 3
#define   REG_TIMER_0_CMD_REGISTER_RESET_COMMAND_MASK 0x1
#define   REG_TIMER_0_CMD_REGISTER_UPDATE_COMMAND_LSB 2
#define   REG_TIMER_0_CMD_REGISTER_UPDATE_COMMAND_MASK 0x1
#define   REG_TIMER_0_CMD_REGISTER_STOP_COMMAND_LSB 1
#define   REG_TIMER_0_CMD_REGISTER_STOP_COMMAND_MASK 0x1
#define   REG_TIMER_0_CMD_REGISTER_START_COMMAND_LSB 0
#define   REG_TIMER_0_CMD_REGISTER_START_COMMAND_MASK 0x1
#define REG_TIMER_0_CONFIG_REGISTER    0x004
#define   REG_TIMER_0_CONFIG_REGISTER_RESERVED1_LSB 24
#define   REG_TIMER_0_CONFIG_REGISTER_RESERVED1_MASK 0xff
#define   REG_TIMER_0_CONFIG_REGISTER_PRESCALER_VALUE_LSB 16
#define   REG_TIMER_0_CONFIG_REGISTER_PRESCALER_VALUE_MASK 0xff
#define   REG_TIMER_0_CONFIG_REGISTER_RESERVED2_LSB 13
#define   REG_TIMER_0_CONFIG_REGISTER_RESERVED2_MASK 0x7
#define   REG_TIMER_0_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_LSB 12
#define   REG_TIMER_0_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_MASK 0x1
#define   REG_TIMER_0_CONFIG_REGISTER_CLOCK_SEL_LSB 11
#define   REG_TIMER_0_CONFIG_REGISTER_CLOCK_SEL_MASK 0x1
#define   REG_TIMER_0_CONFIG_REGISTER_TRIGGER_MODE_SEL_LSB 8
#define   REG_TIMER_0_CONFIG_REGISTER_TRIGGER_MODE_SEL_MASK 0x7
#define   REG_TIMER_0_CONFIG_REGISTER_INPUT_SOURCE_SEL_LSB 0
#define   REG_TIMER_0_CONFIG_REGISTER_INPUT_SOURCE_SEL_MASK 0xff
#define REG_TIMER_0_THRESHOLD_REGISTER 0x008
#define   REG_TIMER_0_THRESHOLD_REGISTER_THRESHOLD_HIGH_LSB 16
#define   REG_TIMER_0_THRESHOLD_REGISTER_THRESHOLD_HIGH_MASK 0xffff
#define   REG_TIMER_0_THRESHOLD_REGISTER_THRESHOLD_LOW_LSB 0
#define   REG_TIMER_0_THRESHOLD_REGISTER_THRESHOLD_LOW_MASK 0xffff
#define REG_TIMER_0_THRESHOLD_CHANNEL_0_REG 0x00C
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_RESERVED1_LSB 19
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_0_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_0_THRESHOLD_CHANNEL_1_REG 0x010
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_RESERVED1_LSB 19
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_0_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_0_THRESHOLD_CHANNEL_2_REG 0x014
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_RESERVED1_LSB 19
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_0_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_0_THRESHOLD_CHANNEL_3_REG 0x018
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_RESERVED1_LSB 19
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_0_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_0_THRESHOLD_CHANNEL_0_LUT 0x01C
#define REG_TIMER_0_THRESHOLD_CHANNEL_1_LUT 0x020
#define REG_TIMER_0_THRESHOLD_CHANNEL_2_LUT 0x024
#define REG_TIMER_0_THRESHOLD_CHANNEL_3_LUT 0x028
#define REG_TIMER_0_COUNTER_STATUS_REGISTER 0x02C
#define   REG_TIMER_0_COUNTER_STATUS_REGISTER_RESERVED1_LSB 16
#define   REG_TIMER_0_COUNTER_STATUS_REGISTER_RESERVED1_MASK 0xffff
#define   REG_TIMER_0_COUNTER_STATUS_REGISTER_COUNTER_VALUE_LSB 0
#define   REG_TIMER_0_COUNTER_STATUS_REGISTER_COUNTER_VALUE_MASK 0xffff
#define REG_TIMER_1_CMD_REGISTER       0x040
#define   REG_TIMER_1_CMD_REGISTER_RESERVED1 _LSB  5
#define   REG_TIMER_1_CMD_REGISTER_RESERVED1 _MASK 0x7ffffff
#define   REG_TIMER_1_CMD_REGISTER_ARM_COMMAND_LSB 4
#define   REG_TIMER_1_CMD_REGISTER_ARM_COMMAND_MASK 0x1
#define   REG_TIMER_1_CMD_REGISTER_RESET_COMMAND_LSB 3
#define   REG_TIMER_1_CMD_REGISTER_RESET_COMMAND_MASK 0x1
#define   REG_TIMER_1_CMD_REGISTER_UPDATE_COMMAND_LSB 2
#define   REG_TIMER_1_CMD_REGISTER_UPDATE_COMMAND_MASK 0x1
#define   REG_TIMER_1_CMD_REGISTER_STOP_COMMAND_LSB 1
#define   REG_TIMER_1_CMD_REGISTER_STOP_COMMAND_MASK 0x1
#define   REG_TIMER_1_CMD_REGISTER_START_COMMAND_LSB 0
#define   REG_TIMER_1_CMD_REGISTER_START_COMMAND_MASK 0x1
#define REG_TIMER_1_CONFIG_REGISTER    0x044
#define   REG_TIMER_1_CONFIG_REGISTER_RESERVED1_LSB 24
#define   REG_TIMER_1_CONFIG_REGISTER_RESERVED1_MASK 0xff
#define   REG_TIMER_1_CONFIG_REGISTER_PRESCALER_VALUE_LSB 16
#define   REG_TIMER_1_CONFIG_REGISTER_PRESCALER_VALUE_MASK 0xff
#define   REG_TIMER_1_CONFIG_REGISTER_RESERVED2_LSB 13
#define   REG_TIMER_1_CONFIG_REGISTER_RESERVED2_MASK 0x7
#define   REG_TIMER_1_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_LSB 12
#define   REG_TIMER_1_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_MASK 0x1
#define   REG_TIMER_1_CONFIG_REGISTER_CLOCK_SEL_LSB 11
#define   REG_TIMER_1_CONFIG_REGISTER_CLOCK_SEL_MASK 0x1
#define   REG_TIMER_1_CONFIG_REGISTER_TRIGGER_MODE_SEL_LSB 8
#define   REG_TIMER_1_CONFIG_REGISTER_TRIGGER_MODE_SEL_MASK 0x7
#define   REG_TIMER_1_CONFIG_REGISTER_INPUT_SOURCE_SEL_LSB 0
#define   REG_TIMER_1_CONFIG_REGISTER_INPUT_SOURCE_SEL_MASK 0xff
#define REG_TIMER_1_THRESHOLD_REGISTER 0x048
#define   REG_TIMER_1_THRESHOLD_REGISTER_THRESHOLD_HIGH_LSB 16
#define   REG_TIMER_1_THRESHOLD_REGISTER_THRESHOLD_HIGH_MASK 0xffff
#define   REG_TIMER_1_THRESHOLD_REGISTER_THRESHOLD_LOW_LSB 0
#define   REG_TIMER_1_THRESHOLD_REGISTER_THRESHOLD_LOW_MASK 0xffff
#define REG_TIMER_1_THRESHOLD_CHANNEL_0_REG 0x04C
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_RESERVED1_LSB 19
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_1_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_1_THRESHOLD_CHANNEL_1_REG 0x050
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_RESERVED1_LSB 19
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_1_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_1_THRESHOLD_CHANNEL_2_REG 0x054
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_RESERVED1_LSB 19
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_1_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_1_THRESHOLD_CHANNEL_3_REG 0x058
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_RESERVED1_LSB 19
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_1_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_1_THRESHOLD_CHANNEL_0_LUT 0x05C
#define REG_TIMER_1_THRESHOLD_CHANNEL_1_LUT 0x060
#define REG_TIMER_1_THRESHOLD_CHANNEL_2_LUT 0x064
#define REG_TIMER_1_THRESHOLD_CHANNEL_3_LUT 0x068
#define REG_TIMER_1_COUNTER_STATUS_REGISTER 0x06C
#define   REG_TIMER_1_COUNTER_STATUS_REGISTER_RESERVED1_LSB 16
#define   REG_TIMER_1_COUNTER_STATUS_REGISTER_RESERVED1_MASK 0xffff
#define   REG_TIMER_1_COUNTER_STATUS_REGISTER_COUNTER_VALUE_LSB 0
#define   REG_TIMER_1_COUNTER_STATUS_REGISTER_COUNTER_VALUE_MASK 0xffff
#define REG_TIMER_2_CMD_REGISTER       0x080
#define   REG_TIMER_2_CMD_REGISTER_RESERVED1_LSB   5
#define   REG_TIMER_2_CMD_REGISTER_RESERVED1_MASK  0x7ffffff
#define   REG_TIMER_2_CMD_REGISTER_ARM_COMMAND_LSB 4
#define   REG_TIMER_2_CMD_REGISTER_ARM_COMMAND_MASK 0x1
#define   REG_TIMER_2_CMD_REGISTER_RESET_COMMAND_LSB 3
#define   REG_TIMER_2_CMD_REGISTER_RESET_COMMAND_MASK 0x1
#define   REG_TIMER_2_CMD_REGISTER_UPDATE_COMMAND_LSB 2
#define   REG_TIMER_2_CMD_REGISTER_UPDATE_COMMAND_MASK 0x1
#define   REG_TIMER_2_CMD_REGISTER_STOP_COMMAND_LSB 1
#define   REG_TIMER_2_CMD_REGISTER_STOP_COMMAND_MASK 0x1
#define   REG_TIMER_2_CMD_REGISTER_START_COMMAND_LSB 0
#define   REG_TIMER_2_CMD_REGISTER_START_COMMAND_MASK 0x1
#define REG_TIMER_2_CONFIG_REGISTER    0x084
#define   REG_TIMER_2_CONFIG_REGISTER_RESERVED1_LSB 24
#define   REG_TIMER_2_CONFIG_REGISTER_RESERVED1_MASK 0xff
#define   REG_TIMER_2_CONFIG_REGISTER_PRESCALER_VALUE_LSB 16
#define   REG_TIMER_2_CONFIG_REGISTER_PRESCALER_VALUE_MASK 0xff
#define   REG_TIMER_2_CONFIG_REGISTER_RESERVED2_LSB 13
#define   REG_TIMER_2_CONFIG_REGISTER_RESERVED2_MASK 0x7
#define   REG_TIMER_2_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_LSB 12
#define   REG_TIMER_2_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_MASK 0x1
#define   REG_TIMER_2_CONFIG_REGISTER_CLOCK_SEL_LSB 11
#define   REG_TIMER_2_CONFIG_REGISTER_CLOCK_SEL_MASK 0x1
#define   REG_TIMER_2_CONFIG_REGISTER_TRIGGER_MODE_SEL_LSB 8
#define   REG_TIMER_2_CONFIG_REGISTER_TRIGGER_MODE_SEL_MASK 0x7
#define   REG_TIMER_2_CONFIG_REGISTER_INPUT_SOURCE_SEL_LSB 0
#define   REG_TIMER_2_CONFIG_REGISTER_INPUT_SOURCE_SEL_MASK 0xff
#define REG_TIMER_2_THRESHOLD_REGISTER 0x088
#define   REG_TIMER_2_THRESHOLD_REGISTER_THRESHOLD_HIGH_LSB 16
#define   REG_TIMER_2_THRESHOLD_REGISTER_THRESHOLD_HIGH_MASK 0xffff
#define   REG_TIMER_2_THRESHOLD_REGISTER_THRESHOLD_LOW_LSB 0
#define   REG_TIMER_2_THRESHOLD_REGISTER_THRESHOLD_LOW_MASK 0xffff
#define REG_TIMER_2_THRESHOLD_CHANNEL_0_REG 0x08C
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_RESERVED1_LSB 19
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_2_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_2_THRESHOLD_CHANNEL_1_REG 0x090
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_RESERVED1_LSB 19
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_2_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_2_THRESHOLD_CHANNEL_2_REG 0x094
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_RESERVED1_LSB 19
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_2_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_2_THRESHOLD_CHANNEL_3_REG 0x098
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_RESERVED1_LSB 19
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_2_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_2_THRESHOLD_CHANNEL_0_LUT 0x09C
#define REG_TIMER_2_THRESHOLD_CHANNEL_1_LUT 0x0A0
#define REG_TIMER_2_THRESHOLD_CHANNEL_2_LUT 0x0A4
#define REG_TIMER_2_THRESHOLD_CHANNEL_3_LUT 0x0A8
#define REG_TIMER_2_COUNTER_STATUS_REGISTER 0x0AC
#define   REG_TIMER_2_COUNTER_STATUS_REGISTER_RESERVED1_LSB 16
#define   REG_TIMER_2_COUNTER_STATUS_REGISTER_RESERVED1_MASK 0xffff
#define   REG_TIMER_2_COUNTER_STATUS_REGISTER_COUNTER_VALUE_LSB 0
#define   REG_TIMER_2_COUNTER_STATUS_REGISTER_COUNTER_VALUE_MASK 0xffff
#define REG_TIMER_3_CMD_REGISTER       0x0C0
#define   REG_TIMER_3_CMD_REGISTER_RESERVED1_LSB   5
#define   REG_TIMER_3_CMD_REGISTER_RESERVED1_MASK  0x7ffffff
#define   REG_TIMER_3_CMD_REGISTER_ARM_COMMAND_LSB 4
#define   REG_TIMER_3_CMD_REGISTER_ARM_COMMAND_MASK 0x1
#define   REG_TIMER_3_CMD_REGISTER_RESET_COMMAND_LSB 3
#define   REG_TIMER_3_CMD_REGISTER_RESET_COMMAND_MASK 0x1
#define   REG_TIMER_3_CMD_REGISTER_UPDATE_COMMAND_LSB 2
#define   REG_TIMER_3_CMD_REGISTER_UPDATE_COMMAND_MASK 0x1
#define   REG_TIMER_3_CMD_REGISTER_STOP_COMMAND_LSB 1
#define   REG_TIMER_3_CMD_REGISTER_STOP_COMMAND_MASK 0x1
#define   REG_TIMER_3_CMD_REGISTER_START_COMMAND_LSB 0
#define   REG_TIMER_3_CMD_REGISTER_START_COMMAND_MASK 0x1
#define REG_TIMER_3_CONFIG_REGISTER    0x0C4
#define   REG_TIMER_3_CONFIG_REGISTER_RESERVED1_LSB 24
#define   REG_TIMER_3_CONFIG_REGISTER_RESERVED1_MASK 0xff
#define   REG_TIMER_3_CONFIG_REGISTER_PRESCALER_VALUE_LSB 16
#define   REG_TIMER_3_CONFIG_REGISTER_PRESCALER_VALUE_MASK 0xff
#define   REG_TIMER_3_CONFIG_REGISTER_RESERVED2_LSB 13
#define   REG_TIMER_3_CONFIG_REGISTER_RESERVED2_MASK 0x7
#define   REG_TIMER_3_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_LSB 12
#define   REG_TIMER_3_CONFIG_REGISTER_UP_DOWN_COUNTER_SEL_MASK 0x1
#define   REG_TIMER_3_CONFIG_REGISTER_CLOCK_SEL_LSB 11
#define   REG_TIMER_3_CONFIG_REGISTER_CLOCK_SEL_MASK 0x1
#define   REG_TIMER_3_CONFIG_REGISTER_TRIGGER_MODE_SEL_LSB 8
#define   REG_TIMER_3_CONFIG_REGISTER_TRIGGER_MODE_SEL_MASK 0x7
#define   REG_TIMER_3_CONFIG_REGISTER_INPUT_SOURCE_SEL_LSB 0
#define   REG_TIMER_3_CONFIG_REGISTER_INPUT_SOURCE_SEL_MASK 0xff
#define REG_TIMER_3_THRESHOLD_REGISTER 0x0C8
#define   REG_TIMER_3_THRESHOLD_REGISTER_THRESHOLD_HIGH_LSB 16
#define   REG_TIMER_3_THRESHOLD_REGISTER_THRESHOLD_HIGH_MASK 0xffff
#define   REG_TIMER_3_THRESHOLD_REGISTER_THRESHOLD_LOW_LSB 0
#define   REG_TIMER_3_THRESHOLD_REGISTER_THRESHOLD_LOW_MASK 0xffff
#define REG_TIMER_3_THRESHOLD_CHANNEL_0_REG 0x0CC
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_RESERVED1_LSB 19
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_3_THRESHOLD_CHANNEL_0_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_3_THRESHOLD_CHANNEL_1_REG 0x0D0
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_RESERVED1_LSB 19
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_3_THRESHOLD_CHANNEL_1_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_3_THRESHOLD_CHANNEL_2_REG 0x0D4
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_RESERVED1_LSB 19
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_3_THRESHOLD_CHANNEL_2_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_3_THRESHOLD_CHANNEL_3_REG 0x0D8
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_RESERVED1_LSB 19
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_RESERVED1_MASK 0x1fff
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_LSB 16
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_THRESHOLD_MODE_MASK 0x7
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_LSB 0
#define   REG_TIMER_3_THRESHOLD_CHANNEL_3_REG_THRESHOLD_VALUE_MASK 0xffff
#define REG_TIMER_3_THRESHOLD_CHANNEL_0_LUT 0x0DC
#define REG_TIMER_3_THRESHOLD_CHANNEL_1_LUT 0x0E0
#define REG_TIMER_3_THRESHOLD_CHANNEL_2_LUT 0x0E4
#define REG_TIMER_3_THRESHOLD_CHANNEL_3_LUT 0x0E8
#define REG_TIMER_3_COUNTER_STATUS_REGISTER 0x0EC
#define   REG_TIMER_3_COUNTER_STATUS_REGISTER_RESERVED1_LSB 16
#define   REG_TIMER_3_COUNTER_STATUS_REGISTER_RESERVED1_MASK 0xffff
#define   REG_TIMER_3_COUNTER_STATUS_REGISTER_COUNTER_VALUE_LSB 0
#define   REG_TIMER_3_COUNTER_STATUS_REGISTER_COUNTER_VALUE_MASK 0xffff
#define REG_ADV_TIMER_EVENT_CFG_REGISTER 0x100
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_RESERVED1_LSB 20
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_RESERVED1_MASK 0xfff
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT_ENABLE_LSB 16
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT_ENABLE_MASK 0xf
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT3_SEL_LSB 12
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT3_SEL_MASK 0xf
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT2_SEL_LSB 8
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT2_SEL_MASK 0xf
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT1_SEL_LSB 4
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT1_SEL_MASK 0xf
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT0_SEL_LSB 0
#define   REG_ADV_TIMER_EVENT_CFG_REGISTER_EVENT0_SEL_MASK 0xf
#define REG_ADV_TIMER_CFG_REGISTER     0x104
#define   REG_ADV_TIMER_CFG_REGISTER_RESERVED1_LSB 4
#define   REG_ADV_TIMER_CFG_REGISTER_RESERVED1_MASK 0xfffffff
#define   REG_ADV_TIMER_CFG_REGISTER_ADV_TIMER_ENABLE_LSB 0
#define   REG_ADV_TIMER_CFG_REGISTER_ADV_TIMER_ENABLE_MASK 0xf

#ifndef __REGFIELD_OPS_
#define __REGFIELD_OPS_
static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}
#endif  // __REGFIELD_OPS_

#endif // __ADV_TIMER_UNIT_H_
