/*
 * Copyright 2020 GreenWaves Technologies
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

#ifndef HAL_INCLUDE_HAL_I2C_INTERNAL_H_
#define HAL_INCLUDE_HAL_I2C_INTERNAL_H_

#include "core-v-mcu-pmsis.h"
#include "hal_i2c_pi.h"
#include "hal_soc_eu_periph.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Max length of a i2c request/data buffer. */
#define MAX_SIZE               (0xFF)
/* Length of i2c cmd buffer. */
#define __PI_I2C_CMD_BUFF_SIZE (16)
/* Lenght of i2c stop command sequence. */
#define __PI_I2C_STOP_CMD_SIZE (3)

struct i2c_transfer_s
{
    uint8_t *buffer;
    uint32_t size;
    pi_i2c_xfer_flags_e flags;
    int8_t device_id;
    udma_channel_e channel;
};

struct i2c_pending_transfer_s
{
    uint32_t pending_buffer;
    uint32_t pending_size;
    uint32_t pending_repeat;
    uint32_t pending_repeat_size;
    pi_i2c_xfer_flags_e flags;
    int8_t device_id;
    udma_channel_e channel;
};

struct i2c_cb_args_s
{
    struct pi_task *cb;
    struct i2c_transfer_s transfer;
    struct i2c_cb_args_s *next;
};

struct i2c_driver_fifo_s
{
    /* Best to use only one queue since both RX & TX can be used at the same time. */
    struct pi_task *hw_buffer[2];                 /* RX + TX */
    struct i2c_cb_args_s *fifo_head;              /* Head of SW fifo waiting transfers. */
    struct i2c_cb_args_s *fifo_tail;              /* Tail of SW fifo waiting transfers. */
    struct i2c_pending_transfer_s *pending;       /* RX + TX. */
    uint32_t cs;                                  /* Chip select i2c device. */
    uint32_t max_baudrate;                        /* Max baudrate for the selected i2c chip. */
    uint32_t div;                                 /* Clock divider for the selected i2c chip. */
    uint32_t i2c_cmd_index;                       /* Number of commands in i2c_cmd_seq. */
    uint8_t i2c_cmd_seq[__PI_I2C_CMD_BUFF_SIZE];  /* Command sequence. */
    uint8_t i2c_stop_send;                        /* Set if a stop command sequence should be sent. */
    uint8_t i2c_stop_seq[__PI_I2C_STOP_CMD_SIZE]; /* Command STOP sequence. */
};

/*******************************************************************************
 * Driver data
 *****************************************************************************/

/*******************************************************************************
 * Function declaration
 ******************************************************************************/

/* Copy in UDMA. */
void __pi_i2c_copy(struct i2c_driver_fifo_s *fifo, struct i2c_transfer_s *transfer, struct pi_task *task);

/* Handler. */
void i2c_handler(void *arg);

/* Clock divider. */
uint32_t __pi_i2c_get_clk_div(uint32_t baudrate);

#endif /* HAL_INCLUDE_HAL_I2C_INTERNAL_H_ */
