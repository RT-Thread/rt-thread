/***************************************************************************//**
* \file psoc6_03_config.h
*
* \brief
* PSoC6_03 device configuration header
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

#ifndef _PSOC6_03_CONFIG_H_
#define _PSOC6_03_CONFIG_H_

/* Clock Connections */
typedef enum
{
    PCLK_SCB0_CLOCK                 = 0x0000u,  /* scb[0].clock */
    PCLK_SCB1_CLOCK                 = 0x0001u,  /* scb[1].clock */
    PCLK_SCB2_CLOCK                 = 0x0002u,  /* scb[2].clock */
    PCLK_SCB3_CLOCK                 = 0x0003u,  /* scb[3].clock */
    PCLK_SCB4_CLOCK                 = 0x0004u,  /* scb[4].clock */
    PCLK_SCB5_CLOCK                 = 0x0005u,  /* scb[5].clock */
    PCLK_SCB6_CLOCK                 = 0x0006u,  /* scb[6].clock */
    PCLK_SMARTIO8_CLOCK             = 0x0007u,  /* smartio[8].clock */
    PCLK_SMARTIO9_CLOCK             = 0x0008u,  /* smartio[9].clock */
    PCLK_TCPWM0_CLOCKS0             = 0x0009u,  /* tcpwm[0].clocks[0] */
    PCLK_TCPWM0_CLOCKS1             = 0x000Au,  /* tcpwm[0].clocks[1] */
    PCLK_TCPWM0_CLOCKS2             = 0x000Bu,  /* tcpwm[0].clocks[2] */
    PCLK_TCPWM0_CLOCKS3             = 0x000Cu,  /* tcpwm[0].clocks[3] */
    PCLK_TCPWM1_CLOCKS0             = 0x000Du,  /* tcpwm[1].clocks[0] */
    PCLK_TCPWM1_CLOCKS1             = 0x000Eu,  /* tcpwm[1].clocks[1] */
    PCLK_TCPWM1_CLOCKS2             = 0x000Fu,  /* tcpwm[1].clocks[2] */
    PCLK_TCPWM1_CLOCKS3             = 0x0010u,  /* tcpwm[1].clocks[3] */
    PCLK_TCPWM1_CLOCKS4             = 0x0011u,  /* tcpwm[1].clocks[4] */
    PCLK_TCPWM1_CLOCKS5             = 0x0012u,  /* tcpwm[1].clocks[5] */
    PCLK_TCPWM1_CLOCKS6             = 0x0013u,  /* tcpwm[1].clocks[6] */
    PCLK_TCPWM1_CLOCKS7             = 0x0014u,  /* tcpwm[1].clocks[7] */
    PCLK_CSD_CLOCK                  = 0x0015u,  /* csd.clock */
    PCLK_LCD_CLOCK                  = 0x0016u,  /* lcd.clock */
    PCLK_CPUSS_CLOCK_TRACE_IN       = 0x0017u,  /* cpuss.clock_trace_in */
    PCLK_PASS_CLOCK_PUMP_PERI       = 0x0018u,  /* pass.clock_pump_peri */
    PCLK_PASS_CLOCK_SAR             = 0x0019u,  /* pass.clock_sar */
    PCLK_CANFD0_CLOCK_CAN0          = 0x001Au,  /* canfd[0].clock_can[0] */
    PCLK_USB_CLOCK_DEV_BRS          = 0x001Bu   /* usb.clock_dev_brs */
} en_clk_dst_t;

/* Trigger Group */
/* This section contains the enums related to the Trigger multiplexer (TrigMux) driver.
* Refer to the Cypress Peripheral Driver Library Documentation, section Trigger multiplexer (TrigMux) -> Enumerated Types for details.
*/
/* Trigger Group Inputs */
/* Trigger Input Group 0 - PDMA0 Request Assignments */
typedef enum
{
    TRIG_IN_MUX_0_PDMA0_TR_OUT0     = 0x00000001u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT1     = 0x00000002u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT2     = 0x00000003u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT3     = 0x00000004u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT4     = 0x00000005u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT5     = 0x00000006u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT6     = 0x00000007u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT7     = 0x00000008u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT0     = 0x00000009u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT1     = 0x0000000Au, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT2     = 0x0000000Bu, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT3     = 0x0000000Cu, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT4     = 0x0000000Du, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT5     = 0x0000000Eu, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT6     = 0x0000000Fu, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT7     = 0x00000010u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_0_TCPWM0_TR_OVERFLOW0 = 0x00000011u, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_0_TCPWM0_TR_COMPARE_MATCH0 = 0x00000012u, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_0_TCPWM0_TR_UNDERFLOW0 = 0x00000013u, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_0_TCPWM0_TR_OVERFLOW1 = 0x00000014u, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_0_TCPWM0_TR_COMPARE_MATCH1 = 0x00000015u, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_0_TCPWM0_TR_UNDERFLOW1 = 0x00000016u, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_0_TCPWM0_TR_OVERFLOW2 = 0x00000017u, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_0_TCPWM0_TR_COMPARE_MATCH2 = 0x00000018u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_0_TCPWM0_TR_UNDERFLOW2 = 0x00000019u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_0_TCPWM0_TR_OVERFLOW3 = 0x0000001Au, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_0_TCPWM0_TR_COMPARE_MATCH3 = 0x0000001Bu, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_0_TCPWM0_TR_UNDERFLOW3 = 0x0000001Cu, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW0 = 0x0000001Du, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH0 = 0x0000001Eu, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW0 = 0x0000001Fu, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW1 = 0x00000020u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH1 = 0x00000021u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW1 = 0x00000022u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW2 = 0x00000023u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH2 = 0x00000024u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW2 = 0x00000025u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW3 = 0x00000026u, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH3 = 0x00000027u, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW3 = 0x00000028u, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW4 = 0x00000029u, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH4 = 0x0000002Au, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW4 = 0x0000002Bu, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW5 = 0x0000002Cu, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH5 = 0x0000002Du, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW5 = 0x0000002Eu, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW6 = 0x0000002Fu, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH6 = 0x00000030u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW6 = 0x00000031u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_0_TCPWM1_TR_OVERFLOW7 = 0x00000032u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_0_TCPWM1_TR_COMPARE_MATCH7 = 0x00000033u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_0_TCPWM1_TR_UNDERFLOW7 = 0x00000034u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_0_MDMA_TR_OUT0      = 0x00000041u, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_0_MDMA_TR_OUT1      = 0x00000042u, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT0     = 0x00000045u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT1     = 0x00000046u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT2     = 0x00000047u, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT3     = 0x00000048u, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT4     = 0x00000049u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT5     = 0x0000004Au, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT6     = 0x0000004Bu, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT7     = 0x0000004Cu, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT8     = 0x0000004Du, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT9     = 0x0000004Eu, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT10    = 0x0000004Fu, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT11    = 0x00000050u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT12    = 0x00000051u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_0_HSIOM_TR_OUT13    = 0x00000052u, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_0_CTI_TR_OUT0       = 0x00000053u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_0_CTI_TR_OUT1       = 0x00000054u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_0_FAULT_TR_OUT0     = 0x00000055u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_0_FAULT_TR_OUT1     = 0x00000056u /* cpuss.tr_fault[1] */
} en_trig_input_pdma0_tr_t;

/* Trigger Input Group 1 - PDMA1 Request Assignments */
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
    TRIG_IN_MUX_1_PDMA1_TR_OUT0     = 0x00000109u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT1     = 0x0000010Au, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT2     = 0x0000010Bu, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT3     = 0x0000010Cu, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT4     = 0x0000010Du, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT5     = 0x0000010Eu, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT6     = 0x0000010Fu, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_1_PDMA1_TR_OUT7     = 0x00000110u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_1_MDMA_TR_OUT0      = 0x00000141u, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_1_MDMA_TR_OUT1      = 0x00000142u, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_1_CSD_ADC_DONE      = 0x00000145u, /* csd.tr_adc_done */
    TRIG_IN_MUX_1_HSIOM_TR_OUT14    = 0x00000146u, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT15    = 0x00000147u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT16    = 0x00000148u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT17    = 0x00000149u, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT18    = 0x0000014Au, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT19    = 0x0000014Bu, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT20    = 0x0000014Cu, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT21    = 0x0000014Du, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT22    = 0x0000014Eu, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT23    = 0x0000014Fu, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT24    = 0x00000150u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_1_HSIOM_TR_OUT25    = 0x00000151u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_1_LPCOMP_DSI_COMP0  = 0x00000154u, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_1_LPCOMP_DSI_COMP1  = 0x00000155u, /* lpcomp.dsi_comp1 */
    TRIG_IN_MUX_1_CANFD_TT_TR_OUT0  = 0x00000156u /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_pdma1_tr_t;

/* Trigger Input Group 2 - TCPWM0 trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_2_PDMA0_TR_OUT0     = 0x00000201u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT1     = 0x00000202u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT2     = 0x00000203u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT3     = 0x00000204u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT4     = 0x00000205u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT5     = 0x00000206u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT6     = 0x00000207u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT7     = 0x00000208u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_2_TCPWM0_TR_OVERFLOW0 = 0x00000209u, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_2_TCPWM0_TR_COMPARE_MATCH0 = 0x0000020Au, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_2_TCPWM0_TR_UNDERFLOW0 = 0x0000020Bu, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_2_TCPWM0_TR_OVERFLOW1 = 0x0000020Cu, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_2_TCPWM0_TR_COMPARE_MATCH1 = 0x0000020Du, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_2_TCPWM0_TR_UNDERFLOW1 = 0x0000020Eu, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_2_TCPWM0_TR_OVERFLOW2 = 0x0000020Fu, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_2_TCPWM0_TR_COMPARE_MATCH2 = 0x00000210u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_2_TCPWM0_TR_UNDERFLOW2 = 0x00000211u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_2_TCPWM0_TR_OVERFLOW3 = 0x00000212u, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_2_TCPWM0_TR_COMPARE_MATCH3 = 0x00000213u, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_2_TCPWM0_TR_UNDERFLOW3 = 0x00000214u, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW0 = 0x00000221u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH0 = 0x00000222u, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW0 = 0x00000223u, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW1 = 0x00000224u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH1 = 0x00000225u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW1 = 0x00000226u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW2 = 0x00000227u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH2 = 0x00000228u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW2 = 0x00000229u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW3 = 0x0000022Au, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH3 = 0x0000022Bu, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW3 = 0x0000022Cu, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW4 = 0x0000022Du, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH4 = 0x0000022Eu, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW4 = 0x0000022Fu, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW5 = 0x00000230u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH5 = 0x00000231u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW5 = 0x00000232u, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW6 = 0x00000233u, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH6 = 0x00000234u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW6 = 0x00000235u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_2_TCPWM1_TR_OVERFLOW7 = 0x00000236u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_2_TCPWM1_TR_COMPARE_MATCH7 = 0x00000237u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_2_TCPWM1_TR_UNDERFLOW7 = 0x00000238u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_2_MDMA_TR_OUT0      = 0x00000239u, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_2_MDMA_TR_OUT1      = 0x0000023Au, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_2_SCB_I2C_SCL0      = 0x0000023Du, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX0           = 0x0000023Eu, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX0           = 0x0000023Fu, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL1      = 0x00000240u, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX1           = 0x00000241u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX1           = 0x00000242u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL2      = 0x00000243u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX2           = 0x00000244u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX2           = 0x00000245u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL3      = 0x00000246u, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX3           = 0x00000247u, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX3           = 0x00000248u, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL4      = 0x00000249u, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX4           = 0x0000024Au, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX4           = 0x0000024Bu, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL5      = 0x0000024Cu, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX5           = 0x0000024Du, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX5           = 0x0000024Eu, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_2_SCB_I2C_SCL6      = 0x0000024Fu, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_2_SCB_TX6           = 0x00000250u, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_2_SCB_RX6           = 0x00000251u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_2_SMIF_TX           = 0x00000264u, /* smif.tr_tx_req */
    TRIG_IN_MUX_2_SMIF_RX           = 0x00000265u, /* smif.tr_rx_req */
    TRIG_IN_MUX_2_USB_DMA0          = 0x00000266u, /* usb.dma_req[0] */
    TRIG_IN_MUX_2_USB_DMA1          = 0x00000267u, /* usb.dma_req[1] */
    TRIG_IN_MUX_2_USB_DMA2          = 0x00000268u, /* usb.dma_req[2] */
    TRIG_IN_MUX_2_USB_DMA3          = 0x00000269u, /* usb.dma_req[3] */
    TRIG_IN_MUX_2_USB_DMA4          = 0x0000026Au, /* usb.dma_req[4] */
    TRIG_IN_MUX_2_USB_DMA5          = 0x0000026Bu, /* usb.dma_req[5] */
    TRIG_IN_MUX_2_USB_DMA6          = 0x0000026Cu, /* usb.dma_req[6] */
    TRIG_IN_MUX_2_USB_DMA7          = 0x0000026Du, /* usb.dma_req[7] */
    TRIG_IN_MUX_2_PASS_SAR_DONE     = 0x00000273u, /* pass.tr_sar_out */
    TRIG_IN_MUX_2_CSD_SENSE         = 0x00000274u, /* csd.dsi_sense_out */
    TRIG_IN_MUX_2_HSIOM_TR_OUT0     = 0x00000275u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT1     = 0x00000276u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT2     = 0x00000277u, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT3     = 0x00000278u, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT4     = 0x00000279u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT5     = 0x0000027Au, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT6     = 0x0000027Bu, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT7     = 0x0000027Cu, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT8     = 0x0000027Du, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT9     = 0x0000027Eu, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT10    = 0x0000027Fu, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT11    = 0x00000280u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT12    = 0x00000281u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_2_HSIOM_TR_OUT13    = 0x00000282u, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_2_CTI_TR_OUT0       = 0x00000283u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_2_CTI_TR_OUT1       = 0x00000284u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_2_LPCOMP_DSI_COMP0  = 0x00000285u, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_2_LPCOMP_DSI_COMP1  = 0x00000286u, /* lpcomp.dsi_comp1 */
    TRIG_IN_MUX_2_CANFD_TT_TR_OUT0  = 0x00000287u /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_tcpwm0_t;

