/**************************************************************************//**
 * @file     sdh_reg.h
 * @brief    SDH register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SDH_REG_H__
#define __SDH_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- System Security Peripheral Configuration Controller -------------------------*/
/**
    @addtogroup SDH System Security Peripheral Configuration Controller(SDH)
    Memory Mapped Structure for SDH Controller
@{ */

typedef struct
{
    __IO uint32_t SDMASA;                 /*!< [0x0000] SDMA System Address Register */

    union
    {
        __IO uint16_t BLOCKSIZE;          /*!< [0x0004] BLOCK Size Register          */
        struct
        {
            //  0x1: 1 byte
            //  0x2: 2 bytes
            //  0x3: 3 bytes
            //  ......
            //  0x1FF: 511 byte
            //  0x200: 512 bytes
            //  ......
            //  0x800: 2048 bytes
            __IO uint16_t  XFER_BLOCK_SIZE: 12;

            //  0x0 (BYTES_4K): 4 Kbytes SDMA Buffer Boundary
            //  0x1 (BYTES_8K): 8 Kbytes SDMA Buffer Boundary
            //  0x2 (BYTES_16K): 16 Kbytes SDMA Buffer Boundary
            //  0x3 (BYTES_32K): 32 Kbytes SDMA Buffer Boundary
            //  0x4 (BYTES_64K): 64 Kbytes SDMA Buffer Boundary
            //  0x5 (BYTES_128K): 128 Kbytes SDMA Buffer Boundary
            //  0x6 (BYTES_256K): 256 Kbytes SDMA Buffer Boundary
            //  0x7 (BYTES_512K): 512 Kbytes SDMA Buffer Boundary
            __IO uint16_t  SDMA_BUF_BDARY: 3;
            __IO uint16_t  : 1;
        } S_BLOCKSIZE;
    };


    union
    {
        __IO uint16_t BLOCKCOUNT;         /*!< [0x0006] BLOCK Count Register         */
        struct
        {
            // Following are the values for BLOCK_CNT:
            //  0x0: Stop Count
            //  0x1: 1 Block
            //  0x2: 2 Blocks
            //  ... - ...
            //  0xFFFF: 65535 Blocks
            __IO uint16_t  BLOCK_CNT: 16;

        } S_BLOCKCOUNT;
    };


    // These bits specify the SD/eMMC command argument that is specified in bits 39-8 of the Command format.
    __IO uint32_t ARGUMENT;                /*!< [0x0008] Argument Register            */

    union
    {
        __IO uint16_t XFER_MODE;          /*!< [0x000C] Transfer Mode Register       */
        struct
        {
            // 0x1 (ENABLED): DMA Data transfer
            // 0x0 (DISABLED): No data transfer or Non-DMA data transfer
            __IO uint16_t  DMA_ENABLE: 1;

            // 0x1 (ENABLED): Enable
            // 0x0 (DISABLED): Disable
            __IO uint16_t  BLOCK_COUNT_ENABLE: 1;

            // This field determines use of Auto Command functions.
            // Note: In SDIO, this field must be set as 00b (Auto Command Disabled).
            // 0x0 (AUTO_CMD_DISABLED): Auto Command Disabled
            // 0x1 (AUTO_CMD12_ENABLED): Auto CMD12 Enable
            // 0x2 (AUTO_CMD23_ENABLED): Auto CMD23 Enable
            // 0x3 (AUTO_CMD_AUTO_SEL): Auto CMD Auto Select
            __IO uint16_t  AUTO_CMD_ENABLE: 2;

            //  0x1 (READ): Read (Card to Host)
            //  0x0 (WRITE): Write (Host to Card)
            __IO uint16_t  DATA_XFER_DIR: 1;

            //  0x0 (SINGLE): Single Block
            //  0x1 (MULTI): Multiple Block
            __IO uint16_t  MULTI_BLK_SEL: 1;

            //  0x0 (RESP_R1): R1 (Memory)
            //  0x1 (RESP_R5): R5 (SDIO)
            __IO uint16_t  RESP_TYPE: 1;

            //  0x0 (DISABLED): Response Error Check is disabled
            //  0x1 (ENABLED): Response Error Check is enabled
            __IO uint16_t  RESP_ERR_CHK_ENABLE: 1;

            //  0x0 (ENABLED): Response Interrupt is enabled
            //  0x1 (DISABLED): Response Interrupt is disabled
            __IO uint16_t  RESP_INT_DISABLE: 1;

            __IO uint16_t  : 7;
        } S_XFER_MODE;
    };


    union
    {
        __IO uint16_t CMD;          /*!< [0x000E] Command Register              */
        struct
        {
            // 0x0 (NO_RESP): No Response
            // 0x1 (RESP_LEN_136): Response Length 136
            // 0x2 (RESP_LEN_48): Response Length 48
            // 0x3 (RESP_LEN_48B): Response Length 48; Check Busy after response
            __IO uint16_t  RESP_TYPE_SELECT: 2;

            // 0x0 (MAIN): Main Command
            // 0x1 (SUB): Sub Command
            __IO uint16_t  SUB_CMD_FLAG: 1;

            // 0x0 (DISABLED): Disable
            // 0x1 (ENABLED): Enable
            __IO uint16_t  CMD_CRC_CHK_ENABLE: 1;

            // 0x0 (DISABLED): Disable
            // 0x1 (ENABLED): Enable
            __IO uint16_t  CMD_IDX_CHK_ENABLE: 1;

            // 0x0 (NO_DATA): No Data Present
            // 0x1 (DATA): Data Present
            __IO uint16_t  CMD_PRESENT_SEL: 1;

            // 0x3 (ABORT_CMD): Abort
            // 0x2 (RESUME_CMD): Resume
            // 0x1 (SUSPEND_CMD): Suspend
            // 0x0 (NORMAL_CMD): Normal
            __IO uint16_t  CMD_TYPE: 2;

            //These bits are set to the command number that is specified in bits 45-40 of the Command Format.
            __IO uint16_t  CMD_INDEX: 6;

            __IO uint16_t  : 2;
        } S_CMD;
    };


    // Command Response
    // These bits reflect 39-8 bits of SD/eMMC Response Field.
    // Note: For Auto CMD, the 32-bit response (bits 39-8 of the Response Field) is updated in the RESP67_R register.
    union
    {
        __I  uint32_t RESP01;                /*!< [0x0010] Response 0/1 Register       */
        struct
        {
            __I  uint32_t B0: 8;
            __I  uint32_t B1: 8;
            __I  uint32_t B2: 8;
            __I  uint32_t B3: 8;
        } S_RESP01;
    };

    // Command Response
    // These bits reflect 71-40 bits of the SD/eMMC Response Field.
    union
    {
        __I  uint32_t RESP23;                /*!< [0x0014] Response 0/1 Register       */
        struct
        {
            __I  uint32_t B0: 8;
            __I  uint32_t B1: 8;
            __I  uint32_t B2: 8;
            __I  uint32_t B3: 8;
        } S_RESP23;
    };

    // Command Response
    // These bits reflect 103-72 bits of the Response Field.
    union
    {
        __I  uint32_t RESP45;                /*!< [0x0018] Response 0/1 Register       */
        struct
        {
            __I  uint32_t B0: 8;
            __I  uint32_t B1: 8;
            __I  uint32_t B2: 8;
            __I  uint32_t B3: 8;
        } S_RESP45;
    };

    // Command Response
    // These bits reflect bits 135-104 of SD/EMMC Response Field.
    // Note: For Auto CMD, this register also reflects the 32-bit response (bits 39-8 of the Response Field).
    union
    {
        __I  uint32_t RESP67;                /*!< [0x001C] Response 0/1 Register       */
        struct
        {
            __I  uint32_t B0: 8;
            __I  uint32_t B1: 8;
            __I  uint32_t B2: 8;
            __I  uint32_t B3: 8;
        } S_RESP67;
    };

    // Buffer Data
    // These bits enable access to the Host Controller packet buffer.
    __IO uint32_t BUF_DATA;              /*!< [0x0020] Response 0/1 Register       */

    union
    {
        __I  uint32_t PSTATE;            /*!< [0x0024] Command Register            */
        struct
        {
            // Command Inhibit
            // 0x0 (READY): Host Controller is ready to issue a command
            // 0x1 (NOT_READY): Host Controller is not ready to issue a command
            __I uint32_t  CMD_INHIBIT: 1;

            // Command Inhibit DAT
            // 0x0 (READY): Can issue command which used DAT line
            // 0x1 (NOT_READY): Cannot issue command which used DAT line
            __I uint32_t  CMD_INHIBIT_DAT: 1;

            // DAT Line Active
            // 0x0 (INACTIVE): DAT Line Inactive
            // 0x1 (ACTIVE): DAT Line Active
            __I uint32_t  DAT_LINE_ACTIVE: 1;

            // Re-Tuning Request
            // DWC_mshc does not generate retuning request. The software must maintain the Retuning timer.
            __I uint32_t  RE_TUNE_REQ: 1;

            // DAT[7:4] Line Signal Level
            // This bit is used to check the DAT line level to recover from errors and for debugging. These bits reflect the value of the sd_dat_in (upper nibble) signal.
            __I uint32_t  DAT_7_4: 4;

            // Write Transfer Active
            // This status indicates whether a write transfer is active for SD/eMMC mode.
            __I uint32_t  WR_XFER_ACTIVE: 1;

            // Read Transfer Active
            // 0x0 (INACTIVE): No valid data
            // 0x1 (ACTIVE): Transferring data
            // This bit indicates whether a read transfer is active for SD/eMMC mode.
            __I uint32_t  RD_XFER_ACTIVE: 1;

            // Buffer Write Enable
            // 0x0 (DISABLED): Write disable
            // 0x1 (ENABLED): Write enable
            // This bit is used for non-DMA transfers. This bit is set if space is available for writing data
            __I uint32_t  BUF_WR_ENABLE: 1;

            // Buffer Read Enable
            // 0x0 (DISABLED): Read disable
            // 0x1 (ENABLED): Read enable
            // This bit is used for non-DMA transfers. This bit is set if valid data exists in the Host buffer
            __I uint32_t  BUF_RD_ENABLE: 1;

            __I uint32_t  : 4;

            // Card Inserted
            // 0x0 (FALSE): Reset, Debouncing, or No card
            // 0x1 (TRUE): Card Inserted
            __I uint32_t  CARD_INSERTED: 1;

            // Card Stable
            // 0x0 (FALSE): Reset or Debouncing
            // 0x1 (TRUE): No Card or Inserted
            __I uint32_t  CARD_STABLE: 1;

            // Card Detect Pin Level
            // 0x0 (FALSE): No card present
            // 0x1 (TRUE): Card Present
            __I uint32_t  CARD_DETECT_PIN_LEVEL: 1;

            // Write Protect Switch Pin Level
            // 0x0 (FALSE): Write protected
            // 0x1 (TRUE): Write enabled
            __I uint32_t  WR_PROTECT_SW_LVL: 1;

            // DAT[3:0] Line Signal Level
            // This bit is used to check the DAT line level to recover from errors and for debugging. These bits reflect the value of the sd_dat_in (lower nibble) signal.
            __I uint32_t  DAT_3_0: 4;

            // Command-Line Signal Level
            // This bit is used to check the CMD line level to recover from errors and for debugging. These bits reflect the value of the sd_cmd_in signal.
            __I uint32_t  CMD_LINE_LVL: 1;

            // Host Regulator Voltage Stable
            // This bit is used to check whether the host regulator voltage is stable for switching the voltage of UHS-I mode. This bit reflects the synchronized value of the host_reg_vol_stable signal.
            __I uint32_t  HOST_REG_VOL: 1;

            __I uint32_t  : 1;

            // Command Not Issued by Error
            // 0x0 (FALSE): Host Regulator Voltage is not stable
            // 0x1 (TRUE): Host Regulator Voltage is stable
            __I uint32_t  CMD_ISSUE_ERR: 1;

            // Sub Command Status
            // 0x0 (FALSE): Main Command Status
            // 0x1 (TRUE): Sub Command Status
            __I uint32_t  SUB_CMD_STAT: 1;

            // In Dormant Status
            // 0x0 (FALSE): Not in DORMANT state
            // 0x1 (TRUE): In DORMANT state
            __I uint32_t  IN_DORMANT_ST: 1;

            // Lane Synchronization
            // 0x0 (FALSE): UHS-II PHY is not initialized
            // 0x1 (TRUE): UHS-II PHY is initialized
            __I uint32_t  LANE_SYNC: 1;

            // UHS-II Interface Detection
            // 0x0 (FALSE): UHS-II interface is not detected
            // 0x1 (TRUE): UHS-II interface is detected
            __I uint32_t  UHS2_IF_DETECT: 1;
        } S_PSTATE;
    };


    union
    {
        __IO uint8_t HOST_CTRL1;          /*!< [0x0028] Host Control 1 Register   */
        struct
        {
            // LED Control
            // 0x0 (OFF): LED off
            // 0x1 (ON): LED on
            // This bit is used to caution the user not to remove the card while the SD card is being accessed. The value is reflected on the led_control signal.
            // Note: This bit is unused, do not set this bit to 0x1.
            __IO uint8_t  LED_CTRL: 1;

            // Data Transfer Width
            //  0x1 (FOUR_BIT): 4-bit mode
            //  0x0 (ONE_BIT): 1-bit mode
            // For SD/eMMC mode, this bit selects the data transfer width of the Host Controller. The Host Driver sets it to match the data width of the SD/eMMC card.
            __IO uint8_t  DAT_XFER_WIDTH: 1;

            // High Speed Enable
            //  0x1 (HIGH_SPEED): High Speed mode
            //  0x0 (NORMAL_SPEED): Normal Speed mode
            // In SD/eMMC mode, this bit is used to determine the selection of preset value for High Speed mode. Before setting this bit, the Host Driver checks the High Speed Support in the Capabilities register.
            // Note: DWC_MSHC always outputs the sd_cmd_out and sd_dat_out lines at the rising edge of cclk_tx clock irrespective of this bit. Please refer the section Connecting the Clock I/O interface in the Mobile Storage Host Controller user guide on clocking requirement for an SD/eMMC card.
            // Note: SD/eMMC Mode only.
            __IO uint8_t  HIGH_SPEED_EN: 1;

            // DMA Select
            //  0x0 (SDMA): SDMA is selected
            //  0x1 (RSVD_BIT): Reserved
            //  0x2 (ADMA2): ADMA2 is selected
            //  0x3 (ADMA2_3): ADMA2 or ADMA3 is selected
            // This field is used to select the DMA type.
            // When Host Version 4 Enable is 1 in Host Control 2 register:
            //  0x0 : SDMA is selected
            //  0x1 : Reserved
            //  0x2 : ADMA2 is selected
            //  0x3 : ADMA2 or ADMA3 is selected
            // When Host Version 4 Enable is 0 in Host Control 2 register:
            //  0x0 : SDMA is selected
            //  0x1 : Reserved
            //  0x2 : 32-bit Address ADMA2 is selected
            //  0x3 : 64-bit Address ADMA2 is selected
            __IO uint8_t  DMA_SEL: 2;

            // Extended Data Transfer Width
            //  0x1 (CARD_INSERTED): Card Inserted
            //  0x0 (No_CARD): No Card
            // This bit controls 8-bit bus width mode of embedded device.
            __IO uint8_t  EXT_DAT_XFER: 1;

            // Card Detect Test Level
            //  0x1 (CARD_INSERTED): Card Inserted
            //  0x0 (No_CARD): No Card
            // This bit is enabled while the Card Detect Signal Selection is set to 1 and it indicates whether a card inserted or not.
            __IO uint8_t  CARD_DETECT_TEST_LVL: 1;

            // Card Detect Signal Selection
            //  0x1 (CARD_DT_TEST_LEVEL): Card Detect Test Level is selected (for test purpose)
            //  0x0 (SDCD_PIN): SDCD# (card_detect_n signal) is selected (for normal use)
            // This bit selects a source for card detection. When the source for the card detection is switched, the interrupt must be disabled during the switching period.
            __IO uint8_t  CARD_DETECT_SIG_SEL: 1;

        } S_HOST_CTRL1;
    };


    union
    {
        __IO uint8_t PWR_CTRL;           /*!< [0x0029] Power Control Register     */
        struct
        {
            // SD Bus Power for VDD1
            //   0x0 (OFF): Power off
            //   0x1 (ON): Power on
            // This bit enables VDD1 power of the card. This setting is available on the sd_vdd1_on output of DWC_mshc so that it can be used to control the VDD1 power supply of the card. Before setting this bit, the SD Host Driver sets the SD Bus Voltage Select bit. If the Host Controller detects a No Card state, this bit is cleared.
            // In SD mode, if this bit is cleared, the Host Controller stops the SD Clock by clearing the SD_CLK_IN bit in the CLK_CTRL_R register.
            __IO uint8_t  SD_BUS_PWR_VDD1: 1;

            // SD Bus Voltage Select for VDD1/eMMC Bus Voltage Select for VDD
            //   0x7 (V_3_3): 3.3V (Typ.)
            //   0x6 (V_3_0): 3.0V (Typ.)
            //   0x5 (V_1_8): 1.8V (Typ.) for Embedded
            //   0x4 (RSVD4): Reserved
            //   0x3 (RSVD3): Reserved
            //   0x2 (RSVD2): Reserved
            //   0x1 (RSVD1): Reserved
            //   0x0 (RSVD0): Reserved
            // These bits enable the Host Driver to select the voltage level for an SD/eMMC card. Before setting this register, the Host Driver checks the Voltage Support bits in the Capabilities register. If an unsupported voltage is selected, the Host System does not supply the SD Bus voltage. The value set in this field is available on the DWC_mshc output signal (sd_vdd1_sel), which is used by the voltage switching circuitry.
            // SD Bus Voltage Select options:
            //   0x7 : 3.3V(Typical)
            //   0x6 : 3.0V(Typical)
            //   0x5 : 1.8V(Typical) for Embedded
            //   0x4 : 0x0 - Reserved
            // eMMC Bus Voltage Select options:
            //   0x7 : 3.3V(Typical)
            //   0x6 : 1.8V(Typical)
            //   0x5 : 1.2V(Typical)
            //   0x4 : 0x0 - Reserved
            __IO uint8_t  SD_BUS_VOL_VDD1: 3;

            // SD Bus Power for VDD2
            // This is irrelevant for SD/eMMC card.
            //   0x0 (OFF): Power off
            //   0x1 (ON): Power on
            __IO uint8_t  SD_BUS_PWR_VDD2: 1;

            // SD Bus Voltage Select for VDD2
            // This is irrelevant for SD/eMMC card.
            //   0x7 (NOT_USED7): Not used
            //   0x6 (NOT_USED6): Not used
            //   0x5 (V_1_8): 1.8V
            //   0x4 (V_1_2): Reserved for 1.2V
            //   0x3 (RSVD3): Reserved
            //   0x2 (RSVD2): Reserved
            //   0x1 (RSVD1): Reserved
            //   0x0 (NO_VDD2): VDD2 Not Supported
            __IO uint8_t  SD_BUS_VOL_VDD2: 3;
        } S_PWR_CTRL;
    };


    union
    {
        __IO uint8_t BGAP_CTRL;          /*!< [0x002A] Block Gap Control Register     */
        struct
        {
            // Stop At Block Gap Request
            //   0x0 (XFER): Transfer
            //   0x1 (STOP): Stop
            // This bit is used to stop executing read and write transactions at the next block gap for non-DMA, SDMA, and ADMA transfers.
            __IO uint8_t  STOP_BG_REQ: 1;

            // Continue Request
            //   0x0 (NO_AFFECT): No Affect
            //   0x1 (RESTART): Restart
            // This bit is used to restart the transaction, which was stopped using the Stop At Block Gap Request. The Host Controller automatically clears this bit when the transaction restarts. If stop at block gap request is set to 1, any write to this bit is ignored.
            __IO uint8_t  CONTINUE_REQ: 1;

            // Read Wait Control
            //   0x0 (DISABLE): Disable Read Wait Control
            //   0x1 (ENABLE): Enable Read Wait Control
            // This bit is used to enable the read wait protocol to stop read data using DAT[2] line if the card supports read wait. Otherwise, the Host Controller has to stop the card clock to hold the read data.
            __IO uint8_t  RD_WAIT_CTRL: 1;

            // These bits of the Block Gap Control register are reserved and always return 0.
            // Interrupt At Block Gap
            //   0x0 (DISABLE): Disabled
            //   0x1 (ENABLE): Enabled
            // This bit is valid only in the 4-bit mode of an SDIO card and is used to select a sample point in the interrupt cycle. Setting to 1 enables interrupt detection at the block gap for a multiple block transfer.
            __IO uint8_t  INT_AT_BGAP: 1;

            __IO uint8_t  : 4;
        } S_BGAP_CTRL;
    };


    union
    {
        __IO uint8_t WUP_CTRL;          /*!< [0x002B] Wake-up Control Register     */
        struct
        {
            // CARD_INT Wakeup Event Enable on Card Interrupt
            //   0x0 (DISABLED): Disable
            //   0x1 (ENABLED): Enable
            // This bit enables wakeup event through a Card Interrupt assertion in the Normal Interrupt Status register.
            // This bit can be set to 1 if FN_WUS (Wake Up Support) in CIS is set to 1.
            __IO uint8_t  CARD_INT: 1;

            // CARD_INSERT  Wakeup Event Enable on SD Card Insertion
            //   0x0 (DISABLED): Disable
            //   0x1 (ENABLED): Enable
            // This bit enables wakeup event through Card Insertion assertion in the Normal Interrupt Status register.
            // FN_WUS (Wake Up Support) in CIS does not affect this bit.
            __IO uint8_t  CARD_INSERT: 1;

            // CARD_REMOVAL Wakeup Event Enable on SD Card Removal
            //   0x0 (DISABLED): Disable
            //   0x1 (ENABLED): Enable
            // This bit enables wakeup event through Card Removal assertion in the Normal Interrupt Status register.
            // For the SDIO card, Wake Up Support (FN_WUS) in the Card Information Structure (CIS) register does not affect this bit.
            __IO uint8_t  CARD_REMOVAL: 1;

            __IO uint8_t  : 5;
        } S_WUP_CTRL;
    };


    union
    {
        __IO uint16_t CLK_CTRL;          /*!< [0x002C] Clock Control Register     */
        struct
        {
            // INTERNAL_CLK_EN  Internal Clock Enable
            //   0x0 (FALSE): Stop
            //   0x1 (TRUE): Oscillate
            // This bit is set to 0 when the Host Driver is not using the Host Controller or the Host Controller awaits a wakeup interrupt.
            // The Host Controller must stop its internal clock to enter a very low power state. However, registers can still be read and written to.
            // The value is reflected on the intclk_en signal.
            // Note: If this bit is not used to control the internal clock (base clock and master clock), it is recommended to set this bit to '1' .
            __IO uint16_t  INTERNAL_CLK_EN: 1;

            // INTERNAL_CLK_STABLE  Internal Clock Stable
            //   0x0 (FALSE): Not Ready
            //   0x1 (TRUE): Ready
            // This bit enables the Host Driver to check the clock stability twice after the Internal Clock Enable bit is set and after the PLL Enable bit is set.
            // This bit reflects the synchronized value of the intclk_stable signal after the Internal Clock Enable bit is set to 1 and also reflects the synchronized value of the
            // card_clk_stable signal after the PLL Enable bit is set to 1.
            __IO uint16_t  INTERNAL_CLK_STABLE: 1;

            // SD_CLK_EN    SD/eMMC Clock Enable
            //   0x0 (FALSE): Disable providing SDCLK/RCLK
            //   0x1 (TRUE): Enable providing SDCLK/RCLK
            // This bit stops the SDCLK or RCLK when set to 0. The SDCLK/RCLK Frequency Select bit can be changed when this bit is set to 0. The value is reflected on the clk2card_on pin.
            __IO uint16_t  SD_CLK_EN: 1;

            // PLL_ENABLE   PLL Enable
            //   0x0 (FALSE): PLL is in low power mode
            //   0x1 (TRUE): PLL is enabled
            // This bit is used to activate the PLL (applicable when Host Version 4 Enable = 1). When Host Version 4 Enable = 0, INTERNAL_CLK_EN bit may be used to activate PLL.
            // The value is reflected on the card_clk_en signal.
            // Note: If this bit is not used to to active the PLL when Host Version 4 Enable = 1, it is recommended to set this bit to '1' .
            __IO uint16_t  PLL_ENABLE: 1;

            __IO uint16_t  : 1;

            // CLK_GEN_SELECT   Clock Generator Select
            //   0x0 (FALSE): Divided Clock Mode
            //   0x1 (TRUE): Programmable Clock Mode
            // This bit is used to select the clock generator mode in SDCLK/RCLK Frequency Select. If Preset Value Enable = 0, this bit is set by the Host Driver.
            // If Preset Value Enable = 1, this bit is automatically set to a value specified in one of the Preset Value registers. The value is reflected on the card_clk_gen_sel signal.
            __IO uint16_t  CLK_GEN_SELECT: 1;

            // UPPER_FREQ_SEL   These bits specify the upper 2 bits of 10-bit SDCLK/RCLK Frequency Select control The value is reflected on the upper 2 bits of the card_clk_freq_sel signal.
            __IO uint16_t  UPPER_FREQ_SEL: 2;

            // FREQ_SEL SDCLK/RCLK Frequency Select
            // These bits are used to select the frequency of the SDCLK signal. These bits depend on setting of Preset Value Enable in the Host Control 2 register.
            // If Preset Value Enable = 0, these bits are set by the Host Driver.
            // If Preset Value Enable = 1, these bits are automatically set to a value specified in one of the Preset Value register.
            // The value is reflected on the lower 8-bit of the card_clk_freq_sel signal.
            // 10-bit Divided Clock Mode:
            //   0x3FF : 1/2046 Divided clock
            //   ..........
            //   N : 1/2N Divided Clock
            //   ..........
            //   0x002 : 1/4 Divided Clock
            //   0x001 : 1/2 Divided Clock
            //   0x000 : Base clock
            __IO uint16_t  FREQ_SEL: 8;
        } S_CLK_CTRL;
    };


    union
    {
        __IO uint8_t TOUT_CTRL;          /*!< [0x002E] Timeout Control Register     */
        struct
        {
            // TOUT_CNT Data Timeout Counter Value
            // This value determines the interval by which DAT line timeouts are detected.
            // The Timeout clock frequency is generated by dividing the base clock TMCLK value by this value.
            // When setting this register, prevent inadvertent timeout events by clearing the Data Timeout Error Status Enable (in the Error Interrupt Status Enable register).
            // The values for these bits are:
            //   0xF : Reserved
            //   0xE : TMCLK x 2^27
            //   .........
            //   0x1 : TMCLK x 2^14
            //   0x0 : TMCLK x 2^13
            // Note: During a boot operating in an eMMC mode, an application must configure the boot data timeout value (approximately 1 sec) in this bit.
            __IO uint8_t  TOUT_CNT: 4;

            __IO uint8_t  : 4;
        } S_TOUT_CTRL;
    };


    union
    {
        __IO uint8_t SW_RST;             /*!< [0x002F] Software Reset Register     */
        struct
        {
            // SW_RST_ALL   Software Reset For All
            //   0x0 (FALSE): Work
            //   0x1 (TRUE): Reset
            // This reset affects the entire Host Controller except for the card detection circuit.
            // During its initialization, the Host Driver sets this bit to 1 to reset the Host Controller.
            // All registers are reset except the capabilities register. If this bit is set to 1, the Host Driver must issue reset command and reinitialize the card.
            __IO uint8_t  SW_RST_ALL: 1;

            // SW_RST_CMD   Software Reset For CMD line
            //   0x0 (FALSE): Work
            //   0x1 (TRUE): Reset
            // This bit resets only a part of the command circuit to be able to issue a command.
            // This reset is effective only for a command issuing circuit (including response error statuses related to Command Inhibit (CMD) control) and does not affect the data transfer circuit.
            // Host Controller can continue data transfer even after this reset is executed while handling subcommand-response errors.
            // The following registers and bits are cleared by this bit:
            //   Present State register : Command Inhibit (CMD) bit
            //   Normal Interrupt Status register : Command Complete bit
            //   Error Interrupt Status : Response error statuses related to Command Inhibit (CMD) bit
            __IO uint8_t  SW_RST_CMD: 1;

            // SW_RST_DAT   Software Reset For DAT line
            //   0x0 (FALSE): Work
            //   0x1 (TRUE): Reset
            // This bit is used in SD/eMMC mode and it resets only a part of the data circuit and the DMA circuit is also reset.
            // The following registers and bits are cleared by this bit:
            // Buffer Data Port register
            //   Buffer is cleared and initialized.
            // Present state register
            //   Buffer Read Enable
            //   Buffer Write Enable
            //   Read Transfer Active
            //   Write Transfer Active
            //   DAT Line Active
            //   Command Inhibit (DAT)
            // Block Gap Control register
            //   Continue Request
            //   Stop At Block Gap Request
            // Normal Interrupt status register
            //   Buffer Read Ready
            //   Buffer Write Ready
            //   DMA Interrupt
            //   Block Gap Event
            //   Transfer Complete
            __IO uint8_t  SW_RST_DAT: 1;

            __IO uint8_t  : 5;
        } S_SW_RST;
    };


    union
    {
        __IO uint16_t NORMAL_INT_STAT;   /*!< [0x0030] Normal Interrupt Status Register     */
        struct
        {
            // CMD_COMPLETE Command Complete
            //   0x0 (FALSE): No command complete
            //   0x1 (TRUE): Command Complete
            // In an SD/eMMC Mode, this bit is set when the end bit of a response except for Auto CMD12 and Auto CMD23.
            // This interrupt is not generated when the Response Interrupt Disable in Transfer Mode Register is set to 1.
            __IO uint16_t  CMD_COMPLETE: 1;

            // XFER_COMPLETE    Transfer Complete
            //   0x0 (FALSE): Not complete
            //   0x1 (TRUE): Command execution is completed
            // This bit is set when a read/write transfer and a command with status busy is completed.
            __IO uint16_t  XFER_COMPLETE: 1;

            // BGAP_EVENT   Block Gap Event
            //   0x0 (FALSE): No Block Gap Event
            //   0x1 (TRUE): Transaction stopped at block gap
            // This bit is set when both read/write transaction is stopped at block gap due to a Stop at Block Gap Request.
            __IO uint16_t  BGAP_EVENT: 1;

            // DMA_INTERRUPT    DMA Interrupt
            //   0x0 (FALSE): No DMA Interrupt
            //   0x1 (TRUE): DMA Interrupt is generated
            // This bit is set if the Host Controller detects the SDMA Buffer Boundary during transfer. In case of ADMA, by setting the Int field in the descriptor table, the Host controller generates this interrupt. This interrupt is not generated after a Transfer Complete.
            __IO uint16_t  DMA_INTERRUPT: 1;

            // BUF_WR_READY Buffer Write Ready
            //   0x0 (FALSE): Not ready to write buffer
            //   0x1 (TRUE): Ready to write buffer
            // This bit is set if the Buffer Write Enable changes from 0 to 1.
            __IO uint16_t  BUF_WR_READY: 1;

            // BUF_RD_READY Buffer Read Ready
            //   0x0 (FALSE): Not ready to read buffer
            //   0x1 (TRUE): Ready to read buffer
            // This bit is set if the Buffer Read Enable changes from 0 to 1.
            __IO uint16_t  BUF_RD_READY: 1;

            // CARD_INSERTION   Card Insertion
            //   0x0 (FALSE): Card state stable or Debouncing
            //   0x1 (TRUE): Card Inserted
            // This bit is set if the Card Inserted in the Present State register changes from 0 to 1.
            __IO uint16_t  CARD_INSERTION: 1;

            // CARD_REMOVAL Card Removal
            //   0x0 (FALSE): Card state stable or Debouncing
            //   0x1 (TRUE): Card Removed
            // This bit is set if the Card Inserted in the Present State register changes from 1 to 0.
            __IO uint16_t  CARD_REMOVAL: 1;

            // CARD_INTERRUPT   Card Interrupt
            //   0x0 (FALSE): No Card Interrupt
            //   0x1 (TRUE): Generate Card Interrupt
            // This bit reflects the synchronized value of:
            //   DAT[1] Interrupt Input for SD Mode
            //   DAT[2] Interrupt Input for UHS-II Mode
            __IO uint16_t  CARD_INTERRUPT: 1;

            // INT_A    INT_A
            // This bit is set if INT_A is enabled and if INT_A# pin is in low level. The INT_A# pin is not supported.
            __IO uint16_t  INT_A: 1;

            // INT_B    INT_B
            // This bit is set if INT_B is enabled and if INT_B# pin is in low level. The INT_B# pin is not supported.
            __IO uint16_t  INT_B: 1;

            // INT_C    INT_C
            // This bit is set if INT_C is enabled and if INT_C# pin is in low level. The INT_C# pin is not supported.
            __IO uint16_t  INT_C: 1;

            // RE_TUNE_EVENT    Re-tuning Event
            // This bit is set if the Re-Tuning Request changes from 0 to 1. Re-Tuning request is not supported.
            __IO uint16_t  RE_TUNE_EVENT: 1;

            // FX_EVENT FX Event
            //   0x0 (FALSE): No Event
            //   0x1 (TRUE): FX Event is detected
            // This status is set when R[14] of response register is set to 1 and Response Type R1/R5 is set to 0 in Transfer Mode register. This interrupt is used with response check function.
            __IO uint16_t  FX_EVENT: 1;

            // CQE_EVENT    Command Queuing Event
            //   0x0 (FALSE): No Event
            //   0x1 (TRUE): Command Queuing Event is detected
            // This status is set if Command Queuing/Crypto related event has occurred in eMMC/SD mode. Read CQHCI's CQIS/CRNQIS register for more details.
            __IO uint16_t  CQE_EVENT: 1;

            // ERR_INTERRUPT    Error Interrupt
            //   0x0 (FALSE): No Error
            //   0x1 (TRUE): Error
            // If any of the bits in the Error Interrupt Status register are set, then this bit is set.
            __IO uint16_t  ERR_INTERRUPT: 1;

        } S_NORMAL_INT_STAT;
    };


    union
    {
        __IO uint16_t ERROR_INT_STAT;   /*!< [0x0032] Error Interrupt Status Register     */
        struct
        {
            // CMD_TOUT_ERR Command Timeout Error
            // In SD/eMMC Mode, this bit is set only if no response is returned within 64 SD clock cycles from the end bit of the command.
            // If the Host Controller detects a CMD line conflict, along with Command CRC Error bit, this bit is set to 1, without waiting for 64 SD/eMMC card clock cycles.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Time out
            __IO uint16_t  CMD_TOUT_ERR: 1;

            // CMD_CRC_ERR  Command CRC Error
            // Command CRC Error is generated in SD/eMMC mode for following two cases.
            // If a response is returned and the Command Timeout Error is set to 0 (indicating no timeout), this bit is set to 1 when detecting a CRC error in the command response.
            // The Host Controller detects a CMD line conflict by monitoring the CMD line when a command is issued.
            // If the Host Controller drives the CMD line to 1 level, but detects 0 level on the CMD line at the next SD clock edge,
            // then the Host Controller aborts the command (stop driving CMD line) and set this bit to 1. The Command Timeout Error is also set to 1 to distinguish a CMD line conflict.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): CRC error generated
            __IO uint16_t  CMD_CRC_ERR: 1;

            // CMD_END_BIT_ERR  Command End Bit Error
            // This bit is set when detecting that the end bit of a command response is 0 in SD/eMMC mode.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): End Bit error generated
            __IO uint16_t  CMD_END_BIT_ERR: 1;

            // CMD_IDX_ERR  Command Index Error
            // This bit is set if a Command Index error occurs in the command respons in SD/eMMC mode.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  CMD_IDX_ERR: 1;

            // DATA_TOUT_ERR    Data Timeout Error
            // This bit is set in SD/eMMC mode when detecting one of the following timeout conditions:
            // Busy timeout for R1b, R5b type
            // Busy timeout after Write CRC status
            // Write CRC Status timeout
            // Read Data timeout
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Time out
            __IO uint16_t  DATA_TOUT_ERR: 1;

            // DATA_CRC_ERR Data CRC Error
            // This error occurs in SD/eMMC mode when detecting CRC error when transferring read data which uses the DAT line, when detecting the Write CRC status having a value of other than 010 or when write CRC status timeout.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  DATA_CRC_ERR: 1;

            // DATA_END_BIT_ERR Data End Bit Error
            // This error occurs in SD/eMMC mode either when detecting 0 at the end bit position of read data that uses the DAT line or at the end bit position of the CRC status.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  DATA_END_BIT_ERR: 1;

            // CUR_LMT_ERR  Current Limit Error
            // By setting the SD Bus Power bit in the Power Control register, the Host Controller is requested to supply power for the SD Bus.
            // If the Host Controller supports the Current Limit function, it can be protected from an illegal card by stopping power supply to the card
            // in which case this bit indicates a failure status.
            // A reading of 1 for this bit means that the Host Controller is not supplying power to the SD card due to some failure.
            // A reading of 0 for this bit means that the Host Controller is supplying power and no error has occurred.
            // The Host Controller may require some sampling time to detect the current limit. DWC_mshc Host Controller does not support this function, this bit is always set to 0.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Power Fail
            __IO uint16_t  CUR_LMT_ERR: 1;

            // AUTO_CMD_ERR Auto CMD Error
            // This error status is used by Auto CMD12 and Auto CMD23 in SD/eMMC mode.
            // This bit is set when detecting that any of the bits D00 to D05 in Auto CMD Error Status register has changed from 0 to 1.
            // D07 is effective in case of Auto CMD12. Auto CMD Error Status register is valid while this bit is set to 1 and may be cleared by clearing of this bit.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  AUTO_CMD_ERR: 1;

            // ADMA_ERR ADMA Error
            // This bit is set when the Host Controller detects error during ADMA-based data transfer. The error could be due to following reasons:
            // Error response received from System bus (Master I/F)
            // ADMA3,ADMA2 Descriptors invalid
            // CQE Task or Transfer descriptors invalid
            // When the error occurs, the state of the ADMA is saved in the ADMA Error Status register.
            // In eMMC CQE mode:
            // The Host Controller generates this Interrupt when it detects an invalid descriptor data (Valid=0) at the ST_FDS state.
            // ADMA Error State in the ADMA Error Status indicates that an error has occurred in ST_FDS state. The Host Driver may find that Valid bit is not set at the error descriptor.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  ADMA_ERR: 1;

            // TUNING_ERR   Tuning Error
            // This bit is set when an unrecoverable error is detected in a tuning circuit except during the tuning procedure (occurrence of an error during tuning procedure is indicated by Sampling Clock Select in the Host Control 2 register). By detecting Tuning Error, Host Driver needs to abort a command executing and perform tuning.
            // To reset tuning circuit, Sampling Clock Select is set to 0 before executing tuning procedure.
            // The Tuning Error is higher priority than the other error interrupts generated during data transfer.
            // By detecting Tuning Error, the Host Driver must discard data transferred by a current read/write command and retry data transfer after the Host Controller retrieved from the tuning circuit error. This is applicable in SD/eMMC mode.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  TUNING_ERR: 1;

            // RESP_ERR Response Error
            // Host Controller Version 4.00 supports response error check function to avoid overhead of response error check by Host Driver during DMA execution.
            // If Response Error Check Enable is set to 1 in the Transfer Mode register, Host Controller Checks R1 or R5 response.
            // If an error is detected in a response, this bit is set to 1.This is applicable in SD/eMMC mode.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  RESP_ERR: 1;

            // BOOT_ACK_ERR Boot Acknowledgement Error
            // This bit is set when there is a timeout for boot acknowledgement or when detecting boot ack status having a value other than 010.
            // This is applicable only when boot acknowledgement is expected in eMMC mode.
            //   0x0 (FALSE): No error
            //   0x1 (TRUE): Error
            __IO uint16_t  BOOT_ACK_ERR: 1;

            // VENDOR_ERR1  This bit (VENDOR_ERR1) of the ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  VENDOR_ERR1: 1;

            // VENDOR_ERR2  This bit (VENDOR_ERR2) of the ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  VENDOR_ERR2: 1;

            // VENDOR_ERR3  This bit (VENDOR_ERR3) of the ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  VENDOR_ERR3: 1;

        } S_ERROR_INT_STAT;
    };


    union
    {
        __IO uint16_t NORMAL_INT_STAT_EN;   /*!< [0x0034] Normal Interrupt Status Enable Register     */
        struct
        {
            // CMD_COMPLETE_STAT_EN Command Complete Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CMD_COMPLETE_STAT_EN: 1;

            // XFER_COMPLETE_STAT_EN    Transfer Complete Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  XFER_COMPLETE_STAT_EN: 1;

            // BGAP_EVENT_STAT_EN   Block Gap Event Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BGAP_EVENT_STAT_EN: 1;

            // DMA_INTERRUPT_STAT_EN    DMA Interrupt Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  DMA_INTERRUPT_STAT_EN: 1;

            // BUF_WR_READY_STAT_EN Buffer Write Ready Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BUF_WR_READY_STAT_EN: 1;

            // BUF_RD_READY_STAT_EN Buffer Read Ready Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BUF_RD_READY_STAT_EN: 1;

            // CARD_INSERTION_STAT_EN   Card Insertion Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_INSERTION_STAT_EN: 1;

            // CARD_REMOVAL_STAT_EN Card Removal Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_REMOVAL_STAT_EN: 1;

            // CARD_INTERRUPT_STAT_EN   Card Interrupt Status Enable
            // If this bit is set to 0, the Host Controller clears the interrupt request to the System.
            // The Card Interrupt detection is stopped when this bit is cleared and restarted when this bit is set to 1.
            // The Host Driver may clear the Card Interrupt Status Enable before servicing the Card Interrupt and may set this bit again after all interrupt requests from the card are cleared to prevent inadvertent interrupts.
            // By setting this bit to 0, interrupt input must be masked by implementation so that the interrupt input is not affected by external signal in any state (for example, floating).
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_INTERRUPT_STAT_EN: 1;

            // INT_A_STAT_EN    INT_A Status Enable
            // If this bit is set to 0, the Host Controller clears the interrupt request to the System.
            // The Host Driver may clear this bit before servicing the INT_A and may set this bit again after all interrupt requests to INT_A pin are cleared to prevent inadvertent interrupts.
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_A_STAT_EN: 1;

            // INT_B_STAT_EN    INT_B Status Enable
            // If this bit is set to 0, the Host Controller clears the interrupt request to the System.
            // The Host Driver may clear this bit before servicing the INT_B and may set this bit again after all interrupt requests to INT_B pin are cleared to prevent inadvertent interrupts.
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_B_STAT_EN: 1;

            // INT_C_STAT_EN    INT_C Status Enable
            // If this bit is set to 0, the Host Controller clears the interrupt request to the System.
            // The Host Driver may clear this bit before servicing the INT_C and may set this bit again after all interrupt requests to INT_C pin are cleared to prevent inadvertent interrupts.
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_C_STAT_EN: 1;

            // RE_TUNE_EVENT_STAT_EN    Re-Tuning Event Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: UHS-I only.
            __IO uint16_t  RE_TUNE_EVENT_STAT_EN: 1;

            // FX_EVENT_STAT_EN FX Event Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // This bit is added from Version 4.10.
            __IO uint16_t  FX_EVENT_STAT_EN: 1;

            // CQE_EVENT_STAT_EN    CQE Event Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CQE_EVENT_STAT_EN: 1;

            __IO uint16_t  : 1;
        } S_NORMAL_INT_STAT_EN;
    };


    union
    {
        __IO uint16_t ERROR_INT_STAT_EN;   /*!< [0x0036] Error Interrupt Status Enable Register     */
        struct
        {
            // CMD_TOUT_ERR_STAT_EN Command Timeout Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_TOUT_ERR_STAT_EN: 1;

            // CMD_CRC_ERR_STAT_EN  Command CRC Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_CRC_ERR_STAT_EN: 1;

            // CMD_END_BIT_ERR_STAT_EN  Command End Bit Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_END_BIT_ERR_STAT_EN: 1;

            // CMD_IDX_ERR_STAT_EN  Command Index Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_IDX_ERR_STAT_EN: 1;

            // DATA_TOUT_ERR_STAT_EN    Data Timeout Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_TOUT_ERR_STAT_EN: 1;

            // DATA_CRC_ERR_STAT_EN Data CRC Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_CRC_ERR_STAT_EN: 1;

            // DATA_END_BIT_ERR_STAT_EN Data End Bit Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_END_BIT_ERR_STAT_EN: 1;

            // CUR_LMT_ERR_STAT_EN  Current Limit Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CUR_LMT_ERR_STAT_EN: 1;

            // AUTO_CMD_ERR_STAT_EN Auto CMD Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  AUTO_CMD_ERR_STAT_EN: 1;

            // ADMA_ERR_STAT_EN ADMA Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  ADMA_ERR_STAT_EN: 1;

            // TUNING_ERR_STAT_EN   Tuning Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: UHS-I Mode only.
            __IO uint16_t  TUNING_ERR_STAT_EN: 1;

            // RESP_ERR_STAT_EN Response Error Status Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD Mode only.
            __IO uint16_t  RESP_ERR_STAT_EN: 1;

            // BOOT_ACK_ERR_STAT_EN Boot Acknowledgment Error
            // Setting this bit to 1 enables setting of Boot Acknowledgment Error in Error Interrupt Status register (ERROR_INT_STAT_R).
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: eMMC Mode only.
            __IO uint16_t  BOOT_ACK_ERR_STAT_EN: 1;

            // VENDOR_ERR_STAT_EN1  The 13th bit of Error Interrupt Status Enable register is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_STAT_EN1: 1;

            // VENDOR_ERR_STAT_EN2  The 14th bit of Error Interrupt Status Enable register is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_STAT_EN2: 1;

            // VENDOR_ERR_STAT_EN3  The 15th bit of Error Interrupt Status Enable register is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_STAT_EN3: 1;

        } S_ERROR_INT_STAT_EN;
    };


    union
    {
        __IO uint16_t NORMAL_INT_SIGNAL_EN;   /*!< [0x0038] Normal Interrupt Signal Enable Register     */
        struct
        {
            // CMD_COMPLETE_SIGNAL_EN   Command Complete Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CMD_COMPLETE_SIGNAL_EN: 1;

            // XFER_COMPLETE_SIGNAL_EN  Transfer Complete Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  XFER_COMPLETE_SIGNAL: 1;

            // BGAP_EVENT_SIGNAL_EN Block Gap Event Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BGAP_EVENT_SIGNAL_EN: 1;

            // DMA_INTERRUPT_SIGNAL_EN  DMA Interrupt Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  DMA_INTERRUPT_SIGNAL_EN: 1;

            // BUF_WR_READY_SIGNAL_EN   Buffer Write Ready Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BUF_WR_READY_SIGNAL_EN: 1;

            // BUF_RD_READY_SIGNAL_EN   Buffer Read Ready Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  BUF_RD_READY_SIGNAL_EN: 1;

            // CARD_INSERTION_SIGNAL_EN Card Insertion Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_INSERTION_SIGNAL_EN: 1;

            // CARD_REMOVAL_SIGNAL_EN   Card Removal Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_REMOVAL_SIGNAL_EN: 1;

            // CARD_INTERRUPT_SIGNAL_EN Card Interrupt Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CARD_INTERRUPT_SIGNAL_EN: 1;

            // INT_A_SIGNAL_EN  INT_A Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_A_SIGNAL_EN: 1;

            // INT_B_SIGNAL_EN  INT_B Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_B_SIGNAL_EN: 1;

            // INT_C_SIGNAL_EN  INT_C Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  INT_C_SIGNAL_EN: 1;

            // RE_TUNE_EVENT_SIGNAL_EN  Re-Tuning Event Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: UHS-I only.
            __IO uint16_t  RE_TUNE_EVENT_SIGNAL_EN: 1;

            // FX_EVENT_SIGNAL_EN   FX Event Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  FX_EVENT_SIGNAL_EN: 1;

            // CQE_EVENT_SIGNAL_EN  Command Queuing Engine Event Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CQE_EVENT_SIGNAL_EN: 1;

            __IO uint16_t  : 1;

        } S_NORMAL_INT_SIGNAL_EN;
    };


    union
    {
        __IO uint16_t ERROR_INT_SIGNAL_EN;   /*!< [0x003A] Error Interrupt Signal Enable Register     */
        struct
        {
            // CMD_TOUT_ERR_SIGNAL_EN   Command Timeout Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_TOUT_ERR_SIGNAL_EN: 1;

            // CMD_CRC_ERR_SIGNAL_EN    Command CRC Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_CRC_ERR_SIGNAL_EN: 1;

            // CMD_END_BIT_ERR_SIGNAL_EN    Command End Bit Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_END_BIT_ERR_SIGNAL_EN: 1;

            // CMD_IDX_ERR_SIGNAL_EN    Command Index Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  CMD_IDX_ERR_SIGNAL_EN: 1;

            // DATA_TOUT_ERR_SIGNAL_EN  Data Timeout Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_TOUT_ERR_SIGNAL_EN: 1;

            // DATA_CRC_ERR_SIGNAL_EN   Data CRC Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_CRC_ERR_SIGNAL_EN: 1;

            // DATA_END_BIT_ERR_SIGNAL_EN   Data End Bit Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  DATA_END_BIT_ERR_SIGNAL_EN: 1;

            // CUR_LMT_ERR_SIGNAL_EN    Current Limit Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  CUR_LMT_ERR_SIGNAL_EN: 1;

            // AUTO_CMD_ERR_SIGNAL_EN   Auto CMD Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD/eMMC Mode only.
            __IO uint16_t  AUTO_CMD_ERR_SIGNAL_EN: 1;

            // ADMA_ERR_SIGNAL_EN   ADMA Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  ADMA_ERR_SIGNAL_EN: 1;

            // TUNING_ERR_SIGNAL_EN Tuning Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: UHS-I Mode only.
            __IO uint16_t  TUNING_ERR_SIGNAL_EN: 1;

            // RESP_ERR_SIGNAL_EN   Response Error Signal Enable
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: SD Mode only.
            __IO uint16_t  RESP_ERR_SIGNAL_EN: 1;

            // BOOT_ACK_ERR_SIGNAL_EN   Boot Acknowledgment Error
            // Setting this bit to 1 enables generating interrupt signal when Boot Acknowledgement Error in Error Interrupt Status register is set.
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            // Note: eMMC Mode only.
            __IO uint16_t  BOOT_ACK_ERR_SIGNAL_EN: 1;

            // VENDOR_ERR_SIGNAL_EN1    The 14th bit of Error Interrupt Signal Enable is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_SIGNAL_EN1: 1;

            // VENDOR_ERR_SIGNAL_EN2    The 15th bit of Error Interrupt Signal Enable is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_SIGNAL_EN2: 1;

            // VENDOR_ERR_SIGNAL_EN3    The 16th bit of Error Interrupt Signal Enable is reserved
            //   0x0 (FALSE): Masked
            //   0x1 (TRUE): Enabled
            __IO uint16_t  VENDOR_ERR_SIGNAL_EN3: 1;

        } S_ERROR_INT_SIGNAL_EN;
    };


    union
    {
        __IO uint16_t AUTO_CMD_STAT;    /*!< [0x003C] ErrorAuto CMD Status  Register     */
        struct
        {
            // AUTO_CMD12_NOT_EXEC  Auto CMD12 Not Executed
            // If multiple memory block data transfer is not started due to a command error, this bit is not set because it is not necessary to issue an Auto CMD12. Setting this bit to 1 means that the Host Controller cannot issue Auto CMD12 to stop multiple memory block data transfer, due to some error. If this bit is set to 1, error status bits (D04-D01) is meaningless.
            // This bit is set to 0 when Auto CMD Error is generated by Auto CMD23.
            //   0x0 (FALSE): Not Executed
            //   0x1 (TRUE): Executed
            __IO uint16_t  AUTO_CMD12_NOT_EXEC: 1;

            // AUTO_CMD_TOUT_ERR    Auto CMD Timeout Error
            // This bit is set if no response is returned with 64 SDCLK cycles from the end bit of the command.
            // If this bit is set to 1, error status bits (D04-D01) are meaningless.
            //   0x0 (FALSE): Time out
            //   0x1 (TRUE): No Error
            __IO uint16_t  AUTO_CMD_TOUT_ERR: 1;

            // AUTO_CMD_CRC_ERR Auto CMD CRC Error
            // This bit is set when detecting a CRC error in the command response.
            //   0x0 (FALSE): CRC Error Generated
            //   0x1 (TRUE): No Error
            __IO uint16_t  AUTO_CMD_CRC_ERR: 1;

            // AUTO_CMD_EBIT_ERR    Auto CMD End Bit Error
            // This bit is set when detecting that the end bit of command response is 0.
            //   0x0 (FALSE): End Bit Error Generated
            //   0x1 (TRUE): No Error
            __IO uint16_t  AUTO_CMD_EBIT_ERR: 1;

            // AUTO_CMD_IDX_ERR Auto CMD Index Error
            // This bit is set if the command index error occurs in response to a command.
            //   0x1 (TRUE): Error
            //   0x0 (FALSE): No Error
            __IO uint16_t  AUTO_CMD_IDX_ERR: 1;

            // AUTO_CMD_RESP_ERR    Auto CMD Response Error
            // This bit is set when Response Error Check Enable in the Transfer Mode register is set to 1 and an error is detected in R1 response of either Auto CMD12 or CMD13. This status is ignored if any bit between D00 to D04 is set to 1.
            //   0x1 (TRUE): Error
            //   0x0 (FALSE): No Error
            __IO uint16_t  AUTO_CMD_RESP_ERR: 1;

            __IO uint16_t  : 1;

            // CMD_NOT_ISSUED_AUTO_CMD12    Command Not Issued By Auto CMD12 Error
            // If this bit is set to 1, CMD_wo_DAT is not executed due to an Auto CMD12 Error (D04-D01) in this register.
            // This bit is set to 0 when Auto CMD Error is generated by Auto CMD23.
            //   0x1 (TRUE): Not Issued
            //   0x0 (FALSE): No Error
            __IO uint16_t  CMD_NOT_ISSUED_AUTO_CMD12: 1;

            __IO uint16_t  : 8;

        } S_AUTO_CMD_STAT;
    };


    union
    {
        __IO uint16_t HOST_CTRL2;     /*!< [0x003E] Host Control 2 Register     */
        struct
        {
            //UHS Mode/eMMC Speed Mode Select
            // These bits are used to select UHS mode in the SD mode of operation. In eMMC mode, these bits are used to select eMMC Speed mode.
            // UHS Mode (SD/UHS-II mode only):
            // 0x0: SDR12
            // 0x1: SDR25
            // 0x2: SDR50
            // 0x3: SDR104
            // 0x4: DDR50
            // 0x5: Reserved
            // 0x6: Reserved
            // 0x7: UHS-II
            //eMMC Speed Mode (eMMC mode only):
            // 0x0: Legacy
            // 0x1: High Speed SDR
            // 0x2: Reserved
            // 0x3: HS200
            // 0x4: High Speed DDR
            // 0x5: Reserved
            // 0x6: Reserved
            // 0x7: HS400
            //  Note: This Host Controller not supports DDR50 and UHS-II mode(SD/UHS-II mode only), please do not set this bit to 0x4 and 0x7.
            //  Note: This Host Controller not supports High Speed DDR and HS400 mode(eMMC mode only), please do not set this bit to 0x4 and 0x7.
            __IO uint16_t  UHS_MODE_SEL: 3;

            // SIGNALING_EN 1.8V Signaling Enable
            // This bit controls voltage regulator for I/O cell in UHS-I/eMMC speed modes. Setting this bit from 0 to 1 starts changing the signal voltage from 3.3V to 1.8V.
            // Host Controller clears this bit if switching to 1.8 signaling fails. The value is reflected on the uhs1_swvolt_en pin.
            // Note: This bit must be set for all UHS-I speed modes (SDR12/SDR25/SDR50/SDR104/DDR50).
            __IO uint16_t  SIGNALING_EN: 1;

            // DRV_STRENGTH_SEL Driver Strength Select
            // This bit is used to select the Host Controller output driver in 1.8V signaling UHS-I/eMMC speed modes.
            // The bit depends on setting of Preset Value Enable. The value is reflected on the uhs1_drv_sth pin.
            __IO uint16_t  DRV_STRENGTH_SEL: 2;

            // EXEC_TUNING  Execute Tuning
            // This bit is set to 1 to start the tuning procedure in UHS-I/eMMC speed modes and this bit is automatically cleared when tuning procedure is completed.
            __IO uint16_t  EXEC_TUNING: 1;

            // SAMPLE_CLK_SEL   Sampling Clock Select
            // This bit is used by the Host Controller to select the sampling clock in SD/eMMC mode to receive CMD and DAT.
            // This bit is set by the tuning procedure and is valid after the completion of tuning (when Execute Tuning is cleared).
            // Setting this bit to 1 means that tuning is completed successfully and setting this bit to 0 means that tuning has failed.
            // The value is reflected on the sample_cclk_sel pin.
            //   0x0 (FALSE): Fixed clock is used to sample data
            //   0x1 (TRUE): Tuned clock is used to sample data
            __IO uint16_t  SAMPLE_CLK_SEL: 1;

            // UHS2_IF_ENABLE   UHS-II Interface Enable
            // This bit is used to enable the UHS-II Interface. The value is reflected on the uhs2_if_en pin.
            //   0x0 (FALSE): SD/eMMC Interface Enabled
            //   0x1 (TRUE): UHS-II Interface Enabled
            // Note: This Host Controller not supports UHS-II mode, please do not set this bit to 0x1.
            __IO uint16_t  UHS2_IF_ENABLE: 1;

            __IO uint16_t  : 1;

            // ADMA2_LEN_MODE   ADMA2 Length Mode
            // This bit selects ADMA2 Length mode to be either 16-bit or 26-bit.
            //   0x0 (FALSE): 16-bit Data Length Mode
            //   0x1 (TRUE): 26-bit Data Length Mode
            // RSVD_9   This bit of the HOST_CTRL2_R register is reserved and always returns 0.
            __IO uint16_t  ADMA2_LEN_MODE: 1;

            // CMD23_ENABLE CMD23 Enable
            // If the card supports CMD23, this bit is set to 1. This bit is used to select Auto CMD23 or Auto CMD12 for ADMA3 data transfer.
            //   0x0 (FALSE): Auto CMD23 is disabled
            //   0x1 (TRUE): Auto CMD23 is enabled
            __IO uint16_t  CMD23_ENABLE: 1;

            // HOST_VER4_ENABLE Host Version 4 Enable
            // This bit selects either Version 3.00 compatible mode or Version 4 mode.
            // Functions of following fields are modified for Host Version 4 mode:
            //   SDMA Address: SDMA uses ADMA System Address (05Fh-058h) instead of SDMA System Address register (003h-000h)
            //   ADMA2/ADMA3 selection: ADMA3 is selected by DMA select in Host Control 1 register
            //   64-bit ADMA Descriptor Size: 128-bit descriptor is used instead of 96-bit descriptor when 64-bit Addressing is set to 1
            //   Selection of 32-bit/64-bit System Addressing: Either 32-bit or 64-bit system addressing is selected by 64-bit Addressing bit in this register
            //   32-bit Block Count: SDMA System Address register (003h-000h) is modified to 32-bit Block Count register
            // Note: It is recommended not to program ADMA3 Integrated Descriptor Address registers while operating in Host version less than 4 mode (Host Version 4 Enable = 0).
            //   0x0 (FALSE): Version 3.00 compatible mode
            //   0x1 (TRUE): Version 4 mode
            __IO uint16_t  HOST_VER4_ENABLE: 1;

            // ADDRESSING   64-bit Addressing
            // This bit is effective when Host Version 4 Enable is set to 1.
            //   0x0 (FALSE): 32 bits addressing
            //   0x1 (TRUE): 64 bits addressing
            __IO uint16_t  ADDRESSING: 1;

            // ASYNC_INT_ENABLE Asynchronous Interrupt Enable
            // This bit can be set if a card supports asynchronous interrupts and Asynchronous Interrupt Support is set to 1 in the Capabilities register
            //   0x0 (FALSE): Disabled
            //   0x1 (TRUE): Enabled
            __IO uint16_t  ASYNC_INT_ENABLE: 1;

            // PRESET_VAL_ENABLE    Preset Value Enable
            // This bit enables automatic selection of SDCLK frequency and Driver strength Preset Value registers.
            // When Preset Value Enable is set, SDCLK frequency generation (Frequency Select and Clock Generator Select) and the driver strength selection are performed by the controller.
            // These values are selected from set of Preset Value registers based on selected speed mode.
            // Note: For more information, see the FAQ on Preset Register in the DWC_mshc Databook.
            //   0x0 (FALSE): SDCLK and Driver Strength are controlled by Host Driver
            //   0x1 (TRUE): Automatic Selection by Preset Value are Enabled
            __IO uint16_t  PRESET_VAL_ENABLE: 1;

        } S_HOST_CTRL2;
    };


    union
    {
        __I uint32_t CAPABILITIES1;     /*!< [0x0040] Capabilities 1 Register - 0 to 31     */
        struct
        {
            // TOUT_CLK_FREQ    Timeout Clock Frequency
            // This bit shows the base clock frequency used to detect Data Timeout Error. The Timeout Clock unit defines the unit of timeout clock frequency. It can be kHz or MHz.
            //   0x00 : Get information through another method
            //   0x01 : 1 kHz / 1 MHz
            //   0x02 : 2 kHz / 2 MHz
            //   0x03 : 3 kHz / 3 MHz
            //   ...........
            //   0x3F : 63 kHz / 63 MHz
            __IO uint32_t  TOUT_CLK_FREQ: 6;

            __IO uint32_t  : 1;

            // TOUT_CLK_UNIT    Timeout Clock Unit
            // This bit shows the unit of base clock frequency used to detect Data Timeout Error.
            //   0x0 ( kHz): kHz
            //   0x1 ( MHz): MHz
            // RSVD_6   This bit of the CAPABILITIES1_R register is reserved and always returns 0.
            __IO uint32_t  TOUT_CLK_UNIT: 1;

            // BASE_CLK_FREQ    Base Clock Frequency for SD clock
            // These bits indicate the base (maximum) clock frequency for the SD Clock. The definition of these bits depend on the Host Controller Version.
            // 6-Bit Base Clock Frequency: This mode is supported by the Host Controller version 1.00 and 2.00. The upper 2 bits are not effective and are always 0. The unit values are 1 MHz. The supported clock range is 10 MHz to 63 MHz.
            //   0x00 : Get information through another method
            //   0x01 : 1 MHz
            //   0x02 : 2 MHz
            //   .............
            //   0x3F : 63 MHz
            //   0x40-0xFF : Not Supported
            // 8-Bit Base Clock Frequency: This mode is supported by the Host Controller version 3.00. The unit values are 1 MHz. The supported clock range is 10 MHz to 255 MHz.
            //   0x00 : Get information through another method
            //   0x01 : 1 MHz
            //   0x02 : 2 MHz
            //   ............
            //   0xFF : 255 MHz
            // If the frequency is 16.5 MHz, the larger value is set to 0001001b (17 MHz) because the Host Driver uses this value to calculate the clock divider value and it does not exceed the upper limit of the SD Clock frequency. If these bits are all 0, the Host system has to get information using a different method.
            __IO uint32_t  BASE_CLK_FREQ: 8;

            // MAX_BLK_LEN  Maximum Block Length
            // This bit indicates the maximum block size that the Host driver can read and write to the buffer in the Host Controller. The buffer transfers this block size without wait cycles. The transfer block length is always 512 bytes for the SD Memory irrespective of this bit
            //   0x0 (ZERO): 512 Byte
            //   0x1 (ONE): 1024 Byte
            //   0x2 (TWO): 2048 Byte
            //   0x3 (THREE): Reserved
            __IO uint32_t  MAX_BLK_LEN: 2;

            // Embedded_8_BIT   8-bit Support for Embedded Device
            // This bit indicates whether the Host Controller is capable of using an 8-bit bus width mode. This bit is not effective when the Slot Type is set to 10b.
            //   0x0 (FALSE): 8-bit Bus Width not Supported
            //   0x1 (TRUE): 8-bit Bus Width Supported
            __IO uint32_t  Embedded_8_BIT: 1;

            // ADMA2_SUPPORT    ADMA2 Support
            // This bit indicates whether the Host Controller is capable of using ADMA2.
            //   0x0 (FALSE): ADMA2 not Supported
            //   0x1 (TRUE): ADMA2 Supported
            __IO uint32_t  ADMA2_SUPPORT: 1;

            __IO uint32_t  : 1;

            // HIGH_SPEED_SUPPORT   High Speed Support
            // This bit indicates whether the Host Controller and the Host System supports High Speed mode and they can supply the SD Clock frequency from 25 MHz to 50 MHz.
            //   0x0 (FALSE): High Speed not Supported
            //   0x1 (TRUE): High Speed Supported
            // RSVD_20  This bit of the CAPABILITIES1_R is a reserved and always returns 0.
            __IO uint32_t  HIGH_SPEED_SUPPORT: 1;

            // SDMA_SUPPORT SDMA Support
            // This bit indicates whether the Host Controller is capable of using SDMA to transfer data between the system memory and the Host Controller directly.
            //   0x0 (FALSE): SDMA not Supported
            //   0x1 (TRUE): SDMA Supported
            __IO uint32_t  SDMA_SUPPORT: 1;

            // SUS_RES_SUPPORT  Suspense/Resume Support
            // This bit indicates whether the Host Controller supports Suspend/Resume functionality. If this bit is 0, the Host Driver does not issue either Suspend or Resume commands because the Suspend and Resume mechanism is not supported.
            //   0x0 (FALSE): Not Supported
            //   0x1 (TRUE): Supported
            __IO uint32_t  SUS_RES_SUPPORT: 1;

            // VOLT_33  Voltage Support for 3.3V
            //   0x0 (FALSE): 3.3V Not Supported
            //   0x1 (TRUE): 3.3V Supported
            __IO uint32_t  VOLT_33: 1;

            // VOLT_30  Voltage Support for SD 3.0V or Embedded 1.2V
            //   0x0 (FALSE): SD 3.0V or Embedded 1.2V Not Supported
            //   0x1 (TRUE): SD 3.0V or Embedded Supported
            __IO uint32_t  VOLT_30: 1;

            // VOLT_18  Voltage Support for 1.8V
            //   0x0 (FALSE): 1.8V Not Supported
            //   0x1 (TRUE): 1.8V Supported
            __IO uint32_t  VOLT_18: 1;

            // SYS_ADDR_64_V4   64-bit System Address Support for V4
            // This bit sets the Host Controller to support 64-bit System Addressing of V4 mode.
            // When this bit is set to 1, full or part of 64-bit address must be used to decode the Host Controller Registers so that Host Controller Registers can be placed above system memory area.
            // 64-bit address decode of Host Controller registers is effective regardless of setting to 64-bit Addressing in Host Control 2.
            // If this bit is set to 1, 64-bit DMA Addressing for version 4 is enabled by setting Host Version 4 Enable (HOST_VER4_ENABLE = 1) and by setting 64-bit Addressing (ADDRESSING =1) in the Host Control 2 register. SDMA can be used and ADMA2 uses 128-bit Descriptor.
            //   0x0 (FALSE): 64-bit System Address for V4 is Not Supported
            //   0x1 (TRUE): 64-bit System Address for V4 is Supported
            __IO uint32_t  SYS_ADDR_64_V4: 1;

            // SYS_ADDR_64_V3   64-bit System Address Support for V3
            // This bit sets the Host controller to support 64-bit System Addressing of V3 mode.
            // SDMA cannot be used in 64-bit Addressing in Version 3 Mode.
            // If this bit is set to 1, 64-bit ADMA2 with using 96-bit Descriptor can be enabled by setting Host Version 4 Enable (HOST_VER4_ENABLE = 0) and DMA select (DMA_SEL = 11b).
            //   0x0 (FALSE): 64-bit System Address for V3 is Not Supported
            //   0x1 (TRUE): 64-bit System Address for V3 is Supported
            __IO uint32_t  SYS_ADDR_64_V3: 1;

            // ASYNC_INT_SUPPORT    Asynchronous Interrupt Support
            //   0x0 (FALSE): Asynchronous Interrupt Not Supported
            //   0x1 (TRUE): Asynchronous Interrupt Supported
            // Note: SD Mode only.
            __IO uint32_t  ASYNC_INT_SUPPORT: 1;

            // SLOT_TYPE_R  Slot Type
            // These bits indicate usage of a slot by a specific Host System.
            //   0x0 (REMOVABLE_SLOT): Removable Card Slot
            //   0x1 (EMBEDDED_SLOT): Embedded Slot for one Device
            //   0x2 (SHARED_SLOT): Shared Bus Slot (SD mode)
            //   0x3 (UHS2_EMBEDDED_SLOT): UHS-II Multiple Embedded Devices
            __IO uint32_t  SLOT_TYPE_R: 2;

        } S_CAPABILITIES1;
    };


    union
    {
        __I uint32_t CAPABILITIES2;     /*!< [0x0044] Capabilities 2 Register - 32 to 63     */
        struct
        {
            // SDR50_SUPPORT    SDR50 Support
            // This bit indicates that SDR50 is supported. The bit 13 (USE_TUNING_SDR50) indicates whether SDR50 requires tuning or not.
            // Note: UHS-I only.
            __IO uint32_t  SDR50_SUPPORT: 1;

            // SDR104_SUPPORT   SDR104 Support
            // This bit mentions that SDR104 requires tuning.
            // Note: UHS-I only.
            __IO uint32_t  SDR104_SUPPORT: 1;

            // DDR50_SUPPORT    DDR50 Support
            // Note: UHS-I only.
            __IO uint32_t  DDR50_SUPPORT: 1;

            // UHS2_SUPPORT UHS-II Support
            // This bit indicates whether Host Controller supports UHS-II.
            // Note: UHS-I only.
            __IO uint32_t  UHS2_SUPPORT: 1;

            // DRV_TYPEA    Driver Type A Support
            // This bit indicates support of Driver Type A for 1.8 Signaling.
            // Note: UHS-I only.
            __IO uint32_t  DRV_TYPEA: 1;

            // DRV_TYPEC    Driver Type C Support
            // This bit indicates support of Driver Type C for 1.8 Signaling.
            // Note: UHS-I only.
            __IO uint32_t  DRV_TYPEC: 1;

            // DRV_TYPED    Driver Type D Support
            // This bit indicates support of Driver Type D for 1.8 Signaling.
            // Note: UHS-I only.
            __IO uint32_t  DRV_TYPED: 1;
            __IO uint32_t  : 1;

            // RETUNE_CNT   Timer Count for Re-Tuning
            //   0x0: Re-Tuning Timer disabled
            //   0x1: 1 seconds
            //   0x2: 2 seconds
            //   0x3: 4 seconds
            //   ........
            //   0xB: 1024 seconds
            //   0xC: Reserved
            //   0xD: Reserved
            //   0xE: Reserved
            //   0xF: Get information from other source
            // Note: UHS-I only.
            __IO uint32_t  RETUNE_CNT: 4;

            __IO uint32_t  : 1;

            // USE_TUNING_SDR50 Use Tuning for SDR50
            // Note: UHS-I only.
            // RSVD_44  This bit (RSVD_44) of the CAPABILITIES2_R register is reserved and always returns 0.
            __IO uint32_t  USE_TUNING_SDR50: 1;

            // RE_TUNING_MODES  Re-Tuning Modes
            // These bits select the re-tuning method and limit the maximum data length.
            // Note: UHS-I only.
            __IO uint32_t  RE_TUNING_MODES: 2;

            // CLK_MUL  Clock Multiplier
            // These bits indicate the clock multiplier of the programmable clock generator. Setting these bits to 0 means that the Host Controller does not support a programmable clock generator.
            //   0x0: Clock Multiplier is not Supported
            //   0x1: Clock Multiplier M = 2.
            //   0x2: Clock Multiplier M = 3.
            //   .........
            //   0xFF: Clock Multiplier M = 256.
            __IO uint32_t  CLK_MUL: 8;

            __IO uint32_t  : 4;

            // VDD2_18V_SUPPORT 1.8V VDD2 Support
            // This bit indicates support of VDD2 for the Host System.
            //
            //   0x0 (FALSE): 1.8V VDD2 is not Supported
            //   0x1 (TRUE): 1.8V VDD2 is Supported
            __IO uint32_t  VDD2_18V_SUPPORT: 1;

            __IO uint32_t  : 3;

        } S_CAPABILITIES2;
    };


    union
    {
        __I uint32_t CURR_CAPABILITIES1;     /*!< [0x0048] Maximum Current Capabilities Register - 0 to 31     */
        struct
        {
            // MAX_CUR_33V  Maximum Current for 3.3V
            // This bit specifies the Maximum Current for 3.3V VDD1 power supply for the card.
            //   0: Get information through another method
            //   1: 4mA
            //   2: 8mA
            //   3: 13mA
            //   .......
            //   255: 1020mA
            __I uint32_t  MAX_CUR_33V: 8;


            // MAX_CUR_30V  Maximum Current for 3.0V
            // This bit specifies the Maximum Current for 3.0V VDD1 power supply for the card.
            //   0: Get information through another method
            //   1: 4mA
            //   2: 8mA
            //   3: 13mA
            //   .......
            //   255: 1020mA
            __I uint32_t  MAX_CUR_30V: 8;

            // MAX_CUR_18V  Maximum Current for 1.8V
            // This bit specifies the Maximum Current for 1.8V VDD1 power supply for the card.
            //   0: Get information through another method
            //   1: 4mA
            //   2: 8mA
            //   3: 13mA
            //   .......
            //   255: 1020mA
            __I uint32_t  MAX_CUR_18V: 8;

            __I uint32_t  : 8;

        } S_CURR_CAPABILITIES1;
    };


    union
    {
        __I uint32_t CURR_CAPABILITIES2;     /*!< [0x004C] Maximum Current Capabilities Register - 32 to 63     */
        struct
        {
            // MAX_CUR_VDD2_18V Maximum Current for 1.8V VDD2
            // This bit specifies the Maximum Current for 1.8V VDD2 power supply for the UHS-II card.
            //   0: Get information through another method
            //   1: 4mA
            //   2: 8mA
            //   3: 13mA
            //   .......
            //   255: 1020mA
            __I uint32_t  MAX_CUR_VDD2_18V: 8;

            __I uint32_t  : 24;
        } S_CURR_CAPABILITIES2;
    };


    union
    {
        __IO uint16_t FORCE_AUTO_CMD_STAT;     /*!< [0x0050] Force Event Register for Auto CMD Error Status register  */
        struct
        {
            // FORCE_AUTO_CMD12_NOT_EXEC    Force Event for Auto CMD12 Not Executed
            //   0x1 (TRUE): Auto CMD12 Not Executed Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD12_NOT_EXEC: 1;

            // FORCE_AUTO_CMD_TOUT_ERR  Force Event for Auto CMD Timeout Error
            //   0x1 (TRUE): Auto CMD Timeout Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD_TOUT_ERR: 1;

            // FORCE_AUTO_CMD_CRC_ERR   Force Event for Auto CMD CRC Error
            //   0x1 (TRUE): Auto CMD CRC Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD_CRC_ERR: 1;

            // FORCE_AUTO_CMD_EBIT_ERR  Force Event for Auto CMD End Bit Error
            //   0x1 (TRUE): Auto CMD End Bit Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD_EBIT_ERR: 1;

            // FORCE_AUTO_CMD_IDX_ERR   Force Event for Auto CMD Index Error
            //   0x1 (TRUE): Auto CMD Index Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD_IDX_ERR: 1;

            // FORCE_AUTO_CMD_RESP_ERR  Force Event for Auto CMD Response Error
            //   0x1 (TRUE): Auto CMD Response Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_AUTO_CMD_RESP_ERR: 1;

            __IO uint16_t  : 1;

            // FORCE_CMD_NOT_ISSUED_AUTO_CMD12  Force Event for Command Not Issued By Auto CMD12 Error
            //   0x1 (TRUE): Command Not Issued By Auto CMD12 Error Status is set
            //   0x0 (FALSE): Not Affected
            __IO uint16_t  FORCE_CMD_NOT_ISSUED_AUTO_CMD12: 1;

            __IO uint16_t  : 8;

        } S_FORCE_AUTO_CMD_STAT;
    };


    union
    {
        __IO uint16_t FORCE_ERROR_INT_STAT;     /*!< [0x0052] Force Event Register for Auto CMD Error Status register  */
        struct
        {
            // FORCE_CMD_TOUT_ERR   Force Event for Command Timeout Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Command Timeout Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_CMD_TOUT_ERR: 1;

            // FORCE_CMD_CRC_ERR    Force Event for Command CRC Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Command CRC Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_CMD_CRC_ERR: 1;

            // FORCE_CMD_END_BIT_ERR    Force Event for Command End Bit Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Command End Bit Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_CMD_END_BIT_ERR: 1;

            // FORCE_CMD_IDX_ERR    Force Event for Command Index Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Command Index Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_CMD_IDX_ERR: 1;

            // FORCE_DATA_TOUT_ERR  Force Event for Data Timeout Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Data Timeout Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_DATA_TOUT_ERR: 1;

            // FORCE_DATA_CRC_ERR   Force Event for Data CRC Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Data CRC Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_DATA_CRC_ERR: 1;

            // FORCE_DATA_END_BIT_ERR   Force Event for Data End Bit Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Data End Bit Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_DATA_END_BIT_ERR: 1;

            // FORCE_CUR_LMT_ERR    Force Event for Current Limit Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Current Limit Error Status is set
            __IO uint16_t  FORCE_CUR_LMT_ERR: 1;

            // FORCE_AUTO_CMD_ERR   Force Event for Auto CMD Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Auto CMD Error Status is set
            // Note: SD/eMMC Mode only.
            __IO uint16_t  FORCE_AUTO_CMD_ERR: 1;

            // FORCE_ADMA_ERR   Force Event for ADMA Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): ADMA Error Status is set
            __IO uint16_t  FORCE_ADMA_ERR: 1;

            // FORCE_TUNING_ERR Force Event for Tuning Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Tuning Error Status is set
            // Note: UHS-I Mode only.
            __IO uint16_t  FORCE_TUNING_ERR: 1;

            // FORCE_RESP_ERR   Force Event for Response Error
            //   0x0 (FALSE): Not Affected
            //   0x1 (TRUE): Response Error Status is set
            // Note: SD Mode only.
            __IO uint16_t  FORCE_RESP_ERR: 1;

            // FORCE_BOOT_ACK_ERR   Force Event for Boot Ack error
            // 0x0 (FALSE): Not Affected
            // 0x1 (TRUE): Boot ack Error Status is set
            __IO uint16_t  FORCE_BOOT_ACK_ERR: 1;

            // FORCE_VENDOR_ERR1    This bit (FORCE_VENDOR_ERR1) of the FORCE_ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  FORCE_VENDOR_ERR1: 1;

            // FORCE_VENDOR_ERR2    This bit (FORCE_VENDOR_ERR2) of the FORCE_ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  FORCE_VENDOR_ERR2: 1;

            // FORCE_VENDOR_ERR3    This bit (FORCE_VENDOR_ERR3) of the FORCE_ERROR_INT_STAT_R register is reserved and always returns 0.
            __IO uint16_t  FORCE_VENDOR_ERR3: 1;

        } S_FORCE_ERROR_INT_STAT;
    };


    union
    {
        __I uint8_t ADMA_ERR_STAT;     /*!< [0x0054] ADMA Error Status Register  */
        struct
        {
            // ADMA_ERR_STATES  ADMA Error States
            //   0x0 (ST_STOP): Stop DMA - SYS_ADR register points to a location next to the error descriptor
            //   0x1 (ST_FDS): Fetch Descriptor - SYS_ADR register points to the error descriptor
            //   0x2 (UNUSED): Never set this state
            //   0x3 (ST_TFR): Transfer Data - SYS_ADR register points to a location next to the error descriptor
            // These bits indicate the state of ADMA when an error occurs during ADMA data transfer.
            __I uint8_t  ADMA_ERR_STATES: 2;

            // ADMA_LEN_ERR ADMA Length Mismatch Error States
            //   0x0 (NO_ERR): No Error
            //   0x1 (ERROR): Error
            // This error occurs in the following instances:
            //   While the Block Count Enable is being set, the total data length specified by the Descriptor table is different from that specified by the Block Count and Block Length
            //   When the total data length cannot be divided by the block length
            __I uint8_t  ADMA_LEN_ERR: 1;

            __I uint8_t  : 5;

        } S_ADMA_ERR_STAT;
    };

    // ADMA_SA_LOW  ADMA System Address
    // These bits indicate the lower 32 bits of the ADMA system address.
    //   SDMA: If Host Version 4 Enable is set to 1, this register stores the system address of the data location
    //   ADMA2: This register stores the byte address of the executing command of the descriptor table
    //   ADMA3: This register is set by ADMA3. ADMA2 increments the address of this register that points to the next line, every time a Descriptor line is fetched.
    __IO uint32_t ADMA_SA_LOW;         /*!< [0x0058] ADMA System Address Register - Low  */

    __IO uint32_t RESERVED0[1];        /*!< [0x005C] Revered  */

    union
    {
        __I uint16_t PRESET_INIT;      /*!< [0x0060] Preset Value for Initialization  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when the Host Controller supports a programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate that the Driver strength is supported by 1.8V signaling bus speed modes. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_INIT;
    };


    union
    {
        __I uint16_t PRESET_DS;       /*!< [0x0062] Preset Value for Default Speed  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported by 1.8V signaling bus speed modes. This field is meaningless for the Default speed mode as it uses 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_DS;
    };


    union
    {
        __I uint16_t PRESET_HS;       /*!< [0x0064] Preset Value for High Speed  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported by 1.8V signaling bus speed modes. This field is meaningless for High speed mode as it uses 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_HS;
    };


    union
    {
        __I uint16_t PRESET_SDR12;      /*!< [0x0066] Preset Value for SDR12  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generato
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported for the SDR12 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_SDR12;
    };


    union
    {
        __I uint16_t PRESET_SDR25;      /*!< [0x0068] Preset Value for SDR25  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported for the SDR25 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_SDR25;
    };


    union
    {
        __I uint16_t PRESET_SDR50;      /*!< [0x006A] Preset Value for SDR50  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            // This bit is effective when Host Controller supports programmable clock generator
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported for the SDR12 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;
        } S_PRESET_SDR50;
    };


    union
    {
        __I uint16_t PRESET_SDR104;      /*!< [0x006C] Preset Value for SDR104  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate the Driver strength value supported for the SDR25 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_SDR104;
    };


    union
    {
        __I uint16_t PRESET_DDR50;        /*!< [0x006E] Preset Value for DDR50  */
        struct
        {

            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This bit is effective when Host Controller supports programmable clock generator.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate Driver strength value supported for SDR50 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_DDR50;
    };

    __IO uint32_t RESERVED2[1];           /*!< [0x0070] Revered */

    union
    {
        __I uint16_t PRESET_UHS2;        /*!< [0x0074] Preset Value for UHS-II  */
        struct
        {
            // FREQ_SEL_VAL SDCLK/RCLK Frequency Select Value
            // These bits specify a 10-bit preset value that must be set in the SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
            __I uint16_t  FREQ_SEL_VAL: 10;

            // CLK_GEN_SEL_VAL  Clock Generator Select Value
            //   0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
            //   0x1 (PROG): Programmable Clock Generator
            // This Host Controller not supports programmable clock generator, please do not set this bit to 0x1.
            __I uint16_t  CLK_GEN_SEL_VAL: 1;

            __I uint16_t  : 3;

            // DRV_SEL_VAL  Driver Strength Select Value
            //   0x0 (TYPEB): Driver Type B is selected
            //   0x1 (TYPEA): Driver Type A is selected
            //   0x2 (TYPEC): Driver Type C is selected
            //   0x3 (TYPED): Driver Type D is selected
            // These bits indicate Driver strength value supported for SDR104 bus speed mode. These bits are meaningless for 3.3V signaling.
            __I uint16_t  DRV_SEL_VAL: 2;

        } S_PRESET_UHS2;
    };

    __IO uint16_t RESERVED3[1];           /*!< [0x0076] Revered */
    __IO uint32_t RESERVED4[27];          /*!< [0x0078] Revered */
    __IO uint16_t RESERVED5[1];           /*!< [0x00E4] Revered */

    union
    {
        __I uint16_t P_EMBEDDED_CNTRL;    /*!< [0x00E6] Pointer for Embedded Control */
        struct
        {
            // Offset Address of Embedded Control register
            __I uint16_t REG_OFFSET_ADDR: 12;

            __I uint16_t  : 4;

        } S_P_EMBEDDED_CNTRL;
    };

    union
    {
        __I uint16_t P_VENDOR_SPECIFIC_AREA;  /*!< [0x00E8] Pointer for Vendor Specific Area 1 */
        struct
        {
            // Base offset Address for Vendor-Specific registers
            __I uint16_t REG_OFFSET_ADDR: 12;

            __I uint16_t  : 4;

        } S_P_VENDOR_SPECIFIC_AREA;
    };

    // Base offset Address for Command Queuing registers
    __I uint16_t P_VENDOR2_SPECIFIC_AREA;      /*!< [0x00EA] Pointer for Vendor Specific Area 2 */

    __IO uint32_t RESERVED6[4];                /*!< [0x00EC] Revered */

    union
    {
        __I uint16_t SLOT_INTR_STATUS;        /*!< [0x00FC] Slot Interrupt Status Register */
        struct
        {
            // Interrupt signal for each Slot
            // These status bits indicate the logical OR of Interrupt signal and Wakeup signal for each slot. A maximum of 8 slots can be defined.
            // If one interrupt signal is associated with multiple slots, the Host Driver can identify the interrupt that is generated by reading these bits.
            // By a power on reset or by setting Software Reset For All bit, the interrupt signals are de-asserted and this status reads 00h.
            //   Bit 00: Slot 1
            //   Bit 01: Slot 2
            //   Bit 02: Slot 3
            //   ..........
            //   ..........
            //   Bit 07: Slot 8
            // Note: MSHC Host Controller support single card slot. This register shall always return 0.
            __I uint16_t INTR_SLOT: 8;

            __I uint16_t : 8;

        } S_SLOT_INTR_STATUS;
    };


    union
    {
        __I uint16_t HOST_CNTRL_VERS;         /*!< [0x00FE] Host Controller Version */
        struct
        {
            // SPEC_VERSION_NUM Specification Version Number
            //   0x0 (VER_1_00): SD Host Controller Specification Version 1.00
            //   0x1 (VER_2_00): SD Host Controller Specification Version 2.00
            //   0x2 (VER_3_00): SD Host Controller Specification Version 3.00
            //   0x3 (VER_4_00): SD Host Controller Specification Version 4.00
            //   0x4 (VER_4_10): SD Host Controller Specification Version 4.10
            //   0x5 (VER_4_20): SD Host Controller Specification Version 4.20
            // These bits indicate the Host controller specification version. The upper and lower 4-bits indicate the version. Values 0x06-0xFF are reserved.
            __I uint16_t SPEC_VERSION_NUM: 8;

            // VENDOR_VERSION_NUM   Vendor Version Number
            // This field is reserved for the vendor version number. Host Driver must not use this status.
            __I uint16_t VENDOR_VERSION_NUM: 8;

        } S_HOST_CNTRL_VERS;
    };

    __IO uint32_t RESERVED7[33];              /*!< [0x0100] Revered */

    union
    {
        __I uint32_t CQCAP ;                  /*!< [0x00184] Command Queuing Capabilities register */
        struct
        {
            // ITCFVAL  Internal Timer Clock Frequency Value
            //   0x0 (CLK_1 kHz): 1 kHz clock
            //   0x1 (CLK_10 kHz): 10 kHz clock
            //   0x2 (CLK_100 kHz): 100 kHz clock
            //   0x3 (CLK_1 MHz): 1 MHz clock
            //   0x4 (CLK_10 MHz): 10 MHz clock
            // This field scales the frequency of the timer clock provided by ITCFMUL. The Final clock frequency of actual timer clock is calculated as ITCFVAL* ITCFMUL.
            __I uint32_t  ITCFVAL: 10 ;

            __I uint32_t  : 2 ;

            // ITCFMUL  Internal Timer Clock Frequency Multiplier
            // This field indicates the frequency of the clock used for interrupt coalescing timer and for determining the SQS polling period.
            // See ITCFVAL definition for details. Values 0x5 to 0xF are reserved.
            __I uint32_t  ITCFMUL: 4 ;

            __I uint32_t  : 12 ;

            // CRYPTO_SUPPORT   Crypto Support
            //   0x0 (FALSE): Crypto not Supported
            //   0x1 (TRUE): Crypto Supported
            // This bit indicates whether the Host Controller supports cryptographic operations.
            __I uint32_t  CRYPTO_SUPPORT: 1 ;

            __I uint32_t  : 3 ;

        } S_CQCAP;
    };


    __IO uint32_t RESERVED8[222];             /*!< [0x0188] Revered */

    // MSHC_VER_ID  Current release number
    // This field indicates the Synopsys DesignWare Cores DWC_mshc/DWC_mshc_lite current release number that is read by an application.
    // An application reading this register in conjunction with the MSHC_VER_TYPE_R register, gathers details of the current release.
    __I uint32_t MSHC_VER_ID;                 /*!< [0x0500] MSHC version */

    // MSHC_VER_TYPE    Current release type
    // This field indicates the Synopsys DesignWare Cores DWC_mshc/DWC_mshc_lite current release type that is read by an application.
    // An application reading this register in conjunction with the MSHC_VER_ID_R register, gathers details of the current release.
    __I uint32_t MSHC_VER_TYPE;               /*!< [0x0504] MSHC version type  */

    union
    {
        __IO uint16_t MSHC_CTRL;              /*!< [0x0508] MSHC Control register */
        struct
        {
            // CMD_CONFLICT_CHECK   Command conflict check
            //   0x0 (DISABLE_CMD_CONFLICT_CHK): Disable command conflict check
            //   0x1 (CMD_CONFLICT_CHK_LAT1): Check for command conflict after 1 card clock cycle
            // This bit enables command conflict check.
            // Note: DWC_mshc controller monitors the CMD line whenever a command is issued and checks whether the value driven on sd_cmd_out matches the value
            // on sd_cmd_in at next subsequent edge of cclk_tx to determine command conflict error.
            // This bit is cleared only if the feed back delay (including I/O Pad delay) is more than (t_card_clk_period - t_setup), where t_setup is the setup time of a flop in DWC_mshc.
            // The I/O pad delay is consistent across CMD and DATA lines, and it is within the value:
            // (2*t_card_clk_period - t_setup)
            __IO uint8_t CMD_CONFLICT_CHECK: 1;

            __IO uint8_t : 3;

            // SW_CG_DIS    Internal clock gating disable control
            //   0x0 (ENABLE): Internal clock gates are active and clock gating is controlled internally
            //   0x1 (DISABLE): Internal clock gating is disabled, clocks are not gated internally
            // This bit must be used to disable IP's internal clock gating when required. when disabled clocks are not gated.
            // Clocks to the core (except hclk) must be stopped when programming this bit.
            __IO uint8_t SW_CG_DIS: 1;

            __IO uint8_t : 3;

        } S_MSHC_CTRL;
    };

    __IO uint16_t RESERVED9[1];                /*!< [0x050A] Revered */
    __IO uint32_t RESERVED10[1];               /*!< [0x050C] Revered */

    union
    {
        __IO uint16_t MBIU_CTRL;              /*!< [0x0510] MBIU Control register */
        struct
        {
            // UNDEFL_INCR_EN   Undefined INCR Burst
            //   0x0 (FALSE): Undefined INCR type burst is the least preferred burst on AHB Master I/F
            //   0x1 (TRUE): Undefined INCR type burst is the most preferred burst on AHB Master I/F
            // Controls generation of undefined length INCR transfer on Master interface.
            __IO uint8_t UNDEFL_INCR_EN: 1;

            // BURST_INCR4_EN   INCR4 Burst
            //   0x0 (FALSE): AHB INCR4 burst type is not generated on Master I/F
            //   0x1 (TRUE): AHB INCR4 burst type can be generated on Master I/F
            // Controls generation of INCR4 transfers on Master interface.
            __IO uint8_t BURST_INCR4_EN: 1;

            // BURST_INCR8_EN   INCR8 Burst
            //   0x0 (FALSE): AHB INCR8 burst type is not generated on Master I/F
            //   0x1 (TRUE): AHB INCR8 burst type can be generated on Master I/F
            // Controls generation of INCR8 transfers on Master interface.
            __IO uint8_t BURST_INCR8_EN: 1;

            // BURST_INCR16_EN  INCR16 Burst
            //   0x0 (FALSE): AHB INCR16 burst type is not generated on Master I/F
            //   0x1 (TRUE): AHB INCR16 burst type can be generated on Master I/F
            // Controls generation of INCR16 transfers on Master interface.
            __IO uint8_t BURST_INCR16_EN: 1;

            __IO uint8_t : 4;

        } S_MBIU_CTRL;
    };

    __IO uint16_t RESERVED11[1];               /*!< [0x0512] Revered */

    __IO uint32_t RESERVED12[6];               /*!< [0x0514] Revered */

    union
    {
        __IO uint16_t EMMC_CTRL;              /*!< [0x052C] eMMC Control register */
        struct
        {
            // CARD_IS_EMMC eMMC Card present
            //   0x1 (EMMC_CARD): Card connected to MSHC is an eMMC card
            //   0x0 (NON_EMMC_CARD): Card connected to MSHC is a non-eMMC card
            // This bit indicates the type of card connected. An application program this bit based on the card connected to MSHC.
            __IO uint16_t CARD_IS_EMMC: 1;

            // DISABLE_DATA_CRC_CHK Disable Data CRC Check
            //   0x1 (DISABLE): DATA CRC check is disabled
            //   0x0 (ENABLE): DATA CRC check is enabled
            // This bit controls masking of CRC16 error for Card Write in eMMC mode. This is useful in bus testing (CMD19) for an eMMC device. In bus testing, an eMMC card does not send CRC status for a block, which may generate CRC error. This CRC error can be masked using this bit during bus testing.
            __IO uint16_t DISABLE_DATA_CRC_CHK: 1;

            // EMMC_RST_N   EMMC Device Reset signal control
            //   0x1 (RST_DEASSERT): Reset to eMMC device is deasserted
            //   0x0 (RST_ASSERT): Reset to eMMC device asserted (active low)
            // This register field controls the sd_rst_n output of DWC_mshc
            __IO uint16_t EMMC_RST_N: 1;

            // EMMC_RST_N_OE    Output Enable control for EMMC Device Reset signal PAD control
            //   0x1 (ENABLE): sd_rst_n_oe is 1
            //   0x0 (DISABLE): sd_rst_n_oe is 0
            // This field drived sd_rst_n_oe output of DWC_mshc
            __IO uint16_t EMMC_RST_N_OE: 1;

            __IO uint16_t : 12;
        } S_EMMC_CTRL;
    };


    union
    {
        __IO uint16_t BOOT_CTRL;              /*!< [0x052E] eMMC Boot Control register */
        struct
        {
            // MAN_BOOT_EN  Mandatory Boot Enable
            // This bit is used to initiate the mandatory boot operation. The application sets this bit along with VALIDATE_BOOT bit. Writing 0 is ignored.
            // The DWC_mshc clears this bit after the boot transfer is completed or terminated.
            //   0x1 (MAN_BOOT_EN): Mandatory boot enable
            //   0x0 (MAN_BOOT_DIS): Mandatory boot disable
            // Testable: read only
            __IO uint16_t MAN_BOOT_EN: 1;

            __IO uint16_t : 6;

            // VALIDATE_BOOT    Validate Mandatory Boot Enable bit
            //   0x1 (TRUE): Validate Mandatory boot enable bit
            //   0x0 (FALSE): Ignore Mandatory boot Enable bit
            // This bit is used to validate the MAN_BOOT_EN bit.
            __IO uint16_t VALIDATE_BOOT: 1;

            // BOOT_ACK_ENABLE  Boot Acknowledge Enable
            //   0x1 (TRUE): Boot Ack enable
            //   0x0 (FALSE): Boot Ack disable
            // When this bit set, DWC_mshc checks for boot acknowledge start pattern of 0-1-0 during boot operation.
            // This bit is applicable for both mandatory and alternate boot mode.
            __IO uint16_t BOOT_ACK_ENABLE: 1;

            __IO uint16_t : 3;

            // BOOT_TOUT_CNT    Boot Ack Timeout Counter Value
            // This value determines the interval by which boot ack timeout (50 ms) is detected when boot ack is expected during boot operation.
            //   0xF : Reserved
            //   0xE : TMCLK x 2^27
            //   .. - ............
            //   0x1 : TMCLK x 2^14
            //   0x0 : TMCLK x 2^13
            __IO uint16_t BOOT_TOUT_CNT: 4;

        } S_BOOT_CTRL;
    };


    __IO uint32_t RESERVED13[4];             /*!< [0x0530] Revered */

    union
    {
        __IO uint32_t AT_CTRL;                /*!< [0x0540] Tuning and Auto-tuning control register */
        struct
        {
            // AT_EN    Setting this bit enables Auto tuning engine This bit is enabled by default when core is configured with mode3 retuning support Clear this bit to 0
            // when core is configured to have Mode3 re-tuning but SW wishes to disable mode3 re-tuning
            // This field should be programmed only when CLK_CTRL_R.SD_CLK_EN is 0.
            //   0x1 (AT_ENABLE): AutoTuning is enabled
            //   0x0 (AT_DISABLE): AutoTuning is disabled
            __IO uint32_t AT_EN: 1;

            // CI_SEL   Select the interval when the corrected center phase select code can be driven on tuning_cclk_sel output.
            //   0x0 (WHEN_IN_BLK_GAP): Driven in block gap interval
            //   0x1 (WHEN_IN_IDLE): Driven at the end of the transfer
            __IO uint32_t CI_SEL: 1;

            // SWIN_TH_EN   Sampling window Threshold enable
            // Selects the tuning mode
            // Field should be programmed only when SAMPLE_CLK_SEL is '0'
            //   0x1 (THRESHOLD_MODE): Tuning engine selects the first complete sampling window that meets the threshold set by SWIN_TH_VAL field
            //   0x0 (LARGEST_WIN_MODE): Tuning engine sweeps all taps and settles at the largest window
            __IO uint32_t SWIN_TH_EN: 1;

            // RPT_TUNE_ERR Framing errors are not generated when executing tuning. This debug bit allows users to report these errors.
            //   0x1 (DEBUG_ERRORS): Debug mode for reporting framing errors
            //   0x0 (ERRORS_DISABLED): Default mode where as per SD-HCI no errors are reported.
            __IO uint32_t RPT_TUNE_ERR: 1;

            // SW_TUNE_EN   Enable software-managed tuning flow
            //   0x1 (SW_TUNING_ENABLE): Software-managed tuning enabled. AT_STAT_R.CENTER_PH_CODE Field is now writable.
            //   0x0 (SW_TUNING_DISABLE): Software-managed tuning disabled.
            __IO uint32_t SW_TUNE_EN: 1;

            __IO uint32_t : 3;

            // WIN_EDGE_SEL This field sets the phase for Left and Right edges for drift monitoring [Left edge offset + Right edge offset] must not be less than total taps of delayLine.
            //   0x0: User selection disabled. Tuning calculated edges are used.
            //   0x1: Right edge Phase is center + 2 stages, Left edge Phase is center - 2 stages.
            //   0x2: Right edge Phase is center + 3 stages, Left edge Phase is center - 3 stages.
            //   ...
            //   0xF: Right edge Phase is center + 16 stages, Left edge Phase is center - 16 stages.
            __IO uint32_t WIN_EDGE_SEL: 4;

            __IO uint32_t : 4;

            // TUNE_CLK_STOP_EN Clock stopping control for Tuning and auto-tuning circuit
            // When enabled, clock gate control output of DWC_mshc (clk2card_on) is pulled low before changing phase select codes on tuning_cclk_sel and autotuning_cclk_sel.
            // This effectively stops the Device/Card clock, cclk_rx and also drift_cclk_rx. Changing phase code when clocks are stopped ensures glitch free phase switching.
            // Set this bit to 0 if the PHY or delayline can guarantee glitch free switching.
            //   0x1 (ENABLE_CLK_STOPPING): Clocks stopped during phase code change
            //   0x0 (DISABLE_CLK_STOPPING): Clocks not stopped. PHY ensures glitch free phase switching.
            __IO uint32_t TUNE_CLK_STOP_EN: 1;

            // PRE_CHANGE_DLY   Maximum Latency specification between cclk_tx and cclk_rx
            //   0x0 (LATENCY_LT_1): Less than 1-cycle latency
            //   0x1 (LATENCY_LT_2): Less than 2-cycle latency
            //   0x2 (LATENCY_LT_3): Less than 3-cycle latency
            //   0x3 (LATENCY_LT_4): Less than 4-cycle latency
            __IO uint32_t PRE_CHANGE_DLY: 2;

            // POST_CHANGE_DLY  Time taken for phase switching and stable clock output
            // Specifies the maximum time (in terms of cclk cycles) that the delay line can take to switch its output phase after a change in tuning_cclk_sel or autotuning_cclk_sel.
            //   0x0 (LATENCY_LT_1): Less than 1-cycle latency
            //   0x1 (LATENCY_LT_2): Less than 2-cycle latency
            //   0x2 (LATENCY_LT_3): Less than 3-cycle latency
            //   0x3 (LATENCY_LT_4): Less than 4-cycle latency
            __IO uint32_t POST_CHANGE_DLY: 2;

            __IO uint32_t : 3;

            // SWIN_TH_VAL  Sampling window threshold value setting
            // The maximum value that can be set here depends on the length of delayline used for tuning. A delayLine with 128 taps can use values from 0x0 to 0x7F.
            // This field is valid only when SWIN_TH_EN is '1'. Should be programmed only when SAMPLE_CLK_SEL is '0'
            //   0x0 : Threshold values is 0x1, windows of length 1 tap and above can be selected as sampling window.
            //   0x1 : Threshold values is 0x2, windows of length 2 taps and above can be selected as sampling window.
            //   0x2 : Threshold values is 0x1, windows of length 3 taps and above can be selected as sampling window.
            //   ........
            //   0x7F : Threshold values is 0x1, windows of length 127 taps and above can be selected as sampling window.
            __IO uint32_t SWIN_TH_VAL: 4;

            __IO uint32_t : 4;

        } S_AT_CTRL;
    };


    union
    {
        __IO uint32_t AT_STAT;                /*!< [0x0544] Tuning and Auto-tuning status register */
        struct
        {
            // CENTER_PH_CODE   Centered Phase code
            // Reading this field returns the current value on tuning_cclk_sel output Setting AT_CTRL_R.SW_TUNE_EN enables software to write to this field and its contents are reflected on tuning_cclk_sel.
            // Testable: read only
            __IO uint32_t CENTER_PH_CODE: 4;

            // R_EDGE_PH_CODE   Right Edge Phase code
            // Reading this field returns the phase code value used by Auto-tuning engine to sample data on Right edge of sampling window.
            __IO uint32_t R_EDGE_PH_CODE: 4;

            // L_EDGE_PH_CODE   Left Edge Phase code
            // Reading this field returns the phase code value used by Auto-tuning engine to sample data on Left edge of sampling window.
            __IO uint32_t L_EDGE_PH_CODE: 4;

            __IO uint32_t : 4;

        } S_AT_STAT;
    };

    __IO uint32_t RESERVED14[649];            /*!< [0x0548] Revered */

    union
    {
        __IO uint32_t EMBEDDED_CTRL;          /*!< [0x0F6C] Embedded Control register */
        struct
        {
            // NUM_CLK_PIN  Number of Clock Pins
            // This field indicates support of clock pins to select one of devices for shared bus system. Up to 7 clock pins can be supported.
            //   0x0 : Shared bus is not supported
            //   0x1 : 1 SDCLK is supported
            //   0x2 - 2 SDCLK is supported
            //   . .
            //   . .
            //   . .
            //   0x7 : 7 SDCLK is supported
            // Note: SD Mode.
            __IO uint32_t NUM_CLK_PIN: 3;

            __IO uint32_t : 1;

            // NUM_INT_PIN  Number of Interrupt Input Pins
            // This field indicates support of interrupt input pins for an embedded system.
            __IO uint32_t NUM_INT_PIN: 2;

            __IO uint32_t : 2;

            // BUS_WIDTH_PRESET Bus Width Preset
            // Each bit of this field specifies the bus width for each embedded device. The shared bus supports mixing of 4-bit and 8-bit bus width devices.
            //   D08 : Bus Width Preset for Device 1
            //   D09 : Bus Width Preset for Device 2
            //   D10 : Bus Width Preset for Device 3
            //   D11 : Bus Width Preset for Device 4
            //   D12 : Bus Width Preset for Device 5
            //   D13 : Bus Width Preset for Device 6
            //   D14 : Bus Width Preset for Device 7
            // Function of each bit is defined as follows:
            //   0 : 4-bit bus width mode
            //   1 : 8-bit bus width mode
            // Note: SD Mode.
            __IO uint32_t BUS_WIDTH_PRESET: 7;

            __IO uint32_t : 1;

            // CLK_PIN_SEL  Clock Pin Select
            // This bit is selected by one of clock pin outputs.
            //   0x0 : Clock pins are disabled
            //   0x1 : CLK[1] is selected
            //   0x2 : CLK[2] is selected
            //   . .
            //   . .
            //   . .
            //   0x7 : CLK[7] is selected
            // Note: SD Mode.
            __IO uint32_t CLK_PIN_SEL: 3;

            __IO uint32_t : 1;

            // INT_PIN_SEL  Interrupt Pin Select
            // These bits enable the interrupt pin inputs.
            //   000 : Interrupts (INT_A,INT_B,INT_C) are disabled
            //   xx1 : INT_A is enabled
            //   x1x : INT_B is enabled
            //   1xx : INT_C is enabled
            __IO uint32_t INT_PIN_SEL: 3;

            __IO uint32_t : 1;

            // BACK_END_PWR_CTRL    Back-End Power Control
            // Each bit of this field controls back-end power supply for an embedded device.
            //   0 : Back-End Power is off
            //   1 : Back-End Power is supplied
            // D24 : Back-End Power for Device 1
            // D25 : Back-End Power for Device 2
            // D26 : Back-End Power for Device 3
            // D27 : Back-End Power for Device 4
            // D28 : Back-End Power for Device 5
            // D29 : Back-End Power for Device 6
            // D30 : Back-End Power for Device 7
            // Note: SD Mode
            __IO uint32_t BACK_END_PWR_CTRL: 7;

            __IO uint32_t : 1;

        } S_EMBEDDED_CTRL;
    };

} SDH_T;


/**@}*/ /* end of SDH register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __SDH_REG_H__ */
