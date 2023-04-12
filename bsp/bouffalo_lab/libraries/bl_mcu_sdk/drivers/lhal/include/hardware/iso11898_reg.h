/**
  ******************************************************************************
  * @file    iso11898_reg.h
  * @version V1.0
  * @date    2022-10-31
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
#ifndef  __ISO11898_REG_H__
#define  __ISO11898_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define ISO11898_MODE_OFFSET                                    (0x0)/* mode */
#define ISO11898_COMMAND_OFFSET                                 (0x4)/* command */
#define ISO11898_STATUS_OFFSET                                  (0x8)/* status */
#define ISO11898_INTERRUPT_OFFSET                               (0xc)/* interrupt */
#define ISO11898_INTERRUPT_ENABLE_OFFSET                        (0x10)/* interrupt_enable */
#define ISO11898_BUS_TIMING_0_OFFSET                            (0x18)/* bus_timing_0 */
#define ISO11898_BUS_TIMING_1_OFFSET                            (0x1c)/* bus_timing_1 */
#define ISO11898_ARB_LOST_CAPTURE_OFFSET                        (0x2c)/* arb_lost_capture */
#define ISO11898_ERROR_CODE_CAPTURE_OFFSET                      (0x30)/* error_code_capture */
#define ISO11898_ERROR_WARNING_LIMIT_OFFSET                     (0x34)/* error_warning_limit */
#define ISO11898_RX_ERR_COUNT_OFFSET                            (0x38)/* rx_err_count */
#define ISO11898_TX_ERR_COUNT_OFFSET                            (0x3c)/* tx_err_count */
#define ISO11898_FRAME_INFORMATION_OFFSET                       (0x40)/* frame_information */
#define ISO11898_ACCEPTANCE_CODE_0_OFFSET                       (0x40)/* acceptance_code_0 */
#define ISO11898_SFF_ID1_OFFSET                                 (0x44)/* sff_id1 */
#define ISO11898_EFF_ID1_OFFSET                                 (0x44)/* eff_id1 */
#define ISO11898_ACCEPTANCE_CODE_1_OFFSET                       (0x44)/* acceptance_code_1 */
#define ISO11898_SFF_ID2_OFFSET                                 (0x48)/* sff_id2 */
#define ISO11898_EFF_ID2_OFFSET                                 (0x48)/* eff_id2 */
#define ISO11898_ACCEPTANCE_CODE_2_OFFSET                       (0x48)/* acceptance_code_2 */
#define ISO11898_SFF_DATA1_OFFSET                               (0x4c)/* sff_data1 */
#define ISO11898_EFF_ID3_OFFSET                                 (0x4c)/* eff_id3 */
#define ISO11898_ACCEPTANCE_CODE_3_OFFSET                       (0x4c)/* acceptance_code_3 */
#define ISO11898_SFF_DATA2_OFFSET                               (0x50)/* sff_data2 */
#define ISO11898_EFF_ID4_OFFSET                                 (0x50)/* eff_id4 */
#define ISO11898_ACCEPTANCE_MASK_0_OFFSET                       (0x50)/* acceptance_mask_0 */
#define ISO11898_SFF_DATA3_OFFSET                               (0x54)/* sff_data3 */
#define ISO11898_EFF_DATA1_OFFSET                               (0x54)/* eff_data1 */
#define ISO11898_ACCEPTANCE_MASK_1_OFFSET                       (0x54)/* acceptance_mask_1 */
#define ISO11898_SFF_DATA4_OFFSET                               (0x58)/* sff_data4 */
#define ISO11898_EFF_DATA2_OFFSET                               (0x58)/* eff_data2 */
#define ISO11898_ACCEPTANCE_MASK_2_OFFSET                       (0x58)/* acceptance_mask_2 */
#define ISO11898_SFF_DATA5_OFFSET                               (0x5c)/* sff_data5 */
#define ISO11898_EFF_DATA3_OFFSET                               (0x5c)/* eff_data3 */
#define ISO11898_ACCEPTANCE_MASK_3_OFFSET                       (0x5c)/* acceptance_mask_3 */
#define ISO11898_SFF_DATA6_OFFSET                               (0x60)/* sff_data6 */
#define ISO11898_EFF_DATA4_OFFSET                               (0x60)/* eff_data4 */
#define ISO11898_SFF_DATA7_OFFSET                               (0x64)/* sff_data7 */
#define ISO11898_EFF_DATA5_OFFSET                               (0x64)/* eff_data5 */
#define ISO11898_SFF_DATA8_OFFSET                               (0x68)/* sff_data8 */
#define ISO11898_EFF_DATA6_OFFSET                               (0x68)/* eff_data6 */
#define ISO11898_EFF_DATA7_OFFSET                               (0x6c)/* eff_data7 */
#define ISO11898_EFF_DATA8_OFFSET                               (0x70)/* eff_data8 */
#define ISO11898_RX_MESSAGE_COUNT_OFFSET                        (0x74)/* rx_message_count */
#define ISO11898_CLOCK_DIVIDER_OFFSET                           (0x7c)/* clock_divider */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : mode */
#define ISO11898_RESET_REQUEST                                  (1<<0U)
#define ISO11898_LISTEN_ONLY                                    (1<<1U)
#define ISO11898_SELF_TEST                                      (1<<2U)
#define ISO11898_FILTER_TYPE                                    (1<<3U)

