/***************************************************************************//**
* \file cyhal_triggers_xmc7100.h
*
* \brief
* XMC7100 family HAL triggers header
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

#ifndef _CYHAL_TRIGGERS_XMC7100_H_
#define _CYHAL_TRIGGERS_XMC7100_H_

/**
 * \addtogroup group_hal_impl_triggers_xmc7100 XMC7100
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for xmc7100
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \cond INTERNAL */
/** @brief Name of each input trigger. */
typedef enum
{
    _CYHAL_TRIGGER_CPUSS_ZERO = 0, //!< cpuss.zero
    _CYHAL_TRIGGER_AUDIOSS0_TR_I2S_RX_REQ = 1, //!< audioss[0].tr_i2s_rx_req
    _CYHAL_TRIGGER_AUDIOSS1_TR_I2S_RX_REQ = 2, //!< audioss[1].tr_i2s_rx_req
    _CYHAL_TRIGGER_AUDIOSS2_TR_I2S_RX_REQ = 3, //!< audioss[2].tr_i2s_rx_req
    _CYHAL_TRIGGER_AUDIOSS0_TR_I2S_TX_REQ = 4, //!< audioss[0].tr_i2s_tx_req
    _CYHAL_TRIGGER_AUDIOSS1_TR_I2S_TX_REQ = 5, //!< audioss[1].tr_i2s_tx_req
    _CYHAL_TRIGGER_AUDIOSS2_TR_I2S_TX_REQ = 6, //!< audioss[2].tr_i2s_tx_req
    _CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0 = 7, //!< canfd[0].tr_dbg_dma_req[0]
    _CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ1 = 8, //!< canfd[0].tr_dbg_dma_req[1]
    _CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ2 = 9, //!< canfd[0].tr_dbg_dma_req[2]
    _CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ3 = 10, //!< canfd[0].tr_dbg_dma_req[3]
    _CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ0 = 11, //!< canfd[1].tr_dbg_dma_req[0]
    _CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ1 = 12, //!< canfd[1].tr_dbg_dma_req[1]
    _CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ2 = 13, //!< canfd[1].tr_dbg_dma_req[2]
    _CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ3 = 14, //!< canfd[1].tr_dbg_dma_req[3]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO00 = 15, //!< canfd[0].tr_fifo0[0]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO01 = 16, //!< canfd[0].tr_fifo0[1]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO02 = 17, //!< canfd[0].tr_fifo0[2]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO03 = 18, //!< canfd[0].tr_fifo0[3]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO00 = 19, //!< canfd[1].tr_fifo0[0]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO01 = 20, //!< canfd[1].tr_fifo0[1]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO02 = 21, //!< canfd[1].tr_fifo0[2]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO03 = 22, //!< canfd[1].tr_fifo0[3]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO10 = 23, //!< canfd[0].tr_fifo1[0]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO11 = 24, //!< canfd[0].tr_fifo1[1]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO12 = 25, //!< canfd[0].tr_fifo1[2]
    _CYHAL_TRIGGER_CANFD0_TR_FIFO13 = 26, //!< canfd[0].tr_fifo1[3]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO10 = 27, //!< canfd[1].tr_fifo1[0]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO11 = 28, //!< canfd[1].tr_fifo1[1]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO12 = 29, //!< canfd[1].tr_fifo1[2]
    _CYHAL_TRIGGER_CANFD1_TR_FIFO13 = 30, //!< canfd[1].tr_fifo1[3]
    _CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0 = 31, //!< canfd[0].tr_tmp_rtp_out[0]
    _CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT1 = 32, //!< canfd[0].tr_tmp_rtp_out[1]
    _CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT2 = 33, //!< canfd[0].tr_tmp_rtp_out[2]
    _CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT3 = 34, //!< canfd[0].tr_tmp_rtp_out[3]
    _CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT0 = 35, //!< canfd[1].tr_tmp_rtp_out[0]
    _CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT1 = 36, //!< canfd[1].tr_tmp_rtp_out[1]
    _CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT2 = 37, //!< canfd[1].tr_tmp_rtp_out[2]
    _CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT3 = 38, //!< canfd[1].tr_tmp_rtp_out[3]
    _CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0 = 39, //!< cpuss.cti_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1 = 40, //!< cpuss.cti_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT0 = 41, //!< cpuss.dmac_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT1 = 42, //!< cpuss.dmac_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT2 = 43, //!< cpuss.dmac_tr_out[2]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT3 = 44, //!< cpuss.dmac_tr_out[3]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT4 = 45, //!< cpuss.dmac_tr_out[4]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT5 = 46, //!< cpuss.dmac_tr_out[5]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT6 = 47, //!< cpuss.dmac_tr_out[6]
    _CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT7 = 48, //!< cpuss.dmac_tr_out[7]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0 = 49, //!< cpuss.dw0_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT1 = 50, //!< cpuss.dw0_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT2 = 51, //!< cpuss.dw0_tr_out[2]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT3 = 52, //!< cpuss.dw0_tr_out[3]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT4 = 53, //!< cpuss.dw0_tr_out[4]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT5 = 54, //!< cpuss.dw0_tr_out[5]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT6 = 55, //!< cpuss.dw0_tr_out[6]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT7 = 56, //!< cpuss.dw0_tr_out[7]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT8 = 57, //!< cpuss.dw0_tr_out[8]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT9 = 58, //!< cpuss.dw0_tr_out[9]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT10 = 59, //!< cpuss.dw0_tr_out[10]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT11 = 60, //!< cpuss.dw0_tr_out[11]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT12 = 61, //!< cpuss.dw0_tr_out[12]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT13 = 62, //!< cpuss.dw0_tr_out[13]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT14 = 63, //!< cpuss.dw0_tr_out[14]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT15 = 64, //!< cpuss.dw0_tr_out[15]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT16 = 65, //!< cpuss.dw0_tr_out[16]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT17 = 66, //!< cpuss.dw0_tr_out[17]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT18 = 67, //!< cpuss.dw0_tr_out[18]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT19 = 68, //!< cpuss.dw0_tr_out[19]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT20 = 69, //!< cpuss.dw0_tr_out[20]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT21 = 70, //!< cpuss.dw0_tr_out[21]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT22 = 71, //!< cpuss.dw0_tr_out[22]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT23 = 72, //!< cpuss.dw0_tr_out[23]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT24 = 73, //!< cpuss.dw0_tr_out[24]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT25 = 74, //!< cpuss.dw0_tr_out[25]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT26 = 75, //!< cpuss.dw0_tr_out[26]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT27 = 76, //!< cpuss.dw0_tr_out[27]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT28 = 77, //!< cpuss.dw0_tr_out[28]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT29 = 78, //!< cpuss.dw0_tr_out[29]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT30 = 79, //!< cpuss.dw0_tr_out[30]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT31 = 80, //!< cpuss.dw0_tr_out[31]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT32 = 81, //!< cpuss.dw0_tr_out[32]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT33 = 82, //!< cpuss.dw0_tr_out[33]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT34 = 83, //!< cpuss.dw0_tr_out[34]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT35 = 84, //!< cpuss.dw0_tr_out[35]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT36 = 85, //!< cpuss.dw0_tr_out[36]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT37 = 86, //!< cpuss.dw0_tr_out[37]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT38 = 87, //!< cpuss.dw0_tr_out[38]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT39 = 88, //!< cpuss.dw0_tr_out[39]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT40 = 89, //!< cpuss.dw0_tr_out[40]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT41 = 90, //!< cpuss.dw0_tr_out[41]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT42 = 91, //!< cpuss.dw0_tr_out[42]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT43 = 92, //!< cpuss.dw0_tr_out[43]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT44 = 93, //!< cpuss.dw0_tr_out[44]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT45 = 94, //!< cpuss.dw0_tr_out[45]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT46 = 95, //!< cpuss.dw0_tr_out[46]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT47 = 96, //!< cpuss.dw0_tr_out[47]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT48 = 97, //!< cpuss.dw0_tr_out[48]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT49 = 98, //!< cpuss.dw0_tr_out[49]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT50 = 99, //!< cpuss.dw0_tr_out[50]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT51 = 100, //!< cpuss.dw0_tr_out[51]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT52 = 101, //!< cpuss.dw0_tr_out[52]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT53 = 102, //!< cpuss.dw0_tr_out[53]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT54 = 103, //!< cpuss.dw0_tr_out[54]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT55 = 104, //!< cpuss.dw0_tr_out[55]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT56 = 105, //!< cpuss.dw0_tr_out[56]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT57 = 106, //!< cpuss.dw0_tr_out[57]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT58 = 107, //!< cpuss.dw0_tr_out[58]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT59 = 108, //!< cpuss.dw0_tr_out[59]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT60 = 109, //!< cpuss.dw0_tr_out[60]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT61 = 110, //!< cpuss.dw0_tr_out[61]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT62 = 111, //!< cpuss.dw0_tr_out[62]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT63 = 112, //!< cpuss.dw0_tr_out[63]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT64 = 113, //!< cpuss.dw0_tr_out[64]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT65 = 114, //!< cpuss.dw0_tr_out[65]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT66 = 115, //!< cpuss.dw0_tr_out[66]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT67 = 116, //!< cpuss.dw0_tr_out[67]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT68 = 117, //!< cpuss.dw0_tr_out[68]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT69 = 118, //!< cpuss.dw0_tr_out[69]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT70 = 119, //!< cpuss.dw0_tr_out[70]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT71 = 120, //!< cpuss.dw0_tr_out[71]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT72 = 121, //!< cpuss.dw0_tr_out[72]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT73 = 122, //!< cpuss.dw0_tr_out[73]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT74 = 123, //!< cpuss.dw0_tr_out[74]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT75 = 124, //!< cpuss.dw0_tr_out[75]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT76 = 125, //!< cpuss.dw0_tr_out[76]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT77 = 126, //!< cpuss.dw0_tr_out[77]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT78 = 127, //!< cpuss.dw0_tr_out[78]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT79 = 128, //!< cpuss.dw0_tr_out[79]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT80 = 129, //!< cpuss.dw0_tr_out[80]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT81 = 130, //!< cpuss.dw0_tr_out[81]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT82 = 131, //!< cpuss.dw0_tr_out[82]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT83 = 132, //!< cpuss.dw0_tr_out[83]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT84 = 133, //!< cpuss.dw0_tr_out[84]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT85 = 134, //!< cpuss.dw0_tr_out[85]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT86 = 135, //!< cpuss.dw0_tr_out[86]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT87 = 136, //!< cpuss.dw0_tr_out[87]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT88 = 137, //!< cpuss.dw0_tr_out[88]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT89 = 138, //!< cpuss.dw0_tr_out[89]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT90 = 139, //!< cpuss.dw0_tr_out[90]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT91 = 140, //!< cpuss.dw0_tr_out[91]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT92 = 141, //!< cpuss.dw0_tr_out[92]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT93 = 142, //!< cpuss.dw0_tr_out[93]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT94 = 143, //!< cpuss.dw0_tr_out[94]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT95 = 144, //!< cpuss.dw0_tr_out[95]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT96 = 145, //!< cpuss.dw0_tr_out[96]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT97 = 146, //!< cpuss.dw0_tr_out[97]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT98 = 147, //!< cpuss.dw0_tr_out[98]
    _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT99 = 148, //!< cpuss.dw0_tr_out[99]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT0 = 149, //!< cpuss.dw1_tr_out[0]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT1 = 150, //!< cpuss.dw1_tr_out[1]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT2 = 151, //!< cpuss.dw1_tr_out[2]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT3 = 152, //!< cpuss.dw1_tr_out[3]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT4 = 153, //!< cpuss.dw1_tr_out[4]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT5 = 154, //!< cpuss.dw1_tr_out[5]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT6 = 155, //!< cpuss.dw1_tr_out[6]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT7 = 156, //!< cpuss.dw1_tr_out[7]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT8 = 157, //!< cpuss.dw1_tr_out[8]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT9 = 158, //!< cpuss.dw1_tr_out[9]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT10 = 159, //!< cpuss.dw1_tr_out[10]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT11 = 160, //!< cpuss.dw1_tr_out[11]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT12 = 161, //!< cpuss.dw1_tr_out[12]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT13 = 162, //!< cpuss.dw1_tr_out[13]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT14 = 163, //!< cpuss.dw1_tr_out[14]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT15 = 164, //!< cpuss.dw1_tr_out[15]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT16 = 165, //!< cpuss.dw1_tr_out[16]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT17 = 166, //!< cpuss.dw1_tr_out[17]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT18 = 167, //!< cpuss.dw1_tr_out[18]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT19 = 168, //!< cpuss.dw1_tr_out[19]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT20 = 169, //!< cpuss.dw1_tr_out[20]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT21 = 170, //!< cpuss.dw1_tr_out[21]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT22 = 171, //!< cpuss.dw1_tr_out[22]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT23 = 172, //!< cpuss.dw1_tr_out[23]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT24 = 173, //!< cpuss.dw1_tr_out[24]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT25 = 174, //!< cpuss.dw1_tr_out[25]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT26 = 175, //!< cpuss.dw1_tr_out[26]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT27 = 176, //!< cpuss.dw1_tr_out[27]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT28 = 177, //!< cpuss.dw1_tr_out[28]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT29 = 178, //!< cpuss.dw1_tr_out[29]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT30 = 179, //!< cpuss.dw1_tr_out[30]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT31 = 180, //!< cpuss.dw1_tr_out[31]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT32 = 181, //!< cpuss.dw1_tr_out[32]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT33 = 182, //!< cpuss.dw1_tr_out[33]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT34 = 183, //!< cpuss.dw1_tr_out[34]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT35 = 184, //!< cpuss.dw1_tr_out[35]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT36 = 185, //!< cpuss.dw1_tr_out[36]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT37 = 186, //!< cpuss.dw1_tr_out[37]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT38 = 187, //!< cpuss.dw1_tr_out[38]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT39 = 188, //!< cpuss.dw1_tr_out[39]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT40 = 189, //!< cpuss.dw1_tr_out[40]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT41 = 190, //!< cpuss.dw1_tr_out[41]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT42 = 191, //!< cpuss.dw1_tr_out[42]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT43 = 192, //!< cpuss.dw1_tr_out[43]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT44 = 193, //!< cpuss.dw1_tr_out[44]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT45 = 194, //!< cpuss.dw1_tr_out[45]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT46 = 195, //!< cpuss.dw1_tr_out[46]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT47 = 196, //!< cpuss.dw1_tr_out[47]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT48 = 197, //!< cpuss.dw1_tr_out[48]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT49 = 198, //!< cpuss.dw1_tr_out[49]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT50 = 199, //!< cpuss.dw1_tr_out[50]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT51 = 200, //!< cpuss.dw1_tr_out[51]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT52 = 201, //!< cpuss.dw1_tr_out[52]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT53 = 202, //!< cpuss.dw1_tr_out[53]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT54 = 203, //!< cpuss.dw1_tr_out[54]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT55 = 204, //!< cpuss.dw1_tr_out[55]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT56 = 205, //!< cpuss.dw1_tr_out[56]
    _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT57 = 206, //!< cpuss.dw1_tr_out[57]
    _CYHAL_TRIGGER_CPUSS_TR_FAULT0 = 207, //!< cpuss.tr_fault[0]
    _CYHAL_TRIGGER_CPUSS_TR_FAULT1 = 208, //!< cpuss.tr_fault[1]
    _CYHAL_TRIGGER_CPUSS_TR_FAULT2 = 209, //!< cpuss.tr_fault[2]
    _CYHAL_TRIGGER_CPUSS_TR_FAULT3 = 210, //!< cpuss.tr_fault[3]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT0 = 211, //!< evtgen[0].tr_out[0]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT1 = 212, //!< evtgen[0].tr_out[1]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT2 = 213, //!< evtgen[0].tr_out[2]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT3 = 214, //!< evtgen[0].tr_out[3]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT4 = 215, //!< evtgen[0].tr_out[4]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT5 = 216, //!< evtgen[0].tr_out[5]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT6 = 217, //!< evtgen[0].tr_out[6]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT7 = 218, //!< evtgen[0].tr_out[7]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT8 = 219, //!< evtgen[0].tr_out[8]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT9 = 220, //!< evtgen[0].tr_out[9]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT10 = 221, //!< evtgen[0].tr_out[10]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT11 = 222, //!< evtgen[0].tr_out[11]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT12 = 223, //!< evtgen[0].tr_out[12]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT13 = 224, //!< evtgen[0].tr_out[13]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT14 = 225, //!< evtgen[0].tr_out[14]
    _CYHAL_TRIGGER_EVTGEN0_TR_OUT15 = 226, //!< evtgen[0].tr_out[15]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0 = 227, //!< pass[0].tr_sar_ch_done[0]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1 = 228, //!< pass[0].tr_sar_ch_done[1]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2 = 229, //!< pass[0].tr_sar_ch_done[2]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3 = 230, //!< pass[0].tr_sar_ch_done[3]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4 = 231, //!< pass[0].tr_sar_ch_done[4]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5 = 232, //!< pass[0].tr_sar_ch_done[5]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6 = 233, //!< pass[0].tr_sar_ch_done[6]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7 = 234, //!< pass[0].tr_sar_ch_done[7]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8 = 235, //!< pass[0].tr_sar_ch_done[8]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9 = 236, //!< pass[0].tr_sar_ch_done[9]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10 = 237, //!< pass[0].tr_sar_ch_done[10]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11 = 238, //!< pass[0].tr_sar_ch_done[11]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12 = 239, //!< pass[0].tr_sar_ch_done[12]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13 = 240, //!< pass[0].tr_sar_ch_done[13]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14 = 241, //!< pass[0].tr_sar_ch_done[14]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15 = 242, //!< pass[0].tr_sar_ch_done[15]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16 = 243, //!< pass[0].tr_sar_ch_done[16]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17 = 244, //!< pass[0].tr_sar_ch_done[17]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18 = 245, //!< pass[0].tr_sar_ch_done[18]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19 = 246, //!< pass[0].tr_sar_ch_done[19]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20 = 247, //!< pass[0].tr_sar_ch_done[20]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21 = 248, //!< pass[0].tr_sar_ch_done[21]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22 = 249, //!< pass[0].tr_sar_ch_done[22]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23 = 250, //!< pass[0].tr_sar_ch_done[23]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24 = 251, //!< pass[0].tr_sar_ch_done[24]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25 = 252, //!< pass[0].tr_sar_ch_done[25]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26 = 253, //!< pass[0].tr_sar_ch_done[26]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27 = 254, //!< pass[0].tr_sar_ch_done[27]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28 = 255, //!< pass[0].tr_sar_ch_done[28]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29 = 256, //!< pass[0].tr_sar_ch_done[29]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30 = 257, //!< pass[0].tr_sar_ch_done[30]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31 = 258, //!< pass[0].tr_sar_ch_done[31]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32 = 259, //!< pass[0].tr_sar_ch_done[32]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33 = 260, //!< pass[0].tr_sar_ch_done[33]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34 = 261, //!< pass[0].tr_sar_ch_done[34]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35 = 262, //!< pass[0].tr_sar_ch_done[35]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36 = 263, //!< pass[0].tr_sar_ch_done[36]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37 = 264, //!< pass[0].tr_sar_ch_done[37]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38 = 265, //!< pass[0].tr_sar_ch_done[38]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39 = 266, //!< pass[0].tr_sar_ch_done[39]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40 = 267, //!< pass[0].tr_sar_ch_done[40]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41 = 268, //!< pass[0].tr_sar_ch_done[41]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42 = 269, //!< pass[0].tr_sar_ch_done[42]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43 = 270, //!< pass[0].tr_sar_ch_done[43]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44 = 271, //!< pass[0].tr_sar_ch_done[44]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45 = 272, //!< pass[0].tr_sar_ch_done[45]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46 = 273, //!< pass[0].tr_sar_ch_done[46]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47 = 274, //!< pass[0].tr_sar_ch_done[47]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48 = 275, //!< pass[0].tr_sar_ch_done[48]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49 = 276, //!< pass[0].tr_sar_ch_done[49]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50 = 277, //!< pass[0].tr_sar_ch_done[50]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51 = 278, //!< pass[0].tr_sar_ch_done[51]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52 = 279, //!< pass[0].tr_sar_ch_done[52]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53 = 280, //!< pass[0].tr_sar_ch_done[53]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54 = 281, //!< pass[0].tr_sar_ch_done[54]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55 = 282, //!< pass[0].tr_sar_ch_done[55]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56 = 283, //!< pass[0].tr_sar_ch_done[56]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57 = 284, //!< pass[0].tr_sar_ch_done[57]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58 = 285, //!< pass[0].tr_sar_ch_done[58]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59 = 286, //!< pass[0].tr_sar_ch_done[59]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60 = 287, //!< pass[0].tr_sar_ch_done[60]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61 = 288, //!< pass[0].tr_sar_ch_done[61]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62 = 289, //!< pass[0].tr_sar_ch_done[62]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63 = 290, //!< pass[0].tr_sar_ch_done[63]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64 = 291, //!< pass[0].tr_sar_ch_done[64]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65 = 292, //!< pass[0].tr_sar_ch_done[65]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66 = 293, //!< pass[0].tr_sar_ch_done[66]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67 = 294, //!< pass[0].tr_sar_ch_done[67]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68 = 295, //!< pass[0].tr_sar_ch_done[68]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69 = 296, //!< pass[0].tr_sar_ch_done[69]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70 = 297, //!< pass[0].tr_sar_ch_done[70]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71 = 298, //!< pass[0].tr_sar_ch_done[71]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO0 = 299, //!< pass[0].tr_sar_ch_rangevio[0]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO1 = 300, //!< pass[0].tr_sar_ch_rangevio[1]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO2 = 301, //!< pass[0].tr_sar_ch_rangevio[2]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO3 = 302, //!< pass[0].tr_sar_ch_rangevio[3]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO4 = 303, //!< pass[0].tr_sar_ch_rangevio[4]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO5 = 304, //!< pass[0].tr_sar_ch_rangevio[5]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO6 = 305, //!< pass[0].tr_sar_ch_rangevio[6]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO7 = 306, //!< pass[0].tr_sar_ch_rangevio[7]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO8 = 307, //!< pass[0].tr_sar_ch_rangevio[8]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO9 = 308, //!< pass[0].tr_sar_ch_rangevio[9]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO10 = 309, //!< pass[0].tr_sar_ch_rangevio[10]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO11 = 310, //!< pass[0].tr_sar_ch_rangevio[11]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO12 = 311, //!< pass[0].tr_sar_ch_rangevio[12]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO13 = 312, //!< pass[0].tr_sar_ch_rangevio[13]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO14 = 313, //!< pass[0].tr_sar_ch_rangevio[14]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO15 = 314, //!< pass[0].tr_sar_ch_rangevio[15]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO16 = 315, //!< pass[0].tr_sar_ch_rangevio[16]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO17 = 316, //!< pass[0].tr_sar_ch_rangevio[17]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO18 = 317, //!< pass[0].tr_sar_ch_rangevio[18]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO19 = 318, //!< pass[0].tr_sar_ch_rangevio[19]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO20 = 319, //!< pass[0].tr_sar_ch_rangevio[20]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO21 = 320, //!< pass[0].tr_sar_ch_rangevio[21]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO22 = 321, //!< pass[0].tr_sar_ch_rangevio[22]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO23 = 322, //!< pass[0].tr_sar_ch_rangevio[23]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO24 = 323, //!< pass[0].tr_sar_ch_rangevio[24]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO25 = 324, //!< pass[0].tr_sar_ch_rangevio[25]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO26 = 325, //!< pass[0].tr_sar_ch_rangevio[26]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO27 = 326, //!< pass[0].tr_sar_ch_rangevio[27]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO28 = 327, //!< pass[0].tr_sar_ch_rangevio[28]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO29 = 328, //!< pass[0].tr_sar_ch_rangevio[29]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO30 = 329, //!< pass[0].tr_sar_ch_rangevio[30]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO31 = 330, //!< pass[0].tr_sar_ch_rangevio[31]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO32 = 331, //!< pass[0].tr_sar_ch_rangevio[32]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO33 = 332, //!< pass[0].tr_sar_ch_rangevio[33]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO34 = 333, //!< pass[0].tr_sar_ch_rangevio[34]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO35 = 334, //!< pass[0].tr_sar_ch_rangevio[35]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO36 = 335, //!< pass[0].tr_sar_ch_rangevio[36]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO37 = 336, //!< pass[0].tr_sar_ch_rangevio[37]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO38 = 337, //!< pass[0].tr_sar_ch_rangevio[38]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO39 = 338, //!< pass[0].tr_sar_ch_rangevio[39]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO40 = 339, //!< pass[0].tr_sar_ch_rangevio[40]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO41 = 340, //!< pass[0].tr_sar_ch_rangevio[41]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO42 = 341, //!< pass[0].tr_sar_ch_rangevio[42]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO43 = 342, //!< pass[0].tr_sar_ch_rangevio[43]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO44 = 343, //!< pass[0].tr_sar_ch_rangevio[44]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO45 = 344, //!< pass[0].tr_sar_ch_rangevio[45]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO46 = 345, //!< pass[0].tr_sar_ch_rangevio[46]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO47 = 346, //!< pass[0].tr_sar_ch_rangevio[47]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO48 = 347, //!< pass[0].tr_sar_ch_rangevio[48]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO49 = 348, //!< pass[0].tr_sar_ch_rangevio[49]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO50 = 349, //!< pass[0].tr_sar_ch_rangevio[50]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO51 = 350, //!< pass[0].tr_sar_ch_rangevio[51]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO52 = 351, //!< pass[0].tr_sar_ch_rangevio[52]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO53 = 352, //!< pass[0].tr_sar_ch_rangevio[53]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO54 = 353, //!< pass[0].tr_sar_ch_rangevio[54]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO55 = 354, //!< pass[0].tr_sar_ch_rangevio[55]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO56 = 355, //!< pass[0].tr_sar_ch_rangevio[56]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO57 = 356, //!< pass[0].tr_sar_ch_rangevio[57]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO58 = 357, //!< pass[0].tr_sar_ch_rangevio[58]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO59 = 358, //!< pass[0].tr_sar_ch_rangevio[59]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO60 = 359, //!< pass[0].tr_sar_ch_rangevio[60]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO61 = 360, //!< pass[0].tr_sar_ch_rangevio[61]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO62 = 361, //!< pass[0].tr_sar_ch_rangevio[62]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO63 = 362, //!< pass[0].tr_sar_ch_rangevio[63]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO64 = 363, //!< pass[0].tr_sar_ch_rangevio[64]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO65 = 364, //!< pass[0].tr_sar_ch_rangevio[65]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO66 = 365, //!< pass[0].tr_sar_ch_rangevio[66]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO67 = 366, //!< pass[0].tr_sar_ch_rangevio[67]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO68 = 367, //!< pass[0].tr_sar_ch_rangevio[68]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO69 = 368, //!< pass[0].tr_sar_ch_rangevio[69]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO70 = 369, //!< pass[0].tr_sar_ch_rangevio[70]
    _CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO71 = 370, //!< pass[0].tr_sar_ch_rangevio[71]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0 = 371, //!< pass[0].tr_sar_gen_out[0]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1 = 372, //!< pass[0].tr_sar_gen_out[1]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2 = 373, //!< pass[0].tr_sar_gen_out[2]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3 = 374, //!< pass[0].tr_sar_gen_out[3]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4 = 375, //!< pass[0].tr_sar_gen_out[4]
    _CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5 = 376, //!< pass[0].tr_sar_gen_out[5]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT0 = 377, //!< peri.tr_io_input[0]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT1 = 378, //!< peri.tr_io_input[1]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT2 = 379, //!< peri.tr_io_input[2]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT3 = 380, //!< peri.tr_io_input[3]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT4 = 381, //!< peri.tr_io_input[4]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT5 = 382, //!< peri.tr_io_input[5]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT6 = 383, //!< peri.tr_io_input[6]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT7 = 384, //!< peri.tr_io_input[7]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT8 = 385, //!< peri.tr_io_input[8]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT9 = 386, //!< peri.tr_io_input[9]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT10 = 387, //!< peri.tr_io_input[10]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT11 = 388, //!< peri.tr_io_input[11]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT12 = 389, //!< peri.tr_io_input[12]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT13 = 390, //!< peri.tr_io_input[13]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT14 = 391, //!< peri.tr_io_input[14]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT15 = 392, //!< peri.tr_io_input[15]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT16 = 393, //!< peri.tr_io_input[16]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT17 = 394, //!< peri.tr_io_input[17]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT18 = 395, //!< peri.tr_io_input[18]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT19 = 396, //!< peri.tr_io_input[19]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT20 = 397, //!< peri.tr_io_input[20]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT21 = 398, //!< peri.tr_io_input[21]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT22 = 399, //!< peri.tr_io_input[22]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT23 = 400, //!< peri.tr_io_input[23]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT24 = 401, //!< peri.tr_io_input[24]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT25 = 402, //!< peri.tr_io_input[25]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT26 = 403, //!< peri.tr_io_input[26]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT27 = 404, //!< peri.tr_io_input[27]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT28 = 405, //!< peri.tr_io_input[28]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT29 = 406, //!< peri.tr_io_input[29]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT30 = 407, //!< peri.tr_io_input[30]
    _CYHAL_TRIGGER_PERI_TR_IO_INPUT31 = 408, //!< peri.tr_io_input[31]
    _CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED = 409, //!< scb[0].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB1_TR_I2C_SCL_FILTERED = 410, //!< scb[1].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED = 411, //!< scb[2].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB3_TR_I2C_SCL_FILTERED = 412, //!< scb[3].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB4_TR_I2C_SCL_FILTERED = 413, //!< scb[4].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB5_TR_I2C_SCL_FILTERED = 414, //!< scb[5].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB6_TR_I2C_SCL_FILTERED = 415, //!< scb[6].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB7_TR_I2C_SCL_FILTERED = 416, //!< scb[7].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB8_TR_I2C_SCL_FILTERED = 417, //!< scb[8].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB9_TR_I2C_SCL_FILTERED = 418, //!< scb[9].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB10_TR_I2C_SCL_FILTERED = 419, //!< scb[10].tr_i2c_scl_filtered
    _CYHAL_TRIGGER_SCB0_TR_RX_REQ = 420, //!< scb[0].tr_rx_req
    _CYHAL_TRIGGER_SCB1_TR_RX_REQ = 421, //!< scb[1].tr_rx_req
    _CYHAL_TRIGGER_SCB2_TR_RX_REQ = 422, //!< scb[2].tr_rx_req
    _CYHAL_TRIGGER_SCB3_TR_RX_REQ = 423, //!< scb[3].tr_rx_req
    _CYHAL_TRIGGER_SCB4_TR_RX_REQ = 424, //!< scb[4].tr_rx_req
    _CYHAL_TRIGGER_SCB5_TR_RX_REQ = 425, //!< scb[5].tr_rx_req
    _CYHAL_TRIGGER_SCB6_TR_RX_REQ = 426, //!< scb[6].tr_rx_req
    _CYHAL_TRIGGER_SCB7_TR_RX_REQ = 427, //!< scb[7].tr_rx_req
    _CYHAL_TRIGGER_SCB8_TR_RX_REQ = 428, //!< scb[8].tr_rx_req
    _CYHAL_TRIGGER_SCB9_TR_RX_REQ = 429, //!< scb[9].tr_rx_req
    _CYHAL_TRIGGER_SCB10_TR_RX_REQ = 430, //!< scb[10].tr_rx_req
    _CYHAL_TRIGGER_SCB0_TR_TX_REQ = 431, //!< scb[0].tr_tx_req
    _CYHAL_TRIGGER_SCB1_TR_TX_REQ = 432, //!< scb[1].tr_tx_req
    _CYHAL_TRIGGER_SCB2_TR_TX_REQ = 433, //!< scb[2].tr_tx_req
    _CYHAL_TRIGGER_SCB3_TR_TX_REQ = 434, //!< scb[3].tr_tx_req
    _CYHAL_TRIGGER_SCB4_TR_TX_REQ = 435, //!< scb[4].tr_tx_req
    _CYHAL_TRIGGER_SCB5_TR_TX_REQ = 436, //!< scb[5].tr_tx_req
    _CYHAL_TRIGGER_SCB6_TR_TX_REQ = 437, //!< scb[6].tr_tx_req
    _CYHAL_TRIGGER_SCB7_TR_TX_REQ = 438, //!< scb[7].tr_tx_req
    _CYHAL_TRIGGER_SCB8_TR_TX_REQ = 439, //!< scb[8].tr_tx_req
    _CYHAL_TRIGGER_SCB9_TR_TX_REQ = 440, //!< scb[9].tr_tx_req
    _CYHAL_TRIGGER_SCB10_TR_TX_REQ = 441, //!< scb[10].tr_tx_req
    _CYHAL_TRIGGER_SMIF0_TR_RX_REQ = 442, //!< smif[0].tr_rx_req
    _CYHAL_TRIGGER_SMIF0_TR_TX_REQ = 443, //!< smif[0].tr_tx_req
    _CYHAL_TRIGGER_TCPWM0_TR_OUT00 = 444, //!< tcpwm[0].tr_out0[0]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT01 = 445, //!< tcpwm[0].tr_out0[1]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT02 = 446, //!< tcpwm[0].tr_out0[2]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT03 = 447, //!< tcpwm[0].tr_out0[3]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT04 = 448, //!< tcpwm[0].tr_out0[4]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT05 = 449, //!< tcpwm[0].tr_out0[5]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT06 = 450, //!< tcpwm[0].tr_out0[6]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT07 = 451, //!< tcpwm[0].tr_out0[7]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT08 = 452, //!< tcpwm[0].tr_out0[8]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT09 = 453, //!< tcpwm[0].tr_out0[9]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT010 = 454, //!< tcpwm[0].tr_out0[10]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT011 = 455, //!< tcpwm[0].tr_out0[11]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT012 = 456, //!< tcpwm[0].tr_out0[12]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT013 = 457, //!< tcpwm[0].tr_out0[13]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT014 = 458, //!< tcpwm[0].tr_out0[14]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT015 = 459, //!< tcpwm[0].tr_out0[15]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT016 = 460, //!< tcpwm[0].tr_out0[16]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT017 = 461, //!< tcpwm[0].tr_out0[17]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT018 = 462, //!< tcpwm[0].tr_out0[18]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT019 = 463, //!< tcpwm[0].tr_out0[19]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT020 = 464, //!< tcpwm[0].tr_out0[20]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT021 = 465, //!< tcpwm[0].tr_out0[21]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT022 = 466, //!< tcpwm[0].tr_out0[22]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT023 = 467, //!< tcpwm[0].tr_out0[23]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT024 = 468, //!< tcpwm[0].tr_out0[24]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT025 = 469, //!< tcpwm[0].tr_out0[25]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT026 = 470, //!< tcpwm[0].tr_out0[26]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT027 = 471, //!< tcpwm[0].tr_out0[27]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT028 = 472, //!< tcpwm[0].tr_out0[28]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT029 = 473, //!< tcpwm[0].tr_out0[29]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT030 = 474, //!< tcpwm[0].tr_out0[30]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT031 = 475, //!< tcpwm[0].tr_out0[31]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT032 = 476, //!< tcpwm[0].tr_out0[32]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT033 = 477, //!< tcpwm[0].tr_out0[33]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT034 = 478, //!< tcpwm[0].tr_out0[34]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT035 = 479, //!< tcpwm[0].tr_out0[35]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT036 = 480, //!< tcpwm[0].tr_out0[36]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT037 = 481, //!< tcpwm[0].tr_out0[37]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT038 = 482, //!< tcpwm[0].tr_out0[38]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT039 = 483, //!< tcpwm[0].tr_out0[39]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT040 = 484, //!< tcpwm[0].tr_out0[40]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT041 = 485, //!< tcpwm[0].tr_out0[41]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT042 = 486, //!< tcpwm[0].tr_out0[42]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT043 = 487, //!< tcpwm[0].tr_out0[43]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT044 = 488, //!< tcpwm[0].tr_out0[44]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT045 = 489, //!< tcpwm[0].tr_out0[45]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT046 = 490, //!< tcpwm[0].tr_out0[46]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT047 = 491, //!< tcpwm[0].tr_out0[47]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT048 = 492, //!< tcpwm[0].tr_out0[48]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT049 = 493, //!< tcpwm[0].tr_out0[49]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT050 = 494, //!< tcpwm[0].tr_out0[50]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT051 = 495, //!< tcpwm[0].tr_out0[51]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT052 = 496, //!< tcpwm[0].tr_out0[52]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT053 = 497, //!< tcpwm[0].tr_out0[53]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT054 = 498, //!< tcpwm[0].tr_out0[54]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT055 = 499, //!< tcpwm[0].tr_out0[55]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT056 = 500, //!< tcpwm[0].tr_out0[56]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT057 = 501, //!< tcpwm[0].tr_out0[57]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT058 = 502, //!< tcpwm[0].tr_out0[58]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT059 = 503, //!< tcpwm[0].tr_out0[59]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT060 = 504, //!< tcpwm[0].tr_out0[60]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT061 = 505, //!< tcpwm[0].tr_out0[61]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT062 = 506, //!< tcpwm[0].tr_out0[62]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0256 = 507, //!< tcpwm[0].tr_out0[256]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0257 = 508, //!< tcpwm[0].tr_out0[257]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0258 = 509, //!< tcpwm[0].tr_out0[258]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0259 = 510, //!< tcpwm[0].tr_out0[259]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0260 = 511, //!< tcpwm[0].tr_out0[260]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0261 = 512, //!< tcpwm[0].tr_out0[261]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0262 = 513, //!< tcpwm[0].tr_out0[262]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0263 = 514, //!< tcpwm[0].tr_out0[263]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0264 = 515, //!< tcpwm[0].tr_out0[264]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0265 = 516, //!< tcpwm[0].tr_out0[265]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0266 = 517, //!< tcpwm[0].tr_out0[266]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0267 = 518, //!< tcpwm[0].tr_out0[267]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0512 = 519, //!< tcpwm[0].tr_out0[512]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0513 = 520, //!< tcpwm[0].tr_out0[513]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0514 = 521, //!< tcpwm[0].tr_out0[514]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0515 = 522, //!< tcpwm[0].tr_out0[515]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0516 = 523, //!< tcpwm[0].tr_out0[516]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0517 = 524, //!< tcpwm[0].tr_out0[517]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0518 = 525, //!< tcpwm[0].tr_out0[518]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT0519 = 526, //!< tcpwm[0].tr_out0[519]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT10 = 527, //!< tcpwm[0].tr_out1[0]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT11 = 528, //!< tcpwm[0].tr_out1[1]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT12 = 529, //!< tcpwm[0].tr_out1[2]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT13 = 530, //!< tcpwm[0].tr_out1[3]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT14 = 531, //!< tcpwm[0].tr_out1[4]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT15 = 532, //!< tcpwm[0].tr_out1[5]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT16 = 533, //!< tcpwm[0].tr_out1[6]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT17 = 534, //!< tcpwm[0].tr_out1[7]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT18 = 535, //!< tcpwm[0].tr_out1[8]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT19 = 536, //!< tcpwm[0].tr_out1[9]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT110 = 537, //!< tcpwm[0].tr_out1[10]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT111 = 538, //!< tcpwm[0].tr_out1[11]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT112 = 539, //!< tcpwm[0].tr_out1[12]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT113 = 540, //!< tcpwm[0].tr_out1[13]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT114 = 541, //!< tcpwm[0].tr_out1[14]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT115 = 542, //!< tcpwm[0].tr_out1[15]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT116 = 543, //!< tcpwm[0].tr_out1[16]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT117 = 544, //!< tcpwm[0].tr_out1[17]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT118 = 545, //!< tcpwm[0].tr_out1[18]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT119 = 546, //!< tcpwm[0].tr_out1[19]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT120 = 547, //!< tcpwm[0].tr_out1[20]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT121 = 548, //!< tcpwm[0].tr_out1[21]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT122 = 549, //!< tcpwm[0].tr_out1[22]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT123 = 550, //!< tcpwm[0].tr_out1[23]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT124 = 551, //!< tcpwm[0].tr_out1[24]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT125 = 552, //!< tcpwm[0].tr_out1[25]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT126 = 553, //!< tcpwm[0].tr_out1[26]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT127 = 554, //!< tcpwm[0].tr_out1[27]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT128 = 555, //!< tcpwm[0].tr_out1[28]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT129 = 556, //!< tcpwm[0].tr_out1[29]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT130 = 557, //!< tcpwm[0].tr_out1[30]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT131 = 558, //!< tcpwm[0].tr_out1[31]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT132 = 559, //!< tcpwm[0].tr_out1[32]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT133 = 560, //!< tcpwm[0].tr_out1[33]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT134 = 561, //!< tcpwm[0].tr_out1[34]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT135 = 562, //!< tcpwm[0].tr_out1[35]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT136 = 563, //!< tcpwm[0].tr_out1[36]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT137 = 564, //!< tcpwm[0].tr_out1[37]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT138 = 565, //!< tcpwm[0].tr_out1[38]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT139 = 566, //!< tcpwm[0].tr_out1[39]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT140 = 567, //!< tcpwm[0].tr_out1[40]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT141 = 568, //!< tcpwm[0].tr_out1[41]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT142 = 569, //!< tcpwm[0].tr_out1[42]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT143 = 570, //!< tcpwm[0].tr_out1[43]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT144 = 571, //!< tcpwm[0].tr_out1[44]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT145 = 572, //!< tcpwm[0].tr_out1[45]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT146 = 573, //!< tcpwm[0].tr_out1[46]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT147 = 574, //!< tcpwm[0].tr_out1[47]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT148 = 575, //!< tcpwm[0].tr_out1[48]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT149 = 576, //!< tcpwm[0].tr_out1[49]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT150 = 577, //!< tcpwm[0].tr_out1[50]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT151 = 578, //!< tcpwm[0].tr_out1[51]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT152 = 579, //!< tcpwm[0].tr_out1[52]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT153 = 580, //!< tcpwm[0].tr_out1[53]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT154 = 581, //!< tcpwm[0].tr_out1[54]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT155 = 582, //!< tcpwm[0].tr_out1[55]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT156 = 583, //!< tcpwm[0].tr_out1[56]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT157 = 584, //!< tcpwm[0].tr_out1[57]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT158 = 585, //!< tcpwm[0].tr_out1[58]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT159 = 586, //!< tcpwm[0].tr_out1[59]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT160 = 587, //!< tcpwm[0].tr_out1[60]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT161 = 588, //!< tcpwm[0].tr_out1[61]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT162 = 589, //!< tcpwm[0].tr_out1[62]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1256 = 590, //!< tcpwm[0].tr_out1[256]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1257 = 591, //!< tcpwm[0].tr_out1[257]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1258 = 592, //!< tcpwm[0].tr_out1[258]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1259 = 593, //!< tcpwm[0].tr_out1[259]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1260 = 594, //!< tcpwm[0].tr_out1[260]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1261 = 595, //!< tcpwm[0].tr_out1[261]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1262 = 596, //!< tcpwm[0].tr_out1[262]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1263 = 597, //!< tcpwm[0].tr_out1[263]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1264 = 598, //!< tcpwm[0].tr_out1[264]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1265 = 599, //!< tcpwm[0].tr_out1[265]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1266 = 600, //!< tcpwm[0].tr_out1[266]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1267 = 601, //!< tcpwm[0].tr_out1[267]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1512 = 602, //!< tcpwm[0].tr_out1[512]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1513 = 603, //!< tcpwm[0].tr_out1[513]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1514 = 604, //!< tcpwm[0].tr_out1[514]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1515 = 605, //!< tcpwm[0].tr_out1[515]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1516 = 606, //!< tcpwm[0].tr_out1[516]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1517 = 607, //!< tcpwm[0].tr_out1[517]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1518 = 608, //!< tcpwm[0].tr_out1[518]
    _CYHAL_TRIGGER_TCPWM0_TR_OUT1519 = 609, //!< tcpwm[0].tr_out1[519]
    _CYHAL_TRIGGER_TR_GROUP10_OUTPUT0 = 610, //!< tr_group[10].output[0]
    _CYHAL_TRIGGER_TR_GROUP10_OUTPUT1 = 611, //!< tr_group[10].output[1]
    _CYHAL_TRIGGER_TR_GROUP10_OUTPUT2 = 612, //!< tr_group[10].output[2]
    _CYHAL_TRIGGER_TR_GROUP10_OUTPUT3 = 613, //!< tr_group[10].output[3]
    _CYHAL_TRIGGER_TR_GROUP10_OUTPUT4 = 614, //!< tr_group[10].output[4]
    _CYHAL_TRIGGER_TR_GROUP11_OUTPUT0 = 615, //!< tr_group[11].output[0]
    _CYHAL_TRIGGER_TR_GROUP11_OUTPUT1 = 616, //!< tr_group[11].output[1]
    _CYHAL_TRIGGER_TR_GROUP11_OUTPUT2 = 617, //!< tr_group[11].output[2]
    _CYHAL_TRIGGER_TR_GROUP11_OUTPUT3 = 618, //!< tr_group[11].output[3]
    _CYHAL_TRIGGER_TR_GROUP11_OUTPUT4 = 619, //!< tr_group[11].output[4]
    _CYHAL_TRIGGER_TR_GROUP12_OUTPUT0 = 620, //!< tr_group[12].output[0]
    _CYHAL_TRIGGER_TR_GROUP12_OUTPUT1 = 621, //!< tr_group[12].output[1]
    _CYHAL_TRIGGER_TR_GROUP12_OUTPUT2 = 622, //!< tr_group[12].output[2]
    _CYHAL_TRIGGER_TR_GROUP12_OUTPUT3 = 623, //!< tr_group[12].output[3]
    _CYHAL_TRIGGER_TR_GROUP12_OUTPUT4 = 624, //!< tr_group[12].output[4]
} _cyhal_trigger_source_xmc7100_t;

