/*
 * Copyright (C) 2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
 */

#ifndef __HW_USDHC_REGISTERS_H__
#define __HW_USDHC_REGISTERS_H__

#include "regs.h"

/*
 * i.MX6UL USDHC registers defined in this header file.
 *
 * - HW_USDHC_DS_ADDR - DMA System Address
 * - HW_USDHC_BLK_ATT - Block Attributes
 * - HW_USDHC_CMD_ARG - Command Argument
 * - HW_USDHC_CMD_XFR_TYP - Command Transfer Type
 * - HW_USDHC_CMD_RSP0 - Command Response0
 * - HW_USDHC_CMD_RSP1 - Command Response1
 * - HW_USDHC_CMD_RSP2 - Command Response2
 * - HW_USDHC_CMD_RSP3 - Command Response3
 * - HW_USDHC_DATA_BUFF_ACC_PORT - Data Buffer Access Port
 * - HW_USDHC_PRES_STATE - Present State
 * - HW_USDHC_PROT_CTRL - Protocol Control
 * - HW_USDHC_SYS_CTRL - System Control
 * - HW_USDHC_INT_STATUS - Interrupt Status
 * - HW_USDHC_INT_STATUS_EN - Interrupt Status Enable
 * - HW_USDHC_INT_SIGNAL_EN - Interrupt Signal Enable
 * - HW_USDHC_AUTOCMD12_ERR_STATUS - Auto CMD12 Error Status
 * - HW_USDHC_HOST_CTRL_CAP - Host Controller Capabilities
 * - HW_USDHC_WTMK_LVL - Watermark Level
 * - HW_USDHC_MIX_CTRL - Mixer Control
 * - HW_USDHC_FORCE_EVENT - Force Event
 * - HW_USDHC_ADMA_ERR_STATUS - ADMA Error Status Register
 * - HW_USDHC_ADMA_SYS_ADDR - ADMA System Address
 * - HW_USDHC_DLL_CTRL - DLL (Delay Line) Control
 * - HW_USDHC_DLL_STATUS - DLL Status
 * - HW_USDHC_CLK_TUNE_CTRL_STATUS - CLK Tuning Control and Status
 * - HW_USDHC_VEND_SPEC - Vendor Specific Register
 * - HW_USDHC_MMC_BOOT - MMC Boot Register
 * - HW_USDHC_VEND_SPEC2 - Vendor Specific 2 Register
 * - HW_USDHC_HOST_CTRL_VER - Host Controller Version
 *
 * - hw_usdhc_t - Struct containing all module registers.
 */

//! @name Module base addresses
//@{
#ifndef REGS_USDHC_BASE
#define HW_USDHC_INSTANCE_COUNT (4) //!< Number of instances of the USDHC module.
#define HW_USDHC1 (1) //!< Instance number for USDHC1.
#define HW_USDHC2 (2) //!< Instance number for USDHC2.
#define HW_USDHC3 (3) //!< Instance number for USDHC3.
#define HW_USDHC4 (4) //!< Instance number for USDHC4.

#define REGS_USDHC1_BASE (0x02190000) //!< Base address for USDHC instance number 1.
#define REGS_USDHC2_BASE (0x02194000) //!< Base address for USDHC instance number 2.
#define REGS_USDHC3_BASE (0x02198000) //!< Base address for USDHC instance number 3.
#define REGS_USDHC4_BASE (0x0219c000) //!< Base address for USDHC instance number 4.

//! @brief Get the base address of USDHC by instance number.
//! @param x USDHC instance number, from 1 through 4.
#define REGS_USDHC_BASE(x) ( (x) == HW_USDHC1 ? REGS_USDHC1_BASE : (x) == HW_USDHC2 ? REGS_USDHC2_BASE : (x) == HW_USDHC3 ? REGS_USDHC3_BASE : (x) == HW_USDHC4 ? REGS_USDHC4_BASE : 0x00d00000)

//! @brief Get the instance number given a base address.
//! @param b Base address for an instance of USDHC.
#define REGS_USDHC_INSTANCE(b) ( (b) == REGS_USDHC1_BASE ? HW_USDHC1 : (b) == REGS_USDHC2_BASE ? HW_USDHC2 : (b) == REGS_USDHC3_BASE ? HW_USDHC3 : (b) == REGS_USDHC4_BASE ? HW_USDHC4 : 0)
#endif
//@}


//-------------------------------------------------------------------------------------------
// HW_USDHC_DS_ADDR - DMA System Address
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_DS_ADDR - DMA System Address (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains the physical system memory address used for DMA transfers.
 */
typedef union _hw_usdhc_ds_addr
{
    reg32_t U;
    struct _hw_usdhc_ds_addr_bitfields
    {
        unsigned RESERVED0 : 2; //!< [1:0] Reserved
        unsigned DS_ADDR : 30; //!< [31:2] DMA System Address: This register contains the 32-bit system memory address for a DMA transfer.
    } B;
} hw_usdhc_ds_addr_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_DS_ADDR register
 */
#define HW_USDHC_DS_ADDR_ADDR(x)      (REGS_USDHC_BASE(x) + 0x0)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_DS_ADDR(x)           (*(volatile hw_usdhc_ds_addr_t *) HW_USDHC_DS_ADDR_ADDR(x))
#define HW_USDHC_DS_ADDR_RD(x)        (HW_USDHC_DS_ADDR(x).U)
#define HW_USDHC_DS_ADDR_WR(x, v)     (HW_USDHC_DS_ADDR(x).U = (v))
#define HW_USDHC_DS_ADDR_SET(x, v)    (HW_USDHC_DS_ADDR_WR(x, HW_USDHC_DS_ADDR_RD(x) |  (v)))
#define HW_USDHC_DS_ADDR_CLR(x, v)    (HW_USDHC_DS_ADDR_WR(x, HW_USDHC_DS_ADDR_RD(x) & ~(v)))
#define HW_USDHC_DS_ADDR_TOG(x, v)    (HW_USDHC_DS_ADDR_WR(x, HW_USDHC_DS_ADDR_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_DS_ADDR bitfields
 */

/* --- Register HW_USDHC_DS_ADDR, field DS_ADDR[31:2] (RW)
 *
 * DMA System Address: This register contains the 32-bit system memory address for a DMA transfer.
 * Since the address must be word (4 bytes) align, the least 2 bits are reserved, always 0. When the
 * uSDHC stops a DMA transfer, this register points to the system address of the next contiguous
 * data position. It can be accessed only when no transaction is executing (i.e. after a transaction
 * has stopped). Read operation during transfers may return an invalid value. The Host Driver shall
 * initialize this register before starting a DMA transaction. After DMA has stopped, the system
 * address of the next contiguous data position can be read from this register. This register is
 * protected during a data transfer. When data lines are active, write to this register is ignored.
 * The Host driver shall wait, until the DLA bit in the Present State register is cleared, before
 * writing to this register. The uSDHC internal DMA does not support a virtual memory system. It
 * only supports continuous physical memory access. And due to AHB burst limitations, if the burst
 * must cross the 1 KB boundary, uSDHC will automatically change SEQ burst type to NSEQ. Since this
 * register supports dynamic address reflecting, when TC bit is set, it automatically alters the
 * value of internal address counter, so SW cannot change this register when TC bit is set. Such
 * restriction is also listed in .
 */

#define BP_USDHC_DS_ADDR_DS_ADDR      (2)      //!< Bit position for USDHC_DS_ADDR_DS_ADDR.
#define BM_USDHC_DS_ADDR_DS_ADDR      (0xfffffffc)  //!< Bit mask for USDHC_DS_ADDR_DS_ADDR.

//! @brief Get value of USDHC_DS_ADDR_DS_ADDR from a register value.
#define BG_USDHC_DS_ADDR_DS_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DS_ADDR_DS_ADDR) >> BP_USDHC_DS_ADDR_DS_ADDR)

//! @brief Format value for bitfield USDHC_DS_ADDR_DS_ADDR.
#define BF_USDHC_DS_ADDR_DS_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DS_ADDR_DS_ADDR) & BM_USDHC_DS_ADDR_DS_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DS_ADDR field to a new value.
#define BW_USDHC_DS_ADDR_DS_ADDR(x, v)   (HW_USDHC_DS_ADDR_WR(x, (HW_USDHC_DS_ADDR_RD(x) & ~BM_USDHC_DS_ADDR_DS_ADDR) | BF_USDHC_DS_ADDR_DS_ADDR(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_BLK_ATT - Block Attributes
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_BLK_ATT - Block Attributes (RW)
 *
 * Reset value: 0x00000000
 *
 * This register is used to configure the number of data blocks and the number of bytes in each
 * block.
 */
typedef union _hw_usdhc_blk_att
{
    reg32_t U;
    struct _hw_usdhc_blk_att_bitfields
    {
        unsigned BLKSIZE : 13; //!< [12:0] Transfer Block Size: This register specifies the block size for block data transfers.
        unsigned RESERVED0 : 3; //!< [15:13] Reserved
        unsigned BLKCNT : 16; //!< [31:16] Blocks Count For Current Transfer: This register is enabled when the Block Count Enable bit in the Transfer Mode register is set to 1 and is valid only for multiple block transfers.
    } B;
} hw_usdhc_blk_att_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_BLK_ATT register
 */
#define HW_USDHC_BLK_ATT_ADDR(x)      (REGS_USDHC_BASE(x) + 0x4)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_BLK_ATT(x)           (*(volatile hw_usdhc_blk_att_t *) HW_USDHC_BLK_ATT_ADDR(x))
#define HW_USDHC_BLK_ATT_RD(x)        (HW_USDHC_BLK_ATT(x).U)
#define HW_USDHC_BLK_ATT_WR(x, v)     (HW_USDHC_BLK_ATT(x).U = (v))
#define HW_USDHC_BLK_ATT_SET(x, v)    (HW_USDHC_BLK_ATT_WR(x, HW_USDHC_BLK_ATT_RD(x) |  (v)))
#define HW_USDHC_BLK_ATT_CLR(x, v)    (HW_USDHC_BLK_ATT_WR(x, HW_USDHC_BLK_ATT_RD(x) & ~(v)))
#define HW_USDHC_BLK_ATT_TOG(x, v)    (HW_USDHC_BLK_ATT_WR(x, HW_USDHC_BLK_ATT_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_BLK_ATT bitfields
 */

/* --- Register HW_USDHC_BLK_ATT, field BLKSIZE[12:0] (RW)
 *
 * Transfer Block Size: This register specifies the block size for block data transfers. Values
 * ranging from 1 byte up to the maximum buffer size can be set. It can be accessed only when no
 * transaction is executing (i.e. after a transaction has stopped). Read operations during transfers
 * may return an invalid value, and write operations will be ignored.
 *
 * Values:
 * 000 - No data transfer
 * 001 - 1 Byte
 * 002 - 2 Bytes
 * 003 - 3 Bytes
 * 004 - 4 Bytes
 * 200 - 512 Bytes
 * 1FF - 511 Bytes
 * 800 - 2048 Bytes
 * 1000 - 4096 Bytes
 */

#define BP_USDHC_BLK_ATT_BLKSIZE      (0)      //!< Bit position for USDHC_BLK_ATT_BLKSIZE.
#define BM_USDHC_BLK_ATT_BLKSIZE      (0x00001fff)  //!< Bit mask for USDHC_BLK_ATT_BLKSIZE.

//! @brief Get value of USDHC_BLK_ATT_BLKSIZE from a register value.
#define BG_USDHC_BLK_ATT_BLKSIZE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_BLK_ATT_BLKSIZE) >> BP_USDHC_BLK_ATT_BLKSIZE)

//! @brief Format value for bitfield USDHC_BLK_ATT_BLKSIZE.
#define BF_USDHC_BLK_ATT_BLKSIZE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_BLK_ATT_BLKSIZE) & BM_USDHC_BLK_ATT_BLKSIZE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BLKSIZE field to a new value.
#define BW_USDHC_BLK_ATT_BLKSIZE(x, v)   (HW_USDHC_BLK_ATT_WR(x, (HW_USDHC_BLK_ATT_RD(x) & ~BM_USDHC_BLK_ATT_BLKSIZE) | BF_USDHC_BLK_ATT_BLKSIZE(v)))
#endif


/* --- Register HW_USDHC_BLK_ATT, field BLKCNT[31:16] (RW)
 *
 * Blocks Count For Current Transfer: This register is enabled when the Block Count Enable bit in
 * the Transfer Mode register is set to 1 and is valid only for multiple block transfers. For single
 * block transfer, this register will always read as 1. The Host Driver shall set this register to a
 * value between 1 and the maximum block count. The uSDHC decrements the block count after each
 * block transfer and stops when the count reaches zero. Setting the block count to 0 results in no
 * data blocks being transferred. This register should be accessed only when no transaction is
 * executing (i.e. after transactions are stopped). During data transfer, read operations on this
 * register may return an invalid value and write operations are ignored. When saving transfer
 * content as a result of a Suspend command, the number of blocks yet to be transferred can be
 * determined by reading this register. The reading of this register should be applied after
 * transfer is paused by stop at block gap operation and before sending the command marked as
 * suspend. This is because when Suspend command is sent out, uSDHC will regard the current transfer
 * is aborted and change BLKCNT register back to its original value instead of keeping the dynamical
 * indicator of remained block count. When restoring transfer content prior to issuing a Resume
 * command, the Host Driver shall restore the previously saved block count. Although the BLKCNT
 * field is 0 after reset, the read of reset value is 0x1. This is because when MSBSEL bit is 鈥?鈥?
 * indicating a single block transfer, the read value of BLKCNT is always 1.
 *
 * Values:
 * 0000 - Stop Count
 * 0001 - 1 block
 * 0002 - 2 blocks
 * FFFF - 65535 blocks
 */

#define BP_USDHC_BLK_ATT_BLKCNT      (16)      //!< Bit position for USDHC_BLK_ATT_BLKCNT.
#define BM_USDHC_BLK_ATT_BLKCNT      (0xffff0000)  //!< Bit mask for USDHC_BLK_ATT_BLKCNT.

//! @brief Get value of USDHC_BLK_ATT_BLKCNT from a register value.
#define BG_USDHC_BLK_ATT_BLKCNT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_BLK_ATT_BLKCNT) >> BP_USDHC_BLK_ATT_BLKCNT)

//! @brief Format value for bitfield USDHC_BLK_ATT_BLKCNT.
#define BF_USDHC_BLK_ATT_BLKCNT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_BLK_ATT_BLKCNT) & BM_USDHC_BLK_ATT_BLKCNT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BLKCNT field to a new value.
#define BW_USDHC_BLK_ATT_BLKCNT(x, v)   (HW_USDHC_BLK_ATT_WR(x, (HW_USDHC_BLK_ATT_RD(x) & ~BM_USDHC_BLK_ATT_BLKCNT) | BF_USDHC_BLK_ATT_BLKCNT(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_ARG - Command Argument
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_ARG - Command Argument (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains the SD/MMC Command Argument.  .
 */
typedef union _hw_usdhc_cmd_arg
{
    reg32_t U;
    struct _hw_usdhc_cmd_arg_bitfields
    {
        unsigned CMDARG : 32; //!< [31:0] Command Argument: The SD/MMC Command Argument is specified as bits 39-8 of the Command Format in the SD or MMC Specification.This register is write protected when the Command Inhibit (CMD) bit in the Present State register is set.
    } B;
} hw_usdhc_cmd_arg_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_ARG register
 */
#define HW_USDHC_CMD_ARG_ADDR(x)      (REGS_USDHC_BASE(x) + 0x8)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_ARG(x)           (*(volatile hw_usdhc_cmd_arg_t *) HW_USDHC_CMD_ARG_ADDR(x))
#define HW_USDHC_CMD_ARG_RD(x)        (HW_USDHC_CMD_ARG(x).U)
#define HW_USDHC_CMD_ARG_WR(x, v)     (HW_USDHC_CMD_ARG(x).U = (v))
#define HW_USDHC_CMD_ARG_SET(x, v)    (HW_USDHC_CMD_ARG_WR(x, HW_USDHC_CMD_ARG_RD(x) |  (v)))
#define HW_USDHC_CMD_ARG_CLR(x, v)    (HW_USDHC_CMD_ARG_WR(x, HW_USDHC_CMD_ARG_RD(x) & ~(v)))
#define HW_USDHC_CMD_ARG_TOG(x, v)    (HW_USDHC_CMD_ARG_WR(x, HW_USDHC_CMD_ARG_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_CMD_ARG bitfields
 */

/* --- Register HW_USDHC_CMD_ARG, field CMDARG[31:0] (RW)
 *
 * Command Argument: The SD/MMC Command Argument is specified as bits 39-8 of the Command Format in
 * the SD or MMC Specification.This register is write protected when the Command Inhibit (CMD) bit
 * in the Present State register is set.
 */

#define BP_USDHC_CMD_ARG_CMDARG      (0)      //!< Bit position for USDHC_CMD_ARG_CMDARG.
#define BM_USDHC_CMD_ARG_CMDARG      (0xffffffff)  //!< Bit mask for USDHC_CMD_ARG_CMDARG.

//! @brief Get value of USDHC_CMD_ARG_CMDARG from a register value.
#define BG_USDHC_CMD_ARG_CMDARG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_ARG_CMDARG) >> BP_USDHC_CMD_ARG_CMDARG)

//! @brief Format value for bitfield USDHC_CMD_ARG_CMDARG.
#define BF_USDHC_CMD_ARG_CMDARG(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_ARG_CMDARG) & BM_USDHC_CMD_ARG_CMDARG)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMDARG field to a new value.
#define BW_USDHC_CMD_ARG_CMDARG(x, v)   (HW_USDHC_CMD_ARG_WR(x, (HW_USDHC_CMD_ARG_RD(x) & ~BM_USDHC_CMD_ARG_CMDARG) | BF_USDHC_CMD_ARG_CMDARG(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_XFR_TYP - Command Transfer Type
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_XFR_TYP - Command Transfer Type (RW)
 *
 * Reset value: 0x00000000
 *
 * This register is used to control the operation of data transfers. The Host Driver shall set this
 * register before issuing a command followed by a data transfer, or before issuing a Resume
 * command. To prevent data loss, the uSDHC prevents writing to the bits, that are involved in the
 * data transfer of this register, when data transfer is active. These bits are DPSEL, MBSEL,
 * DTDSEL, AC12EN, BCEN and DMAEN.  The Host Driver shall check the Command Inhibit DAT bit (CDIHB)
 * and the Command Inhibit CMD bit (CIHB) in the Present State register before writing to this
 * register. When the CDIHB bit in the Present State register is set, any attempt to send a command
 * with data by writing to this register is ignored; when the CIHB bit is set, any write to this
 * register is ignored.  On sending commands with data transfer invovled, it is mandatory that the
 * block size is non-zero. Besides, block count must also be non-zero, or indicated as single block
 * transfer (bit 5 of this register is '0' when written), or block count is disabled (bit 1 of this
 * register is '0' when written), otherwise uSDHC will ignore the sending of this command and do
 * nothing. For write command, with all above restrictions, it is also mandatory that the write
 * protect switch is not active (WPSPL bit of Present State Register is '1), otherwise uSDHC will
 * also ignore the command.  If the commands with data transfer does not receive the response in 64
 * clock cycles, i.e., response time-out, uSDHC will regard the external device does not accept the
 * command and abort the data transfer. In this scenario, the driver should issue the command again
 * to re-try the transfer. It is also possible that for some reason the card responds the command
 * but uSDHC does not receive the response, and if it is internal DMA (either simple DMA or ADMA)
 * read operation, the external system memory is over-written by the internal DMA with data sent
 * back from the card.  The table below shows the summary of how register settings determine the
 * type of data transfer.   Transfer Type Register Setting for Various Transfer Types
 * Multi/Single Block Select    Block Count Enable    Block Count    Function        0    Don't Care
 * Don't Care    Single Transfer      1    0    Don't Care    Infinite Transfer      1    1
 * Positive Number    Multiple Transfer      1    1    Zero    No Data Transfer       The table
 * belowshows the relationship between the Command Index Check Enable and the Command CRC Check
 * Enable, in regards to the Response Type bits as well as the name of the response type.
 * Relationship Between Parameters and the Name of the Response Type          Response Type    Index
 * Check Enable    CRC Check Enable    Name of Response Type        00    0    0    No Response
 * 01    0    1    R2      10    0    0    R3,R4      10    1    1    R1,R5,R6      11    1    1
 * R1b,R5b        In the SDIO specification, response type notation for R5b is not defined. R5
 * includes R5b in the SDIO specification. But R5b is defined in this specification to specify that
 * the uSDHC will check the busy status after receiving a response. For example, usually CMD52 is
 * used with R5, but the I/O abort command shall be used with R5b.  The CRC field for R3 and R4 is
 * expected to be all 1 bits. The CRC check shall be disabled for these response types.
 */
typedef union _hw_usdhc_cmd_xfr_typ
{
    reg32_t U;
    struct _hw_usdhc_cmd_xfr_typ_bitfields
    {
        unsigned RESERVED0 : 16; //!< [15:0] Reserved
        unsigned RSPTYP : 2; //!< [17:16] Response Type Select:
        unsigned RESERVED1 : 1; //!< [18] Reserved
        unsigned CCCEN : 1; //!< [19] Command CRC Check Enable: If this bit is set to 1, the uSDHC shall check the CRC field in the response.
        unsigned CICEN : 1; //!< [20] Command Index Check Enable: If this bit is set to 1, the uSDHC will check the Index field in the response to see if it has the same value as the command index.
        unsigned DPSEL : 1; //!< [21] Data Present Select: This bit is set to 1 to indicate that data is present and shall be transferred using the DAT line.
        unsigned CMDTYP : 2; //!< [23:22] Command Type: There are three types of special commands: Suspend, Resume and Abort.
        unsigned CMDINX : 6; //!< [29:24] Command Index: These bits shall be set to the command number that is specified in bits 45-40 of the Command-Format in the SD Memory Card Physical Layer Specification and SDIO Card Specification.
        unsigned RESERVED2 : 2; //!< [31:30] Reserved
    } B;
} hw_usdhc_cmd_xfr_typ_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_XFR_TYP register
 */
#define HW_USDHC_CMD_XFR_TYP_ADDR(x)      (REGS_USDHC_BASE(x) + 0xc)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_XFR_TYP(x)           (*(volatile hw_usdhc_cmd_xfr_typ_t *) HW_USDHC_CMD_XFR_TYP_ADDR(x))
#define HW_USDHC_CMD_XFR_TYP_RD(x)        (HW_USDHC_CMD_XFR_TYP(x).U)
#define HW_USDHC_CMD_XFR_TYP_WR(x, v)     (HW_USDHC_CMD_XFR_TYP(x).U = (v))
#define HW_USDHC_CMD_XFR_TYP_SET(x, v)    (HW_USDHC_CMD_XFR_TYP_WR(x, HW_USDHC_CMD_XFR_TYP_RD(x) |  (v)))
#define HW_USDHC_CMD_XFR_TYP_CLR(x, v)    (HW_USDHC_CMD_XFR_TYP_WR(x, HW_USDHC_CMD_XFR_TYP_RD(x) & ~(v)))
#define HW_USDHC_CMD_XFR_TYP_TOG(x, v)    (HW_USDHC_CMD_XFR_TYP_WR(x, HW_USDHC_CMD_XFR_TYP_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_CMD_XFR_TYP bitfields
 */

/* --- Register HW_USDHC_CMD_XFR_TYP, field RSPTYP[17:16] (RW)
 *
 * Response Type Select:
 *
 * Values:
 * 00 - No Response
 * 01 - Response Length 136
 * 10 - Response Length 48
 * 11 - Response Length 48, check Busy after response
 */

#define BP_USDHC_CMD_XFR_TYP_RSPTYP      (16)      //!< Bit position for USDHC_CMD_XFR_TYP_RSPTYP.
#define BM_USDHC_CMD_XFR_TYP_RSPTYP      (0x00030000)  //!< Bit mask for USDHC_CMD_XFR_TYP_RSPTYP.

//! @brief Get value of USDHC_CMD_XFR_TYP_RSPTYP from a register value.
#define BG_USDHC_CMD_XFR_TYP_RSPTYP(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_RSPTYP) >> BP_USDHC_CMD_XFR_TYP_RSPTYP)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_RSPTYP.
#define BF_USDHC_CMD_XFR_TYP_RSPTYP(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_RSPTYP) & BM_USDHC_CMD_XFR_TYP_RSPTYP)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RSPTYP field to a new value.
#define BW_USDHC_CMD_XFR_TYP_RSPTYP(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_RSPTYP) | BF_USDHC_CMD_XFR_TYP_RSPTYP(v)))
#endif


/* --- Register HW_USDHC_CMD_XFR_TYP, field CCCEN[19] (RW)
 *
 * Command CRC Check Enable: If this bit is set to 1, the uSDHC shall check the CRC field in the
 * response. If an error is detected, it is reported as a Command CRC Error. If this bit is set to
 * 0, the CRC field is not checked. The number of bits checked by the CRC field value changes
 * according to the length of the response. (Refer to RSPTYP[1:0] and .)
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_CMD_XFR_TYP_CCCEN      (19)      //!< Bit position for USDHC_CMD_XFR_TYP_CCCEN.
#define BM_USDHC_CMD_XFR_TYP_CCCEN      (0x00080000)  //!< Bit mask for USDHC_CMD_XFR_TYP_CCCEN.

//! @brief Get value of USDHC_CMD_XFR_TYP_CCCEN from a register value.
#define BG_USDHC_CMD_XFR_TYP_CCCEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_CCCEN) >> BP_USDHC_CMD_XFR_TYP_CCCEN)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_CCCEN.
#define BF_USDHC_CMD_XFR_TYP_CCCEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_CCCEN) & BM_USDHC_CMD_XFR_TYP_CCCEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCCEN field to a new value.
#define BW_USDHC_CMD_XFR_TYP_CCCEN(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_CCCEN) | BF_USDHC_CMD_XFR_TYP_CCCEN(v)))
#endif


/* --- Register HW_USDHC_CMD_XFR_TYP, field CICEN[20] (RW)
 *
 * Command Index Check Enable: If this bit is set to 1, the uSDHC will check the Index field in the
 * response to see if it has the same value as the command index. If it is not, it is reported as a
 * Command Index Error. If this bit is set to 0, the Index field is not checked.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_CMD_XFR_TYP_CICEN      (20)      //!< Bit position for USDHC_CMD_XFR_TYP_CICEN.
#define BM_USDHC_CMD_XFR_TYP_CICEN      (0x00100000)  //!< Bit mask for USDHC_CMD_XFR_TYP_CICEN.

//! @brief Get value of USDHC_CMD_XFR_TYP_CICEN from a register value.
#define BG_USDHC_CMD_XFR_TYP_CICEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_CICEN) >> BP_USDHC_CMD_XFR_TYP_CICEN)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_CICEN.
#define BF_USDHC_CMD_XFR_TYP_CICEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_CICEN) & BM_USDHC_CMD_XFR_TYP_CICEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CICEN field to a new value.
#define BW_USDHC_CMD_XFR_TYP_CICEN(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_CICEN) | BF_USDHC_CMD_XFR_TYP_CICEN(v)))
#endif


/* --- Register HW_USDHC_CMD_XFR_TYP, field DPSEL[21] (RW)
 *
 * Data Present Select: This bit is set to 1 to indicate that data is present and shall be
 * transferred using the DAT line. It is set to 0 for the following: Commands using only the CMD
 * line (e.g. CMD52). Commands with no data transfer, but using the busy signal on DAT[0] line (R1b
 * or R5b e.g. CMD38) Note: In resume command, this bit shall be set, and other bits in this
 * register shall be set the same as when the transfer was initially launched. When the Write
 * Protect switch is on, (i.e. the WPSPL bit is active as '0'), any command with a write operation
 * will be ignored. That is to say, when this bit is set, while the DTDSEL bit is 0, writes to the
 * register Transfer Type are ignored.
 *
 * Values:
 * 0 - No Data Present
 * 1 - Data Present
 */

#define BP_USDHC_CMD_XFR_TYP_DPSEL      (21)      //!< Bit position for USDHC_CMD_XFR_TYP_DPSEL.
#define BM_USDHC_CMD_XFR_TYP_DPSEL      (0x00200000)  //!< Bit mask for USDHC_CMD_XFR_TYP_DPSEL.

//! @brief Get value of USDHC_CMD_XFR_TYP_DPSEL from a register value.
#define BG_USDHC_CMD_XFR_TYP_DPSEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_DPSEL) >> BP_USDHC_CMD_XFR_TYP_DPSEL)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_DPSEL.
#define BF_USDHC_CMD_XFR_TYP_DPSEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_DPSEL) & BM_USDHC_CMD_XFR_TYP_DPSEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DPSEL field to a new value.
#define BW_USDHC_CMD_XFR_TYP_DPSEL(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_DPSEL) | BF_USDHC_CMD_XFR_TYP_DPSEL(v)))
#endif


/* --- Register HW_USDHC_CMD_XFR_TYP, field CMDTYP[23:22] (RW)
 *
 * Command Type: There are three types of special commands: Suspend, Resume and Abort. These bits
 * shall be set to 00b for all other commands. Suspend Command: If the Suspend command succeeds, the
 * uSDHC shall assume that the card bus has been released and that it is possible to issue the next
 * command which uses the DAT line. Since the uSDHC does not monitor the content of command
 * response, it does not know if the Suspend command succeeded or not. It is the Host Driver's
 * responsibility to check the status of the Suspend command and send another command marked as
 * Suspend to inform the uSDHC that a Suspend command was successfully issued. Refer to for more
 * details. After the end bit of command is sent, the uSDHC de-asserts Read Wait for read
 * transactions and stops checking busy for write transactions. In 4-bit mode, the interrupt cycle
 * starts. If the Suspend command fails, the uSDHC will maintain its current state, and the Host
 * Driver shall restart the transfer by setting the Continue Request bit in the Protocol Control
 * register. Resume Command: The Host Driver re-starts the data transfer by restoring the registers
 * saved before sending the Suspend Command and then sends the Resume Command. The uSDHC will check
 * for a pending busy state before starting write transfers. Abort Command: If this command is set
 * when executing a read transfer, the uSDHC will stop reads to the buffer. If this command is set
 * when executing a write transfer, the uSDHC will stop driving the DAT line. After issuing the
 * Abort command, the Host Driver should issue a software reset (Abort Transaction).
 *
 * Values:
 * 00 - Normal Other commands
 * 01 - Suspend CMD52 for writing Bus Suspend in CCCR
 * 10 - Resume CMD52 for writing Function Select in CCCR
 * 11 - Abort CMD12, CMD52 for writing I/O Abort in CCCR
 */

#define BP_USDHC_CMD_XFR_TYP_CMDTYP      (22)      //!< Bit position for USDHC_CMD_XFR_TYP_CMDTYP.
#define BM_USDHC_CMD_XFR_TYP_CMDTYP      (0x00c00000)  //!< Bit mask for USDHC_CMD_XFR_TYP_CMDTYP.

//! @brief Get value of USDHC_CMD_XFR_TYP_CMDTYP from a register value.
#define BG_USDHC_CMD_XFR_TYP_CMDTYP(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_CMDTYP) >> BP_USDHC_CMD_XFR_TYP_CMDTYP)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_CMDTYP.
#define BF_USDHC_CMD_XFR_TYP_CMDTYP(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_CMDTYP) & BM_USDHC_CMD_XFR_TYP_CMDTYP)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMDTYP field to a new value.
#define BW_USDHC_CMD_XFR_TYP_CMDTYP(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_CMDTYP) | BF_USDHC_CMD_XFR_TYP_CMDTYP(v)))
#endif


/* --- Register HW_USDHC_CMD_XFR_TYP, field CMDINX[29:24] (RW)
 *
 * Command Index: These bits shall be set to the command number that is specified in bits 45-40 of
 * the Command-Format in the SD Memory Card Physical Layer Specification and SDIO Card
 * Specification.
 */

#define BP_USDHC_CMD_XFR_TYP_CMDINX      (24)      //!< Bit position for USDHC_CMD_XFR_TYP_CMDINX.
#define BM_USDHC_CMD_XFR_TYP_CMDINX      (0x3f000000)  //!< Bit mask for USDHC_CMD_XFR_TYP_CMDINX.

//! @brief Get value of USDHC_CMD_XFR_TYP_CMDINX from a register value.
#define BG_USDHC_CMD_XFR_TYP_CMDINX(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_XFR_TYP_CMDINX) >> BP_USDHC_CMD_XFR_TYP_CMDINX)

//! @brief Format value for bitfield USDHC_CMD_XFR_TYP_CMDINX.
#define BF_USDHC_CMD_XFR_TYP_CMDINX(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CMD_XFR_TYP_CMDINX) & BM_USDHC_CMD_XFR_TYP_CMDINX)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMDINX field to a new value.
#define BW_USDHC_CMD_XFR_TYP_CMDINX(x, v)   (HW_USDHC_CMD_XFR_TYP_WR(x, (HW_USDHC_CMD_XFR_TYP_RD(x) & ~BM_USDHC_CMD_XFR_TYP_CMDINX) | BF_USDHC_CMD_XFR_TYP_CMDINX(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_RSP0 - Command Response0
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_RSP0 - Command Response0 (RO)
 *
 * Reset value: 0x00000000
 *
 * This register is used to store part 0 of the response bits from the card.
 */
typedef union _hw_usdhc_cmd_rsp0
{
    reg32_t U;
    struct _hw_usdhc_cmd_rsp0_bitfields
    {
        unsigned CMDRSP0 : 32; //!< [31:0] Command Response 0: Refer to for the mapping of command responses from the SD Bus to this register for each response type.
    } B;
} hw_usdhc_cmd_rsp0_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_RSP0 register
 */
#define HW_USDHC_CMD_RSP0_ADDR(x)      (REGS_USDHC_BASE(x) + 0x10)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_RSP0(x)           (*(volatile hw_usdhc_cmd_rsp0_t *) HW_USDHC_CMD_RSP0_ADDR(x))
#define HW_USDHC_CMD_RSP0_RD(x)        (HW_USDHC_CMD_RSP0(x).U)
#endif

/*
 * constants & macros for individual USDHC_CMD_RSP0 bitfields
 */

/* --- Register HW_USDHC_CMD_RSP0, field CMDRSP0[31:0] (RO)
 *
 * Command Response 0: Refer to for the mapping of command responses from the SD Bus to this
 * register for each response type.
 */

#define BP_USDHC_CMD_RSP0_CMDRSP0      (0)      //!< Bit position for USDHC_CMD_RSP0_CMDRSP0.
#define BM_USDHC_CMD_RSP0_CMDRSP0      (0xffffffff)  //!< Bit mask for USDHC_CMD_RSP0_CMDRSP0.

//! @brief Get value of USDHC_CMD_RSP0_CMDRSP0 from a register value.
#define BG_USDHC_CMD_RSP0_CMDRSP0(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_RSP0_CMDRSP0) >> BP_USDHC_CMD_RSP0_CMDRSP0)

//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_RSP1 - Command Response1
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_RSP1 - Command Response1 (RO)
 *
 * Reset value: 0x00000000
 *
 * This register is used to store part 1 of the response bits from the card.
 */
typedef union _hw_usdhc_cmd_rsp1
{
    reg32_t U;
    struct _hw_usdhc_cmd_rsp1_bitfields
    {
        unsigned CMDRSP1 : 32; //!< [31:0] Command Response 1: Refer to for the mapping of command responses from the SD Bus to this register for each response type.
    } B;
} hw_usdhc_cmd_rsp1_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_RSP1 register
 */
#define HW_USDHC_CMD_RSP1_ADDR(x)      (REGS_USDHC_BASE(x) + 0x14)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_RSP1(x)           (*(volatile hw_usdhc_cmd_rsp1_t *) HW_USDHC_CMD_RSP1_ADDR(x))
#define HW_USDHC_CMD_RSP1_RD(x)        (HW_USDHC_CMD_RSP1(x).U)
#endif

/*
 * constants & macros for individual USDHC_CMD_RSP1 bitfields
 */

/* --- Register HW_USDHC_CMD_RSP1, field CMDRSP1[31:0] (RO)
 *
 * Command Response 1: Refer to for the mapping of command responses from the SD Bus to this
 * register for each response type.
 */

#define BP_USDHC_CMD_RSP1_CMDRSP1      (0)      //!< Bit position for USDHC_CMD_RSP1_CMDRSP1.
#define BM_USDHC_CMD_RSP1_CMDRSP1      (0xffffffff)  //!< Bit mask for USDHC_CMD_RSP1_CMDRSP1.

//! @brief Get value of USDHC_CMD_RSP1_CMDRSP1 from a register value.
#define BG_USDHC_CMD_RSP1_CMDRSP1(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_RSP1_CMDRSP1) >> BP_USDHC_CMD_RSP1_CMDRSP1)

//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_RSP2 - Command Response2
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_RSP2 - Command Response2 (RO)
 *
 * Reset value: 0x00000000
 *
 * This register is used to store part 2 of the response bits from the card.
 */
typedef union _hw_usdhc_cmd_rsp2
{
    reg32_t U;
    struct _hw_usdhc_cmd_rsp2_bitfields
    {
        unsigned CMDRSP2 : 32; //!< [31:0] Command Response 2: Refer to for the mapping of command responses from the SD Bus to this register for each response type.
    } B;
} hw_usdhc_cmd_rsp2_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_RSP2 register
 */
#define HW_USDHC_CMD_RSP2_ADDR(x)      (REGS_USDHC_BASE(x) + 0x18)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_RSP2(x)           (*(volatile hw_usdhc_cmd_rsp2_t *) HW_USDHC_CMD_RSP2_ADDR(x))
#define HW_USDHC_CMD_RSP2_RD(x)        (HW_USDHC_CMD_RSP2(x).U)
#endif

/*
 * constants & macros for individual USDHC_CMD_RSP2 bitfields
 */

/* --- Register HW_USDHC_CMD_RSP2, field CMDRSP2[31:0] (RO)
 *
 * Command Response 2: Refer to for the mapping of command responses from the SD Bus to this
 * register for each response type.
 */

#define BP_USDHC_CMD_RSP2_CMDRSP2      (0)      //!< Bit position for USDHC_CMD_RSP2_CMDRSP2.
#define BM_USDHC_CMD_RSP2_CMDRSP2      (0xffffffff)  //!< Bit mask for USDHC_CMD_RSP2_CMDRSP2.

//! @brief Get value of USDHC_CMD_RSP2_CMDRSP2 from a register value.
#define BG_USDHC_CMD_RSP2_CMDRSP2(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_RSP2_CMDRSP2) >> BP_USDHC_CMD_RSP2_CMDRSP2)

//-------------------------------------------------------------------------------------------
// HW_USDHC_CMD_RSP3 - Command Response3
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CMD_RSP3 - Command Response3 (RO)
 *
 * Reset value: 0x00000000
 *
 * This register is used to store part 3 of the response bits from the card.  The table below
 * describes the mapping of command responses from the SD Bus to Command Response registers for each
 * response type. In the table, R[ ] refers to a bit range within the response data as transmitted
 * on the SD Bus.   Response Bit Definition for Each Response Type          Response Type    Meaning
 * of Response    Response Field    Response Register        R1,R1b (normal response)    Card Status
 * R[39:8]    CMDRSP0      R1b (Auto CMD12 response)    Card Status for Auto CMD12    R[39:8]
 * CMDRSP3      R2 (CID, CSD register)    CID/CSD register [127:8]    R[127:8]    {CMDRSP3[23:0],
 * CMDRSP2,  CMDRSP1,  CMDRSP0}      R3 (OCR register)    OCR register for memory    R[39:8]
 * CMDRSP0      R4 (OCR register)    OCR register for I/O etc.    R[39:8]    CMDRSP0      R5, R5b
 * SDIO response    R[39:8]    CMDRSP0      R6 (Publish RCA)    New Published RCA[31:16] and card
 * status[15:0]    R[39:9]    CMDRSP0       This table shows that most responses with a length of 48
 * (R[47:0]) have 32-bits of the response data (R[39:8]) stored in the CMDRSP0 register. Responses
 * of type R1b (Auto CMD12 responses) have response data bits (R[39:8]) stored in the CMDRSP3
 * register. Responses with length 136 (R[135:0]) have 120-bits of the response data (R[127:8])
 * stored in the CMDRSP0, 1, 2, and 3 registers.  To be able to read the response status
 * efficiently, the uSDHC only stores part of the response data in the Command Response registers.
 * This enables the Host Driver to efficiently read 32-bits of response data in one read cycle on a
 * 32-bit bus system. Parts of the response, the Index field and the CRC, are checked by the uSDHC
 * (as specified by the Command Index Check Enable and the Command CRC Check Enable bits in the
 * Transfer Type register) and generate an error interrupt if any error is detected. The bit range
 * for the CRC check depends on the response length. If the response length is 48, the uSDHC will
 * check R[47:1], and if the response length is 136 the uSDHC will check R[119:1].  Since the uSDHC
 * may have a multiple block data transfer executing concurrently with a CMD_wo_DAT command, the
 * uSDHC stores the Auto CMD12 response in the CMDRSP3 register. The CMD_wo_DAT response is stored
 * in CMDRSP0. This allows the uSDHC to avoid overwriting the Auto CMD12 response with the
 * CMD_wo_DAT and vice versa. When the uSDHC modifies part of the Command Response registers, as
 * shown in the table above, it preserves the unmodified bits.
 */
typedef union _hw_usdhc_cmd_rsp3
{
    reg32_t U;
    struct _hw_usdhc_cmd_rsp3_bitfields
    {
        unsigned CMDRSP3 : 32; //!< [31:0] Command Response 3: Refer to for the mapping of command responses from the SD Bus to this register for each response type.
    } B;
} hw_usdhc_cmd_rsp3_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CMD_RSP3 register
 */
#define HW_USDHC_CMD_RSP3_ADDR(x)      (REGS_USDHC_BASE(x) + 0x1c)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CMD_RSP3(x)           (*(volatile hw_usdhc_cmd_rsp3_t *) HW_USDHC_CMD_RSP3_ADDR(x))
#define HW_USDHC_CMD_RSP3_RD(x)        (HW_USDHC_CMD_RSP3(x).U)
#endif

/*
 * constants & macros for individual USDHC_CMD_RSP3 bitfields
 */

/* --- Register HW_USDHC_CMD_RSP3, field CMDRSP3[31:0] (RO)
 *
 * Command Response 3: Refer to for the mapping of command responses from the SD Bus to this
 * register for each response type.
 */

#define BP_USDHC_CMD_RSP3_CMDRSP3      (0)      //!< Bit position for USDHC_CMD_RSP3_CMDRSP3.
#define BM_USDHC_CMD_RSP3_CMDRSP3      (0xffffffff)  //!< Bit mask for USDHC_CMD_RSP3_CMDRSP3.

//! @brief Get value of USDHC_CMD_RSP3_CMDRSP3 from a register value.
#define BG_USDHC_CMD_RSP3_CMDRSP3(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CMD_RSP3_CMDRSP3) >> BP_USDHC_CMD_RSP3_CMDRSP3)

//-------------------------------------------------------------------------------------------
// HW_USDHC_DATA_BUFF_ACC_PORT - Data Buffer Access Port
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_DATA_BUFF_ACC_PORT - Data Buffer Access Port (RW)
 *
 * Reset value: 0x00000000
 *
 * This is a 32-bit data port register used to access the internal buffer.
 */
typedef union _hw_usdhc_data_buff_acc_port
{
    reg32_t U;
    struct _hw_usdhc_data_buff_acc_port_bitfields
    {
        unsigned DATCONT : 32; //!< [31:0] Data Content: The Buffer Data Port register is for 32-bit data access by the ARM platform or the external DMA.
    } B;
} hw_usdhc_data_buff_acc_port_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_DATA_BUFF_ACC_PORT register
 */
#define HW_USDHC_DATA_BUFF_ACC_PORT_ADDR(x)      (REGS_USDHC_BASE(x) + 0x20)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_DATA_BUFF_ACC_PORT(x)           (*(volatile hw_usdhc_data_buff_acc_port_t *) HW_USDHC_DATA_BUFF_ACC_PORT_ADDR(x))
#define HW_USDHC_DATA_BUFF_ACC_PORT_RD(x)        (HW_USDHC_DATA_BUFF_ACC_PORT(x).U)
#define HW_USDHC_DATA_BUFF_ACC_PORT_WR(x, v)     (HW_USDHC_DATA_BUFF_ACC_PORT(x).U = (v))
#define HW_USDHC_DATA_BUFF_ACC_PORT_SET(x, v)    (HW_USDHC_DATA_BUFF_ACC_PORT_WR(x, HW_USDHC_DATA_BUFF_ACC_PORT_RD(x) |  (v)))
#define HW_USDHC_DATA_BUFF_ACC_PORT_CLR(x, v)    (HW_USDHC_DATA_BUFF_ACC_PORT_WR(x, HW_USDHC_DATA_BUFF_ACC_PORT_RD(x) & ~(v)))
#define HW_USDHC_DATA_BUFF_ACC_PORT_TOG(x, v)    (HW_USDHC_DATA_BUFF_ACC_PORT_WR(x, HW_USDHC_DATA_BUFF_ACC_PORT_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_DATA_BUFF_ACC_PORT bitfields
 */

/* --- Register HW_USDHC_DATA_BUFF_ACC_PORT, field DATCONT[31:0] (RW)
 *
 * Data Content: The Buffer Data Port register is for 32-bit data access by the ARM platform or the
 * external DMA. When the internal DMA is enabled, any write to this register is ignored, and any
 * read from this register will always yield 0s.
 */

#define BP_USDHC_DATA_BUFF_ACC_PORT_DATCONT      (0)      //!< Bit position for USDHC_DATA_BUFF_ACC_PORT_DATCONT.
#define BM_USDHC_DATA_BUFF_ACC_PORT_DATCONT      (0xffffffff)  //!< Bit mask for USDHC_DATA_BUFF_ACC_PORT_DATCONT.

//! @brief Get value of USDHC_DATA_BUFF_ACC_PORT_DATCONT from a register value.
#define BG_USDHC_DATA_BUFF_ACC_PORT_DATCONT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DATA_BUFF_ACC_PORT_DATCONT) >> BP_USDHC_DATA_BUFF_ACC_PORT_DATCONT)

//! @brief Format value for bitfield USDHC_DATA_BUFF_ACC_PORT_DATCONT.
#define BF_USDHC_DATA_BUFF_ACC_PORT_DATCONT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DATA_BUFF_ACC_PORT_DATCONT) & BM_USDHC_DATA_BUFF_ACC_PORT_DATCONT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATCONT field to a new value.
#define BW_USDHC_DATA_BUFF_ACC_PORT_DATCONT(x, v)   (HW_USDHC_DATA_BUFF_ACC_PORT_WR(x, (HW_USDHC_DATA_BUFF_ACC_PORT_RD(x) & ~BM_USDHC_DATA_BUFF_ACC_PORT_DATCONT) | BF_USDHC_DATA_BUFF_ACC_PORT_DATCONT(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_PRES_STATE - Present State
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_PRES_STATE - Present State (RO)
 *
 * Reset value: 0x00000000
 *
 * The Host Driver can get status of the uSDHC from this 32-bit read only register.   The Host
 * Driver can issue CMD0, CMD12, CMD13 (for memory) and CMD52 (for SDIO) when the DAT lines are busy
 * during a data transfer. These commands can be issued when Command Inhibit (CMD) is set to zero.
 * Other commands shall be issued when Command Inhibit (DAT) is set to zero. Possible changes to the
 * SD Physical Specification may add other commands to this list in the future.  Note: the reset
 * value of Present State Register depend on testbench connectivity.
 */
typedef union _hw_usdhc_pres_state
{
    reg32_t U;
    struct _hw_usdhc_pres_state_bitfields
    {
        unsigned CIHB : 1; //!< [0] Command Inhibit (CMD): If this status bit is 0, it indicates that the CMD line is not in use and the uSDHC can issue a SD/MMC Command using the CMD line.
        unsigned CDIHB : 1; //!< [1] Command Inhibit (DAT): This status bit is generated if either the DAT Line Active or the Read Transfer Active is set to 1.
        unsigned DLA : 1; //!< [2] Data Line Active This status bit indicates whether one of the DAT lines on the SD Bus is in use.
        unsigned SDSTB : 1; //!< [3] SD Clock Stable This status bit indicates that the internal card clock is stable.
        unsigned IPGOFF : 1; //!< [4] ipg_clk Gated Off Internally: This status bit indicates that the ipg_clk is internally gated off.
        unsigned HCKOFF : 1; //!< [5] hclk Gated Off Internally: This status bit indicates that the hclk is internally gated off.
        unsigned PEROFF : 1; //!< [6] ipg_perclk Gated Off Internally: This status bit indicates that the ipg_perclk is internally gated off.
        unsigned SDOFF : 1; //!< [7] SD Clock Gated Off Internally: This status bit indicates that the SD Clock is internally gated off, because of buffer over/under-run or read pause without read wait assertion, or the driver set FRC_SDCLK_ON bit is 0 to stop the SD clock in idle status.
        unsigned WTA : 1; //!< [8] Write Transfer Active: This status bit indicates a write transfer is active.
        unsigned RTA : 1; //!< [9] Read Transfer Active: This status bit is used for detecting completion of a read transfer.
        unsigned BWEN : 1; //!< [10] Buffer Write Enable: This status bit is used for non-DMA write transfers.
        unsigned BREN : 1; //!< [11] Buffer Read Enable: This status bit is used for non-DMA read transfers.
        unsigned RTR : 1; //!< [12] Re-Tuning Request: (only for SD3.0 SDR104 mode) Host Controller may request Host Driver to execute re-tuning sequence by setting this bit when the data window is shifted by temperature drift and a tuned sampling point does not have a good margin to receive correct data.
        unsigned RESERVED0 : 3; //!< [15:13] Reserved
        unsigned CINST : 1; //!< [16] Card Inserted: This bit indicates whether a card has been inserted.
        unsigned RESERVED1 : 1; //!< [17] Reserved
        unsigned CDPL : 1; //!< [18] Card Detect Pin Level: This bit reflects the inverse value of the CD# pin for the card socket.
        unsigned WPSPL : 1; //!< [19] Write Protect Switch Pin Level: The Write Protect Switch is supported for memory and combo cards.This bit reflects the inverted value of the WP pin of the card socket.
        unsigned RESERVED2 : 3; //!< [22:20] Reserved
        unsigned CLSL : 1; //!< [23] CMD Line Signal Level: This status is used to check the CMD line level to recover from errors, and for debugging.
        unsigned DLSL : 8; //!< [31:24] DAT[7:0] Line Signal Level: This status is used to check the DAT line level to recover from errors, and for debugging.This is especially useful in detecting the busy signal level from DAT[0].
    } B;
} hw_usdhc_pres_state_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_PRES_STATE register
 */
#define HW_USDHC_PRES_STATE_ADDR(x)      (REGS_USDHC_BASE(x) + 0x24)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_PRES_STATE(x)           (*(volatile hw_usdhc_pres_state_t *) HW_USDHC_PRES_STATE_ADDR(x))
#define HW_USDHC_PRES_STATE_RD(x)        (HW_USDHC_PRES_STATE(x).U)
#endif

/*
 * constants & macros for individual USDHC_PRES_STATE bitfields
 */

/* --- Register HW_USDHC_PRES_STATE, field CIHB[0] (RO)
 *
 * Command Inhibit (CMD): If this status bit is 0, it indicates that the CMD line is not in use and
 * the uSDHC can issue a SD/MMC Command using the CMD line. This bit is set also immediately after
 * the Transfer Type register is written. This bit is cleared when the command response is received.
 * Even if the Command Inhibit (DAT) is set to 1, Commands using only the CMD line can be issued if
 * this bit is 0. Changing from 1 to 0 generates a Command Complete interrupt in the Interrupt
 * Status register. If the uSDHC cannot issue the command because of a command conflict error (Refer
 * to Command CRC Error) or because of a Command Not Issued By Auto CMD12 Error, this bit will
 * remain 1 and the Command Complete is not set. The Status of issuing an Auto CMD12 does not show
 * on this bit.
 *
 * Values:
 * 0 - Can issue command using only CMD line
 * 1 - Cannot issue command
 */

#define BP_USDHC_PRES_STATE_CIHB      (0)      //!< Bit position for USDHC_PRES_STATE_CIHB.
#define BM_USDHC_PRES_STATE_CIHB      (0x00000001)  //!< Bit mask for USDHC_PRES_STATE_CIHB.

//! @brief Get value of USDHC_PRES_STATE_CIHB from a register value.
#define BG_USDHC_PRES_STATE_CIHB(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_CIHB) >> BP_USDHC_PRES_STATE_CIHB)


/* --- Register HW_USDHC_PRES_STATE, field CDIHB[1] (RO)
 *
 * Command Inhibit (DAT): This status bit is generated if either the DAT Line Active or the Read
 * Transfer Active is set to 1. If this bit is 0, it indicates that the uSDHC can issue the next
 * SD/MMC Command. Commands with a busy signal belong to Command Inhibit (DAT) (e.g. R1b, R5b type).
 * Except in the case when the command busy is finished, changing from 1 to 0 generates a Transfer
 * Complete interrupt in the Interrupt Status register. Note: The SD Host Driver can save registers
 * for a suspend transaction after this bit has changed from 1 to 0.
 *
 * Values:
 * 0 - Can issue command which uses the DAT line
 * 1 - Cannot issue command which uses the DAT line
 */

#define BP_USDHC_PRES_STATE_CDIHB      (1)      //!< Bit position for USDHC_PRES_STATE_CDIHB.
#define BM_USDHC_PRES_STATE_CDIHB      (0x00000002)  //!< Bit mask for USDHC_PRES_STATE_CDIHB.

//! @brief Get value of USDHC_PRES_STATE_CDIHB from a register value.
#define BG_USDHC_PRES_STATE_CDIHB(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_CDIHB) >> BP_USDHC_PRES_STATE_CDIHB)


/* --- Register HW_USDHC_PRES_STATE, field DLA[2] (RO)
 *
 * Data Line Active This status bit indicates whether one of the DAT lines on the SD Bus is in use.
 * In the case of read transactions: This status indicates if a read transfer is executing on the SD
 * Bus. Changes in this value from 1 to 0, between data blocks, generates a Block Gap Event
 * interrupt in the Interrupt Status register. This bit will be set in either of the following
 * cases: After the end bit of the read command. When writing a 1 to the Continue Request bit in the
 * Protocol Control register to restart a read transfer. This bit will be cleared in either of the
 * following cases: (1) When the end bit of the last data block is sent from the SD Bus to the
 * uSDHC. (2) When the Read Wait state is stopped by a Suspend command and the DAT2 line is
 * released. The uSDHC will wait at the next block gap by driving Read Wait at the start of the
 * interrupt cycle. If the Read Wait signal is already driven (data buffer cannot receive data), the
 * uSDHC can wait for a current block gap by continuing to drive the Read Wait signal. It is
 * necessary to support Read Wait in order to use the suspend / resume function. This bit will
 * remain 1 during Read Wait. In the case of write transactions: This status indicates that a write
 * transfer is executing on the SD Bus. Changes in this value from 1 to 0 generate a Transfer
 * Complete interrupt in the Interrupt Status register. This bit will be set in either of the
 * following cases: After the end bit of the write command. When writing to 1 to the Continue
 * Request bit in the Protocol Control register to continue a write transfer. This bit will be
 * cleared in either of the following cases: When the SD card releases Write Busy of the last data
 * block, the uSDHC will also detect if the output is not busy. If the SD card does not drive the
 * busy signal after the CRC status is received, the uSDHC shall assume the card drive "Not Busy".
 * When the SD card releases write busy, prior to waiting for write transfer, and as a result of a
 * Stop At Block Gap Request. In the case of command with busy pending: This status indicates that a
 * busy state follows the command and the data line is in use. This bit will be cleared when the
 * DAT0 line is released.
 *
 * Values:
 * 0 - DAT Line Inactive
 * 1 - DAT Line Active
 */

#define BP_USDHC_PRES_STATE_DLA      (2)      //!< Bit position for USDHC_PRES_STATE_DLA.
#define BM_USDHC_PRES_STATE_DLA      (0x00000004)  //!< Bit mask for USDHC_PRES_STATE_DLA.

//! @brief Get value of USDHC_PRES_STATE_DLA from a register value.
#define BG_USDHC_PRES_STATE_DLA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_DLA) >> BP_USDHC_PRES_STATE_DLA)


/* --- Register HW_USDHC_PRES_STATE, field SDSTB[3] (RO)
 *
 * SD Clock Stable This status bit indicates that the internal card clock is stable. This bit is for
 * the Host Driver to poll clock status when changing the clock frequency. It is recommended to
 * clear FRC_SDCLK_ON bit in System Control register to remove glitch on the card clock when the
 * frequency is changing. Before changing clock divisor value(SDCLKFS or DVS), Host Driver should
 * make sure the SDSTB bit is high.
 *
 * Values:
 * 0 - clock is changing frequency and not stable
 * 1 - clock is stable
 */

#define BP_USDHC_PRES_STATE_SDSTB      (3)      //!< Bit position for USDHC_PRES_STATE_SDSTB.
#define BM_USDHC_PRES_STATE_SDSTB      (0x00000008)  //!< Bit mask for USDHC_PRES_STATE_SDSTB.

//! @brief Get value of USDHC_PRES_STATE_SDSTB from a register value.
#define BG_USDHC_PRES_STATE_SDSTB(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_SDSTB) >> BP_USDHC_PRES_STATE_SDSTB)


/* --- Register HW_USDHC_PRES_STATE, field IPGOFF[4] (RO)
 *
 * ipg_clk Gated Off Internally: This status bit indicates that the ipg_clk is internally gated off.
 * This bit is for the Host Driver to debug.
 *
 * Values:
 * 0 - ipg_clk is active
 * 1 - ipg_clk is gated off
 */

#define BP_USDHC_PRES_STATE_IPGOFF      (4)      //!< Bit position for USDHC_PRES_STATE_IPGOFF.
#define BM_USDHC_PRES_STATE_IPGOFF      (0x00000010)  //!< Bit mask for USDHC_PRES_STATE_IPGOFF.

//! @brief Get value of USDHC_PRES_STATE_IPGOFF from a register value.
#define BG_USDHC_PRES_STATE_IPGOFF(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_IPGOFF) >> BP_USDHC_PRES_STATE_IPGOFF)


/* --- Register HW_USDHC_PRES_STATE, field HCKOFF[5] (RO)
 *
 * hclk Gated Off Internally: This status bit indicates that the hclk is internally gated off. This
 * bit is for the Host Driver to debug during a data transfer.
 *
 * Values:
 * 0 - hclk is active
 * 1 - hclk is gated off
 */

#define BP_USDHC_PRES_STATE_HCKOFF      (5)      //!< Bit position for USDHC_PRES_STATE_HCKOFF.
#define BM_USDHC_PRES_STATE_HCKOFF      (0x00000020)  //!< Bit mask for USDHC_PRES_STATE_HCKOFF.

//! @brief Get value of USDHC_PRES_STATE_HCKOFF from a register value.
#define BG_USDHC_PRES_STATE_HCKOFF(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_HCKOFF) >> BP_USDHC_PRES_STATE_HCKOFF)


/* --- Register HW_USDHC_PRES_STATE, field PEROFF[6] (RO)
 *
 * ipg_perclk Gated Off Internally: This status bit indicates that the ipg_perclk is internally
 * gated off. This bit is for the Host Driver to debug transaction on the SD bus. When
 * IPG_CLK_SOFT_EN is cleared, ipg_perclk will be gated off, otherwise ipg_perclk will be always
 * active.
 *
 * Values:
 * 0 - ipg_perclk is active
 * 1 - ipg_perclk is gated off
 */

#define BP_USDHC_PRES_STATE_PEROFF      (6)      //!< Bit position for USDHC_PRES_STATE_PEROFF.
#define BM_USDHC_PRES_STATE_PEROFF      (0x00000040)  //!< Bit mask for USDHC_PRES_STATE_PEROFF.

//! @brief Get value of USDHC_PRES_STATE_PEROFF from a register value.
#define BG_USDHC_PRES_STATE_PEROFF(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_PEROFF) >> BP_USDHC_PRES_STATE_PEROFF)


/* --- Register HW_USDHC_PRES_STATE, field SDOFF[7] (RO)
 *
 * SD Clock Gated Off Internally: This status bit indicates that the SD Clock is internally gated
 * off, because of buffer over/under-run or read pause without read wait assertion, or the driver
 * set FRC_SDCLK_ON bit is 0 to stop the SD clock in idle status. Set IPG_PERCLK_SOFT_EN and
 * CARD_CLK_SOFT_EN to 0 also gate off SD clock. This bit is for the Host Driver to debug data
 * transaction on the SD bus.
 *
 * Values:
 * 0 - SD Clock is active
 * 1 - SD Clock is gated off
 */

#define BP_USDHC_PRES_STATE_SDOFF      (7)      //!< Bit position for USDHC_PRES_STATE_SDOFF.
#define BM_USDHC_PRES_STATE_SDOFF      (0x00000080)  //!< Bit mask for USDHC_PRES_STATE_SDOFF.

//! @brief Get value of USDHC_PRES_STATE_SDOFF from a register value.
#define BG_USDHC_PRES_STATE_SDOFF(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_SDOFF) >> BP_USDHC_PRES_STATE_SDOFF)


/* --- Register HW_USDHC_PRES_STATE, field WTA[8] (RO)
 *
 * Write Transfer Active: This status bit indicates a write transfer is active. If this bit is 0, it
 * means no valid write data exists in the uSDHC. This bit is set in either of the following cases:
 * After the end bit of the write command. When writing 1 to the Continue Request bit in the
 * Protocol Control register to restart a write transfer. This bit is cleared in either of the
 * following cases: After getting the CRC status of the last data block as specified by the transfer
 * count (Single and Multiple). After getting the CRC status of any block where data transmission is
 * about to be stopped by a Stop At Block Gap Request. During a write transaction, a Block Gap Event
 * interrupt is generated when this bit is changed to 0, as result of the Stop At Block Gap Request
 * being set. This status is useful for the Host Driver in determining when to issue commands during
 * Write Busy state.
 *
 * Values:
 * 0 - No valid data
 * 1 - Transferring data
 */

#define BP_USDHC_PRES_STATE_WTA      (8)      //!< Bit position for USDHC_PRES_STATE_WTA.
#define BM_USDHC_PRES_STATE_WTA      (0x00000100)  //!< Bit mask for USDHC_PRES_STATE_WTA.

//! @brief Get value of USDHC_PRES_STATE_WTA from a register value.
#define BG_USDHC_PRES_STATE_WTA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_WTA) >> BP_USDHC_PRES_STATE_WTA)


/* --- Register HW_USDHC_PRES_STATE, field RTA[9] (RO)
 *
 * Read Transfer Active: This status bit is used for detecting completion of a read transfer. This
 * bit is set for either of the following conditions: After the end bit of the read command. When
 * writing a 1 to the Continue Request bit in the Protocol Control register to restart a read
 * transfer. A Transfer Complete interrupt is generated when this bit changes to 0. This bit is
 * cleared for either of the following conditions: When the last data block as specified by block
 * length is transferred to the System, i.e. all data are read away from uSDHC internal buffer. When
 * all valid data blocks have been transferred from uSDHC internal buffer to the System and no
 * current block transfers are being sent as a result of the Stop At Block Gap Request being set to
 * 1.
 *
 * Values:
 * 0 - No valid data
 * 1 - Transferring data
 */

#define BP_USDHC_PRES_STATE_RTA      (9)      //!< Bit position for USDHC_PRES_STATE_RTA.
#define BM_USDHC_PRES_STATE_RTA      (0x00000200)  //!< Bit mask for USDHC_PRES_STATE_RTA.

//! @brief Get value of USDHC_PRES_STATE_RTA from a register value.
#define BG_USDHC_PRES_STATE_RTA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_RTA) >> BP_USDHC_PRES_STATE_RTA)


/* --- Register HW_USDHC_PRES_STATE, field BWEN[10] (RO)
 *
 * Buffer Write Enable: This status bit is used for non-DMA write transfers. The uSDHC implements an
 * internal buffer to transfer data efficiently. This read only flag indicates if space is available
 * for write data. If this bit is 1, valid data greater than the watermark level can be written to
 * the buffer. A change of this bit from 1 to 0 occurs when some writes to the buffer(write
 * DATPORT(Base + 0x20)) are made and the buffer hasn't valid space greater than the watermake
 * level. . A change of this bit from 0 to 1 occurs when the buffer can hold valid data greater than
 * the write watermark level and the Buffer Write Ready interrupt is generated and enabled.
 *
 * Values:
 * 0 - Write disable
 * 1 - Write enable
 */

#define BP_USDHC_PRES_STATE_BWEN      (10)      //!< Bit position for USDHC_PRES_STATE_BWEN.
#define BM_USDHC_PRES_STATE_BWEN      (0x00000400)  //!< Bit mask for USDHC_PRES_STATE_BWEN.

//! @brief Get value of USDHC_PRES_STATE_BWEN from a register value.
#define BG_USDHC_PRES_STATE_BWEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_BWEN) >> BP_USDHC_PRES_STATE_BWEN)


/* --- Register HW_USDHC_PRES_STATE, field BREN[11] (RO)
 *
 * Buffer Read Enable: This status bit is used for non-DMA read transfers. The uSDHC implements an
 * internal buffer to transfer data efficiently. This read only flag indicates that valid data
 * exists in the host side buffer. If this bit is high, valid data greater than the watermark level
 * exist in the buffer. A change of this bit from 1 to 0 occurs when some reads from the buffer(read
 * DATPORT(Base + 0x20)) are made and the buffer hasn't valid data greater than the watermake level.
 * A change of this bit from 0 to1 occurs when there is enough valid data ready in the buffer and
 * the Buffer Read Ready interrupt has been generated and enabled.
 *
 * Values:
 * 0 - Read disable
 * 1 - Read enable
 */

#define BP_USDHC_PRES_STATE_BREN      (11)      //!< Bit position for USDHC_PRES_STATE_BREN.
#define BM_USDHC_PRES_STATE_BREN      (0x00000800)  //!< Bit mask for USDHC_PRES_STATE_BREN.

//! @brief Get value of USDHC_PRES_STATE_BREN from a register value.
#define BG_USDHC_PRES_STATE_BREN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_BREN) >> BP_USDHC_PRES_STATE_BREN)


/* --- Register HW_USDHC_PRES_STATE, field RTR[12] (RO)
 *
 * Re-Tuning Request: (only for SD3.0 SDR104 mode) Host Controller may request Host Driver to
 * execute re-tuning sequence by setting this bit when the data window is shifted by temperature
 * drift and a tuned sampling point does not have a good margin to receive correct data. This bit is
 * cleared when a command is issued with setting Execute Tuning bit in MIXER_CTRL register. Changing
 * of this bit from 0 to 1 generates Re-Tuning Event. Refer to Interrupt status registers for more
 * delail. This bit isn't set to 1 if Sampling Clock Select in the MIXER_CTRL register is set to 0
 * (using fixed sampling clock).
 *
 * Values:
 * 0 - Fixed or well tuned sampling clock
 * 1 - Sampling clock needs re-tuning
 */

#define BP_USDHC_PRES_STATE_RTR      (12)      //!< Bit position for USDHC_PRES_STATE_RTR.
#define BM_USDHC_PRES_STATE_RTR      (0x00001000)  //!< Bit mask for USDHC_PRES_STATE_RTR.

//! @brief Get value of USDHC_PRES_STATE_RTR from a register value.
#define BG_USDHC_PRES_STATE_RTR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_RTR) >> BP_USDHC_PRES_STATE_RTR)


/* --- Register HW_USDHC_PRES_STATE, field CINST[16] (RO)
 *
 * Card Inserted: This bit indicates whether a card has been inserted. The uSDHC debounces this
 * signal so that the Host Driver will not need to wait for it to stabilize. Changing from a 0 to 1
 * generates a Card Insertion interrupt in the Interrupt Status register. Changing from a 1 to 0
 * generates a Card Removal interrupt in the Interrupt Status register. A write to the Force Event
 * Register does not effect this bit. The Software Reset For All in the System Control register does
 * not effect this bit.A software reset does not effect this bit.
 *
 * Values:
 * 0 - Power on Reset or No Card
 * 1 - Card Inserted
 */

#define BP_USDHC_PRES_STATE_CINST      (16)      //!< Bit position for USDHC_PRES_STATE_CINST.
#define BM_USDHC_PRES_STATE_CINST      (0x00010000)  //!< Bit mask for USDHC_PRES_STATE_CINST.

//! @brief Get value of USDHC_PRES_STATE_CINST from a register value.
#define BG_USDHC_PRES_STATE_CINST(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_CINST) >> BP_USDHC_PRES_STATE_CINST)


/* --- Register HW_USDHC_PRES_STATE, field CDPL[18] (RO)
 *
 * Card Detect Pin Level: This bit reflects the inverse value of the CD# pin for the card socket.
 * Debouncing is not performed on this bit. This bit may be valid, but is not guaranteed, because of
 * propagation delay. Use of this bit is limited to testing since it must be debounced by software.
 * A software reset does not effect this bit. A write to the Force Event Register does not effect
 * this bit. The reset value is effected by the external card detection pin. This bit shows the
 * value on the CD# pin (i.e. when a card is inserted in the socket, it is 0 on the CD# input, and
 * consequently the CDPL reads 1.)
 *
 * Values:
 * 0 - No card present (CD#=1)
 * 1 - Card present (CD#=0)
 */

#define BP_USDHC_PRES_STATE_CDPL      (18)      //!< Bit position for USDHC_PRES_STATE_CDPL.
#define BM_USDHC_PRES_STATE_CDPL      (0x00040000)  //!< Bit mask for USDHC_PRES_STATE_CDPL.

//! @brief Get value of USDHC_PRES_STATE_CDPL from a register value.
#define BG_USDHC_PRES_STATE_CDPL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_CDPL) >> BP_USDHC_PRES_STATE_CDPL)


/* --- Register HW_USDHC_PRES_STATE, field WPSPL[19] (RO)
 *
 * Write Protect Switch Pin Level: The Write Protect Switch is supported for memory and combo
 * cards.This bit reflects the inverted value of the WP pin of the card socket. A software reset
 * does not affect this bit. The reset value is effected by the external write protect switch. If
 * the WP pin is not used, it should be tied low, so that the reset value of this bit is high and
 * write is enabled.
 *
 * Values:
 * 0 - Write protected (WP=1)
 * 1 - Write enabled (WP=0)
 */

#define BP_USDHC_PRES_STATE_WPSPL      (19)      //!< Bit position for USDHC_PRES_STATE_WPSPL.
#define BM_USDHC_PRES_STATE_WPSPL      (0x00080000)  //!< Bit mask for USDHC_PRES_STATE_WPSPL.

//! @brief Get value of USDHC_PRES_STATE_WPSPL from a register value.
#define BG_USDHC_PRES_STATE_WPSPL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_WPSPL) >> BP_USDHC_PRES_STATE_WPSPL)


/* --- Register HW_USDHC_PRES_STATE, field CLSL[23] (RO)
 *
 * CMD Line Signal Level: This status is used to check the CMD line level to recover from errors,
 * and for debugging. The reset value is effected by the external pull-up/pull-down resistor, by
 * default, the read value of this bit after reset is 1'b1, when the command line is pulled up.
 */

#define BP_USDHC_PRES_STATE_CLSL      (23)      //!< Bit position for USDHC_PRES_STATE_CLSL.
#define BM_USDHC_PRES_STATE_CLSL      (0x00800000)  //!< Bit mask for USDHC_PRES_STATE_CLSL.

//! @brief Get value of USDHC_PRES_STATE_CLSL from a register value.
#define BG_USDHC_PRES_STATE_CLSL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_CLSL) >> BP_USDHC_PRES_STATE_CLSL)

/* --- Register HW_USDHC_PRES_STATE, field DLSL[31:24] (RO)
 *
 * DAT[7:0] Line Signal Level: This status is used to check the DAT line level to recover from
 * errors, and for debugging.This is especially useful in detecting the busy signal level from
 * DAT[0]. The reset value is effected by the external pull-up/pull-down resistors. By default, the
 * read value of this bit field after reset is 8'b11110111, when DAT[3] is pulled down and the other
 * lines are pulled up. DAT[7]: Data 7 line signal level DAT[6]: Data 6 line signal level DAT[5]:
 * Data 5 line signal level DAT[4]: Data 4 line signal level DAT[3]: Data 3 line signal level
 * DAT[2]: Data 2 line signal level DAT[1]: Data 1 line signal level DAT[0]: Data 0 line signal
 * level
 */

#define BP_USDHC_PRES_STATE_DLSL      (24)      //!< Bit position for USDHC_PRES_STATE_DLSL.
#define BM_USDHC_PRES_STATE_DLSL      (0xff000000)  //!< Bit mask for USDHC_PRES_STATE_DLSL.

//! @brief Get value of USDHC_PRES_STATE_DLSL from a register value.
#define BG_USDHC_PRES_STATE_DLSL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PRES_STATE_DLSL) >> BP_USDHC_PRES_STATE_DLSL)

//-------------------------------------------------------------------------------------------
// HW_USDHC_PROT_CTRL - Protocol Control
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_PROT_CTRL - Protocol Control (RW)
 *
 * Reset value: 0x08800020
 *
 * There are three cases to restart the transfer after stop at the block gap. Which case is
 * appropriate depends on whether the uSDHC issues a Suspend command or the SD card accepts the
 * Suspend command.   If the Host Driver does not issue a Suspend command, the Continue Request
 * shall be used to restart the transfer.  If the Host Driver issues a Suspend command and the SD
 * card accepts it, a Resume command shall be used to restart the transfer.  If the Host Driver
 * issues a Suspend command and the SD card does not accept it, the Continue Request shall be used
 * to restart the transfer.   Any time Stop At Block Gap Request stops the data transfer, the Host
 * Driver shall wait for a Transfer Complete (in the Interrupt Status register), before attempting
 * to restart the transfer. When restarting the data transfer by Continue Request, the Host Driver
 * shall clear the Stop At Block Gap Request before or simultaneously.
 */
typedef union _hw_usdhc_prot_ctrl
{
    reg32_t U;
    struct _hw_usdhc_prot_ctrl_bitfields
    {
        unsigned LCTL : 1; //!< [0] LED Control: This bit, fully controlled by the Host Driver, is used to caution the user not to remove the card while the card is being accessed.
        unsigned DTW : 2; //!< [2:1] Data Transfer Width: This bit selects the data width of the SD bus for a data transfer.
        unsigned D3CD : 1; //!< [3] DAT3 as Card Detection Pin: If this bit is set, DAT3 should be pulled down to act as a card detection pin.
        unsigned EMODE : 2; //!< [5:4] Endian Mode: The uSDHC supports all four endian modes in data transfer.
        unsigned CDTL : 1; //!< [6] Card Detect Test Level: This is bit is enabled while the Card Detection Signal Selection is set to 1 and it indicates card insertion.
        unsigned CDSS : 1; //!< [7] Card Detect Signal Selection: This bit selects the source for the card detection.
        unsigned DMASEL : 2; //!< [9:8] DMA Select: This field is valid while DMA (SDMA or ADMA) is enabled and selects the DMA operation.
        unsigned RESERVED0 : 6; //!< [15:10] Reserved
        unsigned SABGREQ : 1; //!< [16] Stop At Block Gap Request: This bit is used to stop executing a transaction at the next block gap for both DMA and non-DMA transfers.
        unsigned CREQ : 1; //!< [17] Continue Request: This bit is used to restart a transaction which was stopped using the Stop At Block Gap Request.
        unsigned RWCTL : 1; //!< [18] Read Wait Control: The read wait function is optional for SDIO cards.
        unsigned IABG : 1; //!< [19] Interrupt At Block Gap: This bit is valid only in 4-bit mode, of the SDIO card, and selects a sample point in the interrupt cycle.
        unsigned RD_DONE_NO_8CLK : 1; //!< [20] Read done no 8 clock: According to the SD/MMC spec, for read data transaction, 8 clocks are needed after the end bit of the last data block.
        unsigned RD_WAIT_POINT : 3; //!< [23:21] Read wait point : This is only for debug purpose.
        unsigned WECINT : 1; //!< [24] Wakeup Event Enable On Card Interrupt: This bit enables a wakeup event, via a Card Interrupt, in the Interrupt Status register.
        unsigned WECINS : 1; //!< [25] Wakeup Event Enable On SD Card Insertion: This bit enables a wakeup event, via a Card Insertion, in the Interrupt Status register.
        unsigned WECRM : 1; //!< [26] Wakeup Event Enable On SD Card Removal: This bit enables a wakeup event, via a Card Removal, in the Interrupt Status register.
        unsigned BURST_LEN_EN : 3; //!< [29:27] BURST length enable for INCR, INCR4/INCR8/INCR16, INCR4-WRAP/INCR8-WRAP/INCR16-WRAP This is used to enable/disable the burst length for the external AHB2AXI bridge.
        unsigned NON_EXACT_BLK_RD : 1; //!< [30] Current block read is non-exact block read.
        unsigned RD_NO8CLK_EN : 1; //!< [31] Only for debug.
    } B;
} hw_usdhc_prot_ctrl_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_PROT_CTRL register
 */
#define HW_USDHC_PROT_CTRL_ADDR(x)      (REGS_USDHC_BASE(x) + 0x28)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_PROT_CTRL(x)           (*(volatile hw_usdhc_prot_ctrl_t *) HW_USDHC_PROT_CTRL_ADDR(x))
#define HW_USDHC_PROT_CTRL_RD(x)        (HW_USDHC_PROT_CTRL(x).U)
#define HW_USDHC_PROT_CTRL_WR(x, v)     (HW_USDHC_PROT_CTRL(x).U = (v))
#define HW_USDHC_PROT_CTRL_SET(x, v)    (HW_USDHC_PROT_CTRL_WR(x, HW_USDHC_PROT_CTRL_RD(x) |  (v)))
#define HW_USDHC_PROT_CTRL_CLR(x, v)    (HW_USDHC_PROT_CTRL_WR(x, HW_USDHC_PROT_CTRL_RD(x) & ~(v)))
#define HW_USDHC_PROT_CTRL_TOG(x, v)    (HW_USDHC_PROT_CTRL_WR(x, HW_USDHC_PROT_CTRL_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_PROT_CTRL bitfields
 */

/* --- Register HW_USDHC_PROT_CTRL, field LCTL[0] (RW)
 *
 * LED Control: This bit, fully controlled by the Host Driver, is used to caution the user not to
 * remove the card while the card is being accessed. If the software is going to issue multiple SD
 * commands, this bit can be set during all these transactions. It is not necessary to change for
 * each transaction. When the software issues multiple SD commands, setting the bit once before the
 * first command is sufficient: it is not necessary to reset the bit between commands.
 *
 * Values:
 * 0 - LED off
 * 1 - LED on
 */

#define BP_USDHC_PROT_CTRL_LCTL      (0)      //!< Bit position for USDHC_PROT_CTRL_LCTL.
#define BM_USDHC_PROT_CTRL_LCTL      (0x00000001)  //!< Bit mask for USDHC_PROT_CTRL_LCTL.

//! @brief Get value of USDHC_PROT_CTRL_LCTL from a register value.
#define BG_USDHC_PROT_CTRL_LCTL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_LCTL) >> BP_USDHC_PROT_CTRL_LCTL)

//! @brief Format value for bitfield USDHC_PROT_CTRL_LCTL.
#define BF_USDHC_PROT_CTRL_LCTL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_LCTL) & BM_USDHC_PROT_CTRL_LCTL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the LCTL field to a new value.
#define BW_USDHC_PROT_CTRL_LCTL(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_LCTL) | BF_USDHC_PROT_CTRL_LCTL(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field DTW[2:1] (RW)
 *
 * Data Transfer Width: This bit selects the data width of the SD bus for a data transfer. The Host
 * Driver shall set it to match the data width of the card. Possible Data transfer Width is 1-bit,
 * 4-bits or 8-bits.
 *
 * Values:
 * 00 - 1-bit mode
 * 01 - 4-bit mode
 * 10 - 8-bit mode
 * 11 - Reserved
 */

#define BP_USDHC_PROT_CTRL_DTW      (1)      //!< Bit position for USDHC_PROT_CTRL_DTW.
#define BM_USDHC_PROT_CTRL_DTW      (0x00000006)  //!< Bit mask for USDHC_PROT_CTRL_DTW.

//! @brief Get value of USDHC_PROT_CTRL_DTW from a register value.
#define BG_USDHC_PROT_CTRL_DTW(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_DTW) >> BP_USDHC_PROT_CTRL_DTW)

//! @brief Format value for bitfield USDHC_PROT_CTRL_DTW.
#define BF_USDHC_PROT_CTRL_DTW(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_DTW) & BM_USDHC_PROT_CTRL_DTW)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTW field to a new value.
#define BW_USDHC_PROT_CTRL_DTW(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_DTW) | BF_USDHC_PROT_CTRL_DTW(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field D3CD[3] (RW)
 *
 * DAT3 as Card Detection Pin: If this bit is set, DAT3 should be pulled down to act as a card
 * detection pin. Be cautious when using this feature, because DAT3 is also a chip-select for the
 * SPI mode. A pull-down on this pin and CMD0 may set the card into the SPI mode, which the uSDHC
 * does not support.
 *
 * Values:
 * 0 - DAT3 does not monitor Card Insertion
 * 1 - DAT3 as Card Detection Pin
 */

#define BP_USDHC_PROT_CTRL_D3CD      (3)      //!< Bit position for USDHC_PROT_CTRL_D3CD.
#define BM_USDHC_PROT_CTRL_D3CD      (0x00000008)  //!< Bit mask for USDHC_PROT_CTRL_D3CD.

//! @brief Get value of USDHC_PROT_CTRL_D3CD from a register value.
#define BG_USDHC_PROT_CTRL_D3CD(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_D3CD) >> BP_USDHC_PROT_CTRL_D3CD)

//! @brief Format value for bitfield USDHC_PROT_CTRL_D3CD.
#define BF_USDHC_PROT_CTRL_D3CD(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_D3CD) & BM_USDHC_PROT_CTRL_D3CD)

#ifndef __LANGUAGE_ASM__
//! @brief Set the D3CD field to a new value.
#define BW_USDHC_PROT_CTRL_D3CD(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_D3CD) | BF_USDHC_PROT_CTRL_D3CD(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field EMODE[5:4] (RW)
 *
 * Endian Mode: The uSDHC supports all four endian modes in data transfer. Refer to " for more
 * details.
 *
 * Values:
 * 00 - Big Endian Mode
 * 01 - Half Word Big Endian Mode
 * 10 - Little Endian Mode
 * 11 - Reserved
 */

#define BP_USDHC_PROT_CTRL_EMODE      (4)      //!< Bit position for USDHC_PROT_CTRL_EMODE.
#define BM_USDHC_PROT_CTRL_EMODE      (0x00000030)  //!< Bit mask for USDHC_PROT_CTRL_EMODE.

//! @brief Get value of USDHC_PROT_CTRL_EMODE from a register value.
#define BG_USDHC_PROT_CTRL_EMODE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_EMODE) >> BP_USDHC_PROT_CTRL_EMODE)

//! @brief Format value for bitfield USDHC_PROT_CTRL_EMODE.
#define BF_USDHC_PROT_CTRL_EMODE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_EMODE) & BM_USDHC_PROT_CTRL_EMODE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the EMODE field to a new value.
#define BW_USDHC_PROT_CTRL_EMODE(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_EMODE) | BF_USDHC_PROT_CTRL_EMODE(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field CDTL[6] (RW)
 *
 * Card Detect Test Level: This is bit is enabled while the Card Detection Signal Selection is set
 * to 1 and it indicates card insertion.
 *
 * Values:
 * 0 - Card Detect Test Level is 0, no card inserted
 * 1 - Card Detect Test Level is 1, card inserted
 */

#define BP_USDHC_PROT_CTRL_CDTL      (6)      //!< Bit position for USDHC_PROT_CTRL_CDTL.
#define BM_USDHC_PROT_CTRL_CDTL      (0x00000040)  //!< Bit mask for USDHC_PROT_CTRL_CDTL.

//! @brief Get value of USDHC_PROT_CTRL_CDTL from a register value.
#define BG_USDHC_PROT_CTRL_CDTL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_CDTL) >> BP_USDHC_PROT_CTRL_CDTL)

//! @brief Format value for bitfield USDHC_PROT_CTRL_CDTL.
#define BF_USDHC_PROT_CTRL_CDTL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_CDTL) & BM_USDHC_PROT_CTRL_CDTL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CDTL field to a new value.
#define BW_USDHC_PROT_CTRL_CDTL(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_CDTL) | BF_USDHC_PROT_CTRL_CDTL(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field CDSS[7] (RW)
 *
 * Card Detect Signal Selection: This bit selects the source for the card detection.
 *
 * Values:
 * 0 - Card Detection Level is selected (for normal purpose)
 * 1 - Card Detection Test Level is selected (for test purpose)
 */

#define BP_USDHC_PROT_CTRL_CDSS      (7)      //!< Bit position for USDHC_PROT_CTRL_CDSS.
#define BM_USDHC_PROT_CTRL_CDSS      (0x00000080)  //!< Bit mask for USDHC_PROT_CTRL_CDSS.

//! @brief Get value of USDHC_PROT_CTRL_CDSS from a register value.
#define BG_USDHC_PROT_CTRL_CDSS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_CDSS) >> BP_USDHC_PROT_CTRL_CDSS)

//! @brief Format value for bitfield USDHC_PROT_CTRL_CDSS.
#define BF_USDHC_PROT_CTRL_CDSS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_CDSS) & BM_USDHC_PROT_CTRL_CDSS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CDSS field to a new value.
#define BW_USDHC_PROT_CTRL_CDSS(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_CDSS) | BF_USDHC_PROT_CTRL_CDSS(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field DMASEL[9:8] (RW)
 *
 * DMA Select: This field is valid while DMA (SDMA or ADMA) is enabled and selects the DMA
 * operation.
 *
 * Values:
 * 00 - No DMA or Simple DMA is selected
 * 01 - ADMA1 is selected
 * 10 - ADMA2 is selected
 * 11 - reserved
 */

#define BP_USDHC_PROT_CTRL_DMASEL      (8)      //!< Bit position for USDHC_PROT_CTRL_DMASEL.
#define BM_USDHC_PROT_CTRL_DMASEL      (0x00000300)  //!< Bit mask for USDHC_PROT_CTRL_DMASEL.

//! @brief Get value of USDHC_PROT_CTRL_DMASEL from a register value.
#define BG_USDHC_PROT_CTRL_DMASEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_DMASEL) >> BP_USDHC_PROT_CTRL_DMASEL)

//! @brief Format value for bitfield USDHC_PROT_CTRL_DMASEL.
#define BF_USDHC_PROT_CTRL_DMASEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_DMASEL) & BM_USDHC_PROT_CTRL_DMASEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DMASEL field to a new value.
#define BW_USDHC_PROT_CTRL_DMASEL(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_DMASEL) | BF_USDHC_PROT_CTRL_DMASEL(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field SABGREQ[16] (RW)
 *
 * Stop At Block Gap Request: This bit is used to stop executing a transaction at the next block gap
 * for both DMA and non-DMA transfers. Until the Transfer Complete is set to 1, indicating a
 * transfer completion, the Host Driver shall leave this bit set to 1. Clearing both the Stop At
 * Block Gap Request and Continue Request does not cause the transaction to restart. Read Wait is
 * used to stop the read transaction at the block gap. The uSDHC will honor the Stop At Block Gap
 * Request for write transfers, but for read transfers it requires that the SDIO card support Read
 * Wait. Therefore, the Host Driver shall not set this bit during read transfers unless the SDIO
 * card supports Read Wait and has set the Read Wait Control to 1, otherwise the uSDHC will stop the
 * SD bus clock to pause the read operation during block gap. In the case of write transfers in
 * which the Host Driver writes data to the Data Port register, the Host Driver shall set this bit
 * after all block data is written. If this bit is set to 1, the Host Driver shall not write data to
 * the Data Port register after a block is sent. Once this bit is set, the Host Driver shall not
 * clear this bit before the Transfer Complete bit in Interrupt Status Register is set, otherwise
 * the uSDHCs behavior is undefined. This bit effects Read Transfer Active, Write Transfer Active,
 * DAT Line Active and Command Inhibit (DAT) in the Present State register.
 *
 * Values:
 * 0 - Transfer
 * 1 - Stop
 */

#define BP_USDHC_PROT_CTRL_SABGREQ      (16)      //!< Bit position for USDHC_PROT_CTRL_SABGREQ.
#define BM_USDHC_PROT_CTRL_SABGREQ      (0x00010000)  //!< Bit mask for USDHC_PROT_CTRL_SABGREQ.

//! @brief Get value of USDHC_PROT_CTRL_SABGREQ from a register value.
#define BG_USDHC_PROT_CTRL_SABGREQ(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_SABGREQ) >> BP_USDHC_PROT_CTRL_SABGREQ)

//! @brief Format value for bitfield USDHC_PROT_CTRL_SABGREQ.
#define BF_USDHC_PROT_CTRL_SABGREQ(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_SABGREQ) & BM_USDHC_PROT_CTRL_SABGREQ)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SABGREQ field to a new value.
#define BW_USDHC_PROT_CTRL_SABGREQ(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_SABGREQ) | BF_USDHC_PROT_CTRL_SABGREQ(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field CREQ[17] (RW)
 *
 * Continue Request: This bit is used to restart a transaction which was stopped using the Stop At
 * Block Gap Request. When a Suspend operation is not accepted by the card, it is also by setting
 * this bit to restart the paused transfer. To cancel stop at the block gap, set Stop At Block Gap
 * Request to 0 and set this bit to 1 to restart the transfer. The uSDHC automatically clears this
 * bit, therefore it is not necessary for the Host Driver to set this bit to 0. If both Stop At
 * Block Gap Request and this bit are 1, the continue request is ignored.
 *
 * Values:
 * 0 - No effect
 * 1 - Restart
 */

#define BP_USDHC_PROT_CTRL_CREQ      (17)      //!< Bit position for USDHC_PROT_CTRL_CREQ.
#define BM_USDHC_PROT_CTRL_CREQ      (0x00020000)  //!< Bit mask for USDHC_PROT_CTRL_CREQ.

//! @brief Get value of USDHC_PROT_CTRL_CREQ from a register value.
#define BG_USDHC_PROT_CTRL_CREQ(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_CREQ) >> BP_USDHC_PROT_CTRL_CREQ)

//! @brief Format value for bitfield USDHC_PROT_CTRL_CREQ.
#define BF_USDHC_PROT_CTRL_CREQ(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_CREQ) & BM_USDHC_PROT_CTRL_CREQ)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CREQ field to a new value.
#define BW_USDHC_PROT_CTRL_CREQ(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_CREQ) | BF_USDHC_PROT_CTRL_CREQ(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field RWCTL[18] (RW)
 *
 * Read Wait Control: The read wait function is optional for SDIO cards. If the card supports read
 * wait, set this bit to enable use of the read wait protocol to stop read data using the DAT[2]
 * line. Otherwise the uSDHC has to stop the SD Clock to hold read data, which restricts commands
 * generation. When the Host Driver detects an SDIO card insertion, it shall set this bit according
 * to the CCCR of the card. If the card does not support read wait, this bit shall never be set to
 * 1, otherwise DAT line conflicts may occur. If this bit is set to 0, stop at block gap during read
 * operation is also supported, but the uSDHC will stop the SD Clock to pause reading operation.
 *
 * Values:
 * 0 - Disable Read Wait Control, and stop SD Clock at block gap when SABGREQ bit is set
 * 1 - Enable Read Wait Control, and assert Read Wait without stopping SD Clock at block gap when SABGREQ
 *     bit is set
 */

#define BP_USDHC_PROT_CTRL_RWCTL      (18)      //!< Bit position for USDHC_PROT_CTRL_RWCTL.
#define BM_USDHC_PROT_CTRL_RWCTL      (0x00040000)  //!< Bit mask for USDHC_PROT_CTRL_RWCTL.

//! @brief Get value of USDHC_PROT_CTRL_RWCTL from a register value.
#define BG_USDHC_PROT_CTRL_RWCTL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_RWCTL) >> BP_USDHC_PROT_CTRL_RWCTL)

//! @brief Format value for bitfield USDHC_PROT_CTRL_RWCTL.
#define BF_USDHC_PROT_CTRL_RWCTL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_RWCTL) & BM_USDHC_PROT_CTRL_RWCTL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RWCTL field to a new value.
#define BW_USDHC_PROT_CTRL_RWCTL(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_RWCTL) | BF_USDHC_PROT_CTRL_RWCTL(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field IABG[19] (RW)
 *
 * Interrupt At Block Gap: This bit is valid only in 4-bit mode, of the SDIO card, and selects a
 * sample point in the interrupt cycle. Setting to 1 enables interrupt detection at the block gap
 * for a multiple block transfer. Setting to 0 disables interrupt detection during a multiple block
 * transfer. If the SDIO card can't signal an interrupt during a multiple block transfer, this bit
 * should be set to 0 to avoid an inadvertent interrupt. When the Host Driver detects an SDIO card
 * insertion, it shall set this bit according to the CCCR of the card.
 *
 * Values:
 * 0 - Disabled
 * 1 - Enabled
 */

#define BP_USDHC_PROT_CTRL_IABG      (19)      //!< Bit position for USDHC_PROT_CTRL_IABG.
#define BM_USDHC_PROT_CTRL_IABG      (0x00080000)  //!< Bit mask for USDHC_PROT_CTRL_IABG.

//! @brief Get value of USDHC_PROT_CTRL_IABG from a register value.
#define BG_USDHC_PROT_CTRL_IABG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_IABG) >> BP_USDHC_PROT_CTRL_IABG)

//! @brief Format value for bitfield USDHC_PROT_CTRL_IABG.
#define BF_USDHC_PROT_CTRL_IABG(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_IABG) & BM_USDHC_PROT_CTRL_IABG)

#ifndef __LANGUAGE_ASM__
//! @brief Set the IABG field to a new value.
#define BW_USDHC_PROT_CTRL_IABG(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_IABG) | BF_USDHC_PROT_CTRL_IABG(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field RD_DONE_NO_8CLK[20] (RW)
 *
 * Read done no 8 clock: According to the SD/MMC spec, for read data transaction, 8 clocks are
 * needed after the end bit of the last data block. So, by default(RD_DONE_NO_8CLK=0), 8 clocks will
 * be active after the end bit of the last read data transaction. However, this 8 clocks should not
 * be active if user wants to use stop at block gap(include the auto stop at block gap in boot mode)
 * feature for read and the RWCTL bit(bit18) is not enabled. In this case, software should set
 * RD_DONE_NO_8CLK to avoid this 8 clocks. Otherwise, the device may send extra data to uSDHC while
 * uSDHC ignores these data. In a summary, this bit should be set only if the use case needs to use
 * stop at block gap feature while the device can't support the read wait feature.
 */

#define BP_USDHC_PROT_CTRL_RD_DONE_NO_8CLK      (20)      //!< Bit position for USDHC_PROT_CTRL_RD_DONE_NO_8CLK.
#define BM_USDHC_PROT_CTRL_RD_DONE_NO_8CLK      (0x00100000)  //!< Bit mask for USDHC_PROT_CTRL_RD_DONE_NO_8CLK.

//! @brief Get value of USDHC_PROT_CTRL_RD_DONE_NO_8CLK from a register value.
#define BG_USDHC_PROT_CTRL_RD_DONE_NO_8CLK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_RD_DONE_NO_8CLK) >> BP_USDHC_PROT_CTRL_RD_DONE_NO_8CLK)

//! @brief Format value for bitfield USDHC_PROT_CTRL_RD_DONE_NO_8CLK.
#define BF_USDHC_PROT_CTRL_RD_DONE_NO_8CLK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_RD_DONE_NO_8CLK) & BM_USDHC_PROT_CTRL_RD_DONE_NO_8CLK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RD_DONE_NO_8CLK field to a new value.
#define BW_USDHC_PROT_CTRL_RD_DONE_NO_8CLK(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_RD_DONE_NO_8CLK) | BF_USDHC_PROT_CTRL_RD_DONE_NO_8CLK(v)))
#endif

/* --- Register HW_USDHC_PROT_CTRL, field RD_WAIT_POINT[23:21] (RW)
 *
 * Read wait point : This is only for debug purpose. As a Host controller, uSDHC should pause the
 * SDHC_CLK or assert the DAT[2](if read wait feature is supported by the device) to avoid the
 * device to send extra data. The SDHC_CLK should be paused or the DAT[2] should be asserted in two
 * clock cycles after the end bit of the last transaction. Meanwhile, because the uSDHC controller
 * has async FIFO between the card interface and the internal state machine, we need this "Read wait
 * point" configuration to overcome the latency which is introduced by this async FIFO. The default
 * value is 0x4, which should be accurately overcome the latency.
 */

#define BP_USDHC_PROT_CTRL_RD_WAIT_POINT      (21)      //!< Bit position for USDHC_PROT_CTRL_RD_WAIT_POINT.
#define BM_USDHC_PROT_CTRL_RD_WAIT_POINT      (0x00e00000)  //!< Bit mask for USDHC_PROT_CTRL_RD_WAIT_POINT.

//! @brief Get value of USDHC_PROT_CTRL_RD_WAIT_POINT from a register value.
#define BG_USDHC_PROT_CTRL_RD_WAIT_POINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_RD_WAIT_POINT) >> BP_USDHC_PROT_CTRL_RD_WAIT_POINT)

//! @brief Format value for bitfield USDHC_PROT_CTRL_RD_WAIT_POINT.
#define BF_USDHC_PROT_CTRL_RD_WAIT_POINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_RD_WAIT_POINT) & BM_USDHC_PROT_CTRL_RD_WAIT_POINT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RD_WAIT_POINT field to a new value.
#define BW_USDHC_PROT_CTRL_RD_WAIT_POINT(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_RD_WAIT_POINT) | BF_USDHC_PROT_CTRL_RD_WAIT_POINT(v)))
#endif

/* --- Register HW_USDHC_PROT_CTRL, field WECINT[24] (RW)
 *
 * Wakeup Event Enable On Card Interrupt: This bit enables a wakeup event, via a Card Interrupt, in
 * the Interrupt Status register. This bit can be set to 1 if FN_WUS (Wake Up Support) in CIS is set
 * to 1. When this bit is set, the Card Interrupt Status and the uSDHC interrupt can be asserted
 * without CLK toggling. When the wakeup feature is not enabled, the CLK must be active in order to
 * assert the Card Interrupt Status and the uSDHC interrupt.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_PROT_CTRL_WECINT      (24)      //!< Bit position for USDHC_PROT_CTRL_WECINT.
#define BM_USDHC_PROT_CTRL_WECINT      (0x01000000)  //!< Bit mask for USDHC_PROT_CTRL_WECINT.

//! @brief Get value of USDHC_PROT_CTRL_WECINT from a register value.
#define BG_USDHC_PROT_CTRL_WECINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_WECINT) >> BP_USDHC_PROT_CTRL_WECINT)

//! @brief Format value for bitfield USDHC_PROT_CTRL_WECINT.
#define BF_USDHC_PROT_CTRL_WECINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_WECINT) & BM_USDHC_PROT_CTRL_WECINT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WECINT field to a new value.
#define BW_USDHC_PROT_CTRL_WECINT(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_WECINT) | BF_USDHC_PROT_CTRL_WECINT(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field WECINS[25] (RW)
 *
 * Wakeup Event Enable On SD Card Insertion: This bit enables a wakeup event, via a Card Insertion,
 * in the Interrupt Status register. FN_WUS (Wake Up Support) in CIS does not effect this bit. When
 * this bit is set, the Card Insertion Status and the uSDHC interrupt can be asserted without CLK
 * toggling. When the wakeup feature is not enabled, the CLK must be active in order to assert the
 * Card Insertion Status and the uSDHC interrupt.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_PROT_CTRL_WECINS      (25)      //!< Bit position for USDHC_PROT_CTRL_WECINS.
#define BM_USDHC_PROT_CTRL_WECINS      (0x02000000)  //!< Bit mask for USDHC_PROT_CTRL_WECINS.

//! @brief Get value of USDHC_PROT_CTRL_WECINS from a register value.
#define BG_USDHC_PROT_CTRL_WECINS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_WECINS) >> BP_USDHC_PROT_CTRL_WECINS)

//! @brief Format value for bitfield USDHC_PROT_CTRL_WECINS.
#define BF_USDHC_PROT_CTRL_WECINS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_WECINS) & BM_USDHC_PROT_CTRL_WECINS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WECINS field to a new value.
#define BW_USDHC_PROT_CTRL_WECINS(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_WECINS) | BF_USDHC_PROT_CTRL_WECINS(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field WECRM[26] (RW)
 *
 * Wakeup Event Enable On SD Card Removal: This bit enables a wakeup event, via a Card Removal, in
 * the Interrupt Status register. FN_WUS (Wake Up Support) in CIS does not effect this bit. When
 * this bit is set, the Card Removal Status and the uSDHC interrupt can be asserted without CLK
 * toggling. When the wakeup feature is not enabled, the CLK must be active in order to assert the
 * Card Removal Status and the uSDHC interrupt.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_PROT_CTRL_WECRM      (26)      //!< Bit position for USDHC_PROT_CTRL_WECRM.
#define BM_USDHC_PROT_CTRL_WECRM      (0x04000000)  //!< Bit mask for USDHC_PROT_CTRL_WECRM.

//! @brief Get value of USDHC_PROT_CTRL_WECRM from a register value.
#define BG_USDHC_PROT_CTRL_WECRM(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_WECRM) >> BP_USDHC_PROT_CTRL_WECRM)

//! @brief Format value for bitfield USDHC_PROT_CTRL_WECRM.
#define BF_USDHC_PROT_CTRL_WECRM(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_WECRM) & BM_USDHC_PROT_CTRL_WECRM)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WECRM field to a new value.
#define BW_USDHC_PROT_CTRL_WECRM(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_WECRM) | BF_USDHC_PROT_CTRL_WECRM(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field BURST_LEN_EN[29:27] (RW)
 *
 * BURST length enable for INCR, INCR4/INCR8/INCR16, INCR4-WRAP/INCR8-WRAP/INCR16-WRAP This is used
 * to enable/disable the burst length for the external AHB2AXI bridge. It's useful especially for
 * INCR transfer because without burst length indicator, the AHB2AXI bridge doesn't know the burst
 * length in advance. Without burst length indicator, AHB INCR transfers can only be converted to
 * SINGLEs in AXI side.
 *
 * Values:
 * xx1 - Burst length is enabled for INCR
 * x1x - Burst length is enabled for INCR4/INCR8/INCR16
 * 1xx - Burst length is enabled for INCR4-WRAP/INCR8-WRAP/INCR16-WRAP
 */

#define BP_USDHC_PROT_CTRL_BURST_LEN_EN      (27)      //!< Bit position for USDHC_PROT_CTRL_BURST_LEN_EN.
#define BM_USDHC_PROT_CTRL_BURST_LEN_EN      (0x38000000)  //!< Bit mask for USDHC_PROT_CTRL_BURST_LEN_EN.

//! @brief Get value of USDHC_PROT_CTRL_BURST_LEN_EN from a register value.
#define BG_USDHC_PROT_CTRL_BURST_LEN_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_BURST_LEN_EN) >> BP_USDHC_PROT_CTRL_BURST_LEN_EN)

//! @brief Format value for bitfield USDHC_PROT_CTRL_BURST_LEN_EN.
#define BF_USDHC_PROT_CTRL_BURST_LEN_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_BURST_LEN_EN) & BM_USDHC_PROT_CTRL_BURST_LEN_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BURST_LEN_EN field to a new value.
#define BW_USDHC_PROT_CTRL_BURST_LEN_EN(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_BURST_LEN_EN) | BF_USDHC_PROT_CTRL_BURST_LEN_EN(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field NON_EXACT_BLK_RD[30] (RW)
 *
 * Current block read is non-exact block read. It's only used for SDIO.
 *
 * Values:
 * 0 - The block read is exact block read. Host driver doesn't need to issue abort command to terminate
 *     this multi-block read.
 * 1 - The block read is non-exact block read. Host driver needs to issue abort command to terminate this
 *     multi-block read.
 */

#define BP_USDHC_PROT_CTRL_NON_EXACT_BLK_RD      (30)      //!< Bit position for USDHC_PROT_CTRL_NON_EXACT_BLK_RD.
#define BM_USDHC_PROT_CTRL_NON_EXACT_BLK_RD      (0x40000000)  //!< Bit mask for USDHC_PROT_CTRL_NON_EXACT_BLK_RD.

//! @brief Get value of USDHC_PROT_CTRL_NON_EXACT_BLK_RD from a register value.
#define BG_USDHC_PROT_CTRL_NON_EXACT_BLK_RD(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_NON_EXACT_BLK_RD) >> BP_USDHC_PROT_CTRL_NON_EXACT_BLK_RD)

//! @brief Format value for bitfield USDHC_PROT_CTRL_NON_EXACT_BLK_RD.
#define BF_USDHC_PROT_CTRL_NON_EXACT_BLK_RD(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_NON_EXACT_BLK_RD) & BM_USDHC_PROT_CTRL_NON_EXACT_BLK_RD)

#ifndef __LANGUAGE_ASM__
//! @brief Set the NON_EXACT_BLK_RD field to a new value.
#define BW_USDHC_PROT_CTRL_NON_EXACT_BLK_RD(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_NON_EXACT_BLK_RD) | BF_USDHC_PROT_CTRL_NON_EXACT_BLK_RD(v)))
#endif


/* --- Register HW_USDHC_PROT_CTRL, field RD_NO8CLK_EN[31] (RW)
 *
 * Only for debug. enable S/W RD_DONE_NO_8CLK bit
 *
 * Values:
 * 0 - Disable S/W RD_DONE_NO_8CLK, uSHDC determines if 8 clocks are needed automatically.
 * 1 - S/W RD_DONE_NO_8CLK is enabled
 */

#define BP_USDHC_PROT_CTRL_RD_NO8CLK_EN      (31)      //!< Bit position for USDHC_PROT_CTRL_RD_NO8CLK_EN.
#define BM_USDHC_PROT_CTRL_RD_NO8CLK_EN      (0x80000000)  //!< Bit mask for USDHC_PROT_CTRL_RD_NO8CLK_EN.

//! @brief Get value of USDHC_PROT_CTRL_RD_NO8CLK_EN from a register value.
#define BG_USDHC_PROT_CTRL_RD_NO8CLK_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_PROT_CTRL_RD_NO8CLK_EN) >> BP_USDHC_PROT_CTRL_RD_NO8CLK_EN)

//! @brief Format value for bitfield USDHC_PROT_CTRL_RD_NO8CLK_EN.
#define BF_USDHC_PROT_CTRL_RD_NO8CLK_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_PROT_CTRL_RD_NO8CLK_EN) & BM_USDHC_PROT_CTRL_RD_NO8CLK_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RD_NO8CLK_EN field to a new value.
#define BW_USDHC_PROT_CTRL_RD_NO8CLK_EN(x, v)   (HW_USDHC_PROT_CTRL_WR(x, (HW_USDHC_PROT_CTRL_RD(x) & ~BM_USDHC_PROT_CTRL_RD_NO8CLK_EN) | BF_USDHC_PROT_CTRL_RD_NO8CLK_EN(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_SYS_CTRL - System Control
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_SYS_CTRL - System Control (RW)
 *
 * Reset value: 0x0080800f
 *

 */
typedef union _hw_usdhc_sys_ctrl
{
    reg32_t U;
    struct _hw_usdhc_sys_ctrl_bitfields
    {
        unsigned IPGEN : 1; //!< [0] IPG Clock Enable: It's not implemented in uSDHC IP.
        unsigned HCKEN : 1; //!< [1] HCLK Enable: It's not implemented in uSDHC IP.
        unsigned PEREN : 1; //!< [2] Perpherial Clock Enable It's not implemented in uSDHC IP.
        unsigned SDCLKEN : 1; //!< [3] SD Clock Enable It's not implemented in uSDHC IP.
        unsigned DVS : 4; //!< [7:4] Divisor: This register is used to provide a more exact divisor to generate the desired SD clock frequency.
        unsigned SDCLKFS : 8; //!< [15:8] SDCLK Frequency Select: This register is used to select the frequency of the SDCLK pin.
        unsigned DTOCV : 4; //!< [19:16] Data Timeout Counter Value: This value determines the interval by which DAT line timeouts are detected.
        unsigned RESERVED0 : 2; //!< [21:20] Reserved
        unsigned RST_FIFO : 1; //!< [22] Reset the Async FIFO: Reset the Async FIFO between card interface and the internal logic.
        unsigned IPP_RST_N : 1; //!< [23] This register's value will be output to CARD from pad directly for hardware reset of the card if card support this feature.
        unsigned RSTA : 1; //!< [24] Software Reset For ALL: This reset effects the entire Host Controller except for the card detection circuit.
        unsigned RSTC : 1; //!< [25] Software Reset For CMD Line: Only part of the command circuit is reset.
        unsigned RSTD : 1; //!< [26] Software Reset For DAT Line: Only part of the data circuit is reset.
        unsigned INITA : 1; //!< [27] Initialization Active: When this bit is set, 80 SD-Clocks are sent to the card.
        unsigned RESERVED1 : 4; //!< [31:28] Reserved
    } B;
} hw_usdhc_sys_ctrl_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_SYS_CTRL register
 */
#define HW_USDHC_SYS_CTRL_ADDR(x)      (REGS_USDHC_BASE(x) + 0x2c)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_SYS_CTRL(x)           (*(volatile hw_usdhc_sys_ctrl_t *) HW_USDHC_SYS_CTRL_ADDR(x))
#define HW_USDHC_SYS_CTRL_RD(x)        (HW_USDHC_SYS_CTRL(x).U)
#define HW_USDHC_SYS_CTRL_WR(x, v)     (HW_USDHC_SYS_CTRL(x).U = (v))
#define HW_USDHC_SYS_CTRL_SET(x, v)    (HW_USDHC_SYS_CTRL_WR(x, HW_USDHC_SYS_CTRL_RD(x) |  (v)))
#define HW_USDHC_SYS_CTRL_CLR(x, v)    (HW_USDHC_SYS_CTRL_WR(x, HW_USDHC_SYS_CTRL_RD(x) & ~(v)))
#define HW_USDHC_SYS_CTRL_TOG(x, v)    (HW_USDHC_SYS_CTRL_WR(x, HW_USDHC_SYS_CTRL_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_SYS_CTRL bitfields
 */

/* --- Register HW_USDHC_SYS_CTRL, field IPGEN[0] (RW)
 *
 * IPG Clock Enable: It's not implemented in uSDHC IP.
 */

#define BP_USDHC_SYS_CTRL_IPGEN      (0)      //!< Bit position for USDHC_SYS_CTRL_IPGEN.
#define BM_USDHC_SYS_CTRL_IPGEN      (0x00000001)  //!< Bit mask for USDHC_SYS_CTRL_IPGEN.

//! @brief Get value of USDHC_SYS_CTRL_IPGEN from a register value.
#define BG_USDHC_SYS_CTRL_IPGEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_IPGEN) >> BP_USDHC_SYS_CTRL_IPGEN)

//! @brief Format value for bitfield USDHC_SYS_CTRL_IPGEN.
#define BF_USDHC_SYS_CTRL_IPGEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_IPGEN) & BM_USDHC_SYS_CTRL_IPGEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the IPGEN field to a new value.
#define BW_USDHC_SYS_CTRL_IPGEN(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_IPGEN) | BF_USDHC_SYS_CTRL_IPGEN(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field HCKEN[1] (RW)
 *
 * HCLK Enable: It's not implemented in uSDHC IP.
 */

#define BP_USDHC_SYS_CTRL_HCKEN      (1)      //!< Bit position for USDHC_SYS_CTRL_HCKEN.
#define BM_USDHC_SYS_CTRL_HCKEN      (0x00000002)  //!< Bit mask for USDHC_SYS_CTRL_HCKEN.

//! @brief Get value of USDHC_SYS_CTRL_HCKEN from a register value.
#define BG_USDHC_SYS_CTRL_HCKEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_HCKEN) >> BP_USDHC_SYS_CTRL_HCKEN)

//! @brief Format value for bitfield USDHC_SYS_CTRL_HCKEN.
#define BF_USDHC_SYS_CTRL_HCKEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_HCKEN) & BM_USDHC_SYS_CTRL_HCKEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the HCKEN field to a new value.
#define BW_USDHC_SYS_CTRL_HCKEN(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_HCKEN) | BF_USDHC_SYS_CTRL_HCKEN(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field PEREN[2] (RW)
 *
 * Perpherial Clock Enable It's not implemented in uSDHC IP.
 */

#define BP_USDHC_SYS_CTRL_PEREN      (2)      //!< Bit position for USDHC_SYS_CTRL_PEREN.
#define BM_USDHC_SYS_CTRL_PEREN      (0x00000004)  //!< Bit mask for USDHC_SYS_CTRL_PEREN.

//! @brief Get value of USDHC_SYS_CTRL_PEREN from a register value.
#define BG_USDHC_SYS_CTRL_PEREN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_PEREN) >> BP_USDHC_SYS_CTRL_PEREN)

//! @brief Format value for bitfield USDHC_SYS_CTRL_PEREN.
#define BF_USDHC_SYS_CTRL_PEREN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_PEREN) & BM_USDHC_SYS_CTRL_PEREN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the PEREN field to a new value.
#define BW_USDHC_SYS_CTRL_PEREN(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_PEREN) | BF_USDHC_SYS_CTRL_PEREN(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field SDCLKEN[3] (RW)
 *
 * SD Clock Enable It's not implemented in uSDHC IP.
 */

#define BP_USDHC_SYS_CTRL_SDCLKEN      (3)      //!< Bit position for USDHC_SYS_CTRL_SDCLKEN.
#define BM_USDHC_SYS_CTRL_SDCLKEN      (0x00000008)  //!< Bit mask for USDHC_SYS_CTRL_SDCLKEN.

//! @brief Get value of USDHC_SYS_CTRL_SDCLKEN from a register value.
#define BG_USDHC_SYS_CTRL_SDCLKEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_SDCLKEN) >> BP_USDHC_SYS_CTRL_SDCLKEN)

//! @brief Format value for bitfield USDHC_SYS_CTRL_SDCLKEN.
#define BF_USDHC_SYS_CTRL_SDCLKEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_SDCLKEN) & BM_USDHC_SYS_CTRL_SDCLKEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SDCLKEN field to a new value.
#define BW_USDHC_SYS_CTRL_SDCLKEN(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_SDCLKEN) | BF_USDHC_SYS_CTRL_SDCLKEN(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field DVS[7:4] (RW)
 *
 * Divisor: This register is used to provide a more exact divisor to generate the desired SD clock
 * frequency. Note the divider can even support odd divisor without deterioration of duty cycle.
 * Before changing clock divisor value(SDCLKFS or DVS), Host Driver should make sure the SDSTB bit
 * is high. The setting are as following:
 *
 * Values:
 * 0 - Divisor by 1
 * 1 - Divisor by 2
 * e - Divisor by 15
 * f - Divisor by 16
 */

#define BP_USDHC_SYS_CTRL_DVS      (4)      //!< Bit position for USDHC_SYS_CTRL_DVS.
#define BM_USDHC_SYS_CTRL_DVS      (0x000000f0)  //!< Bit mask for USDHC_SYS_CTRL_DVS.

//! @brief Get value of USDHC_SYS_CTRL_DVS from a register value.
#define BG_USDHC_SYS_CTRL_DVS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_DVS) >> BP_USDHC_SYS_CTRL_DVS)

//! @brief Format value for bitfield USDHC_SYS_CTRL_DVS.
#define BF_USDHC_SYS_CTRL_DVS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_DVS) & BM_USDHC_SYS_CTRL_DVS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DVS field to a new value.
#define BW_USDHC_SYS_CTRL_DVS(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_DVS) | BF_USDHC_SYS_CTRL_DVS(v)))
#endif


/* --- Register HW_USDHC_SYS_CTRL, field SDCLKFS[15:8] (RW)
 *
 * SDCLK Frequency Select: This register is used to select the frequency of the SDCLK pin. The
 * frequency is not programmed directly, rather this register holds the prescaler (this register)
 * and divisor (next register) of the Base Clock Frequency register. I n Single Data Rate
 * mode(DDR_EN bit of MIXERCTRL is '0') Only the following settings are allowed: 80h) Base clock
 * divided by 256 40h) Base clock divided by 128 20h) Base clock divided by 64 10h) Base clock
 * divided by 32 08h) Base clock divided by 16 04h) Base clock divided by 8 02h) Base clock divided
 * by 4 01h) Base clock divided by 2 00h) Base clock divided by 1 W hile in Dual Data Rate
 * mode(DDR_EN bit of MIXERCTRL is '1') Only the following settings are allowed: 80h) Base clock
 * divided by 512 40h) Base clock divided by 256 20h) Base clock divided by 128 10h) Base clock
 * divided by 64 08h) Base clock divided by 32 04h) Base clock divided by 16 02h) Base clock divided
 * by 8 01h) Base clock divided by 4 00h) Base clock divided by 2 W hen S/W changes the DDR_EN bit,
 * SDCLKFS may need to be changed also ! In Single Data Rate mode, setting 00h bypasses the
 * frequency prescaler of the SD Clock. Multiple bits must not be set, or the behavior of this
 * prescaler is undefined. The two default divider values can be calculated by the frequency of
 * ipg_perclk and the following Divisor bits. The frequency of SDCLK is set by the following
 * formula: Clock Frequency = (Base Clock) / (prescaler x divisor) For example, in Single Data Rate
 * mode, if the Base Clock Frequency is 96 MHz, and the target frequency is 25 MHz, then choosing
 * the prescaler value of 01h and divisor value of 1h will yield 24 MHz, which is the nearest
 * frequency less than or equal to the target. Similarly, to approach a clock value of 400 kHz, the
 * prescaler value of 08h and divisor value of eh yields the exact clock value of 400 kHz. The reset
 * value of this bit field is 80h, so if the input Base Clock (ipg_perclk) is about 96 MHz, the
 * default SD Clock after reset is 375 kHz. According to the SD Physical Specification Version 1.1
 * and the SDIO Card Specification Version 1.2, the maximum SD Clock frequency is 50 MHz and shall
 * never exceed this limit. B efore changing clock divisor value(SDCLKFS or DVS), Host Driver should
 * make sure the SDSTB bit is high. If setting SDCLKFS and DVS can generate same clock
 * frequency,(For example, in SDR mode, SDCLKFS = 01h is same as DVS = 01h.) SDCLKFS is highly
 * recommended.
 */

#define BP_USDHC_SYS_CTRL_SDCLKFS      (8)      //!< Bit position for USDHC_SYS_CTRL_SDCLKFS.
#define BM_USDHC_SYS_CTRL_SDCLKFS      (0x0000ff00)  //!< Bit mask for USDHC_SYS_CTRL_SDCLKFS.

//! @brief Get value of USDHC_SYS_CTRL_SDCLKFS from a register value.
#define BG_USDHC_SYS_CTRL_SDCLKFS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_SDCLKFS) >> BP_USDHC_SYS_CTRL_SDCLKFS)

//! @brief Format value for bitfield USDHC_SYS_CTRL_SDCLKFS.
#define BF_USDHC_SYS_CTRL_SDCLKFS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_SDCLKFS) & BM_USDHC_SYS_CTRL_SDCLKFS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SDCLKFS field to a new value.
#define BW_USDHC_SYS_CTRL_SDCLKFS(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_SDCLKFS) | BF_USDHC_SYS_CTRL_SDCLKFS(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field DTOCV[19:16] (RW)
 *
 * Data Timeout Counter Value: This value determines the interval by which DAT line timeouts are
 * detected. Refer to the Data Timeout Error bit in the Interrupt Status register for information on
 * factors that dictate time-out generation. Time-out clock frequency will be generated by dividing
 * the base clock SDCLK value by this value. The Host Driver can clear the Data Timeout Error Status
 * Enable (in the Interrupt Status Enable register) to prevent inadvertent time-out events.
 *
 * Values:
 * 0000 - SDCLK x 2 1  3
 * 0001 - SDCLK x 2 14
 * 1110 - SDCLK x 2 2  7
 * 1111 - SDCLK x 2 28
 */

#define BP_USDHC_SYS_CTRL_DTOCV      (16)      //!< Bit position for USDHC_SYS_CTRL_DTOCV.
#define BM_USDHC_SYS_CTRL_DTOCV      (0x000f0000)  //!< Bit mask for USDHC_SYS_CTRL_DTOCV.

//! @brief Get value of USDHC_SYS_CTRL_DTOCV from a register value.
#define BG_USDHC_SYS_CTRL_DTOCV(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_DTOCV) >> BP_USDHC_SYS_CTRL_DTOCV)

//! @brief Format value for bitfield USDHC_SYS_CTRL_DTOCV.
#define BF_USDHC_SYS_CTRL_DTOCV(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_DTOCV) & BM_USDHC_SYS_CTRL_DTOCV)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTOCV field to a new value.
#define BW_USDHC_SYS_CTRL_DTOCV(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_DTOCV) | BF_USDHC_SYS_CTRL_DTOCV(v)))
#endif


/* --- Register HW_USDHC_SYS_CTRL, field RST_FIFO[22] (WORZ)
 *
 * Reset the Async FIFO: Reset the Async FIFO between card interface and the internal logic. It's
 * only used for debugging. Software should not tough it.
 */

#define BP_USDHC_SYS_CTRL_RST_FIFO      (22)      //!< Bit position for USDHC_SYS_CTRL_RST_FIFO.
#define BM_USDHC_SYS_CTRL_RST_FIFO      (0x00400000)  //!< Bit mask for USDHC_SYS_CTRL_RST_FIFO.

//! @brief Get value of USDHC_SYS_CTRL_RST_FIFO from a register value.
#define BG_USDHC_SYS_CTRL_RST_FIFO(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_RST_FIFO) >> BP_USDHC_SYS_CTRL_RST_FIFO)

//! @brief Format value for bitfield USDHC_SYS_CTRL_RST_FIFO.
#define BF_USDHC_SYS_CTRL_RST_FIFO(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_RST_FIFO) & BM_USDHC_SYS_CTRL_RST_FIFO)

/* --- Register HW_USDHC_SYS_CTRL, field IPP_RST_N[23] (RW)
 *
 * This register's value will be output to CARD from pad directly for hardware reset of the card if
 * card support this feature.
 */

#define BP_USDHC_SYS_CTRL_IPP_RST_N      (23)      //!< Bit position for USDHC_SYS_CTRL_IPP_RST_N.
#define BM_USDHC_SYS_CTRL_IPP_RST_N      (0x00800000)  //!< Bit mask for USDHC_SYS_CTRL_IPP_RST_N.

//! @brief Get value of USDHC_SYS_CTRL_IPP_RST_N from a register value.
#define BG_USDHC_SYS_CTRL_IPP_RST_N(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_IPP_RST_N) >> BP_USDHC_SYS_CTRL_IPP_RST_N)

//! @brief Format value for bitfield USDHC_SYS_CTRL_IPP_RST_N.
#define BF_USDHC_SYS_CTRL_IPP_RST_N(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_IPP_RST_N) & BM_USDHC_SYS_CTRL_IPP_RST_N)

#ifndef __LANGUAGE_ASM__
//! @brief Set the IPP_RST_N field to a new value.
#define BW_USDHC_SYS_CTRL_IPP_RST_N(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_IPP_RST_N) | BF_USDHC_SYS_CTRL_IPP_RST_N(v)))
#endif

/* --- Register HW_USDHC_SYS_CTRL, field RSTA[24] (WORZ)
 *
 * Software Reset For ALL: This reset effects the entire Host Controller except for the card
 * detection circuit. Register bits of type ROC, RW, RW1C, RWAC are cleared. During its
 * initialization, the Host Driver shall set this bit to 1 to reset the uSDHC. The uSDHC shall reset
 * this bit to 0 when the capabilities registers are valid and the Host Driver can read them.
 * Additional use of Software Reset For All does not affect the value of the Capabilities registers.
 * After this bit is set, it is recommended that the Host Driver reset the external card and re-
 * initialize it.
 *
 * Values:
 * 0 - No Reset
 * 1 - Reset
 */

#define BP_USDHC_SYS_CTRL_RSTA      (24)      //!< Bit position for USDHC_SYS_CTRL_RSTA.
#define BM_USDHC_SYS_CTRL_RSTA      (0x01000000)  //!< Bit mask for USDHC_SYS_CTRL_RSTA.

//! @brief Get value of USDHC_SYS_CTRL_RSTA from a register value.
#define BG_USDHC_SYS_CTRL_RSTA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_RSTA) >> BP_USDHC_SYS_CTRL_RSTA)

//! @brief Format value for bitfield USDHC_SYS_CTRL_RSTA.
#define BF_USDHC_SYS_CTRL_RSTA(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_RSTA) & BM_USDHC_SYS_CTRL_RSTA)


/* --- Register HW_USDHC_SYS_CTRL, field RSTC[25] (WORZ)
 *
 * Software Reset For CMD Line: Only part of the command circuit is reset. The following registers
 * and bits are cleared by this bit: Present State register Command Inhibit (CMD) Interrupt Status
 * register Command Complete
 *
 * Values:
 * 0 - No Reset
 * 1 - Reset
 */

#define BP_USDHC_SYS_CTRL_RSTC      (25)      //!< Bit position for USDHC_SYS_CTRL_RSTC.
#define BM_USDHC_SYS_CTRL_RSTC      (0x02000000)  //!< Bit mask for USDHC_SYS_CTRL_RSTC.

//! @brief Get value of USDHC_SYS_CTRL_RSTC from a register value.
#define BG_USDHC_SYS_CTRL_RSTC(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_RSTC) >> BP_USDHC_SYS_CTRL_RSTC)

//! @brief Format value for bitfield USDHC_SYS_CTRL_RSTC.
#define BF_USDHC_SYS_CTRL_RSTC(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_RSTC) & BM_USDHC_SYS_CTRL_RSTC)


/* --- Register HW_USDHC_SYS_CTRL, field RSTD[26] (WORZ)
 *
 * Software Reset For DAT Line: Only part of the data circuit is reset. DMA circuit is also reset.
 * The following registers and bits are cleared by this bit: Data Port register Buffer is cleared
 * and initialized.Present State register Buffer Read Enable Buffer Write Enable Read Transfer
 * Active Write Transfer Active DAT Line Active Command Inhibit (DAT) Protocol Control register
 * Continue Request Stop At Block Gap Request Interrupt Status register Buffer Read Ready Buffer
 * Write Ready DMA Interrupt Block Gap Event Transfer Complete
 *
 * Values:
 * 0 - No Reset
 * 1 - Reset
 */

#define BP_USDHC_SYS_CTRL_RSTD      (26)      //!< Bit position for USDHC_SYS_CTRL_RSTD.
#define BM_USDHC_SYS_CTRL_RSTD      (0x04000000)  //!< Bit mask for USDHC_SYS_CTRL_RSTD.

//! @brief Get value of USDHC_SYS_CTRL_RSTD from a register value.
#define BG_USDHC_SYS_CTRL_RSTD(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_RSTD) >> BP_USDHC_SYS_CTRL_RSTD)

//! @brief Format value for bitfield USDHC_SYS_CTRL_RSTD.
#define BF_USDHC_SYS_CTRL_RSTD(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_RSTD) & BM_USDHC_SYS_CTRL_RSTD)


/* --- Register HW_USDHC_SYS_CTRL, field INITA[27] (RW)
 *
 * Initialization Active: When this bit is set, 80 SD-Clocks are sent to the card. After the 80
 * clocks are sent, this bit is self cleared. This bit is very useful during the card power-up
 * period when 74 SD-Clocks are needed and the clock auto gating feature is enabled. Writing 1 to
 * this bit when this bit is already 1 has no effect. Writing 0 to this bit at any time has no
 * effect. When either of the CIHB and CDIHB bits in the Present State Register are set, writing 1
 * to this bit is ignored (i.e. when command line or data lines are active, write to this bit is not
 * allowed). On the otherhand, when this bit is set, i.e., during intialization active period, it is
 * allowed to issue command, and the command bit stream will appear on the CMD pad after all 80
 * clock cycles are done. So when this command ends, the driver can make sure the 80 clock cycles
 * are sent out. This is very useful when the driver needs send 80 cycles to the card and does not
 * want to wait till this bit is self cleared.
 */

#define BP_USDHC_SYS_CTRL_INITA      (27)      //!< Bit position for USDHC_SYS_CTRL_INITA.
#define BM_USDHC_SYS_CTRL_INITA      (0x08000000)  //!< Bit mask for USDHC_SYS_CTRL_INITA.

//! @brief Get value of USDHC_SYS_CTRL_INITA from a register value.
#define BG_USDHC_SYS_CTRL_INITA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_SYS_CTRL_INITA) >> BP_USDHC_SYS_CTRL_INITA)

//! @brief Format value for bitfield USDHC_SYS_CTRL_INITA.
#define BF_USDHC_SYS_CTRL_INITA(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_SYS_CTRL_INITA) & BM_USDHC_SYS_CTRL_INITA)

#ifndef __LANGUAGE_ASM__
//! @brief Set the INITA field to a new value.
#define BW_USDHC_SYS_CTRL_INITA(x, v)   (HW_USDHC_SYS_CTRL_WR(x, (HW_USDHC_SYS_CTRL_RD(x) & ~BM_USDHC_SYS_CTRL_INITA) | BF_USDHC_SYS_CTRL_INITA(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_INT_STATUS - Interrupt Status
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_INT_STATUS - Interrupt Status (W1C)
 *
 * Reset value: 0x00000000
 *
 * An interrupt is generated when the Normal Interrupt Signal Enable is enabled and at least one of
 * the status bits is set to 1. For all bits, writing 1 to a bit clears it; writing to 0 keeps the
 * bit unchanged. More than one status can be cleared with a single register write. For Card
 * Interrupt, before writing 1 to clear, it is required that the card stops asserting the interrupt,
 * meaning that when the Card Driver services the interrupt condition, otherwise the CINT bit will
 * be asserted again.  The table below shows the relationship between the Command Timeout Error and
 * the Command Complete.   uSDHC Status for Command Timeout Error/Command Complete Bit Combinations
 * Command Complete    Command Timeout Error    Meaning of the Status        0    0    X      X    1
 * Response not received within 64 SDCLK cycles      1    0    Response received       The table
 * below shows the relationship between the Transfer Complete and the Data Timeout Error.   uSDHC
 * Status for Data Timeout Error/Transfer Complete Bit Combinations         Transfer Complete
 * Data Timeout Error    Meaning of the Status        0    0    X      0    1    Timeout occurred
 * during transfer      1    X    Data Transfer Complete       The table below shows the
 * relationship between the Command CRC Error and Command Timeout Error.   uSDHC Status for Command
 * CRC Error/Command Timeout Error Bit Combinations         Command Complete    Command Timeout
 * Error    Meaning of the Status        0    0    No error      0    1    Response Timeout Error
 * 1    0    Response CRC Error      1    1    CMD line conflict
 */
typedef union _hw_usdhc_int_status
{
    reg32_t U;
    struct _hw_usdhc_int_status_bitfields
    {
        unsigned CC : 1; //!< [0] Command Complete: This bit is set when you receive the end bit of the command response (except Auto CMD12).
        unsigned TC : 1; //!< [1] Transfer Complete: This bit is set when a read or write transfer is completed.
        unsigned BGE : 1; //!< [2] Block Gap Event: If the Stop At Block Gap Request bit in the Protocol Control register is set, this bit is set when a read or write transaction is stopped at a block gap.
        unsigned DINT : 1; //!< [3] DMA Interrupt: Occurs only when the internal DMA finishes the data transfer successfully.
        unsigned BWR : 1; //!< [4] Buffer Write Ready: This status bit is set if the Buffer Write Enable bit, in the Present State register, changes from 0 to 1.
        unsigned BRR : 1; //!< [5] Buffer Read Ready: This status bit is set if the Buffer Read Enable bit, in the Present State register, changes from 0 to 1.
        unsigned CINS : 1; //!< [6] Card Insertion: This status bit is set if the Card Inserted bit in the Present State register changes from 0 to 1.
        unsigned CRM : 1; //!< [7] Card Removal: This status bit is set if the Card Inserted bit in the Present State register changes from 1 to 0.
        unsigned CINT : 1; //!< [8] Card Interrupt: This status bit is set when an interrupt signal is detected from the external card.
        unsigned RESERVED0 : 3; //!< [11:9] Reserved
        unsigned RTE : 1; //!< [12] Re-Tuning Event: (only for SD3.0 SDR104 mode) This status is set if Re-Tuning Request in the Present State register changes from 0 to 1.
        unsigned RESERVED1 : 1; //!< [13] Reserved
        unsigned TP : 1; //!< [14] Tuning Pass:(only for SD3.0 SDR104 mode) Current CMD19 transfer is done successfully.
        unsigned RESERVED2 : 1; //!< [15] Reserved
        unsigned CTOE : 1; //!< [16] Command Timeout Error: Occurs only if no response is returned within 64 SDCLK cycles from the end bit of the command.
        unsigned CCE : 1; //!< [17] Command CRC Error: Command CRC Error is generated in two cases.
        unsigned CEBE : 1; //!< [18] Command End Bit Error: Occurs when detecting that the end bit of a command response is 0.
        unsigned CIE : 1; //!< [19] Command Index Error: Occurs if a Command Index error occurs in the command response.
        unsigned DTOE : 1; //!< [20] Data Timeout Error: Occurs when detecting one of following time-out conditions.
        unsigned DCE : 1; //!< [21] Data CRC Error: Occurs when detecting a CRC error when transferring read data, which uses the DAT line, or when detecting the Write CRC status having a value other than 010.
        unsigned DEBE : 1; //!< [22] Data End Bit Error: Occurs either when detecting 0 at the end bit position of read data, which uses the DAT line, or at the end bit position of the CRC.
        unsigned RESERVED3 : 1; //!< [23] Reserved
        unsigned AC12E : 1; //!< [24] Auto CMD12 Error: Occurs when detecting that one of the bits in the Auto CMD12 Error Status register has changed from 0 to 1.
        unsigned RESERVED4 : 1; //!< [25] Reserved
        unsigned TNE : 1; //!< [26] Tuning Error: (only for SD3.0 SDR104 mode) This bit is set when an unrecoverable error is detected in a tuning circuit.
        unsigned RESERVED5 : 1; //!< [27] Reserved
        unsigned DMAE : 1; //!< [28] DMA Error: Occurs when an Internal DMA transfer has failed.
        unsigned RESERVED6 : 3; //!< [31:29] Reserved
    } B;
} hw_usdhc_int_status_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_INT_STATUS register
 */
#define HW_USDHC_INT_STATUS_ADDR(x)      (REGS_USDHC_BASE(x) + 0x30)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_INT_STATUS(x)           (*(volatile hw_usdhc_int_status_t *) HW_USDHC_INT_STATUS_ADDR(x))
#define HW_USDHC_INT_STATUS_RD(x)        (HW_USDHC_INT_STATUS(x).U)
#define HW_USDHC_INT_STATUS_WR(x, v)     (HW_USDHC_INT_STATUS(x).U = (v))
#define HW_USDHC_INT_STATUS_SET(x, v)    (HW_USDHC_INT_STATUS_WR(x, HW_USDHC_INT_STATUS_RD(x) |  (v)))
#define HW_USDHC_INT_STATUS_CLR(x, v)    (HW_USDHC_INT_STATUS_WR(x, HW_USDHC_INT_STATUS_RD(x) & ~(v)))
#define HW_USDHC_INT_STATUS_TOG(x, v)    (HW_USDHC_INT_STATUS_WR(x, HW_USDHC_INT_STATUS_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_INT_STATUS bitfields
 */

/* --- Register HW_USDHC_INT_STATUS, field CC[0] (W1C)
 *
 * Command Complete: This bit is set when you receive the end bit of the command response (except
 * Auto CMD12). Refer to the Command Inhibit (CMD) in the Present State register.
 *
 * Values:
 * 0 - Command not complete
 * 1 - Command complete
 */

#define BP_USDHC_INT_STATUS_CC      (0)      //!< Bit position for USDHC_INT_STATUS_CC.
#define BM_USDHC_INT_STATUS_CC      (0x00000001)  //!< Bit mask for USDHC_INT_STATUS_CC.

//! @brief Get value of USDHC_INT_STATUS_CC from a register value.
#define BG_USDHC_INT_STATUS_CC(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CC) >> BP_USDHC_INT_STATUS_CC)

//! @brief Format value for bitfield USDHC_INT_STATUS_CC.
#define BF_USDHC_INT_STATUS_CC(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CC) & BM_USDHC_INT_STATUS_CC)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CC field to a new value.
#define BW_USDHC_INT_STATUS_CC(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CC) | BF_USDHC_INT_STATUS_CC(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field TC[1] (W1C)
 *
 * Transfer Complete: This bit is set when a read or write transfer is completed. In the case of a
 * Read Transaction: This bit is set at the falling edge of the Read Transfer Active Status. There
 * are two cases in which this interrupt is generated. The first is when a data transfer is
 * completed as specified by the data length (after the last data has been read to the Host System).
 * The second is when data has stopped at the block gap and completed the data transfer by setting
 * the Stop At Block Gap Request bit in the Protocol Control register (after valid data has been
 * read to the Host System). In the case of a Write Transaction: This bit is set at the falling edge
 * of the DAT Line Active Status. There are two cases in which this interrupt is generated. The
 * first is when the last data is written to the SD card as specified by the data length and the
 * busy signal is released. The second is when data transfers are stopped at the block gap, by
 * setting the Stop At Block Gap Request bit in the Protocol Control register, and the data
 * transfers are completed. (after valid data is written to the SD card and the busy signal
 * released).
 *
 * Values:
 * 0 - Transfer not complete
 * 1 - Transfer complete
 */

#define BP_USDHC_INT_STATUS_TC      (1)      //!< Bit position for USDHC_INT_STATUS_TC.
#define BM_USDHC_INT_STATUS_TC      (0x00000002)  //!< Bit mask for USDHC_INT_STATUS_TC.

//! @brief Get value of USDHC_INT_STATUS_TC from a register value.
#define BG_USDHC_INT_STATUS_TC(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_TC) >> BP_USDHC_INT_STATUS_TC)

//! @brief Format value for bitfield USDHC_INT_STATUS_TC.
#define BF_USDHC_INT_STATUS_TC(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_TC) & BM_USDHC_INT_STATUS_TC)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TC field to a new value.
#define BW_USDHC_INT_STATUS_TC(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_TC) | BF_USDHC_INT_STATUS_TC(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field BGE[2] (W1C)
 *
 * Block Gap Event: If the Stop At Block Gap Request bit in the Protocol Control register is set,
 * this bit is set when a read or write transaction is stopped at a block gap. If Stop At Block Gap
 * Request is not set to 1, this bit is not set to 1. In the case of a Read Transaction: This bit is
 * set at the falling edge of the DAT Line Active Status (When the transaction is stopped at SD Bus
 * timing). The Read Wait must be supported in order to use this function. In the case of Write
 * Transaction: This bit is set at the falling edge of Write Transfer Active Status (After getting
 * CRC status at SD Bus timing).
 *
 * Values:
 * 0 - No block gap event
 * 1 - Transaction stopped at block gap
 */

#define BP_USDHC_INT_STATUS_BGE      (2)      //!< Bit position for USDHC_INT_STATUS_BGE.
#define BM_USDHC_INT_STATUS_BGE      (0x00000004)  //!< Bit mask for USDHC_INT_STATUS_BGE.

//! @brief Get value of USDHC_INT_STATUS_BGE from a register value.
#define BG_USDHC_INT_STATUS_BGE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_BGE) >> BP_USDHC_INT_STATUS_BGE)

//! @brief Format value for bitfield USDHC_INT_STATUS_BGE.
#define BF_USDHC_INT_STATUS_BGE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_BGE) & BM_USDHC_INT_STATUS_BGE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BGE field to a new value.
#define BW_USDHC_INT_STATUS_BGE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_BGE) | BF_USDHC_INT_STATUS_BGE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field DINT[3] (W1C)
 *
 * DMA Interrupt: Occurs only when the internal DMA finishes the data transfer successfully.
 * Whenever errors occur during data transfer, this bit will not be set. Instead, the DMAE bit will
 * be set. Either Simple DMA or ADMA finishes data transferring, this bit will be set.
 *
 * Values:
 * 0 - No DMA Interrupt
 * 1 - DMA Interrupt is generated
 */

#define BP_USDHC_INT_STATUS_DINT      (3)      //!< Bit position for USDHC_INT_STATUS_DINT.
#define BM_USDHC_INT_STATUS_DINT      (0x00000008)  //!< Bit mask for USDHC_INT_STATUS_DINT.

//! @brief Get value of USDHC_INT_STATUS_DINT from a register value.
#define BG_USDHC_INT_STATUS_DINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_DINT) >> BP_USDHC_INT_STATUS_DINT)

//! @brief Format value for bitfield USDHC_INT_STATUS_DINT.
#define BF_USDHC_INT_STATUS_DINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_DINT) & BM_USDHC_INT_STATUS_DINT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DINT field to a new value.
#define BW_USDHC_INT_STATUS_DINT(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_DINT) | BF_USDHC_INT_STATUS_DINT(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field BWR[4] (W1C)
 *
 * Buffer Write Ready: This status bit is set if the Buffer Write Enable bit, in the Present State
 * register, changes from 0 to 1. Refer to the Buffer Write Enable bit in the Present State register
 * for additional information.
 *
 * Values:
 * 0 - Not ready to write buffer
 * 1 - Ready to write buffer:
 */

#define BP_USDHC_INT_STATUS_BWR      (4)      //!< Bit position for USDHC_INT_STATUS_BWR.
#define BM_USDHC_INT_STATUS_BWR      (0x00000010)  //!< Bit mask for USDHC_INT_STATUS_BWR.

//! @brief Get value of USDHC_INT_STATUS_BWR from a register value.
#define BG_USDHC_INT_STATUS_BWR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_BWR) >> BP_USDHC_INT_STATUS_BWR)

//! @brief Format value for bitfield USDHC_INT_STATUS_BWR.
#define BF_USDHC_INT_STATUS_BWR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_BWR) & BM_USDHC_INT_STATUS_BWR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BWR field to a new value.
#define BW_USDHC_INT_STATUS_BWR(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_BWR) | BF_USDHC_INT_STATUS_BWR(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field BRR[5] (W1C)
 *
 * Buffer Read Ready: This status bit is set if the Buffer Read Enable bit, in the Present State
 * register, changes from 0 to 1. Refer to the Buffer Read Enable bit in the Present State register
 * for additional information.
 *
 * Values:
 * 0 - Not ready to read buffer
 * 1 - Ready to read buffer
 */

#define BP_USDHC_INT_STATUS_BRR      (5)      //!< Bit position for USDHC_INT_STATUS_BRR.
#define BM_USDHC_INT_STATUS_BRR      (0x00000020)  //!< Bit mask for USDHC_INT_STATUS_BRR.

//! @brief Get value of USDHC_INT_STATUS_BRR from a register value.
#define BG_USDHC_INT_STATUS_BRR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_BRR) >> BP_USDHC_INT_STATUS_BRR)

//! @brief Format value for bitfield USDHC_INT_STATUS_BRR.
#define BF_USDHC_INT_STATUS_BRR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_BRR) & BM_USDHC_INT_STATUS_BRR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BRR field to a new value.
#define BW_USDHC_INT_STATUS_BRR(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_BRR) | BF_USDHC_INT_STATUS_BRR(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CINS[6] (W1C)
 *
 * Card Insertion: This status bit is set if the Card Inserted bit in the Present State register
 * changes from 0 to 1. When the Host Driver writes this bit to 1 to clear this status, the status
 * of the Card Inserted in the Present State register should be confirmed. Because the card state
 * may possibly be changed when the Host Driver clears this bit and the interrupt event may not be
 * generated. When this bit is cleared, it will be set again if a card is inserted. In order to
 * leave it cleared, clear the Card Inserted Status Enable bit in Interrupt Status Enable register.
 *
 * Values:
 * 0 - Card state unstable or removed
 * 1 - Card inserted
 */

#define BP_USDHC_INT_STATUS_CINS      (6)      //!< Bit position for USDHC_INT_STATUS_CINS.
#define BM_USDHC_INT_STATUS_CINS      (0x00000040)  //!< Bit mask for USDHC_INT_STATUS_CINS.

//! @brief Get value of USDHC_INT_STATUS_CINS from a register value.
#define BG_USDHC_INT_STATUS_CINS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CINS) >> BP_USDHC_INT_STATUS_CINS)

//! @brief Format value for bitfield USDHC_INT_STATUS_CINS.
#define BF_USDHC_INT_STATUS_CINS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CINS) & BM_USDHC_INT_STATUS_CINS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINS field to a new value.
#define BW_USDHC_INT_STATUS_CINS(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CINS) | BF_USDHC_INT_STATUS_CINS(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CRM[7] (W1C)
 *
 * Card Removal: This status bit is set if the Card Inserted bit in the Present State register
 * changes from 1 to 0. When the Host Driver writes this bit to 1 to clear this status, the status
 * of the Card Inserted in the Present State register should be confirmed. Because the card state
 * may possibly be changed when the Host Driver clears this bit and the interrupt event may not be
 * generated. When this bit is cleared, it will be set again if no card is inserted. In order to
 * leave it cleared, clear the Card Removal Status Enable bit in Interrupt Status Enable register.
 *
 * Values:
 * 0 - Card state unstable or inserted
 * 1 - Card removed
 */

#define BP_USDHC_INT_STATUS_CRM      (7)      //!< Bit position for USDHC_INT_STATUS_CRM.
#define BM_USDHC_INT_STATUS_CRM      (0x00000080)  //!< Bit mask for USDHC_INT_STATUS_CRM.

//! @brief Get value of USDHC_INT_STATUS_CRM from a register value.
#define BG_USDHC_INT_STATUS_CRM(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CRM) >> BP_USDHC_INT_STATUS_CRM)

//! @brief Format value for bitfield USDHC_INT_STATUS_CRM.
#define BF_USDHC_INT_STATUS_CRM(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CRM) & BM_USDHC_INT_STATUS_CRM)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRM field to a new value.
#define BW_USDHC_INT_STATUS_CRM(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CRM) | BF_USDHC_INT_STATUS_CRM(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CINT[8] (W1C)
 *
 * Card Interrupt: This status bit is set when an interrupt signal is detected from the external
 * card. In 1-bit mode, the uSDHC will detect the Card Interrupt without the SD Clock to support
 * wakeup. In 4-bit mode, the card interrupt signal is sampled during the interrupt cycle, so the
 * interrupt from card can only be sampled during interrupt cycle, introducing some delay between
 * the interrupt signal from the SDIO card and the interrupt to the Host System. Writing this bit to
 * 1 can clear this bit, but as the interrupt factor from the SDIO card does not clear, this bit is
 * set again. In order to clear this bit, it is required to reset the interrupt factor from the
 * external card followed by a writing 1 to this bit. When this status has been set, and the Host
 * Driver needs to service this interrupt, the Card Interrupt Signal Enable in the Interrupt Signal
 * Enable register should be 0 to stop driving the interrupt signal to the Host System. After
 * completion of the card interrupt service (It should reset the interrupt factors in the SDIO card
 * and the interrupt signal may not be asserted), write 1 to clear this bit, set the Card Interrupt
 * Signal Enable to 1, and start sampling the interrupt signal again.
 *
 * Values:
 * 0 - No Card Interrupt
 * 1 - Generate Card Interrupt
 */

#define BP_USDHC_INT_STATUS_CINT      (8)      //!< Bit position for USDHC_INT_STATUS_CINT.
#define BM_USDHC_INT_STATUS_CINT      (0x00000100)  //!< Bit mask for USDHC_INT_STATUS_CINT.

//! @brief Get value of USDHC_INT_STATUS_CINT from a register value.
#define BG_USDHC_INT_STATUS_CINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CINT) >> BP_USDHC_INT_STATUS_CINT)

//! @brief Format value for bitfield USDHC_INT_STATUS_CINT.
#define BF_USDHC_INT_STATUS_CINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CINT) & BM_USDHC_INT_STATUS_CINT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINT field to a new value.
#define BW_USDHC_INT_STATUS_CINT(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CINT) | BF_USDHC_INT_STATUS_CINT(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field RTE[12] (W1C)
 *
 * Re-Tuning Event: (only for SD3.0 SDR104 mode) This status is set if Re-Tuning Request in the
 * Present State register changes from 0 to 1. Host Controller requests Host Driver to perform re-
 * tuning for next data transfer. Current data transfer (not large block count) can be completed
 * without re-tuning.
 *
 * Values:
 * 0 - Re-Tuning is not required
 * 1 - Re-Tuning should be performed
 */

#define BP_USDHC_INT_STATUS_RTE      (12)      //!< Bit position for USDHC_INT_STATUS_RTE.
#define BM_USDHC_INT_STATUS_RTE      (0x00001000)  //!< Bit mask for USDHC_INT_STATUS_RTE.

//! @brief Get value of USDHC_INT_STATUS_RTE from a register value.
#define BG_USDHC_INT_STATUS_RTE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_RTE) >> BP_USDHC_INT_STATUS_RTE)

//! @brief Format value for bitfield USDHC_INT_STATUS_RTE.
#define BF_USDHC_INT_STATUS_RTE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_RTE) & BM_USDHC_INT_STATUS_RTE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RTE field to a new value.
#define BW_USDHC_INT_STATUS_RTE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_RTE) | BF_USDHC_INT_STATUS_RTE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field TP[14] (W1C)
 *
 * Tuning Pass:(only for SD3.0 SDR104 mode) Current CMD19 transfer is done successfully. That is,
 * current sampling point is correct.
 */

#define BP_USDHC_INT_STATUS_TP      (14)      //!< Bit position for USDHC_INT_STATUS_TP.
#define BM_USDHC_INT_STATUS_TP      (0x00004000)  //!< Bit mask for USDHC_INT_STATUS_TP.

//! @brief Get value of USDHC_INT_STATUS_TP from a register value.
#define BG_USDHC_INT_STATUS_TP(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_TP) >> BP_USDHC_INT_STATUS_TP)

//! @brief Format value for bitfield USDHC_INT_STATUS_TP.
#define BF_USDHC_INT_STATUS_TP(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_TP) & BM_USDHC_INT_STATUS_TP)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TP field to a new value.
#define BW_USDHC_INT_STATUS_TP(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_TP) | BF_USDHC_INT_STATUS_TP(v)))
#endif

/* --- Register HW_USDHC_INT_STATUS, field CTOE[16] (W1C)
 *
 * Command Timeout Error: Occurs only if no response is returned within 64 SDCLK cycles from the end
 * bit of the command. If the uSDHC detects a CMD line conflict, in which case a Command CRC Error
 * shall also be set (as shown in ), this bit shall be set without waiting for 64 SDCLK cycles. This
 * is because the command will be aborted by the uSDHC.
 *
 * Values:
 * 0 - No Error
 * 1 - Time out
 */

#define BP_USDHC_INT_STATUS_CTOE      (16)      //!< Bit position for USDHC_INT_STATUS_CTOE.
#define BM_USDHC_INT_STATUS_CTOE      (0x00010000)  //!< Bit mask for USDHC_INT_STATUS_CTOE.

//! @brief Get value of USDHC_INT_STATUS_CTOE from a register value.
#define BG_USDHC_INT_STATUS_CTOE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CTOE) >> BP_USDHC_INT_STATUS_CTOE)

//! @brief Format value for bitfield USDHC_INT_STATUS_CTOE.
#define BF_USDHC_INT_STATUS_CTOE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CTOE) & BM_USDHC_INT_STATUS_CTOE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CTOE field to a new value.
#define BW_USDHC_INT_STATUS_CTOE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CTOE) | BF_USDHC_INT_STATUS_CTOE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CCE[17] (W1C)
 *
 * Command CRC Error: Command CRC Error is generated in two cases. If a response is returned and the
 * Command Timeout Error is set to 0 (indicating no time-out), this bit is set when detecting a CRC
 * error in the command response. The uSDHC detects a CMD line conflict by monitoring the CMD line
 * when a command is issued. If the uSDHC drives the CMD line to 1, but detects 0 on the CMD line at
 * the next SDCLK edge, then the uSDHC shall abort the command (Stop driving CMD line) and set this
 * bit to 1. The Command Timeout Error shall also be set to 1 to distinguish CMD line conflict.
 *
 * Values:
 * 0 - No Error
 * 1 - CRC Error Generated.
 */

#define BP_USDHC_INT_STATUS_CCE      (17)      //!< Bit position for USDHC_INT_STATUS_CCE.
#define BM_USDHC_INT_STATUS_CCE      (0x00020000)  //!< Bit mask for USDHC_INT_STATUS_CCE.

//! @brief Get value of USDHC_INT_STATUS_CCE from a register value.
#define BG_USDHC_INT_STATUS_CCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CCE) >> BP_USDHC_INT_STATUS_CCE)

//! @brief Format value for bitfield USDHC_INT_STATUS_CCE.
#define BF_USDHC_INT_STATUS_CCE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CCE) & BM_USDHC_INT_STATUS_CCE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCE field to a new value.
#define BW_USDHC_INT_STATUS_CCE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CCE) | BF_USDHC_INT_STATUS_CCE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CEBE[18] (W1C)
 *
 * Command End Bit Error: Occurs when detecting that the end bit of a command response is 0.
 *
 * Values:
 * 0 - No Error
 * 1 - End Bit Error Generated
 */

#define BP_USDHC_INT_STATUS_CEBE      (18)      //!< Bit position for USDHC_INT_STATUS_CEBE.
#define BM_USDHC_INT_STATUS_CEBE      (0x00040000)  //!< Bit mask for USDHC_INT_STATUS_CEBE.

//! @brief Get value of USDHC_INT_STATUS_CEBE from a register value.
#define BG_USDHC_INT_STATUS_CEBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CEBE) >> BP_USDHC_INT_STATUS_CEBE)

//! @brief Format value for bitfield USDHC_INT_STATUS_CEBE.
#define BF_USDHC_INT_STATUS_CEBE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CEBE) & BM_USDHC_INT_STATUS_CEBE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CEBE field to a new value.
#define BW_USDHC_INT_STATUS_CEBE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CEBE) | BF_USDHC_INT_STATUS_CEBE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field CIE[19] (W1C)
 *
 * Command Index Error: Occurs if a Command Index error occurs in the command response.
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_INT_STATUS_CIE      (19)      //!< Bit position for USDHC_INT_STATUS_CIE.
#define BM_USDHC_INT_STATUS_CIE      (0x00080000)  //!< Bit mask for USDHC_INT_STATUS_CIE.

//! @brief Get value of USDHC_INT_STATUS_CIE from a register value.
#define BG_USDHC_INT_STATUS_CIE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_CIE) >> BP_USDHC_INT_STATUS_CIE)

//! @brief Format value for bitfield USDHC_INT_STATUS_CIE.
#define BF_USDHC_INT_STATUS_CIE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_CIE) & BM_USDHC_INT_STATUS_CIE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CIE field to a new value.
#define BW_USDHC_INT_STATUS_CIE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_CIE) | BF_USDHC_INT_STATUS_CIE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field DTOE[20] (W1C)
 *
 * Data Timeout Error: Occurs when detecting one of following time-out conditions. Busy time-out for
 * R1b,R5b type Busy time-out after Write CRC status Read Data time-out.
 *
 * Values:
 * 0 - No Error
 * 1 - Time out
 */

#define BP_USDHC_INT_STATUS_DTOE      (20)      //!< Bit position for USDHC_INT_STATUS_DTOE.
#define BM_USDHC_INT_STATUS_DTOE      (0x00100000)  //!< Bit mask for USDHC_INT_STATUS_DTOE.

//! @brief Get value of USDHC_INT_STATUS_DTOE from a register value.
#define BG_USDHC_INT_STATUS_DTOE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_DTOE) >> BP_USDHC_INT_STATUS_DTOE)

//! @brief Format value for bitfield USDHC_INT_STATUS_DTOE.
#define BF_USDHC_INT_STATUS_DTOE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_DTOE) & BM_USDHC_INT_STATUS_DTOE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTOE field to a new value.
#define BW_USDHC_INT_STATUS_DTOE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_DTOE) | BF_USDHC_INT_STATUS_DTOE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field DCE[21] (W1C)
 *
 * Data CRC Error: Occurs when detecting a CRC error when transferring read data, which uses the DAT
 * line, or when detecting the Write CRC status having a value other than 010.
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_INT_STATUS_DCE      (21)      //!< Bit position for USDHC_INT_STATUS_DCE.
#define BM_USDHC_INT_STATUS_DCE      (0x00200000)  //!< Bit mask for USDHC_INT_STATUS_DCE.

//! @brief Get value of USDHC_INT_STATUS_DCE from a register value.
#define BG_USDHC_INT_STATUS_DCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_DCE) >> BP_USDHC_INT_STATUS_DCE)

//! @brief Format value for bitfield USDHC_INT_STATUS_DCE.
#define BF_USDHC_INT_STATUS_DCE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_DCE) & BM_USDHC_INT_STATUS_DCE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DCE field to a new value.
#define BW_USDHC_INT_STATUS_DCE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_DCE) | BF_USDHC_INT_STATUS_DCE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field DEBE[22] (W1C)
 *
 * Data End Bit Error: Occurs either when detecting 0 at the end bit position of read data, which
 * uses the DAT line, or at the end bit position of the CRC.
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_INT_STATUS_DEBE      (22)      //!< Bit position for USDHC_INT_STATUS_DEBE.
#define BM_USDHC_INT_STATUS_DEBE      (0x00400000)  //!< Bit mask for USDHC_INT_STATUS_DEBE.

//! @brief Get value of USDHC_INT_STATUS_DEBE from a register value.
#define BG_USDHC_INT_STATUS_DEBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_DEBE) >> BP_USDHC_INT_STATUS_DEBE)

//! @brief Format value for bitfield USDHC_INT_STATUS_DEBE.
#define BF_USDHC_INT_STATUS_DEBE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_DEBE) & BM_USDHC_INT_STATUS_DEBE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DEBE field to a new value.
#define BW_USDHC_INT_STATUS_DEBE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_DEBE) | BF_USDHC_INT_STATUS_DEBE(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field AC12E[24] (W1C)
 *
 * Auto CMD12 Error: Occurs when detecting that one of the bits in the Auto CMD12 Error Status
 * register has changed from 0 to 1. This bit is set to 1, not only when the errors in Auto CMD12
 * occur, but also when the Auto CMD12 is not executed due to the previous command error.
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_INT_STATUS_AC12E      (24)      //!< Bit position for USDHC_INT_STATUS_AC12E.
#define BM_USDHC_INT_STATUS_AC12E      (0x01000000)  //!< Bit mask for USDHC_INT_STATUS_AC12E.

//! @brief Get value of USDHC_INT_STATUS_AC12E from a register value.
#define BG_USDHC_INT_STATUS_AC12E(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_AC12E) >> BP_USDHC_INT_STATUS_AC12E)

//! @brief Format value for bitfield USDHC_INT_STATUS_AC12E.
#define BF_USDHC_INT_STATUS_AC12E(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_AC12E) & BM_USDHC_INT_STATUS_AC12E)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12E field to a new value.
#define BW_USDHC_INT_STATUS_AC12E(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_AC12E) | BF_USDHC_INT_STATUS_AC12E(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS, field TNE[26] (W1C)
 *
 * Tuning Error: (only for SD3.0 SDR104 mode) This bit is set when an unrecoverable error is
 * detected in a tuning circuit. By detecting Tuning Error, Host Driver needs to abort a command
 * executeing and perform tuning.
 */

#define BP_USDHC_INT_STATUS_TNE      (26)      //!< Bit position for USDHC_INT_STATUS_TNE.
#define BM_USDHC_INT_STATUS_TNE      (0x04000000)  //!< Bit mask for USDHC_INT_STATUS_TNE.

//! @brief Get value of USDHC_INT_STATUS_TNE from a register value.
#define BG_USDHC_INT_STATUS_TNE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_TNE) >> BP_USDHC_INT_STATUS_TNE)

//! @brief Format value for bitfield USDHC_INT_STATUS_TNE.
#define BF_USDHC_INT_STATUS_TNE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_TNE) & BM_USDHC_INT_STATUS_TNE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TNE field to a new value.
#define BW_USDHC_INT_STATUS_TNE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_TNE) | BF_USDHC_INT_STATUS_TNE(v)))
#endif

/* --- Register HW_USDHC_INT_STATUS, field DMAE[28] (W1C)
 *
 * DMA Error: Occurs when an Internal DMA transfer has failed. This bit is set to 1, when some error
 * occurs in the data transfer. This error can be caused by either Simple DMA or ADMA, depending on
 * which DMA is in use. The value in DMA System Address register is the next fetch address where the
 * error occurs. Since any error corrupts the whole data block, the Host Driver shall re-start the
 * transfer from the corrupted block boundary. The address of the block boundary can be calculated
 * either from the current DS_ADDR value or from the remaining number of blocks and the block size.
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_INT_STATUS_DMAE      (28)      //!< Bit position for USDHC_INT_STATUS_DMAE.
#define BM_USDHC_INT_STATUS_DMAE      (0x10000000)  //!< Bit mask for USDHC_INT_STATUS_DMAE.

//! @brief Get value of USDHC_INT_STATUS_DMAE from a register value.
#define BG_USDHC_INT_STATUS_DMAE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_DMAE) >> BP_USDHC_INT_STATUS_DMAE)

//! @brief Format value for bitfield USDHC_INT_STATUS_DMAE.
#define BF_USDHC_INT_STATUS_DMAE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_DMAE) & BM_USDHC_INT_STATUS_DMAE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DMAE field to a new value.
#define BW_USDHC_INT_STATUS_DMAE(x, v)   (HW_USDHC_INT_STATUS_WR(x, (HW_USDHC_INT_STATUS_RD(x) & ~BM_USDHC_INT_STATUS_DMAE) | BF_USDHC_INT_STATUS_DMAE(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_INT_STATUS_EN - Interrupt Status Enable
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_INT_STATUS_EN - Interrupt Status Enable (RW)
 *
 * Reset value: 0x157f413f
 *
 * Setting the bits in this register to 1 enables the corresponding Interrupt Status to be set by
 * the specified event. If any bit is cleared, the corresponding Interrupt Status bit is also
 * cleared (i.e. when the bit in this register is cleared, the corresponding bit in Interrupt Status
 * Register is always 0).   Depending on IABG bit setting, uSDHC may be programmed to sample the
 * card interrupt signal during the interrupt period and hold its value in the flip-flop. There will
 * be some delays on the Card Interrupt, asserted from the card, to the time the Host System is
 * informed.  To detect a CMD line conflict, the Host Driver must set both Command Timeout Error
 * Status Enable and Command CRC Error Status Enable to 1.
 */
typedef union _hw_usdhc_int_status_en
{
    reg32_t U;
    struct _hw_usdhc_int_status_en_bitfields
    {
        unsigned CCSEN : 1; //!< [0] Command Complete Status Enable: 1 Enabled 0 Masked
        unsigned TCSEN : 1; //!< [1] Transfer Complete Status Enable:
        unsigned BGESEN : 1; //!< [2] Block Gap Event Status Enable:
        unsigned DINTSEN : 1; //!< [3] DMA Interrupt Status Enable:
        unsigned BWRSEN : 1; //!< [4] Buffer Write Ready Status Enable:
        unsigned BRRSEN : 1; //!< [5] Buffer Read Ready Status Enable:
        unsigned CINSSEN : 1; //!< [6] Card Insertion Status Enable:
        unsigned CRMSEN : 1; //!< [7] Card Removal Status Enable:
        unsigned CINTSEN : 1; //!< [8] Card Interrupt Status Enable: If this bit is set to 0, the uSDHC will clear the interrupt request to the System.
        unsigned RESERVED0 : 3; //!< [11:9] Reserved
        unsigned RTESEN : 1; //!< [12] Re-Tuning Event Status Enable
        unsigned RESERVED1 : 1; //!< [13] Reserved
        unsigned TPSEN : 1; //!< [14] Tuning Pass Status Enable
        unsigned RESERVED2 : 1; //!< [15] Reserved
        unsigned CTOESEN : 1; //!< [16] Command Timeout Error Status Enable:
        unsigned CCESEN : 1; //!< [17] Command CRC Error Status Enable:
        unsigned CEBESEN : 1; //!< [18] Command End Bit Error Status Enable:
        unsigned CIESEN : 1; //!< [19] Command Index Error Status Enable:
        unsigned DTOESEN : 1; //!< [20] Data Timeout Error Status Enable:
        unsigned DCESEN : 1; //!< [21] Data CRC Error Status Enable:
        unsigned DEBESEN : 1; //!< [22] Data End Bit Error Status Enable:
        unsigned RESERVED3 : 1; //!< [23] Reserved
        unsigned AC12ESEN : 1; //!< [24] Auto CMD12 Error Status Enable:
        unsigned RESERVED4 : 1; //!< [25] Reserved
        unsigned TNESEN : 1; //!< [26] Tuning Error Status Enable:
        unsigned RESERVED5 : 1; //!< [27] Reserved
        unsigned DMAESEN : 1; //!< [28] DMA Error Status Enable:
        unsigned RESERVED6 : 3; //!< [31:29] Reserved
    } B;
} hw_usdhc_int_status_en_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_INT_STATUS_EN register
 */
#define HW_USDHC_INT_STATUS_EN_ADDR(x)      (REGS_USDHC_BASE(x) + 0x34)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_INT_STATUS_EN(x)           (*(volatile hw_usdhc_int_status_en_t *) HW_USDHC_INT_STATUS_EN_ADDR(x))
#define HW_USDHC_INT_STATUS_EN_RD(x)        (HW_USDHC_INT_STATUS_EN(x).U)
#define HW_USDHC_INT_STATUS_EN_WR(x, v)     (HW_USDHC_INT_STATUS_EN(x).U = (v))
#define HW_USDHC_INT_STATUS_EN_SET(x, v)    (HW_USDHC_INT_STATUS_EN_WR(x, HW_USDHC_INT_STATUS_EN_RD(x) |  (v)))
#define HW_USDHC_INT_STATUS_EN_CLR(x, v)    (HW_USDHC_INT_STATUS_EN_WR(x, HW_USDHC_INT_STATUS_EN_RD(x) & ~(v)))
#define HW_USDHC_INT_STATUS_EN_TOG(x, v)    (HW_USDHC_INT_STATUS_EN_WR(x, HW_USDHC_INT_STATUS_EN_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_INT_STATUS_EN bitfields
 */

/* --- Register HW_USDHC_INT_STATUS_EN, field CCSEN[0] (RW)
 *
 * Command Complete Status Enable: 1 Enabled 0 Masked
 */

#define BP_USDHC_INT_STATUS_EN_CCSEN      (0)      //!< Bit position for USDHC_INT_STATUS_EN_CCSEN.
#define BM_USDHC_INT_STATUS_EN_CCSEN      (0x00000001)  //!< Bit mask for USDHC_INT_STATUS_EN_CCSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CCSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CCSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CCSEN) >> BP_USDHC_INT_STATUS_EN_CCSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CCSEN.
#define BF_USDHC_INT_STATUS_EN_CCSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CCSEN) & BM_USDHC_INT_STATUS_EN_CCSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CCSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CCSEN) | BF_USDHC_INT_STATUS_EN_CCSEN(v)))
#endif

/* --- Register HW_USDHC_INT_STATUS_EN, field TCSEN[1] (RW)
 *
 * Transfer Complete Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_TCSEN      (1)      //!< Bit position for USDHC_INT_STATUS_EN_TCSEN.
#define BM_USDHC_INT_STATUS_EN_TCSEN      (0x00000002)  //!< Bit mask for USDHC_INT_STATUS_EN_TCSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_TCSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_TCSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_TCSEN) >> BP_USDHC_INT_STATUS_EN_TCSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_TCSEN.
#define BF_USDHC_INT_STATUS_EN_TCSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_TCSEN) & BM_USDHC_INT_STATUS_EN_TCSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TCSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_TCSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_TCSEN) | BF_USDHC_INT_STATUS_EN_TCSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field BGESEN[2] (RW)
 *
 * Block Gap Event Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_BGESEN      (2)      //!< Bit position for USDHC_INT_STATUS_EN_BGESEN.
#define BM_USDHC_INT_STATUS_EN_BGESEN      (0x00000004)  //!< Bit mask for USDHC_INT_STATUS_EN_BGESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_BGESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_BGESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_BGESEN) >> BP_USDHC_INT_STATUS_EN_BGESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_BGESEN.
#define BF_USDHC_INT_STATUS_EN_BGESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_BGESEN) & BM_USDHC_INT_STATUS_EN_BGESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BGESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_BGESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_BGESEN) | BF_USDHC_INT_STATUS_EN_BGESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field DINTSEN[3] (RW)
 *
 * DMA Interrupt Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_DINTSEN      (3)      //!< Bit position for USDHC_INT_STATUS_EN_DINTSEN.
#define BM_USDHC_INT_STATUS_EN_DINTSEN      (0x00000008)  //!< Bit mask for USDHC_INT_STATUS_EN_DINTSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_DINTSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_DINTSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_DINTSEN) >> BP_USDHC_INT_STATUS_EN_DINTSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_DINTSEN.
#define BF_USDHC_INT_STATUS_EN_DINTSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_DINTSEN) & BM_USDHC_INT_STATUS_EN_DINTSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DINTSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_DINTSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_DINTSEN) | BF_USDHC_INT_STATUS_EN_DINTSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field BWRSEN[4] (RW)
 *
 * Buffer Write Ready Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_BWRSEN      (4)      //!< Bit position for USDHC_INT_STATUS_EN_BWRSEN.
#define BM_USDHC_INT_STATUS_EN_BWRSEN      (0x00000010)  //!< Bit mask for USDHC_INT_STATUS_EN_BWRSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_BWRSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_BWRSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_BWRSEN) >> BP_USDHC_INT_STATUS_EN_BWRSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_BWRSEN.
#define BF_USDHC_INT_STATUS_EN_BWRSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_BWRSEN) & BM_USDHC_INT_STATUS_EN_BWRSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BWRSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_BWRSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_BWRSEN) | BF_USDHC_INT_STATUS_EN_BWRSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field BRRSEN[5] (RW)
 *
 * Buffer Read Ready Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_BRRSEN      (5)      //!< Bit position for USDHC_INT_STATUS_EN_BRRSEN.
#define BM_USDHC_INT_STATUS_EN_BRRSEN      (0x00000020)  //!< Bit mask for USDHC_INT_STATUS_EN_BRRSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_BRRSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_BRRSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_BRRSEN) >> BP_USDHC_INT_STATUS_EN_BRRSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_BRRSEN.
#define BF_USDHC_INT_STATUS_EN_BRRSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_BRRSEN) & BM_USDHC_INT_STATUS_EN_BRRSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BRRSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_BRRSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_BRRSEN) | BF_USDHC_INT_STATUS_EN_BRRSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CINSSEN[6] (RW)
 *
 * Card Insertion Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CINSSEN      (6)      //!< Bit position for USDHC_INT_STATUS_EN_CINSSEN.
#define BM_USDHC_INT_STATUS_EN_CINSSEN      (0x00000040)  //!< Bit mask for USDHC_INT_STATUS_EN_CINSSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CINSSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CINSSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CINSSEN) >> BP_USDHC_INT_STATUS_EN_CINSSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CINSSEN.
#define BF_USDHC_INT_STATUS_EN_CINSSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CINSSEN) & BM_USDHC_INT_STATUS_EN_CINSSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINSSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CINSSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CINSSEN) | BF_USDHC_INT_STATUS_EN_CINSSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CRMSEN[7] (RW)
 *
 * Card Removal Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CRMSEN      (7)      //!< Bit position for USDHC_INT_STATUS_EN_CRMSEN.
#define BM_USDHC_INT_STATUS_EN_CRMSEN      (0x00000080)  //!< Bit mask for USDHC_INT_STATUS_EN_CRMSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CRMSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CRMSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CRMSEN) >> BP_USDHC_INT_STATUS_EN_CRMSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CRMSEN.
#define BF_USDHC_INT_STATUS_EN_CRMSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CRMSEN) & BM_USDHC_INT_STATUS_EN_CRMSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRMSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CRMSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CRMSEN) | BF_USDHC_INT_STATUS_EN_CRMSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CINTSEN[8] (RW)
 *
 * Card Interrupt Status Enable: If this bit is set to 0, the uSDHC will clear the interrupt request
 * to the System. The Card Interrupt detection is stopped when this bit is cleared and restarted
 * when this bit is set to 1. The Host Driver should clear the Card Interrupt Status Enable before
 * servicing the Card Interrupt and should set this bit again after all interrupt requests from the
 * card are cleared to prevent inadvertent interrupts.
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CINTSEN      (8)      //!< Bit position for USDHC_INT_STATUS_EN_CINTSEN.
#define BM_USDHC_INT_STATUS_EN_CINTSEN      (0x00000100)  //!< Bit mask for USDHC_INT_STATUS_EN_CINTSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CINTSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CINTSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CINTSEN) >> BP_USDHC_INT_STATUS_EN_CINTSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CINTSEN.
#define BF_USDHC_INT_STATUS_EN_CINTSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CINTSEN) & BM_USDHC_INT_STATUS_EN_CINTSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINTSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CINTSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CINTSEN) | BF_USDHC_INT_STATUS_EN_CINTSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field RTESEN[12] (RW)
 *
 * Re-Tuning Event Status Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_RTESEN      (12)      //!< Bit position for USDHC_INT_STATUS_EN_RTESEN.
#define BM_USDHC_INT_STATUS_EN_RTESEN      (0x00001000)  //!< Bit mask for USDHC_INT_STATUS_EN_RTESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_RTESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_RTESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_RTESEN) >> BP_USDHC_INT_STATUS_EN_RTESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_RTESEN.
#define BF_USDHC_INT_STATUS_EN_RTESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_RTESEN) & BM_USDHC_INT_STATUS_EN_RTESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RTESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_RTESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_RTESEN) | BF_USDHC_INT_STATUS_EN_RTESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field TPSEN[14] (RW)
 *
 * Tuning Pass Status Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_TPSEN      (14)      //!< Bit position for USDHC_INT_STATUS_EN_TPSEN.
#define BM_USDHC_INT_STATUS_EN_TPSEN      (0x00004000)  //!< Bit mask for USDHC_INT_STATUS_EN_TPSEN.

//! @brief Get value of USDHC_INT_STATUS_EN_TPSEN from a register value.
#define BG_USDHC_INT_STATUS_EN_TPSEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_TPSEN) >> BP_USDHC_INT_STATUS_EN_TPSEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_TPSEN.
#define BF_USDHC_INT_STATUS_EN_TPSEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_TPSEN) & BM_USDHC_INT_STATUS_EN_TPSEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TPSEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_TPSEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_TPSEN) | BF_USDHC_INT_STATUS_EN_TPSEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CTOESEN[16] (RW)
 *
 * Command Timeout Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CTOESEN      (16)      //!< Bit position for USDHC_INT_STATUS_EN_CTOESEN.
#define BM_USDHC_INT_STATUS_EN_CTOESEN      (0x00010000)  //!< Bit mask for USDHC_INT_STATUS_EN_CTOESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CTOESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CTOESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CTOESEN) >> BP_USDHC_INT_STATUS_EN_CTOESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CTOESEN.
#define BF_USDHC_INT_STATUS_EN_CTOESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CTOESEN) & BM_USDHC_INT_STATUS_EN_CTOESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CTOESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CTOESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CTOESEN) | BF_USDHC_INT_STATUS_EN_CTOESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CCESEN[17] (RW)
 *
 * Command CRC Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CCESEN      (17)      //!< Bit position for USDHC_INT_STATUS_EN_CCESEN.
#define BM_USDHC_INT_STATUS_EN_CCESEN      (0x00020000)  //!< Bit mask for USDHC_INT_STATUS_EN_CCESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CCESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CCESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CCESEN) >> BP_USDHC_INT_STATUS_EN_CCESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CCESEN.
#define BF_USDHC_INT_STATUS_EN_CCESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CCESEN) & BM_USDHC_INT_STATUS_EN_CCESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CCESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CCESEN) | BF_USDHC_INT_STATUS_EN_CCESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CEBESEN[18] (RW)
 *
 * Command End Bit Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CEBESEN      (18)      //!< Bit position for USDHC_INT_STATUS_EN_CEBESEN.
#define BM_USDHC_INT_STATUS_EN_CEBESEN      (0x00040000)  //!< Bit mask for USDHC_INT_STATUS_EN_CEBESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CEBESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CEBESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CEBESEN) >> BP_USDHC_INT_STATUS_EN_CEBESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CEBESEN.
#define BF_USDHC_INT_STATUS_EN_CEBESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CEBESEN) & BM_USDHC_INT_STATUS_EN_CEBESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CEBESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CEBESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CEBESEN) | BF_USDHC_INT_STATUS_EN_CEBESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field CIESEN[19] (RW)
 *
 * Command Index Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_CIESEN      (19)      //!< Bit position for USDHC_INT_STATUS_EN_CIESEN.
#define BM_USDHC_INT_STATUS_EN_CIESEN      (0x00080000)  //!< Bit mask for USDHC_INT_STATUS_EN_CIESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_CIESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_CIESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_CIESEN) >> BP_USDHC_INT_STATUS_EN_CIESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_CIESEN.
#define BF_USDHC_INT_STATUS_EN_CIESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_CIESEN) & BM_USDHC_INT_STATUS_EN_CIESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CIESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_CIESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_CIESEN) | BF_USDHC_INT_STATUS_EN_CIESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field DTOESEN[20] (RW)
 *
 * Data Timeout Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_DTOESEN      (20)      //!< Bit position for USDHC_INT_STATUS_EN_DTOESEN.
#define BM_USDHC_INT_STATUS_EN_DTOESEN      (0x00100000)  //!< Bit mask for USDHC_INT_STATUS_EN_DTOESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_DTOESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_DTOESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_DTOESEN) >> BP_USDHC_INT_STATUS_EN_DTOESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_DTOESEN.
#define BF_USDHC_INT_STATUS_EN_DTOESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_DTOESEN) & BM_USDHC_INT_STATUS_EN_DTOESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTOESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_DTOESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_DTOESEN) | BF_USDHC_INT_STATUS_EN_DTOESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field DCESEN[21] (RW)
 *
 * Data CRC Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_DCESEN      (21)      //!< Bit position for USDHC_INT_STATUS_EN_DCESEN.
#define BM_USDHC_INT_STATUS_EN_DCESEN      (0x00200000)  //!< Bit mask for USDHC_INT_STATUS_EN_DCESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_DCESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_DCESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_DCESEN) >> BP_USDHC_INT_STATUS_EN_DCESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_DCESEN.
#define BF_USDHC_INT_STATUS_EN_DCESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_DCESEN) & BM_USDHC_INT_STATUS_EN_DCESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DCESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_DCESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_DCESEN) | BF_USDHC_INT_STATUS_EN_DCESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field DEBESEN[22] (RW)
 *
 * Data End Bit Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_DEBESEN      (22)      //!< Bit position for USDHC_INT_STATUS_EN_DEBESEN.
#define BM_USDHC_INT_STATUS_EN_DEBESEN      (0x00400000)  //!< Bit mask for USDHC_INT_STATUS_EN_DEBESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_DEBESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_DEBESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_DEBESEN) >> BP_USDHC_INT_STATUS_EN_DEBESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_DEBESEN.
#define BF_USDHC_INT_STATUS_EN_DEBESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_DEBESEN) & BM_USDHC_INT_STATUS_EN_DEBESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DEBESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_DEBESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_DEBESEN) | BF_USDHC_INT_STATUS_EN_DEBESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field AC12ESEN[24] (RW)
 *
 * Auto CMD12 Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_AC12ESEN      (24)      //!< Bit position for USDHC_INT_STATUS_EN_AC12ESEN.
#define BM_USDHC_INT_STATUS_EN_AC12ESEN      (0x01000000)  //!< Bit mask for USDHC_INT_STATUS_EN_AC12ESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_AC12ESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_AC12ESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_AC12ESEN) >> BP_USDHC_INT_STATUS_EN_AC12ESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_AC12ESEN.
#define BF_USDHC_INT_STATUS_EN_AC12ESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_AC12ESEN) & BM_USDHC_INT_STATUS_EN_AC12ESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12ESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_AC12ESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_AC12ESEN) | BF_USDHC_INT_STATUS_EN_AC12ESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field TNESEN[26] (RW)
 *
 * Tuning Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_TNESEN      (26)      //!< Bit position for USDHC_INT_STATUS_EN_TNESEN.
#define BM_USDHC_INT_STATUS_EN_TNESEN      (0x04000000)  //!< Bit mask for USDHC_INT_STATUS_EN_TNESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_TNESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_TNESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_TNESEN) >> BP_USDHC_INT_STATUS_EN_TNESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_TNESEN.
#define BF_USDHC_INT_STATUS_EN_TNESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_TNESEN) & BM_USDHC_INT_STATUS_EN_TNESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TNESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_TNESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_TNESEN) | BF_USDHC_INT_STATUS_EN_TNESEN(v)))
#endif


/* --- Register HW_USDHC_INT_STATUS_EN, field DMAESEN[28] (RW)
 *
 * DMA Error Status Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_STATUS_EN_DMAESEN      (28)      //!< Bit position for USDHC_INT_STATUS_EN_DMAESEN.
#define BM_USDHC_INT_STATUS_EN_DMAESEN      (0x10000000)  //!< Bit mask for USDHC_INT_STATUS_EN_DMAESEN.

//! @brief Get value of USDHC_INT_STATUS_EN_DMAESEN from a register value.
#define BG_USDHC_INT_STATUS_EN_DMAESEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_STATUS_EN_DMAESEN) >> BP_USDHC_INT_STATUS_EN_DMAESEN)

//! @brief Format value for bitfield USDHC_INT_STATUS_EN_DMAESEN.
#define BF_USDHC_INT_STATUS_EN_DMAESEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_STATUS_EN_DMAESEN) & BM_USDHC_INT_STATUS_EN_DMAESEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DMAESEN field to a new value.
#define BW_USDHC_INT_STATUS_EN_DMAESEN(x, v)   (HW_USDHC_INT_STATUS_EN_WR(x, (HW_USDHC_INT_STATUS_EN_RD(x) & ~BM_USDHC_INT_STATUS_EN_DMAESEN) | BF_USDHC_INT_STATUS_EN_DMAESEN(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_INT_SIGNAL_EN - Interrupt Signal Enable
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_INT_SIGNAL_EN - Interrupt Signal Enable (RW)
 *
 * Reset value: 0x00000000
 *
 * This register is used to select which interrupt status is indicated to the Host System as the
 * interrupt. These status bits all share the same interrupt line. Setting any of these bits to 1
 * enables interrupt generation. The corresponding Status register bit will generate an interrupt
 * when the corresponding interrupt signal enable bit is set.
 */
typedef union _hw_usdhc_int_signal_en
{
    reg32_t U;
    struct _hw_usdhc_int_signal_en_bitfields
    {
        unsigned CCIEN : 1; //!< [0] Command Complete Interrupt Enable:
        unsigned TCIEN : 1; //!< [1] Transfer Complete Interrupt Enable:
        unsigned BGEIEN : 1; //!< [2] Block Gap Event Interrupt Enable:
        unsigned DINTIEN : 1; //!< [3] DMA Interrupt Enable:
        unsigned BWRIEN : 1; //!< [4] Buffer Write Ready Interrupt Enable:
        unsigned BRRIEN : 1; //!< [5] Buffer Read Ready Interrupt Enable:
        unsigned CINSIEN : 1; //!< [6] Card Insertion Interrupt Enable:
        unsigned CRMIEN : 1; //!< [7] Card Removal Interrupt Enable:
        unsigned CINTIEN : 1; //!< [8] Card Interrupt Interrupt Enable:
        unsigned RESERVED0 : 3; //!< [11:9] Reserved
        unsigned RTEIEN : 1; //!< [12] Re-Tuning Event Interrupt Enable
        unsigned RESERVED1 : 1; //!< [13] Reserved
        unsigned TPIEN : 1; //!< [14] Tuning Pass Interrupt Enable
        unsigned RESERVED2 : 1; //!< [15] Reserved
        unsigned CTOEIEN : 1; //!< [16] Command Timeout Error Interrupt Enable
        unsigned CCEIEN : 1; //!< [17] Command CRC Error Interrupt Enable:
        unsigned CEBEIEN : 1; //!< [18] Command End Bit Error Interrupt Enable:
        unsigned CIEIEN : 1; //!< [19] Command Index Error Interrupt Enable:
        unsigned DTOEIEN : 1; //!< [20] Data Timeout Error Interrupt Enable:
        unsigned DCEIEN : 1; //!< [21] Data CRC Error Interrupt Enable:
        unsigned DEBEIEN : 1; //!< [22] Data End Bit Error Interrupt Enable:
        unsigned RESERVED3 : 1; //!< [23] Reserved
        unsigned AC12EIEN : 1; //!< [24] Auto CMD12 Error Interrupt Enable:
        unsigned RESERVED4 : 1; //!< [25] Reserved
        unsigned TNEIEN : 1; //!< [26] Tuning Error Interrupt Enable
        unsigned RESERVED5 : 1; //!< [27] Reserved
        unsigned DMAEIEN : 1; //!< [28] DMA Error Interrupt Enable:
        unsigned RESERVED6 : 3; //!< [31:29] Reserved
    } B;
} hw_usdhc_int_signal_en_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_INT_SIGNAL_EN register
 */
#define HW_USDHC_INT_SIGNAL_EN_ADDR(x)      (REGS_USDHC_BASE(x) + 0x38)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_INT_SIGNAL_EN(x)           (*(volatile hw_usdhc_int_signal_en_t *) HW_USDHC_INT_SIGNAL_EN_ADDR(x))
#define HW_USDHC_INT_SIGNAL_EN_RD(x)        (HW_USDHC_INT_SIGNAL_EN(x).U)
#define HW_USDHC_INT_SIGNAL_EN_WR(x, v)     (HW_USDHC_INT_SIGNAL_EN(x).U = (v))
#define HW_USDHC_INT_SIGNAL_EN_SET(x, v)    (HW_USDHC_INT_SIGNAL_EN_WR(x, HW_USDHC_INT_SIGNAL_EN_RD(x) |  (v)))
#define HW_USDHC_INT_SIGNAL_EN_CLR(x, v)    (HW_USDHC_INT_SIGNAL_EN_WR(x, HW_USDHC_INT_SIGNAL_EN_RD(x) & ~(v)))
#define HW_USDHC_INT_SIGNAL_EN_TOG(x, v)    (HW_USDHC_INT_SIGNAL_EN_WR(x, HW_USDHC_INT_SIGNAL_EN_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_INT_SIGNAL_EN bitfields
 */

/* --- Register HW_USDHC_INT_SIGNAL_EN, field CCIEN[0] (RW)
 *
 * Command Complete Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CCIEN      (0)      //!< Bit position for USDHC_INT_SIGNAL_EN_CCIEN.
#define BM_USDHC_INT_SIGNAL_EN_CCIEN      (0x00000001)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CCIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CCIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CCIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CCIEN) >> BP_USDHC_INT_SIGNAL_EN_CCIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CCIEN.
#define BF_USDHC_INT_SIGNAL_EN_CCIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CCIEN) & BM_USDHC_INT_SIGNAL_EN_CCIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CCIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CCIEN) | BF_USDHC_INT_SIGNAL_EN_CCIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field TCIEN[1] (RW)
 *
 * Transfer Complete Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_TCIEN      (1)      //!< Bit position for USDHC_INT_SIGNAL_EN_TCIEN.
#define BM_USDHC_INT_SIGNAL_EN_TCIEN      (0x00000002)  //!< Bit mask for USDHC_INT_SIGNAL_EN_TCIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_TCIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_TCIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_TCIEN) >> BP_USDHC_INT_SIGNAL_EN_TCIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_TCIEN.
#define BF_USDHC_INT_SIGNAL_EN_TCIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_TCIEN) & BM_USDHC_INT_SIGNAL_EN_TCIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TCIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_TCIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_TCIEN) | BF_USDHC_INT_SIGNAL_EN_TCIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field BGEIEN[2] (RW)
 *
 * Block Gap Event Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_BGEIEN      (2)      //!< Bit position for USDHC_INT_SIGNAL_EN_BGEIEN.
#define BM_USDHC_INT_SIGNAL_EN_BGEIEN      (0x00000004)  //!< Bit mask for USDHC_INT_SIGNAL_EN_BGEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_BGEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_BGEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_BGEIEN) >> BP_USDHC_INT_SIGNAL_EN_BGEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_BGEIEN.
#define BF_USDHC_INT_SIGNAL_EN_BGEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_BGEIEN) & BM_USDHC_INT_SIGNAL_EN_BGEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BGEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_BGEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_BGEIEN) | BF_USDHC_INT_SIGNAL_EN_BGEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field DINTIEN[3] (RW)
 *
 * DMA Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_DINTIEN      (3)      //!< Bit position for USDHC_INT_SIGNAL_EN_DINTIEN.
#define BM_USDHC_INT_SIGNAL_EN_DINTIEN      (0x00000008)  //!< Bit mask for USDHC_INT_SIGNAL_EN_DINTIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_DINTIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_DINTIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_DINTIEN) >> BP_USDHC_INT_SIGNAL_EN_DINTIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_DINTIEN.
#define BF_USDHC_INT_SIGNAL_EN_DINTIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_DINTIEN) & BM_USDHC_INT_SIGNAL_EN_DINTIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DINTIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_DINTIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_DINTIEN) | BF_USDHC_INT_SIGNAL_EN_DINTIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field BWRIEN[4] (RW)
 *
 * Buffer Write Ready Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_BWRIEN      (4)      //!< Bit position for USDHC_INT_SIGNAL_EN_BWRIEN.
#define BM_USDHC_INT_SIGNAL_EN_BWRIEN      (0x00000010)  //!< Bit mask for USDHC_INT_SIGNAL_EN_BWRIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_BWRIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_BWRIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_BWRIEN) >> BP_USDHC_INT_SIGNAL_EN_BWRIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_BWRIEN.
#define BF_USDHC_INT_SIGNAL_EN_BWRIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_BWRIEN) & BM_USDHC_INT_SIGNAL_EN_BWRIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BWRIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_BWRIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_BWRIEN) | BF_USDHC_INT_SIGNAL_EN_BWRIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field BRRIEN[5] (RW)
 *
 * Buffer Read Ready Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_BRRIEN      (5)      //!< Bit position for USDHC_INT_SIGNAL_EN_BRRIEN.
#define BM_USDHC_INT_SIGNAL_EN_BRRIEN      (0x00000020)  //!< Bit mask for USDHC_INT_SIGNAL_EN_BRRIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_BRRIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_BRRIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_BRRIEN) >> BP_USDHC_INT_SIGNAL_EN_BRRIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_BRRIEN.
#define BF_USDHC_INT_SIGNAL_EN_BRRIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_BRRIEN) & BM_USDHC_INT_SIGNAL_EN_BRRIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BRRIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_BRRIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_BRRIEN) | BF_USDHC_INT_SIGNAL_EN_BRRIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CINSIEN[6] (RW)
 *
 * Card Insertion Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CINSIEN      (6)      //!< Bit position for USDHC_INT_SIGNAL_EN_CINSIEN.
#define BM_USDHC_INT_SIGNAL_EN_CINSIEN      (0x00000040)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CINSIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CINSIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CINSIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CINSIEN) >> BP_USDHC_INT_SIGNAL_EN_CINSIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CINSIEN.
#define BF_USDHC_INT_SIGNAL_EN_CINSIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CINSIEN) & BM_USDHC_INT_SIGNAL_EN_CINSIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINSIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CINSIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CINSIEN) | BF_USDHC_INT_SIGNAL_EN_CINSIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CRMIEN[7] (RW)
 *
 * Card Removal Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CRMIEN      (7)      //!< Bit position for USDHC_INT_SIGNAL_EN_CRMIEN.
#define BM_USDHC_INT_SIGNAL_EN_CRMIEN      (0x00000080)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CRMIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CRMIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CRMIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CRMIEN) >> BP_USDHC_INT_SIGNAL_EN_CRMIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CRMIEN.
#define BF_USDHC_INT_SIGNAL_EN_CRMIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CRMIEN) & BM_USDHC_INT_SIGNAL_EN_CRMIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRMIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CRMIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CRMIEN) | BF_USDHC_INT_SIGNAL_EN_CRMIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CINTIEN[8] (RW)
 *
 * Card Interrupt Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CINTIEN      (8)      //!< Bit position for USDHC_INT_SIGNAL_EN_CINTIEN.
#define BM_USDHC_INT_SIGNAL_EN_CINTIEN      (0x00000100)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CINTIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CINTIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CINTIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CINTIEN) >> BP_USDHC_INT_SIGNAL_EN_CINTIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CINTIEN.
#define BF_USDHC_INT_SIGNAL_EN_CINTIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CINTIEN) & BM_USDHC_INT_SIGNAL_EN_CINTIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CINTIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CINTIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CINTIEN) | BF_USDHC_INT_SIGNAL_EN_CINTIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field RTEIEN[12] (RW)
 *
 * Re-Tuning Event Interrupt Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_RTEIEN      (12)      //!< Bit position for USDHC_INT_SIGNAL_EN_RTEIEN.
#define BM_USDHC_INT_SIGNAL_EN_RTEIEN      (0x00001000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_RTEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_RTEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_RTEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_RTEIEN) >> BP_USDHC_INT_SIGNAL_EN_RTEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_RTEIEN.
#define BF_USDHC_INT_SIGNAL_EN_RTEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_RTEIEN) & BM_USDHC_INT_SIGNAL_EN_RTEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RTEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_RTEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_RTEIEN) | BF_USDHC_INT_SIGNAL_EN_RTEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field TPIEN[14] (RW)
 *
 * Tuning Pass Interrupt Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_TPIEN      (14)      //!< Bit position for USDHC_INT_SIGNAL_EN_TPIEN.
#define BM_USDHC_INT_SIGNAL_EN_TPIEN      (0x00004000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_TPIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_TPIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_TPIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_TPIEN) >> BP_USDHC_INT_SIGNAL_EN_TPIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_TPIEN.
#define BF_USDHC_INT_SIGNAL_EN_TPIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_TPIEN) & BM_USDHC_INT_SIGNAL_EN_TPIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TPIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_TPIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_TPIEN) | BF_USDHC_INT_SIGNAL_EN_TPIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CTOEIEN[16] (RW)
 *
 * Command Timeout Error Interrupt Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CTOEIEN      (16)      //!< Bit position for USDHC_INT_SIGNAL_EN_CTOEIEN.
#define BM_USDHC_INT_SIGNAL_EN_CTOEIEN      (0x00010000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CTOEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CTOEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CTOEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CTOEIEN) >> BP_USDHC_INT_SIGNAL_EN_CTOEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CTOEIEN.
#define BF_USDHC_INT_SIGNAL_EN_CTOEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CTOEIEN) & BM_USDHC_INT_SIGNAL_EN_CTOEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CTOEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CTOEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CTOEIEN) | BF_USDHC_INT_SIGNAL_EN_CTOEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CCEIEN[17] (RW)
 *
 * Command CRC Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CCEIEN      (17)      //!< Bit position for USDHC_INT_SIGNAL_EN_CCEIEN.
#define BM_USDHC_INT_SIGNAL_EN_CCEIEN      (0x00020000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CCEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CCEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CCEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CCEIEN) >> BP_USDHC_INT_SIGNAL_EN_CCEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CCEIEN.
#define BF_USDHC_INT_SIGNAL_EN_CCEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CCEIEN) & BM_USDHC_INT_SIGNAL_EN_CCEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CCEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CCEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CCEIEN) | BF_USDHC_INT_SIGNAL_EN_CCEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CEBEIEN[18] (RW)
 *
 * Command End Bit Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CEBEIEN      (18)      //!< Bit position for USDHC_INT_SIGNAL_EN_CEBEIEN.
#define BM_USDHC_INT_SIGNAL_EN_CEBEIEN      (0x00040000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CEBEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CEBEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CEBEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CEBEIEN) >> BP_USDHC_INT_SIGNAL_EN_CEBEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CEBEIEN.
#define BF_USDHC_INT_SIGNAL_EN_CEBEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CEBEIEN) & BM_USDHC_INT_SIGNAL_EN_CEBEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CEBEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CEBEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CEBEIEN) | BF_USDHC_INT_SIGNAL_EN_CEBEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field CIEIEN[19] (RW)
 *
 * Command Index Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_CIEIEN      (19)      //!< Bit position for USDHC_INT_SIGNAL_EN_CIEIEN.
#define BM_USDHC_INT_SIGNAL_EN_CIEIEN      (0x00080000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_CIEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_CIEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_CIEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_CIEIEN) >> BP_USDHC_INT_SIGNAL_EN_CIEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_CIEIEN.
#define BF_USDHC_INT_SIGNAL_EN_CIEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_CIEIEN) & BM_USDHC_INT_SIGNAL_EN_CIEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CIEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_CIEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_CIEIEN) | BF_USDHC_INT_SIGNAL_EN_CIEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field DTOEIEN[20] (RW)
 *
 * Data Timeout Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_DTOEIEN      (20)      //!< Bit position for USDHC_INT_SIGNAL_EN_DTOEIEN.
#define BM_USDHC_INT_SIGNAL_EN_DTOEIEN      (0x00100000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_DTOEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_DTOEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_DTOEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_DTOEIEN) >> BP_USDHC_INT_SIGNAL_EN_DTOEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_DTOEIEN.
#define BF_USDHC_INT_SIGNAL_EN_DTOEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_DTOEIEN) & BM_USDHC_INT_SIGNAL_EN_DTOEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTOEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_DTOEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_DTOEIEN) | BF_USDHC_INT_SIGNAL_EN_DTOEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field DCEIEN[21] (RW)
 *
 * Data CRC Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_DCEIEN      (21)      //!< Bit position for USDHC_INT_SIGNAL_EN_DCEIEN.
#define BM_USDHC_INT_SIGNAL_EN_DCEIEN      (0x00200000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_DCEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_DCEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_DCEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_DCEIEN) >> BP_USDHC_INT_SIGNAL_EN_DCEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_DCEIEN.
#define BF_USDHC_INT_SIGNAL_EN_DCEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_DCEIEN) & BM_USDHC_INT_SIGNAL_EN_DCEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DCEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_DCEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_DCEIEN) | BF_USDHC_INT_SIGNAL_EN_DCEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field DEBEIEN[22] (RW)
 *
 * Data End Bit Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_DEBEIEN      (22)      //!< Bit position for USDHC_INT_SIGNAL_EN_DEBEIEN.
#define BM_USDHC_INT_SIGNAL_EN_DEBEIEN      (0x00400000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_DEBEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_DEBEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_DEBEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_DEBEIEN) >> BP_USDHC_INT_SIGNAL_EN_DEBEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_DEBEIEN.
#define BF_USDHC_INT_SIGNAL_EN_DEBEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_DEBEIEN) & BM_USDHC_INT_SIGNAL_EN_DEBEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DEBEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_DEBEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_DEBEIEN) | BF_USDHC_INT_SIGNAL_EN_DEBEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field AC12EIEN[24] (RW)
 *
 * Auto CMD12 Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_AC12EIEN      (24)      //!< Bit position for USDHC_INT_SIGNAL_EN_AC12EIEN.
#define BM_USDHC_INT_SIGNAL_EN_AC12EIEN      (0x01000000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_AC12EIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_AC12EIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_AC12EIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_AC12EIEN) >> BP_USDHC_INT_SIGNAL_EN_AC12EIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_AC12EIEN.
#define BF_USDHC_INT_SIGNAL_EN_AC12EIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_AC12EIEN) & BM_USDHC_INT_SIGNAL_EN_AC12EIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12EIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_AC12EIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_AC12EIEN) | BF_USDHC_INT_SIGNAL_EN_AC12EIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field TNEIEN[26] (RW)
 *
 * Tuning Error Interrupt Enable
 *
 * Values:
 * 0 - Masked
 * 1 - Enabled
 */

#define BP_USDHC_INT_SIGNAL_EN_TNEIEN      (26)      //!< Bit position for USDHC_INT_SIGNAL_EN_TNEIEN.
#define BM_USDHC_INT_SIGNAL_EN_TNEIEN      (0x04000000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_TNEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_TNEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_TNEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_TNEIEN) >> BP_USDHC_INT_SIGNAL_EN_TNEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_TNEIEN.
#define BF_USDHC_INT_SIGNAL_EN_TNEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_TNEIEN) & BM_USDHC_INT_SIGNAL_EN_TNEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TNEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_TNEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_TNEIEN) | BF_USDHC_INT_SIGNAL_EN_TNEIEN(v)))
#endif


/* --- Register HW_USDHC_INT_SIGNAL_EN, field DMAEIEN[28] (RW)
 *
 * DMA Error Interrupt Enable:
 *
 * Values:
 * 0 - Masked
 * 1 - Enable
 */

#define BP_USDHC_INT_SIGNAL_EN_DMAEIEN      (28)      //!< Bit position for USDHC_INT_SIGNAL_EN_DMAEIEN.
#define BM_USDHC_INT_SIGNAL_EN_DMAEIEN      (0x10000000)  //!< Bit mask for USDHC_INT_SIGNAL_EN_DMAEIEN.

//! @brief Get value of USDHC_INT_SIGNAL_EN_DMAEIEN from a register value.
#define BG_USDHC_INT_SIGNAL_EN_DMAEIEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_INT_SIGNAL_EN_DMAEIEN) >> BP_USDHC_INT_SIGNAL_EN_DMAEIEN)

//! @brief Format value for bitfield USDHC_INT_SIGNAL_EN_DMAEIEN.
#define BF_USDHC_INT_SIGNAL_EN_DMAEIEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_INT_SIGNAL_EN_DMAEIEN) & BM_USDHC_INT_SIGNAL_EN_DMAEIEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DMAEIEN field to a new value.
#define BW_USDHC_INT_SIGNAL_EN_DMAEIEN(x, v)   (HW_USDHC_INT_SIGNAL_EN_WR(x, (HW_USDHC_INT_SIGNAL_EN_RD(x) & ~BM_USDHC_INT_SIGNAL_EN_DMAEIEN) | BF_USDHC_INT_SIGNAL_EN_DMAEIEN(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_AUTOCMD12_ERR_STATUS - Auto CMD12 Error Status
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_AUTOCMD12_ERR_STATUS - Auto CMD12 Error Status (RO)
 *
 * Reset value: 0x00000000
 *
 * When the Auto CMD12 Error Status bit in the Status register is set, the Host Driver shall check
 * this register to identify what kind of error the Auto CMD12 indicated. This register is valid
 * only when the Auto CMD12 Error status bit is set.  The table bwlow shows the relationship between
 * the Auto CMGD12 CRC Error and the Auto CMD12 Command Timeout Error.   Relationship Between
 * Command CRC Error and Command Timeout Error for Auto CMD12         Auto CMD12 CRC Error    Auto
 * CMD12 Timeout Error    Type of Error        0    0    No Error      0    1    Response Timeout
 * Error      1    0    Response CRC Error      1    1    CMD line conflict       Changes in Auto
 * CMD12 Error Status register can be classified in three scenarios:   When the uSDHC is going to
 * issue an Auto CMD12.  Set bit 0 to 1 if the Auto CMD12 can't be issued due to an error in the
 * previous command  Set bit 0 to 0 if the Auto CMD12 is issued    At the end bit of an Auto CMD12
 * response.  Check errors correspond to bits 1-4.  Set bits 1-4 corresponding to detected errors.
 * Clear bits 1-4 corresponding to detected errors    Before reading the Auto CMD12 Error Status bit
 * 7.  Set bit 7 to 1 if there is a command that can't be issued  Clear bit 7 if there is no command
 * to issue     The timing for generating the Auto CMD12 Error and writing to the Command register
 * are asynchronous. After that, bit 7 shall be sampled when the driver is not writing to the
 * Command register. So it is suggested to read this register only when the AC12E bit in Interrupt
 * Status register is set. An Auto CMD12 Error Interrupt is generated when one of the error bits
 * (0-4) is set to 1. The Command Not Issued By Auto CMD12 Error does not generate an interrupt.
 */
typedef union _hw_usdhc_autocmd12_err_status
{
    reg32_t U;
    struct _hw_usdhc_autocmd12_err_status_bitfields
    {
        unsigned AC12NE : 1; //!< [0] Auto CMD12 Not Executed: If memory multiple block data transfer is not started, due to a command error, this bit is not set because it is not necessary to issue an Auto CMD12.
        unsigned AC12TOE : 1; //!< [1] Auto CMD12 Timeout Error: Occurs if no response is returned within 64 SDCLK cycles from the end bit of the command.
        unsigned AC12EBE : 1; //!< [2] Auto CMD12 End Bit Error: Occurs when detecting that the end bit of command response is 0 which should be 1.
        unsigned AC12CE : 1; //!< [3] Auto CMD12 CRC Error: Occurs when detecting a CRC error in the command response.
        unsigned AC12IE : 1; //!< [4] Auto CMD12 Index Error: Occurs if the Command Index error occurs in response to a command.
        unsigned RESERVED0 : 2; //!< [6:5] Reserved
        unsigned CNIBAC12E : 1; //!< [7] Command Not Issued By Auto CMD12 Error: Setting this bit to 1 means CMD_wo_DAT is not executed due to an Auto CMD12 Error (D04-D01) in this register.
        unsigned RESERVED1 : 24; //!< [31:8] Reserved
    } B;
} hw_usdhc_autocmd12_err_status_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_AUTOCMD12_ERR_STATUS register
 */
#define HW_USDHC_AUTOCMD12_ERR_STATUS_ADDR(x)      (REGS_USDHC_BASE(x) + 0x3c)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_AUTOCMD12_ERR_STATUS(x)           (*(volatile hw_usdhc_autocmd12_err_status_t *) HW_USDHC_AUTOCMD12_ERR_STATUS_ADDR(x))
#define HW_USDHC_AUTOCMD12_ERR_STATUS_RD(x)        (HW_USDHC_AUTOCMD12_ERR_STATUS(x).U)
#endif

/*
 * constants & macros for individual USDHC_AUTOCMD12_ERR_STATUS bitfields
 */

/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field AC12NE[0] (RO)
 *
 * Auto CMD12 Not Executed: If memory multiple block data transfer is not started, due to a command
 * error, this bit is not set because it is not necessary to issue an Auto CMD12. Setting this bit
 * to 1 means the uSDHC cannot issue the Auto CMD12 to stop a memory multiple block data transfer
 * due to some error. If this bit is set to 1, other error status bits (1-4) have no meaning.
 *
 * Values:
 * 0 - Executed
 * 1 - Not executed
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_AC12NE      (0)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_AC12NE.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_AC12NE      (0x00000001)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_AC12NE.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_AC12NE from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_AC12NE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_AC12NE) >> BP_USDHC_AUTOCMD12_ERR_STATUS_AC12NE)


/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field AC12TOE[1] (RO)
 *
 * Auto CMD12 Timeout Error: Occurs if no response is returned within 64 SDCLK cycles from the end
 * bit of the command. If this bit is set to1, the other error status bits (2-4) have no meaning.
 *
 * Values:
 * 0 - No error
 * 1 - Time out
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_AC12TOE      (1)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_AC12TOE.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_AC12TOE      (0x00000002)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_AC12TOE.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_AC12TOE from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_AC12TOE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_AC12TOE) >> BP_USDHC_AUTOCMD12_ERR_STATUS_AC12TOE)


/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field AC12EBE[2] (RO)
 *
 * Auto CMD12 End Bit Error: Occurs when detecting that the end bit of command response is 0 which
 * should be 1.
 *
 * Values:
 * 0 - No error
 * 1 - End Bit Error Generated
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_AC12EBE      (2)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_AC12EBE.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_AC12EBE      (0x00000004)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_AC12EBE.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_AC12EBE from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_AC12EBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_AC12EBE) >> BP_USDHC_AUTOCMD12_ERR_STATUS_AC12EBE)


/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field AC12CE[3] (RO)
 *
 * Auto CMD12 CRC Error: Occurs when detecting a CRC error in the command response.
 *
 * Values:
 * 0 - No CRC error
 * 1 - CRC Error Met in Auto CMD12 Response
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_AC12CE      (3)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_AC12CE.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_AC12CE      (0x00000008)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_AC12CE.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_AC12CE from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_AC12CE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_AC12CE) >> BP_USDHC_AUTOCMD12_ERR_STATUS_AC12CE)


/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field AC12IE[4] (RO)
 *
 * Auto CMD12 Index Error: Occurs if the Command Index error occurs in response to a command.
 *
 * Values:
 * 0 - No error
 * 1 - Error, the CMD index in response is not CMD12
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_AC12IE      (4)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_AC12IE.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_AC12IE      (0x00000010)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_AC12IE.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_AC12IE from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_AC12IE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_AC12IE) >> BP_USDHC_AUTOCMD12_ERR_STATUS_AC12IE)


/* --- Register HW_USDHC_AUTOCMD12_ERR_STATUS, field CNIBAC12E[7] (RO)
 *
 * Command Not Issued By Auto CMD12 Error: Setting this bit to 1 means CMD_wo_DAT is not executed
 * due to an Auto CMD12 Error (D04-D01) in this register.
 *
 * Values:
 * 0 - No error
 * 1 - Not Issued
 */

#define BP_USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E      (7)      //!< Bit position for USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E.
#define BM_USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E      (0x00000080)  //!< Bit mask for USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E.

//! @brief Get value of USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E from a register value.
#define BG_USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E) >> BP_USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E)


//-------------------------------------------------------------------------------------------
// HW_USDHC_HOST_CTRL_CAP - Host Controller Capabilities
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_HOST_CTRL_CAP - Host Controller Capabilities (RO)
 *
 * Reset value: 0x07f30000
 *
 * This register provides the Host Driver with information specific to the uSDHC implementation. The
 * value in this register is the power-on-reset value, and does not change with a software reset.
 * Any write to this register is ignored.
 */
typedef union _hw_usdhc_host_ctrl_cap
{
    reg32_t U;
    struct _hw_usdhc_host_ctrl_cap_bitfields
    {
        unsigned RESERVED0 : 16; //!< [15:0] Reserved
        unsigned MBL : 3; //!< [18:16] Max Block Length: This value indicates the maximum block size that the Host Driver can read and write to the buffer in the uSDHC.
        unsigned RESERVED1 : 1; //!< [19] Reserved
        unsigned ADMAS : 1; //!< [20] ADMA Support: This bit indicates whether the uSDHC supports the ADMA feature.
        unsigned HSS : 1; //!< [21] High Speed Support: This bit indicates whether the uSDHC supports High Speed mode and the Host System can supply a SD Clock frequency from 25 MHz to 50 MHz.
        unsigned DMAS : 1; //!< [22] DMA Support: This bit indicates whether the uSDHC is capable of using the internal DMA to transfer data between system memory and the data buffer directly.
        unsigned SRS : 1; //!< [23] Suspend / Resume Support: This bit indicates whether the uSDHC supports Suspend / Resume functionality.
        unsigned VS33 : 1; //!< [24] Voltage Support 3.3V: This bit shall depend on the Host System ability.
        unsigned VS30 : 1; //!< [25] Voltage Support 3.0V: This bit shall depend on the Host System ability.
        unsigned VS18 : 1; //!< [26] Voltage Support 1.8V: This bit shall depend on the Host System ability.
        unsigned RESERVED2 : 5; //!< [31:27] Reserved
    } B;
} hw_usdhc_host_ctrl_cap_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_HOST_CTRL_CAP register
 */
#define HW_USDHC_HOST_CTRL_CAP_ADDR(x)      (REGS_USDHC_BASE(x) + 0x40)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_HOST_CTRL_CAP(x)           (*(volatile hw_usdhc_host_ctrl_cap_t *) HW_USDHC_HOST_CTRL_CAP_ADDR(x))
#define HW_USDHC_HOST_CTRL_CAP_RD(x)        (HW_USDHC_HOST_CTRL_CAP(x).U)
#endif

/*
 * constants & macros for individual USDHC_HOST_CTRL_CAP bitfields
 */

/* --- Register HW_USDHC_HOST_CTRL_CAP, field MBL[18:16] (RO)
 *
 * Max Block Length: This value indicates the maximum block size that the Host Driver can read and
 * write to the buffer in the uSDHC. The buffer shall transfer block size without wait cycles.
 *
 * Values:
 * 000 - 512 bytes
 * 001 - 1024 bytes
 * 010 - 2048 bytes
 * 011 - 4096 bytes
 */

#define BP_USDHC_HOST_CTRL_CAP_MBL      (16)      //!< Bit position for USDHC_HOST_CTRL_CAP_MBL.
#define BM_USDHC_HOST_CTRL_CAP_MBL      (0x00070000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_MBL.

//! @brief Get value of USDHC_HOST_CTRL_CAP_MBL from a register value.
#define BG_USDHC_HOST_CTRL_CAP_MBL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_MBL) >> BP_USDHC_HOST_CTRL_CAP_MBL)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field ADMAS[20] (RO)
 *
 * ADMA Support: This bit indicates whether the uSDHC supports the ADMA feature.
 *
 * Values:
 * 0 - Advanced DMA Not supported
 * 1 - Advanced DMA Supported
 */

#define BP_USDHC_HOST_CTRL_CAP_ADMAS      (20)      //!< Bit position for USDHC_HOST_CTRL_CAP_ADMAS.
#define BM_USDHC_HOST_CTRL_CAP_ADMAS      (0x00100000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_ADMAS.

//! @brief Get value of USDHC_HOST_CTRL_CAP_ADMAS from a register value.
#define BG_USDHC_HOST_CTRL_CAP_ADMAS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_ADMAS) >> BP_USDHC_HOST_CTRL_CAP_ADMAS)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field HSS[21] (RO)
 *
 * High Speed Support: This bit indicates whether the uSDHC supports High Speed mode and the Host
 * System can supply a SD Clock frequency from 25 MHz to 50 MHz.
 *
 * Values:
 * 0 - High Speed Not Supported
 * 1 - High Speed Supported
 */

#define BP_USDHC_HOST_CTRL_CAP_HSS      (21)      //!< Bit position for USDHC_HOST_CTRL_CAP_HSS.
#define BM_USDHC_HOST_CTRL_CAP_HSS      (0x00200000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_HSS.

//! @brief Get value of USDHC_HOST_CTRL_CAP_HSS from a register value.
#define BG_USDHC_HOST_CTRL_CAP_HSS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_HSS) >> BP_USDHC_HOST_CTRL_CAP_HSS)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field DMAS[22] (RO)
 *
 * DMA Support: This bit indicates whether the uSDHC is capable of using the internal DMA to
 * transfer data between system memory and the data buffer directly.
 *
 * Values:
 * 0 - DMA not supported
 * 1 - DMA Supported
 */

#define BP_USDHC_HOST_CTRL_CAP_DMAS      (22)      //!< Bit position for USDHC_HOST_CTRL_CAP_DMAS.
#define BM_USDHC_HOST_CTRL_CAP_DMAS      (0x00400000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_DMAS.

//! @brief Get value of USDHC_HOST_CTRL_CAP_DMAS from a register value.
#define BG_USDHC_HOST_CTRL_CAP_DMAS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_DMAS) >> BP_USDHC_HOST_CTRL_CAP_DMAS)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field SRS[23] (RO)
 *
 * Suspend / Resume Support: This bit indicates whether the uSDHC supports Suspend / Resume
 * functionality. If this bit is 0, the Suspend and Resume mechanism, as well as the Read Wait, are
 * not supported, and the Host Driver shall not issue either Suspend or Resume commands.
 *
 * Values:
 * 0 - Not supported
 * 1 - Supported
 */

#define BP_USDHC_HOST_CTRL_CAP_SRS      (23)      //!< Bit position for USDHC_HOST_CTRL_CAP_SRS.
#define BM_USDHC_HOST_CTRL_CAP_SRS      (0x00800000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_SRS.

//! @brief Get value of USDHC_HOST_CTRL_CAP_SRS from a register value.
#define BG_USDHC_HOST_CTRL_CAP_SRS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_SRS) >> BP_USDHC_HOST_CTRL_CAP_SRS)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field VS33[24] (RO)
 *
 * Voltage Support 3.3V: This bit shall depend on the Host System ability.
 *
 * Values:
 * 0 - 3.3V not supported
 * 1 - 3.3V supported
 */

#define BP_USDHC_HOST_CTRL_CAP_VS33      (24)      //!< Bit position for USDHC_HOST_CTRL_CAP_VS33.
#define BM_USDHC_HOST_CTRL_CAP_VS33      (0x01000000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_VS33.

//! @brief Get value of USDHC_HOST_CTRL_CAP_VS33 from a register value.
#define BG_USDHC_HOST_CTRL_CAP_VS33(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_VS33) >> BP_USDHC_HOST_CTRL_CAP_VS33)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field VS30[25] (RO)
 *
 * Voltage Support 3.0V: This bit shall depend on the Host System ability.
 *
 * Values:
 * 0 - 3.0V not supported
 * 1 - 3.0V supported
 */

#define BP_USDHC_HOST_CTRL_CAP_VS30      (25)      //!< Bit position for USDHC_HOST_CTRL_CAP_VS30.
#define BM_USDHC_HOST_CTRL_CAP_VS30      (0x02000000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_VS30.

//! @brief Get value of USDHC_HOST_CTRL_CAP_VS30 from a register value.
#define BG_USDHC_HOST_CTRL_CAP_VS30(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_VS30) >> BP_USDHC_HOST_CTRL_CAP_VS30)


/* --- Register HW_USDHC_HOST_CTRL_CAP, field VS18[26] (RO)
 *
 * Voltage Support 1.8V: This bit shall depend on the Host System ability.
 *
 * Values:
 * 0 - 1.8V not supported
 * 1 - 1.8V supported
 */

#define BP_USDHC_HOST_CTRL_CAP_VS18      (26)      //!< Bit position for USDHC_HOST_CTRL_CAP_VS18.
#define BM_USDHC_HOST_CTRL_CAP_VS18      (0x04000000)  //!< Bit mask for USDHC_HOST_CTRL_CAP_VS18.

//! @brief Get value of USDHC_HOST_CTRL_CAP_VS18 from a register value.
#define BG_USDHC_HOST_CTRL_CAP_VS18(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_CAP_VS18) >> BP_USDHC_HOST_CTRL_CAP_VS18)


//-------------------------------------------------------------------------------------------
// HW_USDHC_WTMK_LVL - Watermark Level
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_WTMK_LVL - Watermark Level (RW)
 *
 * Reset value: 0x08100810
 *
 * Both write and read watermark levels (FIFO threshold) are configurable. There value can range
 * from 1 to 128 words. Both write and read burst lengths are also Configurable. There value can
 * range from 1 to 31 words.
 */
typedef union _hw_usdhc_wtmk_lvl
{
    reg32_t U;
    struct _hw_usdhc_wtmk_lvl_bitfields
    {
        unsigned RD_WML : 8; //!< [7:0] Read Watermark Level: The number of words used as the watermark level (FIFO threshold) in a DMA read operation.
        unsigned RD_BRST_LEN : 5; //!< [12:8] Read Burst Length: Due to system restriction, the actual burst length may not exceed 16.
        unsigned RESERVED0 : 3; //!< [15:13] Reserved
        unsigned WR_WML : 8; //!< [23:16] Write Watermark Level: The number of words used as the watermark level (FIFO threshold) in a DMA write operation.
        unsigned WR_BRST_LEN : 5; //!< [28:24] Write Burst Length: Due to system restriction, the actual burst length may not exceed 16.
        unsigned RESERVED1 : 3; //!< [31:29] Reserved
    } B;
} hw_usdhc_wtmk_lvl_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_WTMK_LVL register
 */
#define HW_USDHC_WTMK_LVL_ADDR(x)      (REGS_USDHC_BASE(x) + 0x44)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_WTMK_LVL(x)           (*(volatile hw_usdhc_wtmk_lvl_t *) HW_USDHC_WTMK_LVL_ADDR(x))
#define HW_USDHC_WTMK_LVL_RD(x)        (HW_USDHC_WTMK_LVL(x).U)
#define HW_USDHC_WTMK_LVL_WR(x, v)     (HW_USDHC_WTMK_LVL(x).U = (v))
#define HW_USDHC_WTMK_LVL_SET(x, v)    (HW_USDHC_WTMK_LVL_WR(x, HW_USDHC_WTMK_LVL_RD(x) |  (v)))
#define HW_USDHC_WTMK_LVL_CLR(x, v)    (HW_USDHC_WTMK_LVL_WR(x, HW_USDHC_WTMK_LVL_RD(x) & ~(v)))
#define HW_USDHC_WTMK_LVL_TOG(x, v)    (HW_USDHC_WTMK_LVL_WR(x, HW_USDHC_WTMK_LVL_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_WTMK_LVL bitfields
 */

/* --- Register HW_USDHC_WTMK_LVL, field RD_WML[7:0] (RW)
 *
 * Read Watermark Level: The number of words used as the watermark level (FIFO threshold) in a DMA
 * read operation. Also the number of words as a sequence of read bursts in back-to-back mode. The
 * maximum legal value for the read water mark level is 128.
 */

#define BP_USDHC_WTMK_LVL_RD_WML      (0)      //!< Bit position for USDHC_WTMK_LVL_RD_WML.
#define BM_USDHC_WTMK_LVL_RD_WML      (0x000000ff)  //!< Bit mask for USDHC_WTMK_LVL_RD_WML.

//! @brief Get value of USDHC_WTMK_LVL_RD_WML from a register value.
#define BG_USDHC_WTMK_LVL_RD_WML(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_WTMK_LVL_RD_WML) >> BP_USDHC_WTMK_LVL_RD_WML)

//! @brief Format value for bitfield USDHC_WTMK_LVL_RD_WML.
#define BF_USDHC_WTMK_LVL_RD_WML(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_WTMK_LVL_RD_WML) & BM_USDHC_WTMK_LVL_RD_WML)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RD_WML field to a new value.
#define BW_USDHC_WTMK_LVL_RD_WML(x, v)   (HW_USDHC_WTMK_LVL_WR(x, (HW_USDHC_WTMK_LVL_RD(x) & ~BM_USDHC_WTMK_LVL_RD_WML) | BF_USDHC_WTMK_LVL_RD_WML(v)))
#endif

/* --- Register HW_USDHC_WTMK_LVL, field RD_BRST_LEN[12:8] (RW)
 *
 * Read Burst Length: Due to system restriction, the actual burst length may not exceed 16. The
 * number of words the uSDHC reads in a single burst. The read burst length must be less than or
 * equal to the read watermark level, and all bursts within a watermark level transfer will be in
 * back-to-back mode. On reset, this field will be 8. Writing 0 to this field will result in '01000'
 * (i.e. it is not able to clear this field).
 */

#define BP_USDHC_WTMK_LVL_RD_BRST_LEN      (8)      //!< Bit position for USDHC_WTMK_LVL_RD_BRST_LEN.
#define BM_USDHC_WTMK_LVL_RD_BRST_LEN      (0x00001f00)  //!< Bit mask for USDHC_WTMK_LVL_RD_BRST_LEN.

//! @brief Get value of USDHC_WTMK_LVL_RD_BRST_LEN from a register value.
#define BG_USDHC_WTMK_LVL_RD_BRST_LEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_WTMK_LVL_RD_BRST_LEN) >> BP_USDHC_WTMK_LVL_RD_BRST_LEN)

//! @brief Format value for bitfield USDHC_WTMK_LVL_RD_BRST_LEN.
#define BF_USDHC_WTMK_LVL_RD_BRST_LEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_WTMK_LVL_RD_BRST_LEN) & BM_USDHC_WTMK_LVL_RD_BRST_LEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RD_BRST_LEN field to a new value.
#define BW_USDHC_WTMK_LVL_RD_BRST_LEN(x, v)   (HW_USDHC_WTMK_LVL_WR(x, (HW_USDHC_WTMK_LVL_RD(x) & ~BM_USDHC_WTMK_LVL_RD_BRST_LEN) | BF_USDHC_WTMK_LVL_RD_BRST_LEN(v)))
#endif

/* --- Register HW_USDHC_WTMK_LVL, field WR_WML[23:16] (RW)
 *
 * Write Watermark Level: The number of words used as the watermark level (FIFO threshold) in a DMA
 * write operation. Also the number of words as a sequence of write bursts in back-to-back mode. The
 * maximum legal value for the write watermark level is 128.
 */

#define BP_USDHC_WTMK_LVL_WR_WML      (16)      //!< Bit position for USDHC_WTMK_LVL_WR_WML.
#define BM_USDHC_WTMK_LVL_WR_WML      (0x00ff0000)  //!< Bit mask for USDHC_WTMK_LVL_WR_WML.

//! @brief Get value of USDHC_WTMK_LVL_WR_WML from a register value.
#define BG_USDHC_WTMK_LVL_WR_WML(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_WTMK_LVL_WR_WML) >> BP_USDHC_WTMK_LVL_WR_WML)

//! @brief Format value for bitfield USDHC_WTMK_LVL_WR_WML.
#define BF_USDHC_WTMK_LVL_WR_WML(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_WTMK_LVL_WR_WML) & BM_USDHC_WTMK_LVL_WR_WML)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WR_WML field to a new value.
#define BW_USDHC_WTMK_LVL_WR_WML(x, v)   (HW_USDHC_WTMK_LVL_WR(x, (HW_USDHC_WTMK_LVL_RD(x) & ~BM_USDHC_WTMK_LVL_WR_WML) | BF_USDHC_WTMK_LVL_WR_WML(v)))
#endif

/* --- Register HW_USDHC_WTMK_LVL, field WR_BRST_LEN[28:24] (RW)
 *
 * Write Burst Length: Due to system restriction, the actual burst length may not exceed 16. The
 * number of words the uSDHC writes in a single burst. The write burst length must be less than or
 * equal to the write watermark level, and all bursts within a watermark level transfer will be in
 * back-to-back mode. On reset, this field will be 8. Writing 0 to this field will result in '01000'
 * (i.e. it is not able to clear this field).
 */

#define BP_USDHC_WTMK_LVL_WR_BRST_LEN      (24)      //!< Bit position for USDHC_WTMK_LVL_WR_BRST_LEN.
#define BM_USDHC_WTMK_LVL_WR_BRST_LEN      (0x1f000000)  //!< Bit mask for USDHC_WTMK_LVL_WR_BRST_LEN.

//! @brief Get value of USDHC_WTMK_LVL_WR_BRST_LEN from a register value.
#define BG_USDHC_WTMK_LVL_WR_BRST_LEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_WTMK_LVL_WR_BRST_LEN) >> BP_USDHC_WTMK_LVL_WR_BRST_LEN)

//! @brief Format value for bitfield USDHC_WTMK_LVL_WR_BRST_LEN.
#define BF_USDHC_WTMK_LVL_WR_BRST_LEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_WTMK_LVL_WR_BRST_LEN) & BM_USDHC_WTMK_LVL_WR_BRST_LEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WR_BRST_LEN field to a new value.
#define BW_USDHC_WTMK_LVL_WR_BRST_LEN(x, v)   (HW_USDHC_WTMK_LVL_WR(x, (HW_USDHC_WTMK_LVL_RD(x) & ~BM_USDHC_WTMK_LVL_WR_BRST_LEN) | BF_USDHC_WTMK_LVL_WR_BRST_LEN(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_MIX_CTRL - Mixer Control
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_MIX_CTRL - Mixer Control (RW)
 *
 * Reset value: 0x80000000
 *
 * This register is used to DMA and data transfer. To prevent data loss, The software should be
 * check if data transfer is active before write this register. Olny data transfer is invalid there
 * can be write. These bits are DPSEL, MBSEL, DTDSEL, AC12EN, BCEN and DMAEN.   Transfer Type
 * Register Setting for Various Transfer Types          Multi/Single Block Select    Block Count
 * Enable    Block Count    Function        0    Don't Care    Don't Care    Single Transfer      1
 * 0    Don't Care    Infinite Transfer      1    1    Positive Number    Multiple Transfer      1
 * 1    Zero    No Data Transfer
 */
typedef union _hw_usdhc_mix_ctrl
{
    reg32_t U;
    struct _hw_usdhc_mix_ctrl_bitfields
    {
        unsigned DMAEN : 1; //!< [0] DMA Enable: This bit enables DMA functionality.
        unsigned BCEN : 1; //!< [1] Block Count Enable: This bit is used to enable the Block Count register, which is only relevant for multiple block transfers.
        unsigned AC12EN : 1; //!< [2] Auto CMD12 Enable: Multiple block transfers for memory require a CMD12 to stop the transaction.
        unsigned DDR_EN : 1; //!< [3] Dual Data Rate mode selection
        unsigned DTDSEL : 1; //!< [4] Data Transfer Direction Select: This bit defines the direction of DAT line data transfers.
        unsigned MSBSEL : 1; //!< [5] Multi / Single Block Select: This bit enables multiple block DAT line data transfers.
        unsigned NIBBLE_POS : 1; //!< [6] In DDR 4 bit mode nibble position indictation.
        unsigned AC23EN : 1; //!< [7] Auto CMD23 Enable When this bit is set to 1, the Host Controller issues a CMD23 automatically before issuing a command specified in the Command Register.
        unsigned RESERVED0 : 14; //!< [21:8] Reserved
        unsigned EXE_TUNE : 1; //!< [22] Execute Tuning: (Only used for SD3.0, SDR104 mode) This bit is set to 1 to indicate the Host Driver is starting tuning procedure.
        unsigned SMP_CLK_SEL : 1; //!< [23] Tuned clock or Fixed clock is used to sample data/cmd (Only used for SD3.0, SDR104 mode)
        unsigned AUTO_TUNE_EN : 1; //!< [24] Auto tuning enable (Only used for SD3.0, SDR104 mode)
        unsigned FBCLK_SEL : 1; //!< [25] Feedback clock source selection (Only used for SD3.0, SDR104 mode)
        unsigned RESERVED1 : 3; //!< [28:26] Reserved
        unsigned AC12_RD_POINT : 1; //!< [29] Only for debug.
        unsigned CMD_DMY_WAIT_CFG : 1; //!< [30] Only for debug.
        unsigned CMD_DMY_EN : 1; //!< [31] Only for debug.
    } B;
} hw_usdhc_mix_ctrl_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_MIX_CTRL register
 */
#define HW_USDHC_MIX_CTRL_ADDR(x)      (REGS_USDHC_BASE(x) + 0x48)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_MIX_CTRL(x)           (*(volatile hw_usdhc_mix_ctrl_t *) HW_USDHC_MIX_CTRL_ADDR(x))
#define HW_USDHC_MIX_CTRL_RD(x)        (HW_USDHC_MIX_CTRL(x).U)
#define HW_USDHC_MIX_CTRL_WR(x, v)     (HW_USDHC_MIX_CTRL(x).U = (v))
#define HW_USDHC_MIX_CTRL_SET(x, v)    (HW_USDHC_MIX_CTRL_WR(x, HW_USDHC_MIX_CTRL_RD(x) |  (v)))
#define HW_USDHC_MIX_CTRL_CLR(x, v)    (HW_USDHC_MIX_CTRL_WR(x, HW_USDHC_MIX_CTRL_RD(x) & ~(v)))
#define HW_USDHC_MIX_CTRL_TOG(x, v)    (HW_USDHC_MIX_CTRL_WR(x, HW_USDHC_MIX_CTRL_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_MIX_CTRL bitfields
 */

/* --- Register HW_USDHC_MIX_CTRL, field DMAEN[0] (RW)
 *
 * DMA Enable: This bit enables DMA functionality. If this bit is set to 1, a DMA operation shall
 * begin when the Host Driver sets the DPSEL bit of this register. Whether the Simple DMA, or the
 * Advanced DMA, is active depends on the DMA Select field of the Protocol Control register.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_MIX_CTRL_DMAEN      (0)      //!< Bit position for USDHC_MIX_CTRL_DMAEN.
#define BM_USDHC_MIX_CTRL_DMAEN      (0x00000001)  //!< Bit mask for USDHC_MIX_CTRL_DMAEN.

//! @brief Get value of USDHC_MIX_CTRL_DMAEN from a register value.
#define BG_USDHC_MIX_CTRL_DMAEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_DMAEN) >> BP_USDHC_MIX_CTRL_DMAEN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_DMAEN.
#define BF_USDHC_MIX_CTRL_DMAEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_DMAEN) & BM_USDHC_MIX_CTRL_DMAEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DMAEN field to a new value.
#define BW_USDHC_MIX_CTRL_DMAEN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_DMAEN) | BF_USDHC_MIX_CTRL_DMAEN(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field BCEN[1] (RW)
 *
 * Block Count Enable: This bit is used to enable the Block Count register, which is only relevant
 * for multiple block transfers. When this bit is 0, the internal counter for block is disabled,
 * which is useful in executing an infinite transfer.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_MIX_CTRL_BCEN      (1)      //!< Bit position for USDHC_MIX_CTRL_BCEN.
#define BM_USDHC_MIX_CTRL_BCEN      (0x00000002)  //!< Bit mask for USDHC_MIX_CTRL_BCEN.

//! @brief Get value of USDHC_MIX_CTRL_BCEN from a register value.
#define BG_USDHC_MIX_CTRL_BCEN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_BCEN) >> BP_USDHC_MIX_CTRL_BCEN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_BCEN.
#define BF_USDHC_MIX_CTRL_BCEN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_BCEN) & BM_USDHC_MIX_CTRL_BCEN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BCEN field to a new value.
#define BW_USDHC_MIX_CTRL_BCEN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_BCEN) | BF_USDHC_MIX_CTRL_BCEN(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field AC12EN[2] (RW)
 *
 * Auto CMD12 Enable: Multiple block transfers for memory require a CMD12 to stop the transaction.
 * When this bit is set to 1, the uSDHC will issue a CMD12 automatically when the last block
 * transfer has completed. The Host Driver shall not set this bit to issue commands that do not
 * require CMD12 to stop a multiple block data transfer. In particular, secure commands defined in
 * File Security Specification (see reference list) do not require CMD12. In single block transfer,
 * the uSDHC will ignore this bit no matter if it is set or not.
 *
 * Values:
 * 0 - Disable
 * 1 - Enable
 */

#define BP_USDHC_MIX_CTRL_AC12EN      (2)      //!< Bit position for USDHC_MIX_CTRL_AC12EN.
#define BM_USDHC_MIX_CTRL_AC12EN      (0x00000004)  //!< Bit mask for USDHC_MIX_CTRL_AC12EN.

//! @brief Get value of USDHC_MIX_CTRL_AC12EN from a register value.
#define BG_USDHC_MIX_CTRL_AC12EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_AC12EN) >> BP_USDHC_MIX_CTRL_AC12EN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_AC12EN.
#define BF_USDHC_MIX_CTRL_AC12EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_AC12EN) & BM_USDHC_MIX_CTRL_AC12EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12EN field to a new value.
#define BW_USDHC_MIX_CTRL_AC12EN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_AC12EN) | BF_USDHC_MIX_CTRL_AC12EN(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field DDR_EN[3] (RW)
 *
 * Dual Data Rate mode selection
 */

#define BP_USDHC_MIX_CTRL_DDR_EN      (3)      //!< Bit position for USDHC_MIX_CTRL_DDR_EN.
#define BM_USDHC_MIX_CTRL_DDR_EN      (0x00000008)  //!< Bit mask for USDHC_MIX_CTRL_DDR_EN.

//! @brief Get value of USDHC_MIX_CTRL_DDR_EN from a register value.
#define BG_USDHC_MIX_CTRL_DDR_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_DDR_EN) >> BP_USDHC_MIX_CTRL_DDR_EN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_DDR_EN.
#define BF_USDHC_MIX_CTRL_DDR_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_DDR_EN) & BM_USDHC_MIX_CTRL_DDR_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DDR_EN field to a new value.
#define BW_USDHC_MIX_CTRL_DDR_EN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_DDR_EN) | BF_USDHC_MIX_CTRL_DDR_EN(v)))
#endif

/* --- Register HW_USDHC_MIX_CTRL, field DTDSEL[4] (RW)
 *
 * Data Transfer Direction Select: This bit defines the direction of DAT line data transfers. The
 * bit is set to 1 by the Host Driver to transfer data from the SD card to the uSDHC and is set to 0
 * for all other commands.
 *
 * Values:
 * 0 - Write (Host to Card)
 * 1 - Read (Card to Host)
 */

#define BP_USDHC_MIX_CTRL_DTDSEL      (4)      //!< Bit position for USDHC_MIX_CTRL_DTDSEL.
#define BM_USDHC_MIX_CTRL_DTDSEL      (0x00000010)  //!< Bit mask for USDHC_MIX_CTRL_DTDSEL.

//! @brief Get value of USDHC_MIX_CTRL_DTDSEL from a register value.
#define BG_USDHC_MIX_CTRL_DTDSEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_DTDSEL) >> BP_USDHC_MIX_CTRL_DTDSEL)

//! @brief Format value for bitfield USDHC_MIX_CTRL_DTDSEL.
#define BF_USDHC_MIX_CTRL_DTDSEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_DTDSEL) & BM_USDHC_MIX_CTRL_DTDSEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTDSEL field to a new value.
#define BW_USDHC_MIX_CTRL_DTDSEL(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_DTDSEL) | BF_USDHC_MIX_CTRL_DTDSEL(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field MSBSEL[5] (RW)
 *
 * Multi / Single Block Select: This bit enables multiple block DAT line data transfers. For any
 * other commands, this bit shall be set to 0. If this bit is 0, it is not necessary to set the
 * Block Count register. (Refer to ).
 *
 * Values:
 * 0 - Single Block
 * 1 - Multiple Blocks
 */

#define BP_USDHC_MIX_CTRL_MSBSEL      (5)      //!< Bit position for USDHC_MIX_CTRL_MSBSEL.
#define BM_USDHC_MIX_CTRL_MSBSEL      (0x00000020)  //!< Bit mask for USDHC_MIX_CTRL_MSBSEL.

//! @brief Get value of USDHC_MIX_CTRL_MSBSEL from a register value.
#define BG_USDHC_MIX_CTRL_MSBSEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_MSBSEL) >> BP_USDHC_MIX_CTRL_MSBSEL)

//! @brief Format value for bitfield USDHC_MIX_CTRL_MSBSEL.
#define BF_USDHC_MIX_CTRL_MSBSEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_MSBSEL) & BM_USDHC_MIX_CTRL_MSBSEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the MSBSEL field to a new value.
#define BW_USDHC_MIX_CTRL_MSBSEL(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_MSBSEL) | BF_USDHC_MIX_CTRL_MSBSEL(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field NIBBLE_POS[6] (RW)
 *
 * In DDR 4 bit mode nibble position indictation. 0- the sequence is 'odd high nibble -> even high
 * nibble -> odd low nibble -> even low nibble'; 1- the sequence is 'odd high nibble -> odd low
 * nibble -> even high nibble -> even low nibble'.
 */

#define BP_USDHC_MIX_CTRL_NIBBLE_POS      (6)      //!< Bit position for USDHC_MIX_CTRL_NIBBLE_POS.
#define BM_USDHC_MIX_CTRL_NIBBLE_POS      (0x00000040)  //!< Bit mask for USDHC_MIX_CTRL_NIBBLE_POS.

//! @brief Get value of USDHC_MIX_CTRL_NIBBLE_POS from a register value.
#define BG_USDHC_MIX_CTRL_NIBBLE_POS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_NIBBLE_POS) >> BP_USDHC_MIX_CTRL_NIBBLE_POS)

//! @brief Format value for bitfield USDHC_MIX_CTRL_NIBBLE_POS.
#define BF_USDHC_MIX_CTRL_NIBBLE_POS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_NIBBLE_POS) & BM_USDHC_MIX_CTRL_NIBBLE_POS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the NIBBLE_POS field to a new value.
#define BW_USDHC_MIX_CTRL_NIBBLE_POS(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_NIBBLE_POS) | BF_USDHC_MIX_CTRL_NIBBLE_POS(v)))
#endif

/* --- Register HW_USDHC_MIX_CTRL, field AC23EN[7] (RW)
 *
 * Auto CMD23 Enable When this bit is set to 1, the Host Controller issues a CMD23 automatically
 * before issuing a command specified in the Command Register.
 */

#define BP_USDHC_MIX_CTRL_AC23EN      (7)      //!< Bit position for USDHC_MIX_CTRL_AC23EN.
#define BM_USDHC_MIX_CTRL_AC23EN      (0x00000080)  //!< Bit mask for USDHC_MIX_CTRL_AC23EN.

//! @brief Get value of USDHC_MIX_CTRL_AC23EN from a register value.
#define BG_USDHC_MIX_CTRL_AC23EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_AC23EN) >> BP_USDHC_MIX_CTRL_AC23EN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_AC23EN.
#define BF_USDHC_MIX_CTRL_AC23EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_AC23EN) & BM_USDHC_MIX_CTRL_AC23EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC23EN field to a new value.
#define BW_USDHC_MIX_CTRL_AC23EN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_AC23EN) | BF_USDHC_MIX_CTRL_AC23EN(v)))
#endif

/* --- Register HW_USDHC_MIX_CTRL, field EXE_TUNE[22] (RW)
 *
 * Execute Tuning: (Only used for SD3.0, SDR104 mode) This bit is set to 1 to indicate the Host
 * Driver is starting tuning procedure. Tuning procedure is aborted by writing 0.
 *
 * Values:
 * 0 - Not Tuned or Tuning Completed
 * 1 - Execute Tuning
 */

#define BP_USDHC_MIX_CTRL_EXE_TUNE      (22)      //!< Bit position for USDHC_MIX_CTRL_EXE_TUNE.
#define BM_USDHC_MIX_CTRL_EXE_TUNE      (0x00400000)  //!< Bit mask for USDHC_MIX_CTRL_EXE_TUNE.

//! @brief Get value of USDHC_MIX_CTRL_EXE_TUNE from a register value.
#define BG_USDHC_MIX_CTRL_EXE_TUNE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_EXE_TUNE) >> BP_USDHC_MIX_CTRL_EXE_TUNE)

//! @brief Format value for bitfield USDHC_MIX_CTRL_EXE_TUNE.
#define BF_USDHC_MIX_CTRL_EXE_TUNE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_EXE_TUNE) & BM_USDHC_MIX_CTRL_EXE_TUNE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the EXE_TUNE field to a new value.
#define BW_USDHC_MIX_CTRL_EXE_TUNE(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_EXE_TUNE) | BF_USDHC_MIX_CTRL_EXE_TUNE(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field SMP_CLK_SEL[23] (RW)
 *
 * Tuned clock or Fixed clock is used to sample data/cmd (Only used for SD3.0, SDR104 mode)
 *
 * Values:
 * 0 - Fixed clock is used to sample data/cmd
 * 1 - Tuned clock is used to sample data/cmd
 */

#define BP_USDHC_MIX_CTRL_SMP_CLK_SEL      (23)      //!< Bit position for USDHC_MIX_CTRL_SMP_CLK_SEL.
#define BM_USDHC_MIX_CTRL_SMP_CLK_SEL      (0x00800000)  //!< Bit mask for USDHC_MIX_CTRL_SMP_CLK_SEL.

//! @brief Get value of USDHC_MIX_CTRL_SMP_CLK_SEL from a register value.
#define BG_USDHC_MIX_CTRL_SMP_CLK_SEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_SMP_CLK_SEL) >> BP_USDHC_MIX_CTRL_SMP_CLK_SEL)

//! @brief Format value for bitfield USDHC_MIX_CTRL_SMP_CLK_SEL.
#define BF_USDHC_MIX_CTRL_SMP_CLK_SEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_SMP_CLK_SEL) & BM_USDHC_MIX_CTRL_SMP_CLK_SEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SMP_CLK_SEL field to a new value.
#define BW_USDHC_MIX_CTRL_SMP_CLK_SEL(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_SMP_CLK_SEL) | BF_USDHC_MIX_CTRL_SMP_CLK_SEL(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field AUTO_TUNE_EN[24] (RW)
 *
 * Auto tuning enable (Only used for SD3.0, SDR104 mode)
 *
 * Values:
 * 0 - disable auto tuning
 * 1 - enable auto tuning
 */

#define BP_USDHC_MIX_CTRL_AUTO_TUNE_EN      (24)      //!< Bit position for USDHC_MIX_CTRL_AUTO_TUNE_EN.
#define BM_USDHC_MIX_CTRL_AUTO_TUNE_EN      (0x01000000)  //!< Bit mask for USDHC_MIX_CTRL_AUTO_TUNE_EN.

//! @brief Get value of USDHC_MIX_CTRL_AUTO_TUNE_EN from a register value.
#define BG_USDHC_MIX_CTRL_AUTO_TUNE_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_AUTO_TUNE_EN) >> BP_USDHC_MIX_CTRL_AUTO_TUNE_EN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_AUTO_TUNE_EN.
#define BF_USDHC_MIX_CTRL_AUTO_TUNE_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_AUTO_TUNE_EN) & BM_USDHC_MIX_CTRL_AUTO_TUNE_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AUTO_TUNE_EN field to a new value.
#define BW_USDHC_MIX_CTRL_AUTO_TUNE_EN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_AUTO_TUNE_EN) | BF_USDHC_MIX_CTRL_AUTO_TUNE_EN(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field FBCLK_SEL[25] (RW)
 *
 * Feedback clock source selection (Only used for SD3.0, SDR104 mode)
 *
 * Values:
 * 0 - feedback clock comes from the loopback CLK
 * 1 - feedback clock comes from the ipp_card_clk_out
 */

#define BP_USDHC_MIX_CTRL_FBCLK_SEL      (25)      //!< Bit position for USDHC_MIX_CTRL_FBCLK_SEL.
#define BM_USDHC_MIX_CTRL_FBCLK_SEL      (0x02000000)  //!< Bit mask for USDHC_MIX_CTRL_FBCLK_SEL.

//! @brief Get value of USDHC_MIX_CTRL_FBCLK_SEL from a register value.
#define BG_USDHC_MIX_CTRL_FBCLK_SEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_FBCLK_SEL) >> BP_USDHC_MIX_CTRL_FBCLK_SEL)

//! @brief Format value for bitfield USDHC_MIX_CTRL_FBCLK_SEL.
#define BF_USDHC_MIX_CTRL_FBCLK_SEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_FBCLK_SEL) & BM_USDHC_MIX_CTRL_FBCLK_SEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the FBCLK_SEL field to a new value.
#define BW_USDHC_MIX_CTRL_FBCLK_SEL(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_FBCLK_SEL) | BF_USDHC_MIX_CTRL_FBCLK_SEL(v)))
#endif


/* --- Register HW_USDHC_MIX_CTRL, field AC12_RD_POINT[29] (RW)
 *
 * Only for debug. It's used to control when to send Auto CMD12 after multi-block read. 1 send Auto
 * CMD12 8 cycles after CRC is checked successfully 0 send Auto CMD12 right after CRC is checked
 * successfully
 */

#define BP_USDHC_MIX_CTRL_AC12_RD_POINT      (29)      //!< Bit position for USDHC_MIX_CTRL_AC12_RD_POINT.
#define BM_USDHC_MIX_CTRL_AC12_RD_POINT      (0x20000000)  //!< Bit mask for USDHC_MIX_CTRL_AC12_RD_POINT.

//! @brief Get value of USDHC_MIX_CTRL_AC12_RD_POINT from a register value.
#define BG_USDHC_MIX_CTRL_AC12_RD_POINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_AC12_RD_POINT) >> BP_USDHC_MIX_CTRL_AC12_RD_POINT)

//! @brief Format value for bitfield USDHC_MIX_CTRL_AC12_RD_POINT.
#define BF_USDHC_MIX_CTRL_AC12_RD_POINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_AC12_RD_POINT) & BM_USDHC_MIX_CTRL_AC12_RD_POINT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12_RD_POINT field to a new value.
#define BW_USDHC_MIX_CTRL_AC12_RD_POINT(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_AC12_RD_POINT) | BF_USDHC_MIX_CTRL_AC12_RD_POINT(v)))
#endif

/* --- Register HW_USDHC_MIX_CTRL, field CMD_DMY_WAIT_CFG[30] (RW)
 *
 * Only for debug. It's also used to control the number of dummy clock cycles after each command
 * when CMD_DMY_EN bit is enabled. CMD_DMY_EN = 0, CMD_DMY_WAIT_CFG = x : 12 dummy clocks after each
 * command CMD_DMY_EN = 1, CMD_DMY_WAIT_CFG = 0: 20 dummy clocks after each command CMD_DMY_EN = 1,
 * CMD_DMY_WAIT_CFG = 1: 31 dummy clocks after each command
 */

#define BP_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG      (30)      //!< Bit position for USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG.
#define BM_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG      (0x40000000)  //!< Bit mask for USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG.

//! @brief Get value of USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG from a register value.
#define BG_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG) >> BP_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG)

//! @brief Format value for bitfield USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG.
#define BF_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG) & BM_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMD_DMY_WAIT_CFG field to a new value.
#define BW_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG) | BF_USDHC_MIX_CTRL_CMD_DMY_WAIT_CFG(v)))
#endif

/* --- Register HW_USDHC_MIX_CTRL, field CMD_DMY_EN[31] (RW)
 *
 * Only for debug. It's used to control the number of dummy clock cycles after each command.
 */

#define BP_USDHC_MIX_CTRL_CMD_DMY_EN      (31)      //!< Bit position for USDHC_MIX_CTRL_CMD_DMY_EN.
#define BM_USDHC_MIX_CTRL_CMD_DMY_EN      (0x80000000)  //!< Bit mask for USDHC_MIX_CTRL_CMD_DMY_EN.

//! @brief Get value of USDHC_MIX_CTRL_CMD_DMY_EN from a register value.
#define BG_USDHC_MIX_CTRL_CMD_DMY_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MIX_CTRL_CMD_DMY_EN) >> BP_USDHC_MIX_CTRL_CMD_DMY_EN)

//! @brief Format value for bitfield USDHC_MIX_CTRL_CMD_DMY_EN.
#define BF_USDHC_MIX_CTRL_CMD_DMY_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MIX_CTRL_CMD_DMY_EN) & BM_USDHC_MIX_CTRL_CMD_DMY_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMD_DMY_EN field to a new value.
#define BW_USDHC_MIX_CTRL_CMD_DMY_EN(x, v)   (HW_USDHC_MIX_CTRL_WR(x, (HW_USDHC_MIX_CTRL_RD(x) & ~BM_USDHC_MIX_CTRL_CMD_DMY_EN) | BF_USDHC_MIX_CTRL_CMD_DMY_EN(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_FORCE_EVENT - Force Event
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_FORCE_EVENT - Force Event (WORZ)
 *
 * Reset value: 0x00000000
 *
 * The Force Event Register is not a physically implemented register. Rather, it is an address at
 * which the Interrupt Status Register can be written if the corresponding bit of the Interrupt
 * Status Enable Register is set. This register is a write only register and writing 0 to it has no
 * effect. Writing 1 to this register actually sets the corresponding bit of Interrupt Status
 * Register. A read from this register always results in 0's. In order to change the corresponding
 * status bits in the Interrupt Status Register, make sure to set IPGEN bit in System Control
 * Register so that ipg_clk is always active.  Forcing a card interrupt will generate a short pulse
 * on the DAT[1] line, and the driver may treat this interrupt as a normal interrupt. The interrupt
 * service routine may skip polling the card interrupt factor as the interrupt is self cleared.
 */
typedef union _hw_usdhc_force_event
{
    reg32_t U;
    struct _hw_usdhc_force_event_bitfields
    {
        unsigned FEVTAC12NE : 1; //!< [0] Force Event Auto Command 12 Not Executed: Forces the AC12NE bit in the Auto Command12 Error Status Register to be set
        unsigned FEVTAC12TOE : 1; //!< [1] Force Event Auto Command 12 Time Out Error: Forces the AC12TOE bit in the Auto Command12 Error Status Register to be set
        unsigned FEVTAC12CE : 1; //!< [2] Force Event Auto Command 12 CRC Error: Forces the AC12CE bit in the Auto Command12 Error Status Register to be set
        unsigned FEVTAC12EBE : 1; //!< [3] Force Event Auto Command 12 End Bit Error: Forces the AC12EBE bit in the Auto Command12 Error Status Register to be set
        unsigned FEVTAC12IE : 1; //!< [4] Force Event Auto Command 12 Index Error: Forces the AC12IE bit in the Auto Command12 Error Status Register to be set
        unsigned RESERVED0 : 2; //!< [6:5] Reserved
        unsigned FEVTCNIBAC12E : 1; //!< [7] Force Event Command Not Executed By Auto Command 12 Error: Forces the CNIBAC12E bit in the Auto Command12 Error Status Register to be set
        unsigned RESERVED1 : 8; //!< [15:8] Reserved
        unsigned FEVTCCE : 1; //!< [16] Force Event Command Time Out Error: Forces the CTOE bit of Interrupt Status Register to be set
        unsigned FEVTCCE1 : 1; //!< [17] Force Event Command CRC Error: Forces the CCE bit of Interrupt Status Register to be set
        unsigned FEVTCEBE : 1; //!< [18] Force Event Command End Bit Error: Forces the CEBE bit of Interrupt Status Register to be set
        unsigned FEVTCIE : 1; //!< [19] Force Event Command Index Error: Forces the CCE bit of Interrupt Status Register to be set
        unsigned FEVTDTOE : 1; //!< [20] Force Event Data Time Out Error: Force the DTOE bit of Interrupt Status Register to be set
        unsigned FEVTDCE : 1; //!< [21] Force Event Data CRC Error: Forces the DCE bit of Interrupt Status Register to be set
        unsigned FEVTDEBE : 1; //!< [22] Force Event Data End Bit Error: Forces the DEBE bit of Interrupt Status Register to be set
        unsigned RESERVED2 : 1; //!< [23] Reserved
        unsigned FEVTAC12E : 1; //!< [24] Force Event Auto Command 12 Error: Forces the AC12E bit of Interrupt Status Register to be set
        unsigned RESERVED3 : 1; //!< [25] Reserved
        unsigned FEVTTNE : 1; //!< [26] Force Tuning Error: Forces the TNE bit of Interrupt Status Register to be set
        unsigned RESERVED4 : 1; //!< [27] Reserved
        unsigned FEVTDMAE : 1; //!< [28] Force Event DMA Error: Forces the DMAE bit of Interrupt Status Register to be set
        unsigned RESERVED5 : 2; //!< [30:29] Reserved
        unsigned FEVTCINT : 1; //!< [31] Force Event Card Interrupt: Writing 1 to this bit generates a short low-level pulse on the internal DAT[1] line, as if a self clearing interrupt was received from the external card.
    } B;
} hw_usdhc_force_event_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_FORCE_EVENT register
 */
#define HW_USDHC_FORCE_EVENT_ADDR(x)      (REGS_USDHC_BASE(x) + 0x50)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_FORCE_EVENT(x)           (*(volatile hw_usdhc_force_event_t *) HW_USDHC_FORCE_EVENT_ADDR(x))
#define HW_USDHC_FORCE_EVENT_WR(x, v)     (HW_USDHC_FORCE_EVENT(x).U = (v))
#endif

/*
 * constants & macros for individual USDHC_FORCE_EVENT bitfields
 */

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12NE[0] (WORZ)
 *
 * Force Event Auto Command 12 Not Executed: Forces the AC12NE bit in the Auto Command12 Error
 * Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12NE      (0)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12NE.
#define BM_USDHC_FORCE_EVENT_FEVTAC12NE      (0x00000001)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12NE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12NE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12NE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12NE) >> BP_USDHC_FORCE_EVENT_FEVTAC12NE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12NE.
#define BF_USDHC_FORCE_EVENT_FEVTAC12NE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12NE) & BM_USDHC_FORCE_EVENT_FEVTAC12NE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12TOE[1] (WORZ)
 *
 * Force Event Auto Command 12 Time Out Error: Forces the AC12TOE bit in the Auto Command12 Error
 * Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12TOE      (1)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12TOE.
#define BM_USDHC_FORCE_EVENT_FEVTAC12TOE      (0x00000002)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12TOE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12TOE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12TOE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12TOE) >> BP_USDHC_FORCE_EVENT_FEVTAC12TOE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12TOE.
#define BF_USDHC_FORCE_EVENT_FEVTAC12TOE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12TOE) & BM_USDHC_FORCE_EVENT_FEVTAC12TOE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12CE[2] (WORZ)
 *
 * Force Event Auto Command 12 CRC Error: Forces the AC12CE bit in the Auto Command12 Error Status
 * Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12CE      (2)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12CE.
#define BM_USDHC_FORCE_EVENT_FEVTAC12CE      (0x00000004)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12CE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12CE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12CE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12CE) >> BP_USDHC_FORCE_EVENT_FEVTAC12CE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12CE.
#define BF_USDHC_FORCE_EVENT_FEVTAC12CE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12CE) & BM_USDHC_FORCE_EVENT_FEVTAC12CE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12EBE[3] (WORZ)
 *
 * Force Event Auto Command 12 End Bit Error: Forces the AC12EBE bit in the Auto Command12 Error
 * Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12EBE      (3)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12EBE.
#define BM_USDHC_FORCE_EVENT_FEVTAC12EBE      (0x00000008)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12EBE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12EBE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12EBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12EBE) >> BP_USDHC_FORCE_EVENT_FEVTAC12EBE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12EBE.
#define BF_USDHC_FORCE_EVENT_FEVTAC12EBE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12EBE) & BM_USDHC_FORCE_EVENT_FEVTAC12EBE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12IE[4] (WORZ)
 *
 * Force Event Auto Command 12 Index Error: Forces the AC12IE bit in the Auto Command12 Error Status
 * Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12IE      (4)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12IE.
#define BM_USDHC_FORCE_EVENT_FEVTAC12IE      (0x00000010)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12IE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12IE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12IE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12IE) >> BP_USDHC_FORCE_EVENT_FEVTAC12IE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12IE.
#define BF_USDHC_FORCE_EVENT_FEVTAC12IE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12IE) & BM_USDHC_FORCE_EVENT_FEVTAC12IE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCNIBAC12E[7] (WORZ)
 *
 * Force Event Command Not Executed By Auto Command 12 Error: Forces the CNIBAC12E bit in the Auto
 * Command12 Error Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTCNIBAC12E      (7)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCNIBAC12E.
#define BM_USDHC_FORCE_EVENT_FEVTCNIBAC12E      (0x00000080)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCNIBAC12E.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCNIBAC12E from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCNIBAC12E(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCNIBAC12E) >> BP_USDHC_FORCE_EVENT_FEVTCNIBAC12E)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCNIBAC12E.
#define BF_USDHC_FORCE_EVENT_FEVTCNIBAC12E(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCNIBAC12E) & BM_USDHC_FORCE_EVENT_FEVTCNIBAC12E)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCCE[16] (WORZ)
 *
 * Force Event Command Time Out Error: Forces the CTOE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTCCE      (16)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCCE.
#define BM_USDHC_FORCE_EVENT_FEVTCCE      (0x00010000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCCE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCCE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCCE) >> BP_USDHC_FORCE_EVENT_FEVTCCE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCCE.
#define BF_USDHC_FORCE_EVENT_FEVTCCE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCCE) & BM_USDHC_FORCE_EVENT_FEVTCCE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCCE1[17] (WORZ)
 *
 * Force Event Command CRC Error: Forces the CCE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTCCE1      (17)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCCE1.
#define BM_USDHC_FORCE_EVENT_FEVTCCE1      (0x00020000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCCE1.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCCE1 from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCCE1(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCCE1) >> BP_USDHC_FORCE_EVENT_FEVTCCE1)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCCE1.
#define BF_USDHC_FORCE_EVENT_FEVTCCE1(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCCE1) & BM_USDHC_FORCE_EVENT_FEVTCCE1)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCEBE[18] (WORZ)
 *
 * Force Event Command End Bit Error: Forces the CEBE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTCEBE      (18)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCEBE.
#define BM_USDHC_FORCE_EVENT_FEVTCEBE      (0x00040000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCEBE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCEBE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCEBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCEBE) >> BP_USDHC_FORCE_EVENT_FEVTCEBE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCEBE.
#define BF_USDHC_FORCE_EVENT_FEVTCEBE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCEBE) & BM_USDHC_FORCE_EVENT_FEVTCEBE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCIE[19] (WORZ)
 *
 * Force Event Command Index Error: Forces the CCE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTCIE      (19)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCIE.
#define BM_USDHC_FORCE_EVENT_FEVTCIE      (0x00080000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCIE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCIE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCIE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCIE) >> BP_USDHC_FORCE_EVENT_FEVTCIE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCIE.
#define BF_USDHC_FORCE_EVENT_FEVTCIE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCIE) & BM_USDHC_FORCE_EVENT_FEVTCIE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTDTOE[20] (WORZ)
 *
 * Force Event Data Time Out Error: Force the DTOE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTDTOE      (20)      //!< Bit position for USDHC_FORCE_EVENT_FEVTDTOE.
#define BM_USDHC_FORCE_EVENT_FEVTDTOE      (0x00100000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTDTOE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTDTOE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTDTOE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTDTOE) >> BP_USDHC_FORCE_EVENT_FEVTDTOE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTDTOE.
#define BF_USDHC_FORCE_EVENT_FEVTDTOE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTDTOE) & BM_USDHC_FORCE_EVENT_FEVTDTOE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTDCE[21] (WORZ)
 *
 * Force Event Data CRC Error: Forces the DCE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTDCE      (21)      //!< Bit position for USDHC_FORCE_EVENT_FEVTDCE.
#define BM_USDHC_FORCE_EVENT_FEVTDCE      (0x00200000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTDCE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTDCE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTDCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTDCE) >> BP_USDHC_FORCE_EVENT_FEVTDCE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTDCE.
#define BF_USDHC_FORCE_EVENT_FEVTDCE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTDCE) & BM_USDHC_FORCE_EVENT_FEVTDCE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTDEBE[22] (WORZ)
 *
 * Force Event Data End Bit Error: Forces the DEBE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTDEBE      (22)      //!< Bit position for USDHC_FORCE_EVENT_FEVTDEBE.
#define BM_USDHC_FORCE_EVENT_FEVTDEBE      (0x00400000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTDEBE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTDEBE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTDEBE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTDEBE) >> BP_USDHC_FORCE_EVENT_FEVTDEBE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTDEBE.
#define BF_USDHC_FORCE_EVENT_FEVTDEBE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTDEBE) & BM_USDHC_FORCE_EVENT_FEVTDEBE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTAC12E[24] (WORZ)
 *
 * Force Event Auto Command 12 Error: Forces the AC12E bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTAC12E      (24)      //!< Bit position for USDHC_FORCE_EVENT_FEVTAC12E.
#define BM_USDHC_FORCE_EVENT_FEVTAC12E      (0x01000000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTAC12E.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTAC12E from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTAC12E(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTAC12E) >> BP_USDHC_FORCE_EVENT_FEVTAC12E)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTAC12E.
#define BF_USDHC_FORCE_EVENT_FEVTAC12E(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTAC12E) & BM_USDHC_FORCE_EVENT_FEVTAC12E)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTTNE[26] (WORZ)
 *
 * Force Tuning Error: Forces the TNE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTTNE      (26)      //!< Bit position for USDHC_FORCE_EVENT_FEVTTNE.
#define BM_USDHC_FORCE_EVENT_FEVTTNE      (0x04000000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTTNE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTTNE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTTNE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTTNE) >> BP_USDHC_FORCE_EVENT_FEVTTNE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTTNE.
#define BF_USDHC_FORCE_EVENT_FEVTTNE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTTNE) & BM_USDHC_FORCE_EVENT_FEVTTNE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTDMAE[28] (WORZ)
 *
 * Force Event DMA Error: Forces the DMAE bit of Interrupt Status Register to be set
 */

#define BP_USDHC_FORCE_EVENT_FEVTDMAE      (28)      //!< Bit position for USDHC_FORCE_EVENT_FEVTDMAE.
#define BM_USDHC_FORCE_EVENT_FEVTDMAE      (0x10000000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTDMAE.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTDMAE from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTDMAE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTDMAE) >> BP_USDHC_FORCE_EVENT_FEVTDMAE)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTDMAE.
#define BF_USDHC_FORCE_EVENT_FEVTDMAE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTDMAE) & BM_USDHC_FORCE_EVENT_FEVTDMAE)

/* --- Register HW_USDHC_FORCE_EVENT, field FEVTCINT[31] (WORZ)
 *
 * Force Event Card Interrupt: Writing 1 to this bit generates a short low-level pulse on the
 * internal DAT[1] line, as if a self clearing interrupt was received from the external card. If
 * enabled, the CINT bit will be set and the interrupt service routine may treat this interrupt as a
 * normal interrupt from the external card.
 */

#define BP_USDHC_FORCE_EVENT_FEVTCINT      (31)      //!< Bit position for USDHC_FORCE_EVENT_FEVTCINT.
#define BM_USDHC_FORCE_EVENT_FEVTCINT      (0x80000000)  //!< Bit mask for USDHC_FORCE_EVENT_FEVTCINT.

//! @brief Get value of USDHC_FORCE_EVENT_FEVTCINT from a register value.
#define BG_USDHC_FORCE_EVENT_FEVTCINT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_FORCE_EVENT_FEVTCINT) >> BP_USDHC_FORCE_EVENT_FEVTCINT)

//! @brief Format value for bitfield USDHC_FORCE_EVENT_FEVTCINT.
#define BF_USDHC_FORCE_EVENT_FEVTCINT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_FORCE_EVENT_FEVTCINT) & BM_USDHC_FORCE_EVENT_FEVTCINT)

//-------------------------------------------------------------------------------------------
// HW_USDHC_ADMA_ERR_STATUS - ADMA Error Status Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_ADMA_ERR_STATUS - ADMA Error Status Register (RO)
 *
 * Reset value: 0x00000000
 *
 * When an ADMA Error Interrupt has occurred, the ADMA Error States field in this register holds the
 * ADMA state and the ADMA System Address register holds the address around the error descriptor.
 * For recovering from this error, the Host Driver requires the ADMA state to identify the error
 * descriptor address as follows:   ST_STOP: Previous location set in the ADMA System Address
 * register is the error descriptor address  ST_FDS: Current location set in the ADMA System Address
 * register is the error descriptor address  ST_CADR: This state is never set because it only
 * increments the descriptor pointer and doesn't generate an ADMA error  ST_TFR: Previous location
 * set in the ADMA System Address register is the error descriptor address   In case of a write
 * operation, the Host Driver should use the ACMD22 to get the number of the written block, rather
 * than using this information, since unwritten data may exist in the Host Controller.  The Host
 * Controller generates the ADMA Error Interrupt when it detects invalid descriptor data (Valid=0)
 * in the ST_FDS state. The Host Driver can distinguish this error by reading the Valid bit of the
 * error descriptor.   ADMA Error State Coding         D01-D00    ADMA Error State (when error has
 * occurred)    Contents of ADMA System Address Register        00    ST_STOP (Stop DMA)    Holds
 * the address of the next executable Descriptor command      01    ST_FDS (Fetch Descriptor)
 * Holds the valid Descriptor address      10    ST_CADR (Change Address)    No ADMA Error is
 * generated      11    ST_TFR (Transfer Data)    Holds the address of the next executable
 * Descriptor command
 */
typedef union _hw_usdhc_adma_err_status
{
    reg32_t U;
    struct _hw_usdhc_adma_err_status_bitfields
    {
        unsigned ADMAES : 2; //!< [1:0] ADMA Error State (when ADMA Error is occurred.): This field indicates the state of the ADMA when an error has occurred during an ADMA data transfer.
        unsigned ADMALME : 1; //!< [2] ADMA Length Mismatch Error: This error occurs in the following 2 cases: While the Block Count Enable is being set, the total data length specified by the Descriptor table is different from that specified by the Block Count and Block Length Total data length can not be divided by the block length
        unsigned ADMADCE : 1; //!< [3] ADMA Descritor Error: This error occurs when invalid descriptor fetched by ADMA:
        unsigned RESERVED0 : 28; //!< [31:4] Reserved
    } B;
} hw_usdhc_adma_err_status_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_ADMA_ERR_STATUS register
 */
#define HW_USDHC_ADMA_ERR_STATUS_ADDR(x)      (REGS_USDHC_BASE(x) + 0x54)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_ADMA_ERR_STATUS(x)           (*(volatile hw_usdhc_adma_err_status_t *) HW_USDHC_ADMA_ERR_STATUS_ADDR(x))
#define HW_USDHC_ADMA_ERR_STATUS_RD(x)        (HW_USDHC_ADMA_ERR_STATUS(x).U)
#endif

/*
 * constants & macros for individual USDHC_ADMA_ERR_STATUS bitfields
 */

/* --- Register HW_USDHC_ADMA_ERR_STATUS, field ADMAES[1:0] (RO)
 *
 * ADMA Error State (when ADMA Error is occurred.): This field indicates the state of the ADMA when
 * an error has occurred during an ADMA data transfer. Refer to for more details.
 */

#define BP_USDHC_ADMA_ERR_STATUS_ADMAES      (0)      //!< Bit position for USDHC_ADMA_ERR_STATUS_ADMAES.
#define BM_USDHC_ADMA_ERR_STATUS_ADMAES      (0x00000003)  //!< Bit mask for USDHC_ADMA_ERR_STATUS_ADMAES.

//! @brief Get value of USDHC_ADMA_ERR_STATUS_ADMAES from a register value.
#define BG_USDHC_ADMA_ERR_STATUS_ADMAES(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_ADMA_ERR_STATUS_ADMAES) >> BP_USDHC_ADMA_ERR_STATUS_ADMAES)

/* --- Register HW_USDHC_ADMA_ERR_STATUS, field ADMALME[2] (RO)
 *
 * ADMA Length Mismatch Error: This error occurs in the following 2 cases: While the Block Count
 * Enable is being set, the total data length specified by the Descriptor table is different from
 * that specified by the Block Count and Block Length Total data length can not be divided by the
 * block length
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_ADMA_ERR_STATUS_ADMALME      (2)      //!< Bit position for USDHC_ADMA_ERR_STATUS_ADMALME.
#define BM_USDHC_ADMA_ERR_STATUS_ADMALME      (0x00000004)  //!< Bit mask for USDHC_ADMA_ERR_STATUS_ADMALME.

//! @brief Get value of USDHC_ADMA_ERR_STATUS_ADMALME from a register value.
#define BG_USDHC_ADMA_ERR_STATUS_ADMALME(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_ADMA_ERR_STATUS_ADMALME) >> BP_USDHC_ADMA_ERR_STATUS_ADMALME)


/* --- Register HW_USDHC_ADMA_ERR_STATUS, field ADMADCE[3] (RO)
 *
 * ADMA Descritor Error: This error occurs when invalid descriptor fetched by ADMA:
 *
 * Values:
 * 0 - No Error
 * 1 - Error
 */

#define BP_USDHC_ADMA_ERR_STATUS_ADMADCE      (3)      //!< Bit position for USDHC_ADMA_ERR_STATUS_ADMADCE.
#define BM_USDHC_ADMA_ERR_STATUS_ADMADCE      (0x00000008)  //!< Bit mask for USDHC_ADMA_ERR_STATUS_ADMADCE.

//! @brief Get value of USDHC_ADMA_ERR_STATUS_ADMADCE from a register value.
#define BG_USDHC_ADMA_ERR_STATUS_ADMADCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_ADMA_ERR_STATUS_ADMADCE) >> BP_USDHC_ADMA_ERR_STATUS_ADMADCE)


//-------------------------------------------------------------------------------------------
// HW_USDHC_ADMA_SYS_ADDR - ADMA System Address
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_ADMA_SYS_ADDR - ADMA System Address (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains the physical system memory address used for ADMA transfers.
 */
typedef union _hw_usdhc_adma_sys_addr
{
    reg32_t U;
    struct _hw_usdhc_adma_sys_addr_bitfields
    {
        unsigned RESERVED0 : 2; //!< [1:0] Reserved
        unsigned ADS_ADDR : 30; //!< [31:2] ADMA System Address: This register holds the word address of the executing command in the Descriptor table.
    } B;
} hw_usdhc_adma_sys_addr_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_ADMA_SYS_ADDR register
 */
#define HW_USDHC_ADMA_SYS_ADDR_ADDR(x)      (REGS_USDHC_BASE(x) + 0x58)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_ADMA_SYS_ADDR(x)           (*(volatile hw_usdhc_adma_sys_addr_t *) HW_USDHC_ADMA_SYS_ADDR_ADDR(x))
#define HW_USDHC_ADMA_SYS_ADDR_RD(x)        (HW_USDHC_ADMA_SYS_ADDR(x).U)
#define HW_USDHC_ADMA_SYS_ADDR_WR(x, v)     (HW_USDHC_ADMA_SYS_ADDR(x).U = (v))
#define HW_USDHC_ADMA_SYS_ADDR_SET(x, v)    (HW_USDHC_ADMA_SYS_ADDR_WR(x, HW_USDHC_ADMA_SYS_ADDR_RD(x) |  (v)))
#define HW_USDHC_ADMA_SYS_ADDR_CLR(x, v)    (HW_USDHC_ADMA_SYS_ADDR_WR(x, HW_USDHC_ADMA_SYS_ADDR_RD(x) & ~(v)))
#define HW_USDHC_ADMA_SYS_ADDR_TOG(x, v)    (HW_USDHC_ADMA_SYS_ADDR_WR(x, HW_USDHC_ADMA_SYS_ADDR_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_ADMA_SYS_ADDR bitfields
 */

/* --- Register HW_USDHC_ADMA_SYS_ADDR, field ADS_ADDR[31:2] (RW)
 *
 * ADMA System Address: This register holds the word address of the executing command in the
 * Descriptor table. At the start of ADMA, the Host Driver shall set the start address of the
 * Descriptor table. The ADMA engine increments this register address whenever fetching a Descriptor
 * command. When the ADMA is stopped at the Block Gap, this register indicates the address of the
 * next executable Descriptor command. When the ADMA Error Interrupt is generated, this register
 * shall hold the valid Descriptor address depending on the ADMA state. The lower 2 bits of this
 * register is tied to '0' so the ADMA address is always word aligned. Since this register supports
 * dynamic address reflecting, when TC bit is set, it automatically alters the value of internal
 * address counter, so SW cannot change this register when TC bit is set. Such restriction is also
 * listed in .
 */

#define BP_USDHC_ADMA_SYS_ADDR_ADS_ADDR      (2)      //!< Bit position for USDHC_ADMA_SYS_ADDR_ADS_ADDR.
#define BM_USDHC_ADMA_SYS_ADDR_ADS_ADDR      (0xfffffffc)  //!< Bit mask for USDHC_ADMA_SYS_ADDR_ADS_ADDR.

//! @brief Get value of USDHC_ADMA_SYS_ADDR_ADS_ADDR from a register value.
#define BG_USDHC_ADMA_SYS_ADDR_ADS_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_ADMA_SYS_ADDR_ADS_ADDR) >> BP_USDHC_ADMA_SYS_ADDR_ADS_ADDR)

//! @brief Format value for bitfield USDHC_ADMA_SYS_ADDR_ADS_ADDR.
#define BF_USDHC_ADMA_SYS_ADDR_ADS_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_ADMA_SYS_ADDR_ADS_ADDR) & BM_USDHC_ADMA_SYS_ADDR_ADS_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the ADS_ADDR field to a new value.
#define BW_USDHC_ADMA_SYS_ADDR_ADS_ADDR(x, v)   (HW_USDHC_ADMA_SYS_ADDR_WR(x, (HW_USDHC_ADMA_SYS_ADDR_RD(x) & ~BM_USDHC_ADMA_SYS_ADDR_ADS_ADDR) | BF_USDHC_ADMA_SYS_ADDR_ADS_ADDR(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_DLL_CTRL - DLL (Delay Line) Control
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_DLL_CTRL - DLL (Delay Line) Control (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains control bits for DLL.
 */
typedef union _hw_usdhc_dll_ctrl
{
    reg32_t U;
    struct _hw_usdhc_dll_ctrl_bitfields
    {
        unsigned DLL_CTRL_ENABLE : 1; //!< [0] Set this bit to 1 to enable the DLL and delay chain; otherwise; set to 0 to bypasses DLL.
        unsigned DLL_CTRL_RESET : 1; //!< [1] Setting this bit to 1 force a reset on DLL.
        unsigned DLL_CTRL_SLV_FORCE_UPD : 1; //!< [2] Setting this bit to 1, forces the slave delay line to update to the DLL calibrated value immediately.
        unsigned DLL_CTRL_SLV_DLY_TARGET : 4; //!< [6:3] The delay target for the uSDHC loopback read clock can be programmed in 1/16th increments of an ref_clock half-period.
        unsigned DLL_CTRL_GATE_UPDATE : 1; //!< [7] Set this bit to 1 to force DLL not update from now on.Since when clock_in exists, glitches might appear during update.
        unsigned DLL_CTRL_SLV_OVERRIDE : 1; //!< [8] Set this bit to 1 to Enable manual override for slave delay chain using SLV_OVERRIDE_VAL; to set 0 to disable manual override.
        unsigned DLL_CTRL_SLV_OVERRIDE_VAL : 7; //!< [15:9] When SLV_OVERRIDE=1 This field is used to select 1 of 128 physical taps manually.
        unsigned DLL_CTRL_SLV_DLY_TARGET1 : 3; //!< [18:16] Refer to DLL_CTRL_SLV_DLY_TARGET[3:0] below.
        unsigned RESERVED0 : 1; //!< [19] Reserved
        unsigned DLL_CTRL_SLV_UPDATE_INT : 8; //!< [27:20] slave delay line update interval.
        unsigned DLL_CTRL_REF_UPDATE_INT : 4; //!< [31:28] DLL control loop update interval.
    } B;
} hw_usdhc_dll_ctrl_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_DLL_CTRL register
 */
#define HW_USDHC_DLL_CTRL_ADDR(x)      (REGS_USDHC_BASE(x) + 0x60)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_DLL_CTRL(x)           (*(volatile hw_usdhc_dll_ctrl_t *) HW_USDHC_DLL_CTRL_ADDR(x))
#define HW_USDHC_DLL_CTRL_RD(x)        (HW_USDHC_DLL_CTRL(x).U)
#define HW_USDHC_DLL_CTRL_WR(x, v)     (HW_USDHC_DLL_CTRL(x).U = (v))
#define HW_USDHC_DLL_CTRL_SET(x, v)    (HW_USDHC_DLL_CTRL_WR(x, HW_USDHC_DLL_CTRL_RD(x) |  (v)))
#define HW_USDHC_DLL_CTRL_CLR(x, v)    (HW_USDHC_DLL_CTRL_WR(x, HW_USDHC_DLL_CTRL_RD(x) & ~(v)))
#define HW_USDHC_DLL_CTRL_TOG(x, v)    (HW_USDHC_DLL_CTRL_WR(x, HW_USDHC_DLL_CTRL_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_DLL_CTRL bitfields
 */

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_ENABLE[0] (RW)
 *
 * Set this bit to 1 to enable the DLL and delay chain; otherwise; set to 0 to bypasses DLL. Note
 * that using the slave delay line override feature with SLV_OVERRIDE and SLV_OVERRIDE VAL, the DLL
 * does not need to be enabled
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_ENABLE      (0)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_ENABLE.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_ENABLE      (0x00000001)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_ENABLE.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_ENABLE from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_ENABLE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_ENABLE) >> BP_USDHC_DLL_CTRL_DLL_CTRL_ENABLE)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_ENABLE.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_ENABLE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_ENABLE) & BM_USDHC_DLL_CTRL_DLL_CTRL_ENABLE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_ENABLE field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_ENABLE(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_ENABLE) | BF_USDHC_DLL_CTRL_DLL_CTRL_ENABLE(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_RESET[1] (RW)
 *
 * Setting this bit to 1 force a reset on DLL. This will cause the DLL to lose lock and re-calibrate
 * to detect an ref_clock half period phase shift. This signal is used by the DLL as edge-sensitive,
 * so in order to create a subsequent reset, RESET must be taken low and then asserted again
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_RESET      (1)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_RESET.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_RESET      (0x00000002)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_RESET.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_RESET from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_RESET(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_RESET) >> BP_USDHC_DLL_CTRL_DLL_CTRL_RESET)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_RESET.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_RESET(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_RESET) & BM_USDHC_DLL_CTRL_DLL_CTRL_RESET)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_RESET field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_RESET(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_RESET) | BF_USDHC_DLL_CTRL_DLL_CTRL_RESET(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_FORCE_UPD[2] (RW)
 *
 * Setting this bit to 1, forces the slave delay line to update to the DLL calibrated value
 * immediately. The slave delay line shall update automatically based on the SLV_UPDATE_INT interval
 * or when a DLL lock condition is sensed. Subsequent forcing of the slave-line update can only
 * occur if SLV_FORCE_UP is set back to 0 and then asserted again (edge triggered). Be sure to use
 * it when uSDHC is idle. This function may not work when uSDHC is working on data/cmd/response.
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD      (2)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD      (0x00000004)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_FORCE_UPD field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_FORCE_UPD(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_DLY_TARGET[6:3] (RW)
 *
 * The delay target for the uSDHC loopback read clock can be programmed in 1/16th increments of an
 * ref_clock half-period. The delay is ((DLL_CTRL_SLV_DLY_TARGET[6:0] +1)* ref_clock/2)/16 So the
 * input read-clock can be delayed relative input data from (ref_clock/2)/16 to ref_clock*4
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET      (3)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET      (0x00000078)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_DLY_TARGET field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_GATE_UPDATE[7] (RW)
 *
 * Set this bit to 1 to force DLL not update from now on.Since when clock_in exists, glitches might
 * appear during update. This bit is used by software if we met such kind of condition. Set it to 0
 * to let DLL update automatically
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE      (7)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE      (0x00000080)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE) >> BP_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE) & BM_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_GATE_UPDATE field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE) | BF_USDHC_DLL_CTRL_DLL_CTRL_GATE_UPDATE(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_OVERRIDE[8] (RW)
 *
 * Set this bit to 1 to Enable manual override for slave delay chain using SLV_OVERRIDE_VAL; to set
 * 0 to disable manual override. This feature does not require the DLL to tbe enabled using the
 * ENABLE bit. In fact to reduce power, if SLV_OVERRIDE is used, it is recommended to disable the
 * DLL with ENABLE=0
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE      (8)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE      (0x00000100)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_OVERRIDE field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_OVERRIDE_VAL[15:9] (RW)
 *
 * When SLV_OVERRIDE=1 This field is used to select 1 of 128 physical taps manually. A value of 0
 * selects tap 1, and a value of 0x7f selects tap 128.
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL      (9)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL      (0x0000fe00)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_OVERRIDE_VAL field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_OVERRIDE_VAL(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_DLY_TARGET1[18:16] (RW)
 *
 * Refer to DLL_CTRL_SLV_DLY_TARGET[3:0] below.
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1      (16)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1      (0x00070000)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1 from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_DLY_TARGET1 field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_DLY_TARGET1(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_SLV_UPDATE_INT[27:20] (RW)
 *
 * slave delay line update interval. If default 0 is used, it means 256 cycles of ref_clock. A value
 * of 0x0f results in 15 cycles and so on. Note that software can always cause an update of the
 * slave-delay line using the SLV_FORCE_UPDATE register. Note that the slave delay line will also
 * update automatically when the reference DLL transitions to a locked state (from an un-locked
 * state).
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT      (20)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT      (0x0ff00000)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT) >> BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT) & BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_SLV_UPDATE_INT field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT) | BF_USDHC_DLL_CTRL_DLL_CTRL_SLV_UPDATE_INT(v)))
#endif

/* --- Register HW_USDHC_DLL_CTRL, field DLL_CTRL_REF_UPDATE_INT[31:28] (RW)
 *
 * DLL control loop update interval. The interval cycle is (2 + REF_UPDATE_INT) * ref_clock. By
 * default, the DLL control loop shall update every two ref_clock cycles. It should be noted that
 * increasing the reference delay-line update interval reduces the ability of the DLL to adjust to
 * fast changes in conditions that may effect the delay (such as voltage and temperature)
 */

#define BP_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT      (28)      //!< Bit position for USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT.
#define BM_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT      (0xf0000000)  //!< Bit mask for USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT.

//! @brief Get value of USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT from a register value.
#define BG_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT) >> BP_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT)

//! @brief Format value for bitfield USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT.
#define BF_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT) & BM_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLL_CTRL_REF_UPDATE_INT field to a new value.
#define BW_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT(x, v)   (HW_USDHC_DLL_CTRL_WR(x, (HW_USDHC_DLL_CTRL_RD(x) & ~BM_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT) | BF_USDHC_DLL_CTRL_DLL_CTRL_REF_UPDATE_INT(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_DLL_STATUS - DLL Status
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_DLL_STATUS - DLL Status (RO)
 *
 * Reset value: 0x00000000
 *
 * This register contains the DLL status information. All bits are read only and will read the same
 * as the power-reset value.
 */
typedef union _hw_usdhc_dll_status
{
    reg32_t U;
    struct _hw_usdhc_dll_status_bitfields
    {
        unsigned DLL_STS_SLV_LOCK : 1; //!< [0] Slave delay-line lock status.
        unsigned DLL_STS_REF_LOCK : 1; //!< [1] Reference DLL lock status.
        unsigned DLL_STS_SLV_SEL : 7; //!< [8:2] Slave delay line select status.
        unsigned DLL_STS_REF_SEL : 7; //!< [15:9] Reference delay line select taps.
        unsigned RESERVED0 : 16; //!< [31:16] Reserved
    } B;
} hw_usdhc_dll_status_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_DLL_STATUS register
 */
#define HW_USDHC_DLL_STATUS_ADDR(x)      (REGS_USDHC_BASE(x) + 0x64)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_DLL_STATUS(x)           (*(volatile hw_usdhc_dll_status_t *) HW_USDHC_DLL_STATUS_ADDR(x))
#define HW_USDHC_DLL_STATUS_RD(x)        (HW_USDHC_DLL_STATUS(x).U)
#endif

/*
 * constants & macros for individual USDHC_DLL_STATUS bitfields
 */

/* --- Register HW_USDHC_DLL_STATUS, field DLL_STS_SLV_LOCK[0] (RO)
 *
 * Slave delay-line lock status. This signifies that a valid calibration has been set to the slave-
 * delay line and that the slave-delay line is implementing the programmed delay value
 */

#define BP_USDHC_DLL_STATUS_DLL_STS_SLV_LOCK      (0)      //!< Bit position for USDHC_DLL_STATUS_DLL_STS_SLV_LOCK.
#define BM_USDHC_DLL_STATUS_DLL_STS_SLV_LOCK      (0x00000001)  //!< Bit mask for USDHC_DLL_STATUS_DLL_STS_SLV_LOCK.

//! @brief Get value of USDHC_DLL_STATUS_DLL_STS_SLV_LOCK from a register value.
#define BG_USDHC_DLL_STATUS_DLL_STS_SLV_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_STATUS_DLL_STS_SLV_LOCK) >> BP_USDHC_DLL_STATUS_DLL_STS_SLV_LOCK)

/* --- Register HW_USDHC_DLL_STATUS, field DLL_STS_REF_LOCK[1] (RO)
 *
 * Reference DLL lock status. This signifies that the DLL has detected and locked to a half-phase
 * ref_clock shift, allowing the slave delay-line to perform programmed clock delays
 */

#define BP_USDHC_DLL_STATUS_DLL_STS_REF_LOCK      (1)      //!< Bit position for USDHC_DLL_STATUS_DLL_STS_REF_LOCK.
#define BM_USDHC_DLL_STATUS_DLL_STS_REF_LOCK      (0x00000002)  //!< Bit mask for USDHC_DLL_STATUS_DLL_STS_REF_LOCK.

//! @brief Get value of USDHC_DLL_STATUS_DLL_STS_REF_LOCK from a register value.
#define BG_USDHC_DLL_STATUS_DLL_STS_REF_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_STATUS_DLL_STS_REF_LOCK) >> BP_USDHC_DLL_STATUS_DLL_STS_REF_LOCK)

/* --- Register HW_USDHC_DLL_STATUS, field DLL_STS_SLV_SEL[8:2] (RO)
 *
 * Slave delay line select status. This is the instant value generated from reference chain. Since
 * only when ref_lock is detected can the reference chain get updated, this value should be the
 * right value next be update to the slave line when reference is locked.
 */

#define BP_USDHC_DLL_STATUS_DLL_STS_SLV_SEL      (2)      //!< Bit position for USDHC_DLL_STATUS_DLL_STS_SLV_SEL.
#define BM_USDHC_DLL_STATUS_DLL_STS_SLV_SEL      (0x000001fc)  //!< Bit mask for USDHC_DLL_STATUS_DLL_STS_SLV_SEL.

//! @brief Get value of USDHC_DLL_STATUS_DLL_STS_SLV_SEL from a register value.
#define BG_USDHC_DLL_STATUS_DLL_STS_SLV_SEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_STATUS_DLL_STS_SLV_SEL) >> BP_USDHC_DLL_STATUS_DLL_STS_SLV_SEL)

/* --- Register HW_USDHC_DLL_STATUS, field DLL_STS_REF_SEL[15:9] (RO)
 *
 * Reference delay line select taps. Be noted this is encoded by 7 bits for 127taps.
 */

#define BP_USDHC_DLL_STATUS_DLL_STS_REF_SEL      (9)      //!< Bit position for USDHC_DLL_STATUS_DLL_STS_REF_SEL.
#define BM_USDHC_DLL_STATUS_DLL_STS_REF_SEL      (0x0000fe00)  //!< Bit mask for USDHC_DLL_STATUS_DLL_STS_REF_SEL.

//! @brief Get value of USDHC_DLL_STATUS_DLL_STS_REF_SEL from a register value.
#define BG_USDHC_DLL_STATUS_DLL_STS_REF_SEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_DLL_STATUS_DLL_STS_REF_SEL) >> BP_USDHC_DLL_STATUS_DLL_STS_REF_SEL)

//-------------------------------------------------------------------------------------------
// HW_USDHC_CLK_TUNE_CTRL_STATUS - CLK Tuning Control and Status
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_CLK_TUNE_CTRL_STATUS - CLK Tuning Control and Status (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains the Clock Tuning Control status information. All bits are read only and
 * will read the same as the power-reset value. This register is added to support SD3.0 UHS-I SDR104
 * mode.
 */
typedef union _hw_usdhc_clk_tune_ctrl_status
{
    reg32_t U;
    struct _hw_usdhc_clk_tune_ctrl_status_bitfields
    {
        unsigned DLY_CELL_SET_POST : 4; //!< [3:0] Set the number of delay cells on the feedback clock between CLK_OUT and CLK_POST.
        unsigned DLY_CELL_SET_OUT : 4; //!< [7:4] Set the number of delay cells on the feedback clock between CLK_PRE and CLK_OUT.
        unsigned DLY_CELL_SET_PRE : 7; //!< [14:8] Set the number of delay cells on the feedback clock between the feedback clock and CLK_PRE.
        unsigned NXT_ERR : 1; //!< [15] NXT error which means the number of delay cells added on the feedback clock is too large.
        unsigned TAP_SEL_POST : 4; //!< [19:16] Reflect the number of delay cells added on the feedback clock between CLK_OUT and CLK_POST.
        unsigned TAP_SEL_OUT : 4; //!< [23:20] Reflect the number of delay cells added on the feedback clock between CLK_PRE and CLK_OUT.
        unsigned TAP_SEL_PRE : 7; //!< [30:24] Reflect the number of delay cells added on the feedback clock between the feedback clock and CLK_PRE.
        unsigned PRE_ERR : 1; //!< [31] PRE error which means the number of delay cells added on the feedback clock is too small.
    } B;
} hw_usdhc_clk_tune_ctrl_status_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_CLK_TUNE_CTRL_STATUS register
 */
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_ADDR(x)      (REGS_USDHC_BASE(x) + 0x68)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_CLK_TUNE_CTRL_STATUS(x)           (*(volatile hw_usdhc_clk_tune_ctrl_status_t *) HW_USDHC_CLK_TUNE_CTRL_STATUS_ADDR(x))
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x)        (HW_USDHC_CLK_TUNE_CTRL_STATUS(x).U)
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, v)     (HW_USDHC_CLK_TUNE_CTRL_STATUS(x).U = (v))
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_SET(x, v)    (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) |  (v)))
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_CLR(x, v)    (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) & ~(v)))
#define HW_USDHC_CLK_TUNE_CTRL_STATUS_TOG(x, v)    (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_CLK_TUNE_CTRL_STATUS bitfields
 */

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field DLY_CELL_SET_POST[3:0] (RW)
 *
 * Set the number of delay cells on the feedback clock between CLK_OUT and CLK_POST.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST      (0)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST      (0x0000000f)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST)

//! @brief Format value for bitfield USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST.
#define BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLY_CELL_SET_POST field to a new value.
#define BW_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST(x, v)   (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, (HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) & ~BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST) | BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_POST(v)))
#endif

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field DLY_CELL_SET_OUT[7:4] (RW)
 *
 * Set the number of delay cells on the feedback clock between CLK_PRE and CLK_OUT.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT      (4)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT      (0x000000f0)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT)

//! @brief Format value for bitfield USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT.
#define BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLY_CELL_SET_OUT field to a new value.
#define BW_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT(x, v)   (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, (HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) & ~BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT) | BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_OUT(v)))
#endif

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field DLY_CELL_SET_PRE[14:8] (RW)
 *
 * Set the number of delay cells on the feedback clock between the feedback clock and CLK_PRE.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE      (8)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE      (0x00007f00)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE)

//! @brief Format value for bitfield USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE.
#define BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE) & BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DLY_CELL_SET_PRE field to a new value.
#define BW_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE(x, v)   (HW_USDHC_CLK_TUNE_CTRL_STATUS_WR(x, (HW_USDHC_CLK_TUNE_CTRL_STATUS_RD(x) & ~BM_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE) | BF_USDHC_CLK_TUNE_CTRL_STATUS_DLY_CELL_SET_PRE(v)))
#endif

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field NXT_ERR[15] (RO)
 *
 * NXT error which means the number of delay cells added on the feedback clock is too large. It's
 * valid only when SMP_CLK_SEL of Mix control register(bit23 of 0x48) is enabled.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR      (15)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR      (0x00008000)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR)

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field TAP_SEL_POST[19:16] (RO)
 *
 * Reflect the number of delay cells added on the feedback clock between CLK_OUT and CLK_POST.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST      (16)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST      (0x000f0000)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_POST)

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field TAP_SEL_OUT[23:20] (RO)
 *
 * Reflect the number of delay cells added on the feedback clock between CLK_PRE and CLK_OUT.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT      (20)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT      (0x00f00000)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_OUT)

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field TAP_SEL_PRE[30:24] (RO)
 *
 * Reflect the number of delay cells added on the feedback clock between the feedback clock and
 * CLK_PRE. When AUTO_TUNE_EN(bit24 of 0x48) is disabled, TAP_SEL_PRE is always equal to
 * DLY_CELL_SET_PRE. When AUTO_TUNE_EN(bit24 of 0x48) is enabled, TAP_SEL_PRE will be updated
 * automatically according to the status of the auto tuning circuit to adjust the sample clock
 * phase.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE      (24)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE      (0x7f000000)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_TAP_SEL_PRE)

/* --- Register HW_USDHC_CLK_TUNE_CTRL_STATUS, field PRE_ERR[31] (RO)
 *
 * PRE error which means the number of delay cells added on the feedback clock is too small. It's
 * valid only when SMP_CLK_SEL of Mix control register(bit23 of 0x48) is enabled.
 */

#define BP_USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR      (31)      //!< Bit position for USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR.
#define BM_USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR      (0x80000000)  //!< Bit mask for USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR.

//! @brief Get value of USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR from a register value.
#define BG_USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR) >> BP_USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR)

//-------------------------------------------------------------------------------------------
// HW_USDHC_VEND_SPEC - Vendor Specific Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_VEND_SPEC - Vendor Specific Register (RW)
 *
 * Reset value: 0x20007809
 *
 * This register contains the vendor specific control/status register.
 */
typedef union _hw_usdhc_vend_spec
{
    reg32_t U;
    struct _hw_usdhc_vend_spec_bitfields
    {
        unsigned EXT_DMA_EN : 1; //!< [0] External DMA Request Enable Enable the request to external DMA.
        unsigned VSELECT : 1; //!< [1] Voltage Selection Change the value of output signal VSELECT, to control the voltage on pads for external card.
        unsigned CONFLICT_CHK_EN : 1; //!< [2] It's not implemented in uSDHC IP.
        unsigned AC12_WR_CHKBUSY_EN : 1; //!< [3] Check busy enable after auto CMD12 for write data packet
        unsigned DAT3_CD_POL : 1; //!< [4] This bit only uses for debugging.
        unsigned CD_POL : 1; //!< [5] This bit only uses for debugging.
        unsigned WP_POL : 1; //!< [6] This bit only uses for debugging.
        unsigned CLKONJ_IN_ABORT : 1; //!< [7] This bit only uses for debugging.
        unsigned FRC_SDCLK_ON : 1; //!< [8] Force CLK output active:
        unsigned AC12_ISNOT_ABORT : 1; //!< [9] This bit only uses for debugging.
        unsigned DDREN_ACT_ATONCE : 1; //!< [10] This bit only uses for debugging.
        unsigned IPG_CLK_SOFT_EN : 1; //!< [11] IPG_CLK software enable
        unsigned HCLK_SOFT_EN : 1; //!< [12] Please note, hardware auto-enables the AHB clock when the internal DMA is enabled even if HCLK_SOFT_EN is 0.
        unsigned IPG_PERCLK_SOFT_EN : 1; //!< [13] ipg_perclk software enable
        unsigned CARD_CLK_SOFT_EN : 1; //!< [14] card clock software enable
        unsigned CRC_CHK_DIS : 1; //!< [15] CRC check disable
        unsigned INT_ST_VAL : 8; //!< [23:16] Internal State Value Internal state value, reflecting the corresponding state value selected by Debug Select field.
        unsigned DBG_SEL : 4; //!< [27:24] Debug Select Select the internal sub-module to show its internal state value.
        unsigned CMD_OE_PRE_EN : 1; //!< [28] Only for debug.
        unsigned AC12_RD_CHKBUSY_EN : 1; //!< [29] Only for debug.
        unsigned CARD_DET_IN_IDLE_ENJ : 1; //!< [30] Only for debug.
        unsigned RESERVED0 : 1; //!< [31] Reserved
    } B;
} hw_usdhc_vend_spec_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_VEND_SPEC register
 */
#define HW_USDHC_VEND_SPEC_ADDR(x)      (REGS_USDHC_BASE(x) + 0xc0)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_VEND_SPEC(x)           (*(volatile hw_usdhc_vend_spec_t *) HW_USDHC_VEND_SPEC_ADDR(x))
#define HW_USDHC_VEND_SPEC_RD(x)        (HW_USDHC_VEND_SPEC(x).U)
#define HW_USDHC_VEND_SPEC_WR(x, v)     (HW_USDHC_VEND_SPEC(x).U = (v))
#define HW_USDHC_VEND_SPEC_SET(x, v)    (HW_USDHC_VEND_SPEC_WR(x, HW_USDHC_VEND_SPEC_RD(x) |  (v)))
#define HW_USDHC_VEND_SPEC_CLR(x, v)    (HW_USDHC_VEND_SPEC_WR(x, HW_USDHC_VEND_SPEC_RD(x) & ~(v)))
#define HW_USDHC_VEND_SPEC_TOG(x, v)    (HW_USDHC_VEND_SPEC_WR(x, HW_USDHC_VEND_SPEC_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_VEND_SPEC bitfields
 */

/* --- Register HW_USDHC_VEND_SPEC, field EXT_DMA_EN[0] (RW)
 *
 * External DMA Request Enable Enable the request to external DMA. When the internal DMA (either
 * Simple DMA or Advanced DMA) is not in use, and this bit is set, uSDHC will send out DMA request
 * when the internal buffer is ready. This bit is particularly useful when transferring data by ARM
 * platform polling mode, and it is not allowed to send out the external DMA request. By default,
 * this bit is set.
 *
 * Values:
 * 0 - In any scenario, uSDHC does not send out external DMA request
 * 1 - When internal DMA is not active, the external DMA request will be sent out
 */

#define BP_USDHC_VEND_SPEC_EXT_DMA_EN      (0)      //!< Bit position for USDHC_VEND_SPEC_EXT_DMA_EN.
#define BM_USDHC_VEND_SPEC_EXT_DMA_EN      (0x00000001)  //!< Bit mask for USDHC_VEND_SPEC_EXT_DMA_EN.

//! @brief Get value of USDHC_VEND_SPEC_EXT_DMA_EN from a register value.
#define BG_USDHC_VEND_SPEC_EXT_DMA_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_EXT_DMA_EN) >> BP_USDHC_VEND_SPEC_EXT_DMA_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_EXT_DMA_EN.
#define BF_USDHC_VEND_SPEC_EXT_DMA_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_EXT_DMA_EN) & BM_USDHC_VEND_SPEC_EXT_DMA_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the EXT_DMA_EN field to a new value.
#define BW_USDHC_VEND_SPEC_EXT_DMA_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_EXT_DMA_EN) | BF_USDHC_VEND_SPEC_EXT_DMA_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field VSELECT[1] (RW)
 *
 * Voltage Selection Change the value of output signal VSELECT, to control the voltage on pads for
 * external card. There must be a control circuit out of uSDHC to change the voltage on pads.
 *
 * Values:
 * 0 - Change the voltage to high voltage range, around 3.0V
 * 1 - Change the voltage to low voltage range, around 1.8V
 */

#define BP_USDHC_VEND_SPEC_VSELECT      (1)      //!< Bit position for USDHC_VEND_SPEC_VSELECT.
#define BM_USDHC_VEND_SPEC_VSELECT      (0x00000002)  //!< Bit mask for USDHC_VEND_SPEC_VSELECT.

//! @brief Get value of USDHC_VEND_SPEC_VSELECT from a register value.
#define BG_USDHC_VEND_SPEC_VSELECT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_VSELECT) >> BP_USDHC_VEND_SPEC_VSELECT)

//! @brief Format value for bitfield USDHC_VEND_SPEC_VSELECT.
#define BF_USDHC_VEND_SPEC_VSELECT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_VSELECT) & BM_USDHC_VEND_SPEC_VSELECT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the VSELECT field to a new value.
#define BW_USDHC_VEND_SPEC_VSELECT(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_VSELECT) | BF_USDHC_VEND_SPEC_VSELECT(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field CONFLICT_CHK_EN[2] (RW)
 *
 * It's not implemented in uSDHC IP. Conflict check enable.
 *
 * Values:
 * 0 - conflict check disable
 * 1 - conflict check enable
 */

#define BP_USDHC_VEND_SPEC_CONFLICT_CHK_EN      (2)      //!< Bit position for USDHC_VEND_SPEC_CONFLICT_CHK_EN.
#define BM_USDHC_VEND_SPEC_CONFLICT_CHK_EN      (0x00000004)  //!< Bit mask for USDHC_VEND_SPEC_CONFLICT_CHK_EN.

//! @brief Get value of USDHC_VEND_SPEC_CONFLICT_CHK_EN from a register value.
#define BG_USDHC_VEND_SPEC_CONFLICT_CHK_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CONFLICT_CHK_EN) >> BP_USDHC_VEND_SPEC_CONFLICT_CHK_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CONFLICT_CHK_EN.
#define BF_USDHC_VEND_SPEC_CONFLICT_CHK_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CONFLICT_CHK_EN) & BM_USDHC_VEND_SPEC_CONFLICT_CHK_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CONFLICT_CHK_EN field to a new value.
#define BW_USDHC_VEND_SPEC_CONFLICT_CHK_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CONFLICT_CHK_EN) | BF_USDHC_VEND_SPEC_CONFLICT_CHK_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field AC12_WR_CHKBUSY_EN[3] (RW)
 *
 * Check busy enable after auto CMD12 for write data packet
 *
 * Values:
 * 0 - Not check busy after auto CMD12 for write data packet
 * 1 - Check busy after auto CMD12 for write data packet
 */

#define BP_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN      (3)      //!< Bit position for USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN.
#define BM_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN      (0x00000008)  //!< Bit mask for USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN.

//! @brief Get value of USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN from a register value.
#define BG_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN) >> BP_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN.
#define BF_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN) & BM_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12_WR_CHKBUSY_EN field to a new value.
#define BW_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN) | BF_USDHC_VEND_SPEC_AC12_WR_CHKBUSY_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field DAT3_CD_POL[4] (RW)
 *
 * This bit only uses for debugging. Polarity of Dat3 pin when it's used as card detection:
 *
 * Values:
 * 0 - card detected when DAT3 is high
 * 1 - card detected when DAT3 is low
 */

#define BP_USDHC_VEND_SPEC_DAT3_CD_POL      (4)      //!< Bit position for USDHC_VEND_SPEC_DAT3_CD_POL.
#define BM_USDHC_VEND_SPEC_DAT3_CD_POL      (0x00000010)  //!< Bit mask for USDHC_VEND_SPEC_DAT3_CD_POL.

//! @brief Get value of USDHC_VEND_SPEC_DAT3_CD_POL from a register value.
#define BG_USDHC_VEND_SPEC_DAT3_CD_POL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_DAT3_CD_POL) >> BP_USDHC_VEND_SPEC_DAT3_CD_POL)

//! @brief Format value for bitfield USDHC_VEND_SPEC_DAT3_CD_POL.
#define BF_USDHC_VEND_SPEC_DAT3_CD_POL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_DAT3_CD_POL) & BM_USDHC_VEND_SPEC_DAT3_CD_POL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DAT3_CD_POL field to a new value.
#define BW_USDHC_VEND_SPEC_DAT3_CD_POL(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_DAT3_CD_POL) | BF_USDHC_VEND_SPEC_DAT3_CD_POL(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field CD_POL[5] (RW)
 *
 * This bit only uses for debugging. Polarity of the CD pin:
 *
 * Values:
 * 0 - CD pin is low active
 * 1 - CD pin is high active
 */

#define BP_USDHC_VEND_SPEC_CD_POL      (5)      //!< Bit position for USDHC_VEND_SPEC_CD_POL.
#define BM_USDHC_VEND_SPEC_CD_POL      (0x00000020)  //!< Bit mask for USDHC_VEND_SPEC_CD_POL.

//! @brief Get value of USDHC_VEND_SPEC_CD_POL from a register value.
#define BG_USDHC_VEND_SPEC_CD_POL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CD_POL) >> BP_USDHC_VEND_SPEC_CD_POL)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CD_POL.
#define BF_USDHC_VEND_SPEC_CD_POL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CD_POL) & BM_USDHC_VEND_SPEC_CD_POL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CD_POL field to a new value.
#define BW_USDHC_VEND_SPEC_CD_POL(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CD_POL) | BF_USDHC_VEND_SPEC_CD_POL(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field WP_POL[6] (RW)
 *
 * This bit only uses for debugging. Polarity of the WP pin:
 *
 * Values:
 * 0 - WP pin is high active
 * 1 - WP pin is low active
 */

#define BP_USDHC_VEND_SPEC_WP_POL      (6)      //!< Bit position for USDHC_VEND_SPEC_WP_POL.
#define BM_USDHC_VEND_SPEC_WP_POL      (0x00000040)  //!< Bit mask for USDHC_VEND_SPEC_WP_POL.

//! @brief Get value of USDHC_VEND_SPEC_WP_POL from a register value.
#define BG_USDHC_VEND_SPEC_WP_POL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_WP_POL) >> BP_USDHC_VEND_SPEC_WP_POL)

//! @brief Format value for bitfield USDHC_VEND_SPEC_WP_POL.
#define BF_USDHC_VEND_SPEC_WP_POL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_WP_POL) & BM_USDHC_VEND_SPEC_WP_POL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WP_POL field to a new value.
#define BW_USDHC_VEND_SPEC_WP_POL(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_WP_POL) | BF_USDHC_VEND_SPEC_WP_POL(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field CLKONJ_IN_ABORT[7] (RW)
 *
 * This bit only uses for debugging. Force CLK output active when sending Abort command:
 *
 * Values:
 * 0 - the CLK output is active when sending abort command while data is transmitting even if the internal
 *     FIFO is full(for read) or empty(for write)
 * 1 - the CLK output is inactive when sending abort command while data is transmitting if the internal
 *     FIFO is full(for read) or empty(for write)
 */

#define BP_USDHC_VEND_SPEC_CLKONJ_IN_ABORT      (7)      //!< Bit position for USDHC_VEND_SPEC_CLKONJ_IN_ABORT.
#define BM_USDHC_VEND_SPEC_CLKONJ_IN_ABORT      (0x00000080)  //!< Bit mask for USDHC_VEND_SPEC_CLKONJ_IN_ABORT.

//! @brief Get value of USDHC_VEND_SPEC_CLKONJ_IN_ABORT from a register value.
#define BG_USDHC_VEND_SPEC_CLKONJ_IN_ABORT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CLKONJ_IN_ABORT) >> BP_USDHC_VEND_SPEC_CLKONJ_IN_ABORT)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CLKONJ_IN_ABORT.
#define BF_USDHC_VEND_SPEC_CLKONJ_IN_ABORT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CLKONJ_IN_ABORT) & BM_USDHC_VEND_SPEC_CLKONJ_IN_ABORT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CLKONJ_IN_ABORT field to a new value.
#define BW_USDHC_VEND_SPEC_CLKONJ_IN_ABORT(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CLKONJ_IN_ABORT) | BF_USDHC_VEND_SPEC_CLKONJ_IN_ABORT(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field FRC_SDCLK_ON[8] (RW)
 *
 * Force CLK output active:
 *
 * Values:
 * 0 - CLK active or inactive is fully controlled by the hardware
 * 1 - force CLK active
 */

#define BP_USDHC_VEND_SPEC_FRC_SDCLK_ON      (8)      //!< Bit position for USDHC_VEND_SPEC_FRC_SDCLK_ON.
#define BM_USDHC_VEND_SPEC_FRC_SDCLK_ON      (0x00000100)  //!< Bit mask for USDHC_VEND_SPEC_FRC_SDCLK_ON.

//! @brief Get value of USDHC_VEND_SPEC_FRC_SDCLK_ON from a register value.
#define BG_USDHC_VEND_SPEC_FRC_SDCLK_ON(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_FRC_SDCLK_ON) >> BP_USDHC_VEND_SPEC_FRC_SDCLK_ON)

//! @brief Format value for bitfield USDHC_VEND_SPEC_FRC_SDCLK_ON.
#define BF_USDHC_VEND_SPEC_FRC_SDCLK_ON(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_FRC_SDCLK_ON) & BM_USDHC_VEND_SPEC_FRC_SDCLK_ON)

#ifndef __LANGUAGE_ASM__
//! @brief Set the FRC_SDCLK_ON field to a new value.
#define BW_USDHC_VEND_SPEC_FRC_SDCLK_ON(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_FRC_SDCLK_ON) | BF_USDHC_VEND_SPEC_FRC_SDCLK_ON(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field AC12_ISNOT_ABORT[9] (RW)
 *
 * This bit only uses for debugging. Auto CMD12 is not a abort command:
 *
 * Values:
 * 0 - Hardware treats the Auto CMD12 as abort command
 * 1 - Hardwae doesn't treat the Auto CMD12 as abort comman
 */

#define BP_USDHC_VEND_SPEC_AC12_ISNOT_ABORT      (9)      //!< Bit position for USDHC_VEND_SPEC_AC12_ISNOT_ABORT.
#define BM_USDHC_VEND_SPEC_AC12_ISNOT_ABORT      (0x00000200)  //!< Bit mask for USDHC_VEND_SPEC_AC12_ISNOT_ABORT.

//! @brief Get value of USDHC_VEND_SPEC_AC12_ISNOT_ABORT from a register value.
#define BG_USDHC_VEND_SPEC_AC12_ISNOT_ABORT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_AC12_ISNOT_ABORT) >> BP_USDHC_VEND_SPEC_AC12_ISNOT_ABORT)

//! @brief Format value for bitfield USDHC_VEND_SPEC_AC12_ISNOT_ABORT.
#define BF_USDHC_VEND_SPEC_AC12_ISNOT_ABORT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_AC12_ISNOT_ABORT) & BM_USDHC_VEND_SPEC_AC12_ISNOT_ABORT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12_ISNOT_ABORT field to a new value.
#define BW_USDHC_VEND_SPEC_AC12_ISNOT_ABORT(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_AC12_ISNOT_ABORT) | BF_USDHC_VEND_SPEC_AC12_ISNOT_ABORT(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field DDREN_ACT_ATONCE[10] (RW)
 *
 * This bit only uses for debugging. DDR_EN setting take active at once:
 *
 * Values:
 * 0 - DDR_EN setting takes active only when the data and cmd line are idle.
 * 1 - DDR_EN setting takes active at once no matter what the state of the data and cmd line are.
 */

#define BP_USDHC_VEND_SPEC_DDREN_ACT_ATONCE      (10)      //!< Bit position for USDHC_VEND_SPEC_DDREN_ACT_ATONCE.
#define BM_USDHC_VEND_SPEC_DDREN_ACT_ATONCE      (0x00000400)  //!< Bit mask for USDHC_VEND_SPEC_DDREN_ACT_ATONCE.

//! @brief Get value of USDHC_VEND_SPEC_DDREN_ACT_ATONCE from a register value.
#define BG_USDHC_VEND_SPEC_DDREN_ACT_ATONCE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_DDREN_ACT_ATONCE) >> BP_USDHC_VEND_SPEC_DDREN_ACT_ATONCE)

//! @brief Format value for bitfield USDHC_VEND_SPEC_DDREN_ACT_ATONCE.
#define BF_USDHC_VEND_SPEC_DDREN_ACT_ATONCE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_DDREN_ACT_ATONCE) & BM_USDHC_VEND_SPEC_DDREN_ACT_ATONCE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DDREN_ACT_ATONCE field to a new value.
#define BW_USDHC_VEND_SPEC_DDREN_ACT_ATONCE(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_DDREN_ACT_ATONCE) | BF_USDHC_VEND_SPEC_DDREN_ACT_ATONCE(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field IPG_CLK_SOFT_EN[11] (RW)
 *
 * IPG_CLK software enable
 *
 * Values:
 * 0 - gate off the IPG_CLK
 * 1 - enable the IPG_CLK
 */

#define BP_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN      (11)      //!< Bit position for USDHC_VEND_SPEC_IPG_CLK_SOFT_EN.
#define BM_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN      (0x00000800)  //!< Bit mask for USDHC_VEND_SPEC_IPG_CLK_SOFT_EN.

//! @brief Get value of USDHC_VEND_SPEC_IPG_CLK_SOFT_EN from a register value.
#define BG_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN) >> BP_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_IPG_CLK_SOFT_EN.
#define BF_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN) & BM_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the IPG_CLK_SOFT_EN field to a new value.
#define BW_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN) | BF_USDHC_VEND_SPEC_IPG_CLK_SOFT_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field HCLK_SOFT_EN[12] (RW)
 *
 * Please note, hardware auto-enables the AHB clock when the internal DMA is enabled even if
 * HCLK_SOFT_EN is 0. AHB clock software enable
 *
 * Values:
 * 0 - gate off the AHB clock.
 * 1 - enable the AHB clock.
 */

#define BP_USDHC_VEND_SPEC_HCLK_SOFT_EN      (12)      //!< Bit position for USDHC_VEND_SPEC_HCLK_SOFT_EN.
#define BM_USDHC_VEND_SPEC_HCLK_SOFT_EN      (0x00001000)  //!< Bit mask for USDHC_VEND_SPEC_HCLK_SOFT_EN.

//! @brief Get value of USDHC_VEND_SPEC_HCLK_SOFT_EN from a register value.
#define BG_USDHC_VEND_SPEC_HCLK_SOFT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_HCLK_SOFT_EN) >> BP_USDHC_VEND_SPEC_HCLK_SOFT_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_HCLK_SOFT_EN.
#define BF_USDHC_VEND_SPEC_HCLK_SOFT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_HCLK_SOFT_EN) & BM_USDHC_VEND_SPEC_HCLK_SOFT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the HCLK_SOFT_EN field to a new value.
#define BW_USDHC_VEND_SPEC_HCLK_SOFT_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_HCLK_SOFT_EN) | BF_USDHC_VEND_SPEC_HCLK_SOFT_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field IPG_PERCLK_SOFT_EN[13] (RW)
 *
 * ipg_perclk software enable
 *
 * Values:
 * 0 - gate off the ipg_perclk
 * 1 - enable the ipg_perclk
 */

#define BP_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN      (13)      //!< Bit position for USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN.
#define BM_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN      (0x00002000)  //!< Bit mask for USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN.

//! @brief Get value of USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN from a register value.
#define BG_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN) >> BP_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN.
#define BF_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN) & BM_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the IPG_PERCLK_SOFT_EN field to a new value.
#define BW_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN) | BF_USDHC_VEND_SPEC_IPG_PERCLK_SOFT_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field CARD_CLK_SOFT_EN[14] (ROO)
 *
 * card clock software enable
 *
 * Values:
 * 0 - gate off the sd_clk
 * 1 - enable the sd_clk
 */

#define BP_USDHC_VEND_SPEC_CARD_CLK_SOFT_EN      (14)      //!< Bit position for USDHC_VEND_SPEC_CARD_CLK_SOFT_EN.
#define BM_USDHC_VEND_SPEC_CARD_CLK_SOFT_EN      (0x00004000)  //!< Bit mask for USDHC_VEND_SPEC_CARD_CLK_SOFT_EN.

//! @brief Get value of USDHC_VEND_SPEC_CARD_CLK_SOFT_EN from a register value.
#define BG_USDHC_VEND_SPEC_CARD_CLK_SOFT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CARD_CLK_SOFT_EN) >> BP_USDHC_VEND_SPEC_CARD_CLK_SOFT_EN)


/* --- Register HW_USDHC_VEND_SPEC, field CRC_CHK_DIS[15] (RW)
 *
 * CRC check disable
 *
 * Values:
 * 0 - check CRC16 for every read data packet and check CRC bits for every write data packet
 * 1 - ignore CRC16 check for every read data packet and ignore CRC bits check for every write data packet
 */

#define BP_USDHC_VEND_SPEC_CRC_CHK_DIS      (15)      //!< Bit position for USDHC_VEND_SPEC_CRC_CHK_DIS.
#define BM_USDHC_VEND_SPEC_CRC_CHK_DIS      (0x00008000)  //!< Bit mask for USDHC_VEND_SPEC_CRC_CHK_DIS.

//! @brief Get value of USDHC_VEND_SPEC_CRC_CHK_DIS from a register value.
#define BG_USDHC_VEND_SPEC_CRC_CHK_DIS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CRC_CHK_DIS) >> BP_USDHC_VEND_SPEC_CRC_CHK_DIS)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CRC_CHK_DIS.
#define BF_USDHC_VEND_SPEC_CRC_CHK_DIS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CRC_CHK_DIS) & BM_USDHC_VEND_SPEC_CRC_CHK_DIS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRC_CHK_DIS field to a new value.
#define BW_USDHC_VEND_SPEC_CRC_CHK_DIS(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CRC_CHK_DIS) | BF_USDHC_VEND_SPEC_CRC_CHK_DIS(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field INT_ST_VAL[23:16] (RO)
 *
 * Internal State Value Internal state value, reflecting the corresponding state value selected by
 * Debug Select field. This field is read-only and write to this field does not have effect.
 */

#define BP_USDHC_VEND_SPEC_INT_ST_VAL      (16)      //!< Bit position for USDHC_VEND_SPEC_INT_ST_VAL.
#define BM_USDHC_VEND_SPEC_INT_ST_VAL      (0x00ff0000)  //!< Bit mask for USDHC_VEND_SPEC_INT_ST_VAL.

//! @brief Get value of USDHC_VEND_SPEC_INT_ST_VAL from a register value.
#define BG_USDHC_VEND_SPEC_INT_ST_VAL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_INT_ST_VAL) >> BP_USDHC_VEND_SPEC_INT_ST_VAL)

/* --- Register HW_USDHC_VEND_SPEC, field DBG_SEL[27:24] (RW)
 *
 * Debug Select Select the internal sub-module to show its internal state value.
 */

#define BP_USDHC_VEND_SPEC_DBG_SEL      (24)      //!< Bit position for USDHC_VEND_SPEC_DBG_SEL.
#define BM_USDHC_VEND_SPEC_DBG_SEL      (0x0f000000)  //!< Bit mask for USDHC_VEND_SPEC_DBG_SEL.

//! @brief Get value of USDHC_VEND_SPEC_DBG_SEL from a register value.
#define BG_USDHC_VEND_SPEC_DBG_SEL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_DBG_SEL) >> BP_USDHC_VEND_SPEC_DBG_SEL)

//! @brief Format value for bitfield USDHC_VEND_SPEC_DBG_SEL.
#define BF_USDHC_VEND_SPEC_DBG_SEL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_DBG_SEL) & BM_USDHC_VEND_SPEC_DBG_SEL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DBG_SEL field to a new value.
#define BW_USDHC_VEND_SPEC_DBG_SEL(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_DBG_SEL) | BF_USDHC_VEND_SPEC_DBG_SEL(v)))
#endif

/* --- Register HW_USDHC_VEND_SPEC, field CMD_OE_PRE_EN[28] (RW)
 *
 * Only for debug. Control the assert point of CMD_OE signal
 *
 * Values:
 * 0 - CMD_OE and CMD_O assert at the same time
 * 1 - CMD_OE asserts one clock cycle before CMD_O
 */

#define BP_USDHC_VEND_SPEC_CMD_OE_PRE_EN      (28)      //!< Bit position for USDHC_VEND_SPEC_CMD_OE_PRE_EN.
#define BM_USDHC_VEND_SPEC_CMD_OE_PRE_EN      (0x10000000)  //!< Bit mask for USDHC_VEND_SPEC_CMD_OE_PRE_EN.

//! @brief Get value of USDHC_VEND_SPEC_CMD_OE_PRE_EN from a register value.
#define BG_USDHC_VEND_SPEC_CMD_OE_PRE_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CMD_OE_PRE_EN) >> BP_USDHC_VEND_SPEC_CMD_OE_PRE_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CMD_OE_PRE_EN.
#define BF_USDHC_VEND_SPEC_CMD_OE_PRE_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CMD_OE_PRE_EN) & BM_USDHC_VEND_SPEC_CMD_OE_PRE_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CMD_OE_PRE_EN field to a new value.
#define BW_USDHC_VEND_SPEC_CMD_OE_PRE_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CMD_OE_PRE_EN) | BF_USDHC_VEND_SPEC_CMD_OE_PRE_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field AC12_RD_CHKBUSY_EN[29] (RW)
 *
 * Only for debug. Auto CMD12 to terminate multi-block read needs to check busy or not
 *
 * Values:
 * 0 - Auto CMD12 to terminate multi-block read doesn't need to check busy
 * 1 - Auto CMD12 to terminate multi-block read needs to check busy
 */

#define BP_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN      (29)      //!< Bit position for USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN.
#define BM_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN      (0x20000000)  //!< Bit mask for USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN.

//! @brief Get value of USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN from a register value.
#define BG_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN) >> BP_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN.
#define BF_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN) & BM_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AC12_RD_CHKBUSY_EN field to a new value.
#define BW_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN) | BF_USDHC_VEND_SPEC_AC12_RD_CHKBUSY_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC, field CARD_DET_IN_IDLE_ENJ[30] (RW)
 *
 * Only for debug. Card detection is only detected during data line idle.
 *
 * Values:
 * 1b - 
 */

#define BP_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ      (30)      //!< Bit position for USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ.
#define BM_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ      (0x40000000)  //!< Bit mask for USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ.

//! @brief Get value of USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ from a register value.
#define BG_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ) >> BP_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ)

//! @brief Format value for bitfield USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ.
#define BF_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ) & BM_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CARD_DET_IN_IDLE_ENJ field to a new value.
#define BW_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ(x, v)   (HW_USDHC_VEND_SPEC_WR(x, (HW_USDHC_VEND_SPEC_RD(x) & ~BM_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ) | BF_USDHC_VEND_SPEC_CARD_DET_IN_IDLE_ENJ(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_MMC_BOOT - MMC Boot Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_MMC_BOOT - MMC Boot Register (RW)
 *
 * Reset value: 0x00000000
 *
 * This register contains the MMC Fast Boot control register.
 */
typedef union _hw_usdhc_mmc_boot
{
    reg32_t U;
    struct _hw_usdhc_mmc_boot_bitfields
    {
        unsigned DTOCV_ACK : 4; //!< [3:0] Boot ACK time out counter value.
        unsigned BOOT_ACK : 1; //!< [4] Boot ack mode select 0: no ack 1: ack
        unsigned BOOT_MODE : 1; //!< [5] Boot mode select 0: normal boot 1: alternative boot
        unsigned BOOT_EN : 1; //!< [6] Boot mode enable 0: fast boot disable 1: fast boot enable
        unsigned AUTO_SABG_EN : 1; //!< [7] When boot, enable auto stop at block gap function.
        unsigned DISABLE_TIME_OUT : 1; //!< [8] Please note, when this bit is set, there is no timeout check no matter boot_en is set or not.
        unsigned RESERVED0 : 7; //!< [15:9] Reserved
        unsigned BOOT_BLK_CNT : 16; //!< [31:16] The value defines the Stop At Block Gap value of automatic mode.
    } B;
} hw_usdhc_mmc_boot_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_MMC_BOOT register
 */
#define HW_USDHC_MMC_BOOT_ADDR(x)      (REGS_USDHC_BASE(x) + 0xc4)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_MMC_BOOT(x)           (*(volatile hw_usdhc_mmc_boot_t *) HW_USDHC_MMC_BOOT_ADDR(x))
#define HW_USDHC_MMC_BOOT_RD(x)        (HW_USDHC_MMC_BOOT(x).U)
#define HW_USDHC_MMC_BOOT_WR(x, v)     (HW_USDHC_MMC_BOOT(x).U = (v))
#define HW_USDHC_MMC_BOOT_SET(x, v)    (HW_USDHC_MMC_BOOT_WR(x, HW_USDHC_MMC_BOOT_RD(x) |  (v)))
#define HW_USDHC_MMC_BOOT_CLR(x, v)    (HW_USDHC_MMC_BOOT_WR(x, HW_USDHC_MMC_BOOT_RD(x) & ~(v)))
#define HW_USDHC_MMC_BOOT_TOG(x, v)    (HW_USDHC_MMC_BOOT_WR(x, HW_USDHC_MMC_BOOT_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_MMC_BOOT bitfields
 */

/* --- Register HW_USDHC_MMC_BOOT, field DTOCV_ACK[3:0] (RW)
 *
 * Boot ACK time out counter value.
 *
 * Values:
 * 0000 - SDCLK x 2^13
 * 0001 - SDCLK x 2^14
 * 0010 - SDCLK x 2^15
 * 0011 - SDCLK x 2^16
 * 0100 - SDCLK x 2^17
 * 0101 - SDCLK x 2^18
 * 0110 - SDCLK x 2^19
 * 0111 - SDCLK x 2^20
 * 1110 - SDCLK x 2^27
 * 1111 - SDCLK x 2^28
 */

#define BP_USDHC_MMC_BOOT_DTOCV_ACK      (0)      //!< Bit position for USDHC_MMC_BOOT_DTOCV_ACK.
#define BM_USDHC_MMC_BOOT_DTOCV_ACK      (0x0000000f)  //!< Bit mask for USDHC_MMC_BOOT_DTOCV_ACK.

//! @brief Get value of USDHC_MMC_BOOT_DTOCV_ACK from a register value.
#define BG_USDHC_MMC_BOOT_DTOCV_ACK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_DTOCV_ACK) >> BP_USDHC_MMC_BOOT_DTOCV_ACK)

//! @brief Format value for bitfield USDHC_MMC_BOOT_DTOCV_ACK.
#define BF_USDHC_MMC_BOOT_DTOCV_ACK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_DTOCV_ACK) & BM_USDHC_MMC_BOOT_DTOCV_ACK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DTOCV_ACK field to a new value.
#define BW_USDHC_MMC_BOOT_DTOCV_ACK(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_DTOCV_ACK) | BF_USDHC_MMC_BOOT_DTOCV_ACK(v)))
#endif


/* --- Register HW_USDHC_MMC_BOOT, field BOOT_ACK[4] (RW)
 *
 * Boot ack mode select 0: no ack 1: ack
 */

#define BP_USDHC_MMC_BOOT_BOOT_ACK      (4)      //!< Bit position for USDHC_MMC_BOOT_BOOT_ACK.
#define BM_USDHC_MMC_BOOT_BOOT_ACK      (0x00000010)  //!< Bit mask for USDHC_MMC_BOOT_BOOT_ACK.

//! @brief Get value of USDHC_MMC_BOOT_BOOT_ACK from a register value.
#define BG_USDHC_MMC_BOOT_BOOT_ACK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_BOOT_ACK) >> BP_USDHC_MMC_BOOT_BOOT_ACK)

//! @brief Format value for bitfield USDHC_MMC_BOOT_BOOT_ACK.
#define BF_USDHC_MMC_BOOT_BOOT_ACK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_BOOT_ACK) & BM_USDHC_MMC_BOOT_BOOT_ACK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BOOT_ACK field to a new value.
#define BW_USDHC_MMC_BOOT_BOOT_ACK(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_BOOT_ACK) | BF_USDHC_MMC_BOOT_BOOT_ACK(v)))
#endif

/* --- Register HW_USDHC_MMC_BOOT, field BOOT_MODE[5] (RW)
 *
 * Boot mode select 0: normal boot 1: alternative boot
 */

#define BP_USDHC_MMC_BOOT_BOOT_MODE      (5)      //!< Bit position for USDHC_MMC_BOOT_BOOT_MODE.
#define BM_USDHC_MMC_BOOT_BOOT_MODE      (0x00000020)  //!< Bit mask for USDHC_MMC_BOOT_BOOT_MODE.

//! @brief Get value of USDHC_MMC_BOOT_BOOT_MODE from a register value.
#define BG_USDHC_MMC_BOOT_BOOT_MODE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_BOOT_MODE) >> BP_USDHC_MMC_BOOT_BOOT_MODE)

//! @brief Format value for bitfield USDHC_MMC_BOOT_BOOT_MODE.
#define BF_USDHC_MMC_BOOT_BOOT_MODE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_BOOT_MODE) & BM_USDHC_MMC_BOOT_BOOT_MODE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BOOT_MODE field to a new value.
#define BW_USDHC_MMC_BOOT_BOOT_MODE(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_BOOT_MODE) | BF_USDHC_MMC_BOOT_BOOT_MODE(v)))
#endif

/* --- Register HW_USDHC_MMC_BOOT, field BOOT_EN[6] (RW)
 *
 * Boot mode enable 0: fast boot disable 1: fast boot enable
 */

#define BP_USDHC_MMC_BOOT_BOOT_EN      (6)      //!< Bit position for USDHC_MMC_BOOT_BOOT_EN.
#define BM_USDHC_MMC_BOOT_BOOT_EN      (0x00000040)  //!< Bit mask for USDHC_MMC_BOOT_BOOT_EN.

//! @brief Get value of USDHC_MMC_BOOT_BOOT_EN from a register value.
#define BG_USDHC_MMC_BOOT_BOOT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_BOOT_EN) >> BP_USDHC_MMC_BOOT_BOOT_EN)

//! @brief Format value for bitfield USDHC_MMC_BOOT_BOOT_EN.
#define BF_USDHC_MMC_BOOT_BOOT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_BOOT_EN) & BM_USDHC_MMC_BOOT_BOOT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BOOT_EN field to a new value.
#define BW_USDHC_MMC_BOOT_BOOT_EN(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_BOOT_EN) | BF_USDHC_MMC_BOOT_BOOT_EN(v)))
#endif

/* --- Register HW_USDHC_MMC_BOOT, field AUTO_SABG_EN[7] (RW)
 *
 * When boot, enable auto stop at block gap function. This function will be triggered, and host will
 * stop at block gap when received card block cnt is equal to (BLK_CNT - BOOT_BLK_CNT).
 */

#define BP_USDHC_MMC_BOOT_AUTO_SABG_EN      (7)      //!< Bit position for USDHC_MMC_BOOT_AUTO_SABG_EN.
#define BM_USDHC_MMC_BOOT_AUTO_SABG_EN      (0x00000080)  //!< Bit mask for USDHC_MMC_BOOT_AUTO_SABG_EN.

//! @brief Get value of USDHC_MMC_BOOT_AUTO_SABG_EN from a register value.
#define BG_USDHC_MMC_BOOT_AUTO_SABG_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_AUTO_SABG_EN) >> BP_USDHC_MMC_BOOT_AUTO_SABG_EN)

//! @brief Format value for bitfield USDHC_MMC_BOOT_AUTO_SABG_EN.
#define BF_USDHC_MMC_BOOT_AUTO_SABG_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_AUTO_SABG_EN) & BM_USDHC_MMC_BOOT_AUTO_SABG_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AUTO_SABG_EN field to a new value.
#define BW_USDHC_MMC_BOOT_AUTO_SABG_EN(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_AUTO_SABG_EN) | BF_USDHC_MMC_BOOT_AUTO_SABG_EN(v)))
#endif

/* --- Register HW_USDHC_MMC_BOOT, field DISABLE_TIME_OUT[8] (RW)
 *
 * Please note, when this bit is set, there is no timeout check no matter boot_en is set or not.
 * Disable time out.
 *
 * Values:
 * 0 - enable time out
 * 1 - Disable time out
 */

#define BP_USDHC_MMC_BOOT_DISABLE_TIME_OUT      (8)      //!< Bit position for USDHC_MMC_BOOT_DISABLE_TIME_OUT.
#define BM_USDHC_MMC_BOOT_DISABLE_TIME_OUT      (0x00000100)  //!< Bit mask for USDHC_MMC_BOOT_DISABLE_TIME_OUT.

//! @brief Get value of USDHC_MMC_BOOT_DISABLE_TIME_OUT from a register value.
#define BG_USDHC_MMC_BOOT_DISABLE_TIME_OUT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_DISABLE_TIME_OUT) >> BP_USDHC_MMC_BOOT_DISABLE_TIME_OUT)

//! @brief Format value for bitfield USDHC_MMC_BOOT_DISABLE_TIME_OUT.
#define BF_USDHC_MMC_BOOT_DISABLE_TIME_OUT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_DISABLE_TIME_OUT) & BM_USDHC_MMC_BOOT_DISABLE_TIME_OUT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DISABLE_TIME_OUT field to a new value.
#define BW_USDHC_MMC_BOOT_DISABLE_TIME_OUT(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_DISABLE_TIME_OUT) | BF_USDHC_MMC_BOOT_DISABLE_TIME_OUT(v)))
#endif


/* --- Register HW_USDHC_MMC_BOOT, field BOOT_BLK_CNT[31:16] (RW)
 *
 * The value defines the Stop At Block Gap value of automatic mode. When received card block cnt is
 * equal to (BLK_CNT - BOOT_BLK_CNT) and AUTO_SABG_EN is 1, then Stop At Block Gap. Here, BLK_CNT is
 * defined in the Block Atrributes Register, bit31-16 of 0x04.
 */

#define BP_USDHC_MMC_BOOT_BOOT_BLK_CNT      (16)      //!< Bit position for USDHC_MMC_BOOT_BOOT_BLK_CNT.
#define BM_USDHC_MMC_BOOT_BOOT_BLK_CNT      (0xffff0000)  //!< Bit mask for USDHC_MMC_BOOT_BOOT_BLK_CNT.

//! @brief Get value of USDHC_MMC_BOOT_BOOT_BLK_CNT from a register value.
#define BG_USDHC_MMC_BOOT_BOOT_BLK_CNT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_MMC_BOOT_BOOT_BLK_CNT) >> BP_USDHC_MMC_BOOT_BOOT_BLK_CNT)

//! @brief Format value for bitfield USDHC_MMC_BOOT_BOOT_BLK_CNT.
#define BF_USDHC_MMC_BOOT_BOOT_BLK_CNT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_MMC_BOOT_BOOT_BLK_CNT) & BM_USDHC_MMC_BOOT_BOOT_BLK_CNT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BOOT_BLK_CNT field to a new value.
#define BW_USDHC_MMC_BOOT_BOOT_BLK_CNT(x, v)   (HW_USDHC_MMC_BOOT_WR(x, (HW_USDHC_MMC_BOOT_RD(x) & ~BM_USDHC_MMC_BOOT_BOOT_BLK_CNT) | BF_USDHC_MMC_BOOT_BOOT_BLK_CNT(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_USDHC_VEND_SPEC2 - Vendor Specific 2 Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_VEND_SPEC2 - Vendor Specific 2 Register (RW)
 *
 * Reset value: 0x00000006
 *
 * This register contains the vendor specific control 2 register.
 */
typedef union _hw_usdhc_vend_spec2
{
    reg32_t U;
    struct _hw_usdhc_vend_spec2_bitfields
    {
        unsigned SDR104_TIMING_DIS : 1; //!< [0] Timeout counter test.
        unsigned SDR104_OE_DIS : 1; //!< [1] CMD_OE/DAT_OE logic generation test.
        unsigned SDR104_NSD_DIS : 1; //!< [2] Interrupt window after abort command is sent.
        unsigned CARD_INT_D3_TEST : 1; //!< [3] Card interrupt detection test.
        unsigned TUNING_8BIT_EN : 1; //!< [4] Enable the auto tuning circuit to check the DAT[7:0].
        unsigned TUNING_1BIT_EN : 1; //!< [5] Enable the auto tuning circuit to check the DAT0 only.
        unsigned TUNING_CMD_EN : 1; //!< [6] Enable the auto tuning circuit to check the CMD line.
        unsigned CARD_INT_AUTO_CLR_DIS : 1; //!< [7] Disable the feature to clear the Card interrupt status bit when Card Interrupt status enable bit is cleared.
        unsigned RESERVED0 : 24; //!< [31:8] Reserved
    } B;
} hw_usdhc_vend_spec2_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_VEND_SPEC2 register
 */
#define HW_USDHC_VEND_SPEC2_ADDR(x)      (REGS_USDHC_BASE(x) + 0xc8)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_VEND_SPEC2(x)           (*(volatile hw_usdhc_vend_spec2_t *) HW_USDHC_VEND_SPEC2_ADDR(x))
#define HW_USDHC_VEND_SPEC2_RD(x)        (HW_USDHC_VEND_SPEC2(x).U)
#define HW_USDHC_VEND_SPEC2_WR(x, v)     (HW_USDHC_VEND_SPEC2(x).U = (v))
#define HW_USDHC_VEND_SPEC2_SET(x, v)    (HW_USDHC_VEND_SPEC2_WR(x, HW_USDHC_VEND_SPEC2_RD(x) |  (v)))
#define HW_USDHC_VEND_SPEC2_CLR(x, v)    (HW_USDHC_VEND_SPEC2_WR(x, HW_USDHC_VEND_SPEC2_RD(x) & ~(v)))
#define HW_USDHC_VEND_SPEC2_TOG(x, v)    (HW_USDHC_VEND_SPEC2_WR(x, HW_USDHC_VEND_SPEC2_RD(x) ^  (v)))
#endif

/*
 * constants & macros for individual USDHC_VEND_SPEC2 bitfields
 */

/* --- Register HW_USDHC_VEND_SPEC2, field SDR104_TIMING_DIS[0] (RW)
 *
 * Timeout counter test. This bit only uses for debugging.
 *
 * Values:
 * 0 - The timeout counter for Ncr changes to 80, Ncrc changes to 21.
 * 1 - The timeout counter for Ncr changes to 72, Ncrc changes to 15.
 */

#define BP_USDHC_VEND_SPEC2_SDR104_TIMING_DIS      (0)      //!< Bit position for USDHC_VEND_SPEC2_SDR104_TIMING_DIS.
#define BM_USDHC_VEND_SPEC2_SDR104_TIMING_DIS      (0x00000001)  //!< Bit mask for USDHC_VEND_SPEC2_SDR104_TIMING_DIS.

//! @brief Get value of USDHC_VEND_SPEC2_SDR104_TIMING_DIS from a register value.
#define BG_USDHC_VEND_SPEC2_SDR104_TIMING_DIS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_SDR104_TIMING_DIS) >> BP_USDHC_VEND_SPEC2_SDR104_TIMING_DIS)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_SDR104_TIMING_DIS.
#define BF_USDHC_VEND_SPEC2_SDR104_TIMING_DIS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_SDR104_TIMING_DIS) & BM_USDHC_VEND_SPEC2_SDR104_TIMING_DIS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SDR104_TIMING_DIS field to a new value.
#define BW_USDHC_VEND_SPEC2_SDR104_TIMING_DIS(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_SDR104_TIMING_DIS) | BF_USDHC_VEND_SPEC2_SDR104_TIMING_DIS(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field SDR104_OE_DIS[1] (RW)
 *
 * CMD_OE/DAT_OE logic generation test. This bit only uses for debugging.
 *
 * Values:
 * 0 - Drive the CMD_OE/DAT_OE for one more clock cycle after the end bit.
 * 1 - Stop to drive the CMD_OE/DAT_OE at once after driving the end bit.
 */

#define BP_USDHC_VEND_SPEC2_SDR104_OE_DIS      (1)      //!< Bit position for USDHC_VEND_SPEC2_SDR104_OE_DIS.
#define BM_USDHC_VEND_SPEC2_SDR104_OE_DIS      (0x00000002)  //!< Bit mask for USDHC_VEND_SPEC2_SDR104_OE_DIS.

//! @brief Get value of USDHC_VEND_SPEC2_SDR104_OE_DIS from a register value.
#define BG_USDHC_VEND_SPEC2_SDR104_OE_DIS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_SDR104_OE_DIS) >> BP_USDHC_VEND_SPEC2_SDR104_OE_DIS)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_SDR104_OE_DIS.
#define BF_USDHC_VEND_SPEC2_SDR104_OE_DIS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_SDR104_OE_DIS) & BM_USDHC_VEND_SPEC2_SDR104_OE_DIS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SDR104_OE_DIS field to a new value.
#define BW_USDHC_VEND_SPEC2_SDR104_OE_DIS(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_SDR104_OE_DIS) | BF_USDHC_VEND_SPEC2_SDR104_OE_DIS(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field SDR104_NSD_DIS[2] (RW)
 *
 * Interrupt window after abort command is sent. This bit only uses for debugging.
 *
 * Values:
 * 0 - Enable the interrupt window 9 cycles later after the end of the I/O abort command(or CMD12) is sent.
 * 1 - Enable the interrupt window 5 cycles later after the end of the I/O abort command(or CMD12) is sent.
 */

#define BP_USDHC_VEND_SPEC2_SDR104_NSD_DIS      (2)      //!< Bit position for USDHC_VEND_SPEC2_SDR104_NSD_DIS.
#define BM_USDHC_VEND_SPEC2_SDR104_NSD_DIS      (0x00000004)  //!< Bit mask for USDHC_VEND_SPEC2_SDR104_NSD_DIS.

//! @brief Get value of USDHC_VEND_SPEC2_SDR104_NSD_DIS from a register value.
#define BG_USDHC_VEND_SPEC2_SDR104_NSD_DIS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_SDR104_NSD_DIS) >> BP_USDHC_VEND_SPEC2_SDR104_NSD_DIS)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_SDR104_NSD_DIS.
#define BF_USDHC_VEND_SPEC2_SDR104_NSD_DIS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_SDR104_NSD_DIS) & BM_USDHC_VEND_SPEC2_SDR104_NSD_DIS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SDR104_NSD_DIS field to a new value.
#define BW_USDHC_VEND_SPEC2_SDR104_NSD_DIS(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_SDR104_NSD_DIS) | BF_USDHC_VEND_SPEC2_SDR104_NSD_DIS(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field CARD_INT_D3_TEST[3] (RW)
 *
 * Card interrupt detection test. This bit only uses for debugging.
 *
 * Values:
 * 0 - Check the card interrupt only when DAT[3] is high.
 * 1 - Check the card interrupt by ignoring the status of DAT[3].
 */

#define BP_USDHC_VEND_SPEC2_CARD_INT_D3_TEST      (3)      //!< Bit position for USDHC_VEND_SPEC2_CARD_INT_D3_TEST.
#define BM_USDHC_VEND_SPEC2_CARD_INT_D3_TEST      (0x00000008)  //!< Bit mask for USDHC_VEND_SPEC2_CARD_INT_D3_TEST.

//! @brief Get value of USDHC_VEND_SPEC2_CARD_INT_D3_TEST from a register value.
#define BG_USDHC_VEND_SPEC2_CARD_INT_D3_TEST(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_CARD_INT_D3_TEST) >> BP_USDHC_VEND_SPEC2_CARD_INT_D3_TEST)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_CARD_INT_D3_TEST.
#define BF_USDHC_VEND_SPEC2_CARD_INT_D3_TEST(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_CARD_INT_D3_TEST) & BM_USDHC_VEND_SPEC2_CARD_INT_D3_TEST)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CARD_INT_D3_TEST field to a new value.
#define BW_USDHC_VEND_SPEC2_CARD_INT_D3_TEST(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_CARD_INT_D3_TEST) | BF_USDHC_VEND_SPEC2_CARD_INT_D3_TEST(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field TUNING_8BIT_EN[4] (RW)
 *
 * Enable the auto tuning circuit to check the DAT[7:0]. It's used with the TUNING_1bit_EN together.
 *
 * Values:
 * 00 - Tuning circuit only checks the DAT[3:0].
 * 01 - Tuning circuit only checks the DAT[0].
 * 10 - Tuning circuit checks the whole DAT[7:0].
 * 11 - Invalid.
 */

#define BP_USDHC_VEND_SPEC2_TUNING_8BIT_EN      (4)      //!< Bit position for USDHC_VEND_SPEC2_TUNING_8BIT_EN.
#define BM_USDHC_VEND_SPEC2_TUNING_8BIT_EN      (0x00000010)  //!< Bit mask for USDHC_VEND_SPEC2_TUNING_8BIT_EN.

//! @brief Get value of USDHC_VEND_SPEC2_TUNING_8BIT_EN from a register value.
#define BG_USDHC_VEND_SPEC2_TUNING_8BIT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_TUNING_8BIT_EN) >> BP_USDHC_VEND_SPEC2_TUNING_8BIT_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_TUNING_8BIT_EN.
#define BF_USDHC_VEND_SPEC2_TUNING_8BIT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_TUNING_8BIT_EN) & BM_USDHC_VEND_SPEC2_TUNING_8BIT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TUNING_8BIT_EN field to a new value.
#define BW_USDHC_VEND_SPEC2_TUNING_8BIT_EN(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_TUNING_8BIT_EN) | BF_USDHC_VEND_SPEC2_TUNING_8BIT_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field TUNING_1BIT_EN[5] (RW)
 *
 * Enable the auto tuning circuit to check the DAT0 only. It's used with the TUNING_8bit_EN
 * together.
 */

#define BP_USDHC_VEND_SPEC2_TUNING_1BIT_EN      (5)      //!< Bit position for USDHC_VEND_SPEC2_TUNING_1BIT_EN.
#define BM_USDHC_VEND_SPEC2_TUNING_1BIT_EN      (0x00000020)  //!< Bit mask for USDHC_VEND_SPEC2_TUNING_1BIT_EN.

//! @brief Get value of USDHC_VEND_SPEC2_TUNING_1BIT_EN from a register value.
#define BG_USDHC_VEND_SPEC2_TUNING_1BIT_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_TUNING_1BIT_EN) >> BP_USDHC_VEND_SPEC2_TUNING_1BIT_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_TUNING_1BIT_EN.
#define BF_USDHC_VEND_SPEC2_TUNING_1BIT_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_TUNING_1BIT_EN) & BM_USDHC_VEND_SPEC2_TUNING_1BIT_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TUNING_1BIT_EN field to a new value.
#define BW_USDHC_VEND_SPEC2_TUNING_1BIT_EN(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_TUNING_1BIT_EN) | BF_USDHC_VEND_SPEC2_TUNING_1BIT_EN(v)))
#endif

/* --- Register HW_USDHC_VEND_SPEC2, field TUNING_CMD_EN[6] (RW)
 *
 * Enable the auto tuning circuit to check the CMD line.
 *
 * Values:
 * 0 - Auto tuning circuit doesn't check the CMD line.
 * 1 - Auto tuning circuit checks the CMD line.
 */

#define BP_USDHC_VEND_SPEC2_TUNING_CMD_EN      (6)      //!< Bit position for USDHC_VEND_SPEC2_TUNING_CMD_EN.
#define BM_USDHC_VEND_SPEC2_TUNING_CMD_EN      (0x00000040)  //!< Bit mask for USDHC_VEND_SPEC2_TUNING_CMD_EN.

//! @brief Get value of USDHC_VEND_SPEC2_TUNING_CMD_EN from a register value.
#define BG_USDHC_VEND_SPEC2_TUNING_CMD_EN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_TUNING_CMD_EN) >> BP_USDHC_VEND_SPEC2_TUNING_CMD_EN)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_TUNING_CMD_EN.
#define BF_USDHC_VEND_SPEC2_TUNING_CMD_EN(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_TUNING_CMD_EN) & BM_USDHC_VEND_SPEC2_TUNING_CMD_EN)

#ifndef __LANGUAGE_ASM__
//! @brief Set the TUNING_CMD_EN field to a new value.
#define BW_USDHC_VEND_SPEC2_TUNING_CMD_EN(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_TUNING_CMD_EN) | BF_USDHC_VEND_SPEC2_TUNING_CMD_EN(v)))
#endif


/* --- Register HW_USDHC_VEND_SPEC2, field CARD_INT_AUTO_CLR_DIS[7] (RW)
 *
 * Disable the feature to clear the Card interrupt status bit when Card Interrupt status enable bit
 * is cleared. This bit only uses for debugging.
 *
 * Values:
 * 0 - Card interrupt status bit(CINT) can be cleared when Card Interrupt status enable bit is 0.
 * 1 - Card interrupt status bit(CINT) can only be cleared by written-1 to CINT bit.
 */

#define BP_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS      (7)      //!< Bit position for USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS.
#define BM_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS      (0x00000080)  //!< Bit mask for USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS.

//! @brief Get value of USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS from a register value.
#define BG_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS) >> BP_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS)

//! @brief Format value for bitfield USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS.
#define BF_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS) & BM_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CARD_INT_AUTO_CLR_DIS field to a new value.
#define BW_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS(x, v)   (HW_USDHC_VEND_SPEC2_WR(x, (HW_USDHC_VEND_SPEC2_RD(x) & ~BM_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS) | BF_USDHC_VEND_SPEC2_CARD_INT_AUTO_CLR_DIS(v)))
#endif


//-------------------------------------------------------------------------------------------
// HW_USDHC_HOST_CTRL_VER - Host Controller Version
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_USDHC_HOST_CTRL_VER - Host Controller Version (RO)
 *
 * Reset value: 0x00000003
 *
 * This register contains the vendor Host Controller version information. All bits are read only and
 * will read the same as the power-reset value.
 */
typedef union _hw_usdhc_host_ctrl_ver
{
    reg32_t U;
    struct _hw_usdhc_host_ctrl_ver_bitfields
    {
        unsigned SVN : 8; //!< [7:0] Specification Version Number: These status bits indicate the Host Controller Specification Version.
        unsigned VVN : 8; //!< [15:8] Vendor Version Number: These status bits are reserved for the vendor version number.
        unsigned RESERVED0 : 16; //!< [31:16] Reserved
    } B;
} hw_usdhc_host_ctrl_ver_t;
#endif

/*
 * constants & macros for entire multi-block USDHC_HOST_CTRL_VER register
 */
#define HW_USDHC_HOST_CTRL_VER_ADDR(x)      (REGS_USDHC_BASE(x) + 0xfc)

#ifndef __LANGUAGE_ASM__
#define HW_USDHC_HOST_CTRL_VER(x)           (*(volatile hw_usdhc_host_ctrl_ver_t *) HW_USDHC_HOST_CTRL_VER_ADDR(x))
#define HW_USDHC_HOST_CTRL_VER_RD(x)        (HW_USDHC_HOST_CTRL_VER(x).U)
#endif

/*
 * constants & macros for individual USDHC_HOST_CTRL_VER bitfields
 */

/* --- Register HW_USDHC_HOST_CTRL_VER, field SVN[7:0] (RO)
 *
 * Specification Version Number: These status bits indicate the Host Controller Specification
 * Version. 00 SD Host Specification Version 1.0 03 SD Host Specification Version 3.0, supports Test
 * Event Register and ADMA. All others) Reserved
 */

#define BP_USDHC_HOST_CTRL_VER_SVN      (0)      //!< Bit position for USDHC_HOST_CTRL_VER_SVN.
#define BM_USDHC_HOST_CTRL_VER_SVN      (0x000000ff)  //!< Bit mask for USDHC_HOST_CTRL_VER_SVN.

//! @brief Get value of USDHC_HOST_CTRL_VER_SVN from a register value.
#define BG_USDHC_HOST_CTRL_VER_SVN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_VER_SVN) >> BP_USDHC_HOST_CTRL_VER_SVN)

/* --- Register HW_USDHC_HOST_CTRL_VER, field VVN[15:8] (RO)
 *
 * Vendor Version Number: These status bits are reserved for the vendor version number. The Host
 * Driver shall not use this status. 01 Freescale uSDHC Version 1.1 others) Reserved
 */

#define BP_USDHC_HOST_CTRL_VER_VVN      (8)      //!< Bit position for USDHC_HOST_CTRL_VER_VVN.
#define BM_USDHC_HOST_CTRL_VER_VVN      (0x0000ff00)  //!< Bit mask for USDHC_HOST_CTRL_VER_VVN.

//! @brief Get value of USDHC_HOST_CTRL_VER_VVN from a register value.
#define BG_USDHC_HOST_CTRL_VER_VVN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_USDHC_HOST_CTRL_VER_VVN) >> BP_USDHC_HOST_CTRL_VER_VVN)


/*!
 * @brief All USDHC module registers.
 */
#ifndef __LANGUAGE_ASM__
#pragma pack(1)
typedef struct _hw_usdhc
{
    volatile hw_usdhc_ds_addr_t DS_ADDR; //!< DMA System Address
    volatile hw_usdhc_blk_att_t BLK_ATT; //!< Block Attributes
    volatile hw_usdhc_cmd_arg_t CMD_ARG; //!< Command Argument
    volatile hw_usdhc_cmd_xfr_typ_t CMD_XFR_TYP; //!< Command Transfer Type
    volatile hw_usdhc_cmd_rsp0_t CMD_RSP0; //!< Command Response0
    volatile hw_usdhc_cmd_rsp1_t CMD_RSP1; //!< Command Response1
    volatile hw_usdhc_cmd_rsp2_t CMD_RSP2; //!< Command Response2
    volatile hw_usdhc_cmd_rsp3_t CMD_RSP3; //!< Command Response3
    volatile hw_usdhc_data_buff_acc_port_t DATA_BUFF_ACC_PORT; //!< Data Buffer Access Port
    volatile hw_usdhc_pres_state_t PRES_STATE; //!< Present State
    volatile hw_usdhc_prot_ctrl_t PROT_CTRL; //!< Protocol Control
    volatile hw_usdhc_sys_ctrl_t SYS_CTRL; //!< System Control
    volatile hw_usdhc_int_status_t INT_STATUS; //!< Interrupt Status
    volatile hw_usdhc_int_status_en_t INT_STATUS_EN; //!< Interrupt Status Enable
    volatile hw_usdhc_int_signal_en_t INT_SIGNAL_EN; //!< Interrupt Signal Enable
    volatile hw_usdhc_autocmd12_err_status_t AUTOCMD12_ERR_STATUS; //!< Auto CMD12 Error Status
    volatile hw_usdhc_host_ctrl_cap_t HOST_CTRL_CAP; //!< Host Controller Capabilities
    volatile hw_usdhc_wtmk_lvl_t WTMK_LVL; //!< Watermark Level
    volatile hw_usdhc_mix_ctrl_t MIX_CTRL; //!< Mixer Control
    reg32_t _reserved0;
    volatile hw_usdhc_force_event_t FORCE_EVENT; //!< Force Event
    volatile hw_usdhc_adma_err_status_t ADMA_ERR_STATUS; //!< ADMA Error Status Register
    volatile hw_usdhc_adma_sys_addr_t ADMA_SYS_ADDR; //!< ADMA System Address
    reg32_t _reserved1;
    volatile hw_usdhc_dll_ctrl_t DLL_CTRL; //!< DLL (Delay Line) Control
    volatile hw_usdhc_dll_status_t DLL_STATUS; //!< DLL Status
    volatile hw_usdhc_clk_tune_ctrl_status_t CLK_TUNE_CTRL_STATUS; //!< CLK Tuning Control and Status
    reg32_t _reserved2[21];
    volatile hw_usdhc_vend_spec_t VEND_SPEC; //!< Vendor Specific Register
    volatile hw_usdhc_mmc_boot_t MMC_BOOT; //!< MMC Boot Register
    volatile hw_usdhc_vend_spec2_t VEND_SPEC2; //!< Vendor Specific 2 Register
    reg32_t _reserved3[12];
    volatile hw_usdhc_host_ctrl_ver_t HOST_CTRL_VER; //!< Host Controller Version
} hw_usdhc_t;
#pragma pack()

//! @brief Macro to access all USDHC registers.
//! @param x USDHC instance number.
//! @return Reference (not a pointer) to the registers struct. To get a pointer to the struct,
//!     use the '&' operator, like <code>&HW_USDHC(0)</code>.
#define HW_USDHC(x)     (*(volatile hw_usdhc_t *) REGS_USDHC_BASE(x))

#endif


#endif // __HW_USDHC_REGISTERS_H__
