/**************************************************************************//**
 * @file     sys_reg.h
 * @brief    SYS register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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

/**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
@{ */

typedef struct
{


    /**
     * @var SYS_T::PDID
     * Offset: 0x00  Product and Device Identifier Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PID       |Product ID
     * |        |          |This field stores the 16-bit Product ID loaded from OTP memory.
     * |[27:16] |DID       |Device ID
     * |        |          |This field stores the 8-bit Device ID loaded from OTP memory.
     * @var SYS_T::PWRONOTP
     * Offset: 0x04  Power-on Setting OTP Source Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWRONSRC  |Power on Setting Source Control (Read Only)
     * |        |          |0 = Power on setting values come from pin. (Default)
     * |        |          |1 = Power on setting values come from OTP.
     * |[1]     |QSPI0CKSEL|QSPI0_CLK Frequency Selection (Read Only)
     * |        |          |0 = QSPI0_CLK frequency is 30 MHz.
     * |        |          |1 = QSPI0_CLK frequency is 50 MHz.
     * |        |          |Note: The value of WDT0ON latched from OTP when pin nRESET transited from low to high.
     * |[2]     |WDT0ON    |Watchdog Timer 0 ON/OFF Selection (Read Only)
     * |        |          |0 = After power-on, WDT 0 Disabled.
     * |        |          |1 = after power-on WDT 0 Enabled.
     * |        |          |Note: The value of WDT0ON latched from OTP when pin nRESET transited from low to high.
     * |[4]     |UR0DBGDIS |UART 0 Debug Message Output Disable Bit (Read Only)
     * |        |          |0= UART 0 debug message output Enabled.
     * |        |          |1= UART 0 debug message output Disabled.
     * |        |          |Note: The value of UR0DBGDIS latched from OTP when pin nRESET transited from low to high.
     * |[5]     |SD0BKEN   |SD0 Back Up Boot Enable Bit (Read Only)
     * |        |          |0 = SD0 back up boot Disabled (Default).
     * |        |          |1 = SD0 back up boot Enabled.
     * |        |          |Note: SD0BKEN didn't take effect if BTSRCSEL= 01 and BTOPTION = 00..
     * |[11:10] |BTSRCSEL  |Boot Source Selection (Read Only)
     * |        |          |00 = Boot from SPI Flash (Default).
     * |        |          |01 = Boot from SD/eMMC.
     * |        |          |10 = Boot from NAND Flash.
     * |        |          |11 = Boot from USB.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[3:2] latched to BTSRCSEL when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of BTSRCSEL latched from OTP's BTSRCSEL.
     * |[13:12] |NPAGESEL  |NAND Flash Page Size Selection (Read Only)
     * |        |          |00 = NAND Flash page size is 2 KB.
     * |        |          |01 = NAND Flash page size is 4 KB.
     * |        |          |10 = NAND Flash page size is 8 KB.
     * |        |          |11 = Ignore.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[5:4] latched to NPAGSEL when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of NPAGSEL latched from OTP's BTNANDPS.
     * |[15:14] |MISCCFG   |Miscellaneous Configuration (Read Only)
     * |        |          |If BTSRCSEL = 01, boot from SD/eMMC.
     * |        |          |MISCCFG[0]:
     * |        |          |0 = SD0/eMMC0 booting. (Default)
     * |        |          |1 = SD1/eMMC1 booting.
     * |        |          |MISCCFG[1]:
     * |        |          |0 = eMMC 4-bit booting. (Default)
     * |        |          |1 = eMMC 8-bit booting.00 = SD0/eMMC0 booting (Default).
     * |        |          |01 = SD1/eMMC1 booting.
     * |        |          |10 = SD1/eMMC1 booting.
     * |        |          |11 = SD1/eMMC1 booting.
     * |        |          |If BTSRCSEL = 10, boot from NAND Flash.
     * |        |          |00 = No ECC (Default).
     * |        |          |01 = ECC is BCH T12.
     * |        |          |10 = ECC is BCH T24.
     * |        |          |11 = Ignore.
     * |        |          |If BTSRCSEL = 00, the Boot from SPI Flash.
     * |        |          |00 = SPI-NAND Flash with 1-bit mode booting (Default).
     * |        |          |01 = SPI-NAND Flash with 4-bit mode booting.
     * |        |          |10 = SPI-NOR Flash with 1-bit mode booting.
     * |        |          |11 = SPI-NOR Flash with 4-bit mode booting.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[7:6] latched to MISCCFG when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of MISCCFG latched from OTP's BTOPTION.
     * |[16]    |USBP0ID   |USB Port 0 ID Pin Status
     * |        |          |0= USB port 0 used as a USB device.
     * |        |          |1= USB port 0 used as a USB host.
     * |[31:24] |SECBTPSWD |Secure Boot Disable Password (Read Only)
     * |        |          |If SECBTPSWD is 0x5A, the secure boot Disabled.
     * |        |          |Note 1: SECBTPSWD didn't take effect and PG[0] used as Secure Boot Disable if PWRONSRC = 0.
     * |        |          |Note 2: In RMA mode, SECBTPSWD didn't take effect and PG[0] used as Secure Boot Disable.
     * @var SYS_T::PWRONPIN
     * Offset: 0x08  Power-on Setting Pin Source Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SECBTDIS  |Secure Boot Disable Bit (Read Only)
     * |        |          |0 = Secure Boot Enabled (Default).
     * |        |          |1 = Secure Boot Disabled.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[0] latched to SECBTDIS when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of SECBTDIS latched from OTP's SECBTDIS.
     * |[3:2]   |BTSRCSEL  |Boot Source Selection (Read Only)
     * |        |          |00 = Boot from SPI Flash (Default).
     * |        |          |01 = Boot from SD/eMMC.
     * |        |          |10 = Boot from NAND Flash.
     * |        |          |11 = Boot from USB.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[3:2] latched to BTSRCSEL when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of BTSRCSEL latched from OTP's BTSRCSEL.
     * |[5:4]   |NPAGESEL  |NAND Flash Page Size Selection (Read Only)
     * |        |          |00 = NAND Flash page size is 2 KB.
     * |        |          |01 = NAND Flash page size is 4 KB.
     * |        |          |10 = NAND Flash page size is 8 KB.
     * |        |          |11 = Ignore.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[5:4] latched to NPAGSEL when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of NPAGSEL latched from OTP's BTNANDPS.
     * |[7:6]   |MISCCFG   |Miscellaneous Configuration (Read Only)
     * |        |          |If BTSRCSEL = 01, boot from SD/eMMC.
     * |        |          |MISCCFG[0]:
     * |        |          |0 = SD0/eMMC0 booting. (Default)
     * |        |          |1 = SD1/eMMC1 booting.
     * |        |          |MISCCFG[1]:
     * |        |          |0 = eMMC 4-bit booting. (Default)
     * |        |          |1 = eMMC 8-bit booting.00 = SD0/eMMC0 booting (Default).
     * |        |          |01 = SD1/eMMC1 booting.
     * |        |          |10 = SD1/eMMC1 booting.
     * |        |          |11 = SD1/eMMC1 booting.
     * |        |          |If BTSRCSEL = 10, boot from NAND Flash.
     * |        |          |00 = No ECC (Default).
     * |        |          |01 = ECC is BCH T12.
     * |        |          |10 = ECC is BCH T24.
     * |        |          |11 = Ignore.
     * |        |          |If BTSRCSEL = 00, the Boot from SPI Flash.
     * |        |          |00 = SPI-NAND Flash with 1-bit mode booting (Default).
     * |        |          |01 = SPI-NAND Flash with 4-bit mode booting.
     * |        |          |10 = SPI-NOR Flash with 1-bit mode booting.
     * |        |          |11 = SPI-NOR Flash with 4-bit mode booting.
     * |        |          |Note: If PWRONSRC = 0, the value of pin PG[7:6] latched to MISCCFG when pin nRESET transited from low to high
     * |        |          |If PWRONSRC = 1, the value of MISCCFG latched from OTP's BTOPTION.
     * @var SYS_T::RSTSTS
     * Offset: 0x10  Reset Source Active Status Register (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PORF      |POR Reset Flag
     * |        |          |0 = No reset from POR.
     * |        |          |1 = POR had issued reset signal to reset the chip.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |PINRF     |NRESET Pin Reset Flag
     * |        |          |0 = No reset from nRESET pin.
     * |        |          |1 = nRESET pin had issued reset signal to reset the chip.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[2]     |WDT0RF    |WDT 0 Reset Flag
     * |        |          |The WDT 0 reset flag is set by the "Reset Signal" from the Watchdog Timer 0 or Window Watchdog Timer 0 to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer 0 or window watchdog timer 0.
     * |        |          |1 = The watchdog timer 0 or window watchdog timer 0 had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer 0 register RSTF(WDT0_CTL[2]) bit is set if the system has been reset by WDT 0 time-out reset
     * |        |          |Window Watchdog Timer 0 register WWDTRF(WWDT0_STATUS[1]) bit is set if the system has been reset by WWDT 0 time-out reset.
     * |[3]     |LVRF      |LVR Reset Flag
     * |        |          |The LVR reset flag is set by the "Reset Signal" from the Low Voltage Reset Controller to indicate the previous reset source.
     * |        |          |0 = No reset from LVR.
     * |        |          |1 = LVR had issued reset signal to reset the chip.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |CPU0DBGRF |Cortex-A35 Core 0 Debug Reset Flag
     * |        |          |The Cortex-A35 core 0 debug reset flag is set by the "Reset Signal" from DBGRSTREQ of Cortex-A35 core 0 to indicate the previous reset source.
     * |        |          |0 = No reset from DBGRSTREQ of Cortex-A35 core 0.
     * |        |          |1 = The Cortex-A35 core 0 had issued DBGRSTREQ reset signal to reset itself.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |CPU0WARMRF|Cortex-A35 Core 0 Warm Reset Flag
     * |        |          |The Cortex-A35 core 0 warm reset flag is set by the "Reset Signal" from WARMRSTREQ of Cortex-A35 core 0 to indicate the previous reset source
     * |        |          |The WARMRSTREQ of Cortex-A35 core 0 trigger by writing 1 to the bit RR (RMR[1], Reset Management Register of Cortex-A35 core 0)
     * |        |          |0 = No reset from WARMRSTREQ of Cortex-A35 core 0.
     * |        |          |1 = The Cortex-A35 core 0 had issued WARMRSTREQ reset signal to reset itself.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[6]     |HRESETRF  |HRESET Reset Flag
     * |        |          |The HRESET reset flag is set by the "Reset Signal" from the HRESET.
     * |        |          |0 = No reset from HRESET.
     * |        |          |1 = Reset from HRESET.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[7]     |CPU0RF    |CPU 0 Reset Flag
     * |        |          |The CPU 0 reset flag is set by hardware if software writes CA35CR0RST (SYS_IPRST0[1]) 1 to reset Cortex-A35 Core 0.
     * |        |          |0 = No reset to CPU.
     * |        |          |1 = The Cortex-A35 Core 0 is reset by software setting CA35CR0RST (SYS_IPRST0[1]) to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[10]    |WDT1RF    |WDT 1 Reset Flag
     * |        |          |The WDT 1 reset flag is set by the "Reset Signal" from the Watchdog Timer 1 or Window Watchdog Timer 1 to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer 1 or window watchdog timer 1.
     * |        |          |1 = The watchdog timer 1 or window watchdog timer 1 had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer 1 register RSTF (WDT1_CTL[2]) bit is set if the system has been reset by WDT 1 time-out reset
     * |        |          |Window Watchdog Timer 1 register WWDTRF (WWDT1_STATUS[1]) bit is set if the system has been reset by WWDT 1 time-out reset.
     * |        |          |Note 3: This flag only take effect when WDT1RSTAEN (SYS_MISCRFCR[16]) is 1.
     * |[11]    |WDT2RFA   |WDT 2 Reset Flag for Cortex-A35
     * |        |          |The WDT 2 reset flag is set by the "Reset Signal" from the Watchdog Timer 2 or Window Watchdog Timer 2 to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer 2 or window watchdog timer 2.
     * |        |          |1 = The watchdog timer 2 or window watchdog timer 2 had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer 2 register RSTF(WDT2_CTL[2]) bit is set if the system has been reset by WDT 2 time-out reset
     * |        |          |Window Watchdog Timer 2 register WWDTRF(WWDT2_STATUS[1]) bit is set if the system has been reset by WWDT 2 time-out reset.
     * |        |          |Note 3: This flag only take effect when WDT2RSTAEN (SYS_MISCRFCR[17]) is 1.
     * |[12]    |CPU1DBGRF |Cortex-A35 Core 1 Debug Reset Flag
     * |        |          |The Cortex-A35 core 1 debug reset flag is set by the "Reset Signal" from DBGRSTREQ of Cortex-A35 core 1 to indicate the previous reset source.
     * |        |          |0 = No reset from DBGRSTREQ of Cortex-A35 core 1.
     * |        |          |1 = The Cortex-A35 core 1 had issued DBGRSTREQ reset signal to reset itself.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[13]    |CPU1WARMRF|Cortex-A35 Core 1 Warm Reset Flag
     * |        |          |The Cortex-A35 core 1 warm reset flag is set by the "Reset Signal" from WARMRSTREQ of Cortex-A35 core 1 to indicate the previous reset source
     * |        |          |The WARMRSTREQ of Cortex-A35 core 1 trigger by writing 1 to the bit RR (RMR[1], Reset Management Register of Cortex-A35 core 1)
     * |        |          |0 = No reset from WARMRSTREQ of Cortex-A35 core 1.
     * |        |          |1 = The Cortex-A35 core 1 had issued WARMRSTREQ reset signal to reset itself.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[15]    |CPU1RF    |Cortex-A35 Core 1 Reset Flag
     * |        |          |The Cortex-A35 Core 1 reset flag is set by hardware if software writes CA35CR1RST (SYS_IPRST0[2]) 1 to reset Cortex-A35 Core 1.
     * |        |          |0 = No reset to Cortex-A35 Core 1.
     * |        |          |1 = The Cortex-A35 Core 1 is reset by software setting CA35CR1RST (SYS_IPRST0[2]) to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[18]    |WDT1RFM   |WDT 1 Reset Flag for RTP Cortex-M4
     * |        |          |The WDT 1 reset flag is set by the "Reset Signal" from the Watchdog Timer 1 or Window Watchdog Timer 1 to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer 1 or window watchdog timer 1.
     * |        |          |1 = The watchdog timer 1 or window watchdog timer 1 had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer 1 register RSTF(WDT1_CTL[2]) bit is set if the system has been reset by WDT 1 time-out reset
     * |        |          |Window Watchdog Timer 1 register WWDTRF(WWDT1_STATUS[1]) bit is set if the system has been reset by WWDT 1 time-out reset.
     * |        |          |Note 3: This flag only take effect when WDT1RSTMEN (SYS_MISCRFCR[18]) is 1.
     * |[19]    |WDT2RF    |WDT 2 Reset Flag for RTP Cortex-M4
     * |        |          |The WDT 2 reset flag is set by the "Reset Signal" from the Watchdog Timer 2 or Window Watchdog Timer 2 to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer 2 or window watchdog timer 2.
     * |        |          |1 = The watchdog timer 2 or window watchdog timer 2 had issued the reset signal to reset the system.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer 2 register RSTF(WDT2_CTL[2]) bit is set if the system has been reset by WDT 2 time-out reset
     * |        |          |Window Watchdog Timer 2 register WWDTRF(WWDT2_STATUS[1]) bit is set if the system has been reset by WWDT 2 time-out reset.
     * |[20]    |RTPM4LKRF |RTP M4 CPU Lockup Reset Flag
     * |        |          |0 = No reset from RTP M4 CPU lockup happened.
     * |        |          |1 = The RTP Cortex-M4 lockup happened and chip is reset.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: When CPU lockup happened under ICE is connected, this flag will set to 1 but chip will not reset.
     * |[21]    |RTPM4SYSRF|RTP M4 System Reset Flag
     * |        |          |The system reset flag is set by the "Reset Signal" from the Cortex-M4 Core to indicate the previous reset source.
     * |        |          |0 = No reset from Cortex-M4.
     * |        |          |1 = The Cortex-M4 had issued the reset signal to reset the system by writing 1 to the bit SYSRESETREQ(AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M4 core.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[22]    |RTPPMUSYSRF|RTP PMU System Reset Flag
     * |        |          |The system reset flag is set by the "Reset Signal" from the PMU of Cortex-M4 Core to indicate the previous reset source.
     * |        |          |0 = No reset from PMU of Cortex-M4.
     * |        |          |1 = The PMU of Cortex-M4 had issued the reset signal (PMURESETREQ) to reset the system.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[23]    |RTPM4CPURF|RTP M4 CPU Reset Flag
     * |        |          |The RTP M4 CPU reset flag is set by hardware if software writes CM4RST (SYS_IPRST0[3]) 1 to reset Cortex-M4 Core.
     * |        |          |0 = No reset to RTP M4 CPU.
     * |        |          |1 = The RTP M4 CPU core is reset by software setting CM4RST (SYS_IPRST0[3]) to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * @var SYS_T::MISCRFCR
     * Offset: 0x14  Miscellaneous Reset Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PORDISCODE|Power-on-reset Disable Code (Write Protect)
     * |        |          |When powered on, the Power-On-Reset (POR) circuit generates a reset signal to reset whole chip function
     * |        |          |However, after power is ready, the POR circuit would consume a few power
     * |        |          |To minimize the POR circuit power consumption, user to disable POR circuit by writing 0x5AA5 to this field.
     * |        |          |The POR circuit will become active again when this field is set to other value or chip is reset by other reset source, including /RESET pin, Watchdog, LVR reset and the software chip reset function.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[16]    |WDT1RSTAEN|WDT 1 Reset Cortex-A35 Enable Bit (Write Protect)
     * |        |          |0 = WDT 1 reset Cortex-A35 Disabled. (Default)
     * |        |          |1 = WDT 1 reset Cortex-A35 Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[17]    |WDT2RSTAEN|WDT 2 Reset Cortex-A35 Enable Bit (Write Protect)
     * |        |          |0 = WDT 2 reset Cortex-A35 Disabled. (Default)
     * |        |          |1 = WDT 2 reset Cortex-A35 Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[18]    |WDT1RSTMEN|WDT 1 Reset Real Time Cortex-M4 Sub-system Enable Bit (Write Protect)
     * |        |          |0 = WDT 1 reset real time Cortex-M4 sub-system Disabled. (Default)
     * |        |          |1 = WDT 1 reset real time Cortex-M4 sub-system Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * @var SYS_T::RSTDEBCTL
     * Offset: 0x18  Reset Pin De-bounce Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |DEBCNT    |Power-on-reset Disable Code (Write Protect)
     * |        |          |This 16-bit external RESET De-bounce Counter can specify the external RESET de-bounce time up to around 5.46ms (0xFFFF) @ XIN=12 MHz.
     * |        |          |The default external RESET de-bounce time is 0.1ms (0x04B0) @ XIN = 12 MHz.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[31]    |RSTDEBEN  |Reset Pin De-bounce Enable Bit (Write Protect)
     * |        |          |0 = Reset pin de-bounce Disabled.
     * |        |          |1 = Reset pin de-bounce Enabled. (Default)
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * @var SYS_T::LVRDCR
     * Offset: 0x1C  Low Voltage Reset & Detect Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LVREN     |Low Voltage Reset Enable Bit (Write Protect)
     * |        |          |0 = Low voltage reset function Disabled.
     * |        |          |1 = Low voltage reset function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[3:1]   |LVRDGSEL  |LVR Output De-glitch Time Select (Write Protect)
     * |        |          |000 = Without de-glitch function.
     * |        |          |001 = 4 system clock (LVRDGCLK).
     * |        |          |010 = 8 system clock (LVRDGCLK).
     * |        |          |011 = 16 system clock (LVRDGCLK).
     * |        |          |100 = 32 system clock (LVRDGCLK).
     * |        |          |101 = 64 system clock (LVRDGCLK).
     * |        |          |110 = 128 system clock (LVRDGCLK).
     * |        |          |111 = 256 system clock (LVRDGCLK).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: Refer to LVRDBSEL (CLK_CLKSEL0[3]) for LVRDGCLK clock source selection.
     * |[8]     |LVDEN     |Low Voltage Detect Enable Bit (Write Protect)
     * |        |          |0 = Low voltage detect function Disabled.
     * |        |          |1 = Low voltage detect function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[9]     |LVDSEL    |Low Voltage Detect Threshold Selection (Write Protect)
     * |        |          |0 = Low voltage detection level is 2.8V.
     * |        |          |1 = Low voltage detection level is 2.6V.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[10]    |LVDWKA35EN|Low Voltage Detect Wake-up Cortex-A35 Enable Control Bit (Write Protect)
     * |        |          |0 = Low voltage detection wakeup A35 Disabled.
     * |        |          |1 = Low voltage detection wakeup A35 Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[11]    |LVDWKRTPEN|Low Voltage Detect Wake-up RTP Cortex-M4 Enable Control Bit (Write Protect)
     * |        |          |0 = Low voltage detection wakeup RTP Cortex-M4 Disabled.
     * |        |          |1 = Low voltage detection wakeup RTP Cortex-M4 Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[14:12] |LVDODGSEL |LVD Output De-glitch Time Select (Write Protect)
     * |        |          |000 = Without de-glitch function.
     * |        |          |001 = 4 system clock (LVRDGCLK).
     * |        |          |010 = 8 system clock (LVRDGCLK).
     * |        |          |011 = 16 system clock (LVRDGCLK).
     * |        |          |100 = 32 system clock (LVRDGCLK).
     * |        |          |101 = 64 system clock (LVRDGCLK).
     * |        |          |110 = 128 system clock (LVRDGCLK).
     * |        |          |111 = 256 system clock (LVRDGCLK).
     * |        |          |Note 1: These bits are write protected. Refer to the SYS_RLKTZS register.
     * |        |          |Note 2: Refer to LVRDBSEL (CLK_CLKSEL0[3]) for LVRDGCLK clock source selection.
     * @var SYS_T::IPRST0
     * Offset: 0x20  Reset Control Register 0 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHIPRST   |Chip One-shot Reset Enable Bit (Write Protect)
     * |        |          |0 = Chip one-shot reset Disabled.
     * |        |          |1 = Chip one-shot reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[1]     |CA35CR0RST|Cortex-A35 Core 0 One-shot Reset (Write Protect)
     * |        |          |0 = Cortex-A35 core 0 one-shot reset Disabled.
     * |        |          |1 = Cortex-A35 core 0 one-shot reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[2]     |CA35CR1RST|Cortex-A35 Core 1 One-shot Reset (Write Protect)
     * |        |          |0 = Cortex-A35 core 1 one-shot reset Disabled.
     * |        |          |1 = Cortex-A35 core 1 one-shot reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[3]     |CM4RST    |Cortex-M4 Core Reset (Write Protect)
     * |        |          |0 = Cortex-M4 core reset Disabled.
     * |        |          |1 = Cortex-M4 core reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[4]     |PDMA0RST  |PDMA 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = PDMA 0 reset Disabled.
     * |        |          |1 = PDMA 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[5]     |PDMA1RST  |PDMA 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = PDMA 1 reset Disabled.
     * |        |          |1 = PDMA 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[6]     |PDMA2RST  |PDMA2 Reset Enable Bit (Write Protect)
     * |        |          |0 = PDMA 2 reset Disabled.
     * |        |          |1 = PDMA 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[7]     |PDMA3RST  |PDMA 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = PDMA 3 reset Disabled.
     * |        |          |1 = PDMA 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[9]     |DISPCRST  |LCD Display Controller Reset Enable Bit (Write Protect)
     * |        |          |0 = LCD Display Controller reset Disabled.
     * |        |          |1 = LCD Display Controller reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[10]    |VCAP0RST  |Video Capture Sensor Interface 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = Video Capture sensor interface 0 reset Disabled.
     * |        |          |1 = Video Capture sensor interface 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[11]    |VCAP1RST  |Video Capture Sensor Interface 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = Video Capture sensor interface 1 reset Disabled.
     * |        |          |1 = Video Capture sensor interface 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[12]    |GFXRST    |Graphic Engine Reset Enable Bit (Write Protect)
     * |        |          |0 = Graphic Engine reset Disabled.
     * |        |          |1 = Graphic Engine reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[13]    |VDECRST   |Video Decoder Reset Enable Bit (Write Protect)
     * |        |          |0 = Video Decoder (H.264/JPEG) reset Disabled.
     * |        |          |1 = Video Decoder (H.264/JPEG) reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[14]    |WRHO0RST  |Wormhole 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = Wormhole 0 reset Disabled.
     * |        |          |1 = Wormhole 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[15]    |WRHO1RST  |Wormhole 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = Wormhole 1 reset Disabled.
     * |        |          |1 = Wormhole 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[16]    |GMAC0RST  |Gigabit Ethernet MAC 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = Gigabit Ethernet MAC 0 reset Disabled.
     * |        |          |1 = Gigabit Ethernet MAC 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[17]    |GMAC1RST  |Gigabit Ethernet MAC 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = Gigabit Ethernet MAC 1 reset Disabled.
     * |        |          |1 = Gigabit Ethernet MAC 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[18]    |HWSEMRST  |Hardware Semaphore Reset Enable Bit (Write Protect)
     * |        |          |0 = Hardware Semaphore reset Disabled.
     * |        |          |1 = Hardware Semaphore reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[19]    |EBIRST    |EBI Controller Reset (Write Protect)
     * |        |          |0 = EBI controller reset Disabled.
     * |        |          |1 = EBI controller reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[20]    |HSUSBH0RST|High-speed USB Host Controller 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = High-Speed USB host controller 0 reset Disabled.
     * |        |          |1 = High-Speed USB host controller 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[21]    |HSUSBH1RST|High-speed USB Host Controller 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = High-Speed USB host controller 1 reset Disabled.
     * |        |          |1 = High-Speed USB host controller 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[22]    |HSUSBDRST |High-speed USB Device Controller Reset Enable Bit (Write Protect)
     * |        |          |0 = High-Speed USB device controller reset Disabled.
     * |        |          |1 = High-Speed USB device controller reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[24]    |SDH0RST   |SDIO Controller 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = SDIO controller 0 reset Disabled.
     * |        |          |1 = SDIO controller 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[25]    |SDH1RST   |SDIO Controller 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = SDIO controller 1 reset Disabled.
     * |        |          |1 = SDIO controller 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[26]    |NANDRST   |NAND Flash Controller Reset Enable Bit (Write Protect)
     * |        |          |0 = NAND Flash controller reset Disabled.
     * |        |          |1 = NAND Flash controller reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[27]    |GPIORST   |GPIO Reset Enable Bit (Write Protect)
     * |        |          |0 = GPIO reset Disabled.
     * |        |          |1 = GPIO reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[28]    |MCTLPRST  |DDR Memory Controller MCTL2 APB Interface Reset Enable Bit (Write Protect)
     * |        |          |Write 1 to enable MCTL2 APB reset to reset APB interface logic of MCTL2.
     * |        |          |Write 0 to trigger a reset disable procedure and this bit cleared automatically after 128 pclk.
     * |        |          |0 = DDR Memory Controller MCTL2 APB interface reset Disabled.
     * |        |          |1 = DDR Memory Controller MCTL2 APB interface reset Enabled.
     * |        |          |Note 1: Once trigger reset disable procedure, it's necessary to poll MCTLPRST till its 0.
     * |        |          |Note 2: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[29]    |MCTLCRST  |DDR Memory Controller MCTL2 Core Reset Enable Bit (Write Protect)
     * |        |          |0 = DDR Memory Controller MCTL2 core reset Disabled.
     * |        |          |1 = DDR Memory Controller MCTL2 core reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[30]    |DDRPUBRST |DDR PHY PUB Reset Enable Bit (Write Protect)
     * |        |          |0 = DDR PHY PUB reset Disabled.
     * |        |          |1 = DDR PHY PUB reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * @var SYS_T::IPRST1
     * Offset: 0x24  Reset Control Register 1 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |TMR0RST   |TIMER 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 0 reset Disabled.
     * |        |          |1 = TIMER 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[3]     |TMR1RST   |TIMER 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 1 reset Disabled.
     * |        |          |1 = TIMER 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[4]     |TMR2RST   |TIMER 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 2 reset Disabled.
     * |        |          |1 = TIMER 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[5]     |TMR3RST   |TIMER 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 3 reset Disabled.
     * |        |          |1 = TIMER 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[8]     |I2C0RST   |I2C 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 0 reset Disabled.
     * |        |          |1 = I2C 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[9]     |I2C1RST   |I2C 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 1 reset Disabled.
     * |        |          |1 = I2C 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[10]    |I2C2RST   |I2C 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 2 reset Disabled.
     * |        |          |1 = I2C 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[11]    |I2C3RST   |I2C 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 3 reset Disabled.
     * |        |          |1 = I2C 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[12]    |QSPI0RST  |QSPI 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = QSPI 0 reset Disabled.
     * |        |          |1 = QSPI 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[13]    |SPI0RST   |SPI 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = SPI 0 reset Disabled.
     * |        |          |1 = SPI 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[14]    |SPI1RST   |SPI 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = SPI 1 reset Disabled.
     * |        |          |1 = SPI 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[15]    |SPI2RST   |SPI 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = SPI 2 reset Disabled.
     * |        |          |1 = SPI 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[16]    |UART0RST  |UART 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 0 reset Disabled.
     * |        |          |1 = UART 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[17]    |UART1RST  |UART 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 1 reset Disabled.
     * |        |          |1 = UART 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[18]    |UART2RST  |UART 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 2 reset Disabled.
     * |        |          |1 = UART 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[19]    |UART3RST  |UART 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 3 reset Disabled.
     * |        |          |1 = UART 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[20]    |UART4RST  |UART 4 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 4 reset Disabled.
     * |        |          |1 = UART 4 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[21]    |UART5RST  |UART 5 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 5 reset Disabled.
     * |        |          |1 = UART 5 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[22]    |UART6RST  |UART 6 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 6 reset Disabled.
     * |        |          |1 = UART 6 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[23]    |UART7RST  |UART 7 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 7 reset Disabled.
     * |        |          |1 = UART 7 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[24]    |CANFD0RST |CAN FD 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = CAN FD 1 reset Disabled.
     * |        |          |1 = CAN FD 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[25]    |CANFD1RST |CAN FD 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = CAN FD 1 reset Disabled.
     * |        |          |1 = CAN FD 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[28]    |EADC0RST  |EADC 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = EADC 0 reset Disabled.
     * |        |          |1 = EADC 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[29]    |I2S0RST   |I2S 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2S 0 reset Disabled.
     * |        |          |1 = I2S 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * @var SYS_T::IPRST2
     * Offset: 0x28  Reset Control Register 2 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SC0RST    |SC 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = SC 0 reset Disabled.
     * |        |          |1 = SC 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[1]     |SC1RST    |SC 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = SC 1 reset Disabled.
     * |        |          |1 = SC 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[4]     |QSPI1RST  |QSPI 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = QSPI 1 reset Disabled.
     * |        |          |1 = QSPI 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[6]     |SPI3RST   |SPI 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = SPI 3 reset Disabled.
     * |        |          |1 = SPI 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[16]    |EPWM0RST  |EPWM 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = EPWM 0 reset Disabled.
     * |        |          |1 = EPWM 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[17]    |EPWM1RST  |EPWM 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = EPWM 1 reset Disabled.
     * |        |          |1 = EPWM 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[22]    |QEI0RST   |QEI 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = QEI 0 reset Disabled.
     * |        |          |1 = QEI 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[23]    |QEI1RST   |QEI 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = QEI 1 reset Disabled.
     * |        |          |1 = QEI 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[26]    |ECAP0RST  |ECAP 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = ECAP 0 reset Disabled.
     * |        |          |1 = ECAP 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[27]    |ECAP1RST  |ECAP 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = ECAP 1 reset Disabled.
     * |        |          |1 = ECAP 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[28]    |CANFD2RST |CAN FD 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = CAN FD 2 reset Disabled.
     * |        |          |1 = CAN FD 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[31]    |ADC0RST   |ADC 0 Reset Enable Bit (Write Protect)
     * |        |          |0 = ADC 0 reset Disabled.
     * |        |          |1 = ADC 0 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * @var SYS_T::IPRST3
     * Offset: 0x2C  Reset Control Register 3 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TMR4RST   |TIMER 4 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 4 reset Disabled.
     * |        |          |1 = TIMER 4 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[1]     |TMR5RST   |TIMER 5 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 5 reset Disabled.
     * |        |          |1 = TIMER 5 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[2]     |TMR6RST   |TIMER 6 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 6 reset Disabled.
     * |        |          |1 = TIMER 6 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[3]     |TMR7RST   |TIMER 7 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 7 reset Disabled.
     * |        |          |1 = TIMER 7 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[4]     |TMR8RST   |TIMER 8 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 8 reset Disabled.
     * |        |          |1 = TIMER 8 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[5]     |TMR9RST   |TIMER 9 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 9 reset Disabled.
     * |        |          |1 = TIMER 9 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[6]     |TMR10RST  |TIMER 10 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 10 reset Disabled.
     * |        |          |1 = TIMER 10 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[7]     |TMR11RST  |TIMER 11 Reset Enable Bit (Write Protect)
     * |        |          |0 = TIMER 11 reset Disabled.
     * |        |          |1 = TIMER 11 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[8]     |UART8RST  |UART 8 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 8 reset Disabled.
     * |        |          |1 = UART 8 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[9]     |UART9RST  |UART 9 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 9 reset Disabled.
     * |        |          |1 = UART 9 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[10]    |UART10RST |UART 10 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 10 reset Disabled.
     * |        |          |1 = UART 10 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[11]    |UART11RST |UART 11 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 11 reset Disabled.
     * |        |          |1 = UART 11 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[12]    |UART12RST |UART 12 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 12 reset Disabled.
     * |        |          |1 = UART 12 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[13]    |UART13RST |UART 13 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 13 reset Disabled.
     * |        |          |1 = UART 13 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[14]    |UART14RST |UART 14 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 14 reset Disabled.
     * |        |          |1 = UART 14 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[15]    |UART15RST |UART 15 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 15 reset Disabled.
     * |        |          |1 = UART 15 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[16]    |UART16RST |UART 16 Reset Enable Bit (Write Protect)
     * |        |          |0 = UART 16 reset Disabled.
     * |        |          |1 = UART 16 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[17]    |I2S1RST   |I2S 1 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2S 1 reset Disabled.
     * |        |          |1 = I2S 1 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[18]    |I2C4RST   |I2C 4 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 4 reset Disabled.
     * |        |          |1 = I2C 4reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[19]    |I2C5RST   |I2C 5 Reset Enable Bit (Write Protect)
     * |        |          |0 = I2C 5 reset Disabled.
     * |        |          |1 = I2C 5 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[20]    |EPWM2RST  |EPWM 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = EPWM 2 reset Disabled.
     * |        |          |1 = EPWM 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[21]    |ECAP2RST  |ECAP 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = ECAP 2 reset Disabled.
     * |        |          |1 = ECAP 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[22]    |QEI2RST   |QEI 2 Reset Enable Bit (Write Protect)
     * |        |          |0 = QEI 2 reset Disabled.
     * |        |          |1 = QEI 2 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[23]    |CANFD3RST |CAN FD 3 Reset Enable Bit (Write Protect)
     * |        |          |0 = CAN FD 3 reset Disabled.
     * |        |          |1 = CAN FD 3 reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[24]    |KPIRST    |KPI Reset Enable Bit (Write Protect)
     * |        |          |0 = KPI reset Disabled.
     * |        |          |1 = KPI reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[28]    |GICRST    |GIC Reset Enable Bit (Write Protect)
     * |        |          |0 = GIC reset Disabled.
     * |        |          |1 = GIC reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[30]    |SSMCCRST  |SSMCC Reset Enable Bit (Write Protect)
     * |        |          |0 = SSMCC reset Disabled.
     * |        |          |1 = SSMCC reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[31]    |SSPCCRST  |SSPCC Reset Enable Bit (Write Protect)
     * |        |          |0 = SSPCC reset Disabled.
     * |        |          |1 = SSPCC reset Enabled.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * @var SYS_T::PMUCR
     * Offset: 0x30  Power Management Unit Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |A35PGEN   |Cortex-A35 Power Gating Enable (Write Protect)
     * |        |          |0 = Cortex-A35 dual core power gating Disabled.
     * |        |          |1 = Cortex-A35 dual core power gating Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[4]     |AUTOL2FDIS|Automatic L2 Cache Flush Disable (Write Protect)
     * |        |          |0 = Automatic L2 cache flush Enabled.
     * |        |          |1 = Automatic L2 cache flush Disabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[6]     |PDWKDLY   |Wake-up Delay Counter Enable Bit (Write Protect)
     * |        |          |When the Cortex-A35 wakes up from Power-down mode, the clock control will delay certain clock cycles to wait system clock stable.
     * |        |          |The delayed clock cycle is 4096 clock cycles when chip works at 24 Mhz external high speed crystal oscillator (HXT), and 256 clock cycles when chip works at 12 MHz internal high speed RC oscillator (HIRC).
     * |        |          |0 = Wake-up delay counter Disabled.
     * |        |          |1 = Wake-up delay counter Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[11:8]  |PWRSTBTM  |Power Gating Acknowledgement Stable Time (Write Protect)
     * |        |          |The PWRSTBTM indicates the stable time after receiving power gating acknowledgement.
     * |        |          |0000 = 5us (Default).
     * |        |          |0001 = 10us.
     * |        |          |0010 = 20us.
     * |        |          |0011 = 40us.
     * |        |          |0100 = 60us.
     * |        |          |0101 = 80us.
     * |        |          |0110 = 100us.
     * |        |          |0111 = 200us.
     * |        |          |1000 = 400us.
     * |        |          |1001 = 600us.
     * |        |          |1010 = 800us.
     * |        |          |1011 = 1ms.
     * |        |          |1100 = 2ms.
     * |        |          |1101 = 4ms.
     * |        |          |1110 = 5.4ms.
     * |        |          |1111 = 0us.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[15:12] |PWRACKTO  |Power Gating Acknowledgement Time Out Selection (Write Protect)
     * |        |          |0000 = 20us (Default).
     * |        |          |0001 = 30us.
     * |        |          |0010 = 40us.
     * |        |          |0011 = 50us.
     * |        |          |0100 = 60us.
     * |        |          |0101 = 80us.
     * |        |          |0110 = 100us.
     * |        |          |0111 = 200us.
     * |        |          |1000 = 400us.
     * |        |          |1001 = 600us.
     * |        |          |1010 = 800us.
     * |        |          |1011 = 1ms.
     * |        |          |1100 = 2ms.
     * |        |          |1101 = 4ms.
     * |        |          |1110 = 5.4ms.
     * |        |          |1111 = 0us.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[16]    |A35PDEN   |Cortex-A35 Power Down Enable Bit (Write Protect)
     * |        |          |When this bit is set to 1, Power-down mode is enabled and the chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
     * |        |          |When chip wakes up from Power-down mode, this bit is auto cleared
     * |        |          |Users need to set this bit again for next Power-down.
     * |        |          |In Power-down mode, HXT, HIRC, HIRC48, PLL and system clock will be disabled and ignored the clock source selection
     * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LXT or LIRC.
     * |        |          |0 = Chip operating normally or chip in idle mode because of WFI command.
     * |        |          |1 = Chip waits CPU sleep command WFI and then enters Power-down mode.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[18]    |A35DBPDEN |Cortex-A35 Entering Power-down Even ICE Connected (Write Protect)
     * |        |          |0 = Cortex-A35 does not enter Power-down during Debug mode.
     * |        |          |1 = Cortex-A35 enters power-down in Debug mode.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[24]    |RTPPDEN   |RTP M4 Power Down Enable (Write Protect)
     * |        |          |When this bit is set to 1, Power-down mode is enabled and the chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
     * |        |          |When chip wakes up from Power-down mode, this bit is auto cleared
     * |        |          |Users need to set this bit again for next Power-down.
     * |        |          |In Power-down mode, HXT, HIRC, HIRC48, PLL and system clock will be disabled and ignored the clock source selection
     * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LXT or LIRC.
     * |        |          |0 = Chip operating normally or chip in idle mode because of WFI command.
     * |        |          |1 = Chip waits CPU sleep command WFI and then enters Power-down mode.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[26]    |RTPDBPDEN |RTP M4 Entering Power-down Even ICE Connected (Write Protect)
     * |        |          |0 = RTP M4 does not enter Power-down during Debug mode.
     * |        |          |1 = RTP M4 enters power-down in Debug mode.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKSUBM register.
     * @var SYS_T::DDRCQCSR
     * Offset: 0x34  DDR Controller Q Channel Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |AXIQBYPAS |DDR Controller AXI Port 7 ~ Port 0 Q Channel Handshake Bypass (Write Protect)
     * |        |          |The AXIQBYPAS indicates to bypass DDR controller's AXI port Q channel handshake mechanism
     * |        |          |The each bit of AXIQBYPAS is for corresponding AXI port of DDR controller.
     * |        |          |AXIQBYPAS[x]
     * |        |          |0 = Q channel handshake mechanism of AXI port x Not Bypassed (x=0, 1, ?? 7).
     * |        |          |1 = Q channel handshake mechanism of AXI port x Bypassed (x=0, 1, ?? 7).
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[15:8]  |AXIQDENYIF|DDR Controller AXI Port 7 ~ Port 0 Q Channel Interrupt Flag
     * |        |          |0 = Q channel power down request accept by DDR controller AXI port x (x=0, 1, ?? 7).
     * |        |          |1 = Q channel power down request reject by DDR controller AXI port x, AXI port x wouldn't enter low power mode and clock of AXI port x keep clocking (x=0, 1, ?? 7).
     * |[16]    |DDRCQBYPAS|DDR Controller Core Q Channel Handshake Bypass (Write Protect)
     * |        |          |0 = Q channel handshake of DDR controller core Not Bypassed.
     * |        |          |1 = Q channel handshake of DDR controller core Bypassed.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[17]    |DDRCQDENYIF|DDR Controller Core Q Channel Deny Interrupt Flag
     * |        |          |0 = Q channel power down request accept by DDR controller core.
     * |        |          |1 = Q channel power down request reject by DDR controller core and DDR controller wouldn't enter self-refresh mode.
     * |[27:24] |DDRQREQDLY|DDR Controller Q Channel Request Delay Time Selection (Write Protect)
     * |        |          |0000 = 20us (Default).
     * |        |          |0001 = 30us.
     * |        |          |0010 = 40us.
     * |        |          |0011 = 50us.
     * |        |          |0100 = 60us.
     * |        |          |0101 = 80us.
     * |        |          |0110 = 100us.
     * |        |          |0111 = 200us.
     * |        |          |1000 = 400us.
     * |        |          |1001 = 600us.
     * |        |          |1010 = 800us.
     * |        |          |1011 = 1ms.
     * |        |          |1100 = 2ms.
     * |        |          |1101 = 3ms.
     * |        |          |1110 = 5.4ms.
     * |        |          |1111 = 0us.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[31:28] |DDRQACKTO |DDR Controller Q Channel Acknowledgement Time Out Selection (Write Protect)
     * |        |          |0000 = 20us (Default).
     * |        |          |0001 = 30us.
     * |        |          |0010 = 40us.
     * |        |          |0011 = 50us.
     * |        |          |0100 = 60us.
     * |        |          |0101 = 80us.
     * |        |          |0110 = 100us.
     * |        |          |0111 = 200us.
     * |        |          |1000 = 400us.
     * |        |          |1001 = 600us.
     * |        |          |1010 = 800us.
     * |        |          |1011 = 1ms.
     * |        |          |1100 = 2ms.
     * |        |          |1101 = 3ms.
     * |        |          |1110 = 5.4ms.
     * |        |          |1111 = 0us.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * @var SYS_T::PMUIEN
     * Offset: 0x38  Power Management Unit Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PMUIEN    |PMU Interrupt Enable Control Bit (Write Protect)
     * |        |          |0 = PMU interrupt Disabled.
     * |        |          |1 = PMU interrupt Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[8]     |A35PDWKIEN|Cortex-A35 Power-down Wake-up Interrupt Enable Control Bit (Write Protect)
     * |        |          |0 = Cortex-a35 wake-up interrupt Disabled.
     * |        |          |1 = Cortex-a35 wake-up interrupt Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKTZS register.
     * |[12]    |RTPPDWKIEN|RTP M4 Power-down Wake-up Interrupt Enable Control Bit (Write Protect)
     * |        |          |0 = RTP M4 wake-up interrupt Disabled.
     * |        |          |1 = RTP M4 wake-up interrupt Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_RLKSUBM register.
     * @var SYS_T::PMUSTS
     * Offset: 0x3C  Power Management Unit Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PMUIF     |PMU Interrupt Flag
     * |        |          |When PMUIEN high, this bit high to indicate that PGTOIF, DDRCQDENYIF or AXIQDENYIF is active
     * |        |          |When PMUIEN low, this bit didn't take effect.
     * |        |          |0 = PGTOIF, DDRCQDENYIF and AXIQDENYIF are not active.
     * |        |          |1 = PGTOIF, DDRCQDENYIF or AXIQDENYIF is active.
     * |[1]     |PGTOIF    |Power Gating Time Out Interrupt Flag
     * |        |          |0 = Power gating acknowledgement counter is not time-out yet.
     * |        |          |1 = Power gating acknowledgement counter is time-out.
     * |[5]     |L2FDONE   |Cortex-A35 L2 Cache Flush Done Status
     * |        |          |0 = Cortex-A35 L2 cache flush didn't finish yet.
     * |        |          |1 = Cortex-A35 L2 cache flush done.
     * |[8]     |A35PDWKIF |Cortex-A35 Power-down Wake-up Interrupt Flag
     * |        |          |0 = Cortex-A35 didn't wake-up from power-down mode.
     * |        |          |1 = Cortex-A35 receive a wake-up event and wake-up from power-down mode.
     * |[12]    |RTPPDWKIF |RTP M4 Power-down Wake-up Interrupt Flag
     * |        |          |0 = RTP M4 didn't wake-up from power-down mode.
     * |        |          |1 = RTP M4 receive a wake-up event and wake-up from power-down mode.
     * |[31:16] |PWRACKCNT |Power Gating Acknowledgement Timing Counter Value
     * |        |          |The PWRACKCNT show the value of power gating acknowledgement time-out counter.
     * @var SYS_T::CA35WRBADR0
     * Offset: 0x40  Cortexu00AE-A35 Core 0 Warm-boot Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WRMBTADDR |Warm Boot Address
     * |        |          |The WRMBTADDR indicates the warm boot run address for Cortex-A35 Core 0.
     * @var SYS_T::CA35WRBPAR0
     * Offset: 0x44  Cortexu00AE-A35 Core 0 Warm-boot Parameter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WRMBTPARA |Warm Boot Parameter
     * |        |          |The WRMBTPARA indicates the warm boot parameters for Cortex-A35 Core 0.
     * @var SYS_T::CA35WRBADR1
     * Offset: 0x48  Cortexu00AE-A35 Core 1 Warm-boot Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WRMBTADDR |Warm Boot Address
     * |        |          |The WRMBTADDR indicates the warm boot run address for Cortex-A35 Core 1.
     * @var SYS_T::CA35WRBPAR1
     * Offset: 0x4C  Cortexu00AE-A35 Core 1 Warm-boot Parameter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WRMBTPARA |Warm Boot Parameter
     * |        |          |The WRMBTPARA indicates the warm boot parameters for Cortex-A35 Core 1.
     * @var SYS_T::USBPMISCR
     * Offset: 0x60  USB PHY Miscellaneous Control Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PHY0POR   |USB 2.0 Port 0 High-speed PHY Power-On Reset Control Bit
     * |        |          |0 = All test registers and state machines in the USB 2.0 port 0 high-speed PHY are not in reset state.
     * |        |          |1 = All test registers and state machines in the USB 2.0 port 0 high-speed PHY are in reset state.
     * |[1]     |PHY0SUSPEND|USB 2.0 Port 0 High-speed PHY Suspend Control Bit
     * |        |          |0 = USB 2.0 port 0 high-speed PHY is in Suspend mode.
     * |        |          |1 = USB 2.0 port 0 high-speed PHY is in Normal operating mode.
     * |[2]     |PHY0COMN  |USB 2.0 Port 0 High-speed PHY Common Block Power-Down Control Bit
     * |        |          |0 = In Suspend or Sleep modes, the REFCLK_LOGIC, Bias and PLL blocks of USB 2.0 port 0 high-speed PHY remain powered
     * |        |          |With this setting, the input reference clock must remain on and valid during suspend or sleep.
     * |        |          |1 = In Suspend mode, the REFCLK_LOGIC, Bias and PLL blocks of USB 2.0 port 0 high-speed PHY are powered down
     * |        |          |In Sleep mode, the Bias and PLL blocks of USB 2.0 port 0 high-speed PHY are powered down.
     * |[6:4]   |VBUSDGSEL |VBUS Detect De-glitch Time Select
     * |        |          |000 = Without de-glitch function.
     * |        |          |001 = 4 HIRC clock.
     * |        |          |010 = 8 HIRC clock.
     * |        |          |011 = 16 HIRC clock.
     * |        |          |100 = 32 HIRC clock.
     * |        |          |101 = 64 HIRC clock.
     * |        |          |110 = 128 HIRC clock.
     * |        |          |111 = 256 HIRC clock.
     * |[7]     |EFUSESEL0 |USB 2.0 Port 0 High-speed PHY Resistor Calibration with External Resistor Control Bit
     * |        |          |0 = An external resistor (REXT) is needed and internal digital calibration code is based on REXT.
     * |        |          |1 = Enable the internal resistor method with RCALCODE1 resistance control up to +/- 18%, allowing the removal of the REXT resistor.
     * |[8]     |PHY0HSTCKSTB|USB 2.0 Port 0 High-speed PHY 60 MHz UTMI Interface Clock for Host Stable Flag
     * |        |          |0 = USB 2.0 port 0 high-speed PHY UTMI Interface clock for Host is not stable.
     * |        |          |1 = USB 2.0 port 0 high-speed PHY UTMI Interface clock for Host is stable.
     * |[9]     |PHY0CK12MSTB|USB 2.0 Port 0 High-speed PHY 12 MHz Clock Stable Flag
     * |        |          |0 = USB 2.0 port 0 high-speed PHY 12 MHz clock is not stable.
     * |        |          |1 = USB 2.0 port 0 high-speed PHY 12 MHz clock is stable.
     * |[10]    |PHY0DEVCKSTB|USB 2.0 Port 0 High-speed PHY 60 MHz UTMI Interface Clock for Device Stable Flag
     * |        |          |0 = USB 2.0 port 0 high-speed PHY UTMI Interface clock for Device is not stable.
     * |        |          |1 = USB 2.0 port 0 high-speed PHY UTMI Interface clock for Device is stable.
     * |[11]    |RTUNESEL0 |USB 2.0 Port 0 High-speed PHY Source Impedance Tuning Method Selection
     * |        |          |0 = Internal digital calibration codes are used for tuning the high-speed source impedance.
     * |        |          |1 = The RCALCODE0 value is used for tuning the high-speed source impedance.
     * |[15:12] |RCALCODE0 |USB 2.0 Port 0 High-Speed PHY Internal Resistor Trim Code
     * |        |          |If RTUNESEL0 = 1, RCALCODE0 provides the tuning code for high-speed source impedance directly.
     * |        |          |If RTUNESEL0 = 0, RCALCODE0 provides the tuning code for on-chip resistor within +/- 18% resistance tuning range.
     * |        |          |0000 = +18% (236 u03A9).
     * |        |          |0001 = +15.6%.
     * |        |          |0010 = +13.2%.
     * |        |          |0011 = +10.8%.
     * |        |          |0100 = +8.4%.
     * |        |          |0101 = +6%.
     * |        |          |0110 = +3.6%.
     * |        |          |0111 = +1.2%.
     * |        |          |1000 = -1.2%.
     * |        |          |1001 = -3.6%.
     * |        |          |1010 = -6%.
     * |        |          |1011 = -8.4%.
     * |        |          |1100 = -10.8%.
     * |        |          |1101 = -13.2%.
     * |        |          |1110 = -15.6%.
     * |        |          |1111 = -18% (164 u03A9).
     * |[16]    |PHY1POR   |USB 2.0 Port 1 High-speed PHY Power-On Reset Control Bit
     * |        |          |0 = All test registers and state machines in the USB 2.0 port 1 high-speed PHY are not in reset state.
     * |        |          |1 = All test registers and state machines in the USB 2.0 port 1 high-speed PHY are in reset state.
     * |[17]    |PHY1SUSPEND|USB 2.0 Port 1 High-speed PHY Suspend Control Bit
     * |        |          |0 = USB 2.0 port 1 high-speed PHY is in Suspend mode.
     * |        |          |1 = USB 2.0 port 1 high-speed PHY is in Normal operating mode.
     * |[18]    |PHY1COMN  |USB 2.0 Port 1 High-speed PHY Common Block Power-Down Control Bit
     * |        |          |0 = In Suspend or Sleep modes, the REFCLK_LOGIC, Bias and PLL blocks of USB 2.0 port 1 high-speed PHY remain powered
     * |        |          |With this setting, the input reference clock must remain on and valid during suspend or sleep.
     * |        |          |1 = In Suspend mode, the REFCLK_LOGIC, Bias and PLL blocks of USB 2.0 port 1 high-speed PHY are powered down
     * |        |          |In Sleep mode, the Bias and PLL blocks of USB 2.0 port 1 high-speed PHY are powered down.
     * |[23]    |EFUSESEL1 |USB 2.0 Port 1 High-speed PHY Resistor Calibration with External Resistor Control Bit
     * |        |          |0 = An external resistor (REXT) is needed and internal digital calibration code is based on REXT.
     * |        |          |1 = Enable the internal resistor method with RCALCODE1 resistance control up to +/- 18%, allowing the removal of the REXT resistor.
     * |[24]    |PHY1HSTCKSTB|USB 2.0 Port 1 High-speed PHY 60 MHz UTMI Interface Clock for Host Stable Flag
     * |        |          |0 = USB 2.0 port 1 high-speed PHY UTMI Interface clock for Host is not stable.
     * |        |          |1 = USB 2.0 port 1 high-speed PHY UTMI Interface clock for Host is stable.
     * |[25]    |PHY1CK12MSTB|USB 2.0 Port 1 High-speed PHY 12 MHz Clock Stable Flag
     * |        |          |0 = USB 2.0 port 1 high-speed PHY 12 MHz clock is not stable.
     * |        |          |1 = USB 2.0 port 1 high-speed PHY 12 MHz clock is stable.
     * |[27]    |RTUNESEL1 |USB 2.0 Port 1 High-speed PHY Source Impedance Tuning Method Selection
     * |        |          |0 = Internal digital calibration codes are used for tuning the high-speed source impedance.
     * |        |          |1 = The RCALCODE1 value is used for tuning the high-speed source impedance.
     * |[31:28] |RCALCODE1 |USB 2.0 Port 1 High-Speed PHY Internal Resistor Trim Code
     * |        |          |If RTUNESEL1 = 1, RCALCODE1 provides the tuning code for high-speed source impedance directly.
     * |        |          |If RTUNESEL1 = 0, RCALCODE1 provides the tuning code for on-chip resistor within +/- 18% resistance tuning range.
     * |        |          |0000 = +18% (236 u03A9).
     * |        |          |0001 = +15.6%.
     * |        |          |0010 = +13.2%.
     * |        |          |0011 = +10.8%.
     * |        |          |0100 = +8.4%.
     * |        |          |0101 = +6%.
     * |        |          |0110 = +3.6%.
     * |        |          |0111 = +1.2%.
     * |        |          |1000 = -1.2%.
     * |        |          |1001 = -3.6%.
     * |        |          |1010 = -6%.
     * |        |          |1011 = -8.4%.
     * |        |          |1100 = -10.8%.
     * |        |          |1101 = -13.2%.
     * |        |          |1110 = -15.6%.
     * |        |          |1111 = -18% (164 u03A9).
     * @var SYS_T::USBP0PCR
     * Offset: 0x64  USB Port 0 PHY Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |COMPDISTUNE|USB 2.0 High-speed Disconnect Threshold Adjustment
     * |        |          |The SQRXTUNE adjusts the voltage level for the threshold used to detect a disconnect event at the host.
     * |        |          |000 = -5.48%.
     * |        |          |001 = 0. (Default)
     * |        |          |010 = +6.04%.
     * |        |          |011 = +12.75%.
     * |        |          |100 = +19.66%.
     * |        |          |101 = +28.24%.
     * |        |          |110 = +38.31%.
     * |        |          |111 = +50.28%.
     * |[3]     |EQBYPASSENB|USB 2.0 High-speed PHY Squelch Equalizer Bypass Control Bit
     * |        |          |0 = Equalizer is Enabled.
     * |        |          |1 = Equalizer is bypassed and acts as a simple differential input amplifier.
     * |[6:4]   |SQRXTUNE  |USB 2.0 High-speed PHY Squelch Threshold Adjustment
     * |        |          |The SQRXTUNE adjusts the voltage level for the threshold used to detect valid high-speed data.
     * |        |          |000 = +15.5%.
     * |        |          |001 = +10.87%.
     * |        |          |010 = +5.86%.
     * |        |          |011 = 0 (Default).
     * |        |          |100 = -5.86%.
     * |        |          |101 = -13.33%.
     * |        |          |110 = -21.56%.
     * |        |          |111 = -31.54%.
     * |[7]     |TXPREEMPPULSETUNE|USB 2.0 High-speed PHY Squelch Equalizer Bypass Control Bit
     * |        |          |0 = Equalizer is Enabled.
     * |        |          |1 = Equalizer is bypassed and acts as a simple differential input amplifier.
     * |[11:8]  |PLLPTUNE  |USB 2.0 High-speed PHY PLL Proportional Path Tune
     * |        |          |The value of PLLPTUNE should be keep in default.
     * |        |          |0000 = 4.0x.
     * |        |          |0001 = 4.5x.
     * |        |          |0010 = 5.0x.
     * |        |          |0011 = 5.5x.
     * |        |          |0100 = 6.0x.
     * |        |          |0101 = 6.5x.
     * |        |          |0110 = 7.0x.
     * |        |          |0111 = 7.5x.
     * |        |          |1000 = 8.0x.
     * |        |          |1001 = 8.5x.
     * |        |          |1010 = 9.0x.
     * |        |          |1011 = 9.5x.
     * |        |          |1100 = 10.0x (Default).
     * |        |          |1101 = 10.5x.
     * |        |          |1110 = 11.0x.
     * |        |          |1111 = 11.5x.
     * |[15:12] |TXFSLSTUNE|USB 2.0 High-speed PHY FS/LS Source Impedance Adjustment
     * |        |          |The TXFSLSTUNE adjusts the low- and full-speed single-ended source impedance while driving high.
     * |        |          |0000 = +14.2%.
     * |        |          |0001 = +6.60%
     * |        |          |0011 = 0 (Default).
     * |        |          |0111 = -5.48%
     * |        |          |1111 = -10.29%
     * |[17:16] |PLLITUNE  |USB 2.0 High-speed PHY Integral Path Tune
     * |        |          |The value of PLLITUNE should be keep in default.
     * |        |          |00 = 1.0x (Default).
     * |        |          |01 = 2.0x
     * |        |          |10 = 3.0x
     * |        |          |11 = 4.0x
     * |[21:20] |TXPREEMPAMPTUNE|USB 2.0 High-speed PHY HS Transmitter Pre-Emphasis Current Control
     * |        |          |00 = HS Transmitter pre-emphasis is disabled. (Default)
     * |        |          |01 = HS Transmitter pre-emphasis circuit sources 1x pre-emphasis current.
     * |        |          |10 = HS Transmitter pre-emphasis circuit sources 2x pre-emphasis current.
     * |        |          |11 = HS Transmitter pre-emphasis circuit sources 3x pre-emphasis current.
     * |[23:22] |TXRISETUNE|USB 2.0 High-speed PHY HS Transmitter Rise/Fall Time Adjustment
     * |        |          |The TXRISETUNE adjusts the rise/fall times of the high-speed waveform.
     * |        |          |00 = +7.34%.
     * |        |          |01 = 0 (Default)
     * |        |          |10 = -5.98%.
     * |        |          |11 = -7.49%
     * |[27:24] |TXVREFTUNE|USB 2.0 High-speed PHY HS DC Voltage Level Adjustment
     * |        |          |The TXVREFTUNE adjusts the high-speed DC level voltage.
     * |        |          |0000 = -9.37%.
     * |        |          |0001 = -6.24%.
     * |        |          |0010 = -3.12%.
     * |        |          |0011 = 0 (Default)
     * |        |          |0100 = +2.75%.
     * |        |          |0101 = +5.87%.
     * |        |          |0110 = +8.99%.
     * |        |          |0111 = +12.11%.
     * |        |          |1000 = +14.71%.
     * |        |          |1001 = +17.82%.
     * |        |          |1010 = +20.94%.
     * |        |          |1011 = +24.06%.
     * |        |          |1100 = +26.81%.
     * |        |          |1101 = +29.94%.
     * |        |          |1110 = +33.06%.
     * |        |          |1111 = +36.18%.
     * |[29:28] |TXHSXVTUNE|USB 2.0 High-speed PHY Transmitter High-Speed Crossover Adjustment
     * |        |          |The TXHSXVTUNE adjusts the voltage at which the DP and DM signals cross while transmitting in HS mode.
     * |        |          |00 = Reserved
     * |        |          |01 = -9.16mV
     * |        |          |10 = +9.42mV
     * |        |          |11 = 0 (Default)
     * |[31:30] |TXRESTUNE |USB 2.0 High-speed PHY USB Source Impedance Adjustment
     * |        |          |00 = Source Impedance is increased by approximately 3.03 u03A9
     * |        |          |01 = 0 (Default)
     * |        |          |10 = Source Impedance is increased by approximately 2.11 u03A9
     * |        |          |11 = Source Impedance is increased by approximately 4.51 u03A9
     * @var SYS_T::USBP1PCR
     * Offset: 0x68  USB Port 1 PHY Control Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |COMPDISTUNE|USB 2.0 High-speed Disconnect Threshold Adjustment
     * |        |          |The SQRXTUNE adjusts the voltage level for the threshold used to detect a disconnect event at the host.
     * |        |          |000 = -5.48%.
     * |        |          |001 = 0. (Default)
     * |        |          |010 = +6.04%.
     * |        |          |011 = +12.75%.
     * |        |          |100 = +19.66%.
     * |        |          |101 = +28.24%.
     * |        |          |110 = +38.31%.
     * |        |          |111 = +50.28%.
     * |[3]     |EQBYPASSENB|USB 2.0 High-speed PHY Squelch Equalizer Bypass Control Bit
     * |        |          |0 = Equalizer is Enabled.
     * |        |          |1 = Equalizer is bypassed and acts as a simple differential input amplifier.
     * |[6:4]   |SQRXTUNE  |USB 2.0 High-speed PHY Squelch Threshold Adjustment
     * |        |          |The SQRXTUNE adjusts the voltage level for the threshold used to detect valid high-speed data.
     * |        |          |000 = +15.5%.
     * |        |          |001 = +10.87%.
     * |        |          |010 = +5.86%.
     * |        |          |011 = 0 (Default).
     * |        |          |100 = -5.86%.
     * |        |          |101 = -13.33%.
     * |        |          |110 = -21.56%.
     * |        |          |111 = -31.54%.
     * |[7]     |TXPREEMPPULSETUNE|USB 2.0 High-speed PHY Squelch Equalizer Bypass Control Bit
     * |        |          |0 = Equalizer is Enabled.
     * |        |          |1 = Equalizer is bypassed and acts as a simple differential input amplifier.
     * |[11:8]  |PLLPTUNE  |USB 2.0 High-speed PHY PLL Proportional Path Tune
     * |        |          |The value of PLLPTUNE should be keep in default.
     * |        |          |0000 = 4.0x.
     * |        |          |0001 = 4.5x.
     * |        |          |0010 = 5.0x.
     * |        |          |0011 = 5.5x.
     * |        |          |0100 = 6.0x.
     * |        |          |0101 = 6.5x.
     * |        |          |0110 = 7.0x.
     * |        |          |0111 = 7.5x.
     * |        |          |1000 = 8.0x.
     * |        |          |1001 = 8.5x.
     * |        |          |1010 = 9.0x.
     * |        |          |1011 = 9.5x.
     * |        |          |1100 = 10.0x (Default).
     * |        |          |1101 = 10.5x.
     * |        |          |1110 = 11.0x.
     * |        |          |1111 = 11.5x.
     * |[15:12] |TXFSLSTUNE|USB 2.0 High-speed PHY FS/LS Source Impedance Adjustment
     * |        |          |The TXFSLSTUNE adjusts the low- and full-speed single-ended source impedance while driving high.
     * |        |          |0000 = +14.2%.
     * |        |          |0001 = +6.60%
     * |        |          |0011 = 0 (Default).
     * |        |          |0111 = -5.48%
     * |        |          |1111 = -10.29%
     * |[17:16] |PLLITUNE  |USB 2.0 High-speed PHY Integral Path Tune
     * |        |          |The value of PLLITUNE should be keep in default.
     * |        |          |00 = 1.0x (Default).
     * |        |          |01 = 2.0x
     * |        |          |10 = 3.0x
     * |        |          |11 = 4.0x
     * |[21:20] |TXPREEMPAMPTUNE|USB 2.0 High-speed PHY HS Transmitter Pre-Emphasis Current Control
     * |        |          |00 = HS Transmitter pre-emphasis is disabled. (Default)
     * |        |          |01 = HS Transmitter pre-emphasis circuit sources 1x pre-emphasis current.
     * |        |          |10 = HS Transmitter pre-emphasis circuit sources 2x pre-emphasis current.
     * |        |          |11 = HS Transmitter pre-emphasis circuit sources 3x pre-emphasis current.
     * |[23:22] |TXRISETUNE|USB 2.0 High-speed PHY HS Transmitter Rise/Fall Time Adjustment
     * |        |          |The TXRISETUNE adjusts the rise/fall times of the high-speed waveform.
     * |        |          |00 = +7.34%.
     * |        |          |01 = 0 (Default)
     * |        |          |10 = -5.98%.
     * |        |          |11 = -7.49%
     * |[27:24] |TXVREFTUNE|USB 2.0 High-speed PHY HS DC Voltage Level Adjustment
     * |        |          |The TXVREFTUNE adjusts the high-speed DC level voltage.
     * |        |          |0000 = -9.37%.
     * |        |          |0001 = -6.24%.
     * |        |          |0010 = -3.12%.
     * |        |          |0011 = 0 (Default)
     * |        |          |0100 = +2.75%.
     * |        |          |0101 = +5.87%.
     * |        |          |0110 = +8.99%.
     * |        |          |0111 = +12.11%.
     * |        |          |1000 = +14.71%.
     * |        |          |1001 = +17.82%.
     * |        |          |1010 = +20.94%.
     * |        |          |1011 = +24.06%.
     * |        |          |1100 = +26.81%.
     * |        |          |1101 = +29.94%.
     * |        |          |1110 = +33.06%.
     * |        |          |1111 = +36.18%.
     * |[29:28] |TXHSXVTUNE|USB 2.0 High-speed PHY Transmitter High-Speed Crossover Adjustment
     * |        |          |The TXHSXVTUNE adjusts the voltage at which the DP and DM signals cross while transmitting in HS mode.
     * |        |          |00 = Reserved
     * |        |          |01 = -9.16mV
     * |        |          |10 = +9.42mV
     * |        |          |11 = 0 (Default)
     * |[31:30] |TXRESTUNE |USB 2.0 High-speed PHY USB Source Impedance Adjustment
     * |        |          |00 = Source Impedance is increased by approximately 3.03 u03A9
     * |        |          |01 = 0 (Default)
     * |        |          |10 = Source Impedance is increased by approximately 2.11 u03A9
     * |        |          |11 = Source Impedance is increased by approximately 4.51 u03A9
     * @var SYS_T::MISCFCR0
     * Offset: 0x70  Miscellaneous Function Control Register 0 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RTPICACHEN|Real-time Cortex-M4 Processor Instruction Cache Enable Bit (SUBM)
     * |        |          |0 = Real-Time Cortex-M4 processor instruction cache Disabled.
     * |        |          |1 = Real-Time Cortex-M4 processor instruction cache Enabled.
     * |[1]     |RTPDCACHEN|Real-time Cortex-M4 Processor Data Cache Enable Bit (SUBM)
     * |        |          |0 = Real-Time Cortex-M4 processor data cache Disabled.
     * |        |          |1 = Real-Time Cortex-M4 processor data cache Enabled.
     * |[8]     |WDT0RSTEN |WatchDog Timer 0 Reset Connection Enable Bit
     * |        |          |This bit is use to enable the function that connect watch-dog timer 0 reset to nRESET pin
     * |        |          |If this bit is enabled, the watch-dog timer 0 reset is connected to nRESET pin internally
     * |        |          |0 = Watch-dog timer 0 reset not connected to nRESET pin internally.
     * |        |          |1 = Watch-dog timer 0 reset connected to nRESET pin internally.
     * |[9]     |HDSPUEN   |HDS Pin Internal Pull-up Enable Bit (TZNS)
     * |        |          |0 = HDS pin internal pull-up resister Disabled.
     * |        |          |1 = HDS pin internal pull-up resister Enabled.
     * |[12]    |UHOVRCURH |USB Host Overcurrent Detection High Active (TZNS)
     * |        |          |0 = USB host overcurrent detection signal is low active.
     * |        |          |1 = USB host overcurrent detection signal is high active.
     * |[13]    |SELFTEST  |Self-test Mode Enable Bit
     * |        |          |0 = Self-Test mode Disabled.
     * |        |          |1 = Self-Test mode Enabled.
     * |[14]    |WDT1RSTEN |WatchDog Timer 1 Reset Connection Enable Bit (TZNS)
     * |        |          |This bit is use to enable the function that connect watch-dog timer 1 reset to nRESET pin
     * |        |          |If this bit is enabled, the watch-dog timer 1 reset is connected to nRESET pin internally
     * |        |          |0 = Watch-dog timer 1 reset not connected to nRESET pin internally.
     * |        |          |1 = Watch-dog timer 1 reset connected to nRESET pin internally.
     * |[15]    |WDT2RSTEN |WatchDog Timer 2 Reset Connection Enable Bit (SUBM)
     * |        |          |This bit is use to enable the function that connect watch-dog timer 2 reset to nRESET pin
     * |        |          |If this bit is enabled, the watch-dog timer 2 reset is connected to nRESET pin internally
     * |        |          |0 = Watch-dog timer 2 reset not connected to nRESET pin internally.
     * |        |          |1 = Watch-dog timer 2 reset connected to nRESET pin internally.
     * |[16]    |SDH0VSTB  |Voltage Stable Indicator to SDH 0 (TZNS)
     * |        |          |Set this bit high to indicate SDH 0 that I/O voltage is stable.
     * |        |          |0 = Voltage of I/O used as SDH 0 is not stable.
     * |        |          |1 = Voltage of I/O used as SDH 0 is stable.
     * |[17]    |SDH1VSTB  |Voltage Stable Indicator to SDH 1 (TZNS)
     * |        |          |Set this bit high to indicate SDH 1 that I/O voltage is stable.
     * |        |          |0 = Voltage of I/O used as SDH 1 is not stable.
     * |        |          |1 = Voltage of I/O used as SDH 1 is stable.
     * |[18]    |VBUSWKEN  |HSUSBD VBUS Detect Wakeup Enable Control Bit (TZNS)
     * |        |          |0 = HSUSBD VBUS detect wakeup system from Power-down mode Disabled.
     * |        |          |1 = HSUSBD VBUS detect wakeup system from Power-down mode Enabled.
     * |[19]    |LNSTWKEN  |HSUSBD Line State Wakeup Enable Control Bit (TZNS)
     * |        |          |0 = HSUSBD line state wakeup system from Power-down mode Disabled.
     * |        |          |1 = HSUSBD line state wakeup system from Power-down mode Enabled.
     * |[23]    |DDRCGDIS  |DDR Controller Core Clock Gating Disable Bit
     * |        |          |0 = DDR controller core clock gating in auto self-refresh mode Enabled.
     * |        |          |1 = DDR controller core clock gating in auto self-refresh mode Disabled.
     * |        |          |Note: This register needs to be set to 1'b1 to bypass clock gating function of DDR core clock before user writes/reads control registers or status registers of DDR memory controller.
     * |        |          |Therefore the signals in PCLK domain of DDR memory controller can be synchronous to core clock domain of DDR memory controller, and the signals in core clock domain of DDR memory controller can be synchronous to PCLK domain of DDR memory controller correctly.
     * |        |          |After user writes/reads control registers or status registers of DDR memory controller, this register can be set to 1'b0 to enable clock gating function of DDR core clock.
     * |[31:24] |DRATSRDLY |DDR Auto Self Refresh Delay Count
     * |        |          |This register uses to set the delay cycles of DDR memory controller before the core clock of DDR memory controller is gating
     * |        |          |It allows for the self-refresh status to propagate to the APB domain so the STAT.selfref_type register field also reflects the status.
     * |        |          |It is sufficient to set this delay cycles to 31 cycles normally
     * |        |          |In particular, if the AXI frequency is much less than the DDRC frequency, a higher value may be required in order to ensure that all read data is synchronized to the AXI domain before the clock is removed.
     * |        |          |Note: User can set this register value during core reset of DDR memory controller is asserted (i.e
     * |        |          |MCTLCRST (SYS_IPRST0[29]) set to 1'b1).
     * @var SYS_T::MISCFCR1
     * Offset: 0x74  Miscellaneous Function Control Register 1 (Shared)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CANFD0PDEN|CAN FD 0 Power Down Enable Bit
     * |        |          |0 = CAN FD 0 Power-down mode Disabled.
     * |        |          |1 = CAN FD 0 Power-down mode Enabled.
     * |[1]     |CANFD1PDEN|CAN FD 1 Power Down Enable Bit
     * |        |          |0 = CAN FD 1 Power-down mode Disabled.
     * |        |          |1 = CAN FD 1 Power-down mode Enabled.
     * |[2]     |CANFD2PDEN|CAN FD 2 Power Down Enable Bit
     * |        |          |0 = CAN FD 2 Power-down mode Disabled.
     * |        |          |1 = CAN FD 2 Power-down mode Enabled.
     * |[3]     |CANFD3PDEN|CAN FD 3 Power Down Enable Bit
     * |        |          |0 = CAN FD 3 Power-down mode Disabled.
     * |        |          |1 = CAN FD 3 Power-down mode Enabled.
     * |[4]     |CANFD0CKSTP|CAN FD 0 Clock Stop Acknowledgement (Read Only)
     * |        |          |0 = CAN FD 0 clock didn't stop.
     * |        |          |1 = CAN FD 0 clock stop.
     * |[5]     |CANFD1CKSTP|CAN FD 1 Clock Stop Acknowledgement (Read Only)
     * |        |          |0 = CAN FD 1 clock didn't stop.
     * |        |          |1 = CAN FD 1 clock stop.
     * |[6]     |CANFD2CKSTP|CAN FD 2 Clock Stop Acknowledgement (Read Only)
     * |        |          |0 = CAN FD 2 clock didn't stop.
     * |        |          |1 = CAN FD 2 clock stop.
     * |[7]     |CANFD3CKSTP|CAN FD 3 Clock Stop Acknowledgement (Read Only)
     * |        |          |0 = CAN FD 3 clock didn't stop.
     * |        |          |1 = CAN FD 3 clock stop.
     * |[9:8]   |HXTDS     |HXT Driving Current Selection (Write Protect)
     * |        |          |00 = Low power consumption mode for 2.5V~3.3V operating voltage.
     * |        |          |01 = High noise immunity mode for 2.5V~3.3V operating voltage.
     * |        |          |10 = Low power consumption mode for 1.8V~2.5V operating voltage.
     * |        |          |11 = High noise immunity mode for 1.8V~2.5V operating voltage.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[15:12] |TSENSRTRIM|Temperature Sensor VTRIM (Write Protect)
     * |        |          |Trimming for temperature sensor calibration.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[16]    |RMEL1RAM  |Cortex-A35 L1 Cache SRAM Macro RME Control Bit (Write Protect)
     * |        |          |0 = Default read-write margin of Cortex-A35 L1 cache SRAM selected.
     * |        |          |1 = High speed read-write margin of Cortex-A35 L1 cache SRAM selected.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * |[17]    |RMESYSRAM |System SRAM Macro RME Control Bit (Write Protect)
     * |        |          |0 = Default read-write margin of system SRAM selected.
     * |        |          |1 = High speed read-write margin of system SRAM selected.
     * |        |          |Note: This bit is write protected
     * |        |          |Refer to the SYS_RLKTZS, SYS_RLKTZNS or SYS_RLKSUBM register according to security attribute of each circuit.
     * @var SYS_T::MISCIER
     * Offset: 0x78  Miscellaneous Interrupt Enable Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LVDIEN    |Low Voltage Detect Interrupt Enable Bit
     * |        |          |0 = Low voltage detect interrupt Disabled.
     * |        |          |1 = Low voltage detect interrupt Enabled.
     * |[1]     |USB0IDCHGIEN|USB0_ID Pin Status Change Interrupt Enable Bit
     * |        |          |0 = USB0_ID pin status change interrupt Disabled.
     * |        |          |1 = USB0_ID pin status change interrupt Enabled.
     * |[2]     |VBUSCHGIEN|USUSB0_VBUSVLD Pin Status Change Interrupt Enable Bit
     * |        |          |0 = USUSB0_VBUSVLD pin status change interrupt Disabled.
     * |        |          |1 = USUSB0_VBUSVLD pin status change interrupt Enabled.
     * @var SYS_T::MISCISR
     * Offset: 0x7C  Miscellaneous Interrupt Status Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LVDIF     |Low Voltage Detect Interrupt Flag
     * |        |          |0 = No low voltage event.
     * |        |          |1 = Low voltage event detected.
     * |[1]     |USB0IDCHGIF|USB0_ID Pin State Change Interrupt Flag
     * |        |          |0 = USB0_ID state didn't change.
     * |        |          |1 = USB0_ID state changed from low to high or from high to low.
     * |[2]     |VBUSCHGIF |USUSB0_VBUSVLD Pin State Change Interrupt Flag
     * |        |          |0 = USUSB0_VBUSVLD pin state didn't change.
     * |        |          |1 = USUSB0_VBUSVLD pin state changed from low to high or from high to low.
     * |[16]    |LVDSTS    |Low Voltage Detect State
     * |        |          |0 = Low voltage detect state is low.
     * |        |          |1 = Low voltage detect state is high.
     * |[17]    |USB0IDSTS |USB0_ID Pin State
     * |        |          |0 = USB port 0 used as a USB device port.
     * |        |          |1 = USB port 0 used as a USB host port.
     * |[18]    |VBUSSTS   |VBUS Detect Pin State
     * |        |          |0 = VBUS detect pin state is low.
     * |        |          |1 = VBUS detect pin state is high.
     * @var SYS_T::GPA_MFPL
     * Offset: 0x80  GPIOA Low Byte Multiple Function Control Register
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
     * Offset: 0x84  GPIOA High Byte Multiple Function Control Register
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
     * Offset: 0x88  GPIOB Low Byte Multiple Function Control Register
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
     * Offset: 0x8C  GPIOB High Byte Multiple Function Control Register
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
     * Offset: 0x90  GPIOC Low Byte Multiple Function Control Register
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
     * Offset: 0x94  GPIOC High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PC8MFP    |PC.8 Multi-function Pin Selection
     * |[7:4]   |PC9MFP    |PC.9 Multi-function Pin Selection
     * |[11:8]  |PC10MFP   |PC.10 Multi-function Pin Selection
     * |[15:12] |PC11MFP   |PC.11 Multi-function Pin Selection
     * |[19:16] |PC12MFP   |PC.12 Multi-function Pin Selection
     * |[23:20] |PC13MFP   |PC.13 Multi-function Pin Selection
     * |[27:24] |PC14MFP   |PC.14 Multi-function Pin Selection
     * |[31:28] |PC15MFP   |PC.15 Multi-function Pin Selection
     * @var SYS_T::GPD_MFPL
     * Offset: 0x98  GPIOD Low Byte Multiple Function Control Register
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
     * Offset: 0x9C  GPIOD High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PD8MFP    |PD.8 Multi-function Pin Selection
     * |[7:4]   |PD9MFP    |PD.9 Multi-function Pin Selection
     * |[11:8]  |PD10MFP   |PD.10 Multi-function Pin Selection
     * |[15:12] |PD11MFP   |PD.11 Multi-function Pin Selection
     * |[19:16] |PD12MFP   |PD.12 Multi-function Pin Selection
     * |[23:20] |PD13MFP   |PD.13 Multi-function Pin Selection
     * |[27:24] |PD14MFP   |PD.14 Multi-function Pin Selection
     * |[31:28] |PD15MFP   |PD.15 Multi-function Pin Selection
     * @var SYS_T::GPE_MFPL
     * Offset: 0xA0  GPIOE Low Byte Multiple Function Control Register
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
     * Offset: 0xA4  GPIOE High Byte Multiple Function Control Register
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
     * Offset: 0xA8  GPIOF Low Byte Multiple Function Control Register
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
     * Offset: 0xAC  GPIOF High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PF8MFP    |PF.8 Multi-function Pin Selection
     * |[7:4]   |PF9MFP    |PF.9 Multi-function Pin Selection
     * |[11:8]  |PF10MFP   |PF.10 Multi-function Pin Selection
     * |[15:12] |PF11MFP   |PF.11 Multi-function Pin Selection
     * |[19:16] |PF12MFP   |PF.12 Multi-function Pin Selection
     * |[23:20] |PF13MFP   |PF.13 Multi-function Pin Selection
     * |[27:24] |PF14MFP   |PF.14 Multi-function Pin Selection
     * |[31:28] |PF15MFP   |PF.15 Multi-function Pin Selection
     * @var SYS_T::GPG_MFPL
     * Offset: 0xB0  GPIOG Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PG0MFP    |PG.0 Multi-function Pin Selection
     * |[7:4]   |PG1MFP    |PG.1 Multi-function Pin Selection
     * |[11:8]  |PG2MFP    |PG.2 Multi-function Pin Selection
     * |[15:12] |PG3MFP    |PG.3 Multi-function Pin Selection
     * |[19:16] |PG4MFP    |PG.4 Multi-function Pin Selection
     * |[23:20] |PG5MFP    |PG.5 Multi-function Pin Selection
     * |[27:24] |PG6MFP    |PG.6 Multi-function Pin Selection
     * |[31:28] |PG7MFP    |PG.7 Multi-function Pin Selection
     * @var SYS_T::GPG_MFPH
     * Offset: 0xB4  GPIOG High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PG8MFP    |PG.8 Multi-function Pin Selection
     * |[7:4]   |PG9MFP    |PG.9 Multi-function Pin Selection
     * |[11:8]  |PG10MFP   |PG.10 Multi-function Pin Selection
     * |[15:12] |PG11MFP   |PG.11 Multi-function Pin Selection
     * |[19:16] |PG12MFP   |PG.12 Multi-function Pin Selection
     * |[23:20] |PG13MFP   |PG.13 Multi-function Pin Selection
     * |[27:24] |PG14MFP   |PG.14 Multi-function Pin Selection
     * |[31:28] |PG15MFP   |PG.15 Multi-function Pin Selection
     * @var SYS_T::GPH_MFPL
     * Offset: 0xB8  GPIOH Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PH0MFP    |PH.0 Multi-function Pin Selection
     * |[7:4]   |PH1MFP    |PH.1 Multi-function Pin Selection
     * |[11:8]  |PH2MFP    |PH.2 Multi-function Pin Selection
     * |[15:12] |PH3MFP    |PH.3 Multi-function Pin Selection
     * |[19:16] |PH4MFP    |PH.4 Multi-function Pin Selection
     * |[23:20] |PH5MFP    |PH.5 Multi-function Pin Selection
     * |[27:24] |PH6MFP    |PH.6 Multi-function Pin Selection
     * |[31:28] |PH7MFP    |PH.7 Multi-function Pin Selection
     * @var SYS_T::GPH_MFPH
     * Offset: 0xBC  GPIOH High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PH8MFP    |PH.8 Multi-function Pin Selection
     * |[7:4]   |PH9MFP    |PH.9 Multi-function Pin Selection
     * |[11:8]  |PH10MFP   |PH.10 Multi-function Pin Selection
     * |[15:12] |PH11MFP   |PH.11 Multi-function Pin Selection
     * |[19:16] |PH12MFP   |PH.12 Multi-function Pin Selection
     * |[23:20] |PH13MFP   |PH.13 Multi-function Pin Selection
     * |[27:24] |PH14MFP   |PH.14 Multi-function Pin Selection
     * |[31:28] |PH15MFP   |PH.15 Multi-function Pin Selection
     * @var SYS_T::GPI_MFPL
     * Offset: 0xC0  GPIOI Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PI0MFP    |PI.0 Multi-function Pin Selection
     * |[7:4]   |PI1MFP    |PI.1 Multi-function Pin Selection
     * |[11:8]  |PI2MFP    |PI.2 Multi-function Pin Selection
     * |[15:12] |PI3MFP    |PI.3 Multi-function Pin Selection
     * |[19:16] |PI4MFP    |PI.4 Multi-function Pin Selection
     * |[23:20] |PI5MFP    |PI.5 Multi-function Pin Selection
     * |[27:24] |PI6MFP    |PI.6 Multi-function Pin Selection
     * |[31:28] |PI7MFP    |PI.7 Multi-function Pin Selection
     * @var SYS_T::GPI_MFPH
     * Offset: 0xC4  GPIOI High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PI8MFP    |PI.8 Multi-function Pin Selection
     * |[7:4]   |PI9MFP    |PI.9 Multi-function Pin Selection
     * |[11:8]  |PI10MFP   |PI.10 Multi-function Pin Selection
     * |[15:12] |PI11MFP   |PI.11 Multi-function Pin Selection
     * |[19:16] |PI12MFP   |PI.12 Multi-function Pin Selection
     * |[23:20] |PI13MFP   |PI.13 Multi-function Pin Selection
     * |[27:24] |PI14MFP   |PI.14 Multi-function Pin Selection
     * |[31:28] |PI15MFP   |PI.15 Multi-function Pin Selection
     * @var SYS_T::GPJ_MFPL
     * Offset: 0xC8  GPIOJ Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PJ0MFP    |PJ.0 Multi-function Pin Selection
     * |[7:4]   |PJ1MFP    |PJ.1 Multi-function Pin Selection
     * |[11:8]  |PJ2MFP    |PJ.2 Multi-function Pin Selection
     * |[15:12] |PJ3MFP    |PJ.3 Multi-function Pin Selection
     * |[19:16] |PJ4MFP    |PJ.4 Multi-function Pin Selection
     * |[23:20] |PJ5MFP    |PJ.5 Multi-function Pin Selection
     * |[27:24] |PJ6MFP    |PJ.6 Multi-function Pin Selection
     * |[31:28] |PJ7MFP    |PJ.7 Multi-function Pin Selection
     * @var SYS_T::GPJ_MFPH
     * Offset: 0xCC  GPIOJ High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PJ8MFP    |PJ.8 Multi-function Pin Selection
     * |[7:4]   |PJ9MFP    |PJ.9 Multi-function Pin Selection
     * |[11:8]  |PJ10MFP   |PJ.10 Multi-function Pin Selection
     * |[15:12] |PJ11MFP   |PJ.11 Multi-function Pin Selection
     * |[19:16] |PJ12MFP   |PJ.12 Multi-function Pin Selection
     * |[23:20] |PJ13MFP   |PJ.13 Multi-function Pin Selection
     * |[27:24] |PJ14MFP   |PJ.14 Multi-function Pin Selection
     * |[31:28] |PJ15MFP   |PJ.15 Multi-function Pin Selection
     * @var SYS_T::GPK_MFPL
     * Offset: 0xD0  GPIOK Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PK0MFP    |PK.0 Multi-function Pin Selection
     * |[7:4]   |PK1MFP    |PK.1 Multi-function Pin Selection
     * |[11:8]  |PK2MFP    |PK.2 Multi-function Pin Selection
     * |[15:12] |PK3MFP    |PK.3 Multi-function Pin Selection
     * |[19:16] |PK4MFP    |PK.4 Multi-function Pin Selection
     * |[23:20] |PK5MFP    |PK.5 Multi-function Pin Selection
     * |[27:24] |PK6MFP    |PK.6 Multi-function Pin Selection
     * |[31:28] |PK7MFP    |PK.7 Multi-function Pin Selection
     * @var SYS_T::GPK_MFPH
     * Offset: 0xD4  GPIOK High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PK8MFP    |PK.8 Multi-function Pin Selection
     * |[7:4]   |PK9MFP    |PK.9 Multi-function Pin Selection
     * |[11:8]  |PK10MFP   |PK.10 Multi-function Pin Selection
     * |[15:12] |PK11MFP   |PK.11 Multi-function Pin Selection
     * |[19:16] |PK12MFP   |PK.12 Multi-function Pin Selection
     * |[23:20] |PK13MFP   |PK.13 Multi-function Pin Selection
     * |[27:24] |PK14MFP   |PK.14 Multi-function Pin Selection
     * |[31:28] |PK15MFP   |PK.15 Multi-function Pin Selection
     * @var SYS_T::GPL_MFPL
     * Offset: 0xD8  GPIOL Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PL0MFP    |PL.0 Multi-function Pin Selection
     * |[7:4]   |PL1MFP    |PL.1 Multi-function Pin Selection
     * |[11:8]  |PL2MFP    |PL.2 Multi-function Pin Selection
     * |[15:12] |PL3MFP    |PL.3 Multi-function Pin Selection
     * |[19:16] |PL4MFP    |PL.4 Multi-function Pin Selection
     * |[23:20] |PL5MFP    |PL.5 Multi-function Pin Selection
     * |[27:24] |PL6MFP    |PL.6 Multi-function Pin Selection
     * |[31:28] |PL7MFP    |PL.7 Multi-function Pin Selection
     * @var SYS_T::GPL_MFPH
     * Offset: 0xDC  GPIOL High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PL8MFP    |PL.8 Multi-function Pin Selection
     * |[7:4]   |PL9MFP    |PL.9 Multi-function Pin Selection
     * |[11:8]  |PL10MFP   |PL.10 Multi-function Pin Selection
     * |[15:12] |PL11MFP   |PL.11 Multi-function Pin Selection
     * |[19:16] |PL12MFP   |PL.12 Multi-function Pin Selection
     * |[23:20] |PL13MFP   |PL.13 Multi-function Pin Selection
     * |[27:24] |PL14MFP   |PL.14 Multi-function Pin Selection
     * |[31:28] |PL15MFP   |PL.15 Multi-function Pin Selection
     * @var SYS_T::GPM_MFPL
     * Offset: 0xE0  GPIOM Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PM0MFP    |PM.0 Multi-function Pin Selection
     * |[7:4]   |PM1MFP    |PM.1 Multi-function Pin Selection
     * |[11:8]  |PM2MFP    |PM.2 Multi-function Pin Selection
     * |[15:12] |PM3MFP    |PM.3 Multi-function Pin Selection
     * |[19:16] |PM4MFP    |PM.4 Multi-function Pin Selection
     * |[23:20] |PM5MFP    |PM.5 Multi-function Pin Selection
     * |[27:24] |PM6MFP    |PM.6 Multi-function Pin Selection
     * |[31:28] |PM7MFP    |PM.7 Multi-function Pin Selection
     * @var SYS_T::GPM_MFPH
     * Offset: 0xE4  GPIOM High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PM8MFP    |PM.8 Multi-function Pin Selection
     * |[7:4]   |PM9MFP    |PM.9 Multi-function Pin Selection
     * |[11:8]  |PM10MFP   |PM.10 Multi-function Pin Selection
     * |[15:12] |PM11MFP   |PM.11 Multi-function Pin Selection
     * |[19:16] |PM12MFP   |PM.12 Multi-function Pin Selection
     * |[23:20] |PM13MFP   |PM.13 Multi-function Pin Selection
     * |[27:24] |PM14MFP   |PM.14 Multi-function Pin Selection
     * |[31:28] |PM15MFP   |PM.15 Multi-function Pin Selection
     * @var SYS_T::GPN_MFPL
     * Offset: 0xE8  GPION Low Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PN0MFP    |PN.0 Multi-function Pin Selection
     * |[7:4]   |PN1MFP    |PN.1 Multi-function Pin Selection
     * |[11:8]  |PN2MFP    |PN.2 Multi-function Pin Selection
     * |[15:12] |PN3MFP    |PN.3 Multi-function Pin Selection
     * |[19:16] |PN4MFP    |PN.4 Multi-function Pin Selection
     * |[23:20] |PN5MFP    |PN.5 Multi-function Pin Selection
     * |[27:24] |PN6MFP    |PN.6 Multi-function Pin Selection
     * |[31:28] |PN7MFP    |PN.7 Multi-function Pin Selection
     * @var SYS_T::GPN_MFPH
     * Offset: 0xEC  GPION High Byte Multiple Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PN8MFP    |PN.8 Multi-function Pin Selection
     * |[7:4]   |PN9MFP    |PN.9 Multi-function Pin Selection
     * |[11:8]  |PN10MFP   |PN.10 Multi-function Pin Selection
     * |[15:12] |PN11MFP   |PN.11 Multi-function Pin Selection
     * |[19:16] |PN12MFP   |PN.12 Multi-function Pin Selection
     * |[23:20] |PN13MFP   |PN.13 Multi-function Pin Selection
     * |[27:24] |PN14MFP   |PN.14 Multi-function Pin Selection
     * |[31:28] |PN15MFP   |PN.15 Multi-function Pin Selection
     * @var SYS_T::TSENSRFCR
     * Offset: 0x104  Temperature Sensor Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |TSENSRREF0|Temperature Sensor Reference Value 0
     * |        |          |TSENSRREF0 keeps 8-bit value measured at 25C for temperature conversion formula variable A calibration.
     * |[15:8]  |TSENSRREF1|Temperature Sensor Reference Value 1
     * |        |          |TSENSRREF1 keeps 8-bit value measured at 25C for temperature conversion formula variable B calibration.
     * |[27:16] |TSENSRDATA|Temperature Sensor Data
     * |        |          |TSENSRDATA keeps 12-bit value measured by temperature sensor.
     * |[28]    |PD        |Temperature Sensor Power Down
     * |        |          |0 = Temperature sensor data is in normal operation.
     * |        |          |1 = Temperature sensor data is in power down.
     * |[29]    |REFUDEN   |Temperature Sensor Reference Data Update Enable Bit
     * |        |          |0 = Write to update TSENSRREF0 and TSENSRREF1 is Disabled.
     * |        |          |1 = Write to update TSENSRREF0 and TSENSRREF1 is Enabled.
     * |[31]    |DATAVALID |Temperature Sensor Data Valid
     * |        |          |0 = Temperature sensor data in TSENSRDATA is not valid.
     * |        |          |1 = Temperature sensor data in TSENSRDATA is valid.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * @var SYS_T::GMAC0MISCR
     * Offset: 0x108  GMAC 0 Miscellaneous Control Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RMIIEN    |RMII Mode Enable Bit
     * |        |          |0 = GMAC 0 is in RGMII mode.
     * |        |          |1 = GMAC 0 is in RMII mode.
     * |[1]     |PFRMTXEN  |Pause Frame Transmit Enable Bit
     * |        |          |0 = Pause frame transmit Disabled.
     * |        |          |1 = Pause frame transmit Enabled.
     * |[8]     |TXCLKINV  |Transmit Clock Inverter Enable Bit
     * |        |          |0 = Transmit clock (output) inverter Disabled.
     * |        |          |1 = Transmit clock (output) inverter Enabled.
     * |        |          |Note: This bit is reserved when GMAC 0 is in RMII mode.
     * |[9]     |TXCLKGEN  |Transmit Clock Gating Enable Bit
     * |        |          |0 = Transmit clock (output) gating when entered LPI mode Disabled.
     * |        |          |1 = Transmit clock (output) gating when entered LPI mode Enabled.
     * |        |          |Note: This bit is reserved when GMAC 0 is in RMII mode.
     * |[12]    |RXCLKINV  |Receive Clock Inverter Enable Bit
     * |        |          |0 = Receive clock (input) inverter Disabled.
     * |        |          |1 = Receive clock (input) inverter Enabled.
     * |        |          |Note: This bit is reserved when GMAC 0 is in RMII mode.
     * |[19:16] |TXCLKDLY  |Transmit Clock Path Delay Control
     * |        |          |0000 = 0.00ns (Default).
     * |        |          |0001 = 0.13ns.
     * |        |          |0010 = 0.27ns.
     * |        |          |0011 = 0.40ns.
     * |        |          |0100 = 0.53ns.
     * |        |          |0101 = 0.67ns.
     * |        |          |0110 = 0.80ns.
     * |        |          |0111 = 0.93ns.
     * |        |          |1000 = 1.07ns.
     * |        |          |1001 = 1.20ns.
     * |        |          |1010 = 1.33ns.
     * |        |          |1011 = 1.47ns.
     * |        |          |1100 = 1.60ns.
     * |        |          |1101 = 1.73ns.
     * |        |          |1110 = 1.87ns.
     * |        |          |1111 = 2.00ns.
     * |        |          |Note: These bits are reserved when GMAC 0 is in RMII mode.
     * |[23:20] |RXCLKDLY  |Receive Clock Path Delay Control
     * |        |          |0000 = 0.00ns (Default).
     * |        |          |0001 = 0.13ns.
     * |        |          |0010 = 0.27ns.
     * |        |          |0011 = 0.40ns.
     * |        |          |0100 = 0.53ns.
     * |        |          |0101 = 0.67ns.
     * |        |          |0110 = 0.80ns.
     * |        |          |0111 = 0.93ns.
     * |        |          |1000 = 1.07ns.
     * |        |          |1001 = 1.20ns.
     * |        |          |1010 = 1.33ns.
     * |        |          |1011 = 1.47ns.
     * |        |          |1100 = 1.60ns.
     * |        |          |1101 = 1.73ns.
     * |        |          |1110 = 1.87ns.
     * |        |          |1111 = 2.00ns.
     * |        |          |Note: These bits are reserved when GMAC 0 is in RMII mode.
     * @var SYS_T::GMAC1MISCR
     * Offset: 0x10C  GMAC 1 Miscellaneous Control Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RMIIEN    |RMII Mode Enable Bit
     * |        |          |0 = GMAC 1 is in RGMII mode.
     * |        |          |1 = GMAC 1 is in RMII mode.
     * |[1]     |PFRMTXEN  |Pause Frame Transmit Enable Bit
     * |        |          |0 = Pause frame transmit Disabled.
     * |        |          |1 = Pause frame transmit Enabled.
     * |[8]     |TXCLKINV  |Transmit Clock Inverter Enable Bit
     * |        |          |0 = Transmit clock (output) inverter Disabled.
     * |        |          |1 = Transmit clock (output) inverter Enabled.
     * |        |          |Note: This bit is reserved when GMAC 1 is in RMII mode.
     * |[9]     |TXCLKGEN  |Transmit Clock Gating Enable Bit
     * |        |          |0 = Transmit clock (output) gating when entered LPI mode Disabled.
     * |        |          |1 = Transmit clock (output) gating when entered LPI mode Enabled.
     * |        |          |Note: This bit is reserved when GMAC 1 is in RMII mode.
     * |[12]    |RXCLKINV  |Receive Clock Inverter Enable Bit
     * |        |          |0 = Receive clock (input) inverter Disabled.
     * |        |          |1 = Receive clock (input) inverter Enabled.
     * |        |          |Note: This bit is reserved when GMAC 1 is in RMII mode.
     * |[19:16] |TXCLKDLY  |Transmit Clock Path Delay Control
     * |        |          |0000 = 0.00ns (Default).
     * |        |          |0001 = 0.13ns.
     * |        |          |0010 = 0.27ns.
     * |        |          |0011 = 0.40ns.
     * |        |          |0100 = 0.53ns.
     * |        |          |0101 = 0.67ns.
     * |        |          |0110 = 0.80ns.
     * |        |          |0111 = 0.93ns.
     * |        |          |1000 = 1.07ns.
     * |        |          |1001 = 1.20ns.
     * |        |          |1010 = 1.33ns.
     * |        |          |1011 = 1.47ns.
     * |        |          |1100 = 1.60ns.
     * |        |          |1101 = 1.73ns.
     * |        |          |1110 = 1.87ns.
     * |        |          |1111 = 2.00ns.
     * |        |          |Note: These bits are reserved when GMAC 1 is in RMII mode.
     * |[23:20] |RXCLKDLY  |Receive Clock Path Delay Control
     * |        |          |0000 = 0.00ns (Default).
     * |        |          |0001 = 0.13ns.
     * |        |          |0010 = 0.27ns.
     * |        |          |0011 = 0.40ns.
     * |        |          |0100 = 0.53ns.
     * |        |          |0101 = 0.67ns.
     * |        |          |0110 = 0.80ns.
     * |        |          |0111 = 0.93ns.
     * |        |          |1000 = 1.07ns.
     * |        |          |1001 = 1.20ns.
     * |        |          |1010 = 1.33ns.
     * |        |          |1011 = 1.47ns.
     * |        |          |1100 = 1.60ns.
     * |        |          |1101 = 1.73ns.
     * |        |          |1110 = 1.87ns.
     * |        |          |1111 = 2.00ns.
     * |        |          |Note: These bits are reserved when GMAC 1 is in RMII mode.
     * @var SYS_T::MACAD0LSR
     * Offset: 0x110  MAC Address 0 Low Significant Word Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MACADRLSR |MAC Address Low Significant Word Register
     * @var SYS_T::MACAD0HSR
     * Offset: 0x114  MAC Address 0 High Significant Word Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MACADRHSR |MAC Address High Significant Word Register
     * @var SYS_T::MACAD1LSR
     * Offset: 0x118  MAC Address 1 Low Significant Word Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MACADRLSR |MAC Address Low Significant Word Register
     * @var SYS_T::MACAD1HSR
     * Offset: 0x11C  MAC Address 1 High Significant Word Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MACADRHSR |MAC Address High Significant Word Register
     * @var SYS_T::CSDBGCTL
     * Offset: 0x120  CoreSight Debug Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DBGRST    |Debug Reset Bit
     * |        |          |0 = Release the reset for all debug component including A35, RTP and Coresight
     * |        |          |1 = Reset all debug component including A35, RTP and Coresight
     * |[1]     |DBGPWRUPREQ|Debug Power Up Request Bit
     * |        |          |0 = Disable the power-up request.
     * |        |          |1 = Enable the power-up request
     * |        |          |Note: If user wants to do self-hosted debug, it has to write the DBGPWRUPREQ to 1, and check the DBGPWRUPACK to 1 before self-hosted debug start
     * |        |          |This bit will enable A35 power and clock and RTP clock.
     * |[2]     |DBGPWRUPACK|Debug Power Up Acknowledge Bit
     * |        |          |0 = Debug power-up request is not ready
     * |        |          |1 = Debug power-up request is ready
     * |[3]     |LPEMU     |Low Power Emulation Enable Bit
     * |        |          |0 = Low power Emulation Enabled.
     * |        |          |1 = Low power Emulation Disabled.
     * |        |          |When this bit is on, CA35 and RTP's clock and power will be maintained even the SOC in power-down mode.
     * @var SYS_T::GPAB_MFOS
     * Offset: 0x140  GPIOA and GPIOB Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPCD_MFOS
     * Offset: 0x144  GPIOC and GPIOD Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPEF_MFOS
     * Offset: 0x148  GPIOE and GPIOF Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPGH_MFOS
     * Offset: 0x14C  GPIOG and GPIOH Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPIJ_MFOS
     * Offset: 0x150  GPIOI and GPIOJ Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPKL_MFOS
     * Offset: 0x154  GPIOK and GPIOL Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::GPMN_MFOS
     * Offset: 0x158  GPIOM and GPION Multiple Function Output Mode Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GPIOxMFOS0|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[1]     |GPIOxMFOS1|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[2]     |GPIOxMFOS2|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[3]     |GPIOxMFOS3|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[4]     |GPIOxMFOS4|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[5]     |GPIOxMFOS5|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[6]     |GPIOxMFOS6|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[7]     |GPIOxMFOS7|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[8]     |GPIOxMFOS8|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[9]     |GPIOxMFOS9|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[10]    |GPIOxMFOS10|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[11]    |GPIOxMFOS11|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[12]    |GPIOxMFOS12|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[13]    |GPIOxMFOS13|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[14]    |GPIOxMFOS14|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[15]    |GPIOxMFOS15|GPIOx Pin[m] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Px.m pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: Max. m=15.
     * |        |          |Note: y= A, C, E, F, I, K, M
     * |[16]    |GPIOyMFOS16|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[17]    |GPIOyMFOS17|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[18]    |GPIOyMFOS18|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[19]    |GPIOyMFOS19|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[20]    |GPIOyMFOS20|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[21]    |GPIOyMFOS21|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[22]    |GPIOyMFOS22|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[23]    |GPIOyMFOS23|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[24]    |GPIOyMFOS24|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[25]    |GPIOyMFOS25|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[26]    |GPIOyMFOS26|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[27]    |GPIOyMFOS27|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[28]    |GPIOyMFOS28|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[29]    |GPIOyMFOS29|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[30]    |GPIOyMFOS30|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * |[31]    |GPIOyMFOS31|GPIOy Pin[n] Multiple Function Pin Output Mode Select
     * |        |          |This bit used to select multiple function pin output mode type for Py.n pin
     * |        |          |0 = Multiple function pin output mode type is Push-pull mode.
     * |        |          |1 = Multiple function pin output mode type is Open-drain mode.
     * |        |          |Note: n=0, 1..15, Max. n=15.
     * |        |          |Note: y= B, D, F, H, J, L, N
     * @var SYS_T::UID0
     * Offset: 0x180  Unique Identifier Word 0 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UID       |Unique ID
     * |        |          |Unique identify number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::UID1
     * Offset: 0x184  Unique Identifier Word 1 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UID       |Unique ID
     * |        |          |Unique identify number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::UID2
     * Offset: 0x188  Unique Identifier Word 2 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UID       |Unique ID
     * |        |          |Unique identify number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::UCID0
     * Offset: 0x190  Unique Customer Identifier Word 0 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UCID      |Unique Customer ID
     * |        |          |Unique customer identifier number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::UCID1
     * Offset: 0x194  Unique Customer Identifier Word 1 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UCID      |Unique Customer ID
     * |        |          |Unique customer identifier number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::UCID2
     * Offset: 0x198  Unique Customer Identifier Word 2 Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UCID      |Unique Customer ID
     * |        |          |Unique customer identifier number of the chip.
     * |        |          |Loaded from OTP automatically during chip power on.
     * @var SYS_T::RLKTZS
     * Offset: 0x1A0  TZS Register Lock Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REGLCTL   |Register Lock Control Code (Write Only)
     * |        |          |Some registers have write-protection function
     * |        |          |Writing these registers have to disable the protected function by writing the sequence value "59h", "16h", "88h" to this field
     * |        |          |After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
     * |        |          |REGLCTL[0]
     * |        |          |Register Lock Control Disable Index (Read Only)
     * |        |          |0 = Write-protection Enabled for writing protected registers
     * |        |          |Any write to the protected register is ignored.
     * |        |          |1 = Write-protection Disabled for writing protected registers.
     * @var SYS_T::RLKTZNS
     * Offset: 0x1A4  TZNS Register Lock Control Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REGLCTL   |Register Lock Control Code (Write Only)
     * |        |          |Some registers have write-protection function
     * |        |          |Writing these registers have to disable the protected function by writing the sequence value "59h", "16h", "88h" to this field
     * |        |          |After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
     * |        |          |REGLCTL[0]
     * |        |          |Register Lock Control Disable Index (Read Only)
     * |        |          |0 = Write-protection Enabled for writing protected registers
     * |        |          |Any write to the protected register is ignored.
     * |        |          |1 = Write-protection Disabled for writing protected registers.
     * @var SYS_T::RLKSUBM
     * Offset: 0x1A8  SUBM Register Lock Control Register (SUBM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REGLCTL   |Register Lock Control Code (Write Only)
     * |        |          |Some registers have write-protection function
     * |        |          |Writing these registers have to disable the protected function by writing the sequence value "59h", "16h", "88h" to this field
     * |        |          |After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
     * |        |          |REGLCTL[0]
     * |        |          |Register Lock Control Disable Index (Read Only)
     * |        |          |0 = Write-protection Enabled for writing protected registers
     * |        |          |Any write to the protected register is ignored.
     * |        |          |1 = Write-protection Disabled for writing protected registers.
     */
    __I  uint32_t PDID;                  /*!< [0x0000] Product and Device Identifier Register (TZNS)                    */
    __I  uint32_t PWRONOTP;              /*!< [0x0004] Power-on Setting OTP Source Register (TZNS)                      */
    __I  uint32_t PWRONPIN;              /*!< [0x0008] Power-on Setting Pin Source Register (TZNS)                      */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t RSTSTS;                /*!< [0x0010] Reset Source Active Status Register (Shared)                     */
    __IO uint32_t MISCRFCR;              /*!< [0x0014] Miscellaneous Reset Function Control Register                    */
    __IO uint32_t RSTDEBCTL;             /*!< [0x0018] Reset Pin De-bounce Control Register                             */
    __IO uint32_t LVRDCR;                /*!< [0x001c] Low Voltage Reset & Detect Control Register                      */
    __IO uint32_t IPRST0;                /*!< [0x0020] Reset Control Register 0 (Shared)                                */
    __IO uint32_t IPRST1;                /*!< [0x0024] Reset Control Register 1 (Shared)                                */
    __IO uint32_t IPRST2;                /*!< [0x0028] Reset Control Register 2 (Shared)                                */
    __IO uint32_t IPRST3;                /*!< [0x002c] Reset Control Register 3 (Shared)                                */
    __IO uint32_t PMUCR;                 /*!< [0x0030] Power Management Unit Control Register                           */
    __IO uint32_t DDRCQCSR;              /*!< [0x0034] DDR Controller Q Channel Control and Status Register             */
    __IO uint32_t PMUIEN;                /*!< [0x0038] Power Management Unit Interrupt Enable Register                  */
    __IO uint32_t PMUSTS;                /*!< [0x003c] Power Management Unit Status Register                            */
    __IO uint32_t CA35WRBADR0;           /*!< [0x0040] Cortexu00AE-A35 Core 0 Warm-boot Address Register                */
    __IO uint32_t CA35WRBPAR0;           /*!< [0x0044] Cortexu00AE-A35 Core 0 Warm-boot Parameter Register              */
    __IO uint32_t CA35WRBADR1;           /*!< [0x0048] Cortexu00AE-A35 Core 1 Warm-boot Address Register                */
    __IO uint32_t CA35WRBPAR1;           /*!< [0x004c] Cortexu00AE-A35 Core 1 Warm-boot Parameter Register              */
    __I  uint32_t RESERVE1[4];
    __IO uint32_t USBPMISCR;             /*!< [0x0060] USB PHY Miscellaneous Control Register (TZNS)                    */
    __IO uint32_t USBP0PCR;              /*!< [0x0064] USB Port 0 PHY Control Register                                  */
    __IO uint32_t USBP1PCR;              /*!< [0x0068] USB Port 1 PHY Control Register (TZNS)                           */
    __I  uint32_t RESERVE2[1];
    __IO uint32_t MISCFCR0;              /*!< [0x0070] Miscellaneous Function Control Register 0 (Shared)               */
    __IO uint32_t MISCFCR1;              /*!< [0x0074] Miscellaneous Function Control Register 1 (Shared)               */
    __IO uint32_t MISCIER;               /*!< [0x0078] Miscellaneous Interrupt Enable Register (TZNS)                   */
    __IO uint32_t MISCISR;               /*!< [0x007c] Miscellaneous Interrupt Status Register (TZNS)                   */
    __IO uint32_t GPA_MFPL;              /*!< [0x0080] GPIOA Low Byte Multiple Function Control Register                */
    __IO uint32_t GPA_MFPH;              /*!< [0x0084] GPIOA High Byte Multiple Function Control Register               */
    __IO uint32_t GPB_MFPL;              /*!< [0x0088] GPIOB Low Byte Multiple Function Control Register                */
    __IO uint32_t GPB_MFPH;              /*!< [0x008c] GPIOB High Byte Multiple Function Control Register               */
    __IO uint32_t GPC_MFPL;              /*!< [0x0090] GPIOC Low Byte Multiple Function Control Register                */
    __IO uint32_t GPC_MFPH;              /*!< [0x0094] GPIOC High Byte Multiple Function Control Register               */
    __IO uint32_t GPD_MFPL;              /*!< [0x0098] GPIOD Low Byte Multiple Function Control Register                */
    __IO uint32_t GPD_MFPH;              /*!< [0x009c] GPIOD High Byte Multiple Function Control Register               */
    __IO uint32_t GPE_MFPL;              /*!< [0x00a0] GPIOE Low Byte Multiple Function Control Register                */
    __IO uint32_t GPE_MFPH;              /*!< [0x00a4] GPIOE High Byte Multiple Function Control Register               */
    __IO uint32_t GPF_MFPL;              /*!< [0x00a8] GPIOF Low Byte Multiple Function Control Register                */
    __IO uint32_t GPF_MFPH;              /*!< [0x00ac] GPIOF High Byte Multiple Function Control Register               */
    __IO uint32_t GPG_MFPL;              /*!< [0x00b0] GPIOG Low Byte Multiple Function Control Register                */
    __IO uint32_t GPG_MFPH;              /*!< [0x00b4] GPIOG High Byte Multiple Function Control Register               */
    __IO uint32_t GPH_MFPL;              /*!< [0x00b8] GPIOH Low Byte Multiple Function Control Register                */
    __IO uint32_t GPH_MFPH;              /*!< [0x00bc] GPIOH High Byte Multiple Function Control Register               */
    __IO uint32_t GPI_MFPL;              /*!< [0x00c0] GPIOI Low Byte Multiple Function Control Register                */
    __IO uint32_t GPI_MFPH;              /*!< [0x00c4] GPIOI High Byte Multiple Function Control Register               */
    __IO uint32_t GPJ_MFPL;              /*!< [0x00c8] GPIOJ Low Byte Multiple Function Control Register                */
    __IO uint32_t GPJ_MFPH;              /*!< [0x00cc] GPIOJ High Byte Multiple Function Control Register               */
    __IO uint32_t GPK_MFPL;              /*!< [0x00d0] GPIOK Low Byte Multiple Function Control Register                */
    __IO uint32_t GPK_MFPH;              /*!< [0x00d4] GPIOK High Byte Multiple Function Control Register               */
    __IO uint32_t GPL_MFPL;              /*!< [0x00d8] GPIOL Low Byte Multiple Function Control Register                */
    __IO uint32_t GPL_MFPH;              /*!< [0x00dc] GPIOL High Byte Multiple Function Control Register               */
    __IO uint32_t GPM_MFPL;              /*!< [0x00e0] GPIOM Low Byte Multiple Function Control Register                */
    __IO uint32_t GPM_MFPH;              /*!< [0x00e4] GPIOM High Byte Multiple Function Control Register               */
    __IO uint32_t GPN_MFPL;              /*!< [0x00e8] GPION Low Byte Multiple Function Control Register                */
    __IO uint32_t GPN_MFPH;              /*!< [0x00ec] GPION High Byte Multiple Function Control Register               */
    __I  uint32_t RESERVE3[5];
    __IO uint32_t TSENSRFCR;             /*!< [0x0104] Temperature Sensor Function Control Register                     */
    __IO uint32_t GMAC0MISCR;            /*!< [0x0108] GMAC 0 Miscellaneous Control Register (TZNS)                     */
    __IO uint32_t GMAC1MISCR;            /*!< [0x010c] GMAC 1 Miscellaneous Control Register (TZNS)                     */
    __I  uint32_t MACAD0LSR;             /*!< [0x0110] MAC Address 0 Low Significant Word Register (TZNS)               */
    __I  uint32_t MACAD0HSR;             /*!< [0x0114] MAC Address 0 High Significant Word Register (TZNS)              */
    __I  uint32_t MACAD1LSR;             /*!< [0x0118] MAC Address 1 Low Significant Word Register (TZNS)               */
    __I  uint32_t MACAD1HSR;             /*!< [0x011c] MAC Address 1 High Significant Word Register (TZNS)              */
    __IO uint32_t CSDBGCTL;              /*!< [0x0120] CoreSight Debug Control Register                                 */
    __I  uint32_t RESERVE4[7];
    __IO uint32_t GPAB_MFOS;             /*!< [0x0140] GPIOA and GPIOB Multiple Function Output Mode Select Register    */
    __IO uint32_t GPCD_MFOS;             /*!< [0x0144] GPIOC and GPIOD Multiple Function Output Mode Select Register    */
    __IO uint32_t GPEF_MFOS;             /*!< [0x0148] GPIOE and GPIOF Multiple Function Output Mode Select Register    */
    __IO uint32_t GPGH_MFOS;             /*!< [0x014c] GPIOG and GPIOH Multiple Function Output Mode Select Register    */
    __IO uint32_t GPIJ_MFOS;             /*!< [0x0150] GPIOI and GPIOJ Multiple Function Output Mode Select Register    */
    __IO uint32_t GPKL_MFOS;             /*!< [0x0154] GPIOK and GPIOL Multiple Function Output Mode Select Register    */
    __IO uint32_t GPMN_MFOS;             /*!< [0x0158] GPIOM and GPION Multiple Function Output Mode Select Register    */
    __I  uint32_t RESERVE5[9];
    __I  uint32_t UID0;                  /*!< [0x0180] Unique Identifier Word 0 Register (TZNS)                         */
    __I  uint32_t UID1;                  /*!< [0x0184] Unique Identifier Word 1 Register (TZNS)                         */
    __I  uint32_t UID2;                  /*!< [0x0188] Unique Identifier Word 2 Register (TZNS)                         */
    __I  uint32_t RESERVE6[1];
    __I  uint32_t UCID0;                 /*!< [0x0190] Unique Customer Identifier Word 0 Register (TZNS)                */
    __I  uint32_t UCID1;                 /*!< [0x0194] Unique Customer Identifier Word 1 Register (TZNS)                */
    __I  uint32_t UCID2;                 /*!< [0x0198] Unique Customer Identifier Word 2 Register (TZNS)                */
    __I  uint32_t RESERVE7[1];
    __O  uint32_t RLKTZS;                /*!< [0x01a0] TZS Register Lock Control Register                               */
    __O  uint32_t RLKTZNS;               /*!< [0x01a4] TZNS Register Lock Control Register (TZNS)                       */
    __O  uint32_t RLKSUBM;               /*!< [0x01a8] SUBM Register Lock Control Register (SUBM)                       */

} SYS_T;

