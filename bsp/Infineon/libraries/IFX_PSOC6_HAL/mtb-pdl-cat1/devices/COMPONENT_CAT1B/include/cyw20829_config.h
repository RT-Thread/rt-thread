/***************************************************************************//**
* \file cyw20829_config.h
*
* \brief
* CYW20829 device configuration header
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
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

#ifndef _CYW20829_CONFIG_H_
#define _CYW20829_CONFIG_H_

/* Clock Connections */
typedef enum
{
    PCLK_CPUSS_CLOCK_TRACE_IN_POS_EN = 0x0000u, /* cpuss.clock_trace_in_pos_en */
    PCLK_SCB0_CLOCK_SCB_EN          = 0x0100u,  /* scb[0].clock_scb_en */
    PCLK_SCB1_CLOCK_SCB_EN          = 0x0101u,  /* scb[1].clock_scb_en */
    PCLK_SCB2_CLOCK_SCB_EN          = 0x0102u,  /* scb[2].clock_scb_en */
    PCLK_TCPWM0_CLOCK_COUNTER_EN0   = 0x0103u,  /* tcpwm[0].clock_counter_en[0] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN1   = 0x0104u,  /* tcpwm[0].clock_counter_en[1] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN256 = 0x0105u,  /* tcpwm[0].clock_counter_en[256] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN257 = 0x0106u,  /* tcpwm[0].clock_counter_en[257] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN258 = 0x0107u,  /* tcpwm[0].clock_counter_en[258] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN259 = 0x0108u,  /* tcpwm[0].clock_counter_en[259] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN260 = 0x0109u,  /* tcpwm[0].clock_counter_en[260] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN261 = 0x010Au,  /* tcpwm[0].clock_counter_en[261] */
    PCLK_TCPWM0_CLOCK_COUNTER_EN262 = 0x010Bu,  /* tcpwm[0].clock_counter_en[262] */
    PCLK_LIN0_CLOCK_CH_EN0          = 0x010Cu,  /* lin[0].clock_ch_en[0] */
    PCLK_LIN0_CLOCK_CH_EN1          = 0x010Du,  /* lin[0].clock_ch_en[1] */
    PCLK_CANFD0_CLOCK_CAN_EN0       = 0x010Eu,  /* canfd[0].clock_can_en[0] */
    PCLK_IOSS_CLOCK_SMARTIO_PCLK_POS_EN3 = 0x010Fu, /* ioss.clock_smartio_pclk_pos_en[3] */
    PCLK_SMIF_CLK_MEM               = 0x0200u,  /* smif.clk_mem */
    PCLK_SMIF_CLK_FAST              = 0x0201u,  /* smif.clk_fast */
    PCLK_SMIF_CLK_SLOW              = 0x0202u,  /* smif.clk_slow */
    PCLK_BTSS_CLK_CPUSS_EXP         = 0x0203u,  /* btss.clk_cpuss_exp */
    PCLK_BTSS_CLK_PERI              = 0x0204u,  /* btss.clk_peri */
    PCLK_CRYPTO_CLK_HF              = 0x0205u,  /* crypto.clk_hf */
    PCLK_PDM0_CLK_IF_SRSS           = 0x0300u,  /* pdm[0].clk_if_srss */
    PCLK_TDM0_CLK_IF_SRSS0          = 0x0301u,  /* tdm[0].clk_if_srss[0] */
    PCLK_ADCMIC_CLK_HF              = 0x0500u,  /* adcmic.clk_hf */
    PCLK_SMIF_CLK_IF                = 0x0600u,  /* smif.clk_if */
    PCLK_IOSS_CLK_HF                = 0x0601u   /* ioss.clk_hf */
} en_clk_dst_t;

/* Trigger Group */
/* This section contains the enums related to the Trigger multiplexer (TrigMux) driver.
* Refer to the Cypress Peripheral Driver Library Documentation, section Trigger multiplexer (TrigMux) -> Enumerated Types for details.
*/
/* Trigger Group Inputs */
/* Trigger Input Group 0 - P-DMA0 Request Assignments */
typedef enum
{
    TRIG_IN_MUX_0_PDMA0_TR_OUT0     = 0x00000001u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT1     = 0x00000002u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT2     = 0x00000003u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT3     = 0x00000004u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_0_TCPWM0_TR_OUT00   = 0x00000005u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_0_TCPWM0_TR_OUT10   = 0x00000006u, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_0_TCPWM0_TR_OUT01   = 0x00000007u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_0_TCPWM0_TR_OUT11   = 0x00000008u, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT0     = 0x00000009u, /* ioss.peri_tr_io_input_in[0] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT1     = 0x0000000Au, /* ioss.peri_tr_io_input_in[1] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT2     = 0x0000000Bu, /* ioss.peri_tr_io_input_in[2] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT3     = 0x0000000Cu, /* ioss.peri_tr_io_input_in[3] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT4     = 0x0000000Du, /* ioss.peri_tr_io_input_in[4] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT5     = 0x0000000Eu, /* ioss.peri_tr_io_input_in[5] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT6     = 0x0000000Fu, /* ioss.peri_tr_io_input_in[6] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT7     = 0x00000010u, /* ioss.peri_tr_io_input_in[7] */
    TRIG_IN_MUX_0_CTI_TR_OUT0       = 0x00000011u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_0_CTI_TR_OUT1       = 0x00000012u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_0_ADCMIC_DC_DONE    = 0x00000013u, /* adcmic.tr_adcmic_dc */
    TRIG_IN_MUX_0_ADCMIC_DATA_AVAIL = 0x00000014u, /* adcmic.tr_adcmic_data */
    TRIG_IN_MUX_0_I2S_TDM_TX0       = 0x00000015u, /* tdm.tr_tx_req[0] */
    TRIG_IN_MUX_0_I2S_TDM_RX0       = 0x00000016u, /* tdm.tr_rx_req[0] */
    TRIG_IN_MUX_0_PDM_RX0           = 0x00000017u, /* pdm.tr_rx_req[0] */
    TRIG_IN_MUX_0_PDM_RX1           = 0x00000018u /* pdm.tr_rx_req[1] */
} en_trig_input_pdma0_tr_t;

/* Trigger Input Group 1 - TCPWM0 trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_1_PDMA0_TR_OUT0     = 0x00000101u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT1     = 0x00000102u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT2     = 0x00000103u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT3     = 0x00000104u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT4     = 0x00000105u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT5     = 0x00000106u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT6     = 0x00000107u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_1_PDMA0_TR_OUT7     = 0x00000108u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT00   = 0x00000109u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT10   = 0x0000010Au, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT01   = 0x0000010Bu, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT11   = 0x0000010Cu, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0256 = 0x0000010Du, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1256 = 0x0000010Eu, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0257 = 0x0000010Fu, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1257 = 0x00000110u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0258 = 0x00000111u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1258 = 0x00000112u, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0259 = 0x00000113u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1259 = 0x00000114u, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0260 = 0x00000115u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1260 = 0x00000116u, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0261 = 0x00000117u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1261 = 0x00000118u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT0262 = 0x00000119u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_1_TCPWM0_TR_OUT1262 = 0x0000011Au, /* tcpwm[0].tr_out1[262] */
    TRIG_IN_MUX_1_SCB_I2C_SCL0      = 0x0000011Bu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_1_SCB_TX0           = 0x0000011Cu, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_1_SCB_RX0           = 0x0000011Du, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_1_TIE_LOW           = 0x0000011Eu, /* cpuss.zero */
    TRIG_IN_MUX_1_SCB_TX1           = 0x0000011Fu, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_1_SCB_RX1           = 0x00000120u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_1_SCB_I2C_SCL2      = 0x00000121u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_1_SCB_TX2           = 0x00000122u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_1_SCB_RX2           = 0x00000123u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_1_SMIF_TX           = 0x00000124u, /* smif.tr_tx_req */
    TRIG_IN_MUX_1_SMIF_RX           = 0x00000125u, /* smif.tr_rx_req */
    TRIG_IN_MUX_1_I2S_TDM_TX0       = 0x00000126u, /* tdm.tr_tx_req[0] */
    TRIG_IN_MUX_1_I2S_TDM_RX0       = 0x00000127u, /* tdm.tr_rx_req[0] */
    TRIG_IN_MUX_1_PDM_RX0           = 0x00000128u, /* pdm.tr_rx_req[0] */
    TRIG_IN_MUX_1_PDM_RX1           = 0x00000129u, /* pdm.tr_rx_req[1] */
    TRIG_IN_MUX_1_PDM_RX_REQ_ALL    = 0x0000012Au, /* pdm.tr_rx_req_all */
    TRIG_IN_MUX_1_HSIOM_TR_OUT0     = 0x0000012Bu, /* ioss.peri_tr_io_input_in[0] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT1     = 0x0000012Cu, /* ioss.peri_tr_io_input_in[1] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT2     = 0x0000012Du, /* ioss.peri_tr_io_input_in[2] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT3     = 0x0000012Eu, /* ioss.peri_tr_io_input_in[3] */
    TRIG_IN_MUX_1_CTI_TR_OUT0       = 0x0000012Fu, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_1_CTI_TR_OUT1       = 0x00000130u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_1_ADCMIC_DC_DONE    = 0x00000131u, /* adcmic.tr_adcmic_dc */
    TRIG_IN_MUX_1_ADCMIC_DATA_AVAIL = 0x00000132u, /* adcmic.tr_adcmic_data */
    TRIG_IN_MUX_1_CANFD_TT_TR_OUT0  = 0x00000133u, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_1_BTSS_TR_TX        = 0x00000134u, /* btss.tr_tx_start */
    TRIG_IN_MUX_1_BTSS_TR_RX        = 0x00000135u /* btss.tr_rx_packet_sync */
} en_trig_input_tcpwm0_t;

/* Trigger Input Group 2 - TCPWM1 trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_2_PDMA0_TR_OUT8     = 0x00000201u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT9     = 0x00000202u, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT10    = 0x00000203u, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT11    = 0x00000204u, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT12    = 0x00000205u, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT13    = 0x00000206u, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT14    = 0x00000207u, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT15    = 0x00000208u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT00   = 0x00000209u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT10   = 0x0000020Au, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT01   = 0x0000020Bu, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT11   = 0x0000020Cu, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0256 = 0x0000020Du, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1256 = 0x0000020Eu, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0257 = 0x0000020Fu, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1257 = 0x00000210u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0258 = 0x00000211u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1258 = 0x00000212u, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0259 = 0x00000213u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1259 = 0x00000214u, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0260 = 0x00000215u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1260 = 0x00000216u, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0261 = 0x00000217u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1261 = 0x00000218u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT0262 = 0x00000219u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_2_TCPWM0_TR_OUT1262 = 0x0000021Au, /* tcpwm[0].tr_out1[262] */
    TRIG_IN_MUX_2_SCB_I2C_SCL0      = 0x0000021Bu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX0           = 0x0000021Cu, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX0           = 0x0000021Du, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_2_TIE_LOW           = 0x0000021Eu, /* cpuss.zero */
    TRIG_IN_MUX_2_SCB_TX1           = 0x0000021Fu, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX1           = 0x00000220u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL2      = 0x00000221u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX2           = 0x00000222u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX2           = 0x00000223u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_2_SMIF_TX           = 0x00000224u, /* smif.tr_tx_req */
    TRIG_IN_MUX_2_SMIF_RX           = 0x00000225u, /* smif.tr_rx_req */
    TRIG_IN_MUX_2_I2S_TDM_TX0       = 0x00000226u, /* tdm.tr_tx_req[0] */
    TRIG_IN_MUX_2_I2S_TDM_RX0       = 0x00000227u, /* tdm.tr_rx_req[0] */
    TRIG_IN_MUX_2_PDM_RX0           = 0x00000228u, /* pdm.tr_rx_req[0] */
    TRIG_IN_MUX_2_PDM_RX1           = 0x00000229u, /* pdm.tr_rx_req[1] */
    TRIG_IN_MUX_2_PDM_RX_REQ_ALL    = 0x0000022Au, /* pdm.tr_rx_req_all */
    TRIG_IN_MUX_2_HSIOM_TR_OUT4     = 0x0000022Bu, /* ioss.peri_tr_io_input_in[4] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT5     = 0x0000022Cu, /* ioss.peri_tr_io_input_in[5] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT6     = 0x0000022Du, /* ioss.peri_tr_io_input_in[6] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT7     = 0x0000022Eu, /* ioss.peri_tr_io_input_in[7] */
    TRIG_IN_MUX_2_CTI_TR_OUT0       = 0x0000022Fu, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_2_CTI_TR_OUT1       = 0x00000230u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_2_ADCMIC_DC_DONE    = 0x00000231u, /* adcmic.tr_adcmic_dc */
    TRIG_IN_MUX_2_ADCMIC_DATA_AVAIL = 0x00000232u, /* adcmic.tr_adcmic_data */
    TRIG_IN_MUX_2_CANFD_TT_TR_OUT0  = 0x00000233u, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_2_BTSS_TR_TX        = 0x00000234u, /* btss.tr_tx_start */
    TRIG_IN_MUX_2_BTSS_TR_RX        = 0x00000235u /* btss.tr_rx_packet_sync */
} en_trig_input_tcpwm1_t;

/* Trigger Input Group 3 - HSIOM trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_3_PDMA0_TR_OUT0     = 0x00000301u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT1     = 0x00000302u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT2     = 0x00000303u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT3     = 0x00000304u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT4     = 0x00000305u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT5     = 0x00000306u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT6     = 0x00000307u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_3_PDMA0_TR_OUT7     = 0x00000308u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT00   = 0x00000309u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT10   = 0x0000030Au, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT01   = 0x0000030Bu, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT11   = 0x0000030Cu, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0256 = 0x0000030Du, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1256 = 0x0000030Eu, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0257 = 0x0000030Fu, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1257 = 0x00000310u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0258 = 0x00000311u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1258 = 0x00000312u, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0259 = 0x00000313u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1259 = 0x00000314u, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0260 = 0x00000315u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1260 = 0x00000316u, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0261 = 0x00000317u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1261 = 0x00000318u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT0262 = 0x00000319u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_3_TCPWM0_TR_OUT1262 = 0x0000031Au, /* tcpwm[0].tr_out1[262] */
    TRIG_IN_MUX_3_SCB_I2C_SCL0      = 0x0000031Bu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX0           = 0x0000031Cu, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX0           = 0x0000031Du, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_3_TIE_LOW           = 0x0000031Eu, /* cpuss.zero */
    TRIG_IN_MUX_3_SCB_TX1           = 0x0000031Fu, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX1           = 0x00000320u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL2      = 0x00000321u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX2           = 0x00000322u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX2           = 0x00000323u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_3_I2S_TDM_TX0       = 0x00000324u, /* tdm.tr_tx_req[0] */
    TRIG_IN_MUX_3_I2S_TDM_RX0       = 0x00000325u, /* tdm.tr_rx_req[0] */
    TRIG_IN_MUX_3_PDM_RX0           = 0x00000326u, /* pdm.tr_rx_req[0] */
    TRIG_IN_MUX_3_PDM_RX1           = 0x00000327u, /* pdm.tr_rx_req[1] */
    TRIG_IN_MUX_3_PDM_RX_REQ_ALL    = 0x00000328u, /* pdm.tr_rx_req_all */
    TRIG_IN_MUX_3_CTI_TR_OUT0       = 0x00000329u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_3_CTI_TR_OUT1       = 0x0000032Au, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_3_ADCMIC_DC_DONE    = 0x0000032Bu, /* adcmic.tr_adcmic_dc */
    TRIG_IN_MUX_3_ADCMIC_DATA_AVAIL = 0x0000032Cu, /* adcmic.tr_adcmic_data */
    TRIG_IN_MUX_3_CANFD_TT_TR_OUT0  = 0x0000032Du /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_hsiom_t;

