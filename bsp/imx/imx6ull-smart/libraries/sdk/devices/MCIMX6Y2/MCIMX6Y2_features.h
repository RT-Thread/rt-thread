/*
** ###################################################################
**     Version:             rev. 3.0, 2017-02-28
**     Build:               b170422
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2015-12-18)
**         Initial version.
**     - rev. 2.0 (2016-08-02)
**         Rev.B Header GA
**     - rev. 3.0 (2017-02-28)
**         Rev.1 Header GA
**
** ###################################################################
*/

#ifndef _MCIMX6Y2_FEATURES_H_
#define _MCIMX6Y2_FEATURES_H_

/* SOC module features */

/* @brief ACMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACMP_COUNT (0)
/* @brief ADC availability on the SoC. */
#define FSL_FEATURE_SOC_ADC_COUNT (1)
/* @brief ADC12 availability on the SoC. */
#define FSL_FEATURE_SOC_ADC12_COUNT (0)
/* @brief ADC16 availability on the SoC. */
#define FSL_FEATURE_SOC_ADC16_COUNT (0)
/* @brief ADC_5HC availability on the SoC. */
#define FSL_FEATURE_SOC_ADC_5HC_COUNT (1)
/* @brief AES availability on the SoC. */
#define FSL_FEATURE_SOC_AES_COUNT (0)
/* @brief AFE availability on the SoC. */
#define FSL_FEATURE_SOC_AFE_COUNT (0)
/* @brief AGC availability on the SoC. */
#define FSL_FEATURE_SOC_AGC_COUNT (0)
/* @brief AIPS availability on the SoC. */
#define FSL_FEATURE_SOC_AIPS_COUNT (0)
/* @brief AIPSTZ availability on the SoC. */
#define FSL_FEATURE_SOC_AIPSTZ_COUNT (3)
/* @brief ANATOP availability on the SoC. */
#define FSL_FEATURE_SOC_ANATOP_COUNT (0)
/* @brief AOI availability on the SoC. */
#define FSL_FEATURE_SOC_AOI_COUNT (0)
/* @brief APBH availability on the SoC. */
#define FSL_FEATURE_SOC_APBH_COUNT (1)
/* @brief ASMC availability on the SoC. */
#define FSL_FEATURE_SOC_ASMC_COUNT (0)
/* @brief ASRC availability on the SoC. */
#define FSL_FEATURE_SOC_ASRC_COUNT (1)
/* @brief ASYNC_SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_ASYNC_SYSCON_COUNT (0)
/* @brief ATX availability on the SoC. */
#define FSL_FEATURE_SOC_ATX_COUNT (0)
/* @brief AXBS availability on the SoC. */
#define FSL_FEATURE_SOC_AXBS_COUNT (0)
/* @brief BCH availability on the SoC. */
#define FSL_FEATURE_SOC_BCH_COUNT (1)
/* @brief BLEDP availability on the SoC. */
#define FSL_FEATURE_SOC_BLEDP_COUNT (0)
/* @brief BOD availability on the SoC. */
#define FSL_FEATURE_SOC_BOD_COUNT (0)
/* @brief CAAM availability on the SoC. */
#define FSL_FEATURE_SOC_CAAM_COUNT (0)
/* @brief CADC availability on the SoC. */
#define FSL_FEATURE_SOC_CADC_COUNT (0)
/* @brief CALIB availability on the SoC. */
#define FSL_FEATURE_SOC_CALIB_COUNT (0)
/* @brief CAN availability on the SoC. */
#define FSL_FEATURE_SOC_CAN_COUNT (0)
/* @brief CAU availability on the SoC. */
#define FSL_FEATURE_SOC_CAU_COUNT (0)
/* @brief CAU3 availability on the SoC. */
#define FSL_FEATURE_SOC_CAU3_COUNT (0)
/* @brief CCM availability on the SoC. */
#define FSL_FEATURE_SOC_CCM_COUNT (1)
/* @brief CCM_ANALOG availability on the SoC. */
#define FSL_FEATURE_SOC_CCM_ANALOG_COUNT (1)
/* @brief CHRG availability on the SoC. */
#define FSL_FEATURE_SOC_CHRG_COUNT (0)
/* @brief CMP availability on the SoC. */
#define FSL_FEATURE_SOC_CMP_COUNT (0)
/* @brief CMT availability on the SoC. */
#define FSL_FEATURE_SOC_CMT_COUNT (0)
/* @brief CNC availability on the SoC. */
#define FSL_FEATURE_SOC_CNC_COUNT (0)
/* @brief COP availability on the SoC. */
#define FSL_FEATURE_SOC_COP_COUNT (0)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (0)
/* @brief CS availability on the SoC. */
#define FSL_FEATURE_SOC_CS_COUNT (0)
/* @brief CSI availability on the SoC. */
#define FSL_FEATURE_SOC_CSI_COUNT (1)
/* @brief CT32B availability on the SoC. */
#define FSL_FEATURE_SOC_CT32B_COUNT (0)
/* @brief CTI availability on the SoC. */
#define FSL_FEATURE_SOC_CTI_COUNT (0)
/* @brief CTIMER availability on the SoC. */
#define FSL_FEATURE_SOC_CTIMER_COUNT (0)
/* @brief DAC availability on the SoC. */
#define FSL_FEATURE_SOC_DAC_COUNT (0)
/* @brief DAC32 availability on the SoC. */
#define FSL_FEATURE_SOC_DAC32_COUNT (0)
/* @brief DCDC availability on the SoC. */
#define FSL_FEATURE_SOC_DCDC_COUNT (0)
/* @brief DCP availability on the SoC. */
#define FSL_FEATURE_SOC_DCP_COUNT (1)
/* @brief DDR availability on the SoC. */
#define FSL_FEATURE_SOC_DDR_COUNT (0)
/* @brief DDRC availability on the SoC. */
#define FSL_FEATURE_SOC_DDRC_COUNT (0)
/* @brief DDRC_MP availability on the SoC. */
#define FSL_FEATURE_SOC_DDRC_MP_COUNT (0)
/* @brief DDR_PHY availability on the SoC. */
#define FSL_FEATURE_SOC_DDR_PHY_COUNT (0)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (0)
/* @brief DMAMUX availability on the SoC. */
#define FSL_FEATURE_SOC_DMAMUX_COUNT (0)
/* @brief DMIC availability on the SoC. */
#define FSL_FEATURE_SOC_DMIC_COUNT (0)
/* @brief DRY availability on the SoC. */
#define FSL_FEATURE_SOC_DRY_COUNT (0)
/* @brief DSPI availability on the SoC. */
#define FSL_FEATURE_SOC_DSPI_COUNT (0)
/* @brief ECSPI availability on the SoC. */
#define FSL_FEATURE_SOC_ECSPI_COUNT (4)
/* @brief EDMA availability on the SoC. */
#define FSL_FEATURE_SOC_EDMA_COUNT (0)
/* @brief EEPROM availability on the SoC. */
#define FSL_FEATURE_SOC_EEPROM_COUNT (0)
/* @brief EIM availability on the SoC. */
#define FSL_FEATURE_SOC_EIM_COUNT (1)
/* @brief EMC availability on the SoC. */
#define FSL_FEATURE_SOC_EMC_COUNT (0)
/* @brief EMVSIM availability on the SoC. */
#define FSL_FEATURE_SOC_EMVSIM_COUNT (0)
/* @brief ENC availability on the SoC. */
#define FSL_FEATURE_SOC_ENC_COUNT (0)
/* @brief ENET availability on the SoC. */
#define FSL_FEATURE_SOC_ENET_COUNT (2)
/* @brief EPDC availability on the SoC. */
#define FSL_FEATURE_SOC_EPDC_COUNT (0)
/* @brief EPIT availability on the SoC. */
#define FSL_FEATURE_SOC_EPIT_COUNT (2)
/* @brief ESAI availability on the SoC. */
#define FSL_FEATURE_SOC_ESAI_COUNT (1)
/* @brief EWM availability on the SoC. */
#define FSL_FEATURE_SOC_EWM_COUNT (0)
/* @brief FB availability on the SoC. */
#define FSL_FEATURE_SOC_FB_COUNT (0)
/* @brief FGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_FGPIO_COUNT (0)
/* @brief FLASH availability on the SoC. */
#define FSL_FEATURE_SOC_FLASH_COUNT (0)
/* @brief FLEXCAN availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCAN_COUNT (2)
/* @brief FLEXCOMM availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCOMM_COUNT (0)
/* @brief FLEXIO availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXIO_COUNT (0)
/* @brief FLEXRAM availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXRAM_COUNT (0)
/* @brief FLEXSPI availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXSPI_COUNT (0)
/* @brief FMC availability on the SoC. */
#define FSL_FEATURE_SOC_FMC_COUNT (0)
/* @brief FSKDT availability on the SoC. */
#define FSL_FEATURE_SOC_FSKDT_COUNT (0)
/* @brief FSP availability on the SoC. */
#define FSL_FEATURE_SOC_FSP_COUNT (0)
/* @brief FTFA availability on the SoC. */
#define FSL_FEATURE_SOC_FTFA_COUNT (0)
/* @brief FTFE availability on the SoC. */
#define FSL_FEATURE_SOC_FTFE_COUNT (0)
/* @brief FTFL availability on the SoC. */
#define FSL_FEATURE_SOC_FTFL_COUNT (0)
/* @brief FTM availability on the SoC. */
#define FSL_FEATURE_SOC_FTM_COUNT (0)
/* @brief FTMRA availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRA_COUNT (0)
/* @brief FTMRE availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRE_COUNT (0)
/* @brief FTMRH availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRH_COUNT (0)
/* @brief GINT availability on the SoC. */
#define FSL_FEATURE_SOC_GINT_COUNT (0)
/* @brief GPC availability on the SoC. */
#define FSL_FEATURE_SOC_GPC_COUNT (1)
/* @brief GPC_PGC availability on the SoC. */
#define FSL_FEATURE_SOC_GPC_PGC_COUNT (0)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (0)
/* @brief GPMI availability on the SoC. */
#define FSL_FEATURE_SOC_GPMI_COUNT (1)
/* @brief GPT availability on the SoC. */
#define FSL_FEATURE_SOC_GPT_COUNT (2)
/* @brief HSADC availability on the SoC. */
#define FSL_FEATURE_SOC_HSADC_COUNT (0)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (0)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (3)
/* @brief ICS availability on the SoC. */
#define FSL_FEATURE_SOC_ICS_COUNT (0)
/* @brief IEE availability on the SoC. */
#define FSL_FEATURE_SOC_IEE_COUNT (0)
/* @brief IEER availability on the SoC. */
#define FSL_FEATURE_SOC_IEER_COUNT (0)
/* @brief IGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_IGPIO_COUNT (5)
/* @brief II2C availability on the SoC. */
#define FSL_FEATURE_SOC_II2C_COUNT (4)
/* @brief INPUTMUX availability on the SoC. */
#define FSL_FEATURE_SOC_INPUTMUX_COUNT (0)
/* @brief INTMUX availability on the SoC. */
#define FSL_FEATURE_SOC_INTMUX_COUNT (0)
/* @brief IOCON availability on the SoC. */
#define FSL_FEATURE_SOC_IOCON_COUNT (0)
/* @brief IOMUXC availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_COUNT (1)
/* @brief IOMUXC_GPR availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_GPR_COUNT (1)
/* @brief IOMUXC_LPSR availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_LPSR_COUNT (0)
/* @brief IOMUXC_LPSR_GPR availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_LPSR_GPR_COUNT (0)
/* @brief IOMUXC_SNVS availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_SNVS_COUNT (1)
/* @brief IPWM availability on the SoC. */
#define FSL_FEATURE_SOC_IPWM_COUNT (8)
/* @brief IRQ availability on the SoC. */
#define FSL_FEATURE_SOC_IRQ_COUNT (0)
/* @brief IUART availability on the SoC. */
#define FSL_FEATURE_SOC_IUART_COUNT (8)
/* @brief KBI availability on the SoC. */
#define FSL_FEATURE_SOC_KBI_COUNT (0)
/* @brief KPP availability on the SoC. */
#define FSL_FEATURE_SOC_KPP_COUNT (1)
/* @brief L2CACHEC availability on the SoC. */
#define FSL_FEATURE_SOC_L2CACHEC_COUNT (0)
/* @brief LCD availability on the SoC. */
#define FSL_FEATURE_SOC_LCD_COUNT (0)
/* @brief LCDC availability on the SoC. */
#define FSL_FEATURE_SOC_LCDC_COUNT (0)
/* @brief LCDIF availability on the SoC. */
#define FSL_FEATURE_SOC_LCDIF_COUNT (1)
/* @brief LDO availability on the SoC. */
#define FSL_FEATURE_SOC_LDO_COUNT (0)
/* @brief LLWU availability on the SoC. */
#define FSL_FEATURE_SOC_LLWU_COUNT (0)
/* @brief LMEM availability on the SoC. */
#define FSL_FEATURE_SOC_LMEM_COUNT (0)
/* @brief LPADC availability on the SoC. */
#define FSL_FEATURE_SOC_LPADC_COUNT (0)
/* @brief LPCMP availability on the SoC. */
#define FSL_FEATURE_SOC_LPCMP_COUNT (0)
/* @brief LPDAC availability on the SoC. */
#define FSL_FEATURE_SOC_LPDAC_COUNT (0)
/* @brief LPI2C availability on the SoC. */
#define FSL_FEATURE_SOC_LPI2C_COUNT (0)
/* @brief LPIT availability on the SoC. */
#define FSL_FEATURE_SOC_LPIT_COUNT (0)
/* @brief LPSCI availability on the SoC. */
#define FSL_FEATURE_SOC_LPSCI_COUNT (0)
/* @brief LPSPI availability on the SoC. */
#define FSL_FEATURE_SOC_LPSPI_COUNT (0)
/* @brief LPTMR availability on the SoC. */
#define FSL_FEATURE_SOC_LPTMR_COUNT (0)
/* @brief LPTPM availability on the SoC. */
#define FSL_FEATURE_SOC_LPTPM_COUNT (0)
/* @brief LPUART availability on the SoC. */
#define FSL_FEATURE_SOC_LPUART_COUNT (0)
/* @brief LTC availability on the SoC. */
#define FSL_FEATURE_SOC_LTC_COUNT (0)
/* @brief MAILBOX availability on the SoC. */
#define FSL_FEATURE_SOC_MAILBOX_COUNT (0)
/* @brief MC availability on the SoC. */
#define FSL_FEATURE_SOC_MC_COUNT (0)
/* @brief MCG availability on the SoC. */
#define FSL_FEATURE_SOC_MCG_COUNT (0)
/* @brief MCGLITE availability on the SoC. */
#define FSL_FEATURE_SOC_MCGLITE_COUNT (0)
/* @brief MCM availability on the SoC. */
#define FSL_FEATURE_SOC_MCM_COUNT (0)
/* @brief MIPI_CSI2 availability on the SoC. */
#define FSL_FEATURE_SOC_MIPI_CSI2_COUNT (0)
/* @brief MIPI_DSI availability on the SoC. */
#define FSL_FEATURE_SOC_MIPI_DSI_COUNT (0)
/* @brief MIPI_DSI_HOST availability on the SoC. */
#define FSL_FEATURE_SOC_MIPI_DSI_HOST_COUNT (0)
/* @brief MMAU availability on the SoC. */
#define FSL_FEATURE_SOC_MMAU_COUNT (0)
/* @brief MMCAU availability on the SoC. */
#define FSL_FEATURE_SOC_MMCAU_COUNT (0)
/* @brief MMDC availability on the SoC. */
#define FSL_FEATURE_SOC_MMDC_COUNT (1)
/* @brief MMDVSQ availability on the SoC. */
#define FSL_FEATURE_SOC_MMDVSQ_COUNT (0)
/* @brief MPU availability on the SoC. */
#define FSL_FEATURE_SOC_MPU_COUNT (0)
/* @brief MRT availability on the SoC. */
#define FSL_FEATURE_SOC_MRT_COUNT (0)
/* @brief MSCAN availability on the SoC. */
#define FSL_FEATURE_SOC_MSCAN_COUNT (0)
/* @brief MSCM availability on the SoC. */
#define FSL_FEATURE_SOC_MSCM_COUNT (0)
/* @brief MTB availability on the SoC. */
#define FSL_FEATURE_SOC_MTB_COUNT (0)
/* @brief MTBDWT availability on the SoC. */
#define FSL_FEATURE_SOC_MTBDWT_COUNT (0)
/* @brief MU availability on the SoC. */
#define FSL_FEATURE_SOC_MU_COUNT (0)
/* @brief NFC availability on the SoC. */
#define FSL_FEATURE_SOC_NFC_COUNT (0)
/* @brief OCOTP availability on the SoC. */
#define FSL_FEATURE_SOC_OCOTP_COUNT (1)
/* @brief OPAMP availability on the SoC. */
#define FSL_FEATURE_SOC_OPAMP_COUNT (0)
/* @brief OSC availability on the SoC. */
#define FSL_FEATURE_SOC_OSC_COUNT (0)
/* @brief OSC32 availability on the SoC. */
#define FSL_FEATURE_SOC_OSC32_COUNT (0)
/* @brief OTFAD availability on the SoC. */
#define FSL_FEATURE_SOC_OTFAD_COUNT (0)
/* @brief PCC availability on the SoC. */
#define FSL_FEATURE_SOC_PCC_COUNT (0)
/* @brief PCIE_PHY_CMN availability on the SoC. */
#define FSL_FEATURE_SOC_PCIE_PHY_CMN_COUNT (0)
/* @brief PCIE_PHY_TRSV availability on the SoC. */
#define FSL_FEATURE_SOC_PCIE_PHY_TRSV_COUNT (0)
/* @brief PDB availability on the SoC. */
#define FSL_FEATURE_SOC_PDB_COUNT (0)
/* @brief PGA availability on the SoC. */
#define FSL_FEATURE_SOC_PGA_COUNT (0)
/* @brief PINT availability on the SoC. */
#define FSL_FEATURE_SOC_PINT_COUNT (0)
/* @brief PIT availability on the SoC. */
#define FSL_FEATURE_SOC_PIT_COUNT (0)
/* @brief PMC availability on the SoC. */
#define FSL_FEATURE_SOC_PMC_COUNT (0)
/* @brief PMU availability on the SoC. */
#define FSL_FEATURE_SOC_PMU_COUNT (1)
/* @brief PORT availability on the SoC. */
#define FSL_FEATURE_SOC_PORT_COUNT (0)
/* @brief PROP availability on the SoC. */
#define FSL_FEATURE_SOC_PROP_COUNT (0)
/* @brief PWM availability on the SoC. */
#define FSL_FEATURE_SOC_PWM_COUNT (0)
/* @brief PWT availability on the SoC. */
#define FSL_FEATURE_SOC_PWT_COUNT (0)
/* @brief PXP availability on the SoC. */
#define FSL_FEATURE_SOC_PXP_COUNT (1)
/* @brief QDEC availability on the SoC. */
#define FSL_FEATURE_SOC_QDEC_COUNT (0)
/* @brief QuadSPI availability on the SoC. */
#define FSL_FEATURE_SOC_QuadSPI_COUNT (1)
/* @brief RCM availability on the SoC. */
#define FSL_FEATURE_SOC_RCM_COUNT (0)
/* @brief RDC availability on the SoC. */
#define FSL_FEATURE_SOC_RDC_COUNT (0)
/* @brief RDC_SEMAPHORE availability on the SoC. */
#define FSL_FEATURE_SOC_RDC_SEMAPHORE_COUNT (0)
/* @brief RFSYS availability on the SoC. */
#define FSL_FEATURE_SOC_RFSYS_COUNT (0)
/* @brief RFVBAT availability on the SoC. */
#define FSL_FEATURE_SOC_RFVBAT_COUNT (0)
/* @brief RIT availability on the SoC. */
#define FSL_FEATURE_SOC_RIT_COUNT (0)
/* @brief RNG availability on the SoC. */
#define FSL_FEATURE_SOC_RNG_COUNT (1)
/* @brief RNGB availability on the SoC. */
#define FSL_FEATURE_SOC_RNGB_COUNT (0)
/* @brief ROM availability on the SoC. */
#define FSL_FEATURE_SOC_ROM_COUNT (0)
/* @brief ROMC availability on the SoC. */
#define FSL_FEATURE_SOC_ROMC_COUNT (1)
/* @brief RSIM availability on the SoC. */
#define FSL_FEATURE_SOC_RSIM_COUNT (0)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (0)
/* @brief SCG availability on the SoC. */
#define FSL_FEATURE_SOC_SCG_COUNT (0)
/* @brief SCI availability on the SoC. */
#define FSL_FEATURE_SOC_SCI_COUNT (0)
/* @brief SCT availability on the SoC. */
#define FSL_FEATURE_SOC_SCT_COUNT (0)
/* @brief SDHC availability on the SoC. */
#define FSL_FEATURE_SOC_SDHC_COUNT (0)
/* @brief SDIF availability on the SoC. */
#define FSL_FEATURE_SOC_SDIF_COUNT (0)
/* @brief SDIO availability on the SoC. */
#define FSL_FEATURE_SOC_SDIO_COUNT (0)
/* @brief SDMA availability on the SoC. */
#define FSL_FEATURE_SOC_SDMA_COUNT (1)
/* @brief SDMAARM availability on the SoC. */
#define FSL_FEATURE_SOC_SDMAARM_COUNT (0)
/* @brief SDMABP availability on the SoC. */
#define FSL_FEATURE_SOC_SDMABP_COUNT (0)
/* @brief SDMACORE availability on the SoC. */
#define FSL_FEATURE_SOC_SDMACORE_COUNT (0)
/* @brief SDMCORE availability on the SoC. */
#define FSL_FEATURE_SOC_SDMCORE_COUNT (0)
/* @brief SDRAM availability on the SoC. */
#define FSL_FEATURE_SOC_SDRAM_COUNT (0)
/* @brief SEMA4 availability on the SoC. */
#define FSL_FEATURE_SOC_SEMA4_COUNT (0)
/* @brief SEMA42 availability on the SoC. */
#define FSL_FEATURE_SOC_SEMA42_COUNT (0)
/* @brief SHA availability on the SoC. */
#define FSL_FEATURE_SOC_SHA_COUNT (0)
/* @brief SIM availability on the SoC. */
#define FSL_FEATURE_SOC_SIM_COUNT (0)
/* @brief SIMDGO availability on the SoC. */
#define FSL_FEATURE_SOC_SIMDGO_COUNT (0)
/* @brief SJC availability on the SoC. */
#define FSL_FEATURE_SOC_SJC_COUNT (0)
/* @brief SLCD availability on the SoC. */
#define FSL_FEATURE_SOC_SLCD_COUNT (0)
/* @brief SMARTCARD availability on the SoC. */
#define FSL_FEATURE_SOC_SMARTCARD_COUNT (0)
/* @brief SMC availability on the SoC. */
#define FSL_FEATURE_SOC_SMC_COUNT (0)
/* @brief SNVS availability on the SoC. */
#define FSL_FEATURE_SOC_SNVS_COUNT (1)
/* @brief SPBA availability on the SoC. */
#define FSL_FEATURE_SOC_SPBA_COUNT (1)
/* @brief SPDIF availability on the SoC. */
#define FSL_FEATURE_SOC_SPDIF_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (0)
/* @brief SPIFI availability on the SoC. */
#define FSL_FEATURE_SOC_SPIFI_COUNT (0)
/* @brief SPM availability on the SoC. */
#define FSL_FEATURE_SOC_SPM_COUNT (0)
/* @brief SRC availability on the SoC. */
#define FSL_FEATURE_SOC_SRC_COUNT (1)
/* @brief SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCON_COUNT (0)
/* @brief TEMPMON availability on the SoC. */
#define FSL_FEATURE_SOC_TEMPMON_COUNT (1)
/* @brief TMR availability on the SoC. */
#define FSL_FEATURE_SOC_TMR_COUNT (0)
/* @brief TPM availability on the SoC. */
#define FSL_FEATURE_SOC_TPM_COUNT (0)
/* @brief TRGMUX availability on the SoC. */
#define FSL_FEATURE_SOC_TRGMUX_COUNT (0)
/* @brief TRIAMP availability on the SoC. */
#define FSL_FEATURE_SOC_TRIAMP_COUNT (0)
/* @brief TRNG availability on the SoC. */
#define FSL_FEATURE_SOC_TRNG_COUNT (0)
/* @brief TSC availability on the SoC. */
#define FSL_FEATURE_SOC_TSC_COUNT (1)
/* @brief TSI availability on the SoC. */
#define FSL_FEATURE_SOC_TSI_COUNT (0)
/* @brief TSTMR availability on the SoC. */
#define FSL_FEATURE_SOC_TSTMR_COUNT (0)
/* @brief UART availability on the SoC. */
#define FSL_FEATURE_SOC_UART_COUNT (0)
/* @brief USART availability on the SoC. */
#define FSL_FEATURE_SOC_USART_COUNT (0)
/* @brief USB availability on the SoC. */
#define FSL_FEATURE_SOC_USB_COUNT (0)
/* @brief USBHS availability on the SoC. */
#define FSL_FEATURE_SOC_USBHS_COUNT (2)
/* @brief USBDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBDCD_COUNT (0)
/* @brief USBFSH availability on the SoC. */
#define FSL_FEATURE_SOC_USBFSH_COUNT (0)
/* @brief USBHSD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSD_COUNT (0)
/* @brief USBHSDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSDCD_COUNT (0)
/* @brief USBHSH availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSH_COUNT (0)
/* @brief USBNC availability on the SoC. */
#define FSL_FEATURE_SOC_USBNC_COUNT (2)
/* @brief USBPHY availability on the SoC. */
#define FSL_FEATURE_SOC_USBPHY_COUNT (2)
/* @brief USB_HSIC availability on the SoC. */
#define FSL_FEATURE_SOC_USB_HSIC_COUNT (0)
/* @brief USB_OTG availability on the SoC. */
#define FSL_FEATURE_SOC_USB_OTG_COUNT (0)
/* @brief USDHC availability on the SoC. */
#define FSL_FEATURE_SOC_USDHC_COUNT (2)
/* @brief UTICK availability on the SoC. */
#define FSL_FEATURE_SOC_UTICK_COUNT (0)
/* @brief VIU availability on the SoC. */
#define FSL_FEATURE_SOC_VIU_COUNT (0)
/* @brief VREF availability on the SoC. */
#define FSL_FEATURE_SOC_VREF_COUNT (0)
/* @brief VFIFO availability on the SoC. */
#define FSL_FEATURE_SOC_VFIFO_COUNT (0)
/* @brief WDOG availability on the SoC. */
#define FSL_FEATURE_SOC_WDOG_COUNT (3)
/* @brief WKPU availability on the SoC. */
#define FSL_FEATURE_SOC_WKPU_COUNT (0)
/* @brief WWDT availability on the SoC. */
#define FSL_FEATURE_SOC_WWDT_COUNT (0)
/* @brief XBAR availability on the SoC. */
#define FSL_FEATURE_SOC_XBAR_COUNT (0)
/* @brief XBARA availability on the SoC. */
#define FSL_FEATURE_SOC_XBARA_COUNT (0)
/* @brief XBARB availability on the SoC. */
#define FSL_FEATURE_SOC_XBARB_COUNT (0)
/* @brief XCVR availability on the SoC. */
#define FSL_FEATURE_SOC_XCVR_COUNT (0)
/* @brief XRDC availability on the SoC. */
#define FSL_FEATURE_SOC_XRDC_COUNT (0)
/* @brief XTALOSC availability on the SoC. */
#define FSL_FEATURE_SOC_XTALOSC_COUNT (0)
/* @brief XTALOSC24M availability on the SoC. */
#define FSL_FEATURE_SOC_XTALOSC24M_COUNT (1)
/* @brief ZLL availability on the SoC. */
#define FSL_FEATURE_SOC_ZLL_COUNT (0)

