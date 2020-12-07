/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_hw.h
* @addtogroup sdps_v3_9
* @{
*
* This header file contains the identifiers and basic HW access driver
* functions (or  macros) that can be used to access the device. Other driver
* functions are defined in xsdps.h.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 1.00a hk/sg  10/17/13 Initial release
* 2.5 	sg	   07/09/15 Added SD 3.0 features
*       kvn    07/15/15 Modified the code according to MISRAC-2012.
* 2.7   sk     12/10/15 Added support for MMC cards.
*       sk     03/02/16 Configured the Tap Delay values for eMMC HS200 mode.
* 2.8   sk     04/20/16 Added new workaround for auto tuning.
* 3.0   sk     06/09/16 Added support for mkfs to calculate sector count.
*       sk     07/16/16 Added support for UHS modes.
*       sk     07/16/16 Added Tap delays accordingly to different SD/eMMC
*                       operating modes.
* 3.1   sk     11/07/16 Enable Rst_n bit in ext_csd reg if not enabled.
* 3.2   sk     03/20/17 Add support for EL1 non-secure mode.
* 3.3   mn     08/22/17 Updated for Word Access System support
*       mn     09/06/17 Added support for ARMCC toolchain
* 3.4   mn     01/22/18 Separated out SDR104 and HS200 clock defines
* 3.6   mn     07/06/18 Fix Doxygen warnings for sdps driver
* 3.8   mn     04/12/19 Modified TapDelay code for supporting ZynqMP and Versal
*       mn     05/21/19 Set correct tap delays for Versal
*       mn     05/21/19 Disable DLL Reset code for Versal
*       mn     07/03/19 Update Input Tap Delays for Versal
* 3.9   mn     03/03/20 Restructured the code for more readability and modularity
*
* </pre>
*
******************************************************************************/

#ifndef SD_HW_H_
#define SD_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of an SD device.
 * @{
 */

#define XSDPS_SDMA_SYS_ADDR_OFFSET	0x00U	/**< SDMA System Address
							Register */
#define XSDPS_SDMA_SYS_ADDR_LO_OFFSET	XSDPS_SDMA_SYS_ADDR_OFFSET
						/**< SDMA System Address
							Low Register */
#define XSDPS_ARGMT2_LO_OFFSET		0x00U	/**< Argument2 Low Register */
#define XSDPS_SDMA_SYS_ADDR_HI_OFFSET	0x02U	/**< SDMA System Address
							High Register */
#define XSDPS_ARGMT2_HI_OFFSET		0x02U	/**< Argument2 High Register */

#define XSDPS_BLK_SIZE_OFFSET		0x04U	/**< Block Size Register */
#define XSDPS_BLK_CNT_OFFSET		0x06U	/**< Block Count Register */
#define XSDPS_ARGMT_OFFSET		0x08U	/**< Argument Register */
#define XSDPS_ARGMT1_LO_OFFSET		XSDPS_ARGMT_OFFSET
						/**< Argument1 Register */
#define XSDPS_ARGMT1_HI_OFFSET		0x0AU	/**< Argument1 Register */

#define XSDPS_XFER_MODE_OFFSET		0x0CU	/**< Transfer Mode Register */
#define XSDPS_CMD_OFFSET		0x0EU	/**< Command Register */
#define XSDPS_RESP0_OFFSET		0x10U	/**< Response0 Register */
#define XSDPS_RESP1_OFFSET		0x14U	/**< Response1 Register */
#define XSDPS_RESP2_OFFSET		0x18U	/**< Response2 Register */
#define XSDPS_RESP3_OFFSET		0x1CU	/**< Response3 Register */
#define XSDPS_BUF_DAT_PORT_OFFSET	0x20U	/**< Buffer Data Port */
#define XSDPS_PRES_STATE_OFFSET		0x24U	/**< Present State */
#define XSDPS_HOST_CTRL1_OFFSET		0x28U	/**< Host Control 1 */
#define XSDPS_POWER_CTRL_OFFSET		0x29U	/**< Power Control */
#define XSDPS_BLK_GAP_CTRL_OFFSET	0x2AU	/**< Block Gap Control */
#define XSDPS_WAKE_UP_CTRL_OFFSET	0x2BU	/**< Wake Up Control */
#define XSDPS_CLK_CTRL_OFFSET		0x2CU	/**< Clock Control */
#define XSDPS_TIMEOUT_CTRL_OFFSET	0x2EU	/**< Timeout Control */
#define XSDPS_SW_RST_OFFSET		0x2FU	/**< Software Reset */
#define XSDPS_NORM_INTR_STS_OFFSET 	0x30U	/**< Normal Interrupt
							Status Register */
#define XSDPS_ERR_INTR_STS_OFFSET 	0x32U	/**< Error Interrupt
							Status Register */
#define XSDPS_NORM_INTR_STS_EN_OFFSET	0x34U	/**< Normal Interrupt
						Status Enable Register */
#define XSDPS_ERR_INTR_STS_EN_OFFSET	0x36U	/**< Error Interrupt
						Status Enable Register */
#define XSDPS_NORM_INTR_SIG_EN_OFFSET	0x38U	/**< Normal Interrupt
						Signal Enable Register */
#define XSDPS_ERR_INTR_SIG_EN_OFFSET	0x3AU	/**< Error Interrupt
						Signal Enable Register */

#define XSDPS_AUTO_CMD12_ERR_STS_OFFSET	0x3CU	/**< Auto CMD12 Error Status
							Register */
#define XSDPS_HOST_CTRL2_OFFSET		0x3EU	/**< Host Control2 Register */
#define XSDPS_CAPS_OFFSET 		0x40U	/**< Capabilities Register */
#define XSDPS_CAPS_EXT_OFFSET 		0x44U	/**< Capabilities Extended */
#define XSDPS_MAX_CURR_CAPS_OFFSET	0x48U	/**< Maximum Current
						Capabilities Register */
#define XSDPS_MAX_CURR_CAPS_EXT_OFFSET	0x4CU	/**< Maximum Current
						Capabilities Ext Register */
#define XSDPS_FE_ERR_INT_STS_OFFSET	0x52U	/**< Force Event for
						Error Interrupt Status */
#define XSDPS_FE_AUTO_CMD12_EIS_OFFSET	0x50U	/**< Auto CM12 Error Interrupt
							Status Register */
#define XSDPS_ADMA_ERR_STS_OFFSET	0x54U	/**< ADMA Error Status
							Register */
#define XSDPS_ADMA_SAR_OFFSET		0x58U	/**< ADMA System Address
							Register */
#define XSDPS_ADMA_SAR_EXT_OFFSET	0x5CU	/**< ADMA System Address
							Extended Register */
#define XSDPS_PRE_VAL_1_OFFSET		0x60U	/**< Preset Value Register */
#define XSDPS_PRE_VAL_2_OFFSET		0x64U	/**< Preset Value Register */
#define XSDPS_PRE_VAL_3_OFFSET		0x68U	/**< Preset Value Register */
#define XSDPS_PRE_VAL_4_OFFSET		0x6CU	/**< Preset Value Register */
#define XSDPS_BOOT_TOUT_CTRL_OFFSET	0x70U	/**< Boot timeout control
							register */

#define XSDPS_SHARED_BUS_CTRL_OFFSET	0xE0U	/**< Shared Bus Control
							Register */
#define XSDPS_SLOT_INTR_STS_OFFSET	0xFCU	/**< Slot Interrupt Status
							Register */
#define XSDPS_HOST_CTRL_VER_OFFSET	0xFEU	/**< Host Controller Version
							Register */

/* @} */

/** @name Control Register - Host control, Power control,
 * 			Block Gap control and Wakeup control
 *
 * This register contains bits for various configuration options of
 * the SD host controller. Read/Write apart from the reserved bits.
 * @{
 */

#define XSDPS_HC_LED_MASK		0x00000001U /**< LED Control */
#define XSDPS_HC_WIDTH_MASK		0x00000002U /**< Bus width */
#define XSDPS_HC_BUS_WIDTH_4		0x00000002U
#define XSDPS_HC_SPEED_MASK		0x00000004U /**< High Speed */
#define XSDPS_HC_DMA_MASK		0x00000018U /**< DMA Mode Select */
#define XSDPS_HC_DMA_SDMA_MASK		0x00000000U /**< SDMA Mode */
#define XSDPS_HC_DMA_ADMA1_MASK		0x00000008U /**< ADMA1 Mode */
#define XSDPS_HC_DMA_ADMA2_32_MASK	0x00000010U /**< ADMA2 Mode - 32 bit */
#define XSDPS_HC_DMA_ADMA2_64_MASK	0x00000018U /**< ADMA2 Mode - 64 bit */
#define XSDPS_HC_EXT_BUS_WIDTH		0x00000020U /**< Bus width - 8 bit */
#define XSDPS_HC_CARD_DET_TL_MASK	0x00000040U /**< Card Detect Tst Lvl */
#define XSDPS_HC_CARD_DET_SD_MASK	0x00000080U /**< Card Detect Sig Det */

#define XSDPS_PC_BUS_PWR_MASK		0x00000001U /**< Bus Power Control */
#define XSDPS_PC_BUS_VSEL_MASK		0x0000000EU /**< Bus Voltage Select */
#define XSDPS_PC_BUS_VSEL_3V3_MASK	0x0000000EU /**< Bus Voltage 3.3V */
#define XSDPS_PC_BUS_VSEL_3V0_MASK	0x0000000CU /**< Bus Voltage 3.0V */
#define XSDPS_PC_BUS_VSEL_1V8_MASK	0x0000000AU /**< Bus Voltage 1.8V */
#define XSDPS_PC_EMMC_HW_RST_MASK	0x00000010U /**< HW reset for eMMC */

#define XSDPS_BGC_STP_REQ_MASK		0x00000001U /**< Block Gap Stop Req */
#define XSDPS_BGC_CNT_REQ_MASK		0x00000002U /**< Block Gap Cont Req */
#define XSDPS_BGC_RWC_MASK		0x00000004U /**< Block Gap Rd Wait */
#define XSDPS_BGC_INTR_MASK		0x00000008U /**< Block Gap Intr */
#define XSDPS_BGC_SPI_MODE_MASK		0x00000010U /**< Block Gap SPI Mode */
#define XSDPS_BGC_BOOT_EN_MASK		0x00000020U /**< Block Gap Boot Enb */
#define XSDPS_BGC_ALT_BOOT_EN_MASK	0x00000040U /**< Block Gap Alt BootEn */
#define XSDPS_BGC_BOOT_ACK_MASK		0x00000080U /**< Block Gap Boot Ack */

#define XSDPS_WC_WUP_ON_INTR_MASK	0x00000001U /**< Wakeup Card Intr */
#define XSDPS_WC_WUP_ON_INSRT_MASK	0x00000002U /**< Wakeup Card Insert */
#define XSDPS_WC_WUP_ON_REM_MASK	0x00000004U /**< Wakeup Card Removal */

/* @} */

/** @name Control Register - Clock control, Timeout control & Software reset
 *
 * This register contains bits for configuration options of clock, timeout and
 * software reset.
 * Read/Write except for Inter_Clock_Stable bit (read only) and reserved bits.
 * @{
 */

#define XSDPS_CC_INT_CLK_EN_MASK		0x00000001U
#define XSDPS_CC_INT_CLK_STABLE_MASK	0x00000002U
#define XSDPS_CC_SD_CLK_EN_MASK			0x00000004U
#define XSDPS_CC_SD_CLK_GEN_SEL_MASK		0x00000020U
#define XSDPS_CC_SDCLK_FREQ_SEL_EXT_MASK	0x00000003U
#define XSDPS_CC_SDCLK_FREQ_SEL_MASK		0x000000FFU
#define XSDPS_CC_SDCLK_FREQ_D256_MASK		0x00008000U
#define XSDPS_CC_SDCLK_FREQ_D128_MASK		0x00004000U
#define XSDPS_CC_SDCLK_FREQ_D64_MASK		0x00002000U
#define XSDPS_CC_SDCLK_FREQ_D32_MASK		0x00001000U
#define XSDPS_CC_SDCLK_FREQ_D16_MASK		0x00000800U
#define XSDPS_CC_SDCLK_FREQ_D8_MASK		0x00000400U
#define XSDPS_CC_SDCLK_FREQ_D4_MASK		0x00000200U
#define XSDPS_CC_SDCLK_FREQ_D2_MASK		0x00000100U
#define XSDPS_CC_SDCLK_FREQ_BASE_MASK	0x00000000U
#define XSDPS_CC_MAX_DIV_CNT			256U
#define XSDPS_CC_EXT_MAX_DIV_CNT		2046U
#define XSDPS_CC_EXT_DIV_SHIFT			6U

#define XSDPS_TC_CNTR_VAL_MASK			0x0000000FU

#define XSDPS_SWRST_ALL_MASK			0x00000001U
#define XSDPS_SWRST_CMD_LINE_MASK		0x00000002U
#define XSDPS_SWRST_DAT_LINE_MASK		0x00000004U

#define XSDPS_CC_MAX_NUM_OF_DIV		9U
#define XSDPS_CC_DIV_SHIFT		8U

/* @} */

/** @name SD Interrupt Registers
 *
 * <b> Normal and Error Interrupt Status Register </b>
 * This register shows the normal and error interrupt status.
 * Status enable register affects reads of this register.
 * If Signal enable register is set and the corresponding status bit is set,
 * interrupt is generated.
 * Write to clear except
 * Error_interrupt and Card_Interrupt bits - Read only
 *
 * <b> Normal and Error Interrupt Status Enable Register </b>
 * Setting this register bits enables Interrupt status.
 * Read/Write except Fixed_to_0 bit (Read only)
 *
 * <b> Normal and Error Interrupt Signal Enable Register </b>
 * This register is used to select which interrupt status is
 * indicated to the Host System as the interrupt.
 * Read/Write except Fixed_to_0 bit (Read only)
 *
 * All three registers have same bit definitions
 * @{
 */

#define XSDPS_INTR_CC_MASK		0x00000001U /**< Command Complete */
#define XSDPS_INTR_TC_MASK		0x00000002U /**< Transfer Complete */
#define XSDPS_INTR_BGE_MASK		0x00000004U /**< Block Gap Event */
#define XSDPS_INTR_DMA_MASK		0x00000008U /**< DMA Interrupt */
#define XSDPS_INTR_BWR_MASK		0x00000010U /**< Buffer Write Ready */
#define XSDPS_INTR_BRR_MASK		0x00000020U /**< Buffer Read Ready */
#define XSDPS_INTR_CARD_INSRT_MASK	0x00000040U /**< Card Insert */
#define XSDPS_INTR_CARD_REM_MASK	0x00000080U /**< Card Remove */
#define XSDPS_INTR_CARD_MASK		0x00000100U /**< Card Interrupt */
#define XSDPS_INTR_INT_A_MASK		0x00000200U /**< INT A Interrupt */
#define XSDPS_INTR_INT_B_MASK		0x00000400U /**< INT B Interrupt */
#define XSDPS_INTR_INT_C_MASK		0x00000800U /**< INT C Interrupt */
#define XSDPS_INTR_RE_TUNING_MASK	0x00001000U /**< Re-Tuning Interrupt */
#define XSDPS_INTR_BOOT_ACK_RECV_MASK	0x00002000U /**< Boot Ack Recv
							Interrupt */
#define XSDPS_INTR_BOOT_TERM_MASK	0x00004000U /**< Boot Terminate
							Interrupt */
#define XSDPS_INTR_ERR_MASK		0x00008000U /**< Error Interrupt */
#define XSDPS_NORM_INTR_ALL_MASK	0x0000FFFFU

#define XSDPS_INTR_ERR_CT_MASK		0x00000001U /**< Command Timeout
							Error */
#define XSDPS_INTR_ERR_CCRC_MASK	0x00000002U /**< Command CRC Error */
#define XSDPS_INTR_ERR_CEB_MASK		0x00000004U /**< Command End Bit
							Error */
#define XSDPS_INTR_ERR_CI_MASK		0x00000008U /**< Command Index Error */
#define XSDPS_INTR_ERR_DT_MASK		0x00000010U /**< Data Timeout Error */
#define XSDPS_INTR_ERR_DCRC_MASK	0x00000020U /**< Data CRC Error */
#define XSDPS_INTR_ERR_DEB_MASK		0x00000040U /**< Data End Bit Error */
#define XSDPS_INTR_ERR_CUR_LMT_MASK	0x00000080U /**< Current Limit Error */
#define XSDPS_INTR_ERR_AUTO_CMD12_MASK	0x00000100U /**< Auto CMD12 Error */
#define XSDPS_INTR_ERR_ADMA_MASK	0x00000200U /**< ADMA Error */
#define XSDPS_INTR_ERR_TR_MASK		0x00001000U /**< Tuning Error */
#define XSDPS_INTR_VEND_SPF_ERR_MASK	0x0000E000U /**< Vendor Specific
							Error */
#define XSDPS_ERROR_INTR_ALL_MASK	0x0000F3FFU /**< Mask for error bits */
/* @} */

/** @name Block Size and Block Count Register
 *
 * This register contains the block count for current transfer,
 * block size and SDMA buffer size.
 * Read/Write except for reserved bits.
 * @{
 */

#define XSDPS_BLK_SIZE_MASK		0x00000FFFU /**< Transfer Block Size */
#define XSDPS_SDMA_BUFF_SIZE_MASK	0x00007000U /**< Host SDMA Buffer Size */
#define XSDPS_BLK_SIZE_1024		0x400U
#define XSDPS_BLK_SIZE_2048		0x800U
#define XSDPS_BLK_CNT_MASK		0x0000FFFFU /**< Block Count for
								Current Transfer */

/* @} */

/** @name Transfer Mode and Command Register
 *
 * The Transfer Mode register is used to control the data transfers and
 * Command register is used for command generation
 * Read/Write except for reserved bits.
 * @{
 */

#define XSDPS_TM_DMA_EN_MASK		0x00000001U /**< DMA Enable */
#define XSDPS_TM_BLK_CNT_EN_MASK	0x00000002U /**< Block Count Enable */
#define XSDPS_TM_AUTO_CMD12_EN_MASK	0x00000004U /**< Auto CMD12 Enable */
#define XSDPS_TM_DAT_DIR_SEL_MASK	0x00000010U /**< Data Transfer
							Direction Select */
#define XSDPS_TM_MUL_SIN_BLK_SEL_MASK	0x00000020U /**< Multi/Single
							Block Select */

#define XSDPS_CMD_RESP_SEL_MASK		0x00000003U /**< Response Type
							Select */
#define XSDPS_CMD_RESP_NONE_MASK	0x00000000U /**< No Response */
#define XSDPS_CMD_RESP_L136_MASK	0x00000001U /**< Response length 138 */
#define XSDPS_CMD_RESP_L48_MASK		0x00000002U /**< Response length 48 */
#define XSDPS_CMD_RESP_L48_BSY_CHK_MASK	0x00000003U /**< Response length 48 &
							check busy after
							response */
#define XSDPS_CMD_CRC_CHK_EN_MASK	0x00000008U /**< Command CRC Check
							Enable */
#define XSDPS_CMD_INX_CHK_EN_MASK	0x00000010U /**< Command Index Check
							Enable */
#define XSDPS_DAT_PRESENT_SEL_MASK	0x00000020U /**< Data Present Select */
#define XSDPS_CMD_TYPE_MASK		0x000000C0U /**< Command Type */
#define XSDPS_CMD_TYPE_NORM_MASK	0x00000000U /**< CMD Type - Normal */
#define XSDPS_CMD_TYPE_SUSPEND_MASK	0x00000040U /**< CMD Type - Suspend */
#define XSDPS_CMD_TYPE_RESUME_MASK	0x00000080U /**< CMD Type - Resume */
#define XSDPS_CMD_TYPE_ABORT_MASK	0x000000C0U /**< CMD Type - Abort */
#define XSDPS_CMD_MASK			0x00003F00U /**< Command Index Mask -
							Set to CMD0-63,
							AMCD0-63 */

/* @} */

/** @name Auto CMD Error Status Register
 *
 * This register is read only register which contains
 * information about the error status of Auto CMD 12 and 23.
 * Read Only
 * @{
 */
#define XSDPS_AUTO_CMD12_NT_EX_MASK	0x0001U /**< Auto CMD12 Not
							executed */
#define XSDPS_AUTO_CMD_TOUT_MASK	0x0002U /**< Auto CMD Timeout
							Error */
#define XSDPS_AUTO_CMD_CRC_MASK		0x0004U /**< Auto CMD CRC Error */
#define XSDPS_AUTO_CMD_EB_MASK		0x0008U /**< Auto CMD End Bit
							Error */
#define XSDPS_AUTO_CMD_IND_MASK		0x0010U /**< Auto CMD Index Error */
#define XSDPS_AUTO_CMD_CNI_ERR_MASK	0x0080U /**< Command not issued by
							Auto CMD12 Error */
/* @} */

/** @name Host Control2 Register
 *
 * This register contains extended configuration bits.
 * Read Write
 * @{
 */
#define XSDPS_HC2_UHS_MODE_MASK		0x0007U /**< UHS Mode select bits */
#define XSDPS_HC2_UHS_MODE_SDR12_MASK	0x0000U /**< SDR12 UHS Mode */
#define XSDPS_HC2_UHS_MODE_SDR25_MASK	0x0001U /**< SDR25 UHS Mode */
#define XSDPS_HC2_UHS_MODE_SDR50_MASK	0x0002U /**< SDR50 UHS Mode */
#define XSDPS_HC2_UHS_MODE_SDR104_MASK	0x0003U /**< SDR104 UHS Mode */
#define XSDPS_HC2_UHS_MODE_DDR50_MASK	0x0004U /**< DDR50 UHS Mode */
#define XSDPS_HC2_1V8_EN_MASK		0x0008U /**< 1.8V Signal Enable */
#define XSDPS_HC2_DRV_STR_SEL_MASK	0x0030U /**< Driver Strength
							Selection */
#define XSDPS_HC2_DRV_STR_B_MASK	0x0000U /**< Driver Strength B */
#define XSDPS_HC2_DRV_STR_A_MASK	0x0010U /**< Driver Strength A */
#define XSDPS_HC2_DRV_STR_C_MASK	0x0020U /**< Driver Strength C */
#define XSDPS_HC2_DRV_STR_D_MASK	0x0030U /**< Driver Strength D */
#define XSDPS_HC2_EXEC_TNG_MASK		0x0040U /**< Execute Tuning */
#define XSDPS_HC2_SAMP_CLK_SEL_MASK	0x0080U /**< Sampling Clock
							Selection */
#define XSDPS_HC2_ASYNC_INTR_EN_MASK	0x4000U /**< Asynchronous Interrupt
							Enable */
#define XSDPS_HC2_PRE_VAL_EN_MASK	0x8000U /**< Preset Value Enable */

/* @} */

/** @name Capabilities Register
 *
 * Capabilities register is a read only register which contains
 * information about the host controller.
 * Sufficient if read once after power on.
 * Read Only
 * @{
 */
#define XSDPS_CAP_TOUT_CLK_FREQ_MASK	0x0000003FU /**< Timeout clock freq
							select */
#define XSDPS_CAP_TOUT_CLK_UNIT_MASK	0x00000080U /**< Timeout clock unit -
							MHz/KHz */
#define XSDPS_CAP_MAX_BLK_LEN_MASK	0x00030000U /**< Max block length */
#define XSDPS_CAP_MAX_BLK_LEN_512B_MASK	0x00000000U /**< Max block 512 bytes */
#define XSDPS_CAP_MAX_BL_LN_1024_MASK	0x00010000U /**< Max block 1024 bytes */
#define XSDPS_CAP_MAX_BL_LN_2048_MASK	0x00020000U /**< Max block 2048 bytes */
#define XSDPS_CAP_MAX_BL_LN_4096_MASK	0x00030000U /**< Max block 4096 bytes */

#define XSDPS_CAP_EXT_MEDIA_BUS_MASK	0x00040000U /**< Extended media bus */
#define XSDPS_CAP_ADMA2_MASK		0x00080000U /**< ADMA2 support */
#define XSDPS_CAP_HIGH_SPEED_MASK	0x00200000U /**< High speed support */
#define XSDPS_CAP_SDMA_MASK		0x00400000U /**< SDMA support */
#define XSDPS_CAP_SUSP_RESUME_MASK	0x00800000U /**< Suspend/Resume
							support */
#define XSDPS_CAP_VOLT_3V3_MASK		0x01000000U /**< 3.3V support */
#define XSDPS_CAP_VOLT_3V0_MASK		0x02000000U /**< 3.0V support */
#define XSDPS_CAP_VOLT_1V8_MASK		0x04000000U /**< 1.8V support */

#define XSDPS_CAP_SYS_BUS_64_MASK	0x10000000U /**< 64 bit system bus
							support */
/* Spec 2.0 */
#define XSDPS_CAP_INTR_MODE_MASK	0x08000000U /**< Interrupt mode
							support */
#define XSDPS_CAP_SPI_MODE_MASK		0x20000000U /**< SPI mode */
#define XSDPS_CAP_SPI_BLOCK_MODE_MASK	0x40000000U /**< SPI block mode */


/* Spec 3.0 */
#define XSDPS_CAPS_ASYNC_INTR_MASK	0x20000000U /**< Async Interrupt
							support */
#define XSDPS_CAPS_SLOT_TYPE_MASK	0xC0000000U /**< Slot Type */
#define XSDPS_CAPS_REM_CARD			0x00000000U /**< Removable Slot */
#define XSDPS_CAPS_EMB_SLOT			0x40000000U /**< Embedded Slot */
#define XSDPS_CAPS_SHR_BUS			0x80000000U /**< Shared Bus Slot */

#define XSDPS_ECAPS_SDR50_MASK		0x00000001U /**< SDR50 Mode support */
#define XSDPS_ECAPS_SDR104_MASK		0x00000002U /**< SDR104 Mode support */
#define XSDPS_ECAPS_DDR50_MASK		0x00000004U /**< DDR50 Mode support */
#define XSDPS_ECAPS_DRV_TYPE_A_MASK	0x00000010U /**< DriverType A support */
#define XSDPS_ECAPS_DRV_TYPE_C_MASK	0x00000020U /**< DriverType C support */
#define XSDPS_ECAPS_DRV_TYPE_D_MASK	0x00000040U /**< DriverType D support */
#define XSDPS_ECAPS_TMR_CNT_MASK	0x00000F00U /**< Timer Count for
							Re-tuning */
#define XSDPS_ECAPS_USE_TNG_SDR50_MASK	0x00002000U /**< SDR50 Mode needs
							tuning */
#define XSDPS_ECAPS_RE_TNG_MODES_MASK	0x0000C000U /**< Re-tuning modes
							support */
#define XSDPS_ECAPS_RE_TNG_MODE1_MASK	0x00000000U /**< Re-tuning mode 1 */
#define XSDPS_ECAPS_RE_TNG_MODE2_MASK	0x00004000U /**< Re-tuning mode 2 */
#define XSDPS_ECAPS_RE_TNG_MODE3_MASK	0x00008000U /**< Re-tuning mode 3 */
#define XSDPS_ECAPS_CLK_MULT_MASK	0x00FF0000U /**< Clock Multiplier value
							for Programmable clock
							mode */
#define XSDPS_ECAPS_SPI_MODE_MASK	0x01000000U /**< SPI mode */
#define XSDPS_ECAPS_SPI_BLK_MODE_MASK	0x02000000U /**< SPI block mode */

/* @} */

/** @name Present State Register
 *
 * Gives the current status of the host controller
 * Read Only
 * @{
 */

#define XSDPS_PSR_INHIBIT_CMD_MASK	0x00000001U /**< Command inhibit - CMD */
#define XSDPS_PSR_INHIBIT_DAT_MASK	0x00000002U /**< Command Inhibit - DAT */
#define XSDPS_PSR_DAT_ACTIVE_MASK	0x00000004U /**< DAT line active */
#define XSDPS_PSR_RE_TUNING_REQ_MASK	0x00000008U /**< Re-tuning request */
#define XSDPS_PSR_WR_ACTIVE_MASK	0x00000100U /**< Write transfer active */
#define XSDPS_PSR_RD_ACTIVE_MASK	0x00000200U /**< Read transfer active */
#define XSDPS_PSR_BUFF_WR_EN_MASK	0x00000400U /**< Buffer write enable */
#define XSDPS_PSR_BUFF_RD_EN_MASK	0x00000800U /**< Buffer read enable */
#define XSDPS_PSR_CARD_INSRT_MASK	0x00010000U /**< Card inserted */
#define XSDPS_PSR_CARD_STABLE_MASK	0x00020000U /**< Card state stable */
#define XSDPS_PSR_CARD_DPL_MASK		0x00040000U /**< Card detect pin level */
#define XSDPS_PSR_WPS_PL_MASK		0x00080000U /**< Write protect switch
								pin level */
#define XSDPS_PSR_DAT30_SG_LVL_MASK	0x00F00000U /**< Data 3:0 signal lvl */
#define XSDPS_PSR_CMD_SG_LVL_MASK	0x01000000U /**< Cmd Line signal lvl */
#define XSDPS_PSR_DAT74_SG_LVL_MASK	0x1E000000U /**< Data 7:4 signal lvl */

/* @} */

/** @name Maximum Current Capabilities Register
 *
 * This register is read only register which contains
 * information about current capabilities at each voltage levels.
 * Read Only
 * @{
 */
#define XSDPS_MAX_CUR_CAPS_1V8_MASK	0x00000F00U /**< Maximum Current
							Capability at 1.8V */
#define XSDPS_MAX_CUR_CAPS_3V0_MASK	0x000000F0U /**< Maximum Current
							Capability at 3.0V */
#define XSDPS_MAX_CUR_CAPS_3V3_MASK	0x0000000FU /**< Maximum Current
							Capability at 3.3V */
/* @} */


/** @name Force Event for Auto CMD Error Status Register
 *
 * This register is write only register which contains
 * control bits to generate events for Auto CMD error status.
 * Write Only
 * @{
 */
#define XSDPS_FE_AUTO_CMD12_NT_EX_MASK	0x0001U /**< Auto CMD12 Not
							executed */
#define XSDPS_FE_AUTO_CMD_TOUT_MASK	0x0002U /**< Auto CMD Timeout
							Error */
#define XSDPS_FE_AUTO_CMD_CRC_MASK	0x0004U /**< Auto CMD CRC Error */
#define XSDPS_FE_AUTO_CMD_EB_MASK	0x0008U /**< Auto CMD End Bit
							Error */
#define XSDPS_FE_AUTO_CMD_IND_MASK	0x0010U /**< Auto CMD Index Error */
#define XSDPS_FE_AUTO_CMD_CNI_ERR_MASK	0x0080U /**< Command not issued by
							Auto CMD12 Error */
/* @} */



/** @name Force Event for Error Interrupt Status Register
 *
 * This register is write only register which contains
 * control bits to generate events of error interrupt status register.
 * Write Only
 * @{
 */
#define XSDPS_FE_INTR_ERR_CT_MASK	0x0001U /**< Command Timeout
							Error */
#define XSDPS_FE_INTR_ERR_CCRC_MASK	0x0002U /**< Command CRC Error */
#define XSDPS_FE_INTR_ERR_CEB_MASK	0x0004U /**< Command End Bit
							Error */
#define XSDPS_FE_INTR_ERR_CI_MASK	0x0008U /**< Command Index Error */
#define XSDPS_FE_INTR_ERR_DT_MASK	0x0010U /**< Data Timeout Error */
#define XSDPS_FE_INTR_ERR_DCRC_MASK	0x0020U /**< Data CRC Error */
#define XSDPS_FE_INTR_ERR_DEB_MASK	0x0040U /**< Data End Bit Error */
#define XSDPS_FE_INTR_ERR_CUR_LMT_MASK	0x0080U /**< Current Limit Error */
#define XSDPS_FE_INTR_ERR_AUTO_CMD_MASK	0x0100U /**< Auto CMD Error */
#define XSDPS_FE_INTR_ERR_ADMA_MASK	0x0200U /**< ADMA Error */
#define XSDPS_FE_INTR_ERR_TR_MASK	0x1000U /**< Target Response */
#define XSDPS_FE_INTR_VEND_SPF_ERR_MASK	0xE000U /**< Vendor Specific
							Error */

/* @} */

/** @name ADMA Error Status Register
 *
 * This register is read only register which contains
 * status information about ADMA errors.
 * Read Only
 * @{
 */
#define XSDPS_ADMA_ERR_MM_LEN_MASK	0x04U /**< ADMA Length Mismatch
							Error */
#define XSDPS_ADMA_ERR_STATE_MASK	0x03U /**< ADMA Error State */
#define XSDPS_ADMA_ERR_STATE_STOP_MASK	0x00U /**< ADMA Error State
							STOP */
#define XSDPS_ADMA_ERR_STATE_FDS_MASK	0x01U /**< ADMA Error State
							FDS */
#define XSDPS_ADMA_ERR_STATE_TFR_MASK	0x03U /**< ADMA Error State
							TFR */
/* @} */

/** @name Preset Values Register
 *
 * This register is read only register which contains
 * preset values for each of speed modes.
 * Read Only
 * @{
 */
#define XSDPS_PRE_VAL_SDCLK_FSEL_MASK	0x03FFU /**< SDCLK Frequency
							Select Value */
#define XSDPS_PRE_VAL_CLK_GEN_SEL_MASK	0x0400U /**< Clock Generator
							Mode Select */
#define XSDPS_PRE_VAL_DRV_STR_SEL_MASK	0xC000U /**< Driver Strength
							Select Value */

/* @} */

/** @name Slot Interrupt Status Register
 *
 * This register is read only register which contains
 * interrupt slot signal for each slot.
 * Read Only
 * @{
 */
#define XSDPS_SLOT_INTR_STS_INT_MASK	0x0007U /**< Interrupt Signal
							mask */

/* @} */

/** @name Host Controller Version Register
 *
 * This register is read only register which contains
 * Host Controller and Vendor Specific version.
 * Read Only
 * @{
 */
#define XSDPS_HC_VENDOR_VER		0xFF00U /**< Vendor
							Specification
							version mask */
#define XSDPS_HC_SPEC_VER_MASK		0x00FFU /**< Host
							Specification
							version mask */
#define XSDPS_HC_SPEC_V3		0x0002U
#define XSDPS_HC_SPEC_V2		0x0001U
#define XSDPS_HC_SPEC_V1		0x0000U

/** @name Block size mask for 512 bytes
 *
 * Block size mask for 512 bytes - This is the default block size.
 * @{
 */

#define XSDPS_BLK_SIZE_512_MASK	0x200U

/* @} */

/** @name Commands
 *
 * Constant definitions for commands and response related to SD
 * @{
 */

#define XSDPS_APP_CMD_PREFIX	 0x8000U
#define CMD0	 0x0000U
#define CMD1	 0x0100U
#define CMD2	 0x0200U
#define CMD3	 0x0300U
#define CMD4	 0x0400U
#define CMD5	 0x0500U
#define CMD6	 0x0600U
#define ACMD6	(XSDPS_APP_CMD_PREFIX + 0x0600U)
#define CMD7	 0x0700U
#define CMD8	 0x0800U
#define CMD9	 0x0900U
#define CMD10	 0x0A00U
#define CMD11	 0x0B00U
#define CMD12	 0x0C00U
#define ACMD13	 (XSDPS_APP_CMD_PREFIX + 0x0D00U)
#define CMD16	 0x1000U
#define CMD17	 0x1100U
#define CMD18	 0x1200U
#define CMD19	 0x1300U
#define CMD21	 0x1500U
#define CMD23	 0x1700U
#define ACMD23	 (XSDPS_APP_CMD_PREFIX + 0x1700U)
#define CMD24	 0x1800U
#define CMD25	 0x1900U
#define CMD41	 0x2900U
#define ACMD41	 (XSDPS_APP_CMD_PREFIX + 0x2900U)
#define ACMD42	 (XSDPS_APP_CMD_PREFIX + 0x2A00U)
#define ACMD51	 (XSDPS_APP_CMD_PREFIX + 0x3300U)
#define CMD52	 0x3400U
#define CMD55	 0x3700U
#define CMD58	 0x3A00U

#if 0
#define RESP_NONE	(u32)XSDPS_CMD_RESP_NONE_MASK
#define RESP_R1		(u32)XSDPS_CMD_RESP_L48_MASK | (u32)XSDPS_CMD_CRC_CHK_EN_MASK | \
			(u32)XSDPS_CMD_INX_CHK_EN_MASK

#define RESP_R1B	(u32)XSDPS_CMD_RESP_L48_BSY_CHK_MASK | \
			(u32)XSDPS_CMD_CRC_CHK_EN_MASK | (u32)XSDPS_CMD_INX_CHK_EN_MASK

#define RESP_R2		(u32)XSDPS_CMD_RESP_L136_MASK | (u32)XSDPS_CMD_CRC_CHK_EN_MASK
#define RESP_R3		(u32)XSDPS_CMD_RESP_L48_MASK

#define RESP_R6		(u32)XSDPS_CMD_RESP_L48_BSY_CHK_MASK | \
			(u32)XSDPS_CMD_CRC_CHK_EN_MASK | (u32)XSDPS_CMD_INX_CHK_EN_MASK
#else
#define XSDPS_RESP_NONE	(u32)XSDPS_CMD_RESP_NONE_MASK
#define XSDPS_RESP_R1		(u32)XSDPS_CMD_RESP_L48_MASK | (u32)XSDPS_CMD_CRC_CHK_EN_MASK | \
			(u32)XSDPS_CMD_INX_CHK_EN_MASK

#define XSDPS_RESP_R1B	(u32)XSDPS_CMD_RESP_L48_BSY_CHK_MASK | \
			(u32)XSDPS_CMD_CRC_CHK_EN_MASK | (u32)XSDPS_CMD_INX_CHK_EN_MASK

#define XSDPS_RESP_R2		(u32)XSDPS_CMD_RESP_L136_MASK | (u32)XSDPS_CMD_CRC_CHK_EN_MASK
#define XSDPS_RESP_R3		(u32)XSDPS_CMD_RESP_L48_MASK

#define XSDPS_RESP_R6		(u32)XSDPS_CMD_RESP_L48_BSY_CHK_MASK | \
			(u32)XSDPS_CMD_CRC_CHK_EN_MASK | (u32)XSDPS_CMD_INX_CHK_EN_MASK
#endif

/* @} */

/* Card Interface Conditions Definitions */
#define XSDPS_CIC_CHK_PATTERN	0xAAU
#define XSDPS_CIC_VOLT_MASK	(0xFU<<8)
#define XSDPS_CIC_VOLT_2V7_3V6	(1U<<8)
#define XSDPS_CIC_VOLT_LOW	(1U<<9)

/* Operation Conditions Register Definitions */
#define XSDPS_OCR_PWRUP_STS	(1U<<31)
#define XSDPS_OCR_CC_STS	(1U<<30)
#define XSDPS_OCR_S18		(1U<<24)
#define XSDPS_OCR_3V5_3V6	(1U<<23)
#define XSDPS_OCR_3V4_3V5	(1U<<22)
#define XSDPS_OCR_3V3_3V4	(1U<<21)
#define XSDPS_OCR_3V2_3V3	(1U<<20)
#define XSDPS_OCR_3V1_3V2	(1U<<19)
#define XSDPS_OCR_3V0_3V1	(1U<<18)
#define XSDPS_OCR_2V9_3V0	(1U<<17)
#define XSDPS_OCR_2V8_2V9	(1U<<16)
#define XSDPS_OCR_2V7_2V8	(1U<<15)
#define XSDPS_OCR_1V7_1V95	(1U<<7)
#define XSDPS_OCR_HIGH_VOL	0x00FF8000U
#define XSDPS_OCR_LOW_VOL	0x00000080U

/* SD Card Configuration Register Definitions */
#define XSDPS_SCR_REG_LEN		8U
#define XSDPS_SCR_STRUCT_MASK		(0xFU<<28)
#define XSDPS_SCR_SPEC_MASK		(0xFU<<24)
#define XSDPS_SCR_SPEC_1V0		0U
#define XSDPS_SCR_SPEC_1V1		(1U<<24)
#define XSDPS_SCR_SPEC_2V0_3V0		(2U<<24)
#define XSDPS_SCR_MEM_VAL_AF_ERASE	(1U<<23)
#define XSDPS_SCR_SEC_SUPP_MASK		(7U<<20)
#define XSDPS_SCR_SEC_SUPP_NONE		0U
#define XSDPS_SCR_SEC_SUPP_1V1		(2U<<20)
#define XSDPS_SCR_SEC_SUPP_2V0		(3U<<20)
#define XSDPS_SCR_SEC_SUPP_3V0		(4U<<20)
#define XSDPS_SCR_BUS_WIDTH_MASK	(0xFU<<16)
#define XSDPS_SCR_BUS_WIDTH_1		(1U<<16)
#define XSDPS_SCR_BUS_WIDTH_4		(4U<<16)
#define XSDPS_SCR_SPEC3_MASK		(1U<<12)
#define XSDPS_SCR_SPEC3_2V0		0U
#define XSDPS_SCR_SPEC3_3V0		(1U<<12)
#define XSDPS_SCR_CMD_SUPP_MASK		0x3U
#define XSDPS_SCR_CMD23_SUPP		(1U<<1)
#define XSDPS_SCR_CMD20_SUPP		(1U<<0)

/* Card Status Register Definitions */
#define XSDPS_CD_STS_OUT_OF_RANGE	(1U<<31)
#define XSDPS_CD_STS_ADDR_ERR		(1U<<30)
#define XSDPS_CD_STS_BLK_LEN_ERR	(1U<<29)
#define XSDPS_CD_STS_ER_SEQ_ERR		(1U<<28)
#define XSDPS_CD_STS_ER_PRM_ERR		(1U<<27)
#define XSDPS_CD_STS_WP_VIO		(1U<<26)
#define XSDPS_CD_STS_IS_LOCKED		(1U<<25)
#define XSDPS_CD_STS_LOCK_UNLOCK_FAIL	(1U<<24)
#define XSDPS_CD_STS_CMD_CRC_ERR	(1U<<23)
#define XSDPS_CD_STS_ILGL_CMD		(1U<<22)
#define XSDPS_CD_STS_CARD_ECC_FAIL	(1U<<21)
#define XSDPS_CD_STS_CC_ERR		(1U<<20)
#define XSDPS_CD_STS_ERR		(1U<<19)
#define XSDPS_CD_STS_CSD_OVRWR		(1U<<16)
#define XSDPS_CD_STS_WP_ER_SKIP		(1U<<15)
#define XSDPS_CD_STS_CARD_ECC_DIS	(1U<<14)
#define XSDPS_CD_STS_ER_RST		(1U<<13)
#define XSDPS_CD_STS_CUR_STATE		(0xFU<<9)
#define XSDPS_CD_STS_RDY_FOR_DATA	(1U<<8)
#define XSDPS_CD_STS_APP_CMD		(1U<<5)
#define XSDPS_CD_STS_AKE_SEQ_ERR	(1U<<2)

/* Switch Function Definitions CMD6 */
#define XSDPS_SWITCH_SD_RESP_LEN	64U

#define XSDPS_SWITCH_FUNC_SWITCH	(1U<<31)
#define XSDPS_SWITCH_FUNC_CHECK		0U

#define XSDPS_MODE_FUNC_GRP1		1U
#define XSDPS_MODE_FUNC_GRP2		2U
#define XSDPS_MODE_FUNC_GRP3		3U
#define XSDPS_MODE_FUNC_GRP4		4U
#define XSDPS_MODE_FUNC_GRP5		5U
#define XSDPS_MODE_FUNC_GRP6		6U

#define XSDPS_FUNC_GRP_DEF_VAL		0xFU
#define XSDPS_FUNC_ALL_GRP_DEF_VAL	0xFFFFFFU

#define XSDPS_ACC_MODE_DEF_SDR12	0U
#define XSDPS_ACC_MODE_HS_SDR25		1U
#define XSDPS_ACC_MODE_SDR50		2U
#define XSDPS_ACC_MODE_SDR104		3U
#define XSDPS_ACC_MODE_DDR50		4U

#define XSDPS_CMD_SYS_ARG_SHIFT		4U
#define XSDPS_CMD_SYS_DEF		0U
#define XSDPS_CMD_SYS_eC		1U
#define XSDPS_CMD_SYS_OTP		3U
#define XSDPS_CMD_SYS_ASSD		4U
#define XSDPS_CMD_SYS_VEND		5U

#define XSDPS_DRV_TYPE_ARG_SHIFT	8U
#define XSDPS_DRV_TYPE_B		0U
#define XSDPS_DRV_TYPE_A		1U
#define XSDPS_DRV_TYPE_C		2U
#define XSDPS_DRV_TYPE_D		3U

#define XSDPS_CUR_LIM_ARG_SHIFT		12U
#define XSDPS_CUR_LIM_200		0U
#define XSDPS_CUR_LIM_400		1U
#define XSDPS_CUR_LIM_600		2U
#define XSDPS_CUR_LIM_800		3U

#define CSD_SPEC_VER_MASK		0x3C0000U
#define READ_BLK_LEN_MASK		0x00000F00U
#define C_SIZE_MULT_MASK		0x00000380U
#define C_SIZE_LOWER_MASK		0xFFC00000U
#define C_SIZE_UPPER_MASK		0x00000003U
#define CSD_STRUCT_MASK			0x00C00000U
#define CSD_V2_C_SIZE_MASK		0x3FFFFF00U

/* EXT_CSD field definitions */
#define XSDPS_EXT_CSD_SIZE		512U

#define EXT_CSD_WR_REL_PARAM_EN		(1U<<2)

#define EXT_CSD_BOOT_WP_B_PWR_WP_DIS    (0x40U)
#define EXT_CSD_BOOT_WP_B_PERM_WP_DIS   (0x10U)
#define EXT_CSD_BOOT_WP_B_PERM_WP_EN    (0x04U)
#define EXT_CSD_BOOT_WP_B_PWR_WP_EN     (0x01U)

#define EXT_CSD_PART_CONFIG_ACC_MASK    (0x7U)
#define EXT_CSD_PART_CONFIG_ACC_BOOT0   (0x1U)
#define EXT_CSD_PART_CONFIG_ACC_BOOT1   (0x2U)
#define EXT_CSD_PART_CONFIG_ACC_RPMB    (0x3U)
#define EXT_CSD_PART_CONFIG_ACC_GP0     (0x4U)
#define EXT_CSD_PART_CONFIG_BYTE		179U
#define XSDPS_MMC_PART_CFG_0_ARG		((XSDPS_EXT_CSD_WRITE_BYTE << 24U) \
					 | (EXT_CSD_PART_CONFIG_BYTE << 16U) \
					 | ((0U) << 8U))

#define XSDPS_MMC_PART_CFG_1_ARG		((XSDPS_EXT_CSD_WRITE_BYTE << 24U) \
					 | (EXT_CSD_PART_CONFIG_BYTE << 16U) \
					 | (EXT_CSD_PART_CONFIG_ACC_BOOT0 << 8U))

