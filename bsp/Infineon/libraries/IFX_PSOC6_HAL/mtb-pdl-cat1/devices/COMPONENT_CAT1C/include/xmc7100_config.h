/***************************************************************************//**
* \file xmc7100_config.h
*
* \brief
* XMC7100 device configuration header
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

#ifndef _XMC7100_CONFIG_H_
#define _XMC7100_CONFIG_H_

/* Clock Connections */
typedef enum
{
    PCLK_CPUSS_CLOCK_TRACE_IN       = 0x0000u,  /* cpuss.clock_trace_in */
    PCLK_SMARTIO12_CLOCK            = 0x0001u,  /* smartio[12].clock */
    PCLK_SMARTIO13_CLOCK            = 0x0002u,  /* smartio[13].clock */
    PCLK_SMARTIO14_CLOCK            = 0x0003u,  /* smartio[14].clock */
    PCLK_SMARTIO15_CLOCK            = 0x0004u,  /* smartio[15].clock */
    PCLK_SMARTIO17_CLOCK            = 0x0005u,  /* smartio[17].clock */
    PCLK_CANFD0_CLOCK_CAN0          = 0x0100u,  /* canfd[0].clock_can[0] */
    PCLK_CANFD0_CLOCK_CAN1          = 0x0101u,  /* canfd[0].clock_can[1] */
    PCLK_CANFD0_CLOCK_CAN2          = 0x0102u,  /* canfd[0].clock_can[2] */
    PCLK_CANFD0_CLOCK_CAN3          = 0x0103u,  /* canfd[0].clock_can[3] */
    PCLK_CANFD1_CLOCK_CAN0          = 0x0104u,  /* canfd[1].clock_can[0] */
    PCLK_CANFD1_CLOCK_CAN1          = 0x0105u,  /* canfd[1].clock_can[1] */
    PCLK_CANFD1_CLOCK_CAN2          = 0x0106u,  /* canfd[1].clock_can[2] */
    PCLK_CANFD1_CLOCK_CAN3          = 0x0107u,  /* canfd[1].clock_can[3] */
    PCLK_LIN0_CLOCK_CH_EN0          = 0x0108u,  /* lin[0].clock_ch_en[0] */
    PCLK_LIN0_CLOCK_CH_EN1          = 0x0109u,  /* lin[0].clock_ch_en[1] */
    PCLK_LIN0_CLOCK_CH_EN2          = 0x010Au,  /* lin[0].clock_ch_en[2] */
    PCLK_LIN0_CLOCK_CH_EN3          = 0x010Bu,  /* lin[0].clock_ch_en[3] */
    PCLK_LIN0_CLOCK_CH_EN4          = 0x010Cu,  /* lin[0].clock_ch_en[4] */
    PCLK_LIN0_CLOCK_CH_EN5          = 0x010Du,  /* lin[0].clock_ch_en[5] */
    PCLK_LIN0_CLOCK_CH_EN6          = 0x010Eu,  /* lin[0].clock_ch_en[6] */
    PCLK_LIN0_CLOCK_CH_EN7          = 0x010Fu,  /* lin[0].clock_ch_en[7] */
    PCLK_LIN0_CLOCK_CH_EN8          = 0x0110u,  /* lin[0].clock_ch_en[8] */
    PCLK_LIN0_CLOCK_CH_EN9          = 0x0111u,  /* lin[0].clock_ch_en[9] */
    PCLK_LIN0_CLOCK_CH_EN10         = 0x0112u,  /* lin[0].clock_ch_en[10] */
    PCLK_LIN0_CLOCK_CH_EN11         = 0x0113u,  /* lin[0].clock_ch_en[11] */
    PCLK_LIN0_CLOCK_CH_EN12         = 0x0114u,  /* lin[0].clock_ch_en[12] */
    PCLK_LIN0_CLOCK_CH_EN13         = 0x0115u,  /* lin[0].clock_ch_en[13] */
    PCLK_LIN0_CLOCK_CH_EN14         = 0x0116u,  /* lin[0].clock_ch_en[14] */
    PCLK_LIN0_CLOCK_CH_EN15         = 0x0117u,  /* lin[0].clock_ch_en[15] */
    PCLK_SCB0_CLOCK                 = 0x0118u,  /* scb[0].clock */
    PCLK_SCB1_CLOCK                 = 0x0119u,  /* scb[1].clock */
    PCLK_SCB2_CLOCK                 = 0x011Au,  /* scb[2].clock */
    PCLK_SCB3_CLOCK                 = 0x011Bu,  /* scb[3].clock */
    PCLK_SCB4_CLOCK                 = 0x011Cu,  /* scb[4].clock */
    PCLK_SCB5_CLOCK                 = 0x011Du,  /* scb[5].clock */
    PCLK_SCB6_CLOCK                 = 0x011Eu,  /* scb[6].clock */
    PCLK_SCB7_CLOCK                 = 0x011Fu,  /* scb[7].clock */
    PCLK_SCB8_CLOCK                 = 0x0120u,  /* scb[8].clock */
    PCLK_SCB9_CLOCK                 = 0x0121u,  /* scb[9].clock */
    PCLK_SCB10_CLOCK                = 0x0122u,  /* scb[10].clock */
    PCLK_PASS0_CLOCK_SAR0           = 0x0123u,  /* pass[0].clock_sar[0] */
    PCLK_PASS0_CLOCK_SAR1           = 0x0124u,  /* pass[0].clock_sar[1] */
    PCLK_PASS0_CLOCK_SAR2           = 0x0125u,  /* pass[0].clock_sar[2] */
    PCLK_TCPWM0_CLOCKS0             = 0x0126u,  /* tcpwm[0].clocks[0] */
    PCLK_TCPWM0_CLOCKS1             = 0x0127u,  /* tcpwm[0].clocks[1] */
    PCLK_TCPWM0_CLOCKS2             = 0x0128u,  /* tcpwm[0].clocks[2] */
    PCLK_TCPWM0_CLOCKS3             = 0x0129u,  /* tcpwm[0].clocks[3] */
    PCLK_TCPWM0_CLOCKS4             = 0x012Au,  /* tcpwm[0].clocks[4] */
    PCLK_TCPWM0_CLOCKS5             = 0x012Bu,  /* tcpwm[0].clocks[5] */
    PCLK_TCPWM0_CLOCKS6             = 0x012Cu,  /* tcpwm[0].clocks[6] */
    PCLK_TCPWM0_CLOCKS7             = 0x012Du,  /* tcpwm[0].clocks[7] */
    PCLK_TCPWM0_CLOCKS8             = 0x012Eu,  /* tcpwm[0].clocks[8] */
    PCLK_TCPWM0_CLOCKS9             = 0x012Fu,  /* tcpwm[0].clocks[9] */
    PCLK_TCPWM0_CLOCKS10            = 0x0130u,  /* tcpwm[0].clocks[10] */
    PCLK_TCPWM0_CLOCKS11            = 0x0131u,  /* tcpwm[0].clocks[11] */
    PCLK_TCPWM0_CLOCKS12            = 0x0132u,  /* tcpwm[0].clocks[12] */
    PCLK_TCPWM0_CLOCKS13            = 0x0133u,  /* tcpwm[0].clocks[13] */
    PCLK_TCPWM0_CLOCKS14            = 0x0134u,  /* tcpwm[0].clocks[14] */
    PCLK_TCPWM0_CLOCKS15            = 0x0135u,  /* tcpwm[0].clocks[15] */
    PCLK_TCPWM0_CLOCKS16            = 0x0136u,  /* tcpwm[0].clocks[16] */
    PCLK_TCPWM0_CLOCKS17            = 0x0137u,  /* tcpwm[0].clocks[17] */
    PCLK_TCPWM0_CLOCKS18            = 0x0138u,  /* tcpwm[0].clocks[18] */
    PCLK_TCPWM0_CLOCKS19            = 0x0139u,  /* tcpwm[0].clocks[19] */
    PCLK_TCPWM0_CLOCKS20            = 0x013Au,  /* tcpwm[0].clocks[20] */
    PCLK_TCPWM0_CLOCKS21            = 0x013Bu,  /* tcpwm[0].clocks[21] */
    PCLK_TCPWM0_CLOCKS22            = 0x013Cu,  /* tcpwm[0].clocks[22] */
    PCLK_TCPWM0_CLOCKS23            = 0x013Du,  /* tcpwm[0].clocks[23] */
    PCLK_TCPWM0_CLOCKS24            = 0x013Eu,  /* tcpwm[0].clocks[24] */
    PCLK_TCPWM0_CLOCKS25            = 0x013Fu,  /* tcpwm[0].clocks[25] */
    PCLK_TCPWM0_CLOCKS26            = 0x0140u,  /* tcpwm[0].clocks[26] */
    PCLK_TCPWM0_CLOCKS27            = 0x0141u,  /* tcpwm[0].clocks[27] */
    PCLK_TCPWM0_CLOCKS28            = 0x0142u,  /* tcpwm[0].clocks[28] */
    PCLK_TCPWM0_CLOCKS29            = 0x0143u,  /* tcpwm[0].clocks[29] */
    PCLK_TCPWM0_CLOCKS30            = 0x0144u,  /* tcpwm[0].clocks[30] */
    PCLK_TCPWM0_CLOCKS31            = 0x0145u,  /* tcpwm[0].clocks[31] */
    PCLK_TCPWM0_CLOCKS32            = 0x0146u,  /* tcpwm[0].clocks[32] */
    PCLK_TCPWM0_CLOCKS33            = 0x0147u,  /* tcpwm[0].clocks[33] */
    PCLK_TCPWM0_CLOCKS34            = 0x0148u,  /* tcpwm[0].clocks[34] */
    PCLK_TCPWM0_CLOCKS35            = 0x0149u,  /* tcpwm[0].clocks[35] */
    PCLK_TCPWM0_CLOCKS36            = 0x014Au,  /* tcpwm[0].clocks[36] */
    PCLK_TCPWM0_CLOCKS37            = 0x014Bu,  /* tcpwm[0].clocks[37] */
    PCLK_TCPWM0_CLOCKS38            = 0x014Cu,  /* tcpwm[0].clocks[38] */
    PCLK_TCPWM0_CLOCKS39            = 0x014Du,  /* tcpwm[0].clocks[39] */
    PCLK_TCPWM0_CLOCKS40            = 0x014Eu,  /* tcpwm[0].clocks[40] */
    PCLK_TCPWM0_CLOCKS41            = 0x014Fu,  /* tcpwm[0].clocks[41] */
    PCLK_TCPWM0_CLOCKS42            = 0x0150u,  /* tcpwm[0].clocks[42] */
    PCLK_TCPWM0_CLOCKS43            = 0x0151u,  /* tcpwm[0].clocks[43] */
    PCLK_TCPWM0_CLOCKS44            = 0x0152u,  /* tcpwm[0].clocks[44] */
    PCLK_TCPWM0_CLOCKS45            = 0x0153u,  /* tcpwm[0].clocks[45] */
    PCLK_TCPWM0_CLOCKS46            = 0x0154u,  /* tcpwm[0].clocks[46] */
    PCLK_TCPWM0_CLOCKS47            = 0x0155u,  /* tcpwm[0].clocks[47] */
    PCLK_TCPWM0_CLOCKS48            = 0x0156u,  /* tcpwm[0].clocks[48] */
    PCLK_TCPWM0_CLOCKS49            = 0x0157u,  /* tcpwm[0].clocks[49] */
    PCLK_TCPWM0_CLOCKS50            = 0x0158u,  /* tcpwm[0].clocks[50] */
    PCLK_TCPWM0_CLOCKS51            = 0x0159u,  /* tcpwm[0].clocks[51] */
    PCLK_TCPWM0_CLOCKS52            = 0x015Au,  /* tcpwm[0].clocks[52] */
    PCLK_TCPWM0_CLOCKS53            = 0x015Bu,  /* tcpwm[0].clocks[53] */
    PCLK_TCPWM0_CLOCKS54            = 0x015Cu,  /* tcpwm[0].clocks[54] */
    PCLK_TCPWM0_CLOCKS55            = 0x015Du,  /* tcpwm[0].clocks[55] */
    PCLK_TCPWM0_CLOCKS56            = 0x015Eu,  /* tcpwm[0].clocks[56] */
    PCLK_TCPWM0_CLOCKS57            = 0x015Fu,  /* tcpwm[0].clocks[57] */
    PCLK_TCPWM0_CLOCKS58            = 0x0160u,  /* tcpwm[0].clocks[58] */
    PCLK_TCPWM0_CLOCKS59            = 0x0161u,  /* tcpwm[0].clocks[59] */
    PCLK_TCPWM0_CLOCKS60            = 0x0162u,  /* tcpwm[0].clocks[60] */
    PCLK_TCPWM0_CLOCKS61            = 0x0163u,  /* tcpwm[0].clocks[61] */
    PCLK_TCPWM0_CLOCKS62            = 0x0164u,  /* tcpwm[0].clocks[62] */
    PCLK_TCPWM0_CLOCKS256           = 0x0165u,  /* tcpwm[0].clocks[256] */
    PCLK_TCPWM0_CLOCKS257           = 0x0166u,  /* tcpwm[0].clocks[257] */
    PCLK_TCPWM0_CLOCKS258           = 0x0167u,  /* tcpwm[0].clocks[258] */
    PCLK_TCPWM0_CLOCKS259           = 0x0168u,  /* tcpwm[0].clocks[259] */
    PCLK_TCPWM0_CLOCKS260           = 0x0169u,  /* tcpwm[0].clocks[260] */
    PCLK_TCPWM0_CLOCKS261           = 0x016Au,  /* tcpwm[0].clocks[261] */
    PCLK_TCPWM0_CLOCKS262           = 0x016Bu,  /* tcpwm[0].clocks[262] */
    PCLK_TCPWM0_CLOCKS263           = 0x016Cu,  /* tcpwm[0].clocks[263] */
    PCLK_TCPWM0_CLOCKS264           = 0x016Du,  /* tcpwm[0].clocks[264] */
    PCLK_TCPWM0_CLOCKS265           = 0x016Eu,  /* tcpwm[0].clocks[265] */
    PCLK_TCPWM0_CLOCKS266           = 0x016Fu,  /* tcpwm[0].clocks[266] */
    PCLK_TCPWM0_CLOCKS267           = 0x0170u,  /* tcpwm[0].clocks[267] */
    PCLK_TCPWM0_CLOCKS512           = 0x0171u,  /* tcpwm[0].clocks[512] */
    PCLK_TCPWM0_CLOCKS513           = 0x0172u,  /* tcpwm[0].clocks[513] */
    PCLK_TCPWM0_CLOCKS514           = 0x0173u,  /* tcpwm[0].clocks[514] */
    PCLK_TCPWM0_CLOCKS515           = 0x0174u,  /* tcpwm[0].clocks[515] */
    PCLK_TCPWM0_CLOCKS516           = 0x0175u,  /* tcpwm[0].clocks[516] */
    PCLK_TCPWM0_CLOCKS517           = 0x0176u,  /* tcpwm[0].clocks[517] */
    PCLK_TCPWM0_CLOCKS518           = 0x0177u,  /* tcpwm[0].clocks[518] */
    PCLK_TCPWM0_CLOCKS519           = 0x0178u   /* tcpwm[0].clocks[519] */
} en_clk_dst_t;

/* Trigger Group */
/* This section contains the enums related to the Trigger multiplexer (TrigMux) driver.
* Refer to the Cypress Peripheral Driver Library Documentation, section Trigger multiplexer (TrigMux) -> Enumerated Types for details.
*/
/* Trigger Group Inputs */
/* Trigger Input Group 0 - P-DMA0[0:7] Request Assignments */
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
    TRIG_IN_MUX_0_PDMA0_TR_OUT8     = 0x00000009u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT9     = 0x0000000Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT10    = 0x0000000Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT11    = 0x0000000Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT12    = 0x0000000Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT13    = 0x0000000Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT14    = 0x0000000Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_0_PDMA0_TR_OUT15    = 0x00000010u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT0     = 0x00000011u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT1     = 0x00000012u, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT2     = 0x00000013u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT3     = 0x00000014u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT4     = 0x00000015u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT5     = 0x00000016u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT6     = 0x00000017u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT7     = 0x00000018u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT8     = 0x00000019u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT9     = 0x0000001Au, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT10    = 0x0000001Bu, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT11    = 0x0000001Cu, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT12    = 0x0000001Du, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT13    = 0x0000001Eu, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT14    = 0x0000001Fu, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_0_PDMA1_TR_OUT15    = 0x00000020u, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_0_MDMA_TR_OUT0      = 0x00000021u, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_0_MDMA_TR_OUT1      = 0x00000022u, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_0_MDMA_TR_OUT2      = 0x00000023u, /* cpuss.dmac_tr_out[2] */
    TRIG_IN_MUX_0_MDMA_TR_OUT3      = 0x00000024u, /* cpuss.dmac_tr_out[3] */
    TRIG_IN_MUX_0_MDMA_TR_OUT4      = 0x00000025u, /* cpuss.dmac_tr_out[4] */
    TRIG_IN_MUX_0_MDMA_TR_OUT5      = 0x00000026u, /* cpuss.dmac_tr_out[5] */
    TRIG_IN_MUX_0_MDMA_TR_OUT6      = 0x00000027u, /* cpuss.dmac_tr_out[6] */
    TRIG_IN_MUX_0_MDMA_TR_OUT7      = 0x00000028u, /* cpuss.dmac_tr_out[7] */
    TRIG_IN_MUX_0_CAN0_TT_TR_OUT0   = 0x00000029u, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_0_CAN0_TT_TR_OUT1   = 0x0000002Au, /* canfd[0].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_0_CAN0_TT_TR_OUT2   = 0x0000002Bu, /* canfd[0].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_0_CAN0_TT_TR_OUT3   = 0x0000002Cu, /* canfd[0].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_0_CAN1_TT_TR_OUT0   = 0x0000002Du, /* canfd[1].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_0_CAN1_TT_TR_OUT1   = 0x0000002Eu, /* canfd[1].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_0_CAN1_TT_TR_OUT2   = 0x0000002Fu, /* canfd[1].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_0_CAN1_TT_TR_OUT3   = 0x00000030u, /* canfd[1].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT0   = 0x00000031u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT1   = 0x00000032u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT2   = 0x00000033u, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT3   = 0x00000034u, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT4   = 0x00000035u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT5   = 0x00000036u, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT6   = 0x00000037u, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT7   = 0x00000038u, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT8   = 0x00000039u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT9   = 0x0000003Au, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT10  = 0x0000003Bu, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT11  = 0x0000003Cu, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT12  = 0x0000003Du, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT13  = 0x0000003Eu, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT14  = 0x0000003Fu, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_0_HSIOM_IO_INPUT15  = 0x00000040u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_0_FAULT_TR_OUT0     = 0x00000041u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_0_FAULT_TR_OUT1     = 0x00000042u, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_0_FAULT_TR_OUT2     = 0x00000043u, /* cpuss.tr_fault[2] */
    TRIG_IN_MUX_0_FAULT_TR_OUT3     = 0x00000044u /* cpuss.tr_fault[3] */
} en_trig_input_pdma0_tr_0_t;

/* Trigger Input Group 1 - P-DMA0[8:15] Request Assignments */
typedef enum
{
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT00 = 0x00000101u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT01 = 0x00000102u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT02 = 0x00000103u, /* tcpwm[0].tr_out0[2] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT03 = 0x00000104u, /* tcpwm[0].tr_out0[3] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT04 = 0x00000105u, /* tcpwm[0].tr_out0[4] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT05 = 0x00000106u, /* tcpwm[0].tr_out0[5] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT06 = 0x00000107u, /* tcpwm[0].tr_out0[6] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT07 = 0x00000108u, /* tcpwm[0].tr_out0[7] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT08 = 0x00000109u, /* tcpwm[0].tr_out0[8] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT09 = 0x0000010Au, /* tcpwm[0].tr_out0[9] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT010 = 0x0000010Bu, /* tcpwm[0].tr_out0[10] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT011 = 0x0000010Cu, /* tcpwm[0].tr_out0[11] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT012 = 0x0000010Du, /* tcpwm[0].tr_out0[12] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT013 = 0x0000010Eu, /* tcpwm[0].tr_out0[13] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT014 = 0x0000010Fu, /* tcpwm[0].tr_out0[14] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT015 = 0x00000110u, /* tcpwm[0].tr_out0[15] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT016 = 0x00000111u, /* tcpwm[0].tr_out0[16] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT017 = 0x00000112u, /* tcpwm[0].tr_out0[17] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT018 = 0x00000113u, /* tcpwm[0].tr_out0[18] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT019 = 0x00000114u, /* tcpwm[0].tr_out0[19] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT020 = 0x00000115u, /* tcpwm[0].tr_out0[20] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT021 = 0x00000116u, /* tcpwm[0].tr_out0[21] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT022 = 0x00000117u, /* tcpwm[0].tr_out0[22] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT023 = 0x00000118u, /* tcpwm[0].tr_out0[23] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT024 = 0x00000119u, /* tcpwm[0].tr_out0[24] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT025 = 0x0000011Au, /* tcpwm[0].tr_out0[25] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT026 = 0x0000011Bu, /* tcpwm[0].tr_out0[26] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT027 = 0x0000011Cu, /* tcpwm[0].tr_out0[27] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT028 = 0x0000011Du, /* tcpwm[0].tr_out0[28] */
    TRIG_IN_MUX_1_TCPWM_16_TR_OUT029 = 0x0000011Eu, /* tcpwm[0].tr_out0[29] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT00 = 0x0000011Fu, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT01 = 0x00000120u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT02 = 0x00000121u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT03 = 0x00000122u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT04 = 0x00000123u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT05 = 0x00000124u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT06 = 0x00000125u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT07 = 0x00000126u, /* tcpwm[0].tr_out0[263] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT08 = 0x00000127u, /* tcpwm[0].tr_out0[264] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT09 = 0x00000128u, /* tcpwm[0].tr_out0[265] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT010 = 0x00000129u, /* tcpwm[0].tr_out0[266] */
    TRIG_IN_MUX_1_TCPWM_16M_TR_OUT011 = 0x0000012Au, /* tcpwm[0].tr_out0[267] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT00 = 0x0000012Bu, /* tcpwm[0].tr_out0[512] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT01 = 0x0000012Cu, /* tcpwm[0].tr_out0[513] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT02 = 0x0000012Du, /* tcpwm[0].tr_out0[514] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT03 = 0x0000012Eu, /* tcpwm[0].tr_out0[515] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT04 = 0x0000012Fu, /* tcpwm[0].tr_out0[516] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT05 = 0x00000130u, /* tcpwm[0].tr_out0[517] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT06 = 0x00000131u, /* tcpwm[0].tr_out0[518] */
    TRIG_IN_MUX_1_TCPWM_32_TR_OUT07 = 0x00000132u, /* tcpwm[0].tr_out0[519] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT0  = 0x00000133u, /* pass[0].tr_sar_gen_out[0] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT1  = 0x00000134u, /* pass[0].tr_sar_gen_out[1] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT2  = 0x00000135u, /* pass[0].tr_sar_gen_out[2] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT3  = 0x00000136u, /* pass[0].tr_sar_gen_out[3] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT4  = 0x00000137u, /* pass[0].tr_sar_gen_out[4] */
    TRIG_IN_MUX_1_PASS_GEN_TR_OUT5  = 0x00000138u, /* pass[0].tr_sar_gen_out[5] */
    TRIG_IN_MUX_1_CTI_TR_OUT0       = 0x00000139u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_1_CTI_TR_OUT1       = 0x0000013Au, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_1_EVTGEN_TR_OUT0    = 0x0000013Bu, /* evtgen[0].tr_out[0] */
    TRIG_IN_MUX_1_EVTGEN_TR_OUT1    = 0x0000013Cu, /* evtgen[0].tr_out[1] */
    TRIG_IN_MUX_1_EVTGEN_TR_OUT2    = 0x0000013Du, /* evtgen[0].tr_out[2] */
    TRIG_IN_MUX_1_EVTGEN_TR_OUT3    = 0x0000013Eu /* evtgen[0].tr_out[3] */
} en_trig_input_pdma0_tr_1_t;

/* Trigger Input Group 2 - P-DMA1[0:15] Request Assignments */
typedef enum
{
    TRIG_IN_MUX_2_PDMA1_TR_OUT0     = 0x00000201u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT1     = 0x00000202u, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT2     = 0x00000203u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT3     = 0x00000204u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT4     = 0x00000205u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT5     = 0x00000206u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT6     = 0x00000207u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT7     = 0x00000208u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT8     = 0x00000209u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT9     = 0x0000020Au, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT10    = 0x0000020Bu, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT11    = 0x0000020Cu, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT12    = 0x0000020Du, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT13    = 0x0000020Eu, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT14    = 0x0000020Fu, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_2_PDMA1_TR_OUT15    = 0x00000210u, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT0     = 0x00000211u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT1     = 0x00000212u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT2     = 0x00000213u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT3     = 0x00000214u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT4     = 0x00000215u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT5     = 0x00000216u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT6     = 0x00000217u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT7     = 0x00000218u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT8     = 0x00000219u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT9     = 0x0000021Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT10    = 0x0000021Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT11    = 0x0000021Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT12    = 0x0000021Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT13    = 0x0000021Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT14    = 0x0000021Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_2_PDMA0_TR_OUT15    = 0x00000220u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT030 = 0x00000221u, /* tcpwm[0].tr_out0[30] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT031 = 0x00000222u, /* tcpwm[0].tr_out0[31] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT032 = 0x00000223u, /* tcpwm[0].tr_out0[32] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT033 = 0x00000224u, /* tcpwm[0].tr_out0[33] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT034 = 0x00000225u, /* tcpwm[0].tr_out0[34] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT035 = 0x00000226u, /* tcpwm[0].tr_out0[35] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT036 = 0x00000227u, /* tcpwm[0].tr_out0[36] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT037 = 0x00000228u, /* tcpwm[0].tr_out0[37] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT038 = 0x00000229u, /* tcpwm[0].tr_out0[38] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT039 = 0x0000022Au, /* tcpwm[0].tr_out0[39] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT040 = 0x0000022Bu, /* tcpwm[0].tr_out0[40] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT041 = 0x0000022Cu, /* tcpwm[0].tr_out0[41] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT042 = 0x0000022Du, /* tcpwm[0].tr_out0[42] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT043 = 0x0000022Eu, /* tcpwm[0].tr_out0[43] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT044 = 0x0000022Fu, /* tcpwm[0].tr_out0[44] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT045 = 0x00000230u, /* tcpwm[0].tr_out0[45] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT046 = 0x00000231u, /* tcpwm[0].tr_out0[46] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT047 = 0x00000232u, /* tcpwm[0].tr_out0[47] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT048 = 0x00000233u, /* tcpwm[0].tr_out0[48] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT049 = 0x00000234u, /* tcpwm[0].tr_out0[49] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT050 = 0x00000235u, /* tcpwm[0].tr_out0[50] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT051 = 0x00000236u, /* tcpwm[0].tr_out0[51] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT052 = 0x00000237u, /* tcpwm[0].tr_out0[52] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT053 = 0x00000238u, /* tcpwm[0].tr_out0[53] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT054 = 0x00000239u, /* tcpwm[0].tr_out0[54] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT055 = 0x0000023Au, /* tcpwm[0].tr_out0[55] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT056 = 0x0000023Bu, /* tcpwm[0].tr_out0[56] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT057 = 0x0000023Cu, /* tcpwm[0].tr_out0[57] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT058 = 0x0000023Du, /* tcpwm[0].tr_out0[58] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT059 = 0x0000023Eu, /* tcpwm[0].tr_out0[59] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT060 = 0x0000023Fu, /* tcpwm[0].tr_out0[60] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT061 = 0x00000240u, /* tcpwm[0].tr_out0[61] */
    TRIG_IN_MUX_2_TCPWM_16_TR_OUT062 = 0x00000241u, /* tcpwm[0].tr_out0[62] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT16  = 0x00000242u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT17  = 0x00000243u, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT18  = 0x00000244u, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT19  = 0x00000245u, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT20  = 0x00000246u, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT21  = 0x00000247u, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT22  = 0x00000248u, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT23  = 0x00000249u, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT24  = 0x0000024Au, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT25  = 0x0000024Bu, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT26  = 0x0000024Cu, /* peri.tr_io_input[26] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT27  = 0x0000024Du, /* peri.tr_io_input[27] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT28  = 0x0000024Eu, /* peri.tr_io_input[28] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT29  = 0x0000024Fu, /* peri.tr_io_input[29] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT30  = 0x00000250u, /* peri.tr_io_input[30] */
    TRIG_IN_MUX_2_HSIOM_IO_INPUT31  = 0x00000251u /* peri.tr_io_input[31] */
} en_trig_input_pdma1_tr_t;

/* Trigger Input Group 3 - M-DMA Request Assignments */
typedef enum
{
    TRIG_IN_MUX_3_TCPWM_16_TR_OUT10 = 0x00000301u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_3_TCPWM_16_TR_OUT11 = 0x00000302u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_3_TCPWM_16_TR_OUT12 = 0x00000303u, /* tcpwm[0].tr_out0[2] */
    TRIG_IN_MUX_3_TCPWM_16M_TR_OUT10 = 0x00000304u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_3_TCPWM_16M_TR_OUT11 = 0x00000305u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_3_TCPWM_16M_TR_OUT12 = 0x00000306u /* tcpwm[0].tr_out0[258] */
} en_trig_input_mdma_t;