/**
    @addtogroup SYS_CONST SYS Bit Field Definition
    Constant Definitions for SYS Controller
@{ */

#define SYS_PDID_PID_Pos                 (0)                                               /*!< SYS_T::PDID: PID Position              */
#define SYS_PDID_PID_Msk                 (0xfffful << SYS_PDID_PID_Pos)                    /*!< SYS_T::PDID: PID Mask                  */

#define SYS_PDID_DID_Pos                 (16)                                              /*!< SYS_T::PDID: DID Position              */
#define SYS_PDID_DID_Msk                 (0xffful << SYS_PDID_DID_Pos)                     /*!< SYS_T::PDID: DID Mask                  */

#define SYS_PWRONOTP_PWRONSRC_Pos        (0)                                               /*!< SYS_T::PWRONOTP: PWRONSRC Position     */
#define SYS_PWRONOTP_PWRONSRC_Msk        (0x1ul << SYS_PWRONOTP_PWRONSRC_Pos)              /*!< SYS_T::PWRONOTP: PWRONSRC Mask         */

#define SYS_PWRONOTP_QSPI0CKSEL_Pos      (1)                                               /*!< SYS_T::PWRONOTP: QSPI0CKSEL Position   */
#define SYS_PWRONOTP_QSPI0CKSEL_Msk      (0x1ul << SYS_PWRONOTP_QSPI0CKSEL_Pos)            /*!< SYS_T::PWRONOTP: QSPI0CKSEL Mask       */

