/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-25     RT-Thread    the first version
 */

#ifndef __DRV_PL041_H__
#define __DRV_PL041_H__

#define PL041_BASE_ADDR    (0x10004000)

/* offsets in CTRL_CH */
#define AACI_RXCR        0x00	/* 29 bits Control Rx FIFO */
#define AACI_TXCR        0x04	/* 17 bits Control Tx FIFO */
#define AACI_SR          0x08	/* 12 bits Status */
#define AACI_ISR         0x0C	/* 7 bits  Int Status */
#define AACI_IE          0x10	/* 7 bits  Int Enable */

/* both for AACI_RXCR and AACI_TXCR */
#define AACI_CR_FEN           (1 << 16)  /* fifo enable */
#define AACI_CR_COMPACT       (1 << 15)  /* compact mode */
#define AACI_CR_SZ16          (0 << 13)  /* 16 bits */
#define AACI_CR_SZ18          (1 << 13)  /* 18 bits */
#define AACI_CR_SZ20          (2 << 13)  /* 20 bits */
#define AACI_CR_SZ12          (3 << 13)  /* 12 bits */
#define AACI_CR_SL12          (1 << 12)
#define AACI_CR_SL11          (1 << 11)
#define AACI_CR_SL10          (1 << 10)
#define AACI_CR_SL9           (1 << 9)
#define AACI_CR_SL8           (1 << 8)
#define AACI_CR_SL7           (1 << 7)
#define AACI_CR_SL6           (1 << 6)
#define AACI_CR_SL5           (1 << 5)
#define AACI_CR_SL4           (1 << 4)
#define AACI_CR_SL3           (1 << 3)
#define AACI_CR_SL2           (1 << 2)
#define AACI_CR_SL1           (1 << 1)
#define AACI_CR_EN            (1 << 0)	/* receive enable */

/* status register bits */
#define AACI_SR_RXTOFE        (1 << 11)  /* rx timeout fifo empty */
#define AACI_SR_TXTO          (1 << 10)  /* rx timeout fifo nonempty */
#define AACI_SR_TXU           (1 << 9)   /* tx underrun */
#define AACI_SR_RXO           (1 << 8)   /* rx overrun */
#define AACI_SR_TXB           (1 << 7)   /* tx busy */
#define AACI_SR_RXB           (1 << 6)   /* rx busy */
#define AACI_SR_TXFF          (1 << 5)   /* tx fifo full */
#define AACI_SR_RXFF          (1 << 4)   /* rx fifo full */
#define AACI_SR_TXHE          (1 << 3)   /* tx fifo half empty */
#define AACI_SR_RXHF          (1 << 2)   /* rx fifo half full */
#define AACI_SR_TXFE          (1 << 1)   /* tx fifo empty */
#define AACI_SR_RXFE          (1 << 0)   /* rx fifo empty */

#define AACI_ISR_RXTOFEINTR   (1 << 6)    /* rx fifo empty */
#define AACI_ISR_URINTR       (1 << 5)    /* tx underflow */
#define AACI_ISR_ORINTR       (1 << 4)    /* rx overflow */
#define AACI_ISR_RXINTR       (1 << 3)    /* rx fifo */
#define AACI_ISR_TXINTR       (1 << 2)    /* tx fifo intr */
#define AACI_ISR_RXTOINTR     (1 << 1)    /* rx timeout */
#define AACI_ISR_TXCINTR      (1 << 0)    /* tx complete */

/* interrupt enable */
#define AACI_IE_RXTOIE        (1 << 6)   /*rx timeout interrupt enable*/
#define AACI_IE_URIE          (1 << 5)   /*Transmit underrun interrupt enable*/
#define AACI_IE_ORIE          (1 << 4)	 /*Overrun receive interrupt enable*/
#define AACI_IE_RXIE          (1 << 3)   /*Receive interrupt enable*/
#define AACI_IE_TXIE          (1 << 2)   /*Transmit interrupt enable*/
#define AACI_IE_RXTIE         (1 << 1)   /*Receive timeout interrupt enable*/
#define AACI_IE_TXCIE         (1 << 0)	 /*Transmit complete interrupt enable*/

/* interrupt status */
#define AACI_ISR_RXTOFE	(1 << 6)	/* rx timeout fifo empty */
#define AACI_ISR_UR		(1 << 5)	/* tx fifo underrun */
#define AACI_ISR_OR		(1 << 4)	/* rx fifo overrun */
#define AACI_ISR_RX		(1 << 3)	/* rx interrupt status */
#define AACI_ISR_TX		(1 << 2)	/* tx interrupt status */
#define AACI_ISR_RXTO	(1 << 1)	/* rx timeout */
#define AACI_ISR_TXC	(1 << 0)	/* tx complete */

