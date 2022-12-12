#ifndef _PPC4xx_UIC_H_
#define _PPC4xx_UIC_H_

/*
 * Define the number of UIC's
 */
#define UIC_MAX     1
#define IRQ_MAX     UIC_MAX * 32

/* UIC0 dcr base address */
#define UIC0_DCR_BASE 0xc0

/*
 * UIC register
 */
#define UIC_SR  0x0         /* UIC status           */
#define UIC_ER  0x2         /* UIC enable           */
#define UIC_CR  0x3         /* UIC critical         */
#define UIC_PR  0x4         /* UIC polarity         */
#define UIC_TR  0x5         /* UIC triggering       */
#define UIC_MSR 0x6         /* UIC masked status        */
#define UIC_VR  0x7         /* UIC vector           */
#define UIC_VCR 0x8         /* UIC vector configuration */

#define uic0sr  (UIC0_DCR_BASE+0x0) /* UIC0 status          */
#define uic0er  (UIC0_DCR_BASE+0x2) /* UIC0 enable          */
#define uic0cr  (UIC0_DCR_BASE+0x3) /* UIC0 critical        */
#define uic0pr  (UIC0_DCR_BASE+0x4) /* UIC0 polarity        */
#define uic0tr  (UIC0_DCR_BASE+0x5) /* UIC0 triggering      */
#define uic0msr (UIC0_DCR_BASE+0x6) /* UIC0 masked status       */
#define uic0vr  (UIC0_DCR_BASE+0x7) /* UIC0 vector          */
#define uic0vcr (UIC0_DCR_BASE+0x8) /* UIC0 vector configuration    */

/* The following is for compatibility with 405 code */
#define uicsr   uic0sr
#define uicer   uic0er
#define uiccr   uic0cr
#define uicpr   uic0pr
#define uictr   uic0tr
#define uicmsr  uic0msr
#define uicvr   uic0vr
#define uicvcr  uic0vcr

/* the interrupt vector definitions */
#define VECNUM_MAL_SERR     10
#define VECNUM_MAL_TXEOB    11
#define VECNUM_MAL_RXEOB    12
#define VECNUM_MAL_TXDE     13
#define VECNUM_MAL_RXDE     14
#define VECNUM_ETH0         15
#define VECNUM_ETH1_OFFS    2
#define VECNUM_EIRQ6        29

/*
 * Mask definitions (used for example in 4xx_enet.c)
 */
#define UIC_MASK(vec)       (0x80000000 >> ((vec) & 0x1f))
/* UIC_NR won't work for 440GX because of its specific UIC DCR addresses */
#define UIC_NR(vec)         ((vec) >> 5)

#endif /* _PPC4xx_UIC_H_ */
