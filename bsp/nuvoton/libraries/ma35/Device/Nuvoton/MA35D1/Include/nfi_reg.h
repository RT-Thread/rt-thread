/**************************************************************************//**
 * @file     nfi_reg.h
 * @brief    NFI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NFI_REG_H__
#define __NFI_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- NAND Flash Interface -------------------------*/
/**
    @addtogroup NFI NAND Flash Interface(NFI)
    Memory Mapped Structure for NFI Controller
@{ */

typedef struct
{


    /**
     * @var NFI_T::BUFFER0
     * Offset: 0x00  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER1
     * Offset: 0x04  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER2
     * Offset: 0x08  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER3
     * Offset: 0x0C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER4
     * Offset: 0x10  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER5
     * Offset: 0x14  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER6
     * Offset: 0x18  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER7
     * Offset: 0x1C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER8
     * Offset: 0x20  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER9
     * Offset: 0x24  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER10
     * Offset: 0x28  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER11
     * Offset: 0x2C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER12
     * Offset: 0x30  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER13
     * Offset: 0x34  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER14
     * Offset: 0x38  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER15
     * Offset: 0x3C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER16
     * Offset: 0x40  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER17
     * Offset: 0x44  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER18
     * Offset: 0x48  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER19
     * Offset: 0x4C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER20
     * Offset: 0x50  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER21
     * Offset: 0x54  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER22
     * Offset: 0x58  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER23
     * Offset: 0x5C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER24
     * Offset: 0x60  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER25
     * Offset: 0x64  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER26
     * Offset: 0x68  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER27
     * Offset: 0x6C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER28
     * Offset: 0x70  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER29
     * Offset: 0x74  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER30
     * Offset: 0x78  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::BUFFER31
     * Offset: 0x7C  NFI Embedded Buffer Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NFI Embedded Buffer Word n
     * |        |          |This field indicates a 32-bit data of NAND Flash controller embedded buffer.
     * @var NFI_T::DMACTL
     * Offset: 0x400  NFI DMA Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMACEN    |DMA Controller Engine Enable Bit
     * |        |          |0 = DMA Controller Disabled.
     * |        |          |1 = DMA Controller Enabled.
     * |        |          |Note 1: If this bit is cleared, DMA will ignore all requests from NAND Flash and force bus master into IDLE state.
     * |        |          |Note 2: If target abort occurred, DMACEN will be cleared.
     * |[1]     |DMARST    |Software Engine Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset internal state machine and pointers
     * |        |          |The contents of control register will not be cleared
     * |        |          |This bit will auto be cleared after a few clock cycles.
     * |        |          |Note: The software reset DMA related registers.
     * |[3]     |SGEN      |Scatter-gather Function for NFI Enable Bit
     * |        |          |0 = Scatter-gather function Disabled (DMA will treat the starting address in DMASA as starting pointer of a single block memory).
     * |        |          |1 = Scatter-gather function Enabled (DMA will treat the starting address in DMASA as a starting address of Physical Address Descriptor (PAD) table
     * |        |          |The format of these Pads' will be described later).
     * |[9]     |DMABUSY   |NFI DMA Transfer in Progress
     * |        |          |This bit indicates if NFI is granted and doing DMA transfer or not.
     * |        |          |0 = NFI DMA transfer is not in progress.
     * |        |          |1 = NFI DMA transfer is in progress.
     * @var NFI_T::DMASA
     * Offset: 0x408  NFI DMA Transfer Starting Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ORDER     |Determined to the PAD Table Fetching Is in Order or Out of Order
     * |        |          |0 = PAD table is fetched in order.
     * |        |          |1 = PAD table is fetched out of order.
     * |        |          |Note: the bit 0 is valid in scatter-gather mode when SGEN (NFI_DMACTL[3]) = 1.
     * |[31:1]  |DMASA     |DMA Transfer Starting Address
     * |        |          |This field pads 0 as least significant bit indicates a 32-bit starting address of system memory (SRAM) for DMA to retrieve or fill in data.
     * |        |          |If DMA is not in normal mode, this field will be interpreted as a starting address of Physical Address Descriptor (PAD) table.
     * |        |          |Note: Starting address of the SRAM must be word aligned, for example, 0x0000_0000, 0x0000_0004.
     * @var NFI_T::DMABCNT
     * Offset: 0x40C  NFI DMA Transfer Byte Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[25:0]  |BCNT      |DMA Transfer Byte Count (Read Only)
     * |        |          |This field indicates the remained byte count of DMA transfer
     * |        |          |The value of this field is valid only when NFI is busy; otherwise, it is zero.
     * @var NFI_T::DMAINTEN
     * Offset: 0x410  NFI DMA Interrupt Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ABORTIEN  |DMA Read/Write Target Abort Interrupt Enable Bit
     * |        |          |0 = Target abort interrupt generation Disabled during DMA transfer.
     * |        |          |1 = Target abort interrupt generation Enabled during DMA transfer.
     * |[1]     |WEOTIEN   |Wrong EOT Encountered Interrupt Enable Bit
     * |        |          |0 = Interrupt generation Disabled when wrong EOT (end of transfer) is encountered.
     * |        |          |1 = Interrupt generation Enabled when wrong EOT (end of transfer) is encountered.
     * @var NFI_T::DMAINTSTS
     * Offset: 0x414  NFI DMA Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ABORTIF   |DMA Read/Write Target Abort Interrupt Flag(Read Only)
     * |        |          |0 = No bus ERROR response received.
     * |        |          |1 = Bus ERROR response received.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * |        |          |Note: When DMA's bus master received ERROR response, it means that target abort happened
     * |        |          |DMA will stop transfer and respond this event by set ABORTIF high
     * |        |          |Then, NFI go to IDLE state
     * |        |          |When target abort occurred or WEOTIF is set, it is necessary to reset NFI's DMA and then transfer those data again.
     * |[1]     |WEOTIF    |Wrong EOT Encountered Interrupt Flag(Read Only)
     * |        |          |When DMA Scatter-Gather function is enabled, and EOT of the descriptor is encountered before DMA transfer finished (that means the total sector count of all PAD is less than the sector count of NFI), this bit will be set.
     * |        |          |0 = No EOT encountered before DMA transfer finished.
     * |        |          |1 = EOT encountered before DMA transfer finished.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * @var NFI_T::GCTL
     * Offset: 0x800  NFI Global Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GCTLRST   |Software Engine Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset all NFI engines.
     * |        |          |Note: The contents of control register will not be cleared
     * |        |          |This bit will auto cleared after a few clock cycles.
     * |[3]     |NANDEN    |NAND Flash Functionality Enable Bit
     * |        |          |0 = NAND Flash functionality of NFI Disabled.
     * |        |          |1 = NAND Flash functionality of NFI Enabled.
     * @var NFI_T::GINTEN
     * Offset: 0x804  NFI Global Interrupt Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DTAIEN    |DMA READ/WRITE Target Abort Interrupt Enable Bit
     * |        |          |0 = DMA READ/WRITE target abort interrupt generation Disabled.
     * |        |          |1 = DMA READ/WRITE target abort interrupt generation Enabled.
     * @var NFI_T::GINTSTS
     * Offset: 0x808  NFI Global Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DTAIF     |DMA READ/WRITE Target Abort Interrupt Flag (Read Only)
     * |        |          |This bit indicates DMA received an ERROR response from internal AHB bus during DMA read/write operation
     * |        |          |When Target Abort occurred, please reset all engines.
     * |        |          |0 = No bus ERROR response received.
     * |        |          |1 = Bus ERROR response received.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * @var NFI_T::NANDCTL
     * Offset: 0x8A0  NAND Flash Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SWRST     |Software Engine Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset the internal state machine and counters (include DWREN (NFI_NANDCTL[2]) and DRDEN (NFI_NANDCTL[1])).
     * |        |          |Note: The contents of control register will not be cleared
     * |        |          |This bit will be auto cleared after a few clock cycles.
     * |[1]     |DRDEN     |DMA Read Data Enable Bit
     * |        |          |This bit enables NAND controller to transfer data (1 page) from NAND Flash or NAND type Flash into DMAC's embedded frame buffer.
     * |        |          |0 = No effect.
     * |        |          |1 = DMA read data transfer Enabled.
     * |        |          |Note: When DMA transfer completed, this bit will be cleared automatically.
     * |[2]     |DWREN     |DMA Write Data Enable Bit
     * |        |          |This bit enables NAND controller to transfer data (1 page) from DMAC's embedded frame buffer into NAND Flash or NAND type Flash.
     * |        |          |0 = No effect.
     * |        |          |1 = DMA write data transfer Enabled.
     * |        |          |Note: When DMA transfer completed, this bit will be cleared automatically.
     * |[3]     |REDUNREN  |Redundant Area Read Enable Bit
     * |        |          |This bit enables NAND controller to transfer redundant data from NAND Flash into NFI_NANDRA, the data size is dependent on NFI_NANDRACTL register.
     * |        |          |0 = No effect.
     * |        |          |1 = Read redundant data transfer Enabled.
     * |        |          |Note: When transfer completed, this bit will be cleared automatically.
     * |[4]     |REDUNAUTOWEN|Redundant Area Auto Write Enable Bit
     * |        |          |This field is used to auto write redundant data out to NAND Flash
     * |        |          |The redundant data area is dependent on NFI_NANDRACTL register.
     * |        |          |0 = Auto write redundant data out to NAND Flash Disabled.
     * |        |          |1 = Auto write redundant data out to NAND Flash Enabled.
     * |[7]     |ECCCHK    |None Used Field ECC Check After Read Page Data
     * |        |          |0 = ECC check Disabled
     * |        |          |The NAND controller will always check ECC result for each field, no matter it is used or not.
     * |        |          |1 = ECC check Enabled
     * |        |          |The NAND controller will check 1's count for byte 2, 3 of redundant data of the ECC in each field
     * |        |          |If the count value is greater than 8, the NAND controller will treat this field as none used field; otherwise, it is used
     * |        |          |If that field is none used field, the NAND controller will ignore its ECC check result.
     * |[8]     |PROT3BEN  |Protect_3Byte Software Data Enable Bit
     * |        |          |The ECC algorithm only protects data area and hardware ECC parity code
     * |        |          |User can choose to protect software redundant data first 3 bytes by setting this bit high.
     * |        |          |0 = Software redundant data is not protected by ECC algorithm.
     * |        |          |1 = Software redundant data first 3 bytes protected by ECC algorithm.
     * |[9]     |SRAMINT   |SRAM Initial
     * |        |          |0 = No effect.
     * |        |          |1 = Reset the internal NFI_NANDRA0~NFI_NANDRA1 to 0xFFFF_FFFF.
     * |        |          |Note: The contents of control register will not be cleared
     * |        |          |This bit will be auto cleared after a few clock cycles.
     * |[17:16] |PSIZE     |Page Size of NAND
     * |        |          |This bit indicates the page size of NAND
     * |        |          |There are four page sizes for choose, 2048 bytes/page, 4096 bytes/page and 8192 bytes/page
     * |        |          |Before setting PSIZE register, user must set BCHTSEL register at first.
     * |        |          |01 = Page size is 2048 bytes/page.
     * |        |          |10 = Page size is 4096 bytes/page.
     * |        |          |11 = Page size is 8192 bytes/page.
     * |[22:18] |BCHTSEL   |BCH Correct Bit Selection
     * |        |          |This field is used to select BCH correct bits for data protecting
     * |        |          |For BCH algorithm, T can be 8 or 12 or 24 for choosing (correct 8 or 12 or 24 bits).
     * |        |          |00001 = Using BCH T24 to encode/decode (T24).(.1024 Bytes per block)
     * |        |          |00100 = Using BCH T8 to encode/decode (T8).
     * |        |          |01000 = Using BCH T12 to encode/decode (T12).
     * |[23]    |ECCEN     |ECC Algorithm Enable Bit
     * |        |          |This field is used to select the ECC algorithm for data protecting
     * |        |          |The BCH algorithm can correct 8 or 12 or 24 bits.
     * |        |          |0 = BCH code encode/decode Disabled.
     * |        |          |1 = BCH code encode/decode Enabled.
     * |        |          |Note: If disabling ECCEN and when reading data from NAND, the NAND controller will ignore its ECC check result
     * |        |          |When writing data to NAND, the NAND controller will write out 0xFF to every parity field.
     * |        |          |Note: The ECC algorithm only protects data area and hardware ECC parity code by default
     * |        |          |By setting PROT3BEN (NFI_NANDCTL[8]) high, the first 3 bytes of redundant data are also protected by ECC algorithm.
     * |[25]    |CS0       |NAND Flash Chip Select 0 Enable Bit
     * |        |          |0 = Chip select 0 Enabled.
     * |        |          |1 = Chip select 0 Disabled.
     * @var NFI_T::NANDTMCTL
     * Offset: 0x8A4  NAND Flash Timing Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |LOWID     |Read/Write Enable Signal Low Pulse Width
     * |        |          |This field controls the low pulse width of signals -RE and -WE while HARDWARE mode page access is enabled
     * |        |          |The pulse width is a multiple of period of AHB bus clock
     * |        |          |( The actual width time will be [clock period*(LOWID+1)] )
     * |[15:8]  |HIWID     |Read/Write Enable Signal High Pulse Width
     * |        |          |This field controls the high pulse width of signals -RE and -WE while HARDWARE mode page access is enabled
     * |        |          |The pulse width is a multiple of period of AHB bus clock
     * |        |          |( The actual width time will be [clock period*(HIWID+1)] )
     * |[22:16] |CALESH    |CLE/ALE Setup/Hold Time
     * |        |          |This field controls the CLE/ALE setup/hold time to -WE.
     * |        |          |The setup/hold time can be calculated using following equation:
     * |        |          |tCLS = (CALESH+1)*TAHB.
     * |        |          |tCLH = ((CALESH*2)+2)*TAHB.
     * |        |          |tALS = (CALESH+1)*TAHB.
     * |        |          |tALH = ((CALESH*2)+2)*TAHB.
     * |[27:24] |EDOD      |EDO Mode Delay Time
     * |        |          |Control this field to delay sampling point when NAND Flash enters EDO mode only.
     * |        |          |The EDO mode delay time can be calculated using following equation:
     * |        |          |Delay time = (EDOD+1)*(TAHB/2).
     * |[31]    |EDOEN     |EDO Mode Enable Bit
     * |        |          |This bit specifies NAND Flash to EDO mode
     * |        |          |Before trigger this bit, software should fill EDOD(NFI_NANDTMCTL[27:24]), CALESH(NFI_NANDTMCTL[22:16]), HIWID(NFI_NANDTMCTL[15:8]) and LOWID(NFI_NANDTMCTL[7:0]).
     * |        |          |0 = EDO Mode related function Disabled.
     * |        |          |1 = EDO Mode related function Enabled.
     * |        |          |Note: Only NAND Flash entering EDO mode should set this bit.
     * @var NFI_T::NANDINTEN
     * Offset: 0x8A8  NAND Flash Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMAIE     |DMA Read/Write Data Complete Interrupt Enable Bit
     * |        |          |0 = DMA read/write data complete interrupt generation Disabled.
     * |        |          |1 = DMA read/write data complete interrupt generation Enabled.
     * |[2]     |ECCFLDIE  |ECC Field Check Error Interrupt Enable Bit
     * |        |          |This bit can check the ECC error on each field (512bytes) of data transfer
     * |        |          |Enable this bit to detect error and do error correction.
     * |        |          |0 = ECC field check error Disabled.
     * |        |          |1 = ECC field check error Enabled.
     * |[10]    |RB0IE     |Ready/-Busy Rising Edge Detect Interrupt Enable Bit
     * |        |          |0 = R/-B rising edge detect interrupt generation Disabled.
     * |        |          |1 = R/-B rising edge detect interrupt generation Enabled.
     * @var NFI_T::NANDINTSTS
     * Offset: 0x8AC  NAND Flash Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMAIF     |DMA Read/Write Data Complete Interrupt Flag (Read Only)
     * |        |          |0 = DMA read/write transfer is not finished yet.
     * |        |          |1 = DMA read/write transfer is done.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * |[2]     |ECCFLDIF  |ECC Field Check Error Interrupt Flag (Read Only)
     * |        |          |This bit can check the ECC error on each field (512bytes) of data transfer
     * |        |          |Read this bit to check if the error occurred.
     * |        |          |0 = No occurrence of ECC error.
     * |        |          |1 = Occurrence of ECC error.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * |[4]     |EDOF      |EDO Mode Entrance Flag (Read Only)
     * |        |          |0 = NAND Flash did not enter EDO mode.
     * |        |          |1 = NAND Flash entered EDO mode.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * |[10]    |RB0IF     |Ready/-Busy 0 Rising Edge Detect Interrupt Flag (Read Only)
     * |        |          |0 = R/-B rising edge is not detected.
     * |        |          |1 = R/-B rising edge is detected.
     * |        |          |Note: This bit is read only, but can be cleared by writing '1' to it.
     * |[18]    |RB0Status |Ready/-Busy 0 Pin Status (Read Only)
     * |        |          |This bit reflects the Ready/-Busy pin status of NAND Flash.
     * @var NFI_T::NANDCMD
     * Offset: 0x8B0  NAND Flash Command Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |COMMAND   |NAND Flash Command Port
     * |        |          |When CPU writes to this port, NFI will send a command to NAND Flash.
     * @var NFI_T::NANDADDR
     * Offset: 0x8B4  NAND Flash Address Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ADDRESS   |NAND Flash Address Port
     * |        |          |By writing this port, NAND Flash control will send an address to NAND Flash.
     * |[31]    |EOA       |End of Address
     * |        |          |Write this bit to indicate if this address is the last one or not
     * |        |          |By writing address port with this bit low, the NAND Flash controller will set ALE pin to active (HIGH)
     * |        |          |After the last address is written (with this bit set high), the NAND Flash controller will set ALE pin to inactive (LOW).
     * |        |          |0 = Not the last address cycle.
     * |        |          |1 = The last one address cycle.
     * @var NFI_T::NANDDATA
     * Offset: 0x8B8  NAND Flash Data Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DATA      |NAND Flash Data Port
     * |        |          |CPU can access NAND's memory array through this data port
     * |        |          |When CPU WRITE, the lower 8-bit data from CPU will appear on the data bus of NAND controller
     * |        |          |When CPU READ, NAND controller will get 8-bit data from data bus.
     * @var NFI_T::NANDRACTL
     * Offset: 0x8BC  NAND Flash Redundant Area Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |RA128EN   |Redundant Area 128 Byte Enable Bit
     * |        |          |These bits indicate NAND Flash extended redundant area.
     * |        |          |If PSIZE (NFI_NANDCTL[17:16]) = 2'b01, this field will be set 0x40 (64bytes) automatically.
     * |        |          |If PSIZE (NFI_NANDCTL[17:16]) = 2'b10, this field will be set 0x80 (128 bytes) automatically.
     * |        |          |If PSIZE (NFI_NANDCTL[17:16]) = 2'b11, this field will be set 0x100 (256bytes) automatically.
     * |        |          |Note: The REA128EN must be 4 byte aligned, so bit1 and bit0 can't be filled 1 to it.
     * |        |          |The maximum redundant area of the controller is 472Bytes.
     * |[31:16] |MECC      |Mask ECC During Write Page Data
     * |        |          |These 16 bits registers indicate NAND controller to write out ECC parity or just 0xFF for each field (every 512 bytes) the real parity data will be write out to NFI_NANDRAx.
     * |        |          |0x00 = Do not mask the ECC parity for each field.
     * |        |          |0x01 = Mask ECC parity and write out FF to NAND ECC parity for 512 Bytes page size or 2K/4K/8K page size first 512 field.
     * |        |          |0x02 = Mask ECC parity and write out FF to NAND ECC parity for 512 Bytes page size or 2K/4K/8K page size second 512 field.
     * |        |          |Others = Mask ECC parity and write out FF to NAND ECC parity for 512 Bytes page size or 2K/4K/8K page size each 512 field.
     * @var NFI_T::NANDECTL
     * Offset: 0x8C0  NAND Flash Extend Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WP        |NAND Flash Write Protect Control
     * |        |          |Set this bit low (low active) to make NAND_nWP functional pin low to prevent the write to NAND Flash device.
     * |        |          |0 = NAND Flash is write-protected and is not writeable.
     * |        |          |1 = NAND Flash is not write-protected and is writeable.
     * @var NFI_T::NANDECCES0
     * Offset: 0x8D0  NAND Flash ECC Error Status 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |F1STAT    |ECC Status of Field 1
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 1.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[6:2]   |F1ECNT    |Error Count of ECC Field 1
     * |        |          |This field contains the error counts after ECC correct calculation of Field 1
     * |        |          |For this ECC core (BCH algorithm), only when F1STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F1ECNT means how many errors depending on which ECC is used.
     * |[9:8]   |F2STAT    |ECC Status of Field 2
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 2.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[14:10] |F2ECNT    |Error Count of ECC Field 2
     * |        |          |This field contains the error counts after ECC correct calculation of Field 2
     * |        |          |For this ECC core (BCH algorithm), only when F2STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F2ECNT means how many errors depending on which ECC is used.
     * |[17:16] |F3STAT    |ECC Status of Field 3
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 3.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[22:18] |F3ECNT    |Error Count of ECC Field 3
     * |        |          |This field contains the error counts after ECC correct calculation of Field 3
     * |        |          |For this ECC core (BCH algorithm), only when F3STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F3ECNT means how many errors depending on which ECC is used.
     * |[25:24] |F4STAT    |ECC Status of Field 4
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 4.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[30:26] |F4ECNT    |Error Count of ECC Field 4
     * |        |          |This field contains the error counts after ECC correct calculation of Field 4
     * |        |          |For this ECC core (BCH algorithm), only when F4STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F4ECNT means how many errors depending on which ECC is used.
     * @var NFI_T::NANDECCES1
     * Offset: 0x8D4  NAND Flash ECC Error Status 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |F5STAT    |ECC Status of Field 5
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field5.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[6:2]   |F5ECNT    |Error Count of ECC Field 5
     * |        |          |This field contains the error counts after ECC correct calculation of Field 5
     * |        |          |For this ECC core (BCH algorithm), only when F5STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F5ECNT means how many errors depending on which ECC is used.
     * |[9:8]   |F6STAT    |ECC Status of Field 6
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 6.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[14:10] |F6ECNT    |Error Count of ECC Field 6
     * |        |          |This field contains the error counts after ECC correct calculation of Field 6
     * |        |          |For this ECC core (BCH algorithm), only when F6STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F6ECNT means how many errors depending on which ECC is used.
     * |[17:16] |F7STAT    |ECC Status of Field 7
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 7.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[22:18] |F7ECNT    |Error Count of ECC Field 7
     * |        |          |This field contains the error counts after ECC correct calculation of Field 7
     * |        |          |For this ECC core (BCH algorithm), only when F7STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F7ECNT means how many errors depending on which ECC is used.
     * |[25:24] |F8STAT    |ECC Status of Field 8
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 8.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[30:26] |F8ECNT    |Error Count of ECC Field 8
     * |        |          |This field contains the error counts after ECC correct calculation of Field 8
     * |        |          |For this ECC core (BCH algorithm), only when F8STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F8ECNT means how many errors depending on which ECC is used.
     * @var NFI_T::NANDECCES2
     * Offset: 0x8D8  NAND Flash ECC Error Status 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |F9STAT    |ECC Status of Field 9
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 9.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[6:2]   |F9ECNT    |Error Count of ECC Field 9
     * |        |          |This field contains the error counts after ECC correct calculation of Field 9
     * |        |          |For this ECC core (BCH algorithm), only when F9STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F9ECNT means how many errors depending on which ECC is used.
     * |[9:8]   |F10STAT   |ECC Status of Field 10
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 10.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[14:10] |F10ECNT   |Error Count of ECC Field 10
     * |        |          |This field contains the error counts after ECC correct calculation of Field 10
     * |        |          |For this ECC core (BCH algorithm), only when F10STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F10ECNT means how many errors depending on which ECC is used.
     * |[17:16] |F11STAT   |ECC Status of Field 11
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 11.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[22:18] |F11ECNT   |Error Count of ECC Field 11
     * |        |          |This field contains the error counts after ECC correct calculation of Field 11
     * |        |          |For this ECC core (BCH algorithm), only when F11STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F11ECNT means how many errors depending on which ECC is used.
     * |[25:24] |F12STAT   |ECC Status of Field 12
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 12.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[30:26] |F12ECNT   |Error Count of ECC Field 12
     * |        |          |This field contains the error counts after ECC correct calculation of Field 12
     * |        |          |For this ECC core (BCH algorithm), only when F12STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F12ECNT means how many errors depending on which ECC is used.
     * @var NFI_T::NANDECCES3
     * Offset: 0x8DC  NAND Flash ECC Error Status 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |F13STAT   |ECC Status of Field 13
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 13.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[6:2]   |F13ECNT   |Error Count of ECC Field 13
     * |        |          |This field contains the error counts after ECC correct calculation of Field 13
     * |        |          |For this ECC core (BCH algorithm), only when F13STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F13ECNT means how many errors depending on which ECC is used.
     * |[9:8]   |F14STAT   |ECC Status of Field 14
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 14.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[14:10] |F14ECNT   |Error Count of ECC Field 14
     * |        |          |This field contains the error counts after ECC correct calculation of Field 14
     * |        |          |For this ECC core (BCH algorithm), only when F14STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F14ECNT means how many errors depending on which ECC is used.
     * |[17:16] |F15STAT   |ECC Status of Field 15
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 15.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[22:18] |F15ECNT   |Error Count of ECC Field 15
     * |        |          |This field contains the error counts after ECC correct calculation of Field 15
     * |        |          |For this ECC core (BCH algorithm), only when F15STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F15ECNT means how many errors depending on which ECC is used.
     * |[25:24] |F16STAT   |ECC Status of Field 16
     * |        |          |This field contains the ECC correction status (BCH algorithm) of ECC-field 16.
     * |        |          |00 = No error.
     * |        |          |01 = Correctable error.
     * |        |          |10 = Uncorrectable error.
     * |        |          |11 = Reserved.
     * |[30:26] |F16ECNT   |Error Count of ECC Field 16
     * |        |          |This field contains the error counts after ECC correct calculation of Field 16
     * |        |          |For this ECC core (BCH algorithm), only when F16STAT equals to 0x01, the value in this field is meaningful
     * |        |          |F16ECNT means how many errors depending on which ECC is used.
     * @var NFI_T::NANDECCEA0
     * Offset: 0x900  NAND Flash ECC Error Byte Address 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR0  |ECC Error Address First Field of Error 0
     * |        |          |This field contains an 11-bit ECC error address 0 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA0 (NFI_NANDECCED0[7:0]), to correct this error.
     * |[26:16] |ERRADDR1  |ECC Error Address First Field of Error 1
     * |        |          |This field contains an 11-bit ECC error address 1 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA1 (NFI_NANDECCED0[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA1
     * Offset: 0x904  NAND Flash ECC Error Byte Address 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR2  |ECC Error Address First Field of Error 2
     * |        |          |This field contains an 11-bit ECC error address 2 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA2 (NFI_NANDECCED0[23:16]), to correct this error.
     * |[26:16] |ERRADDR3  |ECC Error Address First Field of Error 3
     * |        |          |This field contains an 11-bit ECC error address 3 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA3 (NFI_NANDECCED0[31:24]), to correct this error.
     * @var NFI_T::NANDECCEA2
     * Offset: 0x908  NAND Flash ECC Error Byte Address 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR4  |ECC Error Address First Field of Error 4
     * |        |          |This field contains an 11-bit ECC error address 4 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA4 (NFI_NANDECCED1[7:0]), to correct this error.
     * |[26:16] |ERRADDR5  |ECC Error Address First Field of Error 5
     * |        |          |This field contains an 11-bit ECC error address 5 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA5 (NFI_NANDECCED1[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA3
     * Offset: 0x90C  NAND Flash ECC Error Byte Address 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR6  |ECC Error Address First Field of Error 6
     * |        |          |This field contains an 11-bit ECC error address 6 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA6 (NFI_NANDECCED1[23:16]), to correct this error.
     * |[26:16] |ERRADDR7  |ECC Error Address First Field of Error 7
     * |        |          |This field contains an 11-bit ECC error address 7 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA7 (NFI_NANDECCED1[31:24]), to correct this error.
     * @var NFI_T::NANDECCEA4
     * Offset: 0x910  NAND Flash ECC Error Byte Address 4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR8  |ECC Error Address First Field of Error 8
     * |        |          |This field contains an 11-bit ECC error address 8 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA8 (NFI_NANDECCED2[7:0]), to correct this error.
     * |[26:16] |ERRADDR9  |ECC Error Address First Field of Error 9
     * |        |          |This field contains an 11-bit ECC error address 9 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA9 (NFI_NANDECCED2[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA5
     * Offset: 0x914  NAND Flash ECC Error Byte Address 5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR10 |ECC Error Address First Field of Error 10
     * |        |          |This field contains an 11-bit ECC error address 10 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA10 (NFI_NANDECCED2[23:16]), to correct this error.
     * |[26:16] |ERRADDR11 |ECC Error Address First Field of Error 11
     * |        |          |This field contains an 11-bit ECC error address 11 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA11 (NFI_NANDECCED2[31:24]), to correct this error.
     * @var NFI_T::NANDECCEA6
     * Offset: 0x918  NAND Flash ECC Error Byte Address 6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR12 |ECC Error Address First Field of Error 12
     * |        |          |This field contains an 11-bit ECC error address 12 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA12 (NFI_NANDECCED3[7:0]), to correct this error.
     * |[26:16] |ERRADDR13 |ECC Error Address First Field of Error 13
     * |        |          |This field contains an 11-bit ECC error address 13 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA13 (NFI_NANDECCED3[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA7
     * Offset: 0x91C  NAND Flash ECC Error Byte Address 7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR14 |ECC Error Address First Field of Error 14
     * |        |          |This field contains an 11-bit ECC error address 14 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA14 (NFI_NANDECCED3[23:16]), to correct this error.
     * |[26:16] |ERRADDR15 |ECC Error Address First Field of Error 15
     * |        |          |This field contains an 11-bit ECC error address 15 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA15 (NFI_NANDECCED3[31:24]), to correct this error.
     * @var NFI_T::NANDECCEA8
     * Offset: 0x920  NAND Flash ECC Error Byte Address 8 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR16 |ECC Error Address First Field of Error 16
     * |        |          |This field contains an 11-bit ECC error address 16 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA16 (NFI_NANDECCED4[7:0]), to correct this error.
     * |[26:16] |ERRADDR17 |ECC Error Address First Field of Error 17
     * |        |          |This field contains an 11-bit ECC error address 17 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA17 (NFI_NANDECCED4[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA9
     * Offset: 0x924  NAND Flash ECC Error Byte Address 9 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR18 |ECC Error Address First Field of Error 18
     * |        |          |This field contains an 11-bit ECC error address 18 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA18 (NFI_NANDECCED4[23:16]), to correct this error.
     * |[26:16] |ERRADDR19 |ECC Error Address First Field of Error 19
     * |        |          |This field contains an 11-bit ECC error address 19 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA19 (NFI_NANDECCED4[31:24]), to correct this error.
     * @var NFI_T::NANDECCEA10
     * Offset: 0x928  NAND Flash ECC Error Byte Address 10 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR20 |ECC Error Address First Field of Error 20
     * |        |          |This field contains an 11-bit ECC error address 20 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA20 (NFI_NANDECCED5[7:0]), to correct this error.
     * |[26:16] |ERRADDR21 |ECC Error Address First Field of Error 21
     * |        |          |This field contains an 11-bit ECC error address 21 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA21 (NFI_NANDECCED5[15:8]), to correct this error.
     * @var NFI_T::NANDECCEA11
     * Offset: 0x92C  NAND Flash ECC Error Byte Address 11 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |ERRADDR22 |ECC Error Address First Field of Error 22
     * |        |          |This field contains an 11-bit ECC error address 22 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA22 (NFI_NANDECCED5[23:16]), to correct this error.
     * |[26:16] |ERRADDR23 |ECC Error Address First Field of Error 23
     * |        |          |This field contains an 11-bit ECC error address 23 of first field
     * |        |          |If it is a correctable error, please read the error data, ERRDATA23 (NFI_NANDECCED5[31:24]), to correct this error.
     * @var NFI_T::NANDECCED0
     * Offset: 0x960  NAND Flash ECC Error Data Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA0  |ECC Error Data of First Field 0
     * |        |          |This field contains an 8-bit BCH ECC error data 0 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR0 (NFI_ANNDECCEA0[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA1  |ECC Error Data of First Field 1
     * |        |          |This field contains an 8-bit BCH ECC error data 1 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR1 (NFI_NANDECCEA0[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA2  |ECC Error Data of First Field 2
     * |        |          |This field contains an 8-bit BCH ECC error data 2 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR2 (NFI_NANDECCEA1[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA3  |ECC Error Data of First Field 3
     * |        |          |This field contains an 8-bit BCH ECC error data 3 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR3 (NFI_NANDECCEA1[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDECCED1
     * Offset: 0x964  NAND Flash ECC Error Data Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA4  |ECC Error Data of First Field 4
     * |        |          |This field contains an 8-bit BCH ECC error data 4 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR4 (NFI_NANDECCEA2[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA5  |ECC Error Data of First Field 5
     * |        |          |This field contains an 8-bit BCH ECC error data 5 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR5 (NFI_NANDECCEA2[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA6  |ECC Error Data of First Field 6
     * |        |          |This field contains an 8-bit BCH ECC error data 6 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR6 (NFI_NANDECCEA3[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA7  |ECC Error Data of First Field 7
     * |        |          |This field contains an 8-bit BCH ECC error data 7 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR7 (NFI_NANDECCEA3[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDECCED2
     * Offset: 0x968  NAND Flash ECC Error Data Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA8  |ECC Error Data of First Field 8
     * |        |          |This field contains an 8-bit BCH ECC error data 8 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR8 (NFI_NANDECCEA4[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA9  |ECC Error Data of First Field 9
     * |        |          |This field contains an 8-bit BCH ECC error data 9 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR9 (NFI_NANDECCEA4[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA10 |ECC Error Data of First Field 10
     * |        |          |This field contains an 8-bit BCH ECC error data 10 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR10 (NFI_NANDECCEA5[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA11 |ECC Error Data of First Field 11
     * |        |          |This field contains an 8-bit BCH ECC error data 11 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR11 (NFI_NANDECCEA5[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDECCED3
     * Offset: 0x96C  NAND Flash ECC Error Data Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA12 |ECC Error Data of First Field 12
     * |        |          |This field contains an 8-bit BCH ECC error data 12 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR12 (NFI_NANDECCEA6[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA13 |ECC Error Data of First Field 13
     * |        |          |This field contains an 8-bit BCH ECC error data 13 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR13 (NFI_NANDECCEA6[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA14 |ECC Error Data of First Field 14
     * |        |          |This field contains an 8-bit BCH ECC error data 14 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR14 (NFI_NANDECCEA7[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA15 |ECC Error Data of First Field 15
     * |        |          |This field contains an 8-bit BCH ECC error data 15 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR15 (NFI_NANDECCEA7[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDECCED4
     * Offset: 0x970  NAND Flash ECC Error Data Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA16 |ECC Error Data of First Field 16
     * |        |          |This field contains an 8-bit BCH ECC error data 16 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR16 (NFI_NANDECCEA8[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA17 |ECC Error Data of First Field 17
     * |        |          |This field contains an 8-bit BCH ECC error data 17 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR17 (NFI_NANDECCEA8[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA18 |ECC Error Data of First Field 18
     * |        |          |This field contains an 8-bit BCH ECC error data 18 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR18 (NFI_NANDECCEA9[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA19 |ECC Error Data of First Field 19
     * |        |          |This field contains an 8-bit BCH ECC error data 19 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR19 (NFI_NANDECCEA9[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDECCED5
     * Offset: 0x974  NAND Flash ECC Error Data Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |ERRDATA20 |ECC Error Data of First Field 20
     * |        |          |This field contains an 8-bit BCH ECC error data 20 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR20 (NFI_NANDECCEA10[10:0]), and then the result will be the correct data.
     * |[15:8]  |ERRDATA21 |ECC Error Data of First Field 21
     * |        |          |This field contains an 8-bit BCH ECC error data 21 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR21 (NFI_NANDECCEA10[26:16]), and then the result will be the correct data.
     * |[23:16] |ERRDATA22 |ECC Error Data of First Field 22
     * |        |          |This field contains an 8-bit BCH ECC error data 22 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR22 (NFI_NANDECCEA11[10:0]), and then the result will be the correct data.
     * |[31:24] |ERRDATA23 |ECC Error Data of First Field 23
     * |        |          |This field contains an 8-bit BCH ECC error data 23 of first field
     * |        |          |If it is a correctable error, please read out the error data in this field and doing bitwise XOR with received data locating at address ERRADDR23 (NFI_NANDECCEA11[26:16]), and then the result will be the correct data.
     * @var NFI_T::NANDRA0
     * Offset: 0xA00  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA1
     * Offset: 0xA04  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA2
     * Offset: 0xA08  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA3
     * Offset: 0xA0C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA4
     * Offset: 0xA10  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA5
     * Offset: 0xA14  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA6
     * Offset: 0xA18  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA7
     * Offset: 0xA1C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA8
     * Offset: 0xA20  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA9
     * Offset: 0xA24  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA10
     * Offset: 0xA28  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA11
     * Offset: 0xA2C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA12
     * Offset: 0xA30  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA13
     * Offset: 0xA34  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA14
     * Offset: 0xA38  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA15
     * Offset: 0xA3C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA16
     * Offset: 0xA40  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA17
     * Offset: 0xA44  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA18
     * Offset: 0xA48  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA19
     * Offset: 0xA4C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA20
     * Offset: 0xA50  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA21
     * Offset: 0xA54  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA22
     * Offset: 0xA58  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA23
     * Offset: 0xA5C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA24
     * Offset: 0xA60  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA25
     * Offset: 0xA64  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA26
     * Offset: 0xA68  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA27
     * Offset: 0xA6C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA28
     * Offset: 0xA70  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA29
     * Offset: 0xA74  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA30
     * Offset: 0xA78  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA31
     * Offset: 0xA7C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA32
     * Offset: 0xA80  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA33
     * Offset: 0xA84  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA34
     * Offset: 0xA88  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA35
     * Offset: 0xA8C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA36
     * Offset: 0xA90  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA37
     * Offset: 0xA94  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA38
     * Offset: 0xA98  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA39
     * Offset: 0xA9C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA40
     * Offset: 0xAA0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA41
     * Offset: 0xAA4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA42
     * Offset: 0xAA8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA43
     * Offset: 0xAAC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA44
     * Offset: 0xAB0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA45
     * Offset: 0xAB4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA46
     * Offset: 0xAB8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA47
     * Offset: 0xABC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA48
     * Offset: 0xAC0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA49
     * Offset: 0xAC4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA50
     * Offset: 0xAC8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA51
     * Offset: 0xACC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA52
     * Offset: 0xAD0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA53
     * Offset: 0xAD4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA54
     * Offset: 0xAD8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA55
     * Offset: 0xADC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA56
     * Offset: 0xAE0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA57
     * Offset: 0xAE4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA58
     * Offset: 0xAE8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA59
     * Offset: 0xAEC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA60
     * Offset: 0xAF0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA61
     * Offset: 0xAF4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA62
     * Offset: 0xAF8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA63
     * Offset: 0xAFC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA64
     * Offset: 0xB00  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA65
     * Offset: 0xB04  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA66
     * Offset: 0xB08  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA67
     * Offset: 0xB0C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA68
     * Offset: 0xB10  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA69
     * Offset: 0xB14  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA70
     * Offset: 0xB18  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA71
     * Offset: 0xB1C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA72
     * Offset: 0xB20  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA73
     * Offset: 0xB24  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA74
     * Offset: 0xB28  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA75
     * Offset: 0xB2C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA76
     * Offset: 0xB30  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA77
     * Offset: 0xB34  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA78
     * Offset: 0xB38  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA79
     * Offset: 0xB3C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA80
     * Offset: 0xB40  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA81
     * Offset: 0xB44  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA82
     * Offset: 0xB48  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA83
     * Offset: 0xB4C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA84
     * Offset: 0xB50  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA85
     * Offset: 0xB54  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA86
     * Offset: 0xB58  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA87
     * Offset: 0xB5C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA88
     * Offset: 0xB60  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA89
     * Offset: 0xB64  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA90
     * Offset: 0xB68  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA91
     * Offset: 0xB6C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA92
     * Offset: 0xB70  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA93
     * Offset: 0xB74  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA94
     * Offset: 0xB78  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA95
     * Offset: 0xB7C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA96
     * Offset: 0xB80  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA97
     * Offset: 0xB84  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA98
     * Offset: 0xB88  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA99
     * Offset: 0xB8C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA100
     * Offset: 0xB90  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA101
     * Offset: 0xB94  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA102
     * Offset: 0xB98  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA103
     * Offset: 0xB9C  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA104
     * Offset: 0xBA0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA105
     * Offset: 0xBA4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA106
     * Offset: 0xBA8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA107
     * Offset: 0xBAC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA108
     * Offset: 0xBB0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA109
     * Offset: 0xBB4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA110
     * Offset: 0xBB8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA111
     * Offset: 0xBBC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA112
     * Offset: 0xBC0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA113
     * Offset: 0xBC4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA114
     * Offset: 0xBC8  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA115
     * Offset: 0xBCC  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA116
     * Offset: 0xBD0  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     * @var NFI_T::NANDRA117
     * Offset: 0xBD4  NAND Flash Redundant Area Word n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |Data      |NAND Flash Redundant Area Word n
     * |        |          |This field indicates a 32-bit data of redundant area.
     */
    __IO uint32_t BUFFER[32];            /*!< [0x0000] NFI Embedded Buffer Word n                                       */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE0[224];         /*!< [0x0080~0x03FC]                                                           */
    /** @endcond */
    __IO uint32_t DMACTL;                /*!< [0x0400] NFI DMA Control and Status Register                              */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE1[1];           /*!< [0x0404]                                                                  */
    /** @endcond */
    __IO uint32_t DMASA;                 /*!< [0x0408] NFI DMA Transfer Starting Address Register                       */
    __I  uint32_t DMABCNT;               /*!< [0x040c] NFI DMA Transfer Byte Count Register                             */
    __IO uint32_t DMAINTEN;              /*!< [0x0410] NFI DMA Interrupt Enable Control Register                        */
    __I  uint32_t DMAINTSTS;             /*!< [0x0414] NFI DMA Interrupt Status Register                                */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE2[250];         /*!< [0x0418~0x07FC]                                                           */
    /** @endcond */
    __IO uint32_t GCTL;                  /*!< [0x0800] NFI Global Control and Status Register                           */
    __IO uint32_t GINTEN;                /*!< [0x0804] NFI Global Interrupt Control Register                            */
    __I  uint32_t GINTSTS;               /*!< [0x0808] NFI Global Interrupt Status Register                             */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE3[37];          /*!< [0x080C~0x089C]                                                           */
    /** @endcond */
    __IO uint32_t NANDCTL;               /*!< [0x08a0] NAND Flash Control Register                                      */
    __IO uint32_t NANDTMCTL;             /*!< [0x08a4] NAND Flash Timing Control Register                               */
    __IO uint32_t NANDINTEN;             /*!< [0x08a8] NAND Flash Interrupt Enable Register                             */
    __IO uint32_t NANDINTSTS;            /*!< [0x08ac] NAND Flash Interrupt Status Register                             */
    __O  uint32_t NANDCMD;               /*!< [0x08b0] NAND Flash Command Port Register                                 */
    __O  uint32_t NANDADDR;              /*!< [0x08b4] NAND Flash Address Port Register                                 */
    __IO uint32_t NANDDATA;              /*!< [0x08b8] NAND Flash Data Port Register                                    */
    __IO uint32_t NANDRACTL;             /*!< [0x08bc] NAND Flash Redundant Area Control Register                       */
    __IO uint32_t NANDECTL;              /*!< [0x08c0] NAND Flash Extend Control Register                               */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE4[3];           /*!< [0x08C4~0x08CC]                                                           */
    /** @endcond */
    __I  uint32_t NANDECCES[4];          /*!< [0x08d0] NAND Flash ECC Error Status 0 Register                           */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE5[8];           /*!< [0x08E0~0x08FC]                                                           */
    /** @endcond */
    __I  uint32_t NANDECCEA[12];         /*!< [0x0900] NAND Flash ECC Error Byte Address 0 Register                     */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE6[12];          /*!< [0x0930~0x095C]                                                           */
    /** @endcond */
    __I  uint32_t NANDECCED[6];          /*!< [0x0960] NAND Flash ECC Error Data Register 0                             */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE7[34];          /*!< [0x0978~0x09FC]                                                           */
    /** @endcond */
    __IO uint32_t NANDRA[118];           /*!< [0x0a00] NAND Flash Redundant Area Word n                                 */
} NFI_T;

