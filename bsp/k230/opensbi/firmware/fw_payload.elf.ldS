/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
	#include "fw_base.ldS"

#ifdef FW_PAYLOAD_OFFSET
	. = FW_TEXT_START + FW_PAYLOAD_OFFSET;
#else
	. = ALIGN(FW_PAYLOAD_ALIGN);
#endif

	.payload :
	{
		PROVIDE(_payload_start = .);
		*(.payload)
		. = ALIGN(8);
		PROVIDE(_payload_end = .);
	}

	PROVIDE(_fw_reloc_end = .);
}
