/**************************************************************************//**
 * @file     clk_reg.h
 * @brief    CLK register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CLK_REG_H__
#define __CLK_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

typedef struct
{
    /**
     * @var PLL_T::CTL0
     * Offset: 0x0  PLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var PLL_T::CTL1
     * Offset: 0x4  PLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var PLL_T::CTL2
     * Offset: 0x8  PLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var PLL_T::RESERVE
     * Offset: 0xC
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t CTL0;              /*!< [0x0000] PLL Control Register 0 of PLL Channel n.(Write Protect)          */
    __IO uint32_t CTL1;              /*!< [0x0004] PLL Control Register 1 of PLL Channel n.(Write Protect)          */
    __IO uint32_t CTL2;              /*!< [0x0008] PLL Control Register 2 of PLL Channel n.(Write Protect)          */
    __IO uint32_t RESERVE;           /*!< [0x000c] Reserved                                                         */

} PLL_T;

/**
    @addtogroup CLK System Clock Controller(CLK)
    Memory Mapped Structure for CLK Controller
@{ */

typedef struct
{


    /**
     * @var CLK_T::PWRCTL
     * Offset: 0x00  System Power-down Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTEN     |HXT Enable Bit (Write Protect)
     * |        |          |0 = 24 MHz external high speed crystal (HXT) Disabled.
     * |        |          |1 = 24 MHz external high speed crystal (HXT) Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: HXT cannot be disabled and HXTEN will always read as 1 if HCLK clock source is selected from HXT or PLL (clock source from HXT).
     * |[1]     |LXTEN     |LXT Enable Bit (Write Protect)
     * |        |          |0 = 32.768 kHz external low speed crystal (external LXT) Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal (external LXT) Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: LXT cannot be disabled and LXTEN will always read as 1 if HCLK clock source is selected from LXT when the LXT clock source is selected as external LXT by setting C32KS(RTC_LXTCTL[6]) to 1.
     * |[2]     |HIRCEN    |HIRC Enable Bit (Write Protect)
     * |        |          |The HCLK default clock source is from HIRC and this bit default value is 1.
     * |        |          |0 = 12 MHz internal high speed RC oscillator (HIRC) Disabled.
     * |        |          |1 = 12 MHz internal high speed RC oscillator (HIRC) Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: HIRC cannot be disabled and HIRCEN will always read as 1 if HXTFQIEN or is set.
     * |[3]     |LIRCEN    |LIRC Enable Bit (Write Protect)
     * |        |          |0 = 32 kHz internal low speed RC oscillator (LIRC) Disabled.
     * |        |          |1 = 32 kHz internal low speed RC oscillator (LIRC) Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[10]    |HXTDS     |HXT Drive Current Strength (Write Protect)
     * |        |          |0 = Lower power consumption requirement for 2.5V~3.3V I/O power application.
     * |        |          |1 = higher noise immunity requirement for 2.5V~3.3V I/O power application.(default)
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[11]    |SYSPLLAPD |SYSPLL Auto Power Down Option when CA35 & RTP-M4 are Power Down (Write Protect)
     * |        |          |0 = When CA35 and RTP-M4 are both in WFI, the PD pin of SYS-PLL is the same as CLK_PLL2CTL1[0].
     * |        |          |1 = When CA35 and RTP-M4 are both in WFI, set the PD pin of SYS-PLL to high automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 and RTP-M4 are not both in Power-down mode
     * |        |          |If one of RTP-M4 and CA35 is not in Power-down mode, the PLL PD pin status is the controlled by CLK_PLL1CTL1[0].
     * |[12]    |CAPLLAPD  |CAPLL Auto Power Down Option when CA35 is Power Gating (Write Protect)
     * |        |          |0 = When CA35 core power is not ready, the PD pin of CA-PLL is the same as CLK_PLL0CTL1[0].
     * |        |          |1 = When CA35 core power is not ready, set the PD pin of CA-PLL to high automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 core power is not ready
     * |        |          |If CA35 core power is ready, the PLL PD pin status is the controlled by CLK_PLL0CTL1[0].
     * |[13]    |DDRPLLAPD |DDRPLL Auto Power Down Option when CA35 is Power Gating (Write Protect)
     * |        |          |0 = When CA35 core power is not ready, the PD pin of DDR-PLL is the same as CLK_PLL2CTL1[0].
     * |        |          |1 = When CA35 core power is not ready, set the PD pin of DDR-PLL to high automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 core power is not ready
     * |        |          |If CA35 core power is ready, the PLL PD pin status is the controlled by CLK_PLL2CTL1[0].
     * |[14]    |HXTAOFF   |HXT Auto Off Option when CA35 is Power Gating (Write Protect)
     * |        |          |0 = When CA35 core power is not ready, the HXT enable bit is the same as CLK_PWRCTL[0].
     * |        |          |1 = When CA35 core power is not ready, switch the HXT enable bit to low automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 core power is not ready
     * |        |          |If CA35 core power is ready, the HXT enable bit is the controlled by CLK_PWRCTL[0].
     * |[15]    |HIRCAOFF  |HIRC Auto Off Option when CA35 is Power Gating (Write Protect)
     * |        |          |0 = When CA35 core power is not ready, the HIRC enable bit is the same as CLK_PWRCTL[2].
     * |        |          |1 = When CA35 core power is not ready, switch the HIRC enable bit to low automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 core power is not ready
     * |        |          |If CA35 core power is ready, the HIRC enable bit is the controlled by CLK_PWRCTL[2].
     * |[17:16] |LXTSTBS   |LXT Stable Count Select (Write Protect)
     * |        |          |00 = LXT stable count = 16384 clocks.
     * |        |          |01 = LXT stable count = 65536 clocks.
     * |        |          |10 = LXT stable count = 131072 clocks.
     * |        |          |11 = LXT stable count = 327680 clocks.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[21]    |GICAOFF   |GIC CLK Auto Off Option when CA35 is Power Gating (Write Protect)
     * |        |          |0 = When CA35 core power is not ready, the GIC CLK will not be gated.
     * |        |          |1 = When CA35 core power is not ready, the GIC CLK will be gated.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 core power is not ready
     * |        |          |If CA35 core power is ready, the HIRC enable bit is the controlled by CLK_PWRCTL[2].
     * |[22]    |HXTAPD    |HXT Auto Off Option when CA35 is Power Down (Write Protect)
     * |        |          |0 = When CA35 cores are in WFI, the HXT enable bit is the same as CLK_PWRCTL[0].
     * |        |          |1 = When CA35 cores are in WFI, switch the HXT enable bit to low automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 cores are in the WFI
     * |        |          |If CA35 cores are not in WFI, the HXT enable bit is the controlled by CLK_PWRCTL[0].
     * |[23]    |HIRCAPD   |HIRC Auto Off Option when CA35 is Power Down (Write Protect)
     * |        |          |0 = When CA35 cores are in WFI, the HIRC enable bit is the same as CLK_PWRCTL[2].
     * |        |          |1 = When CA35 cores are in WFI, switch the HIRC enable bit to low automatically.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: This bit only works when the CA35 cores are in the WFI
     * |        |          |If CA35 cores are not in WFI, the HIRC enable bit is the controlled by CLK_PWRCTL[2].
     * @var CLK_T::SYSCLK0
     * Offset: 0x04  AXI and AHB Device Clock Enable Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |RTPEN     |CPU RTP CortexM4 AHB Clock Enable Bit (Write Protect)
     * |        |          |0 = Cortex M4 AHB clock Disabled.
     * |        |          |1 = Cortex M4 AHB clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[2]     |TAHBCKEN  |TSI AHB HCLK Clock Enable Bit (Write Protect)
     * |        |          |0 = TSI AHB HCLK Disabled.
     * |        |          |1 = TSI AHB HCLK Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[3]     |LVRDBEN   |LVR Debounce Clock Enable Bit (Write Protect)
     * |        |          |0 = LVR Debounce clock Disabled.
     * |        |          |1 = LVR Debounce clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[4]     |DDR0CKEN  |DDR Port0 Clock Enable Bit (Write Protect)
     * |        |          |0 = DDR Port0 peripheral clock Disabled.
     * |        |          |1 = DDR Port0 peripheral clock Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: The peripheral clock of DDR Port 1, DDR Port 2, DDR Port 3, DDR Port 4, DDR Port5, DDR Port7 are enabled automatically by the peripheral clock enable bit of the IP on the corresponding bus.
     * |[5]     |DDR6CKEN  |DDR Port6 Clock Enable Bit (Write Protect)
     * |        |          |0 = DDR Port6 peripheral clock Disabled.
     * |        |          |1 = DDR Port6 peripheral clock Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: The peripheral clock of DDR Port 1, DDR Port 2, DDR Port 3, DDR Port 4, DDR Port5, DDR Port7 are enabled automatically by the peripheral clock enable bit of the IP on the corresponding bus.
     * |[8]     |CANFD0CKEN|CANFD0 Clock Enable Bit
     * |        |          |0 = CANFD0 clock Disabled.
     * |        |          |1 = CANFD0 clock Enabled.
     * |[9]     |CANFD1CKEN|CANFD1 Clock Enable Bit
     * |        |          |0 = CANFD1 clock Disabled.
     * |        |          |1 = CANFD1 clock Enabled.
     * |[10]    |CANFD2CKEN|CANFD2 Clock Enable Bit
     * |        |          |0 = CANFD2 clock Disabled.
     * |        |          |1 = CANFD2 clock Enabled.
     * |[11]    |CANFD3CKEN|CANFD3 Clock Enable Bit
     * |        |          |0 = CANFD3 clock Disabled.
     * |        |          |1 = CANFD3 clock Enabled.
     * |[16]    |SDH0EN    |SD0 Host Controller AHB clock Enable Bit
     * |        |          |0 = SDH0 controller AHB clock Disabled.
     * |        |          |1 = SDH0 controller AHB clock Enabled.
     * |[17]    |SDH1EN    |SD1 Host Controller AHB clock Enable Bit
     * |        |          |0 = SDH1 controller AHB clock Disabled.
     * |        |          |1 = SDH1 controller AHB clock Enabled.
     * |[18]    |NANDEN    |NAND Controller Clock Enable Bit
     * |        |          |0 = NAND controller clock Disabled.
     * |        |          |1 = NAND controller clock Enabled.
     * |[19]    |USBDEN    |USBD Clock Enable Bit
     * |        |          |0 = USBD clock Disabled.
     * |        |          |1 = USBD clock Enabled.
     * |[20]    |USBHEN    |USBH Clock Enable Bit (TZNS)
     * |        |          |0 = USBH clock Disabled.
     * |        |          |1 = USBH clock Enabled.
     * |[21]    |HUSBH0EN  |High Speed USBH Clock Enable Bit (TZNS)
     * |        |          |0 = HUSBH0 clock Disabled.
     * |        |          |1 = HUSBH0 clock Enabled.
     * |[22]    |HUSBH1EN  |High Speed USBH Clock Enable Bit (TZNS)
     * |        |          |0 = HUSBH1 clock Disabled.
     * |        |          |1 = HUSBH1 clock Enabled.
     * |[24]    |GFXEN     |GFX Clock Enable Bit (TZNS)
     * |        |          |0 = GFX clock Disabled.
     * |        |          |1 = GFX clock Enabled.
     * |[25]    |VDECEN    |VC8000 Clock Enable Bit (TZNS)
     * |        |          |0 = VC8000 clock Disabled.
     * |        |          |1 = VC8000 clock Enabled.
     * |[26]    |DCUEN     |DC Ultra Clock Enable Bit (TZNS)
     * |        |          |0 = DC Ultra clock Disabled.
     * |        |          |1 = DC Ultra clock Enabled.
     * |[27]    |GMAC0EN   |Gigabit Ethernet MAC 0 AXI Clock Enable Bit (TZNS)
     * |        |          |0 = Gigabit Ethernet MAC 0 AXI clock Disabled.
     * |        |          |1 = Gigabit Ethernet MAC 0 AXI clock Enabled.
     * |[28]    |GMAC1EN   |Gigabit Ethernet MAC 1 AXI Clock Enable Bit (TZNS)
     * |        |          |0 = Gigabit Ethernet MAC 1 AXI clock Disabled.
     * |        |          |1 = Gigabit Ethernet MAC 1 AXI clock Enabled.
     * |[29]    |CCAP0EN   |CCAP0 Clock Enable Bit (TZNS)
     * |        |          |0 = CCAP0 clock Disabled.
     * |        |          |1 = CCAP0 clock Enabled.
     * |[30]    |CCAP1EN   |CCAP1 Clock Enable Bit (TZNS)
     * |        |          |0 = CCAP1 clock Disabled.
     * |        |          |1 = CCAP1 clock Enabled.
     * @var CLK_T::SYSCLK1
     * Offset: 0x08  AXI and AHB Device Clock Enable Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PDMA0EN   |PDMA0 Controller Clock Enable Bit
     * |        |          |0 = PDMA0 peripheral clock Disabled.
     * |        |          |1 = PDMA0 peripheral clock Enabled.
     * |[1]     |PDMA1EN   |PDMA1 Controller Clock Enable Bit
     * |        |          |0 = PDMA1 peripheral clock Disabled.
     * |        |          |1 = PDMA1 peripheral clock Enabled.
     * |[2]     |PDMA2EN   |PDMA2 Controller Clock Enable Bit
     * |        |          |0 = PDMA2 peripheral clock Disabled.
     * |        |          |1 = PDMA2 peripheral clock Enabled.
     * |[3]     |PDMA3EN   |PDMA3 Controller Clock Enable Bit
     * |        |          |0 = PDMA3 peripheral clock Disabled.
     * |        |          |1 = PDMA3 peripheral clock Enabled.
     * |[4]     |WH0CKEN   |Wormhole 0 Peripheral Clock Enable Bit (Write Protect, TZNS)
     * |        |          |0 = Wormhole 0 clock Disabled.
     * |        |          |1 = Wormhole 0 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZNS register.
     * |[5]     |WH1CKEN   |Wormhole 1 Peripheral Clock Enable Bit (Write Protect)
     * |        |          |0 = Wormhole 1 clock Disabled.
     * |        |          |1 = Wormhole 1 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[6]     |HWSCKEN   |Hardware Semaphore Clock Enable Bit (Write Protect, TZNS)
     * |        |          |0 = Hardware Semaphore peripheral clock Disabled.
     * |        |          |1 = Hardware Semaphore clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZNS register.
     * |[7]     |EBICKEN   |EBI Controller Clock Enable Bit
     * |        |          |0 = EBI peripheral clock Disabled.
     * |        |          |1 = EBI peripheral clock Enabled.
     * |[8]     |SRAM0CKEN |SRAM Bank0 Controller Clock Enable Bit (Write Protect)
     * |        |          |0 = SRAM bank0 clock Disabled.
     * |        |          |1 = SRAM bank0 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[9]     |SRAM1CKEN |SRAM Bank1 Controller Clock Enable Bit (Write Protect)
     * |        |          |0 = SRAM bank1 clock Disabled.
     * |        |          |1 = SRAM bank1 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[10]    |ROMCKEN   |ROM AHB Clock Enable Bit (Write Protect)
     * |        |          |0 = ROM AHB clock Disabled.
     * |        |          |1 = ROM AHB clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[11]    |TRACKEN   |Coresight Trace Clock Enable Bit (Write Protect)
     * |        |          |0 = Coresight trace clock Disabled.
     * |        |          |1 = Coresight trace clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[12]    |DBGCKEN   |Coresight Debug Clock Enable Bit (Write Protect)
     * |        |          |0 = Coresight debug clock Disabled.
     * |        |          |1 = Coresight debug clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[13]    |CLKOCKEN  |CLKO Clock Enable Bit (Write Protect)
     * |        |          |0 = CLKO clock Disabled.
     * |        |          |1 = CLKO clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[14]    |GTMRCKEN  |Cortex A35 Generic Timer Clock Enable Bit (Write Protect)
     * |        |          |0 = Cortex A35 Generic timer clock Disabled.
     * |        |          |1 = Cortex A35 Generic timer clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[16]    |GPACKEN   |GPIOA AHB Clock Enable Bit
     * |        |          |0 = GPIOA port clock Disabled.
     * |        |          |1 = GPIOA port clock Enabled.
     * |[17]    |GPBCKEN   |GPIOB AHB Clock Enable Bit
     * |        |          |0 = GPIOB port clock Disabled.
     * |        |          |1 = GPIOB port clock Enabled.
     * |[18]    |GPCCKEN   |GPIOC AHB Clock Enable Bit
     * |        |          |0 = GPIOC port clock Disabled.
     * |        |          |1 = GPIOC port clock Enabled.
     * |[19]    |GPDCKEN   |GPIOD AHB Clock Enable Bit
     * |        |          |0 = GPIOD port clock Disabled.
     * |        |          |1 = GPIOD port clock Enabled.
     * |[20]    |GPECKEN   |GPIOE AHB Clock Enable Bit
     * |        |          |0 = GPIOE port clock Disabled.
     * |        |          |1 = GPIOE port clock Enabled.
     * |[21]    |GPFCKEN   |GPIOF AHB Clock Enable Bit
     * |        |          |0 = GPIOF port clock Disabled.
     * |        |          |1 = GPIOF port clock Enabled.
     * |[22]    |GPGCKEN   |GPIOG AHB Clock Enable Bit
     * |        |          |0 = GPIOG port clock Disabled.
     * |        |          |1 = GPIOG port clock Enabled.
     * |[23]    |GPHCKEN   |GPIOH AHB Clock Enable Bit
     * |        |          |0 = GPIOH port clock Disabled.
     * |        |          |1 = GPIOH port clock Enabled.
     * |[24]    |GPICKEN   |GPIOI AHB Clock Enable Bit
     * |        |          |0 = GPIOI port clock Disabled.
     * |        |          |1 = GPIOI port clock Enabled.
     * |[25]    |GPJCKEN   |GPIOJ AHB Clock Enable Bit
     * |        |          |0 = GPIOJ port clock Disabled.
     * |        |          |1 = GPIOJ port clock Enabled.
     * |[26]    |GPKCKEN   |GPIOK AHB Clock Enable Bit
     * |        |          |0 = GPIOK port clock Disabled.
     * |        |          |1 = GPIOK port clock Enabled.
     * |[27]    |GPLCKEN   |GPIOL AHB Clock Enable Bit
     * |        |          |0 = GPIOL port clock Disabled.
     * |        |          |1 = GPIOL port clock Enabled.
     * |[28]    |GPMCKEN   |GPIOM AHB Clock Enable Bit
     * |        |          |0 = GPIOM port clock Disabled.
     * |        |          |1 = GPIOM port clock Enabled.
     * |[29]    |GPNCKEN   |GPION AHB Clock Enable Bit
     * |        |          |0 = GPION port clock Disabled.
     * |        |          |1 = GPION port clock Enabled.
     * @var CLK_T::APBCLK0
     * Offset: 0x0C  APB Devices Clock Enable Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TMR0CKEN  |Timer0 Clock Enable Bit
     * |        |          |0 = Timer0 clock Disabled.
     * |        |          |1 = Timer0 clock Enabled.
     * |[1]     |TMR1CKEN  |Timer1 Clock Enable Bit
     * |        |          |0 = Timer1 clock Disabled.
     * |        |          |1 = Timer1 clock Enabled.
     * |[2]     |TMR2CKEN  |Timer2 Clock Enable Bit
     * |        |          |0 = Timer2 clock Disabled.
     * |        |          |1 = Timer2 clock Enabled.
     * |[3]     |TMR3CKEN  |Timer3 Clock Enable Bit
     * |        |          |0 = Timer3 clock Disabled.
     * |        |          |1 = Timer3 clock Enabled.
     * |[4]     |TMR4CKEN  |Timer4 Clock Enable Bit
     * |        |          |0 = Timer4 clock Disabled.
     * |        |          |1 = Timer4 clock Enabled.
     * |[5]     |TMR5CKEN  |Timer5 Clock Enable Bit
     * |        |          |0 = Timer5 clock Disabled.
     * |        |          |1 = Timer5 clock Enabled.
     * |[6]     |TMR6CKEN  |Timer6 Clock Enable Bit
     * |        |          |0 = Timer6 clock Disabled.
     * |        |          |1 = Timer6 clock Enabled.
     * |[7]     |TMR7CKEN  |Timer7 Clock Enable Bit
     * |        |          |0 = Timer7 clock Disabled.
     * |        |          |1 = Timer7 clock Enabled.
     * |[8]     |TMR8CKEN  |Timer8 Clock Enable Bit
     * |        |          |0 = Timer8 clock Disabled.
     * |        |          |1 = Timer8 clock Enabled.
     * |[9]     |TMR9CKEN  |Timer9 Clock Enable Bit
     * |        |          |0 = Timer9 clock Disabled.
     * |        |          |1 = Timer9 clock Enabled.
     * |[10]    |TMR10CKEN |Timer10 Clock Enable Bit
     * |        |          |0 = Timer10 clock Disabled.
     * |        |          |1 = Timer10 clock Enabled.
     * |[11]    |TMR11CKEN |Timer11 Clock Enable Bit
     * |        |          |0 = Timer11 clock Disabled.
     * |        |          |1 = Timer11 clock Enabled.
     * |[12]    |UART0CKEN |UART0 Clock Enable Bit
     * |        |          |0 = UART0 clock Disabled.
     * |        |          |1 = UART0 clock Enabled.
     * |[13]    |UART1CKEN |UART1 Clock Enable Bit
     * |        |          |0 = UART1 clock Disabled.
     * |        |          |1 = UART1 clock Enabled.
     * |[14]    |UART2CKEN |UART2 Clock Enable Bit
     * |        |          |0 = UART2 clock Disabled.
     * |        |          |1 = UART2 clock Enabled.
     * |[15]    |UART3CKEN |UART3 Clock Enable Bit
     * |        |          |0 = UART3 clock Disabled.
     * |        |          |1 = UART3 clock Enabled.
     * |[16]    |UART4CKEN |UART4 Clock Enable Bit
     * |        |          |0 = UART4 clock Disabled.
     * |        |          |1 = UART4 clock Enabled.
     * |[17]    |UART5CKEN |UART5 Clock Enable Bit
     * |        |          |0 = UART5 clock Disabled.
     * |        |          |1 = UART5 clock Enabled.
     * |[18]    |UART6CKEN |UART6 Clock Enable Bit
     * |        |          |0 = UART6 clock Disabled.
     * |        |          |1 = UART6 clock Enabled.
     * |[19]    |UART7CKEN |UART7 Clock Enable Bit
     * |        |          |0 = UART7 clock Disabled.
     * |        |          |1 = UART7 clock Enabled.
     * |[20]    |UART8CKEN |UART8 Clock Enable Bit
     * |        |          |0 = UART8 clock Disabled.
     * |        |          |1 = UART8 clock Enabled.
     * |[21]    |UART9CKEN |UART9 Clock Enable Bit
     * |        |          |0 = UART9 clock Disabled.
     * |        |          |1 = UART9 clock Enabled.
     * |[22]    |UART10CKEN|UART10 Clock Enable Bit
     * |        |          |0 = UART10 clock Disabled.
     * |        |          |1 = UART10 clock Enabled.
     * |[23]    |UART11CKEN|UART11 Clock Enable Bit
     * |        |          |0 = UART11 clock Disabled.
     * |        |          |1 = UART11 clock Enabled.
     * |[24]    |UART12CKEN|UART12 Clock Enable Bit
     * |        |          |0 = UART12 clock Disabled.
     * |        |          |1 = UART12 clock Enabled.
     * |[25]    |UART13CKEN|UART13 Clock Enable Bit
     * |        |          |0 = UART13 clock Disabled.
     * |        |          |1 = UART13 clock Enabled.
     * |[26]    |UART14CKEN|UART14 Clock Enable Bit
     * |        |          |0 = UART14 clock Disabled.
     * |        |          |1 = UART14 clock Enabled.
     * |[27]    |UART15CKEN|UART15 Clock Enable Bit
     * |        |          |0 = UART15 clock Disabled.
     * |        |          |1 = UART15 clock Enabled.
     * |[28]    |UART16CKEN|UART16 Clock Enable Bit
     * |        |          |0 = UART16 clock Disabled.
     * |        |          |1 = UART16 clock Enabled.
     * |[29]    |RTCCKEN   |RTC Clock Enable Bit (Shared)
     * |        |          |0 = RTC Clock Disabled.
     * |        |          |1 = RTC Clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[30]    |DDRPCKEN  |DDR PHY Utility Block Clock Enable Bit
     * |        |          |0 = DDR PHY utility clock Disabled.
     * |        |          |1 = DDR PHY utility clock Enabled.
     * |[31]    |KPICKEN   |Keypad Interface Clock Enable Bit
     * |        |          |0 = Keypad interface clock Disabled.
     * |        |          |1 = Keypad interface clock Enabled.
     * @var CLK_T::APBCLK1
     * Offset: 0x10  APB Devices Clock Enable Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |I2C0CKEN  |I2C0 Clock Enable Bit
     * |        |          |0 = I2C0 clock Disabled.
     * |        |          |1 = I2C0 clock Enabled.
     * |[1]     |I2C1CKEN  |I2C1 Clock Enable Bit
     * |        |          |0 = I2C1 clock Disabled.
     * |        |          |1 = I2C1 clock Enabled.
     * |[2]     |I2C2CKEN  |I2C2 Clock Enable Bit
     * |        |          |0 = I2C2 clock Disabled.
     * |        |          |1 = I2C2 clock Enabled.
     * |[3]     |I2C3CKEN  |I2C3 Clock Enable Bit
     * |        |          |0 = I2C3 clock Disabled.
     * |        |          |1 = I2C3 clock Enabled.
     * |[4]     |I2C4CKEN  |I2C4 Clock Enable Bit
     * |        |          |0 = I2C4 clock Disabled.
     * |        |          |1 = I2C4 clock Enabled.
     * |[5]     |I2C5CKEN  |I2C5 Clock Enable Bit
     * |        |          |0 = I2C5 clock Disabled.
     * |        |          |1 = I2C5 clock Enabled.
     * |[6]     |QSPI0CKEN |QSPI0 Clock Enable Bit
     * |        |          |0 = QSPI0 clock Disabled.
     * |        |          |1 = QSPI0 clock Enabled.
     * |[7]     |QSPI1CKEN |QSPI1 Clock Enable Bit
     * |        |          |0 = QSPI1 clock Disabled.
     * |        |          |1 = QSPI1 clock Enabled.
     * |[12]    |SC0CKEN   |SC0 Clock Enable Bit
     * |        |          |0 = SC0 clock Disabled.
     * |        |          |1 = SC0 clock Enabled.
     * |[13]    |SC1CKEN   |SC1 Clock Enable Bit
     * |        |          |0 = SC1 clock Disabled.
     * |        |          |1 = SC1 clock Enabled.
     * |[16]    |WDT0CKEN  |Watchdog Timer 0 Clock Enable Bit (Write Protect)
     * |        |          |0 = Watchdog timer 0 clock Disabled.
     * |        |          |1 = Watchdog timer 0 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[17]    |WDT1CKEN  |Watchdog Timer 1 Clock Enable Bit (Write Protect)
     * |        |          |0 = Watchdog timer 1 clock Disabled.
     * |        |          |1 = Watchdog timer 1 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register or SYS_RLKTZNS register.
     * |[18]    |WDT2CKEN  |Watchdog Timer 2 Clock Enable Bit (Write Protect, SUBM)
     * |        |          |0 = Watchdog timer 2 clock Disabled.
     * |        |          |1 = Watchdog timer 2 clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKSUBM register.
     * |[24]    |EPWM0CKEN |EPWM0 Clock Enable Bit
     * |        |          |0 = EPWM0 clock Disabled.
     * |        |          |1 = EPWM0 clock Enabled.
     * |[25]    |EPWM1CKEN |EPWM1 Clock Enable Bit
     * |        |          |0 = EPWM1 clock Disabled.
     * |        |          |1 = EPWM1 clock Enabled.
     * |[26]    |EPWM2CKEN |EPWM2 Clock Enable Bit
     * |        |          |0 = EPWM2 clock Disabled.
     * |        |          |1 = EPWM2 clock Enabled.
     * @var CLK_T::APBCLK2
     * Offset: 0x14  APB Devices Clock Enable Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |I2S0CKEN  |I2S0 Clock Enable Bit
     * |        |          |0 = I2S0 Clock Disabled.
     * |        |          |1 = I2S0 Clock Enabled.
     * |[1]     |I2S1CKEN  |I2S1 Clock Enable Bit
     * |        |          |0 = I2S1 Clock Disabled.
     * |        |          |1 = I2S1 Clock Enabled.
     * |[2]     |SSMCCEN   |SSMCC Clock Enable Bit (Write Protect)
     * |        |          |0 = SSMCC clock Disabled.
     * |        |          |1 = SSMCC clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[3]     |SSPCCEN   |SSPCC Clock Enable Bit (Write Protect)
     * |        |          |0 = SSPCC clock Disabled.
     * |        |          |1 = SSPCC clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[4]     |SPI0CKEN  |SPI0 Clock Enable Bit
     * |        |          |0 = SPI0 clock Disabled.
     * |        |          |1 = SPI0 clock Enabled.
     * |[5]     |SPI1CKEN  |SPI1 Clock Enable Bit
     * |        |          |0 = SPI1 clock Disabled.
     * |        |          |1 = SPI1 clock Enabled.
     * |[6]     |SPI2CKEN  |SPI2 Clock Enable Bit
     * |        |          |0 = SPI2 clock Disabled.
     * |        |          |1 = SPI2 clock Enabled.
     * |[7]     |SPI3CKEN  |SPI3 Clock Enable Bit
     * |        |          |0 = SPI3 clock Disabled.
     * |        |          |1 = SPI3 clock Enabled.
     * |[8]     |ECAP0CKEN |ECAP0 Clock Enable Bit
     * |        |          |0 = ECAP0 clock Disabled.
     * |        |          |1 = ECAP0 clock Enabled.
     * |[9]     |ECAP1CKEN |ECAP1 Clock Enable Bit
     * |        |          |0 = ECAP1 clock Disabled.
     * |        |          |1 = ECAP1 clock Enabled.
     * |[10]    |ECAP2CKEN |ECAP2 Clock Enable Bit
     * |        |          |0 = ECAP2 clock Disabled.
     * |        |          |1 = ECAP2 clock Enabled.
     * |[12]    |QEI0CKEN  |QEI0 Clock Enable Bit
     * |        |          |0 = QEI0 clock Disabled.
     * |        |          |1 = QEI0 clock Enabled.
     * |[13]    |QEI1CKEN  |QEI1 Clock Enable Bit
     * |        |          |0 = QEI1 clock Disabled.
     * |        |          |1 = QEI1 clock Enabled.
     * |[14]    |QEI2CKEN  |QEI2 Clock Enable Bit
     * |        |          |0 = QEI2 clock Disabled.
     * |        |          |1 = QEI2 clock Enabled.
     * |[24]    |ADCCKEN   |ADC Clock Enable Bit
     * |        |          |0 = ADC clock Disabled.
     * |        |          |1 = ADC clock Enabled.
     * |[25]    |EADCCKEN  |EADC Clock Enable Bit
     * |        |          |0 = EADC clock Disabled.
     * |        |          |1 = EADC clock Enabled.
     * @var CLK_T::CLKSEL0
     * Offset: 0x18  Clock Source Select Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CA35CKSEL |Cortex A35 CPU Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from HXT.
     * |        |          |01 = Clock source from CA-PLL.
     * |        |          |10 = Clock source from EPLL.
     * |        |          |11 = Clock source from APLL.
     * |        |          |Note 2: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[2]     |SYSCK0SEL |System Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from EPLL/2.
     * |        |          |1 = Clock source from SYS-PLL.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[3]     |LVRDBSEL  |LVR Debounce Clock Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from LIRC.
     * |        |          |1 = Clock source from HIRC.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[5:4]   |SYSCK1SEL |System Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from HXT.
     * |        |          |01 = Clock source from SYS-PLL.
     * |        |          |10 = Clock source from APLL.
     * |        |          |11 = Clock source from APLL.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[10:8]  |RTPSTSEL  |RTP CortexM4 SysTick Clock Source Selection (Write Protect, SUBM)
     * |        |          |If SYST_CTRL[2]=0, SysTick uses listed clock source below.
     * |        |          |000 = Clock source from HXT.
     * |        |          |001 = Clock source from LXT.
     * |        |          |010 = Clock source from HXT/2.
     * |        |          |011 = Clock source from SYSCLK1/2.
     * |        |          |Others = Clock source from HIRC.
     * |        |          |Note 1: if SysTick clock source is not from HCLK (i.e
     * |        |          |SYST_CTRL[2] = 0), SysTick need clock frequency must less than or equal to HCLK/2.
     * |        |          |Note 2: These bits are write protected. Refer to the SYS_RLKSUBM register.
     * |[13:12] |CCAP0SEL  |CCAP0 Sensor Clock Source Selection (TZNS)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from HXT.
     * |        |          |01 = Clock source from VPLL.
     * |        |          |10 = Clock source from APLL.
     * |        |          |11 = Clock source from SYS-PLL.
     * |[15:14] |CCAP1SEL  |CCAP1 Sensor Clock Source Selection (TZNS)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from HXT.
     * |        |          |01 = Clock source from VPLL.
     * |        |          |10 = Clock source from APLL.
     * |        |          |11 = Clock source from SYS-PLL.
     * |[17:16] |SD0SEL    |SD HOST0 Controller Core Logic Clock Source Selection
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from APLL.
     * |        |          |01 = Clock source from VPLL.
     * |        |          |10 = Clock source from SYS-PLL.
     * |        |          |11 = Clock source from SYS-PLL.
     * |[19:18] |SD1SEL    |SD HOST1 Controller Core Logic Clock Source Selection
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |00 = Clock source from APLL.
     * |        |          |01 = Clock source from VPLL.
     * |        |          |10 = Clock source from SYS-PLL.
     * |        |          |11 = Clock source from SYS-PLL.
     * |[24]    |DCUSEL    |Display Controller Ultra Core Clock Source Selection (TZNS)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from EPLL/2.
     * |        |          |1 = Clock source from SYS-PLL.
     * |[25]    |DCUPSEL   |Display Controller Ultra Pixel Clock Source Selection (TZNS)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from VPLL.
     * |        |          |1 = Clock source from APLL.
     * |[26]    |GFXSEL    |GFX Core Clock Source Selection (TZNS)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from EPLL.
     * |        |          |1 = Clock source from SYS-PLL.
     * |[27]    |DBGSEL    |Coresight DBG Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |0 = Clock source from HIRC.1.
     * |        |          |1 = Clock source from SYS-PLL.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * @var CLK_T::CLKSEL1
     * Offset: 0x1C  Clock Source Select Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TMR0SEL   |TIMER0 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock TM0 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[6:4]   |TMR1SEL   |TIMER1 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock TM1 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[10:8]  |TMR2SEL   |TIMER2 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock TM2 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[14:12] |TMR3SEL   |TIMER3 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock TM3 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[18:16] |TMR4SEL   |TIMER4 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK2.
     * |        |          |011 = Clock source from external clock TM4 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[22:20] |TMR5SEL   |TIMER5 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK2.
     * |        |          |011 = Clock source from external clock TM5 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[26:24] |TMR6SEL   |TIMER6 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock TM6 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[30:28] |TMR7SEL   |TIMER7 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock TM7 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * @var CLK_T::CLKSEL2
     * Offset: 0x20  Clock Source Select Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TMR8SEL   |TIMER8 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock TM8 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[6:4]   |TMR9SEL   |TIMER9 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock TM9 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[10:8]  |TMR10SEL  |TIMER10 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK2.
     * |        |          |011 = Clock source from external clock TM10 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[14:12] |TMR11SEL  |TIMER11 Clock Source Selection
     * |        |          |000 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |010 = Clock source from PCLK2.
     * |        |          |011 = Clock source from external clock TM11 pin.
     * |        |          |101 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[17:16] |UART0SEL  |UART0 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[19:18] |UART1SEL  |UART1 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[21:20] |UART2SEL  |UART2 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[23:22] |UART3SEL  |UART3 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[25:24] |UART4SEL  |UART4 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[27:26] |UART5SEL  |UART5 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[29:28] |UART6SEL  |UART6 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[31:30] |UART7SEL  |UART7 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * @var CLK_T::CLKSEL3
     * Offset: 0x24  Clock Source Select Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |UART8SEL  |UART8 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[3:2]   |UART9SEL  |UART6 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[5:4]   |UART10SEL |UART10 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[7:6]   |UART11SEL |UART11 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[9:8]   |UART12SEL |UART12 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[11:10] |UART13SEL |UART13 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[13:12] |UART14SEL |UART14 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[15:14] |UART15SEL |UART15 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[17:16] |UART16SEL |UART16 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from SYSCLK1/2.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[21:20] |WDT0SEL   |Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |10 = Clock source from PCLK3/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[23:22] |WWDT0SEL  |Window Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |10 = Clock source from PCLK3/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |[25:24] |WDT1SEL   |Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |10 = Clock source from PCLK3/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZNS register or SYS_RLKTZS register.
     * |[27:26] |WWDT1SEL  |Window Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |10 = Clock source from PCLK3/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZNS register or SYS_RLKTZS register.
     * |[29:28] |WDT2SEL   |Watchdog Timer Clock Source Selection (Write Protect, SUBM)
     * |        |          |01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * |        |          |10 = Clock source from PCLK4/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZNS register.
     * |[31:30] |WWDT2SEL  |Window Watchdog Timer Clock Source Selection (Write Protect, SUBM)
     * |        |          |10 = Clock source from PCLK4/4096.
     * |        |          |11 = Clock source from 32 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_RLKTZNS register.
     * @var CLK_T::CLKSEL4
     * Offset: 0x28  Clock Source Select Control Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |SPI0SEL   |SPI3 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK1.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[3:2]   |SPI1SEL   |SPI1 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK2.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[5:4]   |SPI2SEL   |SPI2 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK1.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[7:6]   |SPI3SEL   |SPI3 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK2.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[9:8]   |QSPI0SEL  |QSPI0 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK0.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[11:10] |QSPI1SEL  |QSPI1 Clock Source Selection
     * |        |          |00 = Clock source from 24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from EPLL/4.
     * |        |          |10 = Clock source from PCLK0.
     * |        |          |11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
     * |[13:12] |I2S0SEL   |I2S0 Clock Source Selection
     * |        |          |00 = Clock source from HXT clock.
     * |        |          |01 = Clock source from APLL clock.
     * |        |          |10 = Clock source from PCLK0.
     * |        |          |11 = Clock source from HIRC clock.
     * |[15:14] |I2S1SEL   |I2S1 Clock Source Selection
     * |        |          |00 = Clock source from HXT clock.
     * |        |          |01 = Clock source from APLL clock.
     * |        |          |10 = Clock source from PCLK2.
     * |        |          |11 = Clock source from HIRC clock.
     * |[16]    |CANFD0SEL |CANFD0 Clock Source Selection
     * |        |          |0 = Clock source from APLL clock.
     * |        |          |1 = Clock source from VPLL clock.
     * |[17]    |CANFD1SEL |CANFD1 Clock Source Selection
     * |        |          |0 = Clock source from APLL clock.
     * |        |          |1 = Clock source from VPLL clock.
     * |[18]    |CANFD2SEL |CANFD2 Clock Source Selection
     * |        |          |0 = Clock source from APLL clock.
     * |        |          |1 = Clock source from VPLL clock.
     * |[19]    |CANFD3SEL |CANFD3 Clock Source Selection
     * |        |          |0 = Clock source from APLL clock.
     * |        |          |1 = Clock source from VPLL clock.
     * |[27:24] |CKOSEL    |Reference Clock Our Source Selection
     * |        |          |This field selects which clock is used to be the source of reference clock output
     * |        |          |0000 = Clock source from HXT.
     * |        |          |0001 = Clock source from LXT.
     * |        |          |0010 = Clock source from HIRC.
     * |        |          |0011 = Clock source from LIRC.
     * |        |          |0100 = Reserved..
     * |        |          |0101 = Clock source from SYS-PLL.
     * |        |          |0110 = Clock source from DDR core CLK.
     * |        |          |0111 = Clock source from EPLL/4.
     * |        |          |1000 = Clock source from APLL.
     * |        |          |1001 = Clock source from VPLL.
     * |        |          |1010 = Clock source from CA CLK.
     * |        |          |1011 = Clock source from AXI0 ACLK.
     * |        |          |1100 = Clock source from SYSCLK0.
     * |        |          |1101 = Clock source from SYSCLK1.
     * |        |          |1110 = Clock source from PCLK3.
     * |        |          |1111 = Clock source from PCLK4.
     * |        |          |Others = Reserved.
     * |[28]    |SC0SEL    |Smart Card 0 Clock Source Selection
     * |        |          |0 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |1 = Clock source from PCLK4.
     * |[29]    |SC1SEL    |Smart Card 1 Clock Source Selection
     * |        |          |0 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |1 = Clock source from PCLK4.
     * |[30]    |KPISEL    |Key Pad Interface Clock Source Selection
     * |        |          |0 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |1 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
     * @var CLK_T::CLKDIV0
     * Offset: 0x2C  Clock Divider Number Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CANFD0DIV |CANFD0 Clock Divide Number From CANFD0 Clock Source
     * |        |          |00 = Clock source from CANFD0 Clock Source /2.
     * |        |          |01 = Clock source from CANFD0 Clock Source /4.
     * |        |          |10 = Clock source from CANFD0 Clock Source /8.
     * |        |          |11 = Clock source from CANFD0 Clock Source /16.
     * |[3:2]   |CANFD1DIV |CANFD1 Clock Divide Number From CANFD1 Clock Source
     * |        |          |00 = Clock source from CANFD1 Clock Source /2.
     * |        |          |01 = Clock source from CANFD1 Clock Source /4.
     * |        |          |10 = Clock source from CANFD1 Clock Source /8.
     * |        |          |11 = Clock source from CANFD1 Clock Source /16.
     * |[5:4]   |CANFD2DIV |CANFD2 Clock Divide Number From CANFD2 Clock Source
     * |        |          |00 = Clock source from CANFD2 Clock Source /2.
     * |        |          |01 = Clock source from CANFD2 Clock Source /4.
     * |        |          |10 = Clock source from CANFD2 Clock Source /8.
     * |        |          |11 = Clock source from CANFD2 Clock Source /16.
     * |[7:6]   |CANFD3DIV |CANFD3 Clock Divide Number From CANFD3 Clock Source
     * |        |          |00 = Clock source from CANFD3 Clock Source /2.
     * |        |          |01 = Clock source from CANFD3 Clock Source /4.
     * |        |          |10 = Clock source from CANFD3 Clock Source /8.
     * |        |          |11 = Clock source from CANFD3 Clock Source /16.
     * |[25:24] |DCUPDIV   |Display Controller Ultra Pixel Divided Clock Source (Read Only)
     * |        |          |00 = Clock source from Display Controller Ultra Pixel Clock Source /2.
     * |        |          |01 = Clock source from Display Controller Ultra Pixel Clock Source /4.
     * |        |          |10 = Clock source from Display Controller Ultra Pixel Clock Source /8.
     * |        |          |11 = Clock source from Display Controller Ultra Pixel Clock Source /16.
     * |[26]    |ACLK0DIV  |AXI0 Bus Clock Divide Number From CA-PLL Clock Source (Write Protect)
     * |        |          |0 = Clock source from CA-PLL /2.
     * |        |          |1 = Clock source from CA-PLL /4.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[29:28] |EMAC0DIV  |EMAC0 TX Clock Divide Selection From EPLL Clock Source (Read Only)
     * |        |          |00 = Clock source from EPLL /2.(RGMII).
     * |        |          |01 = Clock source from EPLL /2.(RGMII).
     * |        |          |10 = Clock source from EPLL /100 (RGMII).
     * |        |          |11 = Clock source from EPLL /10 (RGMII).
     * |        |          |X0 = Clock source from RMII reference clock /20 (RMII).
     * |        |          |X1 = Clock source from RMII reference clock /2 (RMII).
     * |        |          |Others = Reserved.
     * |        |          |Note: This field definition depends on the Ethernet mac is RMII or not.
     * |[31:30] |EMAC1DIV  |EMAC1 TX Clock Divide Selection From EPLL Clock Source (Read Only)
     * |        |          |00 = Clock source from EPLL /2.(RGMII).
     * |        |          |01 = Clock source from EPLL /2.(RGMII).
     * |        |          |10 = Clock source from EPLL /100 (RGMII).
     * |        |          |11 = Clock source from EPLL /10 (RGMII).
     * |        |          |X0 = Clock source from RMII reference clock /20 (RMII).
     * |        |          |X1 = Clock source from RMII reference clock /2 (RMII).
     * |        |          |Others = Reserved.
     * |        |          |Note: This field definition depends on the Ethernet mac is RMII or not.
     * @var CLK_T::CLKDIV1
     * Offset: 0x30  Clock Divider Number Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SC0DIV    |Smart Card 0 Clock Divide Number From SC0 Clock Source
     * |        |          |SC0 clock frequency = (SC0 clock source frequency) / (SC0DIV + 1).
     * |[7:4]   |SC1DIV    |Smart Card 1 Clock Divide Number From SC1 Clock Source
     * |        |          |SC1 clock frequency = (SC1 clock source frequency) / (SC1DIV + 1).
     * |[11:8]  |CCAP0DIV  |CCAP0 Clock Divide Number From CCAP0 Clock Source (TZNS)
     * |        |          |CCAP0 clock frequency = (CCAP0 clock source frequency) / (CCAP0DIV + 1).
     * |[15:12] |CCAP1DIV  |CCAP1 Clock Divide Number From CCAP1 Clock Source (TZNS)
     * |        |          |CCAP1 clock frequency = (CCAP1 clock source frequency) / (CCAP1DIV + 1).
     * |[19:16] |UART0DIV  |UART0 Clock Divide Number From UART0 Clock Source
     * |        |          |UART0 clock frequency = (UART0 clock source frequency) / (UART0DIV + 1).
     * |[23:20] |UART1DIV  |UART1 Clock Divide Number From UART1 Clock Source
     * |        |          |UART1 clock frequency = (UART1 clock source frequency) / (UART1DIV + 1).
     * |[27:24] |UART2DIV  |UART2 Clock Divide Number From UART2 Clock Source
     * |        |          |UART2 clock frequency = (UART2 clock source frequency) / (UART2DIV + 1).
     * |[31:28] |UART3DIV  |UART3 Clock Divide Number From UART3 Clock Source
     * |        |          |UART3 clock frequency = (UART3 clock source frequency) / (UART3DIV + 1).
     * @var CLK_T::CLKDIV2
     * Offset: 0x34  Clock Divider Number Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |UART4DIV  |UART4 Clock Divide Number From UART4 Clock Source
     * |        |          |UART4 clock frequency = (UART4 clock source frequency) / (UART4DIV + 1).
     * |[7:4]   |UART5DIV  |UART5 Clock Divide Number From UART5 Clock Source
     * |        |          |UART5 clock frequency = (UART5 clock source frequency) / (UART5DIV + 1).
     * |[11:8]  |UART6DIV  |UART6 Clock Divide Number From UART6 Clock Source
     * |        |          |UART6 clock frequency = (UART6 clock source frequency) / (UART6DIV + 1).
     * |[15:12] |UART7DIV  |UART7 Clock Divide Number From UART7 Clock Source
     * |        |          |UART7 clock frequency = (UART7 clock source frequency) / (UART7DIV + 1).
     * |[19:16] |UART8DIV  |UART8 Clock Divide Number From UART8 Clock Source
     * |        |          |UART8 clock frequency = (UART8 clock source frequency) / (UART8DIV + 1).
     * |[23:20] |UART9DIV  |UART9 Clock Divide Number From UART9 Clock Source
     * |        |          |UART9 clock frequency = (UART9 clock source frequency) / (UART9DIV + 1).
     * |[27:24] |UART10DIV |UART10 Clock Divide Number From UART10 Clock Source
     * |        |          |UART10 clock frequency = (UART10 clock source frequency) / (UART10DIV + 1).
     * |[31:28] |UART11DIV |UART11 Clock Divide Number From UART11 Clock Source
     * |        |          |UART11 clock frequency = (UART11 clock source frequency) / (UART11DIV + 1).
     * @var CLK_T::CLKDIV3
     * Offset: 0x38  Clock Divider Number Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |UART12DIV |UART12 Clock Divide Number From UART12 Clock Source
     * |        |          |UART12 clock frequency = (UART12 clock source frequency) / (UART12DIV + 1).
     * |[7:4]   |UART13DIV |UART13 Clock Divide Number From UART13 Clock Source
     * |        |          |UART13 clock frequency = (UART13 clock source frequency) / (UART13DIV + 1).
     * |[11:8]  |UART14DIV |UART14 Clock Divide Number From UART14 Clock Source
     * |        |          |UART14 clock frequency = (UART14 clock source frequency) / (UART14DIV + 1).
     * |[15:12] |UART15DIV |UART15 Clock Divide Number From UART15 Clock Source
     * |        |          |UART15 clock frequency = (UART15 clock source frequency) / (UART15DIV + 1).
     * |[19:16] |UART16DIV |UART16 Clock Divide Number From UART16 Clock Source
     * |        |          |UART16 clock frequency = (UART16 clock source frequency) / (UART16DIV + 1).
     * @var CLK_T::CLKDIV4
     * Offset: 0x3C  Clock Divider Number Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |EADCDIV   |EADC Clock Divide Number From EADC Clock Source
     * |        |          |EADC clock frequency = (EADC clock source frequency) / (EADCDIV + 1).
     * |[20:4]  |ADCDIV    |ADC Clock Divide Number From ADC Clock Source
     * |        |          |ADC clock frequency = (ADC clock source frequency) / (ADCDIV + 1).
     * |[31:24] |KPIDIV    |Keypad Interface Clock Divide Number From KPI Clock Source
     * |        |          |KPI clock frequency = (KPI clock source frequency) / (KPIDIV + 1).
     * @var CLK_T::CLKOCTL
     * Offset: 0x40  Clock Output Control Register (Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FREQSEL   |Clock Output Frequency Selection
     * |        |          |The formula of output frequency is
     * |        |          |Fout = Fin/2(N+1).
     * |        |          |Fin is the input clock frequency.
     * |        |          |Fout is the frequency of divider output clock.
     * |        |          |N is the 4-bit value of FREQSEL [3:0].
     * |[4]     |CLKOEN    |Clock Output Enable Bit
     * |        |          |0 = Clock Output function Disabled.
     * |        |          |1 = Clock Output function Enabled.
     * |[5]     |DIV1EN    |Clock Output Divide One Enable Bit
     * |        |          |0 = Clock Output will output clock with source frequency divided by FREQSEL.
     * |        |          |1 = Clock Output will output clock with source frequency.
     * @var CLK_T::STATUS
     * Offset: 0x50  Clock Status Monitor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTSTB    |HXT Clock Source Stable Flag (Read Only)
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock is not stable or disabled.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock is stable and enabled.
     * |[1]     |LXTSTB    |LXT Clock Source Stable Flag (Read Only)
     * |        |          |LXT clock source can be selected as external LXT or LIRC32 by setting C32KS(RTC_LXTCTL[6])
     * |        |          |IfC32KS is set to 0 the LXT stable flag is set when external LXT clock source is stable
     * |        |          |IfC32KS is set to 1 the LXT stable flag is set when LIRC32 clock source is stable.
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is not stable or disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock is stabled and enabled.
     * |[2]     |SYSPLLSTB |SYS-PLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = SYS-PLL clock is not stable or disabled.
     * |        |          |1 = SYS-PLL clock is stable and enabled.
     * |[3]     |LIRCSTB   |LIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = 32 kHz internal low speed RC oscillator (LIRC) clock is not stable or disabled.
     * |        |          |1 = 32 kHz internal low speed RC oscillator (LIRC) clock is stable and enabled.
     * |[4]     |HIRCSTB   |HIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = 12 MHz internal high speed RC oscillator (HIRC) clock is not stable or disabled.
     * |        |          |1 = 12 MHz internal high speed RC oscillator (HIRC) clock is stable and enabled.
     * |[6]     |CAPLLSTB  |Cortex35 PLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = CA-PLL clock is not stable or disabled.
     * |        |          |1 = CA-PLL clock is stable and enabled.
     * |[8]     |DDRPLLSTB |DDR-PLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = DDR-PLL clock is not stable or disabled.
     * |        |          |1 = DDR-PLL clock is stable and enabled.
     * |[9]     |EPLLSTB   |EPLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = EPLL clock is not stable or disabled.
     * |        |          |1 = EPLL clock is stable and enabled.
     * |[10]    |APLLSTB   |APLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = APLL clock is not stable or disabled.
     * |        |          |1 = APLL clock is stable and enabled.
     * |[11]    |VPLLSTB   |VPLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = VPLL clock is not stable or disabled.
     * |        |          |1 = VPLL clock is stable and enabled.
     * @var CLK_T::PLL0CTL0
     * Offset: 0x60  CA-PLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL0CTL1
     * Offset: 0x64  CA-PLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL0CTL2
     * Offset: 0x68  CA-PLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL1CTL0
     * Offset: 0x70  SYS-PLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL1CTL1
     * Offset: 0x74  SYS-PLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL1CTL2
     * Offset: 0x78  SYS-PLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL2CTL0
     * Offset: 0x80  DDR-PLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL2CTL1
     * Offset: 0x84  DDR-PLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL2CTL2
     * Offset: 0x88  DDR-PLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL3CTL0
     * Offset: 0x90  APLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL3CTL1
     * Offset: 0x94  APLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL3CTL2
     * Offset: 0x98  APLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL4CTL0
     * Offset: 0xA0  EPLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL4CTL1
     * Offset: 0xA4  EPLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL4CTL2
     * Offset: 0xA8  EPLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL5CTL0
     * Offset: 0xB0  VPLL Control Register 0(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Set the feedback divider factor (N) from 16 to 2047.
     * |        |          |The N = FBDIV[10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[17:12] |INDIV     |PLL Reference Input Divider Control (Write Protect)
     * |        |          |Set the reference divider factor (M) from 1 to 63.
     * |        |          |The M = INDIV[5:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[19:18] |MODE      |Operation Mode Selection(Write Protect)
     * |        |          |00 = Integer mode.
     * |        |          |In this mode, the rising edges of the two clocks at the input of PFD are phase aligned
     * |        |          |And the output clock frequency is at multiples of the input clock frequency contingent on the configuration of OUTDIV, INDIV and FBDIV.
     * |        |          |01 = Fractional mode.
     * |        |          |This mode is suitable for applications which need small output frequency steps, like 20 kHz
     * |        |          |The jitter performance in this mode may be worse than in Integer Mode.
     * |        |          |In this mode, the output clock frequency is at the fractional multiples of the input clock frequency
     * |        |          |By setting the control pins FRAC [23:0], a small output frequency step is achieved..
     * |        |          |10 = Spread Spectrum Mode.
     * |        |          |This mode is suitable for In this mode the output frequency of PLL will be modulated by triangle wave
     * |        |          |It is for EMI consideration.
     * |        |          |By setting SSRATE [10:0] and SLOPE [23:0], the modulation index and the modulation frequency can be programmed.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[30:20] |SSRATE    |Spreading Frequency Control (Write Protect)
     * |        |          |Set the spread step factor SSRATE from 0 to 2047,
     * |        |          |SSRATE = SSRATE [10:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL5CTL1
     * Offset: 0xB4  VPLL Control Register 1(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PD        |Power-down Mode (Write Protect)
     * |        |          |0 = PLL is enable (in normal mode).
     * |        |          |1 = PLL is disable (in Power-down mode) (default).
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[1]     |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock Fref.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[6:4]   |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Set the output divider factor (P) from 1 to 7.
     * |        |          |P = OUTDIV[2:0].
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * |[31:8]  |FRAC      |PLL Fractional Portion of DN Value (Write Protect)
     * |        |          |Set the fraction part (X) of Fractional Portion of DN Value factor.
     * |        |          |The X = FRAC[23:0] / 224.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::PLL5CTL2
     * Offset: 0xB8  VPLL Control Register 2(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |SLOPE     |PLL Stable Counter Selection (Write Protect)
     * |        |          |Set the spread step factor SLOPE from 0 to 16777215,
     * |        |          |SLOPE = SLOPE[23:0].
     * |        |          |Note 1: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS register
     * |        |          |For PLL3, PLL4, and PLL5, user can also refer to the SYS_RLKTZNS register if SYSSIAEN is 1.
     * @var CLK_T::CLKDCTL
     * Offset: 0xC0  Clock Fail Detector Control Register(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |HXTFDEN   |HXT Clock Fail Detector Enable Bit
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock fail detector Disabled.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock fail detector Enabled.
     * |[5]     |HXTFIEN   |HXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock fail interrupt Disabled.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock fail interrupt Enabled.
     * |[12]    |LXTFDEN   |LXT Clock Fail Detector Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail detector Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail detector Enabled.
     * |[13]    |LXTFIEN   |LXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail interrupt Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail interrupt Enabled.
     * |[16]    |HXTFQDEN  |HXT Clock Frequency Monitor Enable Bit
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Disabled.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Enabled.
     * |[17]    |HXTFQIEN  |HXT Clock Frequency Monitor Interrupt Enable Bit
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Disabled.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Enabled.
     * @var CLK_T::CLKDSTS
     * Offset: 0xC4  Clock Fail Detector Status Register(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTFIF    |HXT Clock Fail Interrupt Flag (Write Protect, Write 1 to Clear)
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock is normal.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock stops.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[1]     |LXTFIF    |LXT Clock Fail Interrupt Flag (Write Protect, Write 1 to Clear)
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is normal.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) stops.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[8]     |HXTFQIF   |HXT Clock Frequency Monitor Interrupt Flag (Write Protect, Write 1 to Clear)
     * |        |          |0 = 24 MHz external high speed crystal oscillator (HXT) clock is normal.
     * |        |          |1 = 24 MHz external high speed crystal oscillator (HXT) clock frequency is abnormal.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_RLKTZS register.
     * @var CLK_T::CDUPB
     * Offset: 0xC8  Clock Frequency Detector Upper Boundary Register(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |UPERBD    |HXT Clock Frequency Detector Upper Boundary
     * |        |          |The bits define the high value of frequency monitor window.
     * |        |          |When HXT frequency monitor value higher than this register, the HXT frequency detect fail interrupt flag will set to 1.
     * @var CLK_T::CDLOWB
     * Offset: 0xCC  Clock Frequency Detector Lower Boundary Register(Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |LOWERBD   |HXT Clock Frequency Detector Lower Boundary
     * |        |          |The bits define the low value of frequency monitor window.
     * |        |          |When HXT frequency monitor value lower than this register, the HXT frequency detect fail interrupt flag will set to 1.
     * @var CLK_T::CKFLTRCTL
     * Offset: 0xD0  Clock Filter Control Register (Write Protect)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTFLTREN |HXT Clock Filter Enable Control Bit (Write Protect)
     * |        |          |0 = HXT clock filter function Disabled.
     * |        |          |1 = HXT clock filter function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[1]     |HXTFLTRSEL|HXT Clock Filter Frequency Select
     * |        |          |0 = HXT frequency is > 24 MHz.
     * |        |          |1 = HXT frequency is <= 24 MHz.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[4]     |HXTGTEN   |HXT Clock Gating Enable Control Bit (Write Protect)
     * |        |          |0 = HXT clock filter function Disabled.
     * |        |          |1 = HXT clock filter function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[5]     |HXTBYPSEN |HXT Clock Bypass Enable Control Bit (Write Protect)
     * |        |          |0 = HXT clock filter function Disabled.
     * |        |          |1 = HXT clock filter function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[8]     |HIRCFLTREN|HIRC Clock Filter Enable Control Bit (Write Protect)
     * |        |          |0 = HIRC clock filter function Disabled.
     * |        |          |1 = HIRC clock filter function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[9]     |HIRCFLTRSEL|HIRC Clock Filter Frequency Select
     * |        |          |0 = HIRC frequency is > 12 MHz.
     * |        |          |1 = HIRC frequency is <= 12 MHz.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[12]    |HIRCGTEN  |HIRC Clock Gating Enable Control Bit (Write Protect)
     * |        |          |0 = HIRC clock filter function Disabled.
     * |        |          |1 = HIRC clock filter function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     */
    __IO uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    __IO uint32_t SYSCLK0;               /*!< [0x0004] AXI and AHB Device Clock Enable Control Register 0               */
    __IO uint32_t SYSCLK1;               /*!< [0x0008] AXI and AHB Device Clock Enable Control Register 1               */
    __IO uint32_t APBCLK0;               /*!< [0x000c] APB Devices Clock Enable Control Register 0                      */
    __IO uint32_t APBCLK1;               /*!< [0x0010] APB Devices Clock Enable Control Register 1                      */
    __IO uint32_t APBCLK2;               /*!< [0x0014] APB Devices Clock Enable Control Register 2                      */
    __IO uint32_t CLKSEL0;               /*!< [0x0018] Clock Source Select Control Register 0                           */
    __IO uint32_t CLKSEL1;               /*!< [0x001c] Clock Source Select Control Register 1                           */
    __IO uint32_t CLKSEL2;               /*!< [0x0020] Clock Source Select Control Register 2                           */
    __IO uint32_t CLKSEL3;               /*!< [0x0024] Clock Source Select Control Register 3                           */
    __IO uint32_t CLKSEL4;               /*!< [0x0028] Clock Source Select Control Register 4                           */
    __IO uint32_t CLKDIV0;               /*!< [0x002c] Clock Divider Number Register 0                                  */
    __IO uint32_t CLKDIV1;               /*!< [0x0030] Clock Divider Number Register 1                                  */
    __IO uint32_t CLKDIV2;               /*!< [0x0034] Clock Divider Number Register 2                                  */
    __IO uint32_t CLKDIV3;               /*!< [0x0038] Clock Divider Number Register 3                                  */
    __IO uint32_t CLKDIV4;               /*!< [0x003c] Clock Divider Number Register 4                                  */
    __IO uint32_t CLKOCTL;               /*!< [0x0040] Clock Output Control Register (Write Protect)                    */
    __I  uint32_t RESERVE0[3];
    __I  uint32_t STATUS;                /*!< [0x0050] Clock Status Monitor Register                                    */
    __I  uint32_t RESERVE1[3];
    union
    {
        /* data */
        __IO uint32_t PLL0CTL0;          /*!< [0x0060] CA-PLL Control Register 0                                        */
        PLL_T PLL[6];                    /*!< [0x0080] PLL Control Registers (Write Protect)                            */
    };
    __IO uint32_t CLKDCTL;               /*!< [0x00c0] Clock Fail Detector Control Register(Write Protect)              */
    __IO uint32_t CLKDSTS;               /*!< [0x00c4] Clock Fail Detector Status Register(Write Protect)               */
    __IO uint32_t CDUPB;                 /*!< [0x00c8] Clock Frequency Detector Upper Boundary Register(Write Protect)  */
    __IO uint32_t CDLOWB;                /*!< [0x00cc] Clock Frequency Detector Lower Boundary Register(Write Protect)  */
    __IO uint32_t CKFLTRCTL;             /*!< [0x00d0] Clock Filter Control Register (Write Protect)                    */

} CLK_T;