#define SYS_PWRONOTP_WDT0ON_Pos          (2)                                               /*!< SYS_T::PWRONOTP: WDT0ON Position       */
#define SYS_PWRONOTP_WDT0ON_Msk          (0x1ul << SYS_PWRONOTP_WDT0ON_Pos)                /*!< SYS_T::PWRONOTP: WDT0ON Mask           */

#define SYS_PWRONOTP_UR0DBGDIS_Pos       (4)                                               /*!< SYS_T::PWRONOTP: UR0DBGDIS Position    */
#define SYS_PWRONOTP_UR0DBGDIS_Msk       (0x1ul << SYS_PWRONOTP_UR0DBGDIS_Pos)             /*!< SYS_T::PWRONOTP: UR0DBGDIS Mask        */

#define SYS_PWRONOTP_SD0BKEN_Pos         (5)                                               /*!< SYS_T::PWRONOTP: SD0BKEN Position      */
#define SYS_PWRONOTP_SD0BKEN_Msk         (0x1ul << SYS_PWRONOTP_SD0BKEN_Pos)               /*!< SYS_T::PWRONOTP: SD0BKEN Mask          */

#define SYS_PWRONOTP_BTSRCSEL_Pos        (10)                                              /*!< SYS_T::PWRONOTP: BTSRCSEL Position     */
#define SYS_PWRONOTP_BTSRCSEL_Msk        (0x3ul << SYS_PWRONOTP_BTSRCSEL_Pos)              /*!< SYS_T::PWRONOTP: BTSRCSEL Mask         */