/* Trigger Input Group 5 -  */
typedef enum
{
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT00 = 0x00000501u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT01 = 0x00000502u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT02 = 0x00000503u, /* tcpwm[0].tr_out0[2] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT03 = 0x00000504u, /* tcpwm[0].tr_out0[3] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT04 = 0x00000505u, /* tcpwm[0].tr_out0[4] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT05 = 0x00000506u, /* tcpwm[0].tr_out0[5] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT06 = 0x00000507u, /* tcpwm[0].tr_out0[6] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT07 = 0x00000508u, /* tcpwm[0].tr_out0[7] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT08 = 0x00000509u, /* tcpwm[0].tr_out0[8] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT09 = 0x0000050Au, /* tcpwm[0].tr_out0[9] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT010 = 0x0000050Bu, /* tcpwm[0].tr_out0[10] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT011 = 0x0000050Cu, /* tcpwm[0].tr_out0[11] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT012 = 0x0000050Du, /* tcpwm[0].tr_out0[12] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT013 = 0x0000050Eu, /* tcpwm[0].tr_out0[13] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT014 = 0x0000050Fu, /* tcpwm[0].tr_out0[14] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT015 = 0x00000510u, /* tcpwm[0].tr_out0[15] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT016 = 0x00000511u, /* tcpwm[0].tr_out0[16] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT017 = 0x00000512u, /* tcpwm[0].tr_out0[17] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT018 = 0x00000513u, /* tcpwm[0].tr_out0[18] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT019 = 0x00000514u, /* tcpwm[0].tr_out0[19] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT020 = 0x00000515u, /* tcpwm[0].tr_out0[20] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT021 = 0x00000516u, /* tcpwm[0].tr_out0[21] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT022 = 0x00000517u, /* tcpwm[0].tr_out0[22] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT023 = 0x00000518u, /* tcpwm[0].tr_out0[23] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT024 = 0x00000519u, /* tcpwm[0].tr_out0[24] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT025 = 0x0000051Au, /* tcpwm[0].tr_out0[25] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT026 = 0x0000051Bu, /* tcpwm[0].tr_out0[26] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT027 = 0x0000051Cu, /* tcpwm[0].tr_out0[27] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT028 = 0x0000051Du, /* tcpwm[0].tr_out0[28] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT029 = 0x0000051Eu, /* tcpwm[0].tr_out0[29] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT030 = 0x0000051Fu, /* tcpwm[0].tr_out0[30] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT031 = 0x00000520u, /* tcpwm[0].tr_out0[31] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT032 = 0x00000521u, /* tcpwm[0].tr_out0[32] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT033 = 0x00000522u, /* tcpwm[0].tr_out0[33] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT034 = 0x00000523u, /* tcpwm[0].tr_out0[34] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT035 = 0x00000524u, /* tcpwm[0].tr_out0[35] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT036 = 0x00000525u, /* tcpwm[0].tr_out0[36] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT037 = 0x00000526u, /* tcpwm[0].tr_out0[37] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT038 = 0x00000527u, /* tcpwm[0].tr_out0[38] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT039 = 0x00000528u, /* tcpwm[0].tr_out0[39] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT040 = 0x00000529u, /* tcpwm[0].tr_out0[40] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT041 = 0x0000052Au, /* tcpwm[0].tr_out0[41] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT042 = 0x0000052Bu, /* tcpwm[0].tr_out0[42] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT043 = 0x0000052Cu, /* tcpwm[0].tr_out0[43] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT044 = 0x0000052Du, /* tcpwm[0].tr_out0[44] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT045 = 0x0000052Eu, /* tcpwm[0].tr_out0[45] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT046 = 0x0000052Fu, /* tcpwm[0].tr_out0[46] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT047 = 0x00000530u, /* tcpwm[0].tr_out0[47] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT048 = 0x00000531u, /* tcpwm[0].tr_out0[48] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT049 = 0x00000532u, /* tcpwm[0].tr_out0[49] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT050 = 0x00000533u, /* tcpwm[0].tr_out0[50] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT051 = 0x00000534u, /* tcpwm[0].tr_out0[51] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT052 = 0x00000535u, /* tcpwm[0].tr_out0[52] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT053 = 0x00000536u, /* tcpwm[0].tr_out0[53] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT054 = 0x00000537u, /* tcpwm[0].tr_out0[54] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT055 = 0x00000538u, /* tcpwm[0].tr_out0[55] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT056 = 0x00000539u, /* tcpwm[0].tr_out0[56] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT057 = 0x0000053Au, /* tcpwm[0].tr_out0[57] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT058 = 0x0000053Bu, /* tcpwm[0].tr_out0[58] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT059 = 0x0000053Cu, /* tcpwm[0].tr_out0[59] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT060 = 0x0000053Du, /* tcpwm[0].tr_out0[60] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT061 = 0x0000053Eu, /* tcpwm[0].tr_out0[61] */
    TRIG_IN_MUX_5_TCPWM_16_TR_OUT062 = 0x0000053Fu, /* tcpwm[0].tr_out0[62] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT00 = 0x00000540u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT01 = 0x00000541u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT02 = 0x00000542u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT03 = 0x00000543u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT04 = 0x00000544u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT05 = 0x00000545u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT06 = 0x00000546u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT07 = 0x00000547u, /* tcpwm[0].tr_out0[263] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT08 = 0x00000548u, /* tcpwm[0].tr_out0[264] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT09 = 0x00000549u, /* tcpwm[0].tr_out0[265] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT010 = 0x0000054Au, /* tcpwm[0].tr_out0[266] */
    TRIG_IN_MUX_5_TCPWM_16M_TR_OUT011 = 0x0000054Bu, /* tcpwm[0].tr_out0[267] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT00 = 0x0000054Cu, /* tcpwm[0].tr_out0[512] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT01 = 0x0000054Du, /* tcpwm[0].tr_out0[513] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT02 = 0x0000054Eu, /* tcpwm[0].tr_out0[514] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT03 = 0x0000054Fu, /* tcpwm[0].tr_out0[515] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT04 = 0x00000550u, /* tcpwm[0].tr_out0[516] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT05 = 0x00000551u, /* tcpwm[0].tr_out0[517] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT06 = 0x00000552u, /* tcpwm[0].tr_out0[518] */
    TRIG_IN_MUX_5_TCPWM_32_TR_OUT07 = 0x00000553u, /* tcpwm[0].tr_out0[519] */
    TRIG_IN_MUX_5_CAN0_DBG_TR_OUT0  = 0x00000554u, /* canfd[0].tr_dbg_dma_req[0] */
    TRIG_IN_MUX_5_CAN0_DBG_TR_OUT1  = 0x00000555u, /* canfd[0].tr_dbg_dma_req[1] */
    TRIG_IN_MUX_5_CAN0_DBG_TR_OUT2  = 0x00000556u, /* canfd[0].tr_dbg_dma_req[2] */
    TRIG_IN_MUX_5_CAN0_DBG_TR_OUT3  = 0x00000557u, /* canfd[0].tr_dbg_dma_req[3] */
    TRIG_IN_MUX_5_CAN0_FIFO0_TR_OUT0 = 0x00000558u, /* canfd[0].tr_fifo0[0] */
    TRIG_IN_MUX_5_CAN0_FIFO0_TR_OUT1 = 0x00000559u, /* canfd[0].tr_fifo0[1] */
    TRIG_IN_MUX_5_CAN0_FIFO0_TR_OUT2 = 0x0000055Au, /* canfd[0].tr_fifo0[2] */
    TRIG_IN_MUX_5_CAN0_FIFO0_TR_OUT3 = 0x0000055Bu, /* canfd[0].tr_fifo0[3] */
    TRIG_IN_MUX_5_CAN0_FIFO1_TR_OUT0 = 0x0000055Cu, /* canfd[0].tr_fifo1[0] */
    TRIG_IN_MUX_5_CAN0_FIFO1_TR_OUT1 = 0x0000055Du, /* canfd[0].tr_fifo1[1] */
    TRIG_IN_MUX_5_CAN0_FIFO1_TR_OUT2 = 0x0000055Eu, /* canfd[0].tr_fifo1[2] */
    TRIG_IN_MUX_5_CAN0_FIFO1_TR_OUT3 = 0x0000055Fu, /* canfd[0].tr_fifo1[3] */
    TRIG_IN_MUX_5_CAN1_DBG_TR_OUT0  = 0x00000560u, /* canfd[1].tr_dbg_dma_req[0] */
    TRIG_IN_MUX_5_CAN1_DBG_TR_OUT1  = 0x00000561u, /* canfd[1].tr_dbg_dma_req[1] */
    TRIG_IN_MUX_5_CAN1_DBG_TR_OUT2  = 0x00000562u, /* canfd[1].tr_dbg_dma_req[2] */
    TRIG_IN_MUX_5_CAN1_DBG_TR_OUT3  = 0x00000563u, /* canfd[1].tr_dbg_dma_req[3] */
    TRIG_IN_MUX_5_CAN1_FIFO0_TR_OUT0 = 0x00000564u, /* canfd[1].tr_fifo0[0] */
    TRIG_IN_MUX_5_CAN1_FIFO0_TR_OUT1 = 0x00000565u, /* canfd[1].tr_fifo0[1] */
    TRIG_IN_MUX_5_CAN1_FIFO0_TR_OUT2 = 0x00000566u, /* canfd[1].tr_fifo0[2] */
    TRIG_IN_MUX_5_CAN1_FIFO0_TR_OUT3 = 0x00000567u, /* canfd[1].tr_fifo0[3] */
    TRIG_IN_MUX_5_CAN1_FIFO1_TR_OUT0 = 0x00000568u, /* canfd[1].tr_fifo1[0] */
    TRIG_IN_MUX_5_CAN1_FIFO1_TR_OUT1 = 0x00000569u, /* canfd[1].tr_fifo1[1] */
    TRIG_IN_MUX_5_CAN1_FIFO1_TR_OUT2 = 0x0000056Au, /* canfd[1].tr_fifo1[2] */
    TRIG_IN_MUX_5_CAN1_FIFO1_TR_OUT3 = 0x0000056Bu, /* canfd[1].tr_fifo1[3] */
    TRIG_IN_MUX_5_CAN0_TT_TR_OUT0   = 0x0000056Cu, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_5_CAN0_TT_TR_OUT1   = 0x0000056Du, /* canfd[0].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_5_CAN0_TT_TR_OUT2   = 0x0000056Eu, /* canfd[0].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_5_CAN0_TT_TR_OUT3   = 0x0000056Fu, /* canfd[0].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_5_CAN1_TT_TR_OUT0   = 0x00000570u, /* canfd[1].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_5_CAN1_TT_TR_OUT1   = 0x00000571u, /* canfd[1].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_5_CAN1_TT_TR_OUT2   = 0x00000572u, /* canfd[1].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_5_CAN1_TT_TR_OUT3   = 0x00000573u, /* canfd[1].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT4    = 0x00000574u, /* evtgen[0].tr_out[4] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT5    = 0x00000575u, /* evtgen[0].tr_out[5] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT6    = 0x00000576u, /* evtgen[0].tr_out[6] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT7    = 0x00000577u, /* evtgen[0].tr_out[7] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT8    = 0x00000578u, /* evtgen[0].tr_out[8] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT9    = 0x00000579u, /* evtgen[0].tr_out[9] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT10   = 0x0000057Au, /* evtgen[0].tr_out[10] */
    TRIG_IN_MUX_5_EVTGEN_TR_OUT11   = 0x0000057Bu, /* evtgen[0].tr_out[11] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT0     = 0x0000057Cu, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT1     = 0x0000057Du, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT2     = 0x0000057Eu, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT3     = 0x0000057Fu, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT4     = 0x00000580u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT5     = 0x00000581u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT6     = 0x00000582u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT7     = 0x00000583u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT8     = 0x00000584u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT9     = 0x00000585u, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT10    = 0x00000586u, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT11    = 0x00000587u, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT12    = 0x00000588u, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT13    = 0x00000589u, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT14    = 0x0000058Au, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_5_PDMA0_TR_OUT15    = 0x0000058Bu, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT0     = 0x0000058Cu, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT1     = 0x0000058Du, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT2     = 0x0000058Eu, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT3     = 0x0000058Fu, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT4     = 0x00000590u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT5     = 0x00000591u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT6     = 0x00000592u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT7     = 0x00000593u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT8     = 0x00000594u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT9     = 0x00000595u, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT10    = 0x00000596u, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT11    = 0x00000597u, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT12    = 0x00000598u, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT13    = 0x00000599u, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT14    = 0x0000059Au, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_5_PDMA1_TR_OUT15    = 0x0000059Bu, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_5_MDMA_TR_OUT0      = 0x0000059Cu, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_5_MDMA_TR_OUT1      = 0x0000059Du, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_5_MDMA_TR_OUT2      = 0x0000059Eu, /* cpuss.dmac_tr_out[2] */
    TRIG_IN_MUX_5_MDMA_TR_OUT3      = 0x0000059Fu, /* cpuss.dmac_tr_out[3] */
    TRIG_IN_MUX_5_MDMA_TR_OUT4      = 0x000005A0u, /* cpuss.dmac_tr_out[4] */
    TRIG_IN_MUX_5_MDMA_TR_OUT5      = 0x000005A1u, /* cpuss.dmac_tr_out[5] */
    TRIG_IN_MUX_5_MDMA_TR_OUT6      = 0x000005A2u, /* cpuss.dmac_tr_out[6] */
    TRIG_IN_MUX_5_MDMA_TR_OUT7      = 0x000005A3u, /* cpuss.dmac_tr_out[7] */
    TRIG_IN_MUX_5_SMIF_TX_TR_OUT    = 0x000005A4u, /* smif[0].tr_tx_req */
    TRIG_IN_MUX_5_SMIF_RX_TR_OUT    = 0x000005A5u, /* smif[0].tr_rx_req */
    TRIG_IN_MUX_5_I2S0_TX_TR_OUT    = 0x000005A6u, /* audioss[0].tr_i2s_tx_req */
    TRIG_IN_MUX_5_I2S0_RX_TR_OUT    = 0x000005A7u, /* audioss[0].tr_i2s_rx_req */
    TRIG_IN_MUX_5_I2S1_TX_TR_OUT    = 0x000005A8u, /* audioss[1].tr_i2s_tx_req */
    TRIG_IN_MUX_5_I2S1_RX_TR_OUT    = 0x000005A9u, /* audioss[1].tr_i2s_rx_req */
    TRIG_IN_MUX_5_I2S2_TX_TR_OUT    = 0x000005AAu, /* audioss[2].tr_i2s_tx_req */
    TRIG_IN_MUX_5_I2S2_RX_TR_OUT    = 0x000005ABu /* audioss[2].tr_i2s_rx_req */
} en_trig_input_tcpwm_out_t;

/* Trigger Input Group 6 - TCPWM trigger inputs */
typedef enum
{
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT10 = 0x00000601u, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT11 = 0x00000602u, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT12 = 0x00000603u, /* tcpwm[0].tr_out1[2] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT13 = 0x00000604u, /* tcpwm[0].tr_out1[3] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT14 = 0x00000605u, /* tcpwm[0].tr_out1[4] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT15 = 0x00000606u, /* tcpwm[0].tr_out1[5] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT16 = 0x00000607u, /* tcpwm[0].tr_out1[6] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT17 = 0x00000608u, /* tcpwm[0].tr_out1[7] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT18 = 0x00000609u, /* tcpwm[0].tr_out1[8] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT19 = 0x0000060Au, /* tcpwm[0].tr_out1[9] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT110 = 0x0000060Bu, /* tcpwm[0].tr_out1[10] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT111 = 0x0000060Cu, /* tcpwm[0].tr_out1[11] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT112 = 0x0000060Du, /* tcpwm[0].tr_out1[12] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT113 = 0x0000060Eu, /* tcpwm[0].tr_out1[13] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT114 = 0x0000060Fu, /* tcpwm[0].tr_out1[14] */
    TRIG_IN_MUX_6_TCPWM_16_TR_OUT115 = 0x00000610u, /* tcpwm[0].tr_out1[15] */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT0    = 0x00000611u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT0    = 0x00000612u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT0 = 0x00000613u, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT1    = 0x00000614u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT1    = 0x00000615u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT1 = 0x00000616u, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT2    = 0x00000617u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT2    = 0x00000618u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT2 = 0x00000619u, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT3    = 0x0000061Au, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT3    = 0x0000061Bu, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT3 = 0x0000061Cu, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT4    = 0x0000061Du, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT4    = 0x0000061Eu, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT4 = 0x0000061Fu, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT5    = 0x00000620u, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT5    = 0x00000621u, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT5 = 0x00000622u, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT6    = 0x00000623u, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT6    = 0x00000624u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT6 = 0x00000625u, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT7    = 0x00000626u, /* scb[7].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT7    = 0x00000627u, /* scb[7].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT7 = 0x00000628u, /* scb[7].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT8    = 0x00000629u, /* scb[8].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT8    = 0x0000062Au, /* scb[8].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT8 = 0x0000062Bu, /* scb[8].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT9    = 0x0000062Cu, /* scb[9].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT9    = 0x0000062Du, /* scb[9].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT9 = 0x0000062Eu, /* scb[9].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_SCB_TX_TR_OUT10   = 0x0000062Fu, /* scb[10].tr_tx_req */
    TRIG_IN_MUX_6_SCB_RX_TR_OUT10   = 0x00000630u, /* scb[10].tr_rx_req */
    TRIG_IN_MUX_6_SCB_I2C_SCL_TR_OUT10 = 0x00000631u, /* scb[10].tr_i2c_scl_filtered */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT0  = 0x00000632u, /* pass[0].tr_sar_gen_out[0] */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT1  = 0x00000633u, /* pass[0].tr_sar_gen_out[1] */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT2  = 0x00000634u, /* pass[0].tr_sar_gen_out[2] */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT3  = 0x00000635u, /* pass[0].tr_sar_gen_out[3] */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT4  = 0x00000636u, /* pass[0].tr_sar_gen_out[4] */
    TRIG_IN_MUX_6_PASS_GEN_TR_OUT5  = 0x00000637u, /* pass[0].tr_sar_gen_out[5] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT0   = 0x00000638u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT1   = 0x00000639u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT2   = 0x0000063Au, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT3   = 0x0000063Bu, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT4   = 0x0000063Cu, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT5   = 0x0000063Du, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT6   = 0x0000063Eu, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT7   = 0x0000063Fu, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT8   = 0x00000640u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT9   = 0x00000641u, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT10  = 0x00000642u, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT11  = 0x00000643u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT12  = 0x00000644u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT13  = 0x00000645u, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT14  = 0x00000646u, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT15  = 0x00000647u, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT16  = 0x00000648u, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT17  = 0x00000649u, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT18  = 0x0000064Au, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT19  = 0x0000064Bu, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT20  = 0x0000064Cu, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT21  = 0x0000064Du, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT22  = 0x0000064Eu, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT23  = 0x0000064Fu, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT24  = 0x00000650u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT25  = 0x00000651u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT26  = 0x00000652u, /* peri.tr_io_input[26] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT27  = 0x00000653u, /* peri.tr_io_input[27] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT28  = 0x00000654u, /* peri.tr_io_input[28] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT29  = 0x00000655u, /* peri.tr_io_input[29] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT30  = 0x00000656u, /* peri.tr_io_input[30] */
    TRIG_IN_MUX_6_HSIOM_IO_INPUT31  = 0x00000657u, /* peri.tr_io_input[31] */
    TRIG_IN_MUX_6_CTI_TR_IN0        = 0x00000658u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_6_CTI_TR_IN1        = 0x00000659u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_6_FAULT_TR_OUT0     = 0x0000065Au, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_6_FAULT_TR_OUT1     = 0x0000065Bu, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_6_FAULT_TR_OUT2     = 0x0000065Cu, /* cpuss.tr_fault[2] */
    TRIG_IN_MUX_6_FAULT_TR_OUT3     = 0x0000065Du /* cpuss.tr_fault[3] */
} en_trig_input_tcpwm_in_t;

/* Trigger Input Group 7 - PASS trigger multiplexer */
typedef enum
{
    TRIG_IN_MUX_7_PDMA0_TR_OUT0     = 0x00000701u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT1     = 0x00000702u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT2     = 0x00000703u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT3     = 0x00000704u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT4     = 0x00000705u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT5     = 0x00000706u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT6     = 0x00000707u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT7     = 0x00000708u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT8     = 0x00000709u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT9     = 0x0000070Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT10    = 0x0000070Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT11    = 0x0000070Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT12    = 0x0000070Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT13    = 0x0000070Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT14    = 0x0000070Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_7_PDMA0_TR_OUT15    = 0x00000710u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT00 = 0x00000711u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT01 = 0x00000712u, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT02 = 0x00000713u, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT03 = 0x00000714u, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT04 = 0x00000715u, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT05 = 0x00000716u, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT06 = 0x00000717u, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT07 = 0x00000718u, /* tcpwm[0].tr_out0[263] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT08 = 0x00000719u, /* tcpwm[0].tr_out0[264] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT09 = 0x0000071Au, /* tcpwm[0].tr_out0[265] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT010 = 0x0000071Bu, /* tcpwm[0].tr_out0[266] */
    TRIG_IN_MUX_7_TCPWM_16M_TR_OUT011 = 0x0000071Cu, /* tcpwm[0].tr_out0[267] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT00 = 0x0000071Du, /* tcpwm[0].tr_out0[512] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT01 = 0x0000071Eu, /* tcpwm[0].tr_out0[513] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT02 = 0x0000071Fu, /* tcpwm[0].tr_out0[514] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT03 = 0x00000720u, /* tcpwm[0].tr_out0[515] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT04 = 0x00000721u, /* tcpwm[0].tr_out0[516] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT05 = 0x00000722u, /* tcpwm[0].tr_out0[517] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT06 = 0x00000723u, /* tcpwm[0].tr_out0[518] */
    TRIG_IN_MUX_7_TCPWM_32_TR_OUT07 = 0x00000724u, /* tcpwm[0].tr_out0[519] */
    TRIG_IN_MUX_7_TCPWM_16_TR_OUT160 = 0x00000725u, /* tcpwm[0].tr_out1[60] */
    TRIG_IN_MUX_7_TCPWM_16_TR_OUT161 = 0x00000726u, /* tcpwm[0].tr_out1[61] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT0   = 0x00000727u, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT1   = 0x00000728u, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT2   = 0x00000729u, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT3   = 0x0000072Au, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT4   = 0x0000072Bu, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT5   = 0x0000072Cu, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT6   = 0x0000072Du, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_7_HSIOM_IO_INPUT7   = 0x0000072Eu, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_7_EVTGEN_TR_OUT12   = 0x0000072Fu, /* evtgen[0].tr_out[12] */
    TRIG_IN_MUX_7_EVTGEN_TR_OUT13   = 0x00000730u, /* evtgen[0].tr_out[13] */
    TRIG_IN_MUX_7_EVTGEN_TR_OUT14   = 0x00000731u /* evtgen[0].tr_out[14] */
} en_trig_input_pass_t;

/* Trigger Input Group 8 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_IN_MUX_8_CAN0_TT_TR_OUT0   = 0x00000801u, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_8_CAN0_TT_TR_OUT1   = 0x00000802u, /* canfd[0].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_8_CAN0_TT_TR_OUT2   = 0x00000803u, /* canfd[0].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_8_CAN0_TT_TR_OUT3   = 0x00000804u, /* canfd[0].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_8_CAN1_TT_TR_OUT0   = 0x00000805u, /* canfd[1].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_8_CAN1_TT_TR_OUT1   = 0x00000806u, /* canfd[1].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_8_CAN1_TT_TR_OUT2   = 0x00000807u, /* canfd[1].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_8_CAN1_TT_TR_OUT3   = 0x00000808u /* canfd[1].tr_tmp_rtp_out[3] */
} en_trig_input_cantt_t;

/* Trigger Input Group 9 - 2nd level MUX using input from MUX_9/10/11 */
typedef enum
{
    TRIG_IN_MUX_9_TR_GROUP10_OUTPUT0 = 0x00000901u, /* tr_group[10].output[0] */
    TRIG_IN_MUX_9_TR_GROUP10_OUTPUT1 = 0x00000902u, /* tr_group[10].output[1] */
    TRIG_IN_MUX_9_TR_GROUP10_OUTPUT2 = 0x00000903u, /* tr_group[10].output[2] */
    TRIG_IN_MUX_9_TR_GROUP10_OUTPUT3 = 0x00000904u, /* tr_group[10].output[3] */
    TRIG_IN_MUX_9_TR_GROUP10_OUTPUT4 = 0x00000905u, /* tr_group[10].output[4] */
    TRIG_IN_MUX_9_TR_GROUP11_OUTPUT0 = 0x00000906u, /* tr_group[11].output[0] */
    TRIG_IN_MUX_9_TR_GROUP11_OUTPUT1 = 0x00000907u, /* tr_group[11].output[1] */
    TRIG_IN_MUX_9_TR_GROUP11_OUTPUT2 = 0x00000908u, /* tr_group[11].output[2] */
    TRIG_IN_MUX_9_TR_GROUP11_OUTPUT3 = 0x00000909u, /* tr_group[11].output[3] */
    TRIG_IN_MUX_9_TR_GROUP11_OUTPUT4 = 0x0000090Au, /* tr_group[11].output[4] */
    TRIG_IN_MUX_9_TR_GROUP12_OUTPUT0 = 0x0000090Bu, /* tr_group[12].output[0] */
    TRIG_IN_MUX_9_TR_GROUP12_OUTPUT1 = 0x0000090Cu, /* tr_group[12].output[1] */
    TRIG_IN_MUX_9_TR_GROUP12_OUTPUT2 = 0x0000090Du, /* tr_group[12].output[2] */
    TRIG_IN_MUX_9_TR_GROUP12_OUTPUT3 = 0x0000090Eu, /* tr_group[12].output[3] */
    TRIG_IN_MUX_9_TR_GROUP12_OUTPUT4 = 0x0000090Fu /* tr_group[12].output[4] */
} en_trig_input_debugmain_t;

/* Trigger Input Group 10 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_IN_MUX_10_PDMA0_TR_OUT0    = 0x00000A01u, /* cpuss.dw0_tr_out[0] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT1    = 0x00000A02u, /* cpuss.dw0_tr_out[1] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT2    = 0x00000A03u, /* cpuss.dw0_tr_out[2] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT3    = 0x00000A04u, /* cpuss.dw0_tr_out[3] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT4    = 0x00000A05u, /* cpuss.dw0_tr_out[4] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT5    = 0x00000A06u, /* cpuss.dw0_tr_out[5] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT6    = 0x00000A07u, /* cpuss.dw0_tr_out[6] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT7    = 0x00000A08u, /* cpuss.dw0_tr_out[7] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT8    = 0x00000A09u, /* cpuss.dw0_tr_out[8] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT9    = 0x00000A0Au, /* cpuss.dw0_tr_out[9] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT10   = 0x00000A0Bu, /* cpuss.dw0_tr_out[10] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT11   = 0x00000A0Cu, /* cpuss.dw0_tr_out[11] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT12   = 0x00000A0Du, /* cpuss.dw0_tr_out[12] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT13   = 0x00000A0Eu, /* cpuss.dw0_tr_out[13] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT14   = 0x00000A0Fu, /* cpuss.dw0_tr_out[14] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT15   = 0x00000A10u, /* cpuss.dw0_tr_out[15] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT16   = 0x00000A11u, /* cpuss.dw0_tr_out[16] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT17   = 0x00000A12u, /* cpuss.dw0_tr_out[17] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT18   = 0x00000A13u, /* cpuss.dw0_tr_out[18] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT19   = 0x00000A14u, /* cpuss.dw0_tr_out[19] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT20   = 0x00000A15u, /* cpuss.dw0_tr_out[20] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT21   = 0x00000A16u, /* cpuss.dw0_tr_out[21] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT22   = 0x00000A17u, /* cpuss.dw0_tr_out[22] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT23   = 0x00000A18u, /* cpuss.dw0_tr_out[23] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT24   = 0x00000A19u, /* cpuss.dw0_tr_out[24] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT25   = 0x00000A1Au, /* cpuss.dw0_tr_out[25] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT26   = 0x00000A1Bu, /* cpuss.dw0_tr_out[26] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT27   = 0x00000A1Cu, /* cpuss.dw0_tr_out[27] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT28   = 0x00000A1Du, /* cpuss.dw0_tr_out[28] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT29   = 0x00000A1Eu, /* cpuss.dw0_tr_out[29] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT30   = 0x00000A1Fu, /* cpuss.dw0_tr_out[30] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT31   = 0x00000A20u, /* cpuss.dw0_tr_out[31] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT32   = 0x00000A21u, /* cpuss.dw0_tr_out[32] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT33   = 0x00000A22u, /* cpuss.dw0_tr_out[33] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT34   = 0x00000A23u, /* cpuss.dw0_tr_out[34] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT35   = 0x00000A24u, /* cpuss.dw0_tr_out[35] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT36   = 0x00000A25u, /* cpuss.dw0_tr_out[36] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT37   = 0x00000A26u, /* cpuss.dw0_tr_out[37] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT38   = 0x00000A27u, /* cpuss.dw0_tr_out[38] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT39   = 0x00000A28u, /* cpuss.dw0_tr_out[39] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT40   = 0x00000A29u, /* cpuss.dw0_tr_out[40] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT41   = 0x00000A2Au, /* cpuss.dw0_tr_out[41] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT42   = 0x00000A2Bu, /* cpuss.dw0_tr_out[42] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT43   = 0x00000A2Cu, /* cpuss.dw0_tr_out[43] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT44   = 0x00000A2Du, /* cpuss.dw0_tr_out[44] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT45   = 0x00000A2Eu, /* cpuss.dw0_tr_out[45] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT46   = 0x00000A2Fu, /* cpuss.dw0_tr_out[46] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT47   = 0x00000A30u, /* cpuss.dw0_tr_out[47] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT48   = 0x00000A31u, /* cpuss.dw0_tr_out[48] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT49   = 0x00000A32u, /* cpuss.dw0_tr_out[49] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT50   = 0x00000A33u, /* cpuss.dw0_tr_out[50] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT51   = 0x00000A34u, /* cpuss.dw0_tr_out[51] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT52   = 0x00000A35u, /* cpuss.dw0_tr_out[52] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT53   = 0x00000A36u, /* cpuss.dw0_tr_out[53] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT54   = 0x00000A37u, /* cpuss.dw0_tr_out[54] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT55   = 0x00000A38u, /* cpuss.dw0_tr_out[55] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT56   = 0x00000A39u, /* cpuss.dw0_tr_out[56] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT57   = 0x00000A3Au, /* cpuss.dw0_tr_out[57] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT58   = 0x00000A3Bu, /* cpuss.dw0_tr_out[58] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT59   = 0x00000A3Cu, /* cpuss.dw0_tr_out[59] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT60   = 0x00000A3Du, /* cpuss.dw0_tr_out[60] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT61   = 0x00000A3Eu, /* cpuss.dw0_tr_out[61] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT62   = 0x00000A3Fu, /* cpuss.dw0_tr_out[62] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT63   = 0x00000A40u, /* cpuss.dw0_tr_out[63] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT64   = 0x00000A41u, /* cpuss.dw0_tr_out[64] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT65   = 0x00000A42u, /* cpuss.dw0_tr_out[65] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT66   = 0x00000A43u, /* cpuss.dw0_tr_out[66] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT67   = 0x00000A44u, /* cpuss.dw0_tr_out[67] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT68   = 0x00000A45u, /* cpuss.dw0_tr_out[68] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT69   = 0x00000A46u, /* cpuss.dw0_tr_out[69] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT70   = 0x00000A47u, /* cpuss.dw0_tr_out[70] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT71   = 0x00000A48u, /* cpuss.dw0_tr_out[71] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT72   = 0x00000A49u, /* cpuss.dw0_tr_out[72] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT73   = 0x00000A4Au, /* cpuss.dw0_tr_out[73] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT74   = 0x00000A4Bu, /* cpuss.dw0_tr_out[74] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT75   = 0x00000A4Cu, /* cpuss.dw0_tr_out[75] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT76   = 0x00000A4Du, /* cpuss.dw0_tr_out[76] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT77   = 0x00000A4Eu, /* cpuss.dw0_tr_out[77] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT78   = 0x00000A4Fu, /* cpuss.dw0_tr_out[78] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT79   = 0x00000A50u, /* cpuss.dw0_tr_out[79] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT80   = 0x00000A51u, /* cpuss.dw0_tr_out[80] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT81   = 0x00000A52u, /* cpuss.dw0_tr_out[81] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT82   = 0x00000A53u, /* cpuss.dw0_tr_out[82] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT83   = 0x00000A54u, /* cpuss.dw0_tr_out[83] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT84   = 0x00000A55u, /* cpuss.dw0_tr_out[84] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT85   = 0x00000A56u, /* cpuss.dw0_tr_out[85] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT86   = 0x00000A57u, /* cpuss.dw0_tr_out[86] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT87   = 0x00000A58u, /* cpuss.dw0_tr_out[87] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT88   = 0x00000A59u, /* cpuss.dw0_tr_out[88] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT89   = 0x00000A5Au, /* cpuss.dw0_tr_out[89] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT90   = 0x00000A5Bu, /* cpuss.dw0_tr_out[90] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT91   = 0x00000A5Cu, /* cpuss.dw0_tr_out[91] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT92   = 0x00000A5Du, /* cpuss.dw0_tr_out[92] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT93   = 0x00000A5Eu, /* cpuss.dw0_tr_out[93] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT94   = 0x00000A5Fu, /* cpuss.dw0_tr_out[94] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT95   = 0x00000A60u, /* cpuss.dw0_tr_out[95] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT96   = 0x00000A61u, /* cpuss.dw0_tr_out[96] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT97   = 0x00000A62u, /* cpuss.dw0_tr_out[97] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT98   = 0x00000A63u, /* cpuss.dw0_tr_out[98] */
    TRIG_IN_MUX_10_PDMA0_TR_OUT99   = 0x00000A64u, /* cpuss.dw0_tr_out[99] */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT0   = 0x00000A65u, /* scb[0].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT1   = 0x00000A66u, /* scb[1].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT2   = 0x00000A67u, /* scb[2].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT3   = 0x00000A68u, /* scb[3].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT4   = 0x00000A69u, /* scb[4].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT5   = 0x00000A6Au, /* scb[5].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT6   = 0x00000A6Bu, /* scb[6].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT7   = 0x00000A6Cu, /* scb[7].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT8   = 0x00000A6Du, /* scb[8].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT9   = 0x00000A6Eu, /* scb[9].tr_tx_req */
    TRIG_IN_MUX_10_SCB_TX_TR_OUT10  = 0x00000A6Fu, /* scb[10].tr_tx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT0   = 0x00000A70u, /* scb[0].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT1   = 0x00000A71u, /* scb[1].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT2   = 0x00000A72u, /* scb[2].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT3   = 0x00000A73u, /* scb[3].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT4   = 0x00000A74u, /* scb[4].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT5   = 0x00000A75u, /* scb[5].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT6   = 0x00000A76u, /* scb[6].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT7   = 0x00000A77u, /* scb[7].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT8   = 0x00000A78u, /* scb[8].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT9   = 0x00000A79u, /* scb[9].tr_rx_req */
    TRIG_IN_MUX_10_SCB_RX_TR_OUT10  = 0x00000A7Au, /* scb[10].tr_rx_req */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT0 = 0x00000A7Bu, /* scb[0].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT1 = 0x00000A7Cu, /* scb[1].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT2 = 0x00000A7Du, /* scb[2].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT3 = 0x00000A7Eu, /* scb[3].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT4 = 0x00000A7Fu, /* scb[4].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT5 = 0x00000A80u, /* scb[5].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT6 = 0x00000A81u, /* scb[6].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT7 = 0x00000A82u, /* scb[7].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT8 = 0x00000A83u, /* scb[8].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT9 = 0x00000A84u, /* scb[9].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_SCB_I2C_SCL_TR_OUT10 = 0x00000A85u, /* scb[10].tr_i2c_scl_filtered */
    TRIG_IN_MUX_10_CAN0_DBG_TR_OUT0 = 0x00000A86u, /* canfd[0].tr_dbg_dma_req[0] */
    TRIG_IN_MUX_10_CAN0_DBG_TR_OUT1 = 0x00000A87u, /* canfd[0].tr_dbg_dma_req[1] */
    TRIG_IN_MUX_10_CAN0_DBG_TR_OUT2 = 0x00000A88u, /* canfd[0].tr_dbg_dma_req[2] */
    TRIG_IN_MUX_10_CAN0_DBG_TR_OUT3 = 0x00000A89u, /* canfd[0].tr_dbg_dma_req[3] */
    TRIG_IN_MUX_10_CAN0_FIFO0_TR_OUT0 = 0x00000A8Au, /* canfd[0].tr_fifo0[0] */
    TRIG_IN_MUX_10_CAN0_FIFO0_TR_OUT1 = 0x00000A8Bu, /* canfd[0].tr_fifo0[1] */
    TRIG_IN_MUX_10_CAN0_FIFO0_TR_OUT2 = 0x00000A8Cu, /* canfd[0].tr_fifo0[2] */
    TRIG_IN_MUX_10_CAN0_FIFO0_TR_OUT3 = 0x00000A8Du, /* canfd[0].tr_fifo0[3] */
    TRIG_IN_MUX_10_CAN0_FIFO1_TR_OUT0 = 0x00000A8Eu, /* canfd[0].tr_fifo1[0] */
    TRIG_IN_MUX_10_CAN0_FIFO1_TR_OUT1 = 0x00000A8Fu, /* canfd[0].tr_fifo1[1] */
    TRIG_IN_MUX_10_CAN0_FIFO1_TR_OUT2 = 0x00000A90u, /* canfd[0].tr_fifo1[2] */
    TRIG_IN_MUX_10_CAN0_FIFO1_TR_OUT3 = 0x00000A91u, /* canfd[0].tr_fifo1[3] */
    TRIG_IN_MUX_10_CAN0_TT_TR_OUT0  = 0x00000A92u, /* canfd[0].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_10_CAN0_TT_TR_OUT1  = 0x00000A93u, /* canfd[0].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_10_CAN0_TT_TR_OUT2  = 0x00000A94u, /* canfd[0].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_10_CAN0_TT_TR_OUT3  = 0x00000A95u, /* canfd[0].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_10_CAN1_DBG_TR_OUT0 = 0x00000A96u, /* canfd[1].tr_dbg_dma_req[0] */
    TRIG_IN_MUX_10_CAN1_DBG_TR_OUT1 = 0x00000A97u, /* canfd[1].tr_dbg_dma_req[1] */
    TRIG_IN_MUX_10_CAN1_DBG_TR_OUT2 = 0x00000A98u, /* canfd[1].tr_dbg_dma_req[2] */
    TRIG_IN_MUX_10_CAN1_DBG_TR_OUT3 = 0x00000A99u, /* canfd[1].tr_dbg_dma_req[3] */
    TRIG_IN_MUX_10_CAN1_FIFO0_TR_OUT0 = 0x00000A9Au, /* canfd[1].tr_fifo0[0] */
    TRIG_IN_MUX_10_CAN1_FIFO0_TR_OUT1 = 0x00000A9Bu, /* canfd[1].tr_fifo0[1] */
    TRIG_IN_MUX_10_CAN1_FIFO0_TR_OUT2 = 0x00000A9Cu, /* canfd[1].tr_fifo0[2] */
    TRIG_IN_MUX_10_CAN1_FIFO0_TR_OUT3 = 0x00000A9Du, /* canfd[1].tr_fifo0[3] */
    TRIG_IN_MUX_10_CAN1_FIFO1_TR_OUT0 = 0x00000A9Eu, /* canfd[1].tr_fifo1[0] */
    TRIG_IN_MUX_10_CAN1_FIFO1_TR_OUT1 = 0x00000A9Fu, /* canfd[1].tr_fifo1[1] */
    TRIG_IN_MUX_10_CAN1_FIFO1_TR_OUT2 = 0x00000AA0u, /* canfd[1].tr_fifo1[2] */
    TRIG_IN_MUX_10_CAN1_FIFO1_TR_OUT3 = 0x00000AA1u, /* canfd[1].tr_fifo1[3] */
    TRIG_IN_MUX_10_CAN1_TT_TR_OUT0  = 0x00000AA2u, /* canfd[1].tr_tmp_rtp_out[0] */
    TRIG_IN_MUX_10_CAN1_TT_TR_OUT1  = 0x00000AA3u, /* canfd[1].tr_tmp_rtp_out[1] */
    TRIG_IN_MUX_10_CAN1_TT_TR_OUT2  = 0x00000AA4u, /* canfd[1].tr_tmp_rtp_out[2] */
    TRIG_IN_MUX_10_CAN1_TT_TR_OUT3  = 0x00000AA5u, /* canfd[1].tr_tmp_rtp_out[3] */
    TRIG_IN_MUX_10_CTI_TR_OUT0      = 0x00000AA6u, /* cpuss.cti_tr_out[0] */
    TRIG_IN_MUX_10_CTI_TR_OUT1      = 0x00000AA7u, /* cpuss.cti_tr_out[1] */
    TRIG_IN_MUX_10_FAULT_TR_OU0     = 0x00000AA8u, /* cpuss.tr_fault[0] */
    TRIG_IN_MUX_10_FAULT_TR_OU1     = 0x00000AA9u, /* cpuss.tr_fault[1] */
    TRIG_IN_MUX_10_FAULT_TR_OU2     = 0x00000AAAu, /* cpuss.tr_fault[2] */
    TRIG_IN_MUX_10_FAULT_TR_OU3     = 0x00000AABu, /* cpuss.tr_fault[3] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT0   = 0x00000AACu, /* evtgen[0].tr_out[0] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT1   = 0x00000AADu, /* evtgen[0].tr_out[1] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT2   = 0x00000AAEu, /* evtgen[0].tr_out[2] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT3   = 0x00000AAFu, /* evtgen[0].tr_out[3] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT4   = 0x00000AB0u, /* evtgen[0].tr_out[4] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT5   = 0x00000AB1u, /* evtgen[0].tr_out[5] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT6   = 0x00000AB2u, /* evtgen[0].tr_out[6] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT7   = 0x00000AB3u, /* evtgen[0].tr_out[7] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT8   = 0x00000AB4u, /* evtgen[0].tr_out[8] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT9   = 0x00000AB5u, /* evtgen[0].tr_out[9] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT10  = 0x00000AB6u, /* evtgen[0].tr_out[10] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT11  = 0x00000AB7u, /* evtgen[0].tr_out[11] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT12  = 0x00000AB8u, /* evtgen[0].tr_out[12] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT13  = 0x00000AB9u, /* evtgen[0].tr_out[13] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT14  = 0x00000ABAu, /* evtgen[0].tr_out[14] */
    TRIG_IN_MUX_10_EVTGEN_TR_OUT15  = 0x00000ABBu /* evtgen[0].tr_out[15] */
} en_trig_input_debugreduction1_t;

