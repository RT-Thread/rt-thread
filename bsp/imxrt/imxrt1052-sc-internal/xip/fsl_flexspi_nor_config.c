/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi_nor_config.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xip_board"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.conf")))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.conf"
#endif

const flexspi_nor_config_t qspiflash_config = {
		.memConfig =
		{
			.tag = FLEXSPI_CFG_BLK_TAG,
			.version = FLEXSPI_CFG_BLK_VERSION,
			.readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackInternally,
			.csHoldTime = 3u,
			.csSetupTime = 3u,

			.deviceModeCfgEnable = true,
			.deviceModeType = 1, //Quad enable command
			.deviceModeSeq.seqNum = 1,
			.deviceModeSeq.seqId = 4,
			.deviceModeArg = 0x000200,  //Set QE
			.deviceType = kFlexSpiDeviceType_SerialNOR,//kFlexSpiDeviceType_SerialNOR,

			.sflashPadType = kSerialFlash_4Pads,
			.serialClkFreq = kFlexSpiSerialClk_166MHz,   // 80Mhz for winbond, 100Mhz for GD, 133Mhz for ISSI
			.sflashA1Size = 32u * 1024u * 1024u,
			.dataValidTime = {16u, 16u},

			.lookupTable =
				{
					//Quad Input/Output read sequence
					[0] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
					[1] = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x04),
					[2] = FLEXSPI_LUT_SEQ(0, 0, 0, 0, 0, 0),

					//Read Status
					[1*4] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x05, READ_SDR, FLEXSPI_1PAD, 0x04),

					//Write Enable
					[3*4] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x06, STOP, FLEXSPI_1PAD, 0),

					//Write Status
					[4*4] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x01, WRITE_SDR, FLEXSPI_1PAD, 0x04),
				},
		},
    .pageSize           = 512u,
    .sectorSize         = 256u * 1024u,
    .blockSize          = 256u * 1024u,
    .isUniformBlockSize = true,
};
#endif /* XIP_BOOT_HEADER_ENABLE */
