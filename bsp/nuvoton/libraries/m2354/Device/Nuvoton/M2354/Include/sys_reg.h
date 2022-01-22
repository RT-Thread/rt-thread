/**************************************************************************//**
 * @file     sys_reg.h
 * @version  V1.00
 * @brief    SYS register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SYS_REG_H__
#define __SYS_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- System Manger Controller -------------------------*/
/**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
  @{
*/

typedef struct
{


    /**
     * @var SYS_T::PDID
     * Offset: 0x00  Part Device Identification Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PDID      |Part Device Identification Number (Read Only)
     * |        |          |This register reflects device part number code.
     * |        |          |Software can read this register to identify which device is used.
     * @var SYS_T::RSTSTS
     * Offset: 0x04  System Reset Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PORF      |POR Reset Flag
     * |        |          |The POR reset flag is set by the "Reset Signal" from the Power-on Reset (POR) Controller or bit CHIPRST (SYS_IPRST0[0]) to indicate the previous reset source.
     * |        |          |0 = No reset from POR or CHIPRST.
     * |        |          |1 = Power-on Reset (POR) or CHIPRST had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |PINRF     |nRESET Pin Reset Flag
     * |        |          |The nRESET pin reset flag is set by the "Reset Signal" from the nRESET Pin to indicate the previous reset source.
     * |        |          |0 = No reset from nRESET pin.
     * |        |          |1 = Pin nRESET had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[2]     |WDTRF     |WDT Reset Flag
     * |        |          |The WDT reset flag is set by the "Reset Signal" from the Watchdog Timer or Window Watchdog Timer to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer or window watchdog timer.
     * |        |          |1 = The watchdog timer or window watchdog timer had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer register RSTF(WDT_CTL[2]) bit is set if the system has been reset by WDT time-out reset.
     * |        |          |Window Watchdog Timer register WWDTRF(WWDT_STATUS[1]) bit is set if the system has been reset by WWDT time-out reset.
     * |        |          |Note 3: Extra Watchdog Timer register RSTF(EWDT_CTL[2]) bit is set if the system has been reset by EWDT time-out reset.
     * |        |          |Extra Window Watchdog Timer register WWDTRF(EWWDT_STATUS[1]) bit is set if the system has been reset by EWWDT time-out reset.
     * |[3]     |LVRF      |LVR Reset Flag
     * |        |          |The LVR reset flag is set by the "Reset Signal" from the Low Voltage Reset Controller to indicate the previous reset source.
     * |        |          |0 = No reset from LVR.
     * |        |          |1 = LVR controller had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |BODRF     |BOD Reset Flag
     * |        |          |The BOD reset flag is set by the "Reset Signal" from the Brown-out Detector to indicate the previous reset source.
     * |        |          |0 = No reset from BOD.
     * |        |          |1 = The BOD had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |SYSRF     |System Reset Flag
     * |        |          |The system reset flag is set by the "Reset Signal" from the Cortex-M23 Core to indicate the previous reset source.
     * |        |          |0 = No reset from Cortex-M23.
     * |        |          |1 = The Cortex-M23 had issued the reset signal to reset the system by writing 1 to the bit SYSRESETREQ(AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M23 core.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[7]     |CPURF     |CPU Reset Flag
     * |        |          |The CPU reset flag is set by hardware if software writes CPURST (SYS_IPRST0[1]) 1 to reset Cortex-M23 Core and Flash Memory Controller (FMC).
     * |        |          |0 = No reset from CPU.
     * |        |          |1 = The Cortex-M23 Core and FMC are reset by software setting CPURST to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[8]     |CPULKRF   |CPU Lockup Reset Flag
     * |        |          |The CPULK reset flag is set by hardware if Cortex-M23 lockup happened.
     * |        |          |0 = No reset from CPU lockup happened.
     * |        |          |1 = The Cortex-M23 lockup happened and chip is reset.
     * |        |          |Note1: Write 1 to clear this bit to 0.
     * |        |          |Note2: When CPU lockup happened under ICE is connected, This flag will set to 1 but chip will not reset.
     * @var SYS_T::IPRST0
     * Offset: 0x08  Peripheral Reset Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHIPRST   |Chip One-shot Reset (Write Protect)
     * |        |          |Setting this bit will reset the whole chip, including Processor core and all peripherals, and this bit will automatically return to 0 after the 2 clock cycles.
     * |        |          |The CHIPRST is same as the POR reset, all the chip controllers is reset and the chip setting from flash are also reload.
     * |        |          |0 = Chip normal operation.
     * |        |          |1 = Chip one-shot reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |CPURST    |Processor Core One-shot Reset (Write Protect)
     * |        |          |Setting this bit will only reset the processor core and Flash Memory Controller(FMC), and this bit will automatically return to 0 after the 2 clock cycles.
     * |        |          |0 = Processor core normal operation.
     * |        |          |1 = Processor core one-shot reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |PDMA0RST  |PDMA0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the PDMA0 (always secure).
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = PDMA0 controller normal operation.
     * |        |          |1 = PDMA0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |EBIRST    |EBI Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the EBI
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = EBI controller normal operation.
     * |        |          |1 = EBI controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |USBHRST   |USB Host Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the USB Host.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = USB Host controller normal operation.
     * |        |          |1 = USB Host controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |SDH0RST   |SDHOST0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the SDHOST0 controller
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = SDHOST0 controller normal operation.
     * |        |          |1 = SDHOST0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |CRCRST    |CRC Calculation Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the CRC calculation controller
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = CRC calculation controller normal operation.
     * |        |          |1 = CRC calculation controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12]    |CRPTRST   |CRYPTO Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CRYPTO controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = CRYPTO controller normal operation.
     * |        |          |1 = CRYPTO controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[13]    |KSRST     |Key Store Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CRYPTO controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = Key Store controller normal operation.
     * |        |          |1 = Key Store controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[29]    |PDMA1RST  |PDMA1 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the PDMA1.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = PDMA1 controller normal operation.
     * |        |          |1 = PDMA1 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::IPRST1
     * Offset: 0x0C  Peripheral Reset Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |GPIORST   |GPIO Controller Reset
     * |        |          |0 = GPIO controller normal operation.
     * |        |          |1 = GPIO controller reset.
     * |[2]     |TMR0RST   |Timer0 Controller Reset
     * |        |          |0 = Timer0 controller normal operation.
     * |        |          |1 = Timer0 controller reset.
     * |[3]     |TMR1RST   |Timer1 Controller Reset
     * |        |          |0 = Timer1 controller normal operation.
     * |        |          |1 = Timer1 controller reset.
     * |[4]     |TMR2RST   |Timer2 Controller Reset
     * |        |          |0 = Timer2 controller normal operation.
     * |        |          |1 = Timer2 controller reset.
     * |[5]     |TMR3RST   |Timer3 Controller Reset
     * |        |          |0 = Timer3 controller normal operation.
     * |        |          |1 = Timer3 controller reset.
     * |[7]     |ACMP01RST |Analog Comparator 0/1 Controller Reset
     * |        |          |0 = Analog Comparator 0/1 controller normal operation.
     * |        |          |1 = Analog Comparator 0/1 controller reset.
     * |[8]     |I2C0RST   |I2C0 Controller Reset
     * |        |          |0 = I2C0 controller normal operation.
     * |        |          |1 = I2C0 controller reset.
     * |[9]     |I2C1RST   |I2C1 Controller Reset
     * |        |          |0 = I2C1 controller normal operation.
     * |        |          |1 = I2C1 controller reset.
     * |[10]    |I2C2RST   |I2C2 Controller Reset
     * |        |          |0 = I2C2 controller normal operation.
     * |        |          |1 = I2C2 controller reset.
     * |[12]    |QSPI0RST  |QSPI0 Controller Reset
     * |        |          |0 = QSPI0 controller normal operation.
     * |        |          |1 = QSPI0 controller reset.
     * |[13]    |SPI0RST   |SPI0 Controller Reset
     * |        |          |0 = SPI0 controller normal operation.
     * |        |          |1 = SPI0 controller reset.
     * |[14]    |SPI1RST   |SPI1 Controller Reset
     * |        |          |0 = SPI1 controller normal operation.
     * |        |          |1 = SPI1 controller reset.
     * |[15]    |SPI2RST   |SPI2 Controller Reset
     * |        |          |0 = SPI2 controller normal operation.
     * |        |          |1 = SPI2 controller reset.
     * |[16]    |UART0RST  |UART0 Controller Reset
     * |        |          |0 = UART0 controller normal operation.
     * |        |          |1 = UART0 controller reset.
     * |[17]    |UART1RST  |UART1 Controller Reset
     * |        |          |0 = UART1 controller normal operation.
     * |        |          |1 = UART1 controller reset.
     * |[18]    |UART2RST  |UART2 Controller Reset
     * |        |          |0 = UART2 controller normal operation.
     * |        |          |1 = UART2 controller reset.
     * |[19]    |UART3RST  |UART3 Controller Reset
     * |        |          |0 = UART3 controller normal operation.
     * |        |          |1 = UART3 controller reset.
     * |[20]    |UART4RST  |UART4 Controller Reset
     * |        |          |0 = UART4 controller normal operation.
     * |        |          |1 = UART4 controller reset.
     * |[21]    |UART5RST  |UART5 Controller Reset
     * |        |          |0 = UART5 controller normal operation.
     * |        |          |1 = UART5 controller reset.
     * |[24]    |CAN0RST   |CAN0 Controller Reset
     * |        |          |0 = CAN0 controller normal operation.
     * |        |          |1 = CAN0 controller reset.
     * |[26]    |OTGRST    |OTG Controller Reset
     * |        |          |0 = OTG controller normal operation.
     * |        |          |1 = OTG controller reset.
     * |[27]    |USBDRST   |USBD Controller Reset
     * |        |          |0 = USBD controller normal operation.
     * |        |          |1 = USBD controller reset.
     * |[28]    |EADCRST   |EADC Controller Reset
     * |        |          |0 = EADC controller normal operation.
     * |        |          |1 = EADC controller reset.
     * |[29]    |I2S0RST   |I2S0 Controller Reset
     * |        |          |0 = I2S0 controller normal operation.
     * |        |          |1 = I2S0 controller reset.
     * |[30]    |LCDRST    |LCD Controller Reset
     * |        |          |0 = LCD controller normal operation.
     * |        |          |1 = LCD controller reset.
     * |[31]    |TRNGRST   |TRNG Controller Reset
     * |        |          |0 = TRNG controller normal operation.
     * |        |          |1 = TRNG controller reset.
     * @var SYS_T::IPRST2
     * Offset: 0x10  Peripheral Reset Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SC0RST    |SC0 Controller Reset
     * |        |          |0 = SC0 controller normal operation.
     * |        |          |1 = SC0 controller reset.
     * |[1]     |SC1RST    |SC1 Controller Reset
     * |        |          |0 = SC1 controller normal operation.
     * |        |          |1 = SC1 controller reset.
     * |[2]     |SC2RST    |SC2 Controller Reset
     * |        |          |0 = SC2 controller normal operation.
     * |        |          |1 = SC2 controller reset.
     * |[6]     |SPI3RST   |SPI3 Controller Reset
     * |        |          |0 = SPI3 controller normal operation.
     * |        |          |1 = SPI3 controller reset.
     * |[8]     |USCI0RST  |USCI0 Controller Reset
     * |        |          |0 = USCI0 controller normal operation.
     * |        |          |1 = USCI0 controller reset.
     * |[9]     |USCI1RST  |USCI1 Controller Reset
     * |        |          |0 = USCI1 controller normal operation.
     * |        |          |1 = USCI1 controller reset.
     * |[12]    |DACRST    |DAC Controller Reset
     * |        |          |0 = DAC controller normal operation.
     * |        |          |1 = DAC controller reset.
     * |[16]    |EPWM0RST  |EPWM0 Controller Reset
     * |        |          |0 = EPWM0 controller normal operation.
     * |        |          |1 = EPWM0 controller reset.
     * |[17]    |EPWM1RST  |EPWM1 Controller Reset
     * |        |          |0 = EPWM1 controller normal operation.
     * |        |          |1 = EPWM1 controller reset.
     * |[18]    |BPWM0RST  |BPWM0 Controller Reset
     * |        |          |0 = BPWM0 controller normal operation.
     * |        |          |1 = BPWM0 controller reset.
     * |[19]    |BPWM1RST  |BPWM1 Controller Reset
     * |        |          |0 = BPWM1 controller normal operation.
     * |        |          |1 = BPWM1 controller reset.
     * |[20]    |TMR4RST   |Timer4 Controller Reset
     * |        |          |0 = Timer4 controller normal operation.
     * |        |          |1 = Timer4 controller reset.
     * |[21]    |TMR5RST   |Timer5 Controller Reset
     * |        |          |0 = Timer5 controller normal operation.
     * |        |          |1 = Timer5 controller reset.
     * |[22]    |QEI0RST   |QEI0 Controller Reset
     * |        |          |0 = QEI0 controller normal operation.
     * |        |          |1 = QEI0 controller reset.
     * |[23]    |QEI1RST   |QEI1 Controller Reset
     * |        |          |0 = QEI1 controller normal operation.
     * |        |          |1 = QEI1 controller reset.
     * |[26]    |ECAP0RST  |ECAP0 Controller Reset
     * |        |          |0 = ECAP0 controller normal operation.
     * |        |          |1 = ECAP0 controller reset.
     * |[27]    |ECAP1RST  |ECAP1 Controller Reset
     * |        |          |0 = ECAP1 controller normal operation.
     * |        |          |1 = ECAP1 controller reset.
     * @var SYS_T::BODCTL
     * Offset: 0x18  Brown-out Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BODEN     |Brown-out Detector Enable Bit (Write Protect)
     * |        |          |The default value is set by flash controller user configuration register CBODEN (CONFIG0 [23]).
     * |        |          |0 = Brown-out Detector function Disabled.
     * |        |          |1 = Brown-out Detector function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |BODRSTEN  |Brown-out Reset Enable Bit (Write Protect)
     * |        |          |The default value is set by flash controller user configuration register CBORST(CONFIG0[20]) bit .
     * |        |          |0 = Brown-out INTERRUPT function Enabled.
     * |        |          |1 = Brown-out RESET function Enabled.
     * |        |          |Note1:
     * |        |          |While the Brown-out Detector function is enabled (BODEN high) and BOD reset function is enabled (BODRSTEN high), BOD will assert a signal to reset chip when the detected voltage is lower than the threshold (BODOUT high).
     * |        |          |While the BOD function is enabled (BODEN high) and BOD interrupt function is enabled (BODRSTEN low), BOD will assert an interrupt if AVDD high.than BODVL, BOD interrupt will keep till to the BODIF set to 0.
     * |        |          |BOD interrupt can be blocked by disabling the NVIC BOD interrupt or disabling BOD function (set BODEN low).
     * |        |          |Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |BODIF     |Brown-out Detector Interrupt Flag
     * |        |          |0 = Brown-out Detector does not detect any voltage draft at VDD down through or up through the voltage of BODVL setting.
     * |        |          |1 = When Brown-out Detector detects the VDD is dropped down through the voltage of BODVL setting or the VDD is raised up through the voltage of BODVL setting, this bit is set to 1 and the brown-out interrupt is requested if brown-out interrupt is enabled.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[6]     |BODOUT    |Brown-out Detector Output Status
     * |        |          |0 = Brown-out Detector output status is 0.
     * |        |          |It means the detected voltage is higher than BODVL setting or BODEN is 0.
     * |        |          |1 = Brown-out Detector output status is 1.
     * |        |          |It means the detected voltage is lower than BODVL setting.
     * |        |          |If the BODEN is 0, BOD function disabled , this bit always responds 0.
     * |[7]     |LVREN     |Low Voltage Reset Enable Bit (Write Protect)
     * |        |          |The LVR function resets the chip when the input power voltage is lower than LVR circuit setting.
     * |        |          |LVR function is enabled by default.
     * |        |          |0 = Low Voltage Reset function Disabled.
     * |        |          |1 = Low Voltage Reset function Enabled.
     * |        |          |Note1: After enabling the bit, the LVR function will be active with 200us delay for LVR output stable (default).
     * |        |          |Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[10:8]  |BODDGSEL  |Brown-out Detector Output De-glitch Time Select (Write Protect)
     * |        |          |000 = BOD output is sampled by LIRC clock.
     * |        |          |001 = 4 system clock (HCLK).
     * |        |          |010 = 8 system clock (HCLK).
     * |        |          |011 = 16 system clock (HCLK).
     * |        |          |100 = 32 system clock (HCLK).
     * |        |          |101 = 64 system clock (HCLK).
     * |        |          |110 = 128 system clock (HCLK).
     * |        |          |111 = 256 system clock (HCLK).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[14:12] |LVRDGSEL  |LVR Output De-glitch Time Select (Write Protect)
     * |        |          |000 = Without de-glitch function.
     * |        |          |001 = 4 system clock (HCLK).
     * |        |          |010 = 8 system clock (HCLK).
     * |        |          |011 = 16 system clock (HCLK).
     * |        |          |100 = 32 system clock (HCLK).
     * |        |          |101 = 64 system clock (HCLK).
     * |        |          |110 = 128 system clock (HCLK).
     * |        |          |111 = 256 system clock (HCLK).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[23]    |STB       |Circuit Stable Flag (Read Only)
     * |        |          |This bit indicates LVR and BOD already stable, system cannot detect LVR and BOD event when this bit is not set.
     * |        |          |0 = LVR and BOD is not stable.
     * |        |          |1 = LVR and BOD already stable.
     * |[18:16] |BODVL     |Brown-out Detector Threshold Voltage Selection (Write Protect)
     * |        |          |The default value is set by flash controller user configuration register CBOV (CONFIG0 [23:21]).
     * |        |          |000 = Brown-out Detector threshold voltage is 1.6V.
     * |        |          |001 = Brown-out Detector threshold voltage is 1.8V.
     * |        |          |010 = Brown-out Detector threshold voltage is 2.0V.
     * |        |          |011 = Brown-out Detector threshold voltage is 2.2V.
     * |        |          |100 = Brown-out Detector threshold voltage is 2.4V.
     * |        |          |101 = Brown-out Detector threshold voltage is 2.6V.
     * |        |          |110 = Brown-out Detector threshold voltage is 2.8V.
     * |        |          |111 = Brown-out Detector threshold voltage is 3.0V.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[31]    |WRBUSY    |Write Busy Flag (Read Only)
     * |        |          |If SYS_BODCTL is written, this bit is asserted automatically by hardware, and is de-asserted when write procedure is finished.
     * |        |          |0 = SYS_BODCTL register is ready for write operation.
     * |        |          |1 = SYS_BODCTL register is busy on the last write operation. Other write operations are ignored.
     * @var SYS_T::IVSCTL
     * Offset: 0x1C  Internal Voltage Source Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |VTEMPEN   |Temperature Sensor Enable Bit
     * |        |          |This bit is used to enable/disable temperature sensor function.
     * |        |          |0 = Temperature sensor function Disabled (default).
     * |        |          |1 = Temperature sensor function Enabled.
     * |        |          |Note: After this bit is set to 1, the value of temperature sensor output can be obtained through GPC.9.
     * |[1]     |VBATUGEN  |VBAT Unity Gain Buffer Enable Bit
     * |        |          |This bit is used to enable/disable VBAT unity gain buffer function.
     * |        |          |0 = VBAT unity gain buffer function Disabled (default).
     * |        |          |1 = VBAT unity gain buffer function Enabled.
     * |        |          |Note: After this bit is set to 1, the value of VBAT unity gain buffer output voltage can be obtained from ADC conversion result.
     * @var SYS_T::PORCTL0
     * Offset: 0x24  Power-on Reset Controller Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PORMASK   |Power-on Reset Mask Enable Bit (Write Protect)
     * |        |          |When powered on, the POR circuit generates a reset signal to reset the whole chip function, but noise on the power may cause the POR active again.
     * |        |          |User can mask  internal POR signal to avoid unpredictable noise to cause chip reset by writing 0x5AA5 to this field.
     * |        |          |The POR function will be active again when this field is set to another value or chip is reset by other reset source, including:
     * |        |          |nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::VREFCTL
     * Offset: 0x28  VREF Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |VREFCTL   |VREF Control Bits (Write Protect)
     * |        |          |00000 = VREF is from external pin.
     * |        |          |00011 = VREF is internal 1.6V.
     * |        |          |00111 = VREF is internal 2.0V.
     * |        |          |01011 = VREF is internal 2.5V.
     * |        |          |01111 = VREF is internal 3.0V.
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |IBIASSEL  |VREF Bias Current Selection (Write Protect)
     * |        |          |0 = Bias current from MEGBIAS.
     * |        |          |1 = Bias current from internal.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7:6]   |PRELOADSEL|Pre-load Timing Selection (Write Protect)
     * |        |          |00 = pre-load time is 60us for 0.1uF Capacitor.
     * |        |          |01 = pre-load time is 310us for 1uF Capacitor.
     * |        |          |10 = pre-load time is 1270us for 4.7uF Capacitor.
     * |        |          |11 = pre-load time is 2650us for 10uF Capacitor.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::USBPHY
     * Offset: 0x2C  USB PHY Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |USBROLE   |USB Role Option (Write Protect)
     * |        |          |These two bits are used to select the role of USB.
     * |        |          |00 = Standard USB Device mode.
     * |        |          |01 = Standard USB Host mode.
     * |        |          |10 = ID dependent mode.
     * |        |          |11 = On-The-Go device mode (default).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |SBO       |Note: This bit must always be kept 1. If set to 0, the result is unpredictable.
     * |[8]     |OTGPHYEN  |USB OTG PHY Enable
     * |        |          |This bit is used to enable/disable OTG PHY function.
     * |        |          |0 = OTG PHY function Disabled (default).
     * |        |          |1 = OTG PHY function Enabled.
     * @var SYS_T::GPA_MFPL
     * Offset: 0x30  GPIOA Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PA0MFP    |PA.0 Multi-function Pin Selection
     * |[7:4]   |PA1MFP    |PA.1 Multi-function Pin Selection
     * |[11:8]  |PA2MFP    |PA.2 Multi-function Pin Selection
     * |[15:12] |PA3MFP    |PA.3 Multi-function Pin Selection
     * |[19:16] |PA4MFP    |PA.4 Multi-function Pin Selection
     * |[23:20] |PA5MFP    |PA.5 Multi-function Pin Selection
     * |[27:24] |PA6MFP    |PA.6 Multi-function Pin Selection
     * |[31:28] |PA7MFP    |PA.7 Multi-function Pin Selection
     * @var SYS_T::GPA_MFPH
     * Offset: 0x34  GPIOA High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PA8MFP    |PA.8 Multi-function Pin Selection
     * |[7:4]   |PA9MFP    |PA.9 Multi-function Pin Selection
     * |[11:8]  |PA10MFP   |PA.10 Multi-function Pin Selection
     * |[15:12] |PA11MFP   |PA.11 Multi-function Pin Selection
     * |[19:16] |PA12MFP   |PA.12 Multi-function Pin Selection
     * |[23:20] |PA13MFP   |PA.13 Multi-function Pin Selection
     * |[27:24] |PA14MFP   |PA.14 Multi-function Pin Selection
     * |[31:28] |PA15MFP   |PA.15 Multi-function Pin Selection
     * @var SYS_T::GPB_MFPL
     * Offset: 0x38  GPIOB Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PB0MFP    |PB.0 Multi-function Pin Selection
     * |[7:4]   |PB1MFP    |PB.1 Multi-function Pin Selection
     * |[11:8]  |PB2MFP    |PB.2 Multi-function Pin Selection
     * |[15:12] |PB3MFP    |PB.3 Multi-function Pin Selection
     * |[19:16] |PB4MFP    |PB.4 Multi-function Pin Selection
     * |[23:20] |PB5MFP    |PB.5 Multi-function Pin Selection
     * |[27:24] |PB6MFP    |PB.6 Multi-function Pin Selection
     * |[31:28] |PB7MFP    |PB.7 Multi-function Pin Selection
     * @var SYS_T::GPB_MFPH
     * Offset: 0x3C  GPIOB High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PB8MFP    |PB.8 Multi-function Pin Selection
     * |[7:4]   |PB9MFP    |PB.9 Multi-function Pin Selection
     * |[11:8]  |PB10MFP   |PB.10 Multi-function Pin Selection
     * |[15:12] |PB11MFP   |PB.11 Multi-function Pin Selection
     * |[19:16] |PB12MFP   |PB.12 Multi-function Pin Selection
     * |[23:20] |PB13MFP   |PB.13 Multi-function Pin Selection
     * |[27:24] |PB14MFP   |PB.14 Multi-function Pin Selection
     * |[31:28] |PB15MFP   |PB.15 Multi-function Pin Selection
     * @var SYS_T::GPC_MFPL
     * Offset: 0x40  GPIOC Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PC0MFP    |PC.0 Multi-function Pin Selection
     * |[7:4]   |PC1MFP    |PC.1 Multi-function Pin Selection
     * |[11:8]  |PC2MFP    |PC.2 Multi-function Pin Selection
     * |[15:12] |PC3MFP    |PC.3 Multi-function Pin Selection
     * |[19:16] |PC4MFP    |PC.4 Multi-function Pin Selection
     * |[23:20] |PC5MFP    |PC.5 Multi-function Pin Selection
     * |[27:24] |PC6MFP    |PC.6 Multi-function Pin Selection
     * |[31:28] |PC7MFP    |PC.7 Multi-function Pin Selection
     * @var SYS_T::GPC_MFPH
     * Offset: 0x44  GPIOC High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PC8MFP    |PC.8 Multi-function Pin Selection
     * |[7:4]   |PC9MFP    |PC.9 Multi-function Pin Selection
     * |[11:8]  |PC10MFP   |PC.10 Multi-function Pin Selection
     * |[15:12] |PC11MFP   |PC.11 Multi-function Pin Selection
     * |[19:16] |PC12MFP   |PC.12 Multi-function Pin Selection
     * |[23:20] |PC13MFP   |PC.13 Multi-function Pin Selection
     * @var SYS_T::GPD_MFPL
     * Offset: 0x48  GPIOD Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PD0MFP    |PD.0 Multi-function Pin Selection
     * |[7:4]   |PD1MFP    |PD.1 Multi-function Pin Selection
     * |[11:8]  |PD2MFP    |PD.2 Multi-function Pin Selection
     * |[15:12] |PD3MFP    |PD.3 Multi-function Pin Selection
     * |[19:16] |PD4MFP    |PD.4 Multi-function Pin Selection
     * |[23:20] |PD5MFP    |PD.5 Multi-function Pin Selection
     * |[27:24] |PD6MFP    |PD.6 Multi-function Pin Selection
     * |[31:28] |PD7MFP    |PD.7 Multi-function Pin Selection
     * @var SYS_T::GPD_MFPH
     * Offset: 0x4C  GPIOD High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PD8MFP    |PD.8 Multi-function Pin Selection
     * |[7:4]   |PD9MFP    |PD.9 Multi-function Pin Selection
     * |[11:8]  |PD10MFP   |PD.10 Multi-function Pin Selection
     * |[15:12] |PD11MFP   |PD.11 Multi-function Pin Selection
     * |[19:16] |PD12MFP   |PD.12 Multi-function Pin Selection
     * |[27:24] |PD14MFP   |PD.14 Multi-function Pin Selection
     * @var SYS_T::GPE_MFPL
     * Offset: 0x50  GPIOE Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PE0MFP    |PE.0 Multi-function Pin Selection
     * |[7:4]   |PE1MFP    |PE.1 Multi-function Pin Selection
     * |[11:8]  |PE2MFP    |PE.2 Multi-function Pin Selection
     * |[15:12] |PE3MFP    |PE.3 Multi-function Pin Selection
     * |[19:16] |PE4MFP    |PE.4 Multi-function Pin Selection
     * |[23:20] |PE5MFP    |PE.5 Multi-function Pin Selection
     * |[27:24] |PE6MFP    |PE.6 Multi-function Pin Selection
     * |[31:28] |PE7MFP    |PE.7 Multi-function Pin Selection
     * @var SYS_T::GPE_MFPH
     * Offset: 0x54  GPIOE High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PE8MFP    |PE.8 Multi-function Pin Selection
     * |[7:4]   |PE9MFP    |PE.9 Multi-function Pin Selection
     * |[11:8]  |PE10MFP   |PE.10 Multi-function Pin Selection
     * |[15:12] |PE11MFP   |PE.11 Multi-function Pin Selection
     * |[19:16] |PE12MFP   |PE.12 Multi-function Pin Selection
     * |[23:20] |PE13MFP   |PE.13 Multi-function Pin Selection
     * |[27:24] |PE14MFP   |PE.14 Multi-function Pin Selection
     * |[31:28] |PE15MFP   |PE.15 Multi-function Pin Selection
     * @var SYS_T::GPF_MFPL
     * Offset: 0x58  GPIOF Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PF0MFP    |PF.0 Multi-function Pin Selection
     * |[7:4]   |PF1MFP    |PF.1 Multi-function Pin Selection
     * |[11:8]  |PF2MFP    |PF.2 Multi-function Pin Selection
     * |[15:12] |PF3MFP    |PF.3 Multi-function Pin Selection
     * |[19:16] |PF4MFP    |PF.4 Multi-function Pin Selection
     * |[23:20] |PF5MFP    |PF.5 Multi-function Pin Selection
     * |[27:24] |PF6MFP    |PF.6 Multi-function Pin Selection
     * |[31:28] |PF7MFP    |PF.7 Multi-function Pin Selection
     * @var SYS_T::GPF_MFPH
     * Offset: 0x5C  GPIOF High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PF8MFP    |PF.8 Multi-function Pin Selection
     * |[7:4]   |PF9MFP    |PF.9 Multi-function Pin Selection
     * |[11:8]  |PF10MFP   |PF.10 Multi-function Pin Selection
     * |[15:12] |PF11MFP   |PF.11 Multi-function Pin Selection
     * @var SYS_T::GPG_MFPL
     * Offset: 0x60  GPIOG Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:8]  |PG2MFP    |PG.2 Multi-function Pin Selection
     * |[15:12] |PG3MFP    |PG.3 Multi-function Pin Selection
     * |[19:16] |PG4MFP    |PG.4 Multi-function Pin Selection
     * @var SYS_T::GPG_MFPH
     * Offset: 0x64  GPIOG High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:4]   |PG9MFP    |PG.9 Multi-function Pin Selection
     * |[11:8]  |PG10MFP   |PG.10 Multi-function Pin Selection
     * |[15:12] |PG11MFP   |PG.11 Multi-function Pin Selection
     * |[19:16] |PG12MFP   |PG.12 Multi-function Pin Selection
     * |[23:20] |PG13MFP   |PG.13 Multi-function Pin Selection
     * |[27:24] |PG14MFP   |PG.14 Multi-function Pin Selection
     * |[31:28] |PG15MFP   |PG.15 Multi-function Pin Selection
     * @var SYS_T::GPH_MFPL
     * Offset: 0x68  GPIOH Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[19:16] |PH4MFP    |PH.4 Multi-function Pin Selection
     * |[23:20] |PH5MFP    |PH.5 Multi-function Pin Selection
     * |[27:24] |PH6MFP    |PH.6 Multi-function Pin Selection
     * |[31:28] |PH7MFP    |PH.7 Multi-function Pin Selection
     * @var SYS_T::GPH_MFPH
     * Offset: 0x6C  GPIOH High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PH8MFP    |PH.8 Multi-function Pin Selection
     * |[7:4]   |PH9MFP    |PH.9 Multi-function Pin Selection
     * |[11:8]  |PH10MFP   |PH.10 Multi-function Pin Selection
     * |[15:12] |PH11MFP   |PH.11 Multi-function Pin Selection
     * @var SYS_T::VTORSET
     * Offset: 0xA0  VTOR Setting Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |VTORSET   |VTOR Setting After SPD Wakeup (Write Protect)
     * |        |          |This is the register to set the address of vector table after chip is waked up from SPD Power-down mode.
     * |        |          |The value will be loaded to Vector Table Offset Register, which is at the address 0xE000ED08, when chip wake up from SPD mode.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::SRAMICTL
     * Offset: 0xC0  System SRAM Parity Error Interrupt Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PERRIEN   |SRAM Parity Check Error Interrupt Enable Bit
     * |        |          |0 = SRAM parity check error interrupt Disabled.
     * |        |          |1 = SRAM parity check error interrupt Enabled.
     * @var SYS_T::SRAMSTS
     * Offset: 0xC4  System SRAM Parity Check Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PERRIF    |SRAM Parity Check Error Flag
     * |        |          |This bit indicates the System SRAM parity error occurred. Write 1 to clear this to 0.
     * |        |          |0 = No System SRAM parity error.
     * |        |          |1 = System SRAM parity error occur.
     * @var SYS_T::SRAMEADR
     * Offset: 0xC8  System SRAM Parity Check Error Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ERRADDR   |System SRAM Parity Error Address
     * |        |          |This register shows system SRAM parity error byte address.
     * @var SYS_T::SRAMPC0
     * Offset: 0xDC  SRAM Power Mode Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |SRAM0PM0  |Bank0 SRAM Power Mode Select 0 (Write Protect)
     * |        |          |This field can control SRAM bank0 selection 0 (4k) power mode for range 0x2000_0000 - 0x2000_0FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[3:2]   |SRAM0PM1  |Bank0 SRAM Power Mode Select 1 (Write Protect)
     * |        |          |This field can control SRAM bank0 selection 1 power mode for range 0x2000_1000 - 0x2000_1FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[5:4]   |SRAM0PM2  |Bank0 SRAM Power Mode Select 2 (Write Protect)
     * |        |          |This field can control SRAM bank0 selection 2 (8k) power mode for range 0x2000_2000 - 0x2000_3FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[7:6]   |SRAM0PM3  |Bank0 SRAM Power Mode Select 3 (Write Protect)
     * |        |          |This field can control SRAM bank0 selection 3 (8k) power mode for range 0x2000_4000 - 0x2000_5FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[9:8]   |SRAM0PM4  |Bank0 SRAM Power Mode Select 4 (Write Protect)
     * |        |          |This field can control SRAM0 bank0 selection 4 (8k) power mode for range 0x2000_6000 - 0x2000_7FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[11:10] |SRAM1PM0  |Bank1 SRAM Power Mode Select 0 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 0 (16k) power mode for range 0x2000_8000 - 0x2000_BFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[13:12] |SRAM1PM1  |Bank1 SRAM Power Mode Select 1 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 1 (16k) power mode for range 0x2000_C000 - 0x2000_FFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[15:14] |SRAM1PM2  |Bank1 SRAM Power Mode Select 2 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 2 (16k) power mode for range 0x2001_0000 - 0x2001_3FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[17:16] |SRAM1PM3  |Bank1 SRAM Power Mode Select 3 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 3 (16k) power mode for range 0x2001_4000 - 0x2001_7FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[19:18] |SRAM1PM4  |Bank1 SRAM Power Mode Select 4 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 4 (16k) power mode for range 0x2001_8000 - 0x2001_BFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[21:20] |SRAM1PM5  |Bank1 SRAM Power Mode Select 5 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 5 (16k) power mode for range 0x2001_C000 - 0x2001_FFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[23:22] |SRAM1PM6  |Bank1 SRAM Power Mode Select 6 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 6 (16k) power mode for range 0x2002_0000 - 0x2002_3FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[25:24] |SRAM1PM7  |Bank1 SRAM Power Mode Select 7 (Write Protect)
     * |        |          |This field can control SRAM bank1 selection 7 (16k) power mode for range 0x2002_4000 - 0x2002_7FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[27:26] |SRAM2PM0  |Bank2 SRAM Power Mode Select 0 (Write Protect)
     * |        |          |This field can control SRAM bank2 selection 0 (16k) power mode for range 0x2002_8000 - 0x2002_BFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[29:28] |SRAM2PM1  |Bank2 SRAM Power Mode Select 1 (Write Protect)
     * |        |          |This field can control SRAM bank2 selection 1 (16k) power mode for range 0x2002_C000 - 0x2002_FFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[31]    |PCBUSY    |Power Changing Busy Flag (Read Only)
     * |        |          |This bit indicate SRAM power changing.
     * |        |          |0 = SRAM power change finish.
     * |        |          |1 = SRAM power changing.
     * @var SYS_T::SRAMPC1
     * Offset: 0xE0  SRAM Power Mode Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |SRAM2PM2  |Bank2 SRAM Power Mode Select 2 (Write Protect)
     * |        |          |This field can control SRAM bank2 selection 2 (16k) power mode for range 0x2003_0000 - 0x2003_3FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[3:2]   |SRAM2PM3  |Bank2 SRAM Power Mode Select 3 (Write Protect)
     * |        |          |This field can control bank2 sram3 (16k) power mode for range 0x2003_4000 - 0x2003_7FFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[5:4]   |SRAM2PM4  |Bank2 SRAM Power Mode Select 4 (Write Protect)
     * |        |          |This field can control SRAM bank2 selection 4 (16k) power mode for range 0x2003_8000 - 0x2003_BFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[7:6]   |SRAM2PM5  |Bank2 SRAM Power Mode Select 5 (Write Protect)
     * |        |          |This field can control SRAM bank2 selection 5 (16k) power mode for range 0x2003_C000 - 0x2003_FFFF.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[17:16] |CAN       |CAN SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control CAN sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved.
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[19:18] |USBD      |USB Device SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control USB device sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[21:20] |PDMA0     |PDMA SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control PDMA0 (always secure) sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[23:22] |PDMA1     |PDMA SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control PDMA1 sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[25:24] |FMCCACHE  |FMC Cache SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control FMC cache sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[27:26] |RSA       |RSA SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control RSA sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |        |          |Note 3: If CRPTPWREN of SYS_PSWCTL is set to 1, RSA SRAM is auto set to normal mode by hardware.
     * |[29:28] |KS        |Key Store SRAM Power Mode Select (Write Protect)
     * |        |          |This field can control Key Store sram power mode.
     * |        |          |00 = Normal mode.
     * |        |          |01 = Retention mode.
     * |        |          |10 = Power shut down mode.
     * |        |          |11 = Reserved (Write Ignore).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: Write ignore when PCBUSY is 1.
     * |[31]    |PCBUSY    |Power Changing Busy Flag (Read Only)
     * |        |          |This bit indicate SRAM power changing.
     * |        |          |0 = SRAM power change finish.
     * |        |          |1 = SRAM power changing.
     * @var SYS_T::TCTL48M
     * Offset: 0xE4  HIRC 48M Trim Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |FREQSEL   |Trim Frequency Selection
     * |        |          |This field indicates the target frequency of 48 MHz internal high speed RC oscillator (HIRC48) auto trim.
     * |        |          |During auto trim operation, if clock error detected with CESTOPEN is set to 1 or trim retry limitation count reached, this field will be cleared to 00 automatically.
     * |        |          |00 = Disable HIRC auto trim function.
     * |        |          |01 = Enable HIRC auto trim function and trim HIRC to 48 MHz.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[5:4]   |LOOPSEL   |Trim Calculation Loop Selection
     * |        |          |This field defines that trim value calculation is based on how many reference clocks.
     * |        |          |00 = Trim value calculation is based on average difference in 4 clocks of reference clock.
     * |        |          |01 = Trim value calculation is based on average difference in 8 clocks of reference clock.
     * |        |          |10 = Trim value calculation is based on average difference in 16 clocks of reference clock.
     * |        |          |11 = Trim value calculation is based on average difference in 32 clocks of reference clock.
     * |        |          |Note: For example, if LOOPSEL is set as 00, auto trim circuit will calculate trim value based on the average frequency difference in 4 clocks of reference clock.
     * |[7:6]   |RETRYCNT  |Trim Value Update Limitation Count
     * |        |          |This field defines that how many times the auto trim circuit will try to update the HIRC trim value before the frequency of HIRC locked.
     * |        |          |Once the HIRC locked, the internal trim value update counter will be reset.
     * |        |          |If the trim value update counter reached this limitation value and frequency of HIRC still doesn't lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
     * |        |          |00 = Trim retry count limitation is 64 loops.
     * |        |          |01 = Trim retry count limitation is 128 loops.
     * |        |          |10 = Trim retry count limitation is 256 loops.
     * |        |          |11 = Trim retry count limitation is 512 loops.
     * |[9]     |BOUNDEN   |Boundary Enable Bit
     * |        |          |0 = Boundary function is disable.
     * |        |          |1 = Boundary function is enable.
     * |[8]     |CESTOPEN  |Clock Error Stop Enable Bit
     * |        |          |0 = The trim operation is keep going if clock is inaccuracy.
     * |        |          |1 = The trim operation is stopped if clock is inaccuracy.
     * |[10]    |REFCKSEL  |Reference Clock Selection
     * |        |          |0 = HIRC trim 48M reference clock is from external 32.768 kHz crystal oscillator.
     * |        |          |1 = HIRC trim 48M reference clock is from internal USB synchronous mode.
     * |[20:16] |BOUNDARY  |Boundary Selection
     * |        |          |Fill the boundary range from 0x1 to 0x31, 0x0 is reserved.
     * |        |          |Note: This field is effective only when the BOUNDEN(SYS_TCTL48M [9]) is enable.
     * @var SYS_T::TIEN48M
     * Offset: 0xE8  HIRC 48M Trim Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |TFAILIEN  |Trim Failure Interrupt Enable Bit
     * |        |          |This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_TCTL48M[1:0]).
     * |        |          |If this bit is high and TFAILIF(SYS_TISTS48M[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |0 = Disable TFAILIF(SYS_TISTS48M[1]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable TFAILIF(SYS_TISTS48MM[1]) status to trigger an interrupt to CPU.
     * |[2]     |CLKEIEN   |Clock Error Interrupt Enable Bit
     * |        |          |This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
     * |        |          |If this bit is set to1, and CLKERRIF(SYS_TISTS48M[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |0 = Disable CLKERRIF(SYS_TISTS48M[2]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable CLKERRIF(SYS_TISTS48M[2]) status to trigger an interrupt to CPU.
     * @var SYS_T::TISTS48M
     * Offset: 0xEC  HIRC 48M Trim Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FREQLOCK  |HIRC Frequency Lock Status
     * |        |          |This bit indicates the HIRC frequency is locked.
     * |        |          |This is a status bit and doesn't trigger any interrupt.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
     * |        |          |0 = The internal high-speed oscillator frequency doesn't lock at 48 MHz yet.
     * |        |          |1 = The internal high-speed oscillator frequency locked at 48 MHz.
     * |[1]     |TFAILIF   |Trim Failure Interrupt Status
     * |        |          |This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still doesn't be locked.
     * |        |          |Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_TCTL48M[1:0]) will be cleared to 00 by hardware automatically.
     * |        |          |If this bit is set and TFAILIEN(SYS_TIEN48M[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Trim value update limitation count does not reach.
     * |        |          |1 = Trim value update limitation count reached and HIRC frequency still not locked.
     * |[2]     |CLKERRIF  |Clock Error Interrupt Status
     * |        |          |When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 48MHz internal high speed RC oscillator (HIRC48) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy
     * |        |          |Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_TICTL48M[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_TCTL48M[8]) is set to 1.
     * |        |          |If this bit is set and CLKEIEN(SYS_TIEN48M[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Clock frequency is accuracy.
     * |        |          |1 = Clock frequency is inaccuracy.
     * |[3]     |OVBDIF    |Over Boundary Status
     * |        |          |When the over boundary function is set, if there occurs the over boundary condition, this flag will be set.
     * |        |          |0 = Over boundary condition did not occur.
     * |        |          |1 = Over boundary condition occurred.
     * |        |          |Note: Write 1 to clear this flag.
     * @var SYS_T::TCTL12M
     * Offset: 0xF0  HIRC 12M Trim Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |FREQSEL   |Trim Frequency Selection
     * |        |          |This field indicates the target frequency of 12 MHz internal high speed RC oscillator (HIRC) auto trim.
     * |        |          |During auto trim operation, if clock error detected with CESTOPEN is set to 1 or trim retry limitation count reached, this field will be cleared to 00 automatically.
     * |        |          |00 = Disable HIRC auto trim function.
     * |        |          |01 = Enable HIRC auto trim function and trim HIRC to 12 MHz.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[5:4]   |LOOPSEL   |Trim Calculation Loop Selection
     * |        |          |This field defines that trim value calculation is based on how many reference clocks.
     * |        |          |00 = Trim value calculation is based on average difference in 4 clocks of reference clock.
     * |        |          |01 = Trim value calculation is based on average difference in 8 clocks of reference clock.
     * |        |          |10 = Trim value calculation is based on average difference in 16 clocks of reference clock.
     * |        |          |11 = Trim value calculation is based on average difference in 32 clocks of reference clock.
     * |        |          |Note: For example, if LOOPSEL is set as 00, auto trim circuit will calculate trim value based on the average frequency difference in 4 clocks of reference clock.
     * |[7:6]   |RETRYCNT  |Trim Value Update Limitation Count
     * |        |          |This field defines that how many times the auto trim circuit will try to update the HIRC trim value before the frequency of HIRC locked.
     * |        |          |Once the HIRC locked, the internal trim value update counter will be reset.
     * |        |          |If the trim value update counter reached this limitation value and frequency of HIRC still doesn't lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
     * |        |          |00 = Trim retry count limitation is 64 loops.
     * |        |          |01 = Trim retry count limitation is 128 loops.
     * |        |          |10 = Trim retry count limitation is 256 loops.
     * |        |          |11 = Trim retry count limitation is 512 loops.
     * |[9]     |BOUNDEN   |Boundary Enable Bit
     * |        |          |0 = Boundary function is disable.
     * |        |          |1 = Boundary function is enable.
     * |[8]     |CESTOPEN  |Clock Error Stop Enable Bit
     * |        |          |0 = The trim operation is keep going if clock is inaccuracy.
     * |        |          |1 = The trim operation is stopped if clock is inaccuracy.
     * |[10]    |REFCKSEL  |Reference Clock Selection
     * |        |          |0 = HIRC trim reference clock is from external 32.768 kHz crystal oscillator.
     * |        |          |1 = HIRC trim reference clock is from internal USB synchronous mode.
     * |[20:16] |BOUNDARY  |Boundary Selection
     * |        |          |Fill the boundary range from 0x1 to 0x31, 0x0 is reserved.
     * |        |          |Note: This field is effective only when the BOUNDEN(SYS_TCTL12M[9]) is enabled.
     * @var SYS_T::TIEN12M
     * Offset: 0xF4  HIRC 12M Trim Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |TFAILIEN  |Trim Failure Interrupt Enable Bit
     * |        |          |This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_TCTL12M[1:0]).
     * |        |          |If this bit is high and TFAILIF(SYS_TISTS12M[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |0 = Disable TFAILIF(SYS_TISTS12M[1]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable TFAILIF(SYS_TISTS12M[1]) status to trigger an interrupt to CPU.
     * |[2]     |CLKEIEN   |Clock Error Interrupt Enable Bit
     * |        |          |This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
     * |        |          |If this bit is set to1, and CLKERRIF(SYS_TISTS12M[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |0 = Disable CLKERRIF(SYS_TISTS12M[2]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable CLKERRIF(SYS_TISTS12M[2]) status to trigger an interrupt to CPU.
     * @var SYS_T::TISTS12M
     * Offset: 0xF8  HIRC 12M Trim Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FREQLOCK  |HIRC Frequency Lock Status
     * |        |          |This bit indicates the HIRC frequency is locked.
     * |        |          |This is a status bit and doesn't trigger any interrupt.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
     * |        |          |0 = The internal high-speed oscillator frequency doesn't lock at 12 MHz yet.
     * |        |          |1 = The internal high-speed oscillator frequency locked at 12 MHz.
     * |[1]     |TFAILIF   |Trim Failure Interrupt Status
     * |        |          |This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still doesn't be locked.
     * |        |          |Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_TCTL12M[1:0]) will be cleared to 00 by hardware automatically.
     * |        |          |If this bit is set and TFAILIEN(SYS_TIEN12M[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Trim value update limitation count does not reach.
     * |        |          |1 = Trim value update limitation count reached and HIRC frequency still not locked.
     * |[2]     |CLKERRIF  |Clock Error Interrupt Status
     * |        |          |When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 12MHz internal high speed RC oscillator (HIRC) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy
     * |        |          |Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_TICTL12M[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_TCTL12M[8]) is set to 1.
     * |        |          |If this bit is set and CLKEIEN(SYS_TIEN12M[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Clock frequency is accuracy.
     * |        |          |1 = Clock frequency is inaccuracy.
     * |[3]     |OVBDIF    |Over Boundary Status
     * |        |          |When the over boundary function is set, if there occurs the over boundary condition, this flag will be set.
     * |        |          |0 = Over boundary condition did not occur.
     * |        |          |1 = Over boundary condition occurred.
     * |        |          |Note: Write 1 to clear this flag.
     * @var SYS_T::REGLCTL
     * Offset: 0x100  Register Lock Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REGLCTL   |Register Lock Control Code (Write Only)
     * |        |          |Some registers have write-protection function
     * |        |          |Writing these registers have to disable the protected function by writing the sequence value 59h, 16h, 88h to this field.
     * |        |          |After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
     * |[0]     |REGLCTL[0]|Register Lock Control Disable Index (Read Only)
     * |        |          |0 = Write-protection Enabled for writing protected registers.
     * |        |          |Any write to the protected register is ignored.
     * |        |          |1 = Write-protection Disabled for writing protected registers.
     * @var SYS_T::CPUCFG
     * Offset: 0x1D8  CPU General Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INTRTEN   |CPU Interrupt Realtime Enable Bit
     * |        |          |When this bit is 0, the latency of CPU entering interrupt service routine (ISR) will be various but shorter.
     * |        |          |When this bit is 1, the latency of CPU entering ISR will be kept constant.
     * |        |          |0 = CPU Interrupt Realtime Disabled.
     * |        |          |1 = CPU Interrupt Realtime Enabled.
     * @var SYS_T::PORCTL1
     * Offset: 0x1EC  Power-on Reset Controller Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |POROFF    |Power-on Reset Enable Bit (Write Protect)
     * |        |          |When powered on, the POR circuit generates a reset signal to reset the whole chip function, but noise on the power may cause the POR active again.
     * |        |          |User can disable internal POR circuit to avoid unpredictable noise to cause chip reset by writing 0x5AA5 to this field.
     * |        |          |The POR function will be active again when  this field is set to another value or chip is reset by other reset source, including:
     * |        |          |nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::PSWCTL
     * Offset: 0x1F4  Power Switch Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12]    |CRPTPWREN |Cryptographic Accelerator Power Switch Enable Bit (Write Protect)
     * |        |          |0 = Cryptographic accelerator power supply Disabled.
     * |        |          |1 = Cryptographic accelerator power supply Enabled.
     * |        |          |Note 1: If this bit is set 1, RSA of SYS_SRAMPC1 is set to normal mode by hardware.
     * |        |          |Note 2: Write ignored when PCBUSY(SYS_SRAMPC1[31]) is 1.
     * |        |          |Note 3: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::PLCTL
     * Offset: 0x1F8  Power Level Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PLSEL     |Power Level Select (Write Protect)
     * |        |          |00 = Set to Power level 0 (PL0). Support system clock up to 96MHz.
     * |        |          |01 = Set to Power level 1 (PL1). Support system clock up to 84MHz.
     * |        |          |10 = Set to Power level 2 (PL2). Support system clock up to 64MHz.
     * |        |          |11 = Set to Power level 3 (PL3). Support system clock up to 4MHz.
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: These bits not be reset when wake-up from Standby Power-down mode(SPD).
     * |[4]     |MVRS      |Main Voltage Regulator Type Select (Write Protect)
     * |        |          |This bit filed sets main voltage regulator type.
     * |        |          |After setting main voltage regulator type to DCDC (MVRS (SYS_PLCTL[4]) = 1) system will set main voltage regulator type change busy flag MVRCBUSY(SYS_PLSTS[1]), detect inductor connection and update inductor connection status LCONS (SYS_PLSTS[3]).
     * |        |          |If inductor exist LCONS will be cleared and main voltage regulator type can switch to DCDC (CURMVRS (SYS_PLSTS[12])=1).
     * |        |          |0 = Set main voltage regulator to LDO.
     * |        |          |1 = Set main voltage regulator to DCDC.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: This bit not be reset when wake-up from Standby Power-down mode(SPD).
     * |[7]     |WRBUSY    |Write Busy Flag
     * |        |          |If SYS_PLCTL be written, this bit be asserted automatic by hardware, and be de-asserted when write procedure finish.
     * |        |          |0 = SYS_PLCTL register is ready for write operation.
     * |        |          |1 = SYS_PLCTL register is busy on the last write operation. Other write operations are ignored.
     * |[21:16] |LVSSTEP   |LDO Voltage Scaling Step (Write Protect)
     * |        |          |The LVSSTEP value is LDO voltage rising step.
     * |        |          |LDO voltage scaling step = (LVSSTEP + 1) * 10mV.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[31:24] |LVSPRD    |LDO Voltage Scaling Period (Write Protect)
     * |        |          |The LVSPRD value is the period of each LDO voltage rising step.
     * |        |          |LDO voltage scaling period = (LVSPRD + 1) * 1us.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::PLSTS
     * Offset: 0x1FC  Power Level Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PLCBUSY   |Power Level Change Busy Bit (Read Only)
     * |        |          |This bit is set by hardware when power level is changing.
     * |        |          |After power level change is completed, this bit will be cleared automatically by hardware.
     * |        |          |0 = Power level change is completed.
     * |        |          |1 = Power level change is ongoing.
     * |[1]     |MVRCBUSY  |Main Voltage Regulator Type Change Busy Bit (Read Only)
     * |        |          |This bit is set by hardware when main voltage regulator type is changing.
     * |        |          |After main voltage regulator type change is completed, this bit will be cleared automatically by hardware.
     * |        |          |0 = Main voltage regulator type change is completed.
     * |        |          |1 = Main voltage regulator type change is ongoing.
     * |[2]     |MVRCERR   |Main Voltage Regulator Type Change Error Bit (Write Protect)
     * |        |          |This bit is set to 1 when main voltage regulator type change from LDO to DCDC error, the following conditions will cause change errors:
     * |        |          |1.System change to DC-DC mode but LDO change voltage process not finish.
     * |        |          |2.Detect inductor fail.
     * |        |          |Read:
     * |        |          |0 = No main voltage regulator type change error.
     * |        |          |1 = Main voltage regulator type change to DCDC error occurred.
     * |        |          |Write:
     * |        |          |0 = No effect.
     * |        |          |1 = Clears MVRCERR to 0.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |LCONS     |Inductor for DC-DC Connect Status (Read Only)
     * |        |          |0 = Inductor connect between Vsw and LDO_CAP pin.
     * |        |          |This bit is valid when current main voltage regulator type is DCDC (CURMVRS (SYS_PLSTS[12])=1).
     * |        |          |If current main voltage regulator type is LDO (CURMVRS (SYS_PLSTS[12])=0), this bit is set to 1.
     * |        |          |0 = Inductor connect between Vsw and LDO_CAP pin.
     * |        |          |1 = No Inductor connect between Vsw and LDO_CAP pin.
     * |        |          |Note: This bit is 1 when main voltage regulator is LDO.
     * |[9:8]   |PLSTATUS  |Power Level Status (Read Only)
     * |        |          |This bit field reflect the current power level.
     * |        |          |00 = Power level is PL0. Support system clock up to 96MHz.
     * |        |          |01 = Power level is PL1. Support system clock up to 84MHz.
     * |        |          |10 = Power level is PL2. Support system clock up to 48MHz.
     * |        |          |11 = Power level is PL3. Support system clock up to 4MHz.
     * |[12]    |CURMVR    |Current Main Voltage Regulator Type (Read Only)
     * |        |          |This bit field reflects current main voltage regulator type.
     * |        |          |0 = Current main voltage regulator in active and Idle mode is LDO.
     * |        |          |1 = Current main voltage regulator in active and Idle mode is DCDC.
     * @var SYS_T::AHBMCTL
     * Offset: 0x400  AHB Bus Matrix Priority Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INTACTEN  |Highest AHB Bus Priority of Cortex-M23 Core Enable Bit (Write Protect)
     * |        |          |Enable Cortex-M23 core with highest AHB bus priority in AHB bus matrix.
     * |        |          |0 = Run robin mode.
     * |        |          |1 = Cortex-M23 CPU with highest bus priority when interrupt occurs.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     */

    __I  uint32_t PDID;                  /*!< [0x0000] Part Device Identification Number Register                       */
    __IO uint32_t RSTSTS;                /*!< [0x0004] System Reset Status Register                                     */
    __IO uint32_t IPRST0;                /*!< [0x0008] Peripheral  Reset Control Register 0                             */
    __IO uint32_t IPRST1;                /*!< [0x000c] Peripheral Reset Control Register 1                              */
    __IO uint32_t IPRST2;                /*!< [0x0010] Peripheral Reset Control Register 2                              */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t BODCTL;                /*!< [0x0018] Brown-out Detector Control Register                              */
    __IO uint32_t IVSCTL;                /*!< [0x001c] Internal Voltage Source Control Register                         */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t PORCTL0;               /*!< [0x0024] Power-on Reset Controller Register 0                             */
    __IO uint32_t VREFCTL;               /*!< [0x0028] VREF Control Register                                            */
    __IO uint32_t USBPHY;                /*!< [0x002C] USB PHY Control Register                                         */
    __IO uint32_t GPA_MFPL;              /*!< [0x0030] GPIOA Low Byte Multiple Function Control Register                */
    __IO uint32_t GPA_MFPH;              /*!< [0x0034] GPIOA High Byte Multiple Function Control Register               */
    __IO uint32_t GPB_MFPL;              /*!< [0x0038] GPIOB Low Byte Multiple Function Control Register                */
    __IO uint32_t GPB_MFPH;              /*!< [0x003c] GPIOB High Byte Multiple Function Control Register               */
    __IO uint32_t GPC_MFPL;              /*!< [0x0040] GPIOC Low Byte Multiple Function Control Register                */
    __IO uint32_t GPC_MFPH;              /*!< [0x0044] GPIOC High Byte Multiple Function Control Register               */
    __IO uint32_t GPD_MFPL;              /*!< [0x0048] GPIOD Low Byte Multiple Function Control Register                */
    __IO uint32_t GPD_MFPH;              /*!< [0x004c] GPIOD High Byte Multiple Function Control Register               */
    __IO uint32_t GPE_MFPL;              /*!< [0x0050] GPIOE Low Byte Multiple Function Control Register                */
    __IO uint32_t GPE_MFPH;              /*!< [0x0054] GPIOE High Byte Multiple Function Control Register               */
    __IO uint32_t GPF_MFPL;              /*!< [0x0058] GPIOF Low Byte Multiple Function Control Register                */
    __IO uint32_t GPF_MFPH;              /*!< [0x005C] GPIOF High Byte Multiple Function Control Register               */
    __IO uint32_t GPG_MFPL;              /*!< [0x0060] GPIOG Low Byte Multiple Function Control Register                */
    __IO uint32_t GPG_MFPH;              /*!< [0x0064] GPIOG High Byte Multiple Function Control Register               */
    __IO uint32_t GPH_MFPL;              /*!< [0x0068] GPIOH Low Byte Multiple Function Control Register                */
    __IO uint32_t GPH_MFPH;              /*!< [0x006C] GPIOH High Byte Multiple Function Control Register               */
    __I  uint32_t RESERVE2[4];
    __IO uint32_t GPA_MFOS;              /*!< [0x0080] GPIOA Multiple Function Output Select Register                   */
    __IO uint32_t GPB_MFOS;              /*!< [0x0084] GPIOB Multiple Function Output Select Register                   */
    __IO uint32_t GPC_MFOS;              /*!< [0x0088] GPIOC Multiple Function Output Select Register                   */
    __IO uint32_t GPD_MFOS;              /*!< [0x008c] GPIOD Multiple Function Output Select Register                   */
    __IO uint32_t GPE_MFOS;              /*!< [0x0090] GPIOE Multiple Function Output Select Register                   */
    __IO uint32_t GPF_MFOS;              /*!< [0x0094] GPIOF Multiple Function Output Select Register                   */
    __IO uint32_t GPG_MFOS;              /*!< [0x0098] GPIOG Multiple Function Output Select Register                   */
    __IO uint32_t GPH_MFOS;              /*!< [0x009c] GPIOH Multiple Function Output Select Register                   */
    __IO uint32_t VTORSET;               /*!< [0x00A0] VTOR Setting Register                                            */
    __I  uint32_t RESERVE3[7];
    __IO uint32_t SRAMICTL;              /*!< [0x00C0] System SRAM Interrupt Enable Control Register                    */
    __I  uint32_t SRAMSTS;               /*!< [0x00C4] System SRAM Parity Error Status Register                         */
    __I  uint32_t SRAMEADR;              /*!< [0x00C8] System SRAM Parity Check Error Address Register                  */
    __IO uint32_t RESERVE4[4];
    __IO uint32_t SRAMPC0;               /*!< [0x00DC] SRAM Power Mode Control Register 0                               */
    __IO uint32_t SRAMPC1;               /*!< [0x00E0] SRAM Power Mode Control Register 1                               */
    __IO uint32_t TCTL48M;               /*!< [0x00E4] HIRC 48M Trim Control Register                                   */
    __IO uint32_t TIEN48M;               /*!< [0x00E8] HIRC 48M Trim Interrupt Enable Register                          */
    __IO uint32_t TISTS48M;              /*!< [0x00EC] HIRC 48M Trim Interrupt Status Register                          */
    __IO uint32_t TCTL12M;               /*!< [0x00F0] HIRC 12M Trim Control Register                                   */
    __IO uint32_t TIEN12M;               /*!< [0x00F4] HIRC 12M Trim Interrupt Enable Register                          */
    __IO uint32_t TISTS12M;              /*!< [0x00F8] HIRC 12M Trim Interrupt Status Register                          */
    __I  uint32_t RESERVE6[1];
    __IO uint32_t REGLCTL;               /*!< [0x0100] Register Lock Control Register                                   */
    __I  uint32_t RESERVE7[53];
    __IO uint32_t CPUCFG;                /*!< [0x01D8] CPU General Configuration Register                               */
    __IO uint32_t BATLDCTL;              /*!< [0x01DC] Battery Loss Detector Control Register                           */
    __IO uint32_t OVDCTL;                /*!< [0x01E0] Over Voltage Detector Control Register                           */
    __I  uint32_t RESERVE8[2];
    __IO uint32_t PORCTL1;               /*!< [0x01EC] Power-on Reset Controller Register 1                             */
    __I  uint32_t RESERVE9[1];
    __IO uint32_t PSWCTL;                /*!< [0x01F4] Power Switch Control Register                                    */
    __IO uint32_t PLCTL;                 /*!< [0x01F8] Power Level Control Register                                     */
    __IO uint32_t PLSTS;                 /*!< [0x01FC] Power Level Status Register                                      */
    __I  uint32_t RESERVE10[128];
    __IO uint32_t AHBMCTL;               /*!< [0x0400] AHB Bus Matrix Priority Control Register                         */


} SYS_T;