/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

#define CLK_PWRCTL_HXTEN_Pos             (0)                                               /*!< CLK_T::PWRCTL: HXTEN Position          */
#define CLK_PWRCTL_HXTEN_Msk             (0x1ul << CLK_PWRCTL_HXTEN_Pos)                   /*!< CLK_T::PWRCTL: HXTEN Mask              */

#define CLK_PWRCTL_LXTEN_Pos             (1)                                               /*!< CLK_T::PWRCTL: LXTEN Position          */
#define CLK_PWRCTL_LXTEN_Msk             (0x1ul << CLK_PWRCTL_LXTEN_Pos)                   /*!< CLK_T::PWRCTL: LXTEN Mask              */

#define CLK_PWRCTL_HIRCEN_Pos            (2)                                               /*!< CLK_T::PWRCTL: HIRCEN Position         */
#define CLK_PWRCTL_HIRCEN_Msk            (0x1ul << CLK_PWRCTL_HIRCEN_Pos)                  /*!< CLK_T::PWRCTL: HIRCEN Mask             */

#define CLK_PWRCTL_LIRCEN_Pos            (3)                                               /*!< CLK_T::PWRCTL: LIRCEN Position         */
#define CLK_PWRCTL_LIRCEN_Msk            (0x1ul << CLK_PWRCTL_LIRCEN_Pos)                  /*!< CLK_T::PWRCTL: LIRCEN Mask             */

