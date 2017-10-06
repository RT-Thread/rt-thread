/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Mar.16.2008     Created.
 ****************************************************************************/

#include "hal.h"
#include "sspd_rts.h"
#include "bsp_hal.h"

#define RTS_PRESSED_Z1_MIN	0x10
#define RTS_PRESSED_Z2_MAX	0xfe0

typedef struct _SSPD_RTS_CONTEXT{

	hal_bh_t		hisr;

	hal_semaphore_t		*usr_ievent;
	struct ts_data		*usr_idata;

} SSPD_RTS_CONTEXT;

SSPD_RTS_CONTEXT rts_ctxt;

#define SSPD_HISR_STACK_SIZE	1024
static uint32_t sspd_rts_hisr_stack[SSPD_HISR_STACK_SIZE];

static void _sspd_rts_lisr(int vector){

	int x = 0, y = 0, z1 = 0, z2 = 0, p = 0;

	DEBUG(0, 1, "Enter\n");

	if (vector != RTS_LISR_VECTOR)
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);

	/* Disable #PENIRQ interrupt */
	uint32_t prv_msk = hal_intc_irq_mask(RTS_LISR_VECTOR);

	/* Clear #PENIRQ interrupt status */
	hal_intc_irq_clean(RTS_LISR_VECTOR);

	/* Enable higher priority interrupt */
	GIE_ENABLE();
//FIXME	
#if 0
#if(NO_EXTERNAL_INT_CTL==0)
	/* Disable #PENIRQ interrupt temporarily */
	CLRB32(INTC_HW1_ER, RTS_LISR_VECTOR);

	/* Clear #PENIRQ interrupt status */
	SETB32(INTC_HW1_CLR, RTS_LISR_VECTOR);
#else
	/* FIXME add clear ts interrupt */
#endif
#endif
	_sspd_rts_probe(&x, &y, &z1, &z2, &p);
	_sspd_rts_probe(&x, &y, &z1, &z2, &p);
	_sspd_rts_probe(&x, &y, &z1, &z2, &p);

	rts_ctxt.usr_idata->x = x;
	rts_ctxt.usr_idata->y = y;
	rts_ctxt.usr_idata->z1 = z1;
	rts_ctxt.usr_idata->z2 = z2;

	DEBUG(0, 1, "%4d, %4d, %4d, %4d\n", x, y, z1, z2);

	if (z1 < 100) {
		/* Disable GIE to prevent nested self */
		GIE_DISABLE();
		/* 
 		 * Clear #PENIRQ interrupt status again because _sspd_rts_probe would trigger #PENIRQ interrupt 
		 * Please reference ADS7846 Spec. 
		 */
		hal_intc_irq_clean(RTS_LISR_VECTOR);
		
		/* Re-enable touch interrupt */
		hal_intc_irq_unmask(prv_msk);	
		return;

	}

	hal_raise_bh(&rts_ctxt.hisr);
	// TODO
	// It is a walk around since interrupt priority
	// we should change the hisr 
	hal_intc_irq_unmask(prv_msk);
	hal_intc_irq_disable(RTS_LISR_VECTOR);
}

static inline void ts_hisr(void *param){

	hal_bh_t *bh = param;

	while (1){

		DEBUG(0, 1, "before\n");
		hal_pend_semaphore(&bh->sem, HAL_SUSPEND);
		DEBUG(0, 1, "after\n");
		hal_post_semaphore(rts_ctxt.usr_ievent);

#ifndef CONFIG_PLAT_QEMU
		hal_sleep(300);
#endif
	
		hal_intc_irq_clean(RTS_LISR_VECTOR);
		HAL_INTC_IRQ_ATOMIC_ENABLE(RTS_LISR_VECTOR);	
	//	SETB32(INTC_HW1_ER, RTS_LISR_VECTOR);
	//	SETB32(INTC_HW1_CLR, RTS_LISR_VECTOR);
	}
}

