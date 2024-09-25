/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_VERSION_H__
#define __SBI_VERSION_H__

#define OPENSBI_VERSION_MAJOR 0
#define OPENSBI_VERSION_MINOR 9

/**
 * OpenSBI 32-bit version with:
 * 1. upper 16-bits as major number
 * 2. lower 16-bits as minor number
 */
#define OPENSBI_VERSION ((OPENSBI_VERSION_MAJOR << 16) | \
			 (OPENSBI_VERSION_MINOR))

#endif
