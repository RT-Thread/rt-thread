#include "hal.h"
#include "dma/dmad.h"

#include "sspd_ac97.h"

/* SSP FIFO properties */
#define SSPD_HW_TXFIFO_DEPTH	16	/* TX FIFO size, units of 32bit (todo: HW readback?) */
#define SSPD_HW_RXFIFO_DEPTH	16	/* RX FIFO size, units of 32bit (todo: HW readback?) */

/*****************************************************************************
 * Data size for each each DMA request
 *
 * Adjust hint:
 *
 *   AC97DMA_REQ_FRAMES  sampling_rate    effective  data_size(2ch)  data_size(6ch)
 *   ------------------------------------------------------------------------------
 *    4096               48k (ac97-fix)   85.33 ms    32768 bytes     98304 bytes
 *    8192               48k (ac97-fix)  170.66 ms    65536 bytes    196608 bytes
 *   10240               48k (ac97-fix)  213.33 ms    81920 bytes    245760 bytes
 *   12288               48k (ac97-fix)  256.00 ms    98304 bytes    294912 bytes
 *   20480               48k (ac97-fix)  426.66 ms   163840 bytes    491520 bytes
 ****************************************************************************/
#define AC97DMA_REQ_FRAMES	(20480)		/* number of frames */

#define AC97_RESET_WAIT		(0x600000)	/* polling loop counter for waiting hw-reset */

enum SSPD_AC97_RESET {

	SSPD_AC97_COLDRESET,	/* All AC97 logic is initialized to its default state */
	SSPD_AC97_WARMRESET,	/* Contents of AC97 registers are left unaltered */
	SSPD_AC97_REGRESET,	/* Only Initialize the AC97 registers to their default states */
};

void sspd_ac97_sdata_out(uint32_t *txb, int cnt)
{
	while (cnt > 0) {
		
		uint32_t tfve;

		/* Check room in TX FIFO */
		tfve = MASK32(I2SAC97_SR, SSPC_SR_TFVE_MASK) >> SSPC_SR_TFVE_SHIFT;

		/* Burst send to TX FIFO */
		while (tfve++ < SSPD_HW_TXFIFO_DEPTH) {

			/* Send one 32-bit word to TX FIFO */
			OUT32(I2SAC97_DR, *txb++);

			if (--cnt == 0)
				break;
		}
	}
}

void sspd_ac97_cmd_out(int regidx, uint32_t data)
{
	uint32_t txb[16];

	/* Prepare AC97 write register address (slot1) and data (slot2) */
	AC97_MAKE_WCMD(txb, regidx, data);

	/* Clear SSP FIFO garbage */
	SETR32(I2SAC97_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);

	/* Set frame-tag slot-valid bits */
	OUT32(I2SAC97_ACLINK, SSPC_AC97_WCMD_SLOTS_MASK | SSPC_AC97_MAKE_CODECID(0));

	/* Feed data to TX FIFO -- AC97 CR-write contains 2 slots */

	/*
	 * [??] According to AC97 2.1 spec, stuff bits with 0 has to be at their
	 * position during the slot's active time.  SSP will smart enough to
	 * identify giving valid slots and auto stuffs 0s to empty slots in TX
	 * mode?  And whot about the same question in RX mode?
	 */

	sspd_ac97_sdata_out(txb, SSPC_AC97_WCMD_SLOTS);

	/* Enable SSP TX data out */
	SETR32(I2SAC97_CR2, SSPC_C2_TXDOE_MASK | SSPC_C2_SSPEN_MASK);

	while (MASK32(I2SAC97_SR, SSPC_SR_TFVE_MASK))
		;

	/* Disable SSP TX data out */
	CLRR32(I2SAC97_CR2, SSPC_C2_TXDOE_MASK | SSPC_C2_SSPEN_MASK);
}

