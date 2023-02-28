/**************************************************************************//**
 * @file     ddr32phy_reg.h
 * @brief    DDR32PHY register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __DDR32PHY_REG_H__
#define __DDR32PHY_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif
/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- DDR 3/2 PHY Controller -------------------------*/
/**
    @addtogroup DDR32PHY DDR 3/2 PHY Controller(DDR32PHY)
    Memory Mapped Structure for DDRPHY Controller
@{ */

typedef struct
{


    /**
     * @var DDRPHY_T::RIDR
     * Offset: 0x00  Revision Identification Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PUBMNR    |PUB Minor Revision
     * |        |          |Indicates minor update of the PUB such as bug fixes. Normally no new features are included.
     * |[7:4]   |PUBMDR    |PUB Moderate Revision
     * |        |          |Indicates moderate revision of the PUB such as addition of new features
     * |        |          |Normally the new version is still compatible with previous versions.
     * |[11:8]  |PUBMJR    |PUB Major Revision
     * |        |          |Indicates major revision of the PUB such addition of the features that make the new version not compatible with previous versions.
     * |[15:12] |PHYMNR    |PHY Minor Revision
     * |        |          |Indicates minor update of the PHY such as bug fixes. Normally no new features are included.
     * |[19:16] |PHYMDR    |PHY Moderate Revision
     * |        |          |Indicates moderate revision of the PHY such as addition of new features
     * |        |          |Normally the new version is still compatible with previous versions.
     * |[23:20] |PHYMJR    |PHY Major Revision
     * |        |          |Indicates major revision of the PHY such addition of the features that make the new version not compatible with previous versions.
     * |[31:24] |UDRID     |User-Defined Revision ID
     * |        |          |General purpose revision identification set by the user.
     * @var DDRPHY_T::PIR
     * Offset: 0x04  PHY Initialization Register (PIR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INIT      |Initialization Trigger
     * |        |          |A write of '1' to this bit triggers the DDR system initialization, including PHY initialization, DRAM initialization, and PHY training
     * |        |          |The exact initialization steps to be executed are specified in bits 1 to 15 of this register
     * |        |          |A bit setting of 1 means the step will be executed as part of the initialization sequence, while a setting of '0' means the step will be bypassed
     * |        |          |The initialization trigger bit is self-clearing.
     * |[1]     |ZCAL      |Impedance Calibration
     * |        |          |Performs PHY impedance calibration
     * |        |          |When set the impedance calibration will be performed in parallel with PHY initialization (PLL initialization + DDL calibration + PHY reset).
     * |[4]     |PLLINIT   |PLL Initialization
     * |        |          |Executes the PLL initialization sequence which includes correct driving of PLL power-down, reset and gear shift pins, and then waiting for the PHY PLLs to lock.
     * |[5]     |DCAL      |Digital Delay Line Calibration
     * |        |          |Performs PHY delay line calibration.
     * |[6]     |PHYRST    |PHY Reset
     * |        |          |Resets the AC and DATX8 modules by asserting the AC/DATX8 reset pin.
     * |[7]     |DRAMRST   |DRAM Reset
     * |        |          |Issues a reset to the DRAM (by driving the DRAM reset pin low) and wait 200us
     * |        |          |This can be triggered in isolation or with the full DRAM initialization (DRAMINIT)
     * |        |          |For the latter case, the reset is issued and 200us is waited before starting the full initialization sequence.
     * |[8]     |DRAMINIT  |DRAM Initialization
     * |        |          |Executes the DRAM initialization sequence.
     * |[9]     |WL        |Write Leveling
     * |        |          |Executes a PUB write leveling routine.
     * |[10]    |QSGATE    |Read DQS Gate Training
     * |        |          |Executes a PUB training routine to determine the optimum position of the read data DQS strobe for maximum system timing margins.
     * |[11]    |WLADJ     |Write Leveling Adjust
     * |        |          |Executes a PUB training routine that re- adjusts the write latency used during write in case the write leveling routine changed the expected latency.
     * |        |          |Note: Ensure that the DCU command cache is cleared prior to running WLADJ.
     * |[12]    |RDDSKW    |Read Data Bit Deskew
     * |        |          |Executes a PUB training routine to deskew the DQ bits during read.
     * |[13]    |WRDSKW    |Write Data Bit Deskew
     * |        |          |Executes a PUB training routine to deskew the DQ bits during write.
     * |[14]    |RDEYE     |Read Data Eye Training
     * |        |          |Executes a PUB training routine to maximize the read data eye.
     * |[15]    |WREYE     |Write Data Eye Training
     * |        |          |Executes a PUB training routine to maximize the write data eye.
     * |[16]    |ICPC      |Initialization Complete Pin Configuration
     * |        |          |Specifies how the DFI initialization complete output pin (dfi_init_complete) should be used to indicate the status of initialization
     * |        |          |Valid values are:
     * |        |          |0 = Asserted after PHY initialization (DLL locking and impedance calibration) is complete.
     * |        |          |1 = Asserted after PHY initialization is complete and the triggered the PUB initialization (DRAM initialization, data training, or initialization trigger with no selected initialization) is complete.
     * |[17]    |PLLBYP    |PLL Bypass
     * |        |          |A setting of 1 on this bit will put all PHY PLLs in bypass mode.
     * |[18]    |CTLDINIT  |Controller DRAM Initialization
     * |        |          |Indicates, if set, that DRAM initialization will be performed by the controller
     * |        |          |Otherwise if not set it indicates that DRAM initialization will be performed using the built-in initialization sequence or using software through the configuration port.
     * |[19]    |RDIMMINIT |RDIMM Initialization
     * |        |          |Executes the RDIMM buffer chip initialization before executing DRAM initialization
     * |        |          |The RDIMM buffer chip initialization is run after the DRAM is reset and CKE have been driven high by the DRAM initialization sequence.
     * |[27]    |CLRSR     |Clear Status Registers
     * |        |          |Writing 1 to this bit clears (reset to 0) select status bits in register PGSR0.
     * |        |          |This bit is primarily for debug purposes and is typically not needed during normal functional operation
     * |        |          |It can be used when PGSR.IDONE=1, to manually clear a selection of the PGSR status bits, although starting a new initialization process (PIR[0].INIT = 1'b1) automatically clears the PGSR status bits associated with the initialization steps enabled.
     * |        |          |The following list describes which bits within the PGSR0 register are cleared when CLRSR is set to 1'b1 and which bits are not cleared:
     * |        |          |The following bits are not cleared by PIR[27] (CLRSR):
     * |        |          |- PGSR0[31] (APLOCK)
     * |        |          |- PGSR0[29:28] (PLDONE_CHN)
     * |        |          |- PGSR0[23] (WLAERR)
     * |        |          |- PGSR0[21] (WLERR)
     * |        |          |- PGSR0[4] (DIDONE)
     * |        |          |- PGSR0[2] (DCDONE)
     * |        |          |- PGSR0[1] (PLDONE)
     * |        |          |- PGSR0[0] (IDONE)
     * |        |          |The following bits are always zero:
     * |        |          |- PGSR0[30] (reserved)
     * |        |          |- PGSR0[19:12] (reserved)
     * |        |          |The following bits are cleared unconditionally by PIR[27] (CLRSR):
     * |        |          |- PGSR0[27] (WEERR)
     * |        |          |- PGSR0[26] (REERR)
     * |        |          |- PGSR0[25] (WDERR)
     * |        |          |- PGSR0[24] (RDERR)
     * |        |          |- PGSR0[22] (QSGERR)
     * |        |          |- PGSR0[20] (ZCERR)
     * |        |          |- PGSR0[11] (WEDONE)
     * |        |          |- PGSR0[10] (REDONE)
     * |        |          |- PGSR0[9] (WDDONE)
     * |        |          |- PGSR0[8] (RDDONE)
     * |        |          |- PGSR0[7] (WLADONE)
     * |        |          |- PGSR0[6] (QSGDONE)
     * |        |          |- PGSR0[5] (WLDONE)
     * |        |          |- PGSR0[3] (ZCDONE)
     * |[28]    |LOCKBYP   |PLL Lock Bypass
     * |        |          |Bypasses or stops, if set, the waiting of PLLs to lock
     * |        |          |PLL lock wait is automatically triggered after reset
     * |        |          |PLL lock wait may be triggered manually using INIT and PLLINIT bits of the PIR register
     * |        |          |This bit is self-clearing.
     * |[29]    |DCALBYP   |Digital Delay Line Calibration Bypass
     * |        |          |Bypasses or stops, if set, DDL calibration that automatically triggers after reset
     * |        |          |DDL calibration may be triggered manually using INIT and DCAL bits of the PIR register
     * |        |          |This bit is self- clearing.
     * |[30]    |ZCALBYP   |Impedance Calibration Bypass
     * |        |          |Bypasses or stops, if set, impedance calibration of all ZQ control blocks that automatically triggers after reset
     * |        |          |Impedance calibration may be triggered manually using INIT and ZCAL bits of the PIR register
     * |        |          |This bit is self-clearing.
     * |[31]    |INITBYP   |Initialization Bypass
     * |        |          |Bypasses or stops, if set, all initialization routines currently running, including PHY initialization, DRAM initialization, and PHY training
     * |        |          |Initialization may be triggered manually using INIT and the other relevant bits of the PIR register
     * |        |          |This bit is self-clearing.
     * @var DDRPHY_T::PGCR0
     * Offset: 0x08  PHY General Configuration Registers 0 (PGCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WLLVT     |Write Leveling LCDL Delay VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the write leveling LCDL.
     * |[1]     |WDLVT     |Write DQ LCDL Delay VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the write DQ LCDL.
     * |[2]     |RDLVT     |Read DQS LCDL Delay VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the read DQS LCDL.
     * |[3]     |RGLVT     |Read DQS Gating LCDL Delay VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the read DQS gating LCDL.
     * |[4]     |WDBVT     |Write Data BDL VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the write data bit delay lines.
     * |[5]     |RDBVT     |Read Data BDL VT Compensation
     * |        |          |Enables, if set, the VT drift compensation of the read data bit delay lines.
     * |[6]     |DLTMODE   |Delay Line Test Mode
     * |        |          |Selects, if set, the delay line oscillator test mode
     * |        |          |Setting this bit also clears all delay line register values
     * |        |          |For DL oscillator testing, first set this bit, then apply desired non-zero LCDL and BDL register programmings.
     * |[7]     |DLTST     |Delay Line Test Start
     * |        |          |A write of '1' to this bit will trigger delay line oscillator mode period measurement
     * |        |          |This bit is not self clearing and needs to be reset to '0' before the measurement can be re-triggered.
     * |[8]     |OSCEN     |Oscillator Enable: Enables, if set, the delay line oscillation.
     * |[11:9]  |OSCDIV    |Oscillator Mode Division
     * |        |          |Specifies the factor by which the delay line oscillator mode output is divided down before it is output on the delay line digital test output pin dl_dto
     * |        |          |Valid values are:
     * |        |          |000 = Divide by 1
     * |        |          |001 = Divide by 256
     * |        |          |010 = Divide by 512
     * |        |          |011 = Divide by 1024
     * |        |          |100 = Divide by 2048
     * |        |          |101 = Divide by 4096
     * |        |          |110 = Divide by 8192
     * |        |          |111 = Divide by 65536
     * |[13:12] |OSCWDL    |Oscillator Mode Write-Leveling Delay Line Select
     * |        |          |Selects which of the two write leveling LCDLs is active
     * |        |          |The delay select value of the inactive LCDL is set to zero while the delay select value of the active LCDL can be varied by the input write leveling delay select pin
     * |        |          |Valid values are:
     * |        |          |00 = No WL LCDL is active
     * |        |          |01 = DDR WL LCDL is active
     * |        |          |10 = SDR WL LCDL is active
     * |        |          |11 = Both LCDLs are active
     * |[18:14] |DTOSEL    |Digital Test Output Select
     * |        |          |Selects the PHY digital test output that is driven onto PHY digital test output (phy_dto) pin: Valid values are:
     * |        |          |00000 = DATX8 0 PLL digital test output
     * |        |          |00001 = DATX8 1 PLL digital test output
     * |        |          |00010 = DATX8 2 PLL digital test output
     * |        |          |00011 = DATX8 3 PLL digital test output
     * |        |          |00100 = DATX8 4 PLL digital test output
     * |        |          |00101 = DATX8 5 PLL digital test output
     * |        |          |00110 = DATX8 6 PLL digital test output
     * |        |          |00111 = DATX8 7 PLL digital test output
     * |        |          |01000 = DATX8 8 PLL digital test output
     * |        |          |01001 = AC PLL digital test output
     * |        |          |01010 - 01111 = Reserved
     * |        |          |10000 = DATX8 0 delay line digital test output
     * |        |          |10001 = DATX8 1 delay line digital test output
     * |        |          |10010 = DATX8 2 delay line digital test output
     * |        |          |10011 = DATX8 3 delay line digital test output
     * |        |          |10100 = DATX8 4 delay line digital test output
     * |        |          |10101 = DATX8 5 delay line digital test output
     * |        |          |10110 = DATX8 6 delay line digital test output
     * |        |          |10111 = DATX8 7 delay line digital test output
     * |        |          |11000 = DATX8 8 delay line digital test output
     * |        |          |11001 = AC delay line digital test output
     * |        |          |11010 - 11111 = Reserved
     * |[25]    |PUBMODE   |PUB Mode Enable
     * |        |          |Enables, if set, the PUB to control the interface to the PHY and SDRAM
     * |        |          |In this mode the DFI commands from the controller are ignored
     * |        |          |The bit must be set to 0 after the system determines it is convenient to pass control of the DFI bus to the controller
     * |        |          |When set to 0 the DFI interface has control of the PHY and SDRAM interface except when triggering pub operations such as BIST, DCU or data training.
     * |[31:26] |CKEN      |CK Enable
     * |        |          |Controls whether the CK going to the SDRAM is enabled (toggling) or disabled (static value) and whether the CK is inverted
     * |        |          |Two bits for each of the up to three CK pairs
     * |        |          |Valid values for the two bits are:
     * |        |          |00 = CK disabled (Driven to constant 0)
     * |        |          |01 = CK toggling with inverted polarity
     * |        |          |10 = CK toggling with normal polarity (This should be the default setting)
     * |        |          |11 = CK disabled (Driven to constant 1)
     * @var DDRPHY_T::PGCR1
     * Offset: 0x0C  PHY General Configuration Registers 1 (PGCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PDDISDX   |Power Down Disabled Byte
     * |        |          |Indicates, if set, that the PLL and I/Os of a disabled byte should be powered down.
     * |[1]     |WLMODE    |Write Leveling Mode
     * |        |          |Indicates, if set, that the PUB is in software write leveling mode in which software executes single steps of DQS pulsing by writing '1' to PIR.WL
     * |        |          |The write leveling DQ status from the DRAM is captured in DXnGSR0.WLDQ.
     * |[2]     |WLSTEP    |Write Leveling Step
     * |        |          |Specifies the number of delay step-size increments during each step of write leveling
     * |        |          |Valid values are:
     * |        |          |0 = computed to be 1/2 of the associated lane's DXnGSR0.WLPRD value
     * |        |          |1 = 1 step size
     * |[4]     |WSLOPT    |Write System Latency Optimization
     * |        |          |Controls the insertion of a pipeline stage on the AC signals from the DFI interface to the PHY to cater for a negative write system latency (WSL) value (only -1 possible).
     * |        |          |0x0 = A pipeline stage is inserted only if WL2 training results in a WSL of -1 for any rank
     * |        |          |0x1 = Inserts a pipeline stage
     * |[5]     |ACHRST    |AC PHY High-Speed Reset
     * |        |          |A Write of '0' to this bit resets the AC macro without resetting the PUB RTL logic
     * |        |          |This bit is not self-clearing and a '1' must be written to de-assert the reset.
     * |[6]     |WLSELT    |Write Leveling Select Type
     * |        |          |Selects the encoding type for the write leveling select signal depending on the desired setup/hold margins for the internal pipelines
     * |        |          |Refer to the DDR PHY Databook for details of how the select type is used
     * |        |          |Valid values are:
     * |        |          |0 = Type 1: Setup margin of 90 degrees and hold margin of 90 degrees
     * |        |          |1 = Type 2: Setup margin of 135 degrees and hold margin of 45 degrees
     * |[8:7]   |IODDRM    |I/O DDR Mode
     * |        |          |Selects the DDR mode for the I/Os
     * |        |          |These bits connect to bits [2:1] of the IOM pin of the SSTL I/O
     * |        |          |For more information, refer to the SSTL I/O chapter in the DWC DDR PHY Databook.
     * |[9]     |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the AC master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or on when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high.
     * |[10]    |LPFEN     |Low-Pass Filter Enable
     * |        |          |Enables, if set, the low pass filtering of MDL period measurements.
     * |[12:11] |LPFDEPTH  |Low-Pass Filter Depth
     * |        |          |Specifies the number of measurements over which MDL period measurements are filtered
     * |        |          |This determines the time constant of the low pass filter
     * |        |          |Valid values are:
     * |        |          |00 = 2
     * |        |          |01 = 4
     * |        |          |10 = 8
     * |        |          |11 = 16
     * |[14:13] |FDEPTH    |Filter Depth
     * |        |          |Specifies the number of measurements over which all AC and DATX8 initial period measurements, that happen after reset or when calibration is manually triggered, are averaged
     * |        |          |Valid values are:
     * |        |          |00 = 2
     * |        |          |01 = 4
     * |        |          |10 = 8
     * |        |          |11 = 16
     * |[22:15] |DLDLMT    |Delay Line VT Drift Limit
     * |        |          |Specifies the minimum change in the delay line VT drift in one direction which should result in the assertion of the delay line VT drift status signal (vt_drift)
     * |        |          |The limit is specified in terms of delay select values
     * |        |          |A value of 0 disables the assertion of delay line VT drift status signal.
     * |[24:23] |ZCKSEL    |Impedance Clock Divider Select
     * |        |          |Selects the divide ratio for the clock used by the impedance control logic relative to the clock used by the memory controller and SDRAM.
     * |        |          |Valid values are:
     * |        |          |00 = Divide by 2
     * |        |          |01 = Divide by 8
     * |        |          |10 = Divide by 32
     * |        |          |11 = Divide by 64
     * |[25]    |DXHRST    |DX PHY High-Speed Reset
     * |        |          |a Write of '0' to this bit resets the DX macro without resetting the PUB RTL logic
     * |        |          |This bit is not self-clearing and a '1' must be written to de-assert the reset.
     * |[26]    |INHVT     |VT Calculation Inhibit
     * |        |          |Inhibits calculation of the next VT compensated delay line values
     * |        |          |A value of 1 will inhibit the VT calculation
     * |        |          |This bit should be set to 1 during writes to the delay line registers.
     * |[27]    |IOLB      |I/O Loop-Back Select
     * |        |          |Selects where inside the I/O the loop-back of signals happens. Valid values are:
     * |        |          |1'b0 = Loopback is after output buffer; output enable must be asserted
     * |        |          |1'b1 = Loopback is before output buffer; output enable is don't care
     * |[28]    |LBDQSS    |Loopback DQS Shift
     * |        |          |Selects how the read DQS is shifted during loopback to ensure that the read DQS is centered into the read data eye
     * |        |          |Valid values are:
     * |        |          |1'b0 = PUB sets the read DQS LCDL to 0 (internally)
     * |        |          |DQS is already shifted 90 degrees by write path
     * |        |          |1'b1 = The read DQS shift is set manually through software
     * |[30:29] |LBGDQS    |Loopback DQS Gating
     * |        |          |Selects the DQS gating mode that should be used when the PHY is in loopback mode, including BIST loopback mode
     * |        |          |Valid values are:
     * |        |          |2'b00 = DQS gate is always on
     * |        |          |2'b01 = DQS gate training will be triggered on the PUB
     * |        |          |2'b10 = DQS gate is set manually using software
     * |        |          |2'b11 = Reserved
     * |[31]    |LBMODE    |Loopback Mode
     * |        |          |Indicates, if set, that the PHY/PUB is in loopback mode.
     * @var DDRPHY_T::PGSR0
     * Offset: 0x10  PHY General Status Registers 0 (PGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IDONE     |Initialization Done
     * |        |          |Indicates, if set, that the DDR system initialization has completed
     * |        |          |This bit is set after all the selected initialization routines in PIR register have completed.
     * |[1]     |PLDONE    |PLL Lock Done
     * |        |          |Indicates, if set, that PLL locking has completed.
     * |[2]     |DCDONE    |Digital Delay Line Calibration Done
     * |        |          |Indicates, if set, that DDL calibration has completed.
     * |[3]     |ZCDONE    |Impedance Calibration Done: Indicates, if set, that impedance calibration has completed.
     * |[4]     |DIDONE    |DRAM Initialization Done
     * |        |          |Indicates, if set, that DRAM initialization has completed.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that write leveling has completed.
     * |[6]     |QSGDONE   |Read DQS Gate Training Done
     * |        |          |Indicates, if set, that DQS gate training has completed.
     * |[7]     |WLADONE   |Write Leveling Adjustment Done
     * |        |          |Indicates, if set, that write leveling adjustment has completed.
     * |[8]     |RDDONE    |Read Data Bit Deskew Done
     * |        |          |Indicates, if set, that read bit deskew has completed.
     * |[9]     |WDDONE    |Write Data Bit Deskew Done
     * |        |          |Indicates, if set, that write bit deskew has completed.
     * |[10]    |REDONE    |Read Data Eye Training Done
     * |        |          |Indicates, if set, that read eye training has completed.
     * |[11]    |WEDONE    |Write Data Eye Training Done
     * |        |          |Indicates, if set, that write eye training has completed.
     * |[20]    |ZCERR     |Impedance Calibration Error
     * |        |          |Indicates, if set, that there is an error in impedance calibration.
     * |[21]    |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is an error in write leveling.
     * |[22]    |QSGERR    |Read DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training.
     * |[23]    |WLAERR    |Write Data Leveling Adjustment Error
     * |        |          |Indicates, if set, that there is an error in write leveling adjustment.
     * |[24]    |RDERR     |Read Data Bit Deskew Error
     * |        |          |Indicates, if set, that there is an error in read bit deskew.
     * |[25]    |WDERR     |Write Data Bit Deskew Error
     * |        |          |Indicates, if set, that there is an error in write bit deskew.
     * |[26]    |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that there is an error in read eye training.
     * |[27]    |WEERR     |Write Eye Training Error
     * |        |          |Indicates, if set, that there is an error in write eye training.
     * |[29:28] |PLDONE_CHN|PLL Lock Done per Channel
     * |        |          |Indicates PLL locking has completed for each underlying channel
     * |        |          |Bit 28 represents channel 0 while bit 29 represents channel 1.
     * |[31]    |APLOCK    |AC PLL Lock
     * |        |          |Indicates, if set, that AC PLL has locked. This is a direct status of the AC PLL lock pin.
     * @var DDRPHY_T::PGSR1
     * Offset: 0x14  PHY General Status Registers 1 (PGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the AC delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the AC delay line digital test output.
     * |[30]    |VTSTOP    |VT Stop
     * |        |          |Indicates, if set, that the VT calculation logic has stopped computing the next values for the VT compensated delay line values
     * |        |          |After assertion of the PGCR.INHVT, the VTSTOP bit should be read to ensure all VT compensation logic has stopped computations before writing to the delay line registers.
     * |[31]    |PARERR    |RDIMM Parity Error
     * |        |          |Indicates, if set, that there was a parity error (i.e
     * |        |          |err_out_n was sampled low) during one of the transactions to the RDIMM buffer chip
     * |        |          |This bit remains asserted until cleared by the PIR.CLRSR.
     * @var DDRPHY_T::PLLCR
     * Offset: 0x18  PLL Control Register (PLLCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |DTC       |Digital Test Control
     * |        |          |Selects various PLL digital test signals and other test mode signals to be brought out via bit [1] of the PLL digital test output (pll_dto[1])
     * |        |          |Valid values are:
     * |        |          |00 = '0' (Test output is disabled)
     * |        |          |01 = PLL x1 clock (X1)
     * |        |          |10 = PLL reference (input) clock (REF_CLK)
     * |        |          |11 = PLL feedback clock (FB_X1)
     * |[5:2]   |ATC       |Analog Test Control
     * |        |          |Selects various PLL analog test signals to be brought out via PLL analog test output pin (pll_ato)
     * |        |          |Valid values are:
     * |        |          |0000 = Reserved
     * |        |          |0001 = vdd_ckin
     * |        |          |0010 = vrfbf
     * |        |          |0011 = vdd_cko
     * |        |          |0100 = vp_cp
     * |        |          |0101 = vpfil(vp)
     * |        |          |0110 = Reserved
     * |        |          |0111 = gd
     * |        |          |1000 = vcntrl_atb
     * |        |          |1001 = vref_atb
     * |        |          |1010 = vpsf_atb
     * |        |          |1011 - 1111 = Reserved
     * |[9:6]   |ATOEN     |Analog Test Enable
     * |        |          |Selects the analog test signal that is driven on the analog test output pin
     * |        |          |Otherwise the analog test output is tri-stated
     * |        |          |This allows analog test output pins from multiple PLLs to be connected together
     * |        |          |Valid values are:
     * |        |          |0000 = All PLL analog test signals are tri-stated
     * |        |          |0001 = AC PLL analog test signal is driven out
     * |        |          |0010 = DATX8 0 PLL analog test signal is driven out
     * |        |          |0011 = DATX8 1 PLL analog test signal is driven out
     * |        |          |0100 = DATX8 2 PLL analog test signal is driven out
     * |        |          |0101 = DATX8 3 PLL analog test signal is driven out
     * |        |          |0110 = DATX8 4 PLL analog test signal is driven out
     * |        |          |0111 = DATX8 5 PLL analog test signal is driven out
     * |        |          |1000 = DATX8 6 PLL analog test signal is driven out
     * |        |          |1001 = DATX8 7 PLL analog test signal is driven out
     * |        |          |1010 = DATX8 8 PLL analog test signal is driven out
     * |        |          |1011 - 1111 = Reserved
     * |[10]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode.
     * |[12:11] |CPIC      |Charge Pump Integrating Current Control
     * |[16:13] |CPPC      |Charge Pump Proportional Current Control
     * |[17]    |QPMODE    |PLL Quadrature Phase Mode
     * |        |          |Enables, if set, the quadrature phase clock outputs. This mode is not used in this version of the PHY.
     * |[19:18] |FRQSEL    |PLL Frequency Select
     * |        |          |00 = PLL reference clock (ctl_clk/REF_CLK) ranges from 250 MHz to 400 MHz
     * |        |          |01 = PLL reference clock (ctl_clk/REF_CLK) ranges from 166 MHz to 300 MHz
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[29]    |PLLPD     |PLL Power Down
     * |        |          |Puts the PLLs in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down.
     * |[30]    |PLLRST    |PLL Rest
     * |        |          |Resets the PLLs by driving the PLL reset pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the reset.
     * |[31]    |BYP       |PLL Bypass
     * |        |          |Bypasses the PLL, if set, to 1.
     * @var DDRPHY_T::PTR0
     * Offset: 0x1C  PHY Timing Registers 0 (PTR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |tPHYRST   |PHY Reset Time
     * |        |          |Number of configuration or APB clock cycles that the PHY reset must remain asserted after PHY calibration is done before the reset to the PHY is de-asserted
     * |        |          |This is used to extend the reset to the PHY so that the reset is asserted for some clock cycles after the clocks are stable
     * |        |          |Valid values are from 1 to 63 (the value must be non-zero).
     * |[20:6]  |tPLLGS    |PLL Gear Shift Time
     * |        |          |Number of configuration or APB clock cycles from when the PLL reset pin is de-asserted to when the PLL gear shift pin is de-asserted
     * |        |          |This must correspond to a value that is equal to or more than 4us
     * |        |          |Default value corresponds to 4us.
     * |[31:21] |tPLLPD    |PLL Power-Down Time
     * |        |          |Number of configuration or APB clock cycles that the PLL must remain in power-down mode, i.e
     * |        |          |number of clock cycles from when PLL power-down pin is asserted to when PLL power-down pin is de-asserted
     * |        |          |This must correspond to a value that is equal to or more than 1us
     * |        |          |Default value corresponds to 1us.
     * @var DDRPHY_T::PTR1
     * Offset: 0x20  PHY Timing Registers 1 (PTR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12:0]  |tPLLRST   |PLL Reset Time
     * |        |          |Number of configuration or APB clock cycles that the PLL must remain in reset mode, i.e
     * |        |          |number of clock cycles from when PLL power-down pin is de-asserted and PLL reset pin is asserted to when PLL reset pin is de-asserted
     * |        |          |The setting must correspond to a value that is equal to, or greater than 3us.
     * |[31:16] |tPLLLOCK  |PLL Lock Time
     * |        |          |Number of configuration or APB clock cycles for the PLL to stabilize and lock, i.e
     * |        |          |number of clock cycles from when the PLL reset pin is de-asserted to when the PLL has lock and is ready for use
     * |        |          |This must correspond to a value that is equal to or more than 100us
     * |        |          |Default value corresponds to 100us.
     * @var DDRPHY_T::PTR2
     * Offset: 0x24  PHY Timing Registers 2 (PTR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |tCALON    |Calibration On Time
     * |        |          |Number of clock cycles that the calibration clock is enabled (cal_clk_en asserted).
     * |[9:5]   |tCALS     |Calibration Setup Time
     * |        |          |Number of controller clock cycles from when calibration is enabled (cal_en asserted) to when the calibration clock is asserted again (cal_clk_en asserted).
     * |[14:10] |tCALH     |Calibration Hold Time
     * |        |          |Number of controller clock cycles from when the clock was disabled (cal_clk_en deasserted) to when calibration is enable (cal_en asserted).
     * |[19:15] |tWLDLYS   |Write Leveling Delay Settling Time
     * |        |          |Number of controller clock cycles from when a new value of the write leveling delay is applied to the LCDL to when to DQS high is driven high
     * |        |          |This allows the delay to settle.
     * @var DDRPHY_T::PTR3
     * Offset: 0x28  PHY Timing Registers 3 (PTR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[19:0]  |tDINIT0   |DRAM Initialization Time 0
     * |        |          |DRAM initialization time in DRAM clock cycles corresponding to the following:
     * |        |          |DDR3 = CKE low time with power and clock stable (500 us) DDR2 = CKE low time with power and clock stable (200 us) Default value corresponds to DDR3 500 us at 1066 MHz.
     * |        |          |During Verilog simulations, it is recommended that this value is changed to a much smaller value in order to avoid long simulation times
     * |        |          |However, this may cause a memory model error, due to a violation of the CKE setup sequence
     * |        |          |This violation is expected if this value is not programmed to the required SDRAM CKE low time, but memory models should be able to tolerate this violation without malfunction of the model.
     * |[28:20] |tDINIT1   |DRAM Initialization Time 1
     * |        |          |DRAM initialization time in DRAM clock cycles corresponding to the following:
     * |        |          |DDR3 = CKE high time to first command (tRFC + 10 ns or 5 tCK, whichever is bigger) DDR2 = CKE high time to first command (400 ns)
     * |        |          |Default value corresponds to DDR3 tRFC of 360ns at 1066 MHz.
     * @var DDRPHY_T::PTR4
     * Offset: 0x2C  PHY Timing Registers 4 (PTR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |tDINIT2   |DRAM Initialization Time 2
     * |        |          |DRAM initialization time in DRAM clock cycles corresponding to the following:
     * |        |          |DDR3 = Reset low time (200 us on power-up or 100 ns after power-up) Default value corresponds to DDR3 200 us at 1066 MHz.
     * |[27:18] |tDINIT3   |DRAM Initialization Time 3
     * |        |          |DRAM initialization time in DRAM clock cycles corresponding to the following:
     * |        |          |DDR3 = Time from ZQ initialization command to first command (1 us) Default value corresponds to the DDR3 640ns at 1066 MHz.
     * @var DDRPHY_T::ACMDLR
     * Offset: 0x30  AC Master Delay Line Register (ACMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::ACBDLR
     * Offset: 0x34  AC Bit Delay Line Register (ACBDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |CK0BD     |CK0 Bit Delay
     * |        |          |Delay select for the BDL on CK0.
     * |[11:6]  |CK1BD     |CK1 Bit Delay
     * |        |          |Delay select for the BDL on CK1.
     * |[17:12] |CK2BD     |CK2 Bit Delay
     * |        |          |Delay select for the BDL on CK2.
     * |[23:18] |ACBD      |Address/Command Bit Delay
     * |        |          |Delay select for the BDLs on address and command signals.
     * @var DDRPHY_T::ACIOCR
     * Offset: 0x38  AC I/O Configuration Register (ACIOCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ACIOM     |Address/Command I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for all address and command pins
     * |        |          |This bit connects to bit [0] of the IOM pin on the D3F I/Os, and for other I/O libraries, it connects to the IOM pin of the I/O.
     * |[1]     |ACOE      |Address/Command Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for all address and command pins.
     * |[2]     |ACODT     |Address/Command On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
     * |[3]     |ACPDD     |AC Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[4]     |ACPDR     |AC Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
     * |[7:5]   |CKODT     |CK On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
     * |[10:8]  |CKPDD     |CK Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[13:11] |CKPDR     |CK Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
     * |[17:14] |RANKODT   |Rank On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for CKE[3:0], ODT[3:0], and CS#[3:0] pins
     * |        |          |RANKODT[0] controls the on-die termination for CKE[0], ODT[0], and CS#[0], RANKODT[1] controls the on-die termination for CKE[1], ODT[1], and CS#[1], and so on.
     * |[21:18] |CSPDD     |CS# Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for CS#[3:0] pins
     * |        |          |CSPDD[0] controls the power down for CS#[0], CSPDD[1] controls the power down for CS#[1], and so on
     * |        |          |CKE and ODT driver power down is controlled by DSGCR register.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[25:22] |RANKPDR   |Rank Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O CKE[3:0], ODT[3:0], and CS#[3:0] pins
     * |        |          |RANKPDR[0] controls the power down for CKE[0], ODT[0], and CS#[0], RANKPDR[1] controls the power down for CKE[1], ODT[1], and CS#[1], and so on.
     * |[26]    |RSTODT    |SDRAM Reset On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for SDRAM RST# pin.
     * |[27]    |RSTPDD    |SDRAM Reset Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for SDRAM RST# pin.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[28]    |RSTPDR    |SDRAM Reset Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for SDRAM RST# pin.
     * |[29]    |RSTIOM    |SDRAM Reset I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for SDRAM Reset.
     * |[31:30] |ACSR      |Address/Command Slew Rate
     * |        |          |Selects slew rate of the I/O for all address and command pins.
     * @var DDRPHY_T::DXCCR
     * Offset: 0x3C  DATX8 Common Configuration Register (DXCCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros
     * |        |          |This bit is ORed with the ODT configuration bit of the individual DATX8 ("DATX8 General Configuration Register (DXnGCR)")
     * |[1]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8.
     * |[2]     |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, all DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or on when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the MDLEN bit in the individual DATX8.
     * |[3]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros
     * |        |          |This bit is ORed with the PDD configuration bit of the individual DATX8.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[4]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros
     * |        |          |This bit is ORed with the PDR configuration bit of the individual DATX8.
     * |[8:5]   |DQSRES    |DQS Resistor
     * |        |          |Selects the on-die pull-down/pull-up resistor for DQS pins
     * |        |          |DQSRES[3] selects pull-down (when set to 0) or pull-up (when set to 1)
     * |        |          |DQSRES[2:0] selects the resistor value.
     * |        |          |Refer PHY databook for pull-down/pull-up resistor values (RA_SEL/RB_SEL) for
     * |        |          |DQS/DQS_b.
     * |[12:9]  |DQSNRES   |DQS# Resistor
     * |        |          |Selects the on-die pull-up/pull-down resistor for DQS# pins. Same encoding as DQSRES.
     * |        |          |Refer PHY databook for pull-down/pull-up resistor values (RA_SEL/RB_SEL) for
     * |        |          |DQS/DQS_b.
     * |[14:13] |DXSR      |Data Slew Rate
     * |        |          |Selects slew rate of the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros.
     * |[17:15] |MSBUDQ    |Most Significant Byte Unused DQs
     * |        |          |Specifies the number of DQ bits that are not used in the most significant byte
     * |        |          |The used (valid) bits for this byte are [8-MSBDQ-1:0]
     * |        |          |To disable the whole byte, use the DXnGCR.DXEN register.
     * |[18]    |UDQODT    |Unused DQ On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for unused DQ pins.
     * |[19]    |UDQPDD    |Unused DQ Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for unused DQ pins.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[20]    |UDQPDR    |Unused DQ Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for unused DQ pins.
     * |[21]    |UDQIOM    |Unused DQ I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for unused DQ pins.
     * |[22]    |DYNDXPDD  |Dynamic Data Power Down Driver
     * |        |          |Dynamically powers down, when set, the output driver on I/O for the DQ pins of the active DATX8 macros
     * |        |          |Applies only when DXPDD and DXnGCR.DXPDD are not set to 1
     * |        |          |Driver is powered-up on a DFI WRITE command and powered-down (twrlat + WL/2 + n) HDR cycles after the last DFI WRITE command
     * |        |          |Note that n is defined by the register bit field DXCCR[27:24] (DDPDDCDO).
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[23]    |DYNDXPDR  |Data Power Down Receiver
     * |        |          |Dynamically powers down, when set, the input receiver on I/O for the DQ pins of the active DATX8 macros
     * |        |          |Applies only when DXPDR and DXnGCR.DXPDR are not set to 1
     * |        |          |Receiver is powered-up on a DFI READ command and powered-down (trddata_en + fixed_read_latency + n) HDR cycles after the last DFI READ command
     * |        |          |Note that n is defined by the register bit field DXCCR[31:28] (DDPDRCDO).
     * |[27:24] |DDPDDCDO  |Dynamic Data Power Down Driver Count Down Offset
     * |        |          |Offset applied in calculating window of time where driver is powered up
     * |[31:28] |DDPDRCDO  |Dynamic Data Power Down Receiver Count Down Offset
     * |        |          |Offset applied in calculating window of time where receiver is powered up
     * @var DDRPHY_T::DSGCR
     * Offset: 0x40  DDR System General Configuration Register(DSGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PUREN     |PHY Update Request Enable
     * |        |          |Specifies if set, that the PHY should issue PHY- initiated update request when there is DDL VT drift.
     * |[1]     |BDISEN    |Byte Disable Enable
     * |        |          |Specifies, if set, that the PHY should respond to DFI byte disable request
     * |        |          |Otherwise the byte disable from the DFI is ignored in which case bytes can only be disabled using the DXnGCR register.
     * |[2]     |ZUEN      |Impedance Update Enable
     * |        |          |Specifies, if set, that in addition to DDL VT update, the PHY could also perform impedance calibration (update).
     * |        |          |Refer to the "Impedance Control Register 0-1 (ZQnCR0-1)" bit fields DFICU0, DFICU1 and DFICCU bits to control if an impedance calibration is performed (update) with a DFI controller update request.
     * |        |          |Refer to the "Impedance Control Register 0-1 (ZQnCR0-1)"D bit fields DFIPU0 and DFIPU1 bits to control if an impedance calibration is performed (update) with a DFI PHY update request.
     * |[3]     |LPIOPD    |Low Power I/O Power Down
     * |        |          |Specifies, if set, that the PHY should respond to the DFI low power opportunity request and power down the I/Os of the byte.
     * |[4]     |LPPLLPD   |Low Power PLL Power Down
     * |        |          |Specifies, if set, that the PHY should respond to the DFI low power opportunity request and power down the PLL of the byte if the wakeup time request satisfies the PLL lock time.
     * |[5]     |CUAEN     |Controller Update Acknowledge Enable
     * |        |          |Specifies, if set, that the PHY should issue controller update acknowledge when the DFI controller update request is asserted
     * |        |          |By default, the PHY does not acknowledge controller initiated update requests but simply does an update whenever there is a controller update request
     * |        |          |This speeds up the update.
     * |[6]     |DQSGX     |DQS Gate Extension
     * |        |          |Specifies, if set, that the DQS gating must be extended by two DRAM clock cycles and then re-centered, i.e
     * |        |          |one clock cycle extension on either side.
     * |[7]     |BRRMODE   |Bypass Rise-to-Rise Mode
     * |        |          |Indicates, if set, that the PHY bypass mode is configured to run in rise-to-rise mode
     * |        |          |Otherwise if not set the PHY bypass mode is running in rise-to-fall mode.
     * |[11:8]  |PUAD      |PHY Update Acknowledge Delay
     * |        |          |Specifies the number of clock cycles that the indication for the completion of PHY update from the PHY to the controller should be delayed
     * |        |          |This essentially delays, by this many clock cycles, the de-assertion of dfi_ctrlup_ack and dfi_phyupd_req signals relative to the time when the delay lines or I/Os are updated.
     * |[12]    |DTOODT    |DTO On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DTO pins.
     * |[13]    |DTOPDD    |DTO Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for DTO pins.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[14]    |DTOPDR    |DTO Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for DTO pins.
     * |[15]    |DTOIOM    |DTO I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DTO pins.
     * |[16]    |DTOOE     |DTO Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for DTO pins.
     * |[17]    |ATOAE     |ATO Analog Test Enable
     * |        |          |Enables, if set, the analog test output (ATO) I/O.
     * |[18]    |RRMODE    |Rise-to-Rise Mode
     * |        |          |Indicates, if set, that the PHY mission mode is configured to run in rise-to-rise mode
     * |        |          |Otherwise if not set the PHY mission mode is running in rise-to- fall mode.
     * |[19]    |SDRMODE   |Single Data Rate Mode
     * |        |          |Indicates, if set, that the external controller is configured to run in single data rate (SDR) mode
     * |        |          |Otherwise if not set the controller is running in half data rate (HDR) mode
     * |        |          |This bit not supported in the current version of the PUB.
     * |[23:20] |CKEPDD    |CKE Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for CKE[3:0] pins
     * |        |          |CKEPDD[0] controls the power down for CKE[0], CKEPDD[1] controls the power down for CKE[1], and so on.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[27:24] |ODTPDD    |ODT Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for ODT[3:0] pins
     * |        |          |ODTPDD[0] controls the power down for ODT[0], ODTPDD[1] controls the power down for ODT[1], and so on.
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[28]    |CKOE      |SDRAM CK Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for SDRAM CK/CK# pins.
     * |[29]    |ODTOE     |SDRAM ODT Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for SDRAM ODT pins.
     * |[30]    |RSTOE     |SDRAM Reset Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for SDRAM RST# pin.
     * |[31]    |CKEOE     |SDRAM CKE Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for SDRAM CKE pins.
     * @var DDRPHY_T::DCR
     * Offset: 0x44  DRAM Configuration Register (DCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |DDRMD     |DDR Mode
     * |        |          |SDRAM DDR mode. Valid values are:
     * |        |          |000 = Reserved
     * |        |          |001 = Reserved
     * |        |          |010 = DDR2
     * |        |          |011 = DDR3
     * |        |          |100 - 111 = Reserved
     * |[3]     |DDR8BNK   |DDR 8-Bank
     * |        |          |Indicates, if set, that the SDRAM used has 8 banks
     * |        |          |tRPA = tRP+1 and tFAW are used for 8-bank DRAMs, otherwise tRPA = tRP and no tFAW is used.
     * |        |          |Note that a setting of 1 for DRAMs that have fewer than 8 banks results in correct functionality, but less tight DRAM command spacing for the parameters.
     * |[6:4]   |PDQ       |Primary DQ
     * |        |          |Specifies the DQ pin in a byte that is designated as a primary pin for Multi-Purpose Register (MPR) reads
     * |        |          |Valid values are 0 to 7 for DQ[0] to DQ[7], respectively.
     * |[7]     |MPRDQ     |Multi-Purpose Register DQ
     * |        |          |Specifies the value that is driven on non-primary DQ pins during MPR reads. Valid values are:
     * |        |          |0 = Primary DQ drives out the data from MPR (0-1-0-1); non-primary DQs drive '0'
     * |        |          |1 = Primary DQ and non-primary DQs all drive the same data from MPR (0-1-0-1)
     * |[17:10] |BYTEMASK  |Byte Mask
     * |        |          |Mask applied to all beats of read data on all byte lanes during read DQS gate training
     * |        |          |This allows training to be conducted based on selected bit(s) from the byte lanes.
     * |        |          |Valid values for each bit are:
     * |        |          |0 = Disable compare for that bit
     * |        |          |1 = Enable compare for that bit
     * |        |          |Note that this mask applies in DDR3 MPR operation mode as well and must be in keeping with the PDQ field setting.
     * |[27]    |NOSRA     |No Simultaneous Rank Access
     * |        |          |Specifies, if set, that simultaneous rank access on the same clock cycle is not allowed
     * |        |          |This means that multiple chip select signals should not be asserted at the same time
     * |        |          |This may be required on some DIMM systems.
     * |[28]    |DDR2T     |DDR 2T Timing
     * |        |          |Indicates, if set, that 2T timing should be used by PUB internally generated SDRAM transactions.
     * |[29]    |UDIMM     |Un-buffered DIMM Address Mirroring
     * |        |          |Indicates, if set, that there is address mirroring on the second rank of an un-buffered DIMM (the rank connected to CS#[1])
     * |        |          |In this case, the PUB re-scrambles the bank and address when sending mode register commands to the second rank
     * |        |          |This only applies to PUB internal SDRAM transactions
     * |        |          |Transactions generated by the controller must make its own adjustments when using an un-buffered DIMM
     * |        |          |DCR[NOSRA] must be set if address mirroring is enabled.
     * @var DDRPHY_T::DTPR0
     * Offset: 0x48  DRAM Timing Parameters Register 0 (DTPR0) 105
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |tRTP      |Internal read to precharge command delay
     * |        |          |Valid values are 2 to 15.
     * |[7:4]   |tWTR      |Internal write to read command delay
     * |        |          |Valid values are 1 to 15.
     * |[11:8]  |tRP       |Precharge command period
     * |        |          |The minimum time between a precharge command and any other command
     * |        |          |Note that the Controller automatically derives tRPA for 8- bank DDR2 devices by adding 1 to tRP
     * |        |          |Valid values are 2 to 15.
     * |[15:12] |tRCD      |Activate to read or write delay
     * |        |          |Minimum time from when an activate command is issued to when a read or write to the activated row can be issued
     * |        |          |Valid values are 2 to 15.
     * |[21:16] |tRAS      |Activate to precharge command delay
     * |        |          |Valid values are 2 to 63.
     * |[25:22] |tRRD      |Activate to activate command delay
     * |        |          |Valid values are 1 to 15.
     * |[31:26] |tRC       |Activate to activate command delay
     * |        |          |Valid values are 2 to 63.
     * @var DDRPHY_T::DTPR1
     * Offset: 0x4C  DRAM Timing Parameters Register 1 (DTPR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |tMRD      |Load mode cycle time
     * |        |          |The minimum time between a load mode register command and any other command
     * |        |          |For DDR3 this is the minimum time between two load mode register commands
     * |        |          |Valid values for DDR2 are 2 to 3
     * |        |          |For DDR3, the value used for tMRD is 4 plus the value programmed in these bits, i.e
     * |        |          |tMRD value for DDR3 ranges from 4 to 7.
     * |[4:2]   |tMOD      |Load mode update delay
     * |        |          |The minimum time between a load mode register command and a non-load mode register command
     * |        |          |Valid values are:
     * |        |          |000 = 12
     * |        |          |001 = 13
     * |        |          |010 = 14
     * |        |          |011 = 15
     * |        |          |100 = 16
     * |        |          |101 = 17
     * |        |          |110 - 111 = Reserved
     * |[10:5]  |tFAW      |4-bank activate period
     * |        |          |No more than 4-bank activate commands may be issued in a given tFAW period
     * |        |          |Only applies to 8-bank devices
     * |        |          |Valid values are 2 to 63.
     * |[19:11] |tRFC      |Refresh-to-Refresh
     * |        |          |Indicates the minimum time between two refresh commands or between a refresh and an active command
     * |        |          |This is derived from the minimum refresh interval from the Datasheet, tRFC(min), divided by the clock cycle time
     * |        |          |The default number of clock cycles is for the largest JEDEC tRFC(min parameter value supported.
     * |[25:20] |tWLMRD    |Minimum delay from when write leveling mode is programmed to the first
     * |        |          |DQS/DQS# rising edge.
     * |[29:26] |tWLO      |Write leveling output delay
     * |        |          |Number of clock cycles from when write leveling DQS is driven high by the control block to when the results from the SDRAM on DQ is sampled by the control block
     * |        |          |This must include the SDRAM tWLO timing parameter plus the round trip delay from control block to SDRAM back to control block.
     * |[31:30] |tAONDtAOFD|ODT turn-on/turn-off delays.
     * |        |          |Valid values are:
     * |        |          |00 = 2/2.5
     * |        |          |01 = 3/3.5
     * |        |          |10 = 4/4.5
     * |        |          |11 = 5/5.5
     * |        |          |Most DDR2 devices utilize a fixed value of 2/2.5
     * |        |          |For non-standard SDRAMs, the user must ensure that the operational Write Latency is always greater than or equal to the ODT turn-on delay
     * |        |          |For example, a DDR2 SDRAM with CAS latency set to 3 and CAS additive latency set to 0 has a Write Latency of 2
     * |        |          |Thus 2/2.5 can be used, but not 3/3.5 or higher.
     * @var DDRPHY_T::DTPR2
     * Offset: 0x50  DRAM Timing Parameters Register 2 (DTPR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |tXS       |Self refresh exit delay
     * |        |          |The minimum time between a self refresh exit command and any other command
     * |        |          |This parameter must be set to the maximum of the various minimum self refresh exit delay parameters specified in the SDRAM Datasheet, i.e
     * |        |          |max(tXSNR, tXSRD) for DDR2 and max(tXS, tXSDLL) for DDR3
     * |        |          |Valid values are 2 to
     * |        |          |1023.
     * |[14:10] |tXP       |Power down exit delay
     * |        |          |The minimum time between a power down exit command and any other command
     * |        |          |This parameter must be set to the maximum of the various minimum power down exit delay parameters specified in the SDRAM Datasheet, i.e
     * |        |          |max(tXP, tXARD, tXARDS) for DDR2 and max(tXP, tXPDLL) for DDR3
     * |        |          |Valid values are 2 to 31.
     * |[18:15] |tCKE      |CKE minimum pulse width
     * |        |          |Also specifies the minimum time that the SDRAM must remain in power down or self refresh mode
     * |        |          |For DDR3 this parameter must be set to the value of tCKESR which is usually bigger than the value of tCKE
     * |        |          |Valid values are 2 to 15.
     * |[28:19] |tDLLK     |DLL locking time
     * |        |          |Valid values are 2 to 1023.
     * |[29]    |tRTODT    |Read to ODT delay
     * |        |          |Specifies whether ODT can be enabled immediately after the read post-amble or one clock delay has to be added
     * |        |          |Valid values are:
     * |        |          |0 = ODT may be turned on immediately after read post-amble
     * |        |          |1 = ODT may not be turned on until one clock after the read post-amble
     * |        |          |If tRTODT is set to 1, then the read-to-write latency is increased by 1 if ODT is enabled.
     * |[30]    |tRTW      |Read to Write command delay
     * |        |          |Valid values are:
     * |        |          |0 = standard bus turn around delay
     * |        |          |1 = add 1 clock to standard bus turn around delay
     * |        |          |This parameter allows the user to increase the delay between issuing Write commands to the SDRAM when preceded by Read commands
     * |        |          |This provides an option to increase bus turn-around margin for high frequency systems.
     * |[31]    |tCCD      |Read to read and write to write command delay
     * |        |          |Valid values are:
     * |        |          |0 = BL/2 for DDR2 and 4 for DDR3
     * |        |          |1 = BL/2 + 1 for DDR2 and 5 for DDR3
     * @var DDRPHY_T::MR0
     * Offset: 0x54  Mode Register 0 (MR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |BL        |Burst Length
     * |        |          |Determines the maximum number of column locations that can be accessed during a given read or write command
     * |        |          |Valid values are:
     * |        |          |Valid values for DDR3 are:
     * |        |          |00 = 8 (Fixed)
     * |        |          |01 = 4 or 8 (On the fly)
     * |        |          |10 = 4 (Fixed)
     * |        |          |11 = Reserved
     * |[2]     |CL0       |CAS Latency
     * |        |          |The delay between when the SDRAM registers a read command to when data is available. Valid values are:
     * |        |          |0010 = 5
     * |        |          |0100 = 6
     * |        |          |0110 = 7
     * |        |          |1000 = 8
     * |        |          |1010 = 9
     * |        |          |1100 = 10
     * |        |          |1110 = 11
     * |        |          |0001 = 12
     * |        |          |0011 = 13
     * |        |          |0101 = 14
     * |        |          |All other settings are reserved and should not be used.
     * |[3]     |BT        |Burst Type
     * |        |          |Indicates whether a burst is sequential (0) or interleaved (1).
     * |[6:4]   |CL1       |CAS Latency
     * |        |          |The delay between when the SDRAM registers a read command to when data is available. Valid values are:
     * |        |          |0010 = 5
     * |        |          |0100 = 6
     * |        |          |0110 = 7
     * |        |          |1000 = 8
     * |        |          |1010 = 9
     * |        |          |1100 = 10
     * |        |          |1110 = 11
     * |        |          |0001 = 12
     * |        |          |0011 = 13
     * |        |          |0101 = 14
     * |        |          |All other settings are reserved and should not be used.
     * |[7]     |TM        |Operating Mode
     * |        |          |Selects either normal operating mode (0) or test mode (1)
     * |        |          |Test mode is reserved for the manufacturer and should not be used.
     * |[8]     |DR        |DLL Reset
     * |        |          |Writing a '1' to this bit will reset the SDRAM DLL
     * |        |          |This bit is self- clearing, i.e
     * |        |          |it returns back to '0' after the DLL reset has been issued.
     * |[11:9]  |WR        |Write Recovery
     * |        |          |This is the value of the write recovery
     * |        |          |It is calculated by dividing the Datasheet write recovery time, tWR (ns) by the Datasheet clock cycle time, tCK (ns) and rounding up a non-integer value to the next integer
     * |        |          |Valid values are:
     * |        |          |000 = 16
     * |        |          |001 = 5
     * |        |          |010 = 6
     * |        |          |011 = 7
     * |        |          |100 = 8
     * |        |          |101 = 10
     * |        |          |110 = 12
     * |        |          |111 = 14
     * |        |          |All other settings are reserved and should not be used.
     * |        |          |Note: tWR (ns) is the time from the first SDRAM positive clock edge after the last data-in pair of a write command, to when a precharge of the same bank can be issued.
     * |[12]    |PD        |Power-Down Control
     * |        |          |Controls the exit time for power-down modes
     * |        |          |Refer to the SDRAM Datasheet for details on power-down modes
     * |        |          |Valid values are:
     * |        |          |0 = Slow exit (DLL off)
     * |        |          |1 = Fast exit (DLL on)
     * @var DDRPHY_T::MR1
     * Offset: 0x58  Mode Register 1 (MR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DE        |DLL Enable/Disable
     * |        |          |Enable (0) or disable (1) the DLL. DLL must be enabled for normal operation.
     * |        |          |Note: SDRAM DLL off mode is not supported
     * |[1]     |DIC0      |Output Driver Impedance Control
     * |        |          |Controls the output drive strength. Valid values are:
     * |        |          |00 = RZQ/6
     * |        |          |01 = RZQ7
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[2]     |RTT0      |On Die Termination
     * |        |          |Selects the effective resistance for SDRAM on die termination. Valid values are:
     * |        |          |000 = ODT disabled
     * |        |          |001 = RZQ/4
     * |        |          |010 = RZQ/2
     * |        |          |011 = RZQ/6
     * |        |          |100 = RZQ/12
     * |        |          |101 = RZQ/8
     * |        |          |All other settings are reserved and should not be used.
     * |[4:3]   |AL        |Posted CAS Additive Latency
     * |        |          |Setting additive latency that allows read and write commands to be issued to the SDRAM earlier than normal (refer to the SDRAM Datasheet for details)
     * |        |          |Valid values are:
     * |        |          |00 = 0 (AL disabled)
     * |        |          |01 = CL - 1
     * |        |          |10 = CL - 2
     * |        |          |11 = Reserved
     * |[5]     |DIC1      |Output Driver Impedance Control
     * |        |          |Controls the output drive strength. Valid values are:
     * |        |          |00 = RZQ/6
     * |        |          |01 = RZQ7
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[6]     |RTT1      |On Die Termination
     * |        |          |Selects the effective resistance for SDRAM on die termination. Valid values are:
     * |        |          |000 = ODT disabled
     * |        |          |001 = RZQ/4
     * |        |          |010 = RZQ/2
     * |        |          |011 = RZQ/6
     * |        |          |100 = RZQ/12
     * |        |          |101 = RZQ/8
     * |        |          |All other settings are reserved and should not be used.
     * |[7]     |LEVEL     |Write Leveling Enable
     * |        |          |Enables write-leveling when set.
     * |[9]     |RTT2      |On Die Termination
     * |        |          |Selects the effective resistance for SDRAM on die termination. Valid values are:
     * |        |          |000 = ODT disabled
     * |        |          |001 = RZQ/4
     * |        |          |010 = RZQ/2
     * |        |          |011 = RZQ/6
     * |        |          |100 = RZQ/12
     * |        |          |101 = RZQ/8
     * |        |          |All other settings are reserved and should not be used.
     * |[11]    |TDQS      |Termination Data Strobe
     * |        |          |When enabled ('1') TDQS provides additional termination resistance outputs that may be useful in some system configurations
     * |        |          |Refer to the SDRAM Datasheet for details.
     * |[12]    |QOFF      |Output Enable/Disable
     * |        |          |When '0', all outputs function normal; when '1' all SDRAM outputs are disabled removing output buffer current
     * |        |          |This feature is intended to be used for IDD characterization of read current and should not be used in normal operation.
     * @var DDRPHY_T::MR2
     * Offset: 0x5C  Mode Register 2/Extended Mode Register 2 (MR2/EMR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |PASR      |Partial Array Self Refresh
     * |        |          |Specifies that data located in areas of the array beyond the specified location will be lost if self refresh is entered.
     * |        |          |Valid settings for 4 banks are:
     * |        |          |000 = Full Array
     * |        |          |001 = Half Array (BA[1:0] = 00 & 01)
     * |        |          |010 = Quarter Array (BA[1:0] = 00)
     * |        |          |011 = Not defined
     * |        |          |100 = 3/4 Array (BA[1:0] = 01, 10, & 11)
     * |        |          |101 = Half Array (BA[1:0] = 10 & 11)
     * |        |          |110 = Quarter Array (BA[1:0] = 11)
     * |        |          |111 = Not defined
     * |        |          |Valid settings for 8 banks are:
     * |        |          |000 = Full Array
     * |        |          |001 = Half Array (BA[2:0] = 000, 001, 010 & 011)
     * |        |          |010 = Quarter Array (BA[2:0] = 000, 001)
     * |        |          |011 = 1/8 Array (BA[2:0] = 000)
     * |        |          |100 = 3/4 Array (BA[2:0] = 010, 011, 100, 101, 110 & 111)
     * |        |          |101 = Half Array (BA[2:0] = 100, 101, 110 & 111)
     * |        |          |110 = Quarter Array (BA[2:0] = 110 & 111)
     * |        |          |111 = 1/8 Array (BA[2:0] 111)
     * |[5:3]   |CWL       |CAS Write Latency
     * |        |          |The delay between when the SDRAM registers a write command to when write data is available
     * |        |          |Valid values are:
     * |        |          |000 = 5 (tCK > 2.5ns)
     * |        |          |001 = 6 (2.5ns > tCK > 1.875ns)
     * |        |          |010 = 7 (1.875ns > tCK> 1.5ns)
     * |        |          |011 = 8 (1.5ns > tCK > 1.25ns)
     * |        |          |100 = 9 (1.25ns > tCK > 1.07ns)
     * |        |          |101 = 10 (1.07ns > tCK > 0.935ns)
     * |        |          |110 = 11 (0.935ns > tCK > 0.833ns)
     * |        |          |111 = 12 (0.833ns > tCK > 0.75ns)
     * |        |          |All other settings are reserved and should not be used.
     * |[6]     |ASR       |Auto Self-Refresh
     * |        |          |When enabled ('1'), SDRAM automatically provides self-refresh power management functions for all supported operating temperature values
     * |        |          |Otherwise the SRT bit must be programmed to indicate the temperature range.
     * |[7]     |SRT       |Self-Refresh Temperature Range
     * |        |          |Selects either normal ('0') or extended ('1') operating temperature range during self-refresh.
     * |[10:9]  |RTTWR     |Dynamic ODT
     * |        |          |Selects RTT for dynamic ODT. Valid values are:
     * |        |          |00 = Dynamic ODT off
     * |        |          |01 = RZQ/4
     * |        |          |10 = RZQ/2
     * |        |          |11 = Reserved
     * @var DDRPHY_T::MR3
     * Offset: 0x60  Mode Register 3 (MR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |MPRLOC    |Multi-Purpose Register Location
     * |        |          |Selects MPR data location: Valid value are:
     * |        |          |00 = Predefined pattern for system calibration
     * |        |          |All other settings are reserved and should not be used.
     * |[2]     |MPR       |Multi-Purpose Register Enable
     * |        |          |Enables, if set, that read data should come from the Multi-Purpose Register
     * |        |          |Otherwise read data come from the DRAM array.
     * @var DDRPHY_T::ODTCR
     * Offset: 0x64  ODT Configuration Register (ODTCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |RDODT0    |Write ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a write command is sent to rank n
     * |        |          |WRODT0, WRODT1, WRODT2, and WRODT3 specify ODT settings when a write is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to enable ODT only on rank being written to.
     * |[7:4]   |RDODT1    |Write ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a write command is sent to rank n
     * |        |          |WRODT0, WRODT1, WRODT2, and WRODT3 specify ODT settings when a write is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to enable ODT only on rank being written to.
     * |[11:8]  |RDODT2    |Write ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a write command is sent to rank n
     * |        |          |WRODT0, WRODT1, WRODT2, and WRODT3 specify ODT settings when a write is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to enable ODT only on rank being written to.
     * |[15:12] |RDODT3    |Write ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a write command is sent to rank n
     * |        |          |WRODT0, WRODT1, WRODT2, and WRODT3 specify ODT settings when a write is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to enable ODT only on rank being written to.
     * |[19:16] |WRODT0    |Read ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a read command is sent to rank n
     * |        |          |RDODT0, RDODT1, RDODT2, and RDODT3 specify ODT settings when a read is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to disable ODT during reads
     * |[23:20] |WRODT1    |Read ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a read command is sent to rank n
     * |        |          |RDODT0, RDODT1, RDODT2, and RDODT3 specify ODT settings when a read is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to disable ODT during reads
     * |[27:24] |WRODT2    |Read ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a read command is sent to rank n
     * |        |          |RDODT0, RDODT1, RDODT2, and RDODT3 specify ODT settings when a read is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to disable ODT during reads
     * |[31:28] |WRODT3    |Read ODT
     * |        |          |Specifies whether ODT should be enabled ('1') or disabled ('0') on each of the up to four ranks when a read command is sent to rank n
     * |        |          |RDODT0, RDODT1, RDODT2, and RDODT3 specify ODT settings when a read is to rank 0, rank 1, rank 2, and rank 3, respectively
     * |        |          |The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3
     * |        |          |Default is to disable ODT during reads
     * @var DDRPHY_T::DTCR
     * Offset: 0x68  Data Training Configuration Register (DTCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |DTCOL     |Data Training Column Address
     * |        |          |Selects the SDRAM column address to be used during data training
     * |        |          |The lower four bits of this address must always be "000".
     * |[27:12] |DTROW     |Data Training Row Address
     * |        |          |Selects the SDRAM row address to be used during data training.
     * |[30:28] |DTBANK    |Data Training Bank Address
     * |        |          |Selects the SDRAM bank address to be used during data training.
     * @var DDRPHY_T::DTAR0
     * Offset: 0x6C  Data Training Address Register 0 (DTAR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var DDRPHY_T::DTAR1
     * Offset: 0x70  Data Training Address Register 1 (DTAR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |DTCOL     |Data Training Column Address
     * |        |          |Selects the SDRAM column address to be used during data training
     * |        |          |The lower four bits of this address must always be "000".
     * |[27:12] |DTROW     |Data Training Row Address
     * |        |          |Selects the SDRAM row address to be used during data training.
     * |[30:28] |DTBANK    |Data Training Bank Address
     * |        |          |Selects the SDRAM bank address to be used during data training.
     * @var DDRPHY_T::DTAR2
     * Offset: 0x74  Data Training Address Register 2 (DTAR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |DTCOL     |Data Training Column Address
     * |        |          |Selects the SDRAM column address to be used during data training
     * |        |          |The lower four bits of this address must always be "000".
     * |[27:12] |DTROW     |Data Training Row Address
     * |        |          |Selects the SDRAM row address to be used during data training.
     * |[30:28] |DTBANK    |Data Training Bank Address
     * |        |          |Selects the SDRAM bank address to be used during data training.
     * @var DDRPHY_T::DTAR3
     * Offset: 0x78  Data Training Address Register 3 (DTAR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |DTCOL     |Data Training Column Address
     * |        |          |Selects the SDRAM column address to be used during data training
     * |        |          |The lower four bits of this address must always be "000".
     * |[27:12] |DTROW     |Data Training Row Address
     * |        |          |Selects the SDRAM row address to be used during data training.
     * |[30:28] |DTBANK    |Data Training Bank Address
     * |        |          |Selects the SDRAM bank address to be used during data training.
     * @var DDRPHY_T::DTDR0
     * Offset: 0x7C  Data Training Data Register 0 (DTDR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DTBYTE1   |Data Training Data
     * |        |          |The first 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[15:8]  |DTBYTE0   |Data Training Data
     * |        |          |The first 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[23:16] |DTBYTE2   |Data Training Data
     * |        |          |The first 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[31:24] |DTBYTE3   |Data Training Data
     * |        |          |The first 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * @var DDRPHY_T::DTDR1
     * Offset: 0x80  Data Training Data Register 1 (DTDR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DTBYTE4   |Data Training Data
     * |        |          |The second 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[15:8]  |DTBYTE5   |Data Training Data
     * |        |          |The second 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[23:16] |DTBYTE6   |Data Training Data
     * |        |          |The second 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * |[31:24] |DTBYTE7   |Data Training Data
     * |        |          |The second 4 bytes of data used during data training
     * |        |          |This same data byte is used for each Byte Lane
     * |        |          |Default sequence is a walking 1 while toggling data every data cycle.
     * @var DDRPHY_T::DTEDR0
     * Offset: 0x84  Data Training Eye Data Register 0 (DTEDR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DTWLMN    |Data Training WDQ LCDL Minimum.
     * |[15:8]  |DTWLMX    |Data Training WDQ LCDL Maximum.
     * |[23:16] |DTWBMN    |Data Training Write BDL Shift Minimum.
     * |[31:24] |DTWBMX    |Data Training Write BDL Shift Maximum.
     * @var DDRPHY_T::DTEDR1
     * Offset: 0x88  Data Training Eye Data Register 1 (DTEDR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DTRLMN    |Data Training RDQS LCDL Minimum.
     * |[15:8]  |DTRLMX    |Data Training RDQS LCDL Maximum.
     * |[23:16] |DTRBMN    |Data Training Read BDL Shift Minimum.
     * |[31:24] |DTRBMX    |Data Training Read BDL Shift Maximum.
     * @var DDRPHY_T::PGCR2
     * Offset: 0x8C  PHY General Configuration Register 2 (PGCR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |tREFPRD   |Refresh Period
     * |        |          |Indicates the period, after which the PUB has to issue a refresh command to the SDRAM
     * |        |          |This is derived from the maximum refresh interval from the Datasheet, tRFC(max) or REFI, divided by the clock cycle time
     * |        |          |A further 400 clocks must be subtracted from the derived number to account for command flow and missed slots of refreshes in the internal PUB blocks
     * |        |          |The default corresponds to DDR3 9*7.8us at 1066 MHz when a burst of 9 refreshes are issued at every refresh interval.
     * |[18]    |NOBUB     |No Bubbles
     * |        |          |Specified whether reads should be returned to the controller with no bubbles
     * |        |          |Enabling no-bubble reads increases the read latency
     * |        |          |Valid values are:
     * |        |          |0 = Bubbles are allowed during reads
     * |        |          |1 = Bubbles are not allowed during reads
     * |[19]    |FXDLAT    |Fixed Latency
     * |        |          |Specified whether all reads should be returned to the controller with a fixed read latency
     * |        |          |Enabling fixed read latency increases the read latency
     * |        |          |Valid values are:
     * |        |          |0 = Disable fixed read latency
     * |        |          |1 = Enable fixed read latency
     * |        |          |Fixed read latency is calculated as (12 + (maximum DXnGTR.RxDGSL)/2) HDR
     * |        |          |clock cycles
     * |[27:20] |DTPMXTMR  |Data Training PUB Mode Timer Exit
     * |        |          |Specifies the number of controller clocks to wait when entering and exiting pub mode data training
     * |        |          |The default value ensures controller refreshes do not cause memory model errors when entering and exiting data training
     * |        |          |The value should be increased if controller initiated SDRAM ZQ short or long operation may occur just before or just after the execution of data training.
     * |[28]    |SHRAC     |Shared-AC mode
     * |        |          |Set to 1 to enable shared address/command mode with two independent data channels - available only if shared address/command mode support is compiled in.
     * |[29]    |ACPDDC    |AC Power-Down with Dual Channels
     * |        |          |Set to 1 to power-down address/command lane when both data channels are powered-down
     * |        |          |Only valid in shared-AC mode.
     * |[30]    |LPMSTRC0  |Low-Power Master Channel 0
     * |        |          |Set to 1 to have channel 0 act as master to drive channel 1 low-power functions simultaneously
     * |        |          |Only valid in shared-AC mode.
     * |[31]    |DYNACPDD  |Dynamic AC Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for ADDR and BA
     * |        |          |This bit is ORed with bit ACIOCR[3] (ACPDD).
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * @var DDRPHY_T::RDIMMGCR0
     * Offset: 0xB0  RDIMM General Configuration Register 0 (RDIMMGCR0)  123
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDIMM     |Registered DIMM
     * |        |          |Indicates, if set, that a registered DIMM is used
     * |        |          |In this case, the PUB increases the SDRAM write and read latencies (WL/RL) by 1 and also enforces that accesses adhere to RDIMM buffer chip
     * |        |          |This only applies to PUB internal SDRAM transactions
     * |        |          |Transactions generated by the controller must make its own adjustments to WL/RL when using a registered DIMM
     * |        |          |The DCR.NOSRA register bit must be set to '1' if using the standard RDIMM buffer chip so that normal DRAM accesses do not assert multiple chip select bits at the same time.
     * |[1]     |ERRNOREG  |Parity Error No Registering
     * |        |          |Indicates, if set, that parity error signal from the RDIMM should be passed to the DFI controller without any synchronization or registering
     * |[2]     |SOPERR    |Stop On Parity Error
     * |        |          |Indicates, if set, that the PUB is to stop driving commands to the DRAM upon encountering a parity error
     * |        |          |Transactions can resume only after status is cleared via PIR.CLRSR.
     * |[14]    |PARINODT  |PAR_IN On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for PAR_IN pin.
     * |[15]    |PARINPDD  |PAR_IN Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for PAR_IN pin.
     * |[16]    |PARINPDR  |PAR_IN Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for PAR_IN pin.
     * |[17]    |PARINIOM  |PAR_IN I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for PAR_IN pin.
     * |[18]    |PARINOE   |PAR_IN Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for PAR_IN pin.
     * |[19]    |ERROUTODT |ERROUT# On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for ERROUT# pin.
     * |[20]    |ERROUTPDD |ERROUT# Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for ERROUT# pin.
     * |[21]    |ERROUTPDR |ERROUT# Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for ERROUT# pin.
     * |[22]    |ERROUTIOM |ERROUT# I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for ERROUT# pin.
     * |[23]    |ERROUTOE  |ERROUT# Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for ERROUT# pin.
     * |[24]    |RDIMMODT  |RDIMM Outputs On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for QCSEN# and MIRROR pins.
     * |[25]    |RDIMMPDD  |RDIMM Outputs Power Down Driver
     * |        |          |Powers down, when set, the output driver on the I/O for QCSEN# and MIRROR pins.
     * |[26]    |RDIMMPDR  |RDIMM Outputs Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on the I/O for QCSEN# and MIRROR pins.
     * |[27]    |RDIMMIOM  |RDIMM Outputs I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for QCSEN# and MIRROR pins.
     * |[28]    |QCSENOE   |QCSEN# Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for QCSEN# pin.
     * |[29]    |MIRROROE  |MIRROR Output Enable
     * |        |          |Enables, when set, the output driver on the I/O for MIRROR pin.
     * |[30]    |QCSEN     |RDMIMM Quad CS Enable
     * |        |          |Enables, if set, the Quad CS mode for the RDIMM registering buffer chip
     * |        |          |This register bit controls the buffer chip QCSEN# signal.
     * |[31]    |MIRROR    |RDIMM Mirror
     * |        |          |Selects between two different ballouts of the RDIMM buffer chip for front or back operation
     * |        |          |This register bit controls the buffer chip MIRROR signal.
     * @var DDRPHY_T::RDIMMGCR1
     * Offset: 0xB4  RDIMM General Configuration Register 1 (RDIMMGCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |tBCSTAB   |Stabilization time
     * |        |          |Number of DRAM clock cycles for the RDIMM buffer chip to stabilize
     * |        |          |This parameter corresponds to the buffer chip tSTAB parameter
     * |        |          |Default value is in decimal format and corresponds to 6us at 533 MHz.
     * |[14:12] |tBCMRD    |Command word to command word programming delay
     * |        |          |Number of DRAM clock cycles between two RDIMM buffer chip command programming accesses
     * |        |          |The value used for tBCMRD is 8 plus the value programmed in these bits, i.e
     * |        |          |tBCMRD value ranges from 8 to 15
     * |        |          |This parameter corresponds to the buffer chip tMRD parameter.
     * |[31:16] |CRINIT    |Control Registers Initialization Enable
     * |        |          |Indicates which RDIMM buffer chip control registers (RC0 to RC15) should be initialized (written) when the PUB is triggered to initialize the buffer chip
     * |        |          |A setting of '1' on CRINIT[n] bit means that CRn should be written during initialization.
     * @var DDRPHY_T::RDIMMCR0
     * Offset: 0xB8  RDIMM Control Register 0 (RDIMMCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |RC0       |Control Word 0
     * |        |          |Bit definitions are:
     * |        |          |RC0[0]: 0 = Output inversion enabled, 1 = Output inversion disabled.
     * |        |          |RC0[1]: 0 = Floating outputs disabled, 1 = Floating outputs enabled.
     * |        |          |RC0[2]: 0 = A outputs enabled, 1 = A outputs disabled.
     * |        |          |RC0[3]: 0 = B outputs enabled, 1 = B outputs disabled.
     * |[7:4]   |RC1       |Control Word 1
     * |        |          |Bit definitions are:
     * |        |          |RC1[0]: 0 = Y0/Y0# clock enabled, 1 = Y0/Y0# clock disabled.
     * |        |          |RC1[1]: 0 = Y1/Y1# clock enabled, 1 = Y1/Y1# clock disabled.
     * |        |          |RC1[2]: 0 = Y2/Y2# clock enabled, 1 = Y2/Y2# clock disabled.
     * |        |          |RC1[3]: 0 = Y3/Y3# clock enabled, 1 = Y3/Y3# clock disabled.
     * |[11:8]  |RC2       |Control Word 2
     * |        |          |Bit definitions are:
     * |        |          |RC2[0]: 0 = Standard (1/2 clock) pre-launch, 1 = Prelaunch controlled by RC1.
     * |        |          |RC2[1]: 0 = Reserved.
     * |        |          |RC2[2]: 0 = 100 Ohm input bus termination, 1 = 150 Ohm input bus termination.
     * |        |          |RC2[3]: 0 = Operation frequency band 1, 1 = Test mode frequency band 2.
     * |[15:12] |RC3       |Control Word 3
     * |        |          |RC3[1:0] is driver settings for command/address A outputs, and RC3[3:2] is driver settings for command/address B outputs
     * |        |          |Bit definitions are:
     * |        |          |00 = Light drive (4 or 5 DRAM loads)
     * |        |          |01 = Moderate drive (8 or 10 DRAM loads)
     * |        |          |10 = Strong drive (16 or 20 DRAM loads)
     * |        |          |11 = Reserved
     * |[19:16] |RC4       |Control Word 4
     * |        |          |RC4[1:0] is driver settings for control A outputs, and RC4[3:2] is driver settings for control B outputs
     * |        |          |Bit definitions are:
     * |        |          |00 = Light drive (4 or 5 DRAM loads)
     * |        |          |01 = Moderate drive (8 or 10 DRAM loads)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[23:20] |RC5       |Control Word 5
     * |        |          |RC5[1:0] is driver settings for clock Y1, Y1#, Y3, and Y3# outputs, and RC5[3:2] is driver settings for clock Y0, Y0#, Y2, and Y2# outputs
     * |        |          |Bit definitions are:
     * |        |          |00 = Light drive (4 or 5 DRAM loads)
     * |        |          |01 = Moderate drive (8 or 10 DRAM loads)
     * |        |          |10 = Strong drive (16 or 20 DRAM loads)
     * |        |          |11 = Reserved
     * |[27:24] |RC6       |Control Word 6
     * |        |          |Reserved, free to use by vendor.
     * |[31:28] |RC7       |Control Word 7
     * |        |          |Reserved, free to use by vendor.
     * @var DDRPHY_T::RDIMMCR1
     * Offset: 0xBC  RDIMM Control Register 1 (RDIMMCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |RC8       |Control Word 8
     * |        |          |RC8[2:0] is Input Bus Termination (IBT) setting as follows:
     * |        |          |000 = IBT as defined in RC2.
     * |        |          |001 = Reserved
     * |        |          |010 = 200 Ohm
     * |        |          |011 = Reserved
     * |        |          |100 = 300 Ohm
     * |        |          |101 = Reserved
     * |        |          |110 = Reserved
     * |        |          |111 = Off
     * |        |          |RC8[3]: 0 = IBT off when MIRROR is HIGH, 1 = IBT on when MIRROR is high
     * |[7:4]   |RC9       |Control Word 9
     * |        |          |Bit definitions are:
     * |        |          |RC9[0]: 0 = Floating outputs as defined in RC0, 1 = Weak drive enabled.
     * |        |          |RC9[1]: 0 = Reserved.
     * |        |          |RC9[2]: 0 = CKE power down with IBT ON, QxODT is a function of DxODT, 1 = CKE power down with IBT off, QxODT held LOW
     * |        |          |RC9[2] is valid only when RC9[3] is 1.
     * |        |          |RC9[3]: 0 = CKE Power-down mode disabled, 1 = CKE Power-down mode enabled.
     * |[11:8]  |RC10      |Control Word 10
     * |        |          |RC10[2:0] is RDIMM operating speed setting as follows:
     * |        |          |000 = DDR3/DDR3L-800
     * |        |          |001 = DDR3/DDR3L-1066
     * |        |          |010 = DDR3/DDR3L-1333
     * |        |          |011 = DDR3/DDR3L-1600
     * |        |          |100 = Reserved
     * |        |          |101 = Reserved
     * |        |          |110 = Reserved
     * |        |          |111 = Reserved
     * |        |          |RC10[3]: Don't care.
     * |[15:12] |RC11      |Control Word 11
     * |        |          |RC10[1:0] is VDD operating voltage setting as follows:
     * |        |          |00 = DDR3 1.5V mode
     * |        |          |01 = DDR3L 1.35V mode
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |        |          |RC10[3:2]: Reserved.
     * |[19:16] |RC12      |Control Word 12
     * |        |          |Reserved for future use.
     * |[23:20] |RC13      |Control Word 13
     * |        |          |Reserved for future use.
     * |[27:24] |RC14      |Control Word 14
     * |        |          |Reserved for future use
     * |[31:28] |RC15      |Control Word 15
     * |        |          |Reserved for future use
     * @var DDRPHY_T::DCUAR
     * Offset: 0xC0  DCU Address Register (DCUAR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |CWADDR    |Cache Word Address
     * |        |          |Address of the cache word to be accessed.
     * |[7:4]   |CSADDR    |Cache Slice Address
     * |        |          |Address of the cache slice to be accessed.
     * |[9:8]   |CSEL      |Cache Select
     * |        |          |Selects the cache to be accessed. Valid values are:
     * |        |          |00 = Command cache
     * |        |          |01 = Expected data cache
     * |        |          |10 = Read data cache
     * |        |          |11 = Reserved
     * |[10]    |INCA      |Increment Address
     * |        |          |Specifies, if set, that the cache address specified in WADDR and SADDR should be automatically incremented after each access of the cache
     * |        |          |The increment happens in such a way that all the slices of a selected word are first accessed before going to the next word.
     * |[11]    |ATYPE     |Access Type
     * |        |          |Specifies the type of access to be performed using this address. Valid values are:
     * |        |          |0 = Write access
     * |        |          |1 = Read access
     * @var DDRPHY_T::DCUDR
     * Offset: 0xC4  DCU Data Register (DCUDR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CDATA     |Cache Data
     * |        |          |Data to be written to or read from a cache
     * |        |          |This data corresponds to the cache word slice specified by the DCU Address Register.
     * @var DDRPHY_T::DCURR
     * Offset: 0xC8  DCU Run Register (DCURR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DINST     |DCU Instruction
     * |        |          |Selects the DCU command to be executed: Valid values are:
     * |        |          |0000 = NOP: No operation
     * |        |          |0001 = Run: Triggers the execution of commands in the command cache.
     * |        |          |0010 = Stop: Stops the execution of commands in the command cache.
     * |        |          |0011 = Stop Loop: Stops the execution of an infinite loop in the command cache.
     * |        |          |0100 = Reset: Resets all DCU run time registers. See "DCU Status" for details.
     * |        |          |0101 - 1111 Reserved
     * |[7:4]   |SADDR     |Start Address
     * |        |          |Cache word address where the execution of commands should begin.
     * |[11:8]  |EADDR     |End Address
     * |        |          |Cache word address where the execution of command should end.
     * |[19:12] |NFAIL     |Number of Failures
     * |        |          |Specifies the number of failures after which the execution of commands and the capture of read data should stop if SONF bit of this register is set
     * |        |          |Execution of commands and the capture of read data will stop after (NFAIL+1) failures if SONF is set.
     * |        |          |Valid values are from 0 to 254.
     * |[20]    |SONF      |Stop On Nth Fail
     * |        |          |Specifies, if set, that the execution of commands and the capture of read data should stop when there are N read data failures
     * |        |          |The number of failures is specified by NFAIL
     * |        |          |Otherwise commands execute until the end of the program or until manually stopped using a STOP command.
     * |[21]    |SCOF      |Stop Capture On Full
     * |        |          |Specifies, if set, that the capture of read data should stop when the capture cache is full.
     * |[22]    |RCEN      |Read Capture Enable
     * |        |          |Indicates, if set, that read data coming back from the SDRAM should be captured into the read data cache.
     * |[23]    |XCEN      |Expected Compare Enable
     * |        |          |Indicates, if set, that read data coming back from the SDRAM should be should be compared with the expected data.
     * @var DDRPHY_T::DCULR
     * Offset: 0xCC  DCU Loop Register (DCULR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |LSADDR    |Loop Start Address
     * |        |          |Command cache word address where the loop should start.
     * |[7:4]   |LEADDR    |Loop End Address
     * |        |          |Command cache word address where the loop should end.
     * |[15:8]  |LCNT      |Loop Count
     * |        |          |The number of times that the loop should be executed if LINF is not set.
     * |[16]    |LINF      |Loop Infinite
     * |        |          |Indicates, if set, that the loop should be executed indefinitely until stopped by the STOP command
     * |        |          |Otherwise the loop is execute LCNT times.
     * |[17]    |IDA       |Increment DRAM Address
     * |        |          |Indicates, if set, that DRAM addresses should be incremented every time a DRAM read/write command inside the loop is executed.
     * |[31:28] |XLEADDR   |Expected Data Loop End Address
     * |        |          |The last expected data cache word address that contains valid expected data
     * |        |          |Expected data should be looped between 0 and this address.
     * |        |          |XLEADDR field uses only the following bits based on the cache depth:
     * |        |          |DCU expected data cache = 4, XLEADDR[1:0]
     * |        |          |DCU expected data cache = 8, XLEADDR[2:0]
     * |        |          |DCU expected data cache = 16, XLEADDR[3:0]
     * @var DDRPHY_T::DCUGCR
     * Offset: 0xD0  DCU General Configuration Register (DCUGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |RCSW      |Read Capture Start Word
     * |        |          |The capture and compare of read data should start after Nth word
     * |        |          |For example setting this value to 12 will skip the first 12 read data.
     * @var DDRPHY_T::DCUTPR
     * Offset: 0xD4  DCU Timing Parameter Register (DCUTPR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |tDCUT0    |DCU Generic Timing Parameter 0
     * |[15:8]  |tDCUT1    |DCU Generic Timing Parameter 1
     * |[23:16] |tDCUT2    |DCU Generic Timing Parameter 2
     * |[31:24] |tDCUT3    |DCU Generic Timing Parameter 3
     * @var DDRPHY_T::DCUSR0
     * Offset: 0xD8  DCU Status Register 0 (DCUSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDONE     |Run Done
     * |        |          |Indicates, if set, that the DCU has finished executing the commands in the command cache
     * |        |          |This bit is also set to indicate that a STOP command has successfully been executed and command execution has stopped.
     * |[1]     |CFAIL     |Capture Fail
     * |        |          |Indicates, if set, that at least one read data word has failed.
     * |[2]     |CFULL     |Capture Full
     * |        |          |Indicates, if set, that the capture cache is full.
     * @var DDRPHY_T::DCUSR1
     * Offset: 0xDC  DCU Status Register 1 (DCUSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |RDCNT     |Read Count
     * |        |          |Number of read words returned from the SDRAM.
     * |[23:16] |FLCNT     |Fail Count
     * |        |          |Number of read words that have failed.
     * |[31:24] |LPCNT     |Loop Count
     * |        |          |Indicates the value of the loop count
     * |        |          |This is useful when the program has stopped because of failures to assess how many reads were executed before first fail.
     * @var DDRPHY_T::BISTRR
     * Offset: 0x100  BIST Run Register (BISTRR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |BINST     |BIST Instruction
     * |        |          |Selects the BIST instruction to be executed: Valid values are:
     * |        |          |000 = NOP: No operation
     * |        |          |001 = Run: Triggers the running of the BIST.
     * |        |          |010 = Stop: Stops the running of the BIST.
     * |        |          |011 = Reset: Resets all BIST run-time registers, such as error counters.
     * |        |          |100 - 111 Reserved
     * |[3]     |BMODE     |BIST Mode
     * |        |          |Selects the mode in which BIST is run. Valid values are:
     * |        |          |0 = Loopback mode: Address, commands and data loop back at the PHY I/Os.
     * |        |          |1 = DRAM mode: Address, commands and data go to DRAM for normal memory accesses.
     * |[4]     |BINF      |BIST Infinite Run
     * |        |          |Specifies, if set, that the BIST should be run indefinitely until when it is either stopped or a failure has been encountered
     * |        |          |Otherwise BIST is run until number of BIST words specified in the BISTWCR register has been generated.
     * |[12:5]  |NFAIL     |Number of Failures
     * |        |          |Specifies the number of failures after which the execution of commands and the capture of read data should stop if BSONF bit of this register is set
     * |        |          |Execution of commands and the capture of read data will stop after (NFAIL+1) failures if BSONF is set.
     * |[13]    |BSONF     |BIST Stop On Nth Fail
     * |        |          |Specifies, if set, that the BIST should stop when an nth data word or address/command comparison error has been encountered.
     * |[14]    |BDXEN     |BIST DATX8 Enable
     * |        |          |Enables the running of BIST on the data byte lane PHYs
     * |        |          |This bit is exclusive with BACEN, i.e
     * |        |          |both cannot be set to '1' at the same time.
     * |[15]    |BACEN     |BIST AC Enable
     * |        |          |Enables the running of BIST on the address/command lane PHY
     * |        |          |This bit is exclusive with BDXEN, i.e
     * |        |          |both cannot be set to '1' at the same time.
     * |[16]    |BDMEN     |BIST Data Mask Enable
     * |        |          |Enables, if set, that the data mask BIST should be included in the BIST run, i.e
     * |        |          |data pattern generated and loopback data compared
     * |        |          |This is valid only for loopback mode.
     * |[18:17] |BDPAT     |BIST Data Pattern
     * |        |          |Selects the data pattern used during BIST. Valid values are:
     * |        |          |00 = Walking 0
     * |        |          |01 = Walking 1
     * |        |          |10 = LFSR-based pseudo-random
     * |        |          |11 = User programmable (Not valid for AC loopback).
     * |[22:19] |BDXSEL    |BIST DATX8 Select
     * |        |          |Select the byte lane for comparison of loopback/read data. Valid values are 0 to 8.
     * |[24:23] |BCKSEL    |BIST CK Select
     * |        |          |Selects the CK that should be used to register the AC loopback signals from the I/Os. Valid values are:
     * |        |          |00 = CK[0]
     * |        |          |01 = CK[1]
     * |        |          |10 = CK[2]
     * |        |          |11 = Reserved
     * |[26:25] |BCCSEL    |BIST Clock Cycle Select
     * |        |          |Selects the clock numbers on which the AC loopback data is written into the FIFO
     * |        |          |Data is written into the loopback FIFO once every four clock cycles
     * |        |          |Valid values are:
     * |        |          |00 = Clock cycle 0, 4, 8, 12, etc.
     * |        |          |01 = Clock cycle 1, 5, 9, 13, etc.
     * |        |          |10 = Clock cycle 2, 6, 10, 14, etc.
     * |        |          |11 = Clock cycle 3, 7, 11, 15, etc.
     * @var DDRPHY_T::BISTWCR
     * Offset: 0x104  BIST Word Count Register (BISTWCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |BWCNT     |BIST Word Count
     * |        |          |Indicates the number of words to generate during BIST
     * |        |          |This must be a multiple of DRAM burst length (BL) divided by 2, e.g
     * |        |          |for BL=8, valid values are 4, 8, 12, 16, and so on.
     * @var DDRPHY_T::BISTMSKR0
     * Offset: 0x108  BIST Mask Register 0 (BISTMSKR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |AMSK      |Address Mask
     * |        |          |Mask bit for each of the up to 16 address bits.
     * |[18:16] |BAMSK     |Bank Address Mask
     * |        |          |Mask bit for each of the up to 3 bank address bits.
     * |[19]    |WEMSK     |WE Mask
     * |        |          |Mask bit for the WE#.
     * |[23:20] |CKEMSK    |CKE Mask
     * |        |          |Mask bit for each of the up to 4 CKE bits.
     * |[27:24] |CSMSK     |CS Mask
     * |        |          |Mask bit for each of the up to 4 CS# bits.
     * |[31:28] |ODTMSK    |ODT Mask
     * |        |          |Mask bit for each of the up to 4 ODT bits.
     * @var DDRPHY_T::BISTMSKR1
     * Offset: 0x10C  BIST Mask Register 1 (BISTMSKR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RASMSK    |RAS Mask
     * |        |          |Mask bit for the RAS.
     * |[1]     |CASMSK    |CAS Mask
     * |        |          |Mask bit for the CAS.
     * |[27]    |PARMSK    |Mask bit for the PAR_IN
     * |        |          |Only for DIMM parity support and only if the design is compiled for less than 3 ranks.
     * |[31:28] |DMMSK     |DM Mask
     * |        |          |Mask bit for the data mask (DM) bit.
     * @var DDRPHY_T::BISTMSKR2
     * Offset: 0x110  BIST Mask Register 2 (BISTMSKR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DQMSK     |DQ Mask
     * |        |          |Mask bit for each of the 8 data (DQ) bits.
     * @var DDRPHY_T::BISTLSR
     * Offset: 0x114  BIST LFSR Seed Register (BISTLSR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |LFSR seed
     * |        |          |LFSR seed for pseudo-random BIST patterns.
     * @var DDRPHY_T::BISTAR0
     * Offset: 0x118  BIST Address Register 0 (BISTAR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |BCOL      |BIST Column Address
     * |        |          |Selects the SDRAM column address to be used during BIST
     * |        |          |The lower bits of this address must be "0000" for BL16, "000" for BL8, "00" for BL4 and "0" for BL2.
     * |[27:12] |BROW      |BIST Row Address
     * |        |          |Selects the SDRAM row address to be used during BIST.
     * |[30:28] |BBANK     |BIST Bank Address
     * |        |          |Selects the SDRAM bank address to be used during BIST.
     * @var DDRPHY_T::BISTAR1
     * Offset: 0x11C  BIST Address Register 1 (BISTAR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |BRANK     |BIST Rank
     * |        |          |Selects the SDRAM rank to be used during BIST. Valid values range from 0 to maximum ranks minus 1.
     * |[3:2]   |BMRANK    |BIST Maximum Rank
     * |        |          |Specifies the maximum SDRAM rank to be used during BIST
     * |        |          |The default value is set to maximum ranks minus 1
     * |        |          |Example default shown here is for a 4-rank system
     * |[15:4]  |BAINC     |BIST Address Increment
     * |        |          |Selects the value by which the SDRAM address is incremented for each write/read access
     * |        |          |This value must be at the beginning of a burst boundary, i.e
     * |        |          |the lower bits must be "0000" for BL16, "000" for BL8, "00" for BL4 and "0" for BL2.
     * @var DDRPHY_T::BISTAR2
     * Offset: 0x120  BIST Address Register 2 (BISTAR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |BMCOL     |BIST Maximum Column Address
     * |        |          |Specifies the maximum SDRAM column address to be used during BIST before the address increments to the next row.
     * |[27:12] |BMROW     |BIST Maximum Row Address
     * |        |          |Specifies the maximum SDRAM row address to be used during BIST before the address increments to the next bank.
     * |[30:28] |BMBANK    |BIST Maximum Bank Address
     * |        |          |Specifies the maximum SDRAM bank address to be used during BIST before the address increments to the next rank.
     * @var DDRPHY_T::BISTUDPR
     * Offset: 0x124  BIST User Data Pattern Register (BISTUDPR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |BUDP0     |BIST User Data Pattern 0
     * |        |          |Data to be applied on even DQ pins during BIST.
     * |[31:16] |BUDP1     |BIST User Data Pattern 1
     * |        |          |Data to be applied on odd DQ pins during BIST.
     * @var DDRPHY_T::BISTGSR
     * Offset: 0x128  BIST General Status Register (BISTGSR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BDONE     |BIST Done
     * |        |          |Indicates, if set, that the BIST has finished executing
     * |        |          |This bit is reset to zero when BIST is triggered.
     * |[1]     |BACERR    |BIST Address/Command Error
     * |        |          |indicates, if set, that there is a data comparison error in the address/command lane.
     * |[2]     |BDXERR    |BIST Data Error
     * |        |          |indicates, if set, that there is a data comparison error in the byte lane.
     * |[17:16] |PARBER    |PAR_IN Bit Error
     * |        |          |Indicates the number of bit errors on PAR_IN
     * |[27:20] |DMBER     |DM Bit Error
     * |        |          |Indicates the number of bit errors on data mask (DM) bit
     * |        |          |DMBER[1:0] are for even DQS cycles first DM beat, and DMBER[3:2] are for even DQS cycles second DM beat
     * |        |          |Similarly, DMBER[5:4] are for odd DQS cycles first DM beat, and DMBER[7:6] are for odd DQS cycles second DM beat.
     * |[29:28] |RASBER    |RAS Bit Error
     * |        |          |Indicates the number of bit errors on RAS.
     * |[31:30] |CASBER    |CAS Bit Error
     * |        |          |Indicates the number of bit errors on CAS.
     * @var DDRPHY_T::BISTWER
     * Offset: 0x12C  BIST Word Error Register (BISTWER)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |ACWER     |Address/Command Word Error
     * |        |          |Indicates the number of word errors on the address/command lane
     * |        |          |An error on any bit of the address/command bus increments the error count.
     * |[31:16] |DXWER     |Byte Word Error
     * |        |          |Indicates the number of word errors on the byte lane
     * |        |          |An error on any bit of the data bus including the data mask bit increments the error count.
     * @var DDRPHY_T::BISTBER0
     * Offset: 0x130  BIST Bit Error Register 0 (BISTBER0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ABER      |Address Bit Error
     * |        |          |Each group of two bits indicate the bit error count on each of the up to 16 address bits
     * |        |          |[1:0] is the error count for A[0], [3:2] for A[1], and so on.
     * @var DDRPHY_T::BISTBER1
     * Offset: 0x134  BIST Bit Error Register 1 (BISTBER1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |BABER     |Bank Address Bit Error
     * |        |          |Each group of two bits indicate the bit error count on each of the up to 3 bank address bits
     * |        |          |[1:0] is the error count for BA[0], [3:2] for BA[1], and so on.
     * |[7:6]   |WEBER     |WE# Bit Error
     * |        |          |Indicates the number of bit errors on WE#.
     * |[15:8]  |CKEBER    |CKE Bit Error
     * |        |          |Each group of two bits indicate the bit error count on each of the up to 4 CKE bits
     * |        |          |[1:0] is the error count for CKE[0], [3:2] for CKE[1], and so on.
     * |[23:16] |CSBER     |CS# Bit Error
     * |        |          |Each group of two bits indicate the bit error count on each of the up to 4 CS# bits
     * |        |          |[1:0] is the error count for CS#[0], [3:2] for CS#[1], and so on.
     * |[31:24] |ODTBER    |ODT Bit Error
     * |        |          |Each group of two bits indicates the bit error count on each of the up to 4 ODT bits
     * |        |          |[1:0] is the error count for ODT[0], [3:2] for ODT[1], and so on.
     * @var DDRPHY_T::BISTBER2
     * Offset: 0x138  BIST Bit Error Register 2 (BISTBER2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DQBER0    |Data Bit Error
     * |        |          |The error count for even DQS cycles
     * |        |          |The first 16 bits indicate the error count for the first data beat (i.e
     * |        |          |the data driven out on DQ[7:0] on the rising edge of DQS)
     * |        |          |The second 16 bits indicate the error on the second data beat (i.e
     * |        |          |the error count of the data driven out on DQ[7:0] on the falling edge of DQS)
     * |        |          |For each of the 16-bit group, the first 2 bits are for DQ[0], the second for DQ[1], and so on.
     * @var DDRPHY_T::BISTBER3
     * Offset: 0x13C  BIST Bit Error Register 3 (BISTBER3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DQBER1    |Data Bit Error
     * |        |          |The error count for odd DQS cycles
     * |        |          |The first 16 bits indicate the error count for the first data beat (i.e
     * |        |          |the data driven out on DQ[7:0] on the rising edge of DQS)
     * |        |          |The second 16 bits indicate the error on the second data beat (i.e
     * |        |          |the error count of the data driven out on DQ[7:0] on the falling edge of DQS)
     * |        |          |For each of the 16-bit group, the first 2 bits are for DQ[0], the second for DQ[1], and so on.
     * @var DDRPHY_T::BISTWCSR
     * Offset: 0x140  BIST Word Count Status Register (BISTWCSR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |ACWCNT    |Address/Command Word Count
     * |        |          |Indicates the number of words received from the address/command lane.
     * |[31:16] |DXWCNT    |Byte Word Count
     * |        |          |Indicates the number of words received from the byte lane.
     * @var DDRPHY_T::BISTFWR0
     * Offset: 0x144  BIST Fail Word Register 0 (BISTFWR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |AWEBS     |Address Word Error Bit Status
     * |        |          |Bit status during a word error for each of the up to 16 address bits.
     * |[18:16] |BAWEBS    |Bank Address Word Error Bit Status
     * |        |          |Bit status during a word error for each of the up to 3 bank address bits.
     * |[19]    |WEWEBS    |WE Word Error Bit Status
     * |        |          |Bit status during a word error for the WE#.
     * |[23:20] |CKEWEBS   |CKE Word Error Bit Status
     * |        |          |Bit status during a word error for each of the up to 4 CKE bits.
     * |[27:24] |CSWEBS    |CS Word Error Bit Status
     * |        |          |Bit status during a word error for each of the up to 4 CS# bits.
     * |[31:28] |ODTWEBS   |ODT Word Error Bit Status
     * |        |          |Bit status during a word error for each of the up to 4 ODT bits.
     * @var DDRPHY_T::BISTFWR1
     * Offset: 0x148  BIST Fail Word Register 1 (BISTFWR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RASWEBS   |RAS Word Error Bit Status
     * |        |          |Bit status during a word error for the RAS.
     * |[1]     |CASWEBS   |CAS Word Error Bit Status
     * |        |          |Bit status during a word error for the CAS.
     * |[26]    |PARWEBS   |PAR_IN Word Error Bit Status
     * |        |          |Bit status during a word error for the PAR_IN. Only for DIMM parity support
     * |[31:28] |DMWEBS    |DM Word Error Bit Status
     * |        |          |Bit status during a word error for the data mask (DM) bit
     * |        |          |DMWEBS [0] is for the first DM beat, DMWEBS [1] is for the second DM beat, and so on.
     * @var DDRPHY_T::BISTFWR2
     * Offset: 0x14C  BIST Fail Word Register 2 (BISTFWR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DQWEBS    |DQ Word Error Bit Status
     * |        |          |Bit status during a word error for each of the 8 data (DQ) bits
     * |        |          |The first 8 bits indicate the status of the first data beat (i.e
     * |        |          |the status of the data driven out on DQ[7:0] on the rising edge of DQS)
     * |        |          |The second 8 bits indicate the status of the second data beat (i.e
     * |        |          |the status of the data driven out on DQ[7:0] on the falling edge of DQS), and so on
     * |        |          |For each of the 8-bit group, the first bit is for DQ[0], the second bit is for DQ[1], and so on.
     * @var DDRPHY_T::AACR
     * Offset: 0x174  Anti-Aging Control Register (AACR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[29:0]  |AATR      |Anti-Aging Toggle Rate
     * |        |          |Defines the number of controller clock (ctl_clk) cycles after which the PUB will toggle the data going to DATX8 if the data channel between the controller/PUB and DATX8 has been idle for this long.
     * |        |          |The default value corresponds to a toggling count of 4096 ctl_clk cycles
     * |        |          |For a ctl_clk running at 533 MHz the toggle rate will be approximately 7.68us.
     * |        |          |The default value may also be overridden by the macro
     * |        |          |DWC_AACR_AATR_DFLT.
     * |[30]    |AAENC     |Anti-Aging Enable Control
     * |        |          |Enables, if set, the automatic toggling of the data going to the DATX8 when the data channel from the controller/PUB to DATX8 is idle for programmable number of clock cycles.
     * |[31]    |AAOENC    |Anti-Aging PAD Output Enable Control
     * |        |          |Enables, if set, anti-aging toggling on the pad output enable signal "ctl_oe_n" going into the DATX8s
     * |        |          |This will increase power consumption for the anti-aging feature.
     * @var DDRPHY_T::GPR0
     * Offset: 0x178  General Purpose Register 0 (GPR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |GPR0      |General Purpose Register 0
     * |        |          |General purpose register bits.
     * @var DDRPHY_T::GPR1
     * Offset: 0x17C  General Purpose Register 1 (GPR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |GPR1      |General Purpose Register 1
     * |        |          |General purpose register bits.
     * @var DDRPHY_T::ZQ0CR0
     * Offset: 0x180  Impedance Control Register 0 (ZQnCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZDATA     |Impedance Over-Ride Data
     * |        |          |Data used to directly drive the impedance control.
     * |        |          |ZDATA field mapping for D3R I/O is as follows:
     * |        |          |ZDATA[27:20] is reserved and returns zeros on reads.
     * |        |          |ZDATA[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZDATA[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZDATA[9:5] is used to select the pull-up output impedance
     * |        |          |ZDATA[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[28]    |ZDEN      |Impedance Over-Ride Enable
     * |        |          |When this bit is set, it allows users to directly drive the impedance control using the data programmed in the ZDATA field
     * |        |          |Otherwise, the control is generated automatically by the impedance control logic.
     * |[29]    |ZCALBYP   |Impedance Calibration Bypass
     * |        |          |Bypasses, if set, impedance calibration of this ZQ control block when impedance calibration is already in progress
     * |        |          |Impedance calibration can be disabled prior to trigger by using the ZCALEN bit.
     * |[30]    |ZCALEN    |Impedance Calibration Enable
     * |        |          |Enables, if set, the impedance calibration of this ZQ control block when impedance calibration is triggered using either the ZCAL bit of PIR register or the DFI update interface.
     * |[31]    |ZQPD      |ZQ Power Down
     * |        |          |Powers down, if set, the PZQ cell.
     * @var DDRPHY_T::ZQ0CR1
     * Offset: 0x184  Impedance Control Register 1 (ZQnCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ZPROG     |Impedance Divide Ratio
     * |        |          |Selects the external resistor divide ratio to be used to set the output impedance and the on-die termination as follows:
     * |        |          |ZPROG[7:4] = On-die termination divide select
     * |        |          |ZPROG[3:0] = Output impedance divide select
     * |[12]    |DFICU0    |DFI Controller Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 0 (channel 0) requests an update.
     * |[13]    |DFICU1    |DFI Controller Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * |[14]    |DFICCU    |DFI Concurrent Controller Update Interface
     * |        |          |Sets this impedance controller to be enabled for calibration when both of the DFI controller update interfaces request an update on the same clock
     * |        |          |This provides the ability to enable impedance calibration updates for the Address/Command lane
     * |        |          |Only valid in shared-AC mode.
     * |[16]    |DFIPU0    |DFI Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 0 (channel 0) requests an update.
     * |[17]    |DFIPU1    |DFI Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * @var DDRPHY_T::ZQ0SR0
     * Offset: 0x188  Impedance Status Register 0 (ZQnSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZCTRL     |Impedance Control
     * |        |          |Current value of impedance control.
     * |        |          |ZCTRL field mapping for D3R I/O is as follows:
     * |        |          |ZCTRL[27:20] is reserved and returns zeros on reads.
     * |        |          |ZCTRL[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZCTRL[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZCTRL[9:5] is used to select the pull-up output impedance.
     * |        |          |ZCTRL[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[30]    |ZERR      |Impedance Calibration Error
     * |        |          |If set, indicates that there was an error during impedance calibration.
     * |[31]    |ZDONE     |Impedance Calibration Done
     * |        |          |Indicates that impedance calibration has completed.
     * @var DDRPHY_T::ZQ0SR1
     * Offset: 0x18C  Impedance Status Register 1 (ZQnSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ZPD       |Output impedance pull-down calibration status
     * |        |          |Valid status encodings are:
     * |        |          |00 = Completed with no errors
     * |        |          |01 = Overflow error
     * |        |          |10 = Underflow error
     * |        |          |11 = Calibration in progress
     * |[3:2]   |ZPU       |Output impedance pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[5:4]   |OPD       |On-die termination pull-down calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[7:6]   |OPU       |On-die termination pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * @var DDRPHY_T::ZQ1CR0
     * Offset: 0x190  Impedance Control Register 0 (ZQnCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZDATA     |Impedance Over-Ride Data
     * |        |          |Data used to directly drive the impedance control.
     * |        |          |ZDATA field mapping for D3R I/O is as follows:
     * |        |          |ZDATA[27:20] is reserved and returns zeros on reads.
     * |        |          |ZDATA[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZDATA[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZDATA[9:5] is used to select the pull-up output impedance
     * |        |          |ZDATA[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[28]    |ZDEN      |Impedance Over-Ride Enable
     * |        |          |When this bit is set, it allows users to directly drive the impedance control using the data programmed in the ZDATA field
     * |        |          |Otherwise, the control is generated automatically by the impedance control logic.
     * |[29]    |ZCALBYP   |Impedance Calibration Bypass
     * |        |          |Bypasses, if set, impedance calibration of this ZQ control block when impedance calibration is already in progress
     * |        |          |Impedance calibration can be disabled prior to trigger by using the ZCALEN bit.
     * |[30]    |ZCALEN    |Impedance Calibration Enable
     * |        |          |Enables, if set, the impedance calibration of this ZQ control block when impedance calibration is triggered using either the ZCAL bit of PIR register or the DFI update interface.
     * |[31]    |ZQPD      |ZQ Power Down
     * |        |          |Powers down, if set, the PZQ cell.
     * @var DDRPHY_T::ZQ1CR1
     * Offset: 0x194  Impedance Control Register 1 (ZQnCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ZPROG     |Impedance Divide Ratio
     * |        |          |Selects the external resistor divide ratio to be used to set the output impedance and the on-die termination as follows:
     * |        |          |ZPROG[7:4] = On-die termination divide select
     * |        |          |ZPROG[3:0] = Output impedance divide select
     * |[12]    |DFICU0    |DFI Controller Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 0 (channel 0) requests an update.
     * |[13]    |DFICU1    |DFI Controller Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * |[14]    |DFICCU    |DFI Concurrent Controller Update Interface
     * |        |          |Sets this impedance controller to be enabled for calibration when both of the DFI controller update interfaces request an update on the same clock
     * |        |          |This provides the ability to enable impedance calibration updates for the Address/Command lane
     * |        |          |Only valid in shared-AC mode.
     * |[16]    |DFIPU0    |DFI Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 0 (channel 0) requests an update.
     * |[17]    |DFIPU1    |DFI Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * @var DDRPHY_T::ZQ1SR0
     * Offset: 0x198  Impedance Status Register 0 (ZQnSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZCTRL     |Impedance Control
     * |        |          |Current value of impedance control.
     * |        |          |ZCTRL field mapping for D3R I/O is as follows:
     * |        |          |ZCTRL[27:20] is reserved and returns zeros on reads.
     * |        |          |ZCTRL[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZCTRL[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZCTRL[9:5] is used to select the pull-up output impedance.
     * |        |          |ZCTRL[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[30]    |ZERR      |Impedance Calibration Error
     * |        |          |If set, indicates that there was an error during impedance calibration.
     * |[31]    |ZDONE     |Impedance Calibration Done
     * |        |          |Indicates that impedance calibration has completed.
     * @var DDRPHY_T::ZQ1SR1
     * Offset: 0x19C  Impedance Status Register 1 (ZQnSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ZPD       |Output impedance pull-down calibration status
     * |        |          |Valid status encodings are:
     * |        |          |00 = Completed with no errors
     * |        |          |01 = Overflow error
     * |        |          |10 = Underflow error
     * |        |          |11 = Calibration in progress
     * |[3:2]   |ZPU       |Output impedance pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[5:4]   |OPD       |On-die termination pull-down calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[7:6]   |OPU       |On-die termination pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * @var DDRPHY_T::ZQ2CR0
     * Offset: 0x1A0  Impedance Control Register 0 (ZQnCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZDATA     |Impedance Over-Ride Data
     * |        |          |Data used to directly drive the impedance control.
     * |        |          |ZDATA field mapping for D3R I/O is as follows:
     * |        |          |ZDATA[27:20] is reserved and returns zeros on reads.
     * |        |          |ZDATA[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZDATA[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZDATA[9:5] is used to select the pull-up output impedance
     * |        |          |ZDATA[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[28]    |ZDEN      |Impedance Over-Ride Enable
     * |        |          |When this bit is set, it allows users to directly drive the impedance control using the data programmed in the ZDATA field
     * |        |          |Otherwise, the control is generated automatically by the impedance control logic.
     * |[29]    |ZCALBYP   |Impedance Calibration Bypass
     * |        |          |Bypasses, if set, impedance calibration of this ZQ control block when impedance calibration is already in progress
     * |        |          |Impedance calibration can be disabled prior to trigger by using the ZCALEN bit.
     * |[30]    |ZCALEN    |Impedance Calibration Enable
     * |        |          |Enables, if set, the impedance calibration of this ZQ control block when impedance calibration is triggered using either the ZCAL bit of PIR register or the DFI update interface.
     * |[31]    |ZQPD      |ZQ Power Down
     * |        |          |Powers down, if set, the PZQ cell.
     * @var DDRPHY_T::ZQ2CR1
     * Offset: 0x1A4  Impedance Control Register 1 (ZQnCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ZPROG     |Impedance Divide Ratio
     * |        |          |Selects the external resistor divide ratio to be used to set the output impedance and the on-die termination as follows:
     * |        |          |ZPROG[7:4] = On-die termination divide select
     * |        |          |ZPROG[3:0] = Output impedance divide select
     * |[12]    |DFICU0    |DFI Controller Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 0 (channel 0) requests an update.
     * |[13]    |DFICU1    |DFI Controller Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * |[14]    |DFICCU    |DFI Concurrent Controller Update Interface
     * |        |          |Sets this impedance controller to be enabled for calibration when both of the DFI controller update interfaces request an update on the same clock
     * |        |          |This provides the ability to enable impedance calibration updates for the Address/Command lane
     * |        |          |Only valid in shared-AC mode.
     * |[16]    |DFIPU0    |DFI Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 0 (channel 0) requests an update.
     * |[17]    |DFIPU1    |DFI Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * @var DDRPHY_T::ZQ2SR0
     * Offset: 0x1A8  Impedance Status Register 0 (ZQnSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZCTRL     |Impedance Control
     * |        |          |Current value of impedance control.
     * |        |          |ZCTRL field mapping for D3R I/O is as follows:
     * |        |          |ZCTRL[27:20] is reserved and returns zeros on reads.
     * |        |          |ZCTRL[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZCTRL[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZCTRL[9:5] is used to select the pull-up output impedance.
     * |        |          |ZCTRL[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[30]    |ZERR      |Impedance Calibration Error
     * |        |          |If set, indicates that there was an error during impedance calibration.
     * |[31]    |ZDONE     |Impedance Calibration Done
     * |        |          |Indicates that impedance calibration has completed.
     * @var DDRPHY_T::ZQ2SR1
     * Offset: 0x1AC  Impedance Status Register 1 (ZQnSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ZPD       |Output impedance pull-down calibration status
     * |        |          |Valid status encodings are:
     * |        |          |00 = Completed with no errors
     * |        |          |01 = Overflow error
     * |        |          |10 = Underflow error
     * |        |          |11 = Calibration in progress
     * |[3:2]   |ZPU       |Output impedance pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[5:4]   |OPD       |On-die termination pull-down calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[7:6]   |OPU       |On-die termination pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * @var DDRPHY_T::ZQ3CR0
     * Offset: 0x1B0  Impedance Control Register 0 (ZQnCR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZDATA     |Impedance Over-Ride Data
     * |        |          |Data used to directly drive the impedance control.
     * |        |          |ZDATA field mapping for D3R I/O is as follows:
     * |        |          |ZDATA[27:20] is reserved and returns zeros on reads.
     * |        |          |ZDATA[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZDATA[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZDATA[9:5] is used to select the pull-up output impedance
     * |        |          |ZDATA[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[28]    |ZDEN      |Impedance Over-Ride Enable
     * |        |          |When this bit is set, it allows users to directly drive the impedance control using the data programmed in the ZDATA field
     * |        |          |Otherwise, the control is generated automatically by the impedance control logic.
     * |[29]    |ZCALBYP   |Impedance Calibration Bypass
     * |        |          |Bypasses, if set, impedance calibration of this ZQ control block when impedance calibration is already in progress
     * |        |          |Impedance calibration can be disabled prior to trigger by using the ZCALEN bit.
     * |[30]    |ZCALEN    |Impedance Calibration Enable
     * |        |          |Enables, if set, the impedance calibration of this ZQ control block when impedance calibration is triggered using either the ZCAL bit of PIR register or the DFI update interface.
     * |[31]    |ZQPD      |ZQ Power Down
     * |        |          |Powers down, if set, the PZQ cell.
     * @var DDRPHY_T::ZQ3CR1
     * Offset: 0x1B4  Impedance Control Register 1 (ZQnCR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ZPROG     |Impedance Divide Ratio
     * |        |          |Selects the external resistor divide ratio to be used to set the output impedance and the on-die termination as follows:
     * |        |          |ZPROG[7:4] = On-die termination divide select
     * |        |          |ZPROG[3:0] = Output impedance divide select
     * |[12]    |DFICU0    |DFI Controller Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 0 (channel 0) requests an update.
     * |[13]    |DFICU1    |DFI Controller Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI controller update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * |[14]    |DFICCU    |DFI Concurrent Controller Update Interface
     * |        |          |Sets this impedance controller to be enabled for calibration when both of the DFI controller update interfaces request an update on the same clock
     * |        |          |This provides the ability to enable impedance calibration updates for the Address/Command lane
     * |        |          |Only valid in shared-AC mode.
     * |[16]    |DFIPU0    |DFI Update Interface 0
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 0 (channel 0) requests an update.
     * |[17]    |DFIPU1    |DFI Update Interface 1
     * |        |          |Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 1 (channel 1) requests an update
     * |        |          |Only valid in shared-AC mode.
     * @var DDRPHY_T::ZQ3SR0
     * Offset: 0x1B8  Impedance Status Register 0 (ZQnSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27:0]  |ZCTRL     |Impedance Control
     * |        |          |Current value of impedance control.
     * |        |          |ZCTRL field mapping for D3R I/O is as follows:
     * |        |          |ZCTRL[27:20] is reserved and returns zeros on reads.
     * |        |          |ZCTRL[19:15] is used to select the pull-up on-die termination impedance.
     * |        |          |ZCTRL[14:10] is used to select the pull-down on-die termination impedance.
     * |        |          |ZCTRL[9:5] is used to select the pull-up output impedance.
     * |        |          |ZCTRL[4:0] is used to select the pull-down output impedance.
     * |        |          |Note: The default value is 0x000014A for I/O type D3R.
     * |[30]    |ZERR      |Impedance Calibration Error
     * |        |          |If set, indicates that there was an error during impedance calibration.
     * |[31]    |ZDONE     |Impedance Calibration Done
     * |        |          |Indicates that impedance calibration has completed.
     * @var DDRPHY_T::ZQ3SR1
     * Offset: 0x1BC  Impedance Status Register 1 (ZQnSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ZPD       |Output impedance pull-down calibration status
     * |        |          |Valid status encodings are:
     * |        |          |00 = Completed with no errors
     * |        |          |01 = Overflow error
     * |        |          |10 = Underflow error
     * |        |          |11 = Calibration in progress
     * |[3:2]   |ZPU       |Output impedance pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[5:4]   |OPD       |On-die termination pull-down calibration status
     * |        |          |Similar status encodings as ZPD.
     * |[7:6]   |OPU       |On-die termination pull-up calibration status
     * |        |          |Similar status encodings as ZPD.
     * @var DDRPHY_T::DX0GCR
     * Offset: 0x1C0  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to "0") when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX0GSR0
     * Offset: 0x1C4  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX0GSR1
     * Offset: 0x1C8  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX0BDLR0
     * Offset: 0x1CC  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX0BDLR1
     * Offset: 0x1D0  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX0BDLR2
     * Offset: 0x1D4  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX0BDLR3
     * Offset: 0x1D8  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX0BDLR4
     * Offset: 0x1DC  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX0LCDLR0
     * Offset: 0x1E0  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX0LCDLR1
     * Offset: 0x1E4  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX0LCDLR2
     * Offset: 0x1E8  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX0MDLR
     * Offset: 0x1EC  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX0GTR
     * Offset: 0x1F0  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX0GSR2
     * Offset: 0x1F4  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX1GCR
     * Offset: 0x200  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX1GSR0
     * Offset: 0x204  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX1GSR1
     * Offset: 0x208  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX1BDLR0
     * Offset: 0x20C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX1BDLR1
     * Offset: 0x210  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX1BDLR2
     * Offset: 0x214  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX1BDLR3
     * Offset: 0x218  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX1BDLR4
     * Offset: 0x21C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX1LCDLR0
     * Offset: 0x220  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX1LCDLR1
     * Offset: 0x224  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX1LCDLR2
     * Offset: 0x228  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX1MDLR
     * Offset: 0x22C  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX1GTR
     * Offset: 0x230  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX1GSR2
     * Offset: 0x234  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX2GCR
     * Offset: 0x240  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX2GSR0
     * Offset: 0x244  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX2GSR1
     * Offset: 0x248  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX2BDLR0
     * Offset: 0x24C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX2BDLR1
     * Offset: 0x250  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX2BDLR2
     * Offset: 0x254  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX2BDLR3
     * Offset: 0x258  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX2BDLR4
     * Offset: 0x25C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX2LCDLR0
     * Offset: 0x260  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX2LCDLR1
     * Offset: 0x264  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX2LCDLR2
     * Offset: 0x268  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX2MDLR
     * Offset: 0x26C  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX2GTR
     * Offset: 0x270  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX2GSR2
     * Offset: 0x274  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX3GCR
     * Offset: 0x280  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX3GSR0
     * Offset: 0x284  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX3GSR1
     * Offset: 0x288  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX3BDLR0
     * Offset: 0x28C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX3BDLR1
     * Offset: 0x290  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX3BDLR2
     * Offset: 0x294  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX3BDLR3
     * Offset: 0x298  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX3BDLR4
     * Offset: 0x29C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX3LCDLR0
     * Offset: 0x2A0  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX3LCDLR1
     * Offset: 0x2A4  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX3LCDLR2
     * Offset: 0x2A8  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX3MDLR
     * Offset: 0x2AC  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX3GTR
     * Offset: 0x2B0  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX3GSR2
     * Offset: 0x2B4  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX4GCR
     * Offset: 0x2C0  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX4GSR0
     * Offset: 0x2C4  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX4GSR1
     * Offset: 0x2C8  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX4BDLR0
     * Offset: 0x2CC  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX4BDLR1
     * Offset: 0x2D0  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX4BDLR2
     * Offset: 0x2D4  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX4BDLR3
     * Offset: 0x2D8  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX4BDLR4
     * Offset: 0x2DC  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX4LCDLR0
     * Offset: 0x2E0  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX4LCDLR1
     * Offset: 0x2E4  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var DDRPHY_T::DX4LCDLR2
     * Offset: 0x2E8  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX4MDLR
     * Offset: 0x2EC  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX4GTR
     * Offset: 0x2F0  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX4GSR2
     * Offset: 0x2F4  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX5GCR
     * Offset: 0x300  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX5GSR0
     * Offset: 0x304  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX5GSR1
     * Offset: 0x308  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX5BDLR0
     * Offset: 0x30C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX5BDLR1
     * Offset: 0x310  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX5BDLR2
     * Offset: 0x314  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX5BDLR3
     * Offset: 0x318  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX5BDLR4
     * Offset: 0x31C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX5LCDLR0
     * Offset: 0x320  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX5LCDLR1
     * Offset: 0x324  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX5LCDLR2
     * Offset: 0x328  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX5MDLR
     * Offset: 0x32C  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX5GTR
     * Offset: 0x330  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX5GSR2
     * Offset: 0x334  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX6GCR
     * Offset: 0x340  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX6GSR0
     * Offset: 0x344  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX6GSR1
     * Offset: 0x348  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX6BDLR0
     * Offset: 0x34C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX6BDLR1
     * Offset: 0x350  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX6BDLR2
     * Offset: 0x354  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX6BDLR3
     * Offset: 0x358  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX6BDLR4
     * Offset: 0x35C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX6LCDLR0
     * Offset: 0x360  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX6LCDLR1
     * Offset: 0x364  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var DDRPHY_T::DX6LCDLR2
     * Offset: 0x368  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX6MDLR
     * Offset: 0x36C  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX6GTR
     * Offset: 0x370  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX6GSR2
     * Offset: 0x374  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX7GCR
     * Offset: 0x380  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX7GSR0
     * Offset: 0x384  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX7GSR1
     * Offset: 0x388  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX7BDLR0
     * Offset: 0x38C  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX7BDLR1
     * Offset: 0x390  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX7BDLR2
     * Offset: 0x394  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX7BDLR3
     * Offset: 0x398  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX7BDLR4
     * Offset: 0x39C  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX7LCDLR0
     * Offset: 0x3A0  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX7LCDLR1
     * Offset: 0x3A4  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX7LCDLR2
     * Offset: 0x3A8  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX7MDLR
     * Offset: 0x3AC  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX7GTR
     * Offset: 0x3B0  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX7GSR2
     * Offset: 0x3B4  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     * @var DDRPHY_T::DX8GCR
     * Offset: 0x3C0  DATX8 General Configuration Register (DXnGCR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DXEN      |Data Byte Enable
     * |        |          |Enables, if set, the data byte
     * |        |          |Setting this bit to '0' disables the byte, i.e
     * |        |          |the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
     * |[1]     |DQSODT    |DQS On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[9] is '0'.
     * |[2]     |DQODT     |Data On-Die Termination
     * |        |          |Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte
     * |        |          |This bit is ORed with the common DATX8 ODT configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: This bit is only valid when DXnGCR0[10] is '0'.
     * |[3]     |DXIOM     |Data I/O Mode
     * |        |          |Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the IOM configuration bit of the individual DATX8(see "DATX8 Common Configuration Register (DXCCR)").
     * |[4]     |DXPDD     |Data Power Down Driver
     * |        |          |Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDD configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |        |          |Note: Asserting PDD puts the IO driver cell into a lower power, lower speed mode of operation
     * |        |          |However, it will still drive if its OE is asserted
     * |        |          |ODT will be disabled (if used)
     * |        |          |Asserting PDD does not prevent the IO from driving.
     * |[5]     |DXPDR     |Data Power Down Receiver
     * |        |          |Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)").
     * |[6]     |DQSRPD    |DQSR Power Down
     * |        |          |Powers down, if set, the PDQSR cell
     * |        |          |This bit is ORed with the common PDR configuration bit (see "DATX8 Common Configuration Register (DXCCR)")
     * |[8:7]   |DSEN      |Write DQS Enable
     * |        |          |Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted
     * |        |          |DQS# is always the inversion of DQS
     * |        |          |These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated
     * |        |          |Valid settings are:
     * |        |          |00 = Reserved
     * |        |          |01 = DQS toggling with normal polarity (This should be the default setting)
     * |        |          |10 = Reserved
     * |        |          |11 = Reserved
     * |[9]     |DQSRTT    |DQS Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[10]    |DQRTT     |DQ Dynamic RTT Control
     * |        |          |If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise
     * |        |          |By setting this bit to '0' the dynamic ODT feature is disabled
     * |        |          |To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
     * |[12:11] |RTTOH     |RTT Output Hold
     * |        |          |Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to '0') when using dynamic ODT control
     * |        |          |ODT is disabled almost RTTOH clock cycles after the read postamble.
     * |[13]    |RTTOAL    |RTT On Additive Latency
     * |        |          |Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles
     * |        |          |Valid values are:
     * |        |          |0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
     * |        |          |1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
     * |[15:14] |DXOEO     |Data Byte Output Enable Override
     * |        |          |Specifies whether the output I/O output enable for the byte lane should be set to a fixed value
     * |        |          |Valid values are:
     * |        |          |00 = No override. Output enable is controlled by DFI transactions
     * |        |          |01 = Output enable is asserted (I/O is forced to output mode).
     * |        |          |10 = Output enable is de-asserted (I/O is forced to input mode)
     * |        |          |11 = Reserved
     * |[16]    |PLLRST    |PLL Rest
     * |        |          |Resets the byte PLL by driving the PLL reset pin
     * |        |          |This bit is not self- clearing and a '0' must be written to de-assert the reset
     * |        |          |This bit is ORed with the global PLLRST configuration bit.
     * |[17]    |PLLPD     |PLL Power Down
     * |        |          |Puts the byte PLL in Power-down mode by driving the PLL power down pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the power-down
     * |        |          |This bit is ORed with the global PLLPD configuration bit.
     * |[18]    |GSHIFT    |Gear Shift
     * |        |          |Enables, if set, rapid locking mode on the byte PLL
     * |        |          |This bit is ORed with the global GSHIFT configuration bit.
     * |[19]    |PLLBYP    |PLL Bypass
     * |        |          |Puts the byte PLL in bypass mode by driving the PLL bypass pin
     * |        |          |This bit is not self-clearing and a '0' must be written to de-assert the bypass
     * |        |          |This bit is ORed with the global BYP configuration bit.
     * |[29:26] |WLRKEN    |Write Level Rank Enable
     * |        |          |Specifies the ranks that should be write leveled for this byte
     * |        |          |Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks
     * |        |          |WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables rank 3.
     * |[30]    |MDLEN     |Master Delay Line Enable
     * |        |          |Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered
     * |        |          |These additional measurements are accumulated and filtered as long as this bit remains high
     * |        |          |This bit is ANDed with the common DATX8 MDL enable bit.
     * |[31]    |CALBYP    |Calibration Bypass
     * |        |          |Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
     * @var DDRPHY_T::DX8GSR0
     * Offset: 0x3C4  DATX8 General Status Registers 0 (DXnGSR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDQCAL    |Write DQ Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
     * |[1]     |RDQSCAL   |Read DQS Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
     * |[2]     |RDQSNCAL  |Read DQS# Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
     * |[3]     |GDQSCAL   |Read DQS gating Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
     * |[4]     |WLCAL     |Write Leveling Calibration
     * |        |          |Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
     * |[5]     |WLDONE    |Write Leveling Done
     * |        |          |Indicates, if set, that the DATX8 has completed write leveling.
     * |[6]     |WLERR     |Write Leveling Error
     * |        |          |Indicates, if set, that there is a write leveling error in the DATX8.
     * |[14:7]  |WLPRD     |Write Leveling Period
     * |        |          |Returns the DDR clock period measured by the write leveling LCDL during calibration
     * |        |          |The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period
     * |        |          |This value is PVT compensated.
     * |[15]    |DPLOCK    |DATX8 PLL Lock
     * |        |          |Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
     * |[23:16] |GDQSPRD   |Read DQS gating Period
     * |        |          |Returns the DDR clock period measured by the read DQS gating LCDL during calibration
     * |        |          |This value is PVT compensated.
     * |[27:24] |QSGERR    |DQS Gate Training Error
     * |        |          |Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
     * |[28]    |WLDQ      |Write Leveling DQ Status
     * |        |          |Captures the write leveling DQ status from the DRAM during software write leveling.
     * @var DDRPHY_T::DX8GSR1
     * Offset: 0x3C8  DATX8 General Status Registers 1 (DXnGSR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DLTDONE   |Delay Line Test Done
     * |        |          |Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
     * |[24:1]  |DLTCODE   |Delay Line Test Code
     * |        |          |Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
     * @var DDRPHY_T::DX8BDLR0
     * Offset: 0x3CC  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0WBD    |DQ0 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ0 write path.
     * |[11:6]  |DQ1WBD    |DQ1 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ1 write path.
     * |[17:12] |DQ2WBD    |DQ2 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ2 write path.
     * |[23:18] |DQ3WBD    |DQ3 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ3 write path
     * |[29:24] |DQ4WBD    |DQ4 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ4 write path.
     * @var DDRPHY_T::DX8BDLR1
     * Offset: 0x3D0  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5WBD    |DQ5 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ5 write path.
     * |[11:6]  |DQ6WBD    |DQ6 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ6 write path.
     * |[17:12] |DQ7WBD    |DQ7 Write Bit Delay
     * |        |          |Delay select for the BDL on DQ7 write path.
     * |[23:18] |DMWBD     |DM Write Bit Delay
     * |        |          |Delay select for the BDL on DM write path.
     * |[29:24] |DSWBD     |DQS Write Bit Delay
     * |        |          |Delay select for the BDL on DQS write path
     * @var DDRPHY_T::DX8BDLR2
     * Offset: 0x3D4  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DSOEBD    |DQS Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQS output enable path
     * |[11:6]  |DQOEBD    |DQ Output Enable Bit Delay
     * |        |          |Delay select for the BDL on DQ/DM output enable path.
     * |[17:12] |DSRBD     |DQS Read Bit Delay
     * |        |          |Delay select for the BDL on DQS read path
     * |[23:18] |DSNRBD    |DQSN Read Bit Delay
     * |        |          |Delay select for the BDL on DQSN read path
     * @var DDRPHY_T::DX8BDLR3
     * Offset: 0x3D8  DATX8 Bit Delay Line Register 3 (DXnBDLR3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ0RBD    |DQ0 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ0 read path.
     * |[11:6]  |DQ1RBD    |DQ1 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ1 read path.
     * |[17:12] |DQ2RBD    |DQ2 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ2 read path.
     * |[23:18] |DQ3RBD    |DQ3 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ3 read path
     * |[29:24] |DQ4RBD    |DQ4 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ4 read path.
     * @var DDRPHY_T::DX8BDLR4
     * Offset: 0x3DC  DATX8 Bit Delay Line Register 4 (DXnBDLR4)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |DQ5RBD    |DQ5 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ5 read path.
     * |[11:6]  |DQ6RBD    |DQ6 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ6 read path.
     * |[17:12] |DQ7RBD    |DQ7 Read Bit Delay
     * |        |          |Delay select for the BDL on DQ7 read path.
     * |[23:18] |DMRBD     |DM Read Bit Delay
     * |        |          |Delay select for the BDL on DM read path.
     * @var DDRPHY_T::DX8LCDLR0
     * Offset: 0x3E0  DATX8 Bit Delay Line Register 0 (DXnBDLR0)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0WLD     |Rank 0 Write Leveling Delay
     * |        |          |Rank 0 delay select for the write leveling (WL) LCDL
     * |[15:8]  |R1WLD     |Rank 1 Write Leveling Delay
     * |        |          |Rank 1 delay select for the write leveling (WL) LCDL
     * |[23:16] |R2WLD     |Rank 2 Write Leveling Delay
     * |        |          |Rank 2 delay select for the write leveling (WL) LCDL
     * |[31:24] |R3WLD     |Rank 3 Write Leveling Delay
     * |        |          |Rank 3 delay select for the write leveling (WL) LCDL
     * @var DDRPHY_T::DX8LCDLR1
     * Offset: 0x3E4  DATX8 Bit Delay Line Register 1 (DXnBDLR1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDQD      |Write Data Delay
     * |        |          |Delay select for the write data (WDQ) LCDL
     * |[15:8]  |RDQSD     |Read DQS Delay
     * |        |          |Delay select for the read DQS (RDQS) LCDL
     * |[23:16] |RDQSND    |Read DQSN Delay
     * |        |          |Delay select for the read DQSN (RDQS) LCDL
     * @var DDRPHY_T::DX8LCDLR2
     * Offset: 0x3E8  DATX8 Bit Delay Line Register 2 (DXnBDLR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |R0DQSGD   |Rank 0 Read DQS Gating Delay
     * |        |          |Rank 0 delay select for the read DQS gating (DQSG) LCDL
     * |[15:8]  |R1DQSGD   |Rank 1 Read DQS Gating Delay
     * |        |          |Rank 1 delay select for the read DQS gating (DQSG) LCDL
     * |[23:16] |R2DQSGD   |Rank 2 Read DQS Gating Delay
     * |        |          |Rank 2 delay select for the read DQS gating (DQSG) LCDL
     * |[31:24] |R3DQSGD   |Rank 3 Read DQS Gating Delay
     * |        |          |Rank 3 delay select for the read DQS gating (DQSG) LCDL
     * @var DDRPHY_T::DX8MDLR
     * Offset: 0x3EC  DATX8 Master Delay Line Register (DXnMDLR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IPRD      |Initial Period
     * |        |          |Initial period measured by the master delay line calibration for VT drift compensation
     * |        |          |This value is used as the denominator when calculating the ratios of updates during VT compensation.
     * |[15:8]  |TPRD      |Target Period
     * |        |          |Target period measured by the master delay line calibration for VT drift compensation
     * |        |          |This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
     * |[23:16] |MDLD      |MDL Delay
     * |        |          |Delay select for the LCDL for the Master Delay Line.
     * @var DDRPHY_T::DX8GTR
     * Offset: 0x3F0  DATX8 General Timing Register (DXnGTR)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |R0DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[5:3]   |R1DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[8:6]   |R2DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[11:9]  |R3DGSL    |Rank n DQS Gating System Latency
     * |        |          |This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles
     * |        |          |This is used to compensate for board delays and other system delays
     * |        |          |Power-up default is 000 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register
     * |        |          |Every three bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on
     * |        |          |Valid values are 0 to 7.
     * |[13:12] |R0WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[15:14] |R1WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[17:16] |R2WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * |[19:18] |R3WLSL    |Rank n Write Leveling System Latency
     * |        |          |This is used to adjust the write latency after write leveling
     * |        |          |Power-up default is 01 (i.e
     * |        |          |no extra clock cycles required)
     * |        |          |The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register
     * |        |          |Every two bits of this register control the latency of each of the (up to) four ranks
     * |        |          |R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on
     * |        |          |Valid values:
     * |        |          |00 = Write latency = WL - 1
     * |        |          |01 = Write latency = WL
     * |        |          |10 = Write latency = WL + 1
     * |        |          |11 = Reserved
     * @var DDRPHY_T::DX8GSR2
     * Offset: 0x3F4  DATX8 General Status Register 2 (DXnGSR2)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDERR     |Read Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
     * |[1]     |RDWN      |Read Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
     * |[2]     |WDERR     |Write Bit Deskew Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
     * |[3]     |WDWN      |Write Bit Deskew Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
     * |[4]     |REERR     |Read Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
     * |[5]     |REWN      |Read Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
     * |[6]     |WEERR     |Write Data Eye Training Error
     * |        |          |Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
     * |[7]     |WEWN      |Write Data Eye Training Warning
     * |        |          |Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
     * |[11:8]  |ESTAT     |Error Status
     * |        |          |If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
     */
    __I  uint32_t RIDR;                  /*!< [0x0000] Revision Identification Register                                 */
    __IO uint32_t PIR;                   /*!< [0x0004] PHY Initialization Register (PIR)                                */
    __IO uint32_t PGCR0;                 /*!< [0x0008] PHY General Configuration Registers 0 (PGCR0)                    */
    __IO uint32_t PGCR1;                 /*!< [0x000c] PHY General Configuration Registers 1 (PGCR1)                    */
    __I  uint32_t PGSR0;                 /*!< [0x0010] PHY General Status Registers 0 (PGSR0)                           */
    __I  uint32_t PGSR1;                 /*!< [0x0014] PHY General Status Registers 1 (PGSR1)                           */
    __IO uint32_t PLLCR;                 /*!< [0x0018] PLL Control Register (PLLCR)                                     */
    __IO uint32_t PTR0;                  /*!< [0x001c] PHY Timing Registers 0 (PTR0)                                    */
    __IO uint32_t PTR1;                  /*!< [0x0020] PHY Timing Registers 1 (PTR1)                                    */
    __IO uint32_t PTR2;                  /*!< [0x0024] PHY Timing Registers 2 (PTR2)                                    */
    __IO uint32_t PTR3;                  /*!< [0x0028] PHY Timing Registers 3 (PTR3)                                    */
    __IO uint32_t PTR4;                  /*!< [0x002c] PHY Timing Registers 4 (PTR4)                                    */
    __IO uint32_t ACMDLR;                /*!< [0x0030] AC Master Delay Line Register (ACMDLR)                           */
    __IO uint32_t ACBDLR;                /*!< [0x0034] AC Bit Delay Line Register (ACBDLR)                              */
    __IO uint32_t ACIOCR;                /*!< [0x0038] AC I/O Configuration Register (ACIOCR)                           */
    __IO uint32_t DXCCR;                 /*!< [0x003c] DATX8 Common Configuration Register (DXCCR)                      */
    __IO uint32_t DSGCR;                 /*!< [0x0040] DDR System General Configuration Register(DSGCR)                */
    __IO uint32_t DCR;                   /*!< [0x0044] DRAM Configuration Register (DCR)                                */
    __IO uint32_t DTPR0;                 /*!< [0x0048] DRAM Timing Parameters Register 0 (DTPR0) 105                    */
    __IO uint32_t DTPR1;                 /*!< [0x004c] DRAM Timing Parameters Register 1 (DTPR1)                        */
    __IO uint32_t DTPR2;                 /*!< [0x0050] DRAM Timing Parameters Register 2 (DTPR2)                        */
    __IO uint32_t MR0;                   /*!< [0x0054] Mode Register 0 (MR0)                                            */
    __IO uint32_t MR1;                   /*!< [0x0058] Mode Register 1 (MR1)                                            */
    __IO uint32_t MR2;                   /*!< [0x005c] Mode Register 2/Extended Mode Register 2 (MR2/EMR2)              */
    __IO uint32_t MR3;                   /*!< [0x0060] Mode Register 3 (MR3)                                            */
    __IO uint32_t ODTCR;                 /*!< [0x0064] ODT Configuration Register (ODTCR)                               */
    __IO uint32_t DTCR;                  /*!< [0x0068] Data Training Configuration Register (DTCR)                      */
    __IO uint32_t DTAR0;                 /*!< [0x006c] Data Training Address Register 0 (DTAR0)                         */
    __IO uint32_t DTAR1;                 /*!< [0x0070] Data Training Address Register 1 (DTAR1)                         */
    __IO uint32_t DTAR2;                 /*!< [0x0074] Data Training Address Register 2 (DTAR2)                         */
    __IO uint32_t DTAR3;                 /*!< [0x0078] Data Training Address Register 3 (DTAR3)                         */
    __IO uint32_t DTDR0;                 /*!< [0x007c] Data Training Data Register 0 (DTDR0)                            */
    __IO uint32_t DTDR1;                 /*!< [0x0080] Data Training Data Register 1 (DTDR1)                            */
    __I  uint32_t DTEDR0;                /*!< [0x0084] Data Training Eye Data Register 0 (DTEDR0)                       */
    __I  uint32_t DTEDR1;                /*!< [0x0088] Data Training Eye Data Register 1 (DTEDR1)                       */
    __IO uint32_t PGCR2;                 /*!< [0x008c] PHY General Configuration Register 2 (PGCR2)                     */
    __I  uint32_t RESERVE0[8];
    __I  uint32_t RDIMMGCR0;             /*!< [0x00b0] RDIMM General Configuration Register 0 (RDIMMGCR0)  123          */
    __I  uint32_t RDIMMGCR1;             /*!< [0x00b4] RDIMM General Configuration Register 1 (RDIMMGCR1)               */
    __I  uint32_t RDIMMCR0;              /*!< [0x00b8] RDIMM Control Register 0 (RDIMMCR0)                              */
    __I  uint32_t RDIMMCR1;              /*!< [0x00bc] RDIMM Control Register 1 (RDIMMCR1)                              */
    __IO uint32_t DCUAR;                 /*!< [0x00c0] DCU Address Register (DCUAR)                                     */
    __IO uint32_t DCUDR;                 /*!< [0x00c4] DCU Data Register (DCUDR)                                        */
    __IO uint32_t DCURR;                 /*!< [0x00c8] DCU Run Register (DCURR)                                         */
    __IO uint32_t DCULR;                 /*!< [0x00cc] DCU Loop Register (DCULR)                                        */
    __IO uint32_t DCUGCR;                /*!< [0x00d0] DCU General Configuration Register (DCUGCR)                      */
    __IO uint32_t DCUTPR;                /*!< [0x00d4] DCU Timing Parameter Register (DCUTPR)                           */
    __I  uint32_t DCUSR0;                /*!< [0x00d8] DCU Status Register 0 (DCUSR0)                                   */
    __I  uint32_t DCUSR1;                /*!< [0x00dc] DCU Status Register 1 (DCUSR1)                                   */
    __I  uint32_t RESERVE1[8];
    __IO uint32_t BISTRR;                /*!< [0x0100] BIST Run Register (BISTRR)                                       */
    __IO uint32_t BISTWCR;               /*!< [0x0104] BIST Word Count Register (BISTWCR)                               */
    __IO uint32_t BISTMSKR0;             /*!< [0x0108] BIST Mask Register 0 (BISTMSKR0)                                 */
    __IO uint32_t BISTMSKR1;             /*!< [0x010c] BIST Mask Register 1 (BISTMSKR1)                                 */
    __IO uint32_t BISTMSKR2;             /*!< [0x0110] BIST Mask Register 2 (BISTMSKR2)                                 */
    __IO uint32_t BISTLSR;               /*!< [0x0114] BIST LFSR Seed Register (BISTLSR)                                */
    __IO uint32_t BISTAR0;               /*!< [0x0118] BIST Address Register 0 (BISTAR0)                                */
    __IO uint32_t BISTAR1;               /*!< [0x011c] BIST Address Register 1 (BISTAR1)                                */
    __IO uint32_t BISTAR2;               /*!< [0x0120] BIST Address Register 2 (BISTAR2)                                */
    __IO uint32_t BISTUDPR;              /*!< [0x0124] BIST User Data Pattern Register (BISTUDPR)                       */
    __I  uint32_t BISTGSR;               /*!< [0x0128] BIST General Status Register (BISTGSR)                           */
    __I  uint32_t BISTWER;               /*!< [0x012c] BIST Word Error Register (BISTWER)                               */
    __I  uint32_t BISTBER0;              /*!< [0x0130] BIST Bit Error Register 0 (BISTBER0)                             */
    __I  uint32_t BISTBER1;              /*!< [0x0134] BIST Bit Error Register 1 (BISTBER1)                             */
    __I  uint32_t BISTBER2;              /*!< [0x0138] BIST Bit Error Register 2 (BISTBER2)                             */
    __I  uint32_t BISTBER3;              /*!< [0x013c] BIST Bit Error Register 3 (BISTBER3)                             */
    __I  uint32_t BISTWCSR;              /*!< [0x0140] BIST Word Count Status Register (BISTWCSR)                       */
    __I  uint32_t BISTFWR0;              /*!< [0x0144] BIST Fail Word Register 0 (BISTFWR0)                             */
    __I  uint32_t BISTFWR1;              /*!< [0x0148] BIST Fail Word Register 1 (BISTFWR1)                             */
    __I  uint32_t BISTFWR2;              /*!< [0x014c] BIST Fail Word Register 2 (BISTFWR2)                             */
    __I  uint32_t RESERVE2[9];
    __IO uint32_t AACR;                  /*!< [0x0174] Anti-Aging Control Register (AACR)                               */
    __IO uint32_t GPR0;                  /*!< [0x0178] General Purpose Register 0 (GPR0)                                */
    __IO uint32_t GPR1;                  /*!< [0x017c] General Purpose Register 1 (GPR1)                                */
    __IO uint32_t ZQ0CR0;                /*!< [0x0180] Impedance Control Register 0 (ZQnCR0)                            */
    __IO uint32_t ZQ0CR1;                /*!< [0x0184] Impedance Control Register 1 (ZQnCR1)                            */
    __I  uint32_t ZQ0SR0;                /*!< [0x0188] Impedance Status Register 0 (ZQnSR0)                             */
    __I  uint32_t ZQ0SR1;                /*!< [0x018c] Impedance Status Register 1 (ZQnSR1)                             */
    __IO uint32_t ZQ1CR0;                /*!< [0x0190] Impedance Control Register 0 (ZQnCR0)                            */
    __IO uint32_t ZQ1CR1;                /*!< [0x0194] Impedance Control Register 1 (ZQnCR1)                            */
    __I  uint32_t ZQ1SR0;                /*!< [0x0198] Impedance Status Register 0 (ZQnSR0)                             */
    __I  uint32_t ZQ1SR1;                /*!< [0x019c] Impedance Status Register 1 (ZQnSR1)                             */
    __IO uint32_t ZQ2CR0;                /*!< [0x01a0] Impedance Control Register 0 (ZQnCR0)                            */
    __IO uint32_t ZQ2CR1;                /*!< [0x01a4] Impedance Control Register 1 (ZQnCR1)                            */
    __I  uint32_t ZQ2SR0;                /*!< [0x01a8] Impedance Status Register 0 (ZQnSR0)                             */
    __I  uint32_t ZQ2SR1;                /*!< [0x01ac] Impedance Status Register 1 (ZQnSR1)                             */
    __IO uint32_t ZQ3CR0;                /*!< [0x01b0] Impedance Control Register 0 (ZQnCR0)                            */
    __IO uint32_t ZQ3CR1;                /*!< [0x01b4] Impedance Control Register 1 (ZQnCR1)                            */
    __I  uint32_t ZQ3SR0;                /*!< [0x01b8] Impedance Status Register 0 (ZQnSR0)                             */
    __I  uint32_t ZQ3SR1;                /*!< [0x01bc] Impedance Status Register 1 (ZQnSR1)                             */
    __IO uint32_t DX0GCR;                /*!< [0x01c0] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX0GSR0;               /*!< [0x01c4] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX0GSR1;               /*!< [0x01c8] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX0BDLR0;              /*!< [0x01cc] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX0BDLR1;              /*!< [0x01d0] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX0BDLR2;              /*!< [0x01d4] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX0BDLR3;              /*!< [0x01d8] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX0BDLR4;              /*!< [0x01dc] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX0LCDLR0;             /*!< [0x01e0] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX0LCDLR1;             /*!< [0x01e4] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX0LCDLR2;             /*!< [0x01e8] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX0MDLR;               /*!< [0x01ec] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX0GTR;                /*!< [0x01f0] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX0GSR2;               /*!< [0x01f4] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE3[2];
    __IO uint32_t DX1GCR;                /*!< [0x0200] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX1GSR0;               /*!< [0x0204] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX1GSR1;               /*!< [0x0208] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX1BDLR0;              /*!< [0x020c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX1BDLR1;              /*!< [0x0210] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX1BDLR2;              /*!< [0x0214] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX1BDLR3;              /*!< [0x0218] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX1BDLR4;              /*!< [0x021c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX1LCDLR0;             /*!< [0x0220] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX1LCDLR1;             /*!< [0x0224] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX1LCDLR2;             /*!< [0x0228] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX1MDLR;               /*!< [0x022c] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX1GTR;                /*!< [0x0230] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX1GSR2;               /*!< [0x0234] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE4[2];
    __IO uint32_t DX2GCR;                /*!< [0x0240] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX2GSR0;               /*!< [0x0244] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX2GSR1;               /*!< [0x0248] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX2BDLR0;              /*!< [0x024c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX2BDLR1;              /*!< [0x0250] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX2BDLR2;              /*!< [0x0254] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX2BDLR3;              /*!< [0x0258] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX2BDLR4;              /*!< [0x025c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX2LCDLR0;             /*!< [0x0260] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX2LCDLR1;             /*!< [0x0264] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX2LCDLR2;             /*!< [0x0268] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX2MDLR;               /*!< [0x026c] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX2GTR;                /*!< [0x0270] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX2GSR2;               /*!< [0x0274] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE5[2];
    __IO uint32_t DX3GCR;                /*!< [0x0280] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX3GSR0;               /*!< [0x0284] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX3GSR1;               /*!< [0x0288] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX3BDLR0;              /*!< [0x028c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX3BDLR1;              /*!< [0x0290] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX3BDLR2;              /*!< [0x0294] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX3BDLR3;              /*!< [0x0298] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX3BDLR4;              /*!< [0x029c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX3LCDLR0;             /*!< [0x02a0] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX3LCDLR1;             /*!< [0x02a4] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX3LCDLR2;             /*!< [0x02a8] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX3MDLR;               /*!< [0x02ac] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX3GTR;                /*!< [0x02b0] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX3GSR2;               /*!< [0x02b4] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE6[2];
    __IO uint32_t DX4GCR;                /*!< [0x02c0] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX4GSR0;               /*!< [0x02c4] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX4GSR1;               /*!< [0x02c8] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX4BDLR0;              /*!< [0x02cc] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX4BDLR1;              /*!< [0x02d0] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX4BDLR2;              /*!< [0x02d4] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX4BDLR3;              /*!< [0x02d8] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX4BDLR4;              /*!< [0x02dc] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX4LCDLR0;             /*!< [0x02e0] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX4LCDLR1;             /*!< [0x02e4] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX4LCDLR2;             /*!< [0x02e8] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX4MDLR;               /*!< [0x02ec] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX4GTR;                /*!< [0x02f0] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX4GSR2;               /*!< [0x02f4] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE7[2];
    __IO uint32_t DX5GCR;                /*!< [0x0300] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX5GSR0;               /*!< [0x0304] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX5GSR1;               /*!< [0x0308] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX5BDLR0;              /*!< [0x030c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX5BDLR1;              /*!< [0x0310] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX5BDLR2;              /*!< [0x0314] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX5BDLR3;              /*!< [0x0318] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX5BDLR4;              /*!< [0x031c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX5LCDLR0;             /*!< [0x0320] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX5LCDLR1;             /*!< [0x0324] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX5LCDLR2;             /*!< [0x0328] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX5MDLR;               /*!< [0x032c] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX5GTR;                /*!< [0x0330] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX5GSR2;               /*!< [0x0334] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE8[2];
    __IO uint32_t DX6GCR;                /*!< [0x0340] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX6GSR0;               /*!< [0x0344] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX6GSR1;               /*!< [0x0348] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX6BDLR0;              /*!< [0x034c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX6BDLR1;              /*!< [0x0350] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX6BDLR2;              /*!< [0x0354] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX6BDLR3;              /*!< [0x0358] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX6BDLR4;              /*!< [0x035c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX6LCDLR0;             /*!< [0x0360] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX6LCDLR1;             /*!< [0x0364] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX6LCDLR2;             /*!< [0x0368] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX6MDLR;               /*!< [0x036c] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX6GTR;                /*!< [0x0370] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX6GSR2;               /*!< [0x0374] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE9[2];
    __IO uint32_t DX7GCR;                /*!< [0x0380] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX7GSR0;               /*!< [0x0384] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX7GSR1;               /*!< [0x0388] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX7BDLR0;              /*!< [0x038c] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX7BDLR1;              /*!< [0x0390] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX7BDLR2;              /*!< [0x0394] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX7BDLR3;              /*!< [0x0398] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX7BDLR4;              /*!< [0x039c] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX7LCDLR0;             /*!< [0x03a0] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX7LCDLR1;             /*!< [0x03a4] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX7LCDLR2;             /*!< [0x03a8] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX7MDLR;               /*!< [0x03ac] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX7GTR;                /*!< [0x03b0] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX7GSR2;               /*!< [0x03b4] DATX8 General Status Register 2 (DXnGSR2)                        */
    __I  uint32_t RESERVE10[2];
    __IO uint32_t DX8GCR;                /*!< [0x03c0] DATX8 General Configuration Register (DXnGCR)                    */
    __I  uint32_t DX8GSR0;               /*!< [0x03c4] DATX8 General Status Registers 0 (DXnGSR0)                       */
    __I  uint32_t DX8GSR1;               /*!< [0x03c8] DATX8 General Status Registers 1 (DXnGSR1)                       */
    __IO uint32_t DX8BDLR0;              /*!< [0x03cc] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX8BDLR1;              /*!< [0x03d0] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX8BDLR2;              /*!< [0x03d4] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX8BDLR3;              /*!< [0x03d8] DATX8 Bit Delay Line Register 3 (DXnBDLR3)                       */
    __IO uint32_t DX8BDLR4;              /*!< [0x03dc] DATX8 Bit Delay Line Register 4 (DXnBDLR4)                       */
    __IO uint32_t DX8LCDLR0;             /*!< [0x03e0] DATX8 Bit Delay Line Register 0 (DXnBDLR0)                       */
    __IO uint32_t DX8LCDLR1;             /*!< [0x03e4] DATX8 Bit Delay Line Register 1 (DXnBDLR1)                       */
    __IO uint32_t DX8LCDLR2;             /*!< [0x03e8] DATX8 Bit Delay Line Register 2 (DXnBDLR2)                       */
    __IO uint32_t DX8MDLR;               /*!< [0x03ec] DATX8 Master Delay Line Register (DXnMDLR)                       */
    __IO uint32_t DX8GTR;                /*!< [0x03f0] DATX8 General Timing Register (DXnGTR)                           */
    __IO uint32_t DX8GSR2;               /*!< [0x03f4] DATX8 General Status Register 2 (DXnGSR2)                        */

} DDRPHY_T;

/**
    @addtogroup DDRPHY_CONST DDRPHY Bit Field Definition
    Constant Definitions for DDRPHY Controller
@{ */

#define DDRPHY_RIDR_PUBMNR_Pos           (0)                                               /*!< DDRPHY_T::RIDR: PUBMNR Position        */
#define DDRPHY_RIDR_PUBMNR_Msk           (0xful << DDRPHY_RIDR_PUBMNR_Pos)                 /*!< DDRPHY_T::RIDR: PUBMNR Mask            */

#define DDRPHY_RIDR_PUBMDR_Pos           (4)                                               /*!< DDRPHY_T::RIDR: PUBMDR Position        */
#define DDRPHY_RIDR_PUBMDR_Msk           (0xful << DDRPHY_RIDR_PUBMDR_Pos)                 /*!< DDRPHY_T::RIDR: PUBMDR Mask            */

#define DDRPHY_RIDR_PUBMJR_Pos           (8)                                               /*!< DDRPHY_T::RIDR: PUBMJR Position        */
#define DDRPHY_RIDR_PUBMJR_Msk           (0xful << DDRPHY_RIDR_PUBMJR_Pos)                 /*!< DDRPHY_T::RIDR: PUBMJR Mask            */

#define DDRPHY_RIDR_PHYMNR_Pos           (12)                                              /*!< DDRPHY_T::RIDR: PHYMNR Position        */
#define DDRPHY_RIDR_PHYMNR_Msk           (0xful << DDRPHY_RIDR_PHYMNR_Pos)                 /*!< DDRPHY_T::RIDR: PHYMNR Mask            */

#define DDRPHY_RIDR_PHYMDR_Pos           (16)                                              /*!< DDRPHY_T::RIDR: PHYMDR Position        */
#define DDRPHY_RIDR_PHYMDR_Msk           (0xful << DDRPHY_RIDR_PHYMDR_Pos)                 /*!< DDRPHY_T::RIDR: PHYMDR Mask            */

#define DDRPHY_RIDR_PHYMJR_Pos           (20)                                              /*!< DDRPHY_T::RIDR: PHYMJR Position        */
#define DDRPHY_RIDR_PHYMJR_Msk           (0xful << DDRPHY_RIDR_PHYMJR_Pos)                 /*!< DDRPHY_T::RIDR: PHYMJR Mask            */

#define DDRPHY_RIDR_UDRID_Pos            (24)                                              /*!< DDRPHY_T::RIDR: UDRID Position         */
#define DDRPHY_RIDR_UDRID_Msk            (0xfful << DDRPHY_RIDR_UDRID_Pos)                 /*!< DDRPHY_T::RIDR: UDRID Mask             */

#define DDRPHY_PIR_INIT_Pos              (0)                                               /*!< DDRPHY_T::PIR: INIT Position           */
#define DDRPHY_PIR_INIT_Msk              (0x1ul << DDRPHY_PIR_INIT_Pos)                    /*!< DDRPHY_T::PIR: INIT Mask               */

#define DDRPHY_PIR_ZCAL_Pos              (1)                                               /*!< DDRPHY_T::PIR: ZCAL Position           */
#define DDRPHY_PIR_ZCAL_Msk              (0x1ul << DDRPHY_PIR_ZCAL_Pos)                    /*!< DDRPHY_T::PIR: ZCAL Mask               */

#define DDRPHY_PIR_PLLINIT_Pos           (4)                                               /*!< DDRPHY_T::PIR: PLLINIT Position        */
#define DDRPHY_PIR_PLLINIT_Msk           (0x1ul << DDRPHY_PIR_PLLINIT_Pos)                 /*!< DDRPHY_T::PIR: PLLINIT Mask            */

#define DDRPHY_PIR_DCAL_Pos              (5)                                               /*!< DDRPHY_T::PIR: DCAL Position           */
#define DDRPHY_PIR_DCAL_Msk              (0x1ul << DDRPHY_PIR_DCAL_Pos)                    /*!< DDRPHY_T::PIR: DCAL Mask               */

#define DDRPHY_PIR_PHYRST_Pos            (6)                                               /*!< DDRPHY_T::PIR: PHYRST Position         */
#define DDRPHY_PIR_PHYRST_Msk            (0x1ul << DDRPHY_PIR_PHYRST_Pos)                  /*!< DDRPHY_T::PIR: PHYRST Mask             */

#define DDRPHY_PIR_DRAMRST_Pos           (7)                                               /*!< DDRPHY_T::PIR: DRAMRST Position        */
#define DDRPHY_PIR_DRAMRST_Msk           (0x1ul << DDRPHY_PIR_DRAMRST_Pos)                 /*!< DDRPHY_T::PIR: DRAMRST Mask            */

#define DDRPHY_PIR_DRAMINIT_Pos          (8)                                               /*!< DDRPHY_T::PIR: DRAMINIT Position       */
#define DDRPHY_PIR_DRAMINIT_Msk          (0x1ul << DDRPHY_PIR_DRAMINIT_Pos)                /*!< DDRPHY_T::PIR: DRAMINIT Mask           */

#define DDRPHY_PIR_WL_Pos                (9)                                               /*!< DDRPHY_T::PIR: WL Position             */
#define DDRPHY_PIR_WL_Msk                (0x1ul << DDRPHY_PIR_WL_Pos)                      /*!< DDRPHY_T::PIR: WL Mask                 */

#define DDRPHY_PIR_QSGATE_Pos            (10)                                              /*!< DDRPHY_T::PIR: QSGATE Position         */
#define DDRPHY_PIR_QSGATE_Msk            (0x1ul << DDRPHY_PIR_QSGATE_Pos)                  /*!< DDRPHY_T::PIR: QSGATE Mask             */

#define DDRPHY_PIR_WLADJ_Pos             (11)                                              /*!< DDRPHY_T::PIR: WLADJ Position          */
#define DDRPHY_PIR_WLADJ_Msk             (0x1ul << DDRPHY_PIR_WLADJ_Pos)                   /*!< DDRPHY_T::PIR: WLADJ Mask              */

#define DDRPHY_PIR_RDDSKW_Pos            (12)                                              /*!< DDRPHY_T::PIR: RDDSKW Position         */
#define DDRPHY_PIR_RDDSKW_Msk            (0x1ul << DDRPHY_PIR_RDDSKW_Pos)                  /*!< DDRPHY_T::PIR: RDDSKW Mask             */

#define DDRPHY_PIR_WRDSKW_Pos            (13)                                              /*!< DDRPHY_T::PIR: WRDSKW Position         */
#define DDRPHY_PIR_WRDSKW_Msk            (0x1ul << DDRPHY_PIR_WRDSKW_Pos)                  /*!< DDRPHY_T::PIR: WRDSKW Mask             */

#define DDRPHY_PIR_RDEYE_Pos             (14)                                              /*!< DDRPHY_T::PIR: RDEYE Position          */
#define DDRPHY_PIR_RDEYE_Msk             (0x1ul << DDRPHY_PIR_RDEYE_Pos)                   /*!< DDRPHY_T::PIR: RDEYE Mask              */

#define DDRPHY_PIR_WREYE_Pos             (15)                                              /*!< DDRPHY_T::PIR: WREYE Position          */
#define DDRPHY_PIR_WREYE_Msk             (0x1ul << DDRPHY_PIR_WREYE_Pos)                   /*!< DDRPHY_T::PIR: WREYE Mask              */

#define DDRPHY_PIR_ICPC_Pos              (16)                                              /*!< DDRPHY_T::PIR: ICPC Position           */
#define DDRPHY_PIR_ICPC_Msk              (0x1ul << DDRPHY_PIR_ICPC_Pos)                    /*!< DDRPHY_T::PIR: ICPC Mask               */

#define DDRPHY_PIR_PLLBYP_Pos            (17)                                              /*!< DDRPHY_T::PIR: PLLBYP Position         */
#define DDRPHY_PIR_PLLBYP_Msk            (0x1ul << DDRPHY_PIR_PLLBYP_Pos)                  /*!< DDRPHY_T::PIR: PLLBYP Mask             */

#define DDRPHY_PIR_CTLDINIT_Pos          (18)                                              /*!< DDRPHY_T::PIR: CTLDINIT Position       */
#define DDRPHY_PIR_CTLDINIT_Msk          (0x1ul << DDRPHY_PIR_CTLDINIT_Pos)                /*!< DDRPHY_T::PIR: CTLDINIT Mask           */

#define DDRPHY_PIR_RDIMMINIT_Pos         (19)                                              /*!< DDRPHY_T::PIR: RDIMMINIT Position      */
#define DDRPHY_PIR_RDIMMINIT_Msk         (0x1ul << DDRPHY_PIR_RDIMMINIT_Pos)               /*!< DDRPHY_T::PIR: RDIMMINIT Mask          */

#define DDRPHY_PIR_CLRSR_Pos             (27)                                              /*!< DDRPHY_T::PIR: CLRSR Position          */
#define DDRPHY_PIR_CLRSR_Msk             (0x1ul << DDRPHY_PIR_CLRSR_Pos)                   /*!< DDRPHY_T::PIR: CLRSR Mask              */

#define DDRPHY_PIR_LOCKBYP_Pos           (28)                                              /*!< DDRPHY_T::PIR: LOCKBYP Position        */
#define DDRPHY_PIR_LOCKBYP_Msk           (0x1ul << DDRPHY_PIR_LOCKBYP_Pos)                 /*!< DDRPHY_T::PIR: LOCKBYP Mask            */

#define DDRPHY_PIR_DCALBYP_Pos           (29)                                              /*!< DDRPHY_T::PIR: DCALBYP Position        */
#define DDRPHY_PIR_DCALBYP_Msk           (0x1ul << DDRPHY_PIR_DCALBYP_Pos)                 /*!< DDRPHY_T::PIR: DCALBYP Mask            */

#define DDRPHY_PIR_ZCALBYP_Pos           (30)                                              /*!< DDRPHY_T::PIR: ZCALBYP Position        */
#define DDRPHY_PIR_ZCALBYP_Msk           (0x1ul << DDRPHY_PIR_ZCALBYP_Pos)                 /*!< DDRPHY_T::PIR: ZCALBYP Mask            */

#define DDRPHY_PIR_INITBYP_Pos           (31)                                              /*!< DDRPHY_T::PIR: INITBYP Position        */
#define DDRPHY_PIR_INITBYP_Msk           (0x1ul << DDRPHY_PIR_INITBYP_Pos)                 /*!< DDRPHY_T::PIR: INITBYP Mask            */

#define DDRPHY_PGCR0_WLLVT_Pos           (0)                                               /*!< DDRPHY_T::PGCR0: WLLVT Position        */
#define DDRPHY_PGCR0_WLLVT_Msk           (0x1ul << DDRPHY_PGCR0_WLLVT_Pos)                 /*!< DDRPHY_T::PGCR0: WLLVT Mask            */

#define DDRPHY_PGCR0_WDLVT_Pos           (1)                                               /*!< DDRPHY_T::PGCR0: WDLVT Position        */
#define DDRPHY_PGCR0_WDLVT_Msk           (0x1ul << DDRPHY_PGCR0_WDLVT_Pos)                 /*!< DDRPHY_T::PGCR0: WDLVT Mask            */

#define DDRPHY_PGCR0_RDLVT_Pos           (2)                                               /*!< DDRPHY_T::PGCR0: RDLVT Position        */
#define DDRPHY_PGCR0_RDLVT_Msk           (0x1ul << DDRPHY_PGCR0_RDLVT_Pos)                 /*!< DDRPHY_T::PGCR0: RDLVT Mask            */

#define DDRPHY_PGCR0_RGLVT_Pos           (3)                                               /*!< DDRPHY_T::PGCR0: RGLVT Position        */
#define DDRPHY_PGCR0_RGLVT_Msk           (0x1ul << DDRPHY_PGCR0_RGLVT_Pos)                 /*!< DDRPHY_T::PGCR0: RGLVT Mask            */

#define DDRPHY_PGCR0_WDBVT_Pos           (4)                                               /*!< DDRPHY_T::PGCR0: WDBVT Position        */
#define DDRPHY_PGCR0_WDBVT_Msk           (0x1ul << DDRPHY_PGCR0_WDBVT_Pos)                 /*!< DDRPHY_T::PGCR0: WDBVT Mask            */

#define DDRPHY_PGCR0_RDBVT_Pos           (5)                                               /*!< DDRPHY_T::PGCR0: RDBVT Position        */
#define DDRPHY_PGCR0_RDBVT_Msk           (0x1ul << DDRPHY_PGCR0_RDBVT_Pos)                 /*!< DDRPHY_T::PGCR0: RDBVT Mask            */

#define DDRPHY_PGCR0_DLTMODE_Pos         (6)                                               /*!< DDRPHY_T::PGCR0: DLTMODE Position      */
#define DDRPHY_PGCR0_DLTMODE_Msk         (0x1ul << DDRPHY_PGCR0_DLTMODE_Pos)               /*!< DDRPHY_T::PGCR0: DLTMODE Mask          */

#define DDRPHY_PGCR0_DLTST_Pos           (7)                                               /*!< DDRPHY_T::PGCR0: DLTST Position        */
#define DDRPHY_PGCR0_DLTST_Msk           (0x1ul << DDRPHY_PGCR0_DLTST_Pos)                 /*!< DDRPHY_T::PGCR0: DLTST Mask            */

#define DDRPHY_PGCR0_OSCEN_Pos           (8)                                               /*!< DDRPHY_T::PGCR0: OSCEN Position        */
#define DDRPHY_PGCR0_OSCEN_Msk           (0x1ul << DDRPHY_PGCR0_OSCEN_Pos)                 /*!< DDRPHY_T::PGCR0: OSCEN Mask            */

#define DDRPHY_PGCR0_OSCDIV_Pos          (9)                                               /*!< DDRPHY_T::PGCR0: OSCDIV Position       */
#define DDRPHY_PGCR0_OSCDIV_Msk          (0x7ul << DDRPHY_PGCR0_OSCDIV_Pos)                /*!< DDRPHY_T::PGCR0: OSCDIV Mask           */

#define DDRPHY_PGCR0_OSCWDL_Pos          (12)                                              /*!< DDRPHY_T::PGCR0: OSCWDL Position       */
#define DDRPHY_PGCR0_OSCWDL_Msk          (0x3ul << DDRPHY_PGCR0_OSCWDL_Pos)                /*!< DDRPHY_T::PGCR0: OSCWDL Mask           */

#define DDRPHY_PGCR0_DTOSEL_Pos          (14)                                              /*!< DDRPHY_T::PGCR0: DTOSEL Position       */
#define DDRPHY_PGCR0_DTOSEL_Msk          (0x1ful << DDRPHY_PGCR0_DTOSEL_Pos)               /*!< DDRPHY_T::PGCR0: DTOSEL Mask           */

#define DDRPHY_PGCR0_PUBMODE_Pos         (25)                                              /*!< DDRPHY_T::PGCR0: PUBMODE Position      */
#define DDRPHY_PGCR0_PUBMODE_Msk         (0x1ul << DDRPHY_PGCR0_PUBMODE_Pos)               /*!< DDRPHY_T::PGCR0: PUBMODE Mask          */

#define DDRPHY_PGCR0_CKEN_Pos            (26)                                              /*!< DDRPHY_T::PGCR0: CKEN Position         */
#define DDRPHY_PGCR0_CKEN_Msk            (0x3ful << DDRPHY_PGCR0_CKEN_Pos)                 /*!< DDRPHY_T::PGCR0: CKEN Mask             */

#define DDRPHY_PGCR1_PDDISDX_Pos         (0)                                               /*!< DDRPHY_T::PGCR1: PDDISDX Position      */
#define DDRPHY_PGCR1_PDDISDX_Msk         (0x1ul << DDRPHY_PGCR1_PDDISDX_Pos)               /*!< DDRPHY_T::PGCR1: PDDISDX Mask          */

#define DDRPHY_PGCR1_WLMODE_Pos          (1)                                               /*!< DDRPHY_T::PGCR1: WLMODE Position       */
#define DDRPHY_PGCR1_WLMODE_Msk          (0x1ul << DDRPHY_PGCR1_WLMODE_Pos)                /*!< DDRPHY_T::PGCR1: WLMODE Mask           */

#define DDRPHY_PGCR1_WLSTEP_Pos          (2)                                               /*!< DDRPHY_T::PGCR1: WLSTEP Position       */
#define DDRPHY_PGCR1_WLSTEP_Msk          (0x1ul << DDRPHY_PGCR1_WLSTEP_Pos)                /*!< DDRPHY_T::PGCR1: WLSTEP Mask           */

#define DDRPHY_PGCR1_WSLOPT_Pos          (4)                                               /*!< DDRPHY_T::PGCR1: WSLOPT Position       */
#define DDRPHY_PGCR1_WSLOPT_Msk          (0x1ul << DDRPHY_PGCR1_WSLOPT_Pos)                /*!< DDRPHY_T::PGCR1: WSLOPT Mask           */

#define DDRPHY_PGCR1_ACHRST_Pos          (5)                                               /*!< DDRPHY_T::PGCR1: ACHRST Position       */
#define DDRPHY_PGCR1_ACHRST_Msk          (0x1ul << DDRPHY_PGCR1_ACHRST_Pos)                /*!< DDRPHY_T::PGCR1: ACHRST Mask           */

#define DDRPHY_PGCR1_WLSELT_Pos          (6)                                               /*!< DDRPHY_T::PGCR1: WLSELT Position       */
#define DDRPHY_PGCR1_WLSELT_Msk          (0x1ul << DDRPHY_PGCR1_WLSELT_Pos)                /*!< DDRPHY_T::PGCR1: WLSELT Mask           */

#define DDRPHY_PGCR1_IODDRM_Pos          (7)                                               /*!< DDRPHY_T::PGCR1: IODDRM Position       */
#define DDRPHY_PGCR1_IODDRM_Msk          (0x3ul << DDRPHY_PGCR1_IODDRM_Pos)                /*!< DDRPHY_T::PGCR1: IODDRM Mask           */

#define DDRPHY_PGCR1_MDLEN_Pos           (9)                                               /*!< DDRPHY_T::PGCR1: MDLEN Position        */
#define DDRPHY_PGCR1_MDLEN_Msk           (0x1ul << DDRPHY_PGCR1_MDLEN_Pos)                 /*!< DDRPHY_T::PGCR1: MDLEN Mask            */

#define DDRPHY_PGCR1_LPFEN_Pos           (10)                                              /*!< DDRPHY_T::PGCR1: LPFEN Position        */
#define DDRPHY_PGCR1_LPFEN_Msk           (0x1ul << DDRPHY_PGCR1_LPFEN_Pos)                 /*!< DDRPHY_T::PGCR1: LPFEN Mask            */

#define DDRPHY_PGCR1_LPFDEPTH_Pos        (11)                                              /*!< DDRPHY_T::PGCR1: LPFDEPTH Position     */
#define DDRPHY_PGCR1_LPFDEPTH_Msk        (0x3ul << DDRPHY_PGCR1_LPFDEPTH_Pos)              /*!< DDRPHY_T::PGCR1: LPFDEPTH Mask         */

#define DDRPHY_PGCR1_FDEPTH_Pos          (13)                                              /*!< DDRPHY_T::PGCR1: FDEPTH Position       */
#define DDRPHY_PGCR1_FDEPTH_Msk          (0x3ul << DDRPHY_PGCR1_FDEPTH_Pos)                /*!< DDRPHY_T::PGCR1: FDEPTH Mask           */

#define DDRPHY_PGCR1_DLDLMT_Pos          (15)                                              /*!< DDRPHY_T::PGCR1: DLDLMT Position       */
#define DDRPHY_PGCR1_DLDLMT_Msk          (0xfful << DDRPHY_PGCR1_DLDLMT_Pos)               /*!< DDRPHY_T::PGCR1: DLDLMT Mask           */

#define DDRPHY_PGCR1_ZCKSEL_Pos          (23)                                              /*!< DDRPHY_T::PGCR1: ZCKSEL Position       */
#define DDRPHY_PGCR1_ZCKSEL_Msk          (0x3ul << DDRPHY_PGCR1_ZCKSEL_Pos)                /*!< DDRPHY_T::PGCR1: ZCKSEL Mask           */

#define DDRPHY_PGCR1_DXHRST_Pos          (25)                                              /*!< DDRPHY_T::PGCR1: DXHRST Position       */
#define DDRPHY_PGCR1_DXHRST_Msk          (0x1ul << DDRPHY_PGCR1_DXHRST_Pos)                /*!< DDRPHY_T::PGCR1: DXHRST Mask           */

#define DDRPHY_PGCR1_INHVT_Pos           (26)                                              /*!< DDRPHY_T::PGCR1: INHVT Position        */
#define DDRPHY_PGCR1_INHVT_Msk           (0x1ul << DDRPHY_PGCR1_INHVT_Pos)                 /*!< DDRPHY_T::PGCR1: INHVT Mask            */

#define DDRPHY_PGCR1_IOLB_Pos            (27)                                              /*!< DDRPHY_T::PGCR1: IOLB Position         */
#define DDRPHY_PGCR1_IOLB_Msk            (0x1ul << DDRPHY_PGCR1_IOLB_Pos)                  /*!< DDRPHY_T::PGCR1: IOLB Mask             */

#define DDRPHY_PGCR1_LBDQSS_Pos          (28)                                              /*!< DDRPHY_T::PGCR1: LBDQSS Position       */
#define DDRPHY_PGCR1_LBDQSS_Msk          (0x1ul << DDRPHY_PGCR1_LBDQSS_Pos)                /*!< DDRPHY_T::PGCR1: LBDQSS Mask           */

#define DDRPHY_PGCR1_LBGDQS_Pos          (29)                                              /*!< DDRPHY_T::PGCR1: LBGDQS Position       */
#define DDRPHY_PGCR1_LBGDQS_Msk          (0x3ul << DDRPHY_PGCR1_LBGDQS_Pos)                /*!< DDRPHY_T::PGCR1: LBGDQS Mask           */

#define DDRPHY_PGCR1_LBMODE_Pos          (31)                                              /*!< DDRPHY_T::PGCR1: LBMODE Position       */
#define DDRPHY_PGCR1_LBMODE_Msk          (0x1ul << DDRPHY_PGCR1_LBMODE_Pos)                /*!< DDRPHY_T::PGCR1: LBMODE Mask           */

#define DDRPHY_PGSR0_IDONE_Pos           (0)                                               /*!< DDRPHY_T::PGSR0: IDONE Position        */
#define DDRPHY_PGSR0_IDONE_Msk           (0x1ul << DDRPHY_PGSR0_IDONE_Pos)                 /*!< DDRPHY_T::PGSR0: IDONE Mask            */

#define DDRPHY_PGSR0_PLDONE_Pos          (1)                                               /*!< DDRPHY_T::PGSR0: PLDONE Position       */
#define DDRPHY_PGSR0_PLDONE_Msk          (0x1ul << DDRPHY_PGSR0_PLDONE_Pos)                /*!< DDRPHY_T::PGSR0: PLDONE Mask           */

#define DDRPHY_PGSR0_DCDONE_Pos          (2)                                               /*!< DDRPHY_T::PGSR0: DCDONE Position       */
#define DDRPHY_PGSR0_DCDONE_Msk          (0x1ul << DDRPHY_PGSR0_DCDONE_Pos)                /*!< DDRPHY_T::PGSR0: DCDONE Mask           */

#define DDRPHY_PGSR0_ZCDONE_Pos          (3)                                               /*!< DDRPHY_T::PGSR0: ZCDONE Position       */
#define DDRPHY_PGSR0_ZCDONE_Msk          (0x1ul << DDRPHY_PGSR0_ZCDONE_Pos)                /*!< DDRPHY_T::PGSR0: ZCDONE Mask           */

#define DDRPHY_PGSR0_DIDONE_Pos          (4)                                               /*!< DDRPHY_T::PGSR0: DIDONE Position       */
#define DDRPHY_PGSR0_DIDONE_Msk          (0x1ul << DDRPHY_PGSR0_DIDONE_Pos)                /*!< DDRPHY_T::PGSR0: DIDONE Mask           */

#define DDRPHY_PGSR0_WLDONE_Pos          (5)                                               /*!< DDRPHY_T::PGSR0: WLDONE Position       */
#define DDRPHY_PGSR0_WLDONE_Msk          (0x1ul << DDRPHY_PGSR0_WLDONE_Pos)                /*!< DDRPHY_T::PGSR0: WLDONE Mask           */

#define DDRPHY_PGSR0_QSGDONE_Pos         (6)                                               /*!< DDRPHY_T::PGSR0: QSGDONE Position      */
#define DDRPHY_PGSR0_QSGDONE_Msk         (0x1ul << DDRPHY_PGSR0_QSGDONE_Pos)               /*!< DDRPHY_T::PGSR0: QSGDONE Mask          */

#define DDRPHY_PGSR0_WLADONE_Pos         (7)                                               /*!< DDRPHY_T::PGSR0: WLADONE Position      */
#define DDRPHY_PGSR0_WLADONE_Msk         (0x1ul << DDRPHY_PGSR0_WLADONE_Pos)               /*!< DDRPHY_T::PGSR0: WLADONE Mask          */

#define DDRPHY_PGSR0_RDDONE_Pos          (8)                                               /*!< DDRPHY_T::PGSR0: RDDONE Position       */
#define DDRPHY_PGSR0_RDDONE_Msk          (0x1ul << DDRPHY_PGSR0_RDDONE_Pos)                /*!< DDRPHY_T::PGSR0: RDDONE Mask           */

#define DDRPHY_PGSR0_WDDONE_Pos          (9)                                               /*!< DDRPHY_T::PGSR0: WDDONE Position       */
#define DDRPHY_PGSR0_WDDONE_Msk          (0x1ul << DDRPHY_PGSR0_WDDONE_Pos)                /*!< DDRPHY_T::PGSR0: WDDONE Mask           */

#define DDRPHY_PGSR0_REDONE_Pos          (10)                                              /*!< DDRPHY_T::PGSR0: REDONE Position       */
#define DDRPHY_PGSR0_REDONE_Msk          (0x1ul << DDRPHY_PGSR0_REDONE_Pos)                /*!< DDRPHY_T::PGSR0: REDONE Mask           */

#define DDRPHY_PGSR0_WEDONE_Pos          (11)                                              /*!< DDRPHY_T::PGSR0: WEDONE Position       */
#define DDRPHY_PGSR0_WEDONE_Msk          (0x1ul << DDRPHY_PGSR0_WEDONE_Pos)                /*!< DDRPHY_T::PGSR0: WEDONE Mask           */

#define DDRPHY_PGSR0_ZCERR_Pos           (20)                                              /*!< DDRPHY_T::PGSR0: ZCERR Position        */
#define DDRPHY_PGSR0_ZCERR_Msk           (0x1ul << DDRPHY_PGSR0_ZCERR_Pos)                 /*!< DDRPHY_T::PGSR0: ZCERR Mask            */

#define DDRPHY_PGSR0_WLERR_Pos           (21)                                              /*!< DDRPHY_T::PGSR0: WLERR Position        */
#define DDRPHY_PGSR0_WLERR_Msk           (0x1ul << DDRPHY_PGSR0_WLERR_Pos)                 /*!< DDRPHY_T::PGSR0: WLERR Mask            */

#define DDRPHY_PGSR0_QSGERR_Pos          (22)                                              /*!< DDRPHY_T::PGSR0: QSGERR Position       */
#define DDRPHY_PGSR0_QSGERR_Msk          (0x1ul << DDRPHY_PGSR0_QSGERR_Pos)                /*!< DDRPHY_T::PGSR0: QSGERR Mask           */

#define DDRPHY_PGSR0_WLAERR_Pos          (23)                                              /*!< DDRPHY_T::PGSR0: WLAERR Position       */
#define DDRPHY_PGSR0_WLAERR_Msk          (0x1ul << DDRPHY_PGSR0_WLAERR_Pos)                /*!< DDRPHY_T::PGSR0: WLAERR Mask           */

#define DDRPHY_PGSR0_RDERR_Pos           (24)                                              /*!< DDRPHY_T::PGSR0: RDERR Position        */
#define DDRPHY_PGSR0_RDERR_Msk           (0x1ul << DDRPHY_PGSR0_RDERR_Pos)                 /*!< DDRPHY_T::PGSR0: RDERR Mask            */

#define DDRPHY_PGSR0_WDERR_Pos           (25)                                              /*!< DDRPHY_T::PGSR0: WDERR Position        */
#define DDRPHY_PGSR0_WDERR_Msk           (0x1ul << DDRPHY_PGSR0_WDERR_Pos)                 /*!< DDRPHY_T::PGSR0: WDERR Mask            */

#define DDRPHY_PGSR0_REERR_Pos           (26)                                              /*!< DDRPHY_T::PGSR0: REERR Position        */
#define DDRPHY_PGSR0_REERR_Msk           (0x1ul << DDRPHY_PGSR0_REERR_Pos)                 /*!< DDRPHY_T::PGSR0: REERR Mask            */

#define DDRPHY_PGSR0_WEERR_Pos           (27)                                              /*!< DDRPHY_T::PGSR0: WEERR Position        */
#define DDRPHY_PGSR0_WEERR_Msk           (0x1ul << DDRPHY_PGSR0_WEERR_Pos)                 /*!< DDRPHY_T::PGSR0: WEERR Mask            */

#define DDRPHY_PGSR0_PLDONE_CHN_Pos      (28)                                              /*!< DDRPHY_T::PGSR0: PLDONE_CHN Position   */
#define DDRPHY_PGSR0_PLDONE_CHN_Msk      (0x3ul << DDRPHY_PGSR0_PLDONE_CHN_Pos)            /*!< DDRPHY_T::PGSR0: PLDONE_CHN Mask       */

#define DDRPHY_PGSR0_APLOCK_Pos          (31)                                              /*!< DDRPHY_T::PGSR0: APLOCK Position       */
#define DDRPHY_PGSR0_APLOCK_Msk          (0x1ul << DDRPHY_PGSR0_APLOCK_Pos)                /*!< DDRPHY_T::PGSR0: APLOCK Mask           */

#define DDRPHY_PGSR1_DLTDONE_Pos         (0)                                               /*!< DDRPHY_T::PGSR1: DLTDONE Position      */
#define DDRPHY_PGSR1_DLTDONE_Msk         (0x1ul << DDRPHY_PGSR1_DLTDONE_Pos)               /*!< DDRPHY_T::PGSR1: DLTDONE Mask          */

#define DDRPHY_PGSR1_DLTCODE_Pos         (1)                                               /*!< DDRPHY_T::PGSR1: DLTCODE Position      */
#define DDRPHY_PGSR1_DLTCODE_Msk         (0xfffffful << DDRPHY_PGSR1_DLTCODE_Pos)          /*!< DDRPHY_T::PGSR1: DLTCODE Mask          */

#define DDRPHY_PGSR1_VTSTOP_Pos          (30)                                              /*!< DDRPHY_T::PGSR1: VTSTOP Position       */
#define DDRPHY_PGSR1_VTSTOP_Msk          (0x1ul << DDRPHY_PGSR1_VTSTOP_Pos)                /*!< DDRPHY_T::PGSR1: VTSTOP Mask           */

#define DDRPHY_PGSR1_PARERR_Pos          (31)                                              /*!< DDRPHY_T::PGSR1: PARERR Position       */
#define DDRPHY_PGSR1_PARERR_Msk          (0x1ul << DDRPHY_PGSR1_PARERR_Pos)                /*!< DDRPHY_T::PGSR1: PARERR Mask           */

#define DDRPHY_PLLCR_DTC_Pos             (0)                                               /*!< DDRPHY_T::PLLCR: DTC Position          */
#define DDRPHY_PLLCR_DTC_Msk             (0x3ul << DDRPHY_PLLCR_DTC_Pos)                   /*!< DDRPHY_T::PLLCR: DTC Mask              */

#define DDRPHY_PLLCR_ATC_Pos             (2)                                               /*!< DDRPHY_T::PLLCR: ATC Position          */
#define DDRPHY_PLLCR_ATC_Msk             (0xful << DDRPHY_PLLCR_ATC_Pos)                   /*!< DDRPHY_T::PLLCR: ATC Mask              */

#define DDRPHY_PLLCR_ATOEN_Pos           (6)                                               /*!< DDRPHY_T::PLLCR: ATOEN Position        */
#define DDRPHY_PLLCR_ATOEN_Msk           (0xful << DDRPHY_PLLCR_ATOEN_Pos)                 /*!< DDRPHY_T::PLLCR: ATOEN Mask            */

#define DDRPHY_PLLCR_GSHIFT_Pos          (10)                                              /*!< DDRPHY_T::PLLCR: GSHIFT Position       */
#define DDRPHY_PLLCR_GSHIFT_Msk          (0x1ul << DDRPHY_PLLCR_GSHIFT_Pos)                /*!< DDRPHY_T::PLLCR: GSHIFT Mask           */

#define DDRPHY_PLLCR_CPIC_Pos            (11)                                              /*!< DDRPHY_T::PLLCR: CPIC Position         */
#define DDRPHY_PLLCR_CPIC_Msk            (0x3ul << DDRPHY_PLLCR_CPIC_Pos)                  /*!< DDRPHY_T::PLLCR: CPIC Mask             */

#define DDRPHY_PLLCR_CPPC_Pos            (13)                                              /*!< DDRPHY_T::PLLCR: CPPC Position         */
#define DDRPHY_PLLCR_CPPC_Msk            (0xful << DDRPHY_PLLCR_CPPC_Pos)                  /*!< DDRPHY_T::PLLCR: CPPC Mask             */

#define DDRPHY_PLLCR_QPMODE_Pos          (17)                                              /*!< DDRPHY_T::PLLCR: QPMODE Position       */
#define DDRPHY_PLLCR_QPMODE_Msk          (0x1ul << DDRPHY_PLLCR_QPMODE_Pos)                /*!< DDRPHY_T::PLLCR: QPMODE Mask           */

#define DDRPHY_PLLCR_FRQSEL_Pos          (18)                                              /*!< DDRPHY_T::PLLCR: FRQSEL Position       */
#define DDRPHY_PLLCR_FRQSEL_Msk          (0x3ul << DDRPHY_PLLCR_FRQSEL_Pos)                /*!< DDRPHY_T::PLLCR: FRQSEL Mask           */

#define DDRPHY_PLLCR_PLLPD_Pos           (29)                                              /*!< DDRPHY_T::PLLCR: PLLPD Position        */
#define DDRPHY_PLLCR_PLLPD_Msk           (0x1ul << DDRPHY_PLLCR_PLLPD_Pos)                 /*!< DDRPHY_T::PLLCR: PLLPD Mask            */

#define DDRPHY_PLLCR_PLLRST_Pos          (30)                                              /*!< DDRPHY_T::PLLCR: PLLRST Position       */
#define DDRPHY_PLLCR_PLLRST_Msk          (0x1ul << DDRPHY_PLLCR_PLLRST_Pos)                /*!< DDRPHY_T::PLLCR: PLLRST Mask           */

#define DDRPHY_PLLCR_BYP_Pos             (31)                                              /*!< DDRPHY_T::PLLCR: BYP Position          */
#define DDRPHY_PLLCR_BYP_Msk             (0x1ul << DDRPHY_PLLCR_BYP_Pos)                   /*!< DDRPHY_T::PLLCR: BYP Mask              */

#define DDRPHY_PTR0_tPHYRST_Pos          (0)                                               /*!< DDRPHY_T::PTR0: tPHYRST Position       */
#define DDRPHY_PTR0_tPHYRST_Msk          (0x3ful << DDRPHY_PTR0_tPHYRST_Pos)               /*!< DDRPHY_T::PTR0: tPHYRST Mask           */

#define DDRPHY_PTR0_tPLLGS_Pos           (6)                                               /*!< DDRPHY_T::PTR0: tPLLGS Position        */
#define DDRPHY_PTR0_tPLLGS_Msk           (0x7ffful << DDRPHY_PTR0_tPLLGS_Pos)              /*!< DDRPHY_T::PTR0: tPLLGS Mask            */

#define DDRPHY_PTR0_tPLLPD_Pos           (21)                                              /*!< DDRPHY_T::PTR0: tPLLPD Position        */
#define DDRPHY_PTR0_tPLLPD_Msk           (0x7fful << DDRPHY_PTR0_tPLLPD_Pos)               /*!< DDRPHY_T::PTR0: tPLLPD Mask            */

#define DDRPHY_PTR1_tPLLRST_Pos          (0)                                               /*!< DDRPHY_T::PTR1: tPLLRST Position       */
#define DDRPHY_PTR1_tPLLRST_Msk          (0x1ffful << DDRPHY_PTR1_tPLLRST_Pos)             /*!< DDRPHY_T::PTR1: tPLLRST Mask           */

#define DDRPHY_PTR1_tPLLLOCK_Pos         (16)                                              /*!< DDRPHY_T::PTR1: tPLLLOCK Position      */
#define DDRPHY_PTR1_tPLLLOCK_Msk         (0xfffful << DDRPHY_PTR1_tPLLLOCK_Pos)            /*!< DDRPHY_T::PTR1: tPLLLOCK Mask          */

#define DDRPHY_PTR2_tCALON_Pos           (0)                                               /*!< DDRPHY_T::PTR2: tCALON Position        */
#define DDRPHY_PTR2_tCALON_Msk           (0x1ful << DDRPHY_PTR2_tCALON_Pos)                /*!< DDRPHY_T::PTR2: tCALON Mask            */

#define DDRPHY_PTR2_tCALS_Pos            (5)                                               /*!< DDRPHY_T::PTR2: tCALS Position         */
#define DDRPHY_PTR2_tCALS_Msk            (0x1ful << DDRPHY_PTR2_tCALS_Pos)                 /*!< DDRPHY_T::PTR2: tCALS Mask             */

#define DDRPHY_PTR2_tCALH_Pos            (10)                                              /*!< DDRPHY_T::PTR2: tCALH Position         */
#define DDRPHY_PTR2_tCALH_Msk            (0x1ful << DDRPHY_PTR2_tCALH_Pos)                 /*!< DDRPHY_T::PTR2: tCALH Mask             */

#define DDRPHY_PTR2_tWLDLYS_Pos          (15)                                              /*!< DDRPHY_T::PTR2: tWLDLYS Position       */
#define DDRPHY_PTR2_tWLDLYS_Msk          (0x1ful << DDRPHY_PTR2_tWLDLYS_Pos)               /*!< DDRPHY_T::PTR2: tWLDLYS Mask           */

#define DDRPHY_PTR3_tDINIT0_Pos          (0)                                               /*!< DDRPHY_T::PTR3: tDINIT0 Position       */
#define DDRPHY_PTR3_tDINIT0_Msk          (0xffffful << DDRPHY_PTR3_tDINIT0_Pos)            /*!< DDRPHY_T::PTR3: tDINIT0 Mask           */

#define DDRPHY_PTR3_tDINIT1_Pos          (20)                                              /*!< DDRPHY_T::PTR3: tDINIT1 Position       */
#define DDRPHY_PTR3_tDINIT1_Msk          (0x1fful << DDRPHY_PTR3_tDINIT1_Pos)              /*!< DDRPHY_T::PTR3: tDINIT1 Mask           */

#define DDRPHY_PTR4_tDINIT2_Pos          (0)                                               /*!< DDRPHY_T::PTR4: tDINIT2 Position       */
#define DDRPHY_PTR4_tDINIT2_Msk          (0x3fffful << DDRPHY_PTR4_tDINIT2_Pos)            /*!< DDRPHY_T::PTR4: tDINIT2 Mask           */

#define DDRPHY_PTR4_tDINIT3_Pos          (18)                                              /*!< DDRPHY_T::PTR4: tDINIT3 Position       */
#define DDRPHY_PTR4_tDINIT3_Msk          (0x3fful << DDRPHY_PTR4_tDINIT3_Pos)              /*!< DDRPHY_T::PTR4: tDINIT3 Mask           */

#define DDRPHY_ACMDLR_IPRD_Pos           (0)                                               /*!< DDRPHY_T::ACMDLR: IPRD Position        */
#define DDRPHY_ACMDLR_IPRD_Msk           (0xfful << DDRPHY_ACMDLR_IPRD_Pos)                /*!< DDRPHY_T::ACMDLR: IPRD Mask            */

#define DDRPHY_ACMDLR_TPRD_Pos           (8)                                               /*!< DDRPHY_T::ACMDLR: TPRD Position        */
#define DDRPHY_ACMDLR_TPRD_Msk           (0xfful << DDRPHY_ACMDLR_TPRD_Pos)                /*!< DDRPHY_T::ACMDLR: TPRD Mask            */

#define DDRPHY_ACMDLR_MDLD_Pos           (16)                                              /*!< DDRPHY_T::ACMDLR: MDLD Position        */
#define DDRPHY_ACMDLR_MDLD_Msk           (0xfful << DDRPHY_ACMDLR_MDLD_Pos)                /*!< DDRPHY_T::ACMDLR: MDLD Mask            */

#define DDRPHY_ACBDLR_CK0BD_Pos          (0)                                               /*!< DDRPHY_T::ACBDLR: CK0BD Position       */
#define DDRPHY_ACBDLR_CK0BD_Msk          (0x3ful << DDRPHY_ACBDLR_CK0BD_Pos)               /*!< DDRPHY_T::ACBDLR: CK0BD Mask           */

#define DDRPHY_ACBDLR_CK1BD_Pos          (6)                                               /*!< DDRPHY_T::ACBDLR: CK1BD Position       */
#define DDRPHY_ACBDLR_CK1BD_Msk          (0x3ful << DDRPHY_ACBDLR_CK1BD_Pos)               /*!< DDRPHY_T::ACBDLR: CK1BD Mask           */

#define DDRPHY_ACBDLR_CK2BD_Pos          (12)                                              /*!< DDRPHY_T::ACBDLR: CK2BD Position       */
#define DDRPHY_ACBDLR_CK2BD_Msk          (0x3ful << DDRPHY_ACBDLR_CK2BD_Pos)               /*!< DDRPHY_T::ACBDLR: CK2BD Mask           */

#define DDRPHY_ACBDLR_ACBD_Pos           (18)                                              /*!< DDRPHY_T::ACBDLR: ACBD Position        */
#define DDRPHY_ACBDLR_ACBD_Msk           (0x3ful << DDRPHY_ACBDLR_ACBD_Pos)                /*!< DDRPHY_T::ACBDLR: ACBD Mask            */

#define DDRPHY_ACIOCR_ACIOM_Pos          (0)                                               /*!< DDRPHY_T::ACIOCR: ACIOM Position       */
#define DDRPHY_ACIOCR_ACIOM_Msk          (0x1ul << DDRPHY_ACIOCR_ACIOM_Pos)                /*!< DDRPHY_T::ACIOCR: ACIOM Mask           */

#define DDRPHY_ACIOCR_ACOE_Pos           (1)                                               /*!< DDRPHY_T::ACIOCR: ACOE Position        */
#define DDRPHY_ACIOCR_ACOE_Msk           (0x1ul << DDRPHY_ACIOCR_ACOE_Pos)                 /*!< DDRPHY_T::ACIOCR: ACOE Mask            */

#define DDRPHY_ACIOCR_ACODT_Pos          (2)                                               /*!< DDRPHY_T::ACIOCR: ACODT Position       */
#define DDRPHY_ACIOCR_ACODT_Msk          (0x1ul << DDRPHY_ACIOCR_ACODT_Pos)                /*!< DDRPHY_T::ACIOCR: ACODT Mask           */

#define DDRPHY_ACIOCR_ACPDD_Pos          (3)                                               /*!< DDRPHY_T::ACIOCR: ACPDD Position       */
#define DDRPHY_ACIOCR_ACPDD_Msk          (0x1ul << DDRPHY_ACIOCR_ACPDD_Pos)                /*!< DDRPHY_T::ACIOCR: ACPDD Mask           */

#define DDRPHY_ACIOCR_ACPDR_Pos          (4)                                               /*!< DDRPHY_T::ACIOCR: ACPDR Position       */
#define DDRPHY_ACIOCR_ACPDR_Msk          (0x1ul << DDRPHY_ACIOCR_ACPDR_Pos)                /*!< DDRPHY_T::ACIOCR: ACPDR Mask           */

#define DDRPHY_ACIOCR_CKODT_Pos          (5)                                               /*!< DDRPHY_T::ACIOCR: CKODT Position       */
#define DDRPHY_ACIOCR_CKODT_Msk          (0x7ul << DDRPHY_ACIOCR_CKODT_Pos)                /*!< DDRPHY_T::ACIOCR: CKODT Mask           */

#define DDRPHY_ACIOCR_CKPDD_Pos          (8)                                               /*!< DDRPHY_T::ACIOCR: CKPDD Position       */
#define DDRPHY_ACIOCR_CKPDD_Msk          (0x7ul << DDRPHY_ACIOCR_CKPDD_Pos)                /*!< DDRPHY_T::ACIOCR: CKPDD Mask           */

#define DDRPHY_ACIOCR_CKPDR_Pos          (11)                                              /*!< DDRPHY_T::ACIOCR: CKPDR Position       */
#define DDRPHY_ACIOCR_CKPDR_Msk          (0x7ul << DDRPHY_ACIOCR_CKPDR_Pos)                /*!< DDRPHY_T::ACIOCR: CKPDR Mask           */

#define DDRPHY_ACIOCR_RANKODT_Pos        (14)                                              /*!< DDRPHY_T::ACIOCR: RANKODT Position     */
#define DDRPHY_ACIOCR_RANKODT_Msk        (0xful << DDRPHY_ACIOCR_RANKODT_Pos)              /*!< DDRPHY_T::ACIOCR: RANKODT Mask         */

#define DDRPHY_ACIOCR_CSPDD_Pos          (18)                                              /*!< DDRPHY_T::ACIOCR: CSPDD Position       */
#define DDRPHY_ACIOCR_CSPDD_Msk          (0xful << DDRPHY_ACIOCR_CSPDD_Pos)                /*!< DDRPHY_T::ACIOCR: CSPDD Mask           */

#define DDRPHY_ACIOCR_RANKPDR_Pos        (22)                                              /*!< DDRPHY_T::ACIOCR: RANKPDR Position     */
#define DDRPHY_ACIOCR_RANKPDR_Msk        (0xful << DDRPHY_ACIOCR_RANKPDR_Pos)              /*!< DDRPHY_T::ACIOCR: RANKPDR Mask         */

#define DDRPHY_ACIOCR_RSTODT_Pos         (26)                                              /*!< DDRPHY_T::ACIOCR: RSTODT Position      */
#define DDRPHY_ACIOCR_RSTODT_Msk         (0x1ul << DDRPHY_ACIOCR_RSTODT_Pos)               /*!< DDRPHY_T::ACIOCR: RSTODT Mask          */

#define DDRPHY_ACIOCR_RSTPDD_Pos         (27)                                              /*!< DDRPHY_T::ACIOCR: RSTPDD Position      */
#define DDRPHY_ACIOCR_RSTPDD_Msk         (0x1ul << DDRPHY_ACIOCR_RSTPDD_Pos)               /*!< DDRPHY_T::ACIOCR: RSTPDD Mask          */

#define DDRPHY_ACIOCR_RSTPDR_Pos         (28)                                              /*!< DDRPHY_T::ACIOCR: RSTPDR Position      */
#define DDRPHY_ACIOCR_RSTPDR_Msk         (0x1ul << DDRPHY_ACIOCR_RSTPDR_Pos)               /*!< DDRPHY_T::ACIOCR: RSTPDR Mask          */

#define DDRPHY_ACIOCR_RSTIOM_Pos         (29)                                              /*!< DDRPHY_T::ACIOCR: RSTIOM Position      */
#define DDRPHY_ACIOCR_RSTIOM_Msk         (0x1ul << DDRPHY_ACIOCR_RSTIOM_Pos)               /*!< DDRPHY_T::ACIOCR: RSTIOM Mask          */

#define DDRPHY_ACIOCR_ACSR_Pos           (30)                                              /*!< DDRPHY_T::ACIOCR: ACSR Position        */
#define DDRPHY_ACIOCR_ACSR_Msk           (0x3ul << DDRPHY_ACIOCR_ACSR_Pos)                 /*!< DDRPHY_T::ACIOCR: ACSR Mask            */

#define DDRPHY_DXCCR_DXODT_Pos           (0)                                               /*!< DDRPHY_T::DXCCR: DXODT Position        */
#define DDRPHY_DXCCR_DXODT_Msk           (0x1ul << DDRPHY_DXCCR_DXODT_Pos)                 /*!< DDRPHY_T::DXCCR: DXODT Mask            */

#define DDRPHY_DXCCR_DXIOM_Pos           (1)                                               /*!< DDRPHY_T::DXCCR: DXIOM Position        */
#define DDRPHY_DXCCR_DXIOM_Msk           (0x1ul << DDRPHY_DXCCR_DXIOM_Pos)                 /*!< DDRPHY_T::DXCCR: DXIOM Mask            */

#define DDRPHY_DXCCR_MDLEN_Pos           (2)                                               /*!< DDRPHY_T::DXCCR: MDLEN Position        */
#define DDRPHY_DXCCR_MDLEN_Msk           (0x1ul << DDRPHY_DXCCR_MDLEN_Pos)                 /*!< DDRPHY_T::DXCCR: MDLEN Mask            */

#define DDRPHY_DXCCR_DXPDD_Pos           (3)                                               /*!< DDRPHY_T::DXCCR: DXPDD Position        */
#define DDRPHY_DXCCR_DXPDD_Msk           (0x1ul << DDRPHY_DXCCR_DXPDD_Pos)                 /*!< DDRPHY_T::DXCCR: DXPDD Mask            */

#define DDRPHY_DXCCR_DXPDR_Pos           (4)                                               /*!< DDRPHY_T::DXCCR: DXPDR Position        */
#define DDRPHY_DXCCR_DXPDR_Msk           (0x1ul << DDRPHY_DXCCR_DXPDR_Pos)                 /*!< DDRPHY_T::DXCCR: DXPDR Mask            */

#define DDRPHY_DXCCR_DQSRES_Pos          (5)                                               /*!< DDRPHY_T::DXCCR: DQSRES Position       */
#define DDRPHY_DXCCR_DQSRES_Msk          (0xful << DDRPHY_DXCCR_DQSRES_Pos)                /*!< DDRPHY_T::DXCCR: DQSRES Mask           */

#define DDRPHY_DXCCR_DQSNRES_Pos         (9)                                               /*!< DDRPHY_T::DXCCR: DQSNRES Position      */
#define DDRPHY_DXCCR_DQSNRES_Msk         (0xful << DDRPHY_DXCCR_DQSNRES_Pos)               /*!< DDRPHY_T::DXCCR: DQSNRES Mask          */

#define DDRPHY_DXCCR_DXSR_Pos            (13)                                              /*!< DDRPHY_T::DXCCR: DXSR Position         */
#define DDRPHY_DXCCR_DXSR_Msk            (0x3ul << DDRPHY_DXCCR_DXSR_Pos)                  /*!< DDRPHY_T::DXCCR: DXSR Mask             */

#define DDRPHY_DXCCR_MSBUDQ_Pos          (15)                                              /*!< DDRPHY_T::DXCCR: MSBUDQ Position       */
#define DDRPHY_DXCCR_MSBUDQ_Msk          (0x7ul << DDRPHY_DXCCR_MSBUDQ_Pos)                /*!< DDRPHY_T::DXCCR: MSBUDQ Mask           */

#define DDRPHY_DXCCR_UDQODT_Pos          (18)                                              /*!< DDRPHY_T::DXCCR: UDQODT Position       */
#define DDRPHY_DXCCR_UDQODT_Msk          (0x1ul << DDRPHY_DXCCR_UDQODT_Pos)                /*!< DDRPHY_T::DXCCR: UDQODT Mask           */

#define DDRPHY_DXCCR_UDQPDD_Pos          (19)                                              /*!< DDRPHY_T::DXCCR: UDQPDD Position       */
#define DDRPHY_DXCCR_UDQPDD_Msk          (0x1ul << DDRPHY_DXCCR_UDQPDD_Pos)                /*!< DDRPHY_T::DXCCR: UDQPDD Mask           */

#define DDRPHY_DXCCR_UDQPDR_Pos          (20)                                              /*!< DDRPHY_T::DXCCR: UDQPDR Position       */
#define DDRPHY_DXCCR_UDQPDR_Msk          (0x1ul << DDRPHY_DXCCR_UDQPDR_Pos)                /*!< DDRPHY_T::DXCCR: UDQPDR Mask           */

#define DDRPHY_DXCCR_UDQIOM_Pos          (21)                                              /*!< DDRPHY_T::DXCCR: UDQIOM Position       */
#define DDRPHY_DXCCR_UDQIOM_Msk          (0x1ul << DDRPHY_DXCCR_UDQIOM_Pos)                /*!< DDRPHY_T::DXCCR: UDQIOM Mask           */

#define DDRPHY_DXCCR_DYNDXPDD_Pos        (22)                                              /*!< DDRPHY_T::DXCCR: DYNDXPDD Position     */
#define DDRPHY_DXCCR_DYNDXPDD_Msk        (0x1ul << DDRPHY_DXCCR_DYNDXPDD_Pos)              /*!< DDRPHY_T::DXCCR: DYNDXPDD Mask         */

#define DDRPHY_DXCCR_DYNDXPDR_Pos        (23)                                              /*!< DDRPHY_T::DXCCR: DYNDXPDR Position     */
#define DDRPHY_DXCCR_DYNDXPDR_Msk        (0x1ul << DDRPHY_DXCCR_DYNDXPDR_Pos)              /*!< DDRPHY_T::DXCCR: DYNDXPDR Mask         */

#define DDRPHY_DXCCR_DDPDDCDO_Pos        (24)                                              /*!< DDRPHY_T::DXCCR: DDPDDCDO Position     */
#define DDRPHY_DXCCR_DDPDDCDO_Msk        (0xful << DDRPHY_DXCCR_DDPDDCDO_Pos)              /*!< DDRPHY_T::DXCCR: DDPDDCDO Mask         */

#define DDRPHY_DXCCR_DDPDRCDO_Pos        (28)                                              /*!< DDRPHY_T::DXCCR: DDPDRCDO Position     */
#define DDRPHY_DXCCR_DDPDRCDO_Msk        (0xful << DDRPHY_DXCCR_DDPDRCDO_Pos)              /*!< DDRPHY_T::DXCCR: DDPDRCDO Mask         */

#define DDRPHY_DSGCR_PUREN_Pos           (0)                                               /*!< DDRPHY_T::DSGCR: PUREN Position        */
#define DDRPHY_DSGCR_PUREN_Msk           (0x1ul << DDRPHY_DSGCR_PUREN_Pos)                 /*!< DDRPHY_T::DSGCR: PUREN Mask            */

#define DDRPHY_DSGCR_BDISEN_Pos          (1)                                               /*!< DDRPHY_T::DSGCR: BDISEN Position       */
#define DDRPHY_DSGCR_BDISEN_Msk          (0x1ul << DDRPHY_DSGCR_BDISEN_Pos)                /*!< DDRPHY_T::DSGCR: BDISEN Mask           */

#define DDRPHY_DSGCR_ZUEN_Pos            (2)                                               /*!< DDRPHY_T::DSGCR: ZUEN Position         */
#define DDRPHY_DSGCR_ZUEN_Msk            (0x1ul << DDRPHY_DSGCR_ZUEN_Pos)                  /*!< DDRPHY_T::DSGCR: ZUEN Mask             */

#define DDRPHY_DSGCR_LPIOPD_Pos          (3)                                               /*!< DDRPHY_T::DSGCR: LPIOPD Position       */
#define DDRPHY_DSGCR_LPIOPD_Msk          (0x1ul << DDRPHY_DSGCR_LPIOPD_Pos)                /*!< DDRPHY_T::DSGCR: LPIOPD Mask           */

#define DDRPHY_DSGCR_LPPLLPD_Pos         (4)                                               /*!< DDRPHY_T::DSGCR: LPPLLPD Position      */
#define DDRPHY_DSGCR_LPPLLPD_Msk         (0x1ul << DDRPHY_DSGCR_LPPLLPD_Pos)               /*!< DDRPHY_T::DSGCR: LPPLLPD Mask          */

#define DDRPHY_DSGCR_CUAEN_Pos           (5)                                               /*!< DDRPHY_T::DSGCR: CUAEN Position        */
#define DDRPHY_DSGCR_CUAEN_Msk           (0x1ul << DDRPHY_DSGCR_CUAEN_Pos)                 /*!< DDRPHY_T::DSGCR: CUAEN Mask            */

#define DDRPHY_DSGCR_DQSGX_Pos           (6)                                               /*!< DDRPHY_T::DSGCR: DQSGX Position        */
#define DDRPHY_DSGCR_DQSGX_Msk           (0x1ul << DDRPHY_DSGCR_DQSGX_Pos)                 /*!< DDRPHY_T::DSGCR: DQSGX Mask            */

#define DDRPHY_DSGCR_BRRMODE_Pos         (7)                                               /*!< DDRPHY_T::DSGCR: BRRMODE Position      */
#define DDRPHY_DSGCR_BRRMODE_Msk         (0x1ul << DDRPHY_DSGCR_BRRMODE_Pos)               /*!< DDRPHY_T::DSGCR: BRRMODE Mask          */

#define DDRPHY_DSGCR_PUAD_Pos            (8)                                               /*!< DDRPHY_T::DSGCR: PUAD Position         */
#define DDRPHY_DSGCR_PUAD_Msk            (0xful << DDRPHY_DSGCR_PUAD_Pos)                  /*!< DDRPHY_T::DSGCR: PUAD Mask             */

#define DDRPHY_DSGCR_DTOODT_Pos          (12)                                              /*!< DDRPHY_T::DSGCR: DTOODT Position       */
#define DDRPHY_DSGCR_DTOODT_Msk          (0x1ul << DDRPHY_DSGCR_DTOODT_Pos)                /*!< DDRPHY_T::DSGCR: DTOODT Mask           */

#define DDRPHY_DSGCR_DTOPDD_Pos          (13)                                              /*!< DDRPHY_T::DSGCR: DTOPDD Position       */
#define DDRPHY_DSGCR_DTOPDD_Msk          (0x1ul << DDRPHY_DSGCR_DTOPDD_Pos)                /*!< DDRPHY_T::DSGCR: DTOPDD Mask           */

#define DDRPHY_DSGCR_DTOPDR_Pos          (14)                                              /*!< DDRPHY_T::DSGCR: DTOPDR Position       */
#define DDRPHY_DSGCR_DTOPDR_Msk          (0x1ul << DDRPHY_DSGCR_DTOPDR_Pos)                /*!< DDRPHY_T::DSGCR: DTOPDR Mask           */

#define DDRPHY_DSGCR_DTOIOM_Pos          (15)                                              /*!< DDRPHY_T::DSGCR: DTOIOM Position       */
#define DDRPHY_DSGCR_DTOIOM_Msk          (0x1ul << DDRPHY_DSGCR_DTOIOM_Pos)                /*!< DDRPHY_T::DSGCR: DTOIOM Mask           */

#define DDRPHY_DSGCR_DTOOE_Pos           (16)                                              /*!< DDRPHY_T::DSGCR: DTOOE Position        */
#define DDRPHY_DSGCR_DTOOE_Msk           (0x1ul << DDRPHY_DSGCR_DTOOE_Pos)                 /*!< DDRPHY_T::DSGCR: DTOOE Mask            */

#define DDRPHY_DSGCR_ATOAE_Pos           (17)                                              /*!< DDRPHY_T::DSGCR: ATOAE Position        */
#define DDRPHY_DSGCR_ATOAE_Msk           (0x1ul << DDRPHY_DSGCR_ATOAE_Pos)                 /*!< DDRPHY_T::DSGCR: ATOAE Mask            */

#define DDRPHY_DSGCR_RRMODE_Pos          (18)                                              /*!< DDRPHY_T::DSGCR: RRMODE Position       */
#define DDRPHY_DSGCR_RRMODE_Msk          (0x1ul << DDRPHY_DSGCR_RRMODE_Pos)                /*!< DDRPHY_T::DSGCR: RRMODE Mask           */

#define DDRPHY_DSGCR_SDRMODE_Pos         (19)                                              /*!< DDRPHY_T::DSGCR: SDRMODE Position      */
#define DDRPHY_DSGCR_SDRMODE_Msk         (0x1ul << DDRPHY_DSGCR_SDRMODE_Pos)               /*!< DDRPHY_T::DSGCR: SDRMODE Mask          */

#define DDRPHY_DSGCR_CKEPDD_Pos          (20)                                              /*!< DDRPHY_T::DSGCR: CKEPDD Position       */
#define DDRPHY_DSGCR_CKEPDD_Msk          (0xful << DDRPHY_DSGCR_CKEPDD_Pos)                /*!< DDRPHY_T::DSGCR: CKEPDD Mask           */

#define DDRPHY_DSGCR_ODTPDD_Pos          (24)                                              /*!< DDRPHY_T::DSGCR: ODTPDD Position       */
#define DDRPHY_DSGCR_ODTPDD_Msk          (0xful << DDRPHY_DSGCR_ODTPDD_Pos)                /*!< DDRPHY_T::DSGCR: ODTPDD Mask           */

#define DDRPHY_DSGCR_CKOE_Pos            (28)                                              /*!< DDRPHY_T::DSGCR: CKOE Position         */
#define DDRPHY_DSGCR_CKOE_Msk            (0x1ul << DDRPHY_DSGCR_CKOE_Pos)                  /*!< DDRPHY_T::DSGCR: CKOE Mask             */

#define DDRPHY_DSGCR_ODTOE_Pos           (29)                                              /*!< DDRPHY_T::DSGCR: ODTOE Position        */
#define DDRPHY_DSGCR_ODTOE_Msk           (0x1ul << DDRPHY_DSGCR_ODTOE_Pos)                 /*!< DDRPHY_T::DSGCR: ODTOE Mask            */

#define DDRPHY_DSGCR_RSTOE_Pos           (30)                                              /*!< DDRPHY_T::DSGCR: RSTOE Position        */
#define DDRPHY_DSGCR_RSTOE_Msk           (0x1ul << DDRPHY_DSGCR_RSTOE_Pos)                 /*!< DDRPHY_T::DSGCR: RSTOE Mask            */

#define DDRPHY_DSGCR_CKEOE_Pos           (31)                                              /*!< DDRPHY_T::DSGCR: CKEOE Position        */
#define DDRPHY_DSGCR_CKEOE_Msk           (0x1ul << DDRPHY_DSGCR_CKEOE_Pos)                 /*!< DDRPHY_T::DSGCR: CKEOE Mask            */

#define DDRPHY_DCR_DDRMD_Pos             (0)                                               /*!< DDRPHY_T::DCR: DDRMD Position          */
#define DDRPHY_DCR_DDRMD_Msk             (0x7ul << DDRPHY_DCR_DDRMD_Pos)                   /*!< DDRPHY_T::DCR: DDRMD Mask              */

#define DDRPHY_DCR_DDR8BNK_Pos           (3)                                               /*!< DDRPHY_T::DCR: DDR8BNK Position        */
#define DDRPHY_DCR_DDR8BNK_Msk           (0x1ul << DDRPHY_DCR_DDR8BNK_Pos)                 /*!< DDRPHY_T::DCR: DDR8BNK Mask            */

#define DDRPHY_DCR_PDQ_Pos               (4)                                               /*!< DDRPHY_T::DCR: PDQ Position            */
#define DDRPHY_DCR_PDQ_Msk               (0x7ul << DDRPHY_DCR_PDQ_Pos)                     /*!< DDRPHY_T::DCR: PDQ Mask                */

#define DDRPHY_DCR_MPRDQ_Pos             (7)                                               /*!< DDRPHY_T::DCR: MPRDQ Position          */
#define DDRPHY_DCR_MPRDQ_Msk             (0x1ul << DDRPHY_DCR_MPRDQ_Pos)                   /*!< DDRPHY_T::DCR: MPRDQ Mask              */

#define DDRPHY_DCR_BYTEMASK_Pos          (10)                                              /*!< DDRPHY_T::DCR: BYTEMASK Position       */
#define DDRPHY_DCR_BYTEMASK_Msk          (0xfful << DDRPHY_DCR_BYTEMASK_Pos)               /*!< DDRPHY_T::DCR: BYTEMASK Mask           */

#define DDRPHY_DCR_NOSRA_Pos             (27)                                              /*!< DDRPHY_T::DCR: NOSRA Position          */
#define DDRPHY_DCR_NOSRA_Msk             (0x1ul << DDRPHY_DCR_NOSRA_Pos)                   /*!< DDRPHY_T::DCR: NOSRA Mask              */

#define DDRPHY_DCR_DDR2T_Pos             (28)                                              /*!< DDRPHY_T::DCR: DDR2T Position          */
#define DDRPHY_DCR_DDR2T_Msk             (0x1ul << DDRPHY_DCR_DDR2T_Pos)                   /*!< DDRPHY_T::DCR: DDR2T Mask              */

#define DDRPHY_DCR_UDIMM_Pos             (29)                                              /*!< DDRPHY_T::DCR: UDIMM Position          */
#define DDRPHY_DCR_UDIMM_Msk             (0x1ul << DDRPHY_DCR_UDIMM_Pos)                   /*!< DDRPHY_T::DCR: UDIMM Mask              */

#define DDRPHY_DTPR0_tRTP_Pos            (0)                                               /*!< DDRPHY_T::DTPR0: tRTP Position         */
#define DDRPHY_DTPR0_tRTP_Msk            (0xful << DDRPHY_DTPR0_tRTP_Pos)                  /*!< DDRPHY_T::DTPR0: tRTP Mask             */

#define DDRPHY_DTPR0_tWTR_Pos            (4)                                               /*!< DDRPHY_T::DTPR0: tWTR Position         */
#define DDRPHY_DTPR0_tWTR_Msk            (0xful << DDRPHY_DTPR0_tWTR_Pos)                  /*!< DDRPHY_T::DTPR0: tWTR Mask             */

#define DDRPHY_DTPR0_tRP_Pos             (8)                                               /*!< DDRPHY_T::DTPR0: tRP Position          */
#define DDRPHY_DTPR0_tRP_Msk             (0xful << DDRPHY_DTPR0_tRP_Pos)                   /*!< DDRPHY_T::DTPR0: tRP Mask              */

#define DDRPHY_DTPR0_tRCD_Pos            (12)                                              /*!< DDRPHY_T::DTPR0: tRCD Position         */
#define DDRPHY_DTPR0_tRCD_Msk            (0xful << DDRPHY_DTPR0_tRCD_Pos)                  /*!< DDRPHY_T::DTPR0: tRCD Mask             */

#define DDRPHY_DTPR0_tRAS_Pos            (16)                                              /*!< DDRPHY_T::DTPR0: tRAS Position         */
#define DDRPHY_DTPR0_tRAS_Msk            (0x3ful << DDRPHY_DTPR0_tRAS_Pos)                 /*!< DDRPHY_T::DTPR0: tRAS Mask             */

#define DDRPHY_DTPR0_tRRD_Pos            (22)                                              /*!< DDRPHY_T::DTPR0: tRRD Position         */
#define DDRPHY_DTPR0_tRRD_Msk            (0xful << DDRPHY_DTPR0_tRRD_Pos)                  /*!< DDRPHY_T::DTPR0: tRRD Mask             */

#define DDRPHY_DTPR0_tRC_Pos             (26)                                              /*!< DDRPHY_T::DTPR0: tRC Position          */
#define DDRPHY_DTPR0_tRC_Msk             (0x3ful << DDRPHY_DTPR0_tRC_Pos)                  /*!< DDRPHY_T::DTPR0: tRC Mask              */

#define DDRPHY_DTPR1_tMRD_Pos            (0)                                               /*!< DDRPHY_T::DTPR1: tMRD Position         */
#define DDRPHY_DTPR1_tMRD_Msk            (0x3ul << DDRPHY_DTPR1_tMRD_Pos)                  /*!< DDRPHY_T::DTPR1: tMRD Mask             */

#define DDRPHY_DTPR1_tMOD_Pos            (2)                                               /*!< DDRPHY_T::DTPR1: tMOD Position         */
#define DDRPHY_DTPR1_tMOD_Msk            (0x7ul << DDRPHY_DTPR1_tMOD_Pos)                  /*!< DDRPHY_T::DTPR1: tMOD Mask             */

#define DDRPHY_DTPR1_tFAW_Pos            (5)                                               /*!< DDRPHY_T::DTPR1: tFAW Position         */
#define DDRPHY_DTPR1_tFAW_Msk            (0x3ful << DDRPHY_DTPR1_tFAW_Pos)                 /*!< DDRPHY_T::DTPR1: tFAW Mask             */

#define DDRPHY_DTPR1_tRFC_Pos            (11)                                              /*!< DDRPHY_T::DTPR1: tRFC Position         */
#define DDRPHY_DTPR1_tRFC_Msk            (0x1fful << DDRPHY_DTPR1_tRFC_Pos)                /*!< DDRPHY_T::DTPR1: tRFC Mask             */

#define DDRPHY_DTPR1_tWLMRD_Pos          (20)                                              /*!< DDRPHY_T::DTPR1: tWLMRD Position       */
#define DDRPHY_DTPR1_tWLMRD_Msk          (0x3ful << DDRPHY_DTPR1_tWLMRD_Pos)               /*!< DDRPHY_T::DTPR1: tWLMRD Mask           */

#define DDRPHY_DTPR1_tWLO_Pos            (26)                                              /*!< DDRPHY_T::DTPR1: tWLO Position         */
#define DDRPHY_DTPR1_tWLO_Msk            (0xful << DDRPHY_DTPR1_tWLO_Pos)                  /*!< DDRPHY_T::DTPR1: tWLO Mask             */

#define DDRPHY_DTPR1_tAONDtAOFD_Pos      (30)                                              /*!< DDRPHY_T::DTPR1: tAONDtAOFD Position   */
#define DDRPHY_DTPR1_tAONDtAOFD_Msk      (0x3ul << DDRPHY_DTPR1_tAONDtAOFD_Pos)            /*!< DDRPHY_T::DTPR1: tAONDtAOFD Mask       */

#define DDRPHY_DTPR2_tXS_Pos             (0)                                               /*!< DDRPHY_T::DTPR2: tXS Position          */
#define DDRPHY_DTPR2_tXS_Msk             (0x3fful << DDRPHY_DTPR2_tXS_Pos)                 /*!< DDRPHY_T::DTPR2: tXS Mask              */

#define DDRPHY_DTPR2_tXP_Pos             (10)                                              /*!< DDRPHY_T::DTPR2: tXP Position          */
#define DDRPHY_DTPR2_tXP_Msk             (0x1ful << DDRPHY_DTPR2_tXP_Pos)                  /*!< DDRPHY_T::DTPR2: tXP Mask              */

#define DDRPHY_DTPR2_tCKE_Pos            (15)                                              /*!< DDRPHY_T::DTPR2: tCKE Position         */
#define DDRPHY_DTPR2_tCKE_Msk            (0xful << DDRPHY_DTPR2_tCKE_Pos)                  /*!< DDRPHY_T::DTPR2: tCKE Mask             */

#define DDRPHY_DTPR2_tDLLK_Pos           (19)                                              /*!< DDRPHY_T::DTPR2: tDLLK Position        */
#define DDRPHY_DTPR2_tDLLK_Msk           (0x3fful << DDRPHY_DTPR2_tDLLK_Pos)               /*!< DDRPHY_T::DTPR2: tDLLK Mask            */

#define DDRPHY_DTPR2_tRTODT_Pos          (29)                                              /*!< DDRPHY_T::DTPR2: tRTODT Position       */
#define DDRPHY_DTPR2_tRTODT_Msk          (0x1ul << DDRPHY_DTPR2_tRTODT_Pos)                /*!< DDRPHY_T::DTPR2: tRTODT Mask           */

#define DDRPHY_DTPR2_tRTW_Pos            (30)                                              /*!< DDRPHY_T::DTPR2: tRTW Position         */
#define DDRPHY_DTPR2_tRTW_Msk            (0x1ul << DDRPHY_DTPR2_tRTW_Pos)                  /*!< DDRPHY_T::DTPR2: tRTW Mask             */

#define DDRPHY_DTPR2_tCCD_Pos            (31)                                              /*!< DDRPHY_T::DTPR2: tCCD Position         */
#define DDRPHY_DTPR2_tCCD_Msk            (0x1ul << DDRPHY_DTPR2_tCCD_Pos)                  /*!< DDRPHY_T::DTPR2: tCCD Mask             */

#define DDRPHY_MR0_BL_Pos                (0)                                               /*!< DDRPHY_T::MR0: BL Position             */
#define DDRPHY_MR0_BL_Msk                (0x3ul << DDRPHY_MR0_BL_Pos)                      /*!< DDRPHY_T::MR0: BL Mask                 */

#define DDRPHY_MR0_CL0_Pos               (2)                                               /*!< DDRPHY_T::MR0: CL0 Position            */
#define DDRPHY_MR0_CL0_Msk               (0x1ul << DDRPHY_MR0_CL0_Pos)                     /*!< DDRPHY_T::MR0: CL0 Mask                */

#define DDRPHY_MR0_BT_Pos                (3)                                               /*!< DDRPHY_T::MR0: BT Position             */
#define DDRPHY_MR0_BT_Msk                (0x1ul << DDRPHY_MR0_BT_Pos)                      /*!< DDRPHY_T::MR0: BT Mask                 */

#define DDRPHY_MR0_CL1_Pos               (4)                                               /*!< DDRPHY_T::MR0: CL1 Position            */
#define DDRPHY_MR0_CL1_Msk               (0x7ul << DDRPHY_MR0_CL1_Pos)                     /*!< DDRPHY_T::MR0: CL1 Mask                */

#define DDRPHY_MR0_TM_Pos                (7)                                               /*!< DDRPHY_T::MR0: TM Position             */
#define DDRPHY_MR0_TM_Msk                (0x1ul << DDRPHY_MR0_TM_Pos)                      /*!< DDRPHY_T::MR0: TM Mask                 */

#define DDRPHY_MR0_DR_Pos                (8)                                               /*!< DDRPHY_T::MR0: DR Position             */
#define DDRPHY_MR0_DR_Msk                (0x1ul << DDRPHY_MR0_DR_Pos)                      /*!< DDRPHY_T::MR0: DR Mask                 */

#define DDRPHY_MR0_WR_Pos                (9)                                               /*!< DDRPHY_T::MR0: WR Position             */
#define DDRPHY_MR0_WR_Msk                (0x7ul << DDRPHY_MR0_WR_Pos)                      /*!< DDRPHY_T::MR0: WR Mask                 */

#define DDRPHY_MR0_PD_Pos                (12)                                              /*!< DDRPHY_T::MR0: PD Position             */
#define DDRPHY_MR0_PD_Msk                (0x1ul << DDRPHY_MR0_PD_Pos)                      /*!< DDRPHY_T::MR0: PD Mask                 */

#define DDRPHY_MR1_DE_Pos                (0)                                               /*!< DDRPHY_T::MR1: DE Position             */
#define DDRPHY_MR1_DE_Msk                (0x1ul << DDRPHY_MR1_DE_Pos)                      /*!< DDRPHY_T::MR1: DE Mask                 */

#define DDRPHY_MR1_DIC0_Pos              (1)                                               /*!< DDRPHY_T::MR1: DIC0 Position           */
#define DDRPHY_MR1_DIC0_Msk              (0x1ul << DDRPHY_MR1_DIC0_Pos)                    /*!< DDRPHY_T::MR1: DIC0 Mask               */

#define DDRPHY_MR1_RTT0_Pos              (2)                                               /*!< DDRPHY_T::MR1: RTT0 Position           */
#define DDRPHY_MR1_RTT0_Msk              (0x1ul << DDRPHY_MR1_RTT0_Pos)                    /*!< DDRPHY_T::MR1: RTT0 Mask               */

#define DDRPHY_MR1_AL_Pos                (3)                                               /*!< DDRPHY_T::MR1: AL Position             */
#define DDRPHY_MR1_AL_Msk                (0x3ul << DDRPHY_MR1_AL_Pos)                      /*!< DDRPHY_T::MR1: AL Mask                 */

#define DDRPHY_MR1_DIC1_Pos              (5)                                               /*!< DDRPHY_T::MR1: DIC1 Position           */
#define DDRPHY_MR1_DIC1_Msk              (0x1ul << DDRPHY_MR1_DIC1_Pos)                    /*!< DDRPHY_T::MR1: DIC1 Mask               */

#define DDRPHY_MR1_RTT1_Pos              (6)                                               /*!< DDRPHY_T::MR1: RTT1 Position           */
#define DDRPHY_MR1_RTT1_Msk              (0x1ul << DDRPHY_MR1_RTT1_Pos)                    /*!< DDRPHY_T::MR1: RTT1 Mask               */

#define DDRPHY_MR1_LEVEL_Pos             (7)                                               /*!< DDRPHY_T::MR1: LEVEL Position          */
#define DDRPHY_MR1_LEVEL_Msk             (0x1ul << DDRPHY_MR1_LEVEL_Pos)                   /*!< DDRPHY_T::MR1: LEVEL Mask              */

#define DDRPHY_MR1_RTT2_Pos              (9)                                               /*!< DDRPHY_T::MR1: RTT2 Position           */
#define DDRPHY_MR1_RTT2_Msk              (0x1ul << DDRPHY_MR1_RTT2_Pos)                    /*!< DDRPHY_T::MR1: RTT2 Mask               */

#define DDRPHY_MR1_TDQS_Pos              (11)                                              /*!< DDRPHY_T::MR1: TDQS Position           */
#define DDRPHY_MR1_TDQS_Msk              (0x1ul << DDRPHY_MR1_TDQS_Pos)                    /*!< DDRPHY_T::MR1: TDQS Mask               */

#define DDRPHY_MR1_QOFF_Pos              (12)                                              /*!< DDRPHY_T::MR1: QOFF Position           */
#define DDRPHY_MR1_QOFF_Msk              (0x1ul << DDRPHY_MR1_QOFF_Pos)                    /*!< DDRPHY_T::MR1: QOFF Mask               */

#define DDRPHY_MR2_PASR_Pos              (0)                                               /*!< DDRPHY_T::MR2: PASR Position           */
#define DDRPHY_MR2_PASR_Msk              (0x7ul << DDRPHY_MR2_PASR_Pos)                    /*!< DDRPHY_T::MR2: PASR Mask               */

#define DDRPHY_MR2_CWL_Pos               (3)                                               /*!< DDRPHY_T::MR2: CWL Position            */
#define DDRPHY_MR2_CWL_Msk               (0x7ul << DDRPHY_MR2_CWL_Pos)                     /*!< DDRPHY_T::MR2: CWL Mask                */

#define DDRPHY_MR2_ASR_Pos               (6)                                               /*!< DDRPHY_T::MR2: ASR Position            */
#define DDRPHY_MR2_ASR_Msk               (0x1ul << DDRPHY_MR2_ASR_Pos)                     /*!< DDRPHY_T::MR2: ASR Mask                */

#define DDRPHY_MR2_SRT_Pos               (7)                                               /*!< DDRPHY_T::MR2: SRT Position            */
#define DDRPHY_MR2_SRT_Msk               (0x1ul << DDRPHY_MR2_SRT_Pos)                     /*!< DDRPHY_T::MR2: SRT Mask                */

#define DDRPHY_MR2_RTTWR_Pos             (9)                                               /*!< DDRPHY_T::MR2: RTTWR Position          */
#define DDRPHY_MR2_RTTWR_Msk             (0x3ul << DDRPHY_MR2_RTTWR_Pos)                   /*!< DDRPHY_T::MR2: RTTWR Mask              */

#define DDRPHY_MR3_MPRLOC_Pos            (0)                                               /*!< DDRPHY_T::MR3: MPRLOC Position         */
#define DDRPHY_MR3_MPRLOC_Msk            (0x3ul << DDRPHY_MR3_MPRLOC_Pos)                  /*!< DDRPHY_T::MR3: MPRLOC Mask             */

#define DDRPHY_MR3_MPR_Pos               (2)                                               /*!< DDRPHY_T::MR3: MPR Position            */
#define DDRPHY_MR3_MPR_Msk               (0x1ul << DDRPHY_MR3_MPR_Pos)                     /*!< DDRPHY_T::MR3: MPR Mask                */

#define DDRPHY_ODTCR_RDODT0_Pos          (0)                                               /*!< DDRPHY_T::ODTCR: RDODT0 Position       */
#define DDRPHY_ODTCR_RDODT0_Msk          (0xful << DDRPHY_ODTCR_RDODT0_Pos)                /*!< DDRPHY_T::ODTCR: RDODT0 Mask           */

#define DDRPHY_ODTCR_RDODT1_Pos          (4)                                               /*!< DDRPHY_T::ODTCR: RDODT1 Position       */
#define DDRPHY_ODTCR_RDODT1_Msk          (0xful << DDRPHY_ODTCR_RDODT1_Pos)                /*!< DDRPHY_T::ODTCR: RDODT1 Mask           */

#define DDRPHY_ODTCR_RDODT2_Pos          (8)                                               /*!< DDRPHY_T::ODTCR: RDODT2 Position       */
#define DDRPHY_ODTCR_RDODT2_Msk          (0xful << DDRPHY_ODTCR_RDODT2_Pos)                /*!< DDRPHY_T::ODTCR: RDODT2 Mask           */

#define DDRPHY_ODTCR_RDODT3_Pos          (12)                                              /*!< DDRPHY_T::ODTCR: RDODT3 Position       */
#define DDRPHY_ODTCR_RDODT3_Msk          (0xful << DDRPHY_ODTCR_RDODT3_Pos)                /*!< DDRPHY_T::ODTCR: RDODT3 Mask           */

#define DDRPHY_ODTCR_WRODT0_Pos          (16)                                              /*!< DDRPHY_T::ODTCR: WRODT0 Position       */
#define DDRPHY_ODTCR_WRODT0_Msk          (0xful << DDRPHY_ODTCR_WRODT0_Pos)                /*!< DDRPHY_T::ODTCR: WRODT0 Mask           */

#define DDRPHY_ODTCR_WRODT1_Pos          (20)                                              /*!< DDRPHY_T::ODTCR: WRODT1 Position       */
#define DDRPHY_ODTCR_WRODT1_Msk          (0xful << DDRPHY_ODTCR_WRODT1_Pos)                /*!< DDRPHY_T::ODTCR: WRODT1 Mask           */

#define DDRPHY_ODTCR_WRODT2_Pos          (24)                                              /*!< DDRPHY_T::ODTCR: WRODT2 Position       */
#define DDRPHY_ODTCR_WRODT2_Msk          (0xful << DDRPHY_ODTCR_WRODT2_Pos)                /*!< DDRPHY_T::ODTCR: WRODT2 Mask           */

#define DDRPHY_ODTCR_WRODT3_Pos          (28)                                              /*!< DDRPHY_T::ODTCR: WRODT3 Position       */
#define DDRPHY_ODTCR_WRODT3_Msk          (0xful << DDRPHY_ODTCR_WRODT3_Pos)                /*!< DDRPHY_T::ODTCR: WRODT3 Mask           */

#define DDRPHY_DTCR_DTCOL_Pos            (0)                                               /*!< DDRPHY_T::DTCR: DTCOL Position         */
#define DDRPHY_DTCR_DTCOL_Msk            (0xffful << DDRPHY_DTCR_DTCOL_Pos)                /*!< DDRPHY_T::DTCR: DTCOL Mask             */

#define DDRPHY_DTCR_DTROW_Pos            (12)                                              /*!< DDRPHY_T::DTCR: DTROW Position         */
#define DDRPHY_DTCR_DTROW_Msk            (0xfffful << DDRPHY_DTCR_DTROW_Pos)               /*!< DDRPHY_T::DTCR: DTROW Mask             */

#define DDRPHY_DTCR_DTBANK_Pos           (28)                                              /*!< DDRPHY_T::DTCR: DTBANK Position        */
#define DDRPHY_DTCR_DTBANK_Msk           (0x7ul << DDRPHY_DTCR_DTBANK_Pos)                 /*!< DDRPHY_T::DTCR: DTBANK Mask            */

#define DDRPHY_DTAR1_DTCOL_Pos           (0)                                               /*!< DDRPHY_T::DTAR1: DTCOL Position        */
#define DDRPHY_DTAR1_DTCOL_Msk           (0xffful << DDRPHY_DTAR1_DTCOL_Pos)               /*!< DDRPHY_T::DTAR1: DTCOL Mask            */

#define DDRPHY_DTAR1_DTROW_Pos           (12)                                              /*!< DDRPHY_T::DTAR1: DTROW Position        */
#define DDRPHY_DTAR1_DTROW_Msk           (0xfffful << DDRPHY_DTAR1_DTROW_Pos)              /*!< DDRPHY_T::DTAR1: DTROW Mask            */

#define DDRPHY_DTAR1_DTBANK_Pos          (28)                                              /*!< DDRPHY_T::DTAR1: DTBANK Position       */
#define DDRPHY_DTAR1_DTBANK_Msk          (0x7ul << DDRPHY_DTAR1_DTBANK_Pos)                /*!< DDRPHY_T::DTAR1: DTBANK Mask           */

#define DDRPHY_DTAR2_DTCOL_Pos           (0)                                               /*!< DDRPHY_T::DTAR2: DTCOL Position        */
#define DDRPHY_DTAR2_DTCOL_Msk           (0xffful << DDRPHY_DTAR2_DTCOL_Pos)               /*!< DDRPHY_T::DTAR2: DTCOL Mask            */

#define DDRPHY_DTAR2_DTROW_Pos           (12)                                              /*!< DDRPHY_T::DTAR2: DTROW Position        */
#define DDRPHY_DTAR2_DTROW_Msk           (0xfffful << DDRPHY_DTAR2_DTROW_Pos)              /*!< DDRPHY_T::DTAR2: DTROW Mask            */

#define DDRPHY_DTAR2_DTBANK_Pos          (28)                                              /*!< DDRPHY_T::DTAR2: DTBANK Position       */
#define DDRPHY_DTAR2_DTBANK_Msk          (0x7ul << DDRPHY_DTAR2_DTBANK_Pos)                /*!< DDRPHY_T::DTAR2: DTBANK Mask           */

#define DDRPHY_DTAR3_DTCOL_Pos           (0)                                               /*!< DDRPHY_T::DTAR3: DTCOL Position        */
#define DDRPHY_DTAR3_DTCOL_Msk           (0xffful << DDRPHY_DTAR3_DTCOL_Pos)               /*!< DDRPHY_T::DTAR3: DTCOL Mask            */

#define DDRPHY_DTAR3_DTROW_Pos           (12)                                              /*!< DDRPHY_T::DTAR3: DTROW Position        */
#define DDRPHY_DTAR3_DTROW_Msk           (0xfffful << DDRPHY_DTAR3_DTROW_Pos)              /*!< DDRPHY_T::DTAR3: DTROW Mask            */

#define DDRPHY_DTAR3_DTBANK_Pos          (28)                                              /*!< DDRPHY_T::DTAR3: DTBANK Position       */
#define DDRPHY_DTAR3_DTBANK_Msk          (0x7ul << DDRPHY_DTAR3_DTBANK_Pos)                /*!< DDRPHY_T::DTAR3: DTBANK Mask           */

#define DDRPHY_DTDR0_DTBYTE1_Pos         (0)                                               /*!< DDRPHY_T::DTDR0: DTBYTE1 Position      */
#define DDRPHY_DTDR0_DTBYTE1_Msk         (0xfful << DDRPHY_DTDR0_DTBYTE1_Pos)              /*!< DDRPHY_T::DTDR0: DTBYTE1 Mask          */

#define DDRPHY_DTDR0_DTBYTE0_Pos         (8)                                               /*!< DDRPHY_T::DTDR0: DTBYTE0 Position      */
#define DDRPHY_DTDR0_DTBYTE0_Msk         (0xfful << DDRPHY_DTDR0_DTBYTE0_Pos)              /*!< DDRPHY_T::DTDR0: DTBYTE0 Mask          */

#define DDRPHY_DTDR0_DTBYTE2_Pos         (16)                                              /*!< DDRPHY_T::DTDR0: DTBYTE2 Position      */
#define DDRPHY_DTDR0_DTBYTE2_Msk         (0xfful << DDRPHY_DTDR0_DTBYTE2_Pos)              /*!< DDRPHY_T::DTDR0: DTBYTE2 Mask          */

#define DDRPHY_DTDR0_DTBYTE3_Pos         (24)                                              /*!< DDRPHY_T::DTDR0: DTBYTE3 Position      */
#define DDRPHY_DTDR0_DTBYTE3_Msk         (0xfful << DDRPHY_DTDR0_DTBYTE3_Pos)              /*!< DDRPHY_T::DTDR0: DTBYTE3 Mask          */

#define DDRPHY_DTDR1_DTBYTE4_Pos         (0)                                               /*!< DDRPHY_T::DTDR1: DTBYTE4 Position      */
#define DDRPHY_DTDR1_DTBYTE4_Msk         (0xfful << DDRPHY_DTDR1_DTBYTE4_Pos)              /*!< DDRPHY_T::DTDR1: DTBYTE4 Mask          */

#define DDRPHY_DTDR1_DTBYTE5_Pos         (8)                                               /*!< DDRPHY_T::DTDR1: DTBYTE5 Position      */
#define DDRPHY_DTDR1_DTBYTE5_Msk         (0xfful << DDRPHY_DTDR1_DTBYTE5_Pos)              /*!< DDRPHY_T::DTDR1: DTBYTE5 Mask          */

#define DDRPHY_DTDR1_DTBYTE6_Pos         (16)                                              /*!< DDRPHY_T::DTDR1: DTBYTE6 Position      */
#define DDRPHY_DTDR1_DTBYTE6_Msk         (0xfful << DDRPHY_DTDR1_DTBYTE6_Pos)              /*!< DDRPHY_T::DTDR1: DTBYTE6 Mask          */

#define DDRPHY_DTDR1_DTBYTE7_Pos         (24)                                              /*!< DDRPHY_T::DTDR1: DTBYTE7 Position      */
#define DDRPHY_DTDR1_DTBYTE7_Msk         (0xfful << DDRPHY_DTDR1_DTBYTE7_Pos)              /*!< DDRPHY_T::DTDR1: DTBYTE7 Mask          */

#define DDRPHY_DTEDR0_DTWLMN_Pos         (0)                                               /*!< DDRPHY_T::DTEDR0: DTWLMN Position      */
#define DDRPHY_DTEDR0_DTWLMN_Msk         (0xfful << DDRPHY_DTEDR0_DTWLMN_Pos)              /*!< DDRPHY_T::DTEDR0: DTWLMN Mask          */

#define DDRPHY_DTEDR0_DTWLMX_Pos         (8)                                               /*!< DDRPHY_T::DTEDR0: DTWLMX Position      */
#define DDRPHY_DTEDR0_DTWLMX_Msk         (0xfful << DDRPHY_DTEDR0_DTWLMX_Pos)              /*!< DDRPHY_T::DTEDR0: DTWLMX Mask          */

#define DDRPHY_DTEDR0_DTWBMN_Pos         (16)                                              /*!< DDRPHY_T::DTEDR0: DTWBMN Position      */
#define DDRPHY_DTEDR0_DTWBMN_Msk         (0xfful << DDRPHY_DTEDR0_DTWBMN_Pos)              /*!< DDRPHY_T::DTEDR0: DTWBMN Mask          */

#define DDRPHY_DTEDR0_DTWBMX_Pos         (24)                                              /*!< DDRPHY_T::DTEDR0: DTWBMX Position      */
#define DDRPHY_DTEDR0_DTWBMX_Msk         (0xfful << DDRPHY_DTEDR0_DTWBMX_Pos)              /*!< DDRPHY_T::DTEDR0: DTWBMX Mask          */

#define DDRPHY_DTEDR1_DTRLMN_Pos         (0)                                               /*!< DDRPHY_T::DTEDR1: DTRLMN Position      */
#define DDRPHY_DTEDR1_DTRLMN_Msk         (0xfful << DDRPHY_DTEDR1_DTRLMN_Pos)              /*!< DDRPHY_T::DTEDR1: DTRLMN Mask          */

#define DDRPHY_DTEDR1_DTRLMX_Pos         (8)                                               /*!< DDRPHY_T::DTEDR1: DTRLMX Position      */
#define DDRPHY_DTEDR1_DTRLMX_Msk         (0xfful << DDRPHY_DTEDR1_DTRLMX_Pos)              /*!< DDRPHY_T::DTEDR1: DTRLMX Mask          */

#define DDRPHY_DTEDR1_DTRBMN_Pos         (16)                                              /*!< DDRPHY_T::DTEDR1: DTRBMN Position      */
#define DDRPHY_DTEDR1_DTRBMN_Msk         (0xfful << DDRPHY_DTEDR1_DTRBMN_Pos)              /*!< DDRPHY_T::DTEDR1: DTRBMN Mask          */

#define DDRPHY_DTEDR1_DTRBMX_Pos         (24)                                              /*!< DDRPHY_T::DTEDR1: DTRBMX Position      */
#define DDRPHY_DTEDR1_DTRBMX_Msk         (0xfful << DDRPHY_DTEDR1_DTRBMX_Pos)              /*!< DDRPHY_T::DTEDR1: DTRBMX Mask          */

#define DDRPHY_PGCR2_tREFPRD_Pos         (0)                                               /*!< DDRPHY_T::PGCR2: tREFPRD Position      */
#define DDRPHY_PGCR2_tREFPRD_Msk         (0x3fffful << DDRPHY_PGCR2_tREFPRD_Pos)           /*!< DDRPHY_T::PGCR2: tREFPRD Mask          */

#define DDRPHY_PGCR2_NOBUB_Pos           (18)                                              /*!< DDRPHY_T::PGCR2: NOBUB Position        */
#define DDRPHY_PGCR2_NOBUB_Msk           (0x1ul << DDRPHY_PGCR2_NOBUB_Pos)                 /*!< DDRPHY_T::PGCR2: NOBUB Mask            */

#define DDRPHY_PGCR2_FXDLAT_Pos          (19)                                              /*!< DDRPHY_T::PGCR2: FXDLAT Position       */
#define DDRPHY_PGCR2_FXDLAT_Msk          (0x1ul << DDRPHY_PGCR2_FXDLAT_Pos)                /*!< DDRPHY_T::PGCR2: FXDLAT Mask           */

#define DDRPHY_PGCR2_DTPMXTMR_Pos        (20)                                              /*!< DDRPHY_T::PGCR2: DTPMXTMR Position     */
#define DDRPHY_PGCR2_DTPMXTMR_Msk        (0xfful << DDRPHY_PGCR2_DTPMXTMR_Pos)             /*!< DDRPHY_T::PGCR2: DTPMXTMR Mask         */

#define DDRPHY_PGCR2_SHRAC_Pos           (28)                                              /*!< DDRPHY_T::PGCR2: SHRAC Position        */
#define DDRPHY_PGCR2_SHRAC_Msk           (0x1ul << DDRPHY_PGCR2_SHRAC_Pos)                 /*!< DDRPHY_T::PGCR2: SHRAC Mask            */

#define DDRPHY_PGCR2_ACPDDC_Pos          (29)                                              /*!< DDRPHY_T::PGCR2: ACPDDC Position       */
#define DDRPHY_PGCR2_ACPDDC_Msk          (0x1ul << DDRPHY_PGCR2_ACPDDC_Pos)                /*!< DDRPHY_T::PGCR2: ACPDDC Mask           */

#define DDRPHY_PGCR2_LPMSTRC0_Pos        (30)                                              /*!< DDRPHY_T::PGCR2: LPMSTRC0 Position     */
#define DDRPHY_PGCR2_LPMSTRC0_Msk        (0x1ul << DDRPHY_PGCR2_LPMSTRC0_Pos)              /*!< DDRPHY_T::PGCR2: LPMSTRC0 Mask         */

#define DDRPHY_PGCR2_DYNACPDD_Pos        (31)                                              /*!< DDRPHY_T::PGCR2: DYNACPDD Position     */
#define DDRPHY_PGCR2_DYNACPDD_Msk        (0x1ul << DDRPHY_PGCR2_DYNACPDD_Pos)              /*!< DDRPHY_T::PGCR2: DYNACPDD Mask         */

#define DDRPHY_RDIMMGCR0_RDIMM_Pos       (0)                                               /*!< DDRPHY_T::RDIMMGCR0: RDIMM Position    */
#define DDRPHY_RDIMMGCR0_RDIMM_Msk       (0x1ul << DDRPHY_RDIMMGCR0_RDIMM_Pos)             /*!< DDRPHY_T::RDIMMGCR0: RDIMM Mask        */

#define DDRPHY_RDIMMGCR0_ERRNOREG_Pos    (1)                                               /*!< DDRPHY_T::RDIMMGCR0: ERRNOREG Position */
#define DDRPHY_RDIMMGCR0_ERRNOREG_Msk    (0x1ul << DDRPHY_RDIMMGCR0_ERRNOREG_Pos)          /*!< DDRPHY_T::RDIMMGCR0: ERRNOREG Mask     */

#define DDRPHY_RDIMMGCR0_SOPERR_Pos      (2)                                               /*!< DDRPHY_T::RDIMMGCR0: SOPERR Position   */
#define DDRPHY_RDIMMGCR0_SOPERR_Msk      (0x1ul << DDRPHY_RDIMMGCR0_SOPERR_Pos)            /*!< DDRPHY_T::RDIMMGCR0: SOPERR Mask       */

#define DDRPHY_RDIMMGCR0_PARINODT_Pos    (14)                                              /*!< DDRPHY_T::RDIMMGCR0: PARINODT Position */
#define DDRPHY_RDIMMGCR0_PARINODT_Msk    (0x1ul << DDRPHY_RDIMMGCR0_PARINODT_Pos)          /*!< DDRPHY_T::RDIMMGCR0: PARINODT Mask     */

#define DDRPHY_RDIMMGCR0_PARINPDD_Pos    (15)                                              /*!< DDRPHY_T::RDIMMGCR0: PARINPDD Position */
#define DDRPHY_RDIMMGCR0_PARINPDD_Msk    (0x1ul << DDRPHY_RDIMMGCR0_PARINPDD_Pos)          /*!< DDRPHY_T::RDIMMGCR0: PARINPDD Mask     */

#define DDRPHY_RDIMMGCR0_PARINPDR_Pos    (16)                                              /*!< DDRPHY_T::RDIMMGCR0: PARINPDR Position */
#define DDRPHY_RDIMMGCR0_PARINPDR_Msk    (0x1ul << DDRPHY_RDIMMGCR0_PARINPDR_Pos)          /*!< DDRPHY_T::RDIMMGCR0: PARINPDR Mask     */

#define DDRPHY_RDIMMGCR0_PARINIOM_Pos    (17)                                              /*!< DDRPHY_T::RDIMMGCR0: PARINIOM Position */
#define DDRPHY_RDIMMGCR0_PARINIOM_Msk    (0x1ul << DDRPHY_RDIMMGCR0_PARINIOM_Pos)          /*!< DDRPHY_T::RDIMMGCR0: PARINIOM Mask     */

#define DDRPHY_RDIMMGCR0_PARINOE_Pos     (18)                                              /*!< DDRPHY_T::RDIMMGCR0: PARINOE Position  */
#define DDRPHY_RDIMMGCR0_PARINOE_Msk     (0x1ul << DDRPHY_RDIMMGCR0_PARINOE_Pos)           /*!< DDRPHY_T::RDIMMGCR0: PARINOE Mask      */

#define DDRPHY_RDIMMGCR0_ERROUTODT_Pos   (19)                                              /*!< DDRPHY_T::RDIMMGCR0: ERROUTODT Position*/
#define DDRPHY_RDIMMGCR0_ERROUTODT_Msk   (0x1ul << DDRPHY_RDIMMGCR0_ERROUTODT_Pos)         /*!< DDRPHY_T::RDIMMGCR0: ERROUTODT Mask    */

#define DDRPHY_RDIMMGCR0_ERROUTPDD_Pos   (20)                                              /*!< DDRPHY_T::RDIMMGCR0: ERROUTPDD Position*/
#define DDRPHY_RDIMMGCR0_ERROUTPDD_Msk   (0x1ul << DDRPHY_RDIMMGCR0_ERROUTPDD_Pos)         /*!< DDRPHY_T::RDIMMGCR0: ERROUTPDD Mask    */

#define DDRPHY_RDIMMGCR0_ERROUTPDR_Pos   (21)                                              /*!< DDRPHY_T::RDIMMGCR0: ERROUTPDR Position*/
#define DDRPHY_RDIMMGCR0_ERROUTPDR_Msk   (0x1ul << DDRPHY_RDIMMGCR0_ERROUTPDR_Pos)         /*!< DDRPHY_T::RDIMMGCR0: ERROUTPDR Mask    */

#define DDRPHY_RDIMMGCR0_ERROUTIOM_Pos   (22)                                              /*!< DDRPHY_T::RDIMMGCR0: ERROUTIOM Position*/
#define DDRPHY_RDIMMGCR0_ERROUTIOM_Msk   (0x1ul << DDRPHY_RDIMMGCR0_ERROUTIOM_Pos)         /*!< DDRPHY_T::RDIMMGCR0: ERROUTIOM Mask    */

#define DDRPHY_RDIMMGCR0_ERROUTOE_Pos    (23)                                              /*!< DDRPHY_T::RDIMMGCR0: ERROUTOE Position */
#define DDRPHY_RDIMMGCR0_ERROUTOE_Msk    (0x1ul << DDRPHY_RDIMMGCR0_ERROUTOE_Pos)          /*!< DDRPHY_T::RDIMMGCR0: ERROUTOE Mask     */

#define DDRPHY_RDIMMGCR0_RDIMMODT_Pos    (24)                                              /*!< DDRPHY_T::RDIMMGCR0: RDIMMODT Position */
#define DDRPHY_RDIMMGCR0_RDIMMODT_Msk    (0x1ul << DDRPHY_RDIMMGCR0_RDIMMODT_Pos)          /*!< DDRPHY_T::RDIMMGCR0: RDIMMODT Mask     */

#define DDRPHY_RDIMMGCR0_RDIMMPDD_Pos    (25)                                              /*!< DDRPHY_T::RDIMMGCR0: RDIMMPDD Position */
#define DDRPHY_RDIMMGCR0_RDIMMPDD_Msk    (0x1ul << DDRPHY_RDIMMGCR0_RDIMMPDD_Pos)          /*!< DDRPHY_T::RDIMMGCR0: RDIMMPDD Mask     */

#define DDRPHY_RDIMMGCR0_RDIMMPDR_Pos    (26)                                              /*!< DDRPHY_T::RDIMMGCR0: RDIMMPDR Position */
#define DDRPHY_RDIMMGCR0_RDIMMPDR_Msk    (0x1ul << DDRPHY_RDIMMGCR0_RDIMMPDR_Pos)          /*!< DDRPHY_T::RDIMMGCR0: RDIMMPDR Mask     */

#define DDRPHY_RDIMMGCR0_RDIMMIOM_Pos    (27)                                              /*!< DDRPHY_T::RDIMMGCR0: RDIMMIOM Position */
#define DDRPHY_RDIMMGCR0_RDIMMIOM_Msk    (0x1ul << DDRPHY_RDIMMGCR0_RDIMMIOM_Pos)          /*!< DDRPHY_T::RDIMMGCR0: RDIMMIOM Mask     */

#define DDRPHY_RDIMMGCR0_QCSENOE_Pos     (28)                                              /*!< DDRPHY_T::RDIMMGCR0: QCSENOE Position  */
#define DDRPHY_RDIMMGCR0_QCSENOE_Msk     (0x1ul << DDRPHY_RDIMMGCR0_QCSENOE_Pos)           /*!< DDRPHY_T::RDIMMGCR0: QCSENOE Mask      */

#define DDRPHY_RDIMMGCR0_MIRROROE_Pos    (29)                                              /*!< DDRPHY_T::RDIMMGCR0: MIRROROE Position */
#define DDRPHY_RDIMMGCR0_MIRROROE_Msk    (0x1ul << DDRPHY_RDIMMGCR0_MIRROROE_Pos)          /*!< DDRPHY_T::RDIMMGCR0: MIRROROE Mask     */

#define DDRPHY_RDIMMGCR0_QCSEN_Pos       (30)                                              /*!< DDRPHY_T::RDIMMGCR0: QCSEN Position    */
#define DDRPHY_RDIMMGCR0_QCSEN_Msk       (0x1ul << DDRPHY_RDIMMGCR0_QCSEN_Pos)             /*!< DDRPHY_T::RDIMMGCR0: QCSEN Mask        */

#define DDRPHY_RDIMMGCR0_MIRROR_Pos      (31)                                              /*!< DDRPHY_T::RDIMMGCR0: MIRROR Position   */
#define DDRPHY_RDIMMGCR0_MIRROR_Msk      (0x1ul << DDRPHY_RDIMMGCR0_MIRROR_Pos)            /*!< DDRPHY_T::RDIMMGCR0: MIRROR Mask       */

#define DDRPHY_RDIMMGCR1_tBCSTAB_Pos     (0)                                               /*!< DDRPHY_T::RDIMMGCR1: tBCSTAB Position  */
#define DDRPHY_RDIMMGCR1_tBCSTAB_Msk     (0xffful << DDRPHY_RDIMMGCR1_tBCSTAB_Pos)         /*!< DDRPHY_T::RDIMMGCR1: tBCSTAB Mask      */

#define DDRPHY_RDIMMGCR1_tBCMRD_Pos      (12)                                              /*!< DDRPHY_T::RDIMMGCR1: tBCMRD Position   */
#define DDRPHY_RDIMMGCR1_tBCMRD_Msk      (0x7ul << DDRPHY_RDIMMGCR1_tBCMRD_Pos)            /*!< DDRPHY_T::RDIMMGCR1: tBCMRD Mask       */

#define DDRPHY_RDIMMGCR1_CRINIT_Pos      (16)                                              /*!< DDRPHY_T::RDIMMGCR1: CRINIT Position   */
#define DDRPHY_RDIMMGCR1_CRINIT_Msk      (0xfffful << DDRPHY_RDIMMGCR1_CRINIT_Pos)         /*!< DDRPHY_T::RDIMMGCR1: CRINIT Mask       */

#define DDRPHY_RDIMMCR0_RC0_Pos          (0)                                               /*!< DDRPHY_T::RDIMMCR0: RC0 Position       */
#define DDRPHY_RDIMMCR0_RC0_Msk          (0xful << DDRPHY_RDIMMCR0_RC0_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC0 Mask           */

#define DDRPHY_RDIMMCR0_RC1_Pos          (4)                                               /*!< DDRPHY_T::RDIMMCR0: RC1 Position       */
#define DDRPHY_RDIMMCR0_RC1_Msk          (0xful << DDRPHY_RDIMMCR0_RC1_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC1 Mask           */

#define DDRPHY_RDIMMCR0_RC2_Pos          (8)                                               /*!< DDRPHY_T::RDIMMCR0: RC2 Position       */
#define DDRPHY_RDIMMCR0_RC2_Msk          (0xful << DDRPHY_RDIMMCR0_RC2_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC2 Mask           */

#define DDRPHY_RDIMMCR0_RC3_Pos          (12)                                              /*!< DDRPHY_T::RDIMMCR0: RC3 Position       */
#define DDRPHY_RDIMMCR0_RC3_Msk          (0xful << DDRPHY_RDIMMCR0_RC3_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC3 Mask           */

#define DDRPHY_RDIMMCR0_RC4_Pos          (16)                                              /*!< DDRPHY_T::RDIMMCR0: RC4 Position       */
#define DDRPHY_RDIMMCR0_RC4_Msk          (0xful << DDRPHY_RDIMMCR0_RC4_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC4 Mask           */

#define DDRPHY_RDIMMCR0_RC5_Pos          (20)                                              /*!< DDRPHY_T::RDIMMCR0: RC5 Position       */
#define DDRPHY_RDIMMCR0_RC5_Msk          (0xful << DDRPHY_RDIMMCR0_RC5_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC5 Mask           */

#define DDRPHY_RDIMMCR0_RC6_Pos          (24)                                              /*!< DDRPHY_T::RDIMMCR0: RC6 Position       */
#define DDRPHY_RDIMMCR0_RC6_Msk          (0xful << DDRPHY_RDIMMCR0_RC6_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC6 Mask           */

#define DDRPHY_RDIMMCR0_RC7_Pos          (28)                                              /*!< DDRPHY_T::RDIMMCR0: RC7 Position       */
#define DDRPHY_RDIMMCR0_RC7_Msk          (0xful << DDRPHY_RDIMMCR0_RC7_Pos)                /*!< DDRPHY_T::RDIMMCR0: RC7 Mask           */

#define DDRPHY_RDIMMCR1_RC8_Pos          (0)                                               /*!< DDRPHY_T::RDIMMCR1: RC8 Position       */
#define DDRPHY_RDIMMCR1_RC8_Msk          (0xful << DDRPHY_RDIMMCR1_RC8_Pos)                /*!< DDRPHY_T::RDIMMCR1: RC8 Mask           */

#define DDRPHY_RDIMMCR1_RC9_Pos          (4)                                               /*!< DDRPHY_T::RDIMMCR1: RC9 Position       */
#define DDRPHY_RDIMMCR1_RC9_Msk          (0xful << DDRPHY_RDIMMCR1_RC9_Pos)                /*!< DDRPHY_T::RDIMMCR1: RC9 Mask           */

#define DDRPHY_RDIMMCR1_RC10_Pos         (8)                                               /*!< DDRPHY_T::RDIMMCR1: RC10 Position      */
#define DDRPHY_RDIMMCR1_RC10_Msk         (0xful << DDRPHY_RDIMMCR1_RC10_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC10 Mask          */

#define DDRPHY_RDIMMCR1_RC11_Pos         (12)                                              /*!< DDRPHY_T::RDIMMCR1: RC11 Position      */
#define DDRPHY_RDIMMCR1_RC11_Msk         (0xful << DDRPHY_RDIMMCR1_RC11_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC11 Mask          */

#define DDRPHY_RDIMMCR1_RC12_Pos         (16)                                              /*!< DDRPHY_T::RDIMMCR1: RC12 Position      */
#define DDRPHY_RDIMMCR1_RC12_Msk         (0xful << DDRPHY_RDIMMCR1_RC12_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC12 Mask          */

#define DDRPHY_RDIMMCR1_RC13_Pos         (20)                                              /*!< DDRPHY_T::RDIMMCR1: RC13 Position      */
#define DDRPHY_RDIMMCR1_RC13_Msk         (0xful << DDRPHY_RDIMMCR1_RC13_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC13 Mask          */

#define DDRPHY_RDIMMCR1_RC14_Pos         (24)                                              /*!< DDRPHY_T::RDIMMCR1: RC14 Position      */
#define DDRPHY_RDIMMCR1_RC14_Msk         (0xful << DDRPHY_RDIMMCR1_RC14_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC14 Mask          */

#define DDRPHY_RDIMMCR1_RC15_Pos         (28)                                              /*!< DDRPHY_T::RDIMMCR1: RC15 Position      */
#define DDRPHY_RDIMMCR1_RC15_Msk         (0xful << DDRPHY_RDIMMCR1_RC15_Pos)               /*!< DDRPHY_T::RDIMMCR1: RC15 Mask          */

#define DDRPHY_DCUAR_CWADDR_Pos          (0)                                               /*!< DDRPHY_T::DCUAR: CWADDR Position       */
#define DDRPHY_DCUAR_CWADDR_Msk          (0xful << DDRPHY_DCUAR_CWADDR_Pos)                /*!< DDRPHY_T::DCUAR: CWADDR Mask           */

#define DDRPHY_DCUAR_CSADDR_Pos          (4)                                               /*!< DDRPHY_T::DCUAR: CSADDR Position       */
#define DDRPHY_DCUAR_CSADDR_Msk          (0xful << DDRPHY_DCUAR_CSADDR_Pos)                /*!< DDRPHY_T::DCUAR: CSADDR Mask           */

#define DDRPHY_DCUAR_CSEL_Pos            (8)                                               /*!< DDRPHY_T::DCUAR: CSEL Position         */
#define DDRPHY_DCUAR_CSEL_Msk            (0x3ul << DDRPHY_DCUAR_CSEL_Pos)                  /*!< DDRPHY_T::DCUAR: CSEL Mask             */

#define DDRPHY_DCUAR_INCA_Pos            (10)                                              /*!< DDRPHY_T::DCUAR: INCA Position         */
#define DDRPHY_DCUAR_INCA_Msk            (0x1ul << DDRPHY_DCUAR_INCA_Pos)                  /*!< DDRPHY_T::DCUAR: INCA Mask             */

#define DDRPHY_DCUAR_ATYPE_Pos           (11)                                              /*!< DDRPHY_T::DCUAR: ATYPE Position        */
#define DDRPHY_DCUAR_ATYPE_Msk           (0x1ul << DDRPHY_DCUAR_ATYPE_Pos)                 /*!< DDRPHY_T::DCUAR: ATYPE Mask            */

#define DDRPHY_DCUDR_CDATA_Pos           (0)                                               /*!< DDRPHY_T::DCUDR: CDATA Position        */
#define DDRPHY_DCUDR_CDATA_Msk           (0xfffffffful << DDRPHY_DCUDR_CDATA_Pos)          /*!< DDRPHY_T::DCUDR: CDATA Mask            */

#define DDRPHY_DCURR_DINST_Pos           (0)                                               /*!< DDRPHY_T::DCURR: DINST Position        */
#define DDRPHY_DCURR_DINST_Msk           (0xful << DDRPHY_DCURR_DINST_Pos)                 /*!< DDRPHY_T::DCURR: DINST Mask            */

#define DDRPHY_DCURR_SADDR_Pos           (4)                                               /*!< DDRPHY_T::DCURR: SADDR Position        */
#define DDRPHY_DCURR_SADDR_Msk           (0xful << DDRPHY_DCURR_SADDR_Pos)                 /*!< DDRPHY_T::DCURR: SADDR Mask            */

#define DDRPHY_DCURR_EADDR_Pos           (8)                                               /*!< DDRPHY_T::DCURR: EADDR Position        */
#define DDRPHY_DCURR_EADDR_Msk           (0xful << DDRPHY_DCURR_EADDR_Pos)                 /*!< DDRPHY_T::DCURR: EADDR Mask            */

#define DDRPHY_DCURR_NFAIL_Pos           (12)                                              /*!< DDRPHY_T::DCURR: NFAIL Position        */
#define DDRPHY_DCURR_NFAIL_Msk           (0xfful << DDRPHY_DCURR_NFAIL_Pos)                /*!< DDRPHY_T::DCURR: NFAIL Mask            */

#define DDRPHY_DCURR_SONF_Pos            (20)                                              /*!< DDRPHY_T::DCURR: SONF Position         */
#define DDRPHY_DCURR_SONF_Msk            (0x1ul << DDRPHY_DCURR_SONF_Pos)                  /*!< DDRPHY_T::DCURR: SONF Mask             */

#define DDRPHY_DCURR_SCOF_Pos            (21)                                              /*!< DDRPHY_T::DCURR: SCOF Position         */
#define DDRPHY_DCURR_SCOF_Msk            (0x1ul << DDRPHY_DCURR_SCOF_Pos)                  /*!< DDRPHY_T::DCURR: SCOF Mask             */

#define DDRPHY_DCURR_RCEN_Pos            (22)                                              /*!< DDRPHY_T::DCURR: RCEN Position         */
#define DDRPHY_DCURR_RCEN_Msk            (0x1ul << DDRPHY_DCURR_RCEN_Pos)                  /*!< DDRPHY_T::DCURR: RCEN Mask             */

#define DDRPHY_DCURR_XCEN_Pos            (23)                                              /*!< DDRPHY_T::DCURR: XCEN Position         */
#define DDRPHY_DCURR_XCEN_Msk            (0x1ul << DDRPHY_DCURR_XCEN_Pos)                  /*!< DDRPHY_T::DCURR: XCEN Mask             */

#define DDRPHY_DCULR_LSADDR_Pos          (0)                                               /*!< DDRPHY_T::DCULR: LSADDR Position       */
#define DDRPHY_DCULR_LSADDR_Msk          (0xful << DDRPHY_DCULR_LSADDR_Pos)                /*!< DDRPHY_T::DCULR: LSADDR Mask           */

#define DDRPHY_DCULR_LEADDR_Pos          (4)                                               /*!< DDRPHY_T::DCULR: LEADDR Position       */
#define DDRPHY_DCULR_LEADDR_Msk          (0xful << DDRPHY_DCULR_LEADDR_Pos)                /*!< DDRPHY_T::DCULR: LEADDR Mask           */

#define DDRPHY_DCULR_LCNT_Pos            (8)                                               /*!< DDRPHY_T::DCULR: LCNT Position         */
#define DDRPHY_DCULR_LCNT_Msk            (0xfful << DDRPHY_DCULR_LCNT_Pos)                 /*!< DDRPHY_T::DCULR: LCNT Mask             */

#define DDRPHY_DCULR_LINF_Pos            (16)                                              /*!< DDRPHY_T::DCULR: LINF Position         */
#define DDRPHY_DCULR_LINF_Msk            (0x1ul << DDRPHY_DCULR_LINF_Pos)                  /*!< DDRPHY_T::DCULR: LINF Mask             */

#define DDRPHY_DCULR_IDA_Pos             (17)                                              /*!< DDRPHY_T::DCULR: IDA Position          */
#define DDRPHY_DCULR_IDA_Msk             (0x1ul << DDRPHY_DCULR_IDA_Pos)                   /*!< DDRPHY_T::DCULR: IDA Mask              */

#define DDRPHY_DCULR_XLEADDR_Pos         (28)                                              /*!< DDRPHY_T::DCULR: XLEADDR Position      */
#define DDRPHY_DCULR_XLEADDR_Msk         (0xful << DDRPHY_DCULR_XLEADDR_Pos)               /*!< DDRPHY_T::DCULR: XLEADDR Mask          */

#define DDRPHY_DCUGCR_RCSW_Pos           (0)                                               /*!< DDRPHY_T::DCUGCR: RCSW Position        */
#define DDRPHY_DCUGCR_RCSW_Msk           (0xfffful << DDRPHY_DCUGCR_RCSW_Pos)              /*!< DDRPHY_T::DCUGCR: RCSW Mask            */

#define DDRPHY_DCUTPR_tDCUT0_Pos         (0)                                               /*!< DDRPHY_T::DCUTPR: tDCUT0 Position      */
#define DDRPHY_DCUTPR_tDCUT0_Msk         (0xfful << DDRPHY_DCUTPR_tDCUT0_Pos)              /*!< DDRPHY_T::DCUTPR: tDCUT0 Mask          */

#define DDRPHY_DCUTPR_tDCUT1_Pos         (8)                                               /*!< DDRPHY_T::DCUTPR: tDCUT1 Position      */
#define DDRPHY_DCUTPR_tDCUT1_Msk         (0xfful << DDRPHY_DCUTPR_tDCUT1_Pos)              /*!< DDRPHY_T::DCUTPR: tDCUT1 Mask          */

#define DDRPHY_DCUTPR_tDCUT2_Pos         (16)                                              /*!< DDRPHY_T::DCUTPR: tDCUT2 Position      */
#define DDRPHY_DCUTPR_tDCUT2_Msk         (0xfful << DDRPHY_DCUTPR_tDCUT2_Pos)              /*!< DDRPHY_T::DCUTPR: tDCUT2 Mask          */

#define DDRPHY_DCUTPR_tDCUT3_Pos         (24)                                              /*!< DDRPHY_T::DCUTPR: tDCUT3 Position      */
#define DDRPHY_DCUTPR_tDCUT3_Msk         (0xfful << DDRPHY_DCUTPR_tDCUT3_Pos)              /*!< DDRPHY_T::DCUTPR: tDCUT3 Mask          */

#define DDRPHY_DCUSR0_RDONE_Pos          (0)                                               /*!< DDRPHY_T::DCUSR0: RDONE Position       */
#define DDRPHY_DCUSR0_RDONE_Msk          (0x1ul << DDRPHY_DCUSR0_RDONE_Pos)                /*!< DDRPHY_T::DCUSR0: RDONE Mask           */

#define DDRPHY_DCUSR0_CFAIL_Pos          (1)                                               /*!< DDRPHY_T::DCUSR0: CFAIL Position       */
#define DDRPHY_DCUSR0_CFAIL_Msk          (0x1ul << DDRPHY_DCUSR0_CFAIL_Pos)                /*!< DDRPHY_T::DCUSR0: CFAIL Mask           */

#define DDRPHY_DCUSR0_CFULL_Pos          (2)                                               /*!< DDRPHY_T::DCUSR0: CFULL Position       */
#define DDRPHY_DCUSR0_CFULL_Msk          (0x1ul << DDRPHY_DCUSR0_CFULL_Pos)                /*!< DDRPHY_T::DCUSR0: CFULL Mask           */

#define DDRPHY_DCUSR1_RDCNT_Pos          (0)                                               /*!< DDRPHY_T::DCUSR1: RDCNT Position       */
#define DDRPHY_DCUSR1_RDCNT_Msk          (0xfffful << DDRPHY_DCUSR1_RDCNT_Pos)             /*!< DDRPHY_T::DCUSR1: RDCNT Mask           */

#define DDRPHY_DCUSR1_FLCNT_Pos          (16)                                              /*!< DDRPHY_T::DCUSR1: FLCNT Position       */
#define DDRPHY_DCUSR1_FLCNT_Msk          (0xfful << DDRPHY_DCUSR1_FLCNT_Pos)               /*!< DDRPHY_T::DCUSR1: FLCNT Mask           */

#define DDRPHY_DCUSR1_LPCNT_Pos          (24)                                              /*!< DDRPHY_T::DCUSR1: LPCNT Position       */
#define DDRPHY_DCUSR1_LPCNT_Msk          (0xfful << DDRPHY_DCUSR1_LPCNT_Pos)               /*!< DDRPHY_T::DCUSR1: LPCNT Mask           */

#define DDRPHY_BISTRR_BINST_Pos          (0)                                               /*!< DDRPHY_T::BISTRR: BINST Position       */
#define DDRPHY_BISTRR_BINST_Msk          (0x7ul << DDRPHY_BISTRR_BINST_Pos)                /*!< DDRPHY_T::BISTRR: BINST Mask           */

#define DDRPHY_BISTRR_BMODE_Pos          (3)                                               /*!< DDRPHY_T::BISTRR: BMODE Position       */
#define DDRPHY_BISTRR_BMODE_Msk          (0x1ul << DDRPHY_BISTRR_BMODE_Pos)                /*!< DDRPHY_T::BISTRR: BMODE Mask           */

#define DDRPHY_BISTRR_BINF_Pos           (4)                                               /*!< DDRPHY_T::BISTRR: BINF Position        */
#define DDRPHY_BISTRR_BINF_Msk           (0x1ul << DDRPHY_BISTRR_BINF_Pos)                 /*!< DDRPHY_T::BISTRR: BINF Mask            */

#define DDRPHY_BISTRR_NFAIL_Pos          (5)                                               /*!< DDRPHY_T::BISTRR: NFAIL Position       */
#define DDRPHY_BISTRR_NFAIL_Msk          (0xfful << DDRPHY_BISTRR_NFAIL_Pos)               /*!< DDRPHY_T::BISTRR: NFAIL Mask           */

#define DDRPHY_BISTRR_BSONF_Pos          (13)                                              /*!< DDRPHY_T::BISTRR: BSONF Position       */
#define DDRPHY_BISTRR_BSONF_Msk          (0x1ul << DDRPHY_BISTRR_BSONF_Pos)                /*!< DDRPHY_T::BISTRR: BSONF Mask           */

#define DDRPHY_BISTRR_BDXEN_Pos          (14)                                              /*!< DDRPHY_T::BISTRR: BDXEN Position       */
#define DDRPHY_BISTRR_BDXEN_Msk          (0x1ul << DDRPHY_BISTRR_BDXEN_Pos)                /*!< DDRPHY_T::BISTRR: BDXEN Mask           */

#define DDRPHY_BISTRR_BACEN_Pos          (15)                                              /*!< DDRPHY_T::BISTRR: BACEN Position       */
#define DDRPHY_BISTRR_BACEN_Msk          (0x1ul << DDRPHY_BISTRR_BACEN_Pos)                /*!< DDRPHY_T::BISTRR: BACEN Mask           */

#define DDRPHY_BISTRR_BDMEN_Pos          (16)                                              /*!< DDRPHY_T::BISTRR: BDMEN Position       */
#define DDRPHY_BISTRR_BDMEN_Msk          (0x1ul << DDRPHY_BISTRR_BDMEN_Pos)                /*!< DDRPHY_T::BISTRR: BDMEN Mask           */

#define DDRPHY_BISTRR_BDPAT_Pos          (17)                                              /*!< DDRPHY_T::BISTRR: BDPAT Position       */
#define DDRPHY_BISTRR_BDPAT_Msk          (0x3ul << DDRPHY_BISTRR_BDPAT_Pos)                /*!< DDRPHY_T::BISTRR: BDPAT Mask           */

#define DDRPHY_BISTRR_BDXSEL_Pos         (19)                                              /*!< DDRPHY_T::BISTRR: BDXSEL Position      */
#define DDRPHY_BISTRR_BDXSEL_Msk         (0xful << DDRPHY_BISTRR_BDXSEL_Pos)               /*!< DDRPHY_T::BISTRR: BDXSEL Mask          */

#define DDRPHY_BISTRR_BCKSEL_Pos         (23)                                              /*!< DDRPHY_T::BISTRR: BCKSEL Position      */
#define DDRPHY_BISTRR_BCKSEL_Msk         (0x3ul << DDRPHY_BISTRR_BCKSEL_Pos)               /*!< DDRPHY_T::BISTRR: BCKSEL Mask          */

#define DDRPHY_BISTRR_BCCSEL_Pos         (25)                                              /*!< DDRPHY_T::BISTRR: BCCSEL Position      */
#define DDRPHY_BISTRR_BCCSEL_Msk         (0x3ul << DDRPHY_BISTRR_BCCSEL_Pos)               /*!< DDRPHY_T::BISTRR: BCCSEL Mask          */

#define DDRPHY_BISTWCR_BWCNT_Pos         (0)                                               /*!< DDRPHY_T::BISTWCR: BWCNT Position      */
#define DDRPHY_BISTWCR_BWCNT_Msk         (0xfffful << DDRPHY_BISTWCR_BWCNT_Pos)            /*!< DDRPHY_T::BISTWCR: BWCNT Mask          */

#define DDRPHY_BISTMSKR0_AMSK_Pos        (0)                                               /*!< DDRPHY_T::BISTMSKR0: AMSK Position     */
#define DDRPHY_BISTMSKR0_AMSK_Msk        (0xfffful << DDRPHY_BISTMSKR0_AMSK_Pos)           /*!< DDRPHY_T::BISTMSKR0: AMSK Mask         */

#define DDRPHY_BISTMSKR0_BAMSK_Pos       (16)                                              /*!< DDRPHY_T::BISTMSKR0: BAMSK Position    */
#define DDRPHY_BISTMSKR0_BAMSK_Msk       (0x7ul << DDRPHY_BISTMSKR0_BAMSK_Pos)             /*!< DDRPHY_T::BISTMSKR0: BAMSK Mask        */

#define DDRPHY_BISTMSKR0_WEMSK_Pos       (19)                                              /*!< DDRPHY_T::BISTMSKR0: WEMSK Position    */
#define DDRPHY_BISTMSKR0_WEMSK_Msk       (0x1ul << DDRPHY_BISTMSKR0_WEMSK_Pos)             /*!< DDRPHY_T::BISTMSKR0: WEMSK Mask        */

#define DDRPHY_BISTMSKR0_CKEMSK_Pos      (20)                                              /*!< DDRPHY_T::BISTMSKR0: CKEMSK Position   */
#define DDRPHY_BISTMSKR0_CKEMSK_Msk      (0xful << DDRPHY_BISTMSKR0_CKEMSK_Pos)            /*!< DDRPHY_T::BISTMSKR0: CKEMSK Mask       */

#define DDRPHY_BISTMSKR0_CSMSK_Pos       (24)                                              /*!< DDRPHY_T::BISTMSKR0: CSMSK Position    */
#define DDRPHY_BISTMSKR0_CSMSK_Msk       (0xful << DDRPHY_BISTMSKR0_CSMSK_Pos)             /*!< DDRPHY_T::BISTMSKR0: CSMSK Mask        */

#define DDRPHY_BISTMSKR0_ODTMSK_Pos      (28)                                              /*!< DDRPHY_T::BISTMSKR0: ODTMSK Position   */
#define DDRPHY_BISTMSKR0_ODTMSK_Msk      (0xful << DDRPHY_BISTMSKR0_ODTMSK_Pos)            /*!< DDRPHY_T::BISTMSKR0: ODTMSK Mask       */

#define DDRPHY_BISTMSKR1_RASMSK_Pos      (0)                                               /*!< DDRPHY_T::BISTMSKR1: RASMSK Position   */
#define DDRPHY_BISTMSKR1_RASMSK_Msk      (0x1ul << DDRPHY_BISTMSKR1_RASMSK_Pos)            /*!< DDRPHY_T::BISTMSKR1: RASMSK Mask       */

#define DDRPHY_BISTMSKR1_CASMSK_Pos      (1)                                               /*!< DDRPHY_T::BISTMSKR1: CASMSK Position   */
#define DDRPHY_BISTMSKR1_CASMSK_Msk      (0x1ul << DDRPHY_BISTMSKR1_CASMSK_Pos)            /*!< DDRPHY_T::BISTMSKR1: CASMSK Mask       */

#define DDRPHY_BISTMSKR1_PARMSK_Pos      (27)                                              /*!< DDRPHY_T::BISTMSKR1: PARMSK Position   */
#define DDRPHY_BISTMSKR1_PARMSK_Msk      (0x1ul << DDRPHY_BISTMSKR1_PARMSK_Pos)            /*!< DDRPHY_T::BISTMSKR1: PARMSK Mask       */

#define DDRPHY_BISTMSKR1_DMMSK_Pos       (28)                                              /*!< DDRPHY_T::BISTMSKR1: DMMSK Position    */
#define DDRPHY_BISTMSKR1_DMMSK_Msk       (0xful << DDRPHY_BISTMSKR1_DMMSK_Pos)             /*!< DDRPHY_T::BISTMSKR1: DMMSK Mask        */

#define DDRPHY_BISTMSKR2_DQMSK_Pos       (0)                                               /*!< DDRPHY_T::BISTMSKR2: DQMSK Position    */
#define DDRPHY_BISTMSKR2_DQMSK_Msk       (0xfffffffful << DDRPHY_BISTMSKR2_DQMSK_Pos)      /*!< DDRPHY_T::BISTMSKR2: DQMSK Mask        */

#define DDRPHY_BISTLSR_SEED_Pos          (0)                                               /*!< DDRPHY_T::BISTLSR: SEED Position       */
#define DDRPHY_BISTLSR_SEED_Msk          (0xfffffffful << DDRPHY_BISTLSR_SEED_Pos)         /*!< DDRPHY_T::BISTLSR: SEED Mask           */

#define DDRPHY_BISTAR0_BCOL_Pos          (0)                                               /*!< DDRPHY_T::BISTAR0: BCOL Position       */
#define DDRPHY_BISTAR0_BCOL_Msk          (0xffful << DDRPHY_BISTAR0_BCOL_Pos)              /*!< DDRPHY_T::BISTAR0: BCOL Mask           */

#define DDRPHY_BISTAR0_BROW_Pos          (12)                                              /*!< DDRPHY_T::BISTAR0: BROW Position       */
#define DDRPHY_BISTAR0_BROW_Msk          (0xfffful << DDRPHY_BISTAR0_BROW_Pos)             /*!< DDRPHY_T::BISTAR0: BROW Mask           */

#define DDRPHY_BISTAR0_BBANK_Pos         (28)                                              /*!< DDRPHY_T::BISTAR0: BBANK Position      */
#define DDRPHY_BISTAR0_BBANK_Msk         (0x7ul << DDRPHY_BISTAR0_BBANK_Pos)               /*!< DDRPHY_T::BISTAR0: BBANK Mask          */

#define DDRPHY_BISTAR1_BRANK_Pos         (0)                                               /*!< DDRPHY_T::BISTAR1: BRANK Position      */
#define DDRPHY_BISTAR1_BRANK_Msk         (0x3ul << DDRPHY_BISTAR1_BRANK_Pos)               /*!< DDRPHY_T::BISTAR1: BRANK Mask          */

#define DDRPHY_BISTAR1_BMRANK_Pos        (2)                                               /*!< DDRPHY_T::BISTAR1: BMRANK Position     */
#define DDRPHY_BISTAR1_BMRANK_Msk        (0x3ul << DDRPHY_BISTAR1_BMRANK_Pos)              /*!< DDRPHY_T::BISTAR1: BMRANK Mask         */

#define DDRPHY_BISTAR1_BAINC_Pos         (4)                                               /*!< DDRPHY_T::BISTAR1: BAINC Position      */
#define DDRPHY_BISTAR1_BAINC_Msk         (0xffful << DDRPHY_BISTAR1_BAINC_Pos)             /*!< DDRPHY_T::BISTAR1: BAINC Mask          */

#define DDRPHY_BISTAR2_BMCOL_Pos         (0)                                               /*!< DDRPHY_T::BISTAR2: BMCOL Position      */
#define DDRPHY_BISTAR2_BMCOL_Msk         (0xffful << DDRPHY_BISTAR2_BMCOL_Pos)             /*!< DDRPHY_T::BISTAR2: BMCOL Mask          */

#define DDRPHY_BISTAR2_BMROW_Pos         (12)                                              /*!< DDRPHY_T::BISTAR2: BMROW Position      */
#define DDRPHY_BISTAR2_BMROW_Msk         (0xfffful << DDRPHY_BISTAR2_BMROW_Pos)            /*!< DDRPHY_T::BISTAR2: BMROW Mask          */

#define DDRPHY_BISTAR2_BMBANK_Pos        (28)                                              /*!< DDRPHY_T::BISTAR2: BMBANK Position     */
#define DDRPHY_BISTAR2_BMBANK_Msk        (0x7ul << DDRPHY_BISTAR2_BMBANK_Pos)              /*!< DDRPHY_T::BISTAR2: BMBANK Mask         */

#define DDRPHY_BISTUDPR_BUDP0_Pos        (0)                                               /*!< DDRPHY_T::BISTUDPR: BUDP0 Position     */
#define DDRPHY_BISTUDPR_BUDP0_Msk        (0xfffful << DDRPHY_BISTUDPR_BUDP0_Pos)           /*!< DDRPHY_T::BISTUDPR: BUDP0 Mask         */

#define DDRPHY_BISTUDPR_BUDP1_Pos        (16)                                              /*!< DDRPHY_T::BISTUDPR: BUDP1 Position     */
#define DDRPHY_BISTUDPR_BUDP1_Msk        (0xfffful << DDRPHY_BISTUDPR_BUDP1_Pos)           /*!< DDRPHY_T::BISTUDPR: BUDP1 Mask         */

#define DDRPHY_BISTGSR_BDONE_Pos         (0)                                               /*!< DDRPHY_T::BISTGSR: BDONE Position      */
#define DDRPHY_BISTGSR_BDONE_Msk         (0x1ul << DDRPHY_BISTGSR_BDONE_Pos)               /*!< DDRPHY_T::BISTGSR: BDONE Mask          */

#define DDRPHY_BISTGSR_BACERR_Pos        (1)                                               /*!< DDRPHY_T::BISTGSR: BACERR Position     */
#define DDRPHY_BISTGSR_BACERR_Msk        (0x1ul << DDRPHY_BISTGSR_BACERR_Pos)              /*!< DDRPHY_T::BISTGSR: BACERR Mask         */

#define DDRPHY_BISTGSR_BDXERR_Pos        (2)                                               /*!< DDRPHY_T::BISTGSR: BDXERR Position     */
#define DDRPHY_BISTGSR_BDXERR_Msk        (0x1ul << DDRPHY_BISTGSR_BDXERR_Pos)              /*!< DDRPHY_T::BISTGSR: BDXERR Mask         */

#define DDRPHY_BISTGSR_PARBER_Pos        (16)                                              /*!< DDRPHY_T::BISTGSR: PARBER Position     */
#define DDRPHY_BISTGSR_PARBER_Msk        (0x3ul << DDRPHY_BISTGSR_PARBER_Pos)              /*!< DDRPHY_T::BISTGSR: PARBER Mask         */

#define DDRPHY_BISTGSR_DMBER_Pos         (20)                                              /*!< DDRPHY_T::BISTGSR: DMBER Position      */
#define DDRPHY_BISTGSR_DMBER_Msk         (0xfful << DDRPHY_BISTGSR_DMBER_Pos)              /*!< DDRPHY_T::BISTGSR: DMBER Mask          */

#define DDRPHY_BISTGSR_RASBER_Pos        (28)                                              /*!< DDRPHY_T::BISTGSR: RASBER Position     */
#define DDRPHY_BISTGSR_RASBER_Msk        (0x3ul << DDRPHY_BISTGSR_RASBER_Pos)              /*!< DDRPHY_T::BISTGSR: RASBER Mask         */

#define DDRPHY_BISTGSR_CASBER_Pos        (30)                                              /*!< DDRPHY_T::BISTGSR: CASBER Position     */
#define DDRPHY_BISTGSR_CASBER_Msk        (0x3ul << DDRPHY_BISTGSR_CASBER_Pos)              /*!< DDRPHY_T::BISTGSR: CASBER Mask         */

#define DDRPHY_BISTWER_ACWER_Pos         (0)                                               /*!< DDRPHY_T::BISTWER: ACWER Position      */
#define DDRPHY_BISTWER_ACWER_Msk         (0xfffful << DDRPHY_BISTWER_ACWER_Pos)            /*!< DDRPHY_T::BISTWER: ACWER Mask          */

#define DDRPHY_BISTWER_DXWER_Pos         (16)                                              /*!< DDRPHY_T::BISTWER: DXWER Position      */
#define DDRPHY_BISTWER_DXWER_Msk         (0xfffful << DDRPHY_BISTWER_DXWER_Pos)            /*!< DDRPHY_T::BISTWER: DXWER Mask          */

#define DDRPHY_BISTBER0_ABER_Pos         (0)                                               /*!< DDRPHY_T::BISTBER0: ABER Position      */
#define DDRPHY_BISTBER0_ABER_Msk         (0xfffffffful << DDRPHY_BISTBER0_ABER_Pos)        /*!< DDRPHY_T::BISTBER0: ABER Mask          */

#define DDRPHY_BISTBER1_BABER_Pos        (0)                                               /*!< DDRPHY_T::BISTBER1: BABER Position     */
#define DDRPHY_BISTBER1_BABER_Msk        (0x3ful << DDRPHY_BISTBER1_BABER_Pos)             /*!< DDRPHY_T::BISTBER1: BABER Mask         */

#define DDRPHY_BISTBER1_WEBER_Pos        (6)                                               /*!< DDRPHY_T::BISTBER1: WEBER Position     */
#define DDRPHY_BISTBER1_WEBER_Msk        (0x3ul << DDRPHY_BISTBER1_WEBER_Pos)              /*!< DDRPHY_T::BISTBER1: WEBER Mask         */

#define DDRPHY_BISTBER1_CKEBER_Pos       (8)                                               /*!< DDRPHY_T::BISTBER1: CKEBER Position    */
#define DDRPHY_BISTBER1_CKEBER_Msk       (0xfful << DDRPHY_BISTBER1_CKEBER_Pos)            /*!< DDRPHY_T::BISTBER1: CKEBER Mask        */

#define DDRPHY_BISTBER1_CSBER_Pos        (16)                                              /*!< DDRPHY_T::BISTBER1: CSBER Position     */
#define DDRPHY_BISTBER1_CSBER_Msk        (0xfful << DDRPHY_BISTBER1_CSBER_Pos)             /*!< DDRPHY_T::BISTBER1: CSBER Mask         */

#define DDRPHY_BISTBER1_ODTBER_Pos       (24)                                              /*!< DDRPHY_T::BISTBER1: ODTBER Position    */
#define DDRPHY_BISTBER1_ODTBER_Msk       (0xfful << DDRPHY_BISTBER1_ODTBER_Pos)            /*!< DDRPHY_T::BISTBER1: ODTBER Mask        */

#define DDRPHY_BISTBER2_DQBER0_Pos       (0)                                               /*!< DDRPHY_T::BISTBER2: DQBER0 Position    */
#define DDRPHY_BISTBER2_DQBER0_Msk       (0xfffffffful << DDRPHY_BISTBER2_DQBER0_Pos)      /*!< DDRPHY_T::BISTBER2: DQBER0 Mask        */

#define DDRPHY_BISTBER3_DQBER1_Pos       (0)                                               /*!< DDRPHY_T::BISTBER3: DQBER1 Position    */
#define DDRPHY_BISTBER3_DQBER1_Msk       (0xfffffffful << DDRPHY_BISTBER3_DQBER1_Pos)      /*!< DDRPHY_T::BISTBER3: DQBER1 Mask        */

#define DDRPHY_BISTWCSR_ACWCNT_Pos       (0)                                               /*!< DDRPHY_T::BISTWCSR: ACWCNT Position    */
#define DDRPHY_BISTWCSR_ACWCNT_Msk       (0xfffful << DDRPHY_BISTWCSR_ACWCNT_Pos)          /*!< DDRPHY_T::BISTWCSR: ACWCNT Mask        */

#define DDRPHY_BISTWCSR_DXWCNT_Pos       (16)                                              /*!< DDRPHY_T::BISTWCSR: DXWCNT Position    */
#define DDRPHY_BISTWCSR_DXWCNT_Msk       (0xfffful << DDRPHY_BISTWCSR_DXWCNT_Pos)          /*!< DDRPHY_T::BISTWCSR: DXWCNT Mask        */

#define DDRPHY_BISTFWR0_AWEBS_Pos        (0)                                               /*!< DDRPHY_T::BISTFWR0: AWEBS Position     */
#define DDRPHY_BISTFWR0_AWEBS_Msk        (0xfffful << DDRPHY_BISTFWR0_AWEBS_Pos)           /*!< DDRPHY_T::BISTFWR0: AWEBS Mask         */

#define DDRPHY_BISTFWR0_BAWEBS_Pos       (16)                                              /*!< DDRPHY_T::BISTFWR0: BAWEBS Position    */
#define DDRPHY_BISTFWR0_BAWEBS_Msk       (0x7ul << DDRPHY_BISTFWR0_BAWEBS_Pos)             /*!< DDRPHY_T::BISTFWR0: BAWEBS Mask        */

#define DDRPHY_BISTFWR0_WEWEBS_Pos       (19)                                              /*!< DDRPHY_T::BISTFWR0: WEWEBS Position    */
#define DDRPHY_BISTFWR0_WEWEBS_Msk       (0x1ul << DDRPHY_BISTFWR0_WEWEBS_Pos)             /*!< DDRPHY_T::BISTFWR0: WEWEBS Mask        */

#define DDRPHY_BISTFWR0_CKEWEBS_Pos      (20)                                              /*!< DDRPHY_T::BISTFWR0: CKEWEBS Position   */
#define DDRPHY_BISTFWR0_CKEWEBS_Msk      (0xful << DDRPHY_BISTFWR0_CKEWEBS_Pos)            /*!< DDRPHY_T::BISTFWR0: CKEWEBS Mask       */

#define DDRPHY_BISTFWR0_CSWEBS_Pos       (24)                                              /*!< DDRPHY_T::BISTFWR0: CSWEBS Position    */
#define DDRPHY_BISTFWR0_CSWEBS_Msk       (0xful << DDRPHY_BISTFWR0_CSWEBS_Pos)             /*!< DDRPHY_T::BISTFWR0: CSWEBS Mask        */

#define DDRPHY_BISTFWR0_ODTWEBS_Pos      (28)                                              /*!< DDRPHY_T::BISTFWR0: ODTWEBS Position   */
#define DDRPHY_BISTFWR0_ODTWEBS_Msk      (0xful << DDRPHY_BISTFWR0_ODTWEBS_Pos)            /*!< DDRPHY_T::BISTFWR0: ODTWEBS Mask       */

#define DDRPHY_BISTFWR1_RASWEBS_Pos      (0)                                               /*!< DDRPHY_T::BISTFWR1: RASWEBS Position   */
#define DDRPHY_BISTFWR1_RASWEBS_Msk      (0x1ul << DDRPHY_BISTFWR1_RASWEBS_Pos)            /*!< DDRPHY_T::BISTFWR1: RASWEBS Mask       */

#define DDRPHY_BISTFWR1_CASWEBS_Pos      (1)                                               /*!< DDRPHY_T::BISTFWR1: CASWEBS Position   */
#define DDRPHY_BISTFWR1_CASWEBS_Msk      (0x1ul << DDRPHY_BISTFWR1_CASWEBS_Pos)            /*!< DDRPHY_T::BISTFWR1: CASWEBS Mask       */

#define DDRPHY_BISTFWR1_PARWEBS_Pos      (26)                                              /*!< DDRPHY_T::BISTFWR1: PARWEBS Position   */
#define DDRPHY_BISTFWR1_PARWEBS_Msk      (0x1ul << DDRPHY_BISTFWR1_PARWEBS_Pos)            /*!< DDRPHY_T::BISTFWR1: PARWEBS Mask       */

#define DDRPHY_BISTFWR1_DMWEBS_Pos       (28)                                              /*!< DDRPHY_T::BISTFWR1: DMWEBS Position    */
#define DDRPHY_BISTFWR1_DMWEBS_Msk       (0xful << DDRPHY_BISTFWR1_DMWEBS_Pos)             /*!< DDRPHY_T::BISTFWR1: DMWEBS Mask        */

#define DDRPHY_BISTFWR2_DQWEBS_Pos       (0)                                               /*!< DDRPHY_T::BISTFWR2: DQWEBS Position    */
#define DDRPHY_BISTFWR2_DQWEBS_Msk       (0xfffffffful << DDRPHY_BISTFWR2_DQWEBS_Pos)      /*!< DDRPHY_T::BISTFWR2: DQWEBS Mask        */

#define DDRPHY_AACR_AATR_Pos             (0)                                               /*!< DDRPHY_T::AACR: AATR Position          */
#define DDRPHY_AACR_AATR_Msk             (0x3ffffffful << DDRPHY_AACR_AATR_Pos)            /*!< DDRPHY_T::AACR: AATR Mask              */

#define DDRPHY_AACR_AAENC_Pos            (30)                                              /*!< DDRPHY_T::AACR: AAENC Position         */
#define DDRPHY_AACR_AAENC_Msk            (0x1ul << DDRPHY_AACR_AAENC_Pos)                  /*!< DDRPHY_T::AACR: AAENC Mask             */

#define DDRPHY_AACR_AAOENC_Pos           (31)                                              /*!< DDRPHY_T::AACR: AAOENC Position        */
#define DDRPHY_AACR_AAOENC_Msk           (0x1ul << DDRPHY_AACR_AAOENC_Pos)                 /*!< DDRPHY_T::AACR: AAOENC Mask            */

#define DDRPHY_GPR0_GPR0_Pos             (0)                                               /*!< DDRPHY_T::GPR0: GPR0 Position          */
#define DDRPHY_GPR0_GPR0_Msk             (0xfffffffful << DDRPHY_GPR0_GPR0_Pos)            /*!< DDRPHY_T::GPR0: GPR0 Mask              */

#define DDRPHY_GPR1_GPR1_Pos             (0)                                               /*!< DDRPHY_T::GPR1: GPR1 Position          */
#define DDRPHY_GPR1_GPR1_Msk             (0xfffffffful << DDRPHY_GPR1_GPR1_Pos)            /*!< DDRPHY_T::GPR1: GPR1 Mask              */

#define DDRPHY_ZQ0CR0_ZDATA_Pos          (0)                                               /*!< DDRPHY_T::ZQ0CR0: ZDATA Position       */
#define DDRPHY_ZQ0CR0_ZDATA_Msk          (0xffffffful << DDRPHY_ZQ0CR0_ZDATA_Pos)          /*!< DDRPHY_T::ZQ0CR0: ZDATA Mask           */

#define DDRPHY_ZQ0CR0_ZDEN_Pos           (28)                                              /*!< DDRPHY_T::ZQ0CR0: ZDEN Position        */
#define DDRPHY_ZQ0CR0_ZDEN_Msk           (0x1ul << DDRPHY_ZQ0CR0_ZDEN_Pos)                 /*!< DDRPHY_T::ZQ0CR0: ZDEN Mask            */

#define DDRPHY_ZQ0CR0_ZCALBYP_Pos        (29)                                              /*!< DDRPHY_T::ZQ0CR0: ZCALBYP Position     */
#define DDRPHY_ZQ0CR0_ZCALBYP_Msk        (0x1ul << DDRPHY_ZQ0CR0_ZCALBYP_Pos)              /*!< DDRPHY_T::ZQ0CR0: ZCALBYP Mask         */

#define DDRPHY_ZQ0CR0_ZCALEN_Pos         (30)                                              /*!< DDRPHY_T::ZQ0CR0: ZCALEN Position      */
#define DDRPHY_ZQ0CR0_ZCALEN_Msk         (0x1ul << DDRPHY_ZQ0CR0_ZCALEN_Pos)               /*!< DDRPHY_T::ZQ0CR0: ZCALEN Mask          */

#define DDRPHY_ZQ0CR0_ZQPD_Pos           (31)                                              /*!< DDRPHY_T::ZQ0CR0: ZQPD Position        */
#define DDRPHY_ZQ0CR0_ZQPD_Msk           (0x1ul << DDRPHY_ZQ0CR0_ZQPD_Pos)                 /*!< DDRPHY_T::ZQ0CR0: ZQPD Mask            */

#define DDRPHY_ZQ0CR1_ZPROG_Pos          (0)                                               /*!< DDRPHY_T::ZQ0CR1: ZPROG Position       */
#define DDRPHY_ZQ0CR1_ZPROG_Msk          (0xfful << DDRPHY_ZQ0CR1_ZPROG_Pos)               /*!< DDRPHY_T::ZQ0CR1: ZPROG Mask           */

#define DDRPHY_ZQ0CR1_DFICU0_Pos         (12)                                              /*!< DDRPHY_T::ZQ0CR1: DFICU0 Position      */
#define DDRPHY_ZQ0CR1_DFICU0_Msk         (0x1ul << DDRPHY_ZQ0CR1_DFICU0_Pos)               /*!< DDRPHY_T::ZQ0CR1: DFICU0 Mask          */

#define DDRPHY_ZQ0CR1_DFICU1_Pos         (13)                                              /*!< DDRPHY_T::ZQ0CR1: DFICU1 Position      */
#define DDRPHY_ZQ0CR1_DFICU1_Msk         (0x1ul << DDRPHY_ZQ0CR1_DFICU1_Pos)               /*!< DDRPHY_T::ZQ0CR1: DFICU1 Mask          */

#define DDRPHY_ZQ0CR1_DFICCU_Pos         (14)                                              /*!< DDRPHY_T::ZQ0CR1: DFICCU Position      */
#define DDRPHY_ZQ0CR1_DFICCU_Msk         (0x1ul << DDRPHY_ZQ0CR1_DFICCU_Pos)               /*!< DDRPHY_T::ZQ0CR1: DFICCU Mask          */

#define DDRPHY_ZQ0CR1_DFIPU0_Pos         (16)                                              /*!< DDRPHY_T::ZQ0CR1: DFIPU0 Position      */
#define DDRPHY_ZQ0CR1_DFIPU0_Msk         (0x1ul << DDRPHY_ZQ0CR1_DFIPU0_Pos)               /*!< DDRPHY_T::ZQ0CR1: DFIPU0 Mask          */

#define DDRPHY_ZQ0CR1_DFIPU1_Pos         (17)                                              /*!< DDRPHY_T::ZQ0CR1: DFIPU1 Position      */
#define DDRPHY_ZQ0CR1_DFIPU1_Msk         (0x1ul << DDRPHY_ZQ0CR1_DFIPU1_Pos)               /*!< DDRPHY_T::ZQ0CR1: DFIPU1 Mask          */

#define DDRPHY_ZQ0SR0_ZCTRL_Pos          (0)                                               /*!< DDRPHY_T::ZQ0SR0: ZCTRL Position       */
#define DDRPHY_ZQ0SR0_ZCTRL_Msk          (0xffffffful << DDRPHY_ZQ0SR0_ZCTRL_Pos)          /*!< DDRPHY_T::ZQ0SR0: ZCTRL Mask           */

#define DDRPHY_ZQ0SR0_ZERR_Pos           (30)                                              /*!< DDRPHY_T::ZQ0SR0: ZERR Position        */
#define DDRPHY_ZQ0SR0_ZERR_Msk           (0x1ul << DDRPHY_ZQ0SR0_ZERR_Pos)                 /*!< DDRPHY_T::ZQ0SR0: ZERR Mask            */

#define DDRPHY_ZQ0SR0_ZDONE_Pos          (31)                                              /*!< DDRPHY_T::ZQ0SR0: ZDONE Position       */
#define DDRPHY_ZQ0SR0_ZDONE_Msk          (0x1ul << DDRPHY_ZQ0SR0_ZDONE_Pos)                /*!< DDRPHY_T::ZQ0SR0: ZDONE Mask           */

#define DDRPHY_ZQ0SR1_ZPD_Pos            (0)                                               /*!< DDRPHY_T::ZQ0SR1: ZPD Position         */
#define DDRPHY_ZQ0SR1_ZPD_Msk            (0x3ul << DDRPHY_ZQ0SR1_ZPD_Pos)                  /*!< DDRPHY_T::ZQ0SR1: ZPD Mask             */

#define DDRPHY_ZQ0SR1_ZPU_Pos            (2)                                               /*!< DDRPHY_T::ZQ0SR1: ZPU Position         */
#define DDRPHY_ZQ0SR1_ZPU_Msk            (0x3ul << DDRPHY_ZQ0SR1_ZPU_Pos)                  /*!< DDRPHY_T::ZQ0SR1: ZPU Mask             */

#define DDRPHY_ZQ0SR1_OPD_Pos            (4)                                               /*!< DDRPHY_T::ZQ0SR1: OPD Position         */
#define DDRPHY_ZQ0SR1_OPD_Msk            (0x3ul << DDRPHY_ZQ0SR1_OPD_Pos)                  /*!< DDRPHY_T::ZQ0SR1: OPD Mask             */

#define DDRPHY_ZQ0SR1_OPU_Pos            (6)                                               /*!< DDRPHY_T::ZQ0SR1: OPU Position         */
#define DDRPHY_ZQ0SR1_OPU_Msk            (0x3ul << DDRPHY_ZQ0SR1_OPU_Pos)                  /*!< DDRPHY_T::ZQ0SR1: OPU Mask             */

#define DDRPHY_ZQ1CR0_ZDATA_Pos          (0)                                               /*!< DDRPHY_T::ZQ1CR0: ZDATA Position       */
#define DDRPHY_ZQ1CR0_ZDATA_Msk          (0xffffffful << DDRPHY_ZQ1CR0_ZDATA_Pos)          /*!< DDRPHY_T::ZQ1CR0: ZDATA Mask           */

#define DDRPHY_ZQ1CR0_ZDEN_Pos           (28)                                              /*!< DDRPHY_T::ZQ1CR0: ZDEN Position        */
#define DDRPHY_ZQ1CR0_ZDEN_Msk           (0x1ul << DDRPHY_ZQ1CR0_ZDEN_Pos)                 /*!< DDRPHY_T::ZQ1CR0: ZDEN Mask            */

#define DDRPHY_ZQ1CR0_ZCALBYP_Pos        (29)                                              /*!< DDRPHY_T::ZQ1CR0: ZCALBYP Position     */
#define DDRPHY_ZQ1CR0_ZCALBYP_Msk        (0x1ul << DDRPHY_ZQ1CR0_ZCALBYP_Pos)              /*!< DDRPHY_T::ZQ1CR0: ZCALBYP Mask         */

#define DDRPHY_ZQ1CR0_ZCALEN_Pos         (30)                                              /*!< DDRPHY_T::ZQ1CR0: ZCALEN Position      */
#define DDRPHY_ZQ1CR0_ZCALEN_Msk         (0x1ul << DDRPHY_ZQ1CR0_ZCALEN_Pos)               /*!< DDRPHY_T::ZQ1CR0: ZCALEN Mask          */

#define DDRPHY_ZQ1CR0_ZQPD_Pos           (31)                                              /*!< DDRPHY_T::ZQ1CR0: ZQPD Position        */
#define DDRPHY_ZQ1CR0_ZQPD_Msk           (0x1ul << DDRPHY_ZQ1CR0_ZQPD_Pos)                 /*!< DDRPHY_T::ZQ1CR0: ZQPD Mask            */

#define DDRPHY_ZQ1CR1_ZPROG_Pos          (0)                                               /*!< DDRPHY_T::ZQ1CR1: ZPROG Position       */
#define DDRPHY_ZQ1CR1_ZPROG_Msk          (0xfful << DDRPHY_ZQ1CR1_ZPROG_Pos)               /*!< DDRPHY_T::ZQ1CR1: ZPROG Mask           */

#define DDRPHY_ZQ1CR1_DFICU0_Pos         (12)                                              /*!< DDRPHY_T::ZQ1CR1: DFICU0 Position      */
#define DDRPHY_ZQ1CR1_DFICU0_Msk         (0x1ul << DDRPHY_ZQ1CR1_DFICU0_Pos)               /*!< DDRPHY_T::ZQ1CR1: DFICU0 Mask          */

#define DDRPHY_ZQ1CR1_DFICU1_Pos         (13)                                              /*!< DDRPHY_T::ZQ1CR1: DFICU1 Position      */
#define DDRPHY_ZQ1CR1_DFICU1_Msk         (0x1ul << DDRPHY_ZQ1CR1_DFICU1_Pos)               /*!< DDRPHY_T::ZQ1CR1: DFICU1 Mask          */

#define DDRPHY_ZQ1CR1_DFICCU_Pos         (14)                                              /*!< DDRPHY_T::ZQ1CR1: DFICCU Position      */
#define DDRPHY_ZQ1CR1_DFICCU_Msk         (0x1ul << DDRPHY_ZQ1CR1_DFICCU_Pos)               /*!< DDRPHY_T::ZQ1CR1: DFICCU Mask          */

#define DDRPHY_ZQ1CR1_DFIPU0_Pos         (16)                                              /*!< DDRPHY_T::ZQ1CR1: DFIPU0 Position      */
#define DDRPHY_ZQ1CR1_DFIPU0_Msk         (0x1ul << DDRPHY_ZQ1CR1_DFIPU0_Pos)               /*!< DDRPHY_T::ZQ1CR1: DFIPU0 Mask          */

#define DDRPHY_ZQ1CR1_DFIPU1_Pos         (17)                                              /*!< DDRPHY_T::ZQ1CR1: DFIPU1 Position      */
#define DDRPHY_ZQ1CR1_DFIPU1_Msk         (0x1ul << DDRPHY_ZQ1CR1_DFIPU1_Pos)               /*!< DDRPHY_T::ZQ1CR1: DFIPU1 Mask          */

#define DDRPHY_ZQ1SR0_ZCTRL_Pos          (0)                                               /*!< DDRPHY_T::ZQ1SR0: ZCTRL Position       */
#define DDRPHY_ZQ1SR0_ZCTRL_Msk          (0xffffffful << DDRPHY_ZQ1SR0_ZCTRL_Pos)          /*!< DDRPHY_T::ZQ1SR0: ZCTRL Mask           */

#define DDRPHY_ZQ1SR0_ZERR_Pos           (30)                                              /*!< DDRPHY_T::ZQ1SR0: ZERR Position        */
#define DDRPHY_ZQ1SR0_ZERR_Msk           (0x1ul << DDRPHY_ZQ1SR0_ZERR_Pos)                 /*!< DDRPHY_T::ZQ1SR0: ZERR Mask            */

#define DDRPHY_ZQ1SR0_ZDONE_Pos          (31)                                              /*!< DDRPHY_T::ZQ1SR0: ZDONE Position       */
#define DDRPHY_ZQ1SR0_ZDONE_Msk          (0x1ul << DDRPHY_ZQ1SR0_ZDONE_Pos)                /*!< DDRPHY_T::ZQ1SR0: ZDONE Mask           */

#define DDRPHY_ZQ1SR1_ZPD_Pos            (0)                                               /*!< DDRPHY_T::ZQ1SR1: ZPD Position         */
#define DDRPHY_ZQ1SR1_ZPD_Msk            (0x3ul << DDRPHY_ZQ1SR1_ZPD_Pos)                  /*!< DDRPHY_T::ZQ1SR1: ZPD Mask             */

#define DDRPHY_ZQ1SR1_ZPU_Pos            (2)                                               /*!< DDRPHY_T::ZQ1SR1: ZPU Position         */
#define DDRPHY_ZQ1SR1_ZPU_Msk            (0x3ul << DDRPHY_ZQ1SR1_ZPU_Pos)                  /*!< DDRPHY_T::ZQ1SR1: ZPU Mask             */

#define DDRPHY_ZQ1SR1_OPD_Pos            (4)                                               /*!< DDRPHY_T::ZQ1SR1: OPD Position         */
#define DDRPHY_ZQ1SR1_OPD_Msk            (0x3ul << DDRPHY_ZQ1SR1_OPD_Pos)                  /*!< DDRPHY_T::ZQ1SR1: OPD Mask             */

#define DDRPHY_ZQ1SR1_OPU_Pos            (6)                                               /*!< DDRPHY_T::ZQ1SR1: OPU Position         */
#define DDRPHY_ZQ1SR1_OPU_Msk            (0x3ul << DDRPHY_ZQ1SR1_OPU_Pos)                  /*!< DDRPHY_T::ZQ1SR1: OPU Mask             */

#define DDRPHY_ZQ2CR0_ZDATA_Pos          (0)                                               /*!< DDRPHY_T::ZQ2CR0: ZDATA Position       */
#define DDRPHY_ZQ2CR0_ZDATA_Msk          (0xffffffful << DDRPHY_ZQ2CR0_ZDATA_Pos)          /*!< DDRPHY_T::ZQ2CR0: ZDATA Mask           */

#define DDRPHY_ZQ2CR0_ZDEN_Pos           (28)                                              /*!< DDRPHY_T::ZQ2CR0: ZDEN Position        */
#define DDRPHY_ZQ2CR0_ZDEN_Msk           (0x1ul << DDRPHY_ZQ2CR0_ZDEN_Pos)                 /*!< DDRPHY_T::ZQ2CR0: ZDEN Mask            */

#define DDRPHY_ZQ2CR0_ZCALBYP_Pos        (29)                                              /*!< DDRPHY_T::ZQ2CR0: ZCALBYP Position     */
#define DDRPHY_ZQ2CR0_ZCALBYP_Msk        (0x1ul << DDRPHY_ZQ2CR0_ZCALBYP_Pos)              /*!< DDRPHY_T::ZQ2CR0: ZCALBYP Mask         */

#define DDRPHY_ZQ2CR0_ZCALEN_Pos         (30)                                              /*!< DDRPHY_T::ZQ2CR0: ZCALEN Position      */
#define DDRPHY_ZQ2CR0_ZCALEN_Msk         (0x1ul << DDRPHY_ZQ2CR0_ZCALEN_Pos)               /*!< DDRPHY_T::ZQ2CR0: ZCALEN Mask          */

#define DDRPHY_ZQ2CR0_ZQPD_Pos           (31)                                              /*!< DDRPHY_T::ZQ2CR0: ZQPD Position        */
#define DDRPHY_ZQ2CR0_ZQPD_Msk           (0x1ul << DDRPHY_ZQ2CR0_ZQPD_Pos)                 /*!< DDRPHY_T::ZQ2CR0: ZQPD Mask            */

#define DDRPHY_ZQ2CR1_ZPROG_Pos          (0)                                               /*!< DDRPHY_T::ZQ2CR1: ZPROG Position       */
#define DDRPHY_ZQ2CR1_ZPROG_Msk          (0xfful << DDRPHY_ZQ2CR1_ZPROG_Pos)               /*!< DDRPHY_T::ZQ2CR1: ZPROG Mask           */

#define DDRPHY_ZQ2CR1_DFICU0_Pos         (12)                                              /*!< DDRPHY_T::ZQ2CR1: DFICU0 Position      */
#define DDRPHY_ZQ2CR1_DFICU0_Msk         (0x1ul << DDRPHY_ZQ2CR1_DFICU0_Pos)               /*!< DDRPHY_T::ZQ2CR1: DFICU0 Mask          */

#define DDRPHY_ZQ2CR1_DFICU1_Pos         (13)                                              /*!< DDRPHY_T::ZQ2CR1: DFICU1 Position      */
#define DDRPHY_ZQ2CR1_DFICU1_Msk         (0x1ul << DDRPHY_ZQ2CR1_DFICU1_Pos)               /*!< DDRPHY_T::ZQ2CR1: DFICU1 Mask          */

#define DDRPHY_ZQ2CR1_DFICCU_Pos         (14)                                              /*!< DDRPHY_T::ZQ2CR1: DFICCU Position      */
#define DDRPHY_ZQ2CR1_DFICCU_Msk         (0x1ul << DDRPHY_ZQ2CR1_DFICCU_Pos)               /*!< DDRPHY_T::ZQ2CR1: DFICCU Mask          */

#define DDRPHY_ZQ2CR1_DFIPU0_Pos         (16)                                              /*!< DDRPHY_T::ZQ2CR1: DFIPU0 Position      */
#define DDRPHY_ZQ2CR1_DFIPU0_Msk         (0x1ul << DDRPHY_ZQ2CR1_DFIPU0_Pos)               /*!< DDRPHY_T::ZQ2CR1: DFIPU0 Mask          */

#define DDRPHY_ZQ2CR1_DFIPU1_Pos         (17)                                              /*!< DDRPHY_T::ZQ2CR1: DFIPU1 Position      */
#define DDRPHY_ZQ2CR1_DFIPU1_Msk         (0x1ul << DDRPHY_ZQ2CR1_DFIPU1_Pos)               /*!< DDRPHY_T::ZQ2CR1: DFIPU1 Mask          */

#define DDRPHY_ZQ2SR0_ZCTRL_Pos          (0)                                               /*!< DDRPHY_T::ZQ2SR0: ZCTRL Position       */
#define DDRPHY_ZQ2SR0_ZCTRL_Msk          (0xffffffful << DDRPHY_ZQ2SR0_ZCTRL_Pos)          /*!< DDRPHY_T::ZQ2SR0: ZCTRL Mask           */

#define DDRPHY_ZQ2SR0_ZERR_Pos           (30)                                              /*!< DDRPHY_T::ZQ2SR0: ZERR Position        */
#define DDRPHY_ZQ2SR0_ZERR_Msk           (0x1ul << DDRPHY_ZQ2SR0_ZERR_Pos)                 /*!< DDRPHY_T::ZQ2SR0: ZERR Mask            */

#define DDRPHY_ZQ2SR0_ZDONE_Pos          (31)                                              /*!< DDRPHY_T::ZQ2SR0: ZDONE Position       */
#define DDRPHY_ZQ2SR0_ZDONE_Msk          (0x1ul << DDRPHY_ZQ2SR0_ZDONE_Pos)                /*!< DDRPHY_T::ZQ2SR0: ZDONE Mask           */

#define DDRPHY_ZQ2SR1_ZPD_Pos            (0)                                               /*!< DDRPHY_T::ZQ2SR1: ZPD Position         */
#define DDRPHY_ZQ2SR1_ZPD_Msk            (0x3ul << DDRPHY_ZQ2SR1_ZPD_Pos)                  /*!< DDRPHY_T::ZQ2SR1: ZPD Mask             */

#define DDRPHY_ZQ2SR1_ZPU_Pos            (2)                                               /*!< DDRPHY_T::ZQ2SR1: ZPU Position         */
#define DDRPHY_ZQ2SR1_ZPU_Msk            (0x3ul << DDRPHY_ZQ2SR1_ZPU_Pos)                  /*!< DDRPHY_T::ZQ2SR1: ZPU Mask             */

#define DDRPHY_ZQ2SR1_OPD_Pos            (4)                                               /*!< DDRPHY_T::ZQ2SR1: OPD Position         */
#define DDRPHY_ZQ2SR1_OPD_Msk            (0x3ul << DDRPHY_ZQ2SR1_OPD_Pos)                  /*!< DDRPHY_T::ZQ2SR1: OPD Mask             */

#define DDRPHY_ZQ2SR1_OPU_Pos            (6)                                               /*!< DDRPHY_T::ZQ2SR1: OPU Position         */
#define DDRPHY_ZQ2SR1_OPU_Msk            (0x3ul << DDRPHY_ZQ2SR1_OPU_Pos)                  /*!< DDRPHY_T::ZQ2SR1: OPU Mask             */

#define DDRPHY_ZQ3CR0_ZDATA_Pos          (0)                                               /*!< DDRPHY_T::ZQ3CR0: ZDATA Position       */
#define DDRPHY_ZQ3CR0_ZDATA_Msk          (0xffffffful << DDRPHY_ZQ3CR0_ZDATA_Pos)          /*!< DDRPHY_T::ZQ3CR0: ZDATA Mask           */

#define DDRPHY_ZQ3CR0_ZDEN_Pos           (28)                                              /*!< DDRPHY_T::ZQ3CR0: ZDEN Position        */
#define DDRPHY_ZQ3CR0_ZDEN_Msk           (0x1ul << DDRPHY_ZQ3CR0_ZDEN_Pos)                 /*!< DDRPHY_T::ZQ3CR0: ZDEN Mask            */

#define DDRPHY_ZQ3CR0_ZCALBYP_Pos        (29)                                              /*!< DDRPHY_T::ZQ3CR0: ZCALBYP Position     */
#define DDRPHY_ZQ3CR0_ZCALBYP_Msk        (0x1ul << DDRPHY_ZQ3CR0_ZCALBYP_Pos)              /*!< DDRPHY_T::ZQ3CR0: ZCALBYP Mask         */

#define DDRPHY_ZQ3CR0_ZCALEN_Pos         (30)                                              /*!< DDRPHY_T::ZQ3CR0: ZCALEN Position      */
#define DDRPHY_ZQ3CR0_ZCALEN_Msk         (0x1ul << DDRPHY_ZQ3CR0_ZCALEN_Pos)               /*!< DDRPHY_T::ZQ3CR0: ZCALEN Mask          */

#define DDRPHY_ZQ3CR0_ZQPD_Pos           (31)                                              /*!< DDRPHY_T::ZQ3CR0: ZQPD Position        */
#define DDRPHY_ZQ3CR0_ZQPD_Msk           (0x1ul << DDRPHY_ZQ3CR0_ZQPD_Pos)                 /*!< DDRPHY_T::ZQ3CR0: ZQPD Mask            */

#define DDRPHY_ZQ3CR1_ZPROG_Pos          (0)                                               /*!< DDRPHY_T::ZQ3CR1: ZPROG Position       */
#define DDRPHY_ZQ3CR1_ZPROG_Msk          (0xfful << DDRPHY_ZQ3CR1_ZPROG_Pos)               /*!< DDRPHY_T::ZQ3CR1: ZPROG Mask           */

#define DDRPHY_ZQ3CR1_DFICU0_Pos         (12)                                              /*!< DDRPHY_T::ZQ3CR1: DFICU0 Position      */
#define DDRPHY_ZQ3CR1_DFICU0_Msk         (0x1ul << DDRPHY_ZQ3CR1_DFICU0_Pos)               /*!< DDRPHY_T::ZQ3CR1: DFICU0 Mask          */

#define DDRPHY_ZQ3CR1_DFICU1_Pos         (13)                                              /*!< DDRPHY_T::ZQ3CR1: DFICU1 Position      */
#define DDRPHY_ZQ3CR1_DFICU1_Msk         (0x1ul << DDRPHY_ZQ3CR1_DFICU1_Pos)               /*!< DDRPHY_T::ZQ3CR1: DFICU1 Mask          */

#define DDRPHY_ZQ3CR1_DFICCU_Pos         (14)                                              /*!< DDRPHY_T::ZQ3CR1: DFICCU Position      */
#define DDRPHY_ZQ3CR1_DFICCU_Msk         (0x1ul << DDRPHY_ZQ3CR1_DFICCU_Pos)               /*!< DDRPHY_T::ZQ3CR1: DFICCU Mask          */

#define DDRPHY_ZQ3CR1_DFIPU0_Pos         (16)                                              /*!< DDRPHY_T::ZQ3CR1: DFIPU0 Position      */
#define DDRPHY_ZQ3CR1_DFIPU0_Msk         (0x1ul << DDRPHY_ZQ3CR1_DFIPU0_Pos)               /*!< DDRPHY_T::ZQ3CR1: DFIPU0 Mask          */

#define DDRPHY_ZQ3CR1_DFIPU1_Pos         (17)                                              /*!< DDRPHY_T::ZQ3CR1: DFIPU1 Position      */
#define DDRPHY_ZQ3CR1_DFIPU1_Msk         (0x1ul << DDRPHY_ZQ3CR1_DFIPU1_Pos)               /*!< DDRPHY_T::ZQ3CR1: DFIPU1 Mask          */

#define DDRPHY_ZQ3SR0_ZCTRL_Pos          (0)                                               /*!< DDRPHY_T::ZQ3SR0: ZCTRL Position       */
#define DDRPHY_ZQ3SR0_ZCTRL_Msk          (0xffffffful << DDRPHY_ZQ3SR0_ZCTRL_Pos)          /*!< DDRPHY_T::ZQ3SR0: ZCTRL Mask           */

#define DDRPHY_ZQ3SR0_ZERR_Pos           (30)                                              /*!< DDRPHY_T::ZQ3SR0: ZERR Position        */
#define DDRPHY_ZQ3SR0_ZERR_Msk           (0x1ul << DDRPHY_ZQ3SR0_ZERR_Pos)                 /*!< DDRPHY_T::ZQ3SR0: ZERR Mask            */

#define DDRPHY_ZQ3SR0_ZDONE_Pos          (31)                                              /*!< DDRPHY_T::ZQ3SR0: ZDONE Position       */
#define DDRPHY_ZQ3SR0_ZDONE_Msk          (0x1ul << DDRPHY_ZQ3SR0_ZDONE_Pos)                /*!< DDRPHY_T::ZQ3SR0: ZDONE Mask           */

#define DDRPHY_ZQ3SR1_ZPD_Pos            (0)                                               /*!< DDRPHY_T::ZQ3SR1: ZPD Position         */
#define DDRPHY_ZQ3SR1_ZPD_Msk            (0x3ul << DDRPHY_ZQ3SR1_ZPD_Pos)                  /*!< DDRPHY_T::ZQ3SR1: ZPD Mask             */

#define DDRPHY_ZQ3SR1_ZPU_Pos            (2)                                               /*!< DDRPHY_T::ZQ3SR1: ZPU Position         */
#define DDRPHY_ZQ3SR1_ZPU_Msk            (0x3ul << DDRPHY_ZQ3SR1_ZPU_Pos)                  /*!< DDRPHY_T::ZQ3SR1: ZPU Mask             */

#define DDRPHY_ZQ3SR1_OPD_Pos            (4)                                               /*!< DDRPHY_T::ZQ3SR1: OPD Position         */
#define DDRPHY_ZQ3SR1_OPD_Msk            (0x3ul << DDRPHY_ZQ3SR1_OPD_Pos)                  /*!< DDRPHY_T::ZQ3SR1: OPD Mask             */

#define DDRPHY_ZQ3SR1_OPU_Pos            (6)                                               /*!< DDRPHY_T::ZQ3SR1: OPU Position         */
#define DDRPHY_ZQ3SR1_OPU_Msk            (0x3ul << DDRPHY_ZQ3SR1_OPU_Pos)                  /*!< DDRPHY_T::ZQ3SR1: OPU Mask             */

#define DDRPHY_DX0GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX0GCR: DXEN Position        */
#define DDRPHY_DX0GCR_DXEN_Msk           (0x1ul << DDRPHY_DX0GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX0GCR: DXEN Mask            */

#define DDRPHY_DX0GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX0GCR: DQSODT Position      */
#define DDRPHY_DX0GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX0GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX0GCR: DQSODT Mask          */

#define DDRPHY_DX0GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX0GCR: DQODT Position       */
#define DDRPHY_DX0GCR_DQODT_Msk          (0x1ul << DDRPHY_DX0GCR_DQODT_Pos)                /*!< DDRPHY_T::DX0GCR: DQODT Mask           */

#define DDRPHY_DX0GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX0GCR: DXIOM Position       */
#define DDRPHY_DX0GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX0GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX0GCR: DXIOM Mask           */

#define DDRPHY_DX0GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX0GCR: DXPDD Position       */
#define DDRPHY_DX0GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX0GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX0GCR: DXPDD Mask           */

#define DDRPHY_DX0GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX0GCR: DXPDR Position       */
#define DDRPHY_DX0GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX0GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX0GCR: DXPDR Mask           */

#define DDRPHY_DX0GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX0GCR: DQSRPD Position      */
#define DDRPHY_DX0GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX0GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX0GCR: DQSRPD Mask          */

#define DDRPHY_DX0GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX0GCR: DSEN Position        */
#define DDRPHY_DX0GCR_DSEN_Msk           (0x3ul << DDRPHY_DX0GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX0GCR: DSEN Mask            */

#define DDRPHY_DX0GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX0GCR: DQSRTT Position      */
#define DDRPHY_DX0GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX0GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX0GCR: DQSRTT Mask          */

#define DDRPHY_DX0GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX0GCR: DQRTT Position       */
#define DDRPHY_DX0GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX0GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX0GCR: DQRTT Mask           */

#define DDRPHY_DX0GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX0GCR: RTTOH Position       */
#define DDRPHY_DX0GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX0GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX0GCR: RTTOH Mask           */

#define DDRPHY_DX0GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX0GCR: RTTOAL Position      */
#define DDRPHY_DX0GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX0GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX0GCR: RTTOAL Mask          */

#define DDRPHY_DX0GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX0GCR: DXOEO Position       */
#define DDRPHY_DX0GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX0GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX0GCR: DXOEO Mask           */

#define DDRPHY_DX0GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX0GCR: PLLRST Position      */
#define DDRPHY_DX0GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX0GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX0GCR: PLLRST Mask          */

#define DDRPHY_DX0GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX0GCR: PLLPD Position       */
#define DDRPHY_DX0GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX0GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX0GCR: PLLPD Mask           */

#define DDRPHY_DX0GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX0GCR: GSHIFT Position      */
#define DDRPHY_DX0GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX0GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX0GCR: GSHIFT Mask          */

#define DDRPHY_DX0GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX0GCR: PLLBYP Position      */
#define DDRPHY_DX0GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX0GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX0GCR: PLLBYP Mask          */

#define DDRPHY_DX0GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX0GCR: WLRKEN Position      */
#define DDRPHY_DX0GCR_WLRKEN_Msk         (0xful << DDRPHY_DX0GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX0GCR: WLRKEN Mask          */

#define DDRPHY_DX0GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX0GCR: MDLEN Position       */
#define DDRPHY_DX0GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX0GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX0GCR: MDLEN Mask           */

#define DDRPHY_DX0GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX0GCR: CALBYP Position      */
#define DDRPHY_DX0GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX0GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX0GCR: CALBYP Mask          */

#define DDRPHY_DX0GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX0GSR0: WDQCAL Position     */
#define DDRPHY_DX0GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX0GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX0GSR0: WDQCAL Mask         */

#define DDRPHY_DX0GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX0GSR0: RDQSCAL Position    */
#define DDRPHY_DX0GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX0GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX0GSR0: RDQSCAL Mask        */

#define DDRPHY_DX0GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX0GSR0: RDQSNCAL Position   */
#define DDRPHY_DX0GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX0GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX0GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX0GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX0GSR0: GDQSCAL Position    */
#define DDRPHY_DX0GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX0GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX0GSR0: GDQSCAL Mask        */

#define DDRPHY_DX0GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX0GSR0: WLCAL Position      */
#define DDRPHY_DX0GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX0GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX0GSR0: WLCAL Mask          */

#define DDRPHY_DX0GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX0GSR0: WLDONE Position     */
#define DDRPHY_DX0GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX0GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX0GSR0: WLDONE Mask         */

#define DDRPHY_DX0GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX0GSR0: WLERR Position      */
#define DDRPHY_DX0GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX0GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX0GSR0: WLERR Mask          */

#define DDRPHY_DX0GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX0GSR0: WLPRD Position      */
#define DDRPHY_DX0GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX0GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX0GSR0: WLPRD Mask          */

#define DDRPHY_DX0GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX0GSR0: DPLOCK Position     */
#define DDRPHY_DX0GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX0GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX0GSR0: DPLOCK Mask         */

#define DDRPHY_DX0GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX0GSR0: GDQSPRD Position    */
#define DDRPHY_DX0GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX0GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX0GSR0: GDQSPRD Mask        */

#define DDRPHY_DX0GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX0GSR0: QSGERR Position     */
#define DDRPHY_DX0GSR0_QSGERR_Msk        (0xful << DDRPHY_DX0GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX0GSR0: QSGERR Mask         */

#define DDRPHY_DX0GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX0GSR0: WLDQ Position       */
#define DDRPHY_DX0GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX0GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX0GSR0: WLDQ Mask           */

#define DDRPHY_DX0GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX0GSR1: DLTDONE Position    */
#define DDRPHY_DX0GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX0GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX0GSR1: DLTDONE Mask        */

#define DDRPHY_DX0GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX0GSR1: DLTCODE Position    */
#define DDRPHY_DX0GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX0GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX0GSR1: DLTCODE Mask        */

#define DDRPHY_DX0BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX0BDLR0: DQ0WBD Position    */
#define DDRPHY_DX0BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX0BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX0BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX0BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX0BDLR0: DQ1WBD Position    */
#define DDRPHY_DX0BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX0BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX0BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX0BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX0BDLR0: DQ2WBD Position    */
#define DDRPHY_DX0BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX0BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX0BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX0BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX0BDLR0: DQ3WBD Position    */
#define DDRPHY_DX0BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX0BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX0BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX0BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX0BDLR0: DQ4WBD Position    */
#define DDRPHY_DX0BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX0BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX0BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX0BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX0BDLR1: DQ5WBD Position    */
#define DDRPHY_DX0BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX0BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX0BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX0BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX0BDLR1: DQ6WBD Position    */
#define DDRPHY_DX0BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX0BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX0BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX0BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX0BDLR1: DQ7WBD Position    */
#define DDRPHY_DX0BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX0BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX0BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX0BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX0BDLR1: DMWBD Position     */
#define DDRPHY_DX0BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX0BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX0BDLR1: DMWBD Mask         */

#define DDRPHY_DX0BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX0BDLR1: DSWBD Position     */
#define DDRPHY_DX0BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX0BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX0BDLR1: DSWBD Mask         */

#define DDRPHY_DX0BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX0BDLR2: DSOEBD Position    */
#define DDRPHY_DX0BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX0BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX0BDLR2: DSOEBD Mask        */

#define DDRPHY_DX0BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX0BDLR2: DQOEBD Position    */
#define DDRPHY_DX0BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX0BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX0BDLR2: DQOEBD Mask        */

#define DDRPHY_DX0BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX0BDLR2: DSRBD Position     */
#define DDRPHY_DX0BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX0BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX0BDLR2: DSRBD Mask         */

#define DDRPHY_DX0BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX0BDLR2: DSNRBD Position    */
#define DDRPHY_DX0BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX0BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX0BDLR2: DSNRBD Mask        */

#define DDRPHY_DX0BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX0BDLR3: DQ0RBD Position    */
#define DDRPHY_DX0BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX0BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX0BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX0BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX0BDLR3: DQ1RBD Position    */
#define DDRPHY_DX0BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX0BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX0BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX0BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX0BDLR3: DQ2RBD Position    */
#define DDRPHY_DX0BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX0BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX0BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX0BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX0BDLR3: DQ3RBD Position    */
#define DDRPHY_DX0BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX0BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX0BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX0BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX0BDLR3: DQ4RBD Position    */
#define DDRPHY_DX0BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX0BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX0BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX0BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX0BDLR4: DQ5RBD Position    */
#define DDRPHY_DX0BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX0BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX0BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX0BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX0BDLR4: DQ6RBD Position    */
#define DDRPHY_DX0BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX0BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX0BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX0BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX0BDLR4: DQ7RBD Position    */
#define DDRPHY_DX0BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX0BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX0BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX0BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX0BDLR4: DMRBD Position     */
#define DDRPHY_DX0BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX0BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX0BDLR4: DMRBD Mask         */

#define DDRPHY_DX0LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX0LCDLR0: R0WLD Position    */
#define DDRPHY_DX0LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX0LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX0LCDLR0: R0WLD Mask        */

#define DDRPHY_DX0LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX0LCDLR0: R1WLD Position    */
#define DDRPHY_DX0LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX0LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX0LCDLR0: R1WLD Mask        */

#define DDRPHY_DX0LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX0LCDLR0: R2WLD Position    */
#define DDRPHY_DX0LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX0LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX0LCDLR0: R2WLD Mask        */

#define DDRPHY_DX0LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX0LCDLR0: R3WLD Position    */
#define DDRPHY_DX0LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX0LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX0LCDLR0: R3WLD Mask        */

#define DDRPHY_DX0LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX0LCDLR1: WDQD Position     */
#define DDRPHY_DX0LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX0LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX0LCDLR1: WDQD Mask         */

#define DDRPHY_DX0LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX0LCDLR1: RDQSD Position    */
#define DDRPHY_DX0LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX0LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX0LCDLR1: RDQSD Mask        */

#define DDRPHY_DX0LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX0LCDLR1: RDQSND Position   */
#define DDRPHY_DX0LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX0LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX0LCDLR1: RDQSND Mask       */

#define DDRPHY_DX0LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX0LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX0LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX0LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX0LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX0LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX0LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX0LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX0LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX0LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX0LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX0LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX0LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX0LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX0LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX0LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX0LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX0LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX0LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX0LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX0MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX0MDLR: IPRD Position       */
#define DDRPHY_DX0MDLR_IPRD_Msk          (0xfful << DDRPHY_DX0MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX0MDLR: IPRD Mask           */

#define DDRPHY_DX0MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX0MDLR: TPRD Position       */
#define DDRPHY_DX0MDLR_TPRD_Msk          (0xfful << DDRPHY_DX0MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX0MDLR: TPRD Mask           */

#define DDRPHY_DX0MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX0MDLR: MDLD Position       */
#define DDRPHY_DX0MDLR_MDLD_Msk          (0xfful << DDRPHY_DX0MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX0MDLR: MDLD Mask           */

#define DDRPHY_DX0GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX0GTR: R0DGSL Position      */
#define DDRPHY_DX0GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX0GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX0GTR: R0DGSL Mask          */

#define DDRPHY_DX0GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX0GTR: R1DGSL Position      */
#define DDRPHY_DX0GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX0GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX0GTR: R1DGSL Mask          */

#define DDRPHY_DX0GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX0GTR: R2DGSL Position      */
#define DDRPHY_DX0GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX0GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX0GTR: R2DGSL Mask          */

#define DDRPHY_DX0GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX0GTR: R3DGSL Position      */
#define DDRPHY_DX0GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX0GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX0GTR: R3DGSL Mask          */

#define DDRPHY_DX0GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX0GTR: R0WLSL Position      */
#define DDRPHY_DX0GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX0GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX0GTR: R0WLSL Mask          */

#define DDRPHY_DX0GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX0GTR: R1WLSL Position      */
#define DDRPHY_DX0GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX0GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX0GTR: R1WLSL Mask          */

#define DDRPHY_DX0GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX0GTR: R2WLSL Position      */
#define DDRPHY_DX0GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX0GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX0GTR: R2WLSL Mask          */

#define DDRPHY_DX0GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX0GTR: R3WLSL Position      */
#define DDRPHY_DX0GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX0GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX0GTR: R3WLSL Mask          */

#define DDRPHY_DX0GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX0GSR2: RDERR Position      */
#define DDRPHY_DX0GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX0GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX0GSR2: RDERR Mask          */

#define DDRPHY_DX0GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX0GSR2: RDWN Position       */
#define DDRPHY_DX0GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX0GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX0GSR2: RDWN Mask           */

#define DDRPHY_DX0GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX0GSR2: WDERR Position      */
#define DDRPHY_DX0GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX0GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX0GSR2: WDERR Mask          */

#define DDRPHY_DX0GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX0GSR2: WDWN Position       */
#define DDRPHY_DX0GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX0GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX0GSR2: WDWN Mask           */

#define DDRPHY_DX0GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX0GSR2: REERR Position      */
#define DDRPHY_DX0GSR2_REERR_Msk         (0x1ul << DDRPHY_DX0GSR2_REERR_Pos)               /*!< DDRPHY_T::DX0GSR2: REERR Mask          */

#define DDRPHY_DX0GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX0GSR2: REWN Position       */
#define DDRPHY_DX0GSR2_REWN_Msk          (0x1ul << DDRPHY_DX0GSR2_REWN_Pos)                /*!< DDRPHY_T::DX0GSR2: REWN Mask           */

#define DDRPHY_DX0GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX0GSR2: WEERR Position      */
#define DDRPHY_DX0GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX0GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX0GSR2: WEERR Mask          */

#define DDRPHY_DX0GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX0GSR2: WEWN Position       */
#define DDRPHY_DX0GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX0GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX0GSR2: WEWN Mask           */

#define DDRPHY_DX0GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX0GSR2: ESTAT Position      */
#define DDRPHY_DX0GSR2_ESTAT_Msk         (0xful << DDRPHY_DX0GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX0GSR2: ESTAT Mask          */

#define DDRPHY_DX1GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX1GCR: DXEN Position        */
#define DDRPHY_DX1GCR_DXEN_Msk           (0x1ul << DDRPHY_DX1GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX1GCR: DXEN Mask            */

#define DDRPHY_DX1GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX1GCR: DQSODT Position      */
#define DDRPHY_DX1GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX1GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX1GCR: DQSODT Mask          */

#define DDRPHY_DX1GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX1GCR: DQODT Position       */
#define DDRPHY_DX1GCR_DQODT_Msk          (0x1ul << DDRPHY_DX1GCR_DQODT_Pos)                /*!< DDRPHY_T::DX1GCR: DQODT Mask           */

#define DDRPHY_DX1GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX1GCR: DXIOM Position       */
#define DDRPHY_DX1GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX1GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX1GCR: DXIOM Mask           */

#define DDRPHY_DX1GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX1GCR: DXPDD Position       */
#define DDRPHY_DX1GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX1GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX1GCR: DXPDD Mask           */

#define DDRPHY_DX1GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX1GCR: DXPDR Position       */
#define DDRPHY_DX1GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX1GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX1GCR: DXPDR Mask           */

#define DDRPHY_DX1GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX1GCR: DQSRPD Position      */
#define DDRPHY_DX1GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX1GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX1GCR: DQSRPD Mask          */

#define DDRPHY_DX1GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX1GCR: DSEN Position        */
#define DDRPHY_DX1GCR_DSEN_Msk           (0x3ul << DDRPHY_DX1GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX1GCR: DSEN Mask            */

#define DDRPHY_DX1GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX1GCR: DQSRTT Position      */
#define DDRPHY_DX1GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX1GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX1GCR: DQSRTT Mask          */

#define DDRPHY_DX1GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX1GCR: DQRTT Position       */
#define DDRPHY_DX1GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX1GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX1GCR: DQRTT Mask           */

#define DDRPHY_DX1GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX1GCR: RTTOH Position       */
#define DDRPHY_DX1GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX1GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX1GCR: RTTOH Mask           */

#define DDRPHY_DX1GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX1GCR: RTTOAL Position      */
#define DDRPHY_DX1GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX1GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX1GCR: RTTOAL Mask          */

#define DDRPHY_DX1GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX1GCR: DXOEO Position       */
#define DDRPHY_DX1GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX1GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX1GCR: DXOEO Mask           */

#define DDRPHY_DX1GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX1GCR: PLLRST Position      */
#define DDRPHY_DX1GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX1GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX1GCR: PLLRST Mask          */

#define DDRPHY_DX1GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX1GCR: PLLPD Position       */
#define DDRPHY_DX1GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX1GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX1GCR: PLLPD Mask           */

#define DDRPHY_DX1GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX1GCR: GSHIFT Position      */
#define DDRPHY_DX1GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX1GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX1GCR: GSHIFT Mask          */

#define DDRPHY_DX1GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX1GCR: PLLBYP Position      */
#define DDRPHY_DX1GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX1GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX1GCR: PLLBYP Mask          */

#define DDRPHY_DX1GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX1GCR: WLRKEN Position      */
#define DDRPHY_DX1GCR_WLRKEN_Msk         (0xful << DDRPHY_DX1GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX1GCR: WLRKEN Mask          */

#define DDRPHY_DX1GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX1GCR: MDLEN Position       */
#define DDRPHY_DX1GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX1GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX1GCR: MDLEN Mask           */

#define DDRPHY_DX1GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX1GCR: CALBYP Position      */
#define DDRPHY_DX1GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX1GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX1GCR: CALBYP Mask          */

#define DDRPHY_DX1GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX1GSR0: WDQCAL Position     */
#define DDRPHY_DX1GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX1GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX1GSR0: WDQCAL Mask         */

#define DDRPHY_DX1GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX1GSR0: RDQSCAL Position    */
#define DDRPHY_DX1GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX1GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX1GSR0: RDQSCAL Mask        */

#define DDRPHY_DX1GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX1GSR0: RDQSNCAL Position   */
#define DDRPHY_DX1GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX1GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX1GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX1GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX1GSR0: GDQSCAL Position    */
#define DDRPHY_DX1GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX1GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX1GSR0: GDQSCAL Mask        */

#define DDRPHY_DX1GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX1GSR0: WLCAL Position      */
#define DDRPHY_DX1GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX1GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX1GSR0: WLCAL Mask          */

#define DDRPHY_DX1GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX1GSR0: WLDONE Position     */
#define DDRPHY_DX1GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX1GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX1GSR0: WLDONE Mask         */

#define DDRPHY_DX1GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX1GSR0: WLERR Position      */
#define DDRPHY_DX1GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX1GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX1GSR0: WLERR Mask          */

#define DDRPHY_DX1GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX1GSR0: WLPRD Position      */
#define DDRPHY_DX1GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX1GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX1GSR0: WLPRD Mask          */

#define DDRPHY_DX1GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX1GSR0: DPLOCK Position     */
#define DDRPHY_DX1GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX1GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX1GSR0: DPLOCK Mask         */

#define DDRPHY_DX1GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX1GSR0: GDQSPRD Position    */
#define DDRPHY_DX1GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX1GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX1GSR0: GDQSPRD Mask        */

#define DDRPHY_DX1GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX1GSR0: QSGERR Position     */
#define DDRPHY_DX1GSR0_QSGERR_Msk        (0xful << DDRPHY_DX1GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX1GSR0: QSGERR Mask         */

#define DDRPHY_DX1GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX1GSR0: WLDQ Position       */
#define DDRPHY_DX1GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX1GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX1GSR0: WLDQ Mask           */

#define DDRPHY_DX1GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX1GSR1: DLTDONE Position    */
#define DDRPHY_DX1GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX1GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX1GSR1: DLTDONE Mask        */

#define DDRPHY_DX1GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX1GSR1: DLTCODE Position    */
#define DDRPHY_DX1GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX1GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX1GSR1: DLTCODE Mask        */

#define DDRPHY_DX1BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX1BDLR0: DQ0WBD Position    */
#define DDRPHY_DX1BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX1BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX1BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX1BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX1BDLR0: DQ1WBD Position    */
#define DDRPHY_DX1BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX1BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX1BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX1BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX1BDLR0: DQ2WBD Position    */
#define DDRPHY_DX1BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX1BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX1BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX1BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX1BDLR0: DQ3WBD Position    */
#define DDRPHY_DX1BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX1BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX1BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX1BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX1BDLR0: DQ4WBD Position    */
#define DDRPHY_DX1BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX1BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX1BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX1BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX1BDLR1: DQ5WBD Position    */
#define DDRPHY_DX1BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX1BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX1BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX1BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX1BDLR1: DQ6WBD Position    */
#define DDRPHY_DX1BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX1BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX1BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX1BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX1BDLR1: DQ7WBD Position    */
#define DDRPHY_DX1BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX1BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX1BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX1BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX1BDLR1: DMWBD Position     */
#define DDRPHY_DX1BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX1BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX1BDLR1: DMWBD Mask         */

#define DDRPHY_DX1BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX1BDLR1: DSWBD Position     */
#define DDRPHY_DX1BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX1BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX1BDLR1: DSWBD Mask         */

#define DDRPHY_DX1BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX1BDLR2: DSOEBD Position    */
#define DDRPHY_DX1BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX1BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX1BDLR2: DSOEBD Mask        */

#define DDRPHY_DX1BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX1BDLR2: DQOEBD Position    */
#define DDRPHY_DX1BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX1BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX1BDLR2: DQOEBD Mask        */

#define DDRPHY_DX1BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX1BDLR2: DSRBD Position     */
#define DDRPHY_DX1BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX1BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX1BDLR2: DSRBD Mask         */

#define DDRPHY_DX1BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX1BDLR2: DSNRBD Position    */
#define DDRPHY_DX1BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX1BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX1BDLR2: DSNRBD Mask        */

#define DDRPHY_DX1BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX1BDLR3: DQ0RBD Position    */
#define DDRPHY_DX1BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX1BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX1BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX1BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX1BDLR3: DQ1RBD Position    */
#define DDRPHY_DX1BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX1BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX1BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX1BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX1BDLR3: DQ2RBD Position    */
#define DDRPHY_DX1BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX1BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX1BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX1BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX1BDLR3: DQ3RBD Position    */
#define DDRPHY_DX1BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX1BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX1BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX1BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX1BDLR3: DQ4RBD Position    */
#define DDRPHY_DX1BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX1BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX1BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX1BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX1BDLR4: DQ5RBD Position    */
#define DDRPHY_DX1BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX1BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX1BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX1BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX1BDLR4: DQ6RBD Position    */
#define DDRPHY_DX1BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX1BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX1BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX1BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX1BDLR4: DQ7RBD Position    */
#define DDRPHY_DX1BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX1BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX1BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX1BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX1BDLR4: DMRBD Position     */
#define DDRPHY_DX1BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX1BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX1BDLR4: DMRBD Mask         */

#define DDRPHY_DX1LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX1LCDLR0: R0WLD Position    */
#define DDRPHY_DX1LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX1LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX1LCDLR0: R0WLD Mask        */

#define DDRPHY_DX1LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX1LCDLR0: R1WLD Position    */
#define DDRPHY_DX1LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX1LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX1LCDLR0: R1WLD Mask        */

#define DDRPHY_DX1LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX1LCDLR0: R2WLD Position    */
#define DDRPHY_DX1LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX1LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX1LCDLR0: R2WLD Mask        */

#define DDRPHY_DX1LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX1LCDLR0: R3WLD Position    */
#define DDRPHY_DX1LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX1LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX1LCDLR0: R3WLD Mask        */

#define DDRPHY_DX1LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX1LCDLR1: WDQD Position     */
#define DDRPHY_DX1LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX1LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX1LCDLR1: WDQD Mask         */

#define DDRPHY_DX1LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX1LCDLR1: RDQSD Position    */
#define DDRPHY_DX1LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX1LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX1LCDLR1: RDQSD Mask        */

#define DDRPHY_DX1LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX1LCDLR1: RDQSND Position   */
#define DDRPHY_DX1LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX1LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX1LCDLR1: RDQSND Mask       */

#define DDRPHY_DX1LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX1LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX1LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX1LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX1LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX1LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX1LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX1LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX1LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX1LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX1LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX1LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX1LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX1LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX1LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX1LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX1LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX1LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX1LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX1LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX1MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX1MDLR: IPRD Position       */
#define DDRPHY_DX1MDLR_IPRD_Msk          (0xfful << DDRPHY_DX1MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX1MDLR: IPRD Mask           */

#define DDRPHY_DX1MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX1MDLR: TPRD Position       */
#define DDRPHY_DX1MDLR_TPRD_Msk          (0xfful << DDRPHY_DX1MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX1MDLR: TPRD Mask           */

#define DDRPHY_DX1MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX1MDLR: MDLD Position       */
#define DDRPHY_DX1MDLR_MDLD_Msk          (0xfful << DDRPHY_DX1MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX1MDLR: MDLD Mask           */

#define DDRPHY_DX1GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX1GTR: R0DGSL Position      */
#define DDRPHY_DX1GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX1GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX1GTR: R0DGSL Mask          */

#define DDRPHY_DX1GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX1GTR: R1DGSL Position      */
#define DDRPHY_DX1GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX1GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX1GTR: R1DGSL Mask          */

#define DDRPHY_DX1GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX1GTR: R2DGSL Position      */
#define DDRPHY_DX1GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX1GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX1GTR: R2DGSL Mask          */

#define DDRPHY_DX1GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX1GTR: R3DGSL Position      */
#define DDRPHY_DX1GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX1GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX1GTR: R3DGSL Mask          */

#define DDRPHY_DX1GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX1GTR: R0WLSL Position      */
#define DDRPHY_DX1GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX1GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX1GTR: R0WLSL Mask          */

#define DDRPHY_DX1GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX1GTR: R1WLSL Position      */
#define DDRPHY_DX1GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX1GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX1GTR: R1WLSL Mask          */

#define DDRPHY_DX1GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX1GTR: R2WLSL Position      */
#define DDRPHY_DX1GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX1GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX1GTR: R2WLSL Mask          */

#define DDRPHY_DX1GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX1GTR: R3WLSL Position      */
#define DDRPHY_DX1GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX1GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX1GTR: R3WLSL Mask          */

#define DDRPHY_DX1GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX1GSR2: RDERR Position      */
#define DDRPHY_DX1GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX1GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX1GSR2: RDERR Mask          */

#define DDRPHY_DX1GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX1GSR2: RDWN Position       */
#define DDRPHY_DX1GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX1GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX1GSR2: RDWN Mask           */

#define DDRPHY_DX1GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX1GSR2: WDERR Position      */
#define DDRPHY_DX1GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX1GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX1GSR2: WDERR Mask          */

#define DDRPHY_DX1GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX1GSR2: WDWN Position       */
#define DDRPHY_DX1GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX1GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX1GSR2: WDWN Mask           */

#define DDRPHY_DX1GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX1GSR2: REERR Position      */
#define DDRPHY_DX1GSR2_REERR_Msk         (0x1ul << DDRPHY_DX1GSR2_REERR_Pos)               /*!< DDRPHY_T::DX1GSR2: REERR Mask          */

#define DDRPHY_DX1GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX1GSR2: REWN Position       */
#define DDRPHY_DX1GSR2_REWN_Msk          (0x1ul << DDRPHY_DX1GSR2_REWN_Pos)                /*!< DDRPHY_T::DX1GSR2: REWN Mask           */

#define DDRPHY_DX1GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX1GSR2: WEERR Position      */
#define DDRPHY_DX1GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX1GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX1GSR2: WEERR Mask          */

#define DDRPHY_DX1GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX1GSR2: WEWN Position       */
#define DDRPHY_DX1GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX1GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX1GSR2: WEWN Mask           */

#define DDRPHY_DX1GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX1GSR2: ESTAT Position      */
#define DDRPHY_DX1GSR2_ESTAT_Msk         (0xful << DDRPHY_DX1GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX1GSR2: ESTAT Mask          */

#define DDRPHY_DX2GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX2GCR: DXEN Position        */
#define DDRPHY_DX2GCR_DXEN_Msk           (0x1ul << DDRPHY_DX2GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX2GCR: DXEN Mask            */

#define DDRPHY_DX2GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX2GCR: DQSODT Position      */
#define DDRPHY_DX2GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX2GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX2GCR: DQSODT Mask          */

#define DDRPHY_DX2GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX2GCR: DQODT Position       */
#define DDRPHY_DX2GCR_DQODT_Msk          (0x1ul << DDRPHY_DX2GCR_DQODT_Pos)                /*!< DDRPHY_T::DX2GCR: DQODT Mask           */

#define DDRPHY_DX2GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX2GCR: DXIOM Position       */
#define DDRPHY_DX2GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX2GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX2GCR: DXIOM Mask           */

#define DDRPHY_DX2GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX2GCR: DXPDD Position       */
#define DDRPHY_DX2GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX2GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX2GCR: DXPDD Mask           */

#define DDRPHY_DX2GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX2GCR: DXPDR Position       */
#define DDRPHY_DX2GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX2GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX2GCR: DXPDR Mask           */

#define DDRPHY_DX2GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX2GCR: DQSRPD Position      */
#define DDRPHY_DX2GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX2GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX2GCR: DQSRPD Mask          */

#define DDRPHY_DX2GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX2GCR: DSEN Position        */
#define DDRPHY_DX2GCR_DSEN_Msk           (0x3ul << DDRPHY_DX2GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX2GCR: DSEN Mask            */

#define DDRPHY_DX2GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX2GCR: DQSRTT Position      */
#define DDRPHY_DX2GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX2GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX2GCR: DQSRTT Mask          */

#define DDRPHY_DX2GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX2GCR: DQRTT Position       */
#define DDRPHY_DX2GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX2GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX2GCR: DQRTT Mask           */

#define DDRPHY_DX2GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX2GCR: RTTOH Position       */
#define DDRPHY_DX2GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX2GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX2GCR: RTTOH Mask           */

#define DDRPHY_DX2GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX2GCR: RTTOAL Position      */
#define DDRPHY_DX2GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX2GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX2GCR: RTTOAL Mask          */

#define DDRPHY_DX2GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX2GCR: DXOEO Position       */
#define DDRPHY_DX2GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX2GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX2GCR: DXOEO Mask           */

#define DDRPHY_DX2GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX2GCR: PLLRST Position      */
#define DDRPHY_DX2GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX2GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX2GCR: PLLRST Mask          */

#define DDRPHY_DX2GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX2GCR: PLLPD Position       */
#define DDRPHY_DX2GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX2GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX2GCR: PLLPD Mask           */

#define DDRPHY_DX2GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX2GCR: GSHIFT Position      */
#define DDRPHY_DX2GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX2GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX2GCR: GSHIFT Mask          */

#define DDRPHY_DX2GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX2GCR: PLLBYP Position      */
#define DDRPHY_DX2GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX2GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX2GCR: PLLBYP Mask          */

#define DDRPHY_DX2GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX2GCR: WLRKEN Position      */
#define DDRPHY_DX2GCR_WLRKEN_Msk         (0xful << DDRPHY_DX2GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX2GCR: WLRKEN Mask          */

#define DDRPHY_DX2GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX2GCR: MDLEN Position       */
#define DDRPHY_DX2GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX2GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX2GCR: MDLEN Mask           */

#define DDRPHY_DX2GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX2GCR: CALBYP Position      */
#define DDRPHY_DX2GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX2GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX2GCR: CALBYP Mask          */

#define DDRPHY_DX2GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX2GSR0: WDQCAL Position     */
#define DDRPHY_DX2GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX2GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX2GSR0: WDQCAL Mask         */

#define DDRPHY_DX2GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX2GSR0: RDQSCAL Position    */
#define DDRPHY_DX2GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX2GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX2GSR0: RDQSCAL Mask        */

#define DDRPHY_DX2GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX2GSR0: RDQSNCAL Position   */
#define DDRPHY_DX2GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX2GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX2GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX2GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX2GSR0: GDQSCAL Position    */
#define DDRPHY_DX2GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX2GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX2GSR0: GDQSCAL Mask        */

#define DDRPHY_DX2GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX2GSR0: WLCAL Position      */
#define DDRPHY_DX2GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX2GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX2GSR0: WLCAL Mask          */

#define DDRPHY_DX2GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX2GSR0: WLDONE Position     */
#define DDRPHY_DX2GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX2GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX2GSR0: WLDONE Mask         */

#define DDRPHY_DX2GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX2GSR0: WLERR Position      */
#define DDRPHY_DX2GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX2GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX2GSR0: WLERR Mask          */

#define DDRPHY_DX2GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX2GSR0: WLPRD Position      */
#define DDRPHY_DX2GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX2GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX2GSR0: WLPRD Mask          */

#define DDRPHY_DX2GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX2GSR0: DPLOCK Position     */
#define DDRPHY_DX2GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX2GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX2GSR0: DPLOCK Mask         */

#define DDRPHY_DX2GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX2GSR0: GDQSPRD Position    */
#define DDRPHY_DX2GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX2GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX2GSR0: GDQSPRD Mask        */

#define DDRPHY_DX2GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX2GSR0: QSGERR Position     */
#define DDRPHY_DX2GSR0_QSGERR_Msk        (0xful << DDRPHY_DX2GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX2GSR0: QSGERR Mask         */

#define DDRPHY_DX2GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX2GSR0: WLDQ Position       */
#define DDRPHY_DX2GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX2GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX2GSR0: WLDQ Mask           */

#define DDRPHY_DX2GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX2GSR1: DLTDONE Position    */
#define DDRPHY_DX2GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX2GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX2GSR1: DLTDONE Mask        */

#define DDRPHY_DX2GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX2GSR1: DLTCODE Position    */
#define DDRPHY_DX2GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX2GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX2GSR1: DLTCODE Mask        */

#define DDRPHY_DX2BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX2BDLR0: DQ0WBD Position    */
#define DDRPHY_DX2BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX2BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX2BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX2BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX2BDLR0: DQ1WBD Position    */
#define DDRPHY_DX2BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX2BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX2BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX2BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX2BDLR0: DQ2WBD Position    */
#define DDRPHY_DX2BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX2BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX2BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX2BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX2BDLR0: DQ3WBD Position    */
#define DDRPHY_DX2BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX2BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX2BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX2BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX2BDLR0: DQ4WBD Position    */
#define DDRPHY_DX2BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX2BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX2BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX2BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX2BDLR1: DQ5WBD Position    */
#define DDRPHY_DX2BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX2BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX2BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX2BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX2BDLR1: DQ6WBD Position    */
#define DDRPHY_DX2BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX2BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX2BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX2BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX2BDLR1: DQ7WBD Position    */
#define DDRPHY_DX2BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX2BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX2BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX2BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX2BDLR1: DMWBD Position     */
#define DDRPHY_DX2BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX2BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX2BDLR1: DMWBD Mask         */

#define DDRPHY_DX2BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX2BDLR1: DSWBD Position     */
#define DDRPHY_DX2BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX2BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX2BDLR1: DSWBD Mask         */

#define DDRPHY_DX2BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX2BDLR2: DSOEBD Position    */
#define DDRPHY_DX2BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX2BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX2BDLR2: DSOEBD Mask        */

#define DDRPHY_DX2BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX2BDLR2: DQOEBD Position    */
#define DDRPHY_DX2BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX2BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX2BDLR2: DQOEBD Mask        */

#define DDRPHY_DX2BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX2BDLR2: DSRBD Position     */
#define DDRPHY_DX2BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX2BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX2BDLR2: DSRBD Mask         */

#define DDRPHY_DX2BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX2BDLR2: DSNRBD Position    */
#define DDRPHY_DX2BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX2BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX2BDLR2: DSNRBD Mask        */

#define DDRPHY_DX2BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX2BDLR3: DQ0RBD Position    */
#define DDRPHY_DX2BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX2BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX2BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX2BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX2BDLR3: DQ1RBD Position    */
#define DDRPHY_DX2BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX2BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX2BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX2BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX2BDLR3: DQ2RBD Position    */
#define DDRPHY_DX2BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX2BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX2BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX2BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX2BDLR3: DQ3RBD Position    */
#define DDRPHY_DX2BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX2BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX2BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX2BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX2BDLR3: DQ4RBD Position    */
#define DDRPHY_DX2BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX2BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX2BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX2BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX2BDLR4: DQ5RBD Position    */
#define DDRPHY_DX2BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX2BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX2BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX2BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX2BDLR4: DQ6RBD Position    */
#define DDRPHY_DX2BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX2BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX2BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX2BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX2BDLR4: DQ7RBD Position    */
#define DDRPHY_DX2BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX2BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX2BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX2BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX2BDLR4: DMRBD Position     */
#define DDRPHY_DX2BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX2BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX2BDLR4: DMRBD Mask         */

#define DDRPHY_DX2LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX2LCDLR0: R0WLD Position    */
#define DDRPHY_DX2LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX2LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX2LCDLR0: R0WLD Mask        */

#define DDRPHY_DX2LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX2LCDLR0: R1WLD Position    */
#define DDRPHY_DX2LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX2LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX2LCDLR0: R1WLD Mask        */

#define DDRPHY_DX2LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX2LCDLR0: R2WLD Position    */
#define DDRPHY_DX2LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX2LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX2LCDLR0: R2WLD Mask        */

#define DDRPHY_DX2LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX2LCDLR0: R3WLD Position    */
#define DDRPHY_DX2LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX2LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX2LCDLR0: R3WLD Mask        */

#define DDRPHY_DX2LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX2LCDLR1: WDQD Position     */
#define DDRPHY_DX2LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX2LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX2LCDLR1: WDQD Mask         */

#define DDRPHY_DX2LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX2LCDLR1: RDQSD Position    */
#define DDRPHY_DX2LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX2LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX2LCDLR1: RDQSD Mask        */

#define DDRPHY_DX2LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX2LCDLR1: RDQSND Position   */
#define DDRPHY_DX2LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX2LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX2LCDLR1: RDQSND Mask       */

#define DDRPHY_DX2LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX2LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX2LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX2LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX2LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX2LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX2LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX2LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX2LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX2LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX2LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX2LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX2LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX2LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX2LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX2LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX2LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX2LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX2LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX2LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX2MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX2MDLR: IPRD Position       */
#define DDRPHY_DX2MDLR_IPRD_Msk          (0xfful << DDRPHY_DX2MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX2MDLR: IPRD Mask           */

#define DDRPHY_DX2MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX2MDLR: TPRD Position       */
#define DDRPHY_DX2MDLR_TPRD_Msk          (0xfful << DDRPHY_DX2MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX2MDLR: TPRD Mask           */

#define DDRPHY_DX2MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX2MDLR: MDLD Position       */
#define DDRPHY_DX2MDLR_MDLD_Msk          (0xfful << DDRPHY_DX2MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX2MDLR: MDLD Mask           */

#define DDRPHY_DX2GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX2GTR: R0DGSL Position      */
#define DDRPHY_DX2GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX2GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX2GTR: R0DGSL Mask          */

#define DDRPHY_DX2GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX2GTR: R1DGSL Position      */
#define DDRPHY_DX2GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX2GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX2GTR: R1DGSL Mask          */

#define DDRPHY_DX2GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX2GTR: R2DGSL Position      */
#define DDRPHY_DX2GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX2GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX2GTR: R2DGSL Mask          */

#define DDRPHY_DX2GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX2GTR: R3DGSL Position      */
#define DDRPHY_DX2GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX2GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX2GTR: R3DGSL Mask          */

#define DDRPHY_DX2GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX2GTR: R0WLSL Position      */
#define DDRPHY_DX2GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX2GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX2GTR: R0WLSL Mask          */

#define DDRPHY_DX2GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX2GTR: R1WLSL Position      */
#define DDRPHY_DX2GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX2GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX2GTR: R1WLSL Mask          */

#define DDRPHY_DX2GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX2GTR: R2WLSL Position      */
#define DDRPHY_DX2GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX2GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX2GTR: R2WLSL Mask          */

#define DDRPHY_DX2GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX2GTR: R3WLSL Position      */
#define DDRPHY_DX2GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX2GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX2GTR: R3WLSL Mask          */

#define DDRPHY_DX2GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX2GSR2: RDERR Position      */
#define DDRPHY_DX2GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX2GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX2GSR2: RDERR Mask          */

#define DDRPHY_DX2GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX2GSR2: RDWN Position       */
#define DDRPHY_DX2GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX2GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX2GSR2: RDWN Mask           */

#define DDRPHY_DX2GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX2GSR2: WDERR Position      */
#define DDRPHY_DX2GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX2GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX2GSR2: WDERR Mask          */

#define DDRPHY_DX2GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX2GSR2: WDWN Position       */
#define DDRPHY_DX2GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX2GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX2GSR2: WDWN Mask           */

#define DDRPHY_DX2GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX2GSR2: REERR Position      */
#define DDRPHY_DX2GSR2_REERR_Msk         (0x1ul << DDRPHY_DX2GSR2_REERR_Pos)               /*!< DDRPHY_T::DX2GSR2: REERR Mask          */

#define DDRPHY_DX2GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX2GSR2: REWN Position       */
#define DDRPHY_DX2GSR2_REWN_Msk          (0x1ul << DDRPHY_DX2GSR2_REWN_Pos)                /*!< DDRPHY_T::DX2GSR2: REWN Mask           */

#define DDRPHY_DX2GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX2GSR2: WEERR Position      */
#define DDRPHY_DX2GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX2GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX2GSR2: WEERR Mask          */

#define DDRPHY_DX2GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX2GSR2: WEWN Position       */
#define DDRPHY_DX2GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX2GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX2GSR2: WEWN Mask           */

#define DDRPHY_DX2GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX2GSR2: ESTAT Position      */
#define DDRPHY_DX2GSR2_ESTAT_Msk         (0xful << DDRPHY_DX2GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX2GSR2: ESTAT Mask          */

#define DDRPHY_DX3GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX3GCR: DXEN Position        */
#define DDRPHY_DX3GCR_DXEN_Msk           (0x1ul << DDRPHY_DX3GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX3GCR: DXEN Mask            */

#define DDRPHY_DX3GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX3GCR: DQSODT Position      */
#define DDRPHY_DX3GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX3GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX3GCR: DQSODT Mask          */

#define DDRPHY_DX3GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX3GCR: DQODT Position       */
#define DDRPHY_DX3GCR_DQODT_Msk          (0x1ul << DDRPHY_DX3GCR_DQODT_Pos)                /*!< DDRPHY_T::DX3GCR: DQODT Mask           */

#define DDRPHY_DX3GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX3GCR: DXIOM Position       */
#define DDRPHY_DX3GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX3GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX3GCR: DXIOM Mask           */

#define DDRPHY_DX3GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX3GCR: DXPDD Position       */
#define DDRPHY_DX3GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX3GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX3GCR: DXPDD Mask           */

#define DDRPHY_DX3GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX3GCR: DXPDR Position       */
#define DDRPHY_DX3GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX3GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX3GCR: DXPDR Mask           */

#define DDRPHY_DX3GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX3GCR: DQSRPD Position      */
#define DDRPHY_DX3GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX3GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX3GCR: DQSRPD Mask          */

#define DDRPHY_DX3GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX3GCR: DSEN Position        */
#define DDRPHY_DX3GCR_DSEN_Msk           (0x3ul << DDRPHY_DX3GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX3GCR: DSEN Mask            */

#define DDRPHY_DX3GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX3GCR: DQSRTT Position      */
#define DDRPHY_DX3GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX3GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX3GCR: DQSRTT Mask          */

#define DDRPHY_DX3GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX3GCR: DQRTT Position       */
#define DDRPHY_DX3GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX3GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX3GCR: DQRTT Mask           */

#define DDRPHY_DX3GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX3GCR: RTTOH Position       */
#define DDRPHY_DX3GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX3GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX3GCR: RTTOH Mask           */

#define DDRPHY_DX3GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX3GCR: RTTOAL Position      */
#define DDRPHY_DX3GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX3GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX3GCR: RTTOAL Mask          */

#define DDRPHY_DX3GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX3GCR: DXOEO Position       */
#define DDRPHY_DX3GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX3GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX3GCR: DXOEO Mask           */

#define DDRPHY_DX3GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX3GCR: PLLRST Position      */
#define DDRPHY_DX3GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX3GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX3GCR: PLLRST Mask          */

#define DDRPHY_DX3GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX3GCR: PLLPD Position       */
#define DDRPHY_DX3GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX3GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX3GCR: PLLPD Mask           */

#define DDRPHY_DX3GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX3GCR: GSHIFT Position      */
#define DDRPHY_DX3GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX3GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX3GCR: GSHIFT Mask          */

#define DDRPHY_DX3GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX3GCR: PLLBYP Position      */
#define DDRPHY_DX3GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX3GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX3GCR: PLLBYP Mask          */

#define DDRPHY_DX3GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX3GCR: WLRKEN Position      */
#define DDRPHY_DX3GCR_WLRKEN_Msk         (0xful << DDRPHY_DX3GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX3GCR: WLRKEN Mask          */

#define DDRPHY_DX3GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX3GCR: MDLEN Position       */
#define DDRPHY_DX3GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX3GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX3GCR: MDLEN Mask           */

#define DDRPHY_DX3GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX3GCR: CALBYP Position      */
#define DDRPHY_DX3GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX3GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX3GCR: CALBYP Mask          */

#define DDRPHY_DX3GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX3GSR0: WDQCAL Position     */
#define DDRPHY_DX3GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX3GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX3GSR0: WDQCAL Mask         */

#define DDRPHY_DX3GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX3GSR0: RDQSCAL Position    */
#define DDRPHY_DX3GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX3GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX3GSR0: RDQSCAL Mask        */

#define DDRPHY_DX3GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX3GSR0: RDQSNCAL Position   */
#define DDRPHY_DX3GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX3GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX3GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX3GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX3GSR0: GDQSCAL Position    */
#define DDRPHY_DX3GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX3GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX3GSR0: GDQSCAL Mask        */

#define DDRPHY_DX3GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX3GSR0: WLCAL Position      */
#define DDRPHY_DX3GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX3GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX3GSR0: WLCAL Mask          */

#define DDRPHY_DX3GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX3GSR0: WLDONE Position     */
#define DDRPHY_DX3GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX3GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX3GSR0: WLDONE Mask         */

#define DDRPHY_DX3GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX3GSR0: WLERR Position      */
#define DDRPHY_DX3GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX3GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX3GSR0: WLERR Mask          */

#define DDRPHY_DX3GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX3GSR0: WLPRD Position      */
#define DDRPHY_DX3GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX3GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX3GSR0: WLPRD Mask          */

#define DDRPHY_DX3GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX3GSR0: DPLOCK Position     */
#define DDRPHY_DX3GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX3GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX3GSR0: DPLOCK Mask         */

#define DDRPHY_DX3GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX3GSR0: GDQSPRD Position    */
#define DDRPHY_DX3GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX3GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX3GSR0: GDQSPRD Mask        */

#define DDRPHY_DX3GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX3GSR0: QSGERR Position     */
#define DDRPHY_DX3GSR0_QSGERR_Msk        (0xful << DDRPHY_DX3GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX3GSR0: QSGERR Mask         */

#define DDRPHY_DX3GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX3GSR0: WLDQ Position       */
#define DDRPHY_DX3GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX3GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX3GSR0: WLDQ Mask           */

#define DDRPHY_DX3GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX3GSR1: DLTDONE Position    */
#define DDRPHY_DX3GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX3GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX3GSR1: DLTDONE Mask        */

#define DDRPHY_DX3GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX3GSR1: DLTCODE Position    */
#define DDRPHY_DX3GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX3GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX3GSR1: DLTCODE Mask        */

#define DDRPHY_DX3BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX3BDLR0: DQ0WBD Position    */
#define DDRPHY_DX3BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX3BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX3BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX3BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX3BDLR0: DQ1WBD Position    */
#define DDRPHY_DX3BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX3BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX3BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX3BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX3BDLR0: DQ2WBD Position    */
#define DDRPHY_DX3BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX3BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX3BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX3BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX3BDLR0: DQ3WBD Position    */
#define DDRPHY_DX3BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX3BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX3BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX3BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX3BDLR0: DQ4WBD Position    */
#define DDRPHY_DX3BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX3BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX3BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX3BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX3BDLR1: DQ5WBD Position    */
#define DDRPHY_DX3BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX3BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX3BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX3BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX3BDLR1: DQ6WBD Position    */
#define DDRPHY_DX3BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX3BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX3BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX3BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX3BDLR1: DQ7WBD Position    */
#define DDRPHY_DX3BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX3BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX3BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX3BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX3BDLR1: DMWBD Position     */
#define DDRPHY_DX3BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX3BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX3BDLR1: DMWBD Mask         */

#define DDRPHY_DX3BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX3BDLR1: DSWBD Position     */
#define DDRPHY_DX3BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX3BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX3BDLR1: DSWBD Mask         */

#define DDRPHY_DX3BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX3BDLR2: DSOEBD Position    */
#define DDRPHY_DX3BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX3BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX3BDLR2: DSOEBD Mask        */

#define DDRPHY_DX3BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX3BDLR2: DQOEBD Position    */
#define DDRPHY_DX3BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX3BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX3BDLR2: DQOEBD Mask        */

#define DDRPHY_DX3BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX3BDLR2: DSRBD Position     */
#define DDRPHY_DX3BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX3BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX3BDLR2: DSRBD Mask         */

#define DDRPHY_DX3BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX3BDLR2: DSNRBD Position    */
#define DDRPHY_DX3BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX3BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX3BDLR2: DSNRBD Mask        */

#define DDRPHY_DX3BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX3BDLR3: DQ0RBD Position    */
#define DDRPHY_DX3BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX3BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX3BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX3BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX3BDLR3: DQ1RBD Position    */
#define DDRPHY_DX3BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX3BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX3BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX3BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX3BDLR3: DQ2RBD Position    */
#define DDRPHY_DX3BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX3BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX3BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX3BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX3BDLR3: DQ3RBD Position    */
#define DDRPHY_DX3BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX3BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX3BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX3BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX3BDLR3: DQ4RBD Position    */
#define DDRPHY_DX3BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX3BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX3BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX3BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX3BDLR4: DQ5RBD Position    */
#define DDRPHY_DX3BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX3BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX3BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX3BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX3BDLR4: DQ6RBD Position    */
#define DDRPHY_DX3BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX3BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX3BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX3BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX3BDLR4: DQ7RBD Position    */
#define DDRPHY_DX3BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX3BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX3BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX3BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX3BDLR4: DMRBD Position     */
#define DDRPHY_DX3BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX3BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX3BDLR4: DMRBD Mask         */

#define DDRPHY_DX3LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX3LCDLR0: R0WLD Position    */
#define DDRPHY_DX3LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX3LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX3LCDLR0: R0WLD Mask        */

#define DDRPHY_DX3LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX3LCDLR0: R1WLD Position    */
#define DDRPHY_DX3LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX3LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX3LCDLR0: R1WLD Mask        */

#define DDRPHY_DX3LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX3LCDLR0: R2WLD Position    */
#define DDRPHY_DX3LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX3LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX3LCDLR0: R2WLD Mask        */

#define DDRPHY_DX3LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX3LCDLR0: R3WLD Position    */
#define DDRPHY_DX3LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX3LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX3LCDLR0: R3WLD Mask        */

#define DDRPHY_DX3LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX3LCDLR1: WDQD Position     */
#define DDRPHY_DX3LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX3LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX3LCDLR1: WDQD Mask         */

#define DDRPHY_DX3LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX3LCDLR1: RDQSD Position    */
#define DDRPHY_DX3LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX3LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX3LCDLR1: RDQSD Mask        */

#define DDRPHY_DX3LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX3LCDLR1: RDQSND Position   */
#define DDRPHY_DX3LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX3LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX3LCDLR1: RDQSND Mask       */

#define DDRPHY_DX3LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX3LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX3LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX3LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX3LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX3LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX3LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX3LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX3LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX3LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX3LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX3LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX3LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX3LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX3LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX3LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX3LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX3LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX3LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX3LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX3MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX3MDLR: IPRD Position       */
#define DDRPHY_DX3MDLR_IPRD_Msk          (0xfful << DDRPHY_DX3MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX3MDLR: IPRD Mask           */

#define DDRPHY_DX3MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX3MDLR: TPRD Position       */
#define DDRPHY_DX3MDLR_TPRD_Msk          (0xfful << DDRPHY_DX3MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX3MDLR: TPRD Mask           */

#define DDRPHY_DX3MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX3MDLR: MDLD Position       */
#define DDRPHY_DX3MDLR_MDLD_Msk          (0xfful << DDRPHY_DX3MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX3MDLR: MDLD Mask           */

#define DDRPHY_DX3GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX3GTR: R0DGSL Position      */
#define DDRPHY_DX3GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX3GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX3GTR: R0DGSL Mask          */

#define DDRPHY_DX3GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX3GTR: R1DGSL Position      */
#define DDRPHY_DX3GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX3GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX3GTR: R1DGSL Mask          */

#define DDRPHY_DX3GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX3GTR: R2DGSL Position      */
#define DDRPHY_DX3GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX3GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX3GTR: R2DGSL Mask          */

#define DDRPHY_DX3GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX3GTR: R3DGSL Position      */
#define DDRPHY_DX3GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX3GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX3GTR: R3DGSL Mask          */

#define DDRPHY_DX3GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX3GTR: R0WLSL Position      */
#define DDRPHY_DX3GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX3GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX3GTR: R0WLSL Mask          */

#define DDRPHY_DX3GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX3GTR: R1WLSL Position      */
#define DDRPHY_DX3GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX3GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX3GTR: R1WLSL Mask          */

#define DDRPHY_DX3GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX3GTR: R2WLSL Position      */
#define DDRPHY_DX3GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX3GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX3GTR: R2WLSL Mask          */

#define DDRPHY_DX3GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX3GTR: R3WLSL Position      */
#define DDRPHY_DX3GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX3GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX3GTR: R3WLSL Mask          */

#define DDRPHY_DX3GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX3GSR2: RDERR Position      */
#define DDRPHY_DX3GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX3GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX3GSR2: RDERR Mask          */

#define DDRPHY_DX3GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX3GSR2: RDWN Position       */
#define DDRPHY_DX3GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX3GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX3GSR2: RDWN Mask           */

#define DDRPHY_DX3GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX3GSR2: WDERR Position      */
#define DDRPHY_DX3GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX3GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX3GSR2: WDERR Mask          */

#define DDRPHY_DX3GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX3GSR2: WDWN Position       */
#define DDRPHY_DX3GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX3GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX3GSR2: WDWN Mask           */

#define DDRPHY_DX3GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX3GSR2: REERR Position      */
#define DDRPHY_DX3GSR2_REERR_Msk         (0x1ul << DDRPHY_DX3GSR2_REERR_Pos)               /*!< DDRPHY_T::DX3GSR2: REERR Mask          */

#define DDRPHY_DX3GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX3GSR2: REWN Position       */
#define DDRPHY_DX3GSR2_REWN_Msk          (0x1ul << DDRPHY_DX3GSR2_REWN_Pos)                /*!< DDRPHY_T::DX3GSR2: REWN Mask           */

#define DDRPHY_DX3GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX3GSR2: WEERR Position      */
#define DDRPHY_DX3GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX3GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX3GSR2: WEERR Mask          */

#define DDRPHY_DX3GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX3GSR2: WEWN Position       */
#define DDRPHY_DX3GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX3GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX3GSR2: WEWN Mask           */

#define DDRPHY_DX3GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX3GSR2: ESTAT Position      */
#define DDRPHY_DX3GSR2_ESTAT_Msk         (0xful << DDRPHY_DX3GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX3GSR2: ESTAT Mask          */

#define DDRPHY_DX4GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX4GCR: DXEN Position        */
#define DDRPHY_DX4GCR_DXEN_Msk           (0x1ul << DDRPHY_DX4GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX4GCR: DXEN Mask            */

#define DDRPHY_DX4GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX4GCR: DQSODT Position      */
#define DDRPHY_DX4GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX4GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX4GCR: DQSODT Mask          */

#define DDRPHY_DX4GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX4GCR: DQODT Position       */
#define DDRPHY_DX4GCR_DQODT_Msk          (0x1ul << DDRPHY_DX4GCR_DQODT_Pos)                /*!< DDRPHY_T::DX4GCR: DQODT Mask           */

#define DDRPHY_DX4GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX4GCR: DXIOM Position       */
#define DDRPHY_DX4GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX4GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX4GCR: DXIOM Mask           */

#define DDRPHY_DX4GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX4GCR: DXPDD Position       */
#define DDRPHY_DX4GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX4GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX4GCR: DXPDD Mask           */

#define DDRPHY_DX4GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX4GCR: DXPDR Position       */
#define DDRPHY_DX4GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX4GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX4GCR: DXPDR Mask           */

#define DDRPHY_DX4GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX4GCR: DQSRPD Position      */
#define DDRPHY_DX4GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX4GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX4GCR: DQSRPD Mask          */

#define DDRPHY_DX4GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX4GCR: DSEN Position        */
#define DDRPHY_DX4GCR_DSEN_Msk           (0x3ul << DDRPHY_DX4GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX4GCR: DSEN Mask            */

#define DDRPHY_DX4GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX4GCR: DQSRTT Position      */
#define DDRPHY_DX4GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX4GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX4GCR: DQSRTT Mask          */

#define DDRPHY_DX4GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX4GCR: DQRTT Position       */
#define DDRPHY_DX4GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX4GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX4GCR: DQRTT Mask           */

#define DDRPHY_DX4GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX4GCR: RTTOH Position       */
#define DDRPHY_DX4GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX4GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX4GCR: RTTOH Mask           */

#define DDRPHY_DX4GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX4GCR: RTTOAL Position      */
#define DDRPHY_DX4GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX4GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX4GCR: RTTOAL Mask          */

#define DDRPHY_DX4GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX4GCR: DXOEO Position       */
#define DDRPHY_DX4GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX4GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX4GCR: DXOEO Mask           */

#define DDRPHY_DX4GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX4GCR: PLLRST Position      */
#define DDRPHY_DX4GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX4GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX4GCR: PLLRST Mask          */

#define DDRPHY_DX4GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX4GCR: PLLPD Position       */
#define DDRPHY_DX4GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX4GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX4GCR: PLLPD Mask           */

#define DDRPHY_DX4GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX4GCR: GSHIFT Position      */
#define DDRPHY_DX4GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX4GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX4GCR: GSHIFT Mask          */

#define DDRPHY_DX4GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX4GCR: PLLBYP Position      */
#define DDRPHY_DX4GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX4GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX4GCR: PLLBYP Mask          */

#define DDRPHY_DX4GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX4GCR: WLRKEN Position      */
#define DDRPHY_DX4GCR_WLRKEN_Msk         (0xful << DDRPHY_DX4GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX4GCR: WLRKEN Mask          */

#define DDRPHY_DX4GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX4GCR: MDLEN Position       */
#define DDRPHY_DX4GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX4GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX4GCR: MDLEN Mask           */

#define DDRPHY_DX4GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX4GCR: CALBYP Position      */
#define DDRPHY_DX4GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX4GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX4GCR: CALBYP Mask          */

#define DDRPHY_DX4GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX4GSR0: WDQCAL Position     */
#define DDRPHY_DX4GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX4GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX4GSR0: WDQCAL Mask         */

#define DDRPHY_DX4GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX4GSR0: RDQSCAL Position    */
#define DDRPHY_DX4GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX4GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX4GSR0: RDQSCAL Mask        */

#define DDRPHY_DX4GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX4GSR0: RDQSNCAL Position   */
#define DDRPHY_DX4GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX4GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX4GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX4GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX4GSR0: GDQSCAL Position    */
#define DDRPHY_DX4GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX4GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX4GSR0: GDQSCAL Mask        */

#define DDRPHY_DX4GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX4GSR0: WLCAL Position      */
#define DDRPHY_DX4GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX4GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX4GSR0: WLCAL Mask          */

#define DDRPHY_DX4GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX4GSR0: WLDONE Position     */
#define DDRPHY_DX4GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX4GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX4GSR0: WLDONE Mask         */

#define DDRPHY_DX4GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX4GSR0: WLERR Position      */
#define DDRPHY_DX4GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX4GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX4GSR0: WLERR Mask          */

#define DDRPHY_DX4GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX4GSR0: WLPRD Position      */
#define DDRPHY_DX4GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX4GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX4GSR0: WLPRD Mask          */

#define DDRPHY_DX4GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX4GSR0: DPLOCK Position     */
#define DDRPHY_DX4GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX4GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX4GSR0: DPLOCK Mask         */

#define DDRPHY_DX4GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX4GSR0: GDQSPRD Position    */
#define DDRPHY_DX4GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX4GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX4GSR0: GDQSPRD Mask        */

#define DDRPHY_DX4GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX4GSR0: QSGERR Position     */
#define DDRPHY_DX4GSR0_QSGERR_Msk        (0xful << DDRPHY_DX4GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX4GSR0: QSGERR Mask         */

#define DDRPHY_DX4GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX4GSR0: WLDQ Position       */
#define DDRPHY_DX4GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX4GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX4GSR0: WLDQ Mask           */

#define DDRPHY_DX4GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX4GSR1: DLTDONE Position    */
#define DDRPHY_DX4GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX4GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX4GSR1: DLTDONE Mask        */

#define DDRPHY_DX4GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX4GSR1: DLTCODE Position    */
#define DDRPHY_DX4GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX4GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX4GSR1: DLTCODE Mask        */

#define DDRPHY_DX4BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX4BDLR0: DQ0WBD Position    */
#define DDRPHY_DX4BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX4BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX4BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX4BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX4BDLR0: DQ1WBD Position    */
#define DDRPHY_DX4BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX4BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX4BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX4BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX4BDLR0: DQ2WBD Position    */
#define DDRPHY_DX4BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX4BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX4BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX4BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX4BDLR0: DQ3WBD Position    */
#define DDRPHY_DX4BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX4BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX4BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX4BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX4BDLR0: DQ4WBD Position    */
#define DDRPHY_DX4BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX4BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX4BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX4BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX4BDLR1: DQ5WBD Position    */
#define DDRPHY_DX4BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX4BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX4BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX4BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX4BDLR1: DQ6WBD Position    */
#define DDRPHY_DX4BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX4BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX4BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX4BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX4BDLR1: DQ7WBD Position    */
#define DDRPHY_DX4BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX4BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX4BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX4BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX4BDLR1: DMWBD Position     */
#define DDRPHY_DX4BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX4BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX4BDLR1: DMWBD Mask         */

#define DDRPHY_DX4BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX4BDLR1: DSWBD Position     */
#define DDRPHY_DX4BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX4BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX4BDLR1: DSWBD Mask         */

#define DDRPHY_DX4BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX4BDLR2: DSOEBD Position    */
#define DDRPHY_DX4BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX4BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX4BDLR2: DSOEBD Mask        */

#define DDRPHY_DX4BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX4BDLR2: DQOEBD Position    */
#define DDRPHY_DX4BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX4BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX4BDLR2: DQOEBD Mask        */

#define DDRPHY_DX4BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX4BDLR2: DSRBD Position     */
#define DDRPHY_DX4BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX4BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX4BDLR2: DSRBD Mask         */

#define DDRPHY_DX4BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX4BDLR2: DSNRBD Position    */
#define DDRPHY_DX4BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX4BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX4BDLR2: DSNRBD Mask        */

#define DDRPHY_DX4BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX4BDLR3: DQ0RBD Position    */
#define DDRPHY_DX4BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX4BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX4BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX4BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX4BDLR3: DQ1RBD Position    */
#define DDRPHY_DX4BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX4BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX4BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX4BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX4BDLR3: DQ2RBD Position    */
#define DDRPHY_DX4BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX4BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX4BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX4BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX4BDLR3: DQ3RBD Position    */
#define DDRPHY_DX4BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX4BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX4BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX4BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX4BDLR3: DQ4RBD Position    */
#define DDRPHY_DX4BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX4BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX4BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX4BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX4BDLR4: DQ5RBD Position    */
#define DDRPHY_DX4BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX4BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX4BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX4BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX4BDLR4: DQ6RBD Position    */
#define DDRPHY_DX4BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX4BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX4BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX4BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX4BDLR4: DQ7RBD Position    */
#define DDRPHY_DX4BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX4BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX4BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX4BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX4BDLR4: DMRBD Position     */
#define DDRPHY_DX4BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX4BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX4BDLR4: DMRBD Mask         */

#define DDRPHY_DX4LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX4LCDLR0: R0WLD Position    */
#define DDRPHY_DX4LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX4LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX4LCDLR0: R0WLD Mask        */

#define DDRPHY_DX4LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX4LCDLR0: R1WLD Position    */
#define DDRPHY_DX4LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX4LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX4LCDLR0: R1WLD Mask        */

#define DDRPHY_DX4LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX4LCDLR0: R2WLD Position    */
#define DDRPHY_DX4LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX4LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX4LCDLR0: R2WLD Mask        */

#define DDRPHY_DX4LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX4LCDLR0: R3WLD Position    */
#define DDRPHY_DX4LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX4LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX4LCDLR0: R3WLD Mask        */

#define DDRPHY_DX4LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX4LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX4LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX4LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX4LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX4LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX4LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX4LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX4LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX4LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX4LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX4LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX4LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX4LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX4LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX4LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX4LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX4LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX4LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX4LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX4MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX4MDLR: IPRD Position       */
#define DDRPHY_DX4MDLR_IPRD_Msk          (0xfful << DDRPHY_DX4MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX4MDLR: IPRD Mask           */

#define DDRPHY_DX4MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX4MDLR: TPRD Position       */
#define DDRPHY_DX4MDLR_TPRD_Msk          (0xfful << DDRPHY_DX4MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX4MDLR: TPRD Mask           */

#define DDRPHY_DX4MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX4MDLR: MDLD Position       */
#define DDRPHY_DX4MDLR_MDLD_Msk          (0xfful << DDRPHY_DX4MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX4MDLR: MDLD Mask           */

#define DDRPHY_DX4GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX4GTR: R0DGSL Position      */
#define DDRPHY_DX4GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX4GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX4GTR: R0DGSL Mask          */

#define DDRPHY_DX4GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX4GTR: R1DGSL Position      */
#define DDRPHY_DX4GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX4GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX4GTR: R1DGSL Mask          */

#define DDRPHY_DX4GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX4GTR: R2DGSL Position      */
#define DDRPHY_DX4GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX4GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX4GTR: R2DGSL Mask          */

#define DDRPHY_DX4GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX4GTR: R3DGSL Position      */
#define DDRPHY_DX4GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX4GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX4GTR: R3DGSL Mask          */

#define DDRPHY_DX4GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX4GTR: R0WLSL Position      */
#define DDRPHY_DX4GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX4GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX4GTR: R0WLSL Mask          */

#define DDRPHY_DX4GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX4GTR: R1WLSL Position      */
#define DDRPHY_DX4GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX4GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX4GTR: R1WLSL Mask          */

#define DDRPHY_DX4GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX4GTR: R2WLSL Position      */
#define DDRPHY_DX4GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX4GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX4GTR: R2WLSL Mask          */

#define DDRPHY_DX4GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX4GTR: R3WLSL Position      */
#define DDRPHY_DX4GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX4GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX4GTR: R3WLSL Mask          */

#define DDRPHY_DX4GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX4GSR2: RDERR Position      */
#define DDRPHY_DX4GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX4GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX4GSR2: RDERR Mask          */

#define DDRPHY_DX4GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX4GSR2: RDWN Position       */
#define DDRPHY_DX4GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX4GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX4GSR2: RDWN Mask           */

#define DDRPHY_DX4GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX4GSR2: WDERR Position      */
#define DDRPHY_DX4GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX4GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX4GSR2: WDERR Mask          */

#define DDRPHY_DX4GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX4GSR2: WDWN Position       */
#define DDRPHY_DX4GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX4GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX4GSR2: WDWN Mask           */

#define DDRPHY_DX4GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX4GSR2: REERR Position      */
#define DDRPHY_DX4GSR2_REERR_Msk         (0x1ul << DDRPHY_DX4GSR2_REERR_Pos)               /*!< DDRPHY_T::DX4GSR2: REERR Mask          */

#define DDRPHY_DX4GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX4GSR2: REWN Position       */
#define DDRPHY_DX4GSR2_REWN_Msk          (0x1ul << DDRPHY_DX4GSR2_REWN_Pos)                /*!< DDRPHY_T::DX4GSR2: REWN Mask           */

#define DDRPHY_DX4GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX4GSR2: WEERR Position      */
#define DDRPHY_DX4GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX4GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX4GSR2: WEERR Mask          */

#define DDRPHY_DX4GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX4GSR2: WEWN Position       */
#define DDRPHY_DX4GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX4GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX4GSR2: WEWN Mask           */

#define DDRPHY_DX4GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX4GSR2: ESTAT Position      */
#define DDRPHY_DX4GSR2_ESTAT_Msk         (0xful << DDRPHY_DX4GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX4GSR2: ESTAT Mask          */

#define DDRPHY_DX5GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX5GCR: DXEN Position        */
#define DDRPHY_DX5GCR_DXEN_Msk           (0x1ul << DDRPHY_DX5GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX5GCR: DXEN Mask            */

#define DDRPHY_DX5GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX5GCR: DQSODT Position      */
#define DDRPHY_DX5GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX5GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX5GCR: DQSODT Mask          */

#define DDRPHY_DX5GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX5GCR: DQODT Position       */
#define DDRPHY_DX5GCR_DQODT_Msk          (0x1ul << DDRPHY_DX5GCR_DQODT_Pos)                /*!< DDRPHY_T::DX5GCR: DQODT Mask           */

#define DDRPHY_DX5GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX5GCR: DXIOM Position       */
#define DDRPHY_DX5GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX5GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX5GCR: DXIOM Mask           */

#define DDRPHY_DX5GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX5GCR: DXPDD Position       */
#define DDRPHY_DX5GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX5GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX5GCR: DXPDD Mask           */

#define DDRPHY_DX5GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX5GCR: DXPDR Position       */
#define DDRPHY_DX5GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX5GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX5GCR: DXPDR Mask           */

#define DDRPHY_DX5GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX5GCR: DQSRPD Position      */
#define DDRPHY_DX5GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX5GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX5GCR: DQSRPD Mask          */

#define DDRPHY_DX5GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX5GCR: DSEN Position        */
#define DDRPHY_DX5GCR_DSEN_Msk           (0x3ul << DDRPHY_DX5GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX5GCR: DSEN Mask            */

#define DDRPHY_DX5GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX5GCR: DQSRTT Position      */
#define DDRPHY_DX5GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX5GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX5GCR: DQSRTT Mask          */

#define DDRPHY_DX5GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX5GCR: DQRTT Position       */
#define DDRPHY_DX5GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX5GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX5GCR: DQRTT Mask           */

#define DDRPHY_DX5GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX5GCR: RTTOH Position       */
#define DDRPHY_DX5GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX5GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX5GCR: RTTOH Mask           */

#define DDRPHY_DX5GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX5GCR: RTTOAL Position      */
#define DDRPHY_DX5GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX5GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX5GCR: RTTOAL Mask          */

#define DDRPHY_DX5GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX5GCR: DXOEO Position       */
#define DDRPHY_DX5GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX5GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX5GCR: DXOEO Mask           */

#define DDRPHY_DX5GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX5GCR: PLLRST Position      */
#define DDRPHY_DX5GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX5GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX5GCR: PLLRST Mask          */

#define DDRPHY_DX5GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX5GCR: PLLPD Position       */
#define DDRPHY_DX5GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX5GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX5GCR: PLLPD Mask           */

#define DDRPHY_DX5GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX5GCR: GSHIFT Position      */
#define DDRPHY_DX5GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX5GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX5GCR: GSHIFT Mask          */

#define DDRPHY_DX5GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX5GCR: PLLBYP Position      */
#define DDRPHY_DX5GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX5GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX5GCR: PLLBYP Mask          */

#define DDRPHY_DX5GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX5GCR: WLRKEN Position      */
#define DDRPHY_DX5GCR_WLRKEN_Msk         (0xful << DDRPHY_DX5GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX5GCR: WLRKEN Mask          */

#define DDRPHY_DX5GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX5GCR: MDLEN Position       */
#define DDRPHY_DX5GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX5GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX5GCR: MDLEN Mask           */

#define DDRPHY_DX5GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX5GCR: CALBYP Position      */
#define DDRPHY_DX5GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX5GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX5GCR: CALBYP Mask          */

#define DDRPHY_DX5GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX5GSR0: WDQCAL Position     */
#define DDRPHY_DX5GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX5GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX5GSR0: WDQCAL Mask         */

#define DDRPHY_DX5GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX5GSR0: RDQSCAL Position    */
#define DDRPHY_DX5GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX5GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX5GSR0: RDQSCAL Mask        */

#define DDRPHY_DX5GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX5GSR0: RDQSNCAL Position   */
#define DDRPHY_DX5GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX5GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX5GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX5GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX5GSR0: GDQSCAL Position    */
#define DDRPHY_DX5GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX5GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX5GSR0: GDQSCAL Mask        */

#define DDRPHY_DX5GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX5GSR0: WLCAL Position      */
#define DDRPHY_DX5GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX5GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX5GSR0: WLCAL Mask          */

#define DDRPHY_DX5GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX5GSR0: WLDONE Position     */
#define DDRPHY_DX5GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX5GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX5GSR0: WLDONE Mask         */

#define DDRPHY_DX5GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX5GSR0: WLERR Position      */
#define DDRPHY_DX5GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX5GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX5GSR0: WLERR Mask          */

#define DDRPHY_DX5GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX5GSR0: WLPRD Position      */
#define DDRPHY_DX5GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX5GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX5GSR0: WLPRD Mask          */

#define DDRPHY_DX5GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX5GSR0: DPLOCK Position     */
#define DDRPHY_DX5GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX5GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX5GSR0: DPLOCK Mask         */

#define DDRPHY_DX5GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX5GSR0: GDQSPRD Position    */
#define DDRPHY_DX5GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX5GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX5GSR0: GDQSPRD Mask        */

#define DDRPHY_DX5GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX5GSR0: QSGERR Position     */
#define DDRPHY_DX5GSR0_QSGERR_Msk        (0xful << DDRPHY_DX5GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX5GSR0: QSGERR Mask         */

#define DDRPHY_DX5GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX5GSR0: WLDQ Position       */
#define DDRPHY_DX5GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX5GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX5GSR0: WLDQ Mask           */

#define DDRPHY_DX5GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX5GSR1: DLTDONE Position    */
#define DDRPHY_DX5GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX5GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX5GSR1: DLTDONE Mask        */

#define DDRPHY_DX5GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX5GSR1: DLTCODE Position    */
#define DDRPHY_DX5GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX5GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX5GSR1: DLTCODE Mask        */

#define DDRPHY_DX5BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX5BDLR0: DQ0WBD Position    */
#define DDRPHY_DX5BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX5BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX5BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX5BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX5BDLR0: DQ1WBD Position    */
#define DDRPHY_DX5BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX5BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX5BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX5BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX5BDLR0: DQ2WBD Position    */
#define DDRPHY_DX5BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX5BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX5BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX5BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX5BDLR0: DQ3WBD Position    */
#define DDRPHY_DX5BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX5BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX5BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX5BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX5BDLR0: DQ4WBD Position    */
#define DDRPHY_DX5BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX5BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX5BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX5BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX5BDLR1: DQ5WBD Position    */
#define DDRPHY_DX5BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX5BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX5BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX5BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX5BDLR1: DQ6WBD Position    */
#define DDRPHY_DX5BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX5BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX5BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX5BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX5BDLR1: DQ7WBD Position    */
#define DDRPHY_DX5BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX5BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX5BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX5BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX5BDLR1: DMWBD Position     */
#define DDRPHY_DX5BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX5BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX5BDLR1: DMWBD Mask         */

#define DDRPHY_DX5BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX5BDLR1: DSWBD Position     */
#define DDRPHY_DX5BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX5BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX5BDLR1: DSWBD Mask         */

#define DDRPHY_DX5BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX5BDLR2: DSOEBD Position    */
#define DDRPHY_DX5BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX5BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX5BDLR2: DSOEBD Mask        */

#define DDRPHY_DX5BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX5BDLR2: DQOEBD Position    */
#define DDRPHY_DX5BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX5BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX5BDLR2: DQOEBD Mask        */

#define DDRPHY_DX5BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX5BDLR2: DSRBD Position     */
#define DDRPHY_DX5BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX5BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX5BDLR2: DSRBD Mask         */

#define DDRPHY_DX5BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX5BDLR2: DSNRBD Position    */
#define DDRPHY_DX5BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX5BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX5BDLR2: DSNRBD Mask        */

#define DDRPHY_DX5BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX5BDLR3: DQ0RBD Position    */
#define DDRPHY_DX5BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX5BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX5BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX5BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX5BDLR3: DQ1RBD Position    */
#define DDRPHY_DX5BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX5BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX5BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX5BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX5BDLR3: DQ2RBD Position    */
#define DDRPHY_DX5BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX5BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX5BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX5BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX5BDLR3: DQ3RBD Position    */
#define DDRPHY_DX5BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX5BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX5BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX5BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX5BDLR3: DQ4RBD Position    */
#define DDRPHY_DX5BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX5BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX5BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX5BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX5BDLR4: DQ5RBD Position    */
#define DDRPHY_DX5BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX5BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX5BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX5BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX5BDLR4: DQ6RBD Position    */
#define DDRPHY_DX5BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX5BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX5BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX5BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX5BDLR4: DQ7RBD Position    */
#define DDRPHY_DX5BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX5BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX5BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX5BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX5BDLR4: DMRBD Position     */
#define DDRPHY_DX5BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX5BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX5BDLR4: DMRBD Mask         */

#define DDRPHY_DX5LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX5LCDLR0: R0WLD Position    */
#define DDRPHY_DX5LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX5LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX5LCDLR0: R0WLD Mask        */

#define DDRPHY_DX5LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX5LCDLR0: R1WLD Position    */
#define DDRPHY_DX5LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX5LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX5LCDLR0: R1WLD Mask        */

#define DDRPHY_DX5LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX5LCDLR0: R2WLD Position    */
#define DDRPHY_DX5LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX5LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX5LCDLR0: R2WLD Mask        */

#define DDRPHY_DX5LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX5LCDLR0: R3WLD Position    */
#define DDRPHY_DX5LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX5LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX5LCDLR0: R3WLD Mask        */

#define DDRPHY_DX5LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX5LCDLR1: WDQD Position     */
#define DDRPHY_DX5LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX5LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX5LCDLR1: WDQD Mask         */

#define DDRPHY_DX5LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX5LCDLR1: RDQSD Position    */
#define DDRPHY_DX5LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX5LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX5LCDLR1: RDQSD Mask        */

#define DDRPHY_DX5LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX5LCDLR1: RDQSND Position   */
#define DDRPHY_DX5LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX5LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX5LCDLR1: RDQSND Mask       */

#define DDRPHY_DX5LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX5LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX5LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX5LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX5LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX5LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX5LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX5LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX5LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX5LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX5LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX5LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX5LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX5LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX5LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX5LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX5LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX5LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX5LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX5LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX5MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX5MDLR: IPRD Position       */
#define DDRPHY_DX5MDLR_IPRD_Msk          (0xfful << DDRPHY_DX5MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX5MDLR: IPRD Mask           */

#define DDRPHY_DX5MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX5MDLR: TPRD Position       */
#define DDRPHY_DX5MDLR_TPRD_Msk          (0xfful << DDRPHY_DX5MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX5MDLR: TPRD Mask           */

#define DDRPHY_DX5MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX5MDLR: MDLD Position       */
#define DDRPHY_DX5MDLR_MDLD_Msk          (0xfful << DDRPHY_DX5MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX5MDLR: MDLD Mask           */

#define DDRPHY_DX5GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX5GTR: R0DGSL Position      */
#define DDRPHY_DX5GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX5GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX5GTR: R0DGSL Mask          */

#define DDRPHY_DX5GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX5GTR: R1DGSL Position      */
#define DDRPHY_DX5GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX5GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX5GTR: R1DGSL Mask          */

#define DDRPHY_DX5GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX5GTR: R2DGSL Position      */
#define DDRPHY_DX5GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX5GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX5GTR: R2DGSL Mask          */

#define DDRPHY_DX5GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX5GTR: R3DGSL Position      */
#define DDRPHY_DX5GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX5GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX5GTR: R3DGSL Mask          */

#define DDRPHY_DX5GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX5GTR: R0WLSL Position      */
#define DDRPHY_DX5GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX5GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX5GTR: R0WLSL Mask          */

#define DDRPHY_DX5GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX5GTR: R1WLSL Position      */
#define DDRPHY_DX5GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX5GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX5GTR: R1WLSL Mask          */

#define DDRPHY_DX5GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX5GTR: R2WLSL Position      */
#define DDRPHY_DX5GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX5GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX5GTR: R2WLSL Mask          */

#define DDRPHY_DX5GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX5GTR: R3WLSL Position      */
#define DDRPHY_DX5GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX5GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX5GTR: R3WLSL Mask          */

#define DDRPHY_DX5GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX5GSR2: RDERR Position      */
#define DDRPHY_DX5GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX5GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX5GSR2: RDERR Mask          */

#define DDRPHY_DX5GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX5GSR2: RDWN Position       */
#define DDRPHY_DX5GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX5GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX5GSR2: RDWN Mask           */

#define DDRPHY_DX5GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX5GSR2: WDERR Position      */
#define DDRPHY_DX5GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX5GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX5GSR2: WDERR Mask          */

#define DDRPHY_DX5GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX5GSR2: WDWN Position       */
#define DDRPHY_DX5GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX5GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX5GSR2: WDWN Mask           */

#define DDRPHY_DX5GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX5GSR2: REERR Position      */
#define DDRPHY_DX5GSR2_REERR_Msk         (0x1ul << DDRPHY_DX5GSR2_REERR_Pos)               /*!< DDRPHY_T::DX5GSR2: REERR Mask          */

#define DDRPHY_DX5GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX5GSR2: REWN Position       */
#define DDRPHY_DX5GSR2_REWN_Msk          (0x1ul << DDRPHY_DX5GSR2_REWN_Pos)                /*!< DDRPHY_T::DX5GSR2: REWN Mask           */

#define DDRPHY_DX5GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX5GSR2: WEERR Position      */
#define DDRPHY_DX5GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX5GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX5GSR2: WEERR Mask          */

#define DDRPHY_DX5GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX5GSR2: WEWN Position       */
#define DDRPHY_DX5GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX5GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX5GSR2: WEWN Mask           */

#define DDRPHY_DX5GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX5GSR2: ESTAT Position      */
#define DDRPHY_DX5GSR2_ESTAT_Msk         (0xful << DDRPHY_DX5GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX5GSR2: ESTAT Mask          */

#define DDRPHY_DX6GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX6GCR: DXEN Position        */
#define DDRPHY_DX6GCR_DXEN_Msk           (0x1ul << DDRPHY_DX6GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX6GCR: DXEN Mask            */

#define DDRPHY_DX6GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX6GCR: DQSODT Position      */
#define DDRPHY_DX6GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX6GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX6GCR: DQSODT Mask          */

#define DDRPHY_DX6GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX6GCR: DQODT Position       */
#define DDRPHY_DX6GCR_DQODT_Msk          (0x1ul << DDRPHY_DX6GCR_DQODT_Pos)                /*!< DDRPHY_T::DX6GCR: DQODT Mask           */

#define DDRPHY_DX6GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX6GCR: DXIOM Position       */
#define DDRPHY_DX6GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX6GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX6GCR: DXIOM Mask           */

#define DDRPHY_DX6GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX6GCR: DXPDD Position       */
#define DDRPHY_DX6GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX6GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX6GCR: DXPDD Mask           */

#define DDRPHY_DX6GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX6GCR: DXPDR Position       */
#define DDRPHY_DX6GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX6GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX6GCR: DXPDR Mask           */

#define DDRPHY_DX6GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX6GCR: DQSRPD Position      */
#define DDRPHY_DX6GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX6GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX6GCR: DQSRPD Mask          */

#define DDRPHY_DX6GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX6GCR: DSEN Position        */
#define DDRPHY_DX6GCR_DSEN_Msk           (0x3ul << DDRPHY_DX6GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX6GCR: DSEN Mask            */

#define DDRPHY_DX6GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX6GCR: DQSRTT Position      */
#define DDRPHY_DX6GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX6GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX6GCR: DQSRTT Mask          */

#define DDRPHY_DX6GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX6GCR: DQRTT Position       */
#define DDRPHY_DX6GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX6GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX6GCR: DQRTT Mask           */

#define DDRPHY_DX6GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX6GCR: RTTOH Position       */
#define DDRPHY_DX6GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX6GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX6GCR: RTTOH Mask           */

#define DDRPHY_DX6GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX6GCR: RTTOAL Position      */
#define DDRPHY_DX6GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX6GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX6GCR: RTTOAL Mask          */

#define DDRPHY_DX6GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX6GCR: DXOEO Position       */
#define DDRPHY_DX6GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX6GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX6GCR: DXOEO Mask           */

#define DDRPHY_DX6GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX6GCR: PLLRST Position      */
#define DDRPHY_DX6GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX6GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX6GCR: PLLRST Mask          */

#define DDRPHY_DX6GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX6GCR: PLLPD Position       */
#define DDRPHY_DX6GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX6GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX6GCR: PLLPD Mask           */

#define DDRPHY_DX6GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX6GCR: GSHIFT Position      */
#define DDRPHY_DX6GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX6GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX6GCR: GSHIFT Mask          */

#define DDRPHY_DX6GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX6GCR: PLLBYP Position      */
#define DDRPHY_DX6GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX6GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX6GCR: PLLBYP Mask          */

#define DDRPHY_DX6GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX6GCR: WLRKEN Position      */
#define DDRPHY_DX6GCR_WLRKEN_Msk         (0xful << DDRPHY_DX6GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX6GCR: WLRKEN Mask          */

#define DDRPHY_DX6GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX6GCR: MDLEN Position       */
#define DDRPHY_DX6GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX6GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX6GCR: MDLEN Mask           */

#define DDRPHY_DX6GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX6GCR: CALBYP Position      */
#define DDRPHY_DX6GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX6GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX6GCR: CALBYP Mask          */

#define DDRPHY_DX6GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX6GSR0: WDQCAL Position     */
#define DDRPHY_DX6GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX6GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX6GSR0: WDQCAL Mask         */

#define DDRPHY_DX6GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX6GSR0: RDQSCAL Position    */
#define DDRPHY_DX6GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX6GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX6GSR0: RDQSCAL Mask        */

#define DDRPHY_DX6GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX6GSR0: RDQSNCAL Position   */
#define DDRPHY_DX6GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX6GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX6GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX6GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX6GSR0: GDQSCAL Position    */
#define DDRPHY_DX6GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX6GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX6GSR0: GDQSCAL Mask        */

#define DDRPHY_DX6GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX6GSR0: WLCAL Position      */
#define DDRPHY_DX6GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX6GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX6GSR0: WLCAL Mask          */

#define DDRPHY_DX6GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX6GSR0: WLDONE Position     */
#define DDRPHY_DX6GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX6GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX6GSR0: WLDONE Mask         */

#define DDRPHY_DX6GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX6GSR0: WLERR Position      */
#define DDRPHY_DX6GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX6GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX6GSR0: WLERR Mask          */

#define DDRPHY_DX6GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX6GSR0: WLPRD Position      */
#define DDRPHY_DX6GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX6GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX6GSR0: WLPRD Mask          */

#define DDRPHY_DX6GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX6GSR0: DPLOCK Position     */
#define DDRPHY_DX6GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX6GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX6GSR0: DPLOCK Mask         */

#define DDRPHY_DX6GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX6GSR0: GDQSPRD Position    */
#define DDRPHY_DX6GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX6GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX6GSR0: GDQSPRD Mask        */

#define DDRPHY_DX6GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX6GSR0: QSGERR Position     */
#define DDRPHY_DX6GSR0_QSGERR_Msk        (0xful << DDRPHY_DX6GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX6GSR0: QSGERR Mask         */

#define DDRPHY_DX6GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX6GSR0: WLDQ Position       */
#define DDRPHY_DX6GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX6GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX6GSR0: WLDQ Mask           */

#define DDRPHY_DX6GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX6GSR1: DLTDONE Position    */
#define DDRPHY_DX6GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX6GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX6GSR1: DLTDONE Mask        */

#define DDRPHY_DX6GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX6GSR1: DLTCODE Position    */
#define DDRPHY_DX6GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX6GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX6GSR1: DLTCODE Mask        */

#define DDRPHY_DX6BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX6BDLR0: DQ0WBD Position    */
#define DDRPHY_DX6BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX6BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX6BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX6BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX6BDLR0: DQ1WBD Position    */
#define DDRPHY_DX6BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX6BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX6BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX6BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX6BDLR0: DQ2WBD Position    */
#define DDRPHY_DX6BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX6BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX6BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX6BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX6BDLR0: DQ3WBD Position    */
#define DDRPHY_DX6BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX6BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX6BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX6BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX6BDLR0: DQ4WBD Position    */
#define DDRPHY_DX6BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX6BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX6BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX6BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX6BDLR1: DQ5WBD Position    */
#define DDRPHY_DX6BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX6BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX6BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX6BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX6BDLR1: DQ6WBD Position    */
#define DDRPHY_DX6BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX6BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX6BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX6BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX6BDLR1: DQ7WBD Position    */
#define DDRPHY_DX6BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX6BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX6BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX6BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX6BDLR1: DMWBD Position     */
#define DDRPHY_DX6BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX6BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX6BDLR1: DMWBD Mask         */

#define DDRPHY_DX6BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX6BDLR1: DSWBD Position     */
#define DDRPHY_DX6BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX6BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX6BDLR1: DSWBD Mask         */

#define DDRPHY_DX6BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX6BDLR2: DSOEBD Position    */
#define DDRPHY_DX6BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX6BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX6BDLR2: DSOEBD Mask        */

#define DDRPHY_DX6BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX6BDLR2: DQOEBD Position    */
#define DDRPHY_DX6BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX6BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX6BDLR2: DQOEBD Mask        */

#define DDRPHY_DX6BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX6BDLR2: DSRBD Position     */
#define DDRPHY_DX6BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX6BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX6BDLR2: DSRBD Mask         */

#define DDRPHY_DX6BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX6BDLR2: DSNRBD Position    */
#define DDRPHY_DX6BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX6BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX6BDLR2: DSNRBD Mask        */

#define DDRPHY_DX6BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX6BDLR3: DQ0RBD Position    */
#define DDRPHY_DX6BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX6BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX6BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX6BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX6BDLR3: DQ1RBD Position    */
#define DDRPHY_DX6BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX6BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX6BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX6BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX6BDLR3: DQ2RBD Position    */
#define DDRPHY_DX6BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX6BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX6BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX6BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX6BDLR3: DQ3RBD Position    */
#define DDRPHY_DX6BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX6BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX6BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX6BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX6BDLR3: DQ4RBD Position    */
#define DDRPHY_DX6BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX6BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX6BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX6BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX6BDLR4: DQ5RBD Position    */
#define DDRPHY_DX6BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX6BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX6BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX6BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX6BDLR4: DQ6RBD Position    */
#define DDRPHY_DX6BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX6BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX6BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX6BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX6BDLR4: DQ7RBD Position    */
#define DDRPHY_DX6BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX6BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX6BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX6BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX6BDLR4: DMRBD Position     */
#define DDRPHY_DX6BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX6BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX6BDLR4: DMRBD Mask         */

#define DDRPHY_DX6LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX6LCDLR0: R0WLD Position    */
#define DDRPHY_DX6LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX6LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX6LCDLR0: R0WLD Mask        */

#define DDRPHY_DX6LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX6LCDLR0: R1WLD Position    */
#define DDRPHY_DX6LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX6LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX6LCDLR0: R1WLD Mask        */

#define DDRPHY_DX6LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX6LCDLR0: R2WLD Position    */
#define DDRPHY_DX6LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX6LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX6LCDLR0: R2WLD Mask        */

#define DDRPHY_DX6LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX6LCDLR0: R3WLD Position    */
#define DDRPHY_DX6LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX6LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX6LCDLR0: R3WLD Mask        */

#define DDRPHY_DX6LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX6LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX6LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX6LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX6LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX6LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX6LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX6LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX6LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX6LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX6LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX6LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX6LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX6LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX6LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX6LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX6LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX6LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX6LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX6LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX6MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX6MDLR: IPRD Position       */
#define DDRPHY_DX6MDLR_IPRD_Msk          (0xfful << DDRPHY_DX6MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX6MDLR: IPRD Mask           */

#define DDRPHY_DX6MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX6MDLR: TPRD Position       */
#define DDRPHY_DX6MDLR_TPRD_Msk          (0xfful << DDRPHY_DX6MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX6MDLR: TPRD Mask           */

#define DDRPHY_DX6MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX6MDLR: MDLD Position       */
#define DDRPHY_DX6MDLR_MDLD_Msk          (0xfful << DDRPHY_DX6MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX6MDLR: MDLD Mask           */

#define DDRPHY_DX6GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX6GTR: R0DGSL Position      */
#define DDRPHY_DX6GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX6GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX6GTR: R0DGSL Mask          */

#define DDRPHY_DX6GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX6GTR: R1DGSL Position      */
#define DDRPHY_DX6GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX6GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX6GTR: R1DGSL Mask          */

#define DDRPHY_DX6GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX6GTR: R2DGSL Position      */
#define DDRPHY_DX6GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX6GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX6GTR: R2DGSL Mask          */

#define DDRPHY_DX6GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX6GTR: R3DGSL Position      */
#define DDRPHY_DX6GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX6GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX6GTR: R3DGSL Mask          */

#define DDRPHY_DX6GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX6GTR: R0WLSL Position      */
#define DDRPHY_DX6GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX6GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX6GTR: R0WLSL Mask          */

#define DDRPHY_DX6GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX6GTR: R1WLSL Position      */
#define DDRPHY_DX6GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX6GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX6GTR: R1WLSL Mask          */

#define DDRPHY_DX6GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX6GTR: R2WLSL Position      */
#define DDRPHY_DX6GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX6GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX6GTR: R2WLSL Mask          */

#define DDRPHY_DX6GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX6GTR: R3WLSL Position      */
#define DDRPHY_DX6GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX6GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX6GTR: R3WLSL Mask          */

#define DDRPHY_DX6GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX6GSR2: RDERR Position      */
#define DDRPHY_DX6GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX6GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX6GSR2: RDERR Mask          */

#define DDRPHY_DX6GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX6GSR2: RDWN Position       */
#define DDRPHY_DX6GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX6GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX6GSR2: RDWN Mask           */

#define DDRPHY_DX6GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX6GSR2: WDERR Position      */
#define DDRPHY_DX6GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX6GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX6GSR2: WDERR Mask          */

#define DDRPHY_DX6GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX6GSR2: WDWN Position       */
#define DDRPHY_DX6GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX6GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX6GSR2: WDWN Mask           */

#define DDRPHY_DX6GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX6GSR2: REERR Position      */
#define DDRPHY_DX6GSR2_REERR_Msk         (0x1ul << DDRPHY_DX6GSR2_REERR_Pos)               /*!< DDRPHY_T::DX6GSR2: REERR Mask          */

#define DDRPHY_DX6GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX6GSR2: REWN Position       */
#define DDRPHY_DX6GSR2_REWN_Msk          (0x1ul << DDRPHY_DX6GSR2_REWN_Pos)                /*!< DDRPHY_T::DX6GSR2: REWN Mask           */

#define DDRPHY_DX6GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX6GSR2: WEERR Position      */
#define DDRPHY_DX6GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX6GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX6GSR2: WEERR Mask          */

#define DDRPHY_DX6GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX6GSR2: WEWN Position       */
#define DDRPHY_DX6GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX6GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX6GSR2: WEWN Mask           */

#define DDRPHY_DX6GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX6GSR2: ESTAT Position      */
#define DDRPHY_DX6GSR2_ESTAT_Msk         (0xful << DDRPHY_DX6GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX6GSR2: ESTAT Mask          */

#define DDRPHY_DX7GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX7GCR: DXEN Position        */
#define DDRPHY_DX7GCR_DXEN_Msk           (0x1ul << DDRPHY_DX7GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX7GCR: DXEN Mask            */

#define DDRPHY_DX7GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX7GCR: DQSODT Position      */
#define DDRPHY_DX7GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX7GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX7GCR: DQSODT Mask          */

#define DDRPHY_DX7GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX7GCR: DQODT Position       */
#define DDRPHY_DX7GCR_DQODT_Msk          (0x1ul << DDRPHY_DX7GCR_DQODT_Pos)                /*!< DDRPHY_T::DX7GCR: DQODT Mask           */

#define DDRPHY_DX7GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX7GCR: DXIOM Position       */
#define DDRPHY_DX7GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX7GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX7GCR: DXIOM Mask           */

#define DDRPHY_DX7GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX7GCR: DXPDD Position       */
#define DDRPHY_DX7GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX7GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX7GCR: DXPDD Mask           */

#define DDRPHY_DX7GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX7GCR: DXPDR Position       */
#define DDRPHY_DX7GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX7GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX7GCR: DXPDR Mask           */

#define DDRPHY_DX7GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX7GCR: DQSRPD Position      */
#define DDRPHY_DX7GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX7GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX7GCR: DQSRPD Mask          */

#define DDRPHY_DX7GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX7GCR: DSEN Position        */
#define DDRPHY_DX7GCR_DSEN_Msk           (0x3ul << DDRPHY_DX7GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX7GCR: DSEN Mask            */

#define DDRPHY_DX7GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX7GCR: DQSRTT Position      */
#define DDRPHY_DX7GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX7GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX7GCR: DQSRTT Mask          */

#define DDRPHY_DX7GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX7GCR: DQRTT Position       */
#define DDRPHY_DX7GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX7GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX7GCR: DQRTT Mask           */

#define DDRPHY_DX7GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX7GCR: RTTOH Position       */
#define DDRPHY_DX7GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX7GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX7GCR: RTTOH Mask           */

#define DDRPHY_DX7GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX7GCR: RTTOAL Position      */
#define DDRPHY_DX7GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX7GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX7GCR: RTTOAL Mask          */

#define DDRPHY_DX7GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX7GCR: DXOEO Position       */
#define DDRPHY_DX7GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX7GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX7GCR: DXOEO Mask           */

#define DDRPHY_DX7GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX7GCR: PLLRST Position      */
#define DDRPHY_DX7GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX7GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX7GCR: PLLRST Mask          */

#define DDRPHY_DX7GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX7GCR: PLLPD Position       */
#define DDRPHY_DX7GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX7GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX7GCR: PLLPD Mask           */

#define DDRPHY_DX7GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX7GCR: GSHIFT Position      */
#define DDRPHY_DX7GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX7GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX7GCR: GSHIFT Mask          */

#define DDRPHY_DX7GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX7GCR: PLLBYP Position      */
#define DDRPHY_DX7GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX7GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX7GCR: PLLBYP Mask          */

#define DDRPHY_DX7GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX7GCR: WLRKEN Position      */
#define DDRPHY_DX7GCR_WLRKEN_Msk         (0xful << DDRPHY_DX7GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX7GCR: WLRKEN Mask          */

#define DDRPHY_DX7GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX7GCR: MDLEN Position       */
#define DDRPHY_DX7GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX7GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX7GCR: MDLEN Mask           */

#define DDRPHY_DX7GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX7GCR: CALBYP Position      */
#define DDRPHY_DX7GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX7GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX7GCR: CALBYP Mask          */

#define DDRPHY_DX7GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX7GSR0: WDQCAL Position     */
#define DDRPHY_DX7GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX7GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX7GSR0: WDQCAL Mask         */

#define DDRPHY_DX7GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX7GSR0: RDQSCAL Position    */
#define DDRPHY_DX7GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX7GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX7GSR0: RDQSCAL Mask        */

#define DDRPHY_DX7GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX7GSR0: RDQSNCAL Position   */
#define DDRPHY_DX7GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX7GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX7GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX7GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX7GSR0: GDQSCAL Position    */
#define DDRPHY_DX7GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX7GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX7GSR0: GDQSCAL Mask        */

#define DDRPHY_DX7GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX7GSR0: WLCAL Position      */
#define DDRPHY_DX7GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX7GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX7GSR0: WLCAL Mask          */

#define DDRPHY_DX7GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX7GSR0: WLDONE Position     */
#define DDRPHY_DX7GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX7GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX7GSR0: WLDONE Mask         */

#define DDRPHY_DX7GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX7GSR0: WLERR Position      */
#define DDRPHY_DX7GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX7GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX7GSR0: WLERR Mask          */

#define DDRPHY_DX7GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX7GSR0: WLPRD Position      */
#define DDRPHY_DX7GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX7GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX7GSR0: WLPRD Mask          */

#define DDRPHY_DX7GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX7GSR0: DPLOCK Position     */
#define DDRPHY_DX7GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX7GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX7GSR0: DPLOCK Mask         */

#define DDRPHY_DX7GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX7GSR0: GDQSPRD Position    */
#define DDRPHY_DX7GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX7GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX7GSR0: GDQSPRD Mask        */

#define DDRPHY_DX7GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX7GSR0: QSGERR Position     */
#define DDRPHY_DX7GSR0_QSGERR_Msk        (0xful << DDRPHY_DX7GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX7GSR0: QSGERR Mask         */

#define DDRPHY_DX7GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX7GSR0: WLDQ Position       */
#define DDRPHY_DX7GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX7GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX7GSR0: WLDQ Mask           */

#define DDRPHY_DX7GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX7GSR1: DLTDONE Position    */
#define DDRPHY_DX7GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX7GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX7GSR1: DLTDONE Mask        */

#define DDRPHY_DX7GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX7GSR1: DLTCODE Position    */
#define DDRPHY_DX7GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX7GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX7GSR1: DLTCODE Mask        */

#define DDRPHY_DX7BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX7BDLR0: DQ0WBD Position    */
#define DDRPHY_DX7BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX7BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX7BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX7BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX7BDLR0: DQ1WBD Position    */
#define DDRPHY_DX7BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX7BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX7BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX7BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX7BDLR0: DQ2WBD Position    */
#define DDRPHY_DX7BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX7BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX7BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX7BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX7BDLR0: DQ3WBD Position    */
#define DDRPHY_DX7BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX7BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX7BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX7BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX7BDLR0: DQ4WBD Position    */
#define DDRPHY_DX7BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX7BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX7BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX7BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX7BDLR1: DQ5WBD Position    */
#define DDRPHY_DX7BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX7BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX7BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX7BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX7BDLR1: DQ6WBD Position    */
#define DDRPHY_DX7BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX7BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX7BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX7BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX7BDLR1: DQ7WBD Position    */
#define DDRPHY_DX7BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX7BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX7BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX7BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX7BDLR1: DMWBD Position     */
#define DDRPHY_DX7BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX7BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX7BDLR1: DMWBD Mask         */

#define DDRPHY_DX7BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX7BDLR1: DSWBD Position     */
#define DDRPHY_DX7BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX7BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX7BDLR1: DSWBD Mask         */

#define DDRPHY_DX7BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX7BDLR2: DSOEBD Position    */
#define DDRPHY_DX7BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX7BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX7BDLR2: DSOEBD Mask        */

#define DDRPHY_DX7BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX7BDLR2: DQOEBD Position    */
#define DDRPHY_DX7BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX7BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX7BDLR2: DQOEBD Mask        */

#define DDRPHY_DX7BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX7BDLR2: DSRBD Position     */
#define DDRPHY_DX7BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX7BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX7BDLR2: DSRBD Mask         */

#define DDRPHY_DX7BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX7BDLR2: DSNRBD Position    */
#define DDRPHY_DX7BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX7BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX7BDLR2: DSNRBD Mask        */

#define DDRPHY_DX7BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX7BDLR3: DQ0RBD Position    */
#define DDRPHY_DX7BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX7BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX7BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX7BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX7BDLR3: DQ1RBD Position    */
#define DDRPHY_DX7BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX7BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX7BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX7BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX7BDLR3: DQ2RBD Position    */
#define DDRPHY_DX7BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX7BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX7BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX7BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX7BDLR3: DQ3RBD Position    */
#define DDRPHY_DX7BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX7BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX7BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX7BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX7BDLR3: DQ4RBD Position    */
#define DDRPHY_DX7BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX7BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX7BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX7BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX7BDLR4: DQ5RBD Position    */
#define DDRPHY_DX7BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX7BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX7BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX7BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX7BDLR4: DQ6RBD Position    */
#define DDRPHY_DX7BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX7BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX7BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX7BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX7BDLR4: DQ7RBD Position    */
#define DDRPHY_DX7BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX7BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX7BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX7BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX7BDLR4: DMRBD Position     */
#define DDRPHY_DX7BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX7BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX7BDLR4: DMRBD Mask         */

#define DDRPHY_DX7LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX7LCDLR0: R0WLD Position    */
#define DDRPHY_DX7LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX7LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX7LCDLR0: R0WLD Mask        */

#define DDRPHY_DX7LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX7LCDLR0: R1WLD Position    */
#define DDRPHY_DX7LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX7LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX7LCDLR0: R1WLD Mask        */

#define DDRPHY_DX7LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX7LCDLR0: R2WLD Position    */
#define DDRPHY_DX7LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX7LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX7LCDLR0: R2WLD Mask        */

#define DDRPHY_DX7LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX7LCDLR0: R3WLD Position    */
#define DDRPHY_DX7LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX7LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX7LCDLR0: R3WLD Mask        */

#define DDRPHY_DX7LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX7LCDLR1: WDQD Position     */
#define DDRPHY_DX7LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX7LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX7LCDLR1: WDQD Mask         */

#define DDRPHY_DX7LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX7LCDLR1: RDQSD Position    */
#define DDRPHY_DX7LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX7LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX7LCDLR1: RDQSD Mask        */

#define DDRPHY_DX7LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX7LCDLR1: RDQSND Position   */
#define DDRPHY_DX7LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX7LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX7LCDLR1: RDQSND Mask       */

#define DDRPHY_DX7LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX7LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX7LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX7LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX7LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX7LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX7LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX7LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX7LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX7LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX7LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX7LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX7LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX7LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX7LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX7LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX7LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX7LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX7LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX7LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX7MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX7MDLR: IPRD Position       */
#define DDRPHY_DX7MDLR_IPRD_Msk          (0xfful << DDRPHY_DX7MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX7MDLR: IPRD Mask           */

#define DDRPHY_DX7MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX7MDLR: TPRD Position       */
#define DDRPHY_DX7MDLR_TPRD_Msk          (0xfful << DDRPHY_DX7MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX7MDLR: TPRD Mask           */

#define DDRPHY_DX7MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX7MDLR: MDLD Position       */
#define DDRPHY_DX7MDLR_MDLD_Msk          (0xfful << DDRPHY_DX7MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX7MDLR: MDLD Mask           */

#define DDRPHY_DX7GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX7GTR: R0DGSL Position      */
#define DDRPHY_DX7GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX7GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX7GTR: R0DGSL Mask          */

#define DDRPHY_DX7GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX7GTR: R1DGSL Position      */
#define DDRPHY_DX7GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX7GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX7GTR: R1DGSL Mask          */

#define DDRPHY_DX7GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX7GTR: R2DGSL Position      */
#define DDRPHY_DX7GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX7GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX7GTR: R2DGSL Mask          */

#define DDRPHY_DX7GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX7GTR: R3DGSL Position      */
#define DDRPHY_DX7GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX7GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX7GTR: R3DGSL Mask          */

#define DDRPHY_DX7GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX7GTR: R0WLSL Position      */
#define DDRPHY_DX7GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX7GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX7GTR: R0WLSL Mask          */

#define DDRPHY_DX7GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX7GTR: R1WLSL Position      */
#define DDRPHY_DX7GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX7GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX7GTR: R1WLSL Mask          */

#define DDRPHY_DX7GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX7GTR: R2WLSL Position      */
#define DDRPHY_DX7GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX7GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX7GTR: R2WLSL Mask          */

#define DDRPHY_DX7GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX7GTR: R3WLSL Position      */
#define DDRPHY_DX7GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX7GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX7GTR: R3WLSL Mask          */

#define DDRPHY_DX7GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX7GSR2: RDERR Position      */
#define DDRPHY_DX7GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX7GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX7GSR2: RDERR Mask          */

#define DDRPHY_DX7GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX7GSR2: RDWN Position       */
#define DDRPHY_DX7GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX7GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX7GSR2: RDWN Mask           */

#define DDRPHY_DX7GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX7GSR2: WDERR Position      */
#define DDRPHY_DX7GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX7GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX7GSR2: WDERR Mask          */

#define DDRPHY_DX7GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX7GSR2: WDWN Position       */
#define DDRPHY_DX7GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX7GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX7GSR2: WDWN Mask           */

#define DDRPHY_DX7GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX7GSR2: REERR Position      */
#define DDRPHY_DX7GSR2_REERR_Msk         (0x1ul << DDRPHY_DX7GSR2_REERR_Pos)               /*!< DDRPHY_T::DX7GSR2: REERR Mask          */

#define DDRPHY_DX7GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX7GSR2: REWN Position       */
#define DDRPHY_DX7GSR2_REWN_Msk          (0x1ul << DDRPHY_DX7GSR2_REWN_Pos)                /*!< DDRPHY_T::DX7GSR2: REWN Mask           */

#define DDRPHY_DX7GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX7GSR2: WEERR Position      */
#define DDRPHY_DX7GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX7GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX7GSR2: WEERR Mask          */

#define DDRPHY_DX7GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX7GSR2: WEWN Position       */
#define DDRPHY_DX7GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX7GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX7GSR2: WEWN Mask           */

#define DDRPHY_DX7GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX7GSR2: ESTAT Position      */
#define DDRPHY_DX7GSR2_ESTAT_Msk         (0xful << DDRPHY_DX7GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX7GSR2: ESTAT Mask          */

#define DDRPHY_DX8GCR_DXEN_Pos           (0)                                               /*!< DDRPHY_T::DX8GCR: DXEN Position        */
#define DDRPHY_DX8GCR_DXEN_Msk           (0x1ul << DDRPHY_DX8GCR_DXEN_Pos)                 /*!< DDRPHY_T::DX8GCR: DXEN Mask            */

#define DDRPHY_DX8GCR_DQSODT_Pos         (1)                                               /*!< DDRPHY_T::DX8GCR: DQSODT Position      */
#define DDRPHY_DX8GCR_DQSODT_Msk         (0x1ul << DDRPHY_DX8GCR_DQSODT_Pos)               /*!< DDRPHY_T::DX8GCR: DQSODT Mask          */

#define DDRPHY_DX8GCR_DQODT_Pos          (2)                                               /*!< DDRPHY_T::DX8GCR: DQODT Position       */
#define DDRPHY_DX8GCR_DQODT_Msk          (0x1ul << DDRPHY_DX8GCR_DQODT_Pos)                /*!< DDRPHY_T::DX8GCR: DQODT Mask           */

#define DDRPHY_DX8GCR_DXIOM_Pos          (3)                                               /*!< DDRPHY_T::DX8GCR: DXIOM Position       */
#define DDRPHY_DX8GCR_DXIOM_Msk          (0x1ul << DDRPHY_DX8GCR_DXIOM_Pos)                /*!< DDRPHY_T::DX8GCR: DXIOM Mask           */

#define DDRPHY_DX8GCR_DXPDD_Pos          (4)                                               /*!< DDRPHY_T::DX8GCR: DXPDD Position       */
#define DDRPHY_DX8GCR_DXPDD_Msk          (0x1ul << DDRPHY_DX8GCR_DXPDD_Pos)                /*!< DDRPHY_T::DX8GCR: DXPDD Mask           */

#define DDRPHY_DX8GCR_DXPDR_Pos          (5)                                               /*!< DDRPHY_T::DX8GCR: DXPDR Position       */
#define DDRPHY_DX8GCR_DXPDR_Msk          (0x1ul << DDRPHY_DX8GCR_DXPDR_Pos)                /*!< DDRPHY_T::DX8GCR: DXPDR Mask           */

#define DDRPHY_DX8GCR_DQSRPD_Pos         (6)                                               /*!< DDRPHY_T::DX8GCR: DQSRPD Position      */
#define DDRPHY_DX8GCR_DQSRPD_Msk         (0x1ul << DDRPHY_DX8GCR_DQSRPD_Pos)               /*!< DDRPHY_T::DX8GCR: DQSRPD Mask          */

#define DDRPHY_DX8GCR_DSEN_Pos           (7)                                               /*!< DDRPHY_T::DX8GCR: DSEN Position        */
#define DDRPHY_DX8GCR_DSEN_Msk           (0x3ul << DDRPHY_DX8GCR_DSEN_Pos)                 /*!< DDRPHY_T::DX8GCR: DSEN Mask            */

#define DDRPHY_DX8GCR_DQSRTT_Pos         (9)                                               /*!< DDRPHY_T::DX8GCR: DQSRTT Position      */
#define DDRPHY_DX8GCR_DQSRTT_Msk         (0x1ul << DDRPHY_DX8GCR_DQSRTT_Pos)               /*!< DDRPHY_T::DX8GCR: DQSRTT Mask          */

#define DDRPHY_DX8GCR_DQRTT_Pos          (10)                                              /*!< DDRPHY_T::DX8GCR: DQRTT Position       */
#define DDRPHY_DX8GCR_DQRTT_Msk          (0x1ul << DDRPHY_DX8GCR_DQRTT_Pos)                /*!< DDRPHY_T::DX8GCR: DQRTT Mask           */

#define DDRPHY_DX8GCR_RTTOH_Pos          (11)                                              /*!< DDRPHY_T::DX8GCR: RTTOH Position       */
#define DDRPHY_DX8GCR_RTTOH_Msk          (0x3ul << DDRPHY_DX8GCR_RTTOH_Pos)                /*!< DDRPHY_T::DX8GCR: RTTOH Mask           */

#define DDRPHY_DX8GCR_RTTOAL_Pos         (13)                                              /*!< DDRPHY_T::DX8GCR: RTTOAL Position      */
#define DDRPHY_DX8GCR_RTTOAL_Msk         (0x1ul << DDRPHY_DX8GCR_RTTOAL_Pos)               /*!< DDRPHY_T::DX8GCR: RTTOAL Mask          */

#define DDRPHY_DX8GCR_DXOEO_Pos          (14)                                              /*!< DDRPHY_T::DX8GCR: DXOEO Position       */
#define DDRPHY_DX8GCR_DXOEO_Msk          (0x3ul << DDRPHY_DX8GCR_DXOEO_Pos)                /*!< DDRPHY_T::DX8GCR: DXOEO Mask           */

#define DDRPHY_DX8GCR_PLLRST_Pos         (16)                                              /*!< DDRPHY_T::DX8GCR: PLLRST Position      */
#define DDRPHY_DX8GCR_PLLRST_Msk         (0x1ul << DDRPHY_DX8GCR_PLLRST_Pos)               /*!< DDRPHY_T::DX8GCR: PLLRST Mask          */

#define DDRPHY_DX8GCR_PLLPD_Pos          (17)                                              /*!< DDRPHY_T::DX8GCR: PLLPD Position       */
#define DDRPHY_DX8GCR_PLLPD_Msk          (0x1ul << DDRPHY_DX8GCR_PLLPD_Pos)                /*!< DDRPHY_T::DX8GCR: PLLPD Mask           */

#define DDRPHY_DX8GCR_GSHIFT_Pos         (18)                                              /*!< DDRPHY_T::DX8GCR: GSHIFT Position      */
#define DDRPHY_DX8GCR_GSHIFT_Msk         (0x1ul << DDRPHY_DX8GCR_GSHIFT_Pos)               /*!< DDRPHY_T::DX8GCR: GSHIFT Mask          */

#define DDRPHY_DX8GCR_PLLBYP_Pos         (19)                                              /*!< DDRPHY_T::DX8GCR: PLLBYP Position      */
#define DDRPHY_DX8GCR_PLLBYP_Msk         (0x1ul << DDRPHY_DX8GCR_PLLBYP_Pos)               /*!< DDRPHY_T::DX8GCR: PLLBYP Mask          */

#define DDRPHY_DX8GCR_WLRKEN_Pos         (26)                                              /*!< DDRPHY_T::DX8GCR: WLRKEN Position      */
#define DDRPHY_DX8GCR_WLRKEN_Msk         (0xful << DDRPHY_DX8GCR_WLRKEN_Pos)               /*!< DDRPHY_T::DX8GCR: WLRKEN Mask          */

#define DDRPHY_DX8GCR_MDLEN_Pos          (30)                                              /*!< DDRPHY_T::DX8GCR: MDLEN Position       */
#define DDRPHY_DX8GCR_MDLEN_Msk          (0x1ul << DDRPHY_DX8GCR_MDLEN_Pos)                /*!< DDRPHY_T::DX8GCR: MDLEN Mask           */

#define DDRPHY_DX8GCR_CALBYP_Pos         (31)                                              /*!< DDRPHY_T::DX8GCR: CALBYP Position      */
#define DDRPHY_DX8GCR_CALBYP_Msk         (0x1ul << DDRPHY_DX8GCR_CALBYP_Pos)               /*!< DDRPHY_T::DX8GCR: CALBYP Mask          */

#define DDRPHY_DX8GSR0_WDQCAL_Pos        (0)                                               /*!< DDRPHY_T::DX8GSR0: WDQCAL Position     */
#define DDRPHY_DX8GSR0_WDQCAL_Msk        (0x1ul << DDRPHY_DX8GSR0_WDQCAL_Pos)              /*!< DDRPHY_T::DX8GSR0: WDQCAL Mask         */

#define DDRPHY_DX8GSR0_RDQSCAL_Pos       (1)                                               /*!< DDRPHY_T::DX8GSR0: RDQSCAL Position    */
#define DDRPHY_DX8GSR0_RDQSCAL_Msk       (0x1ul << DDRPHY_DX8GSR0_RDQSCAL_Pos)             /*!< DDRPHY_T::DX8GSR0: RDQSCAL Mask        */

#define DDRPHY_DX8GSR0_RDQSNCAL_Pos      (2)                                               /*!< DDRPHY_T::DX8GSR0: RDQSNCAL Position   */
#define DDRPHY_DX8GSR0_RDQSNCAL_Msk      (0x1ul << DDRPHY_DX8GSR0_RDQSNCAL_Pos)            /*!< DDRPHY_T::DX8GSR0: RDQSNCAL Mask       */

#define DDRPHY_DX8GSR0_GDQSCAL_Pos       (3)                                               /*!< DDRPHY_T::DX8GSR0: GDQSCAL Position    */
#define DDRPHY_DX8GSR0_GDQSCAL_Msk       (0x1ul << DDRPHY_DX8GSR0_GDQSCAL_Pos)             /*!< DDRPHY_T::DX8GSR0: GDQSCAL Mask        */

#define DDRPHY_DX8GSR0_WLCAL_Pos         (4)                                               /*!< DDRPHY_T::DX8GSR0: WLCAL Position      */
#define DDRPHY_DX8GSR0_WLCAL_Msk         (0x1ul << DDRPHY_DX8GSR0_WLCAL_Pos)               /*!< DDRPHY_T::DX8GSR0: WLCAL Mask          */

#define DDRPHY_DX8GSR0_WLDONE_Pos        (5)                                               /*!< DDRPHY_T::DX8GSR0: WLDONE Position     */
#define DDRPHY_DX8GSR0_WLDONE_Msk        (0x1ul << DDRPHY_DX8GSR0_WLDONE_Pos)              /*!< DDRPHY_T::DX8GSR0: WLDONE Mask         */

#define DDRPHY_DX8GSR0_WLERR_Pos         (6)                                               /*!< DDRPHY_T::DX8GSR0: WLERR Position      */
#define DDRPHY_DX8GSR0_WLERR_Msk         (0x1ul << DDRPHY_DX8GSR0_WLERR_Pos)               /*!< DDRPHY_T::DX8GSR0: WLERR Mask          */

#define DDRPHY_DX8GSR0_WLPRD_Pos         (7)                                               /*!< DDRPHY_T::DX8GSR0: WLPRD Position      */
#define DDRPHY_DX8GSR0_WLPRD_Msk         (0xfful << DDRPHY_DX8GSR0_WLPRD_Pos)              /*!< DDRPHY_T::DX8GSR0: WLPRD Mask          */

#define DDRPHY_DX8GSR0_DPLOCK_Pos        (15)                                              /*!< DDRPHY_T::DX8GSR0: DPLOCK Position     */
#define DDRPHY_DX8GSR0_DPLOCK_Msk        (0x1ul << DDRPHY_DX8GSR0_DPLOCK_Pos)              /*!< DDRPHY_T::DX8GSR0: DPLOCK Mask         */

#define DDRPHY_DX8GSR0_GDQSPRD_Pos       (16)                                              /*!< DDRPHY_T::DX8GSR0: GDQSPRD Position    */
#define DDRPHY_DX8GSR0_GDQSPRD_Msk       (0xfful << DDRPHY_DX8GSR0_GDQSPRD_Pos)            /*!< DDRPHY_T::DX8GSR0: GDQSPRD Mask        */

#define DDRPHY_DX8GSR0_QSGERR_Pos        (24)                                              /*!< DDRPHY_T::DX8GSR0: QSGERR Position     */
#define DDRPHY_DX8GSR0_QSGERR_Msk        (0xful << DDRPHY_DX8GSR0_QSGERR_Pos)              /*!< DDRPHY_T::DX8GSR0: QSGERR Mask         */

#define DDRPHY_DX8GSR0_WLDQ_Pos          (28)                                              /*!< DDRPHY_T::DX8GSR0: WLDQ Position       */
#define DDRPHY_DX8GSR0_WLDQ_Msk          (0x1ul << DDRPHY_DX8GSR0_WLDQ_Pos)                /*!< DDRPHY_T::DX8GSR0: WLDQ Mask           */

#define DDRPHY_DX8GSR1_DLTDONE_Pos       (0)                                               /*!< DDRPHY_T::DX8GSR1: DLTDONE Position    */
#define DDRPHY_DX8GSR1_DLTDONE_Msk       (0x1ul << DDRPHY_DX8GSR1_DLTDONE_Pos)             /*!< DDRPHY_T::DX8GSR1: DLTDONE Mask        */

#define DDRPHY_DX8GSR1_DLTCODE_Pos       (1)                                               /*!< DDRPHY_T::DX8GSR1: DLTCODE Position    */
#define DDRPHY_DX8GSR1_DLTCODE_Msk       (0xfffffful << DDRPHY_DX8GSR1_DLTCODE_Pos)        /*!< DDRPHY_T::DX8GSR1: DLTCODE Mask        */

#define DDRPHY_DX8BDLR0_DQ0WBD_Pos       (0)                                               /*!< DDRPHY_T::DX8BDLR0: DQ0WBD Position    */
#define DDRPHY_DX8BDLR0_DQ0WBD_Msk       (0x3ful << DDRPHY_DX8BDLR0_DQ0WBD_Pos)            /*!< DDRPHY_T::DX8BDLR0: DQ0WBD Mask        */

#define DDRPHY_DX8BDLR0_DQ1WBD_Pos       (6)                                               /*!< DDRPHY_T::DX8BDLR0: DQ1WBD Position    */
#define DDRPHY_DX8BDLR0_DQ1WBD_Msk       (0x3ful << DDRPHY_DX8BDLR0_DQ1WBD_Pos)            /*!< DDRPHY_T::DX8BDLR0: DQ1WBD Mask        */

#define DDRPHY_DX8BDLR0_DQ2WBD_Pos       (12)                                              /*!< DDRPHY_T::DX8BDLR0: DQ2WBD Position    */
#define DDRPHY_DX8BDLR0_DQ2WBD_Msk       (0x3ful << DDRPHY_DX8BDLR0_DQ2WBD_Pos)            /*!< DDRPHY_T::DX8BDLR0: DQ2WBD Mask        */

#define DDRPHY_DX8BDLR0_DQ3WBD_Pos       (18)                                              /*!< DDRPHY_T::DX8BDLR0: DQ3WBD Position    */
#define DDRPHY_DX8BDLR0_DQ3WBD_Msk       (0x3ful << DDRPHY_DX8BDLR0_DQ3WBD_Pos)            /*!< DDRPHY_T::DX8BDLR0: DQ3WBD Mask        */

#define DDRPHY_DX8BDLR0_DQ4WBD_Pos       (24)                                              /*!< DDRPHY_T::DX8BDLR0: DQ4WBD Position    */
#define DDRPHY_DX8BDLR0_DQ4WBD_Msk       (0x3ful << DDRPHY_DX8BDLR0_DQ4WBD_Pos)            /*!< DDRPHY_T::DX8BDLR0: DQ4WBD Mask        */

#define DDRPHY_DX8BDLR1_DQ5WBD_Pos       (0)                                               /*!< DDRPHY_T::DX8BDLR1: DQ5WBD Position    */
#define DDRPHY_DX8BDLR1_DQ5WBD_Msk       (0x3ful << DDRPHY_DX8BDLR1_DQ5WBD_Pos)            /*!< DDRPHY_T::DX8BDLR1: DQ5WBD Mask        */

#define DDRPHY_DX8BDLR1_DQ6WBD_Pos       (6)                                               /*!< DDRPHY_T::DX8BDLR1: DQ6WBD Position    */
#define DDRPHY_DX8BDLR1_DQ6WBD_Msk       (0x3ful << DDRPHY_DX8BDLR1_DQ6WBD_Pos)            /*!< DDRPHY_T::DX8BDLR1: DQ6WBD Mask        */

#define DDRPHY_DX8BDLR1_DQ7WBD_Pos       (12)                                              /*!< DDRPHY_T::DX8BDLR1: DQ7WBD Position    */
#define DDRPHY_DX8BDLR1_DQ7WBD_Msk       (0x3ful << DDRPHY_DX8BDLR1_DQ7WBD_Pos)            /*!< DDRPHY_T::DX8BDLR1: DQ7WBD Mask        */

#define DDRPHY_DX8BDLR1_DMWBD_Pos        (18)                                              /*!< DDRPHY_T::DX8BDLR1: DMWBD Position     */
#define DDRPHY_DX8BDLR1_DMWBD_Msk        (0x3ful << DDRPHY_DX8BDLR1_DMWBD_Pos)             /*!< DDRPHY_T::DX8BDLR1: DMWBD Mask         */

#define DDRPHY_DX8BDLR1_DSWBD_Pos        (24)                                              /*!< DDRPHY_T::DX8BDLR1: DSWBD Position     */
#define DDRPHY_DX8BDLR1_DSWBD_Msk        (0x3ful << DDRPHY_DX8BDLR1_DSWBD_Pos)             /*!< DDRPHY_T::DX8BDLR1: DSWBD Mask         */

#define DDRPHY_DX8BDLR2_DSOEBD_Pos       (0)                                               /*!< DDRPHY_T::DX8BDLR2: DSOEBD Position    */
#define DDRPHY_DX8BDLR2_DSOEBD_Msk       (0x3ful << DDRPHY_DX8BDLR2_DSOEBD_Pos)            /*!< DDRPHY_T::DX8BDLR2: DSOEBD Mask        */

#define DDRPHY_DX8BDLR2_DQOEBD_Pos       (6)                                               /*!< DDRPHY_T::DX8BDLR2: DQOEBD Position    */
#define DDRPHY_DX8BDLR2_DQOEBD_Msk       (0x3ful << DDRPHY_DX8BDLR2_DQOEBD_Pos)            /*!< DDRPHY_T::DX8BDLR2: DQOEBD Mask        */

#define DDRPHY_DX8BDLR2_DSRBD_Pos        (12)                                              /*!< DDRPHY_T::DX8BDLR2: DSRBD Position     */
#define DDRPHY_DX8BDLR2_DSRBD_Msk        (0x3ful << DDRPHY_DX8BDLR2_DSRBD_Pos)             /*!< DDRPHY_T::DX8BDLR2: DSRBD Mask         */

#define DDRPHY_DX8BDLR2_DSNRBD_Pos       (18)                                              /*!< DDRPHY_T::DX8BDLR2: DSNRBD Position    */
#define DDRPHY_DX8BDLR2_DSNRBD_Msk       (0x3ful << DDRPHY_DX8BDLR2_DSNRBD_Pos)            /*!< DDRPHY_T::DX8BDLR2: DSNRBD Mask        */

#define DDRPHY_DX8BDLR3_DQ0RBD_Pos       (0)                                               /*!< DDRPHY_T::DX8BDLR3: DQ0RBD Position    */
#define DDRPHY_DX8BDLR3_DQ0RBD_Msk       (0x3ful << DDRPHY_DX8BDLR3_DQ0RBD_Pos)            /*!< DDRPHY_T::DX8BDLR3: DQ0RBD Mask        */

#define DDRPHY_DX8BDLR3_DQ1RBD_Pos       (6)                                               /*!< DDRPHY_T::DX8BDLR3: DQ1RBD Position    */
#define DDRPHY_DX8BDLR3_DQ1RBD_Msk       (0x3ful << DDRPHY_DX8BDLR3_DQ1RBD_Pos)            /*!< DDRPHY_T::DX8BDLR3: DQ1RBD Mask        */

#define DDRPHY_DX8BDLR3_DQ2RBD_Pos       (12)                                              /*!< DDRPHY_T::DX8BDLR3: DQ2RBD Position    */
#define DDRPHY_DX8BDLR3_DQ2RBD_Msk       (0x3ful << DDRPHY_DX8BDLR3_DQ2RBD_Pos)            /*!< DDRPHY_T::DX8BDLR3: DQ2RBD Mask        */

#define DDRPHY_DX8BDLR3_DQ3RBD_Pos       (18)                                              /*!< DDRPHY_T::DX8BDLR3: DQ3RBD Position    */
#define DDRPHY_DX8BDLR3_DQ3RBD_Msk       (0x3ful << DDRPHY_DX8BDLR3_DQ3RBD_Pos)            /*!< DDRPHY_T::DX8BDLR3: DQ3RBD Mask        */

#define DDRPHY_DX8BDLR3_DQ4RBD_Pos       (24)                                              /*!< DDRPHY_T::DX8BDLR3: DQ4RBD Position    */
#define DDRPHY_DX8BDLR3_DQ4RBD_Msk       (0x3ful << DDRPHY_DX8BDLR3_DQ4RBD_Pos)            /*!< DDRPHY_T::DX8BDLR3: DQ4RBD Mask        */

#define DDRPHY_DX8BDLR4_DQ5RBD_Pos       (0)                                               /*!< DDRPHY_T::DX8BDLR4: DQ5RBD Position    */
#define DDRPHY_DX8BDLR4_DQ5RBD_Msk       (0x3ful << DDRPHY_DX8BDLR4_DQ5RBD_Pos)            /*!< DDRPHY_T::DX8BDLR4: DQ5RBD Mask        */

#define DDRPHY_DX8BDLR4_DQ6RBD_Pos       (6)                                               /*!< DDRPHY_T::DX8BDLR4: DQ6RBD Position    */
#define DDRPHY_DX8BDLR4_DQ6RBD_Msk       (0x3ful << DDRPHY_DX8BDLR4_DQ6RBD_Pos)            /*!< DDRPHY_T::DX8BDLR4: DQ6RBD Mask        */

#define DDRPHY_DX8BDLR4_DQ7RBD_Pos       (12)                                              /*!< DDRPHY_T::DX8BDLR4: DQ7RBD Position    */
#define DDRPHY_DX8BDLR4_DQ7RBD_Msk       (0x3ful << DDRPHY_DX8BDLR4_DQ7RBD_Pos)            /*!< DDRPHY_T::DX8BDLR4: DQ7RBD Mask        */

#define DDRPHY_DX8BDLR4_DMRBD_Pos        (18)                                              /*!< DDRPHY_T::DX8BDLR4: DMRBD Position     */
#define DDRPHY_DX8BDLR4_DMRBD_Msk        (0x3ful << DDRPHY_DX8BDLR4_DMRBD_Pos)             /*!< DDRPHY_T::DX8BDLR4: DMRBD Mask         */

#define DDRPHY_DX8LCDLR0_R0WLD_Pos       (0)                                               /*!< DDRPHY_T::DX8LCDLR0: R0WLD Position    */
#define DDRPHY_DX8LCDLR0_R0WLD_Msk       (0xfful << DDRPHY_DX8LCDLR0_R0WLD_Pos)            /*!< DDRPHY_T::DX8LCDLR0: R0WLD Mask        */

#define DDRPHY_DX8LCDLR0_R1WLD_Pos       (8)                                               /*!< DDRPHY_T::DX8LCDLR0: R1WLD Position    */
#define DDRPHY_DX8LCDLR0_R1WLD_Msk       (0xfful << DDRPHY_DX8LCDLR0_R1WLD_Pos)            /*!< DDRPHY_T::DX8LCDLR0: R1WLD Mask        */

#define DDRPHY_DX8LCDLR0_R2WLD_Pos       (16)                                              /*!< DDRPHY_T::DX8LCDLR0: R2WLD Position    */
#define DDRPHY_DX8LCDLR0_R2WLD_Msk       (0xfful << DDRPHY_DX8LCDLR0_R2WLD_Pos)            /*!< DDRPHY_T::DX8LCDLR0: R2WLD Mask        */

#define DDRPHY_DX8LCDLR0_R3WLD_Pos       (24)                                              /*!< DDRPHY_T::DX8LCDLR0: R3WLD Position    */
#define DDRPHY_DX8LCDLR0_R3WLD_Msk       (0xfful << DDRPHY_DX8LCDLR0_R3WLD_Pos)            /*!< DDRPHY_T::DX8LCDLR0: R3WLD Mask        */

#define DDRPHY_DX8LCDLR1_WDQD_Pos        (0)                                               /*!< DDRPHY_T::DX8LCDLR1: WDQD Position     */
#define DDRPHY_DX8LCDLR1_WDQD_Msk        (0xfful << DDRPHY_DX8LCDLR1_WDQD_Pos)             /*!< DDRPHY_T::DX8LCDLR1: WDQD Mask         */

#define DDRPHY_DX8LCDLR1_RDQSD_Pos       (8)                                               /*!< DDRPHY_T::DX8LCDLR1: RDQSD Position    */
#define DDRPHY_DX8LCDLR1_RDQSD_Msk       (0xfful << DDRPHY_DX8LCDLR1_RDQSD_Pos)            /*!< DDRPHY_T::DX8LCDLR1: RDQSD Mask        */

#define DDRPHY_DX8LCDLR1_RDQSND_Pos      (16)                                              /*!< DDRPHY_T::DX8LCDLR1: RDQSND Position   */
#define DDRPHY_DX8LCDLR1_RDQSND_Msk      (0xfful << DDRPHY_DX8LCDLR1_RDQSND_Pos)           /*!< DDRPHY_T::DX8LCDLR1: RDQSND Mask       */

#define DDRPHY_DX8LCDLR2_R0DQSGD_Pos     (0)                                               /*!< DDRPHY_T::DX8LCDLR2: R0DQSGD Position  */
#define DDRPHY_DX8LCDLR2_R0DQSGD_Msk     (0xfful << DDRPHY_DX8LCDLR2_R0DQSGD_Pos)          /*!< DDRPHY_T::DX8LCDLR2: R0DQSGD Mask      */

#define DDRPHY_DX8LCDLR2_R1DQSGD_Pos     (8)                                               /*!< DDRPHY_T::DX8LCDLR2: R1DQSGD Position  */
#define DDRPHY_DX8LCDLR2_R1DQSGD_Msk     (0xfful << DDRPHY_DX8LCDLR2_R1DQSGD_Pos)          /*!< DDRPHY_T::DX8LCDLR2: R1DQSGD Mask      */

#define DDRPHY_DX8LCDLR2_R2DQSGD_Pos     (16)                                              /*!< DDRPHY_T::DX8LCDLR2: R2DQSGD Position  */
#define DDRPHY_DX8LCDLR2_R2DQSGD_Msk     (0xfful << DDRPHY_DX8LCDLR2_R2DQSGD_Pos)          /*!< DDRPHY_T::DX8LCDLR2: R2DQSGD Mask      */

#define DDRPHY_DX8LCDLR2_R3DQSGD_Pos     (24)                                              /*!< DDRPHY_T::DX8LCDLR2: R3DQSGD Position  */
#define DDRPHY_DX8LCDLR2_R3DQSGD_Msk     (0xfful << DDRPHY_DX8LCDLR2_R3DQSGD_Pos)          /*!< DDRPHY_T::DX8LCDLR2: R3DQSGD Mask      */

#define DDRPHY_DX8MDLR_IPRD_Pos          (0)                                               /*!< DDRPHY_T::DX8MDLR: IPRD Position       */
#define DDRPHY_DX8MDLR_IPRD_Msk          (0xfful << DDRPHY_DX8MDLR_IPRD_Pos)               /*!< DDRPHY_T::DX8MDLR: IPRD Mask           */

#define DDRPHY_DX8MDLR_TPRD_Pos          (8)                                               /*!< DDRPHY_T::DX8MDLR: TPRD Position       */
#define DDRPHY_DX8MDLR_TPRD_Msk          (0xfful << DDRPHY_DX8MDLR_TPRD_Pos)               /*!< DDRPHY_T::DX8MDLR: TPRD Mask           */

#define DDRPHY_DX8MDLR_MDLD_Pos          (16)                                              /*!< DDRPHY_T::DX8MDLR: MDLD Position       */
#define DDRPHY_DX8MDLR_MDLD_Msk          (0xfful << DDRPHY_DX8MDLR_MDLD_Pos)               /*!< DDRPHY_T::DX8MDLR: MDLD Mask           */

#define DDRPHY_DX8GTR_R0DGSL_Pos         (0)                                               /*!< DDRPHY_T::DX8GTR: R0DGSL Position      */
#define DDRPHY_DX8GTR_R0DGSL_Msk         (0x7ul << DDRPHY_DX8GTR_R0DGSL_Pos)               /*!< DDRPHY_T::DX8GTR: R0DGSL Mask          */

#define DDRPHY_DX8GTR_R1DGSL_Pos         (3)                                               /*!< DDRPHY_T::DX8GTR: R1DGSL Position      */
#define DDRPHY_DX8GTR_R1DGSL_Msk         (0x7ul << DDRPHY_DX8GTR_R1DGSL_Pos)               /*!< DDRPHY_T::DX8GTR: R1DGSL Mask          */

#define DDRPHY_DX8GTR_R2DGSL_Pos         (6)                                               /*!< DDRPHY_T::DX8GTR: R2DGSL Position      */
#define DDRPHY_DX8GTR_R2DGSL_Msk         (0x7ul << DDRPHY_DX8GTR_R2DGSL_Pos)               /*!< DDRPHY_T::DX8GTR: R2DGSL Mask          */

#define DDRPHY_DX8GTR_R3DGSL_Pos         (9)                                               /*!< DDRPHY_T::DX8GTR: R3DGSL Position      */
#define DDRPHY_DX8GTR_R3DGSL_Msk         (0x7ul << DDRPHY_DX8GTR_R3DGSL_Pos)               /*!< DDRPHY_T::DX8GTR: R3DGSL Mask          */

#define DDRPHY_DX8GTR_R0WLSL_Pos         (12)                                              /*!< DDRPHY_T::DX8GTR: R0WLSL Position      */
#define DDRPHY_DX8GTR_R0WLSL_Msk         (0x3ul << DDRPHY_DX8GTR_R0WLSL_Pos)               /*!< DDRPHY_T::DX8GTR: R0WLSL Mask          */

#define DDRPHY_DX8GTR_R1WLSL_Pos         (14)                                              /*!< DDRPHY_T::DX8GTR: R1WLSL Position      */
#define DDRPHY_DX8GTR_R1WLSL_Msk         (0x3ul << DDRPHY_DX8GTR_R1WLSL_Pos)               /*!< DDRPHY_T::DX8GTR: R1WLSL Mask          */

#define DDRPHY_DX8GTR_R2WLSL_Pos         (16)                                              /*!< DDRPHY_T::DX8GTR: R2WLSL Position      */
#define DDRPHY_DX8GTR_R2WLSL_Msk         (0x3ul << DDRPHY_DX8GTR_R2WLSL_Pos)               /*!< DDRPHY_T::DX8GTR: R2WLSL Mask          */

#define DDRPHY_DX8GTR_R3WLSL_Pos         (18)                                              /*!< DDRPHY_T::DX8GTR: R3WLSL Position      */
#define DDRPHY_DX8GTR_R3WLSL_Msk         (0x3ul << DDRPHY_DX8GTR_R3WLSL_Pos)               /*!< DDRPHY_T::DX8GTR: R3WLSL Mask          */

#define DDRPHY_DX8GSR2_RDERR_Pos         (0)                                               /*!< DDRPHY_T::DX8GSR2: RDERR Position      */
#define DDRPHY_DX8GSR2_RDERR_Msk         (0x1ul << DDRPHY_DX8GSR2_RDERR_Pos)               /*!< DDRPHY_T::DX8GSR2: RDERR Mask          */

#define DDRPHY_DX8GSR2_RDWN_Pos          (1)                                               /*!< DDRPHY_T::DX8GSR2: RDWN Position       */
#define DDRPHY_DX8GSR2_RDWN_Msk          (0x1ul << DDRPHY_DX8GSR2_RDWN_Pos)                /*!< DDRPHY_T::DX8GSR2: RDWN Mask           */

#define DDRPHY_DX8GSR2_WDERR_Pos         (2)                                               /*!< DDRPHY_T::DX8GSR2: WDERR Position      */
#define DDRPHY_DX8GSR2_WDERR_Msk         (0x1ul << DDRPHY_DX8GSR2_WDERR_Pos)               /*!< DDRPHY_T::DX8GSR2: WDERR Mask          */

#define DDRPHY_DX8GSR2_WDWN_Pos          (3)                                               /*!< DDRPHY_T::DX8GSR2: WDWN Position       */
#define DDRPHY_DX8GSR2_WDWN_Msk          (0x1ul << DDRPHY_DX8GSR2_WDWN_Pos)                /*!< DDRPHY_T::DX8GSR2: WDWN Mask           */

#define DDRPHY_DX8GSR2_REERR_Pos         (4)                                               /*!< DDRPHY_T::DX8GSR2: REERR Position      */
#define DDRPHY_DX8GSR2_REERR_Msk         (0x1ul << DDRPHY_DX8GSR2_REERR_Pos)               /*!< DDRPHY_T::DX8GSR2: REERR Mask          */

#define DDRPHY_DX8GSR2_REWN_Pos          (5)                                               /*!< DDRPHY_T::DX8GSR2: REWN Position       */
#define DDRPHY_DX8GSR2_REWN_Msk          (0x1ul << DDRPHY_DX8GSR2_REWN_Pos)                /*!< DDRPHY_T::DX8GSR2: REWN Mask           */

#define DDRPHY_DX8GSR2_WEERR_Pos         (6)                                               /*!< DDRPHY_T::DX8GSR2: WEERR Position      */
#define DDRPHY_DX8GSR2_WEERR_Msk         (0x1ul << DDRPHY_DX8GSR2_WEERR_Pos)               /*!< DDRPHY_T::DX8GSR2: WEERR Mask          */

#define DDRPHY_DX8GSR2_WEWN_Pos          (7)                                               /*!< DDRPHY_T::DX8GSR2: WEWN Position       */
#define DDRPHY_DX8GSR2_WEWN_Msk          (0x1ul << DDRPHY_DX8GSR2_WEWN_Pos)                /*!< DDRPHY_T::DX8GSR2: WEWN Mask           */

#define DDRPHY_DX8GSR2_ESTAT_Pos         (8)                                               /*!< DDRPHY_T::DX8GSR2: ESTAT Position      */
#define DDRPHY_DX8GSR2_ESTAT_Msk         (0xful << DDRPHY_DX8GSR2_ESTAT_Pos)               /*!< DDRPHY_T::DX8GSR2: ESTAT Mask          */

/**@}*/ /* DDRPHY_CONST */
/**@}*/ /* end of DDRPHY register group */


/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __DDR32PHY_REG_H__ */

