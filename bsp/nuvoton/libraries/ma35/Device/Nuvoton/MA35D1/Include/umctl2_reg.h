/**************************************************************************//**
 * @file     umctl2_reg.h
 * @brief    UMCTL2 register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __UMCTL2_REG_H__
#define __UMCTL2_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- DDR Memory Controller -------------------------*/
/**
    @addtogroup UMCTL2 DDR Memory Controller (UMCTL2)
    Memory Mapped Structure for UMCTL2 Controller
@{ */

typedef struct
{


    /**
     * @var UMCTL2_T::MSTR
     * Offset: 0x00  Master Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ddr3      |DDR3 SDRAM Type Enable Bit
     * |        |          |Selects DDR3 SDRAM.
     * |        |          |u00B7 1 - DDR3 SDRAM device in use
     * |        |          |u00B7 0 - non-DDR3 SDRAM device in use
     * |        |          |Present only in designs configured to support DDR3.
     * |        |          |Programming Mode: Static
     * |[9]     |burstchop |Burst-Chop Enable Bit
     * |        |          |When this bit is set, enables burst-chop (BC4 or 8 on-the-fly) in DDR3.
     * |        |          |Burst Chop for reads is exercised only:
     * |        |          |u00B7 If in full bus width mode (MSTR.data_bus_width = 00)
     * |        |          |Burst Chop for writes is exercised only:
     * |        |          |u00B7 If CRC is disabled (CRCPARCTL1.crc_enable = 0)
     * |        |          |BC4 (fixed) mode is not supported.
     * |        |          |Programming Mode: Static
     * |[10]    |en_2t_timing_mode|2T Timing Mode Enable Bit
     * |        |          |If 1, then uMCTL2 uses 2T timing, otherwise uses 1T timing.
     * |        |          |In 2T timing, all command signals (except chip select) are held for 2 clocks on the SDRAM bus
     * |        |          |Chip select is asserted on the second cycle of the command.
     * |        |          |Programming Mode: Static
     * |[13:12] |data_bus_width|DQ Bus Width
     * |        |          |Selects proportion of DQ bus width that is used by the SDRAM.
     * |        |          |u00B7 00 - Full DQ bus width to SDRAM
     * |        |          |u00B7 01 - Half DQ bus width to SDRAM
     * |        |          |u00B7 10 - Reserved
     * |        |          |u00B7 11 - Reserved
     * |        |          |Note that half bus width mode is only supported when the SDRAM bus width is a multiple of 16
     * |        |          |Bus width refers to DQ bus width (excluding any ECC width).
     * |        |          |Programming Mode: Static
     * |[15]    |dll_off_mode|DLL Off Mode Enable Bit
     * |        |          |u00B7 1 - When the uMCTL2 and DRAM has to be put in DLL-off mode for low frequency operation
     * |        |          |u00B7 0 - To put uMCTL2 and DRAM in DLL-on mode for normal frequency operation
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * |[19:16] |burst_rdwr|Burst Length for Read and Write
     * |        |          |Indicates SDRAM burst length used:
     * |        |          |u00B7 0010 - Burst length of 4
     * |        |          |u00B7 0100 - Burst length of 8
     * |        |          |All other values are reserved.
     * |        |          |This bit controls the burst size used to access the SDRAM
     * |        |          |This must match the burst length mode register setting in the SDRAM
     * |        |          |(For BC4/8 on-the-fly mode of DDR3, set this field to 0x0100) Burst length of 2 is not supported with AXI ports when MEMC_BURST_LENGTH is 8.
     * |        |          |Burst length of 2 is only supported when the controller is operating in 1:1 frequency mode.
     * |        |          |For DDR3, this must be set to 0x0100 (BL8).
     * |        |          |Programming Mode: Static
     * |[25:24] |active_ranks|Active Ranks
     * |        |          |u00B7 01 - One rank
     * |        |          |u00B7 11 - Two ranks
     * |        |          |u00B7 Others - Reserved
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::STAT
     * Offset: 0x04  Operating Mode Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |operating_mode|Operating Mode
     * |        |          |u00B7 00 - Init
     * |        |          |u00B7 01 - Normal
     * |        |          |u00B7 10 - Power-down
     * |        |          |u00B7 11 - Self-refresh
     * |        |          |Programming Mode: Static
     * |[5:4]   |selfref_type|Self-Refresh Type
     * |        |          |Flags if self-refresh is entered, and if it is under automatic self-refresh control only or not.
     * |        |          |u00B7 00 - SDRAM is not in self-refresh
     * |        |          |If retry is enabled by CRCPARCTL1.crc_parity_retry_enable, this also indicates that the SRE command is still in parity error window or retry is in-progress.
     * |        |          |u00B7 11 - SDRAM is in self-refresh, which was caused by Automatic self-refresh only
     * |        |          |If retry is enabled, this ensures that the SRE command is executed correctly without parity error.
     * |        |          |u00B7 10 - SDRAM is in self-refresh, which was not caused solely under automatic self-refresh control
     * |        |          |It could have been caused by Hardware Low Power Interface and/or Software (PWRCTL.selfref_sw)
     * |        |          |If retry is enabled, this ensures that the SRE command is executed correctly without parity error.
     * |        |          |u00B7 01 - SDRAM is in self-refresh, which is caused by PHY Master Request.
     * |        |          |Programming Mode: Static
     * |[12]    |selfref_cam_not_empty|Self-Refresh with CAMs Not Empty.
     * |        |          |Set to 1 when self-refresh is entered but CAMs are not drained.
     * |        |          |Cleared after exiting self-refresh.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::MRCTRL0
     * Offset: 0x10  Mode Register Read/Write Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:4]   |mr_rank   |Mode Register Accessing Rank
     * |        |          |Controls which rank is accessed by MRCTRL0.mr_wr.
     * |        |          |Normally, it is desired to access all ranks, so all bits must be set to 1.
     * |        |          |Examples (assuming uMCTL2 is configured for 2 ranks):
     * |        |          |u00B7 0x1 - Select rank 0 only
     * |        |          |u00B7 0x2 - Select rank 1 only
     * |        |          |u00B7 0x3 - Select ranks 0 and 1
     * |        |          |Programming Mode: Dynamic
     * |[15:12] |mr_addr   |Mode Register Address
     * |        |          |Address of the mode register that is to be written to.
     * |        |          |u00B7 0000 - MR0
     * |        |          |u00B7 0001 - MR1
     * |        |          |u00B7 0010 - MR2
     * |        |          |u00B7 0011 - MR3
     * |        |          |u00B7 0100 - MR4
     * |        |          |u00B7 0101 - MR5
     * |        |          |u00B7 0110 - MR6
     * |        |          |u00B7 0111 - MR7
     * |        |          |Programming Mode: Dynamic
     * |[31]    |mr_wr     |Mode Register Read or Write Operation Trigger
     * |        |          |Setting this register bit to 1 triggers a mode register read or write operation.
     * |        |          |When the MR operation is complete, the uMCTL2 automatically clears this bit.
     * |        |          |The other fields of this register must be written in a separate APB transaction, before setting this mr_wr bit.
     * |        |          |It is recommended NOT to set this signal if in Init, Deep power-down, or MPSM operating modes.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::MRCTRL1
     * Offset: 0x14  Mode Register Read/Write Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |mr_data   |Mode Register Write Data
     * |        |          |Mode register write data for all DDR2/DDR3 modes.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::MRSTAT
     * Offset: 0x18  Mode Register Read/Write Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |mr_wr_busy|Mode Register Write Busy
     * |        |          |The SoC might initiate a MR write operation only if this signal is low.
     * |        |          |This signal goes:
     * |        |          |u00B7 High in the clock after the uMCTL2 accepts the MRW/MRR request
     * |        |          |u00B7 Low when the MRW/MRR command is issued to the SDRAM
     * |        |          |It is recommended not to perform MRW/MRR commands when 'MRSTAT.mr_wr_busy' is high.
     * |        |          |u00B7 0 - Indicates that the SoC can initiate a mode register write operation
     * |        |          |u00B7 1 - Indicates that mode register write operation is in progress
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PWRCTL
     * Offset: 0x30  Low Power Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |selfref_en|Self-Refresh Enable Bit
     * |        |          |If it is true, then the uMCTL2 puts the SDRAM into self-refresh after a programmable number of cycles "maximum idle clocks before self-refresh (PWRTMG.selfref_to_x32)".
     * |        |          |This register bit may be re-programmed during the course of normal operation.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |powerdown_en|Power-Down Enable Bit
     * |        |          |If it is true, then the uMCTL2 goes into power-down after a programmable number of cycles "maximum idle clocks before power down" (PWRTMG.powerdown_to_x32).
     * |        |          |This register bit may be re-programmed during the course of normal operation.
     * |        |          |Programming Mode: Dynamic
     * |[3]     |en_dfi_dram_clk_disable|dfi_dram_clk_disable Enable Bit
     * |        |          |Enables the assertion of dfi_dram_clk_disable whenever a clock is not required by the SDRAM.
     * |        |          |If set to 0, dfi_dram_clk_disable is never asserted.
     * |        |          |Assertion of dfi_dram_clk_disable is as follows:
     * |        |          |In DDR2/DDR3, can only be asserted in self-refresh.
     * |        |          |Programming Mode: Dynamic
     * |[5]     |selfref_sw|Self-Refresh Entry/Exit by Software
     * |        |          |A value of 1 to this register causes system to move to self-refresh state immediately, as long as it is not in INIT or DPD/MPSM operating_mode.
     * |        |          |This is referred to as Software Entry/Exit to self-refresh.
     * |        |          |u00B7 1 - Software Entry to self-refresh
     * |        |          |u00B7 0 - Software Exit from self-refresh
     * |        |          |Programming Mode: Dynamic
     * |[7]     |dis_cam_drain_selfref|Disable CAM Drain Before Entering Self-Refresh
     * |        |          |Indicates whether skipping CAM draining is allowed when entering self-refresh.
     * |        |          |This register field cannot be modified while PWRCTL.selfref_sw == 1.
     * |        |          |u00B7 0 - CAMs must be empty before entering SR
     * |        |          |u00B7 1 - CAMs are not emptied before entering SR (unsupported) Note, PWRCTL.dis_cam_drain_selfref=1 is unsupported in this release
     * |        |          |PWRCTL.dis_cam_drain_selfref=0 is required.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PWRTMG
     * Offset: 0x34  Low Power Timing Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |powerdown_to_x32|SDRAM Power-Down Enter After This Clock Number
     * |        |          |After this many clocks of the DDRC command channel being idle the uMCTL2 automatically puts the SDRAM into power-down.
     * |        |          |The DDRC command channel is considered idle when there are no HIF commands outstanding
     * |        |          |This must be enabled in the PWRCTL.powerdown_en.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[23:16] |selfref_to_x32|SDRAM Self-Refresh Enter After This Clock Number
     * |        |          |After this many clocks of the DDRC command channel being idle the uMCTL2 automatically puts the SDRAM into self-refresh.
     * |        |          |The DDRC command channel is considered idle when there are no HIF commands outstanding
     * |        |          |This must be enabled in the PWRCTL.selfref_en.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * @var UMCTL2_T::HWLPCTL
     * Offset: 0x38  Hardware Low Power Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |hw_lp_en  |Hardware Low Power Interface Enable Bit
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * |[1]     |hw_lp_exit_idle_en|Hardware Exit Idle Enable Bit
     * |        |          |When this bit is programmed to 1 the cactive_in_ddrc pin of the DDRC can be used to exit from the automatic clock stop, automatic power down or automatic self-refresh modes.
     * |        |          |Note, it does not cause exit of self-refresh that was caused by Hardware Low Power Interface and/or Software (PWRCTL.selfref_sw).
     * |        |          |Programming Mode: Static
     * |[27:16] |hw_lp_idle_x32|Hardware idle period.
     * |        |          |The cactive_ddrc output is driven low if the DDRC command channel is idle for hw_lp_idle * 32 cycles if not in INIT or DPD/MPSM operating_mode.
     * |        |          |The DDRC command channel is considered idle when there are no HIF commands outstanding
     * |        |          |The hardware idle function is disabled when hw_lp_idle_x32=0
     * |        |          |hw_lp_idle_x32=1 is an illegal value.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::RFSHCTL0
     * Offset: 0x50  Refresh Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:4]   |refresh_burst|Refresh Burst Number
     * |        |          |The programmed value + 1 is the number of refresh timeouts that is allowed to accumulate before traffic is blocked and the refreshes are forced to execute.
     * |        |          |Closing pages to perform a refresh is a one-time penalty that must be paid for each group of refreshes
     * |        |          |Therefore, performing refreshes in a burst reduces the per-refresh penalty of these page closings.
     * |        |          |Higher numbers for RFSHCTL.refresh_burst slightly increase utilization; lower numbers decrease the worst-case latency associated with refreshes.
     * |        |          |u00B7 0 - Single refresh
     * |        |          |u00B7 1 - Burst-of-2 refresh
     * |        |          |u00B7 7 - Burst-of-8 refresh
     * |        |          |For more information on burst refresh feature, see section 3.9 of DDR2 JEDEC specification - JESD79-2F.pdf.
     * |        |          |For DDR2/3, the refresh is always per-rank and not per-bank
     * |        |          |The rank refresh can be accumulated over 8*tREFI cycles using the burst refresh feature.
     * |        |          |If using PHY-initiated updates, care must be taken in the setting of RFSHCTL0.refresh_burst, to ensure that tRFCmax is not violated due to a PHY-initiated update occurring shortly before a refresh burst is due.
     * |        |          |In this situation, the refresh burst is delayed until the PHY-initiated update is complete.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * |[16:12] |refresh_to_x1_x32|SDRAM Bus Idle Period
     * |        |          |If the refresh timer (tRFCnom, also known as tREFI) has expired at least once, then a speculative refresh may be performed.
     * |        |          |A speculative refresh is a refresh performed at a time when refresh would be useful
     * |        |          |When the SDRAM bus is idle for a period of time determined by this RFSHCTL0.refresh_to_x1_x32 and the refresh timer has expired at least once since the last refresh, then a speculative refresh is performed.
     * |        |          |Speculative refreshes continue successively until there are no refreshes pending or until new reads or writes are issued to the uMCTL2.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: DFI clock cycles or multiples of 32 DFI clock cycles, depending on RFSHTMG.t_rfc_nom_x1_sel.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * |[23:20] |refresh_margin|Refresh Margin
     * |        |          |Threshold value in number of DFI clock cycles before the critical refresh or page timer expires.
     * |        |          |A critical refresh is to be issued before this threshold is reached.
     * |        |          |It is recommended that this not be changed from the default value, currently shown as 0x2.
     * |        |          |It must always be less than internally used t_rfc_nom/32.
     * |        |          |Note that internally used t_rfc_nom is equal to RFSHTMG.t_rfc_nom_x1_x32 * 32 if RFSHTMG.t_rfc_nom_x1_sel=0.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * @var UMCTL2_T::RFSHCTL1
     * Offset: 0x54  Refresh Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |refresh_timer0_start_value_x32|Refresh Timer Start Value for Rank 0
     * |        |          |only present in multi-rank configurations
     * |        |          |This is useful in staggering the refreshes to multiple ranks to help traffic to proceed.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * |[27:16] |refresh_timer1_start_value_x32|Refresh Timer Start Value for Rank 1
     * |        |          |only present in multi-rank configurations
     * |        |          |This is useful in staggering the refreshes to multiple ranks to help traffic to proceed.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * @var UMCTL2_T::RFSHCTL3
     * Offset: 0x60  Refresh Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dis_auto_refresh|Disable Auto-Refresh Enable Bit
     * |        |          |When '1', disable auto-refresh generated by the uMCTL2.
     * |        |          |When auto-refresh is disabled, the SoC must generate refreshes using the registers DBGCMD.rankn_refresh.
     * |        |          |When dis_auto_refresh transitions from 0 to 1, any pending refreshes are immediately scheduled by the uMCTL2.
     * |        |          |This register field is changeable on the fly.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * |[1]     |refresh_update_level|Refresh Registers Updated Operation
     * |        |          |Toggle this signal (either from 0 to 1 or from 1 to 0) to indicate that the refresh registers have been updated.
     * |        |          |refresh_update_level must not be toggled when the DDRC is in reset (core_ddrc_rstn = 0).
     * |        |          |The refresh registers are automatically updated when exiting reset.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::RFSHTMG
     * Offset: 0x64  Refresh Timing Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |t_rfc_min |Minimum Time from Refresh to Refresh or Activate
     * |        |          |tRFC (min)
     * |        |          |When the controller is operating in 1:1 mode, t_rfc_min must be set to RoundUp(tRFCmin/tCK).
     * |        |          |When the controller is operating in 1:2 mode, t_rfc_min must be set to RoundUp(RoundUp(tRFCmin/tCK)/2).
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * |[27:16] |t_rfc_nom_x1_x32|Average Time Interval between Refreshes per Rank
     * |        |          |(Specification: 7.8us for DDR2 and DDR3).
     * |        |          |When the controller is operating in 1:1 mode, set this register to RoundDown(tREFI/tCK)
     * |        |          |When the controller is operating in 1:2 mode, set this register to RoundDown(RoundDown(tREFI/tCK)/2)
     * |        |          |In both the previous cases, if RFSHTMG.t_rfc_nom_x1_sel = 0, divide the previous result by 32 and round down.
     * |        |          |Note:
     * |        |          |u00B7 RFSHTMG.t_rfc_nom_x1_x32 must be greater than 0x1
     * |        |          |u00B7 If RFSHTMG.t_rfc_nom_x1_sel == 1, RFSHTMG.t_rfc_nom_x1_x32 must be greater than RFSHTMG.t_rfc_min
     * |        |          |u00B7 If RFSHTMG.t_rfc_nom_x1_sel == 0, RFSHTMG.t_rfc_nom_x1_x32 * 32 must be greater than RFSHTMG.t_rfc_min
     * |        |          |u00B7 In DDR2/DDR3: RFSHTMG.t_rfc_nom_x1_x32 must be less than or equal to 0xFFE
     * |        |          |Unit: DFI clock cycles or multiples of 32 DFI clock cycles, depending on RFSHTMG.t_rfc_nom_x1_sel.
     * |        |          |Programming Mode: Dynamic - Refresh Related
     * @var UMCTL2_T::CRCPARCTL0
     * Offset: 0xC0  CRC Parity Control Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dfi_alert_err_int_en|DFI Alert Error Interrupt Enable Bit
     * |        |          |If this bit is set, any parity/CRC error detected on the dfi_alert_n input results in an interrupt being set on CRCPARSTAT.dfi_alert_err_int.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |dfi_alert_err_int_clr|DFI Alert Error Interrupt Clear Bit
     * |        |          |Interrupt clear bit for DFI alert error
     * |        |          |If this bit is set, the alert error interrupt on CRCPARSTAT.dfi_alert_err_int is cleared
     * |        |          |uMCTL2 automatically clears this bit.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * |[2]     |dfi_alert_err_cnt_clr|DFI Alert Error Counter Clear Bit
     * |        |          |Indicates the clear bit for DFI alert error counter.
     * |        |          |Asserting this bit clears the DFI alert error counter, CRCPARSTAT.dfi_alert_err_cnt
     * |        |          |uMCTL2 automatically clears this bit.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::CRCPARSTAT
     * Offset: 0xCC  CRC Parity Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |dfi_alert_err_cnt|DFI Alert Error Count
     * |        |          |If a parity/CRC error is detected on dfi_alert_n, this counter be incremented
     * |        |          |This is independent of the setting of CRCPARCTL0.dfi_alert_err_int_en
     * |        |          |It saturates at 0xFFFF, and can be cleared by asserting CRCPARCTL0.dfi_alert_err_cnt_clr.
     * |        |          |Programming Mode: Static
     * |[16]    |dfi_alert_err_int|DFI Alert Error Interrupt
     * |        |          |If a parity/CRC error is detected on dfi_alert_n, and the interrupt is enabled by CRCPARCTL0.dfi_alert_err_int_en, this interrupt bit is set
     * |        |          |It remains set until cleared by CRCPARCTL0.dfi_alert_err_int_clr.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::INIT0
     * Offset: 0xD0  SDRAM Initialization Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |pre_cke_x1024|Number of Cycles to Wait after Reset before Driving CKE High to Start SDRAM Initialization
     * |        |          |Indicates the number of cycles to wait after reset before driving CKE high to start the SDRAM initialization sequence.
     * |        |          |DDR2 specifications typically require this to be programmed for a delay of >= 200 us.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to JEDEC spec value divided by 2, and round it up to the next integer value.
     * |        |          |For DDR3 RDIMMs, this must include the time needed to satisfy tSTAB.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[25:16] |post_cke_x1024|Number of Cycles to Wait after Driving CKE High to Start the SDRAM Initialization
     * |        |          |Indicates the number of cycles to wait after driving CKE high to start the SDRAM initialization sequence.
     * |        |          |DDR2 typically requires a 400 ns delay, requiring this value to be programmed to 2 at all clock speeds.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to JEDEC spec value divided by 2, and round it up to the next integer value.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[31:30] |skip_dram_init|SDRAM Initialization Routine Skipped Enable Bit
     * |        |          |If lower bit is enabled the SDRAM initialization routine is skipped
     * |        |          |The upper bit decides what state the controller starts up in when reset is removed.
     * |        |          |u00B7 00 - SDRAM Initialization routine is run after power-up
     * |        |          |u00B7 01 - SDRAM Initialization routine is skipped after power-up
     * |        |          |The controller starts up in normal Mode
     * |        |          |u00B7 11 - SDRAM Initialization routine is skipped after power-up
     * |        |          |The controller starts up in self-refresh Mode
     * |        |          |u00B7 10 - Reserved
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * @var UMCTL2_T::INIT1
     * Offset: 0xD4  SDRAM Initialization Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |pre_ocd_x32|Wait Period before Driving OCD Complete Command to SDRAM
     * |        |          |Indicates the wait period before driving the OCD complete command to SDRAM.
     * |        |          |There is no known specific requirement for this; it may be set to zero.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[24:16] |dram_rstn_x1024|SDRAM Reset During Initialization sequence
     * |        |          |Indicates the number of cycles to assert SDRAM reset signal during initialization sequence.
     * |        |          |This is only present for designs supporting DDR3 devices
     * |        |          |For use with a Synopsys DDR PHY, this must be set to a minimum of 1.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to JEDEC spec value divided by 2, and round it up to the next integer value.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::INIT3
     * Offset: 0xDC  SDRAM Initialization Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |emr       |Write Value to EMR Register
     * |        |          |DDR2: Indicates the value to write to EMR register
     * |        |          |Bits 9:7 are for OCD and the setting in this register is ignored
     * |        |          |The uMCTL2 sets those bits appropriately.
     * |        |          |DDR3: Value to write to MR1 register Set bit 7 to 0.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[31:16] |mr        |Write Value to MR Register
     * |        |          |DDR2:Indicates the value to write to MR register
     * |        |          |Bit 8 is for DLL and the setting here is ignored
     * |        |          |The uMCTL2 sets this bit appropriately.
     * |        |          |DDR3: Value loaded into MR0 register.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * @var UMCTL2_T::INIT4
     * Offset: 0xE0  SDRAM Initialization Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |emr3      |Write Value to EMR3 Register
     * |        |          |DDR2: Indicates the value to write to EMR3 register.
     * |        |          |DDR3: Value to write to MR3 register.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[31:16] |emr2      |Write Value to EMR2 Register
     * |        |          |DDR2: Indicates the value to write to EMR2 register.
     * |        |          |DDR3: Value to write to MR2 register.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * @var UMCTL2_T::INIT5
     * Offset: 0xE4  SDRAM Initialization Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:16] |dev_zqinit_x32|ZQ initial calibration, tZQINIT.
     * |        |          |Present only in designs configured to support DDR3.
     * |        |          |DDR3 typically requires 512 SDRAM clock cycles.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to JEDEC spec value divided by 2, and round it up to the next integer value.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DIMMCTL
     * Offset: 0xF0  DIMM Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dimm_stagger_cs_en|DIMM Staggering Enable Bit
     * |        |          |Staggering enable for multi-rank accesses (for multi-rank UDIMM, RDIMM and LRDIMM implementations only).
     * |        |          |Note: Even if this bit is set it does not take care of software driven MR commands (through MRCTRL0/MRCTRL1), where software is responsible to send them to separate ranks as appropriate.
     * |        |          |u00B7 1 - DDR2/DDR3 Send all commands to even and odd ranks separately
     * |        |          |u00B7 0 - Do not stagger accesses
     * |        |          |Programming Mode: Static
     * |[1]     |dimm_addr_mirr_en|DIMM Address Mirroring Enable Bit
     * |        |          |Enables address mirroring (for multi-rank UDIMM implementations).
     * |        |          |Some UDIMMs implement address mirroring for odd ranks, which means that the following address, bank address and bank group bits are swapped: (A3, A4), (A5, A6), (A7, A8), (BA0, BA1).
     * |        |          |Setting this bit ensures that, for mode register accesses during the automatic initialization routine, these bits are swapped within the uMCTL2 to compensate for this UDIMM/RDIMM/LRDIMM swapping.
     * |        |          |Note: This has no effect on the address of any other memory accesses, or of software-driven mode register accesses.
     * |        |          |u00B7 1 - For odd ranks, implement address mirroring for MRS commands during initialization
     * |        |          |u00B7 0 - Do not implement address mirroring
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::RANKCTL
     * Offset: 0xF4  Rank Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |max_rank_rd|Maximum Number of Reads that Can be Scheduled Consecutively to Same Rank
     * |        |          |Only present for multi-rank configurations.
     * |        |          |Background: Reads to the same rank can be performed back-to-back
     * |        |          |Reads to different ranks require additional gap dictated by the register RANKCTL.diff_rank_rd_gap.
     * |        |          |This is to avoid possible data bus contention as well as to give PHY enough time to switch the delay when changing ranks.
     * |        |          |The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis; therefore after a read is scheduled, there are few clock cycles (determined by the value on RANKCTL.diff_rank_rd_gap register) in which only reads from the same rank are eligible to be scheduled.
     * |        |          |This prevents reads from other ranks from having fair access to the data bus.
     * |        |          |This parameter represents the maximum number of reads that can be scheduled consecutively to the same rank.
     * |        |          |After this number is reached, a delay equal to RANKCTL.diff_rank_rd_gap is inserted by the scheduler to allow all ranks a fair opportunity to be scheduled.
     * |        |          |Higher numbers increase bandwidth utilization, lower numbers increase fairness.
     * |        |          |This feature can be DISABLED by setting this register to 0
     * |        |          |When set to 0, the controller stays on the same rank as long as commands are available for it.
     * |        |          |Minimum programmable value is 0 (feature disabled) and maximum programmable value is 0xF.
     * |        |          |For uPCTL2, this register field must be set to 0 (feature disabled)
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Static
     * |[7:4]   |diff_rank_rd_gap|Number of Clocks of Gap in Data Responses when Performing Consecutive Reads to Different Ranks
     * |        |          |Only present for multi-rank configurations.
     * |        |          |Indicates the number of clocks of gap in data responses when performing consecutive reads to different ranks.
     * |        |          |This is used to switch the delays in the PHY to match the rank requirements.
     * |        |          |This value must consider both PHY requirement and ODT requirement.
     * |        |          |u00B7 PHY requirement:tphy_rdcsgap (For more information on value of tphy_rdcsgap, see PHY databook)
     * |        |          |u00B7 ODT requirement: The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during reads:
     * |        |          |diff_rank_rd_gap must be a minimum of ODTCFG.rd_odt_hold - BL/2
     * |        |          |when the controller is operating in 1:1 mode, program this to the larger of PHY requirement or ODT requirement.
     * |        |          |When the controller is operating in 1:2 mode, program this to the larger value divided by two and round it up to the next integer.
     * |        |          |After PHY has completed training the value programmed may need to be increased
     * |        |          |For more information, see relevant PHY documentation.
     * |        |          |If a value greater than 0xF is needed, the RANKCTL.diff_rank_rd_gap_msb field must be used as extension
     * |        |          |For DFI 1:2 mode, a maximum value of {diff_rank_rd_gap_msb,diff_rank_rd_gap} < 'h11 is supported
     * |        |          |For DFI 1:1 mode a maximum value of {diff_rank_rd_gap_msb,diff_rank_rd_gap} <= 'h1F is supported.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * |[11:8]  |diff_rank_wr_gap|Number of Clocks of Gap in Data Responses when Performing Consecutive Writes to Different Ranks
     * |        |          |Only present for multi-rank configurations.
     * |        |          |Indicates the number of clocks of gap in data responses when performing consecutive writes to different ranks.
     * |        |          |This is used to switch the delays in the PHY to match the rank requirements
     * |        |          |This value must consider both PHY requirement and ODT requirement.
     * |        |          |u00B7 PHY requirement - tphy_wrcsgap (For more information on value of tphy_wrcsgap, see PHY databook)
     * |        |          |If CRC feature is enabled, must be increased by 1.
     * |        |          |u00B7 ODT requirement - The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during writes.
     * |        |          |For other cases, diff_rank_wr_gap must be a minimum of ODTCFG.wr_odt_hold - BL/2
     * |        |          |When the controller is operating in 1:1 mode, program this to the larger of PHY requirement or ODT requirement.
     * |        |          |If CRC is enabled, the value can be decreased by 2 because the programmed value is internally increased by 1 (it is always 2 in terms of DFI PHY clock cycle as CRC is supported only with 1:2 frequency ratio).
     * |        |          |When the controller is operating in 1:2 mode, program this to the larger value divided by two and round it up to the next integer.
     * |        |          |After PHY has completed training the value programmed may need to be increased
     * |        |          |For more information, see relevant PHY documentation.
     * |        |          |If a value greater than 0xF is needed, the RANKCTL.diff_rank_wr_gap_msb field must be used as extension
     * |        |          |For DFI 1:2 mode, a maximum value of {diff_rank_wr_gap_msb,diff_rank_wr_gap} < 'h11 is supported
     * |        |          |For DFI 1:1 mode a maximum value of {diff_rank_wr_gap_msb,diff_rank_wr_gap} <= 'h1F is supported.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * |[15:12] |max_rank_wr|Maximum Number of Writes that Can be Scheduled Consecutively to Same Rank
     * |        |          |Only present for multi-rank configurations.
     * |        |          |Background: Writes to the same rank can be performed back-to-back
     * |        |          |Writes to different ranks require additional gap dictated by the register RANKCTL.diff_rank_wr_gap.
     * |        |          |This is to avoid possible data bus contention as well as to give PHY enough time to switch the delay when changing ranks.
     * |        |          |The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis; therefore after a write is scheduled, there are few clock cycles (determined by the value on RANKCTL.diff_rank_wr_gap register) in which only writes from the same rank are eligible to be scheduled.
     * |        |          |This prevents writes from other ranks from having fair access to the data bus.
     * |        |          |This parameter represents the maximum number of writes that can be scheduled consecutively to the same rank
     * |        |          |After this number is reached, a delay equal to RANKCTL.diff_rank_wr_gap is inserted by the scheduler to allow all ranks a fair opportunity to be scheduled
     * |        |          |Higher numbers increase bandwidth utilization, lower numbers increase fairness.
     * |        |          |This feature can be DISABLED by setting this register to 0
     * |        |          |When set to 0, the controller stays on the same rank as long as commands are available for it.
     * |        |          |Minimum programmable value is 0 (feature disabled) and maximum programmable value is 0xF.
     * |        |          |For uPCTL2, this register field must be set to 0 (feature disabled)
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Static
     * |[24]    |diff_rank_rd_gap_msb|Different Rank Read Gap Extension Bit
     * |        |          |Only present for multi-rank configurations.
     * |        |          |1-bit extension to be used when RANKCTL.diff_rank_rd_gap field needs to be set to a value greater than 0xF.
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * |[26]    |diff_rank_wr_gap_msb|Different Rank Write Gap Extension Bit
     * |        |          |Only present for multi-rank configurations.
     * |        |          |1-bit extension to be used when RANKCTL.diff_rank_wr_gap field needs to be set to a value greater than 0xF.
     * |        |          |Programming Mode: Quasi-dynamic Group 2
     * @var UMCTL2_T::DRAMTMG0
     * Offset: 0x100  SDRAM Timing Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |t_ras_min |Minimum Time Between Activate and Precharge to the Same Bank (tRAS(min))
     * |        |          |When the controller is operating in 1:1 frequency ratio mode, t_ras_min must be set to RoundUp(tRASmin/tCK)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, 1T mode, t_ras_min must be set to RoundDown(RoundUp(tRASmin/tCK)/2)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, 2T mode, geardown mode or LPDDR4 mode, t_ras min must be set to RoundUp(RoundUp(tRASmin/tCK)/2)
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[14:8]  |t_ras_max |Maximum Time Between Activate and Precharge to the Same Bank (tRAS(max))
     * |        |          |This is the maximum time that a page can be kept open Minimum value of this register is 1
     * |        |          |Zero is invalid.
     * |        |          |When the controller is operating in 1:1 frequency ratio mode, t_ras_max must be set to RoundDown(tRAS(max)/tCK/1024).
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, t_ras_max must be set to RoundDown((RoundDown(tRAS(max)/tCK/1024)-1)/2).
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[21:16] |t_faw     |Four Active Window for 2 Kbytes Page Size
     * |        |          |tFAW - valid only when 8 or more banks(or banks x bank groups) are present.
     * |        |          |In 8-bank design, at most 4 banks must be activated in a rolling window of tFAW cycles.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tFAW/2) and round up to next integer value.
     * |        |          |In a 4-bank design, set this register to 0x1 independent of the 1:1/1:2 frequency mode.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[30:24] |wr2pre    |Minimum Time Between Write and Precharge to Same Bank.
     * |        |          |Specifications: WL + BL/2 + tWR = approximately 8 cycles + 15 ns = 14 clocks @400 MHz and less for lower frequencies.
     * |        |          |where:
     * |        |          |u00B7 WL: Write latency
     * |        |          |u00B7 BL: Burst length
     * |        |          |This must match the value programmed in the BL bit of the mode register to the SDRAM
     * |        |          |BST (burst terminate) is not supported at present
     * |        |          |u00B7 tWR: Write recovery time. This comes directly from the SDRAM specification
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, 1T mode, divide the previous value by 2
     * |        |          |No rounding up.
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, 2T mode, geardown mode, divide the previous value by 2 and round it up to the next integer value.
     * |        |          |Note that, depending on the PHY, if using LRDIMM, it may be necessary to adjust the value of this parameter to compensate for the extra cycle of latency through the LRDIMM.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG1
     * Offset: 0x104  SDRAM Timing Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |t_rc      |Minimum Time Between Activates to Same Bank (tRC)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tRC/2) and round up to next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[13:8]  |rd2pre    |Minimum Time from Read to Precharge of Same Bank (tRTP)
     * |        |          |u00B7 DDR2 - tAL + BL/2 + max(RoundUp(tRTP/tCK), 2) - 2
     * |        |          |u00B7 DDR3 - tAL + max (RoundUp(tRTP/tCK), 4)
     * |        |          |When the controller is operating in 1:2 mode, 1T mode, divide the previous value by 2. No rounding up.
     * |        |          |When the controller is operating in 1:2 mode, 2T mode, geardown mode, divide the previous value by 2 and round it up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
     * |[20:16] |t_xp      |Minimum Time after Power-Down Exit to Any Operation (tXP)
     * |        |          |For DDR3, this must be programmed to tXPDLL if slow power down exit is selected in MR0[12].
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tXP/2) and round it up to the next integer value.
     * |        |          |Units: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG2
     * Offset: 0x108  SDRAM Timing Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |wr2rd     |Minimum Time from Write Command to Read Command
     * |        |          |This must include time for bus turn-around and all PHY and system requirements.
     * |        |          |After the PHY has completed training, the value programmed may need to be increased
     * |        |          |Please see the relevant PHY databook for details of what should be included here.
     * |        |          |The following calculations are minimum values, and do not include the PHY/system requirements mentioned above:
     * |        |          |DDR2/DDR3: CWL + BL/2 + tWTR
     * |        |          |Where:
     * |        |          |u00B7 CWL: CAS write latency
     * |        |          |u00B7 WL: Write latency
     * |        |          |u00B7 BL: Burst length
     * |        |          |This must match the value programmed in the BL bit of the mode register to the SDRAM
     * |        |          |u00B7 tWTR: Internal write to read command delay. This comes directly from the SDRAM specification
     * |        |          |Add one extra cycle for LPDDR2/LPDDR3/LPDDR4 operation.
     * |        |          |When the controller is operating in 1:2 mode, divide the value calculated using the previous equation by 2, and round it up to next integer.
     * |        |          |If your configuration has RANKCTL1.wr2rd_dr, write to read bus turn-around between different physical ranks are controlled by RANKCTL1.wr2rd_dr.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
     * |[13:8]  |rd2wr     |Minimum Time from Read Command to Write Command
     * |        |          |This must include time for bus turnaround (both within ranks and between ranks) and all PHY and system requirements.
     * |        |          |After the PHY has completed training, the value programmed may need to be increased
     * |        |          |Please see the relevant PHY databook for details of what should be included here.
     * |        |          |The following calculations are minimum values, and do not include the PHY/system requirements mentioned above:
     * |        |          |DDR2/3 : RL + BL/2 + 2 - WL
     * |        |          |Where:
     * |        |          |u00B7 WL: Write latency
     * |        |          |u00B7 BL: Burst length
     * |        |          |This must match the value programmed in the BL bit of the mode register to the SDRAM
     * |        |          |u00B7 RL: Read latency = CAS latency
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, divide the value calculated using the previous equation by 2, and round it up to next integer.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG3
     * Offset: 0x10C  SDRAM Timing Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |t_mod     |Number of Cycles Between Load Mode Command and Following Non-Load Mode Command (tMOD)
     * |        |          |Used only in DDR3.
     * |        |          |Indicates the number of cycles between load mode command and following non-load mode command.
     * |        |          |If CAL mode is enabled (DFITMG1.dfi_t_cmd_lat > 0), tCAL (=DFITMG1.dfi_cmd_lat) must be added to the previous calculations.
     * |        |          |Set to tMOD if controller is operating in 1:1 frequency ratio mode, or tMOD/2 (rounded up to next integer) if controller is operating in 1:2 frequency ratio mode.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[17:12] |t_mrd     |Number of Cycles to Wait after a Mode Register Write or Read (tMRD)
     * |        |          |Depending on the connected SDRAM, tMRD represents:
     * |        |          |u00B7 DDR2: Time from MRS to any command
     * |        |          |u00B7 DDR3: Time from MRS to MRS command
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tMRD/2) and round it up to the next integer value.
     * |        |          |If CAL mode is enabled (DFITMG1.dfi_t_cmd_lat > 0), tCAL (=DFITMG1.dfi_cmd_lat) must be added to the previous calculations.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG4
     * Offset: 0x110  SDRAM Timing Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |t_rp      |Minimum Time from Single-Bank Precharge to Activate of Same Bank (tRP)
     * |        |          |When the controller is operating in 1:1 frequency ratio mode, t_rp must be set to RoundUp(tRP/tCK).
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, t_rp must be set to RoundDown(RoundUp(tRP/tCK)/2) + 1.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[11:8]  |t_rrd     |Minimum Time Between Activates from Bank "a" to Bank "b" for Others (tRRD)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tRRD/2) and round it up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[19:16] |t_ccd     |Minimum Time Between Two Reads or Two Writes for Others (tCCD)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (tCCD_L/2 or tCCD/2) and round it up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[28:24] |t_rcd     |Minimum Time from Activate to Read or Write Command to Same Bank (tRCD - tAL)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to ((tRCD - tAL)/2) and round it up to the next integer value.
     * |        |          |Minimum value allowed for this register is 1, which implies minimum (tRCD - tAL) value to be 2 when the controller is operating in 1:2 frequency ratio mode.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG5
     * Offset: 0x114  SDRAM Timing Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |t_cke     |Minimum Number of Cycles of CKE HIGH/LOW During Power-Down and Self-Refresh.
     * |        |          |u00B7 DDR2/DDR3: Set this to tCKE value
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to (value described above)/2 and round it up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[13:8]  |t_ckesr   |Minimum CKE Low Width for Self-Refresh or Self-Refresh Power Down Entry to Exit Timing in Memory Clock Cycles.
     * |        |          |Recommended settings:
     * |        |          |u00B7 DDR2 : tCKE
     * |        |          |u00B7 DDR3 : tCKE + 1
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to recommended value divided by two and round it up to next integer.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[22:16] |t_cksre   |Time After Self-Refresh Down Entry that CK is Maintained as a Valid Clock.
     * |        |          |Specifies the clock disable delay after SRE.
     * |        |          |Recommended settings:
     * |        |          |u00B7 DDR2 : 1
     * |        |          |u00B7 DDR3 : Max (10 ns, 5 tCK)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to recommended value divided by two and round it up to next integer.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[27:24] |t_cksrx   |Time Before Self-Refresh Exit that CK is Maintained as a Valid Clock Before Issuing SRX.
     * |        |          |Specifies the clock stable time before SRX.
     * |        |          |Recommended settings:
     * |        |          |u00B7 DDR2 : 1
     * |        |          |u00B7 DDR3 : tCKSRX
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to recommended value divided by two and round it up to next integer.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG8
     * Offset: 0x120  SDRAM Timing Register 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |t_xs_x32  |Exit Self-Refresh to Commands Not Requiring a Locked DLL (tXS)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to the previous value divided by 2 and round up to next integer value.
     * |        |          |Note: Used only for DDR2 and DDR3 SDRAMs.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[14:8]  |t_xs_dll_x32|Exit Self-Refresh to Commands Requiring a Locked DLL (tXSDLL)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to the previous value divided by 2 and round up to next integer value.
     * |        |          |Note: Used only for DDR2 and DDR3 SDRAMs.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * @var UMCTL2_T::DRAMTMG15
     * Offset: 0x13C  SDRAM Timing Register 15
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |t_stab_x32|Stabilization time (tSTAB)
     * |        |          |It is required in the following two cases for DDR3 RDIMM:
     * |        |          |u00B7 When exiting power saving mode, if the clock is stopped, after re-enabling it the clock must be stable for a time specified by tSTAB
     * |        |          |u00B7 After issuing control words that refers to clock timing (Specification: 6us for DDR3)
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to recommended value divided by two and round it up to next integer.
     * |        |          |Unit: Multiples of 32 DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[31]    |en_dfi_lp_t_stab|Enable Bit for Using tSTAB When Exiting DFI LP
     * |        |          |u00B7 1 - Enable using tSTAB when exiting DFI LP
     * |        |          |This must be set when the PHY is stopping the clock during DFI LP to save maximum power.
     * |        |          |u00B7 0 - Disable using tSTAB when exiting DFI LP.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * @var UMCTL2_T::ZQCTL0
     * Offset: 0x180  ZQ Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |t_zq_short_nop|Number of DFI Clock Cycles of NOP Required After a ZQCS (ZQ Calibration Short)/MPC(ZQ Latch) Command is Issued to SDRAM
     * |        |          |tZQCS for DDR3
     * |        |          |When the controller is operating in 1:2 frequency ratio mode, program this to tZQCS/2 and round it up to the next integer value.
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[26:16] |t_zq_long_nop|Number of DFI Clock Cycles of NOP Required After a ZQCL (ZQ Calibration Long)/MPC (ZQ Start) Command is Issued to SDRAM
     * |        |          |tZQoper for DDR3
     * |        |          |When the controller is operating in 1:2 frequency ratio mode:
     * |        |          |DDR3: program this to tZQoper/2 and round it up to the next integer value.
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[29]    |zq_resistor_shared|ZQ Resistor Shared Between Ranks
     * |        |          |u00B7 1 - Denotes that ZQ resistor is shared between ranks
     * |        |          |Means ZQinit/ZQCL/ZQCS/MPC(ZQ calibration) commands are sent to one rank at a time with tZQinit/tZQCL/tZQCS/tZQCAL/tZQLAT timing met between commands so that commands to different ranks do not overlap
     * |        |          |u00B7 0 - ZQ resistor is not shared
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Programming Mode: Static
     * |[30]    |dis_srx_zqcl|Disable Issuing of ZQCL/MPC(ZQ Calibration) Command at Self-Refresh/SR-Power Down Exit
     * |        |          |u00B7 1 - Disable issuing of ZQCL/MPC(ZQ calibration) command at self-refresh/SR-Power down exit
     * |        |          |Only applicable when run in DDR3 mode
     * |        |          |u00B7 0 - Enable issuing of ZQCL/MPC(ZQ calibration) command at self-refresh/SR-Power down exit
     * |        |          |Only applicable when run in DDR3 mode
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[31]    |dis_auto_zq|Disable Auto Generation of ZQCS/MPC(ZQ Calibration) Command
     * |        |          |u00B7 1 - Disable uMCTL2 generation of ZQCS/MPC(ZQ calibration) command
     * |        |          |Register DBGCMD.zq_calib_short can be used instead to issue ZQ calibration request from APB module
     * |        |          |u00B7 0 - Internally generate ZQCS/MPC(ZQ calibration) commands based on ZQCTL1.t_zq_short_interval_x1024
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::ZQCTL1
     * Offset: 0x184  ZQ Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[19:0]  |t_zq_short_interval_x1024|Average Interval to Wait Between Automatically Issuing ZQCS
     * |        |          |Average Interval to Wait Between Automatically Issuing ZQCS (ZQ Calibration Short)/MPC(ZQ Calibration) Commands to DDR3 Devices.
     * |        |          |Meaningless, if ZQCTL0.dis_auto_zq=1.
     * |        |          |This is only present for designs supporting DDR3 devices.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DFITMG0
     * Offset: 0x190  DFI Timing Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |dfi_tphy_wrlat|Write latency
     * |        |          |Number of clocks from the write command to write data enable (dfi_wrdata_en)
     * |        |          |This corresponds to the DFI timing parameter tphy_wrlat.
     * |        |          |Refer to PHY specification for correct value.
     * |        |          |Unit: DFI clock cycles or DFI PHY clock cycles, depending on DFITMG0.dfi_wrdata_use_dfi_phy_clk.
     * |        |          |Programming Mode: Quasi-dynamic Group 2, Group 4
     * |[13:8]  |dfi_tphy_wrdata|Number of Clock Cycles Between When dfi_wrdata_en is Asserted to When the Associated Write Data is Driven on the dfi_wrdata Signal
     * |        |          |This corresponds to the DFI timing parameter tphy_wrdata
     * |        |          |For more information on correct value, see PHY specification
     * |        |          |Note, maximum supported value is 8.
     * |        |          |Unit: DFI clock cycles or DFI PHY clock cycles, depending on DFITMG0.dfi_wrdata_use_dfi_phy_clk.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[15]    |dfi_wrdata_use_dfi_phy_clk|dfi_wrdata_en/dfi_wrdata/dfi_wrdata_mask is Generated Using HDR (DFI Clock) or SDR (DFI PHY Clock) Values
     * |        |          |Selects whether value in DFITMG0.dfi_tphy_wrlat is in terms of HDR (DFI clock) or SDR (DFI PHY clock) cycles.
     * |        |          |Selects whether value in DFITMG0.dfi_tphy_wrdata is in terms of HDR (DFI clock) or SDR (DFI PHY clock) cycles.
     * |        |          |u00B7 0 in terms of HDR (DFI clock) cycles
     * |        |          |Refer to PHY specification for correct value
     * |        |          |If using a Synopsys DWC DDR3/2 PHY, this field must be set to 0.
     * |        |          |Programming Mode: Static
     * |[22:16] |dfi_t_rddata_en|Time from the Assertion of a Read Command on the DFI Interface to the Assertion of the dfi_rddata_en Signal
     * |        |          |Refer to PHY specification for correct value.
     * |        |          |This corresponds to the DFI parameter trddata_en.
     * |        |          |Unit: DFI clock cycles or DFI PHY clock cycles, depending on DFITMG0.dfi_rddata_use_dfi_phy_clk.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * |[23]    |dfi_rddata_use_dfi_phy_clk|dfi_rddata_en/dfi_rddata/dfi_rddata_valid is Generated Using HDR (DFI Clock) or SDR (DFI PHY Clock) Values
     * |        |          |Selects whether value in DFITMG0.dfi_t_rddata_en is in terms of HDR (DFI clock) or SDR (DFI PHY clock) cycles:
     * |        |          |u00B7 0 in terms of HDR (DFI clock) cycles
     * |        |          |Refer to PHY specification for correct value.
     * |        |          |If using a Synopsys DWC DDR3/2 PHY, this field must be set to 0.
     * |        |          |Programming Mode: Static
     * |[28:24] |dfi_t_ctrl_delay|Number of DFI Clock Cycles After an Assertion or De-assertion of the DFI Control Signals that the Control Signals at the PHY-DRAM Interface Reflect the Assertion or De-assertion
     * |        |          |If the DFI clock and the memory clock are not phase-aligned, this timing parameter must be rounded up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * @var UMCTL2_T::DFITMG1
     * Offset: 0x194  DFI Timing Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |dfi_t_dram_clk_enable|Number of DFI Clock Cycles from the De-assertion of the dfi_dram_clk_disable Signal on the DFI Until the First Valid Rising Edge of the Clock to the DRAM Memory Devices, at the PHY-DRAM Boundary
     * |        |          |If the DFI clock and the memory clock are not phase aligned, this timing parameter must be rounded up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[12:8]  |dfi_t_dram_clk_disable|Number of DFI Clock Cycles from the Assertion of the dfi_dram_clk_disable Signal on the DFI Until the Clock to the DRAM Memory Devices, at the PHY-DRAM Boundary, Maintains a Low Value
     * |        |          |If the DFI clock and the memory clock are not phase aligned, this timing parameter must be rounded up to the next integer value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[20:16] |dfi_t_wrdata_delay|Number of DFI Clock Cycles Between When the dfi_wrdata_en Signal is Asserted and When the Corresponding Write Data Transfer is Completed on the DRAM Bus
     * |        |          |This corresponds to the DFI timing parameter twrdata_delay.
     * |        |          |For more information on correct value, see PHY specification.
     * |        |          |For DFI 2.1 PHY, set to tphy_wrdata + (delay of DFI write data to the DRAM).
     * |        |          |Value to be programmed is in terms of DFI clocks, not PHY clocks.
     * |        |          |In FREQ_RATIO=2, divide PHY's value by 2 and round up to next integer.
     * |        |          |If using DFITMG0.dfi_wrdata_use_dfi_phy_clk=1, add 1 to the value.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * |[25:24] |dfi_t_parin_lat|Number of DFI PHY Clock Cycles Between When the dfi_cs signal is Asserted and When the Associated dfi_parity_in Signal is Driven
     * |        |          |Unit: DFI PHY clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 4
     * @var UMCTL2_T::DFILPCFG0
     * Offset: 0x198  DFI Low Power Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dfi_lp_en_pd|Enable Bit for DFI Low Power Interface Handshaking During Power Down Entry/Exit
     * |        |          |u00B7 0 - Disabled
     * |        |          |u00B7 1 - Enabled
     * |        |          |Programming Mode: Static
     * |[7:4]   |dfi_lp_wakeup_pd|Value in DFI Clock Cycles to Drive on dfi_lp_wakeup Signal When Power-Down Mode is Entered
     * |        |          |Determines the DFI's tlp_wakeup time:
     * |        |          |u00B7 0x0 - 16 cycles
     * |        |          |u00B7 0x1 - 32 cycles
     * |        |          |u00B7 0x2 - 64 cycles
     * |        |          |u00B7 0x3 - 128 cycles
     * |        |          |u00B7 0x4 - 256 cycles
     * |        |          |u00B7 0x5 - 512 cycles
     * |        |          |u00B7 0x6 - 1024 cycles
     * |        |          |u00B7 0x7 - 2048 cycles
     * |        |          |u00B7 0x8 - 4096 cycles
     * |        |          |u00B7 0x9 - 8192 cycles
     * |        |          |u00B7 0xA - 16384 cycles
     * |        |          |u00B7 0xB - 32768 cycles
     * |        |          |u00B7 0xC - 65536 cycles
     * |        |          |u00B7 0xD - 131072 cycles
     * |        |          |u00B7 0xE - 262144 cycles
     * |        |          |u00B7 0xF - Unlimited
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[8]     |dfi_lp_en_sr|Enable Bit for DFI Low Power Interface Handshaking During Self-Refresh Entry/Exit
     * |        |          |u00B7 0 - Disabled
     * |        |          |u00B7 1 - Enabled
     * |        |          |Programming Mode: Static
     * |[15:12] |dfi_lp_wakeup_sr|Value in DFI Clock Cycles to Drive on dfi_lp_wakeup Signal When Self-Refresh Mode is Entered
     * |        |          |Determines the DFI's tlp_wakeup time:
     * |        |          |u00B7 0x0 - 16 cycles
     * |        |          |u00B7 0x1 - 32 cycles
     * |        |          |u00B7 0x2 - 64 cycles
     * |        |          |u00B7 0x3 - 128 cycles
     * |        |          |u00B7 0x4 - 256 cycles
     * |        |          |u00B7 0x5 - 512 cycles
     * |        |          |u00B7 0x6 - 1024 cycles
     * |        |          |u00B7 0x7 - 2048 cycles
     * |        |          |u00B7 0x8 - 4096 cycles
     * |        |          |u00B7 0x9 - 8192 cycles
     * |        |          |u00B7 0xA - 16384 cycles
     * |        |          |u00B7 0xB - 32768 cycles
     * |        |          |u00B7 0xC - 65536 cycles
     * |        |          |u00B7 0xD - 131072 cycles
     * |        |          |u00B7 0xE - 262144 cycles
     * |        |          |u00B7 0xF - Unlimited
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[28:24] |dfi_tlp_resp|Setting in DFI Clock Cycles for DFI's tlp_resp Time
     * |        |          |Same value is used for both Power Down, self-refresh, Deep Power Down and Maximum Power Saving modes.
     * |        |          |For more information on recommended values, see PHY databook
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DFIUPD0
     * Offset: 0x1A0  DFI Update Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |dfi_t_ctrlup_min|Minimum Number of DFI Clock Cycles that the dfi_ctrlupd_req Signal must be Asserted The uMCTL2 expects the PHY to respond within this time. If the PHY does not respond, the uMCTL2 de-asserts dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles. Lowest value to assign to this variable is 0x1.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[25:16] |dfi_t_ctrlup_max|Maximum Number of DFI Clock Cycles that the dfi_ctrlupd_req Signal Can Assert
     * |        |          |Lowest value to assign to this variable is 0x40.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[29]    |ctrlupd_pre_srx|dfi_ctrlupd_req Selection at SRX
     * |        |          |u00B7 0 - Send ctrlupd after SRX
     * |        |          |u00B7 1 - Send ctrlupd before SRX If DFIUPD0.dis_auto_ctrlupd_srx=1, this register has no impact, because no dfi_ctrlupd_req is issued when SRX.
     * |        |          |Programming Mode: Static
     * |[30]    |dis_auto_ctrlupd_srx|Disable Bit for Automatic dfi_ctrlupd_req Generation by uMCTL2 at Self-Refresh Exit
     * |        |          |When '1', disable the automatic dfi_ctrlupd_req generation by the uMCTL2 at self-refresh exit.
     * |        |          |When '0', uMCTL2 issues a dfi_ctrlupd_req before or after exiting self-refresh, depending on DFIUPD0.ctrlupd_pre_srx.
     * |        |          |Programming Mode: Static
     * |[31]    |dis_auto_ctrlupd|Disable Bit for Automatic dfi_ctrlupd_req Generation by uMCTL2
     * |        |          |When '1', disable the automatic dfi_ctrlupd_req generation by the uMCTL2.
     * |        |          |The controller must issue the dfi_ctrlupd_req signal using register DBGCMD.ctrlupd.
     * |        |          |When '0', uMCTL2 issues dfi_ctrlupd_req periodically.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::DFIUPD1
     * Offset: 0x1A4  DFI Update Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |dfi_t_ctrlupd_interval_max_x1024|Maximum Amount of Time Between uMCTL2 Initiated DFI Update Requests
     * |        |          |This timer resets with each update request; when the timer expires dfi_ctrlupd_req is sent and traffic is blocked until the dfi_ctrlupd_ackx is received.
     * |        |          |PHY can use this idle time to recalibrate the delay lines to the DLLs
     * |        |          |The DFI controller update is also used to reset PHY FIFO pointers in case of data capture errors.
     * |        |          |Updates are required to maintain calibration over PVT, but frequent updates may impact performance
     * |        |          |Minimum allowed value for this field is 1.
     * |        |          |Note: Value programmed for DFIUPD1.dfi_t_ctrlupd_interval_max_x1024 must be greater than DFIUPD1.dfi_t_ctrlupd_interval_min_x1024.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * |[23:16] |dfi_t_ctrlupd_interval_min_x1024|Minimum Amount of Time Between uMCTL2 Initiated DFI Update Requests (which is Executed whenever the uMCTL2 is Idle)
     * |        |          |Set this number higher to reduce the frequency of update requests, which can have a small impact on the latency of the first read request when the uMCTL2 is idle.
     * |        |          |The minimum allowed value for this field is 1.
     * |        |          |Unit: Multiples of 1024 DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DFIUPD2
     * Offset: 0x1A8  DFI Update Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31]    |dfi_phyupd_en|Enable Bit for Acknowledging PHY-Initiated Updates
     * |        |          |u00B7 0 - Disabled
     * |        |          |u00B7 1 - Enabled
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DFIMISC
     * Offset: 0x1B0  DFI Miscellaneous Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dfi_init_complete_en|PHY Initialization Complete Enable Bit
     * |        |          |When asserted the dfi_init_complete signal can be used to trigger SDRAM initialisation
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[4]     |ctl_idle_en|Enable Bit for ctl_idle Signal
     * |        |          |It is non-DFI related pin specific to certain Synopsys PHYs.
     * |        |          |For more information on ctl_idle functionality, see signal description of ctl_idle signal.
     * |        |          |Programming Mode: Static
     * |[5]     |dfi_init_start|PHY Initialization Start Request Signal
     * |        |          |When asserted it triggers the PHY init start request.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[12:8]  |dfi_frequency|Operating Frequency of System
     * |        |          |The number of supported frequencies and the mapping of signal values to clock frequencies are defined by the PHY.
     * |        |          |Programming Mode: Quasi-dynamic Group 1
     * @var UMCTL2_T::DFISTAT
     * Offset: 0x1BC  DFI Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dfi_init_complete|Status flag when the DFI initialization has been completed
     * |        |          |The DFI INIT triggered by dfi_init_start signal and then the dfi_init_complete flag is polled to know when the initialization is done.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |dfi_lp_ack|Value of the dfi_lp_ack to the controller
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::DFIPHYMSTR
     * Offset: 0x1C4  DFI PHY Master
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dfi_phymstr_en|PHY Master Interface Enable Bit
     * |        |          |u00B7 0 - Disabled
     * |        |          |u00B7 1 - Enabled
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP0
     * Offset: 0x200  Address Map Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |addrmap_cs_bit0|HIF Address Bits for Rank Address Bit 0
     * |        |          |Valid Range: 0 to 29, and 31
     * |        |          |Internal Base: 6
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 31 and then rank address bit 0 is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP1
     * Offset: 0x204  Address Map Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |addrmap_bank_b0|HIF Address Bits for Bank Address Bit 0
     * |        |          |Valid Range: 0 to 32, and 63
     * |        |          |Internal Base: 2
     * |        |          |The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 63 and then bank address bit 0 is set to 0.
     * |        |          |Programming Mode: Static
     * |[13:8]  |addrmap_bank_b1|HIF Address Bits for Bank Address Bit 1
     * |        |          |Valid Range: 0 to 32, and 63
     * |        |          |Internal Base: 3
     * |        |          |The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 63 and then bank address bit 1 is set to 0.
     * |        |          |Programming Mode: Static
     * |[21:16] |addrmap_bank_b2|HIF Address Bits for Bank Address Bit 2
     * |        |          |Valid Range: 0 to 31, and 63
     * |        |          |Internal Base: 4
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 63 and then bank address bit 2 is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP2
     * Offset: 0x208  Address Map Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_col_b2|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 2
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 3
     * |        |          |Valid Range: 0 to 7
     * |        |          |Internal Base: 2
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |In our chip, we configure hardware parameter "MEMC_BURST_LENGTH" to equal to 8 and Full Bus Width (MSTR.data_bus_width==00), it is recommended to program this to 0 so that HIF[2] maps to column address bit 2.
     * |        |          |Programming Mode: Static
     * |[12:8]  |addrmap_col_b3|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 3
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 4
     * |        |          |Valid Range: 0 to 7.
     * |        |          |Internal Base: 3
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |Programming Mode: Static
     * |[19:16] |addrmap_col_b4|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 4
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 5
     * |        |          |Valid Range: 0 to 7, and 15
     * |        |          |Internal Base: 4
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * |[27:24] |addrmap_col_b5|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 5
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 6
     * |        |          |Valid Range: 0 to 7, and 15
     * |        |          |Internal Base: 5
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP3
     * Offset: 0x20C  Address Map Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |addrmap_col_b6|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 6.
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 7.
     * |        |          |Valid Range: 0 to 7, and 31.
     * |        |          |Internal Base: 6
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * |[12:8]  |addrmap_col_b7|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 7
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 8
     * |        |          |Valid Range: 0 to 7, and 31.
     * |        |          |Internal Base: 7
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * |[20:16] |addrmap_col_b8|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 8
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 9
     * |        |          |Valid Range: 0 to 7, and 31.
     * |        |          |Internal Base: 8
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |Note: Per JEDEC DDR2/3 specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * |[28:24] |addrmap_col_b9|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 9
     * |        |          |u00B7 Half bus width mode - Selects the HIF address bit used as column address bit 11
     * |        |          |Valid Range: 0 to 7.
     * |        |          |Internal Base: 9
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |Note: Per JEDEC DDR2/3 specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP4
     * Offset: 0x210  Address Map Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |addrmap_col_b10|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode: Selects the HIF address bit used as column address bit 11
     * |        |          |u00B7 Half bus width mode: Selects the HIF address bit used as column address bit 13
     * |        |          |Valid Range: 0 to 7, and 31.
     * |        |          |Internal Base: 10
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |Note: Per JEDEC DDR2/3 specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * |[12:8]  |addrmap_col_b11|HIF Address Bit for Column Address Bit for Three Bus Width Modes
     * |        |          |u00B7 Full bus width mode - Selects the HIF address bit used as column address bit 13
     * |        |          |u00B7 Half bus width mode - UNUSED
     * |        |          |See later in this description for value you need to set to make it unused
     * |        |          |Valid Range: 0 to 7, and 31.
     * |        |          |Internal Base: 11
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |Note: Per JEDEC DDR2/3 specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
     * |        |          |If unused, set to 31 and then this column address bit is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP5
     * Offset: 0x214  Address Map Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_row_b0|HIF Address Bits for Row Address Bit 0
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 6
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
     * |        |          |Programming Mode: Static
     * |[11:8]  |addrmap_row_b1|HIF Address Bits for Row Address Bit 1
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 7
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
     * |        |          |Programming Mode: Static
     * |[19:16] |addrmap_row_b2_10|HIF Address Bits for Row Address Bits 2 to 10
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 8 (for row address bit 2), 9 (for row address bit 3), 10 (for row address bit 4) and so on, increasing to 16 (for row address bit 10)
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
     * |        |          |When set to 15, the values of row address bits 2 to 10 are defined by registers ADDRMAP9, ADDRMAP10, ADDRMAP11.
     * |        |          |Programming Mode: Static
     * |[27:24] |addrmap_row_b11|HIF Address Bits for Row Address Bit 11
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 17
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then row address bit 11 is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP6
     * Offset: 0x218  Address Map Register 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_row_b12|HIF Address Bit for Row Address Bit 12
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 18
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then row address bit 12 is set to 0.
     * |        |          |Programming Mode: Static
     * |[11:8]  |addrmap_row_b13|HIF Address Bit for Row Address Bit 13
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 19
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then row address bit 13 is set to 0.
     * |        |          |Programming Mode: Static
     * |[19:16] |addrmap_row_b14|HIF Address Bit for Row Address Bit 14
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 20
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then row address bit 14 is set to 0.
     * |        |          |Programming Mode: Static
     * |[27:24] |addrmap_row_b15|HIF Address Bit for Row Address Bit 15
     * |        |          |Valid Range: 0 to 11, and 15
     * |        |          |Internal Base: 21
     * |        |          |The selected HIF address bit is determined by adding the internal base to the value of this field.
     * |        |          |If unused, set to 15 and then row address bit 15 is set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP9
     * Offset: 0x224  Address Map Register 9
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_row_b2|HIF Address Bits for Row Address Bit 2
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 8
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[11:8]  |addrmap_row_b3|HIF Address Bits for Row Address Bit 3
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 9
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[19:16] |addrmap_row_b4|HIF Address Bits for Row Address Bit 4
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 10
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[27:24] |addrmap_row_b5|HIF Address Bits for Row Address Bit 5
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 11
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP10
     * Offset: 0x228  Address Map Register 10
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_row_b6|HIF Address Bits for Row Address Bit 6
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 12
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[11:8]  |addrmap_row_b7|HIF Address Bits for Row Address Bit 7
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 13
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[19:16] |addrmap_row_b8|HIF Address Bits for Row Address Bit 8
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 14
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * |[27:24] |addrmap_row_b9|HIF Address Bits for Row Address Bit 9
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 15
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ADDRMAP11
     * Offset: 0x22C  Address Map Register 11
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |addrmap_row_b10|HIF Address Bits for Row Address Bit 10
     * |        |          |Valid Range: 0 to 11
     * |        |          |Internal Base: 16
     * |        |          |The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field
     * |        |          |This register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to value 15.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::ODTCFG
     * Offset: 0x240  ODT Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:2]   |rd_odt_delay|Delay in DFI PHY Clock Cycles from Issuing a Read Command to Setting ODT Values Associated with that Command
     * |        |          |ODT setting must remain constant for the entire time that DQS is driven by the uMCTL2.
     * |        |          |Recommended values:
     * |        |          |DDR2:
     * |        |          |u00B7 CL + AL - 4 (not DDR2-1066),
     * |        |          |u00B7 CL + AL - 5 (DDR2-1066) If (CL + AL - 4 < 0), uMCTL2 does not support ODT for read operation.
     * |        |          |DDR3:
     * |        |          |u00B7 CL - CWL
     * |        |          |Unit: DFI PHY clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * |[11:8]  |rd_odt_hold|DFI PHY Clock Cycles to Hold ODT for a Read Command
     * |        |          |The minimum supported value is 2.
     * |        |          |Recommended values:
     * |        |          |DDR2:
     * |        |          |u00B7 BL8 - 0x6 (not DDR2-1066), 0x7 (DDR2-1066)
     * |        |          |u00B7 BL4 - 0x4 (not DDR2-1066), 0x5 (DDR2-1066)
     * |        |          |DDR3:
     * |        |          |u00B7 BL8 - 0x6
     * |        |          |Unit: DFI PHY clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * |[20:16] |wr_odt_delay|Delay in DFI PHY Clock Cycles from Issuing a Write Command to Setting ODT Values Associated with that Command
     * |        |          |ODT setting must remain constant for the entire time that DQS is driven by the uMCTL2.
     * |        |          |Recommended values:
     * |        |          |DDR2:
     * |        |          |u00B7 CWL + AL - 3 (DDR2-400/533/667),
     * |        |          |u00B7 CWL + AL - 4 (DDR2-800),
     * |        |          |u00B7 CWL + AL - 5 (DDR2-1066) If (CWL + AL - 3 < 0), uMCTL2 does not support ODT for write operation.
     * |        |          |DDR3:
     * |        |          |u00B7 0x0
     * |        |          |Unit: DFI PHY clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * |[27:24] |wr_odt_hold|DFI PHY Clock Cycles to Hold ODT for a Write Command
     * |        |          |The minimum supported value is 2.
     * |        |          |Recommended values:
     * |        |          |DDR2:
     * |        |          |u00B7 BL8 - 0x5 (DDR2-400/533/667), 0x6 (DDR2-800), 0x7 (DDR2-1066)
     * |        |          |u00B7 BL4 - 0x3 (DDR2-400/533/667), 0x4 (DDR2-800), 0x5 (DDR2-1066)
     * |        |          |DDR3:
     * |        |          |u00B7 BL8 - 0x6
     * |        |          |Unit: DFI PHY clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 1, Group 4
     * @var UMCTL2_T::ODTMAP
     * Offset: 0x244  ODT/Rank Map Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |rank0_wr_odt|Remote ODTs Must be Turned on During a Write to Rank 0.
     * |        |          |Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
     * |        |          |Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, and so on.
     * |        |          |For each rank, set its bit to 1 to enable its ODT.
     * |        |          |Programming Mode: Static
     * |[5:4]   |rank0_rd_odt|Remote ODTs Must be Turned on During a Read from Rank 0
     * |        |          |Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
     * |        |          |Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, and so on.
     * |        |          |For each rank, set its bit to 1 to enable its ODT.
     * |        |          |Programming Mode: Static
     * |[9:8]   |rank1_wr_odt|Remote ODTs Must be Turned on During a Write to Rank 1
     * |        |          |Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
     * |        |          |Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, and so on.
     * |        |          |For each rank, set its bit to 1 to enable its ODT.
     * |        |          |Present only in configurations that have 2 or more ranks.
     * |        |          |Programming Mode: Static
     * |[13:12] |rank1_rd_odt|Remote ODTs Must be Turned on During a Read from Rank 1
     * |        |          |Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
     * |        |          |Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, and so on.
     * |        |          |For each rank, set its bit to 1 to enable its ODT.
     * |        |          |Present only in configurations that have 2 or more ranks.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::SCHED
     * Offset: 0x250  Scheduler Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |prefer_write|Setting Bit for Bank Selector Prefers Writes over Reads
     * |        |          |If set, then the bank selector prefers writes over reads.
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Static
     * |[2]     |Pageclose |Page Close Bit
     * |        |          |If true, bank is kept open only while there are page hit transactions available in the CAM to that bank.
     * |        |          |The last read or write command in the CAM with a bank and page hit is executed with auto-precharge if SCHED1.pageclose_timer=0.
     * |        |          |Even if this register set to 1 and SCHED1.pageclose_timer is set to 0, explicit precharge (and not auto-precharge) may be issued in some cases where there is a mode switch between Write and Read or between LPR and HPR
     * |        |          |The Read and Write commands that are executed as part of the ECC scrub requests are also executed without auto-precharge.
     * |        |          |If false, the bank remains open until there is a need to close it (to open a different page, or for page timeout or refresh timeout) - also known as open page policy
     * |        |          |The open page policy can be overridden by setting the per-command-autopre bit on the HIF interface (hif_cmd_autopre).
     * |        |          |The pageclose feature provids a midway between Open and Close page policies.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[12:8]  |lpr_num_entries|Number of Entries in the Low Priority Transaction Store
     * |        |          |It is this value + 1.
     * |        |          |(MEMC_NO_OF_ENTRY (hardware configures to 32) - (SCHED.lpr_num_entries + 1)) is the number of entries available for the high priority transaction store.
     * |        |          |Setting this to maximum value allocates all entries to low priority transaction store.
     * |        |          |Setting this to 0 allocates 1 entry to low priority transaction store and the rest to high priority transaction store.
     * |        |          |Programming Mode: Static
     * |[23:16] |go2critical_hysteresis|UNUSED.
     * |        |          |Programming Mode: Static
     * |[30:24] |rdwr_idle_gap|Switch Clock Cycles Between Different Transaction Store
     * |        |          |When the preferred transaction store is empty for these many clock cycles, switch to the alternate transaction store if it is non-empty.
     * |        |          |The read transaction store (both high and low priority) is the default preferred transaction store and the write transaction store is the alternative store.
     * |        |          |When prefer write over read is set this is reversed.
     * |        |          |0x0 is a legal value for this register
     * |        |          |When set to 0x0, the transaction store switching happens immediately when the switching conditions become true.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::SCHED1
     * Offset: 0x254  Scheduler Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |pageclose_timer|Page Close Timer
     * |        |          |This field works in conjunction with SCHED.pageclose
     * |        |          |It only has meaning if SCHED.pageclose equals to 1.
     * |        |          |If SCHED.pageclose==1 and pageclose_timer==0, then an auto-precharge may be scheduled for last read or write command in the CAM with a bank and page hit.
     * |        |          |Note, sometimes an explicit precharge is scheduled instead of the auto-precharge
     * |        |          |For more information, see SCHED.pageclose.
     * |        |          |If SCHED.pageclose==1 and pageclose_timer>0, then an auto-precharge is not scheduled for last read or write command in the CAM with a bank and page hit.
     * |        |          |Instead, a timer is started, with pageclose_timer as the initial value.
     * |        |          |There is a timer on a per bank basis.
     * |        |          |The timer decrements unless the next read or write in the CAM to a bank is a page hit.
     * |        |          |It gets reset to pageclose_timer value if the next read or write in the CAM to a bank is a page hit.
     * |        |          |Once the timer has reached zero, an explicit precharge is attempted to be scheduled.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PERFHPR1
     * Offset: 0x25C  High Priority Read CAM Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |hpr_max_starve|Number of DFI Clocks that the HPR Queue can be Starved Before It Goes Critical
     * |        |          |Indicates the number of DFI clocks that the HPR queue can be starved before it goes critical.
     * |        |          |The minimum valid functional value for this register is 0x1.
     * |        |          |Programming it to 0x0 disables the starvation functionality.
     * |        |          |During normal operation, this function must not be disabled as it causes excessive latencies.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[31:24] |hpr_xact_run_length|Number of Transactions that are Serviced once the HPR Queue Goes Critical
     * |        |          |Indicates the number of transactions that are serviced once the HPR queue goes critical is the smaller of:
     * |        |          |u00B7 (a) This number
     * |        |          |u00B7 (b) Number of transactions available
     * |        |          |Unit: Transaction.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PERFLPR1
     * Offset: 0x264  Low Priority Read CAM Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |lpr_max_starve|Number of DFI Clocks that the LPR Queue can be Starved Before It Goes Critical
     * |        |          |Indicates the number of DFI clocks that the LPR queue can be starved before it goes critical.
     * |        |          |The minimum valid functional value for this register is 0x1.
     * |        |          |Programming it to 0x0 disables the starvation functionality.
     * |        |          |During normal operation, this function must not be disabled as it causes excessive latencies.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[31:24] |lpr_xact_run_length|Number of Transactions that are Serviced Once the LPR Queue Goes Critical
     * |        |          |Indicates the number of transactions that are serviced once the LPR queue goes critical is the smaller of:
     * |        |          |u00B7 (a) This number
     * |        |          |u00B7 (b) Number of transactions available
     * |        |          |Unit: Transaction.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PERFWR1
     * Offset: 0x26C  Write CAM Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |w_max_starve|Number of DFI Clocks that the WR Queue can be Starved Before It Goes Critical
     * |        |          |Indicates the number of DFI clocks that the WR queue can be starved before it goes critical.
     * |        |          |The minimum valid functional value for this register is 0x1.
     * |        |          |Programming it to 0x0 disables the starvation functionality.
     * |        |          |During normal operation, this function must not be disabled as it causes excessive latencies.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Unit: DFI clock cycles.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[31:24] |w_xact_run_length|Number of Transactions that are Serviced Once the WR Queue Goes Critical
     * |        |          |Indicates the number of transactions that are serviced once the WR queue goes critical is the smaller of:
     * |        |          |u00B7 (a) This number
     * |        |          |u00B7 (b) Number of transactions available
     * |        |          |Unit: Transaction.
     * |        |          |FOR PERFORMANCE ONLY.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::DBG0
     * Offset: 0x300  Debug Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dis_wc    |Disable Bit for Write Combine
     * |        |          |When 1, disable write combine.
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Static
     * |[1]     |dis_rd_bypass|Disable Bit for Bypass Path for High Priority Read Page Hits
     * |        |          |Only present in designs supporting read bypass.
     * |        |          |When 1, disable bypass path for high priority read page hits.
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Static
     * |[2]     |dis_act_bypass|Disable Bit for Bypass Path for High Priority Read Activates
     * |        |          |Only present in designs supporting activate bypass.
     * |        |          |When 1, disable bypass path for high priority read activates.
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Static
     * |[4]     |dis_collision_page_opt|Disable Bit for Collision Page Option
     * |        |          |When this is set to '0', auto-precharge is disabled for the flushed command in a collision case.
     * |        |          |Collision cases are write followed by read to same address, read followed by write to same address, or write followed by write to same address with DBG0.dis_wc bit = 1 (where same address comparisons exclude the two address bits representing critical word).
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Static
     * |[6]     |dis_max_rank_rd_opt|Disable Bit to Optimize max_rank_rd and max_logical_rank_rd
     * |        |          |This register is for debug purpose only.
     * |        |          |For normal operation, this register must be set to 0.
     * |        |          |Programming Mode: Static
     * |[7]     |dis_max_rank_wr_opt|Disable Bit to Optimize max_rank_wr and max_logical_rank_wr
     * |        |          |This register is for debug purpose only.
     * |        |          |For normal operation, this register must be set to 0.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::DBG1
     * Offset: 0x304  Debug Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |dis_dq    |Disable Bit for De-queue Transactions
     * |        |          |When 1, uMCTL2 does not de-queue any transactions from the CAM.
     * |        |          |Bypass is also disabled.
     * |        |          |All transactions are queued in the CAM
     * |        |          |No reads or writes are issued to SDRAM as long as this is asserted.
     * |        |          |This bit may be used to prevent reads or writes being issued by the uMCTL2, which makes it safe to modify certain register fields associated with reads and writes.
     * |        |          |After setting this bit, it is strongly recommended to poll DBGCAM.wr_data_pipeline_empty and DBGCAM.rd_data_pipeline_empty, before making changes to any registers which affect reads and writes.
     * |        |          |This ensures that the relevant logic in the DDRC is idle.
     * |        |          |This bit is intended to be switched on-the-fly.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |dis_hif   |Disable Bit for HIF Command
     * |        |          |When 1, uMCTL2 asserts the HIF command signal hif_cmd_stall.
     * |        |          |uMCTL2 ignores the hif_cmd_valid and all other associated request signals.
     * |        |          |This bit is intended to be switched on-the-fly.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::DBGCAM
     * Offset: 0x308  CAM Debug Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |dbg_hpr_q_depth|High Priority Read Queue Depth
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Dynamic
     * |[13:8]  |dbg_lpr_q_depth|Low Priority Read Queue Depth
     * |        |          |The last entry of LPR queue is reserved for ECC SCRUB operation
     * |        |          |This entry is not included in the calculation of the queue depth.
     * |        |          |FOR DEBUG ONLY
     * |        |          |Programming Mode: Dynamic
     * |[21:16] |dbg_w_q_depth|Write Queue Depth
     * |        |          |The last entry of WR queue is reserved for ECC SCRUB operation
     * |        |          |This entry is not included in the calculation of the queue depth.
     * |        |          |FOR DEBUG ONLY
     * |        |          |Programming Mode: Dynamic
     * |[24]    |dbg_stall |Command Queues and Data Buffers Stall
     * |        |          |FOR DEBUG ONLY.
     * |        |          |Programming Mode: Dynamic
     * |[25]    |dbg_rd_q_empty|Read Command Queues and Read Data Buffers Empty
     * |        |          |When 1, all the Read command queues and Read data buffers inside DDRC are empty.
     * |        |          |This register is to be used for debug purpose.
     * |        |          |An example use-case scenario: When the controller enters self-refresh using the Low-Power entry sequence, controller is expected to have executed all the commands in its queues and the write and read data drained
     * |        |          |Hence this register must be 1 at that time.
     * |        |          |FOR DEBUG ONLY
     * |        |          |Programming Mode: Dynamic
     * |[26]    |dbg_wr_q_empty|Write Command Queues and Write Data Buffers Empty
     * |        |          |When 1, all the Write command queues and Write data buffers inside DDRC are empty.
     * |        |          |This register is to be used for debug purpose.
     * |        |          |An example use-case scenario: When the controller enters self-refresh using the Low-Power entry sequence, controller is expected to have executed all the commands in its queues and the write and read data drained
     * |        |          |Hence this register must be 1 at that time.
     * |        |          |FOR DEBUG ONLY
     * |        |          |Programming Mode: Dynamic
     * |[28]    |rd_data_pipeline_empty|Read Data Pipeline Empty
     * |        |          |This bit indicates that the read data pipeline on the DFI interface is empty.
     * |        |          |This register is intended to be polled at least twice after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed.
     * |        |          |Programming Mode: Dynamic
     * |[29]    |wr_data_pipeline_empty|Write Data Pipeline Empty
     * |        |          |This bit indicates that the write data pipeline on the DFI interface is empty.
     * |        |          |This register is intended to be polled at least twice after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::DBGCMD
     * Offset: 0x30C  Command Debug Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |rank0_refresh|Signal for uMCTL2 to Issue Refresh to Rank 0
     * |        |          |Setting this register bit to 1 indicates to the uMCTL2 to issue a refresh to rank 0.
     * |        |          |Writing to this bit causes DBGSTAT.rank0_refresh_busy to be set.
     * |        |          |When DBGSTAT.rank0_refresh_busy is cleared, the command has been stored in uMCTL2.
     * |        |          |For 3DS configuration, refresh is sent to rank index 0.
     * |        |          |This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
     * |        |          |It is recommended NOT to set this register bit if in Init or Deep power-down operating modes or Maximum Power Saving Mode.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * |[1]     |rank1_refresh|Signal for uMCTL2 to Issue Refresh to Rank 1
     * |        |          |Setting this register bit to 1 indicates to the uMCTL2 to issue a refresh to rank 1.
     * |        |          |Writing to this bit causes DBGSTAT.rank1_refresh_busy to be set.
     * |        |          |When DBGSTAT.rank1_refresh_busy is cleared, the command has been stored in uMCTL2.
     * |        |          |For 3DS configuration, refresh is sent to rank index 1.
     * |        |          |This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
     * |        |          |It is recommended NOT to set this register bit if in Init or Deep power-down operating modes or Maximum Power Saving Mode.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * |[4]     |zq_calib_short|Signal for uMCTL2 to Issue ZQCS to SDRAM
     * |        |          |Setting this register bit to 1 indicates to the uMCTL2 to issue a ZQCS (ZQ calibration short)/MPC(ZQ calibration) command to the SDRAM.
     * |        |          |When this request is stored in the uMCTL2, the bit is automatically cleared.
     * |        |          |This operation can be performed only when ZQCTL0.dis_auto_zq=1.
     * |        |          |It is recommended NOT to set this register bit if in Init, in self-refresh or Deep power-down operating modes or Maximum Power Saving Mode.
     * |        |          |For Deep power down and Maximum Power Saving Mode, it is not scheduled, although DBGSTAT.zq_calib_short_busy is de-asserted.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * |[5]     |ctrlupd   |Signal for uMCTL2 to Issue dfi_ctrlupd_req to PHY
     * |        |          |Setting this register bit to 1 indicates to the uMCTL2 to issue a dfi_ctrlupd_req to the PHY.
     * |        |          |When this request is stored in the uMCTL2, the bit is automatically cleared.
     * |        |          |This operation must only be performed when DFIUPD0.dis_auto_ctrlupd=1.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::DBGSTAT
     * Offset: 0x310  Status Debug Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |rank0_refresh_busy|Rank0 Refresh Operation Busy
     * |        |          |SoC might initiate a rank0_refresh operation (refresh operation to rank 0) only if this signal is low.
     * |        |          |This signal goes high in the clock after DBGCMD.rank0_refresh is set to one
     * |        |          |It goes low when the rank0_refresh operation is stored in the uMCTL2.
     * |        |          |It is recommended not to perform rank0_refresh operations when this signal is high.
     * |        |          |u00B7 0 - Indicates that the SoC can initiate a rank0_refresh operation
     * |        |          |u00B7 1 - Indicates that rank0_refresh operation has not been stored yet in the uMCTL2
     * |        |          |Programming Mode: Dynamic
     * |[1]     |rank1_refresh_busy|Rank1 Refresh Operation Busy
     * |        |          |SoC might initiate a rank1_refresh operation (refresh operation to rank 1) only if this signal is low.
     * |        |          |This signal goes high in the clock after DBGCMD.rank1_refresh is set to one
     * |        |          |It goes low when the rank1_refresh operation is stored in the uMCTL2.
     * |        |          |It is recommended not to perform rank1_refresh operations when this signal is high.
     * |        |          |u00B7 0 - Indicates that the SoC can initiate a rank1_refresh operation
     * |        |          |u00B7 1 - Indicates that rank1_refresh operation has not been stored yet in the uMCTL2
     * |        |          |Programming Mode: Dynamic
     * |[4]     |zq_calib_short_busy|ZQCS Operation Busy State
     * |        |          |SoC might initiate a ZQCS (ZQ calibration short) operation only if this signal is low.
     * |        |          |This signal goes high in the clock after the uMCTL2 accepts the ZQCS request.
     * |        |          |It goes low when the ZQCS operation is initiated in the uMCTL2
     * |        |          |It is recommended not to perform ZQCS operations when this signal is high.
     * |        |          |u00B7 0 - Indicates that the SoC can initiate a ZQCS operation
     * |        |          |u00B7 1 - Indicates that ZQCS operation has not been initiated yet in the uMCTL2
     * |        |          |Programming Mode: Dynamic
     * |[5]     |ctrlupd_busy|ctrlupd Operation Busy State
     * |        |          |SoC might initiate a ctrlupd operation only if this signal is low.
     * |        |          |This signal goes high in the clock after the uMCTL2 accepts the ctrlupd request.
     * |        |          |It goes low when the ctrlupd operation is initiated in the uMCTL2.
     * |        |          |It is recommended not to perform ctrlupd operations when this signal is high.
     * |        |          |u00B7 0 - Indicates that the SoC can initiate a ctrlupd operation
     * |        |          |u00B7 1 - Indicates that ctrlupd operation has not been initiated yet in the uMCTL2
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::SWCTL
     * Offset: 0x320  Software Register Programming Control Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |sw_done   |Quasi-Dynamic Register Programming Enable Bit
     * |        |          |Enables quasi-dynamic register programming outside reset.
     * |        |          |Program this register to 0 to enable quasi-dynamic programming.
     * |        |          |Set back register to 1 once programming is done.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::SWSTAT
     * Offset: 0x324  Software Register Programming Control Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |sw_done_ack|Register Programming Done ACK
     * |        |          |This register is the echo of SWCTL.sw_done.
     * |        |          |Wait for sw_done value 1 to propagate to sw_done_ack at the end of the programming sequence to ensure that the correct registers values are propagated to the destination clock domains.
     * |        |          |Testable: untestable
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::SWCTLSTATIC
     * Offset: 0x328  Static Registers Write Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |sw_static_unlock|Static Register Programming Unlock Bit
     * |        |          |Enables static register programming outside reset.
     * |        |          |Program this register to 1 to enable static register programming.
     * |        |          |Set register back to 0 once programming is done.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::POISONCFG
     * Offset: 0x36C  AXI Poison Configuration Register. Common for all AXI ports.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |wr_poison_slverr_en|Write Transaction Poisoning SLVERR Response Enable Bit
     * |        |          |If set to 1, enables SLVERR response for write transaction poisoning.
     * |        |          |Programming Mode: Dynamic
     * |[4]     |wr_poison_intr_en|Write Transaction Poisoning Interrupt Enable Bit
     * |        |          |If set to 1, enables interrupts for write transaction poisoning.
     * |        |          |Programming Mode: Dynamic
     * |[8]     |wr_poison_intr_clr|Write Transaction Poisoning Interrupt Clear Bit
     * |        |          |Interrupt clear for write transaction poisoning.
     * |        |          |Allow 2/3 clock cycles for correct value to propagate to controller logic and clear the interrupts.
     * |        |          |uMCTL2 automatically clears this bit.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * |[16]    |rd_poison_slverr_en|Read Transaction Poisoning SLVERR Response Enable Bit
     * |        |          |If set to 1, enables SLVERR response for read transaction poisoning.
     * |        |          |Programming Mode: Dynamic
     * |[20]    |rd_poison_intr_en|Read Transaction Poisoning Interrupt Enable Bit
     * |        |          |If set to 1, enables interrupts for read transaction poisoning.
     * |        |          |Programming Mode: Dynamic
     * |[24]    |rd_poison_intr_clr|Read Transaction Poisoning Interrupt Clear Bit
     * |        |          |Allow 2/3 clock cycles for correct value to propagate to controller logic and clear the interrupts.
     * |        |          |uMCTL2 automatically clears this bit.
     * |        |          |Testable: readOnly
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::POISONSTAT
     * Offset: 0x370  AXI Poison Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |wr_poison_intr_0|Write Transaction Poisoning Error Interrupt for Port 0
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |wr_poison_intr_1|Write Transaction Poisoning Error Interrupt for Port 1
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[2]     |wr_poison_intr_2|Write Transaction Poisoning Error Interrupt for Port 2
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[3]     |wr_poison_intr_3|Write Transaction Poisoning Error Interrupt for Port 3
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[4]     |wr_poison_intr_4|Write Transaction Poisoning Error Interrupt for Port 4
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[5]     |wr_poison_intr_5|Write Transaction Poisoning Error Interrupt for Port 5
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[6]     |wr_poison_intr_6|Write Transaction Poisoning Error Interrupt for Port 6
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[7]     |wr_poison_intr_7|Write Transaction Poisoning Error Interrupt for Port 7
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[16]    |rd_poison_intr_0|Read Transaction Poisoning Error Interrupt for Port 0
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[17]    |rd_poison_intr_1|Read Transaction Poisoning Error Interrupt for Port 1
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[18]    |rd_poison_intr_2|Read Transaction Poisoning Error Interrupt for Port 2
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[19]    |rd_poison_intr_3|Read Transaction Poisoning Error Interrupt for Port 3
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[20]    |rd_poison_intr_4|Read Transaction Poisoning Error Interrupt for Port 4
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[21]    |rd_poison_intr_5|Read Transaction Poisoning Error Interrupt for Port 5
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[22]    |rd_poison_intr_6|Read Transaction Poisoning Error Interrupt for Port 6
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * |[23]    |rd_poison_intr_7|Read Transaction Poisoning Error Interrupt for Port 7
     * |        |          |This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel.
     * |        |          |Bit 0 corresponds to Port 0, and so on
     * |        |          |Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PSTAT
     * Offset: 0x3FC  Port Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |rd_port_busy_0|Outstanding Reads for AXI Port 0
     * |        |          |Indicates if there are outstanding reads for AXI port 0.
     * |        |          |Programming Mode: Dynamic
     * |[1]     |rd_port_busy_1|Outstanding Reads for AXI Port 1
     * |        |          |Indicates if there are outstanding reads for AXI port 1.
     * |        |          |Programming Mode: Dynamic
     * |[2]     |rd_port_busy_2|Outstanding Reads for AXI Port 2
     * |        |          |Indicates if there are outstanding reads for AXI port 2.
     * |        |          |Programming Mode: Dynamic
     * |[3]     |rd_port_busy_3|Outstanding Reads for AXI Port 3
     * |        |          |Indicates if there are outstanding reads for AXI port 3.
     * |        |          |Programming Mode: Dynamic
     * |[4]     |rd_port_busy_4|Outstanding Reads for AXI Port 4
     * |        |          |Indicates if there are outstanding reads for AXI port 4.
     * |        |          |Programming Mode: Dynamic
     * |[5]     |rd_port_busy_5|Outstanding Reads for AXI Port 5
     * |        |          |Indicates if there are outstanding reads for AXI port 5.
     * |        |          |Programming Mode: Dynamic
     * |[6]     |rd_port_busy_6|Outstanding Reads for AXI Port 6
     * |        |          |Indicates if there are outstanding reads for AXI port 6.
     * |        |          |Programming Mode: Dynamic
     * |[7]     |rd_port_busy_7|Outstanding Reads for AXI Port 7
     * |        |          |Indicates if there are outstanding reads for AXI port 7.
     * |        |          |Programming Mode: Dynamic
     * |[16]    |wr_port_busy_0|Outstanding Writes for AXI Port 0
     * |        |          |Indicates if there are outstanding writes for AXI port 0.
     * |        |          |Programming Mode: Dynamic
     * |[17]    |wr_port_busy_1|Outstanding Writes for AXI Port 1
     * |        |          |Indicates if there are outstanding writes for AXI port 1.
     * |        |          |Programming Mode: Dynamic
     * |[18]    |wr_port_busy_2|Outstanding Writes for AXI Port 2
     * |        |          |Indicates if there are outstanding writes for AXI port 2.
     * |        |          |Programming Mode: Dynamic
     * |[19]    |wr_port_busy_3|Outstanding Writes for AXI Port 3
     * |        |          |Indicates if there are outstanding writes for AXI port 3.
     * |        |          |Programming Mode: Dynamic
     * |[20]    |wr_port_busy_4|Outstanding Writes for AXI Port 4
     * |        |          |Indicates if there are outstanding writes for AXI port 4.
     * |        |          |Programming Mode: Dynamic
     * |[21]    |wr_port_busy_5|Outstanding Writes for AXI Port 5
     * |        |          |Indicates if there are outstanding writes for AXI port 5.
     * |        |          |Programming Mode: Dynamic
     * |[22]    |wr_port_busy_6|Outstanding Writes for AXI Port 6
     * |        |          |Indicates if there are outstanding writes for AXI port 6.
     * |        |          |Programming Mode: Dynamic
     * |[23]    |wr_port_busy_7|Outstanding Writes for AXI Port 7
     * |        |          |Indicates if there are outstanding writes for AXI port 7.
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCCFG
     * Offset: 0x400  Port Common Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |go2critical_en|go2critical Function Enable Bit
     * |        |          |If set to 1 (enabled), sets co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals going to DDRC based on urgent input (awurgent, arurgent) coming from AXI master.
     * |        |          |If set to 0 (disabled), co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals at DDRC are driven to 1b'0.
     * |        |          |For uPCTL2, this register field must be set to 0.
     * |        |          |Programming Mode: Static
     * |[4]     |pagematch_limit|Page Match Four Limit
     * |        |          |If set to 1, limits the number of consecutive same page DDRC transactions that can be granted by the Port Arbiter to four when Page Match feature is enabled.
     * |        |          |If set to 0, there is no limit imposed on number of consecutive same page DDRC transactions.
     * |        |          |Programming Mode: Static
     * |[8]     |bl_exp_mode|Burst Length Expansion Mode
     * |        |          |By default, (that is, bl_exp_mode==0) XPI expands every AXI burst into multiple HIF commands, using the memory burst length as a unit
     * |        |          |If set to 1, then XPI uses half of the memory burst length as a unit.
     * |        |          |This applies to both reads and writes
     * |        |          |When MSTR.data_bus_width==00, setting bl_exp_mode to 1 has no effect.
     * |        |          |Functionality is also not supported if Data Channel Interleave is enabled.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGR_0
     * Offset: 0x404  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Note that this register has an effect only if necessary logic is instantiated through the UMCTL2_RDWR_ORDERED_n parameter.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_0
     * Offset: 0x408  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_0
     * Offset: 0x490  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_0
     * Offset: 0x494  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_1
     * Offset: 0x4B4  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_1
     * Offset: 0x4B8  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_1
     * Offset: 0x540  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_1
     * Offset: 0x544  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_2
     * Offset: 0x564  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_2
     * Offset: 0x568  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_2
     * Offset: 0x5F0  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_2
     * Offset: 0x5F4  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_3
     * Offset: 0x614  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_3
     * Offset: 0x618  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_3
     * Offset: 0x6A0  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_3
     * Offset: 0x6A4  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_4
     * Offset: 0x6C4  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_4
     * Offset: 0x6C8  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_4
     * Offset: 0x750  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_4
     * Offset: 0x754  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_5
     * Offset: 0x774  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_5
     * Offset: 0x778  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_5
     * Offset: 0x800  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_5
     * Offset: 0x804  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_6
     * Offset: 0x824  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_6
     * Offset: 0x828  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_6
     * Offset: 0x8B0  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_6
     * Offset: 0x8B4  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::PCFGR_7
     * Offset: 0x8D4  Port n Configuration Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |rd_port_priority|Read Channel of Port Priority
     * |        |          |Determines the initial load value of read aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted
     * |        |          |The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease.
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0).
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |rd_port_aging_en|Read Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the read channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |rd_port_urgent_en|AXI Urgent Sideband Signal (arurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (arurgent)
     * |        |          |When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |rd_port_pagematch_en|Read Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * |[16]    |rdwr_ordered_en|Read/Writes Ordered Enable Bit
     * |        |          |If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port.
     * |        |          |In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance.
     * |        |          |This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCFGW_7
     * Offset: 0x8D8  Port n Configuration Write Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |wr_port_priority|Write Channel of Port Priority
     * |        |          |Determines the initial load value of write aging counters.
     * |        |          |These counters are parallel loaded after reset, or after each grant to the corresponding port.
     * |        |          |The aging counters down-count every clock cycle where the port is requesting but not granted.
     * |        |          |The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port.
     * |        |          |Port's priority increases as the higher significant 5-bits of the counter starts to decrease
     * |        |          |When the aging counter becomes 0, the corresponding port channel has the highest priority level.
     * |        |          |For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable).
     * |        |          |For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.
     * |        |          |Note: The two LSBs of this register field are tied internally to 2'b00.
     * |        |          |Programming Mode: Static
     * |[12]    |wr_port_aging_en|Write Channel of Port Aging Function Enable Bit
     * |        |          |If set to 1, enables aging function for the write channel of the port.
     * |        |          |Programming Mode: Static
     * |[13]    |wr_port_urgent_en|AXI Urgent Sideband Signal (awurgent) Enable Bit
     * |        |          |If set to 1, enables the AXI urgent sideband signal (awurgent).
     * |        |          |When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register.
     * |        |          |Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
     * |        |          |Programming Mode: Static
     * |[14]    |wr_port_pagematch_en|Write Page Match Enable Bit
     * |        |          |If set to 1, enables the Page Match feature.
     * |        |          |If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same rank, same bank and same row).
     * |        |          |See also related PCCFG.pagematch_limit register.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::PCTRL_7
     * Offset: 0x960  Port n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |port_en   |AXI Port n Enable Bit
     * |        |          |Programming Mode: Dynamic
     * @var UMCTL2_T::PCFGQOS0_7
     * Offset: 0x964  Port n Read QoS Configuration Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |rqos_map_level1|End of Region0 Mapping
     * |        |          |Separation level1 indicating the end of region0 mapping; start of region0 is 0
     * |        |          |Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.
     * |        |          |Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
     * |        |          |All of the map_level* registers must be set to distinct values.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[17:16] |rqos_map_region0|Traffic Class of Region 0
     * |        |          |This bit field indicates the traffic class of region 0.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region 0 maps to the blue address queue.
     * |        |          |In this case, valid values are:
     * |        |          |0: LPR and 1: VPR only.
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * |[21:20] |rqos_map_region1|Traffic Class of Region 1
     * |        |          |This bit field indicates the traffic class of region 1.
     * |        |          |Valid values are:
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR
     * |        |          |u00B7 2 - HPR
     * |        |          |For dual address queue configurations, region1 maps to the blue address queue.
     * |        |          |In this case, valid values are
     * |        |          |u00B7 0 - LPR
     * |        |          |u00B7 1 - VPR only
     * |        |          |When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
     * |        |          |Programming Mode: Quasi-dynamic Group 3
     * @var UMCTL2_T::SARBASE0
     * Offset: 0xF04  SAR Base Address Register n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |base_addr |Base Address for Address Region n
     * |        |          |Base address for address region n specified as awaddr[UMCTL2_A_ADDRW-1:x] and araddr[UMCTL2_A_ADDRW-1:x],
     * |        |          |where x is determined by the minimum block size parameter UMCTL2_SARMINSIZE: (x=log2(block size)).
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::SARSIZE0
     * Offset: 0xF08  SAR Size Register n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |nblocks   |Number of Blocks for Address Region n.
     * |        |          |This register determines the total size of the region in multiples of minimum block size as specified by the hardware parameter UMCTL2_SARMINSIZE
     * |        |          |The register value is encoded as number of blocks = nblocks + 1
     * |        |          |For example, if register is programmed to 0, region can have 1 block.
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::VER_NUMBER
     * Offset: 0xFF0  UMCTL2 Version Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ver_number|Device Version Number Value
     * |        |          |This is in ASCII format, with each byte corresponding to a character of the version number
     * |        |          |Programming Mode: Static
     * @var UMCTL2_T::VER_TYPE
     * Offset: 0xFF4  UMCTL2 Version Type Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ver_type  |Device Version Type Value
     * |        |          |This is in ASCII format, with each byte corresponding to a character of the version type
     * |        |          |Programming Mode: Static
     */
    __IO uint32_t MSTR;                  /*!< [0x0000] Master Register0                                                 */
    __I  uint32_t STAT;                  /*!< [0x0004] Operating Mode Status Register                                   */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t MRCTRL0;               /*!< [0x0010] Mode Register Read/Write Control Register 0                      */
    __IO uint32_t MRCTRL1;               /*!< [0x0014] Mode Register Read/Write Control Register 1                      */
    __I  uint32_t MRSTAT;                /*!< [0x0018] Mode Register Read/Write Status Register                         */
    __I  uint32_t RESERVE1[5];
    __IO uint32_t PWRCTL;                /*!< [0x0030] Low Power Control Register                                       */
    __IO uint32_t PWRTMG;                /*!< [0x0034] Low Power Timing Register                                        */
    __IO uint32_t HWLPCTL;               /*!< [0x0038] Hardware Low Power Control Register                              */
    __I  uint32_t RESERVE2[5];
    __IO uint32_t RFSHCTL0;              /*!< [0x0050] Refresh Control Register 0                                       */
    __IO uint32_t RFSHCTL1;              /*!< [0x0054] Refresh Control Register 1                                       */
    __I  uint32_t RESERVE3[2];
    __IO uint32_t RFSHCTL3;              /*!< [0x0060] Refresh Control Register 3                                       */
    __IO uint32_t RFSHTMG;               /*!< [0x0064] Refresh Timing Register                                          */
    __I  uint32_t RESERVE4[22];
    __IO uint32_t CRCPARCTL0;            /*!< [0x00c0] CRC Parity Control Register0                                     */
    __I  uint32_t RESERVE5[2];
    __I  uint32_t CRCPARSTAT;            /*!< [0x00cc] CRC Parity Status Register                                       */
    __IO uint32_t INIT0;                 /*!< [0x00d0] SDRAM Initialization Register 0                                  */
    __IO uint32_t INIT1;                 /*!< [0x00d4] SDRAM Initialization Register 1                                  */
    __I  uint32_t RESERVE6[1];
    __IO uint32_t INIT3;                 /*!< [0x00dc] SDRAM Initialization Register 3                                  */
    __IO uint32_t INIT4;                 /*!< [0x00e0] SDRAM Initialization Register 4                                  */
    __IO uint32_t INIT5;                 /*!< [0x00e4] SDRAM Initialization Register 5                                  */
    __I  uint32_t RESERVE7[2];
    __IO uint32_t DIMMCTL;               /*!< [0x00f0] DIMM Control Register                                            */
    __IO uint32_t RANKCTL;               /*!< [0x00f4] Rank Control Register                                            */
    __I  uint32_t RESERVE8[2];
    __IO uint32_t DRAMTMG0;              /*!< [0x0100] SDRAM Timing Register 0                                          */
    __IO uint32_t DRAMTMG1;              /*!< [0x0104] SDRAM Timing Register 1                                          */
    __IO uint32_t DRAMTMG2;              /*!< [0x0108] SDRAM Timing Register 2                                          */
    __IO uint32_t DRAMTMG3;              /*!< [0x010c] SDRAM Timing Register 3                                          */
    __IO uint32_t DRAMTMG4;              /*!< [0x0110] SDRAM Timing Register 4                                          */
    __IO uint32_t DRAMTMG5;              /*!< [0x0114] SDRAM Timing Register 5                                          */
    __I  uint32_t RESERVE9[2];
    __IO uint32_t DRAMTMG8;              /*!< [0x0120] SDRAM Timing Register 8                                          */
    __I  uint32_t RESERVE10[6];
    __IO uint32_t DRAMTMG15;             /*!< [0x013c] SDRAM Timing Register 15                                         */
    __I  uint32_t RESERVE11[16];
    __IO uint32_t ZQCTL0;                /*!< [0x0180] ZQ Control Register 0                                            */
    __IO uint32_t ZQCTL1;                /*!< [0x0184] ZQ Control Register 1                                            */
    __I  uint32_t RESERVE12[2];
    __IO uint32_t DFITMG0;               /*!< [0x0190] DFI Timing Register 0                                            */
    __IO uint32_t DFITMG1;               /*!< [0x0194] DFI Timing Register 1                                            */
    __IO uint32_t DFILPCFG0;             /*!< [0x0198] DFI Low Power Configuration Register 0                           */
    __I  uint32_t RESERVE13[1];
    __IO uint32_t DFIUPD0;               /*!< [0x01a0] DFI Update Register 0                                            */
    __IO uint32_t DFIUPD1;               /*!< [0x01a4] DFI Update Register 1                                            */
    __IO uint32_t DFIUPD2;               /*!< [0x01a8] DFI Update Register 2                                            */
    __I  uint32_t RESERVE14[1];
    __IO uint32_t DFIMISC;               /*!< [0x01b0] DFI Miscellaneous Control Register                               */
    __I  uint32_t RESERVE15[2];
    __I  uint32_t DFISTAT;               /*!< [0x01bc] DFI Status Register                                              */
    __I  uint32_t RESERVE16[1];
    __IO uint32_t DFIPHYMSTR;            /*!< [0x01c4] DFI PHY Master                                                   */
    __I  uint32_t RESERVE17[14];
    __IO uint32_t ADDRMAP0;              /*!< [0x0200] Address Map Register 0                                           */
    __IO uint32_t ADDRMAP1;              /*!< [0x0204] Address Map Register 1                                           */
    __IO uint32_t ADDRMAP2;              /*!< [0x0208] Address Map Register 2                                           */
    __IO uint32_t ADDRMAP3;              /*!< [0x020c] Address Map Register 3                                           */
    __IO uint32_t ADDRMAP4;              /*!< [0x0210] Address Map Register 4                                           */
    __IO uint32_t ADDRMAP5;              /*!< [0x0214] Address Map Register 5                                           */
    __IO uint32_t ADDRMAP6;              /*!< [0x0218] Address Map Register 6                                           */
    __I  uint32_t RESERVE18[2];
    __IO uint32_t ADDRMAP9;              /*!< [0x0224] Address Map Register 9                                           */
    __IO uint32_t ADDRMAP10;             /*!< [0x0228] Address Map Register 10                                          */
    __IO uint32_t ADDRMAP11;             /*!< [0x022c] Address Map Register 11                                          */
    __I  uint32_t RESERVE19[4];
    __IO uint32_t ODTCFG;                /*!< [0x0240] ODT Configuration Register                                       */
    __IO uint32_t ODTMAP;                /*!< [0x0244] ODT/Rank Map Register                                            */
    __I  uint32_t RESERVE20[2];
    __IO uint32_t SCHED;                 /*!< [0x0250] Scheduler Control Register                                       */
    __IO uint32_t SCHED1;                /*!< [0x0254] Scheduler Control Register 1                                     */
    __I  uint32_t RESERVE21[1];
    __IO uint32_t PERFHPR1;              /*!< [0x025c] High Priority Read CAM Register 1                                */
    __I  uint32_t RESERVE22[1];
    __IO uint32_t PERFLPR1;              /*!< [0x0264] Low Priority Read CAM Register 1                                 */
    __I  uint32_t RESERVE23[1];
    __IO uint32_t PERFWR1;               /*!< [0x026c] Write CAM Register 1                                             */
    __I  uint32_t RESERVE24[36];
    __IO uint32_t DBG0;                  /*!< [0x0300] Debug Register 0                                                 */
    __IO uint32_t DBG1;                  /*!< [0x0304] Debug Register 1                                                 */
    __I  uint32_t DBGCAM;                /*!< [0x0308] CAM Debug Register                                               */
    __IO uint32_t DBGCMD;                /*!< [0x030c] Command Debug Register                                           */
    __I  uint32_t DBGSTAT;               /*!< [0x0310] Status Debug Register                                            */
    __I  uint32_t RESERVE25[3];
    __IO uint32_t SWCTL;                 /*!< [0x0320] Software Register Programming Control Enable                     */
    __I  uint32_t SWSTAT;                /*!< [0x0324] Software Register Programming Control Status                     */
    __IO uint32_t SWCTLSTATIC;           /*!< [0x0328] Static Registers Write Enable                                    */
    __I  uint32_t RESERVE26[16];
    __IO uint32_t POISONCFG;             /*!< [0x036c] AXI Poison Configuration Register. Common for all AXI ports.     */
    __I  uint32_t POISONSTAT;            /*!< [0x0370] AXI Poison Status Register                                       */
    __I  uint32_t RESERVE27[34];
    __I  uint32_t PSTAT;                 /*!< [0x03fc] Port Status Register                                             */
    __IO uint32_t PCCFG;                 /*!< [0x0400] Port Common Configuration Register                               */
    __IO uint32_t PCFGR_0;               /*!< [0x0404] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_0;               /*!< [0x0408] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE28[33];
    __IO uint32_t PCTRL_0;               /*!< [0x0490] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_0;            /*!< [0x0494] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE29[7];
    __IO uint32_t PCFGR_1;               /*!< [0x04b4] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_1;               /*!< [0x04b8] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE30[33];
    __IO uint32_t PCTRL_1;               /*!< [0x0540] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_1;            /*!< [0x0544] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE31[7];
    __IO uint32_t PCFGR_2;               /*!< [0x0564] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_2;               /*!< [0x0568] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE32[33];
    __IO uint32_t PCTRL_2;               /*!< [0x05f0] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_2;            /*!< [0x05f4] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE33[7];
    __IO uint32_t PCFGR_3;               /*!< [0x0614] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_3;               /*!< [0x0618] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE34[33];
    __IO uint32_t PCTRL_3;               /*!< [0x06a0] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_3;            /*!< [0x06a4] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE35[7];
    __IO uint32_t PCFGR_4;               /*!< [0x06c4] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_4;               /*!< [0x06c8] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE36[33];
    __IO uint32_t PCTRL_4;               /*!< [0x0750] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_4;            /*!< [0x0754] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE37[7];
    __IO uint32_t PCFGR_5;               /*!< [0x0774] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_5;               /*!< [0x0778] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE38[33];
    __IO uint32_t PCTRL_5;               /*!< [0x0800] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_5;            /*!< [0x0804] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE39[7];
    __IO uint32_t PCFGR_6;               /*!< [0x0824] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_6;               /*!< [0x0828] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE40[33];
    __IO uint32_t PCTRL_6;               /*!< [0x08b0] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_6;            /*!< [0x08b4] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE41[7];
    __IO uint32_t PCFGR_7;               /*!< [0x08d4] Port n Configuration Read Register                               */
    __IO uint32_t PCFGW_7;               /*!< [0x08d8] Port n Configuration Write Register                              */
    __I  uint32_t RESERVE42[33];
    __IO uint32_t PCTRL_7;               /*!< [0x0960] Port n Control Register                                          */
    __IO uint32_t PCFGQOS0_7;            /*!< [0x0964] Port n Read QoS Configuration Register 0                         */
    __I  uint32_t RESERVE43[359];
    __IO uint32_t SARBASE0;              /*!< [0x0f04] SAR Base Address Register n                                      */
    __IO uint32_t SARSIZE0;              /*!< [0x0f08] SAR Size Register n                                              */
    __I  uint32_t RESERVE44[57];
    __I  uint32_t VER_NUMBER;            /*!< [0x0ff0] UMCTL2 Version Number Register                                   */
    __I  uint32_t VER_TYPE;              /*!< [0x0ff4] UMCTL2 Version Type Register                                     */

} UMCTL2_T;

