
/**
 * \file
 *
 * \brief SAM DMA Controller (XDMAC) Interface
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <hpl_dma.h>
#include <hpl_xdmac_config.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <utils_assert.h>
#include <utils_repeat_macro.h>

#if CONF_DMA_ENABLE
#define DMAC_CH_NUM 24

/* Array containing callbacks for DMAC channels */
static struct _dma_resource _resources[DMAC_CH_NUM];

/* This macro DMAC configuration */
#define DMAC_CHANNEL_CFG(i, n)                                                                                         \
	{XDMAC_CC_MBSIZE(CONF_DMAC_BURSTSIZE_##n) | XDMAC_CC_CSIZE(CONF_DMAC_CHUNKSIZE_##n)                                \
	     | XDMAC_CC_DWIDTH(CONF_DMAC_BEATSIZE_##n) | (CONF_DMAC_SRC_INTERFACE_##n << XDMAC_CC_SIF_Pos)                 \
	     | (CONF_DMAC_DES_INTERFACE_##n << XDMAC_CC_DIF_Pos)                                                           \
	     | XDMAC_CC_SAM((CONF_DMAC_SRC_STRIDE_##n == -1) ? 3 : CONF_DMAC_SRCINC_##n)                                   \
	     | XDMAC_CC_DAM((CONF_DMAC_DES_STRIDE_##n == -1) ? 3 : CONF_DMAC_DSTINC_##n)                                   \
	     | (CONF_DMAC_TYPE_##n << XDMAC_CC_TYPE_Pos) | (CONF_DMAC_DSYNC_##n << XDMAC_CC_DSYNC_Pos)                     \
	     | (CONF_DMAC_SWREQ_##n << XDMAC_CC_SWREQ_Pos)                                                                 \
	     | ((!CONF_DMAC_SWREQ_##n) ? XDMAC_CC_PERID(CONF_DMAC_TRIGSRC_##n) : 0x0),                                     \
	 XDMAC_CDS_MSP_SDS_MSP(CONF_DMAC_SRC_STRIDE_##n) | XDMAC_CDS_MSP_DDS_MSP(CONF_DMAC_DES_STRIDE_##n)},

/* DMAC channel configuration */
struct dmac_channel_cfg {
	uint32_t config_reg;
	uint32_t cds_msp;
};

/* DMAC channel configurations */
const static struct dmac_channel_cfg _cfgs[] = {REPEAT_MACRO(DMAC_CHANNEL_CFG, i, DMAC_CH_NUM)};

int32_t _dma_init(void)
{
	uint8_t i;

	/* Clear the pending Interrupt Status bit */
	for (i = 0; i < DMAC_CH_NUM; i++) {
		hri_xdmac_read_CIS_reg(XDMAC, i);
	}
	/* Configuration Registers */
	for (i = 0; i < DMAC_CH_NUM; i++) {
		hri_xdmac_write_CNDC_reg(XDMAC, i, 0x0);
		hri_xdmac_write_CBC_reg(XDMAC, i, 0x0);
		hri_xdmac_write_CSUS_reg(XDMAC, i, 0x0);
		hri_xdmac_write_CDUS_reg(XDMAC, i, 0x0);
		hri_xdmac_write_CC_reg(XDMAC, i, _cfgs[i].config_reg);
		hri_xdmac_write_CDS_MSP_reg(XDMAC, i, _cfgs[i].cds_msp);
	}

	NVIC_DisableIRQ(XDMAC_IRQn);
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_EnableIRQ(XDMAC_IRQn);

	return ERR_NONE;
}

int32_t _dma_set_destination_address(const uint8_t channel, const void *const dst)
{
	hri_xdmac_write_CDA_reg(XDMAC, channel, (uint32_t)dst);

	return ERR_NONE;
}

int32_t _dma_set_source_address(const uint8_t channel, const void *const src)
{
	hri_xdmac_write_CSA_reg(XDMAC, channel, (uint32_t)src);

	return ERR_NONE;
}

int32_t _dma_srcinc_enable(const uint8_t channel, const bool enable)
{
	if (!enable && (hri_xdmac_read_CC_DWIDTH_bf(XDMAC, channel) != XDMAC_CC_DWIDTH_WORD_Val)) {
		/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source
		 * address or fixed destination address mode, source and destination addresses
		 * are incremented by 8-bit or 16-bit.
		 * Workaround: The user can fix the problem by setting the source addressing
		 * mode to use micro block and data striding with micro block stride set to 0 and
		 * data stride set to -1.
		 */
		hri_xdmac_write_CC_SAM_bf(XDMAC, channel, XDMAC_CC_SAM_UBS_DS_AM_Val);
		hri_xdmac_write_CDS_MSP_SDS_MSP_bf(XDMAC, channel, (int16_t)(-1));
	} else {
		hri_xdmac_write_CC_SAM_bf(XDMAC, channel, enable);
	}

	return ERR_NONE;
}

int32_t _dma_dstinc_enable(const uint8_t channel, const bool enable)
{
	if (!enable && (hri_xdmac_read_CC_DWIDTH_bf(XDMAC, channel) != XDMAC_CC_DWIDTH_WORD_Val)) {
		/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source
		 * address or fixed destination address mode, source and destination addresses
		 * are incremented by 8-bit or 16-bit.
		 * Workaround: The user can fix the problem by setting the source addressing
		 * mode to use micro block and data striding with micro block stride set to 0 and
		 * data stride set to -1.
		 */
		hri_xdmac_write_CC_DAM_bf(XDMAC, channel, XDMAC_CC_DAM_UBS_DS_AM_Val);
		hri_xdmac_write_CDS_MSP_SDS_MSP_bf(XDMAC, channel, (int16_t)(-1));
	} else {
		hri_xdmac_write_CC_DAM_bf(XDMAC, channel, enable);
	}

	return ERR_NONE;
}

int32_t _dma_set_data_amount(const uint8_t channel, const uint32_t amount)
{
	uint8_t width;

	width = hri_xdmac_get_CC_DWIDTH_bf(XDMAC, channel, 0x3);
	hri_xdmac_write_CUBC_reg(XDMAC, channel, amount >> width);

	return ERR_NONE;
}

int32_t _dma_enable_transaction(const uint8_t channel, const bool software_trigger)
{
	hri_xdmac_set_GS_reg(XDMAC, 1 << channel);

	if (software_trigger) {
		hri_xdmac_write_GSWR_reg(XDMAC, 1 << channel);
	}

	return ERR_NONE;
}

int32_t _dma_get_channel_resource(struct _dma_resource **resource, const uint8_t channel)
{
	*resource = &_resources[channel];

	return ERR_NONE;
}

void _dma_set_irq_state(const uint8_t channel, const enum _dma_callback_type type, const bool state)
{
	if (state) {
		if (type == DMA_TRANSFER_COMPLETE_CB) {
			hri_xdmac_set_CIM_reg(XDMAC, channel, XDMAC_CIE_BIE);
		} else if (type == DMA_TRANSFER_ERROR_CB) {
			hri_xdmac_set_CIM_reg(XDMAC, channel, XDMAC_CIE_RBIE | XDMAC_CIE_WBIE | XDMAC_CIE_ROIE);
		}
		hri_xdmac_set_GIM_reg(XDMAC, (1 << channel));
	} else {
		if (type == DMA_TRANSFER_COMPLETE_CB) {
			hri_xdmac_clear_CIM_reg(XDMAC, channel, XDMAC_CID_BID);
		} else if (type == DMA_TRANSFER_ERROR_CB) {
			hri_xdmac_clear_CIM_reg(XDMAC, channel, XDMAC_CID_RBEID | XDMAC_CID_WBEID | XDMAC_CID_ROID);
		}
		hri_xdmac_clear_GIM_reg(XDMAC, (1 << channel));
	}
}

/**
 * \internal XDMAC interrupt handler
 */
void XDMAC_Handler(void)
{
	uint32_t              status;
	struct _dma_resource *tmp_resource;
	int8_t                channel = -1;
	uint32_t              pend;

	pend = hri_xdmac_read_GIS_reg(XDMAC);

	/* Get the first pending channel ID */
	for (uint8_t i = 0; i < DMAC_CH_NUM; i++) {
		if ((pend >> i) & 1) {
			channel = i;
			break;
		}
	}

	if (channel < 0) {
		return;
	}

	tmp_resource = &_resources[channel];
	status       = hri_xdmac_read_CIS_reg(XDMAC, channel);

	if (status & (XDMAC_CIS_RBEIS | XDMAC_CIS_WBEIS | XDMAC_CIS_ROIS)) {
		tmp_resource->dma_cb.error(tmp_resource);
	} else if (status & XDMAC_CIS_BIS) {
		tmp_resource->dma_cb.transfer_done(tmp_resource);
	}
}

#endif /* CONF_DMA_ENABLE */