/* ADC module features */

/* @brief Remove Hardware Trigger feature. */
#define FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE (1)
/* @brief Remove ALT Clock selection feature. */
#define FSL_FEATURE_ADC_SUPPORT_ALTCLK_REMOVE (1)

/* CACHEC module features */

/* @brief L1 ICACHE line size in byte. */
#define FSL_FEATURE_L1ICACHE_LINESIZE_BYTE (32)
/* @brief L1 DCACHE line size in byte. */
#define FSL_FEATURE_L1DCACHE_LINESIZE_BYTE (64)

/* FLEXCAN module features */

/* @brief Message buffer size */
#define FSL_FEATURE_FLEXCAN_HAS_MESSAGE_BUFFER_MAX_NUMBERn(x) (64)
/* @brief Has doze mode support (register bit field MCR[DOZE]). */
#define FSL_FEATURE_FLEXCAN_HAS_DOZE_MODE_SUPPORT (0)
/* @brief Has a glitch filter on the receive pin (register bit field MCR[WAKSRC]). */
#define FSL_FEATURE_FLEXCAN_HAS_GLITCH_FILTER (1)
/* @brief Has extended interrupt mask and flag register (register IMASK2, IFLAG2). */
#define FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER (1)
/* @brief Has extended bit timing register (register CBT). */
#define FSL_FEATURE_FLEXCAN_HAS_EXTENDED_TIMING_REGISTER (0)
/* @brief Has a receive FIFO DMA feature (register bit field MCR[DMA]). */
#define FSL_FEATURE_FLEXCAN_HAS_RX_FIFO_DMA (0)
/* @brief Remove CAN Engine Clock Source Selection from unsupported part. */
#define FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE (1)
/* @brief Is affected by errata with ID 5641 (Module does not transmit a message that is enabled to be transmitted at a specific moment during the arbitration process). */
#define FSL_FEATURE_FLEXCAN_HAS_ERRATA_5641 (0)
/* @brief Has CAN with Flexible Data rate (CAN FD) protocol. */
#define FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE (0)
/* @brief Has extra MB interrupt or common one. */
#define FSL_FEATURE_FLEXCAN_HAS_EXTRA_MB_INT (0)

