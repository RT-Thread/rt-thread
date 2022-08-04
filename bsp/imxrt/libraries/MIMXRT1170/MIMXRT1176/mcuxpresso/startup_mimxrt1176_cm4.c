//*****************************************************************************
// MIMXRT1176_cm4 startup code for use with MCUXpresso IDE
//
// Version : 221121
//*****************************************************************************
//
// Copyright 2016-2021 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************

#if defined (DEBUG)
#pragma GCC push_options
#pragma GCC optimize ("Og")
#endif // (DEBUG)

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define WEAK_AV __attribute__ ((weak, section(".after_vectors")))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
//*****************************************************************************
#include <NXP/crp.h>
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

//*****************************************************************************
// Declaration of external SystemInit function
//*****************************************************************************
#if defined (__USE_CMSIS)
extern void SystemInit(void);
#endif // (__USE_CMSIS)

//*****************************************************************************
// Forward declaration of the core exception handlers.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions.
// If your application is a C++ one, then any interrupt handlers defined
// in C++ files within in your main application will need to have C linkage
// rather than C++ linkage. To do this, make sure that you are using extern "C"
// { .... } around the interrupt handler within your main application code.
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void DMA0_DMA16_IRQHandler(void);
WEAK void DMA1_DMA17_IRQHandler(void);
WEAK void DMA2_DMA18_IRQHandler(void);
WEAK void DMA3_DMA19_IRQHandler(void);
WEAK void DMA4_DMA20_IRQHandler(void);
WEAK void DMA5_DMA21_IRQHandler(void);
WEAK void DMA6_DMA22_IRQHandler(void);
WEAK void DMA7_DMA23_IRQHandler(void);
WEAK void DMA8_DMA24_IRQHandler(void);
WEAK void DMA9_DMA25_IRQHandler(void);
WEAK void DMA10_DMA26_IRQHandler(void);
WEAK void DMA11_DMA27_IRQHandler(void);
WEAK void DMA12_DMA28_IRQHandler(void);
WEAK void DMA13_DMA29_IRQHandler(void);
WEAK void DMA14_DMA30_IRQHandler(void);
WEAK void DMA15_DMA31_IRQHandler(void);
WEAK void DMA_ERROR_IRQHandler(void);
WEAK void Reserved33_IRQHandler(void);
WEAK void Reserved34_IRQHandler(void);
WEAK void CORE_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void LPUART4_IRQHandler(void);
WEAK void LPUART5_IRQHandler(void);
WEAK void LPUART6_IRQHandler(void);
WEAK void LPUART7_IRQHandler(void);
WEAK void LPUART8_IRQHandler(void);
WEAK void LPUART9_IRQHandler(void);
WEAK void LPUART10_IRQHandler(void);
WEAK void LPUART11_IRQHandler(void);
WEAK void LPUART12_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void LPI2C2_IRQHandler(void);
WEAK void LPI2C3_IRQHandler(void);
WEAK void LPI2C4_IRQHandler(void);
WEAK void LPI2C5_IRQHandler(void);
WEAK void LPI2C6_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPSPI2_IRQHandler(void);
WEAK void LPSPI3_IRQHandler(void);
WEAK void LPSPI4_IRQHandler(void);
WEAK void LPSPI5_IRQHandler(void);
WEAK void LPSPI6_IRQHandler(void);
WEAK void CAN1_IRQHandler(void);
WEAK void CAN1_ERROR_IRQHandler(void);
WEAK void CAN2_IRQHandler(void);
WEAK void CAN2_ERROR_IRQHandler(void);
WEAK void CAN3_IRQHandler(void);
WEAK void CAN3_ERROR_IRQHandler(void);
WEAK void Reserved66_IRQHandler(void);
WEAK void KPP_IRQHandler(void);
WEAK void Reserved68_IRQHandler(void);
WEAK void GPR_IRQ_IRQHandler(void);
WEAK void eLCDIF_IRQHandler(void);
WEAK void LCDIFv2_IRQHandler(void);
WEAK void CSI_IRQHandler(void);
WEAK void PXP_IRQHandler(void);
WEAK void MIPI_CSI_IRQHandler(void);
WEAK void MIPI_DSI_IRQHandler(void);
WEAK void GPU2D_IRQHandler(void);
WEAK void GPIO12_Combined_0_15_IRQHandler(void);
WEAK void GPIO12_Combined_16_31_IRQHandler(void);
WEAK void DAC_IRQHandler(void);
WEAK void KEY_MANAGER_IRQHandler(void);
WEAK void WDOG2_IRQHandler(void);
WEAK void SNVS_HP_NON_TZ_IRQHandler(void);
WEAK void SNVS_HP_TZ_IRQHandler(void);
WEAK void SNVS_PULSE_EVENT_IRQHandler(void);
WEAK void CAAM_IRQ0_IRQHandler(void);
WEAK void CAAM_IRQ1_IRQHandler(void);
WEAK void CAAM_IRQ2_IRQHandler(void);
WEAK void CAAM_IRQ3_IRQHandler(void);
WEAK void CAAM_RECORVE_ERRPR_IRQHandler(void);
WEAK void CAAM_RTIC_IRQHandler(void);
WEAK void CDOG_IRQHandler(void);
WEAK void SAI1_IRQHandler(void);
WEAK void SAI2_IRQHandler(void);
WEAK void SAI3_RX_IRQHandler(void);
WEAK void SAI3_TX_IRQHandler(void);
WEAK void SAI4_RX_IRQHandler(void);
WEAK void SAI4_TX_IRQHandler(void);
WEAK void SPDIF_IRQHandler(void);
WEAK void TMPSNS_INT_IRQHandler(void);
WEAK void TMPSNS_LOW_HIGH_IRQHandler(void);
WEAK void TMPSNS_PANIC_IRQHandler(void);
WEAK void LPSR_LP8_BROWNOUT_IRQHandler(void);
WEAK void LPSR_LP0_BROWNOUT_IRQHandler(void);
WEAK void ADC1_IRQHandler(void);
WEAK void ADC2_IRQHandler(void);
WEAK void USBPHY1_IRQHandler(void);
WEAK void USBPHY2_IRQHandler(void);
WEAK void RDC_IRQHandler(void);
WEAK void GPIO13_Combined_0_31_IRQHandler(void);
WEAK void Reserved110_IRQHandler(void);
WEAK void DCIC1_IRQHandler(void);
WEAK void DCIC2_IRQHandler(void);
WEAK void ASRC_IRQHandler(void);
WEAK void FLEXRAM_ECC_IRQHandler(void);
WEAK void GPIO7_8_9_10_11_IRQHandler(void);
WEAK void GPIO1_Combined_0_15_IRQHandler(void);
WEAK void GPIO1_Combined_16_31_IRQHandler(void);
WEAK void GPIO2_Combined_0_15_IRQHandler(void);
WEAK void GPIO2_Combined_16_31_IRQHandler(void);
WEAK void GPIO3_Combined_0_15_IRQHandler(void);
WEAK void GPIO3_Combined_16_31_IRQHandler(void);
WEAK void GPIO4_Combined_0_15_IRQHandler(void);
WEAK void GPIO4_Combined_16_31_IRQHandler(void);
WEAK void GPIO5_Combined_0_15_IRQHandler(void);
WEAK void GPIO5_Combined_16_31_IRQHandler(void);
WEAK void FLEXIO1_IRQHandler(void);
WEAK void FLEXIO2_IRQHandler(void);
WEAK void WDOG1_IRQHandler(void);
WEAK void RTWDOG4_IRQHandler(void);
WEAK void EWM_IRQHandler(void);
WEAK void OCOTP_READ_FUSE_ERROR_IRQHandler(void);
WEAK void OCOTP_READ_DONE_ERROR_IRQHandler(void);
WEAK void GPC_IRQHandler(void);
WEAK void MUB_IRQHandler(void);
WEAK void GPT1_IRQHandler(void);
WEAK void GPT2_IRQHandler(void);
WEAK void GPT3_IRQHandler(void);
WEAK void GPT4_IRQHandler(void);
WEAK void GPT5_IRQHandler(void);
WEAK void GPT6_IRQHandler(void);
WEAK void PWM1_0_IRQHandler(void);
WEAK void PWM1_1_IRQHandler(void);
WEAK void PWM1_2_IRQHandler(void);
WEAK void PWM1_3_IRQHandler(void);
WEAK void PWM1_FAULT_IRQHandler(void);
WEAK void FLEXSPI1_IRQHandler(void);
WEAK void FLEXSPI2_IRQHandler(void);
WEAK void SEMC_IRQHandler(void);
WEAK void USDHC1_IRQHandler(void);
WEAK void USDHC2_IRQHandler(void);
WEAK void USB_OTG2_IRQHandler(void);
WEAK void USB_OTG1_IRQHandler(void);
WEAK void ENET_IRQHandler(void);
WEAK void ENET_1588_Timer_IRQHandler(void);
WEAK void ENET_1G_MAC0_Tx_Rx_1_IRQHandler(void);
WEAK void ENET_1G_MAC0_Tx_Rx_2_IRQHandler(void);
WEAK void ENET_1G_IRQHandler(void);
WEAK void ENET_1G_1588_Timer_IRQHandler(void);
WEAK void XBAR1_IRQ_0_1_IRQHandler(void);
WEAK void XBAR1_IRQ_2_3_IRQHandler(void);
WEAK void ADC_ETC_IRQ0_IRQHandler(void);
WEAK void ADC_ETC_IRQ1_IRQHandler(void);
WEAK void ADC_ETC_IRQ2_IRQHandler(void);
WEAK void ADC_ETC_IRQ3_IRQHandler(void);
WEAK void ADC_ETC_ERROR_IRQ_IRQHandler(void);
WEAK void Reserved166_IRQHandler(void);
WEAK void Reserved167_IRQHandler(void);
WEAK void Reserved168_IRQHandler(void);
WEAK void Reserved169_IRQHandler(void);
WEAK void Reserved170_IRQHandler(void);
WEAK void PIT1_IRQHandler(void);
WEAK void PIT2_IRQHandler(void);
WEAK void ACMP1_IRQHandler(void);
WEAK void ACMP2_IRQHandler(void);
WEAK void ACMP3_IRQHandler(void);
WEAK void ACMP4_IRQHandler(void);
WEAK void Reserved177_IRQHandler(void);
WEAK void Reserved178_IRQHandler(void);
WEAK void Reserved179_IRQHandler(void);
WEAK void Reserved180_IRQHandler(void);
WEAK void ENC1_IRQHandler(void);
WEAK void ENC2_IRQHandler(void);
WEAK void ENC3_IRQHandler(void);
WEAK void ENC4_IRQHandler(void);
WEAK void Reserved185_IRQHandler(void);
WEAK void Reserved186_IRQHandler(void);
WEAK void TMR1_IRQHandler(void);
WEAK void TMR2_IRQHandler(void);
WEAK void TMR3_IRQHandler(void);
WEAK void TMR4_IRQHandler(void);
WEAK void SEMA4_CP0_IRQHandler(void);
WEAK void SEMA4_CP1_IRQHandler(void);
WEAK void PWM2_0_IRQHandler(void);
WEAK void PWM2_1_IRQHandler(void);
WEAK void PWM2_2_IRQHandler(void);
WEAK void PWM2_3_IRQHandler(void);
WEAK void PWM2_FAULT_IRQHandler(void);
WEAK void PWM3_0_IRQHandler(void);
WEAK void PWM3_1_IRQHandler(void);
WEAK void PWM3_2_IRQHandler(void);
WEAK void PWM3_3_IRQHandler(void);
WEAK void PWM3_FAULT_IRQHandler(void);
WEAK void PWM4_0_IRQHandler(void);
WEAK void PWM4_1_IRQHandler(void);
WEAK void PWM4_2_IRQHandler(void);
WEAK void PWM4_3_IRQHandler(void);
WEAK void PWM4_FAULT_IRQHandler(void);
WEAK void Reserved208_IRQHandler(void);
WEAK void Reserved209_IRQHandler(void);
WEAK void Reserved210_IRQHandler(void);
WEAK void Reserved211_IRQHandler(void);
WEAK void Reserved212_IRQHandler(void);
WEAK void Reserved213_IRQHandler(void);
WEAK void Reserved214_IRQHandler(void);
WEAK void Reserved215_IRQHandler(void);
WEAK void PDM_HWVAD_EVENT_IRQHandler(void);
WEAK void PDM_HWVAD_ERROR_IRQHandler(void);
WEAK void PDM_EVENT_IRQHandler(void);
WEAK void PDM_ERROR_IRQHandler(void);
WEAK void EMVSIM1_IRQHandler(void);
WEAK void EMVSIM2_IRQHandler(void);
WEAK void MECC1_INT_IRQHandler(void);
WEAK void MECC1_FATAL_INT_IRQHandler(void);
WEAK void MECC2_INT_IRQHandler(void);
WEAK void MECC2_FATAL_INT_IRQHandler(void);
WEAK void XECC_FLEXSPI1_INT_IRQHandler(void);
WEAK void XECC_FLEXSPI1_FATAL_INT_IRQHandler(void);
WEAK void XECC_FLEXSPI2_INT_IRQHandler(void);
WEAK void XECC_FLEXSPI2_FATAL_INT_IRQHandler(void);
WEAK void XECC_SEMC_INT_IRQHandler(void);
WEAK void XECC_SEMC_FATAL_INT_IRQHandler(void);
WEAK void ENET_QOS_IRQHandler(void);
WEAK void ENET_QOS_PMT_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void DMA0_DMA16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DMA17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_DMA18_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_DMA19_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_DMA20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA5_DMA21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA6_DMA22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA7_DMA23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA8_DMA24_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA9_DMA25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA10_DMA26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA11_DMA27_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA12_DMA28_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA13_DMA29_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA14_DMA30_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA15_DMA31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved33_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved34_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CORE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART9_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART10_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART12_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN3_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved66_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void KPP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved68_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPR_IRQ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void eLCDIF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LCDIFv2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CSI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PXP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MIPI_CSI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MIPI_DSI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPU2D_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO12_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO12_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void KEY_MANAGER_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SNVS_HP_NON_TZ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SNVS_HP_TZ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SNVS_PULSE_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_IRQ0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_IRQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_IRQ2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_IRQ3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_RECORVE_ERRPR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAAM_RTIC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CDOG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI3_RX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI3_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI4_RX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI4_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPDIF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMPSNS_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMPSNS_LOW_HIGH_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMPSNS_PANIC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSR_LP8_BROWNOUT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSR_LP0_BROWNOUT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RDC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO13_Combined_0_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved110_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DCIC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DCIC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ASRC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXRAM_ECC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO7_8_9_10_11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO1_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO1_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO2_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO2_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO3_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO3_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO4_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO4_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO5_Combined_0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO5_Combined_16_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OCOTP_READ_FUSE_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OCOTP_READ_DONE_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MUB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_OTG2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_OTG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1588_Timer_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1G_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1G_1588_Timer_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XBAR1_IRQ_0_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XBAR1_IRQ_2_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_ETC_IRQ0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_ETC_IRQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_ETC_IRQ2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_ETC_IRQ3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_ETC_ERROR_IRQ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved166_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved167_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved168_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved169_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved170_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved177_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved178_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved179_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved180_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved185_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved186_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEMA4_CP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEMA4_CP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved208_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved209_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved210_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved211_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved212_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved213_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved214_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved215_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_HWVAD_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_HWVAD_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EMVSIM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EMVSIM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC1_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC1_FATAL_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC2_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC2_FATAL_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_FLEXSPI1_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_FLEXSPI2_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_SEMC_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XECC_SEMC_FATAL_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_QOS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_QOS_PMT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);