#define CLK_PWRCTL_HXTDS_Pos             (10)                                              /*!< CLK_T::PWRCTL: HXTDS Position          */
#define CLK_PWRCTL_HXTDS_Msk             (0x1ul << CLK_PWRCTL_HXTDS_Pos)                   /*!< CLK_T::PWRCTL: HXTDS Mask              */

#define CLK_PWRCTL_SYSPLLAPD_Pos         (11)                                              /*!< CLK_T::PWRCTL: SYSPLLAPD Position      */
#define CLK_PWRCTL_SYSPLLAPD_Msk         (0x1ul << CLK_PWRCTL_SYSPLLAPD_Pos)               /*!< CLK_T::PWRCTL: SYSPLLAPD Mask          */

#define CLK_PWRCTL_CAPLLAPD_Pos          (12)                                              /*!< CLK_T::PWRCTL: CAPLLAPD Position       */
#define CLK_PWRCTL_CAPLLAPD_Msk          (0x1ul << CLK_PWRCTL_CAPLLAPD_Pos)                /*!< CLK_T::PWRCTL: CAPLLAPD Mask           */

#define CLK_PWRCTL_DDRPLLAPD_Pos         (13)                                              /*!< CLK_T::PWRCTL: DDRPLLAPD Position      */
#define CLK_PWRCTL_DDRPLLAPD_Msk         (0x1ul << CLK_PWRCTL_DDRPLLAPD_Pos)               /*!< CLK_T::PWRCTL: DDRPLLAPD Mask          */