/**
    @addtogroup SYS_CONST SYS Bit Field Definition
    Constant Definitions for SYS Controller
  @{
*/

#define SYS_PDID_PDID_Pos                (0)                                               /*!< SYS_T::PDID: PDID Position             */
#define SYS_PDID_PDID_Msk                (0xfffffffful << SYS_PDID_PDID_Pos)               /*!< SYS_T::PDID: PDID Mask                 */

#define SYS_RSTSTS_PORF_Pos              (0)                                               /*!< SYS_T::RSTSTS: PORF Position           */
#define SYS_RSTSTS_PORF_Msk              (0x1ul << SYS_RSTSTS_PORF_Pos)                    /*!< SYS_T::RSTSTS: PORF Mask               */

#define SYS_RSTSTS_PINRF_Pos             (1)                                               /*!< SYS_T::RSTSTS: PINRF Position          */
#define SYS_RSTSTS_PINRF_Msk             (0x1ul << SYS_RSTSTS_PINRF_Pos)                   /*!< SYS_T::RSTSTS: PINRF Mask              */

#define SYS_RSTSTS_WDTRF_Pos             (2)                                               /*!< SYS_T::RSTSTS: WDTRF Position          */
#define SYS_RSTSTS_WDTRF_Msk             (0x1ul << SYS_RSTSTS_WDTRF_Pos)                   /*!< SYS_T::RSTSTS: WDTRF Mask              */

