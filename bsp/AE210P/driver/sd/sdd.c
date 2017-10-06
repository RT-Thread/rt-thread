/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Aug.21.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *   sdd.c
 *
 * DESCRIPTION
 *
 *   SD driver implementation. (Nucleus I/O Driver Architecture)
 *
 * SDC CONTROL LOGIC
 *
 *   -------------------------------------------------------------------------
 *   SDC controls     <-> SDC Registers     <-> SD In-Card Controller
 *   -------------------------------------------------------------------------
 *   SD commands      <-> SDC CMD/RSP reg   <-> SD Command/Data Line
 *   -------------------------------------------------------------------------
 *   SD data          <-> SDC Data Window   <-> SD Memory
 *   -------------------------------------------------------------------------
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   sdd.h          SD driver common header file
 *
 ****************************************************************************/
#include "sdd.h"
#include "sdd_sd.h"
#include "../../library/ndsvfs/sys_arch.h"
#include "../../library/ndsvfs/include/ndsbdev.h"
#include "bsp_hal.h"

static uint32_t sdd_hisr_stack[SDD_HISR_STACK_SIZE];
/* driver context */
static SDD_DATA sdd __attribute__ ((aligned(4))) = { 0};
#if (SDD_VFS_SUPPORT)
// sdc block device context
static NDS_BDEV         sdd_bdev __attribute__((aligned(4))) = {0};
#endif  // SDD_VFS_SUPPORT

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_alloc_dma_channel
 *
 * DESCRIPTION
 *
 *   
 *   This function allocate a dma channel for use of sd data transfer.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   None
 *
 * OUTPUTS
 *
 *   None
 *
 ****************************************************************************/
static inline uint32_t _sdd_alloc_dma_channel(void)
{
	uint32_t status = HAL_SUCCESS;

	/*
	 * This is function is for code path simplification so it will not
	 * check validity of sdd struct again.
	 */

	/* Try APB DMA first ... */

	/* (in)  DMAD_DMAC_AHB_CORE, DMAD_DMAC_APB_CORE */
	sdd.dma_ch.controller = DMAD_DMAC_APB_CORE;

	/* (in)  Burst mode (0: no burst 1-, 1: burst 4- data cycles per dma cycle) */
	sdd.dma_ch.apbch_req.burst_mode = 0;

	/* (in)  APBBR_DATAWIDTH_4(word), APBBR_DATAWIDTH_2(half-word), APBBR_DATAWIDTH_1(byte) */
	sdd.dma_ch.apbch_req.data_width = APBBR_DATAWIDTH_4;

	/* (in)  APBBR_ADDRINC_xxx */
	sdd.dma_ch.apbch_req.src_addr_ctrl = APBBR_ADDRINC_FIXED;

	/* (in)  APBBR_REQN_xxx (also used to help determine bus selection) */
	sdd.dma_ch.apbch_req.src_index = _dmad_get_reqn(sdd.dma_ch.controller, APB_SDC);

	/* (in)  APBBR_ADDRINC_xxx */
	sdd.dma_ch.apbch_req.dst_addr_ctrl = APBBR_ADDRINC_I4X;

	/* (in)  APBBR_REQN_xxx (also used to help determine bus selection) */
	sdd.dma_ch.apbch_req.dst_index = APBBR_REQN_NONE;

	status = _dmad_channel_alloc(&sdd.dma_ch, HAL_TRUE);

	if (status != HAL_SUCCESS) {

		if (status != HAL_ERR_UNAVAILABLE)
			return status;

		/* Try AHB DMAC again for lucky ... */
		/* (in)  DMAD_DMAC_AHB_CORE, DMAD_DMAC_APB_CORE */
		sdd.dma_ch.controller = DMAD_DMAC_AHB_CORE;

		/* (in)  non-zero if src and dst have different clock domain */
		sdd.dma_ch.ahbch_req.sync = 1;

		/* (in)  DMAC_CSR_CHPRI_0 (lowest) ~ DMAC_CSR_CHPRI_3 (highest) */
		sdd.dma_ch.ahbch_req.priority = DMAC_CSR_CHPRI_0;

		/* (in)  non-zero to enable hardware handshake mode */
		sdd.dma_ch.ahbch_req.hw_handshake = 1;

		/* (in)  DMAC_CSR_SIZE_1 ~ DMAC_CSR_SIZE_256 */
		sdd.dma_ch.ahbch_req.burst_size = DMAC_CSR_SIZE_1;

		/* (in)  DMAC_CSR_WIDTH_8, DMAC_CSR_WIDTH_16, or DMAC_CSR_WIDTH_32 */
		sdd.dma_ch.ahbch_req.src_width = DMAC_CSR_WIDTH_32;

		/* (in)  DMAC_CSR_AD_INC, DMAC_CSR_AD_DEC, or DMAC_CSR_AD_FIX */
		sdd.dma_ch.ahbch_req.src_addr_ctrl = DMAC_CSR_AD_FIX;

		/* (in)  DMAC_REQN_xxx (also used to help determine channel number) */
		sdd.dma_ch.ahbch_req.src_index = DMAC_REQN_SDC;

		sdd.dma_ch.ahbch_req.src_reqn  = _dmad_get_reqn(sdd.dma_ch.controller, AHB_SDC);

		/* (in)  DMAC_CSR_WIDTH_8, DMAC_CSR_WIDTH_16, or DMAC_CSR_WIDTH_32 */
		sdd.dma_ch.ahbch_req.dst_width = DMAC_CSR_WIDTH_32;

		/* (in)  DMAC_CSR_AD_INC, DMAC_CSR_AD_DEC, or DMAC_CSR_AD_FIX */
		sdd.dma_ch.ahbch_req.dst_addr_ctrl = DMAC_CSR_AD_INC;

		/* (in)  DMAC_REQN_xxx (also used to help determine channel number) */
		sdd.dma_ch.ahbch_req.dst_index = DMAC_REQN_NONE;
		sdd.dma_ch.ahbch_req.dst_reqn  = AHB_REQN_NONE;

		status = _dmad_channel_alloc(&sdd.dma_ch, HAL_TRUE);
	}

	SDD_TRACE(("sdd dma channel(%d) controller(%d)\r\n",
				sdd.dma_ch.channel, sdd.dma_ch.controller));

	return status;
}

