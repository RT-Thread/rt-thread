/**
  ******************************************************************************
  * @file    can_reg.h
  * @version V1.0
  * @date    2020-12-29
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __CAN_REG_H__
#define __CAN_REG_H__

#include "bl808.h"

/* 0x0 : op mode:rw        reset mode:rw */
#define CAN_MODE_OFFSET            (0x0)
#define CAN_RESET_REQUEST          CAN_RESET_REQUEST
#define CAN_RESET_REQUEST_POS      (0U)
#define CAN_RESET_REQUEST_LEN      (1U)
#define CAN_RESET_REQUEST_MSK      (((1U << CAN_RESET_REQUEST_LEN) - 1) << CAN_RESET_REQUEST_POS)
#define CAN_RESET_REQUEST_UMSK     (~(((1U << CAN_RESET_REQUEST_LEN) - 1) << CAN_RESET_REQUEST_POS))
#define CAN_LISTEN_ONLY            CAN_LISTEN_ONLY
#define CAN_LISTEN_ONLY_POS        (1U)
#define CAN_LISTEN_ONLY_LEN        (1U)
#define CAN_LISTEN_ONLY_MSK        (((1U << CAN_LISTEN_ONLY_LEN) - 1) << CAN_LISTEN_ONLY_POS)
#define CAN_LISTEN_ONLY_UMSK       (~(((1U << CAN_LISTEN_ONLY_LEN) - 1) << CAN_LISTEN_ONLY_POS))
#define CAN_SELT_TEST              CAN_SELT_TEST
#define CAN_SELT_TEST_POS          (2U)
#define CAN_SELT_TEST_LEN          (1U)
#define CAN_SELT_TEST_MSK          (((1U << CAN_SELT_TEST_LEN) - 1) << CAN_SELT_TEST_POS)
#define CAN_SELT_TEST_UMSK         (~(((1U << CAN_SELT_TEST_LEN) - 1) << CAN_SELT_TEST_POS))
#define CAN_ACCEPTANCE_FILTER      CAN_ACCEPTANCE_FILTER
#define CAN_ACCEPTANCE_FILTER_POS  (3U)
#define CAN_ACCEPTANCE_FILTER_LEN  (1U)
#define CAN_ACCEPTANCE_FILTER_MSK  (((1U << CAN_ACCEPTANCE_FILTER_LEN) - 1) << CAN_ACCEPTANCE_FILTER_POS)
#define CAN_ACCEPTANCE_FILTER_UMSK (~(((1U << CAN_ACCEPTANCE_FILTER_LEN) - 1) << CAN_ACCEPTANCE_FILTER_POS))

/* 0x4 : op mode:w        r  ->  8'h00
reset mode:w    r   -> 8'h00 */
#define CAN_COMMAND_OFFSET              (0x4)
#define CAN_TRANSMIT_REQUEST            CAN_TRANSMIT_REQUEST
#define CAN_TRANSMIT_REQUEST_POS        (0U)
#define CAN_TRANSMIT_REQUEST_LEN        (1U)
#define CAN_TRANSMIT_REQUEST_MSK        (((1U << CAN_TRANSMIT_REQUEST_LEN) - 1) << CAN_TRANSMIT_REQUEST_POS)
#define CAN_TRANSMIT_REQUEST_UMSK       (~(((1U << CAN_TRANSMIT_REQUEST_LEN) - 1) << CAN_TRANSMIT_REQUEST_POS))
#define CAN_ABORT_TRANSMISSION          CAN_ABORT_TRANSMISSION
#define CAN_ABORT_TRANSMISSION_POS      (1U)
#define CAN_ABORT_TRANSMISSION_LEN      (1U)
#define CAN_ABORT_TRANSMISSION_MSK      (((1U << CAN_ABORT_TRANSMISSION_LEN) - 1) << CAN_ABORT_TRANSMISSION_POS)
#define CAN_ABORT_TRANSMISSION_UMSK     (~(((1U << CAN_ABORT_TRANSMISSION_LEN) - 1) << CAN_ABORT_TRANSMISSION_POS))
#define CAN_RELEASE_RECEIVE_BUFFER      CAN_RELEASE_RECEIVE_BUFFER
#define CAN_RELEASE_RECEIVE_BUFFER_POS  (2U)
#define CAN_RELEASE_RECEIVE_BUFFER_LEN  (1U)
#define CAN_RELEASE_RECEIVE_BUFFER_MSK  (((1U << CAN_RELEASE_RECEIVE_BUFFER_LEN) - 1) << CAN_RELEASE_RECEIVE_BUFFER_POS)
#define CAN_RELEASE_RECEIVE_BUFFER_UMSK (~(((1U << CAN_RELEASE_RECEIVE_BUFFER_LEN) - 1) << CAN_RELEASE_RECEIVE_BUFFER_POS))
#define CAN_CLEAR_DATA_OVERRUN          CAN_CLEAR_DATA_OVERRUN
#define CAN_CLEAR_DATA_OVERRUN_POS      (3U)
#define CAN_CLEAR_DATA_OVERRUN_LEN      (1U)
#define CAN_CLEAR_DATA_OVERRUN_MSK      (((1U << CAN_CLEAR_DATA_OVERRUN_LEN) - 1) << CAN_CLEAR_DATA_OVERRUN_POS)
#define CAN_CLEAR_DATA_OVERRUN_UMSK     (~(((1U << CAN_CLEAR_DATA_OVERRUN_LEN) - 1) << CAN_CLEAR_DATA_OVERRUN_POS))
#define CAN_SELF_REQUEST                CAN_SELF_REQUEST
#define CAN_SELF_REQUEST_POS            (4U)
#define CAN_SELF_REQUEST_LEN            (1U)
#define CAN_SELF_REQUEST_MSK            (((1U << CAN_SELF_REQUEST_LEN) - 1) << CAN_SELF_REQUEST_POS)
#define CAN_SELF_REQUEST_UMSK           (~(((1U << CAN_SELF_REQUEST_LEN) - 1) << CAN_SELF_REQUEST_POS))

