/*
 * * Copyright (c) 2019 STMicrolectonics , Xilinx Inc. and Contributors. All rights reserved.
 * *
 * * SPDX-License-Identifier: BSD-3-Clause
 * */

/*
 * * @file      metal/errno.h
 * * @brief     error specific primitives for libmetal.
 * */

#ifndef __METAL_ERRNO__H__
#define __METAL_ERRNO__H__

#if defined (__CC_ARM)
# include <metal/compiler/mdk-arm/errno.h>
#elif defined (__ICCARM__)
# include <metal/compiler/iar/errno.h>
#else
#include <errno.h>
#endif

#endif /* __METAL_ERRNO__H__ */