#define CLK_PWRCTL_HXTAOFF_Pos           (14)                                              /*!< CLK_T::PWRCTL: HXTAOFF Position        */
#define CLK_PWRCTL_HXTAOFF_Msk           (0x1ul << CLK_PWRCTL_HXTAOFF_Pos)                 /*!< CLK_T::PWRCTL: HXTAOFF Mask            */

#define CLK_PWRCTL_HIRCAOFF_Pos          (15)                                              /*!< CLK_T::PWRCTL: HIRCAOFF Position       */
#define CLK_PWRCTL_HIRCAOFF_Msk          (0x1ul << CLK_PWRCTL_HIRCAOFF_Pos)                /*!< CLK_T::PWRCTL: HIRCAOFF Mask           */

#define CLK_PWRCTL_LXTSTBS_Pos           (16)                                              /*!< CLK_T::PWRCTL: LXTSTBS Position        */
#define CLK_PWRCTL_LXTSTBS_Msk           (0x3ul << CLK_PWRCTL_LXTSTBS_Pos)                 /*!< CLK_T::PWRCTL: LXTSTBS Mask            */

#define CLK_PWRCTL_GICAOFF_Pos           (21)                                              /*!< CLK_T::PWRCTL: GICAOFF Position        */
#define CLK_PWRCTL_GICAOFF_Msk           (0x1ul << CLK_PWRCTL_GICAOFF_Pos)                 /*!< CLK_T::PWRCTL: GICAOFF Mask            */

#define CLK_PWRCTL_HXTAPD_Pos            (22)                                              /*!< CLK_T::PWRCTL: HXTAPD Position         */
#define CLK_PWRCTL_HXTAPD_Msk            (0x1ul << CLK_PWRCTL_HXTAPD_Pos)                  /*!< CLK_T::PWRCTL: HXTAPD Mask             */

#define CLK_PWRCTL_HIRCAPD_Pos           (23)                                              /*!< CLK_T::PWRCTL: HIRCAPD Position        */
#define CLK_PWRCTL_HIRCAPD_Msk           (0x1ul << CLK_PWRCTL_HIRCAPD_Pos)                 /*!< CLK_T::PWRCTL: HIRCAPD Mask            */

#define CLK_SYSCLK0_RTPEN_Pos            (1)                                               /*!< CLK_T::SYSCLK0: RTPEN Position         */
#define CLK_SYSCLK0_RTPEN_Msk            (0x1ul << CLK_SYSCLK0_RTPEN_Pos)                  /*!< CLK_T::SYSCLK0: RTPEN Mask             */

#define CLK_SYSCLK0_TAHBCKEN_Pos         (2)                                               /*!< CLK_T::SYSCLK0: TAHBCKEN Position      */
#define CLK_SYSCLK0_TAHBCKEN_Msk         (0x1ul << CLK_SYSCLK0_TAHBCKEN_Pos)               /*!< CLK_T::SYSCLK0: TAHBCKEN Mask          */

#define CLK_SYSCLK0_LVRDBEN_Pos          (3)                                               /*!< CLK_T::SYSCLK0: LVRDBEN Position       */
#define CLK_SYSCLK0_LVRDBEN_Msk          (0x1ul << CLK_SYSCLK0_LVRDBEN_Pos)                /*!< CLK_T::SYSCLK0: LVRDBEN Mask           */

#define CLK_SYSCLK0_DDR0CKEN_Pos         (4)                                               /*!< CLK_T::SYSCLK0: DDR0CKEN Position      */
#define CLK_SYSCLK0_DDR0CKEN_Msk         (0x1ul << CLK_SYSCLK0_DDR0CKEN_Pos)               /*!< CLK_T::SYSCLK0: DDR0CKEN Mask          */

#define CLK_SYSCLK0_DDR6CKEN_Pos         (5)                                               /*!< CLK_T::SYSCLK0: DDR6CKEN Position      */
#define CLK_SYSCLK0_DDR6CKEN_Msk         (0x1ul << CLK_SYSCLK0_DDR6CKEN_Pos)               /*!< CLK_T::SYSCLK0: DDR6CKEN Mask          */

#define CLK_SYSCLK0_CANFD0CKEN_Pos       (8)                                               /*!< CLK_T::SYSCLK0: CANFD0CKEN Position    */
#define CLK_SYSCLK0_CANFD0CKEN_Msk       (0x1ul << CLK_SYSCLK0_CANFD0CKEN_Pos)             /*!< CLK_T::SYSCLK0: CANFD0CKEN Mask        */

#define CLK_SYSCLK0_CANFD1CKEN_Pos       (9)                                               /*!< CLK_T::SYSCLK0: CANFD1CKEN Position    */
#define CLK_SYSCLK0_CANFD1CKEN_Msk       (0x1ul << CLK_SYSCLK0_CANFD1CKEN_Pos)             /*!< CLK_T::SYSCLK0: CANFD1CKEN Mask        */

#define CLK_SYSCLK0_CANFD2CKEN_Pos       (10)                                              /*!< CLK_T::SYSCLK0: CANFD2CKEN Position    */
#define CLK_SYSCLK0_CANFD2CKEN_Msk       (0x1ul << CLK_SYSCLK0_CANFD2CKEN_Pos)             /*!< CLK_T::SYSCLK0: CANFD2CKEN Mask        */

#define CLK_SYSCLK0_CANFD3CKEN_Pos       (11)                                              /*!< CLK_T::SYSCLK0: CANFD3CKEN Position    */
#define CLK_SYSCLK0_CANFD3CKEN_Msk       (0x1ul << CLK_SYSCLK0_CANFD3CKEN_Pos)             /*!< CLK_T::SYSCLK0: CANFD3CKEN Mask        */

#define CLK_SYSCLK0_SDH0EN_Pos           (16)                                              /*!< CLK_T::SYSCLK0: SDH0EN Position        */
#define CLK_SYSCLK0_SDH0EN_Msk           (0x1ul << CLK_SYSCLK0_SDH0EN_Pos)                 /*!< CLK_T::SYSCLK0: SDH0EN Mask            */

#define CLK_SYSCLK0_SDH1EN_Pos           (17)                                              /*!< CLK_T::SYSCLK0: SDH1EN Position        */
#define CLK_SYSCLK0_SDH1EN_Msk           (0x1ul << CLK_SYSCLK0_SDH1EN_Pos)                 /*!< CLK_T::SYSCLK0: SDH1EN Mask            */

#define CLK_SYSCLK0_NANDEN_Pos           (18)                                              /*!< CLK_T::SYSCLK0: NANDEN Position        */
#define CLK_SYSCLK0_NANDEN_Msk           (0x1ul << CLK_SYSCLK0_NANDEN_Pos)                 /*!< CLK_T::SYSCLK0: NANDEN Mask            */

#define CLK_SYSCLK0_USBDEN_Pos           (19)                                              /*!< CLK_T::SYSCLK0: USBDEN Position        */
#define CLK_SYSCLK0_USBDEN_Msk           (0x1ul << CLK_SYSCLK0_USBDEN_Pos)                 /*!< CLK_T::SYSCLK0: USBDEN Mask            */

#define CLK_SYSCLK0_USBHEN_Pos           (20)                                              /*!< CLK_T::SYSCLK0: USBHEN Position        */
#define CLK_SYSCLK0_USBHEN_Msk           (0x1ul << CLK_SYSCLK0_USBHEN_Pos)                 /*!< CLK_T::SYSCLK0: USBHEN Mask            */

#define CLK_SYSCLK0_HUSBH0EN_Pos         (21)                                              /*!< CLK_T::SYSCLK0: HUSBH0EN Position      */
#define CLK_SYSCLK0_HUSBH0EN_Msk         (0x1ul << CLK_SYSCLK0_HUSBH0EN_Pos)               /*!< CLK_T::SYSCLK0: HUSBH0EN Mask          */

#define CLK_SYSCLK0_HUSBH1EN_Pos         (22)                                              /*!< CLK_T::SYSCLK0: HUSBH1EN Position      */
#define CLK_SYSCLK0_HUSBH1EN_Msk         (0x1ul << CLK_SYSCLK0_HUSBH1EN_Pos)               /*!< CLK_T::SYSCLK0: HUSBH1EN Mask          */

#define CLK_SYSCLK0_GFXEN_Pos            (24)                                              /*!< CLK_T::SYSCLK0: GFXEN Position         */
#define CLK_SYSCLK0_GFXEN_Msk            (0x1ul << CLK_SYSCLK0_GFXEN_Pos)                  /*!< CLK_T::SYSCLK0: GFXEN Mask             */

#define CLK_SYSCLK0_VDECEN_Pos           (25)                                              /*!< CLK_T::SYSCLK0: VDECEN Position        */
#define CLK_SYSCLK0_VDECEN_Msk           (0x1ul << CLK_SYSCLK0_VDECEN_Pos)                 /*!< CLK_T::SYSCLK0: VDECEN Mask            */

#define CLK_SYSCLK0_DCUEN_Pos            (26)                                              /*!< CLK_T::SYSCLK0: DCUEN Position         */
#define CLK_SYSCLK0_DCUEN_Msk            (0x1ul << CLK_SYSCLK0_DCUEN_Pos)                  /*!< CLK_T::SYSCLK0: DCUEN Mask             */

#define CLK_SYSCLK0_GMAC0EN_Pos          (27)                                              /*!< CLK_T::SYSCLK0: GMAC0EN Position       */
#define CLK_SYSCLK0_GMAC0EN_Msk          (0x1ul << CLK_SYSCLK0_GMAC0EN_Pos)                /*!< CLK_T::SYSCLK0: GMAC0EN Mask           */

#define CLK_SYSCLK0_GMAC1EN_Pos          (28)                                              /*!< CLK_T::SYSCLK0: GMAC1EN Position       */
#define CLK_SYSCLK0_GMAC1EN_Msk          (0x1ul << CLK_SYSCLK0_GMAC1EN_Pos)                /*!< CLK_T::SYSCLK0: GMAC1EN Mask           */

#define CLK_SYSCLK0_CCAP0EN_Pos          (29)                                              /*!< CLK_T::SYSCLK0: CCAP0EN Position       */
#define CLK_SYSCLK0_CCAP0EN_Msk          (0x1ul << CLK_SYSCLK0_CCAP0EN_Pos)                /*!< CLK_T::SYSCLK0: CCAP0EN Mask           */

#define CLK_SYSCLK0_CCAP1EN_Pos          (30)                                              /*!< CLK_T::SYSCLK0: CCAP1EN Position       */
#define CLK_SYSCLK0_CCAP1EN_Msk          (0x1ul << CLK_SYSCLK0_CCAP1EN_Pos)                /*!< CLK_T::SYSCLK0: CCAP1EN Mask           */

#define CLK_SYSCLK1_PDMA0EN_Pos          (0)                                               /*!< CLK_T::SYSCLK1: PDMA0EN Position       */
#define CLK_SYSCLK1_PDMA0EN_Msk          (0x1ul << CLK_SYSCLK1_PDMA0EN_Pos)                /*!< CLK_T::SYSCLK1: PDMA0EN Mask           */

#define CLK_SYSCLK1_PDMA1EN_Pos          (1)                                               /*!< CLK_T::SYSCLK1: PDMA1EN Position       */
#define CLK_SYSCLK1_PDMA1EN_Msk          (0x1ul << CLK_SYSCLK1_PDMA1EN_Pos)                /*!< CLK_T::SYSCLK1: PDMA1EN Mask           */