/* Trigger Input Group 3 - TCPWM1 trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_3_PDMA1_TR_OUT0     = 0x00000301u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT1     = 0x00000302u, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT2     = 0x00000303u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT3     = 0x00000304u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT4     = 0x00000305u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT5     = 0x00000306u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT6     = 0x00000307u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_3_PDMA1_TR_OUT7     = 0x00000308u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_3_TCPWM0_TR_OVERFLOW0 = 0x00000309u, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_3_TCPWM0_TR_COMPARE_MATCH0 = 0x0000030Au, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_3_TCPWM0_TR_UNDERFLOW0 = 0x0000030Bu, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_3_TCPWM0_TR_OVERFLOW1 = 0x0000030Cu, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_3_TCPWM0_TR_COMPARE_MATCH1 = 0x0000030Du, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_3_TCPWM0_TR_UNDERFLOW1 = 0x0000030Eu, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_3_TCPWM0_TR_OVERFLOW2 = 0x0000030Fu, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_3_TCPWM0_TR_COMPARE_MATCH2 = 0x00000310u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_3_TCPWM0_TR_UNDERFLOW2 = 0x00000311u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_3_TCPWM0_TR_OVERFLOW3 = 0x00000312u, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_3_TCPWM0_TR_COMPARE_MATCH3 = 0x00000313u, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_3_TCPWM0_TR_UNDERFLOW3 = 0x00000314u, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW0 = 0x00000321u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH0 = 0x00000322u, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW0 = 0x00000323u, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW1 = 0x00000324u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH1 = 0x00000325u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW1 = 0x00000326u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW2 = 0x00000327u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH2 = 0x00000328u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW2 = 0x00000329u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW3 = 0x0000032Au, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH3 = 0x0000032Bu, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW3 = 0x0000032Cu, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW4 = 0x0000032Du, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH4 = 0x0000032Eu, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW4 = 0x0000032Fu, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW5 = 0x00000330u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH5 = 0x00000331u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW5 = 0x00000332u, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW6 = 0x00000333u, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH6 = 0x00000334u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW6 = 0x00000335u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_3_TCPWM1_TR_OVERFLOW7 = 0x00000336u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_3_TCPWM1_TR_COMPARE_MATCH7 = 0x00000337u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_3_TCPWM1_TR_UNDERFLOW7 = 0x00000338u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_3_MDMA_TR_OUT0      = 0x00000339u, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_3_MDMA_TR_OUT1      = 0x0000033Au, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_3_SCB_I2C_SCL0      = 0x0000033Du, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX0           = 0x0000033Eu, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX0           = 0x0000033Fu, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL1      = 0x00000340u, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX1           = 0x00000341u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX1           = 0x00000342u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL2      = 0x00000343u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX2           = 0x00000344u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX2           = 0x00000345u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL3      = 0x00000346u, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX3           = 0x00000347u, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX3           = 0x00000348u, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL4      = 0x00000349u, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX4           = 0x0000034Au, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX4           = 0x0000034Bu, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL5      = 0x0000034Cu, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX5           = 0x0000034Du, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX5           = 0x0000034Eu, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_3_SCB_I2C_SCL6      = 0x0000034Fu, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_3_SCB_TX6           = 0x00000350u, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_3_SCB_RX6           = 0x00000351u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_3_SMIF_TX           = 0x00000364u, /* smif.tr_tx_req */
    TRIG_IN_MUX_3_SMIF_RX           = 0x00000365u, /* smif.tr_rx_req */
    TRIG_IN_MUX_3_USB_DMA0          = 0x00000366u, /* usb.dma_req[0] */
    TRIG_IN_MUX_3_USB_DMA1          = 0x00000367u, /* usb.dma_req[1] */
    TRIG_IN_MUX_3_USB_DMA2          = 0x00000368u, /* usb.dma_req[2] */
    TRIG_IN_MUX_3_USB_DMA3          = 0x00000369u, /* usb.dma_req[3] */
    TRIG_IN_MUX_3_USB_DMA4          = 0x0000036Au, /* usb.dma_req[4] */
    TRIG_IN_MUX_3_USB_DMA5          = 0x0000036Bu, /* usb.dma_req[5] */
    TRIG_IN_MUX_3_USB_DMA6          = 0x0000036Cu, /* usb.dma_req[6] */
    TRIG_IN_MUX_3_USB_DMA7          = 0x0000036Du, /* usb.dma_req[7] */
    TRIG_IN_MUX_3_PASS_SAR_DONE     = 0x00000373u, /* pass.tr_sar_out */
    TRIG_IN_MUX_3_CSD_SENSE         = 0x00000374u, /* csd.dsi_sense_out */
    TRIG_IN_MUX_3_HSIOM_TR_OUT14    = 0x00000375u, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT15    = 0x00000376u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT16    = 0x00000377u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT17    = 0x00000378u, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT18    = 0x00000379u, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT19    = 0x0000037Au, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT20    = 0x0000037Bu, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT21    = 0x0000037Cu, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT22    = 0x0000037Du, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT23    = 0x0000037Eu, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT24    = 0x0000037Fu, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_3_HSIOM_TR_OUT25    = 0x00000380u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_3_FAULT_TR_OUT0     = 0x00000383u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_3_FAULT_TR_OUT1     = 0x00000384u, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_3_LPCOMP_DSI_COMP0  = 0x00000385u, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_3_LPCOMP_DSI_COMP1  = 0x00000386u, /* lpcomp.dsi_comp1 */
    TRIG_IN_MUX_3_CANFD_TT_TR_OUT0  = 0x00000387u /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_tcpwm1_t;

/* Trigger Input Group 4 - HSIOM trigger multiplexer */
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
    TRIG_IN_MUX_4_PDMA0_TR_OUT16    = 0x00000411u, /* cpuss.dw0_tr_out[16] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT17    = 0x00000412u, /* cpuss.dw0_tr_out[17] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT18    = 0x00000413u, /* cpuss.dw0_tr_out[18] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT19    = 0x00000414u, /* cpuss.dw0_tr_out[19] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT20    = 0x00000415u, /* cpuss.dw0_tr_out[20] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT21    = 0x00000416u, /* cpuss.dw0_tr_out[21] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT22    = 0x00000417u, /* cpuss.dw0_tr_out[22] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT23    = 0x00000418u, /* cpuss.dw0_tr_out[23] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT24    = 0x00000419u, /* cpuss.dw0_tr_out[24] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT25    = 0x0000041Au, /* cpuss.dw0_tr_out[25] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT26    = 0x0000041Bu, /* cpuss.dw0_tr_out[26] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT27    = 0x0000041Cu, /* cpuss.dw0_tr_out[27] */
    TRIG_IN_MUX_4_PDMA0_TR_OUT28    = 0x0000041Du, /* cpuss.dw0_tr_out[28] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT0     = 0x0000041Eu, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT1     = 0x0000041Fu, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT2     = 0x00000420u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT3     = 0x00000421u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT4     = 0x00000422u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT5     = 0x00000423u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT6     = 0x00000424u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT7     = 0x00000425u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT8     = 0x00000426u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT9     = 0x00000427u, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT10    = 0x00000428u, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT11    = 0x00000429u, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT12    = 0x0000042Au, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT13    = 0x0000042Bu, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT14    = 0x0000042Cu, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT15    = 0x0000042Du, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT16    = 0x0000042Eu, /* cpuss.dw1_tr_out[16] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT17    = 0x0000042Fu, /* cpuss.dw1_tr_out[17] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT18    = 0x00000430u, /* cpuss.dw1_tr_out[18] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT19    = 0x00000431u, /* cpuss.dw1_tr_out[19] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT20    = 0x00000432u, /* cpuss.dw1_tr_out[20] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT21    = 0x00000433u, /* cpuss.dw1_tr_out[21] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT22    = 0x00000434u, /* cpuss.dw1_tr_out[22] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT23    = 0x00000435u, /* cpuss.dw1_tr_out[23] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT24    = 0x00000436u, /* cpuss.dw1_tr_out[24] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT25    = 0x00000437u, /* cpuss.dw1_tr_out[25] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT26    = 0x00000438u, /* cpuss.dw1_tr_out[26] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT27    = 0x00000439u, /* cpuss.dw1_tr_out[27] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT28    = 0x0000043Au, /* cpuss.dw1_tr_out[28] */
    TRIG_IN_MUX_4_TCPWM0_TR_OVERFLOW0 = 0x0000043Bu, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_4_TCPWM0_TR_COMPARE_MATCH0 = 0x0000043Cu, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_4_TCPWM0_TR_UNDERFLOW0 = 0x0000043Du, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_4_TCPWM0_TR_OVERFLOW1 = 0x0000043Eu, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_4_TCPWM0_TR_COMPARE_MATCH1 = 0x0000043Fu, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_4_TCPWM0_TR_UNDERFLOW1 = 0x00000440u, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_4_TCPWM0_TR_OVERFLOW2 = 0x00000441u, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_4_TCPWM0_TR_COMPARE_MATCH2 = 0x00000442u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_4_TCPWM0_TR_UNDERFLOW2 = 0x00000443u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_4_TCPWM0_TR_OVERFLOW3 = 0x00000444u, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_4_TCPWM0_TR_COMPARE_MATCH3 = 0x00000445u, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_4_TCPWM0_TR_UNDERFLOW3 = 0x00000446u, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW0 = 0x00000453u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH0 = 0x00000454u, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW0 = 0x00000455u, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW1 = 0x00000456u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH1 = 0x00000457u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW1 = 0x00000458u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW2 = 0x00000459u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH2 = 0x0000045Au, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW2 = 0x0000045Bu, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW3 = 0x0000045Cu, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH3 = 0x0000045Du, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW3 = 0x0000045Eu, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW4 = 0x0000045Fu, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH4 = 0x00000460u, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW4 = 0x00000461u, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW5 = 0x00000462u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH5 = 0x00000463u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW5 = 0x00000464u, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW6 = 0x00000465u, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH6 = 0x00000466u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW6 = 0x00000467u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_4_TCPWM1_TR_OVERFLOW7 = 0x00000468u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_4_TCPWM1_TR_COMPARE_MATCH7 = 0x00000469u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_4_TCPWM1_TR_UNDERFLOW7 = 0x0000046Au, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_4_MDMA_TR_OUT0      = 0x0000049Bu, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_4_MDMA_TR_OUT1      = 0x0000049Cu, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_4_SCB_I2C_SCL0      = 0x0000049Fu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX0           = 0x000004A0u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX0           = 0x000004A1u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL1      = 0x000004A2u, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX1           = 0x000004A3u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX1           = 0x000004A4u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL2      = 0x000004A5u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX2           = 0x000004A6u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX2           = 0x000004A7u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL3      = 0x000004A8u, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX3           = 0x000004A9u, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX3           = 0x000004AAu, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL4      = 0x000004ABu, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX4           = 0x000004ACu, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX4           = 0x000004ADu, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL5      = 0x000004AEu, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX5           = 0x000004AFu, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX5           = 0x000004B0u, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_4_SCB_I2C_SCL6      = 0x000004B1u, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_4_SCB_TX6           = 0x000004B2u, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_4_SCB_RX6           = 0x000004B3u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_4_SMIF_TX           = 0x000004C6u, /* smif.tr_tx_req */
    TRIG_IN_MUX_4_SMIF_RX           = 0x000004C7u, /* smif.tr_rx_req */
    TRIG_IN_MUX_4_USB_DMA0          = 0x000004C8u, /* usb.dma_req[0] */
    TRIG_IN_MUX_4_USB_DMA1          = 0x000004C9u, /* usb.dma_req[1] */
    TRIG_IN_MUX_4_USB_DMA2          = 0x000004CAu, /* usb.dma_req[2] */
    TRIG_IN_MUX_4_USB_DMA3          = 0x000004CBu, /* usb.dma_req[3] */
    TRIG_IN_MUX_4_USB_DMA4          = 0x000004CCu, /* usb.dma_req[4] */
    TRIG_IN_MUX_4_USB_DMA5          = 0x000004CDu, /* usb.dma_req[5] */
    TRIG_IN_MUX_4_USB_DMA6          = 0x000004CEu, /* usb.dma_req[6] */
    TRIG_IN_MUX_4_USB_DMA7          = 0x000004CFu, /* usb.dma_req[7] */
    TRIG_IN_MUX_4_CSD_SENSE         = 0x000004D5u, /* csd.dsi_sense_out */
    TRIG_IN_MUX_4_CSD_SAMPLE        = 0x000004D6u, /* csd.dsi_sample_out */
    TRIG_IN_MUX_4_CSD_ADC_DONE      = 0x000004D7u, /* csd.tr_adc_done */
    TRIG_IN_MUX_4_PASS_SAR_DONE     = 0x000004D8u, /* pass.tr_sar_out */
    TRIG_IN_MUX_4_FAULT_TR_OUT0     = 0x000004D9u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_4_FAULT_TR_OUT1     = 0x000004DAu, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_4_CTI_TR_OUT0       = 0x000004DBu, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_4_CTI_TR_OUT1       = 0x000004DCu, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_4_LPCOMP_DSI_COMP0  = 0x000004DDu, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_4_LPCOMP_DSI_COMP1  = 0x000004DEu, /* lpcomp.dsi_comp1 */
    TRIG_IN_MUX_4_CANFD_TT_TR_OUT0  = 0x000004DFu, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT29    = 0x000004E0u, /* cpuss.dw1_tr_out[29] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT30    = 0x000004E1u, /* cpuss.dw1_tr_out[30] */
    TRIG_IN_MUX_4_PDMA1_TR_OUT31    = 0x000004E2u /* cpuss.dw1_tr_out[31] */
} en_trig_input_hsiom_t;