#define XSDPS_MMC_PART_CFG_2_ARG		((XSDPS_EXT_CSD_WRITE_BYTE << 24U) \
					 | (EXT_CSD_PART_CONFIG_BYTE << 16U) \
					 | (EXT_CSD_PART_CONFIG_ACC_BOOT1 << 8U))

#define EXT_CSD_PART_SUPPORT_PART_EN    (0x1U)

#define EXT_CSD_CMD_SET_NORMAL          (1U<<0)
#define EXT_CSD_CMD_SET_SECURE          (1U<<1)
#define EXT_CSD_CMD_SET_CPSECURE        (1U<<2)

#define EXT_CSD_CARD_TYPE_26    	(1U<<0)  /* Card can run at 26MHz */
#define EXT_CSD_CARD_TYPE_52    	(1U<<1)  /* Card can run at 52MHz */
#define EXT_CSD_CARD_TYPE_MASK  	0x3FU    /* Mask out reserved bits */
#define EXT_CSD_CARD_TYPE_DDR_1_8V	(1U<<2)   /* Card can run at 52MHz */
                                             /* DDR mode @1.8V or 3V I/O */
#define EXT_CSD_CARD_TYPE_DDR_1_2V	(1U<<3)   /* Card can run at 52MHz */
                                             /* DDR mode @1.2V I/O */