#define SYS_PWRONOTP_NPAGESEL_Pos        (12)                                              /*!< SYS_T::PWRONOTP: NPAGESEL Position     */
#define SYS_PWRONOTP_NPAGESEL_Msk        (0x3ul << SYS_PWRONOTP_NPAGESEL_Pos)              /*!< SYS_T::PWRONOTP: NPAGESEL Mask         */

#define SYS_PWRONOTP_MISCCFG_Pos         (14)                                              /*!< SYS_T::PWRONOTP: MISCCFG Position      */
#define SYS_PWRONOTP_MISCCFG_Msk         (0x3ul << SYS_PWRONOTP_MISCCFG_Pos)               /*!< SYS_T::PWRONOTP: MISCCFG Mask          */

#define SYS_PWRONOTP_USBP0ID_Pos         (16)                                              /*!< SYS_T::PWRONOTP: USBP0ID Position      */
#define SYS_PWRONOTP_USBP0ID_Msk         (0x1ul << SYS_PWRONOTP_USBP0ID_Pos)               /*!< SYS_T::PWRONOTP: USBP0ID Mask          */

#define SYS_PWRONOTP_SECBTPSWD_Pos       (24)                                              /*!< SYS_T::PWRONOTP: SECBTPSWD Position    */
#define SYS_PWRONOTP_SECBTPSWD_Msk       (0xfful << SYS_PWRONOTP_SECBTPSWD_Pos)            /*!< SYS_T::PWRONOTP: SECBTPSWD Mask        */

#define SYS_PWRONPIN_SECBTDIS_Pos        (0)                                               /*!< SYS_T::PWRONPIN: SECBTDIS Position     */
#define SYS_PWRONPIN_SECBTDIS_Msk        (0x1ul << SYS_PWRONPIN_SECBTDIS_Pos)              /*!< SYS_T::PWRONPIN: SECBTDIS Mask         */

#define SYS_PWRONPIN_BTSRCSEL_Pos        (2)                                               /*!< SYS_T::PWRONPIN: BTSRCSEL Position     */
#define SYS_PWRONPIN_BTSRCSEL_Msk        (0x3ul << SYS_PWRONPIN_BTSRCSEL_Pos)              /*!< SYS_T::PWRONPIN: BTSRCSEL Mask         */

#define SYS_PWRONPIN_NPAGESEL_Pos        (4)                                               /*!< SYS_T::PWRONPIN: NPAGESEL Position     */
#define SYS_PWRONPIN_NPAGESEL_Msk        (0x3ul << SYS_PWRONPIN_NPAGESEL_Pos)              /*!< SYS_T::PWRONPIN: NPAGESEL Mask         */

#define SYS_PWRONPIN_MISCCFG_Pos         (6)                                               /*!< SYS_T::PWRONPIN: MISCCFG Position      */
#define SYS_PWRONPIN_MISCCFG_Msk         (0x3ul << SYS_PWRONPIN_MISCCFG_Pos)               /*!< SYS_T::PWRONPIN: MISCCFG Mask          */

#define SYS_RSTSTS_PORF_Pos              (0)                                               /*!< SYS_T::RSTSTS: PORF Position           */
#define SYS_RSTSTS_PORF_Msk              (0x1ul << SYS_RSTSTS_PORF_Pos)                    /*!< SYS_T::RSTSTS: PORF Mask               */

#define SYS_RSTSTS_PINRF_Pos             (1)                                               /*!< SYS_T::RSTSTS: PINRF Position          */
#define SYS_RSTSTS_PINRF_Msk             (0x1ul << SYS_RSTSTS_PINRF_Pos)                   /*!< SYS_T::RSTSTS: PINRF Mask              */

#define SYS_RSTSTS_WDT0RF_Pos            (2)                                               /*!< SYS_T::RSTSTS: WDT0RF Position         */
#define SYS_RSTSTS_WDT0RF_Msk            (0x1ul << SYS_RSTSTS_WDT0RF_Pos)                  /*!< SYS_T::RSTSTS: WDT0RF Mask             */

#define SYS_RSTSTS_LVRF_Pos              (3)                                               /*!< SYS_T::RSTSTS: LVRF Position           */
#define SYS_RSTSTS_LVRF_Msk              (0x1ul << SYS_RSTSTS_LVRF_Pos)                    /*!< SYS_T::RSTSTS: LVRF Mask               */

#define SYS_RSTSTS_CPU0DBGRF_Pos         (4)                                               /*!< SYS_T::RSTSTS: CPU0DBGRF Position      */
#define SYS_RSTSTS_CPU0DBGRF_Msk         (0x1ul << SYS_RSTSTS_CPU0DBGRF_Pos)               /*!< SYS_T::RSTSTS: CPU0DBGRF Mask          */

#define SYS_RSTSTS_CPU0WARMRF_Pos        (5)                                               /*!< SYS_T::RSTSTS: CPU0WARMRF Position     */
#define SYS_RSTSTS_CPU0WARMRF_Msk        (0x1ul << SYS_RSTSTS_CPU0WARMRF_Pos)              /*!< SYS_T::RSTSTS: CPU0WARMRF Mask         */

#define SYS_RSTSTS_HRESETRF_Pos          (6)                                               /*!< SYS_T::RSTSTS: HRESETRF Position       */
#define SYS_RSTSTS_HRESETRF_Msk          (0x1ul << SYS_RSTSTS_HRESETRF_Pos)                /*!< SYS_T::RSTSTS: HRESETRF Mask           */

#define SYS_RSTSTS_CPU0RF_Pos            (7)                                               /*!< SYS_T::RSTSTS: CPU0RF Position         */
#define SYS_RSTSTS_CPU0RF_Msk            (0x1ul << SYS_RSTSTS_CPU0RF_Pos)                  /*!< SYS_T::RSTSTS: CPU0RF Mask             */

#define SYS_RSTSTS_WDT1RF_Pos            (10)                                              /*!< SYS_T::RSTSTS: WDT1RF Position         */
#define SYS_RSTSTS_WDT1RF_Msk            (0x1ul << SYS_RSTSTS_WDT1RF_Pos)                  /*!< SYS_T::RSTSTS: WDT1RF Mask             */

#define SYS_RSTSTS_WDT2RFA_Pos           (11)                                              /*!< SYS_T::RSTSTS: WDT2RFA Position        */
#define SYS_RSTSTS_WDT2RFA_Msk           (0x1ul << SYS_RSTSTS_WDT2RFA_Pos)                 /*!< SYS_T::RSTSTS: WDT2RFA Mask            */

#define SYS_RSTSTS_CPU1DBGRF_Pos         (12)                                              /*!< SYS_T::RSTSTS: CPU1DBGRF Position      */
#define SYS_RSTSTS_CPU1DBGRF_Msk         (0x1ul << SYS_RSTSTS_CPU1DBGRF_Pos)               /*!< SYS_T::RSTSTS: CPU1DBGRF Mask          */

#define SYS_RSTSTS_CPU1WARMRF_Pos        (13)                                              /*!< SYS_T::RSTSTS: CPU1WARMRF Position     */
#define SYS_RSTSTS_CPU1WARMRF_Msk        (0x1ul << SYS_RSTSTS_CPU1WARMRF_Pos)              /*!< SYS_T::RSTSTS: CPU1WARMRF Mask         */

#define SYS_RSTSTS_CPU1RF_Pos            (15)                                              /*!< SYS_T::RSTSTS: CPU1RF Position         */
#define SYS_RSTSTS_CPU1RF_Msk            (0x1ul << SYS_RSTSTS_CPU1RF_Pos)                  /*!< SYS_T::RSTSTS: CPU1RF Mask             */