#define CLK_SYSCLK1_PDMA2EN_Pos          (2)                                               /*!< CLK_T::SYSCLK1: PDMA2EN Position       */
#define CLK_SYSCLK1_PDMA2EN_Msk          (0x1ul << CLK_SYSCLK1_PDMA2EN_Pos)                /*!< CLK_T::SYSCLK1: PDMA2EN Mask           */

#define CLK_SYSCLK1_PDMA3EN_Pos          (3)                                               /*!< CLK_T::SYSCLK1: PDMA3EN Position       */
#define CLK_SYSCLK1_PDMA3EN_Msk          (0x1ul << CLK_SYSCLK1_PDMA3EN_Pos)                /*!< CLK_T::SYSCLK1: PDMA3EN Mask           */

#define CLK_SYSCLK1_WH0CKEN_Pos          (4)                                               /*!< CLK_T::SYSCLK1: WH0CKEN Position       */
#define CLK_SYSCLK1_WH0CKEN_Msk          (0x1ul << CLK_SYSCLK1_WH0CKEN_Pos)                /*!< CLK_T::SYSCLK1: WH0CKEN Mask           */

#define CLK_SYSCLK1_WH1CKEN_Pos          (5)                                               /*!< CLK_T::SYSCLK1: WH1CKEN Position       */
#define CLK_SYSCLK1_WH1CKEN_Msk          (0x1ul << CLK_SYSCLK1_WH1CKEN_Pos)                /*!< CLK_T::SYSCLK1: WH1CKEN Mask           */

#define CLK_SYSCLK1_HWSCKEN_Pos          (6)                                               /*!< CLK_T::SYSCLK1: HWSCKEN Position       */
#define CLK_SYSCLK1_HWSCKEN_Msk          (0x1ul << CLK_SYSCLK1_HWSCKEN_Pos)                /*!< CLK_T::SYSCLK1: HWSCKEN Mask           */

#define CLK_SYSCLK1_EBICKEN_Pos          (7)                                               /*!< CLK_T::SYSCLK1: EBICKEN Position       */
#define CLK_SYSCLK1_EBICKEN_Msk          (0x1ul << CLK_SYSCLK1_EBICKEN_Pos)                /*!< CLK_T::SYSCLK1: EBICKEN Mask           */

#define CLK_SYSCLK1_SRAM0CKEN_Pos        (8)                                               /*!< CLK_T::SYSCLK1: SRAM0CKEN Position     */
#define CLK_SYSCLK1_SRAM0CKEN_Msk        (0x1ul << CLK_SYSCLK1_SRAM0CKEN_Pos)              /*!< CLK_T::SYSCLK1: SRAM0CKEN Mask         */

#define CLK_SYSCLK1_SRAM1CKEN_Pos        (9)                                               /*!< CLK_T::SYSCLK1: SRAM1CKEN Position     */
#define CLK_SYSCLK1_SRAM1CKEN_Msk        (0x1ul << CLK_SYSCLK1_SRAM1CKEN_Pos)              /*!< CLK_T::SYSCLK1: SRAM1CKEN Mask         */

#define CLK_SYSCLK1_ROMCKEN_Pos          (10)                                              /*!< CLK_T::SYSCLK1: ROMCKEN Position       */
#define CLK_SYSCLK1_ROMCKEN_Msk          (0x1ul << CLK_SYSCLK1_ROMCKEN_Pos)                /*!< CLK_T::SYSCLK1: ROMCKEN Mask           */

#define CLK_SYSCLK1_TRACKEN_Pos          (11)                                              /*!< CLK_T::SYSCLK1: TRACKEN Position       */
#define CLK_SYSCLK1_TRACKEN_Msk          (0x1ul << CLK_SYSCLK1_TRACKEN_Pos)                /*!< CLK_T::SYSCLK1: TRACKEN Mask           */

#define CLK_SYSCLK1_DBGCKEN_Pos          (12)                                              /*!< CLK_T::SYSCLK1: DBGCKEN Position       */
#define CLK_SYSCLK1_DBGCKEN_Msk          (0x1ul << CLK_SYSCLK1_DBGCKEN_Pos)                /*!< CLK_T::SYSCLK1: DBGCKEN Mask           */

#define CLK_SYSCLK1_CLKOCKEN_Pos         (13)                                              /*!< CLK_T::SYSCLK1: CLKOCKEN Position      */
#define CLK_SYSCLK1_CLKOCKEN_Msk         (0x1ul << CLK_SYSCLK1_CLKOCKEN_Pos)               /*!< CLK_T::SYSCLK1: CLKOCKEN Mask          */

#define CLK_SYSCLK1_GTMRCKEN_Pos         (14)                                              /*!< CLK_T::SYSCLK1: GTMRCKEN Position      */
#define CLK_SYSCLK1_GTMRCKEN_Msk         (0x1ul << CLK_SYSCLK1_GTMRCKEN_Pos)               /*!< CLK_T::SYSCLK1: GTMRCKEN Mask          */

#define CLK_SYSCLK1_GPACKEN_Pos          (16)                                              /*!< CLK_T::SYSCLK1: GPACKEN Position       */
#define CLK_SYSCLK1_GPACKEN_Msk          (0x1ul << CLK_SYSCLK1_GPACKEN_Pos)                /*!< CLK_T::SYSCLK1: GPACKEN Mask           */

#define CLK_SYSCLK1_GPBCKEN_Pos          (17)                                              /*!< CLK_T::SYSCLK1: GPBCKEN Position       */
#define CLK_SYSCLK1_GPBCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPBCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPBCKEN Mask           */

#define CLK_SYSCLK1_GPCCKEN_Pos          (18)                                              /*!< CLK_T::SYSCLK1: GPCCKEN Position       */
#define CLK_SYSCLK1_GPCCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPCCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPCCKEN Mask           */

#define CLK_SYSCLK1_GPDCKEN_Pos          (19)                                              /*!< CLK_T::SYSCLK1: GPDCKEN Position       */
#define CLK_SYSCLK1_GPDCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPDCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPDCKEN Mask           */

#define CLK_SYSCLK1_GPECKEN_Pos          (20)                                              /*!< CLK_T::SYSCLK1: GPECKEN Position       */
#define CLK_SYSCLK1_GPECKEN_Msk          (0x1ul << CLK_SYSCLK1_GPECKEN_Pos)                /*!< CLK_T::SYSCLK1: GPECKEN Mask           */

#define CLK_SYSCLK1_GPFCKEN_Pos          (21)                                              /*!< CLK_T::SYSCLK1: GPFCKEN Position       */
#define CLK_SYSCLK1_GPFCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPFCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPFCKEN Mask           */

#define CLK_SYSCLK1_GPGCKEN_Pos          (22)                                              /*!< CLK_T::SYSCLK1: GPGCKEN Position       */
#define CLK_SYSCLK1_GPGCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPGCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPGCKEN Mask           */

#define CLK_SYSCLK1_GPHCKEN_Pos          (23)                                              /*!< CLK_T::SYSCLK1: GPHCKEN Position       */
#define CLK_SYSCLK1_GPHCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPHCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPHCKEN Mask           */

#define CLK_SYSCLK1_GPICKEN_Pos          (24)                                              /*!< CLK_T::SYSCLK1: GPICKEN Position       */
#define CLK_SYSCLK1_GPICKEN_Msk          (0x1ul << CLK_SYSCLK1_GPICKEN_Pos)                /*!< CLK_T::SYSCLK1: GPICKEN Mask           */

#define CLK_SYSCLK1_GPJCKEN_Pos          (25)                                              /*!< CLK_T::SYSCLK1: GPJCKEN Position       */
#define CLK_SYSCLK1_GPJCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPJCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPJCKEN Mask           */

#define CLK_SYSCLK1_GPKCKEN_Pos          (26)                                              /*!< CLK_T::SYSCLK1: GPKCKEN Position       */
#define CLK_SYSCLK1_GPKCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPKCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPKCKEN Mask           */

#define CLK_SYSCLK1_GPLCKEN_Pos          (27)                                              /*!< CLK_T::SYSCLK1: GPLCKEN Position       */
#define CLK_SYSCLK1_GPLCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPLCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPLCKEN Mask           */

#define CLK_SYSCLK1_GPMCKEN_Pos          (28)                                              /*!< CLK_T::SYSCLK1: GPMCKEN Position       */
#define CLK_SYSCLK1_GPMCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPMCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPMCKEN Mask           */

#define CLK_SYSCLK1_GPNCKEN_Pos          (29)                                              /*!< CLK_T::SYSCLK1: GPNCKEN Position       */
#define CLK_SYSCLK1_GPNCKEN_Msk          (0x1ul << CLK_SYSCLK1_GPNCKEN_Pos)                /*!< CLK_T::SYSCLK1: GPNCKEN Mask           */

#define CLK_APBCLK0_TMR0CKEN_Pos         (0)                                               /*!< CLK_T::APBCLK0: TMR0CKEN Position      */
#define CLK_APBCLK0_TMR0CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR0CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR0CKEN Mask          */

#define CLK_APBCLK0_TMR1CKEN_Pos         (1)                                               /*!< CLK_T::APBCLK0: TMR1CKEN Position      */
#define CLK_APBCLK0_TMR1CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR1CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR1CKEN Mask          */

#define CLK_APBCLK0_TMR2CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK0: TMR2CKEN Position      */
#define CLK_APBCLK0_TMR2CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR2CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR2CKEN Mask          */

#define CLK_APBCLK0_TMR3CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK0: TMR3CKEN Position      */
#define CLK_APBCLK0_TMR3CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR3CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR3CKEN Mask          */

#define CLK_APBCLK0_TMR4CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK0: TMR4CKEN Position      */
#define CLK_APBCLK0_TMR4CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR4CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR4CKEN Mask          */

#define CLK_APBCLK0_TMR5CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK0: TMR5CKEN Position      */
#define CLK_APBCLK0_TMR5CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR5CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR5CKEN Mask          */

#define CLK_APBCLK0_TMR6CKEN_Pos         (6)                                               /*!< CLK_T::APBCLK0: TMR6CKEN Position      */
#define CLK_APBCLK0_TMR6CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR6CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR6CKEN Mask          */

#define CLK_APBCLK0_TMR7CKEN_Pos         (7)                                               /*!< CLK_T::APBCLK0: TMR7CKEN Position      */
#define CLK_APBCLK0_TMR7CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR7CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR7CKEN Mask          */

#define CLK_APBCLK0_TMR8CKEN_Pos         (8)                                               /*!< CLK_T::APBCLK0: TMR8CKEN Position      */
#define CLK_APBCLK0_TMR8CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR8CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR8CKEN Mask          */

#define CLK_APBCLK0_TMR9CKEN_Pos         (9)                                               /*!< CLK_T::APBCLK0: TMR9CKEN Position      */
#define CLK_APBCLK0_TMR9CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR9CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR9CKEN Mask          */

#define CLK_APBCLK0_TMR10CKEN_Pos        (10)                                              /*!< CLK_T::APBCLK0: TMR10CKEN Position     */
#define CLK_APBCLK0_TMR10CKEN_Msk        (0x1ul << CLK_APBCLK0_TMR10CKEN_Pos)              /*!< CLK_T::APBCLK0: TMR10CKEN Mask         */

#define CLK_APBCLK0_TMR11CKEN_Pos        (11)                                              /*!< CLK_T::APBCLK0: TMR11CKEN Position     */
#define CLK_APBCLK0_TMR11CKEN_Msk        (0x1ul << CLK_APBCLK0_TMR11CKEN_Pos)              /*!< CLK_T::APBCLK0: TMR11CKEN Mask         */

#define CLK_APBCLK0_UART0CKEN_Pos        (12)                                              /*!< CLK_T::APBCLK0: UART0CKEN Position     */
#define CLK_APBCLK0_UART0CKEN_Msk        (0x1ul << CLK_APBCLK0_UART0CKEN_Pos)              /*!< CLK_T::APBCLK0: UART0CKEN Mask         */

#define CLK_APBCLK0_UART1CKEN_Pos        (13)                                              /*!< CLK_T::APBCLK0: UART1CKEN Position     */
#define CLK_APBCLK0_UART1CKEN_Msk        (0x1ul << CLK_APBCLK0_UART1CKEN_Pos)              /*!< CLK_T::APBCLK0: UART1CKEN Mask         */

#define CLK_APBCLK0_UART2CKEN_Pos        (14)                                              /*!< CLK_T::APBCLK0: UART2CKEN Position     */
#define CLK_APBCLK0_UART2CKEN_Msk        (0x1ul << CLK_APBCLK0_UART2CKEN_Pos)              /*!< CLK_T::APBCLK0: UART2CKEN Mask         */

#define CLK_APBCLK0_UART3CKEN_Pos        (15)                                              /*!< CLK_T::APBCLK0: UART3CKEN Position     */
#define CLK_APBCLK0_UART3CKEN_Msk        (0x1ul << CLK_APBCLK0_UART3CKEN_Pos)              /*!< CLK_T::APBCLK0: UART3CKEN Mask         */

#define CLK_APBCLK0_UART4CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK0: UART4CKEN Position     */
#define CLK_APBCLK0_UART4CKEN_Msk        (0x1ul << CLK_APBCLK0_UART4CKEN_Pos)              /*!< CLK_T::APBCLK0: UART4CKEN Mask         */

#define CLK_APBCLK0_UART5CKEN_Pos        (17)                                              /*!< CLK_T::APBCLK0: UART5CKEN Position     */
#define CLK_APBCLK0_UART5CKEN_Msk        (0x1ul << CLK_APBCLK0_UART5CKEN_Pos)              /*!< CLK_T::APBCLK0: UART5CKEN Mask         */

#define CLK_APBCLK0_UART6CKEN_Pos        (18)                                              /*!< CLK_T::APBCLK0: UART6CKEN Position     */
#define CLK_APBCLK0_UART6CKEN_Msk        (0x1ul << CLK_APBCLK0_UART6CKEN_Pos)              /*!< CLK_T::APBCLK0: UART6CKEN Mask         */

#define CLK_APBCLK0_UART7CKEN_Pos        (19)                                              /*!< CLK_T::APBCLK0: UART7CKEN Position     */
#define CLK_APBCLK0_UART7CKEN_Msk        (0x1ul << CLK_APBCLK0_UART7CKEN_Pos)              /*!< CLK_T::APBCLK0: UART7CKEN Mask         */

#define CLK_APBCLK0_UART8CKEN_Pos        (20)                                              /*!< CLK_T::APBCLK0: UART8CKEN Position     */
#define CLK_APBCLK0_UART8CKEN_Msk        (0x1ul << CLK_APBCLK0_UART8CKEN_Pos)              /*!< CLK_T::APBCLK0: UART8CKEN Mask         */

#define CLK_APBCLK0_UART9CKEN_Pos        (21)                                              /*!< CLK_T::APBCLK0: UART9CKEN Position     */
#define CLK_APBCLK0_UART9CKEN_Msk        (0x1ul << CLK_APBCLK0_UART9CKEN_Pos)              /*!< CLK_T::APBCLK0: UART9CKEN Mask         */

#define CLK_APBCLK0_UART10CKEN_Pos       (22)                                              /*!< CLK_T::APBCLK0: UART10CKEN Position    */
#define CLK_APBCLK0_UART10CKEN_Msk       (0x1ul << CLK_APBCLK0_UART10CKEN_Pos)             /*!< CLK_T::APBCLK0: UART10CKEN Mask        */

#define CLK_APBCLK0_UART11CKEN_Pos       (23)                                              /*!< CLK_T::APBCLK0: UART11CKEN Position    */
#define CLK_APBCLK0_UART11CKEN_Msk       (0x1ul << CLK_APBCLK0_UART11CKEN_Pos)             /*!< CLK_T::APBCLK0: UART11CKEN Mask        */

#define CLK_APBCLK0_UART12CKEN_Pos       (24)                                              /*!< CLK_T::APBCLK0: UART12CKEN Position    */
#define CLK_APBCLK0_UART12CKEN_Msk       (0x1ul << CLK_APBCLK0_UART12CKEN_Pos)             /*!< CLK_T::APBCLK0: UART12CKEN Mask        */

#define CLK_APBCLK0_UART13CKEN_Pos       (25)                                              /*!< CLK_T::APBCLK0: UART13CKEN Position    */
#define CLK_APBCLK0_UART13CKEN_Msk       (0x1ul << CLK_APBCLK0_UART13CKEN_Pos)             /*!< CLK_T::APBCLK0: UART13CKEN Mask        */

#define CLK_APBCLK0_UART14CKEN_Pos       (26)                                              /*!< CLK_T::APBCLK0: UART14CKEN Position    */
#define CLK_APBCLK0_UART14CKEN_Msk       (0x1ul << CLK_APBCLK0_UART14CKEN_Pos)             /*!< CLK_T::APBCLK0: UART14CKEN Mask        */

#define CLK_APBCLK0_UART15CKEN_Pos       (27)                                              /*!< CLK_T::APBCLK0: UART15CKEN Position    */
#define CLK_APBCLK0_UART15CKEN_Msk       (0x1ul << CLK_APBCLK0_UART15CKEN_Pos)             /*!< CLK_T::APBCLK0: UART15CKEN Mask        */

#define CLK_APBCLK0_UART16CKEN_Pos       (28)                                              /*!< CLK_T::APBCLK0: UART16CKEN Position    */
#define CLK_APBCLK0_UART16CKEN_Msk       (0x1ul << CLK_APBCLK0_UART16CKEN_Pos)             /*!< CLK_T::APBCLK0: UART16CKEN Mask        */

#define CLK_APBCLK0_RTCCKEN_Pos          (29)                                              /*!< CLK_T::APBCLK0: RTCCKEN Position       */
#define CLK_APBCLK0_RTCCKEN_Msk          (0x1ul << CLK_APBCLK0_RTCCKEN_Pos)                /*!< CLK_T::APBCLK0: RTCCKEN Mask           */

#define CLK_APBCLK0_DDRPCKEN_Pos         (30)                                              /*!< CLK_T::APBCLK0: DDRPCKEN Position      */
#define CLK_APBCLK0_DDRPCKEN_Msk         (0x1ul << CLK_APBCLK0_DDRPCKEN_Pos)               /*!< CLK_T::APBCLK0: DDRPCKEN Mask          */

#define CLK_APBCLK0_KPICKEN_Pos          (31)                                              /*!< CLK_T::APBCLK0: KPICKEN Position       */
#define CLK_APBCLK0_KPICKEN_Msk          (0x1ul << CLK_APBCLK0_KPICKEN_Pos)                /*!< CLK_T::APBCLK0: KPICKEN Mask           */

#define CLK_APBCLK1_I2C0CKEN_Pos         (0)                                               /*!< CLK_T::APBCLK1: I2C0CKEN Position      */
#define CLK_APBCLK1_I2C0CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C0CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C0CKEN Mask          */

#define CLK_APBCLK1_I2C1CKEN_Pos         (1)                                               /*!< CLK_T::APBCLK1: I2C1CKEN Position      */
#define CLK_APBCLK1_I2C1CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C1CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C1CKEN Mask          */

#define CLK_APBCLK1_I2C2CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK1: I2C2CKEN Position      */
#define CLK_APBCLK1_I2C2CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C2CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C2CKEN Mask          */