/* Trigger Input Group 11 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT00 = 0x00000B01u, /* tcpwm[0].tr_out0[512] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT01 = 0x00000B02u, /* tcpwm[0].tr_out0[513] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT02 = 0x00000B03u, /* tcpwm[0].tr_out0[514] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT03 = 0x00000B04u, /* tcpwm[0].tr_out0[515] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT04 = 0x00000B05u, /* tcpwm[0].tr_out0[516] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT05 = 0x00000B06u, /* tcpwm[0].tr_out0[517] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT06 = 0x00000B07u, /* tcpwm[0].tr_out0[518] */
    TRIG_IN_MUX_11_TCPWM_32_TR_OUT07 = 0x00000B08u, /* tcpwm[0].tr_out0[519] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT00 = 0x00000B09u, /* tcpwm[0].tr_out0[256] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT01 = 0x00000B0Au, /* tcpwm[0].tr_out0[257] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT02 = 0x00000B0Bu, /* tcpwm[0].tr_out0[258] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT03 = 0x00000B0Cu, /* tcpwm[0].tr_out0[259] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT04 = 0x00000B0Du, /* tcpwm[0].tr_out0[260] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT05 = 0x00000B0Eu, /* tcpwm[0].tr_out0[261] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT06 = 0x00000B0Fu, /* tcpwm[0].tr_out0[262] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT07 = 0x00000B10u, /* tcpwm[0].tr_out0[263] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT08 = 0x00000B11u, /* tcpwm[0].tr_out0[264] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT09 = 0x00000B12u, /* tcpwm[0].tr_out0[265] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT010 = 0x00000B13u, /* tcpwm[0].tr_out0[266] */
    TRIG_IN_MUX_11_TCPWM_16M_TR_OUT011 = 0x00000B14u, /* tcpwm[0].tr_out0[267] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT00 = 0x00000B15u, /* tcpwm[0].tr_out0[0] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT01 = 0x00000B16u, /* tcpwm[0].tr_out0[1] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT02 = 0x00000B17u, /* tcpwm[0].tr_out0[2] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT03 = 0x00000B18u, /* tcpwm[0].tr_out0[3] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT04 = 0x00000B19u, /* tcpwm[0].tr_out0[4] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT05 = 0x00000B1Au, /* tcpwm[0].tr_out0[5] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT06 = 0x00000B1Bu, /* tcpwm[0].tr_out0[6] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT07 = 0x00000B1Cu, /* tcpwm[0].tr_out0[7] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT08 = 0x00000B1Du, /* tcpwm[0].tr_out0[8] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT09 = 0x00000B1Eu, /* tcpwm[0].tr_out0[9] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT010 = 0x00000B1Fu, /* tcpwm[0].tr_out0[10] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT011 = 0x00000B20u, /* tcpwm[0].tr_out0[11] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT012 = 0x00000B21u, /* tcpwm[0].tr_out0[12] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT013 = 0x00000B22u, /* tcpwm[0].tr_out0[13] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT014 = 0x00000B23u, /* tcpwm[0].tr_out0[14] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT015 = 0x00000B24u, /* tcpwm[0].tr_out0[15] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT016 = 0x00000B25u, /* tcpwm[0].tr_out0[16] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT017 = 0x00000B26u, /* tcpwm[0].tr_out0[17] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT018 = 0x00000B27u, /* tcpwm[0].tr_out0[18] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT019 = 0x00000B28u, /* tcpwm[0].tr_out0[19] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT020 = 0x00000B29u, /* tcpwm[0].tr_out0[20] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT021 = 0x00000B2Au, /* tcpwm[0].tr_out0[21] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT022 = 0x00000B2Bu, /* tcpwm[0].tr_out0[22] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT023 = 0x00000B2Cu, /* tcpwm[0].tr_out0[23] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT024 = 0x00000B2Du, /* tcpwm[0].tr_out0[24] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT025 = 0x00000B2Eu, /* tcpwm[0].tr_out0[25] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT026 = 0x00000B2Fu, /* tcpwm[0].tr_out0[26] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT027 = 0x00000B30u, /* tcpwm[0].tr_out0[27] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT028 = 0x00000B31u, /* tcpwm[0].tr_out0[28] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT029 = 0x00000B32u, /* tcpwm[0].tr_out0[29] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT030 = 0x00000B33u, /* tcpwm[0].tr_out0[30] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT031 = 0x00000B34u, /* tcpwm[0].tr_out0[31] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT032 = 0x00000B35u, /* tcpwm[0].tr_out0[32] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT033 = 0x00000B36u, /* tcpwm[0].tr_out0[33] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT034 = 0x00000B37u, /* tcpwm[0].tr_out0[34] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT035 = 0x00000B38u, /* tcpwm[0].tr_out0[35] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT036 = 0x00000B39u, /* tcpwm[0].tr_out0[36] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT037 = 0x00000B3Au, /* tcpwm[0].tr_out0[37] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT038 = 0x00000B3Bu, /* tcpwm[0].tr_out0[38] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT039 = 0x00000B3Cu, /* tcpwm[0].tr_out0[39] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT040 = 0x00000B3Du, /* tcpwm[0].tr_out0[40] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT041 = 0x00000B3Eu, /* tcpwm[0].tr_out0[41] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT042 = 0x00000B3Fu, /* tcpwm[0].tr_out0[42] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT043 = 0x00000B40u, /* tcpwm[0].tr_out0[43] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT044 = 0x00000B41u, /* tcpwm[0].tr_out0[44] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT045 = 0x00000B42u, /* tcpwm[0].tr_out0[45] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT046 = 0x00000B43u, /* tcpwm[0].tr_out0[46] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT047 = 0x00000B44u, /* tcpwm[0].tr_out0[47] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT048 = 0x00000B45u, /* tcpwm[0].tr_out0[48] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT049 = 0x00000B46u, /* tcpwm[0].tr_out0[49] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT050 = 0x00000B47u, /* tcpwm[0].tr_out0[50] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT051 = 0x00000B48u, /* tcpwm[0].tr_out0[51] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT052 = 0x00000B49u, /* tcpwm[0].tr_out0[52] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT053 = 0x00000B4Au, /* tcpwm[0].tr_out0[53] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT054 = 0x00000B4Bu, /* tcpwm[0].tr_out0[54] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT055 = 0x00000B4Cu, /* tcpwm[0].tr_out0[55] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT056 = 0x00000B4Du, /* tcpwm[0].tr_out0[56] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT057 = 0x00000B4Eu, /* tcpwm[0].tr_out0[57] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT058 = 0x00000B4Fu, /* tcpwm[0].tr_out0[58] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT059 = 0x00000B50u, /* tcpwm[0].tr_out0[59] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT060 = 0x00000B51u, /* tcpwm[0].tr_out0[60] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT061 = 0x00000B52u, /* tcpwm[0].tr_out0[61] */
    TRIG_IN_MUX_11_TCPWM_16_TR_OUT062 = 0x00000B53u, /* tcpwm[0].tr_out0[62] */
    TRIG_IN_MUX_11_SMIF_TX_TR_OUT   = 0x00000B54u, /* smif[0].tr_tx_req */
    TRIG_IN_MUX_11_SMIF_RX_TR_OUT   = 0x00000B55u, /* smif[0].tr_rx_req */
    TRIG_IN_MUX_11_I2S0_TX_TR_OUT   = 0x00000B56u, /* audioss[0].tr_i2s_tx_req */
    TRIG_IN_MUX_11_I2S0_RX_TR_OUT   = 0x00000B57u, /* audioss[0].tr_i2s_rx_req */
    TRIG_IN_MUX_11_I2S1_TX_TR_OUT   = 0x00000B58u, /* audioss[1].tr_i2s_tx_req */
    TRIG_IN_MUX_11_I2S1_RX_TR_OUT   = 0x00000B59u, /* audioss[1].tr_i2s_rx_req */
    TRIG_IN_MUX_11_I2S2_TX_TR_OUT   = 0x00000B5Au, /* audioss[2].tr_i2s_tx_req */
    TRIG_IN_MUX_11_I2S2_RX_TR_OUT   = 0x00000B5Bu, /* audioss[2].tr_i2s_rx_req */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT0  = 0x00000B5Cu, /* peri.tr_io_input[0] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT1  = 0x00000B5Du, /* peri.tr_io_input[1] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT2  = 0x00000B5Eu, /* peri.tr_io_input[2] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT3  = 0x00000B5Fu, /* peri.tr_io_input[3] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT4  = 0x00000B60u, /* peri.tr_io_input[4] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT5  = 0x00000B61u, /* peri.tr_io_input[5] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT6  = 0x00000B62u, /* peri.tr_io_input[6] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT7  = 0x00000B63u, /* peri.tr_io_input[7] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT8  = 0x00000B64u, /* peri.tr_io_input[8] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT9  = 0x00000B65u, /* peri.tr_io_input[9] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT10 = 0x00000B66u, /* peri.tr_io_input[10] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT11 = 0x00000B67u, /* peri.tr_io_input[11] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT12 = 0x00000B68u, /* peri.tr_io_input[12] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT13 = 0x00000B69u, /* peri.tr_io_input[13] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT14 = 0x00000B6Au, /* peri.tr_io_input[14] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT15 = 0x00000B6Bu, /* peri.tr_io_input[15] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT16 = 0x00000B6Cu, /* peri.tr_io_input[16] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT17 = 0x00000B6Du, /* peri.tr_io_input[17] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT18 = 0x00000B6Eu, /* peri.tr_io_input[18] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT19 = 0x00000B6Fu, /* peri.tr_io_input[19] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT20 = 0x00000B70u, /* peri.tr_io_input[20] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT21 = 0x00000B71u, /* peri.tr_io_input[21] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT22 = 0x00000B72u, /* peri.tr_io_input[22] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT23 = 0x00000B73u, /* peri.tr_io_input[23] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT24 = 0x00000B74u, /* peri.tr_io_input[24] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT25 = 0x00000B75u, /* peri.tr_io_input[25] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT26 = 0x00000B76u, /* peri.tr_io_input[26] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT27 = 0x00000B77u, /* peri.tr_io_input[27] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT28 = 0x00000B78u, /* peri.tr_io_input[28] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT29 = 0x00000B79u, /* peri.tr_io_input[29] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT30 = 0x00000B7Au, /* peri.tr_io_input[30] */
    TRIG_IN_MUX_11_HSIOM_IO_INPUT31 = 0x00000B7Bu /* peri.tr_io_input[31] */
} en_trig_input_debugreduction2_t;

/* Trigger Input Group 12 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_IN_MUX_12_PDMA1_TR_OUT0    = 0x00000C01u, /* cpuss.dw1_tr_out[0] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT1    = 0x00000C02u, /* cpuss.dw1_tr_out[1] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT2    = 0x00000C03u, /* cpuss.dw1_tr_out[2] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT3    = 0x00000C04u, /* cpuss.dw1_tr_out[3] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT4    = 0x00000C05u, /* cpuss.dw1_tr_out[4] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT5    = 0x00000C06u, /* cpuss.dw1_tr_out[5] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT6    = 0x00000C07u, /* cpuss.dw1_tr_out[6] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT7    = 0x00000C08u, /* cpuss.dw1_tr_out[7] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT8    = 0x00000C09u, /* cpuss.dw1_tr_out[8] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT9    = 0x00000C0Au, /* cpuss.dw1_tr_out[9] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT10   = 0x00000C0Bu, /* cpuss.dw1_tr_out[10] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT11   = 0x00000C0Cu, /* cpuss.dw1_tr_out[11] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT12   = 0x00000C0Du, /* cpuss.dw1_tr_out[12] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT13   = 0x00000C0Eu, /* cpuss.dw1_tr_out[13] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT14   = 0x00000C0Fu, /* cpuss.dw1_tr_out[14] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT15   = 0x00000C10u, /* cpuss.dw1_tr_out[15] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT16   = 0x00000C11u, /* cpuss.dw1_tr_out[16] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT17   = 0x00000C12u, /* cpuss.dw1_tr_out[17] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT18   = 0x00000C13u, /* cpuss.dw1_tr_out[18] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT19   = 0x00000C14u, /* cpuss.dw1_tr_out[19] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT20   = 0x00000C15u, /* cpuss.dw1_tr_out[20] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT21   = 0x00000C16u, /* cpuss.dw1_tr_out[21] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT22   = 0x00000C17u, /* cpuss.dw1_tr_out[22] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT23   = 0x00000C18u, /* cpuss.dw1_tr_out[23] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT24   = 0x00000C19u, /* cpuss.dw1_tr_out[24] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT25   = 0x00000C1Au, /* cpuss.dw1_tr_out[25] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT26   = 0x00000C1Bu, /* cpuss.dw1_tr_out[26] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT27   = 0x00000C1Cu, /* cpuss.dw1_tr_out[27] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT28   = 0x00000C1Du, /* cpuss.dw1_tr_out[28] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT29   = 0x00000C1Eu, /* cpuss.dw1_tr_out[29] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT30   = 0x00000C1Fu, /* cpuss.dw1_tr_out[30] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT31   = 0x00000C20u, /* cpuss.dw1_tr_out[31] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT32   = 0x00000C21u, /* cpuss.dw1_tr_out[32] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT33   = 0x00000C22u, /* cpuss.dw1_tr_out[33] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT34   = 0x00000C23u, /* cpuss.dw1_tr_out[34] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT35   = 0x00000C24u, /* cpuss.dw1_tr_out[35] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT36   = 0x00000C25u, /* cpuss.dw1_tr_out[36] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT37   = 0x00000C26u, /* cpuss.dw1_tr_out[37] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT38   = 0x00000C27u, /* cpuss.dw1_tr_out[38] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT39   = 0x00000C28u, /* cpuss.dw1_tr_out[39] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT40   = 0x00000C29u, /* cpuss.dw1_tr_out[40] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT41   = 0x00000C2Au, /* cpuss.dw1_tr_out[41] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT42   = 0x00000C2Bu, /* cpuss.dw1_tr_out[42] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT43   = 0x00000C2Cu, /* cpuss.dw1_tr_out[43] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT44   = 0x00000C2Du, /* cpuss.dw1_tr_out[44] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT45   = 0x00000C2Eu, /* cpuss.dw1_tr_out[45] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT46   = 0x00000C2Fu, /* cpuss.dw1_tr_out[46] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT47   = 0x00000C30u, /* cpuss.dw1_tr_out[47] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT48   = 0x00000C31u, /* cpuss.dw1_tr_out[48] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT49   = 0x00000C32u, /* cpuss.dw1_tr_out[49] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT50   = 0x00000C33u, /* cpuss.dw1_tr_out[50] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT51   = 0x00000C34u, /* cpuss.dw1_tr_out[51] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT52   = 0x00000C35u, /* cpuss.dw1_tr_out[52] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT53   = 0x00000C36u, /* cpuss.dw1_tr_out[53] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT54   = 0x00000C37u, /* cpuss.dw1_tr_out[54] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT55   = 0x00000C38u, /* cpuss.dw1_tr_out[55] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT56   = 0x00000C39u, /* cpuss.dw1_tr_out[56] */
    TRIG_IN_MUX_12_PDMA1_TR_OUT57   = 0x00000C3Au, /* cpuss.dw1_tr_out[57] */
    TRIG_IN_MUX_12_MDMA_TR_OUT0     = 0x00000C3Bu, /* cpuss.dmac_tr_out[0] */
    TRIG_IN_MUX_12_MDMA_TR_OUT1     = 0x00000C3Cu, /* cpuss.dmac_tr_out[1] */
    TRIG_IN_MUX_12_MDMA_TR_OUT2     = 0x00000C3Du, /* cpuss.dmac_tr_out[2] */
    TRIG_IN_MUX_12_MDMA_TR_OUT3     = 0x00000C3Eu, /* cpuss.dmac_tr_out[3] */
    TRIG_IN_MUX_12_MDMA_TR_OUT4     = 0x00000C3Fu, /* cpuss.dmac_tr_out[4] */
    TRIG_IN_MUX_12_MDMA_TR_OUT5     = 0x00000C40u, /* cpuss.dmac_tr_out[5] */
    TRIG_IN_MUX_12_MDMA_TR_OUT6     = 0x00000C41u, /* cpuss.dmac_tr_out[6] */
    TRIG_IN_MUX_12_MDMA_TR_OUT7     = 0x00000C42u, /* cpuss.dmac_tr_out[7] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT10 = 0x00000C43u, /* tcpwm[0].tr_out1[0] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT11 = 0x00000C44u, /* tcpwm[0].tr_out1[1] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT12 = 0x00000C45u, /* tcpwm[0].tr_out1[2] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT13 = 0x00000C46u, /* tcpwm[0].tr_out1[3] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT14 = 0x00000C47u, /* tcpwm[0].tr_out1[4] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT15 = 0x00000C48u, /* tcpwm[0].tr_out1[5] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT16 = 0x00000C49u, /* tcpwm[0].tr_out1[6] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT17 = 0x00000C4Au, /* tcpwm[0].tr_out1[7] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT18 = 0x00000C4Bu, /* tcpwm[0].tr_out1[8] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT19 = 0x00000C4Cu, /* tcpwm[0].tr_out1[9] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT110 = 0x00000C4Du, /* tcpwm[0].tr_out1[10] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT111 = 0x00000C4Eu, /* tcpwm[0].tr_out1[11] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT112 = 0x00000C4Fu, /* tcpwm[0].tr_out1[12] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT113 = 0x00000C50u, /* tcpwm[0].tr_out1[13] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT114 = 0x00000C51u, /* tcpwm[0].tr_out1[14] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT115 = 0x00000C52u, /* tcpwm[0].tr_out1[15] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT116 = 0x00000C53u, /* tcpwm[0].tr_out1[16] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT117 = 0x00000C54u, /* tcpwm[0].tr_out1[17] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT118 = 0x00000C55u, /* tcpwm[0].tr_out1[18] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT119 = 0x00000C56u, /* tcpwm[0].tr_out1[19] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT120 = 0x00000C57u, /* tcpwm[0].tr_out1[20] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT121 = 0x00000C58u, /* tcpwm[0].tr_out1[21] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT122 = 0x00000C59u, /* tcpwm[0].tr_out1[22] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT123 = 0x00000C5Au, /* tcpwm[0].tr_out1[23] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT124 = 0x00000C5Bu, /* tcpwm[0].tr_out1[24] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT125 = 0x00000C5Cu, /* tcpwm[0].tr_out1[25] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT126 = 0x00000C5Du, /* tcpwm[0].tr_out1[26] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT127 = 0x00000C5Eu, /* tcpwm[0].tr_out1[27] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT128 = 0x00000C5Fu, /* tcpwm[0].tr_out1[28] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT129 = 0x00000C60u, /* tcpwm[0].tr_out1[29] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT130 = 0x00000C61u, /* tcpwm[0].tr_out1[30] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT131 = 0x00000C62u, /* tcpwm[0].tr_out1[31] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT132 = 0x00000C63u, /* tcpwm[0].tr_out1[32] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT133 = 0x00000C64u, /* tcpwm[0].tr_out1[33] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT134 = 0x00000C65u, /* tcpwm[0].tr_out1[34] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT135 = 0x00000C66u, /* tcpwm[0].tr_out1[35] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT136 = 0x00000C67u, /* tcpwm[0].tr_out1[36] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT137 = 0x00000C68u, /* tcpwm[0].tr_out1[37] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT138 = 0x00000C69u, /* tcpwm[0].tr_out1[38] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT139 = 0x00000C6Au, /* tcpwm[0].tr_out1[39] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT140 = 0x00000C6Bu, /* tcpwm[0].tr_out1[40] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT141 = 0x00000C6Cu, /* tcpwm[0].tr_out1[41] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT142 = 0x00000C6Du, /* tcpwm[0].tr_out1[42] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT143 = 0x00000C6Eu, /* tcpwm[0].tr_out1[43] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT144 = 0x00000C6Fu, /* tcpwm[0].tr_out1[44] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT145 = 0x00000C70u, /* tcpwm[0].tr_out1[45] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT146 = 0x00000C71u, /* tcpwm[0].tr_out1[46] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT147 = 0x00000C72u, /* tcpwm[0].tr_out1[47] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT148 = 0x00000C73u, /* tcpwm[0].tr_out1[48] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT149 = 0x00000C74u, /* tcpwm[0].tr_out1[49] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT150 = 0x00000C75u, /* tcpwm[0].tr_out1[50] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT151 = 0x00000C76u, /* tcpwm[0].tr_out1[51] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT152 = 0x00000C77u, /* tcpwm[0].tr_out1[52] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT153 = 0x00000C78u, /* tcpwm[0].tr_out1[53] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT154 = 0x00000C79u, /* tcpwm[0].tr_out1[54] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT155 = 0x00000C7Au, /* tcpwm[0].tr_out1[55] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT156 = 0x00000C7Bu, /* tcpwm[0].tr_out1[56] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT157 = 0x00000C7Cu, /* tcpwm[0].tr_out1[57] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT158 = 0x00000C7Du, /* tcpwm[0].tr_out1[58] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT159 = 0x00000C7Eu, /* tcpwm[0].tr_out1[59] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT160 = 0x00000C7Fu, /* tcpwm[0].tr_out1[60] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT161 = 0x00000C80u, /* tcpwm[0].tr_out1[61] */
    TRIG_IN_MUX_12_TCPWM_16_TR_OUT162 = 0x00000C81u, /* tcpwm[0].tr_out1[62] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT10 = 0x00000C82u, /* tcpwm[0].tr_out1[256] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT11 = 0x00000C83u, /* tcpwm[0].tr_out1[257] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT12 = 0x00000C84u, /* tcpwm[0].tr_out1[258] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT13 = 0x00000C85u, /* tcpwm[0].tr_out1[259] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT14 = 0x00000C86u, /* tcpwm[0].tr_out1[260] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT15 = 0x00000C87u, /* tcpwm[0].tr_out1[261] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT16 = 0x00000C88u, /* tcpwm[0].tr_out1[262] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT17 = 0x00000C89u, /* tcpwm[0].tr_out1[263] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT18 = 0x00000C8Au, /* tcpwm[0].tr_out1[264] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT19 = 0x00000C8Bu, /* tcpwm[0].tr_out1[265] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT110 = 0x00000C8Cu, /* tcpwm[0].tr_out1[266] */
    TRIG_IN_MUX_12_TCPWM_16M_TR_OUT111 = 0x00000C8Du, /* tcpwm[0].tr_out1[267] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT10 = 0x00000C8Eu, /* tcpwm[0].tr_out1[512] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT11 = 0x00000C8Fu, /* tcpwm[0].tr_out1[513] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT12 = 0x00000C90u, /* tcpwm[0].tr_out1[514] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT13 = 0x00000C91u, /* tcpwm[0].tr_out1[515] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT14 = 0x00000C92u, /* tcpwm[0].tr_out1[516] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT15 = 0x00000C93u, /* tcpwm[0].tr_out1[517] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT16 = 0x00000C94u, /* tcpwm[0].tr_out1[518] */
    TRIG_IN_MUX_12_TCPWM_32_TR_OUT17 = 0x00000C95u, /* tcpwm[0].tr_out1[519] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT0 = 0x00000C96u, /* pass[0].tr_sar_gen_out[0] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT1 = 0x00000C97u, /* pass[0].tr_sar_gen_out[1] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT2 = 0x00000C98u, /* pass[0].tr_sar_gen_out[2] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT3 = 0x00000C99u, /* pass[0].tr_sar_gen_out[3] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT4 = 0x00000C9Au, /* pass[0].tr_sar_gen_out[4] */
    TRIG_IN_MUX_12_PASS_GEN_TR_OUT5 = 0x00000C9Bu /* pass[0].tr_sar_gen_out[5] */
} en_trig_input_debugreduction3_t;

/* Trigger Group Outputs */
/* Trigger Output Group 0 - P-DMA0[0:7] Request Assignments */
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
} en_trig_output_pdma0_tr_0_t;

/* Trigger Output Group 1 - P-DMA0[8:15] Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_1_PDMA0_TR_IN8     = 0x40000100u, /* cpuss.dw0_tr_in[8] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN9     = 0x40000101u, /* cpuss.dw0_tr_in[9] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN10    = 0x40000102u, /* cpuss.dw0_tr_in[10] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN11    = 0x40000103u, /* cpuss.dw0_tr_in[11] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN12    = 0x40000104u, /* cpuss.dw0_tr_in[12] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN13    = 0x40000105u, /* cpuss.dw0_tr_in[13] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN14    = 0x40000106u, /* cpuss.dw0_tr_in[14] */
    TRIG_OUT_MUX_1_PDMA0_TR_IN15    = 0x40000107u /* cpuss.dw0_tr_in[15] */
} en_trig_output_pdma0_tr_1_t;

/* Trigger Output Group 2 - P-DMA1[0:15] Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_2_PDMA1_TR_IN0     = 0x40000200u, /* cpuss.dw1_tr_in[0] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN1     = 0x40000201u, /* cpuss.dw1_tr_in[1] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN2     = 0x40000202u, /* cpuss.dw1_tr_in[2] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN3     = 0x40000203u, /* cpuss.dw1_tr_in[3] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN4     = 0x40000204u, /* cpuss.dw1_tr_in[4] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN5     = 0x40000205u, /* cpuss.dw1_tr_in[5] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN6     = 0x40000206u, /* cpuss.dw1_tr_in[6] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN7     = 0x40000207u, /* cpuss.dw1_tr_in[7] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN8     = 0x40000208u, /* cpuss.dw1_tr_in[8] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN9     = 0x40000209u, /* cpuss.dw1_tr_in[9] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN10    = 0x4000020Au, /* cpuss.dw1_tr_in[10] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN11    = 0x4000020Bu, /* cpuss.dw1_tr_in[11] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN12    = 0x4000020Cu, /* cpuss.dw1_tr_in[12] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN13    = 0x4000020Du, /* cpuss.dw1_tr_in[13] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN14    = 0x4000020Eu, /* cpuss.dw1_tr_in[14] */
    TRIG_OUT_MUX_2_PDMA1_TR_IN15    = 0x4000020Fu /* cpuss.dw1_tr_in[15] */
} en_trig_output_pdma1_tr_t;

/* Trigger Output Group 3 - M-DMA Request Assignments */
typedef enum
{
    TRIG_OUT_MUX_3_MDMA_TR_IN0      = 0x40000300u, /* cpuss.dmac_tr_in[0] */
    TRIG_OUT_MUX_3_MDMA_TR_IN1      = 0x40000301u, /* cpuss.dmac_tr_in[1] */
    TRIG_OUT_MUX_3_MDMA_TR_IN2      = 0x40000302u, /* cpuss.dmac_tr_in[2] */
    TRIG_OUT_MUX_3_MDMA_TR_IN3      = 0x40000303u, /* cpuss.dmac_tr_in[3] */
    TRIG_OUT_MUX_3_MDMA_TR_IN4      = 0x40000304u, /* cpuss.dmac_tr_in[4] */
    TRIG_OUT_MUX_3_MDMA_TR_IN5      = 0x40000305u, /* cpuss.dmac_tr_in[5] */
    TRIG_OUT_MUX_3_MDMA_TR_IN6      = 0x40000306u, /* cpuss.dmac_tr_in[6] */
    TRIG_OUT_MUX_3_MDMA_TR_IN7      = 0x40000307u /* cpuss.dmac_tr_in[7] */
} en_trig_output_mdma_t;