/**
    @addtogroup NFI_CONST NFI Bit Field Definition
    Constant Definitions for NFI Controller
@{ */

#define NFI_BUFFER_Data_Pos              (0)                                               /*!< NFI_T::BUFFER0: Data Position          */
#define NFI_BUFFER_Data_Msk              (0xfffffffful << NFI_BUFFER0_Data_Pos)            /*!< NFI_T::BUFFER0: Data Mask              */

#define NFI_DMACTL_DMACEN_Pos            (0)                                               /*!< NFI_T::DMACTL: DMACEN Position         */
#define NFI_DMACTL_DMACEN_Msk            (0x1ul << NFI_DMACTL_DMACEN_Pos)                  /*!< NFI_T::DMACTL: DMACEN Mask             */

#define NFI_DMACTL_DMARST_Pos            (1)                                               /*!< NFI_T::DMACTL: DMARST Position         */
#define NFI_DMACTL_DMARST_Msk            (0x1ul << NFI_DMACTL_DMARST_Pos)                  /*!< NFI_T::DMACTL: DMARST Mask             */

#define NFI_DMACTL_SGEN_Pos              (3)                                               /*!< NFI_T::DMACTL: SGEN Position           */
#define NFI_DMACTL_SGEN_Msk              (0x1ul << NFI_DMACTL_SGEN_Pos)                    /*!< NFI_T::DMACTL: SGEN Mask               */

