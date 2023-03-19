/**
  ******************************************************************************
  * @file    bl808_glb.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL808_GLB_H__
#define __BL808_GLB_H__

#include "glb_reg.h"
#include "cci_reg.h"
#include "mm_glb_reg.h"
#include "pds_reg.h"
#include "bl808_gpio.h"
#include "bl808_hbn.h"
#include "bl808_aon.h"
#include "bl808_pds.h"
#include "bl808_common.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sf_cfg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Public_Types
 *  @{
 */

/**
 *  @brief GLB AHB clock IP type definition
 */
typedef enum {
    GLB_AHB_CLOCK_IP_CPU,
    GLB_AHB_CLOCK_IP_SDU,
    GLB_AHB_CLOCK_IP_SEC,
    GLB_AHB_CLOCK_IP_DMA_0,
    GLB_AHB_CLOCK_IP_DMA_1,
    GLB_AHB_CLOCK_IP_DMA_2,
    GLB_AHB_CLOCK_IP_CCI,
    GLB_AHB_CLOCK_IP_RF_TOP,
    GLB_AHB_CLOCK_IP_GPIP,
    GLB_AHB_CLOCK_IP_TZC,
    GLB_AHB_CLOCK_IP_EF_CTRL,
    GLB_AHB_CLOCK_IP_SF_CTRL,
    GLB_AHB_CLOCK_IP_EMAC,
    GLB_AHB_CLOCK_IP_UART0,
    GLB_AHB_CLOCK_IP_UART1,
    GLB_AHB_CLOCK_IP_UART2,
    GLB_AHB_CLOCK_IP_UART3,
    GLB_AHB_CLOCK_IP_SPI,
    GLB_AHB_CLOCK_IP_I2C,
    GLB_AHB_CLOCK_IP_PWM,
    GLB_AHB_CLOCK_IP_TIMER,
    GLB_AHB_CLOCK_IP_IR,
    GLB_AHB_CLOCK_IP_CHECKSUM,
    GLB_AHB_CLOCK_IP_QDEC,
    GLB_AHB_CLOCK_IP_KYS,
    GLB_AHB_CLOCK_IP_I2S,
    GLB_AHB_CLOCK_IP_USB11,
    GLB_AHB_CLOCK_IP_CAM,
    GLB_AHB_CLOCK_IP_MJPEG,
    GLB_AHB_CLOCK_IP_BT_BLE_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_LP,
    GLB_AHB_CLOCK_IP_ZB_NORMAL,
    GLB_AHB_CLOCK_IP_ZB_LP,
    GLB_AHB_CLOCK_IP_WIFI_NORMAL,
    GLB_AHB_CLOCK_IP_WIFI_LP,
    GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_2_LP,
    GLB_AHB_CLOCK_IP_EMI_MISC,
    GLB_AHB_CLOCK_IP_PSRAM0_CTRL,
    GLB_AHB_CLOCK_IP_PSRAM1_CTRL,
    GLB_AHB_CLOCK_IP_USB20,
    GLB_AHB_CLOCK_IP_MIX2,
    GLB_AHB_CLOCK_IP_AUDIO,
    GLB_AHB_CLOCK_IP_SDH,
    GLB_AHB_CLOCK_IP_ZB2_NORMAL,
    GLB_AHB_CLOCK_IP_ZB2_LP,
    GLB_AHB_CLOCK_IP_I2C1,
    GLB_AHB_CLOCK_IP_WIFI_PHY,
    GLB_AHB_CLOCK_IP_WIFI_MAC_PHY,
    GLB_AHB_CLOCK_IP_WIFI_PLATFORM,
    GLB_AHB_CLOCK_IP_LZ4,
    GLB_AHB_CLOCK_IP_AUPDM,
    GLB_AHB_CLOCK_IP_GAUGE,
} GLB_AHB_CLOCK_IP_Type;

/**
 *  @brief GLB core ID type definition
 */
typedef enum {
    GLB_CORE_ID_M0,      /*!< M0 */
    GLB_CORE_ID_D0,      /*!< D0 */
    GLB_CORE_ID_LP,      /*!< LP */
    GLB_CORE_ID_MAX,     /*!< ID max */
    GLB_CORE_ID_INVALID, /*!< ID invalid */
} GLB_CORE_ID_Type;

/**
 *  @brief cci ID type definition
 */
typedef enum {
    CCI0_ID,    /*!< CCI0 port define */
    CCI_ID_MAX, /*!< CCI MAX ID define */
} CCI_ID_Type;

/**
 *  @brief GLB DSP all interrupt type definition
 */
typedef enum {
    GLB_DSP_ALL_INT_BUS_DEC_ERR_INT = 0,      /*!< bus_dec_err_int */
    GLB_DSP_ALL_INT_RSV1_INT = 1,             /*!< rsv1 */
    GLB_DSP_ALL_INT_IPC2_NP2AP_IRQ = 2,       /*!< |ipc2_np2ap_irq */
    GLB_DSP_ALL_INT_RSV3 = 3,                 /*!< rsv3 */
    GLB_DSP_ALL_INT_UART0_INT = 4,            /*!< uart0_int */
    GLB_DSP_ALL_INT_I2C0_INT = 5,             /*!< i2c0_int */
    GLB_DSP_ALL_INT_I2C1_INT = 6,             /*!< i2c1_int */
    GLB_DSP_ALL_INT_SPI_INT = 7,              /*!< spi_int */
    GLB_DSP_ALL_INT_RSV4_INT = 8,             /*!< rsv4 */
    GLB_DSP_ALL_INT_RSV5_INT = 9,             /*!< rsv5 */
    GLB_DSP_ALL_INT_SEOF1_INT = 10,           /*!< seof1_int */
    GLB_DSP_ALL_INT_SEOF2_INT = 11,           /*!< seof2_int */
    GLB_DSP_ALL_INT_SEOF3_INT = 12,           /*!< seof3_int */
    GLB_DSP_ALL_INT_DVP2BUS_INT_0 = 13,       /*!< dvp2bus_int[0] */
    GLB_DSP_ALL_INT_DVP2BUS_INT_1 = 14,       /*!< dvp2bus_int[1] */
    GLB_DSP_ALL_INT_DVP2BUS_INT_2 = 15,       /*!< dvp2bus_int[2] */
    GLB_DSP_ALL_INT_DVP2BUS_INT_3 = 16,       /*!< dvp2bus_int[3] */
    GLB_DSP_ALL_INT_H264_BS_IRQ = 17,         /*!< h264_bs_irq */
    GLB_DSP_ALL_INT_H264_FRAME_IRQ = 18,      /*!< h264_frame_irq */
    GLB_DSP_ALL_INT_H264_SEQ_DONE_INT = 19,   /*!< h264_seq_done_int */
    GLB_DSP_ALL_INT_MJPEG_INT = 20,           /*!< mjpeg_int */
    GLB_DSP_ALL_INT_H264_S_BS_IRQ = 21,       /*!< h264_s_bs_irq */
    GLB_DSP_ALL_INT_H264_S_FRAME_IRQ = 22,    /*!< h264_s_frame_irq */
    GLB_DSP_ALL_INT_H264_S_SEQ_DONE_INT = 23, /*!< h264_s_seq_done_int */
    GLB_DSP_ALL_INT_DMA_INTR_0 = 24,          /*!< DMA_INTR[0] */
    GLB_DSP_ALL_INT_DMA_INTR_1 = 25,          /*!< DMA_INTR[1] */
    GLB_DSP_ALL_INT_DMA_INTR_2 = 26,          /*!< DMA_INTR[2] */
    GLB_DSP_ALL_INT_DMA_INTR_3 = 27,          /*!< DMA_INTR[3] */
    GLB_DSP_ALL_INT_DMA_INTR_4 = 28,          /*!< DMA_INTR[4] */
    GLB_DSP_ALL_INT_DMA_INTR_5 = 29,          /*!< DMA_INTR[5] */
    GLB_DSP_ALL_INT_DMA_INTR_6 = 30,          /*!< DMA_INTR[6] */
    GLB_DSP_ALL_INT_DMA_INTR_7 = 31,          /*!< DMA_INTR[7] */
    GLB_DSP_ALL_INT_RSV32 = 32,               /*!< rsv32 */
    GLB_DSP_ALL_INT_RSV33 = 33,               /*!< rsv33 */
    GLB_DSP_ALL_INT_RSV34 = 34,               /*!< rsv34 */
    GLB_DSP_ALL_INT_RSV35 = 35,               /*!< rsv35 */
    GLB_DSP_ALL_INT_RSV36 = 36,               /*!< rsv36 */
    GLB_DSP_ALL_INT_MIPI_CSI_INT = 37,        /*!< mipi_csi_int */
    GLB_DSP_ALL_INT_IPC2_AP2NP_IRQ = 38,      /*!< |ipc2_ap2np_irq */
    GLB_DSP_ALL_INT_RSV39 = 39,               /*!< rsv39 */
    GLB_DSP_ALL_INT_MJDEC_INT = 40,           /*!< mjdec_int */
    GLB_DSP_ALL_INT_DVP2BUS_IN_4 = 41,        /*!< dvp2bus_int[4] */
    GLB_DSP_ALL_INT_DVP2BUS_IN_5 = 42,        /*!< dvp2bus_int[5] */
    GLB_DSP_ALL_INT_DVP2BUS_IN_6 = 43,        /*!< dvp2bus_int[6] */
    GLB_DSP_ALL_INT_DVP2BUS_IN_7 = 44,        /*!< dvp2bus_int[7] */
    GLB_DSP_ALL_INT_DMA2D_INT_0 = 45,         /*!< dma2d_int[0] */
    GLB_DSP_ALL_INT_DMA2D_INT_1 = 46,         /*!< dma2d_int[1] */
    GLB_DSP_ALL_INT_DP_SOEF0_INT = 47,        /*!< dp_soef0_int */
    GLB_DSP_ALL_INT_RSV48 = 48,               /*!< rsv48 */
    GLB_DSP_ALL_INT_RSV49 = 49,               /*!< rsv49 */
    GLB_DSP_ALL_INT_RSV50 = 50,               /*!< rsv50 */
    GLB_DSP_ALL_INT_RSV51 = 51,               /*!< rsv51 */
    GLB_DSP_ALL_INT_OSDDP_INT = 52,           /*!< osdDP_int */
    GLB_DSP_ALL_INT_DBI_INT = 53,             /*!< dbi_int */
    GLB_DSP_ALL_INT_RSV6_INT = 54,            /*!< rsv6 */
    GLB_DSP_ALL_INT_OSDA_INT = 55,            /*!< osdA_int */
    GLB_DSP_ALL_INT_OSDB_INT = 56,            /*!< osdB_int */
    GLB_DSP_ALL_INT_OSD_PB_INT = 57,          /*!< osd_pb_int */
    GLB_DSP_ALL_INT_RSV7_INT = 58,            /*!< rsv7 */
    GLB_DSP_ALL_INT_MIPI_DSI_INT = 59,        /*!< mipi_dsi_int */
    GLB_DSP_ALL_INT_RSV8_INT = 60,            /*!< rsv8 */
    GLB_DSP_ALL_INT_MM_TIMER_IRQ2 = 61,       /*!< mm_timer_irq2 */
    GLB_DSP_ALL_INT_MM_TIMER_IRQ3 = 62,       /*!< mm_timer_irq3 */
    GLB_DSP_ALL_INT_MM_WDT_IRQ = 63,          /*!< mm_wdt_irq */
} GLB_DSP_ALL_INT_Type;

/**
 *  @brief GLB MCU all interrupt type definition
 */
typedef enum {
    GLB_MCU_ALL_INT_BMX_ERR_INT = 0,                       /*!< bmx_err_intmcu_dec_err_int */
    GLB_MCU_ALL_INT_BMX_TIMEOUT_INT_MCU_TIMEOUT_INT = 1,   /*!< bmx_timeout_intmcu_timeout_int */
    GLB_MCU_ALL_INT_IPC0_NP2AP_IRQ = 2,                    /*!< ipc0_np2ap_irq */
    GLB_MCU_ALL_INT_IPC0_AP2NP_IRQ = 3,                    /*!< ipc0_ap2np_irq */
    GLB_MCU_ALL_INT_AUDIO_INT = 4,                         /*!< audio_int */
    GLB_MCU_ALL_INT_RF_TOP_INT_0 = 5,                      /*!< rf_top_int[0] */
    GLB_MCU_ALL_INT_RF_TOP_INT_1 = 6,                      /*!< rf_top_int[1] */
    GLB_MCU_ALL_INT_LZ4_INT = 7,                           /*!< lz4_int */
    GLB_MCU_ALL_INT_RSV8 = 8,                              /*!< rsv8 */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_GMAC_INT = 9,              /*!< sec_eng_id0_gmac_int */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_CDET_INT = 10,             /*!< sec_eng_id0_cdet_int */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_PKA_INT = 11,              /*!< sec_eng_id0_pka_int */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_TRNG_INT = 12,             /*!< sec_eng_id0_trng_int */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_AES_INT = 13,              /*!< sec_eng_id0_aes_int */
    GLB_MCU_ALL_INT_SEC_ENG_ID0_SHA_INT = 14,              /*!< sec_eng_id0_sha_int */
    GLB_MCU_ALL_INT_DMA_INTR_ALL = 15,                     /*!< DMA_INTR_ALL */
    GLB_MCU_ALL_INT_DMA2_INTR_ALL = 16,                    /*!< DMA2_INTR_ALL */
    GLB_MCU_ALL_INT_SDH_MMC1_INT_SDH2PMU_WAKEUP_INT1 = 17, /*!< sdh_mmc1_intsdh2pmu_wakeup_int1 */
    GLB_MCU_ALL_INT_MM_IRQ_ALL = 18,                       /*!< mm_irq_all */
    GLB_MCU_ALL_INT_IRTX_INT = 19,                         /*!< irtx_int */
    GLB_MCU_ALL_INT_IRRX_INT = 20,                         /*!< irrx_int */
    GLB_MCU_ALL_INT_USB_INT = 21,                          /*!< usb_int */
    GLB_MCU_ALL_INT_AUPDM_INT = 22,                        /*!< aupdm_int */
    GLB_MCU_ALL_INT_SF_CTRL_ID0_INT = 23,                  /*!< sf_ctrl_id0_int */
    GLB_MCU_ALL_INT_EMAC_INT = 24,                         /*!< emac_int */
    GLB_MCU_ALL_INT_GPADC_DMA_INT = 25,                    /*!< gpadc_dma_int */
    GLB_MCU_ALL_INT_EFUSE_INT = 26,                        /*!< efuse_int */
    GLB_MCU_ALL_INT_SPI_0_INT = 27,                        /*!< spi_0_int */
    GLB_MCU_ALL_INT_UART_IRQ = 28,                         /*!< uart_irq */
    GLB_MCU_ALL_INT_UART1_IRQ = 29,                        /*!< uart1_irq */
    GLB_MCU_ALL_INT_UART2_IRQ = 30,                        /*!< uart2_irq */
    GLB_MCU_ALL_INT_GPIO_DMA_INT = 31,                     /*!< gpio_dma_int */
    GLB_MCU_ALL_INT_I2C_0_INT = 32,                        /*!< i2c_0_int */
    GLB_MCU_ALL_INT_PWM_INT = 33,                          /*!< pwm_int */
    GLB_MCU_ALL_INT_IPC1_NP2AP_IRQ = 34,                   /*!< ipc1_np2ap_irq */
    GLB_MCU_ALL_INT_IPC1_AP2NP_IRQ = 35,                   /*!< ipc1_ap2np_irq */
    GLB_MCU_ALL_INT_TIMER0_2_IRQ = 36,                     /*!< timer0_2_irq */
    GLB_MCU_ALL_INT_TIMER0_3_IRQ = 37,                     /*!< timer0_3_irq */
    GLB_MCU_ALL_INT_WDT0_IRQ = 38,                         /*!< wdt0_irq */
    GLB_MCU_ALL_INT_I2C_1_INT = 39,                        /*!< i2c_1_int */
    GLB_MCU_ALL_INT_I2S0_INT = 40,                         /*!< i2s0_int */
    GLB_MCU_ALL_INT_RSV41 = 41,                            /*!< rsv41 */
    GLB_MCU_ALL_INT_RSV42 = 42,                            /*!< rsv42 */
    GLB_MCU_ALL_INT_ANA_OCP_OUT_TO_CPU_IRQ = 43,           /*!< ana_ocp_out_to_cpu_irq[2:0] */
    GLB_MCU_ALL_INT_GPIO_IRQ = 44,                         /*!< gpio_irq */
    GLB_MCU_ALL_INT_DM_IRQ = 45,                           /*!< dm_irq */
    GLB_MCU_ALL_INT_BT_IRQ = 46,                           /*!< bt_irq */
    GLB_MCU_ALL_INT_M154_REQ_ENH_ACK_INT = 47,             /*!< m154_req_enh_ack_int */
    GLB_MCU_ALL_INT_M154_INT = 48,                         /*!< m154_int */
    GLB_MCU_ALL_INT_M154_AES_INT = 49,                     /*!< m154_aes_int */
    GLB_MCU_ALL_INT_PDS_INT = 50,                          /*!< pds_int */
    GLB_MCU_ALL_INT_HBN_IRQ_OUT_0 = 51,                    /*!< hbn_irq_out[0] */
    GLB_MCU_ALL_INT_HBN_IRQ_OUT_1 = 52,                    /*!< hbn_irq_out[1] */
    GLB_MCU_ALL_INT_BOR_OUT = 53,                          /*!< bor_out */
    GLB_MCU_ALL_INT_WIFI_TO_CPU_IRQ_N = 54,                /*!< wifi_to_cpu_irq_n */
    GLB_MCU_ALL_INT_BZ_PHY_INT = 55,                       /*!< bz_phy_int */
    GLB_MCU_ALL_INT_BLE_INT = 56,                          /*!< ble_int */
    GLB_MCU_ALL_INT_MAC_INT_TX_RX_TIMER = 57,              /*!< mac_int_tx_rx_timer */
    GLB_MCU_ALL_INT_MAC_INT_TX_RX_MISC = 58,               /*!< mac_int_tx_rx_misc */
    GLB_MCU_ALL_INT_MAC_INT_RX_TRIGGER = 59,               /*!< mac_int_rx_trigger */
    GLB_MCU_ALL_INT_MAC_INT_TX_TRIGGER = 60,               /*!< mac_int_tx_trigger */
    GLB_MCU_ALL_INT_MAC_INT_GEN = 61,                      /*!< mac_int_gen */
    GLB_MCU_ALL_INT_MAC_INT_PROT_TRIGGER = 62,             /*!< mac_int_prot_trigger */
    GLB_MCU_ALL_INT_WIFI_IPC = 63,                         /*!< wifi_ipc */
} GLB_MCU_ALL_INT_Type;

/**
 *  @brief GLB LP all interrupt type definition
 */