void sspd_ac97_reset(enum SSPD_AC97_RESET rest_type)
{
	uint32_t core_intl;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Disable SSP interrupts */
	CLRR32(I2SAC97_INTCR, SSPC_INTCR_RFORIEN_MASK | SSPC_INTCR_TFURIEN_MASK |
			SSPC_INTCR_RFTHIEN_MASK | SSPC_INTCR_TFTHIEN_MASK |
			SSPC_INTCR_RFDMAEN_MASK | SSPC_INTCR_TFDMAEN_MASK |
			SSPC_INTCR_AC97FCEN_MASK);

	/* Disable SSP data out */
	CLRR32(I2SAC97_CR2, SSPC_C2_SSPEN_MASK | SSPC_C2_TXDOE_MASK);

	/* Disable DMA request FIFO trigger */
	CLRR32(I2SAC97_INTCR, SSPC_INTCR_TFDMAEN_MASK | SSPC_INTCR_RFDMAEN_MASK);

	/* Clear FIFO garbage */
	SETR32(I2SAC97_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);

	/* Set SSP frame format as AC97 */
	SETR32SHL(I2SAC97_CR0, SSPC_C0_FFMT_MASK, SSPC_C0_FFMT_SHIFT, SSPC_INTEL_ACLINK);

	switch (rest_type) {

		case SSPD_AC97_COLDRESET: /* All AC97 logic is initialized to its default state */

			/* (reset time: SSPCLK * SCLK_DIV) */
			DEBUG(1, 1, "SSPD_AC97_COLDRESET\n");
			SETB32(I2SAC97_CR2, SSPC_C2_ACCRST_BIT);

			while (GETB32(I2SAC97_CR2, SSPC_C2_ACCRST_BIT))
				;
			_nds_kwait(AC97_RESET_WAIT);

			break;
		case SSPD_AC97_WARMRESET: /* Contents of AC97 registers are left unaltered */

			/* (reset time: SSPCLK * SCLK_DIV, or wait ACWRST cleared) */
			DEBUG(1, 1, "SSPD_AC97_WARMRESET\n");
			SETB32(I2SAC97_CR2, SSPC_C2_ACWRST_BIT);

			while (GETB32(I2SAC97_CR2, SSPC_C2_ACWRST_BIT))
				;

			break;
		case SSPD_AC97_REGRESET: /* Only Initialize the AC97 registers to their default states */

			DEBUG(1, 1, "SSPD_AC97_REGRESET\n");

			/* Write AC97 reset register to do codec register reset */
			sspd_ac97_cmd_out(AC97_CRIDX_RESET, 0);
			_nds_kwait(AC97_RESET_WAIT);

			break;
		default:
			DEBUG(1, 1, "Invalid reset method!\n");
	}

	hal_global_int_ctl(core_intl);
}

void sspd_ac97_init(void)
{
	uint32_t core_intl;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/*
	 *  Change AC97 codec & SSP clock source
	 * 
	 *  PMU_AC97PINSEL: MFPSR[3]
	 *    0: X_I2Ssclkout/I2SCLK
	 *    1: X_ac97_resetn/50MHz in AG101
	 *  PMU_AC97CLKSEL: MFPSR[4]
	 *    0: AC97CLK (Set AC97 XTL_IN source is from internal PLL.  BIT_CLK is XTL_IN / 2)
	 *    1: GPIO22
	 *  PMU_SSPCLKSEL: MFPSR[6]
	 *    0: SSPCLK
	 *    1: GPIO25
	 *  PMU_AC97CLKOUTSEL: MFPSR[13]
	 *    0: GPIO
	 *    1: AC97CLK out
	 */ 

	 // SETR32(PMU_MFPSR, PMU_AC97PINSEL_MASK | PMU_AC97CLKSEL_MASK | PMU_SSPCLKSEL_MASK | PMU_AC97CLKOUTSEL_MASK);
	 // SETR32(PMU_MFPSR, PMU_AC97PINSEL_MASK | PMU_AC97CLKOUTSEL_MASK);
	 // SETB32(PMU_MFPSR, PMU_AC97CLKSEL_BIT);

#if (MB_AC97_EXT_CLK)
	DEBUG(1, 1, "AC97CLK: GPIO22\n");
	SETR32(PMU_MFPSR, PMU_AC97PINSEL_MASK | PMU_AC97CLKSEL_MASK | PMU_AC97CLKOUTSEL_MASK);
#else  /* MB_AC97_EXT_CLK */
	DEBUG(1, 1, "AC97CLK: PLL\n");
	SETR32(PMU_MFPSR, PMU_AC97PINSEL_MASK | PMU_AC97CLKOUTSEL_MASK);
	CLRB32(PMU_MFPSR, PMU_AC97CLKSEL_BIT);
#endif  /* MB_AC97_EXT_CLK */

	sspd_ac97_reset(SSPD_AC97_COLDRESET);

	/* Setup DMA FIFO trigger threshold */
	SETR32SHL(I2SAC97_INTCR, SSPC_INTCR_TFTHOD_MASK, SSPC_INTCR_TFTHOD_SHIFT, 0);
	SETR32SHL(I2SAC97_INTCR, SSPC_INTCR_RFTHOD_MASK, SSPC_INTCR_RFTHOD_SHIFT, 0);

	/* SSP AC97 codec initialization */

	/*
	 * Default master volume?
	 * Default mixer-in gain?
	 * Default record input selection?
	 */
	//sspd_ac97_cmd_out(AC97_CRIDX_MASTER_VOLUME, 0);

	hal_global_int_ctl(core_intl);
}

