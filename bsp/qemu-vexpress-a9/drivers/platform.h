#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* SOC-relative definitions */
#include "realview.h"

/* the maximum entries of the exception table */
#define MAX_HANDLERS    NR_IRQS_PBA8

/* the basic constants needed by gic */
#define GIC_DIST_BASE   REALVIEW_GIC_DIST_BASE
#define GIC_CPU_BASE    REALVIEW_GIC_CPU_BASE
#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK  0x000003ff

#endif	// __PLATFORM_H__