/* Trigger Input Group 4 - CPUSS Debug  multiplexer */
typedef enum
{
    TRIG_IN_MUX_4_PDMA0_TR_OUT0     = 0x00000401u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT1     = 0x00000402u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT2     = 0x00000403u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT3     = 0x00000404u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT4     = 0x00000405u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT5     = 0x00000406u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT6     = 0x00000407u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT7     = 0x00000408u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT8     = 0x00000409u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT9     = 0x0000040Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT10    = 0x0000040Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT11    = 0x0000040Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT12    = 0x0000040Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT13    = 0x0000040Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT14    = 0x0000040Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT15    = 0x00000410u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT00   = 0x00000411u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT10   = 0x00000412u, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT01   = 0x00000413u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT11   = 0x00000414u, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0256 = 0x00000415u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1256 = 0x00000416u, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0257 = 0x00000417u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1257 = 0x00000418u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0258 = 0x00000419u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1258 = 0x0000041Au, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0259 = 0x0000041Bu, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1259 = 0x0000041Cu, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0260 = 0x0000041Du, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1260 = 0x0000041Eu, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0261 = 0x0000041Fu, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1261 = 0x00000420u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT0262 = 0x00000421u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_4_TCPWM0_TR_OUT1262 = 0x00000422u, /* tcpwm[0].tr_out1[262] */
    TRIG_IN_MUX_4_SCB_I2C_SCL0      = 0x00000423u, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX0           = 0x00000424u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX0           = 0x00000425u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_4_TIE_LOW           = 0x00000426u, /* cpuss.zero */
    TRIG_IN_MUX_4_SCB_TX1           = 0x00000427u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX1           = 0x00000428u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL2      = 0x00000429u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX2           = 0x0000042Au, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX2           = 0x0000042Bu, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_4_SMIF_TX           = 0x0000042Cu, /* smif.tr_tx_req */
    TRIG_IN_MUX_4_SMIF_RX           = 0x0000042Du, /* smif.tr_rx_req */
    TRIG_IN_MUX_4_I2S_TDM_TX0       = 0x0000042Eu, /* tdm.tr_tx_req[0] */
    TRIG_IN_MUX_4_I2S_TDM_RX0       = 0x0000042Fu, /* tdm.tr_rx_req[0] */
    TRIG_IN_MUX_4_PDM_RX0           = 0x00000430u, /* pdm.tr_rx_req[0] */
    TRIG_IN_MUX_4_PDM_RX1           = 0x00000431u, /* pdm.tr_rx_req[1] */
    TRIG_IN_MUX_4_PDM_RX_REQ_ALL    = 0x00000432u, /* pdm.tr_rx_req_all */
    TRIG_IN_MUX_4_HSIOM_TR_OUT0     = 0x00000433u, /* ioss.peri_tr_io_input_in[0] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT1     = 0x00000434u, /* ioss.peri_tr_io_input_in[1] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT2     = 0x00000435u, /* ioss.peri_tr_io_input_in[2] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT3     = 0x00000436u, /* ioss.peri_tr_io_input_in[3] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT4     = 0x00000437u, /* ioss.peri_tr_io_input_in[4] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT5     = 0x00000438u, /* ioss.peri_tr_io_input_in[5] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT6     = 0x00000439u, /* ioss.peri_tr_io_input_in[6] */
    TRIG_IN_MUX_4_HSIOM_TR_OUT7     = 0x0000043Au, /* ioss.peri_tr_io_input_in[7] */
    TRIG_IN_MUX_4_CTI_TR_OUT0       = 0x0000043Bu, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_4_CTI_TR_OUT1       = 0x0000043Cu, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_4_ADCMIC_DC_DONE    = 0x0000043Du, /* adcmic.tr_adcmic_dc */
    TRIG_IN_MUX_4_ADCMIC_DATA_AVAIL = 0x0000043Eu, /* adcmic.tr_adcmic_data */
    TRIG_IN_MUX_4_CANFD_TT_TR_OUT0  = 0x0000043Fu /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_cpuss_cti_t;

/* Trigger Input Group 5 - PERI Freeze trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_5_CTI_TR_OUT0       = 0x00000501u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_5_CTI_TR_OUT1       = 0x00000502u /* cpuss.cti_tr_out[1] */
} en_trig_input_peri_freeze_t;

/* Trigger Input Group 6 - TCPWM and PDM trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_6_TCPWM0_TR_OUT00   = 0x00000601u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT10   = 0x00000602u, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT01   = 0x00000603u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT11   = 0x00000604u, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0256 = 0x00000605u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1256 = 0x00000606u, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0257 = 0x00000607u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1257 = 0x00000608u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0258 = 0x00000609u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1258 = 0x0000060Au, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0259 = 0x0000060Bu, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1259 = 0x0000060Cu, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0260 = 0x0000060Du, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1260 = 0x0000060Eu, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0261 = 0x0000060Fu, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1261 = 0x00000610u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT0262 = 0x00000611u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_6_TCPWM0_TR_OUT1262 = 0x00000612u /* tcpwm[0].tr_out1[262] */
} en_trig_input_tcpwm_pdm_t;

/* Trigger Input Group 7 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_IN_MUX_7_CAN_TT_TR_OUT0    = 0x00000701u /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_cantt_t;

/* Trigger Input Group 8 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_IN_MUX_8_SCB_TX0           = 0x00000801u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_8_CAN_DBG0          = 0x00000802u /* canfd[0].tr_dbg_dma_req[0] */
} en_trig_input_scb_can0_t;

/* Trigger Input Group 9 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_IN_MUX_9_SCB_RX0           = 0x00000901u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_9_CAN_FIFO0         = 0x00000902u /* canfd[0].tr_fifo0[0] */
} en_trig_input_scb_can1_t;

/* Trigger Group Outputs */
/* Trigger Output Group 0 - P-DMA0 Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_0_PDMA0_TR_IN0     = 0x40000000u, /* cpuss.dw0_tr_in[0] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN1     = 0x40000001u, /* cpuss.dw0_tr_in[1] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN2     = 0x40000002u, /* cpuss.dw0_tr_in[2] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN3     = 0x40000003u /* cpuss.dw0_tr_in[3] */
} en_trig_output_pdma0_tr_t;

/* Trigger Output Group 1 - TCPWM0 trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_1_TCPWM0_TR_IN0    = 0x40000100u, /* tcpwm[0].tr_all_cnt_in[0] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN1    = 0x40000101u, /* tcpwm[0].tr_all_cnt_in[1] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN2    = 0x40000102u, /* tcpwm[0].tr_all_cnt_in[2] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN3    = 0x40000103u, /* tcpwm[0].tr_all_cnt_in[3] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN4    = 0x40000104u, /* tcpwm[0].tr_all_cnt_in[4] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN5    = 0x40000105u, /* tcpwm[0].tr_all_cnt_in[5] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN6    = 0x40000106u, /* tcpwm[0].tr_all_cnt_in[6] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN7    = 0x40000107u, /* tcpwm[0].tr_all_cnt_in[7] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN8    = 0x40000108u, /* tcpwm[0].tr_all_cnt_in[8] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN9    = 0x40000109u, /* tcpwm[0].tr_all_cnt_in[9] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN10   = 0x4000010Au, /* tcpwm[0].tr_all_cnt_in[10] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN11   = 0x4000010Bu, /* tcpwm[0].tr_all_cnt_in[11] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN12   = 0x4000010Cu, /* tcpwm[0].tr_all_cnt_in[12] */
    TRIG_OUT_MUX_1_TCPWM0_TR_IN13   = 0x4000010Du /* tcpwm[0].tr_all_cnt_in[13] */
} en_trig_output_tcpwm0_t;

/* Trigger Output Group 2 - TCPWM1 trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_2_TCPWM0_TR_IN14   = 0x40000200u, /* tcpwm[0].tr_all_cnt_in[14] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN15   = 0x40000201u, /* tcpwm[0].tr_all_cnt_in[15] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN16   = 0x40000202u, /* tcpwm[0].tr_all_cnt_in[16] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN17   = 0x40000203u, /* tcpwm[0].tr_all_cnt_in[17] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN18   = 0x40000204u, /* tcpwm[0].tr_all_cnt_in[18] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN19   = 0x40000205u, /* tcpwm[0].tr_all_cnt_in[19] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN20   = 0x40000206u, /* tcpwm[0].tr_all_cnt_in[20] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN21   = 0x40000207u, /* tcpwm[0].tr_all_cnt_in[21] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN22   = 0x40000208u, /* tcpwm[0].tr_all_cnt_in[22] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN23   = 0x40000209u, /* tcpwm[0].tr_all_cnt_in[23] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN24   = 0x4000020Au, /* tcpwm[0].tr_all_cnt_in[24] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN25   = 0x4000020Bu, /* tcpwm[0].tr_all_cnt_in[25] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN26   = 0x4000020Cu, /* tcpwm[0].tr_all_cnt_in[26] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN27   = 0x4000020Du /* tcpwm[0].tr_all_cnt_in[27] */
} en_trig_output_tcpwm1_t;

/* Trigger Output Group 3 - HSIOM trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_3_HSIOM_TR_IO_OUTPUT0 = 0x40000300u, /* ioss.peri_tr_io_output_out[0] */
    TRIG_OUT_MUX_3_HSIOM_TR_IO_OUTPUT1 = 0x40000301u /* ioss.peri_tr_io_output_out[1] */
} en_trig_output_hsiom_t;

/* Trigger Output Group 4 - CPUSS Debug  multiplexer */
typedef enum
{
    TRIG_OUT_MUX_4_CPUSS_CTI_TR_IN0 = 0x40000400u, /* cpuss.cti_tr_in[0] */
    TRIG_OUT_MUX_4_CPUSS_CTI_TR_IN1 = 0x40000401u, /* cpuss.cti_tr_in[1] */
    TRIG_OUT_MUX_4_SRSS_MCWDT_DEBUG_FREEZE_TR_IN0 = 0x40000403u /* srss.tr_debug_freeze_mcwdt[0] */
} en_trig_output_cpuss_cti_t;

/* Trigger Output Group 5 - PERI Freeze trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_5_PERI_DEBUG_FREEZE_TR_IN = 0x40000500u, /* peri.tr_dbg_freeze */
    TRIG_OUT_MUX_5_PDM_DEBUG_FREEZE_TR_IN = 0x40000501u, /* pdm.tr_dbg_freeze */
    TRIG_OUT_MUX_5_TDM_DEBUG_FREEZE_TR_IN = 0x40000502u, /* tdm.tr_dbg_freeze */
    TRIG_OUT_MUX_5_TCPWM_DEBUG_FREEZE_TR_IN = 0x40000503u /* tcpwm[0].tr_debug_freeze */
} en_trig_output_peri_freeze_t;

/* Trigger Output Group 6 - TCPWM and PDM trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_6_PDM_TR_ACTIVATE0 = 0x40000600u, /* pdm.tr_activate[0] */
    TRIG_OUT_MUX_6_PDM_TR_ACTIVATE1 = 0x40000601u /* pdm.tr_activate[1] */
} en_trig_output_tcpwm_pdm_t;

/* Trigger Output Group 7 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_OUT_MUX_7_CAN_TT_TR_IN0    = 0x40000700u /* canfd[0].tr_evt_swt_in[0] */
} en_trig_output_cantt_t;

/* Trigger Output Group 8 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_OUT_MUX_8_PDMA0_TR_IN4     = 0x40000800u /* cpuss.dw0_tr_in[4] */
} en_trig_output_scb_can0_t;

/* Trigger Output Group 9 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_OUT_MUX_9_PDMA0_TR_IN5     = 0x40000900u /* cpuss.dw0_tr_in[5] */
} en_trig_output_scb_can1_t;

/* Trigger Output Group 0 - SCB PDMA0 Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_0_SCB1_TX_TO_PDMA0_TR_IN6 = 0x40001000u, /* From scb[1].tr_tx_req to cpuss.dw0_tr_in[6] */
    TRIG_OUT_1TO1_0_SCB1_RX_TO_PDMA0_TR_IN7 = 0x40001001u, /* From scb[1].tr_rx_req to cpuss.dw0_tr_in[7] */
    TRIG_OUT_1TO1_0_SCB2_TX_TO_PDMA1_TR_IN8 = 0x40001002u, /* From scb[2].tr_tx_req to cpuss.dw0_tr_in[8] */
    TRIG_OUT_1TO1_0_SCB2_RX_TO_PDMA1_TR_IN9 = 0x40001003u /* From scb[2].tr_rx_req to cpuss.dw0_tr_in[9] */
} en_trig_output_1to1_scb_pdma0_tr_t;

/* Trigger Output Group 1 - I2S and PDM PDMA triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_1_I2S0_TX_TO_PDMA0_TR_IN10 = 0x40001100u, /* From tdm.tr_tx_req[0] to cpuss.dw0_tr_in[10] */
    TRIG_OUT_1TO1_1_I2S0_RX_TO_PDMA0_TR_IN11 = 0x40001101u, /* From tdm.tr_rx_req[0] to cpuss.dw0_tr_in[11] */
    TRIG_OUT_1TO1_1_PDM0_RX_TO_PDMA0_TR_IN12 = 0x40001102u, /* From pdm.tr_rx_req[0] to cpuss.dw0_tr_in[12] */
    TRIG_OUT_1TO1_1_PDM0_RX_TO_PDMA0_TR_IN13 = 0x40001103u, /* From pdm.tr_rx_req[1] to cpuss.dw0_tr_in[13] */
    TRIG_OUT_1TO1_1_PDM0_RX_ALL_TO_PDMA0_TR_IN14 = 0x40001104u /* From pdm.tr_rx_req_all to cpuss.dw0_tr_in[14] */
} en_trig_output_1to1_audioss_pdma1_tr_t;

/* Trigger Output Group 2 - CAN to PDMA0 direct connect (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_2_CAN_FIFO1_TO_PDMA0_TR_IN15 = 0x40001200u /* From canfd[0].tr_fifo1[0] to cpuss.dw0_tr_in[15] */
} en_trig_output_1to1_can_to_pdma0_t;