static void _sspd_rts_set_sclk(int sclk){

	int sclk_div; /* serial clock rate divisor */

	if (sclk > RTS_ADS7846_DCLK_MAX){

		DEBUG(1, 1, "Warning : SCLK exceed allowable range! Truncation is performed.\n");
		sclk = RTS_ADS7846_DCLK_MAX;
	}

	/*
	 * sclk source:
	 *   PLL3   (SSPCLK = PLL3/6) AG101 internal clk
	 *   GPIO25 (SSPCLK = GPIO25) AG101 external clk
	 *   OSCCLK (SSPCLK = OSCCLK * 6 / 6) Leopard
	 *
	 * calculate sclk_div from internal PLL3
	 *
	 * sclk_div = (SSPCLK / sclk / 2) - 1
	 *          = ((PLL3 / 6) / sclk / 2) - 1
	 *          = ((OSCCLK * 30 / 6) / sclk / 2) - 1
	 */

	/*
	 * setup PMU SSP clock source
	 *
	 * PMU_SSPCLKSEL: MFPSR[6]
	 *   0: SSPCLK
	 *   1: GPIO25
	 *
	 * PMU_AC97CLKOUTSEL: MFPSR[13]
	 *   0: GPIO
	 *   1: AC97CLK out
	 */

	/* [2008-03-20] SSP1 only works with internal clock source on AG101 and Leopard EVBs. */

#if 0 /*(MB_SSP_EXT_CLK) */
	sclk_div = (24768000 / (sclk << 1)) - 1;
	SSPD_TRACE(("\nSSPCLK: GPIO25\n"));
	SETB32(PMU_MFPSR, PMU_SSPCLKSEL_BIT);
#else
	sclk_div = (MB_OSCCLK / (2 * sclk)) - 1;
	DEBUG(1, 1, "SSPCLK: PLL\n");
	CLRB32(PMU_MFPSR, PMU_SSPCLKSEL_BIT);
#endif

	DEBUG(1, 1, "sclk     : %d, sclk_div : 0x%04x\n", sclk, sclk_div);

	/*
	 * setup SSP SCLKDIV
	 *   PDL     : (padding data length) not used
	 *   SDL     : (serial data length) 8-1 (8 bits)
	 *   SCLKDIV : sclk_div
	 */
#ifndef CONFIG_PLAT_QEMU
	OUT32(SSPC_CR1, ((7  << SSPC_C1_SDL_SHIFT) & SSPC_C1_SDL_MASK) |               /* bit data length */
			((sclk_div << SSPC_C1_SCLKDIV_SHIFT) & SSPC_C1_SCLKDIV_MASK)); /* sclkdiv */
#else
	OUT32(SSPC_CR1, ((23 << SSPC_C1_SDL_SHIFT) & SSPC_C1_SDL_MASK) |               /* bit data length */
			((sclk_div << SSPC_C1_SCLKDIV_SHIFT) & SSPC_C1_SCLKDIV_MASK)); /* sclkdiv */
#endif
}

