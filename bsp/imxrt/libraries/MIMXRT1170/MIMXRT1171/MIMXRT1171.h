/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    IMXRT1170RM, Rev 1, 02/2021
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MIMXRT1171
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file MIMXRT1171.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for MIMXRT1171
 *
 * CMSIS Peripheral Access Layer for MIMXRT1171
 */

#if !defined(MIMXRT1171_H_)  /* Check if memory map has not been already included */
#define MIMXRT1171_H_

/* IP Header Files List */
#include "PERI_ADC.h"
#include "PERI_ADC_ETC.h"
#include "PERI_ANADIG_LDO_SNVS.h"
#include "PERI_ANADIG_LDO_SNVS_DIG.h"
#include "PERI_ANADIG_MISC.h"
#include "PERI_ANADIG_OSC.h"
#include "PERI_ANADIG_PLL.h"
#include "PERI_ANADIG_PMU.h"
#include "PERI_ANADIG_TEMPSENSOR.h"
#include "PERI_AOI.h"
#include "PERI_ASRC.h"
#include "PERI_AUDIO_PLL.h"
#include "PERI_CAAM.h"
#include "PERI_CAN.h"
#include "PERI_CAN_WRAPPER.h"
#include "PERI_CCM.h"
#include "PERI_CCM_OBS.h"
#include "PERI_CDOG.h"
#include "PERI_CMP.h"
#include "PERI_DAC.h"
#include "PERI_DCDC.h"
#include "PERI_DCIC.h"
#include "PERI_DMA.h"
#include "PERI_DMAMUX.h"
#include "PERI_DSI_HOST.h"
#include "PERI_DSI_HOST_APB_PKT_IF.h"
#include "PERI_DSI_HOST_DPI_INTFC.h"
#include "PERI_DSI_HOST_NXP_FDSOI28_DPHY_INTFC.h"
#include "PERI_EMVSIM.h"
#include "PERI_ENC.h"
#include "PERI_ENET.h"
#include "PERI_ETHERNET_PLL.h"
#include "PERI_EWM.h"
#include "PERI_FLEXIO.h"
#include "PERI_FLEXRAM.h"
#include "PERI_FLEXSPI.h"
#include "PERI_GPC_CPU_MODE_CTRL.h"
#include "PERI_GPC_SET_POINT_CTRL.h"
#include "PERI_GPC_STBY_CTRL.h"
#include "PERI_GPIO.h"
#include "PERI_GPT.h"
#include "PERI_I2S.h"
#include "PERI_IEE.h"
#include "PERI_IEE_APC.h"
#include "PERI_IOMUXC.h"
#include "PERI_IOMUXC_GPR.h"
#include "PERI_IOMUXC_LPSR.h"
#include "PERI_IOMUXC_LPSR_GPR.h"
#include "PERI_IOMUXC_SNVS.h"
#include "PERI_IOMUXC_SNVS_GPR.h"
#include "PERI_IPS_DOMAIN.h"
#include "PERI_KEY_MANAGER.h"
#include "PERI_KPP.h"
#include "PERI_LCDIFV2.h"
#include "PERI_LPI2C.h"
#include "PERI_LPSPI.h"
#include "PERI_LPUART.h"
#include "PERI_MCM.h"
#include "PERI_MECC.h"
#include "PERI_MIPI_CSI2RX.h"
#include "PERI_MU.h"
#include "PERI_OCOTP.h"
#include "PERI_OSC_RC_400M.h"
#include "PERI_OTFAD.h"
#include "PERI_PDM.h"
#include "PERI_PGMC_BPC.h"
#include "PERI_PGMC_CPC.h"
#include "PERI_PGMC_MIF.h"
#include "PERI_PGMC_PPC.h"
#include "PERI_PHY_LDO.h"
#include "PERI_PIT.h"
#include "PERI_PUF.h"
#include "PERI_PWM.h"
#include "PERI_RDC.h"
#include "PERI_RDC_SEMAPHORE.h"
#include "PERI_RTWDOG.h"
#include "PERI_SEMA4.h"
#include "PERI_SEMC.h"
#include "PERI_SNVS.h"
#include "PERI_SPDIF.h"
#include "PERI_SRAM.h"
#include "PERI_SRC.h"
#include "PERI_SSARC_HP.h"
#include "PERI_SSARC_LP.h"
#include "PERI_TMPSNS.h"
#include "PERI_TMR.h"
#include "PERI_USB.h"
#include "PERI_USBHSDCD.h"
#include "PERI_USBNC.h"
#include "PERI_USBPHY.h"
#include "PERI_USDHC.h"
#include "PERI_VIDEO_MUX.h"
#include "PERI_VIDEO_PLL.h"
#include "PERI_VMBANDGAP.h"
#include "PERI_WDOG.h"
#include "PERI_XBARA.h"
#include "PERI_XBARB.h"
#include "PERI_XECC.h"
#include "PERI_XRDC2.h"

#endif  /* #if !defined(MIMXRT1171_H_) */