/**
    @addtogroup UMCTL2_CONST UMCTL2 Bit Field Definition
    Constant Definitions for UMCTL2 Controller
@{ */

#define UMCTL2_MSTR_ddr3_Pos             (0)                                               /*!< UMCTL2_T::MSTR: ddr3 Position          */
#define UMCTL2_MSTR_ddr3_Msk             (0x1ul << UMCTL2_MSTR_ddr3_Pos)                   /*!< UMCTL2_T::MSTR: ddr3 Mask              */

#define UMCTL2_MSTR_burstchop_Pos        (9)                                               /*!< UMCTL2_T::MSTR: burstchop Position     */
#define UMCTL2_MSTR_burstchop_Msk        (0x1ul << UMCTL2_MSTR_burstchop_Pos)              /*!< UMCTL2_T::MSTR: burstchop Mask         */

#define UMCTL2_MSTR_en_2t_timing_mode_Pos (10)                                             /*!< UMCTL2_T::MSTR: en_2t_timing_mode Position*/
#define UMCTL2_MSTR_en_2t_timing_mode_Msk (0x1ul << UMCTL2_MSTR_en_2t_timing_mode_Pos)     /*!< UMCTL2_T::MSTR: en_2t_timing_mode Mask */

#define UMCTL2_MSTR_data_bus_width_Pos   (12)                                              /*!< UMCTL2_T::MSTR: data_bus_width Position*/
#define UMCTL2_MSTR_data_bus_width_Msk   (0x3ul << UMCTL2_MSTR_data_bus_width_Pos)         /*!< UMCTL2_T::MSTR: data_bus_width Mask    */