#define EXT_CSD_CARD_TYPE_DDR_52	(EXT_CSD_CARD_TYPE_DDR_1_8V  \
                                        | EXT_CSD_CARD_TYPE_DDR_1_2V)
#define EXT_CSD_CARD_TYPE_SDR_1_8V      (1U<<4)  /* Card can run at 200MHz */
#define EXT_CSD_CARD_TYPE_SDR_1_2V      (1U<<5)  /* Card can run at 200MHz */
                                                /* SDR mode @1.2V I/O */
#define EXT_CSD_BUS_WIDTH_BYTE			183U
#define EXT_CSD_BUS_WIDTH_1_BIT			0U	/* Card is in 1 bit mode */
#define EXT_CSD_BUS_WIDTH_4_BIT			1U	/* Card is in 4 bit mode */
#define EXT_CSD_BUS_WIDTH_8_BIT			2U	/* Card is in 8 bit mode */
#define EXT_CSD_BUS_WIDTH_DDR_4_BIT		5U	/* Card is in 4 bit DDR mode */
#define EXT_CSD_BUS_WIDTH_DDR_8_BIT		6U	/* Card is in 8 bit DDR mode */

#define EXT_CSD_HS_TIMING_BYTE		185U
#define EXT_CSD_HS_TIMING_DEF		0U
#define EXT_CSD_HS_TIMING_HIGH		1U	/* Card is in high speed mode */
#define EXT_CSD_HS_TIMING_HS200		2U	/* Card is in HS200 mode */