#define SYS_RSTSTS_LVRF_Pos              (3)                                               /*!< SYS_T::RSTSTS: LVRF Position           */
#define SYS_RSTSTS_LVRF_Msk              (0x1ul << SYS_RSTSTS_LVRF_Pos)                    /*!< SYS_T::RSTSTS: LVRF Mask               */

#define SYS_RSTSTS_BODRF_Pos             (4)                                               /*!< SYS_T::RSTSTS: BODRF Position          */
#define SYS_RSTSTS_BODRF_Msk             (0x1ul << SYS_RSTSTS_BODRF_Pos)                   /*!< SYS_T::RSTSTS: BODRF Mask              */

#define SYS_RSTSTS_SYSRF_Pos             (5)                                               /*!< SYS_T::RSTSTS: SYSRF Position          */
#define SYS_RSTSTS_SYSRF_Msk             (0x1ul << SYS_RSTSTS_SYSRF_Pos)                   /*!< SYS_T::RSTSTS: SYSRF Mask              */

#define SYS_RSTSTS_CPURF_Pos             (7)                                               /*!< SYS_T::RSTSTS: CPURF Position          */
#define SYS_RSTSTS_CPURF_Msk             (0x1ul << SYS_RSTSTS_CPURF_Pos)                   /*!< SYS_T::RSTSTS: CPURF Mask              */

#define SYS_RSTSTS_CPULKRF_Pos           (8)                                               /*!< SYS_T::RSTSTS: CPULKRF Position        */
#define SYS_RSTSTS_CPULKRF_Msk           (0x1ul << SYS_RSTSTS_CPULKRF_Pos)                 /*!< SYS_T::RSTSTS: CPULKRF Mask            */

#define SYS_IPRST0_CHIPRST_Pos           (0)                                               /*!< SYS_T::IPRST0: CHIPRST Position        */
#define SYS_IPRST0_CHIPRST_Msk           (0x1ul << SYS_IPRST0_CHIPRST_Pos)                 /*!< SYS_T::IPRST0: CHIPRST Mask            */

#define SYS_IPRST0_CPURST_Pos            (1)                                               /*!< SYS_T::IPRST0: CPURST Position         */
#define SYS_IPRST0_CPURST_Msk            (0x1ul << SYS_IPRST0_CPURST_Pos)                  /*!< SYS_T::IPRST0: CPURST Mask             */

#define SYS_IPRST0_PDMA0RST_Pos          (2)                                               /*!< SYS_T::IPRST0: PDMA0RST Position       */
#define SYS_IPRST0_PDMA0RST_Msk          (0x1ul << SYS_IPRST0_PDMA0RST_Pos)                /*!< SYS_T::IPRST0: PDMA0RST Mask           */

#define SYS_IPRST0_EBIRST_Pos            (3)                                               /*!< SYS_T::IPRST0: EBIRST Position         */
#define SYS_IPRST0_EBIRST_Msk            (0x1ul << SYS_IPRST0_EBIRST_Pos)                  /*!< SYS_T::IPRST0: EBIRST Mask             */

#define SYS_IPRST0_USBHRST_Pos           (4)                                               /*!< SYS_T::IPRST0: USBHRST Position        */
#define SYS_IPRST0_USBHRST_Msk           (0x1ul << SYS_IPRST0_USBHRST_Pos)                 /*!< SYS_T::IPRST0: USBHRST Mask            */

#define SYS_IPRST0_SDH0RST_Pos           (6)                                               /*!< SYS_T::IPRST0: SDH0RST Position        */
#define SYS_IPRST0_SDH0RST_Msk           (0x1ul << SYS_IPRST0_SDH0RST_Pos)                 /*!< SYS_T::IPRST0: SDH0RST Mask            */

#define SYS_IPRST0_CRCRST_Pos            (7)                                               /*!< SYS_T::IPRST0: CRCRST Position         */
#define SYS_IPRST0_CRCRST_Msk            (0x1ul << SYS_IPRST0_CRCRST_Pos)                  /*!< SYS_T::IPRST0: CRCRST Mask             */

#define SYS_IPRST0_CRPTRST_Pos           (12)                                              /*!< SYS_T::IPRST0: CRPTRST Position        */
#define SYS_IPRST0_CRPTRST_Msk           (0x1ul << SYS_IPRST0_CRPTRST_Pos)                 /*!< SYS_T::IPRST0: CRPTRST Mask            */

#define SYS_IPRST0_KSRST_Pos             (13)                                              /*!< SYS_T::IPRST0: KSRST Position          */
#define SYS_IPRST0_KSRST_Msk             (0x1ul << SYS_IPRST0_KSRST_Pos)                   /*!< SYS_T::IPRST0: KSRST Mask              */

#define SYS_IPRST0_PDMA1RST_Pos          (29)                                              /*!< SYS_T::IPRST0: PDMA1RST Position       */
#define SYS_IPRST0_PDMA1RST_Msk          (0x1ul << SYS_IPRST0_PDMA1RST_Pos)                /*!< SYS_T::IPRST0: PDMA1RST Mask           */

#define SYS_IPRST1_GPIORST_Pos           (1)                                               /*!< SYS_T::IPRST1: GPIORST Position        */
#define SYS_IPRST1_GPIORST_Msk           (0x1ul << SYS_IPRST1_GPIORST_Pos)                 /*!< SYS_T::IPRST1: GPIORST Mask            */

#define SYS_IPRST1_TMR0RST_Pos           (2)                                               /*!< SYS_T::IPRST1: TMR0RST Position        */
#define SYS_IPRST1_TMR0RST_Msk           (0x1ul << SYS_IPRST1_TMR0RST_Pos)                 /*!< SYS_T::IPRST1: TMR0RST Mask            */

#define SYS_IPRST1_TMR1RST_Pos           (3)                                               /*!< SYS_T::IPRST1: TMR1RST Position        */
#define SYS_IPRST1_TMR1RST_Msk           (0x1ul << SYS_IPRST1_TMR1RST_Pos)                 /*!< SYS_T::IPRST1: TMR1RST Mask            */