/* Trigger Output Group 3 - Acknowledge dma request triggers from DW0 to CAN (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_3_PDMA0_TR_OUT0_ACK_TO_CAN_0 = 0x40001300u /* From cpuss.dw0_tr_out[8] to canfd[0].tr_dbg_dma_ack[0] */
} en_trig_output_1to1_can0_dw_ack_t;

/* Trigger Output Group 4 - Dedicated triggers to LIN[0] (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_4_PDMA0_TR_OUT0_ACK_TO_LIN = 0x40001400u, /* From cpuss.dw0_tr_out[9] to lin[0].tr_cmd_tx_header[0] */
    TRIG_OUT_1TO1_4_PDMA0_TR_OUT1_ACK_TO_LIN = 0x40001401u /* From cpuss.dw0_tr_out[10] to lin[0].tr_cmd_tx_header[1] */
} en_trig_output_1to1_to_lin0_t;

/* Level or edge detection setting for a trigger mux */
typedef enum
{
    /* The trigger is a simple level output */
    TRIGGER_TYPE_LEVEL = 0u,
    /* The trigger is synchronized to the consumer blocks clock
       and a two cycle pulse is generated on this clock */
    TRIGGER_TYPE_EDGE = 1u
} en_trig_type_t;

/* Trigger Type Defines */
/* ADCMIC Trigger Types */
#define TRIGGER_TYPE_ADCMIC_TR_ADCMIC_DATA      TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_ADCMIC_TR_ADCMIC_DC        TRIGGER_TYPE_LEVEL
/* BTSS Trigger Types */
#define TRIGGER_TYPE_BTSS_TR_RX_PACKET_SYNC     TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_BTSS_TR_TX_START           TRIGGER_TYPE_EDGE
/* CANFD Trigger Types */
#define TRIGGER_TYPE_CANFD_TR_DBG_DMA_ACK       TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CANFD_TR_DBG_DMA_REQ       TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CANFD_TR_EVT_SWT_IN        TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CANFD_TR_FIFO0             TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CANFD_TR_FIFO1             TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CANFD_TR_TMP_RTP_OUT       TRIGGER_TYPE_EDGE
/* CPUSS Trigger Types */
#define TRIGGER_TYPE_CPUSS_CTI_TR_IN            TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_CTI_TR_OUT           TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW0_TR_IN__LEVEL     TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CPUSS_DW0_TR_IN__EDGE      TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW0_TR_OUT           TRIGGER_TYPE_EDGE
/* LIN Trigger Types */
#define TRIGGER_TYPE_LIN_TR_CMD_TX_HEADER       TRIGGER_TYPE_EDGE
/* PDM Trigger Types */
#define TRIGGER_TYPE_PDM_TR_ACTIVATE            TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PDM_TR_DBG_FREEZE          TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PDM_TR_RX_REQ              TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PDM_TR_RX_REQ_ALL          TRIGGER_TYPE_LEVEL
/* PERI Trigger Types */
#define TRIGGER_TYPE_PERI_TR_DBG_FREEZE         TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PERI_TR_IO_INPUT__LEVEL    TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PERI_TR_IO_INPUT__EDGE     TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PERI_TR_IO_OUTPUT__LEVEL   TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PERI_TR_IO_OUTPUT__EDGE    TRIGGER_TYPE_EDGE
/* SCB Trigger Types */
#define TRIGGER_TYPE_SCB_TR_I2C_SCL_FILTERED    TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_SCB_TR_RX_REQ              TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_SCB_TR_TX_REQ              TRIGGER_TYPE_LEVEL
/* SMIF Trigger Types */
#define TRIGGER_TYPE_SMIF_TR_RX_REQ             TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_SMIF_TR_TX_REQ             TRIGGER_TYPE_LEVEL
/* SRSS Trigger Types */
#define TRIGGER_TYPE_SRSS_TR_DEBUG_FREEZE_MCWDT TRIGGER_TYPE_LEVEL
/* TCPWM Trigger Types */
#define TRIGGER_TYPE_TCPWM_TR_DEBUG_FREEZE      TRIGGER_TYPE_LEVEL
/* TDM Trigger Types */
#define TRIGGER_TYPE_TDM_TR_DBG_FREEZE          TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TDM_TR_RX_REQ              TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TDM_TR_TX_REQ              TRIGGER_TYPE_LEVEL

/* Include IP definitions */
#include "ip/cyip_peri.h"
#include "ip/cyip_ppc.h"
#include "ip/cyip_peri_pclk.h"
#include "ip/cyip_ramc_ppu.h"
#include "ip/cyip_icache.h"
#include "ip/cyip_cpuss_ppu.h"
#include "ip/cyip_ramc.h"
#include "ip/cyip_promc.h"
#include "ip/cyip_mxcm33.h"
#include "ip/cyip_dw.h"
#include "ip/cyip_cpuss.h"
#include "ip/cyip_ms_ctl_1_2.h"
#include "ip/cyip_cpuss_sl_ctl.h"
#include "ip/cyip_ipc.h"
#include "ip/cyip_srss.h"
#include "ip/cyip_pwrmode.h"
#include "ip/cyip_backup.h"
#include "ip/cyip_cryptolite.h"
#include "ip/cyip_hsiom.h"
#include "ip/cyip_gpio.h"
#include "ip/cyip_smartio.h"
#include "ip/cyip_lin.h"
#include "ip/cyip_canfd_v3.h"
#include "ip/cyip_tcpwm_v2.h"
#include "ip/cyip_mxs40adcmic.h"
#include "ip/cyip_scb_v4.h"
#include "ip/cyip_efuse_v3.h"
#include "ip/cyip_efuse_data_v3_cyw20829.h"
#include "ip/cyip_smif_v3.h"
#include "ip/cyip_tdm.h"
#include "ip/cyip_pdm.h"
#include "ip/cyip_mxkeyscan.h"
#include "ip/cyip_btss.h"

/* Parameter Defines */
/* Number of TTCAN instances */
#define CANFD_CAN_NR                    1u
/* ECC logic present or not */
#define CANFD_ECC_PRESENT               0u
/* address included in ECC logic or not */
#define CANFD_ECC_ADDR_PRESENT          0u
/* Time Stamp counter present or not (required for instance 0, otherwise not
   allowed) */
#define CANFD_TS_PRESENT                1u
/* Message RAM size in KB */
#define CANFD_MRAM_SIZE                 4u
/* Message RAM address width */
#define CANFD_MRAM_ADDR_WIDTH           10u
/* System RAM 0 MPC protection block size in Bytes: 1<< (RAMC0_BLOCK_SIZE+5).
   Example: 7 = 4KB protection block size. */
#define CPUSS_RAMC0_BLOCK_SIZE          7u
/* Number of macros used to implement System RAM 0. Example: 8 if 256 KB System
   SRAM0 is implemented with 8 32KB macros. */
#define CPUSS_RAMC0_MACRO_NR            2u
/* Number of power partitions in system RAM 0. Each power partition can be
   independently power controlled using a switch. Example: RAMC0_MACRO_NR = 16
   and RAMC0_PWR_GROUP_NR = 4 will create 4 power partitions with 4 macros in
   each power partition. */
#define CPUSS_RAMC0_PWR_GROUP_NR        2u
/* System RAM 1 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC1_PRESENT             0u
/* System RAM 1 MPC protection block size in Bytes: 1<< (RAMC1_BLOCK_SIZE+5).
   Example: 7 = 4KB protection block size. */
#define CPUSS_RAMC1_BLOCK_SIZE          7u
/* Number of macros used to implement System RAM 1. Example: 8 if 256 KB System
   RAM 1 is implemented with 8 32KB macros. */
#define CPUSS_RAMC1_MACRO_NR            1u
/* Number of power partitions in system RAM 1. Each power partition can be
   independently power controlled using a switch. Example: RAMC1_MACRO_NR = 16
   and RAMC1_PWR_GROUP_NR = 4 will create 4 power partitions with 4 macros in
   each power partition. */
#define CPUSS_RAMC1_PWR_GROUP_NR        1u
/* System RAM 2 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC2_PRESENT             0u
/* System RAM 2 MPC protection block size in Bytes: 1<< (RAMC2_BLOCK_SIZE+5).
   Example: 7 = 4KB protection block size. */
#define CPUSS_RAMC2_BLOCK_SIZE          7u
/* Number of macros used to implement System RAM 2. Example: 8 if 256 KB System
   RAM 2 is implemented with 8 32KB macros. */
#define CPUSS_RAMC2_MACRO_NR            1u
/* Number of power partitions in system RAM 2. Each power partition can be
   independently power controlled using a switch. Example: RAMC2_MACRO_NR = 16
   and RAMC2_PWR_GROUP_NR = 4 will create 4 power partitions with 4 macros in
   each power partition. */
#define CPUSS_RAMC2_PWR_GROUP_NR        1u
/* System SRAM(s) ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_PRESENT          0u
/* System SRAM(s) address ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_ADDR_PRESENT     0u
/* System Patchable ROM Controller Present or not ('0' : no, '1': yes) */
#define CPUSS_PROMC_PRESENT             1u
/* Number of macros used to implement system patchable ROM. Example: 4 if 512 KB
   system patchable ROM is implemented with 4 128KB macros. */
#define CPUSS_PROMC_MACRO_NR            1u
/* PROMC memory block size for protection scheme : 1<< (PROMC_BLOCK_SIZE+5).
   Example: 7 = 4KB protection block size. */
#define CPUSS_PROMC_BLOCK_SIZE          6u
/* Presence of the patch functionality. 0: ROM cannot be patched. 1: ROM can be
   patched. */
#define CPUSS_PROMC_PATCH_PRESENT       0u
/* Number of patchable locations (patch entries). Possible range [32,512] in
   powers of 2. (BRCM: 512 is only supported) These are implemented using SRAM.
   (SNPS: 32x128, 64x128, 128x128, 256x128, 512x128 are supported; BRCM: 4
   instances of 512x32 only supported) */
#define CPUSS_PROMC_PATCH_NR            64u
/* Patch size selection of a single structure. 0: 8 Bytes. 1: 16 Bytes. **) 2: 32
   Bytes. 3: 64 Bytes. **) The patch size should fit to the word size of the
   ROM. Thus only PATCH_SIZE=1 is supported for this ROM controller. */
#define CPUSS_PROMC_PATCH_SIZE          1u
/* Width of compared address bits. The LSB is determined by the PATCH_SIZE, for 16
   bytes this equals to bit [4]. The MSB is chosen to address the full size of
   the ROM in bytes. */
#define CPUSS_PROMC_MATCH_ADDR_SIZE     12u
/* Initial value of the first patchable address in the ROM. This address and the
   following higher addresses are patchable if the function is enabled. */
#define CPUSS_PROMC_SROM_BOUNDARY       4096u
/* Flash Controller Present or not ('0' : no, '1': yes) */
#define CPUSS_FLASHC_PRESENT            0u
/* Flash data output word size (in Bytes) */
#define CPUSS_FLASHC_MAIN_DATA_WIDTH    16u
/* Number of Flash BIST_DATA registers */
#define CPUSS_FLASHC_BIST_DATA_NR       4u
/* SONOS Flash RWW present or not ('0': no, '1': yes) When RWW is '0', No special
   sectors present in Flash. Part of main sector 0 is allowcated for Supervisory
   Flash, and no Work Flash present. */
#define CPUSS_FLASHC_SONOS_RWW          1u
/* SONOS Flash, number of main sectors. */
#define CPUSS_FLASHC_SONOS_MAIN_SECTORS 8u
/* SONOS Flash, number of rows per main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_ROWS    512u
/* SONOS Flash, number of words per row of main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_WORDS   128u
/* SONOS Flash, number of special sectors. */
#define CPUSS_FLASHC_SONOS_SPL_SECTORS  2u
/* SONOS Flash, number of rows per special sector. */
#define CPUSS_FLASHC_SONOS_SPL_ROWS     64u
/* DataWire 0 present or not ('0': no, '1': yes) */
#define CPUSS_DW0_PRESENT               1u
/* Number of DataWire 0 channels (8, 16 or 32) */
#define CPUSS_DW0_CH_NR                 16u
/* DataWire 1 present or not ('0': no, '1': yes) */
#define CPUSS_DW1_PRESENT               0u
/* Number of DataWire 1 channels (8, 16 or 32) */
#define CPUSS_DW1_CH_NR                 1u
/* DataWire SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_PRESENT            0u
/* DataWire SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_ADDR_PRESENT       0u
/* DMA controller-0 present or not ('0': no, '1': yes) */
#define CPUSS_DMAC0_PRESENT             0u
/* Number of DMA controller-0 channels ([1, 8]) */
#define CPUSS_DMAC0_CH_NR               1u
/* DMA controller-1 present or not ('0': no, '1': yes) */
#define CPUSS_DMAC1_PRESENT             0u
/* Number of DMA controller-1 channels ([1, 8]) */
#define CPUSS_DMAC1_CH_NR               1u
/* Number of IPC structures. Legal range [1, 16] */
#define CPUSS_IPC_NR                    4u
/* Number of IPC interrupt structures. Legal range [1, 16] */
#define CPUSS_IPC_IRQ_NR                2u
/* Number of protection contexts supported. Legal range [3, 4, 6, 8] (CDT-336698) */
#define CPUSS_PC_NR                     4u
/* System interrupt functionality present or not ('0': no; '1': yes). Not used for
   CM0+ PCU, which always uses system interrupt functionality. */
#define CPUSS_SYSTEM_IRQ_PRESENT        0u
/* Number of total interrupt request inputs to CPUSS */
#define CPUSS_SYSTEM_INT_NR             69u
/* Number of DeepSleep wakeup interrupt inputs to CPUSS */
#define CPUSS_SYSTEM_DPSLP_INT_NR       17u
/* Number of CPU interrupts used when SYSTEM_IRQ_PRESENT is '1'. Legal values 8,
   16. */
#define CPUSS_CM33_INT_NR               8u
/* Individual CPU interrupts to be disabled when SYSTEM_IRQ_PRESENT is '0'. 0: To
   enable respective interrupt-bit functionality; 1: To disable respective
   interrupt-bit functionality; Default value {480{1'b0}} to enable all 480
   interrupts of CM33; Example: {479{1'b0},1'b1} disables the interrupt IRQ[0]
   of CM33 and enables all other interrupts. This parameter is NOT applicable
   when SYSTEM_IRQ_PRESENT is '1'. */