/* Trigger Output Group 5 -  */
typedef enum
{
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN0 = 0x40000500u, /* tcpwm[0].tr_all_cnt_in[0] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN1 = 0x40000501u, /* tcpwm[0].tr_all_cnt_in[1] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN2 = 0x40000502u, /* tcpwm[0].tr_all_cnt_in[2] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN3 = 0x40000503u, /* tcpwm[0].tr_all_cnt_in[3] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN4 = 0x40000504u, /* tcpwm[0].tr_all_cnt_in[4] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN5 = 0x40000505u, /* tcpwm[0].tr_all_cnt_in[5] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN6 = 0x40000506u, /* tcpwm[0].tr_all_cnt_in[6] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN7 = 0x40000507u, /* tcpwm[0].tr_all_cnt_in[7] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN8 = 0x40000508u, /* tcpwm[0].tr_all_cnt_in[8] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN9 = 0x40000509u, /* tcpwm[0].tr_all_cnt_in[9] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN10 = 0x4000050Au, /* tcpwm[0].tr_all_cnt_in[10] */
    TRIG_OUT_MUX_5_TCPWM_ALL_CNT_TR_IN11 = 0x4000050Bu /* tcpwm[0].tr_all_cnt_in[11] */
} en_trig_output_tcpwm_out_t;

/* Trigger Output Group 6 - TCPWM trigger inputs */
typedef enum
{
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN12 = 0x40000600u, /* tcpwm[0].tr_all_cnt_in[12] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN13 = 0x40000601u, /* tcpwm[0].tr_all_cnt_in[13] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN14 = 0x40000602u, /* tcpwm[0].tr_all_cnt_in[14] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN15 = 0x40000603u, /* tcpwm[0].tr_all_cnt_in[15] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN16 = 0x40000604u, /* tcpwm[0].tr_all_cnt_in[16] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN17 = 0x40000605u, /* tcpwm[0].tr_all_cnt_in[17] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN18 = 0x40000606u, /* tcpwm[0].tr_all_cnt_in[18] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN19 = 0x40000607u, /* tcpwm[0].tr_all_cnt_in[19] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN20 = 0x40000608u, /* tcpwm[0].tr_all_cnt_in[20] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN21 = 0x40000609u, /* tcpwm[0].tr_all_cnt_in[21] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN22 = 0x4000060Au, /* tcpwm[0].tr_all_cnt_in[22] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN23 = 0x4000060Bu, /* tcpwm[0].tr_all_cnt_in[23] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN24 = 0x4000060Cu, /* tcpwm[0].tr_all_cnt_in[24] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN25 = 0x4000060Du, /* tcpwm[0].tr_all_cnt_in[25] */
    TRIG_OUT_MUX_6_TCPWM_ALL_CNT_TR_IN26 = 0x4000060Eu /* tcpwm[0].tr_all_cnt_in[26] */
} en_trig_output_tcpwm_in_t;

/* Trigger Output Group 7 - PASS trigger multiplexer */
typedef enum
{
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN0  = 0x40000700u, /* pass[0].tr_sar_gen_in[0] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN1  = 0x40000701u, /* pass[0].tr_sar_gen_in[1] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN2  = 0x40000702u, /* pass[0].tr_sar_gen_in[2] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN3  = 0x40000703u, /* pass[0].tr_sar_gen_in[3] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN4  = 0x40000704u, /* pass[0].tr_sar_gen_in[4] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN5  = 0x40000705u, /* pass[0].tr_sar_gen_in[5] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN6  = 0x40000706u, /* pass[0].tr_sar_gen_in[6] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN7  = 0x40000707u, /* pass[0].tr_sar_gen_in[7] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN8  = 0x40000708u, /* pass[0].tr_sar_gen_in[8] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN9  = 0x40000709u, /* pass[0].tr_sar_gen_in[9] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN10 = 0x4000070Au, /* pass[0].tr_sar_gen_in[10] */
    TRIG_OUT_MUX_7_PASS_GEN_TR_IN11 = 0x4000070Bu /* pass[0].tr_sar_gen_in[11] */
} en_trig_output_pass_t;

/* Trigger Output Group 8 - CAN TT Synchronization triggers */
typedef enum
{
    TRIG_OUT_MUX_8_CAN0_TT_TR_IN0   = 0x40000800u, /* canfd[0].tr_evt_swt_in[0] */
    TRIG_OUT_MUX_8_CAN0_TT_TR_IN1   = 0x40000801u, /* canfd[0].tr_evt_swt_in[1] */
    TRIG_OUT_MUX_8_CAN0_TT_TR_IN2   = 0x40000802u, /* canfd[0].tr_evt_swt_in[2] */
    TRIG_OUT_MUX_8_CAN0_TT_TR_IN3   = 0x40000803u, /* canfd[0].tr_evt_swt_in[3] */
    TRIG_OUT_MUX_8_CAN1_TT_TR_IN0   = 0x40000804u, /* canfd[1].tr_evt_swt_in[0] */
    TRIG_OUT_MUX_8_CAN1_TT_TR_IN1   = 0x40000805u, /* canfd[1].tr_evt_swt_in[1] */
    TRIG_OUT_MUX_8_CAN1_TT_TR_IN2   = 0x40000806u, /* canfd[1].tr_evt_swt_in[2] */
    TRIG_OUT_MUX_8_CAN1_TT_TR_IN3   = 0x40000807u /* canfd[1].tr_evt_swt_in[3] */
} en_trig_output_cantt_t;

/* Trigger Output Group 9 - 2nd level MUX using input from MUX_9/10/11 */
typedef enum
{
    TRIG_OUT_MUX_9_HSIOM_IO_OUTPUT0 = 0x40000900u, /* peri.tr_io_output[0] */
    TRIG_OUT_MUX_9_HSIOM_IO_OUTPUT1 = 0x40000901u, /* peri.tr_io_output[1] */
    TRIG_OUT_MUX_9_CTI_TR_IN0       = 0x40000902u, /* cpuss.cti_tr_in[0] */
    TRIG_OUT_MUX_9_CTI_TR_IN1       = 0x40000903u, /* cpuss.cti_tr_in[1] */
    TRIG_OUT_MUX_9_PERI_DEBUG_FREEZE_TR_IN = 0x40000904u, /* peri.tr_dbg_freeze */
    TRIG_OUT_MUX_9_PASS_DEBUG_FREEZE_TR_IN = 0x40000905u, /* pass[0].tr_debug_freeze */
    TRIG_OUT_MUX_9_SRSS_WDT_DEBUG_FREEZE_TR_IN = 0x40000906u, /* srss.tr_debug_freeze_wdt */
    TRIG_OUT_MUX_9_SRSS_MCWDT_DEBUG_FREEZE_TR_IN2 = 0x40000907u, /* srss.tr_debug_freeze_mcwdt[2] */
    TRIG_OUT_MUX_9_SRSS_MCWDT_DEBUG_FREEZE_TR_IN1 = 0x40000908u, /* srss.tr_debug_freeze_mcwdt[1] */
    TRIG_OUT_MUX_9_SRSS_MCWDT_DEBUG_FREEZE_TR_IN0 = 0x40000909u, /* srss.tr_debug_freeze_mcwdt[0] */
    TRIG_OUT_MUX_9_TCPWM_DEBUG_FREEZE_TR_IN = 0x4000090Au /* tcpwm[0].tr_debug_freeze */
} en_trig_output_debugmain_t;

/* Trigger Output Group 10 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_OUT_MUX_10_TR_GROUP9_INPUT1 = 0x40000A00u, /* tr_group[9].input[1] */
    TRIG_OUT_MUX_10_TR_GROUP9_INPUT2 = 0x40000A01u, /* tr_group[9].input[2] */
    TRIG_OUT_MUX_10_TR_GROUP9_INPUT3 = 0x40000A02u, /* tr_group[9].input[3] */
    TRIG_OUT_MUX_10_TR_GROUP9_INPUT4 = 0x40000A03u, /* tr_group[9].input[4] */
    TRIG_OUT_MUX_10_TR_GROUP9_INPUT5 = 0x40000A04u /* tr_group[9].input[5] */
} en_trig_output_debugreduction1_t;

/* Trigger Output Group 11 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_OUT_MUX_11_TR_GROUP9_INPUT6 = 0x40000B00u, /* tr_group[9].input[6] */
    TRIG_OUT_MUX_11_TR_GROUP9_INPUT7 = 0x40000B01u, /* tr_group[9].input[7] */
    TRIG_OUT_MUX_11_TR_GROUP9_INPUT8 = 0x40000B02u, /* tr_group[9].input[8] */
    TRIG_OUT_MUX_11_TR_GROUP9_INPUT9 = 0x40000B03u, /* tr_group[9].input[9] */
    TRIG_OUT_MUX_11_TR_GROUP9_INPUT10 = 0x40000B04u /* tr_group[9].input[10] */
} en_trig_output_debugreduction2_t;

/* Trigger Output Group 12 - Makes all possible triggers visible as I/O signals for debug purposes, or to build external circuitry */
typedef enum
{
    TRIG_OUT_MUX_12_TR_GROUP9_INPUT11 = 0x40000C00u, /* tr_group[9].input[11] */
    TRIG_OUT_MUX_12_TR_GROUP9_INPUT12 = 0x40000C01u, /* tr_group[9].input[12] */
    TRIG_OUT_MUX_12_TR_GROUP9_INPUT13 = 0x40000C02u, /* tr_group[9].input[13] */
    TRIG_OUT_MUX_12_TR_GROUP9_INPUT14 = 0x40000C03u, /* tr_group[9].input[14] */
    TRIG_OUT_MUX_12_TR_GROUP9_INPUT15 = 0x40000C04u /* tr_group[9].input[15] */
} en_trig_output_debugreduction3_t;

/* Trigger Output Group 0 - CAN DW Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_0_CAN0_DBG_TO_PDMA0_0 = 0x40001000u, /* From canfd[0].tr_dbg_dma_req[0] to cpuss.dw0_tr_in[16] */
    TRIG_OUT_1TO1_0_CAN0_FIFO0_TO_PDMA0_0 = 0x40001001u, /* From canfd[0].tr_fifo0[0] to cpuss.dw0_tr_in[17] */
    TRIG_OUT_1TO1_0_CAN0_FIFO1_TO_PDMA0_0 = 0x40001002u, /* From canfd[0].tr_fifo1[0] to cpuss.dw0_tr_in[18] */
    TRIG_OUT_1TO1_0_CAN0_DBG_TO_PDMA0_1 = 0x40001003u, /* From canfd[0].tr_dbg_dma_req[1] to cpuss.dw0_tr_in[19] */
    TRIG_OUT_1TO1_0_CAN0_FIFO0_TO_PDMA0_1 = 0x40001004u, /* From canfd[0].tr_fifo0[1] to cpuss.dw0_tr_in[20] */
    TRIG_OUT_1TO1_0_CAN0_FIFO1_TO_PDMA0_1 = 0x40001005u, /* From canfd[0].tr_fifo1[1] to cpuss.dw0_tr_in[21] */
    TRIG_OUT_1TO1_0_CAN0_DBG_TO_PDMA0_2 = 0x40001006u, /* From canfd[0].tr_dbg_dma_req[2] to cpuss.dw0_tr_in[22] */
    TRIG_OUT_1TO1_0_CAN0_FIFO0_TO_PDMA0_2 = 0x40001007u, /* From canfd[0].tr_fifo0[2] to cpuss.dw0_tr_in[23] */
    TRIG_OUT_1TO1_0_CAN0_FIFO1_TO_PDMA0_2 = 0x40001008u, /* From canfd[0].tr_fifo1[2] to cpuss.dw0_tr_in[24] */
    TRIG_OUT_1TO1_0_CAN0_DBG_TO_PDMA0_3 = 0x40001009u, /* From canfd[0].tr_dbg_dma_req[3] to cpuss.dw0_tr_in[25] */
    TRIG_OUT_1TO1_0_CAN0_FIFO0_TO_PDMA0_3 = 0x4000100Au, /* From canfd[0].tr_fifo0[3] to cpuss.dw0_tr_in[26] */
    TRIG_OUT_1TO1_0_CAN0_FIFO1_TO_PDMA0_3 = 0x4000100Bu /* From canfd[0].tr_fifo1[3] to cpuss.dw0_tr_in[27] */
} en_trig_output_1to1_can0_dw0_tr_t;

/* Trigger Output Group 1 - PASS to DW0 direct connect (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA00 = 0x40001100u, /* From pass[0].tr_sar_ch_done[0] to cpuss.dw0_tr_in[28] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA01 = 0x40001101u, /* From pass[0].tr_sar_ch_done[1] to cpuss.dw0_tr_in[29] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA02 = 0x40001102u, /* From pass[0].tr_sar_ch_done[2] to cpuss.dw0_tr_in[30] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA03 = 0x40001103u, /* From pass[0].tr_sar_ch_done[3] to cpuss.dw0_tr_in[31] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA04 = 0x40001104u, /* From pass[0].tr_sar_ch_done[4] to cpuss.dw0_tr_in[32] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA05 = 0x40001105u, /* From pass[0].tr_sar_ch_done[5] to cpuss.dw0_tr_in[33] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA06 = 0x40001106u, /* From pass[0].tr_sar_ch_done[6] to cpuss.dw0_tr_in[34] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA07 = 0x40001107u, /* From pass[0].tr_sar_ch_done[7] to cpuss.dw0_tr_in[35] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA08 = 0x40001108u, /* From pass[0].tr_sar_ch_done[8] to cpuss.dw0_tr_in[36] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA09 = 0x40001109u, /* From pass[0].tr_sar_ch_done[9] to cpuss.dw0_tr_in[37] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA010 = 0x4000110Au, /* From pass[0].tr_sar_ch_done[10] to cpuss.dw0_tr_in[38] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA011 = 0x4000110Bu, /* From pass[0].tr_sar_ch_done[11] to cpuss.dw0_tr_in[39] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA012 = 0x4000110Cu, /* From pass[0].tr_sar_ch_done[12] to cpuss.dw0_tr_in[40] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA013 = 0x4000110Du, /* From pass[0].tr_sar_ch_done[13] to cpuss.dw0_tr_in[41] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA014 = 0x4000110Eu, /* From pass[0].tr_sar_ch_done[14] to cpuss.dw0_tr_in[42] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA015 = 0x4000110Fu, /* From pass[0].tr_sar_ch_done[15] to cpuss.dw0_tr_in[43] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA016 = 0x40001110u, /* From pass[0].tr_sar_ch_done[16] to cpuss.dw0_tr_in[44] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA017 = 0x40001111u, /* From pass[0].tr_sar_ch_done[17] to cpuss.dw0_tr_in[45] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA018 = 0x40001112u, /* From pass[0].tr_sar_ch_done[18] to cpuss.dw0_tr_in[46] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA019 = 0x40001113u, /* From pass[0].tr_sar_ch_done[19] to cpuss.dw0_tr_in[47] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA020 = 0x40001114u, /* From pass[0].tr_sar_ch_done[20] to cpuss.dw0_tr_in[48] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA021 = 0x40001115u, /* From pass[0].tr_sar_ch_done[21] to cpuss.dw0_tr_in[49] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA022 = 0x40001116u, /* From pass[0].tr_sar_ch_done[22] to cpuss.dw0_tr_in[50] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA023 = 0x40001117u, /* From pass[0].tr_sar_ch_done[23] to cpuss.dw0_tr_in[51] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA024 = 0x40001118u, /* From pass[0].tr_sar_ch_done[24] to cpuss.dw0_tr_in[52] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA025 = 0x40001119u, /* From pass[0].tr_sar_ch_done[25] to cpuss.dw0_tr_in[53] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA026 = 0x4000111Au, /* From pass[0].tr_sar_ch_done[26] to cpuss.dw0_tr_in[54] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA027 = 0x4000111Bu, /* From pass[0].tr_sar_ch_done[27] to cpuss.dw0_tr_in[55] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA028 = 0x4000111Cu, /* From pass[0].tr_sar_ch_done[28] to cpuss.dw0_tr_in[56] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA029 = 0x4000111Du, /* From pass[0].tr_sar_ch_done[29] to cpuss.dw0_tr_in[57] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA030 = 0x4000111Eu, /* From pass[0].tr_sar_ch_done[30] to cpuss.dw0_tr_in[58] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA031 = 0x4000111Fu, /* From pass[0].tr_sar_ch_done[31] to cpuss.dw0_tr_in[59] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA032 = 0x40001120u, /* From pass[0].tr_sar_ch_done[32] to cpuss.dw0_tr_in[60] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA033 = 0x40001121u, /* From pass[0].tr_sar_ch_done[33] to cpuss.dw0_tr_in[61] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA034 = 0x40001122u, /* From pass[0].tr_sar_ch_done[34] to cpuss.dw0_tr_in[62] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA035 = 0x40001123u, /* From pass[0].tr_sar_ch_done[35] to cpuss.dw0_tr_in[63] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA036 = 0x40001124u, /* From pass[0].tr_sar_ch_done[36] to cpuss.dw0_tr_in[64] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA037 = 0x40001125u, /* From pass[0].tr_sar_ch_done[37] to cpuss.dw0_tr_in[65] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA038 = 0x40001126u, /* From pass[0].tr_sar_ch_done[38] to cpuss.dw0_tr_in[66] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA039 = 0x40001127u, /* From pass[0].tr_sar_ch_done[39] to cpuss.dw0_tr_in[67] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA040 = 0x40001128u, /* From pass[0].tr_sar_ch_done[40] to cpuss.dw0_tr_in[68] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA041 = 0x40001129u, /* From pass[0].tr_sar_ch_done[41] to cpuss.dw0_tr_in[69] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA042 = 0x4000112Au, /* From pass[0].tr_sar_ch_done[42] to cpuss.dw0_tr_in[70] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA043 = 0x4000112Bu, /* From pass[0].tr_sar_ch_done[43] to cpuss.dw0_tr_in[71] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA044 = 0x4000112Cu, /* From pass[0].tr_sar_ch_done[44] to cpuss.dw0_tr_in[72] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA045 = 0x4000112Du, /* From pass[0].tr_sar_ch_done[45] to cpuss.dw0_tr_in[73] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA046 = 0x4000112Eu, /* From pass[0].tr_sar_ch_done[46] to cpuss.dw0_tr_in[74] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA047 = 0x4000112Fu, /* From pass[0].tr_sar_ch_done[47] to cpuss.dw0_tr_in[75] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA048 = 0x40001130u, /* From pass[0].tr_sar_ch_done[48] to cpuss.dw0_tr_in[76] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA049 = 0x40001131u, /* From pass[0].tr_sar_ch_done[49] to cpuss.dw0_tr_in[77] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA050 = 0x40001132u, /* From pass[0].tr_sar_ch_done[50] to cpuss.dw0_tr_in[78] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA051 = 0x40001133u, /* From pass[0].tr_sar_ch_done[51] to cpuss.dw0_tr_in[79] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA052 = 0x40001134u, /* From pass[0].tr_sar_ch_done[52] to cpuss.dw0_tr_in[80] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA053 = 0x40001135u, /* From pass[0].tr_sar_ch_done[53] to cpuss.dw0_tr_in[81] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA054 = 0x40001136u, /* From pass[0].tr_sar_ch_done[54] to cpuss.dw0_tr_in[82] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA055 = 0x40001137u, /* From pass[0].tr_sar_ch_done[55] to cpuss.dw0_tr_in[83] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA056 = 0x40001138u, /* From pass[0].tr_sar_ch_done[56] to cpuss.dw0_tr_in[84] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA057 = 0x40001139u, /* From pass[0].tr_sar_ch_done[57] to cpuss.dw0_tr_in[85] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA058 = 0x4000113Au, /* From pass[0].tr_sar_ch_done[58] to cpuss.dw0_tr_in[86] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA059 = 0x4000113Bu, /* From pass[0].tr_sar_ch_done[59] to cpuss.dw0_tr_in[87] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA060 = 0x4000113Cu, /* From pass[0].tr_sar_ch_done[60] to cpuss.dw0_tr_in[88] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA061 = 0x4000113Du, /* From pass[0].tr_sar_ch_done[61] to cpuss.dw0_tr_in[89] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA062 = 0x4000113Eu, /* From pass[0].tr_sar_ch_done[62] to cpuss.dw0_tr_in[90] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA063 = 0x4000113Fu, /* From pass[0].tr_sar_ch_done[63] to cpuss.dw0_tr_in[91] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA064 = 0x40001140u, /* From pass[0].tr_sar_ch_done[64] to cpuss.dw0_tr_in[92] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA065 = 0x40001141u, /* From pass[0].tr_sar_ch_done[65] to cpuss.dw0_tr_in[93] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA066 = 0x40001142u, /* From pass[0].tr_sar_ch_done[66] to cpuss.dw0_tr_in[94] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA067 = 0x40001143u, /* From pass[0].tr_sar_ch_done[67] to cpuss.dw0_tr_in[95] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA068 = 0x40001144u, /* From pass[0].tr_sar_ch_done[68] to cpuss.dw0_tr_in[96] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA069 = 0x40001145u, /* From pass[0].tr_sar_ch_done[69] to cpuss.dw0_tr_in[97] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA070 = 0x40001146u, /* From pass[0].tr_sar_ch_done[70] to cpuss.dw0_tr_in[98] */
    TRIG_OUT_1TO1_1_PASS_CH_DONE_TO_PDMA071 = 0x40001147u /* From pass[0].tr_sar_ch_done[71] to cpuss.dw0_tr_in[99] */
} en_trig_output_1to1_pass_to_dw0_t;

/* Trigger Output Group 2 - SCB DW Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA10 = 0x40001200u, /* From scb[0].tr_tx_req to cpuss.dw1_tr_in[16] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA10 = 0x40001201u, /* From scb[0].tr_rx_req to cpuss.dw1_tr_in[17] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA11 = 0x40001202u, /* From scb[1].tr_tx_req to cpuss.dw1_tr_in[18] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA11 = 0x40001203u, /* From scb[1].tr_rx_req to cpuss.dw1_tr_in[19] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA12 = 0x40001204u, /* From scb[2].tr_tx_req to cpuss.dw1_tr_in[20] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA12 = 0x40001205u, /* From scb[2].tr_rx_req to cpuss.dw1_tr_in[21] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA13 = 0x40001206u, /* From scb[3].tr_tx_req to cpuss.dw1_tr_in[22] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA13 = 0x40001207u, /* From scb[3].tr_rx_req to cpuss.dw1_tr_in[23] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA14 = 0x40001208u, /* From scb[4].tr_tx_req to cpuss.dw1_tr_in[24] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA14 = 0x40001209u, /* From scb[4].tr_rx_req to cpuss.dw1_tr_in[25] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA15 = 0x4000120Au, /* From scb[5].tr_tx_req to cpuss.dw1_tr_in[26] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA15 = 0x4000120Bu, /* From scb[5].tr_rx_req to cpuss.dw1_tr_in[27] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA16 = 0x4000120Cu, /* From scb[6].tr_tx_req to cpuss.dw1_tr_in[28] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA16 = 0x4000120Du, /* From scb[6].tr_rx_req to cpuss.dw1_tr_in[29] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA17 = 0x4000120Eu, /* From scb[7].tr_tx_req to cpuss.dw1_tr_in[30] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA17 = 0x4000120Fu, /* From scb[7].tr_rx_req to cpuss.dw1_tr_in[31] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA18 = 0x40001210u, /* From scb[8].tr_tx_req to cpuss.dw1_tr_in[32] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA18 = 0x40001211u, /* From scb[8].tr_rx_req to cpuss.dw1_tr_in[33] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA19 = 0x40001212u, /* From scb[9].tr_tx_req to cpuss.dw1_tr_in[34] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA19 = 0x40001213u, /* From scb[9].tr_rx_req to cpuss.dw1_tr_in[35] */
    TRIG_OUT_1TO1_2_SCB_TX_TO_PDMA110 = 0x40001214u, /* From scb[10].tr_tx_req to cpuss.dw1_tr_in[36] */
    TRIG_OUT_1TO1_2_SCB_RX_TO_PDMA110 = 0x40001215u /* From scb[10].tr_rx_req to cpuss.dw1_tr_in[37] */
} en_trig_output_1to1_scb_dw1_tr_t;

/* Trigger Output Group 3 - SMIF DW Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_3_SMIF_TX_TO_PDMA1 = 0x40001300u, /* From smif[0].tr_tx_req to cpuss.dw1_tr_in[50] */
    TRIG_OUT_1TO1_3_SMIF_RX_TO_PDMA1 = 0x40001301u /* From smif[0].tr_rx_req to cpuss.dw1_tr_in[51] */
} en_trig_output_1to1_smif_dw1_tr_t;

/* Trigger Output Group 4 - More CAN DW triggers (on DW1 for max BW) (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_4_CAN1_DBG_TO_PDMA1_0 = 0x40001400u, /* From canfd[1].tr_dbg_dma_req[0] to cpuss.dw1_tr_in[38] */
    TRIG_OUT_1TO1_4_CAN1_FIFO0_TO_PDMA1_0 = 0x40001401u, /* From canfd[1].tr_fifo0[0] to cpuss.dw1_tr_in[39] */
    TRIG_OUT_1TO1_4_CAN1_FIFO1_TO_PDMA1_0 = 0x40001402u, /* From canfd[1].tr_fifo1[0] to cpuss.dw1_tr_in[40] */
    TRIG_OUT_1TO1_4_CAN1_DBG_TO_PDMA1_1 = 0x40001403u, /* From canfd[1].tr_dbg_dma_req[1] to cpuss.dw1_tr_in[41] */
    TRIG_OUT_1TO1_4_CAN1_FIFO0_TO_PDMA1_1 = 0x40001404u, /* From canfd[1].tr_fifo0[1] to cpuss.dw1_tr_in[42] */
    TRIG_OUT_1TO1_4_CAN1_FIFO1_TO_PDMA1_1 = 0x40001405u, /* From canfd[1].tr_fifo1[1] to cpuss.dw1_tr_in[43] */
    TRIG_OUT_1TO1_4_CAN1_DBG_TO_PDMA1_2 = 0x40001406u, /* From canfd[1].tr_dbg_dma_req[2] to cpuss.dw1_tr_in[44] */
    TRIG_OUT_1TO1_4_CAN1_FIFO0_TO_PDMA1_2 = 0x40001407u, /* From canfd[1].tr_fifo0[2] to cpuss.dw1_tr_in[45] */
    TRIG_OUT_1TO1_4_CAN1_FIFO1_TO_PDMA1_2 = 0x40001408u, /* From canfd[1].tr_fifo1[2] to cpuss.dw1_tr_in[46] */
    TRIG_OUT_1TO1_4_CAN1_DBG_TO_PDMA1_3 = 0x40001409u, /* From canfd[1].tr_dbg_dma_req[3] to cpuss.dw1_tr_in[47] */
    TRIG_OUT_1TO1_4_CAN1_FIFO0_TO_PDMA1_3 = 0x4000140Au, /* From canfd[1].tr_fifo0[3] to cpuss.dw1_tr_in[48] */
    TRIG_OUT_1TO1_4_CAN1_FIFO1_TO_PDMA1_3 = 0x4000140Bu /* From canfd[1].tr_fifo1[3] to cpuss.dw1_tr_in[49] */
} en_trig_output_1to1_can1_dw1_tr_t;

/* Trigger Output Group 5 - I2S DW Triggers (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_5_I2S_TX_TO_PDMA10 = 0x40001500u, /* From audioss[0].tr_i2s_tx_req to cpuss.dw1_tr_in[52] */
    TRIG_OUT_1TO1_5_I2S_RX_TO_PDMA10 = 0x40001501u, /* From audioss[0].tr_i2s_rx_req to cpuss.dw1_tr_in[53] */
    TRIG_OUT_1TO1_5_I2S_TX_TO_PDMA11 = 0x40001502u, /* From audioss[1].tr_i2s_tx_req to cpuss.dw1_tr_in[54] */
    TRIG_OUT_1TO1_5_I2S_RX_TO_PDMA11 = 0x40001503u, /* From audioss[1].tr_i2s_rx_req to cpuss.dw1_tr_in[55] */
    TRIG_OUT_1TO1_5_I2S_TX_TO_PDMA12 = 0x40001504u, /* From audioss[2].tr_i2s_tx_req to cpuss.dw1_tr_in[56] */
    TRIG_OUT_1TO1_5_I2S_RX_TO_PDMA12 = 0x40001505u /* From audioss[2].tr_i2s_rx_req to cpuss.dw1_tr_in[57] */
} en_trig_output_1to1_i2s_dw1_tr_t;

