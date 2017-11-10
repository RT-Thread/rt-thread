/*
 * File      : bxcan.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-05-14     aubrcool@qq.com first version
 */

#ifndef BXCAN_H_
#define BXCAN_H_
/* CAN Master Control Register bits */

#define MCR_DBF      ((uint32_t)0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ  ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMR_FINIT    ((uint32_t)0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define INAK_TIMEOUT        ((uint32_t)0x0000FFFF)
/* Time out for SLAK bit */
#define SLAK_TIMEOUT        ((uint32_t)0x0000FFFF)



/* Flags in TSR register */
#define CAN_FLAGS_TSR              ((uint32_t)0x08000000)
/* Flags in RF1R register */
#define CAN_FLAGS_RF1R             ((uint32_t)0x04000000)
/* Flags in RF0R register */
#define CAN_FLAGS_RF0R             ((uint32_t)0x02000000)
/* Flags in MSR register */
#define CAN_FLAGS_MSR              ((uint32_t)0x01000000)
/* Flags in ESR register */
#define CAN_FLAGS_ESR              ((uint32_t)0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0                   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1                   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2                   ((uint8_t)0x02)

#define CAN_MODE_MASK              ((uint32_t) 0x00000003)

void CAN1_RX0_IRQHandler(void);
void CAN1_TX_IRQHandler(void);

#endif /*BXCAN_H_*/