#define NFI_DMACTL_DMABUSY_Pos           (9)                                               /*!< NFI_T::DMACTL: DMABUSY Position        */
#define NFI_DMACTL_DMABUSY_Msk           (0x1ul << NFI_DMACTL_DMABUSY_Pos)                 /*!< NFI_T::DMACTL: DMABUSY Mask            */

#define NFI_DMASA_ORDER_Pos              (0)                                               /*!< NFI_T::DMASA: ORDER Position           */
#define NFI_DMASA_ORDER_Msk              (0x1ul << NFI_DMASA_ORDER_Pos)                    /*!< NFI_T::DMASA: ORDER Mask               */

#define NFI_DMASA_DMASA_Pos              (1)                                               /*!< NFI_T::DMASA: DMASA Position           */
#define NFI_DMASA_DMASA_Msk              (0x7ffffffful << NFI_DMASA_DMASA_Pos)             /*!< NFI_T::DMASA: DMASA Mask               */

#define NFI_DMABCNT_BCNT_Pos             (0)                                               /*!< NFI_T::DMABCNT: BCNT Position          */
#define NFI_DMABCNT_BCNT_Msk             (0x3fffffful << NFI_DMABCNT_BCNT_Pos)             /*!< NFI_T::DMABCNT: BCNT Mask              */