//*****************************************************************************
// External declaration for the pointer to the stack top from the Linker Script
//*****************************************************************************
extern void _vStackTop(void);
//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
// The vector table.
// This relies on the linker script to place at correct location in memory.
//*****************************************************************************

extern void (* const g_pfnVectors[])(void);
extern void * __Vectors __attribute__ ((alias ("g_pfnVectors")));

__attribute__ ((used, section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM4
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    0,                                 // Reserved
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - MIMXRT1176_cm4
    DMA0_DMA16_IRQHandler,               // 16 : DMA channel 0/16 transfer complete
    DMA1_DMA17_IRQHandler,               // 17 : DMA channel 1/17 transfer complete
    DMA2_DMA18_IRQHandler,               // 18 : DMA channel 2/18 transfer complete
    DMA3_DMA19_IRQHandler,               // 19 : DMA channel 3/19 transfer complete
    DMA4_DMA20_IRQHandler,               // 20 : DMA channel 4/20 transfer complete
    DMA5_DMA21_IRQHandler,               // 21 : DMA channel 5/21 transfer complete
    DMA6_DMA22_IRQHandler,               // 22 : DMA channel 6/22 transfer complete
    DMA7_DMA23_IRQHandler,               // 23 : DMA channel 7/23 transfer complete
    DMA8_DMA24_IRQHandler,               // 24 : DMA channel 8/24 transfer complete
    DMA9_DMA25_IRQHandler,               // 25 : DMA channel 9/25 transfer complete
    DMA10_DMA26_IRQHandler,              // 26 : DMA channel 10/26 transfer complete
    DMA11_DMA27_IRQHandler,              // 27 : DMA channel 11/27 transfer complete
    DMA12_DMA28_IRQHandler,              // 28 : DMA channel 12/28 transfer complete
    DMA13_DMA29_IRQHandler,              // 29 : DMA channel 13/29 transfer complete
    DMA14_DMA30_IRQHandler,              // 30 : DMA channel 14/30 transfer complete
    DMA15_DMA31_IRQHandler,              // 31 : DMA channel 15/31 transfer complete
    DMA_ERROR_IRQHandler,                // 32 : DMA error interrupt channels 0-15 / 16-31
    Reserved33_IRQHandler,               // 33 : Reserved interrupt
    Reserved34_IRQHandler,               // 34 : Reserved interrupt
    CORE_IRQHandler,                     // 35 : CorePlatform exception IRQ
    LPUART1_IRQHandler,                  // 36 : LPUART1 TX interrupt and RX interrupt
    LPUART2_IRQHandler,                  // 37 : LPUART2 TX interrupt and RX interrupt
    LPUART3_IRQHandler,                  // 38 : LPUART3 TX interrupt and RX interrupt
    LPUART4_IRQHandler,                  // 39 : LPUART4 TX interrupt and RX interrupt
    LPUART5_IRQHandler,                  // 40 : LPUART5 TX interrupt and RX interrupt
    LPUART6_IRQHandler,                  // 41 : LPUART6 TX interrupt and RX interrupt
    LPUART7_IRQHandler,                  // 42 : LPUART7 TX interrupt and RX interrupt
    LPUART8_IRQHandler,                  // 43 : LPUART8 TX interrupt and RX interrupt
    LPUART9_IRQHandler,                  // 44 : LPUART9 TX interrupt and RX interrupt
    LPUART10_IRQHandler,                 // 45 : LPUART10 TX interrupt and RX interrupt
    LPUART11_IRQHandler,                 // 46 : LPUART11 TX interrupt and RX interrupt
    LPUART12_IRQHandler,                 // 47 : LPUART12 TX interrupt and RX interrupt
    LPI2C1_IRQHandler,                   // 48 : LPI2C1 interrupt
    LPI2C2_IRQHandler,                   // 49 : LPI2C2 interrupt
    LPI2C3_IRQHandler,                   // 50 : LPI2C3 interrupt
    LPI2C4_IRQHandler,                   // 51 : LPI2C4 interrupt
    LPI2C5_IRQHandler,                   // 52 : LPI2C5 interrupt
    LPI2C6_IRQHandler,                   // 53 : LPI2C6 interrupt
    LPSPI1_IRQHandler,                   // 54 : LPSPI1 interrupt request line to the core
    LPSPI2_IRQHandler,                   // 55 : LPSPI2 interrupt request line to the core
    LPSPI3_IRQHandler,                   // 56 : LPSPI3 interrupt request line to the core
    LPSPI4_IRQHandler,                   // 57 : LPSPI4 interrupt request line to the core
    LPSPI5_IRQHandler,                   // 58 : LPSPI5 interrupt request line to the core
    LPSPI6_IRQHandler,                   // 59 : LPSPI6 interrupt request line to the core
    CAN1_IRQHandler,                     // 60 : CAN1 interrupt
    CAN1_ERROR_IRQHandler,               // 61 : CAN1 error interrupt
    CAN2_IRQHandler,                     // 62 : CAN2 interrupt
    CAN2_ERROR_IRQHandler,               // 63 : CAN2 error interrupt
    CAN3_IRQHandler,                     // 64 : CAN3 interrupt
    CAN3_ERROR_IRQHandler,               // 65 : CAN3 erro interrupt
    Reserved66_IRQHandler,               // 66 : Reserved interrupt
    KPP_IRQHandler,                      // 67 : Keypad nterrupt
    Reserved68_IRQHandler,               // 68 : Reserved interrupt
    GPR_IRQ_IRQHandler,                  // 69 : GPR interrupt
    eLCDIF_IRQHandler,                   // 70 : eLCDIF interrupt
    LCDIFv2_IRQHandler,                  // 71 : LCDIFv2 interrupt
    CSI_IRQHandler,                      // 72 : CSI interrupt
    PXP_IRQHandler,                      // 73 : PXP interrupt
    MIPI_CSI_IRQHandler,                 // 74 : MIPI_CSI interrupt
    MIPI_DSI_IRQHandler,                 // 75 : MIPI_DSI interrupt
    GPU2D_IRQHandler,                    // 76 : GPU2D interrupt
    GPIO12_Combined_0_15_IRQHandler,     // 77 : Combined interrupt indication for GPIO12 signal 0 throughout 15
    GPIO12_Combined_16_31_IRQHandler,    // 78 : Combined interrupt indication for GPIO13 signal 16 throughout 31
    DAC_IRQHandler,                      // 79 : DAC interrupt
    KEY_MANAGER_IRQHandler,              // 80 : PUF interrupt
    WDOG2_IRQHandler,                    // 81 : WDOG2 interrupt
    SNVS_HP_NON_TZ_IRQHandler,           // 82 : SRTC Consolidated Interrupt. Non TZ
    SNVS_HP_TZ_IRQHandler,               // 83 : SRTC Security Interrupt. TZ
    SNVS_PULSE_EVENT_IRQHandler,         // 84 : ON-OFF button press shorter than 5 secs (pulse event)
    CAAM_IRQ0_IRQHandler,                // 85 : CAAM interrupt queue for JQ0
    CAAM_IRQ1_IRQHandler,                // 86 : CAAM interrupt queue for JQ1
    CAAM_IRQ2_IRQHandler,                // 87 : CAAM interrupt queue for JQ2
    CAAM_IRQ3_IRQHandler,                // 88 : CAAM interrupt queue for JQ3
    CAAM_RECORVE_ERRPR_IRQHandler,       // 89 : CAAM interrupt for recoverable error
    CAAM_RTIC_IRQHandler,                // 90 : CAAM interrupt for RTIC
    CDOG_IRQHandler,                     // 91 : CDOG interrupt
    SAI1_IRQHandler,                     // 92 : SAI1 interrupt
    SAI2_IRQHandler,                     // 93 : SAI1 interrupt
    SAI3_RX_IRQHandler,                  // 94 : SAI3 interrupt
    SAI3_TX_IRQHandler,                  // 95 : SAI3 interrupt
    SAI4_RX_IRQHandler,                  // 96 : SAI4 interrupt
    SAI4_TX_IRQHandler,                  // 97 : SAI4 interrupt
    SPDIF_IRQHandler,                    // 98 : SPDIF interrupt
    TMPSNS_INT_IRQHandler,               // 99 : TMPSNS interrupt
    TMPSNS_LOW_HIGH_IRQHandler,          // 100: TMPSNS low high interrupt
    TMPSNS_PANIC_IRQHandler,             // 101: TMPSNS panic interrupt
    LPSR_LP8_BROWNOUT_IRQHandler,        // 102: LPSR 1p8 brownout interrupt
    LPSR_LP0_BROWNOUT_IRQHandler,        // 103: LPSR 1p0 brownout interrupt
    ADC1_IRQHandler,                     // 104: ADC1 interrupt
    ADC2_IRQHandler,                     // 105: ADC2 interrupt
    USBPHY1_IRQHandler,                  // 106: USBPHY1 interrupt
    USBPHY2_IRQHandler,                  // 107: USBPHY2 interrupt
    RDC_IRQHandler,                      // 108: RDC interrupt
    GPIO13_Combined_0_31_IRQHandler,     // 109: Combined interrupt indication for GPIO13 signal 0 throughout 31
    Reserved110_IRQHandler,              // 110: Reserved interrupt
    DCIC1_IRQHandler,                    // 111: DCIC1 interrupt
    DCIC2_IRQHandler,                    // 112: DCIC2 interrupt
    ASRC_IRQHandler,                     // 113: ASRC interrupt
    FLEXRAM_ECC_IRQHandler,              // 114: FlexRAM ECC fatal interrupt
    GPIO7_8_9_10_11_IRQHandler,          // 115: GPIO7, GPIO8, GPIO9, GPIO10, GPIO11 interrupt
    GPIO1_Combined_0_15_IRQHandler,      // 116: Combined interrupt indication for GPIO1 signal 0 throughout 15
    GPIO1_Combined_16_31_IRQHandler,     // 117: Combined interrupt indication for GPIO1 signal 16 throughout 31
    GPIO2_Combined_0_15_IRQHandler,      // 118: Combined interrupt indication for GPIO2 signal 0 throughout 15
    GPIO2_Combined_16_31_IRQHandler,     // 119: Combined interrupt indication for GPIO2 signal 16 throughout 31
    GPIO3_Combined_0_15_IRQHandler,      // 120: Combined interrupt indication for GPIO3 signal 0 throughout 15
    GPIO3_Combined_16_31_IRQHandler,     // 121: Combined interrupt indication for GPIO3 signal 16 throughout 31
    GPIO4_Combined_0_15_IRQHandler,      // 122: Combined interrupt indication for GPIO4 signal 0 throughout 15
    GPIO4_Combined_16_31_IRQHandler,     // 123: Combined interrupt indication for GPIO4 signal 16 throughout 31
    GPIO5_Combined_0_15_IRQHandler,      // 124: Combined interrupt indication for GPIO5 signal 0 throughout 15
    GPIO5_Combined_16_31_IRQHandler,     // 125: Combined interrupt indication for GPIO5 signal 16 throughout 31
    FLEXIO1_IRQHandler,                  // 126: FLEXIO1 interrupt
    FLEXIO2_IRQHandler,                  // 127: FLEXIO2 interrupt
    WDOG1_IRQHandler,                    // 128: WDOG1 interrupt
    RTWDOG4_IRQHandler,                  // 129: RTWDOG4 interrupt
    EWM_IRQHandler,                      // 130: EWM interrupt
    OCOTP_READ_FUSE_ERROR_IRQHandler,    // 131: OCOTP read fuse error interrupt
    OCOTP_READ_DONE_ERROR_IRQHandler,    // 132: OCOTP read fuse done interrupt
    GPC_IRQHandler,                      // 133: GPC interrupt
    MUB_IRQHandler,                      // 134: MUB interrupt
    GPT1_IRQHandler,                     // 135: GPT1 interrupt
    GPT2_IRQHandler,                     // 136: GPT2 interrupt
    GPT3_IRQHandler,                     // 137: GPT3 interrupt
    GPT4_IRQHandler,                     // 138: GPT4 interrupt
    GPT5_IRQHandler,                     // 139: GPT5 interrupt
    GPT6_IRQHandler,                     // 140: GPT6 interrupt
    PWM1_0_IRQHandler,                   // 141: PWM1 capture 0, compare 0, or reload 0 interrupt
    PWM1_1_IRQHandler,                   // 142: PWM1 capture 1, compare 1, or reload 0 interrupt
    PWM1_2_IRQHandler,                   // 143: PWM1 capture 2, compare 2, or reload 0 interrupt
    PWM1_3_IRQHandler,                   // 144: PWM1 capture 3, compare 3, or reload 0 interrupt
    PWM1_FAULT_IRQHandler,               // 145: PWM1 fault or reload error interrupt
    FLEXSPI1_IRQHandler,                 // 146: FlexSPI1 interrupt
    FLEXSPI2_IRQHandler,                 // 147: FlexSPI2 interrupt
    SEMC_IRQHandler,                     // 148: SEMC interrupt
    USDHC1_IRQHandler,                   // 149: USDHC1 interrupt
    USDHC2_IRQHandler,                   // 150: USDHC2 interrupt
    USB_OTG2_IRQHandler,                 // 151: USBO2 USB OTG2
    USB_OTG1_IRQHandler,                 // 152: USBO2 USB OTG1
    ENET_IRQHandler,                     // 153: ENET interrupt
    ENET_1588_Timer_IRQHandler,          // 154: ENET_1588_Timer interrupt
    ENET_1G_MAC0_Tx_Rx_1_IRQHandler,     // 155: ENET 1G MAC0 transmit/receive 1
    ENET_1G_MAC0_Tx_Rx_2_IRQHandler,     // 156: ENET 1G MAC0 transmit/receive 2
    ENET_1G_IRQHandler,                  // 157: ENET 1G interrupt
    ENET_1G_1588_Timer_IRQHandler,       // 158: ENET_1G_1588_Timer interrupt
    XBAR1_IRQ_0_1_IRQHandler,            // 159: XBAR1 interrupt
    XBAR1_IRQ_2_3_IRQHandler,            // 160: XBAR1 interrupt
    ADC_ETC_IRQ0_IRQHandler,             // 161: ADCETC IRQ0 interrupt
    ADC_ETC_IRQ1_IRQHandler,             // 162: ADCETC IRQ1 interrupt
    ADC_ETC_IRQ2_IRQHandler,             // 163: ADCETC IRQ2 interrupt
    ADC_ETC_IRQ3_IRQHandler,             // 164: ADCETC IRQ3 interrupt
    ADC_ETC_ERROR_IRQ_IRQHandler,        // 165: ADCETC Error IRQ interrupt
    Reserved166_IRQHandler,              // 166: Reserved interrupt
    Reserved167_IRQHandler,              // 167: Reserved interrupt
    Reserved168_IRQHandler,              // 168: Reserved interrupt
    Reserved169_IRQHandler,              // 169: Reserved interrupt
    Reserved170_IRQHandler,              // 170: Reserved interrupt
    PIT1_IRQHandler,                     // 171: PIT1 interrupt
    PIT2_IRQHandler,                     // 172: PIT2 interrupt
    ACMP1_IRQHandler,                    // 173: ACMP interrupt
    ACMP2_IRQHandler,                    // 174: ACMP interrupt
    ACMP3_IRQHandler,                    // 175: ACMP interrupt
    ACMP4_IRQHandler,                    // 176: ACMP interrupt
    Reserved177_IRQHandler,              // 177: Reserved interrupt
    Reserved178_IRQHandler,              // 178: Reserved interrupt
    Reserved179_IRQHandler,              // 179: Reserved interrupt
    Reserved180_IRQHandler,              // 180: Reserved interrupt
    ENC1_IRQHandler,                     // 181: ENC1 interrupt
    ENC2_IRQHandler,                     // 182: ENC2 interrupt
    ENC3_IRQHandler,                     // 183: ENC3 interrupt
    ENC4_IRQHandler,                     // 184: ENC4 interrupt
    Reserved185_IRQHandler,              // 185: Reserved interrupt
    Reserved186_IRQHandler,              // 186: Reserved interrupt
    TMR1_IRQHandler,                     // 187: TMR1 interrupt
    TMR2_IRQHandler,                     // 188: TMR2 interrupt
    TMR3_IRQHandler,                     // 189: TMR3 interrupt
    TMR4_IRQHandler,                     // 190: TMR4 interrupt
    SEMA4_CP0_IRQHandler,                // 191: SEMA4 CP0 interrupt
    SEMA4_CP1_IRQHandler,                // 192: SEMA4 CP1 interrupt
    PWM2_0_IRQHandler,                   // 193: PWM2 capture 0, compare 0, or reload 0 interrupt
    PWM2_1_IRQHandler,                   // 194: PWM2 capture 1, compare 1, or reload 0 interrupt
    PWM2_2_IRQHandler,                   // 195: PWM2 capture 2, compare 2, or reload 0 interrupt
    PWM2_3_IRQHandler,                   // 196: PWM2 capture 3, compare 3, or reload 0 interrupt
    PWM2_FAULT_IRQHandler,               // 197: PWM2 fault or reload error interrupt
    PWM3_0_IRQHandler,                   // 198: PWM3 capture 0, compare 0, or reload 0 interrupt
    PWM3_1_IRQHandler,                   // 199: PWM3 capture 1, compare 1, or reload 0 interrupt
    PWM3_2_IRQHandler,                   // 200: PWM3 capture 2, compare 2, or reload 0 interrupt
    PWM3_3_IRQHandler,                   // 201: PWM3 capture 3, compare 3, or reload 0 interrupt
    PWM3_FAULT_IRQHandler,               // 202: PWM3 fault or reload error interrupt
    PWM4_0_IRQHandler,                   // 203: PWM4 capture 0, compare 0, or reload 0 interrupt
    PWM4_1_IRQHandler,                   // 204: PWM4 capture 1, compare 1, or reload 0 interrupt
    PWM4_2_IRQHandler,                   // 205: PWM4 capture 2, compare 2, or reload 0 interrupt
    PWM4_3_IRQHandler,                   // 206: PWM4 capture 3, compare 3, or reload 0 interrupt
    PWM4_FAULT_IRQHandler,               // 207: PWM4 fault or reload error interrupt
    Reserved208_IRQHandler,              // 208: Reserved interrupt
    Reserved209_IRQHandler,              // 209: Reserved interrupt
    Reserved210_IRQHandler,              // 210: Reserved interrupt
    Reserved211_IRQHandler,              // 211: Reserved interrupt
    Reserved212_IRQHandler,              // 212: Reserved interrupt
    Reserved213_IRQHandler,              // 213: Reserved interrupt
    Reserved214_IRQHandler,              // 214: Reserved interrupt
    Reserved215_IRQHandler,              // 215: Reserved interrupt
    PDM_HWVAD_EVENT_IRQHandler,          // 216: HWVAD event interrupt
    PDM_HWVAD_ERROR_IRQHandler,          // 217: HWVAD error interrupt
    PDM_EVENT_IRQHandler,                // 218: PDM event interrupt
    PDM_ERROR_IRQHandler,                // 219: PDM error interrupt
    EMVSIM1_IRQHandler,                  // 220: EMVSIM1 interrupt
    EMVSIM2_IRQHandler,                  // 221: EMVSIM2 interrupt
    MECC1_INT_IRQHandler,                // 222: MECC1 int
    MECC1_FATAL_INT_IRQHandler,          // 223: MECC1 fatal int
    MECC2_INT_IRQHandler,                // 224: MECC2 int
    MECC2_FATAL_INT_IRQHandler,          // 225: MECC2 fatal int
    XECC_FLEXSPI1_INT_IRQHandler,        // 226: XECC int
    XECC_FLEXSPI1_FATAL_INT_IRQHandler,  // 227: XECC fatal int
    XECC_FLEXSPI2_INT_IRQHandler,        // 228: XECC int
    XECC_FLEXSPI2_FATAL_INT_IRQHandler,  // 229: XECC fatal int
    XECC_SEMC_INT_IRQHandler,            // 230: XECC int
    XECC_SEMC_FATAL_INT_IRQHandler,      // 231: XECC fatal int
    ENET_QOS_IRQHandler,                 // 232: ENET_QOS interrupt
    ENET_QOS_PMT_IRQHandler,             // 233: ENET_QOS_PMT interrupt
}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors.init_data")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors.init_bss")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((naked, section(".after_vectors.reset")))
void ResetISR(void) {
    // Disable interrupts
    __asm volatile ("cpsid i");
    __asm volatile ("MSR MSP, %0" : : "r" (&_vStackTop) : );

#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();
#else
    // Disable Watchdog
    volatile unsigned int *WDOG1_WCR = (unsigned int *) 0x400B8000;
    *WDOG1_WCR = *WDOG1_WCR & ~(1 << 2);
    volatile unsigned int *WDOG2_WCR = (unsigned int *) 0x400D0000;
    *WDOG2_WCR = *WDOG2_WCR & ~(1 << 2);
    // Write watchdog update key to unlock
    *((volatile unsigned int *)0x40038004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x40038008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *RTWDOG_CS = (unsigned int *) 0x40038000;
    *RTWDOG_CS = (*RTWDOG_CS & ~(1 << 7)) | (1 << 5);

#endif // (__USE_CMSIS)

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }

    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will enable the FPU
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
    //
    // Code to enable the Cortex-M4 FPU only included
    // if appropriate build options have been selected.
    // Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
    //
    // Read CPACR (located at address 0xE000ED88)
    // Set bits 20-23 to enable CP10 and CP11 coprocessors
    // Write back the modified value to the CPACR
    asm volatile ("LDR.W R0, =0xE000ED88\n\t"
                  "LDR R1, [R0]\n\t"
                  "ORR R1, R1, #(0xF << 20)\n\t"
                  "STR R1, [R0]");
#endif // (__VFP_FP__) && !(__SOFTFP__)
#endif // (__USE_CMSIS)

#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will setup the VTOR register

    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }
