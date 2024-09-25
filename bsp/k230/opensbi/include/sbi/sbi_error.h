/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_ERROR_H__
#define __SBI_ERROR_H__

#include <sbi/sbi_ecall_interface.h>

/* clang-format off */

#define SBI_OK			0
#define SBI_EFAIL		SBI_ERR_FAILED
#define SBI_ENOTSUPP		SBI_ERR_NOT_SUPPORTED
#define SBI_EINVAL		SBI_ERR_INVALID_PARAM
#define SBI_EDENIED		SBI_ERR_DENIED
#define SBI_EINVALID_ADDR	SBI_ERR_INVALID_ADDRESS
#define SBI_EALREADY		SBI_ERR_ALREADY_AVAILABLE

#define SBI_ENODEV		-1000
#define SBI_ENOSYS		-1001
#define SBI_ETIMEDOUT		-1002
#define SBI_EIO			-1003
#define SBI_EILL		-1004
#define SBI_ENOSPC		-1005
#define SBI_ENOMEM		-1006
#define SBI_ETRAP		-1007
#define SBI_EUNKNOWN		-1008
#define SBI_ENOENT		-1009

/* clang-format on */

#endif