#define CPUSS_CM33_IRQ_DISABLE          0u
/* CM33_0 Floating point unit present or not ('0': no, '1': yes) */
#define CPUSS_CM33_0_FPU_PRESENT        0u
/* CM33_0 DSP extension present or not ('0': no, '1': yes) */
#define CPUSS_CM33_0_DSP_PRESENT        0u
/* CM33_0 Security extension present or not ('0': no, '1': yes) */
#define CPUSS_CM33_0_SECEXT_PRESENT     0u
/* CM33_0 non-secure MPU regions. Legal values [0, 4, 8, 12, 16] */
#define CPUSS_CM33_0_MPU_NS_REGION_NR   8u
/* CM33_0 secure MPU regions. Legal values [0, 4, 8, 12, 16] */
#define CPUSS_CM33_0_MPU_S_REGION_NR    0u
/* CM33_0 SAU regions. Legal values [0, 4, 8] */
#define CPUSS_CM33_0_SAU_REGION_NR      0u
/* CM33_1 present or not. */
#define CPUSS_CM33_1_PRESENT            0u
/* CM33_1 Floating point unit present or not ('0': no, '1': yes) */
#define CPUSS_CM33_1_FPU_PRESENT        1u
/* CM33_1 DSP extension present or not ('0': no, '1': yes) */
#define CPUSS_CM33_1_DSP_PRESENT        1u
/* CM33_1 Security extension present or not ('0': no, '1': yes) */
#define CPUSS_CM33_1_SECEXT_PRESENT     1u
/* CM33_1 non-secure MPU regions. Legal values [0, 4, 8, 12, 16] */
#define CPUSS_CM33_1_MPU_NS_REGION_NR   16u
/* CM33_1 secure MPU regions. Legal values [0, 4, 8, 12, 16] */
#define CPUSS_CM33_1_MPU_S_REGION_NR    16u
/* CM33_1 SAU regions. Legal values [0, 4, 8] */
#define CPUSS_CM33_1_SAU_REGION_NR      8u
/* Cache RAM size in Kilo Bytes; Supported values are [8, 16, 32]. */
#define CPUSS_CACHE_SIZE                8u
/* Cache RAM ECC present or not ('0': no, '1': yes) */
#define CPUSS_CACHE_RAM_ECC_PRESENT     0u
/* Debug level. Legal range [0,3] (0= No support, 1= Minimum: CM0/4 both 2
   breakpoints +1 watchpoint, 2= Full debug: CM0/4 have 4/6 breakpoints, 2/4
   watchpoints and 0/2 literal compare, 3= Full debug + data matching) */
#define CPUSS_DEBUG_LVL                 2u
/* Trace level. Legal range [0,2] (0= No tracing, 1= ITM + TPIU + SWO, 2= ITM +
   ETM + TPIU + SWO) Note: CM4 HTM is not supported. Hence vaule 3 for trace
   level is not supported in CPUSS. */
#define CPUSS_TRACE_LVL                 1u
/* Embedded Trace Buffer present or not (0=No, 1=Yes) */
#define CPUSS_ETB_PRESENT               0u
/* PTM interface present (0=No, 1=Yes) */
#define CPUSS_PTM_PRESENT               0u
/* Width of the PTM interface in bits ([2,32]) */
#define CPUSS_PTM_WIDTH                 1u
/* Width of the TPIU interface in bits ([1,4]) */
#define CPUSS_TPIU_WIDTH                4u
/* CPUSS external CODE master interface 0 present or not on CODE infrastructure.
   ('0': no, '1': yes). */
#define CPUSS_CODE_MS_0_PRESENT         0u
/* CPUSS external SYS master interface 0 present or not on SYS infrastructure.
   ('0': no, '1': yes). */
#define CPUSS_SYS_MS_0_PRESENT          1u
/* CPUSS external SYS master interface 1 present or not on SYS infrastructure.
   ('0': no, '1': yes). */
#define CPUSS_SYS_MS_1_PRESENT          0u
/* CPUSS external SYS master NVM interface 0 present or not on SYS infrastructure.
   ('0': no, '1': yes). */
#define CPUSS_SYS_MS_0_NVM_PRESENT      0u
/* CPUSS external SYS master NVM interface 1 present or not on SYS infrastructure.
   ('0': no, '1': yes). */
#define CPUSS_SYS_MS_1_NVM_PRESENT      0u
/* Number of external AHB5 slave interfaces connected to SYSTEM infrastructure.
   Maximum number of slaves supported is 4. Width of this parameter is 4-bits.
   1-bit mask for each slave indicating present or not. Example: 4'b0001 - slave
   0 is present. */
#define CPUSS_SYS_SL_PRESENT            1u
/* Number of external EXPANSION masters driving the EXP AHB5 infrastructure.
   Maximum number of masters supported is 8. Width of this parameter is 8-bits.
   1-bit mask for each master indicating present or not. Example: 8'b0000_0101 -
   master 0 & master 2 are present. */
#define CPUSS_EXP_MS_PRESENT            1u
/* The timing de-coupled AHB brdige is present or not on the output of EXP
   infrastructure. ('0': no, '1':yes) */
#define CPUSS_EXP_BRIDGE_PRESENT        1u
/* Specifies the CODE interconnect is present or not; 0: Not present; 1: Present; */
#define CPUSS_CODE_INFRA_PRESENT        1u
/* Specifies the CODE interconnect arbitration type used for generating the RTL.
   0: ROUND; round insert an extra cycle each time the downstream port selects a
   new upstream port to service and must be used to avoid timing issues when
   target frequency is >=100MHz; 1: ROUND_NOLAT; round_nolat have no such
   latency and can be used when target frequency is <100MHz; Improves the
   performance by reducing latency; */
#define CPUSS_CODE_INFRA_ARB_TYPE       1u
/* Specifies the SYSTEM interconnect arbitration type used for generating the RTL.
   0: ROUND; round insert an extra cycle each time the downstream port selects a
   new upstream port to service and must be used to avoid timing issues when
   target frequency is >=100MHz; 1: ROUND_NOLAT; round_nolat have no such
   latency and can be used when target frequency is <100MHz; Improves the
   performance by reducing latency; */
#define CPUSS_SYSTEM_INFRA_ARB_TYPE     1u
/* Specifies the EXPANSION interconnect arbitration type used for generating the
   RTL. 0: ROUND; round insert an extra cycle each time the downstream port
   selects a new upstream port to service and must be used to avoid timing
   issues when target frequency is >=100MHz; 1: ROUND_NOLAT; round_nolat have no
   such latency and can be used when target frequency is <100MHz; Improves the
   performance by reducing latency; */
#define CPUSS_EXP_INFRA_ARB_TYPE        1u
/* CoreSight Part Identification Number */
#define CPUSS_JEPID                     52u
/* CoreSight Part Identification Number */
#define CPUSS_JEPCONTINUATION           0u
/* CoreSight Part Identification Number */
#define CPUSS_FAMILYID                  272u
/* ROM trim register width (for ARM 3, for Synopsys 5, for BRCM 6) */
#define CPUSS_ROM_TRIM_WIDTH            5u
/* ROM trim register default (for both ARM and Synopsys 0x0000_0002; for BRCM
   0x0000_0000) */
#define CPUSS_ROM_TRIM_DEFAULT          18u
/* RAM trim register width (for ARM 8, for SNPS 15, for BRCM 16) For SNPS: SRAM
   will get its trim value from trim[15:0] and RF from trim [31:16] */
#define CPUSS_RAM_TRIM_WIDTH            32u
/* RAM trim register default (for ARM 0x0000_0062 and for Synopsys 0x0000_6012,
   for BRCM 0x0000_0000) */
#define CPUSS_RAM_TRIM_DEFAULT          16403u
/* RAM Trim control-2 register present or not; 1-present; 0-not present; Place
   holder for S22 SRAM memories. */
#define CPUSS_TRIM_RAM_CTL2_PRESENT     0u
/* RAM trim register width Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_WIDTH2           32u
/* RAM trim register default. Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_DEFAULT2         24594u
/* RAM Trim control-3 register present or not; 1-present; 0-not present; Place
   holder for S22 SRAM memories. */
#define CPUSS_TRIM_RAM_CTL3_PRESENT     0u
/* RAM trim register width Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_WIDTH3           32u
/* RAM trim register default. Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_DEFAULT3         24594u
/* RAM Trim control-4 register present or not; 1-present; 0-not present; Place
   holder for S22 SRAM memories. */
#define CPUSS_TRIM_RAM_CTL4_PRESENT     0u
/* RAM trim register width Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_WIDTH4           32u
/* RAM trim register default. Place holder for S22 SRAM memories. */
#define CPUSS_RAM_TRIM_DEFAULT4         24594u
/* Specifies the CM33-0 CACHE SRAM POWER SWITCH is present or not; 0: Not present;
   1: Present; */
#define CPUSS_CM33_0_CACHE_SWITCH_PRESENT 1u
/* Specifies the CM33-1 CACHE SRAM POWER SWITCH is present or not; 0: Not present;
   1: Present; */
#define CPUSS_CM33_1_CACHE_SWITCH_PRESENT 0u
/* Specifies the DW-0 SRAM POWER SWITCH is present or not; 0: Not present; 1:
   Present; */
#define CPUSS_DW0_SWITCH_PRESENT        0u
/* Specifies the DW-1 SRAM POWER SWITCH is present or not; 0: Not present; 1:
   Present; */
#define CPUSS_DW1_SWITCH_PRESENT        0u
/* Specifies the MPC SRAM POWER SWITCH is present or not; 0: Not present; 1:
   Present; */
#define CPUSS_MPC_SWITCH_PRESENT        0u
/* Specifies the PROMC Patch-SRAM POWER SWITCH is present or not; 0: Not present;
   1: Present; */
#define CPUSS_PROMC_SWITCH_PRESENT      0u
/* External Crystal Oscillator is present (high frequency) */
#define CPUSS_ECO_PRESENT               0u
/* System RAM 0 size in KB */
#define CPUSS_CHIP_TOP_RAMC0_SIZE       128u
/* System RAM 1 size in kilobytes */
#define CPUSS_CHIP_TOP_RAMC1_SIZE       1u
/* System RAM 2 size in kilobytes */
#define CPUSS_CHIP_TOP_RAMC2_SIZE       1u
/* System Patchable ROM size in KB */
#define CPUSS_CHIP_TOP_PROMC_SIZE       64u
/* Flash main region size in KB */
#define CPUSS_CHIP_TOP_FLASH_SIZE       2048u
/* Flash work region size in KB (EEPROM emulation, data) */
#define CPUSS_CHIP_TOP_WFLASH_SIZE      32u
/* Flash supervisory region size in KB */
#define CPUSS_CHIP_TOP_SFLASH_SIZE      32u
/* CM4 ETB SRAM buffer size in kilobytes. Legal vaules 4, 8 or 16 */
#define CPUSS_CHIP_TOP_ETB_SRAM_SIZE    2u
/* See MMIO2 instantiation or not */
#define CPUSS_CHIP_TOP_PROFILER_PRESENT 0u
/* ETAS Calibration support pin out present (automotive only) */
#define CPUSS_CHIP_TOP_CAL_SUP_NZ_PRESENT 0u
/* TRACE_LVL>0 */
#define CPUSS_CHIP_TOP_TRACE_PRESENT    1u
/* Number of protection contexts supported. Legal range [3, 4, 6, 8] (CDT-336698) */
#define CPUSS_MS_CTL_STRUCT_PC_NR       4u
/* IP MMIO registers base address in the system address space (32-bit Byte address
   at a 64 kB multiple). The IP MMIO registers occupy a 64 kB memory region in
   the system address space. */
#define CRYPTOLITE_ADDR_BASE            1076035584u
/* ECC present or not ('0': no, '1': yes). */
#define CRYPTOLITE_ECC_PRESENT          0u
/* True random number generation component support ('0': no, '1': yes). */
#define CRYPTOLITE_TRNG_PRESENT         0u
/* Vector unit component support ('0': no, '1': yes). */
#define CRYPTOLITE_VU_PRESENT           0u
/* SHA-256 hash component support ('0': no, '1': yes). */
#define CRYPTOLITE_SHA_PRESENT          1u
/* AES-128 block cipher component support ('0': no, '1': yes). */
#define CRYPTOLITE_AES_PRESENT          0u
/* Number of HFCLK roots present. Must be > 0. Must be same as set for SRSS */
#define DFT_NUM_HFROOT                  4u
/* Width of clk_occ_fast output bus (number of external OCCs) */
#define DFT_EXT_OCC                     0u
/* Number of PLLs usable as struct mode clock source (number of clk_occ_fast
   clocks). Not expected to be more than 4 */
#define DFT_NUM_FASTCLK                 1u
/* Number of select signals to control each FASTCLK multiplexer. Not expected to
   be more than 2 */
#define DFT_NUM_FASTCLK_SEL             1u
/* Number of MBIST controllers with corresponding mbist(pg)_done and mbist(pg)_go
   signals. Value defined by CIC during Pass 1. */
#define DFT_MBIST_C_NUM                 7u
/* Number of LBIST controllers. One LBIST controller on top level and one LBIST
   controller in each optional HDFT block */
#define DFT_LBIST_C_NUM                 1u
/* Number of MBISR chains. Separate chains are required for power domains that can
   be enabled independently */
#define DFT_MBISR_CH_NUM                1u
/* Defines if (Burn-In) Monitor function is present */
#define DFT_MONITOR_PRESENT             1u
/* Defines if Mentor BISR controller is present (controls generation of control
   and status register) */
#define DFT_MENTOR_BISR_PRESENT         1u
/* Defines if Direct MBIST Access function is present (controls generation of
   control and status registers) */
#define DFT_DIRECT_MBIST_ACCESS_PRESENT 0u
/* Defines if DIRECT_MBIST*SEL and DIRECT_MBIST*_RESULT registers are generated
   (only used for DIRECT_MBIST_ACCESS_PRESENT=1) */
#define DFT_DIRECT_MBIST_CTRL_ACCESS_PRESENT 0u
/* Controls generation of BIST_STEP_SEL_EN and BIST_STEP_SEL register fields
   within DIRECT_MBIST_CTL reg (only used for DIRECT_MBIST_ACCESS_PRESENT=1) */
#define DFT_DIRECT_MBIST_STEP_ACCESS_PRESENT 0u
/* Controls generation of BIST_MEM_SEL_EN and BIST_MEM_SEL register fields within
   DIRECT_MBIST_CTL reg (only used for DIRECT_MBIST_ACCESS_PRESENT=1) */
#define DFT_DIRECT_MBIST_MEM_ACCESS_PRESENT 0u
/* Number of HLBs with Direct MBIST Access function (only used for
   DIRECT_MBIST_ACCESS_PRESENT=1) */
#define DFT_DIRECT_MBIST_BAP_NUM        1u
/* Maximum value of MBIST controllers connected to single BAP (only used for
   DIRECT_MBIST_ACCESS_PRESENT=1) */
#define DFT_DIRECT_MBIST_CTRL_NUM       1u
/* local parameter: Number of MBIST controllers mapped to BISTMON_MBIST0_COMPLETED
   register */
#define DFT_MBIST0_C_NUM                7u
/* local parameter: Number of MBIST controllers mapped to BISTMON_MBIST1_COMPLETED
   register */
#define DFT_MBIST1_C_NUM                1u
/* local parameter: Number of MBIST controllers mapped to BISTMON_MBIST2_COMPLETED
   register */
#define DFT_MBIST2_C_NUM                1u
/* local parameter: Number of MBIST controllers mapped to BISTMON_MBIST3_COMPLETED
   register */
#define DFT_MBIST3_C_NUM                1u
/* local parameter: Number of MBIST controllers mapped to DIRECT_MBIST0_SEL and
   DIRECT_MBIST0_RESULT registers */
