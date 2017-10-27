/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Mar.16.2008     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *      sspd_rts.h
 *
 * DESCRIPTION
 *
 *      SPI digital serial interface protocol header for resistive
 *      touch screen controller.
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   None
 *
 ****************************************************************************/
#ifndef __SSPD_RTS_H__
#define __SSPD_RTS_H__

/*****************************************************************************
 * Configuration Options
 ****************************************************************************/

/* Non-zero to enable 16-clock per conversion mode, otherwise 24-clock cycle is applied. */
#define RTS_16CLK_CONV_CYCLE    1

#define RTS_LISR_VECTOR		INTC_HW0_BIT		/* AG101 connects #PENIRQ to hw0 vector */

/* polling loop counter for waiting hw-reset */
#define RTS_RESET_WAIT		(0x300000)

/* CPU polling counter to avoid bouncing signals of previous RTS operation */
#define RTS_DEBOUNCE_WAIT	(0x30000)

/* polling counter for serial data in */
#define RTS_DIN_TIMEOUT		(0x30000)

/* HISR definitions */
#define RTS_HISR_PRIORITY	0		/* 0: highest, 2: lowest */
#define RTS_HISR_STACK_SIZE	2048		/* Please align to 32-bit */

#define RTS_HISR_AS_TOUCHED	0x00000001	/* Activate HISR for touched interrupt */


/*****************************************************************************
 * Resistive Touch Screen Digital Interface Definitions
 ****************************************************************************/

/* Definitions for ADS7846 */

/* Control Byte Bits */
#define RTS_ADS7846_PD_MASK	0x03		/* Start Bit (MSB) */
#define RTS_ADS7846_PD_SHIFT	0
    #define RTS_ADS7846_PD	0x00		/* power down between conversion, #penirq enabled */
    #define RTS_ADS7846_ADC	0x01		/* ref off, adc on, #penirq disabled */
    #define RTS_ADS7846_REF	0x02		/* ref on, adc off, #penirq enabled */
    #define RTS_ADS7846_PW	0x03		/* power on, ref on, adc on, #penirq disabled */

#define RTS_ADS7846_SER_MASK	0x04		/* Single-Ended/#Differential-Reference Register */
#define RTS_ADS7846_SER_SHIFT	2
    #define RTS_ADS7846_DF	0x00		/* differential */
    #define RTS_ADS7846_SE	0x01		/* single-ended */

#define RTS_ADS7846_MODE_MASK	0x08		/* Conversion Selection Bit */
#define RTS_ADS7846_MODE_SHIFT	3
    #define RTS_ADS7846_12_BITS	0x00		/* 12 bits conversion */
    #define RTS_ADS7846_8_BITS	0x01		/* 8 bits conversion */

#define RTS_ADS7846_MUX_MASK	0x70		/* (A2 ~ A0) Control the setting of multiplexer input */
#define RTS_ADS7846_MUX_SHIFT	4

    #define RTS_ADS7846_DF_X	0x05		/* [A2:A0] 101b, Driver: X+ X-, Measure Y+ */
    #define RTS_ADS7846_DF_Y	0x01		/* [A2:A0] 001b, Driver: Y+ Y-, Measure X+ */
    #define RTS_ADS7846_DF_Z1	0x03		/* [A2:A0] 011b, Driver: Y+ X-, Measure X+ */
    #define RTS_ADS7846_DF_Z2	0x04		/* [A2:A0] 100b, Driver: Y+ X-, Measure Y- */

    #define RTS_ADS7846_SE_X	0x05		/* [A2:A0] 101b */
    #define RTS_ADS7846_SE_Y	0x01		/* [A2:A0] 001b */
    #define RTS_ADS7846_SE_Z1	0x03		/* [A2:A0] 011b */
    #define RTS_ADS7846_SE_Z2	0x04		/* [A2:A0] 100b */
    #define RTS_ADS7846_SE_BAT	0x02		/* [A2:A0] 010b */
    #define RTS_ADS7846_SE_AUX	0x06		/* [A2:A0] 110b */
    #define RTS_ADS7846_SE_TEMP0	0x00	/* [A2:A0] 000b */
    #define RTS_ADS7846_SE_TEMP1	0x07	/* [A2:A0] 111b */

#define RTS_ADS7846_START_MASK	0x80            /* Start Bit (MSB) */
#define RTS_ADS7846_START_BIT	7
    #define RTS_ADS7846_START	1

/* Supplimental Macros */
#define RTS_ADS7846_PADDING_BYTE	0	/* Padding byte feed after the command byte to continue serial clocking */

#define RTS_ADS7846_CTRL_BYTE(mux, mode, ser, pd)                            \
    ((((uint32_t)(mux) << RTS_ADS7846_MUX_SHIFT) & RTS_ADS7846_MUX_MASK) |    \
     (((uint32_t)(mode) << RTS_ADS7846_MODE_SHIFT) & RTS_ADS7846_MODE_MASK) | \
     (((uint32_t)(ser) << RTS_ADS7846_SER_SHIFT) & RTS_ADS7846_SER_MASK) |    \
     (((uint32_t)(pd) << RTS_ADS7846_PD_SHIFT) & RTS_ADS7846_PD_MASK) |       \
     (uint32_t)RTS_ADS7846_START_MASK)