#define EXT_CSD_RST_N_FUN_BYTE		162U
#define EXT_CSD_RST_N_FUN_TEMP_DIS	0U	/* RST_n signal is temporarily disabled */
#define EXT_CSD_RST_N_FUN_PERM_EN	1U	/* RST_n signal is permanently enabled */
#define EXT_CSD_RST_N_FUN_PERM_DIS	2U	/* RST_n signal is permanently disabled */

#define XSDPS_EXT_CSD_CMD_SET		0U
#define XSDPS_EXT_CSD_SET_BITS		1U
#define XSDPS_EXT_CSD_CLR_BITS		2U
#define XSDPS_EXT_CSD_WRITE_BYTE	3U

#define XSDPS_MMC_DEF_SPEED_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					| ((u32)EXT_CSD_HS_TIMING_BYTE << 16) \
					| ((u32)EXT_CSD_HS_TIMING_DEF << 8))

#define XSDPS_MMC_HIGH_SPEED_ARG	(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_HS_TIMING_BYTE << 16) \
					 | ((u32)EXT_CSD_HS_TIMING_HIGH << 8))

#define XSDPS_MMC_HS200_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_HS_TIMING_BYTE << 16) \
					 | ((u32)EXT_CSD_HS_TIMING_HS200 << 8))