int _sspd_rts_init(struct ts_dev *ts){

	int  status = HAL_SUCCESS;
	int  core_intl;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* SSP controler initialization - SPI */

	/* Disable all SSP interrupts, and set DMA trigger FIFO threshold to 0. */
	OUT32(SSPC_INTCR, 0);
	/* check ts interrupt vector*/
	if (ts->penirq){
		status = hal_register_isr(RTS_LISR_VECTOR, _sspd_rts_lisr, (void*)0);
		if (status != HAL_SUCCESS){

			DEBUG(1, 1, "Failed to register SSPD driver LISR!\n");
			return status;
		}

		rts_ctxt.usr_ievent	= ts->event_obj;
		rts_ctxt.usr_idata	= ts->event_data;
		rts_ctxt.hisr.th.fn	= ts_hisr;
		rts_ctxt.hisr.th.ptos	= &sspd_rts_hisr_stack[SSPD_HISR_STACK_SIZE];
		rts_ctxt.hisr.th.stack_size = sizeof(sspd_rts_hisr_stack);
		rts_ctxt.hisr.th.prio	= CONFIG_TSD_HISR_PRIORITY;
		rts_ctxt.hisr.th.name	= "TS BH";
		rts_ctxt.hisr.th.arg	= &rts_ctxt.hisr;
		status = hal_create_bh(&rts_ctxt.hisr);

		if (status != HAL_SUCCESS){

			DEBUG(1, 1, "Failed to create SSPD-RTS driver HISR!\n");
			return status;
		}

		/* INTC */
		/* - Disable #PENIRQ interrupt */
		hal_intc_irq_disable(RTS_LISR_VECTOR);
		/* - Clear #PENIRQ interrupt status */
		hal_intc_irq_clean(RTS_LISR_VECTOR);
		/* - Setup #PENIRQ interrupt trigger mode - edge trigger */
		/* - Setup #PENIRQ interrupt trigger level - assert low */
		hal_intc_irq_config(RTS_LISR_VECTOR, IRQ_EDGE_TRIGGER, IRQ_ACTIVE_LOW);

		if (ts->penirq_en){
		/* - Enable #PENIRQ interrupt */
		hal_intc_irq_enable(RTS_LISR_VECTOR);
		}
	}

	/* Reset SSP controller */
	SETB32(SSPC_CR2, SSPC_C2_SSPRST_BIT);

	/* Disable SSP data out */
	CLRR32(SSPC_CR2, SSPC_C2_SSPEN_MASK | SSPC_C2_TXDOE_MASK);

	/* setup sspc clock */
	_sspd_rts_set_sclk(RTS_ADS7846_DCLK_DEFAULT);

	_nds_kwait(RTS_RESET_WAIT);

	/* Set SSP frame format to SPI */
	OUT32(SSPC_CR0, ((0 << SSPC_C0_SCLKPH_BIT) & SSPC_C0_SCLKPH_MASK) |            /* phase (1 not working for 16clk mode) */
			((0 << SSPC_C0_SCLKPO_BIT) & SSPC_C0_SCLKPO_MASK) |            /* polarity */
			((SSPC_SSP_MASTER << SSPC_C0_OPM_SHIFT) & SSPC_C0_OPM_MASK) |  /* operation mode */
			((0 << SSPC_C0_LBM_BIT) & SSPC_C0_LBM_MASK) |                  /* loopback */
			((SSPC_MOTO_SPI << SSPC_C0_FFMT_SHIFT) & SSPC_C0_FFMT_MASK));  /* frame format */

	/* Clear FIFO garbage */
	SETR32(SSPC_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);


	/* Restore CPU interrupt controller to previous level */
	hal_global_int_ctl(core_intl);

	return status;
}

int _sspd_rts_probe(int *x, int *y, int *z1, int *z2, int *pressed){

	uint32_t data[12];
	int t, i;

	/* Clear FIFO garbage */
	SETR32(SSPC_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);

	/* Enable SSP */
	SETB32(SSPC_CR2, SSPC_C2_SSPEN_BIT);

	/* Disable SSP data out temporarily */
	CLRB32(SSPC_CR2, SSPC_C2_TXDOE_BIT);

	/* [hw-limit] Wait until the ssp controller get ready */
	// _nds_kwait(RTS_DIN_WAIT);

	t = 0;
	while (((IN32(SSPC_SR) & SSPC_SR_BUSY_MASK) != 0) && (t++ < RTS_DIN_TIMEOUT))
		;

	DEBUG(0, 1, "[RTS] SR : 0x%08lx\n", IN32(SSPC_SR));

	/*
	 * ------------------------------------------------------------------------
	 * Timing of 16-clock-cycle per conversion
	 *
	 *                 power-up    read y     read x    power down (full cycle)
	 *                 ---------  ---------  ---------  ---------------
	 *  dout (bytes)   ctrl    0  ctrl    0  ctrl    0  ctrl    0    0  ____
	 *  din  (bytes)      0  msb   lsb  msb   lsb  msb   lsb  msb  lsb  ____
	 *                 ^^^^  ^^^^^^^^^  ^^^^^^^^^  ^^^^^^^^^  ^^^^^^^^
	 *                    don't care     x1 or y1   x2 or y2  don't care
	 *
	 *  x = (x1 + x2) / 2 (if averaging was expected)
	 *  y = (y1 + y2) / 2 (if averaging was expected)
	 *
	 * Note: Watch out SSP FIFO depth (12 for AG101/Leopard)
	 * ------------------------------------------------------------------------
	 */

	/* SPI dout ... */
#ifndef CONFIG_PLAT_QEMU
	/* power up */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RY);
	OUT32(SSPC_DR, 0);

	/* read y */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RY);
	OUT32(SSPC_DR, 0);
	
	/* read x */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RX);
	OUT32(SSPC_DR, 0);
	
	/* read z1 */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RZ1);
	OUT32(SSPC_DR, 0);
	
	/* read z2 && power down */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RZ2_PD);
	OUT32(SSPC_DR, 0);
	OUT32(SSPC_DR, 0);