#define NFI_DMAINTEN_ABORTIEN_Pos        (0)                                               /*!< NFI_T::DMAINTEN: ABORTIEN Position     */
#define NFI_DMAINTEN_ABORTIEN_Msk        (0x1ul << NFI_DMAINTEN_ABORTIEN_Pos)              /*!< NFI_T::DMAINTEN: ABORTIEN Mask         */

#define NFI_DMAINTEN_WEOTIEN_Pos         (1)                                               /*!< NFI_T::DMAINTEN: WEOTIEN Position      */
#define NFI_DMAINTEN_WEOTIEN_Msk         (0x1ul << NFI_DMAINTEN_WEOTIEN_Pos)               /*!< NFI_T::DMAINTEN: WEOTIEN Mask          */

#define NFI_DMAINTSTS_ABORTIF_Pos        (0)                                               /*!< NFI_T::DMAINTSTS: ABORTIF Position     */
#define NFI_DMAINTSTS_ABORTIF_Msk        (0x1ul << NFI_DMAINTSTS_ABORTIF_Pos)              /*!< NFI_T::DMAINTSTS: ABORTIF Mask         */

#define NFI_DMAINTSTS_WEOTIF_Pos         (1)                                               /*!< NFI_T::DMAINTSTS: WEOTIF Position      */
#define NFI_DMAINTSTS_WEOTIF_Msk         (0x1ul << NFI_DMAINTSTS_WEOTIF_Pos)               /*!< NFI_T::DMAINTSTS: WEOTIF Mask          */