/* interrupt enable */
#define AACI_IE_RXTOFE	(1 << 6)	/* rx timeout fifo empty */
#define AACI_IE_UR		(1 << 5)	/* tx fifo underrun */
#define AACI_IE_OR		(1 << 4)	/* rx fifo overrun */
#define AACI_IE_RX		(1 << 3)	/* rx interrupt status */
#define AACI_IE_TX		(1 << 2)	/* tx interrupt status */
#define AACI_IE_RXTO	(1 << 1)	/* rx timeout */
#define AACI_IE_TXC		(1 << 0)	/* tx complete */

/* slot flag register bits */
#define AACI_SLFR_RWIS        (1 << 13)    /* raw wake-up interrupt status */
#define AACI_SLFR_RGPIOINTR   (1 << 12)    /* raw gpio interrupt */
#define AACI_SLFR_12TXE       (1 << 11)    /* slot 12 tx empty */
#define AACI_SLFR_12RXV       (1 << 10)    /* slot 12 rx valid */
#define AACI_SLFR_2TXE        (1 << 9)     /* slot 2 tx empty */
#define AACI_SLFR_2RXV        (1 << 8)     /* slot 2 rx valid */
#define AACI_SLFR_1TXE        (1 << 7)     /* slot 1 tx empty */
#define AACI_SLFR_1RXV        (1 << 6)     /* slot 1 rx valid */
#define AACI_SLFR_12TXB       (1 << 5)     /* slot 12 tx busy */
#define AACI_SLFR_12RXB       (1 << 4)     /* slot 12 rx busy */
#define AACI_SLFR_2TXB        (1 << 3)     /* slot 2 tx busy */
#define AACI_SLFR_2RXB        (1 << 2)     /* slot 2 rx busy */
#define AACI_SLFR_1TXB        (1 << 1)     /* slot 1 tx busy */
#define AACI_SLFR_1RXB        (1 << 0)     /* slot 1 rx busy */

/* Interrupt clear register */
#define AACI_ICLR_RXTOFEC4    (1 << 12)      /* Receive timeout FIFO empty clear */
#define AACI_ICLR_RXTOFEC3    (1 << 11)      /* Receive timeout FIFO empty clear */
#define AACI_ICLR_RXTOFEC2    (1 << 10)      /* Receive timeout FIFO empty clear */
#define AACI_ICLR_RXTOFEC1    (1 << 9)       /* Receive timeout FIFO empty clear */
#define AACI_ICLR_TXUEC4      (1 << 8)       /* Transmit underrun error clear */
#define AACI_ICLR_TXUEC3      (1 << 7)       /* Transmit underrun error clear */
#define AACI_ICLR_TXUEC2      (1 << 6)       /* Transmit underrun error clear*/
#define AACI_ICLR_TXUEC1      (1 << 5)       /* Transmit underrun error clear */
#define AACI_ICLR_RXOEC4      (1 << 4)       /* Receive overrun error clear */
#define AACI_ICLR_RXOEC3      (1 << 3)       /* Receive overrun error clear */
#define AACI_ICLR_RXOEC2      (1 << 2)       /* Receive overrun error clear */
#define AACI_ICLR_RXOEC1      (1 << 1)       /* Receive overrun error clear */
#define AACI_ICLR_WISC        (1 << 0)       /* Wake-up interrupt status clear */
                                
/* Main control register bits AACI_MAINCR */
#define AACI_MAINCR_SCRA(x)   ((x) << 10)     /* secondary codec reg access */
#define AACI_MAINCR_DMAEN     (1 << 9)        /* dma enable */
#define AACI_MAINCR_SL12TXEN  (1 << 8)        /* slot 12 transmit enable */
#define AACI_MAINCR_SL12RXEN  (1 << 7)        /* slot 12 receive enable */
#define AACI_MAINCR_SL2TXEN   (1 << 6)        /* slot 2 transmit enable */
#define AACI_MAINCR_SL2RXEN   (1 << 5)        /* slot 2 receive enable */
#define AACI_MAINCR_SL1TXEN   (1 << 4)        /* slot 1 transmit enable */
#define AACI_MAINCR_SL1RXEN   (1 << 3)        /* slot 1 receive enable */
#define AACI_MAINCR_LPM       (1 << 2)        /* low power mode */
#define AACI_MAINCR_LOOPBK    (1 << 1)        /* loopback */
#define AACI_MAINCR_IE        (1 << 0)        /* aaci interface enable */

/* Reset register bits. P65 */
#define RESET_NRST   (1 << 0)