#else
	/* power up */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RY 	<< 16);
	OUT32(SSPC_DR, 0);

	/* read y */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RY	<< 16);
	OUT32(SSPC_DR, 0);
	
	/* read x */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RX	<< 16);
	OUT32(SSPC_DR, 0);
	
	/* read z1 */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RZ1	<< 16);
	OUT32(SSPC_DR, 0);
	
	/* read z2 && power down */
	OUT32(SSPC_DR, RTS_ADS7846_CTL_RZ2_PD	<< 16);
	OUT32(SSPC_DR, 0);
	OUT32(SSPC_DR, 0);
#endif
	/* Enable SSP-TX out */
	SETB32(SSPC_CR2, SSPC_C2_TXDOE_BIT);

	/* SPI din ... */
	for (i = 0; i < 11; ++i){

		/* Wait until data ready */
		t = 0;
		while ((IN32(SSPC_SR) & SSPC_SR_RFVE_MASK) == 0){
			if ( ++t > RTS_DIN_TIMEOUT){

				DEBUG(1, 1, "rts spi timeout at data[%d]\n", i);
				goto _timeout;
			}
		}
		/* Read data byte */
		data[i] = IN32(SSPC_DR);
		DEBUG(0, 1, "[RTS] data[%d] %d, 0x%x\n", i, data[i], data[i]);
	}

	/* Disable SSP data out */
	CLRR32(SSPC_CR2, SSPC_C2_SSPEN_MASK | SSPC_C2_TXDOE_MASK);

	/* Compose final data (12-bits or 8-bits) */
#if ((RTS_ADS7846_RY & RTS_ADS7846_MODE_MASK) == (RTS_ADS7846_8_BITS << RTS_ADS7846_MODE_SHIFT))
	*y = RTS_ADS7846_8BITS_DATA(data[3], data[4]);
	*x = RTS_ADS7846_8BITS_DATA(data[5], data[6]);
	*z1 = RTS_ADS7846_8BITS_DATA(data[7], data[8]);
	*z2 = RTS_ADS7846_8BITS_DATA(data[9], data[10]);
#else
	*y = RTS_ADS7846_12BITS_DATA(data[3], data[4]);
	*x = RTS_ADS7846_12BITS_DATA(data[5], data[6]);
	*z1 = RTS_ADS7846_12BITS_DATA(data[7], data[8]);
	*z2 = RTS_ADS7846_12BITS_DATA(data[9], data[10]);