/* Trigger Input Group 5 - CPUSS Debug trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_5_PDMA0_TR_OUT0     = 0x00000501u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT1     = 0x00000502u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT2     = 0x00000503u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT3     = 0x00000504u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT4     = 0x00000505u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT5     = 0x00000506u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT6     = 0x00000507u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT7     = 0x00000508u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT8     = 0x00000509u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT9     = 0x0000050Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT10    = 0x0000050Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT11    = 0x0000050Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT12    = 0x0000050Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT13    = 0x0000050Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT14    = 0x0000050Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT15    = 0x00000510u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT16    = 0x00000511u, /* cpuss.dw0_tr_out[16] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT17    = 0x00000512u, /* cpuss.dw0_tr_out[17] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT18    = 0x00000513u, /* cpuss.dw0_tr_out[18] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT19    = 0x00000514u, /* cpuss.dw0_tr_out[19] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT20    = 0x00000515u, /* cpuss.dw0_tr_out[20] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT21    = 0x00000516u, /* cpuss.dw0_tr_out[21] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT22    = 0x00000517u, /* cpuss.dw0_tr_out[22] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT23    = 0x00000518u, /* cpuss.dw0_tr_out[23] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT24    = 0x00000519u, /* cpuss.dw0_tr_out[24] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT25    = 0x0000051Au, /* cpuss.dw0_tr_out[25] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT26    = 0x0000051Bu, /* cpuss.dw0_tr_out[26] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT27    = 0x0000051Cu, /* cpuss.dw0_tr_out[27] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT28    = 0x0000051Du, /* cpuss.dw0_tr_out[28] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT0     = 0x0000051Eu, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT1     = 0x0000051Fu, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT2     = 0x00000520u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT3     = 0x00000521u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT4     = 0x00000522u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT5     = 0x00000523u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT6     = 0x00000524u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT7     = 0x00000525u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT8     = 0x00000526u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT9     = 0x00000527u, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT10    = 0x00000528u, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT11    = 0x00000529u, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT12    = 0x0000052Au, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT13    = 0x0000052Bu, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT14    = 0x0000052Cu, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT15    = 0x0000052Du, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT16    = 0x0000052Eu, /* cpuss.dw1_tr_out[16] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT17    = 0x0000052Fu, /* cpuss.dw1_tr_out[17] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT18    = 0x00000530u, /* cpuss.dw1_tr_out[18] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT19    = 0x00000531u, /* cpuss.dw1_tr_out[19] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT20    = 0x00000532u, /* cpuss.dw1_tr_out[20] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT21    = 0x00000533u, /* cpuss.dw1_tr_out[21] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT22    = 0x00000534u, /* cpuss.dw1_tr_out[22] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT23    = 0x00000535u, /* cpuss.dw1_tr_out[23] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT24    = 0x00000536u, /* cpuss.dw1_tr_out[24] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT25    = 0x00000537u, /* cpuss.dw1_tr_out[25] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT26    = 0x00000538u, /* cpuss.dw1_tr_out[26] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT27    = 0x00000539u, /* cpuss.dw1_tr_out[27] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT28    = 0x0000053Au, /* cpuss.dw1_tr_out[28] */
    TRIG_IN_MUX_5_TCPWM0_TR_OVERFLOW0 = 0x0000053Bu, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_5_TCPWM0_TR_COMPARE_MATCH0 = 0x0000053Cu, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_5_TCPWM0_TR_UNDERFLOW0 = 0x0000053Du, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_5_TCPWM0_TR_OVERFLOW1 = 0x0000053Eu, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_5_TCPWM0_TR_COMPARE_MATCH1 = 0x0000053Fu, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_5_TCPWM0_TR_UNDERFLOW1 = 0x00000540u, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_5_TCPWM0_TR_OVERFLOW2 = 0x00000541u, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_5_TCPWM0_TR_COMPARE_MATCH2 = 0x00000542u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_5_TCPWM0_TR_UNDERFLOW2 = 0x00000543u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_5_TCPWM0_TR_OVERFLOW3 = 0x00000544u, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_5_TCPWM0_TR_COMPARE_MATCH3 = 0x00000545u, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_5_TCPWM0_TR_UNDERFLOW3 = 0x00000546u, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW0 = 0x00000553u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH0 = 0x00000554u, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW0 = 0x00000555u, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW1 = 0x00000556u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH1 = 0x00000557u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW1 = 0x00000558u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW2 = 0x00000559u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH2 = 0x0000055Au, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW2 = 0x0000055Bu, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW3 = 0x0000055Cu, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH3 = 0x0000055Du, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW3 = 0x0000055Eu, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW4 = 0x0000055Fu, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH4 = 0x00000560u, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW4 = 0x00000561u, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW5 = 0x00000562u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH5 = 0x00000563u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW5 = 0x00000564u, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW6 = 0x00000565u, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH6 = 0x00000566u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW6 = 0x00000567u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_5_TCPWM1_TR_OVERFLOW7 = 0x00000568u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_5_TCPWM1_TR_COMPARE_MATCH7 = 0x00000569u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_5_TCPWM1_TR_UNDERFLOW7 = 0x0000056Au, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_5_MDMA_TR_OUT0      = 0x0000059Bu, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_5_MDMA_TR_OUT1      = 0x0000059Cu, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_5_SCB_I2C_SCL0      = 0x0000059Fu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX0           = 0x000005A0u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX0           = 0x000005A1u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL1      = 0x000005A2u, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX1           = 0x000005A3u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX1           = 0x000005A4u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL2      = 0x000005A5u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX2           = 0x000005A6u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX2           = 0x000005A7u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL3      = 0x000005A8u, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX3           = 0x000005A9u, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX3           = 0x000005AAu, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL4      = 0x000005ABu, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX4           = 0x000005ACu, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX4           = 0x000005ADu, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL5      = 0x000005AEu, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX5           = 0x000005AFu, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX5           = 0x000005B0u, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_5_SCB_I2C_SCL6      = 0x000005B1u, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_5_SCB_TX6           = 0x000005B2u, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_5_SCB_RX6           = 0x000005B3u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_5_SMIF_TX           = 0x000005C6u, /* smif.tr_tx_req */
    TRIG_IN_MUX_5_SMIF_RX           = 0x000005C7u, /* smif.tr_rx_req */
    TRIG_IN_MUX_5_USB_DMA0          = 0x000005C8u, /* usb.dma_req[0] */
    TRIG_IN_MUX_5_USB_DMA1          = 0x000005C9u, /* usb.dma_req[1] */
    TRIG_IN_MUX_5_USB_DMA2          = 0x000005CAu, /* usb.dma_req[2] */
    TRIG_IN_MUX_5_USB_DMA3          = 0x000005CBu, /* usb.dma_req[3] */
    TRIG_IN_MUX_5_USB_DMA4          = 0x000005CCu, /* usb.dma_req[4] */
    TRIG_IN_MUX_5_USB_DMA5          = 0x000005CDu, /* usb.dma_req[5] */
    TRIG_IN_MUX_5_USB_DMA6          = 0x000005CEu, /* usb.dma_req[6] */
    TRIG_IN_MUX_5_USB_DMA7          = 0x000005CFu, /* usb.dma_req[7] */
    TRIG_IN_MUX_5_CSD_SENSE         = 0x000005D5u, /* csd.dsi_sense_out */
    TRIG_IN_MUX_5_CSD_SAMPLE        = 0x000005D6u, /* csd.dsi_sample_out */
    TRIG_IN_MUX_5_CSD_ADC_DONE      = 0x000005D7u, /* csd.tr_adc_done */
    TRIG_IN_MUX_5_PASS_SAR_DONE     = 0x000005D8u, /* pass.tr_sar_out */
    TRIG_IN_MUX_5_HSIOM_TR_OUT0     = 0x000005D9u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT1     = 0x000005DAu, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT2     = 0x000005DBu, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT3     = 0x000005DCu, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT4     = 0x000005DDu, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT5     = 0x000005DEu, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT6     = 0x000005DFu, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT7     = 0x000005E0u, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT8     = 0x000005E1u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT9     = 0x000005E2u, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT10    = 0x000005E3u, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT11    = 0x000005E4u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT12    = 0x000005E5u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT13    = 0x000005E6u, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT14    = 0x000005E7u, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT15    = 0x000005E8u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT16    = 0x000005E9u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT17    = 0x000005EAu, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT18    = 0x000005EBu, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT19    = 0x000005ECu, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT20    = 0x000005EDu, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT21    = 0x000005EEu, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT22    = 0x000005EFu, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT23    = 0x000005F0u, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT24    = 0x000005F1u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_5_HSIOM_TR_OUT25    = 0x000005F2u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_5_FAULT_TR_OUT0     = 0x000005F5u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_5_FAULT_TR_OUT1     = 0x000005F6u, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_5_CTI_TR_OUT0       = 0x000005F7u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_5_CTI_TR_OUT1       = 0x000005F8u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_5_LPCOMP_DSI_COMP0  = 0x000005F9u, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_5_LPCOMP_DSI_COMP1  = 0x000005FAu, /* lpcomp.dsi_comp1 */
    TRIG_IN_MUX_5_CANFD_TT_TR_OUT0  = 0x000005FBu, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT29    = 0x000005FCu, /* cpuss.dw1_tr_out[29] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT30    = 0x000005FDu, /* cpuss.dw1_tr_out[30] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT31    = 0x000005FEu /* cpuss.dw1_tr_out[31] */
} en_trig_input_cpuss_cti_t;

/* Trigger Input Group 6 - MDMA trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW0 = 0x00000601u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH0 = 0x00000602u, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW0 = 0x00000603u, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW1 = 0x00000604u, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH1 = 0x00000605u, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW1 = 0x00000606u, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW2 = 0x00000607u, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH2 = 0x00000608u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW2 = 0x00000609u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW3 = 0x0000060Au, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH3 = 0x0000060Bu, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW3 = 0x0000060Cu, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW4 = 0x0000060Du, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH4 = 0x0000060Eu, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW4 = 0x0000060Fu, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW5 = 0x00000610u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH5 = 0x00000611u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW5 = 0x00000612u, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW6 = 0x00000613u, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH6 = 0x00000614u, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW6 = 0x00000615u, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_6_TCPWM1_TR_OVERFLOW7 = 0x00000616u, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_6_TCPWM1_TR_COMPARE_MATCH7 = 0x00000617u, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_6_TCPWM1_TR_UNDERFLOW7 = 0x00000618u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_6_SMIF_TX           = 0x00000619u, /* smif.tr_tx_req */
    TRIG_IN_MUX_6_SMIF_RX           = 0x0000061Au /* smif.tr_rx_req */
} en_trig_input_mdma_t;

/* Trigger Input Group 7 - PERI Freeze trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_7_CTI_TR_OUT0       = 0x00000701u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_7_CTI_TR_OUT1       = 0x00000702u /* cpuss.cti_tr_out[1] */
} en_trig_input_peri_freeze_t;

/* Trigger Input Group 8 - Capsense trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_8_TCPWM0_TR_OVERFLOW0 = 0x00000801u, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_8_TCPWM0_TR_COMPARE_MATCH0 = 0x00000802u, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_8_TCPWM0_TR_UNDERFLOW0 = 0x00000803u, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_8_TCPWM0_TR_OVERFLOW1 = 0x00000804u, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_8_TCPWM0_TR_COMPARE_MATCH1 = 0x00000805u, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_8_TCPWM0_TR_UNDERFLOW1 = 0x00000806u, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_8_TCPWM0_TR_OVERFLOW2 = 0x00000807u, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_8_TCPWM0_TR_COMPARE_MATCH2 = 0x00000808u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_8_TCPWM0_TR_UNDERFLOW2 = 0x00000809u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_8_TCPWM0_TR_OVERFLOW3 = 0x0000080Au, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_8_TCPWM0_TR_COMPARE_MATCH3 = 0x0000080Bu, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_8_TCPWM0_TR_UNDERFLOW3 = 0x0000080Cu, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW0 = 0x00000819u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH0 = 0x0000081Au, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW0 = 0x0000081Bu, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW1 = 0x0000081Cu, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH1 = 0x0000081Du, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW1 = 0x0000081Eu, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW2 = 0x0000081Fu, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH2 = 0x00000820u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW2 = 0x00000821u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW3 = 0x00000822u, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH3 = 0x00000823u, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW3 = 0x00000824u, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW4 = 0x00000825u, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH4 = 0x00000826u, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW4 = 0x00000827u, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW5 = 0x00000828u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH5 = 0x00000829u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW5 = 0x0000082Au, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW6 = 0x0000082Bu, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH6 = 0x0000082Cu, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW6 = 0x0000082Du, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_8_TCPWM1_TR_OVERFLOW7 = 0x0000082Eu, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_8_TCPWM1_TR_COMPARE_MATCH7 = 0x0000082Fu, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_8_TCPWM1_TR_UNDERFLOW7 = 0x00000830u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT0     = 0x0000086Du, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT1     = 0x0000086Eu, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT2     = 0x0000086Fu, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT3     = 0x00000870u, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT4     = 0x00000871u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT5     = 0x00000872u, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT6     = 0x00000873u, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT7     = 0x00000874u, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT8     = 0x00000875u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT9     = 0x00000876u, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT10    = 0x00000877u, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT11    = 0x00000878u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT12    = 0x00000879u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT13    = 0x0000087Au, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT14    = 0x0000087Bu, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT15    = 0x0000087Cu, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT16    = 0x0000087Du, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT17    = 0x0000087Eu, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT18    = 0x0000087Fu, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT19    = 0x00000880u, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT20    = 0x00000881u, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT21    = 0x00000882u, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT22    = 0x00000883u, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT23    = 0x00000884u, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT24    = 0x00000885u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_8_HSIOM_TR_OUT25    = 0x00000886u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_8_LPCOMP_DSI_COMP0  = 0x00000889u, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_8_LPCOMP_DSI_COMP1  = 0x0000088Au /* lpcomp.dsi_comp1 */
} en_trig_input_csd_t;

/* Trigger Input Group 9 - ADC trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_9_TCPWM0_TR_OVERFLOW0 = 0x00000901u, /* tcpwm[0].tr_overflow[0] */
    TRIG_IN_MUX_9_TCPWM0_TR_COMPARE_MATCH0 = 0x00000902u, /* tcpwm[0].tr_compare_match[0] */
    TRIG_IN_MUX_9_TCPWM0_TR_UNDERFLOW0 = 0x00000903u, /* tcpwm[0].tr_underflow[0] */
    TRIG_IN_MUX_9_TCPWM0_TR_OVERFLOW1 = 0x00000904u, /* tcpwm[0].tr_overflow[1] */
    TRIG_IN_MUX_9_TCPWM0_TR_COMPARE_MATCH1 = 0x00000905u, /* tcpwm[0].tr_compare_match[1] */
    TRIG_IN_MUX_9_TCPWM0_TR_UNDERFLOW1 = 0x00000906u, /* tcpwm[0].tr_underflow[1] */
    TRIG_IN_MUX_9_TCPWM0_TR_OVERFLOW2 = 0x00000907u, /* tcpwm[0].tr_overflow[2] */
    TRIG_IN_MUX_9_TCPWM0_TR_COMPARE_MATCH2 = 0x00000908u, /* tcpwm[0].tr_compare_match[2] */
    TRIG_IN_MUX_9_TCPWM0_TR_UNDERFLOW2 = 0x00000909u, /* tcpwm[0].tr_underflow[2] */
    TRIG_IN_MUX_9_TCPWM0_TR_OVERFLOW3 = 0x0000090Au, /* tcpwm[0].tr_overflow[3] */
    TRIG_IN_MUX_9_TCPWM0_TR_COMPARE_MATCH3 = 0x0000090Bu, /* tcpwm[0].tr_compare_match[3] */
    TRIG_IN_MUX_9_TCPWM0_TR_UNDERFLOW3 = 0x0000090Cu, /* tcpwm[0].tr_underflow[3] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW0 = 0x00000919u, /* tcpwm[1].tr_overflow[0] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH0 = 0x0000091Au, /* tcpwm[1].tr_compare_match[0] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW0 = 0x0000091Bu, /* tcpwm[1].tr_underflow[0] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW1 = 0x0000091Cu, /* tcpwm[1].tr_overflow[1] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH1 = 0x0000091Du, /* tcpwm[1].tr_compare_match[1] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW1 = 0x0000091Eu, /* tcpwm[1].tr_underflow[1] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW2 = 0x0000091Fu, /* tcpwm[1].tr_overflow[2] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH2 = 0x00000920u, /* tcpwm[1].tr_compare_match[2] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW2 = 0x00000921u, /* tcpwm[1].tr_underflow[2] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW3 = 0x00000922u, /* tcpwm[1].tr_overflow[3] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH3 = 0x00000923u, /* tcpwm[1].tr_compare_match[3] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW3 = 0x00000924u, /* tcpwm[1].tr_underflow[3] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW4 = 0x00000925u, /* tcpwm[1].tr_overflow[4] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH4 = 0x00000926u, /* tcpwm[1].tr_compare_match[4] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW4 = 0x00000927u, /* tcpwm[1].tr_underflow[4] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW5 = 0x00000928u, /* tcpwm[1].tr_overflow[5] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH5 = 0x00000929u, /* tcpwm[1].tr_compare_match[5] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW5 = 0x0000092Au, /* tcpwm[1].tr_underflow[5] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW6 = 0x0000092Bu, /* tcpwm[1].tr_overflow[6] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH6 = 0x0000092Cu, /* tcpwm[1].tr_compare_match[6] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW6 = 0x0000092Du, /* tcpwm[1].tr_underflow[6] */
    TRIG_IN_MUX_9_TCPWM1_TR_OVERFLOW7 = 0x0000092Eu, /* tcpwm[1].tr_overflow[7] */
    TRIG_IN_MUX_9_TCPWM1_TR_COMPARE_MATCH7 = 0x0000092Fu, /* tcpwm[1].tr_compare_match[7] */
    TRIG_IN_MUX_9_TCPWM1_TR_UNDERFLOW7 = 0x00000930u, /* tcpwm[1].tr_underflow[7] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT0     = 0x00000961u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT1     = 0x00000962u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT2     = 0x00000963u, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT3     = 0x00000964u, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT4     = 0x00000965u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT5     = 0x00000966u, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT6     = 0x00000967u, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT7     = 0x00000968u, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT8     = 0x00000969u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT9     = 0x0000096Au, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT10    = 0x0000096Bu, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT11    = 0x0000096Cu, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT12    = 0x0000096Du, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT13    = 0x0000096Eu, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT14    = 0x0000096Fu, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT15    = 0x00000970u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT16    = 0x00000971u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT17    = 0x00000972u, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT18    = 0x00000973u, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT19    = 0x00000974u, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT20    = 0x00000975u, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT21    = 0x00000976u, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT22    = 0x00000977u, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT23    = 0x00000978u, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT24    = 0x00000979u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_9_HSIOM_TR_OUT25    = 0x0000097Au, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_9_LPCOMP_DSI_COMP0  = 0x0000097Du, /* lpcomp.dsi_comp0 */
    TRIG_IN_MUX_9_LPCOMP_DSI_COMP1  = 0x0000097Eu /* lpcomp.dsi_comp1 */
} en_trig_input_sar_adc_start_t;

/* Trigger Input Group 10 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_IN_MUX_10_CAN_TT_TR_OUT0   = 0x00000A01u /* canfd[0].tr_tmp_rtp_out[0] */
} en_trig_input_cantt_t;

/* Trigger Group Outputs */
/* Trigger Output Group 0 - PDMA0 Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_0_PDMA0_TR_IN0     = 0x40000000u, /* cpuss.dw0_tr_in[0] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN1     = 0x40000001u, /* cpuss.dw0_tr_in[1] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN2     = 0x40000002u, /* cpuss.dw0_tr_in[2] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN3     = 0x40000003u, /* cpuss.dw0_tr_in[3] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN4     = 0x40000004u, /* cpuss.dw0_tr_in[4] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN5     = 0x40000005u, /* cpuss.dw0_tr_in[5] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN6     = 0x40000006u, /* cpuss.dw0_tr_in[6] */
    TRIG_OUT_MUX_0_PDMA0_TR_IN7     = 0x40000007u /* cpuss.dw0_tr_in[7] */
} en_trig_output_pdma0_tr_t;

/* Trigger Output Group 1 - PDMA1 Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_1_PDMA1_TR_IN0     = 0x40000100u, /* cpuss.dw1_tr_in[0] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN1     = 0x40000101u, /* cpuss.dw1_tr_in[1] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN2     = 0x40000102u, /* cpuss.dw1_tr_in[2] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN3     = 0x40000103u, /* cpuss.dw1_tr_in[3] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN4     = 0x40000104u, /* cpuss.dw1_tr_in[4] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN5     = 0x40000105u, /* cpuss.dw1_tr_in[5] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN6     = 0x40000106u, /* cpuss.dw1_tr_in[6] */
    TRIG_OUT_MUX_1_PDMA1_TR_IN7     = 0x40000107u /* cpuss.dw1_tr_in[7] */
} en_trig_output_pdma1_tr_t;