/* 0x8 : op mode:r       reset mode:r */
#define CAN_STATUS_OFFSET              (0x8)
#define CAN_RECEIVE_BUFFER_STS         CAN_RECEIVE_BUFFER_STS
#define CAN_RECEIVE_BUFFER_STS_POS     (0U)
#define CAN_RECEIVE_BUFFER_STS_LEN     (1U)
#define CAN_RECEIVE_BUFFER_STS_MSK     (((1U << CAN_RECEIVE_BUFFER_STS_LEN) - 1) << CAN_RECEIVE_BUFFER_STS_POS)
#define CAN_RECEIVE_BUFFER_STS_UMSK    (~(((1U << CAN_RECEIVE_BUFFER_STS_LEN) - 1) << CAN_RECEIVE_BUFFER_STS_POS))
#define CAN_DATA_OVERRUN_STS           CAN_DATA_OVERRUN_STS
#define CAN_DATA_OVERRUN_STS_POS       (1U)
#define CAN_DATA_OVERRUN_STS_LEN       (1U)
#define CAN_DATA_OVERRUN_STS_MSK       (((1U << CAN_DATA_OVERRUN_STS_LEN) - 1) << CAN_DATA_OVERRUN_STS_POS)
#define CAN_DATA_OVERRUN_STS_UMSK      (~(((1U << CAN_DATA_OVERRUN_STS_LEN) - 1) << CAN_DATA_OVERRUN_STS_POS))
#define CAN_TRANSMIT_BUFFER_STS        CAN_TRANSMIT_BUFFER_STS
#define CAN_TRANSMIT_BUFFER_STS_POS    (2U)
#define CAN_TRANSMIT_BUFFER_STS_LEN    (1U)
#define CAN_TRANSMIT_BUFFER_STS_MSK    (((1U << CAN_TRANSMIT_BUFFER_STS_LEN) - 1) << CAN_TRANSMIT_BUFFER_STS_POS)
#define CAN_TRANSMIT_BUFFER_STS_UMSK   (~(((1U << CAN_TRANSMIT_BUFFER_STS_LEN) - 1) << CAN_TRANSMIT_BUFFER_STS_POS))
#define CAN_TRANSMIT_COMPLETE_STS      CAN_TRANSMIT_COMPLETE_STS
#define CAN_TRANSMIT_COMPLETE_STS_POS  (3U)
#define CAN_TRANSMIT_COMPLETE_STS_LEN  (1U)
#define CAN_TRANSMIT_COMPLETE_STS_MSK  (((1U << CAN_TRANSMIT_COMPLETE_STS_LEN) - 1) << CAN_TRANSMIT_COMPLETE_STS_POS)
#define CAN_TRANSMIT_COMPLETE_STS_UMSK (~(((1U << CAN_TRANSMIT_COMPLETE_STS_LEN) - 1) << CAN_TRANSMIT_COMPLETE_STS_POS))
#define CAN_RECEIVE_STS                CAN_RECEIVE_STS
#define CAN_RECEIVE_STS_POS            (4U)
#define CAN_RECEIVE_STS_LEN            (1U)
#define CAN_RECEIVE_STS_MSK            (((1U << CAN_RECEIVE_STS_LEN) - 1) << CAN_RECEIVE_STS_POS)
#define CAN_RECEIVE_STS_UMSK           (~(((1U << CAN_RECEIVE_STS_LEN) - 1) << CAN_RECEIVE_STS_POS))
#define CAN_TRANSMIT_STS               CAN_TRANSMIT_STS
#define CAN_TRANSMIT_STS_POS           (5U)
#define CAN_TRANSMIT_STS_LEN           (1U)
#define CAN_TRANSMIT_STS_MSK           (((1U << CAN_TRANSMIT_STS_LEN) - 1) << CAN_TRANSMIT_STS_POS)
#define CAN_TRANSMIT_STS_UMSK          (~(((1U << CAN_TRANSMIT_STS_LEN) - 1) << CAN_TRANSMIT_STS_POS))
#define CAN_ERROR_STS                  CAN_ERROR_STS
#define CAN_ERROR_STS_POS              (6U)
#define CAN_ERROR_STS_LEN              (1U)
#define CAN_ERROR_STS_MSK              (((1U << CAN_ERROR_STS_LEN) - 1) << CAN_ERROR_STS_POS)
#define CAN_ERROR_STS_UMSK             (~(((1U << CAN_ERROR_STS_LEN) - 1) << CAN_ERROR_STS_POS))
#define CAN_BUS_STS                    CAN_BUS_STS
#define CAN_BUS_STS_POS                (7U)
#define CAN_BUS_STS_LEN                (1U)
#define CAN_BUS_STS_MSK                (((1U << CAN_BUS_STS_LEN) - 1) << CAN_BUS_STS_POS)
#define CAN_BUS_STS_UMSK               (~(((1U << CAN_BUS_STS_LEN) - 1) << CAN_BUS_STS_POS))

