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

#ifndef __APB_I2CS_H_
#define __APB_I2CS_H_

//---------------------------------//
//
// Module: APB_I2CS
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
    __IO uint32_t i2cs_dev_address;
    struct {
      __IO uint32_t  slave_addr :  7;
      __IO uint32_t  reserved   :  1;
    } i2cs_dev_address_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t i2cs_enable;
    struct {
      __IO uint32_t  ip_enable  :  1;
      __IO uint32_t  reserved   :  7;
    } i2cs_enable_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t i2cs_debounce_length;
    struct {
      __IO uint32_t  deb_len    :  8;
    } i2cs_debounce_length_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t i2cs_scl_delay_length;
    struct {
      __IO uint32_t  scl_dly_len :  8;
    } i2cs_scl_delay_length_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t i2cs_sda_delay_length;
    struct {
      __IO uint32_t  sda_dly_len :  8;
    } i2cs_sda_delay_length_b;
  };
  __I uint32_t    unused0[11];

  // Offset = 0x0040
  union {
    __IO uint32_t i2cs_msg_i2c_apb;
    struct {
      __IO uint32_t  i2c_to_apb :  8;
    } i2cs_msg_i2c_apb_b;
  };

  // Offset = 0x0044
  union {
    __IO uint32_t i2cs_msg_i2c_apb_status;
    struct {
      __IO uint32_t  i2c_to_apb_status :  1;
      __IO uint32_t  reserved   :  7;
    } i2cs_msg_i2c_apb_status_b;
  };

  // Offset = 0x0048
  union {
    __IO uint32_t i2cs_msg_apb_i2c;
    struct {
      __IO uint32_t  apb_to_i2c :  8;
    } i2cs_msg_apb_i2c_b;
  };

  // Offset = 0x004c
  union {
    __IO uint32_t i2cs_msg_apb_i2c_status;
    struct {
      __IO uint32_t  apb_to_i2c_status :  1;
      __IO uint32_t  reserved   :  7;
    } i2cs_msg_apb_i2c_status_b;
  };
  __I uint32_t    unused1[12];

  // Offset = 0x0080
  union {
    __IO uint32_t i2cs_fifo_i2c_apb_write_data_port;
    struct {
      __IO uint32_t  i2c_apb_write_data_port : 32;
    } i2cs_fifo_i2c_apb_write_data_port_b;
  };

  // Offset = 0x0084
  union {
    __IO uint32_t i2cs_fifo_i2c_apb_read_data_port;
    struct {
      __IO uint32_t  i2c_apb_read_data_port : 32;
    } i2cs_fifo_i2c_apb_read_data_port_b;
  };

  // Offset = 0x0088
  union {
    __IO uint32_t i2cs_fifo_i2c_apb_flush;
    struct {
      __IO uint32_t  enable     :  1;
      __IO uint32_t  reserved   :  7;
    } i2cs_fifo_i2c_apb_flush_b;
  };

  // Offset = 0x008c
  union {
    __IO uint32_t i2cs_fifo_i2c_apb_write_flags;
    struct {
      __IO uint32_t  flags      :  3;
      __IO uint32_t  reserved   :  5;
    } i2cs_fifo_i2c_apb_write_flags_b;
  };

  // Offset = 0x0090
  union {
    __IO uint32_t i2cs_fifo_i2c_apb_read_flags;
    struct {
      __IO uint32_t  flags      :  3;
      __IO uint32_t  reserved   :  5;
    } i2cs_fifo_i2c_apb_read_flags_b;
  };
  __I uint32_t    unused2[11];

  // Offset = 0x00c0
  union {
    __IO uint32_t i2cs_fifo_apb_i2c_write_data_port;
    struct {
      __IO uint32_t  i2c_apb_write_data_port : 32;
    } i2cs_fifo_apb_i2c_write_data_port_b;
  };

  // Offset = 0x00c4
  union {
    __IO uint32_t i2cs_fifo_apb_i2c_read_data_port;
    struct {
      __IO uint32_t  i2c_apb_read_data_port : 32;
    } i2cs_fifo_apb_i2c_read_data_port_b;
  };

  // Offset = 0x00c8
  union {
    __IO uint32_t i2cs_fifo_apb_i2c_flush;
    struct {
      __IO uint32_t  enable     :  1;
      __IO uint32_t  reserved   :  7;
    } i2cs_fifo_apb_i2c_flush_b;
  };

  // Offset = 0x00cc
  union {
    __IO uint32_t i2cs_fifo_apb_i2c_write_flags;
    struct {
      __IO uint32_t  flags      :  3;
      __IO uint32_t  reserved   :  5;
    } i2cs_fifo_apb_i2c_write_flags_b;
  };

  // Offset = 0x00d0
  union {
    __IO uint32_t i2cs_fifo_apb_i2c_read_flags;
    struct {
      __IO uint32_t  flags      :  3;
      __IO uint32_t  reserved   :  5;
    } i2cs_fifo_apb_i2c_read_flags_b;
  };
  __I uint32_t    unused3[11];

  // Offset = 0x0100
  union {
    __IO uint32_t i2cs_interrupt_status;
    struct {
      __IO uint32_t  apb_i2c_message_available :  1;
      __IO uint32_t  apb_i2c_fifo_read_status :  1;
      __IO uint32_t  i2c_apb_fifo_write_status :  1;
      __IO uint32_t  reserved   :  5;
    } i2cs_interrupt_status_b;
  };

  // Offset = 0x0104
  union {
    __IO uint32_t i2cs_interrupt_enable;
    struct {
      __IO uint32_t  apb_i2c_message_available_int_enable :  1;
      __IO uint32_t  apb_i2c_fifo_read_status_int_enable :  1;
      __IO uint32_t  i2c_apb_fifo_write_status_int_enable :  1;
      __IO uint32_t  reserved   :  5;
    } i2cs_interrupt_enable_b;
  };

  // Offset = 0x0108
  union {
    __IO uint32_t i2cs_interrupt_i2c_apb_write_flags_select;
    struct {
      __IO uint32_t  write_flag_128_space_avail :  1;
      __IO uint32_t  write_flag_64_127_space_avail :  1;
      __IO uint32_t  write_flag_32_63_space_avail :  1;
      __IO uint32_t  write_flag_8_31_space_avail :  1;
      __IO uint32_t  write_flag_4_7_space_avail :  1;
      __IO uint32_t  write_flag_2_3_space_avail :  1;
      __IO uint32_t  write_flag_1_space_avail :  1;
      __IO uint32_t  write_flag_full :  1;
    } i2cs_interrupt_i2c_apb_write_flags_select_b;
  };

  // Offset = 0x010c
  union {
    __IO uint32_t i2cs_interrupt_apb_i2c_read_flags_select;
    struct {
      __IO uint32_t  read_flag_empty :  1;
      __IO uint32_t  read_flag_1_space_avail :  1;
      __IO uint32_t  read_flag_2_3_space_avail :  1;
      __IO uint32_t  read_flag_4_7_space_avail :  1;
      __IO uint32_t  read_flag_8_31_space_avail :  1;
      __IO uint32_t  read_flag_32_63_space_avail :  1;
      __IO uint32_t  read_flag_64_127_space_avail :  1;
      __IO uint32_t  read_flag_128_space_avail :  1;
    } i2cs_interrupt_apb_i2c_read_flags_select_b;
  };
  __I uint32_t    unused4[12];

  // Offset = 0x0140
  union {
    __IO uint32_t i2cs_interrupt_to_apb_status;
    struct {
      __IO uint32_t  new_i2c_apb_msg_avail :  1;
      __IO uint32_t  i2c_apb_fifo_read_status :  1;
      __IO uint32_t  apb_i2c_fifo_write_status :  1;
      __IO uint32_t  reserved   :  5;
    } i2cs_interrupt_to_apb_status_b;
  };

  // Offset = 0x0144
  union {
    __IO uint32_t i2cs_interrupt_to_apb_enable;
    struct {
      __IO uint32_t  new_i2c_apb_msg_avail_enable :  1;
      __IO uint32_t  i2c_apb_fifo_read_status_enable :  1;
      __IO uint32_t  apb_i2c_fifo_write_status_enable :  1;
      __IO uint32_t  reserved   :  5;
    } i2cs_interrupt_to_apb_enable_b;
  };

  // Offset = 0x0148
  union {
    __IO uint32_t i2cs_interrupt_apb_i2c_write_flags_select;
    struct {
      __IO uint32_t  write_flag_128_space_avail :  1;
      __IO uint32_t  write_flag_64_127_space_avail :  1;
      __IO uint32_t  write_flag_32_63_space_avail :  1;
      __IO uint32_t  write_flag_8_31_space_avail :  1;
      __IO uint32_t  write_flag_4_7_space_avail :  1;
      __IO uint32_t  write_flag_2_3_space_avail :  1;
      __IO uint32_t  write_flag_1_space_avail :  1;
      __IO uint32_t  write_flag_full :  1;
    } i2cs_interrupt_apb_i2c_write_flags_select_b;
  };

  // Offset = 0x014c
  union {
    __IO uint32_t i2cs_interrupt_i2c_apb_read_flags_select;
    struct {
      __IO uint32_t  read_flag_empty :  1;
      __IO uint32_t  read_flag_1_space_avail :  1;
      __IO uint32_t  read_flag_2_3_space_avail :  1;
      __IO uint32_t  read_flag_4_7_space_avail :  1;
      __IO uint32_t  read_flag_8_31_space_avail :  1;
      __IO uint32_t  read_flag_32_63_space_avail :  1;
      __IO uint32_t  read_flag_64_127_space_avail :  1;
      __IO uint32_t  read_flag_128_space_avail :  1;
    } i2cs_interrupt_i2c_apb_read_flags_select_b;
  };
} ApbI2cs_t;