#define XSDPS_MMC_1_BIT_BUS_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_BUS_WIDTH_BYTE << 16) \
					 | ((u32)EXT_CSD_BUS_WITH_1_BIT << 8))

#define XSDPS_MMC_4_BIT_BUS_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_BUS_WIDTH_BYTE << 16) \
					 | ((u32)EXT_CSD_BUS_WIDTH_4_BIT << 8))

#define XSDPS_MMC_8_BIT_BUS_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_BUS_WIDTH_BYTE << 16) \
					 | ((u32)EXT_CSD_BUS_WIDTH_8_BIT << 8))

#define XSDPS_MMC_DDR_4_BIT_BUS_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_BUS_WIDTH_BYTE << 16) \
					 | ((u32)EXT_CSD_BUS_WIDTH_DDR_4_BIT << 8))

#define XSDPS_MMC_DDR_8_BIT_BUS_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_BUS_WIDTH_BYTE << 16) \
					 | ((u32)EXT_CSD_BUS_WIDTH_DDR_8_BIT << 8))

#define XSDPS_MMC_RST_FUN_EN_ARG		(((u32)XSDPS_EXT_CSD_WRITE_BYTE << 24) \
					 | ((u32)EXT_CSD_RST_N_FUN_BYTE << 16) \
					 | ((u32)EXT_CSD_RST_N_FUN_PERM_EN << 8))