/* 0xc : op mode:r        reset mode:r      when be read,all bits are reseted and can_int disappear */
#define CAN_INTERRUPT_OFFSET       (0xc)
#define CAN_RECEIVE_INT            CAN_RECEIVE_INT
#define CAN_RECEIVE_INT_POS        (0U)
#define CAN_RECEIVE_INT_LEN        (1U)
#define CAN_RECEIVE_INT_MSK        (((1U << CAN_RECEIVE_INT_LEN) - 1) << CAN_RECEIVE_INT_POS)
#define CAN_RECEIVE_INT_UMSK       (~(((1U << CAN_RECEIVE_INT_LEN) - 1) << CAN_RECEIVE_INT_POS))
#define CAN_TRANSMIT_INT           CAN_TRANSMIT_INT
#define CAN_TRANSMIT_INT_POS       (1U)
#define CAN_TRANSMIT_INT_LEN       (1U)
#define CAN_TRANSMIT_INT_MSK       (((1U << CAN_TRANSMIT_INT_LEN) - 1) << CAN_TRANSMIT_INT_POS)
#define CAN_TRANSMIT_INT_UMSK      (~(((1U << CAN_TRANSMIT_INT_LEN) - 1) << CAN_TRANSMIT_INT_POS))
#define CAN_ERROR_INT              CAN_ERROR_INT
#define CAN_ERROR_INT_POS          (2U)
#define CAN_ERROR_INT_LEN          (1U)
#define CAN_ERROR_INT_MSK          (((1U << CAN_ERROR_INT_LEN) - 1) << CAN_ERROR_INT_POS)
#define CAN_ERROR_INT_UMSK         (~(((1U << CAN_ERROR_INT_LEN) - 1) << CAN_ERROR_INT_POS))
#define CAN_DATA_OVERRUN_INT       CAN_DATA_OVERRUN_INT
#define CAN_DATA_OVERRUN_INT_POS   (3U)
#define CAN_DATA_OVERRUN_INT_LEN   (1U)
#define CAN_DATA_OVERRUN_INT_MSK   (((1U << CAN_DATA_OVERRUN_INT_LEN) - 1) << CAN_DATA_OVERRUN_INT_POS)
#define CAN_DATA_OVERRUN_INT_UMSK  (~(((1U << CAN_DATA_OVERRUN_INT_LEN) - 1) << CAN_DATA_OVERRUN_INT_POS))
#define CAN_ERROR_PASSIVE_INT      CAN_ERROR_PASSIVE_INT
#define CAN_ERROR_PASSIVE_INT_POS  (5U)
#define CAN_ERROR_PASSIVE_INT_LEN  (1U)
#define CAN_ERROR_PASSIVE_INT_MSK  (((1U << CAN_ERROR_PASSIVE_INT_LEN) - 1) << CAN_ERROR_PASSIVE_INT_POS)
#define CAN_ERROR_PASSIVE_INT_UMSK (~(((1U << CAN_ERROR_PASSIVE_INT_LEN) - 1) << CAN_ERROR_PASSIVE_INT_POS))
#define CAN_ARB_LOST_INT           CAN_ARB_LOST_INT
#define CAN_ARB_LOST_INT_POS       (6U)
#define CAN_ARB_LOST_INT_LEN       (1U)
#define CAN_ARB_LOST_INT_MSK       (((1U << CAN_ARB_LOST_INT_LEN) - 1) << CAN_ARB_LOST_INT_POS)
#define CAN_ARB_LOST_INT_UMSK      (~(((1U << CAN_ARB_LOST_INT_LEN) - 1) << CAN_ARB_LOST_INT_POS))
#define CAN_BUS_ERROR_INT          CAN_BUS_ERROR_INT
#define CAN_BUS_ERROR_INT_POS      (7U)
#define CAN_BUS_ERROR_INT_LEN      (1U)
#define CAN_BUS_ERROR_INT_MSK      (((1U << CAN_BUS_ERROR_INT_LEN) - 1) << CAN_BUS_ERROR_INT_POS)
#define CAN_BUS_ERROR_INT_UMSK     (~(((1U << CAN_BUS_ERROR_INT_LEN) - 1) << CAN_BUS_ERROR_INT_POS))

/* 0x10 : op mode:rw        reset mode:rw      when be read,all bits are reseted and can_int disappear */
#define CAN_INTERRUPT_ENABLE_OFFSET   (0x10)
#define CAN_RECEIVE_INT_EN            CAN_RECEIVE_INT_EN
#define CAN_RECEIVE_INT_EN_POS        (0U)
#define CAN_RECEIVE_INT_EN_LEN        (1U)
#define CAN_RECEIVE_INT_EN_MSK        (((1U << CAN_RECEIVE_INT_EN_LEN) - 1) << CAN_RECEIVE_INT_EN_POS)
#define CAN_RECEIVE_INT_EN_UMSK       (~(((1U << CAN_RECEIVE_INT_EN_LEN) - 1) << CAN_RECEIVE_INT_EN_POS))
#define CAN_TRANSMIT_INT_EN           CAN_TRANSMIT_INT_EN
#define CAN_TRANSMIT_INT_EN_POS       (1U)
#define CAN_TRANSMIT_INT_EN_LEN       (1U)
#define CAN_TRANSMIT_INT_EN_MSK       (((1U << CAN_TRANSMIT_INT_EN_LEN) - 1) << CAN_TRANSMIT_INT_EN_POS)
#define CAN_TRANSMIT_INT_EN_UMSK      (~(((1U << CAN_TRANSMIT_INT_EN_LEN) - 1) << CAN_TRANSMIT_INT_EN_POS))
#define CAN_ERROR_INT_EN              CAN_ERROR_INT_EN
#define CAN_ERROR_INT_EN_POS          (2U)
#define CAN_ERROR_INT_EN_LEN          (1U)
#define CAN_ERROR_INT_EN_MSK          (((1U << CAN_ERROR_INT_EN_LEN) - 1) << CAN_ERROR_INT_EN_POS)
#define CAN_ERROR_INT_EN_UMSK         (~(((1U << CAN_ERROR_INT_EN_LEN) - 1) << CAN_ERROR_INT_EN_POS))
#define CAN_DATA_OVERRUN_INT_EN       CAN_DATA_OVERRUN_INT_EN
#define CAN_DATA_OVERRUN_INT_EN_POS   (3U)
#define CAN_DATA_OVERRUN_INT_EN_LEN   (1U)
#define CAN_DATA_OVERRUN_INT_EN_MSK   (((1U << CAN_DATA_OVERRUN_INT_EN_LEN) - 1) << CAN_DATA_OVERRUN_INT_EN_POS)
#define CAN_DATA_OVERRUN_INT_EN_UMSK  (~(((1U << CAN_DATA_OVERRUN_INT_EN_LEN) - 1) << CAN_DATA_OVERRUN_INT_EN_POS))
#define CAN_ERROR_PASSIVE_INT_EN      CAN_ERROR_PASSIVE_INT_EN
#define CAN_ERROR_PASSIVE_INT_EN_POS  (5U)
#define CAN_ERROR_PASSIVE_INT_EN_LEN  (1U)
#define CAN_ERROR_PASSIVE_INT_EN_MSK  (((1U << CAN_ERROR_PASSIVE_INT_EN_LEN) - 1) << CAN_ERROR_PASSIVE_INT_EN_POS)
#define CAN_ERROR_PASSIVE_INT_EN_UMSK (~(((1U << CAN_ERROR_PASSIVE_INT_EN_LEN) - 1) << CAN_ERROR_PASSIVE_INT_EN_POS))
#define CAN_ARB_LOST_INT_EN           CAN_ARB_LOST_INT_EN
#define CAN_ARB_LOST_INT_EN_POS       (6U)
#define CAN_ARB_LOST_INT_EN_LEN       (1U)
#define CAN_ARB_LOST_INT_EN_MSK       (((1U << CAN_ARB_LOST_INT_EN_LEN) - 1) << CAN_ARB_LOST_INT_EN_POS)
#define CAN_ARB_LOST_INT_EN_UMSK      (~(((1U << CAN_ARB_LOST_INT_EN_LEN) - 1) << CAN_ARB_LOST_INT_EN_POS))
#define CAN_BUS_ERROR_INT_EN          CAN_BUS_ERROR_INT_EN
#define CAN_BUS_ERROR_INT_EN_POS      (7U)
#define CAN_BUS_ERROR_INT_EN_LEN      (1U)
#define CAN_BUS_ERROR_INT_EN_MSK      (((1U << CAN_BUS_ERROR_INT_EN_LEN) - 1) << CAN_BUS_ERROR_INT_EN_POS)
#define CAN_BUS_ERROR_INT_EN_UMSK     (~(((1U << CAN_BUS_ERROR_INT_EN_LEN) - 1) << CAN_BUS_ERROR_INT_EN_POS))