/* Trigger Output Group 2 - TCPWM0 trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_2_TCPWM0_TR_IN0    = 0x40000200u, /* tcpwm[0].tr_in[0] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN1    = 0x40000201u, /* tcpwm[0].tr_in[1] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN2    = 0x40000202u, /* tcpwm[0].tr_in[2] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN3    = 0x40000203u, /* tcpwm[0].tr_in[3] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN4    = 0x40000204u, /* tcpwm[0].tr_in[4] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN5    = 0x40000205u, /* tcpwm[0].tr_in[5] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN6    = 0x40000206u, /* tcpwm[0].tr_in[6] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN7    = 0x40000207u, /* tcpwm[0].tr_in[7] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN8    = 0x40000208u, /* tcpwm[0].tr_in[8] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN9    = 0x40000209u, /* tcpwm[0].tr_in[9] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN10   = 0x4000020Au, /* tcpwm[0].tr_in[10] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN11   = 0x4000020Bu, /* tcpwm[0].tr_in[11] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN12   = 0x4000020Cu, /* tcpwm[0].tr_in[12] */
    TRIG_OUT_MUX_2_TCPWM0_TR_IN13   = 0x4000020Du /* tcpwm[0].tr_in[13] */
} en_trig_output_tcpwm0_t;

/* Trigger Output Group 3 - TCPWM1 trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_3_TCPWM1_TR_IN0    = 0x40000300u, /* tcpwm[1].tr_in[0] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN1    = 0x40000301u, /* tcpwm[1].tr_in[1] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN2    = 0x40000302u, /* tcpwm[1].tr_in[2] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN3    = 0x40000303u, /* tcpwm[1].tr_in[3] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN4    = 0x40000304u, /* tcpwm[1].tr_in[4] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN5    = 0x40000305u, /* tcpwm[1].tr_in[5] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN6    = 0x40000306u, /* tcpwm[1].tr_in[6] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN7    = 0x40000307u, /* tcpwm[1].tr_in[7] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN8    = 0x40000308u, /* tcpwm[1].tr_in[8] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN9    = 0x40000309u, /* tcpwm[1].tr_in[9] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN10   = 0x4000030Au, /* tcpwm[1].tr_in[10] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN11   = 0x4000030Bu, /* tcpwm[1].tr_in[11] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN12   = 0x4000030Cu, /* tcpwm[1].tr_in[12] */
    TRIG_OUT_MUX_3_TCPWM1_TR_IN13   = 0x4000030Du /* tcpwm[1].tr_in[13] */
} en_trig_output_tcpwm1_t;

/* Trigger Output Group 4 - HSIOM trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_4_HSIOM_TR_IO_OUTPUT0 = 0x40000400u, /* peri.tr_io_output[0] */
    TRIG_OUT_MUX_4_HSIOM_TR_IO_OUTPUT1 = 0x40000401u /* peri.tr_io_output[1] */
} en_trig_output_hsiom_t;

/* Trigger Output Group 5 - CPUSS Debug trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_5_CPUSS_CTI_TR_IN0 = 0x40000500u, /* cpuss.cti_tr_in[0] */
    TRIG_OUT_MUX_5_CPUSS_CTI_TR_IN1 = 0x40000501u /* cpuss.cti_tr_in[1] */
} en_trig_output_cpuss_cti_t;

/* Trigger Output Group 6 - MDMA trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_6_MDMA_TR_IN0      = 0x40000600u, /* cpuss.dmac_tr_in[0] */
    TRIG_OUT_MUX_6_MDMA_TR_IN1      = 0x40000601u /* cpuss.dmac_tr_in[1] */
} en_trig_output_mdma_t;

/* Trigger Output Group 7 - PERI Freeze trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_7_DEBUG_FREEZE_TR_IN = 0x40000700u /* peri.tr_dbg_freeze */
} en_trig_output_peri_freeze_t;

/* Trigger Output Group 8 - Capsense trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_8_CSD_DSI_START    = 0x40000800u /* csd.dsi_start */
} en_trig_output_csd_t;

/* Trigger Output Group 9 - ADC trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_9_PASS_TR_SAR_IN   = 0x40000900u /* pass.tr_sar_in */
} en_trig_output_sar_adc_start_t;

/* Trigger Output Group 10 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_OUT_MUX_10_CAN_TT_TR_IN0   = 0x40000A00u /* canfd[0].tr_evt_swt_in[0] */
} en_trig_output_cantt_t;

/* Trigger Output Group 0 - SCB PDMA0 Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_0_SCB0_TX_TO_PDMA0_TR_IN16 = 0x40001000u, /* From scb[0].tr_tx_req to cpuss.dw0_tr_in[16] */
    TRIG_OUT_1TO1_0_SCB0_RX_TO_PDMA0_TR_IN17 = 0x40001001u, /* From scb[0].tr_rx_req to cpuss.dw0_tr_in[17] */
    TRIG_OUT_1TO1_0_SCB1_TX_TO_PDMA0_TR_IN18 = 0x40001002u, /* From scb[1].tr_tx_req to cpuss.dw0_tr_in[18] */
    TRIG_OUT_1TO1_0_SCB1_RX_TO_PDMA0_TR_IN19 = 0x40001003u, /* From scb[1].tr_rx_req to cpuss.dw0_tr_in[19] */
    TRIG_OUT_1TO1_0_SCB2_TX_TO_PDMA0_TR_IN20 = 0x40001004u, /* From scb[2].tr_tx_req to cpuss.dw0_tr_in[20] */
    TRIG_OUT_1TO1_0_SCB2_RX_TO_PDMA0_TR_IN21 = 0x40001005u, /* From scb[2].tr_rx_req to cpuss.dw0_tr_in[21] */
    TRIG_OUT_1TO1_0_SCB3_TX_TO_PDMA0_TR_IN22 = 0x40001006u, /* From scb[3].tr_tx_req to cpuss.dw0_tr_in[22] */
    TRIG_OUT_1TO1_0_SCB3_RX_TO_PDMA0_TR_IN23 = 0x40001007u, /* From scb[3].tr_rx_req to cpuss.dw0_tr_in[23] */
    TRIG_OUT_1TO1_0_SCB4_TX_TO_PDMA0_TR_IN24 = 0x40001008u, /* From scb[4].tr_tx_req to cpuss.dw0_tr_in[24] */
    TRIG_OUT_1TO1_0_SCB4_RX_TO_PDMA0_TR_IN25 = 0x40001009u, /* From scb[4].tr_rx_req to cpuss.dw0_tr_in[25] */
    TRIG_OUT_1TO1_0_SCB5_TX_TO_PDMA0_TR_IN26 = 0x4000100Au, /* From scb[5].tr_tx_req to cpuss.dw0_tr_in[26] */
    TRIG_OUT_1TO1_0_SCB5_RX_TO_PDMA0_TR_IN27 = 0x4000100Bu /* From scb[5].tr_rx_req to cpuss.dw0_tr_in[27] */
} en_trig_output_1to1_scb_pdma0_tr_t;

/* Trigger Output Group 1 - SCB PDMA1 Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_1_SCB6_TX_TO_PDMA1_TR_IN8 = 0x40001100u, /* From scb[6].tr_tx_req to cpuss.dw1_tr_in[8] */
    TRIG_OUT_1TO1_1_SCB6_RX_TO_PDMA1_TR_IN9 = 0x40001101u, /* From scb[6].tr_rx_req to cpuss.dw1_tr_in[9] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN10 = 0x40001102u, /* From cpuss.zero to cpuss.dw1_tr_in[10] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN11 = 0x40001103u, /* From cpuss.zero to cpuss.dw1_tr_in[11] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN12 = 0x40001104u, /* From cpuss.zero to cpuss.dw1_tr_in[12] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN13 = 0x40001105u, /* From cpuss.zero to cpuss.dw1_tr_in[13] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN14 = 0x40001106u, /* From cpuss.zero to cpuss.dw1_tr_in[14] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN15 = 0x40001107u, /* From cpuss.zero to cpuss.dw1_tr_in[15] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN16 = 0x40001108u, /* From cpuss.zero to cpuss.dw1_tr_in[16] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN17 = 0x40001109u, /* From cpuss.zero to cpuss.dw1_tr_in[17] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN18 = 0x4000110Au, /* From cpuss.zero to cpuss.dw1_tr_in[18] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN19 = 0x4000110Bu, /* From cpuss.zero to cpuss.dw1_tr_in[19] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN20 = 0x4000110Cu, /* From cpuss.zero to cpuss.dw1_tr_in[20] */
    TRIG1_OUT_1TO1_CPUSS_DW1_TR_IN21 = 0x4000110Du /* From cpuss.zero to cpuss.dw1_tr_in[21] */
} en_trig_output_1to1_scb_pdma1_tr_t;

/* Trigger Output Group 2 - PASS to PDMA0 direct connect (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_2_PASS_SAR_DONE_TO_PDMA0_TR_IN28 = 0x40001200u /* From pass.tr_sar_out to cpuss.dw0_tr_in[28] */
} en_trig_output_1to1_sar_to_pdma1_t;

/* Trigger Output Group 3 -  (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_3_SMIF_TX_TO_PDMA1_TR_IN22 = 0x40001300u, /* From smif.tr_tx_req to cpuss.dw1_tr_in[22] */
    TRIG_OUT_1TO1_3_SMIF_RX_TO_PDMA1_TR_IN23 = 0x40001301u, /* From smif.tr_rx_req to cpuss.dw1_tr_in[23] */
    TRIG3_OUT_1TO1_CPUSS_DW1_TR_IN24 = 0x40001302u, /* From cpuss.zero to cpuss.dw1_tr_in[24] */
    TRIG3_OUT_1TO1_CPUSS_DW1_TR_IN25 = 0x40001303u, /* From cpuss.zero to cpuss.dw1_tr_in[25] */
    TRIG3_OUT_1TO1_CPUSS_DW1_TR_IN26 = 0x40001304u, /* From cpuss.zero to cpuss.dw1_tr_in[26] */
    TRIG3_OUT_1TO1_CPUSS_DW1_TR_IN27 = 0x40001305u, /* From cpuss.zero to cpuss.dw1_tr_in[27] */
    TRIG3_OUT_1TO1_CPUSS_DW1_TR_IN28 = 0x40001306u /* From cpuss.zero to cpuss.dw1_tr_in[28] */
} en_trig_output_1to1_smif_to_pdma1_t;

/* Trigger Output Group 4 - CAN DW triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_4_CAN_DBG_TO_PDMA1_TR_IN29 = 0x40001400u, /* From canfd[0].tr_dbg_dma_req[0] to cpuss.dw1_tr_in[29] */
    TRIG_OUT_1TO1_4_CAN_FIFO0_TO_PDMA1_TR_IN30 = 0x40001401u, /* From canfd[0].tr_fifo0[0] to cpuss.dw1_tr_in[30] */
    TRIG_OUT_1TO1_4_CAN_FIFO1_TO_PDMA1_TR_IN31 = 0x40001402u /* From canfd[0].tr_fifo1[0] to cpuss.dw1_tr_in[31] */
} en_trig_output_1to1_can_dw_tr_t;

/* Trigger Output Group 5 - USB PDMA0 Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_5_USB_DMA0_TO_PDMA0_TR_IN8 = 0x40001500u, /* From usb.dma_req[0] to cpuss.dw0_tr_in[8] */
    TRIG_OUT_1TO1_5_USB_DMA1_TO_PDMA0_TR_IN9 = 0x40001501u, /* From usb.dma_req[1] to cpuss.dw0_tr_in[9] */
    TRIG_OUT_1TO1_5_USB_DMA2_TO_PDMA0_TR_IN10 = 0x40001502u, /* From usb.dma_req[2] to cpuss.dw0_tr_in[10] */
    TRIG_OUT_1TO1_5_USB_DMA3_TO_PDMA0_TR_IN11 = 0x40001503u, /* From usb.dma_req[3] to cpuss.dw0_tr_in[11] */
    TRIG_OUT_1TO1_5_USB_DMA4_TO_PDMA0_TR_IN12 = 0x40001504u, /* From usb.dma_req[4] to cpuss.dw0_tr_in[12] */
    TRIG_OUT_1TO1_5_USB_DMA5_TO_PDMA0_TR_IN13 = 0x40001505u, /* From usb.dma_req[5] to cpuss.dw0_tr_in[13] */
    TRIG_OUT_1TO1_5_USB_DMA6_TO_PDMA0_TR_IN14 = 0x40001506u, /* From usb.dma_req[6] to cpuss.dw0_tr_in[14] */
    TRIG_OUT_1TO1_5_USB_DMA7_TO_PDMA0_TR_IN15 = 0x40001507u /* From usb.dma_req[7] to cpuss.dw0_tr_in[15] */
} en_trig_output_1to1_usb_pdma0_tr_t;

/* Trigger Output Group 6 - USB PDMA0 Acknowledge Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT8_TO_USB_ACK0 = 0x40001600u, /* From cpuss.dw0_tr_out[8] to usb.dma_burstend[0] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT9_TO_USB_ACK1 = 0x40001601u, /* From cpuss.dw0_tr_out[9] to usb.dma_burstend[1] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT10_TO_USB_ACK2 = 0x40001602u, /* From cpuss.dw0_tr_out[10] to usb.dma_burstend[2] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT11_TO_USB_ACK3 = 0x40001603u, /* From cpuss.dw0_tr_out[11] to usb.dma_burstend[3] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT12_TO_USB_ACK4 = 0x40001604u, /* From cpuss.dw0_tr_out[12] to usb.dma_burstend[4] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT13_TO_USB_ACK5 = 0x40001605u, /* From cpuss.dw0_tr_out[13] to usb.dma_burstend[5] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT14_TO_USB_ACK6 = 0x40001606u, /* From cpuss.dw0_tr_out[14] to usb.dma_burstend[6] */
    TRIG_OUT_1TO1_6_PDMA0_TR_OUT15_TO_USB_ACK7 = 0x40001607u /* From cpuss.dw0_tr_out[15] to usb.dma_burstend[7] */
} en_trig_output_1to1_usb_pdma0_ack_tr_t;

/* Trigger Output Group 7 - Acknowledge dma request triggers from DW0 to CAN (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_7_PDMA1_TR_OUT29_ACK_TO_CAN_0 = 0x40001700u /* From cpuss.dw1_tr_out[29] to canfd[0].tr_dbg_dma_ack[0] */
} en_trig_output_1to1_can0_dw_ack_t;

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
#define TRIGGER_TYPE_CPUSS_DMAC_TR_IN__LEVEL    TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CPUSS_DMAC_TR_IN__EDGE     TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DMAC_TR_OUT          TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW0_TR_IN__LEVEL     TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CPUSS_DW0_TR_IN__EDGE      TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW0_TR_OUT           TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW1_TR_IN__LEVEL     TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_CPUSS_DW1_TR_IN__EDGE      TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_DW1_TR_OUT           TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_CPUSS_TR_FAULT             TRIGGER_TYPE_EDGE
/* CSD Trigger Types */
#define TRIGGER_TYPE_CSD_DSI_SAMPLE_OUT         TRIGGER_TYPE_EDGE
/* LPCOMP Trigger Types */
#define TRIGGER_TYPE_LPCOMP_DSI_COMP0           TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_LPCOMP_DSI_COMP1           TRIGGER_TYPE_LEVEL
/* PASS Trigger Types */
#define TRIGGER_TYPE_PASS_TR_SAR_IN__LEVEL      TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_IN__EDGE       TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PASS_TR_SAR_OUT            TRIGGER_TYPE_EDGE
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
/* TCPWM Trigger Types */
#define TRIGGER_TYPE_TCPWM_LINE                 TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TCPWM_LINE_COMPL           TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TCPWM_TR_COMPARE_MATCH     TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_TCPWM_TR_IN__LEVEL         TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TCPWM_TR_IN__EDGE          TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_TCPWM_TR_OVERFLOW          TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_TCPWM_TR_UNDERFLOW         TRIGGER_TYPE_EDGE
/* USB Trigger Types */
#define TRIGGER_TYPE_USB_DMA_BURSTEND           TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_USB_DMA_REQ                TRIGGER_TYPE_EDGE

