/***************************************************************************//**
* \file cyhal_triggers_cyw20829.h
*
* \brief
* CYW20829 family HAL triggers header
*
********************************************************************************
* \copyright
* (c) (2016-2023), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
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
*******************************************************************************/

#ifndef _CYHAL_TRIGGERS_CYW20829_H_
#define _CYHAL_TRIGGERS_CYW20829_H_

/**
 * \addtogroup group_hal_impl_triggers_cyw20829 CYW20829
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for cyw20829
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \cond INTERNAL */
/** @brief Name of each input trigger. */
typedef enum
{
    _CYHAL_TRIGGER_CPUSS_ZERO = 0, //!< cpuss.zero
    _CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DATA = 1, //!< adcmic.tr_adcmic_data
    _CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DC = 2, //!< adcmic.tr_adcmic_dc
    _CYHAL_TRIGGER_BTSS_TR_RX_PACKET_SYNC = 3, //!< btss.tr_rx_packet_sync
    _CYHAL_TRIGGER_BTSS_TR_TX_START = 4, //!< btss.tr_tx_start
    _CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0 = 5, //!< canfd[0].tr_dbg_dma_req[0]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO00 = 6, //!< canfd[0].tr_fifo0[0]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO10 = 7, //!< canfd[0].tr_fifo1[0]
    _CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0 = 8, //!< canfd[0].tr_tmp_rtp_out[0]
    _CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0 = 9, //!< cpuss.cti_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1 = 10, //!< cpuss.cti_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0 = 11, //!< cpuss.dw0_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT1 = 12, //!< cpuss.dw0_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT2 = 13, //!< cpuss.dw0_tr_out[2]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT3 = 14, //!< cpuss.dw0_tr_out[3]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT4 = 15, //!< cpuss.dw0_tr_out[4]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT5 = 16, //!< cpuss.dw0_tr_out[5]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT6 = 17, //!< cpuss.dw0_tr_out[6]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT7 = 18, //!< cpuss.dw0_tr_out[7]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT8 = 19, //!< cpuss.dw0_tr_out[8]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT9 = 20, //!< cpuss.dw0_tr_out[9]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT10 = 21, //!< cpuss.dw0_tr_out[10]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT11 = 22, //!< cpuss.dw0_tr_out[11]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT12 = 23, //!< cpuss.dw0_tr_out[12]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT13 = 24, //!< cpuss.dw0_tr_out[13]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT14 = 25, //!< cpuss.dw0_tr_out[14]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT15 = 26, //!< cpuss.dw0_tr_out[15]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0 = 27, //!< ioss.peri_tr_io_input_in[0]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1 = 28, //!< ioss.peri_tr_io_input_in[1]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2 = 29, //!< ioss.peri_tr_io_input_in[2]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3 = 30, //!< ioss.peri_tr_io_input_in[3]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4 = 31, //!< ioss.peri_tr_io_input_in[4]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5 = 32, //!< ioss.peri_tr_io_input_in[5]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6 = 33, //!< ioss.peri_tr_io_input_in[6]
    _CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7 = 34, //!< ioss.peri_tr_io_input_in[7]
    _CYHAL_TRIGGER_PDM_TR_RX_REQ_ALL = 35, //!< pdm.tr_rx_req_all
    _CYHAL_TRIGGER_PDM_TR_RX_REQ0 = 36, //!< pdm.tr_rx_req[0]
    _CYHAL_TRIGGER_PDM_TR_RX_REQ1 = 37, //!< pdm.tr_rx_req[1]
    _CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED = 38, //!< scb[0].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED = 39, //!< scb[2].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB0_TR_RX_REQ = 40, //!< scb[0].tr_rx_req
    _CYHAL_TRIGGER_SCB1_TR_RX_REQ = 41, //!< scb[1].tr_rx_req
    _CYHAL_TRIGGER_SCB2_TR_RX_REQ = 42, //!< scb[2].tr_rx_req
    _CYHAL_TRIGGER_SCB0_TR_TX_REQ = 43, //!< scb[0].tr_tx_req
    _CYHAL_TRIGGER_SCB1_TR_TX_REQ = 44, //!< scb[1].tr_tx_req
    _CYHAL_TRIGGER_SCB2_TR_TX_REQ = 45, //!< scb[2].tr_tx_req
    _CYHAL_TRIGGER_SMIF_TR_RX_REQ = 46, //!< smif.tr_rx_req
    _CYHAL_TRIGGER_SMIF_TR_TX_REQ = 47, //!< smif.tr_tx_req
    _CYHAL_TRIGGER_TCPWM0_TR_OUT00 = 48, //!< tcpwm[0].tr_out0[0]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT01 = 49, //!< tcpwm[0].tr_out0[1]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0256 = 50, //!< tcpwm[0].tr_out0[256]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0257 = 51, //!< tcpwm[0].tr_out0[257]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0258 = 52, //!< tcpwm[0].tr_out0[258]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0259 = 53, //!< tcpwm[0].tr_out0[259]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0260 = 54, //!< tcpwm[0].tr_out0[260]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0261 = 55, //!< tcpwm[0].tr_out0[261]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0262 = 56, //!< tcpwm[0].tr_out0[262]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT10 = 57, //!< tcpwm[0].tr_out1[0]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT11 = 58, //!< tcpwm[0].tr_out1[1]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1256 = 59, //!< tcpwm[0].tr_out1[256]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1257 = 60, //!< tcpwm[0].tr_out1[257]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1258 = 61, //!< tcpwm[0].tr_out1[258]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1259 = 62, //!< tcpwm[0].tr_out1[259]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1260 = 63, //!< tcpwm[0].tr_out1[260]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1261 = 64, //!< tcpwm[0].tr_out1[261]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1262 = 65, //!< tcpwm[0].tr_out1[262]
    _CYHAL_TRIGGER_TDM_TR_RX_REQ0 = 66, //!< tdm.tr_rx_req[0]
    _CYHAL_TRIGGER_TDM_TR_TX_REQ0 = 67, //!< tdm.tr_tx_req[0]
} _cyhal_trigger_source_cyw20829_t;