#define REG_I2CS_DEV_ADDRESS           0x000
#define   REG_I2CS_DEV_ADDRESS_RESERVED_LSB        7
#define   REG_I2CS_DEV_ADDRESS_RESERVED_MASK       0x1
#define   REG_I2CS_DEV_ADDRESS_SLAVE_ADDR_LSB      0
#define   REG_I2CS_DEV_ADDRESS_SLAVE_ADDR_MASK     0x7f
#define REG_I2CS_ENABLE                0x004
#define   REG_I2CS_ENABLE_RESERVED_LSB             1
#define   REG_I2CS_ENABLE_RESERVED_MASK            0x7f
#define   REG_I2CS_ENABLE_IP_ENABLE_LSB            0
#define   REG_I2CS_ENABLE_IP_ENABLE_MASK           0x1
#define REG_I2CS_DEBOUNCE_LENGTH       0x008
#define   REG_I2CS_DEBOUNCE_LENGTH_DEB_LEN_LSB     0
#define   REG_I2CS_DEBOUNCE_LENGTH_DEB_LEN_MASK    0xff
#define REG_I2CS_SCL_DELAY_LENGTH      0x00C
#define   REG_I2CS_SCL_DELAY_LENGTH_SCL_DLY_LEN_LSB 0
#define   REG_I2CS_SCL_DELAY_LENGTH_SCL_DLY_LEN_MASK 0xff
#define REG_I2CS_SDA_DELAY_LENGTH      0x010
#define   REG_I2CS_SDA_DELAY_LENGTH_SDA_DLY_LEN_LSB 0
#define   REG_I2CS_SDA_DELAY_LENGTH_SDA_DLY_LEN_MASK 0xff
#define REG_I2CS_MSG_I2C_APB           0x040
#define   REG_I2CS_MSG_I2C_APB_I2C_TO_APB_LSB      0
#define   REG_I2CS_MSG_I2C_APB_I2C_TO_APB_MASK     0xff
#define REG_I2CS_MSG_I2C_APB_STATUS    0x044
#define   REG_I2CS_MSG_I2C_APB_STATUS_RESERVED_LSB 1
#define   REG_I2CS_MSG_I2C_APB_STATUS_RESERVED_MASK 0x7f
#define   REG_I2CS_MSG_I2C_APB_STATUS_I2C_TO_APB_STATUS_LSB 0
#define   REG_I2CS_MSG_I2C_APB_STATUS_I2C_TO_APB_STATUS_MASK 0x1
#define REG_I2CS_MSG_APB_I2C           0x048
#define   REG_I2CS_MSG_APB_I2C_APB_TO_I2C_LSB      0
#define   REG_I2CS_MSG_APB_I2C_APB_TO_I2C_MASK     0xff
#define REG_I2CS_MSG_APB_I2C_STATUS    0x04C
#define   REG_I2CS_MSG_APB_I2C_STATUS_RESERVED_LSB 1
#define   REG_I2CS_MSG_APB_I2C_STATUS_RESERVED_MASK 0x7f
#define   REG_I2CS_MSG_APB_I2C_STATUS_APB_TO_I2C_STATUS_LSB 0
#define   REG_I2CS_MSG_APB_I2C_STATUS_APB_TO_I2C_STATUS_MASK 0x1
#define REG_I2CS_FIFO_I2C_APB_WRITE_DATA_PORT 0x080
#define   REG_I2CS_FIFO_I2C_APB_WRITE_DATA_PORT_I2C_APB_WRITE_DATA_PORT_LSB 0
#define   REG_I2CS_FIFO_I2C_APB_WRITE_DATA_PORT_I2C_APB_WRITE_DATA_PORT_MASK 0xffffffff
#define REG_I2CS_FIFO_I2C_APB_READ_DATA_PORT 0x084
#define   REG_I2CS_FIFO_I2C_APB_READ_DATA_PORT_I2C_APB_READ_DATA_PORT_LSB 0
#define   REG_I2CS_FIFO_I2C_APB_READ_DATA_PORT_I2C_APB_READ_DATA_PORT_MASK 0xffffffff
#define REG_I2CS_FIFO_I2C_APB_FLUSH    0x088
#define   REG_I2CS_FIFO_I2C_APB_FLUSH_RESERVED_LSB 1
#define   REG_I2CS_FIFO_I2C_APB_FLUSH_RESERVED_MASK 0x7f
#define   REG_I2CS_FIFO_I2C_APB_FLUSH_ENABLE_LSB   0
#define   REG_I2CS_FIFO_I2C_APB_FLUSH_ENABLE_MASK  0x1
#define REG_I2CS_FIFO_I2C_APB_WRITE_FLAGS 0x08C
#define   REG_I2CS_FIFO_I2C_APB_WRITE_FLAGS_RESERVED_LSB 3
#define   REG_I2CS_FIFO_I2C_APB_WRITE_FLAGS_RESERVED_MASK 0x1f
#define   REG_I2CS_FIFO_I2C_APB_WRITE_FLAGS_FLAGS_LSB 0
#define   REG_I2CS_FIFO_I2C_APB_WRITE_FLAGS_FLAGS_MASK 0x7
#define REG_I2CS_FIFO_I2C_APB_READ_FLAGS 0x090
#define   REG_I2CS_FIFO_I2C_APB_READ_FLAGS_RESERVED_LSB 3
#define   REG_I2CS_FIFO_I2C_APB_READ_FLAGS_RESERVED_MASK 0x1f
#define   REG_I2CS_FIFO_I2C_APB_READ_FLAGS_FLAGS_LSB 0
#define   REG_I2CS_FIFO_I2C_APB_READ_FLAGS_FLAGS_MASK 0x7
#define REG_I2CS_FIFO_APB_I2C_WRITE_DATA_PORT 0x0C0
#define   REG_I2CS_FIFO_APB_I2C_WRITE_DATA_PORT_I2C_APB_WRITE_DATA_PORT_LSB 0
#define   REG_I2CS_FIFO_APB_I2C_WRITE_DATA_PORT_I2C_APB_WRITE_DATA_PORT_MASK 0xffffffff
#define REG_I2CS_FIFO_APB_I2C_READ_DATA_PORT 0x0C4
#define   REG_I2CS_FIFO_APB_I2C_READ_DATA_PORT_I2C_APB_READ_DATA_PORT_LSB 0
#define   REG_I2CS_FIFO_APB_I2C_READ_DATA_PORT_I2C_APB_READ_DATA_PORT_MASK 0xffffffff
#define REG_I2CS_FIFO_APB_I2C_FLUSH    0x0C8
#define   REG_I2CS_FIFO_APB_I2C_FLUSH_RESERVED_LSB 1
#define   REG_I2CS_FIFO_APB_I2C_FLUSH_RESERVED_MASK 0x7f
#define   REG_I2CS_FIFO_APB_I2C_FLUSH_ENABLE_LSB   0
#define   REG_I2CS_FIFO_APB_I2C_FLUSH_ENABLE_MASK  0x1
#define REG_I2CS_FIFO_APB_I2C_WRITE_FLAGS 0x0CC
#define   REG_I2CS_FIFO_APB_I2C_WRITE_FLAGS_RESERVED_LSB 3
#define   REG_I2CS_FIFO_APB_I2C_WRITE_FLAGS_RESERVED_MASK 0x1f
#define   REG_I2CS_FIFO_APB_I2C_WRITE_FLAGS_FLAGS_LSB 0
#define   REG_I2CS_FIFO_APB_I2C_WRITE_FLAGS_FLAGS_MASK 0x7
#define REG_I2CS_FIFO_APB_I2C_READ_FLAGS 0x0D0
#define   REG_I2CS_FIFO_APB_I2C_READ_FLAGS_RESERVED_LSB 3
#define   REG_I2CS_FIFO_APB_I2C_READ_FLAGS_RESERVED_MASK 0x1f
#define   REG_I2CS_FIFO_APB_I2C_READ_FLAGS_FLAGS_LSB 0
#define   REG_I2CS_FIFO_APB_I2C_READ_FLAGS_FLAGS_MASK 0x7
#define REG_I2CS_INTERRUPT_STATUS      0x100
#define   REG_I2CS_INTERRUPT_STATUS_RESERVED_LSB   3
#define   REG_I2CS_INTERRUPT_STATUS_RESERVED_MASK  0x1f
#define   REG_I2CS_INTERRUPT_STATUS_I2C_APB_FIFO_WRITE_STATUS_LSB 2
#define   REG_I2CS_INTERRUPT_STATUS_I2C_APB_FIFO_WRITE_STATUS_MASK 0x1
#define   REG_I2CS_INTERRUPT_STATUS_APB_I2C_FIFO_READ_STATUS_LSB 1
#define   REG_I2CS_INTERRUPT_STATUS_APB_I2C_FIFO_READ_STATUS_MASK 0x1
#define   REG_I2CS_INTERRUPT_STATUS_APB_I2C_MESSAGE_AVAILABLE_LSB 0
#define   REG_I2CS_INTERRUPT_STATUS_APB_I2C_MESSAGE_AVAILABLE_MASK 0x1
#define REG_I2CS_INTERRUPT_ENABLE      0x104
#define   REG_I2CS_INTERRUPT_ENABLE_RESERVED_LSB   3
#define   REG_I2CS_INTERRUPT_ENABLE_RESERVED_MASK  0x1f
#define   REG_I2CS_INTERRUPT_ENABLE_I2C_APB_FIFO_WRITE_STATUS_INT_ENABLE_LSB 2
#define   REG_I2CS_INTERRUPT_ENABLE_I2C_APB_FIFO_WRITE_STATUS_INT_ENABLE_MASK 0x1
#define   REG_I2CS_INTERRUPT_ENABLE_APB_I2C_FIFO_READ_STATUS_INT_ENABLE_LSB 1
#define   REG_I2CS_INTERRUPT_ENABLE_APB_I2C_FIFO_READ_STATUS_INT_ENABLE_MASK 0x1
#define   REG_I2CS_INTERRUPT_ENABLE_APB_I2C_MESSAGE_AVAILABLE_INT_ENABLE_LSB 0
#define   REG_I2CS_INTERRUPT_ENABLE_APB_I2C_MESSAGE_AVAILABLE_INT_ENABLE_MASK 0x1
#define REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT 0x108
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_FULL_LSB 7
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_FULL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_1_SPACE_AVAIL_LSB 6
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_1_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_2_3_SPACE_AVAIL_LSB 5
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_2_3_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_4_7_SPACE_AVAIL_LSB 4
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_4_7_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_8_31_SPACE_AVAIL_LSB 3
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_8_31_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_32_63_SPACE_AVAIL_LSB 2
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_32_63_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_64_127_SPACE_AVAIL_LSB 1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_64_127_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_128_SPACE_AVAIL_LSB 0
#define   REG_I2CS_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT_WRITE_FLAG_128_SPACE_AVAIL_MASK 0x1
#define REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT 0x10C
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_128_SPACE_AVAIL_LSB 7
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_128_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_64_127_SPACE_AVAIL_LSB 6
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_64_127_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_32_63_SPACE_AVAIL_LSB 5
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_32_63_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_8_31_SPACE_AVAIL_LSB 4
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_8_31_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_4_7_SPACE_AVAIL_LSB 3
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_4_7_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_2_3_SPACE_AVAIL_LSB 2
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_2_3_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_1_SPACE_AVAIL_LSB 1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_1_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_EMPTY_LSB 0
#define   REG_I2CS_INTERRUPT_APB_I2C_READ_FLAGS_SELECT_READ_FLAG_EMPTY_MASK 0x1
#define REG_I2CS_INTERRUPT_TO_APB_STATUS 0x140
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_RESERVED_LSB 3
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_RESERVED_MASK 0x1f
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_APB_I2C_FIFO_WRITE_STATUS_LSB 2
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_APB_I2C_FIFO_WRITE_STATUS_MASK 0x1
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_I2C_APB_FIFO_READ_STATUS_LSB 1
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_I2C_APB_FIFO_READ_STATUS_MASK 0x1
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_NEW_I2C_APB_MSG_AVAIL_LSB 0
#define   REG_I2CS_INTERRUPT_TO_APB_STATUS_NEW_I2C_APB_MSG_AVAIL_MASK 0x1
#define REG_I2CS_INTERRUPT_TO_APB_ENABLE 0x144
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_RESERVED_LSB 3
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_RESERVED_MASK 0x1f
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_APB_I2C_FIFO_WRITE_STATUS_ENABLE_LSB 2
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_APB_I2C_FIFO_WRITE_STATUS_ENABLE_MASK 0x1
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_I2C_APB_FIFO_READ_STATUS_ENABLE_LSB 1
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_I2C_APB_FIFO_READ_STATUS_ENABLE_MASK 0x1
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_NEW_I2C_APB_MSG_AVAIL_ENABLE_LSB 0
#define   REG_I2CS_INTERRUPT_TO_APB_ENABLE_NEW_I2C_APB_MSG_AVAIL_ENABLE_MASK 0x1
#define REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT 0x148
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_FULL_LSB 7
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_FULL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_1_SPACE_AVAIL_LSB 6
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_1_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_2_3_SPACE_AVAIL_LSB 5
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_2_3_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_4_7_SPACE_AVAIL_LSB 4
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_4_7_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_8_31_SPACE_AVAIL_LSB 3
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_8_31_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_32_63_SPACE_AVAIL_LSB 2
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_32_63_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_64_127_SPACE_AVAIL_LSB 1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_64_127_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_128_SPACE_AVAIL_LSB 0
#define   REG_I2CS_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT_WRITE_FLAG_128_SPACE_AVAIL_MASK 0x1
#define REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT 0x14C
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_128_SPACE_AVAIL_LSB 7
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_128_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_64_127_SPACE_AVAIL_LSB 6
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_64_127_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_32_63_SPACE_AVAIL_LSB 5
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_32_63_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_8_31_SPACE_AVAIL_LSB 4
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_8_31_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_4_7_SPACE_AVAIL_LSB 3
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_4_7_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_2_3_SPACE_AVAIL_LSB 2
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_2_3_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_1_SPACE_AVAIL_LSB 1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_1_SPACE_AVAIL_MASK 0x1
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_EMPTY_LSB 0
#define   REG_I2CS_INTERRUPT_I2C_APB_READ_FLAGS_SELECT_READ_FLAG_EMPTY_MASK 0x1

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

#endif // __APB_I2CS_H_