#define CLK_APBCLK1_I2C3CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK1: I2C3CKEN Position      */
#define CLK_APBCLK1_I2C3CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C3CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C3CKEN Mask          */

#define CLK_APBCLK1_I2C4CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK1: I2C4CKEN Position      */
#define CLK_APBCLK1_I2C4CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C4CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C4CKEN Mask          */

#define CLK_APBCLK1_I2C5CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK1: I2C5CKEN Position      */
#define CLK_APBCLK1_I2C5CKEN_Msk         (0x1ul << CLK_APBCLK1_I2C5CKEN_Pos)               /*!< CLK_T::APBCLK1: I2C5CKEN Mask          */

#define CLK_APBCLK1_QSPI0CKEN_Pos        (6)                                               /*!< CLK_T::APBCLK1: QSPI0CKEN Position     */
#define CLK_APBCLK1_QSPI0CKEN_Msk        (0x1ul << CLK_APBCLK1_QSPI0CKEN_Pos)              /*!< CLK_T::APBCLK1: QSPI0CKEN Mask         */

#define CLK_APBCLK1_QSPI1CKEN_Pos        (7)                                               /*!< CLK_T::APBCLK1: QSPI1CKEN Position     */
#define CLK_APBCLK1_QSPI1CKEN_Msk        (0x1ul << CLK_APBCLK1_QSPI1CKEN_Pos)              /*!< CLK_T::APBCLK1: QSPI1CKEN Mask         */

#define CLK_APBCLK1_SC0CKEN_Pos          (12)                                              /*!< CLK_T::APBCLK1: SC0CKEN Position       */
#define CLK_APBCLK1_SC0CKEN_Msk          (0x1ul << CLK_APBCLK1_SC0CKEN_Pos)                /*!< CLK_T::APBCLK1: SC0CKEN Mask           */

#define CLK_APBCLK1_SC1CKEN_Pos          (13)                                              /*!< CLK_T::APBCLK1: SC1CKEN Position       */
#define CLK_APBCLK1_SC1CKEN_Msk          (0x1ul << CLK_APBCLK1_SC1CKEN_Pos)                /*!< CLK_T::APBCLK1: SC1CKEN Mask           */

#define CLK_APBCLK1_WDT0CKEN_Pos         (16)                                              /*!< CLK_T::APBCLK1: WDT0CKEN Position      */
#define CLK_APBCLK1_WDT0CKEN_Msk         (0x1ul << CLK_APBCLK1_WDT0CKEN_Pos)               /*!< CLK_T::APBCLK1: WDT0CKEN Mask          */

#define CLK_APBCLK1_WDT1CKEN_Pos         (17)                                              /*!< CLK_T::APBCLK1: WDT1CKEN Position      */
#define CLK_APBCLK1_WDT1CKEN_Msk         (0x1ul << CLK_APBCLK1_WDT1CKEN_Pos)               /*!< CLK_T::APBCLK1: WDT1CKEN Mask          */

#define CLK_APBCLK1_WDT2CKEN_Pos         (18)                                              /*!< CLK_T::APBCLK1: WDT2CKEN Position      */
#define CLK_APBCLK1_WDT2CKEN_Msk         (0x1ul << CLK_APBCLK1_WDT2CKEN_Pos)               /*!< CLK_T::APBCLK1: WDT2CKEN Mask          */

#define CLK_APBCLK1_EPWM0CKEN_Pos        (24)                                              /*!< CLK_T::APBCLK1: EPWM0CKEN Position     */
#define CLK_APBCLK1_EPWM0CKEN_Msk        (0x1ul << CLK_APBCLK1_EPWM0CKEN_Pos)              /*!< CLK_T::APBCLK1: EPWM0CKEN Mask         */

#define CLK_APBCLK1_EPWM1CKEN_Pos        (25)                                              /*!< CLK_T::APBCLK1: EPWM1CKEN Position     */
#define CLK_APBCLK1_EPWM1CKEN_Msk        (0x1ul << CLK_APBCLK1_EPWM1CKEN_Pos)              /*!< CLK_T::APBCLK1: EPWM1CKEN Mask         */

#define CLK_APBCLK1_EPWM2CKEN_Pos        (26)                                              /*!< CLK_T::APBCLK1: EPWM2CKEN Position     */
#define CLK_APBCLK1_EPWM2CKEN_Msk        (0x1ul << CLK_APBCLK1_EPWM2CKEN_Pos)              /*!< CLK_T::APBCLK1: EPWM2CKEN Mask         */

#define CLK_APBCLK2_I2S0CKEN_Pos         (0)                                               /*!< CLK_T::APBCLK2: I2S0CKEN Position      */
#define CLK_APBCLK2_I2S0CKEN_Msk         (0x1ul << CLK_APBCLK2_I2S0CKEN_Pos)               /*!< CLK_T::APBCLK2: I2S0CKEN Mask          */

#define CLK_APBCLK2_I2S1CKEN_Pos         (1)                                               /*!< CLK_T::APBCLK2: I2S1CKEN Position      */
#define CLK_APBCLK2_I2S1CKEN_Msk         (0x1ul << CLK_APBCLK2_I2S1CKEN_Pos)               /*!< CLK_T::APBCLK2: I2S1CKEN Mask          */

#define CLK_APBCLK2_SSMCCEN_Pos          (2)                                               /*!< CLK_T::APBCLK2: SSMCCEN Position       */
#define CLK_APBCLK2_SSMCCEN_Msk          (0x1ul << CLK_APBCLK2_SSMCCEN_Pos)                /*!< CLK_T::APBCLK2: SSMCCEN Mask           */

#define CLK_APBCLK2_SSPCCEN_Pos          (3)                                               /*!< CLK_T::APBCLK2: SSPCCEN Position       */
#define CLK_APBCLK2_SSPCCEN_Msk          (0x1ul << CLK_APBCLK2_SSPCCEN_Pos)                /*!< CLK_T::APBCLK2: SSPCCEN Mask           */

#define CLK_APBCLK2_SPI0CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK2: SPI0CKEN Position      */
#define CLK_APBCLK2_SPI0CKEN_Msk         (0x1ul << CLK_APBCLK2_SPI0CKEN_Pos)               /*!< CLK_T::APBCLK2: SPI0CKEN Mask          */

#define CLK_APBCLK2_SPI1CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK2: SPI1CKEN Position      */
#define CLK_APBCLK2_SPI1CKEN_Msk         (0x1ul << CLK_APBCLK2_SPI1CKEN_Pos)               /*!< CLK_T::APBCLK2: SPI1CKEN Mask          */

#define CLK_APBCLK2_SPI2CKEN_Pos         (6)                                               /*!< CLK_T::APBCLK2: SPI2CKEN Position      */
#define CLK_APBCLK2_SPI2CKEN_Msk         (0x1ul << CLK_APBCLK2_SPI2CKEN_Pos)               /*!< CLK_T::APBCLK2: SPI2CKEN Mask          */

#define CLK_APBCLK2_SPI3CKEN_Pos         (7)                                               /*!< CLK_T::APBCLK2: SPI3CKEN Position      */
#define CLK_APBCLK2_SPI3CKEN_Msk         (0x1ul << CLK_APBCLK2_SPI3CKEN_Pos)               /*!< CLK_T::APBCLK2: SPI3CKEN Mask          */

#define CLK_APBCLK2_ECAP0CKEN_Pos        (8)                                               /*!< CLK_T::APBCLK2: ECAP0CKEN Position     */
#define CLK_APBCLK2_ECAP0CKEN_Msk        (0x1ul << CLK_APBCLK2_ECAP0CKEN_Pos)              /*!< CLK_T::APBCLK2: ECAP0CKEN Mask         */

#define CLK_APBCLK2_ECAP1CKEN_Pos        (9)                                               /*!< CLK_T::APBCLK2: ECAP1CKEN Position     */
#define CLK_APBCLK2_ECAP1CKEN_Msk        (0x1ul << CLK_APBCLK2_ECAP1CKEN_Pos)              /*!< CLK_T::APBCLK2: ECAP1CKEN Mask         */

#define CLK_APBCLK2_ECAP2CKEN_Pos        (10)                                              /*!< CLK_T::APBCLK2: ECAP2CKEN Position     */
#define CLK_APBCLK2_ECAP2CKEN_Msk        (0x1ul << CLK_APBCLK2_ECAP2CKEN_Pos)              /*!< CLK_T::APBCLK2: ECAP2CKEN Mask         */

#define CLK_APBCLK2_QEI0CKEN_Pos         (12)                                              /*!< CLK_T::APBCLK2: QEI0CKEN Position      */
#define CLK_APBCLK2_QEI0CKEN_Msk         (0x1ul << CLK_APBCLK2_QEI0CKEN_Pos)               /*!< CLK_T::APBCLK2: QEI0CKEN Mask          */

#define CLK_APBCLK2_QEI1CKEN_Pos         (13)                                              /*!< CLK_T::APBCLK2: QEI1CKEN Position      */
#define CLK_APBCLK2_QEI1CKEN_Msk         (0x1ul << CLK_APBCLK2_QEI1CKEN_Pos)               /*!< CLK_T::APBCLK2: QEI1CKEN Mask          */

#define CLK_APBCLK2_QEI2CKEN_Pos         (14)                                              /*!< CLK_T::APBCLK2: QEI2CKEN Position      */
#define CLK_APBCLK2_QEI2CKEN_Msk         (0x1ul << CLK_APBCLK2_QEI2CKEN_Pos)               /*!< CLK_T::APBCLK2: QEI2CKEN Mask          */

#define CLK_APBCLK2_ADCCKEN_Pos          (24)                                              /*!< CLK_T::APBCLK2: ADCCKEN Position       */
#define CLK_APBCLK2_ADCCKEN_Msk          (0x1ul << CLK_APBCLK2_ADCCKEN_Pos)                /*!< CLK_T::APBCLK2: ADCCKEN Mask           */

#define CLK_APBCLK2_EADCCKEN_Pos         (25)                                              /*!< CLK_T::APBCLK2: EADCCKEN Position      */
#define CLK_APBCLK2_EADCCKEN_Msk         (0x1ul << CLK_APBCLK2_EADCCKEN_Pos)               /*!< CLK_T::APBCLK2: EADCCKEN Mask          */

#define CLK_CLKSEL0_CA35CKSEL_Pos        (0)                                               /*!< CLK_T::CLKSEL0: CA35CKSEL Position     */
#define CLK_CLKSEL0_CA35CKSEL_Msk        (0x3ul << CLK_CLKSEL0_CA35CKSEL_Pos)              /*!< CLK_T::CLKSEL0: CA35CKSEL Mask         */

#define CLK_CLKSEL0_SYSCK0SEL_Pos        (2)                                               /*!< CLK_T::CLKSEL0: SYSCK0SEL Position     */
#define CLK_CLKSEL0_SYSCK0SEL_Msk        (0x1ul << CLK_CLKSEL0_SYSCK0SEL_Pos)              /*!< CLK_T::CLKSEL0: SYSCK0SEL Mask         */

#define CLK_CLKSEL0_LVRDBSEL_Pos         (3)                                               /*!< CLK_T::CLKSEL0: LVRDBSEL Position      */
#define CLK_CLKSEL0_LVRDBSEL_Msk         (0x1ul << CLK_CLKSEL0_LVRDBSEL_Pos)               /*!< CLK_T::CLKSEL0: LVRDBSEL Mask          */

#define CLK_CLKSEL0_SYSCK1SEL_Pos        (4)                                               /*!< CLK_T::CLKSEL0: SYSCK1SEL Position     */
#define CLK_CLKSEL0_SYSCK1SEL_Msk        (0x1ul << CLK_CLKSEL0_SYSCK1SEL_Pos)              /*!< CLK_T::CLKSEL0: SYSCK1SEL Mask         */

#define CLK_CLKSEL0_RTPSTSEL_Pos         (8)                                               /*!< CLK_T::CLKSEL0: RTPSTSEL Position      */
#define CLK_CLKSEL0_RTPSTSEL_Msk         (0x7ul << CLK_CLKSEL0_RTPSTSEL_Pos)               /*!< CLK_T::CLKSEL0: RTPSTSEL Mask          */

#define CLK_CLKSEL0_CCAP0SEL_Pos         (12)                                              /*!< CLK_T::CLKSEL0: CCAP0SEL Position      */
#define CLK_CLKSEL0_CCAP0SEL_Msk         (0x3ul << CLK_CLKSEL0_CCAP0SEL_Pos)               /*!< CLK_T::CLKSEL0: CCAP0SEL Mask          */

#define CLK_CLKSEL0_CCAP1SEL_Pos         (14)                                              /*!< CLK_T::CLKSEL0: CCAP1SEL Position      */
#define CLK_CLKSEL0_CCAP1SEL_Msk         (0x3ul << CLK_CLKSEL0_CCAP1SEL_Pos)               /*!< CLK_T::CLKSEL0: CCAP1SEL Mask          */

#define CLK_CLKSEL0_SD0SEL_Pos           (16)                                              /*!< CLK_T::CLKSEL0: SD0SEL Position        */
#define CLK_CLKSEL0_SD0SEL_Msk           (0x3ul << CLK_CLKSEL0_SD0SEL_Pos)                 /*!< CLK_T::CLKSEL0: SD0SEL Mask            */

#define CLK_CLKSEL0_SD1SEL_Pos           (18)                                              /*!< CLK_T::CLKSEL0: SD1SEL Position        */
#define CLK_CLKSEL0_SD1SEL_Msk           (0x3ul << CLK_CLKSEL0_SD1SEL_Pos)                 /*!< CLK_T::CLKSEL0: SD1SEL Mask            */

#define CLK_CLKSEL0_DCUSEL_Pos           (24)                                              /*!< CLK_T::CLKSEL0: DCUSEL Position       */
#define CLK_CLKSEL0_DCUSEL_Msk           (0x1ul << CLK_CLKSEL0_DCUSEL_Pos)                 /*!< CLK_T::CLKSEL0: DCUSEL Mask           */

#define CLK_CLKSEL0_GFXSEL_Pos           (26)                                              /*!< CLK_T::CLKSEL0: GFXSEL Position        */
#define CLK_CLKSEL0_GFXSEL_Msk           (0x1ul << CLK_CLKSEL0_GFXSEL_Pos)                 /*!< CLK_T::CLKSEL0: GFXSEL Mask            */

#define CLK_CLKSEL0_DBGSEL_Pos           (27)                                              /*!< CLK_T::CLKSEL0: DBGSEL Position        */
#define CLK_CLKSEL0_DBGSEL_Msk           (0x1ul << CLK_CLKSEL0_DBGSEL_Pos)                 /*!< CLK_T::CLKSEL0: DBGSEL Mask            */

#define CLK_CLKSEL1_TMR0SEL_Pos          (0)                                               /*!< CLK_T::CLKSEL1: TMR0SEL Position       */
#define CLK_CLKSEL1_TMR0SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR0SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR0SEL Mask           */

#define CLK_CLKSEL1_TMR1SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL1: TMR1SEL Position       */
#define CLK_CLKSEL1_TMR1SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR1SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR1SEL Mask           */

#define CLK_CLKSEL1_TMR2SEL_Pos          (8)                                               /*!< CLK_T::CLKSEL1: TMR2SEL Position       */
#define CLK_CLKSEL1_TMR2SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR2SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR2SEL Mask           */

#define CLK_CLKSEL1_TMR3SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL1: TMR3SEL Position       */
#define CLK_CLKSEL1_TMR3SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR3SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR3SEL Mask           */

#define CLK_CLKSEL1_TMR4SEL_Pos          (16)                                              /*!< CLK_T::CLKSEL1: TMR4SEL Position       */
#define CLK_CLKSEL1_TMR4SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR4SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR4SEL Mask           */

#define CLK_CLKSEL1_TMR5SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL1: TMR5SEL Position       */
#define CLK_CLKSEL1_TMR5SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR5SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR5SEL Mask           */

#define CLK_CLKSEL1_TMR6SEL_Pos          (24)                                              /*!< CLK_T::CLKSEL1: TMR6SEL Position       */
#define CLK_CLKSEL1_TMR6SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR6SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR6SEL Mask           */

#define CLK_CLKSEL1_TMR7SEL_Pos          (28)                                              /*!< CLK_T::CLKSEL1: TMR7SEL Position       */
#define CLK_CLKSEL1_TMR7SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR7SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR7SEL Mask           */

#define CLK_CLKSEL2_TMR8SEL_Pos          (0)                                               /*!< CLK_T::CLKSEL2: TMR8SEL Position       */
#define CLK_CLKSEL2_TMR8SEL_Msk          (0x7ul << CLK_CLKSEL2_TMR8SEL_Pos)                /*!< CLK_T::CLKSEL2: TMR8SEL Mask           */

#define CLK_CLKSEL2_TMR9SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL2: TMR9SEL Position       */
#define CLK_CLKSEL2_TMR9SEL_Msk          (0x7ul << CLK_CLKSEL2_TMR9SEL_Pos)                /*!< CLK_T::CLKSEL2: TMR9SEL Mask           */

#define CLK_CLKSEL2_TMR10SEL_Pos         (8)                                               /*!< CLK_T::CLKSEL2: TMR10SEL Position      */
#define CLK_CLKSEL2_TMR10SEL_Msk         (0x7ul << CLK_CLKSEL2_TMR10SEL_Pos)               /*!< CLK_T::CLKSEL2: TMR10SEL Mask          */

#define CLK_CLKSEL2_TMR11SEL_Pos         (12)                                              /*!< CLK_T::CLKSEL2: TMR11SEL Position      */
#define CLK_CLKSEL2_TMR11SEL_Msk         (0x7ul << CLK_CLKSEL2_TMR11SEL_Pos)               /*!< CLK_T::CLKSEL2: TMR11SEL Mask          */

#define CLK_CLKSEL2_UART0SEL_Pos         (16)                                              /*!< CLK_T::CLKSEL2: UART0SEL Position      */
#define CLK_CLKSEL2_UART0SEL_Msk         (0x3ul << CLK_CLKSEL2_UART0SEL_Pos)               /*!< CLK_T::CLKSEL2: UART0SEL Mask          */

#define CLK_CLKSEL2_UART1SEL_Pos         (18)                                              /*!< CLK_T::CLKSEL2: UART1SEL Position      */
#define CLK_CLKSEL2_UART1SEL_Msk         (0x3ul << CLK_CLKSEL2_UART1SEL_Pos)               /*!< CLK_T::CLKSEL2: UART1SEL Mask          */

#define CLK_CLKSEL2_UART2SEL_Pos         (20)                                              /*!< CLK_T::CLKSEL2: UART2SEL Position      */
#define CLK_CLKSEL2_UART2SEL_Msk         (0x3ul << CLK_CLKSEL2_UART2SEL_Pos)               /*!< CLK_T::CLKSEL2: UART2SEL Mask          */

#define CLK_CLKSEL2_UART3SEL_Pos         (22)                                              /*!< CLK_T::CLKSEL2: UART3SEL Position      */
#define CLK_CLKSEL2_UART3SEL_Msk         (0x3ul << CLK_CLKSEL2_UART3SEL_Pos)               /*!< CLK_T::CLKSEL2: UART3SEL Mask          */

#define CLK_CLKSEL2_UART4SEL_Pos         (24)                                              /*!< CLK_T::CLKSEL2: UART4SEL Position      */
#define CLK_CLKSEL2_UART4SEL_Msk         (0x3ul << CLK_CLKSEL2_UART4SEL_Pos)               /*!< CLK_T::CLKSEL2: UART4SEL Mask          */