#define UMCTL2_MSTR_dll_off_mode_Pos     (15)                                              /*!< UMCTL2_T::MSTR: dll_off_mode Position  */
#define UMCTL2_MSTR_dll_off_mode_Msk     (0x1ul << UMCTL2_MSTR_dll_off_mode_Pos)           /*!< UMCTL2_T::MSTR: dll_off_mode Mask      */

#define UMCTL2_MSTR_burst_rdwr_Pos       (16)                                              /*!< UMCTL2_T::MSTR: burst_rdwr Position    */
#define UMCTL2_MSTR_burst_rdwr_Msk       (0xful << UMCTL2_MSTR_burst_rdwr_Pos)             /*!< UMCTL2_T::MSTR: burst_rdwr Mask        */

#define UMCTL2_MSTR_active_ranks_Pos     (24)                                              /*!< UMCTL2_T::MSTR: active_ranks Position  */
#define UMCTL2_MSTR_active_ranks_Msk     (0x3ul << UMCTL2_MSTR_active_ranks_Pos)           /*!< UMCTL2_T::MSTR: active_ranks Mask      */

#define UMCTL2_STAT_operating_mode_Pos   (0)                                               /*!< UMCTL2_T::STAT: operating_mode Position*/
#define UMCTL2_STAT_operating_mode_Msk   (0x3ul << UMCTL2_STAT_operating_mode_Pos)         /*!< UMCTL2_T::STAT: operating_mode Mask    */