/* 0x18 : op mode:r   reset mode:rw */
#define CAN_BUS_TIMING_0_OFFSET      (0x18)
#define CAN_BAUD_RATE_PRESCALER      CAN_BAUD_RATE_PRESCALER
#define CAN_BAUD_RATE_PRESCALER_POS  (0U)
#define CAN_BAUD_RATE_PRESCALER_LEN  (6U)
#define CAN_BAUD_RATE_PRESCALER_MSK  (((1U << CAN_BAUD_RATE_PRESCALER_LEN) - 1) << CAN_BAUD_RATE_PRESCALER_POS)
#define CAN_BAUD_RATE_PRESCALER_UMSK (~(((1U << CAN_BAUD_RATE_PRESCALER_LEN) - 1) << CAN_BAUD_RATE_PRESCALER_POS))
#define CAN_SYNC_JUMP_WIDTH          CAN_SYNC_JUMP_WIDTH
#define CAN_SYNC_JUMP_WIDTH_POS      (6U)
#define CAN_SYNC_JUMP_WIDTH_LEN      (2U)
#define CAN_SYNC_JUMP_WIDTH_MSK      (((1U << CAN_SYNC_JUMP_WIDTH_LEN) - 1) << CAN_SYNC_JUMP_WIDTH_POS)
#define CAN_SYNC_JUMP_WIDTH_UMSK     (~(((1U << CAN_SYNC_JUMP_WIDTH_LEN) - 1) << CAN_SYNC_JUMP_WIDTH_POS))

/* 0x1c : op mode:r  reset mode:rw */
#define CAN_BUS_TIMING_1_OFFSET (0x1c)
#define CAN_TIME_SEGMENT_1      CAN_TIME_SEGMENT_1
#define CAN_TIME_SEGMENT_1_POS  (0U)
#define CAN_TIME_SEGMENT_1_LEN  (4U)
#define CAN_TIME_SEGMENT_1_MSK  (((1U << CAN_TIME_SEGMENT_1_LEN) - 1) << CAN_TIME_SEGMENT_1_POS)
#define CAN_TIME_SEGMENT_1_UMSK (~(((1U << CAN_TIME_SEGMENT_1_LEN) - 1) << CAN_TIME_SEGMENT_1_POS))
#define CAN_TIME_SEGMENT_2      CAN_TIME_SEGMENT_2
#define CAN_TIME_SEGMENT_2_POS  (4U)
#define CAN_TIME_SEGMENT_2_LEN  (3U)
#define CAN_TIME_SEGMENT_2_MSK  (((1U << CAN_TIME_SEGMENT_2_LEN) - 1) << CAN_TIME_SEGMENT_2_POS)
#define CAN_TIME_SEGMENT_2_UMSK (~(((1U << CAN_TIME_SEGMENT_2_LEN) - 1) << CAN_TIME_SEGMENT_2_POS))
#define CAN_SAMPLING            CAN_SAMPLING
#define CAN_SAMPLING_POS        (7U)
#define CAN_SAMPLING_LEN        (1U)
#define CAN_SAMPLING_MSK        (((1U << CAN_SAMPLING_LEN) - 1) << CAN_SAMPLING_POS)
#define CAN_SAMPLING_UMSK       (~(((1U << CAN_SAMPLING_LEN) - 1) << CAN_SAMPLING_POS))

/* 0x2c : op mode:r       reset mode:r */
#define CAN_ARB_LOST_CAPTURE_OFFSET (0x2c)
#define CAN_ALC4_0                  CAN_ALC4_0
#define CAN_ALC4_0_POS              (0U)
#define CAN_ALC4_0_LEN              (5U)
#define CAN_ALC4_0_MSK              (((1U << CAN_ALC4_0_LEN) - 1) << CAN_ALC4_0_POS)
#define CAN_ALC4_0_UMSK             (~(((1U << CAN_ALC4_0_LEN) - 1) << CAN_ALC4_0_POS))

/* 0x30 : op mode:r      reset mode:r */
#define CAN_ERROR_CODE_CAPTURE_OFFSET (0x30)
#define CAN_SEGMENT4_0                CAN_SEGMENT4_0
#define CAN_SEGMENT4_0_POS            (0U)
#define CAN_SEGMENT4_0_LEN            (5U)
#define CAN_SEGMENT4_0_MSK            (((1U << CAN_SEGMENT4_0_LEN) - 1) << CAN_SEGMENT4_0_POS)
#define CAN_SEGMENT4_0_UMSK           (~(((1U << CAN_SEGMENT4_0_LEN) - 1) << CAN_SEGMENT4_0_POS))
#define CAN_DIR                       CAN_DIR
#define CAN_DIR_POS                   (5U)
#define CAN_DIR_LEN                   (1U)
#define CAN_DIR_MSK                   (((1U << CAN_DIR_LEN) - 1) << CAN_DIR_POS)
#define CAN_DIR_UMSK                  (~(((1U << CAN_DIR_LEN) - 1) << CAN_DIR_POS))
#define CAN_ERR_CODE                  CAN_ERR_CODE
#define CAN_ERR_CODE_POS              (6U)
#define CAN_ERR_CODE_LEN              (2U)
#define CAN_ERR_CODE_MSK              (((1U << CAN_ERR_CODE_LEN) - 1) << CAN_ERR_CODE_POS)
#define CAN_ERR_CODE_UMSK             (~(((1U << CAN_ERR_CODE_LEN) - 1) << CAN_ERR_CODE_POS))