typedef enum {
    GLB_LP_ALL_INT_BMX_ERR_INT = 0,                       /*!< bmx_err_int */
    GLB_LP_ALL_INT_BMX_TIMEOUT_INT_MCU_TIMEOUT_INT = 1,   /*!< bmx_timeout_intmcu_timeout_int */
    GLB_LP_ALL_INT_IPC0_NP2AP_IRQ = 2,                    /*!< ipc0_np2ap_irq */
    GLB_LP_ALL_INT_IPC0_AP2NP_IRQ = 3,                    /*!< ipc0_ap2np_irq */
    GLB_LP_ALL_INT_AUDIO_INT = 4,                         /*!< audio_int */
    GLB_LP_ALL_INT_RF_TOP_INT_0 = 5,                      /*!< rf_top_int[0] */
    GLB_LP_ALL_INT_RF_TOP_INT_1 = 6,                      /*!< rf_top_int[1] */
    GLB_LP_ALL_INT_LZ4_INT = 7,                           /*!< lz4_int */
    GLB_LP_ALL_INT_RSV8 = 8,                              /*!< rsv8 */
    GLB_LP_ALL_INT_SEC_ENG_ID0_GMAC_INT = 9,              /*!< sec_eng_id0_gmac_int */
    GLB_LP_ALL_INT_SEC_ENG_ID0_CDET_INT = 10,             /*!< sec_eng_id0_cdet_int */
    GLB_LP_ALL_INT_SEC_ENG_ID0_PKA_INT = 11,              /*!< sec_eng_id0_pka_int */
    GLB_LP_ALL_INT_SEC_ENG_ID0_TRNG_INT = 12,             /*!< sec_eng_id0_trng_int */
    GLB_LP_ALL_INT_SEC_ENG_ID0_AES_INT = 13,              /*!< sec_eng_id0_aes_int */
    GLB_LP_ALL_INT_SEC_ENG_ID0_SHA_INT = 14,              /*!< sec_eng_id0_sha_int */
    GLB_LP_ALL_INT_DMA_INTR_ALL = 15,                     /*!< DMA_INTR_ALL */
    GLB_LP_ALL_INT_DMA2_INTR_ALL = 16,                    /*!< DMA2_INTR_ALL */
    GLB_LP_ALL_INT_SDH_MMC1_INT_SDH2PMU_WAKEUP_INT1 = 17, /*!< sdh_mmc1_intsdh2pmu_wakeup_int1 */
    GLB_LP_ALL_INT_MM_IRQ_ALL = 18,                       /*!< mm_irq_all */
    GLB_LP_ALL_INT_IRTX_INT = 19,                         /*!< irtx_int */
    GLB_LP_ALL_INT_IRRX_INT = 20,                         /*!< irrx_int */
    GLB_LP_ALL_INT_USB_INT = 21,                          /*!< usb_int */
    GLB_LP_ALL_INT_AUPDM_INT = 22,                        /*!< aupdm_int */
    GLB_LP_ALL_INT_SF_CTRL_ID0_INT = 23,                  /*!< sf_ctrl_id0_int */
    GLB_LP_ALL_INT_EMAC_INT = 24,                         /*!< emac_int */
    GLB_LP_ALL_INT_GPADC_DMA_INT = 25,                    /*!< gpadc_dma_int */
    GLB_LP_ALL_INT_EFUSE_INT = 26,                        /*!< efuse_int */
    GLB_LP_ALL_INT_SPI_0_INT = 27,                        /*!< spi_0_int */
    GLB_LP_ALL_INT_UART_IRQ = 28,                         /*!< uart_irq */
    GLB_LP_ALL_INT_UART1_IRQ = 29,                        /*!< uart1_irq */
    GLB_LP_ALL_INT_UART2_IRQ = 30,                        /*!< uart2_irq */
    GLB_LP_ALL_INT_GPIO_DMA_INT = 31,                     /*!< gpio_dma_int */
    GLB_LP_ALL_INT_I2C_0_INT = 32,                        /*!< i2c_0_int */
    GLB_LP_ALL_INT_PWM_INT = 33,                          /*!< pwm_int */
    GLB_LP_ALL_INT_IPC1_NP2AP_IRQ = 34,                   /*!< ipc1_np2ap_irq */
    GLB_LP_ALL_INT_IPC1_AP2NP_IRQ = 35,                   /*!< ipc1_ap2np_irq */
    GLB_LP_ALL_INT_TIMER0_2_IRQ = 36,                     /*!< timer0_2_irq */
    GLB_LP_ALL_INT_TIMER0_3_IRQ = 37,                     /*!< timer0_3_irq */
    GLB_LP_ALL_INT_WDT0_IRQ = 38,                         /*!< wdt0_irq */
    GLB_LP_ALL_INT_I2C_1_INT = 39,                        /*!< i2c_1_int */
    GLB_LP_ALL_INT_I2S0_INT = 40,                         /*!< i2s0_int */
    GLB_LP_ALL_INT_RSV41 = 41,                            /*!< rsv41 */
    GLB_LP_ALL_INT_RSV42 = 42,                            /*!< rsv42 */
    GLB_LP_ALL_INT_ANA_OCP_OUT_TO_CPU_IRQ = 43,           /*!< ana_ocp_out_to_cpu_irq[2:0] */
    GLB_LP_ALL_INT_GPIO_IRQ = 44,                         /*!< gpio_irq */
    GLB_LP_ALL_INT_DM_IRQ = 45,                           /*!< dm_irq */
    GLB_LP_ALL_INT_BT_IRQ = 46,                           /*!< bt_irq */
    GLB_LP_ALL_INT_M154_REQ_ENH_ACK_INT = 47,             /*!< m154_req_enh_ack_int */
    GLB_LP_ALL_INT_M154_INT = 48,                         /*!< m154_int */
    GLB_LP_ALL_INT_M154_AES_INT = 49,                     /*!< m154_aes_int */
    GLB_LP_ALL_INT_PDS_INT = 50,                          /*!< pds_int */
    GLB_LP_ALL_INT_HBN_IRQ_OUT_0 = 51,                    /*!< hbn_irq_out[0] */
    GLB_LP_ALL_INT_HBN_IRQ_OUT_1 = 52,                    /*!< hbn_irq_out[1] */
    GLB_LP_ALL_INT_BOR_OUT = 53,                          /*!< bor_out */
    GLB_LP_ALL_INT_WIFI_TO_CPU_IRQ_N = 54,                /*!< wifi_to_cpu_irq_n */
    GLB_LP_ALL_INT_BZ_PHY_INT = 55,                       /*!< bz_phy_int */
    GLB_LP_ALL_INT_BLE_INT = 56,                          /*!< ble_int */
    GLB_LP_ALL_INT_MAC_INT_TX_RX_TIMER = 57,              /*!< mac_int_tx_rx_timer */
    GLB_LP_ALL_INT_MAC_INT_TX_RX_MISC = 58,               /*!< mac_int_tx_rx_misc */
    GLB_LP_ALL_INT_MAC_INT_RX_TRIGGER = 59,               /*!< mac_int_rx_trigger */
    GLB_LP_ALL_INT_MAC_INT_TX_TRIGGER = 60,               /*!< mac_int_tx_trigger */
    GLB_LP_ALL_INT_MAC_INT_GEN = 61,                      /*!< mac_int_gen */
    GLB_LP_ALL_INT_MAC_INT_PROT_TRIGGER = 62,             /*!< mac_int_prot_trigger */
    GLB_LP_ALL_INT_WIFI_IPC = 63,                         /*!< wifi_ipc */
} GLB_LP_ALL_INT_Type;

/**
 *  @brief GLB dsp muxpll 320M clock type definition
 */
typedef enum {
    GLB_DSP_MUXPLL_SEL_WIFIPLL_320M, /*!< dsp muxpll select wifipll 320M */
    GLB_DSP_MUXPLL_SEL_AUPLL_DIV1,   /*!< dsp muxpll select aupll div1 */
} GLB_DSP_MUXPLL_320M_CLK_SEL_Type;

/**
 *  @brief GLB dsp muxpll 240M clock type definition
 */
typedef enum {
    GLB_DSP_MUXPLL_SEL_WIFIPLL_240M, /*!< dsp muxpll select wifipll 240M */
    GLB_DSP_MUXPLL_SEL_AUPLL_DIV2,   /*!< dsp muxpll select aupll div2 */
} GLB_DSP_MUXPLL_240M_CLK_SEL_Type;

/**
 *  @brief GLB dsp muxpll 160M clock type definition
 */
typedef enum {
    GLB_DSP_MUXPLL_SEL_WIFIPLL_160M, /*!< dsp muxpll select wifipll 160M */
    GLB_DSP_MUXPLL_SEL_CPUPLL_160M,  /*!< dsp muxpll select cpupll 160M */
} GLB_DSP_MUXPLL_160M_CLK_SEL_Type;

/**
 *  @brief GLB mcu muxpll 160M clock type definition
 */
typedef enum {
    GLB_MCU_MUXPLL_SEL_WIFIPLL_160M,    /*!< mcu muxpll select wifipll 160M */
    GLB_MCU_MUXPLL_SEL_TOP_CPUPLL_160M, /*!< mcu muxpll select top cpupll 160M */
    GLB_MCU_MUXPLL_SEL_TOP_AUPLL_DIV2,  /*!< mcu muxpll select top aupll div2 */
    GLB_MCU_MUXPLL_SEL_AUPLL_DIV2P5,    /*!< mcu muxpll select aupll div2p5 */
} GLB_MCU_MUXPLL_160M_CLK_SEL_Type;

/**
 *  @brief GLB mcu muxpll 80M clock type definition
 */
typedef enum {
    GLB_MCU_MUXPLL_SEL_WIFIPLL_80M,    /*!< mcu muxpll select wifipll 80M */
    GLB_MCU_MUXPLL_SEL_TOP_CPUPLL_80M, /*!< mcu muxpll select top cpupll 80M */
    GLB_MCU_MUXPLL_SEL_AUPLL_DIV5,     /*!< mcu muxpll select aupll div5 */
    GLB_MCU_MUXPLL_SEL_AUPLL_DIV6,     /*!< mcu muxpll select aupll div6 */
} GLB_MCU_MUXPLL_80M_CLK_SEL_Type;

/**
 *  @brief GLB pll clock gate type definition
 */
typedef enum {
    GLB_PLL_CGEN_MM_WIFIPLL_160M,  /*!< pll cgen mm wifipll 160m */
    GLB_PLL_CGEN_MM_WIFIPLL_240M,  /*!< pll cgen mm wifipll 240m */
    GLB_PLL_CGEN_MM_WIFIPLL_320M,  /*!< pll cgen mm wifipll 320m */
    GLB_PLL_CGEN_MM_AUPLL_DIV1,    /*!< pll cgen mm aupll div1 */
    GLB_PLL_CGEN_MM_AUPLL_DIV2,    /*!< pll cgen mm aupll div2 */
    GLB_PLL_CGEN_EMI_CPUPLL_400M,  /*!< pll cgen emi cpupll 400m */
    GLB_PLL_CGEN_EMI_CPUPLL_200M,  /*!< pll cgen emi cpupll 200m */
    GLB_PLL_CGEN_EMI_WIFIPLL_320M, /*!< pll cgen emi wifipll 320m */
    GLB_PLL_CGEN_EMI_AUPLL_DIV1,   /*!< pll cgen emi aupll div1 */
    GLB_PLL_CGEN_TOP_CPUPLL_80M,   /*!< pll cgen top cpupll 80m */
    GLB_PLL_CGEN_TOP_CPUPLL_100M,  /*!< pll cgen top cpupll 100m */
    GLB_PLL_CGEN_TOP_CPUPLL_160M,  /*!< pll cgen top cpupll 160m */
    GLB_PLL_CGEN_TOP_CPUPLL_400M,  /*!< pll cgen top cpupll 400m */
    GLB_PLL_CGEN_TOP_WIFIPLL_240M, /*!< pll cgen top wifipll 240m */
    GLB_PLL_CGEN_TOP_WIFIPLL_320M, /*!< pll cgen top wifipll 320m */
    GLB_PLL_CGEN_TOP_AUPLL_DIV2,   /*!< pll cgen top aupll div2 */
    GLB_PLL_CGEN_TOP_AUPLL_DIV1,   /*!< pll cgen top aupll div1 */
} GLB_PLL_CGEN_Type;

/**
 *  @brief GLB mcu system clock type definition
 */
typedef enum {
    GLB_MCU_SYS_CLK_RC32M,        /*!< use RC32M as system clock frequency */
    GLB_MCU_SYS_CLK_XTAL,         /*!< use XTAL as system clock */
    GLB_MCU_SYS_CLK_CPUPLL_400M,  /*!< use CPUPLL output 400M as system clock */
    GLB_MCU_SYS_CLK_WIFIPLL_240M, /*!< use WIFIPLL output 240M as system clock */
    GLB_MCU_SYS_CLK_WIFIPLL_320M, /*!< use WIFIPLL output 320M as system clock */
} GLB_MCU_SYS_CLK_Type;

/**
 *  @brief GLB dsp system clock type definition
 */
typedef enum {
    GLB_DSP_SYS_CLK_RC32M,           /*!< use RC32M as system clock frequency */
    GLB_DSP_SYS_CLK_XTAL,            /*!< use XTAL as system clock */
    GLB_DSP_SYS_CLK_MM_WIFIPLL_240M, /*!< use WIFIPLL 240M as system clock */
    GLB_DSP_SYS_CLK_MM_WIFIPLL_320M, /*!< use WIFIPLL 320M as system clock */
    GLB_DSP_SYS_CLK_CPUPLL_400M,     /*!< use CPUPLL output 400M as system clock */
} GLB_DSP_SYS_CLK_Type;

/**
 *  @brief GLB dsp pbus clock type definition
 */
typedef enum {
    GLB_DSP_SYS_PBCLK_RC32M,           /*!< use rc32m as pbus clock */
    GLB_DSP_SYS_PBCLK_XTAL,            /*!< use xtal as pbus clock */
    GLB_DSP_SYS_PBCLK_MM_WIFIPLL_160M, /*!< use mm_wifipll_160m_clk as pbus clock */
    GLB_DSP_SYS_PBCLK_CPUPLL_160M,     /*!< use cpupll_160m_clk as pbus clock */
    GLB_DSP_SYS_PBCLK_MM_WIFIPLL_240M, /*!< use mm_wifipll_240m_clk as pbus clock */
} GLB_DSP_SYS_PBCLK_Type;

/**
 *  @brief GLB dsp system clock type definition
 */
typedef enum {
    GLB_PLL_REFCLK_XTAL = 0,  /*!< use XTAL as pll ref clock */
    GLB_PLL_REFCLK_RC32M = 3, /*!< use RC32M as pll ref clock */
} GLB_PLL_REF_CLK_Type;

typedef struct {
    uint8_t clkpllRefdivRatio;  /*!< xxx pll_refdiv_ratio */
    uint8_t clkpllIntFracSw;    /*!< xxx pll_int_frac_sw */
    uint8_t clkpllIcp1u;        /*!< xxx pll_icp_1u */
    uint8_t clkpllIcp5u;        /*!< xxx pll_icp_5u */
    uint8_t clkpllRz;           /*!< xxx pll_rz */
    uint8_t clkpllCz;           /*!< xxx pll_cz */
    uint8_t clkpllC3;           /*!< xxx pll_c3 */
    uint8_t clkpllR4Short;      /*!< xxx pll_r4_short */
    uint8_t clkpllC4En;         /*!< xxx pll_r4_en */
    uint8_t clkpllSelSampleClk; /*!< xxx pll_sel_sample_clk */
    uint8_t clkpllVcoSpeed;     /*!< xxx pll_vco_speed */
    uint8_t clkpllSdmCtrlHw;    /*!< xxx pll_sdm_ctrl_hw */
    uint8_t clkpllSdmBypass;    /*!< xxx pll_sdm_bypass */
} GLB_WAC_PLL_CFG_BASIC_Type;

typedef struct {
    const GLB_WAC_PLL_CFG_BASIC_Type *const basicCfg; /*!< pll basic configuration */
    uint32_t clkpllSdmin;                             /*!< pll sdmin value */
} GLB_WAC_PLL_Cfg_Type;

typedef struct {
    uint8_t clkpllRefdivRatio;  /*!< xxx pll_refdiv_ratio */
    uint8_t clkpllSelSampleClk; /*!< xxx pll_sel_sample_clk */
    uint8_t clkpllVcoSpeed;     /*!< xxx pll_vco_speed */
    uint8_t clkpllEvenDivEn;    /*!< xxx pll_even_div_en */
    uint8_t clkpllEvenDivRatio; /*!< xxx pll_even_div_ratio */
} GLB_MU_PLL_CFG_BASIC_Type;

typedef struct {
    const GLB_MU_PLL_CFG_BASIC_Type *const basicCfg; /*!< pll basic configuration */
    uint32_t clkpllSdmin;                            /*!< pll sdmin value */
} GLB_MU_PLL_Cfg_Type;

/**
 *  @brief GLB CAM clock type definition
 */
typedef enum {
    GLB_CAM_CLK_XCLK,        /*!< Select XCLK as CAM clock */
    GLB_CAM_CLK_WIFIPLL_96M, /*!< Select WIFIPLL_96M as CAM clock */
    GLB_CAM_CLK_CPUPLL_100M, /*!< Select CPUPLL_96M as CAM clock */
} GLB_CAM_CLK_Type;

/**
 *  @brief GLB SDH clock type definition
 */
typedef enum {
    GLB_SDH_CLK_WIFIPLL_96M, /*!< Select WIFIPLL_96M as SDH clock */
    GLB_SDH_CLK_CPUPLL_100M, /*!< Select CPUPLL_100M as SDH clock */
} GLB_SDH_CLK_Type;

/**
 *  @brief GLB UART sig swap group type definition
 */
typedef enum {
    GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11,  /*!< SWAP UART SIG GROUP GPIO0  -  GPIO11 */
    GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, /*!< SWAP UART SIG GROUP GPIO12 -  GPIO23 */
    GLB_UART_SIG_SWAP_GRP_GPIO24_GPIO35, /*!< SWAP UART SIG GROUP GPIO24 -  GPIO35 */
    GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, /*!< SWAP UART SIG GROUP GPIO36 -  GPIO45 */
} GLB_UART_SIG_SWAP_GRP_Type;

/**
 *  @brief GLB I2S output ref clock type definition
 */
typedef enum {
    GLB_I2S_OUT_REF_CLK_NONE, /*!< no output reference clock on I2S_0 ref_clock port */
    GLB_I2S_OUT_REF_CLK_SRC,  /*!< output reference clock on I2S_0 ref_clock port */
} GLB_I2S_OUT_REF_CLK_Type;

/**
 *  @brief GLB DMA clock ID type definition
 */
typedef enum {
    GLB_DMA0_CLK_CH0, /*!< DMA0 clock ID:channel 0 */
    GLB_DMA0_CLK_CH1, /*!< DMA0 clock ID:channel 1 */
    GLB_DMA0_CLK_CH2, /*!< DMA0 clock ID:channel 2 */
    GLB_DMA0_CLK_CH3, /*!< DMA0 clock ID:channel 3 */
    GLB_DMA0_CLK_CH4, /*!< DMA0 clock ID:channel 4 */
    GLB_DMA0_CLK_CH5, /*!< DMA0 clock ID:channel 5 */
    GLB_DMA0_CLK_CH6, /*!< DMA0 clock ID:channel 6 */
    GLB_DMA0_CLK_CH7, /*!< DMA0 clock ID:channel 7 */
    GLB_DMA1_CLK_CH0, /*!< DMA1 clock ID:channel 0 */
    GLB_DMA1_CLK_CH1, /*!< DMA1 clock ID:channel 1 */
    GLB_DMA1_CLK_CH2, /*!< DMA1 clock ID:channel 2 */
    GLB_DMA1_CLK_CH3, /*!< DMA1 clock ID:channel 3 */
} GLB_DMA_CLK_ID_Type;