#endif // (__USE_CMSIS)
#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

    // Reenable interrupts
    __asm volatile ("cpsie i");

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main();
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default core exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
WEAK_AV void NMI_Handler(void)
{ while(1) {}
}

WEAK_AV void HardFault_Handler(void)
{ while(1) {}
}

WEAK_AV void MemManage_Handler(void)
{ while(1) {}
}

WEAK_AV void BusFault_Handler(void)
{ while(1) {}
}

WEAK_AV void UsageFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SVC_Handler(void)
{ while(1) {}
}

WEAK_AV void PendSV_Handler(void)
{ while(1) {}
}

WEAK_AV void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//*****************************************************************************
WEAK_AV void IntDefaultHandler(void)
{ while(1) {}
}

//*****************************************************************************
// Default application exception handlers. Override the ones here by defining
// your own handler routines in your application code. These routines call
// driver exception handlers or IntDefaultHandler() if no driver exception
// handler is included.
//*****************************************************************************
WEAK void DMA0_DMA16_IRQHandler(void)
{   DMA0_DMA16_DriverIRQHandler();
}

WEAK void DMA1_DMA17_IRQHandler(void)
{   DMA1_DMA17_DriverIRQHandler();
}

WEAK void DMA2_DMA18_IRQHandler(void)
{   DMA2_DMA18_DriverIRQHandler();
}