/* Trigger Output Group 6 - PASS to PWM direct connect (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL0 = 0x40001600u, /* From pass[0].tr_sar_ch_rangevio[0] to tcpwm[0].tr_one_cnt_in[770] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL1 = 0x40001601u, /* From pass[0].tr_sar_ch_rangevio[1] to tcpwm[0].tr_one_cnt_in[779] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL2 = 0x40001602u, /* From pass[0].tr_sar_ch_rangevio[2] to tcpwm[0].tr_one_cnt_in[788] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL3 = 0x40001603u, /* From pass[0].tr_sar_ch_rangevio[3] to tcpwm[0].tr_one_cnt_in[797] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL4 = 0x40001604u, /* From pass[0].tr_sar_ch_rangevio[4] to tcpwm[0].tr_one_cnt_in[2] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL5 = 0x40001605u, /* From pass[0].tr_sar_ch_rangevio[5] to tcpwm[0].tr_one_cnt_in[5] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL6 = 0x40001606u, /* From pass[0].tr_sar_ch_rangevio[6] to tcpwm[0].tr_one_cnt_in[8] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL7 = 0x40001607u, /* From pass[0].tr_sar_ch_rangevio[7] to tcpwm[0].tr_one_cnt_in[11] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL8 = 0x40001608u, /* From pass[0].tr_sar_ch_rangevio[8] to tcpwm[0].tr_one_cnt_in[14] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL9 = 0x40001609u, /* From pass[0].tr_sar_ch_rangevio[9] to tcpwm[0].tr_one_cnt_in[17] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL10 = 0x4000160Au, /* From pass[0].tr_sar_ch_rangevio[10] to tcpwm[0].tr_one_cnt_in[20] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL11 = 0x4000160Bu, /* From pass[0].tr_sar_ch_rangevio[11] to tcpwm[0].tr_one_cnt_in[23] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL12 = 0x4000160Cu, /* From pass[0].tr_sar_ch_rangevio[12] to tcpwm[0].tr_one_cnt_in[26] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL13 = 0x4000160Du, /* From pass[0].tr_sar_ch_rangevio[13] to tcpwm[0].tr_one_cnt_in[29] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL14 = 0x4000160Eu, /* From pass[0].tr_sar_ch_rangevio[14] to tcpwm[0].tr_one_cnt_in[32] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL15 = 0x4000160Fu, /* From pass[0].tr_sar_ch_rangevio[15] to tcpwm[0].tr_one_cnt_in[35] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL16 = 0x40001610u, /* From pass[0].tr_sar_ch_rangevio[16] to tcpwm[0].tr_one_cnt_in[38] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL17 = 0x40001611u, /* From pass[0].tr_sar_ch_rangevio[17] to tcpwm[0].tr_one_cnt_in[41] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL18 = 0x40001612u, /* From pass[0].tr_sar_ch_rangevio[18] to tcpwm[0].tr_one_cnt_in[44] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL19 = 0x40001613u, /* From pass[0].tr_sar_ch_rangevio[19] to tcpwm[0].tr_one_cnt_in[47] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL20 = 0x40001614u, /* From pass[0].tr_sar_ch_rangevio[20] to tcpwm[0].tr_one_cnt_in[50] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL21 = 0x40001615u, /* From pass[0].tr_sar_ch_rangevio[21] to tcpwm[0].tr_one_cnt_in[53] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL22 = 0x40001616u, /* From pass[0].tr_sar_ch_rangevio[22] to tcpwm[0].tr_one_cnt_in[56] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL23 = 0x40001617u, /* From pass[0].tr_sar_ch_rangevio[23] to tcpwm[0].tr_one_cnt_in[59] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL24 = 0x40001618u, /* From pass[0].tr_sar_ch_rangevio[24] to tcpwm[0].tr_one_cnt_in[62] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL25 = 0x40001619u, /* From pass[0].tr_sar_ch_rangevio[25] to tcpwm[0].tr_one_cnt_in[65] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL26 = 0x4000161Au, /* From pass[0].tr_sar_ch_rangevio[26] to tcpwm[0].tr_one_cnt_in[68] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL27 = 0x4000161Bu, /* From pass[0].tr_sar_ch_rangevio[27] to tcpwm[0].tr_one_cnt_in[71] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL28 = 0x4000161Cu, /* From pass[0].tr_sar_ch_rangevio[28] to tcpwm[0].tr_one_cnt_in[74] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL29 = 0x4000161Du, /* From pass[0].tr_sar_ch_rangevio[29] to tcpwm[0].tr_one_cnt_in[77] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL30 = 0x4000161Eu, /* From pass[0].tr_sar_ch_rangevio[30] to tcpwm[0].tr_one_cnt_in[80] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL31 = 0x4000161Fu, /* From pass[0].tr_sar_ch_rangevio[31] to tcpwm[0].tr_one_cnt_in[83] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL32 = 0x40001620u, /* From pass[0].tr_sar_ch_rangevio[32] to tcpwm[0].tr_one_cnt_in[773] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL33 = 0x40001621u, /* From pass[0].tr_sar_ch_rangevio[33] to tcpwm[0].tr_one_cnt_in[782] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL34 = 0x40001622u, /* From pass[0].tr_sar_ch_rangevio[34] to tcpwm[0].tr_one_cnt_in[791] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL35 = 0x40001623u, /* From pass[0].tr_sar_ch_rangevio[35] to tcpwm[0].tr_one_cnt_in[800] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL36 = 0x40001624u, /* From pass[0].tr_sar_ch_rangevio[36] to tcpwm[0].tr_one_cnt_in[86] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL37 = 0x40001625u, /* From pass[0].tr_sar_ch_rangevio[37] to tcpwm[0].tr_one_cnt_in[89] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL38 = 0x40001626u, /* From pass[0].tr_sar_ch_rangevio[38] to tcpwm[0].tr_one_cnt_in[92] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL39 = 0x40001627u, /* From pass[0].tr_sar_ch_rangevio[39] to tcpwm[0].tr_one_cnt_in[95] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL40 = 0x40001628u, /* From pass[0].tr_sar_ch_rangevio[40] to tcpwm[0].tr_one_cnt_in[98] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL41 = 0x40001629u, /* From pass[0].tr_sar_ch_rangevio[41] to tcpwm[0].tr_one_cnt_in[101] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL42 = 0x4000162Au, /* From pass[0].tr_sar_ch_rangevio[42] to tcpwm[0].tr_one_cnt_in[104] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL43 = 0x4000162Bu, /* From pass[0].tr_sar_ch_rangevio[43] to tcpwm[0].tr_one_cnt_in[107] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL44 = 0x4000162Cu, /* From pass[0].tr_sar_ch_rangevio[44] to tcpwm[0].tr_one_cnt_in[110] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL45 = 0x4000162Du, /* From pass[0].tr_sar_ch_rangevio[45] to tcpwm[0].tr_one_cnt_in[113] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL46 = 0x4000162Eu, /* From pass[0].tr_sar_ch_rangevio[46] to tcpwm[0].tr_one_cnt_in[116] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL47 = 0x4000162Fu, /* From pass[0].tr_sar_ch_rangevio[47] to tcpwm[0].tr_one_cnt_in[119] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL48 = 0x40001630u, /* From pass[0].tr_sar_ch_rangevio[48] to tcpwm[0].tr_one_cnt_in[122] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL49 = 0x40001631u, /* From pass[0].tr_sar_ch_rangevio[49] to tcpwm[0].tr_one_cnt_in[125] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL50 = 0x40001632u, /* From pass[0].tr_sar_ch_rangevio[50] to tcpwm[0].tr_one_cnt_in[128] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL51 = 0x40001633u, /* From pass[0].tr_sar_ch_rangevio[51] to tcpwm[0].tr_one_cnt_in[131] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL52 = 0x40001634u, /* From pass[0].tr_sar_ch_rangevio[52] to tcpwm[0].tr_one_cnt_in[134] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL53 = 0x40001635u, /* From pass[0].tr_sar_ch_rangevio[53] to tcpwm[0].tr_one_cnt_in[137] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL54 = 0x40001636u, /* From pass[0].tr_sar_ch_rangevio[54] to tcpwm[0].tr_one_cnt_in[140] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL55 = 0x40001637u, /* From pass[0].tr_sar_ch_rangevio[55] to tcpwm[0].tr_one_cnt_in[143] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL56 = 0x40001638u, /* From pass[0].tr_sar_ch_rangevio[56] to tcpwm[0].tr_one_cnt_in[146] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL57 = 0x40001639u, /* From pass[0].tr_sar_ch_rangevio[57] to tcpwm[0].tr_one_cnt_in[149] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL58 = 0x4000163Au, /* From pass[0].tr_sar_ch_rangevio[58] to tcpwm[0].tr_one_cnt_in[152] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL59 = 0x4000163Bu, /* From pass[0].tr_sar_ch_rangevio[59] to tcpwm[0].tr_one_cnt_in[155] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL60 = 0x4000163Cu, /* From pass[0].tr_sar_ch_rangevio[60] to tcpwm[0].tr_one_cnt_in[158] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL61 = 0x4000163Du, /* From pass[0].tr_sar_ch_rangevio[61] to tcpwm[0].tr_one_cnt_in[161] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL62 = 0x4000163Eu, /* From pass[0].tr_sar_ch_rangevio[62] to tcpwm[0].tr_one_cnt_in[164] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL63 = 0x4000163Fu, /* From pass[0].tr_sar_ch_rangevio[63] to tcpwm[0].tr_one_cnt_in[167] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL64 = 0x40001640u, /* From pass[0].tr_sar_ch_rangevio[64] to tcpwm[0].tr_one_cnt_in[776] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL65 = 0x40001641u, /* From pass[0].tr_sar_ch_rangevio[65] to tcpwm[0].tr_one_cnt_in[785] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL66 = 0x40001642u, /* From pass[0].tr_sar_ch_rangevio[66] to tcpwm[0].tr_one_cnt_in[794] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL67 = 0x40001643u, /* From pass[0].tr_sar_ch_rangevio[67] to tcpwm[0].tr_one_cnt_in[803] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL68 = 0x40001644u, /* From pass[0].tr_sar_ch_rangevio[68] to tcpwm[0].tr_one_cnt_in[170] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL69 = 0x40001645u, /* From pass[0].tr_sar_ch_rangevio[69] to tcpwm[0].tr_one_cnt_in[173] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL70 = 0x40001646u, /* From pass[0].tr_sar_ch_rangevio[70] to tcpwm[0].tr_one_cnt_in[176] */
    TRIG_OUT_1TO1_6_PASS_CH_RANGEVIO_TO_PWM_KILL71 = 0x40001647u /* From pass[0].tr_sar_ch_rangevio[71] to tcpwm[0].tr_one_cnt_in[179] */
} en_trig_output_1to1_pass_to_pwm_t;

/* Trigger Output Group 7 -  (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR0 = 0x40001700u, /* From tcpwm[0].tr_out1[256] to pass[0].tr_sar_ch_in[0] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR1 = 0x40001701u, /* From tcpwm[0].tr_out1[259] to pass[0].tr_sar_ch_in[1] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR2 = 0x40001702u, /* From tcpwm[0].tr_out1[262] to pass[0].tr_sar_ch_in[2] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR3 = 0x40001703u, /* From tcpwm[0].tr_out1[265] to pass[0].tr_sar_ch_in[3] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR4 = 0x40001704u, /* From tcpwm[0].tr_out1[0] to pass[0].tr_sar_ch_in[4] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR5 = 0x40001705u, /* From tcpwm[0].tr_out1[1] to pass[0].tr_sar_ch_in[5] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR6 = 0x40001706u, /* From tcpwm[0].tr_out1[2] to pass[0].tr_sar_ch_in[6] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR7 = 0x40001707u, /* From tcpwm[0].tr_out1[3] to pass[0].tr_sar_ch_in[7] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR8 = 0x40001708u, /* From tcpwm[0].tr_out1[4] to pass[0].tr_sar_ch_in[8] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR9 = 0x40001709u, /* From tcpwm[0].tr_out1[5] to pass[0].tr_sar_ch_in[9] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR10 = 0x4000170Au, /* From tcpwm[0].tr_out1[6] to pass[0].tr_sar_ch_in[10] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR11 = 0x4000170Bu, /* From tcpwm[0].tr_out1[7] to pass[0].tr_sar_ch_in[11] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR12 = 0x4000170Cu, /* From tcpwm[0].tr_out1[8] to pass[0].tr_sar_ch_in[12] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR13 = 0x4000170Du, /* From tcpwm[0].tr_out1[9] to pass[0].tr_sar_ch_in[13] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR14 = 0x4000170Eu, /* From tcpwm[0].tr_out1[10] to pass[0].tr_sar_ch_in[14] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR15 = 0x4000170Fu, /* From tcpwm[0].tr_out1[11] to pass[0].tr_sar_ch_in[15] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR16 = 0x40001710u, /* From tcpwm[0].tr_out1[12] to pass[0].tr_sar_ch_in[16] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR17 = 0x40001711u, /* From tcpwm[0].tr_out1[13] to pass[0].tr_sar_ch_in[17] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR18 = 0x40001712u, /* From tcpwm[0].tr_out1[14] to pass[0].tr_sar_ch_in[18] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR19 = 0x40001713u, /* From tcpwm[0].tr_out1[15] to pass[0].tr_sar_ch_in[19] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR20 = 0x40001714u, /* From tcpwm[0].tr_out1[16] to pass[0].tr_sar_ch_in[20] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR21 = 0x40001715u, /* From tcpwm[0].tr_out1[17] to pass[0].tr_sar_ch_in[21] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR22 = 0x40001716u, /* From tcpwm[0].tr_out1[18] to pass[0].tr_sar_ch_in[22] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR23 = 0x40001717u, /* From tcpwm[0].tr_out1[19] to pass[0].tr_sar_ch_in[23] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR24 = 0x40001718u, /* From tcpwm[0].tr_out1[20] to pass[0].tr_sar_ch_in[24] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR25 = 0x40001719u, /* From tcpwm[0].tr_out1[21] to pass[0].tr_sar_ch_in[25] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR26 = 0x4000171Au, /* From tcpwm[0].tr_out1[22] to pass[0].tr_sar_ch_in[26] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR27 = 0x4000171Bu, /* From tcpwm[0].tr_out1[23] to pass[0].tr_sar_ch_in[27] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR28 = 0x4000171Cu, /* From tcpwm[0].tr_out1[24] to pass[0].tr_sar_ch_in[28] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR29 = 0x4000171Du, /* From tcpwm[0].tr_out1[25] to pass[0].tr_sar_ch_in[29] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR30 = 0x4000171Eu, /* From tcpwm[0].tr_out1[26] to pass[0].tr_sar_ch_in[30] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR31 = 0x4000171Fu, /* From tcpwm[0].tr_out1[27] to pass[0].tr_sar_ch_in[31] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR32 = 0x40001720u, /* From tcpwm[0].tr_out1[257] to pass[0].tr_sar_ch_in[32] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR33 = 0x40001721u, /* From tcpwm[0].tr_out1[260] to pass[0].tr_sar_ch_in[33] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR34 = 0x40001722u, /* From tcpwm[0].tr_out1[263] to pass[0].tr_sar_ch_in[34] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR35 = 0x40001723u, /* From tcpwm[0].tr_out1[266] to pass[0].tr_sar_ch_in[35] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR36 = 0x40001724u, /* From tcpwm[0].tr_out1[28] to pass[0].tr_sar_ch_in[36] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR37 = 0x40001725u, /* From tcpwm[0].tr_out1[29] to pass[0].tr_sar_ch_in[37] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR38 = 0x40001726u, /* From tcpwm[0].tr_out1[30] to pass[0].tr_sar_ch_in[38] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR39 = 0x40001727u, /* From tcpwm[0].tr_out1[31] to pass[0].tr_sar_ch_in[39] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR40 = 0x40001728u, /* From tcpwm[0].tr_out1[32] to pass[0].tr_sar_ch_in[40] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR41 = 0x40001729u, /* From tcpwm[0].tr_out1[33] to pass[0].tr_sar_ch_in[41] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR42 = 0x4000172Au, /* From tcpwm[0].tr_out1[34] to pass[0].tr_sar_ch_in[42] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR43 = 0x4000172Bu, /* From tcpwm[0].tr_out1[35] to pass[0].tr_sar_ch_in[43] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR44 = 0x4000172Cu, /* From tcpwm[0].tr_out1[36] to pass[0].tr_sar_ch_in[44] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR45 = 0x4000172Du, /* From tcpwm[0].tr_out1[37] to pass[0].tr_sar_ch_in[45] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR46 = 0x4000172Eu, /* From tcpwm[0].tr_out1[38] to pass[0].tr_sar_ch_in[46] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR47 = 0x4000172Fu, /* From tcpwm[0].tr_out1[39] to pass[0].tr_sar_ch_in[47] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR48 = 0x40001730u, /* From tcpwm[0].tr_out1[40] to pass[0].tr_sar_ch_in[48] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR49 = 0x40001731u, /* From tcpwm[0].tr_out1[41] to pass[0].tr_sar_ch_in[49] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR50 = 0x40001732u, /* From tcpwm[0].tr_out1[42] to pass[0].tr_sar_ch_in[50] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR51 = 0x40001733u, /* From tcpwm[0].tr_out1[43] to pass[0].tr_sar_ch_in[51] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR52 = 0x40001734u, /* From tcpwm[0].tr_out1[44] to pass[0].tr_sar_ch_in[52] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR53 = 0x40001735u, /* From tcpwm[0].tr_out1[45] to pass[0].tr_sar_ch_in[53] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR54 = 0x40001736u, /* From tcpwm[0].tr_out1[46] to pass[0].tr_sar_ch_in[54] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR55 = 0x40001737u, /* From tcpwm[0].tr_out1[47] to pass[0].tr_sar_ch_in[55] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR56 = 0x40001738u, /* From tcpwm[0].tr_out1[48] to pass[0].tr_sar_ch_in[56] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR57 = 0x40001739u, /* From tcpwm[0].tr_out1[49] to pass[0].tr_sar_ch_in[57] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR58 = 0x4000173Au, /* From tcpwm[0].tr_out1[50] to pass[0].tr_sar_ch_in[58] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR59 = 0x4000173Bu, /* From tcpwm[0].tr_out1[51] to pass[0].tr_sar_ch_in[59] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR60 = 0x4000173Cu, /* From tcpwm[0].tr_out1[52] to pass[0].tr_sar_ch_in[60] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR61 = 0x4000173Du, /* From tcpwm[0].tr_out1[53] to pass[0].tr_sar_ch_in[61] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR62 = 0x4000173Eu, /* From tcpwm[0].tr_out1[54] to pass[0].tr_sar_ch_in[62] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR63 = 0x4000173Fu, /* From tcpwm[0].tr_out1[55] to pass[0].tr_sar_ch_in[63] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR64 = 0x40001740u, /* From tcpwm[0].tr_out1[258] to pass[0].tr_sar_ch_in[64] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR65 = 0x40001741u, /* From tcpwm[0].tr_out1[261] to pass[0].tr_sar_ch_in[65] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR66 = 0x40001742u, /* From tcpwm[0].tr_out1[264] to pass[0].tr_sar_ch_in[66] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR67 = 0x40001743u, /* From tcpwm[0].tr_out1[267] to pass[0].tr_sar_ch_in[67] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR68 = 0x40001744u, /* From tcpwm[0].tr_out1[56] to pass[0].tr_sar_ch_in[68] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR69 = 0x40001745u, /* From tcpwm[0].tr_out1[57] to pass[0].tr_sar_ch_in[69] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR70 = 0x40001746u, /* From tcpwm[0].tr_out1[58] to pass[0].tr_sar_ch_in[70] */
    TRIG_OUT_1TO1_7_TCPWM_TO_PASS_CH_TR71 = 0x40001747u /* From tcpwm[0].tr_out1[59] to pass[0].tr_sar_ch_in[71] */
} en_trig_output_1to1_pwm_to_pass_t;

/* Trigger Output Group 8 - Acknowledge triggers from DW1 to CAN (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_8_PDMA1_ACK_TO_CAN1_0 = 0x40001800u, /* From cpuss.dw1_tr_out[38] to canfd[1].tr_dbg_dma_ack[0] */
    TRIG_OUT_1TO1_8_PDMA1_ACK_TO_CAN1_1 = 0x40001801u, /* From cpuss.dw1_tr_out[41] to canfd[1].tr_dbg_dma_ack[1] */
    TRIG_OUT_1TO1_8_PDMA1_ACK_TO_CAN1_2 = 0x40001802u, /* From cpuss.dw1_tr_out[44] to canfd[1].tr_dbg_dma_ack[2] */
    TRIG_OUT_1TO1_8_PDMA1_ACK_TO_CAN1_3 = 0x40001803u /* From cpuss.dw1_tr_out[47] to canfd[1].tr_dbg_dma_ack[3] */
} en_trig_output_1to1_can1_dw1_ack_t;

/* Trigger Output Group 9 - Acknowledge triggers from DW0 to CAN (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_9_PDMA0_ACK_TO_CAN0_0 = 0x40001900u, /* From cpuss.dw0_tr_out[16] to canfd[0].tr_dbg_dma_ack[0] */
    TRIG_OUT_1TO1_9_PDMA0_ACK_TO_CAN0_1 = 0x40001901u, /* From cpuss.dw0_tr_out[19] to canfd[0].tr_dbg_dma_ack[1] */
    TRIG_OUT_1TO1_9_PDMA0_ACK_TO_CAN0_2 = 0x40001902u, /* From cpuss.dw0_tr_out[22] to canfd[0].tr_dbg_dma_ack[2] */
    TRIG_OUT_1TO1_9_PDMA0_ACK_TO_CAN0_3 = 0x40001903u /* From cpuss.dw0_tr_out[25] to canfd[0].tr_dbg_dma_ack[3] */
} en_trig_output_1to1_can0_dw0_ack_t;

/* Trigger Output Group 10 -  (OneToOne) */
typedef enum
{
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR0 = 0x40001A00u, /* From tcpwm[0].tr_out0[0] to lin[0].tr_cmd_tx_header[0] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR1 = 0x40001A01u, /* From tcpwm[0].tr_out0[1] to lin[0].tr_cmd_tx_header[1] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR2 = 0x40001A02u, /* From tcpwm[0].tr_out0[2] to lin[0].tr_cmd_tx_header[2] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR3 = 0x40001A03u, /* From tcpwm[0].tr_out0[3] to lin[0].tr_cmd_tx_header[3] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR4 = 0x40001A04u, /* From tcpwm[0].tr_out0[4] to lin[0].tr_cmd_tx_header[4] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR5 = 0x40001A05u, /* From tcpwm[0].tr_out0[5] to lin[0].tr_cmd_tx_header[5] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR6 = 0x40001A06u, /* From tcpwm[0].tr_out0[6] to lin[0].tr_cmd_tx_header[6] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR7 = 0x40001A07u, /* From tcpwm[0].tr_out0[7] to lin[0].tr_cmd_tx_header[7] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR8 = 0x40001A08u, /* From tcpwm[0].tr_out0[8] to lin[0].tr_cmd_tx_header[8] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR9 = 0x40001A09u, /* From tcpwm[0].tr_out0[9] to lin[0].tr_cmd_tx_header[9] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR10 = 0x40001A0Au, /* From tcpwm[0].tr_out0[10] to lin[0].tr_cmd_tx_header[10] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR11 = 0x40001A0Bu, /* From tcpwm[0].tr_out0[11] to lin[0].tr_cmd_tx_header[11] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR12 = 0x40001A0Cu, /* From tcpwm[0].tr_out0[12] to lin[0].tr_cmd_tx_header[12] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR13 = 0x40001A0Du, /* From tcpwm[0].tr_out0[13] to lin[0].tr_cmd_tx_header[13] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR14 = 0x40001A0Eu, /* From tcpwm[0].tr_out0[14] to lin[0].tr_cmd_tx_header[14] */
    TRIG_OUT_1TO1_10_TCPWM_TO_LIN_TR15 = 0x40001A0Fu /* From tcpwm[0].tr_out0[15] to lin[0].tr_cmd_tx_header[15] */
} en_trig_output_1to1_tcpwm_to_lin_t;

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
/* AUDIOSS Trigger Types */
#define TRIGGER_TYPE_AUDIOSS_TR_I2S_RX_REQ      TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_AUDIOSS_TR_I2S_TX_REQ      TRIGGER_TYPE_LEVEL
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
/* LIN Trigger Types */
#define TRIGGER_TYPE_LIN_TR_CMD_TX_HEADER       TRIGGER_TYPE_EDGE
/* PASS Trigger Types */
#define TRIGGER_TYPE_PASS_TR_DEBUG_FREEZE       TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_CH_DONE__LEVEL TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_CH_DONE__EDGE  TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PASS_TR_SAR_CH_IN__LEVEL   TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_CH_IN__EDGE    TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PASS_TR_SAR_CH_RANGEVIO    TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PASS_TR_SAR_GEN_IN__LEVEL  TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_GEN_IN__EDGE   TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_PASS_TR_SAR_GEN_OUT__LEVEL TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_PASS_TR_SAR_GEN_OUT__EDGE  TRIGGER_TYPE_EDGE
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
#define TRIGGER_TYPE_SRSS_TR_DEBUG_FREEZE_WDT   TRIGGER_TYPE_LEVEL
/* TCPWM Trigger Types */
#define TRIGGER_TYPE_TCPWM_TR_DEBUG_FREEZE      TRIGGER_TYPE_LEVEL
/* TR_GROUP Trigger Types */
#define TRIGGER_TYPE_TR_GROUP_OUTPUT__LEVEL     TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TR_GROUP_OUTPUT__EDGE      TRIGGER_TYPE_EDGE
#define TRIGGER_TYPE_TR_GROUP_INPUT__LEVEL      TRIGGER_TYPE_LEVEL
#define TRIGGER_TYPE_TR_GROUP_INPUT__EDGE       TRIGGER_TYPE_EDGE

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
    CPUSS_MS_ID_FAST0               =  9,
    CPUSS_MS_ID_FAST1               = 10,
    CPUSS_MS_ID_FAST2               = 11,
    CPUSS_MS_ID_FAST3               = 12,
    CPUSS_MS_ID_CM7_1               = 13,
    CPUSS_MS_ID_CM7_0               = 14,
    CPUSS_MS_ID_TC                  = 15
} en_prot_master_t;

/* Include IP definitions */
#include "ip/cyip_sflash_v2.h"
#include "ip/cyip_peri_v3.h"
#include "ip/cyip_peri_ms_v3.h"
#include "ip/cyip_peri_pclk_v3.h"
#include "ip/cyip_crypto.h"
#include "ip/cyip_crypto_v2.h"
#include "ip/cyip_cpuss.h"
#include "ip/cyip_fault.h"
#include "ip/cyip_ipc.h"
#include "ip/cyip_prot.h"
#include "ip/cyip_flashc.h"
#include "ip/cyip_srss_v3.h"
#include "ip/cyip_backup_v3.h"
#include "ip/cyip_dw.h"
#include "ip/cyip_dmac.h"
#include "ip/cyip_efuse_v2.h"
#include "ip/cyip_efuse_data_v2_xmc7100.h"
#include "ip/cyip_hsiom_v3.h"
#include "ip/cyip_gpio_v3.h"
#include "ip/cyip_smartio_v3.h"
#include "ip/cyip_evtgen.h"
#include "ip/cyip_smif_v2.h"
#include "ip/cyip_sdhc.h"
#include "ip/cyip_eth_v2.h"
#include "ip/cyip_lin.h"
#include "ip/cyip_canfd.h"
#include "ip/cyip_tcpwm_v2.h"
#include "ip/cyip_scb_v2.h"
#include "ip/cyip_i2s_v2.h"
#include "ip/cyip_pass.h"

/* IP type definitions */
typedef CRYPTO_V2_Type CRYPTO_Type;

/* Parameter Defines */
/* I2S capable? (0=No,1=Yes) */
#define AUDIOSS0_I2S_I2S                1u
/* I2S instantiates both RX and TX. 0=TX Only 1=RX Plus TX present */
#define AUDIOSS0_I2S_I2S_RX_TX          1u
/* PDM capable? (0=No,1=Yes) */
#define AUDIOSS0_PDM_PDM                0u
/* I2S capable? (0=No,1=Yes) */
#define AUDIOSS1_I2S_I2S                1u
/* I2S instantiates both RX and TX. 0=TX Only 1=RX Plus TX present */
#define AUDIOSS1_I2S_I2S_RX_TX          1u
/* PDM capable? (0=No,1=Yes) */
#define AUDIOSS1_PDM_PDM                0u
/* I2S capable? (0=No,1=Yes) */
#define AUDIOSS2_I2S_I2S                1u
/* I2S instantiates both RX and TX. 0=TX Only 1=RX Plus TX present */
#define AUDIOSS2_I2S_I2S_RX_TX          1u
/* PDM capable? (0=No,1=Yes) */
#define AUDIOSS2_PDM_PDM                0u
/* Number of TTCAN instances */
#define CANFD0_CAN_NR                   4u
/* ECC logic present or not */
#define CANFD0_ECC_PRESENT              1u
/* address included in ECC logic or not */
#define CANFD0_ECC_ADDR_PRESENT         1u
/* Time Stamp counter present or not (required for instance 0, otherwise not
   allowed) */
#define CANFD0_TS_PRESENT               1u
/* Message RAM size in KB */
#define CANFD0_MRAM_SIZE                32u
/* Message RAM address width */
#define CANFD0_MRAM_ADDR_WIDTH          13u
/* Number of TTCAN instances */
#define CANFD1_CAN_NR                   4u
/* ECC logic present or not */
#define CANFD1_ECC_PRESENT              1u
/* address included in ECC logic or not */
#define CANFD1_ECC_ADDR_PRESENT         1u
/* Time Stamp counter present or not (required for instance 0, otherwise not
   allowed) */
#define CANFD1_TS_PRESENT               0u
/* Message RAM size in KB */
#define CANFD1_MRAM_SIZE                32u
/* Message RAM address width */
#define CANFD1_MRAM_ADDR_WIDTH          13u
/* UDB present or not ('0': no, '1': yes) */
#define CPUSS_UDB_PRESENT               0u
/* MBIST MMIO for Synopsys MBIST ('0': no, '1': yes). Set this to '1' only for the
   chips which doesn't use mxdft. */
#define CPUSS_MBIST_MMIO_PRESENT        0u
/* System RAM 0 size in KB */
#define CPUSS_SRAM0_SIZE                512u
/* Number of macros used to implement system RAM 0. Example: 8 if 256 KB system
   SRAM 0 is implemented with 8 32KB macros. */
#define CPUSS_RAMC0_MACRO_NR            16u
/* System RAM 1 present or not ('0': no, '1': yes) */
#define CPUSS_RAMC1_PRESENT             1u
/* System RAM 1 size in KB */
#define CPUSS_SRAM1_SIZE                256u
/* Number of macros used to implement system RAM 1. */
#define CPUSS_RAMC1_MACRO_NR            8u
/* System RAM 2 present or not ('0': no, '1': yes) */
#define CPUSS_RAMC2_PRESENT             0u
/* System RAM 2 size in KB */
#define CPUSS_SRAM2_SIZE                256u
/* Number of macros used to implement System RAM 2. */
#define CPUSS_RAMC2_MACRO_NR            8u
/* System SRAM(s) ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_PRESENT          1u
/* System SRAM(s) address ECC present or not ('0': no, '1': yes) */
#define CPUSS_RAMC_ECC_ADDR_PRESENT     1u
/* ECC present in either system RAM or interrupt handler (RAMC_ECC_PRESENT) */
#define CPUSS_ECC_PRESENT               1u
/* DataWire SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_PRESENT            1u
/* DataWire SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_ADDR_PRESENT       1u
/* System ROM size in KB */
#define CPUSS_ROM_SIZE                  64u
/* Number of macros used to implement system ROM. Example: 4 if 512 KB system ROM
   is implemented with 4 128KB macros. */
#define CPUSS_ROMC_MACRO_NR             1u
/* Flash memory present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_PRESENT            1u
/* Flash memory type ('0' : SONOS, '1': ECT) */
#define CPUSS_FLASHC_ECT                1u
/* Flash main region size in KB */
#define CPUSS_FLASH_SIZE                4096u
/* Flash work region size in KB (EEPROM emulation, data) */
#define CPUSS_WFLASH_SIZE               256u
/* Flash supervisory region size in KB */
#define CPUSS_SFLASH_SIZE               32u
/* Flash data output word size (in Bits) Example: 256 for 256-bit Flash data
   output */
#define CPUSS_FLASHC_MAIN_DATA_WIDTH    256u
/* SONOS Flash RWW present or not ('0': no, '1': yes) When RWW is '0', No special
   sectors present in Flash. Part of main sector 0 is allowcated for Supervisory
   Flash, and no Work Flash present. */
#define CPUSS_FLASHC_SONOS_RWW          0u
/* SONOS Flash, number of main sectors. */
#define CPUSS_FLASHC_SONOS_MAIN_SECTORS 0u
/* SONOS Flash, number of rows per main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_ROWS    0u
/* SONOS Flash, number of words per row of main sector. */
#define CPUSS_FLASHC_SONOS_MAIN_WORDS   0u
/* SONOS Flash, number of special sectors. */
#define CPUSS_FLASHC_SONOS_SPL_SECTORS  0u
/* SONOS Flash, number of rows per special sector. */
#define CPUSS_FLASHC_SONOS_SPL_ROWS     0u
/* Flash memory ECC present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASH_ECC_PRESENT  1u
/* Flash cache SRAM(s) ECC present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_RAM_ECC_PRESENT    1u
/* Number of external AHB-Lite slaves directly connected to slow AHB-Lite
   infrastructure. Maximum nubmer of slave supported is 6. Width of this
   parameter is 6-bits. 1-bit mask for each slave indicating present or not.
   Example: 6'b00_0011 - slave 0 and slave 1 are present. Note: The
   SLOW_SLx_ADDR and SLOW_SLx_MASK parameters (for the slaves present) should be
   derived from the Memory Map. */
#define CPUSS_SLOW_SL_PRESENT           1u
/* Number of external AXI slaves directly connected to fast AXI infrastructure.
   Maximum nubmer of slave supported is 8. Width of this parameter is 8-bits.
   1-bit mask for each slave indicating present or not. Example: 8'b0000_0011 -
   slave 0 and slave 1 are present. Note: The FAST_SLx_ADDR and FAST_SLx_MASK
   parameters (for the slaves present) should be derived from the Memory Map. */
#define CPUSS_FAST_SL_PRESENT           1u
/* Number of external AHB-Lite masters driving the slow AHB-Lite infrastructure.
   Maximum number of masters supported is 2. Width of this parameter is 2-bits.
   1-bit mask for each master indicating present or not. Example: 2'b01 - master
   0 is present. */
#define CPUSS_SLOW_MS_PRESENT           3u
/* Number of external AXI masters driving the fast AXI infrastructure. Maximum
   number of masters supported is 4. Width of this parameter is 4-bits. 1-bit
   mask for each master indicating present or not. Example: 4'b0001 - master 0
   is present. */
#define CPUSS_FAST_MS_PRESENT           0u
/* Retain 'protection context' (PC), 'privileged' (P), 'Non Secure' (NS)
   attributes coming from external AXI master or use it from CPUSS protection
   MMIO (PROT_MPU.MS_CTL.PC, PROT_SMPU.MSx_CTL.P, PROT_SMPU.MSx_CTL.NS). Width
   of this parameter is 4-bits. 1-bit mask for each master indicating retain PC
   or not. */
#define CPUSS_AXIM_RETAIN_PROT          0u
/* Width of external AXI master ID signals. Legal range [3,8] */
#define CPUSS_AXIM_ID_WIDTH             3u
/* Width of external AXI slave ID signals (AXIM_ID_WIDTH + MASTER_WIDTH + 1).
   Legal range [12,17] */
#define CPUSS_AXIS_ID_WIDTH             12u
/* IRQ expander present ('0': no, '1': yes) */
#define CPUSS_SYSTEM_IRQ_PRESENT        1u
/* Number of system interrupt inputs to CPUSS */
#define CPUSS_SYSTEM_INT_NR             443u
/* Number of DeepSleep system interrupt inputs to CPUSS */
#define CPUSS_SYSTEM_DPSLP_INT_NR       51u
/* Width of the CM4 interrupt priority bits. Legal range [3,8] Example: 3 = 8
   levels of priority 8 = 256 levels of priority */
#define CPUSS_CM7_LVL_WIDTH             3u
/* Number of CM7 CPU Interrupts. Legal values 8 or 16. */
#define CPUSS_CM7_INT_NR                8u
/* CM7 Cache SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_CM7_CACHE_ECC_PRESENT     1u
/* CM7 TCM SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_CM7_TCM_ECC_PRESENT       1u
/* CM7 TCM SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_CM7_TCM_ECC_ADDR_PRESENT  0u
/* CM7_0 Floating point unit configuration. Legal range [0,2] 0 - No FPU 1 -
   Single precision FPU 2 - Single and Double precision FPU */
#define CPUSS_CM7_0_FPU_LVL             2u
/* Number of MPU regions in CM7_0. Legal values [0, 8, 16] */
#define CPUSS_CM7_0_MPU_NR              16u
/* CM7_0 Instruction cache (ICACHE) size in KB */
#define CPUSS_CM7_0_ICACHE_SIZE         16u
/* CM7_0 Data cache size (DCACHE) in KB */
#define CPUSS_CM7_0_DCACHE_SIZE         16u
/* CM7_0 Instruction TCM (ITCM) size in KB */
#define CPUSS_CM7_0_ITCM_SIZE           16u
/* CM7_0 Data TCM (DTCM) size in KB */
#define CPUSS_CM7_0_DTCM_SIZE           16u
/* CM7_1 CPU present or not ('0': no, '1': yes) */
#define CPUSS_CM7_1_PRESENT             1u
/* System interrupt functionality present or not ('0': no; '1': yes) for CM7_1.
   Not used for CM0+ CPU, which always uses system interrupt functionality. */
