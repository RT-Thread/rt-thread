/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_VEP_TAB__
#define __DE_VEP_TAB__

extern int y2r[192];
extern int r2y[128];
extern int y2y[64];
extern int r2r[32];
extern int bypass_csc[12];
extern unsigned int sin_cos[128];
extern int fcc_range_gain[6];
extern unsigned char ce_bypass_lut[256];
extern unsigned char ce_constant_lut[256];

#endif