#define CLK_CLKSEL2_UART5SEL_Pos         (26)                                              /*!< CLK_T::CLKSEL2: UART5SEL Position      */
#define CLK_CLKSEL2_UART5SEL_Msk         (0x3ul << CLK_CLKSEL2_UART5SEL_Pos)               /*!< CLK_T::CLKSEL2: UART5SEL Mask          */

#define CLK_CLKSEL2_UART6SEL_Pos         (28)                                              /*!< CLK_T::CLKSEL2: UART6SEL Position      */
#define CLK_CLKSEL2_UART6SEL_Msk         (0x3ul << CLK_CLKSEL2_UART6SEL_Pos)               /*!< CLK_T::CLKSEL2: UART6SEL Mask          */

#define CLK_CLKSEL2_UART7SEL_Pos         (30)                                              /*!< CLK_T::CLKSEL2: UART7SEL Position      */
#define CLK_CLKSEL2_UART7SEL_Msk         (0x3ul << CLK_CLKSEL2_UART7SEL_Pos)               /*!< CLK_T::CLKSEL2: UART7SEL Mask          */

#define CLK_CLKSEL3_UART8SEL_Pos         (0)                                               /*!< CLK_T::CLKSEL3: UART8SEL Position      */
#define CLK_CLKSEL3_UART8SEL_Msk         (0x3ul << CLK_CLKSEL3_UART8SEL_Pos)               /*!< CLK_T::CLKSEL3: UART8SEL Mask          */

#define CLK_CLKSEL3_UART9SEL_Pos         (2)                                               /*!< CLK_T::CLKSEL3: UART9SEL Position      */
#define CLK_CLKSEL3_UART9SEL_Msk         (0x3ul << CLK_CLKSEL3_UART9SEL_Pos)               /*!< CLK_T::CLKSEL3: UART9SEL Mask          */

#define CLK_CLKSEL3_UART10SEL_Pos        (4)                                               /*!< CLK_T::CLKSEL3: UART10SEL Position     */
#define CLK_CLKSEL3_UART10SEL_Msk        (0x3ul << CLK_CLKSEL3_UART10SEL_Pos)              /*!< CLK_T::CLKSEL3: UART10SEL Mask         */

#define CLK_CLKSEL3_UART11SEL_Pos        (6)                                               /*!< CLK_T::CLKSEL3: UART11SEL Position     */
#define CLK_CLKSEL3_UART11SEL_Msk        (0x3ul << CLK_CLKSEL3_UART11SEL_Pos)              /*!< CLK_T::CLKSEL3: UART11SEL Mask         */

#define CLK_CLKSEL3_UART12SEL_Pos        (8)                                               /*!< CLK_T::CLKSEL3: UART12SEL Position     */
#define CLK_CLKSEL3_UART12SEL_Msk        (0x3ul << CLK_CLKSEL3_UART12SEL_Pos)              /*!< CLK_T::CLKSEL3: UART12SEL Mask         */

#define CLK_CLKSEL3_UART13SEL_Pos        (10)                                              /*!< CLK_T::CLKSEL3: UART13SEL Position     */
#define CLK_CLKSEL3_UART13SEL_Msk        (0x3ul << CLK_CLKSEL3_UART13SEL_Pos)              /*!< CLK_T::CLKSEL3: UART13SEL Mask         */

#define CLK_CLKSEL3_UART14SEL_Pos        (12)                                              /*!< CLK_T::CLKSEL3: UART14SEL Position     */
#define CLK_CLKSEL3_UART14SEL_Msk        (0x3ul << CLK_CLKSEL3_UART14SEL_Pos)              /*!< CLK_T::CLKSEL3: UART14SEL Mask         */

#define CLK_CLKSEL3_UART15SEL_Pos        (14)                                              /*!< CLK_T::CLKSEL3: UART15SEL Position     */
#define CLK_CLKSEL3_UART15SEL_Msk        (0x3ul << CLK_CLKSEL3_UART15SEL_Pos)              /*!< CLK_T::CLKSEL3: UART15SEL Mask         */

#define CLK_CLKSEL3_UART16SEL_Pos        (16)                                              /*!< CLK_T::CLKSEL3: UART16SEL Position     */
#define CLK_CLKSEL3_UART16SEL_Msk        (0x3ul << CLK_CLKSEL3_UART16SEL_Pos)              /*!< CLK_T::CLKSEL3: UART16SEL Mask         */

#define CLK_CLKSEL3_WDT0SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL3: WDT0SEL Position       */
#define CLK_CLKSEL3_WDT0SEL_Msk          (0x3ul << CLK_CLKSEL3_WDT0SEL_Pos)                /*!< CLK_T::CLKSEL3: WDT0SEL Mask           */

#define CLK_CLKSEL3_WWDT0SEL_Pos         (22)                                              /*!< CLK_T::CLKSEL3: WWDT0SEL Position      */
#define CLK_CLKSEL3_WWDT0SEL_Msk         (0x3ul << CLK_CLKSEL3_WWDT0SEL_Pos)               /*!< CLK_T::CLKSEL3: WWDT0SEL Mask          */

#define CLK_CLKSEL3_WDT1SEL_Pos          (24)                                              /*!< CLK_T::CLKSEL3: WDT1SEL Position       */
#define CLK_CLKSEL3_WDT1SEL_Msk          (0x3ul << CLK_CLKSEL3_WDT1SEL_Pos)                /*!< CLK_T::CLKSEL3: WDT1SEL Mask           */

#define CLK_CLKSEL3_WWDT1SEL_Pos         (26)                                              /*!< CLK_T::CLKSEL3: WWDT1SEL Position      */
#define CLK_CLKSEL3_WWDT1SEL_Msk         (0x3ul << CLK_CLKSEL3_WWDT1SEL_Pos)               /*!< CLK_T::CLKSEL3: WWDT1SEL Mask          */

#define CLK_CLKSEL3_WDT2SEL_Pos          (28)                                              /*!< CLK_T::CLKSEL3: WDT2SEL Position       */
#define CLK_CLKSEL3_WDT2SEL_Msk          (0x3ul << CLK_CLKSEL3_WDT2SEL_Pos)                /*!< CLK_T::CLKSEL3: WDT2SEL Mask           */

#define CLK_CLKSEL3_WWDT2SEL_Pos         (30)                                              /*!< CLK_T::CLKSEL3: WWDT2SEL Position      */
#define CLK_CLKSEL3_WWDT2SEL_Msk         (0x3ul << CLK_CLKSEL3_WWDT2SEL_Pos)               /*!< CLK_T::CLKSEL3: WWDT2SEL Mask          */

#define CLK_CLKSEL4_SPI0SEL_Pos          (0)                                               /*!< CLK_T::CLKSEL4: SPI0SEL Position       */
#define CLK_CLKSEL4_SPI0SEL_Msk          (0x3ul << CLK_CLKSEL4_SPI0SEL_Pos)                /*!< CLK_T::CLKSEL4: SPI0SEL Mask           */

#define CLK_CLKSEL4_SPI1SEL_Pos          (2)                                               /*!< CLK_T::CLKSEL4: SPI1SEL Position       */
#define CLK_CLKSEL4_SPI1SEL_Msk          (0x3ul << CLK_CLKSEL4_SPI1SEL_Pos)                /*!< CLK_T::CLKSEL4: SPI1SEL Mask           */

#define CLK_CLKSEL4_SPI2SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL4: SPI2SEL Position       */
#define CLK_CLKSEL4_SPI2SEL_Msk          (0x3ul << CLK_CLKSEL4_SPI2SEL_Pos)                /*!< CLK_T::CLKSEL4: SPI2SEL Mask           */

#define CLK_CLKSEL4_SPI3SEL_Pos          (6)                                               /*!< CLK_T::CLKSEL4: SPI3SEL Position       */
#define CLK_CLKSEL4_SPI3SEL_Msk          (0x3ul << CLK_CLKSEL4_SPI3SEL_Pos)                /*!< CLK_T::CLKSEL4: SPI3SEL Mask           */

#define CLK_CLKSEL4_QSPI0SEL_Pos         (8)                                               /*!< CLK_T::CLKSEL4: QSPI0SEL Position      */
#define CLK_CLKSEL4_QSPI0SEL_Msk         (0x3ul << CLK_CLKSEL4_QSPI0SEL_Pos)               /*!< CLK_T::CLKSEL4: QSPI0SEL Mask          */

#define CLK_CLKSEL4_QSPI1SEL_Pos         (10)                                              /*!< CLK_T::CLKSEL4: QSPI1SEL Position      */
#define CLK_CLKSEL4_QSPI1SEL_Msk         (0x3ul << CLK_CLKSEL4_QSPI1SEL_Pos)               /*!< CLK_T::CLKSEL4: QSPI1SEL Mask          */

#define CLK_CLKSEL4_I2S0SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL4: I2S0SEL Position       */
#define CLK_CLKSEL4_I2S0SEL_Msk          (0x3ul << CLK_CLKSEL4_I2S0SEL_Pos)                /*!< CLK_T::CLKSEL4: I2S0SEL Mask           */

#define CLK_CLKSEL4_I2S1SEL_Pos          (14)                                              /*!< CLK_T::CLKSEL4: I2S1SEL Position       */
#define CLK_CLKSEL4_I2S1SEL_Msk          (0x3ul << CLK_CLKSEL4_I2S1SEL_Pos)                /*!< CLK_T::CLKSEL4: I2S1SEL Mask           */

#define CLK_CLKSEL4_CANFD0SEL_Pos        (16)                                              /*!< CLK_T::CLKSEL4: CANFD0SEL Position     */
#define CLK_CLKSEL4_CANFD0SEL_Msk        (0x1ul << CLK_CLKSEL4_CANFD0SEL_Pos)              /*!< CLK_T::CLKSEL4: CANFD0SEL Mask         */

#define CLK_CLKSEL4_CANFD1SEL_Pos        (17)                                              /*!< CLK_T::CLKSEL4: CANFD1SEL Position     */
#define CLK_CLKSEL4_CANFD1SEL_Msk        (0x1ul << CLK_CLKSEL4_CANFD1SEL_Pos)              /*!< CLK_T::CLKSEL4: CANFD1SEL Mask         */

#define CLK_CLKSEL4_CANFD2SEL_Pos        (18)                                              /*!< CLK_T::CLKSEL4: CANFD2SEL Position     */
#define CLK_CLKSEL4_CANFD2SEL_Msk        (0x1ul << CLK_CLKSEL4_CANFD2SEL_Pos)              /*!< CLK_T::CLKSEL4: CANFD2SEL Mask         */

#define CLK_CLKSEL4_CANFD3SEL_Pos        (19)                                              /*!< CLK_T::CLKSEL4: CANFD3SEL Position     */
#define CLK_CLKSEL4_CANFD3SEL_Msk        (0x1ul << CLK_CLKSEL4_CANFD3SEL_Pos)              /*!< CLK_T::CLKSEL4: CANFD3SEL Mask         */

#define CLK_CLKSEL4_CKOSEL_Pos           (24)                                              /*!< CLK_T::CLKSEL4: CKOSEL Position        */
#define CLK_CLKSEL4_CKOSEL_Msk           (0xful << CLK_CLKSEL4_CKOSEL_Pos)                 /*!< CLK_T::CLKSEL4: CKOSEL Mask            */

#define CLK_CLKSEL4_SC0SEL_Pos           (28)                                              /*!< CLK_T::CLKSEL4: SC0SEL Position        */
#define CLK_CLKSEL4_SC0SEL_Msk           (0x1ul << CLK_CLKSEL4_SC0SEL_Pos)                 /*!< CLK_T::CLKSEL4: SC0SEL Mask            */

#define CLK_CLKSEL4_SC1SEL_Pos           (29)                                              /*!< CLK_T::CLKSEL4: SC1SEL Position        */
#define CLK_CLKSEL4_SC1SEL_Msk           (0x1ul << CLK_CLKSEL4_SC1SEL_Pos)                 /*!< CLK_T::CLKSEL4: SC1SEL Mask            */

#define CLK_CLKSEL4_KPISEL_Pos           (30)                                              /*!< CLK_T::CLKSEL4: KPISEL Position        */
#define CLK_CLKSEL4_KPISEL_Msk           (0x1ul << CLK_CLKSEL4_KPISEL_Pos)                 /*!< CLK_T::CLKSEL4: KPISEL Mask            */

#define CLK_CLKDIV0_CANFD0DIV_Pos        (0)                                               /*!< CLK_T::CLKDIV0: CANFD0DIV Position     */
#define CLK_CLKDIV0_CANFD0DIV_Msk        (0x7ul << CLK_CLKDIV0_CANFD0DIV_Pos)              /*!< CLK_T::CLKDIV0: CANFD0DIV Mask         */

#define CLK_CLKDIV0_CANFD1DIV_Pos        (4)                                               /*!< CLK_T::CLKDIV0: CANFD1DIV Position     */
#define CLK_CLKDIV0_CANFD1DIV_Msk        (0x7ul << CLK_CLKDIV0_CANFD1DIV_Pos)              /*!< CLK_T::CLKDIV0: CANFD1DIV Mask         */

#define CLK_CLKDIV0_CANFD2DIV_Pos        (8)                                               /*!< CLK_T::CLKDIV0: CANFD2DIV Position     */
#define CLK_CLKDIV0_CANFD2DIV_Msk        (0x7ul << CLK_CLKDIV0_CANFD2DIV_Pos)              /*!< CLK_T::CLKDIV0: CANFD2DIV Mask         */

#define CLK_CLKDIV0_CANFD3DIV_Pos        (12)                                               /*!< CLK_T::CLKDIV0: CANFD3DIV Position     */
#define CLK_CLKDIV0_CANFD3DIV_Msk        (0x7ul << CLK_CLKDIV0_CANFD3DIV_Pos)              /*!< CLK_T::CLKDIV0: CANFD3DIV Mask         */

#define CLK_CLKDIV0_DCUPDIV_Pos          (16)                                              /*!< CLK_T::CLKDIV0: DCUPDIV Position       */
#define CLK_CLKDIV0_DCUPDIV_Msk          (0x7ul << CLK_CLKDIV0_DCUPDIV_Pos)                /*!< CLK_T::CLKDIV0: DCUPDIV Mask           */

#define CLK_CLKDIV0_ACLK0DIV_Pos         (26)                                              /*!< CLK_T::CLKDIV0: ACLK0DIV Position      */
#define CLK_CLKDIV0_ACLK0DIV_Msk         (0x1ul << CLK_CLKDIV0_ACLK0DIV_Pos)               /*!< CLK_T::CLKDIV0: ACLK0DIV Mask          */

#define CLK_CLKDIV0_EMAC0DIV_Pos         (28)                                              /*!< CLK_T::CLKDIV0: EMAC0DIV Position      */
#define CLK_CLKDIV0_EMAC0DIV_Msk         (0x3ul << CLK_CLKDIV0_EMAC0DIV_Pos)               /*!< CLK_T::CLKDIV0: EMAC0DIV Mask          */

#define CLK_CLKDIV0_EMAC1DIV_Pos         (30)                                              /*!< CLK_T::CLKDIV0: EMAC1DIV Position      */
#define CLK_CLKDIV0_EMAC1DIV_Msk         (0x3ul << CLK_CLKDIV0_EMAC1DIV_Pos)               /*!< CLK_T::CLKDIV0: EMAC1DIV Mask          */

#define CLK_CLKDIV1_SC0DIV_Pos           (0)                                               /*!< CLK_T::CLKDIV1: SC0DIV Position        */
#define CLK_CLKDIV1_SC0DIV_Msk           (0xful << CLK_CLKDIV1_SC0DIV_Pos)                 /*!< CLK_T::CLKDIV1: SC0DIV Mask            */

#define CLK_CLKDIV1_SC1DIV_Pos           (4)                                               /*!< CLK_T::CLKDIV1: SC1DIV Position        */
#define CLK_CLKDIV1_SC1DIV_Msk           (0xful << CLK_CLKDIV1_SC1DIV_Pos)                 /*!< CLK_T::CLKDIV1: SC1DIV Mask            */

#define CLK_CLKDIV1_CCAP0DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV1: CCAP0DIV Position      */
#define CLK_CLKDIV1_CCAP0DIV_Msk         (0xful << CLK_CLKDIV1_CCAP0DIV_Pos)               /*!< CLK_T::CLKDIV1: CCAP0DIV Mask          */

#define CLK_CLKDIV1_CCAP1DIV_Pos         (12)                                              /*!< CLK_T::CLKDIV1: CCAP1DIV Position      */
#define CLK_CLKDIV1_CCAP1DIV_Msk         (0xful << CLK_CLKDIV1_CCAP1DIV_Pos)               /*!< CLK_T::CLKDIV1: CCAP1DIV Mask          */

#define CLK_CLKDIV1_UART0DIV_Pos         (16)                                              /*!< CLK_T::CLKDIV1: UART0DIV Position      */
#define CLK_CLKDIV1_UART0DIV_Msk         (0xful << CLK_CLKDIV1_UART0DIV_Pos)               /*!< CLK_T::CLKDIV1: UART0DIV Mask          */

#define CLK_CLKDIV1_UART1DIV_Pos         (20)                                              /*!< CLK_T::CLKDIV1: UART1DIV Position      */
#define CLK_CLKDIV1_UART1DIV_Msk         (0xful << CLK_CLKDIV1_UART1DIV_Pos)               /*!< CLK_T::CLKDIV1: UART1DIV Mask          */

#define CLK_CLKDIV1_UART2DIV_Pos         (24)                                              /*!< CLK_T::CLKDIV1: UART2DIV Position      */
#define CLK_CLKDIV1_UART2DIV_Msk         (0xful << CLK_CLKDIV1_UART2DIV_Pos)               /*!< CLK_T::CLKDIV1: UART2DIV Mask          */

#define CLK_CLKDIV1_UART3DIV_Pos         (28)                                              /*!< CLK_T::CLKDIV1: UART3DIV Position      */
#define CLK_CLKDIV1_UART3DIV_Msk         (0xful << CLK_CLKDIV1_UART3DIV_Pos)               /*!< CLK_T::CLKDIV1: UART3DIV Mask          */

#define CLK_CLKDIV2_UART4DIV_Pos         (0)                                               /*!< CLK_T::CLKDIV2: UART4DIV Position      */
#define CLK_CLKDIV2_UART4DIV_Msk         (0xful << CLK_CLKDIV2_UART4DIV_Pos)               /*!< CLK_T::CLKDIV2: UART4DIV Mask          */

#define CLK_CLKDIV2_UART5DIV_Pos         (4)                                               /*!< CLK_T::CLKDIV2: UART5DIV Position      */
#define CLK_CLKDIV2_UART5DIV_Msk         (0xful << CLK_CLKDIV2_UART5DIV_Pos)               /*!< CLK_T::CLKDIV2: UART5DIV Mask          */

#define CLK_CLKDIV2_UART6DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV2: UART6DIV Position      */
#define CLK_CLKDIV2_UART6DIV_Msk         (0xful << CLK_CLKDIV2_UART6DIV_Pos)               /*!< CLK_T::CLKDIV2: UART6DIV Mask          */

#define CLK_CLKDIV2_UART7DIV_Pos         (12)                                              /*!< CLK_T::CLKDIV2: UART7DIV Position      */
#define CLK_CLKDIV2_UART7DIV_Msk         (0xful << CLK_CLKDIV2_UART7DIV_Pos)               /*!< CLK_T::CLKDIV2: UART7DIV Mask          */