/** Typedef for internal device family specific trigger source to generic trigger source */
typedef _cyhal_trigger_source_xmc7100_t cyhal_internal_source_t;

/** @brief Get a public source signal type (cyhal_trigger_source_xmc7100_t) given an internal source signal and signal type */
#define _CYHAL_TRIGGER_CREATE_SOURCE(src, type)    ((src) << 1 | (type))
/** @brief Get an internal source signal (_cyhal_trigger_source_xmc7100_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_SIGNAL(src)      ((cyhal_internal_source_t)((src) >> 1))
/** @brief Get the signal type (cyhal_signal_type_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_TYPE(src)        ((cyhal_signal_type_t)((src) & 1))
/** \endcond */

/** @brief Name of each input trigger. */
typedef enum
{
    CYHAL_TRIGGER_CPUSS_ZERO_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.zero
    CYHAL_TRIGGER_CPUSS_ZERO_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_LEVEL), //!< cpuss.zero
    CYHAL_TRIGGER_AUDIOSS0_TR_I2S_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS0_TR_I2S_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[0].tr_i2s_rx_req
    CYHAL_TRIGGER_AUDIOSS1_TR_I2S_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS1_TR_I2S_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[1].tr_i2s_rx_req
    CYHAL_TRIGGER_AUDIOSS2_TR_I2S_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS2_TR_I2S_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[2].tr_i2s_rx_req
    CYHAL_TRIGGER_AUDIOSS0_TR_I2S_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS0_TR_I2S_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[0].tr_i2s_tx_req
    CYHAL_TRIGGER_AUDIOSS1_TR_I2S_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS1_TR_I2S_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[1].tr_i2s_tx_req
    CYHAL_TRIGGER_AUDIOSS2_TR_I2S_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_AUDIOSS2_TR_I2S_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< audioss[2].tr_i2s_tx_req
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_dbg_dma_req[0]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ1, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_dbg_dma_req[1]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ2, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_dbg_dma_req[2]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_REQ3, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_dbg_dma_req[3]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ0, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_dbg_dma_req[0]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ1, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_dbg_dma_req[1]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ2, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_dbg_dma_req[2]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_REQ3, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_dbg_dma_req[3]
    CYHAL_TRIGGER_CANFD0_TR_FIFO00 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO00, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo0[0]
    CYHAL_TRIGGER_CANFD0_TR_FIFO01 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO01, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo0[1]
    CYHAL_TRIGGER_CANFD0_TR_FIFO02 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO02, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo0[2]
    CYHAL_TRIGGER_CANFD0_TR_FIFO03 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO03, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo0[3]
    CYHAL_TRIGGER_CANFD1_TR_FIFO00 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO00, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo0[0]
    CYHAL_TRIGGER_CANFD1_TR_FIFO01 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO01, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo0[1]
    CYHAL_TRIGGER_CANFD1_TR_FIFO02 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO02, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo0[2]
    CYHAL_TRIGGER_CANFD1_TR_FIFO03 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO03, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo0[3]
    CYHAL_TRIGGER_CANFD0_TR_FIFO10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO10, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo1[0]
    CYHAL_TRIGGER_CANFD0_TR_FIFO11 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO11, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo1[1]
    CYHAL_TRIGGER_CANFD0_TR_FIFO12 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO12, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo1[2]
    CYHAL_TRIGGER_CANFD0_TR_FIFO13 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_FIFO13, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[0].tr_fifo1[3]
    CYHAL_TRIGGER_CANFD1_TR_FIFO10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO10, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo1[0]
    CYHAL_TRIGGER_CANFD1_TR_FIFO11 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO11, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo1[1]
    CYHAL_TRIGGER_CANFD1_TR_FIFO12 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO12, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo1[2]
    CYHAL_TRIGGER_CANFD1_TR_FIFO13 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_FIFO13, CYHAL_SIGNAL_TYPE_LEVEL), //!< canfd[1].tr_fifo1[3]
    CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[0].tr_tmp_rtp_out[0]
    CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[0].tr_tmp_rtp_out[1]
    CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[0].tr_tmp_rtp_out[2]
    CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD0_TR_TMP_RTP_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[0].tr_tmp_rtp_out[3]
    CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[1].tr_tmp_rtp_out[0]
    CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[1].tr_tmp_rtp_out[1]
    CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[1].tr_tmp_rtp_out[2]
    CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CANFD1_TR_TMP_RTP_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< canfd[1].tr_tmp_rtp_out[3]
    CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_CTI_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.cti_tr_out[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_CTI_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.cti_tr_out[1]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[0]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[1]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[2]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[3]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT4 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[4]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT5 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[5]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT6 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT6, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[6]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT7 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT7, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dmac_tr_out[7]
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
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT16 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT16, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[16]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT17 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT17, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[17]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT18 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT18, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[18]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT19 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT19, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[19]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT20 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT20, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[20]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT21 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT21, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[21]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT22 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT22, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[22]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT23 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT23, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[23]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT24 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT24, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[24]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT25 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT25, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[25]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT26 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT26, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[26]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT27 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT27, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[27]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT28 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT28, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[28]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT29 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT29, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[29]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT30 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT30, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[30]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT31 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT31, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[31]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT32 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT32, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[32]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT33 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT33, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[33]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT34 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT34, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[34]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT35 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT35, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[35]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT36 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT36, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[36]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT37 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT37, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[37]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT38 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT38, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[38]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT39 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT39, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[39]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT40 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT40, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[40]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT41 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT41, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[41]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT42 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT42, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[42]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT43 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT43, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[43]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT44 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT44, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[44]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT45 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT45, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[45]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT46 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT46, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[46]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT47 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT47, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[47]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT48 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT48, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[48]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT49 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT49, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[49]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT50 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT50, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[50]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT51 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT51, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[51]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT52 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT52, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[52]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT53 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT53, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[53]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT54 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT54, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[54]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT55 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT55, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[55]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT56 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT56, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[56]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT57 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT57, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[57]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT58 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT58, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[58]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT59 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT59, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[59]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT60 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT60, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[60]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT61 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT61, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[61]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT62 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT62, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[62]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT63 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT63, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[63]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT64 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT64, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[64]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT65 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT65, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[65]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT66 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT66, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[66]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT67 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT67, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[67]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT68 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT68, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[68]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT69 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT69, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[69]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT70 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT70, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[70]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT71 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT71, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[71]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT72 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT72, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[72]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT73 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT73, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[73]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT74 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT74, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[74]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT75 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT75, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[75]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT76 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT76, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[76]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT77 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT77, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[77]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT78 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT78, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[78]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT79 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT79, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[79]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT80 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT80, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[80]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT81 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT81, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[81]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT82 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT82, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[82]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT83 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT83, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[83]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT84 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT84, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[84]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT85 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT85, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[85]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT86 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT86, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[86]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT87 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT87, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[87]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT88 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT88, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[88]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT89 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT89, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[89]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT90 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT90, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[90]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT91 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT91, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[91]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT92 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT92, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[92]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT93 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT93, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[93]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT94 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT94, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[94]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT95 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT95, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[95]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT96 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT96, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[96]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT97 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT97, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[97]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT98 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT98, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[98]
    CYHAL_TRIGGER_CPUSS_DW0_TR_OUT99 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT99, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw0_tr_out[99]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[0]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[1]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[2]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[3]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT4 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[4]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT5 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[5]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT6 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT6, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[6]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT7 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT7, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[7]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT8 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT8, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[8]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT9 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT9, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[9]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[10]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT11 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[11]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT12 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT12, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[12]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT13 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT13, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[13]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT14 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT14, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[14]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT15 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT15, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[15]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT16 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT16, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[16]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT17 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT17, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[17]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT18 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT18, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[18]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT19 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT19, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[19]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT20 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT20, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[20]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT21 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT21, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[21]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT22 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT22, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[22]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT23 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT23, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[23]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT24 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT24, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[24]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT25 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT25, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[25]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT26 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT26, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[26]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT27 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT27, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[27]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT28 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT28, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[28]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT29 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT29, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[29]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT30 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT30, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[30]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT31 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT31, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[31]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT32 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT32, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[32]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT33 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT33, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[33]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT34 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT34, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[34]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT35 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT35, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[35]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT36 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT36, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[36]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT37 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT37, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[37]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT38 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT38, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[38]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT39 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT39, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[39]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT40 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT40, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[40]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT41 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT41, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[41]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT42 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT42, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[42]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT43 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT43, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[43]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT44 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT44, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[44]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT45 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT45, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[45]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT46 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT46, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[46]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT47 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT47, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[47]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT48 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT48, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[48]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT49 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT49, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[49]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT50 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT50, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[50]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT51 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT51, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[51]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT52 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT52, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[52]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT53 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT53, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[53]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT54 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT54, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[54]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT55 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT55, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[55]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT56 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT56, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[56]
    CYHAL_TRIGGER_CPUSS_DW1_TR_OUT57 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW1_TR_OUT57, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.dw1_tr_out[57]
    CYHAL_TRIGGER_CPUSS_TR_FAULT0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_TR_FAULT0, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.tr_fault[0]
    CYHAL_TRIGGER_CPUSS_TR_FAULT1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_TR_FAULT1, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.tr_fault[1]
    CYHAL_TRIGGER_CPUSS_TR_FAULT2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_TR_FAULT2, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.tr_fault[2]
    CYHAL_TRIGGER_CPUSS_TR_FAULT3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_TR_FAULT3, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.tr_fault[3]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[0]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[0]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[1]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[1]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[2]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[2]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[3]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[3]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[4]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[4]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[5]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT5, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[5]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT6_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT6, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[6]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT6_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT6, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[6]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT7_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT7, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[7]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT7_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT7, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[7]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT8_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT8, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[8]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT8_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT8, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[8]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT9_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT9, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[9]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT9_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT9, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[9]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT10_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[10]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT10_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT10, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[10]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT11_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[11]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT11_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT11, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[11]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT12_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT12, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[12]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT12_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT12, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[12]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT13_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT13, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[13]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT13_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT13, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[13]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT14_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT14, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[14]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT14_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT14, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[14]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT15_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT15, CYHAL_SIGNAL_TYPE_EDGE), //!< evtgen[0].tr_out[15]
    CYHAL_TRIGGER_EVTGEN0_TR_OUT15_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_EVTGEN0_TR_OUT15, CYHAL_SIGNAL_TYPE_LEVEL), //!< evtgen[0].tr_out[15]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[6]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[6]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[7]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[7]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[8]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[8]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[9]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[9]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[10]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[10]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[11]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[11]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[12]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[12]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[13]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[13]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[14]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[14]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[15]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[15]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[16]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[16]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[17]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[17]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[18]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[18]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[19]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[19]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[20]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[20]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[21]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[21]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[22]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[22]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[23]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[23]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[24]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[24]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[25]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[25]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[26]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[26]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[27]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[27]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[28]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[28]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[29]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[29]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[30]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[30]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[31]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[31]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[32]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[32]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[33]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[33]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[34]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[34]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[35]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[35]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[36]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[36]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[37]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[37]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[38]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[38]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[39]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[39]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[40]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[40]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[41]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[41]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[42]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[42]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[43]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[43]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[44]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[44]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[45]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[45]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[46]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[46]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[47]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[47]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[48]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[48]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[49]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[49]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[50]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[50]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[51]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[51]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[52]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[52]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[53]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[53]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[54]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[54]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[55]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[55]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[56]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[56]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[57]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[57]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[58]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[58]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[59]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[59]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[60]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[60]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[61]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[61]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[62]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[62]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[63]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[63]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[64]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[64]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[65]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[65]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[66]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[66]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[67]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[67]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[68]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[68]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[69]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[69]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[70]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[70]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_done[71]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_ch_done[71]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO0 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO0, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO1 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO1, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO2 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO2, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO3 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO3, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO4 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO4, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO5 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO5, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO6 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO6, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[6]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO7 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO7, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[7]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO8 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO8, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[8]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO9 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO9, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[9]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO10 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO10, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[10]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO11 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO11, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[11]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO12 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO12, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[12]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO13 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO13, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[13]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO14 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO14, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[14]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO15 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO15, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[15]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO16 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO16, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[16]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO17 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO17, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[17]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO18 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO18, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[18]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO19 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO19, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[19]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO20 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO20, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[20]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO21 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO21, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[21]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO22 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO22, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[22]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO23 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO23, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[23]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO24 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO24, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[24]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO25 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO25, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[25]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO26 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO26, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[26]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO27 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO27, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[27]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO28 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO28, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[28]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO29 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO29, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[29]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO30 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO30, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[30]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO31 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO31, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[31]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO32 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO32, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[32]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO33 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO33, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[33]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO34 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO34, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[34]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO35 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO35, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[35]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO36 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO36, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[36]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO37 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO37, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[37]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO38 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO38, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[38]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO39 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO39, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[39]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO40 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO40, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[40]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO41 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO41, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[41]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO42 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO42, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[42]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO43 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO43, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[43]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO44 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO44, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[44]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO45 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO45, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[45]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO46 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO46, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[46]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO47 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO47, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[47]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO48 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO48, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[48]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO49 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO49, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[49]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO50 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO50, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[50]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO51 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO51, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[51]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO52 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO52, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[52]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO53 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO53, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[53]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO54 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO54, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[54]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO55 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO55, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[55]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO56 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO56, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[56]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO57 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO57, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[57]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO58 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO58, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[58]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO59 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO59, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[59]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO60 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO60, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[60]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO61 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO61, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[61]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO62 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO62, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[62]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO63 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO63, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[63]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO64 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO64, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[64]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO65 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO65, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[65]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO66 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO66, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[66]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO67 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO67, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[67]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO68 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO68, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[68]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO69 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO69, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[69]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO70 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO70, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[70]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO71 = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_CH_RANGEVIO71, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_ch_rangevio[71]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_gen_out[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_gen_out[5]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[0]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[0]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[1]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[1]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[2]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[2]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[3]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[3]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[4]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[4]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT5, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[5]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT5, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[5]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT6_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT6, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[6]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT6_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT6, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[6]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT7_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT7, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[7]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT7_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT7, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[7]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT8_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT8, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[8]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT8_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT8, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[8]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT9_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT9, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[9]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT9_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT9, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[9]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT10_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[10]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT10_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT10, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[10]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT11_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[11]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT11_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT11, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[11]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT12_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT12, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[12]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT12_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT12, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[12]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT13_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT13, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[13]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT13_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT13, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[13]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT14_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT14, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[14]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT14_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT14, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[14]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT15_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT15, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[15]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT15_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT15, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[15]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT16_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT16, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[16]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT16_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT16, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[16]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT17_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT17, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[17]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT17_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT17, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[17]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT18_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT18, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[18]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT18_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT18, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[18]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT19_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT19, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[19]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT19_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT19, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[19]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT20_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT20, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[20]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT20_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT20, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[20]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT21_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT21, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[21]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT21_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT21, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[21]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT22_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT22, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[22]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT22_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT22, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[22]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT23_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT23, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[23]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT23_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT23, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[23]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT24_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT24, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[24]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT24_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT24, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[24]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT25_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT25, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[25]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT25_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT25, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[25]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT26_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT26, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[26]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT26_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT26, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[26]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT27_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT27, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[27]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT27_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT27, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[27]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT28_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT28, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[28]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT28_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT28, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[28]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT29_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT29, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[29]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT29_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT29, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[29]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT30_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT30, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[30]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT30_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT30, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[30]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT31_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT31, CYHAL_SIGNAL_TYPE_EDGE), //!< peri.tr_io_input[31]
    CYHAL_TRIGGER_PERI_TR_IO_INPUT31_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PERI_TR_IO_INPUT31, CYHAL_SIGNAL_TYPE_LEVEL), //!< peri.tr_io_input[31]
    CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB1_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB1_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[1].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB3_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB3_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[3].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB4_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB4_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[4].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB5_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB5_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[5].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB6_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB6_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[6].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB7_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB7_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[7].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB8_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB8_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[8].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB9_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB9_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[9].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB10_TR_I2C_SCL_FILTERED = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB10_TR_I2C_SCL_FILTERED, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[10].tr_i2c_scl_filtered
    CYHAL_TRIGGER_SCB0_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_rx_req
    CYHAL_TRIGGER_SCB1_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB1_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[1].tr_rx_req
    CYHAL_TRIGGER_SCB2_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_rx_req
    CYHAL_TRIGGER_SCB3_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB3_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[3].tr_rx_req
    CYHAL_TRIGGER_SCB4_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB4_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[4].tr_rx_req
    CYHAL_TRIGGER_SCB5_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB5_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[5].tr_rx_req
    CYHAL_TRIGGER_SCB6_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB6_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[6].tr_rx_req
    CYHAL_TRIGGER_SCB7_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB7_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[7].tr_rx_req
    CYHAL_TRIGGER_SCB8_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB8_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[8].tr_rx_req
    CYHAL_TRIGGER_SCB9_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB9_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[9].tr_rx_req
    CYHAL_TRIGGER_SCB10_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB10_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[10].tr_rx_req
    CYHAL_TRIGGER_SCB0_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB0_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[0].tr_tx_req
    CYHAL_TRIGGER_SCB1_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB1_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[1].tr_tx_req
    CYHAL_TRIGGER_SCB2_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB2_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[2].tr_tx_req
    CYHAL_TRIGGER_SCB3_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB3_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[3].tr_tx_req
    CYHAL_TRIGGER_SCB4_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB4_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[4].tr_tx_req
    CYHAL_TRIGGER_SCB5_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB5_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[5].tr_tx_req
    CYHAL_TRIGGER_SCB6_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB6_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[6].tr_tx_req
    CYHAL_TRIGGER_SCB7_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB7_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[7].tr_tx_req
    CYHAL_TRIGGER_SCB8_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB8_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[8].tr_tx_req
    CYHAL_TRIGGER_SCB9_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB9_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[9].tr_tx_req
    CYHAL_TRIGGER_SCB10_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SCB10_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< scb[10].tr_tx_req
    CYHAL_TRIGGER_SMIF0_TR_RX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SMIF0_TR_RX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< smif[0].tr_rx_req
    CYHAL_TRIGGER_SMIF0_TR_TX_REQ = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_SMIF0_TR_TX_REQ, CYHAL_SIGNAL_TYPE_LEVEL), //!< smif[0].tr_tx_req
    CYHAL_TRIGGER_TCPWM0_TR_OUT00_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT00, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT00_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT00, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT01_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT01, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT01_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT01, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT02_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT02, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[2]
    CYHAL_TRIGGER_TCPWM0_TR_OUT02_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT02, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[2]
    CYHAL_TRIGGER_TCPWM0_TR_OUT03_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT03, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[3]
    CYHAL_TRIGGER_TCPWM0_TR_OUT03_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT03, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[3]
    CYHAL_TRIGGER_TCPWM0_TR_OUT04_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT04, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[4]
    CYHAL_TRIGGER_TCPWM0_TR_OUT04_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT04, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[4]
    CYHAL_TRIGGER_TCPWM0_TR_OUT05_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT05, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[5]
    CYHAL_TRIGGER_TCPWM0_TR_OUT05_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT05, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[5]
    CYHAL_TRIGGER_TCPWM0_TR_OUT06_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT06, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[6]
    CYHAL_TRIGGER_TCPWM0_TR_OUT06_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT06, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[6]
    CYHAL_TRIGGER_TCPWM0_TR_OUT07_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT07, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[7]
    CYHAL_TRIGGER_TCPWM0_TR_OUT07_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT07, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[7]
    CYHAL_TRIGGER_TCPWM0_TR_OUT08_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT08, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[8]
    CYHAL_TRIGGER_TCPWM0_TR_OUT08_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT08, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[8]
    CYHAL_TRIGGER_TCPWM0_TR_OUT09_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT09, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[9]
    CYHAL_TRIGGER_TCPWM0_TR_OUT09_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT09, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[9]
    CYHAL_TRIGGER_TCPWM0_TR_OUT010_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT010, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[10]
    CYHAL_TRIGGER_TCPWM0_TR_OUT010_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT010, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[10]
    CYHAL_TRIGGER_TCPWM0_TR_OUT011_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT011, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[11]
    CYHAL_TRIGGER_TCPWM0_TR_OUT011_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT011, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[11]
    CYHAL_TRIGGER_TCPWM0_TR_OUT012_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT012, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[12]
    CYHAL_TRIGGER_TCPWM0_TR_OUT012_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT012, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[12]
    CYHAL_TRIGGER_TCPWM0_TR_OUT013_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT013, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[13]
    CYHAL_TRIGGER_TCPWM0_TR_OUT013_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT013, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[13]
    CYHAL_TRIGGER_TCPWM0_TR_OUT014_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT014, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[14]
    CYHAL_TRIGGER_TCPWM0_TR_OUT014_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT014, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[14]
    CYHAL_TRIGGER_TCPWM0_TR_OUT015_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT015, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[15]
    CYHAL_TRIGGER_TCPWM0_TR_OUT015_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT015, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[15]
    CYHAL_TRIGGER_TCPWM0_TR_OUT016_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT016, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[16]
    CYHAL_TRIGGER_TCPWM0_TR_OUT016_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT016, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[16]
    CYHAL_TRIGGER_TCPWM0_TR_OUT017_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT017, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[17]
    CYHAL_TRIGGER_TCPWM0_TR_OUT017_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT017, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[17]
    CYHAL_TRIGGER_TCPWM0_TR_OUT018_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT018, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[18]
    CYHAL_TRIGGER_TCPWM0_TR_OUT018_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT018, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[18]
    CYHAL_TRIGGER_TCPWM0_TR_OUT019_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT019, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[19]
    CYHAL_TRIGGER_TCPWM0_TR_OUT019_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT019, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[19]
    CYHAL_TRIGGER_TCPWM0_TR_OUT020_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT020, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[20]
    CYHAL_TRIGGER_TCPWM0_TR_OUT020_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT020, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[20]
    CYHAL_TRIGGER_TCPWM0_TR_OUT021_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT021, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[21]
    CYHAL_TRIGGER_TCPWM0_TR_OUT021_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT021, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[21]
    CYHAL_TRIGGER_TCPWM0_TR_OUT022_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT022, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[22]
    CYHAL_TRIGGER_TCPWM0_TR_OUT022_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT022, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[22]
    CYHAL_TRIGGER_TCPWM0_TR_OUT023_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT023, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[23]
    CYHAL_TRIGGER_TCPWM0_TR_OUT023_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT023, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[23]
    CYHAL_TRIGGER_TCPWM0_TR_OUT024_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT024, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[24]
    CYHAL_TRIGGER_TCPWM0_TR_OUT024_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT024, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[24]
    CYHAL_TRIGGER_TCPWM0_TR_OUT025_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT025, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[25]
    CYHAL_TRIGGER_TCPWM0_TR_OUT025_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT025, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[25]
    CYHAL_TRIGGER_TCPWM0_TR_OUT026_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT026, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[26]
    CYHAL_TRIGGER_TCPWM0_TR_OUT026_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT026, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[26]
    CYHAL_TRIGGER_TCPWM0_TR_OUT027_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT027, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[27]
    CYHAL_TRIGGER_TCPWM0_TR_OUT027_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT027, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[27]
    CYHAL_TRIGGER_TCPWM0_TR_OUT028_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT028, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[28]
    CYHAL_TRIGGER_TCPWM0_TR_OUT028_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT028, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[28]
    CYHAL_TRIGGER_TCPWM0_TR_OUT029_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT029, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[29]
    CYHAL_TRIGGER_TCPWM0_TR_OUT029_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT029, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[29]
    CYHAL_TRIGGER_TCPWM0_TR_OUT030_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT030, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[30]
    CYHAL_TRIGGER_TCPWM0_TR_OUT030_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT030, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[30]
    CYHAL_TRIGGER_TCPWM0_TR_OUT031_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT031, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[31]
    CYHAL_TRIGGER_TCPWM0_TR_OUT031_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT031, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[31]
    CYHAL_TRIGGER_TCPWM0_TR_OUT032_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT032, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[32]
    CYHAL_TRIGGER_TCPWM0_TR_OUT032_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT032, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[32]
    CYHAL_TRIGGER_TCPWM0_TR_OUT033_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT033, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[33]
    CYHAL_TRIGGER_TCPWM0_TR_OUT033_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT033, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[33]
    CYHAL_TRIGGER_TCPWM0_TR_OUT034_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT034, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[34]
    CYHAL_TRIGGER_TCPWM0_TR_OUT034_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT034, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[34]
    CYHAL_TRIGGER_TCPWM0_TR_OUT035_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT035, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[35]
    CYHAL_TRIGGER_TCPWM0_TR_OUT035_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT035, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[35]
    CYHAL_TRIGGER_TCPWM0_TR_OUT036_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT036, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[36]
    CYHAL_TRIGGER_TCPWM0_TR_OUT036_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT036, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[36]
    CYHAL_TRIGGER_TCPWM0_TR_OUT037_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT037, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[37]
    CYHAL_TRIGGER_TCPWM0_TR_OUT037_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT037, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[37]
    CYHAL_TRIGGER_TCPWM0_TR_OUT038_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT038, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[38]
    CYHAL_TRIGGER_TCPWM0_TR_OUT038_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT038, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[38]
    CYHAL_TRIGGER_TCPWM0_TR_OUT039_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT039, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[39]
    CYHAL_TRIGGER_TCPWM0_TR_OUT039_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT039, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[39]
    CYHAL_TRIGGER_TCPWM0_TR_OUT040_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT040, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[40]
    CYHAL_TRIGGER_TCPWM0_TR_OUT040_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT040, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[40]
    CYHAL_TRIGGER_TCPWM0_TR_OUT041_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT041, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[41]
    CYHAL_TRIGGER_TCPWM0_TR_OUT041_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT041, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[41]
    CYHAL_TRIGGER_TCPWM0_TR_OUT042_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT042, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[42]
    CYHAL_TRIGGER_TCPWM0_TR_OUT042_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT042, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[42]
    CYHAL_TRIGGER_TCPWM0_TR_OUT043_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT043, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[43]
    CYHAL_TRIGGER_TCPWM0_TR_OUT043_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT043, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[43]
    CYHAL_TRIGGER_TCPWM0_TR_OUT044_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT044, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[44]
    CYHAL_TRIGGER_TCPWM0_TR_OUT044_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT044, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[44]
    CYHAL_TRIGGER_TCPWM0_TR_OUT045_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT045, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[45]
    CYHAL_TRIGGER_TCPWM0_TR_OUT045_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT045, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[45]
    CYHAL_TRIGGER_TCPWM0_TR_OUT046_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT046, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[46]
    CYHAL_TRIGGER_TCPWM0_TR_OUT046_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT046, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[46]
    CYHAL_TRIGGER_TCPWM0_TR_OUT047_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT047, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[47]
    CYHAL_TRIGGER_TCPWM0_TR_OUT047_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT047, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[47]
    CYHAL_TRIGGER_TCPWM0_TR_OUT048_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT048, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[48]
    CYHAL_TRIGGER_TCPWM0_TR_OUT048_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT048, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[48]
    CYHAL_TRIGGER_TCPWM0_TR_OUT049_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT049, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[49]
    CYHAL_TRIGGER_TCPWM0_TR_OUT049_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT049, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[49]
    CYHAL_TRIGGER_TCPWM0_TR_OUT050_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT050, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[50]
    CYHAL_TRIGGER_TCPWM0_TR_OUT050_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT050, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[50]
    CYHAL_TRIGGER_TCPWM0_TR_OUT051_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT051, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[51]
    CYHAL_TRIGGER_TCPWM0_TR_OUT051_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT051, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[51]
    CYHAL_TRIGGER_TCPWM0_TR_OUT052_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT052, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[52]
    CYHAL_TRIGGER_TCPWM0_TR_OUT052_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT052, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[52]
    CYHAL_TRIGGER_TCPWM0_TR_OUT053_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT053, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[53]
    CYHAL_TRIGGER_TCPWM0_TR_OUT053_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT053, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[53]
    CYHAL_TRIGGER_TCPWM0_TR_OUT054_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT054, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[54]
    CYHAL_TRIGGER_TCPWM0_TR_OUT054_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT054, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[54]
    CYHAL_TRIGGER_TCPWM0_TR_OUT055_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT055, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[55]
    CYHAL_TRIGGER_TCPWM0_TR_OUT055_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT055, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[55]
    CYHAL_TRIGGER_TCPWM0_TR_OUT056_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT056, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[56]
    CYHAL_TRIGGER_TCPWM0_TR_OUT056_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT056, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[56]
    CYHAL_TRIGGER_TCPWM0_TR_OUT057_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT057, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[57]
    CYHAL_TRIGGER_TCPWM0_TR_OUT057_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT057, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[57]
    CYHAL_TRIGGER_TCPWM0_TR_OUT058_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT058, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[58]
    CYHAL_TRIGGER_TCPWM0_TR_OUT058_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT058, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[58]
    CYHAL_TRIGGER_TCPWM0_TR_OUT059_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT059, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[59]
    CYHAL_TRIGGER_TCPWM0_TR_OUT059_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT059, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[59]
    CYHAL_TRIGGER_TCPWM0_TR_OUT060_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT060, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[60]
    CYHAL_TRIGGER_TCPWM0_TR_OUT060_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT060, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[60]
    CYHAL_TRIGGER_TCPWM0_TR_OUT061_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT061, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[61]
    CYHAL_TRIGGER_TCPWM0_TR_OUT061_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT061, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[61]
    CYHAL_TRIGGER_TCPWM0_TR_OUT062_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT062, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[62]
    CYHAL_TRIGGER_TCPWM0_TR_OUT062_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT062, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[62]
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
    CYHAL_TRIGGER_TCPWM0_TR_OUT0263_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0263, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[263]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0263_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0263, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[263]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0264_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0264, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[264]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0264_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0264, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[264]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0265_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0265, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[265]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0265_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0265, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[265]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0266_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0266, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[266]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0266_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0266, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[266]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0267_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0267, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[267]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0267_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0267, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[267]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0512_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0512, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[512]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0512_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0512, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[512]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0513_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0513, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[513]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0513_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0513, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[513]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0514_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0514, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[514]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0514_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0514, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[514]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0515_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0515, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[515]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0515_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0515, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[515]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0516_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0516, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[516]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0516_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0516, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[516]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0517_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0517, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[517]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0517_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0517, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[517]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0518_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0518, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[518]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0518_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0518, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[518]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0519_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0519, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out0[519]
    CYHAL_TRIGGER_TCPWM0_TR_OUT0519_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT0519, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out0[519]
    CYHAL_TRIGGER_TCPWM0_TR_OUT10_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT10, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT10_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT10, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[0]
    CYHAL_TRIGGER_TCPWM0_TR_OUT11_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT11, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT11_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT11, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[1]
    CYHAL_TRIGGER_TCPWM0_TR_OUT12_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT12, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[2]
    CYHAL_TRIGGER_TCPWM0_TR_OUT12_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT12, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[2]
    CYHAL_TRIGGER_TCPWM0_TR_OUT13_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT13, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[3]
    CYHAL_TRIGGER_TCPWM0_TR_OUT13_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT13, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[3]
    CYHAL_TRIGGER_TCPWM0_TR_OUT14_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT14, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[4]
    CYHAL_TRIGGER_TCPWM0_TR_OUT14_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT14, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[4]
    CYHAL_TRIGGER_TCPWM0_TR_OUT15_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT15, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[5]
    CYHAL_TRIGGER_TCPWM0_TR_OUT15_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT15, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[5]
    CYHAL_TRIGGER_TCPWM0_TR_OUT16_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT16, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[6]
    CYHAL_TRIGGER_TCPWM0_TR_OUT16_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT16, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[6]
    CYHAL_TRIGGER_TCPWM0_TR_OUT17_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT17, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[7]
    CYHAL_TRIGGER_TCPWM0_TR_OUT17_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT17, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[7]
    CYHAL_TRIGGER_TCPWM0_TR_OUT18_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT18, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[8]
    CYHAL_TRIGGER_TCPWM0_TR_OUT18_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT18, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[8]
    CYHAL_TRIGGER_TCPWM0_TR_OUT19_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT19, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[9]
    CYHAL_TRIGGER_TCPWM0_TR_OUT19_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT19, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[9]
    CYHAL_TRIGGER_TCPWM0_TR_OUT110_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT110, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[10]
    CYHAL_TRIGGER_TCPWM0_TR_OUT110_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT110, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[10]
    CYHAL_TRIGGER_TCPWM0_TR_OUT111_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT111, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[11]
    CYHAL_TRIGGER_TCPWM0_TR_OUT111_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT111, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[11]
    CYHAL_TRIGGER_TCPWM0_TR_OUT112_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT112, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[12]
    CYHAL_TRIGGER_TCPWM0_TR_OUT112_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT112, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[12]
    CYHAL_TRIGGER_TCPWM0_TR_OUT113_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT113, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[13]
    CYHAL_TRIGGER_TCPWM0_TR_OUT113_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT113, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[13]
    CYHAL_TRIGGER_TCPWM0_TR_OUT114_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT114, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[14]
    CYHAL_TRIGGER_TCPWM0_TR_OUT114_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT114, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[14]
    CYHAL_TRIGGER_TCPWM0_TR_OUT115_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT115, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[15]
    CYHAL_TRIGGER_TCPWM0_TR_OUT115_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT115, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[15]
    CYHAL_TRIGGER_TCPWM0_TR_OUT116_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT116, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[16]
    CYHAL_TRIGGER_TCPWM0_TR_OUT116_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT116, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[16]
    CYHAL_TRIGGER_TCPWM0_TR_OUT117_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT117, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[17]
    CYHAL_TRIGGER_TCPWM0_TR_OUT117_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT117, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[17]
    CYHAL_TRIGGER_TCPWM0_TR_OUT118_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT118, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[18]
    CYHAL_TRIGGER_TCPWM0_TR_OUT118_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT118, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[18]
    CYHAL_TRIGGER_TCPWM0_TR_OUT119_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT119, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[19]
    CYHAL_TRIGGER_TCPWM0_TR_OUT119_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT119, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[19]
    CYHAL_TRIGGER_TCPWM0_TR_OUT120_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT120, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[20]
    CYHAL_TRIGGER_TCPWM0_TR_OUT120_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT120, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[20]
    CYHAL_TRIGGER_TCPWM0_TR_OUT121_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT121, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[21]
    CYHAL_TRIGGER_TCPWM0_TR_OUT121_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT121, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[21]
    CYHAL_TRIGGER_TCPWM0_TR_OUT122_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT122, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[22]
    CYHAL_TRIGGER_TCPWM0_TR_OUT122_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT122, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[22]
    CYHAL_TRIGGER_TCPWM0_TR_OUT123_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT123, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[23]
    CYHAL_TRIGGER_TCPWM0_TR_OUT123_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT123, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[23]
    CYHAL_TRIGGER_TCPWM0_TR_OUT124_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT124, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[24]
    CYHAL_TRIGGER_TCPWM0_TR_OUT124_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT124, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[24]
    CYHAL_TRIGGER_TCPWM0_TR_OUT125_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT125, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[25]
    CYHAL_TRIGGER_TCPWM0_TR_OUT125_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT125, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[25]
    CYHAL_TRIGGER_TCPWM0_TR_OUT126_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT126, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[26]
    CYHAL_TRIGGER_TCPWM0_TR_OUT126_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT126, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[26]
    CYHAL_TRIGGER_TCPWM0_TR_OUT127_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT127, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[27]
    CYHAL_TRIGGER_TCPWM0_TR_OUT127_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT127, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[27]
    CYHAL_TRIGGER_TCPWM0_TR_OUT128_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT128, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[28]
    CYHAL_TRIGGER_TCPWM0_TR_OUT128_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT128, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[28]
    CYHAL_TRIGGER_TCPWM0_TR_OUT129_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT129, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[29]
    CYHAL_TRIGGER_TCPWM0_TR_OUT129_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT129, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[29]
    CYHAL_TRIGGER_TCPWM0_TR_OUT130_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT130, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[30]
    CYHAL_TRIGGER_TCPWM0_TR_OUT130_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT130, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[30]
    CYHAL_TRIGGER_TCPWM0_TR_OUT131_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT131, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[31]
    CYHAL_TRIGGER_TCPWM0_TR_OUT131_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT131, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[31]
    CYHAL_TRIGGER_TCPWM0_TR_OUT132_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT132, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[32]
    CYHAL_TRIGGER_TCPWM0_TR_OUT132_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT132, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[32]
    CYHAL_TRIGGER_TCPWM0_TR_OUT133_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT133, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[33]
    CYHAL_TRIGGER_TCPWM0_TR_OUT133_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT133, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[33]
    CYHAL_TRIGGER_TCPWM0_TR_OUT134_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT134, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[34]
    CYHAL_TRIGGER_TCPWM0_TR_OUT134_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT134, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[34]
    CYHAL_TRIGGER_TCPWM0_TR_OUT135_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT135, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[35]
    CYHAL_TRIGGER_TCPWM0_TR_OUT135_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT135, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[35]
    CYHAL_TRIGGER_TCPWM0_TR_OUT136_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT136, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[36]
    CYHAL_TRIGGER_TCPWM0_TR_OUT136_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT136, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[36]
    CYHAL_TRIGGER_TCPWM0_TR_OUT137_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT137, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[37]
    CYHAL_TRIGGER_TCPWM0_TR_OUT137_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT137, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[37]
    CYHAL_TRIGGER_TCPWM0_TR_OUT138_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT138, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[38]
    CYHAL_TRIGGER_TCPWM0_TR_OUT138_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT138, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[38]
    CYHAL_TRIGGER_TCPWM0_TR_OUT139_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT139, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[39]
    CYHAL_TRIGGER_TCPWM0_TR_OUT139_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT139, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[39]
    CYHAL_TRIGGER_TCPWM0_TR_OUT140_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT140, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[40]
    CYHAL_TRIGGER_TCPWM0_TR_OUT140_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT140, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[40]
    CYHAL_TRIGGER_TCPWM0_TR_OUT141_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT141, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[41]
    CYHAL_TRIGGER_TCPWM0_TR_OUT141_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT141, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[41]
    CYHAL_TRIGGER_TCPWM0_TR_OUT142_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT142, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[42]
    CYHAL_TRIGGER_TCPWM0_TR_OUT142_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT142, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[42]
    CYHAL_TRIGGER_TCPWM0_TR_OUT143_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT143, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[43]
    CYHAL_TRIGGER_TCPWM0_TR_OUT143_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT143, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[43]
    CYHAL_TRIGGER_TCPWM0_TR_OUT144_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT144, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[44]
    CYHAL_TRIGGER_TCPWM0_TR_OUT144_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT144, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[44]
    CYHAL_TRIGGER_TCPWM0_TR_OUT145_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT145, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[45]
    CYHAL_TRIGGER_TCPWM0_TR_OUT145_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT145, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[45]
    CYHAL_TRIGGER_TCPWM0_TR_OUT146_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT146, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[46]
    CYHAL_TRIGGER_TCPWM0_TR_OUT146_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT146, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[46]
    CYHAL_TRIGGER_TCPWM0_TR_OUT147_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT147, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[47]
    CYHAL_TRIGGER_TCPWM0_TR_OUT147_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT147, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[47]
    CYHAL_TRIGGER_TCPWM0_TR_OUT148_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT148, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[48]
    CYHAL_TRIGGER_TCPWM0_TR_OUT148_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT148, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[48]
    CYHAL_TRIGGER_TCPWM0_TR_OUT149_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT149, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[49]
    CYHAL_TRIGGER_TCPWM0_TR_OUT149_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT149, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[49]
    CYHAL_TRIGGER_TCPWM0_TR_OUT150_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT150, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[50]
    CYHAL_TRIGGER_TCPWM0_TR_OUT150_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT150, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[50]
    CYHAL_TRIGGER_TCPWM0_TR_OUT151_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT151, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[51]
    CYHAL_TRIGGER_TCPWM0_TR_OUT151_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT151, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[51]
    CYHAL_TRIGGER_TCPWM0_TR_OUT152_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT152, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[52]
    CYHAL_TRIGGER_TCPWM0_TR_OUT152_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT152, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[52]
    CYHAL_TRIGGER_TCPWM0_TR_OUT153_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT153, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[53]
    CYHAL_TRIGGER_TCPWM0_TR_OUT153_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT153, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[53]
    CYHAL_TRIGGER_TCPWM0_TR_OUT154_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT154, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[54]
    CYHAL_TRIGGER_TCPWM0_TR_OUT154_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT154, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[54]
    CYHAL_TRIGGER_TCPWM0_TR_OUT155_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT155, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[55]
    CYHAL_TRIGGER_TCPWM0_TR_OUT155_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT155, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[55]
    CYHAL_TRIGGER_TCPWM0_TR_OUT156_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT156, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[56]
    CYHAL_TRIGGER_TCPWM0_TR_OUT156_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT156, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[56]
    CYHAL_TRIGGER_TCPWM0_TR_OUT157_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT157, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[57]
    CYHAL_TRIGGER_TCPWM0_TR_OUT157_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT157, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[57]
    CYHAL_TRIGGER_TCPWM0_TR_OUT158_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT158, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[58]
    CYHAL_TRIGGER_TCPWM0_TR_OUT158_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT158, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[58]
    CYHAL_TRIGGER_TCPWM0_TR_OUT159_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT159, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[59]
    CYHAL_TRIGGER_TCPWM0_TR_OUT159_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT159, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[59]
    CYHAL_TRIGGER_TCPWM0_TR_OUT160_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT160, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[60]
    CYHAL_TRIGGER_TCPWM0_TR_OUT160_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT160, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[60]
    CYHAL_TRIGGER_TCPWM0_TR_OUT161_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT161, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[61]
    CYHAL_TRIGGER_TCPWM0_TR_OUT161_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT161, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[61]
    CYHAL_TRIGGER_TCPWM0_TR_OUT162_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT162, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[62]
    CYHAL_TRIGGER_TCPWM0_TR_OUT162_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT162, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[62]
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
    CYHAL_TRIGGER_TCPWM0_TR_OUT1263_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1263, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[263]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1263_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1263, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[263]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1264_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1264, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[264]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1264_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1264, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[264]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1265_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1265, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[265]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1265_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1265, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[265]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1266_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1266, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[266]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1266_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1266, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[266]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1267_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1267, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[267]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1267_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1267, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[267]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1512_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1512, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[512]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1512_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1512, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[512]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1513_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1513, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[513]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1513_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1513, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[513]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1514_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1514, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[514]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1514_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1514, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[514]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1515_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1515, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[515]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1515_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1515, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[515]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1516_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1516, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[516]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1516_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1516, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[516]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1517_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1517, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[517]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1517_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1517, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[517]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1518_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1518, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[518]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1518_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1518, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[518]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1519_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1519, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm[0].tr_out1[519]
    CYHAL_TRIGGER_TCPWM0_TR_OUT1519_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT1519, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm[0].tr_out1[519]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[10].output[0]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[10].output[0]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[10].output[1]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[10].output[1]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[10].output[2]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[10].output[2]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[10].output[3]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[10].output[3]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[10].output[4]
    CYHAL_TRIGGER_TR_GROUP10_OUTPUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP10_OUTPUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[10].output[4]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[11].output[0]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[11].output[0]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[11].output[1]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[11].output[1]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[11].output[2]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[11].output[2]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[11].output[3]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[11].output[3]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[11].output[4]
    CYHAL_TRIGGER_TR_GROUP11_OUTPUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP11_OUTPUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[11].output[4]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[12].output[0]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[12].output[0]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[12].output[1]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[12].output[1]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT2, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[12].output[2]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[12].output[2]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT3, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[12].output[3]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[12].output[3]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT4, CYHAL_SIGNAL_TYPE_EDGE), //!< tr_group[12].output[4]
    CYHAL_TRIGGER_TR_GROUP12_OUTPUT4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TR_GROUP12_OUTPUT4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tr_group[12].output[4]
} cyhal_trigger_source_xmc7100_t;

