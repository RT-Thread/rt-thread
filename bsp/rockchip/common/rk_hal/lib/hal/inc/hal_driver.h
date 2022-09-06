/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2018-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef _HAL_DRIVER_H_
#define _HAL_DRIVER_H_

#include "hal_pm.h"

#ifdef HAL_ACDCDIG_MODULE_ENABLED
#include "hal_acdcdig.h"
#endif

#ifdef HAL_ACODEC_MODULE_ENABLED
#include "hal_acodec.h"
#endif

#ifdef HAL_AUDIOPWM_MODULE_ENABLED
#include "hal_audiopwm.h"
#endif

#include "hal_cache.h"

#ifdef HAL_BUFMGR_MODULE_ENABLED
#include "hal_bufmgr.h"
#endif

#ifdef HAL_CANFD_MODULE_ENABLED
#include "hal_canfd.h"
#endif

#ifdef HAL_CKCAL_MODULE_ENABLED
#include "hal_ckcal.h"
#endif

#ifdef HAL_CACHE_ECC_MODULE_ENABLED
#include "hal_cache_ecc.h"
#endif

#ifdef HAL_CPU_TOPOLOGY_MODULE_ENABLED
#include "hal_cpu_topology.h"
#endif

#ifdef HAL_CRU_MODULE_ENABLED
#include "hal_cru.h"
#endif

#ifdef HAL_CRYPTO_MODULE_ENABLED
#include "hal_crypto.h"
#endif

#ifdef HAL_DSI_MODULE_ENABLED
#include "hal_display.h"
#include "hal_dsi.h"
#endif

#ifdef HAL_DEMO_MODULE_ENABLED
#include "hal_demo.h"
#endif

#ifdef HAL_DDR_ECC_MODULE_ENABLED
#include "hal_ddr_ecc.h"
#endif

#ifdef HAL_DSP_MODULE_ENABLED
#include "hal_dsp.h"
#endif

#include "hal_dma.h"

#ifdef HAL_DWDMA_MODULE_ENABLED
#include "hal_dwdma.h"
#endif

#ifdef HAL_EFUSE_MODULE_ENABLED
#include "hal_efuse.h"
#endif

#ifdef HAL_GMAC_MODULE_ENABLED
#include "hal_gmac.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
#include "hal_gpio.h"
#endif

#ifdef HAL_GPIO_IRQ_GROUP_MODULE_ENABLED
#include "hal_gpio_irq_group.h"
#endif

#ifdef HAL_PINCTRL_MODULE_ENABLED
#include "hal_pinctrl.h"
#endif

#if defined(HAL_HCD_MODULE_ENABLED) || defined(HAL_PCD_MODULE_ENABLED)
#include "hal_usb_core.h"
#include "hal_usb_phy.h"
#endif

#if defined(HAL_EHCI_MODULE_ENABLED) || defined(HAL_OHCI_MODULE_ENABLED)
#include "hal_usbh.h"
#endif

#ifdef HAL_HCD_MODULE_ENABLED
#include "hal_hcd.h"
#endif

#ifdef HAL_HWSPINLOCK_MODULE_ENABLED
#include "hal_hwspinlock.h"
#endif

#ifdef HAL_HYPERPSRAM_MODULE_ENABLED
#include "hal_hyperpsram.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
#include "hal_i2c.h"
#endif

#ifdef HAL_I2S_MODULE_ENABLED
#include "hal_i2s.h"
#endif

#ifdef HAL_I2STDM_MODULE_ENABLED
#include "hal_i2stdm.h"
#endif

#ifdef HAL_INTC_MODULE_ENABLED
#include "hal_intc.h"
#endif

#ifdef HAL_IRQ_HANDLER_MODULE_ENABLED
#include "hal_irq_handler.h"
#endif

#ifdef HAL_GIC_MODULE_ENABLED
#include "hal_gic.h"
#endif

#ifdef HAL_MBOX_MODULE_ENABLED
#include "hal_mbox.h"
#endif

#ifdef HAL_NVIC_MODULE_ENABLED
#include "hal_nvic.h"
#endif

#ifdef HAL_PCD_MODULE_ENABLED
#include "hal_pcd.h"
#endif

#ifdef HAL_PDM_MODULE_ENABLED
#include "hal_pdm.h"
#endif

#ifdef HAL_PL330_MODULE_ENABLED
#include "hal_pl330.h"
#endif

#ifdef HAL_PMU_MODULE_ENABLED
#include "hal_pd.h"
#endif

#ifdef HAL_PVTM_MODULE_ENABLED
#include "hal_pvtm.h"
#endif

#ifdef HAL_PWM_MODULE_ENABLED
#include "hal_pwm.h"
#endif

#include "hal_pwr.h"

#ifdef HAL_SDIO_MODULE_ENABLED
#include "hal_sdio.h"
#endif

#ifdef HAL_SNOR_MODULE_ENABLED
#include "hal_spi_mem.h"
#include "hal_snor.h"
#endif

#ifdef HAL_SFC_MODULE_ENABLED
#include "hal_sfc.h"
#endif

#ifdef HAL_SPINAND_MODULE_ENABLED
#include "hal_spi_mem.h"
#include "hal_spinand.h"
#endif

#ifdef HAL_SYSTICK_MODULE_ENABLED
#include "hal_systick.h"
#endif

#ifdef HAL_FSPI_MODULE_ENABLED
#include "hal_spi_mem.h"
#include "hal_fspi.h"
#endif

#ifdef HAL_QPIPSRAM_MODULE_ENABLED
#include "hal_spi_mem.h"
#include "hal_qpipsram.h"
#endif

#ifdef HAL_TOUCHKEY_MODULE_ENABLED
#include "hal_touchkey.h"
#endif

#ifdef HAL_TSADC_MODULE_ENABLED
#include "hal_tsadc.h"
#endif

#ifdef HAL_SARADC_MODULE_ENABLED
#include "hal_saradc.h"
#endif

#ifdef HAL_SMCCC_MODULE_ENABLED
#include "hal_smccc.h"
#endif

#ifdef HAL_KEYCTRL_MODULE_ENABLED
#include "hal_keyctrl.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
#include "hal_spi.h"
#endif

#ifdef HAL_SPI2APB_MODULE_ENABLED
#include "hal_spi2apb.h"
#endif

#ifdef HAL_TIMER_MODULE_ENABLED
#include "hal_timer.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "hal_uart.h"
#endif

#ifdef HAL_VAD_MODULE_ENABLED
#include "hal_vad.h"
#endif

#ifdef HAL_VICAP_MODULE_ENABLED
#include "hal_vicap.h"
#endif

#ifdef HAL_VOP_MODULE_ENABLED
#include "hal_display.h"
#include "hal_vop.h"
#endif

#ifdef HAL_WDT_MODULE_ENABLED
#include "hal_wdt.h"
#endif

#endif