/** Typedef for internal device family specific trigger source to generic trigger source */
typedef _cyhal_trigger_source_cyw20829_t cyhal_internal_source_t;

/** @brief Get a public source signal type (cyhal_trigger_source_cyw20829_t) given an internal source signal and signal type */
#define _CYHAL_TRIGGER_CREATE_SOURCE(src, type)    ((src) << 1 | (type))
/** @brief Get an internal source signal (_cyhal_trigger_source_cyw20829_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_SIGNAL(src)      ((cyhal_internal_source_t)((src) >> 1))
/** @brief Get the signal type (cyhal_signal_type_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_TYPE(src)        ((cyhal_signal_type_t)((src) & 1))
/** \endcond */

/** @brief Name of each input trigger. */
typedef enum
{
    CYHAL_TRIGGER_CPUSS_ZERO_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.zero
    CYHAL_TRIGGER_CPUSS_ZERO_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_LEVEL), //!< cpuss.zero
    CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DATA = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DATA, CYHAL_SIGNAL_TYPE_LEVEL), //!< adcmic.tr_adcmic_data
    CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DC = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_ADCMIC_TR_ADCMIC_DC, CYHAL_SIGNAL_TYPE_LEVEL), //!< adcmic.tr_adcmic_dc
    CYHAL_TRIGGER_BTSS_TR_RX_PACKET_SYNC = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_BTSS_TR_RX_PACKET_SYNC, CYHAL_SIGNAL_TYPE_EDGE), //!< btss.tr_rx_packet_sync
    CYHAL_TRIGGER_BTSS_TR_TX_START = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_BTSS_TR_TX_START, CYHAL_SIGNAL_TYPE_EDGE), //!< btss.tr_tx_start
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_dbg_dma_req[0]
    CYHAL_TRIGGER_CANFD0_TR_FIFO00 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO00, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo0[0]
    CYHAL_TRIGGER_CANFD0_TR_FIFO10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO10, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo1[0]
    CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[0].tr_tmp_rtp_out[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.cti_tr_out[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.cti_tr_out[1]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[0]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[1]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[2]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[3]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT4 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[4]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT5 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[5]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT6 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT6, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[6]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT7 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT7, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[7]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT8 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT8, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[8]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT9 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT9, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[9]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[10]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT11 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[11]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT12 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT12, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[12]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT13 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT13, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[13]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT14 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT14, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[14]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT15 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT15, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[15]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[0]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[0]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[1]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[1]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[2]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[2]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[3]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[3]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[4]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[4]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[5]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[5]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[6]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[6]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7, CYHAL_SIGNAL_TYPE_EDGE), //!< ioss.peri_tr_io_input_in[7]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7, CYHAL_SIGNAL_TYPE_LEVEL), //!< ioss.peri_tr_io_input_in[7]
    CYHAL_TRIGGER_PDM_TR_RX_REQ_ALL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PDM_TR_RX_REQ_ALL, CYHAL_SIGNAL_TYPE_LEVEL), //!< pdm.tr_rx_req_all
    CYHAL_TRIGGER_PDM_TR_RX_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PDM_TR_RX_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< pdm.tr_rx_req[0]
    CYHAL_TRIGGER_PDM_TR_RX_REQ1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PDM_TR_RX_REQ1, CYHAL_SIGNAL_TYPE_LEVEL), //!< pdm.tr_rx_req[1]
    CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB0_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_rx_req
    CYHAL_TRIGGER_SCB1_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB1_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[1].tr_rx_req
    CYHAL_TRIGGER_SCB2_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_rx_req
    CYHAL_TRIGGER_SCB0_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_tx_req
    CYHAL_TRIGGER_SCB1_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB1_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[1].tr_tx_req
    CYHAL_TRIGGER_SCB2_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_tx_req
    CYHAL_TRIGGER_SMIF_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SMIF_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< smif.tr_rx_req
    CYHAL_TRIGGER_SMIF_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SMIF_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< smif.tr_tx_req
    CYHAL_TRIGGER_TCPWM0_TR_OUT00_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT00, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT00_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT00, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT01_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT01, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT01_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT01, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0256_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0256, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[256]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0256_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0256, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[256]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0257_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0257, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[257]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0257_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0257, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[257]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0258_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0258, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[258]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0258_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0258, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[258]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0259_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0259, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[259]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0259_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0259, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[259]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0260_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0260, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[260]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0260_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0260, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[260]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0261_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0261, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[261]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0261_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0261, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[261]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0262_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0262, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[262]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0262_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0262, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[262]
    CYHAL_TRIGGER_TCPWM0_TR_OUT10_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT10_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT10, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT11_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT11_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT11, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1256_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1256, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[256]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1256_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1256, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[256]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1257_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1257, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[257]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1257_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1257, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[257]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1258_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1258, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[258]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1258_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1258, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[258]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1259_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1259, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[259]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1259_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1259, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[259]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1260_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1260, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[260]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1260_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1260, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[260]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1261_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1261, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[261]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1261_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1261, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[261]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1262_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1262, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[262]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1262_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1262, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[262]
    CYHAL_TRIGGER_TDM_TR_RX_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TDM_TR_RX_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tdm.tr_rx_req[0]
    CYHAL_TRIGGER_TDM_TR_TX_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TDM_TR_TX_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tdm.tr_tx_req[0]
} cyhal_trigger_source_cyw20829_t;