#define SYS_RSTSTS_WDT1RFM_Pos           (18)                                              /*!< SYS_T::RSTSTS: WDT1RFM Position        */
#define SYS_RSTSTS_WDT1RFM_Msk           (0x1ul << SYS_RSTSTS_WDT1RFM_Pos)                 /*!< SYS_T::RSTSTS: WDT1RFM Mask            */

#define SYS_RSTSTS_WDT2RF_Pos            (19)                                              /*!< SYS_T::RSTSTS: WDT2RF Position         */
#define SYS_RSTSTS_WDT2RF_Msk            (0x1ul << SYS_RSTSTS_WDT2RF_Pos)                  /*!< SYS_T::RSTSTS: WDT2RF Mask             */

#define SYS_RSTSTS_RTPM4LKRF_Pos         (20)                                              /*!< SYS_T::RSTSTS: RTPM4LKRF Position      */
#define SYS_RSTSTS_RTPM4LKRF_Msk         (0x1ul << SYS_RSTSTS_RTPM4LKRF_Pos)               /*!< SYS_T::RSTSTS: RTPM4LKRF Mask          */

#define SYS_RSTSTS_RTPM4SYSRF_Pos        (21)                                              /*!< SYS_T::RSTSTS: RTPM4SYSRF Position     */
#define SYS_RSTSTS_RTPM4SYSRF_Msk        (0x1ul << SYS_RSTSTS_RTPM4SYSRF_Pos)              /*!< SYS_T::RSTSTS: RTPM4SYSRF Mask         */

#define SYS_RSTSTS_RTPPMUSYSRF_Pos       (22)                                              /*!< SYS_T::RSTSTS: RTPPMUSYSRF Position    */
#define SYS_RSTSTS_RTPPMUSYSRF_Msk       (0x1ul << SYS_RSTSTS_RTPPMUSYSRF_Pos)             /*!< SYS_T::RSTSTS: RTPPMUSYSRF Mask        */

#define SYS_RSTSTS_RTPM4CPURF_Pos        (23)                                              /*!< SYS_T::RSTSTS: RTPM4CPURF Position     */
#define SYS_RSTSTS_RTPM4CPURF_Msk        (0x1ul << SYS_RSTSTS_RTPM4CPURF_Pos)              /*!< SYS_T::RSTSTS: RTPM4CPURF Mask         */

#define SYS_MISCRFCR_PORDISCODE_Pos      (0)                                               /*!< SYS_T::MISCRFCR: PORDISCODE Position   */
#define SYS_MISCRFCR_PORDISCODE_Msk      (0xfffful << SYS_MISCRFCR_PORDISCODE_Pos)         /*!< SYS_T::MISCRFCR: PORDISCODE Mask       */

#define SYS_MISCRFCR_WDT1RSTAEN_Pos      (16)                                              /*!< SYS_T::MISCRFCR: WDT1RSTAEN Position   */
#define SYS_MISCRFCR_WDT1RSTAEN_Msk      (0x1ul << SYS_MISCRFCR_WDT1RSTAEN_Pos)            /*!< SYS_T::MISCRFCR: WDT1RSTAEN Mask       */

#define SYS_MISCRFCR_WDT2RSTAEN_Pos      (17)                                              /*!< SYS_T::MISCRFCR: WDT2RSTAEN Position   */
#define SYS_MISCRFCR_WDT2RSTAEN_Msk      (0x1ul << SYS_MISCRFCR_WDT2RSTAEN_Pos)            /*!< SYS_T::MISCRFCR: WDT2RSTAEN Mask       */

#define SYS_MISCRFCR_WDT1RSTMEN_Pos      (18)                                              /*!< SYS_T::MISCRFCR: WDT1RSTMEN Position   */
#define SYS_MISCRFCR_WDT1RSTMEN_Msk      (0x1ul << SYS_MISCRFCR_WDT1RSTMEN_Pos)            /*!< SYS_T::MISCRFCR: WDT1RSTMEN Mask       */

#define SYS_RSTDEBCTL_DEBCNT_Pos         (0)                                               /*!< SYS_T::RSTDEBCTL: DEBCNT Position      */
#define SYS_RSTDEBCTL_DEBCNT_Msk         (0xfffful << SYS_RSTDEBCTL_DEBCNT_Pos)            /*!< SYS_T::RSTDEBCTL: DEBCNT Mask          */

#define SYS_RSTDEBCTL_RSTDEBEN_Pos       (31)                                              /*!< SYS_T::RSTDEBCTL: RSTDEBEN Position    */
#define SYS_RSTDEBCTL_RSTDEBEN_Msk       (0x1ul << SYS_RSTDEBCTL_RSTDEBEN_Pos)             /*!< SYS_T::RSTDEBCTL: RSTDEBEN Mask        */

#define SYS_LVRDCR_LVREN_Pos             (0)                                               /*!< SYS_T::LVRDCR: LVREN Position          */
#define SYS_LVRDCR_LVREN_Msk             (0x1ul << SYS_LVRDCR_LVREN_Pos)                   /*!< SYS_T::LVRDCR: LVREN Mask              */

#define SYS_LVRDCR_LVRDGSEL_Pos          (1)                                               /*!< SYS_T::LVRDCR: LVRDGSEL Position       */
#define SYS_LVRDCR_LVRDGSEL_Msk          (0x7ul << SYS_LVRDCR_LVRDGSEL_Pos)                /*!< SYS_T::LVRDCR: LVRDGSEL Mask           */

#define SYS_LVRDCR_LVDEN_Pos             (8)                                               /*!< SYS_T::LVRDCR: LVDEN Position          */
#define SYS_LVRDCR_LVDEN_Msk             (0x1ul << SYS_LVRDCR_LVDEN_Pos)                   /*!< SYS_T::LVRDCR: LVDEN Mask              */

#define SYS_LVRDCR_LVDSEL_Pos            (9)                                               /*!< SYS_T::LVRDCR: LVDSEL Position         */
#define SYS_LVRDCR_LVDSEL_Msk            (0x1ul << SYS_LVRDCR_LVDSEL_Pos)                  /*!< SYS_T::LVRDCR: LVDSEL Mask             */

#define SYS_LVRDCR_LVDWKA35EN_Pos        (10)                                              /*!< SYS_T::LVRDCR: LVDWKA35EN Position     */
#define SYS_LVRDCR_LVDWKA35EN_Msk        (0x1ul << SYS_LVRDCR_LVDWKA35EN_Pos)              /*!< SYS_T::LVRDCR: LVDWKA35EN Mask         */

#define SYS_LVRDCR_LVDWKRTPEN_Pos        (11)                                              /*!< SYS_T::LVRDCR: LVDWKRTPEN Position     */
#define SYS_LVRDCR_LVDWKRTPEN_Msk        (0x1ul << SYS_LVRDCR_LVDWKRTPEN_Pos)              /*!< SYS_T::LVRDCR: LVDWKRTPEN Mask         */

#define SYS_LVRDCR_LVDODGSEL_Pos         (12)                                              /*!< SYS_T::LVRDCR: LVDODGSEL Position      */
#define SYS_LVRDCR_LVDODGSEL_Msk         (0x7ul << SYS_LVRDCR_LVDODGSEL_Pos)               /*!< SYS_T::LVRDCR: LVDODGSEL Mask          */

#define SYS_IPRST0_CHIPRST_Pos           (0)                                               /*!< SYS_T::IPRST0: CHIPRST Position        */
#define SYS_IPRST0_CHIPRST_Msk           (0x1ul << SYS_IPRST0_CHIPRST_Pos)                 /*!< SYS_T::IPRST0: CHIPRST Mask            */

#define SYS_IPRST0_CA35CR0RST_Pos        (1)                                               /*!< SYS_T::IPRST0: CA35CR0RST Position     */
#define SYS_IPRST0_CA35CR0RST_Msk        (0x1ul << SYS_IPRST0_CA35CR0RST_Pos)              /*!< SYS_T::IPRST0: CA35CR0RST Mask         */

#define SYS_IPRST0_CA35CR1RST_Pos        (2)                                               /*!< SYS_T::IPRST0: CA35CR1RST Position     */
#define SYS_IPRST0_CA35CR1RST_Msk        (0x1ul << SYS_IPRST0_CA35CR1RST_Pos)              /*!< SYS_T::IPRST0: CA35CR1RST Mask         */

#define SYS_IPRST0_CM4RST_Pos            (3)                                               /*!< SYS_T::IPRST0: CM4RST Position         */
#define SYS_IPRST0_CM4RST_Msk            (0x1ul << SYS_IPRST0_CM4RST_Pos)                  /*!< SYS_T::IPRST0: CM4RST Mask             */

#define SYS_IPRST0_PDMA0RST_Pos          (4)                                               /*!< SYS_T::IPRST0: PDMA0RST Position       */
#define SYS_IPRST0_PDMA0RST_Msk          (0x1ul << SYS_IPRST0_PDMA0RST_Pos)                /*!< SYS_T::IPRST0: PDMA0RST Mask           */

#define SYS_IPRST0_PDMA1RST_Pos          (5)                                               /*!< SYS_T::IPRST0: PDMA1RST Position       */
#define SYS_IPRST0_PDMA1RST_Msk          (0x1ul << SYS_IPRST0_PDMA1RST_Pos)                /*!< SYS_T::IPRST0: PDMA1RST Mask           */

#define SYS_IPRST0_PDMA2RST_Pos          (6)                                               /*!< SYS_T::IPRST0: PDMA2RST Position       */
#define SYS_IPRST0_PDMA2RST_Msk          (0x1ul << SYS_IPRST0_PDMA2RST_Pos)                /*!< SYS_T::IPRST0: PDMA2RST Mask           */

#define SYS_IPRST0_PDMA3RST_Pos          (7)                                               /*!< SYS_T::IPRST0: PDMA3RST Position       */
#define SYS_IPRST0_PDMA3RST_Msk          (0x1ul << SYS_IPRST0_PDMA3RST_Pos)                /*!< SYS_T::IPRST0: PDMA3RST Mask           */

#define SYS_IPRST0_DISPCRST_Pos          (9)                                               /*!< SYS_T::IPRST0: DISPCRST Position       */
#define SYS_IPRST0_DISPCRST_Msk          (0x1ul << SYS_IPRST0_DISPCRST_Pos)                /*!< SYS_T::IPRST0: DISPCRST Mask           */

#define SYS_IPRST0_CCAP0RST_Pos          (10)                                              /*!< SYS_T::IPRST0: CCAP0RST Position       */
#define SYS_IPRST0_CCAP0RST_Msk          (0x1ul << SYS_IPRST0_CCAP0RST_Pos)                /*!< SYS_T::IPRST0: CCAP0RST Mask           */

#define SYS_IPRST0_CCAP1RST_Pos          (11)                                              /*!< SYS_T::IPRST0: CCAP1RST Position       */
#define SYS_IPRST0_CCAP1RST_Msk          (0x1ul << SYS_IPRST0_CCAP1RST_Pos)                /*!< SYS_T::IPRST0: CCAP1RST Mask           */

#define SYS_IPRST0_GFXRST_Pos            (12)                                              /*!< SYS_T::IPRST0: GFXRST Position         */
#define SYS_IPRST0_GFXRST_Msk            (0x1ul << SYS_IPRST0_GFXRST_Pos)                  /*!< SYS_T::IPRST0: GFXRST Mask             */

#define SYS_IPRST0_VDECRST_Pos           (13)                                              /*!< SYS_T::IPRST0: VDECRST Position        */
#define SYS_IPRST0_VDECRST_Msk           (0x1ul << SYS_IPRST0_VDECRST_Pos)                 /*!< SYS_T::IPRST0: VDECRST Mask            */

#define SYS_IPRST0_WRHO0RST_Pos          (14)                                              /*!< SYS_T::IPRST0: WRHO0RST Position       */
#define SYS_IPRST0_WRHO0RST_Msk          (0x1ul << SYS_IPRST0_WRHO0RST_Pos)                /*!< SYS_T::IPRST0: WRHO0RST Mask           */

#define SYS_IPRST0_WRHO1RST_Pos          (15)                                              /*!< SYS_T::IPRST0: WRHO1RST Position       */
#define SYS_IPRST0_WRHO1RST_Msk          (0x1ul << SYS_IPRST0_WRHO1RST_Pos)                /*!< SYS_T::IPRST0: WRHO1RST Mask           */

#define SYS_IPRST0_GMAC0RST_Pos          (16)                                              /*!< SYS_T::IPRST0: GMAC0RST Position       */
#define SYS_IPRST0_GMAC0RST_Msk          (0x1ul << SYS_IPRST0_GMAC0RST_Pos)                /*!< SYS_T::IPRST0: GMAC0RST Mask           */

#define SYS_IPRST0_GMAC1RST_Pos          (17)                                              /*!< SYS_T::IPRST0: GMAC1RST Position       */
#define SYS_IPRST0_GMAC1RST_Msk          (0x1ul << SYS_IPRST0_GMAC1RST_Pos)                /*!< SYS_T::IPRST0: GMAC1RST Mask           */

#define SYS_IPRST0_HWSEMRST_Pos          (18)                                              /*!< SYS_T::IPRST0: HWSEMRST Position       */
#define SYS_IPRST0_HWSEMRST_Msk          (0x1ul << SYS_IPRST0_HWSEMRST_Pos)                /*!< SYS_T::IPRST0: HWSEMRST Mask           */

#define SYS_IPRST0_EBIRST_Pos            (19)                                              /*!< SYS_T::IPRST0: EBIRST Position         */
#define SYS_IPRST0_EBIRST_Msk            (0x1ul << SYS_IPRST0_EBIRST_Pos)                  /*!< SYS_T::IPRST0: EBIRST Mask             */

#define SYS_IPRST0_HSUSBH0RST_Pos        (20)                                              /*!< SYS_T::IPRST0: HSUSBH0RST Position     */
#define SYS_IPRST0_HSUSBH0RST_Msk        (0x1ul << SYS_IPRST0_HSUSBH0RST_Pos)              /*!< SYS_T::IPRST0: HSUSBH0RST Mask         */

#define SYS_IPRST0_HSUSBH1RST_Pos        (21)                                              /*!< SYS_T::IPRST0: HSUSBH1RST Position     */
#define SYS_IPRST0_HSUSBH1RST_Msk        (0x1ul << SYS_IPRST0_HSUSBH1RST_Pos)              /*!< SYS_T::IPRST0: HSUSBH1RST Mask         */

#define SYS_IPRST0_HSUSBDRST_Pos         (22)                                              /*!< SYS_T::IPRST0: HSUSBDRST Position      */
#define SYS_IPRST0_HSUSBDRST_Msk         (0x1ul << SYS_IPRST0_HSUSBDRST_Pos)               /*!< SYS_T::IPRST0: HSUSBDRST Mask          */

#define SYS_IPRST0_SDH0RST_Pos           (24)                                              /*!< SYS_T::IPRST0: SDH0RST Position        */
#define SYS_IPRST0_SDH0RST_Msk           (0x1ul << SYS_IPRST0_SDH0RST_Pos)                 /*!< SYS_T::IPRST0: SDH0RST Mask            */

#define SYS_IPRST0_SDH1RST_Pos           (25)                                              /*!< SYS_T::IPRST0: SDH1RST Position        */
#define SYS_IPRST0_SDH1RST_Msk           (0x1ul << SYS_IPRST0_SDH1RST_Pos)                 /*!< SYS_T::IPRST0: SDH1RST Mask            */

#define SYS_IPRST0_NANDRST_Pos           (26)                                              /*!< SYS_T::IPRST0: NANDRST Position        */
#define SYS_IPRST0_NANDRST_Msk           (0x1ul << SYS_IPRST0_NANDRST_Pos)                 /*!< SYS_T::IPRST0: NANDRST Mask            */

#define SYS_IPRST0_GPIORST_Pos           (27)                                              /*!< SYS_T::IPRST0: GPIORST Position        */
#define SYS_IPRST0_GPIORST_Msk           (0x1ul << SYS_IPRST0_GPIORST_Pos)                 /*!< SYS_T::IPRST0: GPIORST Mask            */

#define SYS_IPRST0_MCTLPRST_Pos          (28)                                              /*!< SYS_T::IPRST0: MCTLPRST Position       */
#define SYS_IPRST0_MCTLPRST_Msk          (0x1ul << SYS_IPRST0_MCTLPRST_Pos)                /*!< SYS_T::IPRST0: MCTLPRST Mask           */

#define SYS_IPRST0_MCTLCRST_Pos          (29)                                              /*!< SYS_T::IPRST0: MCTLCRST Position       */
#define SYS_IPRST0_MCTLCRST_Msk          (0x1ul << SYS_IPRST0_MCTLCRST_Pos)                /*!< SYS_T::IPRST0: MCTLCRST Mask           */

#define SYS_IPRST0_DDRPUBRST_Pos         (30)                                              /*!< SYS_T::IPRST0: DDRPUBRST Position      */
#define SYS_IPRST0_DDRPUBRST_Msk         (0x1ul << SYS_IPRST0_DDRPUBRST_Pos)               /*!< SYS_T::IPRST0: DDRPUBRST Mask          */

#define SYS_IPRST1_TMR0RST_Pos           (2)                                               /*!< SYS_T::IPRST1: TMR0RST Position        */
#define SYS_IPRST1_TMR0RST_Msk           (0x1ul << SYS_IPRST1_TMR0RST_Pos)                 /*!< SYS_T::IPRST1: TMR0RST Mask            */

#define SYS_IPRST1_TMR1RST_Pos           (3)                                               /*!< SYS_T::IPRST1: TMR1RST Position        */
#define SYS_IPRST1_TMR1RST_Msk           (0x1ul << SYS_IPRST1_TMR1RST_Pos)                 /*!< SYS_T::IPRST1: TMR1RST Mask            */

#define SYS_IPRST1_TMR2RST_Pos           (4)                                               /*!< SYS_T::IPRST1: TMR2RST Position        */
#define SYS_IPRST1_TMR2RST_Msk           (0x1ul << SYS_IPRST1_TMR2RST_Pos)                 /*!< SYS_T::IPRST1: TMR2RST Mask            */

#define SYS_IPRST1_TMR3RST_Pos           (5)                                               /*!< SYS_T::IPRST1: TMR3RST Position        */
#define SYS_IPRST1_TMR3RST_Msk           (0x1ul << SYS_IPRST1_TMR3RST_Pos)                 /*!< SYS_T::IPRST1: TMR3RST Mask            */

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

#define SYS_IPRST1_CANFD0RST_Pos         (24)                                              /*!< SYS_T::IPRST1: CANFD0RST Position      */
#define SYS_IPRST1_CANFD0RST_Msk         (0x1ul << SYS_IPRST1_CANFD0RST_Pos)               /*!< SYS_T::IPRST1: CANFD0RST Mask          */

#define SYS_IPRST1_CANFD1RST_Pos         (25)                                              /*!< SYS_T::IPRST1: CANFD1RST Position      */
#define SYS_IPRST1_CANFD1RST_Msk         (0x1ul << SYS_IPRST1_CANFD1RST_Pos)               /*!< SYS_T::IPRST1: CANFD1RST Mask          */

#define SYS_IPRST1_EADC0RST_Pos          (28)                                              /*!< SYS_T::IPRST1: EADC0RST Position       */
#define SYS_IPRST1_EADC0RST_Msk          (0x1ul << SYS_IPRST1_EADC0RST_Pos)                /*!< SYS_T::IPRST1: EADC0RST Mask           */

#define SYS_IPRST1_I2S0RST_Pos           (29)                                              /*!< SYS_T::IPRST1: I2S0RST Position        */
#define SYS_IPRST1_I2S0RST_Msk           (0x1ul << SYS_IPRST1_I2S0RST_Pos)                 /*!< SYS_T::IPRST1: I2S0RST Mask            */

#define SYS_IPRST2_SC0RST_Pos            (0)                                               /*!< SYS_T::IPRST2: SC0RST Position         */
#define SYS_IPRST2_SC0RST_Msk            (0x1ul << SYS_IPRST2_SC0RST_Pos)                  /*!< SYS_T::IPRST2: SC0RST Mask             */

#define SYS_IPRST2_SC1RST_Pos            (1)                                               /*!< SYS_T::IPRST2: SC1RST Position         */
#define SYS_IPRST2_SC1RST_Msk            (0x1ul << SYS_IPRST2_SC1RST_Pos)                  /*!< SYS_T::IPRST2: SC1RST Mask             */

#define SYS_IPRST2_QSPI1RST_Pos          (4)                                               /*!< SYS_T::IPRST2: QSPI1RST Position       */
#define SYS_IPRST2_QSPI1RST_Msk          (0x1ul << SYS_IPRST2_QSPI1RST_Pos)                /*!< SYS_T::IPRST2: QSPI1RST Mask           */

#define SYS_IPRST2_SPI3RST_Pos           (6)                                               /*!< SYS_T::IPRST2: SPI3RST Position        */
#define SYS_IPRST2_SPI3RST_Msk           (0x1ul << SYS_IPRST2_SPI3RST_Pos)                 /*!< SYS_T::IPRST2: SPI3RST Mask            */

#define SYS_IPRST2_EPWM0RST_Pos          (16)                                              /*!< SYS_T::IPRST2: EPWM0RST Position       */
#define SYS_IPRST2_EPWM0RST_Msk          (0x1ul << SYS_IPRST2_EPWM0RST_Pos)                /*!< SYS_T::IPRST2: EPWM0RST Mask           */

#define SYS_IPRST2_EPWM1RST_Pos          (17)                                              /*!< SYS_T::IPRST2: EPWM1RST Position       */
#define SYS_IPRST2_EPWM1RST_Msk          (0x1ul << SYS_IPRST2_EPWM1RST_Pos)                /*!< SYS_T::IPRST2: EPWM1RST Mask           */

#define SYS_IPRST2_QEI0RST_Pos           (22)                                              /*!< SYS_T::IPRST2: QEI0RST Position        */
#define SYS_IPRST2_QEI0RST_Msk           (0x1ul << SYS_IPRST2_QEI0RST_Pos)                 /*!< SYS_T::IPRST2: QEI0RST Mask            */

#define SYS_IPRST2_QEI1RST_Pos           (23)                                              /*!< SYS_T::IPRST2: QEI1RST Position        */
#define SYS_IPRST2_QEI1RST_Msk           (0x1ul << SYS_IPRST2_QEI1RST_Pos)                 /*!< SYS_T::IPRST2: QEI1RST Mask            */

#define SYS_IPRST2_ECAP0RST_Pos          (26)                                              /*!< SYS_T::IPRST2: ECAP0RST Position       */
#define SYS_IPRST2_ECAP0RST_Msk          (0x1ul << SYS_IPRST2_ECAP0RST_Pos)                /*!< SYS_T::IPRST2: ECAP0RST Mask           */

#define SYS_IPRST2_ECAP1RST_Pos          (27)                                              /*!< SYS_T::IPRST2: ECAP1RST Position       */
#define SYS_IPRST2_ECAP1RST_Msk          (0x1ul << SYS_IPRST2_ECAP1RST_Pos)                /*!< SYS_T::IPRST2: ECAP1RST Mask           */

#define SYS_IPRST2_CANFD2RST_Pos         (28)                                              /*!< SYS_T::IPRST2: CANFD2RST Position      */
#define SYS_IPRST2_CANFD2RST_Msk         (0x1ul << SYS_IPRST2_CANFD2RST_Pos)               /*!< SYS_T::IPRST2: CANFD2RST Mask          */

#define SYS_IPRST2_ADC0RST_Pos           (31)                                              /*!< SYS_T::IPRST2: ADC0RST Position        */
#define SYS_IPRST2_ADC0RST_Msk           (0x1ul << SYS_IPRST2_ADC0RST_Pos)                 /*!< SYS_T::IPRST2: ADC0RST Mask            */

#define SYS_IPRST3_TMR4RST_Pos           (0)                                               /*!< SYS_T::IPRST3: TMR4RST Position        */
#define SYS_IPRST3_TMR4RST_Msk           (0x1ul << SYS_IPRST3_TMR4RST_Pos)                 /*!< SYS_T::IPRST3: TMR4RST Mask            */

#define SYS_IPRST3_TMR5RST_Pos           (1)                                               /*!< SYS_T::IPRST3: TMR5RST Position        */
#define SYS_IPRST3_TMR5RST_Msk           (0x1ul << SYS_IPRST3_TMR5RST_Pos)                 /*!< SYS_T::IPRST3: TMR5RST Mask            */

#define SYS_IPRST3_TMR6RST_Pos           (2)                                               /*!< SYS_T::IPRST3: TMR6RST Position        */
#define SYS_IPRST3_TMR6RST_Msk           (0x1ul << SYS_IPRST3_TMR6RST_Pos)                 /*!< SYS_T::IPRST3: TMR6RST Mask            */

#define SYS_IPRST3_TMR7RST_Pos           (3)                                               /*!< SYS_T::IPRST3: TMR7RST Position        */
#define SYS_IPRST3_TMR7RST_Msk           (0x1ul << SYS_IPRST3_TMR7RST_Pos)                 /*!< SYS_T::IPRST3: TMR7RST Mask            */

#define SYS_IPRST3_TMR8RST_Pos           (4)                                               /*!< SYS_T::IPRST3: TMR8RST Position        */
#define SYS_IPRST3_TMR8RST_Msk           (0x1ul << SYS_IPRST3_TMR8RST_Pos)                 /*!< SYS_T::IPRST3: TMR8RST Mask            */

#define SYS_IPRST3_TMR9RST_Pos           (5)                                               /*!< SYS_T::IPRST3: TMR9RST Position        */
#define SYS_IPRST3_TMR9RST_Msk           (0x1ul << SYS_IPRST3_TMR9RST_Pos)                 /*!< SYS_T::IPRST3: TMR9RST Mask            */

#define SYS_IPRST3_TMR10RST_Pos          (6)                                               /*!< SYS_T::IPRST3: TMR10RST Position       */
#define SYS_IPRST3_TMR10RST_Msk          (0x1ul << SYS_IPRST3_TMR10RST_Pos)                /*!< SYS_T::IPRST3: TMR10RST Mask           */

#define SYS_IPRST3_TMR11RST_Pos          (7)                                               /*!< SYS_T::IPRST3: TMR11RST Position       */
#define SYS_IPRST3_TMR11RST_Msk          (0x1ul << SYS_IPRST3_TMR11RST_Pos)                /*!< SYS_T::IPRST3: TMR11RST Mask           */

#define SYS_IPRST3_UART8RST_Pos          (8)                                               /*!< SYS_T::IPRST3: UART8RST Position       */
#define SYS_IPRST3_UART8RST_Msk          (0x1ul << SYS_IPRST3_UART8RST_Pos)                /*!< SYS_T::IPRST3: UART8RST Mask           */

#define SYS_IPRST3_UART9RST_Pos          (9)                                               /*!< SYS_T::IPRST3: UART9RST Position       */
#define SYS_IPRST3_UART9RST_Msk          (0x1ul << SYS_IPRST3_UART9RST_Pos)                /*!< SYS_T::IPRST3: UART9RST Mask           */

#define SYS_IPRST3_UART10RST_Pos         (10)                                              /*!< SYS_T::IPRST3: UART10RST Position      */
#define SYS_IPRST3_UART10RST_Msk         (0x1ul << SYS_IPRST3_UART10RST_Pos)               /*!< SYS_T::IPRST3: UART10RST Mask          */

#define SYS_IPRST3_UART11RST_Pos         (11)                                              /*!< SYS_T::IPRST3: UART11RST Position      */
#define SYS_IPRST3_UART11RST_Msk         (0x1ul << SYS_IPRST3_UART11RST_Pos)               /*!< SYS_T::IPRST3: UART11RST Mask          */

#define SYS_IPRST3_UART12RST_Pos         (12)                                              /*!< SYS_T::IPRST3: UART12RST Position      */
#define SYS_IPRST3_UART12RST_Msk         (0x1ul << SYS_IPRST3_UART12RST_Pos)               /*!< SYS_T::IPRST3: UART12RST Mask          */

#define SYS_IPRST3_UART13RST_Pos         (13)                                              /*!< SYS_T::IPRST3: UART13RST Position      */
#define SYS_IPRST3_UART13RST_Msk         (0x1ul << SYS_IPRST3_UART13RST_Pos)               /*!< SYS_T::IPRST3: UART13RST Mask          */

#define SYS_IPRST3_UART14RST_Pos         (14)                                              /*!< SYS_T::IPRST3: UART14RST Position      */
#define SYS_IPRST3_UART14RST_Msk         (0x1ul << SYS_IPRST3_UART14RST_Pos)               /*!< SYS_T::IPRST3: UART14RST Mask          */

#define SYS_IPRST3_UART15RST_Pos         (15)                                              /*!< SYS_T::IPRST3: UART15RST Position      */
#define SYS_IPRST3_UART15RST_Msk         (0x1ul << SYS_IPRST3_UART15RST_Pos)               /*!< SYS_T::IPRST3: UART15RST Mask          */

#define SYS_IPRST3_UART16RST_Pos         (16)                                              /*!< SYS_T::IPRST3: UART16RST Position      */
#define SYS_IPRST3_UART16RST_Msk         (0x1ul << SYS_IPRST3_UART16RST_Pos)               /*!< SYS_T::IPRST3: UART16RST Mask          */

#define SYS_IPRST3_I2S1RST_Pos           (17)                                              /*!< SYS_T::IPRST3: I2S1RST Position        */
#define SYS_IPRST3_I2S1RST_Msk           (0x1ul << SYS_IPRST3_I2S1RST_Pos)                 /*!< SYS_T::IPRST3: I2S1RST Mask            */

#define SYS_IPRST3_I2C4RST_Pos           (18)                                              /*!< SYS_T::IPRST3: I2C4RST Position        */
#define SYS_IPRST3_I2C4RST_Msk           (0x1ul << SYS_IPRST3_I2C4RST_Pos)                 /*!< SYS_T::IPRST3: I2C4RST Mask            */

#define SYS_IPRST3_I2C5RST_Pos           (19)                                              /*!< SYS_T::IPRST3: I2C5RST Position        */
#define SYS_IPRST3_I2C5RST_Msk           (0x1ul << SYS_IPRST3_I2C5RST_Pos)                 /*!< SYS_T::IPRST3: I2C5RST Mask            */

#define SYS_IPRST3_EPWM2RST_Pos          (20)                                              /*!< SYS_T::IPRST3: EPWM2RST Position       */
#define SYS_IPRST3_EPWM2RST_Msk          (0x1ul << SYS_IPRST3_EPWM2RST_Pos)                /*!< SYS_T::IPRST3: EPWM2RST Mask           */

#define SYS_IPRST3_ECAP2RST_Pos          (21)                                              /*!< SYS_T::IPRST3: ECAP2RST Position       */
#define SYS_IPRST3_ECAP2RST_Msk          (0x1ul << SYS_IPRST3_ECAP2RST_Pos)                /*!< SYS_T::IPRST3: ECAP2RST Mask           */

#define SYS_IPRST3_QEI2RST_Pos           (22)                                              /*!< SYS_T::IPRST3: QEI2RST Position        */
#define SYS_IPRST3_QEI2RST_Msk           (0x1ul << SYS_IPRST3_QEI2RST_Pos)                 /*!< SYS_T::IPRST3: QEI2RST Mask            */

#define SYS_IPRST3_CANFD3RST_Pos         (23)                                              /*!< SYS_T::IPRST3: CANFD3RST Position      */
#define SYS_IPRST3_CANFD3RST_Msk         (0x1ul << SYS_IPRST3_CANFD3RST_Pos)               /*!< SYS_T::IPRST3: CANFD3RST Mask          */

#define SYS_IPRST3_KPIRST_Pos            (24)                                              /*!< SYS_T::IPRST3: KPIRST Position         */
#define SYS_IPRST3_KPIRST_Msk            (0x1ul << SYS_IPRST3_KPIRST_Pos)                  /*!< SYS_T::IPRST3: KPIRST Mask             */

#define SYS_IPRST3_GICRST_Pos            (28)                                              /*!< SYS_T::IPRST3: GICRST Position         */
#define SYS_IPRST3_GICRST_Msk            (0x1ul << SYS_IPRST3_GICRST_Pos)                  /*!< SYS_T::IPRST3: GICRST Mask             */

#define SYS_IPRST3_SSMCCRST_Pos          (30)                                              /*!< SYS_T::IPRST3: SSMCCRST Position       */
#define SYS_IPRST3_SSMCCRST_Msk          (0x1ul << SYS_IPRST3_SSMCCRST_Pos)                /*!< SYS_T::IPRST3: SSMCCRST Mask           */