/* Bus masters */
typedef enum
{
    CPUSS_MS_ID_CM0                 =  0,
    CPUSS_MS_ID_CRYPTO              =  1,
    CPUSS_MS_ID_DW0                 =  2,
    CPUSS_MS_ID_DW1                 =  3,
    CPUSS_MS_ID_DMAC                =  4,
    CPUSS_MS_ID_SLOW0               =  5,
    CPUSS_MS_ID_SLOW1               =  6,
    CPUSS_MS_ID_CM4                 = 14,
    CPUSS_MS_ID_TC                  = 15
} en_prot_master_t;

/* Pointer to device configuration structure */
#define CY_DEVICE_CFG                   (&cy_deviceIpBlockCfgPSoC6_03)

/* Include IP definitions */
#include "ip/cyip_sflash.h"
#include "ip/cyip_peri_v2.h"
#include "ip/cyip_peri_ms_v2.h"
#include "ip/cyip_crypto_v2.h"
#include "ip/cyip_cpuss_v2.h"
#include "ip/cyip_fault_v2.h"
#include "ip/cyip_ipc_v2.h"
#include "ip/cyip_prot_v2.h"
#include "ip/cyip_flashc_v2.h"
#include "ip/cyip_srss.h"
#include "ip/cyip_backup.h"
#include "ip/cyip_dw_v2.h"
#include "ip/cyip_dmac_v2.h"
#include "ip/cyip_efuse.h"
#include "ip/cyip_efuse_data_psoc6_03.h"
#include "ip/cyip_hsiom_v2.h"
#include "ip/cyip_gpio_v2.h"
#include "ip/cyip_smartio_v2.h"
#include "ip/cyip_lpcomp.h"
#include "ip/cyip_csd.h"
#include "ip/cyip_tcpwm.h"
#include "ip/cyip_lcd_v2.h"
#include "ip/cyip_usbfs.h"
#include "ip/cyip_smif.h"
#include "ip/cyip_sdhc.h"
#include "ip/cyip_canfd.h"
#include "ip/cyip_scb.h"
#include "ip/cyip_ctbm.h"
#include "ip/cyip_ctdac.h"
#include "ip/cyip_sar.h"
#include "ip/cyip_pass.h"

/* IP type definitions */
typedef SFLASH_V1_Type SFLASH_Type;
typedef PERI_GR_V2_Type PERI_GR_Type;
typedef PERI_TR_GR_V2_Type PERI_TR_GR_Type;
typedef PERI_TR_1TO1_GR_V2_Type PERI_TR_1TO1_GR_Type;
typedef PERI_V2_Type PERI_Type;
typedef PERI_MS_PPU_PR_V2_Type PERI_MS_PPU_PR_Type;
typedef PERI_MS_PPU_FX_V2_Type PERI_MS_PPU_FX_Type;
typedef PERI_MS_V2_Type PERI_MS_Type;
typedef CRYPTO_V2_Type CRYPTO_Type;
typedef CPUSS_V2_Type CPUSS_Type;
typedef FAULT_STRUCT_V2_Type FAULT_STRUCT_Type;
typedef FAULT_V2_Type FAULT_Type;
typedef IPC_STRUCT_V2_Type IPC_STRUCT_Type;
typedef IPC_INTR_STRUCT_V2_Type IPC_INTR_STRUCT_Type;
typedef IPC_V2_Type IPC_Type;
typedef PROT_SMPU_SMPU_STRUCT_V2_Type PROT_SMPU_SMPU_STRUCT_Type;
typedef PROT_SMPU_V2_Type PROT_SMPU_Type;
typedef PROT_MPU_MPU_STRUCT_V2_Type PROT_MPU_MPU_STRUCT_Type;
typedef PROT_MPU_V2_Type PROT_MPU_Type;
typedef PROT_V2_Type PROT_Type;
typedef FLASHC_FM_CTL_V2_Type FLASHC_FM_CTL_Type;
typedef FLASHC_V2_Type FLASHC_Type;
typedef MCWDT_STRUCT_V1_Type MCWDT_STRUCT_Type;
typedef SRSS_V1_Type SRSS_Type;
typedef BACKUP_V1_Type BACKUP_Type;
typedef DW_CH_STRUCT_V2_Type DW_CH_STRUCT_Type;
typedef DW_V2_Type DW_Type;
typedef DMAC_CH_V2_Type DMAC_CH_Type;
typedef DMAC_V2_Type DMAC_Type;
typedef EFUSE_V1_Type EFUSE_Type;
typedef HSIOM_PRT_V2_Type HSIOM_PRT_Type;
typedef HSIOM_V2_Type HSIOM_Type;
typedef GPIO_PRT_V2_Type GPIO_PRT_Type;
typedef GPIO_V2_Type GPIO_Type;
typedef SMARTIO_PRT_V2_Type SMARTIO_PRT_Type;
typedef SMARTIO_V2_Type SMARTIO_Type;
typedef LPCOMP_V1_Type LPCOMP_Type;
typedef CSD_V1_Type CSD_Type;
typedef TCPWM_CNT_V1_Type TCPWM_CNT_Type;
typedef TCPWM_V1_Type TCPWM_Type;
typedef LCD_V2_Type LCD_Type;
typedef USBFS_USBDEV_V1_Type USBFS_USBDEV_Type;
typedef USBFS_USBLPM_V1_Type USBFS_USBLPM_Type;
typedef USBFS_USBHOST_V1_Type USBFS_USBHOST_Type;
typedef USBFS_V1_Type USBFS_Type;
typedef SMIF_DEVICE_V1_Type SMIF_DEVICE_Type;
typedef SMIF_V1_Type SMIF_Type;
typedef SDHC_WRAP_V1_Type SDHC_WRAP_Type;
typedef SDHC_CORE_V1_Type SDHC_CORE_Type;
typedef SDHC_V1_Type SDHC_Type;
typedef CANFD_CH_M_TTCAN_V1_Type CANFD_CH_M_TTCAN_Type;
typedef CANFD_CH_V1_Type CANFD_CH_Type;
typedef CANFD_V1_Type CANFD_Type;
typedef CySCB_V1_Type CySCB_Type;
typedef CTBM_V1_Type CTBM_Type;
typedef CTDAC_V1_Type CTDAC_Type;
typedef SAR_V1_Type SAR_Type;
typedef PASS_AREF_V1_Type PASS_AREF_Type;
typedef PASS_V1_Type PASS_Type;

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
/* UDB present or not ('0': no, '1': yes) */
#define CPUSS_UDB_PRESENT               0u
/* MBIST MMIO for Synopsys MBIST ('0': no, '1': yes). Set this to '1' only for the
   chips which doesn't use mxdft. */
#define CPUSS_MBIST_MMIO_PRESENT        1u
/* System RAM 0 size in kilobytes */
#define CPUSS_SRAM0_SIZE                256u
/* Number of macros used to implement System RAM 0. Example: 8 if 256 KB System
   SRAM0 is implemented with 8 32KB macros. */
#define CPUSS_RAMC0_MACRO_NR            8u
/* System RAM 1 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC1_PRESENT             0u
/* System RAM 1 size in kilobytes */
#define CPUSS_SRAM1_SIZE                1u
/* Number of macros used to implement System RAM 1. Example: 8 if 256 KB System
   RAM 1 is implemented with 8 32KB macros. */
#define CPUSS_RAMC1_MACRO_NR            1u
/* System RAM 2 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC2_PRESENT             0u
/* System RAM 2 size in kilobytes */
#define CPUSS_SRAM2_SIZE                1u
/* Number of macros used to implement System RAM 2. Example: 8 if 256 KB System
   RAM 2 is implemented with 8 32KB macros. */
#define CPUSS_RAMC2_MACRO_NR            1u
/* System SRAM(s) ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_PRESENT          0u
/* System SRAM(s) address ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_ADDR_PRESENT     0u
/* ECC present in either system RAM or interrupt handler (RAMC_ECC_PRESENT) */
#define CPUSS_ECC_PRESENT               0u
/* DataWire SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_PRESENT            0u
/* DataWire SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_ADDR_PRESENT       0u
/* System ROM size in KB */
#define CPUSS_ROM_SIZE                  64u
/* Number of macros used to implement system ROM. Example: 4 if 512 KB system ROM
   is implemented with 4 128KB macros. */
#define CPUSS_ROMC_MACRO_NR             1u
/* Flash memory type ('0' : SONOS, '1': ECT) */
#define CPUSS_FLASHC_ECT                0u
/* Flash main region size in KB */
#define CPUSS_FLASH_SIZE                512u
/* Flash work region size in KB (EEPROM emulation, data) */
#define CPUSS_WFLASH_SIZE               32u
/* Flash supervisory region size in KB */
#define CPUSS_SFLASH_SIZE               32u
/* Flash data output word size (in Bytes) */
#define CPUSS_FLASHC_MAIN_DATA_WIDTH    16u
/* SONOS Flash RWW present or not ('0': no, '1': yes) When RWW is '0', No special
   sectors present in Flash. Part of main sector 0 is allowcated for Supervisory
   Flash, and no Work Flash present. */
#define CPUSS_FLASHC_SONOS_RWW          1u
/* SONOS Flash, number of main sectors. */
#define CPUSS_FLASHC_SONOS_MAIN_SECTORS 2u
/* SONOS Flash, number of rows per main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_ROWS    512u
/* SONOS Flash, number of words per row of main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_WORDS   128u
/* SONOS Flash, number of special sectors. */
#define CPUSS_FLASHC_SONOS_SPL_SECTORS  2u
/* SONOS Flash, number of rows per special sector. */
#define CPUSS_FLASHC_SONOS_SPL_ROWS     64u
/* Flash memory ECC present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASH_ECC_PRESENT  0u
/* Flash cache SRAM(s) ECC present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_RAM_ECC_PRESENT    0u
/* Number of external slaves directly connected to slow AHB-Lite infrastructure.
   Maximum nubmer of slave supported is 4. Width of this parameter is 4-bits.
   1-bit mask for each slave indicating present or not. Example: 4'b0011 - slave
   0 and slave 1 are present. Note: The SLOW_SLx_ADDR and SLOW_SLx_MASK
   parameters (for the slaves present) should be derived from the Memory Map. */
#define CPUSS_SLOW_SL_PRESENT           1u
/* Number of external slaves directly connected to fast AHB-Lite infrastructure.
   Maximum nubmer of slave supported is 4. Width of this parameter is 4-bits.
   1-bit mask for each slave indicating present or not. Example: 4'b0011 - slave
   0 and slave 1 are present. Note: The FAST_SLx_ADDR and FAST_SLx_MASK
   parameters (for the slaves present) should be derived from the Memory Map. */
#define CPUSS_FAST_SL_PRESENT           1u
/* Number of external masters driving the slow AHB-Lite infrastructure. Maximum
   number of masters supported is 2. Width of this parameter is 2-bits. 1-bit
   mask for each master indicating present or not. Example: 2'b01 - master 0 is
   present. */
#define CPUSS_SLOW_MS_PRESENT           1u
/* System interrupt functionality present or not ('0': no; '1': yes). Not used for
   CM0+ PCU, which always uses system interrupt functionality. */
#define CPUSS_SYSTEM_IRQ_PRESENT        0u
/* Number of total interrupt request inputs to CPUSS */
#define CPUSS_SYSTEM_INT_NR             174u
/* Number of DeepSleep wakeup interrupt inputs to CPUSS */
#define CPUSS_SYSTEM_DPSLP_INT_NR       39u
/* Width of the CM4 interrupt priority bits. Legal range [3,8] Example: 3 = 8
   levels of priority 8 = 256 levels of priority */
#define CPUSS_CM4_LVL_WIDTH             3u
/* CM4 Floating point unit present or not (0=No, 1=Yes) */
#define CPUSS_CM4_FPU_PRESENT           1u
/* Debug level. Legal range [0,3] (0= No support, 1= Minimum: CM0/4 both 2
   breakpoints +1 watchpoint, 2= Full debug: CM0/4 have 4/6 breakpoints, 2/4
   watchpoints and 0/2 literal compare, 3= Full debug + data matching) */
#define CPUSS_DEBUG_LVL                 3u
/* Trace level. Legal range [0,2] (0= No tracing, 1= ITM + TPIU + SWO, 2= ITM +
   ETM + TPIU + SWO) Note: CM4 HTM is not supported. Hence vaule 3 for trace
   level is not supported in CPUSS. */
#define CPUSS_TRACE_LVL                 2u
/* Embedded Trace Buffer present or not (0=No, 1=Yes) */
#define CPUSS_ETB_PRESENT               0u
/* CM0+ MTB SRAM buffer size in kilobytes. Legal vaules 4, 8 or 16 */
#define CPUSS_MTB_SRAM_SIZE             4u
/* CM4 ETB SRAM buffer size in kilobytes. Legal vaules 4, 8 or 16 */
#define CPUSS_ETB_SRAM_SIZE             8u
/* PTM interface present (0=No, 1=Yes) */
#define CPUSS_PTM_PRESENT               0u
/* Width of the PTM interface in bits ([2,32]) */
#define CPUSS_PTM_WIDTH                 1u
/* Width of the TPIU interface in bits ([1,4]) */
#define CPUSS_TPIU_WIDTH                4u
/* CoreSight Part Identification Number */
#define CPUSS_JEPID                     52u
/* CoreSight Part Identification Number */
#define CPUSS_JEPCONTINUATION           0u
/* CoreSight Part Identification Number */
#define CPUSS_FAMILYID                  261u
/* ROM trim register width (for ARM 3, for Synopsys 5) */
#define CPUSS_ROM_TRIM_WIDTH            5u
/* ROM trim register default (for both ARM and Synopsys 0x0000_0012) */
#define CPUSS_ROM_TRIM_DEFAULT          18u
/* RAM trim register width (for ARM 8, for Synopsys 15) */
#define CPUSS_RAM_TRIM_WIDTH            15u
/* RAM trim register default (for ARM 0x0000_0062 and for Synopsys 0x0000_6012) */
#define CPUSS_RAM_TRIM_DEFAULT          24594u
/* Cryptography IP present or not (0=No, 1=Yes) */
#define CPUSS_CRYPTO_PRESENT            1u
/* DataWire and DMAC SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_SW_TR_PRESENT             0u
/* DataWire 0 present or not (0=No, 1=Yes) */
#define CPUSS_DW0_PRESENT               1u
/* Number of DataWire 0 channels (8, 16 or 32) */
#define CPUSS_DW0_CH_NR                 29u
/* DataWire 1 present or not (0=No, 1=Yes) */
#define CPUSS_DW1_PRESENT               1u
/* Number of DataWire 1 channels (8, 16 or 32) */
#define CPUSS_DW1_CH_NR                 32u
/* DMA controller present or not ('0': no, '1': yes) */
#define CPUSS_DMAC_PRESENT              1u
/* Number of DMA controller channels ([1, 8]) */
#define CPUSS_DMAC_CH_NR                2u
/* DMAC SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_CH_SW_TR_PRESENT          0u
/* Copy value from Globals */
#define CPUSS_CHIP_TOP_PROFILER_PRESENT 0u
/* ETAS Calibration support pin out present (automotive only) */
#define CPUSS_CHIP_TOP_CAL_SUP_NZ_PRESENT 0u
/* TRACE_LVL>0 */
#define CPUSS_CHIP_TOP_TRACE_PRESENT    1u
/* DataWire SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_CH_STRUCT_SW_TR_PRESENT   0u
/* Number of DataWire controllers present (max 2) (same as DW.NR above) */
#define CPUSS_CPUSS_DW_DW_NR            2u
/* Number of channels in each DataWire controller */
#define CPUSS_CPUSS_DW_DW_NR0_DW_CH_NR  29u
/* Width of a channel number in bits */
#define CPUSS_CPUSS_DW_DW_NR0_DW_CH_NR_WIDTH 5u
/* Number of channels in each DataWire controller */
#define CPUSS_CPUSS_DW_DW_NR1_DW_CH_NR  32u
/* Width of a channel number in bits */
#define CPUSS_CPUSS_DW_DW_NR1_DW_CH_NR_WIDTH 5u
/* Cryptography SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_CRYPTO_ECC_PRESENT        0u
/* Cryptography SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_CRYPTO_ECC_ADDR_PRESENT   0u
/* AES cipher support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_AES                1u
/* (Tripple) DES cipher support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_DES                1u
/* Chacha support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_CHACHA             1u
/* Pseudo random number generation support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_PR                 1u
/* SHA1 hash support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_SHA1               1u
/* SHA2 hash support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_SHA2               1u
/* SHA3 hash support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_SHA3               1u
/* Cyclic Redundancy Check support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_CRC                1u
/* True random number generation support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_TR                 1u
/* Vector unit support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_VU                 1u
/* Galios/Counter Mode (GCM) support ('0': no, '1': yes) */
#define CPUSS_CRYPTO_GCM                1u
/* Number of 32-bit words in the IP internal memory buffer (from the set [64, 128,
   256, 512, 1024, 2048, 4096], to allow for a 256 B, 512 B, 1 kB, 2 kB, 4 kB, 8
   kB and 16 kB memory buffer) */