/** Typedef from device family specific trigger source to generic trigger source */
typedef cyhal_trigger_source_xmc7100_t cyhal_source_t;

/** Deprecated defines for signals that can be either level or edge. */
#define CYHAL_TRIGGER_CPUSS_ZERO (CYHAL_TRIGGER_CPUSS_ZERO_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT0 (CYHAL_TRIGGER_EVTGEN0_TR_OUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT1 (CYHAL_TRIGGER_EVTGEN0_TR_OUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT2 (CYHAL_TRIGGER_EVTGEN0_TR_OUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT3 (CYHAL_TRIGGER_EVTGEN0_TR_OUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT4 (CYHAL_TRIGGER_EVTGEN0_TR_OUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT5 (CYHAL_TRIGGER_EVTGEN0_TR_OUT5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT6 (CYHAL_TRIGGER_EVTGEN0_TR_OUT6_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT7 (CYHAL_TRIGGER_EVTGEN0_TR_OUT7_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT8 (CYHAL_TRIGGER_EVTGEN0_TR_OUT8_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT9 (CYHAL_TRIGGER_EVTGEN0_TR_OUT9_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT10 (CYHAL_TRIGGER_EVTGEN0_TR_OUT10_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT11 (CYHAL_TRIGGER_EVTGEN0_TR_OUT11_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT12 (CYHAL_TRIGGER_EVTGEN0_TR_OUT12_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT13 (CYHAL_TRIGGER_EVTGEN0_TR_OUT13_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT14 (CYHAL_TRIGGER_EVTGEN0_TR_OUT14_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_EVTGEN0_TR_OUT15 (CYHAL_TRIGGER_EVTGEN0_TR_OUT15_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE6_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE7_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE8_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE9_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE10_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE11_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE12_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE13_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE14_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE15_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE16_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE17_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE18_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE19_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE20_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE21_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE22_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE23_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE24_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE25_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE26_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE27_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE28_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE29_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE30_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE31_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE32_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE33_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE34_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE35_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE36_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE37_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE38_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE39_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE40_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE41_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE42_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE43_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE44_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE45_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE46_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE47_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE48_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE49_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE50_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE51_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE52_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE53_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE54_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE55_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE56_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE57_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE58_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE59_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE60_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE61_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE62_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE63_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE64_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE65_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE66_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE67_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE68_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE69_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE70_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71 (CYHAL_TRIGGER_PASS0_TR_SAR_CH_DONE71_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5 (CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT0 (CYHAL_TRIGGER_PERI_TR_IO_INPUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT1 (CYHAL_TRIGGER_PERI_TR_IO_INPUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT2 (CYHAL_TRIGGER_PERI_TR_IO_INPUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT3 (CYHAL_TRIGGER_PERI_TR_IO_INPUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT4 (CYHAL_TRIGGER_PERI_TR_IO_INPUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT5 (CYHAL_TRIGGER_PERI_TR_IO_INPUT5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT6 (CYHAL_TRIGGER_PERI_TR_IO_INPUT6_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT7 (CYHAL_TRIGGER_PERI_TR_IO_INPUT7_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT8 (CYHAL_TRIGGER_PERI_TR_IO_INPUT8_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT9 (CYHAL_TRIGGER_PERI_TR_IO_INPUT9_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT10 (CYHAL_TRIGGER_PERI_TR_IO_INPUT10_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT11 (CYHAL_TRIGGER_PERI_TR_IO_INPUT11_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT12 (CYHAL_TRIGGER_PERI_TR_IO_INPUT12_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT13 (CYHAL_TRIGGER_PERI_TR_IO_INPUT13_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT14 (CYHAL_TRIGGER_PERI_TR_IO_INPUT14_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT15 (CYHAL_TRIGGER_PERI_TR_IO_INPUT15_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT16 (CYHAL_TRIGGER_PERI_TR_IO_INPUT16_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT17 (CYHAL_TRIGGER_PERI_TR_IO_INPUT17_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT18 (CYHAL_TRIGGER_PERI_TR_IO_INPUT18_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT19 (CYHAL_TRIGGER_PERI_TR_IO_INPUT19_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT20 (CYHAL_TRIGGER_PERI_TR_IO_INPUT20_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT21 (CYHAL_TRIGGER_PERI_TR_IO_INPUT21_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT22 (CYHAL_TRIGGER_PERI_TR_IO_INPUT22_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT23 (CYHAL_TRIGGER_PERI_TR_IO_INPUT23_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT24 (CYHAL_TRIGGER_PERI_TR_IO_INPUT24_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT25 (CYHAL_TRIGGER_PERI_TR_IO_INPUT25_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT26 (CYHAL_TRIGGER_PERI_TR_IO_INPUT26_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT27 (CYHAL_TRIGGER_PERI_TR_IO_INPUT27_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT28 (CYHAL_TRIGGER_PERI_TR_IO_INPUT28_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT29 (CYHAL_TRIGGER_PERI_TR_IO_INPUT29_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT30 (CYHAL_TRIGGER_PERI_TR_IO_INPUT30_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PERI_TR_IO_INPUT31 (CYHAL_TRIGGER_PERI_TR_IO_INPUT31_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT00 (CYHAL_TRIGGER_TCPWM0_TR_OUT00_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT01 (CYHAL_TRIGGER_TCPWM0_TR_OUT01_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT02 (CYHAL_TRIGGER_TCPWM0_TR_OUT02_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT03 (CYHAL_TRIGGER_TCPWM0_TR_OUT03_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT04 (CYHAL_TRIGGER_TCPWM0_TR_OUT04_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT05 (CYHAL_TRIGGER_TCPWM0_TR_OUT05_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT06 (CYHAL_TRIGGER_TCPWM0_TR_OUT06_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT07 (CYHAL_TRIGGER_TCPWM0_TR_OUT07_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT08 (CYHAL_TRIGGER_TCPWM0_TR_OUT08_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT09 (CYHAL_TRIGGER_TCPWM0_TR_OUT09_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT010 (CYHAL_TRIGGER_TCPWM0_TR_OUT010_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT011 (CYHAL_TRIGGER_TCPWM0_TR_OUT011_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT012 (CYHAL_TRIGGER_TCPWM0_TR_OUT012_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT013 (CYHAL_TRIGGER_TCPWM0_TR_OUT013_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT014 (CYHAL_TRIGGER_TCPWM0_TR_OUT014_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT015 (CYHAL_TRIGGER_TCPWM0_TR_OUT015_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT016 (CYHAL_TRIGGER_TCPWM0_TR_OUT016_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT017 (CYHAL_TRIGGER_TCPWM0_TR_OUT017_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT018 (CYHAL_TRIGGER_TCPWM0_TR_OUT018_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT019 (CYHAL_TRIGGER_TCPWM0_TR_OUT019_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT020 (CYHAL_TRIGGER_TCPWM0_TR_OUT020_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT021 (CYHAL_TRIGGER_TCPWM0_TR_OUT021_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT022 (CYHAL_TRIGGER_TCPWM0_TR_OUT022_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT023 (CYHAL_TRIGGER_TCPWM0_TR_OUT023_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT024 (CYHAL_TRIGGER_TCPWM0_TR_OUT024_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT025 (CYHAL_TRIGGER_TCPWM0_TR_OUT025_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT026 (CYHAL_TRIGGER_TCPWM0_TR_OUT026_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT027 (CYHAL_TRIGGER_TCPWM0_TR_OUT027_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT028 (CYHAL_TRIGGER_TCPWM0_TR_OUT028_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT029 (CYHAL_TRIGGER_TCPWM0_TR_OUT029_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT030 (CYHAL_TRIGGER_TCPWM0_TR_OUT030_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT031 (CYHAL_TRIGGER_TCPWM0_TR_OUT031_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT032 (CYHAL_TRIGGER_TCPWM0_TR_OUT032_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT033 (CYHAL_TRIGGER_TCPWM0_TR_OUT033_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT034 (CYHAL_TRIGGER_TCPWM0_TR_OUT034_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT035 (CYHAL_TRIGGER_TCPWM0_TR_OUT035_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT036 (CYHAL_TRIGGER_TCPWM0_TR_OUT036_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT037 (CYHAL_TRIGGER_TCPWM0_TR_OUT037_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT038 (CYHAL_TRIGGER_TCPWM0_TR_OUT038_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT039 (CYHAL_TRIGGER_TCPWM0_TR_OUT039_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT040 (CYHAL_TRIGGER_TCPWM0_TR_OUT040_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT041 (CYHAL_TRIGGER_TCPWM0_TR_OUT041_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT042 (CYHAL_TRIGGER_TCPWM0_TR_OUT042_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT043 (CYHAL_TRIGGER_TCPWM0_TR_OUT043_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT044 (CYHAL_TRIGGER_TCPWM0_TR_OUT044_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT045 (CYHAL_TRIGGER_TCPWM0_TR_OUT045_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT046 (CYHAL_TRIGGER_TCPWM0_TR_OUT046_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT047 (CYHAL_TRIGGER_TCPWM0_TR_OUT047_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT048 (CYHAL_TRIGGER_TCPWM0_TR_OUT048_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT049 (CYHAL_TRIGGER_TCPWM0_TR_OUT049_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT050 (CYHAL_TRIGGER_TCPWM0_TR_OUT050_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT051 (CYHAL_TRIGGER_TCPWM0_TR_OUT051_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT052 (CYHAL_TRIGGER_TCPWM0_TR_OUT052_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT053 (CYHAL_TRIGGER_TCPWM0_TR_OUT053_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT054 (CYHAL_TRIGGER_TCPWM0_TR_OUT054_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT055 (CYHAL_TRIGGER_TCPWM0_TR_OUT055_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT056 (CYHAL_TRIGGER_TCPWM0_TR_OUT056_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT057 (CYHAL_TRIGGER_TCPWM0_TR_OUT057_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT058 (CYHAL_TRIGGER_TCPWM0_TR_OUT058_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT059 (CYHAL_TRIGGER_TCPWM0_TR_OUT059_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT060 (CYHAL_TRIGGER_TCPWM0_TR_OUT060_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT061 (CYHAL_TRIGGER_TCPWM0_TR_OUT061_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT062 (CYHAL_TRIGGER_TCPWM0_TR_OUT062_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0256 (CYHAL_TRIGGER_TCPWM0_TR_OUT0256_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0257 (CYHAL_TRIGGER_TCPWM0_TR_OUT0257_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0258 (CYHAL_TRIGGER_TCPWM0_TR_OUT0258_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0259 (CYHAL_TRIGGER_TCPWM0_TR_OUT0259_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0260 (CYHAL_TRIGGER_TCPWM0_TR_OUT0260_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0261 (CYHAL_TRIGGER_TCPWM0_TR_OUT0261_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0262 (CYHAL_TRIGGER_TCPWM0_TR_OUT0262_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0263 (CYHAL_TRIGGER_TCPWM0_TR_OUT0263_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0264 (CYHAL_TRIGGER_TCPWM0_TR_OUT0264_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0265 (CYHAL_TRIGGER_TCPWM0_TR_OUT0265_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0266 (CYHAL_TRIGGER_TCPWM0_TR_OUT0266_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0267 (CYHAL_TRIGGER_TCPWM0_TR_OUT0267_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0512 (CYHAL_TRIGGER_TCPWM0_TR_OUT0512_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0513 (CYHAL_TRIGGER_TCPWM0_TR_OUT0513_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0514 (CYHAL_TRIGGER_TCPWM0_TR_OUT0514_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0515 (CYHAL_TRIGGER_TCPWM0_TR_OUT0515_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0516 (CYHAL_TRIGGER_TCPWM0_TR_OUT0516_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0517 (CYHAL_TRIGGER_TCPWM0_TR_OUT0517_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0518 (CYHAL_TRIGGER_TCPWM0_TR_OUT0518_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT0519 (CYHAL_TRIGGER_TCPWM0_TR_OUT0519_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT10 (CYHAL_TRIGGER_TCPWM0_TR_OUT10_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT11 (CYHAL_TRIGGER_TCPWM0_TR_OUT11_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT12 (CYHAL_TRIGGER_TCPWM0_TR_OUT12_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT13 (CYHAL_TRIGGER_TCPWM0_TR_OUT13_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT14 (CYHAL_TRIGGER_TCPWM0_TR_OUT14_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT15 (CYHAL_TRIGGER_TCPWM0_TR_OUT15_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT16 (CYHAL_TRIGGER_TCPWM0_TR_OUT16_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT17 (CYHAL_TRIGGER_TCPWM0_TR_OUT17_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT18 (CYHAL_TRIGGER_TCPWM0_TR_OUT18_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT19 (CYHAL_TRIGGER_TCPWM0_TR_OUT19_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT110 (CYHAL_TRIGGER_TCPWM0_TR_OUT110_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT111 (CYHAL_TRIGGER_TCPWM0_TR_OUT111_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT112 (CYHAL_TRIGGER_TCPWM0_TR_OUT112_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT113 (CYHAL_TRIGGER_TCPWM0_TR_OUT113_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT114 (CYHAL_TRIGGER_TCPWM0_TR_OUT114_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT115 (CYHAL_TRIGGER_TCPWM0_TR_OUT115_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT116 (CYHAL_TRIGGER_TCPWM0_TR_OUT116_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT117 (CYHAL_TRIGGER_TCPWM0_TR_OUT117_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT118 (CYHAL_TRIGGER_TCPWM0_TR_OUT118_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT119 (CYHAL_TRIGGER_TCPWM0_TR_OUT119_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT120 (CYHAL_TRIGGER_TCPWM0_TR_OUT120_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT121 (CYHAL_TRIGGER_TCPWM0_TR_OUT121_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT122 (CYHAL_TRIGGER_TCPWM0_TR_OUT122_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT123 (CYHAL_TRIGGER_TCPWM0_TR_OUT123_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT124 (CYHAL_TRIGGER_TCPWM0_TR_OUT124_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT125 (CYHAL_TRIGGER_TCPWM0_TR_OUT125_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT126 (CYHAL_TRIGGER_TCPWM0_TR_OUT126_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT127 (CYHAL_TRIGGER_TCPWM0_TR_OUT127_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT128 (CYHAL_TRIGGER_TCPWM0_TR_OUT128_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT129 (CYHAL_TRIGGER_TCPWM0_TR_OUT129_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT130 (CYHAL_TRIGGER_TCPWM0_TR_OUT130_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT131 (CYHAL_TRIGGER_TCPWM0_TR_OUT131_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT132 (CYHAL_TRIGGER_TCPWM0_TR_OUT132_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT133 (CYHAL_TRIGGER_TCPWM0_TR_OUT133_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT134 (CYHAL_TRIGGER_TCPWM0_TR_OUT134_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT135 (CYHAL_TRIGGER_TCPWM0_TR_OUT135_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT136 (CYHAL_TRIGGER_TCPWM0_TR_OUT136_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT137 (CYHAL_TRIGGER_TCPWM0_TR_OUT137_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT138 (CYHAL_TRIGGER_TCPWM0_TR_OUT138_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT139 (CYHAL_TRIGGER_TCPWM0_TR_OUT139_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT140 (CYHAL_TRIGGER_TCPWM0_TR_OUT140_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT141 (CYHAL_TRIGGER_TCPWM0_TR_OUT141_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT142 (CYHAL_TRIGGER_TCPWM0_TR_OUT142_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT143 (CYHAL_TRIGGER_TCPWM0_TR_OUT143_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT144 (CYHAL_TRIGGER_TCPWM0_TR_OUT144_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT145 (CYHAL_TRIGGER_TCPWM0_TR_OUT145_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT146 (CYHAL_TRIGGER_TCPWM0_TR_OUT146_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT147 (CYHAL_TRIGGER_TCPWM0_TR_OUT147_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT148 (CYHAL_TRIGGER_TCPWM0_TR_OUT148_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT149 (CYHAL_TRIGGER_TCPWM0_TR_OUT149_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT150 (CYHAL_TRIGGER_TCPWM0_TR_OUT150_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT151 (CYHAL_TRIGGER_TCPWM0_TR_OUT151_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT152 (CYHAL_TRIGGER_TCPWM0_TR_OUT152_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT153 (CYHAL_TRIGGER_TCPWM0_TR_OUT153_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT154 (CYHAL_TRIGGER_TCPWM0_TR_OUT154_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT155 (CYHAL_TRIGGER_TCPWM0_TR_OUT155_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT156 (CYHAL_TRIGGER_TCPWM0_TR_OUT156_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT157 (CYHAL_TRIGGER_TCPWM0_TR_OUT157_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT158 (CYHAL_TRIGGER_TCPWM0_TR_OUT158_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT159 (CYHAL_TRIGGER_TCPWM0_TR_OUT159_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT160 (CYHAL_TRIGGER_TCPWM0_TR_OUT160_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT161 (CYHAL_TRIGGER_TCPWM0_TR_OUT161_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT162 (CYHAL_TRIGGER_TCPWM0_TR_OUT162_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1256 (CYHAL_TRIGGER_TCPWM0_TR_OUT1256_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1257 (CYHAL_TRIGGER_TCPWM0_TR_OUT1257_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1258 (CYHAL_TRIGGER_TCPWM0_TR_OUT1258_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1259 (CYHAL_TRIGGER_TCPWM0_TR_OUT1259_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1260 (CYHAL_TRIGGER_TCPWM0_TR_OUT1260_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1261 (CYHAL_TRIGGER_TCPWM0_TR_OUT1261_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1262 (CYHAL_TRIGGER_TCPWM0_TR_OUT1262_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1263 (CYHAL_TRIGGER_TCPWM0_TR_OUT1263_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1264 (CYHAL_TRIGGER_TCPWM0_TR_OUT1264_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1265 (CYHAL_TRIGGER_TCPWM0_TR_OUT1265_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1266 (CYHAL_TRIGGER_TCPWM0_TR_OUT1266_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1267 (CYHAL_TRIGGER_TCPWM0_TR_OUT1267_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1512 (CYHAL_TRIGGER_TCPWM0_TR_OUT1512_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1513 (CYHAL_TRIGGER_TCPWM0_TR_OUT1513_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1514 (CYHAL_TRIGGER_TCPWM0_TR_OUT1514_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1515 (CYHAL_TRIGGER_TCPWM0_TR_OUT1515_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1516 (CYHAL_TRIGGER_TCPWM0_TR_OUT1516_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1517 (CYHAL_TRIGGER_TCPWM0_TR_OUT1517_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1518 (CYHAL_TRIGGER_TCPWM0_TR_OUT1518_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM0_TR_OUT1519 (CYHAL_TRIGGER_TCPWM0_TR_OUT1519_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP10_OUTPUT0 (CYHAL_TRIGGER_TR_GROUP10_OUTPUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP10_OUTPUT1 (CYHAL_TRIGGER_TR_GROUP10_OUTPUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP10_OUTPUT2 (CYHAL_TRIGGER_TR_GROUP10_OUTPUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP10_OUTPUT3 (CYHAL_TRIGGER_TR_GROUP10_OUTPUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP10_OUTPUT4 (CYHAL_TRIGGER_TR_GROUP10_OUTPUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP11_OUTPUT0 (CYHAL_TRIGGER_TR_GROUP11_OUTPUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP11_OUTPUT1 (CYHAL_TRIGGER_TR_GROUP11_OUTPUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP11_OUTPUT2 (CYHAL_TRIGGER_TR_GROUP11_OUTPUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP11_OUTPUT3 (CYHAL_TRIGGER_TR_GROUP11_OUTPUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP11_OUTPUT4 (CYHAL_TRIGGER_TR_GROUP11_OUTPUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP12_OUTPUT0 (CYHAL_TRIGGER_TR_GROUP12_OUTPUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP12_OUTPUT1 (CYHAL_TRIGGER_TR_GROUP12_OUTPUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP12_OUTPUT2 (CYHAL_TRIGGER_TR_GROUP12_OUTPUT2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP12_OUTPUT3 (CYHAL_TRIGGER_TR_GROUP12_OUTPUT3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TR_GROUP12_OUTPUT4 (CYHAL_TRIGGER_TR_GROUP12_OUTPUT4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.