#define SYS_IPRST3_SSPCCRST_Pos          (31)                                              /*!< SYS_T::IPRST3: SSPCCRST Position       */
#define SYS_IPRST3_SSPCCRST_Msk          (0x1ul << SYS_IPRST3_SSPCCRST_Pos)                /*!< SYS_T::IPRST3: SSPCCRST Mask           */

#define SYS_PMUCR_A35PGEN_Pos            (0)                                               /*!< SYS_T::PMUCR: A35PGEN Position         */
#define SYS_PMUCR_A35PGEN_Msk            (0x1ul << SYS_PMUCR_A35PGEN_Pos)                  /*!< SYS_T::PMUCR: A35PGEN Mask             */

#define SYS_PMUCR_AUTOL2FDIS_Pos         (4)                                               /*!< SYS_T::PMUCR: AUTOL2FDIS Position      */
#define SYS_PMUCR_AUTOL2FDIS_Msk         (0x1ul << SYS_PMUCR_AUTOL2FDIS_Pos)               /*!< SYS_T::PMUCR: AUTOL2FDIS Mask          */

#define SYS_PMUCR_PDWKDLY_Pos            (6)                                               /*!< SYS_T::PMUCR: PDWKDLY Position         */
#define SYS_PMUCR_PDWKDLY_Msk            (0x1ul << SYS_PMUCR_PDWKDLY_Pos)                  /*!< SYS_T::PMUCR: PDWKDLY Mask             */

#define SYS_PMUCR_PWRSTBTM_Pos           (8)                                               /*!< SYS_T::PMUCR: PWRSTBTM Position        */
#define SYS_PMUCR_PWRSTBTM_Msk           (0xful << SYS_PMUCR_PWRSTBTM_Pos)                 /*!< SYS_T::PMUCR: PWRSTBTM Mask            */

#define SYS_PMUCR_PWRACKTO_Pos           (12)                                              /*!< SYS_T::PMUCR: PWRACKTO Position        */
#define SYS_PMUCR_PWRACKTO_Msk           (0xful << SYS_PMUCR_PWRACKTO_Pos)                 /*!< SYS_T::PMUCR: PWRACKTO Mask            */

#define SYS_PMUCR_A35PDEN_Pos            (16)                                              /*!< SYS_T::PMUCR: A35PDEN Position         */
#define SYS_PMUCR_A35PDEN_Msk            (0x1ul << SYS_PMUCR_A35PDEN_Pos)                  /*!< SYS_T::PMUCR: A35PDEN Mask             */

#define SYS_PMUCR_A35DBPDEN_Pos          (18)                                              /*!< SYS_T::PMUCR: A35DBPDEN Position       */
#define SYS_PMUCR_A35DBPDEN_Msk          (0x1ul << SYS_PMUCR_A35DBPDEN_Pos)                /*!< SYS_T::PMUCR: A35DBPDEN Mask           */

#define SYS_PMUCR_RTPPDEN_Pos            (24)                                              /*!< SYS_T::PMUCR: RTPPDEN Position         */
#define SYS_PMUCR_RTPPDEN_Msk            (0x1ul << SYS_PMUCR_RTPPDEN_Pos)                  /*!< SYS_T::PMUCR: RTPPDEN Mask             */

#define SYS_PMUCR_RTPDBPDEN_Pos          (26)                                              /*!< SYS_T::PMUCR: RTPDBPDEN Position       */
#define SYS_PMUCR_RTPDBPDEN_Msk          (0x1ul << SYS_PMUCR_RTPDBPDEN_Pos)                /*!< SYS_T::PMUCR: RTPDBPDEN Mask           */

#define SYS_DDRCQCSR_AXIQBYPAS_Pos       (0)                                               /*!< SYS_T::DDRCQCSR: AXIQBYPAS Position    */
#define SYS_DDRCQCSR_AXIQBYPAS_Msk       (0xfful << SYS_DDRCQCSR_AXIQBYPAS_Pos)            /*!< SYS_T::DDRCQCSR: AXIQBYPAS Mask        */

#define SYS_DDRCQCSR_AXIQDENYIF_Pos      (8)                                               /*!< SYS_T::DDRCQCSR: AXIQDENYIF Position   */
#define SYS_DDRCQCSR_AXIQDENYIF_Msk      (0xfful << SYS_DDRCQCSR_AXIQDENYIF_Pos)           /*!< SYS_T::DDRCQCSR: AXIQDENYIF Mask       */

#define SYS_DDRCQCSR_DDRCQBYPAS_Pos      (16)                                              /*!< SYS_T::DDRCQCSR: DDRCQBYPAS Position   */
#define SYS_DDRCQCSR_DDRCQBYPAS_Msk      (0x1ul << SYS_DDRCQCSR_DDRCQBYPAS_Pos)            /*!< SYS_T::DDRCQCSR: DDRCQBYPAS Mask       */

#define SYS_DDRCQCSR_DDRCQDENYIF_Pos     (17)                                              /*!< SYS_T::DDRCQCSR: DDRCQDENYIF Position  */
#define SYS_DDRCQCSR_DDRCQDENYIF_Msk     (0x1ul << SYS_DDRCQCSR_DDRCQDENYIF_Pos)           /*!< SYS_T::DDRCQCSR: DDRCQDENYIF Mask      */

#define SYS_DDRCQCSR_DDRQREQDLY_Pos      (24)                                              /*!< SYS_T::DDRCQCSR: DDRQREQDLY Position   */
#define SYS_DDRCQCSR_DDRQREQDLY_Msk      (0xful << SYS_DDRCQCSR_DDRQREQDLY_Pos)            /*!< SYS_T::DDRCQCSR: DDRQREQDLY Mask       */

#define SYS_DDRCQCSR_DDRQACKTO_Pos       (28)                                              /*!< SYS_T::DDRCQCSR: DDRQACKTO Position    */
#define SYS_DDRCQCSR_DDRQACKTO_Msk       (0xful << SYS_DDRCQCSR_DDRQACKTO_Pos)             /*!< SYS_T::DDRCQCSR: DDRQACKTO Mask        */

#define SYS_PMUIEN_PMUIEN_Pos            (0)                                               /*!< SYS_T::PMUIEN: PMUIEN Position         */
#define SYS_PMUIEN_PMUIEN_Msk            (0x1ul << SYS_PMUIEN_PMUIEN_Pos)                  /*!< SYS_T::PMUIEN: PMUIEN Mask             */

#define SYS_PMUIEN_A35PDWKIEN_Pos        (8)                                               /*!< SYS_T::PMUIEN: A35PDWKIEN Position     */
#define SYS_PMUIEN_A35PDWKIEN_Msk        (0x1ul << SYS_PMUIEN_A35PDWKIEN_Pos)              /*!< SYS_T::PMUIEN: A35PDWKIEN Mask         */

#define SYS_PMUIEN_RTPPDWKIEN_Pos        (12)                                              /*!< SYS_T::PMUIEN: RTPPDWKIEN Position     */
#define SYS_PMUIEN_RTPPDWKIEN_Msk        (0x1ul << SYS_PMUIEN_RTPPDWKIEN_Pos)              /*!< SYS_T::PMUIEN: RTPPDWKIEN Mask         */

#define SYS_PMUSTS_PMUIF_Pos             (0)                                               /*!< SYS_T::PMUSTS: PMUIF Position          */
#define SYS_PMUSTS_PMUIF_Msk             (0x1ul << SYS_PMUSTS_PMUIF_Pos)                   /*!< SYS_T::PMUSTS: PMUIF Mask              */

#define SYS_PMUSTS_PGTOIF_Pos            (1)                                               /*!< SYS_T::PMUSTS: PGTOIF Position         */
#define SYS_PMUSTS_PGTOIF_Msk            (0x1ul << SYS_PMUSTS_PGTOIF_Pos)                  /*!< SYS_T::PMUSTS: PGTOIF Mask             */

#define SYS_PMUSTS_L2FDONE_Pos           (5)                                               /*!< SYS_T::PMUSTS: L2FDONE Position        */
#define SYS_PMUSTS_L2FDONE_Msk           (0x1ul << SYS_PMUSTS_L2FDONE_Pos)                 /*!< SYS_T::PMUSTS: L2FDONE Mask            */

#define SYS_PMUSTS_A35PDWKIF_Pos         (8)                                               /*!< SYS_T::PMUSTS: A35PDWKIF Position      */
#define SYS_PMUSTS_A35PDWKIF_Msk         (0x1ul << SYS_PMUSTS_A35PDWKIF_Pos)               /*!< SYS_T::PMUSTS: A35PDWKIF Mask          */

#define SYS_PMUSTS_RTPPDWKIF_Pos         (12)                                              /*!< SYS_T::PMUSTS: RTPPDWKIF Position      */
#define SYS_PMUSTS_RTPPDWKIF_Msk         (0x1ul << SYS_PMUSTS_RTPPDWKIF_Pos)               /*!< SYS_T::PMUSTS: RTPPDWKIF Mask          */

#define SYS_PMUSTS_PWRACKCNT_Pos         (16)                                              /*!< SYS_T::PMUSTS: PWRACKCNT Position      */
#define SYS_PMUSTS_PWRACKCNT_Msk         (0xfffful << SYS_PMUSTS_PWRACKCNT_Pos)            /*!< SYS_T::PMUSTS: PWRACKCNT Mask          */

#define SYS_CA35WRBADR0_WRMBTADDR_Pos    (0)                                               /*!< SYS_T::CA35WRBADR0: WRMBTADDR Position */
#define SYS_CA35WRBADR0_WRMBTADDR_Msk    (0xfffffffful << SYS_CA35WRBADR0_WRMBTADDR_Pos)   /*!< SYS_T::CA35WRBADR0: WRMBTADDR Mask     */

#define SYS_CA35WRBPAR0_WRMBTPARA_Pos    (0)                                               /*!< SYS_T::CA35WRBPAR0: WRMBTPARA Position */
#define SYS_CA35WRBPAR0_WRMBTPARA_Msk    (0xfffffffful << SYS_CA35WRBPAR0_WRMBTPARA_Pos)   /*!< SYS_T::CA35WRBPAR0: WRMBTPARA Mask     */

#define SYS_CA35WRBADR1_WRMBTADDR_Pos    (0)                                               /*!< SYS_T::CA35WRBADR1: WRMBTADDR Position */
#define SYS_CA35WRBADR1_WRMBTADDR_Msk    (0xfffffffful << SYS_CA35WRBADR1_WRMBTADDR_Pos)   /*!< SYS_T::CA35WRBADR1: WRMBTADDR Mask     */

#define SYS_CA35WRBPAR1_WRMBTPARA_Pos    (0)                                               /*!< SYS_T::CA35WRBPAR1: WRMBTPARA Position */
#define SYS_CA35WRBPAR1_WRMBTPARA_Msk    (0xfffffffful << SYS_CA35WRBPAR1_WRMBTPARA_Pos)   /*!< SYS_T::CA35WRBPAR1: WRMBTPARA Mask     */

#define SYS_USBPMISCR_PHY0POR_Pos        (0)                                               /*!< SYS_T::USBPMISCR: PHY0POR Position     */
#define SYS_USBPMISCR_PHY0POR_Msk        (0x1ul << SYS_USBPMISCR_PHY0POR_Pos)              /*!< SYS_T::USBPMISCR: PHY0POR Mask         */

#define SYS_USBPMISCR_PHY0SUSPEND_Pos    (1)                                               /*!< SYS_T::USBPMISCR: PHY0SUSPEND Position */
#define SYS_USBPMISCR_PHY0SUSPEND_Msk    (0x1ul << SYS_USBPMISCR_PHY0SUSPEND_Pos)          /*!< SYS_T::USBPMISCR: PHY0SUSPEND Mask     */

#define SYS_USBPMISCR_PHY0COMN_Pos       (2)                                               /*!< SYS_T::USBPMISCR: PHY0COMN Position    */
#define SYS_USBPMISCR_PHY0COMN_Msk       (0x1ul << SYS_USBPMISCR_PHY0COMN_Pos)             /*!< SYS_T::USBPMISCR: PHY0COMN Mask        */

#define SYS_USBPMISCR_VBUSDGSEL_Pos      (4)                                               /*!< SYS_T::USBPMISCR: VBUSDGSEL Position   */
#define SYS_USBPMISCR_VBUSDGSEL_Msk      (0x7ul << SYS_USBPMISCR_VBUSDGSEL_Pos)            /*!< SYS_T::USBPMISCR: VBUSDGSEL Mask       */

#define SYS_USBPMISCR_EFUSESEL0_Pos      (7)                                               /*!< SYS_T::USBPMISCR: EFUSESEL0 Position   */
#define SYS_USBPMISCR_EFUSESEL0_Msk      (0x1ul << SYS_USBPMISCR_EFUSESEL0_Pos)            /*!< SYS_T::USBPMISCR: EFUSESEL0 Mask       */

#define SYS_USBPMISCR_PHY0HSTCKSTB_Pos   (8)                                               /*!< SYS_T::USBPMISCR: PHY0HSTCKSTB Position*/
#define SYS_USBPMISCR_PHY0HSTCKSTB_Msk   (0x1ul << SYS_USBPMISCR_PHY0HSTCKSTB_Pos)         /*!< SYS_T::USBPMISCR: PHY0HSTCKSTB Mask    */

#define SYS_USBPMISCR_PHY0CK12MSTB_Pos   (9)                                               /*!< SYS_T::USBPMISCR: PHY0CK12MSTB Position*/
#define SYS_USBPMISCR_PHY0CK12MSTB_Msk   (0x1ul << SYS_USBPMISCR_PHY0CK12MSTB_Pos)         /*!< SYS_T::USBPMISCR: PHY0CK12MSTB Mask    */

#define SYS_USBPMISCR_PHY0DEVCKSTB_Pos   (10)                                              /*!< SYS_T::USBPMISCR: PHY0DEVCKSTB Position*/
#define SYS_USBPMISCR_PHY0DEVCKSTB_Msk   (0x1ul << SYS_USBPMISCR_PHY0DEVCKSTB_Pos)         /*!< SYS_T::USBPMISCR: PHY0DEVCKSTB Mask    */

#define SYS_USBPMISCR_RTUNESEL0_Pos      (11)                                              /*!< SYS_T::USBPMISCR: RTUNESEL0 Position   */
#define SYS_USBPMISCR_RTUNESEL0_Msk      (0x1ul << SYS_USBPMISCR_RTUNESEL0_Pos)            /*!< SYS_T::USBPMISCR: RTUNESEL0 Mask       */

#define SYS_USBPMISCR_RCALCODE0_Pos      (12)                                              /*!< SYS_T::USBPMISCR: RCALCODE0 Position   */
#define SYS_USBPMISCR_RCALCODE0_Msk      (0xful << SYS_USBPMISCR_RCALCODE0_Pos)            /*!< SYS_T::USBPMISCR: RCALCODE0 Mask       */

#define SYS_USBPMISCR_PHY1POR_Pos        (16)                                              /*!< SYS_T::USBPMISCR: PHY1POR Position     */
#define SYS_USBPMISCR_PHY1POR_Msk        (0x1ul << SYS_USBPMISCR_PHY1POR_Pos)              /*!< SYS_T::USBPMISCR: PHY1POR Mask         */

#define SYS_USBPMISCR_PHY1SUSPEND_Pos    (17)                                              /*!< SYS_T::USBPMISCR: PHY1SUSPEND Position */
#define SYS_USBPMISCR_PHY1SUSPEND_Msk    (0x1ul << SYS_USBPMISCR_PHY1SUSPEND_Pos)          /*!< SYS_T::USBPMISCR: PHY1SUSPEND Mask     */

#define SYS_USBPMISCR_PHY1COMN_Pos       (18)                                              /*!< SYS_T::USBPMISCR: PHY1COMN Position    */
#define SYS_USBPMISCR_PHY1COMN_Msk       (0x1ul << SYS_USBPMISCR_PHY1COMN_Pos)             /*!< SYS_T::USBPMISCR: PHY1COMN Mask        */

#define SYS_USBPMISCR_EFUSESEL1_Pos      (23)                                              /*!< SYS_T::USBPMISCR: EFUSESEL1 Position   */
#define SYS_USBPMISCR_EFUSESEL1_Msk      (0x1ul << SYS_USBPMISCR_EFUSESEL1_Pos)            /*!< SYS_T::USBPMISCR: EFUSESEL1 Mask       */

#define SYS_USBPMISCR_PHY1HSTCKSTB_Pos   (24)                                              /*!< SYS_T::USBPMISCR: PHY1HSTCKSTB Position*/
#define SYS_USBPMISCR_PHY1HSTCKSTB_Msk   (0x1ul << SYS_USBPMISCR_PHY1HSTCKSTB_Pos)         /*!< SYS_T::USBPMISCR: PHY1HSTCKSTB Mask    */

#define SYS_USBPMISCR_PHY1CK12MSTB_Pos   (25)                                              /*!< SYS_T::USBPMISCR: PHY1CK12MSTB Position*/
#define SYS_USBPMISCR_PHY1CK12MSTB_Msk   (0x1ul << SYS_USBPMISCR_PHY1CK12MSTB_Pos)         /*!< SYS_T::USBPMISCR: PHY1CK12MSTB Mask    */

#define SYS_USBPMISCR_RTUNESEL1_Pos      (27)                                              /*!< SYS_T::USBPMISCR: RTUNESEL1 Position   */
#define SYS_USBPMISCR_RTUNESEL1_Msk      (0x1ul << SYS_USBPMISCR_RTUNESEL1_Pos)            /*!< SYS_T::USBPMISCR: RTUNESEL1 Mask       */

#define SYS_USBPMISCR_RCALCODE1_Pos      (28)                                              /*!< SYS_T::USBPMISCR: RCALCODE1 Position   */
#define SYS_USBPMISCR_RCALCODE1_Msk      (0xful << SYS_USBPMISCR_RCALCODE1_Pos)            /*!< SYS_T::USBPMISCR: RCALCODE1 Mask       */

#define SYS_USBP0PCR_COMPDISTUNE_Pos     (0)                                               /*!< SYS_T::USBP0PCR: COMPDISTUNE Position  */
#define SYS_USBP0PCR_COMPDISTUNE_Msk     (0x7ul << SYS_USBP0PCR_COMPDISTUNE_Pos)           /*!< SYS_T::USBP0PCR: COMPDISTUNE Mask      */

#define SYS_USBP0PCR_EQBYPASSENB_Pos     (3)                                               /*!< SYS_T::USBP0PCR: EQBYPASSENB Position  */
#define SYS_USBP0PCR_EQBYPASSENB_Msk     (0x1ul << SYS_USBP0PCR_EQBYPASSENB_Pos)           /*!< SYS_T::USBP0PCR: EQBYPASSENB Mask      */

#define SYS_USBP0PCR_SQRXTUNE_Pos        (4)                                               /*!< SYS_T::USBP0PCR: SQRXTUNE Position     */
#define SYS_USBP0PCR_SQRXTUNE_Msk        (0x7ul << SYS_USBP0PCR_SQRXTUNE_Pos)              /*!< SYS_T::USBP0PCR: SQRXTUNE Mask         */

#define SYS_USBP0PCR_TXPREEMPPULSETUNE_Pos (7)                                             /*!< SYS_T::USBP0PCR: TXPREEMPPULSETUNE Position*/
#define SYS_USBP0PCR_TXPREEMPPULSETUNE_Msk (0x1ul << SYS_USBP0PCR_TXPREEMPPULSETUNE_Pos)   /*!< SYS_T::USBP0PCR: TXPREEMPPULSETUNE Mask*/

#define SYS_USBP0PCR_PLLPTUNE_Pos        (8)                                               /*!< SYS_T::USBP0PCR: PLLPTUNE Position     */
#define SYS_USBP0PCR_PLLPTUNE_Msk        (0xful << SYS_USBP0PCR_PLLPTUNE_Pos)              /*!< SYS_T::USBP0PCR: PLLPTUNE Mask         */

#define SYS_USBP0PCR_TXFSLSTUNE_Pos      (12)                                              /*!< SYS_T::USBP0PCR: TXFSLSTUNE Position   */
#define SYS_USBP0PCR_TXFSLSTUNE_Msk      (0xful << SYS_USBP0PCR_TXFSLSTUNE_Pos)            /*!< SYS_T::USBP0PCR: TXFSLSTUNE Mask       */

#define SYS_USBP0PCR_PLLITUNE_Pos        (16)                                              /*!< SYS_T::USBP0PCR: PLLITUNE Position     */
#define SYS_USBP0PCR_PLLITUNE_Msk        (0x3ul << SYS_USBP0PCR_PLLITUNE_Pos)              /*!< SYS_T::USBP0PCR: PLLITUNE Mask         */

#define SYS_USBP0PCR_TXPREEMPAMPTUNE_Pos (20)                                              /*!< SYS_T::USBP0PCR: TXPREEMPAMPTUNE Position*/
#define SYS_USBP0PCR_TXPREEMPAMPTUNE_Msk (0x3ul << SYS_USBP0PCR_TXPREEMPAMPTUNE_Pos)       /*!< SYS_T::USBP0PCR: TXPREEMPAMPTUNE Mask  */

#define SYS_USBP0PCR_TXRISETUNE_Pos      (22)                                              /*!< SYS_T::USBP0PCR: TXRISETUNE Position   */
#define SYS_USBP0PCR_TXRISETUNE_Msk      (0x3ul << SYS_USBP0PCR_TXRISETUNE_Pos)            /*!< SYS_T::USBP0PCR: TXRISETUNE Mask       */

#define SYS_USBP0PCR_TXVREFTUNE_Pos      (24)                                              /*!< SYS_T::USBP0PCR: TXVREFTUNE Position   */
#define SYS_USBP0PCR_TXVREFTUNE_Msk      (0xful << SYS_USBP0PCR_TXVREFTUNE_Pos)            /*!< SYS_T::USBP0PCR: TXVREFTUNE Mask       */

#define SYS_USBP0PCR_TXHSXVTUNE_Pos      (28)                                              /*!< SYS_T::USBP0PCR: TXHSXVTUNE Position   */
#define SYS_USBP0PCR_TXHSXVTUNE_Msk      (0x3ul << SYS_USBP0PCR_TXHSXVTUNE_Pos)            /*!< SYS_T::USBP0PCR: TXHSXVTUNE Mask       */

#define SYS_USBP0PCR_TXRESTUNE_Pos       (30)                                              /*!< SYS_T::USBP0PCR: TXRESTUNE Position    */
#define SYS_USBP0PCR_TXRESTUNE_Msk       (0x3ul << SYS_USBP0PCR_TXRESTUNE_Pos)             /*!< SYS_T::USBP0PCR: TXRESTUNE Mask        */

#define SYS_USBP1PCR_COMPDISTUNE_Pos     (0)                                               /*!< SYS_T::USBP1PCR: COMPDISTUNE Position  */
#define SYS_USBP1PCR_COMPDISTUNE_Msk     (0x7ul << SYS_USBP1PCR_COMPDISTUNE_Pos)           /*!< SYS_T::USBP1PCR: COMPDISTUNE Mask      */

#define SYS_USBP1PCR_EQBYPASSENB_Pos     (3)                                               /*!< SYS_T::USBP1PCR: EQBYPASSENB Position  */
#define SYS_USBP1PCR_EQBYPASSENB_Msk     (0x1ul << SYS_USBP1PCR_EQBYPASSENB_Pos)           /*!< SYS_T::USBP1PCR: EQBYPASSENB Mask      */

#define SYS_USBP1PCR_SQRXTUNE_Pos        (4)                                               /*!< SYS_T::USBP1PCR: SQRXTUNE Position     */
#define SYS_USBP1PCR_SQRXTUNE_Msk        (0x7ul << SYS_USBP1PCR_SQRXTUNE_Pos)              /*!< SYS_T::USBP1PCR: SQRXTUNE Mask         */

#define SYS_USBP1PCR_TXPREEMPPULSETUNE_Pos (7)                                             /*!< SYS_T::USBP1PCR: TXPREEMPPULSETUNE Position*/
#define SYS_USBP1PCR_TXPREEMPPULSETUNE_Msk (0x1ul << SYS_USBP1PCR_TXPREEMPPULSETUNE_Pos)   /*!< SYS_T::USBP1PCR: TXPREEMPPULSETUNE Mask*/

#define SYS_USBP1PCR_PLLPTUNE_Pos        (8)                                               /*!< SYS_T::USBP1PCR: PLLPTUNE Position     */
#define SYS_USBP1PCR_PLLPTUNE_Msk        (0xful << SYS_USBP1PCR_PLLPTUNE_Pos)              /*!< SYS_T::USBP1PCR: PLLPTUNE Mask         */

#define SYS_USBP1PCR_TXFSLSTUNE_Pos      (12)                                              /*!< SYS_T::USBP1PCR: TXFSLSTUNE Position   */
#define SYS_USBP1PCR_TXFSLSTUNE_Msk      (0xful << SYS_USBP1PCR_TXFSLSTUNE_Pos)            /*!< SYS_T::USBP1PCR: TXFSLSTUNE Mask       */

#define SYS_USBP1PCR_PLLITUNE_Pos        (16)                                              /*!< SYS_T::USBP1PCR: PLLITUNE Position     */
#define SYS_USBP1PCR_PLLITUNE_Msk        (0x3ul << SYS_USBP1PCR_PLLITUNE_Pos)              /*!< SYS_T::USBP1PCR: PLLITUNE Mask         */

#define SYS_USBP1PCR_TXPREEMPAMPTUNE_Pos (20)                                              /*!< SYS_T::USBP1PCR: TXPREEMPAMPTUNE Position*/
#define SYS_USBP1PCR_TXPREEMPAMPTUNE_Msk (0x3ul << SYS_USBP1PCR_TXPREEMPAMPTUNE_Pos)       /*!< SYS_T::USBP1PCR: TXPREEMPAMPTUNE Mask  */

#define SYS_USBP1PCR_TXRISETUNE_Pos      (22)                                              /*!< SYS_T::USBP1PCR: TXRISETUNE Position   */
#define SYS_USBP1PCR_TXRISETUNE_Msk      (0x3ul << SYS_USBP1PCR_TXRISETUNE_Pos)            /*!< SYS_T::USBP1PCR: TXRISETUNE Mask       */

#define SYS_USBP1PCR_TXVREFTUNE_Pos      (24)                                              /*!< SYS_T::USBP1PCR: TXVREFTUNE Position   */
#define SYS_USBP1PCR_TXVREFTUNE_Msk      (0xful << SYS_USBP1PCR_TXVREFTUNE_Pos)            /*!< SYS_T::USBP1PCR: TXVREFTUNE Mask       */

#define SYS_USBP1PCR_TXHSXVTUNE_Pos      (28)                                              /*!< SYS_T::USBP1PCR: TXHSXVTUNE Position   */
#define SYS_USBP1PCR_TXHSXVTUNE_Msk      (0x3ul << SYS_USBP1PCR_TXHSXVTUNE_Pos)            /*!< SYS_T::USBP1PCR: TXHSXVTUNE Mask       */

#define SYS_USBP1PCR_TXRESTUNE_Pos       (30)                                              /*!< SYS_T::USBP1PCR: TXRESTUNE Position    */
#define SYS_USBP1PCR_TXRESTUNE_Msk       (0x3ul << SYS_USBP1PCR_TXRESTUNE_Pos)             /*!< SYS_T::USBP1PCR: TXRESTUNE Mask        */

#define SYS_MISCFCR0_RTPICACHEN_Pos      (0)                                               /*!< SYS_T::MISCFCR0: RTPICACHEN Position   */
#define SYS_MISCFCR0_RTPICACHEN_Msk      (0x1ul << SYS_MISCFCR0_RTPICACHEN_Pos)            /*!< SYS_T::MISCFCR0: RTPICACHEN Mask       */

#define SYS_MISCFCR0_RTPDCACHEN_Pos      (1)                                               /*!< SYS_T::MISCFCR0: RTPDCACHEN Position   */
#define SYS_MISCFCR0_RTPDCACHEN_Msk      (0x1ul << SYS_MISCFCR0_RTPDCACHEN_Pos)            /*!< SYS_T::MISCFCR0: RTPDCACHEN Mask       */

#define SYS_MISCFCR0_RTPDRMAEN_Pos       (2)                                               /*!< SYS_T::MISCFCR0: RTPDRMAEN Position   */
#define SYS_MISCFCR0_RTPDRMAEN_Msk       (0x1ul << SYS_MISCFCR0_RTPDRMAEN_Pos)            /*!< SYS_T::MISCFCR0: RTPDRMAEN Mask       */

#define SYS_MISCFCR0_WDT0RSTEN_Pos       (8)                                               /*!< SYS_T::MISCFCR0: WDT0RSTEN Position    */
#define SYS_MISCFCR0_WDT0RSTEN_Msk       (0x1ul << SYS_MISCFCR0_WDT0RSTEN_Pos)             /*!< SYS_T::MISCFCR0: WDT0RSTEN Mask        */

#define SYS_MISCFCR0_HDSPUEN_Pos         (9)                                               /*!< SYS_T::MISCFCR0: HDSPUEN Position      */
#define SYS_MISCFCR0_HDSPUEN_Msk         (0x1ul << SYS_MISCFCR0_HDSPUEN_Pos)               /*!< SYS_T::MISCFCR0: HDSPUEN Mask          */

#define SYS_MISCFCR0_UHOVRCURH_Pos       (12)                                              /*!< SYS_T::MISCFCR0: UHOVRCURH Position    */
#define SYS_MISCFCR0_UHOVRCURH_Msk       (0x1ul << SYS_MISCFCR0_UHOVRCURH_Pos)             /*!< SYS_T::MISCFCR0: UHOVRCURH Mask        */

#define SYS_MISCFCR0_SELFTEST_Pos        (13)                                              /*!< SYS_T::MISCFCR0: SELFTEST Position     */
#define SYS_MISCFCR0_SELFTEST_Msk        (0x1ul << SYS_MISCFCR0_SELFTEST_Pos)              /*!< SYS_T::MISCFCR0: SELFTEST Mask         */

#define SYS_MISCFCR0_WDT1RSTEN_Pos       (14)                                              /*!< SYS_T::MISCFCR0: WDT1RSTEN Position    */
#define SYS_MISCFCR0_WDT1RSTEN_Msk       (0x1ul << SYS_MISCFCR0_WDT1RSTEN_Pos)             /*!< SYS_T::MISCFCR0: WDT1RSTEN Mask        */

#define SYS_MISCFCR0_WDT2RSTEN_Pos       (15)                                              /*!< SYS_T::MISCFCR0: WDT2RSTEN Position    */
#define SYS_MISCFCR0_WDT2RSTEN_Msk       (0x1ul << SYS_MISCFCR0_WDT2RSTEN_Pos)             /*!< SYS_T::MISCFCR0: WDT2RSTEN Mask        */

#define SYS_MISCFCR0_SDH0VSTB_Pos        (16)                                              /*!< SYS_T::MISCFCR0: SDH0VSTB Position     */
#define SYS_MISCFCR0_SDH0VSTB_Msk        (0x1ul << SYS_MISCFCR0_SDH0VSTB_Pos)              /*!< SYS_T::MISCFCR0: SDH0VSTB Mask         */

#define SYS_MISCFCR0_SDH1VSTB_Pos        (17)                                              /*!< SYS_T::MISCFCR0: SDH1VSTB Position     */
#define SYS_MISCFCR0_SDH1VSTB_Msk        (0x1ul << SYS_MISCFCR0_SDH1VSTB_Pos)              /*!< SYS_T::MISCFCR0: SDH1VSTB Mask         */

#define SYS_MISCFCR0_VBUSWKEN_Pos        (18)                                              /*!< SYS_T::MISCFCR0: VBUSWKEN Position     */
#define SYS_MISCFCR0_VBUSWKEN_Msk        (0x1ul << SYS_MISCFCR0_VBUSWKEN_Pos)              /*!< SYS_T::MISCFCR0: VBUSWKEN Mask         */

#define SYS_MISCFCR0_LNSTWKEN_Pos        (19)                                              /*!< SYS_T::MISCFCR0: LNSTWKEN Position     */
#define SYS_MISCFCR0_LNSTWKEN_Msk        (0x1ul << SYS_MISCFCR0_LNSTWKEN_Pos)              /*!< SYS_T::MISCFCR0: LNSTWKEN Mask         */