#define SYS_IPRST1_TMR2RST_Pos           (4)                                               /*!< SYS_T::IPRST1: TMR2RST Position        */
#define SYS_IPRST1_TMR2RST_Msk           (0x1ul << SYS_IPRST1_TMR2RST_Pos)                 /*!< SYS_T::IPRST1: TMR2RST Mask            */

#define SYS_IPRST1_TMR3RST_Pos           (5)                                               /*!< SYS_T::IPRST1: TMR3RST Position        */
#define SYS_IPRST1_TMR3RST_Msk           (0x1ul << SYS_IPRST1_TMR3RST_Pos)                 /*!< SYS_T::IPRST1: TMR3RST Mask            */

#define SYS_IPRST1_ACMP01RST_Pos         (7)                                               /*!< SYS_T::IPRST1: ACMP01RST Position      */
#define SYS_IPRST1_ACMP01RST_Msk         (0x1ul << SYS_IPRST1_ACMP01RST_Pos)               /*!< SYS_T::IPRST1: ACMP01RST Mask          */

#define SYS_IPRST1_I2C0RST_Pos           (8)                                               /*!< SYS_T::IPRST1: I2C0RST Position        */
#define SYS_IPRST1_I2C0RST_Msk           (0x1ul << SYS_IPRST1_I2C0RST_Pos)                 /*!< SYS_T::IPRST1: I2C0RST Mask            */

#define SYS_IPRST1_I2C1RST_Pos           (9)                                               /*!< SYS_T::IPRST1: I2C1RST Position        */
#define SYS_IPRST1_I2C1RST_Msk           (0x1ul << SYS_IPRST1_I2C1RST_Pos)                 /*!< SYS_T::IPRST1: I2C1RST Mask            */

#define SYS_IPRST1_I2C2RST_Pos           (10)                                              /*!< SYS_T::IPRST1: I2C2RST Position        */
#define SYS_IPRST1_I2C2RST_Msk           (0x1ul << SYS_IPRST1_I2C2RST_Pos)                 /*!< SYS_T::IPRST1: I2C2RST Mask            */

#define SYS_IPRST1_QSPI0RST_Pos          (12)                                              /*!< SYS_T::IPRST1: QSPI0RST Position       */
#define SYS_IPRST1_QSPI0RST_Msk          (0x1ul << SYS_IPRST1_QSPI0RST_Pos)                /*!< SYS_T::IPRST1: QSPI0RST Mask           */

#define SYS_IPRST1_SPI0RST_Pos           (13)                                              /*!< SYS_T::IPRST1: SPI0RST Position        */
#define SYS_IPRST1_SPI0RST_Msk           (0x1ul << SYS_IPRST1_SPI0RST_Pos)                 /*!< SYS_T::IPRST1: SPI0RST Mask            */

#define SYS_IPRST1_SPI1RST_Pos           (14)                                              /*!< SYS_T::IPRST1: SPI1RST Position        */
#define SYS_IPRST1_SPI1RST_Msk           (0x1ul << SYS_IPRST1_SPI1RST_Pos)                 /*!< SYS_T::IPRST1: SPI1RST Mask            */

#define SYS_IPRST1_SPI2RST_Pos           (15)                                              /*!< SYS_T::IPRST1: SPI2RST Position        */
#define SYS_IPRST1_SPI2RST_Msk           (0x1ul << SYS_IPRST1_SPI2RST_Pos)                 /*!< SYS_T::IPRST1: SPI2RST Mask            */

#define SYS_IPRST1_UART0RST_Pos          (16)                                              /*!< SYS_T::IPRST1: UART0RST Position       */
#define SYS_IPRST1_UART0RST_Msk          (0x1ul << SYS_IPRST1_UART0RST_Pos)                /*!< SYS_T::IPRST1: UART0RST Mask           */

#define SYS_IPRST1_UART1RST_Pos          (17)                                              /*!< SYS_T::IPRST1: UART1RST Position       */
#define SYS_IPRST1_UART1RST_Msk          (0x1ul << SYS_IPRST1_UART1RST_Pos)                /*!< SYS_T::IPRST1: UART1RST Mask           */

#define SYS_IPRST1_UART2RST_Pos          (18)                                              /*!< SYS_T::IPRST1: UART2RST Position       */
#define SYS_IPRST1_UART2RST_Msk          (0x1ul << SYS_IPRST1_UART2RST_Pos)                /*!< SYS_T::IPRST1: UART2RST Mask           */

#define SYS_IPRST1_UART3RST_Pos          (19)                                              /*!< SYS_T::IPRST1: UART3RST Position       */
#define SYS_IPRST1_UART3RST_Msk          (0x1ul << SYS_IPRST1_UART3RST_Pos)                /*!< SYS_T::IPRST1: UART3RST Mask           */

#define SYS_IPRST1_UART4RST_Pos          (20)                                              /*!< SYS_T::IPRST1: UART4RST Position       */
#define SYS_IPRST1_UART4RST_Msk          (0x1ul << SYS_IPRST1_UART4RST_Pos)                /*!< SYS_T::IPRST1: UART4RST Mask           */

#define SYS_IPRST1_UART5RST_Pos          (21)                                              /*!< SYS_T::IPRST1: UART5RST Position       */
#define SYS_IPRST1_UART5RST_Msk          (0x1ul << SYS_IPRST1_UART5RST_Pos)                /*!< SYS_T::IPRST1: UART5RST Mask           */

#define SYS_IPRST1_CAN0RST_Pos           (24)                                              /*!< SYS_T::IPRST1: CAN0RST Position        */
#define SYS_IPRST1_CAN0RST_Msk           (0x1ul << SYS_IPRST1_CAN0RST_Pos)                 /*!< SYS_T::IPRST1: CAN0RST Mask            */

#define SYS_IPRST1_OTGRST_Pos            (26)                                              /*!< SYS_T::IPRST1: OTGRST Position         */
#define SYS_IPRST1_OTGRST_Msk            (0x1ul << SYS_IPRST1_OTGRST_Pos)                  /*!< SYS_T::IPRST1: OTGRST Mask             */

#define SYS_IPRST1_USBDRST_Pos           (27)                                              /*!< SYS_T::IPRST1: USBDRST Position        */
#define SYS_IPRST1_USBDRST_Msk           (0x1ul << SYS_IPRST1_USBDRST_Pos)                 /*!< SYS_T::IPRST1: USBDRST Mask            */

#define SYS_IPRST1_EADCRST_Pos           (28)                                              /*!< SYS_T::IPRST1: EADCRST Position        */
#define SYS_IPRST1_EADCRST_Msk           (0x1ul << SYS_IPRST1_EADCRST_Pos)                 /*!< SYS_T::IPRST1: EADCRST Mask            */

#define SYS_IPRST1_I2S0RST_Pos           (29)                                              /*!< SYS_T::IPRST1: I2S0RST Position        */
#define SYS_IPRST1_I2S0RST_Msk           (0x1ul << SYS_IPRST1_I2S0RST_Pos)                 /*!< SYS_T::IPRST1: I2S0RST Mask            */

#define SYS_IPRST1_LCDRST_Pos            (30)                                              /*!< SYS_T::IPRST1: LCDRST Position         */
#define SYS_IPRST1_LCDRST_Msk            (0x1ul << SYS_IPRST1_LCDRST_Pos)                  /*!< SYS_T::IPRST1: LCDRST Mask             */

#define SYS_IPRST1_TRNGRST_Pos           (31)                                              /*!< SYS_T::IPRST1: TRNGRST Position        */
#define SYS_IPRST1_TRNGRST_Msk           (0x1ul << SYS_IPRST1_TRNGRST_Pos)                 /*!< SYS_T::IPRST1: TRNGRST Mask            */

#define SYS_IPRST2_SC0RST_Pos            (0)                                               /*!< SYS_T::IPRST2: SC0RST Position         */
#define SYS_IPRST2_SC0RST_Msk            (0x1ul << SYS_IPRST2_SC0RST_Pos)                  /*!< SYS_T::IPRST2: SC0RST Mask             */

#define SYS_IPRST2_SC1RST_Pos            (1)                                               /*!< SYS_T::IPRST2: SC1RST Position         */
#define SYS_IPRST2_SC1RST_Msk            (0x1ul << SYS_IPRST2_SC1RST_Pos)                  /*!< SYS_T::IPRST2: SC1RST Mask             */

#define SYS_IPRST2_SC2RST_Pos            (2)                                               /*!< SYS_T::IPRST2: SC2RST Position         */
#define SYS_IPRST2_SC2RST_Msk            (0x1ul << SYS_IPRST2_SC2RST_Pos)                  /*!< SYS_T::IPRST2: SC2RST Mask             */

#define SYS_IPRST2_SPI3RST_Pos           (6)                                               /*!< SYS_T::IPRST2: SPI3RST Position        */
#define SYS_IPRST2_SPI3RST_Msk           (0x1ul << SYS_IPRST2_SPI3RST_Pos)                 /*!< SYS_T::IPRST2: SPI3RST Mask            */

#define SYS_IPRST2_USCI0RST_Pos          (8)                                               /*!< SYS_T::IPRST2: USCI0RST Position       */
#define SYS_IPRST2_USCI0RST_Msk          (0x1ul << SYS_IPRST2_USCI0RST_Pos)                /*!< SYS_T::IPRST2: USCI0RST Mask           */

#define SYS_IPRST2_USCI1RST_Pos          (9)                                               /*!< SYS_T::IPRST2: USCI1RST Position       */
#define SYS_IPRST2_USCI1RST_Msk          (0x1ul << SYS_IPRST2_USCI1RST_Pos)                /*!< SYS_T::IPRST2: USCI1RST Mask           */

#define SYS_IPRST2_DACRST_Pos            (12)                                              /*!< SYS_T::IPRST2: DACRST Position         */
#define SYS_IPRST2_DACRST_Msk            (0x1ul << SYS_IPRST2_DACRST_Pos)                  /*!< SYS_T::IPRST2: DACRST Mask             */

#define SYS_IPRST2_EPWM0RST_Pos          (16)                                              /*!< SYS_T::IPRST2: EPWM0RST Position       */
#define SYS_IPRST2_EPWM0RST_Msk          (0x1ul << SYS_IPRST2_EPWM0RST_Pos)                /*!< SYS_T::IPRST2: EPWM0RST Mask           */

#define SYS_IPRST2_EPWM1RST_Pos          (17)                                              /*!< SYS_T::IPRST2: EPWM1RST Position       */
#define SYS_IPRST2_EPWM1RST_Msk          (0x1ul << SYS_IPRST2_EPWM1RST_Pos)                /*!< SYS_T::IPRST2: EPWM1RST Mask           */

#define SYS_IPRST2_BPWM0RST_Pos          (18)                                              /*!< SYS_T::IPRST2: BPWM0RST Position       */
#define SYS_IPRST2_BPWM0RST_Msk          (0x1ul << SYS_IPRST2_BPWM0RST_Pos)                /*!< SYS_T::IPRST2: BPWM0RST Mask           */

#define SYS_IPRST2_BPWM1RST_Pos          (19)                                              /*!< SYS_T::IPRST2: BPWM1RST Position       */
#define SYS_IPRST2_BPWM1RST_Msk          (0x1ul << SYS_IPRST2_BPWM1RST_Pos)                /*!< SYS_T::IPRST2: BPWM1RST Mask           */

#define SYS_IPRST2_TMR4RST_Pos           (20)                                              /*!< SYS_T::IPRST2: TMR4RST Position        */
#define SYS_IPRST2_TMR4RST_Msk           (0x1ul << SYS_IPRST2_TMR4RST_Pos)                 /*!< SYS_T::IPRST2: TMR4RST Mask            */

#define SYS_IPRST2_TMR5RST_Pos           (21)                                              /*!< SYS_T::IPRST2: TMR5RST Position        */
#define SYS_IPRST2_TMR5RST_Msk           (0x1ul << SYS_IPRST2_TMR5RST_Pos)                 /*!< SYS_T::IPRST2: TMR5RST Mask            */

#define SYS_IPRST2_QEI0RST_Pos           (22)                                              /*!< SYS_T::IPRST2: QEI0RST Position        */
#define SYS_IPRST2_QEI0RST_Msk           (0x1ul << SYS_IPRST2_QEI0RST_Pos)                 /*!< SYS_T::IPRST2: QEI0RST Mask            */

#define SYS_IPRST2_QEI1RST_Pos           (23)                                              /*!< SYS_T::IPRST2: QEI1RST Position        */
#define SYS_IPRST2_QEI1RST_Msk           (0x1ul << SYS_IPRST2_QEI1RST_Pos)                 /*!< SYS_T::IPRST2: QEI1RST Mask            */

#define SYS_IPRST2_ECAP0RST_Pos          (26)                                              /*!< SYS_T::IPRST2: ECAP0RST Position       */
#define SYS_IPRST2_ECAP0RST_Msk          (0x1ul << SYS_IPRST2_ECAP0RST_Pos)                /*!< SYS_T::IPRST2: ECAP0RST Mask           */

#define SYS_IPRST2_ECAP1RST_Pos          (27)                                              /*!< SYS_T::IPRST2: ECAP1RST Position       */
#define SYS_IPRST2_ECAP1RST_Msk          (0x1ul << SYS_IPRST2_ECAP1RST_Pos)                /*!< SYS_T::IPRST2: ECAP1RST Mask           */

#define SYS_BODCTL_BODEN_Pos             (0)                                               /*!< SYS_T::BODCTL: BODEN Position          */
#define SYS_BODCTL_BODEN_Msk             (0x1ul << SYS_BODCTL_BODEN_Pos)                   /*!< SYS_T::BODCTL: BODEN Mask              */

#define SYS_BODCTL_BODRSTEN_Pos          (3)                                               /*!< SYS_T::BODCTL: BODRSTEN Position       */
#define SYS_BODCTL_BODRSTEN_Msk          (0x1ul << SYS_BODCTL_BODRSTEN_Pos)                /*!< SYS_T::BODCTL: BODRSTEN Mask           */

#define SYS_BODCTL_BODIF_Pos             (4)                                               /*!< SYS_T::BODCTL: BODIF Position          */
#define SYS_BODCTL_BODIF_Msk             (0x1ul << SYS_BODCTL_BODIF_Pos)                   /*!< SYS_T::BODCTL: BODIF Mask              */

#define SYS_BODCTL_BODOUT_Pos            (6)                                               /*!< SYS_T::BODCTL: BODOUT Position         */
#define SYS_BODCTL_BODOUT_Msk            (0x1ul << SYS_BODCTL_BODOUT_Pos)                  /*!< SYS_T::BODCTL: BODOUT Mask             */

#define SYS_BODCTL_LVREN_Pos             (7)                                               /*!< SYS_T::BODCTL: LVREN Position          */
#define SYS_BODCTL_LVREN_Msk             (0x1ul << SYS_BODCTL_LVREN_Pos)                   /*!< SYS_T::BODCTL: LVREN Mask              */

#define SYS_BODCTL_BODDGSEL_Pos          (8)                                               /*!< SYS_T::BODCTL: BODDGSEL Position       */
#define SYS_BODCTL_BODDGSEL_Msk          (0x7ul << SYS_BODCTL_BODDGSEL_Pos)                /*!< SYS_T::BODCTL: BODDGSEL Mask           */

#define SYS_BODCTL_LVRDGSEL_Pos          (12)                                              /*!< SYS_T::BODCTL: LVRDGSEL Position       */
#define SYS_BODCTL_LVRDGSEL_Msk          (0x7ul << SYS_BODCTL_LVRDGSEL_Pos)                /*!< SYS_T::BODCTL: LVRDGSEL Mask           */

#define SYS_BODCTL_BODVL_Pos             (16)                                              /*!< SYS_T::BODCTL: BODVL Position          */
#define SYS_BODCTL_BODVL_Msk             (0x7ul << SYS_BODCTL_BODVL_Pos)                   /*!< SYS_T::BODCTL: BODVL Mask              */

#define SYS_BODCTL_STB_Pos               (23)                                              /*!< SYS_T::BODCTL: STB Position            */
#define SYS_BODCTL_STB_Msk               (0x1ul << SYS_BODCTL_STB_Pos)                     /*!< SYS_T::BODCTL: STB Mask                */

#define SYS_BODCTL_WRBUSY_Pos            (31)                                              /*!< SYS_T::BODCTL: WRBUSY Position         */
#define SYS_BODCTL_WRBUSY_Msk            (0x1ul << SYS_BODCTL_WRBUSY_Pos)                  /*!< SYS_T::BODCTL: WRBUSY Mask             */

#define SYS_IVSCTL_VTEMPEN_Pos           (0)                                               /*!< SYS_T::IVSCTL: VTEMPEN Position        */
#define SYS_IVSCTL_VTEMPEN_Msk           (0x1ul << SYS_IVSCTL_VTEMPEN_Pos)                 /*!< SYS_T::IVSCTL: VTEMPEN Mask            */

#define SYS_IVSCTL_VBATUGEN_Pos          (1)                                               /*!< SYS_T::IVSCTL: VBATUGEN Position       */
#define SYS_IVSCTL_VBATUGEN_Msk          (0x1ul << SYS_IVSCTL_VBATUGEN_Pos)                /*!< SYS_T::IVSCTL: VBATUGEN Mask           */

#define SYS_PORCTL0_PORMASK_Pos          (0)                                               /*!< SYS_T::PORCTL0: PORMASK Position       */
#define SYS_PORCTL0_PORMASK_Msk          (0xfffful << SYS_PORCTL0_PORMASK_Pos)             /*!< SYS_T::PORCTL0: PORMASK Mask           */

#define SYS_VREFCTL_VREFCTL_Pos          (0)                                               /*!< SYS_T::VREFCTL: VREFCTL Position       */
#define SYS_VREFCTL_VREFCTL_Msk          (0x1ful << SYS_VREFCTL_VREFCTL_Pos)               /*!< SYS_T::VREFCTL: VREFCTL Mask           */

#define SYS_VREFCTL_IBIASSEL_Pos         (5)                                               /*!< SYS_T::VREFCTL: IBIASSEL Position      */
#define SYS_VREFCTL_IBIASSEL_Msk         (0x1ul << SYS_VREFCTL_IBIASSEL_Pos)               /*!< SYS_T::VREFCTL: IBIASSEL Mask          */

#define SYS_VREFCTL_PRELOADSEL_Pos       (6)                                               /*!< SYS_T::VREFCTL: PRELOADSEL Position    */
#define SYS_VREFCTL_PRELOADSEL_Msk       (0x3ul << SYS_VREFCTL_PRELOADSEL_Pos)             /*!< SYS_T::VREFCTL: PRELOADSEL Mask        */

#define SYS_USBPHY_USBROLE_Pos           (0)                                               /*!< SYS_T::USBPHY: USBROLE Position        */
#define SYS_USBPHY_USBROLE_Msk           (0x3ul << SYS_USBPHY_USBROLE_Pos)                 /*!< SYS_T::USBPHY: USBROLE Mask            */

#define SYS_USBPHY_SBO_Pos               (2)                                               /*!< SYS_T::USBPHY: SBO Position            */
#define SYS_USBPHY_SBO_Msk               (0x1ul << SYS_USBPHY_SBO_Pos)                     /*!< SYS_T::USBPHY: SBO Mask                */

#define SYS_USBPHY_OTGPHYEN_Pos          (8)                                               /*!< SYS_T::USBPHY: OTGPHYEN Position       */
#define SYS_USBPHY_OTGPHYEN_Msk          (0x1ul << SYS_USBPHY_OTGPHYEN_Pos)                /*!< SYS_T::USBPHY: OTGPHYEN Mask           */

#define SYS_GPA_MFPL_PA0MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPL: PA0MFP Position       */
#define SYS_GPA_MFPL_PA0MFP_Msk          (0xful << SYS_GPA_MFPL_PA0MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA0MFP Mask           */

#define SYS_GPA_MFPL_PA1MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPL: PA1MFP Position       */
#define SYS_GPA_MFPL_PA1MFP_Msk          (0xful << SYS_GPA_MFPL_PA1MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA1MFP Mask           */

#define SYS_GPA_MFPL_PA2MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFPL: PA2MFP Position       */
#define SYS_GPA_MFPL_PA2MFP_Msk          (0xful << SYS_GPA_MFPL_PA2MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA2MFP Mask           */

#define SYS_GPA_MFPL_PA3MFP_Pos          (12)                                              /*!< SYS_T::GPA_MFPL: PA3MFP Position       */
#define SYS_GPA_MFPL_PA3MFP_Msk          (0xful << SYS_GPA_MFPL_PA3MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA3MFP Mask           */

#define SYS_GPA_MFPL_PA4MFP_Pos          (16)                                              /*!< SYS_T::GPA_MFPL: PA4MFP Position       */
#define SYS_GPA_MFPL_PA4MFP_Msk          (0xful << SYS_GPA_MFPL_PA4MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA4MFP Mask           */

#define SYS_GPA_MFPL_PA5MFP_Pos          (20)                                              /*!< SYS_T::GPA_MFPL: PA5MFP Position       */
#define SYS_GPA_MFPL_PA5MFP_Msk          (0xful << SYS_GPA_MFPL_PA5MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA5MFP Mask           */

#define SYS_GPA_MFPL_PA6MFP_Pos          (24)                                              /*!< SYS_T::GPA_MFPL: PA6MFP Position       */
#define SYS_GPA_MFPL_PA6MFP_Msk          (0xful << SYS_GPA_MFPL_PA6MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA6MFP Mask           */

#define SYS_GPA_MFPL_PA7MFP_Pos          (28)                                              /*!< SYS_T::GPA_MFPL: PA7MFP Position       */
#define SYS_GPA_MFPL_PA7MFP_Msk          (0xful << SYS_GPA_MFPL_PA7MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA7MFP Mask           */

#define SYS_GPA_MFPH_PA8MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPH: PA8MFP Position       */
#define SYS_GPA_MFPH_PA8MFP_Msk          (0xful << SYS_GPA_MFPH_PA8MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA8MFP Mask           */

#define SYS_GPA_MFPH_PA9MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPH: PA9MFP Position       */
#define SYS_GPA_MFPH_PA9MFP_Msk          (0xful << SYS_GPA_MFPH_PA9MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA9MFP Mask           */

#define SYS_GPA_MFPH_PA10MFP_Pos         (8)                                               /*!< SYS_T::GPA_MFPH: PA10MFP Position      */
#define SYS_GPA_MFPH_PA10MFP_Msk         (0xful << SYS_GPA_MFPH_PA10MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA10MFP Mask          */

#define SYS_GPA_MFPH_PA11MFP_Pos         (12)                                              /*!< SYS_T::GPA_MFPH: PA11MFP Position      */
#define SYS_GPA_MFPH_PA11MFP_Msk         (0xful << SYS_GPA_MFPH_PA11MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA11MFP Mask          */

#define SYS_GPA_MFPH_PA12MFP_Pos         (16)                                              /*!< SYS_T::GPA_MFPH: PA12MFP Position      */
#define SYS_GPA_MFPH_PA12MFP_Msk         (0xful << SYS_GPA_MFPH_PA12MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA12MFP Mask          */

#define SYS_GPA_MFPH_PA13MFP_Pos         (20)                                              /*!< SYS_T::GPA_MFPH: PA13MFP Position      */
#define SYS_GPA_MFPH_PA13MFP_Msk         (0xful << SYS_GPA_MFPH_PA13MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA13MFP Mask          */