#define CPUSS_CM7_1_SYSTEM_IRQ_PRESENT  1u
/* CM7_1 Floating point unit configuration. Legal range [0,2] 0 - No FPU 1 -
   Single precision FPU 2 - Single and Double precision FPU */
#define CPUSS_CM7_1_FPU_LVL             2u
/* Number of MPU regions in CM7_1. Legal values [0, 8, 16] */
#define CPUSS_CM7_1_MPU_NR              16u
/* CM7_1 Instruction cache (ICACHE) size in KB */
#define CPUSS_CM7_1_ICACHE_SIZE         16u
/* CM7_1 Data cache size (DCACHE) in KB */
#define CPUSS_CM7_1_DCACHE_SIZE         16u
/* CM7_1 Instruction TCM (ITCM) size in KB */
#define CPUSS_CM7_1_ITCM_SIZE           16u
/* CM7_1 Data TCM (DTCM) size in KB */
#define CPUSS_CM7_1_DTCM_SIZE           16u
/* Debug level. Legal range [0,3] */
#define CPUSS_DEBUG_LVL                 3u
/* Trace level. Legal range [0,2] Note: CM4 HTM is not supported. Hence vaule 3
   for trace level is not supported in CPUSS. // CPUSS_TRACE_LVL: // 0 = no
   tracing // 1 = only ITM source and TPIU sink (no ETM, Funnel, Replicator or
   ETB) // 2 = ITM and ETM sources, Funnel and TPIU (no Replicator or ETB) // 3
   = ITM and ETM sources, Funnel, Replicator, TPIU and ET */
#define CPUSS_TRACE_LVL                 2u
/* Embedded Trace Buffer present or not ('0': no, '1': yes) */
#define CPUSS_ETB_PRESENT               1u
/* CM0+ MTB SRAM buffer size in kilobytes. Legal vaules 4, 8 or 16 */
#define CPUSS_MTB_SRAM_SIZE             4u
/* CM7 ETB SRAM buffer size in kilobytes. Legal vaules 4, 8 or 16 */
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
#define CPUSS_FAMILYID                  263u
/* ROM trim register width (for ARM 3, for Synopsys 5) */
#define CPUSS_ROM_TRIM_WIDTH            3u
/* ROM trim register default (for both ARM and Synopsys 0x0000_0002) */
#define CPUSS_ROM_TRIM_DEFAULT          2u
/* RAM trim register width (for ARM 8, for Synopsys 15) */
#define CPUSS_RAM_TRIM_WIDTH            8u
/* RAM trim register default (for ARM 0x0000_0062 and for Synopsys 0x0000_6012) */
#define CPUSS_RAM_TRIM_DEFAULT          98u
/* Cryptography IP present or not ('0': no, '1': yes) */
#define CPUSS_CRYPTO_PRESENT            1u
/* DataWire and DMAC SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_SW_TR_PRESENT             1u
/* DataWire 0 present or not ('0': no, '1': yes) */
#define CPUSS_DW0_PRESENT               1u
/* Number of DataWire 0 channels ([1, 1024]) */
#define CPUSS_DW0_CH_NR                 100u
/* DataWire 1 present or not ('0': no, '1': yes) */
#define CPUSS_DW1_PRESENT               1u
/* Number of DataWire 1 channels ([1, 1024]) */
#define CPUSS_DW1_CH_NR                 58u
/* DMA controller present or not ('0': no, '1': yes) */
#define CPUSS_DMAC_PRESENT              1u
/* Number of DMA controller channels ([1, 8]) */
#define CPUSS_DMAC_CH_NR                8u
/* DMAC SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_CH_SW_TR_PRESENT          1u
/* See MMIO2 instantiation or not */
#define CPUSS_CHIP_TOP_PROFILER_PRESENT 0u
/* ETAS Calibration support pin out present (automotive only) */
#define CPUSS_CHIP_TOP_CAL_SUP_NZ_PRESENT 1u
/* TRACE_LVL>0 */
#define CPUSS_CHIP_TOP_TRACE_PRESENT    1u
/* PTM_PRESENT ? PTM_WIDTH : 0 */
#define CPUSS_CHIP_TOP_PTM_PRESENT_WIDTH 0u
/* DataWire SW trigger per channel present or not ('0': no, '1': yes) */
#define CPUSS_CH_STRUCT_SW_TR_PRESENT   1u
/* Number of DataWire controllers present (max 2) (same as DW.NR above) */
#define CPUSS_CPUSS_DW_DW_NR            2u
/* Number of channels in each DataWire controller */
#define CPUSS_CPUSS_DW_DW_NR0_DW_CH_NR  100u
/* Width of a channel number in bits */
#define CPUSS_CPUSS_DW_DW_NR0_DW_CH_NR_WIDTH 7u
/* Number of channels in each DataWire controller */
#define CPUSS_CPUSS_DW_DW_NR1_DW_CH_NR  58u
/* Width of a channel number in bits */
#define CPUSS_CPUSS_DW_DW_NR1_DW_CH_NR_WIDTH 6u
/* Cryptography SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_CRYPTO_ECC_PRESENT        1u
/* Cryptography SRAMs address ECC present or not ('0': no, '1': yes) */
#define CPUSS_CRYPTO_ECC_ADDR_PRESENT   1u
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
#define CPUSS_CRYPTO_BUFF_SIZE          2048u
/* Number of DMA controller channels ([1, 8]) */
#define CPUSS_DMAC_CH_NR                8u
/* Number of DataWire controllers present (max 2) */
#define CPUSS_DW_NR                     2u
/* DataWire SRAMs ECC present or not ('0': no, '1': yes) */
#define CPUSS_DW_ECC_PRESENT            1u
/* Number of fault structures. Legal range [1, 4] */
#define CPUSS_FAULT_FAULT_NR            4u
/* Number of Flash BIST_DATA registers */
#define CPUSS_FLASHC_FLASHC_BIST_DATA_NR 8u
/* Page size in # of 32-bit words (1: 4 bytes, 2: 8 bytes, ... */
#define CPUSS_FLASHC_PA_SIZE            128u
/* SONOS Flash is used or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASHC_IS_SONOS    0u
/* eCT Flash is used or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_FLASHC_IS_ECT      1u
/* Sequential Work Flash read feature for the FLASHC AXI port present or not ('0':
   no, '1': yes) */
#define CPUSS_FLASHC_FLASHC_WORK_SEQ_PRESENT 1u
/* CM7_1 CPU present or not ('0': no, '1': yes) */
#define CPUSS_FLASHC_CM7_1_PRESENT      1u
/* External AHB-Lite master0 Present */
#define CPUSS_FLASHC_SLOW0_MS_PRESENT   1u
/* External AHB-Lite master1 Present */
#define CPUSS_FLASHC_SLOW1_MS_PRESENT   1u
/* Number of IPC structures. Legal range [1, 16] */
#define CPUSS_IPC_IPC_NR                8u
/* Number of IPC interrupt structures. Legal range [1, 16] */
#define CPUSS_IPC_IPC_IRQ_NR            8u
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
#define CPUSS_PROT_SMPU_MS6_PC_NR_MINUS1 7u
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
#define CPUSS_PROT_SMPU_MS13_PC_NR_MINUS1 7u
/* Master 14 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS14_PC_NR_MINUS1 7u
/* Master 15 protect contexts minus one */
#define CPUSS_PROT_SMPU_MS15_PC_NR_MINUS1 7u
/* Number of SMPU protection structures */
#define CPUSS_PROT_SMPU_STRUCT_NR       16u
/* Number of protection contexts supported minus 1. Legal range [1,16] */
#define CPUSS_SMPU_STRUCT_PC_NR_MINUS1  7u
/* Number of HFCLK roots present. Must be > 0. Must be same as set for SRSS */
#define DFT_NUM_HFROOT                  8u
/* Width of clk_occ_fast output bus (number of external OCCs) */
#define DFT_EXT_OCC                     2u
/* Number of MBIST controllers with corresponding mbist(pg)_done and mbist(pg)_go
   signals. Value defined by CIC during Pass 1 */
#define DFT_MBIST_C_NUM                 11u
/* Number of instantiated eFUSE macros (256 bit macros). Legal range [1, 16] */
#define EFUSE_EFUSE_NR                  4u
/* AXI Master present ([0,1]): 0 - AHB master interface is present 1 - AXI master
   interface is present. */
#define ETH_AXI_MASTER_PRESENT          0u
/* TX Packet Buffer Size (jumbo frame size is 1.5KB): 00: 16KB to support four
   queues with capacity for two jumbo frames; 01: 8KB to support two queues with
   capacity for two jumbo frames or four queues with capacity for one jumbo
   frame; 10: 4KB to support one queue with capacity for two jumbo frames or two
   queues with capacity for one jumbo frame; 11: 2KB to support one queue with
   capacity for one jumbo frame; */
#define ETH_TX_PACKET_BUFFER_SIZE       1u
/* RX Packet Buffer Size (jumbo frame size is 1.5KB): 00: 4KB to support capacity
   for two jumbo frames; 01: 2KB to support capacity for one jumbo frames; */
#define ETH_RX_PACKET_BUFFER_SIZE       0u
/* Selects the clock source to use for the tsu_clk. A value of 0=Internal PCLK, ,
   1=clk_hf */
#define ETH_TSU_CLK_SOURCE              1u
/* This parameter is used to specify if mxeth should contain a clock divider. The
   clock divider is useful for chips where multiple mxeth are instantiated as it
   allows a single source PLL to be used 0=No Divider, ref_clk_int_in is used as
   is 1=Divider instantiated, ref_clk_int_in should be 125MHz */
#define ETH_SRC_CLOCK_DIVIDER           1u
/* Set to 1 if IP will instantiate spares (0=None, 1=Max, 2=Min) */
#define ETH_SPARE_EN                    1u
/* Number of Priority Queues. */
#define ETH_ETH_NPQ                     3u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define ETH_MASTER_WIDTH                8u
/* Platform variant (0=ULL65, 1=MXS40S-ULP, 2=MXS40E, 3=M0S8, 4=MXS40S-HD) */
#define ETH_PLATFORM_VARIANT            2u
/* RAM vendor (0=CYP, 1=SNPS, 2=ARM) */
#define ETH_RAM_VEND                    2u
/* Width of external AXI master ID signals. Legal range [3,8] */
#define ETH_AXIM_ID_WIDTH               3u
/* RMII internal clock mode support */
#define ETH_CHIP_TOP_MXETH_RMII_INT_MODE_EN 0u
/* RGMII internal clock mode support */
#define ETH_CHIP_TOP_MXETH_RGMII_INT_MODE_EN 1u
/* Number of comparator structures ([1, 32]) */
#define EVTGEN_COMP_STRUCT_NR           16u
/* Number of GPIO ports in range 0..31 */
#define IOSS_GPIO_GPIO_PORT_NR_0_31     32u
/* Number of GPIO ports in range 32..63 */
#define IOSS_GPIO_GPIO_PORT_NR_32_63    1u
/* Number of GPIO ports in range 64..95 */
#define IOSS_GPIO_GPIO_PORT_NR_64_95    0u
/* Number of GPIO ports in range 96..127 */
#define IOSS_GPIO_GPIO_PORT_NR_96_127   0u
/* Number of GPIO ports in device */
#define IOSS_GPIO_GPIO_PORT_NR          33u
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
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR1_GPIO_PRT_AUTOLVL 1u
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
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR3_GPIO_PRT_AUTOLVL 1u
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
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR4_GPIO_PRT_AUTOLVL 1u
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
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR6_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR7_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR8_GPIO_PRT_SLOW_IO3 0u
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
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR9_GPIO_PRT_SLOW_IO3 0u
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
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR10_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR11_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR12_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR13_GPIO_PRT_AUTOLVL 1u
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
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR14_GPIO_PRT_SLOW_IO1 0u
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
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR15_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR16_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR17_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR18_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR19_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR20_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR21_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR22_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR23_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR24_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR25_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR26_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR27_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR28_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR29_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR30_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR31_GPIO_PRT_SLOW_IO7 0u
/* Indicates port is either GPIO or SIO (i.e. all GPIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_GPIO 1u
/* Indicates port is an SIO port (i.e. both GPIO and SIO registers present) */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SIO 0u
/* Indicates port is a GPIO port including the "AUTO" input threshold */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_AUTOLVL 1u
/* Indicates that pin #0 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO0 0u
/* Indicates that pin #1 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO1 0u
/* Indicates that pin #2 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO2 0u
/* Indicates that pin #3 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO3 0u
/* Indicates that pin #4 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO4 0u
/* Indicates that pin #5 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO5 0u
/* Indicates that pin #6 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO6 0u
/* Indicates that pin #7 exists for this port with slew control feature */
#define IOSS_GPIO_GPIO_PORT_NR32_GPIO_PRT_SLOW_IO7 0u
/* Number of AMUX splitter cells */
#define IOSS_HSIOM_AMUX_SPLIT_NR        3u
/* Number of HSIOM ports in device */
#define IOSS_HSIOM_HSIOM_PORT_NR        33u
/* Number of PWR/GND MONITOR CELLs in the device */
#define IOSS_HSIOM_MONITOR_NR           22u
/* Number of PWR/GND MONITOR CELLs in range 0..31 */
#define IOSS_HSIOM_MONITOR_NR_0_31      22u
/* Number of PWR/GND MONITOR CELLs in range 32..63 */
#define IOSS_HSIOM_MONITOR_NR_32_63     0u
/* Number of PWR/GND MONITOR CELLs in range 64..95 */
#define IOSS_HSIOM_MONITOR_NR_64_95     0u
/* Number of PWR/GND MONITOR CELLs in range 96..127 */
#define IOSS_HSIOM_MONITOR_NR_96_127    0u
/* Indicates the presence of alternate JTAG interface */
#define IOSS_HSIOM_ALTJTAG_PRESENT      1u
/* Mask of SMARTIO instances presence */
#define IOSS_SMARTIO_SMARTIO_MASK       192512u
/* Number of LIN channels ([2, 32]). For test functionality (two channels are
   connected), the minimal number of LIN channels is 2. */
#define LIN_CH_NR                       16u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define LIN_MASTER_WIDTH                8u
/* Platform variant (0=ULL65, 1=MXS40S-ULP, 2=MXS40E, 3=M0S8, 4=MXS40S-HD) */
#define LIN_CHIP_TOP_PLATFORM_VARIANT   2u
/* Number of SAR blocks */
#define PASS_SAR_ADC_NR                 3u
/* Number of ADC slices. Each slice will contain one SARMUX block and optionally a
   SAR and associated sequencer logic. */
#define PASS_SAR_SLICE_NR               3u
/* Number of SAR sequencer channels (per SAR) */
#define PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR 32u
/* Number of MUX inputs (per SAR), must be 8, 16, 24, or 32 */
#define PASS_SAR_SLICE_NR0_SAR_SAR_MUX_IN 32u
/* Is ADC is present on slice (1 = Yes, 0 = No). Calculated from SAR_ADC_NR such
   that lower numbered slices contain the ADCs that are present. */
#define PASS_SAR_SLICE_NR0_SAR_SAR_ADC_PRESENT 1u
/* Averaging logic present in SAR */
#define PASS_SAR_SLICE_NR0_SAR_SAR_AVERAGE 1u
/* Range detect logic present in SAR */
#define PASS_SAR_SLICE_NR0_SAR_SAR_RANGEDET 1u
/* Pulse detect logic present in SAR */
#define PASS_SAR_SLICE_NR0_SAR_SAR_PULSEDET 1u
/* Number of SAR sequencer channels (per SAR) */
#define PASS_SAR_SLICE_NR1_SAR_SAR_CHAN_NR 32u
/* Number of MUX inputs (per SAR), must be 8, 16, 24, or 32 */
#define PASS_SAR_SLICE_NR1_SAR_SAR_MUX_IN 32u
/* Is ADC is present on slice (1 = Yes, 0 = No). Calculated from SAR_ADC_NR such
   that lower numbered slices contain the ADCs that are present. */
#define PASS_SAR_SLICE_NR1_SAR_SAR_ADC_PRESENT 1u
/* Averaging logic present in SAR */
#define PASS_SAR_SLICE_NR1_SAR_SAR_AVERAGE 1u
/* Range detect logic present in SAR */
#define PASS_SAR_SLICE_NR1_SAR_SAR_RANGEDET 1u
/* Pulse detect logic present in SAR */
#define PASS_SAR_SLICE_NR1_SAR_SAR_PULSEDET 1u
/* Number of SAR sequencer channels (per SAR) */
#define PASS_SAR_SLICE_NR2_SAR_SAR_CHAN_NR 8u
/* Number of MUX inputs (per SAR), must be 8, 16, 24, or 32 */
#define PASS_SAR_SLICE_NR2_SAR_SAR_MUX_IN 8u
/* Is ADC is present on slice (1 = Yes, 0 = No). Calculated from SAR_ADC_NR such
   that lower numbered slices contain the ADCs that are present. */
#define PASS_SAR_SLICE_NR2_SAR_SAR_ADC_PRESENT 1u
/* Averaging logic present in SAR */
#define PASS_SAR_SLICE_NR2_SAR_SAR_AVERAGE 1u
/* Range detect logic present in SAR */
#define PASS_SAR_SLICE_NR2_SAR_SAR_RANGEDET 1u
/* Pulse detect logic present in SAR */
#define PASS_SAR_SLICE_NR2_SAR_SAR_PULSEDET 1u
/* Parameter that is 1 for ADC0 only if ADC1 or, if SAR_SLICE_NR > SAR_ADC_NR */
#define PASS_SAR_SAR_ADC0               1u
/* The number of protection contexts ([2, 16]). */
#define PERI_PC_NR                      8u
/* Master interface presence mask (5 bits) */
#define PERI_MS_PRESENT                 31u
/* Protection structures SRAM ECC present or not ('0': no, '1': yes) */
#define PERI_ECC_PRESENT                1u
/* Protection structures SRAM address ECC present or not ('0': no, '1': yes) */
#define PERI_ECC_ADDR_PRESENT           1u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT0_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT0_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT1_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT1_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT2_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL4_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL5_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL7_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL8_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL9_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL10_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL11_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT2_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT3_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT3_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT4_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT4_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT5_PERI_GROUP_PCLK_ROOT_SEL 1u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT5_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT6_PERI_GROUP_PCLK_ROOT_SEL 1u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL3_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL4_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL5_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL6_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL7_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL8_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL9_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL10_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT6_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT7_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT7_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT8_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL1_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL2_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT8_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT9_PERI_GROUP_PCLK_ROOT_SEL 1u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_CLOCK_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL0_PRESENT 1u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT9_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT10_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT10_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT11_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT11_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT12_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT12_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT13_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT13_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT14_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT14_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Peripheral group PCLK root select */
#define PERI_GROUP_PRESENT15_PERI_GROUP_PCLK_ROOT_SEL 0u
/* Clock control functionality present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_CLOCK_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL0_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL1_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL2_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL3_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL4_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL5_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL6_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL7_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL8_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL9_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL10_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL11_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL12_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL13_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL14_PRESENT 0u
/* Slave present ('0': no, '1': yes) */
#define PERI_GROUP_PRESENT15_PERI_GROUP_STRUCT_SL15_PRESENT 0u
/* Number of asynchronous PCLK groups */
#define PERI_PCLK_GROUP_NR              2u
/* Timeout functionality present ('0': no, '1': yes) */
#define PERI_TIMEOUT_PRESENT            1u
/* Trigger module present ('0': no, '1': yes) */
#define PERI_TR                         1u
/* Number of trigger groups */
#define PERI_TR_GROUP_NR                13u
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
#define PERI_TR_GROUP_NR10_TR_GROUP_TR_MANIPULATION_PRESENT 0u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR11_TR_GROUP_TR_MANIPULATION_PRESENT 0u
/* Trigger group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_GROUP_NR12_TR_GROUP_TR_MANIPULATION_PRESENT 0u
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
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR5_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR6_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR7_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR8_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR9_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* 1-to-1 group trigger manipulation logic present ('0': no, '1': yes) */
#define PERI_TR_1TO1_GROUP_NR10_TR_1TO1_GROUP_TR_1TO1_MANIPULATION_PRESENT 1u
/* Divider number width: max(1,roundup(log2(max(DIV_*_NR))) */
#define PERI_GR_DIV_ADDR_WIDTH          5u
/* Number of asynchronous PCLK groups */
#define PERI_PERI_PCLK_PCLK_GROUP_NR    2u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT 3u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT 1u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT 0u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_CLOCK_VECT 6u
/* Number of 8.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT 16u
/* Number of 16.0 dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT 17u
/* Number of 16.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT 0u
/* Number of 24.5 (fractional) dividers */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT 16u
/* Number of programmable clocks [1, 256] */
#define PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_CLOCK_VECT 121u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB0_DEEPSLEEP                  1u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB0_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB0_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB0_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB0_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB0_I2C                        1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB0_I2C_EC                     1u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB0_I2C_M_S                    1u
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
#define SCB0_UART                       1u
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
#define SCB0_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB0_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB1_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB1_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB1_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB1_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB1_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB1_I2C                        1u
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
#define SCB1_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB1_SPI_S_EC                   1u
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
#define SCB1_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB1_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB1_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB1_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB1_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB1_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB1_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB2_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB2_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB2_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB2_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB2_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB2_I2C                        1u
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
#define SCB2_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB2_SPI_S_EC                   1u
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
#define SCB2_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB2_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB2_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB2_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB2_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB2_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB2_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB3_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB3_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB3_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB3_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB3_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB3_I2C                        1u
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
#define SCB3_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB3_SPI_S_EC                   1u
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
#define SCB3_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB3_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB3_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB3_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB3_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB3_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB3_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB4_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB4_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB4_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB4_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB4_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB4_I2C                        1u
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
#define SCB4_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB4_SPI_S_EC                   1u
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
#define SCB4_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB4_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB4_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB4_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB4_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB4_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB4_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB5_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB5_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB5_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB5_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB5_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB5_I2C                        1u
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
#define SCB5_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB5_SPI_S_EC                   1u
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
#define SCB5_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB5_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB5_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB5_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB5_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB5_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB5_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB6_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB6_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB6_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB6_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB6_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB6_I2C                        1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB6_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB6_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB6_I2C_S_EC                   0u
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
#define SCB6_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB6_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB6_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB6_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB6_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB6_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB6_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB6_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB6_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB6_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB6_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB7_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB7_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB7_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB7_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB7_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB7_I2C                        1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB7_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB7_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB7_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB7_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB7_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB7_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB7_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB7_SPI_S_EC                   1u
/* UART support? ('0': no, '1': yes) */
#define SCB7_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB7_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB7_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB7_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB7_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB7_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB7_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB7_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB7_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB7_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB7_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB8_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB8_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB8_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB8_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB8_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB8_I2C                        1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB8_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB8_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB8_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB8_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB8_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB8_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB8_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB8_SPI_S_EC                   1u
/* UART support? ('0': no, '1': yes) */
#define SCB8_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB8_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB8_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB8_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB8_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB8_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB8_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB8_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB8_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB8_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB8_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB9_DEEPSLEEP                  0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB9_EC                         1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB9_I2C_M                      1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB9_I2C_S                      1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB9_I2C_GLITCH                 1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB9_I2C                        1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB9_I2C_EC                     0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB9_I2C_M_S                    1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB9_I2C_S_EC                   0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB9_SPI_M                      1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB9_SPI_S                      1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB9_SPI                        1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB9_SPI_EC                     1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB9_SPI_S_EC                   1u
/* UART support? ('0': no, '1': yes) */
#define SCB9_UART                       1u
/* SPI or UART (SPI | UART) */
#define SCB9_SPI_UART                   1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB9_EZ_DATA_NR                 256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB9_CMD_RESP                   0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB9_EZ                         1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB9_EZ_CMD_RESP                1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB9_I2C_S_EZ                   1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB9_SPI_S_EZ                   1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB9_MASTER_WIDTH               8u
/* Number of used spi_select signals (max 4) */
#define SCB9_CHIP_TOP_SPI_SEL_NR        4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB9_CHIP_TOP_I2C_FAST_PLUS     1u
/* DeepSleep support ('0':no, '1': yes) */
#define SCB10_DEEPSLEEP                 0u
/* Externally clocked support? ('0': no, '1': yes) */
#define SCB10_EC                        1u
/* I2C master support? ('0': no, '1': yes) */
#define SCB10_I2C_M                     1u
/* I2C slave support? ('0': no, '1': yes) */
#define SCB10_I2C_S                     1u
/* I2C glitch filters present? ('0': no, '1': yes) */
#define SCB10_I2C_GLITCH                1u
/* I2C support? (I2C_M | I2C_S) */
#define SCB10_I2C                       1u
/* I2C externally clocked support? ('0': no, '1': yes) */
#define SCB10_I2C_EC                    0u
/* I2C master and slave support? (I2C_M & I2C_S) */
#define SCB10_I2C_M_S                   1u
/* I2C slave with EC? (I2C_S & I2C_EC) */
#define SCB10_I2C_S_EC                  0u
/* SPI master support? ('0': no, '1': yes) */
#define SCB10_SPI_M                     1u
/* SPI slave support? ('0': no, '1': yes) */
#define SCB10_SPI_S                     1u
/* SPI support? (SPI_M | SPI_S) */
#define SCB10_SPI                       1u
/* SPI externally clocked support? ('0': no, '1': yes) */
#define SCB10_SPI_EC                    1u
/* SPI slave with EC? (SPI_S & SPI_EC) */
#define SCB10_SPI_S_EC                  1u
/* UART support? ('0': no, '1': yes) */
#define SCB10_UART                      1u
/* SPI or UART (SPI | UART) */
#define SCB10_SPI_UART                  1u
/* Number of EZ memory Bytes ([32, 256, 512]). This memory is used in EZ mode,
   CMD_RESP mode and FIFO mode. Note that in EZ mode, if EZ_DATA_NR is 512, only
   256 B are used. This is because the EZ mode uses 8-bit addresses. */
#define SCB10_EZ_DATA_NR                256u
/* Command/response mode support? ('0': no, '1': yes) */
#define SCB10_CMD_RESP                  0u
/* EZ mode support? ('0': no, '1': yes) */
#define SCB10_EZ                        1u
/* Command/response mode or EZ mode support? (CMD_RESP | EZ) */
#define SCB10_EZ_CMD_RESP               1u
/* I2C slave with EZ mode (I2C_S & EZ) */
#define SCB10_I2C_S_EZ                  1u
/* SPI slave with EZ mode (SPI_S & EZ) */
#define SCB10_SPI_S_EZ                  1u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SCB10_MASTER_WIDTH              8u
/* Number of used spi_select signals (max 4) */
#define SCB10_CHIP_TOP_SPI_SEL_NR       4u
/* Support I2C FM+/1Mbps speed ('0': no, '1': yes) */
#define SCB10_CHIP_TOP_I2C_FAST_PLUS    1u
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
#define SDHC_RETENTION_PRESENT          0u
/* Chip top connect all 8 data pins (0= connect 4 data pins, 1= connect 8 data
   pins) */
#define SDHC_CHIP_TOP_DATA8_PRESENT     1u
/* Chip top connect card_detect */
#define SDHC_CHIP_TOP_CARD_DETECT_PRESENT 1u
/* Chip top connect card_mech_write_prot_in */
#define SDHC_CHIP_TOP_CARD_WRITE_PROT_PRESENT 1u
/* Chip top connect led_ctrl_out and led_ctrl_out_en */
#define SDHC_CHIP_TOP_LED_CTRL_PRESENT  0u
/* Chip top connect io_volt_sel_out and io_volt_sel_out_en */
#define SDHC_CHIP_TOP_IO_VOLT_SEL_PRESENT 0u
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
#define SDHC_CORE_RETENTION_PRESENT     0u
/* SONOS Flash is used or not ('0': no, '1': yes) */
#define SFLASH_FLASHC_IS_SONOS          0u
/* WOUND_PRESENT or not ('0': no, '1': yes) */
#define SFLASH_WOUND_PRESENT            1u
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
/* AXI ID width. Legal range [11,16] */
#define SMIF_AXIS_ID_WIDTH              12u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define SMIF_MASTER_WIDTH               8u
/* Chip top connect all 8 data pins (0= connect 4 data pins, 1= connect 8 data
   pins) */
#define SMIF_CHIP_TOP_DATA8_PRESENT     1u
/* Number of used spi_select signals (max 4) */
#define SMIF_CHIP_TOP_SPI_SEL_NR        2u
/* ULP variant. Must be 1 when targeting S40S and 0 otherwise. */
#define SRSS_ULP_VARIANT                0u
/* HT variant. Must be 1 when targeting S40E and 0 otherwise. */
#define SRSS_HT_VARIANT                 1u
/* Number of regulator modules instantiated within SRSS. Must be > 0. */
#define SRSS_NUM_ACTREG_PWRMOD          6u
/* Number of shorting switches between vccd and vccact. Must be > 0. */
#define SRSS_NUM_ACTIVE_SWITCH          6u
/* ULP linear regulator system is present */
#define SRSS_ULPLINREG_PRESENT          0u
/* HT linear regulator system is present */
#define SRSS_HTLINREG_PRESENT           1u
/* SIMO buck core regulator is present. Only compatible with ULP linear regulator
   system (ULPLINREG_PRESENT==1). */
#define SRSS_SIMOBUCK_PRESENT           0u
/* Precision ILO (PILO) is present */
#define SRSS_PILO_PRESENT               0u
/* External Crystal Oscillator is present (high frequency) */
#define SRSS_ECO_PRESENT                1u
/* System Buck-Boost is present */
#define SRSS_SYSBB_PRESENT              0u
/* Number of PWR_HIB_DATA registers. Min is zero. */
#define SRSS_NUM_HIBDATA                1u
/* Number of clock paths. Must be > 0. Recommend
   NUM_CLKPATH>=NUM_TOTAL_PLL+CSV_PRESENT+2. CSV and FLL requires special paths,
   and one extra is recommended for programming flexibility. */
#define SRSS_NUM_CLKPATH                7u
/* Number of 200MHz PLLs present. */
#define SRSS_NUM_PLL                    2u
/* Number of HFCLK roots present. Must be > 0. Recommend NUM_HFROOT=<# chipwide
   roots>+CSV_PRESENT. */
#define SRSS_NUM_HFROOT                 8u
/* Number of DSI inputs into clock muxes. This is used for logic optimization.
   Must be > 0 */
#define SRSS_NUM_DSI                    0u
/* Alternate high-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTHF_PRESENT              0u
/* Alternate low-frequency clock is present. This is used for logic optimization. */
#define SRSS_ALTLF_PRESENT              0u
/* Backup domain is present. See VBCK_PRESENT for whether it is supplied by vddd
   or by an independent vbackup supply. */
#define SRSS_BACKUP_PRESENT             1u
/* CSV present. User must add one NUM_CLKPATH and one NUM_HFROOT to monitor ILO0
   with CSV_HF_REF clock. */
#define SRSS_CSV_PRESENT                1u
/* Number of multi-counter watchdog timers. Min is zero. */
#define SRSS_NUM_MCWDT                  3u
/* Use the hardened clkactfllmux block */
#define SRSS_USE_HARD_CLKACTFLLMUX      1u
/* Number of clock paths, including direct paths in hardened clkactfllmux block */
#define SRSS_HARD_CLKPATH               8u
/* Number of clock paths with muxes in hardened clkactfllmux block */
#define SRSS_HARD_CLKPATHMUX            8u
/* Number of HFCLKS present in hardened clkactfllmux block */
#define SRSS_HARD_HFROOT                8u
/* ECO mux is present in hardened clkactfllmux block */
#define SRSS_HARD_ECOMUX_PRESENT        1u
/* ALTHF mux is present in hardened clkactfllmux block */
#define SRSS_HARD_ALTHFMUX_PRESENT      1u
/* POR present. */
#define SRSS_POR_PRESENT                1u
/* Low-current buck regulator present. Can be derived from S40S_SISOBUCKLC_PRESENT
   or SIMOBUCK_PRESENT. */
#define SRSS_BUCKCTL_PRESENT            0u
/* Low-current SISO buck core regulator is present. Only compatible with ULP
   linear regulator system (ULPLINREG_PRESENT==1). */
#define SRSS_S40S_SISOBUCKLC_PRESENT    0u
/* HT linear regulator system is present */
#define SRSS_S40E_HTREGHC_PRESENT       1u
/* LPECO mux is present in hardened clkactfllmux block */
#define SRSS_HARD_LPECOMUX_PRESENT      1u
/* Number of 400MHz PLLs present. */
#define SRSS_NUM_PLL400M                2u
/* Mask of DIRECT_MUX defaults. For each clock root i, if bit[i] is low the
   DIRECT_MUX defaults to IMO. If bit[0] is high, the DIRECT_MUX selects the
   output of ROOT_MUX. For backward compatibility, M4 systems can have all mask
   bits high. BootROM needs either Bit0 high or a code change to pick predivider
   output before using the FLL. */
#define SRSS_MASK_DIRECTMUX_DEF         1u
/* Mask of which HFCLK roots are enabled when the debugger requests power up
   (CDBGPWRUPREQ). For each clock root i, SRSS enables the clock in response to
   CDBGPWRUPREQ, if bit[i] of mask is high. SRSS automatically enables clk_hf0,
   regardless of setting of mask bit0. */