#define XSDPS_MMC_DELAY_FOR_SWITCH	1000U

/* @} */

/* @400KHz, in usec */
#define XSDPS_74CLK_DELAY	2960U
#define XSDPS_100CLK_DELAY	4000U
#define XSDPS_INIT_DELAY	10000U

#define XSDPS_DEF_VOLT_LVL	XSDPS_PC_BUS_VSEL_3V0_MASK
#define XSDPS_CARD_DEF_ADDR	0x1234U

#define XSDPS_CARD_SD		1U
#define XSDPS_CARD_MMC		2U
#define XSDPS_CARD_SDIO		3U
#define XSDPS_CARD_SDCOMBO	4U
#define XSDPS_CHIP_EMMC		5U


/** @name ADMA2 Descriptor related definitions
 *
 * ADMA2 Descriptor related definitions
 * @{
 */

#define XSDPS_DESC_MAX_LENGTH 65536U

#define XSDPS_DESC_VALID     	(0x1U << 0)
#define XSDPS_DESC_END       	(0x1U << 1)
#define XSDPS_DESC_INT       	(0x1U << 2)
#define XSDPS_DESC_TRAN  	(0x2U << 4)

/* @} */

/* For changing clock frequencies */
#define XSDPS_CLK_400_KHZ		400000U		/**< 400 KHZ */
#define XSDPS_CLK_50_MHZ		50000000U	/**< 50 MHZ */
#define XSDPS_CLK_52_MHZ		52000000U	/**< 52 MHZ */
#define XSDPS_SD_VER_1_0		0x1U		/**< SD ver 1 */
#define XSDPS_SD_VER_2_0		0x2U		/**< SD ver 2 */
#define XSDPS_SCR_BLKCNT	1U
#define XSDPS_SCR_BLKSIZE	8U
#define XSDPS_1_BIT_WIDTH	0x1U
#define XSDPS_4_BIT_WIDTH	0x2U
#define XSDPS_8_BIT_WIDTH	0x3U
#define XSDPS_UHS_SPEED_MODE_SDR12	0x0U
#define XSDPS_UHS_SPEED_MODE_SDR25	0x1U
#define XSDPS_UHS_SPEED_MODE_SDR50	0x2U
#define XSDPS_UHS_SPEED_MODE_SDR104	0x3U
#define XSDPS_UHS_SPEED_MODE_DDR50	0x4U
#define XSDPS_HIGH_SPEED_MODE		0x5U
#define XSDPS_DEFAULT_SPEED_MODE	0x6U
#define XSDPS_HS200_MODE			0x7U
#define XSDPS_DDR52_MODE			0x4U
#define XSDPS_SWITCH_CMD_BLKCNT		1U
#define XSDPS_SWITCH_CMD_BLKSIZE	64U
#define XSDPS_SWITCH_CMD_HS_GET		0x00FFFFF0U
#define XSDPS_SWITCH_CMD_HS_SET		0x80FFFFF1U
#define XSDPS_SWITCH_CMD_SDR12_SET		0x80FFFFF0U
#define XSDPS_SWITCH_CMD_SDR25_SET		0x80FFFFF1U
#define XSDPS_SWITCH_CMD_SDR50_SET		0x80FFFFF2U
#define XSDPS_SWITCH_CMD_SDR104_SET		0x80FFFFF3U
#define XSDPS_SWITCH_CMD_DDR50_SET		0x80FFFFF4U
#define XSDPS_EXT_CSD_CMD_BLKCNT	1U
#define XSDPS_EXT_CSD_CMD_BLKSIZE	512U
#define XSDPS_TUNING_CMD_BLKCNT		1U
#define XSDPS_TUNING_CMD_BLKSIZE	64U
#define XSDPS_SD_STATUS_BLKCNT		1U
#define XSDPS_SD_STATUS_BLKSIZE		64U