#define DFT_DIRECT_MBIST0_CTRL_NUM      1u
/* local parameter: Number of MBIST controllers mapped to DIRECT_MBIST1_SEL and
   DIRECT_MBIST1_RESULT registers */
#define DFT_DIRECT_MBIST1_CTRL_NUM      1u
/* local parameter: Number of MBIST controllers mapped to DIRECT_MBIST2_SEL and
   DIRECT_MBIST2_RESULT registers */
#define DFT_DIRECT_MBIST2_CTRL_NUM      1u
/* local parameter: Number of MBIST controllers mapped to DIRECT_MBIST3_SEL and
   DIRECT_MBIST3_RESULT registers */
#define DFT_DIRECT_MBIST3_CTRL_NUM      1u
/* Must be set to 1 when using this mxdft version in MXS40Sv2 devices */
#define DFT_PLATFORM_MXS40SV2           1u
/* Defines if VCCRET supply is generated in UPF. Must be set to 1 in MXS40S*
   technologies and to 0 in MXS40E */
#define DFT_VCCRET_PRESENT              1u
/* Defines if UPF is generated for S28 technology (1) or S40 technolgy (0) */
#define DFT_TECH_S28                    0u
/* Controls the polulation of the "accessed" monitor bits <IOBSC,0,MBIST,LBIST>.
   Default = 4'b1011 */
#define DFT_POP_ACC                     10u
/* Controls the polulation of the "started" monitor bits
   <0,FLASH_DBI,MBIST,LBIST>. Default = 4'b0111 */
#define DFT_POP_START                   2u
/* Controls the polulation of the "done" (completed) monitor bits
   <0,FLASH_DBI,MBIST,LBIST>. Default = 4'b0111 */
#define DFT_POP_DONE                    2u
/* Controls the polulation of the "failed" monitor bits <0,0,MBIST,LBIST>. Default
   = 4'b0011 */
#define DFT_POP_FAIL                    2u
/* Used for mxdft_tap: controls generation of logic for "TDR capture&update via
   MMIO" (default value is 1) */
#define DFT_CAP_UP_PRESENT              0u
/* Number of DataWire channels ([1, 512]) */
#define DW_CH_NR                        16u
/* DataWire SRAM ECC present or not ('0': no, '1': yes) */
#define DW_ECC_PRESENT                  0u
/* DataWire SRAM address ECC present or not ('0': no, '1': yes) */
#define DW_ECC_ADDR_PRESENT             0u
#define DW_CH_NR_WIDTH                  1u
#define DW_CH_STRUCT_ECC_PRESENT        0u
/* Number of instantiated eFUSE macros (256 bit macros). Legal range [4,8,12,16] */
#define EFUSE_EFUSE_NR                  4u
/* Enables limiting access to region defined by PROT_MASTER_START/END by
   PROT_MASTER */
#define EFUSE_BLOCK_NVM_CRYPTO          0u
/* Begining of region of EFUSE only accessible by master defined by PROT_MASTER. */
#define EFUSE_PROT_MASTER_START         4092u
/* End of region of EFUSE (last address) only accessible by master defined by
   PROT_MASTER. */
#define EFUSE_PROT_MASTER_END           4092u
/* The Master with permission to access the region defined by
   PROT_MASTER_START/PROT_MASTER_END */
#define EFUSE_PROT_MASTER               255u
/* Cache SRAM ECC present or not ('0': no, '1': yes) */
#define ICACHE_ECC_PRESENT              0u
/* Number of GPIO ports in range 0..31 */
#define IOSS_GPIO_GPIO_PORT_NR_0_31     6u
/* Number of GPIO ports in range 32..63 */
#define IOSS_GPIO_GPIO_PORT_NR_32_63    0u
/* Number of GPIO ports in range 64..95 */
#define IOSS_GPIO_GPIO_PORT_NR_64_95    0u
/* Number of GPIO ports in range 96..127 */
#define IOSS_GPIO_GPIO_PORT_NR_96_127   0u
/* Number of ports in device */
#define IOSS_GPIO_GPIO_PORT_NR          6u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_HSIO 0u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_HSIO 0u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_HSIO 1u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_HSIO 0u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_HSIO 0u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SIO 0u
/* Indicates port is an HSIO port */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_HSIO 0u
/* Indicates port is a GPIO_SMC */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_GPIO_SMC 0u
/* Indicates port is a HSIO_ENH */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_HSIO_ENH 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_AUTOLVL 0u
/* Indicates port supports drive select trims */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_DS_CTRL 0u
/* Indicates port supports slew extension bits */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLEW_EXT 1u
/* Indicates port supports drive select extension trims */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_DRIVE_EXT 1u
/* Indicates slew bit width */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLEW_WIDTH 1u
/* Indicates drive bit width */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_DRIVE_WIDTH 3u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO7 0u
/* Power Switch exists */
#define IOSS_GPIO_PWRSW                 0u
/* Number of AMUX splitter cells */
#define IOSS_HSIOM_AMUX_SPLIT_NR        1u
/* Number of HSIOM ports in device (same as GPIO.GPIO_PRT_NR) */
#define IOSS_HSIOM_HSIOM_PORT_NR        6u
/* Number of PWR/GND MONITOR CELLs in the device */
#define IOSS_HSIOM_MONITOR_NR           0u
/* Number of PWR/GND MONITOR CELLs in range 0..31 */
#define IOSS_HSIOM_MONITOR_NR_0_31      0u
/* Number of PWR/GND MONITOR CELLs in range 32..63 */
#define IOSS_HSIOM_MONITOR_NR_32_63     0u
/* Number of PWR/GND MONITOR CELLs in range 64..95 */
#define IOSS_HSIOM_MONITOR_NR_64_95     0u
/* Number of PWR/GND MONITOR CELLs in range 96..127 */
#define IOSS_HSIOM_MONITOR_NR_96_127    0u
/* Number of HSIOM ports in device (same as GPIO.GPIO_PRT_NR) */
#define IOSS_HSIOM_HSIOM_SEC_PORT_NR    0u
/* Mask of SMARTIO instances presence */
#define IOSS_SMARTIO_SMARTIO_MASK       8u
/* Page size in # of 32-bit words (1: 4 bytes, 2: 8 bytes, ... */
#define IPC_PA_SIZE                     32u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define IPC_MASTER_WIDTH                6u
#define IPC_IPC_NR                      4u
#define IPC_IPC_IRQ_NR                  2u
/* Number of LIN channels ([2, 32]). For test functionality (two channels are
   connected), the minimal number of LIN channels is 2. */
#define LIN_CH_NR                       2u
/* Number of AHB5 "hmaster[]" bits ([1, 8]). */
#define LIN_MASTER_WIDTH                6u
/* 0=ULL65, 1=MXS40-ULP, 2=MXS40E, 3=M0S8, 4=MXS40-HD, 5=F45, 6=MXS40v2, 7=T28HPM,
   8=T28HPL, 9=T28HPC */
#define LIN_CHIP_TOP_PLATFORM_VARIANT   6u
/* CM33[0] should be 0, CM33[1] should have 1 */
#define MXCM33_CPU_WAIT_DEFAULT         0u
/* Number of CPU interrupts used when SYSTEM_IRQ_PRESENT is '1'. Legal values 8,
   16. */
#define MXCM33_CM33_INT_NR              8u
/* IRQ expander present ('0': no, '1': yes) */
#define MXCM33_SYSTEM_IRQ_PRESENT       0u
/* CM33[0] should be 1, CM33[1] should have 0 */
#define MXCM33_PC_MON_PRESENT           1u
/* Number of system interrupt inputs to CPUSS */
#define MXCM33_SYSTEM_INT_NR            69u
/* TrustZone security extention present or not */
#define MXCM33_SECEXT                   0u
/* FPU extention present or not */
#define MXCM33_FPU_PRESENT              0u
/* DSP extention present or not */
#define MXCM33_DSP_PRESENT              0u
/* AHB5 master bus width */
#define MXKEYSCAN_AHB_MASTER_WIDTH      6u
/* AHB5 address bus width */
#define MXKEYSCAN_AHB_ADDR_WIDTH        12u
/* AHB5 user bus width */
#define MXKEYSCAN_AHB_USER_WIDTH        4u
/* AHB5 prot bus width */
#define MXKEYSCAN_AHB_PROT_WIDTH        7u
/* Number of keyboard rows as input */
#define MXKEYSCAN_NUM_ROWS_IN           8u
/* Number of keyboard columns as output */
#define MXKEYSCAN_NUM_COLS_OUT          18u
/* CELL VT selection for ACTIVE Domain */
#define MXKEYSCAN_CELL_VT_TYPE_ACTIVE   1u
/* CELL VT selection DEEEPSLEEP Domain */
#define MXKEYSCAN_CELL_VT_TYPE_DPSLP    0u
/* Number of PDM structures ({2, 4, 6, 8}]). */
#define PDM_NR                          2u
/* Master interface presence mask (4 bits) */
#define PERI_MS_PRESENT                 3u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_CLOCK_PRESENT 0u
/* Default value for SL_CTL register value on POR. Group-0 it is 32'hFFFF_FFFF
   Group-1 to Group-15 it is 32'h000_0000 */
#define PERI_GROUP_PRESENT0_PERI_GROUP_SL_CTL_DEFAULT 4294967295u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_CLOCK_PRESENT 1u
/* Default value for SL_CTL register value on POR. Group-0 it is 32'hFFFF_FFFF
   Group-1 to Group-15 it is 32'h000_0000 */
#define PERI_GROUP_PRESENT1_PERI_GROUP_SL_CTL_DEFAULT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_CLOCK_PRESENT 1u
/* Default value for SL_CTL register value on POR. Group-0 it is 32'hFFFF_FFFF
   Group-1 to Group-15 it is 32'h000_0000 */
#define PERI_GROUP_PRESENT2_PERI_GROUP_SL_CTL_DEFAULT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_CLOCK_PRESENT 0u
/* Default value for SL_CTL register value on POR. Group-0 it is 32'hFFFF_FFFF
   Group-1 to Group-15 it is 32'h000_0000 */
#define PERI_GROUP_PRESENT3_PERI_GROUP_SL_CTL_DEFAULT 0u
/* Number of asynchronous PCLK groups */
#define PERI_PCLK_GROUP_NR              7u
/* Defines the width of INTR_AHB_ERROR.AHB_ERROR_VIO register width based on
   number of peripheral groups enabled and AHB error reporting is enabled
   (AHB_ERROR_PRESENT==1) */
#define PERI_GROUP_AHB_ERROR_WIDTH      4u
/* Defines the width of INTR_AHB_ERROR.TIMEOUT_VIO register width based on number
   of peripheral groups present and timeout error reporting logic is present
   (TIMEOUT_PRESENT==1). Note that group-0 is excluded from timeout reporting,
   so max width is 15 (group-1 to group-15). */
#define PERI_GROUP_TIMEOUT_WIDTH        3u
/* Timeout functionality present ('0': no, '1': yes) */
#define PERI_TIMEOUT_PRESENT            1u
/* AHB ERROR response reporting present ('0': no, '1':yes) */
#define PERI_AHB_ERROR_PRESENT          1u
/* Trigger module present ('0': no, '1': yes) */
#define PERI_TR                         1u
/* Number of trigger groups */
#define PERI_TR_GROUP_NR                10u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR0_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR1_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR2_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR3_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR4_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR5_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR6_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR7_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR8_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR9_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR0_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR1_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR2_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR3_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR4_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Divider number width: max(1,roundup(log2(max(DIV_*_NR))) */
#define PERI_GR_DIV_ADDR_WIDTH          4u
/* Number of asynchronous PCLK groups */
#define PERI_PERI_PCLK_PCLK_GROUP_NR    7u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT 1u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_CLOCK_VECT 1u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_PCLK_DIV_PRESENT 1u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT 5u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT 4u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT 2u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT 1u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_CLOCK_VECT 16u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_PCLK_DIV_PRESENT 1u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_CLOCK_VECT 0u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_PCLK_DIV_PRESENT 0u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT 2u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_CLOCK_VECT 2u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_PCLK_DIV_PRESENT 1u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_CLOCK_VECT 0u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_PCLK_DIV_PRESENT 0u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_CLOCK_VECT 0u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_PCLK_DIV_PRESENT 0u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT 0u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT 0u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_CLOCK_VECT 0u
/* If Direct Clocks PCLK DIVIDER would be zero, other wise 1 */
#define PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_PCLK_DIV_PRESENT 0u
/* Number of protection contexts supported. Legal range [3, 4, 6, 8] (CDT-336698) */
#define PERI_PPC_PC_NR                  4u
/* Security extension present ('0': no, '1': yes) */
#define PERI_PPC_SECEXT                 0u
/* Security Aware */
#define PERI_PPC_PPC_NR0_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR1_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR2_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR3_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR4_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR5_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR6_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR7_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR8_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR9_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR10_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR11_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR12_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR13_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR14_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR15_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR16_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR17_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR18_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR19_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR20_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR21_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR22_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR23_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR24_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR25_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR26_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR27_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR28_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR29_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR30_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR31_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR32_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR33_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR34_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR35_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR36_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR37_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR38_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR39_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR40_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR41_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR42_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR43_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR44_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR45_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR46_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR47_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR48_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR49_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR50_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR51_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR52_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR53_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR54_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR55_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR56_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR57_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR58_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR59_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR60_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR61_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR62_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR63_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR64_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR65_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR66_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR67_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR68_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR69_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR70_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR71_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR72_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR73_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR74_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR75_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR76_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR77_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR78_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR79_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR80_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR81_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR82_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR83_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR84_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR85_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR86_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR87_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR88_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR89_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR90_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR91_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR92_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR93_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR94_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR95_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR96_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR97_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR98_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR99_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR100_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR101_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR102_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR103_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR104_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR105_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR106_SECURITY_AWARE 1u
/* Security Aware */
#define PERI_PPC_PPC_NR107_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR108_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR109_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR110_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR111_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR112_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR113_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR114_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR115_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR116_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR117_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR118_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR119_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR120_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR121_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR122_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR123_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR124_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR125_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR126_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR127_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR128_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR129_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR130_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR131_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR132_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR133_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR134_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR135_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR136_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR137_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR138_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR139_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR140_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR141_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR142_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR143_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR144_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR145_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR146_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR147_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR148_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR149_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR150_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR151_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR152_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR153_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR154_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR155_SECURITY_AWARE 0u
/* Security Aware */
#define PERI_PPC_PPC_NR156_SECURITY_AWARE 0u
/* Presence of the patch functionality. 0: ROM cannot be patched. 1: ROM can be
   patched. */
#define PROMC_PATCH_PRESENT             0u
/* Number of patchable locations (patch entries). Possible range [0,512]. */
#define PROMC_PATCH_NR                  64u
/* Number of patchable locations, qualified by PATCH_PRESENT. Local param to mimic
   by product XLS. */