#define SRSS_MASK_DEBUG_CLK             65535u
/* Total number of PLLs present. Must be calculated (NUM_PLL+NUM_PLL400M). Cannot
   exceed max or NUM_CLKPATH. */
#define SRSS_NUM_TOTAL_PLL              4u
/* PMIC control of vccd is present (without REGHC). */
#define SRSS_S40E_PMIC_PRESENT          0u
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
#define SRSS_BACKUP_NUM_BREG            4u
/* Low power external crystal oscillator (LPECO) is present. */
#define SRSS_BACKUP_S40E_LPECO_PRESENT  0u
/* ULP variant. Must be 1 when targeting S40S and 0 otherwise. */
#define SRSS_CLK_TRIM_PLL400M_ULP_VARIANT 0u
/* Mask of HFCLK root clock supervisors (CSV). For each clock root i, bit[i] of
   mask indicates presence of a CSV. */
#define SRSS_CSV_HF_MASK_HFCSV          255u
/* Number of input triggers per counter only routed to one counter (0..8) */
#define TCPWM_TR_ONE_CNT_NR             3u
/* Number of input triggers routed to all counters (0..254),
   NR_TR_ONE_CNT+NR_TR_ALL CNT <= 254 */
#define TCPWM_TR_ALL_CNT_NR             27u
/* Number of TCPWM counter groups (1..4) */
#define TCPWM_GRP_NR                    3u
/* Counter width in number of bits per TCPWM group (16: 16-bits, 32: 32-bits) */
#define TCPWM_GRP_NR0_CNT_GRP_CNT_WIDTH 16u
/* Second Capture / Compare Unit is present (0, 1) */
#define TCPWM_GRP_NR0_CNT_GRP_CC1_PRESENT 1u
/* Advanced Motor Control features are present (0, 1). Should only be 1 when
   GRP_CC1_PRESENT = 1 */
#define TCPWM_GRP_NR0_CNT_GRP_AMC_PRESENT 0u
/* Stepper Motor Control features are present (0, 1). */
#define TCPWM_GRP_NR0_CNT_GRP_SMC_PRESENT 0u
/* Number of counters per TCPWM group (1..256) */
#define TCPWM_GRP_NR0_GRP_GRP_CNT_NR    63u
/* Counter width in number of bits per TCPWM group (16: 16-bits, 32: 32-bits) */
#define TCPWM_GRP_NR1_CNT_GRP_CNT_WIDTH 16u
/* Second Capture / Compare Unit is present (0, 1) */
#define TCPWM_GRP_NR1_CNT_GRP_CC1_PRESENT 1u
/* Advanced Motor Control features are present (0, 1). Should only be 1 when
   GRP_CC1_PRESENT = 1 */
#define TCPWM_GRP_NR1_CNT_GRP_AMC_PRESENT 1u
/* Stepper Motor Control features are present (0, 1). */
#define TCPWM_GRP_NR1_CNT_GRP_SMC_PRESENT 1u
/* Number of counters per TCPWM group (1..256) */
#define TCPWM_GRP_NR1_GRP_GRP_CNT_NR    12u
/* Counter width in number of bits per TCPWM group (16: 16-bits, 32: 32-bits) */
#define TCPWM_GRP_NR2_CNT_GRP_CNT_WIDTH 32u
/* Second Capture / Compare Unit is present (0, 1) */
#define TCPWM_GRP_NR2_CNT_GRP_CC1_PRESENT 1u
/* Advanced Motor Control features are present (0, 1). Should only be 1 when
   GRP_CC1_PRESENT = 1 */
#define TCPWM_GRP_NR2_CNT_GRP_AMC_PRESENT 0u
/* Stepper Motor Control features are present (0, 1). */
#define TCPWM_GRP_NR2_CNT_GRP_SMC_PRESENT 0u
/* Number of counters per TCPWM group (1..256) */
#define TCPWM_GRP_NR2_GRP_GRP_CNT_NR    8u
/* Number of AHB-Lite "hmaster[]" bits ([1, 8]). */
#define TCPWM_MASTER_WIDTH              8u

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
#define CY_MMIO_SRSS_SLAVE_NR           5u
#define CY_MMIO_BACKUP_GROUP_NR         2u
#define CY_MMIO_BACKUP_SLAVE_NR         6u
#define CY_MMIO_DW_GROUP_NR             2u
#define CY_MMIO_DW_SLAVE_NR             7u
#define CY_MMIO_DMAC_GROUP_NR           2u
#define CY_MMIO_DMAC_SLAVE_NR           9u
#define CY_MMIO_EFUSE_GROUP_NR          2u
#define CY_MMIO_EFUSE_SLAVE_NR          10u
#define CY_MMIO_DFT_GROUP_NR            2u
#define CY_MMIO_DFT_SLAVE_NR            11u
#define CY_MMIO_HSIOM_GROUP_NR          3u
#define CY_MMIO_HSIOM_SLAVE_NR          0u
#define CY_MMIO_GPIO_GROUP_NR           3u
#define CY_MMIO_GPIO_SLAVE_NR           1u
#define CY_MMIO_SMARTIO_GROUP_NR        3u
#define CY_MMIO_SMARTIO_SLAVE_NR        2u
#define CY_MMIO_EVTGEN0_GROUP_NR        3u
#define CY_MMIO_EVTGEN0_SLAVE_NR        3u
#define CY_MMIO_SMIF0_GROUP_NR          4u
#define CY_MMIO_SMIF0_SLAVE_NR          0u
#define CY_MMIO_SDHC0_GROUP_NR          4u
#define CY_MMIO_SDHC0_SLAVE_NR          1u
#define CY_MMIO_ETH0_GROUP_NR           4u
#define CY_MMIO_ETH0_SLAVE_NR           2u
#define CY_MMIO_LIN0_GROUP_NR           5u
#define CY_MMIO_LIN0_SLAVE_NR           0u
#define CY_MMIO_CANFD0_GROUP_NR         5u
#define CY_MMIO_CANFD0_SLAVE_NR         1u
#define CY_MMIO_CANFD1_GROUP_NR         5u
#define CY_MMIO_CANFD1_SLAVE_NR         2u
#define CY_MMIO_TCPWM0_GROUP_NR         5u
#define CY_MMIO_TCPWM0_SLAVE_NR         3u
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
#define CY_MMIO_SCB7_GROUP_NR           6u
#define CY_MMIO_SCB7_SLAVE_NR           7u
#define CY_MMIO_SCB8_GROUP_NR           6u
#define CY_MMIO_SCB8_SLAVE_NR           8u
#define CY_MMIO_SCB9_GROUP_NR           6u
#define CY_MMIO_SCB9_SLAVE_NR           9u
#define CY_MMIO_SCB10_GROUP_NR          6u
#define CY_MMIO_SCB10_SLAVE_NR          10u
#define CY_MMIO_I2S0_GROUP_NR           8u
#define CY_MMIO_I2S0_SLAVE_NR           0u
#define CY_MMIO_I2S1_GROUP_NR           8u
#define CY_MMIO_I2S1_SLAVE_NR           1u
#define CY_MMIO_I2S2_GROUP_NR           8u
#define CY_MMIO_I2S2_SLAVE_NR           2u
#define CY_MMIO_PASS0_GROUP_NR          9u
#define CY_MMIO_PASS0_SLAVE_NR          0u