/* 0x4 : command */
#define ISO11898_TRANSMIT_REQUEST                               (1<<0U)
#define ISO11898_ABORT_TRANSMISSION                             (1<<1U)
#define ISO11898_RELEASE_RECEIVE_BUFFER                         (1<<2U)
#define ISO11898_CLEAR_DATA_OVERRUN                             (1<<3U)
#define ISO11898_SELF_REQUEST                                   (1<<4U)

/* 0x8 : status */
#define ISO11898_RECEIVE_BUFFER_STS                             (1<<0U)
#define ISO11898_DATA_OVERRUN_STS                               (1<<1U)
#define ISO11898_TRANSMIT_BUFFER_STS                            (1<<2U)
#define ISO11898_TRANSMIT_COMPLETE_STS                          (1<<3U)
#define ISO11898_RECEIVE_STS                                    (1<<4U)
#define ISO11898_TRANSMIT_STS                                   (1<<5U)
#define ISO11898_ERROR_STS                                      (1<<6U)
#define ISO11898_BUS_STS                                        (1<<7U)

/* 0xc : interrupt */
#define ISO11898_RECEIVE_INT                                    (1<<0U)
#define ISO11898_TRANSMIT_INT                                   (1<<1U)
#define ISO11898_ERROR_INT                                      (1<<2U)
#define ISO11898_DATA_OVERRUN_INT                               (1<<3U)
#define ISO11898_ERROR_PASSIVE_INT                              (1<<5U)
#define ISO11898_ARB_LOST_INT                                   (1<<6U)
#define ISO11898_BUS_ERROR_INT                                  (1<<7U)

/* 0x10 : interrupt_enable */
#define ISO11898_RECEIVE_INT_EN                                 (1<<0U)
#define ISO11898_TRANSMIT_INT_EN                                (1<<1U)
#define ISO11898_ERROR_INT_EN                                   (1<<2U)
#define ISO11898_DATA_OVERRUN_INT_EN                            (1<<3U)
#define ISO11898_ERROR_PASSIVE_INT_EN                           (1<<5U)
#define ISO11898_ARB_LOST_INT_EN                                (1<<6U)
#define ISO11898_BUS_ERROR_INT_EN                               (1<<7U)

/* 0x18 : bus_timing_0 */
#define ISO11898_BAUD_RATE_PRESCALER_SHIFT                      (0U)
#define ISO11898_BAUD_RATE_PRESCALER_MASK                       (0x3f<<ISO11898_BAUD_RATE_PRESCALER_SHIFT)
#define ISO11898_SYNC_JUMP_WIDTH_SHIFT                          (6U)
#define ISO11898_SYNC_JUMP_WIDTH_MASK                           (0x3<<ISO11898_SYNC_JUMP_WIDTH_SHIFT)

/* 0x1c : bus_timing_1 */
#define ISO11898_TIME_SEGMENT_1_SHIFT                           (0U)
#define ISO11898_TIME_SEGMENT_1_MASK                            (0xf<<ISO11898_TIME_SEGMENT_1_SHIFT)
#define ISO11898_TIME_SEGMENT_2_SHIFT                           (4U)
#define ISO11898_TIME_SEGMENT_2_MASK                            (0x7<<ISO11898_TIME_SEGMENT_2_SHIFT)
#define ISO11898_SAMPLING                                       (1<<7U)

/* 0x2c : arb_lost_capture */
#define ISO11898_ALC4_0_SHIFT                                   (0U)
#define ISO11898_ALC4_0_MASK                                    (0x1f<<ISO11898_ALC4_0_SHIFT)

/* 0x30 : error_code_capture */
#define ISO11898_SEGMENT4_0_SHIFT                               (0U)
#define ISO11898_SEGMENT4_0_MASK                                (0x1f<<ISO11898_SEGMENT4_0_SHIFT)
#define ISO11898_DIR                                            (1<<5U)
#define ISO11898_ERR_CODE_SHIFT                                 (6U)
#define ISO11898_ERR_CODE_MASK                                  (0x3<<ISO11898_ERR_CODE_SHIFT)