#define XSDPS_HIGH_SPEED_MAX_CLK	50000000U
#define XSDPS_UHS_SDR104_MAX_CLK	208000000U
#define XSDPS_UHS_SDR50_MAX_CLK		100000000U
#define XSDPS_UHS_DDR50_MAX_CLK		50000000U
#define XSDPS_UHS_SDR25_MAX_CLK		50000000U
#define XSDPS_UHS_SDR12_MAX_CLK		25000000U

#define SD_DRIVER_TYPE_B	0x01U
#define SD_DRIVER_TYPE_A	0x02U
#define SD_DRIVER_TYPE_C	0x04U
#define SD_DRIVER_TYPE_D	0x08U
#define SD_SET_CURRENT_LIMIT_200	0U
#define SD_SET_CURRENT_LIMIT_400	1U
#define SD_SET_CURRENT_LIMIT_600	2U
#define SD_SET_CURRENT_LIMIT_800	3U

#define SD_MAX_CURRENT_200	(1U << SD_SET_CURRENT_LIMIT_200)
#define SD_MAX_CURRENT_400	(1U << SD_SET_CURRENT_LIMIT_400)
#define SD_MAX_CURRENT_600	(1U << SD_SET_CURRENT_LIMIT_600)
#define SD_MAX_CURRENT_800	(1U << SD_SET_CURRENT_LIMIT_800)

#define XSDPS_SD_SDR12_MAX_CLK	25000000U
#define XSDPS_SD_SDR25_MAX_CLK	50000000U
#define XSDPS_SD_SDR50_MAX_CLK	100000000U
#define XSDPS_SD_DDR50_MAX_CLK	50000000U
#define XSDPS_SD_SDR104_MAX_CLK	208000000U
/*
 * XSDPS_SD_INPUT_MAX_CLK is set to 175000000 in order to keep it smaller
 * than the clock value coming from the core. This value is kept to safely
 * switch to SDR104 mode if the SD card supports it.
 */
#define XSDPS_SD_INPUT_MAX_CLK	175000000U

#define XSDPS_MMC_HS200_MAX_CLK	200000000U
#define XSDPS_MMC_HSD_MAX_CLK	52000000U
#define XSDPS_MMC_DDR_MAX_CLK	52000000U

#define XSDPS_CARD_STATE_IDLE		0U
#define XSDPS_CARD_STATE_RDY		1U
#define XSDPS_CARD_STATE_IDEN		2U
#define XSDPS_CARD_STATE_STBY		3U
#define XSDPS_CARD_STATE_TRAN		4U
#define XSDPS_CARD_STATE_DATA		5U
#define XSDPS_CARD_STATE_RCV		6U
#define XSDPS_CARD_STATE_PROG		7U
#define XSDPS_CARD_STATE_DIS		8U
#define XSDPS_CARD_STATE_BTST		9U
#define XSDPS_CARD_STATE_SLP		10U

#define XSDPS_SLOT_REM			0U
#define XSDPS_SLOT_EMB			1U

#define XSDPS_WIDTH_8		8U
#define XSDPS_WIDTH_4		4U