/* Protection regions */
typedef enum
{
    PROT_PERI_MAIN                  =   0,      /* Address 0x40000200, size 0x00000040 */
    PROT_PERI_SECURE                =   1,      /* Address 0x40002000, size 0x00000004 */
    PROT_PERI_GR0_GROUP             =   2,      /* Address 0x40004010, size 0x00000004 */
    PROT_PERI_GR1_GROUP             =   3,      /* Address 0x40004050, size 0x00000004 */
    PROT_PERI_GR2_GROUP             =   4,      /* Address 0x40004090, size 0x00000004 */
    PROT_PERI_GR3_GROUP             =   5,      /* Address 0x400040c0, size 0x00000020 */
    PROT_PERI_GR4_GROUP             =   6,      /* Address 0x40004100, size 0x00000020 */
    PROT_PERI_GR5_GROUP             =   7,      /* Address 0x40004140, size 0x00000020 */
    PROT_PERI_GR6_GROUP             =   8,      /* Address 0x40004180, size 0x00000020 */
    PROT_PERI_GR8_GROUP             =   9,      /* Address 0x40004200, size 0x00000020 */
    PROT_PERI_GR9_GROUP             =  10,      /* Address 0x40004240, size 0x00000020 */
    PROT_PERI_GR0_BOOT              =  11,      /* Address 0x40004020, size 0x00000004 */
    PROT_PERI_GR1_BOOT              =  12,      /* Address 0x40004060, size 0x00000004 */
    PROT_PERI_GR2_BOOT              =  13,      /* Address 0x400040a0, size 0x00000004 */
    PROT_PERI_GR3_BOOT              =  14,      /* Address 0x400040e0, size 0x00000004 */
    PROT_PERI_GR4_BOOT              =  15,      /* Address 0x40004120, size 0x00000004 */
    PROT_PERI_GR5_BOOT              =  16,      /* Address 0x40004160, size 0x00000004 */
    PROT_PERI_GR6_BOOT              =  17,      /* Address 0x400041a0, size 0x00000004 */
    PROT_PERI_GR8_BOOT              =  18,      /* Address 0x40004220, size 0x00000004 */
    PROT_PERI_GR9_BOOT              =  19,      /* Address 0x40004260, size 0x00000004 */
    PROT_PERI_TR                    =  20,      /* Address 0x40008000, size 0x00008000 */
    PROT_PERI_MS_BOOT               =  21,      /* Address 0x40030000, size 0x00001000 */
    PROT_PERI_PCLK_MAIN             =  22,      /* Address 0x40040000, size 0x00004000 */
    PROT_CRYPTO_MAIN                =  23,      /* Address 0x40100000, size 0x00000400 */
    PROT_CRYPTO_CRYPTO              =  24,      /* Address 0x40101000, size 0x00000800 */
    PROT_CRYPTO_BOOT                =  25,      /* Address 0x40102000, size 0x00000100 */
    PROT_CRYPTO_KEY0                =  26,      /* Address 0x40102100, size 0x00000004 */
    PROT_CRYPTO_KEY1                =  27,      /* Address 0x40102120, size 0x00000004 */
    PROT_CRYPTO_BUF                 =  28,      /* Address 0x40108000, size 0x00002000 */
    PROT_CPUSS_CM7_0                =  29,      /* Address 0x40200000, size 0x00000400 */
    PROT_CPUSS_CM7_1                =  30,      /* Address 0x40200400, size 0x00000400 */
    PROT_CPUSS_CM0                  =  31,      /* Address 0x40201000, size 0x00001000 */
    PROT_CPUSS_BOOT                 =  32,      /* Address 0x40202000, size 0x00000200 */
    PROT_CPUSS_CM0_INT              =  33,      /* Address 0x40208000, size 0x00000800 */
    PROT_CPUSS_CM7_0_INT            =  34,      /* Address 0x4020a000, size 0x00000800 */
    PROT_CPUSS_CM7_1_INT            =  35,      /* Address 0x4020c000, size 0x00000800 */
    PROT_FAULT_STRUCT0_MAIN         =  36,      /* Address 0x40210000, size 0x00000100 */
    PROT_FAULT_STRUCT1_MAIN         =  37,      /* Address 0x40210100, size 0x00000100 */
    PROT_FAULT_STRUCT2_MAIN         =  38,      /* Address 0x40210200, size 0x00000100 */
    PROT_FAULT_STRUCT3_MAIN         =  39,      /* Address 0x40210300, size 0x00000100 */
    PROT_IPC_STRUCT0_IPC            =  40,      /* Address 0x40220000, size 0x00000020 */
    PROT_IPC_STRUCT1_IPC            =  41,      /* Address 0x40220020, size 0x00000020 */
    PROT_IPC_STRUCT2_IPC            =  42,      /* Address 0x40220040, size 0x00000020 */
    PROT_IPC_STRUCT3_IPC            =  43,      /* Address 0x40220060, size 0x00000020 */
    PROT_IPC_STRUCT4_IPC            =  44,      /* Address 0x40220080, size 0x00000020 */
    PROT_IPC_STRUCT5_IPC            =  45,      /* Address 0x402200a0, size 0x00000020 */
    PROT_IPC_STRUCT6_IPC            =  46,      /* Address 0x402200c0, size 0x00000020 */
    PROT_IPC_STRUCT7_IPC            =  47,      /* Address 0x402200e0, size 0x00000020 */
    PROT_IPC_INTR_STRUCT0_INTR      =  48,      /* Address 0x40221000, size 0x00000010 */
    PROT_IPC_INTR_STRUCT1_INTR      =  49,      /* Address 0x40221020, size 0x00000010 */
    PROT_IPC_INTR_STRUCT2_INTR      =  50,      /* Address 0x40221040, size 0x00000010 */
    PROT_IPC_INTR_STRUCT3_INTR      =  51,      /* Address 0x40221060, size 0x00000010 */
    PROT_IPC_INTR_STRUCT4_INTR      =  52,      /* Address 0x40221080, size 0x00000010 */
    PROT_IPC_INTR_STRUCT5_INTR      =  53,      /* Address 0x402210a0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT6_INTR      =  54,      /* Address 0x402210c0, size 0x00000010 */
    PROT_IPC_INTR_STRUCT7_INTR      =  55,      /* Address 0x402210e0, size 0x00000010 */
    PROT_PROT_SMPU_MAIN             =  56,      /* Address 0x40230000, size 0x00000040 */
    PROT_PROT_MPU0_MAIN             =  57,      /* Address 0x40234000, size 0x00000004 */
    PROT_PROT_MPU5_MAIN             =  58,      /* Address 0x40235400, size 0x00000400 */
    PROT_PROT_MPU6_MAIN             =  59,      /* Address 0x40235800, size 0x00000400 */
    PROT_PROT_MPU13_MAIN            =  60,      /* Address 0x40237400, size 0x00000004 */
    PROT_PROT_MPU14_MAIN            =  61,      /* Address 0x40237800, size 0x00000004 */
    PROT_PROT_MPU15_MAIN            =  62,      /* Address 0x40237c00, size 0x00000400 */
    PROT_FLASHC_MAIN                =  63,      /* Address 0x40240000, size 0x00000008 */
    PROT_FLASHC_CMD                 =  64,      /* Address 0x40240008, size 0x00000004 */
    PROT_FLASHC_DFT                 =  65,      /* Address 0x40240200, size 0x00000100 */
    PROT_FLASHC_CM0                 =  66,      /* Address 0x40240400, size 0x00000080 */
    PROT_FLASHC_CM7_0               =  67,      /* Address 0x402404e0, size 0x00000004 */
    PROT_FLASHC_CM7_1               =  68,      /* Address 0x40240560, size 0x00000004 */
    PROT_FLASHC_CRYPTO              =  69,      /* Address 0x40240580, size 0x00000004 */
    PROT_FLASHC_DW0                 =  70,      /* Address 0x40240600, size 0x00000004 */
    PROT_FLASHC_DW1                 =  71,      /* Address 0x40240680, size 0x00000004 */
    PROT_FLASHC_DMAC                =  72,      /* Address 0x40240700, size 0x00000004 */
    PROT_FLASHC_SLOW0               =  73,      /* Address 0x40240780, size 0x00000004 */
    PROT_FLASHC_SLOW1               =  74,      /* Address 0x40240800, size 0x00000004 */
    PROT_FLASHC_FlashMgmt           =  75,      /* Address 0x4024f000, size 0x00000080 */
    PROT_FLASHC_MainSafety          =  76,      /* Address 0x4024f400, size 0x00000008 */
    PROT_FLASHC_WorkSafety          =  77,      /* Address 0x4024f500, size 0x00000004 */
    PROT_SRSS_GENERAL               =  78,      /* Address 0x40260000, size 0x00000400 */
    PROT_SRSS_MAIN                  =  79,      /* Address 0x40261000, size 0x00001000 */
    PROT_SRSS_SECURE                =  80,      /* Address 0x40262000, size 0x00002000 */
    PROT_MCWDT0_CONFIG              =  81,      /* Address 0x40268000, size 0x00000080 */
    PROT_MCWDT1_CONFIG              =  82,      /* Address 0x40268100, size 0x00000080 */
    PROT_MCWDT2_CONFIG              =  83,      /* Address 0x40268200, size 0x00000080 */
    PROT_MCWDT0_MAIN                =  84,      /* Address 0x40268080, size 0x00000040 */
    PROT_MCWDT1_MAIN                =  85,      /* Address 0x40268180, size 0x00000040 */
    PROT_MCWDT2_MAIN                =  86,      /* Address 0x40268280, size 0x00000040 */
    PROT_WDT_CONFIG                 =  87,      /* Address 0x4026c000, size 0x00000020 */
    PROT_WDT_MAIN                   =  88,      /* Address 0x4026c040, size 0x00000020 */
    PROT_BACKUP_BACKUP              =  89,      /* Address 0x40270000, size 0x00010000 */
    PROT_DW0_DW                     =  90,      /* Address 0x40280000, size 0x00000100 */
    PROT_DW1_DW                     =  91,      /* Address 0x40290000, size 0x00000100 */
    PROT_DW0_DW_CRC                 =  92,      /* Address 0x40280100, size 0x00000080 */
    PROT_DW1_DW_CRC                 =  93,      /* Address 0x40290100, size 0x00000080 */
    PROT_DW0_CH_STRUCT0_CH          =  94,      /* Address 0x40288000, size 0x00000040 */
    PROT_DW0_CH_STRUCT1_CH          =  95,      /* Address 0x40288040, size 0x00000040 */
    PROT_DW0_CH_STRUCT2_CH          =  96,      /* Address 0x40288080, size 0x00000040 */
    PROT_DW0_CH_STRUCT3_CH          =  97,      /* Address 0x402880c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT4_CH          =  98,      /* Address 0x40288100, size 0x00000040 */
    PROT_DW0_CH_STRUCT5_CH          =  99,      /* Address 0x40288140, size 0x00000040 */
    PROT_DW0_CH_STRUCT6_CH          = 100,      /* Address 0x40288180, size 0x00000040 */
    PROT_DW0_CH_STRUCT7_CH          = 101,      /* Address 0x402881c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT8_CH          = 102,      /* Address 0x40288200, size 0x00000040 */
    PROT_DW0_CH_STRUCT9_CH          = 103,      /* Address 0x40288240, size 0x00000040 */
    PROT_DW0_CH_STRUCT10_CH         = 104,      /* Address 0x40288280, size 0x00000040 */
    PROT_DW0_CH_STRUCT11_CH         = 105,      /* Address 0x402882c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT12_CH         = 106,      /* Address 0x40288300, size 0x00000040 */
    PROT_DW0_CH_STRUCT13_CH         = 107,      /* Address 0x40288340, size 0x00000040 */
    PROT_DW0_CH_STRUCT14_CH         = 108,      /* Address 0x40288380, size 0x00000040 */
    PROT_DW0_CH_STRUCT15_CH         = 109,      /* Address 0x402883c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT16_CH         = 110,      /* Address 0x40288400, size 0x00000040 */
    PROT_DW0_CH_STRUCT17_CH         = 111,      /* Address 0x40288440, size 0x00000040 */
    PROT_DW0_CH_STRUCT18_CH         = 112,      /* Address 0x40288480, size 0x00000040 */
    PROT_DW0_CH_STRUCT19_CH         = 113,      /* Address 0x402884c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT20_CH         = 114,      /* Address 0x40288500, size 0x00000040 */
    PROT_DW0_CH_STRUCT21_CH         = 115,      /* Address 0x40288540, size 0x00000040 */
    PROT_DW0_CH_STRUCT22_CH         = 116,      /* Address 0x40288580, size 0x00000040 */
    PROT_DW0_CH_STRUCT23_CH         = 117,      /* Address 0x402885c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT24_CH         = 118,      /* Address 0x40288600, size 0x00000040 */
    PROT_DW0_CH_STRUCT25_CH         = 119,      /* Address 0x40288640, size 0x00000040 */
    PROT_DW0_CH_STRUCT26_CH         = 120,      /* Address 0x40288680, size 0x00000040 */
    PROT_DW0_CH_STRUCT27_CH         = 121,      /* Address 0x402886c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT28_CH         = 122,      /* Address 0x40288700, size 0x00000040 */
    PROT_DW0_CH_STRUCT29_CH         = 123,      /* Address 0x40288740, size 0x00000040 */
    PROT_DW0_CH_STRUCT30_CH         = 124,      /* Address 0x40288780, size 0x00000040 */
    PROT_DW0_CH_STRUCT31_CH         = 125,      /* Address 0x402887c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT32_CH         = 126,      /* Address 0x40288800, size 0x00000040 */
    PROT_DW0_CH_STRUCT33_CH         = 127,      /* Address 0x40288840, size 0x00000040 */
    PROT_DW0_CH_STRUCT34_CH         = 128,      /* Address 0x40288880, size 0x00000040 */
    PROT_DW0_CH_STRUCT35_CH         = 129,      /* Address 0x402888c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT36_CH         = 130,      /* Address 0x40288900, size 0x00000040 */
    PROT_DW0_CH_STRUCT37_CH         = 131,      /* Address 0x40288940, size 0x00000040 */
    PROT_DW0_CH_STRUCT38_CH         = 132,      /* Address 0x40288980, size 0x00000040 */
    PROT_DW0_CH_STRUCT39_CH         = 133,      /* Address 0x402889c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT40_CH         = 134,      /* Address 0x40288a00, size 0x00000040 */
    PROT_DW0_CH_STRUCT41_CH         = 135,      /* Address 0x40288a40, size 0x00000040 */
    PROT_DW0_CH_STRUCT42_CH         = 136,      /* Address 0x40288a80, size 0x00000040 */
    PROT_DW0_CH_STRUCT43_CH         = 137,      /* Address 0x40288ac0, size 0x00000040 */
    PROT_DW0_CH_STRUCT44_CH         = 138,      /* Address 0x40288b00, size 0x00000040 */
    PROT_DW0_CH_STRUCT45_CH         = 139,      /* Address 0x40288b40, size 0x00000040 */
    PROT_DW0_CH_STRUCT46_CH         = 140,      /* Address 0x40288b80, size 0x00000040 */
    PROT_DW0_CH_STRUCT47_CH         = 141,      /* Address 0x40288bc0, size 0x00000040 */
    PROT_DW0_CH_STRUCT48_CH         = 142,      /* Address 0x40288c00, size 0x00000040 */
    PROT_DW0_CH_STRUCT49_CH         = 143,      /* Address 0x40288c40, size 0x00000040 */
    PROT_DW0_CH_STRUCT50_CH         = 144,      /* Address 0x40288c80, size 0x00000040 */
    PROT_DW0_CH_STRUCT51_CH         = 145,      /* Address 0x40288cc0, size 0x00000040 */
    PROT_DW0_CH_STRUCT52_CH         = 146,      /* Address 0x40288d00, size 0x00000040 */
    PROT_DW0_CH_STRUCT53_CH         = 147,      /* Address 0x40288d40, size 0x00000040 */
    PROT_DW0_CH_STRUCT54_CH         = 148,      /* Address 0x40288d80, size 0x00000040 */
    PROT_DW0_CH_STRUCT55_CH         = 149,      /* Address 0x40288dc0, size 0x00000040 */
    PROT_DW0_CH_STRUCT56_CH         = 150,      /* Address 0x40288e00, size 0x00000040 */
    PROT_DW0_CH_STRUCT57_CH         = 151,      /* Address 0x40288e40, size 0x00000040 */
    PROT_DW0_CH_STRUCT58_CH         = 152,      /* Address 0x40288e80, size 0x00000040 */
    PROT_DW0_CH_STRUCT59_CH         = 153,      /* Address 0x40288ec0, size 0x00000040 */
    PROT_DW0_CH_STRUCT60_CH         = 154,      /* Address 0x40288f00, size 0x00000040 */
    PROT_DW0_CH_STRUCT61_CH         = 155,      /* Address 0x40288f40, size 0x00000040 */
    PROT_DW0_CH_STRUCT62_CH         = 156,      /* Address 0x40288f80, size 0x00000040 */
    PROT_DW0_CH_STRUCT63_CH         = 157,      /* Address 0x40288fc0, size 0x00000040 */
    PROT_DW0_CH_STRUCT64_CH         = 158,      /* Address 0x40289000, size 0x00000040 */
    PROT_DW0_CH_STRUCT65_CH         = 159,      /* Address 0x40289040, size 0x00000040 */
    PROT_DW0_CH_STRUCT66_CH         = 160,      /* Address 0x40289080, size 0x00000040 */
    PROT_DW0_CH_STRUCT67_CH         = 161,      /* Address 0x402890c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT68_CH         = 162,      /* Address 0x40289100, size 0x00000040 */
    PROT_DW0_CH_STRUCT69_CH         = 163,      /* Address 0x40289140, size 0x00000040 */
    PROT_DW0_CH_STRUCT70_CH         = 164,      /* Address 0x40289180, size 0x00000040 */
    PROT_DW0_CH_STRUCT71_CH         = 165,      /* Address 0x402891c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT72_CH         = 166,      /* Address 0x40289200, size 0x00000040 */
    PROT_DW0_CH_STRUCT73_CH         = 167,      /* Address 0x40289240, size 0x00000040 */
    PROT_DW0_CH_STRUCT74_CH         = 168,      /* Address 0x40289280, size 0x00000040 */
    PROT_DW0_CH_STRUCT75_CH         = 169,      /* Address 0x402892c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT76_CH         = 170,      /* Address 0x40289300, size 0x00000040 */
    PROT_DW0_CH_STRUCT77_CH         = 171,      /* Address 0x40289340, size 0x00000040 */
    PROT_DW0_CH_STRUCT78_CH         = 172,      /* Address 0x40289380, size 0x00000040 */
    PROT_DW0_CH_STRUCT79_CH         = 173,      /* Address 0x402893c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT80_CH         = 174,      /* Address 0x40289400, size 0x00000040 */
    PROT_DW0_CH_STRUCT81_CH         = 175,      /* Address 0x40289440, size 0x00000040 */
    PROT_DW0_CH_STRUCT82_CH         = 176,      /* Address 0x40289480, size 0x00000040 */
    PROT_DW0_CH_STRUCT83_CH         = 177,      /* Address 0x402894c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT84_CH         = 178,      /* Address 0x40289500, size 0x00000040 */
    PROT_DW0_CH_STRUCT85_CH         = 179,      /* Address 0x40289540, size 0x00000040 */
    PROT_DW0_CH_STRUCT86_CH         = 180,      /* Address 0x40289580, size 0x00000040 */
    PROT_DW0_CH_STRUCT87_CH         = 181,      /* Address 0x402895c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT88_CH         = 182,      /* Address 0x40289600, size 0x00000040 */
    PROT_DW0_CH_STRUCT89_CH         = 183,      /* Address 0x40289640, size 0x00000040 */
    PROT_DW0_CH_STRUCT90_CH         = 184,      /* Address 0x40289680, size 0x00000040 */
    PROT_DW0_CH_STRUCT91_CH         = 185,      /* Address 0x402896c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT92_CH         = 186,      /* Address 0x40289700, size 0x00000040 */
    PROT_DW0_CH_STRUCT93_CH         = 187,      /* Address 0x40289740, size 0x00000040 */
    PROT_DW0_CH_STRUCT94_CH         = 188,      /* Address 0x40289780, size 0x00000040 */
    PROT_DW0_CH_STRUCT95_CH         = 189,      /* Address 0x402897c0, size 0x00000040 */
    PROT_DW0_CH_STRUCT96_CH         = 190,      /* Address 0x40289800, size 0x00000040 */
    PROT_DW0_CH_STRUCT97_CH         = 191,      /* Address 0x40289840, size 0x00000040 */
    PROT_DW0_CH_STRUCT98_CH         = 192,      /* Address 0x40289880, size 0x00000040 */
    PROT_DW0_CH_STRUCT99_CH         = 193,      /* Address 0x402898c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT0_CH          = 194,      /* Address 0x40298000, size 0x00000040 */
    PROT_DW1_CH_STRUCT1_CH          = 195,      /* Address 0x40298040, size 0x00000040 */
    PROT_DW1_CH_STRUCT2_CH          = 196,      /* Address 0x40298080, size 0x00000040 */
    PROT_DW1_CH_STRUCT3_CH          = 197,      /* Address 0x402980c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT4_CH          = 198,      /* Address 0x40298100, size 0x00000040 */
    PROT_DW1_CH_STRUCT5_CH          = 199,      /* Address 0x40298140, size 0x00000040 */
    PROT_DW1_CH_STRUCT6_CH          = 200,      /* Address 0x40298180, size 0x00000040 */
    PROT_DW1_CH_STRUCT7_CH          = 201,      /* Address 0x402981c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT8_CH          = 202,      /* Address 0x40298200, size 0x00000040 */
    PROT_DW1_CH_STRUCT9_CH          = 203,      /* Address 0x40298240, size 0x00000040 */
    PROT_DW1_CH_STRUCT10_CH         = 204,      /* Address 0x40298280, size 0x00000040 */
    PROT_DW1_CH_STRUCT11_CH         = 205,      /* Address 0x402982c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT12_CH         = 206,      /* Address 0x40298300, size 0x00000040 */
    PROT_DW1_CH_STRUCT13_CH         = 207,      /* Address 0x40298340, size 0x00000040 */
    PROT_DW1_CH_STRUCT14_CH         = 208,      /* Address 0x40298380, size 0x00000040 */
    PROT_DW1_CH_STRUCT15_CH         = 209,      /* Address 0x402983c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT16_CH         = 210,      /* Address 0x40298400, size 0x00000040 */
    PROT_DW1_CH_STRUCT17_CH         = 211,      /* Address 0x40298440, size 0x00000040 */
    PROT_DW1_CH_STRUCT18_CH         = 212,      /* Address 0x40298480, size 0x00000040 */
    PROT_DW1_CH_STRUCT19_CH         = 213,      /* Address 0x402984c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT20_CH         = 214,      /* Address 0x40298500, size 0x00000040 */
    PROT_DW1_CH_STRUCT21_CH         = 215,      /* Address 0x40298540, size 0x00000040 */
    PROT_DW1_CH_STRUCT22_CH         = 216,      /* Address 0x40298580, size 0x00000040 */
    PROT_DW1_CH_STRUCT23_CH         = 217,      /* Address 0x402985c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT24_CH         = 218,      /* Address 0x40298600, size 0x00000040 */
    PROT_DW1_CH_STRUCT25_CH         = 219,      /* Address 0x40298640, size 0x00000040 */
    PROT_DW1_CH_STRUCT26_CH         = 220,      /* Address 0x40298680, size 0x00000040 */
    PROT_DW1_CH_STRUCT27_CH         = 221,      /* Address 0x402986c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT28_CH         = 222,      /* Address 0x40298700, size 0x00000040 */
    PROT_DW1_CH_STRUCT29_CH         = 223,      /* Address 0x40298740, size 0x00000040 */
    PROT_DW1_CH_STRUCT30_CH         = 224,      /* Address 0x40298780, size 0x00000040 */
    PROT_DW1_CH_STRUCT31_CH         = 225,      /* Address 0x402987c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT32_CH         = 226,      /* Address 0x40298800, size 0x00000040 */
    PROT_DW1_CH_STRUCT33_CH         = 227,      /* Address 0x40298840, size 0x00000040 */
    PROT_DW1_CH_STRUCT34_CH         = 228,      /* Address 0x40298880, size 0x00000040 */
    PROT_DW1_CH_STRUCT35_CH         = 229,      /* Address 0x402988c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT36_CH         = 230,      /* Address 0x40298900, size 0x00000040 */
    PROT_DW1_CH_STRUCT37_CH         = 231,      /* Address 0x40298940, size 0x00000040 */
    PROT_DW1_CH_STRUCT38_CH         = 232,      /* Address 0x40298980, size 0x00000040 */
    PROT_DW1_CH_STRUCT39_CH         = 233,      /* Address 0x402989c0, size 0x00000040 */
    PROT_DW1_CH_STRUCT40_CH         = 234,      /* Address 0x40298a00, size 0x00000040 */
    PROT_DW1_CH_STRUCT41_CH         = 235,      /* Address 0x40298a40, size 0x00000040 */
    PROT_DW1_CH_STRUCT42_CH         = 236,      /* Address 0x40298a80, size 0x00000040 */
    PROT_DW1_CH_STRUCT43_CH         = 237,      /* Address 0x40298ac0, size 0x00000040 */
    PROT_DW1_CH_STRUCT44_CH         = 238,      /* Address 0x40298b00, size 0x00000040 */
    PROT_DW1_CH_STRUCT45_CH         = 239,      /* Address 0x40298b40, size 0x00000040 */
    PROT_DW1_CH_STRUCT46_CH         = 240,      /* Address 0x40298b80, size 0x00000040 */
    PROT_DW1_CH_STRUCT47_CH         = 241,      /* Address 0x40298bc0, size 0x00000040 */
    PROT_DW1_CH_STRUCT48_CH         = 242,      /* Address 0x40298c00, size 0x00000040 */
    PROT_DW1_CH_STRUCT49_CH         = 243,      /* Address 0x40298c40, size 0x00000040 */
    PROT_DW1_CH_STRUCT50_CH         = 244,      /* Address 0x40298c80, size 0x00000040 */
    PROT_DW1_CH_STRUCT51_CH         = 245,      /* Address 0x40298cc0, size 0x00000040 */
    PROT_DW1_CH_STRUCT52_CH         = 246,      /* Address 0x40298d00, size 0x00000040 */
    PROT_DW1_CH_STRUCT53_CH         = 247,      /* Address 0x40298d40, size 0x00000040 */
    PROT_DW1_CH_STRUCT54_CH         = 248,      /* Address 0x40298d80, size 0x00000040 */
    PROT_DW1_CH_STRUCT55_CH         = 249,      /* Address 0x40298dc0, size 0x00000040 */
    PROT_DW1_CH_STRUCT56_CH         = 250,      /* Address 0x40298e00, size 0x00000040 */
    PROT_DW1_CH_STRUCT57_CH         = 251,      /* Address 0x40298e40, size 0x00000040 */
    PROT_DMAC_TOP                   = 252,      /* Address 0x402a0000, size 0x00000010 */
    PROT_DMAC_CH0_CH                = 253,      /* Address 0x402a1000, size 0x00000100 */
    PROT_DMAC_CH1_CH                = 254,      /* Address 0x402a1100, size 0x00000100 */
    PROT_DMAC_CH2_CH                = 255,      /* Address 0x402a1200, size 0x00000100 */
    PROT_DMAC_CH3_CH                = 256,      /* Address 0x402a1300, size 0x00000100 */
    PROT_DMAC_CH4_CH                = 257,      /* Address 0x402a1400, size 0x00000100 */
    PROT_DMAC_CH5_CH                = 258,      /* Address 0x402a1500, size 0x00000100 */
    PROT_DMAC_CH6_CH                = 259,      /* Address 0x402a1600, size 0x00000100 */
    PROT_DMAC_CH7_CH                = 260,      /* Address 0x402a1700, size 0x00000100 */
    PROT_EFUSE_CTL                  = 261,      /* Address 0x402c0000, size 0x00000200 */
    PROT_EFUSE_DATA                 = 262,      /* Address 0x402c0800, size 0x00000200 */
    PROT_BIST                       = 263,      /* Address 0x402f0000, size 0x00001000 */
    PROT_HSIOM_PRT0_PRT             = 264,      /* Address 0x40300000, size 0x00000008 */
    PROT_HSIOM_PRT1_PRT             = 265,      /* Address 0x40300010, size 0x00000008 */
    PROT_HSIOM_PRT2_PRT             = 266,      /* Address 0x40300020, size 0x00000008 */
    PROT_HSIOM_PRT3_PRT             = 267,      /* Address 0x40300030, size 0x00000008 */
    PROT_HSIOM_PRT4_PRT             = 268,      /* Address 0x40300040, size 0x00000008 */
    PROT_HSIOM_PRT5_PRT             = 269,      /* Address 0x40300050, size 0x00000008 */
    PROT_HSIOM_PRT6_PRT             = 270,      /* Address 0x40300060, size 0x00000008 */
    PROT_HSIOM_PRT7_PRT             = 271,      /* Address 0x40300070, size 0x00000008 */
    PROT_HSIOM_PRT8_PRT             = 272,      /* Address 0x40300080, size 0x00000008 */
    PROT_HSIOM_PRT9_PRT             = 273,      /* Address 0x40300090, size 0x00000008 */
    PROT_HSIOM_PRT10_PRT            = 274,      /* Address 0x403000a0, size 0x00000008 */
    PROT_HSIOM_PRT11_PRT            = 275,      /* Address 0x403000b0, size 0x00000008 */
    PROT_HSIOM_PRT12_PRT            = 276,      /* Address 0x403000c0, size 0x00000008 */
    PROT_HSIOM_PRT13_PRT            = 277,      /* Address 0x403000d0, size 0x00000008 */
    PROT_HSIOM_PRT14_PRT            = 278,      /* Address 0x403000e0, size 0x00000008 */
    PROT_HSIOM_PRT15_PRT            = 279,      /* Address 0x403000f0, size 0x00000008 */
    PROT_HSIOM_PRT16_PRT            = 280,      /* Address 0x40300100, size 0x00000008 */
    PROT_HSIOM_PRT17_PRT            = 281,      /* Address 0x40300110, size 0x00000008 */
    PROT_HSIOM_PRT18_PRT            = 282,      /* Address 0x40300120, size 0x00000008 */
    PROT_HSIOM_PRT19_PRT            = 283,      /* Address 0x40300130, size 0x00000008 */
    PROT_HSIOM_PRT20_PRT            = 284,      /* Address 0x40300140, size 0x00000008 */
    PROT_HSIOM_PRT21_PRT            = 285,      /* Address 0x40300150, size 0x00000008 */
    PROT_HSIOM_PRT22_PRT            = 286,      /* Address 0x40300160, size 0x00000008 */
    PROT_HSIOM_PRT23_PRT            = 287,      /* Address 0x40300170, size 0x00000008 */
    PROT_HSIOM_PRT24_PRT            = 288,      /* Address 0x40300180, size 0x00000008 */
    PROT_HSIOM_PRT25_PRT            = 289,      /* Address 0x40300190, size 0x00000008 */
    PROT_HSIOM_PRT26_PRT            = 290,      /* Address 0x403001a0, size 0x00000008 */
    PROT_HSIOM_PRT27_PRT            = 291,      /* Address 0x403001b0, size 0x00000008 */
    PROT_HSIOM_PRT28_PRT            = 292,      /* Address 0x403001c0, size 0x00000008 */
    PROT_HSIOM_PRT29_PRT            = 293,      /* Address 0x403001d0, size 0x00000008 */
    PROT_HSIOM_PRT30_PRT            = 294,      /* Address 0x403001e0, size 0x00000008 */
    PROT_HSIOM_PRT31_PRT            = 295,      /* Address 0x403001f0, size 0x00000008 */
    PROT_HSIOM_PRT32_PRT            = 296,      /* Address 0x40300200, size 0x00000008 */
    PROT_HSIOM_AMUX                 = 297,      /* Address 0x40302000, size 0x00000010 */
    PROT_HSIOM_MON                  = 298,      /* Address 0x40302200, size 0x00000010 */
    PROT_HSIOM_ALTJTAG              = 299,      /* Address 0x40302240, size 0x00000004 */
    PROT_GPIO_PRT0_PRT              = 300,      /* Address 0x40310000, size 0x00000040 */
    PROT_GPIO_PRT1_PRT              = 301,      /* Address 0x40310080, size 0x00000040 */
    PROT_GPIO_PRT2_PRT              = 302,      /* Address 0x40310100, size 0x00000040 */
    PROT_GPIO_PRT3_PRT              = 303,      /* Address 0x40310180, size 0x00000040 */
    PROT_GPIO_PRT4_PRT              = 304,      /* Address 0x40310200, size 0x00000040 */
    PROT_GPIO_PRT5_PRT              = 305,      /* Address 0x40310280, size 0x00000040 */
    PROT_GPIO_PRT6_PRT              = 306,      /* Address 0x40310300, size 0x00000040 */
    PROT_GPIO_PRT7_PRT              = 307,      /* Address 0x40310380, size 0x00000040 */
    PROT_GPIO_PRT8_PRT              = 308,      /* Address 0x40310400, size 0x00000040 */
    PROT_GPIO_PRT9_PRT              = 309,      /* Address 0x40310480, size 0x00000040 */
    PROT_GPIO_PRT10_PRT             = 310,      /* Address 0x40310500, size 0x00000040 */
    PROT_GPIO_PRT11_PRT             = 311,      /* Address 0x40310580, size 0x00000040 */
    PROT_GPIO_PRT12_PRT             = 312,      /* Address 0x40310600, size 0x00000040 */
    PROT_GPIO_PRT13_PRT             = 313,      /* Address 0x40310680, size 0x00000040 */
    PROT_GPIO_PRT14_PRT             = 314,      /* Address 0x40310700, size 0x00000040 */
    PROT_GPIO_PRT15_PRT             = 315,      /* Address 0x40310780, size 0x00000040 */
    PROT_GPIO_PRT16_PRT             = 316,      /* Address 0x40310800, size 0x00000040 */
    PROT_GPIO_PRT17_PRT             = 317,      /* Address 0x40310880, size 0x00000040 */
    PROT_GPIO_PRT18_PRT             = 318,      /* Address 0x40310900, size 0x00000040 */
    PROT_GPIO_PRT19_PRT             = 319,      /* Address 0x40310980, size 0x00000040 */
    PROT_GPIO_PRT20_PRT             = 320,      /* Address 0x40310a00, size 0x00000040 */
    PROT_GPIO_PRT21_PRT             = 321,      /* Address 0x40310a80, size 0x00000040 */
    PROT_GPIO_PRT22_PRT             = 322,      /* Address 0x40310b00, size 0x00000040 */
    PROT_GPIO_PRT23_PRT             = 323,      /* Address 0x40310b80, size 0x00000040 */
    PROT_GPIO_PRT24_PRT             = 324,      /* Address 0x40310c00, size 0x00000040 */
    PROT_GPIO_PRT25_PRT             = 325,      /* Address 0x40310c80, size 0x00000040 */
    PROT_GPIO_PRT26_PRT             = 326,      /* Address 0x40310d00, size 0x00000040 */
    PROT_GPIO_PRT27_PRT             = 327,      /* Address 0x40310d80, size 0x00000040 */
    PROT_GPIO_PRT28_PRT             = 328,      /* Address 0x40310e00, size 0x00000040 */
    PROT_GPIO_PRT29_PRT             = 329,      /* Address 0x40310e80, size 0x00000040 */
    PROT_GPIO_PRT30_PRT             = 330,      /* Address 0x40310f00, size 0x00000040 */
    PROT_GPIO_PRT31_PRT             = 331,      /* Address 0x40310f80, size 0x00000040 */
    PROT_GPIO_PRT32_PRT             = 332,      /* Address 0x40311000, size 0x00000040 */
    PROT_GPIO_PRT0_CFG              = 333,      /* Address 0x40310040, size 0x00000020 */
    PROT_GPIO_PRT1_CFG              = 334,      /* Address 0x403100c0, size 0x00000020 */
    PROT_GPIO_PRT2_CFG              = 335,      /* Address 0x40310140, size 0x00000020 */
    PROT_GPIO_PRT3_CFG              = 336,      /* Address 0x403101c0, size 0x00000020 */
    PROT_GPIO_PRT4_CFG              = 337,      /* Address 0x40310240, size 0x00000020 */
    PROT_GPIO_PRT5_CFG              = 338,      /* Address 0x403102c0, size 0x00000020 */
    PROT_GPIO_PRT6_CFG              = 339,      /* Address 0x40310340, size 0x00000020 */
    PROT_GPIO_PRT7_CFG              = 340,      /* Address 0x403103c0, size 0x00000020 */
    PROT_GPIO_PRT8_CFG              = 341,      /* Address 0x40310440, size 0x00000020 */
    PROT_GPIO_PRT9_CFG              = 342,      /* Address 0x403104c0, size 0x00000020 */
    PROT_GPIO_PRT10_CFG             = 343,      /* Address 0x40310540, size 0x00000020 */
    PROT_GPIO_PRT11_CFG             = 344,      /* Address 0x403105c0, size 0x00000020 */
    PROT_GPIO_PRT12_CFG             = 345,      /* Address 0x40310640, size 0x00000020 */
    PROT_GPIO_PRT13_CFG             = 346,      /* Address 0x403106c0, size 0x00000020 */
    PROT_GPIO_PRT14_CFG             = 347,      /* Address 0x40310740, size 0x00000020 */
    PROT_GPIO_PRT15_CFG             = 348,      /* Address 0x403107c0, size 0x00000020 */
    PROT_GPIO_PRT16_CFG             = 349,      /* Address 0x40310840, size 0x00000020 */
    PROT_GPIO_PRT17_CFG             = 350,      /* Address 0x403108c0, size 0x00000020 */
    PROT_GPIO_PRT18_CFG             = 351,      /* Address 0x40310940, size 0x00000020 */
    PROT_GPIO_PRT19_CFG             = 352,      /* Address 0x403109c0, size 0x00000020 */
    PROT_GPIO_PRT20_CFG             = 353,      /* Address 0x40310a40, size 0x00000020 */
    PROT_GPIO_PRT21_CFG             = 354,      /* Address 0x40310ac0, size 0x00000020 */
    PROT_GPIO_PRT22_CFG             = 355,      /* Address 0x40310b40, size 0x00000020 */
    PROT_GPIO_PRT23_CFG             = 356,      /* Address 0x40310bc0, size 0x00000020 */
    PROT_GPIO_PRT24_CFG             = 357,      /* Address 0x40310c40, size 0x00000020 */
    PROT_GPIO_PRT25_CFG             = 358,      /* Address 0x40310cc0, size 0x00000020 */
    PROT_GPIO_PRT26_CFG             = 359,      /* Address 0x40310d40, size 0x00000020 */
    PROT_GPIO_PRT27_CFG             = 360,      /* Address 0x40310dc0, size 0x00000020 */
    PROT_GPIO_PRT28_CFG             = 361,      /* Address 0x40310e40, size 0x00000020 */
    PROT_GPIO_PRT29_CFG             = 362,      /* Address 0x40310ec0, size 0x00000020 */
    PROT_GPIO_PRT30_CFG             = 363,      /* Address 0x40310f40, size 0x00000020 */
    PROT_GPIO_PRT31_CFG             = 364,      /* Address 0x40310fc0, size 0x00000020 */
    PROT_GPIO_PRT32_CFG             = 365,      /* Address 0x40311040, size 0x00000020 */
    PROT_GPIO_GPIO                  = 366,      /* Address 0x40314000, size 0x00000040 */
    PROT_GPIO_TEST                  = 367,      /* Address 0x40315000, size 0x00000008 */
    PROT_SMARTIO_PRT12_PRT          = 368,      /* Address 0x40320c00, size 0x00000100 */
    PROT_SMARTIO_PRT13_PRT          = 369,      /* Address 0x40320d00, size 0x00000100 */
    PROT_SMARTIO_PRT14_PRT          = 370,      /* Address 0x40320e00, size 0x00000100 */
    PROT_SMARTIO_PRT15_PRT          = 371,      /* Address 0x40320f00, size 0x00000100 */
    PROT_SMARTIO_PRT17_PRT          = 372,      /* Address 0x40321100, size 0x00000100 */
    PROT_EVTGEN0                    = 373,      /* Address 0x403f0000, size 0x00001000 */
    PROT_SMIF0                      = 374,      /* Address 0x40420000, size 0x00010000 */
    PROT_SDHC0                      = 375,      /* Address 0x40460000, size 0x00010000 */
    PROT_ETH0                       = 376,      /* Address 0x40480000, size 0x00010000 */
    PROT_LIN0_MAIN                  = 377,      /* Address 0x40500000, size 0x00000008 */
    PROT_LIN0_CH0_CH                = 378,      /* Address 0x40508000, size 0x00000100 */
    PROT_LIN0_CH1_CH                = 379,      /* Address 0x40508100, size 0x00000100 */
    PROT_LIN0_CH2_CH                = 380,      /* Address 0x40508200, size 0x00000100 */
    PROT_LIN0_CH3_CH                = 381,      /* Address 0x40508300, size 0x00000100 */
    PROT_LIN0_CH4_CH                = 382,      /* Address 0x40508400, size 0x00000100 */
    PROT_LIN0_CH5_CH                = 383,      /* Address 0x40508500, size 0x00000100 */
    PROT_LIN0_CH6_CH                = 384,      /* Address 0x40508600, size 0x00000100 */
    PROT_LIN0_CH7_CH                = 385,      /* Address 0x40508700, size 0x00000100 */
    PROT_LIN0_CH8_CH                = 386,      /* Address 0x40508800, size 0x00000100 */
    PROT_LIN0_CH9_CH                = 387,      /* Address 0x40508900, size 0x00000100 */
    PROT_LIN0_CH10_CH               = 388,      /* Address 0x40508a00, size 0x00000100 */
    PROT_LIN0_CH11_CH               = 389,      /* Address 0x40508b00, size 0x00000100 */
    PROT_LIN0_CH12_CH               = 390,      /* Address 0x40508c00, size 0x00000100 */
    PROT_LIN0_CH13_CH               = 391,      /* Address 0x40508d00, size 0x00000100 */
    PROT_LIN0_CH14_CH               = 392,      /* Address 0x40508e00, size 0x00000100 */
    PROT_LIN0_CH15_CH               = 393,      /* Address 0x40508f00, size 0x00000100 */
    PROT_CANFD0_CH0_CH              = 394,      /* Address 0x40520000, size 0x00000200 */
    PROT_CANFD0_CH1_CH              = 395,      /* Address 0x40520200, size 0x00000200 */
    PROT_CANFD0_CH2_CH              = 396,      /* Address 0x40520400, size 0x00000200 */
    PROT_CANFD0_CH3_CH              = 397,      /* Address 0x40520600, size 0x00000200 */
    PROT_CANFD1_CH0_CH              = 398,      /* Address 0x40540000, size 0x00000200 */
    PROT_CANFD1_CH1_CH              = 399,      /* Address 0x40540200, size 0x00000200 */
    PROT_CANFD1_CH2_CH              = 400,      /* Address 0x40540400, size 0x00000200 */
    PROT_CANFD1_CH3_CH              = 401,      /* Address 0x40540600, size 0x00000200 */
    PROT_CANFD0_MAIN                = 402,      /* Address 0x40521000, size 0x00000100 */
    PROT_CANFD1_MAIN                = 403,      /* Address 0x40541000, size 0x00000100 */
    PROT_CANFD0_BUF                 = 404,      /* Address 0x40530000, size 0x00010000 */
    PROT_CANFD1_BUF                 = 405,      /* Address 0x40550000, size 0x00010000 */
    PROT_TCPWM0_GRP0_CNT0_CNT       = 406,      /* Address 0x40580000, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT1_CNT       = 407,      /* Address 0x40580080, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT2_CNT       = 408,      /* Address 0x40580100, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT3_CNT       = 409,      /* Address 0x40580180, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT4_CNT       = 410,      /* Address 0x40580200, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT5_CNT       = 411,      /* Address 0x40580280, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT6_CNT       = 412,      /* Address 0x40580300, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT7_CNT       = 413,      /* Address 0x40580380, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT8_CNT       = 414,      /* Address 0x40580400, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT9_CNT       = 415,      /* Address 0x40580480, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT10_CNT      = 416,      /* Address 0x40580500, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT11_CNT      = 417,      /* Address 0x40580580, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT12_CNT      = 418,      /* Address 0x40580600, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT13_CNT      = 419,      /* Address 0x40580680, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT14_CNT      = 420,      /* Address 0x40580700, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT15_CNT      = 421,      /* Address 0x40580780, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT16_CNT      = 422,      /* Address 0x40580800, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT17_CNT      = 423,      /* Address 0x40580880, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT18_CNT      = 424,      /* Address 0x40580900, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT19_CNT      = 425,      /* Address 0x40580980, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT20_CNT      = 426,      /* Address 0x40580a00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT21_CNT      = 427,      /* Address 0x40580a80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT22_CNT      = 428,      /* Address 0x40580b00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT23_CNT      = 429,      /* Address 0x40580b80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT24_CNT      = 430,      /* Address 0x40580c00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT25_CNT      = 431,      /* Address 0x40580c80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT26_CNT      = 432,      /* Address 0x40580d00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT27_CNT      = 433,      /* Address 0x40580d80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT28_CNT      = 434,      /* Address 0x40580e00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT29_CNT      = 435,      /* Address 0x40580e80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT30_CNT      = 436,      /* Address 0x40580f00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT31_CNT      = 437,      /* Address 0x40580f80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT32_CNT      = 438,      /* Address 0x40581000, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT33_CNT      = 439,      /* Address 0x40581080, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT34_CNT      = 440,      /* Address 0x40581100, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT35_CNT      = 441,      /* Address 0x40581180, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT36_CNT      = 442,      /* Address 0x40581200, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT37_CNT      = 443,      /* Address 0x40581280, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT38_CNT      = 444,      /* Address 0x40581300, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT39_CNT      = 445,      /* Address 0x40581380, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT40_CNT      = 446,      /* Address 0x40581400, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT41_CNT      = 447,      /* Address 0x40581480, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT42_CNT      = 448,      /* Address 0x40581500, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT43_CNT      = 449,      /* Address 0x40581580, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT44_CNT      = 450,      /* Address 0x40581600, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT45_CNT      = 451,      /* Address 0x40581680, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT46_CNT      = 452,      /* Address 0x40581700, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT47_CNT      = 453,      /* Address 0x40581780, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT48_CNT      = 454,      /* Address 0x40581800, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT49_CNT      = 455,      /* Address 0x40581880, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT50_CNT      = 456,      /* Address 0x40581900, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT51_CNT      = 457,      /* Address 0x40581980, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT52_CNT      = 458,      /* Address 0x40581a00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT53_CNT      = 459,      /* Address 0x40581a80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT54_CNT      = 460,      /* Address 0x40581b00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT55_CNT      = 461,      /* Address 0x40581b80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT56_CNT      = 462,      /* Address 0x40581c00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT57_CNT      = 463,      /* Address 0x40581c80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT58_CNT      = 464,      /* Address 0x40581d00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT59_CNT      = 465,      /* Address 0x40581d80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT60_CNT      = 466,      /* Address 0x40581e00, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT61_CNT      = 467,      /* Address 0x40581e80, size 0x00000080 */
    PROT_TCPWM0_GRP0_CNT62_CNT      = 468,      /* Address 0x40581f00, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT0_CNT       = 469,      /* Address 0x40588000, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT1_CNT       = 470,      /* Address 0x40588080, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT2_CNT       = 471,      /* Address 0x40588100, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT3_CNT       = 472,      /* Address 0x40588180, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT4_CNT       = 473,      /* Address 0x40588200, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT5_CNT       = 474,      /* Address 0x40588280, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT6_CNT       = 475,      /* Address 0x40588300, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT7_CNT       = 476,      /* Address 0x40588380, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT8_CNT       = 477,      /* Address 0x40588400, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT9_CNT       = 478,      /* Address 0x40588480, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT10_CNT      = 479,      /* Address 0x40588500, size 0x00000080 */
    PROT_TCPWM0_GRP1_CNT11_CNT      = 480,      /* Address 0x40588580, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT0_CNT       = 481,      /* Address 0x40590000, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT1_CNT       = 482,      /* Address 0x40590080, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT2_CNT       = 483,      /* Address 0x40590100, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT3_CNT       = 484,      /* Address 0x40590180, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT4_CNT       = 485,      /* Address 0x40590200, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT5_CNT       = 486,      /* Address 0x40590280, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT6_CNT       = 487,      /* Address 0x40590300, size 0x00000080 */
    PROT_TCPWM0_GRP2_CNT7_CNT       = 488,      /* Address 0x40590380, size 0x00000080 */
    PROT_SCB0                       = 489,      /* Address 0x40600000, size 0x00010000 */
    PROT_SCB1                       = 490,      /* Address 0x40610000, size 0x00010000 */
    PROT_SCB2                       = 491,      /* Address 0x40620000, size 0x00010000 */
    PROT_SCB3                       = 492,      /* Address 0x40630000, size 0x00010000 */
    PROT_SCB4                       = 493,      /* Address 0x40640000, size 0x00010000 */
    PROT_SCB5                       = 494,      /* Address 0x40650000, size 0x00010000 */
    PROT_SCB6                       = 495,      /* Address 0x40660000, size 0x00010000 */
    PROT_SCB7                       = 496,      /* Address 0x40670000, size 0x00010000 */
    PROT_SCB8                       = 497,      /* Address 0x40680000, size 0x00010000 */
    PROT_SCB9                       = 498,      /* Address 0x40690000, size 0x00010000 */
    PROT_SCB10                      = 499,      /* Address 0x406a0000, size 0x00010000 */
    PROT_I2S0                       = 500,      /* Address 0x40800000, size 0x00001000 */
    PROT_I2S1                       = 501,      /* Address 0x40801000, size 0x00001000 */
    PROT_I2S2                       = 502,      /* Address 0x40802000, size 0x00001000 */
    PROT_PASS0_SAR0_SAR             = 503,      /* Address 0x40900000, size 0x00000400 */
    PROT_PASS0_SAR1_SAR             = 504,      /* Address 0x40901000, size 0x00000400 */
    PROT_PASS0_SAR2_SAR             = 505,      /* Address 0x40902000, size 0x00000400 */
    PROT_PASS0_SAR0_CH0_CH          = 506,      /* Address 0x40900800, size 0x00000040 */
    PROT_PASS0_SAR0_CH1_CH          = 507,      /* Address 0x40900840, size 0x00000040 */
    PROT_PASS0_SAR0_CH2_CH          = 508,      /* Address 0x40900880, size 0x00000040 */
    PROT_PASS0_SAR0_CH3_CH          = 509,      /* Address 0x409008c0, size 0x00000040 */
    PROT_PASS0_SAR0_CH4_CH          = 510,      /* Address 0x40900900, size 0x00000040 */
    PROT_PASS0_SAR0_CH5_CH          = 511,      /* Address 0x40900940, size 0x00000040 */
    PROT_PASS0_SAR0_CH6_CH          = 512,      /* Address 0x40900980, size 0x00000040 */
    PROT_PASS0_SAR0_CH7_CH          = 513,      /* Address 0x409009c0, size 0x00000040 */
    PROT_PASS0_SAR0_CH8_CH          = 514,      /* Address 0x40900a00, size 0x00000040 */
    PROT_PASS0_SAR0_CH9_CH          = 515,      /* Address 0x40900a40, size 0x00000040 */
    PROT_PASS0_SAR0_CH10_CH         = 516,      /* Address 0x40900a80, size 0x00000040 */
    PROT_PASS0_SAR0_CH11_CH         = 517,      /* Address 0x40900ac0, size 0x00000040 */
    PROT_PASS0_SAR0_CH12_CH         = 518,      /* Address 0x40900b00, size 0x00000040 */
    PROT_PASS0_SAR0_CH13_CH         = 519,      /* Address 0x40900b40, size 0x00000040 */
    PROT_PASS0_SAR0_CH14_CH         = 520,      /* Address 0x40900b80, size 0x00000040 */
    PROT_PASS0_SAR0_CH15_CH         = 521,      /* Address 0x40900bc0, size 0x00000040 */
    PROT_PASS0_SAR0_CH16_CH         = 522,      /* Address 0x40900c00, size 0x00000040 */
    PROT_PASS0_SAR0_CH17_CH         = 523,      /* Address 0x40900c40, size 0x00000040 */
    PROT_PASS0_SAR0_CH18_CH         = 524,      /* Address 0x40900c80, size 0x00000040 */
    PROT_PASS0_SAR0_CH19_CH         = 525,      /* Address 0x40900cc0, size 0x00000040 */
    PROT_PASS0_SAR0_CH20_CH         = 526,      /* Address 0x40900d00, size 0x00000040 */
    PROT_PASS0_SAR0_CH21_CH         = 527,      /* Address 0x40900d40, size 0x00000040 */
    PROT_PASS0_SAR0_CH22_CH         = 528,      /* Address 0x40900d80, size 0x00000040 */
    PROT_PASS0_SAR0_CH23_CH         = 529,      /* Address 0x40900dc0, size 0x00000040 */
    PROT_PASS0_SAR0_CH24_CH         = 530,      /* Address 0x40900e00, size 0x00000040 */
    PROT_PASS0_SAR0_CH25_CH         = 531,      /* Address 0x40900e40, size 0x00000040 */
    PROT_PASS0_SAR0_CH26_CH         = 532,      /* Address 0x40900e80, size 0x00000040 */
    PROT_PASS0_SAR0_CH27_CH         = 533,      /* Address 0x40900ec0, size 0x00000040 */
    PROT_PASS0_SAR0_CH28_CH         = 534,      /* Address 0x40900f00, size 0x00000040 */
    PROT_PASS0_SAR0_CH29_CH         = 535,      /* Address 0x40900f40, size 0x00000040 */
    PROT_PASS0_SAR0_CH30_CH         = 536,      /* Address 0x40900f80, size 0x00000040 */
    PROT_PASS0_SAR0_CH31_CH         = 537,      /* Address 0x40900fc0, size 0x00000040 */
    PROT_PASS0_SAR1_CH0_CH          = 538,      /* Address 0x40901800, size 0x00000040 */
    PROT_PASS0_SAR1_CH1_CH          = 539,      /* Address 0x40901840, size 0x00000040 */
    PROT_PASS0_SAR1_CH2_CH          = 540,      /* Address 0x40901880, size 0x00000040 */
    PROT_PASS0_SAR1_CH3_CH          = 541,      /* Address 0x409018c0, size 0x00000040 */
    PROT_PASS0_SAR1_CH4_CH          = 542,      /* Address 0x40901900, size 0x00000040 */
    PROT_PASS0_SAR1_CH5_CH          = 543,      /* Address 0x40901940, size 0x00000040 */
    PROT_PASS0_SAR1_CH6_CH          = 544,      /* Address 0x40901980, size 0x00000040 */
    PROT_PASS0_SAR1_CH7_CH          = 545,      /* Address 0x409019c0, size 0x00000040 */
    PROT_PASS0_SAR1_CH8_CH          = 546,      /* Address 0x40901a00, size 0x00000040 */
    PROT_PASS0_SAR1_CH9_CH          = 547,      /* Address 0x40901a40, size 0x00000040 */
    PROT_PASS0_SAR1_CH10_CH         = 548,      /* Address 0x40901a80, size 0x00000040 */
    PROT_PASS0_SAR1_CH11_CH         = 549,      /* Address 0x40901ac0, size 0x00000040 */
    PROT_PASS0_SAR1_CH12_CH         = 550,      /* Address 0x40901b00, size 0x00000040 */
    PROT_PASS0_SAR1_CH13_CH         = 551,      /* Address 0x40901b40, size 0x00000040 */
    PROT_PASS0_SAR1_CH14_CH         = 552,      /* Address 0x40901b80, size 0x00000040 */
    PROT_PASS0_SAR1_CH15_CH         = 553,      /* Address 0x40901bc0, size 0x00000040 */
    PROT_PASS0_SAR1_CH16_CH         = 554,      /* Address 0x40901c00, size 0x00000040 */
    PROT_PASS0_SAR1_CH17_CH         = 555,      /* Address 0x40901c40, size 0x00000040 */
    PROT_PASS0_SAR1_CH18_CH         = 556,      /* Address 0x40901c80, size 0x00000040 */
    PROT_PASS0_SAR1_CH19_CH         = 557,      /* Address 0x40901cc0, size 0x00000040 */
    PROT_PASS0_SAR1_CH20_CH         = 558,      /* Address 0x40901d00, size 0x00000040 */
    PROT_PASS0_SAR1_CH21_CH         = 559,      /* Address 0x40901d40, size 0x00000040 */
    PROT_PASS0_SAR1_CH22_CH         = 560,      /* Address 0x40901d80, size 0x00000040 */
    PROT_PASS0_SAR1_CH23_CH         = 561,      /* Address 0x40901dc0, size 0x00000040 */
    PROT_PASS0_SAR1_CH24_CH         = 562,      /* Address 0x40901e00, size 0x00000040 */
    PROT_PASS0_SAR1_CH25_CH         = 563,      /* Address 0x40901e40, size 0x00000040 */
    PROT_PASS0_SAR1_CH26_CH         = 564,      /* Address 0x40901e80, size 0x00000040 */
    PROT_PASS0_SAR1_CH27_CH         = 565,      /* Address 0x40901ec0, size 0x00000040 */
    PROT_PASS0_SAR1_CH28_CH         = 566,      /* Address 0x40901f00, size 0x00000040 */
    PROT_PASS0_SAR1_CH29_CH         = 567,      /* Address 0x40901f40, size 0x00000040 */
    PROT_PASS0_SAR1_CH30_CH         = 568,      /* Address 0x40901f80, size 0x00000040 */
    PROT_PASS0_SAR1_CH31_CH         = 569,      /* Address 0x40901fc0, size 0x00000040 */
    PROT_PASS0_SAR2_CH0_CH          = 570,      /* Address 0x40902800, size 0x00000040 */
    PROT_PASS0_SAR2_CH1_CH          = 571,      /* Address 0x40902840, size 0x00000040 */
    PROT_PASS0_SAR2_CH2_CH          = 572,      /* Address 0x40902880, size 0x00000040 */
    PROT_PASS0_SAR2_CH3_CH          = 573,      /* Address 0x409028c0, size 0x00000040 */
    PROT_PASS0_SAR2_CH4_CH          = 574,      /* Address 0x40902900, size 0x00000040 */
    PROT_PASS0_SAR2_CH5_CH          = 575,      /* Address 0x40902940, size 0x00000040 */
    PROT_PASS0_SAR2_CH6_CH          = 576,      /* Address 0x40902980, size 0x00000040 */
    PROT_PASS0_SAR2_CH7_CH          = 577,      /* Address 0x409029c0, size 0x00000040 */
    PROT_PASS0_TOP                  = 578       /* Address 0x409f0000, size 0x00001000 */
} cy_en_prot_region_t;

#endif /* _XMC7100_CONFIG_H_ */


/* [] END OF FILE */