/* this is correct */
#define RTS_ADS7846_8BITS_DATA(msb, lsb)    ((((uint32_t)(msb) & 0x07) << 5) | (((uint32_t)(lsb) & 0xff) >> 3))
#ifndef CONFIG_PLAT_QEMU
#define RTS_ADS7846_12BITS_DATA(msb, lsb)   ((((uint32_t)(msb) & 0x7f) << 5) | (((uint32_t)(lsb) & 0xff) >> 3))
#else
#define RTS_ADS7846_12BITS_DATA(msb, lsb)   msb
//#define RTS_ADS7846_12BITS_DATA(msb, lsb)   ((msb >> 19) & 0xfff)
#endif

/* Pre-defined Control-Byte Constants */
#define RTS_ADS7846_CTL_RY  RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Y, RTS_ADS7846_12_BITS,    \
                                                  RTS_ADS7846_DF, RTS_ADS7846_PW)
#define RTS_ADS7846_CTL_RX  RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_X, RTS_ADS7846_12_BITS,    \
                                                  RTS_ADS7846_DF, RTS_ADS7846_PW)
#define RTS_ADS7846_CTL_RZ1 RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Z1, RTS_ADS7846_12_BITS,   \
                                                  RTS_ADS7846_DF, RTS_ADS7846_PW)
#define RTS_ADS7846_CTL_RZ2 RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Z2, RTS_ADS7846_12_BITS,   \
                                                  RTS_ADS7846_DF, RTS_ADS7846_PW)

#define RTS_ADS7846_CTL_RY_PD   RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Y, RTS_ADS7846_12_BITS,    \
                                                      RTS_ADS7846_DF, RTS_ADS7846_PD)
#define RTS_ADS7846_CTL_RX_PD   RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_X, RTS_ADS7846_12_BITS,    \
                                                      RTS_ADS7846_DF, RTS_ADS7846_PD)
#define RTS_ADS7846_CTL_RZ1_PD  RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Z1, RTS_ADS7846_12_BITS,   \
                                                      RTS_ADS7846_DF, RTS_ADS7846_PD)
#define RTS_ADS7846_CTL_RZ2_PD  RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Z2, RTS_ADS7846_12_BITS,   \
                                                      RTS_ADS7846_DF, RTS_ADS7846_PD)
#define RTS_ADS7846_CTL_PD      RTS_ADS7846_CTRL_BYTE(RTS_ADS7846_DF_Y, RTS_ADS7846_12_BITS,    \
                                                      RTS_ADS7846_DF, RTS_ADS7846_PD)
/*
 * DCLK
 * ---------------
 * From pp3:
 *   125 kHz max throughput rate, so ...
 *     DCLK_max = 125k * 16(16-clock-per-conversion mode) = 2.0MHz
 *
 * From table VI (p.p.14):
 *   (tch + tcl) = 400ns minimum, so ...
 *     DCLK_max = 1/400ns = 2.5MHz ?
 */
#define RTS_ADS7846_DCLK_MAX                2000000     /* adopt 2.0MHz for safe */
#define RTS_ADS7846_DCLK_DEFAULT            125000      /* 7812 data per second (3906 x-y/sec, or 1953 x-y-z1-z2/sec) */


/*****************************************************************************
 * SSP Controller Resistive Touch Screen Driver-Supplement Interfaces
 ****************************************************************************/
struct ts_data {

	int	x;
	int	y;
	int	z1;
	int	z2;
	int	pressed;

};

struct ts_dev {

	int left;
	int right;
	int top;
	int bottom;

	int lcd_width;
	int lcd_height;

	int			penirq;		/* initialize touch screen driver in #penirq mode or polling mode */
	int			penirq_en;	/* enable #penirq after initialization if penirq is non-zero */

	void			*event_obj;	/* (in) Event object to notify app about the interrupt. */
	struct ts_data		*event_data;	/* Client specified struct pointer to receive {x,y,touched} states */

	hal_semaphore_t		sem;
	struct ts_data		data;
};

extern int _sspd_rts_init(struct ts_dev *ts);
extern int _sspd_rts_probe(int *x, int *y, int *z1, int *z2, int *pressed);

extern void ts_adjust(struct ts_dev *ts, int ts_x, int ts_y, int *x, int *y);
extern void ts_raw_value(struct ts_dev *ts, int *x, int *y);
extern void ts_value(struct ts_dev *ts, int *x, int *y);
extern void ts_init(struct ts_dev *ts);
extern void ts_calibrate(struct ts_dev *ts, void (*draw_cross)(void *param, int x, int y), int count);
#endif /* __SSPD_RTS_H__ */