/**
 *  @brief GLB peripheral DMA type definition
 */
typedef enum {
    GLB_PERI_DMA_UART0_RX =  0, /*!< uart_rx  */
    GLB_PERI_DMA_UART0_TX =  1, /*!< uart_tx  */
    GLB_PERI_DMA_UART1_RX =  2, /*!< uart1_rx */
    GLB_PERI_DMA_UART1_TX =  3, /*!< uart1_tx */
    GLB_PERI_DMA_UART2_RX =  4, /*!< uart2_rx */
    GLB_PERI_DMA_UART2_TX =  5, /*!< uart2_tx */
    GLB_PERI_DMA_I2C_0_RX =  6, /*!< i2c_0_rx */
    GLB_PERI_DMA_I2C_0_TX =  7, /*!< i2c_0_tx */
    GLB_PERI_DMA_IRTX_TX  =  8, /*!< irtx_tx  */
    GLB_PERI_DMA_GPIO_TX  =  9, /*!< gpio_tx  */
    GLB_PERI_DMA_SPI_RX   = 10, /*!< spi_rx   */
    GLB_PERI_DMA_SPI_TX   = 11, /*!< spi_tx   */
    GLB_PERI_DMA_AUDIO_RX = 12, /*!< audio_rx */
    GLB_PERI_DMA_AUDIO_TX = 13, /*!< audio_tx */
    GLB_PERI_DMA_I2C_1_RX = 14, /*!< i2c_1_rx */
    GLB_PERI_DMA_I2C_1_TX = 15, /*!< i2c_1_tx */
    GLB_PERI_DMA_I2S_0_RX = 16, /*!< i2s_0_rx */
    GLB_PERI_DMA_I2S_0_TX = 17, /*!< i2s_0_tx */
    GLB_PERI_DMA_PDM_RX   = 18, /*!< pdm_rx   */
    GLB_PERI_DMA_PADC     = 19, /*!< padc     */
    GLB_PERI_DMA_GAUGE    = 20, /*!< gauge    */
    GLB_PERI_DMA_GPADC    = 22, /*!< gpadc    */
    GLB_PERI_DMA_GPDAC_TX = 23, /*!< gpdac_tx */
} GLB_PERI_DMA_Type;

/**
 *  @brief GLB DMA CN selection type definition
 */
typedef enum {
    GLB_PERI_DMA_CN_SEL_DMA0 = 0, /*!< peripheral DMA channel select DMA0 */
    GLB_PERI_DMA_CN_SEL_DMA1 = 1, /*!< peripheral DMA channel select DMA1 */
} GLB_PERI_DMA_CN_SEL_Type;

/**
 *  @brief GLB clock source type definition
 */
typedef enum {
    GLB_IR_CLK_SRC_XCLK, /*!< IR clock source select XCLK */
} GLB_IR_CLK_SRC_Type;

/**
 *  @brief GLB flash clock type definition
 */
typedef enum {
    GLB_SFLASH_CLK_120M_WIFIPLL, /*!< Select WIFIPLL 120M as flash clock */
    GLB_SFLASH_CLK_XTAL,         /*!< Select XTAL as flash clock */
    GLB_SFLASH_CLK_100M_CPUPLL,  /*!< Select CPUPLL 100M as flash clock */
    GLB_SFLASH_CLK_80M_MUXPLL,   /*!< Select MUXPLL 80M as flash clock */
    GLB_SFLASH_CLK_BCLK,         /*!< Select BCLK as flash clock */
    GLB_SFLASH_CLK_96M_WIFIPLL,  /*!< Select WIFIPLL 96M as flash clock */
} GLB_SFLASH_CLK_Type;

/**
 *  @brief GLB I2C clock type definition
 */
typedef enum {
    GLB_I2C_CLK_BCLK, /*!< Select bus clk as I2C clock */
    GLB_I2C_CLK_XCLK, /*!< Select xclk as I2C clock */
} GLB_I2C_CLK_Type;

/**
 *  @brief GLB SPI clock type definition
 */
typedef enum {
    GLB_SPI_CLK_MCU_MUXPLL_160M, /*!< Select MCU MUXPLL 160M as SPI clock */
    GLB_SPI_CLK_XCLK,            /*!< Select xclk as SPI clock */
} GLB_SPI_CLK_Type;

/**
 *  @brief GLB PWM1 io type definition
 */
typedef enum {
    GLB_PWM1_IO_SINGLE_END, /*!< Select pwm1 io single end */
    GLB_PWM1_IO_DIFF_END,   /*!< Select pwm1 io differential end for BLDC */
} GLB_PWM1_IO_SEL_Type;

/**
 *  @brief GLB PWM2 io type definition
 */
typedef enum {
    GLB_PWM2_IO_SINGLE_END,      /*!< Select pwm2 io single end */
    GLB_PWM2_IO_SINGLE_END_BLDC, /*!< Select pwm2 io single end BLDC */
} GLB_PWM2_IO_SEL_Type;

/**
 *  @brief GLB PDM io type definition
 */
typedef enum {
    GLB_PDM_IO_SEL_AUDIO_TOP, /*!< Select audio_top PDM */
    GLB_PDM_IO_SEL_AUPDM_TOP, /*!< Select aupdm_top PDM */
} GLB_PDM_IO_SEL_Type;

/**
 *  @brief GLB SPI pad action type definition
 */
typedef enum {
    GLB_SPI_PAD_ACT_AS_SLAVE,  /*!< SPI pad act as slave */
    GLB_SPI_PAD_ACT_AS_MASTER, /*!< SPI pad act as master */
} GLB_SPI_PAD_ACT_AS_Type;

/**
 *  @brief GLB AHB software type definition
 */
typedef enum {
    GLB_AHB_MCU_SW_RSV0 = 0,
    GLB_AHB_MCU_SW_RSV1 = 1,
    GLB_AHB_MCU_SW_WIFI = 4,
    GLB_AHB_MCU_SW_BTDM = 8,
    GLB_AHB_MCU_SW_ZIGBEE = 9,
    GLB_AHB_MCU_SW_BLE2 = 10,
    GLB_AHB_MCU_SW_ZIGBEE2 = 11,
    GLB_AHB_MCU_SW_EMI_MISC = 16,
    GLB_AHB_MCU_SW_PSRAM0_CTRL = 17,
    GLB_AHB_MCU_SW_PSRAM1_CTRL = 18,
    GLB_AHB_MCU_SW_USB_EMAC = 19,
    GLB_AHB_MCU_SW_RSV20 = 20,
    GLB_AHB_MCU_SW_AUDIO = 21,
    GLB_AHB_MCU_SW_SDH = 22,
    GLB_AHB_MCU_SW_RSV23 = 23,
    GLB_AHB_MCU_SW_DMA2 = 24,
    GLB_AHB_MCU_SW_GLB = 32,
    GLB_AHB_MCU_SW_MIX = 33,
    GLB_AHB_MCU_SW_GPIP = 34,
    GLB_AHB_MCU_SW_SEC_DBG = 35,
    GLB_AHB_MCU_SW_SEC_ENG = 36,
    GLB_AHB_MCU_SW_TZ1 = 37,
    GLB_AHB_MCU_SW_TZ2 = 38,
    GLB_AHB_MCU_SW_EFUSE = 39,
    GLB_AHB_MCU_SW_CCI = 40,
    GLB_AHB_MCU_SW_MCU_PERI_BUS = 41,
    GLB_AHB_MCU_SW_RSV42 = 42,
    GLB_AHB_MCU_SW_SF = 43,
    GLB_AHB_MCU_SW_DMA = 44,
    GLB_AHB_MCU_SW_SDU = 45,
    GLB_AHB_MCU_SW_PDS = 46,
    GLB_AHB_MCU_SW_RSV47 = 47,
    GLB_AHB_MCU_SW_UART0 = 48,
    GLB_AHB_MCU_SW_UART1 = 49,
    GLB_AHB_MCU_SW_SPI = 50,
    GLB_AHB_MCU_SW_I2C = 51,
    GLB_AHB_MCU_SW_PWM = 52,
    GLB_AHB_MCU_SW_TIMER = 53,
    GLB_AHB_MCU_SW_IR_REMOTE = 54,
    GLB_AHB_MCU_SW_CHECKSUM = 55,
    GLB_AHB_MCU_SW_IPC = 56,
    GLB_AHB_MCU_SW_I2C1 = 57,
    GLB_AHB_MCU_SW_UART2 = 58,
    GLB_AHB_MCU_SW_I2S = 59,
    GLB_AHB_MCU_SW_AUPDM = 60,
    GLB_AHB_MCU_SW_LZ4 = 61,
    GLB_AHB_MCU_SW_RSV62 = 62,
    GLB_AHB_MCU_SW_RSV63 = 63,
    GLB_AHB_MCU_SW_PWRON_RST = 64,
    GLB_AHB_MCU_SW_CPU_RESET = 65,
    GLB_AHB_MCU_SW_SYS_RESET = 66,
    GLB_AHB_MCU_SW_PICO_RESET = 67,
    GLB_AHB_MCU_SW_CPU2_RESET = 68,
    GLB_AHB_MCU_SW_CHIP_RESET = 69,
    GLB_AHB_MCU_SW_WL_WDT_RESET_MM_EN = 70,
    GLB_AHB_MCU_SW_MMWDT2WL_RST_MSK = 71,
} GLB_AHB_MCU_SW_Type;

/**
 *  @brief GLB AHB software type definition
 */
typedef enum {
    GLB_AHB_DSP_SW_REG_CTRL_SYS_RESET = 0,
    GLB_AHB_DSP_SW_REG_CTRL_PWRON_RST = 2,
    GLB_AHB_DSP_SW_REG_CTRL_MMCPU0_RESET = 8,
    GLB_AHB_DSP_SW_SWRST_MM_MISC = 32,
    GLB_AHB_DSP_SW_SWRST_DMA = 33,
    GLB_AHB_DSP_SW_SWRST_UART0 = 34,
    GLB_AHB_DSP_SW_SWRST_I2C0 = 35,
    GLB_AHB_DSP_SW_SWRST_I2C1 = 36,
    GLB_AHB_DSP_SW_SWRST_IPC = 37,
    GLB_AHB_DSP_SW_SWRST_DMA2D = 38,
    GLB_AHB_DSP_SW_SWRST_SPI = 40,
    GLB_AHB_DSP_SW_SWRST_TIMER = 41,
    GLB_AHB_DSP_SW_SWRST_I2S0 = 42,
    GLB_AHB_DSP_SW_SWRST_I2S1 = 43,
    GLB_AHB_DSP_SW_SWRST_PDM0 = 44,
    GLB_AHB_DSP_SW_SWRST_PDM1 = 45,
    GLB_AHB_DSP_SW_SWRST_PUHS = 47,
    GLB_AHB_DSP_SW_SWRST_SUB_MISC = 64,
    GLB_AHB_DSP_SW_SWRST_SUB_MAIN = 65,
    GLB_AHB_DSP_SW_SWRST_SUB_TSRC = 66,
    GLB_AHB_DSP_SW_SWRST_DP_TSRC = 67,
    GLB_AHB_DSP_SW_SWRST_NR3D_CTRL = 68,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSA = 69,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSB = 70,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSC = 71,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSD = 72,
    GLB_AHB_DSP_SW_SWRST_MIPI = 73,
    GLB_AHB_DSP_SW_SWRST_SUB_REG = 80,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSE = 81,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSF = 82,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSG = 83,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSH = 84,
    GLB_AHB_DSP_SW_SWRST_CODEC_MISC = 96,
    GLB_AHB_DSP_SW_SWRST_MJPEG = 97,
    GLB_AHB_DSP_SW_SWRST_H264 = 98,
    GLB_AHB_DSP_SW_SWRST_MJPEG_DEC = 99,
    GLB_AHB_DSP_SW_SWRST_CNN = 100,
    GLB_AHB_DSP_SW_SWRST_VRAM = 112,
    GLB_AHB_DSP_SW_RG_IS_RST_N = 128,
} GLB_AHB_DSP_SW_Type;

/**
 *  @brief GLB dis reset type definition
 */
typedef enum {
    GLB_DISRST_GPIP = 2,
    GLB_DISRST_SEC_ENG = 4,
    GLB_DISRST_CCI = 8,
    GLB_DISRST_SF = 11,
    GLB_DISRST_UART0 = 16,
    GLB_DISRST_UART1 = 17,
    GLB_DISRST_SPI = 18,
    GLB_DISRST_I2C0 = 19,
    GLB_DISRST_PWM = 20,
    GLB_DISRST_TIMER = 21,
    GLB_DISRST_IR_REMOTE = 22,
    GLB_DISRST_CHECKSUM = 23,
    GLB_DISRST_IPC = 24,
    GLB_DISRST_I2C1 = 25,
    GLB_DISRST_UART2 = 26,
} GLB_DISRST_Type;

/**
 *  @brief GLB PKA clock type definition
 */
typedef enum {
    GLB_PKA_CLK_MCU_BCLK,        /*!< Select MCU_BCLK as PKA clock */
    GLB_PKA_CLK_MCU_MUXPLL_160M, /*!< Select MCU MUXPLL 160M as PKA clock */
} GLB_PKA_CLK_Type;

/**
 *  @brief GLB MCU software system reset type definition
 */
typedef enum {
    GLB_MCU_SW_SYSTEM_CTRL_MCU = 1, /*!< mcu reset */
    GLB_MCU_SW_SYSTEM_CTRL_LP = 3,  /*!< lp reset */
} GLB_MCU_SW_SYSTEM_Type;

/**
 *  @brief BMX arb mode type definition
 */
typedef enum {
    BMX_ARB_ROUND_ROBIN = 0, /*!< 0->round-robin */
    BMX_ARB_FIX = 1,         /*!< 1->fix */
} BMX_ARB_Type;

/**
 *  @brief BMX latch type definition
 */
typedef enum {
    BMX_LATCH_FIRST_ERROR = 0, /*!< 0->Latch first error */
    BMX_LATCH_LAST_ERROR = 1,  /*!< 1->Latch last error */
} BMX_LATCH_Type;

/**
 *  @brief BMX configuration structure type definition
 */
typedef struct {
    BMX_ARB_Type arbMod; /*!< 0->fix, 2->round-robin, 3->random */
    uint8_t timeoutEn;   /*!< Bus timeout enable: detect slave no reaponse in 1024 cycles */
} BMX_TO_Cfg_Type;

/**
 *  @brief BMX bus err type definition
 */
typedef enum {
    BMX_BUS_ERR_TRUSTZONE_DECODE, /*!< Bus trustzone decode error */
    BMX_BUS_ERR_ADDR_DECODE,      /*!< Bus addr decode error */
} BMX_BUS_ERR_Type;

/**
 *  @brief BMX bus err interrupt type definition
 */
typedef enum {
    BMX_ERR_INT_ERR, /*!< BMX bus err interrupt */
    BMX_ERR_INT_ALL, /*!< BMX bus err interrupt max num */
} BMX_ERR_INT_Type;

/**
 *  @brief BMX time out interrupt type definition
 */
typedef enum {
    BMX_TO_INT_TIMEOUT, /*!< BMX timeout interrupt */
    BMX_TO_INT_ALL,     /*!< BMX timeout interrupt max num */
} BMX_TO_INT_Type;

/**
 *  @brief GLB eth ref clock out type definition
 */
typedef enum {
    GLB_ETH_REF_CLK_OUT_OUTSIDE_50M, /*!< select outside 50MHz RMII ref clock */
    GLB_ETH_REF_CLK_OUT_INSIDE_50M,  /*!< select inside 50MHz RMII ref clock */
} GLB_ETH_REF_CLK_OUT_Type;

/**
 *  @brief GLB EM type definition
 */
typedef enum {
    GLB_WRAM160KB_EM0KB,  /*!< WRAM_160KB EM_0KB */
    GLB_WRAM144KB_EM16KB, /*!< WRAM_144KB EM_16KB */
    GLB_WRAM128KB_EM32KB, /*!< WRAM_128KB EM_32KB */
    GLB_WRAM112KB_EM48KB, /*!< WRAM_112KB EM_48KB */
    GLB_WRAM96KB_EM64KB,  /*!< WRAM_96KB EM_64KB */
} GLB_EM_Type;

/**
 *  @brief GLB ADC clock type definition
 */
typedef enum {
    GLB_ADC_CLK_AUPLL, /*!< use AUPLL as ADC clock */
    GLB_ADC_CLK_XCLK,  /*!< use XCLK as ADC clock */
} GLB_ADC_CLK_Type;

/**
 *  @brief GLB DAC clock type definition
 */
typedef enum {
    GLB_DAC_CLK_32M,  /*!< use 32M as DAC clock */
    GLB_DAC_CLK_XCLK, /*!< use XCLK as DAC clock */
} GLB_DAC_CLK_Type;

/**
 *  @brief GLB chip clock input output type definition
 */
/**
 *  @brief GLB chip clock out 0 type definition
 */
typedef enum {
    GLB_CHIP_CLK_OUT_0_CAM_REF_CLK = 0,   /*!< cam_ref_clk */
    GLB_CHIP_CLK_OUT_0_I2S_REF_CLK = 1,   /*!< i2s_ref_clk out */
    GLB_CHIP_CLK_OUT_0_CLK_AUDIO_ADC = 2, /*!< clk_adc */
    GLB_CHIP_CLK_OUT_0_CLK_AUDIO_DAC = 3, /*!< clk_dac */
} GLB_CHIP_CLK_OUT_0_Type;

/**
 *  @brief GLB chip clock out 1 type definition
 */
typedef enum {
    GLB_CHIP_CLK_OUT_1_CAM_REF_CLK = 0,   /*!< no chip clock out */
    GLB_CHIP_CLK_OUT_1_I2S_REF_CLK = 1,   /*!< i2s_ref_clk out */
    GLB_CHIP_CLK_OUT_1_CLK_AUDIO_ADC = 2, /*!< clk_adc_in_128fs */
    GLB_CHIP_CLK_OUT_1_CLK_AUDIO_DAC = 3, /*!< clk_dac_in_128fs */
} GLB_CHIP_CLK_OUT_1_Type;

/**
 *  @brief GLB chip clock out 2 type definition
 */
typedef enum {
    GLB_CHIP_CLK_OUT_2_CAM_REF_CLK = 0,  /*!< cam_ref_clk */
    GLB_CHIP_CLK_OUT_2_I2S_REF_CLK = 1,  /*!< i2s_ref_clk */
    GLB_CHIP_CLK_OUT_2_ANA_XTAL_CLK = 2, /*!< ana_xtal_clk */
    GLB_CHIP_CLK_OUT_2_PLL_32M_CLK = 3,  /*!< pll_32m_clk */
} GLB_CHIP_CLK_OUT_2_Type;

/**
 *  @brief GLB chip clock out 3 type definition
 */
typedef enum {
    GLB_CHIP_CLK_OUT_3_CAM_REF_CLK = 0, /*!< no chip clock out */
    GLB_CHIP_CLK_OUT_3_I2S_REF_CLK = 1, /*!< i2s_ref_clk out */
    GLB_CHIP_CLK_OUT_3_NONE = 2,        /*!< no clock out */
    GLB_CHIP_CLK_OUT_3_PLL_48M_CLK = 3, /*!< pll_48m_clk */
} GLB_CHIP_CLK_OUT_3_Type;