/** @brief Name of each output trigger. */
typedef enum
{
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_ACK0 = 0, //!< CAN0 DW0 triggers (from DW0 back to CAN0) - canfd[0].tr_dbg_dma_ack[0]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_ACK1 = 1, //!< CAN0 DW0 triggers (from DW0 back to CAN0) - canfd[0].tr_dbg_dma_ack[1]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_ACK2 = 2, //!< CAN0 DW0 triggers (from DW0 back to CAN0) - canfd[0].tr_dbg_dma_ack[2]
    CYHAL_TRIGGER_CANFD0_TR_DBG_DMA_ACK3 = 3, //!< CAN0 DW0 triggers (from DW0 back to CAN0) - canfd[0].tr_dbg_dma_ack[3]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_ACK0 = 4, //!< CAN1 DW1 triggers (from DW1 back to CAN1) - canfd[1].tr_dbg_dma_ack[0]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_ACK1 = 5, //!< CAN1 DW1 triggers (from DW1 back to CAN1) - canfd[1].tr_dbg_dma_ack[1]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_ACK2 = 6, //!< CAN1 DW1 triggers (from DW1 back to CAN1) - canfd[1].tr_dbg_dma_ack[2]
    CYHAL_TRIGGER_CANFD1_TR_DBG_DMA_ACK3 = 7, //!< CAN1 DW1 triggers (from DW1 back to CAN1) - canfd[1].tr_dbg_dma_ack[3]
    CYHAL_TRIGGER_CANFD0_TR_EVT_SWT_IN0 = 8, //!< CAN TT Sync - canfd[0].tr_evt_swt_in[0]
    CYHAL_TRIGGER_CANFD0_TR_EVT_SWT_IN1 = 9, //!< CAN TT Sync - canfd[0].tr_evt_swt_in[1]
    CYHAL_TRIGGER_CANFD0_TR_EVT_SWT_IN2 = 10, //!< CAN TT Sync - canfd[0].tr_evt_swt_in[2]
    CYHAL_TRIGGER_CANFD0_TR_EVT_SWT_IN3 = 11, //!< CAN TT Sync - canfd[0].tr_evt_swt_in[3]
    CYHAL_TRIGGER_CANFD1_TR_EVT_SWT_IN0 = 12, //!< CAN TT Sync - canfd[1].tr_evt_swt_in[0]
    CYHAL_TRIGGER_CANFD1_TR_EVT_SWT_IN1 = 13, //!< CAN TT Sync - canfd[1].tr_evt_swt_in[1]
    CYHAL_TRIGGER_CANFD1_TR_EVT_SWT_IN2 = 14, //!< CAN TT Sync - canfd[1].tr_evt_swt_in[2]
    CYHAL_TRIGGER_CANFD1_TR_EVT_SWT_IN3 = 15, //!< CAN TT Sync - canfd[1].tr_evt_swt_in[3]
    CYHAL_TRIGGER_CPUSS_CTI_TR_IN0 = 16, //!< Debug Multiplexer - cpuss.cti_tr_in[0]
    CYHAL_TRIGGER_CPUSS_CTI_TR_IN1 = 17, //!< Debug Multiplexer - cpuss.cti_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN0 = 18, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[0]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN1 = 19, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN2 = 20, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[2]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN3 = 21, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[3]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN4 = 22, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[4]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN5 = 23, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[5]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN6 = 24, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[6]
    CYHAL_TRIGGER_CPUSS_DMAC_TR_IN7 = 25, //!< M-DMA trigger multiplexer - cpuss.dmac_tr_in[7]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN0 = 26, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[0]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN1 = 27, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN2 = 28, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[2]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN3 = 29, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[3]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN4 = 30, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[4]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN5 = 31, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[5]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN6 = 32, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[6]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN7 = 33, //!< P-DMA0 trigger multiplexer - cpuss.dw0_tr_in[7]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN8 = 34, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[8]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN9 = 35, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[9]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN10 = 36, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[10]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN11 = 37, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[11]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN12 = 38, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[12]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN13 = 39, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[13]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN14 = 40, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[14]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN15 = 41, //!< TCPWM to P-DMA0 trigger mux - cpuss.dw0_tr_in[15]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN16 = 42, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[16]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN17 = 43, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[17]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN18 = 44, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[18]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN19 = 45, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[19]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN20 = 46, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[20]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN21 = 47, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[21]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN22 = 48, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[22]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN23 = 49, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[23]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN24 = 50, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[24]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN25 = 51, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[25]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN26 = 52, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[26]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN27 = 53, //!< CAN0 DW0 Triggers - cpuss.dw0_tr_in[27]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN28 = 54, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[28]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN29 = 55, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[29]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN30 = 56, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[30]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN31 = 57, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[31]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN32 = 58, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[32]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN33 = 59, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[33]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN34 = 60, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[34]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN35 = 61, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[35]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN36 = 62, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[36]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN37 = 63, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[37]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN38 = 64, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[38]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN39 = 65, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[39]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN40 = 66, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[40]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN41 = 67, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[41]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN42 = 68, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[42]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN43 = 69, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[43]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN44 = 70, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[44]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN45 = 71, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[45]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN46 = 72, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[46]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN47 = 73, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[47]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN48 = 74, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[48]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN49 = 75, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[49]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN50 = 76, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[50]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN51 = 77, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[51]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN52 = 78, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[52]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN53 = 79, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[53]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN54 = 80, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[54]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN55 = 81, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[55]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN56 = 82, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[56]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN57 = 83, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[57]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN58 = 84, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[58]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN59 = 85, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[59]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN60 = 86, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[60]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN61 = 87, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[61]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN62 = 88, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[62]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN63 = 89, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[63]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN64 = 90, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[64]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN65 = 91, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[65]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN66 = 92, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[66]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN67 = 93, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[67]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN68 = 94, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[68]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN69 = 95, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[69]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN70 = 96, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[70]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN71 = 97, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[71]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN72 = 98, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[72]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN73 = 99, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[73]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN74 = 100, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[74]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN75 = 101, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[75]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN76 = 102, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[76]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN77 = 103, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[77]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN78 = 104, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[78]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN79 = 105, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[79]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN80 = 106, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[80]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN81 = 107, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[81]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN82 = 108, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[82]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN83 = 109, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[83]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN84 = 110, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[84]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN85 = 111, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[85]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN86 = 112, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[86]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN87 = 113, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[87]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN88 = 114, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[88]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN89 = 115, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[89]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN90 = 116, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[90]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN91 = 117, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[91]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN92 = 118, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[92]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN93 = 119, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[93]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN94 = 120, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[94]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN95 = 121, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[95]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN96 = 122, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[96]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN97 = 123, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[97]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN98 = 124, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[98]
    CYHAL_TRIGGER_CPUSS_DW0_TR_IN99 = 125, //!< PASS to DW0 direct connect - cpuss.dw0_tr_in[99]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN0 = 126, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[0]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN1 = 127, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[1]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN2 = 128, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[2]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN3 = 129, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[3]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN4 = 130, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[4]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN5 = 131, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[5]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN6 = 132, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[6]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN7 = 133, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[7]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN8 = 134, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[8]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN9 = 135, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[9]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN10 = 136, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[10]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN11 = 137, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[11]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN12 = 138, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[12]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN13 = 139, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[13]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN14 = 140, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[14]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN15 = 141, //!< P-DMA1 trigger multiplexer - cpuss.dw1_tr_in[15]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN16 = 142, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[16]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN17 = 143, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[17]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN18 = 144, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[18]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN19 = 145, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[19]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN20 = 146, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[20]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN21 = 147, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[21]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN22 = 148, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[22]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN23 = 149, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[23]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN24 = 150, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[24]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN25 = 151, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[25]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN26 = 152, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[26]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN27 = 153, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[27]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN28 = 154, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[28]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN29 = 155, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[29]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN30 = 156, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[30]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN31 = 157, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[31]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN32 = 158, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[32]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN33 = 159, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[33]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN34 = 160, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[34]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN35 = 161, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[35]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN36 = 162, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[36]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN37 = 163, //!< SCB DW1 Triggers - cpuss.dw1_tr_in[37]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN38 = 164, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[38]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN39 = 165, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[39]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN40 = 166, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[40]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN41 = 167, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[41]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN42 = 168, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[42]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN43 = 169, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[43]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN44 = 170, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[44]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN45 = 171, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[45]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN46 = 172, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[46]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN47 = 173, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[47]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN48 = 174, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[48]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN49 = 175, //!< CAN1 DW1 Triggers - cpuss.dw1_tr_in[49]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN50 = 176, //!< SMIF DW1 Triggers - cpuss.dw1_tr_in[50]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN51 = 177, //!< SMIF DW1 Triggers - cpuss.dw1_tr_in[51]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN52 = 178, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[52]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN53 = 179, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[53]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN54 = 180, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[54]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN55 = 181, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[55]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN56 = 182, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[56]
    CYHAL_TRIGGER_CPUSS_DW1_TR_IN57 = 183, //!< I2S DW1 Triggers - cpuss.dw1_tr_in[57]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER0 = 184, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[0]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER1 = 185, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[1]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER2 = 186, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[2]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER3 = 187, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[3]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER4 = 188, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[4]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER5 = 189, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[5]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER6 = 190, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[6]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER7 = 191, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[7]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER8 = 192, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[8]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER9 = 193, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[9]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER10 = 194, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[10]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER11 = 195, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[11]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER12 = 196, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[12]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER13 = 197, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[13]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER14 = 198, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[14]
    CYHAL_TRIGGER_LIN0_TR_CMD_TX_HEADER15 = 199, //!< TCPWM to LIN - lin[0].tr_cmd_tx_header[15]
    CYHAL_TRIGGER_PASS0_TR_DEBUG_FREEZE = 200, //!< Debug Multiplexer - pass[0].tr_debug_freeze
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN0 = 201, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN1 = 202, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN2 = 203, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN3 = 204, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN4 = 205, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN5 = 206, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN6 = 207, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[6]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN7 = 208, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[7]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN8 = 209, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[8]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN9 = 210, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[9]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN10 = 211, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[10]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN11 = 212, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[11]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN12 = 213, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[12]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN13 = 214, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[13]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN14 = 215, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[14]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN15 = 216, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[15]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN16 = 217, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[16]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN17 = 218, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[17]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN18 = 219, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[18]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN19 = 220, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[19]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN20 = 221, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[20]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN21 = 222, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[21]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN22 = 223, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[22]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN23 = 224, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[23]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN24 = 225, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[24]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN25 = 226, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[25]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN26 = 227, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[26]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN27 = 228, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[27]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN28 = 229, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[28]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN29 = 230, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[29]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN30 = 231, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[30]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN31 = 232, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[31]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN32 = 233, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[32]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN33 = 234, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[33]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN34 = 235, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[34]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN35 = 236, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[35]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN36 = 237, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[36]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN37 = 238, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[37]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN38 = 239, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[38]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN39 = 240, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[39]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN40 = 241, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[40]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN41 = 242, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[41]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN42 = 243, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[42]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN43 = 244, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[43]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN44 = 245, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[44]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN45 = 246, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[45]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN46 = 247, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[46]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN47 = 248, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[47]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN48 = 249, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[48]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN49 = 250, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[49]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN50 = 251, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[50]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN51 = 252, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[51]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN52 = 253, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[52]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN53 = 254, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[53]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN54 = 255, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[54]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN55 = 256, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[55]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN56 = 257, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[56]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN57 = 258, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[57]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN58 = 259, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[58]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN59 = 260, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[59]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN60 = 261, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[60]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN61 = 262, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[61]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN62 = 263, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[62]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN63 = 264, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[63]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN64 = 265, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[64]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN65 = 266, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[65]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN66 = 267, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[66]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN67 = 268, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[67]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN68 = 269, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[68]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN69 = 270, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[69]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN70 = 271, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[70]
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN71 = 272, //!< PWM to PASS direct connect - pass[0].tr_sar_ch_in[71]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN0 = 273, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[0]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN1 = 274, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[1]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN2 = 275, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[2]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN3 = 276, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[3]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN4 = 277, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[4]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN5 = 278, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[5]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN6 = 279, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[6]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN7 = 280, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[7]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN8 = 281, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[8]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN9 = 282, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[9]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN10 = 283, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[10]
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_IN11 = 284, //!< PASS trigger multiplexer - pass[0].tr_sar_gen_in[11]
    CYHAL_TRIGGER_PERI_TR_DBG_FREEZE = 285, //!< Debug Multiplexer - peri.tr_dbg_freeze
    CYHAL_TRIGGER_PERI_TR_IO_OUTPUT0 = 286, //!< Debug Multiplexer - peri.tr_io_output[0]
    CYHAL_TRIGGER_PERI_TR_IO_OUTPUT1 = 287, //!< Debug Multiplexer - peri.tr_io_output[1]
    CYHAL_TRIGGER_SRSS_TR_DEBUG_FREEZE_MCWDT0 = 288, //!< Debug Multiplexer - srss.tr_debug_freeze_mcwdt[0]
    CYHAL_TRIGGER_SRSS_TR_DEBUG_FREEZE_MCWDT1 = 289, //!< Debug Multiplexer - srss.tr_debug_freeze_mcwdt[1]
    CYHAL_TRIGGER_SRSS_TR_DEBUG_FREEZE_MCWDT2 = 290, //!< Debug Multiplexer - srss.tr_debug_freeze_mcwdt[2]
    CYHAL_TRIGGER_SRSS_TR_DEBUG_FREEZE_WDT = 291, //!< Debug Multiplexer - srss.tr_debug_freeze_wdt
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN0 = 292, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[0]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN1 = 293, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[1]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN2 = 294, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[2]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN3 = 295, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[3]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN4 = 296, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[4]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN5 = 297, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[5]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN6 = 298, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[6]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN7 = 299, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[7]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN8 = 300, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[8]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN9 = 301, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[9]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN10 = 302, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[10]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN11 = 303, //!< TCPWM loopback mux - tcpwm[0].tr_all_cnt_in[11]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN12 = 304, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[12]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN13 = 305, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[13]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN14 = 306, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[14]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN15 = 307, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[15]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN16 = 308, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[16]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN17 = 309, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[17]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN18 = 310, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[18]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN19 = 311, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[19]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN20 = 312, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[20]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN21 = 313, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[21]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN22 = 314, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[22]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN23 = 315, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[23]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN24 = 316, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[24]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN25 = 317, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[25]
    CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN26 = 318, //!< TCPWM Trigger Multiplexer - tcpwm[0].tr_all_cnt_in[26]
    CYHAL_TRIGGER_TCPWM0_TR_DEBUG_FREEZE = 319, //!< Debug Multiplexer - tcpwm[0].tr_debug_freeze
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN2 = 320, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[2]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN5 = 321, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[5]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN8 = 322, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[8]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN11 = 323, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[11]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN14 = 324, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[14]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN17 = 325, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[17]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN20 = 326, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[20]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN23 = 327, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[23]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN26 = 328, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[26]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN29 = 329, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[29]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN32 = 330, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[32]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN35 = 331, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[35]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN38 = 332, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[38]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN41 = 333, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[41]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN44 = 334, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[44]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN47 = 335, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[47]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN50 = 336, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[50]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN53 = 337, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[53]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN56 = 338, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[56]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN59 = 339, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[59]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN62 = 340, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[62]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN65 = 341, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[65]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN68 = 342, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[68]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN71 = 343, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[71]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN74 = 344, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[74]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN77 = 345, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[77]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN80 = 346, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[80]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN83 = 347, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[83]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN86 = 348, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[86]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN89 = 349, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[89]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN92 = 350, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[92]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN95 = 351, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[95]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN98 = 352, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[98]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN101 = 353, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[101]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN104 = 354, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[104]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN107 = 355, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[107]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN110 = 356, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[110]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN113 = 357, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[113]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN116 = 358, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[116]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN119 = 359, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[119]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN122 = 360, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[122]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN125 = 361, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[125]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN128 = 362, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[128]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN131 = 363, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[131]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN134 = 364, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[134]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN137 = 365, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[137]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN140 = 366, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[140]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN143 = 367, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[143]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN146 = 368, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[146]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN149 = 369, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[149]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN152 = 370, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[152]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN155 = 371, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[155]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN158 = 372, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[158]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN161 = 373, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[161]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN164 = 374, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[164]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN167 = 375, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[167]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN170 = 376, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[170]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN173 = 377, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[173]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN176 = 378, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[176]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN179 = 379, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[179]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN770 = 380, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[770]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN773 = 381, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[773]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN776 = 382, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[776]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN779 = 383, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[779]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN782 = 384, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[782]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN785 = 385, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[785]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN788 = 386, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[788]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN791 = 387, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[791]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN794 = 388, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[794]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN797 = 389, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[797]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN800 = 390, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[800]
    CYHAL_TRIGGER_TCPWM0_TR_ONE_CNT_IN803 = 391, //!< PASS to PWM direct connect - tcpwm[0].tr_one_cnt_in[803]
    CYHAL_TRIGGER_TR_GROUP9_INPUT1 = 392, //!< Debug Reduction #1 - tr_group[9].input[1]
    CYHAL_TRIGGER_TR_GROUP9_INPUT2 = 393, //!< Debug Reduction #1 - tr_group[9].input[2]
    CYHAL_TRIGGER_TR_GROUP9_INPUT3 = 394, //!< Debug Reduction #1 - tr_group[9].input[3]
    CYHAL_TRIGGER_TR_GROUP9_INPUT4 = 395, //!< Debug Reduction #1 - tr_group[9].input[4]
    CYHAL_TRIGGER_TR_GROUP9_INPUT5 = 396, //!< Debug Reduction #1 - tr_group[9].input[5]
    CYHAL_TRIGGER_TR_GROUP9_INPUT6 = 397, //!< Debug Reduction #2 - tr_group[9].input[6]
    CYHAL_TRIGGER_TR_GROUP9_INPUT7 = 398, //!< Debug Reduction #2 - tr_group[9].input[7]
    CYHAL_TRIGGER_TR_GROUP9_INPUT8 = 399, //!< Debug Reduction #2 - tr_group[9].input[8]
    CYHAL_TRIGGER_TR_GROUP9_INPUT9 = 400, //!< Debug Reduction #2 - tr_group[9].input[9]
    CYHAL_TRIGGER_TR_GROUP9_INPUT10 = 401, //!< Debug Reduction #2 - tr_group[9].input[10]
    CYHAL_TRIGGER_TR_GROUP9_INPUT11 = 402, //!< Debug Reduction #3 - tr_group[9].input[11]
    CYHAL_TRIGGER_TR_GROUP9_INPUT12 = 403, //!< Debug Reduction #3 - tr_group[9].input[12]
    CYHAL_TRIGGER_TR_GROUP9_INPUT13 = 404, //!< Debug Reduction #3 - tr_group[9].input[13]
    CYHAL_TRIGGER_TR_GROUP9_INPUT14 = 405, //!< Debug Reduction #3 - tr_group[9].input[14]
    CYHAL_TRIGGER_TR_GROUP9_INPUT15 = 406, //!< Debug Reduction #3 - tr_group[9].input[15]
} cyhal_trigger_dest_xmc7100_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_xmc7100_t cyhal_dest_t;

/** \cond INTERNAL */
/** Table of number of inputs to each mux. */
extern const uint16_t cyhal_sources_per_mux[24];

/** Table indicating whether mux is 1to1. */
extern const bool cyhal_is_mux_1to1[24];

/** Table pointing to each mux source table. The index of each source in the table is its mux input index. */
extern const _cyhal_trigger_source_xmc7100_t* cyhal_mux_to_sources [24];

/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[407];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[407];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_xmc7100 */
#endif /* _CYHAL_TRIGGERS_XMC7100_H_ */


/* [] END OF FILE */