/* 0x34 : op mode:r     reset mode:rw */
#define CAN_ERROR_WARNING_LIMIT_OFFSET (0x34)
#define CAN_ERR_WARNING_LIMIT          CAN_ERR_WARNING_LIMIT
#define CAN_ERR_WARNING_LIMIT_POS      (0U)
#define CAN_ERR_WARNING_LIMIT_LEN      (8U)
#define CAN_ERR_WARNING_LIMIT_MSK      (((1U << CAN_ERR_WARNING_LIMIT_LEN) - 1) << CAN_ERR_WARNING_LIMIT_POS)
#define CAN_ERR_WARNING_LIMIT_UMSK     (~(((1U << CAN_ERR_WARNING_LIMIT_LEN) - 1) << CAN_ERR_WARNING_LIMIT_POS))

/* 0x38 : op mode:r     reset mode:rw */
#define CAN_RX_ERR_COUNT_OFFSET (0x38)
#define CAN_RX_ERR_CNT          CAN_RX_ERR_CNT
#define CAN_RX_ERR_CNT_POS      (0U)
#define CAN_RX_ERR_CNT_LEN      (8U)
#define CAN_RX_ERR_CNT_MSK      (((1U << CAN_RX_ERR_CNT_LEN) - 1) << CAN_RX_ERR_CNT_POS)
#define CAN_RX_ERR_CNT_UMSK     (~(((1U << CAN_RX_ERR_CNT_LEN) - 1) << CAN_RX_ERR_CNT_POS))

/* 0x3c : op mode:r      reset mode:rw */
#define CAN_TX_ERR_COUNT_OFFSET (0x3c)
#define CAN_TX_ERR_CNT          CAN_TX_ERR_CNT
#define CAN_TX_ERR_CNT_POS      (0U)
#define CAN_TX_ERR_CNT_LEN      (8U)
#define CAN_TX_ERR_CNT_MSK      (((1U << CAN_TX_ERR_CNT_LEN) - 1) << CAN_TX_ERR_CNT_POS)
#define CAN_TX_ERR_CNT_UMSK     (~(((1U << CAN_TX_ERR_CNT_LEN) - 1) << CAN_TX_ERR_CNT_POS))

/* 0x40 : op mode: w  ->  tx_frm_info
                r   ->  rx_frm_info
reset mode:rw  -> acceptance_code0 */
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_OFFSET (0x40)
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0        CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_POS    (0U)
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_LEN    (8U)
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_MSK    (((1U << CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_LEN) - 1) << CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_POS)
#define CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_UMSK   (~(((1U << CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_LEN) - 1) << CAN_TXRX_FRM_INFO_OR_ACCEPTANCE_CODE0_POS))

/* 0x44 : op mode:w  ->  tx_id1
               r   ->  rx_id1
reset mode:rw  ->  acceptance_code1 */
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_OFFSET (0x44)
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1        CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_POS    (0U)
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_LEN    (8U)
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_MSK    (((1U << CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_LEN) - 1) << CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_POS)
#define CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_UMSK   (~(((1U << CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_LEN) - 1) << CAN_TXRX_ID1_OR_ACCEPTANCE_CODE1_POS))

/* 0x48 : op mode:w   ->  tx_id2
                r   ->  rx_id2
 reset mode:rw ->  acceptance_code2 */
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_OFFSET (0x48)
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2        CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_POS    (0U)
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_LEN    (8U)
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_MSK    (((1U << CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_LEN) - 1) << CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_POS)
#define CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_UMSK   (~(((1U << CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_LEN) - 1) << CAN_TXRX_ID2_OR_ACCEPTANCE_CODE2_POS))

/* 0x74 : op mode:r    reset mode:r */
#define CAN_RX_MESSAGE_COUNT_OFFSET (0x74)
#define CAN_RX_MESSAGE_CNT          CAN_RX_MESSAGE_CNT
#define CAN_RX_MESSAGE_CNT_POS      (0U)
#define CAN_RX_MESSAGE_CNT_LEN      (5U)
#define CAN_RX_MESSAGE_CNT_MSK      (((1U << CAN_RX_MESSAGE_CNT_LEN) - 1) << CAN_RX_MESSAGE_CNT_POS)
#define CAN_RX_MESSAGE_CNT_UMSK     (~(((1U << CAN_RX_MESSAGE_CNT_LEN) - 1) << CAN_RX_MESSAGE_CNT_POS))