#define SYS_GPA_MFPH_PA14MFP_Pos         (24)                                              /*!< SYS_T::GPA_MFPH: PA14MFP Position      */
#define SYS_GPA_MFPH_PA14MFP_Msk         (0xful << SYS_GPA_MFPH_PA14MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA14MFP Mask          */

#define SYS_GPA_MFPH_PA15MFP_Pos         (28)                                              /*!< SYS_T::GPA_MFPH: PA15MFP Position      */
#define SYS_GPA_MFPH_PA15MFP_Msk         (0xful << SYS_GPA_MFPH_PA15MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA15MFP Mask          */

#define SYS_GPB_MFPL_PB0MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPL: PB0MFP Position       */
#define SYS_GPB_MFPL_PB0MFP_Msk          (0xful << SYS_GPB_MFPL_PB0MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB0MFP Mask           */

#define SYS_GPB_MFPL_PB1MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPL: PB1MFP Position       */
#define SYS_GPB_MFPL_PB1MFP_Msk          (0xful << SYS_GPB_MFPL_PB1MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB1MFP Mask           */

#define SYS_GPB_MFPL_PB2MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFPL: PB2MFP Position       */
#define SYS_GPB_MFPL_PB2MFP_Msk          (0xful << SYS_GPB_MFPL_PB2MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB2MFP Mask           */

#define SYS_GPB_MFPL_PB3MFP_Pos          (12)                                              /*!< SYS_T::GPB_MFPL: PB3MFP Position       */
#define SYS_GPB_MFPL_PB3MFP_Msk          (0xful << SYS_GPB_MFPL_PB3MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB3MFP Mask           */

#define SYS_GPB_MFPL_PB4MFP_Pos          (16)                                              /*!< SYS_T::GPB_MFPL: PB4MFP Position       */
#define SYS_GPB_MFPL_PB4MFP_Msk          (0xful << SYS_GPB_MFPL_PB4MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB4MFP Mask           */

#define SYS_GPB_MFPL_PB5MFP_Pos          (20)                                              /*!< SYS_T::GPB_MFPL: PB5MFP Position       */
#define SYS_GPB_MFPL_PB5MFP_Msk          (0xful << SYS_GPB_MFPL_PB5MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB5MFP Mask           */

#define SYS_GPB_MFPL_PB6MFP_Pos          (24)                                              /*!< SYS_T::GPB_MFPL: PB6MFP Position       */
#define SYS_GPB_MFPL_PB6MFP_Msk          (0xful << SYS_GPB_MFPL_PB6MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB6MFP Mask           */

#define SYS_GPB_MFPL_PB7MFP_Pos          (28)                                              /*!< SYS_T::GPB_MFPL: PB7MFP Position       */
#define SYS_GPB_MFPL_PB7MFP_Msk          (0xful << SYS_GPB_MFPL_PB7MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB7MFP Mask           */

#define SYS_GPB_MFPH_PB8MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPH: PB8MFP Position       */
#define SYS_GPB_MFPH_PB8MFP_Msk          (0xful << SYS_GPB_MFPH_PB8MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB8MFP Mask           */

#define SYS_GPB_MFPH_PB9MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPH: PB9MFP Position       */
#define SYS_GPB_MFPH_PB9MFP_Msk          (0xful << SYS_GPB_MFPH_PB9MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB9MFP Mask           */

#define SYS_GPB_MFPH_PB10MFP_Pos         (8)                                               /*!< SYS_T::GPB_MFPH: PB10MFP Position      */
#define SYS_GPB_MFPH_PB10MFP_Msk         (0xful << SYS_GPB_MFPH_PB10MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB10MFP Mask          */

#define SYS_GPB_MFPH_PB11MFP_Pos         (12)                                              /*!< SYS_T::GPB_MFPH: PB11MFP Position      */
#define SYS_GPB_MFPH_PB11MFP_Msk         (0xful << SYS_GPB_MFPH_PB11MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB11MFP Mask          */

#define SYS_GPB_MFPH_PB12MFP_Pos         (16)                                              /*!< SYS_T::GPB_MFPH: PB12MFP Position      */
#define SYS_GPB_MFPH_PB12MFP_Msk         (0xful << SYS_GPB_MFPH_PB12MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB12MFP Mask          */

#define SYS_GPB_MFPH_PB13MFP_Pos         (20)                                              /*!< SYS_T::GPB_MFPH: PB13MFP Position      */
#define SYS_GPB_MFPH_PB13MFP_Msk         (0xful << SYS_GPB_MFPH_PB13MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB13MFP Mask          */

#define SYS_GPB_MFPH_PB14MFP_Pos         (24)                                              /*!< SYS_T::GPB_MFPH: PB14MFP Position      */
#define SYS_GPB_MFPH_PB14MFP_Msk         (0xful << SYS_GPB_MFPH_PB14MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB14MFP Mask          */

#define SYS_GPB_MFPH_PB15MFP_Pos         (28)                                              /*!< SYS_T::GPB_MFPH: PB15MFP Position      */
#define SYS_GPB_MFPH_PB15MFP_Msk         (0xful << SYS_GPB_MFPH_PB15MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB15MFP Mask          */

#define SYS_GPC_MFPL_PC0MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPL: PC0MFP Position       */
#define SYS_GPC_MFPL_PC0MFP_Msk          (0xful << SYS_GPC_MFPL_PC0MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC0MFP Mask           */

#define SYS_GPC_MFPL_PC1MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPL: PC1MFP Position       */
#define SYS_GPC_MFPL_PC1MFP_Msk          (0xful << SYS_GPC_MFPL_PC1MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC1MFP Mask           */

#define SYS_GPC_MFPL_PC2MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFPL: PC2MFP Position       */
#define SYS_GPC_MFPL_PC2MFP_Msk          (0xful << SYS_GPC_MFPL_PC2MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC2MFP Mask           */

#define SYS_GPC_MFPL_PC3MFP_Pos          (12)                                              /*!< SYS_T::GPC_MFPL: PC3MFP Position       */
#define SYS_GPC_MFPL_PC3MFP_Msk          (0xful << SYS_GPC_MFPL_PC3MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC3MFP Mask           */

#define SYS_GPC_MFPL_PC4MFP_Pos          (16)                                              /*!< SYS_T::GPC_MFPL: PC4MFP Position       */
#define SYS_GPC_MFPL_PC4MFP_Msk          (0xful << SYS_GPC_MFPL_PC4MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC4MFP Mask           */

#define SYS_GPC_MFPL_PC5MFP_Pos          (20)                                              /*!< SYS_T::GPC_MFPL: PC5MFP Position       */
#define SYS_GPC_MFPL_PC5MFP_Msk          (0xful << SYS_GPC_MFPL_PC5MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC5MFP Mask           */

#define SYS_GPC_MFPL_PC6MFP_Pos          (24)                                              /*!< SYS_T::GPC_MFPL: PC6MFP Position       */
#define SYS_GPC_MFPL_PC6MFP_Msk          (0xful << SYS_GPC_MFPL_PC6MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC6MFP Mask           */

#define SYS_GPC_MFPL_PC7MFP_Pos          (28)                                              /*!< SYS_T::GPC_MFPL: PC7MFP Position       */
#define SYS_GPC_MFPL_PC7MFP_Msk          (0xful << SYS_GPC_MFPL_PC7MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC7MFP Mask           */

#define SYS_GPC_MFPH_PC8MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPH: PC8MFP Position       */
#define SYS_GPC_MFPH_PC8MFP_Msk          (0xful << SYS_GPC_MFPH_PC8MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC8MFP Mask           */

#define SYS_GPC_MFPH_PC9MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPH: PC9MFP Position       */
#define SYS_GPC_MFPH_PC9MFP_Msk          (0xful << SYS_GPC_MFPH_PC9MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC9MFP Mask           */

#define SYS_GPC_MFPH_PC10MFP_Pos         (8)                                               /*!< SYS_T::GPC_MFPH: PC10MFP Position      */
#define SYS_GPC_MFPH_PC10MFP_Msk         (0xful << SYS_GPC_MFPH_PC10MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC10MFP Mask          */

#define SYS_GPC_MFPH_PC11MFP_Pos         (12)                                              /*!< SYS_T::GPC_MFPH: PC11MFP Position      */
#define SYS_GPC_MFPH_PC11MFP_Msk         (0xful << SYS_GPC_MFPH_PC11MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC11MFP Mask          */

#define SYS_GPC_MFPH_PC12MFP_Pos         (16)                                              /*!< SYS_T::GPC_MFPH: PC12MFP Position      */
#define SYS_GPC_MFPH_PC12MFP_Msk         (0xful << SYS_GPC_MFPH_PC12MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC12MFP Mask          */

#define SYS_GPC_MFPH_PC13MFP_Pos         (20)                                              /*!< SYS_T::GPC_MFPH: PC13MFP Position      */
#define SYS_GPC_MFPH_PC13MFP_Msk         (0xful << SYS_GPC_MFPH_PC13MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC13MFP Mask          */

#define SYS_GPD_MFPL_PD0MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPL: PD0MFP Position       */
#define SYS_GPD_MFPL_PD0MFP_Msk          (0xful << SYS_GPD_MFPL_PD0MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD0MFP Mask           */

#define SYS_GPD_MFPL_PD1MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPL: PD1MFP Position       */
#define SYS_GPD_MFPL_PD1MFP_Msk          (0xful << SYS_GPD_MFPL_PD1MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD1MFP Mask           */

#define SYS_GPD_MFPL_PD2MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFPL: PD2MFP Position       */
#define SYS_GPD_MFPL_PD2MFP_Msk          (0xful << SYS_GPD_MFPL_PD2MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD2MFP Mask           */

#define SYS_GPD_MFPL_PD3MFP_Pos          (12)                                              /*!< SYS_T::GPD_MFPL: PD3MFP Position       */
#define SYS_GPD_MFPL_PD3MFP_Msk          (0xful << SYS_GPD_MFPL_PD3MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD3MFP Mask           */

#define SYS_GPD_MFPL_PD4MFP_Pos          (16)                                              /*!< SYS_T::GPD_MFPL: PD4MFP Position       */
#define SYS_GPD_MFPL_PD4MFP_Msk          (0xful << SYS_GPD_MFPL_PD4MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD4MFP Mask           */

#define SYS_GPD_MFPL_PD5MFP_Pos          (20)                                              /*!< SYS_T::GPD_MFPL: PD5MFP Position       */
#define SYS_GPD_MFPL_PD5MFP_Msk          (0xful << SYS_GPD_MFPL_PD5MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD5MFP Mask           */

#define SYS_GPD_MFPL_PD6MFP_Pos          (24)                                              /*!< SYS_T::GPD_MFPL: PD6MFP Position       */
#define SYS_GPD_MFPL_PD6MFP_Msk          (0xful << SYS_GPD_MFPL_PD6MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD6MFP Mask           */

#define SYS_GPD_MFPL_PD7MFP_Pos          (28)                                              /*!< SYS_T::GPD_MFPL: PD7MFP Position       */
#define SYS_GPD_MFPL_PD7MFP_Msk          (0xful << SYS_GPD_MFPL_PD7MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD7MFP Mask           */

#define SYS_GPD_MFPH_PD8MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPH: PD8MFP Position       */
#define SYS_GPD_MFPH_PD8MFP_Msk          (0xful << SYS_GPD_MFPH_PD8MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD8MFP Mask           */

#define SYS_GPD_MFPH_PD9MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPH: PD9MFP Position       */
#define SYS_GPD_MFPH_PD9MFP_Msk          (0xful << SYS_GPD_MFPH_PD9MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD9MFP Mask           */

#define SYS_GPD_MFPH_PD10MFP_Pos         (8)                                               /*!< SYS_T::GPD_MFPH: PD10MFP Position      */
#define SYS_GPD_MFPH_PD10MFP_Msk         (0xful << SYS_GPD_MFPH_PD10MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD10MFP Mask          */

#define SYS_GPD_MFPH_PD11MFP_Pos         (12)                                              /*!< SYS_T::GPD_MFPH: PD11MFP Position      */
#define SYS_GPD_MFPH_PD11MFP_Msk         (0xful << SYS_GPD_MFPH_PD11MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD11MFP Mask          */

#define SYS_GPD_MFPH_PD12MFP_Pos         (16)                                              /*!< SYS_T::GPD_MFPH: PD12MFP Position      */
#define SYS_GPD_MFPH_PD12MFP_Msk         (0xful << SYS_GPD_MFPH_PD12MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD12MFP Mask          */

#define SYS_GPD_MFPH_PD14MFP_Pos         (24)                                              /*!< SYS_T::GPD_MFPH: PD14MFP Position      */
#define SYS_GPD_MFPH_PD14MFP_Msk         (0xful << SYS_GPD_MFPH_PD14MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD14MFP Mask          */

#define SYS_GPE_MFPL_PE0MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPL: PE0MFP Position       */
#define SYS_GPE_MFPL_PE0MFP_Msk          (0xful << SYS_GPE_MFPL_PE0MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE0MFP Mask           */

#define SYS_GPE_MFPL_PE1MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPL: PE1MFP Position       */
#define SYS_GPE_MFPL_PE1MFP_Msk          (0xful << SYS_GPE_MFPL_PE1MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE1MFP Mask           */

#define SYS_GPE_MFPL_PE2MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFPL: PE2MFP Position       */
#define SYS_GPE_MFPL_PE2MFP_Msk          (0xful << SYS_GPE_MFPL_PE2MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE2MFP Mask           */

#define SYS_GPE_MFPL_PE3MFP_Pos          (12)                                              /*!< SYS_T::GPE_MFPL: PE3MFP Position       */
#define SYS_GPE_MFPL_PE3MFP_Msk          (0xful << SYS_GPE_MFPL_PE3MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE3MFP Mask           */

#define SYS_GPE_MFPL_PE4MFP_Pos          (16)                                              /*!< SYS_T::GPE_MFPL: PE4MFP Position       */
#define SYS_GPE_MFPL_PE4MFP_Msk          (0xful << SYS_GPE_MFPL_PE4MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE4MFP Mask           */

#define SYS_GPE_MFPL_PE5MFP_Pos          (20)                                              /*!< SYS_T::GPE_MFPL: PE5MFP Position       */
#define SYS_GPE_MFPL_PE5MFP_Msk          (0xful << SYS_GPE_MFPL_PE5MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE5MFP Mask           */

#define SYS_GPE_MFPL_PE6MFP_Pos          (24)                                              /*!< SYS_T::GPE_MFPL: PE6MFP Position       */
#define SYS_GPE_MFPL_PE6MFP_Msk          (0xful << SYS_GPE_MFPL_PE6MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE6MFP Mask           */

#define SYS_GPE_MFPL_PE7MFP_Pos          (28)                                              /*!< SYS_T::GPE_MFPL: PE7MFP Position       */
#define SYS_GPE_MFPL_PE7MFP_Msk          (0xful << SYS_GPE_MFPL_PE7MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE7MFP Mask           */

#define SYS_GPE_MFPH_PE8MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPH: PE8MFP Position       */
#define SYS_GPE_MFPH_PE8MFP_Msk          (0xful << SYS_GPE_MFPH_PE8MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE8MFP Mask           */

#define SYS_GPE_MFPH_PE9MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPH: PE9MFP Position       */
#define SYS_GPE_MFPH_PE9MFP_Msk          (0xful << SYS_GPE_MFPH_PE9MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE9MFP Mask           */

#define SYS_GPE_MFPH_PE10MFP_Pos         (8)                                               /*!< SYS_T::GPE_MFPH: PE10MFP Position      */
#define SYS_GPE_MFPH_PE10MFP_Msk         (0xful << SYS_GPE_MFPH_PE10MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE10MFP Mask          */

#define SYS_GPE_MFPH_PE11MFP_Pos         (12)                                              /*!< SYS_T::GPE_MFPH: PE11MFP Position      */
#define SYS_GPE_MFPH_PE11MFP_Msk         (0xful << SYS_GPE_MFPH_PE11MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE11MFP Mask          */

#define SYS_GPE_MFPH_PE12MFP_Pos         (16)                                              /*!< SYS_T::GPE_MFPH: PE12MFP Position      */
#define SYS_GPE_MFPH_PE12MFP_Msk         (0xful << SYS_GPE_MFPH_PE12MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE12MFP Mask          */

#define SYS_GPE_MFPH_PE13MFP_Pos         (20)                                              /*!< SYS_T::GPE_MFPH: PE13MFP Position      */
#define SYS_GPE_MFPH_PE13MFP_Msk         (0xful << SYS_GPE_MFPH_PE13MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE13MFP Mask          */

#define SYS_GPE_MFPH_PE14MFP_Pos         (24)                                              /*!< SYS_T::GPE_MFPH: PE14MFP Position      */
#define SYS_GPE_MFPH_PE14MFP_Msk         (0xful << SYS_GPE_MFPH_PE14MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE14MFP Mask          */

#define SYS_GPE_MFPH_PE15MFP_Pos         (28)                                              /*!< SYS_T::GPE_MFPH: PE15MFP Position      */
#define SYS_GPE_MFPH_PE15MFP_Msk         (0xful << SYS_GPE_MFPH_PE15MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE15MFP Mask          */

#define SYS_GPF_MFPL_PF0MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPL: PF0MFP Position       */
#define SYS_GPF_MFPL_PF0MFP_Msk          (0xful << SYS_GPF_MFPL_PF0MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF0MFP Mask           */

#define SYS_GPF_MFPL_PF1MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPL: PF1MFP Position       */
#define SYS_GPF_MFPL_PF1MFP_Msk          (0xful << SYS_GPF_MFPL_PF1MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF1MFP Mask           */

#define SYS_GPF_MFPL_PF2MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFPL: PF2MFP Position       */
#define SYS_GPF_MFPL_PF2MFP_Msk          (0xful << SYS_GPF_MFPL_PF2MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF2MFP Mask           */

#define SYS_GPF_MFPL_PF3MFP_Pos          (12)                                              /*!< SYS_T::GPF_MFPL: PF3MFP Position       */
#define SYS_GPF_MFPL_PF3MFP_Msk          (0xful << SYS_GPF_MFPL_PF3MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF3MFP Mask           */

#define SYS_GPF_MFPL_PF4MFP_Pos          (16)                                              /*!< SYS_T::GPF_MFPL: PF4MFP Position       */
#define SYS_GPF_MFPL_PF4MFP_Msk          (0xful << SYS_GPF_MFPL_PF4MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF4MFP Mask           */

#define SYS_GPF_MFPL_PF5MFP_Pos          (20)                                              /*!< SYS_T::GPF_MFPL: PF5MFP Position       */
#define SYS_GPF_MFPL_PF5MFP_Msk          (0xful << SYS_GPF_MFPL_PF5MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF5MFP Mask           */

#define SYS_GPF_MFPL_PF6MFP_Pos          (24)                                              /*!< SYS_T::GPF_MFPL: PF6MFP Position       */
#define SYS_GPF_MFPL_PF6MFP_Msk          (0xful << SYS_GPF_MFPL_PF6MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF6MFP Mask           */

#define SYS_GPF_MFPL_PF7MFP_Pos          (28)                                              /*!< SYS_T::GPF_MFPL: PF7MFP Position       */
#define SYS_GPF_MFPL_PF7MFP_Msk          (0xful << SYS_GPF_MFPL_PF7MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF7MFP Mask           */

#define SYS_GPF_MFPH_PF8MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPH: PF8MFP Position       */
#define SYS_GPF_MFPH_PF8MFP_Msk          (0xful << SYS_GPF_MFPH_PF8MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF8MFP Mask           */

#define SYS_GPF_MFPH_PF9MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPH: PF9MFP Position       */
#define SYS_GPF_MFPH_PF9MFP_Msk          (0xful << SYS_GPF_MFPH_PF9MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF9MFP Mask           */

#define SYS_GPF_MFPH_PF10MFP_Pos         (8)                                               /*!< SYS_T::GPF_MFPH: PF10MFP Position      */
#define SYS_GPF_MFPH_PF10MFP_Msk         (0xful << SYS_GPF_MFPH_PF10MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF10MFP Mask          */

#define SYS_GPF_MFPH_PF11MFP_Pos         (12)                                              /*!< SYS_T::GPF_MFPH: PF11MFP Position      */
#define SYS_GPF_MFPH_PF11MFP_Msk         (0xful << SYS_GPF_MFPH_PF11MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF11MFP Mask          */

#define SYS_GPG_MFPL_PG2MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFPL: PG2MFP Position       */
#define SYS_GPG_MFPL_PG2MFP_Msk          (0xful << SYS_GPG_MFPL_PG2MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG2MFP Mask           */

#define SYS_GPG_MFPL_PG3MFP_Pos          (12)                                              /*!< SYS_T::GPG_MFPL: PG3MFP Position       */
#define SYS_GPG_MFPL_PG3MFP_Msk          (0xful << SYS_GPG_MFPL_PG3MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG3MFP Mask           */

#define SYS_GPG_MFPL_PG4MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFPL: PG4MFP Position       */
#define SYS_GPG_MFPL_PG4MFP_Msk          (0xful << SYS_GPG_MFPL_PG4MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG4MFP Mask           */

#define SYS_GPG_MFPH_PG9MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPH: PG9MFP Position       */
#define SYS_GPG_MFPH_PG9MFP_Msk          (0xful << SYS_GPG_MFPH_PG9MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG9MFP Mask           */

#define SYS_GPG_MFPH_PG10MFP_Pos         (8)                                               /*!< SYS_T::GPG_MFPH: PG10MFP Position      */
#define SYS_GPG_MFPH_PG10MFP_Msk         (0xful << SYS_GPG_MFPH_PG10MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG10MFP Mask          */

#define SYS_GPG_MFPH_PG11MFP_Pos         (12)                                              /*!< SYS_T::GPG_MFPH: PG11MFP Position      */
#define SYS_GPG_MFPH_PG11MFP_Msk         (0xful << SYS_GPG_MFPH_PG11MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG11MFP Mask          */

#define SYS_GPG_MFPH_PG12MFP_Pos         (16)                                              /*!< SYS_T::GPG_MFPH: PG12MFP Position      */
#define SYS_GPG_MFPH_PG12MFP_Msk         (0xful << SYS_GPG_MFPH_PG12MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG12MFP Mask          */

#define SYS_GPG_MFPH_PG13MFP_Pos         (20)                                              /*!< SYS_T::GPG_MFPH: PG13MFP Position      */
#define SYS_GPG_MFPH_PG13MFP_Msk         (0xful << SYS_GPG_MFPH_PG13MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG13MFP Mask          */

#define SYS_GPG_MFPH_PG14MFP_Pos         (24)                                              /*!< SYS_T::GPG_MFPH: PG14MFP Position      */
#define SYS_GPG_MFPH_PG14MFP_Msk         (0xful << SYS_GPG_MFPH_PG14MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG14MFP Mask          */

#define SYS_GPG_MFPH_PG15MFP_Pos         (28)                                              /*!< SYS_T::GPG_MFPH: PG15MFP Position      */
#define SYS_GPG_MFPH_PG15MFP_Msk         (0xful << SYS_GPG_MFPH_PG15MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG15MFP Mask          */

#define SYS_GPH_MFPL_PH4MFP_Pos          (16)                                              /*!< SYS_T::GPH_MFPL: PH4MFP Position       */
#define SYS_GPH_MFPL_PH4MFP_Msk          (0xful << SYS_GPH_MFPL_PH4MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH4MFP Mask           */

#define SYS_GPH_MFPL_PH5MFP_Pos          (20)                                              /*!< SYS_T::GPH_MFPL: PH5MFP Position       */
#define SYS_GPH_MFPL_PH5MFP_Msk          (0xful << SYS_GPH_MFPL_PH5MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH5MFP Mask           */