#define NFI_GCTL_GCTLRST_Pos             (0)                                               /*!< NFI_T::GCTL: GCTLRST Position          */
#define NFI_GCTL_GCTLRST_Msk             (0x1ul << NFI_GCTL_GCTLRST_Pos)                   /*!< NFI_T::GCTL: GCTLRST Mask              */

#define NFI_GCTL_NANDEN_Pos              (3)                                               /*!< NFI_T::GCTL: NANDEN Position           */
#define NFI_GCTL_NANDEN_Msk              (0x1ul << NFI_GCTL_NANDEN_Pos)                    /*!< NFI_T::GCTL: NANDEN Mask               */

#define NFI_GINTEN_DTAIEN_Pos            (0)                                               /*!< NFI_T::GINTEN: DTAIEN Position         */
#define NFI_GINTEN_DTAIEN_Msk            (0x1ul << NFI_GINTEN_DTAIEN_Pos)                  /*!< NFI_T::GINTEN: DTAIEN Mask             */

#define NFI_GINTSTS_DTAIF_Pos            (0)                                               /*!< NFI_T::GINTSTS: DTAIF Position         */
#define NFI_GINTSTS_DTAIF_Msk            (0x1ul << NFI_GINTSTS_DTAIF_Pos)                  /*!< NFI_T::GINTSTS: DTAIF Mask             */