/* 0x7c : op mode:rw       reset mode:rw    can_mode and cbp can be write in reset mode only */
#define CAN_CLOCK_DIVIDER_OFFSET (0x7c)
#define CAN_CD                   CAN_CD
#define CAN_CD_POS               (0U)
#define CAN_CD_LEN               (3U)
#define CAN_CD_MSK               (((1U << CAN_CD_LEN) - 1) << CAN_CD_POS)
#define CAN_CD_UMSK              (~(((1U << CAN_CD_LEN) - 1) << CAN_CD_POS))
#define CAN_CLOCKOFF             CAN_CLOCKOFF
#define CAN_CLOCKOFF_POS         (3U)
#define CAN_CLOCKOFF_LEN         (1U)
#define CAN_CLOCKOFF_MSK         (((1U << CAN_CLOCKOFF_LEN) - 1) << CAN_CLOCKOFF_POS)
#define CAN_CLOCKOFF_UMSK        (~(((1U << CAN_CLOCKOFF_LEN) - 1) << CAN_CLOCKOFF_POS))
#define CAN_READONLY             CAN_READONLY
#define CAN_READONLY_POS         (4U)
#define CAN_READONLY_LEN         (1U)
#define CAN_READONLY_MSK         (((1U << CAN_READONLY_LEN) - 1) << CAN_READONLY_POS)
#define CAN_READONLY_UMSK        (~(((1U << CAN_READONLY_LEN) - 1) << CAN_READONLY_POS))
#define CAN_RXINTEN              CAN_RXINTEN
#define CAN_RXINTEN_POS          (5U)
#define CAN_RXINTEN_LEN          (1U)
#define CAN_RXINTEN_MSK          (((1U << CAN_RXINTEN_LEN) - 1) << CAN_RXINTEN_POS)
#define CAN_RXINTEN_UMSK         (~(((1U << CAN_RXINTEN_LEN) - 1) << CAN_RXINTEN_POS))
#define CAN_CBP                  CAN_CBP
#define CAN_CBP_POS              (6U)
#define CAN_CBP_LEN              (1U)
#define CAN_CBP_MSK              (((1U << CAN_CBP_LEN) - 1) << CAN_CBP_POS)
#define CAN_CBP_UMSK             (~(((1U << CAN_CBP_LEN) - 1) << CAN_CBP_POS))
#define CAN_MODE                 CAN_MODE
#define CAN_MODE_POS             (7U)
#define CAN_MODE_LEN             (1U)
#define CAN_MODE_MSK             (((1U << CAN_MODE_LEN) - 1) << CAN_MODE_POS)
#define CAN_MODE_UMSK            (~(((1U << CAN_MODE_LEN) - 1) << CAN_MODE_POS))

/* 0x40 : Frame information */
#define CAN_INFORMATION_OFFSET (0x40)
#define CAN_INF_DLC            CAN_INF_DLC
#define CAN_INF_DLC_POS        (0U)
#define CAN_INF_DLC_LEN        (4U)
#define CAN_INF_DLC_MSK        (((1U << CAN_INF_DLC_LEN) - 1) << CAN_INF_DLC_POS)
#define CAN_INF_DLC_UMSK       (~(((1U << CAN_INF_DLC_LEN) - 1) << CAN_INF_DLC_POS))
#define CAN_INF_RTR            CAN_INF_RTR
#define CAN_INF_RTR_POS        (6U)
#define CAN_INF_RTR_LEN        (1U)
#define CAN_INF_RTR_MSK        (((1U << CAN_INF_RTR_LEN) - 1) << CAN_INF_RTR_POS)
#define CAN_INF_RTR_UMSK       (~(((1U << CAN_INF_RTR_LEN) - 1) << CAN_INF_RTR_POS))
#define CAN_INF_FF             CAN_INF_FF
#define CAN_INF_FF_POS         (7U)
#define CAN_INF_FF_LEN         (1U)
#define CAN_INF_FF_MSK         (((1U << CAN_INF_FF_LEN) - 1) << CAN_INF_FF_POS)
#define CAN_INF_FF_UMSK        (~(((1U << CAN_INF_FF_LEN) - 1) << CAN_INF_FF_POS))

/* 0x44 : Identifier 1, ID28~21 */
#define CAN_IDENTIFIER_1_OFFSET (0x44)

/* 0x48 : Identifier 2, ID20~13, SFF Only use ID20~18 */
#define CAN_IDENTIFIER_2_OFFSET (0x48)

/* 0x4C : Identifier 3, ID12~5, only for EFF */
#define CAN_IDENTIFIER_3_OFFSET (0x4C)

/* 0x50 : Identifier 4, ID4~0, only for EFF */
#define CAN_IDENTIFIER_4_OFFSET (0x50)

/* 0x4C : Standard Format Data 1 buffer */
#define CAN_SFF_DATA_1_OFFSET (0x4C)

/* 0x50 : Standard Format Data 2 buffer */
#define CAN_SFF_DATA_2_OFFSET (0x50)

/* 0x54 : Standard Format Data 3 buffer */
#define CAN_SFF_DATA_3_OFFSET (0x54)

/* 0x58 : Standard Format Data 4 buffer */
#define CAN_SFF_DATA_4_OFFSET (0x58)

/* 0x5C : Standard Format Data 5 buffer */
#define CAN_SFF_DATA_5_OFFSET (0x5C)

/* 0x60 : Standard Format Data 6 buffer */
#define CAN_SFF_DATA_6_OFFSET (0x60)

/* 0x64 : Standard Format Data 7 buffer */
#define CAN_SFF_DATA_7_OFFSET (0x64)

/* 0x68 : Standard Format Data 8 buffer */
#define CAN_SFF_DATA_8_OFFSET (0x68)

/* 0x54 : Extended Format Data 1 buffer */
#define CAN_EFF_DATA_1_OFFSET (0x54)

/* 0x58 : Extended Format Data 2 buffer */
#define CAN_EFF_DATA_2_OFFSET (0x58)

/* 0x5C : Extended Format Data 3 buffer */
#define CAN_EFF_DATA_3_OFFSET (0x5C)

/* 0x60 : Extended Format Data 4 buffer */
#define CAN_EFF_DATA_4_OFFSET (0x60)

/* 0x64 : Extended Format Data 5 buffer */
#define CAN_EFF_DATA_5_OFFSET (0x64)

/* 0x68 : Extended Format Data 6 buffer */
#define CAN_EFF_DATA_6_OFFSET (0x68)

/* 0x6C : Extended Format Data 7 buffer */
#define CAN_EFF_DATA_7_OFFSET (0x6C)

/* 0x70 : Extended Format Data 8 buffer */
#define CAN_EFF_DATA_8_OFFSET (0x70)

/* 0x70 : Extended Format Data 8 buffer */
#define CAN_EFF_DATA_8_OFFSET (0x70)

/* 0x40 : Filter Acceptance 0 */
#define CAN_FILTER_ACCEPTANCE_0_OFFSET (0x40)

/* 0x44 : Filter Acceptance 1 */
#define CAN_FILTER_ACCEPTANCE_1_OFFSET (0x44)

/* 0x48 : Filter Acceptance 2 */
#define CAN_FILTER_ACCEPTANCE_2_OFFSET (0x48)