WEAK void DMA3_DMA19_IRQHandler(void)
{   DMA3_DMA19_DriverIRQHandler();
}

WEAK void DMA4_DMA20_IRQHandler(void)
{   DMA4_DMA20_DriverIRQHandler();
}

WEAK void DMA5_DMA21_IRQHandler(void)
{   DMA5_DMA21_DriverIRQHandler();
}

WEAK void DMA6_DMA22_IRQHandler(void)
{   DMA6_DMA22_DriverIRQHandler();
}

WEAK void DMA7_DMA23_IRQHandler(void)
{   DMA7_DMA23_DriverIRQHandler();
}

WEAK void DMA8_DMA24_IRQHandler(void)
{   DMA8_DMA24_DriverIRQHandler();
}

WEAK void DMA9_DMA25_IRQHandler(void)
{   DMA9_DMA25_DriverIRQHandler();
}

WEAK void DMA10_DMA26_IRQHandler(void)
{   DMA10_DMA26_DriverIRQHandler();
}

WEAK void DMA11_DMA27_IRQHandler(void)
{   DMA11_DMA27_DriverIRQHandler();
}

WEAK void DMA12_DMA28_IRQHandler(void)
{   DMA12_DMA28_DriverIRQHandler();
}

WEAK void DMA13_DMA29_IRQHandler(void)
{   DMA13_DMA29_DriverIRQHandler();
}

