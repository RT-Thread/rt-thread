/*
 * hw_emac1.h
 */

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef _HW_EMAC_CTRL_H_
#define _HW_EMAC_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define EMAC_CTRL_REVID              (0x0U)
#define EMAC_CTRL_SOFTRESET          (0x4U)
#define EMAC_CTRL_INTCONTROL         (0xCU)
#define EMAC_CTRL_C0RXTHRESHEN       (0x10U)
#define EMAC_CTRL_CnRXEN(n)          (0x14u + ((n) << 4))
#define EMAC_CTRL_CnTXEN(n)          (0x18u + ((n) << 4))
#define EMAC_CTRL_CnMISCEN(n)        (0x1Cu + ((n) << 4))
#define EMAC_CTRL_CnRXTHRESHEN(n)    (0x20u + ((n) << 4))
#define EMAC_CTRL_C0RXTHRESHSTAT     (0x40U)
#define EMAC_CTRL_C0RXSTAT           (0x44U)
#define EMAC_CTRL_C0TXSTAT           (0x48U)
#define EMAC_CTRL_C0MISCSTAT         (0x4CU)
#define EMAC_CTRL_C1RXTHRESHSTAT     (0x50U)
#define EMAC_CTRL_C1RXSTAT           (0x54U)
#define EMAC_CTRL_C1TXSTAT           (0x58U)
#define EMAC_CTRL_C1MISCSTAT         (0x5CU)
#define EMAC_CTRL_C2RXTHRESHSTAT     (0x60U)
#define EMAC_CTRL_C2RXSTAT           (0x64U)
#define EMAC_CTRL_C2TXSTAT           (0x68U)
#define EMAC_CTRL_C2MISCSTAT         (0x6CU)
#define EMAC_CTRL_C0RXIMAX           (0x70U)
#define EMAC_CTRL_C0TXIMAX           (0x74U)
#define EMAC_CTRL_C1RXIMAX           (0x78U)
#define EMAC_CTRL_C1TXIMAX           (0x7CU)
#define EMAC_CTRL_C2RXIMAX           (0x80U)
#define EMAC_CTRL_C2TXIMAX           (0x84U)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

#ifdef __cplusplus
}
#endif


#endif
