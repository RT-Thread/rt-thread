/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/**
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :       de_scaler_table.h
 *
 *  Description :       display engine 2.0 vsu/gsu common fir table
 *                      information
 *
 *  History     :       2014/03/26  vito cheng  v0.1  Initial version
 *
 */
#ifndef __DE_SCALER_TABLE_H__
#define __DE_SCALER_TABLE_H__

#define GSU_ZOOM0_SIZE  1
#define GSU_ZOOM1_SIZE  8
#define GSU_ZOOM2_SIZE  4
#define GSU_ZOOM3_SIZE  1
#define GSU_ZOOM4_SIZE  1
#define GSU_ZOOM5_SIZE  1

#define VSU_ZOOM0_SIZE  1
#define VSU_ZOOM1_SIZE  8
#define VSU_ZOOM2_SIZE  4
#define VSU_ZOOM3_SIZE  1
#define VSU_ZOOM4_SIZE  1
#define VSU_ZOOM5_SIZE  1

extern unsigned int lan2coefftab16[256];
extern unsigned int lan3coefftab32_left[512];
extern unsigned int lan3coefftab32_right[512];
extern unsigned int lan2coefftab32[512];
extern unsigned int bicubic8coefftab32_left[512];
extern unsigned int bicubic8coefftab32_right[512];
extern unsigned int bicubic4coefftab32[512];

#endif
