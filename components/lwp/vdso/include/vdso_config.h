/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Limited
 */
#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

#define __VVAR_PAGES    2
#define PAGE_SHIFT     12
#define PAGE_SIZE      (1 << PAGE_SHIFT)

#define BIT(nr)			((1) << (nr))

#define VDSO_PATH "../usr/build/librtos_vdso.so"

#endif


