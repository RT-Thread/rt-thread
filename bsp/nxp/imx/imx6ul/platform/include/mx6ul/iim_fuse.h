/*
 * Copyright (C) 2011-2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
*/

#ifndef __IIM_FUSE_H__
#define __IIM_FUSE_H__

#define IIM_STAT_OFF            0x00
#define IIM_STAT_BUSY           (1 << 7)
#define IIM_STAT_PRGD           (1 << 1)
#define IIM_STAT_SNSD           (1 << 0)
#define IIM_STATM_OFF           0x04
#define IIM_ERR_OFF             0x08
#define IIM_ERR_PRGE            (1 << 7)
#define IIM_ERR_WPE         (1 << 6)
#define IIM_ERR_OPE         (1 << 5)
#define IIM_ERR_RPE         (1 << 4)
#define IIM_ERR_WLRE        (1 << 3)
#define IIM_ERR_SNSE        (1 << 2)
#define IIM_ERR_PARITYE     (1 << 1)
#define IIM_EMASK_OFF           0x0C
#define IIM_FCTL_OFF            0x10
#define IIM_UA_OFF              0x14
#define IIM_LA_OFF              0x18
#define IIM_SDAT_OFF            0x1C
#define IIM_PREV_OFF            0x20
#define IIM_SREV_OFF            0x24
#define IIM_PREG_P_OFF          0x28
#define IIM_SCS0_OFF            0x2C
#define IIM_SCS1_P_OFF          0x30
#define IIM_SCS2_OFF            0x34
#define IIM_SCS3_P_OFF          0x38

//unsigned int sense_fuse(int bank, int row);
//int fuse_blow(int bank, int row, int bit);

#endif // __IIM_FUSE_H__