WEAK void DMA14_DMA30_IRQHandler(void)
{   DMA14_DMA30_DriverIRQHandler();
}

WEAK void DMA15_DMA31_IRQHandler(void)
{   DMA15_DMA31_DriverIRQHandler();
}

WEAK void DMA_ERROR_IRQHandler(void)
{   DMA_ERROR_DriverIRQHandler();
}

WEAK void Reserved33_IRQHandler(void)
{   Reserved33_DriverIRQHandler();
}

WEAK void Reserved34_IRQHandler(void)
{   Reserved34_DriverIRQHandler();
}

WEAK void CORE_IRQHandler(void)
{   CORE_DriverIRQHandler();
}

WEAK void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK void LPUART2_IRQHandler(void)
{   LPUART2_DriverIRQHandler();
}

WEAK void LPUART3_IRQHandler(void)
{   LPUART3_DriverIRQHandler();
}

WEAK void LPUART4_IRQHandler(void)
{   LPUART4_DriverIRQHandler();
}

WEAK void LPUART5_IRQHandler(void)
{   LPUART5_DriverIRQHandler();
}

WEAK void LPUART6_IRQHandler(void)
{   LPUART6_DriverIRQHandler();
}

WEAK void LPUART7_IRQHandler(void)
{   LPUART7_DriverIRQHandler();
}