#define UMCTL2_STAT_selfref_type_Pos     (4)                                               /*!< UMCTL2_T::STAT: selfref_type Position  */
#define UMCTL2_STAT_selfref_type_Msk     (0x3ul << UMCTL2_STAT_selfref_type_Pos)           /*!< UMCTL2_T::STAT: selfref_type Mask      */

#define UMCTL2_STAT_selfref_cam_not_empty_Pos (12)                                         /*!< UMCTL2_T::STAT: selfref_cam_not_empty Position*/
#define UMCTL2_STAT_selfref_cam_not_empty_Msk (0x1ul << UMCTL2_STAT_selfref_cam_not_empty_Pos) /*!< UMCTL2_T::STAT: selfref_cam_not_empty Mask*/

#define UMCTL2_MRCTRL0_mr_rank_Pos       (4)                                               /*!< UMCTL2_T::MRCTRL0: mr_rank Position    */
#define UMCTL2_MRCTRL0_mr_rank_Msk       (0x3ul << UMCTL2_MRCTRL0_mr_rank_Pos)             /*!< UMCTL2_T::MRCTRL0: mr_rank Mask        */

#define UMCTL2_MRCTRL0_mr_addr_Pos       (12)                                              /*!< UMCTL2_T::MRCTRL0: mr_addr Position    */
#define UMCTL2_MRCTRL0_mr_addr_Msk       (0xful << UMCTL2_MRCTRL0_mr_addr_Pos)             /*!< UMCTL2_T::MRCTRL0: mr_addr Mask        */