/** Typedef from device family specific trigger source to generic trigger source */
typedef cyhal_trigger_source_cyw20829_t cyhal_source_t;

/** Deprecated defines for signals that can be either level or edge. */
#define CYHAL_TRIGGER_CPUSS_ZERO (CYHAL_TRIGGER_CPUSS_ZERO_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN6_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7 (CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN7_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT00 (CYHAL_TRIGGER_TCPWM0_TR_OUT00_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT01 (CYHAL_TRIGGER_TCPWM0_TR_OUT01_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0256 (CYHAL_TRIGGER_TCPWM0_TR_OUT0256_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0257 (CYHAL_TRIGGER_TCPWM0_TR_OUT0257_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0258 (CYHAL_TRIGGER_TCPWM0_TR_OUT0258_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0259 (CYHAL_TRIGGER_TCPWM0_TR_OUT0259_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0260 (CYHAL_TRIGGER_TCPWM0_TR_OUT0260_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0261 (CYHAL_TRIGGER_TCPWM0_TR_OUT0261_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0262 (CYHAL_TRIGGER_TCPWM0_TR_OUT0262_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT10 (CYHAL_TRIGGER_TCPWM0_TR_OUT10_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT11 (CYHAL_TRIGGER_TCPWM0_TR_OUT11_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1256 (CYHAL_TRIGGER_TCPWM0_TR_OUT1256_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1257 (CYHAL_TRIGGER_TCPWM0_TR_OUT1257_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1258 (CYHAL_TRIGGER_TCPWM0_TR_OUT1258_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1259 (CYHAL_TRIGGER_TCPWM0_TR_OUT1259_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1260 (CYHAL_TRIGGER_TCPWM0_TR_OUT1260_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1261 (CYHAL_TRIGGER_TCPWM0_TR_OUT1261_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1262 (CYHAL_TRIGGER_TCPWM0_TR_OUT1262_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.