/**
 *  @brief GLB CSI DSI clock source select type definition
 */
typedef enum {
    GLB_CSI_DSI_CLK_SEL_XTAL_CLK,     /*!< xtal_clk */
    GLB_CSI_DSI_CLK_SEL_CPUPLL_DIV10, /*!< cpupll_div10 */
} GLB_CSI_DSI_CLK_SEL_Type;

/**
 *  @brief GLB DIG clock source select type definition
 */
typedef enum {
    GLB_DIG_CLK_WIFIPLL_32M, /*!< select WIFIPLL 32M as DIG clock source */
    GLB_DIG_CLK_XCLK,        /*!< select XCLK as DIG clock source */
    GLB_DIG_CLK_AUPLL,       /*!< select AUPLL as DIG clock source */
} GLB_DIG_CLK_Type;

/**
 *  @brief GLB 512K clock out select type definition
 */
typedef enum {
    GLB_512K_CLK_OUT_512K, /*!< select 512K clock out */
    GLB_512K_CLK_OUT_256K, /*!< select 256K clock out */
    GLB_512K_CLK_OUT_128K, /*!< select 128K clock out */
} GLB_512K_CLK_OUT_Type;

/**
 *  @brief GLB BT bandwidth type definition
 */
typedef enum {
    GLB_BT_BANDWIDTH_1M, /*!< BT bandwidth 1MHz */
    GLB_BT_BANDWIDTH_2M, /*!< BT bandwidth 2MHz */
} GLB_BT_BANDWIDTH_Type;

/**
 *  @brief GLB UART2 IO selection type definition
 */
typedef enum {
    GLB_UART2_IO_SEL_UART2,    /*!< Select UART2 function */
    GLB_UART2_IO_SEL_ISO11898, /*!< Select ISO11898 function */
} GLB_UART2_IO_SEL_Type;

/**
 *  @brief GLB UART signal type definition
 */
typedef enum {
    GLB_UART_SIG_0,  /*!< UART signal 0 */
    GLB_UART_SIG_1,  /*!< UART signal 1 */
    GLB_UART_SIG_2,  /*!< UART signal 2 */
    GLB_UART_SIG_3,  /*!< UART signal 3 */
    GLB_UART_SIG_4,  /*!< UART signal 4 */
    GLB_UART_SIG_5,  /*!< UART signal 5 */
    GLB_UART_SIG_6,  /*!< UART signal 6 */
    GLB_UART_SIG_7,  /*!< UART signal 7 */
    GLB_UART_SIG_8,  /*!< UART signal 8 */
    GLB_UART_SIG_9,  /*!< UART signal 9 */
    GLB_UART_SIG_10, /*!< UART signal 10 */
    GLB_UART_SIG_11, /*!< UART signal 11 */
} GLB_UART_SIG_Type;

/**
 *  @brief GLB UART signal  function type definition
 */
typedef enum {
    GLB_UART_SIG_FUN_UART0_RTS, /*!< UART funtion: UART 0 RTS */
    GLB_UART_SIG_FUN_UART0_CTS, /*!< UART funtion: UART 0 CTS */
    GLB_UART_SIG_FUN_UART0_TXD, /*!< UART funtion: UART 0 TXD */
    GLB_UART_SIG_FUN_UART0_RXD, /*!< UART funtion: UART 0 RXD */
    GLB_UART_SIG_FUN_UART1_RTS, /*!< UART funtion: UART 1 RTS */
    GLB_UART_SIG_FUN_UART1_CTS, /*!< UART funtion: UART 1 CTS */
    GLB_UART_SIG_FUN_UART1_TXD, /*!< UART funtion: UART 1 TXD */
    GLB_UART_SIG_FUN_UART1_RXD, /*!< UART funtion: UART 1 RXD */
    GLB_UART_SIG_FUN_UART2_RTS, /*!< UART funtion: UART 2 RTS */
    GLB_UART_SIG_FUN_UART2_CTS, /*!< UART funtion: UART 2 CTS */
    GLB_UART_SIG_FUN_UART2_TXD, /*!< UART funtion: UART 2 TXD */
    GLB_UART_SIG_FUN_UART2_RXD, /*!< UART funtion: UART 2 RXD */
} GLB_UART_SIG_FUN_Type;

/**
 *  @brief XTAL type definition
 */
typedef enum {
    GLB_XTAL_NONE,  /*!< XTAL is none */
    GLB_XTAL_24M,   /*!< XTAL is 24M */
    GLB_XTAL_32M,   /*!< XTAL is 32M */
    GLB_XTAL_38P4M, /*!< XTAL is 38.4M */
    GLB_XTAL_40M,   /*!< XTAL is 40M */
    GLB_XTAL_26M,   /*!< XTAL is 26M */
    GLB_XTAL_RC32M, /*!< XTAL is RC32M */
    GLB_XTAL_MAX,   /*!< type max num */
} GLB_XTAL_Type;

/**
 *  @brief PLL power on type definition
 */
typedef enum {
    GLB_PLL_NONE = 0,    /*!< power on xtal and pll */
    GLB_PLL_WIFIPLL = 1, /*!< power on WIFIPLL */
    GLB_PLL_AUPLL = 2,   /*!< power on AUPLL */
    GLB_PLL_CPUPLL = 4,  /*!< power on CPUPLL */
    GLB_PLL_MIPIPLL = 8, /*!< power on ETHPLL */
    GLB_PLL_UHSPLL = 16, /*!< power on ETHPLL */
} GLB_PLL_Type;

/**
 *  @brief WAC PLL XTAL type definition
 */
typedef enum {
    GLB_WAC_PLL_WIFIPLL, /*!< wifi pll */
    GLB_WAC_PLL_AUPLL,   /*!< audio pll */
    GLB_WAC_PLL_CPUPLL,  /*!< cpu pll */
} GLB_WAC_PLL_Type;

/**
 *  @brief MU PLL XTAL type definition
 */
typedef enum {
    GLB_MU_PLL_MIPIPLL, /*!< mipi pll */
    GLB_MU_PLL_UHSPLL,  /*!< uhs pll */
} GLB_MU_PLL_Type;

/**
 *  @brief DISP clock type definition
 */
typedef enum {
    GLB_DISP_CLK_MIPIPLL_1500M, /*!< mipi pll 1500M */
} GLB_DISP_CLK_Type;

/**
 *  @brief PLL XTAL type definition
 */
typedef enum {
    GLB_PSRAM_EMI_CPUPLL_400M,  /*!< emi_cpupll_400m_clk */
    GLB_PSRAM_EMI_WIFIPLL_320M, /*!< emi_wifipll_320m_clk */
    GLB_PSRAM_EMI_AUPLL_DIV1,   /*!< emi_aupll_div1_clk */
} GLB_PSRAM_PLL_Type;

/**
 *  @brief GLB DSP xclk clock type definition
 */
typedef enum {
    GLB_DSP_XCLK_RC32M, /*!< use RC32M as xclk clock */
    GLB_DSP_XCLK_XTAL,  /*!< use XTAL as xclk clock */
} GLB_DSP_XCLK_Type;

/**
 *  @brief GLB DSP root clock type definition
 */
typedef enum {
    GLB_DSP_ROOT_CLK_XCLK, /*!< use XCLK as root clock */
    GLB_DSP_ROOT_CLK_PLL,  /*!< use PLL as root clock */
} GLB_DSP_ROOT_CLK_Type;

/**
 *  @brief GLB DSP pbroot clock type definition
 */
typedef enum {
    GLB_DSP_PBROOT_CLK_MM_XCLK,        /*!< use mm_xclk as pbroot clock */
    GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M, /*!< use mm_muxpll_160m_clk as pbroot clock */
    GLB_DSP_PBROOT_CLK_MM_MUXPLL_240M, /*!< use mm_muxpll_240m_clk as pbroot clock */
} GLB_DSP_PBROOT_CLK_Type;

/**
 *  @brief GLB DSP PLL clock type definition
 */
typedef enum {
    GLB_DSP_PLL_CLK_MUXPLL_240M, /*!< select DSP PLL output muxpll 240m as cpu clock */
    GLB_DSP_PLL_CLK_MUXPLL_320M, /*!< select DSP PLL output muxpll 320m as cpu clock */
    GLB_DSP_PLL_CLK_CPUPLL_400M, /*!< select DSP PLL output cpupll 400m as cpu clock */
} GLB_DSP_PLL_CLK_Type;

/**
 *  @brief GLB DSP UART clock type definition
 */
typedef enum {
    GLB_DSP_UART_CLK_DSP_PBCLK,   /*!< Select dsp pbclk as UART clock */
    GLB_DSP_UART_CLK_MUXPLL_160M, /*!< Select muxpll 160m as UART clock */
    GLB_DSP_UART_CLK_DSP_XCLK,    /*!< Select xclk as UART clock */
} GLB_DSP_UART_CLK_Type;

/**
 *  @brief GLB UART clock type definition
 */
typedef enum {
    GLB_UART_CLK_BCLK,     /*!< Select bclk clock as UART clock */
    GLB_UART_CLK_PLL_160M, /*!< Select PLL 160M as UART clock */
} GLB_UART_CLK_Type;

/**
 *  @brief GLB DSP CNN clock type definition
 */
typedef enum {
    GLB_DSP_CNN_CLK_160M, /*!< Select 160M as CNN clock */
    GLB_DSP_CNN_CLK_240M, /*!< Select 240M as CNN clock */
    GLB_DSP_CNN_CLK_320M, /*!< Select 320M as CNN clock */
} GLB_DSP_CNN_CLK_Type;

/**
 *  @brief GLB DSP DP clock type definition
 */
typedef enum {
    GLB_DSP_DP_CLK_DISPLAY_PLL, /*!< Select display pll as DP clock */
    GLB_DSP_DP_CLK_DSP_XCLK,    /*!< Select mm xclk as DP clock */
} GLB_DSP_DP_CLK_Type;

/**
 *  @brief GLB DSP clock type definition
 */
typedef enum {
    GLB_DSP_CLK_MUXPLL_160M, /*!< Select muxpll 160M as DSP sub clock */
    GLB_DSP_CLK_MUXPLL_240M, /*!< Select muxpll 240M as DSP sub clock */
    GLB_DSP_CLK_CPUPLL_400M, /*!< Select cpupll 400M as DSP sub clock */
    GLB_DSP_CLK_DSP_XCLK,    /*!< Select dsp xclk as DSP sub clock */
} GLB_DSP_CLK_Type;

/**
 *  @brief GLB DSP H264 clock type definition
 */
typedef enum {
    GLB_DSP_H264_DSP_MUXPLL_160M, /*!< Select dsp muxpll 160M as SUB clock */
    GLB_DSP_H264_DSP_MUXPLL_240M, /*!< Select dsp muxpll 240M as SUB clock */
    GLB_DSP_H264_DSP_MUXPLL_320M, /*!< Select dsp muxpll 320M as SUB clock */
} GLB_DSP_H264_CLK_Type;

/**
 *  @brief GLB DSP SPI clock type definition
 */
typedef enum {
    GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, /*!< Select muxpll 160M as SPI clock */
    GLB_DSP_SPI_CLK_DSP_XCLK,        /*!< Select xclk as SPI clock */
} GLB_DSP_SPI_CLK_Type;

/**
 *  @brief GLB DSP I2C clock type definition
 */
typedef enum {
    GLB_DSP_I2C_CLK_DSP_PBCLK, /*!< Select dsp pbclk as I2C clock */
    GLB_DSP_I2C_CLK_XCLK,      /*!< Select xclk as I2C clock */
} GLB_DSP_I2C_CLK_Type;

/**
 *  @brief GLB I2S di ref clock type definition
 */
typedef enum {
    GLB_I2S_DI_SEL_I2S_DI_INPUT,   /*!< Select i2s_di input */
    GLB_I2S_DI_SEL_I2S_REF_OUTPUT, /*!< Select i2s_ref_clk output */
} GLB_I2S_DI_REF_CLK_Type;

/**
 *  @brief GLB I2S do ref clock type definition
 */
typedef enum {
    GLB_I2S_DO_SEL_I2S_DO_OUTPT,   /*!< Select i2s_do output */
    GLB_I2S_DO_SEL_I2S_REF_OUTPUT, /*!< Select i2s_ref_clk output */
} GLB_I2S_DO_REF_CLK_Type;

/**
 *  @brief GLB EMI clock type definition
 */
typedef enum {
    GLB_EMI_CLK_MCU_PBCLK,        /*!< mcu_pbclk */
    GLB_EMI_CLK_CPUPLL_200M_CLK,  /*!< cpupll_200m_clk */
    GLB_EMI_CLK_WIFIPLL_320M_CLK, /*!< wifipll_320m_clk */
    GLB_EMI_CLK_CPUPLL_400M_CLK,  /*!< cpupll_400m_clk */
} GLB_EMI_CLK_Type;

/**
 *  @brief GLB DSP sw system type definition
 */
typedef enum {
    GLB_DSP_SW_SYSTEM_CTRL_SYS = 0,    /*!< SW system reset(pulse trigger) */
    GLB_DSP_SW_SYSTEM_CTRL_PWRON = 2,  /*!< SW power-on reset (pulse trigger) */
    GLB_DSP_SW_SYSTEM_CTRL_DSP0 = 8,   /*!< MMCPU0 reset(pulse trigger) */
    GLB_DSP_SW_SYSTEM_CTRL_DSP1 = 9,   /*!< MMCPU1 reset(pulse trigger) */
    GLB_DSP_SW_SYSTEM_CTRL_WL2MM = 15, /*!< wl2mm */
} GLB_DSP_SW_SYSTEM_Type;

/**
 *  @brief GLB DSP peripheral type definition
 */
typedef enum {
    GLB_DSP_PERIPHERAL_MM_MISC = 0, /*!< mm_misc */
    GLB_DSP_PERIPHERAL_DMA = 1,     /*!< dma */
    GLB_DSP_PERIPHERAL_UART0 = 2,   /*!< uart0 */
    GLB_DSP_PERIPHERAL_I2C0 = 3,    /*!< i2c0 */
    GLB_DSP_PERIPHERAL_IPC = 5,     /*!< ipc */
    GLB_DSP_PERIPHERAL_SPI = 8,     /*!< spi */
    GLB_DSP_PERIPHERAL_TIMER = 9,   /*!< timer */
    GLB_DSP_PERIPHERAL_I2S0 = 10,   /*!< i2s0 */
} GLB_DSP_PERIPHERAL_Type;

/**
 *  @brief GLB DSP sub type definition
 */
typedef enum {
    GLB_DSP_SUB_MISC = 0,     /*!< sub_misc */
    GLB_DSP_SUB_DVP2BUSA = 1, /*!< dvp2busA */
    GLB_DSP_SUB_DVP2BUSB = 2, /*!< dvp2busB */
    GLB_DSP_SUB_DVP2BUSC = 3, /*!< dvp2busC */
    GLB_DSP_SUB_OSD_DRAW = 4, /*!< osd_draw */
    GLB_DSP_SUB_DP = 5,       /*!< display */
    GLB_DSP_SUB_IMG_PR = 16,  /*!< img_pr scaler/yuv2rgb */
    GLB_DSP_SUB_SCLRA = 17,   /*!< ScalerA */
    GLB_DSP_SUB_SCLRB = 18,   /*!< ScalerB */
} GLB_DSP_SUB_Type;

/**
 *  @brief GLB DSP codec sub type definition
 */
typedef enum {
    GLB_DSP_CODEC_SUB_MJPEG = 1, /*!< mjpeg */
    GLB_DSP_CODEC_SUB_CNN = 2,   /*!< BLAI */
    GLB_DSP_CODEC_SUB_VRAM = 16, /*!< vram control logic(SRAM content would not be reset) */
} GLB_DSP_CODEC_SUB_Type;

/**
 *  @brief GLB DSP image sensor type definition
 */
typedef enum {
    GLB_DSP_IMAGE_SENSOR_RG_IS = 1, /*!< Image sensor */
} GLB_DSP_IMAGE_SENSOR_Type;

/**
 *  @brief GLB LDO15CIS level type definition
 */
typedef enum {
    GLB_LDO15CIS_LEVEL_1P00V = 0,  /*!< GLB LDO15CIS voltage 1.00V */
    GLB_LDO15CIS_LEVEL_1P05V = 1,  /*!< GLB LDO15CIS voltage 1.05V */
    GLB_LDO15CIS_LEVEL_1P10V = 2,  /*!< GLB LDO15CIS voltage 1.10V */
    GLB_LDO15CIS_LEVEL_1P15V = 3,  /*!< GLB LDO15CIS voltage 1.15V */
    GLB_LDO15CIS_LEVEL_1P20V = 4,  /*!< GLB LDO15CIS voltage 1.20V */
    GLB_LDO15CIS_LEVEL_1P30V = 5,  /*!< GLB LDO15CIS voltage 1.30V */
    GLB_LDO15CIS_LEVEL_1P40V = 6,  /*!< GLB LDO15CIS voltage 1.40V */
    GLB_LDO15CIS_LEVEL_1P45V = 7,  /*!< GLB LDO15CIS voltage 1.45V */
    GLB_LDO15CIS_LEVEL_1P50V = 8,  /*!< GLB LDO15CIS voltage 1.50V */
    GLB_LDO15CIS_LEVEL_1P55V = 9,  /*!< GLB LDO15CIS voltage 1.55V */
    GLB_LDO15CIS_LEVEL_1P60V = 10, /*!< GLB LDO15CIS voltage 1.60V */
    GLB_LDO15CIS_LEVEL_1P65V = 11, /*!< GLB LDO15CIS voltage 1.65V */
    GLB_LDO15CIS_LEVEL_1P70V = 12, /*!< GLB LDO15CIS voltage 1.70V */
    GLB_LDO15CIS_LEVEL_1P75V = 13, /*!< GLB LDO15CIS voltage 1.75V */
    GLB_LDO15CIS_LEVEL_1P80V = 14, /*!< GLB LDO15CIS voltage 1.80V */
    GLB_LDO15CIS_LEVEL_1P85V = 15, /*!< GLB LDO15CIS voltage 1.85V */
} GLB_LDO15CIS_LEVEL_Type;

/*@} end of group GLB_Public_Types */

/** @defgroup  GLB_Public_Constants
 *  @{
 */

/** @defgroup  GLB_CORE_ID_TYPE
 *  @{
 */
#define IS_GLB_CORE_ID_TYPE(type) (((type) == GLB_CORE_ID_M0) ||  \
                                   ((type) == GLB_CORE_ID_D0) ||  \
                                   ((type) == GLB_CORE_ID_LP) ||  \
                                   ((type) == GLB_CORE_ID_MAX) || \
                                   ((type) == GLB_CORE_ID_INVALID))

/** @defgroup  CCI_ID_TYPE
 *  @{
 */
#define IS_CCI_ID_TYPE(type) (((type) == CCI0_ID) || \
                              ((type) == CCI_ID_MAX))

/** @defgroup  GLB_DSP_ALL_INT_TYPE
 *  @{
 */
