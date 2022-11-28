/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :       de_vep.h
 *
 *  Description :       display engine 2.0 vep basic function declaration
 *
 *  History     :       2014/04/24  iptang  v0.1  Initial version
 *
 ******************************************************************************/

#ifndef __DE_VEP_H__
#define __DE_VEP_H__

int de_fcc_init(unsigned int sel, unsigned int reg_base);
int de_fcc_update_regs(unsigned int sel);
int de_fcc_set_reg_base(unsigned int sel, unsigned int chno, void *base);
int de_fcc_csc_set(unsigned int sel, unsigned int chno, unsigned int en,
           unsigned int mode);

#endif