/** @brief Name of each output trigger. */
typedef enum
{
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_ACK0 = 0, //!< CAN DW0 triggers (from DW back to CAN) - canfd[0].tr_dbg_dma_ack[0]
    CYHAL_TRIGGER_CANFD0_TR_EVT_SWT_IN0 = 1, //!< CAN TT Sync - canfd[0].tr_evt_swt_in[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_IN0 = 2, //!< CPUSS Debug  multiplexer - cpuss.cti_tr_in[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_IN1 = 3, //!< CPUSS Debug  multiplexer - cpuss.cti_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN0 = 4, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[0]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN1 = 5, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN2 = 6, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[2]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN3 = 7, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[3]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN4 = 8, //!< SCB_CAN0 - cpuss.dw0_tr_in[4]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN5 = 9, //!< SCB_CAN1 - cpuss.dw0_tr_in[5]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN6 = 10, //!< SCB DW0 Triggers - cpuss.dw0_tr_in[6]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN7 = 11, //!< SCB DW0 Triggers - cpuss.dw0_tr_in[7]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN8 = 12, //!< SCB DW0 Triggers - cpuss.dw0_tr_in[8]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN9 = 13, //!< SCB DW0 Triggers - cpuss.dw0_tr_in[9]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN10 = 14, //!< AUDIOSS PDMA1 triggers (I2S & PDM) - cpuss.dw0_tr_in[10]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN11 = 15, //!< AUDIOSS PDMA1 triggers (I2S & PDM) - cpuss.dw0_tr_in[11]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN12 = 16, //!< AUDIOSS PDMA1 triggers (I2S & PDM) - cpuss.dw0_tr_in[12]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN13 = 17, //!< AUDIOSS PDMA1 triggers (I2S & PDM) - cpuss.dw0_tr_in[13]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN14 = 18, //!< AUDIOSS PDMA1 triggers (I2S & PDM) - cpuss.dw0_tr_in[14]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN15 = 19, //!< CAN to PDMA0 direct connect - cpuss.dw0_tr_in[15]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_OUTPUT_OUT0 = 20, //!< HSIOM trigger multiplexer - ioss.peri_tr_io_output_out[0]
    CYHAL_TRIGGER_IOSS_PERI_TR_IO_OUTPUT_OUT1 = 21, //!< HSIOM trigger multiplexer - ioss.peri_tr_io_output_out[1]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER0 = 22, //!< To LIN0 - lin[0].tr_cmd_tx_header[0]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER1 = 23, //!< To LIN0 - lin[0].tr_cmd_tx_header[1]
    CYHAL_TRIGGER_PDM_TR_ACTIVATE0 = 24, //!< TCPWM and PDM trigger multiplexer - pdm.tr_activate[0]
    CYHAL_TRIGGER_PDM_TR_ACTIVATE1 = 25, //!< TCPWM and PDM trigger multiplexer - pdm.tr_activate[1]
    CYHAL_TRIGGER_PDM_TR_DBG_FREEZE = 26, //!< PERI Freeze trigger multiplexer - pdm.tr_dbg_freeze
    CYHAL_TRIGGER_PERI_TR_DBG_FREEZE = 27, //!< PERI Freeze trigger multiplexer - peri.tr_dbg_freeze
    CYHAL_TRIGGER_SRSS_TR_DEBUG_FREEZE_MCWDT0 = 28, //!< CPUSS Debug  multiplexer - srss.tr_debug_freeze_mcwdt[0]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN0 = 29, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[0]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN1 = 30, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[1]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN2 = 31, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[2]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN3 = 32, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[3]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN4 = 33, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[4]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN5 = 34, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[5]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN6 = 35, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[6]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN7 = 36, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[7]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN8 = 37, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[8]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN9 = 38, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[9]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN10 = 39, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[10]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN11 = 40, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[11]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN12 = 41, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[12]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN13 = 42, //!< TCPWM0 trigger multiplexer - tcpwm[0].tr_all_cnt_in[13]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN14 = 43, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[14]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN15 = 44, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[15]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN16 = 45, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[16]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN17 = 46, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[17]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN18 = 47, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[18]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN19 = 48, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[19]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN20 = 49, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[20]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN21 = 50, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[21]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN22 = 51, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[22]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN23 = 52, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[23]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN24 = 53, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[24]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN25 = 54, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[25]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN26 = 55, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[26]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN27 = 56, //!< TCPWM1 trigger multiplexer - tcpwm[0].tr_all_cnt_in[27]
    CYHAL_TRIGGER_TCPWM0_TR_DEBUG_FREEZE = 57, //!< PERI Freeze trigger multiplexer - tcpwm[0].tr_debug_freeze
    CYHAL_TRIGGER_TDM_TR_DBG_FREEZE = 58, //!< PERI Freeze trigger multiplexer - tdm.tr_dbg_freeze
} cyhal_trigger_dest_cyw20829_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_cyw20829_t cyhal_dest_t;

/** \cond INTERNAL */
/** Table of number of inputs to each mux. */
extern const uint16_t cyhal_sources_per_mux[15];

/** Table indicating whether mux is 1to1. */
extern const bool cyhal_is_mux_1to1[15];

/** Table pointing to each mux source table. The index of each source in the table is its mux input index. */
extern const _cyhal_trigger_source_cyw20829_t* cyhal_mux_to_sources [15];

/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[59];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[59];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_cyw20829 */
#endif /* _CYHAL_TRIGGERS_CYW20829_H_ */


/* [] END OF FILE */
