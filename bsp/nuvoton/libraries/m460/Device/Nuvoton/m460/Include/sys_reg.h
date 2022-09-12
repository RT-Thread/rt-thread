/**************************************************************************//**
 * @file     sys_reg.h
 * @version  V3.00
 * @brief    SYS register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SYS_REG_H__
#define __SYS_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/


/*---------------------- System Manger Controller -------------------------*/
/**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
@{ */

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
     * |        |          |Note 2: Watchdog Timer register RSTF(WDT_CTL[2]) bit is set if the system has been reset by WDT time-out reset
     * |        |          |Window Watchdog Timer register WWDTRF(WWDT_STATUS[1]) bit is set if the system has been reset by WWDT time-out reset.
     * |[3]     |LVRF      |LVR Reset Flag
     * |        |          |The LVR reset flag is set by the "Reset Signal" from the Low Voltage Reset Controller to indicate the previous reset source.
     * |        |          |0 = No reset from LVR.
     * |        |          |1 = LVR controller had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |BODRF     |BOD Reset Flag
     * |        |          |The BOD reset flag is set by the "Reset Signal" from the Brown-Out Detector to indicate the previous reset source.
     * |        |          |0 = No reset from BOD.
     * |        |          |1 = The BOD had issued the reset signal to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |MCURF     |MCU Reset Flag
     * |        |          |The system reset flag is set by the "Reset Signal" from the Cortex-M4 Core to indicate the previous reset source.
     * |        |          |0 = No reset from Cortex-M4.
     * |        |          |1 = The Cortex-M4 had issued the reset signal to reset the system by writing 1 to the bit SYSRESETREQ(AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M4 core.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[6]     |HRESETRF  |HRESET Reset Flag
     * |        |          |The HRESET reset flag is set by the "Reset Signal" from the HRESET.
     * |        |          |0 = No reset from HRESET.
     * |        |          |1 = Reset from HRESET.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: HRESET includes: POR, Reset Pin, LVR, BOD, WDT, WWDT, CPU lock up, CHIP and MCU reset.
     * |[7]     |CPURF     |CPU Reset Flag
     * |        |          |The CPU reset flag is set by hardware if software writes CPURST (SYS_IPRST0[1]) 1 to reset Cortex-M4 Core and Flash Memory Controller (FMC).
     * |        |          |0 = No reset from CPU.
     * |        |          |1 = The Cortex-M4 Core and FMC are reset by software setting CPURST to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[8]     |CPULKRF   |CPU Lockup Reset Flag
     * |        |          |0 = No reset from CPU lockup happened.
     * |        |          |1 = The Cortex-M4 lockup happened and chip is reset.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: When CPU lockup happened under ICE is connected, this flag will set to 1 but chip will not reset.
     * @var SYS_T::IPRST0
     * Offset: 0x08  Peripheral Reset Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHIPRST   |Chip One-shot Reset (Write Protect)
     * |        |          |Setting this bit will reset the whole chip, including Processor core and all peripherals, and this bit will automatically return to 0 after the 2 clock cycles.
     * |        |          |The CHIPRST is same as the POR reset, all the chip controllers is reset and the chip setting from Flash are also reload.
     * |        |          |0 = Chip normal operation.
     * |        |          |1 = Chip one-shot reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |CPURST    |Processor Core One-shot Reset (Write Protect)
     * |        |          |Setting this bit will only reset the processor core and Flash Memory Controller(FMC), and this bit will automatically return to 0 after the 2 clock cycles.
     * |        |          |0 = Processor core normal operation.
     * |        |          |1 = Processor core one-shot reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |PDMA0RST  |PDMA0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the PDMA0 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = PDMA0 controller normal operation.
     * |        |          |1 = PDMA0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |EBIRST    |EBI Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the EBI controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = EBI controller normal operation.
     * |        |          |1 = EBI controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |EMAC0RST  |EMAC0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the EMAC0 controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = EMAC0 controller normal operation.
     * |        |          |1 = EMAC0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |SDH0RST   |SDH0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the SDH0 controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = SDH0 controller normal operation.
     * |        |          |1 = SDH0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |CRCRST    |CRC Calculation Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the CRC calculation controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = CRC calculation controller normal operation.
     * |        |          |1 = CRC calculation controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[8]     |CCAPRST   |CCAP Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the CCAP controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = CCAP controller normal operation.
     * |        |          |1 = CCAP controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[10]    |HSUSBDRST |HSUSBD Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the HSUSBD controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = HSUSBD controller normal operation.
     * |        |          |1 = HSUSBD controller reset.
     * |[11]    |HBIRST    |HBI Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the HBI controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = HBI controller normal operation.
     * |        |          |1 = HBI controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12]    |CRPTRST   |CRYPTO Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CRYPTO controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = CRYPTO controller normal operation.
     * |        |          |1 = CRYPTO controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[13]    |KSRST     |Key Store Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the Key Store controller
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = Key Store controller normal operation.
     * |        |          |1 = Key Store controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[14]    |SPIMRST   |SPIM Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the SPIM controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = SPIM controller normal operation.
     * |        |          |1 = SPIM controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[16]    |HSUSBHRST |HSUSBH Controller Reset (Write Protect)
     * |        |          |Set this bit to 1 will generate a reset signal to the HSUSBH controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = HSUSBH controller normal operation.
     * |        |          |1 = HSUSBH controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[17]    |SDH1RST   |SDH1 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the SDH1 controller.
     * |        |          |User needs to set this bit to 0 to release from the reset state.
     * |        |          |0 = SDH1 controller normal operation.
     * |        |          |1 = SDH1 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[18]    |PDMA1RST  |PDMA1 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the PDMA1 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = PDMA1 controller normal operation.
     * |        |          |1 = PDMA1 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[20]    |CANFD0RST |CANFD0 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CANFD0 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = CANFD0 controller normal operation.
     * |        |          |1 = CANFD0 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[21]    |CANFD1RST |CANFD1 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CANFD1 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = CANFD1 controller normal operation.
     * |        |          |1 = CANFD1 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[22]    |CANFD2RST |CANFD2 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CANFD2 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = CANFD2 controller normal operation.
     * |        |          |1 = CANFD2 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[23]    |CANFD3RST |CANFD3 Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the CANFD3 controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = CANFD3 controller normal operation.
     * |        |          |1 = CANFD3 controller reset.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[28]    |BMCRST    |BMC Controller Reset (Write Protect)
     * |        |          |Setting this bit to 1 will generate a reset signal to the BMC controller.
     * |        |          |User needs to set this bit to 0 to release from reset state.
     * |        |          |0 = BCM controller normal operation.
     * |        |          |1 = BMC controller reset.
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
     * |[11]    |I2C3RST   |I2C3 Controller Reset
     * |        |          |0 = I2C3 controller normal operation.
     * |        |          |1 = I2C3 controller reset.
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
     * |[22]    |UART6RST  |UART6 Controller Reset
     * |        |          |0 = UART6 controller normal operation.
     * |        |          |1 = UART6 controller reset.
     * |[23]    |UART7RST  |UART7 Controller Reset
     * |        |          |0 = UART7 controller normal operation.
     * |        |          |1 = UART7 controller reset.
     * |[26]    |OTGRST    |OTG Controller Reset
     * |        |          |0 = OTG controller normal operation.
     * |        |          |1 = OTG controller reset.
     * |[27]    |USBDRST   |USBD Controller Reset
     * |        |          |0 = USBD controller normal operation.
     * |        |          |1 = USBD controller reset.
     * |[28]    |EADC0RST  |EADC0 Controller Reset
     * |        |          |0 = EADC0 controller normal operation.
     * |        |          |1 = EADC0 controller reset.
     * |[29]    |I2S0RST   |I2S0 Controller Reset
     * |        |          |0 = I2S0 controller normal operation.
     * |        |          |1 = I2S0 controller reset.
     * |[30]    |HSOTGRST  |HSOTG Controller Reset
     * |        |          |0 = HSOTG controller normal operation.
     * |        |          |1 = HSOTG controller reset.
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
     * |[3]     |I2C4RST   |I2C4 Controller Reset
     * |        |          |0 = I2C4 controller normal operation.
     * |        |          |1 = I2C4 controller reset.
     * |[4]     |QSPI1RST  |QSPI1 Controller Reset
     * |        |          |0 = QSPI1 controller normal operation.
     * |        |          |1 = QSPI1 controller reset.
     * |[6]     |SPI3RST   |SPI3 Controller Reset
     * |        |          |0 = SPI3 controller normal operation.
     * |        |          |1 = SPI3 controller reset.
     * |[7]     |SPI4RST   |SPI4 Controller Reset
     * |        |          |0 = SPI4 controller normal operation.
     * |        |          |1 = SPI4 controller reset.
     * |[8]     |USCI0RST  |USCI0 Controller Reset
     * |        |          |0 = USCI0 controller normal operation.
     * |        |          |1 = USCI0 controller reset.
     * |[10]    |PSIORST   |PSIO Controller Reset
     * |        |          |0 = PSIO controller normal operation.
     * |        |          |1 = PSIO controller reset.
     * |[12]    |DACRST    |DAC Controller Reset
     * |        |          |0 = DAC controller normal operation.
     * |        |          |1 = DAC controller reset.
     * |[13]    |ECAP2RST  |ECAP2 Controller Reset
     * |        |          |0 = ECAP2 controller normal operation.
     * |        |          |1 = ECAP2 controller reset.
     * |[14]    |ECAP3RST  |ECAP3 Controller Reset
     * |        |          |0 = ECAP3 controller normal operation.
     * |        |          |1 = ECAP3 controller reset.
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
     * |[20]    |EQEI2RST  |EQEI2 Controller Reset
     * |        |          |0 = EQEI2 controller normal operation.
     * |        |          |1 = EQEI2 controller reset.
     * |[21]    |EQEI3RST  |EQEI3 Controller Reset
     * |        |          |0 = EQEI3 controller normal operation.
     * |        |          |1 = EQEI3 controller reset.
     * |[22]    |EQEI0RST  |EQEI0 Controller Reset
     * |        |          |0 = EQEI0 controller normal operation.
     * |        |          |1 = EQEI0 controller reset.
     * |[23]    |EQEI1RST  |EQEI1 Controller Reset
     * |        |          |0 = EQEI1 controller normal operation.
     * |        |          |1 = EQEI1 controller reset.
     * |[26]    |ECAP0RST  |ECAP0 Controller Reset
     * |        |          |0 = ECAP0 controller normal operation.
     * |        |          |1 = ECAP0 controller reset.
     * |[27]    |ECAP1RST  |ECAP1 Controller Reset
     * |        |          |0 = ECAP1 controller normal operation.
     * |        |          |1 = ECAP1 controller reset.
     * |[29]    |I2S1RST   |I2S1 Controller Reset
     * |        |          |0 = I2S1 controller normal operation.
     * |        |          |1 = I2S1 controller reset.
     * |[31]    |EADC1RST  |EADC1 Controller Reset
     * |        |          |0 = EADC1 controller normal operation.
     * |        |          |1 = EADC1 controller reset.
     * @var SYS_T::BODCTL
     * Offset: 0x18  Brown-out Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BODEN     |Brown-out Detector Enable Bit (Write Protect)
     * |        |          |The default value is set by Flash controller user configuration register CBODEN (CONFIG0 [19]).
     * |        |          |0 = Brown-out Detector function Disabled.
     * |        |          |1 = Brown-out Detector function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |BODRSTEN  |Brown-out Reset Enable Bit (Write Protect)
     * |        |          |The default value is set by Flash controller user configuration register CBORST(CONFIG0[20]) bit.
     * |        |          |0 = Brown-out "INTERRUPT" function Enabled.
     * |        |          |1 = Brown-out "RESET" function Enabled.
     * |        |          |Note 1: While the Brown-out Detector function is enabled (BODEN high) and BOD reset function is enabled (BODRSTEN high), BOD will assert a signal to reset chip when the detected voltage is lower than the threshold (BODOUT high).
     * |        |          |While the BOD function is enabled (BODEN high) and BOD interrupt function is enabled (BODRSTEN low), BOD will assert an interrupt if BODOUT is high
     * |        |          |BOD interrupt will keep till to the BODEN set to 0.
     * |        |          |BOD interrupt can be blocked by disabling the NVIC BOD interrupt or disabling BOD function (set BODEN low).
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |BODIF     |Brown-out Detector Interrupt Flag
     * |        |          |0 = Brown-out Detector does not detect any voltage draft at VDD down through or up through the voltage of BODVL setting.
     * |        |          |1 = When Brown-out Detector detects the VDD is dropped down through the voltage of BODVL setting or the VDD is raised up through the voltage of BODVL setting, this bit is set to 1 and the brown-out interrupt is requested if brown-out interrupt is enabled.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |BODLPM    |Brown-out Detector Low Power Mode (Write Protect)
     * |        |          |0 = BOD operate in normal mode (default).
     * |        |          |1 = BOD Low Power mode Enabled.
     * |        |          |Note 1: The BOD consumes about 100uA in normal mode, the low power mode can reduce the current to about 1/10 but slow the BOD response.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |BODOUT    |Brown-out Detector Output Status
     * |        |          |0 = Brown-out Detector output status is 0.
     * |        |          |It means the detected voltage is higher than BODVL setting or BODEN is 0.
     * |        |          |1 = Brown-out Detector output status is 1.
     * |        |          |It means the detected voltage is lower than BODVL setting
     * |        |          |If the BODEN is 0, BOD function disabled, this bit always responds 0.
     * |[7]     |LVREN     |Low Voltage Reset Enable Bit (Write Protect)
     * |        |          |The LVR function resets the chip when the input power voltage is lower than LVR circuit setting
     * |        |          |LVR function is enabled by default.
     * |        |          |0 = Low Voltage Reset function Disabled.
     * |        |          |1 = Low Voltage Reset function Enabled.
     * |        |          |Note 1: After enabling the bit, the LVR function will be active with 100us delay for LVR output stable (default).
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
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
     * |[15]    |LVRRDY    |Low Voltage Reset Ready Flag (Read Only)
     * |        |          |When the LVR function first enable, need more HCLK to wait LVR ready.
     * |        |          |0 = Low Voltage Reset function not ready.
     * |        |          |1 = Low Voltage Reset function ready.
     * |[18:16] |BODVL     |Brown-out Detector Threshold Voltage Selection (Write Protect)
     * |        |          |The default value is set by Flash controller user configuration register CBOV (CONFIG0 [23:21]).
     * |        |          |000 = Brown-Out Detector threshold voltage is 1.6V.
     * |        |          |001 = Brown-Out Detector threshold voltage is 1.8V.
     * |        |          |010 = Brown-Out Detector threshold voltage is 2.0V.
     * |        |          |011 = Brown-Out Detector threshold voltage is 2.2V.
     * |        |          |100 = Brown-Out Detector threshold voltage is 2.4V.
     * |        |          |101 = Brown-Out Detector threshold voltage is 2.6V.
     * |        |          |110 = Brown-Out Detector threshold voltage is 2.8V.
     * |        |          |111 = Brown-Out Detector threshold voltage is 3.0V.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::IVSCTL
     * Offset: 0x1C  Internal Voltage Source Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |VTEMPEN   |Temperature Sensor Enable Bit
     * |        |          |This bit is used to enable/disable temperature sensor function.
     * |        |          |0 = Temperature sensor function Disabled (default).
     * |        |          |1 = Temperature sensor function Enabled.
     * |[1]     |VBATUGEN  |VBAT Unity Gain Buffer Enable Bit
     * |        |          |This bit is used to enable/disable VBAT unity gain buffer function.
     * |        |          |0 = VBAT unity gain buffer function Disabled (default).
     * |        |          |1 = VBAT unity gain buffer function Enabled.
     * |        |          |Note: After this bit is set to 1, the value of VBAT unity gain buffer output voltage can be obtained from ADC conversion result
     * @var SYS_T::IPRST3
     * Offset: 0x20  Peripheral Reset Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |KPIRST    |KPI Controller Reset
     * |        |          |0 = KPI controller normal operation.
     * |        |          |1 = KPI controller reset.
     * |[6]     |EADC2RST  |EADC2 Controller Reset
     * |        |          |0 = EADC2 controller normal operation.
     * |        |          |1 = EADC2 controller reset.
     * |[7]     |ACMP23RST |Analog Comparator 2/3 Controller Reset
     * |        |          |0 = Analog Comparator 2/3 controller normal operation.
     * |        |          |1 = Analog Comparator 2/3 controller reset.
     * |[8]     |SPI5RST   |SPI5 Controller Reset
     * |        |          |0 = SPI5 controller normal operation.
     * |        |          |1 = SPI5 controller reset.
     * |[9]     |SPI6RST   |SPI6 Controller Reset
     * |        |          |0 = SPI6 controller normal operation.
     * |        |          |1 = SPI6 controller reset.
     * |[10]    |SPI7RST   |SPI7 Controller Reset
     * |        |          |0 = SPI7 controller normal operation.
     * |        |          |1 = SPI7 controller reset.
     * |[11]    |SPI8RST   |SPI8 Controller Reset
     * |        |          |0 = SPI8 controller normal operation.
     * |        |          |1 = SPI8 controller reset.
     * |[12]    |SPI9RST   |SPI9 Controller Reset
     * |        |          |0 = SPI9 controller normal operation.
     * |        |          |1 = SPI9 controller reset.
     * |[13]    |SPI10RST  |SPI10 Controller Reset
     * |        |          |0 = SPI10 controller normal operation.
     * |        |          |1 = SPI10 controller reset.
     * |[16]    |UART8RST  |UART8 Controller Reset
     * |        |          |0 = UART8 controller normal operation.
     * |        |          |1 = UART8 controller reset.
     * |[17]    |UART9RST  |UART9 Controller Reset
     * |        |          |0 = UART9 controller normal operation.
     * |        |          |1 = UART9 controller reset.
     * @var SYS_T::PORCTL
     * Offset: 0x24  Power-On-reset Controller Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |POROFF    |Power-on Reset Enable Bit (Write Protect)
     * |        |          |When powered on, the POR circuit generates a reset signal to reset the whole chip function, but noise on the power may cause the POR active again.
     * |        |          |User can disable internal POR circuit to avoid unpredictable noise to cause chip reset by writing 0x5AA5 to this field.
     * |        |          |The POR function will be active again when this field is set to another value or chip is reset by other reset source, including:
     * |        |          |nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
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
     * |[7:6]   |PRELOADSEL|Pre-load Timing Selection (Write Protect)
     * |        |          |00 = pre-load time is 60us for 0.1uF Capacitor.
     * |        |          |01 = pre-load time is 310us for 1uF Capacitor.
     * |        |          |10 = pre-load time is 1270us for 4.7uF Capacitor.
     * |        |          |11 = pre-load time is 2650us for 10uF Capacitor.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[24]    |VBGFEN    |Chip Internal Voltage Bandgap Force Enable Bit (Write Protect)
     * |        |          |0 = Chip internal voltage bandgap controlled by ADC/ACMP if source selected.
     * |        |          |1 = Chip internal voltage bandgap force enable.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[26:25] |VBGISEL   |Chip Internal Voltage Bandgap Current Selection Bits (Write Protect)
     * |        |          |00 = Bandgap voltage buffer current is 4.2uA.
     * |        |          |01 = Bandgap voltage buffer current is 7.3uA.
     * |        |          |10 = Bandgap voltage buffer current is 10.4uA.
     * |        |          |11 = Bandgap voltage buffer current is 13.5uA.
     * |        |          |Note 1: When ADC conversion source select bandgap voltage, suggest set VBGISEL as 10.
     * |        |          |Note 2: These bits are write protected. Refer to the SYS_REGLCTL register.
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
     * |        |          |11 = On-The-Go device mode.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |SBO       |Note: This bit must always be kept 1. If set to 0, the result is unpredictable.
     * |[8]     |USBEN     |USB PHY Enable
     * |        |          |This bit is used to enable/disable USB PHY.
     * |        |          |0 = USB PHY Disabled.
     * |        |          |1 = USB PHY Enabled.
     * |[17:16] |HSUSBROLE |HSUSB Role Option (Write Protect)
     * |        |          |These two bits are used to select the role of HSUSB.
     * |        |          |00 = Standard HSUSB Device mode.
     * |        |          |01 = Standard HSUSB Host mode.
     * |        |          |10 = ID dependent mode.
     * |        |          |11 = On-The-Go device mode.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[24]    |HSUSBEN   |HSUSB PHY Enable
     * |        |          |This bit is used to enable/disable HSUSB PHY.
     * |        |          |0 = HSUSB PHY Disabled.
     * |        |          |1 = HSUSB PHY Enabled.
     * |[25]    |HSUSBACT  |HSUSB PHY Active Control
     * |        |          |This bit is used to control HSUSB PHY at reset state or active state.
     * |        |          |0 = HSUSB PHY at reset state.
     * |        |          |1 = HSUSB PHY at active state.
     * |        |          |Note: After setting HSUSBEN (SYS_USBPHY[24]) to enable HSUSB PHY, user should keep HSUSB PHY at reset mode at lease 10us before changing to active mode.
     * @var SYS_T::GPA_MFOS
     * Offset: 0x80-0xA4  GPIOA-GPIOJ Multiple Function Output Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |MFOSn     |GPIOA-J Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.n pin.
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G/H.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F.
     * |        |          |n=6~15 for port I.
     * |        |          |Max. n=13 for port J.
     * @var SYS_T::SRAM_INTCTL
     * Offset: 0xC0  System SRAM Interrupt Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PERRIEN   |SRAM Parity Check Error Interrupt Enable Bit
     * |        |          |0 = SRAM parity check error interrupt Disabled.
     * |        |          |1 = SRAM parity check error interrupt Enabled.
     * @var SYS_T::SRAM_STATUS
     * Offset: 0xC4  System SRAM Parity Error Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PERRIF    |SRAM Parity Check Error Flag
     * |        |          |This bit indicates the System SRAM parity error occurred. Write 1 to clear this to 0.
     * |        |          |0 = No System SRAM parity error.
     * |        |          |1 = System SRAM parity error occur.
     * @var SYS_T::SRAM_ERRADDR
     * Offset: 0xC8  System SRAM Parity Check Error Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ERRADDR   |System SRAM Parity Error Address (Read Only)
     * |        |          |This register shows system SRAM parity error byte address.
     * @var SYS_T::SRAM_BISTCTL
     * Offset: 0xD0  System SRAM BIST Test Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SRBIST0   |System SRAM Bank0 BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for system SRAM bank0.
     * |        |          |0 = System SRAM bank0 BIST Disabled.
     * |        |          |1 = System SRAM bank0 BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |SRBIST1   |System SRAM Bank1 BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for system SRAM bank1.
     * |        |          |0 = System SRAM bank1 BIST Disabled.
     * |        |          |1 = System SRAM bank1 BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |CRBIST    |CACHE SRAM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for CACHE SRAM.
     * |        |          |0 = CACHE SRAM BIST Disabled.
     * |        |          |1 = CACHE SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |CANBIST   |CAN SRAM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for CAN SRAM.
     * |        |          |0 = CAN SRAM BIST Disabled.
     * |        |          |1 = CAN SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |USBBIST   |USB BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for USB SRAM.
     * |        |          |0 = USB SRAM BIST Disabled.
     * |        |          |1 = USB SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |SPIMBIST  |SPIM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for SPIM SRAM.
     * |        |          |0 = SPIM SRAM BIST Disabled.
     * |        |          |1 = SPIM SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |EMAC0BIST |EMAC0 BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for EMAC0 SRAM.
     * |        |          |0 = EMAC0 SRAM BIST Disabled.
     * |        |          |1 = EMAC0 SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[8]     |HSUSBDBIST|HSUSBD BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for HSUSBD SRAM.
     * |        |          |0 = HSUSBD SRAM BIST Disabled.
     * |        |          |1 = HSUSBD SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[9]     |HSUSBHBIST|HSUSBH BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for HSUSBH SRAM.
     * |        |          |0 = HSUSBH SRAM BIST Disabled.
     * |        |          |1 = HSUSBH SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[10]    |SRBIST2   |System SRAM Bank2 BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for system SRAM bank2.
     * |        |          |0 = System SRAM bank2 BIST Disabled.
     * |        |          |1 = System SRAM bank2 BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[11]    |KSBIST    |Key Store SRAM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for Key Store SRAM.
     * |        |          |0 = Key Store SRAM BIST Disabled.
     * |        |          |1 = Key Store SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12]    |CCAPBIST  |CCAP SRAM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for CCAP SRAM.
     * |        |          |0 = CCAP SRAM BIST Disabled.
     * |        |          |1 = CCAP SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[13]    |RSABIST   |RSA SRAM BIST Enable Bit (Write Protect)
     * |        |          |This bit enables BIST test for RSA SRAM.
     * |        |          |0 = RSA SRAM BIST Disabled.
     * |        |          |1 = RSA SRAM BIST Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::SRAM_BISTSTS
     * Offset: 0xD4  System SRAM BIST Test Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SRBISTEF0 |System SRAM Bank0 BIST Fail Flag (Read Only)
     * |        |          |0 = System SRAM bank0 BIST test pass.
     * |        |          |1 = System SRAM bank0 BIST test fail.
     * |[1]     |SRBISTEF1 |System System Bank1 SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = System SRAM bank1 BIST test pass.
     * |        |          |1 = System SRAM bank1 BIST test fail.
     * |[2]     |CRBISTEF  |CACHE SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = CACHE SRAM BIST test pass.
     * |        |          |1 = CACHE SRAM BIST test fail.
     * |[3]     |CANBEF    |CAN SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = CAN SRAM BIST test pass.
     * |        |          |1 = CAN SRAM BIST test fail.
     * |        |          |Note: Any of the CAN SRAM macros BIST fail, this flag is 1.
     * |[4]     |USBBEF    |USB SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = USB SRAM BIST test pass.
     * |        |          |1 = USB SRAM BIST test fail.
     * |[5]     |SPIMBEF   |SPIM SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = SPIM SRAM BIST test pass.
     * |        |          |1 = SPIM SRAM BIST test fail.
     * |[6]     |EMAC0BEF  |EMAC0 SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = EMAC0 SRAM BIST test pass.
     * |        |          |1 = EMAC0 SRAM BIST test fail.
     * |[8]     |HSUSBDBEF |HSUSBD SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = HSUSBD SRAM BIST test pass.
     * |        |          |1 = HSUSBD SRAM BIST test fail.
     * |[9]     |HSUSBHBEF |HSUSBH BIST Fail Flag (Read Only)
     * |        |          |0 = HSUSBH SRAM BIST test pass.
     * |        |          |1 = HSUSBH SRAM BIST test fail.
     * |[10]    |SRBISTEF2 |System SRAM Bank2 BIST Fail Flag (Read Only)
     * |        |          |0 = System SRAM bank2 BIST test pass.
     * |        |          |1 = System SRAM bank2 BIST test fail.
     * |[11]    |KSBISTEF  |Key Store SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = Key Store SRAM BIST test pass.
     * |        |          |1 = Key Store SRAM BIST test fail.
     * |[12]    |CCAPBISTEF|CCAP BIST Fail Flag (Read Only)
     * |        |          |0 = CCAP BIST test pass.
     * |        |          |1 = CCAP BIST test fail.
     * |[13]    |RSABISTE  |RSA SRAM BIST Fail Flag (Read Only)
     * |        |          |0 = RSA SRAM BIST test pass.
     * |        |          |1 = RSA SRAM BIST test fail.
     * |[16]    |SRBEND0   |System SRAM Bank0 BIST Test Finish (Read Only)
     * |        |          |0 = System SRAM bank0 BIST active.
     * |        |          |1 = System SRAM bank0 BIST finish.
     * |[17]    |SRBEND1   |System SRAM Bank1 BIST Test Finish (Read Only)
     * |        |          |0 = System SRAM bank1 BIST is active.
     * |        |          |1 = System SRAM bank1 BIST finish.
     * |[18]    |CRBEND    |CACHE SRAM BIST Test Finish (Read Only)
     * |        |          |0 = CACHE SRAM BIST is active.
     * |        |          |1 = CACHE SRAM BIST test finish.
     * |[19]    |CANBEND   |CAN SRAM BIST Test Finish (Read Only)
     * |        |          |0 = CAN SRAM BIST is active.
     * |        |          |1 = CAN SRAM BIST test finish.
     * |        |          |Note: All of the CAN SRAM macros BIST finish, this flag is 1.
     * |[20]    |USBBEND   |USB SRAM BIST Test Finish
     * |        |          |0 = USB SRAM BIST is active. (Read Only)
     * |        |          |1 = USB SRAM BIST test finish.
     * |[21]    |SPIMBEND  |SPIM SRAM BIST Test Finish (Read Only)
     * |        |          |0 = SPIM SRAM BIST is active.
     * |        |          |1 = SPIM SRAM BIST test finish.
     * |[22]    |EMAC0BEND |EMAC0 SRAM BIST Test Finish (Read Only)
     * |        |          |0 = EMAC0 SRAM BIST is active.
     * |        |          |1 = EMAC0 SRAM BIST test finish.
     * |[24]    |HSUSBDBEND|HSUSBD BIST Test Finish (Read Only)
     * |        |          |0 = HSUSBD SRAM BIST is active.
     * |        |          |1 = HSUSBD SRAM BIST test finish.
     * |[25]    |HSUSBHBEND|HSUSBH BIST Test Finish (Read Only)
     * |        |          |0 = HSUSBH SRAM BIST is active.
     * |        |          |1 = HSUSBH SRAM BIST test finish.
     * |[26]    |SRBEND2   |System SRAM Bank2 BIST Test Finish (Read Only)
     * |        |          |0 = System SRAM bank2 BIST is active.
     * |        |          |1 = System SRAM bank2 BIST finish.
     * |[27]    |KSBEND    |Key Store SRAM BIST Test Finish (Read Only)
     * |        |          |0 = Key Store SRAM BIST is active.
     * |        |          |1 = Key Store SRAM BIST test finish.
     * |[28]    |CCAPBEND  |CCAP SRAM BIST Test Finish (Read Only)
     * |        |          |0 = CCAP SRAM BIST is active.
     * |        |          |1 = CCAP SRAM BIST test finish.
     * |[29]    |RSABEND   |RSA SRAM BIST Test Finish (Read Only)
     * |        |          |0 = RSA SRAM BIST is active.
     * |        |          |1 = RSA SRAM BIST test finish.
     * @var SYS_T::HIRCTCTL
     * Offset: 0xE4  HIRC48M Trim Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |FREQSEL   |Trim Frequency Selection
     * |        |          |This field indicates the target frequency of 48 MHz internal high speed RC oscillator (HIRC48M) auto trim.
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
     * |        |          |If the trim value update counter reached this limitation value and frequency of HIRC still does not lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
     * |        |          |00 = Trim retry count limitation is 64 loops.
     * |        |          |01 = Trim retry count limitation is 128 loops.
     * |        |          |10 = Trim retry count limitation is 256 loops.
     * |        |          |11 = Trim retry count limitation is 512 loops.
     * |[8]     |CESTOPEN  |Clock Error Stop Enable Bit
     * |        |          |0 = The trim operation is keep going if clock is inaccuracy.
     * |        |          |1 = The trim operation is stopped if clock is inaccuracy.
     * |[9]     |BOUNDEN   |Boundary Enable Bit
     * |        |          |0 = Boundary function Disabled.
     * |        |          |1 = Boundary function Enabled.
     * |[10]    |REFCKSEL  |Reference Clock Selection
     * |        |          |0 = HIRC trim reference clock is from LXT (32.768 kHz).
     * |        |          |1 = HIRC trim reference clock is from internal USB synchronous mode.
     * |        |          |Note: HIRC trim reference clock is 20 kHz in test mode.
     * |[20:16] |BOUNDARY  |Boundary Selection
     * |        |          |Fill the boundary range from 0x1 to 0x31, 0x0 is reserved.
     * |        |          |Note: This field is effective only when the BOUNDEN(SYS_HIRCTCTL[9]) is enabled.
     * @var SYS_T::HIRCTIEN
     * Offset: 0xE8  HIRC48M Trim Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |TFAILIEN  |Trim Failure Interrupt Enable Bit
     * |        |          |This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_HIRCTCTL[1:0]).
     * |        |          |If this bit is high and TFAILIF(SYS_HIRCTISTS[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |0 = Disable TFAILIF(SYS_HIRCTISTS[1]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable TFAILIF(SYS_HIRCTISTS[1]) status to trigger an interrupt to CPU.
     * |[2]     |CLKEIEN   |Clock Error Interrupt Enable Bit
     * |        |          |This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
     * |        |          |If this bit is set to1, and CLKERRIF(SYS_HIRCTISTS[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |0 = Disable CLKERRIF(SYS_HIRCTISTS[2]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable CLKERRIF(SYS_HIRCTISTS[2]) status to trigger an interrupt to CPU.
     * @var SYS_T::HIRCTISTS
     * Offset: 0xEC  HIRC48M Trim Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FREQLOCK  |HIRC Frequency Lock Status
     * |        |          |This bit indicates the HIRC frequency is locked.
     * |        |          |This is a status bit and does not trigger any interrupt.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
     * |        |          |0 = The internal high-speed oscillator frequency does not lock at 48 MHz yet.
     * |        |          |1 = The internal high-speed oscillator frequency locked at 48 MHz.
     * |[1]     |TFAILIF   |Trim Failure Interrupt Status
     * |        |          |This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still does not be locked.
     * |        |          |Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_HIRCTCTL[1:0]) will be cleared to 00 by hardware automatically.
     * |        |          |If this bit is set and TFAILIEN(SYS_HIRCTIEN[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Trim value update limitation count does not reach.
     * |        |          |1 = Trim value update limitation count reached and HIRC frequency still not locked.
     * |[2]     |CLKERRIF  |Clock Error Interrupt Status
     * |        |          |When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 48 MHz internal high speed RC oscillator (HIRC48M) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy.
     * |        |          |Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_HIRCTCTL[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_HIRCTCTL[8]) is set to 1.
     * |        |          |If this bit is set and CLKEIEN(SYS_HIRCTIEN[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Clock frequency is accuracy.
     * |        |          |1 = Clock frequency is inaccuracy.
     * |[3]     |OVBDIF    |Over Boundary Status
     * |        |          |When the over boundary function is set, if there occurs the over boundary condition, this flag will be set.
     * |        |          |0 = Over boundary condition did not occur.
     * |        |          |1 = Over boundary condition occurred.
     * |        |          |Note: Write 1 to clear this flag.
     * @var SYS_T::IRCTCTL
     * Offset: 0xF0  HIRC Trim Control Register
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
     * |        |          |If the trim value update counter reached this limitation value and frequency of HIRC still does not lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
     * |        |          |00 = Trim retry count limitation is 64 loops.
     * |        |          |01 = Trim retry count limitation is 128 loops.
     * |        |          |10 = Trim retry count limitation is 256 loops.
     * |        |          |11 = Trim retry count limitation is 512 loops.
     * |[8]     |CESTOPEN  |Clock Error Stop Enable Bit
     * |        |          |0 = The trim operation is keep going if clock is inaccuracy.
     * |        |          |1 = The trim operation is stopped if clock is inaccuracy.
     * |[9]     |BOUNDEN   |Boundary Enable Bit
     * |        |          |0 = Boundary function Disabled.
     * |        |          |1 = Boundary function Enabled.
     * |[10]    |REFCKSEL  |Reference Clock Selection
     * |        |          |0 = HIRC trim reference clock is from LXT (32.768 kHz).
     * |        |          |1 = HIRC trim reference clock is from internal USB synchronous mode.
     * |        |          |Note: HIRC trim reference clock is 20 kHz in test mode.
     * |[20:16] |BOUNDARY  |Boundary Selection
     * |        |          |Fill the boundary range from 0x1 to 0x31, 0x0 is reserved.
     * |        |          |Note: This field is effective only when the BOUNDEN(SYS_IRCTCTL[9]) is enabled.
     * @var SYS_T::IRCTIEN
     * Offset: 0xF4  HIRC Trim Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |TFAILIEN  |Trim Failure Interrupt Enable Bit
     * |        |          |This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_IRCTCTL[1:0]).
     * |        |          |If this bit is high and TFAILIF(SYS_IRCTISTS[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |0 = Disable TFAILIF(SYS_IRCTISTS[1]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable TFAILIF(SYS_IRCTISTS[1]) status to trigger an interrupt to CPU.
     * |[2]     |CLKEIEN   |Clock Error Interrupt Enable Bit
     * |        |          |This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
     * |        |          |If this bit is set to1, and CLKERRIF(SYS_IRCTISTS[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
     * |        |          |0 = Disable CLKERRIF(SYS_IRCTISTS[2]) status to trigger an interrupt to CPU.
     * |        |          |1 = Enable CLKERRIF(SYS_IRCTISTS[2]) status to trigger an interrupt to CPU.
     * @var SYS_T::IRCTISTS
     * Offset: 0xF8  HIRC Trim Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FREQLOCK  |HIRC Frequency Lock Status
     * |        |          |This bit indicates the HIRC frequency is locked.
     * |        |          |This is a status bit and does not trigger any interrupt.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
     * |        |          |0 = The internal high-speed oscillator frequency does not lock at 12 MHz yet.
     * |        |          |1 = The internal high-speed oscillator frequency locked at 12 MHz.
     * |[1]     |TFAILIF   |Trim Failure Interrupt Status
     * |        |          |This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still does not be locked.
     * |        |          |Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_IRCTCTL[1:0]) will be cleared to 00 by hardware automatically.
     * |        |          |If this bit is set and TFAILIEN(SYS_IRCTIEN[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
     * |        |          |Write 1 to clear this to 0.
     * |        |          |0 = Trim value update limitation count does not reach.
     * |        |          |1 = Trim value update limitation count reached and HIRC frequency still not locked.
     * |[2]     |CLKERRIF  |Clock Error Interrupt Status
     * |        |          |When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 12 MHz internal high speed RC oscillator (HIRC) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy.
     * |        |          |Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_IRCTCL[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_IRCTCTL[8]) is set to 1.
     * |        |          |If this bit is set and CLKEIEN(SYS_IRCTIEN[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
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
     * |        |          |Some registers have write-protection function.
     * |        |          |Writing these registers have to disable the protected function by writing the sequence value 0x59, 0x16, 0x88 to this field.
     * |        |          |After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
     * |        |          |REGLCTL[0]
     * |        |          |Register Lock Control Disable Index (Read Only)
     * |        |          |0 = Write-protection Enabled for writing protected registers. Any write to the protected register is ignored.
     * |        |          |1 = Write-protection Disabled for writing protected registers.
     * @var SYS_T::PORDISAN
     * Offset: 0x1EC  Analog POR Disable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |POROFFAN  |Power-on Reset Enable Bit (Write Protect)
     * |        |          |After powered on, User can turn off internal analog POR circuit to save power by writing 0x5AA5 to this field.
     * |        |          |The analog POR circuit will be active again when this field is set to another value or chip is reset by other reset source, including:
     * |        |          |nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::CSERVER
     * Offset: 0x1F4  Chip Series Version Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |VERSION   |Chip Series Version (Read Only)
     * |        |          |These bits indicate the series version of chip.
     * |        |          |0x2 = M460HD.
     * |        |          |0x3 = M460LD.
     * |        |          |Others = Reserved.
     * @var SYS_T::PLCTL
     * Offset: 0x1F8  Power Level Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PLSEL     |Power Level Select (Write Protect)
     * |        |          |These bits indicate the status of power level.
     * |        |          |00 = Power level is PL0.
     * |        |          |01 = Power level is PL1.
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
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
     * |        |          |0 = Core voltage change is completed.
     * |        |          |1 = Core voltage change is ongoing.
     * |[9:8]   |PLSTATUS  |Power Level Status (Read Only)
     * |        |          |This bit indicates the status of power level.
     * |        |          |00 = Power level is PL0.
     * |        |          |01 = Power level is PL1.
     * |        |          |Others = Reserved.
     * @var SYS_T::AHBMCTL
     * Offset: 0x400  AHB Bus Matrix Priority Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INTACTEN  |Highest AHB Bus Priority of Cortex-M4 Core Enable Bit (Write Protect)
     * |        |          |Enable Cortex-M4 Core With Highest AHB Bus Priority In AHB Bus Matrix.
     * |        |          |0 = Round-robin mode.
     * |        |          |1 = Cortex-M4 CPU with highest bus priority when interrupt occurred.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var SYS_T::GPA_MFP0
     * Offset: 0x500  GPIOA Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PA0MFP    |PA.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_MOSI
     * |        |          |03 = QSPI0_MOSI0
     * |        |          |04 = SPI0_MOSI
     * |        |          |05 = SD1_DAT0
     * |        |          |06 = SC0_CLK
     * |        |          |07 = UART0_RXD
     * |        |          |08 = UART1_nRTS
     * |        |          |09 = I2C2_SDA
     * |        |          |10 = CCAP_DATA6
     * |        |          |12 = BPWM0_CH0
     * |        |          |13 = EPWM0_CH5
     * |        |          |14 = EQEI3_B
     * |        |          |15 = DAC0_ST
     * |        |          |17 = PSIO0_CH7
     * |        |          |20 = BMC19
     * |[12:8]  |PA1MFP    |PA.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_MISO
     * |        |          |03 = QSPI0_MISO0
     * |        |          |04 = SPI0_MISO
     * |        |          |05 = SD1_DAT1
     * |        |          |06 = SC0_DAT
     * |        |          |07 = UART0_TXD
     * |        |          |08 = UART1_nCTS
     * |        |          |09 = I2C2_SCL
     * |        |          |10 = CCAP_DATA7
     * |        |          |12 = BPWM0_CH1
     * |        |          |13 = EPWM0_CH4
     * |        |          |14 = EQEI3_A
     * |        |          |15 = DAC1_ST
     * |        |          |17 = PSIO0_CH6
     * |        |          |20 = BMC18
     * |[20:16] |PA2MFP    |PA.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_CLK
     * |        |          |03 = QSPI0_CLK
     * |        |          |04 = SPI0_CLK
     * |        |          |05 = SD1_DAT2
     * |        |          |06 = SC0_RST
     * |        |          |07 = UART4_RXD
     * |        |          |08 = UART1_RXD
     * |        |          |09 = I2C1_SDA
     * |        |          |10 = I2C0_SMBSUS
     * |        |          |12 = BPWM0_CH2
     * |        |          |13 = EPWM0_CH3
     * |        |          |14 = EQEI3_INDEX
     * |        |          |17 = PSIO0_CH5
     * |        |          |20 = BMC17
     * |[28:24] |PA3MFP    |PA.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_SS
     * |        |          |03 = QSPI0_SS
     * |        |          |04 = SPI0_SS
     * |        |          |05 = SD1_DAT3
     * |        |          |06 = SC0_PWR
     * |        |          |07 = UART4_TXD
     * |        |          |08 = UART1_TXD
     * |        |          |09 = I2C1_SCL
     * |        |          |10 = I2C0_SMBAL
     * |        |          |12 = BPWM0_CH3
     * |        |          |13 = EPWM0_CH2
     * |        |          |14 = EQEI0_B
     * |        |          |15 = EPWM1_BRAKE1
     * |        |          |17 = PSIO0_CH4
     * |        |          |20 = BMC16
     * @var SYS_T::GPA_MFP1
     * Offset: 0x504  GPIOA Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PA4MFP    |PA.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_D3
     * |        |          |03 = QSPI0_MOSI1
     * |        |          |04 = SPI0_I2SMCLK
     * |        |          |05 = SD1_CLK
     * |        |          |06 = SC0_nCD
     * |        |          |07 = UART0_nRTS
     * |        |          |08 = UART5_RXD
     * |        |          |09 = I2C0_SDA
     * |        |          |10 = CAN0_RXD
     * |        |          |11 = UART0_RXD
     * |        |          |12 = BPWM0_CH4
     * |        |          |13 = EPWM0_CH1
     * |        |          |14 = EQEI0_A
     * |[12:8]  |PA5MFP    |PA.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = SPIM_D2
     * |        |          |03 = QSPI0_MISO1
     * |        |          |04 = SPI1_I2SMCLK
     * |        |          |05 = SD1_CMD
     * |        |          |06 = SC2_nCD
     * |        |          |07 = UART0_nCTS
     * |        |          |08 = UART5_TXD
     * |        |          |09 = I2C0_SCL
     * |        |          |10 = CAN0_TXD
     * |        |          |11 = UART0_TXD
     * |        |          |12 = BPWM0_CH5
     * |        |          |13 = EPWM0_CH0
     * |        |          |14 = EQEI0_INDEX
     * |[20:16] |PA6MFP    |PA.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD6
     * |        |          |03 = EMAC0_RMII_RXERR
     * |        |          |04 = SPI1_SS
     * |        |          |05 = SD1_nCD
     * |        |          |06 = SC2_CLK
     * |        |          |07 = UART0_RXD
     * |        |          |08 = I2C1_SDA
     * |        |          |09 = QSPI1_MOSI1
     * |        |          |11 = EPWM1_CH5
     * |        |          |12 = BPWM1_CH3
     * |        |          |13 = ACMP1_WLAT
     * |        |          |14 = TM3
     * |        |          |15 = INT0
     * |        |          |17 = SPI5_CLK
     * |        |          |18 = KPI_COL0
     * |        |          |19 = SPI6_CLK
     * |        |          |20 = BMC15
     * |[28:24] |PA7MFP    |PA.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD7
     * |        |          |03 = EMAC0_RMII_CRSDV
     * |        |          |04 = SPI1_CLK
     * |        |          |06 = SC2_DAT
     * |        |          |07 = UART0_TXD
     * |        |          |08 = I2C1_SCL
     * |        |          |09 = QSPI1_MISO1
     * |        |          |11 = EPWM1_CH4
     * |        |          |12 = BPWM1_CH2
     * |        |          |13 = ACMP0_WLAT
     * |        |          |14 = TM2
     * |        |          |15 = INT1
     * |        |          |17 = SPI5_SS
     * |        |          |18 = KPI_COL1
     * |        |          |19 = SPI6_SS
     * |        |          |20 = BMC14
     * @var SYS_T::GPA_MFP2
     * Offset: 0x508  GPIOA Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PA8MFP    |PA.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH4, EADC2_CH4
     * |        |          |02 = EBI_ALE
     * |        |          |03 = SC2_CLK
     * |        |          |04 = SPI2_MOSI
     * |        |          |05 = SD1_DAT0
     * |        |          |06 = USCI0_CTL1
     * |        |          |07 = UART1_RXD
     * |        |          |08 = UART7_RXD
     * |        |          |09 = BPWM0_CH3
     * |        |          |10 = EQEI1_B
     * |        |          |11 = ECAP0_IC2
     * |        |          |12 = I2S1_DO
     * |        |          |13 = TM3_EXT
     * |        |          |15 = INT4
     * |        |          |20 = BMC9
     * |[12:8]  |PA9MFP    |PA.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH5, EADC2_CH5
     * |        |          |02 = EBI_MCLK
     * |        |          |03 = SC2_DAT
     * |        |          |04 = SPI2_MISO
     * |        |          |05 = SD1_DAT1
     * |        |          |06 = USCI0_DAT1
     * |        |          |07 = UART1_TXD
     * |        |          |08 = UART7_TXD
     * |        |          |09 = BPWM0_CH2
     * |        |          |10 = EQEI1_A
     * |        |          |11 = ECAP0_IC1
     * |        |          |12 = I2S1_DI
     * |        |          |13 = TM2_EXT
     * |        |          |15 = SWDH_DAT (for M460HD)
     * |        |          |20 = BMC8
     * |[20:16] |PA10MFP   |PA.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH6, EADC2_CH6, ACMP1_P0
     * |        |          |02 = EBI_nWR
     * |        |          |03 = SC2_RST
     * |        |          |04 = SPI2_CLK
     * |        |          |05 = SD1_DAT2
     * |        |          |06 = USCI0_DAT0
     * |        |          |07 = I2C2_SDA
     * |        |          |08 = UART6_RXD
     * |        |          |09 = BPWM0_CH1
     * |        |          |10 = EQEI1_INDEX
     * |        |          |11 = ECAP0_IC0
     * |        |          |12 = I2S1_MCLK
     * |        |          |13 = TM1_EXT
     * |        |          |14 = DAC0_ST
     * |        |          |15 = SWDH_CLK (for M460HD)
     * |        |          |18 = KPI_ROW5
     * |        |          |20 = BMC7
     * |[28:24] |PA11MFP   |PA.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH7, EADC2_CH7, ACMP0_P0
     * |        |          |02 = EBI_nRD
     * |        |          |03 = SC2_PWR
     * |        |          |04 = SPI2_SS
     * |        |          |05 = SD1_DAT3
     * |        |          |06 = USCI0_CLK
     * |        |          |07 = I2C2_SCL
     * |        |          |08 = UART6_TXD
     * |        |          |09 = BPWM0_CH0
     * |        |          |10 = EPWM0_SYNC_OUT
     * |        |          |12 = I2S1_BCLK
     * |        |          |13 = TM0_EXT
     * |        |          |14 = DAC1_ST
     * |        |          |18 = KPI_ROW4
     * |        |          |20 = BMC6
     * @var SYS_T::GPA_MFP3
     * Offset: 0x50C  GPIOA Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PA12MFP   |PA.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = I2S0_BCLK
     * |        |          |03 = UART4_TXD
     * |        |          |04 = I2C1_SCL
     * |        |          |05 = SPI2_SS
     * |        |          |06 = CAN0_TXD
     * |        |          |07 = SC2_PWR
     * |        |          |08 = SD1_nCD
     * |        |          |09 = SPI0_SS (for M460LD)
     * |        |          |10 = QSPI1_MISO0
     * |        |          |11 = BPWM1_CH2
     * |        |          |12 = EQEI1_INDEX
     * |        |          |13 = ECAP3_IC0
     * |        |          |14 = USB_VBUS
     * |        |          |17 = PSIO0_CH4
     * |        |          |19 = SPI10_SS
     * |        |          |20 = BMC12
     * |[12:8]  |PA13MFP   |PA.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = I2S0_MCLK
     * |        |          |03 = UART4_RXD
     * |        |          |04 = I2C1_SDA
     * |        |          |05 = SPI2_CLK
     * |        |          |06 = CAN0_RXD
     * |        |          |07 = SC2_RST
     * |        |          |09 = SPI0_CLK (for M460LD)
     * |        |          |10 = QSPI1_MOSI0
     * |        |          |11 = BPWM1_CH3
     * |        |          |12 = EQEI1_A
     * |        |          |13 = ECAP3_IC1
     * |        |          |14 = USB_D-
     * |        |          |17 = PSIO0_CH5
     * |        |          |19 = SPI10_CLK
     * |        |          |20 = BMC13
     * |[20:16] |PA14MFP   |PA.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = I2S0_DI
     * |        |          |03 = UART0_TXD
     * |        |          |04 = EBI_AD5
     * |        |          |05 = SPI2_MISO
     * |        |          |06 = I2C2_SCL
     * |        |          |07 = SC2_DAT
     * |        |          |09 = SPI0_MISO (for M460LD)
     * |        |          |11 = BPWM1_CH4
     * |        |          |12 = EQEI1_B
     * |        |          |13 = ECAP3_IC2
     * |        |          |14 = USB_D+
     * |        |          |16 = I2C0_SCL (for M460LD)
     * |        |          |17 = PSIO0_CH6
     * |        |          |19 = SPI10_MISO
     * |        |          |20 = BMC14
     * |[28:24] |PA15MFP   |PA.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = I2S0_DO
     * |        |          |03 = UART0_RXD
     * |        |          |04 = SPIM_MOSI
     * |        |          |05 = SPI2_MOSI
     * |        |          |06 = I2C2_SDA
     * |        |          |07 = SC2_CLK
     * |        |          |09 = SPI0_MOSI (for M460LD)
     * |        |          |11 = BPWM1_CH5
     * |        |          |12 = EPWM0_SYNC_IN
     * |        |          |13 = EQEI3_INDEX
     * |        |          |14 = USB_OTG_ID
     * |        |          |16 = I2C0_SDA (for M460LD)
     * |        |          |17 = PSIO0_CH7
     * |        |          |19 = SPI10_MOSI
     * |        |          |20 = BMC15
     * @var SYS_T::GPB_MFP0
     * Offset: 0x510  GPIOB Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PB0MFP    |PB.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH0, EADC1_CH8, EADC2_CH8, ACMP3_N
     * |        |          |02 = EBI_ADR9
     * |        |          |03 = SD0_CMD
     * |        |          |04 = SPI2_I2SMCLK
     * |        |          |06 = USCI0_CTL0
     * |        |          |07 = UART2_RXD
     * |        |          |08 = SPI0_I2SMCLK
     * |        |          |09 = I2C1_SDA
     * |        |          |10 = I2S1_LRCK
     * |        |          |11 = EPWM0_CH5
     * |        |          |12 = EPWM1_CH5
     * |        |          |13 = EPWM0_BRAKE1
     * |        |          |14 = ACMP3_O
     * |        |          |15 = QSPI0_MOSI1
     * |        |          |18 = KPI_ROW3
     * |        |          |19 = SPI4_MOSI
     * |        |          |20 = BMC5
     * |[12:8]  |PB1MFP    |PB.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH1, EADC1_CH9, EADC2_CH9, ACMP3_P0
     * |        |          |02 = EBI_ADR8
     * |        |          |03 = SD0_CLK
     * |        |          |04 = EMAC_RMII_RXERR
     * |        |          |05 = SPI1_I2SMCLK
     * |        |          |06 = SPI3_I2SMCLK
     * |        |          |07 = UART2_TXD
     * |        |          |09 = I2C1_SCL
     * |        |          |10 = I2S0_LRCK
     * |        |          |11 = EPWM0_CH4
     * |        |          |12 = EPWM1_CH4
     * |        |          |13 = EPWM0_BRAKE0
     * |        |          |14 = ACMP2_O
     * |        |          |15 = QSPI0_MISO1
     * |        |          |18 = KPI_ROW2
     * |        |          |19 = SPI4_MISO
     * |        |          |20 = BMC4
     * |[20:16] |PB2MFP    |PB.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH2, EADC1_CH10, ACMP0_P1
     * |        |          |02 = EBI_ADR3
     * |        |          |03 = SD0_DAT0
     * |        |          |04 = EMAC0_RMII_CRSDV
     * |        |          |05 = SPI1_SS
     * |        |          |06 = UART1_RXD
     * |        |          |07 = UART5_nCTS
     * |        |          |09 = SC0_PWR
     * |        |          |10 = I2S0_DO
     * |        |          |11 = EPWM0_CH3
     * |        |          |12 = I2C1_SDA
     * |        |          |14 = TM3
     * |        |          |15 = INT3
     * |        |          |17 = PSIO0_CH7
     * |        |          |18 = KPI_ROW1
     * |        |          |19 = SPI4_CLK
     * |        |          |20 = BMC3
     * |[28:24] |PB3MFP    |PB.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH3, EADC1_CH11, ACMP0_N
     * |        |          |02 = EBI_ADR2
     * |        |          |03 = SD0_DAT1
     * |        |          |04 = EMAC0_RMII_RXD1
     * |        |          |05 = SPI1_CLK
     * |        |          |06 = UART1_TXD
     * |        |          |07 = UART5_nRTS
     * |        |          |09 = SC0_RST
     * |        |          |10 = I2S0_DI
     * |        |          |11 = EPWM0_CH2
     * |        |          |12 = I2C1_SCL
     * |        |          |14 = TM2
     * |        |          |15 = INT2
     * |        |          |17 = PSIO0_CH6
     * |        |          |18 = KPI_ROW0
     * |        |          |19 = SPI4_SS
     * |        |          |20 = BMC2
     * @var SYS_T::GPB_MFP1
     * Offset: 0x514  GPIOB Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PB4MFP    |PB.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH4, ACMP1_P1
     * |        |          |02 = EBI_ADR1
     * |        |          |03 = SD0_DAT2
     * |        |          |04 = EMAC0_RMII_RXD0
     * |        |          |05 = SPI1_MOSI
     * |        |          |06 = I2C0_SDA
     * |        |          |07 = UART5_RXD
     * |        |          |09 = SC0_DAT
     * |        |          |10 = I2S0_MCLK
     * |        |          |11 = EPWM0_CH1
     * |        |          |12 = UART2_RXD
     * |        |          |14 = TM1
     * |        |          |15 = INT1
     * |        |          |17 = PSIO0_CH5
     * |        |          |18 = KPI_COL7
     * |        |          |20 = BMC1
     * |[12:8]  |PB5MFP    |PB.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH5, ACMP1_N
     * |        |          |02 = EBI_ADR0
     * |        |          |03 = SD0_DAT3
     * |        |          |04 = EMAC0_RMII_REFCLK
     * |        |          |05 = SPI1_MISO
     * |        |          |06 = I2C0_SCL
     * |        |          |07 = UART5_TXD
     * |        |          |09 = SC0_CLK
     * |        |          |10 = I2S0_BCLK
     * |        |          |11 = EPWM0_CH0
     * |        |          |12 = UART2_TXD
     * |        |          |14 = TM0
     * |        |          |15 = INT0
     * |        |          |17 = PSIO0_CH4
     * |        |          |18 = KPI_COL6
     * |        |          |20 = BMC0
     * |[20:16] |PB6MFP    |PB.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH6, EADC2_CH14, ACMP2_N
     * |        |          |02 = EBI_nWRH
     * |        |          |03 = EMAC0_PPS
     * |        |          |05 = CAN1_RXD
     * |        |          |06 = UART1_RXD
     * |        |          |07 = SD1_CLK
     * |        |          |08 = EBI_nCS1
     * |        |          |10 = BPWM1_CH5
     * |        |          |11 = EPWM1_BRAKE1
     * |        |          |12 = EPWM1_CH5
     * |        |          |13 = INT4
     * |        |          |14 = USB_VBUS_EN
     * |        |          |15 = ACMP1_O
     * |        |          |16 = SPI3_MOSI (for M460LD)
     * |        |          |18 = KPI_COL5
     * |        |          |19 = SPI1_SS
     * |        |          |20 = BMC31
     * |[28:24] |PB7MFP    |PB.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH7, EADC2_CH15, ACMP2_P0
     * |        |          |02 = EBI_nWRL
     * |        |          |03 = EMAC0_RMII_TXEN
     * |        |          |05 = CAN1_TXD
     * |        |          |06 = UART1_TXD
     * |        |          |07 = SD1_CMD
     * |        |          |08 = EBI_nCS0
     * |        |          |10 = BPWM1_CH4
     * |        |          |11 = EPWM1_BRAKE0
     * |        |          |12 = EPWM1_CH4
     * |        |          |13 = INT5
     * |        |          |14 = USB_VBUS_ST
     * |        |          |15 = ACMP0_O
     * |        |          |16 = SPI3_MISO (for M460LD)
     * |        |          |18 = KPI_COL4
     * |        |          |19 = SPI1_CLK (for M460LD)
     * |        |          |20 = BMC30
     * @var SYS_T::GPB_MFP2
     * Offset: 0x518  GPIOB Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PB8MFP    |PB.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH8, ACMP2_P1
     * |        |          |02 = EBI_ADR19
     * |        |          |03 = EMAC0_RMII_TXD1
     * |        |          |05 = UART0_RXD
     * |        |          |06 = UART1_nRTS
     * |        |          |07 = I2C1_SMBSUS
     * |        |          |08 = UART7_RXD
     * |        |          |09 = I2C0_SDA
     * |        |          |10 = BPWM1_CH3
     * |        |          |11 = SPI3_MOSI
     * |        |          |12 = CAN2_RXD
     * |        |          |13 = INT6
     * |        |          |14 = EADC2_ST
     * |        |          |20 = BMC23
     * |[12:8]  |PB9MFP    |PB.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH9, ACMP2_P2
     * |        |          |02 = EBI_ADR18
     * |        |          |03 = EMAC0_RMII_TXD0
     * |        |          |05 = UART0_TXD
     * |        |          |06 = UART1_nCTS
     * |        |          |07 = I2C1_SMBAL
     * |        |          |08 = UART7_TXD
     * |        |          |09 = I2C0_SCL
     * |        |          |10 = BPWM1_CH2
     * |        |          |11 = SPI3_MISO
     * |        |          |12 = CAN2_TXD
     * |        |          |13 = INT7
     * |        |          |14 = CCAP_HSYNC
     * |        |          |20 = BMC22
     * |[20:16] |PB10MFP   |PB.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH10, ACMP2_P3
     * |        |          |02 = EBI_ADR17
     * |        |          |03 = EMAC0_RMII_MDIO
     * |        |          |05 = UART0_nRTS
     * |        |          |06 = UART4_RXD
     * |        |          |07 = I2C1_SDA
     * |        |          |08 = CAN0_RXD
     * |        |          |10 = BPWM1_CH1
     * |        |          |11 = SPI3_SS
     * |        |          |12 = CCAP_VSYNC
     * |        |          |14 = HSUSB_VBUS_EN
     * |        |          |20 = BMC21
     * |[28:24] |PB11MFP   |PB.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH11
     * |        |          |02 = EBI_ADR16
     * |        |          |03 = EMAC0_RMII_MDC
     * |        |          |05 = UART0_nCTS
     * |        |          |06 = UART4_TXD
     * |        |          |07 = I2C1_SCL
     * |        |          |08 = CAN0_TXD
     * |        |          |09 = SPI0_I2SMCLK
     * |        |          |10 = BPWM1_CH0
     * |        |          |11 = SPI3_CLK
     * |        |          |12 = CCAP_SFIELD
     * |        |          |14 = HSUSB_VBUS_ST
     * |        |          |20 = BMC20
     * @var SYS_T::GPB_MFP3
     * Offset: 0x51C  GPIOB Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PB12MFP   |PB.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH12, EADC1_CH12, DAC0_OUT, ACMP0_P2, ACMP1_P2
     * |        |          |02 = EBI_AD15
     * |        |          |03 = SC1_CLK
     * |        |          |04 = SPI0_MOSI
     * |        |          |05 = USCI0_CLK
     * |        |          |06 = UART0_RXD
     * |        |          |07 = UART3_nCTS
     * |        |          |08 = I2C2_SDA
     * |        |          |09 = SD0_nCD
     * |        |          |10 = CCAP_SCLK
     * |        |          |11 = EPWM1_CH3
     * |        |          |12 = ETMC_TRACE_DATA3 (for M460HD)
     * |        |          |13 = TM3_EXT
     * |        |          |14 = CAN3_RXD
     * |        |          |16 = SPI3_SS (for M460LD)
     * |        |          |17 = PSIO0_CH3
     * |        |          |18 = KPI_COL3
     * |        |          |20 = BMC29
     * |[12:8]  |PB13MFP   |PB.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH13, EADC1_CH13, DAC1_OUT, ACMP0_P3, ACMP1_P3
     * |        |          |02 = EBI_AD14
     * |        |          |03 = SC1_DAT
     * |        |          |04 = SPI0_MISO
     * |        |          |05 = USCI0_DAT0
     * |        |          |06 = UART0_TXD
     * |        |          |07 = UART3_nRTS
     * |        |          |08 = I2C2_SCL
     * |        |          |10 = CCAP_PIXCLK
     * |        |          |11 = EPWM1_CH2
     * |        |          |12 = ETMC_TRACE_DATA2 (for M460HD)
     * |        |          |13 = TM2_EXT
     * |        |          |14 = CAN3_TXD
     * |        |          |16 = SPI3_CLK (for M460LD)
     * |        |          |17 = PSIO0_CH2
     * |        |          |18 = KPI_COL2
     * |        |          |19 = SPI9_MISO
     * |        |          |20 = BMC28
     * |[20:16] |PB14MFP   |PB.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH14, EADC1_CH14
     * |        |          |02 = EBI_AD13
     * |        |          |03 = SC1_RST
     * |        |          |04 = SPI0_CLK
     * |        |          |05 = USCI0_DAT1
     * |        |          |06 = UART0_nRTS
     * |        |          |07 = UART3_RXD
     * |        |          |08 = I2C2_SMBSUS
     * |        |          |09 = CCAP_DATA0
     * |        |          |11 = EPWM1_CH1
     * |        |          |12 = ETMC_TRACE_DATA1 (for M460HD)
     * |        |          |13 = TM1_EXT
     * |        |          |14 = CLKO
     * |        |          |15 = USB_VBUS_ST
     * |        |          |17 = PSIO0_CH1
     * |        |          |18 = KPI_COL1
     * |        |          |19 = SPI9_SS
     * |[28:24] |PB15MFP   |PB.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC0_CH15, EADC1_CH15
     * |        |          |02 = EBI_AD12
     * |        |          |03 = SC1_PWR
     * |        |          |04 = SPI0_SS
     * |        |          |05 = USCI0_CTL1
     * |        |          |06 = UART0_nCTS
     * |        |          |07 = UART3_TXD
     * |        |          |08 = I2C2_SMBAL
     * |        |          |09 = CCAP_DATA1
     * |        |          |10 = EPWM0_BRAKE1
     * |        |          |11 = EPWM1_CH0
     * |        |          |12 = ETMC_TRACE_DATA0 (for M460HD)
     * |        |          |13 = TM0_EXT
     * |        |          |14 = USB_VBUS_EN
     * |        |          |15 = HSUSB_VBUS_EN (for M460HD)
     * |        |          |17 = PSIO0_CH0
     * |        |          |18 = KPI_COL0
     * |        |          |19 = SPI9_CLK
     * |        |          |20 = BMC27
     * @var SYS_T::GPC_MFP0
     * Offset: 0x520  GPIOC Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PC0MFP    |PC.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD0
     * |        |          |03 = SPIM_MOSI
     * |        |          |04 = QSPI0_MOSI0
     * |        |          |05 = SC1_CLK
     * |        |          |06 = I2S0_LRCK
     * |        |          |07 = SPI1_SS
     * |        |          |08 = UART2_RXD
     * |        |          |09 = I2C0_SDA
     * |        |          |10 = CAN2_RXD
     * |        |          |12 = EPWM1_CH5
     * |        |          |13 = CCAP_DATA0
     * |        |          |14 = ACMP1_O
     * |        |          |15 = EADC1_ST
     * |        |          |16 = HBI_D2
     * |        |          |17 = QSPI1_CLK (for M460LD)
     * |        |          |18 = KPI_ROW5
     * |        |          |19 = SPI7_MOSI
     * |        |          |20 = BMC25
     * |[12:8]  |PC1MFP    |PC.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD1
     * |        |          |03 = SPIM_MISO
     * |        |          |04 = QSPI0_MISO0
     * |        |          |05 = SC1_DAT
     * |        |          |06 = I2S0_DO
     * |        |          |07 = SPI1_CLK
     * |        |          |08 = UART2_TXD
     * |        |          |09 = I2C0_SCL
     * |        |          |10 = CAN2_TXD
     * |        |          |12 = EPWM1_CH4
     * |        |          |13 = CCAP_DATA1
     * |        |          |14 = ACMP0_O
     * |        |          |15 = EADC0_ST
     * |        |          |16 = HBI_RWDS
     * |        |          |17 = QSPI1_SS (for M460LD)
     * |        |          |18 = KPI_ROW4
     * |        |          |19 = SPI7_MISO
     * |        |          |20 = BMC24
     * |[20:16] |PC2MFP    |PC.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD2
     * |        |          |03 = SPIM_CLK
     * |        |          |04 = QSPI0_CLK
     * |        |          |05 = SC1_RST
     * |        |          |06 = I2S0_DI
     * |        |          |07 = SPI1_MOSI
     * |        |          |08 = UART2_nCTS
     * |        |          |09 = I2C0_SMBSUS
     * |        |          |10 = CAN1_RXD
     * |        |          |11 = UART3_RXD
     * |        |          |12 = EPWM1_CH3
     * |        |          |13 = CCAP_DATA2
     * |        |          |14 = QSPI1_MOSI0
     * |        |          |15 = I2C3_SDA
     * |        |          |16 = HBI_nRESET
     * |        |          |17 = PSIO0_CH3
     * |        |          |18 = KPI_ROW3
     * |        |          |19 = SPI7_CLK
     * |        |          |20 = BMC23
     * |[28:24] |PC3MFP    |PC.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD3
     * |        |          |03 = SPIM_SS
     * |        |          |04 = QSPI0_SS
     * |        |          |05 = SC1_PWR
     * |        |          |06 = I2S0_MCLK
     * |        |          |07 = SPI1_MISO
     * |        |          |08 = UART2_nRTS
     * |        |          |09 = I2C0_SMBAL
     * |        |          |10 = CAN1_TXD
     * |        |          |11 = UART3_TXD
     * |        |          |12 = EPWM1_CH2
     * |        |          |13 = CCAP_DATA3
     * |        |          |14 = QSPI1_MISO0
     * |        |          |15 = I2C3_SCL
     * |        |          |16 = HBI_nCS
     * |        |          |17 = PSIO0_CH2
     * |        |          |18 = KPI_ROW2
     * |        |          |19 = SPI7_SS
     * |        |          |20 = BMC22
     * @var SYS_T::GPC_MFP1
     * Offset: 0x524  GPIOC Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PC4MFP    |PC.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD4
     * |        |          |03 = SPIM_D3
     * |        |          |04 = QSPI0_MOSI1
     * |        |          |05 = SC1_nCD
     * |        |          |06 = I2S0_BCLK
     * |        |          |07 = SPI1_I2SMCLK
     * |        |          |08 = UART2_RXD
     * |        |          |09 = I2C1_SDA
     * |        |          |10 = CAN0_RXD
     * |        |          |11 = UART4_RXD
     * |        |          |12 = EPWM1_CH1
     * |        |          |13 = CCAP_DATA4
     * |        |          |14 = QSPI1_CLK
     * |        |          |15 = I2C3_SMBSUS
     * |        |          |16 = HBI_CK
     * |        |          |17 = PSIO0_CH1
     * |        |          |18 = KPI_ROW1
     * |        |          |20 = BMC21
     * |[12:8]  |PC5MFP    |PC.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD5
     * |        |          |03 = SPIM_D2
     * |        |          |04 = QSPI0_MISO1
     * |        |          |08 = UART2_TXD
     * |        |          |09 = I2C1_SCL
     * |        |          |10 = CAN0_TXD
     * |        |          |11 = UART4_TXD
     * |        |          |12 = EPWM1_CH0
     * |        |          |13 = CCAP_DATA5
     * |        |          |14 = QSPI1_SS
     * |        |          |15 = I2C3_SMBAL
     * |        |          |16 = HBI_nCK
     * |        |          |17 = PSIO0_CH0
     * |        |          |18 = KPI_ROW0
     * |        |          |20 = BMC20
     * |[20:16] |PC6MFP    |PC.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD8
     * |        |          |03 = EMAC0_RMII_RXD1
     * |        |          |04 = SPI1_MOSI
     * |        |          |05 = UART4_RXD
     * |        |          |06 = SC2_RST
     * |        |          |07 = UART0_nRTS
     * |        |          |08 = I2C1_SMBSUS
     * |        |          |09 = UART6_RXD
     * |        |          |10 = ACMP3_WLAT
     * |        |          |11 = EPWM1_CH3
     * |        |          |12 = BPWM1_CH1
     * |        |          |13 = CAN3_RXD
     * |        |          |14 = TM1
     * |        |          |15 = INT2
     * |        |          |18 = KPI_COL2
     * |        |          |19 = SPI6_MOSI
     * |        |          |20 = BMC25
     * |[28:24] |PC7MFP    |PC.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD9
     * |        |          |03 = EMAC0_RMII_RXD0
     * |        |          |04 = SPI1_MISO
     * |        |          |05 = UART4_TXD
     * |        |          |06 = SC2_PWR
     * |        |          |07 = UART0_nCTS
     * |        |          |08 = I2C1_SMBAL
     * |        |          |09 = UART6_TXD
     * |        |          |10 = ACMP2_WLAT
     * |        |          |11 = EPWM1_CH2
     * |        |          |12 = BPWM1_CH0
     * |        |          |13 = CAN3_TXD
     * |        |          |14 = TM0
     * |        |          |15 = INT3
     * |        |          |18 = KPI_COL3
     * |        |          |19 = SPI6_MISO
     * |        |          |20 = BMC24
     * @var SYS_T::GPC_MFP2
     * Offset: 0x528  GPIOC Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PC8MFP    |PC.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR16
     * |        |          |03 = EMAC0_RMII_REFCLK
     * |        |          |04 = I2C0_SDA
     * |        |          |05 = UART4_nCTS
     * |        |          |08 = UART1_RXD
     * |        |          |11 = EPWM1_CH1
     * |        |          |12 = BPWM1_CH4
     * |        |          |18 = KPI_COL4
     * |[12:8]  |PC9MFP    |PC.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC2_CH10, ACMP3_P1
     * |        |          |02 = EBI_ADR7
     * |        |          |05 = UART6_nCTS
     * |        |          |06 = SPI3_SS
     * |        |          |07 = UART3_RXD
     * |        |          |09 = CAN1_RXD
     * |        |          |10 = I2C4_SMBSUS
     * |        |          |12 = EPWM1_CH3
     * |        |          |14 = EADC1_ST
     * |[20:16] |PC10MFP   |PC.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC2_CH11, ACMP3_P2
     * |        |          |02 = EBI_ADR6
     * |        |          |05 = UART6_nRTS
     * |        |          |06 = SPI3_CLK
     * |        |          |07 = UART3_TXD
     * |        |          |09 = CAN1_TXD
     * |        |          |10 = I2C4_SMBAL
     * |        |          |11 = ECAP1_IC0
     * |        |          |12 = EPWM1_CH2
     * |        |          |14 = EADC1_ST
     * |[28:24] |PC11MFP   |PC.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC2_CH12, ACMP3_P3
     * |        |          |02 = EBI_ADR5
     * |        |          |03 = UART0_RXD
     * |        |          |04 = I2C0_SDA
     * |        |          |05 = UART6_RXD
     * |        |          |06 = SPI3_MOSI
     * |        |          |10 = I2C4_SDA
     * |        |          |11 = ECAP1_IC1
     * |        |          |12 = EPWM1_CH1
     * |        |          |14 = ACMP1_O
     * @var SYS_T::GPC_MFP3
     * Offset: 0x52C  GPIOC Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PC12MFP   |PC.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC2_CH13
     * |        |          |02 = EBI_ADR4
     * |        |          |03 = UART0_TXD
     * |        |          |04 = I2C0_SCL
     * |        |          |05 = UART6_TXD
     * |        |          |06 = SPI3_MISO
     * |        |          |09 = SC0_nCD
     * |        |          |10 = I2C4_SCL
     * |        |          |11 = ECAP1_IC2
     * |        |          |12 = EPWM1_CH0
     * |        |          |14 = ACMP0_O
     * |[12:8]  |PC13MFP   |PC.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH3, EADC2_CH3
     * |        |          |02 = EBI_ADR10
     * |        |          |03 = SC2_nCD
     * |        |          |04 = SPI2_I2SMCLK
     * |        |          |05 = CAN1_TXD
     * |        |          |06 = USCI0_CTL0
     * |        |          |07 = UART2_TXD
     * |        |          |08 = UART8_nCTS
     * |        |          |09 = BPWM0_CH4
     * |        |          |13 = CLKO
     * |        |          |14 = EADC0_ST
     * |        |          |19 = SPI9_SS
     * |[20:16] |PC14MFP   |PC.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD11
     * |        |          |03 = SC1_nCD
     * |        |          |04 = SPI0_I2SMCLK
     * |        |          |05 = USCI0_CTL0
     * |        |          |06 = QSPI0_CLK
     * |        |          |10 = TRACE_SWO
     * |        |          |11 = EPWM0_SYNC_IN
     * |        |          |12 = ETMC_TRACE_CLK (for M460HD)
     * |        |          |13 = TM1
     * |        |          |14 = USB_VBUS_ST
     * |        |          |15 = HSUSB_VBUS_ST (for M460HD)
     * |        |          |19 = SPI9_MOSI
     * |        |          |20 = BMC26
     * |[28:24] |PC15MFP   |PC.15 Multi-function Pin Selection
     * @var SYS_T::GPD_MFP0
     * Offset: 0x530  GPIOD Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PD0MFP    |PD.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD13
     * |        |          |03 = USCI0_CLK
     * |        |          |04 = SPI0_MOSI
     * |        |          |05 = UART3_RXD
     * |        |          |06 = I2C2_SDA
     * |        |          |07 = SC2_CLK
     * |        |          |10 = I2S1_DO
     * |        |          |12 = EQEI2_A
     * |        |          |13 = ECAP2_IC1
     * |        |          |14 = TM2
     * |[12:8]  |PD1MFP    |PD.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD12
     * |        |          |03 = USCI0_DAT0
     * |        |          |04 = SPI0_MISO
     * |        |          |05 = UART3_TXD
     * |        |          |06 = I2C2_SCL
     * |        |          |07 = SC2_DAT
     * |        |          |10 = I2S1_DI
     * |        |          |12 = EQEI2_INDEX
     * |        |          |13 = ECAP2_IC0
     * |[20:16] |PD2MFP    |PD.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD11
     * |        |          |03 = USCI0_DAT1
     * |        |          |04 = SPI0_CLK
     * |        |          |05 = UART3_nCTS
     * |        |          |07 = SC2_RST
     * |        |          |09 = UART0_RXD
     * |        |          |10 = I2S1_MCLK
     * |        |          |13 = EQEI3_B
     * |[28:24] |PD3MFP    |PD.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD10
     * |        |          |03 = USCI0_CTL1
     * |        |          |04 = SPI0_SS
     * |        |          |05 = UART3_nRTS
     * |        |          |07 = SC2_PWR
     * |        |          |08 = SC1_nCD
     * |        |          |09 = UART0_TXD
     * |        |          |10 = I2S1_BCLK
     * |        |          |13 = EQEI3_A
     * @var SYS_T::GPD_MFP1
     * Offset: 0x534  GPIOD Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PD4MFP    |PD.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = USCI0_CTL0
     * |        |          |04 = I2C1_SDA
     * |        |          |05 = SPI1_SS
     * |        |          |08 = SC1_CLK
     * |        |          |14 = USB_VBUS_ST
     * |        |          |17 = PSIO0_CH7
     * |[12:8]  |PD5MFP    |PD.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |04 = I2C1_SCL
     * |        |          |05 = SPI1_CLK
     * |        |          |08 = SC1_DAT
     * |        |          |14 = ACMP1_O
     * |        |          |15 = EADC1_ST
     * |        |          |16 = HBI_D7
     * |        |          |17 = PSIO0_CH6
     * |[20:16] |PD6MFP    |PD.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD5
     * |        |          |03 = UART1_RXD
     * |        |          |04 = I2C0_SDA
     * |        |          |05 = SPI1_MOSI
     * |        |          |06 = QSPI1_MOSI0
     * |        |          |08 = SC1_RST
     * |        |          |14 = ACMP0_O
     * |        |          |15 = EADC0_ST
     * |        |          |16 = HBI_D6
     * |        |          |17 = PSIO0_CH5
     * |[28:24] |PD7MFP    |PD.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD4
     * |        |          |03 = UART1_TXD
     * |        |          |04 = I2C0_SCL
     * |        |          |05 = SPI1_MISO
     * |        |          |06 = QSPI1_MISO0
     * |        |          |07 = CCAP_HSYNC
     * |        |          |08 = SC1_PWR
     * |        |          |16 = HBI_D5
     * |        |          |17 = PSIO0_CH4
     * @var SYS_T::GPD_MFP2
     * Offset: 0x538  GPIOD Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PD8MFP    |PD.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD6
     * |        |          |03 = I2C2_SDA
     * |        |          |04 = UART2_nRTS
     * |        |          |05 = UART7_RXD
     * |        |          |06 = CAN2_RXD
     * |        |          |17 = PSIO0_CH3
     * |[12:8]  |PD9MFP    |PD.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD7
     * |        |          |03 = I2C2_SCL
     * |        |          |04 = UART2_nCTS
     * |        |          |05 = UART7_TXD
     * |        |          |06 = CAN2_TXD
     * |        |          |17 = PSIO0_CH2
     * |[20:16] |PD10MFP   |PD.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH0, EADC2_CH0
     * |        |          |02 = EBI_nCS2
     * |        |          |03 = UART1_RXD
     * |        |          |04 = CAN0_RXD
     * |        |          |08 = UART8_RXD
     * |        |          |10 = EQEI0_B
     * |        |          |11 = ECAP3_IC2
     * |        |          |15 = INT7
     * |        |          |19 = SPI9_MOSI
     * |[28:24] |PD11MFP   |PD.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH1, EADC2_CH1
     * |        |          |02 = EBI_nCS1
     * |        |          |03 = UART1_TXD
     * |        |          |04 = CAN0_TXD
     * |        |          |08 = UART8_TXD
     * |        |          |10 = EQEI0_A
     * |        |          |11 = ECAP3_IC1
     * |        |          |15 = INT6
     * |        |          |19 = SPI9_MISO
     * @var SYS_T::GPD_MFP3
     * Offset: 0x53C  GPIOD Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PD12MFP   |PD.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |01 = EADC1_CH2, EADC2_CH2
     * |        |          |02 = EBI_nCS0
     * |        |          |05 = CAN1_RXD
     * |        |          |07 = UART2_RXD
     * |        |          |08 = UART8_nRTS
     * |        |          |09 = BPWM0_CH5
     * |        |          |10 = EQEI0_INDEX
     * |        |          |11 = ECAP3_IC0
     * |        |          |13 = CLKO
     * |        |          |14 = EADC0_ST
     * |        |          |15 = INT5
     * |        |          |19 = SPI9_CLK
     * |[12:8]  |PD13MFP   |PD.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD10
     * |        |          |03 = SD0_nCD
     * |        |          |04 = SPI0_I2SMCLK
     * |        |          |05 = SPI1_I2SMCLK
     * |        |          |06 = QSPI1_MOSI0
     * |        |          |07 = SC2_nCD
     * |        |          |08 = SD1_CLK
     * |        |          |09 = UART6_RXD
     * |        |          |10 = I2S1_LRCK
     * |        |          |11 = BPWM0_CH0
     * |        |          |12 = EQEI2_B
     * |        |          |13 = ECAP2_IC2
     * |        |          |14 = CLKO
     * |        |          |15 = EADC0_ST
     * |        |          |19 = QSPI1_MOSI1 (for M460LD)
     * |[20:16] |PD14MFP   |PD.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS0
     * |        |          |03 = SPI3_I2SMCLK
     * |        |          |04 = SC1_nCD
     * |        |          |05 = SPI0_I2SMCLK
     * |        |          |10 = I2S1_BCLK
     * |        |          |11 = EPWM0_CH4
     * |[28:24] |PD15MFP   |PD.15 Multi-function Pin Selection
     * @var SYS_T::GPE_MFP0
     * Offset: 0x540  GPIOE Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PE0MFP    |PE.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD11
     * |        |          |03 = QSPI0_MOSI0
     * |        |          |04 = SC2_CLK
     * |        |          |05 = I2S0_MCLK
     * |        |          |06 = SPI1_MOSI
     * |        |          |07 = UART3_RXD
     * |        |          |08 = I2C1_SDA
     * |        |          |09 = UART4_nRTS
     * |        |          |10 = UART8_RXD
     * |[12:8]  |PE1MFP    |PE.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD10
     * |        |          |03 = QSPI0_MISO0
     * |        |          |04 = SC2_DAT
     * |        |          |05 = I2S0_BCLK
     * |        |          |06 = SPI1_MISO
     * |        |          |07 = UART3_TXD
     * |        |          |08 = I2C1_SCL
     * |        |          |09 = UART4_nCTS
     * |        |          |10 = UART8_TXD
     * |[20:16] |PE2MFP    |PE.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ALE
     * |        |          |03 = SD0_DAT0
     * |        |          |04 = SPIM_MOSI
     * |        |          |05 = SPI3_MOSI
     * |        |          |06 = SC0_CLK
     * |        |          |07 = USCI0_CLK
     * |        |          |08 = UART6_nCTS
     * |        |          |09 = UART7_RXD
     * |        |          |10 = UART8_nRTS
     * |        |          |11 = EQEI0_B
     * |        |          |12 = EPWM0_CH5
     * |        |          |13 = BPWM0_CH0
     * |[28:24] |PE3MFP    |PE.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_MCLK
     * |        |          |03 = SD0_DAT1
     * |        |          |04 = SPIM_MISO
     * |        |          |05 = SPI3_MISO
     * |        |          |06 = SC0_DAT
     * |        |          |07 = USCI0_DAT0
     * |        |          |08 = UART6_nRTS
     * |        |          |09 = UART7_TXD
     * |        |          |10 = UART8_nCTS
     * |        |          |11 = EQEI0_A
     * |        |          |12 = EPWM0_CH4
     * |        |          |13 = BPWM0_CH1
     * @var SYS_T::GPE_MFP1
     * Offset: 0x544  GPIOE Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PE4MFP    |PE.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nWR
     * |        |          |03 = SD0_DAT2
     * |        |          |04 = SPIM_CLK
     * |        |          |05 = SPI3_CLK
     * |        |          |06 = SC0_RST
     * |        |          |07 = USCI0_DAT1
     * |        |          |08 = UART6_RXD
     * |        |          |09 = UART7_nCTS
     * |        |          |10 = UART9_RXD
     * |        |          |11 = EQEI0_INDEX
     * |        |          |12 = EPWM0_CH3
     * |        |          |13 = BPWM0_CH2
     * |        |          |17 = PSIO0_CH3
     * |[12:8]  |PE5MFP    |PE.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nRD
     * |        |          |03 = SD0_DAT3
     * |        |          |04 = SPIM_SS
     * |        |          |05 = SPI3_SS
     * |        |          |06 = SC0_PWR
     * |        |          |07 = USCI0_CTL1
     * |        |          |08 = UART6_TXD
     * |        |          |09 = UART7_nRTS
     * |        |          |10 = UART9_TXD
     * |        |          |11 = EQEI1_B
     * |        |          |12 = EPWM0_CH2
     * |        |          |13 = BPWM0_CH3
     * |        |          |17 = PSIO0_CH2
     * |[20:16] |PE6MFP    |PE.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SD0_CLK
     * |        |          |04 = SPIM_D3
     * |        |          |05 = SPI3_I2SMCLK
     * |        |          |06 = SC0_nCD
     * |        |          |07 = USCI0_CTL0
     * |        |          |08 = UART5_RXD
     * |        |          |09 = CAN1_RXD
     * |        |          |10 = UART9_nRTS
     * |        |          |11 = EQEI1_A
     * |        |          |12 = EPWM0_CH1
     * |        |          |13 = BPWM0_CH4
     * |        |          |14 = ACMP3_O
     * |        |          |17 = PSIO0_CH1
     * |[28:24] |PE7MFP    |PE.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SD0_CMD
     * |        |          |04 = SPIM_D2
     * |        |          |08 = UART5_TXD
     * |        |          |09 = CAN1_TXD
     * |        |          |10 = UART9_nCTS
     * |        |          |11 = EQEI1_INDEX
     * |        |          |12 = EPWM0_CH0
     * |        |          |13 = BPWM0_CH5
     * |        |          |14 = ACMP2_O
     * |        |          |17 = PSIO0_CH0
     * @var SYS_T::GPE_MFP2
     * Offset: 0x548  GPIOE Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PE8MFP    |PE.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR10
     * |        |          |03 = EMAC0_RMII_MDC
     * |        |          |04 = I2S0_BCLK
     * |        |          |05 = SPI2_CLK
     * |        |          |07 = UART2_TXD
     * |        |          |10 = EPWM0_CH0
     * |        |          |11 = EPWM0_BRAKE0
     * |        |          |12 = ECAP0_IC0
     * |        |          |13 = EQEI2_INDEX
     * |        |          |14 = TRACE_DATA3
     * |        |          |15 = ECAP3_IC0
     * |[12:8]  |PE9MFP    |PE.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR11
     * |        |          |03 = EMAC0_RMII_MDIO
     * |        |          |04 = I2S0_MCLK
     * |        |          |05 = SPI2_MISO
     * |        |          |07 = UART2_RXD
     * |        |          |10 = EPWM0_CH1
     * |        |          |11 = EPWM0_BRAKE1
     * |        |          |12 = ECAP0_IC1
     * |        |          |13 = EQEI2_A
     * |        |          |14 = TRACE_DATA2
     * |        |          |15 = ECAP3_IC1
     * |[20:16] |PE10MFP   |PE.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR12
     * |        |          |03 = EMAC_RMII_TXD0
     * |        |          |04 = I2S0_DI
     * |        |          |05 = SPI2_MOSI
     * |        |          |07 = UART3_TXD
     * |        |          |10 = EPWM0_CH2
     * |        |          |11 = EPWM1_BRAKE0
     * |        |          |12 = ECAP0_IC2
     * |        |          |13 = EQEI2_B
     * |        |          |14 = TRACE_DATA1
     * |        |          |15 = ECAP3_IC2
     * |[28:24] |PE11MFP   |PE.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR13
     * |        |          |03 = EMAC0_RMII_TXD1
     * |        |          |04 = I2S0_DO
     * |        |          |05 = SPI2_SS
     * |        |          |07 = UART3_RXD
     * |        |          |08 = UART1_nCTS
     * |        |          |10 = EPWM0_CH3
     * |        |          |11 = EPWM1_BRAKE1
     * |        |          |13 = ECAP1_IC2
     * |        |          |14 = TRACE_DATA0
     * |        |          |18 = KPI_COL7
     * @var SYS_T::GPE_MFP3
     * Offset: 0x54C  GPIOE Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PE12MFP   |PE.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR14
     * |        |          |03 = EMAC0_RMII_TXEN
     * |        |          |04 = I2S0_LRCK
     * |        |          |05 = SPI2_I2SMCLK
     * |        |          |08 = UART1_nRTS
     * |        |          |10 = EPWM0_CH4
     * |        |          |13 = ECAP1_IC1
     * |        |          |14 = TRACE_CLK
     * |        |          |18 = KPI_COL6
     * |[12:8]  |PE13MFP   |PE.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR15
     * |        |          |03 = EMAC0_PPS
     * |        |          |04 = I2C0_SCL
     * |        |          |05 = UART4_nRTS
     * |        |          |08 = UART1_TXD
     * |        |          |10 = EPWM0_CH5
     * |        |          |11 = EPWM1_CH0
     * |        |          |12 = BPWM1_CH5
     * |        |          |13 = ECAP1_IC0
     * |        |          |14 = TRACE_SWO
     * |        |          |18 = KPI_COL5
     * |[20:16] |PE14MFP   |PE.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD8
     * |        |          |03 = UART2_TXD
     * |        |          |04 = CAN0_TXD
     * |        |          |05 = SD1_nCD
     * |        |          |06 = UART6_TXD
     * |        |          |17 = PSIO0_CH0
     * |[28:24] |PE15MFP   |PE.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD9
     * |        |          |03 = UART2_RXD
     * |        |          |04 = CAN0_RXD
     * |        |          |06 = UART6_RXD
     * |        |          |17 = PSIO0_CH1
     * @var SYS_T::GPF_MFP0
     * Offset: 0x550  GPIOF Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PF0MFP    |PF.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = UART1_TXD
     * |        |          |03 = I2C1_SCL
     * |        |          |04 = UART0_TXD
     * |        |          |05 = SC1_DAT
     * |        |          |06 = I2S0_DO
     * |        |          |08 = UART2_TXD
     * |        |          |09 = I2C0_SCL
     * |        |          |10 = CAN2_TXD
     * |        |          |11 = EPWM1_CH4
     * |        |          |12 = BPWM1_CH0
     * |        |          |13 = ACMP0_O
     * |        |          |14 = ICE_DAT
     * |        |          |15 = EADC0_ST
     * |        |          |19 = QSPI1_MISO0 (for M460LD)
     * |[12:8]  |PF1MFP    |PF.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = UART1_RXD
     * |        |          |03 = I2C1_SDA
     * |        |          |04 = UART0_RXD
     * |        |          |05 = SC1_CLK
     * |        |          |06 = I2S0_LRCK
     * |        |          |08 = UART2_RXD
     * |        |          |09 = I2C0_SDA
     * |        |          |10 = CAN2_RXD
     * |        |          |11 = EPWM1_CH5
     * |        |          |12 = BPWM1_CH1
     * |        |          |13 = ACMP1_O
     * |        |          |14 = ICE_CLK
     * |        |          |15 = EADC1_ST
     * |        |          |19 = QSPI1_MOSI0 (for M460LD)
     * |[20:16] |PF2MFP    |PF.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS1
     * |        |          |03 = UART0_RXD
     * |        |          |04 = I2C0_SDA
     * |        |          |05 = QSPI0_CLK
     * |        |          |07 = UART9_RXD
     * |        |          |10 = XT1_OUT
     * |        |          |11 = BPWM1_CH1
     * |        |          |12 = I2C4_SMBSUS
     * |        |          |13 = ACMP3_O
     * |        |          |20 = BMC13
     * |[28:24] |PF3MFP    |PF.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS0
     * |        |          |03 = UART0_TXD
     * |        |          |04 = I2C0_SCL
     * |        |          |07 = UART9_TXD
     * |        |          |10 = XT1_IN
     * |        |          |11 = BPWM1_CH0
     * |        |          |12 = I2C4_SMBAL
     * |        |          |13 = ACMP2_O
     * |        |          |15 = EADC2_ST
     * |        |          |20 = BMC12
     * @var SYS_T::GPF_MFP1
     * Offset: 0x554  GPIOF Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PF4MFP    |PF.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = UART2_TXD
     * |        |          |03 = EBI_AD0
     * |        |          |04 = UART2_nRTS
     * |        |          |07 = EPWM0_CH1
     * |        |          |08 = BPWM0_CH5
     * |        |          |10 = X32_OUT
     * |        |          |11 = EADC1_ST
     * |        |          |12 = I2C4_SDA
     * |        |          |13 = EQEI2_B
     * |        |          |19 = SPI5_MISO
     * |        |          |20 = BMC11
     * |[12:8]  |PF5MFP    |PF.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = UART2_RXD
     * |        |          |03 = EBI_AD1
     * |        |          |04 = UART2_nCTS
     * |        |          |07 = EPWM0_CH0
     * |        |          |08 = BPWM0_CH4
     * |        |          |09 = EPWM0_SYNC_OUT
     * |        |          |10 = X32_IN
     * |        |          |11 = EADC0_ST
     * |        |          |12 = I2C4_SCL
     * |        |          |13 = EQEI2_A
     * |        |          |19 = SPI5_MOSI
     * |        |          |20 = BMC10
     * |[20:16] |PF6MFP    |PF.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR19
     * |        |          |03 = SC0_CLK
     * |        |          |04 = I2S0_LRCK
     * |        |          |05 = SPI0_MOSI
     * |        |          |06 = UART4_RXD
     * |        |          |07 = EBI_nCS0
     * |        |          |08 = CAN2_RXD
     * |        |          |09 = SPI3_I2SMCLK
     * |        |          |10 = TAMPER0
     * |        |          |13 = EQEI2_INDEX
     * |        |          |14 = TRACE_SWO
     * |        |          |19 = SPI5_CLK
     * |[28:24] |PF7MFP    |PF.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR18
     * |        |          |03 = SC0_DAT
     * |        |          |04 = I2S0_DO
     * |        |          |05 = SPI0_MISO
     * |        |          |06 = UART4_TXD
     * |        |          |07 = CCAP_DATA0
     * |        |          |08 = CAN2_TXD
     * |        |          |10 = TAMPER1
     * |        |          |19 = SPI5_SS

     * @var SYS_T::GPF_MFP2
     * Offset: 0x558  GPIOF Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PF8MFP    |PF.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR17
     * |        |          |03 = SC0_RST
     * |        |          |04 = I2S0_DI
     * |        |          |05 = SPI0_CLK
     * |        |          |06 = UART5_nCTS
     * |        |          |07 = CCAP_DATA1
     * |        |          |08 = CAN1_RXD
     * |        |          |10 = TAMPER2
     * |        |          |11 = UART9_RXD
     * |[12:8]  |PF9MFP    |PF.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR16
     * |        |          |03 = SC0_PWR
     * |        |          |04 = I2S0_MCLK
     * |        |          |05 = SPI0_SS
     * |        |          |06 = UART5_nRTS
     * |        |          |07 = CCAP_DATA2
     * |        |          |08 = CAN1_TXD
     * |        |          |10 = TAMPER3
     * |        |          |11 = UART9_TXD
     * |[20:16] |PF10MFP   |PF.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR15
     * |        |          |03 = SC0_nCD
     * |        |          |04 = I2S0_BCLK
     * |        |          |05 = SPI0_I2SMCLK
     * |        |          |06 = UART5_RXD
     * |        |          |07 = CCAP_DATA3
     * |        |          |08 = CAN3_RXD
     * |        |          |10 = TAMPER4
     * |        |          |11 = UART9_nRTS
     * |[28:24] |PF11MFP   |PF.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR14
     * |        |          |03 = SPI2_MOSI
     * |        |          |06 = UART5_TXD
     * |        |          |07 = CCAP_DATA4
     * |        |          |08 = CAN3_TXD
     * |        |          |10 = TAMPER5
     * |        |          |11 = UART9_nCTS
     * |        |          |13 = TM3
     * @var SYS_T::GPF_MFP3
     * Offset: 0x55C  GPIOF Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PF12MFP   |PF.12 Multi-function Pin Selection
     * |[12:8]  |PF13MFP   |PF.13 Multi-function Pin Selection
     * |[20:16] |PF14MFP   |PF.14 Multi-function Pin Selection
     * |[28:24] |PF15MFP   |PF.15 Multi-function Pin Selection
     * @var SYS_T::GPG_MFP0
     * Offset: 0x560  GPIOG Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PG0MFP    |PG.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR8
     * |        |          |04 = I2C0_SCL
     * |        |          |05 = I2C1_SMBAL
     * |        |          |06 = UART2_RXD
     * |        |          |07 = CAN1_TXD
     * |        |          |08 = UART1_TXD
     * |        |          |09 = I2C3_SCL
     * |[12:8]  |PG1MFP    |PG.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR9
     * |        |          |03 = SPI2_I2SMCLK
     * |        |          |04 = I2C0_SDA
     * |        |          |05 = I2C1_SMBSUS
     * |        |          |06 = UART2_TXD
     * |        |          |07 = CAN1_RXD
     * |        |          |08 = UART1_RXD
     * |        |          |09 = I2C3_SDA
     * |[20:16] |PG2MFP    |PG.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR11
     * |        |          |03 = SPI2_SS
     * |        |          |04 = I2C0_SMBAL
     * |        |          |05 = I2C1_SCL
     * |        |          |07 = CCAP_DATA7
     * |        |          |09 = I2C3_SMBAL
     * |        |          |13 = TM0
     * |[28:24] |PG3MFP    |PG.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR12
     * |        |          |03 = SPI2_CLK
     * |        |          |04 = I2C0_SMBSUS
     * |        |          |05 = I2C1_SDA
     * |        |          |07 = CCAP_DATA6
     * |        |          |09 = I2C3_SMBSUS
     * |        |          |13 = TM1
     * @var SYS_T::GPG_MFP1
     * Offset: 0x564  GPIOG Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PG4MFP    |PG.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR13
     * |        |          |03 = SPI2_MISO
     * |        |          |07 = CCAP_DATA5
     * |        |          |13 = TM2
     * |[12:8]  |PG5MFP    |PG.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS1
     * |        |          |03 = SPI3_SS
     * |        |          |04 = SC1_PWR
     * |        |          |08 = I2C3_SMBAL
     * |        |          |10 = I2S1_MCLK
     * |        |          |11 = EPWM0_CH3
     * |[20:16] |PG6MFP    |PG.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS2
     * |        |          |03 = SPI3_CLK
     * |        |          |04 = SC1_RST
     * |        |          |08 = I2C3_SMBSUS
     * |        |          |10 = I2S1_DI
     * |        |          |11 = EPWM0_CH2
     * |[28:24] |PG7MFP    |PG.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nWRL
     * |        |          |03 = SPI3_MISO
     * |        |          |04 = SC1_DAT
     * |        |          |08 = I2C3_SCL
     * |        |          |10 = I2S1_DO
     * |        |          |11 = EPWM0_CH1
     * @var SYS_T::GPG_MFP2
     * Offset: 0x568  GPIOG Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PG8MFP    |PG.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nWRH
     * |        |          |03 = SPI3_MOSI
     * |        |          |04 = SC1_CLK
     * |        |          |08 = I2C3_SDA
     * |        |          |10 = I2S1_LRCK
     * |        |          |11 = EPWM0_CH0
     * |[12:8]  |PG9MFP    |PG.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD0
     * |        |          |03 = SD1_DAT3
     * |        |          |04 = SPIM_D2
     * |        |          |05 = QSPI1_MISO1
     * |        |          |07 = CCAP_PIXCLK
     * |        |          |08 = I2C4_SCL
     * |        |          |09 = ECAP2_IC0
     * |        |          |12 = BPWM0_CH5
     * |        |          |16 = HBI_D4
     * |        |          |19 = SPI8_SS
     * |        |          |20 = BMC16
     * |[20:16] |PG10MFP   |PG.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD1
     * |        |          |03 = SD1_DAT2
     * |        |          |04 = SPIM_D3
     * |        |          |05 = QSPI1_MOSI1
     * |        |          |07 = CCAP_SCLK
     * |        |          |08 = I2C4_SDA
     * |        |          |09 = ECAP2_IC1
     * |        |          |12 = BPWM0_CH4
     * |        |          |16 = HBI_D3
     * |        |          |19 = SPI8_CLK
     * |        |          |20 = BMC17
     * |[28:24] |PG11MFP   |PG.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD2
     * |        |          |03 = SD1_DAT1
     * |        |          |04 = SPIM_SS
     * |        |          |05 = QSPI1_SS
     * |        |          |06 = UART7_TXD
     * |        |          |07 = CCAP_SFIELD
     * |        |          |08 = I2C4_SMBAL
     * |        |          |09 = ECAP2_IC2
     * |        |          |12 = BPWM0_CH3
     * |        |          |16 = HBI_D0
     * |        |          |19 = SPI8_MOSI
     * |        |          |20 = BMC18
     * @var SYS_T::GPG_MFP3
     * Offset: 0x56C  GPIOG Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PG12MFP   |PG.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD3
     * |        |          |03 = SD1_DAT0
     * |        |          |04 = SPIM_CLK
     * |        |          |05 = QSPI1_CLK
     * |        |          |06 = UART7_RXD
     * |        |          |07 = CCAP_VSYNC
     * |        |          |08 = I2C4_SMBSUS
     * |        |          |12 = BPWM0_CH2
     * |        |          |16 = HBI_D1
     * |        |          |19 = SPI8_MISO
     * |        |          |20 = BMC19
     * |[12:8]  |PG13MFP   |PG.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD4
     * |        |          |03 = SD1_CMD
     * |        |          |04 = SPIM_MISO
     * |        |          |05 = QSPI1_MISO0
     * |        |          |06 = UART6_TXD
     * |        |          |07 = CCAP_HSYNC
     * |        |          |12 = BPWM0_CH1
     * |        |          |16 = HBI_D5
     * |[20:16] |PG14MFP   |PG.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD5
     * |        |          |03 = SD1_CLK
     * |        |          |04 = SPIM_MOSI
     * |        |          |05 = QSPI1_MOSI0
     * |        |          |06 = UART6_RXD
     * |        |          |12 = BPWM0_CH0
     * |        |          |16 = HBI_D6
     * |[28:24] |PG15MFP   |PG.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SD1_nCD
     * |        |          |14 = CLKO
     * |        |          |15 = EADC0_ST
     * |        |          |16 = HBI_D7
     * |        |          |19 = QSPI1_MISO1 (for M460LD)
     * @var SYS_T::GPH_MFP0
     * Offset: 0x570  GPIOH Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PH0MFP    |PH.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR7
     * |        |          |04 = UART5_TXD
     * |        |          |13 = TM0_EXT
     * |[12:8]  |PH1MFP    |PH.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR6
     * |        |          |04 = UART5_RXD
     * |        |          |13 = TM1_EXT
     * |[20:16] |PH2MFP    |PH.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR5
     * |        |          |04 = UART5_nRTS
     * |        |          |05 = UART4_TXD
     * |        |          |06 = I2C0_SCL
     * |        |          |13 = TM2_EXT
     * |[28:24] |PH3MFP    |PH.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR4
     * |        |          |03 = SPI1_I2SMCLK
     * |        |          |04 = UART5_nCTS
     * |        |          |05 = UART4_RXD
     * |        |          |06 = I2C0_SDA
     * |        |          |13 = TM3_EXT
     * @var SYS_T::GPH_MFP1
     * Offset: 0x574  GPIOH Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PH4MFP    |PH.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR3
     * |        |          |03 = SPI1_MISO
     * |        |          |04 = UART7_nRTS
     * |        |          |05 = UART6_TXD
     * |[12:8]  |PH5MFP    |PH.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR2
     * |        |          |03 = SPI1_MOSI
     * |        |          |04 = UART7_nCTS
     * |        |          |05 = UART6_RXD
     * |[20:16] |PH6MFP    |PH.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR1
     * |        |          |03 = SPI1_CLK
     * |        |          |04 = UART7_TXD
     * |        |          |07 = UART9_nCTS
     * |[28:24] |PH7MFP    |PH.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ADR0
     * |        |          |03 = SPI1_SS
     * |        |          |04 = UART7_RXD
     * |        |          |07 = UART9_nRTS
     * @var SYS_T::GPH_MFP2
     * Offset: 0x578  GPIOH Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PH8MFP    |PH.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD12
     * |        |          |03 = QSPI0_CLK
     * |        |          |04 = SC2_PWR
     * |        |          |05 = I2S0_DI
     * |        |          |06 = SPI1_CLK
     * |        |          |07 = UART3_nRTS
     * |        |          |08 = I2C1_SMBAL
     * |        |          |09 = I2C2_SCL
     * |        |          |10 = UART1_TXD
     * |        |          |13 = UART9_nCTS
     * |[12:8]  |PH9MFP    |PH.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD13
     * |        |          |03 = QSPI0_SS
     * |        |          |04 = SC2_RST
     * |        |          |05 = I2S0_DO
     * |        |          |06 = SPI1_SS
     * |        |          |07 = UART3_nCTS
     * |        |          |08 = I2C1_SMBSUS
     * |        |          |09 = I2C2_SDA
     * |        |          |10 = UART1_RXD
     * |        |          |13 = UART9_nRTS
     * |[20:16] |PH10MFP   |PH.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD14
     * |        |          |03 = QSPI0_MISO1
     * |        |          |04 = SC2_nCD
     * |        |          |05 = I2S0_LRCK
     * |        |          |06 = SPI1_I2SMCLK
     * |        |          |07 = UART4_TXD
     * |        |          |08 = UART0_TXD
     * |        |          |13 = UART9_TXD
     * |[28:24] |PH11MFP   |PH.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD15
     * |        |          |03 = QSPI0_MOSI1
     * |        |          |07 = UART4_RXD
     * |        |          |08 = UART0_RXD
     * |        |          |11 = EPWM0_CH5
     * |        |          |13 = UART9_RXD
     * @var SYS_T::GPH_MFP3
     * Offset: 0x57C  GPIOH Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PH12MFP   |PH.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD0
     * |        |          |03 = UART9_TXD
     * |        |          |06 = QSPI1_MISO1
     * |        |          |07 = CCAP_PIXCLK
     * |        |          |10 = CAN3_TXD
     * |        |          |16 = HBI_nCK
     * |[12:8]  |PH13MFP   |PH.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD1
     * |        |          |03 = UART9_RXD
     * |        |          |06 = QSPI1_MOSI1
     * |        |          |07 = CCAP_SCLK
     * |        |          |10 = CAN3_RXD
     * |        |          |16 = HBI_CK
     * |[20:16] |PH14MFP   |PH.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD2
     * |        |          |06 = QSPI1_SS
     * |        |          |07 = CCAP_SFIELD
     * |        |          |16 = HBI_RWDS
     * |[28:24] |PH15MFP   |PH.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD3
     * |        |          |06 = QSPI1_CLK
     * |        |          |07 = CCAP_VSYNC
     * |        |          |16 = HBI_D4
     * @var SYS_T::GPI_MFP0
     * Offset: 0x580  GPIOI Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PI0MFP    |PI.0 Multi-function Pin Selection
     * |[12:8]  |PI1MFP    |PI.1 Multi-function Pin Selection
     * |[20:16] |PI2MFP    |PI.2 Multi-function Pin Selection
     * |[28:24] |PI3MFP    |PI.3 Multi-function Pin Selection
     * @var SYS_T::GPI_MFP1
     * Offset: 0x584  GPIOI Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PI4MFP    |PI.4 Multi-function Pin Selection
     * |[12:8]  |PI5MFP    |PI.5 Multi-function Pin Selection
     * |[20:16] |PI6MFP    |PI.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |05 = SC1_nCD
     * |        |          |06 = I2S0_BCLK
     * |        |          |07 = SPI1_I2SMCLK
     * |        |          |08 = UART2_TXD
     * |        |          |09 = I2C1_SCL
     * |        |          |13 = CAN3_TXD
     * |        |          |15 = USB_VBUS_ST
     * |[28:24] |PI7MFP    |PI.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |05 = SC1_PWR
     * |        |          |06 = I2S0_MCLK
     * |        |          |07 = SPI1_MISO
     * |        |          |08 = UART2_RXD
     * |        |          |09 = I2C1_SDA
     * |        |          |13 = CAN3_RXD
     * |        |          |15 = USB_VBUS_EN
     * @var SYS_T::GPI_MFP2
     * Offset: 0x588  GPIOI Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PI8MFP    |PI.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |05 = SC1_RST
     * |        |          |06 = I2S0_DI
     * |        |          |07 = SPI1_MOSI
     * |        |          |08 = UART2_nRTS
     * |        |          |09 = I2C0_SMBAL
     * |        |          |13 = CAN2_TXD
     * |[12:8]  |PI9MFP    |PI.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |05 = SC1_DAT
     * |        |          |06 = I2S0_DO
     * |        |          |07 = SPI1_CLK
     * |        |          |08 = UART2_nCTS
     * |        |          |09 = I2C0_SMBSUS
     * |        |          |13 = CAN2_RXD
     * |[20:16] |PI10MFP   |PI.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |05 = SC1_CLK
     * |        |          |06 = I2S0_LRCK
     * |        |          |07 = SPI1_SS
     * |        |          |08 = UART2_TXD
     * |        |          |09 = I2C0_SCL
     * |        |          |13 = CAN3_TXD
     * |[28:24] |PI11MFP   |PI.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |08 = UART2_RXD
     * |        |          |09 = I2C0_SDA
     * |        |          |13 = CAN3_RXD
     * @var SYS_T::GPI_MFP3
     * Offset: 0x58C  GPIOI Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PI12MFP   |PI.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_SS
     * |        |          |04 = QSPI0_MISO1
     * |        |          |10 = CAN0_TXD
     * |        |          |11 = UART4_TXD
     * |        |          |12 = EPWM1_CH0
     * |        |          |15 = I2C3_SMBAL
     * |[12:8]  |PI13MFP   |PI.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_MISO
     * |        |          |04 = QSPI0_MOSI1
     * |        |          |10 = CAN0_RXD
     * |        |          |11 = UART4_RXD
     * |        |          |12 = EPWM1_CH1
     * |        |          |15 = I2C3_SMBSUS
     * |[20:16] |PI14MFP   |PI.14 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_D2
     * |        |          |04 = QSPI0_SS
     * |        |          |07 = UART8_nCTS
     * |        |          |10 = CAN1_TXD
     * |        |          |11 = UART3_TXD
     * |        |          |12 = EPWM1_CH2
     * |        |          |15 = I2C3_SCL
     * |[28:24] |PI15MFP   |PI.15 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_D3
     * |        |          |04 = QSPI0_CLK
     * |        |          |07 = UART8_nRTS
     * |        |          |10 = CAN1_RXD
     * |        |          |11 = UART3_RXD
     * |        |          |12 = EPWM1_CH3
     * |        |          |15 = I2C3_SDA
     * @var SYS_T::GPJ_MFP0
     * Offset: 0x590  GPIOJ Multiple Function Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PJ0MFP    |PJ.0 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_CLK
     * |        |          |04 = QSPI0_MISO0
     * |        |          |07 = UART8_TXD
     * |        |          |10 = CAN2_TXD
     * |        |          |12 = EPWM1_CH4
     * |[12:8]  |PJ1MFP    |PJ.1 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SPIM_MOSI
     * |        |          |04 = QSPI0_MOSI0
     * |        |          |07 = UART8_RXD
     * |        |          |10 = CAN2_RXD
     * |        |          |12 = EPWM1_CH5
     * |[20:16] |PJ2MFP    |PJ.2 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD5
     * |        |          |03 = UART8_nCTS
     * |        |          |06 = QSPI1_SS
     * |        |          |07 = CCAP_DATA5
     * |        |          |10 = CAN0_TXD
     * |        |          |16 = HBI_nRESET
     * |[28:24] |PJ3MFP    |PJ.3 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD4
     * |        |          |03 = UART8_nRTS
     * |        |          |06 = QSPI1_CLK
     * |        |          |07 = CCAP_DATA4
     * |        |          |10 = CAN0_RXD
     * |        |          |16 = HBI_D7
     * @var SYS_T::GPJ_MFP1
     * Offset: 0x594  GPIOJ Multiple Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PJ4MFP    |PJ.4 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD3
     * |        |          |03 = UART8_TXD
     * |        |          |06 = QSPI1_MISO0
     * |        |          |07 = CCAP_DATA3
     * |        |          |10 = CAN1_TXD
     * |        |          |16 = HBI_D2
     * |[12:8]  |PJ5MFP    |PJ.5 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD2
     * |        |          |03 = UART8_RXD
     * |        |          |06 = QSPI1_MOSI0
     * |        |          |07 = CCAP_DATA2
     * |        |          |10 = CAN1_RXD
     * |        |          |16 = HBI_D1
     * |[20:16] |PJ6MFP    |PJ.6 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD1
     * |        |          |03 = UART9_nCTS
     * |        |          |07 = CCAP_DATA1
     * |        |          |10 = CAN2_TXD
     * |        |          |16 = HBI_D0
     * |[28:24] |PJ7MFP    |PJ.7 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_AD0
     * |        |          |03 = UART9_nRTS
     * |        |          |07 = CCAP_DATA0
     * |        |          |10 = CAN2_RXD
     * |        |          |16 = HBI_nCS
     * @var SYS_T::GPJ_MFP2
     * Offset: 0x598  GPIOJ Multiple Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PJ8MFP    |PJ.8 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nRD
     * |        |          |03 = SD1_DAT3
     * |        |          |04 = SPIM_SS
     * |        |          |06 = UART7_TXD
     * |        |          |11 = CAN2_TXD
     * |        |          |12 = BPWM0_CH5
     * |[12:8]  |PJ9MFP    |PJ.9 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nWR
     * |        |          |03 = SD1_DAT2
     * |        |          |04 = SPIM_MISO
     * |        |          |06 = UART7_RXD
     * |        |          |11 = CAN2_RXD
     * |        |          |12 = BPWM0_CH4
     * |[20:16] |PJ10MFP   |PJ.10 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_MCLK
     * |        |          |03 = SD1_DAT1
     * |        |          |04 = SPIM_D2
     * |        |          |06 = UART6_TXD
     * |        |          |08 = I2C4_SCL
     * |        |          |09 = ECAP2_IC0
     * |        |          |11 = CAN0_TXD
     * |        |          |12 = BPWM0_CH3
     * |[28:24] |PJ11MFP   |PJ.11 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_ALE
     * |        |          |03 = SD1_DAT0
     * |        |          |04 = SPIM_D3
     * |        |          |06 = UART6_RXD
     * |        |          |08 = I2C4_SDA
     * |        |          |09 = ECAP2_IC1
     * |        |          |11 = CAN0_RXD
     * |        |          |12 = BPWM0_CH2
     * @var SYS_T::GPJ_MFP3
     * Offset: 0x59C  GPIOJ Multiple Function Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |PJ12MFP   |PJ.12 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |02 = EBI_nCS0
     * |        |          |03 = SD1_CMD
     * |        |          |04 = SPIM_CLK
     * |        |          |08 = I2C4_SMBAL
     * |        |          |09 = ECAP2_IC2
     * |        |          |11 = CAN1_TXD
     * |        |          |12 = BPWM0_CH1
     * |        |          |15 = HSUSB_VBUS_ST
     * |[12:8]  |PJ13MFP   |PJ.13 Multi-function Pin Selection
     * |        |          |00 = GPIO
     * |        |          |03 = SD1_CLK
     * |        |          |04 = SPIM_MOSI
     * |        |          |08 = I2C4_SMBSUS
     * |        |          |11 = CAN1_RXD
     * |        |          |12 = BPWM0_CH0
     * |        |          |15 = HSUSB_VBUS_EN
     */
    __I  uint32_t PDID;                  /*!< [0x0000] Part Device Identification Number Register                       */
    __IO uint32_t RSTSTS;                /*!< [0x0004] System Reset Status Register                                     */
    __IO uint32_t IPRST0;                /*!< [0x0008] Peripheral Reset Control Register 0                              */
    __IO uint32_t IPRST1;                /*!< [0x000c] Peripheral Reset Control Register 1                              */
    __IO uint32_t IPRST2;                /*!< [0x0010] Peripheral Reset Control Register 2                              */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t BODCTL;                /*!< [0x0018] Brown-out Detector Control Register                              */
    __IO uint32_t IVSCTL;                /*!< [0x001c] Internal Voltage Source Control Register                         */
    __IO uint32_t IPRST3;                /*!< [0x0020] Peripheral Reset Control Register 3                              */
    __IO uint32_t PORCTL;                /*!< [0x0024] Power-On-reset Controller Register                               */
    __IO uint32_t VREFCTL;               /*!< [0x0028] VREF Control Register                                            */
    __IO uint32_t USBPHY;                /*!< [0x002c] USB PHY Control Register                                         */
    __I  uint32_t RESERVE1[20];
    __IO uint32_t GPA_MFOS;              /*!< [0x0080] GPIOA Multiple Function Output Select Register                   */
    __IO uint32_t GPB_MFOS;              /*!< [0x0084] GPIOB Multiple Function Output Select Register                   */
    __IO uint32_t GPC_MFOS;              /*!< [0x0088] GPIOC Multiple Function Output Select Register                   */
    __IO uint32_t GPD_MFOS;              /*!< [0x008c] GPIOD Multiple Function Output Select Register                   */
    __IO uint32_t GPE_MFOS;              /*!< [0x0090] GPIOE Multiple Function Output Select Register                   */
    __IO uint32_t GPF_MFOS;              /*!< [0x0094] GPIOF Multiple Function Output Select Register                   */
    __IO uint32_t GPG_MFOS;              /*!< [0x0098] GPIOG Multiple Function Output Select Register                   */
    __IO uint32_t GPH_MFOS;              /*!< [0x009c] GPIOH Multiple Function Output Select Register                   */
    __IO uint32_t GPI_MFOS;              /*!< [0x00A0] GPIOI Multiple Function Output Select Register                   */
    __IO uint32_t GPJ_MFOS;              /*!< [0x00A4] GPIOJ Multiple Function Output Select Register                   */
    __I  uint32_t RESERVE2[2];
    __I  uint32_t RESERVE3[4];
    __IO uint32_t SRAM_INTCTL;           /*!< [0x00c0] System SRAM Interrupt Enable Control Register                    */
    __IO uint32_t SRAM_STATUS;           /*!< [0x00c4] System SRAM Parity Error Status Register                         */
    __I  uint32_t SRAM_ERRADDR;          /*!< [0x00c8] System SRAM Parity Check Error Address Register                  */
    __I  uint32_t RESERVE4[1];
    __IO uint32_t SRAM_BISTCTL;          /*!< [0x00d0] System SRAM BIST Test Control Register                           */
    __I  uint32_t SRAM_BISTSTS;          /*!< [0x00d4] System SRAM BIST Test Status Register                            */
    __I  uint32_t RESERVE5[3];
    __IO uint32_t HIRCTCTL;              /*!< [0x00e4] HIRC48M Trim Control Register                                    */
    __IO uint32_t HIRCTIEN;              /*!< [0x00e8] HIRC48M Trim Interrupt Enable Register                           */
    __IO uint32_t HIRCTISTS;             /*!< [0x00ec] HIRC48M Trim Interrupt Status Register                           */
    __IO uint32_t IRCTCTL;               /*!< [0x00f0] HIRC Trim Control Register                                       */
    __IO uint32_t IRCTIEN;               /*!< [0x00f4] HIRC Trim Interrupt Enable Register                              */
    __IO uint32_t IRCTISTS;              /*!< [0x00f8] HIRC Trim Interrupt Status Register                              */
    __I  uint32_t RESERVE6[1];
    __O  uint32_t REGLCTL;               /*!< [0x0100] Register Lock Control Register                                   */
    __I  uint32_t RESERVE7[58];
    __IO uint32_t PORDISAN;              /*!< [0x01ec] Analog POR Disable Control Register                              */
    __I  uint32_t RESERVE8[1];
    __I  uint32_t CSERVER;               /*!< [0x01f4] Chip Series Version Register                                     */
    __IO uint32_t PLCTL;                 /*!< [0x01f8] Power Level Control Register                                     */
    __I  uint32_t PLSTS;                 /*!< [0x01fc] Power Level Status Register                                      */
    __I  uint32_t RESERVE9[128];
    __IO uint32_t AHBMCTL;               /*!< [0x0400] AHB Bus Matrix Priority Control Register                         */
    __I  uint32_t RESERVE10[63];
    __IO uint32_t GPA_MFP0;              /*!< [0x0500] GPIOA Multiple Function Control Register 0                       */
    __IO uint32_t GPA_MFP1;              /*!< [0x0504] GPIOA Multiple Function Control Register 1                       */
    __IO uint32_t GPA_MFP2;              /*!< [0x0508] GPIOA Multiple Function Control Register 2                       */
    __IO uint32_t GPA_MFP3;              /*!< [0x050c] GPIOA Multiple Function Control Register 3                       */
    __IO uint32_t GPB_MFP0;              /*!< [0x0510] GPIOB Multiple Function Control Register 0                       */
    __IO uint32_t GPB_MFP1;              /*!< [0x0514] GPIOB Multiple Function Control Register 1                       */
    __IO uint32_t GPB_MFP2;              /*!< [0x0518] GPIOB Multiple Function Control Register 2                       */
    __IO uint32_t GPB_MFP3;              /*!< [0x051c] GPIOB Multiple Function Control Register 3                       */
    __IO uint32_t GPC_MFP0;              /*!< [0x0520] GPIOC Multiple Function Control Register 0                       */
    __IO uint32_t GPC_MFP1;              /*!< [0x0524] GPIOC Multiple Function Control Register 1                       */
    __IO uint32_t GPC_MFP2;              /*!< [0x0528] GPIOC Multiple Function Control Register 2                       */
    __IO uint32_t GPC_MFP3;              /*!< [0x052c] GPIOC Multiple Function Control Register 3                       */
    __IO uint32_t GPD_MFP0;              /*!< [0x0530] GPIOD Multiple Function Control Register 0                       */
    __IO uint32_t GPD_MFP1;              /*!< [0x0534] GPIOD Multiple Function Control Register 1                       */
    __IO uint32_t GPD_MFP2;              /*!< [0x0538] GPIOD Multiple Function Control Register 2                       */
    __IO uint32_t GPD_MFP3;              /*!< [0x053c] GPIOD Multiple Function Control Register 3                       */
    __IO uint32_t GPE_MFP0;              /*!< [0x0540] GPIOE Multiple Function Control Register 0                       */
    __IO uint32_t GPE_MFP1;              /*!< [0x0544] GPIOE Multiple Function Control Register 1                       */
    __IO uint32_t GPE_MFP2;              /*!< [0x0548] GPIOE Multiple Function Control Register 2                       */
    __IO uint32_t GPE_MFP3;              /*!< [0x054c] GPIOE Multiple Function Control Register 3                       */
    __IO uint32_t GPF_MFP0;              /*!< [0x0550] GPIOF Multiple Function Control Register 0                       */
    __IO uint32_t GPF_MFP1;              /*!< [0x0554] GPIOF Multiple Function Control Register 1                       */
    __IO uint32_t GPF_MFP2;              /*!< [0x0558] GPIOF Multiple Function Control Register 2                       */
    __IO uint32_t GPF_MFP3;              /*!< [0x055c] GPIOF Multiple Function Control Register 3                       */
    __IO uint32_t GPG_MFP0;              /*!< [0x0560] GPIOG Multiple Function Control Register 0                       */
    __IO uint32_t GPG_MFP1;              /*!< [0x0564] GPIOG Multiple Function Control Register 1                       */
    __IO uint32_t GPG_MFP2;              /*!< [0x0568] GPIOG Multiple Function Control Register 2                       */
    __IO uint32_t GPG_MFP3;              /*!< [0x056c] GPIOG Multiple Function Control Register 3                       */
    __IO uint32_t GPH_MFP0;              /*!< [0x0570] GPIOH Multiple Function Control Register 0                       */
    __IO uint32_t GPH_MFP1;              /*!< [0x0574] GPIOH Multiple Function Control Register 1                       */
    __IO uint32_t GPH_MFP2;              /*!< [0x0578] GPIOH Multiple Function Control Register 2                       */
    __IO uint32_t GPH_MFP3;              /*!< [0x057c] GPIOH Multiple Function Control Register 3                       */
    __IO uint32_t GPI_MFP0;              /*!< [0x0580] GPIOI Multiple Function Control Register 0                       */
    __IO uint32_t GPI_MFP1;              /*!< [0x0584] GPIOI Multiple Function Control Register 1                       */
    __IO uint32_t GPI_MFP2;              /*!< [0x0588] GPIOI Multiple Function Control Register 2                       */
    __IO uint32_t GPI_MFP3;              /*!< [0x058c] GPIOI Multiple Function Control Register 3                       */
    __IO uint32_t GPJ_MFP0;              /*!< [0x0590] GPIOJ Multiple Function Control Register 0                       */
    __IO uint32_t GPJ_MFP1;              /*!< [0x0594] GPIOJ Multiple Function Control Register 1                       */
    __IO uint32_t GPJ_MFP2;              /*!< [0x0598] GPIOJ Multiple Function Control Register 2                       */
    __IO uint32_t GPJ_MFP3;              /*!< [0x059c] GPIOJ Multiple Function Control Register 3                       */

} SYS_T;

/**
    @addtogroup SYS_CONST SYS Bit Field Definition
    Constant Definitions for SYS Controller
@{ */

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

#define SYS_RSTSTS_MCURF_Pos             (5)                                               /*!< SYS_T::RSTSTS: MCURF Position          */
#define SYS_RSTSTS_MCURF_Msk             (0x1ul << SYS_RSTSTS_MCURF_Pos)                   /*!< SYS_T::RSTSTS: MCURF Mask              */

#define SYS_RSTSTS_HRESETRF_Pos          (6)                                               /*!< SYS_T::RSTSTS: HRESETRF Position       */
#define SYS_RSTSTS_HRESETRF_Msk          (0x1ul << SYS_RSTSTS_HRESETRF_Pos)                /*!< SYS_T::RSTSTS: HRESETRF Mask           */

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

#define SYS_IPRST0_EMAC0RST_Pos          (5)                                               /*!< SYS_T::IPRST0: EMAC0RST Position        */
#define SYS_IPRST0_EMAC0RST_Msk          (0x1ul << SYS_IPRST0_EMAC0RST_Pos)                /*!< SYS_T::IPRST0: EMAC0RST Mask            */

#define SYS_IPRST0_SDH0RST_Pos           (6)                                               /*!< SYS_T::IPRST0: SDH0RST Position        */
#define SYS_IPRST0_SDH0RST_Msk           (0x1ul << SYS_IPRST0_SDH0RST_Pos)                 /*!< SYS_T::IPRST0: SDH0RST Mask            */

#define SYS_IPRST0_CRCRST_Pos            (7)                                               /*!< SYS_T::IPRST0: CRCRST Position         */
#define SYS_IPRST0_CRCRST_Msk            (0x1ul << SYS_IPRST0_CRCRST_Pos)                  /*!< SYS_T::IPRST0: CRCRST Mask             */

#define SYS_IPRST0_CCAPRST_Pos           (8)                                               /*!< SYS_T::IPRST0: CCAPRST Position        */
#define SYS_IPRST0_CCAPRST_Msk           (0x1ul << SYS_IPRST0_CCAPRST_Pos)                 /*!< SYS_T::IPRST0: CCAPRST Mask            */

#define SYS_IPRST0_HSUSBDRST_Pos         (10)                                              /*!< SYS_T::IPRST0: HSUSBDRST Position      */
#define SYS_IPRST0_HSUSBDRST_Msk         (0x1ul << SYS_IPRST0_HSUSBDRST_Pos)               /*!< SYS_T::IPRST0: HSUSBDRST Mask          */

#define SYS_IPRST0_HBIRST_Pos            (11)                                              /*!< SYS_T::IPRST0: HBIRST Position         */
#define SYS_IPRST0_HBIRST_Msk            (0x1ul << SYS_IPRST0_HBIRST_Pos)                  /*!< SYS_T::IPRST0: HBIRST Mask             */

#define SYS_IPRST0_CRPTRST_Pos           (12)                                              /*!< SYS_T::IPRST0: CRPTRST Position        */
#define SYS_IPRST0_CRPTRST_Msk           (0x1ul << SYS_IPRST0_CRPTRST_Pos)                 /*!< SYS_T::IPRST0: CRPTRST Mask            */

#define SYS_IPRST0_KSRST_Pos             (13)                                              /*!< SYS_T::IPRST0: KSRST Position          */
#define SYS_IPRST0_KSRST_Msk             (0x1ul << SYS_IPRST0_KSRST_Pos)                   /*!< SYS_T::IPRST0: KSRST Mask              */

#define SYS_IPRST0_SPIMRST_Pos           (14)                                              /*!< SYS_T::IPRST0: SPIMRST Position        */
#define SYS_IPRST0_SPIMRST_Msk           (0x1ul << SYS_IPRST0_SPIMRST_Pos)                 /*!< SYS_T::IPRST0: SPIMRST Mask            */

#define SYS_IPRST0_HSUSBHRST_Pos         (16)                                              /*!< SYS_T::IPRST0: HSUSBHRST Position      */
#define SYS_IPRST0_HSUSBHRST_Msk         (0x1ul << SYS_IPRST0_HSUSBHRST_Pos)               /*!< SYS_T::IPRST0: HSUSBHRST Mask          */

#define SYS_IPRST0_SDH1RST_Pos           (17)                                              /*!< SYS_T::IPRST0: SDH1RST Position        */
#define SYS_IPRST0_SDH1RST_Msk           (0x1ul << SYS_IPRST0_SDH1RST_Pos)                 /*!< SYS_T::IPRST0: SDH1RST Mask            */

#define SYS_IPRST0_PDMA1RST_Pos          (18)                                              /*!< SYS_T::IPRST0: PDMA1RST Position       */
#define SYS_IPRST0_PDMA1RST_Msk          (0x1ul << SYS_IPRST0_PDMA1RST_Pos)                /*!< SYS_T::IPRST0: PDMA1RST Mask           */

#define SYS_IPRST0_CANFD0RST_Pos         (20)                                              /*!< SYS_T::IPRST0: CANFD0RST Position      */
#define SYS_IPRST0_CANFD0RST_Msk         (0x1ul << SYS_IPRST0_CANFD0RST_Pos)               /*!< SYS_T::IPRST0: CANFD0RST Mask          */

#define SYS_IPRST0_CANFD1RST_Pos         (21)                                              /*!< SYS_T::IPRST0: CANFD1RST Position      */
#define SYS_IPRST0_CANFD1RST_Msk         (0x1ul << SYS_IPRST0_CANFD1RST_Pos)               /*!< SYS_T::IPRST0: CANFD1RST Mask          */

#define SYS_IPRST0_CANFD2RST_Pos         (22)                                              /*!< SYS_T::IPRST0: CANFD2RST Position      */
#define SYS_IPRST0_CANFD2RST_Msk         (0x1ul << SYS_IPRST0_CANFD2RST_Pos)               /*!< SYS_T::IPRST0: CANFD2RST Mask          */

#define SYS_IPRST0_CANFD3RST_Pos         (23)                                              /*!< SYS_T::IPRST0: CANFD3RST Position      */
#define SYS_IPRST0_CANFD3RST_Msk         (0x1ul << SYS_IPRST0_CANFD3RST_Pos)               /*!< SYS_T::IPRST0: CANFD3RST Mask          */

#define SYS_IPRST0_BMCRST_Pos            (28)                                              /*!< SYS_T::IPRST0: BMCRST Position         */
#define SYS_IPRST0_BMCRST_Msk            (0x1ul << SYS_IPRST0_BMCRST_Pos)                  /*!< SYS_T::IPRST0: BMCRST Mask             */

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

#define SYS_IPRST1_I2C3RST_Pos           (11)                                              /*!< SYS_T::IPRST1: I2C3RST Position        */
#define SYS_IPRST1_I2C3RST_Msk           (0x1ul << SYS_IPRST1_I2C3RST_Pos)                 /*!< SYS_T::IPRST1: I2C3RST Mask            */

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

#define SYS_IPRST1_UART6RST_Pos          (22)                                              /*!< SYS_T::IPRST1: UART6RST Position       */
#define SYS_IPRST1_UART6RST_Msk          (0x1ul << SYS_IPRST1_UART6RST_Pos)                /*!< SYS_T::IPRST1: UART6RST Mask           */

#define SYS_IPRST1_UART7RST_Pos          (23)                                              /*!< SYS_T::IPRST1: UART7RST Position       */
#define SYS_IPRST1_UART7RST_Msk          (0x1ul << SYS_IPRST1_UART7RST_Pos)                /*!< SYS_T::IPRST1: UART7RST Mask           */

#define SYS_IPRST1_OTGRST_Pos            (26)                                              /*!< SYS_T::IPRST1: OTGRST Position         */
#define SYS_IPRST1_OTGRST_Msk            (0x1ul << SYS_IPRST1_OTGRST_Pos)                  /*!< SYS_T::IPRST1: OTGRST Mask             */

#define SYS_IPRST1_USBDRST_Pos           (27)                                              /*!< SYS_T::IPRST1: USBDRST Position        */
#define SYS_IPRST1_USBDRST_Msk           (0x1ul << SYS_IPRST1_USBDRST_Pos)                 /*!< SYS_T::IPRST1: USBDRST Mask            */

#define SYS_IPRST1_EADC0RST_Pos          (28)                                              /*!< SYS_T::IPRST1: EADC0RST Position       */
#define SYS_IPRST1_EADC0RST_Msk          (0x1ul << SYS_IPRST1_EADC0RST_Pos)                /*!< SYS_T::IPRST1: EADC0RST Mask           */

#define SYS_IPRST1_I2S0RST_Pos           (29)                                              /*!< SYS_T::IPRST1: I2S0RST Position        */
#define SYS_IPRST1_I2S0RST_Msk           (0x1ul << SYS_IPRST1_I2S0RST_Pos)                 /*!< SYS_T::IPRST1: I2S0RST Mask            */

#define SYS_IPRST1_HSOTGRST_Pos          (30)                                              /*!< SYS_T::IPRST1: HSOTGRST Position       */
#define SYS_IPRST1_HSOTGRST_Msk          (0x1ul << SYS_IPRST1_HSOTGRST_Pos)                /*!< SYS_T::IPRST1: HSOTGRST Mask           */

#define SYS_IPRST1_TRNGRST_Pos           (31)                                              /*!< SYS_T::IPRST1: TRNGRST Position        */
#define SYS_IPRST1_TRNGRST_Msk           (0x1ul << SYS_IPRST1_TRNGRST_Pos)                 /*!< SYS_T::IPRST1: TRNGRST Mask            */

#define SYS_IPRST2_SC0RST_Pos            (0)                                               /*!< SYS_T::IPRST2: SC0RST Position         */
#define SYS_IPRST2_SC0RST_Msk            (0x1ul << SYS_IPRST2_SC0RST_Pos)                  /*!< SYS_T::IPRST2: SC0RST Mask             */

#define SYS_IPRST2_SC1RST_Pos            (1)                                               /*!< SYS_T::IPRST2: SC1RST Position         */
#define SYS_IPRST2_SC1RST_Msk            (0x1ul << SYS_IPRST2_SC1RST_Pos)                  /*!< SYS_T::IPRST2: SC1RST Mask             */

#define SYS_IPRST2_SC2RST_Pos            (2)                                               /*!< SYS_T::IPRST2: SC2RST Position         */
#define SYS_IPRST2_SC2RST_Msk            (0x1ul << SYS_IPRST2_SC2RST_Pos)                  /*!< SYS_T::IPRST2: SC2RST Mask             */

#define SYS_IPRST2_I2C4RST_Pos           (3)                                               /*!< SYS_T::IPRST2: I2C4RST Position        */
#define SYS_IPRST2_I2C4RST_Msk           (0x1ul << SYS_IPRST2_I2C4RST_Pos)                 /*!< SYS_T::IPRST2: I2C4RST Mask            */

#define SYS_IPRST2_QSPI1RST_Pos          (4)                                               /*!< SYS_T::IPRST2: QSPI1RST Position       */
#define SYS_IPRST2_QSPI1RST_Msk          (0x1ul << SYS_IPRST2_QSPI1RST_Pos)                /*!< SYS_T::IPRST2: QSPI1RST Mask           */

#define SYS_IPRST2_SPI3RST_Pos           (6)                                               /*!< SYS_T::IPRST2: SPI3RST Position        */
#define SYS_IPRST2_SPI3RST_Msk           (0x1ul << SYS_IPRST2_SPI3RST_Pos)                 /*!< SYS_T::IPRST2: SPI3RST Mask            */

#define SYS_IPRST2_SPI4RST_Pos           (7)                                               /*!< SYS_T::IPRST2: SPI4RST Position        */
#define SYS_IPRST2_SPI4RST_Msk           (0x1ul << SYS_IPRST2_SPI4RST_Pos)                 /*!< SYS_T::IPRST2: SPI4RST Mask            */

#define SYS_IPRST2_USCI0RST_Pos          (8)                                               /*!< SYS_T::IPRST2: USCI0RST Position       */
#define SYS_IPRST2_USCI0RST_Msk          (0x1ul << SYS_IPRST2_USCI0RST_Pos)                /*!< SYS_T::IPRST2: USCI0RST Mask           */

#define SYS_IPRST2_PSIORST_Pos           (10)                                              /*!< SYS_T::IPRST2: PSIORST Position        */
#define SYS_IPRST2_PSIORST_Msk           (0x1ul << SYS_IPRST2_PSIORST_Pos)                 /*!< SYS_T::IPRST2: PSIORST Mask            */

#define SYS_IPRST2_DACRST_Pos            (12)                                              /*!< SYS_T::IPRST2: DACRST Position         */
#define SYS_IPRST2_DACRST_Msk            (0x1ul << SYS_IPRST2_DACRST_Pos)                  /*!< SYS_T::IPRST2: DACRST Mask             */

#define SYS_IPRST2_ECAP2RST_Pos          (13)                                              /*!< SYS_T::IPRST2: ECAP2RST Position       */
#define SYS_IPRST2_ECAP2RST_Msk          (0x1ul << SYS_IPRST2_ECAP2RST_Pos)                /*!< SYS_T::IPRST2: ECAP2RST Mask           */

#define SYS_IPRST2_ECAP3RST_Pos          (14)                                              /*!< SYS_T::IPRST2: ECAP3RST Position       */
#define SYS_IPRST2_ECAP3RST_Msk          (0x1ul << SYS_IPRST2_ECAP3RST_Pos)                /*!< SYS_T::IPRST2: ECAP3RST Mask           */

#define SYS_IPRST2_EPWM0RST_Pos          (16)                                              /*!< SYS_T::IPRST2: EPWM0RST Position       */
#define SYS_IPRST2_EPWM0RST_Msk          (0x1ul << SYS_IPRST2_EPWM0RST_Pos)                /*!< SYS_T::IPRST2: EPWM0RST Mask           */

#define SYS_IPRST2_EPWM1RST_Pos          (17)                                              /*!< SYS_T::IPRST2: EPWM1RST Position       */
#define SYS_IPRST2_EPWM1RST_Msk          (0x1ul << SYS_IPRST2_EPWM1RST_Pos)                /*!< SYS_T::IPRST2: EPWM1RST Mask           */

#define SYS_IPRST2_BPWM0RST_Pos          (18)                                              /*!< SYS_T::IPRST2: BPWM0RST Position       */
#define SYS_IPRST2_BPWM0RST_Msk          (0x1ul << SYS_IPRST2_BPWM0RST_Pos)                /*!< SYS_T::IPRST2: BPWM0RST Mask           */

#define SYS_IPRST2_BPWM1RST_Pos          (19)                                              /*!< SYS_T::IPRST2: BPWM1RST Position       */
#define SYS_IPRST2_BPWM1RST_Msk          (0x1ul << SYS_IPRST2_BPWM1RST_Pos)                /*!< SYS_T::IPRST2: BPWM1RST Mask           */

#define SYS_IPRST2_EQEI2RST_Pos          (20)                                              /*!< SYS_T::IPRST2: EQEI2RST Position       */
#define SYS_IPRST2_EQEI2RST_Msk          (0x1ul << SYS_IPRST2_EQEI2RST_Pos)                /*!< SYS_T::IPRST2: EQEI2RST Mask           */

#define SYS_IPRST2_EQEI3RST_Pos          (21)                                              /*!< SYS_T::IPRST2: EQEI3RST Position       */
#define SYS_IPRST2_EQEI3RST_Msk          (0x1ul << SYS_IPRST2_EQEI3RST_Pos)                /*!< SYS_T::IPRST2: EQEI3RST Mask           */

#define SYS_IPRST2_EQEI0RST_Pos          (22)                                              /*!< SYS_T::IPRST2: EQEI0RST Position       */
#define SYS_IPRST2_EQEI0RST_Msk          (0x1ul << SYS_IPRST2_EQEI0RST_Pos)                /*!< SYS_T::IPRST2: EQEI0RST Mask           */

#define SYS_IPRST2_EQEI1RST_Pos          (23)                                              /*!< SYS_T::IPRST2: EQEI1RST Position       */
#define SYS_IPRST2_EQEI1RST_Msk          (0x1ul << SYS_IPRST2_EQEI1RST_Pos)                /*!< SYS_T::IPRST2: EQEI1RST Mask           */

#define SYS_IPRST2_ECAP0RST_Pos          (26)                                              /*!< SYS_T::IPRST2: ECAP0RST Position       */
#define SYS_IPRST2_ECAP0RST_Msk          (0x1ul << SYS_IPRST2_ECAP0RST_Pos)                /*!< SYS_T::IPRST2: ECAP0RST Mask           */

#define SYS_IPRST2_ECAP1RST_Pos          (27)                                              /*!< SYS_T::IPRST2: ECAP1RST Position       */
#define SYS_IPRST2_ECAP1RST_Msk          (0x1ul << SYS_IPRST2_ECAP1RST_Pos)                /*!< SYS_T::IPRST2: ECAP1RST Mask           */

#define SYS_IPRST2_I2S1RST_Pos           (29)                                              /*!< SYS_T::IPRST2: I2S1RST Position        */
#define SYS_IPRST2_I2S1RST_Msk           (0x1ul << SYS_IPRST2_I2S1RST_Pos)                 /*!< SYS_T::IPRST2: I2S1RST Mask            */

#define SYS_IPRST2_EADC1RST_Pos          (31)                                              /*!< SYS_T::IPRST2: EADC1RST Position       */
#define SYS_IPRST2_EADC1RST_Msk          (0x1ul << SYS_IPRST2_EADC1RST_Pos)                /*!< SYS_T::IPRST2: EADC1RST Mask           */

#define SYS_BODCTL_BODEN_Pos             (0)                                               /*!< SYS_T::BODCTL: BODEN Position          */
#define SYS_BODCTL_BODEN_Msk             (0x1ul << SYS_BODCTL_BODEN_Pos)                   /*!< SYS_T::BODCTL: BODEN Mask              */

#define SYS_BODCTL_BODRSTEN_Pos          (3)                                               /*!< SYS_T::BODCTL: BODRSTEN Position       */
#define SYS_BODCTL_BODRSTEN_Msk          (0x1ul << SYS_BODCTL_BODRSTEN_Pos)                /*!< SYS_T::BODCTL: BODRSTEN Mask           */

#define SYS_BODCTL_BODIF_Pos             (4)                                               /*!< SYS_T::BODCTL: BODIF Position          */
#define SYS_BODCTL_BODIF_Msk             (0x1ul << SYS_BODCTL_BODIF_Pos)                   /*!< SYS_T::BODCTL: BODIF Mask              */

#define SYS_BODCTL_BODLPM_Pos            (5)                                               /*!< SYS_T::BODCTL: BODLPM Position         */
#define SYS_BODCTL_BODLPM_Msk            (0x1ul << SYS_BODCTL_BODLPM_Pos)                  /*!< SYS_T::BODCTL: BODLPM Mask             */

#define SYS_BODCTL_BODOUT_Pos            (6)                                               /*!< SYS_T::BODCTL: BODOUT Position         */
#define SYS_BODCTL_BODOUT_Msk            (0x1ul << SYS_BODCTL_BODOUT_Pos)                  /*!< SYS_T::BODCTL: BODOUT Mask             */

#define SYS_BODCTL_LVREN_Pos             (7)                                               /*!< SYS_T::BODCTL: LVREN Position          */
#define SYS_BODCTL_LVREN_Msk             (0x1ul << SYS_BODCTL_LVREN_Pos)                   /*!< SYS_T::BODCTL: LVREN Mask              */

#define SYS_BODCTL_BODDGSEL_Pos          (8)                                               /*!< SYS_T::BODCTL: BODDGSEL Position       */
#define SYS_BODCTL_BODDGSEL_Msk          (0x7ul << SYS_BODCTL_BODDGSEL_Pos)                /*!< SYS_T::BODCTL: BODDGSEL Mask           */

#define SYS_BODCTL_LVRDGSEL_Pos          (12)                                              /*!< SYS_T::BODCTL: LVRDGSEL Position       */
#define SYS_BODCTL_LVRDGSEL_Msk          (0x7ul << SYS_BODCTL_LVRDGSEL_Pos)                /*!< SYS_T::BODCTL: LVRDGSEL Mask           */

#define SYS_BODCTL_LVRRDY_Pos            (15)                                              /*!< SYS_T::BODCTL: LVRRDY Position         */
#define SYS_BODCTL_LVRRDY_Msk            (0x1ul << SYS_BODCTL_LVRRDY_Pos)                  /*!< SYS_T::BODCTL: LVRRDY Mask             */

#define SYS_BODCTL_BODVL_Pos             (16)                                              /*!< SYS_T::BODCTL: BODVL Position          */
#define SYS_BODCTL_BODVL_Msk             (0x7ul << SYS_BODCTL_BODVL_Pos)                   /*!< SYS_T::BODCTL: BODVL Mask              */

#define SYS_IVSCTL_VTEMPEN_Pos           (0)                                               /*!< SYS_T::IVSCTL: VTEMPEN Position        */
#define SYS_IVSCTL_VTEMPEN_Msk           (0x1ul << SYS_IVSCTL_VTEMPEN_Pos)                 /*!< SYS_T::IVSCTL: VTEMPEN Mask            */

#define SYS_IVSCTL_VBATUGEN_Pos          (1)                                               /*!< SYS_T::IVSCTL: VBATUGEN Position       */
#define SYS_IVSCTL_VBATUGEN_Msk          (0x1ul << SYS_IVSCTL_VBATUGEN_Pos)                /*!< SYS_T::IVSCTL: VBATUGEN Mask           */

#define SYS_IPRST3_KPIRST_Pos            (0)                                               /*!< SYS_T::IPRST3: KPIRST Position         */
#define SYS_IPRST3_KPIRST_Msk            (0x1ul << SYS_IPRST3_KPIRST_Pos)                  /*!< SYS_T::IPRST3: KPIRST Mask             */

#define SYS_IPRST3_EADC2RST_Pos          (6)                                               /*!< SYS_T::IPRST3: EADC2RST Position       */
#define SYS_IPRST3_EADC2RST_Msk          (0x1ul << SYS_IPRST3_EADC2RST_Pos)                /*!< SYS_T::IPRST3: EADC2RST Mask           */

#define SYS_IPRST3_ACMP23RST_Pos         (7)                                               /*!< SYS_T::IPRST3: ACMP23RST Position      */
#define SYS_IPRST3_ACMP23RST_Msk         (0x1ul << SYS_IPRST3_ACMP23RST_Pos)               /*!< SYS_T::IPRST3: ACMP23RST Mask          */

#define SYS_IPRST3_SPI5RST_Pos           (8)                                               /*!< SYS_T::IPRST3: SPI5RST Position        */
#define SYS_IPRST3_SPI5RST_Msk           (0x1ul << SYS_IPRST3_SPI5RST_Pos)                 /*!< SYS_T::IPRST3: SPI5RST Mask            */

#define SYS_IPRST3_SPI6RST_Pos           (9)                                               /*!< SYS_T::IPRST3: SPI6RST Position        */
#define SYS_IPRST3_SPI6RST_Msk           (0x1ul << SYS_IPRST3_SPI6RST_Pos)                 /*!< SYS_T::IPRST3: SPI6RST Mask            */

#define SYS_IPRST3_SPI7RST_Pos           (10)                                              /*!< SYS_T::IPRST3: SPI7RST Position        */
#define SYS_IPRST3_SPI7RST_Msk           (0x1ul << SYS_IPRST3_SPI7RST_Pos)                 /*!< SYS_T::IPRST3: SPI7RST Mask            */

#define SYS_IPRST3_SPI8RST_Pos           (11)                                              /*!< SYS_T::IPRST3: SPI8RST Position        */
#define SYS_IPRST3_SPI8RST_Msk           (0x1ul << SYS_IPRST3_SPI8RST_Pos)                 /*!< SYS_T::IPRST3: SPI8RST Mask            */

#define SYS_IPRST3_SPI9RST_Pos           (12)                                              /*!< SYS_T::IPRST3: SPI9RST Position        */
#define SYS_IPRST3_SPI9RST_Msk           (0x1ul << SYS_IPRST3_SPI9RST_Pos)                 /*!< SYS_T::IPRST3: SPI9RST Mask            */

#define SYS_IPRST3_SPI10RST_Pos          (13)                                              /*!< SYS_T::IPRST3: SPI10RST Position       */
#define SYS_IPRST3_SPI10RST_Msk          (0x1ul << SYS_IPRST3_SPI10RST_Pos)                /*!< SYS_T::IPRST3: SPI10RST Mask           */

#define SYS_IPRST3_UART8RST_Pos          (16)                                              /*!< SYS_T::IPRST3: UART8RST Position       */
#define SYS_IPRST3_UART8RST_Msk          (0x1ul << SYS_IPRST3_UART8RST_Pos)                /*!< SYS_T::IPRST3: UART8RST Mask           */

#define SYS_IPRST3_UART9RST_Pos          (17)                                              /*!< SYS_T::IPRST3: UART9RST Position       */
#define SYS_IPRST3_UART9RST_Msk          (0x1ul << SYS_IPRST3_UART9RST_Pos)                /*!< SYS_T::IPRST3: UART9RST Mask           */

#define SYS_PORCTL_POROFF_Pos            (0)                                               /*!< SYS_T::PORCTL: POROFF Position         */
#define SYS_PORCTL_POROFF_Msk            (0xfffful << SYS_PORCTL_POROFF_Pos)               /*!< SYS_T::PORCTL: POROFF Mask             */

#define SYS_VREFCTL_VREFCTL_Pos          (0)                                               /*!< SYS_T::VREFCTL: VREFCTL Position       */
#define SYS_VREFCTL_VREFCTL_Msk          (0x1ful << SYS_VREFCTL_VREFCTL_Pos)               /*!< SYS_T::VREFCTL: VREFCTL Mask           */

#define SYS_VREFCTL_PRELOADSEL_Pos       (6)                                               /*!< SYS_T::VREFCTL: PRELOADSEL Position    */
#define SYS_VREFCTL_PRELOADSEL_Msk       (0x3ul << SYS_VREFCTL_PRELOADSEL_Pos)             /*!< SYS_T::VREFCTL: PRELOADSEL Mask        */

#define SYS_VREFCTL_VBGFEN_Pos           (24)                                              /*!< SYS_T::VREFCTL: VBGFEN Position        */
#define SYS_VREFCTL_VBGFEN_Msk           (0x1ul << SYS_VREFCTL_VBGFEN_Pos)                 /*!< SYS_T::VREFCTL: VBGFEN Mask            */

#define SYS_VREFCTL_VBGISEL_Pos          (25)                                              /*!< SYS_T::VREFCTL: VBGISEL Position       */
#define SYS_VREFCTL_VBGISEL_Msk          (0x3ul << SYS_VREFCTL_VBGISEL_Pos)                /*!< SYS_T::VREFCTL: VBGISEL Mask           */

#define SYS_USBPHY_USBROLE_Pos           (0)                                               /*!< SYS_T::USBPHY: USBROLE Position        */
#define SYS_USBPHY_USBROLE_Msk           (0x3ul << SYS_USBPHY_USBROLE_Pos)                 /*!< SYS_T::USBPHY: USBROLE Mask            */

#define SYS_USBPHY_SBO_Pos               (2)                                               /*!< SYS_T::USBPHY: SBO Position            */
#define SYS_USBPHY_SBO_Msk               (0x1ul << SYS_USBPHY_SBO_Pos)                     /*!< SYS_T::USBPHY: SBO Mask                */

#define SYS_USBPHY_USBEN_Pos             (8)                                               /*!< SYS_T::USBPHY: USBEN Position          */
#define SYS_USBPHY_USBEN_Msk             (0x1ul << SYS_USBPHY_USBEN_Pos)                   /*!< SYS_T::USBPHY: USBEN Mask              */

#define SYS_USBPHY_HSUSBROLE_Pos         (16)                                              /*!< SYS_T::USBPHY: HSUSBROLE Position      */
#define SYS_USBPHY_HSUSBROLE_Msk         (0x3ul << SYS_USBPHY_HSUSBROLE_Pos)               /*!< SYS_T::USBPHY: HSUSBROLE Mask          */

#define SYS_USBPHY_HSUSBEN_Pos           (24)                                              /*!< SYS_T::USBPHY: HSUSBEN Position        */
#define SYS_USBPHY_HSUSBEN_Msk           (0x1ul << SYS_USBPHY_HSUSBEN_Pos)                 /*!< SYS_T::USBPHY: HSUSBEN Mask            */

#define SYS_USBPHY_HSUSBACT_Pos          (25)                                              /*!< SYS_T::USBPHY: HSUSBACT Position       */
#define SYS_USBPHY_HSUSBACT_Msk          (0x1ul << SYS_USBPHY_HSUSBACT_Pos)                /*!< SYS_T::USBPHY: HSUSBACT Mask           */

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

#define SYS_GPC_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPC_MFOS: MFOS14 Position       */
#define SYS_GPC_MFOS_MFOS14_Msk          (0x1ul << SYS_GPC_MFOS_MFOS14_Pos)                /*!< SYS_T::GPC_MFOS: MFOS14 Mask           */

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

#define SYS_GPD_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPD_MFOS: MFOS13 Position       */
#define SYS_GPD_MFOS_MFOS13_Msk          (0x1ul << SYS_GPD_MFOS_MFOS13_Pos)                /*!< SYS_T::GPD_MFOS: MFOS13 Mask           */

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

#define SYS_GPG_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPG_MFOS: MFOS0 Position        */
#define SYS_GPG_MFOS_MFOS0_Msk           (0x1ul << SYS_GPG_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS0 Mask            */

#define SYS_GPG_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPG_MFOS: MFOS1 Position        */
#define SYS_GPG_MFOS_MFOS1_Msk           (0x1ul << SYS_GPG_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS1 Mask            */

#define SYS_GPG_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPG_MFOS: MFOS2 Position        */
#define SYS_GPG_MFOS_MFOS2_Msk           (0x1ul << SYS_GPG_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS2 Mask            */

#define SYS_GPG_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPG_MFOS: MFOS3 Position        */
#define SYS_GPG_MFOS_MFOS3_Msk           (0x1ul << SYS_GPG_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS3 Mask            */

#define SYS_GPG_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPG_MFOS: MFOS4 Position        */
#define SYS_GPG_MFOS_MFOS4_Msk           (0x1ul << SYS_GPG_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS4 Mask            */

#define SYS_GPG_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPG_MFOS: MFOS5 Position        */
#define SYS_GPG_MFOS_MFOS5_Msk           (0x1ul << SYS_GPG_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS5 Mask            */

#define SYS_GPG_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPG_MFOS: MFOS6 Position        */
#define SYS_GPG_MFOS_MFOS6_Msk           (0x1ul << SYS_GPG_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS6 Mask            */

#define SYS_GPG_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPG_MFOS: MFOS7 Position        */
#define SYS_GPG_MFOS_MFOS7_Msk           (0x1ul << SYS_GPG_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS7 Mask            */

#define SYS_GPG_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPG_MFOS: MFOS8 Position        */
#define SYS_GPG_MFOS_MFOS8_Msk           (0x1ul << SYS_GPG_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS8 Mask            */

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

#define SYS_GPH_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPH_MFOS: MFOS0 Position        */
#define SYS_GPH_MFOS_MFOS0_Msk           (0x1ul << SYS_GPH_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS0 Mask            */

#define SYS_GPH_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPH_MFOS: MFOS1 Position        */
#define SYS_GPH_MFOS_MFOS1_Msk           (0x1ul << SYS_GPH_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS1 Mask            */

#define SYS_GPH_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPH_MFOS: MFOS2 Position        */
#define SYS_GPH_MFOS_MFOS2_Msk           (0x1ul << SYS_GPH_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS2 Mask            */

#define SYS_GPH_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPH_MFOS: MFOS3 Position        */
#define SYS_GPH_MFOS_MFOS3_Msk           (0x1ul << SYS_GPH_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS3 Mask            */

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

#define SYS_GPH_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPH_MFOS: MFOS12 Position       */
#define SYS_GPH_MFOS_MFOS12_Msk          (0x1ul << SYS_GPH_MFOS_MFOS12_Pos)                /*!< SYS_T::GPH_MFOS: MFOS12 Mask           */

#define SYS_GPH_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPH_MFOS: MFOS13 Position       */
#define SYS_GPH_MFOS_MFOS13_Msk          (0x1ul << SYS_GPH_MFOS_MFOS13_Pos)                /*!< SYS_T::GPH_MFOS: MFOS13 Mask           */

#define SYS_GPH_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPH_MFOS: MFOS14 Position       */
#define SYS_GPH_MFOS_MFOS14_Msk          (0x1ul << SYS_GPH_MFOS_MFOS14_Pos)                /*!< SYS_T::GPH_MFOS: MFOS14 Mask           */

#define SYS_GPH_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPH_MFOS: MFOS15 Position       */
#define SYS_GPH_MFOS_MFOS15_Msk          (0x1ul << SYS_GPH_MFOS_MFOS15_Pos)                /*!< SYS_T::GPH_MFOS: MFOS15 Mask           */

#define SYS_GPI_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPI_MFOS: MFOS6 Position        */
#define SYS_GPI_MFOS_MFOS6_Msk           (0x1ul << SYS_GPI_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPI_MFOS: MFOS6 Mask            */

#define SYS_GPI_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPI_MFOS: MFOS7 Position        */
#define SYS_GPI_MFOS_MFOS7_Msk           (0x1ul << SYS_GPI_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPI_MFOS: MFOS7 Mask            */

#define SYS_GPI_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPI_MFOS: MFOS8 Position        */
#define SYS_GPI_MFOS_MFOS8_Msk           (0x1ul << SYS_GPI_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPI_MFOS: MFOS8 Mask            */

#define SYS_GPI_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPI_MFOS: MFOS9 Position        */
#define SYS_GPI_MFOS_MFOS9_Msk           (0x1ul << SYS_GPI_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPI_MFOS: MFOS9 Mask            */

#define SYS_GPI_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPI_MFOS: MFOS10 Position       */
#define SYS_GPI_MFOS_MFOS10_Msk          (0x1ul << SYS_GPI_MFOS_MFOS10_Pos)                /*!< SYS_T::GPI_MFOS: MFOS10 Mask           */

#define SYS_GPI_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPI_MFOS: MFOS11 Position       */
#define SYS_GPI_MFOS_MFOS11_Msk          (0x1ul << SYS_GPI_MFOS_MFOS11_Pos)                /*!< SYS_T::GPI_MFOS: MFOS11 Mask           */

#define SYS_GPI_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPI_MFOS: MFOS12 Position       */
#define SYS_GPI_MFOS_MFOS12_Msk          (0x1ul << SYS_GPI_MFOS_MFOS12_Pos)                /*!< SYS_T::GPI_MFOS: MFOS12 Mask           */

#define SYS_GPI_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPI_MFOS: MFOS13 Position       */
#define SYS_GPI_MFOS_MFOS13_Msk          (0x1ul << SYS_GPI_MFOS_MFOS13_Pos)                /*!< SYS_T::GPI_MFOS: MFOS13 Mask           */

#define SYS_GPI_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPI_MFOS: MFOS14 Position       */
#define SYS_GPI_MFOS_MFOS14_Msk          (0x1ul << SYS_GPI_MFOS_MFOS14_Pos)                /*!< SYS_T::GPI_MFOS: MFOS14 Mask           */

#define SYS_GPI_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPI_MFOS: MFOS15 Position       */
#define SYS_GPI_MFOS_MFOS15_Msk          (0x1ul << SYS_GPI_MFOS_MFOS15_Pos)                /*!< SYS_T::GPI_MFOS: MFOS15 Mask           */

#define SYS_GPJ_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPJ_MFOS: MFOS0 Position        */
#define SYS_GPJ_MFOS_MFOS0_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS0 Mask            */

#define SYS_GPJ_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPJ_MFOS: MFOS1 Position        */
#define SYS_GPJ_MFOS_MFOS1_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS1 Mask            */

#define SYS_GPJ_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPJ_MFOS: MFOS2 Position        */
#define SYS_GPJ_MFOS_MFOS2_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS2 Mask            */

#define SYS_GPJ_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPJ_MFOS: MFOS3 Position        */
#define SYS_GPJ_MFOS_MFOS3_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS3 Mask            */

#define SYS_GPJ_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPJ_MFOS: MFOS4 Position        */
#define SYS_GPJ_MFOS_MFOS4_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS4 Mask            */

#define SYS_GPJ_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPJ_MFOS: MFOS5 Position        */
#define SYS_GPJ_MFOS_MFOS5_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS5 Mask            */

#define SYS_GPJ_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPJ_MFOS: MFOS6 Position        */
#define SYS_GPJ_MFOS_MFOS6_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS6 Mask            */

#define SYS_GPJ_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPJ_MFOS: MFOS7 Position        */
#define SYS_GPJ_MFOS_MFOS7_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS7 Mask            */

#define SYS_GPJ_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPJ_MFOS: MFOS8 Position        */
#define SYS_GPJ_MFOS_MFOS8_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS8 Mask            */

#define SYS_GPJ_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPJ_MFOS: MFOS9 Position        */
#define SYS_GPJ_MFOS_MFOS9_Msk           (0x1ul << SYS_GPJ_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPJ_MFOS: MFOS9 Mask            */

#define SYS_GPJ_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPJ_MFOS: MFOS10 Position       */
#define SYS_GPJ_MFOS_MFOS10_Msk          (0x1ul << SYS_GPJ_MFOS_MFOS10_Pos)                /*!< SYS_T::GPJ_MFOS: MFOS10 Mask           */

#define SYS_GPJ_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPJ_MFOS: MFOS11 Position       */
#define SYS_GPJ_MFOS_MFOS11_Msk          (0x1ul << SYS_GPJ_MFOS_MFOS11_Pos)                /*!< SYS_T::GPJ_MFOS: MFOS11 Mask           */

#define SYS_GPJ_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPJ_MFOS: MFOS12 Position       */
#define SYS_GPJ_MFOS_MFOS12_Msk          (0x1ul << SYS_GPJ_MFOS_MFOS12_Pos)                /*!< SYS_T::GPJ_MFOS: MFOS12 Mask           */

#define SYS_GPJ_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPJ_MFOS: MFOS13 Position       */
#define SYS_GPJ_MFOS_MFOS13_Msk          (0x1ul << SYS_GPJ_MFOS_MFOS13_Pos)                /*!< SYS_T::GPJ_MFOS: MFOS13 Mask           */

#define SYS_SRAM_INTCTL_PERRIEN_Pos      (0)                                               /*!< SYS_T::SRAM_INTCTL: PERRIEN Position   */
#define SYS_SRAM_INTCTL_PERRIEN_Msk      (0x1ul << SYS_SRAM_INTCTL_PERRIEN_Pos)            /*!< SYS_T::SRAM_INTCTL: PERRIEN Mask       */

#define SYS_SRAM_STATUS_PERRIF_Pos       (0)                                               /*!< SYS_T::SRAM_STATUS: PERRIF Position    */
#define SYS_SRAM_STATUS_PERRIF_Msk       (0x1ul << SYS_SRAM_STATUS_PERRIF_Pos)             /*!< SYS_T::SRAM_STATUS: PERRIF Mask        */

#define SYS_SRAM_ERRADDR_ERRADDR_Pos     (0)                                               /*!< SYS_T::SRAM_ERRADDR: ERRADDR Position  */
#define SYS_SRAM_ERRADDR_ERRADDR_Msk     (0xfffffffful << SYS_SRAM_ERRADDR_ERRADDR_Pos)    /*!< SYS_T::SRAM_ERRADDR: ERRADDR Mask      */

#define SYS_SRAM_BISTCTL_SRBIST0_Pos     (0)                                               /*!< SYS_T::SRAM_BISTCTL: SRBIST0 Position  */
#define SYS_SRAM_BISTCTL_SRBIST0_Msk     (0x1ul << SYS_SRAM_BISTCTL_SRBIST0_Pos)           /*!< SYS_T::SRAM_BISTCTL: SRBIST0 Mask      */

#define SYS_SRAM_BISTCTL_SRBIST1_Pos     (1)                                               /*!< SYS_T::SRAM_BISTCTL: SRBIST1 Position  */
#define SYS_SRAM_BISTCTL_SRBIST1_Msk     (0x1ul << SYS_SRAM_BISTCTL_SRBIST1_Pos)           /*!< SYS_T::SRAM_BISTCTL: SRBIST1 Mask      */

#define SYS_SRAM_BISTCTL_CRBIST_Pos      (2)                                               /*!< SYS_T::SRAM_BISTCTL: CRBIST Position   */
#define SYS_SRAM_BISTCTL_CRBIST_Msk      (0x1ul << SYS_SRAM_BISTCTL_CRBIST_Pos)            /*!< SYS_T::SRAM_BISTCTL: CRBIST Mask       */

#define SYS_SRAM_BISTCTL_CANBIST_Pos     (3)                                               /*!< SYS_T::SRAM_BISTCTL: CANBIST Position  */
#define SYS_SRAM_BISTCTL_CANBIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_CANBIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: CANBIST Mask      */

#define SYS_SRAM_BISTCTL_USBBIST_Pos     (4)                                               /*!< SYS_T::SRAM_BISTCTL: USBBIST Position  */
#define SYS_SRAM_BISTCTL_USBBIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_USBBIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: USBBIST Mask      */

#define SYS_SRAM_BISTCTL_SPIMBIST_Pos    (5)                                               /*!< SYS_T::SRAM_BISTCTL: SPIMBIST Position */
#define SYS_SRAM_BISTCTL_SPIMBIST_Msk    (0x1ul << SYS_SRAM_BISTCTL_SPIMBIST_Pos)          /*!< SYS_T::SRAM_BISTCTL: SPIMBIST Mask     */

#define SYS_SRAM_BISTCTL_EMAC0BIST_Pos   (6)                                               /*!< SYS_T::SRAM_BISTCTL: EMAC0BIST Position*/
#define SYS_SRAM_BISTCTL_EMAC0BIST_Msk   (0x1ul << SYS_SRAM_BISTCTL_EMAC0BIST_Pos)         /*!< SYS_T::SRAM_BISTCTL: EMAC0BIST Mask    */

#define SYS_SRAM_BISTCTL_HSUSBDBIST_Pos  (8)                                               /*!< SYS_T::SRAM_BISTCTL: HSUSBDBIST Position*/
#define SYS_SRAM_BISTCTL_HSUSBDBIST_Msk  (0x1ul << SYS_SRAM_BISTCTL_HSUSBDBIST_Pos)        /*!< SYS_T::SRAM_BISTCTL: HSUSBDBIST Mask   */

#define SYS_SRAM_BISTCTL_HSUSBHBIST_Pos  (9)                                               /*!< SYS_T::SRAM_BISTCTL: HSUSBHBIST Position*/
#define SYS_SRAM_BISTCTL_HSUSBHBIST_Msk  (0x1ul << SYS_SRAM_BISTCTL_HSUSBHBIST_Pos)        /*!< SYS_T::SRAM_BISTCTL: HSUSBHBIST Mask   */

#define SYS_SRAM_BISTCTL_SRBIST2_Pos     (10)                                              /*!< SYS_T::SRAM_BISTCTL: SRBIST2 Position  */
#define SYS_SRAM_BISTCTL_SRBIST2_Msk     (0x1ul << SYS_SRAM_BISTCTL_SRBIST2_Pos)           /*!< SYS_T::SRAM_BISTCTL: SRBIST2 Mask      */

#define SYS_SRAM_BISTCTL_KSBIST_Pos      (11)                                              /*!< SYS_T::SRAM_BISTCTL: KSBIST Position   */
#define SYS_SRAM_BISTCTL_KSBIST_Msk      (0x1ul << SYS_SRAM_BISTCTL_KSBIST_Pos)            /*!< SYS_T::SRAM_BISTCTL: KSBIST Mask       */

#define SYS_SRAM_BISTCTL_CCAPBIST_Pos    (12)                                              /*!< SYS_T::SRAM_BISTCTL: CCAPBIST Position */
#define SYS_SRAM_BISTCTL_CCAPBIST_Msk    (0x1ul << SYS_SRAM_BISTCTL_CCAPBIST_Pos)          /*!< SYS_T::SRAM_BISTCTL: CCAPBIST Mask     */

#define SYS_SRAM_BISTCTL_RSABIST_Pos     (13)                                              /*!< SYS_T::SRAM_BISTCTL: RSABIST Position  */
#define SYS_SRAM_BISTCTL_RSABIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_RSABIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: RSABIST Mask      */

#define SYS_SRAM_BISTSTS_SRBISTEF0_Pos   (0)                                               /*!< SYS_T::SRAM_BISTSTS: SRBISTEF0 Position*/
#define SYS_SRAM_BISTSTS_SRBISTEF0_Msk   (0x1ul << SYS_SRAM_BISTSTS_SRBISTEF0_Pos)         /*!< SYS_T::SRAM_BISTSTS: SRBISTEF0 Mask    */

#define SYS_SRAM_BISTSTS_SRBISTEF1_Pos   (1)                                               /*!< SYS_T::SRAM_BISTSTS: SRBISTEF1 Position*/
#define SYS_SRAM_BISTSTS_SRBISTEF1_Msk   (0x1ul << SYS_SRAM_BISTSTS_SRBISTEF1_Pos)         /*!< SYS_T::SRAM_BISTSTS: SRBISTEF1 Mask    */

#define SYS_SRAM_BISTSTS_CRBISTEF_Pos    (2)                                               /*!< SYS_T::SRAM_BISTSTS: CRBISTEF Position */
#define SYS_SRAM_BISTSTS_CRBISTEF_Msk    (0x1ul << SYS_SRAM_BISTSTS_CRBISTEF_Pos)          /*!< SYS_T::SRAM_BISTSTS: CRBISTEF Mask     */

#define SYS_SRAM_BISTSTS_CANBEF_Pos      (3)                                               /*!< SYS_T::SRAM_BISTSTS: CANBEF Position   */
#define SYS_SRAM_BISTSTS_CANBEF_Msk      (0x1ul << SYS_SRAM_BISTSTS_CANBEF_Pos)            /*!< SYS_T::SRAM_BISTSTS: CANBEF Mask       */

#define SYS_SRAM_BISTSTS_USBBEF_Pos      (4)                                               /*!< SYS_T::SRAM_BISTSTS: USBBEF Position   */
#define SYS_SRAM_BISTSTS_USBBEF_Msk      (0x1ul << SYS_SRAM_BISTSTS_USBBEF_Pos)            /*!< SYS_T::SRAM_BISTSTS: USBBEF Mask       */

#define SYS_SRAM_BISTSTS_SPIMBEF_Pos     (5)                                               /*!< SYS_T::SRAM_BISTSTS: SPIMBEF Position  */
#define SYS_SRAM_BISTSTS_SPIMBEF_Msk     (0x1ul << SYS_SRAM_BISTSTS_SPIMBEF_Pos)           /*!< SYS_T::SRAM_BISTSTS: SPIMBEF Mask      */

#define SYS_SRAM_BISTSTS_EMAC0BEF_Pos    (6)                                               /*!< SYS_T::SRAM_BISTSTS: EMAC0BEF Position */
#define SYS_SRAM_BISTSTS_EMAC0BEF_Msk    (0x1ul << SYS_SRAM_BISTSTS_EMAC0BEF_Pos)          /*!< SYS_T::SRAM_BISTSTS: EMAC0BEF Mask     */

#define SYS_SRAM_BISTSTS_HSUSBDBEF_Pos   (8)                                               /*!< SYS_T::SRAM_BISTSTS: HSUSBDBEF Position*/
#define SYS_SRAM_BISTSTS_HSUSBDBEF_Msk   (0x1ul << SYS_SRAM_BISTSTS_HSUSBDBEF_Pos)         /*!< SYS_T::SRAM_BISTSTS: HSUSBDBEF Mask    */

#define SYS_SRAM_BISTSTS_HSUSBHBEF_Pos   (9)                                               /*!< SYS_T::SRAM_BISTSTS: HSUSBHBEF Position*/
#define SYS_SRAM_BISTSTS_HSUSBHBEF_Msk   (0x1ul << SYS_SRAM_BISTSTS_HSUSBHBEF_Pos)         /*!< SYS_T::SRAM_BISTSTS: HSUSBHBEF Mask    */

#define SYS_SRAM_BISTSTS_SRBISTEF2_Pos   (10)                                              /*!< SYS_T::SRAM_BISTSTS: SRBISTEF2 Position*/
#define SYS_SRAM_BISTSTS_SRBISTEF2_Msk   (0x1ul << SYS_SRAM_BISTSTS_SRBISTEF2_Pos)         /*!< SYS_T::SRAM_BISTSTS: SRBISTEF2 Mask    */

#define SYS_SRAM_BISTSTS_KSBISTEF_Pos    (11)                                              /*!< SYS_T::SRAM_BISTSTS: KSBISTEF Position */
#define SYS_SRAM_BISTSTS_KSBISTEF_Msk    (0x1ul << SYS_SRAM_BISTSTS_KSBISTEF_Pos)          /*!< SYS_T::SRAM_BISTSTS: KSBISTEF Mask     */

#define SYS_SRAM_BISTSTS_CCAPBISTEF_Pos  (12)                                              /*!< SYS_T::SRAM_BISTSTS: CCAPBISTEF Position*/
#define SYS_SRAM_BISTSTS_CCAPBISTEF_Msk  (0x1ul << SYS_SRAM_BISTSTS_CCAPBISTEF_Pos)        /*!< SYS_T::SRAM_BISTSTS: CCAPBISTEF Mask   */

#define SYS_SRAM_BISTSTS_RSABISTE_Pos    (13)                                              /*!< SYS_T::SRAM_BISTSTS: RSABISTE Position */
#define SYS_SRAM_BISTSTS_RSABISTE_Msk    (0x1ul << SYS_SRAM_BISTSTS_RSABISTE_Pos)          /*!< SYS_T::SRAM_BISTSTS: RSABISTE Mask     */

#define SYS_SRAM_BISTSTS_SRBEND0_Pos     (16)                                              /*!< SYS_T::SRAM_BISTSTS: SRBEND0 Position  */
#define SYS_SRAM_BISTSTS_SRBEND0_Msk     (0x1ul << SYS_SRAM_BISTSTS_SRBEND0_Pos)           /*!< SYS_T::SRAM_BISTSTS: SRBEND0 Mask      */

#define SYS_SRAM_BISTSTS_SRBEND1_Pos     (17)                                              /*!< SYS_T::SRAM_BISTSTS: SRBEND1 Position  */
#define SYS_SRAM_BISTSTS_SRBEND1_Msk     (0x1ul << SYS_SRAM_BISTSTS_SRBEND1_Pos)           /*!< SYS_T::SRAM_BISTSTS: SRBEND1 Mask      */

#define SYS_SRAM_BISTSTS_CRBEND_Pos      (18)                                              /*!< SYS_T::SRAM_BISTSTS: CRBEND Position   */
#define SYS_SRAM_BISTSTS_CRBEND_Msk      (0x1ul << SYS_SRAM_BISTSTS_CRBEND_Pos)            /*!< SYS_T::SRAM_BISTSTS: CRBEND Mask       */

#define SYS_SRAM_BISTSTS_CANBEND_Pos     (19)                                              /*!< SYS_T::SRAM_BISTSTS: CANBEND Position  */
#define SYS_SRAM_BISTSTS_CANBEND_Msk     (0x1ul << SYS_SRAM_BISTSTS_CANBEND_Pos)           /*!< SYS_T::SRAM_BISTSTS: CANBEND Mask      */

#define SYS_SRAM_BISTSTS_USBBEND_Pos     (20)                                              /*!< SYS_T::SRAM_BISTSTS: USBBEND Position  */
#define SYS_SRAM_BISTSTS_USBBEND_Msk     (0x1ul << SYS_SRAM_BISTSTS_USBBEND_Pos)           /*!< SYS_T::SRAM_BISTSTS: USBBEND Mask      */

#define SYS_SRAM_BISTSTS_SPIMBEND_Pos    (21)                                              /*!< SYS_T::SRAM_BISTSTS: SPIMBEND Position */
#define SYS_SRAM_BISTSTS_SPIMBEND_Msk    (0x1ul << SYS_SRAM_BISTSTS_SPIMBEND_Pos)          /*!< SYS_T::SRAM_BISTSTS: SPIMBEND Mask     */

#define SYS_SRAM_BISTSTS_EMAC0BEND_Pos   (22)                                              /*!< SYS_T::SRAM_BISTSTS: EMAC0BEND Position*/
#define SYS_SRAM_BISTSTS_EMAC0BEND_Msk   (0x1ul << SYS_SRAM_BISTSTS_EMAC0BEND_Pos)         /*!< SYS_T::SRAM_BISTSTS: EMAC0BEND Mask    */

#define SYS_SRAM_BISTSTS_HSUSBDBEND_Pos  (24)                                              /*!< SYS_T::SRAM_BISTSTS: HSUSBDBEND Position*/
#define SYS_SRAM_BISTSTS_HSUSBDBEND_Msk  (0x1ul << SYS_SRAM_BISTSTS_HSUSBDBEND_Pos)        /*!< SYS_T::SRAM_BISTSTS: HSUSBDBEND Mask   */

#define SYS_SRAM_BISTSTS_HSUSBHBEND_Pos  (25)                                              /*!< SYS_T::SRAM_BISTSTS: HSUSBHBEND Position*/
#define SYS_SRAM_BISTSTS_HSUSBHBEND_Msk  (0x1ul << SYS_SRAM_BISTSTS_HSUSBHBEND_Pos)        /*!< SYS_T::SRAM_BISTSTS: HSUSBHBEND Mask   */

#define SYS_SRAM_BISTSTS_SRBEND2_Pos     (26)                                              /*!< SYS_T::SRAM_BISTSTS: SRBEND2 Position  */
#define SYS_SRAM_BISTSTS_SRBEND2_Msk     (0x1ul << SYS_SRAM_BISTSTS_SRBEND2_Pos)           /*!< SYS_T::SRAM_BISTSTS: SRBEND2 Mask      */

#define SYS_SRAM_BISTSTS_KSBEND_Pos      (27)                                              /*!< SYS_T::SRAM_BISTSTS: KSBEND Position   */
#define SYS_SRAM_BISTSTS_KSBEND_Msk      (0x1ul << SYS_SRAM_BISTSTS_KSBEND_Pos)            /*!< SYS_T::SRAM_BISTSTS: KSBEND Mask       */

#define SYS_SRAM_BISTSTS_CCAPBEND_Pos    (28)                                              /*!< SYS_T::SRAM_BISTSTS: CCAPBEND Position */
#define SYS_SRAM_BISTSTS_CCAPBEND_Msk    (0x1ul << SYS_SRAM_BISTSTS_CCAPBEND_Pos)          /*!< SYS_T::SRAM_BISTSTS: CCAPBEND Mask     */

#define SYS_SRAM_BISTSTS_RSABEND_Pos     (29)                                              /*!< SYS_T::SRAM_BISTSTS: RSABEND Position  */
#define SYS_SRAM_BISTSTS_RSABEND_Msk     (0x1ul << SYS_SRAM_BISTSTS_RSABEND_Pos)           /*!< SYS_T::SRAM_BISTSTS: RSABEND Mask      */

#define SYS_HIRCTCTL_FREQSEL_Pos         (0)                                               /*!< SYS_T::HIRCTCTL: FREQSEL Position      */
#define SYS_HIRCTCTL_FREQSEL_Msk         (0x3ul << SYS_HIRCTCTL_FREQSEL_Pos)               /*!< SYS_T::HIRCTCTL: FREQSEL Mask          */

#define SYS_HIRCTCTL_LOOPSEL_Pos         (4)                                               /*!< SYS_T::HIRCTCTL: LOOPSEL Position      */
#define SYS_HIRCTCTL_LOOPSEL_Msk         (0x3ul << SYS_HIRCTCTL_LOOPSEL_Pos)               /*!< SYS_T::HIRCTCTL: LOOPSEL Mask          */

#define SYS_HIRCTCTL_RETRYCNT_Pos        (6)                                               /*!< SYS_T::HIRCTCTL: RETRYCNT Position     */
#define SYS_HIRCTCTL_RETRYCNT_Msk        (0x3ul << SYS_HIRCTCTL_RETRYCNT_Pos)              /*!< SYS_T::HIRCTCTL: RETRYCNT Mask         */

#define SYS_HIRCTCTL_CESTOPEN_Pos        (8)                                               /*!< SYS_T::HIRCTCTL: CESTOPEN Position     */
#define SYS_HIRCTCTL_CESTOPEN_Msk        (0x1ul << SYS_HIRCTCTL_CESTOPEN_Pos)              /*!< SYS_T::HIRCTCTL: CESTOPEN Mask         */

#define SYS_HIRCTCTL_BOUNDEN_Pos         (9)                                               /*!< SYS_T::HIRCTCTL: BOUNDEN Position      */
#define SYS_HIRCTCTL_BOUNDEN_Msk         (0x1ul << SYS_HIRCTCTL_BOUNDEN_Pos)               /*!< SYS_T::HIRCTCTL: BOUNDEN Mask          */

#define SYS_HIRCTCTL_REFCKSEL_Pos        (10)                                              /*!< SYS_T::HIRCTCTL: REFCKSEL Position     */
#define SYS_HIRCTCTL_REFCKSEL_Msk        (0x1ul << SYS_HIRCTCTL_REFCKSEL_Pos)              /*!< SYS_T::HIRCTCTL: REFCKSEL Mask         */

#define SYS_HIRCTCTL_BOUNDARY_Pos        (16)                                              /*!< SYS_T::HIRCTCTL: BOUNDARY Position     */
#define SYS_HIRCTCTL_BOUNDARY_Msk        (0x1ful << SYS_HIRCTCTL_BOUNDARY_Pos)             /*!< SYS_T::HIRCTCTL: BOUNDARY Mask         */

#define SYS_HIRCTIEN_TFAILIEN_Pos        (1)                                               /*!< SYS_T::HIRCTIEN: TFAILIEN Position     */
#define SYS_HIRCTIEN_TFAILIEN_Msk        (0x1ul << SYS_HIRCTIEN_TFAILIEN_Pos)              /*!< SYS_T::HIRCTIEN: TFAILIEN Mask         */

#define SYS_HIRCTIEN_CLKEIEN_Pos         (2)                                               /*!< SYS_T::HIRCTIEN: CLKEIEN Position      */
#define SYS_HIRCTIEN_CLKEIEN_Msk         (0x1ul << SYS_HIRCTIEN_CLKEIEN_Pos)               /*!< SYS_T::HIRCTIEN: CLKEIEN Mask          */

#define SYS_HIRCTISTS_FREQLOCK_Pos       (0)                                               /*!< SYS_T::HIRCTISTS: FREQLOCK Position    */
#define SYS_HIRCTISTS_FREQLOCK_Msk       (0x1ul << SYS_HIRCTISTS_FREQLOCK_Pos)             /*!< SYS_T::HIRCTISTS: FREQLOCK Mask        */

#define SYS_HIRCTISTS_TFAILIF_Pos        (1)                                               /*!< SYS_T::HIRCTISTS: TFAILIF Position     */
#define SYS_HIRCTISTS_TFAILIF_Msk        (0x1ul << SYS_HIRCTISTS_TFAILIF_Pos)              /*!< SYS_T::HIRCTISTS: TFAILIF Mask         */

#define SYS_HIRCTISTS_CLKERRIF_Pos       (2)                                               /*!< SYS_T::HIRCTISTS: CLKERRIF Position    */
#define SYS_HIRCTISTS_CLKERRIF_Msk       (0x1ul << SYS_HIRCTISTS_CLKERRIF_Pos)             /*!< SYS_T::HIRCTISTS: CLKERRIF Mask        */

#define SYS_HIRCTISTS_OVBDIF_Pos         (3)                                               /*!< SYS_T::HIRCTISTS: OVBDIF Position      */
#define SYS_HIRCTISTS_OVBDIF_Msk         (0x1ul << SYS_HIRCTISTS_OVBDIF_Pos)               /*!< SYS_T::HIRCTISTS: OVBDIF Mask          */

#define SYS_IRCTCTL_FREQSEL_Pos          (0)                                               /*!< SYS_T::IRCTCTL: FREQSEL Position       */
#define SYS_IRCTCTL_FREQSEL_Msk          (0x3ul << SYS_IRCTCTL_FREQSEL_Pos)                /*!< SYS_T::IRCTCTL: FREQSEL Mask           */

#define SYS_IRCTCTL_LOOPSEL_Pos          (4)                                               /*!< SYS_T::IRCTCTL: LOOPSEL Position       */
#define SYS_IRCTCTL_LOOPSEL_Msk          (0x3ul << SYS_IRCTCTL_LOOPSEL_Pos)                /*!< SYS_T::IRCTCTL: LOOPSEL Mask           */

#define SYS_IRCTCTL_RETRYCNT_Pos         (6)                                               /*!< SYS_T::IRCTCTL: RETRYCNT Position      */
#define SYS_IRCTCTL_RETRYCNT_Msk         (0x3ul << SYS_IRCTCTL_RETRYCNT_Pos)               /*!< SYS_T::IRCTCTL: RETRYCNT Mask          */

#define SYS_IRCTCTL_CESTOPEN_Pos         (8)                                               /*!< SYS_T::IRCTCTL: CESTOPEN Position      */
#define SYS_IRCTCTL_CESTOPEN_Msk         (0x1ul << SYS_IRCTCTL_CESTOPEN_Pos)               /*!< SYS_T::IRCTCTL: CESTOPEN Mask          */

#define SYS_IRCTCTL_BOUNDEN_Pos          (9)                                               /*!< SYS_T::IRCTCTL: BOUNDEN Position       */
#define SYS_IRCTCTL_BOUNDEN_Msk          (0x1ul << SYS_IRCTCTL_BOUNDEN_Pos)                /*!< SYS_T::IRCTCTL: BOUNDEN Mask           */

#define SYS_IRCTCTL_REFCKSEL_Pos         (10)                                              /*!< SYS_T::IRCTCTL: REFCKSEL Position      */
#define SYS_IRCTCTL_REFCKSEL_Msk         (0x1ul << SYS_IRCTCTL_REFCKSEL_Pos)               /*!< SYS_T::IRCTCTL: REFCKSEL Mask          */

#define SYS_IRCTCTL_BOUNDARY_Pos         (16)                                              /*!< SYS_T::IRCTCTL: BOUNDARY Position      */
#define SYS_IRCTCTL_BOUNDARY_Msk         (0x1ful << SYS_IRCTCTL_BOUNDARY_Pos)              /*!< SYS_T::IRCTCTL: BOUNDARY Mask          */

#define SYS_IRCTIEN_TFAILIEN_Pos         (1)                                               /*!< SYS_T::IRCTIEN: TFAILIEN Position      */
#define SYS_IRCTIEN_TFAILIEN_Msk         (0x1ul << SYS_IRCTIEN_TFAILIEN_Pos)               /*!< SYS_T::IRCTIEN: TFAILIEN Mask          */

#define SYS_IRCTIEN_CLKEIEN_Pos          (2)                                               /*!< SYS_T::IRCTIEN: CLKEIEN Position       */
#define SYS_IRCTIEN_CLKEIEN_Msk          (0x1ul << SYS_IRCTIEN_CLKEIEN_Pos)                /*!< SYS_T::IRCTIEN: CLKEIEN Mask           */

#define SYS_IRCTISTS_FREQLOCK_Pos        (0)                                               /*!< SYS_T::IRCTISTS: FREQLOCK Position     */
#define SYS_IRCTISTS_FREQLOCK_Msk        (0x1ul << SYS_IRCTISTS_FREQLOCK_Pos)              /*!< SYS_T::IRCTISTS: FREQLOCK Mask         */

#define SYS_IRCTISTS_TFAILIF_Pos         (1)                                               /*!< SYS_T::IRCTISTS: TFAILIF Position      */
#define SYS_IRCTISTS_TFAILIF_Msk         (0x1ul << SYS_IRCTISTS_TFAILIF_Pos)               /*!< SYS_T::IRCTISTS: TFAILIF Mask          */

#define SYS_IRCTISTS_CLKERRIF_Pos        (2)                                               /*!< SYS_T::IRCTISTS: CLKERRIF Position     */
#define SYS_IRCTISTS_CLKERRIF_Msk        (0x1ul << SYS_IRCTISTS_CLKERRIF_Pos)              /*!< SYS_T::IRCTISTS: CLKERRIF Mask         */

#define SYS_IRCTISTS_OVBDIF_Pos          (3)                                               /*!< SYS_T::IRCTISTS: OVBDIF Position       */
#define SYS_IRCTISTS_OVBDIF_Msk          (0x1ul << SYS_IRCTISTS_OVBDIF_Pos)                /*!< SYS_T::IRCTISTS: OVBDIF Mask           */

#define SYS_REGLCTL_REGLCTL_Pos          (0)                                               /*!< SYS_T::REGLCTL: REGLCTL Position       */
#define SYS_REGLCTL_REGLCTL_Msk          (0xfful << SYS_REGLCTL_REGLCTL_Pos)               /*!< SYS_T::REGLCTL: REGLCTL Mask           */

#define SYS_PORDISAN_POROFFAN_Pos        (0)                                               /*!< SYS_T::PORDISAN: POROFFAN Position     */
#define SYS_PORDISAN_POROFFAN_Msk        (0xfffful << SYS_PORDISAN_POROFFAN_Pos)           /*!< SYS_T::PORDISAN: POROFFAN Mask         */

#define SYS_CSERVER_VERSION_Pos          (0)                                               /*!< SYS_T::CSERVER: VERSION Position       */
#define SYS_CSERVER_VERSION_Msk          (0xfful << SYS_CSERVER_VERSION_Pos)               /*!< SYS_T::CSERVER: VERSION Mask           */

#define SYS_PLCTL_PLSEL_Pos              (0)                                               /*!< SYS_T::PLCTL: PLSEL Position           */
#define SYS_PLCTL_PLSEL_Msk              (0x3ul << SYS_PLCTL_PLSEL_Pos)                    /*!< SYS_T::PLCTL: PLSEL Mask               */

#define SYS_PLCTL_LVSSTEP_Pos            (16)                                              /*!< SYS_T::PLCTL: LVSSTEP Position         */
#define SYS_PLCTL_LVSSTEP_Msk            (0x3ful << SYS_PLCTL_LVSSTEP_Pos)                 /*!< SYS_T::PLCTL: LVSSTEP Mask             */

#define SYS_PLCTL_LVSPRD_Pos             (24)                                              /*!< SYS_T::PLCTL: LVSPRD Position          */
#define SYS_PLCTL_LVSPRD_Msk             (0xfful << SYS_PLCTL_LVSPRD_Pos)                  /*!< SYS_T::PLCTL: LVSPRD Mask              */

#define SYS_PLSTS_PLCBUSY_Pos            (0)                                               /*!< SYS_T::PLSTS: PLCBUSY Position         */
#define SYS_PLSTS_PLCBUSY_Msk            (0x1ul << SYS_PLSTS_PLCBUSY_Pos)                  /*!< SYS_T::PLSTS: PLCBUSY Mask             */

#define SYS_PLSTS_PLSTATUS_Pos           (8)                                               /*!< SYS_T::PLSTS: PLSTATUS Position        */
#define SYS_PLSTS_PLSTATUS_Msk           (0x3ul << SYS_PLSTS_PLSTATUS_Pos)                 /*!< SYS_T::PLSTS: PLSTATUS Mask            */

#define SYS_AHBMCTL_INTACTEN_Pos         (0)                                               /*!< SYS_T::AHBMCTL: INTACTEN Position      */
#define SYS_AHBMCTL_INTACTEN_Msk         (0x1ul << SYS_AHBMCTL_INTACTEN_Pos)               /*!< SYS_T::AHBMCTL: INTACTEN Mask          */

#define SYS_GPA_MFP0_PA0MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFP0: PA0MFP Position       */
#define SYS_GPA_MFP0_PA0MFP_Msk          (0x1ful << SYS_GPA_MFP0_PA0MFP_Pos)               /*!< SYS_T::GPA_MFP0: PA0MFP Mask           */

#define SYS_GPA_MFP0_PA1MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFP0: PA1MFP Position       */
#define SYS_GPA_MFP0_PA1MFP_Msk          (0x1ful << SYS_GPA_MFP0_PA1MFP_Pos)               /*!< SYS_T::GPA_MFP0: PA1MFP Mask           */

#define SYS_GPA_MFP0_PA2MFP_Pos          (16)                                              /*!< SYS_T::GPA_MFP0: PA2MFP Position       */
#define SYS_GPA_MFP0_PA2MFP_Msk          (0x1ful << SYS_GPA_MFP0_PA2MFP_Pos)               /*!< SYS_T::GPA_MFP0: PA2MFP Mask           */

#define SYS_GPA_MFP0_PA3MFP_Pos          (24)                                              /*!< SYS_T::GPA_MFP0: PA3MFP Position       */
#define SYS_GPA_MFP0_PA3MFP_Msk          (0x1ful << SYS_GPA_MFP0_PA3MFP_Pos)               /*!< SYS_T::GPA_MFP0: PA3MFP Mask           */

#define SYS_GPA_MFP1_PA4MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFP1: PA4MFP Position       */
#define SYS_GPA_MFP1_PA4MFP_Msk          (0x1ful << SYS_GPA_MFP1_PA4MFP_Pos)               /*!< SYS_T::GPA_MFP1: PA4MFP Mask           */

#define SYS_GPA_MFP1_PA5MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFP1: PA5MFP Position       */
#define SYS_GPA_MFP1_PA5MFP_Msk          (0x1ful << SYS_GPA_MFP1_PA5MFP_Pos)               /*!< SYS_T::GPA_MFP1: PA5MFP Mask           */

#define SYS_GPA_MFP1_PA6MFP_Pos          (16)                                              /*!< SYS_T::GPA_MFP1: PA6MFP Position       */
#define SYS_GPA_MFP1_PA6MFP_Msk          (0x1ful << SYS_GPA_MFP1_PA6MFP_Pos)               /*!< SYS_T::GPA_MFP1: PA6MFP Mask           */

#define SYS_GPA_MFP1_PA7MFP_Pos          (24)                                              /*!< SYS_T::GPA_MFP1: PA7MFP Position       */
#define SYS_GPA_MFP1_PA7MFP_Msk          (0x1ful << SYS_GPA_MFP1_PA7MFP_Pos)               /*!< SYS_T::GPA_MFP1: PA7MFP Mask           */

#define SYS_GPA_MFP2_PA8MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFP2: PA8MFP Position       */
#define SYS_GPA_MFP2_PA8MFP_Msk          (0x1ful << SYS_GPA_MFP2_PA8MFP_Pos)               /*!< SYS_T::GPA_MFP2: PA8MFP Mask           */

#define SYS_GPA_MFP2_PA9MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFP2: PA9MFP Position       */
#define SYS_GPA_MFP2_PA9MFP_Msk          (0x1ful << SYS_GPA_MFP2_PA9MFP_Pos)               /*!< SYS_T::GPA_MFP2: PA9MFP Mask           */

#define SYS_GPA_MFP2_PA10MFP_Pos         (16)                                              /*!< SYS_T::GPA_MFP2: PA10MFP Position      */
#define SYS_GPA_MFP2_PA10MFP_Msk         (0x1ful << SYS_GPA_MFP2_PA10MFP_Pos)              /*!< SYS_T::GPA_MFP2: PA10MFP Mask          */

#define SYS_GPA_MFP2_PA11MFP_Pos         (24)                                              /*!< SYS_T::GPA_MFP2: PA11MFP Position      */
#define SYS_GPA_MFP2_PA11MFP_Msk         (0x1ful << SYS_GPA_MFP2_PA11MFP_Pos)              /*!< SYS_T::GPA_MFP2: PA11MFP Mask          */

#define SYS_GPA_MFP3_PA12MFP_Pos         (0)                                               /*!< SYS_T::GPA_MFP3: PA12MFP Position      */
#define SYS_GPA_MFP3_PA12MFP_Msk         (0x1ful << SYS_GPA_MFP3_PA12MFP_Pos)              /*!< SYS_T::GPA_MFP3: PA12MFP Mask          */

#define SYS_GPA_MFP3_PA13MFP_Pos         (8)                                               /*!< SYS_T::GPA_MFP3: PA13MFP Position      */
#define SYS_GPA_MFP3_PA13MFP_Msk         (0x1ful << SYS_GPA_MFP3_PA13MFP_Pos)              /*!< SYS_T::GPA_MFP3: PA13MFP Mask          */

#define SYS_GPA_MFP3_PA14MFP_Pos         (16)                                              /*!< SYS_T::GPA_MFP3: PA14MFP Position      */
#define SYS_GPA_MFP3_PA14MFP_Msk         (0x1ful << SYS_GPA_MFP3_PA14MFP_Pos)              /*!< SYS_T::GPA_MFP3: PA14MFP Mask          */

#define SYS_GPA_MFP3_PA15MFP_Pos         (24)                                              /*!< SYS_T::GPA_MFP3: PA15MFP Position      */
#define SYS_GPA_MFP3_PA15MFP_Msk         (0x1ful << SYS_GPA_MFP3_PA15MFP_Pos)              /*!< SYS_T::GPA_MFP3: PA15MFP Mask          */

#define SYS_GPB_MFP0_PB0MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFP0: PB0MFP Position       */
#define SYS_GPB_MFP0_PB0MFP_Msk          (0x1ful << SYS_GPB_MFP0_PB0MFP_Pos)               /*!< SYS_T::GPB_MFP0: PB0MFP Mask           */

#define SYS_GPB_MFP0_PB1MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFP0: PB1MFP Position       */
#define SYS_GPB_MFP0_PB1MFP_Msk          (0x1ful << SYS_GPB_MFP0_PB1MFP_Pos)               /*!< SYS_T::GPB_MFP0: PB1MFP Mask           */

#define SYS_GPB_MFP0_PB2MFP_Pos          (16)                                              /*!< SYS_T::GPB_MFP0: PB2MFP Position       */
#define SYS_GPB_MFP0_PB2MFP_Msk          (0x1ful << SYS_GPB_MFP0_PB2MFP_Pos)               /*!< SYS_T::GPB_MFP0: PB2MFP Mask           */

#define SYS_GPB_MFP0_PB3MFP_Pos          (24)                                              /*!< SYS_T::GPB_MFP0: PB3MFP Position       */
#define SYS_GPB_MFP0_PB3MFP_Msk          (0x1ful << SYS_GPB_MFP0_PB3MFP_Pos)               /*!< SYS_T::GPB_MFP0: PB3MFP Mask           */

#define SYS_GPB_MFP1_PB4MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFP1: PB4MFP Position       */
#define SYS_GPB_MFP1_PB4MFP_Msk          (0x1ful << SYS_GPB_MFP1_PB4MFP_Pos)               /*!< SYS_T::GPB_MFP1: PB4MFP Mask           */

#define SYS_GPB_MFP1_PB5MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFP1: PB5MFP Position       */
#define SYS_GPB_MFP1_PB5MFP_Msk          (0x1ful << SYS_GPB_MFP1_PB5MFP_Pos)               /*!< SYS_T::GPB_MFP1: PB5MFP Mask           */

#define SYS_GPB_MFP1_PB6MFP_Pos          (16)                                              /*!< SYS_T::GPB_MFP1: PB6MFP Position       */
#define SYS_GPB_MFP1_PB6MFP_Msk          (0x1ful << SYS_GPB_MFP1_PB6MFP_Pos)               /*!< SYS_T::GPB_MFP1: PB6MFP Mask           */

#define SYS_GPB_MFP1_PB7MFP_Pos          (24)                                              /*!< SYS_T::GPB_MFP1: PB7MFP Position       */
#define SYS_GPB_MFP1_PB7MFP_Msk          (0x1ful << SYS_GPB_MFP1_PB7MFP_Pos)               /*!< SYS_T::GPB_MFP1: PB7MFP Mask           */

#define SYS_GPB_MFP2_PB8MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFP2: PB8MFP Position       */
#define SYS_GPB_MFP2_PB8MFP_Msk          (0x1ful << SYS_GPB_MFP2_PB8MFP_Pos)               /*!< SYS_T::GPB_MFP2: PB8MFP Mask           */

#define SYS_GPB_MFP2_PB9MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFP2: PB9MFP Position       */
#define SYS_GPB_MFP2_PB9MFP_Msk          (0x1ful << SYS_GPB_MFP2_PB9MFP_Pos)               /*!< SYS_T::GPB_MFP2: PB9MFP Mask           */

#define SYS_GPB_MFP2_PB10MFP_Pos         (16)                                              /*!< SYS_T::GPB_MFP2: PB10MFP Position      */
#define SYS_GPB_MFP2_PB10MFP_Msk         (0x1ful << SYS_GPB_MFP2_PB10MFP_Pos)              /*!< SYS_T::GPB_MFP2: PB10MFP Mask          */

#define SYS_GPB_MFP2_PB11MFP_Pos         (24)                                              /*!< SYS_T::GPB_MFP2: PB11MFP Position      */
#define SYS_GPB_MFP2_PB11MFP_Msk         (0x1ful << SYS_GPB_MFP2_PB11MFP_Pos)              /*!< SYS_T::GPB_MFP2: PB11MFP Mask          */

#define SYS_GPB_MFP3_PB12MFP_Pos         (0)                                               /*!< SYS_T::GPB_MFP3: PB12MFP Position      */
#define SYS_GPB_MFP3_PB12MFP_Msk         (0x1ful << SYS_GPB_MFP3_PB12MFP_Pos)              /*!< SYS_T::GPB_MFP3: PB12MFP Mask          */

#define SYS_GPB_MFP3_PB13MFP_Pos         (8)                                               /*!< SYS_T::GPB_MFP3: PB13MFP Position      */
#define SYS_GPB_MFP3_PB13MFP_Msk         (0x1ful << SYS_GPB_MFP3_PB13MFP_Pos)              /*!< SYS_T::GPB_MFP3: PB13MFP Mask          */

#define SYS_GPB_MFP3_PB14MFP_Pos         (16)                                              /*!< SYS_T::GPB_MFP3: PB14MFP Position      */
#define SYS_GPB_MFP3_PB14MFP_Msk         (0x1ful << SYS_GPB_MFP3_PB14MFP_Pos)              /*!< SYS_T::GPB_MFP3: PB14MFP Mask          */

#define SYS_GPB_MFP3_PB15MFP_Pos         (24)                                              /*!< SYS_T::GPB_MFP3: PB15MFP Position      */
#define SYS_GPB_MFP3_PB15MFP_Msk         (0x1ful << SYS_GPB_MFP3_PB15MFP_Pos)              /*!< SYS_T::GPB_MFP3: PB15MFP Mask          */

#define SYS_GPC_MFP0_PC0MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFP0: PC0MFP Position       */
#define SYS_GPC_MFP0_PC0MFP_Msk          (0x1ful << SYS_GPC_MFP0_PC0MFP_Pos)               /*!< SYS_T::GPC_MFP0: PC0MFP Mask           */

#define SYS_GPC_MFP0_PC1MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFP0: PC1MFP Position       */
#define SYS_GPC_MFP0_PC1MFP_Msk          (0x1ful << SYS_GPC_MFP0_PC1MFP_Pos)               /*!< SYS_T::GPC_MFP0: PC1MFP Mask           */

#define SYS_GPC_MFP0_PC2MFP_Pos          (16)                                              /*!< SYS_T::GPC_MFP0: PC2MFP Position       */
#define SYS_GPC_MFP0_PC2MFP_Msk          (0x1ful << SYS_GPC_MFP0_PC2MFP_Pos)               /*!< SYS_T::GPC_MFP0: PC2MFP Mask           */

#define SYS_GPC_MFP0_PC3MFP_Pos          (24)                                              /*!< SYS_T::GPC_MFP0: PC3MFP Position       */
#define SYS_GPC_MFP0_PC3MFP_Msk          (0x1ful << SYS_GPC_MFP0_PC3MFP_Pos)               /*!< SYS_T::GPC_MFP0: PC3MFP Mask           */

#define SYS_GPC_MFP1_PC4MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFP1: PC4MFP Position       */
#define SYS_GPC_MFP1_PC4MFP_Msk          (0x1ful << SYS_GPC_MFP1_PC4MFP_Pos)               /*!< SYS_T::GPC_MFP1: PC4MFP Mask           */

#define SYS_GPC_MFP1_PC5MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFP1: PC5MFP Position       */
#define SYS_GPC_MFP1_PC5MFP_Msk          (0x1ful << SYS_GPC_MFP1_PC5MFP_Pos)               /*!< SYS_T::GPC_MFP1: PC5MFP Mask           */

#define SYS_GPC_MFP1_PC6MFP_Pos          (16)                                              /*!< SYS_T::GPC_MFP1: PC6MFP Position       */
#define SYS_GPC_MFP1_PC6MFP_Msk          (0x1ful << SYS_GPC_MFP1_PC6MFP_Pos)               /*!< SYS_T::GPC_MFP1: PC6MFP Mask           */

#define SYS_GPC_MFP1_PC7MFP_Pos          (24)                                              /*!< SYS_T::GPC_MFP1: PC7MFP Position       */
#define SYS_GPC_MFP1_PC7MFP_Msk          (0x1ful << SYS_GPC_MFP1_PC7MFP_Pos)               /*!< SYS_T::GPC_MFP1: PC7MFP Mask           */

#define SYS_GPC_MFP2_PC8MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFP2: PC8MFP Position       */
#define SYS_GPC_MFP2_PC8MFP_Msk          (0x1ful << SYS_GPC_MFP2_PC8MFP_Pos)               /*!< SYS_T::GPC_MFP2: PC8MFP Mask           */

#define SYS_GPC_MFP2_PC9MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFP2: PC9MFP Position       */
#define SYS_GPC_MFP2_PC9MFP_Msk          (0x1ful << SYS_GPC_MFP2_PC9MFP_Pos)               /*!< SYS_T::GPC_MFP2: PC9MFP Mask           */

#define SYS_GPC_MFP2_PC10MFP_Pos         (16)                                              /*!< SYS_T::GPC_MFP2: PC10MFP Position      */
#define SYS_GPC_MFP2_PC10MFP_Msk         (0x1ful << SYS_GPC_MFP2_PC10MFP_Pos)              /*!< SYS_T::GPC_MFP2: PC10MFP Mask          */

#define SYS_GPC_MFP2_PC11MFP_Pos         (24)                                              /*!< SYS_T::GPC_MFP2: PC11MFP Position      */
#define SYS_GPC_MFP2_PC11MFP_Msk         (0x1ful << SYS_GPC_MFP2_PC11MFP_Pos)              /*!< SYS_T::GPC_MFP2: PC11MFP Mask          */

#define SYS_GPC_MFP3_PC12MFP_Pos         (0)                                               /*!< SYS_T::GPC_MFP3: PC12MFP Position      */
#define SYS_GPC_MFP3_PC12MFP_Msk         (0x1ful << SYS_GPC_MFP3_PC12MFP_Pos)              /*!< SYS_T::GPC_MFP3: PC12MFP Mask          */

#define SYS_GPC_MFP3_PC13MFP_Pos         (8)                                               /*!< SYS_T::GPC_MFP3: PC13MFP Position      */
#define SYS_GPC_MFP3_PC13MFP_Msk         (0x1ful << SYS_GPC_MFP3_PC13MFP_Pos)              /*!< SYS_T::GPC_MFP3: PC13MFP Mask          */

#define SYS_GPC_MFP3_PC14MFP_Pos         (16)                                              /*!< SYS_T::GPC_MFP3: PC14MFP Position      */
#define SYS_GPC_MFP3_PC14MFP_Msk         (0x1ful << SYS_GPC_MFP3_PC14MFP_Pos)              /*!< SYS_T::GPC_MFP3: PC14MFP Mask          */

#define SYS_GPD_MFP0_PD0MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFP0: PD0MFP Position       */
#define SYS_GPD_MFP0_PD0MFP_Msk          (0x1ful << SYS_GPD_MFP0_PD0MFP_Pos)               /*!< SYS_T::GPD_MFP0: PD0MFP Mask           */

#define SYS_GPD_MFP0_PD1MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFP0: PD1MFP Position       */
#define SYS_GPD_MFP0_PD1MFP_Msk          (0x1ful << SYS_GPD_MFP0_PD1MFP_Pos)               /*!< SYS_T::GPD_MFP0: PD1MFP Mask           */

#define SYS_GPD_MFP0_PD2MFP_Pos          (16)                                              /*!< SYS_T::GPD_MFP0: PD2MFP Position       */
#define SYS_GPD_MFP0_PD2MFP_Msk          (0x1ful << SYS_GPD_MFP0_PD2MFP_Pos)               /*!< SYS_T::GPD_MFP0: PD2MFP Mask           */

#define SYS_GPD_MFP0_PD3MFP_Pos          (24)                                              /*!< SYS_T::GPD_MFP0: PD3MFP Position       */
#define SYS_GPD_MFP0_PD3MFP_Msk          (0x1ful << SYS_GPD_MFP0_PD3MFP_Pos)               /*!< SYS_T::GPD_MFP0: PD3MFP Mask           */

#define SYS_GPD_MFP1_PD4MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFP1: PD4MFP Position       */
#define SYS_GPD_MFP1_PD4MFP_Msk          (0x1ful << SYS_GPD_MFP1_PD4MFP_Pos)               /*!< SYS_T::GPD_MFP1: PD4MFP Mask           */

#define SYS_GPD_MFP1_PD5MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFP1: PD5MFP Position       */
#define SYS_GPD_MFP1_PD5MFP_Msk          (0x1ful << SYS_GPD_MFP1_PD5MFP_Pos)               /*!< SYS_T::GPD_MFP1: PD5MFP Mask           */

#define SYS_GPD_MFP1_PD6MFP_Pos          (16)                                              /*!< SYS_T::GPD_MFP1: PD6MFP Position       */
#define SYS_GPD_MFP1_PD6MFP_Msk          (0x1ful << SYS_GPD_MFP1_PD6MFP_Pos)               /*!< SYS_T::GPD_MFP1: PD6MFP Mask           */

#define SYS_GPD_MFP1_PD7MFP_Pos          (24)                                              /*!< SYS_T::GPD_MFP1: PD7MFP Position       */
#define SYS_GPD_MFP1_PD7MFP_Msk          (0x1ful << SYS_GPD_MFP1_PD7MFP_Pos)               /*!< SYS_T::GPD_MFP1: PD7MFP Mask           */

#define SYS_GPD_MFP2_PD8MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFP2: PD8MFP Position       */
#define SYS_GPD_MFP2_PD8MFP_Msk          (0x1ful << SYS_GPD_MFP2_PD8MFP_Pos)               /*!< SYS_T::GPD_MFP2: PD8MFP Mask           */

#define SYS_GPD_MFP2_PD9MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFP2: PD9MFP Position       */
#define SYS_GPD_MFP2_PD9MFP_Msk          (0x1ful << SYS_GPD_MFP2_PD9MFP_Pos)               /*!< SYS_T::GPD_MFP2: PD9MFP Mask           */

#define SYS_GPD_MFP2_PD10MFP_Pos         (16)                                              /*!< SYS_T::GPD_MFP2: PD10MFP Position      */
#define SYS_GPD_MFP2_PD10MFP_Msk         (0x1ful << SYS_GPD_MFP2_PD10MFP_Pos)              /*!< SYS_T::GPD_MFP2: PD10MFP Mask          */

#define SYS_GPD_MFP2_PD11MFP_Pos         (24)                                              /*!< SYS_T::GPD_MFP2: PD11MFP Position      */
#define SYS_GPD_MFP2_PD11MFP_Msk         (0x1ful << SYS_GPD_MFP2_PD11MFP_Pos)              /*!< SYS_T::GPD_MFP2: PD11MFP Mask          */

#define SYS_GPD_MFP3_PD12MFP_Pos         (0)                                               /*!< SYS_T::GPD_MFP3: PD12MFP Position      */
#define SYS_GPD_MFP3_PD12MFP_Msk         (0x1ful << SYS_GPD_MFP3_PD12MFP_Pos)              /*!< SYS_T::GPD_MFP3: PD12MFP Mask          */

#define SYS_GPD_MFP3_PD13MFP_Pos         (8)                                               /*!< SYS_T::GPD_MFP3: PD13MFP Position      */
#define SYS_GPD_MFP3_PD13MFP_Msk         (0x1ful << SYS_GPD_MFP3_PD13MFP_Pos)              /*!< SYS_T::GPD_MFP3: PD13MFP Mask          */

#define SYS_GPD_MFP3_PD14MFP_Pos         (16)                                              /*!< SYS_T::GPD_MFP3: PD14MFP Position      */
#define SYS_GPD_MFP3_PD14MFP_Msk         (0x1ful << SYS_GPD_MFP3_PD14MFP_Pos)              /*!< SYS_T::GPD_MFP3: PD14MFP Mask          */

#define SYS_GPE_MFP0_PE0MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFP0: PE0MFP Position       */
#define SYS_GPE_MFP0_PE0MFP_Msk          (0x1ful << SYS_GPE_MFP0_PE0MFP_Pos)               /*!< SYS_T::GPE_MFP0: PE0MFP Mask           */

#define SYS_GPE_MFP0_PE1MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFP0: PE1MFP Position       */
#define SYS_GPE_MFP0_PE1MFP_Msk          (0x1ful << SYS_GPE_MFP0_PE1MFP_Pos)               /*!< SYS_T::GPE_MFP0: PE1MFP Mask           */

#define SYS_GPE_MFP0_PE2MFP_Pos          (16)                                              /*!< SYS_T::GPE_MFP0: PE2MFP Position       */
#define SYS_GPE_MFP0_PE2MFP_Msk          (0x1ful << SYS_GPE_MFP0_PE2MFP_Pos)               /*!< SYS_T::GPE_MFP0: PE2MFP Mask           */

#define SYS_GPE_MFP0_PE3MFP_Pos          (24)                                              /*!< SYS_T::GPE_MFP0: PE3MFP Position       */
#define SYS_GPE_MFP0_PE3MFP_Msk          (0x1ful << SYS_GPE_MFP0_PE3MFP_Pos)               /*!< SYS_T::GPE_MFP0: PE3MFP Mask           */

#define SYS_GPE_MFP1_PE4MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFP1: PE4MFP Position       */
#define SYS_GPE_MFP1_PE4MFP_Msk          (0x1ful << SYS_GPE_MFP1_PE4MFP_Pos)               /*!< SYS_T::GPE_MFP1: PE4MFP Mask           */

#define SYS_GPE_MFP1_PE5MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFP1: PE5MFP Position       */
#define SYS_GPE_MFP1_PE5MFP_Msk          (0x1ful << SYS_GPE_MFP1_PE5MFP_Pos)               /*!< SYS_T::GPE_MFP1: PE5MFP Mask           */

#define SYS_GPE_MFP1_PE6MFP_Pos          (16)                                              /*!< SYS_T::GPE_MFP1: PE6MFP Position       */
#define SYS_GPE_MFP1_PE6MFP_Msk          (0x1ful << SYS_GPE_MFP1_PE6MFP_Pos)               /*!< SYS_T::GPE_MFP1: PE6MFP Mask           */

#define SYS_GPE_MFP1_PE7MFP_Pos          (24)                                              /*!< SYS_T::GPE_MFP1: PE7MFP Position       */
#define SYS_GPE_MFP1_PE7MFP_Msk          (0x1ful << SYS_GPE_MFP1_PE7MFP_Pos)               /*!< SYS_T::GPE_MFP1: PE7MFP Mask           */

#define SYS_GPE_MFP2_PE8MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFP2: PE8MFP Position       */
#define SYS_GPE_MFP2_PE8MFP_Msk          (0x1ful << SYS_GPE_MFP2_PE8MFP_Pos)               /*!< SYS_T::GPE_MFP2: PE8MFP Mask           */

#define SYS_GPE_MFP2_PE9MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFP2: PE9MFP Position       */
#define SYS_GPE_MFP2_PE9MFP_Msk          (0x1ful << SYS_GPE_MFP2_PE9MFP_Pos)               /*!< SYS_T::GPE_MFP2: PE9MFP Mask           */

#define SYS_GPE_MFP2_PE10MFP_Pos         (16)                                              /*!< SYS_T::GPE_MFP2: PE10MFP Position      */
#define SYS_GPE_MFP2_PE10MFP_Msk         (0x1ful << SYS_GPE_MFP2_PE10MFP_Pos)              /*!< SYS_T::GPE_MFP2: PE10MFP Mask          */

#define SYS_GPE_MFP2_PE11MFP_Pos         (24)                                              /*!< SYS_T::GPE_MFP2: PE11MFP Position      */
#define SYS_GPE_MFP2_PE11MFP_Msk         (0x1ful << SYS_GPE_MFP2_PE11MFP_Pos)              /*!< SYS_T::GPE_MFP2: PE11MFP Mask          */

#define SYS_GPE_MFP3_PE12MFP_Pos         (0)                                               /*!< SYS_T::GPE_MFP3: PE12MFP Position      */
#define SYS_GPE_MFP3_PE12MFP_Msk         (0x1ful << SYS_GPE_MFP3_PE12MFP_Pos)              /*!< SYS_T::GPE_MFP3: PE12MFP Mask          */

#define SYS_GPE_MFP3_PE13MFP_Pos         (8)                                               /*!< SYS_T::GPE_MFP3: PE13MFP Position      */
#define SYS_GPE_MFP3_PE13MFP_Msk         (0x1ful << SYS_GPE_MFP3_PE13MFP_Pos)              /*!< SYS_T::GPE_MFP3: PE13MFP Mask          */

#define SYS_GPE_MFP3_PE14MFP_Pos         (16)                                              /*!< SYS_T::GPE_MFP3: PE14MFP Position      */
#define SYS_GPE_MFP3_PE14MFP_Msk         (0x1ful << SYS_GPE_MFP3_PE14MFP_Pos)              /*!< SYS_T::GPE_MFP3: PE14MFP Mask          */

#define SYS_GPE_MFP3_PE15MFP_Pos         (24)                                              /*!< SYS_T::GPE_MFP3: PE15MFP Position      */
#define SYS_GPE_MFP3_PE15MFP_Msk         (0x1ful << SYS_GPE_MFP3_PE15MFP_Pos)              /*!< SYS_T::GPE_MFP3: PE15MFP Mask          */

#define SYS_GPF_MFP0_PF0MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFP0: PF0MFP Position       */
#define SYS_GPF_MFP0_PF0MFP_Msk          (0x1ful << SYS_GPF_MFP0_PF0MFP_Pos)               /*!< SYS_T::GPF_MFP0: PF0MFP Mask           */

#define SYS_GPF_MFP0_PF1MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFP0: PF1MFP Position       */
#define SYS_GPF_MFP0_PF1MFP_Msk          (0x1ful << SYS_GPF_MFP0_PF1MFP_Pos)               /*!< SYS_T::GPF_MFP0: PF1MFP Mask           */

#define SYS_GPF_MFP0_PF2MFP_Pos          (16)                                              /*!< SYS_T::GPF_MFP0: PF2MFP Position       */
#define SYS_GPF_MFP0_PF2MFP_Msk          (0x1ful << SYS_GPF_MFP0_PF2MFP_Pos)               /*!< SYS_T::GPF_MFP0: PF2MFP Mask           */

#define SYS_GPF_MFP0_PF3MFP_Pos          (24)                                              /*!< SYS_T::GPF_MFP0: PF3MFP Position       */
#define SYS_GPF_MFP0_PF3MFP_Msk          (0x1ful << SYS_GPF_MFP0_PF3MFP_Pos)               /*!< SYS_T::GPF_MFP0: PF3MFP Mask           */

#define SYS_GPF_MFP1_PF4MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFP1: PF4MFP Position       */
#define SYS_GPF_MFP1_PF4MFP_Msk          (0x1ful << SYS_GPF_MFP1_PF4MFP_Pos)               /*!< SYS_T::GPF_MFP1: PF4MFP Mask           */

#define SYS_GPF_MFP1_PF5MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFP1: PF5MFP Position       */
#define SYS_GPF_MFP1_PF5MFP_Msk          (0x1ful << SYS_GPF_MFP1_PF5MFP_Pos)               /*!< SYS_T::GPF_MFP1: PF5MFP Mask           */

#define SYS_GPF_MFP1_PF6MFP_Pos          (16)                                              /*!< SYS_T::GPF_MFP1: PF6MFP Position       */
#define SYS_GPF_MFP1_PF6MFP_Msk          (0x1ful << SYS_GPF_MFP1_PF6MFP_Pos)               /*!< SYS_T::GPF_MFP1: PF6MFP Mask           */

#define SYS_GPF_MFP1_PF7MFP_Pos          (24)                                              /*!< SYS_T::GPF_MFP1: PF7MFP Position       */
#define SYS_GPF_MFP1_PF7MFP_Msk          (0x1ful << SYS_GPF_MFP1_PF7MFP_Pos)               /*!< SYS_T::GPF_MFP1: PF7MFP Mask           */

#define SYS_GPF_MFP2_PF8MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFP2: PF8MFP Position       */
#define SYS_GPF_MFP2_PF8MFP_Msk          (0x1ful << SYS_GPF_MFP2_PF8MFP_Pos)               /*!< SYS_T::GPF_MFP2: PF8MFP Mask           */

#define SYS_GPF_MFP2_PF9MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFP2: PF9MFP Position       */
#define SYS_GPF_MFP2_PF9MFP_Msk          (0x1ful << SYS_GPF_MFP2_PF9MFP_Pos)               /*!< SYS_T::GPF_MFP2: PF9MFP Mask           */

#define SYS_GPF_MFP2_PF10MFP_Pos         (16)                                              /*!< SYS_T::GPF_MFP2: PF10MFP Position      */
#define SYS_GPF_MFP2_PF10MFP_Msk         (0x1ful << SYS_GPF_MFP2_PF10MFP_Pos)              /*!< SYS_T::GPF_MFP2: PF10MFP Mask          */

#define SYS_GPF_MFP2_PF11MFP_Pos         (24)                                              /*!< SYS_T::GPF_MFP2: PF11MFP Position      */
#define SYS_GPF_MFP2_PF11MFP_Msk         (0x1ful << SYS_GPF_MFP2_PF11MFP_Pos)              /*!< SYS_T::GPF_MFP2: PF11MFP Mask          */

#define SYS_GPG_MFP0_PG0MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFP0: PG0MFP Position       */
#define SYS_GPG_MFP0_PG0MFP_Msk          (0x1ful << SYS_GPG_MFP0_PG0MFP_Pos)               /*!< SYS_T::GPG_MFP0: PG0MFP Mask           */

#define SYS_GPG_MFP0_PG1MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFP0: PG1MFP Position       */
#define SYS_GPG_MFP0_PG1MFP_Msk          (0x1ful << SYS_GPG_MFP0_PG1MFP_Pos)               /*!< SYS_T::GPG_MFP0: PG1MFP Mask           */

#define SYS_GPG_MFP0_PG2MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFP0: PG2MFP Position       */
#define SYS_GPG_MFP0_PG2MFP_Msk          (0x1ful << SYS_GPG_MFP0_PG2MFP_Pos)               /*!< SYS_T::GPG_MFP0: PG2MFP Mask           */

#define SYS_GPG_MFP0_PG3MFP_Pos          (24)                                              /*!< SYS_T::GPG_MFP0: PG3MFP Position       */
#define SYS_GPG_MFP0_PG3MFP_Msk          (0x1ful << SYS_GPG_MFP0_PG3MFP_Pos)               /*!< SYS_T::GPG_MFP0: PG3MFP Mask           */

#define SYS_GPG_MFP1_PG4MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFP1: PG4MFP Position       */
#define SYS_GPG_MFP1_PG4MFP_Msk          (0x1ful << SYS_GPG_MFP1_PG4MFP_Pos)               /*!< SYS_T::GPG_MFP1: PG4MFP Mask           */

#define SYS_GPG_MFP1_PG5MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFP1: PG5MFP Position       */
#define SYS_GPG_MFP1_PG5MFP_Msk          (0x1ful << SYS_GPG_MFP1_PG5MFP_Pos)               /*!< SYS_T::GPG_MFP1: PG5MFP Mask           */

#define SYS_GPG_MFP1_PG6MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFP1: PG6MFP Position       */
#define SYS_GPG_MFP1_PG6MFP_Msk          (0x1ful << SYS_GPG_MFP1_PG6MFP_Pos)               /*!< SYS_T::GPG_MFP1: PG6MFP Mask           */

#define SYS_GPG_MFP1_PG7MFP_Pos          (24)                                              /*!< SYS_T::GPG_MFP1: PG7MFP Position       */
#define SYS_GPG_MFP1_PG7MFP_Msk          (0x1ful << SYS_GPG_MFP1_PG7MFP_Pos)               /*!< SYS_T::GPG_MFP1: PG7MFP Mask           */

#define SYS_GPG_MFP2_PG8MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFP2: PG8MFP Position       */
#define SYS_GPG_MFP2_PG8MFP_Msk          (0x1ful << SYS_GPG_MFP2_PG8MFP_Pos)               /*!< SYS_T::GPG_MFP2: PG8MFP Mask           */

#define SYS_GPG_MFP2_PG9MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFP2: PG9MFP Position       */
#define SYS_GPG_MFP2_PG9MFP_Msk          (0x1ful << SYS_GPG_MFP2_PG9MFP_Pos)               /*!< SYS_T::GPG_MFP2: PG9MFP Mask           */

#define SYS_GPG_MFP2_PG10MFP_Pos         (16)                                              /*!< SYS_T::GPG_MFP2: PG10MFP Position      */
#define SYS_GPG_MFP2_PG10MFP_Msk         (0x1ful << SYS_GPG_MFP2_PG10MFP_Pos)              /*!< SYS_T::GPG_MFP2: PG10MFP Mask          */

#define SYS_GPG_MFP2_PG11MFP_Pos         (24)                                              /*!< SYS_T::GPG_MFP2: PG11MFP Position      */
#define SYS_GPG_MFP2_PG11MFP_Msk         (0x1ful << SYS_GPG_MFP2_PG11MFP_Pos)              /*!< SYS_T::GPG_MFP2: PG11MFP Mask          */

#define SYS_GPG_MFP3_PG12MFP_Pos         (0)                                               /*!< SYS_T::GPG_MFP3: PG12MFP Position      */
#define SYS_GPG_MFP3_PG12MFP_Msk         (0x1ful << SYS_GPG_MFP3_PG12MFP_Pos)              /*!< SYS_T::GPG_MFP3: PG12MFP Mask          */

#define SYS_GPG_MFP3_PG13MFP_Pos         (8)                                               /*!< SYS_T::GPG_MFP3: PG13MFP Position      */
#define SYS_GPG_MFP3_PG13MFP_Msk         (0x1ful << SYS_GPG_MFP3_PG13MFP_Pos)              /*!< SYS_T::GPG_MFP3: PG13MFP Mask          */

#define SYS_GPG_MFP3_PG14MFP_Pos         (16)                                              /*!< SYS_T::GPG_MFP3: PG14MFP Position      */
#define SYS_GPG_MFP3_PG14MFP_Msk         (0x1ful << SYS_GPG_MFP3_PG14MFP_Pos)              /*!< SYS_T::GPG_MFP3: PG14MFP Mask          */

#define SYS_GPG_MFP3_PG15MFP_Pos         (24)                                              /*!< SYS_T::GPG_MFP3: PG15MFP Position      */
#define SYS_GPG_MFP3_PG15MFP_Msk         (0x1ful << SYS_GPG_MFP3_PG15MFP_Pos)              /*!< SYS_T::GPG_MFP3: PG15MFP Mask          */

#define SYS_GPH_MFP0_PH0MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFP0: PH0MFP Position       */
#define SYS_GPH_MFP0_PH0MFP_Msk          (0x1ful << SYS_GPH_MFP0_PH0MFP_Pos)               /*!< SYS_T::GPH_MFP0: PH0MFP Mask           */

#define SYS_GPH_MFP0_PH1MFP_Pos          (8)                                               /*!< SYS_T::GPH_MFP0: PH1MFP Position       */
#define SYS_GPH_MFP0_PH1MFP_Msk          (0x1ful << SYS_GPH_MFP0_PH1MFP_Pos)               /*!< SYS_T::GPH_MFP0: PH1MFP Mask           */

#define SYS_GPH_MFP0_PH2MFP_Pos          (16)                                              /*!< SYS_T::GPH_MFP0: PH2MFP Position       */
#define SYS_GPH_MFP0_PH2MFP_Msk          (0x1ful << SYS_GPH_MFP0_PH2MFP_Pos)               /*!< SYS_T::GPH_MFP0: PH2MFP Mask           */

#define SYS_GPH_MFP0_PH3MFP_Pos          (24)                                              /*!< SYS_T::GPH_MFP0: PH3MFP Position       */
#define SYS_GPH_MFP0_PH3MFP_Msk          (0x1ful << SYS_GPH_MFP0_PH3MFP_Pos)               /*!< SYS_T::GPH_MFP0: PH3MFP Mask           */

#define SYS_GPH_MFP1_PH4MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFP1: PH4MFP Position       */
#define SYS_GPH_MFP1_PH4MFP_Msk          (0x1ful << SYS_GPH_MFP1_PH4MFP_Pos)               /*!< SYS_T::GPH_MFP1: PH4MFP Mask           */

#define SYS_GPH_MFP1_PH5MFP_Pos          (8)                                               /*!< SYS_T::GPH_MFP1: PH5MFP Position       */
#define SYS_GPH_MFP1_PH5MFP_Msk          (0x1ful << SYS_GPH_MFP1_PH5MFP_Pos)               /*!< SYS_T::GPH_MFP1: PH5MFP Mask           */

#define SYS_GPH_MFP1_PH6MFP_Pos          (16)                                              /*!< SYS_T::GPH_MFP1: PH6MFP Position       */
#define SYS_GPH_MFP1_PH6MFP_Msk          (0x1ful << SYS_GPH_MFP1_PH6MFP_Pos)               /*!< SYS_T::GPH_MFP1: PH6MFP Mask           */

#define SYS_GPH_MFP1_PH7MFP_Pos          (24)                                              /*!< SYS_T::GPH_MFP1: PH7MFP Position       */
#define SYS_GPH_MFP1_PH7MFP_Msk          (0x1ful << SYS_GPH_MFP1_PH7MFP_Pos)               /*!< SYS_T::GPH_MFP1: PH7MFP Mask           */

#define SYS_GPH_MFP2_PH8MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFP2: PH8MFP Position       */
#define SYS_GPH_MFP2_PH8MFP_Msk          (0x1ful << SYS_GPH_MFP2_PH8MFP_Pos)               /*!< SYS_T::GPH_MFP2: PH8MFP Mask           */

#define SYS_GPH_MFP2_PH9MFP_Pos          (8)                                               /*!< SYS_T::GPH_MFP2: PH9MFP Position       */
#define SYS_GPH_MFP2_PH9MFP_Msk          (0x1ful << SYS_GPH_MFP2_PH9MFP_Pos)               /*!< SYS_T::GPH_MFP2: PH9MFP Mask           */

#define SYS_GPH_MFP2_PH10MFP_Pos         (16)                                              /*!< SYS_T::GPH_MFP2: PH10MFP Position      */
#define SYS_GPH_MFP2_PH10MFP_Msk         (0x1ful << SYS_GPH_MFP2_PH10MFP_Pos)              /*!< SYS_T::GPH_MFP2: PH10MFP Mask          */

#define SYS_GPH_MFP2_PH11MFP_Pos         (24)                                              /*!< SYS_T::GPH_MFP2: PH11MFP Position      */
#define SYS_GPH_MFP2_PH11MFP_Msk         (0x1ful << SYS_GPH_MFP2_PH11MFP_Pos)              /*!< SYS_T::GPH_MFP2: PH11MFP Mask          */

#define SYS_GPH_MFP3_PH12MFP_Pos         (0)                                               /*!< SYS_T::GPH_MFP3: PH12MFP Position      */
#define SYS_GPH_MFP3_PH12MFP_Msk         (0x1ful << SYS_GPH_MFP3_PH12MFP_Pos)              /*!< SYS_T::GPH_MFP3: PH12MFP Mask          */

#define SYS_GPH_MFP3_PH13MFP_Pos         (8)                                               /*!< SYS_T::GPH_MFP3: PH13MFP Position      */
#define SYS_GPH_MFP3_PH13MFP_Msk         (0x1ful << SYS_GPH_MFP3_PH13MFP_Pos)              /*!< SYS_T::GPH_MFP3: PH13MFP Mask          */

#define SYS_GPH_MFP3_PH14MFP_Pos         (16)                                              /*!< SYS_T::GPH_MFP3: PH14MFP Position      */
#define SYS_GPH_MFP3_PH14MFP_Msk         (0x1ful << SYS_GPH_MFP3_PH14MFP_Pos)              /*!< SYS_T::GPH_MFP3: PH14MFP Mask          */

#define SYS_GPH_MFP3_PH15MFP_Pos         (24)                                              /*!< SYS_T::GPH_MFP3: PH15MFP Position      */
#define SYS_GPH_MFP3_PH15MFP_Msk         (0x1ful << SYS_GPH_MFP3_PH15MFP_Pos)              /*!< SYS_T::GPH_MFP3: PH15MFP Mask          */

#define SYS_GPI_MFP1_PI6MFP_Pos          (16)                                              /*!< SYS_T::GPI_MFP1: PI6MFP Position       */
#define SYS_GPI_MFP1_PI6MFP_Msk          (0x1ful << SYS_GPI_MFP1_PI6MFP_Pos)               /*!< SYS_T::GPI_MFP1: PI6MFP Mask           */

#define SYS_GPI_MFP1_PI7MFP_Pos          (24)                                              /*!< SYS_T::GPI_MFP1: PI7MFP Position       */
#define SYS_GPI_MFP1_PI7MFP_Msk          (0x1ful << SYS_GPI_MFP1_PI7MFP_Pos)               /*!< SYS_T::GPI_MFP1: PI7MFP Mask           */

#define SYS_GPI_MFP2_PI8MFP_Pos          (0)                                               /*!< SYS_T::GPI_MFP2: PI8MFP Position       */
#define SYS_GPI_MFP2_PI8MFP_Msk          (0x1ful << SYS_GPI_MFP2_PI8MFP_Pos)               /*!< SYS_T::GPI_MFP2: PI8MFP Mask           */

#define SYS_GPI_MFP2_PI9MFP_Pos          (8)                                               /*!< SYS_T::GPI_MFP2: PI9MFP Position       */
#define SYS_GPI_MFP2_PI9MFP_Msk          (0x1ful << SYS_GPI_MFP2_PI9MFP_Pos)               /*!< SYS_T::GPI_MFP2: PI9MFP Mask           */

#define SYS_GPI_MFP2_PI10MFP_Pos         (16)                                              /*!< SYS_T::GPI_MFP2: PI10MFP Position      */
#define SYS_GPI_MFP2_PI10MFP_Msk         (0x1ful << SYS_GPI_MFP2_PI10MFP_Pos)              /*!< SYS_T::GPI_MFP2: PI10MFP Mask          */

#define SYS_GPI_MFP2_PI11MFP_Pos         (24)                                              /*!< SYS_T::GPI_MFP2: PI11MFP Position      */
#define SYS_GPI_MFP2_PI11MFP_Msk         (0x1ful << SYS_GPI_MFP2_PI11MFP_Pos)              /*!< SYS_T::GPI_MFP2: PI11MFP Mask          */

#define SYS_GPI_MFP3_PI12MFP_Pos         (0)                                               /*!< SYS_T::GPI_MFP3: PI12MFP Position      */
#define SYS_GPI_MFP3_PI12MFP_Msk         (0x1ful << SYS_GPI_MFP3_PI12MFP_Pos)              /*!< SYS_T::GPI_MFP3: PI12MFP Mask          */

#define SYS_GPI_MFP3_PI13MFP_Pos         (8)                                               /*!< SYS_T::GPI_MFP3: PI13MFP Position      */
#define SYS_GPI_MFP3_PI13MFP_Msk         (0x1ful << SYS_GPI_MFP3_PI13MFP_Pos)              /*!< SYS_T::GPI_MFP3: PI13MFP Mask          */

#define SYS_GPI_MFP3_PI14MFP_Pos         (16)                                              /*!< SYS_T::GPI_MFP3: PI14MFP Position      */
#define SYS_GPI_MFP3_PI14MFP_Msk         (0x1ful << SYS_GPI_MFP3_PI14MFP_Pos)              /*!< SYS_T::GPI_MFP3: PI14MFP Mask          */

#define SYS_GPI_MFP3_PI15MFP_Pos         (24)                                              /*!< SYS_T::GPI_MFP3: PI15MFP Position      */
#define SYS_GPI_MFP3_PI15MFP_Msk         (0x1ful << SYS_GPI_MFP3_PI15MFP_Pos)              /*!< SYS_T::GPI_MFP3: PI15MFP Mask          */

#define SYS_GPJ_MFP0_PJ0MFP_Pos          (0)                                               /*!< SYS_T::GPJ_MFP0: PJ0MFP Position       */
#define SYS_GPJ_MFP0_PJ0MFP_Msk          (0x1ful << SYS_GPJ_MFP0_PJ0MFP_Pos)               /*!< SYS_T::GPJ_MFP0: PJ0MFP Mask           */

#define SYS_GPJ_MFP0_PJ1MFP_Pos          (8)                                               /*!< SYS_T::GPJ_MFP0: PJ1MFP Position       */
#define SYS_GPJ_MFP0_PJ1MFP_Msk          (0x1ful << SYS_GPJ_MFP0_PJ1MFP_Pos)               /*!< SYS_T::GPJ_MFP0: PJ1MFP Mask           */

#define SYS_GPJ_MFP0_PJ2MFP_Pos          (16)                                              /*!< SYS_T::GPJ_MFP0: PJ2MFP Position       */
#define SYS_GPJ_MFP0_PJ2MFP_Msk          (0x1ful << SYS_GPJ_MFP0_PJ2MFP_Pos)               /*!< SYS_T::GPJ_MFP0: PJ2MFP Mask           */

#define SYS_GPJ_MFP0_PJ3MFP_Pos          (24)                                              /*!< SYS_T::GPJ_MFP0: PJ3MFP Position       */
#define SYS_GPJ_MFP0_PJ3MFP_Msk          (0x1ful << SYS_GPJ_MFP0_PJ3MFP_Pos)               /*!< SYS_T::GPJ_MFP0: PJ3MFP Mask           */

#define SYS_GPJ_MFP1_PJ4MFP_Pos          (0)                                               /*!< SYS_T::GPJ_MFP1: PJ4MFP Position       */
#define SYS_GPJ_MFP1_PJ4MFP_Msk          (0x1ful << SYS_GPJ_MFP1_PJ4MFP_Pos)               /*!< SYS_T::GPJ_MFP1: PJ4MFP Mask           */

#define SYS_GPJ_MFP1_PJ5MFP_Pos          (8)                                               /*!< SYS_T::GPJ_MFP1: PJ5MFP Position       */
#define SYS_GPJ_MFP1_PJ5MFP_Msk          (0x1ful << SYS_GPJ_MFP1_PJ5MFP_Pos)               /*!< SYS_T::GPJ_MFP1: PJ5MFP Mask           */

#define SYS_GPJ_MFP1_PJ6MFP_Pos          (16)                                              /*!< SYS_T::GPJ_MFP1: PJ6MFP Position       */
#define SYS_GPJ_MFP1_PJ6MFP_Msk          (0x1ful << SYS_GPJ_MFP1_PJ6MFP_Pos)               /*!< SYS_T::GPJ_MFP1: PJ6MFP Mask           */

#define SYS_GPJ_MFP1_PJ7MFP_Pos          (24)                                              /*!< SYS_T::GPJ_MFP1: PJ7MFP Position       */
#define SYS_GPJ_MFP1_PJ7MFP_Msk          (0x1ful << SYS_GPJ_MFP1_PJ7MFP_Pos)               /*!< SYS_T::GPJ_MFP1: PJ7MFP Mask           */

#define SYS_GPJ_MFP2_PJ8MFP_Pos          (0)                                               /*!< SYS_T::GPJ_MFP2: PJ8MFP Position       */
#define SYS_GPJ_MFP2_PJ8MFP_Msk          (0x1ful << SYS_GPJ_MFP2_PJ8MFP_Pos)               /*!< SYS_T::GPJ_MFP2: PJ8MFP Mask           */

#define SYS_GPJ_MFP2_PJ9MFP_Pos          (8)                                               /*!< SYS_T::GPJ_MFP2: PJ9MFP Position       */
#define SYS_GPJ_MFP2_PJ9MFP_Msk          (0x1ful << SYS_GPJ_MFP2_PJ9MFP_Pos)               /*!< SYS_T::GPJ_MFP2: PJ9MFP Mask           */

#define SYS_GPJ_MFP2_PJ10MFP_Pos         (16)                                              /*!< SYS_T::GPJ_MFP2: PJ10MFP Position      */
#define SYS_GPJ_MFP2_PJ10MFP_Msk         (0x1ful << SYS_GPJ_MFP2_PJ10MFP_Pos)              /*!< SYS_T::GPJ_MFP2: PJ10MFP Mask          */

#define SYS_GPJ_MFP2_PJ11MFP_Pos         (24)                                              /*!< SYS_T::GPJ_MFP2: PJ11MFP Position      */
#define SYS_GPJ_MFP2_PJ11MFP_Msk         (0x1ful << SYS_GPJ_MFP2_PJ11MFP_Pos)              /*!< SYS_T::GPJ_MFP2: PJ11MFP Mask          */

#define SYS_GPJ_MFP3_PJ12MFP_Pos         (0)                                               /*!< SYS_T::GPJ_MFP3: PJ12MFP Position      */
#define SYS_GPJ_MFP3_PJ12MFP_Msk         (0x1ful << SYS_GPJ_MFP3_PJ12MFP_Pos)              /*!< SYS_T::GPJ_MFP3: PJ12MFP Mask          */

#define SYS_GPJ_MFP3_PJ13MFP_Pos         (8)                                               /*!< SYS_T::GPJ_MFP3: PJ13MFP Position      */
#define SYS_GPJ_MFP3_PJ13MFP_Msk         (0x1ful << SYS_GPJ_MFP3_PJ13MFP_Pos)              /*!< SYS_T::GPJ_MFP3: PJ13MFP Mask          */

/**@}*/ /* SYS_CONST */
/**@}*/ /* end of SYS register group */

/**
    @addtogroup NMI NMI Controller (NMI)
    Memory Mapped Structure for NMI Controller
@{ */

typedef struct
{


    /**
     * @var NMI_T::NMIEN
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
     * |[3]     |SRAMPERR  |SRAM Parity Check NMI Source Enable (Write Protect)
     * |        |          |0 = SRAM parity check error NMI source Disabled.
     * |        |          |1 = SRAM parity check error NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |CLKFAIL   |Clock Fail Detected and IRC Auto Trim Interrupt NMI Source Enable (Write Protect)
     * |        |          |0 = Clock fail detected interrupt NMI source Disabled.
     * |        |          |1 = Clock fail detected interrupt NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |RTCINT    |RTC NMI Source Enable (Write Protect)
     * |        |          |0 = RTC NMI source Disabled.
     * |        |          |1 = RTC NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |TAMPERINT |TAMPER NMI Source Enable (Write Protect)
     * |        |          |0 = Backup register tamper detected NMI source Disabled.
     * |        |          |1 = Backup register tamper detected NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[8]     |EINT0     |External Interrupt from INT0 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT0 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT0 pins NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[9]     |EINT1     |External Interrupt from INT1 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT1 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT1 pins NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[10]    |EINT2     |External Interrupt rrom INT2 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT2 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT2 pins NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[11]    |EINT3     |External Interrupt from INT3 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT3 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT3 pins pin NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12]    |EINT4     |External Interrupt from INT4 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT4 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT4 pins NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[13]    |EINT5     |External Interrupt from INT5 Pins NMI Source Enable (Write Protect)
     * |        |          |0 = External interrupt from INT5 pins NMI source Disabled.
     * |        |          |1 = External interrupt from INT5 pins NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[14]    |UART0INT  |UART0 NMI Source Enable (Write Protect)
     * |        |          |0 = UART0 NMI source Disabled.
     * |        |          |1 = UART0 NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[15]    |UART1INT  |UART1 NMI Source Enable (Write Protect)
     * |        |          |0 = UART1 NMI source Disabled.
     * |        |          |1 = UART1 NMI source Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var NMI_T::NMISTS
     * Offset: 0x04  NMI Source Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BODOUT    |BOD Interrupt Flag (Read Only)
     * |        |          |0 = BOD interrupt is deasserted.
     * |        |          |1 = BOD interrupt is asserted.
     * |[1]     |IRCINT    |IRC TRIM Interrupt Flag (Read Only)
     * |        |          |0 = IRC TRIM interrupt is deasserted.
     * |        |          |1 = IRC TRIM interrupt is asserted.
     * |[2]     |PWRWUINT  |Power-down Mode Wake-up Interrupt Flag (Read Only)
     * |        |          |0 = Power-down mode wake-up interrupt is deasserted.
     * |        |          |1 = Power-down mode wake-up interrupt is asserted.
     * |[3]     |SRAMPERR  |SRAM Parity Check Error Interrupt Flag (Read Only)
     * |        |          |0 = SRAM parity check error interrupt is deasserted.
     * |        |          |1 = SRAM parity check error interrupt is asserted.
     * |[4]     |CLKFAIL   |Clock Fail Detected or IRC Auto Trim Interrupt Flag (Read Only)
     * |        |          |0 = Clock fail detected interrupt is deasserted.
     * |        |          |1 = Clock fail detected interrupt is asserted.
     * |[6]     |RTCINT    |RTC Interrupt Flag (Read Only)
     * |        |          |0 = RTC interrupt is deasserted.
     * |        |          |1 = RTC interrupt is asserted.
     * |[7]     |TAMPERINT |TAMPER Interrupt Flag (Read Only)
     * |        |          |0 = Backup register tamper detected interrupt is deasserted.
     * |        |          |1 = Backup register tamper detected interrupt is asserted.
     * |[8]     |EINT0     |External Interrupt from INT0 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT0 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT0 interrupt is asserted.
     * |[9]     |EINT1     |External Interrupt from INT1 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT1 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT1 interrupt is asserted.
     * |[10]    |EINT2     |External Interrupt from INT2 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT2 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT2 interrupt is asserted.
     * |[11]    |EINT3     |External Interrupt from INT3 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT3 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT3 interrupt is asserted.
     * |[12]    |EINT4     |External Interrupt from INT4 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT4 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT4 interrupt is asserted.
     * |[13]    |EINT5     |External Interrupt from INT5 Pins Interrupt Flag (Read Only)
     * |        |          |0 = External Interrupt from INT5 interrupt is deasserted.
     * |        |          |1 = External Interrupt from INT5 interrupt is asserted.
     * |[14]    |UART0INT  |UART0 Interrupt Flag (Read Only)
     * |        |          |0 = UART1 interrupt is deasserted.
     * |        |          |1 = UART1 interrupt is asserted.
     * |[15]    |UART1INT  |UART1 Interrupt Flag (Read Only)
     * |        |          |0 = UART1 interrupt is deasserted.
     * |        |          |1 = UART1 interrupt is asserted.
     */
    __IO uint32_t NMIEN;                 /*!< [0x0000] NMI Source Interrupt Enable Register                             */
    __I  uint32_t NMISTS;                /*!< [0x0004] NMI Source Interrupt Status Register                             */

} NMI_T;

/**
    @addtogroup NMI_CONST NMI Bit Field Definition
    Constant Definitions for NMI Controller
@{ */

#define NMI_NMIEN_BODOUT_Pos             (0)                                               /*!< NMI_T::NMIEN: BODOUT Position          */
#define NMI_NMIEN_BODOUT_Msk             (0x1ul << NMI_NMIEN_BODOUT_Pos)                   /*!< NMI_T::NMIEN: BODOUT Mask              */

#define NMI_NMIEN_IRCINT_Pos             (1)                                               /*!< NMI_T::NMIEN: IRCINT Position          */
#define NMI_NMIEN_IRCINT_Msk             (0x1ul << NMI_NMIEN_IRCINT_Pos)                   /*!< NMI_T::NMIEN: IRCINT Mask              */

#define NMI_NMIEN_PWRWUINT_Pos           (2)                                               /*!< NMI_T::NMIEN: PWRWUINT Position        */
#define NMI_NMIEN_PWRWUINT_Msk           (0x1ul << NMI_NMIEN_PWRWUINT_Pos)                 /*!< NMI_T::NMIEN: PWRWUINT Mask            */

#define NMI_NMIEN_SRAMPERR_Pos           (3)                                               /*!< NMI_T::NMIEN: SRAMPERR Position        */
#define NMI_NMIEN_SRAMPERR_Msk           (0x1ul << NMI_NMIEN_SRAMPERR_Pos)                 /*!< NMI_T::NMIEN: SRAMPERR Mask            */

#define NMI_NMIEN_CLKFAIL_Pos            (4)                                               /*!< NMI_T::NMIEN: CLKFAIL Position         */
#define NMI_NMIEN_CLKFAIL_Msk            (0x1ul << NMI_NMIEN_CLKFAIL_Pos)                  /*!< NMI_T::NMIEN: CLKFAIL Mask             */

#define NMI_NMIEN_RTCINT_Pos             (6)                                               /*!< NMI_T::NMIEN: RTCINT Position          */
#define NMI_NMIEN_RTCINT_Msk             (0x1ul << NMI_NMIEN_RTCINT_Pos)                   /*!< NMI_T::NMIEN: RTCINT Mask              */

#define NMI_NMIEN_TAMPERINT_Pos          (7)                                               /*!< NMI_T::NMIEN: TAMPERINT Position       */
#define NMI_NMIEN_TAMPERINT_Msk          (0x1ul << NMI_NMIEN_TAMPERINT_Pos)                /*!< NMI_T::NMIEN: TAMPERINT Mask           */

#define NMI_NMIEN_EINT0_Pos              (8)                                               /*!< NMI_T::NMIEN: EINT0 Position           */
#define NMI_NMIEN_EINT0_Msk              (0x1ul << NMI_NMIEN_EINT0_Pos)                    /*!< NMI_T::NMIEN: EINT0 Mask               */

#define NMI_NMIEN_EINT1_Pos              (9)                                               /*!< NMI_T::NMIEN: EINT1 Position           */
#define NMI_NMIEN_EINT1_Msk              (0x1ul << NMI_NMIEN_EINT1_Pos)                    /*!< NMI_T::NMIEN: EINT1 Mask               */

#define NMI_NMIEN_EINT2_Pos              (10)                                              /*!< NMI_T::NMIEN: EINT2 Position           */
#define NMI_NMIEN_EINT2_Msk              (0x1ul << NMI_NMIEN_EINT2_Pos)                    /*!< NMI_T::NMIEN: EINT2 Mask               */

#define NMI_NMIEN_EINT3_Pos              (11)                                              /*!< NMI_T::NMIEN: EINT3 Position           */
#define NMI_NMIEN_EINT3_Msk              (0x1ul << NMI_NMIEN_EINT3_Pos)                    /*!< NMI_T::NMIEN: EINT3 Mask               */

#define NMI_NMIEN_EINT4_Pos              (12)                                              /*!< NMI_T::NMIEN: EINT4 Position           */
#define NMI_NMIEN_EINT4_Msk              (0x1ul << NMI_NMIEN_EINT4_Pos)                    /*!< NMI_T::NMIEN: EINT4 Mask               */

#define NMI_NMIEN_EINT5_Pos              (13)                                              /*!< NMI_T::NMIEN: EINT5 Position           */
#define NMI_NMIEN_EINT5_Msk              (0x1ul << NMI_NMIEN_EINT5_Pos)                    /*!< NMI_T::NMIEN: EINT5 Mask               */

#define NMI_NMIEN_UART0INT_Pos           (14)                                              /*!< NMI_T::NMIEN: UART0INT Position        */
#define NMI_NMIEN_UART0INT_Msk           (0x1ul << NMI_NMIEN_UART0INT_Pos)                 /*!< NMI_T::NMIEN: UART0INT Mask            */

#define NMI_NMIEN_UART1INT_Pos           (15)                                              /*!< NMI_T::NMIEN: UART1INT Position        */
#define NMI_NMIEN_UART1INT_Msk           (0x1ul << NMI_NMIEN_UART1INT_Pos)                 /*!< NMI_T::NMIEN: UART1INT Mask            */

#define NMI_NMISTS_BODOUT_Pos            (0)                                               /*!< NMI_T::NMISTS: BODOUT Position         */
#define NMI_NMISTS_BODOUT_Msk            (0x1ul << NMI_NMISTS_BODOUT_Pos)                  /*!< NMI_T::NMISTS: BODOUT Mask             */

#define NMI_NMISTS_IRCINT_Pos            (1)                                               /*!< NMI_T::NMISTS: IRCINT Position        */
#define NMI_NMISTS_IRCINT_Msk            (0x1ul << NMI_NMISTS_IRC_NT_Pos)                  /*!< NMI_T::NMISTS: IRCINT Mask            */

#define NMI_NMISTS_PWRWUINT_Pos          (2)                                               /*!< NMI_T::NMISTS: PWRWUINT Position       */
#define NMI_NMISTS_PWRWUINT_Msk          (0x1ul << NMI_NMISTS_PWRWUINT_Pos)                /*!< NMI_T::NMISTS: PWRWUINT Mask           */

#define NMI_NMISTS_SRAMPERR_Pos          (3)                                               /*!< NMI_T::NMISTS: SRAMPERR Position       */
#define NMI_NMISTS_SRAMPERR_Msk          (0x1ul << NMI_NMISTS_SRAMPERR_Pos)                /*!< NMI_T::NMISTS: SRAMPERR Mask           */

#define NMI_NMISTS_CLKFAIL_Pos           (4)                                               /*!< NMI_T::NMISTS: CLKFAIL Position        */
#define NMI_NMISTS_CLKFAIL_Msk           (0x1ul << NMI_NMISTS_CLKFAIL_Pos)                 /*!< NMI_T::NMISTS: CLKFAIL Mask            */

#define NMI_NMISTS_RTCINT_Pos            (6)                                               /*!< NMI_T::NMISTS: RTCINT Position         */
#define NMI_NMISTS_RTCINT_Msk            (0x1ul << NMI_NMISTS_RTCINT_Pos)                  /*!< NMI_T::NMISTS: RTCINT Mask             */

#define NMI_NMISTS_TAMPERINT_Pos         (7)                                               /*!< NMI_T::NMISTS: TAMPERINT Position      */
#define NMI_NMISTS_TAMPERINT_Msk         (0x1ul << NMI_NMISTS_TAMPERINT_Pos)               /*!< NMI_T::NMISTS: TAMPERINT Mask          */

#define NMI_NMISTS_EINT0_Pos             (8)                                               /*!< NMI_T::NMISTS: EINT0 Position          */
#define NMI_NMISTS_EINT0_Msk             (0x1ul << NMI_NMISTS_EINT0_Pos)                   /*!< NMI_T::NMISTS: EINT0 Mask              */

#define NMI_NMISTS_EINT1_Pos             (9)                                               /*!< NMI_T::NMISTS: EINT1 Position          */
#define NMI_NMISTS_EINT1_Msk             (0x1ul << NMI_NMISTS_EINT1_Pos)                   /*!< NMI_T::NMISTS: EINT1 Mask              */

#define NMI_NMISTS_EINT2_Pos             (10)                                              /*!< NMI_T::NMISTS: EINT2 Position          */
#define NMI_NMISTS_EINT2_Msk             (0x1ul << NMI_NMISTS_EINT2_Pos)                   /*!< NMI_T::NMISTS: EINT2 Mask              */

#define NMI_NMISTS_EINT3_Pos             (11)                                              /*!< NMI_T::NMISTS: EINT3 Position          */
#define NMI_NMISTS_EINT3_Msk             (0x1ul << NMI_NMISTS_EINT3_Pos)                   /*!< NMI_T::NMISTS: EINT3 Mask              */

#define NMI_NMISTS_EINT4_Pos             (12)                                              /*!< NMI_T::NMISTS: EINT4 Position          */
#define NMI_NMISTS_EINT4_Msk             (0x1ul << NMI_NMISTS_EINT4_Pos)                   /*!< NMI_T::NMISTS: EINT4 Mask              */

#define NMI_NMISTS_EINT5_Pos             (13)                                              /*!< NMI_T::NMISTS: EINT5 Position          */
#define NMI_NMISTS_EINT5_Msk             (0x1ul << NMI_NMISTS_EINT5_Pos)                   /*!< NMI_T::NMISTS: EINT5 Mask              */

#define NMI_NMISTS_UART0INT_Pos          (14)                                              /*!< NMI_T::NMISTS: UART0INT Position       */
#define NMI_NMISTS_UART0INT_Msk          (0x1ul << NMI_NMISTS_UART0INT_Pos)                /*!< NMI_T::NMISTS: UART0INT Mask           */

#define NMI_NMISTS_UART1INT_Pos          (15)                                              /*!< NMI_T::NMISTS: UART1INT Position       */
#define NMI_NMISTS_UART1INT_Msk          (0x1ul << NMI_NMISTS_UART1INT_Pos)                /*!< NMI_T::NMISTS: UART1INT Mask           */

/**@}*/ /* NMI_CONST */
/**@}*/ /* end of NMI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __SYS_REG_H__ */