#define SYS_GPH_MFPL_PH6MFP_Pos          (24)                                              /*!< SYS_T::GPH_MFPL: PH6MFP Position       */
#define SYS_GPH_MFPL_PH6MFP_Msk          (0xful << SYS_GPH_MFPL_PH6MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH6MFP Mask           */

#define SYS_GPH_MFPL_PH7MFP_Pos          (28)                                              /*!< SYS_T::GPH_MFPL: PH7MFP Position       */
#define SYS_GPH_MFPL_PH7MFP_Msk          (0xful << SYS_GPH_MFPL_PH7MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH7MFP Mask           */

#define SYS_GPH_MFPH_PH8MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFPH: PH8MFP Position       */
#define SYS_GPH_MFPH_PH8MFP_Msk          (0xful << SYS_GPH_MFPH_PH8MFP_Pos)                /*!< SYS_T::GPH_MFPH: PH8MFP Mask           */

#define SYS_GPH_MFPH_PH9MFP_Pos          (4)                                               /*!< SYS_T::GPH_MFPH: PH9MFP Position       */
#define SYS_GPH_MFPH_PH9MFP_Msk          (0xful << SYS_GPH_MFPH_PH9MFP_Pos)                /*!< SYS_T::GPH_MFPH: PH9MFP Mask           */

#define SYS_GPH_MFPH_PH10MFP_Pos         (8)                                               /*!< SYS_T::GPH_MFPH: PH10MFP Position      */
#define SYS_GPH_MFPH_PH10MFP_Msk         (0xful << SYS_GPH_MFPH_PH10MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH10MFP Mask          */

#define SYS_GPH_MFPH_PH11MFP_Pos         (12)                                              /*!< SYS_T::GPH_MFPH: PH11MFP Position      */
#define SYS_GPH_MFPH_PH11MFP_Msk         (0xful << SYS_GPH_MFPH_PH11MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH11MFP Mask          */

#define SYS_GPA_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPA_MFOS: MFOS0 Position        */
#define SYS_GPA_MFOS_MFOS0_Msk           (0x1ul << SYS_GPA_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS0 Mask            */

#define SYS_GPA_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPA_MFOS: MFOS1 Position        */
#define SYS_GPA_MFOS_MFOS1_Msk           (0x1ul << SYS_GPA_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS1 Mask            */

#define SYS_GPA_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPA_MFOS: MFOS2 Position        */
#define SYS_GPA_MFOS_MFOS2_Msk           (0x1ul << SYS_GPA_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS2 Mask            */

#define SYS_GPA_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPA_MFOS: MFOS3 Position        */
#define SYS_GPA_MFOS_MFOS3_Msk           (0x1ul << SYS_GPA_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS3 Mask            */

#define SYS_GPA_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPA_MFOS: MFOS4 Position        */
#define SYS_GPA_MFOS_MFOS4_Msk           (0x1ul << SYS_GPA_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS4 Mask            */

#define SYS_GPA_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPA_MFOS: MFOS5 Position        */
#define SYS_GPA_MFOS_MFOS5_Msk           (0x1ul << SYS_GPA_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS5 Mask            */

#define SYS_GPA_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPA_MFOS: MFOS6 Position        */
#define SYS_GPA_MFOS_MFOS6_Msk           (0x1ul << SYS_GPA_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS6 Mask            */

#define SYS_GPA_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPA_MFOS: MFOS7 Position        */
#define SYS_GPA_MFOS_MFOS7_Msk           (0x1ul << SYS_GPA_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS7 Mask            */

#define SYS_GPA_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPA_MFOS: MFOS8 Position        */
#define SYS_GPA_MFOS_MFOS8_Msk           (0x1ul << SYS_GPA_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS8 Mask            */

#define SYS_GPA_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPA_MFOS: MFOS9 Position        */
#define SYS_GPA_MFOS_MFOS9_Msk           (0x1ul << SYS_GPA_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS9 Mask            */

#define SYS_GPA_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPA_MFOS: MFOS10 Position       */
#define SYS_GPA_MFOS_MFOS10_Msk          (0x1ul << SYS_GPA_MFOS_MFOS10_Pos)                /*!< SYS_T::GPA_MFOS: MFOS10 Mask           */

#define SYS_GPA_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPA_MFOS: MFOS11 Position       */
#define SYS_GPA_MFOS_MFOS11_Msk          (0x1ul << SYS_GPA_MFOS_MFOS11_Pos)                /*!< SYS_T::GPA_MFOS: MFOS11 Mask           */

#define SYS_GPA_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPA_MFOS: MFOS12 Position       */
#define SYS_GPA_MFOS_MFOS12_Msk          (0x1ul << SYS_GPA_MFOS_MFOS12_Pos)                /*!< SYS_T::GPA_MFOS: MFOS12 Mask           */

#define SYS_GPA_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPA_MFOS: MFOS13 Position       */
#define SYS_GPA_MFOS_MFOS13_Msk          (0x1ul << SYS_GPA_MFOS_MFOS13_Pos)                /*!< SYS_T::GPA_MFOS: MFOS13 Mask           */

#define SYS_GPA_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPA_MFOS: MFOS14 Position       */
#define SYS_GPA_MFOS_MFOS14_Msk          (0x1ul << SYS_GPA_MFOS_MFOS14_Pos)                /*!< SYS_T::GPA_MFOS: MFOS14 Mask           */

#define SYS_GPA_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPA_MFOS: MFOS15 Position       */
#define SYS_GPA_MFOS_MFOS15_Msk          (0x1ul << SYS_GPA_MFOS_MFOS15_Pos)                /*!< SYS_T::GPA_MFOS: MFOS15 Mask           */

#define SYS_GPB_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPB_MFOS: MFOS0 Position        */
#define SYS_GPB_MFOS_MFOS0_Msk           (0x1ul << SYS_GPB_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS0 Mask            */

#define SYS_GPB_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPB_MFOS: MFOS1 Position        */
#define SYS_GPB_MFOS_MFOS1_Msk           (0x1ul << SYS_GPB_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS1 Mask            */

#define SYS_GPB_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPB_MFOS: MFOS2 Position        */
#define SYS_GPB_MFOS_MFOS2_Msk           (0x1ul << SYS_GPB_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS2 Mask            */

#define SYS_GPB_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPB_MFOS: MFOS3 Position        */
#define SYS_GPB_MFOS_MFOS3_Msk           (0x1ul << SYS_GPB_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS3 Mask            */

#define SYS_GPB_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPB_MFOS: MFOS4 Position        */
#define SYS_GPB_MFOS_MFOS4_Msk           (0x1ul << SYS_GPB_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS4 Mask            */

#define SYS_GPB_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPB_MFOS: MFOS5 Position        */
#define SYS_GPB_MFOS_MFOS5_Msk           (0x1ul << SYS_GPB_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS5 Mask            */

#define SYS_GPB_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPB_MFOS: MFOS6 Position        */
#define SYS_GPB_MFOS_MFOS6_Msk           (0x1ul << SYS_GPB_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS6 Mask            */

#define SYS_GPB_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPB_MFOS: MFOS7 Position        */
#define SYS_GPB_MFOS_MFOS7_Msk           (0x1ul << SYS_GPB_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS7 Mask            */

#define SYS_GPB_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPB_MFOS: MFOS8 Position        */
#define SYS_GPB_MFOS_MFOS8_Msk           (0x1ul << SYS_GPB_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS8 Mask            */

#define SYS_GPB_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPB_MFOS: MFOS9 Position        */
#define SYS_GPB_MFOS_MFOS9_Msk           (0x1ul << SYS_GPB_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS9 Mask            */

#define SYS_GPB_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPB_MFOS: MFOS10 Position       */
#define SYS_GPB_MFOS_MFOS10_Msk          (0x1ul << SYS_GPB_MFOS_MFOS10_Pos)                /*!< SYS_T::GPB_MFOS: MFOS10 Mask           */

#define SYS_GPB_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPB_MFOS: MFOS11 Position       */
#define SYS_GPB_MFOS_MFOS11_Msk          (0x1ul << SYS_GPB_MFOS_MFOS11_Pos)                /*!< SYS_T::GPB_MFOS: MFOS11 Mask           */

#define SYS_GPB_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPB_MFOS: MFOS12 Position       */
#define SYS_GPB_MFOS_MFOS12_Msk          (0x1ul << SYS_GPB_MFOS_MFOS12_Pos)                /*!< SYS_T::GPB_MFOS: MFOS12 Mask           */

#define SYS_GPB_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPB_MFOS: MFOS13 Position       */
#define SYS_GPB_MFOS_MFOS13_Msk          (0x1ul << SYS_GPB_MFOS_MFOS13_Pos)                /*!< SYS_T::GPB_MFOS: MFOS13 Mask           */

#define SYS_GPB_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPB_MFOS: MFOS14 Position       */
#define SYS_GPB_MFOS_MFOS14_Msk          (0x1ul << SYS_GPB_MFOS_MFOS14_Pos)                /*!< SYS_T::GPB_MFOS: MFOS14 Mask           */

#define SYS_GPB_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPB_MFOS: MFOS15 Position       */
#define SYS_GPB_MFOS_MFOS15_Msk          (0x1ul << SYS_GPB_MFOS_MFOS15_Pos)                /*!< SYS_T::GPB_MFOS: MFOS15 Mask           */

#define SYS_GPC_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPC_MFOS: MFOS0 Position        */
#define SYS_GPC_MFOS_MFOS0_Msk           (0x1ul << SYS_GPC_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS0 Mask            */

#define SYS_GPC_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPC_MFOS: MFOS1 Position        */
#define SYS_GPC_MFOS_MFOS1_Msk           (0x1ul << SYS_GPC_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS1 Mask            */

#define SYS_GPC_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPC_MFOS: MFOS2 Position        */
#define SYS_GPC_MFOS_MFOS2_Msk           (0x1ul << SYS_GPC_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS2 Mask            */

#define SYS_GPC_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPC_MFOS: MFOS3 Position        */
#define SYS_GPC_MFOS_MFOS3_Msk           (0x1ul << SYS_GPC_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS3 Mask            */

#define SYS_GPC_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPC_MFOS: MFOS4 Position        */
#define SYS_GPC_MFOS_MFOS4_Msk           (0x1ul << SYS_GPC_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS4 Mask            */

#define SYS_GPC_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPC_MFOS: MFOS5 Position        */
#define SYS_GPC_MFOS_MFOS5_Msk           (0x1ul << SYS_GPC_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS5 Mask            */

#define SYS_GPC_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPC_MFOS: MFOS6 Position        */
#define SYS_GPC_MFOS_MFOS6_Msk           (0x1ul << SYS_GPC_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS6 Mask            */

#define SYS_GPC_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPC_MFOS: MFOS7 Position        */
#define SYS_GPC_MFOS_MFOS7_Msk           (0x1ul << SYS_GPC_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS7 Mask            */

#define SYS_GPC_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPC_MFOS: MFOS8 Position        */
#define SYS_GPC_MFOS_MFOS8_Msk           (0x1ul << SYS_GPC_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS8 Mask            */

#define SYS_GPC_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPC_MFOS: MFOS9 Position        */
#define SYS_GPC_MFOS_MFOS9_Msk           (0x1ul << SYS_GPC_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS9 Mask            */

#define SYS_GPC_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPC_MFOS: MFOS10 Position       */
#define SYS_GPC_MFOS_MFOS10_Msk          (0x1ul << SYS_GPC_MFOS_MFOS10_Pos)                /*!< SYS_T::GPC_MFOS: MFOS10 Mask           */

#define SYS_GPC_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPC_MFOS: MFOS11 Position       */
#define SYS_GPC_MFOS_MFOS11_Msk          (0x1ul << SYS_GPC_MFOS_MFOS11_Pos)                /*!< SYS_T::GPC_MFOS: MFOS11 Mask           */

#define SYS_GPC_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPC_MFOS: MFOS12 Position       */
#define SYS_GPC_MFOS_MFOS12_Msk          (0x1ul << SYS_GPC_MFOS_MFOS12_Pos)                /*!< SYS_T::GPC_MFOS: MFOS12 Mask           */

#define SYS_GPC_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPC_MFOS: MFOS13 Position       */
#define SYS_GPC_MFOS_MFOS13_Msk          (0x1ul << SYS_GPC_MFOS_MFOS13_Pos)                /*!< SYS_T::GPC_MFOS: MFOS13 Mask           */

#define SYS_GPD_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPD_MFOS: MFOS0 Position        */
#define SYS_GPD_MFOS_MFOS0_Msk           (0x1ul << SYS_GPD_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS0 Mask            */

#define SYS_GPD_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPD_MFOS: MFOS1 Position        */
#define SYS_GPD_MFOS_MFOS1_Msk           (0x1ul << SYS_GPD_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS1 Mask            */

#define SYS_GPD_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPD_MFOS: MFOS2 Position        */
#define SYS_GPD_MFOS_MFOS2_Msk           (0x1ul << SYS_GPD_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS2 Mask            */

#define SYS_GPD_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPD_MFOS: MFOS3 Position        */
#define SYS_GPD_MFOS_MFOS3_Msk           (0x1ul << SYS_GPD_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS3 Mask            */

#define SYS_GPD_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPD_MFOS: MFOS4 Position        */
#define SYS_GPD_MFOS_MFOS4_Msk           (0x1ul << SYS_GPD_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS4 Mask            */

#define SYS_GPD_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPD_MFOS: MFOS5 Position        */
#define SYS_GPD_MFOS_MFOS5_Msk           (0x1ul << SYS_GPD_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS5 Mask            */

#define SYS_GPD_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPD_MFOS: MFOS6 Position        */
#define SYS_GPD_MFOS_MFOS6_Msk           (0x1ul << SYS_GPD_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS6 Mask            */

#define SYS_GPD_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPD_MFOS: MFOS7 Position        */
#define SYS_GPD_MFOS_MFOS7_Msk           (0x1ul << SYS_GPD_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS7 Mask            */

#define SYS_GPD_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPD_MFOS: MFOS8 Position        */
#define SYS_GPD_MFOS_MFOS8_Msk           (0x1ul << SYS_GPD_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS8 Mask            */

#define SYS_GPD_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPD_MFOS: MFOS9 Position        */
#define SYS_GPD_MFOS_MFOS9_Msk           (0x1ul << SYS_GPD_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS9 Mask            */

#define SYS_GPD_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPD_MFOS: MFOS10 Position       */
#define SYS_GPD_MFOS_MFOS10_Msk          (0x1ul << SYS_GPD_MFOS_MFOS10_Pos)                /*!< SYS_T::GPD_MFOS: MFOS10 Mask           */

#define SYS_GPD_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPD_MFOS: MFOS11 Position       */
#define SYS_GPD_MFOS_MFOS11_Msk          (0x1ul << SYS_GPD_MFOS_MFOS11_Pos)                /*!< SYS_T::GPD_MFOS: MFOS11 Mask           */

#define SYS_GPD_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPD_MFOS: MFOS12 Position       */
#define SYS_GPD_MFOS_MFOS12_Msk          (0x1ul << SYS_GPD_MFOS_MFOS12_Pos)                /*!< SYS_T::GPD_MFOS: MFOS12 Mask           */

#define SYS_GPD_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPD_MFOS: MFOS14 Position       */
#define SYS_GPD_MFOS_MFOS14_Msk          (0x1ul << SYS_GPD_MFOS_MFOS14_Pos)                /*!< SYS_T::GPD_MFOS: MFOS14 Mask           */

#define SYS_GPE_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPE_MFOS: MFOS0 Position        */
#define SYS_GPE_MFOS_MFOS0_Msk           (0x1ul << SYS_GPE_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS0 Mask            */

#define SYS_GPE_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPE_MFOS: MFOS1 Position        */
#define SYS_GPE_MFOS_MFOS1_Msk           (0x1ul << SYS_GPE_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS1 Mask            */

#define SYS_GPE_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPE_MFOS: MFOS2 Position        */
#define SYS_GPE_MFOS_MFOS2_Msk           (0x1ul << SYS_GPE_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS2 Mask            */

#define SYS_GPE_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPE_MFOS: MFOS3 Position        */
#define SYS_GPE_MFOS_MFOS3_Msk           (0x1ul << SYS_GPE_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS3 Mask            */

#define SYS_GPE_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPE_MFOS: MFOS4 Position        */
#define SYS_GPE_MFOS_MFOS4_Msk           (0x1ul << SYS_GPE_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS4 Mask            */

#define SYS_GPE_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPE_MFOS: MFOS5 Position        */
#define SYS_GPE_MFOS_MFOS5_Msk           (0x1ul << SYS_GPE_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS5 Mask            */

#define SYS_GPE_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPE_MFOS: MFOS6 Position        */
#define SYS_GPE_MFOS_MFOS6_Msk           (0x1ul << SYS_GPE_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS6 Mask            */

#define SYS_GPE_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPE_MFOS: MFOS7 Position        */
#define SYS_GPE_MFOS_MFOS7_Msk           (0x1ul << SYS_GPE_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS7 Mask            */

#define SYS_GPE_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPE_MFOS: MFOS8 Position        */
#define SYS_GPE_MFOS_MFOS8_Msk           (0x1ul << SYS_GPE_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS8 Mask            */

#define SYS_GPE_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPE_MFOS: MFOS9 Position        */
#define SYS_GPE_MFOS_MFOS9_Msk           (0x1ul << SYS_GPE_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS9 Mask            */

#define SYS_GPE_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPE_MFOS: MFOS10 Position       */
#define SYS_GPE_MFOS_MFOS10_Msk          (0x1ul << SYS_GPE_MFOS_MFOS10_Pos)                /*!< SYS_T::GPE_MFOS: MFOS10 Mask           */

#define SYS_GPE_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPE_MFOS: MFOS11 Position       */
#define SYS_GPE_MFOS_MFOS11_Msk          (0x1ul << SYS_GPE_MFOS_MFOS11_Pos)                /*!< SYS_T::GPE_MFOS: MFOS11 Mask           */

#define SYS_GPE_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPE_MFOS: MFOS12 Position       */
#define SYS_GPE_MFOS_MFOS12_Msk          (0x1ul << SYS_GPE_MFOS_MFOS12_Pos)                /*!< SYS_T::GPE_MFOS: MFOS12 Mask           */

#define SYS_GPE_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPE_MFOS: MFOS13 Position       */
#define SYS_GPE_MFOS_MFOS13_Msk          (0x1ul << SYS_GPE_MFOS_MFOS13_Pos)                /*!< SYS_T::GPE_MFOS: MFOS13 Mask           */

#define SYS_GPE_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPE_MFOS: MFOS14 Position       */
#define SYS_GPE_MFOS_MFOS14_Msk          (0x1ul << SYS_GPE_MFOS_MFOS14_Pos)                /*!< SYS_T::GPE_MFOS: MFOS14 Mask           */

#define SYS_GPE_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPE_MFOS: MFOS15 Position       */
#define SYS_GPE_MFOS_MFOS15_Msk          (0x1ul << SYS_GPE_MFOS_MFOS15_Pos)                /*!< SYS_T::GPE_MFOS: MFOS15 Mask           */

#define SYS_GPF_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPF_MFOS: MFOS0 Position        */
#define SYS_GPF_MFOS_MFOS0_Msk           (0x1ul << SYS_GPF_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS0 Mask            */

#define SYS_GPF_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPF_MFOS: MFOS1 Position        */
#define SYS_GPF_MFOS_MFOS1_Msk           (0x1ul << SYS_GPF_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS1 Mask            */

#define SYS_GPF_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPF_MFOS: MFOS2 Position        */
#define SYS_GPF_MFOS_MFOS2_Msk           (0x1ul << SYS_GPF_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS2 Mask            */

#define SYS_GPF_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPF_MFOS: MFOS3 Position        */
#define SYS_GPF_MFOS_MFOS3_Msk           (0x1ul << SYS_GPF_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS3 Mask            */

#define SYS_GPF_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPF_MFOS: MFOS4 Position        */
#define SYS_GPF_MFOS_MFOS4_Msk           (0x1ul << SYS_GPF_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS4 Mask            */

#define SYS_GPF_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPF_MFOS: MFOS5 Position        */
#define SYS_GPF_MFOS_MFOS5_Msk           (0x1ul << SYS_GPF_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS5 Mask            */

#define SYS_GPF_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPF_MFOS: MFOS6 Position        */
#define SYS_GPF_MFOS_MFOS6_Msk           (0x1ul << SYS_GPF_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS6 Mask            */

#define SYS_GPF_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPF_MFOS: MFOS7 Position        */
#define SYS_GPF_MFOS_MFOS7_Msk           (0x1ul << SYS_GPF_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS7 Mask            */

#define SYS_GPF_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPF_MFOS: MFOS8 Position        */
#define SYS_GPF_MFOS_MFOS8_Msk           (0x1ul << SYS_GPF_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS8 Mask            */

#define SYS_GPF_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPF_MFOS: MFOS9 Position        */
#define SYS_GPF_MFOS_MFOS9_Msk           (0x1ul << SYS_GPF_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS9 Mask            */

#define SYS_GPF_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPF_MFOS: MFOS10 Position       */
#define SYS_GPF_MFOS_MFOS10_Msk          (0x1ul << SYS_GPF_MFOS_MFOS10_Pos)                /*!< SYS_T::GPF_MFOS: MFOS10 Mask           */

#define SYS_GPF_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPF_MFOS: MFOS11 Position       */
#define SYS_GPF_MFOS_MFOS11_Msk          (0x1ul << SYS_GPF_MFOS_MFOS11_Pos)                /*!< SYS_T::GPF_MFOS: MFOS11 Mask           */

#define SYS_GPG_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPG_MFOS: MFOS2 Position        */
#define SYS_GPG_MFOS_MFOS2_Msk           (0x1ul << SYS_GPG_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS2 Mask            */

#define SYS_GPG_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPG_MFOS: MFOS3 Position        */
#define SYS_GPG_MFOS_MFOS3_Msk           (0x1ul << SYS_GPG_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS3 Mask            */

#define SYS_GPG_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPG_MFOS: MFOS4 Position        */
#define SYS_GPG_MFOS_MFOS4_Msk           (0x1ul << SYS_GPG_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS4 Mask            */

#define SYS_GPG_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPG_MFOS: MFOS9 Position        */
#define SYS_GPG_MFOS_MFOS9_Msk           (0x1ul << SYS_GPG_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS9 Mask            */

#define SYS_GPG_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPG_MFOS: MFOS10 Position       */
#define SYS_GPG_MFOS_MFOS10_Msk          (0x1ul << SYS_GPG_MFOS_MFOS10_Pos)                /*!< SYS_T::GPG_MFOS: MFOS10 Mask           */

#define SYS_GPG_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPG_MFOS: MFOS11 Position       */
#define SYS_GPG_MFOS_MFOS11_Msk          (0x1ul << SYS_GPG_MFOS_MFOS11_Pos)                /*!< SYS_T::GPG_MFOS: MFOS11 Mask           */

#define SYS_GPG_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPG_MFOS: MFOS12 Position       */
#define SYS_GPG_MFOS_MFOS12_Msk          (0x1ul << SYS_GPG_MFOS_MFOS12_Pos)                /*!< SYS_T::GPG_MFOS: MFOS12 Mask           */

#define SYS_GPG_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPG_MFOS: MFOS13 Position       */
#define SYS_GPG_MFOS_MFOS13_Msk          (0x1ul << SYS_GPG_MFOS_MFOS13_Pos)                /*!< SYS_T::GPG_MFOS: MFOS13 Mask           */