void sspd_ac97_terminate(void)
{
	uint32_t core_intl;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Disable SSP interrupts */
	CLRR32(I2SAC97_INTCR, SSPC_INTCR_RFORIEN_MASK | SSPC_INTCR_TFURIEN_MASK |
			SSPC_INTCR_RFTHIEN_MASK | SSPC_INTCR_TFTHIEN_MASK |
			SSPC_INTCR_RFDMAEN_MASK | SSPC_INTCR_TFDMAEN_MASK |
			SSPC_INTCR_AC97FCEN_MASK);

	/* Disable SSP data out */
	CLRR32(I2SAC97_CR2, SSPC_C2_SSPEN_MASK | SSPC_C2_TXDOE_MASK);

	/* Cold reset AC97 codec */
	SETB32(I2SAC97_CR2, SSPC_C2_ACCRST_BIT);
	while (GETB32(I2SAC97_CR2, SSPC_C2_ACCRST_BIT))
		;

	/* Clear FIFO garbage */
	SETR32(I2SAC97_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);

	hal_global_int_ctl(core_intl);
}

void ac97_init(void)
{
	sspd_ac97_init();

	sspd_ac97_cmd_out(AC97_CRIDX_RESET, 0);
	_nds_kwait(AC97_RESET_WAIT);

	sspd_ac97_cmd_out(AC97_CRIDX_PCMOUT_GAIN,
			AC97_MIXER_GAIN(AC97_MIXER_MAX, AC97_MIXER_MAX));

	sspd_ac97_cmd_out(AC97_CRIDX_MASTER_VOLUME,
			AC97_STEREO_VOLUME(AC97_VOLUME_MAX - 0x30, AC97_VOLUME_MAX - 0x30));

	SETR32SHL(I2SAC97_INTCR, SSPC_INTCR_TFTHOD_MASK, SSPC_INTCR_TFTHOD_SHIFT, 4);
	SETR32SHL(I2SAC97_INTCR, SSPC_INTCR_RFTHOD_MASK, SSPC_INTCR_RFTHOD_SHIFT, 4);
	OUT32(I2SAC97_ACLINK, SSPC_AC97_PCM_SLOTS_MASK | SSPC_AC97_MAKE_CODECID(0));
	SETR32(I2SAC97_INTCR, SSPC_INTCR_TFDMAEN_MASK);
	SETR32(I2SAC97_CR2, SSPC_C2_TXDOE_MASK | SSPC_C2_SSPEN_MASK);
	SETR32(I2SAC97_CR2, SSPC_C2_RXFCLR_MASK | SSPC_C2_TXFCLR_MASK);
}

volatile int g_buffered_frames;

/* No use and marked by KCLin */
/*
static void psp(void *data)
{
	g_buffered_frames -= *(int*)data;
	free(data);

}
*/

static void rcp(void *data)
{
	g_buffered_frames -= *(int*)data;
	free(data);
}
extern int ring_idx;
void ac97_play(int frames, uint32_t *pcm_data, void *ac97_data)
{
	DMAD_CHANNEL_REQUEST_DESC *ch_req = ac97_data;

	while (frames > 0){

		int f;
		int *data;
		DMAD_DRB *drb;

		f = (frames < AC97DMA_REQ_FRAMES) ? frames : AC97DMA_REQ_FRAMES;
		data = malloc(sizeof(int));
		KASSERT(data);
		*data = f;

		_dmad_alloc_drb(ch_req, &drb);

		drb->src_addr	= pcm_data;
		drb->dst_addr	= (void *)I2SAC97_DR;
		drb->req_size	= (f << 1); /* units of data width (32bit for AC97) */
		drb->rcp	= rcp;
		drb->data	= data;

		pcm_data += (f << 1);
		g_buffered_frames += f;
//		DEBUG(1, 1, "FRAME: %d,%d\n", g_buffered_frames,ring_idx);
		_dmad_submit_request(ch_req, drb);
		frames -= f;
	}
}