/* Sync register bits. P65 */
#define SYNC_FORCE   (1 << 0)

/* Main flag register bits. P66 */
#define MAINFR_TXB   (1 << 1)	/* transmit busy */
#define MAINFR_RXB   (1 << 0)	/* receive busy */

#define PL041_CHANNEL_LEFT_DAC    (0x1 << 3)
#define PL041_CHANNEL_RIGHT_DAC   (0x1 << 3)
#define PL041_CHANNEL_LEFT_ADC    (0x1 << 3)
#define PL041_CHANNEL_RIGHT_ADC   (0x1 << 3)

struct reg_pl041
{
volatile rt_uint32_t  rxcr1;    /* 0x000 */
volatile rt_uint32_t  txcr1;    /* 0x004 */
volatile rt_uint32_t  sr1;      /* 0x008 */
volatile rt_uint32_t  isr1;     /* 0x00c */
volatile rt_uint32_t  iie1;     /* 0x010 */
volatile rt_uint32_t  rxcr2;    /* 0x014 */
volatile rt_uint32_t  txcr2;    /* 0x018 */
volatile rt_uint32_t  sr2;      /* 0x01c */
volatile rt_uint32_t  isr2;     /* 0x020 */
volatile rt_uint32_t  iie2;     /* 0x024 */
volatile rt_uint32_t  rxcr3;    /* 0x028 */
volatile rt_uint32_t  txcr3;    /* 0x02c */
volatile rt_uint32_t  sr3;      /* 0x030 */
volatile rt_uint32_t  isr3;     /* 0x034 */
volatile rt_uint32_t  iie3;     /* 0x038 */
volatile rt_uint32_t  rxcr4;    /* 0x03c */
volatile rt_uint32_t  txcr4;    /* 0x040 */
volatile rt_uint32_t  sr4;      /* 0x044 */
volatile rt_uint32_t  isr4;     /* 0x048 */
volatile rt_uint32_t  iie4;     /* 0x04c */
volatile rt_uint32_t  sl1rx;    /* 0x050 */
volatile rt_uint32_t  sl1tx;    /* 0x054 */
volatile rt_uint32_t  sl2rx;    /* 0x058 */
volatile rt_uint32_t  sl2tx;    /* 0x05c */
volatile rt_uint32_t  sl12rx;   /* 0x060 */
volatile rt_uint32_t  sl12tx;   /* 0x064 */
volatile rt_uint32_t  slfr;     /* 0x068 */
volatile rt_uint32_t  slistat;  /* 0x06c */
volatile rt_uint32_t  slien;    /* 0x070 */
volatile rt_uint32_t  intclr;   /* 0x074 */
volatile rt_uint32_t  maincr;   /* 0x078 */
volatile rt_uint32_t  reset;    /* 0x07c */
volatile rt_uint32_t  sync;     /* 0x080 */
volatile rt_uint32_t  allints;  /* 0x084 */
volatile rt_uint32_t  mainfr;   /* 0x088 */
volatile rt_uint32_t  res08c;
volatile rt_uint32_t  dr1[8];   /* 0x090 */
volatile rt_uint32_t  dr2[8];   /* 0x0b0 */
volatile rt_uint32_t  dr3[8];   /* 0x0d0 */
volatile rt_uint32_t  dr4[8];   /* 0x0f0 */
};

typedef struct reg_pl041 *reg_pl041_t;

#define PL041  ((reg_pl041_t)PL041_BASE_ADDR)

struct pl041_cfg
{
    rt_uint32_t itype;
    rt_uint32_t otype;
    int vol;
    int rate;
};
typedef struct pl041_cfg *pl041_cfg_t;

typedef void (*pl041_irq_fun_t)(rt_uint32_t status, void * user_data);

rt_err_t aaci_pl041_init(void);
void aaci_ac97_write(rt_uint16_t reg, rt_uint16_t val);
rt_uint16_t aaci_ac97_read(rt_uint16_t reg);
int aaci_pl041_channel_cfg(int channel, pl041_cfg_t cfg);
int aaci_pl041_channel_write(int channel, rt_uint16_t *buff, int count);
int aaci_pl041_channel_read(int channel, rt_uint16_t *buff, int count);
int aaci_pl041_channel_enable(int channel);
int aaci_pl041_channel_disable(int channel);
rt_err_t aaci_pl041_irq_register(int channel, pl041_irq_fun_t fun, void *user_data);
rt_err_t aaci_pl041_irq_unregister(int channel);
void aaci_pl041_irq_disable(int channel, rt_uint32_t vector);
void aaci_pl041_irq_enable(int channel, rt_uint32_t vector);
#endif