#define SYS_GPG_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPG_MFOS: MFOS14 Position       */
#define SYS_GPG_MFOS_MFOS14_Msk          (0x1ul << SYS_GPG_MFOS_MFOS14_Pos)                /*!< SYS_T::GPG_MFOS: MFOS14 Mask           */

#define SYS_GPG_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPG_MFOS: MFOS15 Position       */
#define SYS_GPG_MFOS_MFOS15_Msk          (0x1ul << SYS_GPG_MFOS_MFOS15_Pos)                /*!< SYS_T::GPG_MFOS: MFOS15 Mask           */

#define SYS_GPH_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPH_MFOS: MFOS4 Position        */
#define SYS_GPH_MFOS_MFOS4_Msk           (0x1ul << SYS_GPH_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS4 Mask            */

#define SYS_GPH_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPH_MFOS: MFOS5 Position        */
#define SYS_GPH_MFOS_MFOS5_Msk           (0x1ul << SYS_GPH_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS5 Mask            */

#define SYS_GPH_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPH_MFOS: MFOS6 Position        */
#define SYS_GPH_MFOS_MFOS6_Msk           (0x1ul << SYS_GPH_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS6 Mask            */

#define SYS_GPH_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPH_MFOS: MFOS7 Position        */
#define SYS_GPH_MFOS_MFOS7_Msk           (0x1ul << SYS_GPH_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS7 Mask            */

#define SYS_GPH_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPH_MFOS: MFOS8 Position        */
#define SYS_GPH_MFOS_MFOS8_Msk           (0x1ul << SYS_GPH_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS8 Mask            */

#define SYS_GPH_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPH_MFOS: MFOS9 Position        */
#define SYS_GPH_MFOS_MFOS9_Msk           (0x1ul << SYS_GPH_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS9 Mask            */

#define SYS_GPH_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPH_MFOS: MFOS10 Position       */
#define SYS_GPH_MFOS_MFOS10_Msk          (0x1ul << SYS_GPH_MFOS_MFOS10_Pos)                /*!< SYS_T::GPH_MFOS: MFOS10 Mask           */

#define SYS_GPH_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPH_MFOS: MFOS11 Position       */
#define SYS_GPH_MFOS_MFOS11_Msk          (0x1ul << SYS_GPH_MFOS_MFOS11_Pos)                /*!< SYS_T::GPH_MFOS: MFOS11 Mask           */

#define SYS_VTORSET_VTORSET_Pos          (11)                                              /*!< SYS_T::VTORSET: VTORSET Position       */
#define SYS_VTORSET_VTORSET_Msk          (0x3fffful << SYS_VTORSET_VTORSET_Pos)            /*!< SYS_T::VTORSET: VTORSET Mask           */

#define SYS_SRAMICTL_PERRIEN_Pos         (0)                                               /*!< SYS_T::SRAMICTL: PERRIEN Position      */
#define SYS_SRAMICTL_PERRIEN_Msk         (0x1ul << SYS_SRAMICTL_PERRIEN_Pos)               /*!< SYS_T::SRAMICTL: PERRIEN Mask          */

#define SYS_SRAMSTS_PERRIF_Pos           (0)                                               /*!< SYS_T::SRAMSTS: PERRIF Position        */
#define SYS_SRAMSTS_PERRIF_Msk           (0x1ul << SYS_SRAMSTS_PERRIF_Pos)                 /*!< SYS_T::SRAMSTS: PERRIF Mask            */

#define SYS_SRAMEADR_ERRADDR_Pos         (0)                                               /*!< SYS_T::SRAMEADR: ERRADDR Position      */
#define SYS_SRAMEADR_ERRADDR_Msk         (0xfffffffful << SYS_SRAMEADR_ERRADDR_Pos)        /*!< SYS_T::SRAMEADR: ERRADDR Mask          */

#define SYS_SRAMPC0_SRAM0PM0_Pos         (0)                                               /*!< SYS_T::SRAMPC0: SRAM0PM0 Position      */
#define SYS_SRAMPC0_SRAM0PM0_Msk         (0x3ul << SYS_SRAMPC0_SRAM0PM0_Pos)               /*!< SYS_T::SRAMPC0: SRAM0PM0 Mask          */

#define SYS_SRAMPC0_SRAM0PM1_Pos         (2)                                               /*!< SYS_T::SRAMPC0: SRAM0PM1 Position      */
#define SYS_SRAMPC0_SRAM0PM1_Msk         (0x3ul << SYS_SRAMPC0_SRAM0PM1_Pos)               /*!< SYS_T::SRAMPC0: SRAM0PM1 Mask          */

#define SYS_SRAMPC0_SRAM0PM2_Pos         (4)                                               /*!< SYS_T::SRAMPC0: SRAM0PM2 Position      */
#define SYS_SRAMPC0_SRAM0PM2_Msk         (0x3ul << SYS_SRAMPC0_SRAM0PM2_Pos)               /*!< SYS_T::SRAMPC0: SRAM0PM2 Mask          */

#define SYS_SRAMPC0_SRAM0PM3_Pos         (6)                                               /*!< SYS_T::SRAMPC0: SRAM0PM3 Position      */
#define SYS_SRAMPC0_SRAM0PM3_Msk         (0x3ul << SYS_SRAMPC0_SRAM0PM3_Pos)               /*!< SYS_T::SRAMPC0: SRAM0PM3 Mask          */

#define SYS_SRAMPC0_SRAM0PM4_Pos         (8)                                               /*!< SYS_T::SRAMPC0: SRAM0PM4 Position      */
#define SYS_SRAMPC0_SRAM0PM4_Msk         (0x3ul << SYS_SRAMPC0_SRAM0PM4_Pos)               /*!< SYS_T::SRAMPC0: SRAM0PM4 Mask          */

#define SYS_SRAMPC0_SRAM1PM0_Pos         (10)                                              /*!< SYS_T::SRAMPC0: SRAM1PM0 Position      */
#define SYS_SRAMPC0_SRAM1PM0_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM0_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM0 Mask          */

#define SYS_SRAMPC0_SRAM1PM1_Pos         (12)                                              /*!< SYS_T::SRAMPC0: SRAM1PM1 Position      */
#define SYS_SRAMPC0_SRAM1PM1_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM1_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM1 Mask          */

#define SYS_SRAMPC0_SRAM1PM2_Pos         (14)                                              /*!< SYS_T::SRAMPC0: SRAM1PM2 Position      */
#define SYS_SRAMPC0_SRAM1PM2_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM2_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM2 Mask          */

#define SYS_SRAMPC0_SRAM1PM3_Pos         (16)                                              /*!< SYS_T::SRAMPC0: SRAM1PM3 Position      */
#define SYS_SRAMPC0_SRAM1PM3_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM3_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM3 Mask          */

#define SYS_SRAMPC0_SRAM1PM4_Pos         (18)                                              /*!< SYS_T::SRAMPC0: SRAM1PM4 Position      */
#define SYS_SRAMPC0_SRAM1PM4_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM4_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM4 Mask          */

#define SYS_SRAMPC0_SRAM1PM5_Pos         (20)                                              /*!< SYS_T::SRAMPC0: SRAM1PM5 Position      */
#define SYS_SRAMPC0_SRAM1PM5_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM5_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM5 Mask          */

#define SYS_SRAMPC0_SRAM1PM6_Pos         (22)                                              /*!< SYS_T::SRAMPC0: SRAM1PM6 Position      */
#define SYS_SRAMPC0_SRAM1PM6_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM6_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM6 Mask          */

#define SYS_SRAMPC0_SRAM1PM7_Pos         (24)                                              /*!< SYS_T::SRAMPC0: SRAM1PM7 Position      */
#define SYS_SRAMPC0_SRAM1PM7_Msk         (0x3ul << SYS_SRAMPC0_SRAM1PM7_Pos)               /*!< SYS_T::SRAMPC0: SRAM1PM7 Mask          */

#define SYS_SRAMPC0_SRAM2PM0_Pos         (26)                                              /*!< SYS_T::SRAMPC0: SRAM2PM0 Position      */
#define SYS_SRAMPC0_SRAM2PM0_Msk         (0x3ul << SYS_SRAMPC0_SRAM2PM0_Pos)               /*!< SYS_T::SRAMPC0: SRAM2PM0 Mask          */

#define SYS_SRAMPC0_SRAM2PM1_Pos         (28)                                              /*!< SYS_T::SRAMPC0: SRAM2PM1 Position      */
#define SYS_SRAMPC0_SRAM2PM1_Msk         (0x3ul << SYS_SRAMPC0_SRAM2PM1_Pos)               /*!< SYS_T::SRAMPC0: SRAM2PM1 Mask          */

#define SYS_SRAMPC0_PCBUSY_Pos           (31)                                              /*!< SYS_T::SRAMPC0: PCBUSY Position        */
#define SYS_SRAMPC0_PCBUSY_Msk           (0x1ul << SYS_SRAMPC0_PCBUSY_Pos)                 /*!< SYS_T::SRAMPC0: PCBUSY Mask            */

#define SYS_SRAMPC1_SRAM2PM2_Pos         (0)                                               /*!< SYS_T::SRAMPC1: SRAM2PM2 Position      */
#define SYS_SRAMPC1_SRAM2PM2_Msk         (0x3ul << SYS_SRAMPC1_SRAM2PM2_Pos)               /*!< SYS_T::SRAMPC1: SRAM2PM2 Mask          */

#define SYS_SRAMPC1_SRAM2PM3_Pos         (2)                                               /*!< SYS_T::SRAMPC1: SRAM2PM3 Position      */
#define SYS_SRAMPC1_SRAM2PM3_Msk         (0x3ul << SYS_SRAMPC1_SRAM2PM3_Pos)               /*!< SYS_T::SRAMPC1: SRAM2PM3 Mask          */

#define SYS_SRAMPC1_SRAM2PM4_Pos         (4)                                               /*!< SYS_T::SRAMPC1: SRAM2PM4 Position      */
#define SYS_SRAMPC1_SRAM2PM4_Msk         (0x3ul << SYS_SRAMPC1_SRAM2PM4_Pos)               /*!< SYS_T::SRAMPC1: SRAM2PM4 Mask          */

#define SYS_SRAMPC1_SRAM2PM5_Pos         (6)                                               /*!< SYS_T::SRAMPC1: SRAM2PM5 Position      */
#define SYS_SRAMPC1_SRAM2PM5_Msk         (0x3ul << SYS_SRAMPC1_SRAM2PM5_Pos)               /*!< SYS_T::SRAMPC1: SRAM2PM5 Mask          */

#define SYS_SRAMPC1_CAN_Pos              (16)                                              /*!< SYS_T::SRAMPC1: CAN Position           */
#define SYS_SRAMPC1_CAN_Msk              (0x3ul << SYS_SRAMPC1_CAN_Pos)                    /*!< SYS_T::SRAMPC1: CAN Mask               */

#define SYS_SRAMPC1_USBD_Pos             (18)                                              /*!< SYS_T::SRAMPC1: USBD Position          */
#define SYS_SRAMPC1_USBD_Msk             (0x3ul << SYS_SRAMPC1_USBD_Pos)                   /*!< SYS_T::SRAMPC1: USBD Mask              */

#define SYS_SRAMPC1_PDMA0_Pos            (20)                                              /*!< SYS_T::SRAMPC1: PDMA0 Position         */
#define SYS_SRAMPC1_PDMA0_Msk            (0x3ul << SYS_SRAMPC1_PDMA0_Pos)                  /*!< SYS_T::SRAMPC1: PDMA0 Mask             */

#define SYS_SRAMPC1_PDMA1_Pos            (22)                                              /*!< SYS_T::SRAMPC1: PDMA1 Position         */
#define SYS_SRAMPC1_PDMA1_Msk            (0x3ul << SYS_SRAMPC1_PDMA1_Pos)                  /*!< SYS_T::SRAMPC1: PDMA1 Mask             */

#define SYS_SRAMPC1_FMCCACHE_Pos         (24)                                              /*!< SYS_T::SRAMPC1: FMCCACHE Position      */
#define SYS_SRAMPC1_FMCCACHE_Msk         (0x3ul << SYS_SRAMPC1_FMCCACHE_Pos)               /*!< SYS_T::SRAMPC1: FMCCACHE Mask          */

#define SYS_SRAMPC1_RSA_Pos              (26)                                              /*!< SYS_T::SRAMPC1: RSA Position           */
#define SYS_SRAMPC1_RSA_Msk              (0x3ul << SYS_SRAMPC1_RSA_Pos)                    /*!< SYS_T::SRAMPC1: RSA Mask               */

#define SYS_SRAMPC1_KS_Pos               (28)                                              /*!< SYS_T::SRAMPC1: KS Position            */
#define SYS_SRAMPC1_KS_Msk               (0x3ul << SYS_SRAMPC1_KS_Pos)                     /*!< SYS_T::SRAMPC1: KS Mask                */

#define SYS_SRAMPC1_PCBUSY_Pos           (31)                                              /*!< SYS_T::SRAMPC1: PCBUSY Position        */
#define SYS_SRAMPC1_PCBUSY_Msk           (0x1ul << SYS_SRAMPC1_PCBUSY_Pos)                 /*!< SYS_T::SRAMPC1: PCBUSY Mask            */

#define SYS_TCTL48M_FREQSEL_Pos          (0)                                               /*!< SYS_T::TCTL48M: FREQSEL Position       */
#define SYS_TCTL48M_FREQSEL_Msk          (0x3ul << SYS_TCTL48M_FREQSEL_Pos)                /*!< SYS_T::TCTL48M: FREQSEL Mask           */

#define SYS_TCTL48M_LOOPSEL_Pos          (4)                                               /*!< SYS_T::TCTL48M: LOOPSEL Position       */
#define SYS_TCTL48M_LOOPSEL_Msk          (0x3ul << SYS_TCTL48M_LOOPSEL_Pos)                /*!< SYS_T::TCTL48M: LOOPSEL Mask           */

#define SYS_TCTL48M_RETRYCNT_Pos         (6)                                               /*!< SYS_T::TCTL48M: RETRYCNT Position      */
#define SYS_TCTL48M_RETRYCNT_Msk         (0x3ul << SYS_TCTL48M_RETRYCNT_Pos)               /*!< SYS_T::TCTL48M: RETRYCNT Mask          */

#define SYS_TCTL48M_CESTOPEN_Pos         (8)                                               /*!< SYS_T::TCTL48M: CESTOPEN Position      */
#define SYS_TCTL48M_CESTOPEN_Msk         (0x1ul << SYS_TCTL48M_CESTOPEN_Pos)               /*!< SYS_T::TCTL48M: CESTOPEN Mask          */

#define SYS_TCTL48M_BOUNDEN_Pos          (9)                                               /*!< SYS_T::TCTL48M: BOUNDEN Position       */
#define SYS_TCTL48M_BOUNDEN_Msk          (0x1ul << SYS_TCTL48M_BOUNDEN_Pos)                /*!< SYS_T::TCTL48M: BOUNDEN Mask           */

#define SYS_TCTL48M_REFCKSEL_Pos         (10)                                              /*!< SYS_T::TCTL48M: REFCKSEL Position      */
#define SYS_TCTL48M_REFCKSEL_Msk         (0x1ul << SYS_TCTL48M_REFCKSEL_Pos)               /*!< SYS_T::TCTL48M: REFCKSEL Mask          */

#define SYS_TCTL48M_BOUNDARY_Pos         (16)                                              /*!< SYS_T::TCTL48M: BOUNDARY Position      */
#define SYS_TCTL48M_BOUNDARY_Msk         (0x1ful << SYS_TCTL48M_BOUNDARY_Pos)              /*!< SYS_T::TCTL48M: BOUNDARY Mask          */

#define SYS_TIEN48M_TFAILIEN_Pos         (1)                                               /*!< SYS_T::TIEN48M: TFAILIEN Position      */
#define SYS_TIEN48M_TFAILIEN_Msk         (0x1ul << SYS_TIEN48M_TFAILIEN_Pos)               /*!< SYS_T::TIEN48M: TFAILIEN Mask          */

#define SYS_TIEN48M_CLKEIEN_Pos          (2)                                               /*!< SYS_T::TIEN48M: CLKEIEN Position       */
#define SYS_TIEN48M_CLKEIEN_Msk          (0x1ul << SYS_TIEN48M_CLKEIEN_Pos)                /*!< SYS_T::TIEN48M: CLKEIEN Mask           */

#define SYS_TISTS48M_FREQLOCK_Pos        (0)                                               /*!< SYS_T::TISTS48M: FREQLOCK Position     */
#define SYS_TISTS48M_FREQLOCK_Msk        (0x1ul << SYS_TISTS48M_FREQLOCK_Pos)              /*!< SYS_T::TISTS48M: FREQLOCK Mask         */

#define SYS_TISTS48M_TFAILIF_Pos         (1)                                               /*!< SYS_T::TISTS48M: TFAILIF Position      */
#define SYS_TISTS48M_TFAILIF_Msk         (0x1ul << SYS_TISTS48M_TFAILIF_Pos)               /*!< SYS_T::TISTS48M: TFAILIF Mask          */

#define SYS_TISTS48M_CLKERRIF_Pos        (2)                                               /*!< SYS_T::TISTS48M: CLKERRIF Position     */
#define SYS_TISTS48M_CLKERRIF_Msk        (0x1ul << SYS_TISTS48M_CLKERRIF_Pos)              /*!< SYS_T::TISTS48M: CLKERRIF Mask         */

#define SYS_TISTS48M_OVBDIF_Pos          (3)                                               /*!< SYS_T::TISTS48M: OVBDIF Position       */
#define SYS_TISTS48M_OVBDIF_Msk          (0x1ul << SYS_TISTS48M_OVBDIF_Pos)                /*!< SYS_T::TISTS48M: OVBDIF Mask           */

#define SYS_TCTL12M_FREQSEL_Pos          (0)                                               /*!< SYS_T::TCTL12M: FREQSEL Position       */
#define SYS_TCTL12M_FREQSEL_Msk          (0x3ul << SYS_TCTL12M_FREQSEL_Pos)                /*!< SYS_T::TCTL12M: FREQSEL Mask           */

#define SYS_TCTL12M_LOOPSEL_Pos          (4)                                               /*!< SYS_T::TCTL12M: LOOPSEL Position       */
#define SYS_TCTL12M_LOOPSEL_Msk          (0x3ul << SYS_TCTL12M_LOOPSEL_Pos)                /*!< SYS_T::TCTL12M: LOOPSEL Mask           */

#define SYS_TCTL12M_RETRYCNT_Pos         (6)                                               /*!< SYS_T::TCTL12M: RETRYCNT Position      */
#define SYS_TCTL12M_RETRYCNT_Msk         (0x3ul << SYS_TCTL12M_RETRYCNT_Pos)               /*!< SYS_T::TCTL12M: RETRYCNT Mask          */

#define SYS_TCTL12M_CESTOPEN_Pos         (8)                                               /*!< SYS_T::TCTL12M: CESTOPEN Position      */
#define SYS_TCTL12M_CESTOPEN_Msk         (0x1ul << SYS_TCTL12M_CESTOPEN_Pos)               /*!< SYS_T::TCTL12M: CESTOPEN Mask          */

#define SYS_TCTL12M_BOUNDEN_Pos          (9)                                               /*!< SYS_T::TCTL12M: BOUNDEN Position       */
#define SYS_TCTL12M_BOUNDEN_Msk          (0x1ul << SYS_TCTL12M_BOUNDEN_Pos)                /*!< SYS_T::TCTL12M: BOUNDEN Mask           */

#define SYS_TCTL12M_REFCKSEL_Pos         (10)                                              /*!< SYS_T::TCTL12M: REFCKSEL Position      */
#define SYS_TCTL12M_REFCKSEL_Msk         (0x1ul << SYS_TCTL12M_REFCKSEL_Pos)               /*!< SYS_T::TCTL12M: REFCKSEL Mask          */

#define SYS_TCTL12M_BOUNDARY_Pos         (16)                                              /*!< SYS_T::TCTL12M: BOUNDARY Position      */
#define SYS_TCTL12M_BOUNDARY_Msk         (0x1ful << SYS_TCTL12M_BOUNDARY_Pos)              /*!< SYS_T::TCTL12M: BOUNDARY Mask          */

#define SYS_TIEN12M_TFAILIEN_Pos         (1)                                               /*!< SYS_T::TIEN12M: TFAILIEN Position      */
#define SYS_TIEN12M_TFAILIEN_Msk         (0x1ul << SYS_TIEN12M_TFAILIEN_Pos)               /*!< SYS_T::TIEN12M: TFAILIEN Mask          */

#define SYS_TIEN12M_CLKEIEN_Pos          (2)                                               /*!< SYS_T::TIEN12M: CLKEIEN Position       */
#define SYS_TIEN12M_CLKEIEN_Msk          (0x1ul << SYS_TIEN12M_CLKEIEN_Pos)                /*!< SYS_T::TIEN12M: CLKEIEN Mask           */

#define SYS_TISTS12M_FREQLOCK_Pos        (0)                                               /*!< SYS_T::TISTS12M: FREQLOCK Position     */
#define SYS_TISTS12M_FREQLOCK_Msk        (0x1ul << SYS_TISTS12M_FREQLOCK_Pos)              /*!< SYS_T::TISTS12M: FREQLOCK Mask         */

#define SYS_TISTS12M_TFAILIF_Pos         (1)                                               /*!< SYS_T::TISTS12M: TFAILIF Position      */
#define SYS_TISTS12M_TFAILIF_Msk         (0x1ul << SYS_TISTS12M_TFAILIF_Pos)               /*!< SYS_T::TISTS12M: TFAILIF Mask          */

#define SYS_TISTS12M_CLKERRIF_Pos        (2)                                               /*!< SYS_T::TISTS12M: CLKERRIF Position     */
#define SYS_TISTS12M_CLKERRIF_Msk        (0x1ul << SYS_TISTS12M_CLKERRIF_Pos)              /*!< SYS_T::TISTS12M: CLKERRIF Mask         */

#define SYS_TISTS12M_OVBDIF_Pos          (3)                                               /*!< SYS_T::TISTS12M: OVBDIF Position       */
#define SYS_TISTS12M_OVBDIF_Msk          (0x1ul << SYS_TISTS12M_OVBDIF_Pos)                /*!< SYS_T::TISTS12M: OVBDIF Mask           */

#define SYS_REGLCTL_REGLCTL_Pos          (0)                                               /*!< SYS_T::REGLCTL: REGLCTL Position       */
#define SYS_REGLCTL_REGLCTL_Msk          (0xfful << SYS_REGLCTL_REGLCTL_Pos)               /*!< SYS_T::REGLCTL: REGLCTL Mask           */

#define SYS_CPUCFG_INTRTEN_Pos           (0)                                               /*!< SYS_T::CPUCFG: INTRTEN Position        */
#define SYS_CPUCFG_INTRTEN_Msk           (0x1ul << SYS_CPUCFG_INTRTEN_Pos)                 /*!< SYS_T::CPUCFG: INTRTEN Mask            */

#define SYS_OVDCTL_OVDEN_Pos             (0)                                               /*!< SYS_T::OVDCTL: OVDEN Position          */
#define SYS_OVDCTL_OVDEN_Msk             (0x1ul << SYS_OVDCTL_OVDEN_Pos)                   /*!< SYS_T::OVDCTL: OVDEN Mask              */