/* ECSPI module features */

/* @brief ECSPI Tx FIFO Size. */
#define FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(x) (64)

/* ENET module features */

/* @brief Support Interrupt Coalesce */
#define FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE (1)
/* @brief Queue Size. */
#define FSL_FEATURE_ENET_QUEUE (1)
/* @brief Has AVB Support. */
#define FSL_FEATURE_ENET_HAS_AVB (0)
/* @brief Has Timer Pulse Width control. */
#define FSL_FEATURE_ENET_HAS_TIMER_PWCONTROL (1)
/* @brief Has Extend MDIO Support. */
#define FSL_FEATURE_ENET_HAS_EXTEND_MDIO (1)
/* @brief Has Additional 1588 Timer Channel Interrupt. */
#define FSL_FEATURE_ENET_HAS_ADD_1588_TIMER_CHN_INT (1)

/* ESAI module features */

/* @brief ESAI FIFO Size. */
#define FSL_FEATURE_ESAI_FIFO_SIZEn(x) (128)

/* GPC module features */

/* @brief Has No DVFS0 Change Request. */
#define FSL_FEATURE_GPC_HAS_NO_CNTR_DVFS0CR (1)

/* SAI module features */

/* @brief Receive/transmit FIFO size in item count (register bit fields TCSR[FRDE], TCSR[FRIE], TCSR[FRF], TCR1[TFW], RCSR[FRDE], RCSR[FRIE], RCSR[FRF], RCR1[RFW], registers TFRn, RFRn). */
#define FSL_FEATURE_SAI_FIFO_COUNT (32)
/* @brief Receive/transmit channel number (register bit fields TCR3[TCE], RCR3[RCE], registers TDRn and RDRn). */
#define FSL_FEATURE_SAI_CHANNEL_COUNT (1)
/* @brief Maximum words per frame (register bit fields TCR3[WDFL], TCR4[FRSZ], TMR[TWM], RCR3[WDFL], RCR4[FRSZ], RMR[RWM]). */
#define FSL_FEATURE_SAI_MAX_WORDS_PER_FRAME (32)
/* @brief Has support of combining multiple data channel FIFOs into single channel FIFO (register bit fields TCR3[CFR], TCR4[FCOMB], TFR0[WCP], TFR1[WCP], RCR3[CFR], RCR4[FCOMB], RFR0[RCP], RFR1[RCP]). */
#define FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE (0)
/* @brief Has packing of 8-bit and 16-bit data into each 32-bit FIFO word (register bit fields TCR4[FPACK], RCR4[FPACK]). */
#define FSL_FEATURE_SAI_HAS_FIFO_PACKING (0)
/* @brief Configures when the SAI will continue transmitting after a FIFO error has been detected (register bit fields TCR4[FCONT], RCR4[FCONT]). */
#define FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR (0)
/* @brief Configures if the frame sync is generated internally, a frame sync is only generated when the FIFO warning flag is clear or continuously (register bit fields TCR4[ONDEM], RCR4[ONDEM]). */
#define FSL_FEATURE_SAI_HAS_ON_DEMAND_MODE (0)
/* @brief Simplified bit clock source and asynchronous/synchronous mode selection (register bit fields TCR2[CLKMODE], RCR2[CLKMODE]), in comparison with the exclusively implemented TCR2[SYNC,BCS,BCI,MSEL], RCR2[SYNC,BCS,BCI,MSEL]. */
#define FSL_FEATURE_SAI_HAS_CLOCKING_MODE (0)
/* @brief Has register for configuration of the MCLK divide ratio (register bit fields MDR[FRACT], MDR[DIVIDE]). */
#define FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER (0)
/* @brief Interrupt source number */
#define FSL_FEATURE_SAI_INT_SOURCE_NUM (2)
/* @brief Has register of MCR. */
#define FSL_FEATURE_SAI_HAS_MCR (0)
/* @brief Has register of MDR */
#define FSL_FEATURE_SAI_HAS_MDR (0)