#define UMCTL2_MRCTRL0_mr_wr_Pos         (31)                                              /*!< UMCTL2_T::MRCTRL0: mr_wr Position      */
#define UMCTL2_MRCTRL0_mr_wr_Msk         (0x1ul << UMCTL2_MRCTRL0_mr_wr_Pos)               /*!< UMCTL2_T::MRCTRL0: mr_wr Mask          */

#define UMCTL2_MRCTRL1_mr_data_Pos       (0)                                               /*!< UMCTL2_T::MRCTRL1: mr_data Position    */
#define UMCTL2_MRCTRL1_mr_data_Msk       (0xfffful << UMCTL2_MRCTRL1_mr_data_Pos)          /*!< UMCTL2_T::MRCTRL1: mr_data Mask        */

#define UMCTL2_MRSTAT_mr_wr_busy_Pos     (0)                                               /*!< UMCTL2_T::MRSTAT: mr_wr_busy Position  */
#define UMCTL2_MRSTAT_mr_wr_busy_Msk     (0x1ul << UMCTL2_MRSTAT_mr_wr_busy_Pos)           /*!< UMCTL2_T::MRSTAT: mr_wr_busy Mask      */

#define UMCTL2_PWRCTL_selfref_en_Pos     (0)                                               /*!< UMCTL2_T::PWRCTL: selfref_en Position  */
#define UMCTL2_PWRCTL_selfref_en_Msk     (0x1ul << UMCTL2_PWRCTL_selfref_en_Pos)           /*!< UMCTL2_T::PWRCTL: selfref_en Mask      */

#define UMCTL2_PWRCTL_powerdown_en_Pos   (1)                                               /*!< UMCTL2_T::PWRCTL: powerdown_en Position*/
#define UMCTL2_PWRCTL_powerdown_en_Msk   (0x1ul << UMCTL2_PWRCTL_powerdown_en_Pos)         /*!< UMCTL2_T::PWRCTL: powerdown_en Mask    */

#define UMCTL2_PWRCTL_en_dfi_dram_clk_disable_Pos (3)                                      /*!< UMCTL2_T::PWRCTL: en_dfi_dram_clk_disable Position*/
#define UMCTL2_PWRCTL_en_dfi_dram_clk_disable_Msk (0x1ul << UMCTL2_PWRCTL_en_dfi_dram_clk_disable_Pos) /*!< UMCTL2_T::PWRCTL: en_dfi_dram_clk_disable Mask*/

#define UMCTL2_PWRCTL_selfref_sw_Pos     (5)                                               /*!< UMCTL2_T::PWRCTL: selfref_sw Position  */
#define UMCTL2_PWRCTL_selfref_sw_Msk     (0x1ul << UMCTL2_PWRCTL_selfref_sw_Pos)           /*!< UMCTL2_T::PWRCTL: selfref_sw Mask      */

#define UMCTL2_PWRCTL_dis_cam_drain_selfref_Pos (7)                                        /*!< UMCTL2_T::PWRCTL: dis_cam_drain_selfref Position*/
#define UMCTL2_PWRCTL_dis_cam_drain_selfref_Msk (0x1ul << UMCTL2_PWRCTL_dis_cam_drain_selfref_Pos) /*!< UMCTL2_T::PWRCTL: dis_cam_drain_selfref Mask*/

#define UMCTL2_PWRTMG_powerdown_to_x32_Pos (0)                                             /*!< UMCTL2_T::PWRTMG: powerdown_to_x32 Position*/
#define UMCTL2_PWRTMG_powerdown_to_x32_Msk (0x1ful << UMCTL2_PWRTMG_powerdown_to_x32_Pos)  /*!< UMCTL2_T::PWRTMG: powerdown_to_x32 Mask*/

#define UMCTL2_PWRTMG_selfref_to_x32_Pos (16)                                              /*!< UMCTL2_T::PWRTMG: selfref_to_x32 Position*/
#define UMCTL2_PWRTMG_selfref_to_x32_Msk (0xfful << UMCTL2_PWRTMG_selfref_to_x32_Pos)      /*!< UMCTL2_T::PWRTMG: selfref_to_x32 Mask  */

#define UMCTL2_HWLPCTL_hw_lp_en_Pos      (0)                                               /*!< UMCTL2_T::HWLPCTL: hw_lp_en Position   */
#define UMCTL2_HWLPCTL_hw_lp_en_Msk      (0x1ul << UMCTL2_HWLPCTL_hw_lp_en_Pos)            /*!< UMCTL2_T::HWLPCTL: hw_lp_en Mask       */

#define UMCTL2_HWLPCTL_hw_lp_exit_idle_en_Pos (1)                                          /*!< UMCTL2_T::HWLPCTL: hw_lp_exit_idle_en Position*/
#define UMCTL2_HWLPCTL_hw_lp_exit_idle_en_Msk (0x1ul << UMCTL2_HWLPCTL_hw_lp_exit_idle_en_Pos) /*!< UMCTL2_T::HWLPCTL: hw_lp_exit_idle_en Mask*/

#define UMCTL2_HWLPCTL_hw_lp_idle_x32_Pos (16)                                             /*!< UMCTL2_T::HWLPCTL: hw_lp_idle_x32 Position*/
#define UMCTL2_HWLPCTL_hw_lp_idle_x32_Msk (0xffful << UMCTL2_HWLPCTL_hw_lp_idle_x32_Pos)   /*!< UMCTL2_T::HWLPCTL: hw_lp_idle_x32 Mask */

#define UMCTL2_RFSHCTL0_refresh_burst_Pos (4)                                              /*!< UMCTL2_T::RFSHCTL0: refresh_burst Position*/
#define UMCTL2_RFSHCTL0_refresh_burst_Msk (0x3ful << UMCTL2_RFSHCTL0_refresh_burst_Pos)    /*!< UMCTL2_T::RFSHCTL0: refresh_burst Mask */

#define UMCTL2_RFSHCTL0_refresh_to_x1_x32_Pos (12)                                         /*!< UMCTL2_T::RFSHCTL0: refresh_to_x1_x32 Position*/
#define UMCTL2_RFSHCTL0_refresh_to_x1_x32_Msk (0x1ful << UMCTL2_RFSHCTL0_refresh_to_x1_x32_Pos) /*!< UMCTL2_T::RFSHCTL0: refresh_to_x1_x32 Mask*/

#define UMCTL2_RFSHCTL0_refresh_margin_Pos (20)                                            /*!< UMCTL2_T::RFSHCTL0: refresh_margin Position*/
#define UMCTL2_RFSHCTL0_refresh_margin_Msk (0xful << UMCTL2_RFSHCTL0_refresh_margin_Pos)   /*!< UMCTL2_T::RFSHCTL0: refresh_margin Mask*/

#define UMCTL2_RFSHCTL1_refresh_timer0_start_value_x32_Pos (0)                             /*!< UMCTL2_T::RFSHCTL1: refresh_timer0_start_value_x32 Position*/
#define UMCTL2_RFSHCTL1_refresh_timer0_start_value_x32_Msk (0xffful << UMCTL2_RFSHCTL1_refresh_timer0_start_value_x32_Pos) /*!< UMCTL2_T::RFSHCTL1: refresh_timer0_start_value_x32 Mask*/

#define UMCTL2_RFSHCTL1_refresh_timer1_start_value_x32_Pos (16)                            /*!< UMCTL2_T::RFSHCTL1: refresh_timer1_start_value_x32 Position*/
#define UMCTL2_RFSHCTL1_refresh_timer1_start_value_x32_Msk (0xffful << UMCTL2_RFSHCTL1_refresh_timer1_start_value_x32_Pos) /*!< UMCTL2_T::RFSHCTL1: refresh_timer1_start_value_x32 Mask*/

#define UMCTL2_RFSHCTL3_dis_auto_refresh_Pos (0)                                           /*!< UMCTL2_T::RFSHCTL3: dis_auto_refresh Position*/
#define UMCTL2_RFSHCTL3_dis_auto_refresh_Msk (0x1ul << UMCTL2_RFSHCTL3_dis_auto_refresh_Pos) /*!< UMCTL2_T::RFSHCTL3: dis_auto_refresh Mask*/

#define UMCTL2_RFSHCTL3_refresh_update_level_Pos (1)                                       /*!< UMCTL2_T::RFSHCTL3: refresh_update_level Position*/
#define UMCTL2_RFSHCTL3_refresh_update_level_Msk (0x1ul << UMCTL2_RFSHCTL3_refresh_update_level_Pos) /*!< UMCTL2_T::RFSHCTL3: refresh_update_level Mask*/

#define UMCTL2_RFSHTMG_t_rfc_min_Pos     (0)                                               /*!< UMCTL2_T::RFSHTMG: t_rfc_min Position  */
#define UMCTL2_RFSHTMG_t_rfc_min_Msk     (0x3fful << UMCTL2_RFSHTMG_t_rfc_min_Pos)         /*!< UMCTL2_T::RFSHTMG: t_rfc_min Mask      */

#define UMCTL2_RFSHTMG_t_rfc_nom_x1_x32_Pos (16)                                           /*!< UMCTL2_T::RFSHTMG: t_rfc_nom_x1_x32 Position*/
#define UMCTL2_RFSHTMG_t_rfc_nom_x1_x32_Msk (0xffful << UMCTL2_RFSHTMG_t_rfc_nom_x1_x32_Pos) /*!< UMCTL2_T::RFSHTMG: t_rfc_nom_x1_x32 Mask*/

#define UMCTL2_CRCPARCTL0_dfi_alert_err_int_en_Pos (0)                                     /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_int_en Position*/
#define UMCTL2_CRCPARCTL0_dfi_alert_err_int_en_Msk (0x1ul << UMCTL2_CRCPARCTL0_dfi_alert_err_int_en_Pos) /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_int_en Mask*/

#define UMCTL2_CRCPARCTL0_dfi_alert_err_int_clr_Pos (1)                                    /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_int_clr Position*/
#define UMCTL2_CRCPARCTL0_dfi_alert_err_int_clr_Msk (0x1ul << UMCTL2_CRCPARCTL0_dfi_alert_err_int_clr_Pos) /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_int_clr Mask*/

#define UMCTL2_CRCPARCTL0_dfi_alert_err_cnt_clr_Pos (2)                                    /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_cnt_clr Position*/
#define UMCTL2_CRCPARCTL0_dfi_alert_err_cnt_clr_Msk (0x1ul << UMCTL2_CRCPARCTL0_dfi_alert_err_cnt_clr_Pos) /*!< UMCTL2_T::CRCPARCTL0: dfi_alert_err_cnt_clr Mask*/

#define UMCTL2_CRCPARSTAT_dfi_alert_err_cnt_Pos (0)                                        /*!< UMCTL2_T::CRCPARSTAT: dfi_alert_err_cnt Position*/
#define UMCTL2_CRCPARSTAT_dfi_alert_err_cnt_Msk (0xfffful << UMCTL2_CRCPARSTAT_dfi_alert_err_cnt_Pos) /*!< UMCTL2_T::CRCPARSTAT: dfi_alert_err_cnt Mask*/

#define UMCTL2_CRCPARSTAT_dfi_alert_err_int_Pos (16)                                       /*!< UMCTL2_T::CRCPARSTAT: dfi_alert_err_int Position*/
#define UMCTL2_CRCPARSTAT_dfi_alert_err_int_Msk (0x1ul << UMCTL2_CRCPARSTAT_dfi_alert_err_int_Pos) /*!< UMCTL2_T::CRCPARSTAT: dfi_alert_err_int Mask*/

#define UMCTL2_INIT0_pre_cke_x1024_Pos   (0)                                               /*!< UMCTL2_T::INIT0: pre_cke_x1024 Position*/
#define UMCTL2_INIT0_pre_cke_x1024_Msk   (0xffful << UMCTL2_INIT0_pre_cke_x1024_Pos)       /*!< UMCTL2_T::INIT0: pre_cke_x1024 Mask    */

#define UMCTL2_INIT0_post_cke_x1024_Pos  (16)                                              /*!< UMCTL2_T::INIT0: post_cke_x1024 Position*/
#define UMCTL2_INIT0_post_cke_x1024_Msk  (0x3fful << UMCTL2_INIT0_post_cke_x1024_Pos)      /*!< UMCTL2_T::INIT0: post_cke_x1024 Mask   */

#define UMCTL2_INIT0_skip_dram_init_Pos  (30)                                              /*!< UMCTL2_T::INIT0: skip_dram_init Position*/
#define UMCTL2_INIT0_skip_dram_init_Msk  (0x3ul << UMCTL2_INIT0_skip_dram_init_Pos)        /*!< UMCTL2_T::INIT0: skip_dram_init Mask   */

#define UMCTL2_INIT1_pre_ocd_x32_Pos     (0)                                               /*!< UMCTL2_T::INIT1: pre_ocd_x32 Position  */
#define UMCTL2_INIT1_pre_ocd_x32_Msk     (0xful << UMCTL2_INIT1_pre_ocd_x32_Pos)           /*!< UMCTL2_T::INIT1: pre_ocd_x32 Mask      */

#define UMCTL2_INIT1_dram_rstn_x1024_Pos (16)                                              /*!< UMCTL2_T::INIT1: dram_rstn_x1024 Position*/
#define UMCTL2_INIT1_dram_rstn_x1024_Msk (0x1fful << UMCTL2_INIT1_dram_rstn_x1024_Pos)     /*!< UMCTL2_T::INIT1: dram_rstn_x1024 Mask  */

#define UMCTL2_INIT3_emr_Pos             (0)                                               /*!< UMCTL2_T::INIT3: emr Position          */
#define UMCTL2_INIT3_emr_Msk             (0xfffful << UMCTL2_INIT3_emr_Pos)                /*!< UMCTL2_T::INIT3: emr Mask              */

#define UMCTL2_INIT3_mr_Pos              (16)                                              /*!< UMCTL2_T::INIT3: mr Position           */
#define UMCTL2_INIT3_mr_Msk              (0xfffful << UMCTL2_INIT3_mr_Pos)                 /*!< UMCTL2_T::INIT3: mr Mask               */

#define UMCTL2_INIT4_emr3_Pos            (0)                                               /*!< UMCTL2_T::INIT4: emr3 Position         */
#define UMCTL2_INIT4_emr3_Msk            (0xfffful << UMCTL2_INIT4_emr3_Pos)               /*!< UMCTL2_T::INIT4: emr3 Mask             */

#define UMCTL2_INIT4_emr2_Pos            (16)                                              /*!< UMCTL2_T::INIT4: emr2 Position         */
#define UMCTL2_INIT4_emr2_Msk            (0xfffful << UMCTL2_INIT4_emr2_Pos)               /*!< UMCTL2_T::INIT4: emr2 Mask             */

#define UMCTL2_INIT5_dev_zqinit_x32_Pos  (16)                                              /*!< UMCTL2_T::INIT5: dev_zqinit_x32 Position*/
#define UMCTL2_INIT5_dev_zqinit_x32_Msk  (0xfful << UMCTL2_INIT5_dev_zqinit_x32_Pos)       /*!< UMCTL2_T::INIT5: dev_zqinit_x32 Mask   */

#define UMCTL2_DIMMCTL_dimm_stagger_cs_en_Pos (0)                                          /*!< UMCTL2_T::DIMMCTL: dimm_stagger_cs_en Position*/
#define UMCTL2_DIMMCTL_dimm_stagger_cs_en_Msk (0x1ul << UMCTL2_DIMMCTL_dimm_stagger_cs_en_Pos) /*!< UMCTL2_T::DIMMCTL: dimm_stagger_cs_en Mask*/

#define UMCTL2_DIMMCTL_dimm_addr_mirr_en_Pos (1)                                           /*!< UMCTL2_T::DIMMCTL: dimm_addr_mirr_en Position*/
#define UMCTL2_DIMMCTL_dimm_addr_mirr_en_Msk (0x1ul << UMCTL2_DIMMCTL_dimm_addr_mirr_en_Pos) /*!< UMCTL2_T::DIMMCTL: dimm_addr_mirr_en Mask*/