WEAK void LPUART8_IRQHandler(void)
{   LPUART8_DriverIRQHandler();
}

WEAK void LPUART9_IRQHandler(void)
{   LPUART9_DriverIRQHandler();
}

WEAK void LPUART10_IRQHandler(void)
{   LPUART10_DriverIRQHandler();
}

WEAK void LPUART11_IRQHandler(void)
{   LPUART11_DriverIRQHandler();
}

WEAK void LPUART12_IRQHandler(void)
{   LPUART12_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK void LPI2C2_IRQHandler(void)
{   LPI2C2_DriverIRQHandler();
}

WEAK void LPI2C3_IRQHandler(void)
{   LPI2C3_DriverIRQHandler();
}

WEAK void LPI2C4_IRQHandler(void)
{   LPI2C4_DriverIRQHandler();
}

WEAK void LPI2C5_IRQHandler(void)
{   LPI2C5_DriverIRQHandler();
}

WEAK void LPI2C6_IRQHandler(void)
{   LPI2C6_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK void LPSPI2_IRQHandler(void)
{   LPSPI2_DriverIRQHandler();
}

WEAK void LPSPI3_IRQHandler(void)
{   LPSPI3_DriverIRQHandler();
}

WEAK void LPSPI4_IRQHandler(void)
{   LPSPI4_DriverIRQHandler();
}

WEAK void LPSPI5_IRQHandler(void)
{   LPSPI5_DriverIRQHandler();
}

WEAK void LPSPI6_IRQHandler(void)
{   LPSPI6_DriverIRQHandler();
}

WEAK void CAN1_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_ERROR_IRQHandler(void)
{   CAN1_ERROR_DriverIRQHandler();
}

WEAK void CAN2_IRQHandler(void)
{   CAN2_DriverIRQHandler();
}

WEAK void CAN2_ERROR_IRQHandler(void)
{   CAN2_ERROR_DriverIRQHandler();
}

WEAK void CAN3_IRQHandler(void)
{   CAN3_DriverIRQHandler();
}

WEAK void CAN3_ERROR_IRQHandler(void)
{   CAN3_ERROR_DriverIRQHandler();
}

WEAK void Reserved66_IRQHandler(void)
{   Reserved66_DriverIRQHandler();
}

WEAK void KPP_IRQHandler(void)
{   KPP_DriverIRQHandler();
}

WEAK void Reserved68_IRQHandler(void)
{   Reserved68_DriverIRQHandler();
}

WEAK void GPR_IRQ_IRQHandler(void)
{   GPR_IRQ_DriverIRQHandler();
}

WEAK void eLCDIF_IRQHandler(void)
{   eLCDIF_DriverIRQHandler();
}

WEAK void LCDIFv2_IRQHandler(void)
{   LCDIFv2_DriverIRQHandler();
}

WEAK void CSI_IRQHandler(void)
{   CSI_DriverIRQHandler();
}

WEAK void PXP_IRQHandler(void)
{   PXP_DriverIRQHandler();
}

WEAK void MIPI_CSI_IRQHandler(void)
{   MIPI_CSI_DriverIRQHandler();
}

WEAK void MIPI_DSI_IRQHandler(void)
{   MIPI_DSI_DriverIRQHandler();
}

WEAK void GPU2D_IRQHandler(void)
{   GPU2D_DriverIRQHandler();
}

WEAK void GPIO12_Combined_0_15_IRQHandler(void)
{   GPIO12_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO12_Combined_16_31_IRQHandler(void)
{   GPIO12_Combined_16_31_DriverIRQHandler();
}

WEAK void DAC_IRQHandler(void)
{   DAC_DriverIRQHandler();
}

WEAK void KEY_MANAGER_IRQHandler(void)
{   KEY_MANAGER_DriverIRQHandler();
}

WEAK void WDOG2_IRQHandler(void)
{   WDOG2_DriverIRQHandler();
}

WEAK void SNVS_HP_NON_TZ_IRQHandler(void)
{   SNVS_HP_NON_TZ_DriverIRQHandler();
}

WEAK void SNVS_HP_TZ_IRQHandler(void)
{   SNVS_HP_TZ_DriverIRQHandler();
}

WEAK void SNVS_PULSE_EVENT_IRQHandler(void)
{   SNVS_PULSE_EVENT_DriverIRQHandler();
}

WEAK void CAAM_IRQ0_IRQHandler(void)
{   CAAM_IRQ0_DriverIRQHandler();
}

WEAK void CAAM_IRQ1_IRQHandler(void)
{   CAAM_IRQ1_DriverIRQHandler();
}

WEAK void CAAM_IRQ2_IRQHandler(void)
{   CAAM_IRQ2_DriverIRQHandler();
}

WEAK void CAAM_IRQ3_IRQHandler(void)
{   CAAM_IRQ3_DriverIRQHandler();
}

WEAK void CAAM_RECORVE_ERRPR_IRQHandler(void)
{   CAAM_RECORVE_ERRPR_DriverIRQHandler();
}

WEAK void CAAM_RTIC_IRQHandler(void)
{   CAAM_RTIC_DriverIRQHandler();
}

WEAK void CDOG_IRQHandler(void)
{   CDOG_DriverIRQHandler();
}

WEAK void SAI1_IRQHandler(void)
{   SAI1_DriverIRQHandler();
}

WEAK void SAI2_IRQHandler(void)
{   SAI2_DriverIRQHandler();
}

WEAK void SAI3_RX_IRQHandler(void)
{   SAI3_RX_DriverIRQHandler();
}

WEAK void SAI3_TX_IRQHandler(void)
{   SAI3_TX_DriverIRQHandler();
}

WEAK void SAI4_RX_IRQHandler(void)
{   SAI4_RX_DriverIRQHandler();
}

WEAK void SAI4_TX_IRQHandler(void)
{   SAI4_TX_DriverIRQHandler();
}

WEAK void SPDIF_IRQHandler(void)
{   SPDIF_DriverIRQHandler();
}

WEAK void TMPSNS_INT_IRQHandler(void)
{   TMPSNS_INT_DriverIRQHandler();
}

WEAK void TMPSNS_LOW_HIGH_IRQHandler(void)
{   TMPSNS_LOW_HIGH_DriverIRQHandler();
}

WEAK void TMPSNS_PANIC_IRQHandler(void)
{   TMPSNS_PANIC_DriverIRQHandler();
}

WEAK void LPSR_LP8_BROWNOUT_IRQHandler(void)
{   LPSR_LP8_BROWNOUT_DriverIRQHandler();
}

WEAK void LPSR_LP0_BROWNOUT_IRQHandler(void)
{   LPSR_LP0_BROWNOUT_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)
{   ADC1_DriverIRQHandler();
}

WEAK void ADC2_IRQHandler(void)
{   ADC2_DriverIRQHandler();
}

WEAK void USBPHY1_IRQHandler(void)
{   USBPHY1_DriverIRQHandler();
}

WEAK void USBPHY2_IRQHandler(void)
{   USBPHY2_DriverIRQHandler();
}

WEAK void RDC_IRQHandler(void)
{   RDC_DriverIRQHandler();
}

WEAK void GPIO13_Combined_0_31_IRQHandler(void)
{   GPIO13_Combined_0_31_DriverIRQHandler();
}

WEAK void Reserved110_IRQHandler(void)
{   Reserved110_DriverIRQHandler();
}

WEAK void DCIC1_IRQHandler(void)
{   DCIC1_DriverIRQHandler();
}

WEAK void DCIC2_IRQHandler(void)
{   DCIC2_DriverIRQHandler();
}

WEAK void ASRC_IRQHandler(void)
{   ASRC_DriverIRQHandler();
}

WEAK void FLEXRAM_ECC_IRQHandler(void)
{   FLEXRAM_ECC_DriverIRQHandler();
}

WEAK void GPIO7_8_9_10_11_IRQHandler(void)
{   GPIO7_8_9_10_11_DriverIRQHandler();
}

WEAK void GPIO1_Combined_0_15_IRQHandler(void)
{   GPIO1_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO1_Combined_16_31_IRQHandler(void)
{   GPIO1_Combined_16_31_DriverIRQHandler();
}

WEAK void GPIO2_Combined_0_15_IRQHandler(void)
{   GPIO2_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO2_Combined_16_31_IRQHandler(void)
{   GPIO2_Combined_16_31_DriverIRQHandler();
}

WEAK void GPIO3_Combined_0_15_IRQHandler(void)
{   GPIO3_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO3_Combined_16_31_IRQHandler(void)
{   GPIO3_Combined_16_31_DriverIRQHandler();
}

WEAK void GPIO4_Combined_0_15_IRQHandler(void)
{   GPIO4_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO4_Combined_16_31_IRQHandler(void)
{   GPIO4_Combined_16_31_DriverIRQHandler();
}

WEAK void GPIO5_Combined_0_15_IRQHandler(void)
{   GPIO5_Combined_0_15_DriverIRQHandler();
}

WEAK void GPIO5_Combined_16_31_IRQHandler(void)
{   GPIO5_Combined_16_31_DriverIRQHandler();
}

WEAK void FLEXIO1_IRQHandler(void)
{   FLEXIO1_DriverIRQHandler();
}

WEAK void FLEXIO2_IRQHandler(void)
{   FLEXIO2_DriverIRQHandler();
}

WEAK void WDOG1_IRQHandler(void)
{   WDOG1_DriverIRQHandler();
}

WEAK void RTWDOG4_IRQHandler(void)
{   RTWDOG4_DriverIRQHandler();
}

WEAK void EWM_IRQHandler(void)
{   EWM_DriverIRQHandler();
}

WEAK void OCOTP_READ_FUSE_ERROR_IRQHandler(void)
{   OCOTP_READ_FUSE_ERROR_DriverIRQHandler();
}

WEAK void OCOTP_READ_DONE_ERROR_IRQHandler(void)
{   OCOTP_READ_DONE_ERROR_DriverIRQHandler();
}

WEAK void GPC_IRQHandler(void)
{   GPC_DriverIRQHandler();
}

WEAK void MUB_IRQHandler(void)
{   MUB_DriverIRQHandler();
}

WEAK void GPT1_IRQHandler(void)
{   GPT1_DriverIRQHandler();
}

WEAK void GPT2_IRQHandler(void)
{   GPT2_DriverIRQHandler();
}

WEAK void GPT3_IRQHandler(void)
{   GPT3_DriverIRQHandler();
}

WEAK void GPT4_IRQHandler(void)
{   GPT4_DriverIRQHandler();
}

WEAK void GPT5_IRQHandler(void)
{   GPT5_DriverIRQHandler();
}

WEAK void GPT6_IRQHandler(void)
{   GPT6_DriverIRQHandler();
}

WEAK void PWM1_0_IRQHandler(void)
{   PWM1_0_DriverIRQHandler();
}

WEAK void PWM1_1_IRQHandler(void)
{   PWM1_1_DriverIRQHandler();
}

WEAK void PWM1_2_IRQHandler(void)
{   PWM1_2_DriverIRQHandler();
}

WEAK void PWM1_3_IRQHandler(void)
{   PWM1_3_DriverIRQHandler();
}

WEAK void PWM1_FAULT_IRQHandler(void)
{   PWM1_FAULT_DriverIRQHandler();
}

WEAK void FLEXSPI1_IRQHandler(void)
{   FLEXSPI1_DriverIRQHandler();
}

WEAK void FLEXSPI2_IRQHandler(void)
{   FLEXSPI2_DriverIRQHandler();
}

WEAK void SEMC_IRQHandler(void)
{   SEMC_DriverIRQHandler();
}

WEAK void USDHC1_IRQHandler(void)
{   USDHC1_DriverIRQHandler();
}

WEAK void USDHC2_IRQHandler(void)
{   USDHC2_DriverIRQHandler();
}

WEAK void USB_OTG2_IRQHandler(void)
{   USB_OTG2_DriverIRQHandler();
}

WEAK void USB_OTG1_IRQHandler(void)
{   USB_OTG1_DriverIRQHandler();
}

WEAK void ENET_IRQHandler(void)
{   ENET_DriverIRQHandler();
}

WEAK void ENET_1588_Timer_IRQHandler(void)
{   ENET_1588_Timer_DriverIRQHandler();
}

WEAK void ENET_1G_MAC0_Tx_Rx_1_IRQHandler(void)
{   ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler();
}

WEAK void ENET_1G_MAC0_Tx_Rx_2_IRQHandler(void)
{   ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler();
}

WEAK void ENET_1G_IRQHandler(void)
{   ENET_1G_DriverIRQHandler();
}

WEAK void ENET_1G_1588_Timer_IRQHandler(void)
{   ENET_1G_1588_Timer_DriverIRQHandler();
}

WEAK void XBAR1_IRQ_0_1_IRQHandler(void)
{   XBAR1_IRQ_0_1_DriverIRQHandler();
}

WEAK void XBAR1_IRQ_2_3_IRQHandler(void)
{   XBAR1_IRQ_2_3_DriverIRQHandler();
}

WEAK void ADC_ETC_IRQ0_IRQHandler(void)
{   ADC_ETC_IRQ0_DriverIRQHandler();
}

WEAK void ADC_ETC_IRQ1_IRQHandler(void)
{   ADC_ETC_IRQ1_DriverIRQHandler();
}

WEAK void ADC_ETC_IRQ2_IRQHandler(void)
{   ADC_ETC_IRQ2_DriverIRQHandler();
}

WEAK void ADC_ETC_IRQ3_IRQHandler(void)
{   ADC_ETC_IRQ3_DriverIRQHandler();
}

WEAK void ADC_ETC_ERROR_IRQ_IRQHandler(void)
{   ADC_ETC_ERROR_IRQ_DriverIRQHandler();
}

WEAK void Reserved166_IRQHandler(void)
{   Reserved166_DriverIRQHandler();
}

WEAK void Reserved167_IRQHandler(void)
{   Reserved167_DriverIRQHandler();
}

WEAK void Reserved168_IRQHandler(void)
{   Reserved168_DriverIRQHandler();
}

WEAK void Reserved169_IRQHandler(void)
{   Reserved169_DriverIRQHandler();
}

WEAK void Reserved170_IRQHandler(void)
{   Reserved170_DriverIRQHandler();
}

WEAK void PIT1_IRQHandler(void)
{   PIT1_DriverIRQHandler();
}

WEAK void PIT2_IRQHandler(void)
{   PIT2_DriverIRQHandler();
}

WEAK void ACMP1_IRQHandler(void)
{   ACMP1_DriverIRQHandler();
}

WEAK void ACMP2_IRQHandler(void)
{   ACMP2_DriverIRQHandler();
}

WEAK void ACMP3_IRQHandler(void)
{   ACMP3_DriverIRQHandler();
}

WEAK void ACMP4_IRQHandler(void)
{   ACMP4_DriverIRQHandler();
}

WEAK void Reserved177_IRQHandler(void)
{   Reserved177_DriverIRQHandler();
}

WEAK void Reserved178_IRQHandler(void)
{   Reserved178_DriverIRQHandler();
}

WEAK void Reserved179_IRQHandler(void)
{   Reserved179_DriverIRQHandler();
}

WEAK void Reserved180_IRQHandler(void)
{   Reserved180_DriverIRQHandler();
}

WEAK void ENC1_IRQHandler(void)
{   ENC1_DriverIRQHandler();
}

WEAK void ENC2_IRQHandler(void)
{   ENC2_DriverIRQHandler();
}

WEAK void ENC3_IRQHandler(void)
{   ENC3_DriverIRQHandler();
}

WEAK void ENC4_IRQHandler(void)
{   ENC4_DriverIRQHandler();
}

WEAK void Reserved185_IRQHandler(void)
{   Reserved185_DriverIRQHandler();
}

WEAK void Reserved186_IRQHandler(void)
{   Reserved186_DriverIRQHandler();
}

WEAK void TMR1_IRQHandler(void)
{   TMR1_DriverIRQHandler();
}

WEAK void TMR2_IRQHandler(void)
{   TMR2_DriverIRQHandler();
}

WEAK void TMR3_IRQHandler(void)
{   TMR3_DriverIRQHandler();
}

WEAK void TMR4_IRQHandler(void)
{   TMR4_DriverIRQHandler();
}

WEAK void SEMA4_CP0_IRQHandler(void)
{   SEMA4_CP0_DriverIRQHandler();
}

WEAK void SEMA4_CP1_IRQHandler(void)
{   SEMA4_CP1_DriverIRQHandler();
}

WEAK void PWM2_0_IRQHandler(void)
{   PWM2_0_DriverIRQHandler();
}

WEAK void PWM2_1_IRQHandler(void)
{   PWM2_1_DriverIRQHandler();
}

WEAK void PWM2_2_IRQHandler(void)
{   PWM2_2_DriverIRQHandler();
}

WEAK void PWM2_3_IRQHandler(void)
{   PWM2_3_DriverIRQHandler();
}

WEAK void PWM2_FAULT_IRQHandler(void)
{   PWM2_FAULT_DriverIRQHandler();
}

WEAK void PWM3_0_IRQHandler(void)
{   PWM3_0_DriverIRQHandler();
}

WEAK void PWM3_1_IRQHandler(void)
{   PWM3_1_DriverIRQHandler();
}

WEAK void PWM3_2_IRQHandler(void)
{   PWM3_2_DriverIRQHandler();
}

WEAK void PWM3_3_IRQHandler(void)
{   PWM3_3_DriverIRQHandler();
}

WEAK void PWM3_FAULT_IRQHandler(void)
{   PWM3_FAULT_DriverIRQHandler();
}

WEAK void PWM4_0_IRQHandler(void)
{   PWM4_0_DriverIRQHandler();
}

WEAK void PWM4_1_IRQHandler(void)
{   PWM4_1_DriverIRQHandler();
}

WEAK void PWM4_2_IRQHandler(void)
{   PWM4_2_DriverIRQHandler();
}

WEAK void PWM4_3_IRQHandler(void)
{   PWM4_3_DriverIRQHandler();
}

WEAK void PWM4_FAULT_IRQHandler(void)
{   PWM4_FAULT_DriverIRQHandler();
}

WEAK void Reserved208_IRQHandler(void)
{   Reserved208_DriverIRQHandler();
}

WEAK void Reserved209_IRQHandler(void)
{   Reserved209_DriverIRQHandler();
}

WEAK void Reserved210_IRQHandler(void)
{   Reserved210_DriverIRQHandler();
}

WEAK void Reserved211_IRQHandler(void)
{   Reserved211_DriverIRQHandler();
}

WEAK void Reserved212_IRQHandler(void)
{   Reserved212_DriverIRQHandler();
}

WEAK void Reserved213_IRQHandler(void)
{   Reserved213_DriverIRQHandler();
}

WEAK void Reserved214_IRQHandler(void)
{   Reserved214_DriverIRQHandler();
}

WEAK void Reserved215_IRQHandler(void)
{   Reserved215_DriverIRQHandler();
}

WEAK void PDM_HWVAD_EVENT_IRQHandler(void)
{   PDM_HWVAD_EVENT_DriverIRQHandler();
}

WEAK void PDM_HWVAD_ERROR_IRQHandler(void)
{   PDM_HWVAD_ERROR_DriverIRQHandler();
}

WEAK void PDM_EVENT_IRQHandler(void)
{   PDM_EVENT_DriverIRQHandler();
}

WEAK void PDM_ERROR_IRQHandler(void)
{   PDM_ERROR_DriverIRQHandler();
}

WEAK void EMVSIM1_IRQHandler(void)
{   EMVSIM1_DriverIRQHandler();
}

WEAK void EMVSIM2_IRQHandler(void)
{   EMVSIM2_DriverIRQHandler();
}

WEAK void MECC1_INT_IRQHandler(void)
{   MECC1_INT_DriverIRQHandler();
}

WEAK void MECC1_FATAL_INT_IRQHandler(void)
{   MECC1_FATAL_INT_DriverIRQHandler();
}

WEAK void MECC2_INT_IRQHandler(void)
{   MECC2_INT_DriverIRQHandler();
}

WEAK void MECC2_FATAL_INT_IRQHandler(void)
{   MECC2_FATAL_INT_DriverIRQHandler();
}

WEAK void XECC_FLEXSPI1_INT_IRQHandler(void)
{   XECC_FLEXSPI1_INT_DriverIRQHandler();
}

WEAK void XECC_FLEXSPI1_FATAL_INT_IRQHandler(void)
{   XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler();
}

WEAK void XECC_FLEXSPI2_INT_IRQHandler(void)
{   XECC_FLEXSPI2_INT_DriverIRQHandler();
}

WEAK void XECC_FLEXSPI2_FATAL_INT_IRQHandler(void)
{   XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler();
}

WEAK void XECC_SEMC_INT_IRQHandler(void)
{   XECC_SEMC_INT_DriverIRQHandler();
}

WEAK void XECC_SEMC_FATAL_INT_IRQHandler(void)
{   XECC_SEMC_FATAL_INT_DriverIRQHandler();
}

WEAK void ENET_QOS_IRQHandler(void)
{   ENET_QOS_DriverIRQHandler();
}

WEAK void ENET_QOS_PMT_IRQHandler(void)
{   ENET_QOS_PMT_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