/* MMDC module features */

/* @brief MMDC module has CLK32 clock source gate. */
#define FSL_FEATURE_MMDC_HAS_CLK32_GATE (1)
/* @brief MMDC module has arbitration and reordering control. */
#define FSL_FEATURE_MMDC_HAS_ARB_REO_CONTROL (0)

/* PXP module features */

/* @brief PXP module has dither engine. */
#define FSL_FEATURE_PXP_HAS_DITHER (1)
/* @brief PXP module supports repeat run */
#define FSL_FEATURE_PXP_HAS_EN_REPEAT (0)

/* QSPI module features */

/* @brief QSPI lookup table depth. */
#define FSL_FEATURE_QSPI_LUT_DEPTH (64)
/* @brief QSPI Tx FIFO depth. */
#define FSL_FEATURE_QSPI_TXFIFO_DEPTH (16)
/* @brief QSPI Rx FIFO depth. */
#define FSL_FEATURE_QSPI_RXFIFO_DEPTH (16)
/* @brief QSPI AHB buffer count. */
#define FSL_FEATURE_QSPI_AHB_BUFFER_COUNT (4)
/* @brief QSPI has command usage error flag. */
#define FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR (1)
/* @brief QSPI support parallel mode. */
#define FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE (1)
/* @brief QSPI support dual die. */
#define FSL_FEATURE_QSPI_SUPPORT_DUAL_DIE (1)
/* @brief there is  no SCLKCFG bit in MCR register. */
#define FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL (1)
/* @brief there is no AITEF bit in FR register. */
#define FSL_FEATURE_QSPI_HAS_NO_AITEF (1)
/* @brief  there is no AIBSEF bit in FR register. */
#define FSL_FEATURE_QSPI_HAS_NO_AIBSEF (1)
/* @brief there is no TXDMA and TXWA bit in SR register. */
#define FSL_FEATURE_QSPI_HAS_NO_TXDMA (1)
/* @brief there is no SFACR register. */
#define FSL_FEATURE_QSPI_HAS_NO_SFACR (1)
/* @brief there is no TDH bit in FLSHCR register. */
#define FSL_FEATURE_QSPI_HAS_NO_TDH (1)
/* @brief QSPI AMBA base address. */
#define FSL_FEATURE_QSPI_AMBA_BASE (0x60000000U)
/* @brief QSPI AHB buffer ARDB base address. */
#define FSL_FEATURE_QSPI_ARDB_BASE (0x0C000000U)