#define UMCTL2_RANKCTL_max_rank_rd_Pos   (0)                                               /*!< UMCTL2_T::RANKCTL: max_rank_rd Position*/
#define UMCTL2_RANKCTL_max_rank_rd_Msk   (0xful << UMCTL2_RANKCTL_max_rank_rd_Pos)         /*!< UMCTL2_T::RANKCTL: max_rank_rd Mask    */

#define UMCTL2_RANKCTL_diff_rank_rd_gap_Pos (4)                                            /*!< UMCTL2_T::RANKCTL: diff_rank_rd_gap Position*/
#define UMCTL2_RANKCTL_diff_rank_rd_gap_Msk (0xful << UMCTL2_RANKCTL_diff_rank_rd_gap_Pos) /*!< UMCTL2_T::RANKCTL: diff_rank_rd_gap Mask*/

#define UMCTL2_RANKCTL_diff_rank_wr_gap_Pos (8)                                            /*!< UMCTL2_T::RANKCTL: diff_rank_wr_gap Position*/
#define UMCTL2_RANKCTL_diff_rank_wr_gap_Msk (0xful << UMCTL2_RANKCTL_diff_rank_wr_gap_Pos) /*!< UMCTL2_T::RANKCTL: diff_rank_wr_gap Mask*/

#define UMCTL2_RANKCTL_max_rank_wr_Pos   (12)                                              /*!< UMCTL2_T::RANKCTL: max_rank_wr Position*/
#define UMCTL2_RANKCTL_max_rank_wr_Msk   (0xful << UMCTL2_RANKCTL_max_rank_wr_Pos)         /*!< UMCTL2_T::RANKCTL: max_rank_wr Mask    */

#define UMCTL2_RANKCTL_diff_rank_rd_gap_msb_Pos (24)                                       /*!< UMCTL2_T::RANKCTL: diff_rank_rd_gap_msb Position*/
#define UMCTL2_RANKCTL_diff_rank_rd_gap_msb_Msk (0x1ul << UMCTL2_RANKCTL_diff_rank_rd_gap_msb_Pos) /*!< UMCTL2_T::RANKCTL: diff_rank_rd_gap_msb Mask*/

#define UMCTL2_RANKCTL_diff_rank_wr_gap_msb_Pos (26)                                       /*!< UMCTL2_T::RANKCTL: diff_rank_wr_gap_msb Position*/
#define UMCTL2_RANKCTL_diff_rank_wr_gap_msb_Msk (0x1ul << UMCTL2_RANKCTL_diff_rank_wr_gap_msb_Pos) /*!< UMCTL2_T::RANKCTL: diff_rank_wr_gap_msb Mask*/

#define UMCTL2_DRAMTMG0_t_ras_min_Pos    (0)                                               /*!< UMCTL2_T::DRAMTMG0: t_ras_min Position */
#define UMCTL2_DRAMTMG0_t_ras_min_Msk    (0x3ful << UMCTL2_DRAMTMG0_t_ras_min_Pos)         /*!< UMCTL2_T::DRAMTMG0: t_ras_min Mask     */

#define UMCTL2_DRAMTMG0_t_ras_max_Pos    (8)                                               /*!< UMCTL2_T::DRAMTMG0: t_ras_max Position */
#define UMCTL2_DRAMTMG0_t_ras_max_Msk    (0x7ful << UMCTL2_DRAMTMG0_t_ras_max_Pos)         /*!< UMCTL2_T::DRAMTMG0: t_ras_max Mask     */

#define UMCTL2_DRAMTMG0_t_faw_Pos        (16)                                              /*!< UMCTL2_T::DRAMTMG0: t_faw Position     */
#define UMCTL2_DRAMTMG0_t_faw_Msk        (0x3ful << UMCTL2_DRAMTMG0_t_faw_Pos)             /*!< UMCTL2_T::DRAMTMG0: t_faw Mask         */

#define UMCTL2_DRAMTMG0_wr2pre_Pos       (24)                                              /*!< UMCTL2_T::DRAMTMG0: wr2pre Position    */
#define UMCTL2_DRAMTMG0_wr2pre_Msk       (0x7ful << UMCTL2_DRAMTMG0_wr2pre_Pos)            /*!< UMCTL2_T::DRAMTMG0: wr2pre Mask        */

#define UMCTL2_DRAMTMG1_t_rc_Pos         (0)                                               /*!< UMCTL2_T::DRAMTMG1: t_rc Position      */
#define UMCTL2_DRAMTMG1_t_rc_Msk         (0x7ful << UMCTL2_DRAMTMG1_t_rc_Pos)              /*!< UMCTL2_T::DRAMTMG1: t_rc Mask          */

#define UMCTL2_DRAMTMG1_rd2pre_Pos       (8)                                               /*!< UMCTL2_T::DRAMTMG1: rd2pre Position    */
#define UMCTL2_DRAMTMG1_rd2pre_Msk       (0x3ful << UMCTL2_DRAMTMG1_rd2pre_Pos)            /*!< UMCTL2_T::DRAMTMG1: rd2pre Mask        */

#define UMCTL2_DRAMTMG1_t_xp_Pos         (16)                                              /*!< UMCTL2_T::DRAMTMG1: t_xp Position      */
#define UMCTL2_DRAMTMG1_t_xp_Msk         (0x1ful << UMCTL2_DRAMTMG1_t_xp_Pos)              /*!< UMCTL2_T::DRAMTMG1: t_xp Mask          */

#define UMCTL2_DRAMTMG2_wr2rd_Pos        (0)                                               /*!< UMCTL2_T::DRAMTMG2: wr2rd Position     */
#define UMCTL2_DRAMTMG2_wr2rd_Msk        (0x3ful << UMCTL2_DRAMTMG2_wr2rd_Pos)             /*!< UMCTL2_T::DRAMTMG2: wr2rd Mask         */

#define UMCTL2_DRAMTMG2_rd2wr_Pos        (8)                                               /*!< UMCTL2_T::DRAMTMG2: rd2wr Position     */
#define UMCTL2_DRAMTMG2_rd2wr_Msk        (0x3ful << UMCTL2_DRAMTMG2_rd2wr_Pos)             /*!< UMCTL2_T::DRAMTMG2: rd2wr Mask         */

#define UMCTL2_DRAMTMG3_t_mod_Pos        (0)                                               /*!< UMCTL2_T::DRAMTMG3: t_mod Position     */
#define UMCTL2_DRAMTMG3_t_mod_Msk        (0x3fful << UMCTL2_DRAMTMG3_t_mod_Pos)            /*!< UMCTL2_T::DRAMTMG3: t_mod Mask         */

#define UMCTL2_DRAMTMG3_t_mrd_Pos        (12)                                              /*!< UMCTL2_T::DRAMTMG3: t_mrd Position     */
#define UMCTL2_DRAMTMG3_t_mrd_Msk        (0x3ful << UMCTL2_DRAMTMG3_t_mrd_Pos)             /*!< UMCTL2_T::DRAMTMG3: t_mrd Mask         */

#define UMCTL2_DRAMTMG4_t_rp_Pos         (0)                                               /*!< UMCTL2_T::DRAMTMG4: t_rp Position      */
#define UMCTL2_DRAMTMG4_t_rp_Msk         (0x1ful << UMCTL2_DRAMTMG4_t_rp_Pos)              /*!< UMCTL2_T::DRAMTMG4: t_rp Mask          */

#define UMCTL2_DRAMTMG4_t_rrd_Pos        (8)                                               /*!< UMCTL2_T::DRAMTMG4: t_rrd Position     */
#define UMCTL2_DRAMTMG4_t_rrd_Msk        (0xful << UMCTL2_DRAMTMG4_t_rrd_Pos)              /*!< UMCTL2_T::DRAMTMG4: t_rrd Mask         */

#define UMCTL2_DRAMTMG4_t_ccd_Pos        (16)                                              /*!< UMCTL2_T::DRAMTMG4: t_ccd Position     */
#define UMCTL2_DRAMTMG4_t_ccd_Msk        (0xful << UMCTL2_DRAMTMG4_t_ccd_Pos)              /*!< UMCTL2_T::DRAMTMG4: t_ccd Mask         */

#define UMCTL2_DRAMTMG4_t_rcd_Pos        (24)                                              /*!< UMCTL2_T::DRAMTMG4: t_rcd Position     */
#define UMCTL2_DRAMTMG4_t_rcd_Msk        (0x1ful << UMCTL2_DRAMTMG4_t_rcd_Pos)             /*!< UMCTL2_T::DRAMTMG4: t_rcd Mask         */

#define UMCTL2_DRAMTMG5_t_cke_Pos        (0)                                               /*!< UMCTL2_T::DRAMTMG5: t_cke Position     */
#define UMCTL2_DRAMTMG5_t_cke_Msk        (0x1ful << UMCTL2_DRAMTMG5_t_cke_Pos)             /*!< UMCTL2_T::DRAMTMG5: t_cke Mask         */

#define UMCTL2_DRAMTMG5_t_ckesr_Pos      (8)                                               /*!< UMCTL2_T::DRAMTMG5: t_ckesr Position   */
#define UMCTL2_DRAMTMG5_t_ckesr_Msk      (0x3ful << UMCTL2_DRAMTMG5_t_ckesr_Pos)           /*!< UMCTL2_T::DRAMTMG5: t_ckesr Mask       */

#define UMCTL2_DRAMTMG5_t_cksre_Pos      (16)                                              /*!< UMCTL2_T::DRAMTMG5: t_cksre Position   */
#define UMCTL2_DRAMTMG5_t_cksre_Msk      (0x7ful << UMCTL2_DRAMTMG5_t_cksre_Pos)           /*!< UMCTL2_T::DRAMTMG5: t_cksre Mask       */

#define UMCTL2_DRAMTMG5_t_cksrx_Pos      (24)                                              /*!< UMCTL2_T::DRAMTMG5: t_cksrx Position   */
#define UMCTL2_DRAMTMG5_t_cksrx_Msk      (0xful << UMCTL2_DRAMTMG5_t_cksrx_Pos)            /*!< UMCTL2_T::DRAMTMG5: t_cksrx Mask       */

#define UMCTL2_DRAMTMG8_t_xs_x32_Pos     (0)                                               /*!< UMCTL2_T::DRAMTMG8: t_xs_x32 Position  */
#define UMCTL2_DRAMTMG8_t_xs_x32_Msk     (0x7ful << UMCTL2_DRAMTMG8_t_xs_x32_Pos)          /*!< UMCTL2_T::DRAMTMG8: t_xs_x32 Mask      */

#define UMCTL2_DRAMTMG8_t_xs_dll_x32_Pos (8)                                               /*!< UMCTL2_T::DRAMTMG8: t_xs_dll_x32 Position*/
#define UMCTL2_DRAMTMG8_t_xs_dll_x32_Msk (0x7ful << UMCTL2_DRAMTMG8_t_xs_dll_x32_Pos)      /*!< UMCTL2_T::DRAMTMG8: t_xs_dll_x32 Mask  */

#define UMCTL2_DRAMTMG15_t_stab_x32_Pos  (0)                                               /*!< UMCTL2_T::DRAMTMG15: t_stab_x32 Position*/
#define UMCTL2_DRAMTMG15_t_stab_x32_Msk  (0xfful << UMCTL2_DRAMTMG15_t_stab_x32_Pos)       /*!< UMCTL2_T::DRAMTMG15: t_stab_x32 Mask   */

#define UMCTL2_DRAMTMG15_en_dfi_lp_t_stab_Pos (31)                                         /*!< UMCTL2_T::DRAMTMG15: en_dfi_lp_t_stab Position*/
#define UMCTL2_DRAMTMG15_en_dfi_lp_t_stab_Msk (0x1ul << UMCTL2_DRAMTMG15_en_dfi_lp_t_stab_Pos) /*!< UMCTL2_T::DRAMTMG15: en_dfi_lp_t_stab Mask*/

#define UMCTL2_ZQCTL0_t_zq_short_nop_Pos (0)                                               /*!< UMCTL2_T::ZQCTL0: t_zq_short_nop Position*/
#define UMCTL2_ZQCTL0_t_zq_short_nop_Msk (0x3fful << UMCTL2_ZQCTL0_t_zq_short_nop_Pos)     /*!< UMCTL2_T::ZQCTL0: t_zq_short_nop Mask  */

#define UMCTL2_ZQCTL0_t_zq_long_nop_Pos  (16)                                              /*!< UMCTL2_T::ZQCTL0: t_zq_long_nop Position*/
#define UMCTL2_ZQCTL0_t_zq_long_nop_Msk  (0x7fful << UMCTL2_ZQCTL0_t_zq_long_nop_Pos)      /*!< UMCTL2_T::ZQCTL0: t_zq_long_nop Mask   */

#define UMCTL2_ZQCTL0_zq_resistor_shared_Pos (29)                                          /*!< UMCTL2_T::ZQCTL0: zq_resistor_shared Position*/
#define UMCTL2_ZQCTL0_zq_resistor_shared_Msk (0x1ul << UMCTL2_ZQCTL0_zq_resistor_shared_Pos) /*!< UMCTL2_T::ZQCTL0: zq_resistor_shared Mask*/

#define UMCTL2_ZQCTL0_dis_srx_zqcl_Pos   (30)                                              /*!< UMCTL2_T::ZQCTL0: dis_srx_zqcl Position*/
#define UMCTL2_ZQCTL0_dis_srx_zqcl_Msk   (0x1ul << UMCTL2_ZQCTL0_dis_srx_zqcl_Pos)         /*!< UMCTL2_T::ZQCTL0: dis_srx_zqcl Mask    */

#define UMCTL2_ZQCTL0_dis_auto_zq_Pos    (31)                                              /*!< UMCTL2_T::ZQCTL0: dis_auto_zq Position */
#define UMCTL2_ZQCTL0_dis_auto_zq_Msk    (0x1ul << UMCTL2_ZQCTL0_dis_auto_zq_Pos)          /*!< UMCTL2_T::ZQCTL0: dis_auto_zq Mask     */

#define UMCTL2_ZQCTL1_t_zq_short_interval_x1024_Pos (0)                                    /*!< UMCTL2_T::ZQCTL1: t_zq_short_interval_x1024 Position*/
#define UMCTL2_ZQCTL1_t_zq_short_interval_x1024_Msk (0xffffful << UMCTL2_ZQCTL1_t_zq_short_interval_x1024_Pos) /*!< UMCTL2_T::ZQCTL1: t_zq_short_interval_x1024 Mask*/

#define UMCTL2_DFITMG0_dfi_tphy_wrlat_Pos (0)                                              /*!< UMCTL2_T::DFITMG0: dfi_tphy_wrlat Position*/
#define UMCTL2_DFITMG0_dfi_tphy_wrlat_Msk (0x3ful << UMCTL2_DFITMG0_dfi_tphy_wrlat_Pos)    /*!< UMCTL2_T::DFITMG0: dfi_tphy_wrlat Mask */

#define UMCTL2_DFITMG0_dfi_tphy_wrdata_Pos (8)                                             /*!< UMCTL2_T::DFITMG0: dfi_tphy_wrdata Position*/
#define UMCTL2_DFITMG0_dfi_tphy_wrdata_Msk (0x3ful << UMCTL2_DFITMG0_dfi_tphy_wrdata_Pos)  /*!< UMCTL2_T::DFITMG0: dfi_tphy_wrdata Mask*/

#define UMCTL2_DFITMG0_dfi_wrdata_use_dfi_phy_clk_Pos (15)                                 /*!< UMCTL2_T::DFITMG0: dfi_wrdata_use_dfi_phy_clk Position*/
#define UMCTL2_DFITMG0_dfi_wrdata_use_dfi_phy_clk_Msk (0x1ul << UMCTL2_DFITMG0_dfi_wrdata_use_dfi_phy_clk_Pos) /*!< UMCTL2_T::DFITMG0: dfi_wrdata_use_dfi_phy_clk Mask*/

#define UMCTL2_DFITMG0_dfi_t_rddata_en_Pos (16)                                            /*!< UMCTL2_T::DFITMG0: dfi_t_rddata_en Position*/
#define UMCTL2_DFITMG0_dfi_t_rddata_en_Msk (0x7ful << UMCTL2_DFITMG0_dfi_t_rddata_en_Pos)  /*!< UMCTL2_T::DFITMG0: dfi_t_rddata_en Mask*/

#define UMCTL2_DFITMG0_dfi_rddata_use_dfi_phy_clk_Pos (23)                                 /*!< UMCTL2_T::DFITMG0: dfi_rddata_use_dfi_phy_clk Position*/
#define UMCTL2_DFITMG0_dfi_rddata_use_dfi_phy_clk_Msk (0x1ul << UMCTL2_DFITMG0_dfi_rddata_use_dfi_phy_clk_Pos) /*!< UMCTL2_T::DFITMG0: dfi_rddata_use_dfi_phy_clk Mask*/

#define UMCTL2_DFITMG0_dfi_t_ctrl_delay_Pos (24)                                           /*!< UMCTL2_T::DFITMG0: dfi_t_ctrl_delay Position*/
#define UMCTL2_DFITMG0_dfi_t_ctrl_delay_Msk (0x1ful << UMCTL2_DFITMG0_dfi_t_ctrl_delay_Pos) /*!< UMCTL2_T::DFITMG0: dfi_t_ctrl_delay Mask*/

#define UMCTL2_DFITMG1_dfi_t_dram_clk_enable_Pos (0)                                       /*!< UMCTL2_T::DFITMG1: dfi_t_dram_clk_enable Position*/
#define UMCTL2_DFITMG1_dfi_t_dram_clk_enable_Msk (0x1ful << UMCTL2_DFITMG1_dfi_t_dram_clk_enable_Pos) /*!< UMCTL2_T::DFITMG1: dfi_t_dram_clk_enable Mask*/

#define UMCTL2_DFITMG1_dfi_t_dram_clk_disable_Pos (8)                                      /*!< UMCTL2_T::DFITMG1: dfi_t_dram_clk_disable Position*/
#define UMCTL2_DFITMG1_dfi_t_dram_clk_disable_Msk (0x1ful << UMCTL2_DFITMG1_dfi_t_dram_clk_disable_Pos) /*!< UMCTL2_T::DFITMG1: dfi_t_dram_clk_disable Mask*/

#define UMCTL2_DFITMG1_dfi_t_wrdata_delay_Pos (16)                                         /*!< UMCTL2_T::DFITMG1: dfi_t_wrdata_delay Position*/
#define UMCTL2_DFITMG1_dfi_t_wrdata_delay_Msk (0x1ful << UMCTL2_DFITMG1_dfi_t_wrdata_delay_Pos) /*!< UMCTL2_T::DFITMG1: dfi_t_wrdata_delay Mask*/

#define UMCTL2_DFITMG1_dfi_t_parin_lat_Pos (24)                                            /*!< UMCTL2_T::DFITMG1: dfi_t_parin_lat Position*/
#define UMCTL2_DFITMG1_dfi_t_parin_lat_Msk (0x3ul << UMCTL2_DFITMG1_dfi_t_parin_lat_Pos)   /*!< UMCTL2_T::DFITMG1: dfi_t_parin_lat Mask*/

#define UMCTL2_DFILPCFG0_dfi_lp_en_pd_Pos (0)                                              /*!< UMCTL2_T::DFILPCFG0: dfi_lp_en_pd Position*/
#define UMCTL2_DFILPCFG0_dfi_lp_en_pd_Msk (0x1ul << UMCTL2_DFILPCFG0_dfi_lp_en_pd_Pos)     /*!< UMCTL2_T::DFILPCFG0: dfi_lp_en_pd Mask */

#define UMCTL2_DFILPCFG0_dfi_lp_wakeup_pd_Pos (4)                                          /*!< UMCTL2_T::DFILPCFG0: dfi_lp_wakeup_pd Position*/
#define UMCTL2_DFILPCFG0_dfi_lp_wakeup_pd_Msk (0xful << UMCTL2_DFILPCFG0_dfi_lp_wakeup_pd_Pos) /*!< UMCTL2_T::DFILPCFG0: dfi_lp_wakeup_pd Mask*/

#define UMCTL2_DFILPCFG0_dfi_lp_en_sr_Pos (8)                                              /*!< UMCTL2_T::DFILPCFG0: dfi_lp_en_sr Position*/
#define UMCTL2_DFILPCFG0_dfi_lp_en_sr_Msk (0x1ul << UMCTL2_DFILPCFG0_dfi_lp_en_sr_Pos)     /*!< UMCTL2_T::DFILPCFG0: dfi_lp_en_sr Mask */

#define UMCTL2_DFILPCFG0_dfi_lp_wakeup_sr_Pos (12)                                         /*!< UMCTL2_T::DFILPCFG0: dfi_lp_wakeup_sr Position*/
#define UMCTL2_DFILPCFG0_dfi_lp_wakeup_sr_Msk (0xful << UMCTL2_DFILPCFG0_dfi_lp_wakeup_sr_Pos) /*!< UMCTL2_T::DFILPCFG0: dfi_lp_wakeup_sr Mask*/

#define UMCTL2_DFILPCFG0_dfi_tlp_resp_Pos (24)                                             /*!< UMCTL2_T::DFILPCFG0: dfi_tlp_resp Position*/
#define UMCTL2_DFILPCFG0_dfi_tlp_resp_Msk (0x1ful << UMCTL2_DFILPCFG0_dfi_tlp_resp_Pos)    /*!< UMCTL2_T::DFILPCFG0: dfi_tlp_resp Mask */

#define UMCTL2_DFIUPD0_dfi_t_ctrlup_min_Pos (0)                                            /*!< UMCTL2_T::DFIUPD0: dfi_t_ctrlup_min Position*/
#define UMCTL2_DFIUPD0_dfi_t_ctrlup_min_Msk (0x3fful << UMCTL2_DFIUPD0_dfi_t_ctrlup_min_Pos) /*!< UMCTL2_T::DFIUPD0: dfi_t_ctrlup_min Mask*/

#define UMCTL2_DFIUPD0_dfi_t_ctrlup_max_Pos (16)                                           /*!< UMCTL2_T::DFIUPD0: dfi_t_ctrlup_max Position*/
#define UMCTL2_DFIUPD0_dfi_t_ctrlup_max_Msk (0x3fful << UMCTL2_DFIUPD0_dfi_t_ctrlup_max_Pos) /*!< UMCTL2_T::DFIUPD0: dfi_t_ctrlup_max Mask*/

#define UMCTL2_DFIUPD0_ctrlupd_pre_srx_Pos (29)                                            /*!< UMCTL2_T::DFIUPD0: ctrlupd_pre_srx Position*/
#define UMCTL2_DFIUPD0_ctrlupd_pre_srx_Msk (0x1ul << UMCTL2_DFIUPD0_ctrlupd_pre_srx_Pos)   /*!< UMCTL2_T::DFIUPD0: ctrlupd_pre_srx Mask*/

#define UMCTL2_DFIUPD0_dis_auto_ctrlupd_srx_Pos (30)                                       /*!< UMCTL2_T::DFIUPD0: dis_auto_ctrlupd_srx Position*/
#define UMCTL2_DFIUPD0_dis_auto_ctrlupd_srx_Msk (0x1ul << UMCTL2_DFIUPD0_dis_auto_ctrlupd_srx_Pos) /*!< UMCTL2_T::DFIUPD0: dis_auto_ctrlupd_srx Mask*/

#define UMCTL2_DFIUPD0_dis_auto_ctrlupd_Pos (31)                                           /*!< UMCTL2_T::DFIUPD0: dis_auto_ctrlupd Position*/
#define UMCTL2_DFIUPD0_dis_auto_ctrlupd_Msk (0x1ul << UMCTL2_DFIUPD0_dis_auto_ctrlupd_Pos) /*!< UMCTL2_T::DFIUPD0: dis_auto_ctrlupd Mask*/

#define UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_max_x1024_Pos (0)                            /*!< UMCTL2_T::DFIUPD1: dfi_t_ctrlupd_interval_max_x1024 Position*/
#define UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_max_x1024_Msk (0xfful << UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_max_x1024_Pos) /*!< UMCTL2_T::DFIUPD1: dfi_t_ctrlupd_interval_max_x1024 Mask*/

#define UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_min_x1024_Pos (16)                           /*!< UMCTL2_T::DFIUPD1: dfi_t_ctrlupd_interval_min_x1024 Position*/
#define UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_min_x1024_Msk (0xfful << UMCTL2_DFIUPD1_dfi_t_ctrlupd_interval_min_x1024_Pos) /*!< UMCTL2_T::DFIUPD1: dfi_t_ctrlupd_interval_min_x1024 Mask*/

#define UMCTL2_DFIUPD2_dfi_phyupd_en_Pos (31)                                              /*!< UMCTL2_T::DFIUPD2: dfi_phyupd_en Position*/
#define UMCTL2_DFIUPD2_dfi_phyupd_en_Msk (0x1ul << UMCTL2_DFIUPD2_dfi_phyupd_en_Pos)       /*!< UMCTL2_T::DFIUPD2: dfi_phyupd_en Mask  */

#define UMCTL2_DFIMISC_dfi_init_complete_en_Pos (0)                                        /*!< UMCTL2_T::DFIMISC: dfi_init_complete_en Position*/
#define UMCTL2_DFIMISC_dfi_init_complete_en_Msk (0x1ul << UMCTL2_DFIMISC_dfi_init_complete_en_Pos) /*!< UMCTL2_T::DFIMISC: dfi_init_complete_en Mask*/

#define UMCTL2_DFIMISC_ctl_idle_en_Pos   (4)                                               /*!< UMCTL2_T::DFIMISC: ctl_idle_en Position*/
#define UMCTL2_DFIMISC_ctl_idle_en_Msk   (0x1ul << UMCTL2_DFIMISC_ctl_idle_en_Pos)         /*!< UMCTL2_T::DFIMISC: ctl_idle_en Mask    */

#define UMCTL2_DFIMISC_dfi_init_start_Pos (5)                                              /*!< UMCTL2_T::DFIMISC: dfi_init_start Position*/
#define UMCTL2_DFIMISC_dfi_init_start_Msk (0x1ul << UMCTL2_DFIMISC_dfi_init_start_Pos)     /*!< UMCTL2_T::DFIMISC: dfi_init_start Mask */

#define UMCTL2_DFIMISC_dfi_frequency_Pos (8)                                               /*!< UMCTL2_T::DFIMISC: dfi_frequency Position*/
#define UMCTL2_DFIMISC_dfi_frequency_Msk (0x1ful << UMCTL2_DFIMISC_dfi_frequency_Pos)      /*!< UMCTL2_T::DFIMISC: dfi_frequency Mask  */