#define SYS_MISCFCR0_DDRCGDIS_Pos        (23)                                              /*!< SYS_T::MISCFCR0: DDRCGDIS Position     */
#define SYS_MISCFCR0_DDRCGDIS_Msk        (0x1ul << SYS_MISCFCR0_DDRCGDIS_Pos)              /*!< SYS_T::MISCFCR0: DDRCGDIS Mask         */

#define SYS_MISCFCR0_DRATSRDLY_Pos       (24)                                              /*!< SYS_T::MISCFCR0: DRATSRDLY Position    */
#define SYS_MISCFCR0_DRATSRDLY_Msk       (0xfful << SYS_MISCFCR0_DRATSRDLY_Pos)            /*!< SYS_T::MISCFCR0: DRATSRDLY Mask        */

#define SYS_MISCFCR1_CANFD0PDEN_Pos      (0)                                               /*!< SYS_T::MISCFCR1: CANFD0PDEN Position   */
#define SYS_MISCFCR1_CANFD0PDEN_Msk      (0x1ul << SYS_MISCFCR1_CANFD0PDEN_Pos)            /*!< SYS_T::MISCFCR1: CANFD0PDEN Mask       */

#define SYS_MISCFCR1_CANFD1PDEN_Pos      (1)                                               /*!< SYS_T::MISCFCR1: CANFD1PDEN Position   */
#define SYS_MISCFCR1_CANFD1PDEN_Msk      (0x1ul << SYS_MISCFCR1_CANFD1PDEN_Pos)            /*!< SYS_T::MISCFCR1: CANFD1PDEN Mask       */

#define SYS_MISCFCR1_CANFD2PDEN_Pos      (2)                                               /*!< SYS_T::MISCFCR1: CANFD2PDEN Position   */
#define SYS_MISCFCR1_CANFD2PDEN_Msk      (0x1ul << SYS_MISCFCR1_CANFD2PDEN_Pos)            /*!< SYS_T::MISCFCR1: CANFD2PDEN Mask       */

#define SYS_MISCFCR1_CANFD3PDEN_Pos      (3)                                               /*!< SYS_T::MISCFCR1: CANFD3PDEN Position   */
#define SYS_MISCFCR1_CANFD3PDEN_Msk      (0x1ul << SYS_MISCFCR1_CANFD3PDEN_Pos)            /*!< SYS_T::MISCFCR1: CANFD3PDEN Mask       */

#define SYS_MISCFCR1_CANFD0CKSTP_Pos     (4)                                               /*!< SYS_T::MISCFCR1: CANFD0CKSTP Position  */
#define SYS_MISCFCR1_CANFD0CKSTP_Msk     (0x1ul << SYS_MISCFCR1_CANFD0CKSTP_Pos)           /*!< SYS_T::MISCFCR1: CANFD0CKSTP Mask      */

#define SYS_MISCFCR1_CANFD1CKSTP_Pos     (5)                                               /*!< SYS_T::MISCFCR1: CANFD1CKSTP Position  */
#define SYS_MISCFCR1_CANFD1CKSTP_Msk     (0x1ul << SYS_MISCFCR1_CANFD1CKSTP_Pos)           /*!< SYS_T::MISCFCR1: CANFD1CKSTP Mask      */

#define SYS_MISCFCR1_CANFD2CKSTP_Pos     (6)                                               /*!< SYS_T::MISCFCR1: CANFD2CKSTP Position  */
#define SYS_MISCFCR1_CANFD2CKSTP_Msk     (0x1ul << SYS_MISCFCR1_CANFD2CKSTP_Pos)           /*!< SYS_T::MISCFCR1: CANFD2CKSTP Mask      */

#define SYS_MISCFCR1_CANFD3CKSTP_Pos     (7)                                               /*!< SYS_T::MISCFCR1: CANFD3CKSTP Position  */
#define SYS_MISCFCR1_CANFD3CKSTP_Msk     (0x1ul << SYS_MISCFCR1_CANFD3CKSTP_Pos)           /*!< SYS_T::MISCFCR1: CANFD3CKSTP Mask      */

#define SYS_MISCFCR1_HXTDS_Pos           (8)                                               /*!< SYS_T::MISCFCR1: HXTDS Position        */
#define SYS_MISCFCR1_HXTDS_Msk           (0x3ul << SYS_MISCFCR1_HXTDS_Pos)                 /*!< SYS_T::MISCFCR1: HXTDS Mask            */

#define SYS_MISCFCR1_TSENSRTRIM_Pos      (12)                                              /*!< SYS_T::MISCFCR1: TSENSRTRIM Position   */
#define SYS_MISCFCR1_TSENSRTRIM_Msk      (0xful << SYS_MISCFCR1_TSENSRTRIM_Pos)            /*!< SYS_T::MISCFCR1: TSENSRTRIM Mask       */

#define SYS_MISCFCR1_RMEL1RAM_Pos        (16)                                              /*!< SYS_T::MISCFCR1: RMEL1RAM Position     */
#define SYS_MISCFCR1_RMEL1RAM_Msk        (0x1ul << SYS_MISCFCR1_RMEL1RAM_Pos)              /*!< SYS_T::MISCFCR1: RMEL1RAM Mask         */

#define SYS_MISCFCR1_RMESYSRAM_Pos       (17)                                              /*!< SYS_T::MISCFCR1: RMESYSRAM Position    */
#define SYS_MISCFCR1_RMESYSRAM_Msk       (0x1ul << SYS_MISCFCR1_RMESYSRAM_Pos)             /*!< SYS_T::MISCFCR1: RMESYSRAM Mask        */

#define SYS_MISCIER_LVDIEN_Pos           (0)                                               /*!< SYS_T::MISCIER: LVDIEN Position        */
#define SYS_MISCIER_LVDIEN_Msk           (0x1ul << SYS_MISCIER_LVDIEN_Pos)                 /*!< SYS_T::MISCIER: LVDIEN Mask            */

#define SYS_MISCIER_USB0IDCHGIEN_Pos     (1)                                               /*!< SYS_T::MISCIER: USB0IDCHGIEN Position  */
#define SYS_MISCIER_USB0IDCHGIEN_Msk     (0x1ul << SYS_MISCIER_USB0IDCHGIEN_Pos)           /*!< SYS_T::MISCIER: USB0IDCHGIEN Mask      */

#define SYS_MISCIER_VBUSCHGIEN_Pos       (2)                                               /*!< SYS_T::MISCIER: VBUSCHGIEN Position    */
#define SYS_MISCIER_VBUSCHGIEN_Msk       (0x1ul << SYS_MISCIER_VBUSCHGIEN_Pos)             /*!< SYS_T::MISCIER: VBUSCHGIEN Mask        */

#define SYS_MISCISR_LVDIF_Pos            (0)                                               /*!< SYS_T::MISCISR: LVDIF Position         */
#define SYS_MISCISR_LVDIF_Msk            (0x1ul << SYS_MISCISR_LVDIF_Pos)                  /*!< SYS_T::MISCISR: LVDIF Mask             */

#define SYS_MISCISR_USB0IDCHGIF_Pos      (1)                                               /*!< SYS_T::MISCISR: USB0IDCHGIF Position   */
#define SYS_MISCISR_USB0IDCHGIF_Msk      (0x1ul << SYS_MISCISR_USB0IDCHGIF_Pos)            /*!< SYS_T::MISCISR: USB0IDCHGIF Mask       */

#define SYS_MISCISR_VBUSCHGIF_Pos        (2)                                               /*!< SYS_T::MISCISR: VBUSCHGIF Position     */
#define SYS_MISCISR_VBUSCHGIF_Msk        (0x1ul << SYS_MISCISR_VBUSCHGIF_Pos)              /*!< SYS_T::MISCISR: VBUSCHGIF Mask         */

#define SYS_MISCISR_LVDSTS_Pos           (16)                                              /*!< SYS_T::MISCISR: LVDSTS Position        */
#define SYS_MISCISR_LVDSTS_Msk           (0x1ul << SYS_MISCISR_LVDSTS_Pos)                 /*!< SYS_T::MISCISR: LVDSTS Mask            */

#define SYS_MISCISR_USB0IDSTS_Pos        (17)                                              /*!< SYS_T::MISCISR: USB0IDSTS Position     */
#define SYS_MISCISR_USB0IDSTS_Msk        (0x1ul << SYS_MISCISR_USB0IDSTS_Pos)              /*!< SYS_T::MISCISR: USB0IDSTS Mask         */

#define SYS_MISCISR_VBUSSTS_Pos          (18)                                              /*!< SYS_T::MISCISR: VBUSSTS Position       */
#define SYS_MISCISR_VBUSSTS_Msk          (0x1ul << SYS_MISCISR_VBUSSTS_Pos)                /*!< SYS_T::MISCISR: VBUSSTS Mask           */

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

#define SYS_GPC_MFPH_PC14MFP_Pos         (24)                                              /*!< SYS_T::GPC_MFPH: PC14MFP Position      */
#define SYS_GPC_MFPH_PC14MFP_Msk         (0xful << SYS_GPC_MFPH_PC14MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC14MFP Mask          */

#define SYS_GPC_MFPH_PC15MFP_Pos         (28)                                              /*!< SYS_T::GPC_MFPH: PC15MFP Position      */
#define SYS_GPC_MFPH_PC15MFP_Msk         (0xful << SYS_GPC_MFPH_PC15MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC15MFP Mask          */

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

#define SYS_GPD_MFPH_PD13MFP_Pos         (20)                                              /*!< SYS_T::GPD_MFPH: PD13MFP Position      */
#define SYS_GPD_MFPH_PD13MFP_Msk         (0xful << SYS_GPD_MFPH_PD13MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD13MFP Mask          */

#define SYS_GPD_MFPH_PD14MFP_Pos         (24)                                              /*!< SYS_T::GPD_MFPH: PD14MFP Position      */
#define SYS_GPD_MFPH_PD14MFP_Msk         (0xful << SYS_GPD_MFPH_PD14MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD14MFP Mask          */

#define SYS_GPD_MFPH_PD15MFP_Pos         (28)                                              /*!< SYS_T::GPD_MFPH: PD15MFP Position      */
#define SYS_GPD_MFPH_PD15MFP_Msk         (0xful << SYS_GPD_MFPH_PD15MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD15MFP Mask          */

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

#define SYS_GPF_MFPH_PF12MFP_Pos         (16)                                              /*!< SYS_T::GPF_MFPH: PF12MFP Position      */
#define SYS_GPF_MFPH_PF12MFP_Msk         (0xful << SYS_GPF_MFPH_PF12MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF12MFP Mask          */

#define SYS_GPF_MFPH_PF13MFP_Pos         (20)                                              /*!< SYS_T::GPF_MFPH: PF13MFP Position      */
#define SYS_GPF_MFPH_PF13MFP_Msk         (0xful << SYS_GPF_MFPH_PF13MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF13MFP Mask          */

#define SYS_GPF_MFPH_PF14MFP_Pos         (24)                                              /*!< SYS_T::GPF_MFPH: PF14MFP Position      */
#define SYS_GPF_MFPH_PF14MFP_Msk         (0xful << SYS_GPF_MFPH_PF14MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF14MFP Mask          */

#define SYS_GPF_MFPH_PF15MFP_Pos         (28)                                              /*!< SYS_T::GPF_MFPH: PF15MFP Position      */
#define SYS_GPF_MFPH_PF15MFP_Msk         (0xful << SYS_GPF_MFPH_PF15MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF15MFP Mask          */

#define SYS_GPG_MFPL_PG0MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPL: PG0MFP Position       */
#define SYS_GPG_MFPL_PG0MFP_Msk          (0xful << SYS_GPG_MFPL_PG0MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG0MFP Mask           */

#define SYS_GPG_MFPL_PG1MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPL: PG1MFP Position       */
#define SYS_GPG_MFPL_PG1MFP_Msk          (0xful << SYS_GPG_MFPL_PG1MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG1MFP Mask           */

#define SYS_GPG_MFPL_PG2MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFPL: PG2MFP Position       */
#define SYS_GPG_MFPL_PG2MFP_Msk          (0xful << SYS_GPG_MFPL_PG2MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG2MFP Mask           */

#define SYS_GPG_MFPL_PG3MFP_Pos          (12)                                              /*!< SYS_T::GPG_MFPL: PG3MFP Position       */
#define SYS_GPG_MFPL_PG3MFP_Msk          (0xful << SYS_GPG_MFPL_PG3MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG3MFP Mask           */

#define SYS_GPG_MFPL_PG4MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFPL: PG4MFP Position       */
#define SYS_GPG_MFPL_PG4MFP_Msk          (0xful << SYS_GPG_MFPL_PG4MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG4MFP Mask           */

#define SYS_GPG_MFPL_PG5MFP_Pos          (20)                                              /*!< SYS_T::GPG_MFPL: PG5MFP Position       */
#define SYS_GPG_MFPL_PG5MFP_Msk          (0xful << SYS_GPG_MFPL_PG5MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG5MFP Mask           */

#define SYS_GPG_MFPL_PG6MFP_Pos          (24)                                              /*!< SYS_T::GPG_MFPL: PG6MFP Position       */
#define SYS_GPG_MFPL_PG6MFP_Msk          (0xful << SYS_GPG_MFPL_PG6MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG6MFP Mask           */

#define SYS_GPG_MFPL_PG7MFP_Pos          (28)                                              /*!< SYS_T::GPG_MFPL: PG7MFP Position       */
#define SYS_GPG_MFPL_PG7MFP_Msk          (0xful << SYS_GPG_MFPL_PG7MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG7MFP Mask           */

#define SYS_GPG_MFPH_PG8MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPH: PG8MFP Position       */
#define SYS_GPG_MFPH_PG8MFP_Msk          (0xful << SYS_GPG_MFPH_PG8MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG8MFP Mask           */

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

#define SYS_GPH_MFPL_PH0MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFPL: PH0MFP Position       */
#define SYS_GPH_MFPL_PH0MFP_Msk          (0xful << SYS_GPH_MFPL_PH0MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH0MFP Mask           */

#define SYS_GPH_MFPL_PH1MFP_Pos          (4)                                               /*!< SYS_T::GPH_MFPL: PH1MFP Position       */
#define SYS_GPH_MFPL_PH1MFP_Msk          (0xful << SYS_GPH_MFPL_PH1MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH1MFP Mask           */

#define SYS_GPH_MFPL_PH2MFP_Pos          (8)                                               /*!< SYS_T::GPH_MFPL: PH2MFP Position       */
#define SYS_GPH_MFPL_PH2MFP_Msk          (0xful << SYS_GPH_MFPL_PH2MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH2MFP Mask           */

#define SYS_GPH_MFPL_PH3MFP_Pos          (12)                                              /*!< SYS_T::GPH_MFPL: PH3MFP Position       */
#define SYS_GPH_MFPL_PH3MFP_Msk          (0xful << SYS_GPH_MFPL_PH3MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH3MFP Mask           */

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

#define SYS_GPH_MFPH_PH12MFP_Pos         (16)                                              /*!< SYS_T::GPH_MFPH: PH12MFP Position      */
#define SYS_GPH_MFPH_PH12MFP_Msk         (0xful << SYS_GPH_MFPH_PH12MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH12MFP Mask          */

#define SYS_GPH_MFPH_PH13MFP_Pos         (20)                                              /*!< SYS_T::GPH_MFPH: PH13MFP Position      */
#define SYS_GPH_MFPH_PH13MFP_Msk         (0xful << SYS_GPH_MFPH_PH13MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH13MFP Mask          */

#define SYS_GPH_MFPH_PH14MFP_Pos         (24)                                              /*!< SYS_T::GPH_MFPH: PH14MFP Position      */
#define SYS_GPH_MFPH_PH14MFP_Msk         (0xful << SYS_GPH_MFPH_PH14MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH14MFP Mask          */

#define SYS_GPH_MFPH_PH15MFP_Pos         (28)                                              /*!< SYS_T::GPH_MFPH: PH15MFP Position      */
#define SYS_GPH_MFPH_PH15MFP_Msk         (0xful << SYS_GPH_MFPH_PH15MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH15MFP Mask          */

#define SYS_GPI_MFPL_PI0MFP_Pos          (0)                                               /*!< SYS_T::GPI_MFPL: PI0MFP Position       */
#define SYS_GPI_MFPL_PI0MFP_Msk          (0xful << SYS_GPI_MFPL_PI0MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI0MFP Mask           */

#define SYS_GPI_MFPL_PI1MFP_Pos          (4)                                               /*!< SYS_T::GPI_MFPL: PI1MFP Position       */
#define SYS_GPI_MFPL_PI1MFP_Msk          (0xful << SYS_GPI_MFPL_PI1MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI1MFP Mask           */

#define SYS_GPI_MFPL_PI2MFP_Pos          (8)                                               /*!< SYS_T::GPI_MFPL: PI2MFP Position       */
#define SYS_GPI_MFPL_PI2MFP_Msk          (0xful << SYS_GPI_MFPL_PI2MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI2MFP Mask           */

#define SYS_GPI_MFPL_PI3MFP_Pos          (12)                                              /*!< SYS_T::GPI_MFPL: PI3MFP Position       */
#define SYS_GPI_MFPL_PI3MFP_Msk          (0xful << SYS_GPI_MFPL_PI3MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI3MFP Mask           */

#define SYS_GPI_MFPL_PI4MFP_Pos          (16)                                              /*!< SYS_T::GPI_MFPL: PI4MFP Position       */
#define SYS_GPI_MFPL_PI4MFP_Msk          (0xful << SYS_GPI_MFPL_PI4MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI4MFP Mask           */

#define SYS_GPI_MFPL_PI5MFP_Pos          (20)                                              /*!< SYS_T::GPI_MFPL: PI5MFP Position       */
#define SYS_GPI_MFPL_PI5MFP_Msk          (0xful << SYS_GPI_MFPL_PI5MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI5MFP Mask           */

#define SYS_GPI_MFPL_PI6MFP_Pos          (24)                                              /*!< SYS_T::GPI_MFPL: PI6MFP Position       */
#define SYS_GPI_MFPL_PI6MFP_Msk          (0xful << SYS_GPI_MFPL_PI6MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI6MFP Mask           */

#define SYS_GPI_MFPL_PI7MFP_Pos          (28)                                              /*!< SYS_T::GPI_MFPL: PI7MFP Position       */
#define SYS_GPI_MFPL_PI7MFP_Msk          (0xful << SYS_GPI_MFPL_PI7MFP_Pos)                /*!< SYS_T::GPI_MFPL: PI7MFP Mask           */

#define SYS_GPI_MFPH_PI8MFP_Pos          (0)                                               /*!< SYS_T::GPI_MFPH: PI8MFP Position       */
#define SYS_GPI_MFPH_PI8MFP_Msk          (0xful << SYS_GPI_MFPH_PI8MFP_Pos)                /*!< SYS_T::GPI_MFPH: PI8MFP Mask           */

#define SYS_GPI_MFPH_PI9MFP_Pos          (4)                                               /*!< SYS_T::GPI_MFPH: PI9MFP Position       */
#define SYS_GPI_MFPH_PI9MFP_Msk          (0xful << SYS_GPI_MFPH_PI9MFP_Pos)                /*!< SYS_T::GPI_MFPH: PI9MFP Mask           */

#define SYS_GPI_MFPH_PI10MFP_Pos         (8)                                               /*!< SYS_T::GPI_MFPH: PI10MFP Position      */
#define SYS_GPI_MFPH_PI10MFP_Msk         (0xful << SYS_GPI_MFPH_PI10MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI10MFP Mask          */

#define SYS_GPI_MFPH_PI11MFP_Pos         (12)                                              /*!< SYS_T::GPI_MFPH: PI11MFP Position      */
#define SYS_GPI_MFPH_PI11MFP_Msk         (0xful << SYS_GPI_MFPH_PI11MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI11MFP Mask          */

#define SYS_GPI_MFPH_PI12MFP_Pos         (16)                                              /*!< SYS_T::GPI_MFPH: PI12MFP Position      */
#define SYS_GPI_MFPH_PI12MFP_Msk         (0xful << SYS_GPI_MFPH_PI12MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI12MFP Mask          */

#define SYS_GPI_MFPH_PI13MFP_Pos         (20)                                              /*!< SYS_T::GPI_MFPH: PI13MFP Position      */
#define SYS_GPI_MFPH_PI13MFP_Msk         (0xful << SYS_GPI_MFPH_PI13MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI13MFP Mask          */

#define SYS_GPI_MFPH_PI14MFP_Pos         (24)                                              /*!< SYS_T::GPI_MFPH: PI14MFP Position      */
#define SYS_GPI_MFPH_PI14MFP_Msk         (0xful << SYS_GPI_MFPH_PI14MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI14MFP Mask          */

#define SYS_GPI_MFPH_PI15MFP_Pos         (28)                                              /*!< SYS_T::GPI_MFPH: PI15MFP Position      */
#define SYS_GPI_MFPH_PI15MFP_Msk         (0xful << SYS_GPI_MFPH_PI15MFP_Pos)               /*!< SYS_T::GPI_MFPH: PI15MFP Mask          */

#define SYS_GPJ_MFPL_PJ0MFP_Pos          (0)                                               /*!< SYS_T::GPJ_MFPL: PJ0MFP Position       */
#define SYS_GPJ_MFPL_PJ0MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ0MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ0MFP Mask           */

#define SYS_GPJ_MFPL_PJ1MFP_Pos          (4)                                               /*!< SYS_T::GPJ_MFPL: PJ1MFP Position       */
#define SYS_GPJ_MFPL_PJ1MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ1MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ1MFP Mask           */

#define SYS_GPJ_MFPL_PJ2MFP_Pos          (8)                                               /*!< SYS_T::GPJ_MFPL: PJ2MFP Position       */
#define SYS_GPJ_MFPL_PJ2MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ2MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ2MFP Mask           */

#define SYS_GPJ_MFPL_PJ3MFP_Pos          (12)                                              /*!< SYS_T::GPJ_MFPL: PJ3MFP Position       */
#define SYS_GPJ_MFPL_PJ3MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ3MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ3MFP Mask           */

#define SYS_GPJ_MFPL_PJ4MFP_Pos          (16)                                              /*!< SYS_T::GPJ_MFPL: PJ4MFP Position       */
#define SYS_GPJ_MFPL_PJ4MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ4MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ4MFP Mask           */

#define SYS_GPJ_MFPL_PJ5MFP_Pos          (20)                                              /*!< SYS_T::GPJ_MFPL: PJ5MFP Position       */
#define SYS_GPJ_MFPL_PJ5MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ5MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ5MFP Mask           */

#define SYS_GPJ_MFPL_PJ6MFP_Pos          (24)                                              /*!< SYS_T::GPJ_MFPL: PJ6MFP Position       */
#define SYS_GPJ_MFPL_PJ6MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ6MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ6MFP Mask           */

#define SYS_GPJ_MFPL_PJ7MFP_Pos          (28)                                              /*!< SYS_T::GPJ_MFPL: PJ7MFP Position       */
#define SYS_GPJ_MFPL_PJ7MFP_Msk          (0xful << SYS_GPJ_MFPL_PJ7MFP_Pos)                /*!< SYS_T::GPJ_MFPL: PJ7MFP Mask           */

#define SYS_GPJ_MFPH_PJ8MFP_Pos          (0)                                               /*!< SYS_T::GPJ_MFPH: PJ8MFP Position       */
#define SYS_GPJ_MFPH_PJ8MFP_Msk          (0xful << SYS_GPJ_MFPH_PJ8MFP_Pos)                /*!< SYS_T::GPJ_MFPH: PJ8MFP Mask           */

#define SYS_GPJ_MFPH_PJ9MFP_Pos          (4)                                               /*!< SYS_T::GPJ_MFPH: PJ9MFP Position       */
#define SYS_GPJ_MFPH_PJ9MFP_Msk          (0xful << SYS_GPJ_MFPH_PJ9MFP_Pos)                /*!< SYS_T::GPJ_MFPH: PJ9MFP Mask           */

#define SYS_GPJ_MFPH_PJ10MFP_Pos         (8)                                               /*!< SYS_T::GPJ_MFPH: PJ10MFP Position      */
#define SYS_GPJ_MFPH_PJ10MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ10MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ10MFP Mask          */

#define SYS_GPJ_MFPH_PJ11MFP_Pos         (12)                                              /*!< SYS_T::GPJ_MFPH: PJ11MFP Position      */
#define SYS_GPJ_MFPH_PJ11MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ11MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ11MFP Mask          */

#define SYS_GPJ_MFPH_PJ12MFP_Pos         (16)                                              /*!< SYS_T::GPJ_MFPH: PJ12MFP Position      */
#define SYS_GPJ_MFPH_PJ12MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ12MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ12MFP Mask          */

#define SYS_GPJ_MFPH_PJ13MFP_Pos         (20)                                              /*!< SYS_T::GPJ_MFPH: PJ13MFP Position      */
#define SYS_GPJ_MFPH_PJ13MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ13MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ13MFP Mask          */

#define SYS_GPJ_MFPH_PJ14MFP_Pos         (24)                                              /*!< SYS_T::GPJ_MFPH: PJ14MFP Position      */
#define SYS_GPJ_MFPH_PJ14MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ14MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ14MFP Mask          */

#define SYS_GPJ_MFPH_PJ15MFP_Pos         (28)                                              /*!< SYS_T::GPJ_MFPH: PJ15MFP Position      */
#define SYS_GPJ_MFPH_PJ15MFP_Msk         (0xful << SYS_GPJ_MFPH_PJ15MFP_Pos)               /*!< SYS_T::GPJ_MFPH: PJ15MFP Mask          */

#define SYS_GPK_MFPL_PK0MFP_Pos          (0)                                               /*!< SYS_T::GPK_MFPL: PK0MFP Position       */
#define SYS_GPK_MFPL_PK0MFP_Msk          (0xful << SYS_GPK_MFPL_PK0MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK0MFP Mask           */

#define SYS_GPK_MFPL_PK1MFP_Pos          (4)                                               /*!< SYS_T::GPK_MFPL: PK1MFP Position       */
#define SYS_GPK_MFPL_PK1MFP_Msk          (0xful << SYS_GPK_MFPL_PK1MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK1MFP Mask           */

#define SYS_GPK_MFPL_PK2MFP_Pos          (8)                                               /*!< SYS_T::GPK_MFPL: PK2MFP Position       */
#define SYS_GPK_MFPL_PK2MFP_Msk          (0xful << SYS_GPK_MFPL_PK2MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK2MFP Mask           */

#define SYS_GPK_MFPL_PK3MFP_Pos          (12)                                              /*!< SYS_T::GPK_MFPL: PK3MFP Position       */
#define SYS_GPK_MFPL_PK3MFP_Msk          (0xful << SYS_GPK_MFPL_PK3MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK3MFP Mask           */

#define SYS_GPK_MFPL_PK4MFP_Pos          (16)                                              /*!< SYS_T::GPK_MFPL: PK4MFP Position       */
#define SYS_GPK_MFPL_PK4MFP_Msk          (0xful << SYS_GPK_MFPL_PK4MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK4MFP Mask           */

#define SYS_GPK_MFPL_PK5MFP_Pos          (20)                                              /*!< SYS_T::GPK_MFPL: PK5MFP Position       */
#define SYS_GPK_MFPL_PK5MFP_Msk          (0xful << SYS_GPK_MFPL_PK5MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK5MFP Mask           */

#define SYS_GPK_MFPL_PK6MFP_Pos          (24)                                              /*!< SYS_T::GPK_MFPL: PK6MFP Position       */
#define SYS_GPK_MFPL_PK6MFP_Msk          (0xful << SYS_GPK_MFPL_PK6MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK6MFP Mask           */

#define SYS_GPK_MFPL_PK7MFP_Pos          (28)                                              /*!< SYS_T::GPK_MFPL: PK7MFP Position       */
#define SYS_GPK_MFPL_PK7MFP_Msk          (0xful << SYS_GPK_MFPL_PK7MFP_Pos)                /*!< SYS_T::GPK_MFPL: PK7MFP Mask           */

#define SYS_GPK_MFPH_PK8MFP_Pos          (0)                                               /*!< SYS_T::GPK_MFPH: PK8MFP Position       */
#define SYS_GPK_MFPH_PK8MFP_Msk          (0xful << SYS_GPK_MFPH_PK8MFP_Pos)                /*!< SYS_T::GPK_MFPH: PK8MFP Mask           */

#define SYS_GPK_MFPH_PK9MFP_Pos          (4)                                               /*!< SYS_T::GPK_MFPH: PK9MFP Position       */
#define SYS_GPK_MFPH_PK9MFP_Msk          (0xful << SYS_GPK_MFPH_PK9MFP_Pos)                /*!< SYS_T::GPK_MFPH: PK9MFP Mask           */

#define SYS_GPK_MFPH_PK10MFP_Pos         (8)                                               /*!< SYS_T::GPK_MFPH: PK10MFP Position      */
#define SYS_GPK_MFPH_PK10MFP_Msk         (0xful << SYS_GPK_MFPH_PK10MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK10MFP Mask          */

#define SYS_GPK_MFPH_PK11MFP_Pos         (12)                                              /*!< SYS_T::GPK_MFPH: PK11MFP Position      */
#define SYS_GPK_MFPH_PK11MFP_Msk         (0xful << SYS_GPK_MFPH_PK11MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK11MFP Mask          */

#define SYS_GPK_MFPH_PK12MFP_Pos         (16)                                              /*!< SYS_T::GPK_MFPH: PK12MFP Position      */
#define SYS_GPK_MFPH_PK12MFP_Msk         (0xful << SYS_GPK_MFPH_PK12MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK12MFP Mask          */

#define SYS_GPK_MFPH_PK13MFP_Pos         (20)                                              /*!< SYS_T::GPK_MFPH: PK13MFP Position      */
#define SYS_GPK_MFPH_PK13MFP_Msk         (0xful << SYS_GPK_MFPH_PK13MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK13MFP Mask          */

#define SYS_GPK_MFPH_PK14MFP_Pos         (24)                                              /*!< SYS_T::GPK_MFPH: PK14MFP Position      */
#define SYS_GPK_MFPH_PK14MFP_Msk         (0xful << SYS_GPK_MFPH_PK14MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK14MFP Mask          */

#define SYS_GPK_MFPH_PK15MFP_Pos         (28)                                              /*!< SYS_T::GPK_MFPH: PK15MFP Position      */
#define SYS_GPK_MFPH_PK15MFP_Msk         (0xful << SYS_GPK_MFPH_PK15MFP_Pos)               /*!< SYS_T::GPK_MFPH: PK15MFP Mask          */

#define SYS_GPL_MFPL_PL0MFP_Pos          (0)                                               /*!< SYS_T::GPL_MFPL: PL0MFP Position       */
#define SYS_GPL_MFPL_PL0MFP_Msk          (0xful << SYS_GPL_MFPL_PL0MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL0MFP Mask           */

#define SYS_GPL_MFPL_PL1MFP_Pos          (4)                                               /*!< SYS_T::GPL_MFPL: PL1MFP Position       */
#define SYS_GPL_MFPL_PL1MFP_Msk          (0xful << SYS_GPL_MFPL_PL1MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL1MFP Mask           */

#define SYS_GPL_MFPL_PL2MFP_Pos          (8)                                               /*!< SYS_T::GPL_MFPL: PL2MFP Position       */
#define SYS_GPL_MFPL_PL2MFP_Msk          (0xful << SYS_GPL_MFPL_PL2MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL2MFP Mask           */

#define SYS_GPL_MFPL_PL3MFP_Pos          (12)                                              /*!< SYS_T::GPL_MFPL: PL3MFP Position       */
#define SYS_GPL_MFPL_PL3MFP_Msk          (0xful << SYS_GPL_MFPL_PL3MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL3MFP Mask           */

#define SYS_GPL_MFPL_PL4MFP_Pos          (16)                                              /*!< SYS_T::GPL_MFPL: PL4MFP Position       */
#define SYS_GPL_MFPL_PL4MFP_Msk          (0xful << SYS_GPL_MFPL_PL4MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL4MFP Mask           */

#define SYS_GPL_MFPL_PL5MFP_Pos          (20)                                              /*!< SYS_T::GPL_MFPL: PL5MFP Position       */
#define SYS_GPL_MFPL_PL5MFP_Msk          (0xful << SYS_GPL_MFPL_PL5MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL5MFP Mask           */

#define SYS_GPL_MFPL_PL6MFP_Pos          (24)                                              /*!< SYS_T::GPL_MFPL: PL6MFP Position       */
#define SYS_GPL_MFPL_PL6MFP_Msk          (0xful << SYS_GPL_MFPL_PL6MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL6MFP Mask           */

