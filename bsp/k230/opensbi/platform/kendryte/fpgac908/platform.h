/*
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _C908_PLATFORM_H_
#define _C908_PLATFORM_H_

#define C908_HART_COUNT   1

#define SBI_THEAD_FEATURES	\
	 (SBI_PLATFORM_HAS_MFAULTS_DELEGATION)

#define CSR_MCOR         0x7c2
#define CSR_MHCR         0x7c1
#define CSR_MCCR2        0x7c3
#define CSR_MHINT        0x7c5
#define CSR_MXSTATUS     0x7c0
#define CSR_PLIC_BASE    0xfc1
#define CSR_MRMR         0x7c6
#define CSR_MRVBR        0x7c7

#define C908_PLIC_CLINT_OFFSET     0x04000000  /* 64M */
#define C908_PLIC_DELEG_OFFSET     0x001ffffc
#define C908_PLIC_DELEG_ENABLE     0x1

#endif /* _C908_PLATFORM_H_ */