#define CPUSS_CRYPTO_BUFF_SIZE          1024u
/* Number of DMA controller channels ([1, 8]) */
#define CPUSS_DMAC_CH_NR                2u
/* Number of DataWire controllers present (max 2) */
#define CPUSS_DW_NR                     2u
/* DataWire SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_PRESENT            0u
/* Number of fault structures. Legal range [1, 4] */
#define CPUSS_FAULT_FAULT_NR            2u
/* Number of Flash BIST_DATA registers */
#define CPUSS_FLASHC_FLASHC_BIST_DATA_NR 4u
/* Page size in # of 32-bit words (1: 4 bytes, 2: 8 bytes, ... */
#define CPUSS_FLASHC_PA_SIZE            128u
/* SONOS Flash is used or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASHC_IS_SONOS    1u
/* eCT Flash is used or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASHC_IS_ECT      0u
/* Number of IPC structures. Legal range [1, 16] */
#define CPUSS_IPC_IPC_NR                16u
/* Number of IPC interrupt structures. Legal range [1, 16] */
#define CPUSS_IPC_IPC_IRQ_NR            16u
/* Master 0 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS0_PC_NR_MINUS1 7u
/* Master 1 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS1_PC_NR_MINUS1 0u
/* Master 2 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS2_PC_NR_MINUS1 0u
/* Master 3 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS3_PC_NR_MINUS1 0u
/* Master 4 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS4_PC_NR_MINUS1 0u
/* Master 5 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS5_PC_NR_MINUS1 7u
/* Master 6 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS6_PC_NR_MINUS1 0u
/* Master 7 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS7_PC_NR_MINUS1 0u
/* Master 8 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS8_PC_NR_MINUS1 0u
/* Master 9 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS9_PC_NR_MINUS1 0u
/* Master 10 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS10_PC_NR_MINUS1 0u
/* Master 11 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS11_PC_NR_MINUS1 0u
/* Master 12 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS12_PC_NR_MINUS1 0u
/* Master 13 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS13_PC_NR_MINUS1 0u
/* Master 14 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS14_PC_NR_MINUS1 7u
/* Master 15 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS15_PC_NR_MINUS1 7u
/* Number of SMPU protection structures */
#define CPUSS_PROT_SMPU_STRUCT_NR       16u
/* Number of protection contexts supported minus 1. Legal range [1,16] */
#define CPUSS_SMPU_STRUCT_PC_NR_MINUS1  7u
/* Number of instantiated eFUSE macros (256 bit macros). Legal range [1, 16] */
#define EFUSE_EFUSE_NR                  4u
/* Number of GPIO ports in range 0..31 */
#define IOSS_GPIO_GPIO_PORT_NR_0_31     15u
/* Number of GPIO ports in range 32..63 */
#define IOSS_GPIO_GPIO_PORT_NR_32_63    0u
/* Number of GPIO ports in range 64..95 */
#define IOSS_GPIO_GPIO_PORT_NR_64_95    0u
/* Number of GPIO ports in range 96..127 */
#define IOSS_GPIO_GPIO_PORT_NR_96_127   0u
/* Number of ports in device */
#define IOSS_GPIO_GPIO_PORT_NR          15u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR0_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_GPIO 0u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_AUTOLVL 0u
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
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR2_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_SLOW_IO1 1u
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
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_GPIO 0u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_AUTOLVL 0u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_SLOW_IO1 0u
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
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR5_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO2 1u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO3 1u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO4 1u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO5 1u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO6 1u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO7 1u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_GPIO 0u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_AUTOLVL 0u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_GPIO 0u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_AUTOLVL 0u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO0 1u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO1 1u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO7 0u
/* Number of AMUX splitter cells */
#define IOSS_HSIOM_AMUX_SPLIT_NR        6u
/* Number of HSIOM ports in device (same as GPIO.GPIO_PRT_NR) */
#define IOSS_HSIOM_HSIOM_PORT_NR        15u
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
/* Indicates the presence of alternate JTAG interface */
#define IOSS_HSIOM_ALTJTAG_PRESENT      0u
/* Mask of SMARTIO instances presence */
#define IOSS_SMARTIO_SMARTIO_MASK       768u
/* Number of ports supoprting up to 4 COMs */
#define LCD_NUMPORTS                    8u
/* Number of ports supporting up to 8 COMs */
#define LCD_NUMPORTS8                   8u
/* Number of ports supporting up to 16 COMs */
#define LCD_NUMPORTS16                  0u
/* Max number of LCD commons supported */
#define LCD_CHIP_TOP_COM_NR             8u
/* Max number of LCD pins (total) supported */
#define LCD_CHIP_TOP_PIN_NR             60u
/* Number of IREF outputs from AREF */
#define PASS_NR_IREFS                   4u
/* Number of CTBs in the Subsystem */
#define PASS_NR_CTBS                    0u
/* Number of CTDACs in the Subsystem */
#define PASS_NR_CTDACS                  0u
/* CTB0 Exists */
#define PASS_CTB0_EXISTS                0u
/* CTB1 Exists */
#define PASS_CTB1_EXISTS                0u
/* CTB2 Exists */
#define PASS_CTB2_EXISTS                0u
/* CTB3 Exists */
#define PASS_CTB3_EXISTS                0u
/* CTDAC0 Exists */
#define PASS_CTDAC0_EXISTS              0u
/* CTDAC1 Exists */
#define PASS_CTDAC1_EXISTS              0u
/* CTDAC2 Exists */
#define PASS_CTDAC2_EXISTS              0u
/* CTDAC3 Exists */
#define PASS_CTDAC3_EXISTS              0u
#define PASS_CTBM_CTDAC_PRESENT         0u
/* Number of SAR channels */
#define PASS_SAR_SAR_CHANNELS           16u
/* Averaging logic present in SAR */
#define PASS_SAR_SAR_AVERAGE            1u
/* Range detect logic present in SAR */
#define PASS_SAR_SAR_RANGEDET           1u
/* Support for UAB sampling */
#define PASS_SAR_SAR_UAB                0u
/* The number of protection contexts ([2, 16]). */
#define PERI_PC_NR                      8u
/* Master interface presence mask (4 bits) */
#define PERI_MS_PRESENT                 15u
/* Protection structures SRAM ECC present or not ('0': no, '1': yes) */
#define PERI_ECC_PRESENT                0u
/* Protection structures SRAM address ECC present or not ('0': no, '1': yes) */
#define PERI_ECC_ADDR_PRESENT           0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL4_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL7_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL8_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL9_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL10_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL12_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL5_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL8_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL9_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL11_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL15_PRESENT 1u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL4_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL5_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present (0:No, 1:Yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Number of programmable clocks (outputs) */
#define PERI_CLOCK_NR                   28u
/* Number of 8.0 dividers */
#define PERI_DIV_8_NR                   4u
/* Number of 16.0 dividers */
#define PERI_DIV_16_NR                  8u
/* Number of 16.5 (fractional) dividers */
#define PERI_DIV_16_5_NR                2u
/* Number of 24.5 (fractional) dividers */
#define PERI_DIV_24_5_NR                1u
/* Divider number width: max(1,roundup(log2(max(DIV_*_NR))) */
#define PERI_DIV_ADDR_WIDTH             3u
/* Timeout functionality present ('0': no, '1': yes) */
#define PERI_TIMEOUT_PRESENT            1u
/* Trigger module present (0=No, 1=Yes) */
#define PERI_TR                         1u
/* Number of trigger groups */
#define PERI_TR_GROUP_NR                11u
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
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR10_TR_GROUP_TR_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR0_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR1_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR2_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR3_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR4_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR5_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR6_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Trigger 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR7_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define PERI_MASTER_WIDTH               8u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB0_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB0_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB0_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB0_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB0_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB0_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB0_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB0_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB0_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB0_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB0_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB0_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB0_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB0_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB0_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB0_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB0_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB0_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB0_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB0_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB0_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB0_SPI_S_EZ                   0u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB0_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB0_CHIP_TOP_SPI_SEL_NR        3u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB1_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB1_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB1_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB1_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB1_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB1_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB1_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB1_I2C_M_S                    1u
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
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB1_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB1_CHIP_TOP_SPI_SEL_NR        4u
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
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB2_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB2_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB2_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB2_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB2_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB2_SPI                        1u
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
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB2_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB2_CHIP_TOP_SPI_SEL_NR        1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB3_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB3_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB3_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB3_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB3_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB3_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB3_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB3_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB3_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB3_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB3_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB3_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB3_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB3_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB3_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB3_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB3_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB3_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB3_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB3_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB3_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB3_SPI_S_EZ                   0u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB3_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB3_CHIP_TOP_SPI_SEL_NR        1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB4_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB4_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB4_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB4_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB4_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB4_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB4_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB4_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB4_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB4_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB4_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB4_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB4_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB4_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB4_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB4_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB4_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB4_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB4_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB4_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB4_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB4_SPI_S_EZ                   0u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB4_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB4_CHIP_TOP_SPI_SEL_NR        4u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB5_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB5_EC                         0u
/* I2C master support? ('0': no, '1': yes) */
#define SCB5_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB5_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB5_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB5_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB5_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB5_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB5_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB5_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB5_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB5_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB5_SPI_EC                     0u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB5_SPI_S_EC                   0u
/* UART support? ('0': no, '1': yes) */
#define SCB5_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB5_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB5_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB5_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB5_EZ                         0u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB5_EZ_CMD_RESP                0u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB5_I2C_S_EZ                   0u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB5_SPI_S_EZ                   0u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB5_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB5_CHIP_TOP_SPI_SEL_NR        4u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB6_DEEPSLEEP                  1u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB6_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB6_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB6_I2C_S                      1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB6_I2C                        1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB6_I2C_GLITCH                 1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB6_I2C_EC                     1u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB6_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB6_I2C_S_EC                   1u
/* SPI master support? ('0': no, '1': yes) */
#define SCB6_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB6_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB6_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB6_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB6_SPI_S_EC                   1u
/* UART support? ('0': no, '1': yes) */
#define SCB6_UART                       0u
/* SPI or UART (SPI | UART) */
#define SCB6_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB6_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB6_CMD_RESP                   1u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB6_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB6_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB6_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB6_SPI_S_EZ                   1u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB6_I2C_FAST_PLUS              1u
/* Number of used spi_select signals (max 4) */
#define SCB6_CHIP_TOP_SPI_SEL_NR        1u
/* Basically the max packet size, which gets double buffered in RAM 0: 512B
   (implies 1KB of RAM space for data) 1: 1KB (implies 2KB of RAM space for
   data) */
#define SDHC_MAX_BLK_SIZE               0u
/* 0: No Command Queuing Engine present 1: Command Queuing Engine present; this
   adds 288 bytes of space to the RAM for this purpose. */
#define SDHC_CQE_PRESENT                0u
/* 0: no retention of any SDHC_CORE regs 1: retention of SDHC_CORE regs that have
   the Retention flag (Note, CTL.ENABLE is always retained irrespective of this
   parameter) */
#define SDHC_RETENTION_PRESENT          1u
/* Chip top connect all 8 data pins (0= connect 4 data pins, 1= connect 8 data
   pins) */
#define SDHC_CHIP_TOP_DATA8_PRESENT     0u
/* Chip top connect card_detect */
#define SDHC_CHIP_TOP_CARD_DETECT_PRESENT 1u
/* Chip top connect card_mech_write_prot_in */
#define SDHC_CHIP_TOP_CARD_WRITE_PROT_PRESENT 1u
/* Chip top connect led_ctrl_out and led_ctrl_out_en */
#define SDHC_CHIP_TOP_LED_CTRL_PRESENT  0u
/* Chip top connect io_volt_sel_out and io_volt_sel_out_en */
#define SDHC_CHIP_TOP_IO_VOLT_SEL_PRESENT 1u
/* Chip top connect io_drive_strength_out and io_drive_strength_out_en */
#define SDHC_CHIP_TOP_IO_DRIVE_STRENGTH_PRESENT 0u
/* Chip top connect card_if_pwr_en_out and card_if_pwr_en_out_en */
#define SDHC_CHIP_TOP_CARD_IF_PWR_EN_PRESENT 1u
/* Chip top connect card_emmc_reset_n_out and card_emmc_reset_n_out_en */
#define SDHC_CHIP_TOP_CARD_EMMC_RESET_PRESENT 0u
/* Chip top connect interrupt_wakeup (not used for eMMC) */
#define SDHC_CHIP_TOP_INTERRUPT_WAKEUP_PRESENT 1u
/* Basically the max packet size, which gets double buffered in RAM 0: 512B
   (implies 1KB of RAM space for data) 1: 1KB (implies 2KB of RAM space for
   data) */
#define SDHC_CORE_MAX_BLK_SIZE          0u
/* 0: No Command Queuing Engine present 1: Command Queuing Engine present; this
   adds 288 bytes of space to the RAM for this purpose. */
#define SDHC_CORE_CQE_PRESENT           0u
/* 0: no retention of any SDHC_CORE regs 1: retention of SDHC_CORE regs that have
   the Retention flag (Note, CTL.ENABLE is always retained irrespective of this
   parameter) */
#define SDHC_CORE_RETENTION_PRESENT     1u
/* SONOS Flash is used or not ('0': no, '1': yes) */
#define SFLASH_FLASHC_IS_SONOS          1u
/* CPUSS_WOUNDING_PRESENT or not ('0': no, '1': yes) */
#define SFLASH_CPUSS_WOUNDING_PRESENT   0u
/* Base address of the SMIF XIP memory region. This address must be a multiple of
   the SMIF XIP memory capacity. This address must be a multiple of 64 KB. This
   address must be in the [0x0000:0000, 0x1fff:ffff] memory region. The XIP
   memory region should NOT overlap with other memory regions. */
#define SMIF_SMIF_XIP_ADDR              402653184u
/* Capacity of the SMIF XIP memory region. The more significant bits of this
   parameter must be '1' and the lesser significant bits of this paramter must
   be '0'. E.g., 0xfff0:0000 specifies a 1 MB memory region. Legal values are
   {0xffff:0000, 0xfffe:0000, 0xfffc:0000, 0xfff8:0000, 0xfff0:0000,
   0xffe0:0000, ..., 0xe000:0000}. */
#define SMIF_SMIF_XIP_MASK              4160749568u
/* Cryptography (AES) support ('0' = no support, '1' = support) */
#define SMIF_CRYPTO                     1u
/* Number of external devices supported ([1,4]) */
#define SMIF_DEVICE_NR                  3u
/* External device write support. This is a 4-bit field. Each external device has
   a dedicated bit. E.g., if bit 2 is '1', external device 2 has write support. */
#define SMIF_DEVICE_WR_EN               15u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SMIF_MASTER_WIDTH               8u
/* Chip top connect all 8 data pins (0= connect 4 or 6 data pins based on
   DATA6_PRESENT, 1= connect 8 data pins) */