#define IS_GLB_DSP_ALL_INT_TYPE(type) (((type) == GLB_DSP_ALL_INT_BUS_DEC_ERR_INT) ||     \
                                       ((type) == GLB_DSP_ALL_INT_RSV1_INT) ||        \
                                       ((type) == GLB_DSP_ALL_INT_IPC2_NP2AP_IRQ) ||      \
                                       ((type) == GLB_DSP_ALL_INT_RSV3) ||                \
                                       ((type) == GLB_DSP_ALL_INT_UART0_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_I2C0_INT) ||            \
                                       ((type) == GLB_DSP_ALL_INT_I2C1_INT) ||            \
                                       ((type) == GLB_DSP_ALL_INT_SPI_INT) ||             \
                                       ((type) == GLB_DSP_ALL_INT_RSV4_INT) ||          \
                                       ((type) == GLB_DSP_ALL_INT_RSV5_INT) ||         \
                                       ((type) == GLB_DSP_ALL_INT_SEOF1_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_SEOF2_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_SEOF3_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_INT_0) ||       \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_INT_1) ||       \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_INT_2) ||       \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_INT_3) ||       \
                                       ((type) == GLB_DSP_ALL_INT_H264_BS_IRQ) ||         \
                                       ((type) == GLB_DSP_ALL_INT_H264_FRAME_IRQ) ||      \
                                       ((type) == GLB_DSP_ALL_INT_H264_SEQ_DONE_INT) ||   \
                                       ((type) == GLB_DSP_ALL_INT_MJPEG_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_H264_S_BS_IRQ) ||       \
                                       ((type) == GLB_DSP_ALL_INT_H264_S_FRAME_IRQ) ||    \
                                       ((type) == GLB_DSP_ALL_INT_H264_S_SEQ_DONE_INT) || \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_0) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_1) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_2) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_3) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_4) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_5) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_6) ||          \
                                       ((type) == GLB_DSP_ALL_INT_DMA_INTR_7) ||          \
                                       ((type) == GLB_DSP_ALL_INT_RSV32) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV33) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV34) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV35) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV36) ||               \
                                       ((type) == GLB_DSP_ALL_INT_MIPI_CSI_INT) ||        \
                                       ((type) == GLB_DSP_ALL_INT_IPC2_AP2NP_IRQ) ||      \
                                       ((type) == GLB_DSP_ALL_INT_RSV39) ||               \
                                       ((type) == GLB_DSP_ALL_INT_MJDEC_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_IN_4) ||        \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_IN_5) ||        \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_IN_6) ||        \
                                       ((type) == GLB_DSP_ALL_INT_DVP2BUS_IN_7) ||        \
                                       ((type) == GLB_DSP_ALL_INT_DMA2D_INT_0) ||         \
                                       ((type) == GLB_DSP_ALL_INT_DMA2D_INT_1) ||         \
                                       ((type) == GLB_DSP_ALL_INT_DP_SOEF0_INT) ||        \
                                       ((type) == GLB_DSP_ALL_INT_RSV48) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV49) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV50) ||               \
                                       ((type) == GLB_DSP_ALL_INT_RSV51) ||               \
                                       ((type) == GLB_DSP_ALL_INT_OSDDP_INT) ||           \
                                       ((type) == GLB_DSP_ALL_INT_DBI_INT) ||             \
                                       ((type) == GLB_DSP_ALL_INT_RSV6_INT) ||         \
                                       ((type) == GLB_DSP_ALL_INT_OSDA_INT) ||            \
                                       ((type) == GLB_DSP_ALL_INT_OSDB_INT) ||            \
                                       ((type) == GLB_DSP_ALL_INT_OSD_PB_INT) ||          \
                                       ((type) == GLB_DSP_ALL_INT_RSV7_INT) ||        \
                                       ((type) == GLB_DSP_ALL_INT_MIPI_DSI_INT) ||        \
                                       ((type) == GLB_DSP_ALL_INT_RSV8_INT) ||     \
                                       ((type) == GLB_DSP_ALL_INT_MM_TIMER_IRQ2) ||       \
                                       ((type) == GLB_DSP_ALL_INT_MM_TIMER_IRQ3) ||       \
                                       ((type) == GLB_DSP_ALL_INT_MM_WDT_IRQ))

/** @defgroup  GLB_MCU_ALL_INT_TYPE
 *  @{
 */
#define IS_GLB_MCU_ALL_INT_TYPE(type) (((type) == GLB_MCU_ALL_INT_BMX_ERR_INT) ||                      \
                                       ((type) == GLB_MCU_ALL_INT_BMX_TIMEOUT_INT_MCU_TIMEOUT_INT) ||  \
                                       ((type) == GLB_MCU_ALL_INT_IPC0_NP2AP_IRQ) ||                   \
                                       ((type) == GLB_MCU_ALL_INT_IPC0_AP2NP_IRQ) ||                   \
                                       ((type) == GLB_MCU_ALL_INT_AUDIO_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_RF_TOP_INT_0) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_RF_TOP_INT_1) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_LZ4_INT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_RSV8) ||                             \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_GMAC_INT) ||             \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_CDET_INT) ||             \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_PKA_INT) ||              \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_TRNG_INT) ||             \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_AES_INT) ||              \
                                       ((type) == GLB_MCU_ALL_INT_SEC_ENG_ID0_SHA_INT) ||              \
                                       ((type) == GLB_MCU_ALL_INT_DMA_INTR_ALL) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_DMA2_INTR_ALL) ||                    \
                                       ((type) == GLB_MCU_ALL_INT_SDH_MMC1_INT_SDH2PMU_WAKEUP_INT1) || \
                                       ((type) == GLB_MCU_ALL_INT_MM_IRQ_ALL) ||                       \
                                       ((type) == GLB_MCU_ALL_INT_IRTX_INT) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_IRRX_INT) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_USB_INT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_AUPDM_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_SF_CTRL_ID0_INT) ||                  \
                                       ((type) == GLB_MCU_ALL_INT_EMAC_INT) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_GPADC_DMA_INT) ||                    \
                                       ((type) == GLB_MCU_ALL_INT_EFUSE_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_SPI_0_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_UART_IRQ) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_UART1_IRQ) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_UART2_IRQ) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_GPIO_DMA_INT) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_I2C_0_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_PWM_INT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_IPC1_NP2AP_IRQ) ||                   \
                                       ((type) == GLB_MCU_ALL_INT_IPC1_AP2NP_IRQ) ||                   \
                                       ((type) == GLB_MCU_ALL_INT_TIMER0_2_IRQ) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_TIMER0_3_IRQ) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_WDT0_IRQ) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_I2C_1_INT) ||                        \
                                       ((type) == GLB_MCU_ALL_INT_I2S0_INT) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_RSV41) ||                            \
                                       ((type) == GLB_MCU_ALL_INT_RSV42) ||                            \
                                       ((type) == GLB_MCU_ALL_INT_ANA_OCP_OUT_TO_CPU_IRQ) ||           \
                                       ((type) == GLB_MCU_ALL_INT_GPIO_IRQ) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_DM_IRQ) ||                           \
                                       ((type) == GLB_MCU_ALL_INT_BT_IRQ) ||                           \
                                       ((type) == GLB_MCU_ALL_INT_M154_REQ_ENH_ACK_INT) ||             \
                                       ((type) == GLB_MCU_ALL_INT_M154_INT) ||                         \
                                       ((type) == GLB_MCU_ALL_INT_M154_AES_INT) ||                     \
                                       ((type) == GLB_MCU_ALL_INT_PDS_INT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_HBN_IRQ_OUT_0) ||                    \
                                       ((type) == GLB_MCU_ALL_INT_HBN_IRQ_OUT_1) ||                    \
                                       ((type) == GLB_MCU_ALL_INT_BOR_OUT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_WIFI_TO_CPU_IRQ_N) ||                \
                                       ((type) == GLB_MCU_ALL_INT_BZ_PHY_INT) ||                       \
                                       ((type) == GLB_MCU_ALL_INT_BLE_INT) ||                          \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_TX_RX_TIMER) ||              \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_TX_RX_MISC) ||               \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_RX_TRIGGER) ||               \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_TX_TRIGGER) ||               \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_GEN) ||                      \
                                       ((type) == GLB_MCU_ALL_INT_MAC_INT_PROT_TRIGGER) ||             \
                                       ((type) == GLB_MCU_ALL_INT_WIFI_IPC))

/** @defgroup  GLB_LP_ALL_INT_TYPE
 *  @{
 */
#define IS_GLB_LP_ALL_INT_TYPE(type) (((type) == GLB_LP_ALL_INT_BMX_ERR_INT) ||                      \
                                      ((type) == GLB_LP_ALL_INT_BMX_TIMEOUT_INT_MCU_TIMEOUT_INT) ||  \
                                      ((type) == GLB_LP_ALL_INT_IPC0_NP2AP_IRQ) ||                   \
                                      ((type) == GLB_LP_ALL_INT_IPC0_AP2NP_IRQ) ||                   \
                                      ((type) == GLB_LP_ALL_INT_AUDIO_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_RF_TOP_INT_0) ||                     \
                                      ((type) == GLB_LP_ALL_INT_RF_TOP_INT_1) ||                     \
                                      ((type) == GLB_LP_ALL_INT_LZ4_INT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_RSV8) ||                             \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_GMAC_INT) ||             \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_CDET_INT) ||             \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_PKA_INT) ||              \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_TRNG_INT) ||             \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_AES_INT) ||              \
                                      ((type) == GLB_LP_ALL_INT_SEC_ENG_ID0_SHA_INT) ||              \
                                      ((type) == GLB_LP_ALL_INT_DMA_INTR_ALL) ||                     \
                                      ((type) == GLB_LP_ALL_INT_DMA2_INTR_ALL) ||                    \
                                      ((type) == GLB_LP_ALL_INT_SDH_MMC1_INT_SDH2PMU_WAKEUP_INT1) || \
                                      ((type) == GLB_LP_ALL_INT_MM_IRQ_ALL) ||                       \
                                      ((type) == GLB_LP_ALL_INT_IRTX_INT) ||                         \
                                      ((type) == GLB_LP_ALL_INT_IRRX_INT) ||                         \
                                      ((type) == GLB_LP_ALL_INT_USB_INT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_AUPDM_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_SF_CTRL_ID0_INT) ||                  \
                                      ((type) == GLB_LP_ALL_INT_EMAC_INT) ||                         \
                                      ((type) == GLB_LP_ALL_INT_GPADC_DMA_INT) ||                    \
                                      ((type) == GLB_LP_ALL_INT_EFUSE_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_SPI_0_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_UART_IRQ) ||                         \
                                      ((type) == GLB_LP_ALL_INT_UART1_IRQ) ||                        \
                                      ((type) == GLB_LP_ALL_INT_UART2_IRQ) ||                        \
                                      ((type) == GLB_LP_ALL_INT_GPIO_DMA_INT) ||                     \
                                      ((type) == GLB_LP_ALL_INT_I2C_0_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_PWM_INT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_IPC1_NP2AP_IRQ) ||                   \
                                      ((type) == GLB_LP_ALL_INT_IPC1_AP2NP_IRQ) ||                   \
                                      ((type) == GLB_LP_ALL_INT_TIMER0_2_IRQ) ||                     \
                                      ((type) == GLB_LP_ALL_INT_TIMER0_3_IRQ) ||                     \
                                      ((type) == GLB_LP_ALL_INT_WDT0_IRQ) ||                         \
                                      ((type) == GLB_LP_ALL_INT_I2C_1_INT) ||                        \
                                      ((type) == GLB_LP_ALL_INT_I2S0_INT) ||                         \
                                      ((type) == GLB_LP_ALL_INT_RSV41) ||                            \
                                      ((type) == GLB_LP_ALL_INT_RSV42) ||                            \
                                      ((type) == GLB_LP_ALL_INT_ANA_OCP_OUT_TO_CPU_IRQ) ||           \
                                      ((type) == GLB_LP_ALL_INT_GPIO_IRQ) ||                         \
                                      ((type) == GLB_LP_ALL_INT_DM_IRQ) ||                           \
                                      ((type) == GLB_LP_ALL_INT_BT_IRQ) ||                           \
                                      ((type) == GLB_LP_ALL_INT_M154_REQ_ENH_ACK_INT) ||             \
                                      ((type) == GLB_LP_ALL_INT_M154_INT) ||                         \
                                      ((type) == GLB_LP_ALL_INT_M154_AES_INT) ||                     \
                                      ((type) == GLB_LP_ALL_INT_PDS_INT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_HBN_IRQ_OUT_0) ||                    \
                                      ((type) == GLB_LP_ALL_INT_HBN_IRQ_OUT_1) ||                    \
                                      ((type) == GLB_LP_ALL_INT_BOR_OUT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_WIFI_TO_CPU_IRQ_N) ||                \
                                      ((type) == GLB_LP_ALL_INT_BZ_PHY_INT) ||                       \
                                      ((type) == GLB_LP_ALL_INT_BLE_INT) ||                          \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_TX_RX_TIMER) ||              \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_TX_RX_MISC) ||               \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_RX_TRIGGER) ||               \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_TX_TRIGGER) ||               \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_GEN) ||                      \
                                      ((type) == GLB_LP_ALL_INT_MAC_INT_PROT_TRIGGER) ||             \
                                      ((type) == GLB_LP_ALL_INT_WIFI_IPC))

/** @defgroup  GLB_DSP_MUXPLL_320M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_DSP_MUXPLL_320M_CLK_SEL_TYPE(type) (((type) == GLB_DSP_MUXPLL_SEL_WIFIPLL_320M) || \
                                                   ((type) == GLB_DSP_MUXPLL_SEL_AUPLL_DIV1))

/** @defgroup  GLB_DSP_MUXPLL_240M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_DSP_MUXPLL_240M_CLK_SEL_TYPE(type) (((type) == GLB_DSP_MUXPLL_SEL_WIFIPLL_240M) || \
                                                   ((type) == GLB_DSP_MUXPLL_SEL_AUPLL_DIV2))

/** @defgroup  GLB_DSP_MUXPLL_160M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_DSP_MUXPLL_160M_CLK_SEL_TYPE(type) (((type) == GLB_DSP_MUXPLL_SEL_WIFIPLL_160M) || \
                                                   ((type) == GLB_DSP_MUXPLL_SEL_CPUPLL_160M))

/** @defgroup  GLB_MCU_MUXPLL_160M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_MCU_MUXPLL_160M_CLK_SEL_TYPE(type) (((type) == GLB_MCU_MUXPLL_SEL_WIFIPLL_160M) ||    \
                                                   ((type) == GLB_MCU_MUXPLL_SEL_TOP_CPUPLL_160M) || \
                                                   ((type) == GLB_MCU_MUXPLL_SEL_TOP_AUPLL_DIV2) ||  \
                                                   ((type) == GLB_MCU_MUXPLL_SEL_AUPLL_DIV2P5))

/** @defgroup  GLB_MCU_MUXPLL_80M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_MCU_MUXPLL_80M_CLK_SEL_TYPE(type) (((type) == GLB_MCU_MUXPLL_SEL_WIFIPLL_80M) ||    \
                                                  ((type) == GLB_MCU_MUXPLL_SEL_TOP_CPUPLL_80M) || \
                                                  ((type) == GLB_MCU_MUXPLL_SEL_AUPLL_DIV5) ||     \
                                                  ((type) == GLB_MCU_MUXPLL_SEL_AUPLL_DIV6))

/** @defgroup  GLB_PLL_CGEN_TYPE
 *  @{
 */
#define IS_GLB_PLL_CGEN_TYPE(type) (((type) == GLB_PLL_CGEN_MM_WIFIPLL_160M) ||  \
                                    ((type) == GLB_PLL_CGEN_MM_WIFIPLL_240M) ||  \
                                    ((type) == GLB_PLL_CGEN_MM_WIFIPLL_320M) ||  \
                                    ((type) == GLB_PLL_CGEN_MM_AUPLL_DIV1) ||    \
                                    ((type) == GLB_PLL_CGEN_MM_AUPLL_DIV2) ||    \
                                    ((type) == GLB_PLL_CGEN_EMI_CPUPLL_400M) ||  \
                                    ((type) == GLB_PLL_CGEN_EMI_CPUPLL_200M) ||  \
                                    ((type) == GLB_PLL_CGEN_EMI_WIFIPLL_320M) || \
                                    ((type) == GLB_PLL_CGEN_EMI_AUPLL_DIV1) ||   \
                                    ((type) == GLB_PLL_CGEN_TOP_CPUPLL_80M) ||   \
                                    ((type) == GLB_PLL_CGEN_TOP_CPUPLL_100M) ||  \
                                    ((type) == GLB_PLL_CGEN_TOP_CPUPLL_160M) ||  \
                                    ((type) == GLB_PLL_CGEN_TOP_CPUPLL_400M) ||  \
                                    ((type) == GLB_PLL_CGEN_TOP_WIFIPLL_240M) || \
                                    ((type) == GLB_PLL_CGEN_TOP_WIFIPLL_320M) || \
                                    ((type) == GLB_PLL_CGEN_TOP_AUPLL_DIV2) ||   \
                                    ((type) == GLB_PLL_CGEN_TOP_AUPLL_DIV1))

/** @defgroup  GLB_MCU_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_MCU_SYS_CLK_TYPE(type) (((type) == GLB_MCU_SYS_CLK_RC32M) ||        \
                                       ((type) == GLB_MCU_SYS_CLK_XTAL) ||         \
                                       ((type) == GLB_MCU_SYS_CLK_CPUPLL_400M) ||  \
                                       ((type) == GLB_MCU_SYS_CLK_WIFIPLL_240M) || \
                                       ((type) == GLB_MCU_SYS_CLK_WIFIPLL_320M))

/** @defgroup  GLB_DSP_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_SYS_CLK_TYPE(type) (((type) == GLB_DSP_SYS_CLK_RC32M) ||           \
                                       ((type) == GLB_DSP_SYS_CLK_XTAL) ||            \
                                       ((type) == GLB_DSP_SYS_CLK_MM_WIFIPLL_240M) || \
                                       ((type) == GLB_DSP_SYS_CLK_MM_WIFIPLL_320M) || \
                                       ((type) == GLB_DSP_SYS_CLK_CPUPLL_400M))

/** @defgroup  GLB_DSP_SYS_PBCLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_SYS_PBCLK_TYPE(type) (((type) == GLB_DSP_SYS_PBCLK_RC32M) ||           \
                                         ((type) == GLB_DSP_SYS_PBCLK_XTAL) ||            \
                                         ((type) == GLB_DSP_SYS_PBCLK_MM_WIFIPLL_160M) || \
                                         ((type) == GLB_DSP_SYS_PBCLK_CPUPLL_160M) ||     \
                                         ((type) == GLB_DSP_SYS_PBCLK_MM_WIFIPLL_240M))

/** @defgroup  GLB_PLL_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_PLL_REF_CLK_TYPE(type) (((type) == GLB_PLL_REFCLK_XTAL) || \
                                       ((type) == GLB_PLL_REFCLK_RC32M))

/** @defgroup  GLB_WIFIPLL_REF_CLK_Type
 *  @{
 */
#define IS_GLB_WIFIPLL_REF_CLK_TYPE(type) (((type) == GLB_WIFIPLL_REF_XTAL_SOC_CLK) || \
                                           ((type) == GLB_WIFIPLL_REF_XTAL_CLK) ||     \
                                           ((type) == GLB_WIFIPLL_REF_XTAL_LO_CLK) ||  \
                                           ((type) == GLB_WIFIPLL_REF_RC32M_CLK))

/** @defgroup  GLB_AUPLL_REF_CLK_Type
 *  @{
 */
#define IS_GLB_AUPLL_REF_CLK_TYPE(type) (((type) == GLB_AUPLL_REF_XTAL_SOC_CLK) || \
                                         ((type) == GLB_AUPLL_REF_RC32M_CLK))