#define NFI_NANDCTL_SWRST_Pos            (0)                                               /*!< NFI_T::NANDCTL: SWRST Position         */
#define NFI_NANDCTL_SWRST_Msk            (0x1ul << NFI_NANDCTL_SWRST_Pos)                  /*!< NFI_T::NANDCTL: SWRST Mask             */

#define NFI_NANDCTL_DRDEN_Pos            (1)                                               /*!< NFI_T::NANDCTL: DRDEN Position         */
#define NFI_NANDCTL_DRDEN_Msk            (0x1ul << NFI_NANDCTL_DRDEN_Pos)                  /*!< NFI_T::NANDCTL: DRDEN Mask             */

#define NFI_NANDCTL_DWREN_Pos            (2)                                               /*!< NFI_T::NANDCTL: DWREN Position         */
#define NFI_NANDCTL_DWREN_Msk            (0x1ul << NFI_NANDCTL_DWREN_Pos)                  /*!< NFI_T::NANDCTL: DWREN Mask             */

#define NFI_NANDCTL_REDUNREN_Pos         (3)                                               /*!< NFI_T::NANDCTL: REDUNREN Position      */
#define NFI_NANDCTL_REDUNREN_Msk         (0x1ul << NFI_NANDCTL_REDUNREN_Pos)               /*!< NFI_T::NANDCTL: REDUNREN Mask          */