#define SYS_OVDCTL_OVDSTB_Pos            (31)                                              /*!< SYS_T::OVDCTL: OVDSTB Position         */
#define SYS_OVDCTL_OVDSTB_Msk            (0x1ul << SYS_OVDCTL_OVDSTB_Pos)                  /*!< SYS_T::OVDCTL: OVDSTB Mask             */

#define SYS_PORCTL1_POROFF_Pos           (0)                                               /*!< SYS_T::PORCTL1: POROFF Position        */
#define SYS_PORCTL1_POROFF_Msk           (0xfffful << SYS_PORCTL1_POROFF_Pos)              /*!< SYS_T::PORCTL1: POROFF Mask            */

#define SYS_PSWCTL_CRPTPWREN_Pos         (12)                                              /*!< SYS_T::PSWCTL: CRPTPWREN Position      */
#define SYS_PSWCTL_CRPTPWREN_Msk         (0x1ul << SYS_PSWCTL_CRPTPWREN_Pos)               /*!< SYS_T::PSWCTL: CRPTPWREN Mask          */

#define SYS_PLCTL_PLSEL_Pos              (0)                                               /*!< SYS_T::PLCTL: PLSEL Position           */
#define SYS_PLCTL_PLSEL_Msk              (0x3ul << SYS_PLCTL_PLSEL_Pos)                    /*!< SYS_T::PLCTL: PLSEL Mask               */

#define SYS_PLCTL_MVRS_Pos               (4)                                               /*!< SYS_T::PLCTL: MVRS Position            */
#define SYS_PLCTL_MVRS_Msk               (0x1ul << SYS_PLCTL_MVRS_Pos)                     /*!< SYS_T::PLCTL: MVRS Mask                */

#define SYS_PLCTL_WRBUSY_Pos             (7)                                               /*!< SYS_T::PLCTL: WRBUSY Position          */
#define SYS_PLCTL_WRBUSY_Msk             (0x1ul << SYS_PLCTL_WRBUSY_Pos)                   /*!< SYS_T::PLCTL: WRBUSY Mask              */

#define SYS_PLCTL_LVSSTEP_Pos            (16)                                              /*!< SYS_T::PLCTL: LVSSTEP Position         */
#define SYS_PLCTL_LVSSTEP_Msk            (0x3ful << SYS_PLCTL_LVSSTP_Pos)                  /*!< SYS_T::PLCTL: LVSSTEP Mask             */

#define SYS_PLCTL_LVSPRD_Pos             (24)                                              /*!< SYS_T::PLCTL: LVSPRD Position          */
#define SYS_PLCTL_LVSPRD_Msk             (0xfful << SYS_PLCTL_LVSPRD_Pos)                  /*!< SYS_T::PLCTL: LVSPRD Mask              */

#define SYS_PLSTS_PLCBUSY_Pos            (0)                                               /*!< SYS_T::PLSTS: PLCBUSY Position         */
#define SYS_PLSTS_PLCBUSY_Msk            (0x1ul << SYS_PLSTS_PLCBUSY_Pos)                  /*!< SYS_T::PLSTS: PLCBUSY Mask             */

#define SYS_PLSTS_MVRCBUSY_Pos           (1)                                               /*!< SYS_T::PLSTS: MVRCBUSY Position        */
#define SYS_PLSTS_MVRCBUSY_Msk           (0x1ul << SYS_PLSTS_MVRCBUSY_Pos)                 /*!< SYS_T::PLSTS: MVRCBUSY Mask            */

#define SYS_PLSTS_MVRCERR_Pos            (2)                                               /*!< SYS_T::PLSTS: MVRCERR Position         */
#define SYS_PLSTS_MVRCERR_Msk            (0x1ul << SYS_PLSTS_MVRCERR_Pos)                  /*!< SYS_T::PLSTS: MVRCERR Mask             */

#define SYS_PLSTS_LCONS_Pos              (3)                                               /*!< SYS_T::PLSTS: LCONS Position           */
#define SYS_PLSTS_LCONS_Msk              (0x1ul << SYS_PLSTS_LCONS_Pos)                    /*!< SYS_T::PLSTS: LCONS Mask               */

#define SYS_PLSTS_PLSTATUS_Pos           (8)                                               /*!< SYS_T::PLSTS: PLSTATUS Position        */
#define SYS_PLSTS_PLSTATUS_Msk           (0x3ul << SYS_PLSTS_PLSTATUS_Pos)                 /*!< SYS_T::PLSTS: PLSTATUS Mask            */

#define SYS_PLSTS_CURMVR_Pos             (12)                                              /*!< SYS_T::PLSTS: CURMVR Position          */
#define SYS_PLSTS_CURMVR_Msk             (0x1ul << SYS_PLSTS_CURMVR_Pos)                   /*!< SYS_T::PLSTS: CURMVR Mask              */

#define SYS_AHBMCTL_INTACTEN_Pos         (0)                                               /*!< SYS_T::AHBMCTL: INTACTEN Position      */
#define SYS_AHBMCTL_INTACTEN_Msk         (0x1ul << SYS_AHBMCTL_INTACTEN_Pos)               /*!< SYS_T::AHBMCTL: INTACTEN Mask          */


/**@}*/ /* SYS_CONST */
typedef struct
{

    /**
     * @var SYS_INT_T::NMIEN
     * Offset: 0x00  NMI Source Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BODOUT    |BOD NMI Source Enable (Write Protect)
     * |        |          |0 = BOD NMI source Disabled.
     * |        |          |1 = BOD NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |IRCINT    |IRC TRIM NMI Source Enable (Write Protect)
     * |        |          |0 = IRC TRIM NMI source Disabled.
     * |        |          |1 = IRC TRIM NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |PWRWUINT  |Power-down Mode Wake-up NMI Source Enable (Write Protect)
     * |        |          |0 = Power-down mode wake-up NMI source Disabled.
     * |        |          |1 = Power-down mode wake-up NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |SRAMPERR  |SRAM Parity Check Error NMI Source Enable (Write Protect)
     * |        |          |0 = SRAM parity check error NMI source Disabled.
     * |        |          |1 = SRAM parity check error NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |CLKFAIL   |Clock Fail Detected NMI Source Enable (Write Protect)
     * |        |          |0 = Clock fail detected interrupt NMI source Disabled.
     * |        |          |1 = Clock fail detected interrupt NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |RTCINT    |RTC NMI Source Enable (Write Protect)
     * |        |          |0 = RTC NMI source Disabled.
     * |        |          |1 = RTC NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |TAMPERINT |Tamper Interrupt NMI Source Enable (Write Protect)
     * |        |          |0 = Backup register tamper detected interrupt NMI source Disabled.
     * |        |          |1 = Backup register tamper detected interrupt NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[8]     |EINT0     |External Interrupt From PA.6, or PB.5 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PA.6, or PB.5 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PA.6, or PB.5 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[9]     |EINT1     |External Interrupt From PA.7 or PB.4 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PA.7 or PB.4 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PA.7 or P4.4 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[10]    |EINT2     |External Interrupt From PB.3 or PC.6 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PB.3 or PC.6 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PB.3 or PC.6 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[11]    |EINT3     |External Interrupt From PB.2 or PC.7 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PB.2 or PC.7pin NMI source Disabled.
     * |        |          |1 = External interrupt from PB.2 or PC.7 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12]    |EINT4     |External Interrupt From PA.8 or PB.6 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PA.8 or PB.6 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PA.8 or PB.6 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[13]    |EINT5     |External Interrupt From PB.7 or PD.12 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PB.7 or PD.12 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PB.7 or PD.12 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[14]    |UART0INT  |UART0 NMI Source Enable (Write Protect)
     * |        |          |0 = UART0 NMI source Disabled.
     * |        |          |1 = UART0 NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[15]    |UART1INT  |UART1 NMI Source Enable (Write Protect)
     * |        |          |0 = UART1 NMI source Disabled.
     * |        |          |1 = UART1 NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[16]    |EINT6     |External Interrupt From PB.8 or PD.11 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PB.8 or PD.11 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PB.8 or PD.11 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[17]    |EINT7     |External Interrupt From PB.9 or PD.10 Pin NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from PB.9 or PD.10 pin NMI source Disabled.
     * |        |          |1 = External interrupt from PB.9 or PD.10 pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_INT_T::NMISTS
     * Offset: 0x04  NMI source interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BODOUT    |BOD Interrupt Flag (Read Only)
     * |        |          |0 = BOD interrupt is de-asserted.
     * |        |          |1 = BOD interrupt is asserted.
     * |[1]     |IRCINT    |IRC TRIM Interrupt Flag (Read Only)
     * |        |          |0 = HIRC TRIM interrupt is de-asserted.
     * |        |          |1 = HIRC TRIM interrupt is asserted.
     * |[2]     |PWRWUINT  |Power-down Mode Wake-up Interrupt Flag (Read Only)
     * |        |          |0 = Power-down mode wake-up interrupt is de-asserted.
     * |        |          |1 = Power-down mode wake-up interrupt is asserted.
     * |[3]     |SRAMPERR  |SRAM Parity Check Error Interrupt Flag (Read Only)
     * |        |          |0 = SRAM parity check error interrupt is de-asserted.
     * |        |          |1 = SRAM parity check error interrupt is asserted.
     * |[4]     |CLKFAIL   |Clock Fail Detected Interrupt Flag (Read Only)
     * |        |          |0 = Clock fail detected interrupt is de-asserted.
     * |        |          |1 = Clock fail detected interrupt is asserted.
     * |[6]     |RTCINT    |RTC Interrupt Flag (Read Only)
     * |        |          |0 = RTC interrupt is de-asserted.
     * |        |          |1 = RTC interrupt is asserted.
     * |[7]     |TAMPERINT |Tamper Interrupt Flag (Read Only)
     * |        |          |0 = Backup register tamper detected interrupt is de-asserted.
     * |        |          |1 = Backup register tamper detected interrupt is asserted.
     * |[8]     |EINT0     |External Interrupt From PA.6, or PB.5 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PA.6, or PB.5 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PA.6, or PB.5 interrupt is asserted.
     * |[9]     |EINT1     |External Interrupt From PA.7, or PB.4 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PA.7, or PB.4 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PA.7, or PB.4 interrupt is asserted.
     * |[10]    |EINT2     |External Interrupt From PB.3 or PC.6 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PB.3 or PC.6 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PB.3 or PC.6 interrupt is asserted.
     * |[11]    |EINT3     |External Interrupt From PB.2 or PC.7 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PB.2 or PC.7 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PB.2 or PC.7 interrupt is asserted.
     * |[12]    |EINT4     |External Interrupt From PA.8 or PB.6 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PA.8 or PB.6 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PA.8 or PB.6 interrupt is asserted.
     * |[13]    |EINT5     |External Interrupt From PB.7 or PD.12 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PB.7 or PD.12 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PB.7 or PD.12 interrupt is asserted.
     * |[14]    |UART0INT  |UART0 Interrupt Flag (Read Only)
     * |        |          |0 = UART1 interrupt is de-asserted.
     * |        |          |1 = UART1 interrupt is asserted.
     * |[15]    |UART1INT  |UART1 Interrupt Flag (Read Only)
     * |        |          |0 = UART1 interrupt is de-asserted.
     * |        |          |1 = UART1 interrupt is asserted.
     * |[16]    |EINT6     |External Interrupt From PB.8 or PD.11 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PB.8 or PD.11 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PB.8 or PD.11 interrupt is asserted.
     * |[17]    |EINT7     |External Interrupt From PB.9 or PD.10 Pin Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from PB.9 or PD.10 interrupt is deasserted.
     * |        |          |1 = External Interrupt from PB.9 or PD.10 interrupt is asserted.
     */

    __IO  uint32_t NMIEN;          /* Offset: 0x00  NMI Source Interrupt Enable Register                               */
    __I   uint32_t NMISTS;         /* Offset: 0x04  NMI source interrupt Status Register                               */

} SYS_INT_T;
/**
    @addtogroup INT_CONST INT Bit Field Definition
    Constant Definitions for INT Controller
  @{
*/

#define SYS_NMIEN_BODOUT_Pos             (0)                                               /*!< SYS_INT_T::NMIEN: BODOUT Position         */
#define SYS_NMIEN_BODOUT_Msk             (0x1ul << SYS_NMIEN_BODOUT_Pos )                  /*!< SYS_INT_T::NMIEN: BODOUT Mask             */

#define SYS_NMIEN_IRCINT_Pos             (1)                                               /*!< SYS_INT_T::NMIEN: IRCINT Position         */
#define SYS_NMIEN_IRCINT_Msk             (0x1ul << SYS_NMIEN_IRCINT_Pos )                  /*!< SYS_INT_T::NMIEN: IRCINT Mask             */

#define SYS_NMIEN_PWRWUINT_Pos           (2)                                               /*!< SYS_INT_T::NMIEN: PWRWUINT Position       */
#define SYS_NMIEN_PWRWUINT_Msk           (0x1ul << SYS_NMIEN_PWRWUINT_Pos )                /*!< SYS_INT_T::NMIEN: PWRWUINT Mask           */

#define SYS_NMIEN_SRAMPERR_Pos           (3)                                               /*!< SYS_INT_T::NMIEN: SRAMPERR Position       */
#define SYS_NMIEN_SRAMPERR_Msk           (0x1ul << SYS_NMIEN_SRAMPERR_Pos )                /*!< SYS_INT_T::NMIEN: SRAMPERR Mask           */

#define SYS_NMIEN_CLKFAIL_Pos            (4)                                               /*!< SYS_INT_T::NMIEN: CLKFAIL Position        */
#define SYS_NMIEN_CLKFAIL_Msk            (0x1ul << SYS_NMIEN_CLKFAIL_Pos )                 /*!< SYS_INT_T::NMIEN: CLKFAIL Mask            */

#define SYS_NMIEN_RTCINT_Pos             (6)                                               /*!< SYS_INT_T::NMIEN: RTCINT Position         */
#define SYS_NMIEN_RTCINT_Msk             (0x1ul << SYS_NMIEN_RTCINT_Pos )                  /*!< SYS_INT_T::NMIEN: RTCINT Mask             */

#define SYS_NMIEN_TAMPERINT_Pos          (7)                                               /*!< SYS_INT_T::NMIEN: TAMPERINT Position      */
#define SYS_NMIEN_TAMPERINT_Msk          (0x1ul << SYS_NMIEN_TAMPERINT_Pos )               /*!< SYS_INT_T::NMIEN: TAMPERINT Mask          */

#define SYS_NMIEN_EINT0_Pos              (8)                                               /*!< SYS_INT_T::NMIEN: EINT0 Position          */
#define SYS_NMIEN_EINT0_Msk              (0x1ul << SYS_NMIEN_EINT0_Pos )                   /*!< SYS_INT_T::NMIEN: EINT0 Mask              */

#define SYS_NMIEN_EINT1_Pos              (9)                                               /*!< SYS_INT_T::NMIEN: EINT1 Position          */
#define SYS_NMIEN_EINT1_Msk              (0x1ul << SYS_NMIEN_EINT1_Pos )                   /*!< SYS_INT_T::NMIEN: EINT1 Mask              */

#define SYS_NMIEN_EINT2_Pos              (10)                                              /*!< SYS_INT_T::NMIEN: EINT2 Position          */
#define SYS_NMIEN_EINT2_Msk              (0x1ul << SYS_NMIEN_EINT2_Pos )                   /*!< SYS_INT_T::NMIEN: EINT2 Mask              */

#define SYS_NMIEN_EINT3_Pos              (11)                                              /*!< SYS_INT_T::NMIEN: EINT3 Position          */
#define SYS_NMIEN_EINT3_Msk              (0x1ul << SYS_NMIEN_EINT3_Pos )                   /*!< SYS_INT_T::NMIEN: EINT3 Mask              */

#define SYS_NMIEN_EINT4_Pos              (12)                                              /*!< SYS_INT_T::NMIEN: EINT4 Position          */
#define SYS_NMIEN_EINT4_Msk              (0x1ul << SYS_NMIEN_EINT4_Pos )                   /*!< SYS_INT_T::NMIEN: EINT4 Mask              */

#define SYS_NMIEN_EINT5_Pos              (13)                                              /*!< SYS_INT_T::NMIEN: EINT5 Position          */
#define SYS_NMIEN_EINT5_Msk              (0x1ul << SYS_NMIEN_EINT5_Pos )                   /*!< SYS_INT_T::NMIEN: EINT5 Mask              */

#define SYS_NMIEN_UART0INT_Pos           (14)                                              /*!< SYS_INT_T::NMIEN: UART0INT Position       */
#define SYS_NMIEN_UART0INT_Msk           (0x1ul << SYS_NMIEN_UART0INT_Pos )                /*!< SYS_INT_T::NMIEN: UART0INT Mask           */

#define SYS_NMIEN_UART1INT_Pos           (15)                                              /*!< SYS_INT_T::NMIEN: UART1INT Position       */
#define SYS_NMIEN_UART1INT_Msk           (0x1ul << SYS_NMIEN_UART1INT_Pos )                /*!< SYS_INT_T::NMIEN: UART1INT Mask           */

#define SYS_NMIEN_EINT6_Pos              (16)                                              /*!< SYS_INT_T::NMIEN: EINT6 Position          */
#define SYS_NMIEN_EINT6_Msk              (0x1ul << SYS_NMIEN_EINT6_Pos )                   /*!< SYS_INT_T::NMIEN: EINT6 Mask              */

#define SYS_NMIEN_EINT7_Pos              (17)                                              /*!< SYS_INT_T::NMIEN: EINT7 Position          */
#define SYS_NMIEN_EINT7_Msk              (0x1ul << SYS_NMIEN_EINT7_Pos )                   /*!< SYS_INT_T::NMIEN: EINT7 Mask              */

#define SYS_NMISTS_BODOUT_Pos            (0)                                               /*!< SYS_INT_T::NMISTS: BODOUT Position        */
#define SYS_NMISTS_BODOUT_Msk            (0x1ul << SYS_NMISTS_BODOUT_Pos )                 /*!< SYS_INT_T::NMISTS: BODOUT Mask            */

#define SYS_NMISTS_IRCINT_Pos            (1)                                               /*!< SYS_INT_T::NMISTS: IRCINT Position        */
#define SYS_NMISTS_IRCINT_Msk            (0x1ul << SYS_NMISTS_IRCINT_Pos )                 /*!< SYS_INT_T::NMISTS: IRCINT Mask            */

#define SYS_NMISTS_PWRWUINT_Pos          (2)                                               /*!< SYS_INT_T::NMISTS: PWRWUINT Position      */
#define SYS_NMISTS_PWRWUINT_Msk          (0x1ul << SYS_NMISTS_PWRWUINT_Pos )               /*!< SYS_INT_T::NMISTS: PWRWUINT Mask          */

#define SYS_NMISTS_SRAMPERR_Pos          (3)                                               /*!< SYS_INT_T::NMISTS: SRAMPERR Position      */
#define SYS_NMISTS_SRAMPERR_Msk          (0x1ul << SYS_NMISTS_SRAMPERR_Pos )               /*!< SYS_INT_T::NMISTS: SRAMPERR Mask          */

#define SYS_NMISTS_CLKFAIL_Pos           (4)                                               /*!< SYS_INT_T::NMISTS: CLKFAIL Position       */
#define SYS_NMISTS_CLKFAIL_Msk           (0x1ul << SYS_NMISTS_CLKFAIL_Pos )                /*!< SYS_INT_T::NMISTS: CLKFAIL Mask           */

#define SYS_NMISTS_RTCINT_Pos            (6)                                               /*!< SYS_INT_T::NMISTS: RTCINT Position        */
#define SYS_NMISTS_RTCINT_Msk            (0x1ul << SYS_NMISTS_RTCINT_Pos )                 /*!< SYS_INT_T::NMISTS: RTCINT Mask            */

#define SYS_NMISTS_TAMPERINT_Pos         (7)                                               /*!< SYS_INT_T::NMISTS: TAMPERINT Position     */
#define SYS_NMISTS_TAMPERINT_Msk         (0x1ul << SYS_NMISTS_TAMPERINT_Pos )              /*!< SYS_INT_T::NMISTS: TAMPERINT Mask         */

#define SYS_NMISTS_EINT0_Pos             (8)                                               /*!< SYS_INT_T::NMISTS: EINT0 Position         */
#define SYS_NMISTS_EINT0_Msk             (0x1ul << SYS_NMISTS_EINT0_Pos )                  /*!< SYS_INT_T::NMISTS: EINT0 Mask             */

#define SYS_NMISTS_EINT1_Pos             (9)                                               /*!< SYS_INT_T::NMISTS: EINT1 Position         */
#define SYS_NMISTS_EINT1_Msk             (0x1ul << SYS_NMISTS_EINT1_Pos )                  /*!< SYS_INT_T::NMISTS: EINT1 Mask             */

#define SYS_NMISTS_EINT2_Pos             (10)                                              /*!< SYS_INT_T::NMISTS: EINT2 Position         */
#define SYS_NMISTS_EINT2_Msk             (0x1ul << SYS_NMISTS_EINT2_Pos )                  /*!< SYS_INT_T::NMISTS: EINT2 Mask             */

#define SYS_NMISTS_EINT3_Pos             (11)                                              /*!< SYS_INT_T::NMISTS: EINT3 Position         */
#define SYS_NMISTS_EINT3_Msk             (0x1ul << SYS_NMISTS_EINT3_Pos )                  /*!< SYS_INT_T::NMISTS: EINT3 Mask             */

#define SYS_NMISTS_EINT4_Pos             (12)                                              /*!< SYS_INT_T::NMISTS: EINT4 Position         */
#define SYS_NMISTS_EINT4_Msk             (0x1ul << SYS_NMISTS_EINT4_Pos )                  /*!< SYS_INT_T::NMISTS: EINT4 Mask             */

#define SYS_NMISTS_EINT5_Pos             (13)                                              /*!< SYS_INT_T::NMISTS: EINT5 Position         */
#define SYS_NMISTS_EINT5_Msk             (0x1ul << SYS_NMISTS_EINT5_Pos )                  /*!< SYS_INT_T::NMISTS: EINT5 Mask             */

#define SYS_NMISTS_UART0INT_Pos          (14)                                              /*!< SYS_INT_T::NMISTS: UART0_INT Position     */
#define SYS_NMISTS_UART0INT_Msk          (0x1ul << SYS_NMISTS_UART0INT_Pos )               /*!< SYS_INT_T::NMISTS: UART0_INT Mask         */

#define SYS_NMISTS_UART1INT_Pos          (15)                                              /*!< SYS_INT_T::NMISTS: UART1_INT Position     */
#define SYS_NMISTS_UART1INT_Msk          (0x1ul << SYS_NMISTS_UART1INT_Pos )               /*!< SYS_INT_T::NMISTS: UART1_INT Mask         */

#define SYS_NMISTS_EINT6_Pos             (16)                                              /*!< SYS_INT_T::NMISTS: EINT6 Position         */
#define SYS_NMISTS_EINT6_Msk             (0x1ul << SYS_NMISTS_EINT6_Pos )                  /*!< SYS_INT_T::NMISTS: EINT6 Mask             */

#define SYS_NMISTS_EINT7_Pos             (17)                                              /*!< SYS_INT_T::NMISTS: EINT7 Position         */
#define SYS_NMISTS_EINT7_Msk             (0x1ul << SYS_NMISTS_EINT7_Pos )                  /*!< SYS_INT_T::NMISTS: EINT7 Mask             */


/**@}*/ /* INT_CONST */
/**@}*/ /* end of SYS register group */
/**@}*/ /* end of REGISTER group */


#endif /* __SYS_REG_H__ */
