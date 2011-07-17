/*
 * 	File: gspi_io.h
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
#ifndef _GSPI_IO_H
#define _GSPI_IO_H
typedef char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed long s32;
typedef unsigned long u32;

typedef signed long long s64;
typedef unsigned long long u64;

#define GPIO_PORTA_DIR_V        (0x1000f004)
#define GPIO_PORTA_SEL_V    	(0x1000f008)
#define GPIO_PORTA_INCTL_V 		(0x1000f00c)
#define GPIO_PORTA_INTRCTL_V	(0x1000f010)
#define GPIO_PORTA_INTRCLR_V 	(0x1000f014)

#define GPIO_PORTD_DIR_V		(0x1000f034)
#define GPIO_PORTD_SEL_V		(0x1000f038)
#define GPIO_PORTD_DATA_V		(0x1000f040)

#define SSI_CONTROL0_V			(0x10009000)
#define SSI_CONTROL1_V			(0x10009004)
#define SSI_SSIENR_V			(0x10009008)
#define SSI_SER_V				(0x10009010)		
#define SSI_BAUDR_V				(0x10009014)
#define SSI_TXFLR_V				(0x10009020)
#define SSI_RXFLR_V				(0x1000901C)
#define SSI_SR_V				       (0x10009028)
#define SSI_IMR_V				(0x1000902c)
#define SSI_ISR_V				(0x10009030)
#define SSI_TXOICR_V				(0x10009038)
#define SSI_RXOICR_V				(0x1000903C)
#define SSI_RXUICR_V				(0x10009040)
#define SSI_DR_V				       (0x10009060)
#define SSI_DMACR_V				(0x1000904C)
#define SSI_ICR_V				(0x10009048)
#define SSI_DMATDLR_V			(0x10009050)
#define SSI_DMARDLR_V			(0x10009054)


#define DMAC_INTSTATUS_V		(0x11001020)

#define DMAC_INTTCSTATUS_V		(0x11001050)

#define DMAC_INTTCCLEAR_V		(0x11001060)
#define DMAC_INTINTERRCLR_V	(0x11001090)
#define DMAC_INTTCCLEAR_V		(0x11001060)

#define DMAC_INTERRORSTATUS_V		(0x11001090)

#define DMAC_INTERRCLR_V		(0x11001080)
#define DMAC_C0SRCADDR_V		(0x11001000)
#define DMAC_C1SRCADDR_V          (0x11001100)
#define DMAC_C0DESTADDR_V		(0x11001004)
#define DMAC_C1DESTADDR_V		(0x11001104)

#define DMAC_C0CONTROL_V		(0x1100100C)
#define DMAC_C1CONTROL_V          (0x1100110C)
#define DMAC_C0CONFIGURATION_V (0x11001010)
#define DMAC_C1CONFIGURATION_V (0x11001110)
#define DMAC_C0DESCRIPTOR_V		(0x11001014)
#define DMAC_C1DESCRIPTOR_V		(0x11001114)
#define DMAC_ENBLDCHNS_V 		(0x110010B0)
#define GSPI_OK				0

typedef struct gspihost_info gspihost_info_t;
typedef gspihost_info_t *gspihost_info_p;
typedef struct gspi_card_rec *gspi_card_rec_p;

typedef struct gspi_card_rec io_card_rec_t;
typedef io_card_rec_t *io_card_rec_p;

struct gspi_card_rec
{
    u8 magic[4];
    gspihost_info_p ctrlr;      // Back Reference to Host Controller
    int (*add) (gspi_card_rec_p card);
    int (*remove) (gspi_card_rec_p card);
 //     IRQ_RET_TYPE(*user_isr) (int, void *, struct pt_regs *);
    void *user_arg;
    u16 chiprev;
};


struct gspihost_info
{
    int irq;
    u16 dev_id;
    int dma_init;                                  /*   physical address      */
    unsigned char *iodata;      /* I/O data buffer           */
    unsigned char *iorw;        /* I/O data buffer           */
    gspi_card_rec_p card;
};



extern int gspi_read_reg(u16 reg, u16 * data);
extern int gspi_write_reg(u16 reg, u16 data);
extern int gspi_read_data(u16 * data, u16 size);
extern int gspi_write_data(u16 * data, u16 size);
//extern int gspi_read_data_direct(u8 * data, u16 reg, u16 size);
extern int gspi_write_data_direct(u8 * data, u16 reg, u16 n);
extern int gspi_read_data_direct(u8 * data, u16 reg, u16 n);
//extern int gspi_write_data_direct(u8 * data, u16 reg, u16 size);
extern void gspi_irq_clear(void);//FOR 4020
extern int gspihost_init(void);
#endif /* _GSPI_IO_H */