#define CLK_CLKDIV2_UART8DIV_Pos         (16)                                              /*!< CLK_T::CLKDIV2: UART8DIV Position      */
#define CLK_CLKDIV2_UART8DIV_Msk         (0xful << CLK_CLKDIV2_UART8DIV_Pos)               /*!< CLK_T::CLKDIV2: UART8DIV Mask          */

#define CLK_CLKDIV2_UART9DIV_Pos         (20)                                              /*!< CLK_T::CLKDIV2: UART9DIV Position      */
#define CLK_CLKDIV2_UART9DIV_Msk         (0xful << CLK_CLKDIV2_UART9DIV_Pos)               /*!< CLK_T::CLKDIV2: UART9DIV Mask          */

#define CLK_CLKDIV2_UART10DIV_Pos        (24)                                              /*!< CLK_T::CLKDIV2: UART10DIV Position     */
#define CLK_CLKDIV2_UART10DIV_Msk        (0xful << CLK_CLKDIV2_UART10DIV_Pos)              /*!< CLK_T::CLKDIV2: UART10DIV Mask         */

#define CLK_CLKDIV2_UART11DIV_Pos        (28)                                              /*!< CLK_T::CLKDIV2: UART11DIV Position     */
#define CLK_CLKDIV2_UART11DIV_Msk        (0xful << CLK_CLKDIV2_UART11DIV_Pos)              /*!< CLK_T::CLKDIV2: UART11DIV Mask         */

#define CLK_CLKDIV3_UART12DIV_Pos        (0)                                               /*!< CLK_T::CLKDIV3: UART12DIV Position     */
#define CLK_CLKDIV3_UART12DIV_Msk        (0xful << CLK_CLKDIV3_UART12DIV_Pos)              /*!< CLK_T::CLKDIV3: UART12DIV Mask         */

#define CLK_CLKDIV3_UART13DIV_Pos        (4)                                               /*!< CLK_T::CLKDIV3: UART13DIV Position     */
#define CLK_CLKDIV3_UART13DIV_Msk        (0xful << CLK_CLKDIV3_UART13DIV_Pos)              /*!< CLK_T::CLKDIV3: UART13DIV Mask         */

#define CLK_CLKDIV3_UART14DIV_Pos        (8)                                               /*!< CLK_T::CLKDIV3: UART14DIV Position     */
#define CLK_CLKDIV3_UART14DIV_Msk        (0xful << CLK_CLKDIV3_UART14DIV_Pos)              /*!< CLK_T::CLKDIV3: UART14DIV Mask         */

#define CLK_CLKDIV3_UART15DIV_Pos        (12)                                              /*!< CLK_T::CLKDIV3: UART15DIV Position     */
#define CLK_CLKDIV3_UART15DIV_Msk        (0xful << CLK_CLKDIV3_UART15DIV_Pos)              /*!< CLK_T::CLKDIV3: UART15DIV Mask         */

#define CLK_CLKDIV3_UART16DIV_Pos        (16)                                              /*!< CLK_T::CLKDIV3: UART16DIV Position     */
#define CLK_CLKDIV3_UART16DIV_Msk        (0xful << CLK_CLKDIV3_UART16DIV_Pos)              /*!< CLK_T::CLKDIV3: UART16DIV Mask         */

#define CLK_CLKDIV4_EADCDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV4: EADCDIV Position       */
#define CLK_CLKDIV4_EADCDIV_Msk          (0xful << CLK_CLKDIV4_EADCDIV_Pos)                /*!< CLK_T::CLKDIV4: EADCDIV Mask           */

#define CLK_CLKDIV4_ADCDIV_Pos           (4)                                               /*!< CLK_T::CLKDIV4: ADCDIV Position        */
#define CLK_CLKDIV4_ADCDIV_Msk           (0x1fffful << CLK_CLKDIV4_ADCDIV_Pos)             /*!< CLK_T::CLKDIV4: ADCDIV Mask            */

#define CLK_CLKDIV4_KPIDIV_Pos           (24)                                              /*!< CLK_T::CLKDIV4: KPIDIV Position        */
#define CLK_CLKDIV4_KPIDIV_Msk           (0xfful << CLK_CLKDIV4_KPIDIV_Pos)                /*!< CLK_T::CLKDIV4: KPIDIV Mask            */

#define CLK_CLKOCTL_FREQSEL_Pos          (0)                                               /*!< CLK_T::CLKOCTL: FREQSEL Position       */
#define CLK_CLKOCTL_FREQSEL_Msk          (0xful << CLK_CLKOCTL_FREQSEL_Pos)                /*!< CLK_T::CLKOCTL: FREQSEL Mask           */

#define CLK_CLKOCTL_CLKOEN_Pos           (4)                                               /*!< CLK_T::CLKOCTL: CLKOEN Position        */
#define CLK_CLKOCTL_CLKOEN_Msk           (0x1ul << CLK_CLKOCTL_CLKOEN_Pos)                 /*!< CLK_T::CLKOCTL: CLKOEN Mask            */

#define CLK_CLKOCTL_DIV1EN_Pos           (5)                                               /*!< CLK_T::CLKOCTL: DIV1EN Position        */
#define CLK_CLKOCTL_DIV1EN_Msk           (0x1ul << CLK_CLKOCTL_DIV1EN_Pos)                 /*!< CLK_T::CLKOCTL: DIV1EN Mask            */

#define CLK_STATUS_HXTSTB_Pos            (0)                                               /*!< CLK_T::STATUS: HXTSTB Position         */
#define CLK_STATUS_HXTSTB_Msk            (0x1ul << CLK_STATUS_HXTSTB_Pos)                  /*!< CLK_T::STATUS: HXTSTB Mask             */

#define CLK_STATUS_LXTSTB_Pos            (1)                                               /*!< CLK_T::STATUS: LXTSTB Position         */
#define CLK_STATUS_LXTSTB_Msk            (0x1ul << CLK_STATUS_LXTSTB_Pos)                  /*!< CLK_T::STATUS: LXTSTB Mask             */

#define CLK_STATUS_SYSPLLSTB_Pos         (2)                                               /*!< CLK_T::STATUS: SYSPLLSTB Position      */
#define CLK_STATUS_SYSPLLSTB_Msk         (0x1ul << CLK_STATUS_SYSPLLSTB_Pos)               /*!< CLK_T::STATUS: SYSPLLSTB Mask          */

#define CLK_STATUS_LIRCSTB_Pos           (3)                                               /*!< CLK_T::STATUS: LIRCSTB Position        */
#define CLK_STATUS_LIRCSTB_Msk           (0x1ul << CLK_STATUS_LIRCSTB_Pos)                 /*!< CLK_T::STATUS: LIRCSTB Mask            */

#define CLK_STATUS_HIRCSTB_Pos           (4)                                               /*!< CLK_T::STATUS: HIRCSTB Position        */
#define CLK_STATUS_HIRCSTB_Msk           (0x1ul << CLK_STATUS_HIRCSTB_Pos)                 /*!< CLK_T::STATUS: HIRCSTB Mask            */

#define CLK_STATUS_CAPLLSTB_Pos          (6)                                               /*!< CLK_T::STATUS: CAPLLSTB Position       */
#define CLK_STATUS_CAPLLSTB_Msk          (0x1ul << CLK_STATUS_CAPLLSTB_Pos)                /*!< CLK_T::STATUS: CAPLLSTB Mask           */

#define CLK_STATUS_DDRPLLSTB_Pos         (8)                                               /*!< CLK_T::STATUS: DDRPLLSTB Position      */
#define CLK_STATUS_DDRPLLSTB_Msk         (0x1ul << CLK_STATUS_DDRPLLSTB_Pos)               /*!< CLK_T::STATUS: DDRPLLSTB Mask          */

#define CLK_STATUS_EPLLSTB_Pos           (9)                                               /*!< CLK_T::STATUS: EPLLSTB Position        */
#define CLK_STATUS_EPLLSTB_Msk           (0x1ul << CLK_STATUS_EPLLSTB_Pos)                 /*!< CLK_T::STATUS: EPLLSTB Mask            */

#define CLK_STATUS_APLLSTB_Pos           (10)                                              /*!< CLK_T::STATUS: APLLSTB Position        */
#define CLK_STATUS_APLLSTB_Msk           (0x1ul << CLK_STATUS_APLLSTB_Pos)                 /*!< CLK_T::STATUS: APLLSTB Mask            */

#define CLK_STATUS_VPLLSTB_Pos           (11)                                              /*!< CLK_T::STATUS: VPLLSTB Position        */
#define CLK_STATUS_VPLLSTB_Msk           (0x1ul << CLK_STATUS_VPLLSTB_Pos)                 /*!< CLK_T::STATUS: VPLLSTB Mask            */

#define CLK_PLL0CTL0_FBDIV_Pos           (0)                                               /*!< CLK_T::PLL0CTL0: FBDIV Position        */
#define CLK_PLL0CTL0_FBDIV_Msk           (0xfful << CLK_PLL0CTL0_FBDIV_Pos)                 /*!< CLK_T::PLL0CTL0: FBDIV Mask            */

#define CLK_PLL0CTL0_INDIV_Pos           (8)                                               /*!< CLK_T::PLL0CTL0: INDIV Position        */
#define CLK_PLL0CTL0_INDIV_Msk           (0xful << CLK_PLL0CTL0_INDIV_Pos)                 /*!< CLK_T::PLL0CTL0: INDIV Mask            */

#define CLK_PLL0CTL0_OUTDIV_Pos          (12)                                              /*!< CLK_T::PLL0CTL0: MODE Position         */
#define CLK_PLL0CTL0_OUTDIV_Msk          (0x3ul << CLK_PLL0CTL0_OUTDIV_Pos)                /*!< CLK_T::PLL0CTL0: MODE Mask             */

#define CLK_PLL0CTL0_PD_Pos              (16)                                              /*!< CLK_T::PLL0CTL0: PD Position           */
#define CLK_PLL0CTL0_PD_Msk              (0x1ul << CLK_PLL0CTL0_PD_Pos)                    /*!< CLK_T::PLL0CTL0: PD Mask               */

#define CLK_PLL0CTL0_BP_Pos              (17)                                              /*!< CLK_T::PLL0CTL0: BP Position           */
#define CLK_PLL0CTL0_BP_Msk              (0x1ul << CLK_PLL0CTL0_BP_Pos)                    /*!< CLK_T::PLL0CTL0: BP Mask               */

/* For PLL2 ~ PLL5 */
#define CLK_PLLnCTL0_FBDIV_Pos           (0)                                               /*!< CLK_T::PLLnCTL0: FBDIV Position        */
#define CLK_PLLnCTL0_FBDIV_Msk           (0x7fful << CLK_PLLnCTL0_FBDIV_Pos)               /*!< CLK_T::PLLnCTL0: FBDIV Mask            */

#define CLK_PLLnCTL0_INDIV_Pos           (12)                                              /*!< CLK_T::PLLnCTL0: INDIV Position        */
#define CLK_PLLnCTL0_INDIV_Msk           (0x3ful << CLK_PLLnCTL0_INDIV_Pos)                /*!< CLK_T::PLLnCTL0: INDIV Mask            */

#define CLK_PLLnCTL0_MODE_Pos            (18)                                              /*!< CLK_T::PLLnCTL0: MODE Position         */
#define CLK_PLLnCTL0_MODE_Msk            (0x3ul << CLK_PLLnCTL0_MODE_Pos)                  /*!< CLK_T::PLLnCTL0: MODE Mask             */

#define CLK_PLLnCTL0_SSRATE_Pos          (20)                                              /*!< CLK_T::PLLnCTL0: SSRATE Position       */
#define CLK_PLLnCTL0_SSRATE_Msk          (0x7fful << CLK_PLLnCTL0_SSRATE_Pos)              /*!< CLK_T::PLLnCTL0: SSRATE Mask           */

#define CLK_PLLnCTL1_PD_Pos              (0)                                               /*!< CLK_T::PLLnCTL1: PD Position           */
#define CLK_PLLnCTL1_PD_Msk              (0x1ul << CLK_PLLnCTL1_PD_Pos)                    /*!< CLK_T::PLLnCTL1: PD Mask               */

#define CLK_PLLnCTL1_BP_Pos              (1)                                               /*!< CLK_T::PLLnCTL1: BP Position           */
#define CLK_PLLnCTL1_BP_Msk              (0x1ul << CLK_PLLnCTL1_BP_Pos)                    /*!< CLK_T::PLLnCTL1: BP Mask               */

#define CLK_PLLnCTL1_OUTDIV_Pos          (4)                                               /*!< CLK_T::PLLnCTL1: OUTDIV Position       */
#define CLK_PLLnCTL1_OUTDIV_Msk          (0x7ul << CLK_PLLnCTL1_OUTDIV_Pos)                /*!< CLK_T::PLLnCTL1: OUTDIV Mask           */

#define CLK_PLLnCTL1_FRAC_Pos            (8)                                               /*!< CLK_T::PLLnCTL1: FRAC Position         */
#define CLK_PLLnCTL1_FRAC_Msk            (0xfffffful << CLK_PLLnCTL1_FRAC_Pos)             /*!< CLK_T::PLLnCTL1: FRAC Mask             */

#define CLK_PLLnCTL2_SLOPE_Pos           (0)                                               /*!< CLK_T::PLLnCTL2: SLOPE Position        */
#define CLK_PLLnCTL2_SLOPE_Msk           (0xfffffful << CLK_PLLnCTL2_SLOPE_Pos)            /*!< CLK_T::PLLnCTL2: SLOPE Mask            */

#define CLK_CLKDCTL_HXTFDEN_Pos          (4)                                               /*!< CLK_T::CLKDCTL: HXTFDEN Position       */
#define CLK_CLKDCTL_HXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFDEN Mask           */

#define CLK_CLKDCTL_HXTFIEN_Pos          (5)                                               /*!< CLK_T::CLKDCTL: HXTFIEN Position       */
#define CLK_CLKDCTL_HXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFIEN Mask           */

#define CLK_CLKDCTL_LXTFDEN_Pos          (12)                                              /*!< CLK_T::CLKDCTL: LXTFDEN Position       */
#define CLK_CLKDCTL_LXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFDEN Mask           */

#define CLK_CLKDCTL_LXTFIEN_Pos          (13)                                              /*!< CLK_T::CLKDCTL: LXTFIEN Position       */
#define CLK_CLKDCTL_LXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFIEN Mask           */

#define CLK_CLKDCTL_HXTFQDEN_Pos         (16)                                              /*!< CLK_T::CLKDCTL: HXTFQDEN Position      */
#define CLK_CLKDCTL_HXTFQDEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQDEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQDEN Mask          */

#define CLK_CLKDCTL_HXTFQIEN_Pos         (17)                                              /*!< CLK_T::CLKDCTL: HXTFQIEN Position      */
#define CLK_CLKDCTL_HXTFQIEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQIEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQIEN Mask          */

#define CLK_CLKDSTS_HXTFIF_Pos           (0)                                               /*!< CLK_T::CLKDSTS: HXTFIF Position        */
#define CLK_CLKDSTS_HXTFIF_Msk           (0x1ul << CLK_CLKDSTS_HXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: HXTFIF Mask            */

#define CLK_CLKDSTS_LXTFIF_Pos           (1)                                               /*!< CLK_T::CLKDSTS: LXTFIF Position        */
#define CLK_CLKDSTS_LXTFIF_Msk           (0x1ul << CLK_CLKDSTS_LXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: LXTFIF Mask            */

#define CLK_CLKDSTS_HXTFQIF_Pos          (8)                                               /*!< CLK_T::CLKDSTS: HXTFQIF Position       */
#define CLK_CLKDSTS_HXTFQIF_Msk          (0x1ul << CLK_CLKDSTS_HXTFQIF_Pos)                /*!< CLK_T::CLKDSTS: HXTFQIF Mask           */

#define CLK_CDUPB_UPERBD_Pos             (0)                                               /*!< CLK_T::CDUPB: UPERBD Position          */
#define CLK_CDUPB_UPERBD_Msk             (0x3fful << CLK_CDUPB_UPERBD_Pos)                 /*!< CLK_T::CDUPB: UPERBD Mask              */

#define CLK_CDLOWB_LOWERBD_Pos           (0)                                               /*!< CLK_T::CDLOWB: LOWERBD Position        */
#define CLK_CDLOWB_LOWERBD_Msk           (0x3fful << CLK_CDLOWB_LOWERBD_Pos)               /*!< CLK_T::CDLOWB: LOWERBD Mask            */

#define CLK_CKFLTRCTL_HXTFLTREN_Pos      (0)                                               /*!< CLK_T::CKFLTRCTL: HXTFLTREN Position   */
#define CLK_CKFLTRCTL_HXTFLTREN_Msk      (0x1ul << CLK_CKFLTRCTL_HXTFLTREN_Pos)            /*!< CLK_T::CKFLTRCTL: HXTFLTREN Mask       */

#define CLK_CKFLTRCTL_HXTFLTRSEL_Pos     (1)                                               /*!< CLK_T::CKFLTRCTL: HXTFLTRSEL Position  */
#define CLK_CKFLTRCTL_HXTFLTRSEL_Msk     (0x1ul << CLK_CKFLTRCTL_HXTFLTRSEL_Pos)           /*!< CLK_T::CKFLTRCTL: HXTFLTRSEL Mask      */

#define CLK_CKFLTRCTL_HXTGTEN_Pos        (4)                                               /*!< CLK_T::CKFLTRCTL: HXTGTEN Position     */
#define CLK_CKFLTRCTL_HXTGTEN_Msk        (0x1ul << CLK_CKFLTRCTL_HXTGTEN_Pos)              /*!< CLK_T::CKFLTRCTL: HXTGTEN Mask         */

#define CLK_CKFLTRCTL_HXTBYPSEN_Pos      (5)                                               /*!< CLK_T::CKFLTRCTL: HXTBYPSEN Position   */
#define CLK_CKFLTRCTL_HXTBYPSEN_Msk      (0x1ul << CLK_CKFLTRCTL_HXTBYPSEN_Pos)            /*!< CLK_T::CKFLTRCTL: HXTBYPSEN Mask       */

#define CLK_CKFLTRCTL_HIRCFLTREN_Pos     (8)                                               /*!< CLK_T::CKFLTRCTL: HIRCFLTREN Position  */
#define CLK_CKFLTRCTL_HIRCFLTREN_Msk     (0x1ul << CLK_CKFLTRCTL_HIRCFLTREN_Pos)           /*!< CLK_T::CKFLTRCTL: HIRCFLTREN Mask      */

#define CLK_CKFLTRCTL_HIRCFLTRSEL_Pos    (9)                                               /*!< CLK_T::CKFLTRCTL: HIRCFLTRSEL Position */
#define CLK_CKFLTRCTL_HIRCFLTRSEL_Msk    (0x1ul << CLK_CKFLTRCTL_HIRCFLTRSEL_Pos)          /*!< CLK_T::CKFLTRCTL: HIRCFLTRSEL Mask     */

#define CLK_CKFLTRCTL_HIRCGTEN_Pos       (12)                                              /*!< CLK_T::CKFLTRCTL: HIRCGTEN Position    */
#define CLK_CKFLTRCTL_HIRCGTEN_Msk       (0x1ul << CLK_CKFLTRCTL_HIRCGTEN_Pos)             /*!< CLK_T::CKFLTRCTL: HIRCGTEN Mask        */

/**@}*/ /* CLK_CONST */
/**@}*/ /* end of CLK register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __CLK_REG_H__ */