/* SDMA module features */

/* @brief SDMA module channel number. */
#define FSL_FEATURE_SDMA_MODULE_CHANNEL (32)
/* @brief SDMA module event number. */
#define FSL_FEATURE_SDMA_EVENT_NUM (48)
/* @brief SDMA ROM memory to memory script start address. */
#define FSL_FEATURE_SDMA_M2M_ADDR (642)
/* @brief SDMA ROM peripheral to memory script start address. */
#define FSL_FEATURE_SDMA_P2M_ADDR (683)
/* @brief SDMA ROM memory to peripheral script start address. */
#define FSL_FEATURE_SDMA_M2P_ADDR (747)
/* @brief SDMA ROM uart to memory script start address. */
#define FSL_FEATURE_SDMA_UART2M_ADDR (817)
/* @brief SDMA ROM peripheral on SPBA to memory script start address. */
#define FSL_FEATURE_SDMA_SHP2M_ADDR (891)
/* @brief SDMA ROM memory to peripheral on SPBA script start address. */
#define FSL_FEATURE_SDMA_M2SHP_ADDR (960)
/* @brief SDMA ROM UART on SPBA to memory script start address. */
#define FSL_FEATURE_SDMA_UARTSH2M_ADDR (1032)
/* @brief SDMA ROM SPDIF to memory script start address. */
#define FSL_FEATURE_SDMA_SPDIF2M_ADDR (1100)
/* @brief SDMA ROM memory to SPDIF script start address. */
#define FSL_FEATURE_SDMA_M2SPDIF_ADDR (1134)