#define NFI_NANDCTL_REDUNAUTOWEN_Pos     (4)                                               /*!< NFI_T::NANDCTL: REDUNAUTOWEN Position  */
#define NFI_NANDCTL_REDUNAUTOWEN_Msk     (0x1ul << NFI_NANDCTL_REDUNAUTOWEN_Pos)           /*!< NFI_T::NANDCTL: REDUNAUTOWEN Mask      */

#define NFI_NANDCTL_ECCCHK_Pos           (7)                                               /*!< NFI_T::NANDCTL: ECCCHK Position        */
#define NFI_NANDCTL_ECCCHK_Msk           (0x1ul << NFI_NANDCTL_ECCCHK_Pos)                 /*!< NFI_T::NANDCTL: ECCCHK Mask            */

#define NFI_NANDCTL_PROT3BEN_Pos         (8)                                               /*!< NFI_T::NANDCTL: PROT3BEN Position      */
#define NFI_NANDCTL_PROT3BEN_Msk         (0x1ul << NFI_NANDCTL_PROT3BEN_Pos)               /*!< NFI_T::NANDCTL: PROT3BEN Mask          */

#define NFI_NANDCTL_SRAMINT_Pos          (9)                                               /*!< NFI_T::NANDCTL: SRAMINT Position       */
#define NFI_NANDCTL_SRAMINT_Msk          (0x1ul << NFI_NANDCTL_SRAMINT_Pos)                /*!< NFI_T::NANDCTL: SRAMINT Mask           */

#define NFI_NANDCTL_PSIZE_Pos            (16)                                              /*!< NFI_T::NANDCTL: PSIZE Position         */
#define NFI_NANDCTL_PSIZE_Msk            (0x3ul << NFI_NANDCTL_PSIZE_Pos)                  /*!< NFI_T::NANDCTL: PSIZE Mask             */

#define NFI_NANDCTL_BCHTSEL_Pos          (18)                                              /*!< NFI_T::NANDCTL: BCHTSEL Position       */
#define NFI_NANDCTL_BCHTSEL_Msk          (0x1ful << NFI_NANDCTL_BCHTSEL_Pos)               /*!< NFI_T::NANDCTL: BCHTSEL Mask           */

#define NFI_NANDCTL_ECCEN_Pos            (23)                                              /*!< NFI_T::NANDCTL: ECCEN Position         */
#define NFI_NANDCTL_ECCEN_Msk            (0x1ul << NFI_NANDCTL_ECCEN_Pos)                  /*!< NFI_T::NANDCTL: ECCEN Mask             */

#define NFI_NANDCTL_CS0_Pos              (25)                                              /*!< NFI_T::NANDCTL: CS0 Position           */
#define NFI_NANDCTL_CS0_Msk              (0x1ul << NFI_NANDCTL_CS0_Pos)                    /*!< NFI_T::NANDCTL: CS0 Mask               */

#define NFI_NANDCTL_CS1_Pos              (26)                                              /*!< NFI_T::NANDCTL: CS1 Position           */
#define NFI_NANDCTL_CS1_Msk              (0x1ul << NFI_NANDCTL_CS1_Pos)                    /*!< NFI_T::NANDCTL: CS1 Mask               */

#define NFI_NANDTMCTL_LOWID_Pos          (0)                                               /*!< NFI_T::NANDTMCTL: LOWID Position       */
#define NFI_NANDTMCTL_LOWID_Msk          (0xfful << NFI_NANDTMCTL_LOWID_Pos)               /*!< NFI_T::NANDTMCTL: LOWID Mask           */

#define NFI_NANDTMCTL_HIWID_Pos          (8)                                               /*!< NFI_T::NANDTMCTL: HIWID Position       */
#define NFI_NANDTMCTL_HIWID_Msk          (0xfful << NFI_NANDTMCTL_HIWID_Pos)               /*!< NFI_T::NANDTMCTL: HIWID Mask           */

#define NFI_NANDTMCTL_CALESH_Pos         (16)                                              /*!< NFI_T::NANDTMCTL: CALESH Position      */
#define NFI_NANDTMCTL_CALESH_Msk         (0x7ful << NFI_NANDTMCTL_CALESH_Pos)              /*!< NFI_T::NANDTMCTL: CALESH Mask          */

#define NFI_NANDTMCTL_EDOD_Pos           (24)                                              /*!< NFI_T::NANDTMCTL: EDOD Position        */
#define NFI_NANDTMCTL_EDOD_Msk           (0xful << NFI_NANDTMCTL_EDOD_Pos)                 /*!< NFI_T::NANDTMCTL: EDOD Mask            */

#define NFI_NANDTMCTL_EDOEN_Pos          (31)                                              /*!< NFI_T::NANDTMCTL: EDOEN Position       */
#define NFI_NANDTMCTL_EDOEN_Msk          (0x1ul << NFI_NANDTMCTL_EDOEN_Pos)                /*!< NFI_T::NANDTMCTL: EDOEN Mask           */