#define SMIF_CHIP_TOP_DATA8_PRESENT     0u
/* Number of used spi_select signals (max 4) */
#define SMIF_CHIP_TOP_SPI_SEL_NR        3u
/* Number of regulator modules instantiated within SRSS, start with estimate,
   update after CMR feedback */
#define SRSS_NUM_ACTREG_PWRMOD          2u
/* Number of shorting switches between vccd and vccact (target dynamic voltage
   drop < 10mV) */
#define SRSS_NUM_ACTIVE_SWITCH          3u
/* ULP linear regulator system is present */
#define SRSS_ULPLINREG_PRESENT          1u
/* HT linear regulator system is present */
#define SRSS_HTLINREG_PRESENT           0u
/* Low-current buck regulator present. Can be derived from S40S_SISOBUCKLC_PRESENT
   or SIMOBUCK_PRESENT. */
#define SRSS_BUCKCTL_PRESENT            1u
/* Low-current SISO buck core regulator is present. Only compatible with ULP
   linear regulator system (ULPLINREG_PRESENT==1). */
#define SRSS_S40S_SISOBUCKLC_PRESENT    1u
/* SIMO buck core regulator is present. Only compatible with ULP linear regulator
   system (ULPLINREG_PRESENT==1). */
#define SRSS_SIMOBUCK_PRESENT           0u
/* Precision ILO (PILO) is present */
#define SRSS_PILO_PRESENT               0u
/* External Crystal Oscillator is present (high frequency) */
#define SRSS_ECO_PRESENT                1u
/* System Buck-Boost is present */
#define SRSS_SYSBB_PRESENT              0u
/* Number of clock paths. Must be > 0 */
#define SRSS_NUM_CLKPATH                5u
/* Number of PLLs present. Must be <= NUM_CLKPATH */
#define SRSS_NUM_PLL                    1u
/* Number of HFCLK roots present. Must be > 0 */
#define SRSS_NUM_HFROOT                 5u
/* Number of PWR_HIB_DATA registers, should not be needed if BACKUP_PRESENT */
#define SRSS_NUM_HIBDATA                1u
/* Backup domain is present (includes RTC and WCO) */
#define SRSS_BACKUP_PRESENT             1u
/* Mask of HFCLK root clock supervisors (CSV). For each clock root i, bit[i] of
   mask indicates presence of a CSV. */
#define SRSS_MASK_HFCSV                 0u
/* Clock supervisor is present on WCO. Must be 0 if BACKUP_PRESENT==0. */
#define SRSS_WCOCSV_PRESENT             0u
/* Number of software watchdog timers. */
#define SRSS_NUM_MCWDT                  2u
/* Number of DSI inputs into clock muxes. This is used for logic optimization. */
#define SRSS_NUM_DSI                    0u
/* Alternate high-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTHF_PRESENT              0u
/* Alternate low-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTLF_PRESENT              0u
/* Use the hardened clkactfllmux block */
#define SRSS_USE_HARD_CLKACTFLLMUX      1u
/* Number of clock paths, including direct paths in hardened clkactfllmux block
   (Must be >= NUM_CLKPATH) */
#define SRSS_HARD_CLKPATH               6u
/* Number of clock paths with muxes in hardened clkactfllmux block (Must be >=
   NUM_PLL+1) */
#define SRSS_HARD_CLKPATHMUX            6u
/* Number of HFCLKS present in hardened clkactfllmux block (Must be >= NUM_HFROOT) */
#define SRSS_HARD_HFROOT                6u
/* ECO mux is present in hardened clkactfllmux block (Must be >= ECO_PRESENT) */
#define SRSS_HARD_ECOMUX_PRESENT        1u
/* ALTHF mux is present in hardened clkactfllmux block (Must be >= ALTHF_PRESENT) */
#define SRSS_HARD_ALTHFMUX_PRESENT      1u
/* SRSS version is at least SRSS_VER1P3. Set to 1 for new products. Set to 0 for
   PSoC6ABLE2, PSoC6A2M. */
#define SRSS_SRSS_VER1P3                1u
/* Backup memory is present (only used when BACKUP_PRESENT==1) */
#define SRSS_BACKUP_BMEM_PRESENT        0u
/* Number of Backup registers to include (each is 32b). Only used when
   BACKUP_PRESENT==1. */
#define SRSS_BACKUP_NUM_BREG            16u
/* Number of counters per IP (1..32) */
#define TCPWM0_CNT_NR                   4u
/* Counter width (in number of bits) */
#define TCPWM0_CNT_CNT_WIDTH            32u
/* Number of counters per IP (1..32) */
#define TCPWM1_CNT_NR                   8u
/* Counter width (in number of bits) */
#define TCPWM1_CNT_CNT_WIDTH            16u

/* MMIO Targets Defines */
#define CY_MMIO_CRYPTO_GROUP_NR         1u
#define CY_MMIO_CRYPTO_SLAVE_NR         0u
#define CY_MMIO_CPUSS_GROUP_NR          2u
#define CY_MMIO_CPUSS_SLAVE_NR          0u
#define CY_MMIO_FAULT_GROUP_NR          2u
#define CY_MMIO_FAULT_SLAVE_NR          1u
#define CY_MMIO_IPC_GROUP_NR            2u
#define CY_MMIO_IPC_SLAVE_NR            2u
#define CY_MMIO_PROT_GROUP_NR           2u
#define CY_MMIO_PROT_SLAVE_NR           3u
#define CY_MMIO_FLASHC_GROUP_NR         2u
#define CY_MMIO_FLASHC_SLAVE_NR         4u
#define CY_MMIO_SRSS_GROUP_NR           2u
#define CY_MMIO_SRSS_SLAVE_NR           6u
#define CY_MMIO_BACKUP_GROUP_NR         2u
#define CY_MMIO_BACKUP_SLAVE_NR         7u
#define CY_MMIO_DW_GROUP_NR             2u
#define CY_MMIO_DW_SLAVE_NR             8u
#define CY_MMIO_DMAC_GROUP_NR           2u
#define CY_MMIO_DMAC_SLAVE_NR           10u
#define CY_MMIO_EFUSE_GROUP_NR          2u
#define CY_MMIO_EFUSE_SLAVE_NR          12u
#define CY_MMIO_HSIOM_GROUP_NR          3u
#define CY_MMIO_HSIOM_SLAVE_NR          0u
#define CY_MMIO_GPIO_GROUP_NR           3u
#define CY_MMIO_GPIO_SLAVE_NR           1u
#define CY_MMIO_SMARTIO_GROUP_NR        3u
#define CY_MMIO_SMARTIO_SLAVE_NR        2u
#define CY_MMIO_LPCOMP_GROUP_NR         3u
#define CY_MMIO_LPCOMP_SLAVE_NR         5u
#define CY_MMIO_CSD0_GROUP_NR           3u
#define CY_MMIO_CSD0_SLAVE_NR           6u
#define CY_MMIO_TCPWM0_GROUP_NR         3u
#define CY_MMIO_TCPWM0_SLAVE_NR         8u
#define CY_MMIO_TCPWM1_GROUP_NR         3u
#define CY_MMIO_TCPWM1_SLAVE_NR         9u
#define CY_MMIO_LCD0_GROUP_NR           3u
#define CY_MMIO_LCD0_SLAVE_NR           11u
#define CY_MMIO_USBFS0_GROUP_NR         3u
#define CY_MMIO_USBFS0_SLAVE_NR         15u
#define CY_MMIO_SMIF0_GROUP_NR          4u
#define CY_MMIO_SMIF0_SLAVE_NR          2u
#define CY_MMIO_SDHC0_GROUP_NR          4u
#define CY_MMIO_SDHC0_SLAVE_NR          6u
#define CY_MMIO_CANFD0_GROUP_NR         5u
#define CY_MMIO_CANFD0_SLAVE_NR         2u
#define CY_MMIO_SCB0_GROUP_NR           6u
#define CY_MMIO_SCB0_SLAVE_NR           0u
#define CY_MMIO_SCB1_GROUP_NR           6u
#define CY_MMIO_SCB1_SLAVE_NR           1u
#define CY_MMIO_SCB2_GROUP_NR           6u
#define CY_MMIO_SCB2_SLAVE_NR           2u
#define CY_MMIO_SCB3_GROUP_NR           6u
#define CY_MMIO_SCB3_SLAVE_NR           3u
#define CY_MMIO_SCB4_GROUP_NR           6u
#define CY_MMIO_SCB4_SLAVE_NR           4u
#define CY_MMIO_SCB5_GROUP_NR           6u
#define CY_MMIO_SCB5_SLAVE_NR           5u
#define CY_MMIO_SCB6_GROUP_NR           6u
#define CY_MMIO_SCB6_SLAVE_NR           6u
#define CY_MMIO_PASS_GROUP_NR           9u
#define CY_MMIO_PASS_SLAVE_NR           0u

/* Backward compatibility definitions */
#define CPUSS_IRQ_NR                    CPUSS_SYSTEM_INT_NR
#define CPUSS_DPSLP_IRQ_NR              CPUSS_SYSTEM_DPSLP_INT_NR