#define PROMC_PATCH_NR_QUAL             0u
/* Patch size selection of a single structure. 0: 8 Bytes. 1: 16 Bytes. **) 2: 32
   Bytes. 3: 64 Bytes. **) The patch size should fit to the word size of the
   ROM. Thus only PATCH_SIZE=1 is supported for this ROM controller. */
#define PROMC_PATCH_SIZE                1u
/* Width of compared address bits. The LSB is determined by the PATCH_SIZE, for 16
   bytes this equals to bit [4]. The MSB is chosen to address the full size of
   the ROM in bytes. */
#define PROMC_MATCH_ADDR_SIZE           12u
/* Initial value of the first patchable address in the ROM. This address and the
   following higher addresses are patchable if the function is enabled. */
#define PROMC_SROM_BOUNDARY             303u
/* Width of the byte address (2^ROMC_ADDR_WIDTH byte of total SROM region). */
#define PROMC_ROMC_ADDR_WIDTH           16u
/* Number of physical SROM macros used. */
#define PROMC_ROMC_MACRO_NR             1u
/* Width of the byte address per each physical macro. */
#define PROMC_ROMC_MACRO_ADDR_WIDTH     16u
/* Bit width of hrdata and hwdata (AHB5 slave for ROM access). */
#define PROMC_DATA_PATH_WIDTH           128u
/* Number of RAM words for patch data. Local param to mimic by product XLS. */
#define PROMC_PATCH_RAM_WORDS           0u
/* VT type of instantiated tech cells through mxtk. */
#define PROMC_CELL_VT_TYPE              1u
/* Bit width of mmio_trim_ram_ctl_trim. */
#define PROMC_TRIM_WIDTH                32u
/* 0=ULL65, 1=MXS40-ULP, 2=MXS40E, 3=M0S8, 4=MXS40-HD, 5=F45, 6=MXS40v2, 7=T28HPM,
   8=T28HPL, 9=T28HPC */
#define PROMC_PLATFORM_VARIANT          6u
/* RAM vendor (0=Cypress, 1=Synopsys, 2=ARM, 3=Broadcom,4=TSMC) */
#define PROMC_RAM_VEND                  1u
/* Security based access checks are valid (1: NS bit is checked, 0: NS bit is
   ignored). */
#define PROMC_MPC_SECEXT                0u
/* Bit width of hmaster signal. */
#define PROMC_MPC_MASTER_WIDTH          6u
#define PROMC_MPC_PC_WIDTH              3u
/* Number of supported protection contexts. */
#define PROMC_MPC_PC_NR                 4u
#define PROMC_MPC_BLK_IDX_MAX           0u
#define PROMC_MPC_BLK_IDX_WIDTH         0u
#define PROMC_MPC_EXT_PRESENT           0u
#define PROMC_MPC_BLK_IDX_MAX_TIMES_FOUR_PLUS_THREE 3u
#define PROMC_MPC_BLK_IDX_WIDTH_PLUS_TWO 2u
/* Block size of individually protected blocks (0: 32B, 1: 64B, ...up to 15:1MB) */
#define PROMC_MPC_BLOCK_SIZE            6u
/* Number of AHB5 "huser[]" bits ([1, 8]). */
#define PROMC_MPC_USER_WIDTH            4u
/* Number of System SRAM power partions */
#define RAMC_PWR_GROUP_NR               2u
/* SRAM ECC present or not ('0': no, '1': yes) */
#define RAMC_ECC_PRESENT                0u
#define RAMC_MPC_MASTER_WIDTH           6u
#define RAMC_MPC_PC_WIDTH               3u
#define RAMC_MPC_PC_NR                  4u
#define RAMC_MPC_BLK_IDX_MAX            0u
#define RAMC_MPC_BLK_IDX_WIDTH          0u
#define RAMC_MPC_EXT_PRESENT            0u
#define RAMC_MPC_BLK_IDX_MAX_TIMES_FOUR_PLUS_THREE 3u
#define RAMC_MPC_BLK_IDX_WIDTH_PLUS_TWO 2u
#define RAMC_MPC_BLOCK_SIZE             7u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB0_DEEPSLEEP                  1u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB0_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB0_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB0_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB0_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB0_I2C_GLITCH                 1u
/* Support I2C Hs-mode (3.4Mbps) ('0': no, '1': yes) */
#define SCB0_I2C_HS                     0u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB0_I2C_EC                     1u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB0_I2C_M_S                    1u
/* I2C master and slave support? (I2C_M & I2C_HS) */
#define SCB0_I2C_M_HS                   0u
/* I2C master and slave support? (I2C_S & I2C_HS) */
#define SCB0_I2C_S_HS                   0u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB0_I2C_S_EC                   1u
/* SPI master support? ('0': no, '1': yes) */
#define SCB0_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB0_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB0_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB0_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB0_SPI_S_EC                   1u
/* UART support? ('0': no, '1': yes) */
#define SCB0_UART                       0u
/* SPI or UART (SPI | UART) */
#define SCB0_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB0_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB0_CMD_RESP                   1u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB0_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB0_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB0_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB0_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB0_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB0_CHIP_TOP_SPI_SEL_NR        3u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB0_CHIP_TOP_I2C_FAST_PLUS     1u
/* ddft_in[1:0] and ddft_out[1:0] are used (not used on M0S8 platform) */
#define SCB0_CHIP_TOP_DDFT_USED         4u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB1_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB1_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB1_I2C_M                      0u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB1_I2C_S                      0u
/* I2C support? (I2C_M | I2C_S) */
#define SCB1_I2C                        0u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB1_I2C_GLITCH                 0u
/* Support I2C Hs-mode (3.4Mbps) ('0': no, '1': yes) */
#define SCB1_I2C_HS                     0u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB1_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB1_I2C_M_S                    0u
/* I2C master and slave support? (I2C_M & I2C_HS) */
#define SCB1_I2C_M_HS                   0u
/* I2C master and slave support? (I2C_S & I2C_HS) */
#define SCB1_I2C_S_HS                   0u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB1_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB1_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB1_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB1_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB1_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB1_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB1_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB1_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB1_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB1_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB1_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB1_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB1_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB1_SPI_S_EZ                   0u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB1_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB1_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB1_CHIP_TOP_I2C_FAST_PLUS     1u
/* ddft_in[1:0] and ddft_out[1:0] are used (not used on M0S8 platform) */
#define SCB1_CHIP_TOP_DDFT_USED         4u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB2_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB2_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB2_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB2_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB2_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB2_I2C_GLITCH                 1u
/* Support I2C Hs-mode (3.4Mbps) ('0': no, '1': yes) */
#define SCB2_I2C_HS                     0u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB2_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB2_I2C_M_S                    1u
/* I2C master and slave support? (I2C_M & I2C_HS) */
#define SCB2_I2C_M_HS                   0u
/* I2C master and slave support? (I2C_S & I2C_HS) */
#define SCB2_I2C_S_HS                   0u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB2_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB2_SPI_M                      0u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB2_SPI_S                      0u
/* SPI support? (SPI_M | SPI_S) */
#define SCB2_SPI                        0u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB2_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB2_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB2_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB2_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB2_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB2_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB2_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB2_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB2_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB2_SPI_S_EZ                   0u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB2_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB2_CHIP_TOP_SPI_SEL_NR        0u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB2_CHIP_TOP_I2C_FAST_PLUS     1u
/* ddft_in[1:0] and ddft_out[1:0] are used (not used on M0S8 platform) */
#define SCB2_CHIP_TOP_DDFT_USED         4u
/* Slow AHB XIP cache is present ([0,1]). If SLOW_AHB_XIP_IF_PRESENT=0 then set
   this to 0 as well. */
#define SMIF_SLOW_CACHE_PRESENT         0u
/* Fast AHB XIP cache is present ([0,1]). If FAST_AHB_XIP_IF_PRESENT=0 then set
   this to 0 as well. */
#define SMIF_FAST_CACHE_PRESENT         0u
/* Number of Protection Contexts [1..8] for MPC; only valid when SLOW or
   FAST_AHB_XIP_IF_IS_AHB5 */
#define SMIF_PC_NR                      4u
/* Granularity of the MPC block size; 0: 32B, 1: 64B, ... 15: 1MB; only valid when
   SLOW or FAST_AHB_XIP_IF_IS_AHB5 */
#define SMIF_BLOCK_SIZE                 12u
/* Base address of the SMIF XIP memory region. This address must be a multiple of
   the SMIF XIP memory capacity. This address must be a multiple of the SMIF XIP
   memory region capacity (see SMIP_XIP_MASK below). The SMIF XIP memory region
   should NOT overlap with other memory regions. This adress must be in the
   [0x0000:0000, 0xffff:0000] memory region. However, for MXS40 CM4 based
   platform variant, this address must be in the [0x0000:0000, 0x1fff:0000]
   memory region (to ensure a connection to the ARM CM4 CPU ICode/DCode memory
   region [0x0000:0000, 0x1fff:ffff]). The external memory devices are located
   within the SMIF XIP memory region. */
#define SMIF_SMIF_XIP_ADDR              1610612736u
/* Capacity of the SMIF XIP memory region. The capacity must be a power of 2 and
   greater or equal than 64 KB). The more significant bits of this parameter are
   '1' and the lesser significant bits of this parameter are '0'. E.g.,
   0xfff0:0000 specifies a 1 MB memory region. Legal values are {0xffff:0000,
   0xfffe:0000, 0xfffc:0000, 0xfff8:0000, 0xfff0:0000, 0xffe0:0000, ...,
   0x8000:0000, 0x0000:0000}. */
#define SMIF_SMIF_XIP_MASK              4160749568u
/* Cryptography (AES) support. This is a 1-bit parameter: '0' = no support, '1' =
   support. */
#define SMIF_CRYPTO                     1u
/* Number of cryptography keys [0,1,2,4,8]; set to 0 if CRYPTO=0 */
#define SMIF_CRYPTO_KEY_NR              1u
/* Hardcoded 8-bit parameter (do NOT override) that allows crypto key 0 to take on
   additional registers to support MMIO encryption */
#define SMIF_CRYPTO_KEY_MMIO_CAPABLE    1u
/* Bus CRC support is present ([0,1]) Note: In MXS40 SMIF version 2 this option is
   currently not available (BUS_CRC_PRESENT=0). Based on project schedules this
   feature may be added already to MXS40 SMIF version 2 or to a later SMIF
   version. */
#define SMIF_BUS_CRC_PRESENT            0u
/* Number of external memory devices supported. This parameter is in the range
   [1,4]. */
#define SMIF_DEVICE_NR                  2u
/* External memory devices write support. This is a 4-bit field. Each external
   memory device has a dedicated bit. E.g., if bit 2 is '1', external device 2
   has write support. */
#define SMIF_DEVICE_WR_EN               3u
/* Number of delay lines ([1..8]). */
#define SMIF_DELAY_LINES_NR             4u
/* Number of delay taps in clock delay line. */
#define SMIF_DELAY_TAPS_NR              32u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SMIF_MASTER_WIDTH               6u
/* AXI ID width. Legal range [11,16] */
#define SMIF_AXIS_ID_WIDTH              16u
/* MPC SECEXT Present */
#define SMIF_MPC_SECEXT                 0u
/* Chip top connect all 8 data pins (0= connect 4 data pins, 1= connect 8 data
   pins) */
#define SMIF_CHIP_TOP_DATA8_PRESENT     0u
/* Number of used spi_select signals (max 4) */
#define SMIF_CHIP_TOP_SPI_SEL_NR        2u
/* S40S variant. Must be 1 when targeting S40S and 0 otherwise. */
#define SRSS_S40S_VARIANT               1u
/* S40E variant. Must be 1 when targeting S40E and 0 otherwise. */
#define SRSS_S40E_VARIANT               0u
/* Number of regulator modules instantiated within SRSS. Must be > 0. */
#define SRSS_NUM_ACTREG_PWRMOD          0u
/* Number of shorting switches between vccd and vccact. Must be > 0. */
#define SRSS_NUM_ACTIVE_SWITCH          2u
/* S40S variant. Number of shorting switches between vccd and vccdplsp for S40S
   REGSETB. Must be > 0. Has no affect when S40S_REGSETB_PRESENT=0 */
#define SRSS_NUM_DPSLP_SWITCH           6u
/* S40S Regulator Set A system is present */
#define SRSS_S40S_REGSETA_PRESENT       0u
/* S40E Regulator Set A system is present */
#define SRSS_S40E_REGSETA_PRESENT       0u
/* SIMO buck core regulator is present. Only compatible with S40S linear regulator
   system (S40S_LINREG_PRESENT==1). */
#define SRSS_S40S_SIMOBUCK_PRESENT      0u
/* Precision ILO (PILO) is present */
#define SRSS_S40S_PILO_PRESENT          1u
/* External Crystal Oscillator is present (high frequency) */
#define SRSS_ECO_PRESENT                0u
/* Number of clock paths. Must be > 0 */
#define SRSS_NUM_CLKPATH                4u
/* Number of PLLs present. Must be <= NUM_CLKPATH */
#define SRSS_NUM_PLL200M                0u
/* Number of HFCLK roots present. Must be > 0 */
#define SRSS_NUM_HFROOT                 4u
/* Number of PWR_HIB_DATA registers, should not be needed if BACKUP_PRESENT */
#define SRSS_NUM_HIBDATA                1u
/* Backup domain is present (includes RTC and WCO) */
#define SRSS_BACKUP_PRESENT             1u
/* CSV present. User must add one NUM_CLKPATH and one NUM_HFROOT to monitor ILO0
   with CSV_HF_REF clock. */
#define SRSS_CSV_PRESENT                0u
/* Number of software watchdog timers. */
#define SRSS_NUM_MCWDT                  1u
/* Number of DSI inputs into clock muxes. This is used for logic optimization. */
#define SRSS_NUM_DSI                    0u
/* Alternate high-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTHF_PRESENT              1u
/* Alternate low-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTLF_PRESENT              0u
/* Use the hardened clkactfllmux block */
#define SRSS_USE_HARD_CLKACTFLLMUX      1u
/* Number of clock paths, including direct paths in hardened clkactfllmux block
   (Must be >= NUM_CLKPATH) */
#define SRSS_HARD_CLKPATH               8u
/* Number of clock paths with muxes in hardened clkactfllmux block (Must be >=
   NUM_PLL+1) */
#define SRSS_HARD_CLKPATHMUX            8u
/* Number of HFCLKS present in hardened clkactfllmux block (Must be >= NUM_HFROOT) */
#define SRSS_HARD_HFROOT                8u
/* ECO mux is present in hardened clkactfllmux block (Must be >= ECO_PRESENT) */
#define SRSS_HARD_ECOMUX_PRESENT        1u
/* ALTHF mux is present in hardened clkactfllmux block (Must be >= ALTHF_PRESENT) */
#define SRSS_HARD_ALTHFMUX_PRESENT      1u
/* POR present. */
#define SRSS_POR_PRESENT                0u
/* Low-current buck regulator present. Can be derived from
   S40S_SISOBUCKLC_PRESENT, S40S_SISOBUCKMC_PRESENT or S40S_SIMOBUCK_PRESENT. */