#define NFI_NANDINTEN_DMAIE_Pos          (0)                                               /*!< NFI_T::NANDINTEN: DMAIE Position       */
#define NFI_NANDINTEN_DMAIE_Msk          (0x1ul << NFI_NANDINTEN_DMAIE_Pos)                /*!< NFI_T::NANDINTEN: DMAIE Mask           */

#define NFI_NANDINTEN_ECCFLDIE_Pos       (2)                                               /*!< NFI_T::NANDINTEN: ECCFLDIE Position    */
#define NFI_NANDINTEN_ECCFLDIE_Msk       (0x1ul << NFI_NANDINTEN_ECCFLDIE_Pos)             /*!< NFI_T::NANDINTEN: ECCFLDIE Mask        */

#define NFI_NANDINTEN_RB0IE_Pos          (10)                                              /*!< NFI_T::NANDINTEN: RB0IE Position       */
#define NFI_NANDINTEN_RB0IE_Msk          (0x1ul << NFI_NANDINTEN_RB0IE_Pos)                /*!< NFI_T::NANDINTEN: RB0IE Mask           */

#define NFI_NANDINTSTS_DMAIF_Pos         (0)                                               /*!< NFI_T::NANDINTSTS: DMAIF Position      */
#define NFI_NANDINTSTS_DMAIF_Msk         (0x1ul << NFI_NANDINTSTS_DMAIF_Pos)               /*!< NFI_T::NANDINTSTS: DMAIF Mask          */

#define NFI_NANDINTSTS_ECCFLDIF_Pos      (2)                                               /*!< NFI_T::NANDINTSTS: ECCFLDIF Position   */
#define NFI_NANDINTSTS_ECCFLDIF_Msk      (0x1ul << NFI_NANDINTSTS_ECCFLDIF_Pos)            /*!< NFI_T::NANDINTSTS: ECCFLDIF Mask       */

#define NFI_NANDINTSTS_EDOF_Pos          (4)                                               /*!< NFI_T::NANDINTSTS: EDOF Position       */
#define NFI_NANDINTSTS_EDOF_Msk          (0x1ul << NFI_NANDINTSTS_EDOF_Pos)                /*!< NFI_T::NANDINTSTS: EDOF Mask           */

#define NFI_NANDINTSTS_RB0IF_Pos         (10)                                              /*!< NFI_T::NANDINTSTS: RB0IF Position      */
#define NFI_NANDINTSTS_RB0IF_Msk         (0x1ul << NFI_NANDINTSTS_RB0IF_Pos)               /*!< NFI_T::NANDINTSTS: RB0IF Mask          */

#define NFI_NANDINTSTS_RB0Status_Pos     (18)                                              /*!< NFI_T::NANDINTSTS: RB0Status Position  */
#define NFI_NANDINTSTS_RB0Status_Msk     (0x1ul << NFI_NANDINTSTS_RB0Status_Pos)           /*!< NFI_T::NANDINTSTS: RB0Status Mask      */

#define NFI_NANDCMD_COMMAND_Pos          (0)                                               /*!< NFI_T::NANDCMD: COMMAND Position       */
#define NFI_NANDCMD_COMMAND_Msk          (0xfful << NFI_NANDCMD_COMMAND_Pos)               /*!< NFI_T::NANDCMD: COMMAND Mask           */

#define NFI_NANDADDR_ADDRESS_Pos         (0)                                               /*!< NFI_T::NANDADDR: ADDRESS Position      */
#define NFI_NANDADDR_ADDRESS_Msk         (0xfful << NFI_NANDADDR_ADDRESS_Pos)              /*!< NFI_T::NANDADDR: ADDRESS Mask          */

#define NFI_NANDADDR_EOA_Pos             (31)                                              /*!< NFI_T::NANDADDR: EOA Position          */
#define NFI_NANDADDR_EOA_Msk             (0x1ul << NFI_NANDADDR_EOA_Pos)                   /*!< NFI_T::NANDADDR: EOA Mask              */

#define NFI_NANDDATA_DATA_Pos            (0)                                               /*!< NFI_T::NANDDATA: DATA Position         */
#define NFI_NANDDATA_DATA_Msk            (0xfful << NFI_NANDDATA_DATA_Pos)                 /*!< NFI_T::NANDDATA: DATA Mask             */

#define NFI_NANDRACTL_RA128EN_Pos        (0)                                               /*!< NFI_T::NANDRACTL: RA128EN Position     */
#define NFI_NANDRACTL_RA128EN_Msk        (0x1fful << NFI_NANDRACTL_RA128EN_Pos)            /*!< NFI_T::NANDRACTL: RA128EN Mask         */

#define NFI_NANDRACTL_MECC_Pos           (16)                                              /*!< NFI_T::NANDRACTL: MECC Position        */
#define NFI_NANDRACTL_MECC_Msk           (0xfffful << NFI_NANDRACTL_MECC_Pos)              /*!< NFI_T::NANDRACTL: MECC Mask            */

#define NFI_NANDECTL_WP_Pos              (0)                                               /*!< NFI_T::NANDECTL: WP Position           */
#define NFI_NANDECTL_WP_Msk              (0x1ul << NFI_NANDECTL_WP_Pos)                    /*!< NFI_T::NANDECTL: WP Mask               */

#define NFI_NANDECCES_F1STAT_Pos         (0)                                               /*!< NFI_T::NANDECCES: F1STAT Position     */
#define NFI_NANDECCES_F1STAT_Msk         (0x3ul << NFI_NANDECCES_F1STAT_Pos)               /*!< NFI_T::NANDECCES: F1STAT Mask         */

#define NFI_NANDECCES_F1ECNT_Pos         (2)                                               /*!< NFI_T::NANDECCES: F1ECNT Position     */
#define NFI_NANDECCES_F1ECNT_Msk         (0x1ful << NFI_NANDECCES_F1ECNT_Pos)              /*!< NFI_T::NANDECCES: F1ECNT Mask         */

#define NFI_NANDECCES_F2STAT_Pos         (8)                                               /*!< NFI_T::NANDECCES: F2STAT Position     */
#define NFI_NANDECCES_F2STAT_Msk         (0x3ul << NFI_NANDECCES_F2STAT_Pos)               /*!< NFI_T::NANDECCES: F2STAT Mask         */

#define NFI_NANDECCES_F2ECNT_Pos         (10)                                              /*!< NFI_T::NANDECCES: F2ECNT Position     */
#define NFI_NANDECCES_F2ECNT_Msk         (0x1ful << NFI_NANDECCES_F2ECNT_Pos)              /*!< NFI_T::NANDECCES: F2ECNT Mask         */

#define NFI_NANDECCES_F3STAT_Pos         (16)                                              /*!< NFI_T::NANDECCES: F3STAT Position     */
#define NFI_NANDECCES_F3STAT_Msk         (0x3ul << NFI_NANDECCES_F3STAT_Pos)               /*!< NFI_T::NANDECCES: F3STAT Mask         */

#define NFI_NANDECCES_F3ECNT_Pos         (18)                                              /*!< NFI_T::NANDECCES: F3ECNT Position     */
#define NFI_NANDECCES_F3ECNT_Msk         (0x1ful << NFI_NANDECCES_F3ECNT_Pos)              /*!< NFI_T::NANDECCES: F3ECNT Mask         */

#define NFI_NANDECCES_F4STAT_Pos         (24)                                              /*!< NFI_T::NANDECCES: F4STAT Position     */
#define NFI_NANDECCES_F4STAT_Msk         (0x3ul << NFI_NANDECCES_F4STAT_Pos)               /*!< NFI_T::NANDECCES: F4STAT Mask         */

#define NFI_NANDECCES_F4ECNT_Pos         (26)                                              /*!< NFI_T::NANDECCES: F4ECNT Position     */
#define NFI_NANDECCES_F4ECNT_Msk         (0x1ful << NFI_NANDECCES_F4ECNT_Pos)              /*!< NFI_T::NANDECCES: F4ECNT Mask         */

#define NFI_NANDRA_Data_Pos              (0)                                               /*!< NFI_T::NANDRA: Data Position          */
#define NFI_NANDRA_Data_Msk              (0xfffffffful << NFI_NANDRA_Data_Pos)             /*!< NFI_T::NANDRA: Data Mask              */

/**@}*/ /* NFI_CONST */
/**@}*/ /* end of NFI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __NFI_REG_H__ */