/* 0x4C : Filter Acceptance 3 */
#define CAN_FILTER_ACCEPTANCE_3_OFFSET (0x4C)

/* 0x50 : Filter Mask 0 */
#define CAN_FILTER_Mask_0_OFFSET (0x50)

/* 0x54 : Filter Mask 1 */
#define CAN_FILTER_Mask_1_OFFSET (0x54)

/* 0x58 : Filter Mask 2 */
#define CAN_FILTER_Mask_2_OFFSET (0x58)

/* 0x5C : Filter Mask 3 */
#define CAN_FILTER_Mask_3_OFFSET (0x5C)

/* 0x4C : Extended Format, Tx information 5, ID4~0 */
#define CAN_IDENTIFIER_4_OFFSET (0x50)

struct can_reg {
    /* 0x0 : op mode:rw        reset mode:rw */
    union {
        struct {
            uint32_t reset_request     : 1;  /* [    0],        w1c,        0x0 */
            uint32_t listen_only       : 1;  /* [    1],        w1c,        0x0 */
            uint32_t selt_test         : 1;  /* [    2],        w1c,        0x0 */
            uint32_t acceptance_filter : 1;  /* [    3],        w1c,        0x0 */
            uint32_t rsvd_7_4          : 4;  /* [ 7: 4],       rsvd,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mode;

    /* 0x4 : op mode:w        r  ->  8'h00
reset mode:w    r   -> 8'h00 */
    union {
        struct {
            uint32_t transmit_request       : 1;  /* [    0],        w1c,        0x0 */
            uint32_t abort_transmission     : 1;  /* [    1],        w1c,        0x0 */
            uint32_t release_receive_buffer : 1;  /* [    2],        w1c,        0x0 */
            uint32_t clear_data_overrun     : 1;  /* [    3],        w1c,        0x0 */
            uint32_t self_request           : 1;  /* [    4],        w1c,        0x0 */
            uint32_t rsvd_7_5               : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t reserved_8_31          : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } command;

    /* 0x8 : op mode:r       reset mode:r */
    union {
        struct {
            uint32_t receive_buffer_sts    : 1;  /* [    0],          r,        0x0 */
            uint32_t data_overrun_sts      : 1;  /* [    1],          r,        0x0 */
            uint32_t transmit_buffer_sts   : 1;  /* [    2],          r,        0x0 */
            uint32_t transmit_complete_sts : 1;  /* [    3],          r,        0x0 */
            uint32_t receive_sts           : 1;  /* [    4],          r,        0x0 */
            uint32_t transmit_sts          : 1;  /* [    5],          r,        0x0 */
            uint32_t error_sts             : 1;  /* [    6],          r,        0x0 */
            uint32_t bus_sts               : 1;  /* [    7],          r,        0x0 */
            uint32_t reserved_8_31         : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } status;

    /* 0xc : op mode:r        reset mode:r      when be read,all bits are reseted and can_int disappear */
    union {
        struct {
            uint32_t receive_int       : 1;  /* [    0],          r,        0x0 */
            uint32_t transmit_int      : 1;  /* [    1],          r,        0x0 */
            uint32_t error_int         : 1;  /* [    2],          r,        0x0 */
            uint32_t data_overrun_int  : 1;  /* [    3],          r,        0x0 */
            uint32_t rsvd_4            : 1;  /* [    4],       rsvd,        0x0 */
            uint32_t error_passive_int : 1;  /* [    5],          r,        0x0 */
            uint32_t arb_lost_int      : 1;  /* [    6],          r,        0x0 */
            uint32_t bus_error_int     : 1;  /* [    7],          r,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } interrupt;

    /* 0x10 : op mode:rw        reset mode:rw      when be read,all bits are reseted and can_int disappear */
    union {
        struct {
            uint32_t receive_int_en       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t transmit_int_en      : 1;  /* [    1],        r/w,        0x0 */
            uint32_t error_int_en         : 1;  /* [    2],        r/w,        0x0 */
            uint32_t data_overrun_int_en  : 1;  /* [    3],        r/w,        0x0 */
            uint32_t rsvd_4               : 1;  /* [    4],       rsvd,        0x0 */
            uint32_t error_passive_int_en : 1;  /* [    5],        r/w,        0x0 */
            uint32_t arb_lost_int_en      : 1;  /* [    6],        r/w,        0x0 */
            uint32_t bus_error_int_en     : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31        : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } interrupt_enable;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[4];

    /* 0x18 : op mode:r   reset mode:rw */
    union {
        struct {
            uint32_t baud_rate_prescaler_0 : 1;  /* [    0],        r/w,        0x0 */
            uint32_t baud_rate_prescaler_1 : 1;  /* [    1],        r/w,        0x0 */
            uint32_t baud_rate_prescaler_2 : 1;  /* [    2],        r/w,        0x0 */
            uint32_t baud_rate_prescaler_3 : 1;  /* [    3],        r/w,        0x0 */
            uint32_t baud_rate_prescaler_4 : 1;  /* [    4],        r/w,        0x0 */
            uint32_t baud_rate_prescaler_5 : 1;  /* [    5],        r/w,        0x0 */
            uint32_t sync_jump_width_0     : 1;  /* [    6],        r/w,        0x0 */
            uint32_t sync_jump_width_1     : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31         : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bus_timing_0;

    /* 0x1c : op mode:r  reset mode:rw */
    union {
        struct {
            uint32_t time_segment_1_0 : 1;  /* [    0],        r/w,        0x0 */
            uint32_t time_segment_1_1 : 1;  /* [    1],        r/w,        0x0 */
            uint32_t time_segment_1_2 : 1;  /* [    2],        r/w,        0x0 */
            uint32_t time_segment_1_3 : 1;  /* [    3],        r/w,        0x0 */
            uint32_t time_segment_2_0 : 1;  /* [    4],        r/w,        0x0 */
            uint32_t time_segment_2_1 : 1;  /* [    5],        r/w,        0x0 */
            uint32_t time_segment_2_2 : 1;  /* [    6],        r/w,        0x0 */
            uint32_t sampling         : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31    : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bus_timing_1;

    /* 0x20  reserved */
    uint8_t RESERVED0x20[12];

