/*
 * Copyright (C) 2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
 */

#ifndef __HW_OCOTP_REGISTERS_H__
#define __HW_OCOTP_REGISTERS_H__

#include "regs.h"

/*
 * i.MX6UL OCOTP registers defined in this header file.
 *
 * - HW_OCOTP_CTRL - OTP Controller Control Register
 * - HW_OCOTP_TIMING - OTP Controller Timing Register
 * - HW_OCOTP_DATA - OTP Controller Write Data Register
 * - HW_OCOTP_READ_CTRL - OTP Controller Write Data Register
 * - HW_OCOTP_READ_FUSE_DATA - OTP Controller Read Data Register
 * - HW_OCOTP_SW_STICKY - Sticky bit Register
 * - HW_OCOTP_SCS - Software Controllable Signals Register
 * - HW_OCOTP_CRC_ADDR - OTP Controller CRC test address
 * - HW_OCOTP_CRC_VALUE - OTP Controller CRC Value Register
 * - HW_OCOTP_VERSION - OTP Controller Version Register
 * - HW_OCOTP_LOCK - Value of OTP Bank0 Word0 (Lock controls)
 * - HW_OCOTP_CFG0 - Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG1 - Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG2 - Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG3 - Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG4 - Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG5 - Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_CFG6 - Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.)
 * - HW_OCOTP_MEM0 - Value of OTP Bank1 Word0 (Memory Related Info.)
 * - HW_OCOTP_MEM1 - Value of OTP Bank1 Word1 (Memory Related Info.)
 * - HW_OCOTP_MEM2 - Value of OTP Bank1 Word2 (Memory Related Info.)
 * - HW_OCOTP_MEM3 - Value of OTP Bank1 Word3 (Memory Related Info.)
 * - HW_OCOTP_MEM4 - Value of OTP Bank1 Word4 (Memory Related Info.)
 * - HW_OCOTP_ANA0 - Value of OTP Bank1 Word5 (Memory Related Info.)
 * - HW_OCOTP_ANA1 - Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.)
 * - HW_OCOTP_ANA2 - Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.)
 * - HW_OCOTP_OTPMK0 - Shadow Register for OTP Bank2 Word0 (OTPMK and CRYPTO Key)
 * - HW_OCOTP_OTPMK1 - Shadow Register for OTP Bank2 Word1 (OTPMK and CRYPTO Key)
 * - HW_OCOTP_OTPMK2 - Shadow Register for OTP Bank2 Word2 (OTPMK and CRYPTO Key)
 * - HW_OCOTP_OTPMK3 - Shadow Register for OTP Bank2 Word3 (OTPMK and CRYPTO Key)
 * - HW_OCOTP_OTPMK4 - Shadow Register for OTP Bank2 Word4 (OTPMK Key)
 * - HW_OCOTP_OTPMK5 - Shadow Register for OTP Bank2 Word5 (OTPMK Key)
 * - HW_OCOTP_OTPMK6 - Shadow Register for OTP Bank2 Word6 (OTPMK Key)
 * - HW_OCOTP_OTPMK7 - Shadow Register for OTP Bank2 Word7 (OTPMK Key)
 * - HW_OCOTP_SRK0 - Shadow Register for OTP Bank3 Word0 (SRK Hash)
 * - HW_OCOTP_SRK1 - Shadow Register for OTP Bank3 Word1 (SRK Hash)
 * - HW_OCOTP_SRK2 - Shadow Register for OTP Bank3 Word2 (SRK Hash)
 * - HW_OCOTP_SRK3 - Shadow Register for OTP Bank3 Word3 (SRK Hash)
 * - HW_OCOTP_SRK4 - Shadow Register for OTP Bank3 Word4 (SRK Hash)
 * - HW_OCOTP_SRK5 - Shadow Register for OTP Bank3 Word5 (SRK Hash)
 * - HW_OCOTP_SRK6 - Shadow Register for OTP Bank3 Word6 (SRK Hash)
 * - HW_OCOTP_SRK7 - Shadow Register for OTP Bank3 Word7 (SRK Hash)
 * - HW_OCOTP_RESP0 - Value of OTP Bank4 Word0 (Secure JTAG Response Field)
 * - HW_OCOTP_HSJC_RESP1 - Value of OTP Bank4 Word1 (Secure JTAG Response Field)
 * - HW_OCOTP_MAC0 - Value of OTP Bank4 Word2 (MAC Address)
 * - HW_OCOTP_MAC1 - Value of OTP Bank4 Word3 (MAC Address)
 * - HW_OCOTP_HDCP_KSV0 - Value of OTP Bank4 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KSV1 - Value of OTP Bank4 Word5 (HW Capabilities)
 * - HW_OCOTP_GP1 - Value of OTP Bank4 Word6 (HW Capabilities)
 * - HW_OCOTP_GP2 - Value of OTP Bank4 Word7 (HW Capabilities)
 * - HW_OCOTP_DTCP_KEY0 - Value of OTP Bank5 Word0 (HW Capabilities)
 * - HW_OCOTP_DTCP_KEY1 - Value of OTP Bank5 Word1 (HW Capabilities)
 * - HW_OCOTP_DTCP_KEY2 - Value of OTP Bank5 Word2 (HW Capabilities)
 * - HW_OCOTP_DTCP_KEY3 - Value of OTP Bank5 Word3 (HW Capabilities)
 * - HW_OCOTP_DTCP_KEY4 - Value of OTP Bank5 Word4 (HW Capabilities)
 * - HW_OCOTP_MISC_CONF - Value of OTP Bank5 Word5 (HW Capabilities)
 * - HW_OCOTP_FIELD_RETURN - Value of OTP Bank5 Word6 (HW Capabilities)
 * - HW_OCOTP_SRK_REVOKE - Value of OTP Bank5 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY0 - Value of OTP Bank6 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY1 - Value of OTP Bank6 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY2 - Value of OTP Bank6 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY3 - Value of OTP Bank6 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY4 - Value of OTP Bank6 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY5 - Value of OTP Bank6 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY6 - Value of OTP Bank6 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY7 - Value of OTP Bank6 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY8 - Value of OTP Bank7 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY9 - Value of OTP Bank7 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY10 - Value of OTP Bank7 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY11 - Value of OTP Bank7 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY12 - Value of OTP Bank7 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY13 - Value of OTP Bank7 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY14 - Value of OTP Bank7 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY15 - Value of OTP Bank7 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY16 - Value of OTP Bank8 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY17 - Value of OTP Bank8 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY18 - Value of OTP Bank8 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY19 - Value of OTP Bank8 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY20 - Value of OTP Bank8 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY21 - Value of OTP Bank8 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY22 - Value of OTP Bank8 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY23 - Value of OTP Bank8 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY24 - Value of OTP Bank9 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY25 - Value of OTP Bank9 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY26 - Value of OTP Bank9 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY27 - Value of OTP Bank9 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY28 - Value of OTP Bank9 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY29 - Value of OTP Bank9 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY30 - Value of OTP Bank9 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY31 - Value of OTP Bank9 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY32 - Value of OTP Bank10 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY33 - Value of OTP Bank10 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY34 - Value of OTP Bank10 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY35 - Value of OTP Bank10 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY36 - Value of OTP Bank10 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY37 - Value of OTP Bank10 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY38 - Value of OTP Bank10 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY39 - Value of OTP Bank10 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY40 - Value of OTP Bank11 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY41 - Value of OTP Bank11 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY42 - Value of OTP Bank11 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY43 - Value of OTP Bank11 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY44 - Value of OTP Bank11 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY45 - Value of OTP Bank11 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY46 - Value of OTP Bank11 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY47 - Value of OTP Bank11 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY48 - Value of OTP Bank12 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY49 - Value of OTP Bank12 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY50 - Value of OTP Bank12 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY51 - Value of OTP Bank12 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY52 - Value of OTP Bank12 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY53 - Value of OTP Bank12 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY54 - Value of OTP Bank12 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY55 - Value of OTP Bank12 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY56 - Value of OTP Bank13 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY57 - Value of OTP Bank13 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY58 - Value of OTP Bank13 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY59 - Value of OTP Bank13 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY60 - Value of OTP Bank13 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY61 - Value of OTP Bank13 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY62 - Value of OTP Bank13 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY63 - Value of OTP Bank13 Word7 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY64 - Value of OTP Bank14 Word0 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY65 - Value of OTP Bank14 Word1 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY66 - Value of OTP Bank14 Word2 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY67 - Value of OTP Bank14 Word3 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY68 - Value of OTP Bank14 Word4 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY69 - Value of OTP Bank14 Word5 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY70 - Value of OTP Bank14 Word6 (HW Capabilities)
 * - HW_OCOTP_HDCP_KEY71 - Value of OTP Bank14 Word7 (HW Capabilities)
 * - HW_OCOTP_CRC0 - Value of OTP Bank15 Word0 (HW Capabilities)
 * - HW_OCOTP_CRC1 - Value of OTP Bank15 Word1 (HW Capabilities)
 * - HW_OCOTP_CRC2 - Value of OTP Bank15 Word2 (HW Capabilities)
 * - HW_OCOTP_CRC3 - Value of OTP Bank15 Word3 (HW Capabilities)
 * - HW_OCOTP_CRC4 - Value of OTP Bank15 Word4 (HW Capabilities)
 * - HW_OCOTP_CRC5 - Value of OTP Bank15 Word5 (HW Capabilities)
 * - HW_OCOTP_CRC6 - Value of OTP Bank15 Word6 (HW Capabilities)
 * - HW_OCOTP_CRC7 - Value of OTP Bank15 Word5 (HW Capabilities)
 *
 * - hw_ocotp_t - Struct containing all module registers.
 */

//! @name Module base addresses
//@{
#ifndef REGS_OCOTP_BASE
#define HW_OCOTP_INSTANCE_COUNT (1) //!< Number of instances of the OCOTP module.
#define REGS_OCOTP_BASE (0x021bc000) //!< Base address for OCOTP.
#endif
//@}


//-------------------------------------------------------------------------------------------
// HW_OCOTP_CTRL - OTP Controller Control Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CTRL - OTP Controller Control Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Control and Status Register specifies the copy state, as well as the control required
 * for random access of the OTP memory  OCOTP_CTRL: 0x000  The OCOTP Control and Status Register
 * provides the necessary software interface for performing read and write operations to the On-Chip
 * OTP (One-Time Programmable ROM). The control fields such as WR_UNLOCK, ADDR and BUSY/ERROR may be
 * used in conjuction with the HW_OCOTP_DATA register to perform write operations. Read operations
 * to the On-Chip OTP are involving ADDR, BUSY/ERROR bit field and HW_OCOTP_READ_CTRL register. Read
 * value is saved in HW_OCOTP_READ_FUSE_DATA register.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_ctrl
{
    reg32_t U;
    struct _hw_ocotp_ctrl_bitfields
    {
        unsigned ADDR : 7; //!< [6:0] OTP write and read access address register.
        unsigned RESERVED0 : 1; //!< [7] Reserved
        unsigned BUSY : 1; //!< [8] OTP controller status bit.
        unsigned ERROR : 1; //!< [9] Set by the controller when an access to a locked region(OTP or shadow register) is requested.
        unsigned RELOAD_SHADOWS : 1; //!< [10] Set to force re-loading the shadow registers (HW/SW capability and LOCK).
        unsigned CRC_TEST : 1; //!< [11] Set to calculate CRC according to start address and end address in CRC_ADDR register.And compare with CRC fuse word according CRC address in CRC_ADDR register to generate CRC_FAIL flag
        unsigned CRC_FAIL : 1; //!< [12] Set by controller when calculated CRC value is not equal to appointed CRC fuse word
        unsigned RESERVED1 : 3; //!< [15:13] Reserved
        unsigned WR_UNLOCK : 16; //!< [31:16] Write 0x3E77 to enable OTP write accesses.
    } B;
} hw_ocotp_ctrl_t;
#endif

/*
 * constants & macros for entire OCOTP_CTRL register
 */
#define HW_OCOTP_CTRL_ADDR      (REGS_OCOTP_BASE + 0x0)
#define HW_OCOTP_CTRL_SET_ADDR  (HW_OCOTP_CTRL_ADDR + 0x4)
#define HW_OCOTP_CTRL_CLR_ADDR  (HW_OCOTP_CTRL_ADDR + 0x8)
#define HW_OCOTP_CTRL_TOG_ADDR  (HW_OCOTP_CTRL_ADDR + 0xC)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CTRL           (*(volatile hw_ocotp_ctrl_t *) HW_OCOTP_CTRL_ADDR)
#define HW_OCOTP_CTRL_RD()      (HW_OCOTP_CTRL.U)
#define HW_OCOTP_CTRL_WR(v)     (HW_OCOTP_CTRL.U = (v))
#define HW_OCOTP_CTRL_SET(v)    ((*(volatile reg32_t *) HW_OCOTP_CTRL_SET_ADDR) = (v))
#define HW_OCOTP_CTRL_CLR(v)    ((*(volatile reg32_t *) HW_OCOTP_CTRL_CLR_ADDR) = (v))
#define HW_OCOTP_CTRL_TOG(v)    ((*(volatile reg32_t *) HW_OCOTP_CTRL_TOG_ADDR) = (v))
#endif

/*
 * constants & macros for individual OCOTP_CTRL bitfields
 */

/* --- Register HW_OCOTP_CTRL, field ADDR[6:0] (RW)
 *
 * OTP write and read access address register. Specifies one of 128 word address locations (0x00 -
 * 0x7f). If a valid access is accepted by the controller, the controller makes an internal copy of
 * this value. This internal copy will not update until the access is complete.
 */

#define BP_OCOTP_CTRL_ADDR      (0)      //!< Bit position for OCOTP_CTRL_ADDR.
#define BM_OCOTP_CTRL_ADDR      (0x0000007f)  //!< Bit mask for OCOTP_CTRL_ADDR.

//! @brief Get value of OCOTP_CTRL_ADDR from a register value.
#define BG_OCOTP_CTRL_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_ADDR) >> BP_OCOTP_CTRL_ADDR)

//! @brief Format value for bitfield OCOTP_CTRL_ADDR.
#define BF_OCOTP_CTRL_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_ADDR) & BM_OCOTP_CTRL_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the ADDR field to a new value.
#define BW_OCOTP_CTRL_ADDR(v)   BF_CS1(OCOTP_CTRL, ADDR, v)
#endif

/* --- Register HW_OCOTP_CTRL, field BUSY[8] (RO)
 *
 * OTP controller status bit. When active, no new write access or read access to OTP(including
 * RELOAD_SHADOWS) can be performed. Cleared by controller when access complete. After reset (or
 * after setting RELOAD_SHADOWS), this bit is set by the controller until the HW/SW and LOCK
 * registers are successfully copied, after which time it is automatically cleared by the
 * controller.
 */

#define BP_OCOTP_CTRL_BUSY      (8)      //!< Bit position for OCOTP_CTRL_BUSY.
#define BM_OCOTP_CTRL_BUSY      (0x00000100)  //!< Bit mask for OCOTP_CTRL_BUSY.

//! @brief Get value of OCOTP_CTRL_BUSY from a register value.
#define BG_OCOTP_CTRL_BUSY(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_BUSY) >> BP_OCOTP_CTRL_BUSY)

/* --- Register HW_OCOTP_CTRL, field ERROR[9] (RW)
 *
 * Set by the controller when an access to a locked region(OTP or shadow register) is requested.
 * Must be cleared before any further access can be performed. This bit can only be set by the
 * controller. This bit is also set if the Pin interface is active and software requests an access
 * to the OTP. In this instance, the ERROR bit cannot be cleared until the Pin interface access has
 * completed. Reset this bit by writing a one to the SCT clear address space and not by a general
 * write.
 */

#define BP_OCOTP_CTRL_ERROR      (9)      //!< Bit position for OCOTP_CTRL_ERROR.
#define BM_OCOTP_CTRL_ERROR      (0x00000200)  //!< Bit mask for OCOTP_CTRL_ERROR.

//! @brief Get value of OCOTP_CTRL_ERROR from a register value.
#define BG_OCOTP_CTRL_ERROR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_ERROR) >> BP_OCOTP_CTRL_ERROR)

//! @brief Format value for bitfield OCOTP_CTRL_ERROR.
#define BF_OCOTP_CTRL_ERROR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_ERROR) & BM_OCOTP_CTRL_ERROR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the ERROR field to a new value.
#define BW_OCOTP_CTRL_ERROR(v)   BF_CS1(OCOTP_CTRL, ERROR, v)
#endif

/* --- Register HW_OCOTP_CTRL, field RELOAD_SHADOWS[10] (RW)
 *
 * Set to force re-loading the shadow registers (HW/SW capability and LOCK). This operation will
 * automatically set BUSY. Once the shadow registers have been re-loaded, BUSY and RELOAD_SHADOWS
 * are automatically cleared by the controller.
 */

#define BP_OCOTP_CTRL_RELOAD_SHADOWS      (10)      //!< Bit position for OCOTP_CTRL_RELOAD_SHADOWS.
#define BM_OCOTP_CTRL_RELOAD_SHADOWS      (0x00000400)  //!< Bit mask for OCOTP_CTRL_RELOAD_SHADOWS.

//! @brief Get value of OCOTP_CTRL_RELOAD_SHADOWS from a register value.
#define BG_OCOTP_CTRL_RELOAD_SHADOWS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_RELOAD_SHADOWS) >> BP_OCOTP_CTRL_RELOAD_SHADOWS)

//! @brief Format value for bitfield OCOTP_CTRL_RELOAD_SHADOWS.
#define BF_OCOTP_CTRL_RELOAD_SHADOWS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_RELOAD_SHADOWS) & BM_OCOTP_CTRL_RELOAD_SHADOWS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RELOAD_SHADOWS field to a new value.
#define BW_OCOTP_CTRL_RELOAD_SHADOWS(v)   BF_CS1(OCOTP_CTRL, RELOAD_SHADOWS, v)
#endif

/* --- Register HW_OCOTP_CTRL, field CRC_TEST[11] (RW)
 *
 * Set to calculate CRC according to start address and end address in CRC_ADDR register.And compare
 * with CRC fuse word according CRC address in CRC_ADDR register to generate CRC_FAIL flag
 */

#define BP_OCOTP_CTRL_CRC_TEST      (11)      //!< Bit position for OCOTP_CTRL_CRC_TEST.
#define BM_OCOTP_CTRL_CRC_TEST      (0x00000800)  //!< Bit mask for OCOTP_CTRL_CRC_TEST.

//! @brief Get value of OCOTP_CTRL_CRC_TEST from a register value.
#define BG_OCOTP_CTRL_CRC_TEST(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_CRC_TEST) >> BP_OCOTP_CTRL_CRC_TEST)

//! @brief Format value for bitfield OCOTP_CTRL_CRC_TEST.
#define BF_OCOTP_CTRL_CRC_TEST(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_CRC_TEST) & BM_OCOTP_CTRL_CRC_TEST)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRC_TEST field to a new value.
#define BW_OCOTP_CTRL_CRC_TEST(v)   BF_CS1(OCOTP_CTRL, CRC_TEST, v)
#endif

/* --- Register HW_OCOTP_CTRL, field CRC_FAIL[12] (RW)
 *
 * Set by controller when calculated CRC value is not equal to appointed CRC fuse word
 */

#define BP_OCOTP_CTRL_CRC_FAIL      (12)      //!< Bit position for OCOTP_CTRL_CRC_FAIL.
#define BM_OCOTP_CTRL_CRC_FAIL      (0x00001000)  //!< Bit mask for OCOTP_CTRL_CRC_FAIL.

//! @brief Get value of OCOTP_CTRL_CRC_FAIL from a register value.
#define BG_OCOTP_CTRL_CRC_FAIL(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_CRC_FAIL) >> BP_OCOTP_CTRL_CRC_FAIL)

//! @brief Format value for bitfield OCOTP_CTRL_CRC_FAIL.
#define BF_OCOTP_CTRL_CRC_FAIL(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_CRC_FAIL) & BM_OCOTP_CTRL_CRC_FAIL)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRC_FAIL field to a new value.
#define BW_OCOTP_CTRL_CRC_FAIL(v)   BF_CS1(OCOTP_CTRL, CRC_FAIL, v)
#endif

/* --- Register HW_OCOTP_CTRL, field WR_UNLOCK[31:16] (RW)
 *
 * Write 0x3E77 to enable OTP write accesses. NOTE: This register must be unlocked on a write-by-
 * write basis (a write is initiated when HW_OCOTP_DATA is written), so the UNLOCK bitfield must
 * contain the correct key value during all writes to HW_OCOTP_DATA, otherwise a write shall not be
 * initiated. This field is automatically cleared after a successful write completion (clearing of
 * BUSY).
 *
 * Values:
 * KEY = 0x3E77 - Key needed to unlock HW_OCOTP_DATA register.
 */

#define BP_OCOTP_CTRL_WR_UNLOCK      (16)      //!< Bit position for OCOTP_CTRL_WR_UNLOCK.
#define BM_OCOTP_CTRL_WR_UNLOCK      (0xffff0000)  //!< Bit mask for OCOTP_CTRL_WR_UNLOCK.

//! @brief Get value of OCOTP_CTRL_WR_UNLOCK from a register value.
#define BG_OCOTP_CTRL_WR_UNLOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CTRL_WR_UNLOCK) >> BP_OCOTP_CTRL_WR_UNLOCK)

//! @brief Format value for bitfield OCOTP_CTRL_WR_UNLOCK.
#define BF_OCOTP_CTRL_WR_UNLOCK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CTRL_WR_UNLOCK) & BM_OCOTP_CTRL_WR_UNLOCK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WR_UNLOCK field to a new value.
#define BW_OCOTP_CTRL_WR_UNLOCK(v)   BF_CS1(OCOTP_CTRL, WR_UNLOCK, v)
#endif

#define BV_OCOTP_CTRL_WR_UNLOCK__KEY (0x3e77) //!< Key needed to unlock HW_OCOTP_DATA register.

//-------------------------------------------------------------------------------------------
// HW_OCOTP_TIMING - OTP Controller Timing Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_TIMING - OTP Controller Timing Register (RW)
 *
 * Reset value: 0x01461299
 *
 * The OCOTP Data Register is used for OTP Programming  This register specifies timing parameters
 * for programming and reading the OCOTP fuse array.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_timing
{
    reg32_t U;
    struct _hw_ocotp_timing_bitfields
    {
        unsigned STROBE_PROG : 12; //!< [11:0] This count value specifies the strobe period in one time write OTP.
        unsigned RELAX : 4; //!< [15:12] This count value specifies the time to add to all default timing parameters other than the Tpgm and Trd.
        unsigned STROBE_READ : 6; //!< [21:16] This count value specifies the strobe period in one time read OTP.
        unsigned WAIT : 6; //!< [27:22] This count value specifies time interval between auto read and write access in one time program.
        unsigned RESERVED0 : 4; //!< [31:28] These bits always read back zero.
    } B;
} hw_ocotp_timing_t;
#endif

/*
 * constants & macros for entire OCOTP_TIMING register
 */
#define HW_OCOTP_TIMING_ADDR      (REGS_OCOTP_BASE + 0x10)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_TIMING           (*(volatile hw_ocotp_timing_t *) HW_OCOTP_TIMING_ADDR)
#define HW_OCOTP_TIMING_RD()      (HW_OCOTP_TIMING.U)
#define HW_OCOTP_TIMING_WR(v)     (HW_OCOTP_TIMING.U = (v))
#define HW_OCOTP_TIMING_SET(v)    (HW_OCOTP_TIMING_WR(HW_OCOTP_TIMING_RD() |  (v)))
#define HW_OCOTP_TIMING_CLR(v)    (HW_OCOTP_TIMING_WR(HW_OCOTP_TIMING_RD() & ~(v)))
#define HW_OCOTP_TIMING_TOG(v)    (HW_OCOTP_TIMING_WR(HW_OCOTP_TIMING_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_TIMING bitfields
 */

/* --- Register HW_OCOTP_TIMING, field STROBE_PROG[11:0] (RW)
 *
 * This count value specifies the strobe period in one time write OTP. Tpgm = ((STROBE_PROG+1)-
 * 2*(RELAX+1)) /ipg_clk_freq. It is given in number of ipg_clk periods.
 */

#define BP_OCOTP_TIMING_STROBE_PROG      (0)      //!< Bit position for OCOTP_TIMING_STROBE_PROG.
#define BM_OCOTP_TIMING_STROBE_PROG      (0x00000fff)  //!< Bit mask for OCOTP_TIMING_STROBE_PROG.

//! @brief Get value of OCOTP_TIMING_STROBE_PROG from a register value.
#define BG_OCOTP_TIMING_STROBE_PROG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_TIMING_STROBE_PROG) >> BP_OCOTP_TIMING_STROBE_PROG)

//! @brief Format value for bitfield OCOTP_TIMING_STROBE_PROG.
#define BF_OCOTP_TIMING_STROBE_PROG(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_TIMING_STROBE_PROG) & BM_OCOTP_TIMING_STROBE_PROG)

#ifndef __LANGUAGE_ASM__
//! @brief Set the STROBE_PROG field to a new value.
#define BW_OCOTP_TIMING_STROBE_PROG(v)   (HW_OCOTP_TIMING_WR((HW_OCOTP_TIMING_RD() & ~BM_OCOTP_TIMING_STROBE_PROG) | BF_OCOTP_TIMING_STROBE_PROG(v)))
#endif

/* --- Register HW_OCOTP_TIMING, field RELAX[15:12] (RW)
 *
 * This count value specifies the time to add to all default timing parameters other than the Tpgm
 * and Trd. It is given in number of ipg_clk periods.
 */

#define BP_OCOTP_TIMING_RELAX      (12)      //!< Bit position for OCOTP_TIMING_RELAX.
#define BM_OCOTP_TIMING_RELAX      (0x0000f000)  //!< Bit mask for OCOTP_TIMING_RELAX.

//! @brief Get value of OCOTP_TIMING_RELAX from a register value.
#define BG_OCOTP_TIMING_RELAX(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_TIMING_RELAX) >> BP_OCOTP_TIMING_RELAX)

//! @brief Format value for bitfield OCOTP_TIMING_RELAX.
#define BF_OCOTP_TIMING_RELAX(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_TIMING_RELAX) & BM_OCOTP_TIMING_RELAX)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RELAX field to a new value.
#define BW_OCOTP_TIMING_RELAX(v)   (HW_OCOTP_TIMING_WR((HW_OCOTP_TIMING_RD() & ~BM_OCOTP_TIMING_RELAX) | BF_OCOTP_TIMING_RELAX(v)))
#endif

/* --- Register HW_OCOTP_TIMING, field STROBE_READ[21:16] (RW)
 *
 * This count value specifies the strobe period in one time read OTP. Trd = ((STROBE_READ+1)-
 * 2*(RELAX+1)) /ipg_clk_freq. It is given in number of ipg_clk periods.
 */

#define BP_OCOTP_TIMING_STROBE_READ      (16)      //!< Bit position for OCOTP_TIMING_STROBE_READ.
#define BM_OCOTP_TIMING_STROBE_READ      (0x003f0000)  //!< Bit mask for OCOTP_TIMING_STROBE_READ.

//! @brief Get value of OCOTP_TIMING_STROBE_READ from a register value.
#define BG_OCOTP_TIMING_STROBE_READ(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_TIMING_STROBE_READ) >> BP_OCOTP_TIMING_STROBE_READ)

//! @brief Format value for bitfield OCOTP_TIMING_STROBE_READ.
#define BF_OCOTP_TIMING_STROBE_READ(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_TIMING_STROBE_READ) & BM_OCOTP_TIMING_STROBE_READ)

#ifndef __LANGUAGE_ASM__
//! @brief Set the STROBE_READ field to a new value.
#define BW_OCOTP_TIMING_STROBE_READ(v)   (HW_OCOTP_TIMING_WR((HW_OCOTP_TIMING_RD() & ~BM_OCOTP_TIMING_STROBE_READ) | BF_OCOTP_TIMING_STROBE_READ(v)))
#endif

/* --- Register HW_OCOTP_TIMING, field WAIT[27:22] (RW)
 *
 * This count value specifies time interval between auto read and write access in one time program.
 * It is given in number of ipg_clk periods.
 */

#define BP_OCOTP_TIMING_WAIT      (22)      //!< Bit position for OCOTP_TIMING_WAIT.
#define BM_OCOTP_TIMING_WAIT      (0x0fc00000)  //!< Bit mask for OCOTP_TIMING_WAIT.

//! @brief Get value of OCOTP_TIMING_WAIT from a register value.
#define BG_OCOTP_TIMING_WAIT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_TIMING_WAIT) >> BP_OCOTP_TIMING_WAIT)

//! @brief Format value for bitfield OCOTP_TIMING_WAIT.
#define BF_OCOTP_TIMING_WAIT(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_TIMING_WAIT) & BM_OCOTP_TIMING_WAIT)

#ifndef __LANGUAGE_ASM__
//! @brief Set the WAIT field to a new value.
#define BW_OCOTP_TIMING_WAIT(v)   (HW_OCOTP_TIMING_WR((HW_OCOTP_TIMING_RD() & ~BM_OCOTP_TIMING_WAIT) | BF_OCOTP_TIMING_WAIT(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DATA - OTP Controller Write Data Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DATA - OTP Controller Write Data Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Data Register is used for OTP Programming  This register is used in conjuction with
 * HW_OCOTP_CTRL to perform one-time writes to the OTP. Please see the "Software Write Sequence"
 * section for operating details.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_data
{
    reg32_t U;
    struct _hw_ocotp_data_bitfields
    {
        unsigned DATA : 32; //!< [31:0] Used to initiate a write to OTP.
    } B;
} hw_ocotp_data_t;
#endif

/*
 * constants & macros for entire OCOTP_DATA register
 */
#define HW_OCOTP_DATA_ADDR      (REGS_OCOTP_BASE + 0x20)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DATA           (*(volatile hw_ocotp_data_t *) HW_OCOTP_DATA_ADDR)
#define HW_OCOTP_DATA_RD()      (HW_OCOTP_DATA.U)
#define HW_OCOTP_DATA_WR(v)     (HW_OCOTP_DATA.U = (v))
#define HW_OCOTP_DATA_SET(v)    (HW_OCOTP_DATA_WR(HW_OCOTP_DATA_RD() |  (v)))
#define HW_OCOTP_DATA_CLR(v)    (HW_OCOTP_DATA_WR(HW_OCOTP_DATA_RD() & ~(v)))
#define HW_OCOTP_DATA_TOG(v)    (HW_OCOTP_DATA_WR(HW_OCOTP_DATA_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DATA bitfields
 */

/* --- Register HW_OCOTP_DATA, field DATA[31:0] (RW)
 *
 * Used to initiate a write to OTP. Please see the "Software Write Sequence" section for operating
 * details.
 */

#define BP_OCOTP_DATA_DATA      (0)      //!< Bit position for OCOTP_DATA_DATA.
#define BM_OCOTP_DATA_DATA      (0xffffffff)  //!< Bit mask for OCOTP_DATA_DATA.

//! @brief Get value of OCOTP_DATA_DATA from a register value.
#define BG_OCOTP_DATA_DATA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DATA_DATA) >> BP_OCOTP_DATA_DATA)

//! @brief Format value for bitfield OCOTP_DATA_DATA.
#define BF_OCOTP_DATA_DATA(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DATA_DATA) & BM_OCOTP_DATA_DATA)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATA field to a new value.
#define BW_OCOTP_DATA_DATA(v)   (HW_OCOTP_DATA_WR((HW_OCOTP_DATA_RD() & ~BM_OCOTP_DATA_DATA) | BF_OCOTP_DATA_DATA(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_READ_CTRL - OTP Controller Write Data Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_READ_CTRL - OTP Controller Write Data Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Register is used for OTP Read  This register is used in conjuction with HW_OCOTP_CTRL
 * to perform one time read to the OTP. Please see the "Software read Sequence" section for
 * operating details.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_read_ctrl
{
    reg32_t U;
    struct _hw_ocotp_read_ctrl_bitfields
    {
        unsigned READ_FUSE : 1; //!< [0] Used to initiate a read to OTP.
        unsigned RESERVED0 : 31; //!< [31:1] Reserved
    } B;
} hw_ocotp_read_ctrl_t;
#endif

/*
 * constants & macros for entire OCOTP_READ_CTRL register
 */
#define HW_OCOTP_READ_CTRL_ADDR      (REGS_OCOTP_BASE + 0x30)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_READ_CTRL           (*(volatile hw_ocotp_read_ctrl_t *) HW_OCOTP_READ_CTRL_ADDR)
#define HW_OCOTP_READ_CTRL_RD()      (HW_OCOTP_READ_CTRL.U)
#define HW_OCOTP_READ_CTRL_WR(v)     (HW_OCOTP_READ_CTRL.U = (v))
#define HW_OCOTP_READ_CTRL_SET(v)    (HW_OCOTP_READ_CTRL_WR(HW_OCOTP_READ_CTRL_RD() |  (v)))
#define HW_OCOTP_READ_CTRL_CLR(v)    (HW_OCOTP_READ_CTRL_WR(HW_OCOTP_READ_CTRL_RD() & ~(v)))
#define HW_OCOTP_READ_CTRL_TOG(v)    (HW_OCOTP_READ_CTRL_WR(HW_OCOTP_READ_CTRL_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_READ_CTRL bitfields
 */

/* --- Register HW_OCOTP_READ_CTRL, field READ_FUSE[0] (RW)
 *
 * Used to initiate a read to OTP. Please see the "Software read Sequence" section for operating
 * details.
 */

#define BP_OCOTP_READ_CTRL_READ_FUSE      (0)      //!< Bit position for OCOTP_READ_CTRL_READ_FUSE.
#define BM_OCOTP_READ_CTRL_READ_FUSE      (0x00000001)  //!< Bit mask for OCOTP_READ_CTRL_READ_FUSE.

//! @brief Get value of OCOTP_READ_CTRL_READ_FUSE from a register value.
#define BG_OCOTP_READ_CTRL_READ_FUSE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_READ_CTRL_READ_FUSE) >> BP_OCOTP_READ_CTRL_READ_FUSE)

//! @brief Format value for bitfield OCOTP_READ_CTRL_READ_FUSE.
#define BF_OCOTP_READ_CTRL_READ_FUSE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_READ_CTRL_READ_FUSE) & BM_OCOTP_READ_CTRL_READ_FUSE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the READ_FUSE field to a new value.
#define BW_OCOTP_READ_CTRL_READ_FUSE(v)   (HW_OCOTP_READ_CTRL_WR((HW_OCOTP_READ_CTRL_RD() & ~BM_OCOTP_READ_CTRL_READ_FUSE) | BF_OCOTP_READ_CTRL_READ_FUSE(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_READ_FUSE_DATA - OTP Controller Read Data Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_READ_FUSE_DATA - OTP Controller Read Data Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Data Register is used for OTP Read  The data read from OTP   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_read_fuse_data
{
    reg32_t U;
    struct _hw_ocotp_read_fuse_data_bitfields
    {
        unsigned DATA : 32; //!< [31:0] The data read from OTP
    } B;
} hw_ocotp_read_fuse_data_t;
#endif

/*
 * constants & macros for entire OCOTP_READ_FUSE_DATA register
 */
#define HW_OCOTP_READ_FUSE_DATA_ADDR      (REGS_OCOTP_BASE + 0x40)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_READ_FUSE_DATA           (*(volatile hw_ocotp_read_fuse_data_t *) HW_OCOTP_READ_FUSE_DATA_ADDR)
#define HW_OCOTP_READ_FUSE_DATA_RD()      (HW_OCOTP_READ_FUSE_DATA.U)
#define HW_OCOTP_READ_FUSE_DATA_WR(v)     (HW_OCOTP_READ_FUSE_DATA.U = (v))
#define HW_OCOTP_READ_FUSE_DATA_SET(v)    (HW_OCOTP_READ_FUSE_DATA_WR(HW_OCOTP_READ_FUSE_DATA_RD() |  (v)))
#define HW_OCOTP_READ_FUSE_DATA_CLR(v)    (HW_OCOTP_READ_FUSE_DATA_WR(HW_OCOTP_READ_FUSE_DATA_RD() & ~(v)))
#define HW_OCOTP_READ_FUSE_DATA_TOG(v)    (HW_OCOTP_READ_FUSE_DATA_WR(HW_OCOTP_READ_FUSE_DATA_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_READ_FUSE_DATA bitfields
 */

/* --- Register HW_OCOTP_READ_FUSE_DATA, field DATA[31:0] (RW)
 *
 * The data read from OTP
 */

#define BP_OCOTP_READ_FUSE_DATA_DATA      (0)      //!< Bit position for OCOTP_READ_FUSE_DATA_DATA.
#define BM_OCOTP_READ_FUSE_DATA_DATA      (0xffffffff)  //!< Bit mask for OCOTP_READ_FUSE_DATA_DATA.

//! @brief Get value of OCOTP_READ_FUSE_DATA_DATA from a register value.
#define BG_OCOTP_READ_FUSE_DATA_DATA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_READ_FUSE_DATA_DATA) >> BP_OCOTP_READ_FUSE_DATA_DATA)

//! @brief Format value for bitfield OCOTP_READ_FUSE_DATA_DATA.
#define BF_OCOTP_READ_FUSE_DATA_DATA(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_READ_FUSE_DATA_DATA) & BM_OCOTP_READ_FUSE_DATA_DATA)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATA field to a new value.
#define BW_OCOTP_READ_FUSE_DATA_DATA(v)   (HW_OCOTP_READ_FUSE_DATA_WR((HW_OCOTP_READ_FUSE_DATA_RD() & ~BM_OCOTP_READ_FUSE_DATA_DATA) | BF_OCOTP_READ_FUSE_DATA_DATA(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SW_STICKY - Sticky bit Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SW_STICKY - Sticky bit Register (RW)
 *
 * Reset value: 0x00000000
 *
 * Some SW sticky bits .  Some sticky bits are used by SW to lock some fuse area , shadow registers
 * and other features.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_sw_sticky
{
    reg32_t U;
    struct _hw_ocotp_sw_sticky_bitfields
    {
        unsigned RESERVED0 : 1; //!< [0] Reserved.
        unsigned SRK_REVOKE_LOCK : 1; //!< [1] Shadow register write and OTP write lock for SRK_REVOKE region.
        unsigned FIELD_RETURN_LOCK : 1; //!< [2] Shadow register write and OTP write lock for FIELD_RETURN region.
        unsigned RESERVED1 : 29; //!< [31:3] Reserved
    } B;
} hw_ocotp_sw_sticky_t;
#endif

/*
 * constants & macros for entire OCOTP_SW_STICKY register
 */
#define HW_OCOTP_SW_STICKY_ADDR      (REGS_OCOTP_BASE + 0x50)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SW_STICKY           (*(volatile hw_ocotp_sw_sticky_t *) HW_OCOTP_SW_STICKY_ADDR)
#define HW_OCOTP_SW_STICKY_RD()      (HW_OCOTP_SW_STICKY.U)
#define HW_OCOTP_SW_STICKY_WR(v)     (HW_OCOTP_SW_STICKY.U = (v))
#define HW_OCOTP_SW_STICKY_SET(v)    (HW_OCOTP_SW_STICKY_WR(HW_OCOTP_SW_STICKY_RD() |  (v)))
#define HW_OCOTP_SW_STICKY_CLR(v)    (HW_OCOTP_SW_STICKY_WR(HW_OCOTP_SW_STICKY_RD() & ~(v)))
#define HW_OCOTP_SW_STICKY_TOG(v)    (HW_OCOTP_SW_STICKY_WR(HW_OCOTP_SW_STICKY_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SW_STICKY bitfields
 */

/* --- Register HW_OCOTP_SW_STICKY, field SRK_REVOKE_LOCK[1] (RW)
 *
 * Shadow register write and OTP write lock for SRK_REVOKE region. When set, the writing of this
 * region's shadow register and OTP fuse word are blocked. Once this bit is set, it is always high
 * unless a POR is issued.
 */

#define BP_OCOTP_SW_STICKY_SRK_REVOKE_LOCK      (1)      //!< Bit position for OCOTP_SW_STICKY_SRK_REVOKE_LOCK.
#define BM_OCOTP_SW_STICKY_SRK_REVOKE_LOCK      (0x00000002)  //!< Bit mask for OCOTP_SW_STICKY_SRK_REVOKE_LOCK.

//! @brief Get value of OCOTP_SW_STICKY_SRK_REVOKE_LOCK from a register value.
#define BG_OCOTP_SW_STICKY_SRK_REVOKE_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SW_STICKY_SRK_REVOKE_LOCK) >> BP_OCOTP_SW_STICKY_SRK_REVOKE_LOCK)

//! @brief Format value for bitfield OCOTP_SW_STICKY_SRK_REVOKE_LOCK.
#define BF_OCOTP_SW_STICKY_SRK_REVOKE_LOCK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SW_STICKY_SRK_REVOKE_LOCK) & BM_OCOTP_SW_STICKY_SRK_REVOKE_LOCK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SRK_REVOKE_LOCK field to a new value.
#define BW_OCOTP_SW_STICKY_SRK_REVOKE_LOCK(v)   (HW_OCOTP_SW_STICKY_WR((HW_OCOTP_SW_STICKY_RD() & ~BM_OCOTP_SW_STICKY_SRK_REVOKE_LOCK) | BF_OCOTP_SW_STICKY_SRK_REVOKE_LOCK(v)))
#endif

/* --- Register HW_OCOTP_SW_STICKY, field FIELD_RETURN_LOCK[2] (RW)
 *
 * Shadow register write and OTP write lock for FIELD_RETURN region. When set, the writing of this
 * region's shadow register and OTP fuse word are blocked.Once this bit is set, it is always high
 * unless a POR is issued.
 */

#define BP_OCOTP_SW_STICKY_FIELD_RETURN_LOCK      (2)      //!< Bit position for OCOTP_SW_STICKY_FIELD_RETURN_LOCK.
#define BM_OCOTP_SW_STICKY_FIELD_RETURN_LOCK      (0x00000004)  //!< Bit mask for OCOTP_SW_STICKY_FIELD_RETURN_LOCK.

//! @brief Get value of OCOTP_SW_STICKY_FIELD_RETURN_LOCK from a register value.
#define BG_OCOTP_SW_STICKY_FIELD_RETURN_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SW_STICKY_FIELD_RETURN_LOCK) >> BP_OCOTP_SW_STICKY_FIELD_RETURN_LOCK)

//! @brief Format value for bitfield OCOTP_SW_STICKY_FIELD_RETURN_LOCK.
#define BF_OCOTP_SW_STICKY_FIELD_RETURN_LOCK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SW_STICKY_FIELD_RETURN_LOCK) & BM_OCOTP_SW_STICKY_FIELD_RETURN_LOCK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the FIELD_RETURN_LOCK field to a new value.
#define BW_OCOTP_SW_STICKY_FIELD_RETURN_LOCK(v)   (HW_OCOTP_SW_STICKY_WR((HW_OCOTP_SW_STICKY_RD() & ~BM_OCOTP_SW_STICKY_FIELD_RETURN_LOCK) | BF_OCOTP_SW_STICKY_FIELD_RETURN_LOCK(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SCS - Software Controllable Signals Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SCS - Software Controllable Signals Register (RW)
 *
 * Reset value: 0x00000000
 *
 * HW_OCOTP_SCS: 0x060  This register holds volatile configuration values that can be set and locked
 * by trusted software. All values are returned to their defualt values after POR.   EXAMPLE   Empty
 * Example.
 */
typedef union _hw_ocotp_scs
{
    reg32_t U;
    struct _hw_ocotp_scs_bitfields
    {
        unsigned HAB_JDE : 1; //!< [0] HAB JTAG Debug Enable.
        unsigned SPARE : 30; //!< [30:1] Unallocated read/write bits for implementation specific software use.
        unsigned LOCK : 1; //!< [31] When set, all of the bits in this register are locked and can not be changed through SW programming.
    } B;
} hw_ocotp_scs_t;
#endif

/*
 * constants & macros for entire OCOTP_SCS register
 */
#define HW_OCOTP_SCS_ADDR      (REGS_OCOTP_BASE + 0x60)
#define HW_OCOTP_SCS_SET_ADDR  (HW_OCOTP_SCS_ADDR + 0x4)
#define HW_OCOTP_SCS_CLR_ADDR  (HW_OCOTP_SCS_ADDR + 0x8)
#define HW_OCOTP_SCS_TOG_ADDR  (HW_OCOTP_SCS_ADDR + 0xC)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SCS           (*(volatile hw_ocotp_scs_t *) HW_OCOTP_SCS_ADDR)
#define HW_OCOTP_SCS_RD()      (HW_OCOTP_SCS.U)
#define HW_OCOTP_SCS_WR(v)     (HW_OCOTP_SCS.U = (v))
#define HW_OCOTP_SCS_SET(v)    ((*(volatile reg32_t *) HW_OCOTP_SCS_SET_ADDR) = (v))
#define HW_OCOTP_SCS_CLR(v)    ((*(volatile reg32_t *) HW_OCOTP_SCS_CLR_ADDR) = (v))
#define HW_OCOTP_SCS_TOG(v)    ((*(volatile reg32_t *) HW_OCOTP_SCS_TOG_ADDR) = (v))
#endif

/*
 * constants & macros for individual OCOTP_SCS bitfields
 */

/* --- Register HW_OCOTP_SCS, field HAB_JDE[0] (RW)
 *
 * HAB JTAG Debug Enable. This bit is used by the HAB to enable JTAG debugging, assuming that a
 * properlay signed command to do so is found and validated by the HAB. The HAB must lock the
 * register before passing control to the OS whether or not JTAG debugging has been enabled. Once
 * JTAG is enabled by this bit, it can not be disabled unless the system is reset by POR. 0: JTAG
 * debugging is not enabled by the HAB (it may still be enabled by other mechanisms). 1: JTAG
 * debugging is enabled by the HAB (though this signal may be gated off).
 *
 * Values:
 * 1 - JTAG debugging is enabled by the HAB (though this signal may be gated off)
 */

#define BP_OCOTP_SCS_HAB_JDE      (0)      //!< Bit position for OCOTP_SCS_HAB_JDE.
#define BM_OCOTP_SCS_HAB_JDE      (0x00000001)  //!< Bit mask for OCOTP_SCS_HAB_JDE.

//! @brief Get value of OCOTP_SCS_HAB_JDE from a register value.
#define BG_OCOTP_SCS_HAB_JDE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SCS_HAB_JDE) >> BP_OCOTP_SCS_HAB_JDE)

//! @brief Format value for bitfield OCOTP_SCS_HAB_JDE.
#define BF_OCOTP_SCS_HAB_JDE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SCS_HAB_JDE) & BM_OCOTP_SCS_HAB_JDE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the HAB_JDE field to a new value.
#define BW_OCOTP_SCS_HAB_JDE(v)   BF_CS1(OCOTP_SCS, HAB_JDE, v)
#endif


/* --- Register HW_OCOTP_SCS, field SPARE[30:1] (RW)
 *
 * Unallocated read/write bits for implementation specific software use.
 */

#define BP_OCOTP_SCS_SPARE      (1)      //!< Bit position for OCOTP_SCS_SPARE.
#define BM_OCOTP_SCS_SPARE      (0x7ffffffe)  //!< Bit mask for OCOTP_SCS_SPARE.

//! @brief Get value of OCOTP_SCS_SPARE from a register value.
#define BG_OCOTP_SCS_SPARE(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SCS_SPARE) >> BP_OCOTP_SCS_SPARE)

//! @brief Format value for bitfield OCOTP_SCS_SPARE.
#define BF_OCOTP_SCS_SPARE(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SCS_SPARE) & BM_OCOTP_SCS_SPARE)

#ifndef __LANGUAGE_ASM__
//! @brief Set the SPARE field to a new value.
#define BW_OCOTP_SCS_SPARE(v)   BF_CS1(OCOTP_SCS, SPARE, v)
#endif

/* --- Register HW_OCOTP_SCS, field LOCK[31] (RW)
 *
 * When set, all of the bits in this register are locked and can not be changed through SW
 * programming. This bit is only reset after a POR is issued.
 */

#define BP_OCOTP_SCS_LOCK      (31)      //!< Bit position for OCOTP_SCS_LOCK.
#define BM_OCOTP_SCS_LOCK      (0x80000000)  //!< Bit mask for OCOTP_SCS_LOCK.

//! @brief Get value of OCOTP_SCS_LOCK from a register value.
#define BG_OCOTP_SCS_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SCS_LOCK) >> BP_OCOTP_SCS_LOCK)

//! @brief Format value for bitfield OCOTP_SCS_LOCK.
#define BF_OCOTP_SCS_LOCK(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SCS_LOCK) & BM_OCOTP_SCS_LOCK)

#ifndef __LANGUAGE_ASM__
//! @brief Set the LOCK field to a new value.
#define BW_OCOTP_SCS_LOCK(v)   BF_CS1(OCOTP_SCS, LOCK, v)
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC_ADDR - OTP Controller CRC test address
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC_ADDR - OTP Controller CRC test address (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Data Register is used for OTP Read  The address for CRC calculation   EXAMPLE   Empty
 * Example.
 */
typedef union _hw_ocotp_crc_addr
{
    reg32_t U;
    struct _hw_ocotp_crc_addr_bitfields
    {
        unsigned DATA_START_ADDR : 8; //!< [7:0] End address of fuse location for CRC calculation
        unsigned DATA_END_ADDR : 8; //!< [15:8] Start address of fuse location for CRC calculation
        unsigned CRC_ADDR : 3; //!< [18:16] Address of 32-bit CRC result for comparing
        unsigned RESERVED0 : 13; //!< [31:19] Reserved
    } B;
} hw_ocotp_crc_addr_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC_ADDR register
 */
#define HW_OCOTP_CRC_ADDR_ADDR      (REGS_OCOTP_BASE + 0x70)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC_ADDR           (*(volatile hw_ocotp_crc_addr_t *) HW_OCOTP_CRC_ADDR_ADDR)
#define HW_OCOTP_CRC_ADDR_RD()      (HW_OCOTP_CRC_ADDR.U)
#define HW_OCOTP_CRC_ADDR_WR(v)     (HW_OCOTP_CRC_ADDR.U = (v))
#define HW_OCOTP_CRC_ADDR_SET(v)    (HW_OCOTP_CRC_ADDR_WR(HW_OCOTP_CRC_ADDR_RD() |  (v)))
#define HW_OCOTP_CRC_ADDR_CLR(v)    (HW_OCOTP_CRC_ADDR_WR(HW_OCOTP_CRC_ADDR_RD() & ~(v)))
#define HW_OCOTP_CRC_ADDR_TOG(v)    (HW_OCOTP_CRC_ADDR_WR(HW_OCOTP_CRC_ADDR_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC_ADDR bitfields
 */

/* --- Register HW_OCOTP_CRC_ADDR, field DATA_START_ADDR[7:0] (RW)
 *
 * End address of fuse location for CRC calculation
 */

#define BP_OCOTP_CRC_ADDR_DATA_START_ADDR      (0)      //!< Bit position for OCOTP_CRC_ADDR_DATA_START_ADDR.
#define BM_OCOTP_CRC_ADDR_DATA_START_ADDR      (0x000000ff)  //!< Bit mask for OCOTP_CRC_ADDR_DATA_START_ADDR.

//! @brief Get value of OCOTP_CRC_ADDR_DATA_START_ADDR from a register value.
#define BG_OCOTP_CRC_ADDR_DATA_START_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC_ADDR_DATA_START_ADDR) >> BP_OCOTP_CRC_ADDR_DATA_START_ADDR)

//! @brief Format value for bitfield OCOTP_CRC_ADDR_DATA_START_ADDR.
#define BF_OCOTP_CRC_ADDR_DATA_START_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC_ADDR_DATA_START_ADDR) & BM_OCOTP_CRC_ADDR_DATA_START_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATA_START_ADDR field to a new value.
#define BW_OCOTP_CRC_ADDR_DATA_START_ADDR(v)   (HW_OCOTP_CRC_ADDR_WR((HW_OCOTP_CRC_ADDR_RD() & ~BM_OCOTP_CRC_ADDR_DATA_START_ADDR) | BF_OCOTP_CRC_ADDR_DATA_START_ADDR(v)))
#endif

/* --- Register HW_OCOTP_CRC_ADDR, field DATA_END_ADDR[15:8] (RW)
 *
 * Start address of fuse location for CRC calculation
 */

#define BP_OCOTP_CRC_ADDR_DATA_END_ADDR      (8)      //!< Bit position for OCOTP_CRC_ADDR_DATA_END_ADDR.
#define BM_OCOTP_CRC_ADDR_DATA_END_ADDR      (0x0000ff00)  //!< Bit mask for OCOTP_CRC_ADDR_DATA_END_ADDR.

//! @brief Get value of OCOTP_CRC_ADDR_DATA_END_ADDR from a register value.
#define BG_OCOTP_CRC_ADDR_DATA_END_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC_ADDR_DATA_END_ADDR) >> BP_OCOTP_CRC_ADDR_DATA_END_ADDR)

//! @brief Format value for bitfield OCOTP_CRC_ADDR_DATA_END_ADDR.
#define BF_OCOTP_CRC_ADDR_DATA_END_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC_ADDR_DATA_END_ADDR) & BM_OCOTP_CRC_ADDR_DATA_END_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATA_END_ADDR field to a new value.
#define BW_OCOTP_CRC_ADDR_DATA_END_ADDR(v)   (HW_OCOTP_CRC_ADDR_WR((HW_OCOTP_CRC_ADDR_RD() & ~BM_OCOTP_CRC_ADDR_DATA_END_ADDR) | BF_OCOTP_CRC_ADDR_DATA_END_ADDR(v)))
#endif

/* --- Register HW_OCOTP_CRC_ADDR, field CRC_ADDR[18:16] (RW)
 *
 * Address of 32-bit CRC result for comparing
 */

#define BP_OCOTP_CRC_ADDR_CRC_ADDR      (16)      //!< Bit position for OCOTP_CRC_ADDR_CRC_ADDR.
#define BM_OCOTP_CRC_ADDR_CRC_ADDR      (0x00070000)  //!< Bit mask for OCOTP_CRC_ADDR_CRC_ADDR.

//! @brief Get value of OCOTP_CRC_ADDR_CRC_ADDR from a register value.
#define BG_OCOTP_CRC_ADDR_CRC_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC_ADDR_CRC_ADDR) >> BP_OCOTP_CRC_ADDR_CRC_ADDR)

//! @brief Format value for bitfield OCOTP_CRC_ADDR_CRC_ADDR.
#define BF_OCOTP_CRC_ADDR_CRC_ADDR(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC_ADDR_CRC_ADDR) & BM_OCOTP_CRC_ADDR_CRC_ADDR)

#ifndef __LANGUAGE_ASM__
//! @brief Set the CRC_ADDR field to a new value.
#define BW_OCOTP_CRC_ADDR_CRC_ADDR(v)   (HW_OCOTP_CRC_ADDR_WR((HW_OCOTP_CRC_ADDR_RD() & ~BM_OCOTP_CRC_ADDR_CRC_ADDR) | BF_OCOTP_CRC_ADDR_CRC_ADDR(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC_VALUE - OTP Controller CRC Value Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC_VALUE - OTP Controller CRC Value Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The OCOTP Data Register is used for OTP Read  The crc32 value based on CRC_ADDR   EXAMPLE   Empty
 * Example.
 */
typedef union _hw_ocotp_crc_value
{
    reg32_t U;
    struct _hw_ocotp_crc_value_bitfields
    {
        unsigned DATA : 32; //!< [31:0] The crc32 value based on CRC_ADDR
    } B;
} hw_ocotp_crc_value_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC_VALUE register
 */
#define HW_OCOTP_CRC_VALUE_ADDR      (REGS_OCOTP_BASE + 0x80)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC_VALUE           (*(volatile hw_ocotp_crc_value_t *) HW_OCOTP_CRC_VALUE_ADDR)
#define HW_OCOTP_CRC_VALUE_RD()      (HW_OCOTP_CRC_VALUE.U)
#define HW_OCOTP_CRC_VALUE_WR(v)     (HW_OCOTP_CRC_VALUE.U = (v))
#define HW_OCOTP_CRC_VALUE_SET(v)    (HW_OCOTP_CRC_VALUE_WR(HW_OCOTP_CRC_VALUE_RD() |  (v)))
#define HW_OCOTP_CRC_VALUE_CLR(v)    (HW_OCOTP_CRC_VALUE_WR(HW_OCOTP_CRC_VALUE_RD() & ~(v)))
#define HW_OCOTP_CRC_VALUE_TOG(v)    (HW_OCOTP_CRC_VALUE_WR(HW_OCOTP_CRC_VALUE_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC_VALUE bitfields
 */

/* --- Register HW_OCOTP_CRC_VALUE, field DATA[31:0] (RW)
 *
 * The crc32 value based on CRC_ADDR
 */

#define BP_OCOTP_CRC_VALUE_DATA      (0)      //!< Bit position for OCOTP_CRC_VALUE_DATA.
#define BM_OCOTP_CRC_VALUE_DATA      (0xffffffff)  //!< Bit mask for OCOTP_CRC_VALUE_DATA.

//! @brief Get value of OCOTP_CRC_VALUE_DATA from a register value.
#define BG_OCOTP_CRC_VALUE_DATA(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC_VALUE_DATA) >> BP_OCOTP_CRC_VALUE_DATA)

//! @brief Format value for bitfield OCOTP_CRC_VALUE_DATA.
#define BF_OCOTP_CRC_VALUE_DATA(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC_VALUE_DATA) & BM_OCOTP_CRC_VALUE_DATA)

#ifndef __LANGUAGE_ASM__
//! @brief Set the DATA field to a new value.
#define BW_OCOTP_CRC_VALUE_DATA(v)   (HW_OCOTP_CRC_VALUE_WR((HW_OCOTP_CRC_VALUE_RD() & ~BM_OCOTP_CRC_VALUE_DATA) | BF_OCOTP_CRC_VALUE_DATA(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_VERSION - OTP Controller Version Register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_VERSION - OTP Controller Version Register (RO)
 *
 * Reset value: 0x02000000
 *
 * This register always returns a known read value for debug purposes it indicates the version of
 * the block.  This register indicates the RTL version in use.   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_version
{
    reg32_t U;
    struct _hw_ocotp_version_bitfields
    {
        unsigned STEP : 16; //!< [15:0] Fixed read-only value reflecting the stepping of the RTL version.
        unsigned MINOR : 8; //!< [23:16] Fixed read-only value reflecting the MINOR field of the RTL version.
        unsigned MAJOR : 8; //!< [31:24] Fixed read-only value reflecting the MAJOR field of the RTL version.
    } B;
} hw_ocotp_version_t;
#endif

/*
 * constants & macros for entire OCOTP_VERSION register
 */
#define HW_OCOTP_VERSION_ADDR      (REGS_OCOTP_BASE + 0x90)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_VERSION           (*(volatile hw_ocotp_version_t *) HW_OCOTP_VERSION_ADDR)
#define HW_OCOTP_VERSION_RD()      (HW_OCOTP_VERSION.U)
#endif

/*
 * constants & macros for individual OCOTP_VERSION bitfields
 */

/* --- Register HW_OCOTP_VERSION, field STEP[15:0] (RO)
 *
 * Fixed read-only value reflecting the stepping of the RTL version.
 */

#define BP_OCOTP_VERSION_STEP      (0)      //!< Bit position for OCOTP_VERSION_STEP.
#define BM_OCOTP_VERSION_STEP      (0x0000ffff)  //!< Bit mask for OCOTP_VERSION_STEP.

//! @brief Get value of OCOTP_VERSION_STEP from a register value.
#define BG_OCOTP_VERSION_STEP(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_VERSION_STEP) >> BP_OCOTP_VERSION_STEP)

/* --- Register HW_OCOTP_VERSION, field MINOR[23:16] (RO)
 *
 * Fixed read-only value reflecting the MINOR field of the RTL version.
 */

#define BP_OCOTP_VERSION_MINOR      (16)      //!< Bit position for OCOTP_VERSION_MINOR.
#define BM_OCOTP_VERSION_MINOR      (0x00ff0000)  //!< Bit mask for OCOTP_VERSION_MINOR.

//! @brief Get value of OCOTP_VERSION_MINOR from a register value.
#define BG_OCOTP_VERSION_MINOR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_VERSION_MINOR) >> BP_OCOTP_VERSION_MINOR)

/* --- Register HW_OCOTP_VERSION, field MAJOR[31:24] (RO)
 *
 * Fixed read-only value reflecting the MAJOR field of the RTL version.
 */

#define BP_OCOTP_VERSION_MAJOR      (24)      //!< Bit position for OCOTP_VERSION_MAJOR.
#define BM_OCOTP_VERSION_MAJOR      (0xff000000)  //!< Bit mask for OCOTP_VERSION_MAJOR.

//! @brief Get value of OCOTP_VERSION_MAJOR from a register value.
#define BG_OCOTP_VERSION_MAJOR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_VERSION_MAJOR) >> BP_OCOTP_VERSION_MAJOR)

//-------------------------------------------------------------------------------------------
// HW_OCOTP_LOCK - Value of OTP Bank0 Word0 (Lock controls)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_LOCK - Value of OTP Bank0 Word0 (Lock controls) (RO)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 0 (ADDR = 0x00).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_lock
{
    reg32_t U;
    struct _hw_ocotp_lock_bitfields
    {
        unsigned TESTER : 2; //!< [1:0] Status of shadow register and OTP write lock for tester region.
        unsigned BOOT_CFG : 2; //!< [3:2] Status of shadow register and OTP write lock for boot_cfg region.
        unsigned MEM_TRIM : 2; //!< [5:4] Status of shadow register and OTP write lock for mem_trim region.
        unsigned SJC_RESP : 1; //!< [6] Status of shadow register read and write, OTP read and write lock for sjc_resp region.
        unsigned RESERVED0 : 1; //!< [7] Reserved
        unsigned MAC_ADDR : 2; //!< [9:8] Status of shadow register and OTP write lock for mac_addr region.
        unsigned GP1 : 2; //!< [11:10] Status of shadow register and OTP write lock for gp2 region.
        unsigned GP2 : 2; //!< [13:12] Status of shadow register and OTP write lock for gp2 region.
        unsigned SRK : 1; //!< [14] Status of shadow register and OTP write lock for srk region.
        unsigned RESERVED1 : 1; //!< [15] Reserved
        unsigned DTCP_KEY : 1; //!< [16] Status of shadow register read and write, OTP read and write lock for dtcp_key region.
        unsigned OTPMK : 1; //!< [17] Status of shadow register read and write, OTP read and write lock for otpmk region.
        unsigned ANALOG : 2; //!< [19:18] Status of shadow register and OTP write lock for analog region.
        unsigned HDCP_KSV : 1; //!< [20] Status of shadow register and OTP write lock for hdcp_ksv region.
        unsigned HDCP_KEYS : 1; //!< [21] Status of OTP write, shadow register read and write for hdcp_key region.
        unsigned MISC_CONF : 1; //!< [22] Status of shadow register and OTP write lock for misc_conf region.
        unsigned DTCP_DEV_CERT : 1; //!< [23] Status of shadow register and OTP write lock for dtcp_dev_cert region.
        unsigned RESERVED2 : 1; //!< [24] Reserved
        unsigned PIN : 1; //!< [25] Status of Pin access lock bit.
        unsigned CRC_GP_LO_LOCK : 2; //!< [27:26] Status of shadow register write and read, OTP program and read lock for lower 128 bits CRC region.
        unsigned CRC_GP_HI_LOCK : 2; //!< [29:28] Status of shadow register write and read, OTP program and read lock for upper 128 bits CRC region.
        unsigned UNALLOCATED : 2; //!< [31:30] Value of un-used portion of LOCK word
    } B;
} hw_ocotp_lock_t;
#endif

/*
 * constants & macros for entire OCOTP_LOCK register
 */
#define HW_OCOTP_LOCK_ADDR      (REGS_OCOTP_BASE + 0x400)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_LOCK           (*(volatile hw_ocotp_lock_t *) HW_OCOTP_LOCK_ADDR)
#define HW_OCOTP_LOCK_RD()      (HW_OCOTP_LOCK.U)
#endif

/*
 * constants & macros for individual OCOTP_LOCK bitfields
 */

/* --- Register HW_OCOTP_LOCK, field TESTER[1:0] (RO)
 *
 * Status of shadow register and OTP write lock for tester region. When bit 1 is set, the writing of
 * this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_TESTER      (0)      //!< Bit position for OCOTP_LOCK_TESTER.
#define BM_OCOTP_LOCK_TESTER      (0x00000003)  //!< Bit mask for OCOTP_LOCK_TESTER.

//! @brief Get value of OCOTP_LOCK_TESTER from a register value.
#define BG_OCOTP_LOCK_TESTER(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_TESTER) >> BP_OCOTP_LOCK_TESTER)

/* --- Register HW_OCOTP_LOCK, field BOOT_CFG[3:2] (RO)
 *
 * Status of shadow register and OTP write lock for boot_cfg region. When bit 1 is set, the writing
 * of this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_BOOT_CFG      (2)      //!< Bit position for OCOTP_LOCK_BOOT_CFG.
#define BM_OCOTP_LOCK_BOOT_CFG      (0x0000000c)  //!< Bit mask for OCOTP_LOCK_BOOT_CFG.

//! @brief Get value of OCOTP_LOCK_BOOT_CFG from a register value.
#define BG_OCOTP_LOCK_BOOT_CFG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_BOOT_CFG) >> BP_OCOTP_LOCK_BOOT_CFG)

/* --- Register HW_OCOTP_LOCK, field MEM_TRIM[5:4] (RO)
 *
 * Status of shadow register and OTP write lock for mem_trim region. When bit 1 is set, the writing
 * of this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_MEM_TRIM      (4)      //!< Bit position for OCOTP_LOCK_MEM_TRIM.
#define BM_OCOTP_LOCK_MEM_TRIM      (0x00000030)  //!< Bit mask for OCOTP_LOCK_MEM_TRIM.

//! @brief Get value of OCOTP_LOCK_MEM_TRIM from a register value.
#define BG_OCOTP_LOCK_MEM_TRIM(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_MEM_TRIM) >> BP_OCOTP_LOCK_MEM_TRIM)

/* --- Register HW_OCOTP_LOCK, field SJC_RESP[6] (RO)
 *
 * Status of shadow register read and write, OTP read and write lock for sjc_resp region. When set,
 * the writing of this region's shadow register and OTP fuse word are blocked. The read of this
 * region's shadow register and OTP fuse word are also blocked.
 */

#define BP_OCOTP_LOCK_SJC_RESP      (6)      //!< Bit position for OCOTP_LOCK_SJC_RESP.
#define BM_OCOTP_LOCK_SJC_RESP      (0x00000040)  //!< Bit mask for OCOTP_LOCK_SJC_RESP.

//! @brief Get value of OCOTP_LOCK_SJC_RESP from a register value.
#define BG_OCOTP_LOCK_SJC_RESP(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_SJC_RESP) >> BP_OCOTP_LOCK_SJC_RESP)

/* --- Register HW_OCOTP_LOCK, field MAC_ADDR[9:8] (RO)
 *
 * Status of shadow register and OTP write lock for mac_addr region. When bit 1 is set, the writing
 * of this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_MAC_ADDR      (8)      //!< Bit position for OCOTP_LOCK_MAC_ADDR.
#define BM_OCOTP_LOCK_MAC_ADDR      (0x00000300)  //!< Bit mask for OCOTP_LOCK_MAC_ADDR.

//! @brief Get value of OCOTP_LOCK_MAC_ADDR from a register value.
#define BG_OCOTP_LOCK_MAC_ADDR(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_MAC_ADDR) >> BP_OCOTP_LOCK_MAC_ADDR)

/* --- Register HW_OCOTP_LOCK, field GP1[11:10] (RO)
 *
 * Status of shadow register and OTP write lock for gp2 region. When bit 1 is set, the writing of
 * this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_GP1      (10)      //!< Bit position for OCOTP_LOCK_GP1.
#define BM_OCOTP_LOCK_GP1      (0x00000c00)  //!< Bit mask for OCOTP_LOCK_GP1.

//! @brief Get value of OCOTP_LOCK_GP1 from a register value.
#define BG_OCOTP_LOCK_GP1(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_GP1) >> BP_OCOTP_LOCK_GP1)

/* --- Register HW_OCOTP_LOCK, field GP2[13:12] (RO)
 *
 * Status of shadow register and OTP write lock for gp2 region. When bit 1 is set, the writing of
 * this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_GP2      (12)      //!< Bit position for OCOTP_LOCK_GP2.
#define BM_OCOTP_LOCK_GP2      (0x00003000)  //!< Bit mask for OCOTP_LOCK_GP2.

//! @brief Get value of OCOTP_LOCK_GP2 from a register value.
#define BG_OCOTP_LOCK_GP2(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_GP2) >> BP_OCOTP_LOCK_GP2)

/* --- Register HW_OCOTP_LOCK, field SRK[14] (RO)
 *
 * Status of shadow register and OTP write lock for srk region. When set, the writing of this
 * region's shadow register and OTP fuse word are blocked.
 */

#define BP_OCOTP_LOCK_SRK      (14)      //!< Bit position for OCOTP_LOCK_SRK.
#define BM_OCOTP_LOCK_SRK      (0x00004000)  //!< Bit mask for OCOTP_LOCK_SRK.

//! @brief Get value of OCOTP_LOCK_SRK from a register value.
#define BG_OCOTP_LOCK_SRK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_SRK) >> BP_OCOTP_LOCK_SRK)

/* --- Register HW_OCOTP_LOCK, field DTCP_KEY[16] (RO)
 *
 * Status of shadow register read and write, OTP read and write lock for dtcp_key region. When set,
 * the writing of this region's shadow register and OTP fuse word are blocked. The read of this
 * region's shadow register and OTP fuse word are also blocked.
 */

#define BP_OCOTP_LOCK_DTCP_KEY      (16)      //!< Bit position for OCOTP_LOCK_DTCP_KEY.
#define BM_OCOTP_LOCK_DTCP_KEY      (0x00010000)  //!< Bit mask for OCOTP_LOCK_DTCP_KEY.

//! @brief Get value of OCOTP_LOCK_DTCP_KEY from a register value.
#define BG_OCOTP_LOCK_DTCP_KEY(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_DTCP_KEY) >> BP_OCOTP_LOCK_DTCP_KEY)

/* --- Register HW_OCOTP_LOCK, field OTPMK[17] (RO)
 *
 * Status of shadow register read and write, OTP read and write lock for otpmk region. When set, the
 * writing of this region's shadow register and OTP fuse word are blocked. The read of this region's
 * shadow register and OTP fuse word are also blocked.
 */

#define BP_OCOTP_LOCK_OTPMK      (17)      //!< Bit position for OCOTP_LOCK_OTPMK.
#define BM_OCOTP_LOCK_OTPMK      (0x00020000)  //!< Bit mask for OCOTP_LOCK_OTPMK.

//! @brief Get value of OCOTP_LOCK_OTPMK from a register value.
#define BG_OCOTP_LOCK_OTPMK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_OTPMK) >> BP_OCOTP_LOCK_OTPMK)

/* --- Register HW_OCOTP_LOCK, field ANALOG[19:18] (RO)
 *
 * Status of shadow register and OTP write lock for analog region. When bit 1 is set, the writing of
 * this region's shadow register is blocked. When bit 0 is set, the writing of this region's OTP
 * fuse word is blocked.
 */

#define BP_OCOTP_LOCK_ANALOG      (18)      //!< Bit position for OCOTP_LOCK_ANALOG.
#define BM_OCOTP_LOCK_ANALOG      (0x000c0000)  //!< Bit mask for OCOTP_LOCK_ANALOG.

//! @brief Get value of OCOTP_LOCK_ANALOG from a register value.
#define BG_OCOTP_LOCK_ANALOG(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_ANALOG) >> BP_OCOTP_LOCK_ANALOG)

/* --- Register HW_OCOTP_LOCK, field HDCP_KSV[20] (RO)
 *
 * Status of shadow register and OTP write lock for hdcp_ksv region. When set, the writing of this
 * region's shadow register and OTP fuse word are blocked.
 */

#define BP_OCOTP_LOCK_HDCP_KSV      (20)      //!< Bit position for OCOTP_LOCK_HDCP_KSV.
#define BM_OCOTP_LOCK_HDCP_KSV      (0x00100000)  //!< Bit mask for OCOTP_LOCK_HDCP_KSV.

//! @brief Get value of OCOTP_LOCK_HDCP_KSV from a register value.
#define BG_OCOTP_LOCK_HDCP_KSV(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_HDCP_KSV) >> BP_OCOTP_LOCK_HDCP_KSV)

/* --- Register HW_OCOTP_LOCK, field HDCP_KEYS[21] (RO)
 *
 * Status of OTP write, shadow register read and write for hdcp_key region. When set, the writing of
 * this region's shadow register and OTP fuse word are blocked. HDTP key shadow register also can be
 * not read by ARM if set. The HDCP key region can not support OTP read feature in any case.
 */

#define BP_OCOTP_LOCK_HDCP_KEYS      (21)      //!< Bit position for OCOTP_LOCK_HDCP_KEYS.
#define BM_OCOTP_LOCK_HDCP_KEYS      (0x00200000)  //!< Bit mask for OCOTP_LOCK_HDCP_KEYS.

//! @brief Get value of OCOTP_LOCK_HDCP_KEYS from a register value.
#define BG_OCOTP_LOCK_HDCP_KEYS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_HDCP_KEYS) >> BP_OCOTP_LOCK_HDCP_KEYS)

/* --- Register HW_OCOTP_LOCK, field MISC_CONF[22] (RO)
 *
 * Status of shadow register and OTP write lock for misc_conf region. When set, the writing of this
 * region's shadow register and OTP fuse word are blocked.
 */

#define BP_OCOTP_LOCK_MISC_CONF      (22)      //!< Bit position for OCOTP_LOCK_MISC_CONF.
#define BM_OCOTP_LOCK_MISC_CONF      (0x00400000)  //!< Bit mask for OCOTP_LOCK_MISC_CONF.

//! @brief Get value of OCOTP_LOCK_MISC_CONF from a register value.
#define BG_OCOTP_LOCK_MISC_CONF(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_MISC_CONF) >> BP_OCOTP_LOCK_MISC_CONF)

/* --- Register HW_OCOTP_LOCK, field DTCP_DEV_CERT[23] (RO)
 *
 * Status of shadow register and OTP write lock for dtcp_dev_cert region. When set, the writing of
 * this region's shadow register and OTP fuse word are blocked.
 */

#define BP_OCOTP_LOCK_DTCP_DEV_CERT      (23)      //!< Bit position for OCOTP_LOCK_DTCP_DEV_CERT.
#define BM_OCOTP_LOCK_DTCP_DEV_CERT      (0x00800000)  //!< Bit mask for OCOTP_LOCK_DTCP_DEV_CERT.

//! @brief Get value of OCOTP_LOCK_DTCP_DEV_CERT from a register value.
#define BG_OCOTP_LOCK_DTCP_DEV_CERT(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_DTCP_DEV_CERT) >> BP_OCOTP_LOCK_DTCP_DEV_CERT)

/* --- Register HW_OCOTP_LOCK, field PIN[25] (RO)
 *
 * Status of Pin access lock bit. When set, pin access is disabled.
 */

#define BP_OCOTP_LOCK_PIN      (25)      //!< Bit position for OCOTP_LOCK_PIN.
#define BM_OCOTP_LOCK_PIN      (0x02000000)  //!< Bit mask for OCOTP_LOCK_PIN.

//! @brief Get value of OCOTP_LOCK_PIN from a register value.
#define BG_OCOTP_LOCK_PIN(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_PIN) >> BP_OCOTP_LOCK_PIN)

/* --- Register HW_OCOTP_LOCK, field CRC_GP_LO_LOCK[27:26] (RO)
 *
 * Status of shadow register write and read, OTP program and read lock for lower 128 bits CRC
 * region. When bit 1 is set, the reading and writing of this region's OTP fuse and reading of
 * shadow register are blocked.When bit 0 is set, the writing of this region's shadow register and
 * OTP fuse are blocked.
 */

#define BP_OCOTP_LOCK_CRC_GP_LO_LOCK      (26)      //!< Bit position for OCOTP_LOCK_CRC_GP_LO_LOCK.
#define BM_OCOTP_LOCK_CRC_GP_LO_LOCK      (0x0c000000)  //!< Bit mask for OCOTP_LOCK_CRC_GP_LO_LOCK.

//! @brief Get value of OCOTP_LOCK_CRC_GP_LO_LOCK from a register value.
#define BG_OCOTP_LOCK_CRC_GP_LO_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_CRC_GP_LO_LOCK) >> BP_OCOTP_LOCK_CRC_GP_LO_LOCK)

/* --- Register HW_OCOTP_LOCK, field CRC_GP_HI_LOCK[29:28] (RO)
 *
 * Status of shadow register write and read, OTP program and read lock for upper 128 bits CRC
 * region. When bit 1 is set, the reading and writing of this region's OTP fuse and reading of
 * shadow register are blocked.When bit 0 is set, the writing of this region's shadow register and
 * OTP fuse are blocked.
 */

#define BP_OCOTP_LOCK_CRC_GP_HI_LOCK      (28)      //!< Bit position for OCOTP_LOCK_CRC_GP_HI_LOCK.
#define BM_OCOTP_LOCK_CRC_GP_HI_LOCK      (0x30000000)  //!< Bit mask for OCOTP_LOCK_CRC_GP_HI_LOCK.

//! @brief Get value of OCOTP_LOCK_CRC_GP_HI_LOCK from a register value.
#define BG_OCOTP_LOCK_CRC_GP_HI_LOCK(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_CRC_GP_HI_LOCK) >> BP_OCOTP_LOCK_CRC_GP_HI_LOCK)

/* --- Register HW_OCOTP_LOCK, field UNALLOCATED[31:30] (RO)
 *
 * Value of un-used portion of LOCK word
 */

#define BP_OCOTP_LOCK_UNALLOCATED      (30)      //!< Bit position for OCOTP_LOCK_UNALLOCATED.
#define BM_OCOTP_LOCK_UNALLOCATED      (0xc0000000)  //!< Bit mask for OCOTP_LOCK_UNALLOCATED.

//! @brief Get value of OCOTP_LOCK_UNALLOCATED from a register value.
#define BG_OCOTP_LOCK_UNALLOCATED(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_LOCK_UNALLOCATED) >> BP_OCOTP_LOCK_UNALLOCATED)

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG0 - Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG0 - Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 1 (ADDR = 0x01).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg0
{
    reg32_t U;
    struct _hw_ocotp_cfg0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] This register contains 32 bits of the Unique ID and SJC_CHALLENGE field.
    } B;
} hw_ocotp_cfg0_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG0 register
 */
#define HW_OCOTP_CFG0_ADDR      (REGS_OCOTP_BASE + 0x410)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG0           (*(volatile hw_ocotp_cfg0_t *) HW_OCOTP_CFG0_ADDR)
#define HW_OCOTP_CFG0_RD()      (HW_OCOTP_CFG0.U)
#define HW_OCOTP_CFG0_WR(v)     (HW_OCOTP_CFG0.U = (v))
#define HW_OCOTP_CFG0_SET(v)    (HW_OCOTP_CFG0_WR(HW_OCOTP_CFG0_RD() |  (v)))
#define HW_OCOTP_CFG0_CLR(v)    (HW_OCOTP_CFG0_WR(HW_OCOTP_CFG0_RD() & ~(v)))
#define HW_OCOTP_CFG0_TOG(v)    (HW_OCOTP_CFG0_WR(HW_OCOTP_CFG0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG0 bitfields
 */

/* --- Register HW_OCOTP_CFG0, field BITS[31:0] (RW)
 *
 * This register contains 32 bits of the Unique ID and SJC_CHALLENGE field. Reflects value of OTP
 * Bank 0, word 1 (ADDR = 0x01). These bits become read-only after the HW_OCOTP_LOCK_TESTER[1] bit
 * is set.
 */

#define BP_OCOTP_CFG0_BITS      (0)      //!< Bit position for OCOTP_CFG0_BITS.
#define BM_OCOTP_CFG0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG0_BITS.

//! @brief Get value of OCOTP_CFG0_BITS from a register value.
#define BG_OCOTP_CFG0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG0_BITS) >> BP_OCOTP_CFG0_BITS)

//! @brief Format value for bitfield OCOTP_CFG0_BITS.
#define BF_OCOTP_CFG0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG0_BITS) & BM_OCOTP_CFG0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG0_BITS(v)   (HW_OCOTP_CFG0_WR((HW_OCOTP_CFG0_RD() & ~BM_OCOTP_CFG0_BITS) | BF_OCOTP_CFG0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG1 - Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG1 - Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  shadowed memory mapped access to OTP Bank 0, word 2 (ADDR = 0x02).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg1
{
    reg32_t U;
    struct _hw_ocotp_cfg1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] This register contains 32 bits of the Unique ID and SJC_CHALLENGE field.
    } B;
} hw_ocotp_cfg1_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG1 register
 */
#define HW_OCOTP_CFG1_ADDR      (REGS_OCOTP_BASE + 0x420)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG1           (*(volatile hw_ocotp_cfg1_t *) HW_OCOTP_CFG1_ADDR)
#define HW_OCOTP_CFG1_RD()      (HW_OCOTP_CFG1.U)
#define HW_OCOTP_CFG1_WR(v)     (HW_OCOTP_CFG1.U = (v))
#define HW_OCOTP_CFG1_SET(v)    (HW_OCOTP_CFG1_WR(HW_OCOTP_CFG1_RD() |  (v)))
#define HW_OCOTP_CFG1_CLR(v)    (HW_OCOTP_CFG1_WR(HW_OCOTP_CFG1_RD() & ~(v)))
#define HW_OCOTP_CFG1_TOG(v)    (HW_OCOTP_CFG1_WR(HW_OCOTP_CFG1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG1 bitfields
 */

/* --- Register HW_OCOTP_CFG1, field BITS[31:0] (RW)
 *
 * This register contains 32 bits of the Unique ID and SJC_CHALLENGE field. Reflects value of OTP
 * Bank 0, word 2 (ADDR = 0x02). These bits become read-only after the HW_OCOTP_LOCK_TESTER[1] bit
 * is set.
 */

#define BP_OCOTP_CFG1_BITS      (0)      //!< Bit position for OCOTP_CFG1_BITS.
#define BM_OCOTP_CFG1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG1_BITS.

//! @brief Get value of OCOTP_CFG1_BITS from a register value.
#define BG_OCOTP_CFG1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG1_BITS) >> BP_OCOTP_CFG1_BITS)

//! @brief Format value for bitfield OCOTP_CFG1_BITS.
#define BF_OCOTP_CFG1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG1_BITS) & BM_OCOTP_CFG1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG1_BITS(v)   (HW_OCOTP_CFG1_WR((HW_OCOTP_CFG1_RD() & ~BM_OCOTP_CFG1_BITS) | BF_OCOTP_CFG1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG2 - Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG2 - Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 3 (ADDR = 0x03).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg2
{
    reg32_t U;
    struct _hw_ocotp_cfg2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 0, word 3 (ADDR = 0x03).
    } B;
} hw_ocotp_cfg2_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG2 register
 */
#define HW_OCOTP_CFG2_ADDR      (REGS_OCOTP_BASE + 0x430)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG2           (*(volatile hw_ocotp_cfg2_t *) HW_OCOTP_CFG2_ADDR)
#define HW_OCOTP_CFG2_RD()      (HW_OCOTP_CFG2.U)
#define HW_OCOTP_CFG2_WR(v)     (HW_OCOTP_CFG2.U = (v))
#define HW_OCOTP_CFG2_SET(v)    (HW_OCOTP_CFG2_WR(HW_OCOTP_CFG2_RD() |  (v)))
#define HW_OCOTP_CFG2_CLR(v)    (HW_OCOTP_CFG2_WR(HW_OCOTP_CFG2_RD() & ~(v)))
#define HW_OCOTP_CFG2_TOG(v)    (HW_OCOTP_CFG2_WR(HW_OCOTP_CFG2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG2 bitfields
 */

/* --- Register HW_OCOTP_CFG2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 0, word 3 (ADDR = 0x03). These bits become read-only after the
 * HW_OCOTP_LOCK_TESTER[1] bit is set.
 */

#define BP_OCOTP_CFG2_BITS      (0)      //!< Bit position for OCOTP_CFG2_BITS.
#define BM_OCOTP_CFG2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG2_BITS.

//! @brief Get value of OCOTP_CFG2_BITS from a register value.
#define BG_OCOTP_CFG2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG2_BITS) >> BP_OCOTP_CFG2_BITS)

//! @brief Format value for bitfield OCOTP_CFG2_BITS.
#define BF_OCOTP_CFG2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG2_BITS) & BM_OCOTP_CFG2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG2_BITS(v)   (HW_OCOTP_CFG2_WR((HW_OCOTP_CFG2_RD() & ~BM_OCOTP_CFG2_BITS) | BF_OCOTP_CFG2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG3 - Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG3 - Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Non-shadowed memory mapped access to OTP Bank 0, word 4 (ADDR =
 * 0x04).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg3
{
    reg32_t U;
    struct _hw_ocotp_cfg3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 0, word 4 (ADDR = 0x04).
    } B;
} hw_ocotp_cfg3_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG3 register
 */
#define HW_OCOTP_CFG3_ADDR      (REGS_OCOTP_BASE + 0x440)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG3           (*(volatile hw_ocotp_cfg3_t *) HW_OCOTP_CFG3_ADDR)
#define HW_OCOTP_CFG3_RD()      (HW_OCOTP_CFG3.U)
#define HW_OCOTP_CFG3_WR(v)     (HW_OCOTP_CFG3.U = (v))
#define HW_OCOTP_CFG3_SET(v)    (HW_OCOTP_CFG3_WR(HW_OCOTP_CFG3_RD() |  (v)))
#define HW_OCOTP_CFG3_CLR(v)    (HW_OCOTP_CFG3_WR(HW_OCOTP_CFG3_RD() & ~(v)))
#define HW_OCOTP_CFG3_TOG(v)    (HW_OCOTP_CFG3_WR(HW_OCOTP_CFG3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG3 bitfields
 */

/* --- Register HW_OCOTP_CFG3, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 0, word 4 (ADDR = 0x04). These bits become read-only after the
 * HW_OCOTP_LOCK_TESTER[1] bit is set.
 */

#define BP_OCOTP_CFG3_BITS      (0)      //!< Bit position for OCOTP_CFG3_BITS.
#define BM_OCOTP_CFG3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG3_BITS.

//! @brief Get value of OCOTP_CFG3_BITS from a register value.
#define BG_OCOTP_CFG3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG3_BITS) >> BP_OCOTP_CFG3_BITS)

//! @brief Format value for bitfield OCOTP_CFG3_BITS.
#define BF_OCOTP_CFG3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG3_BITS) & BM_OCOTP_CFG3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG3_BITS(v)   (HW_OCOTP_CFG3_WR((HW_OCOTP_CFG3_RD() & ~BM_OCOTP_CFG3_BITS) | BF_OCOTP_CFG3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG4 - Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG4 - Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 5 (ADDR = 0x05).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg4
{
    reg32_t U;
    struct _hw_ocotp_cfg4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 0, word 5 (ADDR = 0x05).
    } B;
} hw_ocotp_cfg4_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG4 register
 */
#define HW_OCOTP_CFG4_ADDR      (REGS_OCOTP_BASE + 0x450)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG4           (*(volatile hw_ocotp_cfg4_t *) HW_OCOTP_CFG4_ADDR)
#define HW_OCOTP_CFG4_RD()      (HW_OCOTP_CFG4.U)
#define HW_OCOTP_CFG4_WR(v)     (HW_OCOTP_CFG4.U = (v))
#define HW_OCOTP_CFG4_SET(v)    (HW_OCOTP_CFG4_WR(HW_OCOTP_CFG4_RD() |  (v)))
#define HW_OCOTP_CFG4_CLR(v)    (HW_OCOTP_CFG4_WR(HW_OCOTP_CFG4_RD() & ~(v)))
#define HW_OCOTP_CFG4_TOG(v)    (HW_OCOTP_CFG4_WR(HW_OCOTP_CFG4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG4 bitfields
 */

/* --- Register HW_OCOTP_CFG4, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 0, word 5 (ADDR = 0x05). These bits become read-only after the
 * HW_OCOTP_LOCK_BOOT_CFG[1] bit is set.
 */

#define BP_OCOTP_CFG4_BITS      (0)      //!< Bit position for OCOTP_CFG4_BITS.
#define BM_OCOTP_CFG4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG4_BITS.

//! @brief Get value of OCOTP_CFG4_BITS from a register value.
#define BG_OCOTP_CFG4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG4_BITS) >> BP_OCOTP_CFG4_BITS)

//! @brief Format value for bitfield OCOTP_CFG4_BITS.
#define BF_OCOTP_CFG4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG4_BITS) & BM_OCOTP_CFG4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG4_BITS(v)   (HW_OCOTP_CFG4_WR((HW_OCOTP_CFG4_RD() & ~BM_OCOTP_CFG4_BITS) | BF_OCOTP_CFG4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG5 - Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG5 - Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 6 (ADDR = 0x06).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg5
{
    reg32_t U;
    struct _hw_ocotp_cfg5_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 0, word 6 (ADDR = 0x06).
    } B;
} hw_ocotp_cfg5_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG5 register
 */
#define HW_OCOTP_CFG5_ADDR      (REGS_OCOTP_BASE + 0x460)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG5           (*(volatile hw_ocotp_cfg5_t *) HW_OCOTP_CFG5_ADDR)
#define HW_OCOTP_CFG5_RD()      (HW_OCOTP_CFG5.U)
#define HW_OCOTP_CFG5_WR(v)     (HW_OCOTP_CFG5.U = (v))
#define HW_OCOTP_CFG5_SET(v)    (HW_OCOTP_CFG5_WR(HW_OCOTP_CFG5_RD() |  (v)))
#define HW_OCOTP_CFG5_CLR(v)    (HW_OCOTP_CFG5_WR(HW_OCOTP_CFG5_RD() & ~(v)))
#define HW_OCOTP_CFG5_TOG(v)    (HW_OCOTP_CFG5_WR(HW_OCOTP_CFG5_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG5 bitfields
 */

/* --- Register HW_OCOTP_CFG5, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 0, word 6 (ADDR = 0x06). These bits become read-only after the
 * HW_OCOTP_LOCK_BOOT_CFG[1] bit is set.
 */

#define BP_OCOTP_CFG5_BITS      (0)      //!< Bit position for OCOTP_CFG5_BITS.
#define BM_OCOTP_CFG5_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG5_BITS.

//! @brief Get value of OCOTP_CFG5_BITS from a register value.
#define BG_OCOTP_CFG5_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG5_BITS) >> BP_OCOTP_CFG5_BITS)

//! @brief Format value for bitfield OCOTP_CFG5_BITS.
#define BF_OCOTP_CFG5_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG5_BITS) & BM_OCOTP_CFG5_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG5_BITS(v)   (HW_OCOTP_CFG5_WR((HW_OCOTP_CFG5_RD() & ~BM_OCOTP_CFG5_BITS) | BF_OCOTP_CFG5_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CFG6 - Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CFG6 - Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 0, word 7 (ADDR = 0x07).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_cfg6
{
    reg32_t U;
    struct _hw_ocotp_cfg6_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 0, word 7 (ADDR = 0x07).
    } B;
} hw_ocotp_cfg6_t;
#endif

/*
 * constants & macros for entire OCOTP_CFG6 register
 */
#define HW_OCOTP_CFG6_ADDR      (REGS_OCOTP_BASE + 0x470)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CFG6           (*(volatile hw_ocotp_cfg6_t *) HW_OCOTP_CFG6_ADDR)
#define HW_OCOTP_CFG6_RD()      (HW_OCOTP_CFG6.U)
#define HW_OCOTP_CFG6_WR(v)     (HW_OCOTP_CFG6.U = (v))
#define HW_OCOTP_CFG6_SET(v)    (HW_OCOTP_CFG6_WR(HW_OCOTP_CFG6_RD() |  (v)))
#define HW_OCOTP_CFG6_CLR(v)    (HW_OCOTP_CFG6_WR(HW_OCOTP_CFG6_RD() & ~(v)))
#define HW_OCOTP_CFG6_TOG(v)    (HW_OCOTP_CFG6_WR(HW_OCOTP_CFG6_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CFG6 bitfields
 */

/* --- Register HW_OCOTP_CFG6, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 0, word 7 (ADDR = 0x07). These bits become read-only after the
 * HW_OCOTP_LOCK_BOOT_CFG[1] bit is set.
 */

#define BP_OCOTP_CFG6_BITS      (0)      //!< Bit position for OCOTP_CFG6_BITS.
#define BM_OCOTP_CFG6_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CFG6_BITS.

//! @brief Get value of OCOTP_CFG6_BITS from a register value.
#define BG_OCOTP_CFG6_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CFG6_BITS) >> BP_OCOTP_CFG6_BITS)

//! @brief Format value for bitfield OCOTP_CFG6_BITS.
#define BF_OCOTP_CFG6_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CFG6_BITS) & BM_OCOTP_CFG6_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CFG6_BITS(v)   (HW_OCOTP_CFG6_WR((HW_OCOTP_CFG6_RD() & ~BM_OCOTP_CFG6_BITS) | BF_OCOTP_CFG6_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MEM0 - Value of OTP Bank1 Word0 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MEM0 - Value of OTP Bank1 Word0 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 0 (ADDR = 0x08).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mem0
{
    reg32_t U;
    struct _hw_ocotp_mem0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 0 (ADDR = 0x08).
    } B;
} hw_ocotp_mem0_t;
#endif

/*
 * constants & macros for entire OCOTP_MEM0 register
 */
#define HW_OCOTP_MEM0_ADDR      (REGS_OCOTP_BASE + 0x480)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MEM0           (*(volatile hw_ocotp_mem0_t *) HW_OCOTP_MEM0_ADDR)
#define HW_OCOTP_MEM0_RD()      (HW_OCOTP_MEM0.U)
#define HW_OCOTP_MEM0_WR(v)     (HW_OCOTP_MEM0.U = (v))
#define HW_OCOTP_MEM0_SET(v)    (HW_OCOTP_MEM0_WR(HW_OCOTP_MEM0_RD() |  (v)))
#define HW_OCOTP_MEM0_CLR(v)    (HW_OCOTP_MEM0_WR(HW_OCOTP_MEM0_RD() & ~(v)))
#define HW_OCOTP_MEM0_TOG(v)    (HW_OCOTP_MEM0_WR(HW_OCOTP_MEM0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MEM0 bitfields
 */

/* --- Register HW_OCOTP_MEM0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 0 (ADDR = 0x08). These bits become read-only after the
 * HW_OCOTP_LOCK_MEM_TRIM[1] bit is set.
 */

#define BP_OCOTP_MEM0_BITS      (0)      //!< Bit position for OCOTP_MEM0_BITS.
#define BM_OCOTP_MEM0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MEM0_BITS.

//! @brief Get value of OCOTP_MEM0_BITS from a register value.
#define BG_OCOTP_MEM0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MEM0_BITS) >> BP_OCOTP_MEM0_BITS)

//! @brief Format value for bitfield OCOTP_MEM0_BITS.
#define BF_OCOTP_MEM0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MEM0_BITS) & BM_OCOTP_MEM0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MEM0_BITS(v)   (HW_OCOTP_MEM0_WR((HW_OCOTP_MEM0_RD() & ~BM_OCOTP_MEM0_BITS) | BF_OCOTP_MEM0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MEM1 - Value of OTP Bank1 Word1 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MEM1 - Value of OTP Bank1 Word1 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 1 (ADDR = 0x09).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mem1
{
    reg32_t U;
    struct _hw_ocotp_mem1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 1 (ADDR = 0x09).
    } B;
} hw_ocotp_mem1_t;
#endif

/*
 * constants & macros for entire OCOTP_MEM1 register
 */
#define HW_OCOTP_MEM1_ADDR      (REGS_OCOTP_BASE + 0x490)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MEM1           (*(volatile hw_ocotp_mem1_t *) HW_OCOTP_MEM1_ADDR)
#define HW_OCOTP_MEM1_RD()      (HW_OCOTP_MEM1.U)
#define HW_OCOTP_MEM1_WR(v)     (HW_OCOTP_MEM1.U = (v))
#define HW_OCOTP_MEM1_SET(v)    (HW_OCOTP_MEM1_WR(HW_OCOTP_MEM1_RD() |  (v)))
#define HW_OCOTP_MEM1_CLR(v)    (HW_OCOTP_MEM1_WR(HW_OCOTP_MEM1_RD() & ~(v)))
#define HW_OCOTP_MEM1_TOG(v)    (HW_OCOTP_MEM1_WR(HW_OCOTP_MEM1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MEM1 bitfields
 */

/* --- Register HW_OCOTP_MEM1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 1 (ADDR = 0x09). These bits become read-only after the
 * HW_OCOTP_LOCK_MEM_TRIM[1] bit is set.
 */

#define BP_OCOTP_MEM1_BITS      (0)      //!< Bit position for OCOTP_MEM1_BITS.
#define BM_OCOTP_MEM1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MEM1_BITS.

//! @brief Get value of OCOTP_MEM1_BITS from a register value.
#define BG_OCOTP_MEM1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MEM1_BITS) >> BP_OCOTP_MEM1_BITS)

//! @brief Format value for bitfield OCOTP_MEM1_BITS.
#define BF_OCOTP_MEM1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MEM1_BITS) & BM_OCOTP_MEM1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MEM1_BITS(v)   (HW_OCOTP_MEM1_WR((HW_OCOTP_MEM1_RD() & ~BM_OCOTP_MEM1_BITS) | BF_OCOTP_MEM1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MEM2 - Value of OTP Bank1 Word2 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MEM2 - Value of OTP Bank1 Word2 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 2 (ADDR = 0x0A).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mem2
{
    reg32_t U;
    struct _hw_ocotp_mem2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 2 (ADDR = 0x0A).
    } B;
} hw_ocotp_mem2_t;
#endif

/*
 * constants & macros for entire OCOTP_MEM2 register
 */
#define HW_OCOTP_MEM2_ADDR      (REGS_OCOTP_BASE + 0x4a0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MEM2           (*(volatile hw_ocotp_mem2_t *) HW_OCOTP_MEM2_ADDR)
#define HW_OCOTP_MEM2_RD()      (HW_OCOTP_MEM2.U)
#define HW_OCOTP_MEM2_WR(v)     (HW_OCOTP_MEM2.U = (v))
#define HW_OCOTP_MEM2_SET(v)    (HW_OCOTP_MEM2_WR(HW_OCOTP_MEM2_RD() |  (v)))
#define HW_OCOTP_MEM2_CLR(v)    (HW_OCOTP_MEM2_WR(HW_OCOTP_MEM2_RD() & ~(v)))
#define HW_OCOTP_MEM2_TOG(v)    (HW_OCOTP_MEM2_WR(HW_OCOTP_MEM2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MEM2 bitfields
 */

/* --- Register HW_OCOTP_MEM2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 2 (ADDR = 0x0A). These bits become read-only after the
 * HW_OCOTP_LOCK_MEM_TRIM[1] bit is set.
 */

#define BP_OCOTP_MEM2_BITS      (0)      //!< Bit position for OCOTP_MEM2_BITS.
#define BM_OCOTP_MEM2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MEM2_BITS.

//! @brief Get value of OCOTP_MEM2_BITS from a register value.
#define BG_OCOTP_MEM2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MEM2_BITS) >> BP_OCOTP_MEM2_BITS)

//! @brief Format value for bitfield OCOTP_MEM2_BITS.
#define BF_OCOTP_MEM2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MEM2_BITS) & BM_OCOTP_MEM2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MEM2_BITS(v)   (HW_OCOTP_MEM2_WR((HW_OCOTP_MEM2_RD() & ~BM_OCOTP_MEM2_BITS) | BF_OCOTP_MEM2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MEM3 - Value of OTP Bank1 Word3 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MEM3 - Value of OTP Bank1 Word3 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 3 (ADDR = 0x0B).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mem3
{
    reg32_t U;
    struct _hw_ocotp_mem3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 3 (ADDR = 0x0B).
    } B;
} hw_ocotp_mem3_t;
#endif

/*
 * constants & macros for entire OCOTP_MEM3 register
 */
#define HW_OCOTP_MEM3_ADDR      (REGS_OCOTP_BASE + 0x4b0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MEM3           (*(volatile hw_ocotp_mem3_t *) HW_OCOTP_MEM3_ADDR)
#define HW_OCOTP_MEM3_RD()      (HW_OCOTP_MEM3.U)
#define HW_OCOTP_MEM3_WR(v)     (HW_OCOTP_MEM3.U = (v))
#define HW_OCOTP_MEM3_SET(v)    (HW_OCOTP_MEM3_WR(HW_OCOTP_MEM3_RD() |  (v)))
#define HW_OCOTP_MEM3_CLR(v)    (HW_OCOTP_MEM3_WR(HW_OCOTP_MEM3_RD() & ~(v)))
#define HW_OCOTP_MEM3_TOG(v)    (HW_OCOTP_MEM3_WR(HW_OCOTP_MEM3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MEM3 bitfields
 */

/* --- Register HW_OCOTP_MEM3, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 3 (ADDR = 0x0B). These bits become read-only after the
 * HW_OCOTP_LOCK_MEM_TRIM[1] bit is set.
 */

#define BP_OCOTP_MEM3_BITS      (0)      //!< Bit position for OCOTP_MEM3_BITS.
#define BM_OCOTP_MEM3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MEM3_BITS.

//! @brief Get value of OCOTP_MEM3_BITS from a register value.
#define BG_OCOTP_MEM3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MEM3_BITS) >> BP_OCOTP_MEM3_BITS)

//! @brief Format value for bitfield OCOTP_MEM3_BITS.
#define BF_OCOTP_MEM3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MEM3_BITS) & BM_OCOTP_MEM3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MEM3_BITS(v)   (HW_OCOTP_MEM3_WR((HW_OCOTP_MEM3_RD() & ~BM_OCOTP_MEM3_BITS) | BF_OCOTP_MEM3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MEM4 - Value of OTP Bank1 Word4 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MEM4 - Value of OTP Bank1 Word4 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 4 (ADDR = 0x0C).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mem4
{
    reg32_t U;
    struct _hw_ocotp_mem4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 4 (ADDR = 0x0C).
    } B;
} hw_ocotp_mem4_t;
#endif

/*
 * constants & macros for entire OCOTP_MEM4 register
 */
#define HW_OCOTP_MEM4_ADDR      (REGS_OCOTP_BASE + 0x4c0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MEM4           (*(volatile hw_ocotp_mem4_t *) HW_OCOTP_MEM4_ADDR)
#define HW_OCOTP_MEM4_RD()      (HW_OCOTP_MEM4.U)
#define HW_OCOTP_MEM4_WR(v)     (HW_OCOTP_MEM4.U = (v))
#define HW_OCOTP_MEM4_SET(v)    (HW_OCOTP_MEM4_WR(HW_OCOTP_MEM4_RD() |  (v)))
#define HW_OCOTP_MEM4_CLR(v)    (HW_OCOTP_MEM4_WR(HW_OCOTP_MEM4_RD() & ~(v)))
#define HW_OCOTP_MEM4_TOG(v)    (HW_OCOTP_MEM4_WR(HW_OCOTP_MEM4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MEM4 bitfields
 */

/* --- Register HW_OCOTP_MEM4, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 4 (ADDR = 0x0C). These bits become read-only after the
 * HW_OCOTP_LOCK_MEM_TRIM[1] bit is set.
 */

#define BP_OCOTP_MEM4_BITS      (0)      //!< Bit position for OCOTP_MEM4_BITS.
#define BM_OCOTP_MEM4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MEM4_BITS.

//! @brief Get value of OCOTP_MEM4_BITS from a register value.
#define BG_OCOTP_MEM4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MEM4_BITS) >> BP_OCOTP_MEM4_BITS)

//! @brief Format value for bitfield OCOTP_MEM4_BITS.
#define BF_OCOTP_MEM4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MEM4_BITS) & BM_OCOTP_MEM4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MEM4_BITS(v)   (HW_OCOTP_MEM4_WR((HW_OCOTP_MEM4_RD() & ~BM_OCOTP_MEM4_BITS) | BF_OCOTP_MEM4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_ANA0 - Value of OTP Bank1 Word5 (Memory Related Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_ANA0 - Value of OTP Bank1 Word5 (Memory Related Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 5 (ADDR = 0x0D).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_ana0
{
    reg32_t U;
    struct _hw_ocotp_ana0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 5 (ADDR = 0x0D).
    } B;
} hw_ocotp_ana0_t;
#endif

/*
 * constants & macros for entire OCOTP_ANA0 register
 */
#define HW_OCOTP_ANA0_ADDR      (REGS_OCOTP_BASE + 0x4d0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_ANA0           (*(volatile hw_ocotp_ana0_t *) HW_OCOTP_ANA0_ADDR)
#define HW_OCOTP_ANA0_RD()      (HW_OCOTP_ANA0.U)
#define HW_OCOTP_ANA0_WR(v)     (HW_OCOTP_ANA0.U = (v))
#define HW_OCOTP_ANA0_SET(v)    (HW_OCOTP_ANA0_WR(HW_OCOTP_ANA0_RD() |  (v)))
#define HW_OCOTP_ANA0_CLR(v)    (HW_OCOTP_ANA0_WR(HW_OCOTP_ANA0_RD() & ~(v)))
#define HW_OCOTP_ANA0_TOG(v)    (HW_OCOTP_ANA0_WR(HW_OCOTP_ANA0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_ANA0 bitfields
 */

/* --- Register HW_OCOTP_ANA0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 5 (ADDR = 0x0D). These bits become read-only after the
 * HW_OCOTP_LOCK_ANALOG[1] bit is set.
 */

#define BP_OCOTP_ANA0_BITS      (0)      //!< Bit position for OCOTP_ANA0_BITS.
#define BM_OCOTP_ANA0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_ANA0_BITS.

//! @brief Get value of OCOTP_ANA0_BITS from a register value.
#define BG_OCOTP_ANA0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_ANA0_BITS) >> BP_OCOTP_ANA0_BITS)

//! @brief Format value for bitfield OCOTP_ANA0_BITS.
#define BF_OCOTP_ANA0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_ANA0_BITS) & BM_OCOTP_ANA0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_ANA0_BITS(v)   (HW_OCOTP_ANA0_WR((HW_OCOTP_ANA0_RD() & ~BM_OCOTP_ANA0_BITS) | BF_OCOTP_ANA0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_ANA1 - Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_ANA1 - Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 6 (ADDR = 0x0E).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_ana1
{
    reg32_t U;
    struct _hw_ocotp_ana1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 6 (ADDR = 0x0E).
    } B;
} hw_ocotp_ana1_t;
#endif

/*
 * constants & macros for entire OCOTP_ANA1 register
 */
#define HW_OCOTP_ANA1_ADDR      (REGS_OCOTP_BASE + 0x4e0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_ANA1           (*(volatile hw_ocotp_ana1_t *) HW_OCOTP_ANA1_ADDR)
#define HW_OCOTP_ANA1_RD()      (HW_OCOTP_ANA1.U)
#define HW_OCOTP_ANA1_WR(v)     (HW_OCOTP_ANA1.U = (v))
#define HW_OCOTP_ANA1_SET(v)    (HW_OCOTP_ANA1_WR(HW_OCOTP_ANA1_RD() |  (v)))
#define HW_OCOTP_ANA1_CLR(v)    (HW_OCOTP_ANA1_WR(HW_OCOTP_ANA1_RD() & ~(v)))
#define HW_OCOTP_ANA1_TOG(v)    (HW_OCOTP_ANA1_WR(HW_OCOTP_ANA1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_ANA1 bitfields
 */

/* --- Register HW_OCOTP_ANA1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 6 (ADDR = 0x0E). These bits become read-only after the
 * HW_OCOTP_LOCK_ANALOG[1] bit is set.
 */

#define BP_OCOTP_ANA1_BITS      (0)      //!< Bit position for OCOTP_ANA1_BITS.
#define BM_OCOTP_ANA1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_ANA1_BITS.

//! @brief Get value of OCOTP_ANA1_BITS from a register value.
#define BG_OCOTP_ANA1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_ANA1_BITS) >> BP_OCOTP_ANA1_BITS)

//! @brief Format value for bitfield OCOTP_ANA1_BITS.
#define BF_OCOTP_ANA1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_ANA1_BITS) & BM_OCOTP_ANA1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_ANA1_BITS(v)   (HW_OCOTP_ANA1_WR((HW_OCOTP_ANA1_RD() & ~BM_OCOTP_ANA1_BITS) | BF_OCOTP_ANA1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_ANA2 - Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_ANA2 - Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP bank 1, word 7 (ADDR = 0x0F).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_ana2
{
    reg32_t U;
    struct _hw_ocotp_ana2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP bank 1, word 7 (ADDR = 0x0F).
    } B;
} hw_ocotp_ana2_t;
#endif

/*
 * constants & macros for entire OCOTP_ANA2 register
 */
#define HW_OCOTP_ANA2_ADDR      (REGS_OCOTP_BASE + 0x4f0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_ANA2           (*(volatile hw_ocotp_ana2_t *) HW_OCOTP_ANA2_ADDR)
#define HW_OCOTP_ANA2_RD()      (HW_OCOTP_ANA2.U)
#define HW_OCOTP_ANA2_WR(v)     (HW_OCOTP_ANA2.U = (v))
#define HW_OCOTP_ANA2_SET(v)    (HW_OCOTP_ANA2_WR(HW_OCOTP_ANA2_RD() |  (v)))
#define HW_OCOTP_ANA2_CLR(v)    (HW_OCOTP_ANA2_WR(HW_OCOTP_ANA2_RD() & ~(v)))
#define HW_OCOTP_ANA2_TOG(v)    (HW_OCOTP_ANA2_WR(HW_OCOTP_ANA2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_ANA2 bitfields
 */

/* --- Register HW_OCOTP_ANA2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP bank 1, word 7 (ADDR = 0x0F). These bits become read-only after the
 * HW_OCOTP_LOCK_ANALOG[1] bit is set.
 */

#define BP_OCOTP_ANA2_BITS      (0)      //!< Bit position for OCOTP_ANA2_BITS.
#define BM_OCOTP_ANA2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_ANA2_BITS.

//! @brief Get value of OCOTP_ANA2_BITS from a register value.
#define BG_OCOTP_ANA2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_ANA2_BITS) >> BP_OCOTP_ANA2_BITS)

//! @brief Format value for bitfield OCOTP_ANA2_BITS.
#define BF_OCOTP_ANA2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_ANA2_BITS) & BM_OCOTP_ANA2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_ANA2_BITS(v)   (HW_OCOTP_ANA2_WR((HW_OCOTP_ANA2_RD() & ~BM_OCOTP_ANA2_BITS) | BF_OCOTP_ANA2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK0 - Shadow Register for OTP Bank2 Word0 (OTPMK and CRYPTO Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK0 - Shadow Register for OTP Bank2 Word0 (OTPMK and CRYPTO Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 0 (ADDR =
 * 0x10).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk0
{
    reg32_t U;
    struct _hw_ocotp_otpmk0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word0 (Copy of OTP Bank 2, word 0 (ADDR = 0x10)).
    } B;
} hw_ocotp_otpmk0_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK0 register
 */
#define HW_OCOTP_OTPMK0_ADDR      (REGS_OCOTP_BASE + 0x500)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK0           (*(volatile hw_ocotp_otpmk0_t *) HW_OCOTP_OTPMK0_ADDR)
#define HW_OCOTP_OTPMK0_RD()      (HW_OCOTP_OTPMK0.U)
#define HW_OCOTP_OTPMK0_WR(v)     (HW_OCOTP_OTPMK0.U = (v))
#define HW_OCOTP_OTPMK0_SET(v)    (HW_OCOTP_OTPMK0_WR(HW_OCOTP_OTPMK0_RD() |  (v)))
#define HW_OCOTP_OTPMK0_CLR(v)    (HW_OCOTP_OTPMK0_WR(HW_OCOTP_OTPMK0_RD() & ~(v)))
#define HW_OCOTP_OTPMK0_TOG(v)    (HW_OCOTP_OTPMK0_WR(HW_OCOTP_OTPMK0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK0 bitfields
 */

/* --- Register HW_OCOTP_OTPMK0, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word0 (Copy of OTP Bank 2, word 0 (ADDR = 0x10)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK0_BITS      (0)      //!< Bit position for OCOTP_OTPMK0_BITS.
#define BM_OCOTP_OTPMK0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK0_BITS.

//! @brief Get value of OCOTP_OTPMK0_BITS from a register value.
#define BG_OCOTP_OTPMK0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK0_BITS) >> BP_OCOTP_OTPMK0_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK0_BITS.
#define BF_OCOTP_OTPMK0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK0_BITS) & BM_OCOTP_OTPMK0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK0_BITS(v)   (HW_OCOTP_OTPMK0_WR((HW_OCOTP_OTPMK0_RD() & ~BM_OCOTP_OTPMK0_BITS) | BF_OCOTP_OTPMK0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK1 - Shadow Register for OTP Bank2 Word1 (OTPMK and CRYPTO Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK1 - Shadow Register for OTP Bank2 Word1 (OTPMK and CRYPTO Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 1 (ADDR =
 * 0x11).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk1
{
    reg32_t U;
    struct _hw_ocotp_otpmk1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word1 (Copy of OTP Bank 2, word 1 (ADDR = 0x11)).
    } B;
} hw_ocotp_otpmk1_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK1 register
 */
#define HW_OCOTP_OTPMK1_ADDR      (REGS_OCOTP_BASE + 0x510)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK1           (*(volatile hw_ocotp_otpmk1_t *) HW_OCOTP_OTPMK1_ADDR)
#define HW_OCOTP_OTPMK1_RD()      (HW_OCOTP_OTPMK1.U)
#define HW_OCOTP_OTPMK1_WR(v)     (HW_OCOTP_OTPMK1.U = (v))
#define HW_OCOTP_OTPMK1_SET(v)    (HW_OCOTP_OTPMK1_WR(HW_OCOTP_OTPMK1_RD() |  (v)))
#define HW_OCOTP_OTPMK1_CLR(v)    (HW_OCOTP_OTPMK1_WR(HW_OCOTP_OTPMK1_RD() & ~(v)))
#define HW_OCOTP_OTPMK1_TOG(v)    (HW_OCOTP_OTPMK1_WR(HW_OCOTP_OTPMK1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK1 bitfields
 */

/* --- Register HW_OCOTP_OTPMK1, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word1 (Copy of OTP Bank 2, word 1 (ADDR = 0x11)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK1_BITS      (0)      //!< Bit position for OCOTP_OTPMK1_BITS.
#define BM_OCOTP_OTPMK1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK1_BITS.

//! @brief Get value of OCOTP_OTPMK1_BITS from a register value.
#define BG_OCOTP_OTPMK1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK1_BITS) >> BP_OCOTP_OTPMK1_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK1_BITS.
#define BF_OCOTP_OTPMK1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK1_BITS) & BM_OCOTP_OTPMK1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK1_BITS(v)   (HW_OCOTP_OTPMK1_WR((HW_OCOTP_OTPMK1_RD() & ~BM_OCOTP_OTPMK1_BITS) | BF_OCOTP_OTPMK1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK2 - Shadow Register for OTP Bank2 Word2 (OTPMK and CRYPTO Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK2 - Shadow Register for OTP Bank2 Word2 (OTPMK and CRYPTO Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 2 (ADDR =
 * 0x12).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk2
{
    reg32_t U;
    struct _hw_ocotp_otpmk2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word2 (Copy of OTP Bank 2, word 2 (ADDR = 0x12)).
    } B;
} hw_ocotp_otpmk2_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK2 register
 */
#define HW_OCOTP_OTPMK2_ADDR      (REGS_OCOTP_BASE + 0x520)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK2           (*(volatile hw_ocotp_otpmk2_t *) HW_OCOTP_OTPMK2_ADDR)
#define HW_OCOTP_OTPMK2_RD()      (HW_OCOTP_OTPMK2.U)
#define HW_OCOTP_OTPMK2_WR(v)     (HW_OCOTP_OTPMK2.U = (v))
#define HW_OCOTP_OTPMK2_SET(v)    (HW_OCOTP_OTPMK2_WR(HW_OCOTP_OTPMK2_RD() |  (v)))
#define HW_OCOTP_OTPMK2_CLR(v)    (HW_OCOTP_OTPMK2_WR(HW_OCOTP_OTPMK2_RD() & ~(v)))
#define HW_OCOTP_OTPMK2_TOG(v)    (HW_OCOTP_OTPMK2_WR(HW_OCOTP_OTPMK2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK2 bitfields
 */

/* --- Register HW_OCOTP_OTPMK2, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word2 (Copy of OTP Bank 2, word 2 (ADDR = 0x12)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK2_BITS      (0)      //!< Bit position for OCOTP_OTPMK2_BITS.
#define BM_OCOTP_OTPMK2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK2_BITS.

//! @brief Get value of OCOTP_OTPMK2_BITS from a register value.
#define BG_OCOTP_OTPMK2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK2_BITS) >> BP_OCOTP_OTPMK2_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK2_BITS.
#define BF_OCOTP_OTPMK2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK2_BITS) & BM_OCOTP_OTPMK2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK2_BITS(v)   (HW_OCOTP_OTPMK2_WR((HW_OCOTP_OTPMK2_RD() & ~BM_OCOTP_OTPMK2_BITS) | BF_OCOTP_OTPMK2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK3 - Shadow Register for OTP Bank2 Word3 (OTPMK and CRYPTO Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK3 - Shadow Register for OTP Bank2 Word3 (OTPMK and CRYPTO Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 3 (ADDR =
 * 0x13).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk3
{
    reg32_t U;
    struct _hw_ocotp_otpmk3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word3 (Copy of OTP Bank 2, word 3 (ADDR = 0x13)).
    } B;
} hw_ocotp_otpmk3_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK3 register
 */
#define HW_OCOTP_OTPMK3_ADDR      (REGS_OCOTP_BASE + 0x530)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK3           (*(volatile hw_ocotp_otpmk3_t *) HW_OCOTP_OTPMK3_ADDR)
#define HW_OCOTP_OTPMK3_RD()      (HW_OCOTP_OTPMK3.U)
#define HW_OCOTP_OTPMK3_WR(v)     (HW_OCOTP_OTPMK3.U = (v))
#define HW_OCOTP_OTPMK3_SET(v)    (HW_OCOTP_OTPMK3_WR(HW_OCOTP_OTPMK3_RD() |  (v)))
#define HW_OCOTP_OTPMK3_CLR(v)    (HW_OCOTP_OTPMK3_WR(HW_OCOTP_OTPMK3_RD() & ~(v)))
#define HW_OCOTP_OTPMK3_TOG(v)    (HW_OCOTP_OTPMK3_WR(HW_OCOTP_OTPMK3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK3 bitfields
 */

/* --- Register HW_OCOTP_OTPMK3, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word3 (Copy of OTP Bank 2, word 3 (ADDR = 0x13)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK3_BITS      (0)      //!< Bit position for OCOTP_OTPMK3_BITS.
#define BM_OCOTP_OTPMK3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK3_BITS.

//! @brief Get value of OCOTP_OTPMK3_BITS from a register value.
#define BG_OCOTP_OTPMK3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK3_BITS) >> BP_OCOTP_OTPMK3_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK3_BITS.
#define BF_OCOTP_OTPMK3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK3_BITS) & BM_OCOTP_OTPMK3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK3_BITS(v)   (HW_OCOTP_OTPMK3_WR((HW_OCOTP_OTPMK3_RD() & ~BM_OCOTP_OTPMK3_BITS) | BF_OCOTP_OTPMK3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK4 - Shadow Register for OTP Bank2 Word4 (OTPMK Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK4 - Shadow Register for OTP Bank2 Word4 (OTPMK Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 4 (ADDR =
 * 0x14).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk4
{
    reg32_t U;
    struct _hw_ocotp_otpmk4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word4 (Copy of OTP Bank 2, word 4 (ADDR = 0x14)).
    } B;
} hw_ocotp_otpmk4_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK4 register
 */
#define HW_OCOTP_OTPMK4_ADDR      (REGS_OCOTP_BASE + 0x540)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK4           (*(volatile hw_ocotp_otpmk4_t *) HW_OCOTP_OTPMK4_ADDR)
#define HW_OCOTP_OTPMK4_RD()      (HW_OCOTP_OTPMK4.U)
#define HW_OCOTP_OTPMK4_WR(v)     (HW_OCOTP_OTPMK4.U = (v))
#define HW_OCOTP_OTPMK4_SET(v)    (HW_OCOTP_OTPMK4_WR(HW_OCOTP_OTPMK4_RD() |  (v)))
#define HW_OCOTP_OTPMK4_CLR(v)    (HW_OCOTP_OTPMK4_WR(HW_OCOTP_OTPMK4_RD() & ~(v)))
#define HW_OCOTP_OTPMK4_TOG(v)    (HW_OCOTP_OTPMK4_WR(HW_OCOTP_OTPMK4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK4 bitfields
 */

/* --- Register HW_OCOTP_OTPMK4, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word4 (Copy of OTP Bank 2, word 4 (ADDR = 0x14)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK4_BITS      (0)      //!< Bit position for OCOTP_OTPMK4_BITS.
#define BM_OCOTP_OTPMK4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK4_BITS.

//! @brief Get value of OCOTP_OTPMK4_BITS from a register value.
#define BG_OCOTP_OTPMK4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK4_BITS) >> BP_OCOTP_OTPMK4_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK4_BITS.
#define BF_OCOTP_OTPMK4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK4_BITS) & BM_OCOTP_OTPMK4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK4_BITS(v)   (HW_OCOTP_OTPMK4_WR((HW_OCOTP_OTPMK4_RD() & ~BM_OCOTP_OTPMK4_BITS) | BF_OCOTP_OTPMK4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK5 - Shadow Register for OTP Bank2 Word5 (OTPMK Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK5 - Shadow Register for OTP Bank2 Word5 (OTPMK Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 5 (ADDR =
 * 0x15).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk5
{
    reg32_t U;
    struct _hw_ocotp_otpmk5_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word5 (Copy of OTP Bank 2, word 5 (ADDR = 0x15)).
    } B;
} hw_ocotp_otpmk5_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK5 register
 */
#define HW_OCOTP_OTPMK5_ADDR      (REGS_OCOTP_BASE + 0x550)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK5           (*(volatile hw_ocotp_otpmk5_t *) HW_OCOTP_OTPMK5_ADDR)
#define HW_OCOTP_OTPMK5_RD()      (HW_OCOTP_OTPMK5.U)
#define HW_OCOTP_OTPMK5_WR(v)     (HW_OCOTP_OTPMK5.U = (v))
#define HW_OCOTP_OTPMK5_SET(v)    (HW_OCOTP_OTPMK5_WR(HW_OCOTP_OTPMK5_RD() |  (v)))
#define HW_OCOTP_OTPMK5_CLR(v)    (HW_OCOTP_OTPMK5_WR(HW_OCOTP_OTPMK5_RD() & ~(v)))
#define HW_OCOTP_OTPMK5_TOG(v)    (HW_OCOTP_OTPMK5_WR(HW_OCOTP_OTPMK5_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK5 bitfields
 */

/* --- Register HW_OCOTP_OTPMK5, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word5 (Copy of OTP Bank 2, word 5 (ADDR = 0x15)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK5_BITS      (0)      //!< Bit position for OCOTP_OTPMK5_BITS.
#define BM_OCOTP_OTPMK5_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK5_BITS.

//! @brief Get value of OCOTP_OTPMK5_BITS from a register value.
#define BG_OCOTP_OTPMK5_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK5_BITS) >> BP_OCOTP_OTPMK5_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK5_BITS.
#define BF_OCOTP_OTPMK5_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK5_BITS) & BM_OCOTP_OTPMK5_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK5_BITS(v)   (HW_OCOTP_OTPMK5_WR((HW_OCOTP_OTPMK5_RD() & ~BM_OCOTP_OTPMK5_BITS) | BF_OCOTP_OTPMK5_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK6 - Shadow Register for OTP Bank2 Word6 (OTPMK Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK6 - Shadow Register for OTP Bank2 Word6 (OTPMK Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 6 (ADDR =
 * 0x16).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk6
{
    reg32_t U;
    struct _hw_ocotp_otpmk6_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word6 (Copy of OTP Bank 2, word 6 (ADDR = 0x16)).
    } B;
} hw_ocotp_otpmk6_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK6 register
 */
#define HW_OCOTP_OTPMK6_ADDR      (REGS_OCOTP_BASE + 0x560)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK6           (*(volatile hw_ocotp_otpmk6_t *) HW_OCOTP_OTPMK6_ADDR)
#define HW_OCOTP_OTPMK6_RD()      (HW_OCOTP_OTPMK6.U)
#define HW_OCOTP_OTPMK6_WR(v)     (HW_OCOTP_OTPMK6.U = (v))
#define HW_OCOTP_OTPMK6_SET(v)    (HW_OCOTP_OTPMK6_WR(HW_OCOTP_OTPMK6_RD() |  (v)))
#define HW_OCOTP_OTPMK6_CLR(v)    (HW_OCOTP_OTPMK6_WR(HW_OCOTP_OTPMK6_RD() & ~(v)))
#define HW_OCOTP_OTPMK6_TOG(v)    (HW_OCOTP_OTPMK6_WR(HW_OCOTP_OTPMK6_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK6 bitfields
 */

/* --- Register HW_OCOTP_OTPMK6, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word6 (Copy of OTP Bank 2, word 6 (ADDR = 0x16)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK6_BITS      (0)      //!< Bit position for OCOTP_OTPMK6_BITS.
#define BM_OCOTP_OTPMK6_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK6_BITS.

//! @brief Get value of OCOTP_OTPMK6_BITS from a register value.
#define BG_OCOTP_OTPMK6_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK6_BITS) >> BP_OCOTP_OTPMK6_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK6_BITS.
#define BF_OCOTP_OTPMK6_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK6_BITS) & BM_OCOTP_OTPMK6_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK6_BITS(v)   (HW_OCOTP_OTPMK6_WR((HW_OCOTP_OTPMK6_RD() & ~BM_OCOTP_OTPMK6_BITS) | BF_OCOTP_OTPMK6_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_OTPMK7 - Shadow Register for OTP Bank2 Word7 (OTPMK Key)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_OTPMK7 - Shadow Register for OTP Bank2 Word7 (OTPMK Key) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 2, word 7 (ADDR =
 * 0x17).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_otpmk7
{
    reg32_t U;
    struct _hw_ocotp_otpmk7_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the OTPMK Key word7 (Copy of OTP Bank 2, word 7 (ADDR = 0x17)).
    } B;
} hw_ocotp_otpmk7_t;
#endif

/*
 * constants & macros for entire OCOTP_OTPMK7 register
 */
#define HW_OCOTP_OTPMK7_ADDR      (REGS_OCOTP_BASE + 0x570)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_OTPMK7           (*(volatile hw_ocotp_otpmk7_t *) HW_OCOTP_OTPMK7_ADDR)
#define HW_OCOTP_OTPMK7_RD()      (HW_OCOTP_OTPMK7.U)
#define HW_OCOTP_OTPMK7_WR(v)     (HW_OCOTP_OTPMK7.U = (v))
#define HW_OCOTP_OTPMK7_SET(v)    (HW_OCOTP_OTPMK7_WR(HW_OCOTP_OTPMK7_RD() |  (v)))
#define HW_OCOTP_OTPMK7_CLR(v)    (HW_OCOTP_OTPMK7_WR(HW_OCOTP_OTPMK7_RD() & ~(v)))
#define HW_OCOTP_OTPMK7_TOG(v)    (HW_OCOTP_OTPMK7_WR(HW_OCOTP_OTPMK7_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_OTPMK7 bitfields
 */

/* --- Register HW_OCOTP_OTPMK7, field BITS[31:0] (RW)
 *
 * Shadow register for the OTPMK Key word7 (Copy of OTP Bank 2, word 7 (ADDR = 0x17)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_OTPMK bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_OTPMK7_BITS      (0)      //!< Bit position for OCOTP_OTPMK7_BITS.
#define BM_OCOTP_OTPMK7_BITS      (0xffffffff)  //!< Bit mask for OCOTP_OTPMK7_BITS.

//! @brief Get value of OCOTP_OTPMK7_BITS from a register value.
#define BG_OCOTP_OTPMK7_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_OTPMK7_BITS) >> BP_OCOTP_OTPMK7_BITS)

//! @brief Format value for bitfield OCOTP_OTPMK7_BITS.
#define BF_OCOTP_OTPMK7_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_OTPMK7_BITS) & BM_OCOTP_OTPMK7_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_OTPMK7_BITS(v)   (HW_OCOTP_OTPMK7_WR((HW_OCOTP_OTPMK7_RD() & ~BM_OCOTP_OTPMK7_BITS) | BF_OCOTP_OTPMK7_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK0 - Shadow Register for OTP Bank3 Word0 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK0 - Shadow Register for OTP Bank3 Word0 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 0 (ADDR =
 * 0x18).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk0
{
    reg32_t U;
    struct _hw_ocotp_srk0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word0 (Copy of OTP Bank 3, word 0 (ADDR = 0x1C)).
    } B;
} hw_ocotp_srk0_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK0 register
 */
#define HW_OCOTP_SRK0_ADDR      (REGS_OCOTP_BASE + 0x580)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK0           (*(volatile hw_ocotp_srk0_t *) HW_OCOTP_SRK0_ADDR)
#define HW_OCOTP_SRK0_RD()      (HW_OCOTP_SRK0.U)
#define HW_OCOTP_SRK0_WR(v)     (HW_OCOTP_SRK0.U = (v))
#define HW_OCOTP_SRK0_SET(v)    (HW_OCOTP_SRK0_WR(HW_OCOTP_SRK0_RD() |  (v)))
#define HW_OCOTP_SRK0_CLR(v)    (HW_OCOTP_SRK0_WR(HW_OCOTP_SRK0_RD() & ~(v)))
#define HW_OCOTP_SRK0_TOG(v)    (HW_OCOTP_SRK0_WR(HW_OCOTP_SRK0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK0 bitfields
 */

/* --- Register HW_OCOTP_SRK0, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word0 (Copy of OTP Bank 3, word 0 (ADDR =
 * 0x1C)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK0_BITS      (0)      //!< Bit position for OCOTP_SRK0_BITS.
#define BM_OCOTP_SRK0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK0_BITS.

//! @brief Get value of OCOTP_SRK0_BITS from a register value.
#define BG_OCOTP_SRK0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK0_BITS) >> BP_OCOTP_SRK0_BITS)

//! @brief Format value for bitfield OCOTP_SRK0_BITS.
#define BF_OCOTP_SRK0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK0_BITS) & BM_OCOTP_SRK0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK0_BITS(v)   (HW_OCOTP_SRK0_WR((HW_OCOTP_SRK0_RD() & ~BM_OCOTP_SRK0_BITS) | BF_OCOTP_SRK0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK1 - Shadow Register for OTP Bank3 Word1 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK1 - Shadow Register for OTP Bank3 Word1 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 1 (ADDR =
 * 0x19).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk1
{
    reg32_t U;
    struct _hw_ocotp_srk1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word1 (Copy of OTP Bank 3, word 1 (ADDR = 0x1D)).
    } B;
} hw_ocotp_srk1_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK1 register
 */
#define HW_OCOTP_SRK1_ADDR      (REGS_OCOTP_BASE + 0x590)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK1           (*(volatile hw_ocotp_srk1_t *) HW_OCOTP_SRK1_ADDR)
#define HW_OCOTP_SRK1_RD()      (HW_OCOTP_SRK1.U)
#define HW_OCOTP_SRK1_WR(v)     (HW_OCOTP_SRK1.U = (v))
#define HW_OCOTP_SRK1_SET(v)    (HW_OCOTP_SRK1_WR(HW_OCOTP_SRK1_RD() |  (v)))
#define HW_OCOTP_SRK1_CLR(v)    (HW_OCOTP_SRK1_WR(HW_OCOTP_SRK1_RD() & ~(v)))
#define HW_OCOTP_SRK1_TOG(v)    (HW_OCOTP_SRK1_WR(HW_OCOTP_SRK1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK1 bitfields
 */

/* --- Register HW_OCOTP_SRK1, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word1 (Copy of OTP Bank 3, word 1 (ADDR =
 * 0x1D)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK1_BITS      (0)      //!< Bit position for OCOTP_SRK1_BITS.
#define BM_OCOTP_SRK1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK1_BITS.

//! @brief Get value of OCOTP_SRK1_BITS from a register value.
#define BG_OCOTP_SRK1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK1_BITS) >> BP_OCOTP_SRK1_BITS)

//! @brief Format value for bitfield OCOTP_SRK1_BITS.
#define BF_OCOTP_SRK1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK1_BITS) & BM_OCOTP_SRK1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK1_BITS(v)   (HW_OCOTP_SRK1_WR((HW_OCOTP_SRK1_RD() & ~BM_OCOTP_SRK1_BITS) | BF_OCOTP_SRK1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK2 - Shadow Register for OTP Bank3 Word2 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK2 - Shadow Register for OTP Bank3 Word2 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 2 (ADDR =
 * 0x1A).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk2
{
    reg32_t U;
    struct _hw_ocotp_srk2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word2 (Copy of OTP Bank 3, word 2 (ADDR = 0x1E)).
    } B;
} hw_ocotp_srk2_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK2 register
 */
#define HW_OCOTP_SRK2_ADDR      (REGS_OCOTP_BASE + 0x5a0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK2           (*(volatile hw_ocotp_srk2_t *) HW_OCOTP_SRK2_ADDR)
#define HW_OCOTP_SRK2_RD()      (HW_OCOTP_SRK2.U)
#define HW_OCOTP_SRK2_WR(v)     (HW_OCOTP_SRK2.U = (v))
#define HW_OCOTP_SRK2_SET(v)    (HW_OCOTP_SRK2_WR(HW_OCOTP_SRK2_RD() |  (v)))
#define HW_OCOTP_SRK2_CLR(v)    (HW_OCOTP_SRK2_WR(HW_OCOTP_SRK2_RD() & ~(v)))
#define HW_OCOTP_SRK2_TOG(v)    (HW_OCOTP_SRK2_WR(HW_OCOTP_SRK2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK2 bitfields
 */

/* --- Register HW_OCOTP_SRK2, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word2 (Copy of OTP Bank 3, word 2 (ADDR =
 * 0x1E)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK2_BITS      (0)      //!< Bit position for OCOTP_SRK2_BITS.
#define BM_OCOTP_SRK2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK2_BITS.

//! @brief Get value of OCOTP_SRK2_BITS from a register value.
#define BG_OCOTP_SRK2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK2_BITS) >> BP_OCOTP_SRK2_BITS)

//! @brief Format value for bitfield OCOTP_SRK2_BITS.
#define BF_OCOTP_SRK2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK2_BITS) & BM_OCOTP_SRK2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK2_BITS(v)   (HW_OCOTP_SRK2_WR((HW_OCOTP_SRK2_RD() & ~BM_OCOTP_SRK2_BITS) | BF_OCOTP_SRK2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK3 - Shadow Register for OTP Bank3 Word3 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK3 - Shadow Register for OTP Bank3 Word3 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 3 (ADDR =
 * 0x1B).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk3
{
    reg32_t U;
    struct _hw_ocotp_srk3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word3 (Copy of OTP Bank 3, word 3 (ADDR = 0x1F)).
    } B;
} hw_ocotp_srk3_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK3 register
 */
#define HW_OCOTP_SRK3_ADDR      (REGS_OCOTP_BASE + 0x5b0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK3           (*(volatile hw_ocotp_srk3_t *) HW_OCOTP_SRK3_ADDR)
#define HW_OCOTP_SRK3_RD()      (HW_OCOTP_SRK3.U)
#define HW_OCOTP_SRK3_WR(v)     (HW_OCOTP_SRK3.U = (v))
#define HW_OCOTP_SRK3_SET(v)    (HW_OCOTP_SRK3_WR(HW_OCOTP_SRK3_RD() |  (v)))
#define HW_OCOTP_SRK3_CLR(v)    (HW_OCOTP_SRK3_WR(HW_OCOTP_SRK3_RD() & ~(v)))
#define HW_OCOTP_SRK3_TOG(v)    (HW_OCOTP_SRK3_WR(HW_OCOTP_SRK3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK3 bitfields
 */

/* --- Register HW_OCOTP_SRK3, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word3 (Copy of OTP Bank 3, word 3 (ADDR =
 * 0x1F)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK3_BITS      (0)      //!< Bit position for OCOTP_SRK3_BITS.
#define BM_OCOTP_SRK3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK3_BITS.

//! @brief Get value of OCOTP_SRK3_BITS from a register value.
#define BG_OCOTP_SRK3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK3_BITS) >> BP_OCOTP_SRK3_BITS)

//! @brief Format value for bitfield OCOTP_SRK3_BITS.
#define BF_OCOTP_SRK3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK3_BITS) & BM_OCOTP_SRK3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK3_BITS(v)   (HW_OCOTP_SRK3_WR((HW_OCOTP_SRK3_RD() & ~BM_OCOTP_SRK3_BITS) | BF_OCOTP_SRK3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK4 - Shadow Register for OTP Bank3 Word4 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK4 - Shadow Register for OTP Bank3 Word4 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 4 (ADDR =
 * 0x1C).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk4
{
    reg32_t U;
    struct _hw_ocotp_srk4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word4 (Copy of OTP Bank 3, word 4 (ADDR = 0x20)).
    } B;
} hw_ocotp_srk4_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK4 register
 */
#define HW_OCOTP_SRK4_ADDR      (REGS_OCOTP_BASE + 0x5c0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK4           (*(volatile hw_ocotp_srk4_t *) HW_OCOTP_SRK4_ADDR)
#define HW_OCOTP_SRK4_RD()      (HW_OCOTP_SRK4.U)
#define HW_OCOTP_SRK4_WR(v)     (HW_OCOTP_SRK4.U = (v))
#define HW_OCOTP_SRK4_SET(v)    (HW_OCOTP_SRK4_WR(HW_OCOTP_SRK4_RD() |  (v)))
#define HW_OCOTP_SRK4_CLR(v)    (HW_OCOTP_SRK4_WR(HW_OCOTP_SRK4_RD() & ~(v)))
#define HW_OCOTP_SRK4_TOG(v)    (HW_OCOTP_SRK4_WR(HW_OCOTP_SRK4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK4 bitfields
 */

/* --- Register HW_OCOTP_SRK4, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word4 (Copy of OTP Bank 3, word 4 (ADDR =
 * 0x20)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK4_BITS      (0)      //!< Bit position for OCOTP_SRK4_BITS.
#define BM_OCOTP_SRK4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK4_BITS.

//! @brief Get value of OCOTP_SRK4_BITS from a register value.
#define BG_OCOTP_SRK4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK4_BITS) >> BP_OCOTP_SRK4_BITS)

//! @brief Format value for bitfield OCOTP_SRK4_BITS.
#define BF_OCOTP_SRK4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK4_BITS) & BM_OCOTP_SRK4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK4_BITS(v)   (HW_OCOTP_SRK4_WR((HW_OCOTP_SRK4_RD() & ~BM_OCOTP_SRK4_BITS) | BF_OCOTP_SRK4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK5 - Shadow Register for OTP Bank3 Word5 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK5 - Shadow Register for OTP Bank3 Word5 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 5 (ADDR =
 * 0x1D).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk5
{
    reg32_t U;
    struct _hw_ocotp_srk5_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word5 (Copy of OTP Bank 3, word 5 (ADDR = 0x21)).
    } B;
} hw_ocotp_srk5_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK5 register
 */
#define HW_OCOTP_SRK5_ADDR      (REGS_OCOTP_BASE + 0x5d0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK5           (*(volatile hw_ocotp_srk5_t *) HW_OCOTP_SRK5_ADDR)
#define HW_OCOTP_SRK5_RD()      (HW_OCOTP_SRK5.U)
#define HW_OCOTP_SRK5_WR(v)     (HW_OCOTP_SRK5.U = (v))
#define HW_OCOTP_SRK5_SET(v)    (HW_OCOTP_SRK5_WR(HW_OCOTP_SRK5_RD() |  (v)))
#define HW_OCOTP_SRK5_CLR(v)    (HW_OCOTP_SRK5_WR(HW_OCOTP_SRK5_RD() & ~(v)))
#define HW_OCOTP_SRK5_TOG(v)    (HW_OCOTP_SRK5_WR(HW_OCOTP_SRK5_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK5 bitfields
 */

/* --- Register HW_OCOTP_SRK5, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word5 (Copy of OTP Bank 3, word 5 (ADDR =
 * 0x21)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK5_BITS      (0)      //!< Bit position for OCOTP_SRK5_BITS.
#define BM_OCOTP_SRK5_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK5_BITS.

//! @brief Get value of OCOTP_SRK5_BITS from a register value.
#define BG_OCOTP_SRK5_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK5_BITS) >> BP_OCOTP_SRK5_BITS)

//! @brief Format value for bitfield OCOTP_SRK5_BITS.
#define BF_OCOTP_SRK5_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK5_BITS) & BM_OCOTP_SRK5_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK5_BITS(v)   (HW_OCOTP_SRK5_WR((HW_OCOTP_SRK5_RD() & ~BM_OCOTP_SRK5_BITS) | BF_OCOTP_SRK5_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK6 - Shadow Register for OTP Bank3 Word6 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK6 - Shadow Register for OTP Bank3 Word6 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 6 (ADDR =
 * 0x1E).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk6
{
    reg32_t U;
    struct _hw_ocotp_srk6_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word6 (Copy of OTP Bank 3, word 6 (ADDR = 0x22)).
    } B;
} hw_ocotp_srk6_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK6 register
 */
#define HW_OCOTP_SRK6_ADDR      (REGS_OCOTP_BASE + 0x5e0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK6           (*(volatile hw_ocotp_srk6_t *) HW_OCOTP_SRK6_ADDR)
#define HW_OCOTP_SRK6_RD()      (HW_OCOTP_SRK6.U)
#define HW_OCOTP_SRK6_WR(v)     (HW_OCOTP_SRK6.U = (v))
#define HW_OCOTP_SRK6_SET(v)    (HW_OCOTP_SRK6_WR(HW_OCOTP_SRK6_RD() |  (v)))
#define HW_OCOTP_SRK6_CLR(v)    (HW_OCOTP_SRK6_WR(HW_OCOTP_SRK6_RD() & ~(v)))
#define HW_OCOTP_SRK6_TOG(v)    (HW_OCOTP_SRK6_WR(HW_OCOTP_SRK6_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK6 bitfields
 */

/* --- Register HW_OCOTP_SRK6, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word6 (Copy of OTP Bank 3, word 6 (ADDR =
 * 0x22)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK6_BITS      (0)      //!< Bit position for OCOTP_SRK6_BITS.
#define BM_OCOTP_SRK6_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK6_BITS.

//! @brief Get value of OCOTP_SRK6_BITS from a register value.
#define BG_OCOTP_SRK6_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK6_BITS) >> BP_OCOTP_SRK6_BITS)

//! @brief Format value for bitfield OCOTP_SRK6_BITS.
#define BF_OCOTP_SRK6_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK6_BITS) & BM_OCOTP_SRK6_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK6_BITS(v)   (HW_OCOTP_SRK6_WR((HW_OCOTP_SRK6_RD() & ~BM_OCOTP_SRK6_BITS) | BF_OCOTP_SRK6_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK7 - Shadow Register for OTP Bank3 Word7 (SRK Hash)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK7 - Shadow Register for OTP Bank3 Word7 (SRK Hash) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS].  Shadowed memory mapped access to OTP Bank 3, word 7 (ADDR =
 * 0x1F).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk7
{
    reg32_t U;
    struct _hw_ocotp_srk7_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the hash of the Super Root Key word7 (Copy of OTP Bank 3, word 7 (ADDR = 0x23)).
    } B;
} hw_ocotp_srk7_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK7 register
 */
#define HW_OCOTP_SRK7_ADDR      (REGS_OCOTP_BASE + 0x5f0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK7           (*(volatile hw_ocotp_srk7_t *) HW_OCOTP_SRK7_ADDR)
#define HW_OCOTP_SRK7_RD()      (HW_OCOTP_SRK7.U)
#define HW_OCOTP_SRK7_WR(v)     (HW_OCOTP_SRK7.U = (v))
#define HW_OCOTP_SRK7_SET(v)    (HW_OCOTP_SRK7_WR(HW_OCOTP_SRK7_RD() |  (v)))
#define HW_OCOTP_SRK7_CLR(v)    (HW_OCOTP_SRK7_WR(HW_OCOTP_SRK7_RD() & ~(v)))
#define HW_OCOTP_SRK7_TOG(v)    (HW_OCOTP_SRK7_WR(HW_OCOTP_SRK7_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK7 bitfields
 */

/* --- Register HW_OCOTP_SRK7, field BITS[31:0] (RW)
 *
 * Shadow register for the hash of the Super Root Key word7 (Copy of OTP Bank 3, word 7 (ADDR =
 * 0x23)). These bits become read-only after the HW_OCOTP_LOCK_SRK bit is set.
 */

#define BP_OCOTP_SRK7_BITS      (0)      //!< Bit position for OCOTP_SRK7_BITS.
#define BM_OCOTP_SRK7_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK7_BITS.

//! @brief Get value of OCOTP_SRK7_BITS from a register value.
#define BG_OCOTP_SRK7_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK7_BITS) >> BP_OCOTP_SRK7_BITS)

//! @brief Format value for bitfield OCOTP_SRK7_BITS.
#define BF_OCOTP_SRK7_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK7_BITS) & BM_OCOTP_SRK7_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK7_BITS(v)   (HW_OCOTP_SRK7_WR((HW_OCOTP_SRK7_RD() & ~BM_OCOTP_SRK7_BITS) | BF_OCOTP_SRK7_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_RESP0 - Value of OTP Bank4 Word0 (Secure JTAG Response Field)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_RESP0 - Value of OTP Bank4 Word0 (Secure JTAG Response Field) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 0 (ADDR = 0x20).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_resp0
{
    reg32_t U;
    struct _hw_ocotp_resp0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the SJC_RESP Key word0 (Copy of OTP Bank 4, word 0 (ADDR = 0x20)).
    } B;
} hw_ocotp_resp0_t;
#endif

/*
 * constants & macros for entire OCOTP_RESP0 register
 */
#define HW_OCOTP_RESP0_ADDR      (REGS_OCOTP_BASE + 0x600)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_RESP0           (*(volatile hw_ocotp_resp0_t *) HW_OCOTP_RESP0_ADDR)
#define HW_OCOTP_RESP0_RD()      (HW_OCOTP_RESP0.U)
#define HW_OCOTP_RESP0_WR(v)     (HW_OCOTP_RESP0.U = (v))
#define HW_OCOTP_RESP0_SET(v)    (HW_OCOTP_RESP0_WR(HW_OCOTP_RESP0_RD() |  (v)))
#define HW_OCOTP_RESP0_CLR(v)    (HW_OCOTP_RESP0_WR(HW_OCOTP_RESP0_RD() & ~(v)))
#define HW_OCOTP_RESP0_TOG(v)    (HW_OCOTP_RESP0_WR(HW_OCOTP_RESP0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_RESP0 bitfields
 */

/* --- Register HW_OCOTP_RESP0, field BITS[31:0] (RW)
 *
 * Shadow register for the SJC_RESP Key word0 (Copy of OTP Bank 4, word 0 (ADDR = 0x20)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_SJC_RESP bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_RESP0_BITS      (0)      //!< Bit position for OCOTP_RESP0_BITS.
#define BM_OCOTP_RESP0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_RESP0_BITS.

//! @brief Get value of OCOTP_RESP0_BITS from a register value.
#define BG_OCOTP_RESP0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_RESP0_BITS) >> BP_OCOTP_RESP0_BITS)

//! @brief Format value for bitfield OCOTP_RESP0_BITS.
#define BF_OCOTP_RESP0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_RESP0_BITS) & BM_OCOTP_RESP0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_RESP0_BITS(v)   (HW_OCOTP_RESP0_WR((HW_OCOTP_RESP0_RD() & ~BM_OCOTP_RESP0_BITS) | BF_OCOTP_RESP0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HSJC_RESP1 - Value of OTP Bank4 Word1 (Secure JTAG Response Field)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HSJC_RESP1 - Value of OTP Bank4 Word1 (Secure JTAG Response Field) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 1 (ADDR = 0x21).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hsjc_resp1
{
    reg32_t U;
    struct _hw_ocotp_hsjc_resp1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Shadow register for the SJC_RESP Key word1 (Copy of OTP Bank 4, word 1 (ADDR = 0x21)).
    } B;
} hw_ocotp_hsjc_resp1_t;
#endif

/*
 * constants & macros for entire OCOTP_HSJC_RESP1 register
 */
#define HW_OCOTP_HSJC_RESP1_ADDR      (REGS_OCOTP_BASE + 0x610)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HSJC_RESP1           (*(volatile hw_ocotp_hsjc_resp1_t *) HW_OCOTP_HSJC_RESP1_ADDR)
#define HW_OCOTP_HSJC_RESP1_RD()      (HW_OCOTP_HSJC_RESP1.U)
#define HW_OCOTP_HSJC_RESP1_WR(v)     (HW_OCOTP_HSJC_RESP1.U = (v))
#define HW_OCOTP_HSJC_RESP1_SET(v)    (HW_OCOTP_HSJC_RESP1_WR(HW_OCOTP_HSJC_RESP1_RD() |  (v)))
#define HW_OCOTP_HSJC_RESP1_CLR(v)    (HW_OCOTP_HSJC_RESP1_WR(HW_OCOTP_HSJC_RESP1_RD() & ~(v)))
#define HW_OCOTP_HSJC_RESP1_TOG(v)    (HW_OCOTP_HSJC_RESP1_WR(HW_OCOTP_HSJC_RESP1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HSJC_RESP1 bitfields
 */

/* --- Register HW_OCOTP_HSJC_RESP1, field BITS[31:0] (RW)
 *
 * Shadow register for the SJC_RESP Key word1 (Copy of OTP Bank 4, word 1 (ADDR = 0x21)). These bits
 * can be not read and wrotten after the HW_OCOTP_LOCK_SJC_RESP bit is set. If read, returns
 * 0xBADA_BADA and sets HW_OCOTP_CTRL[ERROR].
 */

#define BP_OCOTP_HSJC_RESP1_BITS      (0)      //!< Bit position for OCOTP_HSJC_RESP1_BITS.
#define BM_OCOTP_HSJC_RESP1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HSJC_RESP1_BITS.

//! @brief Get value of OCOTP_HSJC_RESP1_BITS from a register value.
#define BG_OCOTP_HSJC_RESP1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HSJC_RESP1_BITS) >> BP_OCOTP_HSJC_RESP1_BITS)

//! @brief Format value for bitfield OCOTP_HSJC_RESP1_BITS.
#define BF_OCOTP_HSJC_RESP1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HSJC_RESP1_BITS) & BM_OCOTP_HSJC_RESP1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HSJC_RESP1_BITS(v)   (HW_OCOTP_HSJC_RESP1_WR((HW_OCOTP_HSJC_RESP1_RD() & ~BM_OCOTP_HSJC_RESP1_BITS) | BF_OCOTP_HSJC_RESP1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MAC0 - Value of OTP Bank4 Word2 (MAC Address)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MAC0 - Value of OTP Bank4 Word2 (MAC Address) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 2 (ADDR = 0x22).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mac0
{
    reg32_t U;
    struct _hw_ocotp_mac0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 2 (ADDR = 0x22).
    } B;
} hw_ocotp_mac0_t;
#endif

/*
 * constants & macros for entire OCOTP_MAC0 register
 */
#define HW_OCOTP_MAC0_ADDR      (REGS_OCOTP_BASE + 0x620)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MAC0           (*(volatile hw_ocotp_mac0_t *) HW_OCOTP_MAC0_ADDR)
#define HW_OCOTP_MAC0_RD()      (HW_OCOTP_MAC0.U)
#define HW_OCOTP_MAC0_WR(v)     (HW_OCOTP_MAC0.U = (v))
#define HW_OCOTP_MAC0_SET(v)    (HW_OCOTP_MAC0_WR(HW_OCOTP_MAC0_RD() |  (v)))
#define HW_OCOTP_MAC0_CLR(v)    (HW_OCOTP_MAC0_WR(HW_OCOTP_MAC0_RD() & ~(v)))
#define HW_OCOTP_MAC0_TOG(v)    (HW_OCOTP_MAC0_WR(HW_OCOTP_MAC0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MAC0 bitfields
 */

/* --- Register HW_OCOTP_MAC0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 2 (ADDR = 0x22).
 */

#define BP_OCOTP_MAC0_BITS      (0)      //!< Bit position for OCOTP_MAC0_BITS.
#define BM_OCOTP_MAC0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MAC0_BITS.

//! @brief Get value of OCOTP_MAC0_BITS from a register value.
#define BG_OCOTP_MAC0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MAC0_BITS) >> BP_OCOTP_MAC0_BITS)

//! @brief Format value for bitfield OCOTP_MAC0_BITS.
#define BF_OCOTP_MAC0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MAC0_BITS) & BM_OCOTP_MAC0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MAC0_BITS(v)   (HW_OCOTP_MAC0_WR((HW_OCOTP_MAC0_RD() & ~BM_OCOTP_MAC0_BITS) | BF_OCOTP_MAC0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MAC1 - Value of OTP Bank4 Word3 (MAC Address)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MAC1 - Value of OTP Bank4 Word3 (MAC Address) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 3 (ADDR = 0x23).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_mac1
{
    reg32_t U;
    struct _hw_ocotp_mac1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 3 (ADDR = 0x23).
    } B;
} hw_ocotp_mac1_t;
#endif

/*
 * constants & macros for entire OCOTP_MAC1 register
 */
#define HW_OCOTP_MAC1_ADDR      (REGS_OCOTP_BASE + 0x630)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MAC1           (*(volatile hw_ocotp_mac1_t *) HW_OCOTP_MAC1_ADDR)
#define HW_OCOTP_MAC1_RD()      (HW_OCOTP_MAC1.U)
#define HW_OCOTP_MAC1_WR(v)     (HW_OCOTP_MAC1.U = (v))
#define HW_OCOTP_MAC1_SET(v)    (HW_OCOTP_MAC1_WR(HW_OCOTP_MAC1_RD() |  (v)))
#define HW_OCOTP_MAC1_CLR(v)    (HW_OCOTP_MAC1_WR(HW_OCOTP_MAC1_RD() & ~(v)))
#define HW_OCOTP_MAC1_TOG(v)    (HW_OCOTP_MAC1_WR(HW_OCOTP_MAC1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MAC1 bitfields
 */

/* --- Register HW_OCOTP_MAC1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 3 (ADDR = 0x23).
 */

#define BP_OCOTP_MAC1_BITS      (0)      //!< Bit position for OCOTP_MAC1_BITS.
#define BM_OCOTP_MAC1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MAC1_BITS.

//! @brief Get value of OCOTP_MAC1_BITS from a register value.
#define BG_OCOTP_MAC1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MAC1_BITS) >> BP_OCOTP_MAC1_BITS)

//! @brief Format value for bitfield OCOTP_MAC1_BITS.
#define BF_OCOTP_MAC1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MAC1_BITS) & BM_OCOTP_MAC1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MAC1_BITS(v)   (HW_OCOTP_MAC1_WR((HW_OCOTP_MAC1_RD() & ~BM_OCOTP_MAC1_BITS) | BF_OCOTP_MAC1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KSV0 - Value of OTP Bank4 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KSV0 - Value of OTP Bank4 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 4 (ADDR = 0x24).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_ksv0
{
    reg32_t U;
    struct _hw_ocotp_hdcp_ksv0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 4 (ADDR = 0x24).
    } B;
} hw_ocotp_hdcp_ksv0_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KSV0 register
 */
#define HW_OCOTP_HDCP_KSV0_ADDR      (REGS_OCOTP_BASE + 0x640)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KSV0           (*(volatile hw_ocotp_hdcp_ksv0_t *) HW_OCOTP_HDCP_KSV0_ADDR)
#define HW_OCOTP_HDCP_KSV0_RD()      (HW_OCOTP_HDCP_KSV0.U)
#define HW_OCOTP_HDCP_KSV0_WR(v)     (HW_OCOTP_HDCP_KSV0.U = (v))
#define HW_OCOTP_HDCP_KSV0_SET(v)    (HW_OCOTP_HDCP_KSV0_WR(HW_OCOTP_HDCP_KSV0_RD() |  (v)))
#define HW_OCOTP_HDCP_KSV0_CLR(v)    (HW_OCOTP_HDCP_KSV0_WR(HW_OCOTP_HDCP_KSV0_RD() & ~(v)))
#define HW_OCOTP_HDCP_KSV0_TOG(v)    (HW_OCOTP_HDCP_KSV0_WR(HW_OCOTP_HDCP_KSV0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KSV0 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KSV0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 4 (ADDR = 0x24).
 */

#define BP_OCOTP_HDCP_KSV0_BITS      (0)      //!< Bit position for OCOTP_HDCP_KSV0_BITS.
#define BM_OCOTP_HDCP_KSV0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KSV0_BITS.

//! @brief Get value of OCOTP_HDCP_KSV0_BITS from a register value.
#define BG_OCOTP_HDCP_KSV0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KSV0_BITS) >> BP_OCOTP_HDCP_KSV0_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KSV0_BITS.
#define BF_OCOTP_HDCP_KSV0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KSV0_BITS) & BM_OCOTP_HDCP_KSV0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KSV0_BITS(v)   (HW_OCOTP_HDCP_KSV0_WR((HW_OCOTP_HDCP_KSV0_RD() & ~BM_OCOTP_HDCP_KSV0_BITS) | BF_OCOTP_HDCP_KSV0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KSV1 - Value of OTP Bank4 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KSV1 - Value of OTP Bank4 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 5 (ADDR = 0x25).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_ksv1
{
    reg32_t U;
    struct _hw_ocotp_hdcp_ksv1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 5 (ADDR = 0x25).
    } B;
} hw_ocotp_hdcp_ksv1_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KSV1 register
 */
#define HW_OCOTP_HDCP_KSV1_ADDR      (REGS_OCOTP_BASE + 0x650)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KSV1           (*(volatile hw_ocotp_hdcp_ksv1_t *) HW_OCOTP_HDCP_KSV1_ADDR)
#define HW_OCOTP_HDCP_KSV1_RD()      (HW_OCOTP_HDCP_KSV1.U)
#define HW_OCOTP_HDCP_KSV1_WR(v)     (HW_OCOTP_HDCP_KSV1.U = (v))
#define HW_OCOTP_HDCP_KSV1_SET(v)    (HW_OCOTP_HDCP_KSV1_WR(HW_OCOTP_HDCP_KSV1_RD() |  (v)))
#define HW_OCOTP_HDCP_KSV1_CLR(v)    (HW_OCOTP_HDCP_KSV1_WR(HW_OCOTP_HDCP_KSV1_RD() & ~(v)))
#define HW_OCOTP_HDCP_KSV1_TOG(v)    (HW_OCOTP_HDCP_KSV1_WR(HW_OCOTP_HDCP_KSV1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KSV1 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KSV1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 5 (ADDR = 0x25).
 */

#define BP_OCOTP_HDCP_KSV1_BITS      (0)      //!< Bit position for OCOTP_HDCP_KSV1_BITS.
#define BM_OCOTP_HDCP_KSV1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KSV1_BITS.

//! @brief Get value of OCOTP_HDCP_KSV1_BITS from a register value.
#define BG_OCOTP_HDCP_KSV1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KSV1_BITS) >> BP_OCOTP_HDCP_KSV1_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KSV1_BITS.
#define BF_OCOTP_HDCP_KSV1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KSV1_BITS) & BM_OCOTP_HDCP_KSV1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KSV1_BITS(v)   (HW_OCOTP_HDCP_KSV1_WR((HW_OCOTP_HDCP_KSV1_RD() & ~BM_OCOTP_HDCP_KSV1_BITS) | BF_OCOTP_HDCP_KSV1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_GP1 - Value of OTP Bank4 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_GP1 - Value of OTP Bank4 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 6 (ADDR = 0x26).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_gp1
{
    reg32_t U;
    struct _hw_ocotp_gp1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 6 (ADDR = 0x26).
    } B;
} hw_ocotp_gp1_t;
#endif

/*
 * constants & macros for entire OCOTP_GP1 register
 */
#define HW_OCOTP_GP1_ADDR      (REGS_OCOTP_BASE + 0x660)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_GP1           (*(volatile hw_ocotp_gp1_t *) HW_OCOTP_GP1_ADDR)
#define HW_OCOTP_GP1_RD()      (HW_OCOTP_GP1.U)
#define HW_OCOTP_GP1_WR(v)     (HW_OCOTP_GP1.U = (v))
#define HW_OCOTP_GP1_SET(v)    (HW_OCOTP_GP1_WR(HW_OCOTP_GP1_RD() |  (v)))
#define HW_OCOTP_GP1_CLR(v)    (HW_OCOTP_GP1_WR(HW_OCOTP_GP1_RD() & ~(v)))
#define HW_OCOTP_GP1_TOG(v)    (HW_OCOTP_GP1_WR(HW_OCOTP_GP1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_GP1 bitfields
 */

/* --- Register HW_OCOTP_GP1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 6 (ADDR = 0x26).
 */

#define BP_OCOTP_GP1_BITS      (0)      //!< Bit position for OCOTP_GP1_BITS.
#define BM_OCOTP_GP1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_GP1_BITS.

//! @brief Get value of OCOTP_GP1_BITS from a register value.
#define BG_OCOTP_GP1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_GP1_BITS) >> BP_OCOTP_GP1_BITS)

//! @brief Format value for bitfield OCOTP_GP1_BITS.
#define BF_OCOTP_GP1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_GP1_BITS) & BM_OCOTP_GP1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_GP1_BITS(v)   (HW_OCOTP_GP1_WR((HW_OCOTP_GP1_RD() & ~BM_OCOTP_GP1_BITS) | BF_OCOTP_GP1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_GP2 - Value of OTP Bank4 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_GP2 - Value of OTP Bank4 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 7 (ADDR = 0x27).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_gp2
{
    reg32_t U;
    struct _hw_ocotp_gp2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 4, word 7 (ADDR = 0x27).
    } B;
} hw_ocotp_gp2_t;
#endif

/*
 * constants & macros for entire OCOTP_GP2 register
 */
#define HW_OCOTP_GP2_ADDR      (REGS_OCOTP_BASE + 0x670)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_GP2           (*(volatile hw_ocotp_gp2_t *) HW_OCOTP_GP2_ADDR)
#define HW_OCOTP_GP2_RD()      (HW_OCOTP_GP2.U)
#define HW_OCOTP_GP2_WR(v)     (HW_OCOTP_GP2.U = (v))
#define HW_OCOTP_GP2_SET(v)    (HW_OCOTP_GP2_WR(HW_OCOTP_GP2_RD() |  (v)))
#define HW_OCOTP_GP2_CLR(v)    (HW_OCOTP_GP2_WR(HW_OCOTP_GP2_RD() & ~(v)))
#define HW_OCOTP_GP2_TOG(v)    (HW_OCOTP_GP2_WR(HW_OCOTP_GP2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_GP2 bitfields
 */

/* --- Register HW_OCOTP_GP2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 4, word 7 (ADDR = 0x27).
 */

#define BP_OCOTP_GP2_BITS      (0)      //!< Bit position for OCOTP_GP2_BITS.
#define BM_OCOTP_GP2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_GP2_BITS.

//! @brief Get value of OCOTP_GP2_BITS from a register value.
#define BG_OCOTP_GP2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_GP2_BITS) >> BP_OCOTP_GP2_BITS)

//! @brief Format value for bitfield OCOTP_GP2_BITS.
#define BF_OCOTP_GP2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_GP2_BITS) & BM_OCOTP_GP2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_GP2_BITS(v)   (HW_OCOTP_GP2_WR((HW_OCOTP_GP2_RD() & ~BM_OCOTP_GP2_BITS) | BF_OCOTP_GP2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DTCP_KEY0 - Value of OTP Bank5 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DTCP_KEY0 - Value of OTP Bank5 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 0 (ADDR = 0x28).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_dtcp_key0
{
    reg32_t U;
    struct _hw_ocotp_dtcp_key0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 0 (ADDR = 0x28).
    } B;
} hw_ocotp_dtcp_key0_t;
#endif

/*
 * constants & macros for entire OCOTP_DTCP_KEY0 register
 */
#define HW_OCOTP_DTCP_KEY0_ADDR      (REGS_OCOTP_BASE + 0x680)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DTCP_KEY0           (*(volatile hw_ocotp_dtcp_key0_t *) HW_OCOTP_DTCP_KEY0_ADDR)
#define HW_OCOTP_DTCP_KEY0_RD()      (HW_OCOTP_DTCP_KEY0.U)
#define HW_OCOTP_DTCP_KEY0_WR(v)     (HW_OCOTP_DTCP_KEY0.U = (v))
#define HW_OCOTP_DTCP_KEY0_SET(v)    (HW_OCOTP_DTCP_KEY0_WR(HW_OCOTP_DTCP_KEY0_RD() |  (v)))
#define HW_OCOTP_DTCP_KEY0_CLR(v)    (HW_OCOTP_DTCP_KEY0_WR(HW_OCOTP_DTCP_KEY0_RD() & ~(v)))
#define HW_OCOTP_DTCP_KEY0_TOG(v)    (HW_OCOTP_DTCP_KEY0_WR(HW_OCOTP_DTCP_KEY0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DTCP_KEY0 bitfields
 */

/* --- Register HW_OCOTP_DTCP_KEY0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 0 (ADDR = 0x28).
 */

#define BP_OCOTP_DTCP_KEY0_BITS      (0)      //!< Bit position for OCOTP_DTCP_KEY0_BITS.
#define BM_OCOTP_DTCP_KEY0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_DTCP_KEY0_BITS.

//! @brief Get value of OCOTP_DTCP_KEY0_BITS from a register value.
#define BG_OCOTP_DTCP_KEY0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DTCP_KEY0_BITS) >> BP_OCOTP_DTCP_KEY0_BITS)

//! @brief Format value for bitfield OCOTP_DTCP_KEY0_BITS.
#define BF_OCOTP_DTCP_KEY0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DTCP_KEY0_BITS) & BM_OCOTP_DTCP_KEY0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_DTCP_KEY0_BITS(v)   (HW_OCOTP_DTCP_KEY0_WR((HW_OCOTP_DTCP_KEY0_RD() & ~BM_OCOTP_DTCP_KEY0_BITS) | BF_OCOTP_DTCP_KEY0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DTCP_KEY1 - Value of OTP Bank5 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DTCP_KEY1 - Value of OTP Bank5 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 1 (ADDR = 0x29).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_dtcp_key1
{
    reg32_t U;
    struct _hw_ocotp_dtcp_key1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 1 (ADDR = 0x29).
    } B;
} hw_ocotp_dtcp_key1_t;
#endif

/*
 * constants & macros for entire OCOTP_DTCP_KEY1 register
 */
#define HW_OCOTP_DTCP_KEY1_ADDR      (REGS_OCOTP_BASE + 0x690)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DTCP_KEY1           (*(volatile hw_ocotp_dtcp_key1_t *) HW_OCOTP_DTCP_KEY1_ADDR)
#define HW_OCOTP_DTCP_KEY1_RD()      (HW_OCOTP_DTCP_KEY1.U)
#define HW_OCOTP_DTCP_KEY1_WR(v)     (HW_OCOTP_DTCP_KEY1.U = (v))
#define HW_OCOTP_DTCP_KEY1_SET(v)    (HW_OCOTP_DTCP_KEY1_WR(HW_OCOTP_DTCP_KEY1_RD() |  (v)))
#define HW_OCOTP_DTCP_KEY1_CLR(v)    (HW_OCOTP_DTCP_KEY1_WR(HW_OCOTP_DTCP_KEY1_RD() & ~(v)))
#define HW_OCOTP_DTCP_KEY1_TOG(v)    (HW_OCOTP_DTCP_KEY1_WR(HW_OCOTP_DTCP_KEY1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DTCP_KEY1 bitfields
 */

/* --- Register HW_OCOTP_DTCP_KEY1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 1 (ADDR = 0x29).
 */

#define BP_OCOTP_DTCP_KEY1_BITS      (0)      //!< Bit position for OCOTP_DTCP_KEY1_BITS.
#define BM_OCOTP_DTCP_KEY1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_DTCP_KEY1_BITS.

//! @brief Get value of OCOTP_DTCP_KEY1_BITS from a register value.
#define BG_OCOTP_DTCP_KEY1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DTCP_KEY1_BITS) >> BP_OCOTP_DTCP_KEY1_BITS)

//! @brief Format value for bitfield OCOTP_DTCP_KEY1_BITS.
#define BF_OCOTP_DTCP_KEY1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DTCP_KEY1_BITS) & BM_OCOTP_DTCP_KEY1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_DTCP_KEY1_BITS(v)   (HW_OCOTP_DTCP_KEY1_WR((HW_OCOTP_DTCP_KEY1_RD() & ~BM_OCOTP_DTCP_KEY1_BITS) | BF_OCOTP_DTCP_KEY1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DTCP_KEY2 - Value of OTP Bank5 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DTCP_KEY2 - Value of OTP Bank5 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 2 (ADDR = 0x2a).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_dtcp_key2
{
    reg32_t U;
    struct _hw_ocotp_dtcp_key2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 2 (ADDR = 0x2a).
    } B;
} hw_ocotp_dtcp_key2_t;
#endif

/*
 * constants & macros for entire OCOTP_DTCP_KEY2 register
 */
#define HW_OCOTP_DTCP_KEY2_ADDR      (REGS_OCOTP_BASE + 0x6a0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DTCP_KEY2           (*(volatile hw_ocotp_dtcp_key2_t *) HW_OCOTP_DTCP_KEY2_ADDR)
#define HW_OCOTP_DTCP_KEY2_RD()      (HW_OCOTP_DTCP_KEY2.U)
#define HW_OCOTP_DTCP_KEY2_WR(v)     (HW_OCOTP_DTCP_KEY2.U = (v))
#define HW_OCOTP_DTCP_KEY2_SET(v)    (HW_OCOTP_DTCP_KEY2_WR(HW_OCOTP_DTCP_KEY2_RD() |  (v)))
#define HW_OCOTP_DTCP_KEY2_CLR(v)    (HW_OCOTP_DTCP_KEY2_WR(HW_OCOTP_DTCP_KEY2_RD() & ~(v)))
#define HW_OCOTP_DTCP_KEY2_TOG(v)    (HW_OCOTP_DTCP_KEY2_WR(HW_OCOTP_DTCP_KEY2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DTCP_KEY2 bitfields
 */

/* --- Register HW_OCOTP_DTCP_KEY2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 2 (ADDR = 0x2a).
 */

#define BP_OCOTP_DTCP_KEY2_BITS      (0)      //!< Bit position for OCOTP_DTCP_KEY2_BITS.
#define BM_OCOTP_DTCP_KEY2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_DTCP_KEY2_BITS.

//! @brief Get value of OCOTP_DTCP_KEY2_BITS from a register value.
#define BG_OCOTP_DTCP_KEY2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DTCP_KEY2_BITS) >> BP_OCOTP_DTCP_KEY2_BITS)

//! @brief Format value for bitfield OCOTP_DTCP_KEY2_BITS.
#define BF_OCOTP_DTCP_KEY2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DTCP_KEY2_BITS) & BM_OCOTP_DTCP_KEY2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_DTCP_KEY2_BITS(v)   (HW_OCOTP_DTCP_KEY2_WR((HW_OCOTP_DTCP_KEY2_RD() & ~BM_OCOTP_DTCP_KEY2_BITS) | BF_OCOTP_DTCP_KEY2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DTCP_KEY3 - Value of OTP Bank5 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DTCP_KEY3 - Value of OTP Bank5 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 3 (ADDR = 0x2b).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_dtcp_key3
{
    reg32_t U;
    struct _hw_ocotp_dtcp_key3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 3 (ADDR = 0x2b).
    } B;
} hw_ocotp_dtcp_key3_t;
#endif

/*
 * constants & macros for entire OCOTP_DTCP_KEY3 register
 */
#define HW_OCOTP_DTCP_KEY3_ADDR      (REGS_OCOTP_BASE + 0x6b0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DTCP_KEY3           (*(volatile hw_ocotp_dtcp_key3_t *) HW_OCOTP_DTCP_KEY3_ADDR)
#define HW_OCOTP_DTCP_KEY3_RD()      (HW_OCOTP_DTCP_KEY3.U)
#define HW_OCOTP_DTCP_KEY3_WR(v)     (HW_OCOTP_DTCP_KEY3.U = (v))
#define HW_OCOTP_DTCP_KEY3_SET(v)    (HW_OCOTP_DTCP_KEY3_WR(HW_OCOTP_DTCP_KEY3_RD() |  (v)))
#define HW_OCOTP_DTCP_KEY3_CLR(v)    (HW_OCOTP_DTCP_KEY3_WR(HW_OCOTP_DTCP_KEY3_RD() & ~(v)))
#define HW_OCOTP_DTCP_KEY3_TOG(v)    (HW_OCOTP_DTCP_KEY3_WR(HW_OCOTP_DTCP_KEY3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DTCP_KEY3 bitfields
 */

/* --- Register HW_OCOTP_DTCP_KEY3, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 3 (ADDR = 0x2b).
 */

#define BP_OCOTP_DTCP_KEY3_BITS      (0)      //!< Bit position for OCOTP_DTCP_KEY3_BITS.
#define BM_OCOTP_DTCP_KEY3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_DTCP_KEY3_BITS.

//! @brief Get value of OCOTP_DTCP_KEY3_BITS from a register value.
#define BG_OCOTP_DTCP_KEY3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DTCP_KEY3_BITS) >> BP_OCOTP_DTCP_KEY3_BITS)

//! @brief Format value for bitfield OCOTP_DTCP_KEY3_BITS.
#define BF_OCOTP_DTCP_KEY3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DTCP_KEY3_BITS) & BM_OCOTP_DTCP_KEY3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_DTCP_KEY3_BITS(v)   (HW_OCOTP_DTCP_KEY3_WR((HW_OCOTP_DTCP_KEY3_RD() & ~BM_OCOTP_DTCP_KEY3_BITS) | BF_OCOTP_DTCP_KEY3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_DTCP_KEY4 - Value of OTP Bank5 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_DTCP_KEY4 - Value of OTP Bank5 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 4 (ADDR = 0x2c).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_dtcp_key4
{
    reg32_t U;
    struct _hw_ocotp_dtcp_key4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 4 (ADDR = 0x2c).
    } B;
} hw_ocotp_dtcp_key4_t;
#endif

/*
 * constants & macros for entire OCOTP_DTCP_KEY4 register
 */
#define HW_OCOTP_DTCP_KEY4_ADDR      (REGS_OCOTP_BASE + 0x6c0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_DTCP_KEY4           (*(volatile hw_ocotp_dtcp_key4_t *) HW_OCOTP_DTCP_KEY4_ADDR)
#define HW_OCOTP_DTCP_KEY4_RD()      (HW_OCOTP_DTCP_KEY4.U)
#define HW_OCOTP_DTCP_KEY4_WR(v)     (HW_OCOTP_DTCP_KEY4.U = (v))
#define HW_OCOTP_DTCP_KEY4_SET(v)    (HW_OCOTP_DTCP_KEY4_WR(HW_OCOTP_DTCP_KEY4_RD() |  (v)))
#define HW_OCOTP_DTCP_KEY4_CLR(v)    (HW_OCOTP_DTCP_KEY4_WR(HW_OCOTP_DTCP_KEY4_RD() & ~(v)))
#define HW_OCOTP_DTCP_KEY4_TOG(v)    (HW_OCOTP_DTCP_KEY4_WR(HW_OCOTP_DTCP_KEY4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_DTCP_KEY4 bitfields
 */

/* --- Register HW_OCOTP_DTCP_KEY4, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 4 (ADDR = 0x2c).
 */

#define BP_OCOTP_DTCP_KEY4_BITS      (0)      //!< Bit position for OCOTP_DTCP_KEY4_BITS.
#define BM_OCOTP_DTCP_KEY4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_DTCP_KEY4_BITS.

//! @brief Get value of OCOTP_DTCP_KEY4_BITS from a register value.
#define BG_OCOTP_DTCP_KEY4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_DTCP_KEY4_BITS) >> BP_OCOTP_DTCP_KEY4_BITS)

//! @brief Format value for bitfield OCOTP_DTCP_KEY4_BITS.
#define BF_OCOTP_DTCP_KEY4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_DTCP_KEY4_BITS) & BM_OCOTP_DTCP_KEY4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_DTCP_KEY4_BITS(v)   (HW_OCOTP_DTCP_KEY4_WR((HW_OCOTP_DTCP_KEY4_RD() & ~BM_OCOTP_DTCP_KEY4_BITS) | BF_OCOTP_DTCP_KEY4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_MISC_CONF - Value of OTP Bank5 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_MISC_CONF - Value of OTP Bank5 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 5 (ADDR = 0x2d).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_misc_conf
{
    reg32_t U;
    struct _hw_ocotp_misc_conf_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 5 (ADDR = 0x2d).
    } B;
} hw_ocotp_misc_conf_t;
#endif

/*
 * constants & macros for entire OCOTP_MISC_CONF register
 */
#define HW_OCOTP_MISC_CONF_ADDR      (REGS_OCOTP_BASE + 0x6d0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_MISC_CONF           (*(volatile hw_ocotp_misc_conf_t *) HW_OCOTP_MISC_CONF_ADDR)
#define HW_OCOTP_MISC_CONF_RD()      (HW_OCOTP_MISC_CONF.U)
#define HW_OCOTP_MISC_CONF_WR(v)     (HW_OCOTP_MISC_CONF.U = (v))
#define HW_OCOTP_MISC_CONF_SET(v)    (HW_OCOTP_MISC_CONF_WR(HW_OCOTP_MISC_CONF_RD() |  (v)))
#define HW_OCOTP_MISC_CONF_CLR(v)    (HW_OCOTP_MISC_CONF_WR(HW_OCOTP_MISC_CONF_RD() & ~(v)))
#define HW_OCOTP_MISC_CONF_TOG(v)    (HW_OCOTP_MISC_CONF_WR(HW_OCOTP_MISC_CONF_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_MISC_CONF bitfields
 */

/* --- Register HW_OCOTP_MISC_CONF, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 5 (ADDR = 0x2d).
 */

#define BP_OCOTP_MISC_CONF_BITS      (0)      //!< Bit position for OCOTP_MISC_CONF_BITS.
#define BM_OCOTP_MISC_CONF_BITS      (0xffffffff)  //!< Bit mask for OCOTP_MISC_CONF_BITS.

//! @brief Get value of OCOTP_MISC_CONF_BITS from a register value.
#define BG_OCOTP_MISC_CONF_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_MISC_CONF_BITS) >> BP_OCOTP_MISC_CONF_BITS)

//! @brief Format value for bitfield OCOTP_MISC_CONF_BITS.
#define BF_OCOTP_MISC_CONF_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_MISC_CONF_BITS) & BM_OCOTP_MISC_CONF_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_MISC_CONF_BITS(v)   (HW_OCOTP_MISC_CONF_WR((HW_OCOTP_MISC_CONF_RD() & ~BM_OCOTP_MISC_CONF_BITS) | BF_OCOTP_MISC_CONF_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_FIELD_RETURN - Value of OTP Bank5 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_FIELD_RETURN - Value of OTP Bank5 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 6 (ADDR = 0x2e).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_field_return
{
    reg32_t U;
    struct _hw_ocotp_field_return_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 6 (ADDR = 0x2e).
    } B;
} hw_ocotp_field_return_t;
#endif

/*
 * constants & macros for entire OCOTP_FIELD_RETURN register
 */
#define HW_OCOTP_FIELD_RETURN_ADDR      (REGS_OCOTP_BASE + 0x6e0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_FIELD_RETURN           (*(volatile hw_ocotp_field_return_t *) HW_OCOTP_FIELD_RETURN_ADDR)
#define HW_OCOTP_FIELD_RETURN_RD()      (HW_OCOTP_FIELD_RETURN.U)
#define HW_OCOTP_FIELD_RETURN_WR(v)     (HW_OCOTP_FIELD_RETURN.U = (v))
#define HW_OCOTP_FIELD_RETURN_SET(v)    (HW_OCOTP_FIELD_RETURN_WR(HW_OCOTP_FIELD_RETURN_RD() |  (v)))
#define HW_OCOTP_FIELD_RETURN_CLR(v)    (HW_OCOTP_FIELD_RETURN_WR(HW_OCOTP_FIELD_RETURN_RD() & ~(v)))
#define HW_OCOTP_FIELD_RETURN_TOG(v)    (HW_OCOTP_FIELD_RETURN_WR(HW_OCOTP_FIELD_RETURN_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_FIELD_RETURN bitfields
 */

/* --- Register HW_OCOTP_FIELD_RETURN, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 6 (ADDR = 0x2e).
 */

#define BP_OCOTP_FIELD_RETURN_BITS      (0)      //!< Bit position for OCOTP_FIELD_RETURN_BITS.
#define BM_OCOTP_FIELD_RETURN_BITS      (0xffffffff)  //!< Bit mask for OCOTP_FIELD_RETURN_BITS.

//! @brief Get value of OCOTP_FIELD_RETURN_BITS from a register value.
#define BG_OCOTP_FIELD_RETURN_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_FIELD_RETURN_BITS) >> BP_OCOTP_FIELD_RETURN_BITS)

//! @brief Format value for bitfield OCOTP_FIELD_RETURN_BITS.
#define BF_OCOTP_FIELD_RETURN_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_FIELD_RETURN_BITS) & BM_OCOTP_FIELD_RETURN_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_FIELD_RETURN_BITS(v)   (HW_OCOTP_FIELD_RETURN_WR((HW_OCOTP_FIELD_RETURN_RD() & ~BM_OCOTP_FIELD_RETURN_BITS) | BF_OCOTP_FIELD_RETURN_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_SRK_REVOKE - Value of OTP Bank5 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_SRK_REVOKE - Value of OTP Bank5 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 5, word 7 (ADDR = 0x2f).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_srk_revoke
{
    reg32_t U;
    struct _hw_ocotp_srk_revoke_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 5, word 7 (ADDR = 0x2f).
    } B;
} hw_ocotp_srk_revoke_t;
#endif

/*
 * constants & macros for entire OCOTP_SRK_REVOKE register
 */
#define HW_OCOTP_SRK_REVOKE_ADDR      (REGS_OCOTP_BASE + 0x6f0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_SRK_REVOKE           (*(volatile hw_ocotp_srk_revoke_t *) HW_OCOTP_SRK_REVOKE_ADDR)
#define HW_OCOTP_SRK_REVOKE_RD()      (HW_OCOTP_SRK_REVOKE.U)
#define HW_OCOTP_SRK_REVOKE_WR(v)     (HW_OCOTP_SRK_REVOKE.U = (v))
#define HW_OCOTP_SRK_REVOKE_SET(v)    (HW_OCOTP_SRK_REVOKE_WR(HW_OCOTP_SRK_REVOKE_RD() |  (v)))
#define HW_OCOTP_SRK_REVOKE_CLR(v)    (HW_OCOTP_SRK_REVOKE_WR(HW_OCOTP_SRK_REVOKE_RD() & ~(v)))
#define HW_OCOTP_SRK_REVOKE_TOG(v)    (HW_OCOTP_SRK_REVOKE_WR(HW_OCOTP_SRK_REVOKE_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_SRK_REVOKE bitfields
 */

/* --- Register HW_OCOTP_SRK_REVOKE, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 5, word 7 (ADDR = 0x2f).
 */

#define BP_OCOTP_SRK_REVOKE_BITS      (0)      //!< Bit position for OCOTP_SRK_REVOKE_BITS.
#define BM_OCOTP_SRK_REVOKE_BITS      (0xffffffff)  //!< Bit mask for OCOTP_SRK_REVOKE_BITS.

//! @brief Get value of OCOTP_SRK_REVOKE_BITS from a register value.
#define BG_OCOTP_SRK_REVOKE_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_SRK_REVOKE_BITS) >> BP_OCOTP_SRK_REVOKE_BITS)

//! @brief Format value for bitfield OCOTP_SRK_REVOKE_BITS.
#define BF_OCOTP_SRK_REVOKE_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_SRK_REVOKE_BITS) & BM_OCOTP_SRK_REVOKE_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_SRK_REVOKE_BITS(v)   (HW_OCOTP_SRK_REVOKE_WR((HW_OCOTP_SRK_REVOKE_RD() & ~BM_OCOTP_SRK_REVOKE_BITS) | BF_OCOTP_SRK_REVOKE_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY0 - Value of OTP Bank6 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY0 - Value of OTP Bank6 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 0 (ADDR = 0x30).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key0
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 0 (ADDR = 0x30).
    } B;
} hw_ocotp_hdcp_key0_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY0 register
 */
#define HW_OCOTP_HDCP_KEY0_ADDR      (REGS_OCOTP_BASE + 0x800)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY0           (*(volatile hw_ocotp_hdcp_key0_t *) HW_OCOTP_HDCP_KEY0_ADDR)
#define HW_OCOTP_HDCP_KEY0_RD()      (HW_OCOTP_HDCP_KEY0.U)
#define HW_OCOTP_HDCP_KEY0_WR(v)     (HW_OCOTP_HDCP_KEY0.U = (v))
#define HW_OCOTP_HDCP_KEY0_SET(v)    (HW_OCOTP_HDCP_KEY0_WR(HW_OCOTP_HDCP_KEY0_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY0_CLR(v)    (HW_OCOTP_HDCP_KEY0_WR(HW_OCOTP_HDCP_KEY0_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY0_TOG(v)    (HW_OCOTP_HDCP_KEY0_WR(HW_OCOTP_HDCP_KEY0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY0 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 0 (ADDR = 0x30).
 */

#define BP_OCOTP_HDCP_KEY0_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY0_BITS.
#define BM_OCOTP_HDCP_KEY0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY0_BITS.

//! @brief Get value of OCOTP_HDCP_KEY0_BITS from a register value.
#define BG_OCOTP_HDCP_KEY0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY0_BITS) >> BP_OCOTP_HDCP_KEY0_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY0_BITS.
#define BF_OCOTP_HDCP_KEY0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY0_BITS) & BM_OCOTP_HDCP_KEY0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY0_BITS(v)   (HW_OCOTP_HDCP_KEY0_WR((HW_OCOTP_HDCP_KEY0_RD() & ~BM_OCOTP_HDCP_KEY0_BITS) | BF_OCOTP_HDCP_KEY0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY1 - Value of OTP Bank6 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY1 - Value of OTP Bank6 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 1 (ADDR = 0x31).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key1
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 1 (ADDR = 0x31).
    } B;
} hw_ocotp_hdcp_key1_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY1 register
 */
#define HW_OCOTP_HDCP_KEY1_ADDR      (REGS_OCOTP_BASE + 0x810)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY1           (*(volatile hw_ocotp_hdcp_key1_t *) HW_OCOTP_HDCP_KEY1_ADDR)
#define HW_OCOTP_HDCP_KEY1_RD()      (HW_OCOTP_HDCP_KEY1.U)
#define HW_OCOTP_HDCP_KEY1_WR(v)     (HW_OCOTP_HDCP_KEY1.U = (v))
#define HW_OCOTP_HDCP_KEY1_SET(v)    (HW_OCOTP_HDCP_KEY1_WR(HW_OCOTP_HDCP_KEY1_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY1_CLR(v)    (HW_OCOTP_HDCP_KEY1_WR(HW_OCOTP_HDCP_KEY1_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY1_TOG(v)    (HW_OCOTP_HDCP_KEY1_WR(HW_OCOTP_HDCP_KEY1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY1 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 1 (ADDR = 0x31).
 */

#define BP_OCOTP_HDCP_KEY1_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY1_BITS.
#define BM_OCOTP_HDCP_KEY1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY1_BITS.

//! @brief Get value of OCOTP_HDCP_KEY1_BITS from a register value.
#define BG_OCOTP_HDCP_KEY1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY1_BITS) >> BP_OCOTP_HDCP_KEY1_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY1_BITS.
#define BF_OCOTP_HDCP_KEY1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY1_BITS) & BM_OCOTP_HDCP_KEY1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY1_BITS(v)   (HW_OCOTP_HDCP_KEY1_WR((HW_OCOTP_HDCP_KEY1_RD() & ~BM_OCOTP_HDCP_KEY1_BITS) | BF_OCOTP_HDCP_KEY1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY2 - Value of OTP Bank6 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY2 - Value of OTP Bank6 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 2 (ADDR = 0x32).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key2
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 2 (ADDR = 0x32).
    } B;
} hw_ocotp_hdcp_key2_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY2 register
 */
#define HW_OCOTP_HDCP_KEY2_ADDR      (REGS_OCOTP_BASE + 0x820)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY2           (*(volatile hw_ocotp_hdcp_key2_t *) HW_OCOTP_HDCP_KEY2_ADDR)
#define HW_OCOTP_HDCP_KEY2_RD()      (HW_OCOTP_HDCP_KEY2.U)
#define HW_OCOTP_HDCP_KEY2_WR(v)     (HW_OCOTP_HDCP_KEY2.U = (v))
#define HW_OCOTP_HDCP_KEY2_SET(v)    (HW_OCOTP_HDCP_KEY2_WR(HW_OCOTP_HDCP_KEY2_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY2_CLR(v)    (HW_OCOTP_HDCP_KEY2_WR(HW_OCOTP_HDCP_KEY2_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY2_TOG(v)    (HW_OCOTP_HDCP_KEY2_WR(HW_OCOTP_HDCP_KEY2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY2 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 2 (ADDR = 0x32).
 */

#define BP_OCOTP_HDCP_KEY2_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY2_BITS.
#define BM_OCOTP_HDCP_KEY2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY2_BITS.

//! @brief Get value of OCOTP_HDCP_KEY2_BITS from a register value.
#define BG_OCOTP_HDCP_KEY2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY2_BITS) >> BP_OCOTP_HDCP_KEY2_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY2_BITS.
#define BF_OCOTP_HDCP_KEY2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY2_BITS) & BM_OCOTP_HDCP_KEY2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY2_BITS(v)   (HW_OCOTP_HDCP_KEY2_WR((HW_OCOTP_HDCP_KEY2_RD() & ~BM_OCOTP_HDCP_KEY2_BITS) | BF_OCOTP_HDCP_KEY2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY3 - Value of OTP Bank6 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY3 - Value of OTP Bank6 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 3 (ADDR = 0x33).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key3
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 3 (ADDR = 0x33).
    } B;
} hw_ocotp_hdcp_key3_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY3 register
 */
#define HW_OCOTP_HDCP_KEY3_ADDR      (REGS_OCOTP_BASE + 0x830)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY3           (*(volatile hw_ocotp_hdcp_key3_t *) HW_OCOTP_HDCP_KEY3_ADDR)
#define HW_OCOTP_HDCP_KEY3_RD()      (HW_OCOTP_HDCP_KEY3.U)
#define HW_OCOTP_HDCP_KEY3_WR(v)     (HW_OCOTP_HDCP_KEY3.U = (v))
#define HW_OCOTP_HDCP_KEY3_SET(v)    (HW_OCOTP_HDCP_KEY3_WR(HW_OCOTP_HDCP_KEY3_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY3_CLR(v)    (HW_OCOTP_HDCP_KEY3_WR(HW_OCOTP_HDCP_KEY3_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY3_TOG(v)    (HW_OCOTP_HDCP_KEY3_WR(HW_OCOTP_HDCP_KEY3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY3 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY3, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 3 (ADDR = 0x33).
 */

#define BP_OCOTP_HDCP_KEY3_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY3_BITS.
#define BM_OCOTP_HDCP_KEY3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY3_BITS.

//! @brief Get value of OCOTP_HDCP_KEY3_BITS from a register value.
#define BG_OCOTP_HDCP_KEY3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY3_BITS) >> BP_OCOTP_HDCP_KEY3_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY3_BITS.
#define BF_OCOTP_HDCP_KEY3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY3_BITS) & BM_OCOTP_HDCP_KEY3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY3_BITS(v)   (HW_OCOTP_HDCP_KEY3_WR((HW_OCOTP_HDCP_KEY3_RD() & ~BM_OCOTP_HDCP_KEY3_BITS) | BF_OCOTP_HDCP_KEY3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY4 - Value of OTP Bank6 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY4 - Value of OTP Bank6 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank Bank 6, word 4 (ADDR =
 * 0x34).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key4
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 4 (ADDR = 0x34).
    } B;
} hw_ocotp_hdcp_key4_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY4 register
 */
#define HW_OCOTP_HDCP_KEY4_ADDR      (REGS_OCOTP_BASE + 0x840)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY4           (*(volatile hw_ocotp_hdcp_key4_t *) HW_OCOTP_HDCP_KEY4_ADDR)
#define HW_OCOTP_HDCP_KEY4_RD()      (HW_OCOTP_HDCP_KEY4.U)
#define HW_OCOTP_HDCP_KEY4_WR(v)     (HW_OCOTP_HDCP_KEY4.U = (v))
#define HW_OCOTP_HDCP_KEY4_SET(v)    (HW_OCOTP_HDCP_KEY4_WR(HW_OCOTP_HDCP_KEY4_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY4_CLR(v)    (HW_OCOTP_HDCP_KEY4_WR(HW_OCOTP_HDCP_KEY4_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY4_TOG(v)    (HW_OCOTP_HDCP_KEY4_WR(HW_OCOTP_HDCP_KEY4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY4 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY4, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 4 (ADDR = 0x34).
 */

#define BP_OCOTP_HDCP_KEY4_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY4_BITS.
#define BM_OCOTP_HDCP_KEY4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY4_BITS.

//! @brief Get value of OCOTP_HDCP_KEY4_BITS from a register value.
#define BG_OCOTP_HDCP_KEY4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY4_BITS) >> BP_OCOTP_HDCP_KEY4_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY4_BITS.
#define BF_OCOTP_HDCP_KEY4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY4_BITS) & BM_OCOTP_HDCP_KEY4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY4_BITS(v)   (HW_OCOTP_HDCP_KEY4_WR((HW_OCOTP_HDCP_KEY4_RD() & ~BM_OCOTP_HDCP_KEY4_BITS) | BF_OCOTP_HDCP_KEY4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY5 - Value of OTP Bank6 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY5 - Value of OTP Bank6 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 5 (ADDR = 0x35).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key5
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key5_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 5 (ADDR = 0x35).
    } B;
} hw_ocotp_hdcp_key5_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY5 register
 */
#define HW_OCOTP_HDCP_KEY5_ADDR      (REGS_OCOTP_BASE + 0x850)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY5           (*(volatile hw_ocotp_hdcp_key5_t *) HW_OCOTP_HDCP_KEY5_ADDR)
#define HW_OCOTP_HDCP_KEY5_RD()      (HW_OCOTP_HDCP_KEY5.U)
#define HW_OCOTP_HDCP_KEY5_WR(v)     (HW_OCOTP_HDCP_KEY5.U = (v))
#define HW_OCOTP_HDCP_KEY5_SET(v)    (HW_OCOTP_HDCP_KEY5_WR(HW_OCOTP_HDCP_KEY5_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY5_CLR(v)    (HW_OCOTP_HDCP_KEY5_WR(HW_OCOTP_HDCP_KEY5_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY5_TOG(v)    (HW_OCOTP_HDCP_KEY5_WR(HW_OCOTP_HDCP_KEY5_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY5 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY5, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 5 (ADDR = 0x35).
 */

#define BP_OCOTP_HDCP_KEY5_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY5_BITS.
#define BM_OCOTP_HDCP_KEY5_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY5_BITS.

//! @brief Get value of OCOTP_HDCP_KEY5_BITS from a register value.
#define BG_OCOTP_HDCP_KEY5_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY5_BITS) >> BP_OCOTP_HDCP_KEY5_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY5_BITS.
#define BF_OCOTP_HDCP_KEY5_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY5_BITS) & BM_OCOTP_HDCP_KEY5_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY5_BITS(v)   (HW_OCOTP_HDCP_KEY5_WR((HW_OCOTP_HDCP_KEY5_RD() & ~BM_OCOTP_HDCP_KEY5_BITS) | BF_OCOTP_HDCP_KEY5_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY6 - Value of OTP Bank6 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY6 - Value of OTP Bank6 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 6 (ADDR = 0x36).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key6
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key6_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 6 (ADDR = 0x36).
    } B;
} hw_ocotp_hdcp_key6_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY6 register
 */
#define HW_OCOTP_HDCP_KEY6_ADDR      (REGS_OCOTP_BASE + 0x860)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY6           (*(volatile hw_ocotp_hdcp_key6_t *) HW_OCOTP_HDCP_KEY6_ADDR)
#define HW_OCOTP_HDCP_KEY6_RD()      (HW_OCOTP_HDCP_KEY6.U)
#define HW_OCOTP_HDCP_KEY6_WR(v)     (HW_OCOTP_HDCP_KEY6.U = (v))
#define HW_OCOTP_HDCP_KEY6_SET(v)    (HW_OCOTP_HDCP_KEY6_WR(HW_OCOTP_HDCP_KEY6_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY6_CLR(v)    (HW_OCOTP_HDCP_KEY6_WR(HW_OCOTP_HDCP_KEY6_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY6_TOG(v)    (HW_OCOTP_HDCP_KEY6_WR(HW_OCOTP_HDCP_KEY6_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY6 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY6, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 6 (ADDR = 0x36).
 */

#define BP_OCOTP_HDCP_KEY6_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY6_BITS.
#define BM_OCOTP_HDCP_KEY6_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY6_BITS.

//! @brief Get value of OCOTP_HDCP_KEY6_BITS from a register value.
#define BG_OCOTP_HDCP_KEY6_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY6_BITS) >> BP_OCOTP_HDCP_KEY6_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY6_BITS.
#define BF_OCOTP_HDCP_KEY6_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY6_BITS) & BM_OCOTP_HDCP_KEY6_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY6_BITS(v)   (HW_OCOTP_HDCP_KEY6_WR((HW_OCOTP_HDCP_KEY6_RD() & ~BM_OCOTP_HDCP_KEY6_BITS) | BF_OCOTP_HDCP_KEY6_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY7 - Value of OTP Bank6 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY7 - Value of OTP Bank6 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 6, word 7 (ADDR = 0x37).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key7
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key7_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 6, word 7 (ADDR = 0x37).
    } B;
} hw_ocotp_hdcp_key7_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY7 register
 */
#define HW_OCOTP_HDCP_KEY7_ADDR      (REGS_OCOTP_BASE + 0x870)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY7           (*(volatile hw_ocotp_hdcp_key7_t *) HW_OCOTP_HDCP_KEY7_ADDR)
#define HW_OCOTP_HDCP_KEY7_RD()      (HW_OCOTP_HDCP_KEY7.U)
#define HW_OCOTP_HDCP_KEY7_WR(v)     (HW_OCOTP_HDCP_KEY7.U = (v))
#define HW_OCOTP_HDCP_KEY7_SET(v)    (HW_OCOTP_HDCP_KEY7_WR(HW_OCOTP_HDCP_KEY7_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY7_CLR(v)    (HW_OCOTP_HDCP_KEY7_WR(HW_OCOTP_HDCP_KEY7_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY7_TOG(v)    (HW_OCOTP_HDCP_KEY7_WR(HW_OCOTP_HDCP_KEY7_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY7 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY7, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 6, word 7 (ADDR = 0x37).
 */

#define BP_OCOTP_HDCP_KEY7_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY7_BITS.
#define BM_OCOTP_HDCP_KEY7_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY7_BITS.

//! @brief Get value of OCOTP_HDCP_KEY7_BITS from a register value.
#define BG_OCOTP_HDCP_KEY7_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY7_BITS) >> BP_OCOTP_HDCP_KEY7_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY7_BITS.
#define BF_OCOTP_HDCP_KEY7_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY7_BITS) & BM_OCOTP_HDCP_KEY7_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY7_BITS(v)   (HW_OCOTP_HDCP_KEY7_WR((HW_OCOTP_HDCP_KEY7_RD() & ~BM_OCOTP_HDCP_KEY7_BITS) | BF_OCOTP_HDCP_KEY7_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY8 - Value of OTP Bank7 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY8 - Value of OTP Bank7 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 0 (ADDR = 0x38).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key8
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key8_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 0 (ADDR = 0x38).
    } B;
} hw_ocotp_hdcp_key8_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY8 register
 */
#define HW_OCOTP_HDCP_KEY8_ADDR      (REGS_OCOTP_BASE + 0x880)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY8           (*(volatile hw_ocotp_hdcp_key8_t *) HW_OCOTP_HDCP_KEY8_ADDR)
#define HW_OCOTP_HDCP_KEY8_RD()      (HW_OCOTP_HDCP_KEY8.U)
#define HW_OCOTP_HDCP_KEY8_WR(v)     (HW_OCOTP_HDCP_KEY8.U = (v))
#define HW_OCOTP_HDCP_KEY8_SET(v)    (HW_OCOTP_HDCP_KEY8_WR(HW_OCOTP_HDCP_KEY8_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY8_CLR(v)    (HW_OCOTP_HDCP_KEY8_WR(HW_OCOTP_HDCP_KEY8_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY8_TOG(v)    (HW_OCOTP_HDCP_KEY8_WR(HW_OCOTP_HDCP_KEY8_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY8 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY8, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 0 (ADDR = 0x38).
 */

#define BP_OCOTP_HDCP_KEY8_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY8_BITS.
#define BM_OCOTP_HDCP_KEY8_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY8_BITS.

//! @brief Get value of OCOTP_HDCP_KEY8_BITS from a register value.
#define BG_OCOTP_HDCP_KEY8_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY8_BITS) >> BP_OCOTP_HDCP_KEY8_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY8_BITS.
#define BF_OCOTP_HDCP_KEY8_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY8_BITS) & BM_OCOTP_HDCP_KEY8_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY8_BITS(v)   (HW_OCOTP_HDCP_KEY8_WR((HW_OCOTP_HDCP_KEY8_RD() & ~BM_OCOTP_HDCP_KEY8_BITS) | BF_OCOTP_HDCP_KEY8_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY9 - Value of OTP Bank7 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY9 - Value of OTP Bank7 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 1 (ADDR = 0x39).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key9
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key9_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 1 (ADDR = 0x39).
    } B;
} hw_ocotp_hdcp_key9_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY9 register
 */
#define HW_OCOTP_HDCP_KEY9_ADDR      (REGS_OCOTP_BASE + 0x890)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY9           (*(volatile hw_ocotp_hdcp_key9_t *) HW_OCOTP_HDCP_KEY9_ADDR)
#define HW_OCOTP_HDCP_KEY9_RD()      (HW_OCOTP_HDCP_KEY9.U)
#define HW_OCOTP_HDCP_KEY9_WR(v)     (HW_OCOTP_HDCP_KEY9.U = (v))
#define HW_OCOTP_HDCP_KEY9_SET(v)    (HW_OCOTP_HDCP_KEY9_WR(HW_OCOTP_HDCP_KEY9_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY9_CLR(v)    (HW_OCOTP_HDCP_KEY9_WR(HW_OCOTP_HDCP_KEY9_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY9_TOG(v)    (HW_OCOTP_HDCP_KEY9_WR(HW_OCOTP_HDCP_KEY9_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY9 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY9, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 1 (ADDR = 0x39).
 */

#define BP_OCOTP_HDCP_KEY9_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY9_BITS.
#define BM_OCOTP_HDCP_KEY9_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY9_BITS.

//! @brief Get value of OCOTP_HDCP_KEY9_BITS from a register value.
#define BG_OCOTP_HDCP_KEY9_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY9_BITS) >> BP_OCOTP_HDCP_KEY9_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY9_BITS.
#define BF_OCOTP_HDCP_KEY9_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY9_BITS) & BM_OCOTP_HDCP_KEY9_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY9_BITS(v)   (HW_OCOTP_HDCP_KEY9_WR((HW_OCOTP_HDCP_KEY9_RD() & ~BM_OCOTP_HDCP_KEY9_BITS) | BF_OCOTP_HDCP_KEY9_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY10 - Value of OTP Bank7 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY10 - Value of OTP Bank7 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 2 (ADDR = 0x3a).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key10
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key10_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 2 (ADDR = 0x3a).
    } B;
} hw_ocotp_hdcp_key10_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY10 register
 */
#define HW_OCOTP_HDCP_KEY10_ADDR      (REGS_OCOTP_BASE + 0x8a0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY10           (*(volatile hw_ocotp_hdcp_key10_t *) HW_OCOTP_HDCP_KEY10_ADDR)
#define HW_OCOTP_HDCP_KEY10_RD()      (HW_OCOTP_HDCP_KEY10.U)
#define HW_OCOTP_HDCP_KEY10_WR(v)     (HW_OCOTP_HDCP_KEY10.U = (v))
#define HW_OCOTP_HDCP_KEY10_SET(v)    (HW_OCOTP_HDCP_KEY10_WR(HW_OCOTP_HDCP_KEY10_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY10_CLR(v)    (HW_OCOTP_HDCP_KEY10_WR(HW_OCOTP_HDCP_KEY10_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY10_TOG(v)    (HW_OCOTP_HDCP_KEY10_WR(HW_OCOTP_HDCP_KEY10_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY10 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY10, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 2 (ADDR = 0x3a).
 */

#define BP_OCOTP_HDCP_KEY10_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY10_BITS.
#define BM_OCOTP_HDCP_KEY10_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY10_BITS.

//! @brief Get value of OCOTP_HDCP_KEY10_BITS from a register value.
#define BG_OCOTP_HDCP_KEY10_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY10_BITS) >> BP_OCOTP_HDCP_KEY10_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY10_BITS.
#define BF_OCOTP_HDCP_KEY10_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY10_BITS) & BM_OCOTP_HDCP_KEY10_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY10_BITS(v)   (HW_OCOTP_HDCP_KEY10_WR((HW_OCOTP_HDCP_KEY10_RD() & ~BM_OCOTP_HDCP_KEY10_BITS) | BF_OCOTP_HDCP_KEY10_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY11 - Value of OTP Bank7 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY11 - Value of OTP Bank7 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 3 (ADDR = 0x3b).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key11
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key11_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 3 (ADDR = 0x3b).
    } B;
} hw_ocotp_hdcp_key11_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY11 register
 */
#define HW_OCOTP_HDCP_KEY11_ADDR      (REGS_OCOTP_BASE + 0x8b0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY11           (*(volatile hw_ocotp_hdcp_key11_t *) HW_OCOTP_HDCP_KEY11_ADDR)
#define HW_OCOTP_HDCP_KEY11_RD()      (HW_OCOTP_HDCP_KEY11.U)
#define HW_OCOTP_HDCP_KEY11_WR(v)     (HW_OCOTP_HDCP_KEY11.U = (v))
#define HW_OCOTP_HDCP_KEY11_SET(v)    (HW_OCOTP_HDCP_KEY11_WR(HW_OCOTP_HDCP_KEY11_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY11_CLR(v)    (HW_OCOTP_HDCP_KEY11_WR(HW_OCOTP_HDCP_KEY11_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY11_TOG(v)    (HW_OCOTP_HDCP_KEY11_WR(HW_OCOTP_HDCP_KEY11_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY11 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY11, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 3 (ADDR = 0x3b).
 */

#define BP_OCOTP_HDCP_KEY11_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY11_BITS.
#define BM_OCOTP_HDCP_KEY11_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY11_BITS.

//! @brief Get value of OCOTP_HDCP_KEY11_BITS from a register value.
#define BG_OCOTP_HDCP_KEY11_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY11_BITS) >> BP_OCOTP_HDCP_KEY11_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY11_BITS.
#define BF_OCOTP_HDCP_KEY11_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY11_BITS) & BM_OCOTP_HDCP_KEY11_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY11_BITS(v)   (HW_OCOTP_HDCP_KEY11_WR((HW_OCOTP_HDCP_KEY11_RD() & ~BM_OCOTP_HDCP_KEY11_BITS) | BF_OCOTP_HDCP_KEY11_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY12 - Value of OTP Bank7 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY12 - Value of OTP Bank7 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 4 (ADDR = 0x3c).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key12
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key12_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 4 (ADDR = 0x3c).
    } B;
} hw_ocotp_hdcp_key12_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY12 register
 */
#define HW_OCOTP_HDCP_KEY12_ADDR      (REGS_OCOTP_BASE + 0x8c0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY12           (*(volatile hw_ocotp_hdcp_key12_t *) HW_OCOTP_HDCP_KEY12_ADDR)
#define HW_OCOTP_HDCP_KEY12_RD()      (HW_OCOTP_HDCP_KEY12.U)
#define HW_OCOTP_HDCP_KEY12_WR(v)     (HW_OCOTP_HDCP_KEY12.U = (v))
#define HW_OCOTP_HDCP_KEY12_SET(v)    (HW_OCOTP_HDCP_KEY12_WR(HW_OCOTP_HDCP_KEY12_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY12_CLR(v)    (HW_OCOTP_HDCP_KEY12_WR(HW_OCOTP_HDCP_KEY12_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY12_TOG(v)    (HW_OCOTP_HDCP_KEY12_WR(HW_OCOTP_HDCP_KEY12_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY12 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY12, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 4 (ADDR = 0x3c).
 */

#define BP_OCOTP_HDCP_KEY12_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY12_BITS.
#define BM_OCOTP_HDCP_KEY12_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY12_BITS.

//! @brief Get value of OCOTP_HDCP_KEY12_BITS from a register value.
#define BG_OCOTP_HDCP_KEY12_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY12_BITS) >> BP_OCOTP_HDCP_KEY12_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY12_BITS.
#define BF_OCOTP_HDCP_KEY12_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY12_BITS) & BM_OCOTP_HDCP_KEY12_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY12_BITS(v)   (HW_OCOTP_HDCP_KEY12_WR((HW_OCOTP_HDCP_KEY12_RD() & ~BM_OCOTP_HDCP_KEY12_BITS) | BF_OCOTP_HDCP_KEY12_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY13 - Value of OTP Bank7 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY13 - Value of OTP Bank7 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 5 (ADDR = 0x3d).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key13
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key13_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 5 (ADDR = 0x3d).
    } B;
} hw_ocotp_hdcp_key13_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY13 register
 */
#define HW_OCOTP_HDCP_KEY13_ADDR      (REGS_OCOTP_BASE + 0x8d0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY13           (*(volatile hw_ocotp_hdcp_key13_t *) HW_OCOTP_HDCP_KEY13_ADDR)
#define HW_OCOTP_HDCP_KEY13_RD()      (HW_OCOTP_HDCP_KEY13.U)
#define HW_OCOTP_HDCP_KEY13_WR(v)     (HW_OCOTP_HDCP_KEY13.U = (v))
#define HW_OCOTP_HDCP_KEY13_SET(v)    (HW_OCOTP_HDCP_KEY13_WR(HW_OCOTP_HDCP_KEY13_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY13_CLR(v)    (HW_OCOTP_HDCP_KEY13_WR(HW_OCOTP_HDCP_KEY13_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY13_TOG(v)    (HW_OCOTP_HDCP_KEY13_WR(HW_OCOTP_HDCP_KEY13_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY13 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY13, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 5 (ADDR = 0x3d).
 */

#define BP_OCOTP_HDCP_KEY13_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY13_BITS.
#define BM_OCOTP_HDCP_KEY13_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY13_BITS.

//! @brief Get value of OCOTP_HDCP_KEY13_BITS from a register value.
#define BG_OCOTP_HDCP_KEY13_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY13_BITS) >> BP_OCOTP_HDCP_KEY13_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY13_BITS.
#define BF_OCOTP_HDCP_KEY13_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY13_BITS) & BM_OCOTP_HDCP_KEY13_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY13_BITS(v)   (HW_OCOTP_HDCP_KEY13_WR((HW_OCOTP_HDCP_KEY13_RD() & ~BM_OCOTP_HDCP_KEY13_BITS) | BF_OCOTP_HDCP_KEY13_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY14 - Value of OTP Bank7 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY14 - Value of OTP Bank7 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 6 (ADDR = 0x3e).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key14
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key14_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 6 (ADDR = 0x3e).
    } B;
} hw_ocotp_hdcp_key14_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY14 register
 */
#define HW_OCOTP_HDCP_KEY14_ADDR      (REGS_OCOTP_BASE + 0x8e0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY14           (*(volatile hw_ocotp_hdcp_key14_t *) HW_OCOTP_HDCP_KEY14_ADDR)
#define HW_OCOTP_HDCP_KEY14_RD()      (HW_OCOTP_HDCP_KEY14.U)
#define HW_OCOTP_HDCP_KEY14_WR(v)     (HW_OCOTP_HDCP_KEY14.U = (v))
#define HW_OCOTP_HDCP_KEY14_SET(v)    (HW_OCOTP_HDCP_KEY14_WR(HW_OCOTP_HDCP_KEY14_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY14_CLR(v)    (HW_OCOTP_HDCP_KEY14_WR(HW_OCOTP_HDCP_KEY14_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY14_TOG(v)    (HW_OCOTP_HDCP_KEY14_WR(HW_OCOTP_HDCP_KEY14_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY14 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY14, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 6 (ADDR = 0x3e).
 */

#define BP_OCOTP_HDCP_KEY14_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY14_BITS.
#define BM_OCOTP_HDCP_KEY14_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY14_BITS.

//! @brief Get value of OCOTP_HDCP_KEY14_BITS from a register value.
#define BG_OCOTP_HDCP_KEY14_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY14_BITS) >> BP_OCOTP_HDCP_KEY14_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY14_BITS.
#define BF_OCOTP_HDCP_KEY14_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY14_BITS) & BM_OCOTP_HDCP_KEY14_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY14_BITS(v)   (HW_OCOTP_HDCP_KEY14_WR((HW_OCOTP_HDCP_KEY14_RD() & ~BM_OCOTP_HDCP_KEY14_BITS) | BF_OCOTP_HDCP_KEY14_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY15 - Value of OTP Bank7 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY15 - Value of OTP Bank7 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 7, word 7 (ADDR = 0x3f).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key15
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key15_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 7, word 7 (ADDR = 0x3f).
    } B;
} hw_ocotp_hdcp_key15_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY15 register
 */
#define HW_OCOTP_HDCP_KEY15_ADDR      (REGS_OCOTP_BASE + 0x8f0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY15           (*(volatile hw_ocotp_hdcp_key15_t *) HW_OCOTP_HDCP_KEY15_ADDR)
#define HW_OCOTP_HDCP_KEY15_RD()      (HW_OCOTP_HDCP_KEY15.U)
#define HW_OCOTP_HDCP_KEY15_WR(v)     (HW_OCOTP_HDCP_KEY15.U = (v))
#define HW_OCOTP_HDCP_KEY15_SET(v)    (HW_OCOTP_HDCP_KEY15_WR(HW_OCOTP_HDCP_KEY15_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY15_CLR(v)    (HW_OCOTP_HDCP_KEY15_WR(HW_OCOTP_HDCP_KEY15_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY15_TOG(v)    (HW_OCOTP_HDCP_KEY15_WR(HW_OCOTP_HDCP_KEY15_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY15 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY15, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 7, word 7 (ADDR = 0x3f).
 */

#define BP_OCOTP_HDCP_KEY15_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY15_BITS.
#define BM_OCOTP_HDCP_KEY15_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY15_BITS.

//! @brief Get value of OCOTP_HDCP_KEY15_BITS from a register value.
#define BG_OCOTP_HDCP_KEY15_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY15_BITS) >> BP_OCOTP_HDCP_KEY15_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY15_BITS.
#define BF_OCOTP_HDCP_KEY15_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY15_BITS) & BM_OCOTP_HDCP_KEY15_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY15_BITS(v)   (HW_OCOTP_HDCP_KEY15_WR((HW_OCOTP_HDCP_KEY15_RD() & ~BM_OCOTP_HDCP_KEY15_BITS) | BF_OCOTP_HDCP_KEY15_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY16 - Value of OTP Bank8 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY16 - Value of OTP Bank8 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 0 (ADDR = 0x40).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key16
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key16_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 0 (ADDR = 0x40).
    } B;
} hw_ocotp_hdcp_key16_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY16 register
 */
#define HW_OCOTP_HDCP_KEY16_ADDR      (REGS_OCOTP_BASE + 0x900)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY16           (*(volatile hw_ocotp_hdcp_key16_t *) HW_OCOTP_HDCP_KEY16_ADDR)
#define HW_OCOTP_HDCP_KEY16_RD()      (HW_OCOTP_HDCP_KEY16.U)
#define HW_OCOTP_HDCP_KEY16_WR(v)     (HW_OCOTP_HDCP_KEY16.U = (v))
#define HW_OCOTP_HDCP_KEY16_SET(v)    (HW_OCOTP_HDCP_KEY16_WR(HW_OCOTP_HDCP_KEY16_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY16_CLR(v)    (HW_OCOTP_HDCP_KEY16_WR(HW_OCOTP_HDCP_KEY16_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY16_TOG(v)    (HW_OCOTP_HDCP_KEY16_WR(HW_OCOTP_HDCP_KEY16_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY16 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY16, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 0 (ADDR = 0x40).
 */

#define BP_OCOTP_HDCP_KEY16_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY16_BITS.
#define BM_OCOTP_HDCP_KEY16_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY16_BITS.

//! @brief Get value of OCOTP_HDCP_KEY16_BITS from a register value.
#define BG_OCOTP_HDCP_KEY16_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY16_BITS) >> BP_OCOTP_HDCP_KEY16_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY16_BITS.
#define BF_OCOTP_HDCP_KEY16_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY16_BITS) & BM_OCOTP_HDCP_KEY16_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY16_BITS(v)   (HW_OCOTP_HDCP_KEY16_WR((HW_OCOTP_HDCP_KEY16_RD() & ~BM_OCOTP_HDCP_KEY16_BITS) | BF_OCOTP_HDCP_KEY16_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY17 - Value of OTP Bank8 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY17 - Value of OTP Bank8 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 1 (ADDR = 0x41).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key17
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key17_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 1 (ADDR = 0x41).
    } B;
} hw_ocotp_hdcp_key17_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY17 register
 */
#define HW_OCOTP_HDCP_KEY17_ADDR      (REGS_OCOTP_BASE + 0x910)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY17           (*(volatile hw_ocotp_hdcp_key17_t *) HW_OCOTP_HDCP_KEY17_ADDR)
#define HW_OCOTP_HDCP_KEY17_RD()      (HW_OCOTP_HDCP_KEY17.U)
#define HW_OCOTP_HDCP_KEY17_WR(v)     (HW_OCOTP_HDCP_KEY17.U = (v))
#define HW_OCOTP_HDCP_KEY17_SET(v)    (HW_OCOTP_HDCP_KEY17_WR(HW_OCOTP_HDCP_KEY17_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY17_CLR(v)    (HW_OCOTP_HDCP_KEY17_WR(HW_OCOTP_HDCP_KEY17_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY17_TOG(v)    (HW_OCOTP_HDCP_KEY17_WR(HW_OCOTP_HDCP_KEY17_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY17 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY17, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 1 (ADDR = 0x41).
 */

#define BP_OCOTP_HDCP_KEY17_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY17_BITS.
#define BM_OCOTP_HDCP_KEY17_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY17_BITS.

//! @brief Get value of OCOTP_HDCP_KEY17_BITS from a register value.
#define BG_OCOTP_HDCP_KEY17_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY17_BITS) >> BP_OCOTP_HDCP_KEY17_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY17_BITS.
#define BF_OCOTP_HDCP_KEY17_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY17_BITS) & BM_OCOTP_HDCP_KEY17_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY17_BITS(v)   (HW_OCOTP_HDCP_KEY17_WR((HW_OCOTP_HDCP_KEY17_RD() & ~BM_OCOTP_HDCP_KEY17_BITS) | BF_OCOTP_HDCP_KEY17_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY18 - Value of OTP Bank8 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY18 - Value of OTP Bank8 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 2 (ADDR = 0x42).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key18
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key18_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 2 (ADDR = 0x42).
    } B;
} hw_ocotp_hdcp_key18_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY18 register
 */
#define HW_OCOTP_HDCP_KEY18_ADDR      (REGS_OCOTP_BASE + 0x920)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY18           (*(volatile hw_ocotp_hdcp_key18_t *) HW_OCOTP_HDCP_KEY18_ADDR)
#define HW_OCOTP_HDCP_KEY18_RD()      (HW_OCOTP_HDCP_KEY18.U)
#define HW_OCOTP_HDCP_KEY18_WR(v)     (HW_OCOTP_HDCP_KEY18.U = (v))
#define HW_OCOTP_HDCP_KEY18_SET(v)    (HW_OCOTP_HDCP_KEY18_WR(HW_OCOTP_HDCP_KEY18_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY18_CLR(v)    (HW_OCOTP_HDCP_KEY18_WR(HW_OCOTP_HDCP_KEY18_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY18_TOG(v)    (HW_OCOTP_HDCP_KEY18_WR(HW_OCOTP_HDCP_KEY18_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY18 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY18, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 2 (ADDR = 0x42).
 */

#define BP_OCOTP_HDCP_KEY18_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY18_BITS.
#define BM_OCOTP_HDCP_KEY18_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY18_BITS.

//! @brief Get value of OCOTP_HDCP_KEY18_BITS from a register value.
#define BG_OCOTP_HDCP_KEY18_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY18_BITS) >> BP_OCOTP_HDCP_KEY18_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY18_BITS.
#define BF_OCOTP_HDCP_KEY18_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY18_BITS) & BM_OCOTP_HDCP_KEY18_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY18_BITS(v)   (HW_OCOTP_HDCP_KEY18_WR((HW_OCOTP_HDCP_KEY18_RD() & ~BM_OCOTP_HDCP_KEY18_BITS) | BF_OCOTP_HDCP_KEY18_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY19 - Value of OTP Bank8 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY19 - Value of OTP Bank8 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 3 (ADDR = 0x43).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key19
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key19_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 3 (ADDR = 0x43).
    } B;
} hw_ocotp_hdcp_key19_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY19 register
 */
#define HW_OCOTP_HDCP_KEY19_ADDR      (REGS_OCOTP_BASE + 0x930)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY19           (*(volatile hw_ocotp_hdcp_key19_t *) HW_OCOTP_HDCP_KEY19_ADDR)
#define HW_OCOTP_HDCP_KEY19_RD()      (HW_OCOTP_HDCP_KEY19.U)
#define HW_OCOTP_HDCP_KEY19_WR(v)     (HW_OCOTP_HDCP_KEY19.U = (v))
#define HW_OCOTP_HDCP_KEY19_SET(v)    (HW_OCOTP_HDCP_KEY19_WR(HW_OCOTP_HDCP_KEY19_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY19_CLR(v)    (HW_OCOTP_HDCP_KEY19_WR(HW_OCOTP_HDCP_KEY19_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY19_TOG(v)    (HW_OCOTP_HDCP_KEY19_WR(HW_OCOTP_HDCP_KEY19_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY19 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY19, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 3 (ADDR = 0x43).
 */

#define BP_OCOTP_HDCP_KEY19_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY19_BITS.
#define BM_OCOTP_HDCP_KEY19_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY19_BITS.

//! @brief Get value of OCOTP_HDCP_KEY19_BITS from a register value.
#define BG_OCOTP_HDCP_KEY19_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY19_BITS) >> BP_OCOTP_HDCP_KEY19_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY19_BITS.
#define BF_OCOTP_HDCP_KEY19_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY19_BITS) & BM_OCOTP_HDCP_KEY19_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY19_BITS(v)   (HW_OCOTP_HDCP_KEY19_WR((HW_OCOTP_HDCP_KEY19_RD() & ~BM_OCOTP_HDCP_KEY19_BITS) | BF_OCOTP_HDCP_KEY19_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY20 - Value of OTP Bank8 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY20 - Value of OTP Bank8 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 4 (ADDR = 0x44).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key20
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key20_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 4 (ADDR = 0x44).
    } B;
} hw_ocotp_hdcp_key20_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY20 register
 */
#define HW_OCOTP_HDCP_KEY20_ADDR      (REGS_OCOTP_BASE + 0x940)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY20           (*(volatile hw_ocotp_hdcp_key20_t *) HW_OCOTP_HDCP_KEY20_ADDR)
#define HW_OCOTP_HDCP_KEY20_RD()      (HW_OCOTP_HDCP_KEY20.U)
#define HW_OCOTP_HDCP_KEY20_WR(v)     (HW_OCOTP_HDCP_KEY20.U = (v))
#define HW_OCOTP_HDCP_KEY20_SET(v)    (HW_OCOTP_HDCP_KEY20_WR(HW_OCOTP_HDCP_KEY20_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY20_CLR(v)    (HW_OCOTP_HDCP_KEY20_WR(HW_OCOTP_HDCP_KEY20_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY20_TOG(v)    (HW_OCOTP_HDCP_KEY20_WR(HW_OCOTP_HDCP_KEY20_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY20 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY20, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 4 (ADDR = 0x44).
 */

#define BP_OCOTP_HDCP_KEY20_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY20_BITS.
#define BM_OCOTP_HDCP_KEY20_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY20_BITS.

//! @brief Get value of OCOTP_HDCP_KEY20_BITS from a register value.
#define BG_OCOTP_HDCP_KEY20_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY20_BITS) >> BP_OCOTP_HDCP_KEY20_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY20_BITS.
#define BF_OCOTP_HDCP_KEY20_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY20_BITS) & BM_OCOTP_HDCP_KEY20_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY20_BITS(v)   (HW_OCOTP_HDCP_KEY20_WR((HW_OCOTP_HDCP_KEY20_RD() & ~BM_OCOTP_HDCP_KEY20_BITS) | BF_OCOTP_HDCP_KEY20_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY21 - Value of OTP Bank8 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY21 - Value of OTP Bank8 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 5 (ADDR = 0x45).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key21
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key21_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 5 (ADDR = 0x45).
    } B;
} hw_ocotp_hdcp_key21_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY21 register
 */
#define HW_OCOTP_HDCP_KEY21_ADDR      (REGS_OCOTP_BASE + 0x950)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY21           (*(volatile hw_ocotp_hdcp_key21_t *) HW_OCOTP_HDCP_KEY21_ADDR)
#define HW_OCOTP_HDCP_KEY21_RD()      (HW_OCOTP_HDCP_KEY21.U)
#define HW_OCOTP_HDCP_KEY21_WR(v)     (HW_OCOTP_HDCP_KEY21.U = (v))
#define HW_OCOTP_HDCP_KEY21_SET(v)    (HW_OCOTP_HDCP_KEY21_WR(HW_OCOTP_HDCP_KEY21_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY21_CLR(v)    (HW_OCOTP_HDCP_KEY21_WR(HW_OCOTP_HDCP_KEY21_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY21_TOG(v)    (HW_OCOTP_HDCP_KEY21_WR(HW_OCOTP_HDCP_KEY21_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY21 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY21, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 5 (ADDR = 0x45).
 */

#define BP_OCOTP_HDCP_KEY21_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY21_BITS.
#define BM_OCOTP_HDCP_KEY21_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY21_BITS.

//! @brief Get value of OCOTP_HDCP_KEY21_BITS from a register value.
#define BG_OCOTP_HDCP_KEY21_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY21_BITS) >> BP_OCOTP_HDCP_KEY21_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY21_BITS.
#define BF_OCOTP_HDCP_KEY21_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY21_BITS) & BM_OCOTP_HDCP_KEY21_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY21_BITS(v)   (HW_OCOTP_HDCP_KEY21_WR((HW_OCOTP_HDCP_KEY21_RD() & ~BM_OCOTP_HDCP_KEY21_BITS) | BF_OCOTP_HDCP_KEY21_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY22 - Value of OTP Bank8 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY22 - Value of OTP Bank8 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 6 (ADDR = 0x46).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key22
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key22_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 6 (ADDR = 0x46).
    } B;
} hw_ocotp_hdcp_key22_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY22 register
 */
#define HW_OCOTP_HDCP_KEY22_ADDR      (REGS_OCOTP_BASE + 0x960)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY22           (*(volatile hw_ocotp_hdcp_key22_t *) HW_OCOTP_HDCP_KEY22_ADDR)
#define HW_OCOTP_HDCP_KEY22_RD()      (HW_OCOTP_HDCP_KEY22.U)
#define HW_OCOTP_HDCP_KEY22_WR(v)     (HW_OCOTP_HDCP_KEY22.U = (v))
#define HW_OCOTP_HDCP_KEY22_SET(v)    (HW_OCOTP_HDCP_KEY22_WR(HW_OCOTP_HDCP_KEY22_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY22_CLR(v)    (HW_OCOTP_HDCP_KEY22_WR(HW_OCOTP_HDCP_KEY22_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY22_TOG(v)    (HW_OCOTP_HDCP_KEY22_WR(HW_OCOTP_HDCP_KEY22_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY22 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY22, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 6 (ADDR = 0x46).
 */

#define BP_OCOTP_HDCP_KEY22_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY22_BITS.
#define BM_OCOTP_HDCP_KEY22_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY22_BITS.

//! @brief Get value of OCOTP_HDCP_KEY22_BITS from a register value.
#define BG_OCOTP_HDCP_KEY22_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY22_BITS) >> BP_OCOTP_HDCP_KEY22_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY22_BITS.
#define BF_OCOTP_HDCP_KEY22_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY22_BITS) & BM_OCOTP_HDCP_KEY22_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY22_BITS(v)   (HW_OCOTP_HDCP_KEY22_WR((HW_OCOTP_HDCP_KEY22_RD() & ~BM_OCOTP_HDCP_KEY22_BITS) | BF_OCOTP_HDCP_KEY22_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY23 - Value of OTP Bank8 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY23 - Value of OTP Bank8 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 8, word 7 (ADDR = 0x47).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key23
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key23_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 8, word 7 (ADDR = 0x47).
    } B;
} hw_ocotp_hdcp_key23_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY23 register
 */
#define HW_OCOTP_HDCP_KEY23_ADDR      (REGS_OCOTP_BASE + 0x970)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY23           (*(volatile hw_ocotp_hdcp_key23_t *) HW_OCOTP_HDCP_KEY23_ADDR)
#define HW_OCOTP_HDCP_KEY23_RD()      (HW_OCOTP_HDCP_KEY23.U)
#define HW_OCOTP_HDCP_KEY23_WR(v)     (HW_OCOTP_HDCP_KEY23.U = (v))
#define HW_OCOTP_HDCP_KEY23_SET(v)    (HW_OCOTP_HDCP_KEY23_WR(HW_OCOTP_HDCP_KEY23_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY23_CLR(v)    (HW_OCOTP_HDCP_KEY23_WR(HW_OCOTP_HDCP_KEY23_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY23_TOG(v)    (HW_OCOTP_HDCP_KEY23_WR(HW_OCOTP_HDCP_KEY23_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY23 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY23, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 8, word 7 (ADDR = 0x47).
 */

#define BP_OCOTP_HDCP_KEY23_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY23_BITS.
#define BM_OCOTP_HDCP_KEY23_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY23_BITS.

//! @brief Get value of OCOTP_HDCP_KEY23_BITS from a register value.
#define BG_OCOTP_HDCP_KEY23_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY23_BITS) >> BP_OCOTP_HDCP_KEY23_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY23_BITS.
#define BF_OCOTP_HDCP_KEY23_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY23_BITS) & BM_OCOTP_HDCP_KEY23_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY23_BITS(v)   (HW_OCOTP_HDCP_KEY23_WR((HW_OCOTP_HDCP_KEY23_RD() & ~BM_OCOTP_HDCP_KEY23_BITS) | BF_OCOTP_HDCP_KEY23_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY24 - Value of OTP Bank9 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY24 - Value of OTP Bank9 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 0 (ADDR = 0x48).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key24
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key24_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 0 (ADDR = 0x48).
    } B;
} hw_ocotp_hdcp_key24_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY24 register
 */
#define HW_OCOTP_HDCP_KEY24_ADDR      (REGS_OCOTP_BASE + 0x980)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY24           (*(volatile hw_ocotp_hdcp_key24_t *) HW_OCOTP_HDCP_KEY24_ADDR)
#define HW_OCOTP_HDCP_KEY24_RD()      (HW_OCOTP_HDCP_KEY24.U)
#define HW_OCOTP_HDCP_KEY24_WR(v)     (HW_OCOTP_HDCP_KEY24.U = (v))
#define HW_OCOTP_HDCP_KEY24_SET(v)    (HW_OCOTP_HDCP_KEY24_WR(HW_OCOTP_HDCP_KEY24_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY24_CLR(v)    (HW_OCOTP_HDCP_KEY24_WR(HW_OCOTP_HDCP_KEY24_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY24_TOG(v)    (HW_OCOTP_HDCP_KEY24_WR(HW_OCOTP_HDCP_KEY24_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY24 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY24, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 0 (ADDR = 0x48).
 */

#define BP_OCOTP_HDCP_KEY24_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY24_BITS.
#define BM_OCOTP_HDCP_KEY24_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY24_BITS.

//! @brief Get value of OCOTP_HDCP_KEY24_BITS from a register value.
#define BG_OCOTP_HDCP_KEY24_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY24_BITS) >> BP_OCOTP_HDCP_KEY24_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY24_BITS.
#define BF_OCOTP_HDCP_KEY24_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY24_BITS) & BM_OCOTP_HDCP_KEY24_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY24_BITS(v)   (HW_OCOTP_HDCP_KEY24_WR((HW_OCOTP_HDCP_KEY24_RD() & ~BM_OCOTP_HDCP_KEY24_BITS) | BF_OCOTP_HDCP_KEY24_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY25 - Value of OTP Bank9 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY25 - Value of OTP Bank9 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 1 (ADDR = 0x49).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key25
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key25_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 1 (ADDR = 0x49).
    } B;
} hw_ocotp_hdcp_key25_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY25 register
 */
#define HW_OCOTP_HDCP_KEY25_ADDR      (REGS_OCOTP_BASE + 0x990)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY25           (*(volatile hw_ocotp_hdcp_key25_t *) HW_OCOTP_HDCP_KEY25_ADDR)
#define HW_OCOTP_HDCP_KEY25_RD()      (HW_OCOTP_HDCP_KEY25.U)
#define HW_OCOTP_HDCP_KEY25_WR(v)     (HW_OCOTP_HDCP_KEY25.U = (v))
#define HW_OCOTP_HDCP_KEY25_SET(v)    (HW_OCOTP_HDCP_KEY25_WR(HW_OCOTP_HDCP_KEY25_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY25_CLR(v)    (HW_OCOTP_HDCP_KEY25_WR(HW_OCOTP_HDCP_KEY25_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY25_TOG(v)    (HW_OCOTP_HDCP_KEY25_WR(HW_OCOTP_HDCP_KEY25_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY25 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY25, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 1 (ADDR = 0x49).
 */

#define BP_OCOTP_HDCP_KEY25_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY25_BITS.
#define BM_OCOTP_HDCP_KEY25_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY25_BITS.

//! @brief Get value of OCOTP_HDCP_KEY25_BITS from a register value.
#define BG_OCOTP_HDCP_KEY25_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY25_BITS) >> BP_OCOTP_HDCP_KEY25_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY25_BITS.
#define BF_OCOTP_HDCP_KEY25_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY25_BITS) & BM_OCOTP_HDCP_KEY25_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY25_BITS(v)   (HW_OCOTP_HDCP_KEY25_WR((HW_OCOTP_HDCP_KEY25_RD() & ~BM_OCOTP_HDCP_KEY25_BITS) | BF_OCOTP_HDCP_KEY25_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY26 - Value of OTP Bank9 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY26 - Value of OTP Bank9 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 2 (ADDR = 0x4a).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key26
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key26_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 2 (ADDR = 0x4a).
    } B;
} hw_ocotp_hdcp_key26_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY26 register
 */
#define HW_OCOTP_HDCP_KEY26_ADDR      (REGS_OCOTP_BASE + 0x9a0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY26           (*(volatile hw_ocotp_hdcp_key26_t *) HW_OCOTP_HDCP_KEY26_ADDR)
#define HW_OCOTP_HDCP_KEY26_RD()      (HW_OCOTP_HDCP_KEY26.U)
#define HW_OCOTP_HDCP_KEY26_WR(v)     (HW_OCOTP_HDCP_KEY26.U = (v))
#define HW_OCOTP_HDCP_KEY26_SET(v)    (HW_OCOTP_HDCP_KEY26_WR(HW_OCOTP_HDCP_KEY26_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY26_CLR(v)    (HW_OCOTP_HDCP_KEY26_WR(HW_OCOTP_HDCP_KEY26_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY26_TOG(v)    (HW_OCOTP_HDCP_KEY26_WR(HW_OCOTP_HDCP_KEY26_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY26 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY26, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 2 (ADDR = 0x4a).
 */

#define BP_OCOTP_HDCP_KEY26_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY26_BITS.
#define BM_OCOTP_HDCP_KEY26_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY26_BITS.

//! @brief Get value of OCOTP_HDCP_KEY26_BITS from a register value.
#define BG_OCOTP_HDCP_KEY26_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY26_BITS) >> BP_OCOTP_HDCP_KEY26_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY26_BITS.
#define BF_OCOTP_HDCP_KEY26_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY26_BITS) & BM_OCOTP_HDCP_KEY26_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY26_BITS(v)   (HW_OCOTP_HDCP_KEY26_WR((HW_OCOTP_HDCP_KEY26_RD() & ~BM_OCOTP_HDCP_KEY26_BITS) | BF_OCOTP_HDCP_KEY26_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY27 - Value of OTP Bank9 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY27 - Value of OTP Bank9 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 3 (ADDR = 0x4b).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key27
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key27_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 3 (ADDR = 0x4b).
    } B;
} hw_ocotp_hdcp_key27_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY27 register
 */
#define HW_OCOTP_HDCP_KEY27_ADDR      (REGS_OCOTP_BASE + 0x9b0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY27           (*(volatile hw_ocotp_hdcp_key27_t *) HW_OCOTP_HDCP_KEY27_ADDR)
#define HW_OCOTP_HDCP_KEY27_RD()      (HW_OCOTP_HDCP_KEY27.U)
#define HW_OCOTP_HDCP_KEY27_WR(v)     (HW_OCOTP_HDCP_KEY27.U = (v))
#define HW_OCOTP_HDCP_KEY27_SET(v)    (HW_OCOTP_HDCP_KEY27_WR(HW_OCOTP_HDCP_KEY27_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY27_CLR(v)    (HW_OCOTP_HDCP_KEY27_WR(HW_OCOTP_HDCP_KEY27_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY27_TOG(v)    (HW_OCOTP_HDCP_KEY27_WR(HW_OCOTP_HDCP_KEY27_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY27 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY27, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 3 (ADDR = 0x4b).
 */

#define BP_OCOTP_HDCP_KEY27_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY27_BITS.
#define BM_OCOTP_HDCP_KEY27_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY27_BITS.

//! @brief Get value of OCOTP_HDCP_KEY27_BITS from a register value.
#define BG_OCOTP_HDCP_KEY27_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY27_BITS) >> BP_OCOTP_HDCP_KEY27_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY27_BITS.
#define BF_OCOTP_HDCP_KEY27_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY27_BITS) & BM_OCOTP_HDCP_KEY27_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY27_BITS(v)   (HW_OCOTP_HDCP_KEY27_WR((HW_OCOTP_HDCP_KEY27_RD() & ~BM_OCOTP_HDCP_KEY27_BITS) | BF_OCOTP_HDCP_KEY27_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY28 - Value of OTP Bank9 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY28 - Value of OTP Bank9 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 4 (ADDR = 0x4c).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key28
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key28_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 4 (ADDR = 0x4c).
    } B;
} hw_ocotp_hdcp_key28_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY28 register
 */
#define HW_OCOTP_HDCP_KEY28_ADDR      (REGS_OCOTP_BASE + 0x9c0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY28           (*(volatile hw_ocotp_hdcp_key28_t *) HW_OCOTP_HDCP_KEY28_ADDR)
#define HW_OCOTP_HDCP_KEY28_RD()      (HW_OCOTP_HDCP_KEY28.U)
#define HW_OCOTP_HDCP_KEY28_WR(v)     (HW_OCOTP_HDCP_KEY28.U = (v))
#define HW_OCOTP_HDCP_KEY28_SET(v)    (HW_OCOTP_HDCP_KEY28_WR(HW_OCOTP_HDCP_KEY28_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY28_CLR(v)    (HW_OCOTP_HDCP_KEY28_WR(HW_OCOTP_HDCP_KEY28_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY28_TOG(v)    (HW_OCOTP_HDCP_KEY28_WR(HW_OCOTP_HDCP_KEY28_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY28 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY28, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 4 (ADDR = 0x4c).
 */

#define BP_OCOTP_HDCP_KEY28_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY28_BITS.
#define BM_OCOTP_HDCP_KEY28_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY28_BITS.

//! @brief Get value of OCOTP_HDCP_KEY28_BITS from a register value.
#define BG_OCOTP_HDCP_KEY28_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY28_BITS) >> BP_OCOTP_HDCP_KEY28_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY28_BITS.
#define BF_OCOTP_HDCP_KEY28_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY28_BITS) & BM_OCOTP_HDCP_KEY28_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY28_BITS(v)   (HW_OCOTP_HDCP_KEY28_WR((HW_OCOTP_HDCP_KEY28_RD() & ~BM_OCOTP_HDCP_KEY28_BITS) | BF_OCOTP_HDCP_KEY28_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY29 - Value of OTP Bank9 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY29 - Value of OTP Bank9 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 5 (ADDR = 0x4d).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key29
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key29_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 5 (ADDR = 0x4d).
    } B;
} hw_ocotp_hdcp_key29_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY29 register
 */
#define HW_OCOTP_HDCP_KEY29_ADDR      (REGS_OCOTP_BASE + 0x9d0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY29           (*(volatile hw_ocotp_hdcp_key29_t *) HW_OCOTP_HDCP_KEY29_ADDR)
#define HW_OCOTP_HDCP_KEY29_RD()      (HW_OCOTP_HDCP_KEY29.U)
#define HW_OCOTP_HDCP_KEY29_WR(v)     (HW_OCOTP_HDCP_KEY29.U = (v))
#define HW_OCOTP_HDCP_KEY29_SET(v)    (HW_OCOTP_HDCP_KEY29_WR(HW_OCOTP_HDCP_KEY29_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY29_CLR(v)    (HW_OCOTP_HDCP_KEY29_WR(HW_OCOTP_HDCP_KEY29_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY29_TOG(v)    (HW_OCOTP_HDCP_KEY29_WR(HW_OCOTP_HDCP_KEY29_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY29 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY29, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 5 (ADDR = 0x4d).
 */

#define BP_OCOTP_HDCP_KEY29_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY29_BITS.
#define BM_OCOTP_HDCP_KEY29_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY29_BITS.

//! @brief Get value of OCOTP_HDCP_KEY29_BITS from a register value.
#define BG_OCOTP_HDCP_KEY29_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY29_BITS) >> BP_OCOTP_HDCP_KEY29_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY29_BITS.
#define BF_OCOTP_HDCP_KEY29_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY29_BITS) & BM_OCOTP_HDCP_KEY29_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY29_BITS(v)   (HW_OCOTP_HDCP_KEY29_WR((HW_OCOTP_HDCP_KEY29_RD() & ~BM_OCOTP_HDCP_KEY29_BITS) | BF_OCOTP_HDCP_KEY29_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY30 - Value of OTP Bank9 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY30 - Value of OTP Bank9 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 6 (ADDR = 0x4e).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key30
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key30_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 6 (ADDR = 0x4e).
    } B;
} hw_ocotp_hdcp_key30_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY30 register
 */
#define HW_OCOTP_HDCP_KEY30_ADDR      (REGS_OCOTP_BASE + 0x9e0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY30           (*(volatile hw_ocotp_hdcp_key30_t *) HW_OCOTP_HDCP_KEY30_ADDR)
#define HW_OCOTP_HDCP_KEY30_RD()      (HW_OCOTP_HDCP_KEY30.U)
#define HW_OCOTP_HDCP_KEY30_WR(v)     (HW_OCOTP_HDCP_KEY30.U = (v))
#define HW_OCOTP_HDCP_KEY30_SET(v)    (HW_OCOTP_HDCP_KEY30_WR(HW_OCOTP_HDCP_KEY30_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY30_CLR(v)    (HW_OCOTP_HDCP_KEY30_WR(HW_OCOTP_HDCP_KEY30_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY30_TOG(v)    (HW_OCOTP_HDCP_KEY30_WR(HW_OCOTP_HDCP_KEY30_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY30 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY30, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 6 (ADDR = 0x4e).
 */

#define BP_OCOTP_HDCP_KEY30_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY30_BITS.
#define BM_OCOTP_HDCP_KEY30_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY30_BITS.

//! @brief Get value of OCOTP_HDCP_KEY30_BITS from a register value.
#define BG_OCOTP_HDCP_KEY30_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY30_BITS) >> BP_OCOTP_HDCP_KEY30_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY30_BITS.
#define BF_OCOTP_HDCP_KEY30_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY30_BITS) & BM_OCOTP_HDCP_KEY30_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY30_BITS(v)   (HW_OCOTP_HDCP_KEY30_WR((HW_OCOTP_HDCP_KEY30_RD() & ~BM_OCOTP_HDCP_KEY30_BITS) | BF_OCOTP_HDCP_KEY30_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY31 - Value of OTP Bank9 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY31 - Value of OTP Bank9 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 9, word 7 (ADDR = 0x4f).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key31
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key31_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 9, word 7 (ADDR = 0x4f).
    } B;
} hw_ocotp_hdcp_key31_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY31 register
 */
#define HW_OCOTP_HDCP_KEY31_ADDR      (REGS_OCOTP_BASE + 0x9f0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY31           (*(volatile hw_ocotp_hdcp_key31_t *) HW_OCOTP_HDCP_KEY31_ADDR)
#define HW_OCOTP_HDCP_KEY31_RD()      (HW_OCOTP_HDCP_KEY31.U)
#define HW_OCOTP_HDCP_KEY31_WR(v)     (HW_OCOTP_HDCP_KEY31.U = (v))
#define HW_OCOTP_HDCP_KEY31_SET(v)    (HW_OCOTP_HDCP_KEY31_WR(HW_OCOTP_HDCP_KEY31_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY31_CLR(v)    (HW_OCOTP_HDCP_KEY31_WR(HW_OCOTP_HDCP_KEY31_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY31_TOG(v)    (HW_OCOTP_HDCP_KEY31_WR(HW_OCOTP_HDCP_KEY31_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY31 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY31, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 9, word 7 (ADDR = 0x4f).
 */

#define BP_OCOTP_HDCP_KEY31_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY31_BITS.
#define BM_OCOTP_HDCP_KEY31_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY31_BITS.

//! @brief Get value of OCOTP_HDCP_KEY31_BITS from a register value.
#define BG_OCOTP_HDCP_KEY31_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY31_BITS) >> BP_OCOTP_HDCP_KEY31_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY31_BITS.
#define BF_OCOTP_HDCP_KEY31_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY31_BITS) & BM_OCOTP_HDCP_KEY31_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY31_BITS(v)   (HW_OCOTP_HDCP_KEY31_WR((HW_OCOTP_HDCP_KEY31_RD() & ~BM_OCOTP_HDCP_KEY31_BITS) | BF_OCOTP_HDCP_KEY31_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY32 - Value of OTP Bank10 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY32 - Value of OTP Bank10 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 0 (ADDR =
 * 0x50).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key32
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key32_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 0 (ADDR = 0x50).
    } B;
} hw_ocotp_hdcp_key32_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY32 register
 */
#define HW_OCOTP_HDCP_KEY32_ADDR      (REGS_OCOTP_BASE + 0xa00)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY32           (*(volatile hw_ocotp_hdcp_key32_t *) HW_OCOTP_HDCP_KEY32_ADDR)
#define HW_OCOTP_HDCP_KEY32_RD()      (HW_OCOTP_HDCP_KEY32.U)
#define HW_OCOTP_HDCP_KEY32_WR(v)     (HW_OCOTP_HDCP_KEY32.U = (v))
#define HW_OCOTP_HDCP_KEY32_SET(v)    (HW_OCOTP_HDCP_KEY32_WR(HW_OCOTP_HDCP_KEY32_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY32_CLR(v)    (HW_OCOTP_HDCP_KEY32_WR(HW_OCOTP_HDCP_KEY32_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY32_TOG(v)    (HW_OCOTP_HDCP_KEY32_WR(HW_OCOTP_HDCP_KEY32_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY32 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY32, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 0 (ADDR = 0x50).
 */

#define BP_OCOTP_HDCP_KEY32_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY32_BITS.
#define BM_OCOTP_HDCP_KEY32_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY32_BITS.

//! @brief Get value of OCOTP_HDCP_KEY32_BITS from a register value.
#define BG_OCOTP_HDCP_KEY32_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY32_BITS) >> BP_OCOTP_HDCP_KEY32_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY32_BITS.
#define BF_OCOTP_HDCP_KEY32_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY32_BITS) & BM_OCOTP_HDCP_KEY32_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY32_BITS(v)   (HW_OCOTP_HDCP_KEY32_WR((HW_OCOTP_HDCP_KEY32_RD() & ~BM_OCOTP_HDCP_KEY32_BITS) | BF_OCOTP_HDCP_KEY32_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY33 - Value of OTP Bank10 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY33 - Value of OTP Bank10 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 1 (ADDR =
 * 0x51).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key33
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key33_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 1 (ADDR = 0x51).
    } B;
} hw_ocotp_hdcp_key33_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY33 register
 */
#define HW_OCOTP_HDCP_KEY33_ADDR      (REGS_OCOTP_BASE + 0xa10)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY33           (*(volatile hw_ocotp_hdcp_key33_t *) HW_OCOTP_HDCP_KEY33_ADDR)
#define HW_OCOTP_HDCP_KEY33_RD()      (HW_OCOTP_HDCP_KEY33.U)
#define HW_OCOTP_HDCP_KEY33_WR(v)     (HW_OCOTP_HDCP_KEY33.U = (v))
#define HW_OCOTP_HDCP_KEY33_SET(v)    (HW_OCOTP_HDCP_KEY33_WR(HW_OCOTP_HDCP_KEY33_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY33_CLR(v)    (HW_OCOTP_HDCP_KEY33_WR(HW_OCOTP_HDCP_KEY33_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY33_TOG(v)    (HW_OCOTP_HDCP_KEY33_WR(HW_OCOTP_HDCP_KEY33_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY33 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY33, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 1 (ADDR = 0x51).
 */

#define BP_OCOTP_HDCP_KEY33_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY33_BITS.
#define BM_OCOTP_HDCP_KEY33_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY33_BITS.

//! @brief Get value of OCOTP_HDCP_KEY33_BITS from a register value.
#define BG_OCOTP_HDCP_KEY33_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY33_BITS) >> BP_OCOTP_HDCP_KEY33_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY33_BITS.
#define BF_OCOTP_HDCP_KEY33_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY33_BITS) & BM_OCOTP_HDCP_KEY33_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY33_BITS(v)   (HW_OCOTP_HDCP_KEY33_WR((HW_OCOTP_HDCP_KEY33_RD() & ~BM_OCOTP_HDCP_KEY33_BITS) | BF_OCOTP_HDCP_KEY33_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY34 - Value of OTP Bank10 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY34 - Value of OTP Bank10 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 2 (ADDR =
 * 0x52).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key34
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key34_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 2 (ADDR = 0x52).
    } B;
} hw_ocotp_hdcp_key34_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY34 register
 */
#define HW_OCOTP_HDCP_KEY34_ADDR      (REGS_OCOTP_BASE + 0xa20)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY34           (*(volatile hw_ocotp_hdcp_key34_t *) HW_OCOTP_HDCP_KEY34_ADDR)
#define HW_OCOTP_HDCP_KEY34_RD()      (HW_OCOTP_HDCP_KEY34.U)
#define HW_OCOTP_HDCP_KEY34_WR(v)     (HW_OCOTP_HDCP_KEY34.U = (v))
#define HW_OCOTP_HDCP_KEY34_SET(v)    (HW_OCOTP_HDCP_KEY34_WR(HW_OCOTP_HDCP_KEY34_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY34_CLR(v)    (HW_OCOTP_HDCP_KEY34_WR(HW_OCOTP_HDCP_KEY34_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY34_TOG(v)    (HW_OCOTP_HDCP_KEY34_WR(HW_OCOTP_HDCP_KEY34_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY34 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY34, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 2 (ADDR = 0x52).
 */

#define BP_OCOTP_HDCP_KEY34_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY34_BITS.
#define BM_OCOTP_HDCP_KEY34_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY34_BITS.

//! @brief Get value of OCOTP_HDCP_KEY34_BITS from a register value.
#define BG_OCOTP_HDCP_KEY34_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY34_BITS) >> BP_OCOTP_HDCP_KEY34_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY34_BITS.
#define BF_OCOTP_HDCP_KEY34_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY34_BITS) & BM_OCOTP_HDCP_KEY34_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY34_BITS(v)   (HW_OCOTP_HDCP_KEY34_WR((HW_OCOTP_HDCP_KEY34_RD() & ~BM_OCOTP_HDCP_KEY34_BITS) | BF_OCOTP_HDCP_KEY34_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY35 - Value of OTP Bank10 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY35 - Value of OTP Bank10 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 3 (ADDR =
 * 0x53).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key35
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key35_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 3 (ADDR = 0x53).
    } B;
} hw_ocotp_hdcp_key35_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY35 register
 */
#define HW_OCOTP_HDCP_KEY35_ADDR      (REGS_OCOTP_BASE + 0xa30)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY35           (*(volatile hw_ocotp_hdcp_key35_t *) HW_OCOTP_HDCP_KEY35_ADDR)
#define HW_OCOTP_HDCP_KEY35_RD()      (HW_OCOTP_HDCP_KEY35.U)
#define HW_OCOTP_HDCP_KEY35_WR(v)     (HW_OCOTP_HDCP_KEY35.U = (v))
#define HW_OCOTP_HDCP_KEY35_SET(v)    (HW_OCOTP_HDCP_KEY35_WR(HW_OCOTP_HDCP_KEY35_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY35_CLR(v)    (HW_OCOTP_HDCP_KEY35_WR(HW_OCOTP_HDCP_KEY35_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY35_TOG(v)    (HW_OCOTP_HDCP_KEY35_WR(HW_OCOTP_HDCP_KEY35_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY35 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY35, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 3 (ADDR = 0x53).
 */

#define BP_OCOTP_HDCP_KEY35_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY35_BITS.
#define BM_OCOTP_HDCP_KEY35_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY35_BITS.

//! @brief Get value of OCOTP_HDCP_KEY35_BITS from a register value.
#define BG_OCOTP_HDCP_KEY35_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY35_BITS) >> BP_OCOTP_HDCP_KEY35_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY35_BITS.
#define BF_OCOTP_HDCP_KEY35_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY35_BITS) & BM_OCOTP_HDCP_KEY35_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY35_BITS(v)   (HW_OCOTP_HDCP_KEY35_WR((HW_OCOTP_HDCP_KEY35_RD() & ~BM_OCOTP_HDCP_KEY35_BITS) | BF_OCOTP_HDCP_KEY35_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY36 - Value of OTP Bank10 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY36 - Value of OTP Bank10 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 4 (ADDR =
 * 0x54).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key36
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key36_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 4 (ADDR = 0x54).
    } B;
} hw_ocotp_hdcp_key36_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY36 register
 */
#define HW_OCOTP_HDCP_KEY36_ADDR      (REGS_OCOTP_BASE + 0xa40)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY36           (*(volatile hw_ocotp_hdcp_key36_t *) HW_OCOTP_HDCP_KEY36_ADDR)
#define HW_OCOTP_HDCP_KEY36_RD()      (HW_OCOTP_HDCP_KEY36.U)
#define HW_OCOTP_HDCP_KEY36_WR(v)     (HW_OCOTP_HDCP_KEY36.U = (v))
#define HW_OCOTP_HDCP_KEY36_SET(v)    (HW_OCOTP_HDCP_KEY36_WR(HW_OCOTP_HDCP_KEY36_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY36_CLR(v)    (HW_OCOTP_HDCP_KEY36_WR(HW_OCOTP_HDCP_KEY36_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY36_TOG(v)    (HW_OCOTP_HDCP_KEY36_WR(HW_OCOTP_HDCP_KEY36_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY36 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY36, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 4 (ADDR = 0x54).
 */

#define BP_OCOTP_HDCP_KEY36_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY36_BITS.
#define BM_OCOTP_HDCP_KEY36_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY36_BITS.

//! @brief Get value of OCOTP_HDCP_KEY36_BITS from a register value.
#define BG_OCOTP_HDCP_KEY36_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY36_BITS) >> BP_OCOTP_HDCP_KEY36_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY36_BITS.
#define BF_OCOTP_HDCP_KEY36_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY36_BITS) & BM_OCOTP_HDCP_KEY36_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY36_BITS(v)   (HW_OCOTP_HDCP_KEY36_WR((HW_OCOTP_HDCP_KEY36_RD() & ~BM_OCOTP_HDCP_KEY36_BITS) | BF_OCOTP_HDCP_KEY36_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY37 - Value of OTP Bank10 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY37 - Value of OTP Bank10 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 5 (ADDR =
 * 0x55).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key37
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key37_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 5 (ADDR = 0x55).
    } B;
} hw_ocotp_hdcp_key37_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY37 register
 */
#define HW_OCOTP_HDCP_KEY37_ADDR      (REGS_OCOTP_BASE + 0xa50)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY37           (*(volatile hw_ocotp_hdcp_key37_t *) HW_OCOTP_HDCP_KEY37_ADDR)
#define HW_OCOTP_HDCP_KEY37_RD()      (HW_OCOTP_HDCP_KEY37.U)
#define HW_OCOTP_HDCP_KEY37_WR(v)     (HW_OCOTP_HDCP_KEY37.U = (v))
#define HW_OCOTP_HDCP_KEY37_SET(v)    (HW_OCOTP_HDCP_KEY37_WR(HW_OCOTP_HDCP_KEY37_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY37_CLR(v)    (HW_OCOTP_HDCP_KEY37_WR(HW_OCOTP_HDCP_KEY37_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY37_TOG(v)    (HW_OCOTP_HDCP_KEY37_WR(HW_OCOTP_HDCP_KEY37_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY37 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY37, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 5 (ADDR = 0x55).
 */

#define BP_OCOTP_HDCP_KEY37_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY37_BITS.
#define BM_OCOTP_HDCP_KEY37_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY37_BITS.

//! @brief Get value of OCOTP_HDCP_KEY37_BITS from a register value.
#define BG_OCOTP_HDCP_KEY37_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY37_BITS) >> BP_OCOTP_HDCP_KEY37_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY37_BITS.
#define BF_OCOTP_HDCP_KEY37_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY37_BITS) & BM_OCOTP_HDCP_KEY37_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY37_BITS(v)   (HW_OCOTP_HDCP_KEY37_WR((HW_OCOTP_HDCP_KEY37_RD() & ~BM_OCOTP_HDCP_KEY37_BITS) | BF_OCOTP_HDCP_KEY37_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY38 - Value of OTP Bank10 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY38 - Value of OTP Bank10 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 6 (ADDR =
 * 0x56).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key38
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key38_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 6 (ADDR = 0x56).
    } B;
} hw_ocotp_hdcp_key38_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY38 register
 */
#define HW_OCOTP_HDCP_KEY38_ADDR      (REGS_OCOTP_BASE + 0xa60)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY38           (*(volatile hw_ocotp_hdcp_key38_t *) HW_OCOTP_HDCP_KEY38_ADDR)
#define HW_OCOTP_HDCP_KEY38_RD()      (HW_OCOTP_HDCP_KEY38.U)
#define HW_OCOTP_HDCP_KEY38_WR(v)     (HW_OCOTP_HDCP_KEY38.U = (v))
#define HW_OCOTP_HDCP_KEY38_SET(v)    (HW_OCOTP_HDCP_KEY38_WR(HW_OCOTP_HDCP_KEY38_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY38_CLR(v)    (HW_OCOTP_HDCP_KEY38_WR(HW_OCOTP_HDCP_KEY38_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY38_TOG(v)    (HW_OCOTP_HDCP_KEY38_WR(HW_OCOTP_HDCP_KEY38_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY38 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY38, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 6 (ADDR = 0x56).
 */

#define BP_OCOTP_HDCP_KEY38_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY38_BITS.
#define BM_OCOTP_HDCP_KEY38_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY38_BITS.

//! @brief Get value of OCOTP_HDCP_KEY38_BITS from a register value.
#define BG_OCOTP_HDCP_KEY38_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY38_BITS) >> BP_OCOTP_HDCP_KEY38_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY38_BITS.
#define BF_OCOTP_HDCP_KEY38_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY38_BITS) & BM_OCOTP_HDCP_KEY38_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY38_BITS(v)   (HW_OCOTP_HDCP_KEY38_WR((HW_OCOTP_HDCP_KEY38_RD() & ~BM_OCOTP_HDCP_KEY38_BITS) | BF_OCOTP_HDCP_KEY38_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY39 - Value of OTP Bank10 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY39 - Value of OTP Bank10 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 10, word 7 (ADDR =
 * 0x57).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key39
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key39_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 10, word 7 (ADDR = 0x57).
    } B;
} hw_ocotp_hdcp_key39_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY39 register
 */
#define HW_OCOTP_HDCP_KEY39_ADDR      (REGS_OCOTP_BASE + 0xa70)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY39           (*(volatile hw_ocotp_hdcp_key39_t *) HW_OCOTP_HDCP_KEY39_ADDR)
#define HW_OCOTP_HDCP_KEY39_RD()      (HW_OCOTP_HDCP_KEY39.U)
#define HW_OCOTP_HDCP_KEY39_WR(v)     (HW_OCOTP_HDCP_KEY39.U = (v))
#define HW_OCOTP_HDCP_KEY39_SET(v)    (HW_OCOTP_HDCP_KEY39_WR(HW_OCOTP_HDCP_KEY39_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY39_CLR(v)    (HW_OCOTP_HDCP_KEY39_WR(HW_OCOTP_HDCP_KEY39_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY39_TOG(v)    (HW_OCOTP_HDCP_KEY39_WR(HW_OCOTP_HDCP_KEY39_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY39 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY39, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 10, word 7 (ADDR = 0x57).
 */

#define BP_OCOTP_HDCP_KEY39_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY39_BITS.
#define BM_OCOTP_HDCP_KEY39_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY39_BITS.

//! @brief Get value of OCOTP_HDCP_KEY39_BITS from a register value.
#define BG_OCOTP_HDCP_KEY39_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY39_BITS) >> BP_OCOTP_HDCP_KEY39_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY39_BITS.
#define BF_OCOTP_HDCP_KEY39_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY39_BITS) & BM_OCOTP_HDCP_KEY39_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY39_BITS(v)   (HW_OCOTP_HDCP_KEY39_WR((HW_OCOTP_HDCP_KEY39_RD() & ~BM_OCOTP_HDCP_KEY39_BITS) | BF_OCOTP_HDCP_KEY39_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY40 - Value of OTP Bank11 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY40 - Value of OTP Bank11 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 0 (ADDR =
 * 0x58).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key40
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key40_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 0 (ADDR = 0x58).
    } B;
} hw_ocotp_hdcp_key40_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY40 register
 */
#define HW_OCOTP_HDCP_KEY40_ADDR      (REGS_OCOTP_BASE + 0xa80)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY40           (*(volatile hw_ocotp_hdcp_key40_t *) HW_OCOTP_HDCP_KEY40_ADDR)
#define HW_OCOTP_HDCP_KEY40_RD()      (HW_OCOTP_HDCP_KEY40.U)
#define HW_OCOTP_HDCP_KEY40_WR(v)     (HW_OCOTP_HDCP_KEY40.U = (v))
#define HW_OCOTP_HDCP_KEY40_SET(v)    (HW_OCOTP_HDCP_KEY40_WR(HW_OCOTP_HDCP_KEY40_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY40_CLR(v)    (HW_OCOTP_HDCP_KEY40_WR(HW_OCOTP_HDCP_KEY40_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY40_TOG(v)    (HW_OCOTP_HDCP_KEY40_WR(HW_OCOTP_HDCP_KEY40_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY40 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY40, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 0 (ADDR = 0x58).
 */

#define BP_OCOTP_HDCP_KEY40_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY40_BITS.
#define BM_OCOTP_HDCP_KEY40_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY40_BITS.

//! @brief Get value of OCOTP_HDCP_KEY40_BITS from a register value.
#define BG_OCOTP_HDCP_KEY40_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY40_BITS) >> BP_OCOTP_HDCP_KEY40_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY40_BITS.
#define BF_OCOTP_HDCP_KEY40_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY40_BITS) & BM_OCOTP_HDCP_KEY40_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY40_BITS(v)   (HW_OCOTP_HDCP_KEY40_WR((HW_OCOTP_HDCP_KEY40_RD() & ~BM_OCOTP_HDCP_KEY40_BITS) | BF_OCOTP_HDCP_KEY40_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY41 - Value of OTP Bank11 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY41 - Value of OTP Bank11 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 1 (ADDR =
 * 0x59).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key41
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key41_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 1 (ADDR = 0x59).
    } B;
} hw_ocotp_hdcp_key41_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY41 register
 */
#define HW_OCOTP_HDCP_KEY41_ADDR      (REGS_OCOTP_BASE + 0xa90)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY41           (*(volatile hw_ocotp_hdcp_key41_t *) HW_OCOTP_HDCP_KEY41_ADDR)
#define HW_OCOTP_HDCP_KEY41_RD()      (HW_OCOTP_HDCP_KEY41.U)
#define HW_OCOTP_HDCP_KEY41_WR(v)     (HW_OCOTP_HDCP_KEY41.U = (v))
#define HW_OCOTP_HDCP_KEY41_SET(v)    (HW_OCOTP_HDCP_KEY41_WR(HW_OCOTP_HDCP_KEY41_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY41_CLR(v)    (HW_OCOTP_HDCP_KEY41_WR(HW_OCOTP_HDCP_KEY41_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY41_TOG(v)    (HW_OCOTP_HDCP_KEY41_WR(HW_OCOTP_HDCP_KEY41_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY41 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY41, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 1 (ADDR = 0x59).
 */

#define BP_OCOTP_HDCP_KEY41_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY41_BITS.
#define BM_OCOTP_HDCP_KEY41_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY41_BITS.

//! @brief Get value of OCOTP_HDCP_KEY41_BITS from a register value.
#define BG_OCOTP_HDCP_KEY41_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY41_BITS) >> BP_OCOTP_HDCP_KEY41_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY41_BITS.
#define BF_OCOTP_HDCP_KEY41_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY41_BITS) & BM_OCOTP_HDCP_KEY41_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY41_BITS(v)   (HW_OCOTP_HDCP_KEY41_WR((HW_OCOTP_HDCP_KEY41_RD() & ~BM_OCOTP_HDCP_KEY41_BITS) | BF_OCOTP_HDCP_KEY41_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY42 - Value of OTP Bank11 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY42 - Value of OTP Bank11 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 2 (ADDR =
 * 0x5a).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key42
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key42_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 2 (ADDR = 0x5a).
    } B;
} hw_ocotp_hdcp_key42_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY42 register
 */
#define HW_OCOTP_HDCP_KEY42_ADDR      (REGS_OCOTP_BASE + 0xaa0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY42           (*(volatile hw_ocotp_hdcp_key42_t *) HW_OCOTP_HDCP_KEY42_ADDR)
#define HW_OCOTP_HDCP_KEY42_RD()      (HW_OCOTP_HDCP_KEY42.U)
#define HW_OCOTP_HDCP_KEY42_WR(v)     (HW_OCOTP_HDCP_KEY42.U = (v))
#define HW_OCOTP_HDCP_KEY42_SET(v)    (HW_OCOTP_HDCP_KEY42_WR(HW_OCOTP_HDCP_KEY42_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY42_CLR(v)    (HW_OCOTP_HDCP_KEY42_WR(HW_OCOTP_HDCP_KEY42_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY42_TOG(v)    (HW_OCOTP_HDCP_KEY42_WR(HW_OCOTP_HDCP_KEY42_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY42 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY42, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 2 (ADDR = 0x5a).
 */

#define BP_OCOTP_HDCP_KEY42_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY42_BITS.
#define BM_OCOTP_HDCP_KEY42_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY42_BITS.

//! @brief Get value of OCOTP_HDCP_KEY42_BITS from a register value.
#define BG_OCOTP_HDCP_KEY42_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY42_BITS) >> BP_OCOTP_HDCP_KEY42_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY42_BITS.
#define BF_OCOTP_HDCP_KEY42_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY42_BITS) & BM_OCOTP_HDCP_KEY42_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY42_BITS(v)   (HW_OCOTP_HDCP_KEY42_WR((HW_OCOTP_HDCP_KEY42_RD() & ~BM_OCOTP_HDCP_KEY42_BITS) | BF_OCOTP_HDCP_KEY42_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY43 - Value of OTP Bank11 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY43 - Value of OTP Bank11 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 3 (ADDR =
 * 0x5b).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key43
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key43_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 3 (ADDR = 0x5b).
    } B;
} hw_ocotp_hdcp_key43_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY43 register
 */
#define HW_OCOTP_HDCP_KEY43_ADDR      (REGS_OCOTP_BASE + 0xab0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY43           (*(volatile hw_ocotp_hdcp_key43_t *) HW_OCOTP_HDCP_KEY43_ADDR)
#define HW_OCOTP_HDCP_KEY43_RD()      (HW_OCOTP_HDCP_KEY43.U)
#define HW_OCOTP_HDCP_KEY43_WR(v)     (HW_OCOTP_HDCP_KEY43.U = (v))
#define HW_OCOTP_HDCP_KEY43_SET(v)    (HW_OCOTP_HDCP_KEY43_WR(HW_OCOTP_HDCP_KEY43_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY43_CLR(v)    (HW_OCOTP_HDCP_KEY43_WR(HW_OCOTP_HDCP_KEY43_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY43_TOG(v)    (HW_OCOTP_HDCP_KEY43_WR(HW_OCOTP_HDCP_KEY43_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY43 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY43, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 3 (ADDR = 0x5b).
 */

#define BP_OCOTP_HDCP_KEY43_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY43_BITS.
#define BM_OCOTP_HDCP_KEY43_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY43_BITS.

//! @brief Get value of OCOTP_HDCP_KEY43_BITS from a register value.
#define BG_OCOTP_HDCP_KEY43_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY43_BITS) >> BP_OCOTP_HDCP_KEY43_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY43_BITS.
#define BF_OCOTP_HDCP_KEY43_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY43_BITS) & BM_OCOTP_HDCP_KEY43_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY43_BITS(v)   (HW_OCOTP_HDCP_KEY43_WR((HW_OCOTP_HDCP_KEY43_RD() & ~BM_OCOTP_HDCP_KEY43_BITS) | BF_OCOTP_HDCP_KEY43_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY44 - Value of OTP Bank11 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY44 - Value of OTP Bank11 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 4 (ADDR =
 * 0x5c).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key44
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key44_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 4 (ADDR = 0x5c).
    } B;
} hw_ocotp_hdcp_key44_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY44 register
 */
#define HW_OCOTP_HDCP_KEY44_ADDR      (REGS_OCOTP_BASE + 0xac0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY44           (*(volatile hw_ocotp_hdcp_key44_t *) HW_OCOTP_HDCP_KEY44_ADDR)
#define HW_OCOTP_HDCP_KEY44_RD()      (HW_OCOTP_HDCP_KEY44.U)
#define HW_OCOTP_HDCP_KEY44_WR(v)     (HW_OCOTP_HDCP_KEY44.U = (v))
#define HW_OCOTP_HDCP_KEY44_SET(v)    (HW_OCOTP_HDCP_KEY44_WR(HW_OCOTP_HDCP_KEY44_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY44_CLR(v)    (HW_OCOTP_HDCP_KEY44_WR(HW_OCOTP_HDCP_KEY44_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY44_TOG(v)    (HW_OCOTP_HDCP_KEY44_WR(HW_OCOTP_HDCP_KEY44_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY44 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY44, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 4 (ADDR = 0x5c).
 */

#define BP_OCOTP_HDCP_KEY44_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY44_BITS.
#define BM_OCOTP_HDCP_KEY44_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY44_BITS.

//! @brief Get value of OCOTP_HDCP_KEY44_BITS from a register value.
#define BG_OCOTP_HDCP_KEY44_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY44_BITS) >> BP_OCOTP_HDCP_KEY44_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY44_BITS.
#define BF_OCOTP_HDCP_KEY44_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY44_BITS) & BM_OCOTP_HDCP_KEY44_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY44_BITS(v)   (HW_OCOTP_HDCP_KEY44_WR((HW_OCOTP_HDCP_KEY44_RD() & ~BM_OCOTP_HDCP_KEY44_BITS) | BF_OCOTP_HDCP_KEY44_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY45 - Value of OTP Bank11 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY45 - Value of OTP Bank11 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 5 (ADDR =
 * 0x5d).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key45
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key45_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 5 (ADDR = 0x5d).
    } B;
} hw_ocotp_hdcp_key45_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY45 register
 */
#define HW_OCOTP_HDCP_KEY45_ADDR      (REGS_OCOTP_BASE + 0xad0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY45           (*(volatile hw_ocotp_hdcp_key45_t *) HW_OCOTP_HDCP_KEY45_ADDR)
#define HW_OCOTP_HDCP_KEY45_RD()      (HW_OCOTP_HDCP_KEY45.U)
#define HW_OCOTP_HDCP_KEY45_WR(v)     (HW_OCOTP_HDCP_KEY45.U = (v))
#define HW_OCOTP_HDCP_KEY45_SET(v)    (HW_OCOTP_HDCP_KEY45_WR(HW_OCOTP_HDCP_KEY45_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY45_CLR(v)    (HW_OCOTP_HDCP_KEY45_WR(HW_OCOTP_HDCP_KEY45_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY45_TOG(v)    (HW_OCOTP_HDCP_KEY45_WR(HW_OCOTP_HDCP_KEY45_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY45 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY45, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 5 (ADDR = 0x5d).
 */

#define BP_OCOTP_HDCP_KEY45_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY45_BITS.
#define BM_OCOTP_HDCP_KEY45_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY45_BITS.

//! @brief Get value of OCOTP_HDCP_KEY45_BITS from a register value.
#define BG_OCOTP_HDCP_KEY45_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY45_BITS) >> BP_OCOTP_HDCP_KEY45_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY45_BITS.
#define BF_OCOTP_HDCP_KEY45_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY45_BITS) & BM_OCOTP_HDCP_KEY45_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY45_BITS(v)   (HW_OCOTP_HDCP_KEY45_WR((HW_OCOTP_HDCP_KEY45_RD() & ~BM_OCOTP_HDCP_KEY45_BITS) | BF_OCOTP_HDCP_KEY45_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY46 - Value of OTP Bank11 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY46 - Value of OTP Bank11 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 6 (ADDR =
 * 0x5e).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key46
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key46_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 6 (ADDR = 0x5e).
    } B;
} hw_ocotp_hdcp_key46_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY46 register
 */
#define HW_OCOTP_HDCP_KEY46_ADDR      (REGS_OCOTP_BASE + 0xae0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY46           (*(volatile hw_ocotp_hdcp_key46_t *) HW_OCOTP_HDCP_KEY46_ADDR)
#define HW_OCOTP_HDCP_KEY46_RD()      (HW_OCOTP_HDCP_KEY46.U)
#define HW_OCOTP_HDCP_KEY46_WR(v)     (HW_OCOTP_HDCP_KEY46.U = (v))
#define HW_OCOTP_HDCP_KEY46_SET(v)    (HW_OCOTP_HDCP_KEY46_WR(HW_OCOTP_HDCP_KEY46_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY46_CLR(v)    (HW_OCOTP_HDCP_KEY46_WR(HW_OCOTP_HDCP_KEY46_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY46_TOG(v)    (HW_OCOTP_HDCP_KEY46_WR(HW_OCOTP_HDCP_KEY46_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY46 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY46, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 6 (ADDR = 0x5e).
 */

#define BP_OCOTP_HDCP_KEY46_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY46_BITS.
#define BM_OCOTP_HDCP_KEY46_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY46_BITS.

//! @brief Get value of OCOTP_HDCP_KEY46_BITS from a register value.
#define BG_OCOTP_HDCP_KEY46_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY46_BITS) >> BP_OCOTP_HDCP_KEY46_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY46_BITS.
#define BF_OCOTP_HDCP_KEY46_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY46_BITS) & BM_OCOTP_HDCP_KEY46_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY46_BITS(v)   (HW_OCOTP_HDCP_KEY46_WR((HW_OCOTP_HDCP_KEY46_RD() & ~BM_OCOTP_HDCP_KEY46_BITS) | BF_OCOTP_HDCP_KEY46_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY47 - Value of OTP Bank11 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY47 - Value of OTP Bank11 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 11, word 7 (ADDR =
 * 0x5f).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key47
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key47_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 11, word 7 (ADDR = 0x5f).
    } B;
} hw_ocotp_hdcp_key47_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY47 register
 */
#define HW_OCOTP_HDCP_KEY47_ADDR      (REGS_OCOTP_BASE + 0xaf0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY47           (*(volatile hw_ocotp_hdcp_key47_t *) HW_OCOTP_HDCP_KEY47_ADDR)
#define HW_OCOTP_HDCP_KEY47_RD()      (HW_OCOTP_HDCP_KEY47.U)
#define HW_OCOTP_HDCP_KEY47_WR(v)     (HW_OCOTP_HDCP_KEY47.U = (v))
#define HW_OCOTP_HDCP_KEY47_SET(v)    (HW_OCOTP_HDCP_KEY47_WR(HW_OCOTP_HDCP_KEY47_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY47_CLR(v)    (HW_OCOTP_HDCP_KEY47_WR(HW_OCOTP_HDCP_KEY47_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY47_TOG(v)    (HW_OCOTP_HDCP_KEY47_WR(HW_OCOTP_HDCP_KEY47_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY47 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY47, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 11, word 7 (ADDR = 0x5f).
 */

#define BP_OCOTP_HDCP_KEY47_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY47_BITS.
#define BM_OCOTP_HDCP_KEY47_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY47_BITS.

//! @brief Get value of OCOTP_HDCP_KEY47_BITS from a register value.
#define BG_OCOTP_HDCP_KEY47_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY47_BITS) >> BP_OCOTP_HDCP_KEY47_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY47_BITS.
#define BF_OCOTP_HDCP_KEY47_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY47_BITS) & BM_OCOTP_HDCP_KEY47_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY47_BITS(v)   (HW_OCOTP_HDCP_KEY47_WR((HW_OCOTP_HDCP_KEY47_RD() & ~BM_OCOTP_HDCP_KEY47_BITS) | BF_OCOTP_HDCP_KEY47_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY48 - Value of OTP Bank12 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY48 - Value of OTP Bank12 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 0 (ADDR =
 * 0x60).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key48
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key48_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 0 (ADDR = 0x60).
    } B;
} hw_ocotp_hdcp_key48_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY48 register
 */
#define HW_OCOTP_HDCP_KEY48_ADDR      (REGS_OCOTP_BASE + 0xb00)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY48           (*(volatile hw_ocotp_hdcp_key48_t *) HW_OCOTP_HDCP_KEY48_ADDR)
#define HW_OCOTP_HDCP_KEY48_RD()      (HW_OCOTP_HDCP_KEY48.U)
#define HW_OCOTP_HDCP_KEY48_WR(v)     (HW_OCOTP_HDCP_KEY48.U = (v))
#define HW_OCOTP_HDCP_KEY48_SET(v)    (HW_OCOTP_HDCP_KEY48_WR(HW_OCOTP_HDCP_KEY48_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY48_CLR(v)    (HW_OCOTP_HDCP_KEY48_WR(HW_OCOTP_HDCP_KEY48_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY48_TOG(v)    (HW_OCOTP_HDCP_KEY48_WR(HW_OCOTP_HDCP_KEY48_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY48 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY48, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 0 (ADDR = 0x60).
 */

#define BP_OCOTP_HDCP_KEY48_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY48_BITS.
#define BM_OCOTP_HDCP_KEY48_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY48_BITS.

//! @brief Get value of OCOTP_HDCP_KEY48_BITS from a register value.
#define BG_OCOTP_HDCP_KEY48_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY48_BITS) >> BP_OCOTP_HDCP_KEY48_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY48_BITS.
#define BF_OCOTP_HDCP_KEY48_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY48_BITS) & BM_OCOTP_HDCP_KEY48_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY48_BITS(v)   (HW_OCOTP_HDCP_KEY48_WR((HW_OCOTP_HDCP_KEY48_RD() & ~BM_OCOTP_HDCP_KEY48_BITS) | BF_OCOTP_HDCP_KEY48_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY49 - Value of OTP Bank12 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY49 - Value of OTP Bank12 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 1 (ADDR =
 * 0x61).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key49
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key49_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 1 (ADDR = 0x61).
    } B;
} hw_ocotp_hdcp_key49_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY49 register
 */
#define HW_OCOTP_HDCP_KEY49_ADDR      (REGS_OCOTP_BASE + 0xb10)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY49           (*(volatile hw_ocotp_hdcp_key49_t *) HW_OCOTP_HDCP_KEY49_ADDR)
#define HW_OCOTP_HDCP_KEY49_RD()      (HW_OCOTP_HDCP_KEY49.U)
#define HW_OCOTP_HDCP_KEY49_WR(v)     (HW_OCOTP_HDCP_KEY49.U = (v))
#define HW_OCOTP_HDCP_KEY49_SET(v)    (HW_OCOTP_HDCP_KEY49_WR(HW_OCOTP_HDCP_KEY49_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY49_CLR(v)    (HW_OCOTP_HDCP_KEY49_WR(HW_OCOTP_HDCP_KEY49_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY49_TOG(v)    (HW_OCOTP_HDCP_KEY49_WR(HW_OCOTP_HDCP_KEY49_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY49 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY49, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 1 (ADDR = 0x61).
 */

#define BP_OCOTP_HDCP_KEY49_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY49_BITS.
#define BM_OCOTP_HDCP_KEY49_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY49_BITS.

//! @brief Get value of OCOTP_HDCP_KEY49_BITS from a register value.
#define BG_OCOTP_HDCP_KEY49_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY49_BITS) >> BP_OCOTP_HDCP_KEY49_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY49_BITS.
#define BF_OCOTP_HDCP_KEY49_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY49_BITS) & BM_OCOTP_HDCP_KEY49_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY49_BITS(v)   (HW_OCOTP_HDCP_KEY49_WR((HW_OCOTP_HDCP_KEY49_RD() & ~BM_OCOTP_HDCP_KEY49_BITS) | BF_OCOTP_HDCP_KEY49_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY50 - Value of OTP Bank12 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY50 - Value of OTP Bank12 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 2 (ADDR =
 * 0x62).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key50
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key50_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 2 (ADDR = 0x62).
    } B;
} hw_ocotp_hdcp_key50_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY50 register
 */
#define HW_OCOTP_HDCP_KEY50_ADDR      (REGS_OCOTP_BASE + 0xb20)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY50           (*(volatile hw_ocotp_hdcp_key50_t *) HW_OCOTP_HDCP_KEY50_ADDR)
#define HW_OCOTP_HDCP_KEY50_RD()      (HW_OCOTP_HDCP_KEY50.U)
#define HW_OCOTP_HDCP_KEY50_WR(v)     (HW_OCOTP_HDCP_KEY50.U = (v))
#define HW_OCOTP_HDCP_KEY50_SET(v)    (HW_OCOTP_HDCP_KEY50_WR(HW_OCOTP_HDCP_KEY50_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY50_CLR(v)    (HW_OCOTP_HDCP_KEY50_WR(HW_OCOTP_HDCP_KEY50_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY50_TOG(v)    (HW_OCOTP_HDCP_KEY50_WR(HW_OCOTP_HDCP_KEY50_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY50 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY50, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 2 (ADDR = 0x62).
 */

#define BP_OCOTP_HDCP_KEY50_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY50_BITS.
#define BM_OCOTP_HDCP_KEY50_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY50_BITS.

//! @brief Get value of OCOTP_HDCP_KEY50_BITS from a register value.
#define BG_OCOTP_HDCP_KEY50_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY50_BITS) >> BP_OCOTP_HDCP_KEY50_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY50_BITS.
#define BF_OCOTP_HDCP_KEY50_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY50_BITS) & BM_OCOTP_HDCP_KEY50_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY50_BITS(v)   (HW_OCOTP_HDCP_KEY50_WR((HW_OCOTP_HDCP_KEY50_RD() & ~BM_OCOTP_HDCP_KEY50_BITS) | BF_OCOTP_HDCP_KEY50_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY51 - Value of OTP Bank12 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY51 - Value of OTP Bank12 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 3 (ADDR =
 * 0x63).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key51
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key51_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 3 (ADDR = 0x63).
    } B;
} hw_ocotp_hdcp_key51_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY51 register
 */
#define HW_OCOTP_HDCP_KEY51_ADDR      (REGS_OCOTP_BASE + 0xb30)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY51           (*(volatile hw_ocotp_hdcp_key51_t *) HW_OCOTP_HDCP_KEY51_ADDR)
#define HW_OCOTP_HDCP_KEY51_RD()      (HW_OCOTP_HDCP_KEY51.U)
#define HW_OCOTP_HDCP_KEY51_WR(v)     (HW_OCOTP_HDCP_KEY51.U = (v))
#define HW_OCOTP_HDCP_KEY51_SET(v)    (HW_OCOTP_HDCP_KEY51_WR(HW_OCOTP_HDCP_KEY51_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY51_CLR(v)    (HW_OCOTP_HDCP_KEY51_WR(HW_OCOTP_HDCP_KEY51_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY51_TOG(v)    (HW_OCOTP_HDCP_KEY51_WR(HW_OCOTP_HDCP_KEY51_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY51 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY51, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 3 (ADDR = 0x63).
 */

#define BP_OCOTP_HDCP_KEY51_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY51_BITS.
#define BM_OCOTP_HDCP_KEY51_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY51_BITS.

//! @brief Get value of OCOTP_HDCP_KEY51_BITS from a register value.
#define BG_OCOTP_HDCP_KEY51_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY51_BITS) >> BP_OCOTP_HDCP_KEY51_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY51_BITS.
#define BF_OCOTP_HDCP_KEY51_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY51_BITS) & BM_OCOTP_HDCP_KEY51_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY51_BITS(v)   (HW_OCOTP_HDCP_KEY51_WR((HW_OCOTP_HDCP_KEY51_RD() & ~BM_OCOTP_HDCP_KEY51_BITS) | BF_OCOTP_HDCP_KEY51_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY52 - Value of OTP Bank12 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY52 - Value of OTP Bank12 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 4 (ADDR =
 * 0x64).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key52
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key52_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 4 (ADDR = 0x64).
    } B;
} hw_ocotp_hdcp_key52_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY52 register
 */
#define HW_OCOTP_HDCP_KEY52_ADDR      (REGS_OCOTP_BASE + 0xb40)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY52           (*(volatile hw_ocotp_hdcp_key52_t *) HW_OCOTP_HDCP_KEY52_ADDR)
#define HW_OCOTP_HDCP_KEY52_RD()      (HW_OCOTP_HDCP_KEY52.U)
#define HW_OCOTP_HDCP_KEY52_WR(v)     (HW_OCOTP_HDCP_KEY52.U = (v))
#define HW_OCOTP_HDCP_KEY52_SET(v)    (HW_OCOTP_HDCP_KEY52_WR(HW_OCOTP_HDCP_KEY52_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY52_CLR(v)    (HW_OCOTP_HDCP_KEY52_WR(HW_OCOTP_HDCP_KEY52_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY52_TOG(v)    (HW_OCOTP_HDCP_KEY52_WR(HW_OCOTP_HDCP_KEY52_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY52 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY52, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 4 (ADDR = 0x64).
 */

#define BP_OCOTP_HDCP_KEY52_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY52_BITS.
#define BM_OCOTP_HDCP_KEY52_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY52_BITS.

//! @brief Get value of OCOTP_HDCP_KEY52_BITS from a register value.
#define BG_OCOTP_HDCP_KEY52_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY52_BITS) >> BP_OCOTP_HDCP_KEY52_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY52_BITS.
#define BF_OCOTP_HDCP_KEY52_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY52_BITS) & BM_OCOTP_HDCP_KEY52_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY52_BITS(v)   (HW_OCOTP_HDCP_KEY52_WR((HW_OCOTP_HDCP_KEY52_RD() & ~BM_OCOTP_HDCP_KEY52_BITS) | BF_OCOTP_HDCP_KEY52_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY53 - Value of OTP Bank12 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY53 - Value of OTP Bank12 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 5 (ADDR =
 * 0x65).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key53
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key53_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 5 (ADDR = 0x65).
    } B;
} hw_ocotp_hdcp_key53_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY53 register
 */
#define HW_OCOTP_HDCP_KEY53_ADDR      (REGS_OCOTP_BASE + 0xb50)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY53           (*(volatile hw_ocotp_hdcp_key53_t *) HW_OCOTP_HDCP_KEY53_ADDR)
#define HW_OCOTP_HDCP_KEY53_RD()      (HW_OCOTP_HDCP_KEY53.U)
#define HW_OCOTP_HDCP_KEY53_WR(v)     (HW_OCOTP_HDCP_KEY53.U = (v))
#define HW_OCOTP_HDCP_KEY53_SET(v)    (HW_OCOTP_HDCP_KEY53_WR(HW_OCOTP_HDCP_KEY53_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY53_CLR(v)    (HW_OCOTP_HDCP_KEY53_WR(HW_OCOTP_HDCP_KEY53_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY53_TOG(v)    (HW_OCOTP_HDCP_KEY53_WR(HW_OCOTP_HDCP_KEY53_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY53 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY53, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 5 (ADDR = 0x65).
 */

#define BP_OCOTP_HDCP_KEY53_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY53_BITS.
#define BM_OCOTP_HDCP_KEY53_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY53_BITS.

//! @brief Get value of OCOTP_HDCP_KEY53_BITS from a register value.
#define BG_OCOTP_HDCP_KEY53_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY53_BITS) >> BP_OCOTP_HDCP_KEY53_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY53_BITS.
#define BF_OCOTP_HDCP_KEY53_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY53_BITS) & BM_OCOTP_HDCP_KEY53_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY53_BITS(v)   (HW_OCOTP_HDCP_KEY53_WR((HW_OCOTP_HDCP_KEY53_RD() & ~BM_OCOTP_HDCP_KEY53_BITS) | BF_OCOTP_HDCP_KEY53_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY54 - Value of OTP Bank12 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY54 - Value of OTP Bank12 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 6 (ADDR =
 * 0x66).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key54
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key54_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 6 (ADDR = 0x66).
    } B;
} hw_ocotp_hdcp_key54_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY54 register
 */
#define HW_OCOTP_HDCP_KEY54_ADDR      (REGS_OCOTP_BASE + 0xb60)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY54           (*(volatile hw_ocotp_hdcp_key54_t *) HW_OCOTP_HDCP_KEY54_ADDR)
#define HW_OCOTP_HDCP_KEY54_RD()      (HW_OCOTP_HDCP_KEY54.U)
#define HW_OCOTP_HDCP_KEY54_WR(v)     (HW_OCOTP_HDCP_KEY54.U = (v))
#define HW_OCOTP_HDCP_KEY54_SET(v)    (HW_OCOTP_HDCP_KEY54_WR(HW_OCOTP_HDCP_KEY54_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY54_CLR(v)    (HW_OCOTP_HDCP_KEY54_WR(HW_OCOTP_HDCP_KEY54_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY54_TOG(v)    (HW_OCOTP_HDCP_KEY54_WR(HW_OCOTP_HDCP_KEY54_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY54 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY54, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 6 (ADDR = 0x66).
 */

#define BP_OCOTP_HDCP_KEY54_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY54_BITS.
#define BM_OCOTP_HDCP_KEY54_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY54_BITS.

//! @brief Get value of OCOTP_HDCP_KEY54_BITS from a register value.
#define BG_OCOTP_HDCP_KEY54_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY54_BITS) >> BP_OCOTP_HDCP_KEY54_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY54_BITS.
#define BF_OCOTP_HDCP_KEY54_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY54_BITS) & BM_OCOTP_HDCP_KEY54_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY54_BITS(v)   (HW_OCOTP_HDCP_KEY54_WR((HW_OCOTP_HDCP_KEY54_RD() & ~BM_OCOTP_HDCP_KEY54_BITS) | BF_OCOTP_HDCP_KEY54_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY55 - Value of OTP Bank12 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY55 - Value of OTP Bank12 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 12, word 7 (ADDR =
 * 0x67).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key55
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key55_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 12, word 7 (ADDR = 0x67).
    } B;
} hw_ocotp_hdcp_key55_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY55 register
 */
#define HW_OCOTP_HDCP_KEY55_ADDR      (REGS_OCOTP_BASE + 0xb70)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY55           (*(volatile hw_ocotp_hdcp_key55_t *) HW_OCOTP_HDCP_KEY55_ADDR)
#define HW_OCOTP_HDCP_KEY55_RD()      (HW_OCOTP_HDCP_KEY55.U)
#define HW_OCOTP_HDCP_KEY55_WR(v)     (HW_OCOTP_HDCP_KEY55.U = (v))
#define HW_OCOTP_HDCP_KEY55_SET(v)    (HW_OCOTP_HDCP_KEY55_WR(HW_OCOTP_HDCP_KEY55_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY55_CLR(v)    (HW_OCOTP_HDCP_KEY55_WR(HW_OCOTP_HDCP_KEY55_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY55_TOG(v)    (HW_OCOTP_HDCP_KEY55_WR(HW_OCOTP_HDCP_KEY55_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY55 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY55, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 12, word 7 (ADDR = 0x67).
 */

#define BP_OCOTP_HDCP_KEY55_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY55_BITS.
#define BM_OCOTP_HDCP_KEY55_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY55_BITS.

//! @brief Get value of OCOTP_HDCP_KEY55_BITS from a register value.
#define BG_OCOTP_HDCP_KEY55_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY55_BITS) >> BP_OCOTP_HDCP_KEY55_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY55_BITS.
#define BF_OCOTP_HDCP_KEY55_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY55_BITS) & BM_OCOTP_HDCP_KEY55_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY55_BITS(v)   (HW_OCOTP_HDCP_KEY55_WR((HW_OCOTP_HDCP_KEY55_RD() & ~BM_OCOTP_HDCP_KEY55_BITS) | BF_OCOTP_HDCP_KEY55_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY56 - Value of OTP Bank13 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY56 - Value of OTP Bank13 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 0 (ADDR =
 * 0x68).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key56
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key56_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 0 (ADDR = 0x68).
    } B;
} hw_ocotp_hdcp_key56_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY56 register
 */
#define HW_OCOTP_HDCP_KEY56_ADDR      (REGS_OCOTP_BASE + 0xb80)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY56           (*(volatile hw_ocotp_hdcp_key56_t *) HW_OCOTP_HDCP_KEY56_ADDR)
#define HW_OCOTP_HDCP_KEY56_RD()      (HW_OCOTP_HDCP_KEY56.U)
#define HW_OCOTP_HDCP_KEY56_WR(v)     (HW_OCOTP_HDCP_KEY56.U = (v))
#define HW_OCOTP_HDCP_KEY56_SET(v)    (HW_OCOTP_HDCP_KEY56_WR(HW_OCOTP_HDCP_KEY56_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY56_CLR(v)    (HW_OCOTP_HDCP_KEY56_WR(HW_OCOTP_HDCP_KEY56_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY56_TOG(v)    (HW_OCOTP_HDCP_KEY56_WR(HW_OCOTP_HDCP_KEY56_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY56 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY56, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 0 (ADDR = 0x68).
 */

#define BP_OCOTP_HDCP_KEY56_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY56_BITS.
#define BM_OCOTP_HDCP_KEY56_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY56_BITS.

//! @brief Get value of OCOTP_HDCP_KEY56_BITS from a register value.
#define BG_OCOTP_HDCP_KEY56_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY56_BITS) >> BP_OCOTP_HDCP_KEY56_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY56_BITS.
#define BF_OCOTP_HDCP_KEY56_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY56_BITS) & BM_OCOTP_HDCP_KEY56_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY56_BITS(v)   (HW_OCOTP_HDCP_KEY56_WR((HW_OCOTP_HDCP_KEY56_RD() & ~BM_OCOTP_HDCP_KEY56_BITS) | BF_OCOTP_HDCP_KEY56_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY57 - Value of OTP Bank13 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY57 - Value of OTP Bank13 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 1 (ADDR =
 * 0x69).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key57
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key57_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 1 (ADDR = 0x69).
    } B;
} hw_ocotp_hdcp_key57_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY57 register
 */
#define HW_OCOTP_HDCP_KEY57_ADDR      (REGS_OCOTP_BASE + 0xb90)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY57           (*(volatile hw_ocotp_hdcp_key57_t *) HW_OCOTP_HDCP_KEY57_ADDR)
#define HW_OCOTP_HDCP_KEY57_RD()      (HW_OCOTP_HDCP_KEY57.U)
#define HW_OCOTP_HDCP_KEY57_WR(v)     (HW_OCOTP_HDCP_KEY57.U = (v))
#define HW_OCOTP_HDCP_KEY57_SET(v)    (HW_OCOTP_HDCP_KEY57_WR(HW_OCOTP_HDCP_KEY57_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY57_CLR(v)    (HW_OCOTP_HDCP_KEY57_WR(HW_OCOTP_HDCP_KEY57_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY57_TOG(v)    (HW_OCOTP_HDCP_KEY57_WR(HW_OCOTP_HDCP_KEY57_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY57 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY57, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 1 (ADDR = 0x69).
 */

#define BP_OCOTP_HDCP_KEY57_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY57_BITS.
#define BM_OCOTP_HDCP_KEY57_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY57_BITS.

//! @brief Get value of OCOTP_HDCP_KEY57_BITS from a register value.
#define BG_OCOTP_HDCP_KEY57_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY57_BITS) >> BP_OCOTP_HDCP_KEY57_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY57_BITS.
#define BF_OCOTP_HDCP_KEY57_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY57_BITS) & BM_OCOTP_HDCP_KEY57_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY57_BITS(v)   (HW_OCOTP_HDCP_KEY57_WR((HW_OCOTP_HDCP_KEY57_RD() & ~BM_OCOTP_HDCP_KEY57_BITS) | BF_OCOTP_HDCP_KEY57_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY58 - Value of OTP Bank13 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY58 - Value of OTP Bank13 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 2 (ADDR =
 * 0x6a).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key58
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key58_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 2 (ADDR = 0x6a).
    } B;
} hw_ocotp_hdcp_key58_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY58 register
 */
#define HW_OCOTP_HDCP_KEY58_ADDR      (REGS_OCOTP_BASE + 0xba0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY58           (*(volatile hw_ocotp_hdcp_key58_t *) HW_OCOTP_HDCP_KEY58_ADDR)
#define HW_OCOTP_HDCP_KEY58_RD()      (HW_OCOTP_HDCP_KEY58.U)
#define HW_OCOTP_HDCP_KEY58_WR(v)     (HW_OCOTP_HDCP_KEY58.U = (v))
#define HW_OCOTP_HDCP_KEY58_SET(v)    (HW_OCOTP_HDCP_KEY58_WR(HW_OCOTP_HDCP_KEY58_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY58_CLR(v)    (HW_OCOTP_HDCP_KEY58_WR(HW_OCOTP_HDCP_KEY58_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY58_TOG(v)    (HW_OCOTP_HDCP_KEY58_WR(HW_OCOTP_HDCP_KEY58_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY58 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY58, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 2 (ADDR = 0x6a).
 */

#define BP_OCOTP_HDCP_KEY58_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY58_BITS.
#define BM_OCOTP_HDCP_KEY58_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY58_BITS.

//! @brief Get value of OCOTP_HDCP_KEY58_BITS from a register value.
#define BG_OCOTP_HDCP_KEY58_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY58_BITS) >> BP_OCOTP_HDCP_KEY58_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY58_BITS.
#define BF_OCOTP_HDCP_KEY58_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY58_BITS) & BM_OCOTP_HDCP_KEY58_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY58_BITS(v)   (HW_OCOTP_HDCP_KEY58_WR((HW_OCOTP_HDCP_KEY58_RD() & ~BM_OCOTP_HDCP_KEY58_BITS) | BF_OCOTP_HDCP_KEY58_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY59 - Value of OTP Bank13 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY59 - Value of OTP Bank13 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 3 (ADDR =
 * 0x6b).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key59
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key59_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 3 (ADDR = 0x6b).
    } B;
} hw_ocotp_hdcp_key59_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY59 register
 */
#define HW_OCOTP_HDCP_KEY59_ADDR      (REGS_OCOTP_BASE + 0xbb0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY59           (*(volatile hw_ocotp_hdcp_key59_t *) HW_OCOTP_HDCP_KEY59_ADDR)
#define HW_OCOTP_HDCP_KEY59_RD()      (HW_OCOTP_HDCP_KEY59.U)
#define HW_OCOTP_HDCP_KEY59_WR(v)     (HW_OCOTP_HDCP_KEY59.U = (v))
#define HW_OCOTP_HDCP_KEY59_SET(v)    (HW_OCOTP_HDCP_KEY59_WR(HW_OCOTP_HDCP_KEY59_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY59_CLR(v)    (HW_OCOTP_HDCP_KEY59_WR(HW_OCOTP_HDCP_KEY59_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY59_TOG(v)    (HW_OCOTP_HDCP_KEY59_WR(HW_OCOTP_HDCP_KEY59_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY59 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY59, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 3 (ADDR = 0x6b).
 */

#define BP_OCOTP_HDCP_KEY59_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY59_BITS.
#define BM_OCOTP_HDCP_KEY59_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY59_BITS.

//! @brief Get value of OCOTP_HDCP_KEY59_BITS from a register value.
#define BG_OCOTP_HDCP_KEY59_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY59_BITS) >> BP_OCOTP_HDCP_KEY59_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY59_BITS.
#define BF_OCOTP_HDCP_KEY59_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY59_BITS) & BM_OCOTP_HDCP_KEY59_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY59_BITS(v)   (HW_OCOTP_HDCP_KEY59_WR((HW_OCOTP_HDCP_KEY59_RD() & ~BM_OCOTP_HDCP_KEY59_BITS) | BF_OCOTP_HDCP_KEY59_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY60 - Value of OTP Bank13 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY60 - Value of OTP Bank13 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 4 (ADDR =
 * 0x6c).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key60
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key60_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 4 (ADDR = 0x6c).
    } B;
} hw_ocotp_hdcp_key60_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY60 register
 */
#define HW_OCOTP_HDCP_KEY60_ADDR      (REGS_OCOTP_BASE + 0xbc0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY60           (*(volatile hw_ocotp_hdcp_key60_t *) HW_OCOTP_HDCP_KEY60_ADDR)
#define HW_OCOTP_HDCP_KEY60_RD()      (HW_OCOTP_HDCP_KEY60.U)
#define HW_OCOTP_HDCP_KEY60_WR(v)     (HW_OCOTP_HDCP_KEY60.U = (v))
#define HW_OCOTP_HDCP_KEY60_SET(v)    (HW_OCOTP_HDCP_KEY60_WR(HW_OCOTP_HDCP_KEY60_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY60_CLR(v)    (HW_OCOTP_HDCP_KEY60_WR(HW_OCOTP_HDCP_KEY60_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY60_TOG(v)    (HW_OCOTP_HDCP_KEY60_WR(HW_OCOTP_HDCP_KEY60_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY60 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY60, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 4 (ADDR = 0x6c).
 */

#define BP_OCOTP_HDCP_KEY60_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY60_BITS.
#define BM_OCOTP_HDCP_KEY60_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY60_BITS.

//! @brief Get value of OCOTP_HDCP_KEY60_BITS from a register value.
#define BG_OCOTP_HDCP_KEY60_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY60_BITS) >> BP_OCOTP_HDCP_KEY60_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY60_BITS.
#define BF_OCOTP_HDCP_KEY60_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY60_BITS) & BM_OCOTP_HDCP_KEY60_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY60_BITS(v)   (HW_OCOTP_HDCP_KEY60_WR((HW_OCOTP_HDCP_KEY60_RD() & ~BM_OCOTP_HDCP_KEY60_BITS) | BF_OCOTP_HDCP_KEY60_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY61 - Value of OTP Bank13 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY61 - Value of OTP Bank13 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 5 (ADDR =
 * 0x6d).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key61
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key61_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 5 (ADDR = 0x6d).
    } B;
} hw_ocotp_hdcp_key61_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY61 register
 */
#define HW_OCOTP_HDCP_KEY61_ADDR      (REGS_OCOTP_BASE + 0xbd0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY61           (*(volatile hw_ocotp_hdcp_key61_t *) HW_OCOTP_HDCP_KEY61_ADDR)
#define HW_OCOTP_HDCP_KEY61_RD()      (HW_OCOTP_HDCP_KEY61.U)
#define HW_OCOTP_HDCP_KEY61_WR(v)     (HW_OCOTP_HDCP_KEY61.U = (v))
#define HW_OCOTP_HDCP_KEY61_SET(v)    (HW_OCOTP_HDCP_KEY61_WR(HW_OCOTP_HDCP_KEY61_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY61_CLR(v)    (HW_OCOTP_HDCP_KEY61_WR(HW_OCOTP_HDCP_KEY61_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY61_TOG(v)    (HW_OCOTP_HDCP_KEY61_WR(HW_OCOTP_HDCP_KEY61_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY61 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY61, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 5 (ADDR = 0x6d).
 */

#define BP_OCOTP_HDCP_KEY61_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY61_BITS.
#define BM_OCOTP_HDCP_KEY61_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY61_BITS.

//! @brief Get value of OCOTP_HDCP_KEY61_BITS from a register value.
#define BG_OCOTP_HDCP_KEY61_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY61_BITS) >> BP_OCOTP_HDCP_KEY61_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY61_BITS.
#define BF_OCOTP_HDCP_KEY61_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY61_BITS) & BM_OCOTP_HDCP_KEY61_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY61_BITS(v)   (HW_OCOTP_HDCP_KEY61_WR((HW_OCOTP_HDCP_KEY61_RD() & ~BM_OCOTP_HDCP_KEY61_BITS) | BF_OCOTP_HDCP_KEY61_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY62 - Value of OTP Bank13 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY62 - Value of OTP Bank13 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to Bank 13, word 6 (ADDR = 0x6e).
 * EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key62
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key62_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of Bank 13, word 6 (ADDR = 0x6e).
    } B;
} hw_ocotp_hdcp_key62_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY62 register
 */
#define HW_OCOTP_HDCP_KEY62_ADDR      (REGS_OCOTP_BASE + 0xbe0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY62           (*(volatile hw_ocotp_hdcp_key62_t *) HW_OCOTP_HDCP_KEY62_ADDR)
#define HW_OCOTP_HDCP_KEY62_RD()      (HW_OCOTP_HDCP_KEY62.U)
#define HW_OCOTP_HDCP_KEY62_WR(v)     (HW_OCOTP_HDCP_KEY62.U = (v))
#define HW_OCOTP_HDCP_KEY62_SET(v)    (HW_OCOTP_HDCP_KEY62_WR(HW_OCOTP_HDCP_KEY62_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY62_CLR(v)    (HW_OCOTP_HDCP_KEY62_WR(HW_OCOTP_HDCP_KEY62_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY62_TOG(v)    (HW_OCOTP_HDCP_KEY62_WR(HW_OCOTP_HDCP_KEY62_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY62 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY62, field BITS[31:0] (RW)
 *
 * Reflects value of Bank 13, word 6 (ADDR = 0x6e).
 */

#define BP_OCOTP_HDCP_KEY62_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY62_BITS.
#define BM_OCOTP_HDCP_KEY62_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY62_BITS.

//! @brief Get value of OCOTP_HDCP_KEY62_BITS from a register value.
#define BG_OCOTP_HDCP_KEY62_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY62_BITS) >> BP_OCOTP_HDCP_KEY62_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY62_BITS.
#define BF_OCOTP_HDCP_KEY62_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY62_BITS) & BM_OCOTP_HDCP_KEY62_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY62_BITS(v)   (HW_OCOTP_HDCP_KEY62_WR((HW_OCOTP_HDCP_KEY62_RD() & ~BM_OCOTP_HDCP_KEY62_BITS) | BF_OCOTP_HDCP_KEY62_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY63 - Value of OTP Bank13 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY63 - Value of OTP Bank13 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 13, word 7 (ADDR =
 * 0x6f).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key63
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key63_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 13, word 7 (ADDR = 0x6f).
    } B;
} hw_ocotp_hdcp_key63_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY63 register
 */
#define HW_OCOTP_HDCP_KEY63_ADDR      (REGS_OCOTP_BASE + 0xbf0)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY63           (*(volatile hw_ocotp_hdcp_key63_t *) HW_OCOTP_HDCP_KEY63_ADDR)
#define HW_OCOTP_HDCP_KEY63_RD()      (HW_OCOTP_HDCP_KEY63.U)
#define HW_OCOTP_HDCP_KEY63_WR(v)     (HW_OCOTP_HDCP_KEY63.U = (v))
#define HW_OCOTP_HDCP_KEY63_SET(v)    (HW_OCOTP_HDCP_KEY63_WR(HW_OCOTP_HDCP_KEY63_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY63_CLR(v)    (HW_OCOTP_HDCP_KEY63_WR(HW_OCOTP_HDCP_KEY63_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY63_TOG(v)    (HW_OCOTP_HDCP_KEY63_WR(HW_OCOTP_HDCP_KEY63_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY63 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY63, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 13, word 7 (ADDR = 0x6f).
 */

#define BP_OCOTP_HDCP_KEY63_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY63_BITS.
#define BM_OCOTP_HDCP_KEY63_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY63_BITS.

//! @brief Get value of OCOTP_HDCP_KEY63_BITS from a register value.
#define BG_OCOTP_HDCP_KEY63_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY63_BITS) >> BP_OCOTP_HDCP_KEY63_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY63_BITS.
#define BF_OCOTP_HDCP_KEY63_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY63_BITS) & BM_OCOTP_HDCP_KEY63_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY63_BITS(v)   (HW_OCOTP_HDCP_KEY63_WR((HW_OCOTP_HDCP_KEY63_RD() & ~BM_OCOTP_HDCP_KEY63_BITS) | BF_OCOTP_HDCP_KEY63_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY64 - Value of OTP Bank14 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY64 - Value of OTP Bank14 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 0 (ADDR =
 * 0x70).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key64
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key64_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 0 (ADDR = 0x70).
    } B;
} hw_ocotp_hdcp_key64_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY64 register
 */
#define HW_OCOTP_HDCP_KEY64_ADDR      (REGS_OCOTP_BASE + 0xc00)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY64           (*(volatile hw_ocotp_hdcp_key64_t *) HW_OCOTP_HDCP_KEY64_ADDR)
#define HW_OCOTP_HDCP_KEY64_RD()      (HW_OCOTP_HDCP_KEY64.U)
#define HW_OCOTP_HDCP_KEY64_WR(v)     (HW_OCOTP_HDCP_KEY64.U = (v))
#define HW_OCOTP_HDCP_KEY64_SET(v)    (HW_OCOTP_HDCP_KEY64_WR(HW_OCOTP_HDCP_KEY64_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY64_CLR(v)    (HW_OCOTP_HDCP_KEY64_WR(HW_OCOTP_HDCP_KEY64_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY64_TOG(v)    (HW_OCOTP_HDCP_KEY64_WR(HW_OCOTP_HDCP_KEY64_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY64 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY64, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 0 (ADDR = 0x70).
 */

#define BP_OCOTP_HDCP_KEY64_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY64_BITS.
#define BM_OCOTP_HDCP_KEY64_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY64_BITS.

//! @brief Get value of OCOTP_HDCP_KEY64_BITS from a register value.
#define BG_OCOTP_HDCP_KEY64_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY64_BITS) >> BP_OCOTP_HDCP_KEY64_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY64_BITS.
#define BF_OCOTP_HDCP_KEY64_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY64_BITS) & BM_OCOTP_HDCP_KEY64_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY64_BITS(v)   (HW_OCOTP_HDCP_KEY64_WR((HW_OCOTP_HDCP_KEY64_RD() & ~BM_OCOTP_HDCP_KEY64_BITS) | BF_OCOTP_HDCP_KEY64_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY65 - Value of OTP Bank14 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY65 - Value of OTP Bank14 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 1 (ADDR =
 * 0x71).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key65
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key65_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 1 (ADDR = 0x71).
    } B;
} hw_ocotp_hdcp_key65_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY65 register
 */
#define HW_OCOTP_HDCP_KEY65_ADDR      (REGS_OCOTP_BASE + 0xc10)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY65           (*(volatile hw_ocotp_hdcp_key65_t *) HW_OCOTP_HDCP_KEY65_ADDR)
#define HW_OCOTP_HDCP_KEY65_RD()      (HW_OCOTP_HDCP_KEY65.U)
#define HW_OCOTP_HDCP_KEY65_WR(v)     (HW_OCOTP_HDCP_KEY65.U = (v))
#define HW_OCOTP_HDCP_KEY65_SET(v)    (HW_OCOTP_HDCP_KEY65_WR(HW_OCOTP_HDCP_KEY65_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY65_CLR(v)    (HW_OCOTP_HDCP_KEY65_WR(HW_OCOTP_HDCP_KEY65_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY65_TOG(v)    (HW_OCOTP_HDCP_KEY65_WR(HW_OCOTP_HDCP_KEY65_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY65 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY65, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 1 (ADDR = 0x71).
 */

#define BP_OCOTP_HDCP_KEY65_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY65_BITS.
#define BM_OCOTP_HDCP_KEY65_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY65_BITS.

//! @brief Get value of OCOTP_HDCP_KEY65_BITS from a register value.
#define BG_OCOTP_HDCP_KEY65_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY65_BITS) >> BP_OCOTP_HDCP_KEY65_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY65_BITS.
#define BF_OCOTP_HDCP_KEY65_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY65_BITS) & BM_OCOTP_HDCP_KEY65_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY65_BITS(v)   (HW_OCOTP_HDCP_KEY65_WR((HW_OCOTP_HDCP_KEY65_RD() & ~BM_OCOTP_HDCP_KEY65_BITS) | BF_OCOTP_HDCP_KEY65_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY66 - Value of OTP Bank14 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY66 - Value of OTP Bank14 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 2 (ADDR =
 * 0x72).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key66
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key66_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 2 (ADDR = 0x72).
    } B;
} hw_ocotp_hdcp_key66_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY66 register
 */
#define HW_OCOTP_HDCP_KEY66_ADDR      (REGS_OCOTP_BASE + 0xc20)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY66           (*(volatile hw_ocotp_hdcp_key66_t *) HW_OCOTP_HDCP_KEY66_ADDR)
#define HW_OCOTP_HDCP_KEY66_RD()      (HW_OCOTP_HDCP_KEY66.U)
#define HW_OCOTP_HDCP_KEY66_WR(v)     (HW_OCOTP_HDCP_KEY66.U = (v))
#define HW_OCOTP_HDCP_KEY66_SET(v)    (HW_OCOTP_HDCP_KEY66_WR(HW_OCOTP_HDCP_KEY66_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY66_CLR(v)    (HW_OCOTP_HDCP_KEY66_WR(HW_OCOTP_HDCP_KEY66_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY66_TOG(v)    (HW_OCOTP_HDCP_KEY66_WR(HW_OCOTP_HDCP_KEY66_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY66 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY66, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 2 (ADDR = 0x72).
 */

#define BP_OCOTP_HDCP_KEY66_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY66_BITS.
#define BM_OCOTP_HDCP_KEY66_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY66_BITS.

//! @brief Get value of OCOTP_HDCP_KEY66_BITS from a register value.
#define BG_OCOTP_HDCP_KEY66_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY66_BITS) >> BP_OCOTP_HDCP_KEY66_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY66_BITS.
#define BF_OCOTP_HDCP_KEY66_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY66_BITS) & BM_OCOTP_HDCP_KEY66_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY66_BITS(v)   (HW_OCOTP_HDCP_KEY66_WR((HW_OCOTP_HDCP_KEY66_RD() & ~BM_OCOTP_HDCP_KEY66_BITS) | BF_OCOTP_HDCP_KEY66_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY67 - Value of OTP Bank14 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY67 - Value of OTP Bank14 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 3 (ADDR =
 * 0x73).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key67
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key67_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 3 (ADDR = 0x73).
    } B;
} hw_ocotp_hdcp_key67_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY67 register
 */
#define HW_OCOTP_HDCP_KEY67_ADDR      (REGS_OCOTP_BASE + 0xc30)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY67           (*(volatile hw_ocotp_hdcp_key67_t *) HW_OCOTP_HDCP_KEY67_ADDR)
#define HW_OCOTP_HDCP_KEY67_RD()      (HW_OCOTP_HDCP_KEY67.U)
#define HW_OCOTP_HDCP_KEY67_WR(v)     (HW_OCOTP_HDCP_KEY67.U = (v))
#define HW_OCOTP_HDCP_KEY67_SET(v)    (HW_OCOTP_HDCP_KEY67_WR(HW_OCOTP_HDCP_KEY67_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY67_CLR(v)    (HW_OCOTP_HDCP_KEY67_WR(HW_OCOTP_HDCP_KEY67_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY67_TOG(v)    (HW_OCOTP_HDCP_KEY67_WR(HW_OCOTP_HDCP_KEY67_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY67 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY67, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 3 (ADDR = 0x73).
 */

#define BP_OCOTP_HDCP_KEY67_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY67_BITS.
#define BM_OCOTP_HDCP_KEY67_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY67_BITS.

//! @brief Get value of OCOTP_HDCP_KEY67_BITS from a register value.
#define BG_OCOTP_HDCP_KEY67_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY67_BITS) >> BP_OCOTP_HDCP_KEY67_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY67_BITS.
#define BF_OCOTP_HDCP_KEY67_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY67_BITS) & BM_OCOTP_HDCP_KEY67_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY67_BITS(v)   (HW_OCOTP_HDCP_KEY67_WR((HW_OCOTP_HDCP_KEY67_RD() & ~BM_OCOTP_HDCP_KEY67_BITS) | BF_OCOTP_HDCP_KEY67_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY68 - Value of OTP Bank14 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY68 - Value of OTP Bank14 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 4 (ADDR =
 * 0x74).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key68
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key68_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 4 (ADDR = 0x74).
    } B;
} hw_ocotp_hdcp_key68_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY68 register
 */
#define HW_OCOTP_HDCP_KEY68_ADDR      (REGS_OCOTP_BASE + 0xc40)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY68           (*(volatile hw_ocotp_hdcp_key68_t *) HW_OCOTP_HDCP_KEY68_ADDR)
#define HW_OCOTP_HDCP_KEY68_RD()      (HW_OCOTP_HDCP_KEY68.U)
#define HW_OCOTP_HDCP_KEY68_WR(v)     (HW_OCOTP_HDCP_KEY68.U = (v))
#define HW_OCOTP_HDCP_KEY68_SET(v)    (HW_OCOTP_HDCP_KEY68_WR(HW_OCOTP_HDCP_KEY68_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY68_CLR(v)    (HW_OCOTP_HDCP_KEY68_WR(HW_OCOTP_HDCP_KEY68_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY68_TOG(v)    (HW_OCOTP_HDCP_KEY68_WR(HW_OCOTP_HDCP_KEY68_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY68 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY68, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 4 (ADDR = 0x74).
 */

#define BP_OCOTP_HDCP_KEY68_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY68_BITS.
#define BM_OCOTP_HDCP_KEY68_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY68_BITS.

//! @brief Get value of OCOTP_HDCP_KEY68_BITS from a register value.
#define BG_OCOTP_HDCP_KEY68_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY68_BITS) >> BP_OCOTP_HDCP_KEY68_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY68_BITS.
#define BF_OCOTP_HDCP_KEY68_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY68_BITS) & BM_OCOTP_HDCP_KEY68_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY68_BITS(v)   (HW_OCOTP_HDCP_KEY68_WR((HW_OCOTP_HDCP_KEY68_RD() & ~BM_OCOTP_HDCP_KEY68_BITS) | BF_OCOTP_HDCP_KEY68_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY69 - Value of OTP Bank14 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY69 - Value of OTP Bank14 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 5 (ADDR =
 * 0x75).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key69
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key69_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 5 (ADDR = 0x75).
    } B;
} hw_ocotp_hdcp_key69_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY69 register
 */
#define HW_OCOTP_HDCP_KEY69_ADDR      (REGS_OCOTP_BASE + 0xc50)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY69           (*(volatile hw_ocotp_hdcp_key69_t *) HW_OCOTP_HDCP_KEY69_ADDR)
#define HW_OCOTP_HDCP_KEY69_RD()      (HW_OCOTP_HDCP_KEY69.U)
#define HW_OCOTP_HDCP_KEY69_WR(v)     (HW_OCOTP_HDCP_KEY69.U = (v))
#define HW_OCOTP_HDCP_KEY69_SET(v)    (HW_OCOTP_HDCP_KEY69_WR(HW_OCOTP_HDCP_KEY69_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY69_CLR(v)    (HW_OCOTP_HDCP_KEY69_WR(HW_OCOTP_HDCP_KEY69_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY69_TOG(v)    (HW_OCOTP_HDCP_KEY69_WR(HW_OCOTP_HDCP_KEY69_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY69 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY69, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 5 (ADDR = 0x75).
 */

#define BP_OCOTP_HDCP_KEY69_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY69_BITS.
#define BM_OCOTP_HDCP_KEY69_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY69_BITS.

//! @brief Get value of OCOTP_HDCP_KEY69_BITS from a register value.
#define BG_OCOTP_HDCP_KEY69_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY69_BITS) >> BP_OCOTP_HDCP_KEY69_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY69_BITS.
#define BF_OCOTP_HDCP_KEY69_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY69_BITS) & BM_OCOTP_HDCP_KEY69_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY69_BITS(v)   (HW_OCOTP_HDCP_KEY69_WR((HW_OCOTP_HDCP_KEY69_RD() & ~BM_OCOTP_HDCP_KEY69_BITS) | BF_OCOTP_HDCP_KEY69_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY70 - Value of OTP Bank14 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY70 - Value of OTP Bank14 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 6 (ADDR =
 * 0x76).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key70
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key70_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 6 (ADDR = 0x76).
    } B;
} hw_ocotp_hdcp_key70_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY70 register
 */
#define HW_OCOTP_HDCP_KEY70_ADDR      (REGS_OCOTP_BASE + 0xc60)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY70           (*(volatile hw_ocotp_hdcp_key70_t *) HW_OCOTP_HDCP_KEY70_ADDR)
#define HW_OCOTP_HDCP_KEY70_RD()      (HW_OCOTP_HDCP_KEY70.U)
#define HW_OCOTP_HDCP_KEY70_WR(v)     (HW_OCOTP_HDCP_KEY70.U = (v))
#define HW_OCOTP_HDCP_KEY70_SET(v)    (HW_OCOTP_HDCP_KEY70_WR(HW_OCOTP_HDCP_KEY70_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY70_CLR(v)    (HW_OCOTP_HDCP_KEY70_WR(HW_OCOTP_HDCP_KEY70_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY70_TOG(v)    (HW_OCOTP_HDCP_KEY70_WR(HW_OCOTP_HDCP_KEY70_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY70 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY70, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 6 (ADDR = 0x76).
 */

#define BP_OCOTP_HDCP_KEY70_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY70_BITS.
#define BM_OCOTP_HDCP_KEY70_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY70_BITS.

//! @brief Get value of OCOTP_HDCP_KEY70_BITS from a register value.
#define BG_OCOTP_HDCP_KEY70_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY70_BITS) >> BP_OCOTP_HDCP_KEY70_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY70_BITS.
#define BF_OCOTP_HDCP_KEY70_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY70_BITS) & BM_OCOTP_HDCP_KEY70_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY70_BITS(v)   (HW_OCOTP_HDCP_KEY70_WR((HW_OCOTP_HDCP_KEY70_RD() & ~BM_OCOTP_HDCP_KEY70_BITS) | BF_OCOTP_HDCP_KEY70_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_HDCP_KEY71 - Value of OTP Bank14 Word7 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_HDCP_KEY71 - Value of OTP Bank14 Word7 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 14, word 7 (ADDR =
 * 0x77).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_hdcp_key71
{
    reg32_t U;
    struct _hw_ocotp_hdcp_key71_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 14, word 7 (ADDR = 0x77).
    } B;
} hw_ocotp_hdcp_key71_t;
#endif

/*
 * constants & macros for entire OCOTP_HDCP_KEY71 register
 */
#define HW_OCOTP_HDCP_KEY71_ADDR      (REGS_OCOTP_BASE + 0xc70)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_HDCP_KEY71           (*(volatile hw_ocotp_hdcp_key71_t *) HW_OCOTP_HDCP_KEY71_ADDR)
#define HW_OCOTP_HDCP_KEY71_RD()      (HW_OCOTP_HDCP_KEY71.U)
#define HW_OCOTP_HDCP_KEY71_WR(v)     (HW_OCOTP_HDCP_KEY71.U = (v))
#define HW_OCOTP_HDCP_KEY71_SET(v)    (HW_OCOTP_HDCP_KEY71_WR(HW_OCOTP_HDCP_KEY71_RD() |  (v)))
#define HW_OCOTP_HDCP_KEY71_CLR(v)    (HW_OCOTP_HDCP_KEY71_WR(HW_OCOTP_HDCP_KEY71_RD() & ~(v)))
#define HW_OCOTP_HDCP_KEY71_TOG(v)    (HW_OCOTP_HDCP_KEY71_WR(HW_OCOTP_HDCP_KEY71_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_HDCP_KEY71 bitfields
 */

/* --- Register HW_OCOTP_HDCP_KEY71, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 14, word 7 (ADDR = 0x77).
 */

#define BP_OCOTP_HDCP_KEY71_BITS      (0)      //!< Bit position for OCOTP_HDCP_KEY71_BITS.
#define BM_OCOTP_HDCP_KEY71_BITS      (0xffffffff)  //!< Bit mask for OCOTP_HDCP_KEY71_BITS.

//! @brief Get value of OCOTP_HDCP_KEY71_BITS from a register value.
#define BG_OCOTP_HDCP_KEY71_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_HDCP_KEY71_BITS) >> BP_OCOTP_HDCP_KEY71_BITS)

//! @brief Format value for bitfield OCOTP_HDCP_KEY71_BITS.
#define BF_OCOTP_HDCP_KEY71_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_HDCP_KEY71_BITS) & BM_OCOTP_HDCP_KEY71_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_HDCP_KEY71_BITS(v)   (HW_OCOTP_HDCP_KEY71_WR((HW_OCOTP_HDCP_KEY71_RD() & ~BM_OCOTP_HDCP_KEY71_BITS) | BF_OCOTP_HDCP_KEY71_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC0 - Value of OTP Bank15 Word0 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC0 - Value of OTP Bank15 Word0 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 0 (ADDR =
 * 0x78).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc0
{
    reg32_t U;
    struct _hw_ocotp_crc0_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 0 (ADDR = 0x78).
    } B;
} hw_ocotp_crc0_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC0 register
 */
#define HW_OCOTP_CRC0_ADDR      (REGS_OCOTP_BASE + 0xd00)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC0           (*(volatile hw_ocotp_crc0_t *) HW_OCOTP_CRC0_ADDR)
#define HW_OCOTP_CRC0_RD()      (HW_OCOTP_CRC0.U)
#define HW_OCOTP_CRC0_WR(v)     (HW_OCOTP_CRC0.U = (v))
#define HW_OCOTP_CRC0_SET(v)    (HW_OCOTP_CRC0_WR(HW_OCOTP_CRC0_RD() |  (v)))
#define HW_OCOTP_CRC0_CLR(v)    (HW_OCOTP_CRC0_WR(HW_OCOTP_CRC0_RD() & ~(v)))
#define HW_OCOTP_CRC0_TOG(v)    (HW_OCOTP_CRC0_WR(HW_OCOTP_CRC0_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC0 bitfields
 */

/* --- Register HW_OCOTP_CRC0, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 0 (ADDR = 0x78).
 */

#define BP_OCOTP_CRC0_BITS      (0)      //!< Bit position for OCOTP_CRC0_BITS.
#define BM_OCOTP_CRC0_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC0_BITS.

//! @brief Get value of OCOTP_CRC0_BITS from a register value.
#define BG_OCOTP_CRC0_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC0_BITS) >> BP_OCOTP_CRC0_BITS)

//! @brief Format value for bitfield OCOTP_CRC0_BITS.
#define BF_OCOTP_CRC0_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC0_BITS) & BM_OCOTP_CRC0_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC0_BITS(v)   (HW_OCOTP_CRC0_WR((HW_OCOTP_CRC0_RD() & ~BM_OCOTP_CRC0_BITS) | BF_OCOTP_CRC0_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC1 - Value of OTP Bank15 Word1 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC1 - Value of OTP Bank15 Word1 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 1 (ADDR =
 * 0x79).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc1
{
    reg32_t U;
    struct _hw_ocotp_crc1_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 1 (ADDR = 0x79).
    } B;
} hw_ocotp_crc1_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC1 register
 */
#define HW_OCOTP_CRC1_ADDR      (REGS_OCOTP_BASE + 0xd10)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC1           (*(volatile hw_ocotp_crc1_t *) HW_OCOTP_CRC1_ADDR)
#define HW_OCOTP_CRC1_RD()      (HW_OCOTP_CRC1.U)
#define HW_OCOTP_CRC1_WR(v)     (HW_OCOTP_CRC1.U = (v))
#define HW_OCOTP_CRC1_SET(v)    (HW_OCOTP_CRC1_WR(HW_OCOTP_CRC1_RD() |  (v)))
#define HW_OCOTP_CRC1_CLR(v)    (HW_OCOTP_CRC1_WR(HW_OCOTP_CRC1_RD() & ~(v)))
#define HW_OCOTP_CRC1_TOG(v)    (HW_OCOTP_CRC1_WR(HW_OCOTP_CRC1_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC1 bitfields
 */

/* --- Register HW_OCOTP_CRC1, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 1 (ADDR = 0x79).
 */

#define BP_OCOTP_CRC1_BITS      (0)      //!< Bit position for OCOTP_CRC1_BITS.
#define BM_OCOTP_CRC1_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC1_BITS.

//! @brief Get value of OCOTP_CRC1_BITS from a register value.
#define BG_OCOTP_CRC1_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC1_BITS) >> BP_OCOTP_CRC1_BITS)

//! @brief Format value for bitfield OCOTP_CRC1_BITS.
#define BF_OCOTP_CRC1_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC1_BITS) & BM_OCOTP_CRC1_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC1_BITS(v)   (HW_OCOTP_CRC1_WR((HW_OCOTP_CRC1_RD() & ~BM_OCOTP_CRC1_BITS) | BF_OCOTP_CRC1_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC2 - Value of OTP Bank15 Word2 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC2 - Value of OTP Bank15 Word2 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 2 (ADDR =
 * 0x7A).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc2
{
    reg32_t U;
    struct _hw_ocotp_crc2_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 2 (ADDR = 0x7A).
    } B;
} hw_ocotp_crc2_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC2 register
 */
#define HW_OCOTP_CRC2_ADDR      (REGS_OCOTP_BASE + 0xd20)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC2           (*(volatile hw_ocotp_crc2_t *) HW_OCOTP_CRC2_ADDR)
#define HW_OCOTP_CRC2_RD()      (HW_OCOTP_CRC2.U)
#define HW_OCOTP_CRC2_WR(v)     (HW_OCOTP_CRC2.U = (v))
#define HW_OCOTP_CRC2_SET(v)    (HW_OCOTP_CRC2_WR(HW_OCOTP_CRC2_RD() |  (v)))
#define HW_OCOTP_CRC2_CLR(v)    (HW_OCOTP_CRC2_WR(HW_OCOTP_CRC2_RD() & ~(v)))
#define HW_OCOTP_CRC2_TOG(v)    (HW_OCOTP_CRC2_WR(HW_OCOTP_CRC2_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC2 bitfields
 */

/* --- Register HW_OCOTP_CRC2, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 2 (ADDR = 0x7A).
 */

#define BP_OCOTP_CRC2_BITS      (0)      //!< Bit position for OCOTP_CRC2_BITS.
#define BM_OCOTP_CRC2_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC2_BITS.

//! @brief Get value of OCOTP_CRC2_BITS from a register value.
#define BG_OCOTP_CRC2_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC2_BITS) >> BP_OCOTP_CRC2_BITS)

//! @brief Format value for bitfield OCOTP_CRC2_BITS.
#define BF_OCOTP_CRC2_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC2_BITS) & BM_OCOTP_CRC2_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC2_BITS(v)   (HW_OCOTP_CRC2_WR((HW_OCOTP_CRC2_RD() & ~BM_OCOTP_CRC2_BITS) | BF_OCOTP_CRC2_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC3 - Value of OTP Bank15 Word3 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC3 - Value of OTP Bank15 Word3 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 3 (ADDR =
 * 0x7B).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc3
{
    reg32_t U;
    struct _hw_ocotp_crc3_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 3 (ADDR = 0x7B).
    } B;
} hw_ocotp_crc3_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC3 register
 */
#define HW_OCOTP_CRC3_ADDR      (REGS_OCOTP_BASE + 0xd30)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC3           (*(volatile hw_ocotp_crc3_t *) HW_OCOTP_CRC3_ADDR)
#define HW_OCOTP_CRC3_RD()      (HW_OCOTP_CRC3.U)
#define HW_OCOTP_CRC3_WR(v)     (HW_OCOTP_CRC3.U = (v))
#define HW_OCOTP_CRC3_SET(v)    (HW_OCOTP_CRC3_WR(HW_OCOTP_CRC3_RD() |  (v)))
#define HW_OCOTP_CRC3_CLR(v)    (HW_OCOTP_CRC3_WR(HW_OCOTP_CRC3_RD() & ~(v)))
#define HW_OCOTP_CRC3_TOG(v)    (HW_OCOTP_CRC3_WR(HW_OCOTP_CRC3_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC3 bitfields
 */

/* --- Register HW_OCOTP_CRC3, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 3 (ADDR = 0x7B).
 */

#define BP_OCOTP_CRC3_BITS      (0)      //!< Bit position for OCOTP_CRC3_BITS.
#define BM_OCOTP_CRC3_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC3_BITS.

//! @brief Get value of OCOTP_CRC3_BITS from a register value.
#define BG_OCOTP_CRC3_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC3_BITS) >> BP_OCOTP_CRC3_BITS)

//! @brief Format value for bitfield OCOTP_CRC3_BITS.
#define BF_OCOTP_CRC3_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC3_BITS) & BM_OCOTP_CRC3_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC3_BITS(v)   (HW_OCOTP_CRC3_WR((HW_OCOTP_CRC3_RD() & ~BM_OCOTP_CRC3_BITS) | BF_OCOTP_CRC3_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC4 - Value of OTP Bank15 Word4 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC4 - Value of OTP Bank15 Word4 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 4 (ADDR =
 * 0x7C).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc4
{
    reg32_t U;
    struct _hw_ocotp_crc4_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 4 (ADDR = 0x7C).
    } B;
} hw_ocotp_crc4_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC4 register
 */
#define HW_OCOTP_CRC4_ADDR      (REGS_OCOTP_BASE + 0xd40)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC4           (*(volatile hw_ocotp_crc4_t *) HW_OCOTP_CRC4_ADDR)
#define HW_OCOTP_CRC4_RD()      (HW_OCOTP_CRC4.U)
#define HW_OCOTP_CRC4_WR(v)     (HW_OCOTP_CRC4.U = (v))
#define HW_OCOTP_CRC4_SET(v)    (HW_OCOTP_CRC4_WR(HW_OCOTP_CRC4_RD() |  (v)))
#define HW_OCOTP_CRC4_CLR(v)    (HW_OCOTP_CRC4_WR(HW_OCOTP_CRC4_RD() & ~(v)))
#define HW_OCOTP_CRC4_TOG(v)    (HW_OCOTP_CRC4_WR(HW_OCOTP_CRC4_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC4 bitfields
 */

/* --- Register HW_OCOTP_CRC4, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 4 (ADDR = 0x7C).
 */

#define BP_OCOTP_CRC4_BITS      (0)      //!< Bit position for OCOTP_CRC4_BITS.
#define BM_OCOTP_CRC4_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC4_BITS.

//! @brief Get value of OCOTP_CRC4_BITS from a register value.
#define BG_OCOTP_CRC4_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC4_BITS) >> BP_OCOTP_CRC4_BITS)

//! @brief Format value for bitfield OCOTP_CRC4_BITS.
#define BF_OCOTP_CRC4_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC4_BITS) & BM_OCOTP_CRC4_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC4_BITS(v)   (HW_OCOTP_CRC4_WR((HW_OCOTP_CRC4_RD() & ~BM_OCOTP_CRC4_BITS) | BF_OCOTP_CRC4_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC5 - Value of OTP Bank15 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC5 - Value of OTP Bank15 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 5 (ADDR =
 * 0x7D).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc5
{
    reg32_t U;
    struct _hw_ocotp_crc5_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 5 (ADDR = 0x7D).
    } B;
} hw_ocotp_crc5_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC5 register
 */
#define HW_OCOTP_CRC5_ADDR      (REGS_OCOTP_BASE + 0xd50)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC5           (*(volatile hw_ocotp_crc5_t *) HW_OCOTP_CRC5_ADDR)
#define HW_OCOTP_CRC5_RD()      (HW_OCOTP_CRC5.U)
#define HW_OCOTP_CRC5_WR(v)     (HW_OCOTP_CRC5.U = (v))
#define HW_OCOTP_CRC5_SET(v)    (HW_OCOTP_CRC5_WR(HW_OCOTP_CRC5_RD() |  (v)))
#define HW_OCOTP_CRC5_CLR(v)    (HW_OCOTP_CRC5_WR(HW_OCOTP_CRC5_RD() & ~(v)))
#define HW_OCOTP_CRC5_TOG(v)    (HW_OCOTP_CRC5_WR(HW_OCOTP_CRC5_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC5 bitfields
 */

/* --- Register HW_OCOTP_CRC5, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 5 (ADDR = 0x7D).
 */

#define BP_OCOTP_CRC5_BITS      (0)      //!< Bit position for OCOTP_CRC5_BITS.
#define BM_OCOTP_CRC5_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC5_BITS.

//! @brief Get value of OCOTP_CRC5_BITS from a register value.
#define BG_OCOTP_CRC5_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC5_BITS) >> BP_OCOTP_CRC5_BITS)

//! @brief Format value for bitfield OCOTP_CRC5_BITS.
#define BF_OCOTP_CRC5_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC5_BITS) & BM_OCOTP_CRC5_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC5_BITS(v)   (HW_OCOTP_CRC5_WR((HW_OCOTP_CRC5_RD() & ~BM_OCOTP_CRC5_BITS) | BF_OCOTP_CRC5_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC6 - Value of OTP Bank15 Word6 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC6 - Value of OTP Bank15 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 6 (ADDR =
 * 0x7E).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc6
{
    reg32_t U;
    struct _hw_ocotp_crc6_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 6 (ADDR = 0x7E).
    } B;
} hw_ocotp_crc6_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC6 register
 */
#define HW_OCOTP_CRC6_ADDR      (REGS_OCOTP_BASE + 0xd60)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC6           (*(volatile hw_ocotp_crc6_t *) HW_OCOTP_CRC6_ADDR)
#define HW_OCOTP_CRC6_RD()      (HW_OCOTP_CRC6.U)
#define HW_OCOTP_CRC6_WR(v)     (HW_OCOTP_CRC6.U = (v))
#define HW_OCOTP_CRC6_SET(v)    (HW_OCOTP_CRC6_WR(HW_OCOTP_CRC6_RD() |  (v)))
#define HW_OCOTP_CRC6_CLR(v)    (HW_OCOTP_CRC6_WR(HW_OCOTP_CRC6_RD() & ~(v)))
#define HW_OCOTP_CRC6_TOG(v)    (HW_OCOTP_CRC6_WR(HW_OCOTP_CRC6_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC6 bitfields
 */

/* --- Register HW_OCOTP_CRC6, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 6 (ADDR = 0x7E).
 */

#define BP_OCOTP_CRC6_BITS      (0)      //!< Bit position for OCOTP_CRC6_BITS.
#define BM_OCOTP_CRC6_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC6_BITS.

//! @brief Get value of OCOTP_CRC6_BITS from a register value.
#define BG_OCOTP_CRC6_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC6_BITS) >> BP_OCOTP_CRC6_BITS)

//! @brief Format value for bitfield OCOTP_CRC6_BITS.
#define BF_OCOTP_CRC6_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC6_BITS) & BM_OCOTP_CRC6_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC6_BITS(v)   (HW_OCOTP_CRC6_WR((HW_OCOTP_CRC6_RD() & ~BM_OCOTP_CRC6_BITS) | BF_OCOTP_CRC6_BITS(v)))
#endif

//-------------------------------------------------------------------------------------------
// HW_OCOTP_CRC7 - Value of OTP Bank15 Word5 (HW Capabilities)
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_OCOTP_CRC7 - Value of OTP Bank15 Word5 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 15, word 7 (ADDR =
 * 0x7F).   EXAMPLE   Empty Example.
 */
typedef union _hw_ocotp_crc7
{
    reg32_t U;
    struct _hw_ocotp_crc7_bitfields
    {
        unsigned BITS : 32; //!< [31:0] Reflects value of OTP Bank 15, word 7 (ADDR = 0x7F).
    } B;
} hw_ocotp_crc7_t;
#endif

/*
 * constants & macros for entire OCOTP_CRC7 register
 */
#define HW_OCOTP_CRC7_ADDR      (REGS_OCOTP_BASE + 0xd70)

#ifndef __LANGUAGE_ASM__
#define HW_OCOTP_CRC7           (*(volatile hw_ocotp_crc7_t *) HW_OCOTP_CRC7_ADDR)
#define HW_OCOTP_CRC7_RD()      (HW_OCOTP_CRC7.U)
#define HW_OCOTP_CRC7_WR(v)     (HW_OCOTP_CRC7.U = (v))
#define HW_OCOTP_CRC7_SET(v)    (HW_OCOTP_CRC7_WR(HW_OCOTP_CRC7_RD() |  (v)))
#define HW_OCOTP_CRC7_CLR(v)    (HW_OCOTP_CRC7_WR(HW_OCOTP_CRC7_RD() & ~(v)))
#define HW_OCOTP_CRC7_TOG(v)    (HW_OCOTP_CRC7_WR(HW_OCOTP_CRC7_RD() ^  (v)))
#endif

/*
 * constants & macros for individual OCOTP_CRC7 bitfields
 */

/* --- Register HW_OCOTP_CRC7, field BITS[31:0] (RW)
 *
 * Reflects value of OTP Bank 15, word 7 (ADDR = 0x7F).
 */

#define BP_OCOTP_CRC7_BITS      (0)      //!< Bit position for OCOTP_CRC7_BITS.
#define BM_OCOTP_CRC7_BITS      (0xffffffff)  //!< Bit mask for OCOTP_CRC7_BITS.

//! @brief Get value of OCOTP_CRC7_BITS from a register value.
#define BG_OCOTP_CRC7_BITS(r)   ((__REG_VALUE_TYPE((r), reg32_t) & BM_OCOTP_CRC7_BITS) >> BP_OCOTP_CRC7_BITS)

//! @brief Format value for bitfield OCOTP_CRC7_BITS.
#define BF_OCOTP_CRC7_BITS(v)   ((__REG_VALUE_TYPE((v), reg32_t) << BP_OCOTP_CRC7_BITS) & BM_OCOTP_CRC7_BITS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the BITS field to a new value.
#define BW_OCOTP_CRC7_BITS(v)   (HW_OCOTP_CRC7_WR((HW_OCOTP_CRC7_RD() & ~BM_OCOTP_CRC7_BITS) | BF_OCOTP_CRC7_BITS(v)))
#endif


/*!
 * @brief All OCOTP module registers.
 */
#ifndef __LANGUAGE_ASM__
#pragma pack(1)
typedef struct _hw_ocotp
{
    volatile hw_ocotp_ctrl_t CTRL; //!< OTP Controller Control Register
    volatile reg32_t CTRL_SET; //!< OTP Controller Control Register Set
    volatile reg32_t CTRL_CLR; //!< OTP Controller Control Register Clear
    volatile reg32_t CTRL_TOG; //!< OTP Controller Control Register Toggle
    volatile hw_ocotp_timing_t TIMING; //!< OTP Controller Timing Register
    reg32_t _reserved0[3];
    volatile hw_ocotp_data_t DATA; //!< OTP Controller Write Data Register
    reg32_t _reserved1[3];
    volatile hw_ocotp_read_ctrl_t READ_CTRL; //!< OTP Controller Write Data Register
    reg32_t _reserved2[3];
    volatile hw_ocotp_read_fuse_data_t READ_FUSE_DATA; //!< OTP Controller Read Data Register
    reg32_t _reserved3[3];
    volatile hw_ocotp_sw_sticky_t SW_STICKY; //!< Sticky bit Register
    reg32_t _reserved4[3];
    volatile hw_ocotp_scs_t SCS; //!< Software Controllable Signals Register
    volatile reg32_t SCS_SET; //!< Software Controllable Signals Register Set
    volatile reg32_t SCS_CLR; //!< Software Controllable Signals Register Clear
    volatile reg32_t SCS_TOG; //!< Software Controllable Signals Register Toggle
    volatile hw_ocotp_crc_addr_t CRC_ADDR; //!< OTP Controller CRC test address
    reg32_t _reserved5[3];
    volatile hw_ocotp_crc_value_t CRC_VALUE; //!< OTP Controller CRC Value Register
    reg32_t _reserved6[3];
    volatile hw_ocotp_version_t VERSION; //!< OTP Controller Version Register
    reg32_t _reserved7[219];
    volatile hw_ocotp_lock_t LOCK; //!< Value of OTP Bank0 Word0 (Lock controls)
    reg32_t _reserved8[3];
    volatile hw_ocotp_cfg0_t CFG0; //!< Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.)
    reg32_t _reserved9[3];
    volatile hw_ocotp_cfg1_t CFG1; //!< Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.)
    reg32_t _reserved10[3];
    volatile hw_ocotp_cfg2_t CFG2; //!< Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.)
    reg32_t _reserved11[3];
    volatile hw_ocotp_cfg3_t CFG3; //!< Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.)
    reg32_t _reserved12[3];
    volatile hw_ocotp_cfg4_t CFG4; //!< Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.)
    reg32_t _reserved13[3];
    volatile hw_ocotp_cfg5_t CFG5; //!< Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.)
    reg32_t _reserved14[3];
    volatile hw_ocotp_cfg6_t CFG6; //!< Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.)
    reg32_t _reserved15[3];
    volatile hw_ocotp_mem0_t MEM0; //!< Value of OTP Bank1 Word0 (Memory Related Info.)
    reg32_t _reserved16[3];
    volatile hw_ocotp_mem1_t MEM1; //!< Value of OTP Bank1 Word1 (Memory Related Info.)
    reg32_t _reserved17[3];
    volatile hw_ocotp_mem2_t MEM2; //!< Value of OTP Bank1 Word2 (Memory Related Info.)
    reg32_t _reserved18[3];
    volatile hw_ocotp_mem3_t MEM3; //!< Value of OTP Bank1 Word3 (Memory Related Info.)
    reg32_t _reserved19[3];
    volatile hw_ocotp_mem4_t MEM4; //!< Value of OTP Bank1 Word4 (Memory Related Info.)
    reg32_t _reserved20[3];
    volatile hw_ocotp_ana0_t ANA0; //!< Value of OTP Bank1 Word5 (Memory Related Info.)
    reg32_t _reserved21[3];
    volatile hw_ocotp_ana1_t ANA1; //!< Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.)
    reg32_t _reserved22[3];
    volatile hw_ocotp_ana2_t ANA2; //!< Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.)
    reg32_t _reserved23[3];
    volatile hw_ocotp_otpmk0_t OTPMK0; //!< Shadow Register for OTP Bank2 Word0 (OTPMK and CRYPTO Key)
    reg32_t _reserved24[3];
    volatile hw_ocotp_otpmk1_t OTPMK1; //!< Shadow Register for OTP Bank2 Word1 (OTPMK and CRYPTO Key)
    reg32_t _reserved25[3];
    volatile hw_ocotp_otpmk2_t OTPMK2; //!< Shadow Register for OTP Bank2 Word2 (OTPMK and CRYPTO Key)
    reg32_t _reserved26[3];
    volatile hw_ocotp_otpmk3_t OTPMK3; //!< Shadow Register for OTP Bank2 Word3 (OTPMK and CRYPTO Key)
    reg32_t _reserved27[3];
    volatile hw_ocotp_otpmk4_t OTPMK4; //!< Shadow Register for OTP Bank2 Word4 (OTPMK Key)
    reg32_t _reserved28[3];
    volatile hw_ocotp_otpmk5_t OTPMK5; //!< Shadow Register for OTP Bank2 Word5 (OTPMK Key)
    reg32_t _reserved29[3];
    volatile hw_ocotp_otpmk6_t OTPMK6; //!< Shadow Register for OTP Bank2 Word6 (OTPMK Key)
    reg32_t _reserved30[3];
    volatile hw_ocotp_otpmk7_t OTPMK7; //!< Shadow Register for OTP Bank2 Word7 (OTPMK Key)
    reg32_t _reserved31[3];
    volatile hw_ocotp_srk0_t SRK0; //!< Shadow Register for OTP Bank3 Word0 (SRK Hash)
    reg32_t _reserved32[3];
    volatile hw_ocotp_srk1_t SRK1; //!< Shadow Register for OTP Bank3 Word1 (SRK Hash)
    reg32_t _reserved33[3];
    volatile hw_ocotp_srk2_t SRK2; //!< Shadow Register for OTP Bank3 Word2 (SRK Hash)
    reg32_t _reserved34[3];
    volatile hw_ocotp_srk3_t SRK3; //!< Shadow Register for OTP Bank3 Word3 (SRK Hash)
    reg32_t _reserved35[3];
    volatile hw_ocotp_srk4_t SRK4; //!< Shadow Register for OTP Bank3 Word4 (SRK Hash)
    reg32_t _reserved36[3];
    volatile hw_ocotp_srk5_t SRK5; //!< Shadow Register for OTP Bank3 Word5 (SRK Hash)
    reg32_t _reserved37[3];
    volatile hw_ocotp_srk6_t SRK6; //!< Shadow Register for OTP Bank3 Word6 (SRK Hash)
    reg32_t _reserved38[3];
    volatile hw_ocotp_srk7_t SRK7; //!< Shadow Register for OTP Bank3 Word7 (SRK Hash)
    reg32_t _reserved39[3];
    volatile hw_ocotp_resp0_t RESP0; //!< Value of OTP Bank4 Word0 (Secure JTAG Response Field)
    reg32_t _reserved40[3];
    volatile hw_ocotp_hsjc_resp1_t HSJC_RESP1; //!< Value of OTP Bank4 Word1 (Secure JTAG Response Field)
    reg32_t _reserved41[3];
    volatile hw_ocotp_mac0_t MAC0; //!< Value of OTP Bank4 Word2 (MAC Address)
    reg32_t _reserved42[3];
    volatile hw_ocotp_mac1_t MAC1; //!< Value of OTP Bank4 Word3 (MAC Address)
    reg32_t _reserved43[3];
    volatile hw_ocotp_hdcp_ksv0_t HDCP_KSV0; //!< Value of OTP Bank4 Word4 (HW Capabilities)
    reg32_t _reserved44[3];
    volatile hw_ocotp_hdcp_ksv1_t HDCP_KSV1; //!< Value of OTP Bank4 Word5 (HW Capabilities)
    reg32_t _reserved45[3];
    volatile hw_ocotp_gp1_t GP1; //!< Value of OTP Bank4 Word6 (HW Capabilities)
    reg32_t _reserved46[3];
    volatile hw_ocotp_gp2_t GP2; //!< Value of OTP Bank4 Word7 (HW Capabilities)
    reg32_t _reserved47[3];
    volatile hw_ocotp_dtcp_key0_t DTCP_KEY0; //!< Value of OTP Bank5 Word0 (HW Capabilities)
    reg32_t _reserved48[3];
    volatile hw_ocotp_dtcp_key1_t DTCP_KEY1; //!< Value of OTP Bank5 Word1 (HW Capabilities)
    reg32_t _reserved49[3];
    volatile hw_ocotp_dtcp_key2_t DTCP_KEY2; //!< Value of OTP Bank5 Word2 (HW Capabilities)
    reg32_t _reserved50[3];
    volatile hw_ocotp_dtcp_key3_t DTCP_KEY3; //!< Value of OTP Bank5 Word3 (HW Capabilities)
    reg32_t _reserved51[3];
    volatile hw_ocotp_dtcp_key4_t DTCP_KEY4; //!< Value of OTP Bank5 Word4 (HW Capabilities)
    reg32_t _reserved52[3];
    volatile hw_ocotp_misc_conf_t MISC_CONF; //!< Value of OTP Bank5 Word5 (HW Capabilities)
    reg32_t _reserved53[3];
    volatile hw_ocotp_field_return_t FIELD_RETURN; //!< Value of OTP Bank5 Word6 (HW Capabilities)
    reg32_t _reserved54[3];
    volatile hw_ocotp_srk_revoke_t SRK_REVOKE; //!< Value of OTP Bank5 Word7 (HW Capabilities)
    reg32_t _reserved55[67];
    volatile hw_ocotp_hdcp_key0_t HDCP_KEY0; //!< Value of OTP Bank6 Word0 (HW Capabilities)
    reg32_t _reserved56[3];
    volatile hw_ocotp_hdcp_key1_t HDCP_KEY1; //!< Value of OTP Bank6 Word1 (HW Capabilities)
    reg32_t _reserved57[3];
    volatile hw_ocotp_hdcp_key2_t HDCP_KEY2; //!< Value of OTP Bank6 Word2 (HW Capabilities)
    reg32_t _reserved58[3];
    volatile hw_ocotp_hdcp_key3_t HDCP_KEY3; //!< Value of OTP Bank6 Word3 (HW Capabilities)
    reg32_t _reserved59[3];
    volatile hw_ocotp_hdcp_key4_t HDCP_KEY4; //!< Value of OTP Bank6 Word4 (HW Capabilities)
    reg32_t _reserved60[3];
    volatile hw_ocotp_hdcp_key5_t HDCP_KEY5; //!< Value of OTP Bank6 Word5 (HW Capabilities)
    reg32_t _reserved61[3];
    volatile hw_ocotp_hdcp_key6_t HDCP_KEY6; //!< Value of OTP Bank6 Word6 (HW Capabilities)
    reg32_t _reserved62[3];
    volatile hw_ocotp_hdcp_key7_t HDCP_KEY7; //!< Value of OTP Bank6 Word7 (HW Capabilities)
    reg32_t _reserved63[3];
    volatile hw_ocotp_hdcp_key8_t HDCP_KEY8; //!< Value of OTP Bank7 Word0 (HW Capabilities)
    reg32_t _reserved64[3];
    volatile hw_ocotp_hdcp_key9_t HDCP_KEY9; //!< Value of OTP Bank7 Word1 (HW Capabilities)
    reg32_t _reserved65[3];
    volatile hw_ocotp_hdcp_key10_t HDCP_KEY10; //!< Value of OTP Bank7 Word2 (HW Capabilities)
    reg32_t _reserved66[3];
    volatile hw_ocotp_hdcp_key11_t HDCP_KEY11; //!< Value of OTP Bank7 Word3 (HW Capabilities)
    reg32_t _reserved67[3];
    volatile hw_ocotp_hdcp_key12_t HDCP_KEY12; //!< Value of OTP Bank7 Word4 (HW Capabilities)
    reg32_t _reserved68[3];
    volatile hw_ocotp_hdcp_key13_t HDCP_KEY13; //!< Value of OTP Bank7 Word5 (HW Capabilities)
    reg32_t _reserved69[3];
    volatile hw_ocotp_hdcp_key14_t HDCP_KEY14; //!< Value of OTP Bank7 Word6 (HW Capabilities)
    reg32_t _reserved70[3];
    volatile hw_ocotp_hdcp_key15_t HDCP_KEY15; //!< Value of OTP Bank7 Word7 (HW Capabilities)
    reg32_t _reserved71[3];
    volatile hw_ocotp_hdcp_key16_t HDCP_KEY16; //!< Value of OTP Bank8 Word0 (HW Capabilities)
    reg32_t _reserved72[3];
    volatile hw_ocotp_hdcp_key17_t HDCP_KEY17; //!< Value of OTP Bank8 Word1 (HW Capabilities)
    reg32_t _reserved73[3];
    volatile hw_ocotp_hdcp_key18_t HDCP_KEY18; //!< Value of OTP Bank8 Word2 (HW Capabilities)
    reg32_t _reserved74[3];
    volatile hw_ocotp_hdcp_key19_t HDCP_KEY19; //!< Value of OTP Bank8 Word3 (HW Capabilities)
    reg32_t _reserved75[3];
    volatile hw_ocotp_hdcp_key20_t HDCP_KEY20; //!< Value of OTP Bank8 Word4 (HW Capabilities)
    reg32_t _reserved76[3];
    volatile hw_ocotp_hdcp_key21_t HDCP_KEY21; //!< Value of OTP Bank8 Word5 (HW Capabilities)
    reg32_t _reserved77[3];
    volatile hw_ocotp_hdcp_key22_t HDCP_KEY22; //!< Value of OTP Bank8 Word6 (HW Capabilities)
    reg32_t _reserved78[3];
    volatile hw_ocotp_hdcp_key23_t HDCP_KEY23; //!< Value of OTP Bank8 Word7 (HW Capabilities)
    reg32_t _reserved79[3];
    volatile hw_ocotp_hdcp_key24_t HDCP_KEY24; //!< Value of OTP Bank9 Word0 (HW Capabilities)
    reg32_t _reserved80[3];
    volatile hw_ocotp_hdcp_key25_t HDCP_KEY25; //!< Value of OTP Bank9 Word1 (HW Capabilities)
    reg32_t _reserved81[3];
    volatile hw_ocotp_hdcp_key26_t HDCP_KEY26; //!< Value of OTP Bank9 Word2 (HW Capabilities)
    reg32_t _reserved82[3];
    volatile hw_ocotp_hdcp_key27_t HDCP_KEY27; //!< Value of OTP Bank9 Word3 (HW Capabilities)
    reg32_t _reserved83[3];
    volatile hw_ocotp_hdcp_key28_t HDCP_KEY28; //!< Value of OTP Bank9 Word4 (HW Capabilities)
    reg32_t _reserved84[3];
    volatile hw_ocotp_hdcp_key29_t HDCP_KEY29; //!< Value of OTP Bank9 Word5 (HW Capabilities)
    reg32_t _reserved85[3];
    volatile hw_ocotp_hdcp_key30_t HDCP_KEY30; //!< Value of OTP Bank9 Word6 (HW Capabilities)
    reg32_t _reserved86[3];
    volatile hw_ocotp_hdcp_key31_t HDCP_KEY31; //!< Value of OTP Bank9 Word7 (HW Capabilities)
    reg32_t _reserved87[3];
    volatile hw_ocotp_hdcp_key32_t HDCP_KEY32; //!< Value of OTP Bank10 Word0 (HW Capabilities)
    reg32_t _reserved88[3];
    volatile hw_ocotp_hdcp_key33_t HDCP_KEY33; //!< Value of OTP Bank10 Word1 (HW Capabilities)
    reg32_t _reserved89[3];
    volatile hw_ocotp_hdcp_key34_t HDCP_KEY34; //!< Value of OTP Bank10 Word2 (HW Capabilities)
    reg32_t _reserved90[3];
    volatile hw_ocotp_hdcp_key35_t HDCP_KEY35; //!< Value of OTP Bank10 Word3 (HW Capabilities)
    reg32_t _reserved91[3];
    volatile hw_ocotp_hdcp_key36_t HDCP_KEY36; //!< Value of OTP Bank10 Word4 (HW Capabilities)
    reg32_t _reserved92[3];
    volatile hw_ocotp_hdcp_key37_t HDCP_KEY37; //!< Value of OTP Bank10 Word5 (HW Capabilities)
    reg32_t _reserved93[3];
    volatile hw_ocotp_hdcp_key38_t HDCP_KEY38; //!< Value of OTP Bank10 Word6 (HW Capabilities)
    reg32_t _reserved94[3];
    volatile hw_ocotp_hdcp_key39_t HDCP_KEY39; //!< Value of OTP Bank10 Word7 (HW Capabilities)
    reg32_t _reserved95[3];
    volatile hw_ocotp_hdcp_key40_t HDCP_KEY40; //!< Value of OTP Bank11 Word0 (HW Capabilities)
    reg32_t _reserved96[3];
    volatile hw_ocotp_hdcp_key41_t HDCP_KEY41; //!< Value of OTP Bank11 Word1 (HW Capabilities)
    reg32_t _reserved97[3];
    volatile hw_ocotp_hdcp_key42_t HDCP_KEY42; //!< Value of OTP Bank11 Word2 (HW Capabilities)
    reg32_t _reserved98[3];
    volatile hw_ocotp_hdcp_key43_t HDCP_KEY43; //!< Value of OTP Bank11 Word3 (HW Capabilities)
    reg32_t _reserved99[3];
    volatile hw_ocotp_hdcp_key44_t HDCP_KEY44; //!< Value of OTP Bank11 Word4 (HW Capabilities)
    reg32_t _reserved100[3];
    volatile hw_ocotp_hdcp_key45_t HDCP_KEY45; //!< Value of OTP Bank11 Word5 (HW Capabilities)
    reg32_t _reserved101[3];
    volatile hw_ocotp_hdcp_key46_t HDCP_KEY46; //!< Value of OTP Bank11 Word6 (HW Capabilities)
    reg32_t _reserved102[3];
    volatile hw_ocotp_hdcp_key47_t HDCP_KEY47; //!< Value of OTP Bank11 Word7 (HW Capabilities)
    reg32_t _reserved103[3];
    volatile hw_ocotp_hdcp_key48_t HDCP_KEY48; //!< Value of OTP Bank12 Word0 (HW Capabilities)
    reg32_t _reserved104[3];
    volatile hw_ocotp_hdcp_key49_t HDCP_KEY49; //!< Value of OTP Bank12 Word1 (HW Capabilities)
    reg32_t _reserved105[3];
    volatile hw_ocotp_hdcp_key50_t HDCP_KEY50; //!< Value of OTP Bank12 Word2 (HW Capabilities)
    reg32_t _reserved106[3];
    volatile hw_ocotp_hdcp_key51_t HDCP_KEY51; //!< Value of OTP Bank12 Word3 (HW Capabilities)
    reg32_t _reserved107[3];
    volatile hw_ocotp_hdcp_key52_t HDCP_KEY52; //!< Value of OTP Bank12 Word4 (HW Capabilities)
    reg32_t _reserved108[3];
    volatile hw_ocotp_hdcp_key53_t HDCP_KEY53; //!< Value of OTP Bank12 Word5 (HW Capabilities)
    reg32_t _reserved109[3];
    volatile hw_ocotp_hdcp_key54_t HDCP_KEY54; //!< Value of OTP Bank12 Word6 (HW Capabilities)
    reg32_t _reserved110[3];
    volatile hw_ocotp_hdcp_key55_t HDCP_KEY55; //!< Value of OTP Bank12 Word7 (HW Capabilities)
    reg32_t _reserved111[3];
    volatile hw_ocotp_hdcp_key56_t HDCP_KEY56; //!< Value of OTP Bank13 Word0 (HW Capabilities)
    reg32_t _reserved112[3];
    volatile hw_ocotp_hdcp_key57_t HDCP_KEY57; //!< Value of OTP Bank13 Word1 (HW Capabilities)
    reg32_t _reserved113[3];
    volatile hw_ocotp_hdcp_key58_t HDCP_KEY58; //!< Value of OTP Bank13 Word2 (HW Capabilities)
    reg32_t _reserved114[3];
    volatile hw_ocotp_hdcp_key59_t HDCP_KEY59; //!< Value of OTP Bank13 Word3 (HW Capabilities)
    reg32_t _reserved115[3];
    volatile hw_ocotp_hdcp_key60_t HDCP_KEY60; //!< Value of OTP Bank13 Word4 (HW Capabilities)
    reg32_t _reserved116[3];
    volatile hw_ocotp_hdcp_key61_t HDCP_KEY61; //!< Value of OTP Bank13 Word5 (HW Capabilities)
    reg32_t _reserved117[3];
    volatile hw_ocotp_hdcp_key62_t HDCP_KEY62; //!< Value of OTP Bank13 Word6 (HW Capabilities)
    reg32_t _reserved118[3];
    volatile hw_ocotp_hdcp_key63_t HDCP_KEY63; //!< Value of OTP Bank13 Word7 (HW Capabilities)
    reg32_t _reserved119[3];
    volatile hw_ocotp_hdcp_key64_t HDCP_KEY64; //!< Value of OTP Bank14 Word0 (HW Capabilities)
    reg32_t _reserved120[3];
    volatile hw_ocotp_hdcp_key65_t HDCP_KEY65; //!< Value of OTP Bank14 Word1 (HW Capabilities)
    reg32_t _reserved121[3];
    volatile hw_ocotp_hdcp_key66_t HDCP_KEY66; //!< Value of OTP Bank14 Word2 (HW Capabilities)
    reg32_t _reserved122[3];
    volatile hw_ocotp_hdcp_key67_t HDCP_KEY67; //!< Value of OTP Bank14 Word3 (HW Capabilities)
    reg32_t _reserved123[3];
    volatile hw_ocotp_hdcp_key68_t HDCP_KEY68; //!< Value of OTP Bank14 Word4 (HW Capabilities)
    reg32_t _reserved124[3];
    volatile hw_ocotp_hdcp_key69_t HDCP_KEY69; //!< Value of OTP Bank14 Word5 (HW Capabilities)
    reg32_t _reserved125[3];
    volatile hw_ocotp_hdcp_key70_t HDCP_KEY70; //!< Value of OTP Bank14 Word6 (HW Capabilities)
    reg32_t _reserved126[3];
    volatile hw_ocotp_hdcp_key71_t HDCP_KEY71; //!< Value of OTP Bank14 Word7 (HW Capabilities)
    reg32_t _reserved127[35];
    volatile hw_ocotp_crc0_t CRC0; //!< Value of OTP Bank15 Word0 (HW Capabilities)
    reg32_t _reserved128[3];
    volatile hw_ocotp_crc1_t CRC1; //!< Value of OTP Bank15 Word1 (HW Capabilities)
    reg32_t _reserved129[3];
    volatile hw_ocotp_crc2_t CRC2; //!< Value of OTP Bank15 Word2 (HW Capabilities)
    reg32_t _reserved130[3];
    volatile hw_ocotp_crc3_t CRC3; //!< Value of OTP Bank15 Word3 (HW Capabilities)
    reg32_t _reserved131[3];
    volatile hw_ocotp_crc4_t CRC4; //!< Value of OTP Bank15 Word4 (HW Capabilities)
    reg32_t _reserved132[3];
    volatile hw_ocotp_crc5_t CRC5; //!< Value of OTP Bank15 Word5 (HW Capabilities)
    reg32_t _reserved133[3];
    volatile hw_ocotp_crc6_t CRC6; //!< Value of OTP Bank15 Word6 (HW Capabilities)
    reg32_t _reserved134[3];
    volatile hw_ocotp_crc7_t CRC7; //!< Value of OTP Bank15 Word5 (HW Capabilities)
} hw_ocotp_t;
#pragma pack()

//! @brief Macro to access all OCOTP registers.
//! @return Reference (not a pointer) to the registers struct. To get a pointer to the struct,
//!     use the '&' operator, like <code>&HW_OCOTP(0)</code>.
#define HW_OCOTP     (*(volatile hw_ocotp_t *) REGS_OCOTP_BASE)

#endif


#endif // __HW_OCOTP_REGISTERS_H__