#endif
#ifndef CONFIG_PLAT_QEMU
	DEBUG(0, 1, "[RTS] y  - %04d, msb(0x%02lx) lsb(0x%02lx)\n", *y, (data[3] & 0xff), (data[4] & 0xff));
	DEBUG(0, 1, "[RTS] x  - %04d, msb(0x%02lx) lsb(0x%02lx)\n", *x, (data[5] & 0xff), (data[6] & 0xff));
	DEBUG(0, 1, "[RTS] z1 - %04d, msb(0x%02lx) lsb(0x%02lx)\n", *z1, (data[7] & 0xff), (data[8] & 0xff));
	DEBUG(0, 1, "[RTS] z2 - %04d, msb(0x%02lx) lsb(0x%02lx)\n", *z2, (data[9] & 0xff), (data[10] & 0xff));
#else
	DEBUG(0, 1, "[RTS] y  - %d, msb(0x%x)%d, lsb(0x%x)%d\n", *y,  data[3],data[3], data[4], data[4]);
	DEBUG(0, 1, "[RTS] x  - %d, msb(0x%x)%d, lsb(0x%x)%d\n", *x,  data[5],data[5], data[6], data[6]);
	DEBUG(0, 1, "[RTS] z1 - %d, msb(0x%x)%d, lsb(0x%x)%d\n", *z1, data[7],data[7], data[8], data[8]);
	DEBUG(0, 1, "[RTS] z2 - %d, msb(0x%x)%d, lsb(0x%x)%d\n", *z2, data[9],data[9], data[10], data[10]);
#endif	
	if ((*z1 < RTS_PRESSED_Z1_MIN) && (*z2 >= RTS_PRESSED_Z2_MAX))
		*pressed = 0;
	else
		*pressed = 1;

	return HAL_SUCCESS;

_timeout:

	return HAL_FAILURE;
}

void ts_adjust(struct ts_dev *ts, int ts_x, int ts_y, int *x, int *y)
{
	*x = (ts->lcd_width * (ts_x - ts->left)) / (ts->right - ts->left);
	*y = (ts->lcd_height * (ts_y - ts->top)) / (ts->bottom - ts->top);
	DEBUG(0, 0, "adj (x, y) = (%4d, %4d)\n", *x, *y);
}

void ts_raw_value(struct ts_dev *ts, int *x, int *y)
{
	hal_pend_semaphore(&ts->sem, HAL_SUSPEND);

	*x = ts->data.x;
	*y = ts->data.y;
	DEBUG(0, 0, "raw (x, y) = (%4d, %4d)\n", *x, *y);
}

void ts_value(struct ts_dev *ts, int *x, int *y)
{
	int raw_x, raw_y;
	ts_raw_value(ts, &raw_x, &raw_y);
	ts_adjust(ts, raw_x, raw_y, x, y);
}

void ts_calibrate(struct ts_dev *ts,
		void (*draw_cross)(void *param, int x, int y),
		int count)
{
	int i = 0;
	int left = 0, right = 0, top = 0, bottom = 0;

	for (i = 0; i < count; i++) {

		int raw_x = 0, raw_y = 0;

		DEBUG(0, 0, "(left, top) = ");
		draw_cross(NULL, ts->lcd_width * 1 / 5, ts->lcd_height * 1 / 5);
		ts_raw_value(ts, &raw_x, &raw_y);
		left = ((left * i) + raw_x) / (i + 1);
		top = ((top * i) + raw_y) / (i + 1);
		DEBUG(0, 0, "(%4d, %4d) ||  (x, y) = (%4d, %4d)\n", left, top, raw_x, raw_y);

		DEBUG(0, 0, "(right, bottom) = ");
		draw_cross(NULL, ts->lcd_width * 4 / 5, ts->lcd_height * 4 / 5);
		ts_raw_value(ts, &raw_x, &raw_y);
		right = ((right * i) + raw_x) / (i + 1);
		bottom = ((bottom * i) + raw_y) / (i + 1);
		DEBUG(0, 0, "(%4d, %4d) ||  (x, y) = (%4d, %4d)\n", right, bottom, raw_x, raw_y);
	}

	ts->left        = left - (right - left) / 3;
	ts->right       = right + (right - left) / 3;
	ts->top         = top - (bottom - top) / 3;
	ts->bottom      = bottom + (bottom - top) / 3;
}