#ifdef versal
#define SD_ITAPDLY_SEL_MASK			0x000000FFU
#define SD_OTAPDLY_SEL_MASK			0x0000003FU
#define SD_ITAPDLY					0x0000F0F8U
#define SD_OTAPDLY					0x0000F0FCU
#define SD0_DLL_CTRL 				0x00000448U
#define SD1_DLL_CTRL 				0x000004C8U
#define SD_DLL_RST					0x00000004U
#define SD_ITAPCHGWIN				0x00000200U
#define SD_ITAPDLYENA				0x00000100U
#define SD_OTAPDLYENA				0x00000040U
#define SD_OTAPDLYSEL_HS200_B0		0x00000002U
#define SD_OTAPDLYSEL_HS200_B2		0x00000002U
#define SD_ITAPDLYSEL_SD50			0x0000000EU
#define SD_OTAPDLYSEL_SD50			0x00000003U
#define SD_ITAPDLYSEL_SD_DDR50		0x00000036U
#define SD_ITAPDLYSEL_EMMC_DDR50	0x0000001EU
#define SD_OTAPDLYSEL_SD_DDR50		0x00000003U
#define SD_OTAPDLYSEL_EMMC_DDR50	0x00000005U
#define SD_ITAPDLYSEL_HSD			0x0000002CU
#define SD_OTAPDLYSEL_SD_HSD		0x00000004U
#define SD_OTAPDLYSEL_EMMC_HSD		0x00000005U
#else
#define SD0_ITAPDLY_SEL_MASK		0x000000FFU
#define SD0_OTAPDLY_SEL_MASK		0x0000003FU
#define SD1_ITAPDLY_SEL_MASK		0x00FF0000U
#define SD1_OTAPDLY_SEL_MASK		0x003F0000U
#define SD_DLL_CTRL 				0x00000358U
#define SD_ITAPDLY					0x00000314U
#define SD_OTAPDLY					0x00000318U
#define SD0_DLL_RST					0x00000004U
#define SD1_DLL_RST					0x00040000U
#define SD0_ITAPCHGWIN				0x00000200U
#define SD0_ITAPDLYENA				0x00000100U
#define SD0_OTAPDLYENA				0x00000040U
#define SD1_ITAPCHGWIN				0x02000000U
#define SD1_ITAPDLYENA				0x01000000U
#define SD1_OTAPDLYENA				0x00400000U
#define SD_OTAPDLYSEL_HS200_B0		0x00000003U
#define SD_OTAPDLYSEL_HS200_B2		0x00000002U
#define SD_ITAPDLYSEL_SD50			0x00000014U
#define SD_OTAPDLYSEL_SD50			0x00000003U
#define SD_ITAPDLYSEL_SD_DDR50		0x0000003DU
#define SD_ITAPDLYSEL_EMMC_DDR50	0x00000012U
#define SD_OTAPDLYSEL_SD_DDR50		0x00000004U
#define SD_OTAPDLYSEL_EMMC_DDR50	0x00000006U
#define SD_ITAPDLYSEL_HSD			0x00000015U
#define SD_OTAPDLYSEL_SD_HSD		0x00000005U
#define SD_OTAPDLYSEL_EMMC_HSD		0x00000006U
#endif

#ifdef __MICROBLAZE__
#define XPS_SYS_CTRL_BASEADDR	0xFF180000U
#endif

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define XSdPs_In64 Xil_In64
#define XSdPs_Out64 Xil_Out64

#define XSdPs_In32 Xil_In32
#define XSdPs_Out32 Xil_Out32

#define XSdPs_In16 Xil_In16
#define XSdPs_Out16 Xil_Out16

#define XSdPs_In8 Xil_In8
#define XSdPs_Out8 Xil_Out8

/****************************************************************************/
/**
* Read a register.
*
* @param	InstancePtr is the pointer to the sdps instance.
* @param	RegOffset contains the offset from the 1st register of the
*		device to the target register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		u32 XSdPs_ReadReg(XSdPs *InstancePtr. s32 RegOffset)
*
******************************************************************************/
#define XSdPs_ReadReg64(InstancePtr, RegOffset) \
	XSdPs_In64((InstancePtr->Config.BaseAddress) + RegOffset)

/***************************************************************************/
/**
* Write to a register.
*
* @param	InstancePtr is the pointer to the sdps instance.
* @param	RegOffset contains the offset from the 1st register of the
*		device to target register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note		C-Style signature:
*		void XSdPs_WriteReg(XSdPs *InstancePtr, s32 RegOffset,
*		u64 RegisterValue)
*
******************************************************************************/
#define XSdPs_WriteReg64(InstancePtr, RegOffset, RegisterValue) \
	XSdPs_Out64((InstancePtr->Config.BaseAddress) + (RegOffset), \
		(RegisterValue))

/****************************************************************************/
/**
* Read a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to the target register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		u32 XSdPs_ReadReg(u32 BaseAddress. int RegOffset)
*
******************************************************************************/
#define XSdPs_ReadReg(BaseAddress, RegOffset) \
	XSdPs_In32((BaseAddress) + (RegOffset))

/***************************************************************************/
/**
* Write to a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to target register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note		C-Style signature:
*		void XSdPs_WriteReg(u32 BaseAddress, int RegOffset,
*		u32 RegisterValue)
*
******************************************************************************/
#define XSdPs_WriteReg(BaseAddress, RegOffset, RegisterValue) \
	XSdPs_Out32((BaseAddress) + (RegOffset), (RegisterValue))

/****************************************************************************/
/**
* Read a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to the target register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		u16 XSdPs_ReadReg(u32 BaseAddress. int RegOffset)
*
******************************************************************************/
static INLINE u16 XSdPs_ReadReg16(u32 BaseAddress, u8 RegOffset)
{
#if defined (__MICROBLAZE__)
	u32 Reg;
	BaseAddress += RegOffset & 0xFC;
	Reg = XSdPs_In32(BaseAddress);
	Reg >>= ((RegOffset & 0x3)*8);
	return (u16)Reg;
#else
	return XSdPs_In16((BaseAddress) + (RegOffset));
#endif
}

/***************************************************************************/
/**
* Write to a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to target register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note		C-Style signature:
*		void XSdPs_WriteReg(u32 BaseAddress, int RegOffset,
*		u16 RegisterValue)
*
******************************************************************************/

static INLINE void XSdPs_WriteReg16(u32 BaseAddress, u8 RegOffset, u16 RegisterValue)
{
#if defined (__MICROBLAZE__)
	u32 Reg;
	BaseAddress += RegOffset & 0xFC;
	Reg = XSdPs_In32(BaseAddress);
	Reg &= ~(0xFFFF<<((RegOffset & 0x3)*8));
	Reg |= RegisterValue <<((RegOffset & 0x3)*8);
	XSdPs_Out32(BaseAddress, Reg);
#else
	XSdPs_Out16((BaseAddress) + (RegOffset), (RegisterValue));
#endif
}

/****************************************************************************/
/**
* Read a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to the target register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		u8 XSdPs_ReadReg(u32 BaseAddress. int RegOffset)
*
******************************************************************************/
static INLINE u8 XSdPs_ReadReg8(u32 BaseAddress, u8 RegOffset)
{
#if defined (__MICROBLAZE__)
	u32 Reg;
	BaseAddress += RegOffset & 0xFC;
	Reg = XSdPs_In32(BaseAddress);
	Reg >>= ((RegOffset & 0x3)*8);
	return (u8)Reg;
#else
	return XSdPs_In8((BaseAddress) + (RegOffset));
#endif
}
/***************************************************************************/
/**
* Write to a register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to target register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note		C-Style signature:
*		void XSdPs_WriteReg(u32 BaseAddress, int RegOffset,
*		u8 RegisterValue)
*
******************************************************************************/
static INLINE void XSdPs_WriteReg8(u32 BaseAddress, u8 RegOffset, u8 RegisterValue)
{
#if defined (__MICROBLAZE__)
	u32 Reg;
	BaseAddress += RegOffset & 0xFC;
	Reg = XSdPs_In32(BaseAddress);
	Reg &= ~(0xFF<<((RegOffset & 0x3)*8));
	Reg |= RegisterValue <<((RegOffset & 0x3)*8);
	XSdPs_Out32(BaseAddress, Reg);
#else
	XSdPs_Out8((BaseAddress) + (RegOffset), (RegisterValue));
#endif
}
/***************************************************************************/
/**
* Macro to get present status register
*
* @param	BaseAddress contains the base address of the device.
*
* @return	None.
*
* @note		C-Style signature:
*		void XSdPs_WriteReg(u32 BaseAddress, int RegOffset,
*		u8 RegisterValue)
*
******************************************************************************/
#define XSdPs_GetPresentStatusReg(BaseAddress) \
		XSdPs_In32((BaseAddress) + (XSDPS_PRES_STATE_OFFSET))

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif /* SD_HW_H_ */
/** @} */