#define SRSS_BUCKCTL_PRESENT            0u
/* Low-current SISO buck core regulator is present. Only compatible with S40S
   linear regulator system (S40S_LINREG_PRESENT==1). */
#define SRSS_S40S_SISOBUCKLC_PRESENT    0u
/* S40E linear regulator system is present */
#define SRSS_S40E_REGHC_PRESENT         0u
/* LPECO mux is present in hardened clkactfllmux block */
#define SRSS_HARD_LPECOMUX_PRESENT      1u
/* Number of 400MHz PLLs present. */
#define SRSS_NUM_PLL400M                0u
/* Mask of DIRECT_MUX defaults. For each clock root i, if bit[i] is low the
   DIRECT_MUX defaults to IMO. If bit[0] is high, the DIRECT_MUX selects the
   output of ROOT_MUX. For backward compatibility, M33-only systems can have all
   mask bits high. In all cases, must have bit[0]==1 to start the chip. */
#define SRSS_MASK_DIRECTMUX_DEF         65535u
/* Mask of which HFCLK roots are enabled when the debugger requests power up
   (CDBGPWRUPREQ). For each clock root i, SRSS enables the clock in response to
   CDBGPWRUPREQ, if bit[i] of mask is high. SRSS automatically enables clk_hf0,
   regardless of setting of mask bit0. */
#define SRSS_MASK_DEBUG_CLK             1u
/* Total number of PLLs present. */
#define SRSS_NUM_TOTAL_PLL              0u
/* PMIC control of vccd is present (without REGHC). */
#define SRSS_S40E_PMIC_PRESENT          0u
/* Number of multi-counter watchdog timers (type B). Software incompatibility with
   type A. */
#define SRSS_NUM_MCWDT_B                0u
/* WDT type A is present (backward compatible version) */
#define SRSS_WDT_A_PRESENT              1u
/* WDT type B is present. Software incompatibility with type A. */
#define SRSS_WDT_B_PRESENT              0u
/* Medium-current SISO buck core regulator is present. Only compatible with S40S
   linear regulator system (S40S_LINREG_PRESENT==1). */
#define SRSS_S40S_SISOBUCKMC_PRESENT    0u
/* Mask for whether a PD is present in the PDCM. The zeroth bit is the PD
   controlled by the main PPU and must always be set. */
#define SRSS_PDCM_PD_PRESENT            15u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT0_PDCM_PD_DEFAULT_ON 6u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT0_PDCM_PD_CONFIG_ON 9u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT1_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT1_PDCM_PD_CONFIG_ON 10u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT2_PDCM_PD_DEFAULT_ON 2u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT2_PDCM_PD_CONFIG_ON 14u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT3_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT3_PDCM_PD_CONFIG_ON 10u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT4_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT4_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT5_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT5_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT6_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT6_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT7_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT7_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT8_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT8_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT9_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT9_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT10_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT10_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT11_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT11_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT12_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT12_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT13_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT13_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT14_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT14_PDCM_PD_CONFIG_ON 0u
/* Mask of PDCM PD_FORCE_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_FORCE_ON[k%16]. For a non-configurable sense bit, a high
   value for bit k indicates whether PD<k/16> is always kept on when PD<k%16> is
   on. For configurable sense bits, this indicates the reset value of the
   configuration register. */
#define SRSS_PDCM_PD_PRESENT15_PDCM_PD_DEFAULT_ON 0u
/* Mask of PDCM PD_CONFIG_ON bits. Each bit k maps to
   PD_SPT[k/16].PD_CONFIG_ON[k%16]. A high value for bit k indicates whether
   PD<k/16> can be configured on when PD<k%16> is on. */
#define SRSS_PDCM_PD_PRESENT15_PDCM_PD_CONFIG_ON 0u
/* FLL present */
#define SRSS_FLL_PRESENT                1u
/* S40S Regulator Set B system is present */
#define SRSS_S40S_REGSETB_PRESENT       1u
/* S40S Regulator Set B Nwell regulator is present */
#define SRSS_S40S_REGSETB_NW_PRESENT    0u
/* Number of additional HIBERNATE wakeup sources */
#define SRSS_NUM_HIB_WAKE               4u
/* CSV_BAK is present. Monitors clk_bak_hv using clk_ilo0_hv. */
#define SRSS_CSV_BAK_PRESENT            0u
/* HVLDO0 present */
#define SRSS_S40S_REGSETB_HVLDO0_PRESENT 1u
/* Width of the WDT (Type A) counter. For backward compatibility, the minimum
   allowed is 16b. */
#define SRSS_NUM_WDT_A_BITS             22u
/* Separate power supply Vbackup is present (only used when BACKUP_PRESENT==1) */
#define SRSS_BACKUP_VBCK_PRESENT        0u
/* Alarm1 present in RTC */
#define SRSS_BACKUP_ALM1_PRESENT        1u
/* Alarm2 present in RTC */
#define SRSS_BACKUP_ALM2_PRESENT        1u
/* Backup memory is present (only used when BACKUP_PRESENT==1) */
#define SRSS_BACKUP_BMEM_PRESENT        0u
/* Number of Backup registers to include (each is 32b). Only used when
   BACKUP_PRESENT==1. Approximate size is 850squm per register. */
#define SRSS_BACKUP_NUM_BREG0           4u
/* Number of Backup registers to include (each is 32b). Only used when
   BACKUP_PRESENT==1. Approximate size is 850squm per register. */
#define SRSS_BACKUP_NUM_BREG1           4u
/* Number of Backup registers to include (each is 32b). Only used when
   BACKUP_PRESENT==1. Approximate size is 850squm per register. */
#define SRSS_BACKUP_NUM_BREG2           8u
/* Number of Backup registers to include (each is 32b). Only used when
   BACKUP_PRESENT==1. Approximate size is 850squm per register. */
#define SRSS_BACKUP_NUM_BREG3           0u
/* Low power external crystal oscillator (LPECO) is present. */
#define SRSS_BACKUP_S40E_LPECO_PRESENT  0u
/* CSV_BAK is present. Monitors clk_bak_hv using clk_ilo0_hv. */
#define SRSS_BACKUP_CSV_BAK_PRESENT     0u
/* S40S variant. Must be 1 when targeting S40S and 0 otherwise. */
#define SRSS_CLK_TRIM_PLL400M_S40S_VARIANT 1u
/* Mask of HFCLK root clock supervisors (CSV). For each clock root i, bit[i] of
   mask indicates presence of a CSV. */
#define SRSS_CSV_HF_MASK_HFCSV          0u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define TCPWM_MASTER_WIDTH              8u
/* Number of input triggers per counter only routed to one counter (0..8) */
#define TCPWM_TR_ONE_CNT_NR             1u
/* Number of input triggers routed to all counters (0..254),
   NR_TR_ONE_CNT+NR_TR_ALL CNT <= 254 */
#define TCPWM_TR_ALL_CNT_NR             28u
/* Number of TCPWM counter groups (1..4) */
#define TCPWM_GRP_NR                    2u
/* Counter width in number of bits per TCPWM group (16: 16-bits, 32: 32-bits) */
#define TCPWM_GRP_NR0_CNT_GRP_CNT_WIDTH 32u
/* Second Capture / Compare Unit is present (0, 1) */
#define TCPWM_GRP_NR0_CNT_GRP_CC1_PRESENT 0u
/* Advanced Motor Control features are present (0, 1). Should only be 1 when
   GRP_CC1_PRESENT = 1 */
#define TCPWM_GRP_NR0_CNT_GRP_AMC_PRESENT 0u
/* Stepper Motor Control features are present (0, 1). */
#define TCPWM_GRP_NR0_CNT_GRP_SMC_PRESENT 0u
/* Number of counters per TCPWM group (1..256) */
#define TCPWM_GRP_NR0_GRP_GRP_CNT_NR    2u
/* Counter width in number of bits per TCPWM group (16: 16-bits, 32: 32-bits) */
#define TCPWM_GRP_NR1_CNT_GRP_CNT_WIDTH 16u
/* Second Capture / Compare Unit is present (0, 1) */
#define TCPWM_GRP_NR1_CNT_GRP_CC1_PRESENT 1u
/* Advanced Motor Control features are present (0, 1). Should only be 1 when
   GRP_CC1_PRESENT = 1 */
#define TCPWM_GRP_NR1_CNT_GRP_AMC_PRESENT 1u
/* Stepper Motor Control features are present (0, 1). */
#define TCPWM_GRP_NR1_CNT_GRP_SMC_PRESENT 0u
/* Number of counters per TCPWM group (1..256) */
#define TCPWM_GRP_NR1_GRP_GRP_CNT_NR    7u
/* Number of AHB-Lite "hmaster[]" bits ([4, 8]). */
#define TDM_MASTER_WIDTH                8u
/* Number of TDM structures ({1, 2, 3, 4}]). */
#define TDM_NR                          1u
/* Number of channels per TDM structure. */
#define TDM_NR_CH_NR                    2u
/* Number of channels per TDM structure. */
#define TDM_NR_TDM_RX_STRUCT_CH_NR      2u
/* Number of channels per TDM structure. */
#define TDM_NR_TDM_TX_STRUCT_CH_NR      2u
/* Spare Enable 0=no spare, 1=max, 2=min */
#define TDM_SPARE_EN                    1u
/* 0=ULL65, 1=MXS40-ULP, 2=MXS40E, 3=M0S8, 4=MXS40-HD, 5=F45, 6=MXS40v2, 7=T28HPM,
   8=T28HPL, 9=T28HPC */
#define TDM_PLATFORM_VARIANT            6u
/* SRAM vendor ({0=Cypress, 1=Synopsys, 2=ARM, 3=BRCM}) */
#define TDM_RAM_VEND                    1u
/* Use mxsramwrap IP */
#define TDM_MXSRAMWRAP_EN               1u
/* Number of connected clocks at the IP's top level ([1, 4]). */
#define TDM_CHIP_TOP_CLK_NR             1u
/* Replay functionality for transmitter. This functionality adds significant
   silicon area. */
#define TDM_TDM_TX_STRUCT_REPLAY_PRESENT 0u

/* MMIO Targets Defines */
#define CY_MMIO_SRSS_GROUP_NR           0u
#define CY_MMIO_SRSS_SLAVE_NR           4u
#define CY_MMIO_PWRMODE_GROUP_NR        0u
#define CY_MMIO_PWRMODE_SLAVE_NR        5u
#define CY_MMIO_BACKUP_GROUP_NR         0u
#define CY_MMIO_BACKUP_SLAVE_NR         6u
#define CY_MMIO_CRYPTO_GROUP_NR         0u
#define CY_MMIO_CRYPTO_SLAVE_NR         7u
#define CY_MMIO_HSIOM_GROUP_NR          1u
#define CY_MMIO_HSIOM_SLAVE_NR          0u
#define CY_MMIO_GPIO_GROUP_NR           1u
#define CY_MMIO_GPIO_SLAVE_NR           1u
#define CY_MMIO_SMARTIO_GROUP_NR        1u
#define CY_MMIO_SMARTIO_SLAVE_NR        2u
#define CY_MMIO_LIN0_GROUP_NR           1u
#define CY_MMIO_LIN0_SLAVE_NR           3u
#define CY_MMIO_CANFD0_GROUP_NR         1u
#define CY_MMIO_CANFD0_SLAVE_NR         4u
#define CY_MMIO_TCPWM0_GROUP_NR         1u
#define CY_MMIO_TCPWM0_SLAVE_NR         5u
#define CY_MMIO_MXS40ADCMIC0_GROUP_NR   1u
#define CY_MMIO_MXS40ADCMIC0_SLAVE_NR   6u
#define CY_MMIO_SCB0_GROUP_NR           1u
#define CY_MMIO_SCB0_SLAVE_NR           7u
#define CY_MMIO_SCB01_GROUP_NR          1u
#define CY_MMIO_SCB01_SLAVE_NR          8u
#define CY_MMIO_SCB02_GROUP_NR          1u
#define CY_MMIO_SCB02_SLAVE_NR          9u
#define CY_MMIO_DFT_GROUP_NR            2u
#define CY_MMIO_DFT_SLAVE_NR            0u
#define CY_MMIO_EFUSE_GROUP_NR          2u
#define CY_MMIO_EFUSE_SLAVE_NR          1u
#define CY_MMIO_SMIF0_GROUP_NR          2u
#define CY_MMIO_SMIF0_SLAVE_NR          2u
#define CY_MMIO_TDM0_GROUP_NR           2u
#define CY_MMIO_TDM0_SLAVE_NR           3u
#define CY_MMIO_PDM0_GROUP_NR           2u
#define CY_MMIO_PDM0_SLAVE_NR           4u
#define CY_MMIO_KEYSCAN_GROUP_NR        2u
#define CY_MMIO_KEYSCAN_SLAVE_NR        5u
#define CY_MMIO_BTSS_GROUP_NR           3u
#define CY_MMIO_BTSS_SLAVE_NR           0u