/* Protection regions */
typedef enum
{
    PROT_PERI_MAIN                  =   0,      /* Address 0x40000000, size 0x00002000 */
    PROT_PERI_GR0_GROUP             =   1,      /* Address 0x40004010, size 0x00000004 */
    PROT_PERI_GR1_GROUP             =   2,      /* Address 0x40004030, size 0x00000004 */
    PROT_PERI_GR2_GROUP             =   3,      /* Address 0x40004050, size 0x00000004 */
    PROT_PERI_GR3_GROUP             =   4,      /* Address 0x40004060, size 0x00000020 */
    PROT_PERI_GR4_GROUP             =   5,      /* Address 0x40004080, size 0x00000020 */
    PROT_PERI_GR5_GROUP             =   6,      /* Address 0x400040a0, size 0x00000020 */
    PROT_PERI_GR6_GROUP             =   7,      /* Address 0x400040c0, size 0x00000020 */
    PROT_PERI_GR9_GROUP             =   8,      /* Address 0x40004120, size 0x00000020 */
    PROT_PERI_TR                    =   9,      /* Address 0x40008000, size 0x00008000 */
    PROT_CRYPTO_MAIN                =  10,      /* Address 0x40100000, size 0x00000400 */
    PROT_CRYPTO_CRYPTO              =  11,      /* Address 0x40101000, size 0x00000800 */
    PROT_CRYPTO_BOOT                =  12,      /* Address 0x40102000, size 0x00000100 */
    PROT_CRYPTO_KEY0                =  13,      /* Address 0x40102100, size 0x00000004 */
    PROT_CRYPTO_KEY1                =  14,      /* Address 0x40102120, size 0x00000004 */
    PROT_CRYPTO_BUF                 =  15,      /* Address 0x40108000, size 0x00001000 */
    PROT_CPUSS_CM4                  =  16,      /* Address 0x40200000, size 0x00000400 */
    PROT_CPUSS_CM0                  =  17,      /* Address 0x40201000, size 0x00001000 */
    PROT_CPUSS_BOOT                 =  18,      /* Address 0x40202000, size 0x00000200 */
    PROT_CPUSS_CM0_INT              =  19,      /* Address 0x40208000, size 0x00000400 */
    PROT_CPUSS_CM4_INT              =  20,      /* Address 0x4020a000, size 0x00000400 */
    PROT_FAULT_STRUCT0_MAIN         =  21,      /* Address 0x40210000, size 0x00000100 */
    PROT_FAULT_STRUCT1_MAIN         =  22,      /* Address 0x40210100, size 0x00000100 */
    PROT_IPC_STRUCT0_IPC            =  23,      /* Address 0x40220000, size 0x00000020 */
    PROT_IPC_STRUCT1_IPC            =  24,      /* Address 0x40220020, size 0x00000020 */
    PROT_IPC_STRUCT2_IPC            =  25,      /* Address 0x40220040, size 0x00000020 */
    PROT_IPC_STRUCT3_IPC            =  26,      /* Address 0x40220060, size 0x00000020 */
    PROT_IPC_STRUCT4_IPC            =  27,      /* Address 0x40220080, size 0x00000020 */
    PROT_IPC_STRUCT5_IPC            =  28,      /* Address 0x402200a0, size 0x00000020 */
    PROT_IPC_STRUCT6_IPC            =  29,      /* Address 0x402200c0, size 0x00000020 */
    PROT_IPC_STRUCT7_IPC            =  30,      /* Address 0x402200e0, size 0x00000020 */
    PROT_IPC_STRUCT8_IPC            =  31,      /* Address 0x40220100, size 0x00000020 */
    PROT_IPC_STRUCT9_IPC            =  32,      /* Address 0x40220120, size 0x00000020 */
    PROT_IPC_STRUCT10_IPC           =  33,      /* Address 0x40220140, size 0x00000020 */
    PROT_IPC_STRUCT11_IPC           =  34,      /* Address 0x40220160, size 0x00000020 */
    PROT_IPC_STRUCT12_IPC           =  35,      /* Address 0x40220180, size 0x00000020 */
    PROT_IPC_STRUCT13_IPC           =  36,      /* Address 0x402201a0, size 0x00000020 */
    PROT_IPC_STRUCT14_IPC           =  37,      /* Address 0x402201c0, size 0x00000020 */
    PROT_IPC_STRUCT15_IPC           =  38,      /* Address 0x402201e0, size 0x00000020 */
    PROT_IPC_INTR_STRUCT0_INTR      =  39,      /* Address 0x40221000, size 0x00000010 */
    PROT_IPC_INTR_STRUCT1_INTR      =  40,      /* Address 0x40221020, size 0x00000010 */
    PROT_IPC_INTR_STRUCT2_INTR      =  41,      /* Address 0x40221040, size 0x00000010 */
    PROT_IPC_INTR_STRUCT3_INTR      =  42,      /* Address 0x40221060, size 0x00000010 */
    PROT_IPC_INTR_STRUCT4_INTR      =  43,      /* Address 0x40221080, size 0x00000010 */
    PROT_IPC_INTR_STRUCT5_INTR      =  44,      /* Address 0x402210a0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT6_INTR      =  45,      /* Address 0x402210c0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT7_INTR      =  46,      /* Address 0x402210e0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT8_INTR      =  47,      /* Address 0x40221100, size 0x00000010 */
    PROT_IPC_INTR_STRUCT9_INTR      =  48,      /* Address 0x40221120, size 0x00000010 */
    PROT_IPC_INTR_STRUCT10_INTR     =  49,      /* Address 0x40221140, size 0x00000010 */
    PROT_IPC_INTR_STRUCT11_INTR     =  50,      /* Address 0x40221160, size 0x00000010 */
    PROT_IPC_INTR_STRUCT12_INTR     =  51,      /* Address 0x40221180, size 0x00000010 */
    PROT_IPC_INTR_STRUCT13_INTR     =  52,      /* Address 0x402211a0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT14_INTR     =  53,      /* Address 0x402211c0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT15_INTR     =  54,      /* Address 0x402211e0, size 0x00000010 */
    PROT_PROT_SMPU_MAIN             =  55,      /* Address 0x40230000, size 0x00000040 */
    PROT_PROT_MPU0_MAIN             =  56,      /* Address 0x40234000, size 0x00000004 */
    PROT_PROT_MPU5_MAIN             =  57,      /* Address 0x40235400, size 0x00000400 */
    PROT_PROT_MPU14_MAIN            =  58,      /* Address 0x40237800, size 0x00000004 */
    PROT_PROT_MPU15_MAIN            =  59,      /* Address 0x40237c00, size 0x00000400 */
    PROT_FLASHC_MAIN                =  60,      /* Address 0x40240000, size 0x00000008 */
    PROT_FLASHC_CMD                 =  61,      /* Address 0x40240008, size 0x00000004 */
    PROT_FLASHC_DFT                 =  62,      /* Address 0x40240200, size 0x00000100 */
    PROT_FLASHC_CM0                 =  63,      /* Address 0x40240400, size 0x00000080 */
    PROT_FLASHC_CM4                 =  64,      /* Address 0x40240480, size 0x00000080 */
    PROT_FLASHC_CRYPTO              =  65,      /* Address 0x40240500, size 0x00000004 */
    PROT_FLASHC_DW0                 =  66,      /* Address 0x40240580, size 0x00000004 */
    PROT_FLASHC_DW1                 =  67,      /* Address 0x40240600, size 0x00000004 */
    PROT_FLASHC_DMAC                =  68,      /* Address 0x40240680, size 0x00000004 */
    PROT_FLASHC_EXT_MS0             =  69,      /* Address 0x40240700, size 0x00000004 */
    PROT_FLASHC_FM                  =  70,      /* Address 0x4024f000, size 0x00001000 */
    PROT_SRSS_MAIN1                 =  71,      /* Address 0x40260000, size 0x00000100 */
    PROT_SRSS_MAIN2                 =  72,      /* Address 0x40260100, size 0x00000010 */
    PROT_WDT                        =  73,      /* Address 0x40260180, size 0x00000010 */
    PROT_MAIN                       =  74,      /* Address 0x40260200, size 0x00000080 */
    PROT_SRSS_MAIN3                 =  75,      /* Address 0x40260300, size 0x00000100 */
    PROT_SRSS_MAIN4                 =  76,      /* Address 0x40260400, size 0x00000400 */
    PROT_SRSS_MAIN5                 =  77,      /* Address 0x40260800, size 0x00000008 */
    PROT_SRSS_MAIN6                 =  78,      /* Address 0x40267000, size 0x00001000 */
    PROT_SRSS_MAIN7                 =  79,      /* Address 0x4026ff00, size 0x00000080 */
    PROT_BACKUP_BACKUP              =  80,      /* Address 0x40270000, size 0x00010000 */
    PROT_DW0_DW                     =  81,      /* Address 0x40280000, size 0x00000080 */
    PROT_DW1_DW                     =  82,      /* Address 0x40290000, size 0x00000080 */
    PROT_DW0_DW_CRC                 =  83,      /* Address 0x40280100, size 0x00000080 */
    PROT_DW1_DW_CRC                 =  84,      /* Address 0x40290100, size 0x00000080 */
    PROT_DW0_CH_STRUCT0_CH          =  85,      /* Address 0x40288000, size 0x00000040 */
    PROT_DW0_CH_STRUCT1_CH          =  86,      /* Address 0x40288040, size 0x00000040 */
    PROT_DW0_CH_STRUCT2_CH          =  87,      /* Address 0x40288080, size 0x00000040 */
    PROT_DW0_CH_STRUCT3_CH          =  88,      /* Address 0x402880c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT4_CH          =  89,      /* Address 0x40288100, size 0x00000040 */
    PROT_DW0_CH_STRUCT5_CH          =  90,      /* Address 0x40288140, size 0x00000040 */
    PROT_DW0_CH_STRUCT6_CH          =  91,      /* Address 0x40288180, size 0x00000040 */
    PROT_DW0_CH_STRUCT7_CH          =  92,      /* Address 0x402881c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT8_CH          =  93,      /* Address 0x40288200, size 0x00000040 */
    PROT_DW0_CH_STRUCT9_CH          =  94,      /* Address 0x40288240, size 0x00000040 */
    PROT_DW0_CH_STRUCT10_CH         =  95,      /* Address 0x40288280, size 0x00000040 */
    PROT_DW0_CH_STRUCT11_CH         =  96,      /* Address 0x402882c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT12_CH         =  97,      /* Address 0x40288300, size 0x00000040 */
    PROT_DW0_CH_STRUCT13_CH         =  98,      /* Address 0x40288340, size 0x00000040 */
    PROT_DW0_CH_STRUCT14_CH         =  99,      /* Address 0x40288380, size 0x00000040 */
    PROT_DW0_CH_STRUCT15_CH         = 100,      /* Address 0x402883c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT16_CH         = 101,      /* Address 0x40288400, size 0x00000040 */
    PROT_DW0_CH_STRUCT17_CH         = 102,      /* Address 0x40288440, size 0x00000040 */
    PROT_DW0_CH_STRUCT18_CH         = 103,      /* Address 0x40288480, size 0x00000040 */
    PROT_DW0_CH_STRUCT19_CH         = 104,      /* Address 0x402884c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT20_CH         = 105,      /* Address 0x40288500, size 0x00000040 */
    PROT_DW0_CH_STRUCT21_CH         = 106,      /* Address 0x40288540, size 0x00000040 */
    PROT_DW0_CH_STRUCT22_CH         = 107,      /* Address 0x40288580, size 0x00000040 */
    PROT_DW0_CH_STRUCT23_CH         = 108,      /* Address 0x402885c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT24_CH         = 109,      /* Address 0x40288600, size 0x00000040 */
    PROT_DW0_CH_STRUCT25_CH         = 110,      /* Address 0x40288640, size 0x00000040 */
    PROT_DW0_CH_STRUCT26_CH         = 111,      /* Address 0x40288680, size 0x00000040 */
    PROT_DW0_CH_STRUCT27_CH         = 112,      /* Address 0x402886c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT28_CH         = 113,      /* Address 0x40288700, size 0x00000040 */
    PROT_DW1_CH_STRUCT0_CH          = 114,      /* Address 0x40298000, size 0x00000040 */
    PROT_DW1_CH_STRUCT1_CH          = 115,      /* Address 0x40298040, size 0x00000040 */
    PROT_DW1_CH_STRUCT2_CH          = 116,      /* Address 0x40298080, size 0x00000040 */
    PROT_DW1_CH_STRUCT3_CH          = 117,      /* Address 0x402980c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT4_CH          = 118,      /* Address 0x40298100, size 0x00000040 */
    PROT_DW1_CH_STRUCT5_CH          = 119,      /* Address 0x40298140, size 0x00000040 */
    PROT_DW1_CH_STRUCT6_CH          = 120,      /* Address 0x40298180, size 0x00000040 */
    PROT_DW1_CH_STRUCT7_CH          = 121,      /* Address 0x402981c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT8_CH          = 122,      /* Address 0x40298200, size 0x00000040 */
    PROT_DW1_CH_STRUCT9_CH          = 123,      /* Address 0x40298240, size 0x00000040 */
    PROT_DW1_CH_STRUCT10_CH         = 124,      /* Address 0x40298280, size 0x00000040 */
    PROT_DW1_CH_STRUCT11_CH         = 125,      /* Address 0x402982c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT12_CH         = 126,      /* Address 0x40298300, size 0x00000040 */
    PROT_DW1_CH_STRUCT13_CH         = 127,      /* Address 0x40298340, size 0x00000040 */
    PROT_DW1_CH_STRUCT14_CH         = 128,      /* Address 0x40298380, size 0x00000040 */
    PROT_DW1_CH_STRUCT15_CH         = 129,      /* Address 0x402983c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT16_CH         = 130,      /* Address 0x40298400, size 0x00000040 */
    PROT_DW1_CH_STRUCT17_CH         = 131,      /* Address 0x40298440, size 0x00000040 */
    PROT_DW1_CH_STRUCT18_CH         = 132,      /* Address 0x40298480, size 0x00000040 */
    PROT_DW1_CH_STRUCT19_CH         = 133,      /* Address 0x402984c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT20_CH         = 134,      /* Address 0x40298500, size 0x00000040 */
    PROT_DW1_CH_STRUCT21_CH         = 135,      /* Address 0x40298540, size 0x00000040 */
    PROT_DW1_CH_STRUCT22_CH         = 136,      /* Address 0x40298580, size 0x00000040 */
    PROT_DW1_CH_STRUCT23_CH         = 137,      /* Address 0x402985c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT24_CH         = 138,      /* Address 0x40298600, size 0x00000040 */
    PROT_DW1_CH_STRUCT25_CH         = 139,      /* Address 0x40298640, size 0x00000040 */
    PROT_DW1_CH_STRUCT26_CH         = 140,      /* Address 0x40298680, size 0x00000040 */
    PROT_DW1_CH_STRUCT27_CH         = 141,      /* Address 0x402986c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT28_CH         = 142,      /* Address 0x40298700, size 0x00000040 */
    PROT_DW1_CH_STRUCT29_CH         = 143,      /* Address 0x40298740, size 0x00000040 */
    PROT_DW1_CH_STRUCT30_CH         = 144,      /* Address 0x40298780, size 0x00000040 */
    PROT_DW1_CH_STRUCT31_CH         = 145,      /* Address 0x402987c0, size 0x00000040 */
    PROT_DMAC_TOP                   = 146,      /* Address 0x402a0000, size 0x00000010 */
    PROT_DMAC_CH0_CH                = 147,      /* Address 0x402a1000, size 0x00000100 */
    PROT_DMAC_CH1_CH                = 148,      /* Address 0x402a1100, size 0x00000100 */
    PROT_EFUSE_CTL                  = 149,      /* Address 0x402c0000, size 0x00000080 */
    PROT_EFUSE_DATA                 = 150,      /* Address 0x402c0800, size 0x00000200 */
    PROT_HSIOM_PRT0_PRT             = 151,      /* Address 0x40300000, size 0x00000008 */
    PROT_HSIOM_PRT1_PRT             = 152,      /* Address 0x40300010, size 0x00000008 */
    PROT_HSIOM_PRT2_PRT             = 153,      /* Address 0x40300020, size 0x00000008 */
    PROT_HSIOM_PRT3_PRT             = 154,      /* Address 0x40300030, size 0x00000008 */
    PROT_HSIOM_PRT4_PRT             = 155,      /* Address 0x40300040, size 0x00000008 */
    PROT_HSIOM_PRT5_PRT             = 156,      /* Address 0x40300050, size 0x00000008 */
    PROT_HSIOM_PRT6_PRT             = 157,      /* Address 0x40300060, size 0x00000008 */
    PROT_HSIOM_PRT7_PRT             = 158,      /* Address 0x40300070, size 0x00000008 */
    PROT_HSIOM_PRT8_PRT             = 159,      /* Address 0x40300080, size 0x00000008 */
    PROT_HSIOM_PRT9_PRT             = 160,      /* Address 0x40300090, size 0x00000008 */
    PROT_HSIOM_PRT10_PRT            = 161,      /* Address 0x403000a0, size 0x00000008 */
    PROT_HSIOM_PRT11_PRT            = 162,      /* Address 0x403000b0, size 0x00000008 */
    PROT_HSIOM_PRT12_PRT            = 163,      /* Address 0x403000c0, size 0x00000008 */
    PROT_HSIOM_PRT13_PRT            = 164,      /* Address 0x403000d0, size 0x00000008 */
    PROT_HSIOM_PRT14_PRT            = 165,      /* Address 0x403000e0, size 0x00000008 */
    PROT_HSIOM_AMUX                 = 166,      /* Address 0x40302000, size 0x00000020 */
    PROT_HSIOM_MON                  = 167,      /* Address 0x40302200, size 0x00000010 */
    PROT_GPIO_PRT0_PRT              = 168,      /* Address 0x40310000, size 0x00000040 */
    PROT_GPIO_PRT1_PRT              = 169,      /* Address 0x40310080, size 0x00000040 */
    PROT_GPIO_PRT2_PRT              = 170,      /* Address 0x40310100, size 0x00000040 */
    PROT_GPIO_PRT3_PRT              = 171,      /* Address 0x40310180, size 0x00000040 */
    PROT_GPIO_PRT4_PRT              = 172,      /* Address 0x40310200, size 0x00000040 */
    PROT_GPIO_PRT5_PRT              = 173,      /* Address 0x40310280, size 0x00000040 */
    PROT_GPIO_PRT6_PRT              = 174,      /* Address 0x40310300, size 0x00000040 */
    PROT_GPIO_PRT7_PRT              = 175,      /* Address 0x40310380, size 0x00000040 */
    PROT_GPIO_PRT8_PRT              = 176,      /* Address 0x40310400, size 0x00000040 */
    PROT_GPIO_PRT9_PRT              = 177,      /* Address 0x40310480, size 0x00000040 */
    PROT_GPIO_PRT10_PRT             = 178,      /* Address 0x40310500, size 0x00000040 */
    PROT_GPIO_PRT11_PRT             = 179,      /* Address 0x40310580, size 0x00000040 */
    PROT_GPIO_PRT12_PRT             = 180,      /* Address 0x40310600, size 0x00000040 */
    PROT_GPIO_PRT13_PRT             = 181,      /* Address 0x40310680, size 0x00000040 */
    PROT_GPIO_PRT14_PRT             = 182,      /* Address 0x40310700, size 0x00000040 */
    PROT_GPIO_PRT0_CFG              = 183,      /* Address 0x40310040, size 0x00000020 */
    PROT_GPIO_PRT1_CFG              = 184,      /* Address 0x403100c0, size 0x00000008 */
    PROT_GPIO_PRT2_CFG              = 185,      /* Address 0x40310140, size 0x00000020 */
    PROT_GPIO_PRT3_CFG              = 186,      /* Address 0x403101c0, size 0x00000020 */
    PROT_GPIO_PRT4_CFG              = 187,      /* Address 0x40310240, size 0x00000008 */
    PROT_GPIO_PRT5_CFG              = 188,      /* Address 0x403102c0, size 0x00000020 */
    PROT_GPIO_PRT6_CFG              = 189,      /* Address 0x40310340, size 0x00000020 */
    PROT_GPIO_PRT7_CFG              = 190,      /* Address 0x403103c0, size 0x00000020 */
    PROT_GPIO_PRT8_CFG              = 191,      /* Address 0x40310440, size 0x00000020 */
    PROT_GPIO_PRT9_CFG              = 192,      /* Address 0x403104c0, size 0x00000020 */
    PROT_GPIO_PRT10_CFG             = 193,      /* Address 0x40310540, size 0x00000020 */
    PROT_GPIO_PRT11_CFG             = 194,      /* Address 0x403105c0, size 0x00000020 */
    PROT_GPIO_PRT12_CFG             = 195,      /* Address 0x40310640, size 0x00000020 */
    PROT_GPIO_PRT13_CFG             = 196,      /* Address 0x403106c0, size 0x00000008 */
    PROT_GPIO_PRT14_CFG             = 197,      /* Address 0x40310740, size 0x00000008 */
    PROT_GPIO_GPIO                  = 198,      /* Address 0x40314000, size 0x00000040 */
    PROT_GPIO_TEST                  = 199,      /* Address 0x40315000, size 0x00000008 */
    PROT_SMARTIO_PRT8_PRT           = 200,      /* Address 0x40320800, size 0x00000100 */
    PROT_SMARTIO_PRT9_PRT           = 201,      /* Address 0x40320900, size 0x00000100 */
    PROT_LPCOMP                     = 202,      /* Address 0x40350000, size 0x00010000 */
    PROT_CSD0                       = 203,      /* Address 0x40360000, size 0x00001000 */
    PROT_TCPWM0                     = 204,      /* Address 0x40380000, size 0x00010000 */
    PROT_TCPWM1                     = 205,      /* Address 0x40390000, size 0x00010000 */
    PROT_LCD0                       = 206,      /* Address 0x403b0000, size 0x00010000 */
    PROT_USBFS0                     = 207,      /* Address 0x403f0000, size 0x00010000 */
    PROT_SMIF0                      = 208,      /* Address 0x40420000, size 0x00010000 */
    PROT_SDHC0                      = 209,      /* Address 0x40460000, size 0x00010000 */
    PROT_CANFD0_CH0_CH              = 210,      /* Address 0x40520000, size 0x00000200 */
    PROT_CANFD0_MAIN                = 211,      /* Address 0x40521000, size 0x00000040 */
    PROT_CANFD0_BUF                 = 212,      /* Address 0x40530000, size 0x00010000 */
    PROT_SCB0                       = 213,      /* Address 0x40600000, size 0x00010000 */
    PROT_SCB1                       = 214,      /* Address 0x40610000, size 0x00010000 */
    PROT_SCB2                       = 215,      /* Address 0x40620000, size 0x00010000 */
    PROT_SCB3                       = 216,      /* Address 0x40630000, size 0x00010000 */
    PROT_SCB4                       = 217,      /* Address 0x40640000, size 0x00010000 */
    PROT_SCB5                       = 218,      /* Address 0x40650000, size 0x00010000 */
    PROT_SCB6                       = 219,      /* Address 0x40660000, size 0x00010000 */
    PROT_PASS                       = 220       /* Address 0x40900000, size 0x00100000 */
} cy_en_prot_region_t;

#endif /* _PSOC6_03_CONFIG_H_ */


/* [] END OF FILE */