/* 0x34 : error_warning_limit */
#define ISO11898_ERR_WARNING_LIMIT_SHIFT                        (0U)
#define ISO11898_ERR_WARNING_LIMIT_MASK                         (0xff<<ISO11898_ERR_WARNING_LIMIT_SHIFT)

/* 0x38 : rx_err_count */
#define ISO11898_RX_ERR_CNT_SHIFT                               (0U)
#define ISO11898_RX_ERR_CNT_MASK                                (0xff<<ISO11898_RX_ERR_CNT_SHIFT)

/* 0x3c : tx_err_count */
#define ISO11898_TX_ERR_CNT_SHIFT                               (0U)
#define ISO11898_TX_ERR_CNT_MASK                                (0xff<<ISO11898_TX_ERR_CNT_SHIFT)

/* 0x40 : frame_information */
#define ISO11898_FRAME_INFORMATION_DLC_SHIFT                    (0U)
#define ISO11898_FRAME_INFORMATION_DLC_MASK                     (0xf<<ISO11898_FRAME_INFORMATION_DLC_SHIFT)
#define ISO11898_FRAME_INFORMATION_RTR                          (1<<6U)
#define ISO11898_FRAME_INFORMATION_FF                           (1<<7U)

/* 0x40 : acceptance_code_0 */
#define ISO11898_ACCEPTANCE_CODE_0_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_CODE_0_MASK                         (0xff<<ISO11898_ACCEPTANCE_CODE_0_SHIFT)

/* 0x44 : sff_id1 */
#define ISO11898_SFF_ID1_BIT28_21_SHIFT                         (0U)
#define ISO11898_SFF_ID1_BIT28_21_MASK                          (0xff<<ISO11898_SFF_ID1_BIT28_21_SHIFT)

/* 0x44 : eff_id1 */
#define ISO11898_EFF_ID1_BIT28_21_SHIFT                         (0U)
#define ISO11898_EFF_ID1_BIT28_21_MASK                          (0xff<<ISO11898_EFF_ID1_BIT28_21_SHIFT)

/* 0x44 : acceptance_code_1 */
#define ISO11898_ACCEPTANCE_CODE_1_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_CODE_1_MASK                         (0xff<<ISO11898_ACCEPTANCE_CODE_1_SHIFT)

/* 0x48 : sff_id2 */
#define ISO11898_SFF_ID2_BIT20_18_SHIFT                         (5U)
#define ISO11898_SFF_ID2_BIT20_18_MASK                          (0x7<<ISO11898_SFF_ID2_BIT20_18_SHIFT)

/* 0x48 : eff_id2 */
#define ISO11898_EFF_ID2_BIT20_13_SHIFT                         (0U)
#define ISO11898_EFF_ID2_BIT20_13_MASK                          (0xff<<ISO11898_EFF_ID2_BIT20_13_SHIFT)

/* 0x48 : acceptance_code_2 */
#define ISO11898_ACCEPTANCE_CODE_2_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_CODE_2_MASK                         (0xff<<ISO11898_ACCEPTANCE_CODE_2_SHIFT)

/* 0x4c : sff_data1 */
#define ISO11898_SFF_DATA1_SHIFT                                (0U)
#define ISO11898_SFF_DATA1_MASK                                 (0xff<<ISO11898_SFF_DATA1_SHIFT)

/* 0x4c : eff_id3 */
#define ISO11898_EFF_ID3_BIT12_5_SHIFT                          (0U)
#define ISO11898_EFF_ID3_BIT12_5_MASK                           (0xff<<ISO11898_EFF_ID3_BIT12_5_SHIFT)

/* 0x4c : acceptance_code_3 */
#define ISO11898_ACCEPTANCE_CODE_3_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_CODE_3_MASK                         (0xff<<ISO11898_ACCEPTANCE_CODE_3_SHIFT)

/* 0x50 : sff_data2 */
#define ISO11898_SFF_DATA2_SHIFT                                (0U)
#define ISO11898_SFF_DATA2_MASK                                 (0xff<<ISO11898_SFF_DATA2_SHIFT)

/* 0x50 : eff_id4 */
#define ISO11898_EFF_ID4_BIT4_0_SHIFT                           (3U)
#define ISO11898_EFF_ID4_BIT4_0_MASK                            (0x1f<<ISO11898_EFF_ID4_BIT4_0_SHIFT)

/* 0x50 : acceptance_mask_0 */
#define ISO11898_ACCEPTANCE_MASK_0_SHIFT                        (3U)
#define ISO11898_ACCEPTANCE_MASK_0_MASK                         (0x1f<<ISO11898_ACCEPTANCE_MASK_0_SHIFT)

/* 0x54 : sff_data3 */
#define ISO11898_SFF_DATA3_SHIFT                                (0U)
#define ISO11898_SFF_DATA3_MASK                                 (0xff<<ISO11898_SFF_DATA3_SHIFT)