#define UMCTL2_DFISTAT_dfi_init_complete_Pos (0)                                           /*!< UMCTL2_T::DFISTAT: dfi_init_complete Position*/
#define UMCTL2_DFISTAT_dfi_init_complete_Msk (0x1ul << UMCTL2_DFISTAT_dfi_init_complete_Pos) /*!< UMCTL2_T::DFISTAT: dfi_init_complete Mask*/

#define UMCTL2_DFISTAT_dfi_lp_ack_Pos    (1)                                               /*!< UMCTL2_T::DFISTAT: dfi_lp_ack Position */
#define UMCTL2_DFISTAT_dfi_lp_ack_Msk    (0x1ul << UMCTL2_DFISTAT_dfi_lp_ack_Pos)          /*!< UMCTL2_T::DFISTAT: dfi_lp_ack Mask     */

#define UMCTL2_DFIPHYMSTR_dfi_phymstr_en_Pos (0)                                           /*!< UMCTL2_T::DFIPHYMSTR: dfi_phymstr_en Position*/
#define UMCTL2_DFIPHYMSTR_dfi_phymstr_en_Msk (0x1ul << UMCTL2_DFIPHYMSTR_dfi_phymstr_en_Pos) /*!< UMCTL2_T::DFIPHYMSTR: dfi_phymstr_en Mask*/

#define UMCTL2_ADDRMAP0_addrmap_cs_bit0_Pos (0)                                            /*!< UMCTL2_T::ADDRMAP0: addrmap_cs_bit0 Position*/
#define UMCTL2_ADDRMAP0_addrmap_cs_bit0_Msk (0x1ful << UMCTL2_ADDRMAP0_addrmap_cs_bit0_Pos) /*!< UMCTL2_T::ADDRMAP0: addrmap_cs_bit0 Mask*/

#define UMCTL2_ADDRMAP1_addrmap_bank_b0_Pos (0)                                            /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b0 Position*/
#define UMCTL2_ADDRMAP1_addrmap_bank_b0_Msk (0x3ful << UMCTL2_ADDRMAP1_addrmap_bank_b0_Pos) /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b0 Mask*/

#define UMCTL2_ADDRMAP1_addrmap_bank_b1_Pos (8)                                            /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b1 Position*/
#define UMCTL2_ADDRMAP1_addrmap_bank_b1_Msk (0x3ful << UMCTL2_ADDRMAP1_addrmap_bank_b1_Pos) /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b1 Mask*/

#define UMCTL2_ADDRMAP1_addrmap_bank_b2_Pos (16)                                           /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b2 Position*/
#define UMCTL2_ADDRMAP1_addrmap_bank_b2_Msk (0x3ful << UMCTL2_ADDRMAP1_addrmap_bank_b2_Pos) /*!< UMCTL2_T::ADDRMAP1: addrmap_bank_b2 Mask*/

#define UMCTL2_ADDRMAP2_addrmap_col_b2_Pos (0)                                             /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b2 Position*/
#define UMCTL2_ADDRMAP2_addrmap_col_b2_Msk (0xful << UMCTL2_ADDRMAP2_addrmap_col_b2_Pos)   /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b2 Mask*/

#define UMCTL2_ADDRMAP2_addrmap_col_b3_Pos (8)                                             /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b3 Position*/
#define UMCTL2_ADDRMAP2_addrmap_col_b3_Msk (0x1ful << UMCTL2_ADDRMAP2_addrmap_col_b3_Pos)  /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b3 Mask*/

#define UMCTL2_ADDRMAP2_addrmap_col_b4_Pos (16)                                            /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b4 Position*/
#define UMCTL2_ADDRMAP2_addrmap_col_b4_Msk (0xful << UMCTL2_ADDRMAP2_addrmap_col_b4_Pos)   /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b4 Mask*/

#define UMCTL2_ADDRMAP2_addrmap_col_b5_Pos (24)                                            /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b5 Position*/
#define UMCTL2_ADDRMAP2_addrmap_col_b5_Msk (0xful << UMCTL2_ADDRMAP2_addrmap_col_b5_Pos)   /*!< UMCTL2_T::ADDRMAP2: addrmap_col_b5 Mask*/

#define UMCTL2_ADDRMAP3_addrmap_col_b6_Pos (0)                                             /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b6 Position*/
#define UMCTL2_ADDRMAP3_addrmap_col_b6_Msk (0x1ful << UMCTL2_ADDRMAP3_addrmap_col_b6_Pos)  /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b6 Mask*/

#define UMCTL2_ADDRMAP3_addrmap_col_b7_Pos (8)                                             /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b7 Position*/
#define UMCTL2_ADDRMAP3_addrmap_col_b7_Msk (0x1ful << UMCTL2_ADDRMAP3_addrmap_col_b7_Pos)  /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b7 Mask*/

#define UMCTL2_ADDRMAP3_addrmap_col_b8_Pos (16)                                            /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b8 Position*/
#define UMCTL2_ADDRMAP3_addrmap_col_b8_Msk (0x1ful << UMCTL2_ADDRMAP3_addrmap_col_b8_Pos)  /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b8 Mask*/

#define UMCTL2_ADDRMAP3_addrmap_col_b9_Pos (24)                                            /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b9 Position*/
#define UMCTL2_ADDRMAP3_addrmap_col_b9_Msk (0x1ful << UMCTL2_ADDRMAP3_addrmap_col_b9_Pos)  /*!< UMCTL2_T::ADDRMAP3: addrmap_col_b9 Mask*/

#define UMCTL2_ADDRMAP4_addrmap_col_b10_Pos (0)                                            /*!< UMCTL2_T::ADDRMAP4: addrmap_col_b10 Position*/
#define UMCTL2_ADDRMAP4_addrmap_col_b10_Msk (0x1ful << UMCTL2_ADDRMAP4_addrmap_col_b10_Pos) /*!< UMCTL2_T::ADDRMAP4: addrmap_col_b10 Mask*/

#define UMCTL2_ADDRMAP4_addrmap_col_b11_Pos (8)                                            /*!< UMCTL2_T::ADDRMAP4: addrmap_col_b11 Position*/
#define UMCTL2_ADDRMAP4_addrmap_col_b11_Msk (0x1ful << UMCTL2_ADDRMAP4_addrmap_col_b11_Pos) /*!< UMCTL2_T::ADDRMAP4: addrmap_col_b11 Mask*/

#define UMCTL2_ADDRMAP5_addrmap_row_b0_Pos (0)                                             /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b0 Position*/
#define UMCTL2_ADDRMAP5_addrmap_row_b0_Msk (0xful << UMCTL2_ADDRMAP5_addrmap_row_b0_Pos)   /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b0 Mask*/

#define UMCTL2_ADDRMAP5_addrmap_row_b1_Pos (8)                                             /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b1 Position*/
#define UMCTL2_ADDRMAP5_addrmap_row_b1_Msk (0xful << UMCTL2_ADDRMAP5_addrmap_row_b1_Pos)   /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b1 Mask*/

#define UMCTL2_ADDRMAP5_addrmap_row_b2_10_Pos (16)                                         /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b2_10 Position*/
#define UMCTL2_ADDRMAP5_addrmap_row_b2_10_Msk (0xful << UMCTL2_ADDRMAP5_addrmap_row_b2_10_Pos) /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b2_10 Mask*/

#define UMCTL2_ADDRMAP5_addrmap_row_b11_Pos (24)                                           /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b11 Position*/
#define UMCTL2_ADDRMAP5_addrmap_row_b11_Msk (0xful << UMCTL2_ADDRMAP5_addrmap_row_b11_Pos) /*!< UMCTL2_T::ADDRMAP5: addrmap_row_b11 Mask*/

#define UMCTL2_ADDRMAP6_addrmap_row_b12_Pos (0)                                            /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b12 Position*/
#define UMCTL2_ADDRMAP6_addrmap_row_b12_Msk (0xful << UMCTL2_ADDRMAP6_addrmap_row_b12_Pos) /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b12 Mask*/

#define UMCTL2_ADDRMAP6_addrmap_row_b13_Pos (8)                                            /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b13 Position*/
#define UMCTL2_ADDRMAP6_addrmap_row_b13_Msk (0xful << UMCTL2_ADDRMAP6_addrmap_row_b13_Pos) /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b13 Mask*/

#define UMCTL2_ADDRMAP6_addrmap_row_b14_Pos (16)                                           /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b14 Position*/
#define UMCTL2_ADDRMAP6_addrmap_row_b14_Msk (0xful << UMCTL2_ADDRMAP6_addrmap_row_b14_Pos) /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b14 Mask*/

#define UMCTL2_ADDRMAP6_addrmap_row_b15_Pos (24)                                           /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b15 Position*/
#define UMCTL2_ADDRMAP6_addrmap_row_b15_Msk (0xful << UMCTL2_ADDRMAP6_addrmap_row_b15_Pos) /*!< UMCTL2_T::ADDRMAP6: addrmap_row_b15 Mask*/

#define UMCTL2_ADDRMAP9_addrmap_row_b2_Pos (0)                                             /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b2 Position*/
#define UMCTL2_ADDRMAP9_addrmap_row_b2_Msk (0xful << UMCTL2_ADDRMAP9_addrmap_row_b2_Pos)   /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b2 Mask*/

#define UMCTL2_ADDRMAP9_addrmap_row_b3_Pos (8)                                             /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b3 Position*/
#define UMCTL2_ADDRMAP9_addrmap_row_b3_Msk (0xful << UMCTL2_ADDRMAP9_addrmap_row_b3_Pos)   /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b3 Mask*/

#define UMCTL2_ADDRMAP9_addrmap_row_b4_Pos (16)                                            /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b4 Position*/
#define UMCTL2_ADDRMAP9_addrmap_row_b4_Msk (0xful << UMCTL2_ADDRMAP9_addrmap_row_b4_Pos)   /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b4 Mask*/

#define UMCTL2_ADDRMAP9_addrmap_row_b5_Pos (24)                                            /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b5 Position*/
#define UMCTL2_ADDRMAP9_addrmap_row_b5_Msk (0xful << UMCTL2_ADDRMAP9_addrmap_row_b5_Pos)   /*!< UMCTL2_T::ADDRMAP9: addrmap_row_b5 Mask*/

#define UMCTL2_ADDRMAP10_addrmap_row_b6_Pos (0)                                            /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b6 Position*/
#define UMCTL2_ADDRMAP10_addrmap_row_b6_Msk (0xful << UMCTL2_ADDRMAP10_addrmap_row_b6_Pos) /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b6 Mask*/

#define UMCTL2_ADDRMAP10_addrmap_row_b7_Pos (8)                                            /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b7 Position*/
#define UMCTL2_ADDRMAP10_addrmap_row_b7_Msk (0xful << UMCTL2_ADDRMAP10_addrmap_row_b7_Pos) /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b7 Mask*/

#define UMCTL2_ADDRMAP10_addrmap_row_b8_Pos (16)                                           /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b8 Position*/
#define UMCTL2_ADDRMAP10_addrmap_row_b8_Msk (0xful << UMCTL2_ADDRMAP10_addrmap_row_b8_Pos) /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b8 Mask*/

#define UMCTL2_ADDRMAP10_addrmap_row_b9_Pos (24)                                           /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b9 Position*/
#define UMCTL2_ADDRMAP10_addrmap_row_b9_Msk (0xful << UMCTL2_ADDRMAP10_addrmap_row_b9_Pos) /*!< UMCTL2_T::ADDRMAP10: addrmap_row_b9 Mask*/

#define UMCTL2_ADDRMAP11_addrmap_row_b10_Pos (0)                                           /*!< UMCTL2_T::ADDRMAP11: addrmap_row_b10 Position*/
#define UMCTL2_ADDRMAP11_addrmap_row_b10_Msk (0xful << UMCTL2_ADDRMAP11_addrmap_row_b10_Pos) /*!< UMCTL2_T::ADDRMAP11: addrmap_row_b10 Mask*/

#define UMCTL2_ODTCFG_rd_odt_delay_Pos   (2)                                               /*!< UMCTL2_T::ODTCFG: rd_odt_delay Position*/
#define UMCTL2_ODTCFG_rd_odt_delay_Msk   (0x1ful << UMCTL2_ODTCFG_rd_odt_delay_Pos)        /*!< UMCTL2_T::ODTCFG: rd_odt_delay Mask    */

#define UMCTL2_ODTCFG_rd_odt_hold_Pos    (8)                                               /*!< UMCTL2_T::ODTCFG: rd_odt_hold Position */
#define UMCTL2_ODTCFG_rd_odt_hold_Msk    (0xful << UMCTL2_ODTCFG_rd_odt_hold_Pos)          /*!< UMCTL2_T::ODTCFG: rd_odt_hold Mask     */

#define UMCTL2_ODTCFG_wr_odt_delay_Pos   (16)                                              /*!< UMCTL2_T::ODTCFG: wr_odt_delay Position*/
#define UMCTL2_ODTCFG_wr_odt_delay_Msk   (0x1ful << UMCTL2_ODTCFG_wr_odt_delay_Pos)        /*!< UMCTL2_T::ODTCFG: wr_odt_delay Mask    */

#define UMCTL2_ODTCFG_wr_odt_hold_Pos    (24)                                              /*!< UMCTL2_T::ODTCFG: wr_odt_hold Position */
#define UMCTL2_ODTCFG_wr_odt_hold_Msk    (0xful << UMCTL2_ODTCFG_wr_odt_hold_Pos)          /*!< UMCTL2_T::ODTCFG: wr_odt_hold Mask     */

#define UMCTL2_ODTMAP_rank0_wr_odt_Pos   (0)                                               /*!< UMCTL2_T::ODTMAP: rank0_wr_odt Position*/
#define UMCTL2_ODTMAP_rank0_wr_odt_Msk   (0x3ul << UMCTL2_ODTMAP_rank0_wr_odt_Pos)         /*!< UMCTL2_T::ODTMAP: rank0_wr_odt Mask    */

#define UMCTL2_ODTMAP_rank0_rd_odt_Pos   (4)                                               /*!< UMCTL2_T::ODTMAP: rank0_rd_odt Position*/
#define UMCTL2_ODTMAP_rank0_rd_odt_Msk   (0x3ul << UMCTL2_ODTMAP_rank0_rd_odt_Pos)         /*!< UMCTL2_T::ODTMAP: rank0_rd_odt Mask    */

#define UMCTL2_ODTMAP_rank1_wr_odt_Pos   (8)                                               /*!< UMCTL2_T::ODTMAP: rank1_wr_odt Position*/
#define UMCTL2_ODTMAP_rank1_wr_odt_Msk   (0x3ul << UMCTL2_ODTMAP_rank1_wr_odt_Pos)         /*!< UMCTL2_T::ODTMAP: rank1_wr_odt Mask    */

#define UMCTL2_ODTMAP_rank1_rd_odt_Pos   (12)                                              /*!< UMCTL2_T::ODTMAP: rank1_rd_odt Position*/
#define UMCTL2_ODTMAP_rank1_rd_odt_Msk   (0x3ul << UMCTL2_ODTMAP_rank1_rd_odt_Pos)         /*!< UMCTL2_T::ODTMAP: rank1_rd_odt Mask    */

#define UMCTL2_SCHED_prefer_write_Pos    (1)                                               /*!< UMCTL2_T::SCHED: prefer_write Position */
#define UMCTL2_SCHED_prefer_write_Msk    (0x1ul << UMCTL2_SCHED_prefer_write_Pos)          /*!< UMCTL2_T::SCHED: prefer_write Mask     */

#define UMCTL2_SCHED_Pageclose_Pos       (2)                                               /*!< UMCTL2_T::SCHED: Pageclose Position    */
#define UMCTL2_SCHED_Pageclose_Msk       (0x1ul << UMCTL2_SCHED_Pageclose_Pos)             /*!< UMCTL2_T::SCHED: Pageclose Mask        */

#define UMCTL2_SCHED_lpr_num_entries_Pos (8)                                               /*!< UMCTL2_T::SCHED: lpr_num_entries Position*/
#define UMCTL2_SCHED_lpr_num_entries_Msk (0x1ful << UMCTL2_SCHED_lpr_num_entries_Pos)      /*!< UMCTL2_T::SCHED: lpr_num_entries Mask  */

#define UMCTL2_SCHED_go2critical_hysteresis_Pos (16)                                       /*!< UMCTL2_T::SCHED: go2critical_hysteresis Position*/
#define UMCTL2_SCHED_go2critical_hysteresis_Msk (0xfful << UMCTL2_SCHED_go2critical_hysteresis_Pos) /*!< UMCTL2_T::SCHED: go2critical_hysteresis Mask*/

#define UMCTL2_SCHED_rdwr_idle_gap_Pos   (24)                                              /*!< UMCTL2_T::SCHED: rdwr_idle_gap Position*/
#define UMCTL2_SCHED_rdwr_idle_gap_Msk   (0x7ful << UMCTL2_SCHED_rdwr_idle_gap_Pos)        /*!< UMCTL2_T::SCHED: rdwr_idle_gap Mask    */

#define UMCTL2_SCHED1_pageclose_timer_Pos (0)                                              /*!< UMCTL2_T::SCHED1: pageclose_timer Position*/
#define UMCTL2_SCHED1_pageclose_timer_Msk (0xfful << UMCTL2_SCHED1_pageclose_timer_Pos)    /*!< UMCTL2_T::SCHED1: pageclose_timer Mask */

#define UMCTL2_PERFHPR1_hpr_max_starve_Pos (0)                                             /*!< UMCTL2_T::PERFHPR1: hpr_max_starve Position*/
#define UMCTL2_PERFHPR1_hpr_max_starve_Msk (0xfffful << UMCTL2_PERFHPR1_hpr_max_starve_Pos) /*!< UMCTL2_T::PERFHPR1: hpr_max_starve Mask*/

#define UMCTL2_PERFHPR1_hpr_xact_run_length_Pos (24)                                       /*!< UMCTL2_T::PERFHPR1: hpr_xact_run_length Position*/
#define UMCTL2_PERFHPR1_hpr_xact_run_length_Msk (0xfful << UMCTL2_PERFHPR1_hpr_xact_run_length_Pos) /*!< UMCTL2_T::PERFHPR1: hpr_xact_run_length Mask*/

#define UMCTL2_PERFLPR1_lpr_max_starve_Pos (0)                                             /*!< UMCTL2_T::PERFLPR1: lpr_max_starve Position*/
#define UMCTL2_PERFLPR1_lpr_max_starve_Msk (0xfffful << UMCTL2_PERFLPR1_lpr_max_starve_Pos) /*!< UMCTL2_T::PERFLPR1: lpr_max_starve Mask*/

#define UMCTL2_PERFLPR1_lpr_xact_run_length_Pos (24)                                       /*!< UMCTL2_T::PERFLPR1: lpr_xact_run_length Position*/
#define UMCTL2_PERFLPR1_lpr_xact_run_length_Msk (0xfful << UMCTL2_PERFLPR1_lpr_xact_run_length_Pos) /*!< UMCTL2_T::PERFLPR1: lpr_xact_run_length Mask*/

#define UMCTL2_PERFWR1_w_max_starve_Pos  (0)                                               /*!< UMCTL2_T::PERFWR1: w_max_starve Position*/
#define UMCTL2_PERFWR1_w_max_starve_Msk  (0xfffful << UMCTL2_PERFWR1_w_max_starve_Pos)     /*!< UMCTL2_T::PERFWR1: w_max_starve Mask   */

#define UMCTL2_PERFWR1_w_xact_run_length_Pos (24)                                          /*!< UMCTL2_T::PERFWR1: w_xact_run_length Position*/
#define UMCTL2_PERFWR1_w_xact_run_length_Msk (0xfful << UMCTL2_PERFWR1_w_xact_run_length_Pos) /*!< UMCTL2_T::PERFWR1: w_xact_run_length Mask*/

#define UMCTL2_DBG0_dis_wc_Pos           (0)                                               /*!< UMCTL2_T::DBG0: dis_wc Position        */
#define UMCTL2_DBG0_dis_wc_Msk           (0x1ul << UMCTL2_DBG0_dis_wc_Pos)                 /*!< UMCTL2_T::DBG0: dis_wc Mask            */

#define UMCTL2_DBG0_dis_rd_bypass_Pos    (1)                                               /*!< UMCTL2_T::DBG0: dis_rd_bypass Position */
#define UMCTL2_DBG0_dis_rd_bypass_Msk    (0x1ul << UMCTL2_DBG0_dis_rd_bypass_Pos)          /*!< UMCTL2_T::DBG0: dis_rd_bypass Mask     */

#define UMCTL2_DBG0_dis_act_bypass_Pos   (2)                                               /*!< UMCTL2_T::DBG0: dis_act_bypass Position*/
#define UMCTL2_DBG0_dis_act_bypass_Msk   (0x1ul << UMCTL2_DBG0_dis_act_bypass_Pos)         /*!< UMCTL2_T::DBG0: dis_act_bypass Mask    */

#define UMCTL2_DBG0_dis_collision_page_opt_Pos (4)                                         /*!< UMCTL2_T::DBG0: dis_collision_page_opt Position*/
#define UMCTL2_DBG0_dis_collision_page_opt_Msk (0x1ul << UMCTL2_DBG0_dis_collision_page_opt_Pos) /*!< UMCTL2_T::DBG0: dis_collision_page_opt Mask*/

#define UMCTL2_DBG0_dis_max_rank_rd_opt_Pos (6)                                            /*!< UMCTL2_T::DBG0: dis_max_rank_rd_opt Position*/
#define UMCTL2_DBG0_dis_max_rank_rd_opt_Msk (0x1ul << UMCTL2_DBG0_dis_max_rank_rd_opt_Pos) /*!< UMCTL2_T::DBG0: dis_max_rank_rd_opt Mask*/

#define UMCTL2_DBG0_dis_max_rank_wr_opt_Pos (7)                                            /*!< UMCTL2_T::DBG0: dis_max_rank_wr_opt Position*/
#define UMCTL2_DBG0_dis_max_rank_wr_opt_Msk (0x1ul << UMCTL2_DBG0_dis_max_rank_wr_opt_Pos) /*!< UMCTL2_T::DBG0: dis_max_rank_wr_opt Mask*/

#define UMCTL2_DBG1_dis_dq_Pos           (0)                                               /*!< UMCTL2_T::DBG1: dis_dq Position        */
#define UMCTL2_DBG1_dis_dq_Msk           (0x1ul << UMCTL2_DBG1_dis_dq_Pos)                 /*!< UMCTL2_T::DBG1: dis_dq Mask            */

#define UMCTL2_DBG1_dis_hif_Pos          (1)                                               /*!< UMCTL2_T::DBG1: dis_hif Position       */
#define UMCTL2_DBG1_dis_hif_Msk          (0x1ul << UMCTL2_DBG1_dis_hif_Pos)                /*!< UMCTL2_T::DBG1: dis_hif Mask           */

#define UMCTL2_DBGCAM_dbg_hpr_q_depth_Pos (0)                                              /*!< UMCTL2_T::DBGCAM: dbg_hpr_q_depth Position*/
#define UMCTL2_DBGCAM_dbg_hpr_q_depth_Msk (0x3ful << UMCTL2_DBGCAM_dbg_hpr_q_depth_Pos)    /*!< UMCTL2_T::DBGCAM: dbg_hpr_q_depth Mask */

#define UMCTL2_DBGCAM_dbg_lpr_q_depth_Pos (8)                                              /*!< UMCTL2_T::DBGCAM: dbg_lpr_q_depth Position*/
#define UMCTL2_DBGCAM_dbg_lpr_q_depth_Msk (0x3ful << UMCTL2_DBGCAM_dbg_lpr_q_depth_Pos)    /*!< UMCTL2_T::DBGCAM: dbg_lpr_q_depth Mask */

#define UMCTL2_DBGCAM_dbg_w_q_depth_Pos  (16)                                              /*!< UMCTL2_T::DBGCAM: dbg_w_q_depth Position*/
#define UMCTL2_DBGCAM_dbg_w_q_depth_Msk  (0x3ful << UMCTL2_DBGCAM_dbg_w_q_depth_Pos)       /*!< UMCTL2_T::DBGCAM: dbg_w_q_depth Mask   */

#define UMCTL2_DBGCAM_dbg_stall_Pos      (24)                                              /*!< UMCTL2_T::DBGCAM: dbg_stall Position   */
#define UMCTL2_DBGCAM_dbg_stall_Msk      (0x1ul << UMCTL2_DBGCAM_dbg_stall_Pos)            /*!< UMCTL2_T::DBGCAM: dbg_stall Mask       */

#define UMCTL2_DBGCAM_dbg_rd_q_empty_Pos (25)                                              /*!< UMCTL2_T::DBGCAM: dbg_rd_q_empty Position*/
#define UMCTL2_DBGCAM_dbg_rd_q_empty_Msk (0x1ul << UMCTL2_DBGCAM_dbg_rd_q_empty_Pos)       /*!< UMCTL2_T::DBGCAM: dbg_rd_q_empty Mask  */

#define UMCTL2_DBGCAM_dbg_wr_q_empty_Pos (26)                                              /*!< UMCTL2_T::DBGCAM: dbg_wr_q_empty Position*/
#define UMCTL2_DBGCAM_dbg_wr_q_empty_Msk (0x1ul << UMCTL2_DBGCAM_dbg_wr_q_empty_Pos)       /*!< UMCTL2_T::DBGCAM: dbg_wr_q_empty Mask  */

#define UMCTL2_DBGCAM_rd_data_pipeline_empty_Pos (28)                                      /*!< UMCTL2_T::DBGCAM: rd_data_pipeline_empty Position*/
#define UMCTL2_DBGCAM_rd_data_pipeline_empty_Msk (0x1ul << UMCTL2_DBGCAM_rd_data_pipeline_empty_Pos) /*!< UMCTL2_T::DBGCAM: rd_data_pipeline_empty Mask*/

#define UMCTL2_DBGCAM_wr_data_pipeline_empty_Pos (29)                                      /*!< UMCTL2_T::DBGCAM: wr_data_pipeline_empty Position*/
#define UMCTL2_DBGCAM_wr_data_pipeline_empty_Msk (0x1ul << UMCTL2_DBGCAM_wr_data_pipeline_empty_Pos) /*!< UMCTL2_T::DBGCAM: wr_data_pipeline_empty Mask*/

#define UMCTL2_DBGCMD_rank0_refresh_Pos  (0)                                               /*!< UMCTL2_T::DBGCMD: rank0_refresh Position*/
#define UMCTL2_DBGCMD_rank0_refresh_Msk  (0x1ul << UMCTL2_DBGCMD_rank0_refresh_Pos)        /*!< UMCTL2_T::DBGCMD: rank0_refresh Mask   */