/* SNVS module features */

/* @brief Has Secure Real Time Counter Enabled and Valid (bit field LPCR[SRTC_ENV]). */
#define FSL_FEATURE_SNVS_HAS_SRTC (0)

/* SPBA module features */

/* @brief SPBA module start address. */
#define FSL_FEATURE_SPBA_START (0x02000000U)
/* @brief SPBA module end address. */
#define FSL_FEATURE_SPBA_END (0x0203FFFFU)

/* SRC module features */

/* @brief There is MASK_WDOG3_RST bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_MASK_WDOG3_RST (1)
/* @brief There is MIX_RST_STRCH bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_MIX_RST_STRCH (1)
/* @brief There is DBG_RST_MSK_PG bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_DBG_RST_MSK_PG (1)
/* @brief There is WDOG3_RST_OPTN bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_WDOG3_RST_OPTN (1)
/* @brief There is CORES_DBG_RST bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_CORES_DBG_RST (1)
/* @brief There is MTSR bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_MTSR (0)
/* @brief There is CORE0_DBG_RST bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_CORE0_DBG_RST (1)
/* @brief There is CORE0_RST bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_CORE0_RST (1)
/* @brief There is SWRC bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_SWRC (0)
/* @brief There is EIM_RST bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_EIM_RST (1)
/* @brief There is LUEN bit in SCR register. */
#define FSL_FEATURE_SRC_HAS_SCR_LUEN (0)
/* @brief There is SISR register. */
#define FSL_FEATURE_SRC_HAS_SISR (1)
/* @brief There is RESET_OUT bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_RESET_OUT (0)
/* @brief There is WDOG3_RST_B bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_WDOG3_RST_B (1)
/* @brief There is SW bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_SW (0)
/* @brief There is IPP_USER_RESET_B bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_IPP_USER_RESET_B (1)
/* @brief There is SNVS bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_SNVS (0)
/* @brief There is CSU_RESET_B bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_CSU_RESET_B (1)
/* @brief There is LOCKUP bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_LOCKUP (0)
/* @brief There is POR bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_POR (0)
/* @brief There is IPP_RESET_B bit in SRSR register. */
#define FSL_FEATURE_SRC_HAS_SRSR_IPP_RESET_B (1)

/* IUART module features */

/* @brief UART Transmit/Receive FIFO Size */
#define FSL_FEATURE_IUART_FIFO_SIZEn(x) (32)
/* @brief UART RX MUXed input selected option */
#define FSL_FEATURE_IUART_RXDMUXSEL (1)

/* USBHS module features */

/* @brief EHCI module instance count */
#define FSL_FEATURE_USBHS_EHCI_COUNT (2)
/* @brief Number of endpoints supported */
#define FSL_FEATURE_USBHS_ENDPT_COUNT (8)

/* USDHC module features */

/* @brief Has external DMA support (VEND_SPEC[EXT_DMA_EN]) */
#define FSL_FEATURE_USDHC_HAS_EXT_DMA (1)
/* @brief Has HS400 mode (MIX_CTRL[HS400_MODE]) */
#define FSL_FEATURE_USDHC_HAS_HS400_MODE (0)
/* @brief Has SDR50 support (HOST_CTRL_CAP[SDR50_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR50_MODE (1)
/* @brief Has SDR104 support (HOST_CTRL_CAP[SDR104_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR104_MODE (1)

#endif /* _MCIMX6Y2_FEATURES_H_ */