/** @defgroup  GLB_CPUPLL_REF_CLK_Type
 *  @{
 */
#define IS_GLB_CPUPLL_REF_CLK_TYPE(type) (((type) == GLB_CPUPLL_REF_XTAL_SOC_CLK) || \
                                          ((type) == GLB_CPUPLL_REF_RC32M_CLK))

/** @defgroup  GLB_MIPIPLL_REF_CLK_Type
 *  @{
 */
#define IS_GLB_MIPIPLL_REF_CLK_TYPE(type) (((type) == GLB_MIPIPLL_REF_XTAL_SOC_CLK) || \
                                           ((type) == GLB_MIPIPLL_REF_RC32M_CLK))

/** @defgroup  GLB_UHSPLL_REF_CLK_Type
 *  @{
 */
#define IS_GLB_UHSPLL_REF_CLK_TYPE(type) (((type) == GLB_UHSPLL_REF_XTAL_SOC_CLK) || \
                                          ((type) == GLB_UHSPLL_REF_RC32M_CLK))

/** @defgroup  GLB_CAM_CLK_TYPE
 *  @{
 */
#define IS_GLB_CAM_CLK_TYPE(type) (((type) == GLB_CAM_CLK_XCLK) ||        \
                                   ((type) == GLB_CAM_CLK_WIFIPLL_96M) || \
                                   ((type) == GLB_CAM_CLK_CPUPLL_100M))

/** @defgroup  GLB_SDH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SDH_CLK_TYPE(type) (((type) == GLB_SDH_CLK_WIFIPLL_96M) || \
                                   ((type) == GLB_SDH_CLK_CPUPLL_100M))

/** @defgroup  GLB_GLB_UART_SIG_SWAP_SET_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_SWAP_GRP_TYPE(type) (((type) == GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11) ||  \
                                             ((type) == GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23) || \
                                             ((type) == GLB_UART_SIG_SWAP_GRP_GPIO24_GPIO35) || \
                                             ((type) == GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45))

/** @defgroup  GLB_I2S_OUT_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_I2S_OUT_REF_CLK_TYPE(type) (((type) == GLB_I2S_OUT_REF_CLK_NONE) || \
                                           ((type) == GLB_I2S_OUT_REF_CLK_SRC))

/** @defgroup  GLB_DMA_CLK_ID_TYPE
 *  @{
 */
#define IS_GLB_DMA_CLK_ID_TYPE(type) (((type) == GLB_DMA0_CLK_CH0) || \
                                      ((type) == GLB_DMA0_CLK_CH1) || \
                                      ((type) == GLB_DMA0_CLK_CH2) || \
                                      ((type) == GLB_DMA0_CLK_CH3) || \
                                      ((type) == GLB_DMA0_CLK_CH4) || \
                                      ((type) == GLB_DMA0_CLK_CH5) || \
                                      ((type) == GLB_DMA0_CLK_CH6) || \
                                      ((type) == GLB_DMA0_CLK_CH7) || \
                                      ((type) == GLB_DMA1_CLK_CH0) || \
                                      ((type) == GLB_DMA1_CLK_CH1) || \
                                      ((type) == GLB_DMA1_CLK_CH2) || \
                                      ((type) == GLB_DMA1_CLK_CH3))

/** @defgroup  GLB_PERI_DMA_TYPE
 *  @{
 */
#define IS_GLB_PERI_DMA_TYPE(type) (((type) == GLB_PERI_DMA_UART0_RX) || \
                                    ((type) == GLB_PERI_DMA_UART0_TX) || \
                                    ((type) == GLB_PERI_DMA_UART1_RX) || \
                                    ((type) == GLB_PERI_DMA_UART1_TX) || \
                                    ((type) == GLB_PERI_DMA_UART2_RX) || \
                                    ((type) == GLB_PERI_DMA_UART2_TX) || \
                                    ((type) == GLB_PERI_DMA_I2C_0_RX) || \
                                    ((type) == GLB_PERI_DMA_I2C_0_TX) || \
                                    ((type) == GLB_PERI_DMA_IRTX_TX) ||  \
                                    ((type) == GLB_PERI_DMA_GPIO_TX) ||  \
                                    ((type) == GLB_PERI_DMA_SPI_RX) ||   \
                                    ((type) == GLB_PERI_DMA_SPI_TX) ||   \
                                    ((type) == GLB_PERI_DMA_AUDIO_RX) || \
                                    ((type) == GLB_PERI_DMA_AUDIO_TX) || \
                                    ((type) == GLB_PERI_DMA_I2C_1_RX) || \
                                    ((type) == GLB_PERI_DMA_I2C_1_TX) || \
                                    ((type) == GLB_PERI_DMA_I2S_0_RX) || \
                                    ((type) == GLB_PERI_DMA_I2S_0_TX) || \
                                    ((type) == GLB_PERI_DMA_PDM_RX) ||   \
                                    ((type) == GLB_PERI_DMA_PADC) ||     \
                                    ((type) == GLB_PERI_DMA_GAUGE) ||    \
                                    ((type) == GLB_PERI_DMA_GPADC) ||    \
                                    ((type) == GLB_PERI_DMA_GPDAC_TX))

/** @defgroup  GLB_PERI_DMA_CN_SEL_TYPE
 *  @{
 */
#define IS_GLB_PERI_DMA_CN_SEL_TYPE(type) (((type) == GLB_PERI_DMA_CN_SEL_DMA0) || \
                                           ((type) == GLB_PERI_DMA_CN_SEL_DMA1))

/** @defgroup  GLB_IR_CLK_SRC_TYPE
 *  @{
 */
#define IS_GLB_IR_CLK_SRC_TYPE(type) (((type) == GLB_IR_CLK_SRC_XCLK))

/** @defgroup  GLB_SFLASH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SFLASH_CLK_TYPE(type) (((type) == GLB_SFLASH_CLK_120M_WIFIPLL) || \
                                      ((type) == GLB_SFLASH_CLK_XTAL) ||         \
                                      ((type) == GLB_SFLASH_CLK_100M_CPUPLL) ||  \
                                      ((type) == GLB_SFLASH_CLK_80M_MUXPLL) ||   \
                                      ((type) == GLB_SFLASH_CLK_BCLK) ||         \
                                      ((type) == GLB_SFLASH_CLK_96M_WIFIPLL))

/** @defgroup  GLB_I2C_CLK_TYPE
 *  @{
 */
#define IS_GLB_I2C_CLK_TYPE(type) (((type) == GLB_I2C_CLK_BCLK) || \
                                   ((type) == GLB_I2C_CLK_XCLK))

/** @defgroup  GLB_SPI_CLK_TYPE
 *  @{
 */
#define IS_GLB_SPI_CLK_TYPE(type) (((type) == GLB_SPI_CLK_PLL160M) || \
                                   ((type) == GLB_SPI_CLK_XCLK))

/** @defgroup  GLB_PWM1_IO_SEL_TYPE
 *  @{
 */
#define IS_GLB_PWM1_IO_SEL_TYPE(type) (((type) == GLB_PWM1_IO_SINGLE_END) || \
                                       ((type) == GLB_PWM1_IO_DIFF_END))

/** @defgroup  GLB_PWM2_IO_SEL_TYPE
 *  @{
 */
#define IS_GLB_PWM2_IO_SEL_TYPE(type) (((type) == GLB_PWM2_IO_SINGLE_END) || \
                                       ((type) == GLB_PWM2_IO_SINGLE_END_BLDC))

/** @defgroup  GLB_PDM_IO_SEL_TYPE
 *  @{
 */
#define IS_GLB_PDM_IO_SEL_TYPE(type) (((type) == GLB_PDM_IO_SEL_AUDIO_TOP) || \
                                      ((type) == GLB_PDM_IO_SEL_AUPDM_TOP))

/** @defgroup  GLB_SPI_PAD_ACT_AS_TYPE
 *  @{
 */
#define IS_GLB_SPI_PAD_ACT_AS_TYPE(type) (((type) == GLB_SPI_PAD_ACT_AS_SLAVE) || \
                                          ((type) == GLB_SPI_PAD_ACT_AS_MASTER))

/** @defgroup  GLB_AHB_SW_TYPE
 *  @{
 */
#define IS_GLB_AHB_MCU_SW_TYPE(type) (((type) == GLB_AHB_MCU_SW_RSV0) ||               \
                                      ((type) == GLB_AHB_MCU_SW_RSV1) ||               \
                                      ((type) == GLB_AHB_MCU_SW_WIFI) ||               \
                                      ((type) == GLB_AHB_MCU_SW_BTDM) ||               \
                                      ((type) == GLB_AHB_MCU_SW_ZIGBEE) ||             \
                                      ((type) == GLB_AHB_MCU_SW_BLE2) ||               \
                                      ((type) == GLB_AHB_MCU_SW_ZIGBEE2) ||            \
                                      ((type) == GLB_AHB_MCU_SW_EMI_MISC) ||           \
                                      ((type) == GLB_AHB_MCU_SW_PSRAM0_CTRL) ||        \
                                      ((type) == GLB_AHB_MCU_SW_PSRAM1_CTRL) ||        \
                                      ((type) == GLB_AHB_MCU_SW_USB) ||                \
                                      ((type) == GLB_AHB_MCU_SW_MIX2) ||               \
                                      ((type) == GLB_AHB_MCU_SW_AUDIO) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SDH) ||                \
                                      ((type) == GLB_AHB_MCU_SW_EMAC) ||               \
                                      ((type) == GLB_AHB_MCU_SW_DMA2) ||               \
                                      ((type) == GLB_AHB_MCU_SW_GLB) ||                \
                                      ((type) == GLB_AHB_MCU_SW_MIX) ||                \
                                      ((type) == GLB_AHB_MCU_SW_GPIP) ||               \
                                      ((type) == GLB_AHB_MCU_SW_SEC_DBG) ||            \
                                      ((type) == GLB_AHB_MCU_SW_SEC_ENG) ||            \
                                      ((type) == GLB_AHB_MCU_SW_TZ1) ||                \
                                      ((type) == GLB_AHB_MCU_SW_TZ2) ||                \
                                      ((type) == GLB_AHB_MCU_SW_EFUSE) ||              \
                                      ((type) == GLB_AHB_MCU_SW_CCI) ||                \
                                      ((type) == GLB_AHB_MCU_SW_L1C) ||                \
                                      ((type) == GLB_AHB_MCU_SW_RSV42) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SF) ||                 \
                                      ((type) == GLB_AHB_MCU_SW_DMA) ||                \
                                      ((type) == GLB_AHB_MCU_SW_SDU) ||                \
                                      ((type) == GLB_AHB_MCU_SW_PDS) ||                \
                                      ((type) == GLB_AHB_MCU_SW_RSV47) ||              \
                                      ((type) == GLB_AHB_MCU_SW_UART0) ||              \
                                      ((type) == GLB_AHB_MCU_SW_UART1) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SPI) ||                \
                                      ((type) == GLB_AHB_MCU_SW_I2C) ||                \
                                      ((type) == GLB_AHB_MCU_SW_PWM) ||                \
                                      ((type) == GLB_AHB_MCU_SW_TIMER) ||              \
                                      ((type) == GLB_AHB_MCU_SW_IR_REMOTE) ||          \
                                      ((type) == GLB_AHB_MCU_SW_CHECKSUM) ||           \
                                      ((type) == GLB_AHB_MCU_SW_QDEC) ||               \
                                      ((type) == GLB_AHB_MCU_SW_KYS) ||                \
                                      ((type) == GLB_AHB_MCU_SW_UART2) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV59) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV60) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV61) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV62) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV63) ||              \
                                      ((type) == GLB_AHB_MCU_SW_PWRON_RST) ||          \
                                      ((type) == GLB_AHB_MCU_SW_CPU_RESET) ||          \
                                      ((type) == GLB_AHB_MCU_SW_SYS_RESET) ||          \
                                      ((type) == GLB_AHB_MCU_SW_PICO_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_CPU2_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_CHIP_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_WL_WDT_RESET_MM_EN) || \
                                      ((type) == GLB_AHB_MCU_SW_MMWDT2WL_RST_MSK))

/** @defgroup  GLB_AHB_DSP_SW_TYPE
 *  @{
 */
#define IS_GLB_AHB_DSP_SW_TYPE(type) (((type) == GLB_AHB_DSP_SW_REG_CTRL_SYS_RESET) ||    \
                                      ((type) == GLB_AHB_DSP_SW_REG_CTRL_PWRON_RST) ||    \
                                      ((type) == GLB_AHB_DSP_SW_REG_CTRL_MMCPU0_RESET) || \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MM_MISC) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DMA) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_UART0) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2C0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2C1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_IPC) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DMA2D) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SPI) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_TIMER) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2S0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2S1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PDM0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PDM1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PUHS) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SUB_MISC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SUB_MAIN) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SUB_TSRC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DP_TSRC) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_NR3D_CTRL) ||       \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSA) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSB) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSD) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MIPI) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SUB_REG) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSE) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSF) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSG) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSH) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_CODEC_MISC) ||      \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MJPEG) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_H264) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MJPEG_DEC) ||       \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_CNN) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_VRAM) ||            \
                                      ((type) == GLB_AHB_DSP_SW_RG_IS_RST_N))

/** @defgroup  GLB DISRST_TYPE
 *  @{
 */
#define IS_GLB_DISRST_TYPE(type) (((type) == GLB_DISRST_GPIP) ||      \
                                  ((type) == GLB_DISRST_SEC_ENG) ||   \
                                  ((type) == GLB_DISRST_CCI) ||       \
                                  ((type) == GLB_DISRST_SF) ||        \
                                  ((type) == GLB_DISRST_UART0) ||     \
                                  ((type) == GLB_DISRST_UART1) ||     \
                                  ((type) == GLB_DISRST_SPI) ||       \
                                  ((type) == GLB_DISRST_I2C0) ||      \
                                  ((type) == GLB_DISRST_PWM) ||       \
                                  ((type) == GLB_DISRST_TIMER) ||     \
                                  ((type) == GLB_DISRST_IR_REMOTE) || \
                                  ((type) == GLB_DISRST_CHECKSUM) ||  \
                                  ((type) == GLB_DISRST_IPC) ||       \
                                  ((type) == GLB_DISRST_I2C1) ||      \
                                  ((type) == GLB_DISRST_UART2))

/** @defgroup  GLB_PKA_CLK_TYPE
 *  @{
 */
#define IS_GLB_PKA_CLK_TYPE(type) (((type) == GLB_PKA_CLK_MCU_BCLK) || \
                                   ((type) == GLB_PKA_CLK_MCU_MUXPLL_160M))

/** @defgroup  GLB_MCU_SW_SYSTEM_TYPE
 *  @{
 */
#define IS_GLB_MCU_SW_SYSTEM_TYPE(type) (((type) == GLB_MCU_SW_SYSTEM_CTRL_MCU) || \
                                         ((type) == GLB_MCU_SW_SYSTEM_CTRL_LP))

/** @defgroup  BMX_ARB_TYPE
 *  @{
 */
#define IS_BMX_ARB_TYPE(type) (((type) == BMX_ARB_ROUND_ROBIN) || \
                               ((type) == BMX_ARB_FIX))

/** @defgroup  BMX_LATCH_TYPE
 *  @{
 */
#define IS_BMX_LATCH_TYPE(type) (((type) == BMX_LATCH_FIRST_ERROR) || \
                                 ((type) == BMX_LATCH_LAST_ERROR))

/** @defgroup  BMX_BUS_ERR_TYPE
 *  @{
 */
#define IS_BMX_BUS_ERR_TYPE(type) (((type) == BMX_BUS_ERR_TRUSTZONE_DECODE) || \
                                   ((type) == BMX_BUS_ERR_ADDR_DECODE))

/** @defgroup  BMX_ERR_INT_TYPE
 *  @{
 */
#define IS_BMX_ERR_INT_TYPE(type) (((type) == BMX_ERR_INT_ERR) || \
                                   ((type) == BMX_ERR_INT_ALL))

/** @defgroup  BMX_TO_INT_TYPE
 *  @{
 */
#define IS_BMX_TO_INT_TYPE(type) (((type) == BMX_TO_INT_TIMEOUT) || \
                                  ((type) == BMX_TO_INT_ALL))

/** @defgroup  GLB_ETH_REF_CLK_OUT_TYPE
 *  @{
 */
#define IS_GLB_ETH_REF_CLK_OUT_TYPE(type) (((type) == GLB_ETH_REF_CLK_OUT_OUTSIDE_50M) || \
                                           ((type) == GLB_ETH_REF_CLK_OUT_INSIDE_50M))

/** @defgroup  GLB_EM_TYPE
 *  @{
 */
#define IS_GLB_EM_TYPE(type) (((type) == GLB_WRAM160KB_EM0KB) ||  \
                              ((type) == GLB_WRAM144KB_EM16KB) || \
                              ((type) == GLB_WRAM128KB_EM32KB) || \
                              ((type) == GLB_WRAM112KB_EM48KB) || \
                              ((type) == GLB_WRAM96KB_EM64KB))

/** @defgroup  GLB_ADC_CLK_TYPE
 *  @{
 */
#define IS_GLB_ADC_CLK_TYPE(type) (((type) == GLB_ADC_CLK_AUPLL) || \
                                   ((type) == GLB_ADC_CLK_XCLK))

/** @defgroup  GLB_DAC_CLK_TYPE
 *  @{
 */
#define IS_GLB_DAC_CLK_TYPE(type) (((type) == GLB_DAC_CLK_32M) || \
                                   ((type) == GLB_DAC_CLK_XCLK))

/** @defgroup  GLB_CHIP_CLK_INOUT_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_INOUT_TYPE(type) (((type) == GLB_CHIP_CLK_INOUT_INPUT) || \
                                          ((type) == GLB_CHIP_CLK_INOUT_OUTPUT))

/** @defgroup  GLB_CHIP_CLK_OUT_0_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_OUT_0_TYPE(type) (((type) == GLB_CHIP_CLK_OUT_0_CAM_REF_CLK) ||   \
                                          ((type) == GLB_CHIP_CLK_OUT_0_I2S_REF_CLK) ||   \
                                          ((type) == GLB_CHIP_CLK_OUT_0_CLK_AUDIO_ADC) || \
                                          ((type) == GLB_CHIP_CLK_OUT_0_CLK_AUDIO_DAC))

/** @defgroup  GLB_CHIP_CLK_OUT_1_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_OUT_1_TYPE(type) (((type) == GLB_CHIP_CLK_OUT_1_CAM_REF_CLK) ||   \
                                          ((type) == GLB_CHIP_CLK_OUT_1_I2S_REF_CLK) ||   \
                                          ((type) == GLB_CHIP_CLK_OUT_1_CLK_AUDIO_ADC) || \
                                          ((type) == GLB_CHIP_CLK_OUT_1_CLK_AUDIO_DAC))

/** @defgroup  GLB_CHIP_CLK_OUT_2_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_OUT_2_TYPE(type) (((type) == GLB_CHIP_CLK_OUT_2_CAM_REF_CLK) ||  \
                                          ((type) == GLB_CHIP_CLK_OUT_2_I2S_REF_CLK) ||  \
                                          ((type) == GLB_CHIP_CLK_OUT_2_ANA_XTAL_CLK) || \
                                          ((type) == GLB_CHIP_CLK_OUT_2_PLL_32M_CLK))

/** @defgroup  GLB_CHIP_CLK_OUT_3_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_OUT_3_TYPE(type) (((type) == GLB_CHIP_CLK_OUT_3_CAM_REF_CLK) || \
                                          ((type) == GLB_CHIP_CLK_OUT_3_I2S_REF_CLK) || \
                                          ((type) == GLB_CHIP_CLK_OUT_3_NONE) ||        \
                                          ((type) == GLB_CHIP_CLK_OUT_3_PLL_48M_CLK))

/** @defgroup  GLB_CSI_DSI_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_CSI_DSI_CLK_SEL_TYPE(type) (((type) == GLB_CSI_DSI_CLK_SEL_XTAL_CLK) || \
                                           ((type) == GLB_CSI_DSI_CLK_SEL_CPUPLL_DIV10))

/** @defgroup  GLB_DIG_CLK_TYPE
 *  @{
 */
