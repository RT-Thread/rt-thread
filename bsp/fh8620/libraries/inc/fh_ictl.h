/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef FH_ICTL_H_
#define FH_ICTL_H_

#include "fh_def.h"

typedef struct {
	RwReg IRQ_EN_L;
	RwReg IRQ_EN_H;
	RwReg IRQ_MASK_L;
	RwReg IRQ_MASK_H;
	RwReg IRQ_FORCE_L;
	RwReg IRQ_FORCE_H;
	RwReg IRQ_RAWSTARUS_L;
	RwReg IRQ_RAWSTARUS_H;
	RwReg IRQ_STATUS_L;
	RwReg IRQ_STATUS_H;
	RwReg IRQ_MASKSTATUS_L;
	RwReg IRQ_MASKSTATUS_H;
	RwReg IRQ_FINALSTATUS_L;
	RwReg IRQ_FINALSTATUS_H;
	RwReg IRQ_VECTOR;
}fh_intc;



void ictl_close_all_isr(fh_intc *p);

void ictl_mask_isr(fh_intc *p,int irq);

void ictl_unmask_isr(fh_intc *p,int irq);

#endif