#define UMCTL2_DBGCMD_rank1_refresh_Pos  (1)                                               /*!< UMCTL2_T::DBGCMD: rank1_refresh Position*/
#define UMCTL2_DBGCMD_rank1_refresh_Msk  (0x1ul << UMCTL2_DBGCMD_rank1_refresh_Pos)        /*!< UMCTL2_T::DBGCMD: rank1_refresh Mask   */

#define UMCTL2_DBGCMD_zq_calib_short_Pos (4)                                               /*!< UMCTL2_T::DBGCMD: zq_calib_short Position*/
#define UMCTL2_DBGCMD_zq_calib_short_Msk (0x1ul << UMCTL2_DBGCMD_zq_calib_short_Pos)       /*!< UMCTL2_T::DBGCMD: zq_calib_short Mask  */

#define UMCTL2_DBGCMD_ctrlupd_Pos        (5)                                               /*!< UMCTL2_T::DBGCMD: ctrlupd Position     */
#define UMCTL2_DBGCMD_ctrlupd_Msk        (0x1ul << UMCTL2_DBGCMD_ctrlupd_Pos)              /*!< UMCTL2_T::DBGCMD: ctrlupd Mask         */

#define UMCTL2_DBGSTAT_rank0_refresh_busy_Pos (0)                                          /*!< UMCTL2_T::DBGSTAT: rank0_refresh_busy Position*/
#define UMCTL2_DBGSTAT_rank0_refresh_busy_Msk (0x1ul << UMCTL2_DBGSTAT_rank0_refresh_busy_Pos) /*!< UMCTL2_T::DBGSTAT: rank0_refresh_busy Mask*/

#define UMCTL2_DBGSTAT_rank1_refresh_busy_Pos (1)                                          /*!< UMCTL2_T::DBGSTAT: rank1_refresh_busy Position*/
#define UMCTL2_DBGSTAT_rank1_refresh_busy_Msk (0x1ul << UMCTL2_DBGSTAT_rank1_refresh_busy_Pos) /*!< UMCTL2_T::DBGSTAT: rank1_refresh_busy Mask*/

#define UMCTL2_DBGSTAT_zq_calib_short_busy_Pos (4)                                         /*!< UMCTL2_T::DBGSTAT: zq_calib_short_busy Position*/
#define UMCTL2_DBGSTAT_zq_calib_short_busy_Msk (0x1ul << UMCTL2_DBGSTAT_zq_calib_short_busy_Pos) /*!< UMCTL2_T::DBGSTAT: zq_calib_short_busy Mask*/

#define UMCTL2_DBGSTAT_ctrlupd_busy_Pos  (5)                                               /*!< UMCTL2_T::DBGSTAT: ctrlupd_busy Position*/
#define UMCTL2_DBGSTAT_ctrlupd_busy_Msk  (0x1ul << UMCTL2_DBGSTAT_ctrlupd_busy_Pos)        /*!< UMCTL2_T::DBGSTAT: ctrlupd_busy Mask   */

#define UMCTL2_SWCTL_sw_done_Pos         (0)                                               /*!< UMCTL2_T::SWCTL: sw_done Position      */
#define UMCTL2_SWCTL_sw_done_Msk         (0x1ul << UMCTL2_SWCTL_sw_done_Pos)               /*!< UMCTL2_T::SWCTL: sw_done Mask          */

#define UMCTL2_SWSTAT_sw_done_ack_Pos    (0)                                               /*!< UMCTL2_T::SWSTAT: sw_done_ack Position */
#define UMCTL2_SWSTAT_sw_done_ack_Msk    (0x1ul << UMCTL2_SWSTAT_sw_done_ack_Pos)          /*!< UMCTL2_T::SWSTAT: sw_done_ack Mask     */

#define UMCTL2_SWCTLSTATIC_sw_static_unlock_Pos (0)                                        /*!< UMCTL2_T::SWCTLSTATIC: sw_static_unlock Position*/
#define UMCTL2_SWCTLSTATIC_sw_static_unlock_Msk (0x1ul << UMCTL2_SWCTLSTATIC_sw_static_unlock_Pos) /*!< UMCTL2_T::SWCTLSTATIC: sw_static_unlock Mask*/

#define UMCTL2_POISONCFG_wr_poison_slverr_en_Pos (0)                                       /*!< UMCTL2_T::POISONCFG: wr_poison_slverr_en Position*/
#define UMCTL2_POISONCFG_wr_poison_slverr_en_Msk (0x1ul << UMCTL2_POISONCFG_wr_poison_slverr_en_Pos) /*!< UMCTL2_T::POISONCFG: wr_poison_slverr_en Mask*/

#define UMCTL2_POISONCFG_wr_poison_intr_en_Pos (4)                                         /*!< UMCTL2_T::POISONCFG: wr_poison_intr_en Position*/
#define UMCTL2_POISONCFG_wr_poison_intr_en_Msk (0x1ul << UMCTL2_POISONCFG_wr_poison_intr_en_Pos) /*!< UMCTL2_T::POISONCFG: wr_poison_intr_en Mask*/

#define UMCTL2_POISONCFG_wr_poison_intr_clr_Pos (8)                                        /*!< UMCTL2_T::POISONCFG: wr_poison_intr_clr Position*/
#define UMCTL2_POISONCFG_wr_poison_intr_clr_Msk (0x1ul << UMCTL2_POISONCFG_wr_poison_intr_clr_Pos) /*!< UMCTL2_T::POISONCFG: wr_poison_intr_clr Mask*/

#define UMCTL2_POISONCFG_rd_poison_slverr_en_Pos (16)                                      /*!< UMCTL2_T::POISONCFG: rd_poison_slverr_en Position*/
#define UMCTL2_POISONCFG_rd_poison_slverr_en_Msk (0x1ul << UMCTL2_POISONCFG_rd_poison_slverr_en_Pos) /*!< UMCTL2_T::POISONCFG: rd_poison_slverr_en Mask*/

#define UMCTL2_POISONCFG_rd_poison_intr_en_Pos (20)                                        /*!< UMCTL2_T::POISONCFG: rd_poison_intr_en Position*/
#define UMCTL2_POISONCFG_rd_poison_intr_en_Msk (0x1ul << UMCTL2_POISONCFG_rd_poison_intr_en_Pos) /*!< UMCTL2_T::POISONCFG: rd_poison_intr_en Mask*/

#define UMCTL2_POISONCFG_rd_poison_intr_clr_Pos (24)                                       /*!< UMCTL2_T::POISONCFG: rd_poison_intr_clr Position*/
#define UMCTL2_POISONCFG_rd_poison_intr_clr_Msk (0x1ul << UMCTL2_POISONCFG_rd_poison_intr_clr_Pos) /*!< UMCTL2_T::POISONCFG: rd_poison_intr_clr Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_0_Pos (0)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_0 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_0_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_0_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_0 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_1_Pos (1)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_1 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_1_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_1_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_1 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_2_Pos (2)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_2 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_2_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_2_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_2 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_3_Pos (3)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_3 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_3_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_3_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_3 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_4_Pos (4)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_4 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_4_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_4_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_4 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_5_Pos (5)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_5 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_5_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_5_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_5 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_6_Pos (6)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_6 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_6_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_6_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_6 Mask*/

#define UMCTL2_POISONSTAT_wr_poison_intr_7_Pos (7)                                         /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_7 Position*/
#define UMCTL2_POISONSTAT_wr_poison_intr_7_Msk (0x1ul << UMCTL2_POISONSTAT_wr_poison_intr_7_Pos) /*!< UMCTL2_T::POISONSTAT: wr_poison_intr_7 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_0_Pos (16)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_0 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_0_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_0_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_0 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_1_Pos (17)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_1 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_1_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_1_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_1 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_2_Pos (18)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_2 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_2_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_2_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_2 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_3_Pos (19)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_3 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_3_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_3_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_3 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_4_Pos (20)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_4 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_4_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_4_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_4 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_5_Pos (21)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_5 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_5_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_5_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_5 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_6_Pos (22)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_6 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_6_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_6_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_6 Mask*/

#define UMCTL2_POISONSTAT_rd_poison_intr_7_Pos (23)                                        /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_7 Position*/
#define UMCTL2_POISONSTAT_rd_poison_intr_7_Msk (0x1ul << UMCTL2_POISONSTAT_rd_poison_intr_7_Pos) /*!< UMCTL2_T::POISONSTAT: rd_poison_intr_7 Mask*/

#define UMCTL2_PSTAT_rd_port_busy_0_Pos  (0)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_0 Position*/
#define UMCTL2_PSTAT_rd_port_busy_0_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_0_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_0 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_1_Pos  (1)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_1 Position*/
#define UMCTL2_PSTAT_rd_port_busy_1_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_1_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_1 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_2_Pos  (2)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_2 Position*/
#define UMCTL2_PSTAT_rd_port_busy_2_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_2_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_2 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_3_Pos  (3)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_3 Position*/
#define UMCTL2_PSTAT_rd_port_busy_3_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_3_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_3 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_4_Pos  (4)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_4 Position*/
#define UMCTL2_PSTAT_rd_port_busy_4_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_4_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_4 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_5_Pos  (5)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_5 Position*/
#define UMCTL2_PSTAT_rd_port_busy_5_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_5_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_5 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_6_Pos  (6)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_6 Position*/
#define UMCTL2_PSTAT_rd_port_busy_6_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_6_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_6 Mask   */

#define UMCTL2_PSTAT_rd_port_busy_7_Pos  (7)                                               /*!< UMCTL2_T::PSTAT: rd_port_busy_7 Position*/
#define UMCTL2_PSTAT_rd_port_busy_7_Msk  (0x1ul << UMCTL2_PSTAT_rd_port_busy_7_Pos)        /*!< UMCTL2_T::PSTAT: rd_port_busy_7 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_0_Pos  (16)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_0 Position*/
#define UMCTL2_PSTAT_wr_port_busy_0_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_0_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_0 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_1_Pos  (17)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_1 Position*/
#define UMCTL2_PSTAT_wr_port_busy_1_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_1_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_1 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_2_Pos  (18)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_2 Position*/
#define UMCTL2_PSTAT_wr_port_busy_2_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_2_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_2 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_3_Pos  (19)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_3 Position*/
#define UMCTL2_PSTAT_wr_port_busy_3_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_3_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_3 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_4_Pos  (20)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_4 Position*/
#define UMCTL2_PSTAT_wr_port_busy_4_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_4_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_4 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_5_Pos  (21)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_5 Position*/
#define UMCTL2_PSTAT_wr_port_busy_5_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_5_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_5 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_6_Pos  (22)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_6 Position*/
#define UMCTL2_PSTAT_wr_port_busy_6_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_6_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_6 Mask   */

#define UMCTL2_PSTAT_wr_port_busy_7_Pos  (23)                                              /*!< UMCTL2_T::PSTAT: wr_port_busy_7 Position*/
#define UMCTL2_PSTAT_wr_port_busy_7_Msk  (0x1ul << UMCTL2_PSTAT_wr_port_busy_7_Pos)        /*!< UMCTL2_T::PSTAT: wr_port_busy_7 Mask   */

#define UMCTL2_PCCFG_go2critical_en_Pos  (0)                                               /*!< UMCTL2_T::PCCFG: go2critical_en Position*/
#define UMCTL2_PCCFG_go2critical_en_Msk  (0x1ul << UMCTL2_PCCFG_go2critical_en_Pos)        /*!< UMCTL2_T::PCCFG: go2critical_en Mask   */

#define UMCTL2_PCCFG_pagematch_limit_Pos (4)                                               /*!< UMCTL2_T::PCCFG: pagematch_limit Position*/
#define UMCTL2_PCCFG_pagematch_limit_Msk (0x1ul << UMCTL2_PCCFG_pagematch_limit_Pos)       /*!< UMCTL2_T::PCCFG: pagematch_limit Mask  */

#define UMCTL2_PCCFG_bl_exp_mode_Pos     (8)                                               /*!< UMCTL2_T::PCCFG: bl_exp_mode Position  */
#define UMCTL2_PCCFG_bl_exp_mode_Msk     (0x1ul << UMCTL2_PCCFG_bl_exp_mode_Pos)           /*!< UMCTL2_T::PCCFG: bl_exp_mode Mask      */

#define UMCTL2_PCFGR_0_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_0: rd_port_priority Position */
#define UMCTL2_PCFGR_0_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_0_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_0: rd_port_priority Mask     */

#define UMCTL2_PCFGR_0_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_0: rd_port_aging_en Position */
#define UMCTL2_PCFGR_0_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_0_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_0: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_0_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_0: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_0_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_0_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_0: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_0_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_0: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_0_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_0_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_0: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_0_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_0: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_00_rdwr_ordered_en_Msk     (0x1ul << UMCTL2_PCFGR_0_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_0: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_0_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_0: wr_port_priority Position */
#define UMCTL2_PCFGW_0_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_0_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_0: wr_port_priority Mask     */

#define UMCTL2_PCFGW_0_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_0: wr_port_aging_en Position */
#define UMCTL2_PCFGW_0_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_0_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_0: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_0_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_0: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_0_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_0_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_0: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_0_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_0: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_0_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_0_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_0: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_0_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_0: port_en Position          */
#define UMCTL2_PCTRL_0_port_en_Msk              (0x1ul << UMCTL2_PCTRL_0_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_0: port_en Mask              */

#define UMCTL2_PCFGQOS0_0_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_0: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_0_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_0_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_0: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_0_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_0: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_0_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_0_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_0: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_0_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::0: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_0_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_0_rqos_map_region1_Pos)       /*!< UMCTL2_T::0: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_1_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_1: rd_port_priority Position */
#define UMCTL2_PCFGR_1_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_1_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_1: rd_port_priority Mask     */

#define UMCTL2_PCFGR_1_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_1: rd_port_aging_en Position */
#define UMCTL2_PCFGR_1_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_1_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_1: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_1_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_1: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_1_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_1_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_1: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_1_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_1: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_1_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_1_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_1: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_1_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_1: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_1_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_1_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_1: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_1_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_1: wr_port_priority Position */
#define UMCTL2_PCFGW_1_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_1_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_1: wr_port_priority Mask     */

#define UMCTL2_PCFGW_1_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_1: wr_port_aging_en Position */
#define UMCTL2_PCFGW_1_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_1_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_1: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_1_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_1: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_1_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_1_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_1: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_1_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_1: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_1_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_1_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_1: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_1_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_1: port_en Position          */
#define UMCTL2_PCTRL_1_port_en_Msk              (0x1ul << UMCTL2_PCTRL_1_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_1: port_en Mask              */

#define UMCTL2_PCFGQOS0_1_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_1_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_1_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_1_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_1_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_1_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_1_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_1_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_1_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_1: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_2_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_2: rd_port_priority Position */
#define UMCTL2_PCFGR_2_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_2_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_2: rd_port_priority Mask     */

#define UMCTL2_PCFGR_2_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_2: rd_port_aging_en Position */
#define UMCTL2_PCFGR_2_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_2_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_2: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_2_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_2: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_2_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_2_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_2: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_2_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_2: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_2_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_2_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_2: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_2_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::2: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_2_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_2_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::2: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_2_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_2: wr_port_priority Position */
#define UMCTL2_PCFGW_2_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_2_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_2: wr_port_priority Mask     */

#define UMCTL2_PCFGW_2_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_2: wr_port_aging_en Position */
#define UMCTL2_PCFGW_2_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_2_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_2: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_2_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_2: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_2_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_2_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_2: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_2_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_2: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_2_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_2_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_2: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_2_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_2: port_en Position          */
#define UMCTL2_PCTRL_2_port_en_Msk              (0x1ul << UMCTL2_PCTRL_2_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_2: port_en Mask              */

#define UMCTL2_PCFGQOS0_2_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_2_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_2_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_2_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_2_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_2_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_2_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_2_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_2_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_2: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_3_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_3: rd_port_priority Position */
#define UMCTL2_PCFGR_3_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_3_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_3: rd_port_priority Mask     */

#define UMCTL2_PCFGR_3_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_3: rd_port_aging_en Position */
#define UMCTL2_PCFGR_3_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_3_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_3: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_3_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_3: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_3_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_3_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_3: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_3_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_3: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_3_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_3_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_3: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_3_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_3: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_3_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_3_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_3: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_3_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_3: wr_port_priority Position */
#define UMCTL2_PCFGW_3_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_3_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_3: wr_port_priority Mask     */

#define UMCTL2_PCFGW_3_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_3: wr_port_aging_en Position */
#define UMCTL2_PCFGW_3_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_3_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_3: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_3_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_3: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_3_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_3_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_3: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_3_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::3: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_3_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_3_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::3: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_3_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_3: port_en Position          */
#define UMCTL2_PCTRL_3_port_en_Msk              (0x1ul << UMCTL2_PCTRL_3_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_3: port_en Mask              */

#define UMCTL2_PCFGQOS0_3_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_3_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_3_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_3_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_3_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_3_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_3_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_3_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_3_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_3: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_4_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_4: rd_port_priority Position */
#define UMCTL2_PCFGR_4_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_4_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_4: rd_port_priority Mask     */

#define UMCTL2_PCFGR_4_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_4: rd_port_aging_en Position */
#define UMCTL2_PCFGR_4_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_4_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_4: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_4_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_4: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_4_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_4_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_4: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_4_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_4: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_4_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_4_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_4: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_4_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_4: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_4_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_4_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_4: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_4_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_4: wr_port_priority Position */
#define UMCTL2_PCFGW_4_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_4_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_4: wr_port_priority Mask     */

#define UMCTL2_PCFGW_4_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_4: wr_port_aging_en Position */
#define UMCTL2_PCFGW_4_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_4_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_4: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_4_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_4: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_4_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_4_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_4: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_4_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_4: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_4_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_4_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_4: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_4_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_4: port_en Position          */
#define UMCTL2_PCTRL_4_port_en_Msk              (0x1ul << UMCTL2_PCTRL_4_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_4: port_en Mask              */

#define UMCTL2_PCFGQOS0_4_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_4_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_4_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_4_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_4_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_4_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_4_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_4_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_4_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_4: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_5_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_5: rd_port_priority Position */
#define UMCTL2_PCFGR_5_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_5_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_5: rd_port_priority Mask     */

#define UMCTL2_PCFGR_5_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_5: rd_port_aging_en Position */
#define UMCTL2_PCFGR_5_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_5_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_5: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_5_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_5: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_5_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_5_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_5: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_5_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_5: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_5_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_5_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_5: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_5_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::5: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_5_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_5_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::5: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_5_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_5: wr_port_priority Position */
#define UMCTL2_PCFGW_5_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_5_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_5: wr_port_priority Mask     */

#define UMCTL2_PCFGW_5_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_5: wr_port_aging_en Position */
#define UMCTL2_PCFGW_5_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_5_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_5: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_5_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_5: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_5_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_5_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_5: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_5_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_5: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_5_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_5_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_5: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_5_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_5: port_en Position          */
#define UMCTL2_PCTRL_5_port_en_Msk              (0x1ul << UMCTL2_PCTRL_5_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_5: port_en Mask              */

#define UMCTL2_PCFGQOS0_5_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_5_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_5_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_5_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_5_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_5_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_5_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_5_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_5_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_5: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_6_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_6: rd_port_priority Position */
#define UMCTL2_PCFGR_6_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_6_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_6: rd_port_priority Mask     */

#define UMCTL2_PCFGR_6_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_6: rd_port_aging_en Position */
#define UMCTL2_PCFGR_6_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_6_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_6: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_6_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_6: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_6_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_6_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_6: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_6_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_6: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_6_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_6_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_6: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_6_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_6: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_6_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_6_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_6: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_6_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_6: wr_port_priority Position */
#define UMCTL2_PCFGW_6_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_6_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_6: wr_port_priority Mask     */

#define UMCTL2_PCFGW_6_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_6: wr_port_aging_en Position */
#define UMCTL2_PCFGW_6_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_6_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_6: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_6_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_6: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_6_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_6_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_6: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_6_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_6: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_6_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_6_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_6: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_6_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_6: port_en Position          */
#define UMCTL2_PCTRL_6_port_en_Msk              (0x1ul << UMCTL2_PCTRL_6_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_6: port_en Mask              */

#define UMCTL2_PCFGQOS0_6_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_6_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_6_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_6_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_6_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_6_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_6_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_6_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_6_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_6: rqos_map_region1 Mask     */

#define UMCTL2_PCFGR_7_rd_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGR_7: rd_port_priority Position */
#define UMCTL2_PCFGR_7_rd_port_priority_Msk     (0x3fful << UMCTL2_PCFGR_7_rd_port_priority_Pos)        /*!< UMCTL2_T::PCFGR_7: rd_port_priority Mask     */

#define UMCTL2_PCFGR_7_rd_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGR_7: rd_port_aging_en Position */
#define UMCTL2_PCFGR_7_rd_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGR_7_rd_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGR_7: rd_port_aging_en Mask     */

#define UMCTL2_PCFGR_7_rd_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGR_7: rd_port_urgent_en Position*/
#define UMCTL2_PCFGR_7_rd_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGR_7_rd_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGR_7: rd_port_urgent_en Mask    */

#define UMCTL2_PCFGR_7_rd_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGR_7: rd_port_pagematch_en Position*/
#define UMCTL2_PCFGR_7_rd_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGR_7_rd_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGR_7: rd_port_pagematch_en Mask */

#define UMCTL2_PCFGR_7_rdwr_ordered_en_Pos      (16)                                                    /*!< UMCTL2_T::PCFGR_7: rdwr_ordered_en Position  */
#define UMCTL2_PCFGR_7_rdwr_ordered_en_Msk      (0x1ul << UMCTL2_PCFGR_7_rdwr_ordered_en_Pos)           /*!< UMCTL2_T::PCFGR_7: rdwr_ordered_en Mask      */

#define UMCTL2_PCFGW_7_wr_port_priority_Pos     (0)                                                     /*!< UMCTL2_T::PCFGW_7: wr_port_priority Position */
#define UMCTL2_PCFGW_7_wr_port_priority_Msk     (0x3fful << UMCTL2_PCFGW_7_wr_port_priority_Pos)        /*!< UMCTL2_T::PCFGW_7: wr_port_priority Mask     */

#define UMCTL2_PCFGW_7_wr_port_aging_en_Pos     (12)                                                    /*!< UMCTL2_T::PCFGW_7: wr_port_aging_en Position */
#define UMCTL2_PCFGW_7_wr_port_aging_en_Msk     (0x1ul << UMCTL2_PCFGW_7_wr_port_aging_en_Pos)          /*!< UMCTL2_T::PCFGW_7: wr_port_aging_en Mask     */

#define UMCTL2_PCFGW_7_wr_port_urgent_en_Pos    (13)                                                    /*!< UMCTL2_T::PCFGW_7: wr_port_urgent_en Position*/
#define UMCTL2_PCFGW_7_wr_port_urgent_en_Msk    (0x1ul << UMCTL2_PCFGW_7_wr_port_urgent_en_Pos)         /*!< UMCTL2_T::PCFGW_7: wr_port_urgent_en Mask    */

#define UMCTL2_PCFGW_7_wr_port_pagematch_en_Pos (14)                                                    /*!< UMCTL2_T::PCFGW_7: wr_port_pagematch_en Position*/
#define UMCTL2_PCFGW_7_wr_port_pagematch_en_Msk (0x1ul << UMCTL2_PCFGW_7_wr_port_pagematch_en_Pos)      /*!< UMCTL2_T::PCFGW_7: wr_port_pagematch_en Mask */

#define UMCTL2_PCTRL_7_port_en_Pos              (0)                                                     /*!< UMCTL2_T::PCTRL_7: port_en Position          */
#define UMCTL2_PCTRL_7_port_en_Msk              (0x1ul << UMCTL2_PCTRL_7_port_en_Pos)                   /*!< UMCTL2_T::PCTRL_7: port_en Mask              */

#define UMCTL2_PCFGQOS0_7_rqos_map_level1_Pos   (0)                                                     /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_level1 Position  */
#define UMCTL2_PCFGQOS0_7_rqos_map_level1_Msk   (0xful << UMCTL2_PCFGQOS0_7_rqos_map_level1_Pos)        /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_level1 Mask      */

#define UMCTL2_PCFGQOS0_7_rqos_map_region0_Pos  (16)                                                    /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_region0 Position */
#define UMCTL2_PCFGQOS0_7_rqos_map_region0_Msk  (0x3ul << UMCTL2_PCFGQOS0_7_rqos_map_region0_Pos)       /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_region0 Mask     */

#define UMCTL2_PCFGQOS0_7_rqos_map_region1_Pos  (20)                                                    /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_region1 Position */
#define UMCTL2_PCFGQOS0_7_rqos_map_region1_Msk  (0x3ul << UMCTL2_PCFGQOS0_7_rqos_map_region1_Pos)       /*!< UMCTL2_T::PCFGQOS0_7: rqos_map_region1 Mask     */

#define UMCTL2_SARBASE0_base_addr_Pos    (0)                                               /*!< UMCTL2_T::SARBASE0: base_addr Position */
#define UMCTL2_SARBASE0_base_addr_Msk    (0x3ul << UMCTL2_SARBASE0_base_addr_Pos)          /*!< UMCTL2_T::SARBASE0: base_addr Mask     */

#define UMCTL2_SARSIZE0_nblocks_Pos      (0)                                               /*!< UMCTL2_T::SARSIZE0: nblocks Position   */
#define UMCTL2_SARSIZE0_nblocks_Msk      (0xfful << UMCTL2_SARSIZE0_nblocks_Pos)           /*!< UMCTL2_T::SARSIZE0: nblocks Mask       */

#define UMCTL2_VER_NUMBER_ver_number_Pos (0)                                               /*!< UMCTL2_T::VER_NUMBER: ver_number Position*/
#define UMCTL2_VER_NUMBER_ver_number_Msk (0xfffffffful << UMCTL2_VER_NUMBER_ver_number_Pos) /*!< UMCTL2_T::VER_NUMBER: ver_number Mask  */

#define UMCTL2_VER_TYPE_ver_type_Pos     (0)                                               /*!< UMCTL2_T::VER_TYPE: ver_type Position  */
#define UMCTL2_VER_TYPE_ver_type_Msk     (0xfffffffful << UMCTL2_VER_TYPE_ver_type_Pos)    /*!< UMCTL2_T::VER_TYPE: ver_type Mask      */

/**@}*/ /* UMCTL2_CONST */
/**@}*/ /* end of UMCTL2 register group */


/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __UMCTL2_REG_H__ */