#define IS_GLB_DIG_CLK_TYPE(type) (((type) == GLB_DIG_CLK_WIFIPLL_32M) || \
                                   ((type) == GLB_DIG_CLK_XCLK) ||        \
                                   ((type) == GLB_DIG_CLK_AUPLL))

/** @defgroup  GLB_512K_CLK_OUT_TYPE
 *  @{
 */
#define IS_GLB_512K_CLK_OUT_TYPE(type) (((type) == GLB_512K_CLK_OUT_512K) || \
                                        ((type) == GLB_512K_CLK_OUT_256K) || \
                                        ((type) == GLB_512K_CLK_OUT_128K))

/** @defgroup  GLB_BT_BANDWIDTH_TYPE
 *  @{
 */
#define IS_GLB_BT_BANDWIDTH_TYPE(type) (((type) == GLB_BT_BANDWIDTH_1M) || \
                                        ((type) == GLB_BT_BANDWIDTH_2M))

/** @defgroup  GLB_UART2_IO_SEL_TYPE
 *  @{
 */
#define IS_GLB_UART2_IO_SEL_TYPE(type) (((type) == GLB_UART2_IO_SEL_UART2) || \
                                        ((type) == GLB_UART2_IO_SEL_ISO11898))

/** @defgroup  GLB_UART_SIG_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_TYPE(type) (((type) == GLB_UART_SIG_0) ||  \
                                    ((type) == GLB_UART_SIG_1) ||  \
                                    ((type) == GLB_UART_SIG_2) ||  \
                                    ((type) == GLB_UART_SIG_3) ||  \
                                    ((type) == GLB_UART_SIG_4) ||  \
                                    ((type) == GLB_UART_SIG_5) ||  \
                                    ((type) == GLB_UART_SIG_6) ||  \
                                    ((type) == GLB_UART_SIG_7) ||  \
                                    ((type) == GLB_UART_SIG_8) ||  \
                                    ((type) == GLB_UART_SIG_9) ||  \
                                    ((type) == GLB_UART_SIG_10) || \
                                    ((type) == GLB_UART_SIG_11))

/** @defgroup  GLB_UART_SIG_FUN_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_FUN_TYPE(type) (((type) == GLB_UART_SIG_FUN_UART0_RTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_CTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_TXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_RXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_RTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_CTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_TXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_RXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART2_RTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART2_CTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART2_TXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART2_RXD))

/** @defgroup  GLB_XTAL_TYPE
 *  @{
 */
#define IS_GLB_XTAL_TYPE(type) (((type) == GLB_XTAL_NONE) ||  \
                                ((type) == GLB_XTAL_24M) ||   \
                                ((type) == GLB_XTAL_32M) ||   \
                                ((type) == GLB_XTAL_38P4M) || \
                                ((type) == GLB_XTAL_40M) ||   \
                                ((type) == GLB_XTAL_26M) ||   \
                                ((type) == GLB_XTAL_RC32M) || \
                                ((type) == GLB_XTAL_MAX))

/** @defgroup  GLB_PLL_TYPE
 *  @{
 */
#define IS_GLB_PLL_TYPE(type) (((type) == GLB_PLL_NONE) ||    \
                               ((type) == GLB_PLL_WIFIPLL) || \
                               ((type) == GLB_PLL_AUPLL) ||   \
                               ((type) == GLB_PLL_CPUPLL) ||  \
                               ((type) == GLB_PLL_MIPIPLL) || \
                               ((type) == GLB_PLL_UHSPLL))

/** @defgroup  GLB_WAC_PLL_TYPE
 *  @{
 */
#define IS_GLB_WAC_PLL_TYPE(type) (((type) == GLB_WAC_PLL_WIFIPLL) || \
                                   ((type) == GLB_WAC_PLL_AUPLL) ||   \
                                   ((type) == GLB_WAC_PLL_CPUPLL))

/** @defgroup  GLB_MU_PLL_TYPE
 *  @{
 */
#define IS_GLB_MU_PLL_TYPE(type) (((type) == GLB_MU_PLL_MIPIPLL) || \
                                  ((type) == GLB_MU_PLL_UHSPLL))

/** @defgroup  GLB_DISP_CLK_TYPE
 *  @{
 */
#define IS_GLB_DISP_CLK_TYPE(type) (((type) == GLB_DISP_CLK_MIPIPLL_1500M))

/** @defgroup  GLB_PSRAM_PLL_TYPE
 *  @{
 */
#define IS_GLB_PSRAM_PLL_TYPE(type) (((type) == GLB_PSRAM_EMI_CPUPLL_400M) ||  \
                                     ((type) == GLB_PSRAM_EMI_WIFIPLL_320M) || \
                                     ((type) == GLB_PSRAM_EMI_AUPLL_DIV1))

/** @defgroup  GLB_DSP_XCLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_XCLK_TYPE(type) (((type) == GLB_DSP_XCLK_RC32M) || \
                                    ((type) == GLB_DSP_XCLK_XTAL))

/** @defgroup  GLB_DSP_ROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_ROOT_CLK_TYPE(type) (((type) == GLB_DSP_ROOT_CLK_XCLK) || \
                                        ((type) == GLB_DSP_ROOT_CLK_PLL))

/** @defgroup  GLB_DSP_PBROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_PBROOT_CLK_TYPE(type) (((type) == GLB_DSP_PBROOT_CLK_MM_XCLK) ||        \
                                          ((type) == GLB_DSP_PBROOT_CLK_MM_MUXPLL_240M) || \
                                          ((type) == GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M))

/** @defgroup  GLB_DSP_PLL_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_PLL_CLK_TYPE(type) (((type) == GLB_DSP_PLL_CLK_MUXPLL_240M) || \
                                       ((type) == GLB_DSP_PLL_CLK_MUXPLL_320M) || \
                                       ((type) == GLB_DSP_PLL_CLK_CPUPLL_400M))

/** @defgroup  GLB_DSP_UART_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_UART_CLK_TYPE(type) (((type) == GLB_DSP_UART_CLK_DSP_PBCLK) ||   \
                                        ((type) == GLB_DSP_UART_CLK_MUXPLL_160M) || \
                                        ((type) == GLB_DSP_UART_CLK_DSP_XCLK))

/** @defgroup  GLB_UART_CLK_TYPE
 *  @{
 */
#define IS_GLB_UART_CLK_TYPE(type) (((type) == GLB_UART_CLK_BCLK) || \
                                    ((type) == GLB_UART_CLK_PLL_160M))

/** @defgroup  GLB_DSP_CNN_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_CNN_CLK_TYPE(type) (((type) == GLB_DSP_CNN_CLK_160M) || \
                                       ((type) == GLB_DSP_CNN_CLK_240M) || \
                                       ((type) == GLB_DSP_CNN_CLK_320M))

/** @defgroup  GLB_DSP_DP_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_DP_CLK_TYPE(type) (((type) == GLB_DSP_DP_CLK_DISPLAY_PLL) || \
                                      ((type) == GLB_DSP_DP_CLK_DSP_XCLK))

/** @defgroup  GLB_DSP_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_CLK_TYPE(type) (((type) == GLB_DSP_CLK_MUXPLL_160M) || \
                                       ((type) == GLB_DSP_CLK_MUXPLL_240M) || \
                                       ((type) == GLB_DSP_CLK_CPUPLL_400M) || \
                                       ((type) == GLB_DSP_CLK_DSP_XCLK))

/** @defgroup  GLB_DSP_H264_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_H264_CLK_TYPE(type) (((type) == GLB_DSP_H264_DSP_MUXPLL_160M) || \
                                        ((type) == GLB_DSP_H264_DSP_MUXPLL_240M) || \
                                        ((type) == GLB_DSP_H264_DSP_MUXPLL_320M))

/** @defgroup  GLB_DSP_SPI_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_SPI_CLK_TYPE(type) (((type) == GLB_DSP_SPI_CLK_DSP_MUXPLL_160M) || \
                                       ((type) == GLB_DSP_SPI_CLK_DSP_XCLK))

/** @defgroup  GLB_DSP_I2C_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_I2C_CLK_TYPE(type) (((type) == GLB_DSP_I2C_CLK_DSP_PBCLK) || \
                                       ((type) == GLB_DSP_I2C_CLK_XCLK))

/** @defgroup  GLB_I2S_DI_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_I2S_DI_REF_CLK_TYPE(type) (((type) == GLB_I2S_DI_SEL_I2S_DI_INPUT) || \
                                          ((type) == GLB_I2S_DI_SEL_I2S_REF_OUTPUT))

/** @defgroup  GLB_I2S_DO_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_I2S_DO_REF_CLK_TYPE(type) (((type) == GLB_I2S_DO_SEL_I2S_DO_OUTPT) || \
                                          ((type) == GLB_I2S_DO_SEL_I2S_REF_OUTPUT))

/** @defgroup  GLB_EMI_CLK_TYPE
 *  @{
 */
#define IS_GLB_EMI_CLK_TYPE(type) (((type) == GLB_EMI_CLK_MCU_PBCLK) ||        \
                                   ((type) == GLB_EMI_CLK_CPUPLL_200M_CLK) ||  \
                                   ((type) == GLB_EMI_CLK_WIFIPLL_320M_CLK) || \
                                   ((type) == GLB_EMI_CLK_CPUPLL_400M_CLK))

/** @defgroup  GLB_DSP_SW_SYSTEM_TYPE
 *  @{
 */
#define IS_GLB_DSP_SW_SYSTEM_TYPE(type) (((type) == GLB_DSP_SW_SYSTEM_CTRL_SYS) ||   \
                                         ((type) == GLB_DSP_SW_SYSTEM_CTRL_PWRON) || \
                                         ((type) == GLB_DSP_SW_SYSTEM_CTRL_DSP0) ||  \
                                         ((type) == GLB_DSP_SW_SYSTEM_CTRL_DSP1) ||  \
                                         ((type) == GLB_DSP_SW_SYSTEM_CTRL_WL2MM))

/** @defgroup  GLB_DSP_PERIPHERAL_TYPE
 *  @{
 */
#define IS_GLB_DSP_PERIPHERAL_TYPE(type) (((type) == GLB_DSP_PERIPHERAL_MM_MISC) || \
                                          ((type) == GLB_DSP_PERIPHERAL_DMA) ||     \
                                          ((type) == GLB_DSP_PERIPHERAL_UART0) ||   \
                                          ((type) == GLB_DSP_PERIPHERAL_I2C0) ||    \
                                          ((type) == GLB_DSP_PERIPHERAL_IPC) ||     \
                                          ((type) == GLB_DSP_PERIPHERAL_SPI) ||     \
                                          ((type) == GLB_DSP_PERIPHERAL_TIMER) ||   \
                                          ((type) == GLB_DSP_PERIPHERAL_I2S0))

/** @defgroup  GLB_DSP_SUB_TYPE
 *  @{
 */
#define IS_GLB_DSP_SUB_TYPE(type) (((type) == GLB_DSP_SUB_MISC) || \
                                   ((type) == GLB_DSP_SUB_DVP2BUSA) || \
                                   ((type) == GLB_DSP_SUB_DVP2BUSB) || \
                                   ((type) == GLB_DSP_SUB_DVP2BUSC) || \
                                   ((type) == GLB_DSP_SUB_OSD_DRAW) || \
                                   ((type) == GLB_DSP_SUB_DP) ||       \
                                   ((type) == GLB_DSP_SUB_IMG_PR) ||   \
                                   ((type) == GLB_DSP_SUB_SCLRA) ||    \
                                   ((type) == GLB_DSP_SUB_SCLRB))

/** @defgroup  GLB_DSP_CODEC_SUB_TYPE
 *  @{
 */
#define IS_GLB_DSP_CODEC_SUB_TYPE(type) (((type) == GLB_DSP_CODEC_SUB_MJPEG) || \
                                         ((type) == GLB_DSP_CODEC_SUB_CNN) ||   \
                                         ((type) == GLB_DSP_CODEC_SUB_VRAM))

/** @defgroup  GLB_DSP_IMAGE_SENSOR_TYPE
 *  @{
 */
#define IS_GLB_DSP_IMAGE_SENSOR_TYPE(type) (((type) == GLB_DSP_IMAGE_SENSOR_RG_IS))

/** @defgroup  GLB_LDO15CIS_LEVEL_TYPE
 *  @{
 */
#define IS_GLB_LDO15CIS_LEVEL_TYPE(type) (((type) == GLB_LDO15CIS_LEVEL_1P00V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P05V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P10V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P15V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P20V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P30V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P40V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P45V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P50V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P55V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P60V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P65V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P70V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P75V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P80V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P85V))

/*@} end of group GLB_Public_Constants */

/** @defgroup  GLB_Public_Macros
 *  @{
 */
#define UART_SIG_SWAP_NONE          (0x00) /* uart_sig[0:11] -> uart_sig[0:11] */
#define UART_SIG_SWAP_GPIO0_GPIO11  (0x01) /* GPIO0-11  uart_sig[ 0:11] -> uart_sig[ 6:11], uart_sig[ 0: 5] */
#define UART_SIG_SWAP_GPIO12_GPIO23 (0x02) /* GPIO12-23 uart_sig[12:23] -> uart_sig[18:23], uart_sig[12:17] */
#define UART_SIG_SWAP_GPIO24_GPIO35 (0x04) /* GPIO24-35 uart_sig[24:35] -> uart_sig[30:35], uart_sig[24:29] */
#define UART_SIG_SWAP_GPIO36_GPIO47 (0x08) /* GPIO36-47 uart_sig[36:47] -> uart_sig[42:47], uart_sig[36:41] */

#define JTAG_SIG_SWAP_NONE 0x00 /* GPIO0-22  E21_TMS/E21_TDI/E21_TCK/E21_TDO <- E21_TCK/E21_TDO/E21_TMS/E21_TDI */

#define GLB_AHB_CLOCK_CPU             (0x1ULL<<GLB_AHB_CLOCK_IP_CPU)
#define GLB_AHB_CLOCK_SDU             (0x1ULL<<GLB_AHB_CLOCK_IP_SDU)
#define GLB_AHB_CLOCK_SEC             (0x1ULL<<GLB_AHB_CLOCK_IP_SEC)
#define GLB_AHB_CLOCK_DMA_0           (0x1ULL<<GLB_AHB_CLOCK_IP_DMA_0)
#define GLB_AHB_CLOCK_DMA_1           (0x1ULL<<GLB_AHB_CLOCK_IP_DMA_1)
#define GLB_AHB_CLOCK_DMA_2           (0x1ULL<<GLB_AHB_CLOCK_IP_DMA_2)
#define GLB_AHB_CLOCK_CCI             (0x1ULL<<GLB_AHB_CLOCK_IP_CCI)
#define GLB_AHB_CLOCK_RF_TOP          (0x1ULL<<GLB_AHB_CLOCK_IP_RF_TOP)
#define GLB_AHB_CLOCK_GPIP            (0x1ULL<<GLB_AHB_CLOCK_IP_GPIP)
#define GLB_AHB_CLOCK_TZC             (0x1ULL<<GLB_AHB_CLOCK_IP_TZC)
#define GLB_AHB_CLOCK_EF_CTRL         (0x1ULL<<GLB_AHB_CLOCK_IP_EF_CTRL)
#define GLB_AHB_CLOCK_SF_CTRL         (0x1ULL<<GLB_AHB_CLOCK_IP_SF_CTRL)
#define GLB_AHB_CLOCK_EMAC            (0x1ULL<<GLB_AHB_CLOCK_IP_EMAC)
#define GLB_AHB_CLOCK_UART0           (0x1ULL<<GLB_AHB_CLOCK_IP_UART0)
#define GLB_AHB_CLOCK_UART1           (0x1ULL<<GLB_AHB_CLOCK_IP_UART1)
#define GLB_AHB_CLOCK_UART2           (0x1ULL<<GLB_AHB_CLOCK_IP_UART2)
#define GLB_AHB_CLOCK_UART3           (0x1ULL<<GLB_AHB_CLOCK_IP_UART3)
//#define GLB_AHB_CLOCK_UART4           (0x1ULL<<GLB_AHB_CLOCK_IP_UART4)
#define GLB_AHB_CLOCK_SPI             (0x1ULL<<GLB_AHB_CLOCK_IP_SPI)
#define GLB_AHB_CLOCK_I2C             (0x1ULL<<GLB_AHB_CLOCK_IP_I2C)
#define GLB_AHB_CLOCK_PWM             (0x1ULL<<GLB_AHB_CLOCK_IP_PWM)
#define GLB_AHB_CLOCK_TIMER           (0x1ULL<<GLB_AHB_CLOCK_IP_TIMER)
#define GLB_AHB_CLOCK_IR              (0x1ULL<<GLB_AHB_CLOCK_IP_IR)
#define GLB_AHB_CLOCK_CHECKSUM        (0x1ULL<<GLB_AHB_CLOCK_IP_CHECKSUM)
#define GLB_AHB_CLOCK_QDEC            (0x1ULL<<GLB_AHB_CLOCK_IP_QDEC)
#define GLB_AHB_CLOCK_KYS             (0x1ULL<<GLB_AHB_CLOCK_IP_KYS)
#define GLB_AHB_CLOCK_I2S             (0x1ULL<<GLB_AHB_CLOCK_IP_I2S)
#define GLB_AHB_CLOCK_USB11           (0x1ULL<<GLB_AHB_CLOCK_IP_USB11)
#define GLB_AHB_CLOCK_CAM             (0x1ULL<<GLB_AHB_CLOCK_IP_CAM)
#define GLB_AHB_CLOCK_MJPEG           (0x1ULL<<GLB_AHB_CLOCK_IP_MJPEG)
#define GLB_AHB_CLOCK_BT_BLE_NORMAL   (0x1ULL<<GLB_AHB_CLOCK_IP_BT_BLE_NORMAL)
#define GLB_AHB_CLOCK_BT_BLE_LP       (0x1ULL<<GLB_AHB_CLOCK_IP_BT_BLE_LP)
#define GLB_AHB_CLOCK_ZB_NORMAL       (0x1ULL<<GLB_AHB_CLOCK_IP_ZB_NORMAL)
#define GLB_AHB_CLOCK_ZB_LP           (0x1ULL<<GLB_AHB_CLOCK_IP_ZB_LP)
#define GLB_AHB_CLOCK_WIFI_NORMAL     (0x1ULL<<GLB_AHB_CLOCK_IP_WIFI_NORMAL)
#define GLB_AHB_CLOCK_WIFI_LP         (0x1ULL<<GLB_AHB_CLOCK_IP_WIFI_LP)
#define GLB_AHB_CLOCK_BT_BLE_2_NORMAL (0x1ULL<<GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL)
#define GLB_AHB_CLOCK_BT_BLE_2_LP     (0x1ULL<<GLB_AHB_CLOCK_IP_BT_BLE_2_LP)
#define GLB_AHB_CLOCK_EMI_MISC        (0x1ULL<<GLB_AHB_CLOCK_IP_EMI_MISC)
#define GLB_AHB_CLOCK_PSRAM0_CTRL     (0x1ULL<<GLB_AHB_CLOCK_IP_PSRAM0_CTRL)
#define GLB_AHB_CLOCK_PSRAM1_CTRL     (0x1ULL<<GLB_AHB_CLOCK_IP_PSRAM1_CTRL)
#define GLB_AHB_CLOCK_USB20           (0x1ULL<<GLB_AHB_CLOCK_IP_USB20)
#define GLB_AHB_CLOCK_MIX2            (0x1ULL<<GLB_AHB_CLOCK_IP_MIX2)
#define GLB_AHB_CLOCK_AUDIO           (0x1ULL<<GLB_AHB_CLOCK_IP_AUDIO)
#define GLB_AHB_CLOCK_SDH             (0x1ULL<<GLB_AHB_CLOCK_IP_SDH)
#define GLB_AHB_CLOCK_ZB_2_NORMAL     (0x1ULL<<GLB_AHB_CLOCK_IP_ZB2_NORMAL)
#define GLB_AHB_CLOCK_ZB_2_LP         (0x1ULL<<GLB_AHB_CLOCK_IP_ZB2_LP)
#define GLB_AHB_CLOCK_I2C1            (0x1ULL<<GLB_AHB_CLOCK_IP_I2C1)
#define GLB_AHB_CLOCK_WIFI_PHY        (0x1ULL<<GLB_AHB_CLOCK_IP_WIFI_PHY)
#define GLB_AHB_CLOCK_WIFI_MAC_PHY    (0x1ULL<<GLB_AHB_CLOCK_IP_WIFI_MAC_PHY)
#define GLB_AHB_CLOCK_WIFI_PLATFORM   (0x1ULL<<GLB_AHB_CLOCK_IP_WIFI_PLATFORM)
#define GLB_AHB_CLOCK_LZ4             (0x1ULL<<GLB_AHB_CLOCK_IP_LZ4)
#define GLB_AHB_CLOCK_AUPDM           (0x1ULL<<GLB_AHB_CLOCK_IP_AUPDM)
#define GLB_AHB_CLOCK_GAUGE           (0x1ULL<<GLB_AHB_CLOCK_IP_GAUGE)