    /* 0x2c : op mode:r       reset mode:r */
    union {
        struct {
            uint32_t ALC4_0        : 5;  /* [ 4: 0],          r,        0x0 */
            uint32_t rsvd_7_5      : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } arb_lost_capture;

    /* 0x30 : op mode:r      reset mode:r */
    union {
        struct {
            uint32_t segment4_0    : 5;  /* [ 4: 0],          r,        0x0 */
            uint32_t dir           : 1;  /* [    5],          r,        0x0 */
            uint32_t err_code      : 2;  /* [ 7: 6],          r,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } error_code_capture;

    /* 0x34 : op mode:r     reset mode:rw */
    union {
        struct {
            uint32_t err_warning_limit : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } error_warning_limit;

    /* 0x38 : op mode:r     reset mode:rw */
    union {
        struct {
            uint32_t rx_err_cnt    : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } rx_err_count;

    /* 0x3c : op mode:r      reset mode:rw */
    union {
        struct {
            uint32_t tx_err_cnt    : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } tx_err_count;

    /* 0x40 : op mode: w  ->  tx_frm_info
                r   ->  rx_frm_info
reset mode:rw  -> acceptance_code0 */
    union {
        struct {
            uint32_t txrx_frm_info_or_acceptance_code0 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_frm_info_or_acceptance_code0;

    /* 0x44 : op mode:w  ->  tx_id1
               r   ->  rx_id1
reset mode:rw  ->  acceptance_code1 */
    union {
        struct {
            uint32_t txrx_id1_or_acceptance_code1 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_id1_or_acceptance_code1;

    /* 0x48 : op mode:w   ->  tx_id2
                r   ->  rx_id2
 reset mode:rw ->  acceptance_code2 */
    union {
        struct {
            uint32_t txrx_id2_or_acceptance_code2 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_id2_or_acceptance_code2;

    /* 0x4c : op mode:w  ->  tx_data1_s or tx_id3
               r   ->  rx_data1_s or rx_id3
 reset mode:rw  ->  acceptance_code3 */
    union {
        struct {
            uint32_t txrx_data1_s_or_txrx_id3_e_or_acceptance_code3 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                                  : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data1_s_or_txrx_id3_e_or_acceptance_code3;

    /* 0x50 : op mode:w  ->   tx_data2_s or tx_id4
               r   ->   rx_data2_s or rx_id4
reset mode:rw  ->  acceptance_mask0 */
    union {
        struct {
            uint32_t txrx_data2_s_or_txrx_id4_e_or_acceptance_mask0 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                                  : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data2_s_or_txrx_id4_e_or_acceptance_mask0;

    /* 0x54 : op mode:w  ->   tx_data3_s or  tx_data1_e
               r   ->   rx_data3_s or rx_data1_e
reset mode:rw  ->  acceptance_mask1 */
    union {
        struct {
            uint32_t txrx_data3_s_or_txrx_data1_e_or_acceptance_mask1 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                                    : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data3_s_or_txrx_data1_e_or_acceptance_mask1;

    /* 0x58 : op mode:w  ->   tx_data4_s or  tx_data2_e
               r   ->   rx_data4_s or rx_data2_e
reset mode:rw  ->  acceptance_mask2 */
    union {
        struct {
            uint32_t txrx_data4_s_or_txrx_data2_e_or_acceptance_mask2 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                                    : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data4_s_or_txrx_data2_e_or_acceptance_mask2;

    /* 0x5c : op mode:w  ->   tx_data5_s or  tx_data3_e
               r   ->   rx_data5_s or rx_data3_e
reset mode:rw  ->  acceptance_mask3 */
    union {
        struct {
            uint32_t txrx_data5_s_or_txrx_data3_e_or_acceptance_mask3 : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                                    : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data5_s_or_txrx_data3_e_or_acceptance_mask3;

    /* 0x60 : op mode:w  ->   tx_data6_s or  tx_data4_e
               r   ->   rx_data6_s or rx_data4_e
reset mode:r   ->  8'H00 */
    union {
        struct {
            uint32_t txrx_data6_s_or_txrx_data4_e : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data6_s_or_txrx_data4_e;

    /* 0x64 : op mode:w  ->   tx_data7_s or  tx_data5_e
               r   ->   rx_data7_s or rx_data5_e
reset mode:r   ->  8'H00 */
    union {
        struct {
            uint32_t txrx_data7_s_or_txrx_data5_e : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data7_s_or_txrx_data5_e;

    /* 0x68 : op mode:w  ->   tx_data8_s or  tx_data6_e
               r   ->   rx_data8_s or rx_data6_e
reset mode:r   ->  8'H00 */
    union {
        struct {
            uint32_t txrx_data8_s_or_txrx_data6_e : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data8_s_or_txrx_data6_e;

    /* 0x6c : op mode:w  ->   tx_data7_e
               r   ->   rx_data7_e
reset mode:r   ->  8'H00 */
    union {
        struct {
            uint32_t txrx_data7_e  : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data7_e;

    /* 0x70 : op mode:w  ->   tx_data8_e
               r   ->   rx_data8_e
reset mode:r   ->  8'H00 */
    union {
        struct {
            uint32_t txrx_data8_e  : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } txrx_data8_e;

    /* 0x74 : op mode:r    reset mode:r */
    union {
        struct {
            uint32_t rx_message_cnt : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31  : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } rx_message_count;

    /* 0x78  reserved */
    uint8_t RESERVED0x78[4];

    /* 0x7c : op mode:rw       reset mode:rw    can_mode and cbp can be write in reset mode only */
    union {
        struct {
            uint32_t cd            : 3;  /* [ 2: 0],        r/w,        0x0 */
            uint32_t clockoff      : 1;  /* [    3],        r/w,        0x0 */
            uint32_t readonly      : 1;  /* [    4],          r,        0x0 */
            uint32_t rxinten       : 1;  /* [    5],        r/w,        0x0 */
            uint32_t cbp           : 1;  /* [    6],        r/w,        0x0 */
            uint32_t can_mode      : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } clock_divider;
};

typedef volatile struct can_reg can_reg_t;

#endif /* __CAN_REG_H__ */