/* 0x54 : eff_data1 */
#define ISO11898_EFF_DATA1_SHIFT                                (0U)
#define ISO11898_EFF_DATA1_MASK                                 (0xff<<ISO11898_EFF_DATA1_SHIFT)

/* 0x54 : acceptance_mask_1 */
#define ISO11898_ACCEPTANCE_MASK_1_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_MASK_1_MASK                         (0xff<<ISO11898_ACCEPTANCE_MASK_1_SHIFT)

/* 0x58 : sff_data4 */
#define ISO11898_SFF_DATA4_SHIFT                                (0U)
#define ISO11898_SFF_DATA4_MASK                                 (0xff<<ISO11898_SFF_DATA4_SHIFT)

/* 0x58 : eff_data2 */
#define ISO11898_EFF_DATA2_SHIFT                                (0U)
#define ISO11898_EFF_DATA2_MASK                                 (0xff<<ISO11898_EFF_DATA2_SHIFT)

/* 0x58 : acceptance_mask_2 */
#define ISO11898_ACCEPTANCE_MASK_2_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_MASK_2_MASK                         (0xff<<ISO11898_ACCEPTANCE_MASK_2_SHIFT)

/* 0x5c : sff_data5 */
#define ISO11898_SFF_DATA5_SHIFT                                (0U)
#define ISO11898_SFF_DATA5_MASK                                 (0xff<<ISO11898_SFF_DATA5_SHIFT)

/* 0x5c : eff_data3 */
#define ISO11898_EFF_DATA3_SHIFT                                (0U)
#define ISO11898_EFF_DATA3_MASK                                 (0xff<<ISO11898_EFF_DATA3_SHIFT)

/* 0x5c : acceptance_mask_3 */
#define ISO11898_ACCEPTANCE_MASK_3_SHIFT                        (0U)
#define ISO11898_ACCEPTANCE_MASK_3_MASK                         (0xff<<ISO11898_ACCEPTANCE_MASK_3_SHIFT)

/* 0x60 : sff_data6 */
#define ISO11898_SFF_DATA6_SHIFT                                (0U)
#define ISO11898_SFF_DATA6_MASK                                 (0xff<<ISO11898_SFF_DATA6_SHIFT)

/* 0x60 : eff_data4 */
#define ISO11898_ESFF_DATA4_SHIFT                               (0U)
#define ISO11898_ESFF_DATA4_MASK                                (0xff<<ISO11898_ESFF_DATA4_SHIFT)

/* 0x64 : sff_data7 */
#define ISO11898_SFF_DATA7_SHIFT                                (0U)
#define ISO11898_SFF_DATA7_MASK                                 (0xff<<ISO11898_SFF_DATA7_SHIFT)

/* 0x64 : eff_data5 */
#define ISO11898_EFF_DATA5_SHIFT                                (0U)
#define ISO11898_EFF_DATA5_MASK                                 (0xff<<ISO11898_EFF_DATA5_SHIFT)

/* 0x68 : sff_data8 */
#define ISO11898_SFF_DATA8_SHIFT                                (0U)
#define ISO11898_SFF_DATA8_MASK                                 (0xff<<ISO11898_SFF_DATA8_SHIFT)

/* 0x68 : eff_data6 */
#define ISO11898_EFF_DATA6_SHIFT                                (0U)
#define ISO11898_EFF_DATA6_MASK                                 (0xff<<ISO11898_EFF_DATA6_SHIFT)

/* 0x6c : eff_data7 */
#define ISO11898_EFF_DATA7_SHIFT                                (0U)
#define ISO11898_EFF_DATA7_MASK                                 (0xff<<ISO11898_EFF_DATA7_SHIFT)

/* 0x70 : eff_data8 */
#define ISO11898_EFF_DATA8_SHIFT                                (0U)
#define ISO11898_EFF_DATA8_MASK                                 (0xff<<ISO11898_EFF_DATA8_SHIFT)

/* 0x74 : rx_message_count */
#define ISO11898_RX_MESSAGE_CNT_SHIFT                           (0U)
#define ISO11898_RX_MESSAGE_CNT_MASK                            (0xff<<ISO11898_RX_MESSAGE_CNT_SHIFT)

/* 0x7c : clock_divider */
#define ISO11898_CD_SHIFT                                       (0U)
#define ISO11898_CD_MASK                                        (0x7<<ISO11898_CD_SHIFT)
#define ISO11898_CLOCKOFF                                       (1<<3U)
#define ISO11898_READONLY                                       (1<<4U)
#define ISO11898_RXINTEN                                        (1<<5U)
#define ISO11898_CBP                                            (1<<6U)
#define ISO11898_CAN_MODE                                       (1<<7U)


#endif  /* __ISO11898_REG_H__ */