#define GLB_AUTO_CALC_XTAL_FLAG_MASK  0x0000ff00
#define GLB_AUTO_CALC_XTAL_FLAG_VALUE 0x5800

extern const GLB_WAC_PLL_Cfg_Type wifiPllCfg_960M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type audioPllCfg_442P368M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type audioPllCfg_451P584M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type cpuPllCfg_380M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type cpuPllCfg_400M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type cpuPllCfg_440M[GLB_XTAL_MAX];
extern const GLB_WAC_PLL_Cfg_Type cpuPllCfg_480M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type mipiPllCfg_1500M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_2100M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_1400M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_1500M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_1600M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_400M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_667M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_800M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_1066M[GLB_XTAL_MAX];
extern const GLB_MU_PLL_Cfg_Type uhsPllCfg_2000M[GLB_XTAL_MAX];

/*@} end of group GLB_Public_Macros */

/** @defgroup  GLB_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void BMX_ERR_IRQHandler(void);
void BMX_TO_IRQHandler(void);
#endif
/*----------*/
BL_Err_Type GLB_Set_MCU_Muxpll_160M_Sel(GLB_MCU_MUXPLL_160M_CLK_SEL_Type clkSel);
GLB_MCU_MUXPLL_160M_CLK_SEL_Type GLB_Get_MCU_Muxpll_160M_Sel(void);
BL_Err_Type GLB_Set_MCU_Muxpll_80M_Sel(GLB_MCU_MUXPLL_80M_CLK_SEL_Type clkSel);
GLB_MCU_MUXPLL_80M_CLK_SEL_Type GLB_Get_MCU_Muxpll_80M_Sel(void);
BL_Err_Type GLB_Set_DSP_Muxpll_320M_Sel(GLB_DSP_MUXPLL_320M_CLK_SEL_Type clkSel);
GLB_DSP_MUXPLL_320M_CLK_SEL_Type GLB_Get_DSP_Muxpll_320M_Sel(void);
BL_Err_Type GLB_Set_DSP_Muxpll_240M_Sel(GLB_DSP_MUXPLL_240M_CLK_SEL_Type clkSel);
GLB_DSP_MUXPLL_240M_CLK_SEL_Type GLB_Get_DSP_Muxpll_240M_Sel(void);
BL_Err_Type GLB_Set_DSP_Muxpll_160M_Sel(GLB_DSP_MUXPLL_160M_CLK_SEL_Type clkSel);
GLB_DSP_MUXPLL_160M_CLK_SEL_Type GLB_Get_DSP_Muxpll_160M_Sel(void);
/*----------*/
BL_Err_Type GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_Type xtalType, GLB_PLL_Type pllPuType);
BL_Err_Type GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_Type pllType);
BL_Err_Type GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk);
BL_Err_Type GLB_Power_On_WAC_PLL(GLB_WAC_PLL_Type pllType, const GLB_WAC_PLL_Cfg_Type *const cfg, uint8_t waitStable);
BL_Err_Type GLB_Set_USB_CLK_From_WIFIPLL(uint8_t enable);
BL_Err_Type GLB_Power_Off_MU_PLL(GLB_MU_PLL_Type pllType);
BL_Err_Type GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk);
BL_Err_Type GLB_Power_On_MU_PLL(GLB_MU_PLL_Type pllType, const GLB_MU_PLL_Cfg_Type *const cfg, uint8_t waitStable);
BL_Err_Type GLB_Set_Display_CLK(uint8_t enable, GLB_DISP_CLK_Type srcClk, uint8_t evenDiv);
BL_Err_Type GLB_Set_EMAC_CLK(uint8_t enable);
BL_Err_Type GLB_Output_EMAC_CLK(uint8_t gpio);
/*----------*/
BL_Err_Type GLB_Set_MCU_System_CLK_Div(uint8_t mcuClkDiv, uint8_t mcuPBclkDiv, uint8_t lpClkDiv);
BL_Err_Type GLB_Get_MCU_System_CLK_Div(uint8_t *mcuClkDiv, uint8_t *mcuPBclkDiv, uint8_t *lpClkDiv);
BL_Err_Type GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_Type clkFreq);
BL_Err_Type GLB_Set_System_CLK_Div(uint8_t hclkDiv,uint8_t bclkDiv);
/*----------*/
BL_Err_Type GLB_Set_DSP_System_CLK_Div(uint8_t dspClkDiv, uint8_t dspBclkDiv);
BL_Err_Type GLB_Get_DSP_System_CLK_Div(uint8_t *dspClkDiv, uint8_t *dspBclkDiv);
BL_Err_Type GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_Type clkFreq);
BL_Err_Type GLB_Set_DSP_PBCLK_Div(uint8_t dspPBclkDiv);
BL_Err_Type GLB_Get_DSP_PBCLK_Div(uint8_t *dspPBclkDiv);
BL_Err_Type GLB_Set_DSP_PBCLK(GLB_DSP_SYS_PBCLK_Type pbClkSel);
/*----------*/
BL_Err_Type GLB_DSP0_Clock_Enable(void);
BL_Err_Type GLB_DSP0_Clock_Disable(void);
GLB_DSP_XCLK_Type GLB_Get_DSP_XCLK_Sel(void);
BL_Err_Type GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_Type xclk);
GLB_DSP_ROOT_CLK_Type GLB_Get_DSP_ROOT_CLK_Sel(void);
BL_Err_Type GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_Type rootClk);
BL_Err_Type GLB_Set_DSP_MUXPLL_CLK_Sel(GLB_DSP_PLL_CLK_Type pllClk);
GLB_DSP_PBROOT_CLK_Type GLB_Get_DSP_PBROOT_CLK_Sel(void);
BL_Err_Type GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_Type pbrootClk);
/*----------*/
GLB_CORE_ID_Type GLB_Get_Core_Type(void);
BL_Err_Type GLB_Halt_CPU(GLB_CORE_ID_Type coreID);
BL_Err_Type GLB_Release_CPU(GLB_CORE_ID_Type coreID);
BL_Err_Type GLB_Set_CPU_Reset_Address(GLB_CORE_ID_Type coreID, uint32_t addr);
/*----------*/
BL_Sts_Type GLB_DSP_Get_MCU_IntStatus(GLB_MCU_ALL_INT_Type intType);
BL_Err_Type GLB_DSP_Set_MCU_IntMask(GLB_MCU_ALL_INT_Type intType, BL_Mask_Type intMask);
BL_Err_Type GLB_DSP_Clr_MCU_IntStatus(GLB_MCU_ALL_INT_Type intType);
BL_Err_Type GLB_DSP_Set_LP_IntEn(uint8_t enable, GLB_LP_ALL_INT_Type intType);
BL_Sts_Type GLB_DSP_Get_LP_IntStatus(GLB_LP_ALL_INT_Type intType);
BL_Sts_Type GLB_MCU_Get_DSP_IntStatus(GLB_DSP_ALL_INT_Type intType);
BL_Err_Type GLB_MCU_Set_DSP_IntMask(GLB_DSP_ALL_INT_Type intType, BL_Mask_Type intMask);
BL_Err_Type GLB_MCU_Clr_DSP_IntStatus(GLB_DSP_ALL_INT_Type intType);
/*----------*/
BL_Err_Type GLB_Set_EMI_CLK(uint8_t enable, GLB_EMI_CLK_Type clkSel, uint32_t div);
BL_Err_Type GLB_Clr_EMI_Reset_Gate(void);
BL_Err_Type GLB_Set_MCU_MTimer_CLK(uint8_t enable, uint16_t div, uint8_t rst);
BL_Err_Type GLB_Set_DSP_MTimer_CLK(uint8_t enable, uint16_t div, uint8_t rst);
BL_Err_Type GLB_Set_ADC_CLK(uint8_t enable, GLB_ADC_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DMA_CLK(uint8_t enable, GLB_DMA_CLK_ID_Type clk);
BL_Err_Type GLB_Set_Peripheral_DMA_CN(GLB_PERI_DMA_Type peri, GLB_PERI_DMA_CN_SEL_Type cn);
BL_Err_Type GLB_Set_IR_CLK(uint8_t enable, GLB_IR_CLK_SRC_Type clkSel, uint8_t div);
BL_Err_Type GLB_IR_RX_GPIO_Sel(GLB_GPIO_Type gpio);
BL_Err_Type GLB_IR_LED_Driver_Enable(void);
BL_Err_Type GLB_IR_LED_Driver_Disable(void);
BL_Err_Type GLB_Set_UART2_IO_Sel(GLB_UART2_IO_SEL_Type ioType);
BL_Err_Type GLB_Set_UART_CLK(uint8_t enable, HBN_UART_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_UART_Fun_Sel(GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun);
BL_Err_Type GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, GLB_I2C_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_I2S_CLK(uint8_t refClkEn, uint8_t refClkDiv, GLB_I2S_DI_REF_CLK_Type inRef, GLB_I2S_DO_REF_CLK_Type outRef);
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, GLB_SPI_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_PWM1_IO_Sel(GLB_PWM1_IO_SEL_Type ioSel);
BL_Err_Type GLB_Set_PWM2_IO_Sel(GLB_PWM2_IO_SEL_Type ioSel);
BL_Err_Type GLB_Set_PDM_IO_Sel(GLB_PDM_IO_SEL_Type ioSel);
/*----------*/
BL_Err_Type GLB_Set_DIG_CLK_Sel(GLB_DIG_CLK_Type clkSel);
BL_Err_Type GLB_Set_DIG_512K_CLK(uint8_t enable, uint8_t compensationEn, uint8_t div);
BL_Err_Type GLB_Set_DIG_32K_CLK(uint8_t enable, uint8_t compensationEn, uint16_t div);
BL_Err_Type GLB_Platform_Wakeup_PDS_Enable(uint8_t enable);
/*----------*/
BL_Err_Type GLB_Sel_MCU_TMR_GPIO_Clock(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Sel_DSP_TMR_GPIO_Clock(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Set_Chip_Clock_Out0_Sel(GLB_CHIP_CLK_OUT_0_Type clkOutType);
BL_Err_Type GLB_Set_Chip_Clock_Out1_Sel(GLB_CHIP_CLK_OUT_1_Type clkOutType);
BL_Err_Type GLB_Set_Chip_Clock_Out2_Sel(GLB_CHIP_CLK_OUT_2_Type clkOutType);
BL_Err_Type GLB_Set_Chip_Clock_Out3_Sel(GLB_CHIP_CLK_OUT_3_Type clkOutType);
BL_Err_Type GLB_Set_CSI_DSI_CLK_Sel(GLB_CSI_DSI_CLK_SEL_Type csiClkSel, GLB_CSI_DSI_CLK_SEL_Type dsiClkSel);
/*----------*/
BL_Err_Type GLB_BMX_TO_Init(BMX_TO_Cfg_Type *BmxCfg);
uint8_t GLB_Get_BMX_TO_Status(void);
BL_Err_Type GLB_Clr_BMX_TO_Status(void);
/*----------*/
BL_Err_Type GLB_Set_Audio_AUTO_CLK(uint8_t divEn);
BL_Err_Type GLB_Set_Audio_ADC_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Set_Audio_DAC_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Set_Audio_PDM_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Set_PADC_CLK(uint8_t enable, uint16_t div);
/*----------*/
BL_Err_Type GLB_Invert_ETH_RX_CLK(uint8_t enable);
BL_Err_Type GLB_Invert_ETH_TX_CLK(uint8_t enable);
BL_Err_Type GLB_Invert_ETH_REF_O_CLK(uint8_t enable);
BL_Err_Type GLB_Set_ETH_REF_O_CLK_Sel(GLB_ETH_REF_CLK_OUT_Type clkSel);
/*----------*/
BL_Err_Type GLB_Set_CAM_CLK(uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_SDH_CLK(uint8_t enable, GLB_SDH_CLK_Type clkSel, uint8_t div);
/*----------*/
BL_Err_Type GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_Type group, uint8_t swap);
BL_Err_Type GLB_Swap_DSP_SPI_0_MOSI_With_MISO(BL_Fun_Type newState);
BL_Err_Type GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_Set_DSP_L2SRAM_Available_Size(uint8_t h2pfSramRel, uint8_t vramSramRel, uint8_t subSramRel, uint8_t blaiSramRel);
BL_Err_Type GLB_Swap_MCU_SPI_0_MOSI_With_MISO(BL_Fun_Type newState);
BL_Err_Type GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_Set_Flash_IO_PARM(uint8_t selEmbedded, uint8_t swap);
/*----------*/
BL_Err_Type GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_Type swrst);
BL_Err_Type GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_Type swrst);
BL_Err_Type GLB_PER_Clock_Gate(uint64_t ips);
BL_Err_Type GLB_PER_Clock_UnGate(uint64_t ips);
BL_Err_Type GLB_PSRAM_PER_Clock_Gate(void);
BL_Err_Type GLB_PSRAM_PER_Clock_UnGate(void);
BL_Err_Type GLB_PLL_CGEN_Clock_Gate(GLB_PLL_CGEN_Type clk);
BL_Err_Type GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_Type clk);
BL_Err_Type GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel);
BL_Err_Type GLB_MCU_SW_System_Reset(GLB_MCU_SW_SYSTEM_Type sysPart);
BL_Err_Type GLB_SW_System_Reset(void);
BL_Err_Type GLB_SW_CPU_Reset(void);
BL_Err_Type GLB_SW_POR_Reset(void);
BL_Err_Type GLB_Disrst_Set(uint8_t enable, GLB_DISRST_Type disrst);
/*----------*/
BL_Err_Type GLB_Set_Auto_Calc_Xtal_Type(GLB_XTAL_Type calcXtalType);
BL_Err_Type GLB_Get_Auto_Calc_Xtal_Type(GLB_XTAL_Type *calcXtalType);
BL_Err_Type GLB_Set_Flash_Id_Value(uint32_t idValue);
uint32_t GLB_Get_Flash_Id_Value(void);
/*----------*/
BL_Err_Type GLB_Set_SRAM_RET(uint32_t value);
uint32_t GLB_Get_SRAM_RET(void);
BL_Err_Type GLB_Set_SRAM_SLP(uint32_t value);
uint32_t GLB_Get_SRAM_SLP(void);
BL_Err_Type GLB_Set_SRAM_PARM(uint32_t value);
uint32_t GLB_Get_SRAM_PARM(void);
BL_Err_Type GLB_Set_EM_Sel(GLB_EM_Type emType);
/*----------*/
BL_Err_Type GLB_Set_PSram_CLK(uint8_t id, uint8_t enable, GLB_PSRAM_PLL_Type pll, uint8_t div);
BL_Err_Type GLB_Trim_LDO18IO_Vout(void);
BL_Err_Type GLB_Trim_LDO18FLASH_Vout(void);
/*----------*/
BL_Err_Type GLB_Set_DSP_CNN_CLK(uint8_t enable, GLB_DSP_CNN_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_DP_CLK(uint8_t enable, GLB_DSP_DP_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_CLK(uint8_t enable, GLB_DSP_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_H264_CLK(uint8_t enable, GLB_DSP_H264_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_SPI_CLK(uint8_t enable, GLB_DSP_SPI_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_UART0_CLK(uint8_t enable, GLB_DSP_UART_CLK_Type uartClk, uint8_t div);
BL_Err_Type GLB_Set_DSP_UART1_CLK(uint8_t enable, GLB_DSP_UART_CLK_Type uartClk, uint8_t div);
BL_Err_Type GLB_Set_DSP_I2C0_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div);
BL_Err_Type GLB_Set_DSP_I2C1_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div);
/*----------*/
BL_Err_Type GLB_DSP_SW_System_Reset(GLB_DSP_SW_SYSTEM_Type sysPart);
BL_Err_Type GLB_DSP_Peripheral_Reset(GLB_DSP_PERIPHERAL_Type periPart);
BL_Err_Type GLB_DSP_Sub_Reset(GLB_DSP_SUB_Type subPart);
BL_Err_Type GLB_DSP_Codec_Sub_Reset(GLB_DSP_CODEC_SUB_Type codecPart);
BL_Err_Type GLB_DSP_Image_Sensor_Reset(GLB_DSP_IMAGE_SENSOR_Type imageSensorPart);
/*----------*/
BL_Err_Type GLB_Config_WIFI_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_AUDIO_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_CPU_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_MIPI_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_MIPI_PLL_Div(uint8_t divEn, uint8_t divRatio);
BL_Err_Type GLB_Config_UHS_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList);
/*----------*/
BL_Err_Type GLB_Set_Ldo15cis_Vout(GLB_LDO15CIS_LEVEL_Type ldoLevel);
BL_Err_Type GLB_CSI_Config_MIPIPLL(uint8_t postDivSel, uint32_t sdmin);
BL_Err_Type GLB_CSI_Power_Up_MIPIPLL(void);
/*----------*/;

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_GLB_H__ */