/* Protection regions */
typedef enum
{
    PROT_PERI_MAIN                  =   0,      /* Address 0x40000000, size 0x00004000 */
    PROT_PERI_GR0_GROUP             =   1,      /* Address 0x40004010, size 0x00000008 */
    PROT_PERI_GR1_GROUP             =   2,      /* Address 0x40004040, size 0x00000020 */
    PROT_PERI_GR2_GROUP             =   3,      /* Address 0x40004080, size 0x00000020 */
    PROT_PERI_GR3_GROUP             =   4,      /* Address 0x400040d0, size 0x00000010 */
    PROT_PERI_GR0_BOOT              =   5,      /* Address 0x40004020, size 0x00000004 */
    PROT_PERI_GR1_BOOT              =   6,      /* Address 0x40004060, size 0x00000004 */
    PROT_PERI_GR2_BOOT              =   7,      /* Address 0x400040a0, size 0x00000004 */
    PROT_PERI_GR3_BOOT              =   8,      /* Address 0x400040e0, size 0x00000004 */
    PROT_PERI_TR                    =   9,      /* Address 0x40008000, size 0x00008000 */
    PROT_PPC_PPC_SECURE             =  10,      /* Address 0x40020000, size 0x00004000 */
    PROT_PPC_PPC_NONSECURE          =  11,      /* Address 0x40024000, size 0x00004000 */
    PROT_PERI_PCLK_MAIN             =  12,      /* Address 0x40040000, size 0x00010000 */
    PROT_CPUSS                      =  13,      /* Address 0x40100000, size 0x00010000 */
    PROT_RAMC0_CM33                 =  14,      /* Address 0x40110000, size 0x00000010 */
    PROT_RAMC0_BOOT                 =  15,      /* Address 0x40110100, size 0x00000004 */
    PROT_RAMC0_RAM_PWR              =  16,      /* Address 0x40110200, size 0x00000100 */
    PROT_RAMC0_MPC0_PPC_MPC_MAIN    =  17,      /* Address 0x40114000, size 0x00000040 */
    PROT_RAMC0_MPC0_PPC_MPC_PC      =  18,      /* Address 0x40114100, size 0x00000020 */
    PROT_RAMC0_MPC0_PPC_MPC_ROT     =  19,      /* Address 0x40114200, size 0x00000020 */
    PROT_PROMC_CM33                 =  20,      /* Address 0x40140000, size 0x00000004 */
    PROT_PROMC_MPC0_PPC_MPC_MAIN    =  21,      /* Address 0x40141000, size 0x00000040 */
    PROT_PROMC_MPC0_PPC_MPC_PC      =  22,      /* Address 0x40141100, size 0x00000020 */
    PROT_PROMC_MPC0_PPC_MPC_ROT     =  23,      /* Address 0x40141200, size 0x00000020 */
    PROT_MXCM33_CM33                =  24,      /* Address 0x40160000, size 0x00000100 */
    PROT_MXCM33_CM33_NS             =  25,      /* Address 0x40161004, size 0x00000004 */
    PROT_MXCM33_BOOT                =  26,      /* Address 0x40162000, size 0x00000100 */
    PROT_MXCM33_CM33_INT            =  27,      /* Address 0x40168000, size 0x00000200 */
    PROT_DW0_DW                     =  28,      /* Address 0x40180000, size 0x00000080 */
    PROT_DW0_DW_CRC                 =  29,      /* Address 0x40180100, size 0x00000080 */
    PROT_DW0_CH_STRUCT0_CH          =  30,      /* Address 0x40188000, size 0x00000040 */
    PROT_DW0_CH_STRUCT1_CH          =  31,      /* Address 0x40188040, size 0x00000040 */
    PROT_DW0_CH_STRUCT2_CH          =  32,      /* Address 0x40188080, size 0x00000040 */
    PROT_DW0_CH_STRUCT3_CH          =  33,      /* Address 0x401880c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT4_CH          =  34,      /* Address 0x40188100, size 0x00000040 */
    PROT_DW0_CH_STRUCT5_CH          =  35,      /* Address 0x40188140, size 0x00000040 */
    PROT_DW0_CH_STRUCT6_CH          =  36,      /* Address 0x40188180, size 0x00000040 */
    PROT_DW0_CH_STRUCT7_CH          =  37,      /* Address 0x401881c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT8_CH          =  38,      /* Address 0x40188200, size 0x00000040 */
    PROT_DW0_CH_STRUCT9_CH          =  39,      /* Address 0x40188240, size 0x00000040 */
    PROT_DW0_CH_STRUCT10_CH         =  40,      /* Address 0x40188280, size 0x00000040 */
    PROT_DW0_CH_STRUCT11_CH         =  41,      /* Address 0x401882c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT12_CH         =  42,      /* Address 0x40188300, size 0x00000040 */
    PROT_DW0_CH_STRUCT13_CH         =  43,      /* Address 0x40188340, size 0x00000040 */
    PROT_DW0_CH_STRUCT14_CH         =  44,      /* Address 0x40188380, size 0x00000040 */
    PROT_DW0_CH_STRUCT15_CH         =  45,      /* Address 0x401883c0, size 0x00000040 */
    PROT_CPUSS_ALL_PC               =  46,      /* Address 0x401c0000, size 0x00000080 */
    PROT_CPUSS_DDFT                 =  47,      /* Address 0x401c0080, size 0x00000004 */
    PROT_CPUSS_CM33_NS              =  48,      /* Address 0x401c0120, size 0x00000004 */
    PROT_CPUSS_AHB_ERR_INT          =  49,      /* Address 0x401c0200, size 0x00000040 */
    PROT_CPUSS_AP                   =  50,      /* Address 0x401c1000, size 0x00000004 */
    PROT_CPUSS_BOOT                 =  51,      /* Address 0x401c2000, size 0x00000200 */
    PROT_MS0_MAIN                   =  52,      /* Address 0x401c4000, size 0x00000004 */
    PROT_MS4_MAIN                   =  53,      /* Address 0x401c4040, size 0x00000004 */
    PROT_MS7_MAIN                   =  54,      /* Address 0x401c4070, size 0x00000004 */
    PROT_MS9_MAIN                   =  55,      /* Address 0x401c4090, size 0x00000004 */
    PROT_MS31_MAIN                  =  56,      /* Address 0x401c41f0, size 0x00000004 */
    PROT_MS_PC0_PRIV                =  57,      /* Address 0x401c5000, size 0x00000004 */
    PROT_MS_PC9_PRIV                =  58,      /* Address 0x401c5090, size 0x00000004 */
    PROT_MS_PC31_PRIV               =  59,      /* Address 0x401c51f0, size 0x00000004 */
    PROT_MS_PC0_PRIV_MIR            =  60,      /* Address 0x401c5004, size 0x00000004 */
    PROT_MS_PC9_PRIV_MIR            =  61,      /* Address 0x401c5094, size 0x00000004 */
    PROT_MS_PC31_PRIV_MIR           =  62,      /* Address 0x401c51f4, size 0x00000004 */
    PROT_MSC_ACG                    =  63,      /* Address 0x401c6000, size 0x00000040 */
    PROT_CPUSS_SL_CTL_GROUP         =  64,      /* Address 0x401c8000, size 0x00000008 */
    PROT_IPC_STRUCT0_IPC            =  65,      /* Address 0x401d0000, size 0x00000020 */
    PROT_IPC_STRUCT1_IPC            =  66,      /* Address 0x401d0020, size 0x00000020 */
    PROT_IPC_STRUCT2_IPC            =  67,      /* Address 0x401d0040, size 0x00000020 */
    PROT_IPC_STRUCT3_IPC            =  68,      /* Address 0x401d0060, size 0x00000020 */
    PROT_IPC_INTR_STRUCT0_INTR      =  69,      /* Address 0x401d1000, size 0x00000010 */
    PROT_IPC_INTR_STRUCT1_INTR      =  70,      /* Address 0x401d1020, size 0x00000010 */
    PROT_SRSS_GENERAL               =  71,      /* Address 0x40200000, size 0x00000400 */
    PROT_SRSS_GENERAL2              =  72,      /* Address 0x40200400, size 0x00000020 */
    PROT_SRSS_HIB_DATA              =  73,      /* Address 0x40200800, size 0x00000100 */
    PROT_SRSS_MAIN                  =  74,      /* Address 0x40201000, size 0x00001000 */
    PROT_SRSS_SECURE                =  75,      /* Address 0x40202000, size 0x00002000 */
    PROT_SRSS_WDT                   =  76,      /* Address 0x4020c000, size 0x00000010 */
    PROT_MAIN                       =  77,      /* Address 0x4020d000, size 0x00000040 */
    PROT_PWRMODE_PWRMODE            =  78,      /* Address 0x40210000, size 0x00004000 */
    PROT_BACKUP_BACKUP              =  79,      /* Address 0x40220000, size 0x00000100 */
    PROT_BACKUP_B_BREG0             =  80,      /* Address 0x40221000, size 0x00000010 */
    PROT_BACKUP_B_BREG1             =  81,      /* Address 0x40221010, size 0x00000010 */
    PROT_BACKUP_B_BREG2             =  82,      /* Address 0x40221020, size 0x00000020 */
    PROT_BACKUP_BACKUP_SECURE       =  83,      /* Address 0x4022ff00, size 0x00000004 */
    PROT_CRYPTO_MAIN                =  84,      /* Address 0x40230000, size 0x00000100 */
    PROT_HSIOM_PRT0_PRT             =  85,      /* Address 0x40400000, size 0x00000008 */
    PROT_HSIOM_PRT1_PRT             =  86,      /* Address 0x40400010, size 0x00000008 */
    PROT_HSIOM_PRT2_PRT             =  87,      /* Address 0x40400020, size 0x00000008 */
    PROT_HSIOM_PRT3_PRT             =  88,      /* Address 0x40400030, size 0x00000008 */
    PROT_HSIOM_PRT4_PRT             =  89,      /* Address 0x40400040, size 0x00000008 */
    PROT_HSIOM_PRT5_PRT             =  90,      /* Address 0x40400050, size 0x00000008 */
    PROT_HSIOM_AMUX                 =  91,      /* Address 0x40402000, size 0x00000004 */
    PROT_HSIOM_MON                  =  92,      /* Address 0x40402200, size 0x00000010 */
    PROT_GPIO_PRT0_PRT              =  93,      /* Address 0x40410000, size 0x00000040 */
    PROT_GPIO_PRT1_PRT              =  94,      /* Address 0x40410080, size 0x00000040 */
    PROT_GPIO_PRT2_PRT              =  95,      /* Address 0x40410100, size 0x00000040 */
    PROT_GPIO_PRT3_PRT              =  96,      /* Address 0x40410180, size 0x00000040 */
    PROT_GPIO_PRT4_PRT              =  97,      /* Address 0x40410200, size 0x00000040 */
    PROT_GPIO_PRT5_PRT              =  98,      /* Address 0x40410280, size 0x00000040 */
    PROT_GPIO_PRT0_CFG              =  99,      /* Address 0x40410040, size 0x00000040 */
    PROT_GPIO_PRT1_CFG              = 100,      /* Address 0x404100c0, size 0x00000040 */
    PROT_GPIO_PRT2_CFG              = 101,      /* Address 0x40410140, size 0x00000040 */
    PROT_GPIO_PRT3_CFG              = 102,      /* Address 0x404101c0, size 0x00000040 */
    PROT_GPIO_PRT4_CFG              = 103,      /* Address 0x40410240, size 0x00000040 */
    PROT_GPIO_PRT5_CFG              = 104,      /* Address 0x404102c0, size 0x00000040 */
    PROT_GPIO_GPIO                  = 105,      /* Address 0x40418000, size 0x00000040 */
    PROT_GPIO_TEST                  = 106,      /* Address 0x40419000, size 0x00000008 */
    PROT_SMARTIO_PRT3_PRT           = 107,      /* Address 0x40420300, size 0x00000100 */
    PROT_LIN0_MAIN                  = 108,      /* Address 0x40430000, size 0x00000008 */
    PROT_LIN0_CH0_CH                = 109,      /* Address 0x40438000, size 0x00000100 */
    PROT_LIN0_CH1_CH                = 110,      /* Address 0x40438100, size 0x00000100 */
    PROT_CANFD0_CH0_CH              = 111,      /* Address 0x40440000, size 0x00000200 */
    PROT_CANFD0_MAIN                = 112,      /* Address 0x40441000, size 0x00000040 */
    PROT_CANFD0_BUF                 = 113,      /* Address 0x40450000, size 0x00010000 */
    PROT_TCPWM0_GRP0_CNT0_CNT       = 114,      /* Address 0x404a0000, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT1_CNT       = 115,      /* Address 0x404a0080, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT0_CNT       = 116,      /* Address 0x404a8000, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT1_CNT       = 117,      /* Address 0x404a8080, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT2_CNT       = 118,      /* Address 0x404a8100, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT3_CNT       = 119,      /* Address 0x404a8180, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT4_CNT       = 120,      /* Address 0x404a8200, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT5_CNT       = 121,      /* Address 0x404a8280, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT6_CNT       = 122,      /* Address 0x404a8300, size 0x00000080 */
    PROT_MXS40ADCMIC0_MAIN          = 123,      /* Address 0x40520000, size 0x00000400 */
    PROT_SCB0                       = 124,      /* Address 0x40590000, size 0x00010000 */
    PROT_SCB1                       = 125,      /* Address 0x405a0000, size 0x00010000 */
    PROT_SCB2                       = 126,      /* Address 0x405b0000, size 0x00010000 */
    PROT_DFT                        = 127,      /* Address 0x40800000, size 0x00001000 */
    PROT_EFUSE_CTL1                 = 128,      /* Address 0x40810000, size 0x00000004 */
    PROT_EFUSE_CTL2                 = 129,      /* Address 0x40810100, size 0x00000080 */
    PROT_EFUSE_CTL3                 = 130,      /* Address 0x40810180, size 0x00000004 */
    PROT_EFUSE_DATA_BOOT1           = 131,      /* Address 0x40810800, size 0x00000020 */
    PROT_EFUSE_DATA_BOOT2           = 132,      /* Address 0x40810820, size 0x00000010 */
    PROT_EFUSE_DATA_BOOT3           = 133,      /* Address 0x40810830, size 0x00000004 */
    PROT_EFUSE_DATA_BLESS1          = 134,      /* Address 0x40810834, size 0x00000004 */
    PROT_EFUSE_DATA_BLESS2          = 135,      /* Address 0x40810838, size 0x00000004 */
    PROT_EFUSE_DATA_BLESS3          = 136,      /* Address 0x4081083c, size 0x00000004 */
    PROT_EFUSE_DATA_APP1            = 137,      /* Address 0x40810840, size 0x00000010 */
    PROT_EFUSE_DATA_APP2            = 138,      /* Address 0x40810850, size 0x00000010 */
    PROT_EFUSE_DATA_APP3            = 139,      /* Address 0x40810860, size 0x00000010 */
    PROT_EFUSE_DATA_ALL             = 140,      /* Address 0x40810870, size 0x00000010 */
    PROT_SMIF0_MAIN                 = 141,      /* Address 0x40890000, size 0x00001000 */
    PROT_SMIF0_MPC0_PPC_MPC_MAIN    = 142,      /* Address 0x40891000, size 0x00000040 */
    PROT_SMIF0_MPC0_PPC_MPC_PC      = 143,      /* Address 0x40891100, size 0x00000020 */
    PROT_SMIF0_MPC0_PPC_MPC_ROT     = 144,      /* Address 0x40891200, size 0x00000020 */
    PROT_TDM0_TDM_STRUCT0_TDM_TX_STRUCT_TX = 145, /* Address 0x408c8000, size 0x00000100 */
    PROT_TDM0_TDM_STRUCT0_TDM_RX_STRUCT_RX = 146, /* Address 0x408c8100, size 0x00000100 */
    PROT_PDM0_MAIN                  = 147,      /* Address 0x408d0000, size 0x00000200 */
    PROT_PDM0_CH0_RX                = 148,      /* Address 0x408d8000, size 0x00000100 */
    PROT_PDM0_CH1_RX                = 149,      /* Address 0x408d8100, size 0x00000100 */
    PROT_MXKEYSCAN_MAIN             = 150,      /* Address 0x40920000, size 0x00000040 */
    PROT_BTSS_ROM                   = 151,      /* Address 0x42000000, size 0x00400000 */
    PROT_BTSS_SYSRAM                = 152,      /* Address 0x42400000, size 0x00004000 */
    PROT_BTSS_DATA_RAM_IPC          = 153,      /* Address 0x42600000, size 0x00100000 */
    PROT_BTSS_DRIVER                = 154,      /* Address 0x42a00000, size 0x00100000 */
    PROT_BTSS_FWONLY                = 155,      /* Address 0x42b00000, size 0x00100000 */
    PROT_BTSS_SECURE                = 156       /* Address 0x42f00000, size 0x00100000 */
} cy_en_prot_region_t;

#endif /* _CYW20829_CONFIG_H_ */


/* [] END OF FILE */