#define SYS_GPL_MFPL_PL7MFP_Pos          (28)                                              /*!< SYS_T::GPL_MFPL: PL7MFP Position       */
#define SYS_GPL_MFPL_PL7MFP_Msk          (0xful << SYS_GPL_MFPL_PL7MFP_Pos)                /*!< SYS_T::GPL_MFPL: PL7MFP Mask           */

#define SYS_GPL_MFPH_PL8MFP_Pos          (0)                                               /*!< SYS_T::GPL_MFPH: PL8MFP Position       */
#define SYS_GPL_MFPH_PL8MFP_Msk          (0xful << SYS_GPL_MFPH_PL8MFP_Pos)                /*!< SYS_T::GPL_MFPH: PL8MFP Mask           */

#define SYS_GPL_MFPH_PL9MFP_Pos          (4)                                               /*!< SYS_T::GPL_MFPH: PL9MFP Position       */
#define SYS_GPL_MFPH_PL9MFP_Msk          (0xful << SYS_GPL_MFPH_PL9MFP_Pos)                /*!< SYS_T::GPL_MFPH: PL9MFP Mask           */

#define SYS_GPL_MFPH_PL10MFP_Pos         (8)                                               /*!< SYS_T::GPL_MFPH: PL10MFP Position      */
#define SYS_GPL_MFPH_PL10MFP_Msk         (0xful << SYS_GPL_MFPH_PL10MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL10MFP Mask          */

#define SYS_GPL_MFPH_PL11MFP_Pos         (12)                                              /*!< SYS_T::GPL_MFPH: PL11MFP Position      */
#define SYS_GPL_MFPH_PL11MFP_Msk         (0xful << SYS_GPL_MFPH_PL11MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL11MFP Mask          */

#define SYS_GPL_MFPH_PL12MFP_Pos         (16)                                              /*!< SYS_T::GPL_MFPH: PL12MFP Position      */
#define SYS_GPL_MFPH_PL12MFP_Msk         (0xful << SYS_GPL_MFPH_PL12MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL12MFP Mask          */

#define SYS_GPL_MFPH_PL13MFP_Pos         (20)                                              /*!< SYS_T::GPL_MFPH: PL13MFP Position      */
#define SYS_GPL_MFPH_PL13MFP_Msk         (0xful << SYS_GPL_MFPH_PL13MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL13MFP Mask          */

#define SYS_GPL_MFPH_PL14MFP_Pos         (24)                                              /*!< SYS_T::GPL_MFPH: PL14MFP Position      */
#define SYS_GPL_MFPH_PL14MFP_Msk         (0xful << SYS_GPL_MFPH_PL14MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL14MFP Mask          */

#define SYS_GPL_MFPH_PL15MFP_Pos         (28)                                              /*!< SYS_T::GPL_MFPH: PL15MFP Position      */
#define SYS_GPL_MFPH_PL15MFP_Msk         (0xful << SYS_GPL_MFPH_PL15MFP_Pos)               /*!< SYS_T::GPL_MFPH: PL15MFP Mask          */

#define SYS_GPM_MFPL_PM0MFP_Pos          (0)                                               /*!< SYS_T::GPM_MFPL: PM0MFP Position       */
#define SYS_GPM_MFPL_PM0MFP_Msk          (0xful << SYS_GPM_MFPL_PM0MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM0MFP Mask           */

#define SYS_GPM_MFPL_PM1MFP_Pos          (4)                                               /*!< SYS_T::GPM_MFPL: PM1MFP Position       */
#define SYS_GPM_MFPL_PM1MFP_Msk          (0xful << SYS_GPM_MFPL_PM1MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM1MFP Mask           */

#define SYS_GPM_MFPL_PM2MFP_Pos          (8)                                               /*!< SYS_T::GPM_MFPL: PM2MFP Position       */
#define SYS_GPM_MFPL_PM2MFP_Msk          (0xful << SYS_GPM_MFPL_PM2MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM2MFP Mask           */

#define SYS_GPM_MFPL_PM3MFP_Pos          (12)                                              /*!< SYS_T::GPM_MFPL: PM3MFP Position       */
#define SYS_GPM_MFPL_PM3MFP_Msk          (0xful << SYS_GPM_MFPL_PM3MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM3MFP Mask           */

#define SYS_GPM_MFPL_PM4MFP_Pos          (16)                                              /*!< SYS_T::GPM_MFPL: PM4MFP Position       */
#define SYS_GPM_MFPL_PM4MFP_Msk          (0xful << SYS_GPM_MFPL_PM4MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM4MFP Mask           */

#define SYS_GPM_MFPL_PM5MFP_Pos          (20)                                              /*!< SYS_T::GPM_MFPL: PM5MFP Position       */
#define SYS_GPM_MFPL_PM5MFP_Msk          (0xful << SYS_GPM_MFPL_PM5MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM5MFP Mask           */

#define SYS_GPM_MFPL_PM6MFP_Pos          (24)                                              /*!< SYS_T::GPM_MFPL: PM6MFP Position       */
#define SYS_GPM_MFPL_PM6MFP_Msk          (0xful << SYS_GPM_MFPL_PM6MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM6MFP Mask           */

#define SYS_GPM_MFPL_PM7MFP_Pos          (28)                                              /*!< SYS_T::GPM_MFPL: PM7MFP Position       */
#define SYS_GPM_MFPL_PM7MFP_Msk          (0xful << SYS_GPM_MFPL_PM7MFP_Pos)                /*!< SYS_T::GPM_MFPL: PM7MFP Mask           */

#define SYS_GPM_MFPH_PM8MFP_Pos          (0)                                               /*!< SYS_T::GPM_MFPH: PM8MFP Position       */
#define SYS_GPM_MFPH_PM8MFP_Msk          (0xful << SYS_GPM_MFPH_PM8MFP_Pos)                /*!< SYS_T::GPM_MFPH: PM8MFP Mask           */

#define SYS_GPM_MFPH_PM9MFP_Pos          (4)                                               /*!< SYS_T::GPM_MFPH: PM9MFP Position       */
#define SYS_GPM_MFPH_PM9MFP_Msk          (0xful << SYS_GPM_MFPH_PM9MFP_Pos)                /*!< SYS_T::GPM_MFPH: PM9MFP Mask           */

#define SYS_GPM_MFPH_PM10MFP_Pos         (8)                                               /*!< SYS_T::GPM_MFPH: PM10MFP Position      */
#define SYS_GPM_MFPH_PM10MFP_Msk         (0xful << SYS_GPM_MFPH_PM10MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM10MFP Mask          */

#define SYS_GPM_MFPH_PM11MFP_Pos         (12)                                              /*!< SYS_T::GPM_MFPH: PM11MFP Position      */
#define SYS_GPM_MFPH_PM11MFP_Msk         (0xful << SYS_GPM_MFPH_PM11MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM11MFP Mask          */

#define SYS_GPM_MFPH_PM12MFP_Pos         (16)                                              /*!< SYS_T::GPM_MFPH: PM12MFP Position      */
#define SYS_GPM_MFPH_PM12MFP_Msk         (0xful << SYS_GPM_MFPH_PM12MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM12MFP Mask          */

#define SYS_GPM_MFPH_PM13MFP_Pos         (20)                                              /*!< SYS_T::GPM_MFPH: PM13MFP Position      */
#define SYS_GPM_MFPH_PM13MFP_Msk         (0xful << SYS_GPM_MFPH_PM13MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM13MFP Mask          */

#define SYS_GPM_MFPH_PM14MFP_Pos         (24)                                              /*!< SYS_T::GPM_MFPH: PM14MFP Position      */
#define SYS_GPM_MFPH_PM14MFP_Msk         (0xful << SYS_GPM_MFPH_PM14MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM14MFP Mask          */

#define SYS_GPM_MFPH_PM15MFP_Pos         (28)                                              /*!< SYS_T::GPM_MFPH: PM15MFP Position      */
#define SYS_GPM_MFPH_PM15MFP_Msk         (0xful << SYS_GPM_MFPH_PM15MFP_Pos)               /*!< SYS_T::GPM_MFPH: PM15MFP Mask          */

#define SYS_GPN_MFPL_PN0MFP_Pos          (0)                                               /*!< SYS_T::GPN_MFPL: PN0MFP Position       */
#define SYS_GPN_MFPL_PN0MFP_Msk          (0xful << SYS_GPN_MFPL_PN0MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN0MFP Mask           */

#define SYS_GPN_MFPL_PN1MFP_Pos          (4)                                               /*!< SYS_T::GPN_MFPL: PN1MFP Position       */
#define SYS_GPN_MFPL_PN1MFP_Msk          (0xful << SYS_GPN_MFPL_PN1MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN1MFP Mask           */

#define SYS_GPN_MFPL_PN2MFP_Pos          (8)                                               /*!< SYS_T::GPN_MFPL: PN2MFP Position       */
#define SYS_GPN_MFPL_PN2MFP_Msk          (0xful << SYS_GPN_MFPL_PN2MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN2MFP Mask           */

#define SYS_GPN_MFPL_PN3MFP_Pos          (12)                                              /*!< SYS_T::GPN_MFPL: PN3MFP Position       */
#define SYS_GPN_MFPL_PN3MFP_Msk          (0xful << SYS_GPN_MFPL_PN3MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN3MFP Mask           */

#define SYS_GPN_MFPL_PN4MFP_Pos          (16)                                              /*!< SYS_T::GPN_MFPL: PN4MFP Position       */
#define SYS_GPN_MFPL_PN4MFP_Msk          (0xful << SYS_GPN_MFPL_PN4MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN4MFP Mask           */

#define SYS_GPN_MFPL_PN5MFP_Pos          (20)                                              /*!< SYS_T::GPN_MFPL: PN5MFP Position       */
#define SYS_GPN_MFPL_PN5MFP_Msk          (0xful << SYS_GPN_MFPL_PN5MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN5MFP Mask           */

#define SYS_GPN_MFPL_PN6MFP_Pos          (24)                                              /*!< SYS_T::GPN_MFPL: PN6MFP Position       */
#define SYS_GPN_MFPL_PN6MFP_Msk          (0xful << SYS_GPN_MFPL_PN6MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN6MFP Mask           */

#define SYS_GPN_MFPL_PN7MFP_Pos          (28)                                              /*!< SYS_T::GPN_MFPL: PN7MFP Position       */
#define SYS_GPN_MFPL_PN7MFP_Msk          (0xful << SYS_GPN_MFPL_PN7MFP_Pos)                /*!< SYS_T::GPN_MFPL: PN7MFP Mask           */

#define SYS_GPN_MFPH_PN8MFP_Pos          (0)                                               /*!< SYS_T::GPN_MFPH: PN8MFP Position       */
#define SYS_GPN_MFPH_PN8MFP_Msk          (0xful << SYS_GPN_MFPH_PN8MFP_Pos)                /*!< SYS_T::GPN_MFPH: PN8MFP Mask           */

#define SYS_GPN_MFPH_PN9MFP_Pos          (4)                                               /*!< SYS_T::GPN_MFPH: PN9MFP Position       */
#define SYS_GPN_MFPH_PN9MFP_Msk          (0xful << SYS_GPN_MFPH_PN9MFP_Pos)                /*!< SYS_T::GPN_MFPH: PN9MFP Mask           */

#define SYS_GPN_MFPH_PN10MFP_Pos         (8)                                               /*!< SYS_T::GPN_MFPH: PN10MFP Position      */
#define SYS_GPN_MFPH_PN10MFP_Msk         (0xful << SYS_GPN_MFPH_PN10MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN10MFP Mask          */

#define SYS_GPN_MFPH_PN11MFP_Pos         (12)                                              /*!< SYS_T::GPN_MFPH: PN11MFP Position      */
#define SYS_GPN_MFPH_PN11MFP_Msk         (0xful << SYS_GPN_MFPH_PN11MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN11MFP Mask          */

#define SYS_GPN_MFPH_PN12MFP_Pos         (16)                                              /*!< SYS_T::GPN_MFPH: PN12MFP Position      */
#define SYS_GPN_MFPH_PN12MFP_Msk         (0xful << SYS_GPN_MFPH_PN12MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN12MFP Mask          */

#define SYS_GPN_MFPH_PN13MFP_Pos         (20)                                              /*!< SYS_T::GPN_MFPH: PN13MFP Position      */
#define SYS_GPN_MFPH_PN13MFP_Msk         (0xful << SYS_GPN_MFPH_PN13MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN13MFP Mask          */

#define SYS_GPN_MFPH_PN14MFP_Pos         (24)                                              /*!< SYS_T::GPN_MFPH: PN14MFP Position      */
#define SYS_GPN_MFPH_PN14MFP_Msk         (0xful << SYS_GPN_MFPH_PN14MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN14MFP Mask          */

#define SYS_GPN_MFPH_PN15MFP_Pos         (28)                                              /*!< SYS_T::GPN_MFPH: PN15MFP Position      */
#define SYS_GPN_MFPH_PN15MFP_Msk         (0xful << SYS_GPN_MFPH_PN15MFP_Pos)               /*!< SYS_T::GPN_MFPH: PN15MFP Mask          */

#define SYS_TSENSRFCR_TSENSRREF0_Pos     (0)                                               /*!< SYS_T::TSENSRFCR: TSENSRREF0 Position  */
#define SYS_TSENSRFCR_TSENSRREF0_Msk     (0xfful << SYS_TSENSRFCR_TSENSRREF0_Pos)          /*!< SYS_T::TSENSRFCR: TSENSRREF0 Mask      */

#define SYS_TSENSRFCR_TSENSRREF1_Pos     (8)                                               /*!< SYS_T::TSENSRFCR: TSENSRREF1 Position  */
#define SYS_TSENSRFCR_TSENSRREF1_Msk     (0xfful << SYS_TSENSRFCR_TSENSRREF1_Pos)          /*!< SYS_T::TSENSRFCR: TSENSRREF1 Mask      */

#define SYS_TSENSRFCR_TSENSRDATA_Pos     (16)                                              /*!< SYS_T::TSENSRFCR: TSENSRDATA Position  */
#define SYS_TSENSRFCR_TSENSRDATA_Msk     (0xffful << SYS_TSENSRFCR_TSENSRDATA_Pos)         /*!< SYS_T::TSENSRFCR: TSENSRDATA Mask      */

#define SYS_TSENSRFCR_PD_Pos             (28)                                              /*!< SYS_T::TSENSRFCR: PD Position          */
#define SYS_TSENSRFCR_PD_Msk             (0x1ul << SYS_TSENSRFCR_PD_Pos)                   /*!< SYS_T::TSENSRFCR: PD Mask              */

#define SYS_TSENSRFCR_REFUDEN_Pos        (29)                                              /*!< SYS_T::TSENSRFCR: REFUDEN Position     */
#define SYS_TSENSRFCR_REFUDEN_Msk        (0x1ul << SYS_TSENSRFCR_REFUDEN_Pos)              /*!< SYS_T::TSENSRFCR: REFUDEN Mask         */

#define SYS_TSENSRFCR_DATAVALID_Pos      (31)                                              /*!< SYS_T::TSENSRFCR: DATAVALID Position   */
#define SYS_TSENSRFCR_DATAVALID_Msk      (0x1ul << SYS_TSENSRFCR_DATAVALID_Pos)            /*!< SYS_T::TSENSRFCR: DATAVALID Mask       */

#define SYS_GMAC0MISCR_RMIIEN_Pos        (0)                                               /*!< SYS_T::GMAC0MISCR: RMIIEN Position     */
#define SYS_GMAC0MISCR_RMIIEN_Msk        (0x1ul << SYS_GMAC0MISCR_RMIIEN_Pos)              /*!< SYS_T::GMAC0MISCR: RMIIEN Mask         */

#define SYS_GMAC0MISCR_PFRMTXEN_Pos      (1)                                               /*!< SYS_T::GMAC0MISCR: PFRMTXEN Position   */
#define SYS_GMAC0MISCR_PFRMTXEN_Msk      (0x1ul << SYS_GMAC0MISCR_PFRMTXEN_Pos)            /*!< SYS_T::GMAC0MISCR: PFRMTXEN Mask       */

#define SYS_GMAC0MISCR_TXCLKINV_Pos      (8)                                               /*!< SYS_T::GMAC0MISCR: TXCLKINV Position   */
#define SYS_GMAC0MISCR_TXCLKINV_Msk      (0x1ul << SYS_GMAC0MISCR_TXCLKINV_Pos)            /*!< SYS_T::GMAC0MISCR: TXCLKINV Mask       */

#define SYS_GMAC0MISCR_TXCLKGEN_Pos      (9)                                               /*!< SYS_T::GMAC0MISCR: TXCLKGEN Position   */
#define SYS_GMAC0MISCR_TXCLKGEN_Msk      (0x1ul << SYS_GMAC0MISCR_TXCLKGEN_Pos)            /*!< SYS_T::GMAC0MISCR: TXCLKGEN Mask       */

#define SYS_GMAC0MISCR_RXCLKINV_Pos      (12)                                              /*!< SYS_T::GMAC0MISCR: RXCLKINV Position   */
#define SYS_GMAC0MISCR_RXCLKINV_Msk      (0x1ul << SYS_GMAC0MISCR_RXCLKINV_Pos)            /*!< SYS_T::GMAC0MISCR: RXCLKINV Mask       */

#define SYS_GMAC0MISCR_TXCLKDLY_Pos      (16)                                              /*!< SYS_T::GMAC0MISCR: TXCLKDLY Position   */
#define SYS_GMAC0MISCR_TXCLKDLY_Msk      (0xful << SYS_GMAC0MISCR_TXCLKDLY_Pos)            /*!< SYS_T::GMAC0MISCR: TXCLKDLY Mask       */

#define SYS_GMAC0MISCR_RXCLKDLY_Pos      (20)                                              /*!< SYS_T::GMAC0MISCR: RXCLKDLY Position   */
#define SYS_GMAC0MISCR_RXCLKDLY_Msk      (0xful << SYS_GMAC0MISCR_RXCLKDLY_Pos)            /*!< SYS_T::GMAC0MISCR: RXCLKDLY Mask       */

#define SYS_GMAC1MISCR_RMIIEN_Pos        (0)                                               /*!< SYS_T::GMAC1MISCR: RMIIEN Position     */
#define SYS_GMAC1MISCR_RMIIEN_Msk        (0x1ul << SYS_GMAC1MISCR_RMIIEN_Pos)              /*!< SYS_T::GMAC1MISCR: RMIIEN Mask         */

#define SYS_GMAC1MISCR_PFRMTXEN_Pos      (1)                                               /*!< SYS_T::GMAC1MISCR: PFRMTXEN Position   */
#define SYS_GMAC1MISCR_PFRMTXEN_Msk      (0x1ul << SYS_GMAC1MISCR_PFRMTXEN_Pos)            /*!< SYS_T::GMAC1MISCR: PFRMTXEN Mask       */

#define SYS_GMAC1MISCR_TXCLKINV_Pos      (8)                                               /*!< SYS_T::GMAC1MISCR: TXCLKINV Position   */
#define SYS_GMAC1MISCR_TXCLKINV_Msk      (0x1ul << SYS_GMAC1MISCR_TXCLKINV_Pos)            /*!< SYS_T::GMAC1MISCR: TXCLKINV Mask       */

#define SYS_GMAC1MISCR_TXCLKGEN_Pos      (9)                                               /*!< SYS_T::GMAC1MISCR: TXCLKGEN Position   */
#define SYS_GMAC1MISCR_TXCLKGEN_Msk      (0x1ul << SYS_GMAC1MISCR_TXCLKGEN_Pos)            /*!< SYS_T::GMAC1MISCR: TXCLKGEN Mask       */

#define SYS_GMAC1MISCR_RXCLKINV_Pos      (12)                                              /*!< SYS_T::GMAC1MISCR: RXCLKINV Position   */
#define SYS_GMAC1MISCR_RXCLKINV_Msk      (0x1ul << SYS_GMAC1MISCR_RXCLKINV_Pos)            /*!< SYS_T::GMAC1MISCR: RXCLKINV Mask       */

#define SYS_GMAC1MISCR_TXCLKDLY_Pos      (16)                                              /*!< SYS_T::GMAC1MISCR: TXCLKDLY Position   */
#define SYS_GMAC1MISCR_TXCLKDLY_Msk      (0xful << SYS_GMAC1MISCR_TXCLKDLY_Pos)            /*!< SYS_T::GMAC1MISCR: TXCLKDLY Mask       */

#define SYS_GMAC1MISCR_RXCLKDLY_Pos      (20)                                              /*!< SYS_T::GMAC1MISCR: RXCLKDLY Position   */
#define SYS_GMAC1MISCR_RXCLKDLY_Msk      (0xful << SYS_GMAC1MISCR_RXCLKDLY_Pos)            /*!< SYS_T::GMAC1MISCR: RXCLKDLY Mask       */

#define SYS_MACAD0LSR_MACADRLSR_Pos      (0)                                               /*!< SYS_T::MACAD0LSR: MACADRLSR Position   */
#define SYS_MACAD0LSR_MACADRLSR_Msk      (0xfffffffful << SYS_MACAD0LSR_MACADRLSR_Pos)     /*!< SYS_T::MACAD0LSR: MACADRLSR Mask       */

#define SYS_MACAD0HSR_MACADRHSR_Pos      (0)                                               /*!< SYS_T::MACAD0HSR: MACADRHSR Position   */
#define SYS_MACAD0HSR_MACADRHSR_Msk      (0xfffful << SYS_MACAD0HSR_MACADRHSR_Pos)         /*!< SYS_T::MACAD0HSR: MACADRHSR Mask       */

#define SYS_MACAD1LSR_MACADRLSR_Pos      (0)                                               /*!< SYS_T::MACAD1LSR: MACADRLSR Position   */
#define SYS_MACAD1LSR_MACADRLSR_Msk      (0xfffffffful << SYS_MACAD1LSR_MACADRLSR_Pos)     /*!< SYS_T::MACAD1LSR: MACADRLSR Mask       */

#define SYS_MACAD1HSR_MACADRHSR_Pos      (0)                                               /*!< SYS_T::MACAD1HSR: MACADRHSR Position   */
#define SYS_MACAD1HSR_MACADRHSR_Msk      (0xfffful << SYS_MACAD1HSR_MACADRHSR_Pos)         /*!< SYS_T::MACAD1HSR: MACADRHSR Mask       */

#define SYS_CSDBGCTL_DBGRST_Pos          (0)                                               /*!< SYS_T::CSDBGCTL: DBGRST Position       */
#define SYS_CSDBGCTL_DBGRST_Msk          (0x1ul << SYS_CSDBGCTL_DBGRST_Pos)                /*!< SYS_T::CSDBGCTL: DBGRST Mask           */

#define SYS_CSDBGCTL_DBGPWRUPREQ_Pos     (1)                                               /*!< SYS_T::CSDBGCTL: DBGPWRUPREQ Position  */
#define SYS_CSDBGCTL_DBGPWRUPREQ_Msk     (0x1ul << SYS_CSDBGCTL_DBGPWRUPREQ_Pos)           /*!< SYS_T::CSDBGCTL: DBGPWRUPREQ Mask      */

#define SYS_CSDBGCTL_DBGPWRUPACK_Pos     (2)                                               /*!< SYS_T::CSDBGCTL: DBGPWRUPACK Position  */
#define SYS_CSDBGCTL_DBGPWRUPACK_Msk     (0x1ul << SYS_CSDBGCTL_DBGPWRUPACK_Pos)           /*!< SYS_T::CSDBGCTL: DBGPWRUPACK Mask      */

#define SYS_CSDBGCTL_LPEMU_Pos           (3)                                               /*!< SYS_T::CSDBGCTL: LPEMU Position        */
#define SYS_CSDBGCTL_LPEMU_Msk           (0x1ul << SYS_CSDBGCTL_LPEMU_Pos)                 /*!< SYS_T::CSDBGCTL: LPEMU Mask            */

#define SYS_GPAB_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPAB_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPAB_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPAB_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPAB_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS10 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPAB_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS11 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPAB_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS12 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPAB_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS13 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPAB_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS14 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPAB_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPAB_MFOS: GPIOxMFOS15 Position */
#define SYS_GPAB_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS16 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS17 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS18 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS19 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS20 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS21 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS22 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS23 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS24 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS25 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS26 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS27 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS28 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS29 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS30 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPAB_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPAB_MFOS: GPIOyMFOS31 Position */
#define SYS_GPAB_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPAB_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPAB_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPCD_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPCD_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPCD_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPCD_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS10 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS11 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS12 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS13 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS14 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPCD_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPCD_MFOS: GPIOxMFOS15 Position */
#define SYS_GPCD_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS16 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS17 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS18 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS19 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS20 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS21 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS22 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS23 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS24 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS25 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS26 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS27 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS28 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS29 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS30 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPCD_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPCD_MFOS: GPIOyMFOS31 Position */
#define SYS_GPCD_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPCD_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPCD_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPEF_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPEF_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPEF_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPEF_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS10 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS11 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS12 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS13 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS14 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPEF_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPEF_MFOS: GPIOxMFOS15 Position */
#define SYS_GPEF_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS16 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS17 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS18 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS19 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS20 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS21 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS22 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS23 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS24 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS25 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS26 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS27 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS28 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS29 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS30 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPEF_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPEF_MFOS: GPIOyMFOS31 Position */
#define SYS_GPEF_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPEF_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPEF_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPGH_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPGH_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPGH_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPGH_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS10 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS11 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS12 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS13 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS14 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPGH_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPGH_MFOS: GPIOxMFOS15 Position */
#define SYS_GPGH_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS16 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS17 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS18 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS19 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS20 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS21 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS22 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS23 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS24 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS25 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS26 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS27 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS28 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS29 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS30 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPGH_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPGH_MFOS: GPIOyMFOS31 Position */
#define SYS_GPGH_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPGH_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPGH_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPIJ_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPIJ_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS10 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS11 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS12 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS13 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS14 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPIJ_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS15 Position */
#define SYS_GPIJ_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS16 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS17 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS18 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS19 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS20 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS21 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS22 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS23 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS24 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS25 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS26 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS27 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS28 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS29 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS30 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPIJ_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS31 Position */
#define SYS_GPIJ_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPIJ_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPIJ_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPKL_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPKL_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPKL_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPKL_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS10 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS11 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS12 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS13 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS14 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPKL_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPKL_MFOS: GPIOxMFOS15 Position */
#define SYS_GPKL_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS16 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS17 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS18 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS19 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS20 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS21 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS22 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS23 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS24 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS25 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS26 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS27 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS28 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS29 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS30 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPKL_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPKL_MFOS: GPIOyMFOS31 Position */
#define SYS_GPKL_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPKL_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPKL_MFOS: GPIOyMFOS31 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS0_Pos     (0)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS0 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS0_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS0_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS0 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS1_Pos     (1)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS1 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS1_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS1_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS1 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS2_Pos     (2)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS2 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS2_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS2_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS2 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS3_Pos     (3)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS3 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS3_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS3_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS3 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS4_Pos     (4)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS4 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS4_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS4_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS4 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS5_Pos     (5)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS5 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS5_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS5_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS5 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS6_Pos     (6)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS6 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS6_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS6_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS6 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS7_Pos     (7)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS7 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS7_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS7_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS7 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS8_Pos     (8)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS8 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS8_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS8_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS8 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS9_Pos     (9)                                               /*!< SYS_T::GPMN_MFOS: GPIOxMFOS9 Position  */
#define SYS_GPMN_MFOS_GPIOxMFOS9_Msk     (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS9_Pos)           /*!< SYS_T::GPMN_MFOS: GPIOxMFOS9 Mask      */

#define SYS_GPMN_MFOS_GPIOxMFOS10_Pos    (10)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS10 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS10_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS10_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS10 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS11_Pos    (11)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS11 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS11_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS11_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS11 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS12_Pos    (12)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS12 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS12_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS12_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS12 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS13_Pos    (13)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS13 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS13_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS13_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS13 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS14_Pos    (14)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS14 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS14_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS14_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS14 Mask     */

#define SYS_GPMN_MFOS_GPIOxMFOS15_Pos    (15)                                              /*!< SYS_T::GPMN_MFOS: GPIOxMFOS15 Position */
#define SYS_GPMN_MFOS_GPIOxMFOS15_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOxMFOS15_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOxMFOS15 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS16_Pos    (16)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS16 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS16_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS16_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS16 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS17_Pos    (17)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS17 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS17_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS17_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS17 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS18_Pos    (18)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS18 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS18_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS18_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS18 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS19_Pos    (19)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS19 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS19_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS19_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS19 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS20_Pos    (20)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS20 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS20_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS20_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS20 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS21_Pos    (21)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS21 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS21_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS21_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS21 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS22_Pos    (22)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS22 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS22_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS22_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS22 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS23_Pos    (23)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS23 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS23_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS23_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS23 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS24_Pos    (24)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS24 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS24_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS24_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS24 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS25_Pos    (25)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS25 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS25_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS25_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS25 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS26_Pos    (26)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS26 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS26_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS26_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS26 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS27_Pos    (27)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS27 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS27_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS27_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS27 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS28_Pos    (28)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS28 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS28_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS28_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS28 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS29_Pos    (29)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS29 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS29_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS29_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS29 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS30_Pos    (30)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS30 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS30_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS30_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS30 Mask     */

#define SYS_GPMN_MFOS_GPIOyMFOS31_Pos    (31)                                              /*!< SYS_T::GPMN_MFOS: GPIOyMFOS31 Position */
#define SYS_GPMN_MFOS_GPIOyMFOS31_Msk    (0x1ul << SYS_GPMN_MFOS_GPIOyMFOS31_Pos)          /*!< SYS_T::GPMN_MFOS: GPIOyMFOS31 Mask     */

#define SYS_UID0_UID_Pos                 (0)                                               /*!< SYS_T::UID0: UID Position              */
#define SYS_UID0_UID_Msk                 (0xfffffffful << SYS_UID0_UID_Pos)                /*!< SYS_T::UID0: UID Mask                  */

#define SYS_UID1_UID_Pos                 (0)                                               /*!< SYS_T::UID1: UID Position              */
#define SYS_UID1_UID_Msk                 (0xfffffffful << SYS_UID1_UID_Pos)                /*!< SYS_T::UID1: UID Mask                  */

#define SYS_UID2_UID_Pos                 (0)                                               /*!< SYS_T::UID2: UID Position              */
#define SYS_UID2_UID_Msk                 (0xfffffffful << SYS_UID2_UID_Pos)                /*!< SYS_T::UID2: UID Mask                  */

#define SYS_UCID0_UCID_Pos               (0)                                               /*!< SYS_T::UCID0: UCID Position            */
#define SYS_UCID0_UCID_Msk               (0xfffffffful << SYS_UCID0_UCID_Pos)              /*!< SYS_T::UCID0: UCID Mask                */

#define SYS_UCID1_UCID_Pos               (0)                                               /*!< SYS_T::UCID1: UCID Position            */
#define SYS_UCID1_UCID_Msk               (0xfffffffful << SYS_UCID1_UCID_Pos)              /*!< SYS_T::UCID1: UCID Mask                */

#define SYS_UCID2_UCID_Pos               (0)                                               /*!< SYS_T::UCID2: UCID Position            */
#define SYS_UCID2_UCID_Msk               (0xfffffffful << SYS_UCID2_UCID_Pos)              /*!< SYS_T::UCID2: UCID Mask                */

#define SYS_RLKTZS_REGLCTL_Pos           (0)                                               /*!< SYS_T::RLKTZS: REGLCTL Position        */
#define SYS_RLKTZS_REGLCTL_Msk           (0xfful << SYS_RLKTZS_REGLCTL_Pos)                /*!< SYS_T::RLKTZS: REGLCTL Mask            */

#define SYS_RLKTZNS_REGLCTL_Pos          (0)                                               /*!< SYS_T::RLKTZNS: REGLCTL Position       */
#define SYS_RLKTZNS_REGLCTL_Msk          (0xfful << SYS_RLKTZNS_REGLCTL_Pos)               /*!< SYS_T::RLKTZNS: REGLCTL Mask           */

#define SYS_RLKSUBM_REGLCTL_Pos          (0)                                               /*!< SYS_T::RLKSUBM: REGLCTL Position       */
#define SYS_RLKSUBM_REGLCTL_Msk          (0xfful << SYS_RLKSUBM_REGLCTL_Pos)

/**@}*/ /* SYS_CONST */
/**@}*/ /* end of SYS register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __SYS_REG_H__ */