static inline void _sdd_free_dma_channel(void)
{
	_dmad_channel_free(&sdd.dma_ch);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_cd_reset
 *
 * DESCRIPTION
 *
 *   This function performs card-detection initialization and card remove
 *   clean-up tasks.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   insert     : non-zero to perform card-inserting tasks, zero for removing.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_cd_reset(uint8_t insert)
{
	uint32_t status = HAL_SUCCESS;	/* Return status code */
	SD_R32 sd_rsp32;	/* SD card command response 32-bit */
	SD_R128 sd_rsp128;	/* SD card command response 128-bit */
	char *tmp_str;
	uint32_t tmp_val;

	SDD_TRACE(("_sdd_cd_reset\r\n"));
	/* ------------ */
	/* Reset host SDC */
	SETB32(SDC_CMD, SDC_SDC_RST_BIT);
	while (GETB32(SDC_CMD, SDC_SDC_RST_BIT) != 0) ;

	/* Perform card removal tasks */
	if (insert != HAL_TRUE) {
		/* Stop pending DMA ? */

		/* Turn off SD bus power */
		CLRB32(SDC_PWR_CTL, SDC_SD_POWER_ON_BIT);

		/* Turn off SD bus clock */
		SETB32(SDC_CLK_CTL, SDC_CLK_DIS_BIT);

		/* Setup removed flag */
		sdd.card_desc.rca = 0;

#if (SDD_VFS_SUPPORT)
        // notify file system layer, if any ...
        if (sdd_bdev.propagate_event != HAL_NULL)
            sdd_bdev.propagate_event(&sdd_bdev, NDSBDEV_DEVICE_UNPLUG, HAL_NULL);
#endif  // SDD_VFS_SUPPORT
		return HAL_SUCCESS;
	}

	/* ------------ */
	/* Turn on SD card power using default voltage level */
	SETB32(SDC_PWR_CTL, SDC_SD_POWER_ON_BIT);
	_nds_kwait(0x1000);

	/* ------------ */
	/* Turn on SD bus clock, apply max freq-division value (smallest frequency) */
	OUT32(SDC_CLK_CTL, (SDC_CLK_ON << SDC_CLK_DIS_BIT) |
			(SDC_CLK_SD << SDC_CLK_SD_BIT) | SDC_CLK_DIV_MASK);

	_nds_kwait(0x1000);

	SDD_TRACE(("power-on & clock-on!\r\n"));

	/* Perform card initialization & identification process */

	/* Idle State -> Ready State */
	/* - CMD0 */
	SDD_TRACE(("CMD0\r\n"));
	status = _sd_cmd0();
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* - CMD8 */
	SDD_TRACE(("CMD8\r\n"));
	status = _sd_cmd8(SD_CMD8_MAKE_ARG(SD_VHS_2_7V_3_6V, SD_CMD8_DEFAULT_PTN), &sd_rsp32);

	if (status != HAL_SUCCESS) {

		if ((status != SDD_RSP_TIMEOUT) && (status != SDD_CMD_TIMEOUT))
			goto _err_exit;

		sdd.card_desc.version = SDD_SPEC_1XX;
	}
	else {
		/* version 2.0 or later card */

		/* validates CMD8 response */
		if ((SD_R7_GET_PTN(sd_rsp32) != 0xaa) || (SD_R7_GET_VHS(sd_rsp32) == 0x00)) {

			/* unusable card */
			status = SDD_INVALID_MEDIA;
			goto _err_exit;
		}

		sdd.card_desc.version = SDD_SPEC_200;
	}

	/* - ACMD41 */
	SDD_TRACE(("ACMD41\r\n"));
	{
		uint32_t retry = 0;
		uint32_t timeout = 1;
		uint32_t sd_hcs = SD_HCS_SD;	/* SD(0) or SDHC(1) for ACMD41 */

		/*
		 * HCS should be 0 if CMD8 does not response.
		 * HCS is 1 if host supports SDHC (AG101 does not support SDHC).
		 */

		 if (sdd.card_desc.version == SDD_SPEC_200)
		 {
		     sd_hcs = SD_HCS_SDHC;
		 }

		/* issue ACMD41 to get OCR */
		while (retry++ < SD_ACMD41_MAX_RETRY_COUNT) {

			/* cases: */
			/* - v2.0 or latter SD memory card - voltage mismatch */
			/* - v1.x SD memory card */
			/* - not SD memory card */
			SDD_TRACE(("cmd55\r\n"));

			/* notify card we're going to send an ACMD, RCA is 0x00 in card's idle state */
			status = _sd_cmd55(0x00, &sd_rsp32);
			if (status != HAL_SUCCESS)
				goto _err_exit;

			if (SD_CSR_GET_APP_CMD(sd_rsp32) == 0) {

				/* error if card was not expecting ACMD */
				status = SDD_NOT_SUPPORT_ACMD;
				goto _err_exit;
			}

			SDD_TRACE(("acmd41\r\n"));
			status = _sd_acmd41(SD_ACMD41_MAKE_ARG(sd_hcs), &sd_rsp32);
			if (status != HAL_SUCCESS) {

				/* no response - not a SD memory card */
				goto _err_exit;
			}

			/* Continue if the OCR power state is not ready yet */
			if (SD_OCR_GET_BUSY(sd_rsp32) == 1) {

				/* card power up status is ready */
				sdd.card_desc.card_ccs =
					((SD_OCR_GET_CCS(sd_rsp32) == SD_CCS_SDHC) ? SDD_CCS_SDHC : SDD_CCS_SD);

				sdd.card_desc.vdd_window = SD_OCR_GET_VDD(sd_rsp32);

				timeout = 0;
				break;
			}
		}

		if (timeout) {

			/*
			 * unusable card
			 * - no compatible voltage range (go to inactive state)
			 * - timeout (no resposne or timeout)
			 */
			SDD_TRACE(("timeout!\r\n"));
			status = SDD_INVALID_MEDIA;
			goto _err_exit;
		}
	}

	/* Ready State -> Identification State */
	/* - CMD2 */
	SDD_TRACE(("CMD2\r\n"));
	status = _sd_cmd2(&sd_rsp128);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	sdd.card_desc.mfg_id = SD_CID_GET_MID(sd_rsp128);	/* ID */

	tmp_str = (char *)SD_CID_GET_OID_PTR(sd_rsp128);	/* string */
	sdd.card_desc.oem_id[0] = tmp_str[0];
	sdd.card_desc.oem_id[1] = tmp_str[1];
	sdd.card_desc.oem_id[2] = 0x00;

	tmp_str = (char *)SD_CID_GET_PNM_PTR(sd_rsp128);	/* string */
	sdd.card_desc.prod_name[0] = tmp_str[0];
	sdd.card_desc.prod_name[1] = tmp_str[1];
	sdd.card_desc.prod_name[2] = tmp_str[2];
	sdd.card_desc.prod_name[3] = tmp_str[3];
	sdd.card_desc.prod_name[4] = tmp_str[4];
	sdd.card_desc.prod_name[5] = 0x00;

	tmp_val = (uint32_t) SD_CID_GET_PRV(sd_rsp128);	/* BCD */
	sdd.card_desc.prod_rev[0] = (char)((tmp_val >> 4) + 0x30);
	sdd.card_desc.prod_rev[1] = (char)'.';
	sdd.card_desc.prod_rev[2] = (char)((tmp_val & 0x0f) + 0x30);
	sdd.card_desc.prod_rev[3] = 0x00;

	sdd.card_desc.prod_sn = (uint32_t) SD_CID_GET_PSN(sd_rsp128);	/* 32-bit word value */

	tmp_val = (uint32_t) SD_CID_GET_MDT(sd_rsp128);	/* 12-bit value */
	sdd.card_desc.mfg_year = (uint16_t) (tmp_val >> 4) + 2000;
	sdd.card_desc.mfg_month = (uint16_t) (tmp_val & 0x0f);

	SDD_TRACE(("oem_id    : 0x%081x\r\n", sdd.card_desc.oem_id));

	SDD_TRACE(("prod_name : %s\r\n", sdd.card_desc.prod_name));

	SDD_TRACE(("prod_rev  : 0x%081x\r\n",sdd.card_desc.prod_rev));

	SDD_TRACE(("prod_sn   : 0x%08lx\r\n", sdd.card_desc.prod_sn));
	SDD_TRACE(("mfg_year  : %d\r\n", sdd.card_desc.mfg_year));
	SDD_TRACE(("mfg_month : %d\r\n", sdd.card_desc.mfg_month));

	/* Identification -> Standby State */

	/* - CMD3 */
	SDD_TRACE(("CMD3\r\n"));
	status = _sd_cmd3(&sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	if (SD_R6_GET_CSR_ERR(sd_rsp32)) {

		status = SDD_CMD_ERROR;
		goto _err_exit;
	}

	sdd.card_desc.rca = SD_R6_GET_RCA(sd_rsp32);
	SDD_TRACE(("New RCA: 0x%08lx\r\n", sdd.card_desc.rca));

	/*
	 * Get CSD register (Standby -> Standby)
	 * (Majorly we need the data access timing and SD bus clock)
	 */

	/* - CMD9 */
	SDD_TRACE(("Get CSD (CMD9)\r\n"));
	status = _sd_cmd9(sdd.card_desc.rca, &sd_rsp128);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	tmp_val = SD_CSD_GET_CSD_STRUCTURE(sd_rsp128);

	SDD_TRACE(("CSD r0: 0x%08lx\r\n", sd_rsp128.r[0]));
	SDD_TRACE(("CSD r1: 0x%08lx\r\n", sd_rsp128.r[1]));
	SDD_TRACE(("CSD r2: 0x%08lx\r\n", sd_rsp128.r[2]));
	SDD_TRACE(("CSD r3: 0x%08lx\r\n", sd_rsp128.r[3]));

	{
		static uint32_t taac_tu2ns[] = {
			/*
			 * Note: Due to minimum is 1, taac did not divided by 10 initially.
			 *       Values derived from this taac has to be divided by 10.
			 */
			1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
		};

		static uint32_t ts_tu2bps[] = {
			/*
			 * Note: Reserved index (4~7) will map to 0,
			 *       others are divided by 10 to avoid floating point operation.
			 */
			1000, 100000, 1000000, 10000000, 0, 0, 0, 0
		};

		static uint32_t taac_ts_tv2flt[] = {
			/*
			 * Note: Reserved index (0) will map to 0,
			 *       other value are multiplied with 10 to avoid floating point operation.
			 */
			0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60,
			70, 80
		};

		if (tmp_val == 0x00) {

			/* Standard SD */
			float sdc_clk_ns;	/* SDC to card bus clock */
			float sdc_read_to_ns, sdc_write_to_ns;	/* read/write timeout (ns) */

			SDD_TRACE(("CSD v1.0\r\n"));
			SDD_TRACE(("taac       : 0x%08lx\r\n", SD_CSD_GET_TAAC(sd_rsp128)));
			SDD_TRACE(("nsac       : 0x%08lx\r\n", SD_CSD_GET_NSAC(sd_rsp128)));

			/* CSD structure version */
			sdd.card_desc.csd_ver = 0x01;

			/* obtain card maximum transfer speed (bps) */
			tmp_val = SD_CSD_GET_TRAN_SPEED(sd_rsp128);

			sdd.card_desc.max_dataline_rate =
				(taac_ts_tv2flt[SD_TRAN_SPEED_TV(tmp_val)] *
				 ts_tu2bps[SD_TRAN_SPEED_TU(tmp_val)]);

			SDD_TRACE(("line_speed : 0x%08lx (bps)\r\n", sdd.card_desc.max_dataline_rate));

			/* AG101 SDC transfer speed limits */

			// if (sdd.card_desc.max_dataline_rate > 25000000)
			//     sdd.card_desc.max_dataline_rate = 25000000;

			/*
			 * assume we would like to reach the maximum transfer speed,
			 * backward derive SDC_CLK_DIC ...
			 */
			sdd.card_desc.sdc_clk_div =
				MB_PCLK / (sdd.card_desc.max_dataline_rate << 1);
			if (sdd.card_desc.sdc_clk_div > 0)
				sdd.card_desc.sdc_clk_div -= 1;

			/* obtain real SDC clock frequency  */
			sdd.card_desc.sdc_clk_freq =
				MB_PCLK / ((sdd.card_desc.sdc_clk_div + 1) << 1);

			/*
			 * obtain card read access time 1 (TAAC, ns)
			 * note that this is 10x value, use of taac has to be divide by 10.
			 */
			tmp_val = SD_CSD_GET_TAAC(sd_rsp128);

			sdd.card_desc.async_access_time =
				taac_ts_tv2flt[SD_TAAC_TV(tmp_val)] *
				taac_tu2ns[SD_TAAC_TU(tmp_val)];

			/* obtain card read access time 2 (NSAC * 100, clocks) */
			sdd.card_desc.read_access_clks = SD_CSD_GET_NSAC(sd_rsp128) * 100;	/* (NSAC * 100) Hz */

			/* obtain programming time multiplication factor */
			sdd.card_desc.prog_factor = (1 << SD_CSD_GET_R2W_FACTOR(sd_rsp128));

			/* obtain total read (TAAC + NSAC) & write (R2W * read) access timeout (x100) */
			sdc_clk_ns = 1000000000.0f / (float)sdd.card_desc.sdc_clk_freq;	/* SDC clock period (ns) */
			sdc_read_to_ns =
				(float)sdd.card_desc.read_access_clks * sdc_clk_ns * 100.0f +
				(float)sdd.card_desc.async_access_time * 10.0f;

			sdc_write_to_ns = (float)sdd.card_desc.prog_factor * sdc_read_to_ns;

			/* obtain read and write timeout value */
			/* read_timeout = min(100ms, 100 x read_access_time_ms) */
			if (sdc_read_to_ns > 100000000.0f)
				sdc_read_to_ns = 100000000.0f;

			sdd.card_desc.read_timeout_clks = (uint32_t) (sdc_read_to_ns / sdc_clk_ns);

			/* write_timeout = min(100ms, 100 x write_access_time_ms) */
			if (sdc_write_to_ns > 100000000.0f)
				sdc_write_to_ns = 100000000.0f;

			sdd.card_desc.write_timeout_clks = (uint32_t) (sdc_write_to_ns / sdc_clk_ns);

			/* command class support list */
			sdd.card_desc.cmd_class = SD_CSD_GET_CCC(sd_rsp128);

			/* read parameters */

			/* should be 512, 1024, or 2048 */
			sdd.card_desc.max_read_block_len = (uint16_t) (1 << SD_CSD_GET_READ_BL_LEN(sd_rsp128));

			/* should be 1 for SD memory card */
			sdd.card_desc.partial_block_read = (uint8_t) SD_CSD_GET_READ_BL_PARTIAL(sd_rsp128);
			sdd.card_desc.read_block_misalign = (uint8_t) SD_CSD_GET_READ_BLK_MISALIGN(sd_rsp128);	/* 0 or 1 */

			/* write parameters */
			sdd.card_desc.max_write_block_len = (uint16_t) (1 << SD_CSD_GET_WRITE_BL_LEN(sd_rsp128));	/* should be same as read-block size in SD memory card */
			sdd.card_desc.partial_block_write = (uint8_t) SD_CSD_GET_WRITE_BL_PARTIAL(sd_rsp128);	/* 0 or 1 */
			sdd.card_desc.write_block_misalign = (uint8_t) SD_CSD_GET_WRITE_BLK_MISALIGN(sd_rsp128);	/* 0 or 1 */

			/* erase parameters */
			sdd.card_desc.erase_single_block = (uint8_t) SD_CSD_GET_ERASE_BLK_EN(sd_rsp128);	/* 0 or 1 */
			sdd.card_desc.erase_sector_size = (uint8_t) SD_CSD_GET_SECTOR_SIZE(sd_rsp128);	/* 0~127 means 1~128 number of write block size */
			sdd.card_desc.file_format = (uint8_t) SD_CSD_GET_FILE_FORMAT(sd_rsp128);

			/* write protect parameters */
			sdd.card_desc.wp_group_size = (uint8_t) SD_CSD_GET_WP_GRP_SIZE(sd_rsp128);	/* 0~127 means 1~128 number of erase sector size */
			sdd.card_desc.wp_group_enable = (uint8_t) SD_CSD_GET_WP_GRP_ENABLE(sd_rsp128);	/* 0 or 1 */
			sdd.card_desc.wp_permanent = (uint8_t) SD_CSD_GET_PERM_WRITE_PROTECT(sd_rsp128);	/* 0 or 1 */
			sdd.card_desc.wp_temp = (uint8_t) SD_CSD_GET_TMP_WRITE_PROTECT(sd_rsp128);	/* 0 or 1 */

			/* other parameters */
			sdd.card_desc.copy = (uint8_t) SD_CSD_GET_COPY(sd_rsp128);	/* 0 or 1 */
			sdd.card_desc.dsr_imp = (uint8_t) SD_CSD_GET_DSR_IMP(sd_rsp128);	/* 0 or 1 */

			/* card capacity parameters */
			sdd.card_desc.c_size = (uint32_t) SD_CSD1_GET_C_SIZE(sd_rsp128);	/* 12-bit value */
			sdd.card_desc.c_size_mult = (uint32_t) SD_CSD1_GET_C_SIZE_MULT(sd_rsp128);	/* 3-bit value */

			/* calculate card capacity of user data (unit of 512-bytes) */
			sdd.card_desc.card_capacity =
				((sdd.card_desc.c_size +
				  1) * (1 << (sdd.card_desc.c_size_mult + 2))) >> 9;
			sdd.card_desc.card_capacity *=
				sdd.card_desc.max_read_block_len;
		}
		else if (tmp_val == 0x01) {
			/* SDHC (or Standard SD with CSD 2.0?) */
			/*static uint32_t soc_pclk = 50000000;  // (assume PCLK 50M) todo: fix it! */
			float sdc_clk_ns;

			SDD_TRACE(("CSD v2.0\r\n"));
			SDD_TRACE(("taac(r/o)  : 0x%08lx\r\n",
						SD_CSD_GET_TAAC(sd_rsp128)));
			SDD_TRACE(("nsac(r/o)  : 0x%08lx\r\n",
						SD_CSD_GET_NSAC(sd_rsp128)));

			/* CSD structure version */
			sdd.card_desc.csd_ver = 0x02;

			/* obtain card maximum transfer speed (bps) */
			tmp_val = SD_CSD_GET_TRAN_SPEED(sd_rsp128);	/* same as 1.0 */
			sdd.card_desc.max_dataline_rate =
				(taac_ts_tv2flt[SD_TRAN_SPEED_TV(tmp_val)] *
				 ts_tu2bps[SD_TRAN_SPEED_TU(tmp_val)]);
			SDD_TRACE(("line_speed : 0x%08lx (bps)\r\n",
						sdd.card_desc.max_dataline_rate));

			/* AG101 SDC transfer speed limits */
			// if (sdd.card_desc.max_dataline_rate > 25000000)
			//     sdd.card_desc.max_dataline_rate = 25000000;

			/*
			 * assume we would like to reach the maximum transfer speed,
			 * backward derive SDC_CLK_DIC ...
			 */
			sdd.card_desc.sdc_clk_div =
				MB_PCLK / (sdd.card_desc.max_dataline_rate << 1);
			if (sdd.card_desc.sdc_clk_div > 0)
				sdd.card_desc.sdc_clk_div -= 1;

			/* obtain real SDC clock frequency  */
			sdd.card_desc.sdc_clk_freq =
				MB_PCLK / ((sdd.card_desc.sdc_clk_div + 1) << 1);

			/* obtain card read access time 1 (TAAC, ns) */
			/* note that this is 10x value, use of taac has to be divide by 10. */

			// tmp_val = SD_CSD_GET_TAAC(sd_rsp128);
			// sdd.card_desc.async_access_time =
			//     taac_ts_tv2flt[SD_TAAC_TV(tmp_val)] * taac_tu2ns[SD_TAAC_TU(tmp_val)];

			/* obtain card read access time 2 (NSAC * 100, clocks) */
			// sdd.card_desc.read_access_clks = SD_CSD_GET_NSAC(sd_rsp128) * 100;  // (NSAC * 100) Hz */

			/* obtain programming time multiplication factor */
			sdd.card_desc.prog_factor = (1 << SD_CSD_GET_R2W_FACTOR(sd_rsp128));	/* should be 4 */

			/* obtain total read (TAAC + NSAC) & write (R2W * read) access timeout (x100) */
			sdc_clk_ns = 1000000000.0f / (float)sdd.card_desc.sdc_clk_freq;	/* SDC clock period (ns) */

			/* obtain read and write timeout value */
			sdd.card_desc.read_timeout_clks = (uint32_t) (100000000.0f / sdc_clk_ns);	/* 100ms according to spec 2.0 */
			sdd.card_desc.write_timeout_clks = (uint32_t) (250000000.0f / sdc_clk_ns);	/* 250ms according to spec 2.0 */

			/* command class support list */
			sdd.card_desc.cmd_class = SD_CSD_GET_CCC(sd_rsp128);	/* same as 1.0 */

			/* read parameters */
			sdd.card_desc.max_read_block_len = (uint16_t) (1 << SD_CSD_GET_READ_BL_LEN(sd_rsp128));	/* should be 512 bytes */
			sdd.card_desc.partial_block_read = (uint8_t) SD_CSD_GET_READ_BL_PARTIAL(sd_rsp128);	/* should be 0 */
			sdd.card_desc.read_block_misalign = (uint8_t) SD_CSD_GET_READ_BLK_MISALIGN(sd_rsp128);	/* should be 0 */

			/* write parameters */
			sdd.card_desc.max_write_block_len = (uint16_t) (1 << SD_CSD_GET_WRITE_BL_LEN(sd_rsp128));	/* should be 512 bytes */
			sdd.card_desc.partial_block_write = (uint8_t) SD_CSD_GET_WRITE_BL_PARTIAL(sd_rsp128);	/* should be 0 */
			sdd.card_desc.write_block_misalign = (uint8_t) SD_CSD_GET_WRITE_BLK_MISALIGN(sd_rsp128);	/* should be 0 */

			/* erase parameters */
			sdd.card_desc.erase_single_block = (uint8_t) SD_CSD_GET_ERASE_BLK_EN(sd_rsp128);	/* should be 1 */
			sdd.card_desc.erase_sector_size = (uint8_t) SD_CSD_GET_SECTOR_SIZE(sd_rsp128);	/* should be 64 KBytes (not relate to erase) */
			sdd.card_desc.file_format = (uint8_t) SD_CSD_GET_FILE_FORMAT(sd_rsp128);	/* should be 0 */

			/* write protect parameters */
			sdd.card_desc.wp_group_size = (uint8_t) SD_CSD_GET_WP_GRP_SIZE(sd_rsp128);	/* should be 0 */
			sdd.card_desc.wp_group_enable = (uint8_t) SD_CSD_GET_WP_GRP_ENABLE(sd_rsp128);	/* should be 0 */
			sdd.card_desc.wp_permanent = (uint8_t) SD_CSD_GET_PERM_WRITE_PROTECT(sd_rsp128);	/* same as 1.0 */
			sdd.card_desc.wp_temp = (uint8_t) SD_CSD_GET_TMP_WRITE_PROTECT(sd_rsp128);	/* same as 1.0 */

			/* other parameters */
			sdd.card_desc.copy = (uint8_t) SD_CSD_GET_COPY(sd_rsp128);	/* same as 1.0 */
			sdd.card_desc.dsr_imp = (uint8_t) SD_CSD_GET_DSR_IMP(sd_rsp128);	/* same as 1.0 */

			/* card capacity parameters */
			sdd.card_desc.c_size =
				(uint32_t) SD_CSD2_GET_C_SIZE(sd_rsp128);

			/* calculate card capacity of user data (unit of 512-bytes) */
			sdd.card_desc.card_capacity = sdd.card_desc.c_size + 1;	/* (c_size + 1) * 512 / 512 (KBytes) */
			sdd.card_desc.card_capacity *=
			     sdd.card_desc.max_read_block_len;
		}
		else {
			SDD_TRACE(("Unknown CSD version!\r\n"));

			sdd.card_desc.csd_ver = 0x00;
			status = SDD_INVALID_MEDIA;
			goto _err_exit;
		}
	}

	SDD_TRACE(("card_capacity: 0x%08lx (KB)\r\n", sdd.card_desc.card_capacity));
	SDD_TRACE(("clk_div: 0x%08lx\r\n", sdd.card_desc.sdc_clk_div));
	SDD_TRACE(("clk_freq: %d Hz\r\n", sdd.card_desc.sdc_clk_freq));
	SDD_TRACE(("read_timeout_clks: 0x%08lx\r\n", sdd.card_desc.read_timeout_clks));
	SDD_TRACE(("write_timeout_clks: 0x%08lx\r\n", sdd.card_desc.write_timeout_clks));

	/* ------------ */
	/* Now we know how to setup SD bus clock for maximum data transfer rate ... */
	OUT32(SDC_CLK_CTL, (SDC_CLK_ON << SDC_CLK_DIS_BIT) | (SDC_CLK_SD << SDC_CLK_SD_BIT) |
			((sdd.card_desc.sdc_clk_div << SDC_CLK_DIV_SHIFT) & SDC_CLK_DIV_MASK));
	_nds_kwait(0x1000);

	/* ------------ */
	/*
	 * Get SCR register (Standby -> Transfer -> Standby)
	 * (Majorly we need the data bus width)
	 */
	SDD_TRACE(("Get SCR\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);	/* standby -> transfer */
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/*
	 * send SD command to setup read-block-size
	 * (SD memory card read block size could smaller than 512)
	 */
	SDD_TRACE(("cmd16\r\n"));
	status = _sd_cmd16(8, &sd_rsp32);	/* read 64 bits data */
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* set SDC data timeout register */
	// OUT32(SDC_DATA_TIMER, 0xffffffff);  /* use sdd.card_desc.read_timeout_clks ? */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.read_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, 8);	/* read 64 bits data */

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | ((3 << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^3 = 8 bytes */

	/* send SD command to readback SCR register */
	SDD_TRACE(("cmd55\r\n"));
	status = _sd_cmd55(sdd.card_desc.rca, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	SDD_TRACE(("acmd51\r\n"));
	status = _sd_acmd51(&sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* pio-mode read-back */
	tmp_val = 0;
	while (tmp_val++ < SD_READ_MAX_RETRY_COUNT) {

		uint32_t sdc_status = IN32(SDC_STATUS);

		if (sdc_status & (SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK | SDC_SR_DATA_CRC_FAIL_MASK)) {

			status = SDD_READ_DATA_ERROR;
			goto _err_exit;
		}

		if (sdc_status & (SDC_SR_FIFO_ORUN_MASK | SDC_SR_DATA_END_MASK))
			break;
	}

	/* ACMD51/ACMD13 data are MSB first (big-endian) */
	sd_rsp128.r[3] = IN32(SDC_DATA_WIN);	/* [63:32] BE */
	sd_rsp128.r[2] = IN32(SDC_DATA_WIN);	/* [31:00] BE */

	/* reorder byte endian inside the 32-bit word */
	sd_rsp128.b[0] = sd_rsp128.b[11];
	sd_rsp128.b[1] = sd_rsp128.b[10];
	sd_rsp128.b[2] = sd_rsp128.b[9];
	sd_rsp128.b[3] = sd_rsp128.b[8];
	sd_rsp128.b[4] = sd_rsp128.b[15];
	sd_rsp128.b[5] = sd_rsp128.b[14];
	sd_rsp128.b[6] = sd_rsp128.b[13];
	sd_rsp128.b[7] = sd_rsp128.b[12];

	sdd.card_desc.scr_ver = (uint8_t) SD_SCR_GET_SCR_STRUCTURE(sd_rsp128);
	sdd.card_desc.spec_ver = (uint8_t) SD_SCR_GET_SD_SPEC(sd_rsp128);
	sdd.card_desc.erase_val = (uint8_t) SD_SCR_GET_DATA_STAT_AFTER_ERASE(sd_rsp128);
	sdd.card_desc.security_ver = (uint8_t) SD_SCR_GET_SD_SECURITY(sd_rsp128);
	sdd.card_desc.bus_width = (uint8_t) SD_SCR_GET_SD_BUS_WIDTHS(sd_rsp128);

	SDD_TRACE(("lw       : 0x%08lx\r\n", sd_rsp128.r[2]));
	SDD_TRACE(("hw       : 0x%08lx\r\n", sd_rsp128.r[3]));
	SDD_TRACE(("SCR_ver  : 0x%08lx\r\n", sdd.card_desc.scr_ver));
	SDD_TRACE(("spec_ver : 0x%08lx\r\n", sdd.card_desc.spec_ver));
	SDD_TRACE(("erase_val: 0x%08lx\r\n", sdd.card_desc.erase_val));
	SDD_TRACE(("secu_ver : 0x%08lx\r\n", sdd.card_desc.security_ver));
	SDD_TRACE(("bus_width: 0x%08lx\r\n", sdd.card_desc.bus_width));

	if ((IN32(SDC_BUS_WIDTH) & SDC_WIDE_BUS_SUPPORT_MASK) &&
			(sdd.card_desc.bus_width & 0x04)) {

		SDD_TRACE(("SDC configured to wide bus!\r\n"));

		SDD_TRACE(("cmd55\r\n"));
		status = _sd_cmd55(sdd.card_desc.rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			goto _err_exit;

		SDD_TRACE(("acmd6\r\n"));
		status = _sd_acmd6(SD_ACMD6_MAKE_ARG(SD_BUS_WIDTH_ARG_4BIT), &sd_rsp32);
		if (status != HAL_SUCCESS)
			goto _err_exit;

		SDD_TRACE(("sdc_bus_width\r\n"));
		OUT32(SDC_BUS_WIDTH, SDC_WIDE_BUS_SUPPORT_MASK | SDC_WIDE_BUS_MASK);
	}
	else {
		SDD_TRACE(("SDC configured to single bus!\r\n"));

		SDD_TRACE(("cmd55\r\n"));
		status = _sd_cmd55(sdd.card_desc.rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			goto _err_exit;

		SDD_TRACE(("acmd6\r\n"));
		status = _sd_acmd6(SD_ACMD6_MAKE_ARG(SD_BUS_WIDTH_ARG_1BIT), &sd_rsp32);
		if (status != HAL_SUCCESS)
			goto _err_exit;

		OUT32(SDC_BUS_WIDTH, SDC_WIDE_BUS_SUPPORT_MASK | SDC_SINGLE_BUS_MASK);
	}

	/* transfer -> standby */
	// status = _sd_deselect_card(sdd.card_desc.rca);
	// if (status != HAL_SUCCESS)
	//     goto _err_exit;

	/*
	 * Turn on SD card power using voltage level obtained from card OCR
	 * todo: use default? flib doesn't setup voltage value?
	 */
	// SETB32(SDC_PWR_CTL, SDC_SD_POWER_ON_BIT);
	// _nds_kwait(0x1000);

	return HAL_SUCCESS;

_err_exit:

	SDD_TRACE(("_err_exit!\r\n"));

	/* Turn off SD bus power */
	CLRB32(SDC_PWR_CTL, SDC_SD_POWER_ON_BIT);

	/* Turn off SD bus clock */
	SETB32(SDC_CLK_CTL, SDC_CLK_DIS_BIT);

	/* Setup removed flag */
	sdd.card_desc.rca = 0;
#if (SDD_VFS_SUPPORT)
    // notify file system layer, if any ...
    if (sdd_bdev.propagate_event != HAL_NULL)
        sdd_bdev.propagate_event(&sdd_bdev, NDSBDEV_DEVICE_UNPLUG, HAL_NULL);
#endif  // SDD_VFS_SUPPORT

	return status;
}

#if 0
/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_read_sector_pio
 *
 * DESCRIPTION
 *
 *   This function performs a sector of data PIO transfer from the SD memory
 *   card.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   sector_cnt :
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sdd_read_sector_pio(uint32_t sector, uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	uint32_t sdc_status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;
	uint32_t word_cnt;
	uint32_t fifo_depth;

	SDD_TRACE(("\r\n_sdd_read_sector_pio\r\n"));

	if (sector > (sdd.card_desc.card_capacity << 1)) {
		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	/* todo: sector size */

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* send SD command to setup read-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.read_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to readback data */
	SDD_TRACE(("- cmd17\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd17(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd17(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _err_exit;

	SDD_TRACE(("- wait until card is sending out data\r\n"));
	_nds_kwait(0x1000);	/* hw need delay ? */
	/*status = _sd_wait_sending_state(sdd.card_desc.rca); */
	/*if (status != HAL_SUCCESS) */
	/*    goto _err_exit; */

	SDD_TRACE(("- read back data\r\n"));

	/* per 32-bit word read back */
	word_cnt = SDD_SECTOR_SIZE >> 2;
	while (word_cnt > 0) {
		retry = 0;
		while (retry++ < SD_READ_MAX_RETRY_COUNT) {
			sdc_status = IN32(SDC_STATUS);
			if (sdc_status &
					(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK
					 | SDC_SR_DATA_CRC_FAIL_MASK)) {
				SDD_TRACE(("- data error/timeout or card removed, sdc_status: 0x%08lx\r\n", sdc_status));
				status = SDD_READ_DATA_ERROR;
				goto _err_exit;
			}
			if (sdc_status &
					(SDC_SR_FIFO_ORUN_MASK | SDC_SR_DATA_END_MASK)) {
				SETB32(SDC_CLEAR, SDC_FIFO_ORUN_BIT);
				retry = 0xffffffff;	/* success */
				break;
			}
		}

		if (retry != 0xffffffff) {
			/* wait data timeout */
			SDD_TRACE(("- timeout, sdc_status: 0x%08lx\r\n",
						sdc_status));
			status = SDD_READ_DATA_ERROR;
			goto _err_exit;
		}

		fifo_depth = SDC_FIFO_WORD_DEPTH;
		while (fifo_depth-- > 0) {
			/* CMD17/18/24/25 ACMD18/25 data are LSB first (little-endian) */
			*((uint32_t *) io_buff) = IN32(SDC_DATA_WIN);	/* just mem-move so no data endian issue. */

			io_buff += 4;
			if (--word_cnt == 0)
				break;
		}
	}

	SDD_TRACE(("- data read completed\r\n"));
	return HAL_SUCCESS;

_err_exit:

	SDD_TRACE(("- error on data read\r\n"));
	return status;
}
#endif

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_read_sectors_pio
 *
 * DESCRIPTION
 *
 *   This function performs PIO data transfer from the SD memory card in
 *   multiple unit of sectors.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   sector_cnt :
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_read_sectors_pio(uint32_t sector, uint32_t sector_cnt,
		uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	uint32_t sdc_status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;
	uint32_t word_cnt;
	uint32_t fifo_depth;

	SDD_TRACE(("\r\n_sdd_read_sectors_pio\r\n"));

	if (sector > (sdd.card_desc.card_capacity << 1)) {

		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	if ((sector_cnt == 0) || (((sector + sector_cnt) > (sdd.card_desc.card_capacity << 1)))) {

		SDD_TRACE(("Invalid sector address range!\r\n"));
		return SDD_INVLAID_ADDR_RANGE;
	}

	/* todo: sector size */

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* send SD command to setup read-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.read_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, sector_cnt * SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to readback data */
	SDD_TRACE(("- cmd18\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd18(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd18(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _err_exit;

	SDD_TRACE(("- wait until card is sending out data\r\n"));
	_nds_kwait(0x1000);	/* hw need delay ? */

	/* This method will dirty SDC_STATUS so not been used. */
	// status = _sd_wait_sending_state(sdd.card_desc.rca);
	// if (status != HAL_SUCCESS)
	//     goto _err_exit;

	/* per sector PIO read back */
	OUT32(SDC_CLEAR, 0x3ff);
	SDD_TRACE(("- read back data\r\n"));
	while (sector_cnt-- > 0) {

		/* per 32-bit word read back */
		word_cnt = SDD_SECTOR_SIZE >> 2;
		while (word_cnt > 0) {
			retry = 0;
			while (retry++ < SD_READ_MAX_RETRY_COUNT) {

				sdc_status = IN32(SDC_STATUS);
				if (sdc_status &
						(SDC_SR_CARD_DETECT_MASK |
						 SDC_SR_DATA_TIMEOUT_MASK |
						 SDC_SR_DATA_CRC_FAIL_MASK)) {
					SDD_TRACE(("- data error/timeout or card removed, sdc_status: 0x%08lx\r\n", sdc_status));
					status = SDD_READ_DATA_ERROR;
					goto _err_exit;
				}
				if (sdc_status & (SDC_SR_FIFO_ORUN_MASK | SDC_SR_DATA_END_MASK)) {

					retry = 0xffffffff;	/* success */
					break;
				}
			}

			if (retry != 0xffffffff) {

				/* wait data timeout */
				SDD_TRACE(("- timeout, sdc_status: 0x%08lx\r\n", sdc_status));
				status = SDD_READ_DATA_ERROR;
				goto _err_exit;
			}

			fifo_depth = SDC_FIFO_WORD_DEPTH;
			SETB32(SDC_CLEAR, SDC_FIFO_ORUN_BIT);
			while (fifo_depth-- > 0) {

				/* CMD17/18/24/25 ACMD18/25 data are LSB first (little-endian) */
				*((uint32_t *) io_buff) = IN32(SDC_DATA_WIN);	/* just mem-move so no data endian issue. */

				io_buff += 4;
				if (--word_cnt == 0)
					break;
			}
		}
	}

	_nds_kwait(0x1000);	/* hw need delay ? */

	/* Stop data transmission */
	SDD_TRACE(("- stop transmission\r\n"));
	status = _sd_stop_transmission(sdd.card_desc.rca);
	/* FIXME this part is marked for qemu */
#if 0
	if (status != HAL_SUCCESS)
		goto _err_exit;
#endif
	SDD_TRACE(("- data read completed\r\n"));
	return HAL_SUCCESS;

_err_exit:

	SDD_TRACE(("- error on data read! status(0x%08lx)\r\n", status));
	return status;
}

extern int dmad_apb_config_dir(const DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t dir);
/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_read_sectors_dma
 *
 * DESCRIPTION
 *
 *   This function performs DMA data transfer from the SD memory card in
 *   multiple unit of sectors.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   sector_cnt :
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_read_sectors_dma(uint32_t sector, uint32_t sector_cnt,
		uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	SD_R32 sd_rsp32;
	DMAD_DRB *drb;

	SDD_TRACE(("\r\n_sdd_read_sectors_dma\r\n"));
	if (sector > (sdd.card_desc.card_capacity << 1)) {

		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	if ((sector_cnt == 0) || (((sector + sector_cnt) > (sdd.card_desc.card_capacity << 1)))) {

		SDD_TRACE(("Invalid sector address range!\r\n"));
		return SDD_INVLAID_ADDR_RANGE;
	}
	/* todo: sector size */

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _safe_exit;

	/* send SD command to setup read-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _safe_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.read_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, sector_cnt * SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | SDC_DMA_EN_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to readback data */
	SDD_TRACE(("- cmd18\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd18(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd18(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _safe_exit;

	SDD_TRACE(("- wait until card is sending out data\r\n"));
	// _nds_kwait(0x1000);	/* hw need delay ? */

	/* This method will dirty SDC_STATUS so not been used. */
	// status = _sd_wait_sending_state(sdd.card_desc.rca);
	// if (status != HAL_SUCCESS)
	//     goto _err_exit;

	/* per sector DMA read back */
	/* CMD17/18/24/25 ACMD18/25 data are LSB first (little-endian) */
	SDD_TRACE(("- read back data\r\n"));

	dmad_apb_config_dir(&sdd.dma_ch,DMAD_DIR_A0_TO_A1);	

	while (sector_cnt-- > 0) {

		status = _dmad_alloc_drb(&sdd.dma_ch, &drb);
		if (status != HAL_SUCCESS)
			goto _safe_exit;

		drb->src_addr = (void *)SDC_DATA_WIN;
		drb->dst_addr = (void *)io_buff;
		drb->req_size = SDD_SECTOR_SIZE >> 2;	/* multiple counts of transfer width */

		if (sector_cnt == 0)
			drb->completion_sem = &sdd.dma_sem;

		/* Submit DRB */
		status = _dmad_submit_request(&sdd.dma_ch, drb);
		if (status != HAL_SUCCESS)
			goto _safe_exit;

		/* Point to next buffer location */
		io_buff += SDD_SECTOR_SIZE;
	}

	/* Wait DMA completion */
	/* - method 1: sync with semaphore */
	/* - method 2: check SDC status register SDC_STATUS[7] */
	if (1){

		DEBUG(0, 1, "- wait dma completion ...\n");
		status = hal_pend_semaphore(&sdd.dma_sem, 300);

		if (status == HAL_ERR_TIMEOUT) {

			DEBUG(1, 1, "- wait dma completion timeout (might not an error)\n");
			goto _safe_exit;
		}
		else if (status != HAL_SUCCESS) {

			DEBUG(1, 1, "- wait dma completion failed! (0x%08lx)\n", status);
			goto _safe_exit;
		}
	}
	else {
		uint32_t retry = 0;
		uint32_t sdc_status;

		SDD_TRACE(("- polling dma completion status ...\r\n"));
		while (retry++ < SD_READ_MAX_RETRY_COUNT) {

			sdc_status = IN32(SDC_STATUS);
			if (sdc_status &
					(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK
					 | SDC_SR_DATA_CRC_FAIL_MASK)) {

				SDD_TRACE(("- data error/timeout or card removed, sdc_status: 0x%08lx\r\n", sdc_status));
				status = SDD_READ_DATA_ERROR;
				break;	/* todo: report error to upper layer? */
			}
			if (sdc_status & (SDC_SR_FIFO_ORUN_MASK | SDC_SR_DATA_END_MASK)) {

				SETB32(SDC_CLEAR, SDC_FIFO_ORUN_BIT);
				retry = 0xffffffff;	/* success */
				break;
			}
		}
	}

	/* Stop data transmission anyway after waiting. */
	SDD_TRACE(("- stop transmission\r\n"));
	status = _sd_stop_transmission(sdd.card_desc.rca);
	/* FIXME this part is marked for qemu */
#if 0
	if (status != HAL_SUCCESS)
		goto _safe_exit;
#endif
	status = HAL_SUCCESS;
_safe_exit:

#if (SDD_DEBUG_TRACE)
	if (status == HAL_SUCCESS)
		SDD_TRACE(("- data read completed\r\n"));
	else
		SDD_TRACE(("- error on data read\r\n"));
#endif /* SDD_DEBUG_TRACE */

	return status;
}

#if 0
/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_write_sector_pio
 *
 * DESCRIPTION
 *
 *   This function performs a sector of data PIO transfer to the SD memory
 *   card.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sdd_write_sector_pio(uint32_t sector, uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	uint32_t sdc_status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;
	uint32_t word_cnt;
	uint32_t fifo_depth;

	SDD_TRACE(("\r\n_sdd_write_sector_pio\r\n"));

	if (sector > (sdd.card_desc.card_capacity << 1)) {
		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	if (GETB32(SDC_STATUS, SDC_SR_WRITE_PROT_BIT)) {
		SDD_TRACE(("Card is write protected!\r\n"));
		return SDD_WRITE_PROTECTED;
	}

	/* todo: sector size */

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* send SD command to setup write-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.write_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | SDC_DATA_WRITE_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to write data */
	SDD_TRACE(("- cmd24\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd24(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd24(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _err_exit;

	SDD_TRACE(("- wait ready to write out data\r\n"));
	_nds_kwait(0x1000);	/* hw need delay ? */
	/*status = _sd_wait_receiving_state(sdd.card_desc.rca);  // This method look not necessary for writing. */
	/*if (status != HAL_SUCCESS) */
	/*    goto _err_exit; */

	/* per sector PIO write out */
	SDD_TRACE(("- write out data\r\n"));

	/* clear SDC status bits before sending data */
	OUT32(SDC_CLEAR, SDC_CLEAR_ALL);

	/* per 32-bit word write out */
	word_cnt = SDD_SECTOR_SIZE >> 2;
	while (word_cnt > 0) {
		fifo_depth = SDC_FIFO_WORD_DEPTH;
		while (fifo_depth-- > 0) {
			/* CMD17/18/24/25 ACMD18/25 data are LSB first (little-endian) */
			OUT32(SDC_DATA_WIN, *((uint32_t *) io_buff));	/* just mem-move so no data endian issue. */

			io_buff += 4;
			if (--word_cnt == 0)
				goto _complete_exit;
		}

		retry = 0;
		while (retry++ < SD_WRITE_MAX_RETRY_COUNT) {
			sdc_status = IN32(SDC_STATUS);
			if (sdc_status &
					(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK
					 | SDC_SR_DATA_CRC_FAIL_MASK)) {
				status = SDD_WRITE_DATA_ERROR;
				goto _err_exit;
			}
			if (sdc_status &
					(SDC_SR_FIFO_URUN_MASK | SDC_SR_DATA_END_MASK)) {
				SETB32(SDC_CLEAR, SDC_FIFO_URUN_BIT);
				retry = 0xffffffff;	/* success */
				break;
			}
		}

		if (retry != 0xffffffff) {
			/* wait data timeout */
			SDD_TRACE(("- timeout, sdc_status: 0x%08lx\r\n",
						sdc_status));

			/*SDD_TRACE(("- wait again by polling CSR\r\n")); */
			/*status = _sd_wait_receiving_state(sdd.card_desc.rca); */
			/*if (status != HAL_SUCCESS) */
			goto _err_exit;

			/*SDD_TRACE(("- card ready, sdc_status: 0x%08lx\r\n", IN32(SDC_STATUS))); */
		}
	}

_complete_exit:

	/* Wait host SDC shift-out FIFO data */
	SDD_TRACE(("- final check sdc_status\r\n"));
	retry = 0;
	while (retry++ < SD_WRITE_MAX_RETRY_COUNT) {
		sdc_status = IN32(SDC_STATUS);
		if (sdc_status &
				(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK |
				 SDC_SR_DATA_CRC_FAIL_MASK)) {
			status = SDD_WRITE_DATA_ERROR;
			goto _err_exit;
		}
		if ((sdc_status == 0) || (sdc_status & SDC_SR_DATA_END_MASK)) {
			break;
		}
	}

	SDD_TRACE(("- data write completed\r\n"));
	return HAL_SUCCESS;

_err_exit:

	SDD_TRACE(("- error on data write\r\n"));
	return status;
}
#endif

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_write_sectors_pio
 *
 * DESCRIPTION
 *
 *   This function performs PIO data transfer to the SD memory card in
 *   multiple unit of sectors.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   sector_cnt :
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_write_sectors_pio(uint32_t sector, uint32_t sector_cnt,
		uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	uint32_t sdc_status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;
	uint32_t word_cnt;
	uint32_t fifo_depth;

	if (sector > (sdd.card_desc.card_capacity << 1)) {

		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	if ((sector_cnt == 0) || (((sector + sector_cnt) > (sdd.card_desc.card_capacity << 1)))) {

		SDD_TRACE(("Invalid sector address range!\r\n"));
		return SDD_INVLAID_ADDR_RANGE;
	}

	if (GETB32(SDC_STATUS, SDC_SR_WRITE_PROT_BIT)) {

		SDD_TRACE(("Card is write protected!\r\n"));
		return SDD_WRITE_PROTECTED;
	}

	/* todo: sector size */

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* send SD command to setup write-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _err_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.write_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, sector_cnt * SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | SDC_DATA_WRITE_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to write data */
	SDD_TRACE(("- cmd25\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd25(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd25(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _err_exit;

	SDD_TRACE(("- wait ready to write out data\r\n"));
	_nds_kwait(0x1000);	/* hw need delay ? */

	/* This method look not necessary for writing. */
	// status = _sd_wait_receiving_state(sdd.card_desc.rca);
	// if (status != HAL_SUCCESS) */
	//     goto _err_exit; */

	/* per sector PIO write out */
	OUT32(SDC_CLEAR, 0x3ff);
	SDD_TRACE(("- write out data\r\n"));
	while (sector_cnt-- > 0) {

		/* per 32-bit word write out */
		word_cnt = SDD_SECTOR_SIZE >> 2;
		while (word_cnt > 0) {

			SDD_TRACE(("- word_cnt: 0x%08lx\r\n", word_cnt));

			fifo_depth = SDC_FIFO_WORD_DEPTH;
			while ((fifo_depth-- > 0) && (word_cnt-- > 0)) {

				/* CMD17/18/24/25 ACMD18/25 data are LSB first (little-endian) */
				OUT32(SDC_DATA_WIN, *((uint32_t *) io_buff));	/* just mem-move so no data endian issue. */

				io_buff += 4;
			}

			if (word_cnt == 0)
				break;

			retry = 0;
			while (retry++ < SD_WRITE_MAX_RETRY_COUNT) {

				sdc_status = IN32(SDC_STATUS);
				if (sdc_status &
						(SDC_SR_CARD_DETECT_MASK |
						 SDC_SR_DATA_TIMEOUT_MASK |
						 SDC_SR_DATA_CRC_FAIL_MASK)) {
					status = SDD_WRITE_DATA_ERROR;
					goto _err_exit;
				}
				if (sdc_status &
						(SDC_SR_FIFO_URUN_MASK |
						 SDC_SR_DATA_END_MASK)) {
					SETB32(SDC_CLEAR, SDC_FIFO_URUN_BIT);
					retry = 0xffffffff;	/* success */
					break;
				}
			}

			if (retry != 0xffffffff) {
				/* wait data timeout */
				SDD_TRACE(("- timeout, sdc_status: 0x%08lx\r\n", sdc_status));

				// SDD_TRACE(("- wait again by polling CSR\r\n"));
				// status = _sd_wait_receiving_state(sdd.card_desc.rca);
				// if (status != HAL_SUCCESS)
				goto _err_exit;

				SDD_TRACE(("- card ready, sdc_status: 0x%08lx\r\n", IN32(SDC_STATUS)));
			}
		}
	}

	/* Wait host SDC shift-out FIFO data */
	SDD_TRACE(("- final check sdc_status\r\n"));
	retry = 0;
	while (retry++ < SD_WRITE_MAX_RETRY_COUNT) {

		sdc_status = IN32(SDC_STATUS);
		if (sdc_status &
				(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK |
				 SDC_SR_DATA_CRC_FAIL_MASK)) {

			status = SDD_WRITE_DATA_ERROR;
			goto _err_exit;
		}
		if ((sdc_status == 0) || (sdc_status & SDC_SR_DATA_END_MASK))
			break;
	}

	/* Stop data transmission */
	SDD_TRACE(("- stop transmission\r\n"));
	status = _sd_stop_transmission(sdd.card_desc.rca);
	/* FIXME this part is marked for qemu */
#if 0
	if (status != HAL_SUCCESS)
		goto _err_exit;
#endif
	SDD_TRACE(("- data write completed\r\n"));
	return HAL_SUCCESS;

_err_exit:

	SDD_TRACE(("- error on data write\r\n"));
	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_write_sectors_dma
 *
 * DESCRIPTION
 *
 *   This function performs DMA data transfer to the SD memory card in
 *   multiple unit of sectors.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   sector     : 
 *   sector_cnt :
 *   io_buff    :
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SSPD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_write_sectors_dma(uint32_t sector, uint32_t sector_cnt,
		uint8_t * io_buff)
{
	uint32_t status = SDD_INVALID_FUNCTION;
	SD_R32 sd_rsp32;
	uint32_t retry;
	uint32_t sdc_status;
	DMAD_DRB *drb;
#if 0
	if (sector > (sdd.card_desc.card_capacity << 1)) {

		SDD_TRACE(("Invalid sector address!\r\n"));
		return SDD_INVLAID_ADDRESS;
	}

	if ((sector_cnt == 0) || (((sector + sector_cnt) > (sdd.card_desc.card_capacity << 1)))) {

		SDD_TRACE(("Invalid sector address range!\r\n"));
		return SDD_INVLAID_ADDR_RANGE;
	}
#endif
	if (GETB32(SDC_STATUS, SDC_SR_WRITE_PROT_BIT)) {
		SDD_TRACE(("Card is write protected!\r\n"));
		return SDD_WRITE_PROTECTED;
	}

	/* todo: sector size */

	/* reset dam wait event */
//	hal_set_semaphore(&sdd.dma_sem, 0);

	/* standby -> transfer */
	SDD_TRACE(("- select_card\r\n"));
	status = _sd_select_card(sdd.card_desc.rca);
	if (status != HAL_SUCCESS)
		goto _safe_exit;

	/* send SD command to setup write-block-size */
	/* todo: assume sector size is 512 bytes */
	SDD_TRACE(("- cmd16\r\n"));
	status = _sd_cmd16(SDD_SECTOR_SIZE, &sd_rsp32);
	if (status != HAL_SUCCESS)
		goto _safe_exit;

	/* set SDC data timeout register */
	OUT32(SDC_DATA_TIMER, sdd.card_desc.write_timeout_clks);

	/* set SDC data length register */
	OUT32(SDC_DATA_LEN, sector_cnt * SDD_SECTOR_SIZE);

	/* set SDC data control register */
	OUT32(SDC_DATA_CR, SDC_DATA_EN_MASK | SDC_DATA_WRITE_MASK | SDC_DMA_EN_MASK | ((SDD_POWER_OF_SECTOR_SIZE << SDC_BLK_SIZE_SHIFT) & SDC_BLK_SIZE_MASK));	/* 2^9 = 512 bytes */

	/* send SD command to write data */
	SDD_TRACE(("- cmd25\r\n"));
	if (sdd.card_desc.card_ccs == SDD_CCS_SD)
		status = _sd_cmd25(sector * SDD_SECTOR_SIZE, &sd_rsp32);	/* address unit is byte for SD */
	else
		status = _sd_cmd25(sector, &sd_rsp32);	/* address unit is 512 bytes for SDHC */

	if (status != HAL_SUCCESS)
		goto _safe_exit;

	SDD_TRACE(("- wait ready to write out data\r\n"));
	_nds_kwait(0x1000);	/* hw need delay ? */

	/* This method look not necessary for writing. */
	// status = _sd_wait_receiving_state(sdd.card_desc.rca);
	// if (status != HAL_SUCCESS) */
	//     goto _err_exit; */

	/* per sector DMA write out */
	SDD_TRACE(("- write out data\r\n"));
	
	dmad_apb_config_dir(&sdd.dma_ch, DMAD_DIR_A1_TO_A0);

	if(hal_create_semaphore(&sdd.dma_sem, 0, 0) == HAL_FAILURE)
		SDD_TRACE(("Failed to create dma semaphore\r\n"));

	while (sector_cnt-- > 0) {

		SDD_TRACE(("sector_cnt: %ld\r\n", sector_cnt));

		/* Prepare DRB */
		status = _dmad_alloc_drb(&sdd.dma_ch, &drb);
		if (status != HAL_SUCCESS)
			goto _safe_exit;

		drb->src_addr = (void *)io_buff;
		drb->dst_addr = (void *)SDC_DATA_WIN;
		drb->req_size = SDD_SECTOR_SIZE >> 2;	/* multiple counts of transfer width */

		if (sector_cnt == 0)
			drb->completion_sem = &sdd.dma_sem;	/* Register DMA completion notification */

		/* Submit DRB */
		status = _dmad_submit_request(&sdd.dma_ch, drb);
		if (status != HAL_SUCCESS)
			goto _safe_exit;

		/* Point to next buffer location */
		io_buff += SDD_SECTOR_SIZE;
	}

	/*
	 * Wait DMA completion
	 * - method 1: sync with semaphore
	 * - method 2: check SDC status register SDC_STATUS[7]
	 */
	status = hal_pend_semaphore(&sdd.dma_sem, 600);	/* 6 sec */

	/* Check waiting status */
	if (status == HAL_ERR_TIMEOUT) {

		SDD_TRACE(("- wait dma completion timeout (might not an error)\r\n"));
		goto _safe_exit;
	}
	else if (status != HAL_SUCCESS) {

		SDD_TRACE(("- wait dma completion failed\r\n"));
		goto _safe_exit;
	}

	/* Wait host SDC shift-out FIFO data */
	SDD_TRACE(("- final check sdc_status\r\n"));
	retry = 0;
	while (retry++ < SD_WRITE_MAX_RETRY_COUNT) {

		sdc_status = IN32(SDC_STATUS);
		if (sdc_status &
				(SDC_SR_CARD_DETECT_MASK | SDC_SR_DATA_TIMEOUT_MASK |
				 SDC_SR_DATA_CRC_FAIL_MASK)) {
			status = SDD_WRITE_DATA_ERROR;
			goto _safe_exit;
		}
		if ((sdc_status == 0) || (sdc_status & SDC_SR_DATA_END_MASK))
			break;
	}

	/* Stop data transmission */
	SDD_TRACE(("- stop transmission\r\n"));
	status = _sd_stop_transmission(sdd.card_desc.rca);
	/* FIXME this part is marked for qemu */
#if 0
	if (status != HAL_SUCCESS)
		goto _safe_exit;
#endif
	status = HAL_SUCCESS;

_safe_exit:

#if (SDD_DEBUG_TRACE)
	if (status == HAL_SUCCESS)
		SDD_TRACE(("- data read completed\r\n"));
	else
		SDD_TRACE(("- error on data read\r\n"));
#endif /* SDD_DEBUG_TRACE */

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_lisr
 *
 * DESCRIPTION
 *
 *   This is the ISR that services SD card detection interrupt on the NDS32
 *   evb platform.
 *
 * NOTE
 *
 *   Card Detection Procedures (LISR)
 *    LISR set HISR activation state flag
 *    LISR activates HISR
 *      call _sdd_cd_reset() to perform card insertion or removal tasks.
 *
 *   Card Detection Procedures (_sdd_init)
 *    Perform basic SD controller register setup
 *    Checks SDC_SR_CARD_DETECT_BIT bit
 *      call _sdd_cd_reset() to perform card insertion or removal tasks.
 *
 * INPUTS
 *
 *   vector     : Interrupt vector number
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
void _sdd_lisr(int vector)
{
	DEBUG(1, 1, "_sdd_lisr\r\n");
	printf("hal_raise_bh0\n");
	/* Fault invocation checking */
	if (vector != IRQ_SDC_VECTOR )
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);

	/* Mask : Disable SDC interrupt */
	hal_intc_irq_disable(IRQ_SDC_VECTOR);
	/* Ack : Clean SDC interrupt pending */
	hal_intc_irq_clean(IRQ_SDC_VECTOR);
	
	printf("hal_raise_bh1\n");
	if (GETB32(SDC_STATUS, SDC_SR_CARD_CHANGE_BIT)) {

		SETB32(SDC_CLEAR, SDC_CARD_CHANGE_BIT);

		/* Set HISR status register to get channel number */
		sdd.hisr_as |= SDD_HISR_AS_CD;
		printf("hal_raise_bh2\n");
		hal_raise_bh(&sdd.hisr);	/* Activate HISR to complete deferred tasks */
	}
	else {
		printf("hal_raise_bh3\n");
		/* todo: handle other interrupts. */
		OUT32(SDC_CLEAR, SDC_CLEAR_ALL);
	}

	/* Unmask : Enable SDC interrupt */
	hal_intc_irq_enable(IRQ_SDC_VECTOR);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_hisr
 *
 * DESCRIPTION
 *
 *   This is the HISR that services SD card detection interrupt on the NDS32
 *   evb platform.
 *
 * NOTE
 *   
 *
 * INPUTS
 *
 *
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
void _sdd_hisr(void *param)
{
	hal_bh_t *bh = (hal_bh_t *)param;

	uint32_t core_intl;
	uint8_t hisr_as;	/* HISR activation state - Card Detection */
	while (1){

		DEBUG(1, 1, "_sdd_hisr before\n");
		hal_pend_semaphore(&bh->sem, HAL_SUSPEND);

		/*
		 * Disable CPU interrupt
		 * Todo: frequently int-disable due to frequently HISR-call may cause problems?
		 */
		core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

		/* Clone HISR activation state */
		hisr_as = sdd.hisr_as;
		sdd.hisr_as &= ~(uint32_t) SDD_HISR_AS_CD;

		/* Enable CPU interrupt */
		hal_global_int_ctl(core_intl);

		/* Card detect initialization */
		if (hisr_as & SDD_HISR_AS_CD) {

			if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT)) {

				SDD_TRACE(("SD card removed!\r\n"));

				/* Perform card-remove tasks (turn off clock ...) */
				_sdd_cd_reset(HAL_FALSE);
			}
			else {
				SDD_TRACE(("SD card inserted!\r\n"));
				/* Reset card and get device parameters */
				_sdd_cd_reset(HAL_TRUE);
			}
		}
	}
}

#if (SDD_VFS_SUPPORT)
//STATUS _sdd_read_sectors(SDD_IOCTL_READ_SECTORS_PARAM *iop);

STATUS _sdd_read_sectors_bdev(NDS_BDEV *bdev, UINT32 sector, UINT32 sector_count, void *buffer)
{
    STATUS io_status;
    SDD_DEVICE sdd_dev;        // FIXME, NDS_SD_ReadSectors doesn't use this argument actully

    BDEV_TRACE(("_sdd_read_sectors_bdev()\r\n"));
    BDEV_TRACE(("  read start at sector (0x%08lx + 0x%08lx = 0x%08lx) count (0x%08lx)\r\n",
        bdev->start, sector, bdev->start + sector, sector_count));
#ifndef CONFIG_PLAT_QEMU
    io_status = NDS_SD_ReadSectors(&sdd_dev, bdev->start + sector, sector_count, 512, buffer);
#else
    io_status = NDS_SD_ReadSectors(&sdd_dev, sector, sector_count, 512, buffer);
#endif
#if 0
    if (NU_Current_Task_Pointer() != HAL_NULL)
    {
        // obtain exclusive access to driver
        request.nu_function = NU_ASSIGN;
        request.nu_timeout  = NU_SUSPEND;
        status = NU_Request_Driver(&sdd_dcb, &request);
        if (status != NU_SUCCESS)
            return status;
    }
    // perform i/o operation
    BDEV_TRACE(("  read start at sector (0x%08lx + 0x%08lx = 0x%08lx) count (0x%08lx)\r\n",
        bdev->start, sector, bdev->start + sector, sector_count));
    iop.lba_sector = bdev->start + sector;
    iop.sector_count = sector_count;
    iop.sector_size = SDD_SECTOR_SIZE;
    iop.io_buff = buffer;
    io_status = _sdd_read_sectors(&iop);
    if (NU_Current_Task_Pointer() != HAL_NULL)
    {
        // release exclusive access to driver
        request.nu_function = NU_RELEASE;
        status = NU_Request_Driver(&sdd_dcb, &request);
        if (status != NU_SUCCESS)
            return status;
    }
#endif
    return io_status;
}

//STATUS _sdd_write_sectors(SDD_IOCTL_WRITE_SECTORS_PARAM *iop);

STATUS _sdd_write_sectors_bdev(NDS_BDEV *bdev, UINT32 sector, UINT32 sector_count, void *buffer)
{
    STATUS io_status;
    SDD_DEVICE sdd_dev;        // FIXME, NDS_SD_ReadSectors doesn't use this argument actully

    BDEV_TRACE(("_sdd_write_sectors_bdev()\r\n"));
#ifndef CONFIG_PLAT_QEMU
    io_status = NDS_SD_WriteSectors(&sdd_dev, bdev->start + sector, sector_count, 512, buffer);
#else
    io_status = NDS_SD_WriteSectors(&sdd_dev, sector, sector_count, 512, buffer);
#endif
#if 0
    if (NU_Current_Task_Pointer() != HAL_NULL)
    {
        // obtain exclusive access to driver
        request.nu_function = NU_ASSIGN;
        request.nu_timeout  = NU_SUSPEND;
        status = NU_Request_Driver(&sdd_dcb, &request);
        if (status != NU_SUCCESS)
            return status;
    }

    // perform i/o operation
    BDEV_TRACE(("  write start at sector (0x%08lx + 0x%08lx = 0x%08lx) count (0x%08lx)\r\n",
        bdev->start, sector, bdev->start + sector, sector_count));
    iop.lba_sector = bdev->start + sector;
    iop.sector_count = sector_count;
    iop.sector_size = SDD_SECTOR_SIZE;
    iop.io_buff = buffer;
    io_status = _sdd_write_sectors(&iop);

    if (NU_Current_Task_Pointer() != HAL_NULL)
    {
        // release exclusive access to driver
        request.nu_function = NU_RELEASE;
        status = NU_Request_Driver(&sdd_dcb, &request);
        if (status != NU_SUCCESS)
            return status;
    }
#endif
    BDEV_TRACE(("  status (0x%08lx)\r\n", io_status));
    return io_status;
}
#endif  // SDD_VFS_SUPPORT
/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_init
 *
 * DESCRIPTION
 *
 *   This function initializes the SDC device.
 *
 * NOTE
 *
 *   SD/MEM     : PC-Card Memory mode, PC-Card I/O mode, True-IDE.
 *   SDIO       : Todo.
 *   SDHC       : Not supported.
 *   MMC        : Todo.
 *
 *   Todo       : Resource leaks is not recovered if error happens
 *                during init process.  Client currently has to do
 *                TERMINATE request anyway, if driver load/unload
 *                resource control is a necessary, no-matter the
 *                initialization process is successful or not.
 *
 * INPUTS
 *
 *   sdd_dev    : user device struct
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_init(SDD_DEVICE * sdd_dev)
{
	uint32_t status = HAL_SUCCESS;
	uint32_t core_intl;

	SDD_TRACE(("_sdd_init()\r\n"));
	
	/* Perform Parameter Checking */

#if (!SDD_SMALL_FOOTPRINT)
	/* Check supplemental init structure */
	if (sdd_dev == HAL_NULL) {

		SDD_TRACE(("null sdd_dev!\r\n"));
		return HAL_ERR_INVALID_POINTER;
	}

	/* Check duplicated device initialization */
	if (sdd.valid != 0) {

		/* Error if the device has been initialized */
		SDD_TRACE(("sdd.valid is non-zero!\r\n"));
		return SDD_INVALID_INIT;
	}
#endif /* (!SDD_SMALL_FOOTPRINT) */

	/* Initialize SDC driver resources */

	/* Allocate DMA channel if user requested static DMA channel mode */
	switch (sdd_dev->dma) {
		case SDD_DMA_NONE:
		case SDD_DMA_DCH:
			break;
		case SDD_DMA_SCH:
			status = _sdd_alloc_dma_channel();
			if (status != HAL_SUCCESS)
				return status;
			break;
		default:
			return SDD_INVALID_PARAMETER;
	}

	sdd.dma = sdd_dev->dma;

	/*
	 * Allocate mutex (a semaphore with init count == 1)
	 * for driver access control
	 */
	status = hal_create_mutex(&sdd.semaphore, "sdd_sem");
	if (status != HAL_SUCCESS) {

		SDD_TRACE(("Failed to create SD driver semaphore!\r\n"));
		return status;
	}

	/*
	 * Allocate synchronization object for SDD to receive DMA completion notfication
	 * (init count is 0 so any obtain have to wait first)
	 */
	status = hal_create_semaphore(&sdd.dma_sem, 0, 0);
	if (status != HAL_SUCCESS) {

		SDD_TRACE(("Failed to allocate SD driver dma semaphore!\r\n"));
		hal_destroy_mutex(&sdd.semaphore);
		return status;
	}

	/* Register LISR to receive SDC events */
	if (sdd.lisr_registered == 0) {

		/* Register LISR for SDC events interrupt */
		status = hal_register_isr(IRQ_SDC_VECTOR, _sdd_lisr, (void*)0);

		if (status != HAL_SUCCESS) {

			SDD_TRACE(("Failed to register SD driver LISR!\r\n"));
			hal_destroy_mutex(&sdd.semaphore);
			hal_destroy_semaphore(&sdd.dma_sem);
			return status;
		}

		sdd.lisr_registered = 1;
	}

	/* Register HISR to perform deferred SDC ISR tasks */
	if (sdd.hisr_registered == 0) {
		sdd.hisr.th.fn		= _sdd_hisr;
		sdd.hisr.th.arg		= &sdd.hisr;
		sdd.hisr.th.ptos	= &sdd_hisr_stack[SDD_HISR_STACK_SIZE];
		sdd.hisr.th.stack_size	= sizeof(sdd_hisr_stack);
		sdd.hisr.th.prio	= CONFIG_SDD_HISR_PRIORITY;
		sdd.hisr.th.name	= "SD BH";

		status = hal_create_bh(&sdd.hisr);
		if (status != HAL_SUCCESS) {
			DEBUG(1, 1, "Failed to create SD driver HISR!\r\n");
			hal_destroy_mutex(&sdd.semaphore);
			hal_destroy_semaphore(&sdd.dma_sem);
			return status;
		}
		sdd.hisr_registered = 1;
	}

	/* Update driver data */
#if (SDD_VFS_SUPPORT)
	// Init SDD-specific bdev object
        sdd_bdev.next     = HAL_NULL;
        sdd_bdev.dev_id   = 0;
        sdd_bdev.vol_id   = 0;
        sdd_bdev.type     = 0;                     
	sdd_bdev.start    = 0;                    
	sdd_bdev.blocks   = 0;
	sdd_bdev.propagate_event = HAL_NULL;
	sdd_bdev.read_sectors    = _sdd_read_sectors_bdev;
	sdd_bdev.write_sectors   = _sdd_write_sectors_bdev;
	sdd_dev->bdev_id = &sdd_bdev;
#endif  // SDD_VFS_SUPPORT
    
	/*
	 * Initialize SDC device
	 *
	 * SD card initialization and identification are performed either at
	 *  - when the card was inserted (i.e., triggered from ISR and HISR), or
	 *  - when this init routine was invoked and the card was already in the slot.
	 */

	/* Disable CPU interrupt */
	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* - Disable SDC interrupt */
	hal_intc_irq_disable(IRQ_SDC_VECTOR);
	
	/* - Clear SDC interrupt status */
	hal_intc_irq_clean(IRQ_SDC_VECTOR);
	
	/* - Setup SDC interrupt trigger mode - level trigger */
	/* - Setup SDC interrupt trigger level - assert high */
	hal_intc_irq_config(IRQ_SDC_VECTOR,IRQ_LEVEL_TRIGGER, IRQ_ACTIVE_HIGH);	

	/* - Enable SDC interrupt */
	hal_intc_irq_enable(IRQ_SDC_VECTOR);

#if 0
#if(NO_EXTERNAL_INT_CTL==1)
	/* FIXME 
	 * - Setup SDC interrupt trigger mode */
	/* - Enable SDC interrupt */
	SR_SETB32(NDS32_SR_INT_MASK2,IRQ_SDC_VECTOR );
#else
	/* INTC */
	/* - Disable SDC interrupt */
	CLRB32(INTC_HW1_ER, IRQ_SDC_VECTOR);

	/* - Clear SDC interrupt status */
	SETB32(INTC_HW1_CLR, IRQ_SDC_VECTOR);
	
	/* - Setup SDC interrupt trigger mode - level trigger */
	CLRB32(INTC_HW1_TMR, IRQ_SDC_VECTOR);
	
	/* - Setup SDC interrupt trigger level - assert high */
	CLRB32(INTC_HW1_TLR, IRQ_SDC_VECTOR);
	
	/* - Enable SDC interrupt */
	SETB32(INTC_HW1_ER, IRQ_SDC_VECTOR);
#endif	
#endif

	/* APBMCLKOFF */
	/* todo */

	/*
	 * SDC_PWR_CTL
	 *   SD_POWER       0 (default: 0x00) (leave bootup default?)
	 *   SD_POWER_ON    0 (off) (default: 0x10)
	 */
	CLRB32(SDC_PWR_CTL, SDC_SD_POWER_ON_BIT);
	_nds_kwait(0x4000);

	/*
	 * SDC_CLK_CTL
	 *   CLK_DIV        0x7f (default: 0x7f, result in 97.66K ~ 683.59K SD bus freq)
	 *   CLK_SD         1 (default: 1 (SD))
	 *   CLK_DIS        1 (off) (default: 0x01)
	 */
	OUT32(SDC_CLK_CTL, (SDC_CLK_OFF << SDC_CLK_DIS_BIT) |
			(SDC_CLK_SD << SDC_CLK_SD_BIT) | SDC_CLK_DIV_MASK);

	/*
	 * SDC_MASK (note: spec "mask" means "enable", spec uses wrong term to describe this register)
	 *   RSP_CRC_FAIL   mask int
	 *   DATA_CRC_FAIL  mask int
	 *   RSP_TIMEOUT    mask int
	 *   DATA_TIMEOUT   mask int
	 *   RSP_CRC_OK     mask int
	 *   DATA_CRC_OK    mask int
	 *   CMD_SENT       mask int
	 *   DATA_END       mask int
	 *   FIFO_U_RUN     mask int
	 *   FIFO_O_RUN     mask int
	 *   CARD_CHANGE    enable int
	 */
	OUT32(SDC_MASK, SDC_CARD_CHANGE_MASK);

	/* SDC_CLEAR */
	/*   Clear all */
	OUT32(SDC_CLEAR, SDC_CLEAR_ALL);

	/*
	 * Following host controller register register setting needs information
	 * from the card, hence is postponed in the card initialization and
	 * identification routine.
	 *
	 * Data setup (need CSD/SCR)
	 *
	 *   SDC_DATA_CR        (setup before data transfer)
	 *   SDC_DATA_TIMER     (TAAC/NSAC)
	 *   SDC_DATA_LEN       (READ/WRITE/ERASE_BL_LEN, SECTOR_SIZE)
	 *   SDC_BUS_WIDTH      (SCR::SD_BUS_WIDTHS)
	 *
	 * Power/Clock settings (need OCR)
	 *
	 *   SDC_PWR_CTL        (OCR::Vdd)
	 *   SDC_CLK_CTL        (fod, fpp)
	 */

	/*
	 * Detect card and perform card-detection initialization, if the is
	 * already in the slot before we re-enable interrupt.
	 */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT)) {
		/* Perform card-remove tasks (turn off clock ...) */
		SDD_TRACE(("SD card is not in slot!\r\n"));
		_sdd_cd_reset(HAL_FALSE);
	}
	else {
		/* Reset card and get device parameters */
		SDD_TRACE(("SD card is in slot!\r\n"));
		_sdd_cd_reset(HAL_TRUE);
		//_sdd_cd_reset(HAL_TRUE);
		//_sdd_cd_reset(HAL_TRUE);
		//_sdd_cd_reset(HAL_TRUE);
		// FIXME
	}

	/* Restore CPU interrupt controller to previous level */
	hal_global_int_ctl(core_intl);

	/* Mark driver state as valid */
	sdd.valid = 1;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_unload
 *
 * DESCRIPTION
 *
 *   Remove all the device resource so the driver could be removed safely.
 *
 * NOTE
 *
 * INPUTS
 *
 *   none
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_unload(void)
{
	uint32_t status;

#if (!SDD_SMALL_FOOTPRINT)
	/* Validate to terminate an already initialized driver state */
	if (sdd.valid == 0)
		return HAL_ERR_INVALID_DRIVER;
#endif /* (!SDD_SMALL_FOOTPRINT) */

        // Notify file system
#if (SDD_VFS_SUPPORT)
        if (sdd_bdev.propagate_event != HAL_NULL)
            sdd_bdev.propagate_event(&sdd_bdev, NDSBDEV_DEVICE_UNPLUG, HAL_NULL);

        sdd_bdev.next     = HAL_NULL;
        sdd_bdev.dev_id   = 0;
        sdd_bdev.vol_id   = 0;
        sdd_bdev.type     = 0;
        sdd_bdev.start    = 0;
        sdd_bdev.blocks   = 0;
        sdd_bdev.propagate_event = HAL_NULL;
        sdd_bdev.read_sectors    = HAL_NULL;
        sdd_bdev.write_sectors   = HAL_NULL;
#endif  // SDD_VFS_SUPPORT
	/* Shutdown device operation */

	/* Release driver resources */
	if (sdd.dma == SDD_DMA_SCH)
		_sdd_free_dma_channel();

	status = hal_destroy_bh(&sdd.hisr);
	if (status != HAL_SUCCESS)
		return status;

	status = hal_destroy_semaphore(&sdd.dma_sem);
	if (status != HAL_SUCCESS)
		return status;

	status = hal_destroy_mutex(&sdd.semaphore);
	if (status != HAL_SUCCESS)
		return status;

	sdd.valid = 0;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_lock
 *
 * DESCRIPTION
 *
 *   Obtain exclusive access to the devcie driver.
 *
 * NOTE
 *
 * INPUTS
 *
 *   none
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static inline uint32_t _sdd_lock(void)
{
#if (!SDD_SMALL_FOOTPRINT)
	if (sdd.valid == 0)
		return HAL_ERR_INVALID_DRIVER;
#endif /* (!SDD_SMALL_FOOTPRINT) */

	return hal_wait_for_mutex(&sdd.semaphore, HAL_SUSPEND);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_unlock
 *
 * DESCRIPTION
 *
 *   Release exclusive access to the device driver.
 *
 * NOTE
 *
 * INPUTS
 *
 *   none
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static inline uint32_t _sdd_unlock(void)
{
#if (!SDD_SMALL_FOOTPRINT)
	if (sdd.valid == 0)
		return HAL_ERR_INVALID_DRIVER;
#endif /* (!SDD_SMALL_FOOTPRINT) */

	return hal_release_mutex(&sdd.semaphore);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_read_sectors
 *
 * DESCRIPTION
 *
 *   Read sectors of data from the card.  This is the DMA/PIO mode data-
 *   read dispatch function for client IOCTL request.
 *
 * NOTE
 *
 * INPUTS
 *
 *   iop        : pointer to SDD_IOCTL_READ_SECTORS_PARAM struct which
 *                specifies the IOCTL parameters.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_read_sectors(SDD_IOCTL_READ_SECTORS_PARAM * iop)
{
	uint32_t sector = iop->lba_sector;
	uint32_t sector_cnt = iop->sector_count;
	uint8_t *io_buff = (uint8_t *) iop->io_buff;
	uint32_t status;
	uint32_t core_intl;
	uint32_t rca = 0;

	SDD_TRACE(("\r\n_sdd_read_sectors\r\n"));

	/* Disable CPU interrupt */
	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Check if SD card has been initialized to transfer state */
	rca = sdd.card_desc.rca;

	/* Restore CPU interrupt controller to previous level */
	hal_global_int_ctl(core_intl);

	/* Reject if SD card is not initialized to transfer state */
	if (rca == 0)
		return SDD_INVALID_INIT;

	/* Data transfer ... */
	if ((sdd.dma != SDD_DMA_NONE) /* && (hal_current() != HAL_NULL) */ ) {
		SDD_TRACE(("dma - sector(%ld) counts(%ld)\r\n", sector,
					sector_cnt));

		if (sdd.dma == SDD_DMA_DCH) {

			status = _sdd_alloc_dma_channel();
			if (status != HAL_SUCCESS)
				return status;
		}

		while (sector_cnt > 0) {
			/*
			 * SDC data length register max is 24 bits (32768 sectors).
			 * Divided by 2 for safe in case sector size is larger than 512 bytes.
			 * (so max sector size should be less than 1024 bytes)
			 */
			if (sector_cnt >= 16384) {

				/* Use SD multiple block transfer for sectors. */
				status = _sdd_read_sectors_dma(sector, 16384, io_buff);

				if (status != HAL_SUCCESS) {

					/* Release DMA channel */
					if (sdd.dma == SDD_DMA_DCH)
						_sdd_free_dma_channel();
					return status;
				}

				sector += 16384;
				sector_cnt -= 16384;
				io_buff += SDD_SECTOR_SIZE * 16384;
			}
			else {
				/* Use SD multiple block transfer for all sectors. */
				status = _sdd_read_sectors_dma(sector, sector_cnt, io_buff);
				sector_cnt = 0;
			}
		}

		/* Wait for DMA completion signal */

		/* Release DMA channel */
		if (sdd.dma == SDD_DMA_DCH)
			_sdd_free_dma_channel();
	}
	else {
		/* PIO mode data transfer */
		SDD_TRACE(("pio - sector(%ld) counts(%ld)\r\n", sector, sector_cnt));

		while (sector_cnt > 0) {
			/*
			 * SDC data length register max is 24 bits (32768 sectors).
			 * Divided by 2 for safe in case sector size is larger than 512 bytes.
			 * (so max sector size should be less than 1024 bytes)
			 */
			if (sector_cnt >= 16384) {
				/* Use SD multiple block transfer for sectors. */
				status = _sdd_read_sectors_pio(sector, 16384, io_buff);

				if (status != HAL_SUCCESS)
					return status;

				sector += 16384;
				sector_cnt -= 16384;
				io_buff += SDD_SECTOR_SIZE * 16384;
			}
			else {
				/* Use SD multiple block transfer for all sectors. */
				status = _sdd_read_sectors_pio(sector, sector_cnt, io_buff);
				sector_cnt = 0;
			}
		}
	}

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_write_sectors
 *
 * DESCRIPTION
 *
 *   Write sectors of data to the card.  This is the DMA/PIO mode data-
 *   write dispatch function for client IOCTL request.
 *
 * NOTE
 *
 * INPUTS
 *
 *   iop        : pointer to SDD_IOCTL_READ_SECTORS_PARAM struct which
 *                specifies the IOCTL parameters.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _sdd_write_sectors(SDD_IOCTL_WRITE_SECTORS_PARAM * iop)
{
	uint32_t sector = iop->lba_sector;
	uint32_t sector_cnt = iop->sector_count;
	uint8_t *io_buff = (uint8_t *) iop->io_buff;
	uint32_t status;
	uint32_t core_intl;
	uint32_t rca = 0;

	SDD_TRACE(("\r\n_sdd_write_sectors\r\n"));

	/* Disable CPU interrupt */
	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Check if SD card has been initialized to transfer state */
	rca = sdd.card_desc.rca;

	/* Restore CPU interrupt controller to previous level */
	hal_global_int_ctl(core_intl);

	/* Reject if SD card is not initialized to transfer state */
	if (rca == 0)
		return SDD_INVALID_INIT;

	/* Data transfer ... */
	if ((sdd.dma != SDD_DMA_NONE) /* && (hal_current() != HAL_NULL) */ ) {
		SDD_TRACE(("dma - sector(%ld) counts(%ld)\r\n", sector,
					sector_cnt));

		if (sdd.dma != SDD_DMA_SCH) {

			status = _sdd_alloc_dma_channel();
			if (status != HAL_SUCCESS)
				return status;
		}

		while (sector_cnt > 0) {
			/*
			 * SDC data length register max is 24 bits (32768 sectors).
			 * Divided by 2 for safe in case sector size is larger than 512 bytes.
			 * (so max sector size should be less than 1024 bytes)
			 */
			if (sector_cnt >= 16384) {
				/* Use SD multiple block transfer for sectors. */
				status = _sdd_write_sectors_dma(sector, 16384, io_buff);

				if (status != HAL_SUCCESS) {

					if (sdd.dma == SDD_DMA_DCH)
						_sdd_free_dma_channel();

					return status;
				}

				sector += 16384;
				sector_cnt -= 16384;
				io_buff += SDD_SECTOR_SIZE * 16384;
			}
			else {
				/* Use SD multiple block transfer for all sectors. */
				status = _sdd_write_sectors_dma(sector, sector_cnt, io_buff);
				sector_cnt = 0;
			}
		}

		/* Wait for DMA completion signal */

		/* Release DMA channel */
		if (sdd.dma == SDD_DMA_DCH)
			_sdd_free_dma_channel();
	}
	else {
		/* PIO mode data transfer */
		SDD_TRACE(("pio - sector(%ld) counts(%ld)\r\n", sector,
					sector_cnt));

		while (sector_cnt > 0) {
			/*
			 * SDC data length register max is 24 bits (32768 sectors).
			 * Divided by 2 for safe in case sector size is larger than 512 bytes.
			 * (so max sector size should be less than 1024 bytes)
			 */
			if (sector_cnt >= 16384) {
				/* Use SD multiple block transfer for sectors. */
				status = _sdd_write_sectors_pio(sector, 16384, io_buff);

				if (status != HAL_SUCCESS)
					return status;

				sector += 16384;
				sector_cnt -= 16384;
				io_buff += SDD_SECTOR_SIZE * 16384;
			}
			else {
				/* Use SD multiple block transfer for all sectors. */
				status = _sdd_write_sectors_pio(sector, sector_cnt, io_buff);
				sector_cnt = 0;
			}
		}
	}

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sdd_ioctl
 *
 * DESCRIPTION
 *
 *   This function execute I/O control commands to SDC driver.
 *
 * NOTE
 *
 *
 * INPUTS
 *
 *   driver     : device object/control_block
 *   request    : request function and supplemental parameters
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is SDD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static inline uint32_t _sdd_ioctl(uint32_t ioctl, void *param)
{
	uint32_t status = HAL_SUCCESS;

#if (!SDD_SMALL_FOOTPRINT)
	/* Validate to terminate an already initialized driver state */
	if (sdd.valid == 0)
		return HAL_ERR_INVALID_DRIVER;
#endif /* (!UARTD_SMALL_FOOTPRINT) */

	if (param == HAL_NULL)
		return SDD_INVALID_PARAMETER;

	switch (ioctl) {
		case SDD_IOCTL_READ_SECTORS:
			/* Parameter: pointer to SDD_IOCTL_READ_SECTORS_PARAM struct */
			status = _sdd_read_sectors((SDD_IOCTL_READ_SECTORS_PARAM *) param);
			break;

		case SDD_IOCTL_WRITE_SECTORS:
			/* Parameter: pointer to SDD_IOCTL_READ_SECTORS_PARAM struct */
			status = _sdd_write_sectors((SDD_IOCTL_WRITE_SECTORS_PARAM *) param);
			break;

		default:
			status = SDD_INVALID_IOCTL;
			break;
	}

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   NDS_SD_Init
 *
 * DESCRIPTION
 *
 *   This function initializes the SD device.
 *
 * INPUTS
 *
 *   sdd_dev       :   User mode SDD device structure.
 *
 * OUTPUTS
 *
 *   uint32_t        :   Returns HAL_SUCCESS if successful initialization,
 *                     else a negative value is returned.
 *
 ****************************************************************************/
uint32_t NDS_SD_Init(SDD_DEVICE * sdd_dev)
{
	return _sdd_init(sdd_dev);
}

/*****************************************************************************
 * FUNCTION
 
 *   NDS_SD_Unload
 *
 * DESCRIPTION
 *
 *   This function terminates all SD transaction and unload the driver.
 *
 * INPUTS
 *
 *   None.
 *
 * OUTPUTS
 *
 *   None.
 *
 ****************************************************************************/
void NDS_SD_Unload()
{
	_sdd_unload();
}

/*****************************************************************************
 * FUNCTION
 *
 *   NDS_SD_ReadSectors
 *
 * DESCRIPTION
 *
 *   This function read sectors of data from the SD memory card.
 *
 * INPUTS
 *
 *   sdd_dev      : User mode SDD device structure.
 *   sector       : The starting LBA sector number.
 *   sector_count : Number of sectors to read.
 *   sector_size  : Size of a sector in bytes.
 *   buffer       : Pointer to a user buffer to hold the readback data.
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful initialization,
 *            else a negative value is returned.
 *
 ****************************************************************************/
uint32_t NDS_SD_ReadSectors(SDD_DEVICE * sdd_dev, uint32_t sector,
		uint32_t sector_count, uint32_t sector_size,
		void *buffer)
{
	uint32_t status;
	uint32_t io_status;
	SDD_IOCTL_READ_SECTORS_PARAM iop;

	status = _sdd_lock();
	if (status != HAL_SUCCESS)
		hal_system_error(status);

	iop.lba_sector = sector;
	iop.sector_count = sector_count;
	iop.sector_size = sector_size;
	iop.io_buff = buffer;

	io_status = _sdd_read_sectors(&iop);

	status = _sdd_unlock();
	if (status != HAL_SUCCESS)
		hal_system_error(status);

	return io_status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   NDS_SD_WriteSectors
 *
 * DESCRIPTION
 *
 *   This function write sectors of data to the SD memory card.
 *
 * INPUTS
 *
 *   sdd_dev      : User mode SDD device structure.
 *   sector       : The starting LBA sector number.
 *   sector_count : Number of sectors to write.
 *   sector_size  : Size of a sector in bytes.
 *   buffer       : Pointer to a user buffer of data to be written to the card.
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful initialization,
 *            else a negative value is returned.
 *
 ****************************************************************************/
uint32_t NDS_SD_WriteSectors(SDD_DEVICE * sdd_dev, uint32_t sector,
		uint32_t sector_count, uint32_t sector_size,
		void *buffer)
{
	uint32_t status;
	uint32_t io_status;
	SDD_IOCTL_WRITE_SECTORS_PARAM iop;
	status = _sdd_lock();
	if (status != HAL_SUCCESS)
		hal_system_error(status);

	iop.lba_sector = sector;
	iop.sector_count = sector_count;
	iop.sector_size = sector_size;
	iop.io_buff = buffer;

	io_status = _sdd_write_sectors(&iop);

	status = _sdd_unlock();
	if (status != HAL_SUCCESS)
		hal_system_error(status);

	return io_status;
}
